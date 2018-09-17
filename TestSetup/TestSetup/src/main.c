#include <asf.h>

/*
 * Test program for reaction test setup
 * Author: Philip Ekholm
 */ 

#include "console_driver.h"
#include "pin_mapper.h"

#define LEFT_LED   53
#define MIDDLE_LED 51
#define RIGHT_LED  49
#define BTN1       47
#define BTN2       45

void enable_pins(void) {
	ioport_enable_pin(pin_mapper(LEFT_LED));
	ioport_enable_pin(pin_mapper(MIDDLE_LED));
	ioport_enable_pin(pin_mapper(RIGHT_LED));
	ioport_enable_pin(pin_mapper(BTN1));
	ioport_enable_pin(pin_mapper(BTN2));
	
	ioport_set_pin_dir(pin_mapper(LEFT_LED), IOPORT_DIR_OUTPUT);
	ioport_set_pin_dir(pin_mapper(MIDDLE_LED), IOPORT_DIR_OUTPUT);
	ioport_set_pin_dir(pin_mapper(RIGHT_LED), IOPORT_DIR_OUTPUT);
	
	ioport_set_pin_dir(pin_mapper(BTN1), IOPORT_DIR_INPUT);
	ioport_set_pin_dir(pin_mapper(BTN2), IOPORT_DIR_INPUT);
	
	/*pio_set_input(PIOC, PIO_PC18, PIO_PULLUP);
	pio_set_input(PIOC, PIO_PC16, PIO_PULLUP);*/
	
	/* Unfortunately PIO-system doesn't follow ioport convention so we must enter SAM-pins */
	PIOC->PIO_PUDR  |= PIO_PC18 | PIO_PC16; /* Set pull-up for both buttons */
	PIOC->PIO_IFER  |= PIO_PC18 | PIO_PC16; /* Enable switch debounce filter for both buttons */
	PIOC->PIO_DIFSR |= PIO_PC18 | PIO_PC16;
}

int main (void) {
	sysclk_init();
	board_init();

	console_init();
	ioport_init();
	enable_pins();
	
	uint8_t button1_pressed = 0,
			button2_pressed = 0;
	
	while(1) {
		button1_pressed = ~ioport_get_pin_level(pin_mapper(BTN1)) & 1;
		button2_pressed   = ~ioport_get_pin_level(pin_mapper(BTN2)) & 1;
		
		if (button1_pressed && button2_pressed) {
			ioport_set_pin_level(pin_mapper(RIGHT_LED), 1);
			ioport_set_pin_level(pin_mapper(MIDDLE_LED), 1);
			ioport_set_pin_level(pin_mapper(LEFT_LED), 1);
			printf("Both buttons pressed\n");
		}
		else if (button1_pressed) {
			ioport_set_pin_level(pin_mapper(RIGHT_LED), 0);
			ioport_set_pin_level(pin_mapper(MIDDLE_LED), 0);
			ioport_set_pin_level(pin_mapper(LEFT_LED), 1);
			printf("Button 1 pressed\n");
		}
		else if (button2_pressed) {
			ioport_set_pin_level(pin_mapper(RIGHT_LED), 1);
			ioport_set_pin_level(pin_mapper(MIDDLE_LED), 0);
			ioport_set_pin_level(pin_mapper(LEFT_LED), 0);
			printf("Button 2 pressed\n");
		}
		else {
			ioport_set_pin_level(pin_mapper(RIGHT_LED), 0);
			ioport_set_pin_level(pin_mapper(MIDDLE_LED), 0);
			ioport_set_pin_level(pin_mapper(LEFT_LED), 0);
			printf("No button pressed\n");
		}
		
	}
}
