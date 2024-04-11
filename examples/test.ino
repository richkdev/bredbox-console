// created by Richmond Kleinson

#define TFT_CS 10
#define TFT_DC 9
#define TFT_MOSI 11
#define TFT_CLK 13
#define TFT_RST 8
#define TFT_MISO 12

int joystick_X, joystick_Y, joystick_X_map, joystick_Y_map;
bool joystick_bValue;

void setup()
{
	pinMode(A0, INPUT_PULLUP);
	pinMode(A1, INPUT_PULLUP);
	pinMode(8, INPUT_PULLUP);

	pinMode(6, OUTPUT);

	Serial.begin(9600);

	tft.fillScreen(ILI9341_BLACK);
	tft.setCursor(0, 0);
	tft.setTextSize(1);
	tft.println("hello world!");
}

void loop()
{
	joystick_X = analogRead(A0);
	joystick_Y = analogRead(A1);
	joystick_bValue = digitalRead(8);

	joystick_X_map = map(joystick_X, 0, 1023, 512, -512);
	joystick_Y_map = map(joystick_Y, 0, 1023, 512, -512);

	Serial.println(String(joystick_X_map) + " " + String(joystick_Y_map) + " " + String(!joystick_bValue));

	tone(6, 5);

	delay(500);
}