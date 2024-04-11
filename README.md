# Bredbox Console

Bredbox is an 8-bit game console inspired by retro game consoles.

Bredbox is a combination of the words:

- breadboard, which is used to stitch together electronic circuits on the board, and
- box, since well.. its a box.

## Materials

- Arduino UNO
- ILI9341 TFT LCD display with SPI communication
- Analog Joystick for control
- Piezoelectric buzzer

Minimum operating voltage = 5.4 V

## Wiring

|Arduino|ILI9341|
|-|-|
|10|TFT_CS|
|9|TFT_DC|
|11|TFT_MOSI|
|13|TFT_CLK|
|RESET|TFT_RST|
|12|TFT_MISO|

|Arduino|Analog Joystick<br>(INPUT_PULLUP)|
|-|-|
|A0|Vx/HOR|
|A1|Vy/VERT|
|8|SW|
|GND|GND|

|Arduino|Buzzer|
|7|+|
|GND|GND|

## Examples

Check out the `examples` folder for some games to play on the Bredbox.

These examples are pre-existing games that have been ported to the Bredbox.

|Game|Original authors|Source code|
|-|-|-|
|snake|Phillipp & Dave|_<https://wokwi.com/projects/376567216800840705>_|
