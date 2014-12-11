/*
 * util.c
 *
 *  Created on: 2014. 12. 6.
 *      Author: NCri
 */
#include<stdio.h>
#include "setting.h"

void delete_pae(P_HWATOO header, P_HWATOO del_pae){
	P_HWATOO front = header; // 현재 노드의 이전 노드를 가리킬 변수.

	if(del_pae == NULL){
		printf("ERROR : 삭제할 패가 없습니다.\n");
		return;
	}
	while(header != NULL){
		if(header->id == del_pae->id){
			// 삭제 완료.
			front->next = header->next;
			// 삭제 된 노드의 next는 NULL로 해줘야 한다.
			del_pae->next = NULL;
			return;
		}
		front = header;
		header = header->next;
	}
}
void append_pae(P_HWATOO src, P_HWATOO dest){
	P_HWATOO header = src;
	P_HWATOO tail = src;

	// 꼬리 까지 이동.
	while(tail->next != NULL){
		tail = tail->next;
	}
	// src 꼬리의 dest의 헤드를 넣는다.
	tail->next = dest;
}

