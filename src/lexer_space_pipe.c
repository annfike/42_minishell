/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_space_pipe.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adelaloy <adelaloy <adelaloy@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 10:02:32 by adelaloy          #+#    #+#             */
/*   Updated: 2024/05/04 16:25:06 by adelaloy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pipe(int *i, t_token *token)
{
	token->str = ft_strdup("|");
	token->len = 1;
	token->type = 3;
	(*i)++;
	return (0);
}

int	space(int *i, t_token *token)
{
	token->str = ft_strdup(" ");
	token->len = 1;
	token->type = 1;
	(*i)++;
	return (0);
}

int	delete_spaces(t_msh **msh)
{
	ft_list_remove_if(&(*msh)->tokens, " ", ft_strcmp);
	return (1);
}
