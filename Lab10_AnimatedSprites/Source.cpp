//DT Nesimi

#include <allegro5\allegro.h>
#include <allegro5\allegro_image.h>
#include "Sprite.h"
#include <iostream>
using namespace std;

int main(void)
{
	//variables
	int width = 800;
	int height = 600;
	bool done = false;

	bool redraw = true;
	const int FPS = 60;
	int numSprites = 5; //variable for easier editing

	//allegro variable
	ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;
	sprite cirno[5];
	ALLEGRO_TIMER *timer = NULL;


	//program init
	if(!al_init())										//initialize Allegro
		return -1;

	display = al_create_display(width, height);			//create our display object

	if(!display)										//test display object
		return -1;

	//addon init
	al_install_keyboard();
	al_init_image_addon();
	timer = al_create_timer(1.0 / FPS);

	event_queue = al_create_event_queue();
	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_set_target_bitmap(al_get_backbuffer(display));
	al_start_timer(timer);

	for (int i = 0; i < numSprites; i++) {
		cirno[i].load_animated_sprite(32, i);
	}

	while(!done)
	{
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);

		if(ev.type == ALLEGRO_EVENT_TIMER)
		{
			for (int i = 0; i < numSprites; i++) {
				cirno[i].bouncesprite(width, height);
			}
			for (int i = 0; i < numSprites; i++) {
				cirno[i].collision(cirno, numSprites, i, width, height);
			}

			redraw = true;
		}
		else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
		{
			done = true;

		}
		else if(ev.type == ALLEGRO_EVENT_KEY_DOWN)
		{
			switch(ev.keyboard.keycode)
			{
			case ALLEGRO_KEY_ESCAPE:
				done = true;
				break;
			}
		}
		else if(ev.type == ALLEGRO_EVENT_KEY_UP)
		{
			switch(ev.keyboard.keycode)
			{
			case ALLEGRO_KEY_ESCAPE:
				done = true;
				break;
			}
		}

		if(redraw && al_is_event_queue_empty(event_queue))
		{


			redraw = false; 
			for (int i = 0; i < numSprites; i++) {
				cirno[i].updatesprite();
			}
			for (int i = 0; i < numSprites; i++) {
				cirno[i].drawSprite();
			}
			al_flip_display();
			al_clear_to_color(al_map_rgb(0,0,0));
		}
	}


	al_destroy_event_queue(event_queue);
	al_destroy_display(display);						//destroy our display object

	return 0;
}


