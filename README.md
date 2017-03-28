# xls2csv-go

package xls2csv converts XLS file to CSV records. It's based on [libxls](http://libxls.sourceforge.net/) and [xls2csv](https://github.com/northbright/xls2csv).

#### Building
* xls2csv requires [libxls](http://libxls.sourceforge.net/) to be installed.

        wget http://downloads.sourceforge.net/libxls/libxls-0.2.0.tar.gz
        tar -xzvf libxls-0.2.0.tar.gz
        cd libxls-0.2.0
        ./configure
        make
        sudo make install 

*  Install xls2csv package

    * If you build [libxls](http://libxls.sourceforge.net/) and put the shared library and headers in one of the standard places for your OS, you'll be able to simply run:

          go get github.com/northbright/xls2csv-go

    * If put the shared [libxls](http://libxls.sourceforge.net/) library somewhere weird like /path/to/lib and the headers were installed in /path/to/include. To install xls2csv-go remotely, you'll run:

          CGO_CFLAGS="-I/path/to/include" CGO_LDFLAGS="-L/path/to/lib -lxlsreader" go get github.com/northbright/xls2csv-go

#### Documentation
* [API References](https://godoc.org/github.com/northbright/xls2csv-go/xls2csv)

#### License
* [MIT License](LICENSE)
