//DT Nesimi

class sprite
{
public: 
	~sprite();
	void updatesprite();
	void bouncesprite(int SCREEN_W, int SCREEN_H);
	void load_animated_sprite(int size, int effectType);
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

	int effect; // effect

	//scared
	ALLEGRO_COLOR color; //random color
	//spin
	float angle = 0; //angle for spin
	//baby
	float scale = 1.0; //start normal size
	int prevx, prevy; //for printing position of death
	bool alive = true; //scaling status
	//freeze
	int frozenX = 0, frozenY = 0; //for freezing
	int freezeTimer = 0; //time calculation

	ALLEGRO_BITMAP *image[32];
	ALLEGRO_BITMAP* death;

};