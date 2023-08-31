#include "main.h"

/**
 * get_endianness - Checks the endianness of the system.
 *
 * Return: 0 if big endian, 1 if little endian.
 */
int get_endianness(void)
{
unsigned int check = 1;
char *byte_ptr = (char *)&check;

return (*byte_ptr == 1);
}
