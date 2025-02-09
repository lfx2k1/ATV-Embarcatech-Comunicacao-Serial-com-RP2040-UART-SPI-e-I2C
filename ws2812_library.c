#include "ws2812_library.h"

// Variáveis globais
int numero_atual = 0;
uint32_t buffer_leds[NUM_LEDS] = {0};

// Função para enviar um pixel para a matriz de LEDs
static inline void enviar_pixel(uint32_t pixel_grb) {
    pio_sm_put_blocking(pio0, 0, pixel_grb << 8u);
    sleep_us(50); // Pequeno delay para estabilidade
}

// Função para converter RGB para GRB
static inline uint32_t converter_rgb_para_grb(uint8_t r, uint8_t g, uint8_t b) {
    return ((uint32_t)(r) << 8) | ((uint32_t)(g) << 16) | (uint32_t)(b);
}

// Configura a matriz WS2812
void configurar_matriz_leds() {
    PIO pio = pio0;
    int sm = 0;
    uint offset = pio_add_program(pio, &ws2812_program);
    ws2812_program_init(pio, sm, offset, WS2812_PIN, 800000, IS_RGBW);
    sleep_ms(100); // Pequeno atraso para garantir a inicialização
}

// Limpa o buffer de LEDs
void limpar_buffer_leds() {
    for (int i = 0; i < NUM_LEDS; i++) {
        buffer_leds[i] = 0;
    }
}

// Atualiza a matriz LED
void atualizar_matriz(int numero) {
    static const uint32_t padroes_numeros[10][NUM_LEDS] = {
        // Padrões de números (conforme o seu código original)
        //0
        {1,1,1,1,1, 
         1,0,0,0,1, 
         1,0,0,0,1, 
         1,0,0,0,1, 
         1,1,1,1,1},

        //1
        {0,1,1,1,0, 
         0,0,1,0,0,  
         0,0,1,0,0,  
         0,1,1,0,0,  
         0,0,1,0,0},

        //2
        {1,1,1,1,1,
         1,0,0,0,0, 
         1,1,1,1,1, 
         0,0,0,0,1, 
         1,1,1,1,1},

        //3
        {1,1,1,1,1, 
         0,0,0,0,1, 
         1,1,1,1,1, 
         0,0,0,0,1, 
         1,1,1,1,1},

        //4
        {1,0,0,0,0, 
         0,0,0,0,1, 
         1,1,1,1,1, 
         1,0,0,0,1, 
         1,0,0,0,1},

        //5
        {1,1,1,1,1, 
         0,0,0,0,1,
         1,1,1,1,1, 
         1,0,0,0,0, 
         1,1,1,1,1},
        
        //6
        {1,1,1,1,1, 
         1,0,0,0,1, 
         1,1,1,1,1, 
         1,0,0,0,0, 
         1,1,1,1,1},   
        
        //7
        {0,0,0,1,0, 
         0,0,1,0,0, 
         0,1,0,0,0, 
         0,0,0,0,1, 
         1,1,1,1,1},

        //8
        {1,1,1,1,1, 
         1,0,0,0,1, 
         1,1,1,1,1, 
         1,0,0,0,1, 
         1,1,1,1,1},
         
         //9
        {1,1,1,1,1, 
         0,0,0,0,1, 
         1,1,1,1,1, 
         1,0,0,0,1, 
         1,1,1,1,1}
    };

    limpar_buffer_leds(); // Limpa o buffer de LEDs

    for (int i = 0; i < NUM_LEDS; i++) {
        buffer_leds[i] = padroes_numeros[numero][i] ? converter_rgb_para_grb(255, 0, 0) : 0;
    }
    
    for (int i = 0; i < NUM_LEDS; i++) {
        enviar_pixel(buffer_leds[i]);
    }
}

void execute_command(const char *command) {
    if (command[0] >= '0' && command[0] <= '9' && command[1] == '\0') {
        int numero = command[0] - '0';
        atualizar_matriz(numero);
        printf("Número %d exibido na matriz de LEDs.\n", numero);
    } else {
        printf("Comando inválido para matriz de LEDs: %s\n", command);
    }
}