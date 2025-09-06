// kernel/io.c - реализация serial функций
#include "io.h"

void io_wait(void) {
    outb(0x80, 0);
}

// Инициализация serial порта (COM1)
void serial_init(void) {
    outb(0x3F8 + 1, 0x00);    // Отключаем прерывания
    outb(0x3F8 + 3, 0x80);    // Включаем DLAB
    outb(0x3F8 + 0, 0x03);    // Устанавливаем делитель (лоу байт)
    outb(0x3F8 + 1, 0x00);    // Устанавливаем делитель (хай байт)
    outb(0x3F8 + 3, 0x03);    // 8 бит, нет паритета, 1 стоп-бит
    outb(0x3F8 + 2, 0xC7);    // Включаем FIFO
    outb(0x3F8 + 4, 0x0B);    // Включаем IRQ
}

// Вывод символа в serial
void serial_putchar(char c) {
    while ((inb(0x3F8 + 5) & 0x20) == 0); // Ждем готовности передатчика
    outb(0x3F8, c);
}

// Вывод строки в serial
void serial_puts(const char* str) {
    while (*str) {
        if (*str == '\n') {
            serial_putchar('\r'); // Добавляем carriage return для новых строк
        }
        serial_putchar(*str);
        str++;
    }
}
