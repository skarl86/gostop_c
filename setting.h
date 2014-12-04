#ifndef _GOSTOP_
#define _GOSTOP_
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include<time.h>

typedef struct hwatoo
{
	int id; // 패의 고유번호
	int no; // 패의 월
	char name[4]; // 광 or 피 or 십 or 오
	bool isSSangpi; // 쌍피인지 구분
	struct hwatoo *next;
} HWATOO, *P_HWATOO;

typedef struct score
{
	int gwang; 	// 광 점수.
	int pi;		// 피 점수.
	int sip;	// 10 점수.
	int wo;		// 5 점수.
}SCORE, *P_SCORE;
/* 플레이어의 점수 정보 구조체.*/

typedef struct player_info
{
	bool isSwing; // 흔듦
	bool isChongtong; // 총통
	P_HWATOO head_pae; // 플레이어 패 정보를 접근 위한 헤더 포인터. added by NK
	P_SCORE score; // calcurate.c 에서 최초로 메모리 할당. 그 외에서는 할당 금지 절대!! added by NK
} player_info;
/* 플레이어 정보 구조체(우종이가 더 추가해야함) */


void init();
P_HWATOO init_pae();
P_HWATOO give_pae();
void swing_chongtong_check(player_info *info, P_HWATOO);

void call_show_pae();
void show_pae(P_HWATOO, char, player_info *info);

#endif // _GOSTOP_
