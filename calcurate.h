/*
 * calcurate.h
 *
 *  Created on: 2014. 12. 2.
 *      Author: NCri
 */

#ifndef _CALCURATE_
#define _CALCURATE_

// 외부에 제공될 인터페이스 함수.
// 플레이어 점수 계산.
extern void calcurate(void * player);
// 플레이어가 났는지 확인.
extern bool is_win(void * player);
extern void test_show_score(void * player);

#endif /* _CALCURATE_ */
