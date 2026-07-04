#include <stdio.h>
#include <math.h>
#include "prbs.h"
int main()
{
	uint8 order = 0;
	if(!PRBS_CalOrder(100, 16000, &order)) return;
	printf("order=%d\n", order);
	uint64 seed = 1 << (order - 1);
	PRBSMappingType type = binary;

	// test PRBS_ctor
	PRBS prbs;
	if (!PRBS_ctor(&prbs, order, seed, type, PRBS_sequence))
	{
		printf("PRBS initialization failed");
		return;
	}

	// test PRBS_GenNext
	int8 res;
	for (uint64 i = 0; i < 2 * ((uint64)(pow(2, order)) - 1); i++)
	{
		PRBS_GenNext(&prbs, &res);
		printf("%d", res);
		if ((i + 1) % ((uint64)(powf(2, order))-1) == 0)
		{
			printf("\n");
		}
	}

	getchar();
}