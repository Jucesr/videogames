#ifndef GRID_H
#define GRID_H

/* This clase is used to simulate a grid with N rows and N columns. 
	Where 
	ROW = Y
	COLUMN = X.*/

/*
This struct is the base of the grid. First I tried to make the grid with a matrix.
The problem with the matrix is that you have to give it an static number of values
and if I wanted to create dinamic grids (n rows and n colums) I had to modify the code
of this class which was not ideal. Doing this now I can set whatever I want.

The variable type accomplishes 2 goals. 
	It represents whether the square is empty or not. (-1 means that is empty)
	If it isn't empty it store what kind of entity is in the square (Snake part, wall, food...) 
*/
struct square{
	int type;
	square* next;
};

class Grid {

public:
	Grid();
	Grid(int rows, int columns, int width, int height);
	void clearGrid();
	void createGrid();
	int getType(int c, int r);
	void setType(int c, int r, int nType);

	//Getters
	int getRows();
	int getColumns();
	int getBlockWidth();
	int getBlockHeight();

	void printGrid();

protected:
	int rows;
	int columns;
	int width;
	int height;
	int blockWidth;
	int blockHeight;

	//There are the references of the dinamic grid.
	square* start;
	square* end;
};
 
#endif