/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwalchsh <der.grex@student42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 12:39:16 by gwalchsh          #+#    #+#             */
/*   Updated: 2024/02/10 12:39:17 by gwalchsh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	unset_var(t_msd *data, char *arg)
{
	int	i;
	int	len;

	i = -1;
	len = ft_strlen(arg);
	while (data->envp[++i])
	{
		if (!(ft_strncmp(data->envp[i], arg, len))
			&& (data->envp[i][len] == '='
			|| !data->envp[i][len]))
		{
			free(data->envp[i]);
			while (data->envp[i + 1])
			{
				data->envp[i] = data->envp[i + 1];
				i++;
			}
			data->envp[i] = 0;
		}
	}
}

void	unset(t_msd *data)
{
	int	i;

	i = 1;
	while (data->cmds->bin[i])
	{
		unset_var(data, data->cmds->bin[i]);
		i++;
	}
	data->exit_code = 0;
}
