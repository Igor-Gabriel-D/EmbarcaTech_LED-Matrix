#ifndef __NEOPIXEL_INC
#define __NEOPIXEL_INC

#include <stdlib.h>
#include "ws2818b.pio.h"

// Definição de pixel GRB
struct pixel_t {
  uint8_t G, R, B; // Três valores de 8-bits compõem um pixel.
};
typedef struct pixel_t pixel_t;
typedef pixel_t npLED_t; // Mudança de nome de "struct pixel_t" para "npLED_t" por clareza.


// Declaração do buffer de pixels que formam a matriz.
static npLED_t *leds;
static uint led_count;

// Variáveis para uso da máquina PIO.
static PIO np_pio;
static uint np_sm;

/**
 * Inicializa a máquina PIO para controle da matriz de LEDs.
 */
void npInit(uint pin, uint amount) {

  led_count = amount;
  leds = (npLED_t *)calloc(led_count, sizeof(npLED_t));

  // Cria programa PIO.
  uint offset = pio_add_program(pio0, &ws2818b_program);
  np_pio = pio0;

  // Toma posse de uma máquina PIO.
  np_sm = pio_claim_unused_sm(np_pio, false);
  if (np_sm < 0) {
    np_pio = pio1;
    np_sm = pio_claim_unused_sm(np_pio, true); // Se nenhuma máquina estiver livre, panic!
  }

  // Inicia programa na máquina PIO obtida.
  ws2818b_program_init(np_pio, np_sm, offset, pin, 800000.f);

  // Limpa buffer de pixels.
  for (uint i = 0; i < led_count; ++i) {
    leds[i].R = 0;
    leds[i].G = 0;
    leds[i].B = 0;
  }
}

/**
 * Atribui uma cor RGB a um LED.
 */
void npSetLED(const uint index, const uint8_t r, const uint8_t g, const uint8_t b) {
  leds[index].R = r;
  leds[index].G = g;
  leds[index].B = b;
}

/**
 * Limpa o buffer de pixels.
 */
void npClear() {
  for (uint i = 0; i < led_count; ++i)
    npSetLED(i, 0, 0, 0);
}

/**
 * Escreve os dados do buffer nos LEDs.
 */
void npWrite() {
  // Escreve cada dado de 8-bits dos pixels em sequência no buffer da máquina PIO.
  for (uint i = 0; i < led_count; ++i) {
    pio_sm_put_blocking(np_pio, np_sm, leds[i].G);
    pio_sm_put_blocking(np_pio, np_sm, leds[i].R);
    pio_sm_put_blocking(np_pio, np_sm, leds[i].B);
  }
  sleep_us(100); // Espera 100us, sinal de RESET do datasheet.
}


/* 
NOVAS FUNÇÔES
*/
// Defina as dimensões da matriz física de LEDs
/**/
#define ROWS 5
#define COLS 5

uint cords_to_idx(uint x, uint y){
  uint i = (ROWS * y ) + x;

  return i;
}

uint idx_to_zigzag(int i){
  uint row = (i/5) + 1;

  uint j = i;

  if(row % 2 == 1 ){

    j = ((i/5) * 5) + (4 - (i % 5));
  } 

  return j;
}

void npSetLED_coord(int x, int y, uint R, uint G, uint B){
  uint logical_position = cords_to_idx(x, y);
  uint physical_position = idx_to_zigzag(logical_position);

  leds[physical_position ].R = R;
  leds[physical_position ].G = G;
  leds[physical_position ].B = B;

}
void draw_line(int x1, int y1, int x2, int y2, uint r, uint g, uint b) {
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    int sx = (x1 < x2) ? 1 : -1;
    int sy = (y1 < y2) ? 1 : -1;
    int err = dx - dy;

    while (1) {
        // Define a cor do LED na posição atual
        if (x1 >= 0 && x1 < COLS && y1 >= 0 && y1 < ROWS) { 
            // Garante que as coordenadas estão dentro da matriz
            npSetLED_coord(x1, y1, r, g, b);
        }

        // Verifica se o ponto final foi alcançado
        if (x1 == x2 && y1 == y2) break;

        // Ajusta os valores de x e y usando o algoritmo de Bresenham
        int e2 = 2 * err;
        if (e2 > -dy) {
            err -= dy;
            x1 += sx;
        }
        if (e2 < dx) {
            err += dx;
            y1 += sy;
        }
    }


}

void draw_square(int x1, int y1, int x2, int y2, uint r, uint g, uint b){
  if (x1 > x2) {
    int temp = x1;
    x1 = x2;
    x2 = temp;
  }
  if (y1 > y2) {
    int temp = y1;
    y1 = y2;
    y2 = temp;
  }

  for(int i = y1; i <= y2; i++){
    for(int j = x1; j <= x2; j++){
      npSetLED_coord(j, i, r, g, b);
    }
  }
}
#endif