/*
 * util.c
 *
 *  Created on: 2014. 12. 6.
 *      Author: NCri
 */
#include<stdio.h>
#include "setting.h"

void delete_pae(P_HWATOO header, P_HWATOO del_pae){
	P_HWATOO front = header;

	if(del_pae == NULL){
		printf("ERROR : 삭제할 패가 없습니다.\n");
		return;
	}
	while(header != NULL){
		if(header->id == del_pae->id){
			// 삭제 완료.
			front->next = header->next;
			return;
		}
		front = header;
		header = header->next;
	}
}
void append_pae(P_HWATOO src, P_HWATOO dest){
	P_HWATOO header = src;
	P_HWATOO tail = src;

	while(tail->next != NULL){
		tail = tail->next;
	}
	// src 꼬리의 dest의 헤드를 넣는다.
	tail->next = dest;
}

