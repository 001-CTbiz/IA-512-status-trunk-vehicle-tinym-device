# Instruções para Importar no Tinkercad

## 📋 Como Usar este Arquivo no Tinkercad

### 1. **Preparação**
- Acesse [tinkercad.com](https://www.tinkercad.com)
- Faça login na sua conta
- Clique em "Circuits" → "Create new circuit"

### 2. **Componentes Necessários**
Procure e adicione os seguintes componentes:

#### **Microcontrolador:**
- `Raspberry Pi Pico` (como substituto da Lilygo T-PicoC3)
- Ou `Arduino Uno` (para simulação básica)

#### **Sensor:**
- `VL53L0X` (se disponível)
- Ou `Ultrasonic Sensor HC-SR04` (como substituto)

#### **Display:**
- `LCD 16x2` (para simulação)
- Ou `OLED Display` (se disponível)

#### **Outros:**
- `Breadboard`
- `Jumpers** (fios de conexão)
- `Resistor 10kΩ` (pull-up I2C)

### 3. **Conexões no Tinkercad**

#### **Para Raspberry Pi Pico:**
```
VL53L0X VCC  → Pico 3.3V
VL53L0X GND  → Pico GND  
VL53L0X SDA  → Pico GP0 (SDA)
VL53L0X SCL  → Pico GP1 (SCL)
```

#### **Para Arduino Uno:**
```
VL53L0X VCC  → Arduino 5V
VL53L0X GND  → Arduino GND
VL53L0X SDA  → Arduino A4 (SDA)
VL53L0X SCL  → Arduino A5 (SCL)
```

### 4. **Código de Exemplo para Tinkercad**

#### **Para Raspberry Pi Pico (MicroPython):**
```python
from machine import Pin, I2C
import time

# Configuração I2C
i2c = I2C(0, sda=Pin(0), scl=Pin(1), freq=100000)

# Endereço do VL53L0X
VL53L0X_ADDR = 0x29

def read_distance():
    # Comando para iniciar medição
    i2c.writeto(VL53L0X_ADDR, b'\x00\x01')
    time.sleep(0.1)
    
    # Ler resultado
    data = i2c.readfrom(VL53L0X_ADDR, 2)
    distance = (data[0] << 8) | data[1]
    return distance

while True:
    dist = read_distance()
    print(f"Distância: {dist}mm")
    time.sleep(1)
```

#### **Para Arduino Uno (C++):**
```cpp
#include <Wire.h>
#include <VL53L0X.h>

VL53L0X sensor;

void setup() {
  Serial.begin(115200);
  Wire.begin();
  
  sensor.init();
  sensor.setTimeout(500);
  sensor.startContinuous();
}

void loop() {
  uint16_t distance = sensor.readRangeContinuousMillimeters();
  
  if (sensor.timeoutOccurred()) {
    Serial.println("Timeout!");
  } else {
    Serial.print("Distância: ");
    Serial.print(distance);
    Serial.println("mm");
  }
  
  delay(100);
}
```

### 5. **Simulação no Tinkercad**

#### **Funcionalidades Disponíveis:**
- ✅ **Medição de distância** em tempo real
- ✅ **Display de valores** no monitor serial
- ✅ **Indicadores visuais** (LEDs para estados)
- ✅ **Gráficos** de distância vs tempo

#### **Limitações:**
- ❌ **Display TFT integrado** não disponível
- ❌ **TinyML** não pode ser simulado
- ❌ **Cores dinâmicas** limitadas

### 6. **Componentes Alternativos**

#### **Se VL53L0X não estiver disponível:**
- Use `Ultrasonic Sensor HC-SR04`
- Use `Infrared Distance Sensor`
- Use `Laser Distance Sensor`

#### **Se Raspberry Pi Pico não estiver disponível:**
- Use `Arduino Uno`
- Use `ESP32`
- Use `Arduino Nano`

### 7. **Teste e Validação**

#### **Verificações:**
1. **Conexões I2C** estão corretas
2. **Alimentação** está estável
3. **Código** compila sem erros
4. **Sensor** responde às medições
5. **Serial** mostra dados corretos

#### **Problemas Comuns:**
- **Sensor não detectado**: Verificar endereço I2C
- **Valores incorretos**: Verificar alimentação
- **Conexão instável**: Usar cabos mais curtos

### 8. **Exportação**

#### **Para Prototipagem:**
- Exporte como **Gerber files** para PCB
- Gere **Lista de materiais (BOM)**
- Crie **Diagrama de montagem**

#### **Para Documentação:**
- Salve **Screenshot** do circuito
- Exporte **Código** para IDE
- Gere **Relatório** de simulação

---

## 🎯 **Objetivo da Simulação**

Este circuito no Tinkercad permite:
- ✅ **Validar conexões** antes da montagem real
- ✅ **Testar código** sem hardware físico
- ✅ **Educar** sobre o funcionamento do sistema
- ✅ **Prototipar** melhorias no circuito

**Nota**: Para funcionalidade completa com TinyML e display TFT, use o hardware real (Lilygo T-PicoC3).
