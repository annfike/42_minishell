/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adelaloy <adelaloy <adelaloy@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 12:30:17 by adelaloy          #+#    #+#             */
/*   Updated: 2024/05/04 17:20:18 by adelaloy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_sort_str_arr(char **arr)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	while (arr[i])
	{
		j = i + 1;
		while (arr[j])
		{
			if (ft_strcmp(arr[i], arr[j]) > 0)
			{
				tmp = arr[i];
				arr[i] = arr[j];
				arr[j] = tmp;
			}
			j++;
		}
		i++;
	}
	return (arr);
}

void	print_arr(char **arr)
{
	int		i;
	char	*env_value;
	char	*env_name;

	i = 0;
	while (arr[i])
	{
		env_name = get_env_name(arr[i]);
		env_value = ft_substr(arr[i], ft_strlen(env_name) + 1,
				ft_strlen(arr[i]));
		printf("declare -x %s=\"%s\"\n", env_name, env_value);
		free(env_name);
		free(env_value);
		i++;
	}
}

char	**get_envs_arr(t_msh **msh)
{
	t_list	*envs;
	char	**envs_arr;
	int		i;
	int		size;

	i = 0;
	envs = (*msh)->envs;
	size = ft_lstsize(envs) + 1;
	envs_arr = (char **)(malloc(sizeof(char *) * size));
	while (envs)
	{
		envs_arr[i] = (char *)envs->content;
		envs = envs->next;
		i++;
	}
	envs_arr[i] = NULL;
	return (envs_arr);
}

void	free_envs_arr(char **envs_arr)
{
	int	i;

	i = 0;
	while (envs_arr[i])
	{
		free(envs_arr[i]);
		i++;
	}
	free(envs_arr);
}

void	export_no_args(t_msh **msh)
{
	char	**envs_arr;

	envs_arr = get_envs_arr(msh);
	envs_arr = ft_sort_str_arr(envs_arr);
	print_arr(envs_arr);
	free(envs_arr);
}
