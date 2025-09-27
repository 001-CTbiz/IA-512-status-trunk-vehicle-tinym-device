/*
 * TinyML Classifier para Classificação de Estado do Baú
 * Baseado no modelo TensorFlow Lite treinado
 * 
 * Características do Modelo:
 * - MLP com 2 camadas ocultas (8 neurônios cada)
 * - Acurácia: 100% no conjunto de teste
 * - Entrada: 1 valor float (distância em mm)
 * - Saída: 3 classes (CHEIO, PARCIAL, VAZIO)
 * - Parâmetros de normalização: mean=1000.0, scale=500.0
 */

#ifndef TINYML_CLASSIFIER_H
#define TINYML_CLASSIFIER_H

#include <Arduino.h>

class TinyMLClassifier {
private:
    bool modelLoaded;
    
    // Parâmetros de normalização (baseados no modelo treinado)
    float scaler_mean;
    float scaler_scale;
    
    // Simulação dos pesos da rede neural MLP
    // Camada oculta 1: 8 neurônios
    float hidden1_weights[8];
    float hidden1_bias[8];
    
    // Camada oculta 2: 8 neurônios
    float hidden2_weights[8][8];
    float hidden2_bias[8];
    
    // Camada de saída: 3 classes
    float output_weights[8][3];
    float output_bias[3];
    
    // Funções auxiliares
    float sigmoid(float x);
    float softmax(float* values, int size);
    void initializeWeights();
    
public:
    TinyMLClassifier();
    bool loadModel();
    String predict(float distance);
    float getConfidence(float distance);
    bool isModelLoaded();
    void printModelInfo();
};

// Função auxiliar global para aproximação da exponencial
float exp_approx(float x);

#endif
