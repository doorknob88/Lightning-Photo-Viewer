#include <SDL.h>
#include <stdio.h>
#include "wtypes.h"
#include <string>
#include <SDL_opengl.h>
#include <GL\GLU.h>
#include <iostream>
#include <gl\gl.h> 
#include <gl\glu.h>
#include <windows.h>
#include <sdl_image.h>
using namespace std;

//SDL GLOBAL VARIABLES
int SCREEN_WIDTH = 0;
int SCREEN_HEIGHT = 0;

//The window we'll be rendering to
SDL_Window* window = NULL;
//The surface contained by the window
SDL_Surface* screenSurface = NULL;
// Global function declerations
void initializeSDL();
void getBackground();

//Global function definitions

//Get the horizontal and vertical screen sizes in pixel
void GetDesktopResolution()
{
	RECT desktop;
	// Get a handle to the desktop window
	const HWND hDesktop = GetDesktopWindow();
	// Get the size of screen to the variable desktop
	GetWindowRect(hDesktop, &desktop);
	// The top left corner will have coordinates (0,0)
	// and the bottom right corner will have coordinates
	// (horizontal, vertical)
	SCREEN_WIDTH = desktop.right;
	SCREEN_HEIGHT = desktop.bottom;
	printf("Screen width: %i , Screen Height: %i", SCREEN_WIDTH, SCREEN_HEIGHT);
}
void initializeSDL() {
	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
	}
	else
	{
		//Create window
		window = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_HIDDEN);
		if (window == NULL)
		{
			printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
		}
		else
		{
			//Get window surface
			screenSurface = SDL_GetWindowSurface(window);
			//getBackground();
			//Fill the surface white
			//SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0x00, 0xFF, 0xFF));	
			//SDL_ShowWindow(window);
			//Update the surface
			//SDL_UpdateWindowSurface(window);
			//Wait one second
			//SDL_Delay(1000);
		}
	}
}

// TODO: make screenshot happen
void getBackground() {
	//HWND hwnd = GetConsoleWindow();
	//ShowWindow(hwnd, SW_HIDE);
	//Sleep(1000);
	int x1, y1;
	x1 = GetSystemMetrics(SM_XVIRTUALSCREEN);
	y1 = GetSystemMetrics(SM_YVIRTUALSCREEN);

	HDC hScreen = GetDC(NULL);
	HDC hDC = CreateCompatibleDC(hScreen);
	HBITMAP hBitmap = CreateCompatibleBitmap(hScreen, SCREEN_WIDTH, SCREEN_HEIGHT);
	HGDIOBJ old_obj = SelectObject(hDC, hBitmap);
	BOOL bRet = BitBlt(hDC, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, hScreen, x1, y1, SRCCOPY);
	
	OpenClipboard(NULL);
	EmptyClipboard();
	SetClipboardData(CF_BITMAP, hBitmap);
	CloseClipboard();
	BITMAP bitmap;
	GetObject(hBitmap, sizeof(BITMAP), &bitmap);
	SDL_RWops *rw = SDL_RWFromMem(&bitmap, sizeof(bitmap));
	SDL_Surface *image;
	image = IMG_LoadBMP_RW(rw);
	cout<< "\n" << rw <<"\n";
	//SDL_SaveBMP_RW(screenSurface, rw, 1);
	//SDL_UpdateWindowSurface(window);
	//SDL_SaveBMP(image, "C:/Temp/pic.bmp");
	SDL_RWclose(rw);
}

void loadpicture() {
	bool success = true;
}
void getPictureArray() {}

int main(int argc, char* args[])
{
	
	//getScreenDimensions();
	GetDesktopResolution();
	initializeSDL();

	//getScreenShot();
	getBackground();
	//Destroy window
	SDL_DestroyWindow(window);

	//Quit SDL subsystems
	SDL_Quit();
	getchar();
	return 0;
}