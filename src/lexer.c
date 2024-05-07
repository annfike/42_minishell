/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adelaloy <adelaloy <adelaloy@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 10:02:32 by adelaloy          #+#    #+#             */
/*   Updated: 2024/05/04 17:15:11 by adelaloy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_token_values(char *str, int type, int len, t_token *token)
{
	if (token->str)
		free(token->str);
	token->str = ft_strdup(str);
	token->type = type;
	token->len = len;
}

int	redirection(char *line, int *i, t_token *token)
{
	if (line[*i] == '>')
	{
		if (line[*i + 1] == '>')
			set_token_values(">>", 6, 2, token);
		else
			set_token_values(">", 5, 1, token);
	}
	else
	{
		if (line[*i + 1] == '<')
			set_token_values("<<", 8, 2, token);
		else
			set_token_values("<", 7, 1, token);
	}
	*i += token->len;
	return (0);
}

int	word(char *line, int *i, t_token *token)
{
	int	j;
	int	len;

	j = *i + 1;
	while (line[j] != '\0' && line[j] != ' ' && line[j] != '\"'
		&& line[j] != '\'' && line[j] != '|' && line[j] != '>' && line[j] != '<'
		&& line[j] != '$')
	{
		j++;
	}
	len = j - *i;
	token->str = ft_substr(line, *i, j - *i);
	token->len = len;
	token->type = 4;
	*i = j;
	return (0);
}

static int	lexer_cases(t_msh **msh, char *line, int *i, t_token *token)
{
	int	ret;

	ret = 0;
	if (line[*i] == ' ')
		ret += space(i, token);
	else if (line[*i] == '\'')
		ret += quotes(line, i, token);
	else if (line[*i] == '\"')
		ret += double_quotes(line, i, token);
	else if (line[*i] == '|')
		ret += ft_pipe(i, token);
	else if (line[*i] == '>' || line[*i] == '<')
		ret += redirection(line, i, token);
	else if (line[*i] == '$')
		ret += dollar(msh, line, i, token);
	else
		ret += word(line, i, token);
	return (ret);
}

int	lexer(t_msh **msh, char *line)
{
	int		i;
	t_token	*token;
	int		ret;

	(*msh)->tokens = NULL;
	i = 0;
	ret = 0;
	while (line[i] != '\0')
	{
		token = (t_token *)malloc(sizeof(t_token));
		token->str = NULL;
		ret = lexer_cases(msh, line, &i, token);
		if (ret)
			return (0);
		ft_lstadd_back(&(*msh)->tokens, ft_lstnew((void *)token));
	}
	return (1);
}
