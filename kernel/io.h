// kernel/io.h - добавляем serial функции
#ifndef IO_H
#define IO_H

// Чтение из порта
static inline unsigned char inb(unsigned short port) {
    unsigned char ret;
    asm volatile ("inb %1, %0" : "=a"(ret) : "Nd"(port));
    return ret;
}

// Запись в порт
static inline void outb(unsigned short port, unsigned char val) {
    asm volatile ("outb %0, %1" : : "a"(val), "Nd"(port));
}

// Ожидание
void io_wait(void);

// Serial порт функции
void serial_init(void);
void serial_putchar(char c);
void serial_puts(const char* str);

#endif
