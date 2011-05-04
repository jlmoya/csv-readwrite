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
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "stringToComplex.h"
#include "stringToDouble.h"
#include "MALLOC.h"
#ifdef  _MSC_VER
#include "strdup_windows.h"
#endif
#include "BOOL.h"
#include "csv_strsubst.h"
#include "nan.h"
/* ========================================================================== */
#define PlusChar '+'
#define LessChar '-'
#define ComplexCharI 'i'
#define ComplexCharJ 'j'
#define ComplexScilab "%i"
#define ComplexI "i"
/* ========================================================================== */
#ifndef _MSC_VER
#ifndef strnicmp
#define strnicmp strncasecmp
#endif
#else
#define stricmp _stricmp
#endif
#ifdef _MSC_VER
#undef strnicmp
#define strnicmp _strnicmp
#endif
/* ========================================================================== */
static doublecomplex stringToComplex(const char *pSTR,
                                     BOOL bConvertByNAN,
                                     stringToComplexError *ierr);
static int ParseNumber(const char* tx);
static stringToComplexError ParseComplexValue(const char *tx, BOOL bConvertByNAN, double *real, double *imag);
static char *midstring(const char *tx, int pos, int nb);
static char *leftstring(const char *tx, int pos);
static BOOL is_unit_imaginary (const char *src, double *im);
/* ========================================================================== */
csv_complexArray *stringsToCvsComplexArray(const char **pSTRs, int nbElements,
                                           BOOL bConvertByNAN,
                                           stringToComplexError *ierr)
{
    csv_complexArray *pCsvComplexArray = NULL;
    *ierr = STRINGTOCOMPLEX_ERROR;
    if (nbElements <= 0) return NULL;
    if (pSTRs == NULL)
    {
        *ierr = STRINGTOCOMPLEX_MEMORY_ALLOCATION;
    }
    else
    {
        pCsvComplexArray = createCsvComplexArrayEmpty(nbElements);
        if (pCsvComplexArray)
        {
            int i = 0;
            for (i = 0; i < nbElements; i++)
            {
                doublecomplex dComplexValue = stringToComplex(pSTRs[i], bConvertByNAN, ierr);
                if (*ierr != STRINGTOCOMPLEX_NO_ERROR)
                {
                    freeCsvComplexArray(pCsvComplexArray);
                    return NULL;
                }
                else
                {
                    pCsvComplexArray->realPart[i] = dComplexValue.r;
                    pCsvComplexArray->imagPart[i] = dComplexValue.i;
                }
            }
            cleanImagPartCsvComplexArray(pCsvComplexArray);
        }
        else
        {
            *ierr = STRINGTOCOMPLEX_MEMORY_ALLOCATION;
        }
    }
    return pCsvComplexArray;
}
/* ========================================================================== */
doublecomplex stringToComplex(const char *pSTR,
                              BOOL bConvertByNAN,
                              stringToComplexError *ierr)
{
    doublecomplex dComplexValue;
    *ierr = STRINGTOCOMPLEX_ERROR;

    dComplexValue.r = 0.;
    dComplexValue.i = 0.;

    if (pSTR)
    {
        double real = 0.;
        double imag = 0.;
        char * pStrWithOutBlanks = csv_strsubst(pSTR, " ", "");

        if (pStrWithOutBlanks)
        {
            int lenStrWithOutBlanks = (int) strlen(pStrWithOutBlanks);

            /* case .4 replaced by 0.4 */
            if (pStrWithOutBlanks[0] == '.')
            {
                /* case .4 replaced by 0.4 */
                char *pstStrTemp = (char*)MALLOC(sizeof(char) * (lenStrWithOutBlanks + strlen("0") + 1));
                strcpy(pstStrTemp, "0");
                strcat(pstStrTemp, pStrWithOutBlanks);
                FREE(pStrWithOutBlanks);
                pStrWithOutBlanks = pstStrTemp;
            }

            if (lenStrWithOutBlanks > 1)
            {
                if (((pStrWithOutBlanks[0] == '+') || (pStrWithOutBlanks[0] == '-')) &&
                    (pStrWithOutBlanks[1] == '.'))
                {
                    /* case +.4 replaced by +0.4 */
                    char *pstStrTemp = csv_strsubst(pStrWithOutBlanks, "+.", "+0.");
                    FREE(pStrWithOutBlanks);

                    /* case -.4 replaced by -0.4 */
                    pStrWithOutBlanks = csv_strsubst(pstStrTemp, "-.", "-0.");
                    FREE(pstStrTemp);
                    pstStrTemp = NULL;
                }
            }

            /* Case: "i", "+i", "-i", and with "j"  */
            if (is_unit_imaginary (pStrWithOutBlanks, &imag))
            {
                *ierr = STRINGTODOUBLE_NO_ERROR;
                dComplexValue.r = 0.;
                dComplexValue.i = imag;
            }
            else
            {
                *ierr = ParseComplexValue(pStrWithOutBlanks, bConvertByNAN, &real, &imag);
            }
            FREE(pStrWithOutBlanks);
            pStrWithOutBlanks = NULL;
        }
        dComplexValue.r = real;
        dComplexValue.i = imag;
    }
    return dComplexValue;
}
/* ========================================================================== */
static int ParseNumber(const char* tx)
{
    int lookahead = 0;
    int len = 0;

    if (tx[len] == NULL) return lookahead;
    if (tx[len] < 0) return lookahead; 

    if ((tx[len] == '+') || (tx[len] == '-'))  len++;
    lookahead = len;
    while (isdigit(tx[len])) len++;
    lookahead = len;
    if (tx[lookahead] == '.')
    {
        lookahead++;
        len = 0;
        while (isdigit(tx[len+lookahead])) len++;
        lookahead += len;
    }
    if ((tx[lookahead] == 'E') || (tx[lookahead] == 'e') ||
        (tx[lookahead] == 'D') || (tx[lookahead] == 'd'))
    {
        lookahead++;
        if ((tx[lookahead] == '+') || (tx[lookahead] == '-'))
        {
            lookahead++;
        }
        len = 0;
        while (isdigit(tx[len+lookahead])) len++;
        lookahead += len;
    }
    return lookahead;
}
/* ========================================================================== */
static stringToComplexError ParseComplexValue(const char *tx, BOOL bConvertByNAN, double *real, double *imag)
{
    stringToComplexError ierr = 0;
    char *rnum_string = NULL;
    char *inum_string = NULL;
    int lnum = 0;
    BOOL haveImagI = FALSE;
    char *modifiedTxt = NULL;

    *real = stringToDouble(tx, FALSE, &ierr);
    *imag = 0;

    if (ierr != STRINGTODOUBLE_NO_ERROR)
    {
        modifiedTxt = csv_strsubst(tx, ComplexScilab, ComplexI);
        lnum = ParseNumber(modifiedTxt);
        if (lnum <= 1)
        {
            /* manages special cases nan + nani, ... */
            if (strnicmp(modifiedTxt, NanString, strlen(NanString)) == 0) lnum = strlen(NanString);
            else if (strnicmp(modifiedTxt, InfString, strlen(InfString)) == 0) lnum = strlen(InfString);
            else if (strnicmp(modifiedTxt, NegInfString, strlen(NegInfString)) == 0) lnum = strlen(NegInfString);
            else if (strnicmp(modifiedTxt, PosInfString, strlen(PosInfString)) == 0) lnum = strlen(PosInfString);
            else if (strnicmp(modifiedTxt, NegNanString, strlen(NegNanString)) == 0) lnum = strlen(NegNanString);
            else if (strnicmp(modifiedTxt, PosNanString, strlen(PosNanString)) == 0) lnum = strlen(PosNanString);
        }
        inum_string = midstring(modifiedTxt, lnum, -1);
        if ((inum_string[strlen(inum_string) - 1] == 'i') ||
            (inum_string[strlen(inum_string) - 1] == 'j'))
        {
            inum_string[strlen(inum_string) - 1] = 0;
            if (inum_string[strlen(inum_string) - 1] == '*')
            {
                inum_string[strlen(inum_string) - 1] = 0;
            }
            if (strcmp(inum_string, "+") == 0)
            {
                FREE(inum_string);
                inum_string = strdup("+1");
            }

            if (strcmp(inum_string, "-") == 0)
            {
                FREE(inum_string);
                inum_string = strdup("-1");
            }
            haveImagI = TRUE;
        }
        else
        {
            haveImagI = FALSE;
        }
        rnum_string = leftstring(modifiedTxt, lnum);

        if (strcmp(inum_string, "") == 0)
        {
            *imag = stringToDouble(rnum_string, bConvertByNAN, &ierr);
            *real = 0.;
        }
        else
        {
            double dReal = 0.;
            double dImag = 0.;

            stringToComplexError ierrReal = 0;
            stringToComplexError ierrImag = 0;
            dReal = stringToDouble(rnum_string, FALSE, &ierrReal);
            dImag = stringToDouble(inum_string, FALSE, &ierrImag);

            if ((ierrReal == STRINGTODOUBLE_NO_ERROR) && (ierrImag == STRINGTODOUBLE_NO_ERROR))
            {
                if (!haveImagI)
                {
                    if (bConvertByNAN)
                    {
                        ierr = STRINGTOCOMPLEX_NO_ERROR;
                        *real = returnNAN();
                        *imag = 0.;
                    }
                    else
                    {
                        ierr = STRINGTOCOMPLEX_ERROR;
                    }
                }
                else
                {
                    ierr = STRINGTOCOMPLEX_NO_ERROR;
                    *real = dReal;
                    *imag = dImag;
                }
            }
            else
            {
                if (bConvertByNAN)
                {
                    ierr = STRINGTOCOMPLEX_NO_ERROR;
                    *real = returnNAN();
                    *imag = 0.;
                }
                else
                {
                    ierr = STRINGTOCOMPLEX_ERROR;
                }
            }
        }

        if (rnum_string) {FREE(rnum_string); rnum_string = NULL;}
        if (inum_string) {FREE(inum_string); inum_string = NULL;}
        if (modifiedTxt) {FREE(modifiedTxt); modifiedTxt = NULL;}
    }
    return ierr;
}
/* ========================================================================== */
static char *midstring(const char *tx, int pos, int nb)
{
    char *returnString = NULL;
    if (tx)
    {
        int lenTx = (int) strlen(tx);
        int posEnd = 0;
        int newLen = 0;

        if (nb < 0) posEnd = lenTx;
        else posEnd = nb;
        newLen = posEnd + 1;
        if (newLen > 0)
        {
            returnString = (char*)MALLOC(sizeof(char) * newLen);
            strncpy(returnString, &tx[pos], posEnd);
            returnString[posEnd] = 0;
        }
    }
    return returnString;
}
/* ========================================================================== */
static char *leftstring(const char *tx, int pos)
{
    char *returnString = NULL;
    if (tx)
    {
        int lenTx = (int) strlen(tx);
        returnString = strdup(tx);
        if ((pos > lenTx) || (pos < 0))
        {
            return returnString;
        }
        else
        {
            returnString[pos] = 0;
        }
    }
    return returnString;
}
/* ========================================================================== */
static BOOL is_unit_imaginary (const char *src, double *im)
{
    char *modifiedSrc = csv_strsubst(src, ComplexScilab, ComplexI);
    BOOL isUnitImag = FALSE;

    if (*modifiedSrc == LessChar)
    {
        *im = -1.0;
        modifiedSrc++;
    }
    else
    {
        *im = +1.0;
        if (*modifiedSrc == PlusChar) modifiedSrc++;
    }

    if ((*modifiedSrc == ComplexCharI || *modifiedSrc == ComplexCharJ) && modifiedSrc[1] == 0)
    {
        isUnitImag = TRUE;
    }

    if (modifiedSrc)
    {
        FREE(modifiedSrc);
        modifiedSrc = NULL;
    }
    return isUnitImag;
}
/* ========================================================================== */
