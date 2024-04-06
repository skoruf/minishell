/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwalchsh <der.grex@student42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 13:17:23 by gwalchsh          #+#    #+#             */
/*   Updated: 2024/02/08 13:17:46 by gwalchsh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	chexec(t_msd *data)
{
	if (!data->cmds->bin || !data->execute)
		;
	else if (!ft_strncmp(data->cmds->bin[0], "exit\0", 5) && !data->cmds->next)
		ft_exit(data, data->cmds->bin);
	else if (!ft_strncmp(data->cmds->bin[0], "echo\0", 5) && !data->cmds->next)
		data->exit_code = echo(data->cmds->bin);
	else if (!ft_strncmp(data->cmds->bin[0], "cd\0", 3) && !data->cmds->next)
		cd(data);
	else if (!ft_strncmp(data->cmds->bin[0], "export\0", 7)
		&& !data->cmds->next)
		export(data, data->cmds->bin);
	else if (!ft_strncmp(data->cmds->bin[0], "unset\0", 6) && !data->cmds->next)
		unset(data);
	else if (!ft_strncmp(data->cmds->bin[0], "pwd\0", 4) && !data->cmds->next)
		data->exit_code = pwd();
	else if (!ft_strncmp(data->cmds->bin[0], "env\0", 4))
		data->exit_code = env(data->envp);
	else if (data->execute)
		launch_executable(data);
}

void	make_here(t_msd *data)
{
	t_cmd *cmds = data->cmds;
	t_list *redir;

	while (cmds)
	{
		redir = cmds->redir;
		while (redir)
		{
			if (redir->token == HEREDOC || redir->token == HEREDOC_Q)
				here_and_now(data, redir);
			redir = redir->next;
		}
		cmds = cmds->next;
	}
}

static void	executor2(t_msd *data)
{
	closeline(data);
	if (data->cmds->next)
	{
		pipe(data->pipe_fd);
		data->fd_in = data->pipe_fd[0];
		if (data->red_out != -1 && data->cmds->bin)
			close(data->pipe_fd[1]);
		else
			data->fd_out = data->pipe_fd[1];
	}
	dup2(data->fd_out, 1);
	close(data->fd_out);
	chexec(data);
	data->cmds->redir = NULL;
	close_if(data->red_out);
	close_if(data->red_in);
	data->red_out = -1;
	data->red_in = -1;
}

void	executor(t_msd *data)
{
	data->pids = malloc(sizeof(int *) * (data->nr_cmds + 1));
	protecc(!data->pids, data, 1);
	init_pids(data);
	get_path(data, data->envp);
	data->fd_in = dup(0);
	make_here(data);
	while (data->cmds)
	{
		data->execute = 1;
		redirect(data, data->cmds->redir);
		if (g_sig == SIGINT)
		{
			g_sig = DEFAULT;
			break ;
		}
		executor2(data);
		data->cmds = data->cmds->next;
		dup2(data->def_in, 0);
		dup2(data->def_out, 1);
	}
	if (data->nr_cmds)
		loop_child(data);
	protecc(data->quit, data, data->exit_code);
}
