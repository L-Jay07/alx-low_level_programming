#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "lists.h"

list_t *add_node_end(list_t **head, const char *str)
{
list_t *new_node;
char *str_dup;
list_t *current;

if (head == NULL || str == NULL)
return (NULL);

new_node = malloc(sizeof(list_t));
if (new_node == NULL)
return (NULL);

str_dup = strdup(str);
if (str_dup == NULL)
{
free(new_node);
return (NULL);
}

current = *head;

new_node->str = str_dup;
new_node->len = strlen(str_dup);
new_node->next = NULL;

if (*head == NULL)
{
*head = new_node;
}
else
{
while (current->next != NULL)
{
current = current->next;
}
current->next = new_node;
}

return (new_node);
}

