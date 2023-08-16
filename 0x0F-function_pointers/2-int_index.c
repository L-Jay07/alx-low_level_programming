#include "function_pointers.h"

/**
 * int_index - searches for an integer in an array
 * @array: pointer to array
 * @size: number of elements in the array
 * @cmp: pointer to the comparison function
 *
 * Return: -1 if not found or an error occurs.
 */
int int_index(int *array, int size, int (*cmp)(int))
{
if (array != NULL && cmp != NULL && size > 0)
{
int i;
for (i = 0; i < size; i++)
{
if (cmp(array[i]) != 0)
{
return (i);
}
}
}
return (-1);
}
