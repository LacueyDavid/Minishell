/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ltoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdenis <jdenis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 16:28:30 by jdenis            #+#    #+#             */
/*   Updated: 2024/02/07 16:34:01 by jdenis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	size_of_n(long long n)
{
	size_t	size;

	size = 0;
	if (n == 0)
		size = 1;
	while (n > 0)
	{
		n /= 10;
		size++;
	}
	return (size);
}

static void	str_filler(int sign, size_t size, char *str, long long long_n)
{
	if (sign < 0)
	{
		while (size > 1)
		{
			str[size - 1] = long_n % 10 + '0';
			size--;
			long_n /= 10;
		}
		str[0] = '-';
	}
	else
	{
		while (size > 0)
		{
			str[size - 1] = long_n % 10 + '0';
			size--;
			long_n /= 10;
		}
	}
}

char	*ft_ltoa(long n)
{
	char	*str;
	size_t	size;
	int		sign;
	long	long_n;

	str = NULL;
	size = 0;
	sign = 1;
	long_n = (long long)n;
	if (long_n < 0)
	{
		size++;
		sign = -1;
		long_n = -long_n;
	}
	size += size_of_n(long_n);
	str = ft_calloc(size + 1, 1);
	if (str == NULL)
		return (NULL);
	str_filler(sign, size, str, long_n);
	return (str);
}
