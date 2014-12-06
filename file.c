#include <stdio.h>
#include "setting.h"

void savePae(char* file_name, P_HWATOO save_head)
{
	FILE *save = NULL;
	P_HWATOO save_ptr = NULL;

	save = fopen(file_name, "wt");
	if (save == NULL) puts("save fopen() fail!");

	save_ptr = save_head;
	while (save_ptr != NULL)
	{
		fprintf(save, "%d %d %s %d\n", save_ptr->id, save_ptr->no,	save_ptr->name, save_ptr->isSSangpi);
		save_ptr = save_ptr->next;
	}
	fclose(save);
}

void savePlayer(char* file_name, player_info *player)
{
	FILE *save = NULL;
	save = fopen(file_name, "wt");
	if (save == NULL) puts("save fopen() fail!");

	fprintf(save, "%d %d\n", player->isSwing, player->isChongtong);
	fclose(save);
}

void save(P_HWATOO pilehead, P_HWATOO ahead, P_HWATOO bhead, P_HWATOO chead, P_HWATOO paehead,
		player_info *aplayer, player_info *bplayer, player_info *cplayer)
{
	char file_name[][10] = {"pile.txt",	"a.txt", "b.txt","c.txt", "pae.txt",
							"aplayer", "bplayer", "cplayer"};

	savePae(file_name[0], pilehead);
	savePae(file_name[1], ahead);
	savePae(file_name[2], bhead);
	savePae(file_name[3], chead);
	savePae(file_name[4], paehead);
	savePlayer(file_name[5], aplayer);
	savePlayer(file_name[6], bplayer);
	savePlayer(file_name[7], cplayer);
}

void loadPlayer(char* file_name, player_info *load_player)
{
	FILE *load = NULL;

	char isSwing; // 흔듦
	char isChongtong; // 총통

	load = fopen(file_name, "rt");
	if (load == NULL) puts("load fopen() fail!");

	while(fscanf(load, "%c %c\n", &isSwing, &isChongtong) != EOF)
	{
		load_player->isSwing = isSwing - '0';
		load_player->isChongtong = isChongtong - '0';
	}

	printf("player : %d %d\n", load_player->isSwing, load_player->isChongtong);

	fclose(load);
}

void loadPae(char* file_name, P_HWATOO load_head)
{
	FILE *load = NULL;
	P_HWATOO temp_head = NULL;
	P_HWATOO new_pae = NULL;
	P_HWATOO current = NULL;

	int id; // 패의 고유번호
	int no; // 패의 월
	char name[4]; // 광 or 피 or 십 or 오
	char isSSangpi=0; // 쌍피인지 구분

	load = fopen(file_name, "rt");
	if (load == NULL) puts("load fopen() fail!");


	while(fscanf(load, "%d %d %s %c\n", &id, &no, name, &isSSangpi) != EOF)
	{
		new_pae = (P_HWATOO)malloc(sizeof(HWATOO));
		new_pae->id = id; // 고유번호 셋팅
		new_pae->no = no; // 월 셋팅
		new_pae -> isSSangpi = isSSangpi - '0';
		strcpy(new_pae -> name, name);

		if (temp_head == NULL)
			temp_head = new_pae;
		else
		{
			current = temp_head;
			while (current->next != NULL)
				current = current->next;

			current->next = new_pae;
		}
		printf("%d %d %s %d\n", new_pae->id, new_pae->no, new_pae -> name, new_pae -> isSSangpi);
	}
	printf("\n");

	load_head = temp_head;
	fclose(load);
}

void load(P_HWATOO pilehead, P_HWATOO ahead, P_HWATOO bhead, P_HWATOO chead, P_HWATOO paehead,
		player_info *aplayer, player_info *bplayer, player_info *cplayer)
{
	char file_name[][10] = {"pile.txt",	"a.txt", "b.txt","c.txt", "pae.txt",
								"aplayer", "bplayer", "cplayer"};

	loadPae(file_name[0], pilehead);
	loadPae(file_name[1], ahead);
	loadPae(file_name[2], bhead);
	loadPae(file_name[3], chead);
	loadPae(file_name[4], paehead);
	loadPlayer(file_name[5], aplayer);
	loadPlayer(file_name[6], bplayer);
	loadPlayer(file_name[7], cplayer);
}
