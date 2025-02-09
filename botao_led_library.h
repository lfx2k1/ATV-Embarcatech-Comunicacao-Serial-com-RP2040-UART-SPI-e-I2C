// Protetor de inclusão para evitar múltiplas inclusões do mesmo arquivo
#ifndef BOTAO_LED_LIBRARY_H
#define BOTAO_LED_LIBRARY_H

// Inclusão de bibliotecas padrão
#include <stdio.h>
#include <stdlib.h>
#include "pico/stdlib.h"

// Definição dos pinos para botões e LEDs
#define BOTAO_A_PIN 5
#define BOTAO_B_PIN 6
#define LED_VERDE_PIN 11
#define LED_AZUL_PIN 12
#define DEBOUNCE_MS 250 // Tempo de debounce em milissegundos

// Declaração de variáveis globais voláteis
extern volatile bool led_verde_state; // Estado do LED verde
extern volatile bool led_azul_state; // Estado do LED azul
extern volatile bool atualizar_display; // Flag para atualizar o display
extern volatile uint32_t ultimo_tempo_botao_a; // Tempo do último pressionamento do botão A
extern volatile uint32_t ultimo_tempo_botao_b; // Tempo do último pressionamento do botão B

// Declaração de funções
void configurar_botoes(); // Função para configurar botões
void configurar_leds(); // Função para configurar LEDs
void tratar_botao(uint gpio, uint32_t events); // Função para tratar eventos de botões
void alternar_led(int led_pin, volatile bool *led_state); // Função para alternar estado dos LEDs

#endif // Fim do protetor de inclusão