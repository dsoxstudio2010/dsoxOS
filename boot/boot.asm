; boot/boot.asm - загрузчик с загрузкой ядра
bits 16
org 0x7C00

KERNEL_OFFSET equ 0x1000

start:
    mov ax, 0
    mov ds, ax
    mov es, ax
    mov ss, ax
    mov sp, 0x7C00

    ; Сообщение о загрузке
    mov si, msg_loading
    call print_string

    ; Загрузка ядра
    mov bx, KERNEL_OFFSET
    mov dh, 8               ; 8 секторов для ядра
    call disk_load

    ; Переход в защищенный режим
    call switch_to_pm
    jmp $

disk_load:
    mov ah, 0x02
    mov al, dh
    mov ch, 0x00
    mov dh, 0x00
    mov cl, 0x02
    int 0x13
    jc disk_error
    ret

disk_error:
    mov si, msg_disk_error
    call print_string
    jmp $

print_string:
    mov ah, 0x0E
.print_char:
    lodsb
    cmp al, 0
    je .done
    int 0x10
    jmp .print_char
.done:
    ret

switch_to_pm:
    cli
    lgdt [gdt_descriptor]
    mov eax, cr0
    or eax, 0x1
    mov cr0, eax
    jmp CODE_SEG:init_pm

bits 32
init_pm:
    mov ax, DATA_SEG
    mov ds, ax
    mov ss, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ebp, 0x90000
    mov esp, ebp
    call KERNEL_OFFSET
    jmp $

; GDT
gdt_start:
gdt_null: dd 0x0, 0x0
gdt_code: dw 0xffff, 0x0, 0x9a00, 0x00cf
gdt_data: dw 0xffff, 0x0, 0x9200, 0x00cf
gdt_end:

gdt_descriptor:
    dw gdt_end - gdt_start - 1
    dd gdt_start

CODE_SEG equ gdt_code - gdt_start
DATA_SEG equ gdt_data - gdt_start

msg_loading db 'Loading kernel...', 0
msg_disk_error db 'Disk error!', 0

times 510 - ($ - $$) db 0
dw 0xAA55
