#include <Arduino.h>
#include <TFT_eSPI.h>
#include <VL53L0X.h>

// Inicialização do display TFT
TFT_eSPI tft = TFT_eSPI();

// Inicialização do sensor VL53L0X
VL53L0X sensor;

// Definição dos pinos I2C para o sensor VL53L0X
// Usando I2C0: GP12 (SDA) e GP13 (SCL) - pinos dedicados I2C
#define SDA_PIN 12
#define SCL_PIN 13

// Definição das distâncias limite em milímetros
const int distanciaCheio = 400;    // Menos de 20cm = Baú cheio (vermelho)
const int distanciaParcial = 800;  // Entre 20-40cm = Baú parcial (amarelo)
// Mais de 40cm = Baú vazio (verde)

// Cores para o display com ALTO CONTRASTE - Valores específicos
#define COLOR_BACKGROUND_GREEN 0x07E0        // Verde RGB565
#define COLOR_BACKGROUND_YELLOW 0xFFE0       // Amarelo RGB565
#define COLOR_BACKGROUND_RED 0xF800          // Vermelho RGB565
#define COLOR_TEXT_WHITE 0xFFFF               // Branco RGB565
#define COLOR_TEXT_BLACK 0x0000              // Preto RGB565

// Variáveis para controle de estado
enum EstadoBaú {
  CHEIO,
  PARCIAL,
  VAZIO
};

EstadoBaú estadoAtual = VAZIO;
uint16_t distanciaAtual = 0;
bool sensorOK = false;

// Declaração das funções
void atualizarDisplay();
void atualizarDistancia();

void setup() {
  // Inicializa a comunicação serial para debug
  Serial.begin(115200);
  Serial.println("Iniciando sistema de monitoramento do baú...");

  // Inicializa o display TFT
  Serial.println("Inicializando display TFT...");
  Serial.println("Dimensões: 135x240 pixels");
  
  tft.init();
  tft.setRotation(0);
  tft.fillScreen(TFT_BLACK);
  delay(200);
  
  // Teste inicial do display com dimensões corretas
  Serial.println("=== TESTE DE CORES DO DISPLAY ===");
  Serial.println("Testando VERMELHO (TFT_RED)...");
  tft.fillScreen(TFT_RED);
  delay(1500);
  Serial.println("Testando VERDE (TFT_GREEN)...");
  tft.fillScreen(TFT_GREEN);
  delay(1500);
  Serial.println("Testando AMARELO (TFT_YELLOW)...");
  tft.fillScreen(TFT_YELLOW);
  delay(1500);
  Serial.println("Testando AZUL (TFT_BLUE)...");
  tft.fillScreen(TFT_BLUE);
  delay(1500);
  Serial.println("Testando BRANCO (TFT_WHITE)...");
  tft.fillScreen(TFT_WHITE);
  delay(1500);
  Serial.println("Testando PRETO (TFT_BLACK)...");
  tft.fillScreen(TFT_BLACK);
  delay(1000);
  
  // Teste com cores específicas do projeto
  Serial.println("=== TESTE CORES ESPECÍFICAS ===");
  Serial.println("Testando VERDE PROJETO (0x07E0)...");
  tft.fillScreen(COLOR_BACKGROUND_GREEN);
  delay(1500);
  Serial.println("Testando AMARELO PROJETO (0xFFE0)...");
  tft.fillScreen(COLOR_BACKGROUND_YELLOW);
  delay(1500);
  Serial.println("Testando VERMELHO PROJETO (0xF800)...");
  tft.fillScreen(COLOR_BACKGROUND_RED);
  delay(1500);
  Serial.println("Testando BRANCO PROJETO (0xFFFF)...");
  tft.fillScreen(COLOR_TEXT_WHITE);
  delay(1500);
  Serial.println("Testando PRETO PROJETO (0x0000)...");
  tft.fillScreen(COLOR_TEXT_BLACK);
  delay(1000);
  
  // Configura fonte para o texto - baseado no projeto de referência
  tft.setTextColor(TFT_WHITE, TFT_BLACK);
  tft.setTextSize(2);
  
  // Teste de texto - usando setCursor e print como no projeto de referência
  tft.fillScreen(TFT_BLUE);
  tft.setCursor(10, 10);
  tft.print("DISPLAY OK");
  tft.setCursor(10, 30);
  tft.print("TESTE TEXTO");
  delay(2000);
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
      Serial.println("Sensor VL53L0X inicializado com sucesso!");
      sensor.setTimeout(500);
      sensor.startContinuous();
      break;
    } else {
      Serial.println("Falha na inicialização do sensor, tentando novamente...");
      delay(1000);
    }
  }
  
  if (!sensorOK) {
    Serial.println("AVISO: Sensor VL53L0X não encontrado!");
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
  
  // Tela inicial - usando setCursor como no projeto de referência
  tft.fillScreen(COLOR_BACKGROUND_GREEN);
  tft.setTextColor(COLOR_TEXT_BLACK, COLOR_BACKGROUND_GREEN);
  tft.setTextSize(2);
  tft.setCursor(10, 10);
  tft.print("SISTEMA");
  tft.setCursor(10, 30);
  tft.print("INICIADO");
  delay(2000);
}

void loop() {
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
    distanciaAtual = 1000; // Distância alta = baú vazio
    Serial.println("Sensor não conectado - simulando baú vazio");
  }

  // Determina o estado do baú baseado na distância
  EstadoBaú novoEstado;
  if (distanciaAtual < distanciaCheio) {
    novoEstado = CHEIO;
  } else if (distanciaAtual < distanciaParcial) {
    novoEstado = PARCIAL;
  } else {
    novoEstado = VAZIO;
  }

  // Atualiza o display apenas se o estado mudou
  if (novoEstado != estadoAtual) {
    estadoAtual = novoEstado;
    atualizarDisplay();
  }

  // Atualiza a distância no display a cada ciclo
  atualizarDistancia();

  // Imprime informações no monitor serial
  Serial.print("Distância: ");
  Serial.print(distanciaAtual);
  Serial.print(" mm - Estado: ");
  
  switch (estadoAtual) {
    case CHEIO:
      Serial.println("BAÚ CHEIO");
      break;
    case PARCIAL:
      Serial.println("BAÚ PARCIAL");
      break;
    case VAZIO:
      Serial.println("BAÚ VAZIO");
      break;
  }

  delay(500); // Atualiza a cada 500ms
}

void atualizarDisplay() {
  Serial.print("Atualizando display - Estado: ");
  
  // Limpa a tela e define a cor de fundo baseada no estado
  switch (estadoAtual) {
    case CHEIO:
      Serial.println("CHEIO");
      tft.fillScreen(COLOR_BACKGROUND_RED);
      tft.setTextColor(COLOR_TEXT_WHITE, COLOR_BACKGROUND_RED);
      tft.setTextSize(2);
      tft.setCursor(10, 10);
      tft.print("BAU CHEIO");
      tft.setTextSize(1);
      tft.setCursor(10, 30);
      tft.print("DISTANCIA:");
      break;
      
    case PARCIAL:
      Serial.println("PARCIAL");
      tft.fillScreen(COLOR_BACKGROUND_YELLOW);
      tft.setTextColor(COLOR_TEXT_BLACK, COLOR_BACKGROUND_YELLOW);
      tft.setTextSize(2);
      tft.setCursor(10, 10);
      tft.print("BAU PARCIAL");
      tft.setTextSize(1);
      tft.setCursor(10, 30);
      tft.print("DISTANCIA:");
      break;
      
    case VAZIO:
      Serial.println("VAZIO");
      tft.fillScreen(COLOR_BACKGROUND_GREEN);
      tft.setTextColor(COLOR_TEXT_BLACK, COLOR_BACKGROUND_GREEN);
      tft.setTextSize(2);
      tft.setCursor(10, 10);
      tft.print("BAU VAZIO");
      tft.setTextSize(1);
      tft.setCursor(10, 30);
      tft.print("DISTANCIA:");
      break;
  }
}

void atualizarDistancia() {
  // Determina cores baseadas no estado atual
  uint16_t corFundo, corTexto;
  
  switch (estadoAtual) {
    case CHEIO:
      corFundo = COLOR_BACKGROUND_RED;
      corTexto = COLOR_TEXT_WHITE;  // Branco no vermelho
      break;
    case PARCIAL:
      corFundo = COLOR_BACKGROUND_YELLOW;
      corTexto = COLOR_TEXT_BLACK;  // Preto no amarelo
      break;
    case VAZIO:
      corFundo = COLOR_BACKGROUND_GREEN;
      corTexto = COLOR_TEXT_BLACK;  // Preto no verde
      break;
  }
  
  // Atualiza apenas a distância na tela - usando setCursor como no projeto de referência
  tft.setTextColor(corTexto, corFundo);
  tft.setTextSize(2);
  
  // Limpa área da distância com a cor CORRETA do estado atual
  tft.fillRect(10, 40, 115, 20, corFundo);
  
  // Desenha a nova distância
  String distanciaStr = String(distanciaAtual) + " mm";
  tft.setCursor(10, 40);
  tft.print(distanciaStr);
  
  // Debug no serial
  Serial.print("Estado: ");
  Serial.print(estadoAtual);
  Serial.print(" - Distancia: ");
  Serial.println(distanciaStr);
}
