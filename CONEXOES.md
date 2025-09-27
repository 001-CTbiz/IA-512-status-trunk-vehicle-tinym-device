# Diagrama de Conexões - Sensor VL53L0X

## Placa: Lilygo T-PicoC3 Pi RP2040 LCD

### Conexões do Sensor VL53L0X:

```
┌─────────────────────────────────────┐
│        LILYGO T-PICOC3 PI RP2040    │
│                                     │
│  ┌─────────────────────────────────┐ │
│  │           LCD TFT               │ │
│  │        240x135 pixels           │ │
│  └─────────────────────────────────┘ │
│                                     │
│  GPIO 6  ────── SDA (VL53L0X)      │
│  GPIO 7  ────── SCL (VL53L0X)      │
│  3.3V    ────── VCC (VL53L0X)      │
│  GND     ────── GND (VL53L0X)      │
│                                     │
└─────────────────────────────────────┘
```

### Pinout da Placa Lilygo T-PicoC3:

```
    ┌─────────────────────────────┐
    │                             │
    │  VBUS  GND  GP0   GP1   GP2 │
    │                             │
    │  GP3   GP4   GP5   GP6   GP7│ ← I2C aqui
    │                             │
    │  GP8   GP9   GP10  GP11  GP12│
    │                             │
    │  GP13  GP14  GP15  GP16  GP17│
    │                             │
    │  GP18  GP19  GP20  GP21  GP22│
    │                             │
    └─────────────────────────────┘
```

### Conexões Detalhadas:

| Sensor VL53L0X | Placa Lilygo T-PicoC3 | Função |
|----------------|----------------------|--------|
| VCC            | 3.3V                 | Alimentação |
| GND            | GND                  | Terra |
| SDA            | GPIO 12              | Dados I2C (I2C0_SDA) |
| SCL            | GPIO 13              | Clock I2C (I2C0_SCL) |

### Diagrama de Montagem:

```
                    ┌─────────────┐
                    │   VL53L0X   │
                    │   Sensor    │
                    │             │
                    │ VCC  GND    │
                    │ SDA  SCL    │
                    └─────────────┘
                         │ │ │ │
                         │ │ │ └─── GPIO 13 (SCL)
                         │ │ └───── GPIO 12 (SDA)  
                         │ └─────── GND
                         └───────── 3.3V
```

### Instruções de Conexão:

1. **VCC (Vermelho)**: Conecte ao pino 3.3V da placa
2. **GND (Preto)**: Conecte ao pino GND da placa
3. **SDA (Azul)**: Conecte ao GPIO 12 da placa
4. **SCL (Verde)**: Conecte ao GPIO 13 da placa

### Verificação das Conexões:

- ✅ VCC → 3.3V (alimentação)
- ✅ GND → GND (terra comum)
- ✅ SDA → GPIO 12 (dados I2C)
- ✅ SCL → GPIO 13 (clock I2C)

### Notas Importantes:

- Use cabos de no máximo 20cm para evitar interferência
- Verifique a polaridade antes de conectar
- O sensor VL53L0X funciona com 3.3V (não use 5V)
- Mantenha os cabos organizados para facilitar manutenção
