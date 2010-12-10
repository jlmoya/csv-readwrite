/* ========================================================================== */
/* Allan CORNET */
/* DIGITEO 2010 */
/* ========================================================================== */
#include <string.h>
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
/* ========================================================================== */
#define SEPARATOR_FIELDNAME "separator"
#define DECIMAL_FIELDNAME "decimal"
#define CONVERSION_FIELDNAME "conversion"
#define RESET_PARAMATERS "reset"
/* ========================================================================== */
#define SEPARATOR_DISPLAY_FIELDNAME "separator:"
#define DECIMAL_DISPLAY_FIELDNAME "decimal:"
#define CONVERSION_DISPLAY_FIELDNAME "conversion:"
#define NUMBER_FIELD 3
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

        array[0] = strdup(SEPARATOR_DISPLAY_FIELDNAME);
        array[1] = strdup(DECIMAL_DISPLAY_FIELDNAME);
        array[2] = strdup(CONVERSION_DISPLAY_FIELDNAME);

        array[3] = strdup(getCsvDefaultSeparator());
        array[4] = strdup(getCsvDefaultDecimal());
        array[5] = strdup(getCsvDefaultConversion());

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
    SciErr sciErr;

    int *piAddressVarOne = NULL;
    int m1 = 0, n1 = 0;
    int iType1 = 0;
    char *fieldname = NULL;
    char *fieldvalue = NULL;

    sciErr = getVarAddressFromPosition(pvApiCtx, 1, &piAddressVarOne);
    if(sciErr.iErr)
    {
        printError(&sciErr, 0);
        return 0;
    }

    sciErr = getVarType(pvApiCtx, piAddressVarOne, &iType1);
    if(sciErr.iErr)
    {
        printError(&sciErr, 0);
        return 0;
    }

    if (iType1 != sci_strings)
    {
        Scierror(999,_("%s: Wrong type for input argument #%d: A string expected.\n"), fname, 1);
        return 0;
    }

    sciErr = getVarDimension(pvApiCtx, piAddressVarOne, &m1, &n1);

    if ( (m1 != n1) && (n1 != 1) )
    {
        Scierror(999,_("%s: Wrong size for input argument #%d: A string expected.\n"), fname, 1);
        return 0;
    }

    if (getAllocatedSingleString(pvApiCtx, piAddressVarOne, &fieldname))
    {
        Scierror(999,_("%s: Memory allocation error.\n"), fieldname);
        return 0;
    }

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
    SciErr sciErr;
    int resultSet = 0;

    int *piAddressVarOne = NULL;
    int m1 = 0, n1 = 0;
    int iType1 = 0;
    char *fieldname = NULL;

    int *piAddressVarTwo = NULL;
    int m2 = 0, n2 = 0;
    int iType2 = 0;
    char *fieldvalue = NULL;

    sciErr = getVarAddressFromPosition(pvApiCtx, 1, &piAddressVarOne);
    if(sciErr.iErr)
    {
        printError(&sciErr, 0);
        return 0;
    }

    sciErr = getVarType(pvApiCtx, piAddressVarOne, &iType1);
    if(sciErr.iErr)
    {
        printError(&sciErr, 0);
        return 0;
    }

    if (iType1 != sci_strings)
    {
        Scierror(999,_("%s: Wrong type for input argument #%d: A string expected.\n"), fname, 1);
        return 0;
    }

    sciErr = getVarDimension(pvApiCtx, piAddressVarOne, &m1, &n1);

    if ( (m1 != n1) && (n1 != 1) )
    {
        Scierror(999,_("%s: Wrong size for input argument #%d: A string expected.\n"), fname, 1);
        return 0;
    }

    if (getAllocatedSingleString(pvApiCtx, piAddressVarOne, &fieldname))
    {
        Scierror(999,_("%s: Memory allocation error.\n"), fieldname);
        return 0;
    }

    sciErr = getVarAddressFromPosition(pvApiCtx, 2, &piAddressVarTwo);
    if(sciErr.iErr)
    {
        if (fieldname) {FREE(fieldname); fieldname = NULL;}
        printError(&sciErr, 0);
        return 0;
    }

    sciErr = getVarType(pvApiCtx, piAddressVarTwo, &iType2);
    if(sciErr.iErr)
    {
        if (fieldname) {FREE(fieldname); fieldname = NULL;}
        printError(&sciErr, 0);
        return 0;
    }

    if (iType2 != sci_strings)
    {
        if (fieldname) {FREE(fieldname); fieldname = NULL;}
        Scierror(999,_("%s: Wrong type for input argument #%d: A string expected.\n"), fname, 2);
        return 0;
    }

    sciErr = getVarDimension(pvApiCtx, piAddressVarTwo, &m2, &n2);

    if ( (m2 != n2) && (n2 != 1) )
    {
        if (fieldname) {FREE(fieldname); fieldname = NULL;}
        Scierror(999,_("%s: Wrong size for input argument #%d: A string expected.\n"), fname, 2);
        return 0;
    }

    if (getAllocatedSingleString(pvApiCtx, piAddressVarTwo, &fieldvalue))
    {
        if (fieldname) {FREE(fieldname); fieldname = NULL;}
        Scierror(999,_("%s: Memory allocation error.\n"), fieldvalue);
        return 0;
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
    else
    {
        Scierror(999,_("%s: Wrong value for input argument #%d: '%s', '%s' or '%s' expected.\n"), fname, 1, SEPARATOR_FIELDNAME, DECIMAL_FIELDNAME, CONVERSION_FIELDNAME);
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
