/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_args.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adelaloy <adelaloy <adelaloy@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 12:30:17 by adelaloy          #+#    #+#             */
/*   Updated: 2024/05/04 17:19:44 by adelaloy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_new_env_value(t_msh **msh, char *arg)
{
	char	*env_name;
	t_list	*envs;

	env_name = get_env_name(arg);
	envs = (*msh)->envs;
	while (envs)
	{
		if (ft_strncmp(envs->content, env_name, ft_strlen(env_name)) == 0)
		{
			free(envs->content);
			envs->content = arg;
			break ;
		}
		envs = envs->next;
	}
	free(env_name);
}

static int	check_export_arg(char *arg)
{
	int	i;

	i = 0;
	if (!ft_isalpha(arg[i]) && arg[i] != '_')
	{
		error("export: ", arg, "not a valid identifier");
		return (1);
	}
	i++;
	while (arg[i] && arg[i] != '=')
	{
		if (!ft_isalnum(arg[i]) && arg[i] != '_')
		{
			error("export: ", arg, "not a valid identifier");
			return (1);
		}
		i++;
	}
	return (0);
}

void	export_args(t_msh **msh, char *arg)
{
	char	*env_name;
	char	*env_value;

	if (check_export_arg(arg))
	{
		g_sig = 1;
		return ;
	}
	env_name = get_env_name(arg);
	env_value = get_env_value((*msh)->envs, env_name);
	if (!env_value)
		ft_lstadd_back(&(*msh)->envs, ft_lstnew(ft_strdup(arg)));
	else
	{
		set_new_env_value(msh, ft_strdup(arg));
	}
	free(env_name);
	free(env_value);
}

int	ft_export2(t_msh **msh, char **args)
{
	int	i;

	i = 1;
	if (!args[1])
		export_no_args(msh);
	else
	{
		while (args[i])
		{
			export_args(msh, args[i]);
			i++;
		}
	}
	return (0);
}
