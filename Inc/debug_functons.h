
#if !defined(DEBUG_FUNCTIONS_H)
#define DEBUG_FUNCTIONS_H

#include <stm32f410rx.h>
#include <stm32f4xx.h>

extern "C" int _write(int file, char *ptr, int len)
{
    /* Implement your write code here, this is used by puts and printf for example */
    int i = 0;
    for (i = 0; i < len; i++)
        ITM_SendChar((*ptr++));
    return len;
}

#endif // DEBUG_FUNCTIONS_H
