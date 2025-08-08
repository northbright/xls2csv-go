#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#if defined(__APPLE__)
    #include <stdlib.h>
#else
    #include <malloc.h>
#endif
#include <stdarg.h>

#include <xls.h>
#include "appendstr.h"

static char *lineSeparator = "\n";
static char *fieldSeparator = ",";

// xls2csv reads XLS files and convert XLS data to CSV string.
//     Params:
//       pstrXLSFile: file name of XLS.
//       nSheetId: index of sheets(zero-based).
//     Return:
//       pointer to a memory block contains converted CSV string if succeeded or NULL if failed.
//       It should call free() to free the memory block after use.
//     Example:
//       char * buf = xls2csv("1.csv", 2);
//       if (buf != NULL) {
//           // Do something on the buffer.
//           ......
//           free(buf);
//           buf = NUL;
//       }
char *xls2csv(char *pstrXLSFile, int nSheetId) {
    xls_error_t error = LIBXLS_OK;
    WORD i, j = 0;
    xlsWorkBook *pWB = NULL;
    xlsWorkSheet *pWS = NULL;
    struct st_row_data *row = NULL;
    char *buf = NULL;

    pWB = xls_open_file(pstrXLSFile, "utf-8", &error);
    if (pWB == NULL) {
        printf("xls_open_file: %s error: %s\n", pstrXLSFile, xls_getError(error));
        goto end;
    }

    if (pWB->sheets.count <= 0) {
        printf("xls2csv() error: sheet count <= 0\n");
        goto end;
    }

    if ((nSheetId < 0) || (nSheetId >= pWB->sheets.count)) {
        printf("xls2csv() error: nSheet < 0 or >= sheet count.\n");
        goto end;
    }

    // Open and parse the sheet.
    pWS = xls_getWorkSheet(pWB, nSheetId);
    xls_parseWorkSheet(pWS);

    // process all rows of the sheet
    for (i = 0; i <= (unsigned int)pWS->rows.lastrow; i++) {
        for (j = 0; j <= pWS->rows.lastcol; j++) {
            xlsCell *cell = xls_cell(pWS, i, j);

            if ((!cell) || (cell->isHidden)) {
                continue;
            }

            // display the value of the cell (either numeric or string)
            if (cell->id == XLS_RECORD_RK || cell->id == XLS_RECORD_MULRK || cell->id == XLS_RECORD_NUMBER) {
                buf = appendStr(buf, "%.15g", cell->d);
            } else if (cell->id == XLS_RECORD_FORMULA || cell->id == XLS_RECORD_FORMULA_ALT) {
                // formula
                if (cell->l == 0) // its a number
                {
                    buf = appendStr(buf, "%.15g", cell->d);
                } else if (cell->str) {
                    if (!strcmp((char *)cell->str, "bool")) // its boolean, and test cell->d
                    {
                        buf = appendStr(buf, (int) cell->d ? "true" : "false");
                    } else if (!strcmp((char *)cell->str, "error")) // formula is in error
                    {
                        buf = appendStr(buf, "*error*");
                    } else // ... cell->str is valid as the result of a string formula.
                    {
                        buf = appendStr(buf, (char *)cell->str);
                    }
                }
            } else if (cell->str) {
                buf = appendStr(buf, (char *)cell->str);
                printf("%s", (char *)cell->str);
            } else {
                buf = appendStr(buf, "");
            }

            // Write field separator.
            if (j != pWS->rows.lastcol) {
                buf = appendStr(buf, fieldSeparator);
            }
        }

        // Write link separator(breaker).
        if (i != pWS->rows.lastrow) {
            buf = appendStr(buf, lineSeparator);
        }
    }

end:
    if (pWS != NULL) {
        xls_close_WS(pWS);
        pWS = NULL;
    }

    if (pWB != NULL) {
        xls_close(pWB);
        pWB = NULL;
    }

    return buf;
}
