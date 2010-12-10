/* ========================================================================== */
/* Allan CORNET */
/* DIGITEO 2010 */
/* ========================================================================== */
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
/* ========================================================================== */
#define NanString "Nan"
#define InfString "Inf"
#define NegInfString "-Inf"
#define PlusChar '+'
#define LessChar '-'
#define ComplexCharI 'i'
#define ComplexCharJ 'j'
/* ========================================================================== */
static BOOL isAlphaNum(const char* pStr);
static BOOL getRealImagPartAsString(const char *line, int pos, char **pstReal, char **pstImag);
/* ========================================================================== */
doublecomplex *stringsToComplexs(const char **pSTRs, int nbElements,
                                 BOOL bConvertByNAN,
                                 stringToComplexError *ierr)
{
    doublecomplex *dComplexValues = NULL;
    *ierr = STRINGTOCOMPLEX_ERROR;
    if (nbElements <= 0) return NULL;
    if (pSTRs == NULL)
    {
        *ierr = STRINGTOCOMPLEX_MEMORY_ALLOCATION;
    }
    else
    {
        dComplexValues = (doublecomplex*)MALLOC(sizeof(doublecomplex) * nbElements);
        if (dComplexValues)
        {
            int i = 0;
            for (i = 0; i < nbElements; i++)
            {
                dComplexValues[i] = stringToComplex(pSTRs[i], bConvertByNAN, ierr);
                if (*ierr != STRINGTOCOMPLEX_NO_ERROR)
                {
                    FREE(dComplexValues);
                    return (dComplexValues = NULL);
                }
            }
        }
        else
        {
            *ierr = STRINGTOCOMPLEX_MEMORY_ALLOCATION;
        }
    }
    return dComplexValues;
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
        int len = (int) strlen(pSTR);
        if (len > 0)
        {
            if ((pSTR[len - 1] == ComplexCharI) || (pSTR[len - 1] == ComplexCharJ))
            {
                // complex
                char *line = strdup(pSTR);
                if (line)
                {
                    int l = 0;
                    char *pStrReal = NULL;
                    char *pStrImag = NULL;
                    stringToDoubleError ierrReal = STRINGTODOUBLE_ERROR;
                    stringToDoubleError ierrImag = STRINGTODOUBLE_ERROR;

                    // remove i or j
                    line[len - 1] = '\0';
                    len = (int) strlen(pSTR);
                    for (l = len - 1; l >= 0; l--)
                    {
                        if ((line[l] == PlusChar) || (line[l] == LessChar))
                        {
                            if (l-1 >= 0)
                            {
                                if ((line[l-1] == 'e') || (line[l-1] == 'd'))
                                {
                                    continue;
                                }
                                else
                                {
                                    if (!getRealImagPartAsString(line, l, pStrReal, pStrImag))
                                    {
                                        FREE(line); line = NULL;
                                        dComplexValue.r = 0.;
                                        dComplexValue.i = 0.;
                                        return dComplexValue;
                                    }
                                    break;
                                }
                            }
                            else
                            {
                                    if (!getRealImagPartAsString(line, l, pStrReal, pStrImag))
                                    {
                                        FREE(line); line = NULL;
                                        dComplexValue.r = 0.;
                                        dComplexValue.i = 0.;
                                        return dComplexValue;
                                    }
                                    break;
                            }
                        }
                    }

                    if ((pStrReal == NULL) && (pStrImag == NULL))
                    {
                        ierrReal = STRINGTODOUBLE_NO_ERROR;
                        dComplexValue.r = 0.0;
                        pStrImag = strdup(line);
                        dComplexValue.i = stringToDouble(pStrImag, bConvertByNAN, &ierrImag);
                    }
                    else
                    {
                        dComplexValue.r = stringToDouble(pStrReal, bConvertByNAN, &ierrReal);
                        dComplexValue.i = stringToDouble(pStrImag, bConvertByNAN, &ierrImag);
                    }

                    FREE(line); line = NULL;
                    FREE(pStrReal); pStrReal = NULL;
                    FREE(pStrImag); pStrImag = NULL;

                    if (ierrReal != STRINGTODOUBLE_NO_ERROR)
                    {
                        *ierr = ierrReal;
                        dComplexValue.r = 0.;
                        dComplexValue.i = 0.;
                        return dComplexValue;
                    }

                    if (ierrImag != STRINGTODOUBLE_NO_ERROR)
                    {
                        *ierr = ierrImag;
                        dComplexValue.r = 0.;
                        dComplexValue.i = 0.;                        
                        return dComplexValue;
                    }
                    *ierr = STRINGTOCOMPLEX_NO_ERROR;
                }
                else
                {
                    *ierr = STRINGTOCOMPLEX_MEMORY_ALLOCATION;
                }
            }
            else
            {
                // double
                dComplexValue.r = stringToDouble(pSTR, bConvertByNAN, ierr);
                dComplexValue.i = 0.0;
            }
        }
        else
        {
            *ierr = STRINGTOCOMPLEX_ERROR;
        }
    }
    else
    {
        *ierr = STRINGTOCOMPLEX_MEMORY_ALLOCATION;
    }

    return dComplexValue;
}
/* ========================================================================== */
static BOOL isAlphaNum(const char* pStr)
{
    int i = 0;
    if (pStr)
    {
        int len = (int) strlen(pStr);
        while (isalnum(pStr[i]) || pStr[i] == '.'  || pStr[i] == '-'  || pStr[i] == '+') i++;
        if (i == len)
        {
            return TRUE;
        }
    }
    return FALSE;
}
/* ========================================================================== */
static BOOL getRealImagPartAsString(const char *line, int pos, char **pstReal, char **pstImag)
{
    *pstReal = strdup(line);
    *pstReal[pos] = '\0';
    *pstImag = strdup(&line[pos]);

    // check that it is a number (no space, ...) 
    if (!isAlphaNum(*pstReal) || !isAlphaNum(*pstImag))
    {
        FREE(line); line = NULL;
        FREE(*pstReal); *pstReal = NULL;
        FREE(*pstImag); *pstImag = NULL;
        return FALSE;
    }

    if (*pstReal[0] == PlusChar) // remove + at beginning as '+Nan'
    {
        *pstReal = &*pstReal[1];
    }

    if (*pstImag[0] == PlusChar)  // remove + at beginning as '+Nan'
    {
        *pstImag = &*pstImag[1];
    }

    return TRUE;
}
/* ========================================================================== */
