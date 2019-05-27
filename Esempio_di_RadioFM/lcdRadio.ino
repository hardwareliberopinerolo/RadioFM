/*
LCD Radio
https://hackaday.io/project/9009-arduino-radio-with-rds
*/

#include <EEPROM.h>
#include <LiquidCrystal.h>
#include <Wire.h>
#include "radio.h";

#define SHOW_STATION 0
#define SHOW_VOLUME  1
#define SHOW_TUNING  2


byte CHR_ANTENNA[8] = {
	B11111, B10101, B10101, B01110, B00100, B00100, B00100, B00100
};

byte CHR_STRENGTH[8][8] = {{
	B00000, B00000, B00000, B00000, B00000, B00000, B00000, B10000
}, {
	B00000, B00000, B00000, B00000, B00000, B00000, B11000, B10000
}, {
	B00000, B00000, B00000, B00000, B00000, B11000, B11000, B10000
}, {
	B00000, B00000, B00000, B00000, B11100, B11000, B11000, B10000
}, {
	B00000, B00000, B00000, B11100, B11100, B11000, B11000, B10000
}, {
	B00000, B00000, B11110, B11100, B11100, B11000, B11000, B10000
}, {
	B00000, B11110, B11110, B11100, B11100, B11000, B11000, B10000
}, {
	B11111, B11110, B11110, B11100, B11100, B11000, B11000, B10000
}};


byte CHR_BAR[7][8] = {{
	B11111, B00000, B00000, B00000, B00000, B00000, B00000, B11111
}, {
	B11111, B00000, B11000, B11000, B11000, B11000, B00000, B11111
}, {
	B11111, B00000, B11011, B11011, B11011, B11011, B00000, B11111
}, {
	B01111, B11000, B10000, B10000, B10000, B10000, B11000, B01111
}, {
	B11110, B00011, B00001, B00001, B00001, B00001, B00011, B11110
}};



LiquidCrystal lcd(8, 9, 4, 5, 6, 7);
Radio radio;


byte currentDisplay = SHOW_STATION;
long displayTimeout;
long lastKeyPress;


void setup() {
	lcd.begin(16, 2);
	lcd.createChar(0, CHR_ANTENNA);
	lcd.createChar(1, CHR_STRENGTH[7]);
	lcd.createChar(2, CHR_BAR[0]);
	lcd.createChar(3, CHR_BAR[1]);
	lcd.createChar(4, CHR_BAR[2]);
	lcd.createChar(5, CHR_BAR[3]);
	lcd.createChar(6, CHR_BAR[4]);

	lcd.clear();
	lcd.setCursor(0, 0);
	lcd.print("     Radio?     ");

	if (!radio.init()) {
		lcd.setCursor(0, 1);
		lcd.print("Radio error!    ");
		while(true);
	}
	// tuneTo(87.6);

	if (EEPROM.read(0) == 'R' && EEPROM.read(1) == 'A' && EEPROM.read(2) == 'D' && EEPROM.read(3) == 'I' && EEPROM.read(4) == 'O') {
		radio.tuneTo(getEepromFreq());
		radio.setVolume(getEepromVolume());
	} else {
		EEPROM.update(0, 'R');
		EEPROM.update(1, 'A');
		EEPROM.update(2, 'D');
		EEPROM.update(3, 'I');
		EEPROM.update(4, 'O');
		setEepromVolume(4);
	}

	radio.setBassBoost(true);
	radio.setMute(false);

	lastKeyPress = millis();
	displayTimeout = 0;
}


void loop() {
	radio.updateStatus();
	if (!radio.state.isTunedToChannel && currentDisplay == SHOW_STATION) {
		currentDisplay = SHOW_TUNING;
		displayTimeout = 0;
	} else if (currentDisplay == SHOW_TUNING && radio.state.isTunedToChannel) {
		currentDisplay = SHOW_STATION;
		setEepromFreq(radio.state.frequency);
	}

	handleKeys();
	updateDisplay();
	delay(10);
}


void handleKeys() {
	unsigned short keyState = analogRead(0);
	if (keyState == 1023 || millis() - lastKeyPress < 100) return;

	switch (keyState) {
		case 99:
			if (radio.state.volume < 15) {
				radio.setVolume(radio.state.volume + 1);
				displayTimeout = millis() + 5000;
				currentDisplay = SHOW_VOLUME;
			}
			break;

		case 255:
			if (radio.state.volume > 0) {
				radio.setVolume(radio.state.volume - 1);
				displayTimeout = millis() + 5000;
				currentDisplay = SHOW_VOLUME;
			}
			break;

		case 408:
			radio.seekDown();
			break;

		case 0:
			radio.seekUp();
			break;
	}

	lastKeyPress = millis();
}



void updateDisplay() {
	if (currentDisplay != SHOW_STATION && displayTimeout != 0 && millis() > displayTimeout) {
		if (currentDisplay == SHOW_VOLUME) {
			setEepromVolume(radio.state.volume);
		}
		lcd.clear();
		currentDisplay = SHOW_STATION;
	}

	drawStatusLine();

	switch (currentDisplay) {
		case SHOW_STATION:
			lcd.setCursor(0, 1);
			if (radio.state.hasStationName) {
				lcd.print("    ");
				lcd.print(radio.state.stationName);
				lcd.print("    ");
			} else {
				lcd.print("                ");
			}
			break;

		case SHOW_VOLUME:
			lcd.setCursor(0, 1);
			lcd.print("Volume ");
			lcd.write(byte(5));
			for (byte i = 0; i < 7; i ++) {
				if (radio.state.volume > i * 2 + 1) {
					lcd.write(byte(4));
				} else if (radio.state.volume > i * 2) {
					lcd.write(byte(3));
				} else {
					lcd.write(byte(2));
				}
			}
			lcd.write(byte(6));
			break;

		case SHOW_TUNING:
			lcd.setCursor(0, 1);
			lcd.print("  Searching...  ");
			break;
	}
}


void drawStatusLine() {
	lcd.setCursor(0, 0);
	lcd.print(radio.state.frequency);
	lcd.print(" MHz   ");

	switch (radio.state.signalStrength) {
		case 0 ... 1:
			lcd.createChar(1, CHR_STRENGTH[0]);
			break;
		case 2 ... 13:
			lcd.createChar(1, CHR_STRENGTH[1]);
			break;
		case 14 ... 24:
			lcd.createChar(1, CHR_STRENGTH[2]);
			break;
		case 25 ... 34:
			lcd.createChar(1, CHR_STRENGTH[3]);
			break;
		case 35 ... 43:
			lcd.createChar(1, CHR_STRENGTH[4]);
			break;
		case 44 ... 51:
			lcd.createChar(1, CHR_STRENGTH[5]);
			break;
		case 52 ... 57:
			lcd.createChar(1, CHR_STRENGTH[6]);
			break;
		case 58 ... 63:
			lcd.createChar(1, CHR_STRENGTH[7]);
			break;
	}
	lcd.setCursor(14, 0);
	lcd.write(byte(0));
	lcd.write(byte(1));
}


float getEepromFreq() {
	float frequency = 0.0f;
	frequency += EEPROM.read(6)  * 100.0f;
	frequency += EEPROM.read(7)  * 10.0f;
	frequency += EEPROM.read(8);
	frequency += EEPROM.read(9)  / 10.0f;
	frequency += EEPROM.read(10) / 100.0f;
	return frequency;
}


byte getEepromVolume() {
	return EEPROM.read(11);
}


void setEepromFreq(float frequency) {
	unsigned short freq = frequency * 100;
	EEPROM.update(6, (freq / 10000));
	EEPROM.update(7, (freq / 1000) % 10);
	EEPROM.update(8, (freq / 100) % 10);
	EEPROM.update(9, (freq / 10) % 10);
	EEPROM.update(10, freq % 10);
}


void setEepromVolume(byte volume) {
	EEPROM.update(11, volume);
}

