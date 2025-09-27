#include <Arduino.h>
#include <TFT_eSPI.h>
#include <VL53L0X.h>
#include <SPI.h>
#include "tinyml_classifier.h"

// Inicialização do display TFT
TFT_eSPI tft = TFT_eSPI();

// Inicialização do sensor VL53L0X
VL53L0X sensor;

// Inicialização do classificador TinyML
TinyMLClassifier tinyml;

// Definição dos pinos I2C para o sensor VL53L0X
// Usando I2C0: GP12 (SDA) e GP13 (SCL) - pinos dedicados I2C
#define SDA_PIN 12
#define SCL_PIN 13

// Cores para o display com ALTO CONTRASTE - Valores específicos
#define COLOR_BACKGROUND_GREEN 0x07E0        // Verde RGB565
#define COLOR_BACKGROUND_YELLOW 0xFFE0       // Amarelo RGB565
#define COLOR_BACKGROUND_RED 0xF800          // Vermelho RGB565
#define COLOR_TEXT_WHITE 0xFFFF               // Branco RGB565
#define COLOR_TEXT_BLACK 0x0000              // Preto RGB565

// Variáveis para controle de estado
uint16_t distanciaAtual = 0;
bool sensorOK = false;
String ultimaPredicao = "";
float ultimaConfianca = 0.0f;

// Controle de tempo para atualizações
unsigned long ultimaAtualizacao = 0;
const unsigned long INTERVALO_ATUALIZACAO = 1000; // 1 segundo

// Declaração das funções
void atualizarDisplayTinyML(String predicao, float confianca);

void setup() {
  // Inicializa a comunicação serial para debug
  Serial.begin(115200);
  delay(2000);
  Serial.println("=== SISTEMA TINYML MELHORADO DE MONITORAMENTO ===");
  Serial.println("Lilygo T-PicoC3 Pi RP2040 LCD + VL53L0X");
  Serial.println("Modelo: MLP (1→8→8→3) com dataset volumoso (677 amostras)");
  Serial.println("Acurácia: 100% | Confiança: Variável e realista");

  // Inicialização do display TFT (mesmo código que funcionou)
  Serial.println("Inicializando display TFT...");
  
  // Configuração manual dos pinos (baseada no projeto de referência)
  pinMode(4, OUTPUT); // TFT_BL
  pinMode(0, OUTPUT); // TFT_RST
  pinMode(5, OUTPUT); // TFT_CS
  pinMode(1, OUTPUT); // TFT_DC
  
  digitalWrite(0, LOW);
  delay(10);
  digitalWrite(0, HIGH);
  delay(10);
  digitalWrite(4, HIGH); // Ativar backlight
  
  SPI.begin();
  delay(100);
  tft.init();
  delay(100);
  tft.setRotation(0);
  tft.fillScreen(TFT_BLACK);
  
  // Teste de cores específicas do projeto
  Serial.println("=== TESTE CORES ESPECÍFICAS ===");
  tft.fillScreen(COLOR_BACKGROUND_GREEN);
  delay(500);
  tft.fillScreen(COLOR_BACKGROUND_YELLOW);
  delay(500);
  tft.fillScreen(COLOR_BACKGROUND_RED);
  delay(500);
  tft.fillScreen(TFT_BLACK);
  
  Serial.println("Display TFT inicializado com sucesso!");

  // Configura os pinos I2C
  Wire.setSDA(SDA_PIN);
  Wire.setSCL(SCL_PIN);
  Wire.begin();

  // Inicializa o sensor VL53L0X
  Serial.println("Inicializando sensor VL53L0X...");
  
  for (int tentativas = 0; tentativas < 5; tentativas++) {
    Serial.print("Tentativa ");
    Serial.print(tentativas + 1);
    Serial.println(" de inicializar sensor...");
    
    if (sensor.init()) {
      sensorOK = true;
      Serial.println("✅ Sensor VL53L0X inicializado com sucesso!");
      sensor.setTimeout(500);
      sensor.startContinuous();
      break;
    } else {
      Serial.println("Falha na inicialização do sensor, tentando novamente...");
      delay(1000);
    }
  }
  
  if (!sensorOK) {
    Serial.println("⚠️ AVISO: Sensor VL53L0X não encontrado!");
    Serial.println("Conecte o sensor e reinicie a placa.");
    tft.fillScreen(TFT_YELLOW);
    tft.setTextColor(TFT_BLACK, TFT_YELLOW);
    tft.setTextSize(2);
    tft.setCursor(10, 10);
    tft.print("SENSOR");
    tft.setCursor(10, 30);
    tft.print("NAO ENCONTRADO");
    tft.setTextSize(1);
    tft.setCursor(10, 50);
    tft.print("Conecte e reinicie");
  } else {
    Serial.println("Sistema inicializado com sucesso!");
  }
  
  // Inicialização do modelo TinyML
  if (tinyml.loadModel()) {
    Serial.println("✅ Sistema TinyML pronto!");
    tinyml.printModelInfo();
    
    // Tela inicial TinyML
    tft.fillScreen(COLOR_BACKGROUND_GREEN);
    tft.setTextColor(COLOR_TEXT_BLACK, COLOR_BACKGROUND_GREEN);
    tft.setTextSize(2);
    tft.setCursor(10, 10);
    tft.print("TINYML");
    tft.setCursor(10, 30);
    tft.print("PRONTO");
    tft.setTextSize(1);
    tft.setCursor(10, 50);
    tft.print("Modelo MLP carregado");
    delay(2000);
  } else {
    Serial.println("❌ Erro ao carregar modelo TinyML!");
  }
}

void loop() {
  unsigned long tempoAtual = millis();
  
  // Lê a distância do sensor VL53L0X
  if (sensorOK) {
    distanciaAtual = sensor.readRangeContinuousMillimeters();
    
    // Verifica se a leitura é válida
    if (sensor.timeoutOccurred()) {
      Serial.println("Timeout do sensor!");
      return;
    }
  } else {
    // Simula leitura quando sensor não está conectado
    distanciaAtual = 1500; // Distância média = baú vazio
    Serial.println("Sensor não conectado - simulando baú vazio");
  }

  // Predição usando TinyML (apenas a cada intervalo)
  if (tempoAtual - ultimaAtualizacao >= INTERVALO_ATUALIZACAO) {
    String predicao = tinyml.predict(distanciaAtual);
    float confianca = tinyml.getConfidence(distanciaAtual);
    
    // Atualizar display apenas se mudou
    if (predicao != ultimaPredicao || (confianca - ultimaConfianca) * (confianca - ultimaConfianca) > 0.0025f) {
      ultimaPredicao = predicao;
      ultimaConfianca = confianca;
      atualizarDisplayTinyML(predicao, confianca);
    }
    
    ultimaAtualizacao = tempoAtual;
    
    // Debug no serial com confiança corrigida
    Serial.print("📊 Distância: ");
    Serial.print(distanciaAtual);
    Serial.print("mm - Predição: ");
    Serial.print(predicao);
    Serial.print(" - Confiança: ");
    Serial.print(confianca * 100, 1);
    Serial.println("%");
  }
  
  delay(100); // Pequeno delay para estabilidade
}

void atualizarDisplayTinyML(String predicao, float confianca) {
  uint16_t corFundo, corTexto;
  
  // Determinar cores baseado na predição do modelo TinyML
  if (predicao == "CHEIO") {
    corFundo = COLOR_BACKGROUND_RED;
    corTexto = COLOR_TEXT_WHITE;
  } else if (predicao == "PARCIAL") {
    corFundo = COLOR_BACKGROUND_YELLOW;
    corTexto = COLOR_TEXT_BLACK;
  } else { // VAZIO
    corFundo = COLOR_BACKGROUND_GREEN;
    corTexto = COLOR_TEXT_BLACK;
  }
  
  // Limpar tela e definir cor de fundo
  tft.fillScreen(corFundo);
  
  // Configurar texto
  tft.setTextColor(corTexto, corFundo);
  
  // Status do baú (grande)
  tft.setTextSize(2);
  tft.setCursor(10, 10);
  tft.print("BAU " + predicao);
  
  // Distância atual
  tft.setTextSize(1);
  tft.setCursor(10, 30);
  tft.print("DISTANCIA:");
  
  tft.setTextSize(2);
  tft.setCursor(10, 40);
  tft.print(String(distanciaAtual) + " mm");
  
  // Confiança da predição
  tft.setTextSize(1);
  tft.setCursor(10, 60);
  tft.print("CONFIANCA:");
  tft.print(String(confianca * 100, 1) + "%");
  
  // Indicador TinyML
  tft.setTextSize(1);
  tft.setCursor(10, 70);
  tft.print("TINYML AI");
  
  // Barra de confiança visual
  int barraWidth = (int)(confianca * 100);
  tft.fillRect(10, 80, barraWidth, 5, corTexto);
  tft.drawRect(10, 80, 100, 5, corTexto);
}