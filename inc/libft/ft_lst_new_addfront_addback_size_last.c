/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_new_addfront_addback_size_last.c            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwalchsh <der.grex@student42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 12:04:29 by gwalchsh          #+#    #+#             */
/*   Updated: 2023/10/28 12:04:34 by gwalchsh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_lst	*ft_lstnew(void *content)
/*DESCRIPTION: Allocates (with malloc(3)) and returns a new node.
The member variable ’content’ is initialized with the value of the parameter
’content’. The variable ’next’ is initialized to NULL.
RETURN VALUE: The new node.*/
{
	t_lst	*node;

	node = malloc(sizeof(t_lst));
	if (!(node))
		return (NULL);
	node->content = content;
	node->next = NULL;
	return (node);
}
/*
#include <stdio.h>
int main(void)
{
	int i = 42;
	t_lst *new = ft_lstnew(&i);
	printf("%i\n", *(int *)new->content);
}*/

void	ft_lstadd_front(t_lst **lst, t_lst *new)
//DESCRIPTION: Adds the node ’new’ at the beginning of the list.
{
	new->next = *lst;
	*lst = new;
}
/*
#include <stdio.h>
int main(void)
{
	int i = 42;
	int j = 24;
	t_lst *new = ft_lstnew(&i);
	t_lst *newer = ft_lstnew(&j);
	ft_lstadd_front(&new, newer);
	printf("%i\n", *(int *)newer->content);
	printf("%i\n", *(int *)newer->next->content);
}*/

void	ft_lstadd_back(t_lst **lst, t_lst *new)
//DESCRIPTION: Adds the node ’new’ at the end of the list.
{
	t_lst	*temp;

	if (!*lst)
		*lst = new;
	else
	{
		temp = *lst;
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new;
	}
}
/*
#include <stdio.h>
#include <string.h>
int main(void)
{
	t_lst *l = ((void*)0);
 	t_lst *n = ft_lstnew(strdup("OK"));
 
 	ft_lstadd_back(&l, n);
 	if (l == n && !strcmp(l->content, "OK"))
 	{
 		free(l->next);
 		free(l);
 		printf("TEST_SUCCESS\n");
 		return 0;
 	}
 	free(l->next);
 	free(l);
 	printf("(TEST_FAILED\n");


	int i = 1;
	int j = 2;
	t_lst *new = ft_lstnew(&i);
	t_lst *newer = ft_lstnew(&j);
	ft_lstadd_back(&new, newer);
	printf("%i\n", *(int *)new->content);
	printf("%i\n", *(int *)new->next->content);
}*/

int	ft_lstsize(t_lst *lst)
/*DESCRIPTION: Counts the number of nodes in a list.
RETURN VALUE: The length of the list*/
{
	int		i;
	t_lst	*temp;

	i = 0;
	temp = lst;
	while (temp != NULL)
	{
		temp = temp->next;
		i++;
	}
	return (i);
}
/*
#include <stdio.h>
int main(void)
{
	int i = 1;
	int j = 2;
	t_lst *new = ft_lstnew(&i);
	t_lst *newer = ft_lstnew(&j);
	ft_lstadd_back(&new, newer);
	printf("%i\n", ft_lstsize(new));
}*/

t_lst	*ft_lstlast(t_lst *lst)
/*DESCRIPTION: Returns the last node of the list.
RETURN VALUE: Last node of the list*/
{
	t_lst	*temp;

	temp = lst;
	if (temp == NULL)
		return (NULL);
	while (temp->next != NULL)
		temp = temp->next;
	return (temp);
}
/*
#include <stdio.h>
int main(void)
{
	int i = 1;
	int j = 2;
	t_lst *new = ft_lstnew(&i);
	t_lst *newer = ft_lstnew(&j);
	ft_lstadd_back(&new, newer);
	t_lst *last = ft_lstlast(new);
	printf("%i\n", *(int *)last->content);
}*/
