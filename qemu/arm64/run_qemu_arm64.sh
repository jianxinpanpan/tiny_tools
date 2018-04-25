qemu-system-aarch64  -machine virt -cpu cortex-a57  -nographic -m 1024M -smp 4 -kernel ../open_src/kernel_android4.9/arch/arm64/boot/Image   --append "rdinit=/linuxrc console=ttyAMA0"
