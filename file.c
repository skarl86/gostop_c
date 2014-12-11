#include <stdio.h>
#include "setting.h"

void saveScore(char* fname, P_SCORE score)
{
	
	FILE *save = NULL;

	save = fopen(fname, "wt");
	if (save == NULL)
		puts("save fopen() fail!");

	fprintf(save, "%d %d %d %d\n", score->gwang, score->pi, score->sip, score->wo);
	fclose(save);
}

void loadScore(char* fname, P_SCORE score)
{
	FILE *load = NULL;
	int gwang; 	// 광 점수.
	int pi;		// 피 점수.
	int sip;	// 10 점수.
	int wo;		// 5 점수.


	load = fopen(fname, "rt");
	if (load == NULL) puts("load fopen() fail!");
	puts("fopen success!");

	if(fscanf(load, "%d %d %d %d\n", &gwang, &pi, &sip, &wo) != EOF)
	{
		puts("fscanf success!");
		score->gwang = gwang;
		printf("%d ", gwang);
		score->pi = pi;
		printf("%d", pi);
		score->sip = sip;
		printf("%d", sip);
		score->wo = wo;
		printf("%d\n", wo);
	}

	fclose(load);

}

void loadPae(char* file_name, P_HWATOO *  load_head)
{
	FILE *load = NULL;
	//P_HWATOO temp_head = NULL;
	P_HWATOO new_pae = NULL;
	P_HWATOO current = NULL;

	int id; // 패의 고유번호
	int no; // 패의 월
	char name[4]; // 광 or 피 or 십 or 오
	char isSSangpi=0; // 쌍피인지 구분
	int ctr =0;
	load = fopen(file_name, "rt");
	if (load == NULL) puts("load fopen() fail!");
		
	while(fscanf(load, "%d %d %s %c\n", &id, &no, name, &isSSangpi) != EOF)
	{
		new_pae = (P_HWATOO) malloc(sizeof(HWATOO));
		new_pae->id = id; // 고유번호 셋팅
		new_pae->no = no; // 월 셋팅
		new_pae->isSSangpi = isSSangpi - '0';
		strcpy(new_pae->name, name);
		new_pae->next = NULL;
		//new_pae생성
		if (ctr == 0)//첫패인 경우 
		{
			*load_head = new_pae;	//parameter로 받은 head에 연결
			current =  *load_head; //탐색 포인터 초기화
			ctr++;
		}
		else
		{
			//current = temp_head;
			while (current->next != NULL)
				current = current->next;

			current->next = new_pae;
		}
		printf("%d %d %s %d\n", id, no, name, isSSangpi);
	}
	fclose(load);
}

void savePae(char* fname, P_HWATOO save_head)
{
	FILE *save = NULL;
	P_HWATOO save_ptr = NULL;

	save = fopen(fname, "wt");
	if (save == NULL) puts("save fopen() fail!");

	save_ptr = save_head;
	while (save_ptr != NULL)
	{
		fprintf(save, "%d %d %s %d\n", save_ptr->id, save_ptr->no,	save_ptr->name, save_ptr->isSSangpi);
		save_ptr = save_ptr->next;
	}
	fclose(save);
}

void savePlayer(char* fname, char* fname_head_pae, char* fname_score, player_info *player)
{
	FILE *save = NULL;

	save = fopen(fname, "wt");
	if (save == NULL) puts("save fopen() fail!");

	printf("%s %d %d %d %d %d %d\n",player->id,
			player->isSwing,
			player->isChongtong,
			player->total_score,
			player->go_count,
			player->total_score_when_go,
			player->money);
	fprintf(save, "%s %d %d %d %d %d %d\n",
			player->id,
			player->isSwing,
			player->isChongtong,
			player->total_score,
			player->go_count,
			player->total_score_when_go,
			player->money);

	savePae(fname_head_pae, player->head_pae);
	saveScore(fname_score, player->score);
	fclose(save);
}

void saveWinner(char* fname)
{
	extern char winner;
	FILE *fop;

	fop = fopen(fname,"wt");
	fprintf(fop,"%c\n",winner);
	printf("%c\n",winner);
}
void save(P_HWATOO pilehead, P_HWATOO ahead, P_HWATOO bhead, P_HWATOO chead, P_HWATOO paehead,
		player_info *aplayer, player_info *bplayer, player_info *cplayer)
{
	char file_name[][30] = {"pile.txt", "paehead.txt",
							"ahead.txt", "aplayerinfo.txt", "aplayerpae.txt", "ascore.txt",
							"bhead.txt", "bplayerinfo.txt", "bplayerpae.txt", "bscore.txt",
							"chead.txt", "cplayerinfo.txt", "cplayerpae.txt", "cscore.txt"};

	savePae(file_name[0], pilehead);
	savePae(file_name[2], ahead);
	savePae(file_name[6], bhead);
	savePae(file_name[10], chead);
	savePae(file_name[1], paehead);
	puts("save aplayer");
	savePlayer(file_name[3], file_name[4], file_name[5], aplayer); 		// aplater
	puts("save bplayer");
	savePlayer(file_name[7], file_name[8], file_name[9], bplayer);		// bplayer
	puts("save cplayer");
	savePlayer(file_name[11], file_name[12], file_name[13], cplayer);	// cplayer
	puts("save winner infomation");
	saveWinner("winner.txt");
}

void loadPlayer(char* fname, char* fname_player_head_pae, char* fname_score, player_info *load_player)
{
	FILE *load = NULL;

	char id[2]; // 알파벳으로 구성된 플레이어 고유 번호.
	char isSwing; // 흔듦
	char isChongtong; // 총통
	int total_score; // 총 점수.
	int go_count; // GO 카운트.
	int total_score_when_go; // GO했을때 점수.
	int money; // 사용자 돈.

	load = fopen(fname, "rt");
	if (load == NULL) puts("load fopen() fail!");

	while(fscanf(load, "%s %c %c %d %d %d %d\n", id, &isSwing, &isChongtong, &total_score,
												&go_count, &total_score_when_go, &money) != EOF)
	{
		strcpy(load_player->id, id);
		load_player->isSwing = isSwing - '0';
		load_player->isChongtong = isChongtong - '0';
		load_player->total_score = total_score;
		load_player->go_count = go_count;
		load_player->money = money;
		printf("%s %d %d %d %d %d\n",
				load_player->id,
				load_player->isSwing,
				load_player->isChongtong,
				load_player->total_score,
				load_player->go_count,
				load_player->money);
	}

	puts("load player pae");

	//load_player->head_pae = (P_HWATOO)malloc(sizeof(HWATOO));
	load_player->score = (P_SCORE)malloc(sizeof(SCORE));
	loadPae(fname_player_head_pae, &(load_player->head_pae));

	puts("load player score");
	loadScore(fname_score, load_player->score);
	puts("loadScore success!");
	fclose(load);
}

void loadWinner(char * fname)
{
	extern char winner;
	FILE *fop;
	fop = fopen(fname,"rt");
	fscanf(fop,"%c",&winner);
	printf("%c\n",winner);

}	
void load(P_HWATOO pilehead, P_HWATOO ahead, P_HWATOO bhead, P_HWATOO chead, P_HWATOO paehead,
		player_info *aplayer, player_info *bplayer, player_info *cplayer)
{
	char file_name[][30] = {"pile.txt", "paehead.txt",
							"ahead.txt", "aplayerinfo.txt", "aplayerpae.txt", "ascore.txt",
							"bhead.txt", "bplayerinfo.txt", "bplayerpae.txt", "bscore.txt",
							"chead.txt", "cplayerinfo.txt", "cplayerpae.txt", "cscore.txt"};
	extern P_HWATOO head;
	extern P_HWATOO A_head;
	extern P_HWATOO B_head;
	extern P_HWATOO C_head;
	extern P_HWATOO PAE_head;
	

	pilehead = NULL;
	ahead = NULL;
	bhead = NULL;
	chead = NULL;
	paehead = NULL;
	aplayer -> head_pae = NULL;
	bplayer -> head_pae = NULL;
	cplayer -> head_pae = NULL;
	
	puts("pilehead load start");
	loadPae(file_name[0], &head);
	puts("ahead load start");
	loadPae(file_name[2], &A_head);
	puts("bhead load start");
	loadPae(file_name[6], &B_head);
	puts("chead load start");
	loadPae(file_name[10], &C_head);
	puts("paehead load start");
	loadPae(file_name[1], &PAE_head);
	puts("Aplayer load start");
	loadPlayer(file_name[3], file_name[4], file_name[5], aplayer);
	puts("Bplayer load start");
	loadPlayer(file_name[7], file_name[8], file_name[9], bplayer);
	puts("Cplayer load start");
	loadPlayer(file_name[11], file_name[12], file_name[13], cplayer);
	puts("Winner load start");
	loadWinner("winner.txt");
	puts("load success!");
}

