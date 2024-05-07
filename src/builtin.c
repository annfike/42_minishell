/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adelaloy <adelaloy <adelaloy@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 12:30:17 by adelaloy          #+#    #+#             */
/*   Updated: 2024/05/04 17:40:44 by adelaloy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_builtin2(t_msh **msh, char **args)
{
	if (ft_strcmp(args[0], "export") == 0)
		return (ft_export2(msh, args));
	else if (ft_strcmp(args[0], "unset") == 0)
		return (ft_unset2(msh, args));
	else if (ft_strcmp(args[0], "exit") == 0)
		return (ft_exit(args));
	else if (ft_strcmp(args[0], "cd") == 0)
		return (ft_cd2(msh, args));
	return (1);
}

int	ft_unset(t_msh **msh, char **args)
{
	if (ft_unset2(msh, args))
		exit(2);
	exit(0);
}

int	ft_export(t_msh **msh, char **args)
{
	if (ft_export2(msh, args))
		exit(2);
	exit(0);
}

int	ft_cd(t_msh **msh, char **args)
{
	if (ft_cd2(msh, args))
		exit(2);
	exit(0);
}

int	exec_builtin(t_msh **msh, char **args)
{
	if (ft_strcmp(args[0], "echo") == 0)
		return (ft_echo(args));
	else if (ft_strcmp(args[0], "cd") == 0)
		return (ft_cd(msh, args));
	else if (ft_strcmp(args[0], "pwd") == 0)
		return (ft_pwd());
	else if (ft_strcmp(args[0], "export") == 0)
		return (ft_export2(msh, args));
	else if (ft_strcmp(args[0], "unset") == 0)
		return (ft_unset2(msh, args));
	else if (ft_strcmp(args[0], "env") == 0)
		return (ft_env(msh));
	else if (ft_strcmp(args[0], "exit") == 0)
		return (ft_exit(args));
	return (1);
}
