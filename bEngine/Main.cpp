#include "SDL.h"
#include "iostream"
#include "string"



	const int DISPLAY_WIDTH = 800;
	const int DISPLAY_HEIGHT = 600;

	//SDL_Texture* loadTexture(const std::string &fp, SDL_Renderer *ren)

	void Log_SDLError(std::ostream &stream, std::string msg) //originally an address reference (&msg). Possible problems.?
	{
			stream << msg << "SDL Error: " << SDL_GetError() << std::endl;
	}


	void SDL_RenderTexture(SDL_Texture *texture, SDL_Renderer *renderer, int x, int y)
	{
		SDL_Rect trr;
		trr.x = x;
		trr.y = y;

		SDL_QueryTexture(texture, NULL, NULL, &trr.w, &trr.h); 
		SDL_RenderCopy(renderer, texture, NULL, &trr);

	}
	
	SDL_Texture* SDL_LoadTexture(const std::string &fp, SDL_Renderer *r) //naming conflict?
	{
			SDL_Texture *tempT = nullptr;
			SDL_Surface *tempS = SDL_LoadBMP(fp.c_str()); //SDL_Surface *tempS = SDL_LoadBMP(fp.c_str());

			if(tempS == nullptr)
			{
				Log_SDLError(std::cout, "bEngineX - Failed to load a bitmap file");
			}
			else
			{
				tempT = SDL_CreateTextureFromSurface(r, tempS);
				SDL_FreeSurface(tempS);
				if(tempT == nullptr)
				{
					Log_SDLError(std::cout, "bEngine X - Failed to create a texture from a surface");
				}
			}
			return tempT; //hopefully it's not a null pointer. use if(SDL_LoadTexture(filepath, renderer) == nullptr) { error }
	}


	int main(int argc, char** argv)
	{
		std::cout << "bEngine X is Loading" << std::endl;
		

		if(SDL_Init(SDL_INIT_EVERYTHING) != 0)
		{
			Log_SDLError(std::cout, "bEngine X Critical Error - Could not initialize SDL components");
			return 1;
		}

		SDL_Window *bEngineDisplay = nullptr;
		bEngineDisplay = SDL_CreateWindow("bEngine X Demo", 100, 100, DISPLAY_WIDTH, DISPLAY_HEIGHT, SDL_WINDOW_SHOWN);
		if (bEngineDisplay == nullptr){ //if the Window was not created (null pointer was not assigned to a SDL Window object)
			Log_SDLError(std::cout, "bEngine X Critical Error - Could not create a window");
			return 1;
		}

		 SDL_Renderer *bEngineRenderer = nullptr;
		 bEngineRenderer = SDL_CreateRenderer(bEngineDisplay, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC); //window, video driver, hardware accelerated, sync with monitor refresh rate
		 if (bEngineRenderer == nullptr){ //if a renderer could not be created.
			Log_SDLError(std::cout, "bEngine X Critical Error - Could not create a SDL Renderer");
			return 1;
		}

		 /*
		 SDL_Surface *bgLogo = nullptr;
		 bgLogo = SDL_LoadBMP("logo.bmp");
		 if(bgLogo == nullptr)
		 {
			 Log_SDLError(std::cout, "bEngineX -  oul
				 d
			 return 1;
		 }

		 SDL_Texture *bgLogoTex = nullptr;
		 bgLogoTex = SDL_CreateTextureFromSurface(bEngineRenderer, bgLogo);
		 SDL_FreeSurface(bgLogo);

		 SDL_RenderClear(bEngineRenderer);
		 SDL_RenderCopy(bEngineRenderer, bgLogoTex, NULL, NULL);
		 SDL_RenderPresent(bEngineRenderer);
		 */

		 //BACKGROUND AND LOGO

		 SDL_Texture *background, *logo;

		 background = SDL_LoadTexture("background.bmp", bEngineRenderer);
		 logo = SDL_LoadTexture("logo.bmp", bEngineRenderer);

		 if(logo == nullptr || background == nullptr)
		 {
			 return 1;
			 Log_SDLError(std::cout, "bEngine X - Could not load background/logo");
		 }
    
		 SDL_RenderClear(bEngineRenderer);

		 int backgroundWidth, backgroundHeight;
		 SDL_QueryTexture(background, NULL, NULL, &backgroundWidth, &backgroundHeight);
		 SDL_RenderTexture(background, bEngineRenderer, 0, 0);
		 SDL_RenderTexture(background, bEngineRenderer, backgroundWidth, 0);
		 SDL_RenderTexture(background, bEngineRenderer, 0, backgroundHeight);
		 SDL_RenderTexture(background, bEngineRenderer, backgroundWidth, backgroundHeight);

		 int logoWidth, logoHeight;
		 SDL_QueryTexture(logo, NULL, NULL, &logoWidth, &logoHeight);
		 int xx = 0;
		 int yy = 0;
		 SDL_RenderTexture(logo, bEngineRenderer, xx, yy);

		 SDL_RenderPresent(bEngineRenderer);
		//Quit SDL
		SDL_Delay(5000);
		SDL_DestroyTexture(background);
		SDL_DestroyTexture(logo);
		SDL_DestroyRenderer(bEngineRenderer);
		SDL_DestroyWindow(bEngineDisplay);
		SDL_Quit();
    
		return 0;    
	}
