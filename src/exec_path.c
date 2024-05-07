/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adelaloy <adelaloy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 11:36:01 by dmiasnik          #+#    #+#             */
/*   Updated: 2024/05/06 11:47:27 by adelaloy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_path_cmd(char *path, char *cmd)
{
	char	*path_cmd;
	char	*path_cmd1;

	path_cmd1 = ft_strjoin(path, "/");
	path_cmd = ft_strjoin(path_cmd1, cmd);
	free(path_cmd1);
	return (path_cmd);
}

char	*get_cmd_path(t_list *envs, char *cmd)
{
	char	**path;
	char	*path_cmd;
	int		i;

	while (envs)
	{
		if (!ft_strncmp(envs->content, "PATH=", 5))
		{
			path = ft_split(envs->content + 5, ':');
			i = 0;
			while (path[i])
			{
				path_cmd = get_path_cmd(path[i++], cmd);
				if (access(path_cmd, F_OK) == 0)
				{
					free(path);
					return (path_cmd);
				}
				free(path_cmd);
			}
			free(path);
		}
		envs = envs->next;
	}
	return (NULL);
}
