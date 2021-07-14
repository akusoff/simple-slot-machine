/*** includes ***/

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

/*** rates functions ***/

void DrawRates(TTF_Font *font, int x, int y, SDL_Renderer *renderer);

void DrawPlayerSum(TTF_Font *font,
                   int x,
                   int y, 
                   SDL_Renderer *renderer);

void DrawMachineSum(TTF_Font *font, 
                    int x, 
                    int y, 
                    SDL_Renderer *renderer);

void AddRates(int value);

void CalculateRates(int bar1, int bar2, int bar3);

int IsRateMade();
