package xls2csv_test

import (
	"fmt"
	"log"

	"github.com/northbright/pathhelper"
	"github.com/northbright/xls2csv-go/xls2csv"
)

func ExampleXLS2CSV() {
	const xlsFile string = "./files/my.xls"
	var err error
	records := [][]string{}

	f, _ := pathhelper.GetAbsPath(xlsFile)
	if records, err = xls2csv.XLS2CSV(f, 0); err != nil {
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
	//[Product Vendor Price]
	//[iPhone 7 Plus Gold 128GB Apple 7188]
	//[iPhone 7 Plus Gold 128GB JD 6399]
	//[iPhone 7 Plus Gold 128GB YHD 6488]
	//[iPhone 7 Gold 128GB Apple 6188]
	//[iPhone 7 Gold 128GB JD 5499]
	//[iPhone 7 Gold 128GB YHD 5498]
}
