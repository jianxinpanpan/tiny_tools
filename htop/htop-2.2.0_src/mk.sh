./configure --prefix=`pwd`/install_htop  --disable-unicode --host=arm-linux-gnueabihf  LDFLAGS=-L"/mnt/fileroot/jianxin.pan/git_pan/tiny_tools/htop/ncurses-6.1_src/install_ncurses/lib --static" CPPFLAGS=-I/mnt/fileroot/jianxin.pan/git_pan/tiny_tools/htop/ncurses-6.1_src/install_ncurses/include/ --enable-proc --enable-cgroup  --enable-taskstats --enable-linux-affinity   --enable-setuid  
make -j4
make install -j4
mkdir -p ../bin_s/bin
mkdir -p ../bin_s/share
cp ./install_htop//bin/* ../bin_s/bin/ -rfv
cp ../ncurses-6.1_src/install_ncurses/share/terminfo/* ../bin_s/share/ -rfv
