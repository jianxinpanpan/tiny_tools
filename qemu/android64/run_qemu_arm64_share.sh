mkdir -p share_dir
qemu-system-aarch64  -machine virt -cpu cortex-a53  -nographic -m 1024M -smp 4 -kernel ./Image   --append "rdinit=/linuxrc console=ttyAMA0" -fsdev local,security_model=passthrough,id=fsdev0,path=share_dir -device virtio-9p-pci,id=fs0,fsdev=fsdev0,mount_tag=hostshare  


#host
#mkdir share_dir
#board
#mkdir /tmp/host_files
#mount -t 9p -o trans=virtio,version=9p2000.L hostshare /tmp/host_files
