#include "setting.h"

/* 화투패 초기 셋팅 함수 */
void init() {
	extern P_HWATOO head; // 화투더미
	extern player_info A_player, B_player, C_player;
	extern P_HWATOO A_head, B_head, C_head, PAE_head;
	extern winner;
	P_HWATOO temp;
//	extern P_GAME m_game_info;

	/* 게임 정보 초기화 */
//	m_game_info = (P_GAME) malloc(sizeof(GAME));
//	m_game_info->winner_score = 0;
	reset_score(&A_player);
	reset_score(&B_player);
	reset_score(&C_player);

	/* 플레이어 초기화.*/
	A_player.id[0] = 'A';
	B_player.id[0] = 'B';
	C_player.id[0] = 'C';

	//player정보 초기화
	A_player.head_pae = NULL;
	B_player.head_pae = NULL;
	C_player.head_pae = NULL;
	/* 초기 화투더미 생성 */
	head = init_pae();

	/* 패 돌리기 */
	A_head = give_pae(); // A에게 패돌리기
	B_head = give_pae(); // B에게 패돌리기
	C_head = give_pae(); // C에게 패돌리기
	PAE_head = give_pae(); //패 깔기
	//바닥패에 하나를 더미패에 넣기
	temp = PAE_head->next;
	PAE_head->next = NULL;
	PAE_head->next = head;
	head = PAE_head;
	PAE_head = temp;

	/* 흔들기와 총통 체크 함수 호출 */
	//swing_chongtong_check(&A_player, A_head);
	//swing_chongtong_check(&B_player, B_head);
	//swing_chongtong_check(&C_player, C_head);
	// 총통 (점수 계산하고 끝내는거 추가해야함!!)
	/*
	 if (A_player.isChongtong)
	 winner = 'A';
	 else if (B_player.isChongtong)
	 winner = 'B';
	 else if (C_player.isChongtong)
	 winner = 'C';
	 */
}

/* 초기 화투 더미 셋팅 함수 */
P_HWATOO init_pae() {
	P_HWATOO head = NULL;
	P_HWATOO new_pae = NULL;
	P_HWATOO current = NULL;
	int i, num = 1;
	char gubun[48][4] = { "광", "오", "피", "피", "십", "오", "피", "피", "광", "오", "피",
			"피", "십", "오", "피", "피", "십", "오", "피", "피", "십", "오", "피", "피",
			"십", "오", "피", "피", "광", "십", "피", "피", "피", "오", "피", "피", "십",
			"오", "피", "피", "광", "피", "피", "피", "광", "십", "오", "피" };

	for (i = 0; i < 48; i++) {
		new_pae = (P_HWATOO) malloc(sizeof(HWATOO));
		new_pae->id = i; // 고유번호 셋팅
		new_pae->no = num; // 월 셋팅
		strcpy(new_pae->name, gubun[i]); // 광 or 피 or 십 or 오 셋팅

		if (i == 32 || i == 41 || i == 47) // 쌍피셋팅
			new_pae->isSSangpi = true;
		else
			new_pae->isSSangpi = false;

		new_pae->next = NULL;
		// 링크 연결
		if (head == NULL) {

			head = new_pae;
		} else {
			current = head;
			while (current->next != NULL)
				current = current->next;

			current->next = new_pae;
		}
		if ((i + 1) % 4 == 0) // 월 증가
			num++;
	}

	return head;
}

/* 패돌리기 함수 */
P_HWATOO give_pae() {
	extern P_HWATOO head; // 전역변수 화투더미 참조 선언
	P_HWATOO dummy_head = head;
	P_HWATOO player_head = NULL;
	P_HWATOO current = NULL;
	P_HWATOO prev = NULL;
	P_HWATOO player_prev = NULL;
	int randomNum;
	int i = 0;

	//srand((unsigned)time(NULL));
	randomNum = rand() % 47;
	while (i < 7) // 패 7개 돌리기
	{
		//	printf(" i = %d, random = %d, dummy = %d\n", i, randomNum, head ->id);
		if (randomNum == (head->id)) // 일치한 패를 찾은 경우
				{

			if (player_head == NULL) // 처음 패를 받은 경우
			{
				player_head = head;
				// 연결 끊기
				if (head != dummy_head)
					prev->next = head->next;
				else // 화투더미의 첫번째 패를 받은 경우
				{
					dummy_head = head->next; //화투 더미 헤드 셋팅
					prev = NULL;
				}
				player_head->next = NULL;
				player_prev = player_head;
			} else {
				current = player_head;

				// 화투 더미에서 연결 끊기
				if (head != dummy_head)
					prev->next = head->next;
				else {
					dummy_head = head->next;
					prev = NULL;
				}

				// 화투패 패번호로 정렬
				if (head->id < player_head->id) // head가 player_head보다 작은 경우 player_head 다시 셋팅
						{
					player_head = head;
					head->next = current;
				} else {
					while ((head->id > current->id) && current->next != NULL) {
						player_prev = current;
						current = current->next;
					}
					if (head->id > current->id && current->next == NULL) {
						current->next = head;
						head->next = NULL;
					} else if (head->id < current->id) {
						player_prev->next = head;
						head->next = current;
					} else {
						head->next = current->next;
						current->next = head;
					}
				}
			}
			head = dummy_head; // 처음부터 검색하기 위해
			randomNum = rand() % 47;
			i++;
		} else {
			if (head->next != NULL) {
				prev = head;
				head = head->next;
			} else // 끝까지 돌았는데 못찾은 경우
			{
				randomNum = rand() % 47;
				head = dummy_head;
			}
		}
	}

	head = dummy_head; // 화투 더미 head값 다시 셋팅
	return player_head;
}

/* 흔들기와 총통 체크 함수 */
void swing_chongtong_check(player_info *player, P_HWATOO player_head) {
	int i, j, cnt = 0;
	bool isSwing = false;
	bool isChongtong = false;
	P_HWATOO temp = player_head;	//임시 포인터 선언
	P_HWATOO arr_hwatoo[7];

	for (i = 0; i < 7; i++) {
		arr_hwatoo[i] = temp;
		temp = temp->next;
	}
	//배열에 패 초기화
	for (i = 0; i < 6; i++) {
		for (j = i + 1; j < 7; j++) {
			if (arr_hwatoo[i]->no == arr_hwatoo[j]->no) {
				cnt++;
			}
		}
		if (cnt == 2) {
			isSwing = true;
			break;
		} else if (cnt == 3) {
			isChongtong = true;
			break;
		}
		cnt = 0;
	}
	player->isSwing = isSwing;
	player->isChongtong = isChongtong;
}

