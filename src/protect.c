/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   protect.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cthaler <cthaler@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 09:54:35 by cthaler           #+#    #+#             */
/*   Updated: 2024/04/03 09:54:37 by cthaler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	clear_round3(t_msd *data)
{
	close_if(data->fd_here);
	close_if(data->fd_in);
	close_if(data->fd_out);
	close_if(data->red_out);
	close_if(data->red_in);
	data->fd_here = -1;
	data->fd_in = -1;
	data->fd_out = -1;
	data->red_out = -1;
	data->red_in = -1;
	data->iter = 0;
	data->nr_cmds = 0;
	g_sig = DEFAULT;
}

static void	clear_round2(t_msd *data)
{
	data->path = NULL;
	data->redir_head = NULL;
	data->cmds = NULL;
	data->cmds_head = NULL;
	data->arg_list = NULL;
	free_if(data->line);
	free_if(data->line_history);
	if (data->pids)
		free(data->pids);
	data->pids = NULL;
	data->line = NULL;
	data->line_history = NULL;
	clear_round3(data);
}

void	clear_round(t_msd *data)
{
	if (ft_strlen(data->line_history))
		add_history(data->line_history);
	if (data->cmds_head)
		free_cmds(&data->cmds_head);
	if (data->arg_list)
		free_list(&data->arg_list);
	if (data->redir_head)
		free_redirs(data);
	if (data->path)
		liberate_strarray(data->path);
	clear_round2(data);
}

void	protecc_child(int res, t_msd *data, int err)
{
	if (!res)
		return ;
	if (data)
	{
		if (data->def_in != -1)
			close(data->def_in);
		if (data->def_out != -1)
			close(data->def_out);
		clear_round(data);
		if (data->hist)
			liberate_strarray(data->hist);
		if (data->envp)
			liberate_strarray(data->envp);
		free(data->heredoc);
	}
	exit(err);
}

void	protecc(int res, t_msd *data, int err)
{
	if (!res)
		return ;
	if (data)
	{
		if (data->def_in != -1)
			close(data->def_in);
		if (data->def_out != -1)
			close(data->def_out);
		clear_round(data);
		if (data->hist)
			liberate_strarray(data->hist);
		if (data->envp)
			liberate_strarray(data->envp);
		if (data->heredoc)
			if (!access(data->heredoc, F_OK))
				unlink(data->heredoc);
		free(data->heredoc);
	}
	exit(err);
}
