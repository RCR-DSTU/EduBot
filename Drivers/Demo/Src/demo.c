#include "demo.h"


char* items_menu[2][3] = {
					{"Program #1", "Program #2", "Program #3"},
					{"Program #4", "Program #5", "Program #6"}
						 };

char* names_parameters[] = {"distn", "name2", "name3", "name4", "name5", "name6"};

static const char digits[] = "0123456789";


const uint8_t show_menu_items_X = 10;
uint8_t show_menu_items_Y = 18;

const uint8_t indicator_X = 8;
uint8_t indicator_Y = 16;

const uint8_t progress_bar_X = 14;
uint8_t progress_bar_Y = 43;

char str[4];
char speed_str[5];
char dist_str[5];






void FirstScreen()
{
	SSD1306_Fill(SSD1306_COLOR_BLACK);
	SSD1306_GotoXY(12, 4);
	SSD1306_Puts(" RCR", &Font_7x10, SSD1306_COLOR_WHITE);
	SSD1306_GotoXY(84, 4);
	SSD1306_Puts("DSTU", &Font_7x10, SSD1306_COLOR_WHITE);
	SSD1306_Image(logo_RCR_40x40, 40, 40, 10, 16);
	SSD1306_Image(logo_DSTU_40x40, 40, 40, 80, 16);
}


void MenuRectangle()
{
	SSD1306_DrawRectangle(3, 3, 122, 58, SSD1306_COLOR_WHITE);
	SSD1306_DrawRectangle(3, 3, 122, 12, SSD1306_COLOR_WHITE);
	SSD1306_GotoXY(36, 4);
	SSD1306_Puts("Main menu", &Font_7x10, SSD1306_COLOR_WHITE);
}


void ShowMenuItems()
{
	for(int i = 0; i < 3; i++)
	{
		SSD1306_GotoXY(show_menu_items_X, show_menu_items_Y);
		SSD1306_Puts(items_menu[robot.currentPage][i], &Font_7x10, SSD1306_COLOR_WHITE);
		show_menu_items_Y += 15;
	}

	show_menu_items_Y = 18;
	SSD1306_UpdateScreen();
}


void Indicator(bool IsUp)
{
	switch (IsUp)
			{
				case true:
					if(indicator_Y <= 18 && robot.currentPage == 0)
					{
						break;
					}
					else if(indicator_Y <= 18 && robot.currentPage != 0)
					{
						robot.currentPage -= 1;
						indicator_Y = 46;
						robot.currentProg -= 1;
						break;
					}
					indicator_Y -= 15;
					robot.currentProg -= 1;

					break;
				case false:
					if(indicator_Y >= 46 && robot.currentPage == 1)
					{
						break;
					}
					else if(indicator_Y >= 46 && robot.currentPage < 2 )
					{
						robot.currentPage += 1;
						indicator_Y = 16;
						robot.currentProg += 1;
						break;
					}
					indicator_Y += 15;
					robot.currentProg += 1;
					break;
			}

}


void NewFrameMenu()
{
	SSD1306_Fill(SSD1306_COLOR_BLACK);
	MenuRectangle();
	SSD1306_DrawFilledRectangle(indicator_X, indicator_Y, 110, 13, SSD1306_COLOR_WHITE);
	ShowMenuItems();
}


void ParameterMenu(uint8_t value)
{
	SSD1306_Fill(SSD1306_COLOR_BLACK);
	SSD1306_DrawRectangle(3, 3, 122, 58, SSD1306_COLOR_WHITE);
	SSD1306_DrawRectangle(3, 3, 122, 12, SSD1306_COLOR_WHITE);
	SSD1306_DrawRectangle(22, 31, 84, 15, SSD1306_COLOR_WHITE);
	SSD1306_GotoXY(36, 4);
	SSD1306_Puts("Settings", &Font_7x10, SSD1306_COLOR_WHITE);
	SSD1306_GotoXY(22, 20);
	SSD1306_Puts("Select ", &Font_7x10, SSD1306_COLOR_WHITE);
	SSD1306_GotoXY(71, 20);
	SSD1306_Puts(names_parameters[value], &Font_7x10, SSD1306_COLOR_WHITE);
	SSD1306_GotoXY(56, 34);
	sprintf(str, "%.1f", robot.input_arg);
	SSD1306_Puts(str, &Font_7x10, SSD1306_COLOR_WHITE);
	SSD1306_UpdateScreen();
}


void SelectParameter(bool IsUp)
{
	switch(IsUp)
	{
		case true:
			robot.input_arg += 0.1;
			break;
		case false:
			 if(robot.input_arg != 0.0)
			 {
				 robot.input_arg -= 0.1;
				 break;
			 }
			break;
	}
}


void ScreenExecution(void)
{
	SSD1306_Fill(SSD1306_COLOR_BLACK);
	SSD1306_DrawRectangle(3, 3, 122, 58, SSD1306_COLOR_WHITE);
	SSD1306_DrawRectangle(3, 3, 122, 12, SSD1306_COLOR_WHITE);
	SSD1306_GotoXY(36, 4);
	SSD1306_Puts("Progress", &Font_7x10, SSD1306_COLOR_WHITE);
	SSD1306_DrawRectangle(14, 43, 100, 12, SSD1306_COLOR_WHITE);
}


void ProgressBar(float progress)
{
	if(progress <= 0.0 || progress >= 1.00 ) return;

	uint8_t pixels = 100 * progress;
	SSD1306_DrawFilledRectangle(progress_bar_X, progress_bar_Y, pixels, 12, SSD1306_COLOR_WHITE);
	SSD1306_UpdateScreen();

}


void FloatToChar(float number, char* string)
{
	if(number >= 0){
		string[0] = ' ';

	}
	else{
		string[0] = '-';
		number = -number;
	}
	uint8_t firstNumber = (int)(number);
	uint8_t frac_part = (int)((number - firstNumber) * 100);
	uint8_t secondNumber = (int)(frac_part / 10);
	uint8_t thirdNumber = (int)(frac_part % 10);

	string[1] = digits[firstNumber];
	string[2] = '.';
	string[3] = digits[secondNumber];
	string[4] = digits[thirdNumber];
}









