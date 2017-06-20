#ifndef GAMESTATE_H
#define GAMESTATE_H

/*

	This is the base clase for all the possibles states in the snake game. Basically is used to implement polymorphism 

*/

class GameState{
	public:
    virtual void handle_events() = 0;
    virtual void logic() = 0;
    virtual void render() = 0;
    virtual ~GameState(){};
};


#endif