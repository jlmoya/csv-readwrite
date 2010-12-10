/* ========================================================================== */
/* Allan CORNET */
/* DIGITEO 2010 */
/* ========================================================================== */
#ifndef __STRINGTOCOMPLEX_H__
#define __STRINGTOCOMPLEX_H__

#include "doublecomplex.h"
#include "BOOL.h"

typedef enum {
    STRINGTOCOMPLEX_NO_ERROR = 0,
    STRINGTOCOMPLEX_MEMORY_ALLOCATION = 1,
    STRINGTOCOMPLEX_NOT_A_NUMBER = 2,
    STRINGTOCOMPLEX_ERROR = 3
} stringToComplexError;

doublecomplex *stringsToComplexs(const char **pSTRs, int nbElements,
                       BOOL bConvertByNAN,
                       stringToComplexError *ierr);
                       
doublecomplex stringToComplex(const char *pSTR,
                       BOOL bConvertByNAN,
                       stringToComplexError *ierr);
                       
#endif /* __STRINGTOCOMPLEX_H__ */
/* ========================================================================== */
