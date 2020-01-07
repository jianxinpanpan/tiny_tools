su
mkdir -p rootfs_a32
 gunzip rootfs_a32.cpio.gz -k
cd rootfs_a32
cpio -idmv < ../rootfs_a32.cpio
