/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cthaler <cthaler@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 10:55:15 by cthaler           #+#    #+#             */
/*   Updated: 2023/11/01 10:55:16 by cthaler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	free_redirs(t_msd *data)
{
	while (data->redir_i > 0)
	{
		data->redir_i--;
		free_if(data->redir_head[data->redir_i]->s);
		free(data->redir_head[data->redir_i]);
	}
	free(data->redir_head);
	data->redir_head = NULL;
	data->redir_i = 0;
}

void	ft_strlst_back(t_list **lst, t_list *node)
{
	t_list	*cur;

	if (!*lst)
	{
		*lst = node;
		lst[0]->next = NULL;
	}
	else
	{
		cur = *lst;
		while (cur->next)
			cur = cur->next;
		cur->next = node;
	}
}

t_list	*ft_strlstnew(char *content)
{
	t_list	*lst;

	lst = malloc(sizeof(t_list));
	if (!lst)
		return (NULL);
	lst->s = content;
	lst->next = NULL;
	return (lst);
}

void	free_cmds(t_cmd **a)
{
	t_cmd	*temp;

	if (*a)
	{
		temp = *a;
		while (temp->next)
		{
			*a = temp->next;
			if (temp->bin)
				free_arr(temp->bin, arr_len(temp->bin) - 1);
			free(temp);
			temp = *a;
		}
		if (temp->bin)
			free_arr(temp->bin, arr_len(temp->bin) - 1);
		free(temp);
	}
}

void	free_list(t_list **a)
{
	t_list	*temp;

	if (*a)
	{
		temp = *a;
		while (temp->next)
		{
			*a = temp->next;
			free(temp->s);
			free(temp);
			temp = *a;
		}
		free(temp->s);
		free(temp);
	}
}
