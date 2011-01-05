/* ========================================================================== */
/* Allan CORNET */
/* DIGITEO 2011 */
/* ========================================================================== */
#ifndef __GETRANGE_H__
#define __GETRANGE_H__

#include "doublecomplex.h"

int isValidRange(const int *range, int sizeArray);

char **getRangeAsString(const char **pStrsValues,
                        int nbRows, int nbCols,
                        const int *iRange, 
                        int *returnedNbRows, int *returnedNbCols);
                        

doublecomplex *getRangeAsComplex(const doublecomplex *pComplex,
                        int nbRows, int nbCols, 
                        const int *iRange,
                        int *returnedNbRows, int *returnedNbCols);

#endif /* __GETRANGE_H__ */
/* ========================================================================== */
