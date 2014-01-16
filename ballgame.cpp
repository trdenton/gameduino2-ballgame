// Do not remove the include below
#include "ballgame.h"
#include <EEPROM.h>
#include <SPI.h>
#include <GD2.h>
#include <math.h>
#include "pinball.h"
#include "Common.h"
#include "Ball.h"
#include "Input.h"
#include "PathSeg.h"

PathSeg segs[SCREEN_WIDTH/32];
int score = 0;
int topscore = 0;
bool ballFell()
{
	int i;
	int touchCount = 0;
	int x = player.getX()/16;
	int y = player.getY()/16;

	int start = (y - PINBALL_HEIGHT/2)/2;

	if(start <= 0)
		y = 0;

	int end = (y+ PINBALL_HEIGHT/2)/2;
	if (end >= SCREEN_HEIGHT/32)
		end = SCREEN_HEIGHT/32;

	//check 5 points on the ball, need at least three to not fall
	for(i=start;i<end;i++)
	//for(i=(y >= 12 ? y - 12 : 0);i<(y <= SCREEN_HEIGHT/32 - 12 ? y + 12 : SCREEN_HEIGHT/32);i++)
	{
		PathSeg seg = segs[i];
		if (	x + PINBALL_WIDTH/2 <= (seg.getCentre()+seg.getWidth()/2) && \
				x + PINBALL_WIDTH/2 >= (seg.getCentre()-seg.getWidth()/2) && \
				y <= 2*(i+1) && \
				y >= 2*(i-1))
			touchCount++;

		if (	x - PINBALL_WIDTH/2 <= (seg.getCentre()+seg.getWidth()/2) && \
				x - PINBALL_WIDTH/2 >= (seg.getCentre()-seg.getWidth()/2) && \
				y <= 2*(i+1) && \
				y >= 2*(i-1))
			touchCount++;

		if (	x <= (seg.getCentre()+seg.getWidth()/2) && \
				x >= (seg.getCentre()-seg.getWidth()/2) && \
				y <= 2*(i+1) && \
				y >= 2*(i-1))
			touchCount++;

		if (	x <= (seg.getCentre()+seg.getWidth()/2) && \
				x >= (seg.getCentre()-seg.getWidth()/2) && \
				y + PINBALL_HEIGHT/2 <= 2*(i+1) && \
				y + PINBALL_HEIGHT/2 <= 2*(i-1))
			touchCount++;

		if (	x <= (seg.getCentre()+seg.getWidth()/2) && \
				x >= (seg.getCentre()-seg.getWidth()/2) && \
				y - PINBALL_HEIGHT/2 <= 2*(i+1) && \
				y - PINBALL_HEIGHT/2 <= 2*(i-1))

			touchCount++;



	}

	if (touchCount == 0)
		return true;
	return false;
}

void setup()
{
	Serial.begin(115200);
	GD.begin();
	LOAD_ASSETS();
//	segs = (PathSeg*)malloc((SCREEN_HEIGHT/2)*sizeof(PathSeg));
	/*
	 * Setup initial segs
	 */
	int i;
	for(i=0;i<SCREEN_HEIGHT/32;i++)
	{
		segs[i] = PathSeg(80,SCREEN_WIDTH/32);
	}

}
void loop()
{
	static uint16_t t=0;

	input.update();
	player.update(input);

	GD.Clear();



	//tile background

//	GD.Begin(BITMAPS);
//	GD.BitmapSize(BILINEAR,REPEAT,REPEAT,480,272);
//	GD.Vertex2ii(0,0,TILE_SMALL_HANDLE);

	/*
	 * Draw segs
	 */
	GD.ColorRGB(0xFF,0xFF,0xFF);
	int i;
	for(i=0;i<SCREEN_HEIGHT/32;i++)
	{
		segs[i].draw(i*2);
	}


	player.draw();

	//draw score

	GD.ColorRGB(0xFF,0x00,0x00);
	GD.cmd_text(0,0,28,0,"Score: ");
	GD.cmd_number(0,30,28,0,score);
	GD.ColorRGB(0x00,0x00,0xFF);
	GD.cmd_number(0,60,28,0,topscore);

	GD.swap();



	if (ballFell())
	{
		if (score > topscore)
		{
			topscore = score;
		}
		score = 0;
	}
	else
		score++;

	/*
	 * move each thinger down one
	 */

	PathSeg last = segs[SCREEN_HEIGHT/32 - 2];
	int offset = (int)((double)last.getWidth()*((double)rand()/(double)RAND_MAX)/4.0);
//	Serial.println(offset);
	int x = 0;
	if (last.getCentre() < 2*offset)
		x= last.getCentre() + offset;
	else if (last.getCentre() > SCREEN_WIDTH/16 - 2*offset)
		x= last.getCentre() - offset;
	else
		x= last.getCentre() + (rand()%2==0?-1:1)*offset;

	segs[SCREEN_HEIGHT/32-1]=PathSeg(80,x);
	for(i = 0; i < SCREEN_HEIGHT/32 - 1; i++)
	{
		segs[i]=segs[i+1];
	}




}
