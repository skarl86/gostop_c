#ifndef _GOSTOP_
#define _GOSTOP_
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include<time.h>

#define GWANG 				"광"
#define PI					"피"
#define WO					"오"
#define SIP					"십"

typedef enum show{
	GET_PAE, // 먹은 패.
	OWN_PAE, // 가진 패.
	PLACE_PAE // 깔린 패.
}SHOW_TYPE;

struct hwatoo
{
	int id; // 패의 고유번호
	int no; // 패의 월
	char name[4]; // 광 or 피 or 십 or 오
	bool isSSangpi; // 쌍피인지 구분
	struct hwatoo *next;
};
typedef struct hwatoo HWATOO;
typedef struct hwatoo* P_HWATOO;

typedef struct score
{
	int gwang; 	// 광 점수.
	int pi;		// 피 점수.
	int sip;	// 10 점수.
	int wo;		// 5 점수.
}SCORE, *P_SCORE;
/* 플레이어의 점수 정보 구조체.*/

/* 플레이어 정보 구조체(우종이가 더 추가해야함) */
typedef struct player_info
{
	char id[2]; // 알파벳으로 구성된 플레이어 고유 번호.
	bool isSwing; // 흔듦
	bool isChongtong; // 총통
	P_HWATOO head_pae; // 먹은 패.
	P_SCORE score; // 각각 광,피,10,5 점수.
	int total_score; // 총 점수.
} player_info;

typedef struct game
{
	char winner[2];
}GAME, *P_GAME;

void init();
P_HWATOO init_pae();
P_HWATOO give_pae();
void swing_chongtong_check(player_info *info, P_HWATOO);

void call_show_pae();
void show_ex_pae(P_HWATOO h, SHOW_TYPE type, player_info *info);
void show_pae(P_HWATOO, char, player_info *info);
void start_play(char input, int cmd);
extern P_HWATOO selectPae(P_HWATOO player, int number);
extern P_HWATOO cutList(P_HWATOO head, P_HWATOO cut,int count);
extern P_HWATOO appendList(P_HWATOO head, P_HWATOO append);
extern P_HWATOO sortList(P_HWATOO head);
extern void matchPae(P_HWATOO output, player_info * info);
extern P_HWATOO countMatch(P_HWATOO, int *);
extern P_HWATOO appendMatch(P_HWATOO,P_HWATOO ,int *);
extern void matchPae(P_HWATOO, player_info *);

#endif // _GOSTOP_
