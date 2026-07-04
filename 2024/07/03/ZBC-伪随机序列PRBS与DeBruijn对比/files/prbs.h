/*! \file prbs.h

	\brief headfile of module prbs

	A PRBS Generator.

*/


#ifndef PRBS_H
#define PRBS_H
/*! \def false 0
*/
#define false 0
/*! \def true 1
*/
#define true 1
/*! \typedef char int8
*/
typedef char int8;
/*! \var char int8
*/
typedef unsigned char uint8;
typedef int int32;
typedef unsigned int uint32;
typedef short int16;
typedef unsigned short uint16;
typedef long long int64;
typedef unsigned long long uint64;
typedef int8 bool;

/*! \enum PRBSMappingType
*/
typedef enum PRBSMappingTypeTag
{
	binary,	/**< binary mapping (0/1) */  
	sign	/**< sign mapping (+/-) */  
}PRBSMappingType;

/*! \enum PRBSMappingType
*/
typedef enum PRBSSequenceTypeTag
{
	PRBS_sequence,	/**< standard PRBS sequence */  
	DeBruijn_sequence	/**< De Bruijn sequence */  
}PRBSSequenceType;

/*! \struct PRBS
*/
typedef struct PRBSTag
{
	//uint64 seed;
	uint64 maskn;/**< mask for highest bit */ 
	uint64 maskp;/**< mask for characteristic polynomial */ 
	uint64 LSFR;/**< linear feedback shift register */ 
	//uint64 ntimes;
	int8 falsevalue;/**< false value (0 or -1) */ 
	PRBSSequenceType seqtype;
}PRBS;
/*! \fn PRBS_ctor(PRBS* me, uint8 order, uint64 seed, PRBSMappingType type, PRBSSequenceType seqtype)
	\brief PRBS constructor
	\param[in] order PRBS order
	\param[in] seed initial seed value
	\param[in] type output mapping type
	\param[in] seqtype sequence type (PRBS or De Bruijn)
	\return \a true - success \a false - failure
*/
bool PRBS_ctor(PRBS* me, uint8 order, uint64 seed, PRBSMappingType type, PRBSSequenceType seqtype);
bool PRBS_GenNext(PRBS* me, int8* res);
bool PRBS_GenNextN(PRBS* me, int N, int8* res);
//void PRBS_Reset(PRBS* me);


/*! \fn PRBS_CalOrder(float minHz, float sampHz)
	\brief Calculate required PRBS order from frequency constraints
	\param[in] minHz minimum frequency
	\param[in] sampHz sampling frequency
	\param[out] order calculated PRBS order
	\return \a true - success \a false - failure
*/
bool PRBS_CalOrder(float minHz, float sampHz, uint8* order);
#endif // !PRBS_H