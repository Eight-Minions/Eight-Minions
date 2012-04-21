#ifndef BUTTON_H
#define BUTTON_H
#include "resources.h"

using std::string;

class Button
{
private:
	SDL_Rect *rect;
	SDL_Surface* image[2];
	int isPressed;
	bool lock;
public:
	Button(string baseImageName, int x, int y, int width, int height);

	void display(SDL_Surface* screen);

	bool wasClicked(int clickX, int clickY);
	bool isClicked();
	void setClick(bool nPress);
	bool wasClickedState( int clickX, int clickY);

	void Lock();
};
#endif