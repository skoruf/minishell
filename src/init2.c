/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cthaler <cthaler@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 14:34:42 by cthaler           #+#    #+#             */
/*   Updated: 2024/03/14 14:34:43 by cthaler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*heredoc_filename(void)
{
	char	rnd[1];
	char	filename[4096];
	int		rand_fd;
	int		i;

	i = 0;
	ft_strlcpy(filename, "/tmp/", 6);
	rand_fd = open("/dev/urandom", O_RDONLY);
	while (i < 8)
	{
		rnd[0] = '\0';
		read(rand_fd, rnd, 1);
		if (ft_isalnum(rnd[0]))
		{
			filename[i + 5] = rnd[0];
			i++;
		}
	}
	filename[13] = '\0';
	ft_strlcat(filename, ".minishell", 24);
	close(rand_fd);
	return (ft_strdup(filename));
}
