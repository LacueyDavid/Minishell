/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlacuey <dlacuey@student42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 19:00:24 by dlacuey           #+#    #+#             */
/*   Updated: 2023/05/12 19:57:37 by dlacuey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	if (lst && del)
	{
		if (*lst)
			if ((*lst)->next)
				ft_lstclear(&(*lst)->next, del);
		del((*lst)->content);
		free(*lst);
		*lst = NULL;
	}
}
