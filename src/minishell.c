/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cthaler <cthaler@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 12:04:08 by cthaler           #+#    #+#             */
/*   Updated: 2024/01/02 12:04:10 by cthaler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	g_sig = DEFAULT;

static int	main_loop2(t_msd *data)
{
	if (!data->line[0])
	{
		clear_round(data);
		return (0);
	}
	protecc(!parse_hell(data), data, 1);
	protecc(!lex_it(data->line, data, 1), data, 1);
	protecc(!tokenize(&data->arg_list), data, 1);
	if (!check_syntax(data, 0, 1))
	{
		clear_round(data);
		return (0);
	}
	protecc(!cmd_table(data->arg_list, &data->cmds, data, 0), data, 1);
	data->cmds_head = data->cmds;
	return (1);
}

void	main_loop(t_msd *data)
{
	while (data->quit == 0)
	{
		signal(SIGINT, ctrl_c);
		data->line = readline(data->prompt);
		if (g_sig == SIGINT)
			data->exit_code = 130;
		if (!data->line)
			ft_exit(data, NULL);
		signal(SIGINT, SIG_IGN);
		if (!main_loop2(data))
			continue ;
		executor(data);
		clear_round(data);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_msd	data;

	(void)argc;
	(void)argv;
	if (!envp)
		return (1);
	init_data(&data, envp);
	signal(SIGQUIT, SIG_IGN);
	main_loop(&data);
	protecc(1, &data, data.exit_code);
	return (data.exit_code);
}
