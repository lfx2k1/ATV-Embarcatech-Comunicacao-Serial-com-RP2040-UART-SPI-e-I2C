#include <stdio.h>
#include <stdlib.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/i2c.h"
#include "inc/ssd1306.h"
#include "inc/font.h"
#include <string.h>
#include "hardware/watchdog.h"
#include "hardware/structs/psm.h"
#include "pico/bootrom.h"
#include "hardware/pio.h"
#include "hardware/clocks.h"
#include "hardware/timer.h"
#include "ws2812.pio.h"
#include "ws2812_library.h"
#include "botao_led_library.h"

#define I2C_PORT i2c1
#define I2C_SDA 14
#define I2C_SCL 15
#define endereco 0x3C

// Variáveis globais
ssd1306_t ssd; // Display SSD1306

int main() {
    stdio_init_all();
    
    // Configura os LEDs e botões
    configurar_leds();
    configurar_botoes();
    
    // I2C e SSD1306
    i2c_init(I2C_PORT, 400 * 1000);
    gpio_set_function(I2C_SDA, GPIO_FUNC_I2C); 
    gpio_set_function(I2C_SCL, GPIO_FUNC_I2C); 
    gpio_pull_up(I2C_SDA); 
    gpio_pull_up(I2C_SCL); 
    ssd1306_init(&ssd, WIDTH, HEIGHT, false, endereco, I2C_PORT); 
    ssd1306_config(&ssd); 
    ssd1306_send_data(&ssd);
    ssd1306_fill(&ssd, false);
    ssd1306_send_data(&ssd);
    
    // Configura a matriz de LEDs
    configurar_matriz_leds();
    
    bool cor = true;
    char command[100]; // Buffer para o comando recebido

    while (true) {

        scanf("%s",command); //captura caractere de digitação
        fflush(stdin); //remover lixo de digitação
        
        cor = !cor;
      // Atualiza o conteúdo do display com animações
       ssd1306_fill(&ssd, !cor); // Limpa o display
       ssd1306_rect(&ssd, 3, 3, 122, 58, cor, !cor); // Desenha um retângulo
       ssd1306_draw_string(&ssd, command, 8, 10); // Desenha uma string      
       ssd1306_send_data(&ssd); // Atualiza o display 
       execute_command(command); // Exibe o comando na matriz de LEDs

        sleep_ms(1000);
    }
}
