/*
	iptn
	File:/test.c
	Date:2021.10.04
	For __ONLY__ x86-64.
	By MIT License.
	Copyright (c) 2021 Suote127.All rights reserved.
*/

#include<stdio.h>
#include<stdint.h>

#include"iptn.h"

iptn_define(add,7)
	0x48,0x89,0xf8,			// mov	%rdi,	%rax
	0x48,0xff,0xc0,			// inc	%rax
	0xc3				// retq
iptn_end

int main(void)
{
	Iptn_State state;
	iptn_init(state,4096);

	iptn_emit(state,iptn_label(add),7);

	iptn_spawn(state);

	int result = iptn_do(state,int (*)(int),4);
	printf("%d\n",result);

	iptn_destroy(state);

	return 0;
}
