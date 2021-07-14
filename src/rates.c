/*** includes ***/

#include <stdio.h>
#include "rates.h"

/*** defines ***/

#define PLAYER_SUM 1000
#define MACHINE_SUM 5000

/*** rates data ***/

static unsigned int rate = 0;

static unsigned int machine_sum = MACHINE_SUM;

static unsigned int player_sum = PLAYER_SUM;

/*** rates functions ***/

void DrawText(char *text, 
              TTF_Font *font, 
              int x, 
              int y, 
              SDL_Renderer *renderer) {
	
	SDL_Color foregroundColor = { 255, 255, 255 };
	SDL_Color backgroundColor = { 0, 0, 0 };

	SDL_Surface* surface = TTF_RenderText_Shaded(font, 
	                                             text, 
	                                             foregroundColor, 
	                                             backgroundColor);
	
	SDL_Rect textLocation = { x, y, 0, 0 };
	
	TTF_SizeText(font, text, &textLocation.w, &textLocation.h);
	
	SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, 
	                                                    surface);

	SDL_FreeSurface(surface);

	SDL_RenderCopy(renderer, texture, NULL, &textLocation);
	
}

void DrawRates(TTF_Font *font, int x, int y, SDL_Renderer *renderer) {
	
	char *result_text = (char*)malloc(32 * sizeof(char));;
	
	sprintf(result_text, "rates: %d$", rate);
	
	DrawText(result_text, font, x, y, renderer);
	
}

void DrawPlayerSum(TTF_Font *font,
                   int x,
                   int y, 
                   SDL_Renderer *renderer) {
	
	char *result_text = (char*)malloc(32 * sizeof(char));;
	
	sprintf(result_text, "player: %d$", player_sum);
	
	DrawText(result_text, font, x, y, renderer);
	
}

void DrawMachineSum(TTF_Font *font, 
                    int x, 
                    int y, 
                    SDL_Renderer *renderer) {
	
	char *result_text = (char*)malloc(32 * sizeof(char));;
	
	sprintf(result_text, "machine: %d$", machine_sum);
	
	DrawText(result_text, font, x, y, renderer);
	
}

void AddRates(int value) {
	
	if (player_sum) {
		rate += value;
		player_sum -= value;
	}
}

void GiveSum(int value) {
	
	if (value > machine_sum) {
		player_sum += machine_sum + rate;
		machine_sum = 0;
	} else {
		player_sum += rate + value;
		machine_sum -= value;
	}
	
	rate = 0;
}

void CalculateRates(int bar1, int bar2, int bar3){
	
	if (bar1 == bar2 && bar2 == bar3)
		GiveSum(3 * rate);
	
	machine_sum += rate;
	rate = 0;
}

int IsRateMade(){
	return rate > 0;
}
