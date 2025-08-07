package xls2csv_test

import (
	"fmt"
	"log"

	"github.com/northbright/xls2csv-go/xls2csv"
)

func ExampleXLS2CSV() {
	const xlsFile string = "files/hello-goodbye.xls"
	var err error
	records := [][]string{}

	// Call XLS2CSV() to convert XLS and get all records.
	if records, err = xls2csv.XLS2CSV(xlsFile, 0); err != nil {
		log.Printf("XLS2CSV() error: %v\n", err)
		goto end
	}

	for i, row := range records {
		fmt.Printf("%v", row)
		if i != len(records)-1 {
			fmt.Printf("\n")
		}
	}

end:
	// output:
	// [English Chinese Japanese]
	// [Hello 你好 こんにちは]
	// [Goodbye 再见 さようなら]
}
