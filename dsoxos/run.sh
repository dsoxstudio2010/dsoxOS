#!/bin/bash

echo "Starting DSOX OS in QEMU..."

# Вариант 1: Запуск с выводом в терминал через serial
qemu-system-x86_64 \
#    -drive format=raw,file=disk.img \
#    -serial stdio \
#    -display none

# Вариант 2: Запуск с графическим интерфейсом (если есть X11)
qemu-system-x86_64 -drive format=raw,file=disk.img

# Вариант 3: Запуск с VNC (раскомментируйте если нужно)
# qemu-system-x86_64 -drive format=raw,file=disk.img -vnc :0
