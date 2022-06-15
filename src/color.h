#ifndef COLOR_H
#define COLOR_H

#include <windows.h>

#define DARK_PIECE_COLOR (FOREGROUND_BLUE | FOREGROUND_INTENSITY)
#define LIGHT_PIECE_COLOR (FOREGROUND_RED)

#define DARK_SPOT_COLOR (0)
#define LIGHT_SPOT_COLOR (BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_INTENSITY)

#define WRITING_COLOR (FOREGROUND_RED | FOREGROUND_GREEN)

void set_color(COLOR16 color);

void reset_color();

void clear_console();

#endif