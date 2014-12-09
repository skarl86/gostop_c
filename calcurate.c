/*
 * calcurate.c
 *
 *  Created on: 2014. 12. 2.
 *      Author: NCri
 */
#include <stdio.h>
#include "setting.h"

#define PI_BAK_COUNT		9	// 피박 조건.#define GWANG_BAK_COUNT		0	// 광박 조건.#define MUNGTUNG_COUNT		7	// 멍텅구리 조건.#define INDEX_OF_BE_GWANG 	44	// 비광의 인덱스#define FIVE_GWANG_SCORE	15	// 5광 점수.#define GODORI_SCORE		5	// 고도리 점수.#define CHONG_TONG_SCORE	10	// 총통 점수.#define THREE_GO			3 	// 쓰리 고.#define SCORE_PER_MONEY		100	// 1점 당 머니.// 배수를 확인할 16진수 값들.typedef enum multiple {
	GO_BAK = 0x2, PI_BAK = 0x4, GWANG_BAK = 0x8, SWING = 0x10, MUNG_BAK = 0x20
} MULTIPLE;
const int MULTIPLE_MASK = 0x1; // 배수를 확인할 마스크 값.

// 이 파일에서만 사용하게 될 private 함수들.
// update로 시작하는 함수는 전달 받은 포인터의 값을 직접 갱신하는 함수들.
// 그 외에는 전달 받은 값을 참조하거나 이용해서 갱신없이 값만 반환.

bool _isGodori(int index);		// 고도리냐.
bool _isChodan(int index);		// 초단이냐.
bool _isHongdan(int index);		// 홍단이냐.
bool _isChungdan(int index);	// 청단이냐.
bool _isPibak(void * payer);	// 피박이냐.
bool _isGwangbak(void * player);	// 광박이냐.
bool _isGobak(void * player);	// 고박이냐.
bool _isMungtung(void * player);	// 멍텅구리냐.

int _update_player_money(void * player, int losed_money); // 플레이어의 잃은 돈을 갱신.
int _update_gwang_score(void *player); // 광 점수 계산.
int _update_pi_count(void *player);
int _update_sip_count(player_info * player);
int _update_wo_count(void *player);

// 십하고 오의 갯수로만 적용되는 점수 계산 방법이 동일하기 때문에 하나의 함수를 이용하는걸로.
int _cal_sip_and_wo(int count);
int _cal_go(void * player);
int _cal_loser_multiple(int win_score, MULTIPLE type); // 패배한 플레이어 배수 계산.
int _cal_final_score(void * winner, void * player); // 패배한 플레이어 최종 점수.
// private 함수 //

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
void reset_score(void * player) {
	player_info * p_player = (player_info *) player;
	p_player->total_score = 0;
	p_player->total_score_when_go = 0;
	p_player->go_count = 0;
	p_player->isChongtong = false;
	p_player->isSwing = false;
	if (p_player->score == NULL)
		p_player->score = (P_SCORE) malloc(sizeof(SCORE));
	p_player->score->gwang = 0;
	p_player->score->pi = 0;
	p_player->score->sip = 0;
	p_player->score->wo = 0;
}
bool is_win(void * player) {
	player_info *p_info = (player_info *) player;
	int sum = 0;
	bool b_is_win = 0;

	if (p_info->total_score >= 3) { // 3점 이상이면 승리.
		// 플레이어가 GO를 했을 때 점수보다 높아야 다시 GO를 할 수 있다.
		// 이 경우는 플레이어가 GO를 하고 나서
		// 다른 플레이어에게 피를 뺏겨 점수가 떨어졌을때를.
		// 점검하기 위한 루틴.
		if (p_info->total_score > p_info->total_score_when_go) {
			b_is_win = 1;
			// GO 했을 때 점수를 저장한다.
			p_info->total_score_when_go = p_info->total_score;
		}
	}

	return b_is_win;
}

int calcurate(void * player) {
	player_info *p_player_info = (player_info *) player;
	int sum = 0;

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
	sum += _update_gwang_score(player);

	/**
	 * 피로 점수
	 * 1) 피를 10장 모으면 1점이고, 한 장씩 추가될 때마다 1점씩 추가가 됨
	 * ** 쌍피는 피 2 장으로 계산해야 함
	 */
	sum += _update_pi_count(player);

	/**
	 * 10 자리 점
	 * 1) 10 자리를 5장 모으면 1점이고, 한 장씩 추가될 때마다 1점씩 추가가 됨
	 * 2) 고도리는 5점
	 */
	sum += _update_sip_count(player);

	/*
	 * 5 자리로 점수
	 * 1) 5 자리를 5장 모으면 1점이고, 한 장씩 추가될 때마다 1점씩 추가가 됨
	 * 2) 청단, 초단, 홍단 : 각 3점씩
	 */
	sum += _update_wo_count(player);

	p_player_info->total_score = sum;

	return sum;
}

int update_player_score_and_money(void * winner, void * loser1, void * loser2) {
	player_info *p_winner = (player_info *) winner;
	player_info *p_loser1 = (player_info *) loser1;
	player_info *p_loser2 = (player_info *) loser2;

	// 패자 배수.
	int loser1_score = 0, loser2_score = 0;
	// 잃은 금액.
	int loser1_money = 0, loser2_money = 0;

	int winner_money = 0;

	// 총통일때는 10점을 주고 게임 끝.
	// 배수 계산을 하지 않는다.
	if (p_winner->isChongtong) {
		p_winner->total_score = CHONG_TONG_SCORE + p_winner->total_score;
	} else { // 그 외의 배수 계산.
		printf("플레이어(%c) ", p_loser1->id[0]);
		loser1_score = _cal_final_score(winner, loser1);
		printf("점수 (%d) 피 : (%d) 광 : (%d) \n", loser1_score, p_loser1->score->pi, p_loser1->score->gwang);
		loser1_money = loser1_score * SCORE_PER_MONEY;

		printf("플레이어(%c) ", p_loser2->id[0]);
		loser2_score = _cal_final_score(winner, loser2);
		printf("점수 (%d) 피 : (%d) 광 : (%d) \n", loser2_score, p_loser2->score->pi, p_loser2->score->gwang);
		loser2_money = loser2_score * SCORE_PER_MONEY;

		// 패배 플레이어의 돈에서 돈을 빼온다.
		winner_money = winner_money
				+ _update_player_money(loser1, loser1_money);
		winner_money = winner_money
				+ _update_player_money(loser2, loser2_money);

		// 승리자에게 돈을 갱신해준다.
		p_winner->money += winner_money;
		printf("승자 플레이어(%c) 획득 돈 : (%d)\n",p_winner->id[0], winner_money);
	}
	return p_winner->total_score;
}
int _cal_final_score(void * winner, void * loser) {
	// 피로 났을때.
	player_info * p_winner = (player_info *) winner;
	player_info * p_loser = (player_info *) loser;
	MULTIPLE multi = 0x0;

	int winner_score = p_winner->total_score; // 승리 플레이어의 배수 적용전 기본 점수.

	if (p_winner->score->pi >= 1) {
		// 피박.
		if (_isPibak(loser))
			multi |= PI_BAK;
	}
	// 광로 났을때.
	if (p_winner->score->gwang >= 2) {
		// 광박.
		if (_isGwangbak(loser)) {
			multi |= GWANG_BAK;
		}
	}
	// 흔들었을때.
	if (p_winner->isSwing) {
		multi |= SWING;
	}
	// 멍텅구리.
	if (_isMungtung(p_winner)) {
		multi |= MUNG_BAK;
	}
	// GO 박.
	if (_isGobak(loser)) {
		multi |= GO_BAK;
	}

	winner_score = _cal_loser_multiple(winner_score, multi);

	// 모든 배수를 적용한 이후에 GO 배수를 적용한다.
	// GO 배수.
	if (p_winner->go_count) {
		winner_score += _cal_go(p_winner);
	}

	return winner_score;
}
int _update_player_money(void * player, int losed_money) {
	int money = 0;
	player_info * p_player = (player_info *) player;
	if (p_player->money < losed_money) {
		// 자신의 소유한 모든 돈을 주고.
		money = p_player->money;
		// 소유한 돈이 잃을 돈 보다 적기때문에 0원 처리.
		p_player->money = 0;
	} else {
		// 자신의 소유한 돈에서 잃을 돈을 빼준다.
		p_player->money = p_player->money - losed_money;
		money = losed_money;
	}
	return money;
}
int _cal_loser_multiple(int win_score, MULTIPLE type) {
	printf(" 배수 : (%d) ",type);
	while (type > 0) {
		if (type & MULTIPLE_MASK) {
			// 점수의 배수 적용.
			win_score = win_score << 1;
		}
		type = type >> 1;
	}
	return win_score;
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
bool _isPibak(void * player) {
	player_info * p_info = (player_info *) player;
	if (p_info->score->pi == 0)
		return 1;
	return 0;
}
bool _isGwangbak(void * player) {
	player_info * p_info = (player_info *) player;
	P_HWATOO p_ht = p_info->head_pae;
	int count = 0;

	while(p_ht != NULL){
		if(!strcmp(p_ht->name, GWANG))
			count++;
		p_ht = p_ht->next;
	}

	if(count == 0)
		return 1;
	return 0;
}
bool _isGobak(void * player) {
	player_info * p_info = (player_info *) player;
	if (p_info->go_count > 0)
		return 1;
	return 0;
}
bool _isMungtung(void * player) {
	player_info * p_info = (player_info *) player;
	if (p_info->score->sip >= MUNGTUNG_COUNT)
		return 1;
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
int _update_gwang_score(void *player) {
	player_info * p_player_info = (player_info *) player;
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
		if (has_be_gwang)
			p_player_info->score->gwang = count_gwang - 1;
		else if(count_gwang == 5)
			// 5광일 경우 카운트 그대로.
			p_player_info->score->gwang = FIVE_GWANG_SCORE;
		else
			p_player_info->score->gwang = count_gwang;
	} else { // 광이 0~2개 일때는 0점 처리.
		p_player_info->score->gwang = 0;
	}

	return p_player_info->score->gwang;
}

int _update_pi_count(void *player) {
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

int _update_sip_count(player_info * player) {
	P_HWATOO temp = player->head_pae;
	int count_sip = 0; // 십 카운트.
	int count_godori = 0; // 고도리 카운트.

	while (temp != NULL) {
//		printf("while!!!\n");
		if (!strcmp(temp->name, SIP)) {
			count_sip++;
			if (_isGodori(temp->id)){
//				printf("godory!!!(%d)", count_godori);
				count_godori++;
			}
		}
		temp = temp->next;
	}
//	printf("escape\n");

	player->score->sip = _cal_sip_and_wo(count_sip);

	// 고도리가 떴따!!
	if (count_godori == 3) {
		printf("고도리떴따!!!!!!!!!!\n");
		player->score->sip += GODORI_SCORE;
	}
	return player->score->sip;
}

int _update_wo_count(void *player) {
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
