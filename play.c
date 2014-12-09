#include<stdio.h>
#include<stdlib.h>
#include"setting.h"
#include "game.h"
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
//cut -> next = NULL이된다.
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
//바닥 패에서 내는 패와 몇개가 맞는 지 저장하고, 맞는 패의 주소를 리턴
P_HWATOO countMatch(P_HWATOO output,int * count)
{
	extern P_HWATOO PAE_head;	//바닥패
	P_HWATOO current = PAE_head;	//탐색을 위한 임시 포인터 초기화
	P_HWATOO match = NULL;

	while(current != NULL)	//바닥에 있는 패 에 맞는 것이 있는지 검사
	{
		if(current -> no == output->no)
		{
			if(*count == 0)	//처음으로 맞는것이 있는경우
			{
				match = current;	//맞는 패의 포인터 저장
			}
			*count = *count + 1;	//count증가
		}
		current = current -> next;	//current포인터 증가
	}
	return match;

}
P_HWATOO appendMatch(P_HWATOO match,P_HWATOO output,int * count)
{
	int cmd =0;
	extern P_HWATOO PAE_head;
	if(*count == 2)
	{	
		printf("다음중 패 하나를 선택하세요\n");
		while(1)
		{
			printf("1) %d %s(%d)\n", match -> no, match -> name, match -> isSSangpi);
			printf("2) %d %s(%d)\n", match -> next -> no, match -> next -> name, match -> next -> isSSangpi);
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
		*count =1;
		PAE_head = cutList(PAE_head, match, *count);	//바닥 패에서 맞은 패 자르기
		match = appendList(match,output);
	}
	else if(*count == 1 )
	{
		PAE_head = cutList(PAE_head, match, *count);	//바닥패에서 맞은 패만 잘라오기
		match = appendList(match,output);	//match리스트 연결
	}
	else if(*count == 0)
	{
		PAE_head = appendList(PAE_head, output);
		return NULL;
	}
	else	//3개인 경우
	{
		
		PAE_head = cutList(PAE_head, match, *count);
		match = appendList(match,output);
	}
	return match;
}
// output : 사용자가 낸패 (next 는 NULL값)
void matchPae(P_HWATOO output,player_info * info )
{
	extern P_HWATOO PAE_head;
	extern P_HWATOO head;
	
	P_HWATOO up_pae = NULL;
	P_HWATOO match = NULL, current = PAE_head,up_match = NULL,temp = NULL;
	int count = 0,cmd = 0;
	
	match = countMatch(output, &count);
	match = appendMatch(match,output,&count);
	
	
	//더미에서 화투 뒤집기
	up_pae = selectPae(head,1);
	head = cutList(head,up_pae,1);

	printf("뒤집은 패 번호 : %d 이름 : %s(%d)\n",up_pae->no, up_pae->name, up_pae->isSSangpi);
	count = 0;	
	up_match = countMatch(up_pae, &count);

	if(count == 0)	//쌀수도 있는  경우
	{

		if(match != NULL && match -> no == up_pae -> no)	//싼경우
		{
			match = appendList(match,up_pae);

		}
		else	//안싼경우
		{
			up_match = appendMatch(up_match,up_pae,&count);
		}
	}
	else//싸지 않은경우
	{	
		up_match = appendMatch(up_match,up_pae,&count);
	}
	
	match = appendList(match, up_match);
	//match 는 짝이 맞는 모든 화투패
	count = 0;
	temp = match;
	while(temp != NULL)
	{
		count++;
		temp = temp -> next;
	}
	//만약에 count가 3이면 싼거 라서 못먹음
	//
	if(count == 3)
	{
		PAE_head = appendList(PAE_head,match);
		PAE_head = sortList(PAE_head);
		printf("쌈\n\n");
	}
	else if(count == 0)	//바닥에 해딩
	{
		PAE_head = appendList(PAE_head,match);
		PAE_head = sortList(PAE_head);
	}
	else
	{
		//먹는 경우
		// 만약 싼걸 먹거나, 따닥 일 경우 상대방의 패를 빼온다.
		if (count >= 4)
		{
			// 현재 턴의 플레이어를 제외한 나머지 플레이어에게서
			// '피' 패를 가져온다.
			count = 0;
			temp = match;
			temp - sortList(temp);
			while(temp -> next != NULL)
			{
				if(temp -> no == temp -> next -> no)
				{
					count++;
				}
				temp = temp -> next;
			}
			if(count == 3)
			{
				//info -> head_pae = appendList(info->head_pae, steal_pi(info));
			}
		}

		info -> head_pae = appendList( info -> head_pae,match );
		info -> head_pae = sortList(info->head_pae);
	}
		
}

