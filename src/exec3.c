/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwalchsh <der.grex@student42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 14:13:13 by gwalchsh          #+#    #+#             */
/*   Updated: 2024/03/16 14:13:16 by gwalchsh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int	is_dir(char *path)
{
	struct stat	s;

	if (stat(path, &s) == 0)
		if (s.st_mode & S_IFDIR)
			return (1);
	return (0);
}

static int	path_precheck2(t_msd *data, char *bin)
{
	if (bin[0] == '.' && bin[1] == '/')
	{
		if (is_dir(bin + 2))
			return (execancel(data, 126, bin,
					"Is a directory"), -1);
		errno = 0;
		access(bin + 2, F_OK);
		if (errno == ENOENT)
			return (execancel(data, 127, bin,
					"No such file or directory"), -1);
		access(bin + 2, X_OK);
		if (errno == EACCES)
			return (execancel(data, 126, bin,
					"Permission denied"), -1);
		if (!access(bin + 2, X_OK))
			return (0);
	}
	if (is_dir(bin))
		return (execancel(data, 127, bin,
				"command not found"), -1);
	return (1);
}

static int	path_precheck(t_msd *data, char *bin)
{
	if (bin[0] == '/')
	{
		if (is_dir(bin))
			return (execancel(data, 126, bin,
					"Is a directory"), -1);
		else if (!access(bin, X_OK))
			return (0);
		return (execancel(data, 127, bin,
				"No such file or directory"), -1);
	}
	return (path_precheck2(data, bin));
}

char	*get_binary_path(t_msd *data, char *bin, int i)
{
	char		*res;

	res = NULL;
	if (path_precheck(data, bin) < 1)
		return (bin);
	errno = 0;
	if (!access(bin, X_OK) && errno == 0)
		return (bin);
	if (!data->path)
		return (execancel(data, 127, bin,
				"No such file or directory"), bin);
	while (data->path[++i] && bin && ft_strlen(bin) > 0)
	{
		if (res)
			(free(res), res = NULL);
		res = ft_strjoin(data->path[i], "/");
		protecc(!res, data, 2);
		res = ft_strjoin_free(res, bin);
		protecc(!res, data, 2);
		if (res)
			if (!access(res, X_OK))
				return (free(bin), res);
	}
	return (execancel(data, 127, bin, "command not found"),
		free(res), bin);
}

void	closeline(t_msd *data)
{
	if (!data->cmds->next && data->red_out == -1)
		data->fd_out = dup(1);
	if (data->red_in != -1 && data->cmds->bin)
	{
		close_if(data->fd_in);
		data->fd_in = data->red_in;
	}
	if (data->red_out != -1)
		data->fd_out = data->red_out;
	dup2(data->fd_in, 0);
	close_if(data->fd_in);
}
