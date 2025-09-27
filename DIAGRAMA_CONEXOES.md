# 🔌 DIAGRAMA DE CONEXÕES - Sensor VL53L0X CJVL53L0XV2

## 📋 Especificações do Sensor

- **Modelo**: CJVL53L0XV2
- **Tipo**: VL53L0X TOF (Time-of-Flight)
- **Comunicação**: I2C
- **Alimentação**: 3.3V
- **Pinos**: 6 pinos (VCC, GND, SCL, SDA, GPIO1, XSHUT)

## 🔗 Conexões com Lilygo T-PicoC3 Pi RP2040 LCD

### **Tabela de Conexões:**

| **Sensor VL53L0X** | **Placa Lilygo T-PicoC3** | **Cor Sugerida** | **Função** |
|-------------------|----------------------------|------------------|------------|
| **VCC**           | **3.3V**                  | 🔴 Vermelho      | Alimentação |
| **GND**           | **GND**                   | ⚫ Preto         | Terra |
| **SCL**           | **GPIO 13**               | 🟢 Verde         | Clock I2C |
| **SDA**           | **GPIO 12**               | 🔵 Azul          | Dados I2C |
| **GPIO1**         | **Não conectado**         | -                | Opcional |
| **XSHUT**         | **Não conectado**         | -                | Opcional |

## 🎯 Diagrama Visual de Conexão

```
    ┌─────────────────────────────────────┐
    │        LILYGO T-PICOC3 PI RP2040    │
    │                                     │
    │  ┌─────────────────────────────────┐ │
    │  │           LCD TFT               │ │
    │  │        240x135 pixels           │ │
    │  └─────────────────────────────────┘ │
    │                                     │
    │  ┌─────────────────────────────────┐ │
    │  │        PINOS GPIO               │ │
    │  │                                 │ │
    │  │  3V3  GND  GP12  GP13  GP14     │ │
    │  │                                 │ │
    │  │  GP15  GP16  GP17  GP18  GP19   │ │
    │  └─────────────────────────────────┘ │
    └─────────────────────────────────────┘
                     │ │ │ │
                     │ │ │ └─── GPIO 13 (SCL) 🟢
                     │ │ └───── GPIO 12 (SDA) 🔵
                     │ └─────── GND ⚫
                     └───────── 3.3V 🔴
                     
    ┌─────────────────────────────────────┐
    │         VL53L0X CJVL53L0XV2         │
    │                                     │
    │  ┌─────────────────────────────────┐ │
    │  │        SENSOR VL53L0X           │ │
    │  │                                 │ │
    │  │  VCC  GND  SCL  SDA  GPIO1      │ │
    │  │                                 │ │
    │  │  XSHUT                          │ │
    │  └─────────────────────────────────┘ │
    └─────────────────────────────────────┘
```

## 📍 Localização dos Pinos na Placa

### **Lado Direito da Placa (Pinos Principais):**
- **3.3V**: Primeiro pino (alimentação)
- **GND**: Segundo pino (terra)
- **GPIO 12**: Terceiro pino (I2C0_SDA)
- **GPIO 13**: Quarto pino (I2C0_SCL)

## 🔧 Instruções de Montagem

### **Passo 1: Preparação**
- Use cabos jumper de 20cm ou menos
- Verifique a polaridade antes de conectar
- Organize os cabos por cor para facilitar identificação

### **Passo 2: Conexões Essenciais**
1. **🔴 VCC → 3.3V**: Alimentação do sensor
2. **⚫ GND → GND**: Terra comum
3. **🔵 SDA → GPIO 12**: Dados I2C
4. **🟢 SCL → GPIO 13**: Clock I2C

### **Passo 3: Conexões Opcionais**
- **GPIO1**: Pode ser usado para interrupção (não necessário para funcionamento básico)
- **XSHUT**: Pode ser usado para reset do sensor (não necessário)

## ⚠️ Cuidados Importantes

### **Alimentação:**
- ✅ Use **3.3V** (não 5V)
- ✅ Verifique polaridade antes de conectar
- ✅ Conecte GND primeiro, depois VCC

### **Comunicação I2C:**
- ✅ Use pinos dedicados I2C (GP12/GP13)
- ✅ Mantenha cabos curtos (< 20cm)
- ✅ Evite interferência eletromagnética

### **Montagem:**
- ✅ Fixe o sensor com parafusos nos orifícios
- ✅ Mantenha distância adequada do LCD
- ✅ Organize os cabos para facilitar manutenção

## 🧪 Teste das Conexões

### **Verificação Visual:**
- ✅ VCC (vermelho) → 3.3V
- ✅ GND (preto) → GND
- ✅ SDA (azul) → GPIO 12
- ✅ SCL (verde) → GPIO 13

### **Teste com Multímetro:**
- ✅ 3.3V entre VCC e GND
- ✅ Continuidade nos cabos I2C
- ✅ Sem curto-circuito entre pinos

## 📊 Especificações Técnicas

### **Sensor VL53L0X:**
- **Alcance**: 2mm a 2m
- **Precisão**: ±3%
- **Resolução**: 1mm
- **Frequência**: Até 50Hz
- **Consumo**: 8mA ativo, 1μA standby

### **Comunicação I2C:**
- **Endereço**: 0x29 (padrão)
- **Velocidade**: 100kHz (padrão) ou 400kHz
- **Protocolo**: I2C padrão

## 🚀 Próximos Passos

1. **Conectar** o sensor conforme diagrama
2. **Verificar** todas as conexões
3. **Fazer upload** do firmware
4. **Monitorar** serial para debug
5. **Testar** funcionamento do sensor

---

**📝 Nota**: Este diagrama é específico para o módulo CJVL53L0XV2 com a placa Lilygo T-PicoC3 Pi RP2040 LCD.
