#ifndef GRID_H
#define GRID_H

#include <stdio.h>
#include <stdlib.h>
#include "../Header Files/Entity.h"

/* This clase is used to simulate a grid with N rows and N columns. 
	Where 
	ROW = Y
	COLUMN = X.


This struct is the base of the grid. First I tried to make the grid with a matrix.
The problem with the matrix is that you have to give it an static number of values
and if I wanted to create dinamic grids (n rows and n colums) I had to modify the code
of this class which was not ideal. Doing this now I can set whatever I want.

The variable info accomplishes 2 goals. 
	It represents whether the square is empty or not. (NULL means that is empty)
	If it isn't empty it store what kind of entity is inside the square.

In this way I can create dinamic grids with dinamic type of data.

*/

struct square{
	Entity* info;
	square* next;
};


class Grid {

public:
	Grid();
	Grid(int rows, int columns, int width, int height);
	void clearGrid();
	void createGrid();

	//Free the square and also free the info in it.
	void freeSquare(int c, int r);

	Entity* getInfo(int c, int r);
	void setInfo(Entity* nInfo, bool setNull = false);

	//Getters
	int getRows();
	int getColumns();
	int getBlockWidth();
	int getBlockHeight();


	void render();

protected:
	int rows;
	int columns;
	int width;
	int height;
	int blockWidth;
	int blockHeight;
	
	//These are the references of the dinamic grid.
	square* start;
	square* end;
};


 
#endif