/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_table.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cthaler <cthaler@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 15:21:56 by cthaler           #+#    #+#             */
/*   Updated: 2024/01/22 15:21:57 by cthaler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static t_cmd	*new_cmd(char **bin, int index, int token, t_list *redir)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (liberate_strarray(bin), free_list(&redir), NULL);
	cmd->index = index;
	cmd->token = token;
	cmd->bin = bin;
	cmd->pid = -1;
	cmd->redir = redir;
	cmd->next = NULL;
	return (cmd);
}

static void	add_cmd_back(t_cmd **cmds, t_cmd *node)
{
	t_cmd	*cur;

	if (!*cmds)
	{
		*cmds = node;
		cmds[0]->next = NULL;
	}
	else
	{
		cur = *cmds;
		while (cur->next)
			cur = cur->next;
		cur->next = node;
	}
}

static int	count_args(t_list *lst)
{
	int	strs;

	strs = 0;
	while (lst)
	{
		if (lst->token == PIPE)
			break ;
		if (lst->token == CMD || lst->token == CMD2 || lst->token == ARG)
			strs++;
		lst = lst->next;
	}
	return (strs);
}

static char	**get_args(t_list *lst)
{
	char	**bin;
	int		i;
	int		len;

	i = 0;
	len = count_args(lst);
	if (!len)
		return (NULL);
	bin = malloc(sizeof(bin) * (len + 1));
	if (!bin)
		return (NULL);
	while (lst && lst->token != PIPE)
	{
		if (lst->token == CMD || lst->token == CMD2 || lst->token == ARG)
		{
			bin[i] = ft_strdup(lst->s);
			if (!bin[i])
				return (free_arr(bin, i - 1), NULL);
			i++;
		}
		lst = lst->next;
	}
	bin[i] = NULL;
	return (bin);
}

int	cmd_table(t_list *lst, t_cmd **cmds, t_msd *data, int index)
{
	t_cmd	*cmd;
	t_list	*redir;
	char	**bin;

	protecc(!alloc_redir_head(data), data, 1);
	while (lst)
	{
		bin = get_args(lst);
		redir = get_redir(lst, data);
		if (count_args(lst) && !bin)
			return (0);
		if (count_redirs(lst, 1) && !redir)
			return (liberate_strarray(bin), 0);
		cmd = new_cmd(bin, index, lst->token, redir);
		if (!cmd)
			return (0);
		add_cmd_back(cmds, cmd);
		data->nr_cmds++;
		while (lst && lst->token != PIPE)
			lst = lst->next;
		if (lst)
			lst = lst->next;
		index++;
	}
	return (1);
}
