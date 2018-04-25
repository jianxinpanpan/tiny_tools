mkdir share_dir
qemu-system-aarch64  -machine virt -cpu cortex-a57  -nographic -m 1024M -smp 4 -kernel ../open_src/kernel_android4.9/arch/arm64/boot/Image   --append "rdinit=/linuxrc console=ttyAMA0" -fsdev local,security_model=passthrough,id=fsdev0,path=share_dir -device virtio-9p-pci,id=fs0,fsdev=fsdev0,mount_tag=hostshare -S -s

#gdb
#arm-linux-gnueabi-gdb --tui vmlinux
#(gdb) target remote localhost:1234  //通过1234端口远程连接到QEMU平台
#(gdb) b start_target				 //在start_kernel处设置断点
#(gdb) c

#host
#mkdir share_dir
#board
#mkdir /tmp/host_files
#mount -t 9p -o trans=virtio,version=9p2000.L hostshare /tmp/host_files
