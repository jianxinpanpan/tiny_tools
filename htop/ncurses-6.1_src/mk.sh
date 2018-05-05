#./configure --host=arm-linux-gnueabihf --prefix=`pwd`/install_ncurses --enable-widec --without-shared 
./configure --host=arm-linux-gnueabihf --prefix=`pwd`/install_ncurses --without-shared 
make -j4
make install -j4 -i
cp  install_ncurses/lib/libncurses.a install_ncurses/lib/libncurses6.a 
cp install_ncurses/include/ncurses/curses.h install_ncurses/include/curses.h 

