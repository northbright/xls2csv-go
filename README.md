# xls2csv-go

Package xls2csv is a [Golang](https://golang.org) package which converts XLS file to CSV records. It's based on [libxls](https://github.com/libxls/libxls/).

#### Install `xls2csv` package
* xls2csv requires [libxls](https://github.com/libxls/libxls/) to be installed.
  * Install Dependencies
    * [libiconv](https://www.gnu.org/software/libiconv/)

      ```sh
      cd download
      wget https://ftp.gnu.org/pub/gnu/libiconv/libiconv-1.18.tar.gz
      tar -xzvf libiconv-1.18.tar.gz
      cd libiconv-1.18
      ```

      ```sh
      ./configure
      make
      sudo make install
      ```

  * Install [libxls](https://github.com/libxls/libxls/)

    ```sh
    wget https://github.com/libxls/libxls/releases/download/v1.6.3/libxls-1.6.3.tar.gz
    tar -xzvf libxls-1.6.3.tar.gz
    cd libxls-1.6.3
    ./configure
    make
    sudo make install
    ```

* Install `xls2csv` package

  ```sh
  CGO_CFLAGS=-I/usr/local/include CGO_LDFLAGS="-L/usr/local/lib -l xlsreader" go get github.com/northbright/xls2csv-go/xls2csv
  ```

#### Usage

```go
package main

import (
    "fmt"

    "github.com/northbright/xls2csv-go/xls2csv"
)

func main() {
    var err error

    f := "my.xls"
    sheetId := 0
    records := [][]string{}

    // Call XLS2CSV() to convert XLS and get all records.
    if records, err = xls2csv.XLS2CSV(f, sheetId); err != nil {
        fmt.Printf("err: %v\n", err)
        return
    }

    fmt.Printf("records: %v\n", records)
}
```

#### Build and Test Your App
```sh
CGO_CFLAGS=-I/usr/local/include CGO_LDFLAGS="-L/usr/local/lib -l xlsreader" go build
```

```sh
CGO_CFLAGS=-I/usr/local/include CGO_LDFLAGS="-L/usr/local/lib -l xlsreader" go test
```

#### Limitation
* UTF-8 encoded XLS files only

#### Alternatives
* [GO-xls](https://github.com/godzie44/go-xls)

  GO wrapper for libxls.

#### Documentation
* [API References](https://pkg.go.dev/github.com/northbright/xls2csv-go/xls2csv)

#### License
* [MIT License](LICENSE)
