// Base Class for on screen objects
#pragma once
#include "wrappers.h"


class object
{
public:
	// Constructors
	object();
	object(float x, float y, float speedX, float speedY, int dirX, int dirY, int boundX,
		int boundY, char * bitmapPath, bool alive, bool collidable);
	object(char * bitmapPath);
	
	// Other Functions
	void draw();
	virtual void update();
	virtual void collision(); // what to do when a collision occurs
	void drawScaled();
	void drawYScaled();

	bool checkCollision(object &obj);

	void setValuesFromBitmap();
	void initAllToZero();

	// Getters/Setters
	float getX() {return x;}
	float getY() {return y;}
	float getSpeedX() {return speedX;}
	float getSpeedY() {return speedY;}
	int getDirX() {return dirX;}
	int getDirY() {return dirY;}
	int getBoundX() {return boundX;}
	int getBoundY() {return boundY;}
	ALLEGRO_BITMAP * getImage() {return wBitmap.getBitmapPointer();}
	bool isAlive() {return alive;}
	bool isCollidable() {return collidable;}
	bool setImage(char *path);
	void setX(float x) {object::x = x;}
	void setY(float y) {object::y = y;}
	void setSpeedX(float speedX) {object::speedX = speedX;}
	void setSpeedY(float speedY) {object::speedY = speedY;}
	void setDirX(int dirX) {object::dirX = dirX;}
	void setDirY(int dirY) {object::dirY = dirY;}
	void setSpeed(double speed) {object::speed = speed;}
	void setAngle(double angle) {object::angle = angle;}
	void setBoundX(int boundX) {object::boundX = boundX;}
	void setBoundY(int boundY) {object::boundY = boundY;}
	void setAlive(bool alive) {object::alive = alive;}
	void setCollidable(bool collidable) {object::collidable = collidable;}
	int getBitmapWidth(){return bitmapWidth;}
	int getBitmapHeight(){return bitmapHeight;}
	bool verifyBitmap() {return wBitmap.verifyInitialization();}
	//for testing
	void drawBoundingBox();
	//

protected:
	int bitmapWidth;
	int bitmapHeight;
	float x;
	float y;
	float speedX;
	float speedY;
	int dirX;
	int dirY;
	double speed;
	double angle;
	int boundX;
	int boundY;
	bitmapWrapper wBitmap;
private:
	bool alive;
	bool collidable;
};