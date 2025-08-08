package xls2csv_test

import (
	"fmt"
	"log"

	"github.com/northbright/xls2csv-go/xls2csv"
)

func ExampleXLS2CSV() {
	type XLSFile struct {
		File    string
		SheetID int
	}

	xlsFiles := []XLSFile{
		XLSFile{"files/hello-goodbye.xls", 0},
		XLSFile{"files/campus-a.xls", 2},
	}

	var err error
	records := [][]string{}

	for _, f := range xlsFiles {
		fmt.Printf("file: %s, sheet ID: %d\n", f.File, f.SheetID)

		// Call XLS2CSV() to convert XLS and get all records.
		if records, err = xls2csv.XLS2CSV(f.File, f.SheetID); err != nil {
			log.Printf("XLS2CSV() error: %v\n", err)
			goto end
		}

		for i, row := range records {
			fmt.Printf("%v", row)
			if i != len(records)-1 {
				fmt.Printf("\n")
			}
		}

		fmt.Printf("\n\n")
	}

end:
	// output:
	// file: files/hello-goodbye.xls, sheet ID: 0
	// [English Chinese Japanese]
	// [Hello 你好 こんにちは]
	// [Goodbye 再见 さようなら]
	//
	// file: files/campus-a.xls, sheet ID: 2
	// [考 勤 记 录 表 ]
	// [考勤时间  2017-07-01 ~ 2017-07-07       制表时间  2017-07-12              ]
	// [1 2 3 4 5 6 7                        ]
	// [工 号:  7      姓 名:  Mary        部 门:  公司          ]
	// [20:49 09:3421:24   17:34 09:2117:36 11:5220:44                        ]
	// [工 号:  8      姓 名:  Bob        部 门:  公司          ]
	// [08:4520:07 08:4618:54 08:2018:18 08:51 08:50  11:5420:44                        ]
	// [工 号:  9      姓 名:  Jack        部 门:  公司          ]
	// [18:02 16:59 18:17 08:58   11:5620:36                        ]
}
