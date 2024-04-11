// created by Philipp & Max on Wokwi
// modded & ported by Richmond Kleinson

#include "SPI.h"
#include "Adafruit_GFX.h"
#include "Adafruit_ILI9341.h"

#define TFT_DC 9
#define TFT_CS 10
Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC);

int position[100][2] = {{12, 16}, {12, 17}, {12, 18}}; // start position
int apple_position[2];
int score = 0;
int highscore = 0;
int speed = 300;
int e = 3;
int direction = 1;

void setup()
{
	pinMode(8, INPUT_PULLUP);
	tft.begin();
}

void loop()
{
	startscreen();
	game();
}

void startscreen()
{
	tft.fillScreen(ILI9341_DARKGREEN);
	draw_appleandsnake();
	draw_logo();
	draw_starttext();

	while (digitalRead(8) == HIGH)
	{
	}
}

void game()
{
	int melody[] = {8, 5, 8};
	playMelody(melody, sizeof(melody));

	draw_design();
	spawn_apple();

	for (int i = 0; i < e; i++)
	{
		draw_quadrat(position[i][0], position[i][1], ILI9341_BLACK);
	}

	check_direction();
}

void check_direction()
{
	while (true)
	{
		if (direction == 1)
		{ // up
			if (position[0][1] == 3)
			{
				gameover();
			}
			step();
			position[0][1] -= 1;
		}

		else if (direction == 2)
		{ // right
			if (position[0][0] == 22)
			{
				gameover();
			}
			step();
			position[0][0] += 1;
		}

		else if (direction == 3)
		{ // down
			if (position[0][1] == 30)
			{
				gameover();
			}
			step();
			position[0][1] += 1;
		}

		else if (direction == 4)
		{ // left
			if (position[0][0] == 1)
			{
				gameover();
			}
			step();
			position[0][0] -= 1;
		}

		draw_quadrat(position[0][0], position[0][1], ILI9341_BLACK);
		check_and_delay(speed);
	}
}

void step()
{
	int last = e - 1;
	draw_quadrat(position[last][0], position[last][1], ILI9341_DARKGREEN);

	for (int i = last; i > 0; i--)
	{
		position[i][0] = position[i - 1][0];
		position[i][1] = position[i - 1][1];
	}
	check_apple();
	check_collision();
}

void check_apple()
{
	if (position[0][0] == apple_position[0] && position[1][1] == apple_position[1])
	{
		score += 1;
		draw_score();
		append_square();
		spawn_apple();

		if (300 - score * 10 < 80)
		{
			speed = 50; // speed minimal 50
		}
		else
		{
			speed = 300 - score * 10;
		}
	}
}

void check_collision()
{
	for (int i = 2; i < e; i++)
	{
		if (position[0][0] == position[i][0] && position[0][1] == position[i][1])
		{
			gameover();
		}
	}
}

void append_square()
{
	position[e][0] = position[e - 1][0];
	position[e][1] = position[e - 1][1];

	e++;
}

void check_and_delay(int ms)
{
	for (int i = 0; i < ms; i++)
	{
		if ((analogRead(A0) < 100) && direction != 3)
		{
			direction = 1; // up
		}
		if ((analogRead(A1) < 100) && direction != 4)
		{
			direction = 2; // right
		}
		if ((analogRead(A0) > 900) && direction != 1)
		{
			direction = 3; // down
		}
		if ((analogRead(A1) > 900) && direction != 2)
		{
			direction = 4; // left
		}
		delay(1);
	}
}

void draw_design()
{
	tft.fillScreen(ILI9341_DARKGREEN);
	tft.drawRect(9, 29, 222, 282, ILI9341_BLACK);

	tft.setCursor(50, 5);
	tft.setTextColor(ILI9341_BLACK);
	tft.setTextSize(3);
	tft.println("SCORE: ");
	tft.setCursor(175, 5);
	tft.println(score);
	draw_apple();
}

void draw_score()
{
	tft.setCursor(175, 5);
	tft.setTextSize(3);
	tft.setTextColor(ILI9341_DARKGREEN);
	tft.println(score - 1);

	tft.setCursor(175, 5);
	tft.setTextSize(3);
	tft.setTextColor(ILI9341_BLACK);
	tft.println(score);

	int melody[] = {3, 5, 8};
	playMelody(melody, sizeof(melody));
}

void spawn_apple()
{
	int random_x = random(1, 23);
	int random_y = random(3, 31);

	for (int i = 0; i < sizeof(position) / 4; i++)
	{
		if (position[i][0] == random_x && position[i][1] == random_y)
		{
			spawn_apple();
			exit(0);
		}
	}

	apple_position[0] = random_x;
	apple_position[1] = random_y;
	draw_quadrat(random_x, random_y, ILI9341_RED); // random Quadrat in rot
}

void draw_quadrat(int x_pos, int y_pos, int color)
{
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			tft.drawPixel(x_pos * 10 + i, y_pos * 10 + j, color);
		}
	}
}

void draw_appleandsnake()
{
	tft.fillRect(80, 30, 130, 10, ILI9341_ORANGE);
	tft.fillRect(200, 30, 10, 70, ILI9341_ORANGE);
	tft.fillRect(30, 90, 170, 10, ILI9341_ORANGE);
	tft.fillRect(30, 90, 10, 80, ILI9341_ORANGE);
	tft.fillRect(30, 170, 80, 10, ILI9341_ORANGE);

	tft.fillRect(104, 176, 2, 2, ILI9341_BLACK);
	tft.fillRect(104, 172, 2, 2, ILI9341_BLACK);
	tft.fillRect(110, 174, 4, 2, ILI9341_RED);

	tft.fillCircle(140, 174, 5, ILI9341_RED);
	tft.drawCircle(140, 174, 6, ILI9341_BLACK);
	tft.fillCircle(143, 165, 1, ILI9341_GREEN);
	tft.fillCircle(144, 165, 1, ILI9341_GREEN);
	tft.fillCircle(144, 166, 1, ILI9341_GREEN);
	tft.drawLine(140, 170, 143, 163, ILI9341_MAROON);
}

void draw_logo()
{
	tft.setCursor(50, 52);
	tft.setTextColor(ILI9341_WHITE);
	tft.setTextSize(5);
	tft.println("SNAKE");
	tft.setCursor(65, 105);
	tft.println("GAME");
}

void draw_starttext()
{
	tft.setCursor(20, 240);
	tft.setTextColor(ILI9341_LIGHTGREY);
	tft.setTextSize(2);
	tft.println("> PRESS TO PLAY <");

	// print credits
	tft.setCursor(20, 300);
	tft.setTextColor(ILI9341_WHITE);
	tft.setTextSize(1);
	tft.println("created by Philipp & Max on Wokwi");
	tft.setCursor(20, 310);
	tft.println("modded & ported by RichKDEV");
}

void draw_apple()
{
	tft.fillCircle(220, 17, 8, ILI9341_RED);
	tft.drawCircle(220, 17, 9, ILI9341_BLACK);
	tft.fillCircle(223, 8, 2, ILI9341_GREEN);
	tft.fillCircle(224, 8, 2, ILI9341_GREEN);
	tft.fillCircle(224, 9, 2, ILI9341_GREEN);
	tft.drawLine(220, 13, 223, 3, ILI9341_MAROON);
	tft.drawLine(219, 13, 222, 3, ILI9341_MAROON);
}

void check_highscore()
{
	if (score > highscore)
	{
		highscore = score;

		tft.setCursor(40, 230);
		tft.setTextColor(ILI9341_YELLOW);
		tft.setTextSize(2);
		tft.println("NEW HIGHSCORE!");
	}

	tft.setCursor(40, 5);
	tft.setTextColor(ILI9341_YELLOW);
	tft.setTextSize(2);
	tft.println("HIGHSCORE:");
	tft.setCursor(180, 5);
	tft.println(highscore);
}

void gameover()
{
	tft.fillScreen(ILI9341_BLACK);
	tft.setCursor(15, 140);
	tft.setTextColor(ILI9341_RED);
	tft.setTextSize(4);
	tft.println("GAME OVER");

	tft.setCursor(70, 200);
	tft.setTextColor(ILI9341_WHITE);
	tft.setTextSize(2);
	tft.println("Score:");
	tft.setCursor(155, 200);
	tft.println(score);

	check_highscore();

	tft.setCursor(7, 300);
	tft.setTextColor(ILI9341_DARKGREY);
	tft.setTextSize(2);
	tft.println("<press to continue>");

	while (digitalRead(8) == HIGH)
	{
	};
	reset_game();
}

void reset_game()
{
	int melody[] = {8, 5, 3};
	playMelody(melody, sizeof(melody));

	direction = 1;
	score = 0;
	speed = 300;
	e = 3;

	for (int i = 0; i < 3; i++)
	{
		position[i][0] = 12;
		position[i][1] = 16 + i;
	}

	game();
}

void playMelody(int melody[], int sizeArray)
{
	for (int i = 0; i < sizeArray - 1; i++)
	{
		tone(7, melody[i], 100);
		delay(70);
		noTone(7);
	}
}