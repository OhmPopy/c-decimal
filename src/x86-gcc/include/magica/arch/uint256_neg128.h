#pragma once

#include <magica/arch/def.h>

static inline void mg_uint256_neg128(mg_uint256_t *op1)
{
	asm volatile (
		".intel_syntax noprefix\n"
		"mov eax, [ecx]\n"
		"not eax, \n"
		"mov [ecx], eax \n"
		"mov eax, 4[ecx]\n"
		"not eax, \n"
		"mov 4[ecx], eax \n"
		"mov eax, 8[ecx]\n"
		"not eax, \n"
		"mov 8[ecx], eax \n"
		"mov eax, 12[ecx]\n"
		"not eax, \n"
		"mov 12[ecx], eax \n"
		"mov eax, [ecx] \n"
		"add eax, 1 \n"
		"mov [ecx], eax \n"
		"mov eax, 4[ecx] \n"
		"adc eax, 1 \n"
		"mov 4[ecx], eax \n"
		"mov eax, 8[ecx] \n"
		"adc eax, 1 \n"
		"mov 8[ecx], eax \n"
		"mov eax, 12[ecx] \n"
		"adc eax, 1 \n"
		"mov 12[ecx], eax \n"
		: 
		: "c"(op1)
		: "memory", "eax"
	);
}
