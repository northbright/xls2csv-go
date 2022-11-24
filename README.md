# xls2csv-go

[![Build Status](https://travis-ci.org/northbright/xls2csv-go.svg?branch=master)](https://travis-ci.org/northbright/xls2csv-go)
[![Go Report Card](https://goreportcard.com/badge/github.com/northbright/xls2csv-go)](https://goreportcard.com/report/github.com/northbright/xls2csv-go)
[![GoDoc](https://godoc.org/github.com/northbright/xls2csv-go/xls2csv?status.svg)](https://godoc.org/github.com/northbright/xls2csv-go/xls2csv)

Package xls2csv is a [Golang](https://golang.org) package which converts XLS file to CSV records. It's based on [libxls](https://github.com/libxls/libxls/) and [xls2csv](https://github.com/northbright/xls2csv).

#### Install `xls2csv` package
* xls2csv requires [libxls](https://github.com/libxls/libxls/) to be installed.

  * Install libxls

    ```
    wget https://github.com/libxls/libxls/releases/download/v1.6.2/libxls-1.6.2.tar.gz
    tar -xzvf libxls-1.6.2.tar.gz
    cd libxls-1.6.2
    ./configure
    make
    sudo make install
    ```

  * Add libxls lib path to `LD_LIBRARY_PATH`
    * Create a new `/etc/ld.so.conf.d/libxls.conf`

              sudo vi /etc/ld.so.conf.d/libxls.conf

              // Add path of libxls to this file
              /usr/local/libxls/lib

    * Update `LD_LIBRARY_PATH`

            sudo ldconfig
            // Check libxlsreader.so
            sudo ldconfig -p | grep libxls

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

#### Build and Test Your App
  * Do not forget to add `CGO_CFLAGS=-I/usr/local/libxls/include CGO_LDFLAGS="-L/usr/local/libxls/lib -l xlsreader"` before `go build` or `go test`

          CGO_CFLAGS=-I/usr/local/libxls/include CGO_LDFLAGS="-L/usr/local/libxls/lib -l xlsreader" go build

#### Documentation
* [API References](https://godoc.org/github.com/northbright/xls2csv-go/xls2csv)

#### License
* [MIT License](LICENSE)
