/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cthaler <cthaler@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 11:53:31 by cthaler           #+#    #+#             */
/*   Updated: 2024/01/21 11:53:32 by cthaler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	execancel(t_msd *data, int code, char *trigger, char *msg)
{
	ft_putstr_fd("🧙: ", 2);
	ft_putstr_fd(trigger, 2);
	ft_putstr_fd (": ", 2);
	ft_putendl_fd(msg, 2);
	data->exit_code = code;
	data->execute = 0;
}

int	close_if(int fd)
{
	int	ret;

	ret = 0;
	if (fd != -1)
		ret = close(fd);
	return (ret);
}

void	free_if(char *s)
{
	if (s)
		free(s);
}

void	free_arr(char **arr, int i)
{
	while (i >= 0)
		free(arr[i--]);
	free(arr);
}

int	arr_len(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		i++;
	return (i);
}
