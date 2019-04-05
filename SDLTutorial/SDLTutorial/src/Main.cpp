#include <SDL.h>
#include <stdio.h>

bool init();
bool loadMedia();
void close();


const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;


SDL_Window* gWindow = NULL;
SDL_Surface* gScreenSurface = NULL;
SDL_Surface* gXout = NULL;

bool init()
{
	bool success = true;

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		gWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

		if (gWindow == NULL)
		{
			printf("Window could not be open! SDL_Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			gScreenSurface = SDL_GetWindowSurface(gWindow);
		}
	}

	return success;
}


bool loadMedia()
{
	bool success = true;

	gXout = SDL_LoadBMP("img/x.bmp");

	if (gXout == NULL)
	{
		printf("Unable to load image %s! SDL Error: %s\n", "img/x.bmp", SDL_GetError());

		success = false;
	}

	return success;
}


void close()
{
	SDL_FreeSurface(gXout);
	gXout = NULL;

	SDL_DestroyWindow(gWindow);
	gWindow = NULL;

	SDL_Quit();
}


int main(int argc, char* args[])
{
	if (!init())
	{
		printf("Failed to initialize!\n");
	}
	else
	{
		if (!loadMedia())
		{
			printf("Failed to load media!\n");
		}
		else
		{
			bool quit = false;
			SDL_Event e;

			while (!quit)
			{
				while (SDL_PollEvent(&e) != 0)
				{
					if (e.type == SDL_QUIT)
					{
						quit = true;
					}
				}
			}

			SDL_BlitSurface(gXout, NULL, gScreenSurface, NULL);

			SDL_UpdateWindowSurface(gWindow);

			close();
		}
	}


	return 0;
}