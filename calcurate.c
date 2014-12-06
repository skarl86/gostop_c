/*
 * calcurate.c
 *
 *  Created on: 2014. 12. 2.
 *      Author: NCri
 */
#include "setting.h"

#define GWANG 				"광"
#define PI					"피"
#define WO					"오"
#define SIP					"십"
#define INDEX_OF_BE_GWANG 	44

// 이 파일에서만 사용하게 될 private 함수들.
void _cal_gwang(void *player);
void _cal_pi(void *player);
void _cal_sip(void *player);
void _cal_wo(void *player);

void test_show_score(void * player){
	player_info *p_info = (player_info *) player;

	printf("광 : %d,  피 : %d, 10점수 : %d, 5점수 : %d",
			p_info->score->gwang, p_info->score->pi, p_info->score->sip, p_info->score->wo);

}
void calcurate(void * player) {
	player_info *p_player_info = (player_info *) player;

	// 사용자.
	p_player_info->score = (P_SCORE) malloc(sizeof(SCORE));

	// 예외 처리.
	if (player == NULL) {
		printf("ERROR :: Player is NULL");
		return;
	}

	/**
	 * 광 점수
	 * - 광을 3장 이상 모으면 점수가 되고 다음 규칙이 적용된다.
	 * 1) 비 광을 제외한 광이 3장이면 3점
	 * 2) 비 광을 포함하여 광이 3장이면 2점
	 * 3) 광이 4장이면 4점
	 * 4) 광이 5장이면 15점
	 */
	_cal_gwang(player);
	/**
	 * 피로 점수
	 * 1) 피를 10장 모으면 1점이고, 한 장씩 추가될 때마다 1점씩 추가가 됨
	 * ** 쌍피는 피 2 장으로 계산해야 함
	 */
	_cal_pi(player);
	/**
	 * 10 자리 점
	 * 1) 10 자리를 5장 모으면 1점이고, 한 장씩 추가될 때마다 1점씩 추가가 됨
	 * 2) 고도리는 5점
	 */
	_cal_sip(player);
	/*
	 * 5 자리로 점수
	 * 1) 5 자리를 5장 모으면 1점이고, 한 장씩 추가될 때마다 1점씩 추가가 됨
	 * 2) 청단, 초단, 홍단 : 각 3점씩
	 */
	_cal_wo(player);
}

void _cal_gwang(void *player) {
	player_info *p_player_info = (player_info *) player;
	P_HWATOO head_pae = p_player_info->head_pae;
	bool has_be_gwang = 0; // 비광 체크 불린.
	int count_gwang = 0;

	while (head_pae != NULL) {
		if (head_pae->id == INDEX_OF_BE_GWANG) {
			// 비광일 존재할 경우.
			has_be_gwang = 1;
		}
		if (!strcmp(head_pae->name, GWANG))
			count_gwang++;
		head_pae = head_pae->next;
	}

	if (count_gwang >= 3) { // 광이 3~5일때.
		// 비광이 포함된 상태에서 5점 미만 일 경우 -1.
		if (has_be_gwang && count_gwang < 5)
			p_player_info->score->gwang = count_gwang - 1;
		else
			// 5광일 경우 카운트 그대로.
			p_player_info->score->gwang = count_gwang;
	} else { // 광이 0~2개 일때는 0점 처리.
		p_player_info->score->gwang = 0;
	}
}

void _cal_pi(void *player) {
	player_info *p_player_info = (player_info *) player;
	P_HWATOO head_pae = p_player_info->head_pae;
	int count_pi = 0;

	while (head_pae != NULL) {
		if (!strcmp(head_pae->name, PI)) {
			if (head_pae->isSSangpi) {
				count_pi += 2;
			} else {
				count_pi += 1;
			}
		}
		head_pae = head_pae->next;
	}

	// 피가 10장일 경우 1점.
	if (count_pi == 10) {
		p_player_info->score->pi = 1;
	} else if (count_pi > 10) { // 10장 이상일 경우 한장당 1점씩.
		p_player_info->score->pi = (count_pi % 10) + (count_pi / 10);
	} else { // 그외에는 0점.
		p_player_info->score->pi = 0;
	}
}

void _cal_sip(void *player) {
	player_info *p_player_info = (player_info *) player;
	P_HWATOO head_pae = p_player_info->head_pae;
	int count_sip = 0;

	while (head_pae != NULL) {
		if (!strcmp(head_pae->name, SIP)) {
			count_sip++;
		}
		head_pae = head_pae->next;
	}

	// 1
	if (count_sip == 5) {
		p_player_info->score->sip = 1;
	} else if (count_sip > 5) {
		p_player_info->score->sip = (count_sip / 5) + (count_sip % 5);
	}
}

void _cal_wo(void *player) {
	player_info *p_player_info = (player_info *) player;
	P_HWATOO head_pae = p_player_info->head_pae;
	int count_wo = 0;
	int count_chungdan = 0;
	int count_hongdan = 0;
	int count_chodan = 0;

	while (head_pae != NULL) {
		if (!strcmp(head_pae->name, WO)) {
			count_wo++;
			// 초단, 청단, 홍단 인덱스.
			// 초단 : 13, 17, 25
			// 청단 : 21, 33, 37
			// 홍단 : 1, 5, 9
			if (head_pae->id == 13 || head_pae->id == 17
					|| head_pae->id == 25) {
				count_chodan++;
			}
			if (head_pae->id == 21 || head_pae->id == 33
					|| head_pae->id == 37) {
				count_chungdan++;
			}
			if (head_pae->id == 1 || head_pae->id == 5 || head_pae->id == 9) {
				count_hongdan++;
			}
		}
		head_pae = head_pae->next;
	}

	// 초단, 홍단, 청단 체크.
	if (count_chodan == 3) {
		p_player_info->score += 3;
	}
	if (count_chungdan == 3) {
		p_player_info->score += 3;
	}
	if (count_hongdan == 3) {
		p_player_info->score += 3;
	}
}
