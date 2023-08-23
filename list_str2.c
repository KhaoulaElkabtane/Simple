#include "shell.h"

/**
 * l_length - determines lenght
 * @head: first node
 * Return: size of list
 */
size_t l_length(const list_t *head)
{
	size_t i = 0;

	while (head)
	{
		head = head->next;
		i++;
	}
	return (i);
}

/**
 * list_string - array of string the list->str
 * @head: first node
 * Return: array of string
 */
char **list_string(list_t *head)
{
	list_t *node = head;
	size_t i = l_length(head), j;
	char **strs;
	char *str;

	if (!head || !i)
		return (NULL);
	strs = malloc(sizeof(char *) * (i + 1));
	if (!strs)
		return (NULL);
	for (i = 0; node; node = node->next, i++)
	{
		str = malloc(_strlength(node->str) + 1);
		if (!str)
		{
			for (j = 0; j < i; j++)
				free(strs[j]);
			free(strs);
			return (NULL);
		}
		str = _strcopy(str, node->str);
		strs[i] = str;
	}
	strs[i] = NULL;
	return (strs);
}

/**
 * _list - prints elements of a list_t linked list
 * @head: first node
 * Return: size of list
 */
size_t _list(const list_t *head)
{
	size_t i = 0;

	while (head)
	{
		_strputs(str_convertion(head->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_strputs(head->str ? head->str : "(nil)");
		_strputs("\n");
		head = head->next;
		i++;
	}
	return (i);
}
/**
 * _nstart - node whose string start with prefix
 * @head: list head
 * @pr: string
 * @str: character after prefix
 * Return: node or null
 */
list_t *_nstart(list_t *head, char *pr, char str)
{
	char *a = NULL;

	while (head)
	{
		a = startWith(head->str, pr);
		if (a && ((str == -1) || (*a == str)))
			return (head);
		head = head->next;
	}
	return (NULL);
}

/**
 * gnode - gets the index a node
 * @hd: the head of list
 * @nd: node
 * Return: index node or -1
 */
size_t gnode(list_t *hd, list_t *nd)
{
	size_t i = 0;

	while (hd)
	{
		if (hd == nd)
			return (i);
		hd = hd->next;
		i++;
	}
	return (-1);
}
