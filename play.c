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

P_HWATOO cutList(P_HWATOO head,P_HWATOO cut)
{
	P_HWATOO current = NULL;	//탐색을 위한 포인터

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


	}
	current -> next = cut -> next;	//cut포인터 자르고 기존 list연결
	cut -> next = NULL;	//잘라낸 화투의 next NULL로 초기화
	return head;
}

P_HWATOO appendList(P_HWATOO head, P_HWATOO append)
{
	P_HWATOO current = NULL;	//탐색을 위한 포인터

	current = head;	//current포인터 초기화
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
