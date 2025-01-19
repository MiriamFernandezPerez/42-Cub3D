/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mirifern <mirifern@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 23:32:02 by mirifern          #+#    #+#             */
/*   Updated: 2024/02/01 00:15:33 by mirifern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new;
	t_list	*new_e;
	void	*content;

	if (!lst || !f)
		return (NULL);
	new = 0;
	while (lst)
	{
		content = f(lst->content);
		if (content)
			new_e = ft_lstnew(content);
		if (!content || !new_e)
		{
			free (content);
			ft_lstclear (&new, del);
			return (NULL);
		}
		ft_lstadd_back(&new, new_e);
		lst = lst->next;
	}
	return (new);
}
