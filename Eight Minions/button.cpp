#include "button.h"


Button::Button( string baseImageName, int x, int y, int width, int height)
{
	string temp;
	rect = newRect(x,y,width,height);
	temp = baseImageName + "Up.png";
	image[0] = LoadImageCK(temp);
	temp = baseImageName + "Down.png";
	image[1] = LoadImageCK(temp);
	isPressed = 0;
	lock = false;
}

void Button::display( SDL_Surface* screen )
{
	if(image[isPressed] != NULL)
	{
		SDL_BlitSurface(image[isPressed], NULL, screen, rect);
	}
	else
	{
		cout << "No image loaded for button.\n";
	}
}

bool Button::wasClicked( int clickX, int clickY)
{
	if(lock)
		return false;
	if(clickX >= rect->x && clickX <= rect->x + rect->w && clickY >= rect->y && clickY <= rect->y + rect->h)
	{
		isPressed = (isPressed + 1) % 2;
		return isPressed == 1;
	}
	else
		return false;
}

bool Button::wasClickedState( int clickX, int clickY)
{
	if(clickX >= rect->x && clickX <= rect->x + rect->w && clickY >= rect->y && clickY <= rect->y + rect->h)
	{
		return true;
	}
	else
		return false;
}

bool Button::isClicked()
{
	return (!lock) && (isPressed == 1);
}

void Button::setClick( bool nPress )
{
	isPressed = nPress;
}

void Button::Lock()
{
	lock = true;
}


