#ifndef __INPUT_H__
#define __INPUT_H__

#include <GD2.h>

class Input
{
private:
	int touchx, touchy, touchz;
	int ax,ay,az;
	int tag;

public:
	int getTouchX();
	int getTouchY();
	int getTouchZ();
	int getAccelerationX();
	int getAccelerationY();
	int getAccelerationZ();
	int getTag();
	void update();
};



int Input::getTouchX()
{
	return this->touchx;
}
int Input::getTouchY()
{
	return this->touchy;
}
int Input::getTouchZ()
{
	return this->touchz;
}
int Input::getAccelerationX()
{
	return this->ax;
}
int Input::getAccelerationY()
{
	return this->ay;
}
int Input:: getAccelerationZ()
{
	return this->az;
}
int Input::getTag()
{
	return this->tag;
}
void Input::update()
{
	GD.get_inputs();
	GD.get_accel(this->ax,this->ay,this->az);
	this->touchx = GD.inputs.x;
	this->touchy = GD.inputs.y;
	this->touchz = GD.inputs.rz;
	this->tag = GD.inputs.tag;

}

Input input;
#endif
