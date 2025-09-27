# Sistema de Monitoramento de Baú - Lilygo T-PicoC3 Pi RP2040 LCD

Este projeto implementa um sistema moderno para monitorar se o baú de um veículo está cheio ou vazio, utilizando:

- **Placa**: Lilygo T-PicoC3 Pi RP2040 LCD
- **Sensor**: VL53L0X TOF I2C (Time-of-Flight)
- **Display**: LCD TFT integrado com cores dinâmicas

## Características

- **Display colorido**: Verde (vazio), Amarelo (parcial), Vermelho (cheio)
- **Fonte grande**: Distância exibida em preto com fonte grande
- **Sensor preciso**: VL53L0X com medição em milímetros
- **Interface moderna**: Tela LCD integrada na placa

## Configuração dos Limites

- **Baú Cheio**: < 200mm (fundo vermelho)
- **Baú Parcial**: 200-400mm (fundo amarelo)  
- **Baú Vazio**: > 400mm (fundo verde)

## Conexões do Sensor VL53L0X

- **VCC**: 3.3V
- **GND**: GND
- **SDA**: GPIO 6
- **SCL**: GPIO 7

## Instalação e Uso

### 1. Instalar PlatformIO

```bash
# Via pip
pip install platformio

# Ou via Homebrew (macOS)
brew install platformio
```

### 2. Compilar e Upload

```bash
# Navegar para o diretório do projeto
cd /Users/ceogrouppra/projects/IA/ultrasonic-sensor-project_lcd

# Compilar o projeto
pio run

# Fazer upload para a placa
pio run --target upload

# Monitorar serial
pio device monitor
```

### 3. Configuração da Porta Serial

Se necessário, ajuste a porta serial no arquivo `platformio.ini`:

```ini
monitor_port = /dev/cu.usbmodem21201  # macOS
upload_port = /dev/cu.usbmodem21201   # macOS
```

## Funcionamento

1. **Inicialização**: Sistema mostra "SISTEMA INICIADO" em verde
2. **Medição contínua**: Sensor VL53L0X mede distância a cada 500ms
3. **Atualização visual**: Display muda cor baseado no estado do baú
4. **Exibição da distância**: Valor atual em milímetros com fonte grande
5. **Monitor serial**: Logs detalhados para debug

## Melhorias em Relação ao Projeto Anterior

- ✅ **Sensor moderno**: VL53L0X TOF I2C (mais preciso que ultrassônico)
- ✅ **Display integrado**: LCD TFT colorido na própria placa
- ✅ **Interface visual**: Cores dinâmicas para fácil identificação
- ✅ **Fonte grande**: Distância bem visível em preto
- ✅ **Placa mais potente**: RP2040 com mais recursos
- ✅ **Código otimizado**: Atualização apenas quando necessário

## Troubleshooting

### Sensor não detectado
- Verifique as conexões I2C (SDA/SCL)
- Confirme alimentação 3.3V do sensor
- Verifique logs no monitor serial

### Display não funciona
- Confirme configurações no `platformio.ini`
- Verifique se a biblioteca TFT_eSPI está instalada
- Teste com exemplo básico da biblioteca

### Upload falha
- Verifique se a placa está conectada
- Confirme a porta serial correta
- Tente resetar a placa antes do upload
