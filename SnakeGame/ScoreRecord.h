#ifndef SCORERECORD_H
#define SCORERECORD_H

#include <string>
#include <SDL.h>

#define LIMIT_RECORD 10

struct record{
	std::string name;
	int score;
	std::string difficulty;
};

class ScoreRecord{

private:
	record list_records[ LIMIT_RECORD ];
	SDL_RWops* file;
	size_t endOfFile;
	int currentNumRecords;

public:

	ScoreRecord();
	~ScoreRecord();

	void free();
	void readFromFile();
	void writeOnFile();
	void addNewRecord(std::string name, int score, std::string difficulty);
	void sort();
	int getHightScore();
	int getNumRecords();

	std::string getName(int pos);
	int getScore(int pos);
	std::string getDifficulty(int pos);
};

#endif