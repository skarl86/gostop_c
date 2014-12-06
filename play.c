#include<stdio.h>
#include"setting.h"
#include<stdlib.h>
P_HWATOO selectPae(P_HWATOO player,int number)
{
	int i = 0;
	P_HWATOO temp = player;	
	for(i; i < number - 1; i++)
	{
		if(temp -> next == NULL)
			return NULL;
		temp = temp -> next;	//player의 다음 링크 저장
	}
	return temp;

}

P_HWATOO cutList(P_HWATOO head,P_HWATOO cut,int count)
{
	P_HWATOO current = NULL;	//탐색을 위한 포인터

	//자를 패가 3개인 경우
	if(count == 3)
	{
		current = head;	//탐색 포인터 초기화
		if(current == cut)	//head의 패와 자르려는 패가 같은 경우
		{
			head = cut -> next -> next -> next;	//list연결
			cut -> next -> next -> next = NULL;
			return head;
		}
		while(current -> next != cut)	//연결을 끊을 포인터와 탐색 포인터가 같을때까지 반복
		{
			current = current -> next;	//current증가
			if(current == NULL)
			{
				return NULL;
			}

		}
		current -> next = cut -> next -> next -> next;
		cut -> next -> next -> next = NULL;
		return head;
		
	}
	else
	{
		//자를 패가 1개인 경우
		current = head;	//탐색 포인터 초기화
		if(current == cut)	//head의 패와 자르려는 패가 같은 경우
		{
			head = cut -> next;	//list연결
			cut -> next = NULL;
			return head;
		}
		while(current -> next != cut)	//연결을 끊을 포인터와 탐색 포인터가 같을때까지 반복
		{
			current = current -> next;	//current증가
			if(current == NULL)
			{
				return NULL;
			}

		}
		current -> next = cut -> next;	//cut포인터 자르고 기존 list연결
		cut -> next = NULL;	//잘라낸 화투의 next NULL로 초기화
		return head;
	}
}

P_HWATOO appendList(P_HWATOO head, P_HWATOO append)
{
	P_HWATOO current = NULL;	//탐색을 위한 포인터

	current = head;	//current포인터 초기화
	if(head == NULL)
	{
		head = append;
		return head;
	}
	while(current -> next != NULL)	//current 를 list의 끝까지 탐색
	{
		current = current -> next;	//current증가
	}
	current -> next = append;	//append추가
	return head;


}

P_HWATOO sortList(P_HWATOO head)
{
	int i,j,count = 0;
	P_HWATOO current = NULL;
	HWATOO temp;
	P_HWATOO * arr_hwatoo;
	current = head;

	while(current -> next != NULL)	//List의 객수 세기
	{
		count++;	//count증가
		current = current -> next;
	}
	count++; //count 1추가로 증가
	current = head;	//current포인터 초기화
	
	arr_hwatoo = (P_HWATOO *)malloc(sizeof(P_HWATOO) * count);	//P_HWATOO배열 할당
	for(i = 0; i < count; i++)
	{
		arr_hwatoo[i] = current;
		current = current-> next;

	}	

	for(i = 0; i < count; i++)
	{
		for(j = 0; j < count - 1; j++)
		{
			if( (arr_hwatoo[j] -> no) > (arr_hwatoo[j+1] -> no) )
			{
				memcpy(&temp,arr_hwatoo[j],sizeof(HWATOO));
				memcpy(arr_hwatoo[j],arr_hwatoo[j+1],sizeof(HWATOO));
				memcpy(arr_hwatoo[j+1],&temp,sizeof(HWATOO));
			}
		}
	}
	
	head = arr_hwatoo[0];
	current = head;
	for(i = 1; i < count; i++)
	{
		current -> next = arr_hwatoo[i];
		current = current -> next;
	}
	arr_hwatoo[count - 1] -> next = NULL;
	return head;

}

// output : 사용자가 낸패 (next 는 NULL값)
void matchPae(P_HWATOO output,player_info * info )
{
	extern P_HWATOO PAE_head;
	P_HWATOO match = NULL, current = PAE_head;
	int count = 0,cmd = 0;
	while(current != NULL)	//바닥에 있는 패 에 맞는 것이 있는지 검사
	{
		if(current -> no == output->no)
		{
			if(count == 0)	//처음으로 맞는것이 있는경우 
			{
				match = current;	//맞는 패의 포인터 저장
			}
			count++;	//count증가
		}
		current = current -> next;	//current포인터 증가
	}
	if(count == 2)
	{	
		printf("다음중 패 하나를 선택하세요\n");
		while(1)
		{
			printf("1) %d %s\n", match -> no, match -> name);
			printf("2) %d %s\n", match -> next -> no, match -> next -> name);
			scanf("%d",&cmd);
			if(cmd == 1)
			{
				getchar();
				break;
			}
			else if(cmd = 2)
			{
				match = match -> next;
				getchar();
				break;
			}
			getchar();
			printf("번호를 잘못 누르셨습니다\n");
		
		}
		count =1;
		PAE_head = cutList(PAE_head, match, count);	//바닥 패에서 맞은 패 자르기
		info -> head_pae = appendList(info -> head_pae, match);	//바닥패에서 맞은 패 먹은패 정보에 붙이기
		info -> head_pae = sortList(info-> head_pae);	//먹은패 정보 정렬
	}
	else if(count == 0)
	{
		PAE_head = appendList(PAE_head,output);	//바닥패에 낸패 붙이기
		PAE_head = sortList(PAE_head);
	}
	else
	{
		info -> head_pae = appendList(info -> head_pae, output);
		PAE_head = cutList(PAE_head, match, count);
		info -> head_pae = appendList(info -> head_pae, match);
		info -> head_pae = sortList(info-> head_pae);
	}
	
}

void show_eat_pae(player_info A_head, player_info B_head, player_info C_head)
{
	printf("A가 먹은 패 : ");
	if(A_head.head_pae != NULL)
	{
		for(;A_head.head_pae; A_head.head_pae = A_head.head_pae -> next)
		{
			printf("%d%s  ",A_head.head_pae -> no, A_head.head_pae -> name);
		}
	}
	printf("\n\n");
	if(A_head.head_pae != NULL)
	{
		printf("B가 먹은 패 : ");
		for(; B_head.head_pae; B_head.head_pae = B_head.head_pae -> next)
		{
			printf("%d%s  ",B_head.head_pae -> no, B_head.head_pae -> name);
		}
	}
	printf("\n\n");
	printf("C가 먹은 패 : ");

	if(A_head.head_pae != NULL)
	{
		for(; C_head.head_pae; C_head.head_pae = C_head.head_pae -> next)
		{
			printf("%d%s  ",C_head.head_pae -> no, C_head.head_pae -> name);
		}
	}
	printf("\n\n");

	

}
