/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_table2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cthaler <cthaler@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 11:03:57 by cthaler           #+#    #+#             */
/*   Updated: 2024/03/07 11:04:00 by cthaler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	is_redir(int token)
{
	if (token == IN || token == OUT || token == APPEND || token == HEREDOC)
		return (1);
	return (0);
}

int	count_redirs(t_list *lst, int flag)
{
	int	strs;

	strs = 0;
	while (lst)
	{
		if (lst->token == PIPE && flag)
			break ;
		if (is_redir(lst->token))
			strs++;
		lst = lst->next;
	}
	return (strs);
}

static int	not_simply_quote(char *s)
{
	int	i;
	int	sq;
	int	dq;

	i = 0;
	sq = 0;
	dq = 0;
	while (s[i])
	{
		if (s[i] == '\'')
			sq++;
		else if (s[i] == '"')
			dq++;
		if (dq >= 2 || sq >= 2)
			return (1);
		i++;
	}
	return (0);
}

static int	here_keyword(t_list *redir)
{
	if (redir->token == HEREDOC)
		if (not_simply_quote(redir->s))
			redir->token = HEREDOC_Q;
	redir->s = remove_quotes(redir->s);
	if (!redir->s)
		return (0);
	return (1);
}

t_list	*get_redir(t_list *lst, t_msd *data)
{
	t_list	*redir;
	t_list	*new;
	char	*file;

	redir = NULL;
	while (lst && lst->token != PIPE)
	{
		if (is_redir(lst->token))
		{
			file = ft_strdup(lst->next->s);
			if (!file)
				return (free_list(&redir), NULL);
			new = ft_strlstnew(file);
			if (!new)
				return (free_list(&redir), NULL);
			new->token = lst->token;
			data->redir_head[data->redir_i++] = new;
			if (!here_keyword(new))
				return (free_list(&redir), NULL);
			ft_strlst_back(&redir, new);
		}
		lst = lst->next;
	}
	return (redir);
}
