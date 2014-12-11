#include "setting.h"
#include "calcurate.h"
#include "game.h"

/* 전역 변수 선언 */
P_HWATOO head = NULL; // 화투더미
P_HWATOO A_head = NULL, B_head = NULL, C_head = NULL, PAE_head = NULL; // 사용자 패
player_info A_player, B_player, C_player; // 사용자 정보

char winner = 'A';

int main() {
	char cmd[5] = "\0"; // 명령어 변수
	srand((unsigned) time(NULL));

	// 돈.
	A_player.money = 100000;
	B_player.money = 100000;
	C_player.money = 100000;

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
			show_help();
		else if (*cmd >= 49 && *cmd <= 55 && strlen(cmd) == 1) {
			start_play(winner, atoi(cmd));	//play시작
		} else if (*cmd == 57 && strlen(cmd) == 1) {
<<<<<<< HEAD
			select_sip_or_pi();
		} else if (!strcmp(cmd, "save")){
			save(head,A_head, B_head, C_head, PAE_head, &A_player, &B_player,&C_player);
		}
		else if (!strcmp(cmd, "load")){
			load(head,A_head, B_head, C_head, PAE_head, &A_player, &B_player, &C_player);
			call_show_pae();
		}
=======
			printf("7이상의 숫자 입력");
		} else if (!strcmp(cmd, "save"))
			save(A_head, B_head, C_head, PAE_head, &A_player, &B_player,
					&C_player);
		else if (!strcmp(cmd, "load"))
			load(A_head, B_head, C_head, PAE_head, &A_player, &B_player,
					&C_player);
>>>>>>> FETCH_HEAD
		else
			printf("잘못입력하셨습니다.\n");

		if (A_head == NULL && B_head == NULL && C_head == NULL) {
			//모든 패를 낸후 게임 재시작 사용자 정보및 기타 초기화 작업
			init();
			call_show_pae();
		}
		printf("명령 : ");
		scanf("%s", cmd);
	}
	printf("고스톱이 종료되었습니다.\n");
	return 0;
}
void select_sip_or_pi()
{
	P_HWATOO current;	//임시 포인터 선언

	if(winner == 'A')	//순서 확인
	{
		current = A_player.head_pae;	//current 포인터 해당 플레이어의 먹은 패로 초기화
		while(1)
		{
			if(current == NULL)
			{
				printf("옮길수 있는 구자리 화투를 먹지 못했습니다\n");
				return;
			}
			if(current->id == 32)
			{
				if(current->isSSangpi == false)	//이미 십으로 옮긴경우
				{
					printf("이미 옮기셨습니다\n");
					return;
				}
				else
				{
					current->isSSangpi = false;	//십으로 옮기기
					printf("구를 쌍피에서 십으로 옮겼습니다\n");
					return;
				}
			}
			else
			{
				current = current -> next;
			}
		}

	}
	else if(winner == 'B')	//순서 확인
	{
		current = B_player.head_pae;	//current 포인터 해당 플레이어의 먹은 패로 초기화
		while(1)
		{
			if(current == NULL)
			{
				printf("옮길수 있는 구자리 화투를 먹지 못했습니다\n");
				return;
			}
			if(current->id == 32)
			{
				if(current->isSSangpi == false)	//이미 십으로 옮긴경우
				{
					printf("이미 옮기셨습니다\n");
					return;
				}
				else
				{
					printf("구를 쌍피에서 십으로 옮겼습니다\n");
					current->isSSangpi = false;	//십으로 옮기기
					return;
				}
			}
			else
			{
				current = current -> next;
			}
		}

	}
	else if(winner == 'C')	//순서 확인
	{
		current = C_player.head_pae;	//current 포인터 해당 플레이어의 먹은 패로 초기화
		while(1)
		{
			if(current == NULL)
			{
				printf("옮길수 있는 구자리 화투를 먹지 못했습니다\n");
				return;
			}
			if(current->id == 32)
			{
				if(current -> isSSangpi == false)	//이미 십으로 옮긴경우
				{
					printf("이미 옮기셨습니다\n");
					return;
				}
				else
				{
					printf("구를 쌍피에서 십으로 옮겼습니다\n");
					current->isSSangpi = false;	//십으로 옮기기
					return;
				}
			}
			else
				current = current -> next;
			
		}

	}

}
void show_help()
{
	printf("키설명 \n");
	printf(" g : 고(자기 turn에 점수가 낫고 3점 이상일 때 할 수 있음)");
	printf(" s : 스톱(자기 turn에 점수가 났고 3점 이상 일 때 할수 있음, 이번 판 을 끝냄)\n");
	printf(" e : exit(프로그램 끝내기)\n");
	printf(" b : 게이머의 잔고 보기\n");
	printf(" 1 ~ 7 : 낼 화투 선택\n");
	printf( " 1 ~ 2 : 화투를 냈는데, 깔린 화투 중 무늬는 같지만 값이 다른 것이 있을 때 선택\n");
	printf(" 9 : 9 십을 피로 또는 십으로 이동(토글), 디폴트로는 피로 함, 각판에서 한번만 할 수 있음\n");
	printf(" save : 현재 상태를 파일에 저장\n");
	printf(" load : 파일에 저장된 상태를 읽어서 계속 게임 진행\n");
}
int select_go_stop(P_HWATOO head) {
	int input;
	if(head == NULL)
		return 0;
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
		if(p == NULL)	//사용자가 가지고있는 패 이상의 번호를 눌렀을경우
		{
			printf("없는 패를 선택하셨습니다\n");
			return;
		}
		A_head = cutList(A_head, p, 1);
		matchPae(p, &A_player);
		//판쓸 테스트
		if(PAE_head == NULL)
			A_player.head_pae = appendList(A_player.head_pae,steal_pi(&A_player));
		//사용자가 낸패의 관한 처리

		calcurate(&A_player);
		/*더미패에서 뒤집은거에 관한 처리 */

		// 계산 후 show를 해야한다. 꼭!! 이유는 계산이 끝나야 플레이어 점수가 갱신되기 때문.
		//더미패에서 뒤집은거에 관한 처리
		// 승리조건이 성립한다면.
		if (is_win(&A_player)) {
			// 고 또는 스톱 처리 부탁.
<<<<<<< HEAD
			if (!select_go_stop(A_head)) { //스톱..
=======
			if (!select_go_stop()) { //스톱..
>>>>>>> FETCH_HEAD
				update_player_score_and_money(&A_player, &B_player, &C_player);
				init();
				call_show_pae();
			} else { //고..
				A_player.go_count++;
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
		if(p == NULL)	//사용자가 가지고있는 패 이상의 번호를 눌렀을경우
		{
			printf("없는 패를 선택하셨습니다");
			return;
		}
		B_head = cutList(B_head, p, 1);
		matchPae(p, &B_player);
		//사용자가 낸패의 관한 처리

		// 계산 후 show를 해야한다. 꼭!! 이유는 계산이 끝나야 플레이어 점수가 갱신되기 때문.
		//판쓸 테스트
		if(PAE_head == NULL)
			B_player.head_pae = appendList(B_player.head_pae,steal_pi(&B_player));
		calcurate(&B_player);
		//더미패에서 뒤집은거에 관한 처리

		// 승리조건이 성립한다면.
		if (is_win(&B_player)) {
			// 고 또는 스톱 처리 부탁.
<<<<<<< HEAD
			if (!select_go_stop(B_head)) { // 스톱.
=======
			if (!select_go_stop()) { // 스톱.
>>>>>>> FETCH_HEAD
				update_player_score_and_money(&B_player, &A_player, &C_player);
				init();
				call_show_pae();
			} else { // 고.
				B_player.go_count++;
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
		if(p == NULL)	//사용자가 가지고있는 패 이상의 번호를 눌렀을경우
		{
			printf("없는 패를 선택하셨습니다");
			return;
		}
		C_head = cutList(C_head, p, 1);
		matchPae(p, &C_player);
		//사용자가 낸패의 관한 처리

		// 계산 후 show를 해야한다. 꼭!! 이유는 계산이 끝나야 플레이어 점수가 갱신되기 때문.
		//판쓸 테스트
		if(PAE_head == NULL)
			C_player.head_pae = appendList(C_player.head_pae,steal_pi(&C_player));
		calcurate(&C_player);
		//더미패에서 뒤집은거에 관한 처리

		// 승리조건이 성립한다면.
		if (is_win(&C_player)) {
			// 고 또는 스톱 처리 부탁.
<<<<<<< HEAD
			if (!select_go_stop(C_head)) {		// 스톱.
=======
			if (!select_go_stop()) {		// 스톱.
>>>>>>> FETCH_HEAD
				update_player_score_and_money(&C_player, &A_player, &B_player);
				init();
				call_show_pae();
			} else // 고.
			{
				C_player.go_count++;
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
<<<<<<< HEAD
	
///	printf("더미 Test\n\n");
=======
>>>>>>> FETCH_HEAD
//	show_ex_pae(head, PLACE_PAE, NULL); //더미 패 출력

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
		printf("%c 가 먹은패(%d) ) ", info->id[0], info->total_score);

	for (; h; h = h->next)
		printf("%d%s(%d)  ", h->no, h->name, h->isSSangpi);

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
		printf("%d%s(%d)  ", h->no, h->name, h->isSSangpi);

	printf("\n\n");
}

