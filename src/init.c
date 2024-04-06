/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cthaler <cthaler@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 16:28:29 by gwalchsh          #+#    #+#             */
/*   Updated: 2024/02/09 15:57:55 by cthaler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	**init_env_arr(char **envp, char *s)
{
	char	**env;
	int		i;

	i = arr_len (envp);
	if (s)
		i++;
	env = malloc(sizeof(env) * (i + 1));
	if (!env)
		return (NULL);
	i = 0;
	while (envp[i])
	{
		env[i] = ft_strdup(envp[i]);
		if (!env[i])
			return (free_arr(env, i - 1), NULL);
		i++;
	}
	if (s)
		env[i++] = s;
	env[i] = 0;
	return (env);
}

static void	get_shlvl(t_msd *data)
{
	char	*lvl;
	int		ret;

	lvl = get_env_value(data->envp, "SHLVL");
	protecc(!lvl, data, 1);
	data->shlvl = ft_atoi(lvl) + 1;
	if (data->shlvl > 999)
	{
		ft_putendl_fd("🧙: warning: shell level (1000) too high, \
		resetting to 1", 2);
		data->shlvl = 1;
	}
	lvl = ft_itoa(data->shlvl);
	protecc(!lvl, data, 1);
	ret = set_env_value(data->envp, "SHLVL", lvl);
	free(lvl);
	protecc(!ret, data, 1);
}

void	get_path(t_msd *data, char **envp)
{
	int	i;

	i = -1;
	while (envp[++i])
	{
		if (!ft_strncmp(envp[i], "PATH=", 5))
		{
			if (ft_strchr(envp[i], '/'))
			{
				data->path = ft_split(ft_strchr(envp[i],
							'/'), ':');
				protecc(data->path == NULL, data, 1);
			}
			break ;
		}
	}
}

static void	init_data2(t_msd *data)
{
	data->pipe_fd[0] = -1;
	data->pipe_fd[1] = -1;
	data->def_in = dup(STDIN_FILENO);
	data->def_out = dup(STDOUT_FILENO);
	data->fd_here = -1;
	data->red_in = -1;
	data->red_out = -1;
	data->fd_in = -1;
	data->fd_out = -1;
	data->exit_code = 0;
	data->redir_i = 0;
	data->execute = 1;
	data->quit = 0;
	data->nr_cmds = 0;
	data->iter = 0;
}

void	init_data(t_msd *data, char **envp)
{
	data->redir_head = NULL;
	data->cmds = NULL;
	data->cmds_head = NULL;
	data->path = NULL;
	data->hist = NULL;
	data->envp = NULL;
	data->arg_list = NULL;
	data->line_history = NULL;
	data->heredoc = NULL;
	data->line = NULL;
	data->pids = NULL;
	init_data2(data);
	ft_strlcpy(data->prompt, "minishell> ", 12);
	data->heredoc = heredoc_filename();
	protecc(!data->heredoc, data, 1);
	data->envp = init_env_arr(envp, NULL);
	protecc(!data->envp, data, 1);
	get_shlvl(data);
}
