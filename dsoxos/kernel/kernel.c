// kernel/kernel.c - основное ядро с serial выводом
#include "kernel.h"

// Текущая позиция курсора
static unsigned int cursor_x = 0;
static unsigned int cursor_y = 0;
static unsigned char current_color = 0x07;

void vga_clear_screen(unsigned char color) {
    unsigned short* buffer = (unsigned short*)VGA_MEMORY;
    for (unsigned int y = 0; y < VGA_HEIGHT; y++) {
        for (unsigned int x = 0; x < VGA_WIDTH; x++) {
            const unsigned int index = y * VGA_WIDTH + x;
            buffer[index] = vga_entry(' ', color);
        }
    }
    cursor_x = 0;
    cursor_y = 0;
}

void vga_put_char(char c, unsigned char color, unsigned int x, unsigned int y) {
    if (x >= VGA_WIDTH || y >= VGA_HEIGHT) return;
    
    unsigned short* buffer = (unsigned short*)VGA_MEMORY;
    const unsigned int index = y * VGA_WIDTH + x;
    buffer[index] = vga_entry(c, color);
}

void vga_put_string(const char* str, unsigned char color, unsigned int x, unsigned int y) {
    unsigned int i = 0;
    while (str[i] != '\0') {
        vga_put_char(str[i], color, x + i, y);
        i++;
    }
}

void vga_draw_box(unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2, unsigned char color) {
    for (unsigned int y = y1; y <= y2; y++) {
        for (unsigned int x = x1; x <= x2; x++) {
            if (x == x1 || x == x2 || y == y1 || y == y2) {
                vga_put_char('*', color, x, y);
            } else {
                vga_put_char(' ', color, x, y);
            }
        }
    }
}

void panic(const char* message) {
    serial_puts("\r\nKERNEL PANIC: ");
    serial_puts(message);
    serial_puts("\r\n");
    
    vga_put_string("KERNEL PANIC: ", vga_entry_color(VGA_COLOR_RED, VGA_COLOR_BLACK), 0, 0);
    vga_put_string(message, vga_entry_color(VGA_COLOR_WHITE, VGA_COLOR_RED), 14, 0);
    
    while(1) io_wait();
}

void kernel_main(void) {
    // Инициализация serial порта
    serial_init();
    serial_puts("\r\n=== DSOX OS Initializing ===\r\n");
    serial_puts("Serial port: OK\r\n");
    
    // Инициализация VGA
    vga_clear_screen(vga_entry_color(VGA_COLOR_BLACK, VGA_COLOR_BLACK));
    serial_puts("VGA: OK\r\n");
    
    // Вывод приветствия
    vga_put_string("DSOX Operating System", 
                  vga_entry_color(VGA_COLOR_LIGHT_GREEN, VGA_COLOR_BLACK), 30, 2);
    serial_puts("Display: DSOX Operating System\r\n");
    
    vga_put_string("Kernel loaded successfully!",
                  vga_entry_color(VGA_COLOR_YELLOW, VGA_COLOR_BLACK), 25, 4);
    serial_puts("Status: Kernel loaded successfully!\r\n");
    
    // Информация о системе
    vga_put_string("Video: VGA Text Mode 80x25",
                  vga_entry_color(VGA_COLOR_LIGHT_CYAN, VGA_COLOR_BLACK), 25, 6);
    
    vga_put_string("Memory: Protected Mode Enabled",
                  vga_entry_color(VGA_COLOR_LIGHT_MAGENTA, VGA_COLOR_BLACK), 25, 7);
    
    vga_put_string("Serial: COM1 9600 baud",
                  vga_entry_color(VGA_COLOR_LIGHT_BLUE, VGA_COLOR_BLACK), 25, 8);
    
    serial_puts("Video: VGA Text Mode 80x25\r\n");
    serial_puts("Memory: Protected Mode Enabled\r\n");
    serial_puts("Serial: COM1 9600 baud\r\n");
    
    // Рисуем рамку вокруг информации
    vga_draw_box(20, 1, 60, 10, vga_entry_color(VGA_COLOR_WHITE, VGA_COLOR_BLACK));
    serial_puts("UI: Frame drawn\r\n");
    
    // Вывод цветовой палитры
    vga_put_string("Color test:", vga_entry_color(VGA_COLOR_GRAY, VGA_COLOR_BLACK), 2, 12);
    serial_puts("Display: Color test\r\n");
    
    const char* color_names[] = {
        "Black", "Blue", "Green", "Cyan", "Red", "Magenta",
        "Brown", "Gray", "Dark Gray", "Light Blue", "Light Green",
        "Light Cyan", "Light Red", "Light Magenta", "Yellow", "White"
    };
    
    for (int i = 0; i < 16; i++) {
        vga_put_string(color_names[i], vga_entry_color(i, VGA_COLOR_BLACK), 2, 14 + i);
    }
    
    serial_puts("Display: Color palette shown\r\n");
    serial_puts("\r\n=== System Ready ===\r\n");
    serial_puts("Press Ctrl+A then X to exit QEMU\r\n");
    
    // Бесконечный цикл
    while(1) {
        io_wait();
    }
}
