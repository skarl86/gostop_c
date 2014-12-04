#include "setting.h"

/* 전역 변수 선언 */
P_HWATOO head = NULL; // 화투더미
P_HWATOO A_head = NULL, B_head = NULL, C_head = NULL, PAE_head = NULL; // 사용자 패
player_info A_player, B_player, C_player; // 사용자 정보
char winner = 'A';

int main()
{
	char cmd[5] = ""; // 명령어 변수 
	srand((unsigned)time(NULL));
	
	init(); // 패 셋팅
	call_show_pae(); // 패 출력 

	printf("명령 : ");
	scanf("%s", cmd);

	while (strcmp(cmd, "e"))
	{
		if (!strcmp(cmd, "g"))
			printf("고!!\n");
		else if (!strcmp(cmd, "s"))
			printf("스톱\n");
		else if (!strcmp(cmd,"b"))
			printf("잔고보기\n");
		else if (!strcmp(cmd, "h"))
			printf("설명보기\n");
		else if (*cmd >= 49 && *cmd <= 55 && strlen(cmd) == 1)
		{
			printf("낼화투선택\n");
			call_show_pae();
		}
		else if (*cmd == 57 && strlen(cmd) == 1)
			printf("십을 피로 또는 십으로 이동\n");
		else if (!strcmp(cmd, "save"))
			printf("저장\n");
		else if (!strcmp(cmd, "load"))
			printf("로드\n");
		else 
			printf("잘못입력하셨습니다.\n");

		printf("명령 : ");
		scanf("%s", cmd);
	}	
	printf("고스톱이 종료되었습니다.\n");
	return 0;
}

/* 사용자패와 깔린 패 출력 함수 */
void call_show_pae()
{
	/* 패 출력 */
	show_pae(A_head, 'A', &A_player);// A패 출력 
	show_pae(B_head, 'B', &B_player); // B패 출력
	show_pae(C_head, 'C', &C_player); // C패 출력
	show_pae(PAE_head, 'P', &C_player); // 깔린 패 출력
}

/* 패 출력 함수 */
void show_pae(P_HWATOO h, char player, player_info *info)
{
	
	if (!(player == 'P')) // Plyaer 화투패
	{

		if(winner == player) // 사용자 순서표시 수정필요!!
			printf("*%c", player);
		else
			printf(" %c", player);

		if (info -> isSwing) // 흔들었을 경우
			printf(" 흔듦   : 패) ");
		else
			printf("        : 패) ");
	}
	else // 깔린 패
		printf("깔린 패) ");

	for (; h; h = h -> next)
		printf("%d%s  ", h->no, h->name);

	printf("\n\n");
}

