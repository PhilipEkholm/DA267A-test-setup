#include <asf.h>

#include "console_driver.h"
#include "pin_mapper.h"

#define LEFT_LED   53
#define MIDDLE_LED 51
#define RIGHT_LED  49
#define GREEN_BTN  47
#define RED_BTN    45
#define PWR        22

int main (void) {
	sysclk_init();
	board_init();

	console_init();
	ioport_init();
	
	ioport_enable_pin(pin_mapper(LEFT_LED));
	ioport_enable_pin(pin_mapper(MIDDLE_LED));
	ioport_enable_pin(pin_mapper(RIGHT_LED));
	ioport_enable_pin(pin_mapper(GREEN_BTN));
	ioport_enable_pin(pin_mapper(RED_BTN));
	ioport_enable_pin(pin_mapper(PWR));
	
	ioport_set_pin_dir(pin_mapper(LEFT_LED), IOPORT_DIR_OUTPUT);
	ioport_set_pin_dir(pin_mapper(MIDDLE_LED), IOPORT_DIR_OUTPUT);
	ioport_set_pin_dir(pin_mapper(RIGHT_LED), IOPORT_DIR_OUTPUT);
	ioport_set_pin_dir(pin_mapper(PWR), IOPORT_DIR_OUTPUT);
	
	ioport_set_pin_dir(pin_mapper(GREEN_BTN), IOPORT_DIR_INPUT);
	ioport_set_pin_dir(pin_mapper(RED_BTN), IOPORT_DIR_INPUT);
	
	/* Should be constant high */
	ioport_set_pin_level(pin_mapper(PWR), 1);
	
	pio_set_input(PIOC, PIO_PC18, PIO_PULLUP);
	pio_set_input(PIOC, PIO_PC16, PIO_PULLUP);
	PIOC->PIO_PUDR |= PIO_PC18 | PIO_PC16;
	
	uint8_t green_pressed = 0,
			red_pressed   = 0;
	
	while(1) {
		green_pressed = ioport_get_pin_level(pin_mapper(GREEN_BTN));
		red_pressed   = ioport_get_pin_level(pin_mapper(RED_BTN));
		
		if (green_pressed && red_pressed) {
			ioport_set_pin_level(pin_mapper(RIGHT_LED), 1);
			ioport_set_pin_level(pin_mapper(MIDDLE_LED), 1);
			ioport_set_pin_level(pin_mapper(LEFT_LED), 1);
			printf("Both buttons pressed\n");
		}
		else if (green_pressed) {
			ioport_set_pin_level(pin_mapper(RIGHT_LED), 0);
			ioport_set_pin_level(pin_mapper(MIDDLE_LED), 0);
			ioport_set_pin_level(pin_mapper(LEFT_LED), 1);
			printf("Green button pressed\n");
		}
		else if (red_pressed) {
			ioport_set_pin_level(pin_mapper(RIGHT_LED), 1);
			ioport_set_pin_level(pin_mapper(MIDDLE_LED), 0);
			ioport_set_pin_level(pin_mapper(LEFT_LED), 0);
			printf("Red button pressed\n");
		}
		else {
			ioport_set_pin_level(pin_mapper(RIGHT_LED), 0);
			ioport_set_pin_level(pin_mapper(MIDDLE_LED), 0);
			ioport_set_pin_level(pin_mapper(LEFT_LED), 0);
			printf("No button pressed\n");
		}
		
	}
}
