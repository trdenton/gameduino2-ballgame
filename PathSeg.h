#ifndef __PATHSEG_H__
#define __PATHSEG_H__
#include <GD2.h>
#include "Common.h"
class PathSeg
{
private:
	int width;
	int centre;
public:
	PathSeg();
	PathSeg& operator=(const PathSeg &other);
	PathSeg(int w, int c);
	void draw(int y);
	int getCentre();
	int getWidth();

};
PathSeg& PathSeg::operator=(const PathSeg &other)
{
	this->width = other.width;
	this->centre = other.centre;
	return *this;
}
int PathSeg::getCentre()
{
	return centre;
}
int PathSeg::getWidth()
{
	return width;
}
PathSeg::PathSeg()
{
	this->width = 10;
	this->centre = SCREEN_WIDTH/2;
}
PathSeg::PathSeg(int w, int c)
{
	this->width = w;
	this->centre = c;
}

void PathSeg::draw(int y)
{
	GD.Begin(LINES);
	GD.LineWidth(16*20);
	GD.Vertex2ii(centre - width/2,y); GD.Vertex2ii(centre + width/2,y);
}
#endif
