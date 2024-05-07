/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adelaloy <adelaloy <adelaloy@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 10:02:32 by adelaloy          #+#    #+#             */
/*   Updated: 2024/05/04 15:46:18 by adelaloy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	parser_syntax_error(void)
{
	ft_putstr_fd("minishell: syntax error near unexpected token\n", 2);
	return (0);
}

static int	lexer_join_words(t_msh **msh)
{
	t_list	*token;
	t_list	*token_next;
	char	*final_str;

	token = (*msh)->tokens;
	token_next = token->next;
	while (token && token_next)
	{
		if (((t_token *)(token->content))->type == 4
			&& ((t_token *)(token->next->content))->type == 4)
		{
			((t_token *)(token->content))->len
				+= ((t_token *)(token->next->content))->len;
			final_str = ft_strjoin(((t_token *)(token->content))->str,
					(((t_token *)(token->next->content))->str));
			((t_token *)(token->content))->str = final_str;
			token->next = token_next->next;
			ft_lstdelone(token_next, free);
			token_next = token->next;
			continue ;
		}
		token = token->next;
		token_next = token->next;
	}
	return (1);
}

int	lexer_check(t_msh **msh)
{
	t_list	*token;
	int		toktype;

	open_quotes(msh);
	lexer_join_words(msh);
	delete_spaces(msh);
	token = (*msh)->tokens;
	if (!token)
		return (0);
	if (((t_token *)(token->content))->type == 3)
		return (parser_syntax_error());
	while (token)
	{
		toktype = ((t_token *)(token->content))->type;
		if (toktype == 5 || toktype == 6 || toktype == 7 || toktype == 8)
		{
			if (!token->next)
				return (parser_syntax_error());
			if (((t_token *)(token->next->content))->type != 4)
				return (parser_syntax_error());
		}
		token = token->next;
	}
	return (1);
}
