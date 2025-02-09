#include "botao_led_library.h"
#include "inc/ssd1306.h"

extern ssd1306_t ssd; // Declaração externa do display

// Variáveis globais
volatile bool led_verde_state = false;
volatile bool led_azul_state = false;
volatile bool atualizar_display = false;
volatile uint32_t ultimo_tempo_botao_a = 0;
volatile uint32_t ultimo_tempo_botao_b = 0;

// Função de interrupção para os botões
void tratar_botao(uint gpio, uint32_t events) {
    uint32_t tempo_atual = to_ms_since_boot(get_absolute_time());
    if (gpio == BOTAO_A_PIN && (tempo_atual - ultimo_tempo_botao_a > DEBOUNCE_MS)) {
        ultimo_tempo_botao_a = tempo_atual;
        alternar_led(LED_VERDE_PIN, &led_verde_state);
        atualizar_display = true;
    } else if (gpio == BOTAO_B_PIN && (tempo_atual - ultimo_tempo_botao_b > DEBOUNCE_MS)) {
        ultimo_tempo_botao_b = tempo_atual;
        alternar_led(LED_AZUL_PIN, &led_azul_state);
        atualizar_display = true;
    }
}

// Alterna o estado do LED e atualiza o display
void alternar_led(int led_pin, volatile bool *led_state) {
    *led_state = !*led_state;
    gpio_put(led_pin, *led_state);

     // Limpa o display antes de atualizar com o novo texto
     ssd1306_fill(&ssd, false);


    char mensagem[20];
    // Atualiza a mensagem no Serial Monitor e no display 
    if (led_pin == LED_VERDE_PIN) {
        printf("LED Verde está agora %s\n", *led_state ? "ON" : "OFF");
        snprintf(mensagem, sizeof(mensagem), "LED Verde: %s", *led_state ? "ON" : "OFF");
        ssd1306_draw_string(&ssd, mensagem, 8, 40);
    } else if (led_pin == LED_AZUL_PIN) {
        printf("LED Azul está agora %s\n", *led_state ? "ON" : "OFF");
        snprintf(mensagem, sizeof(mensagem), "LED Azul: %s", *led_state ? "ON" : "OFF");
        ssd1306_draw_string(&ssd, mensagem, 8, 40);
    }

    ssd1306_send_data(&ssd); // Envia os dados para o display
}

// Configura os botões
void configurar_botoes() {
    gpio_init(BOTAO_A_PIN);
    gpio_set_dir(BOTAO_A_PIN, GPIO_IN);
    gpio_pull_up(BOTAO_A_PIN);
    gpio_set_irq_enabled_with_callback(BOTAO_A_PIN, GPIO_IRQ_EDGE_FALL, true, tratar_botao);

    gpio_init(BOTAO_B_PIN);
    gpio_set_dir(BOTAO_B_PIN, GPIO_IN);
    gpio_pull_up(BOTAO_B_PIN);
    gpio_set_irq_enabled_with_callback(BOTAO_B_PIN, GPIO_IRQ_EDGE_FALL, true, tratar_botao);
}

// Configura os LEDs
void configurar_leds() {
    gpio_init(LED_VERDE_PIN);
    gpio_set_dir(LED_VERDE_PIN, GPIO_OUT);

    gpio_init(LED_AZUL_PIN);
    gpio_set_dir(LED_AZUL_PIN, GPIO_OUT);
}