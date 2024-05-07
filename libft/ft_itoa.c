/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmiasnik <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 10:13:01 by dmiasnik          #+#    #+#             */
/*   Updated: 2023/10/12 12:53:31 by dmiasnik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	numlen(int n)
{
	int	len;

	len = 0;
	if (n == 0)
		return (1);
	if (n < 0)
	{
		len++;
	}
	while (n != 0)
	{
		n = n / 10;
		len++;
	}
	return (len);
}

void	fill(char *res, int n, int len)
{
	res[len] = 0;
	if (n < 0)
	{
		res[0] = '-';
		if (n == -2147483648)
		{
			res[--len] = '8';
			n = n / 10;
		}
		n = -n;
	}
	if (n == 0)
		res[0] = '0';
	while (n != 0)
	{
		res[--len] = n % 10 + '0';
		n = n / 10;
	}
}

char	*ft_itoa(int n)
{
	char	*res;
	int		len;

	len = numlen(n);
	res = malloc(sizeof(char) * (len + 1));
	if (!res)
		return (NULL);
	fill(res, n, len);
	return (res);
}
