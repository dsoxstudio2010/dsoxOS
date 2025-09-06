#!/bin/bash

echo "Building DSOX OS with serial support..."

# Компиляция загрузчика
echo "Compiling bootloader..."
nasm -f bin boot/boot.asm -o boot.bin

# Компиляция ядра
echo "Compiling kernel..."
cd kernel
gcc -ffreestanding -nostdlib -m32 -I. -c kernel.c -o ../kernel.o
gcc -ffreestanding -nostdlib -m32 -I. -c io.c -o ../io.o
cd ..

# Линковка ядра
echo "Linking kernel..."
ld -T linker.ld -m elf_i386 -nostdlib kernel.o io.o -o kernel.bin

# Создание образа диска
echo "Creating disk image..."
dd if=/dev/zero of=disk.img bs=512 count=2880
dd if=boot.bin of=disk.img conv=notrunc
dd if=kernel.bin of=disk.img bs=512 seek=1 conv=notrunc

echo "Build complete!"
echo "Run with: qemu-system-x86_64 -drive format=raw,file=disk.img -nographic -serial mon:stdio"
