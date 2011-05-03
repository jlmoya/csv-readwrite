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
#ifndef __CSV_DEFAULT_H__
#define __CSV_DEFAULT_H__

const char *getCsvDefaultSeparator(void);
const char *getCsvDefaultDecimal(void);
const char *getCsvDefaultConversion(void);
const char *getCsvDefaultPrecision(void);
const char *getCsvDefaultCommentsRegExp(void);
const char *getCsvDefaultEOL(void);

int setCsvDefaultSeparator(const char *separator);
int setCsvDefaultDecimal(const char *decimal);
int setCsvDefaultConversion(const char *conversion);
int setCsvDefaultPrecision(const char *precision);
int setCsvDefaultCommentsRegExp(const char *commentsRegExp);
int setCsvDefaultEOL(const char *eol);

int setCsvDefaultReset(void);

#endif /* __CSV_DEFAULT_H__ */
/* ========================================================================== */
