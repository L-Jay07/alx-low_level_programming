#include <stddef.h>
#include <stdlib.h>
#include "lists.h"

/**
 * pop_listint - Deletes the head node of a listint_t list.
 * @head: Pointer to a pointer to the head of the list.
 * Return: Value of the data in the deleted node, or 0 if list is empty.
 */
int pop_listint(listint_t **head)
{
int data = 0;
listint_t *temp;

if (head != NULL && *head != NULL)
{
temp = *head;
data = temp->n;
*head = (*head)->next;
free(temp);
}
return (data);
}
