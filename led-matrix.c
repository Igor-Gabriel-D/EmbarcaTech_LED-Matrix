#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/dma.h"
#include "hardware/pio.h"
#include "hardware/clocks.h"

#include "hardware/adc.h"
#include "neopixel.c"

// Pino e número de LEDs da matriz de LEDs.
#define LED_PIN 7
#define LED_COUNT 25

int main() {
  stdio_init_all();
  
  npInit(LED_PIN, LED_COUNT);

  while (true) {

	draw_line(4, 0, 0, 4, 0, 0, 255);
	draw_line(0, 0, 4, 4, 255, 0, 0);
	npWrite();
	sleep_ms(50);
	npClear();

	draw_line(3, 0, 1, 4, 0, 0, 255);
	draw_line(0, 1, 4, 3, 255, 0, 0);
	npWrite();
	sleep_ms(50);
	npClear();


	draw_line(2, 0, 2, 4, 0, 0, 255);
	draw_line(0, 2, 4, 2, 255, 0, 0);
	npWrite();
	sleep_ms(50);
	npClear();
   
   
	draw_line(1, 0, 3, 4, 0, 0, 255);
	draw_line(0, 3, 4, 1, 255, 0, 0);
	npWrite();
	sleep_ms(50);
	npClear();


	draw_line(0, 0, 4, 4, 0, 0, 255);
	draw_line(4, 0, 0, 4, 255, 0, 0);
	npWrite();
	sleep_ms(50);
	npClear();


	draw_line(0, 1, 4, 3, 0, 0, 255);
	draw_line(3, 0, 1, 4, 255, 0, 0);
	npWrite();
	sleep_ms(50);
	npClear();


	draw_line(0, 2, 4, 2, 0, 0, 255);
	draw_line(2, 0, 2, 4, 255, 0, 0);
	npWrite();
	sleep_ms(50);
	npClear();


	draw_line(0, 3, 4, 1, 0, 0, 255);
	draw_line(1, 0, 3, 4, 255, 0, 0);
	npWrite();
	sleep_ms(50);
	npClear();

 
    for(int i = 0; i < 5; i++){
        for(int j = 0; j < 5; j++){
            npClear();
            sleep_ms(100);

            npSetLED_coord(i,j, 255,0,0);
            npWrite();
            sleep_ms(100);
        }
    }
    npClear();

    draw_square(1,1,3,4,0,0,2);
    npWrite();
    sleep_ms(1000);
    draw_square(4,0,3,1,0,2,0);
    npWrite();
    sleep_ms(1000);
  }
}
