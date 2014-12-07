/*
 * calcurate.c
 *
 *  Created on: 2014. 12. 2.
 *      Author: NCri
 */
#include <stdio.h>
#include "setting.h"

#define INDEX_OF_BE_GWANG 	44	// 비광의 인덱스#define FIVE_GWANG_SCORE	15	// 5광 점수.#define GODORI_SCORE		5	// 고도리 점수.#define CHONG_TONG_SCORE	10	// 총통 점수.#define THREE_GO			3 	// 쓰리 고.
bool _isGodori(int index);		// 고도리냐.
bool _isChodan(int index);		// 초단이냐.
bool _isHongdan(int index);		// 홍단이냐.
bool _isChungdan(int index);	// 청단이냐.

// 이 파일에서만 사용하게 될 private 함수들.
int _cal_gwang(void *player);
int _cal_pi(void *player);
int _cal_sip(void *player);
int _cal_wo(void *player);
// 십하고 오의 갯수로만 적용되는 점수 계산 방법이 동일하기 때문에 하나의 함수를 이용하는걸로.
int _cal_sip_and_wo(int count);
int _cal_go(void *player);

void test_show_score(void * player) {
	player_info *p_info = (player_info *) player;
	P_HWATOO head = p_info->head_pae;

	while (head != NULL) {
		printf("%d%s\t", head->isSSangpi, head->name);
		head = head->next;
	}
	printf("\n");
	printf("광 : %d,  피 : %d, 10점수 : %d, 5점수 : %d\n", p_info->score->gwang,
			p_info->score->pi, p_info->score->sip, p_info->score->wo);

}
bool is_win(void * player) {
	player_info *p_info = (player_info *) player;
	P_SCORE p_sc = p_info->score;
	int sum;
	bool b_is_win = 0;
	sum = p_sc->gwang + p_sc->pi + p_sc->sip + p_sc->wo;

	if (sum >= 3) // 3점 이상이면 승리.
		b_is_win = 1;

	return b_is_win;
}

int calcurate(void * player) {
	player_info *p_player_info = (player_info *) player;
	int sum = 0;
	// 사용자.
	p_player_info->score = (P_SCORE) malloc(sizeof(SCORE));

	// 예외 처리.
	if (player == NULL) {
		printf("ERROR :: Player is NULL");
		return 0;
	}

	/**
	 * 광 점수
	 * - 광을 3장 이상 모으면 점수가 되고 다음 규칙이 적용된다.
	 * 1) 비 광을 제외한 광이 3장이면 3점
	 * 2) 비 광을 포함하여 광이 3장이면 2점
	 * 3) 광이 4장이면 4점
	 * 4) 광이 5장이면 15점
	 */
	sum += _cal_gwang(player);

	/**
	 * 피로 점수
	 * 1) 피를 10장 모으면 1점이고, 한 장씩 추가될 때마다 1점씩 추가가 됨
	 * ** 쌍피는 피 2 장으로 계산해야 함
	 */
	sum += _cal_pi(player);

	/**
	 * 10 자리 점
	 * 1) 10 자리를 5장 모으면 1점이고, 한 장씩 추가될 때마다 1점씩 추가가 됨
	 * 2) 고도리는 5점
	 */
	sum += _cal_sip(player);

	/*
	 * 5 자리로 점수
	 * 1) 5 자리를 5장 모으면 1점이고, 한 장씩 추가될 때마다 1점씩 추가가 됨
	 * 2) 청단, 초단, 홍단 : 각 3점씩
	 */
	sum += _cal_wo(player);

	p_player_info->total_score = sum;

	return sum;
}

int final_score(void * player) {
	player_info *p_info = (player_info *) player;

	// 총통일때.
	if (p_info->isChongtong) {
		p_info->total_score = CHONG_TONG_SCORE + p_info->total_score;
	}
	// 흔들었을때.
	else if (p_info->isSwing) {
		p_info->total_score = p_info->total_score << 1;
	}
	// GO 했을때.
	else if (p_info->go_count) {
		p_info->total_score = _cal_go(player);
	}

	return p_info->total_score;
}

int _cal_go(void * player) {
	player_info *p_info = (player_info *) player;
	int score = 0; // 배수가 적용 된 마지막 점수.
	int multiple = 0; // 배수.
	int i;

	if (p_info->go_count < 3)
		score = p_info->total_score + p_info->go_count;
	else {
		multiple = (p_info->go_count / THREE_GO)
				+ (p_info->go_count % THREE_GO);
		score = p_info->total_score << multiple;
	}

	return score;
}
/* 내부에서만 사용할 함수들.*/
bool _isGodori(int index) {
	if (index == 4 || index == 12 || index == 29)
		return 1;
	else
		return 0;
}
bool _isChodan(int index) {
	if (index == 13 || index == 17 || index == 25)
		return 1;
	else
		return 0;
}
bool _isHongdan(int index) {
	if (index == 1 || index == 5 || index == 9)
		return 1;
	else
		return 0;
}
bool _isChungdan(int index) {
	if (index == 21 || index == 33 || index == 37)
		return 1;
	else
		return 0;
}
int _cal_sip_and_wo(int count) {
	if (count == 5) {
		return 1;
	} else if (count > 5) {
		return (count / 5) + (count % 5);
	} else {
		return 0;
	}
}
int _cal_gwang(void *player) {
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
			p_player_info->score->gwang = FIVE_GWANG_SCORE;
	} else { // 광이 0~2개 일때는 0점 처리.
		p_player_info->score->gwang = 0;
	}

	return p_player_info->score->gwang;
}

int _cal_pi(void *player) {
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

	return p_player_info->score->pi;
}

int _cal_sip(void *player) {
	player_info *p_player_info = (player_info *) player;
	P_HWATOO head_pae = p_player_info->head_pae;
	int count_sip = 0; // 십 카운트.
	int count_godori = 0; // 고도리 카운트.

	while (head_pae != NULL) {
		if (!strcmp(head_pae->name, SIP)) {
			count_sip++;
			if (_isGodori(head_pae->id))
				count_godori++;
		}
		head_pae = head_pae->next;
	}

	p_player_info->score->sip = _cal_sip_and_wo(count_sip);

	// 고도리가 떴따!!
	if (count_godori == 3) {
		p_player_info->score->sip += GODORI_SCORE;
	}
	return p_player_info->score->sip;
}

int _cal_wo(void *player) {
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
			if (_isChodan(head_pae->id)) {
				count_chodan++;
			}
			if (_isChungdan(head_pae->id)) {
				count_chungdan++;
			}
			if (_isHongdan(head_pae->id)) {
				count_hongdan++;
			}
		}
		head_pae = head_pae->next;
	}
	// 오 점수 계산.
	p_player_info->score->sip = _cal_sip_and_wo(count_wo);

	// 초단, 홍단, 청단 체크.
	if (count_chodan == 3) {
		p_player_info->score->wo += 3;
	}
	if (count_chungdan == 3) {
		p_player_info->score->wo += 3;
	}
	if (count_hongdan == 3) {
		p_player_info->score->wo += 3;
	}

	return p_player_info->score->wo;
}
