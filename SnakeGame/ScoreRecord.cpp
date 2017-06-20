#include "ScoreRecord.h"

ScoreRecord::ScoreRecord(){

	currentNumRecords = 0;

	//Open file for reading in binary
    file = SDL_RWFromFile( "Media\\scoreRecords.bin", "r+b" );

	if( file == NULL )
    {
		//Create file for writing
        file = SDL_RWFromFile( "Media\\scoreRecords.bin", "w+b" );
	}else{

		readFromFile();
		sort();

	}

}

void ScoreRecord::readFromFile(){

	//Read elements from the file

	endOfFile = SDL_RWread( file, &list_records[ currentNumRecords ], sizeof(record), 1 );

	while( endOfFile != 0 && currentNumRecords!= LIMIT_RECORD){

		currentNumRecords++;
		endOfFile = SDL_RWread( file, &list_records[ currentNumRecords ], sizeof(record), 1 );

	}
	

	

}

ScoreRecord::~ScoreRecord(){

	free();
}

void ScoreRecord::free(){

	writeOnFile();
	SDL_RWclose( file );
}

void ScoreRecord::writeOnFile(){

	//Close it in order to ereased the data.
	SDL_RWclose( file );
	file = SDL_RWFromFile( "Media\\scoreRecords.bin", "w+b" );

	for( int i = 0; i < currentNumRecords; ++i )
    {
        SDL_RWwrite( file, &list_records[ i ], sizeof(record), 1 );
    }

}

void ScoreRecord::addNewRecord(std::string name, int score, std::string difficulty){

	record newRecord;
	newRecord.name = name;
	newRecord.score = score;
	newRecord.difficulty = difficulty;

	if( currentNumRecords == LIMIT_RECORD )
	{
		list_records[currentNumRecords-1] = newRecord;

	}else
	{
		list_records[currentNumRecords] = newRecord;
		currentNumRecords++;
	}
}

void ScoreRecord::sort(){

	record aux;
	int i;
	int j;

	for (i=0; i<=currentNumRecords-1; i++)
	{
		for (j=i+1 ; j<currentNumRecords; j++)
		{
			if (list_records[i].score < list_records[j].score)
			   {
                    aux = list_records[i];
                    list_records[i] = list_records[j];
                    list_records[j] = aux;
			   }
		}
	}
    
}

int ScoreRecord::getHightScore(){

	if (currentNumRecords > 0)
		return list_records[0].score;
	else
		return -1;

}

int ScoreRecord::getNumRecords(){

	return currentNumRecords;

}

std::string ScoreRecord::getName(int pos){

	return list_records[pos].name;
}

int ScoreRecord::getScore(int pos){

	return list_records[pos].score;

}

std::string ScoreRecord::getDifficulty(int pos){

	return list_records[pos].difficulty;

}

