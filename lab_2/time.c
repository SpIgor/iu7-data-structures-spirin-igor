#include "time.h"

// Функция для замера времени
unsigned long long tick(void)
{
    uint32_t high, low;
    __asm__ __volatile__ (
    "rdtsc\n"
    "movl %%edx, %0\n"
    "movl %%eax, %1\n"
    : "=r" (high), "=r" (low)
    /* Output */
    :
    /* Input */
    : "%rax", "%rbx",
    "%rcx", "%rdx"
    /* Clobbered regs. */
    );
    return(((uint64_t)high << 32) | low);
}