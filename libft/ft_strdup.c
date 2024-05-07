/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmiasnik <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 15:54:59 by dmiasnik          #+#    #+#             */
/*   Updated: 2023/10/12 09:56:07 by dmiasnik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*res;
	int		len;

	len = ft_strlen(s1) + 1;
	res = malloc(sizeof(char) * len);
	if (res == NULL)
		return (NULL);
	ft_memcpy(res, s1, len);
	return (res);
}
