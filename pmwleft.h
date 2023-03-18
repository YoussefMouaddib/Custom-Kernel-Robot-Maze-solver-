
/******************************************************************************
Robot Maze solver for RPi4B.
Youssef Mouaddib, IEEE St. Mary's University, spring 2023.
*******************************************************************************/

#include <stdio.h>
#include "main.h"

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <stdint.h>

#define GPIO_BASE           0xFE200000  // GPIO controller base address on RPi 4 Model B
#define PWM_BASE            0xFE20C000  // PWM controller base address on RPi 4 Model B
#define PAGE_SIZE (4*1024)
#define BLOCK_SIZE (4*1024)
#define PWM_CTL             0           // PWM control register offset
#define PWM_RNG1            4           // PWM range register offset
#define PWM_DAT1            5           // PWM data register offset
#define PWMCLK_CNTL        40           // PWM clock control register offset
#define PWMCLK_DIV         41           // PWM clock divisor register offset

#define GPIO_PIN            18          // PWM pin number

#define PWM_FREQUENCY       500000     // PWM frequency in Hz
#define PWM_RANGE           1024        // PWM range (max value of duty cycle)

#define BUS_TO_PHYS(x) ((x) & ~0xC0000000)

int pmwLeftlow() {
    // Map the GPIO and PWM controllers to memory
    int mem_fd = open("/dev/mem", O_RDWR | O_SYNC);
    if (mem_fd < 0) {
        perror("Failed to open /dev/mem");
        exit(-1);
    }

    void *gpio_map = mmap(NULL, BLOCK_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, mem_fd, GPIO_BASE);
    void *pwm_map = mmap(NULL, BLOCK_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, mem_fd, PWM_BASE);

    close(mem_fd);

    if (gpio_map == MAP_FAILED) {
        perror("Failed to mmap GPIO");
        exit(-1);
    }

    if (pwm_map == MAP_FAILED) {
        perror("Failed to mmap PWM");
        exit(-1);
    }

    volatile uint32_t *gpio = (volatile uint32_t *) gpio_map;
    volatile uint32_t *pwm = (volatile uint32_t *) pwm_map;

    // Configure PWM clock
    *(pwm + PWMCLK_CNTL) = 0x5A000006;   // Set password and disable clock
    while (*(pwm + PWMCLK_CNTL) & 0x80) {}  // Wait for clock to be disabled
    *(pwm + PWMCLK_DIV) = 0x5A000000 | (uint32_t)(500000000/PWM_FREQUENCY);  // Set password and set divisor
    *(pwm + PWMCLK_CNTL) = 0x5A000016;   // Set password and enable clock
    while (*(pwm + PWMCLK_CNTL) & 0x80) {}  // Wait for clock to be enabled

    // Configure PWM pin as ALT5
    int gpio_pin = GPIO_PIN;
    int gpio_pin_offset = gpio_pin / 10;
    int gpio_pin_shift = (gpio_pin % 10) * 3;

    *(gpio + gpio_pin_offset) &= ~(0x7 << gpio_pin_shift);   // Clear function bits
    *(gpio + gpio_pin_offset) |= (0x2 << gpio_pin_shift);    // Set function bits to ALT5

    // Configure PWM
    *(pwm + PWM_CTL) = 0;               // Disable PWM
    *(pwm + PWM_RNG1) = PWM_RANGE;      // Set PWM range
    *(pwm + PWM_DAT1) = PWM_RANGE/2;    

    // Enable PWM
    *(pwm + PWM_CTL) |= (1 << 7);       // Use PWM1
    *(pwm + PWM_CTL) |= (1 << 0);       // Enable PWM

    // Loop to generate a PWM signal with a varying duty cycle
    int i;
    for (i = 0; i < 10; i++) {
        int duty_cycle = (i+1) * PWM_RANGE / 10;
        *(pwm + PWM_DAT1) = duty_cycle;
        usleep(500000);  // Wait for 500ms
    }

    // Disable PWM
    *(pwm + PWM_CTL) &= ~(1 << 0);

    // Unmap memory
    munmap(gpio_map, BLOCK_SIZE);
    munmap(pwm_map, BLOCK_SIZE);

    return 0;
}
int pmwlefthigh() {
    // Map the GPIO and PWM controllers to memory
    int mem_fd = open("/dev/mem", O_RDWR | O_SYNC);
    if (mem_fd < 0) {
        perror("Failed to open /dev/mem");
        exit(-1);
    }

    void *gpio_map = mmap(NULL, BLOCK_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, mem_fd, GPIO_BASE);
    void *pwm_map = mmap(NULL, BLOCK_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, mem_fd, PWM_BASE);

    close(mem_fd);

    if (gpio_map == MAP_FAILED) {
        perror("Failed to mmap GPIO");
        exit(-1);
    }

    if (pwm_map == MAP_FAILED) {
        perror("Failed to mmap PWM");
        exit(-1);
    }

    volatile uint32_t *gpio = (volatile uint32_t *) gpio_map;
    volatile uint32_t *pwm = (volatile uint32_t *) pwm_map;

    // Configure PWM clock
    *(pwm + PWMCLK_CNTL) = 0x5A000006;   // Set password and disable clock
    while (*(pwm + PWMCLK_CNTL) & 0x80) {}  // Wait for clock to be disabled
    *(pwm + PWMCLK_DIV) = 0x5A000000 | (uint32_t)(500000000/PWM_FREQUENCY);  // Set password and set divisor
    *(pwm + PWMCLK_CNTL) = 0x5A000016;   // Set password and enable clock
    while (*(pwm + PWMCLK_CNTL) & 0x80) {}  // Wait for clock to be enabled

    // Configure PWM pin as ALT5
    int gpio_pin = GPIO_PIN;
    int gpio_pin_offset = gpio_pin / 10;
    int gpio_pin_shift = (gpio_pin % 10) * 3;

    *(gpio + gpio_pin_offset) &= ~(0x7 << gpio_pin_shift);   // Clear function bits
    *(gpio + gpio_pin_offset) |= (0x2 << gpio_pin_shift);    // Set function bits to ALT5

    // Configure PWM
    *(pwm + PWM_CTL) = 0;               // Disable PWM
    *(pwm + PWM_RNG1) = PWM_RANGE;      // Set PWM range
    *(pwm + PWM_DAT1) = PWM_RANGE;      // Set PWM duty cycle to max range

    // Enable PWM
    *(pwm + PWM_CTL) |= (1 << 7);       // Use PWM1
    *(pwm + PWM_CTL) |= (1 << 0);       // Enable PWM

    // Disable PWM
    *(pwm + PWM_CTL) &= ~(1 << 0);

    // Unmap memory
    munmap(gpio_map, BLOCK_SIZE);
    munmap(pwm_map, BLOCK_SIZE);

    return 0;
}
int pmwleftoff() {
    // Map the GPIO and PWM controllers to memory
    int mem_fd = open("/dev/mem", O_RDWR | O_SYNC);
    if (mem_fd < 0) {
        perror("Failed to open /dev/mem");
        exit(-1);
    }

    void *gpio_map = mmap(NULL, BLOCK_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, mem_fd, GPIO_BASE);
    void *pwm_map = mmap(NULL, BLOCK_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, mem_fd, PWM_BASE);

    close(mem_fd);

    if (gpio_map == MAP_FAILED) {
        perror("Failed to mmap GPIO");
        exit(-1);
    }

    if (pwm_map == MAP_FAILED) {
        perror("Failed to mmap PWM");
        exit(-1);
    }

    volatile uint32_t *gpio = (volatile uint32_t *) gpio_map;
    volatile uint32_t *pwm = (volatile uint32_t *) pwm_map;

    // Configure PWM clock
    *(pwm + PWMCLK_CNTL) = 0x5A000006;   // Set password and disable clock
    while (*(pwm + PWMCLK_CNTL) & 0x80) {}  // Wait for clock to be disabled
    *(pwm + PWMCLK_DIV) = 0x5A000000 | (uint32_t)(500000000/PWM_FREQUENCY);  // Set password and set divisor
    *(pwm + PWMCLK_CNTL) = 0x5A000016;   // Set password and enable clock
    while (*(pwm + PWMCLK_CNTL) & 0x80) {}  // Wait for clock to be enabled

    // Configure PWM pin as ALT5
    int gpio_pin = GPIO_PIN;
    int gpio_pin_offset = gpio_pin / 10;
    int gpio_pin_shift = (gpio_pin % 10) * 3;

    *(gpio + gpio_pin_offset) &= ~(0x7 << gpio_pin_shift);   // Clear function bits
    *(gpio + gpio_pin_offset) |= (0x2 << gpio_pin_shift);    // Set function bits to ALT5

    // Disable PWM
    *(pwm + PWM_CTL) &= ~(1 << 0);

    // Unmap memory
    munmap(gpio_map, BLOCK_SIZE);
    munmap(pwm_map, BLOCK_SIZE);

    return 0;
}
