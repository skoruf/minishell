/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cthaler <cthaler@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 15:50:08 by cthaler           #+#    #+#             */
/*   Updated: 2024/04/06 15:50:25 by cthaler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	toke(int *fd, t_list *redir)
{
	if (*fd != -1)
		close(*fd);
	if (redir->token == OUT)
		*fd = open(redir->s, O_TRUNC | O_CREAT | O_WRONLY, 0644);
	else if (redir->token == APPEND)
		*fd = open(redir->s, O_APPEND | O_CREAT | O_WRONLY, 0644);
}

static void	redirect2(t_msd *data)
{
	if (!access(data->heredoc, R_OK))
	{
		if (data->red_in != -1)
			close(data->red_in);
		data->red_in = open(data->heredoc, O_RDONLY);
		if (data->red_in == -1)
			execancel(data, 1, data->heredoc, strerror(errno));
	}
}

void	redirect(t_msd *data, t_list *redir)
{
	while (redir && data->execute)
	{
		if (redir->token == IN)
		{
			if (data->red_in != -1)
				close(data->red_in);
			if (!access(redir->s, R_OK))
			{
				data->red_in = open(redir->s, O_RDONLY);
				if (data->red_in == -1)
					execancel(data, 1, redir->s, strerror(errno));
			}
			else
				execancel(data, 1, redir->s, strerror(errno));
		}
		else if (redir->token == OUT || redir->token == APPEND)
		{
			toke(&data->red_out, redir);
			if (data->red_out == -1)
				execancel(data, 1, redir->s, strerror(errno));
		}
		else if (redir->token == HEREDOC || redir->token == HEREDOC_Q)
			redirect2(data);
		redir = redir->next;
	}
}
