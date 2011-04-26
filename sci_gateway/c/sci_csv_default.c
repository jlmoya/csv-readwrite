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
#include <string.h>
#include <stdio.h>
#include "stack-c.h"
#include "api_scilab.h"
#include "sci_types.h"
#include "Scierror.h"
#include "MALLOC.h"
#include "Scierror.h"
#include "localization.h"
#include "freeArrayOfString.h"
#ifdef _MSC_VER
#include "strdup_windows.h"
#endif
#include "csv_default.h"
#include "gw_csv_helpers.h"
/* ========================================================================== */
#define SEPARATOR_FIELDNAME "separator"
#define DECIMAL_FIELDNAME "decimal"
#define CONVERSION_FIELDNAME "conversion"
#define PRECISION_FIELDNAME "precision"
#define RESET_PARAMATERS "reset"
/* ========================================================================== */
#define NUMBER_FIELD 4
/* ========================================================================== */
static int sci_csv_default_no_rhs(char *fname);
static int sci_csv_default_one_rhs(char *fname);
static int sci_csv_default_two_rhs(char *fname);
/* ========================================================================== */
int sci_csv_default(char *fname)
{
    Rhs = Max(0, Rhs);
    CheckRhs(0, 2);
    CheckLhs(1, 1);

    switch(Rhs)
    {
    case 0:
        return sci_csv_default_no_rhs(fname);
    case 1:
        return sci_csv_default_one_rhs(fname);
    case 2:
        return sci_csv_default_two_rhs(fname);
    }
    return 0;
}
/* ========================================================================== */
static int sci_csv_default_no_rhs(char *fname)
{
    int sizeArray = NUMBER_FIELD * 2;
    char **array = (char**)MALLOC(sizeof(char*) * sizeArray);

    if (array)
    {
        SciErr sciErr;

        int nbRows = NUMBER_FIELD;
        int nbCols = 2;

        array[0] = strdup(SEPARATOR_FIELDNAME);
        array[1] = strdup(DECIMAL_FIELDNAME);
        array[2] = strdup(CONVERSION_FIELDNAME);
        array[3] = strdup(PRECISION_FIELDNAME);

        array[4] = strdup(getCsvDefaultSeparator());
        array[5] = strdup(getCsvDefaultDecimal());
        array[6] = strdup(getCsvDefaultConversion());
        array[7] = strdup(getCsvDefaultPrecision());

        sciErr = createMatrixOfString(pvApiCtx, Rhs + 1, nbRows, nbCols, array);
        freeArrayOfString(array, sizeArray);
        if(sciErr.iErr)
        {
            printError(&sciErr, 0);
            return 0;
        }

        LhsVar(1) = Rhs + 1;
        C2F(putlhsvar)();
    }
    else
    {
        Scierror(999,_("%s: Memory allocation error.\n"), fname);
    }

    return 0;
}
/* ========================================================================== */
static int sci_csv_default_one_rhs(char *fname)
{
    int iErr = 0;

    char *fieldname = NULL;
    char *fieldvalue = NULL;

    fieldname = csv_getArgumentAsString(pvApiCtx, 1, fname, &iErr);
    if (iErr) return 0;

    if (strcmp(fieldname, SEPARATOR_FIELDNAME) == 0)
    {
        fieldvalue = strdup(getCsvDefaultSeparator());
    }
    else if (strcmp(fieldname, DECIMAL_FIELDNAME) == 0)
    {
        fieldvalue = strdup(getCsvDefaultDecimal());
    }
    else if (strcmp(fieldname, CONVERSION_FIELDNAME) == 0)
    {
        fieldvalue = strdup(getCsvDefaultConversion());
    }
    else if (strcmp(fieldname, PRECISION_FIELDNAME) == 0)
    {
        fieldvalue = strdup(getCsvDefaultPrecision());
    }
    else if (strcmp(fieldname, RESET_PARAMATERS) == 0)
    {
        if (fieldname) {FREE(fieldname); fieldname = NULL;}
        if (fieldvalue) {FREE(fieldvalue); fieldvalue = NULL;}

        setCsvDefaultReset();

        createEmptyMatrix(pvApiCtx, Rhs + 1);

        LhsVar(1) = Rhs + 1;
        C2F(putlhsvar)();
        return 0;
    }
    else
    {
        Scierror(999,_("%s: Wrong value for input argument #%d: '%s', '%s' or '%s' expected.\n"), fname, 1, SEPARATOR_FIELDNAME, DECIMAL_FIELDNAME, CONVERSION_FIELDNAME);
        if (fieldname) {FREE(fieldname); fieldname = NULL;}
        return 0;
    }

    if (fieldname) {FREE(fieldname); fieldname = NULL;}

    createSingleString(pvApiCtx, Rhs + 1, fieldvalue);

    if (fieldvalue) {FREE(fieldvalue); fieldvalue = NULL;}

    LhsVar(1) = Rhs + 1;
    C2F(putlhsvar)();

    return 0;
}
/* ========================================================================== */
static int sci_csv_default_two_rhs(char *fname)
{
    int iErr = 0;
    int resultSet = 0;

    char *fieldname = NULL;
    char *fieldvalue = NULL;
    int  ifieldvalue = 0;

    fieldname = csv_getArgumentAsString(pvApiCtx, 1, fname, &iErr);
    if (iErr) return 0;

    if (strcmp(fieldname, PRECISION_FIELDNAME) == 0)
    {
        if (csv_isEmpty(pvApiCtx, 2))
        {
            if (fieldname) {FREE(fieldname); fieldname = NULL;}
            Scierror(999,_("%s: Wrong type for input argument #%d: A double expected.\n"), fname, 2);
            return 0;
        }

        if (csv_isDoubleScalar(pvApiCtx, 2))
        {
#define FORMAT_FIELDVALUESTR "%%.%dlg"
            ifieldvalue = (int) csv_getArgumentAsScalarDouble(pvApiCtx, 2, fname, &iErr);
            if (iErr)
            {
                if (fieldname) {FREE(fieldname); fieldname = NULL;}
                return 0;
            }

            if ((ifieldvalue < 1) || (ifieldvalue > 17))
            {
                if (fieldname) {FREE(fieldname); fieldname = NULL;}
                Scierror(999,_("%s: Wrong value for input argument #%d: A double (value 1 to 17) expected.\n"), fname, 2);
                return 0;
            }

            fieldvalue = (char*)MALLOC(sizeof(char) * ((int)strlen(FORMAT_FIELDVALUESTR)+1));
            if (fieldvalue == NULL)
            {
                if (fieldname) {FREE(fieldname); fieldname = NULL;}
                Scierror(999,_("%s: Memory allocation error.\n"), fname);
                return 0;
            }
            sprintf(fieldvalue, FORMAT_FIELDVALUESTR, ifieldvalue);
        }
        else
        {
            fieldvalue = csv_getArgumentAsString(pvApiCtx, 2, fname, &iErr);
            if (iErr)
            {
                if (fieldname) {FREE(fieldname); fieldname = NULL;}
                return 0;
            }
        }
    }
    else
    {
        fieldvalue = csv_getArgumentAsString(pvApiCtx, 2, fname, &iErr);
        if (iErr)
        {
            if (fieldname) {FREE(fieldname); fieldname = NULL;}
            return 0;
        }
    }


    if (strcmp(fieldname, SEPARATOR_FIELDNAME) == 0)
    {
        resultSet = setCsvDefaultSeparator(fieldvalue);
    }
    else if (strcmp(fieldname, DECIMAL_FIELDNAME) == 0)
    {
        resultSet = setCsvDefaultDecimal(fieldvalue);
    }
    else if (strcmp(fieldname, CONVERSION_FIELDNAME) == 0)
    {
        resultSet = setCsvDefaultConversion(fieldvalue);
    }
    else if (strcmp(fieldname, PRECISION_FIELDNAME) == 0)
    {
        resultSet = setCsvDefaultPrecision(fieldvalue);
    }
    else
    {
        Scierror(999,_("%s: Wrong value for input argument #%d: '%s', '%s' ,'%s' or '%s' expected.\n"), fname, 1, SEPARATOR_FIELDNAME, DECIMAL_FIELDNAME, CONVERSION_FIELDNAME, PRECISION_FIELDNAME);
        if (fieldname) {FREE(fieldname); fieldname = NULL;}
        if (fieldvalue) {FREE(fieldvalue); fieldvalue = NULL;}
        return 0;
    }

    createScalarBoolean(pvApiCtx, Rhs + 1, (resultSet == 0));

    if (fieldname) {FREE(fieldname); fieldname = NULL;}
    if (fieldvalue) {FREE(fieldvalue); fieldvalue = NULL;}

    LhsVar(1) = Rhs + 1;
    C2F(putlhsvar)();

    return 0;
}
/* ========================================================================== */
