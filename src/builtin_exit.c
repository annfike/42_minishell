/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adelaloy <adelaloy <adelaloy@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 12:30:17 by adelaloy          #+#    #+#             */
/*   Updated: 2024/05/04 17:39:12 by adelaloy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_count(char **args)
{
	int		i;

	i = 0;
	while (*args)
	{
		i++;
		args++;
	}
	return (i);
}

static int	ft_isdig(char *c)
{
	if (*c == '-' || *c == '+')
		c++;
	while (*c)
	{
		if (!ft_isdigit(*c))
			return (0);
		c++;
	}
	return (1);
}

int	ft_exit(char **args)
{
	if (get_count(args) == 3)
	{
		ft_putstr_fd("exit: too many arguments\n", 2);
		g_sig = 1;
		return (0);
	}
	else if (get_count(args) == 1)
	{
		exit(g_sig);
	}
	else if (!(ft_isdig(args[1])))
	{
		ft_putstr_fd("exit: ", 2);
		ft_putstr_fd(args[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		exit(255);
	}
	else
	{
		exit(ft_atoi(args[1]));
	}
	exit (0);
}
