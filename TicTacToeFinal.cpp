#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
using namespace std;
void logSDLError(std::ostream& os, const std::string &msg, bool fatal = false);
void refreshScreen(SDL_Window* window, SDL_Renderer* renderer,
    const SDL_Rect& filled_rect, const bool leftMouse);
void logSDLError(std::ostream& os, const std::string &msg, bool fatal) {
    os << msg << " Error: " << SDL_GetError() << std::endl;
    if (fatal) {
        SDL_Quit();
        exit(1);
    }

}
const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;
const string WINDOW_TITLE = "Mega Tic Tac Toe";

const int BUTTON_WIDTH = 45;
const int BUTTON_HEIGHT = 45;
const int TOTAL_BUTTONS = 100;

class LButton
{
	public:
		//Initializes internal variables
		LButton();

		//Sets top left position
		void setPosition( int x, int y );

		void drawButton( SDL_Renderer* renderer);

		//Shows button sprite
		void render();

		int xo = 0;
		int *p = &xo;
		//Top left position
		SDL_Point mPosition;


};
LButton::LButton()
{
	mPosition.x = 0;
	mPosition.y = 0;
}

void LButton::setPosition( int x, int y )
{
	mPosition.x = x;
	mPosition.y = y;
}
void LButton::drawButton(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
    SDL_Rect filled_rect;
    filled_rect.x = LButton::mPosition.x;
    filled_rect.y = LButton::mPosition.y;
    filled_rect.w = BUTTON_WIDTH;
    filled_rect.h = BUTTON_HEIGHT;
    SDL_RenderFillRect(renderer, &filled_rect);
}

bool checkInorOut(class LButton buttons, int x, int y, int z, int t)
{
		//Mouse is left of the button
		if( x < buttons.mPosition.x )
		{
			return false;
		}
		//Mouse is right of the button
		else if( x > buttons.mPosition.x + z )
		{
			return false;
		}
		//Mouse above the button
		else if( y < buttons.mPosition.y )
		{
			return false;
		}
		//Mouse below the button
		else if( y > buttons.mPosition.y + t )
		{
			return false;
		}
		else return true;
		//Mouse is inside button

}
void drawxo (LButton buttons, int* p, int xo, SDL_Renderer* renderer ) {
    if(xo == 1) {
                SDL_Surface * image = IMG_Load("x.png");
                SDL_Rect dstrect = {buttons.mPosition.x, buttons.mPosition.y, BUTTON_WIDTH, BUTTON_HEIGHT};
                SDL_Texture * texture = SDL_CreateTextureFromSurface(renderer, image);
                SDL_RenderCopy(renderer, texture, NULL, &dstrect);
                SDL_RenderPresent(renderer);
                *p = 1;
            }
            else {
                SDL_Surface * image = IMG_Load("o.png");
                SDL_Rect dstrect = {buttons.mPosition.x, buttons.mPosition.y, BUTTON_WIDTH, BUTTON_HEIGHT};
                SDL_Texture * texture = SDL_CreateTextureFromSurface(renderer, image);
                SDL_RenderCopy(renderer, texture, NULL, &dstrect);
                SDL_RenderPresent(renderer);
                *p = 2;
            }


}
bool checkWin1(LButton buttons[], int j) {
    int i, countwin = 0;
    for (i=j; i < 100; i+=11) {
          if(buttons[i].xo != buttons[j].xo) {
                for (i=j-11; i >= 0; i-=11) {
                    if(buttons[i].xo != buttons[j].xo) return false;
                    else {
                        countwin++;
                        if (countwin >= 5) return true;
                    }
                }
                return false;
          }
          else {
            countwin++;
            if (countwin >= 5) return true;
          }
    }
    return false;
}
bool checkWin2(LButton buttons[], int j) {
    int i, countwin = 0;
    for(i=j; i < 100; i+=1) {
          if(buttons[i].xo != buttons[j].xo) {
                 for(i=j-1; i >= 0; i-=1) {
                    if(buttons[i].xo != buttons[j].xo) return false;
                    else {
                        countwin++;
                        if (countwin >= 5) return true;
                    }
                }
                return false;
          }
          else {
            countwin++;
            if (countwin >= 5) return true;
          }
    }
    return false;
}
bool checkWin3(LButton buttons[], int j) {
    int i, countwin = 0;
    for(i=j; i < 100; i+=9) {
          if(buttons[i].xo != buttons[j].xo) {
                for(i=j-9; i >= 0; i-=9) {
                    if(buttons[i].xo != buttons[j].xo) return false;
                    else {
                        countwin++;
                        if (countwin >= 5) return true;
                    }
                }
                return false;
          }
          else {
            countwin++;
            if (countwin >= 5) return true;
          }
    }
    return false;
}
bool checkWin4(LButton buttons[], int j) {
    int i, countwin = 0;
    for(i=j; i < 100; i+=10) {
          if(buttons[i].xo != buttons[j].xo) {
               for(i=j-10; i > 0; i-=10)  {
                    if(buttons[i].xo != buttons[j].xo) return false;
                    else {
                        countwin++;
                        if (countwin >= 5) return true;
                }
            }
          return false;
        }
        else {
                countwin++;
                if (countwin >= 5) return true;
              }
    } return false;
}
bool checkWin(LButton buttons[], int i) {
    if(checkWin1(buttons, i) == false) {
        if(checkWin2(buttons, i) == false) {
            if(checkWin3(buttons, i) == false) {
                if(checkWin4(buttons, i)== true) return true;
                else return false;
            } else return true;
        } else return true;
    } else return true;
}
void quitSDL(SDL_Window* window, SDL_Renderer* renderer) {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
void initSDL(SDL_Window* &window, SDL_Renderer* &renderer) {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)

        logSDLError(std::cout, "SDL_Init", true);
        window = SDL_CreateWindow(WINDOW_TITLE.c_str(), SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (window == nullptr) logSDLError(std::cout, "CreateWindow", true);
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED |
        SDL_RENDERER_PRESENTVSYNC);

        if (renderer == nullptr) logSDLError(std::cout, "CreateRenderer", true);
        int imgFlags = IMG_INIT_PNG;

        SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
        SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);

}
int main(int argc, char* argv[]) {
    SDL_Window* window;
    SDL_Renderer* renderer;
    initSDL(window, renderer);
    SDL_Event e;
    SDL_RenderClear(renderer);
    SDL_Surface * image = IMG_Load("background.jpg");
    SDL_Texture * texture = SDL_CreateTextureFromSurface(renderer, image);
    SDL_RenderCopy(renderer, texture, NULL, NULL);
    int i, j;
    int xo=1;
    int gameStatus = 0;
    class LButton buttons[100];
    for(j = 9; j >= 0; j--) {
        for (i=0; i < 10; i++) {
            buttons[j*10+i].setPosition( i*50+370, 570-j*50 );
            buttons[j*10+i].drawButton(renderer);
        }
    }
    SDL_RenderPresent(renderer);
    while (gameStatus == 0) {
        SDL_Delay(10);

        if ( SDL_WaitEvent(&e) == 0) continue;

        if ((e.type == SDL_QUIT) || (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE)) break;

        if (e.type == SDL_MOUSEBUTTONDOWN) {
            if (e.button.button == SDL_BUTTON_LEFT) {
                for(i = 0; i < 100; i++) {
                    if(checkInorOut(buttons[i], e.button.x, e.button.y, BUTTON_WIDTH, BUTTON_HEIGHT)== true) {
                        if(buttons[i].xo == 0) {
                            drawxo(buttons[i], buttons[i].p, xo, renderer);
                            if(checkWin(buttons, i) == true) {
                                if(xo == 1) {
                                    SDL_Surface * xwon = IMG_Load("xwon.png");
                                    SDL_Texture * texture = SDL_CreateTextureFromSurface(renderer, xwon);
                                    SDL_Rect dstrect = {-30, -350, 1280, 720};
                                    SDL_RenderCopy(renderer, texture, NULL, &dstrect);
                                    SDL_RenderPresent(renderer);
                                }
                                else {
                                    SDL_Surface * owon = IMG_Load("owon.png");
                                    SDL_Texture * texture = SDL_CreateTextureFromSurface(renderer, owon);
                                    SDL_Rect dstrect = {-30, -350, 1280, 720};
                                    SDL_RenderCopy(renderer, texture, NULL, &dstrect);
                                    SDL_RenderPresent(renderer);
                                }
                                gameStatus = 1;
                                while(true) {
                                    SDL_Delay(10);
                                    if ( SDL_WaitEvent(&e) == 0) continue;
                                    if ((e.type == SDL_QUIT) || (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE)) break;
                                }
                            }
                            else {
                                if(xo == 1) xo = 2;
                                else xo = 1;
                            }
                        }
                        break;
                    }
                }
            }
        }
    }
    IMG_Quit();
    quitSDL(window, renderer);
    return 0;
}
