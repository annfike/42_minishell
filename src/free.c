/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adelaloy <adelaloy <adelaloy@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 10:02:32 by adelaloy          #+#    #+#             */
/*   Updated: 2024/05/04 17:51:11 by adelaloy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_tokens(t_msh *msh)
{
	t_list	*tmp;

	while (msh->tokens)
	{
		tmp = msh->tokens->next;
		free(((t_token *)msh->tokens->content)->str);
		((t_token *)msh->tokens->content)->str = NULL;
		free((t_token *)msh->tokens->content);
		msh->tokens->content = NULL;
		free((t_token *)msh->tokens);
		msh->tokens = NULL;
		msh->tokens = tmp;
	}
	msh->tokens = NULL;
}

static void	free_cmd_file(t_list *file)
{
	t_list	*tmp;

	while (file)
	{
		tmp = file->next;
		free((t_file *)file->content);
		file->content = NULL;
		free(file);
		file = NULL;
		file = tmp;
	}
	file = NULL;
}

static void	free_cmd(t_cmd *cmd)
{
	int	i;

	i = 0;
	while (cmd->args[i])
	{
		free(cmd->args[i]);
		cmd->args[i] = NULL;
		i++;
	}
	free(cmd->args);
	cmd->args = NULL;
	if (cmd->file)
		free_cmd_file(cmd->file);
	cmd->file = NULL;
	cmd->hdoc = NULL;
	free(cmd);
	cmd = NULL;
}

static void	free_cmds(t_msh *msh)
{
	t_list	*tmp;

	while (msh->cmds)
	{
		tmp = msh->cmds->next;
		free_cmd(msh->cmds->content);
		msh->cmds->content = NULL;
		free(msh->cmds);
		msh->cmds = NULL;
		msh->cmds = tmp;
	}
	msh->cmds = NULL;
}

void	free_msh(t_msh **msh)
{
	if ((*msh)->tokens)
		free_tokens(*msh);
	if ((*msh)->cmds)
		free_cmds(*msh);
}
