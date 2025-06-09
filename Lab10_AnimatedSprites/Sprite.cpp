#include <allegro5\allegro.h>
#include <allegro5\allegro_image.h>
#include <stdio.h>
#include "Sprite.h"

#include <iostream>
#include <random>
using namespace std;

void sprite::drawSprite()
{
	ALLEGRO_COLOR color = al_map_rgb(rand() % 255, rand() % 255, rand() % 255);
	int effect = rand() % 5;

	//spin
	if (effect == 0) {
		al_draw_rotated_bitmap(image[curframe], al_get_bitmap_width(image[curframe]) / 2, al_get_bitmap_height(image[curframe]) / 2, x, y, 3, 0);
	}
	//scared
	else if (effect == 1 && isCollision == true) {
		al_draw_tinted_bitmap(image[curframe], color, x, y, 0);
	}
	//baby
	else if (effect == 2) {
		al_draw_scaled_bitmap(image[curframe], 0, 0, al_get_bitmap_width(image[curframe]), al_get_bitmap_height(image[curframe]), x, y, al_get_bitmap_width(image[curframe]) / 2, al_get_bitmap_height(image[curframe]) / 2, 0);
	}
	//freeze
	else if (effect == 3) {
		al_draw_bitmap(image[curframe], x, y, 0);
	}
	else {
		al_draw_bitmap(image[curframe], x, y, 0);
	}
}

void sprite::collision(sprite sprites[], int size, int me, int WIDTH, int HEIGHT) {
	for (int i = 0; i < size; i++) {

		if (i != me) {

			if (x >= sprites[i].getX() - width && x <= sprites[i].getX() + width) {

				if (y >= sprites[i].getY() - height && y <= sprites[i].getY() + height) {
					x = rand() % WIDTH;
					y = rand() % HEIGHT;
				}
			}
		}
	}
}

void sprite::updatesprite()
{
	//update x position
	if (++xcount > xdelay)
	{
		xcount = 0;
		x += xspeed;
	}

	//update y position
	if (++ycount > ydelay)
	{
		ycount = 0;
		y += yspeed;
	}


	if (framecount++ > framedelay)
	{
		framecount = 0;
		curframe++;
		if (curframe >= maxframe)
			curframe = 0;
	}
}

void sprite::bouncesprite(int SCREEN_W, int SCREEN_H)
{
	//simple screen bouncing behavior
	if (x < 0)
	{
		x = 0;
		xspeed = rand() % 2 + 4;
		animdir *= -1;
	}

	else if (x > SCREEN_W - width)
	{
		x = SCREEN_W - width;
		xspeed = rand() % 2 - 6;
		animdir *= -1;
	}

	if (y < 0)
	{
		y = 0;
		yspeed = rand() % 2 + 4;
		animdir *= -1;
	}

	else if (y > SCREEN_H - height)
	{
		y = SCREEN_H -  height;
		yspeed = rand() % 2 - 6;
		animdir *= -1;
	}

}

void sprite::load_animated_sprite(int size)
{
	//load the animated sprite
	char s[80];
	maxframe=size;
	for (int n=0; n<size; n++)
	{
		sprintf_s(s,"cirno_%d.png",n);
		image[n] = al_load_bitmap(s);

		//al_convert_mask_to_alpha(image[n], al_map_rgb(255, 255, 255));
	}  
	width=al_get_bitmap_width(image[0]);
	height=al_get_bitmap_height(image[0]);
	curframe = 0;
	framedelay = 2;
	framecount = 0;
}

sprite::~sprite()
{
	for(int i = 0; i < maxframe; i++)
		al_destroy_bitmap(image[i]);
}



