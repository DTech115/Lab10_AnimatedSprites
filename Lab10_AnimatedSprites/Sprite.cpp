#include <allegro5\allegro.h>
#include <allegro5\allegro_image.h>
#include <stdio.h>
#include "Sprite.h"

#include <iostream>
#include <random>
using namespace std;

void sprite::drawSprite()
{

	//spin
	if (effect == 0) {
		angle += 0.1;
		al_draw_rotated_bitmap(image[curframe], width / 2, height / 2, x + (width / 2), y + (height / 2), angle, 0);
	}
	//scared
	else if (effect == 1) {

		al_draw_tinted_bitmap(image[curframe], color, x, y, 0);
	}
	//baby
	else if (effect == 2) {
		
		//check if too smol, dead
		if (alive) {
			al_draw_scaled_bitmap(image[curframe], 0, 0, width, height, x, y, width * scale, height * scale, 0);
			prevx = x;
			prevy = y;
		}
		else {
			al_draw_bitmap(death, prevx, prevy, 0);
		}
	}
	//freeze
	else if (effect == 3) {
		if (freezeTimer > 0) {
			al_draw_tinted_bitmap(image[curframe], al_map_rgb(120, 220, 255), x, y, 0); //makes it blue if frozen :D
		}
		else {
			al_draw_bitmap(image[curframe], x, y, 0);
		}
	}
	/*else {
		al_draw_bitmap(image[curframe], x, y, 0);
	}*/
}

// function to check if sprites collide
void sprite::collision(sprite sprites[], int size, int me, int WIDTH, int HEIGHT) {
	for (int i = 0; i < size; i++) {


		if (i != me) {

			//if dead or frozen, ignore!
			if (!alive || freezeTimer > 0)
			{
				return;
			}

			if (x >= sprites[i].getX() - width && x <= sprites[i].getX() + width) {

				if (y >= sprites[i].getY() - height && y <= sprites[i].getY() + height) {
					x = rand() % WIDTH;
					y = rand() % HEIGHT;

					//scared
					if (effect == 1) {
						color = al_map_rgb(rand() % 255, rand() % 255, rand() % 255);
					}
					//baby
					if (effect == 2) {
						scale *= 0.9;
						if (scale <= 0.05) {
							alive = false;
						}
					}
					//freeze
					if (effect == 3) {
						freezeTimer = 300;
						frozenX = x;
						frozenY = y;
					}

				}
			}
		}
	}
}

void sprite::updatesprite()
{
	//check if sprite is alive [if it's the scaling kind]
	if (!alive) {
		return;
	}
	//check if needs to be frozen
	if (freezeTimer > 0) {
		x = frozenX;
		y = frozenY;
		freezeTimer--;
		return;
	}

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

//turned into a pseudo constructor
//added effect number too
void sprite::load_animated_sprite(int size, int effectType)
{

	//effect = rand() % 5; //applies random effect
	effect = effectType;
	

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

	death = al_load_bitmap("ice.png");
}

sprite::~sprite()
{
	for(int i = 0; i < maxframe; i++)
		al_destroy_bitmap(image[i]);
	al_destroy_bitmap(death);
}



