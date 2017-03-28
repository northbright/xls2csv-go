# xls2csv-go

Package xls2csv is a [Golang](https://golang.org) package which converts XLS file to CSV records. It's based on [libxls](http://libxls.sourceforge.net/) and [xls2csv](https://github.com/northbright/xls2csv).

#### Install `xls2csv` package
* xls2csv requires [libxls](http://libxls.sourceforge.net/) to be installed.

        wget http://downloads.sourceforge.net/libxls/libxls-0.2.0.tar.gz
        tar -xzvf libxls-0.2.0.tar.gz
        cd libxls-0.2.0
        ./configure
        make
        sudo make install 

* Install `xls2csv` package

        CGO_CFLAGS=-I/usr/local/libxls/include CGO_LDFLAGS="-L/usr/local/libxls/lib -l xlsreader" go get github.com/northbright/xls2csv-go/xls2csv

#### Usage

    package main

    import (
        "fmt"

        "github.com/northbright/xls2csv-go/xls2csv"
    )

    func main() {
        var err error

        f := "/home/xx/my.xls"
        sheetId := 0
        records := [][]string{}

        // Call XLS2CSV() to convert XLS and get all records.
        if records, err = xls2csv.XLS2CSV(f, sheetId); err != nil {
            fmt.Printf("err: %v\n", err)
            return
        }

        fmt.Printf("records: %v\n", records)
    }

#### Add Path of `libxlsreader.so` to `LD_LIBRARY_PATH` Before Run Your Golang App or `go test`

        export LD_LIBRARY_PATH="/usr/local/libxls/lib":$LD_LIBRARY_PATH
        go test -c && ./xls2csv.test

#### Documentation
* [API References](https://godoc.org/github.com/northbright/xls2csv-go/xls2csv)

#### License
* [MIT License](LICENSE)
