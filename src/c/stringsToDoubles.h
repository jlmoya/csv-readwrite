/*
 *  Copyright (C) 2010-2012 - DIGITEO - Allan CORNET
 *
 *  This file must be used under the terms of the CeCILL.
 *  This source file is licensed as described in the file COPYING, which
 *  you should have received as part of this distribution.  The terms
 *  are also available at
 *  http://www.cecill.info/licences/Licence_CeCILL_V2-en.txt
 *
 */
/* ========================================================================== */
#ifndef __STRINGSTODOUBLES_H__
#define __STRINGSTODOUBLES_H__

#include "BOOL.h"
#include "stringToDouble.h"

double *stringsToDoubles(const char **pSTRs, int nbElements,
                       BOOL bConvertByNAN,
                       stringToDoubleError *ierr);

#endif /* __STRINGSTODOUBLES_H__ */
/* ========================================================================== */
