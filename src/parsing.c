/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cthaler <cthaler@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 11:44:43 by cthaler           #+#    #+#             */
/*   Updated: 2024/01/21 11:44:45 by cthaler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	check_syntax(t_msd *data, int l_tkn, int ret)
{
	t_list	*args;

	args = data->arg_list;
	while (args)
	{
		if (((l_tkn == PIPE || is_redir(l_tkn))
				&& args->token == PIPE) || (is_redir(l_tkn)
				&& is_redir(args->token))
			|| (is_redir(args->token) && !args->next)
			|| (args->token == PIPE && !args->next)
			|| (args->token == PIPE && !l_tkn))
		{
			ft_putstr_fd("🧙: syntax error near unexpected token `",
				2);
			ft_putstr_fd(args->s, 2);
			ft_putstr_fd("'\n", 2);
			data->exit_code = 2;
			return (clear_round(data), 0);
		}
		l_tkn = args->token;
		args = args->next;
	}
	return (ret);
}
