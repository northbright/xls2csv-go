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

    // Process all rows of the sheet.
    for (i = 0; i <= pWS->rows.lastrow; i++) {
        row = &(pWS->rows.row[i]);

        // Process cells
        for (j = 0; j <= pWS->rows.lastcol; j++) {
            // Display the value of the cell (either numeric or string)
            if (row->cells.cell[j].id == 0x27e || row->cells.cell[j].id==0x0BD || row->cells.cell[j].id==0x203) {
                buf = appendStr(buf, "%.15g", row->cells.cell[j].d);
            } else if (row->cells.cell[j].str != NULL) {
                buf = appendStr(buf, row->cells.cell[j].str);
            } else {
                // Skip if cell value is not number or string.
                continue;
            }

            if (j != pWS->rows.lastcol) {
                buf = appendStr(buf, ",");
            }
        }

        // Write line break.
        if (i != pWS->rows.lastrow) {
            buf = appendStr(buf, "\n");
        }
    } 

end:
    if (pWB != NULL) {
        xls_close(pWB);
        pWB = NULL;
    }

    return buf;
}
