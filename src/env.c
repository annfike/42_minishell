/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmiasnik <dmiasnik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 10:02:32 by adelaloy          #+#    #+#             */
/*   Updated: 2024/05/03 16:29:42 by dmiasnik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parse_envs_create_list(t_msh **msh, char **envp)
{
	t_list	*env;
	int		i;

	i = 0;
	(*msh)->envs = NULL;
	while (envp[i])
	{
		env = ft_lstnew(ft_strdup(envp[i]));
		ft_lstadd_back(&(*msh)->envs, env);
		i++;
	}
	return (1);
}

void	print_envs(t_msh **msh)
{
	t_list	*envs;

	envs = (*msh)->envs;
	while (envs)
	{
		printf("-------------------------\n");
		printf("env=%s\n", (char *)envs->content);
		envs = envs->next;
	}
}

char	*get_env_name(char *env)
{
	int		i;
	char	*env_name;

	i = 0;
	while (env && env[i] && env[i] != '=')
		i++;
	env_name = ft_substr(env, 0, i);
	return (env_name);
}

char	*get_env_value(t_list *env, char *str)
{
	char	*env_value;
	char	*env_name;

	while (env)
	{
		env_name = get_env_name(env->content);
		if (!ft_strcmp(env_name, str))
		{
			env_value = ft_substr(env->content, ft_strlen(env_name) + 1,
					ft_strlen(env->content));
			free(env_name);
			return (env_value);
		}
		free(env_name);
		env = env->next;
	}
	return (NULL);
}
