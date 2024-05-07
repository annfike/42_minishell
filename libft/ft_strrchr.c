/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmiasnik <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 13:16:24 by dmiasnik          #+#    #+#             */
/*   Updated: 2023/10/11 17:16:18 by dmiasnik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strrchr(const char *s, int c)
{
	char	cc;
	char	*res;

	cc = c;
	res = 0;
	while (*s)
	{
		if (*s == cc)
			res = (char *)s;
		s++;
	}
	if (*s == cc)
		return ((char *)s);
	return (res);
}
