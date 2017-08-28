#include <Arduino.h>
#include "setup.cpp"
#include "deskclock.cpp"
#include "leds.cpp"
#include "buttons.cpp"

int timeZone = 0;

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
