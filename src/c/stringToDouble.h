/* ========================================================================== */
/* Allan CORNET */
/* DIGITEO 2010 */
/* ========================================================================== */
#ifndef __STRINGTODOUBLE_H__
#define __STRINGTODOUBLE_H__

#include "BOOL.h"

typedef enum {
    STRINGTODOUBLE_NO_ERROR = 0,
    STRINGTODOUBLE_MEMORY_ALLOCATION = 1,
    STRINGTODOUBLE_NOT_A_NUMBER = 2,
    STRINGTODOUBLE_ERROR = 3
} stringToDoubleError;

double *stringToDouble(char **pSTRs, int nbElements,
                       BOOL bConvertByNAN,
                       stringToDoubleError *ierr);

#endif /* __STRINGTODOUBLE_H__ */
/* ========================================================================== */
