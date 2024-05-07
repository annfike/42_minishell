/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmiasnik <dmiasnik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 10:02:32 by adelaloy          #+#    #+#             */
/*   Updated: 2024/05/03 11:20:38 by dmiasnik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_num_args(t_list *token)
{
	int		i;
	t_list	*tmp;

	i = 0;
	tmp = token;
	while (tmp)
	{
		if (((t_token *)(tmp->content))->type == 4)
			i++;
		else if (((t_token *)(tmp->content))->type == 3)
			break ;
		tmp = tmp->next;
	}
	return (i);
}

static int	make_cmd_type4(t_cmd *content, t_list **token, int *i, int flag)
{
	t_file	*file;

	if (flag == 0)
	{
		(content->args)[*i] = ft_strdup(((t_token *)((*token)->content))->str);
		(*i)++;
	}
	else
	{
		if (flag == 8)
			content->hdoc = ((t_token *)((*token)->content))->str;
		else if (flag == 7 || flag == 5 || flag == 6)
		{
			file = malloc(sizeof(t_file));
			file->file = ((t_token *)((*token)->content))->str;
			file->type = flag;
			ft_lstadd_back(&content->file, ft_lstnew(file));
		}
		flag = 0;
	}
	return (flag);
}

void	make_cmd_lst(t_cmd *content, t_list **token)
{
	int	toktype;
	int	args;
	int	i;
	int	flag;

	args = get_num_args(*token);
	content->args = (char **)malloc(sizeof(char *) * (args + 1));
	content->file = NULL;
	content->hdoc = NULL;
	i = 0;
	flag = 0;
	while (*token)
	{
		toktype = ((t_token *)((*token)->content))->type;
		if (toktype == 3)
			break ;
		if (toktype == 5 || toktype == 6 || toktype == 7 || toktype == 8)
			flag = toktype;
		else if (toktype == 4)
			flag = make_cmd_type4(content, token, &i, flag);
		*token = (*token)->next;
	}
	(content->args)[i] = NULL;
}

void	print_cmds(t_msh **msh)
{
	t_list		*cmd;

	cmd = (*msh)->cmds;
	while (cmd)
	{
		printf ("command-------------------------\n");
		printf ("cmd arg1=%s\n", ((t_cmd *)(cmd->content))->args[0]);
		printf ("cmd arg2=%s\n", ((t_cmd *)(cmd->content))->args[1]);
		printf ("cmd hdoc=%s\n", ((t_cmd *)(cmd->content))->hdoc);
		cmd = cmd->next;
	}
}

void	parser(t_msh **msh)
{
	t_list	*cmd;
	t_list	*token;
	t_cmd	*content;
	int		toktype;

	(*msh)->cmds = NULL;
	token = (*msh)->tokens;
	while (token)
	{
		toktype = ((t_token *)(token->content))->type;
		if (toktype == 4 || toktype == 7 || toktype == 8)
		{
			content = (t_cmd *)malloc(sizeof(t_cmd));
			make_cmd_lst(content, &token);
			cmd = ft_lstnew(content);
			ft_lstadd_back(&(*msh)->cmds, cmd);
		}
		else
			token = token->next;
	}
}
