/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memahote <memahote@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 14:46:41 by memahote          #+#    #+#             */
/*   Updated: 2022/11/18 13:05:15 by memahote         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	intsize(int n)
{
	int	size;

	size = 0;
	if (n == 0)
		return (1);
	if (n == -2147483648)
		return (11);
	if (n < 0)
	{
		size++;
		n *= -1;
	}
	while (n > 0)
	{
		n /= 10;
		size++;
	}
	return (size);
}

char	*ft_itoa(int n)
{
	char	*nb;
	long	n2;
	int		len;

	len = intsize(n);
	nb = malloc (sizeof(char) * (len + 1));
	if (!nb)
		return (NULL);
	nb[len--] = '\0';
	n2 = n;
	if (n2 == 0)
		nb[0] = '0';
	else if (n2 < 0)
	{
		n2 *= -1;
		nb[0] = '-';
	}
	while (n2)
	{
		nb[len--] = n2 % 10 + '0';
		n2 /= 10;
	}
	return (nb);
}
