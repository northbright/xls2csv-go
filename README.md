# xls2csv-go

package xls2csv converts XLS file to CSV records. It's based on [libxls](http://libxls.sourceforge.net/) and [xls2csv](https://github.com/northbright/xls2csv).

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

#### Documentation
* [API References](https://godoc.org/github.com/northbright/xls2csv-go/xls2csv)

#### License
* [MIT License](LICENSE)
