/*! \file prbs.c

	\brief PRBS

	A PRBS Generator.

*/
#include "prbs.h"
#include <math.h>
static const uint8 primlist[] =
{
	0,1,1,1,2,1,1,14,8,4,2,41,13,21,1,22,4,19,19,4,2,1,16,13,4,35,19,4,2,41,4,87,41,115,2,59,31,49,8,28,4,31,44,50,13,151,16,91,56,14,37,4,35,62,35,74,22,49,61,1,19,52,1,13
	//,13,182,19,81,50,21,21,47,14,76,37,26,50,67,14,87,8,233,74,213,131,50,81,157,52,22,118,50,2,49,59,110,32,79,88,194
};
bool PRBS_ctor(PRBS* me, uint8 order, uint64 seed, PRBSMappingType type, PRBSSequenceType seqtype)
{
	// order must be between 1 and 64
	if (order > 64 || order < 1)
	{
		return false;
	}
	// seed cannot be zero (all zeros state is invalid)
	if ((seed  & ((1ull << order) - 1)) == 0)
	{
		return false;
	}
	//me->seed = vinit;
	me->maskn = 1 << (order - 1);
	me->maskp = primlist[order - 1];
	me->LSFR = seed;
	me->seqtype = seqtype;
	//me->ntimes = 0;
	me->falsevalue = type == sign ? -1 : 0;
	return true;
}
bool PRBS_GenNext(PRBS* me, int8* res)
{
    uint64 reg = me->LSFR;
    *res = (reg & me->maskn) ? 1 : me->falsevalue;
    uint64 fb_linear = (reg & me->maskn) ? 1ULL : 0ULL;

    if (me->seqtype == PRBS_sequence)
    {
        if (fb_linear)
        {
            reg = ((reg ^ me->maskp) << 1) | 1ULL;
        }
        else
        {
            reg = reg << 1;
        }
    }
    else if (me->seqtype == DeBruijn_sequence)
    {
        uint64 fb_final = (reg == 0) ? 1ULL : fb_linear;
        if (fb_linear)
        {
            reg = ((reg ^ me->maskp) << 1) | fb_final;
        }
        else
        {
            reg = (reg << 1) | fb_final;
        }
    }
    return true;
}

bool PRBS_GenNextN(PRBS* me, int N, int8* res)
{
	for (int i = 0;  i < N;  i++)
	{
		PRBS_GenNext(me, &res[i]);
	}
	return true;
}

//void PRBS_Reset(PRBS* me)
//{
//	me->LSFR = me->seed;
//	//me->ntimes = 0;
//}


bool PRBS_CalOrder(float minHz, float sampHz, uint8* order)
{
	*order = 0;
	if (minHz <= 0 || sampHz <= 0)
	{
		return false;
	}
	*order = (uint8)ceilf(logf(sampHz / minHz + 1) / logf(2.0f));
	return true;
}