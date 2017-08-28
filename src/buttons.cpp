#include <Arduino.h>

#define DEBOUNCE 10 // ms to debounce; at least 5 is good

#define UPBUTTON 2
#define DOWNBUTTON 3

int wasUpPressed = LOW;
int wasDownPressed = LOW;
long buttonsChecked = 0; // keeeps last button check time

// Button functions that should be defined elsewhere (this is like a "requirement")
void onBothPressed();
void onUpPressed();
void onDownPressed();

void checkButtons() {
	// Check to see if it's been long enough to debounce. If not, just return.
	if ((millis() <= buttonsChecked + DEBOUNCE)) {
		return;
	}

	int upPressed = digitalRead(UPBUTTON);
	int downPressed = digitalRead(DOWNBUTTON);

	if (upPressed == HIGH && downPressed == HIGH && wasUpPressed == LOW && wasDownPressed == LOW) {
		onBothPressed();
	} else if (wasUpPressed == LOW && upPressed == HIGH) {
		onUpPressed();
	} else if (wasDownPressed == LOW && downPressed == HIGH) {
		onDownPressed();
	}

	wasUpPressed = upPressed;
	wasDownPressed = downPressed;
	buttonsChecked = millis();

}
