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

