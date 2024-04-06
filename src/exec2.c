/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwalchsh <der.grex@student42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 16:46:51 by gwalchsh          #+#    #+#             */
/*   Updated: 2024/03/07 16:46:53 by gwalchsh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	chexec2(t_msd *data)
{
	signal(SIGPIPE, SIG_IGN);
	if (!data->cmds->bin || !data->execute)
		;
	else if (!ft_strncmp(data->cmds->bin[0], "exit\0", 5))
		ft_exit(data, data->cmds->bin);
	else if (!ft_strncmp(data->cmds->bin[0], "echo\0", 5))
		data->exit_code = echo(data->cmds->bin);
	else if (!ft_strncmp(data->cmds->bin[0], "cd\0", 3))
		cd(data);
	else if (!ft_strncmp(data->cmds->bin[0], "export\0", 7))
		export(data, data->cmds->bin);
	else if (!ft_strncmp(data->cmds->bin[0], "unset\0", 6))
		unset(data);
	else if (!ft_strncmp(data->cmds->bin[0], "pwd\0", 4))
		data->exit_code = pwd();
	else if (!ft_strncmp(data->cmds->bin[0], "env\0", 4))
		data->exit_code = env(data->envp);
	protecc_child(1, data, data->exit_code);
}

void	change_signals(int flag)
{
	if (flag == 1)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
	}
	else if (flag == 2)
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
	}
}

void	child_process(t_msd *data)
{
	change_signals(1);
	close_if(data->def_in);
	close_if(data->def_out);
	close_if(data->pipe_fd[0]);
	if (data->cmds->token == CMD)
		chexec2(data);
	else
	{
		signal(SIGPIPE, SIG_DFL);
		execve(data->cmds->bin[0], data->cmds->bin, data->envp);
		protecc(1, data, errno);
	}
}

void	launch_executable(t_msd *data)
{
	if (data->cmds->token != CMD)
		data->cmds->bin[0] = get_binary_path(data, data->cmds->bin[0], -1);
	if (data->execute)
	{
		data->cmds->pid = fork();
		data->pids[data->iter++] = data->cmds->pid;
		if (data->cmds->pid == -1)
			protecc(1, data, 10);
		else if (data->cmds->pid == 0)
			child_process(data);
		else
			change_signals(2);
	}
}
