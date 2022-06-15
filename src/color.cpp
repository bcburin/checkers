#include "color.h"

void set_color(COLOR16 color) { SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color); }

void reset_color() { set_color(15U); }