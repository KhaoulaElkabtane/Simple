#include "shell.h"

/**
 * _node - adds a node to the start
 * @add: address pointer
 * @str: string filed of node
 * @n: node index
 * Return: size of list
 */
list_t *_node(list_t **add, const char *str, int n)
{
	list_t *head;

	if (!add)
		return (NULL);
	head = malloc(sizeof(list_t));
	if (!head)
		return (NULL);
	_memoryfle((void *)head, 0, sizeof(list_t));
	head->num = n;
	if (str)
	{
		head->str = _strduplication(str);
		if (!head->str)
		{
			free(head);
			return (NULL);
		}
	}
	head->next = *add;
	*add = head;
	return (head);
}

/**
 * _nend - adds a node to the end of the list
 * @add: address pointer
 * @str: string filed of node
 * @n: node index
 * Return: size of list
 */
list_t *_nend(list_t **add, const char *str, int n)
{
	list_t *node1, *node2;

	if (!add)
		return (NULL);
	node2 = *add;
	node1 = malloc(sizeof(list_t));
	if (!node1)
		return (NULL);
	_memoryfle((void *)node1, 0, sizeof(list_t));
	node1->num = n;
	if (str)
	{
		node1->str = _strduplication(str);
		if (!node1->str)
		{
			free(node1);
			return (NULL);
		}
	}
	if (node2)
	{
		while (node2->next)
			node2 = node2->next;
		node2->next = node1;
	}
	else
		*add = node1;
	return (node1);
}

/**
 * list_str - prints only the string element
 * @tr: pointer first node
 * Return: size of list
 */
size_t list_str(const list_t *tr)
{
	size_t i = 0;

	while (tr)
	{
		_strputs(tr->str ? tr->str : "(nil)");
		_strputs("\n");
		tr = tr->next;
		i++;
	}
	return (i);
}

/**
 * node_index - deletes node at given ingex
 * @hd: address pointer first node
 * @dex: index of node to delete
 * Return: 1 if true, 0 if false
 */
int node_index(list_t **hd, unsigned int dex)
{
	list_t *n, *n1;
	unsigned int i;

	if (!hd || !*hd)
		return (0);
	if (!dex)
	{
		n = *hd;
		*hd = (*hd)->next;
		free(n->str);
		free(n);
		return (1);
	}
	n = *hd;
	while (n)
	{
		if (i == dex)
		{
			n1->next = n->next;
			free(n->str);
			free(n);
			return (1);
		}
		i++;
		n1 = n;
		n = n->next;
	}
	return (0);
}

/**
 * l_free - frees all list of nodes
 * @head: address pointer
 * Return: nothing
 */
void l_free(list_t **head)
{
	list_t *node, *nnode, *hd;

	if (!head || !*head)
		return;
	hd = *head;
	node = hd;
	while (node)
	{
		nnode = node->next;
		free(node->str);
		free(node);
		node = nnode;
	}
	*head = NULL;
}

