# Compiler and linker options
CC = arm-none-eabi-gcc
AS = arm-none-eabi-as
LD = arm-none-eabi-ld
OBJCOPY = arm-none-eabi-objcopy
CFLAGS = -c -ffreestanding -O2 -Wall -Wextra -Werror -I ./include
LDFLAGS = -T linker.ld -ffreestanding -O2 -nostdlib -lgcc

# Source files
SRC = start.s main.c 
HDR = pmwleft.h main.h pmwright.h read32.h

# Object files
OBJ = $(SRC:%.c=%.o) $(SRC:%.s=%.o)

# Default target
all: kernel7.img

# Compile assembly source files
%.o: %.s
	$(AS) -o $@ $<

# Compile C source files
%.o: %.c $(HDR)
	$(CC) $(CFLAGS) -o $@ $<

# Link object files into kernel7.elf
kernel7.elf: $(OBJ)
	$(LD) $(LDFLAGS) -o $@ $^

# Convert kernel7.elf to kernel7.img
kernel7.img: kernel7.elf
	$(OBJCOPY) $< -O binary $@

# Clean up object files and kernel image
clean:
	rm -f $(OBJ) kernel7.elf kernel7.img
