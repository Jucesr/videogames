//*************** GRID CLASS ***************
#include "Grid.h"

Grid::Grid(int nwidth, int nheight){

	width=nwidth;
	height=nheight;
	rows = ROWS;
	columns = COLUMNS;
	
	//Calculate block dimensions
	blockWidth = width / COLUMNS;
	blockHeight = height / ROWS;

	//Initialize the grid
	clearGrid();

}

void Grid::clearGrid(){

	for (int r = 0; r < rows; r++)
	{
		for (int c = 0; c < columns; c++)
		{
			blocks[r][c] = NULL;
		}
	}
}

Rectangle* Grid::checkAvailability(int r, int c){

	return blocks[r][c];
}

void Grid::changeBlockState(int r, int c, Rectangle* rec){

	if( r< ROWS && r>=0 && c<COLUMNS && c>=0)
	blocks[r][c] = rec;
}

int Grid::getBlockWidth(){
	
	return blockWidth;

}

int Grid::getBlockHeight(){
	
	return blockHeight;

}

int Grid::getRows(){
	
	return rows;

}

int Grid::getCols(){
	
	return rows;

}

void Grid::printGrid(){

	for (int r = 0; r < rows; r++)
	{
		for (int c = 0; c < columns; c++)
		{
			if(blocks[r][c]==NULL){
				printf("X");
			}else
				printf("O");
		}
		printf("\n");
	}
	printf("\n\n");

}
