/* ========================================================================== */
/* Allan CORNET */
/* DIGITEO 2011 */
/* ========================================================================== */
#ifndef __GW_CSV_HELPERS_H__
#define __GW_CSV_HELPERS_H__

char *csv_getArgumentAsStringWithEmptyManagement(void* _pvCtx, int _iVar,
                                                 const char *fname, const char *defaultValue,
                                                 int *iErr);

char *csv_getArgumentAsString(void* _pvCtx, int _iVar,
                              const char *fname, int *iErr);

int csv_getArgumentAsScalarBoolean(void* _pvCtx, int _iVar,
                                   const char *fname, int *iErr);

char **csv_getArgumentAsMatrixOfString(void* _pvCtx, int _iVar,
                                       const char *fname,
                                       int *m, int *n, int *iErr);

int *csv_getArgumentAsMatrixofIntFromDouble(void* _pvCtx, int _iVar,
                                       const char *fname,
                                       int *m, int *n, int *iErr);

int csv_isRowVector(void* _pvCtx, int _iVar);
int csv_isColumnVector(void* _pvCtx, int _iVar);
int csv_isScalar(void* _pvCtx, int _iVar);

#endif /* __GW_CSV_HELPERS_H__ */
