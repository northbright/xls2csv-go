#!/bin/sh

wget http://downloads.sourceforge.net/libxls/libxls-0.2.0.tar.gz
tar -xzvf libxls-0.2.0.tar.gz
cd libxls-0.2.0
./configure
make
sudo make install

cd ../xls2csv
CGO_CFLAGS="-I/usr/local/libxls/include" CGO_LDFLAGS="-L/usr/local/libxls/lib -lxlsreader" go build
