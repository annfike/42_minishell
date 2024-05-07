/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmiasnik <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 12:53:52 by dmiasnik          #+#    #+#             */
/*   Updated: 2023/10/11 17:18:48 by dmiasnik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	q;

	q = 0;
	while (*dst != '\0' && q < dstsize)
	{
		dst++;
		q++;
	}
	while (dstsize > 0 && q < dstsize - 1 && *src != '\0')
	{
		*dst = *src;
		src++;
		dst++;
		q++;
	}
	if (q < dstsize)
		*dst = '\0';
	while (*src != '\0')
	{
		src++;
		q++;
	}
	return (q);
}
