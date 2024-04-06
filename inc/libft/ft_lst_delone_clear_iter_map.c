/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_delone_clear_iter_map.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwalchsh <der.grex@student42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 12:08:46 by gwalchsh          #+#    #+#             */
/*   Updated: 2023/10/28 12:08:47 by gwalchsh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdelone(t_lst *lst, void (*del)(void*))
/*DESCRIPTION: Takes a node as a parameter and frees the memory of the node’s
content using the function ’del’ given as a parameter and frees the node. The
memory of ’next’ should not be freed.*/
{
	del(lst->content);
	free(lst);
}

void	ft_lstclear(t_lst **lst, void (*del)(void*))
/*DESCRIPTION: Deletes and frees the given node and every successor of that
node, using the function ’del’ and free(3). Finally, the pointer to the list
must be set to NULL.*/
{
	t_lst	*temp;

	if (lst && del)
	{
		while ((*lst))
		{
			temp = (*lst)->next;
			ft_lstdelone(*lst, del);
			(*lst) = temp;
		}
		*lst = NULL;
	}
}
/*
#include <stdio.h>
#include <string.h>

int main(void)
{
	t_lst *l = ft_lstnew(strdup("nyancat"));
 	t_lst *tmp;
 
 	l->next = ft_lstnew(strdup("#TEST#"));
 	tmp = l->next;
 	ft_lstclear(&l, free(l->content));
 	write(2, "", 1);
 	if (!l)
 	{
 		free(tmp);
 		printf("TEST_SUCCESS\n");
 	}
 	printf("TEST_FAILED\n");

}*/

void	ft_lstiter(t_lst *lst, void (*f)(void *))
/*DESCRIPTION: Iterates the list ’lst’ and applies the function ’f’ on the
content of each node.*/
{
	t_lst	*temp;

	temp = lst;
	while (temp != NULL)
	{
		f(temp->content);
		temp = temp->next;
	}
}
/*
#include <stdio.h>

void	increase_content(void *content)
{
	//content++;
	printf("%i\n", *(int *)content);
}

int main(void)
{
	int i = 1;
	int j = 2;
	t_lst *new = ft_lstnew(&i);
	t_lst *newer = ft_lstnew(&j);
	ft_lstadd_back(&new, newer);
	ft_lstiter(new, increase_content);
}*/

/*
#include <stdio.h>
void	*increase_content(void *content)
{
	++*(int *)content;
	return content;
}

void	print_content(void *content)
{
	printf("%i\n", *(int *)content);
}

void	delete(void *content)
{
	free(content);
}
*/
t_lst	*ft_lstmap(t_lst *lst, void *(*f)(void *), void (*del)(void *))
/*DESCRIPTION: Iterates the list ’lst’ and applies the function ’f’ on the
content of each node. Creates a new list resulting of the successive
applications of the function ’f’. The ’del’ function is used to delete the
content of a node, if needed.
RETURN VALUE: The new list. NULL if the allocation fails.*/
{
	t_lst	*tmp;
	t_lst	*hd;
	t_lst	*new;

	if (!lst || !del || !f)
		return (NULL);
	tmp = lst;
	hd = NULL;
	while (tmp != NULL)
	{
		new = ft_lstnew(NULL);
		if (!new)
			return (ft_lstclear(&hd, del), NULL);
		new->content = f(tmp->content);
		ft_lstadd_back(&hd, new);
		tmp = tmp->next;
	}
	return (hd);
}

/*
int main(void)
{
	int i = 1;
	int j = 2;
	t_lst *new = ft_lstnew(&i);
	t_lst *newer = ft_lstnew(&j);
	ft_lstadd_back(&new, newer);
	void *(*increase_content_ptr)(void *);
	increase_content_ptr = increase_content;
	void (*delete_ptr)(void *);
	delete_ptr = delete;
	void (*print_content_ptr)(void *);
	print_content_ptr = print_content;
	printf("original:\n");
	ft_lstiter(new, print_content_ptr);
	t_lst *inc = ft_lstmap(new, increase_content_ptr, delete_ptr);
	printf("increased:\n");
	ft_lstiter(inc, print_content_ptr);
}*/
