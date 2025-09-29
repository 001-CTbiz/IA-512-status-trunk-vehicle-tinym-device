# Diagrama do Circuito - Tinkercad Style

## 🔌 Esquema de Conexões

```
                    ┌─────────────────────────┐
                    │                         │
                    │    LILYGO T-PICOC3      │
                    │    PI RP2040 LCD        │
                    │                         │
                    │  ┌─────────────────┐    │
                    │  │   TFT DISPLAY   │    │
                    │  │   240x135px     │    │
                    │  └─────────────────┘    │
                    │                         │
                    │  VBUS  GND  3.3V  GND   │
                    │                         │
                    │  GP0   GP1   GP2   GP3  │
                    │  GP4   GP5   GP6   GP7  │
                    │  GP8   GP9   GP10  GP11 │
                    │  GP12  GP13  GP14  GP15 │ ← I2C
                    │  GP16  GP17  GP18  GP19 │
                    │  GP20  GP21  GP22  GP23 │
                    │                         │
                    └─────────────────────────┘
                              │ │ │ │
                              │ │ │ └─── SCL (GP13)
                              │ │ └───── SDA (GP12)
                              │ └─────── GND
                              └───────── 3.3V
                                    │
                    ┌─────────────────────────┐
                    │                         │
                    │      VL53L0X SENSOR     │
                    │                         │
                    │  ┌─────────────────┐    │
                    │  │   LASER TOF     │    │
                    │  │   0-2000mm      │    │
                    │  └─────────────────┘    │
                    │                         │
                    │  VCC  GND  SDA  SCL     │
                    │   │    │    │    │      │
                    │   │    │    │    │      │
                    └───┼────┼────┼────┼──────┘
                        │    │    │    │
                        │    │    │    └─── GP13 (SCL)
                        │    │    └──────── GP12 (SDA)
                        │    └───────────── GND
                        └────────────────── 3.3V
```

## 📋 Lista de Componentes

| Componente | Quantidade | Especificação |
|------------|------------|---------------|
| **Lilygo T-PicoC3** | 1 | Pi RP2040 LCD integrado |
| **VL53L0X** | 1 | Sensor ToF I2C |
| **Jumpers** | 4 | Cabos de conexão |
| **Breadboard** | 1 | Protoboard (opcional) |
| **Fonte USB** | 1 | 5V/2A (para alimentação) |

## 🔗 Conexões Detalhadas

### **Alimentação:**
- **VCC VL53L0X** → **3.3V Lilygo**
- **GND VL53L0X** → **GND Lilygo**

### **Comunicação I2C:**
- **SDA VL53L0X** → **GP12 Lilygo**
- **SCL VL53L0X** → **GP13 Lilygo**

### **Display (Integrado):**
- **TFT LCD** → **Conectado internamente**
- **Backlight** → **GP4 (controle)**

## ⚡ Especificações Técnicas

### **Alimentação:**
- **Voltagem**: 3.3V
- **Corrente Total**: ~100mA
- **Corrente Sensor**: 20mA

### **Comunicação:**
- **Protocolo**: I2C
- **Velocidade**: 100kHz
- **Endereço**: 0x29

### **Sensor:**
- **Alcance**: 0-2000mm
- **Precisão**: ±3%
- **Resolução**: 1mm
- **Taxa**: 10Hz

## 🎯 Estados do Sistema

### **CHEIO (0-400mm):**
- **Cor**: Vermelho
- **Confiança**: 70-100%
- **Display**: "BAU CHEIO"

### **PARCIAL (400-1200mm):**
- **Cor**: Amarelo
- **Confiança**: 50-90%
- **Display**: "BAU PARCIAL"

### **VAZIO (1200mm+):**
- **Cor**: Verde
- **Confiança**: 80-100%
- **Display**: "BAU VAZIO"

## 🔧 Configuração no Tinkercad

### **1. Adicionar Componentes:**
```
- Raspberry Pi Pico (substituto)
- VL53L0X Sensor
- Breadboard
- Jumpers
```

### **2. Fazer Conexões:**
```
Pico 3.3V → VL53L0X VCC
Pico GND  → VL53L0X GND
Pico GP0  → VL53L0X SDA
Pico GP1  → VL53L0X SCL
```

### **3. Programar:**
```python
# Código MicroPython para Pico
from machine import Pin, I2C
import time

i2c = I2C(0, sda=Pin(0), scl=Pin(1))
# ... resto do código
```

## 📊 Simulação Esperada

### **Comportamento:**
- ✅ **Medição contínua** de distância
- ✅ **Classificação automática** do estado
- ✅ **Display visual** com cores
- ✅ **Debug serial** com probabilidades

### **Limitações:**
- ❌ **TinyML** não simulável
- ❌ **Display TFT** limitado
- ❌ **Cores dinâmicas** básicas

---

**Este diagrama pode ser usado como referência para montar o circuito no Tinkercad ou em protoboard real.**
