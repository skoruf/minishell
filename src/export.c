/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cthaler <cthaler@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 13:05:45 by cthaler           #+#    #+#             */
/*   Updated: 2024/01/04 13:05:47 by cthaler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	valid_key2(char *arg, t_msd *data, int ret)
{
	if (ret == 0 && arg[0] == '-')
	{
		ft_putstr_fd("🧙: export: -", 2);
		ft_putchar_fd(arg[1], 2);
		ft_putendl_fd(": invalid option", 2);
		ft_putstr_fd("export: usage: export [-fn] [name[=value] ...] ", 2);
		ft_putendl_fd("or export -p", 2);
		data->exit_code = 2;
	}
	else if (ret == 0 || arg[0] == '=')
	{
		ft_putstr_fd("🧙: export: `", 2);
		ft_putstr_fd(arg, 2);
		ft_putendl_fd("': not a valid identifier", 2);
		data->exit_code = 1;
	}
}

static int	valid_key(char *arg, t_msd *data)
{
	int	i;
	int	ret;

	i = 0;
	ret = 1;
	while (arg[i] && arg[i] != '=')
	{
		if (!env_pattern(arg[i], i + 1))
		{
			ret = 0;
			break ;
		}
		i++;
	}
	valid_key2(arg, data, ret);
	return (ret);
}

static int	export_vars(char **new_env, char **args, t_msd *data, int i)
{
	int		index;
	int		is_env;
	char	*new_var;

	index = arr_len(new_env);
	while (args[i])
	{
		if (valid_key(args[i], data))
		{
			is_env = is_in_env(new_env, args[i]);
			new_var = ft_strdup(args[i]);
			if (!new_var || is_env == -2)
				return (0);
			if (is_env >= 0)
			{
				free(new_env[is_env]);
				new_env[is_env] = new_var;
			}
			else
				new_env[index++] = new_var;
		}
		i++;
	}
	return (1);
}

static char	**copy_env(char **env, int arg_len)
{
	char	**new_env;
	int		len;
	int		i;

	i = 0;
	len = arr_len(env) + arg_len;
	new_env = malloc(sizeof(new_env) * len);
	if (!new_env)
		return (NULL);
	while (env[i])
	{
		new_env[i] = ft_strdup(env[i]);
		if (!new_env[i])
			return (free_arr(new_env, i - 1), NULL);
		i++;
	}
	while (i < len)
		new_env[i++] = 0;
	return (new_env);
}

int	export(t_msd *data, char **args)
{
	char	**env_sorted;
	char	**new_env;
	int		ret;

	if (!args[1])
	{
		env_sorted = sort_env(data->envp);
		protecc(!env_sorted, data, 1);
		print_env(env_sorted);
		free(env_sorted);
		return (0);
	}
	new_env = copy_env(data->envp, arr_len(args));
	protecc(!new_env, data, 1);
	ret = export_vars(new_env, args, data, 1);
	if (!ret)
		free_arr(new_env, arr_len(new_env) - 1);
	protecc(!ret, data, 1);
	free_arr(data->envp, arr_len(data->envp) - 1);
	data->envp = new_env;
	return (0);
}
