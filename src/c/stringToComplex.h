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
#ifndef __STRINGTOCOMPLEX_H__
#define __STRINGTOCOMPLEX_H__

#include "doublecomplex.h"
#include "csv_complex.h"
#include "BOOL.h"

typedef enum {
    STRINGTOCOMPLEX_NO_ERROR = 0,
    STRINGTOCOMPLEX_MEMORY_ALLOCATION = 1,
    STRINGTOCOMPLEX_NOT_A_NUMBER = 2,
    STRINGTOCOMPLEX_ERROR = 3
} stringToComplexError;

csv_complexArray *stringsToCvsComplexArray(const char **pSTRs, int nbElements,
                       BOOL bConvertByNAN,
                       stringToComplexError *ierr);

#endif /* __STRINGTOCOMPLEX_H__ */
/* ========================================================================== */
