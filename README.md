# ATV-Embarcatech-Comunicacao-Serial-com-RP2040-UART-SPI-e-I2C
Repositório para desenvolvimento de atividade do Embarcatech.
##Vídeos com a explicação do código e funcionalidade, vale ressaltar que o vídeo 2 é um vídeo curto mostrando de maneira mais clara o funcionamento na placa BitDogLab.

###Vídeo 1: https://drive.google.com/file/d/1OQBJPoa8yrjp9MDkfD-Rld2I-pYMmVKh/view?usp=sharing

###Vídeo 2: https://drive.google.com/file/d/1zm0ALs-IWnYsZUYB4GMIUuLtUqu4uql5/view?usp=sharing

## Enunciado
Este projeto visa consolidar os conceitos sobre o uso de interfaces de comunicação serial no RP2040 e explorar as funcionalidades da placa de desenvolvimento BitDogLab. A seguir estão os objetivos e a descrição das funcionalidades do projeto:

### Objetivos

- Compreender o funcionamento e a aplicação de comunicação serial em microcontroladores.
- Aplicar conhecimentos sobre UART e I2C na prática.
- Manipular e controlar LEDs comuns e LEDs endereçáveis WS2812.
- Estudar o uso de botões de acionamento, interrupções e debounce.
- Desenvolver um projeto funcional que combine hardware e software.

### Descrição do Projeto

Utilize os seguintes componentes conectados à placa BitDogLab:

- Matriz 5x5 de LEDs (endereçáveis) WS2812, conectada à GPIO 7.
- LED RGB, com os pinos conectados às GPIOs (11, 12 e 13).
- Botão A conectado à GPIO 5.
- Botão B conectado à GPIO 6.
- Display SSD1306 conectado via I2C (GPIO 14 e GPIO15).

### Funcionalidades do Projeto

1. **Modificação da Biblioteca font.h**: Adicionar caracteres minúsculos à biblioteca font.h.
2. **Entrada de caracteres via PC**: Cada caractere digitado no Serial Monitor do VS Code é exibido no display SSD1306. Números entre 0 e 9 são exibidos na matriz 5x5 WS2812.
3. **Interação com o Botão A**: Alterna o estado do LED RGB Verde (ligado/desligado). A operação é registrada no display SSD1306 e no Serial Monitor.
4. **Interação com o Botão B**: Alterna o estado do LED RGB Azul (ligado/desligado). A operação é registrada no display SSD1306 e no Serial Monitor.

## Utilização do programa

## 1. Pré-requisitos
Antes de rodar o programa, certifique-se de ter os seguintes itens configurados:
Placa BitDogLab.
Ambiente de desenvolvimento: SDK do Raspberry Pi Pico configurado (CMake, GCC ARM, etc.).
Cabo USB: Para alimentação e comunicação serial com o Raspberry Pi Pico.

## 2. Compilação e Upload
Clone este repositório:

git clone https://github.com/lfx2k1/ATV-Embarcatech-Comunicacao-Serial-com-RP2040-UART-SPI-e-I2C.git
Selecione a pasta - cd Atividade-2-Temporizador-de-um-disparo-OneShot-UND-4
Compile o código

Após a compilação, um arquivo .uf2 será gerado. Para enviá-lo a placa BitDogLab:
Conecte a placa BitDogLab ao PC segurando o botão BOOTSEL.
Ele será montado como um dispositivo de armazenamento.
Copie o arquivo .uf2 gerado para dentro da placa BitDogLab.

## 3. Execução
Assim que o código for carregado, o sistema ficará aguardando os comandos realizados a partir da interação nos botões A e B para acionar o LED RGB e também a interação no serial monitor, onde é possível inserir caracteres, onde os números de 0 a 9 são exibidos no display e também na matriz de LEDs.
