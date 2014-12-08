/*
 * calcurate.h
 *
 *  Created on: 2014. 12. 2.
 *      Author: NCri
 */

#ifndef _CALCURATE_
#define _CALCURATE_

// 피박 광박 계산도 해줘야됨.

// 외부에 제공될 인터페이스 함수.
// 플레이어 점수 계산.
int calcurate(void * player);
void reset_score(void * player);
// 플레이어가 났는지 확인.
int is_win(void * player);

// 테스트 코드.
void test_show_score(void * player);

// 최종 게임이 끝난 후 점수 및 돈을 갱신해준다.
int update_player_score_and_money(void * player, void * loser1, void * loser2);
#endif /* _CALCURATE_ */
