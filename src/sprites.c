/*** includes ***/

#include "sprites.h"

/*** sprites functions ***/

int LoadImageForSprite(sprite *s, char *name, SDL_Renderer *renderer) {
	
	SDL_Surface *surface;
	
	surface = IMG_Load(name);
	
	if(surface == NULL)
		return 1;
		
	s->width = surface->w;
	s->height = surface->h;
	
	s->image = SDL_CreateTextureFromSurface(renderer, surface);
	
	if (s->image == NULL)
		return 1;
	
	SDL_FreeSurface(surface);
	
	return 0;
	
};

void SetSpriteCropping(sprite *s, int x, int y, int w, int h) {
	
	s->crop.x = x;
	s->crop.y = y;
	s->crop.w = w;
	s->crop.h = h;
	
}

void DestroySprite(sprite *s) {
	
	SDL_DestroyTexture(s->image);
	
}

void DrawSprite(sprite s, 
				int x, 
				int y, 
				int w, 
				int h, 
				int shift_x, 
				int shift_y, 
				SDL_Renderer *renderer) {
					
	SDL_Rect rect;
	SDL_Rect crop;
	
	SDL_Rect second_rect;
	SDL_Rect second_crop;
	
	rect.x = x;
	rect.y = y;
	rect.w = w;
	rect.h = h;
	
	crop.x = s.crop.x + shift_x;
	crop.y = s.crop.y + shift_y;
	crop.w = s.crop.w;
	crop.h = s.crop.h;
	
	if (crop.y < -s.crop.h) {
		
		crop.y = s.height - (abs(crop.y) % s.height);
		
	} else if (crop.y > s.height + s.crop.h) {
		
		crop.y = crop.y % s.height;
		
	}
	
	int second_image = 0;
	
	if (crop.y < 0) {
		
		float rect_dec = (float)rect.h / (float)crop.h;
		
		rect.y -= (int)(crop.y*rect_dec);
		crop.h += crop.y;
		rect.h += (int)(crop.y*rect_dec);
		crop.y = 0;
		
		second_image = 1;
		
		second_crop.x = s.crop.x;
		second_crop.y = s.height - (s.crop.h - crop.h);
		second_crop.w = s.crop.w;
		second_crop.h = s.crop.h - crop.h;
		
		second_rect.x = x;
		second_rect.y = y;
		second_rect.w = w;
		second_rect.h = h - rect.h;
		
	} else if (crop.y > s.height - crop.h) {
		
		float rect_dec = (float)rect.h / (float)crop.h;
		
		crop.h -= crop.y - (s.height - s.crop.h);
		rect.h -= (int)(rect_dec*(crop.y - (s.height - s.crop.h)));
		
		second_image = 1;
		
		second_crop.x = s.crop.x;
		second_crop.y = 0;
		second_crop.w = s.crop.w;
		second_crop.h = s.crop.h - crop.h;
		
		second_rect.x = x;
		second_rect.y = y + rect.h;
		second_rect.w = w;
		second_rect.h = h - rect.h;
		
	}
	
	if (second_image)
		SDL_RenderCopy(renderer, s.image, &second_crop, &second_rect);
		
	SDL_RenderCopy(renderer, s.image, &crop, &rect);
	
};
