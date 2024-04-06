/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cthaler <cthaler@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 11:05:30 by cthaler           #+#    #+#             */
/*   Updated: 2024/03/03 11:05:32 by cthaler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int	can_haz_env(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '$' && s[i + 1] != '?' && env_pattern(s[i + 1], 0))
			return (1);
		else if (s[i] == '$' && s[i + 1] == '?')
			return (1);
		else if (s[i] == '$')
			s[i] = 30;
		i++;
	}
	return (0);
}

static int	parse_here(t_msd *data)
{
	int	i;

	i = 0;
	while (can_haz_env(data->line))
	{
		data->line = env_heredoc(data->line, data, 0);
		if (!data->line)
			return (0);
	}
	while (data->line[i])
	{
		if (data->line[i] == 30)
			data->line[i] = '$';
		i++;
	}
	return (1);
}

static void	here_error(char *eof)
{
	ft_putstr_fd("🧙: warning: here-document at line 1 ", 2);
	ft_putstr_fd("delimited by end-of-file (wanted `", 2);
	ft_putstr_fd(eof, 2);
	ft_putendl_fd("')", 2);
}

static void	here_loop(t_msd *data, t_list *redir, int fd_here)
{
	while (data->line)
	{
		if (g_sig == SIGINT)
		{
			data->exit_code = 130;
			break ;
		}
		free_if(data->line);
		data->line = readline("> ");
		if (!data->line)
			break ;
		if (redir->token != HEREDOC_Q)
			protecc(!parse_here(data), data, 1);
		if (!ft_strncmp(data->line, redir->s, ft_strlen(redir->s) + 1))
			break ;
		write(fd_here, data->line, ft_strlen(data->line));
		write(fd_here, "\n", 1);
	}
}

void	here_and_now(t_msd *data, t_list *redir)
{
	signal(SIGINT, ctrl_c_heredoc);
	close_if(data->fd_here);
	data->fd_here = open(data->heredoc, O_TRUNC | O_CREAT | O_RDWR, 0644);
	protecc(data->fd_here == -1, data, 1);
	here_loop(data, redir, data->fd_here);
	close(data->fd_here);
	data->fd_here = -1;
	close_if(data->red_in);
	signal(SIGINT, SIG_IGN);
	if (!data->line)
		here_error(redir->s);
}
