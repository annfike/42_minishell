/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmiasnik <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 11:26:19 by dmiasnik          #+#    #+#             */
/*   Updated: 2023/10/12 13:17:22 by dmiasnik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char	*d;
	char	*s;

	if (!dst && !src)
		return (dst);
	d = (char *)dst;
	s = (char *)src;
	if (d < s)
		return (ft_memcpy(d, s, len));
	while (len--)
		d[len] = s[len];
	return (dst);
}
