/*
	iptn
	ilo pi tenpo ni
	A simple dynamic code generate tool.
	By MIT License.
	Copyright (c) 2021 Suote127.All rights reserved.
	Date:2021.10.05
	https://gitee.com/suote_127/iptn
*/

#ifndef __IPTN_H_INC__
#define __IPTN_H_INC__

#include<stdlib.h>
#include<string.h>
#include<stdint.h>

#include<sys/mman.h>

typedef struct {
	uint8_t *code;
	uint8_t *now;
	size_t size;
}Iptn_State;

#define iptn_init(state,codeSize)					\
	do {								\
		(state).code	= mmap(NULL,(codeSize),			\
				       PROT_READ | PROT_WRITE,		\
				       MAP_PRIVATE | MAP_ANONYMOUS,	\
				       -1,0);				\
		(state).now	= (state).code;				\
		(state).size	= (codeSize);				\
	} while(0)

#define iptn_destroy(state) ((void)munmap((state).code,(state).size))

#define iptn_emit(state,p,size)						\
	do {								\
		memcpy((state).now,(p),(size));				\
		(state).now	+= (size);				\
	} while(0)

#define iptn_now(state) ((state).p)

#define iptn_emit8(state,p) iptn_emit(state,p,1)
#define iptn_emit16(state,p) iptn_emit(state,p,2)
#define iptn_emit32(state,p) iptn_emit(state,p,4)
#define iptn_emit64(state,p) iptn_emit(state,p,8)
#define iptn_emit48(state,p) iptn_emit(state,p,6)
#define iptn_emit128(state,p) iptn_emit(state,p,16)
#define iptn_emitvar(state,var) iptn_emit(state,&(var),sizeof(var))
#define iptn_emitlabel(state,label) iptn_emitvar(state,			\
						 __iptnCodeDefine_##label)

#define iptn_spawn(state) (void)mprotect((state).code,(state).size,	\
					 PROT_EXEC | PROT_READ)

#define iptn_do(state,type,...)						\
		(((type)((intptr_t)((state).code)))(__VA_ARGS__))	\

#define iptn_offset(state,offset) ((state).code + (offset))
#define iptn_offsetnow(state,offset) ((state).code + (offset))

#define iptn_emitp(target,p,size) memcpy((target),(p),(size))

#define iptn_define(label) const static uint8_t __iptnCodeDefine_##label[] = {
#define iptn_end };
#define iptn_label(label) &__iptnCodeDefine_##label

#endif
