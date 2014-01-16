#ifndef __BALL_H__
#define __BALL_H__

#include <GD2.h>
#include "Input.h"
#include "Common.h"
#include "pinball.h"

class Ball
{
private:
	int x,y,z;
	int dx,dy,dz;
	int ddx,ddy,ddz;
	int r;

public:
	Ball(int x, int y);
	void draw();
	void update(Input i);
	bool isTouchingEdges();
	int getX();
	int getY();
};



Ball::Ball(int x, int y)
{
	this->x = x;
	this->y = y;
	this->z = 0;
	this->dx = 0;
	this->dy = 0;
	this->dz = 0;
	this->ddx = 0;
	this->ddy = 0;
	this->ddz = 0;
	this->r = 30;
}

void Ball::draw()
{
	GD.Begin(BITMAPS);
	GD.Vertex2ii((this->x - PINBALL_HEIGHT*8)/16,(this->y - PINBALL_HEIGHT*8)/16,PINBALL_HANDLE);

}

bool Ball::isTouchingEdges()
{
	return (this->x + 8*PINBALL_WIDTH >= SCREEN_WIDTH || this->x - 8*PINBALL_WIDTH <= 0 || this->y + 8*PINBALL_HEIGHT >= SCREEN_HEIGHT || this->y - 8*PINBALL_HEIGHT <= 0);
}

int Ball::getX()
{
	return this->x;
}

int Ball::getY()
{
	return this->y;
}

void Ball::update(Input i)
{
	//this->ddx = i.getAccelerationX();
	//this->ddy = i.getAccelerationY();

	if (!this->isTouchingEdges())
	{
		this->dx += i.getAccelerationX()/10;
		this->dy += i.getAccelerationY()/10;
	}

	if (this->x + 8*PINBALL_WIDTH >= SCREEN_WIDTH)
	{
		this->dx = -this->dx/3;
		this->x = SCREEN_WIDTH-8*PINBALL_WIDTH-1;

	}
	else if (this->x - 8*PINBALL_WIDTH<= 0)
	{
		this->dx = -this->dx/3;
		this->x = 1+8*PINBALL_WIDTH;

	}
	else
	{
		this->x += this->dx;
		this->ddx = 0;
	}

	if (this->y + 8*PINBALL_HEIGHT >= SCREEN_HEIGHT)
	{
		this->dy = -this->dy/3;
		this->y = SCREEN_HEIGHT-1-8*PINBALL_HEIGHT;

	}
	else if (this->y - 8*PINBALL_HEIGHT <= 0)
	{
		this->dy = -this->dy/3;
		this->y = 1+8*PINBALL_HEIGHT;


	}
	else
	{
		this->y += this->dy;
		this->ddy = 0;
	}

}

Ball player(SCREEN_WIDTH/2,SCREEN_HEIGHT/2);




#endif
