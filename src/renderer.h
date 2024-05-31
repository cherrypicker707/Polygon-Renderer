#ifndef RENDERER
#define RENDERER

#include <stdbool.h>

void loadRenderer(unsigned short _windowWidth, unsigned short _windowHeight, const char *_windowTitle);
void updateRenderer();
void closeRenderer();
void clearRenderer();
bool isOpen();
void setDrawColor(double _red, double _green, double _blue);
bool getKey(unsigned short _key);

#endif
