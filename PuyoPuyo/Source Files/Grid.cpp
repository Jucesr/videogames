#include "../Header Files/Grid.h"

//To see description of some variables and methods please read the comments located in Grid.h

Grid::Grid(int nrows, int ncolumns, int nwidth, int nheight){
	rows = nrows;
	columns = ncolumns;
	width = nwidth;
	height = nheight;

	//Calculate block dimensions
	blockWidth = width / (columns);
	blockHeight = height / (rows);
	createGrid();

}

void Grid::createGrid(){
	for (int i = 0; i < rows * columns; i++)
	{
		square* newSquare;
		newSquare = (square *) malloc(sizeof (square));
		newSquare->info = NULL;
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


void Grid::clearGrid(){

	square* iterator;

	iterator = start;

	while( iterator != NULL) {

		iterator->info = NULL;
		iterator = iterator->next;

	}

}


Entity* Grid::getInfo(int c, int r){

	square* iterator;

	iterator = start;

	//This number is used to tell the iterator how many times it has to iterate to reach the desired square.
	int squareNumber = (r)*columns + c;

	for (int i = 0; i < squareNumber; i++)
	{
		iterator = iterator->next;
	}
	return iterator->info;
}

void Grid::setInfo(Entity* nInfo, bool setNull){
	int c;
	int r;

	c = nInfo->getPosX();
	r = nInfo->getPosY();


	square* iterator;

	iterator = start;

	int squareNumber = (r)*columns + c;

	for (int i = 0; i < squareNumber; i++)
	{
		iterator = iterator->next;
	}
	if ( setNull == false )
		iterator->info = nInfo;
	else
		iterator->info = NULL;

}

void Grid::freeSquare(int c, int r){

	square* iterator;

	iterator = start;

	int squareNumber = (r)*columns + c;

	for (int i = 0; i < squareNumber; i++)
	{
		iterator = iterator->next;
	}
	delete iterator->info;
	iterator->info = NULL;

}


int Grid::getRows(){
	
	return rows;

}

int Grid::getColumns(){
	
	return columns;

}

void Grid::render(){

	square* iterator;

	iterator = start;

	for (int r = 0; r < rows; r++)
	{
		for (int c = 0; c < columns; c++)
		{
			if( iterator->info != NULL){
				iterator->info->render();
				
			}

		iterator = iterator->next;
		}
	}

}

int Grid::getBlockWidth(){
	
	return blockWidth;

}

int Grid::getBlockHeight(){
	
	return blockHeight;

}
