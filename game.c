/*
 * game.c
 *
 *  Created on: 2014. 12. 6.
 *      Author: NCri
 */
#include <stdio.h>
#include "setting.h"
#include "util.h"

P_HWATOO steal_pi(player_info * player){
	P_HWATOO pae = player->head_pae;

	while(pae != NULL){
		if(!strcmp(pae->name, PI)){
			delete_pae(player->head_pae, pae);
			return pae;
		}
		pae = pae->next;
	}

	return pae;
}
player_info * next_turn(char player_id){
	player_info * next_player;
	extern player_info A_player;
	extern player_info B_player;
	extern player_info C_player;

	if('A' == player_id){
		next_player = &A_player;
	}
	if('B' == player_id){
		next_player = &B_player;
	}
	if('C' == player_id){
		next_player = &C_player;
	}

	return next_player;
}
