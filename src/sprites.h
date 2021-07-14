/*** includes ***/

#include <math.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

/*** custom types ***/

typedef struct Sprite {
	SDL_Texture *image;
	SDL_Rect crop;
	int width;
	int height;
} sprite;

/*** sprites functions ***/

int LoadImageForSprite(sprite *s, char *name, SDL_Renderer *renderer);

void SetSpriteCropping(sprite *s, int x, int y, int w, int h);

void DestroySprite(sprite *s);

void DrawSprite(sprite s, 
				int x, 
				int y, 
				int w, 
				int h, 
				int shift_x, 
				int shift_y, 
				SDL_Renderer *renderer);
