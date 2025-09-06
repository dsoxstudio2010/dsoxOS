// kernel/kernel.h - главный заголовочный файл ядра
#ifndef KERNEL_H
#define KERNEL_H

#include "vga.h"
#include "io.h"

// Точка входа ядра
void kernel_main(void);

// Вспомогательные функции
void panic(const char* message);

#endif
