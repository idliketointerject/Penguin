// Base Class for on screen objects
#pragma once
#include "wrappers.h"


class object
{
public:
	// Constructors
	object();
	object(float x, float y, float speedX, float speedY, int dirX, int dirY, int boundX,
		int boundY, ALLEGRO_BITMAP *image, bool alive, bool collidable);
	
	// Other Functions
	void draw();
	virtual void update();

	// Getters/Setters
	float getX() {return x;}
	float getY() {return y;}
	float getSpeedX() {return speedX;}
	float getSpeedY() {return speedY;}
	int getDirX() {return dirX;}
	int getDirY() {return dirY;}
	int getBoundX() {return boundX;}
	int getBoundY() {return boundY;}
	ALLEGRO_BITMAP * getImage() {return image;}
	bool isAlive() {return alive;}
	bool isCollidable() {return collidable;}
	void setX(float x) {object::x = x;}
	void setY(float y) {object::y = y;}
	void setSpeedX(float speedX) {object::speedX = speedX;}
	void setSpeedY(float speedY) {object::speedY = speedY;}
	void setDirX(int dirX) {object::dirX = dirX;}
	void setDirY(int dirY) {object::dirY = dirY;}
	void setBoundX(int boundX) {object::boundX = boundX;}
	void setBoundY(int boundY) {object::boundY = boundY;}
	void setImage(ALLEGRO_BITMAP *image) {object::image = image;}
	void setAlive(bool alive) {object::alive = alive;}
	void setCollidable(bool collidable) {object::collidable = collidable;}
	
protected:
	float x;
	float y;
	float speedX;
	float speedY;
	int dirX;
	int dirY;
	int boundX;
	int boundY;
	ALLEGRO_BITMAP *image;
private:
	bool alive;
	bool collidable;
};