/**
 * Copyright (C) Takuo Hada 2015-2016
 * @author t.hada 2016/08/02
 *
 * IEEE754 double floating point format.
 */
#pragma once

#include <stdint.h>

#define DOUBLE_SIGN_POSITIVE		(0)
#define DOUBLE_SIGN_NEGATIVE		(1)
#define DOUBLE_EXP_INF				(2047)
#define DOUBLE_EXP_ZERO				(0)
#define DOUBLE_EXP_SHIFT			(1023)
#define DOUBLE_FRACTION_BITS		(52)
#define DOUBLE_FRACTION_ONE			(1ULL << DOUBLE_FRACTION_BITS)

#define DOUBLE_STATUS_NORMAL		(0)
#define DOUBLE_STATUS_ZERO			(1)
#define DOUBLE_STATUS_UNNORMAL		(2)
#define DOUBLE_STATUS_INFINITY		(3)
#define DOUBLE_STATUS_NAN			(4)

static inline void _double_parse(
		double value, 
		int *sign, 
		int *scale, 
		unsigned long long *fraction,
		int *status)
{
	unsigned long long *p = (unsigned long long*)&value;

	int s = (*p >> 63) & 0x1;
	int e = (int)((*p >> 52) & 0x7FF);
	unsigned long long f = *p & 0xFFFFFFFFFFFFFULL;

	if(e == DOUBLE_EXP_INF && f == 0) {
		*status = DOUBLE_STATUS_INFINITY;
		
		*sign = s;
	} else if(e == DOUBLE_EXP_INF && f != 0) {
		*status = DOUBLE_STATUS_NAN;
	} else if(e == DOUBLE_EXP_ZERO && f == 0) {
		*status = DOUBLE_STATUS_ZERO;
		
		*sign = s;
	} else if(e == DOUBLE_EXP_ZERO && f != 0) {
		*status = DOUBLE_STATUS_UNNORMAL;
	} else {
		*status = DOUBLE_STATUS_NORMAL;
		
		*sign = s;
		*scale = e - DOUBLE_EXP_SHIFT;
		*fraction = f + DOUBLE_FRACTION_ONE;
	}
}

static inline void _double_set(
		double *value, 
		int sign, 
		int scale, 
		unsigned long long fraction)
{
	unsigned long long *p = (unsigned long long*)value;
	
	int exponent = scale + DOUBLE_EXP_SHIFT;
	
	*p = ((unsigned long long)(sign & 0x1) << 63) |
	     ((unsigned long long)(exponent & 0x7FF) << 52) |
	     (fraction & 0xFFFFFFFFFFFFFULL);
}
