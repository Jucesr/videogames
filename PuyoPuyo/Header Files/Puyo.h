#ifndef PUYO_H
#define PUYO_H

#include "Entity.h"
#include "Texture.h"

enum puyoType
{
    PUYO_RED,
    PUYO_PURPLE,
    PUYO_BLUE,
    PUYO_YELLOW,
	PUYO_TOTAL
};

class Puyo : public Entity{

private:
	Texture* graphicSurface;
	int xrenderOffset;
	int yrenderOffset;
	int width;
	int heigth;

	//This variable is 
	bool togetherWithAnotherPuyo;

public:
	Puyo::Puyo(int nposX, int nposY, int nwidth, int nheight, int ntype, Texture* ngraphicSurface, int xrenderOffset = 0, int yrenderOffset = 0);
	Puyo::Puyo(int ntype);
	void render();

};

#endif