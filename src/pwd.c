/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cthaler <cthaler@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 12:02:26 by cthaler           #+#    #+#             */
/*   Updated: 2024/01/02 12:02:30 by cthaler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	pwd(void)
{
	char	wd[PATH_MAX];

	if (!getcwd(wd, PATH_MAX - 1))
	{
		ft_putendl_fd("🧙: could not get current working dir", 2);
		return (1);
	}
	else
		ft_putendl_fd(wd, 1);
	return (0);
}
