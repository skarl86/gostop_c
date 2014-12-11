/*
 * game.c
 *
 *  Created on: 2014. 12. 6.
 *      Author: NCri
 */
#include <stdio.h>
#include "setting.h"
#include "util.h"

P_HWATOO _steal_pi(player_info * pae);

// 받을 플레이어의 구조체 포인터를 넘긴다.
P_HWATOO steal_pi(player_info * player) {
	extern player_info A_player, B_player, C_player;
	P_HWATOO stealed_pae;
	if (player->id[0] == 'A') {
		stealed_pae = _steal_pi(&B_player);
		append_pae(stealed_pae, _steal_pi(&C_player));
	}
	if (player->id[0] == 'B') {
		stealed_pae = _steal_pi(&A_player);
		append_pae(stealed_pae, _steal_pi(&B_player));
	}
	if (player->id[0] == 'C') {
		stealed_pae = _steal_pi(&A_player);
		append_pae(stealed_pae, _steal_pi(&B_player));
	}

	return stealed_pae;
}
P_HWATOO _steal_pi(player_info * player) {
	P_HWATOO pae = player->head_pae;
	P_HWATOO ssang_pi = NULL; // 쌍피밖에 없을 경우를 대비함.
	while (pae != NULL) {
		// 피를 가져온다. 근데 1피만 가져와야 한다.
		if (!strcmp(pae->name, PI)) {
			if(!pae->isSSangpi){
				delete_pae(player->head_pae, pae);
				return pae;
			}else if(pae->isSSangpi){
				ssang_pi = pae;
			}
		}
		pae = pae->next;
	}

	// 상대 플레이어가 쌍피만 가지고 있을 경우.
	if(pae == NULL && !(ssang_pi == NULL) ){
		// 쌍피를 넘겨준다.
		delete_pae(player->head_pae, ssang_pi);
		return ssang_pi;
	}
	return NULL;
}
player_info * next_turn(char player_id) {
	player_info * next_player;
	extern player_info A_player;
	extern player_info B_player;
	extern player_info C_player;

	if ('A' == player_id) {
		next_player = &A_player;
	}
	if ('B' == player_id) {
		next_player = &B_player;
	}
	if ('C' == player_id) {
		next_player = &C_player;
	}

	return next_player;
}
