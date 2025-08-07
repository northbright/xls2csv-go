package xls2csv

/*
#include <stdio.h>
#include <stdlib.h>
#include "xls2csv.h"
*/
import "C"

import (
	"encoding/csv"
	"fmt"
	"strings"
	"unsafe"
)

// XLS2CSV converts XLS file to CSV records.
//
//	Params:
//	  xlsFile: XLS file name.
//	  sheetID: sheet ID to be converted. It's 0-based.
//	Return:
//	  records: CSV records. Each record is a slice of fields.
//	           See https://godoc.org/encoding/csv#Reader.ReadAll for more info.
func XLS2CSV(xlsFile string, sheetID int) (records [][]string, err error) {
	var buf *C.char
	var r *csv.Reader

	f := C.CString(xlsFile)
	// C string should be free after use.
	defer C.free(unsafe.Pointer(f))

	id := C.int(sheetID)

	// xls2csv() will return a buffer(char *) contains CSV string.
	// The buffer should be free in C.
	buf = C.xls2csv(f, id)
	if buf == nil {
		err = fmt.Errorf("xls2csv() error")
		goto end
	}

	// Free memory block after use.
	defer C.free(unsafe.Pointer(buf))

	r = csv.NewReader(strings.NewReader(C.GoString(buf)))
	records, err = r.ReadAll()

end:
	if err != nil {
		return [][]string{}, err
	}

	return records, nil
}
