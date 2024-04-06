/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cthaler <cthaler@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 14:26:20 by cthaler           #+#    #+#             */
/*   Updated: 2024/03/12 14:26:22 by cthaler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
/*
void	ctrl_c2(__attribute__((unused)) int signum)
{
	rl_replace_line("", 0);
	rl_on_new_line();
}
*/
void	ctrl_c(__attribute__((unused)) int signum)
{
	g_sig = signum;
	ft_putstr_fd("\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	ctrl_c_heredoc(__attribute__((unused)) int signum)
{
	g_sig = signum;
	ioctl(0, TIOCSTI, "\n");
	rl_replace_line("", 0);
	rl_on_new_line();
}
