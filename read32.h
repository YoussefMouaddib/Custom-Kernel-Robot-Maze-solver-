#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <stdint.h>


#define GPIO_BASE           0xFE200000  // GPIO controller base address on RPi 4 Model B
#define PAGE_SIZE (4*1024)
#define BLOCK_SIZE (4*1024)

int  mem_fd;
void *gpio_map;
volatile uint32_t *gpio;

void setup_io()
{
    /* open /dev/mem */
    if ((mem_fd = open("/dev/mem", O_RDWR|O_SYNC) ) < 0) {
        printf("can't open /dev/mem \n");
        exit(-1);
    }

    /* mmap GPIO */
    gpio_map = mmap(
        NULL,             //Any address in our space will do
        BLOCK_SIZE,       //Map length
        PROT_READ|PROT_WRITE,// Enable reading & writing to mapped memory
        MAP_SHARED,       //Shared with other processes
        mem_fd,           //File to map
        GPIO_BASE         //Offset to GPIO peripheral
    );

    close(mem_fd); //No need to keep mem_fd open after mmap

    if (gpio_map == MAP_FAILED) {
        printf("mmap error %p\n", gpio_map);//errno also set!
        exit(-1);
    }

    gpio = (volatile uint32_t *)gpio_map;
}

uint32_t read32(int pin)
{
    /* Set GPIO pin as input */
    *(gpio + (pin/10)) &= ~(7<<((pin%10)*3));

    /* Read GPIO value */
    return (*(gpio + 13) & (1<<pin)) ? 1 : 0;
}

