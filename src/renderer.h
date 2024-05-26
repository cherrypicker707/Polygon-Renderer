#ifndef RENDERER
#define RENDERER

#include <stdbool.h>

void loadRenderer(int _windowWidth, int _windowHeight, const char *_windowTitle);
void updateRenderer();
void closeRenderer();
void clearRenderer();
bool isOpen();
void setDrawColor(float _red, float _green, float _blue);

#endif
