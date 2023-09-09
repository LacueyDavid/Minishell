/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlacuey <dlacuey@student42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 18:31:14 by dlacuey           #+#    #+#             */
/*   Updated: 2023/08/08 17:05:50 by dlacuey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *newlist)
{
	t_list	*traveler;

	traveler = NULL;
	if (lst != NULL)
	{
		if (*lst == NULL)
			*lst = newlist;
		else
		{
			traveler = *lst;
			while (traveler->next)
				traveler = traveler->next;
			traveler->next = newlist;
		}
	}
}
