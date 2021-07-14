/*** includes ***/

#include <time.h>
#include "sprites.h"
#include "rates.h"

/*** defines ***/

#define WINDOW_TITLE "Simple Slot Machine"
#define WINDOW_WIDTH 458
#define WINDOW_HEIGHT 204
#define LOSS 2; // make it higher to make less probability of success

#ifdef _WIN64

#define SPRITES_SRC "res\\images\\"

#define FONTS_SRC "res\\fonts\\"

#else

#define SPRITES_SRC "res/images/"

#define FONTS_SRC "res/fonts/"

#endif

int main(int argc, char *argv[]) {
	
	/*** initialization ***/
	
	srand(time(NULL));
	
	if (SDL_Init(SDL_INIT_VIDEO |  SDL_INIT_TIMER )) {
		
		SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
		
		return 1;
		
	};
	
	TTF_Init();
	
	SDL_Window *window;
	
	window = SDL_CreateWindow(
		WINDOW_TITLE,
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		WINDOW_WIDTH,
		WINDOW_HEIGHT,
		SDL_WINDOW_RESIZABLE
	);
	
	SDL_SetWindowResizable(window, 0);
	
	if (window == NULL) {
		
		SDL_Log("Unable to create window: %s", SDL_GetError());
		
		return 1;
		
	}
	
	SDL_Surface *surface; 
	
	surface = IMG_Load(SPRITES_SRC "icon.png");
 
	SDL_SetWindowIcon(window, surface);
	
	SDL_FreeSurface(surface);
	
	SDL_Renderer *renderer;
	
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	
	if (renderer == NULL) {
		
		SDL_Log("Unable to create renderer: %s", SDL_GetError());
		SDL_DestroyWindow(window);
		
		return 1;
		
	}
	
	/*** load resources ***/
	
	sprite bar;
	
	LoadImageForSprite(&bar, SPRITES_SRC "bar.png", renderer);
	SetSpriteCropping(&bar, 0, 0, 60, 60);	
	
	sprite background;
	
	LoadImageForSprite(&background, SPRITES_SRC "SMFrame_blank.png", renderer);
	SetSpriteCropping(&background, 0, 0, 229, 102);
	
	sprite spin;
	
	LoadImageForSprite(&spin, SPRITES_SRC "spin.png", renderer);
	SetSpriteCropping(&spin, 0, 0, 32, 20);
	
	sprite bet;
	
	LoadImageForSprite(&bet, SPRITES_SRC "bet.png", renderer);
	SetSpriteCropping(&bet, 0, 0, 32, 20);
	
	TTF_Font* font = TTF_OpenFont(FONTS_SRC "8bit.ttf", 10);
	
	/*** main loop ***/
	
	SDL_Event event;
	
	int close_signal = 0;
	
	int spin_signal = 0;
	
	int shift_spin = 0;
	
	int shift_bet = 0;
	
	int dtime;
	
	int bar1_y = (rand() % 11) * bar.crop.h;
	int bar2_y = (rand() % 11) * bar.crop.h;
	int bar3_y = (rand() % 11) * bar.crop.h;
	
	int bar1_fy;
	int bar2_fy;
	int bar3_fy;
	
	int success;
	
	int stop1 = rand() % 1000;
	int stop2 = rand() % 1000;
	int stop3 = rand() % 1000;
	int stop4 = rand() % 1000;
	int stop5 = rand() % 1000;
	int stop6 = rand() % 1000;
	int stop7 = rand() % 1000;
	int stop8 = rand() % 1000;
	int stop9 = rand() % 1000;
	
	int bar1_dy = 0;
	int bar2_dy = 0;
	int bar3_dy = 0;
	
	unsigned int last_time = 0;
	
	while (!close_signal) {
		
		SDL_RenderClear(renderer);
		
		DrawSprite(background, 0, 0, 458, 204, 0, 0, renderer);
		
		DrawSprite(bar, 11, 11, 138, 138, 0, bar1_y, renderer);
		
		DrawSprite(bar, 161, 11, 138, 138, 0, bar2_y, renderer);
		
		DrawSprite(bar, 309, 11, 138, 138, 0, bar3_y, renderer);
		
		DrawSprite(spin, 231, 156, 64, 40, 0, shift_spin, renderer);
		
		DrawSprite(bet, 163, 156, 64, 40, 0, shift_bet, renderer);
		
		DrawRates(font, 10, 170, renderer);
		
		DrawPlayerSum(font, 10, 190, renderer);
		
		DrawMachineSum(font, 310, 170, renderer);
		
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
				
				case SDL_QUIT:
					close_signal = 1;
					break;
					
				case SDL_MOUSEBUTTONDOWN: {
					
				    int mx;
				    int my;
				    SDL_GetMouseState(&mx, &my);
				    
				    int check_mx_spin = (mx > 231) && (mx < 295); 
				    int check_my_spin = (my > 156) && (my < 196);
				    
				    int check_mx_bet = (mx > 163) && (mx < 227); 
				    int check_my_bet = (my > 156) && (my < 196);
				    
				    int check_spin = check_mx_spin && check_my_spin;
				    
				    int check_bet = check_mx_bet && check_my_bet;
				    
					if (check_spin && IsRateMade()) {
						
						spin_signal = 1;
						shift_spin = 20;
						
					} else if (check_bet && !spin_signal) {
						
						shift_bet = 20;
						AddRates(10);
						
					}
					
					break;
				}
				
				case SDL_MOUSEBUTTONUP:
					if (spin_signal == 1)
						shift_spin = 0;
					if(shift_bet)
						shift_bet = 0;
					break;
					
			}
		}
		
		if (spin_signal && !last_time) {
			
			last_time = SDL_GetTicks();
			
			bar1_dy = 10;
			bar2_dy = 10;
			bar3_dy = 10;
			
			stop1 = rand() % 1000;
			stop2 = rand() % 1000;
			stop3 = rand() % 1000;
			stop4 = rand() % 1000;
			stop5 = rand() % 1000;
			stop6 = rand() % 1000;
			stop7 = rand() % 1000;
			stop8 = rand() % 1000;
			stop9 = rand() % 1000;
			
			success = rand() % LOSS;
			
			bar1_fy = (rand() % 11) * bar.crop.h;
			if (!bar1_fy)
				bar1_fy = bar.height;
				
			bar2_fy = (rand() % 11) * bar.crop.h;
			if (!bar2_fy)
				bar2_fy = bar.height;
			if (!success)
				bar2_fy = bar1_fy;
				
			bar3_fy = (rand() % 11) * bar.crop.h;
			if (!bar3_fy)
				bar3_fy = bar.height;
			if (!success)
				bar3_fy = bar2_fy;
				
		}
		
		int bar3_mod = bar.height - abs(bar3_y) % bar.height;
		
		int bar2_mod = bar.height - abs(bar2_y) % bar.height;
		
		int bar1_mod = bar.height - abs(bar1_y) % bar.height;
		
		int bar3_check = bar3_mod != bar3_fy;
		
		int bar2_check = bar3_check || bar2_mod != bar2_fy;
		
		int bar1_check = bar2_check || bar1_mod != bar1_fy;
						 
		int dtime = SDL_GetTicks() - last_time;
		
		int is_time_up = dtime < 10000;
		
		int all_bars_stoped = bar3_check || bar2_check || bar1_check;
		
		int should_continue = all_bars_stoped || is_time_up;
		
		if (last_time && should_continue) {
			
			if (dtime > 2000 + stop1)
				bar3_dy = 5;
			
			if (dtime > 3000 + stop2)
				bar3_dy = 3;
			
			if (dtime > 4000 + stop3)
				bar3_dy = 1;
			
			if (dtime > 5000 + stop4)
				bar2_dy = 5;
			
			if (dtime > 6000 + stop5)
				bar2_dy = 3;
			
			if (dtime > 7000 + stop6)
				bar2_dy = 1;
			
			if (dtime > 8000 + stop7)
				bar1_dy = 5;
			
			if (dtime > 9000 + stop8)
				bar1_dy = 3;
			 
			if(dtime > 10000){
				
				bar3_dy = bar3_check;
				bar2_dy = bar2_check;
				bar1_dy = bar1_check;
				
			}
			
			bar1_y -= bar1_dy;
			bar2_y -= bar2_dy;
			bar3_y -= bar3_dy;
			
		} else if (spin_signal) {
			
			spin_signal = 0;
			
			last_time = 0;
			
			bar1_y = bar1_mod;
			bar2_y = bar2_mod;
			bar3_y = bar3_mod;
			
			CalculateRates(bar1_y, bar2_y, bar3_y);
			
		}
				
		SDL_RenderPresent(renderer);
		
		SDL_Delay(1000 / 60);
		
	}
	
	/*** freeing memory and quit ***/
	
	TTF_CloseFont(font);
	
	DestroySprite(&bet);
	DestroySprite(&spin);
	DestroySprite(&bar);
	DestroySprite(&background);
	
	
	SDL_DestroyRenderer(renderer);
	
	SDL_DestroyWindow(window);
	
	TTF_Quit();
	
	SDL_Quit();
	
	return 0;
}

#ifdef _WIN64

int WinMain(int argc, char *argv[]){
	main(argc, argv);
	return 0;
}

#endif
