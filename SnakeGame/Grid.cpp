#include "Grid.h"

//To see description of some variables and methods please read the comments located in Grid.h

Grid::Grid(int nrows, int ncolumns, int nwidth, int nheight){
	rows = nrows;
	columns = ncolumns;
	width = nwidth;
	height = nheight;

	//Calculate block dimensions
	blockWidth = width / (columns + 2);
	blockHeight = height / (rows + 2);
	createGrid();

}

void Grid::clearGrid(){

	square* iterator;

	iterator = start;

	while( iterator != NULL) {

		iterator->type = -1;
		iterator = iterator->next;

	}

}

int Grid::getType(int c, int r){

	square* iterator;

	iterator = start;

	//This number is used to tell the iterator how many times it has to iterate to reach the desired square.
	int squareNumber = (r)*columns + c;

	for (int i = 0; i < squareNumber; i++)
	{
		iterator = iterator->next;
	}
	return iterator->type;
}


void Grid::setType(int c, int r, int nType){

	square* iterator;

	iterator = start;

	int squareNumber = (r)*columns + c;

	for (int i = 0; i < squareNumber; i++)
	{
		iterator = iterator->next;
	}
	iterator->type = nType;

}


void Grid::createGrid(){
	for (int i = 0; i < rows * columns; i++)
	{
		square* newSquare;
		newSquare = (square *) malloc(sizeof (square));
		newSquare->type = -1;
		newSquare->next = NULL;
	
		if( start == NULL ) {

			start = newSquare;
			end = newSquare;

		}else{

			end->next = newSquare;
			end = newSquare;

		}
	
	}

}


int Grid::getRows(){
	
	return rows;

}

int Grid::getColumns(){
	
	return columns;

}

void Grid::printGrid(){

	square* iterator;

	iterator = start;

	for (int r = 0; r < rows; r++)
	{
		for (int c = 0; c < columns; c++)
		{
			if( iterator->type != -1){
				printf("X");
			}else
				printf("O");

		iterator = iterator->next;
		}
		printf("\n");
	}
	printf("\n\n");

}

int Grid::getBlockWidth(){
	
	return blockWidth;

}

int Grid::getBlockHeight(){
	
	return blockHeight;

}
