/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlevinsc <dlevinsc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 14:49:27 by dlevinsc          #+#    #+#             */
/*   Updated: 2023/11/05 14:49:36 by dlevinsc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*res;
	t_list	*new;
	void	*set;

	res = NULL;
	while (lst)
	{
		set = f(lst->content);
		new = ft_lstnew(set);
		if (!new)
		{
			del(set);
			ft_lstclear(&res, (*del));
			return (res);
		}
		ft_lstadd_back(&res, new);
		lst = lst->next;
	}
	return (res);
}
