/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cthaler <cthaler@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 13:21:52 by cthaler           #+#    #+#             */
/*   Updated: 2024/01/02 13:21:54 by cthaler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int	env_pwd2(t_msd *data, char *pwd2)
{
	char	**envp;
	char	*old_pwd;

	old_pwd = ft_strjoin("OLDPWD=", pwd2);
	if (!old_pwd)
		return (0);
	if (!ft_strncmp(old_pwd, "OLDPWD=", 8))
		free(old_pwd);
	else if (!set_env(data->envp, "OLDPWD", old_pwd))
	{
		envp = init_env_arr(data->envp, old_pwd);
		if (!envp)
			return (free(old_pwd), 0);
		free_arr(data->envp, arr_len(data->envp) - 1);
		data->envp = envp;
	}
	return (1);
}

static int	env_pwd(t_msd *data, char *pwd2)
{
	char	wd[PATH_MAX];
	char	*pwd;
	char	**envp;

	if (!getcwd(wd, PATH_MAX - 1))
		ft_putendl_fd("🧙: cd: error retrieving current directory:\
 getcwd: cannot access parent directories: No such file or directory", 2);
	else
	{
		pwd = ft_strjoin("PWD=", wd);
		if (!pwd)
			return (0);
		if (!set_env(data->envp, "PWD", pwd))
		{
			envp = init_env_arr(data->envp, pwd);
			if (!envp)
				return (free(pwd), 0);
			free_arr(data->envp, arr_len(data->envp) - 1);
			data->envp = envp;
		}
	}
	if (!env_pwd2(data, pwd2))
		return (0);
	return (1);
}

static void	ef(t_msd *data, char *pwd)
{
	if (data->exit_code == -1 && data->cmds->bin[1])
	{
		ft_putstr_fd("🧙: ", 2);
		ft_putstr_fd(data->cmds->bin[1], 2);
		ft_putendl_fd(": No such file or directory", 2);
	}
	else
		protecc(!env_pwd(data, pwd), data, 1);
	if (data->exit_code == -1)
		data->exit_code = 1;
}

void	cd(t_msd *data)
{
	char	*home;
	char	pwd[PATH_MAX];

	getcwd(pwd, PATH_MAX - 1);
	if (!data->cmds->bin[1])
	{
		home = get_env_value(data->envp, "HOME");
		if (home)
			data->exit_code = chdir(home);
		else
		{
			data->exit_code = 1;
			ft_putendl_fd("🧙: cd: HOME not set", 2);
		}
	}
	else if (data->cmds->bin[1] && data->cmds->bin[2])
	{
		data->exit_code = 1;
		ft_putendl_fd("🧙: too many arguments", 2);
		return ;
	}
	else if (data->cmds->bin[1])
		data->exit_code = chdir(data->cmds->bin[1]);
	ef(data, pwd);
}
