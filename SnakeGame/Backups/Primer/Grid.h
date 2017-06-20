#ifndef GRID_H
#define GRID_H
 
#include "Rectangle.h"
#include <stdio.h>

/* This clase is used to simulate a grid with N rows and N columns. 
	Where 
	ROW = Y
	COLUMN = X
In this case it's a grid of Rectangles.*/
const int ROWS = 12;
const int COLUMNS = 12;

class Grid {

public:
	Grid(int width, int height);
	void clearGrid();
	Rectangle* checkAvailability(int r, int c);
	void changeBlockState(int r, int c,  Rectangle* rec);

	//Getters
	int getBlockWidth();
	int getBlockHeight();
	int getRows();
	int getCols();

	void printGrid();

private:
	int rows;
	int columns;
	int width;
	int height;
	int blockWidth;
	int blockHeight;

	// I am gonna use a matrix to manage the grid. If the value is FALSE it means the space is available.
	Rectangle* blocks[ROWS][COLUMNS];
};
 
#endif