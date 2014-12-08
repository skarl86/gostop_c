#include "setting.h"
#include "calcurate.h"
//#include "game.h"

/* 전역 변수 선언 */
P_HWATOO head = NULL; // 화투더미
P_HWATOO A_head = NULL, B_head = NULL, C_head = NULL, PAE_head = NULL; // 사용자 패
player_info A_player, B_player, C_player; // 사용자 정보

char winner = 'A';

int main() {
	char cmd[5] = "\0"; // 명령어 변수
	srand((unsigned) time(NULL));

	init(); // 패 셋팅
	call_show_pae(); // 패 출력

	printf("명령 : ");
	scanf("%s", cmd);

	while (strcmp(cmd, "e")) {
		if (!strcmp(cmd, "g"))
			printf("고!!\n");
		else if (!strcmp(cmd, "s"))
			printf("스톱\n");
		else if (!strcmp(cmd, "b"))
			printf("잔고보기\n");
		else if (!strcmp(cmd, "h"))
			printf("설명보기\n");
		else if (*cmd >= 49 && *cmd <= 55 && strlen(cmd) == 1) {
			start_play(winner, atoi(cmd));	//play시작
		} else if (*cmd == 57 && strlen(cmd) == 1) {
			printf("7이상의 숫자 입력");
		} else if (!strcmp(cmd, "save"))
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
int select_go_stop() {
	int input;
	printf("고 하시겠습니까?(g: Go s: Stop)\n");
	getchar();
	while (1) {
		input = getchar();
		if (input == 'g')
			return 1;
		else if (input == 's')
			return 0;
		printf("잘못 입력하셨습니다. \n ");
	}

}
//플레이 하게 하는 함수
void start_play(char input, int cmd) {
	P_HWATOO p = NULL, up_p = NULL;
	if (input == 'A') {
		/* 사용자가 낸패의 관한 처리 */
		p = selectPae(A_head, cmd);
		A_head = cutList(A_head, p, 1);
		matchPae(p, &A_player);
		//사용자가 낸패의 관한 처리

		calcurate(&A_player);
		/*더미패에서 뒤집은거에 관한 처리 */

		// 계산 후 show를 해야한다. 꼭!! 이유는 계산이 끝나야 플레이어 점수가 갱신되기 때문.
		//더미패에서 뒤집은거에 관한 처리
		// 승리조건이 성립한다면.
		if (is_win(&A_player)) {
			// 고 또는 스톱 처리 부탁.
			if (!select_go_stop()) {
				printf("최종 승리점수 : %d\n",
						update_player_score_and_money(&A_player, &B_player,
								&C_player));
				init();
				call_show_pae();
			} else {
				winner = 'B';
				call_show_pae();
			}
		} else {
			winner = 'B';
			call_show_pae();
		}
	} else if (input == 'B') {
		/* 사용자가 낸패의 관한 처리 */
		p = selectPae(B_head, cmd);
		B_head = cutList(B_head, p, 1);
		matchPae(p, &B_player);
		//사용자가 낸패의 관한 처리

		// 계산 후 show를 해야한다. 꼭!! 이유는 계산이 끝나야 플레이어 점수가 갱신되기 때문.
		calcurate(&B_player);
		//더미패에서 뒤집은거에 관한 처리

		// 승리조건이 성립한다면.
		if (is_win(&B_player)) {
			// 고 또는 스톱 처리 부탁.
			if (!select_go_stop()) {
				printf("최종 승리점수 : %d\n",
						update_player_score_and_money(&B_player, &A_player,
								&C_player));
				init();
				call_show_pae();
			} else {
				winner = 'C';
				call_show_pae();
			}
		} else {
			winner = 'C';
			call_show_pae();
		}

	} else if (input == 'C') {
		/* 사용자가 낸패의 관한 처리 */
		p = selectPae(C_head, cmd);
		C_head = cutList(C_head, p, 1);
		matchPae(p, &C_player);
		//사용자가 낸패의 관한 처리

		// 계산 후 show를 해야한다. 꼭!! 이유는 계산이 끝나야 플레이어 점수가 갱신되기 때문.
		calcurate(&C_player);
		//더미패에서 뒤집은거에 관한 처리

		// 승리조건이 성립한다면.
		if (is_win(&C_player)) {
			// 고 또는 스톱 처리 부탁.
			if (!select_go_stop()) {		// 스톱.
				printf("최종 승리점수 : %d\n",
						update_player_score_and_money(&C_player, &A_player,
								&B_player));
				init();
				call_show_pae();
			} else // 고.
			{
				winner = 'A';
				call_show_pae();
			}
		} else {
			winner = 'A';
			call_show_pae();
		}
	}

}
/* 사용자패와 깔린 패 출력 함수 */
void call_show_pae() {
	/* 패 출력 */
	show_ex_pae(A_head, OWN_PAE, &A_player); // A 플레이어 가진 패 출력.
	show_ex_pae(B_head, OWN_PAE, &B_player); // B 플레이어 가진 패 출력.
	show_ex_pae(C_head, OWN_PAE, &C_player); // C 플레이어 가진 패 출력.

	show_ex_pae(PAE_head, PLACE_PAE, NULL); // 깔린 패 출력

	show_ex_pae(A_player.head_pae, GET_PAE, &A_player); // A플레이어 먹은 패 출력.
	show_ex_pae(B_player.head_pae, GET_PAE, &B_player); // A플레이어 먹은 패 출력.
	show_ex_pae(C_player.head_pae, GET_PAE, &C_player); // A플레이어 먹은 패 출력.
}

void show_ex_pae(P_HWATOO h, SHOW_TYPE type, player_info *info) {
	if (OWN_PAE == type) // 가진 패.
			{
		if (winner == info->id[0]) // 사용자 순서표시 수정필요!!
			printf("*%c", info->id[0]);
		else
			printf(" %c", info->id[0]);

		if (info->isSwing) // 흔들었을 경우
			printf(" 흔듦   : 패) ");
		else
			printf("        : 패) ");
	}
	if (PLACE_PAE == type)
		// 깔린 패.
		printf("깔린 패) ");
	if (GET_PAE == type)
		// 먹은 패.
		printf("%c 가 먹은패(%d) ", info->id[0], info->total_score);

	for (; h; h = h->next)
		printf("%d%s  ", h->no, h->name);

	printf("\n\n");
}

/* 패 출력 함수 */
void show_pae(P_HWATOO h, char player, player_info *info) {

	if (!(player == 'P') && !(player == 'E')) // Plyaer 화투패
			{

		if (winner == player) // 사용자 순서표시 수정필요!!
			printf("*%c", player);
		else
			printf(" %c", player);

		if (info->isSwing) // 흔들었을 경우
			printf(" 흔듦   : 패) ");
		else
			printf("        : 패) ");
	} else if (player == 'P') // 깔린 패
		printf("깔린 패) ");
	else
		printf("%c 가 먹은패 ", player);
	for (; h; h = h->next)
		printf("%d%s  ", h->no, h->name);

	printf("\n\n");
}

