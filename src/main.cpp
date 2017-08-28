#include <Arduino.h>
#include <TimerOne.h>
#include "deskclock.cpp"
#include "leds.cpp"
#include "buttons.cpp"

int timeZone = 0;
uint8_t i2cData = 0;

void setup() {
//#if ARDUINO >= 101
	//pinMode(UPBUTTON, INPUT_PULLUP);
	//pinMode(DOWNBUTTON, INPUT_PULLUP);
//#else
	// Write a high to pin, acts as weak pull-up
	digitalWrite(UPBUTTON, HIGH);
	digitalWrite(DOWNBUTTON, HIGH);
	pinMode(UPBUTTON, INPUT);
	pinMode(DOWNBUTTON, INPUT);
//#endif

	// Column address bits 4 to 16 decode
	pinMode(4, OUTPUT); // DeMux A
	pinMode(5, OUTPUT); // DeMux B
	pinMode(6, OUTPUT); // DeMux C
	pinMode(7, OUTPUT); // DeMux D

	//test with
	DDRB = 0xFF; // all outputs

	// Make these pins outputs (analog 0 to 3)
	DDRC |= 0
		| 1 << PORTC0 // Column 17
		| 1 << PORTC1 // Column 18
		| 1 << PORTC2 // Column 19
		| 1 << PORTC3 // Column 20
		;

	// Turn one Interupts, used to update the displayed LED matrix
	// the ISR holds a single LED on for some number of microseconds;
	// this timeout value must be higher than that (by a few microseconds at least)
	// Lower numbers == less flicker
	Timer1.initialize(30); // was 100
	Timer1.attachInterrupt(LEDupdateTHREE);

	// I2C Inits
	Wire.begin();

	// Power Reduction - S
	power_adc_disable();
	power_spi_disable();
	power_usart0_disable();

	wdt_disable();

	// Program specific inits
	//  fillmatrix();
	delay(300);

	// if the top button is held at startup, run a lamp test
	if (!digitalRead(UPBUTTON)) {
		// TODO: This...
		//lamptest();
	}

	// transpose the image data into the frame buffer
	for (int row = 0 ; row < 7 ; row++)	{
		for (int col = 0 ; col < 20 ; col++) {
			//led_draw(col, row, col * 16 + row * 32);
			led_draw(col, row, logo[row][col]);
		}
	}
	delay(1000);

	displayString("GPSC"); // Updated so we know this isn't the Spikenzie firmware
	delay(1000);
	clearmatrix();

}


void loop() {
	checkButtons();
	// TODO: Check time...
}

void onBothPressed() {
	// TODO: Get GPS status...?
}

void onUpPressed() {
	// TODO: Protect for +12, display
	timeZone++;
}

void onDownPressed() {
	// TODO: Protect for +12, display
	timeZone--;
}
