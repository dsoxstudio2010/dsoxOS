// kernel/vga.h - работа с видеопамятью VGA
#ifndef VGA_H
#define VGA_H

#define VGA_WIDTH 80
#define VGA_HEIGHT 25
#define VGA_MEMORY 0xB8000

// Цвета текстового режима VGA
typedef enum {
    VGA_COLOR_BLACK = 0,
    VGA_COLOR_BLUE = 1,
    VGA_COLOR_GREEN = 2,
    VGA_COLOR_CYAN = 3,
    VGA_COLOR_RED = 4,
    VGA_COLOR_MAGENTA = 5,
    VGA_COLOR_BROWN = 6,
    VGA_COLOR_GRAY = 7,
    VGA_COLOR_DARK_GRAY = 8,
    VGA_COLOR_LIGHT_BLUE = 9,
    VGA_COLOR_LIGHT_GREEN = 10,
    VGA_COLOR_LIGHT_CYAN = 11,
    VGA_COLOR_LIGHT_RED = 12,
    VGA_COLOR_LIGHT_MAGENTA = 13,
    VGA_COLOR_YELLOW = 14,
    VGA_COLOR_WHITE = 15,
} vga_color;

// Создание атрибута цвета
static inline unsigned char vga_entry_color(vga_color fg, vga_color bg) {
    return fg | bg << 4;
}

// Создание символа с атрибутом
static inline unsigned short vga_entry(unsigned char uc, unsigned char color) {
    return (unsigned short) uc | (unsigned short) color << 8;
}

// Очистка экрана
void vga_clear_screen(unsigned char color);

// Вывод символа
void vga_put_char(char c, unsigned char color, unsigned int x, unsigned int y);

// Вывод строки
void vga_put_string(const char* str, unsigned char color, unsigned int x, unsigned int y);

// Рисование рамки
void vga_draw_box(unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2, unsigned char color);

#endif
