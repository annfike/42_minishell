/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_quotes_open.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adelaloy <adelaloy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 10:02:32 by adelaloy          #+#    #+#             */
/*   Updated: 2024/05/06 12:57:26 by adelaloy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*process_quote2(char *str, int i, int j, char *final_str)
{
	char	*after_dollar;
	char	*s;

	after_dollar = ft_substr(str, j, i - j);
	free(str);
	s = final_str;
	final_str = ft_strjoin(s, after_dollar);
	free(after_dollar);
	free(s);
	return (final_str);
}

static void	set_token_values1(char *str, t_token *token)
{
	if (token->str)
		free(token->str);
	token->str = str;
	token->len = ft_strlen(str);
}

static char	*process_quote1(t_token *token, char *before_d, char *final_str)
{
	char	*inside_dollar;
	char	*s;

	inside_dollar = token->str;
	token->str = NULL;
	s = ft_strjoin(final_str, before_d);
	free(final_str);
	free(before_d);
	final_str = ft_strjoin(s, inside_dollar);
	free(inside_dollar);
	free(s);
	return (final_str);
}

static void	process_quotes(t_msh **msh, t_token *token)
{
	char	*str;
	int		i;
	int		j;
	char	*final_str;
	char	*before_dollar;

	str = ft_strdup(token->str);
	i = 0;
	j = 0;
	final_str = ft_strdup("");
	while (str[i])
	{
		while (str[i] && str[i] != '$')
			i++;
		if (str[i] == '$')
		{
			before_dollar = ft_substr(str, j, i - j);
			dollar(msh, str, &i, token);
			j = i;
			final_str = process_quote1(token, before_dollar, final_str);
		}
		i++;
	}
	final_str = process_quote2(str, i, j, final_str);
	set_token_values1(final_str, token);
}

int	open_quotes(t_msh **msh)
{
	t_list	*token_node;

	token_node = (*msh)->tokens;
	while (token_node)
	{
		if (((t_token *)(token_node->content))->type == 2)
		{
			process_quotes(msh, token_node->content);
			((t_token *)(token_node->content))->type = 4;
		}
		token_node = token_node->next;
	}
	return (1);
}
