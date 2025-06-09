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
	
	//bool isCollision; //collision check
	ALLEGRO_COLOR color; //random color
	float angle = 0; //angle for spin

	ALLEGRO_BITMAP *image[32];
};