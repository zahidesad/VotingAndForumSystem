#ifndef COLOR_H
#define COLOR_H

#define ANSI_COLOR_RED "\e[1;91m"
#define ANSI_COLOR_GREEN "\e[1;92m"
#define ANSI_COLOR_YELLOW "\e[1;93m"
#define ANSI_COLOR_BLUE_BOLD "\e[1;94m"
#define ANSI_COLOR_BLUE "\e[0;34m"
#define ANSI_COLOR_MAGENTA "\e[1;95m"
#define ANSI_COLOR_CYAN "\e[1;96m"
#define ANSI_COLOR_WHITE "\e[1;97m"
#define ANSI_COLOR_RESET "\x1b[0m"

void Color_Red();
void Color_Green();
void Color_Yellow();
void Color_Blue_Bold();
void Color_Blue();
void Color_Magenta();
void Color_Cyan();
void Color_White();
void Color_Reset();

#endif