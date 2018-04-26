su
cd rootfs_a32
find . | cpio -o -H newc | gzip > ../rootfs_a32.cpio.gz
