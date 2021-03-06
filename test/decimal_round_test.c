#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <magica/decimal.h>

#include "mg_assert.h"

static void round_test(const char *text, int precision, int type, const char *ret)
{
	char strbuf[1000];
	int size;
	mg_decimal_t value1;

	mg_assert(mg_decimal_parse_string(text, &value1) == 0);

	mg_assert(mg_decimal_round(/*inout*/&value1, precision, type) == 0);

	mg_assert(mg_decimal_to_string(&value1, strbuf, 1000, &size) == 0);

	mg_assert(strcmp(ret, strbuf) == 0);
}

void decimal_round_test()
{
	clock_t tm = clock();

	round_test("10.0015", 3, mgDECIMAL_ROUND_UP, "10.002");
	round_test("10.0015", 3, mgDECIMAL_ROUND_DOWN, "10.001");
	round_test("10.0015", 3, mgDECIMAL_ROUND_OFF, "10.002");
	round_test("10.0014", 3, mgDECIMAL_ROUND_OFF, "10.001");
	round_test("10.0014", 3, mgDECIMAL_ROUND_UP, "10.002");
	round_test("10.0014", 3, mgDECIMAL_ROUND_DOWN, "10.001");
	round_test("10.000000000000000000000015", 23, mgDECIMAL_ROUND_UP, "10.00000000000000000000002");
	round_test("10.000000000000000000000015", 23, mgDECIMAL_ROUND_DOWN, "10.00000000000000000000001");
	round_test("10.000000000000000000000015", 23, mgDECIMAL_ROUND_OFF, "10.00000000000000000000002");
	round_test("10.000000000000000000000014", 23, mgDECIMAL_ROUND_OFF, "10.00000000000000000000001");
	round_test("10.000000000000000000000014", 23, mgDECIMAL_ROUND_UP, "10.00000000000000000000002");
	round_test("10.000000000000000000000014", 23, mgDECIMAL_ROUND_DOWN, "10.00000000000000000000001");

	round_test("10.001412345679", 3, mgDECIMAL_ROUND_DOWN, "10.001");
	round_test("10.001512345679", 3, mgDECIMAL_ROUND_DOWN, "10.001");
	round_test("10.00141", 3, mgDECIMAL_ROUND_DOWN, "10.001");
	round_test("10.00159", 3, mgDECIMAL_ROUND_DOWN, "10.001");
	round_test("10.00141211", 3, mgDECIMAL_ROUND_DOWN, "10.001");
	round_test("10.00151111", 3, mgDECIMAL_ROUND_DOWN, "10.001");

	round_test("10.001412345679", 3, mgDECIMAL_ROUND_UP, "10.002");
	round_test("10.001512345679", 3, mgDECIMAL_ROUND_UP, "10.002");
	round_test("10.00141", 3, mgDECIMAL_ROUND_UP, "10.002");
	round_test("10.00159", 3, mgDECIMAL_ROUND_UP, "10.002");
	round_test("10.00141211", 3, mgDECIMAL_ROUND_UP, "10.002");
	round_test("10.00151111", 3, mgDECIMAL_ROUND_UP, "10.002");

	round_test("10.001412345679", 3, mgDECIMAL_ROUND_OFF, "10.001");
	round_test("10.001512345679", 3, mgDECIMAL_ROUND_OFF, "10.002");
	round_test("10.00141", 3, mgDECIMAL_ROUND_OFF, "10.001");
	round_test("10.00159", 3, mgDECIMAL_ROUND_OFF, "10.002");
	round_test("10.00141211", 3, mgDECIMAL_ROUND_OFF, "10.001");
	round_test("10.00151111", 3, mgDECIMAL_ROUND_OFF, "10.002");

	round_test("-10.001412345679", 3, mgDECIMAL_ROUND_DOWN, "-10.001");
	round_test("-10.001512345679", 3, mgDECIMAL_ROUND_DOWN, "-10.001");
	round_test("-10.00141", 3, mgDECIMAL_ROUND_DOWN, "-10.001");
	round_test("-10.00159", 3, mgDECIMAL_ROUND_DOWN, "-10.001");
	round_test("-10.00141211", 3, mgDECIMAL_ROUND_DOWN, "-10.001");
	round_test("-10.00151111", 3, mgDECIMAL_ROUND_DOWN, "-10.001");

	round_test("-10.001412345679", 3, mgDECIMAL_ROUND_UP, "-10.002");
	round_test("-10.001512345679", 3, mgDECIMAL_ROUND_UP, "-10.002");
	round_test("-10.00141", 3, mgDECIMAL_ROUND_UP, "-10.002");
	round_test("-10.00159", 3, mgDECIMAL_ROUND_UP, "-10.002");
	round_test("-10.00141211", 3, mgDECIMAL_ROUND_UP, "-10.002");
	round_test("-10.00151111", 3, mgDECIMAL_ROUND_UP, "-10.002");

	round_test("-10.001412345679", 3, mgDECIMAL_ROUND_OFF, "-10.001");
	round_test("-10.001512345679", 3, mgDECIMAL_ROUND_OFF, "-10.002");
	round_test("-10.00141", 3, mgDECIMAL_ROUND_OFF, "-10.001");
	round_test("-10.00159", 3, mgDECIMAL_ROUND_OFF, "-10.002");
	round_test("-10.00141211", 3, mgDECIMAL_ROUND_OFF, "-10.001");
	round_test("-10.00151111", 3, mgDECIMAL_ROUND_OFF, "-10.002");

	round_test("10.001412345679", 3, mgDECIMAL_CEILING, "10.002");
	round_test("10.001512345679", 3, mgDECIMAL_CEILING, "10.002");
	round_test("-10.001412345679", 3, mgDECIMAL_CEILING, "-10.001");
	round_test("-10.001512345679", 3, mgDECIMAL_CEILING, "-10.001");

	round_test("0000.001412345679", 3, mgDECIMAL_CEILING, "0.002");
	round_test("0000.001512345679", 3, mgDECIMAL_CEILING, "0.002");
	round_test("-0000.001412345679", 3, mgDECIMAL_CEILING, "-0.001");
	round_test("-0000.001512345679", 3, mgDECIMAL_CEILING, "-0.001");

	round_test("10.001412345679", 3, mgDECIMAL_FLOOR, "10.001");
	round_test("10.001512345679", 3, mgDECIMAL_FLOOR, "10.001");
	round_test("-10.001412345679", 3, mgDECIMAL_FLOOR, "-10.002");
	round_test("-10.001512345679", 3, mgDECIMAL_FLOOR, "-10.002");

	round_test("0000.001412345679", 3, mgDECIMAL_FLOOR, "0.001");
	round_test("0000.001512345679", 3, mgDECIMAL_FLOOR, "0.001");
	round_test("-0000.001412345679", 3, mgDECIMAL_FLOOR, "-0.002");
	round_test("-0000.001512345679", 3, mgDECIMAL_FLOOR, "-0.002");

	round_test("1005", -1, mgDECIMAL_FLOOR, "1000");
	round_test("1000.5", 0, mgDECIMAL_FLOOR, "1000");
	round_test("1025", -2, mgDECIMAL_FLOOR, "1000");
	round_test("-1005", -1, mgDECIMAL_FLOOR, "-1010");
	round_test("-1000.5", 0, mgDECIMAL_FLOOR, "-1001");
	round_test("-1025", -2, mgDECIMAL_FLOOR, "-1100");
	round_test("9999999991025", -5, mgDECIMAL_FLOOR, "9999999900000");

	round_test("1005", -1, mgDECIMAL_CEILING, "1010");
	round_test("1000.5", 0, mgDECIMAL_CEILING, "1001");
	round_test("1025", -2, mgDECIMAL_CEILING, "1100");
	round_test("-1005", -1, mgDECIMAL_CEILING, "-1000");
	round_test("-1000.5", 0, mgDECIMAL_CEILING, "-1000");
	round_test("-1025", -2, mgDECIMAL_CEILING, "-1000");
	round_test("9999999991025", -5, mgDECIMAL_CEILING, "10000000000000");

	printf("TEST mg_decimal_round(): OK\n");
}
