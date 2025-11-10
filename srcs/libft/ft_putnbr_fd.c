/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlacuey <dlacuey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 18:32:20 by dlacuey           #+#    #+#             */
/*   Updated: 2023/05/12 18:17:36 by dlacuey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	long	long_n;
	size_t	div;
	size_t	mod;

	long_n = (long)n;
	if (long_n < 0)
	{
		long_n = -long_n;
		ft_putchar_fd('-', fd);
	}
	div = long_n / 10;
	mod = long_n % 10;
	if (div > 0)
		ft_putnbr_fd(div, fd);
	ft_putchar_fd(mod + '0', fd);
}
