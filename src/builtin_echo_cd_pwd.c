/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo_cd_pwd.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adelaloy <adelaloy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 12:30:17 by adelaloy          #+#    #+#             */
/*   Updated: 2024/05/06 13:16:44 by adelaloy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_echo(char **args)
{
	int	i;
	int	n_flag;

	if (!args[1])
		exit(0);
	if (ft_strcmp(args[1], "-n") == 0)
	{
		n_flag = 1;
		i = 2;
	}
	else
	{
		n_flag = 0;
		i = 1;
	}
	while (args[i])
	{
		write(1, args[i], ft_strlen(args[i]));
		if (args[i + 1])
			write(1, " ", 1);
		i++;
	}
	if (n_flag == 0)
		write(1, "\n", 1);
	exit(0);
}

void	set_new_dir_envs(t_msh **msh, char *dir_begin, char *dir_end)
{
	char	*oldpwd;
	char	*pwd;
	char	*tmp;

	oldpwd = ft_strjoin("OLDPWD=", dir_begin);
	pwd = ft_strjoin("PWD=", dir_end);
	tmp = get_env_value((*msh)->envs, "OLDPWD");
	if (tmp)
		set_new_env_value(msh, oldpwd);
	else
		ft_lstadd_back(&(*msh)->envs, ft_lstnew(oldpwd));
	free(tmp);
	tmp = get_env_value((*msh)->envs, "PWD");
	if (tmp)
		set_new_env_value(msh, pwd);
	else
		ft_lstadd_back(&(*msh)->envs, ft_lstnew(pwd));
	free(tmp);
}

int	cd_special_cases(t_msh **msh, char **args)
{
	char	*dir_end;
	char	*oldpwd;

	if (args[1] && ft_strcmp(args[1], "-") == 0)
	{
		oldpwd = get_env_value((*msh)->envs, "OLDPWD");
		if (!oldpwd)
		{
			printf("cd: OLDPWD not set\n");
			free(oldpwd);
			return (1);
		}
		else
		{
			chdir(oldpwd);
			free(oldpwd);
		}
	}
	else
	{
		dir_end = get_env_value((*msh)->envs, "HOME");
		chdir(dir_end);
		free(dir_end);
	}
	return (0);
}

int	ft_cd2(t_msh **msh, char **args)
{
	char	*dir_begin;
	char	*dir_end;

	if (!args[1] || ft_strcmp(args[1], "~") == 0 || ft_strcmp(args[1],
			"--") == 0 || ft_strcmp(args[1], "-") == 0)
	{
		cd_special_cases(msh, args);
	}
	else if (chdir(args[1]) == -1)
	{
		error("cd", args[1], "No such file or directory");
		g_sig = 1;
	}
	dir_begin = get_env_value((*msh)->envs, "PWD");
	dir_end = getcwd(NULL, 0);
	set_new_dir_envs(msh, dir_begin, dir_end);
	free(dir_begin);
	free(dir_end);
	return (0);
}

int	ft_pwd(void)
{
	char	*cwd;
	char	buff[4096];

	cwd = getcwd(buff, 4096);
	if (cwd != NULL)
		ft_putendl_fd(cwd, 1);
	exit(0);
}
