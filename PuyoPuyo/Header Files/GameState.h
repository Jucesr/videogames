#ifndef GAMESTATE_H
#define GAMESTATE_H

/*

	This is the base clase for all the possibles states in the snake game. Basically is used to implement polymorphism 

*/
enum GameStates
{
    STATE_NULL,
    STATE_MENU,
    STATE_GAME_RUNNING,
    STATE_SCORES,
	STATE_CREDITS,
    STATE_EXIT
};


class GameState{
protected:
	
	bool error;
	int nextState;

public:
    virtual void handle_events() = 0;
    virtual void logic() = 0;
    virtual void render() = 0;
	virtual bool getError() = 0;
    virtual ~GameState(){};

	int getNextState();
};


#endif