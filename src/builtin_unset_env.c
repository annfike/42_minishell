/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset_env.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmiasnik <dmiasnik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 12:30:17 by adelaloy          #+#    #+#             */
/*   Updated: 2024/05/03 16:56:07 by dmiasnik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_list_remove_if1(t_list **begin_list, void *data_ref, int (*cmp)())
{
	t_list	*envs;

	if (begin_list == NULL || *begin_list == NULL)
		return ;
	envs = *begin_list;
	if (cmp(envs->content, data_ref, ft_strlen(data_ref)) == 0)
	{
		*begin_list = envs->next;
		free(envs->content);
		free(envs);
		ft_list_remove_if1(begin_list, data_ref, cmp);
	}
	else
	{
		envs = *begin_list;
		ft_list_remove_if1(&envs->next, data_ref, cmp);
	}
}

int	ft_unset2(t_msh **msh, char **args)
{
	int	i;

	i = 1;
	while (args[i])
	{
		ft_list_remove_if1(&((*msh)->envs), args[i], ft_strncmp);
		i++;
	}
	return (0);
}

int	ft_env(t_msh **msh)
{
	t_list	*envs;

	envs = (*msh)->envs;
	while (envs)
	{
		printf("%s\n", (char *)envs->content);
		envs = envs->next;
	}
	exit(0);
}
