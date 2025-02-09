// Protetor de inclusão para evitar múltiplas inclusões do mesmo arquivo
#ifndef WS2812_LIBRARY_H
#define WS2812_LIBRARY_H

// Inclusão de bibliotecas padrão
#include <stdio.h>
#include <stdlib.h>
#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "hardware/clocks.h"
#include "hardware/timer.h"
#include "ws2812.pio.h"

// Definição de constantes
#define IS_RGBW false // Define se os LEDs são RGBW
#define NUM_LEDS 25 // Número de LEDs na matriz
#define WS2812_PIN 7 // Pino usado para os LEDs WS2812

// Declaração de variáveis globais
extern int numero_atual; // Número atual exibido na matriz de LEDs
extern uint32_t buffer_leds[NUM_LEDS]; // Buffer para os LEDs

// Declaração de funções
void configurar_matriz_leds(); // Função para configurar a matriz de LEDs
void atualizar_matriz(int numero); // Função para atualizar a matriz de LEDs
void execute_command(const char *command); // Função para executar um comando recebido

#endif // Fim do protetor de inclusão