/*
 *  Copyright (C) 2010-2011 - DIGITEO - Allan CORNET
 *
 *  This file must be used under the terms of the CeCILL.
 *  This source file is licensed as described in the file COPYING, which
 *  you should have received as part of this distribution.  The terms
 *  are also available at
 *  http://www.cecill.info/licences/Licence_CeCILL_V2-en.txt
 *
 */
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
