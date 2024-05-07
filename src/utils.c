/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adelaloy <adelaloy <adelaloy@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 10:02:32 by adelaloy          #+#    #+#             */
/*   Updated: 2024/05/02 18:58:36 by adelaloy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while ((s1[i] || s2[i]))
	{
		if ((unsigned char)s1[i] != (unsigned char)s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}

void	ft_lst_print(t_list *lst)
{
	printf("here");
	printf("%s\n", ((t_token *)(lst->content))->str);
	while (lst)
	{
		printf("%s\n", ((t_token *)(lst->content))->str);
		printf("%d\n", ((t_token *)(lst->content))->len);
		lst = lst->next;
	}
}

void	ft_list_remove_if(t_list **begin_list, void *data_ref, int (*cmp)())
{
	t_list	*token_node;

	if (begin_list == NULL || *begin_list == NULL)
		return ;
	token_node = *begin_list;
	if (cmp(((t_token *)(token_node->content))->str, data_ref) == 0)
	{
		*begin_list = token_node->next;
		free(((t_token *)(token_node->content))->str);
		free(token_node->content);
		free(token_node);
		ft_list_remove_if(begin_list, data_ref, cmp);
	}
	else
	{
		token_node = *begin_list;
		ft_list_remove_if(&token_node->next, data_ref, cmp);
	}
}

void	print_tokens(t_msh **msh)
{
	t_list	*token;

	token = (*msh)->tokens;
	while (token)
	{
		printf("-------------------------\n");
		printf("token=%s\n", ((t_token *)(token->content))->str);
		printf("len=%d\n", ((t_token *)(token->content))->len);
		printf("type=%d\n", ((t_token *)(token->content))->type);
		token = token->next;
	}
}

void	error(char *cmd, char *arg, char *error)
{
	ft_putstr_fd("minishell: ", 2);
	if (cmd)
	{
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": ", 2);
	}
	ft_putstr_fd(arg, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(error, 2);
	ft_putstr_fd("\n", 2);
}
