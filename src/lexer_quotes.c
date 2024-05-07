/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adelaloy <adelaloy <adelaloy@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 10:02:32 by adelaloy          #+#    #+#             */
/*   Updated: 2024/05/04 15:35:19 by adelaloy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	quotes(char *line, int *i, t_token *token)
{
	int	j;
	int	len;

	j = *i + 1;
	while (line[j] != '\0' && line[j] != '\'')
		j++;
	if (line[j] == '\0')
	{
		printf("Error: unclosed quotes\n");
		free(token);
		g_sig = 1;
		return (1);
	}
	token->str = ft_substr(line, *i + 1, j - *i - 1);
	len = j - *i + 1;
	token->len = len;
	token->type = 4;
	*i = j + 1;
	return (0);
}

int	double_quotes(char *line, int *i, t_token *token)
{
	int	j;
	int	len;

	j = *i + 1;
	while (line[j] != '\0' && line[j] != '\"')
		j++;
	if (line[j] == '\0')
	{
		printf("Error: unclosed quotes\n");
		free(token);
		g_sig = 1;
		return (1);
	}
	token->str = ft_substr(line, *i + 1, j - *i - 1);
	len = j - *i + 1;
	token->len = len;
	token->type = 2;
	*i = j + 1;
	return (0);
}
