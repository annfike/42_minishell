/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmiasnik <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 16:54:46 by dmiasnik          #+#    #+#             */
/*   Updated: 2023/10/12 14:59:46 by dmiasnik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	fill_words(char **res, char const *s, char c)
{
	char const	*start;
	int			i;

	i = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		start = s;
		while (*s && *s != c)
			s++;
		if (s > start)
		{
			res[i] = ft_substr(start, 0, s - start);
			if (res[i] == NULL)
			{
				while (i)
					free(res[i-- - 1]);
				return (0);
			}
			i++;
		}
	}
	res[i] = NULL;
	return (1);
}

int	get_wordcnt(char const *s, char c)
{
	int	cnt;

	cnt = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s)
			cnt++;
		while (*s && *s != c)
			s++;
	}
	return (cnt);
}

char	**ft_split(char const *s, char c)
{
	char	**res;

	res = malloc(sizeof(char *) * (get_wordcnt(s, c) + 1));
	if (res == NULL)
		return (NULL);
	if (!fill_words(res, s, c))
	{
		free(res);
		return (NULL);
	}
	return (res);
}
