/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec4.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cthaler <cthaler@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 10:34:20 by cthaler           #+#    #+#             */
/*   Updated: 2024/04/03 10:34:22 by cthaler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	init_pids(t_msd *data)
{
	int	i;

	i = 0;
	while (i <= data->nr_cmds)
		data->pids[i++] = -2;
}

void	loop_child(t_msd *data)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (data->pids[i] != -2)
	{
		waitpid(data->pids[i], &data->status, 0);
		data->exit_code = WEXITSTATUS(data->status);
		if (WIFSIGNALED(data->status))
			data->exit_code = 130;
		if (WCOREDUMP(data->status) == 128 && !count)
		{
			data->exit_code = 131;
			ft_putstr_fd("Quit (core dumped)", 2);
			count++;
		}
		if (data->pids[i] == -2 && WIFSIGNALED(data->status))
			ft_putchar_fd('\n', 1);
		i++;
	}
}
