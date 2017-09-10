#include <Arduino.h>
#include "matrix.cpp"

const int digitoffset = 95;                // 95             // was 16


void displayString(const char outText[]);
void displayGraphic(int index, int pos, int len);
void draw_small_digit (uint8_t column, unsigned digit, unsigned blinking);
void draw_char(unsigned col, const char c);
void clearmatrix();
void writeTime(uint8_t dig1, uint8_t dig2, uint8_t dig3, uint8_t dig4);

/*
 * Output 4 Characters to Display
 */
void displayString(const char outText[])
{
	for (int i=0 ; i < 4 ; i++)
		draw_char(5*i+1, outText[i]);
}


/*
 * Output Custom Graphic to Display
 */
void displayGraphic(int index, int pos, int len)
{
	for (int y=0 ; y<len ; y++)
		led_draw_col(pos++, GRAPHIC[index][y], 0xFF);
}


void draw_small_digit (uint8_t column, unsigned digit, unsigned blinking) {
	for (unsigned i=0 ; i < 4 ; i++) {
		led_draw_col(
			column+i,
			LETTERS[digit+digitoffset][i+1],
			0xFF // TODO: Bright?
		);
	}
}


void draw_char(unsigned col, const char c) {
	for (int y=0 ; y<5 ; y++)
		led_draw_col(col++, LETTERS[c - ASCII_OFFSET][y],0xFF );
}


/*
 * Clear LED Matrix
 */
void clearmatrix() {
	for (int i=0 ; i<WIDTH ; i++)
		led_draw_col(i, 0, 0);
}



/**
 * Display the four digit time with small characters.
 *
 *
 * Fills diplay with formated time
 * Depending on postion of "1"s spacing is adjusted beween it and next digit
 * Blinks if it settng mode
 * displays AM/PM dot and Alarm on dot
 */
void writeTime(uint8_t dig1, uint8_t dig2, uint8_t dig3, uint8_t dig4) {

	draw_small_digit(2, dig1, 0);
	draw_small_digit(6, dig2, 0);

	// the slowly flashing " : "
	static uint16_t bright = 0;
	uint8_t b = bright++ / 8;
	if (b >= 128)
		b = 0xFF - b;
	led_draw(10, 2, 2*b);
	led_draw(10, 4, 2*b);

	draw_small_digit(12, dig3, 0);
	draw_small_digit(16, dig4, 0);

}
