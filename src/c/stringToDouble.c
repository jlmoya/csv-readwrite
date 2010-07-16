/* ========================================================================== */
/* Allan CORNET */
/* DIGITEO 2010 */
/* ========================================================================== */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "stringToDouble.h"
#include "MALLOC.h"
/* ========================================================================== */
#define NanString "Nan"
#define InfString "Inf"
#define NegInfString "-Inf"
#ifndef _MSC_VER
  #ifndef stricmp
    #define stricmp strcasecmp
  #endif
#else  
    #define stricmp _stricmp
#endif
/* ========================================================================== */
static double returnINF(BOOL bPositive);
static double returnNAN(void);
/* ========================================================================== */
double *stringToDouble(char **pSTRs, int nbElements, 
                       BOOL bConvertByNAN, stringToDoubleError *ierr)
{
  double *dValues = NULL;

  *ierr = STRINGTODOUBLE_ERROR;
  if (nbElements <= 0) return NULL;

  if (pSTRs == NULL)
  {
    *ierr = STRINGTODOUBLE_MEMORY_ALLOCATION;
  }
  else
  {
    dValues = (double*)MALLOC(sizeof(double) * nbElements);
    if (dValues)
    {
      int i = 0;
      for (i = 0; i < nbElements; i++)
      {
        if (pSTRs[i])
        {
          if (stricmp(pSTRs[i], NanString) == 0)
          {
            dValues[i] = returnNAN();
          }
          else if (stricmp(pSTRs[i], InfString) == 0)
          {
            dValues[i] = returnINF(TRUE);
          }
          else if (stricmp(pSTRs[i], NegInfString) == 0)
          {
            dValues[i] = returnINF(FALSE);
          }
          else
          {
            double v = 0.;
            int err = sscanf(pSTRs[i], "%lf", &v);
            if (err == 0)
            {
              if (bConvertByNAN)
              {
                dValues[i] = returnNAN();
              }
              else
              {
                FREE(dValues);
                dValues = NULL;
                *ierr = STRINGTODOUBLE_NOT_A_NUMBER;
                return NULL;
              }
            }
            else
            {
              dValues[i] = v;
            }
          }
        }
        else
        {
          FREE(dValues);
          dValues = NULL;
        }
      }
      *ierr = STRINGTODOUBLE_NO_ERROR;
    }
    else
    {
      *ierr = STRINGTODOUBLE_MEMORY_ALLOCATION;
    }
  }

  return dValues;
}
/* ========================================================================== */
static double returnINF(BOOL bPositive)
{
    double v = 0 - 0;
    double p = 10;
    if (!bPositive) p = -10;
    return (double) p / (double)v;
}
/* ========================================================================== */
static double returnNAN(void)
{
    static int first = 1;
    static double nan = 1.0;

    if ( first )
    {
        nan = (nan - (double) first)/(nan - (double) first);
        first = 0;
    }
    return (nan);
}
/* ========================================================================== */
