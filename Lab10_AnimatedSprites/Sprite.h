class sprite
{
public: 
	~sprite();
	void updatesprite();
	void bouncesprite(int SCREEN_W, int SCREEN_H);
	void load_animated_sprite(int size);
	void drawSprite();
	int getX(){return x;}
	int getY(){return y;}
	void collision(sprite sprites[], int size, int me, int WIDTH, int HEIGHT);

private:
	int x,y;
	int width,height;
	int xspeed,yspeed;
	int xdelay,ydelay;
	int xcount,ycount;
	int curframe,maxframe,animdir;
	int framecount,framedelay;

	int effect; // random effect

	//scared
	ALLEGRO_COLOR color; //random color
	//spin
	float angle; //angle for spin
	//baby
	float scale; //start size
	int prevx, prevy; //for printing position of death
	bool alive; //scaling status

	ALLEGRO_BITMAP *image[32];
	ALLEGRO_BITMAP* death;

};