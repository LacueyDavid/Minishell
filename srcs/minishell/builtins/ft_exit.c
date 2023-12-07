/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 12:27:18 by marvin            #+#    #+#             */
/*   Updated: 2023/12/04 12:27:18 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "libft.h"

extern int	exit_status;

int ft_exit(char *status) 
{
    if (!status || ft_atoi(status + 5) == 0)
        exit_status = 0;
    else
        exit_status = ft_atoi(status + 5);
    printf("exit WeShell\n");
    return(exit_status);
}
