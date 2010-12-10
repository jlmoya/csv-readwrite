/* ========================================================================== */
/* Allan CORNET */
/* DIGITEO 2010 */
/* ========================================================================== */
#ifndef __CSV_DEFAULT_H__
#define __CSV_DEFAULT_H__

const char *getCsvDefaultSeparator(void);
const char *getCsvDefaultDecimal(void);
const char *getCsvDefaultConversion(void);

int setCsvDefaultSeparator(const char *separator);
int setCsvDefaultDecimal(const char *decimal);
int setCsvDefaultConversion(const char *conversion);

int setCsvDefaultReset(void);

#endif /* __CSV_DEFAULT_H__ */
/* ========================================================================== */