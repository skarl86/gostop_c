/*
 * game.h
 *
 *  Created on: 2014. 12. 6.
 *      Author: NCri
 */

#ifndef GAME_H_
#define GAME_H_

typedef struct game
{
	//char winner[2];
	int winner_score;
}GAME, *P_GAME;

player_info * next_turn(char player_id);
extern P_HWATOO steal_pi(player_info * player);

#endif /* GAME_H_ */
