/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_dollar.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adelaloy <adelaloy <adelaloy@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 10:02:32 by adelaloy          #+#    #+#             */
/*   Updated: 2024/05/04 17:13:43 by adelaloy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	dollar_special_cases(char *line, int *i, t_token *token)
{
	if (line[*i + 1] == '?')
	{
		token->str = ft_itoa(g_sig);
		token->len = ft_strlen(token->str);
		token->type = 4;
		*i = *i + 2;
	}
	else if (line[*i + 1] == ' ' || !line[*i + 1])
	{
		token->str = ft_strdup("$");
		token->len = 1;
		token->type = 4;
		*i = *i + 1;
	}
	return (0);
}

static int	dollar_case_env(t_msh **msh, char *line, int *i, t_token *token)
{
	int		j;
	char	*str;
	char	*env;

	j = *i + 1;
	while (line[j] != '\0' && line[j] != ' ' && line[j] != '\"'
		&& line[j] != '\'' && line[j] != '|' && line[j] != '>' && line[j] != '<'
		&& line[j] != '$')
	{
		j++;
	}
	str = ft_substr(line, *i + 1, j - *i - 1);
	env = get_env_value((*msh)->envs, str);
	if (env == NULL)
	{
		token->str = ft_strdup("");
		free(env);
	}
	else
		token->str = env;
	token->len = ft_strlen(token->str);
	token->type = 4;
	*i = *i + ft_strlen(str) + 1;
	free(str);
	return (0);
}

int	dollar(t_msh **msh, char *line, int *i, t_token *token)
{
	int		j;

	j = *i + 1;
	if (token->str)
		free(token->str);
	if (line[j] == '?' || line[j] == ' ' || !line[j])
	{
		dollar_special_cases(line, i, token);
		return (0);
	}
	dollar_case_env(msh, line, i, token);
	return (0);
}
