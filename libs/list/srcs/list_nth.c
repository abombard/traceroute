/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_nth.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abombard <abombard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/01 00:00:21 by abombard          #+#    #+#             */
/*   Updated: 2016/01/01 00:00:42 by abombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list.h"

t_list	*list_nth(const t_list *head, const int index)
{
	t_list		*tmp;
	int			i;

	tmp = (t_list *)head;
	i = 0;
	if (index > 0)
	{
		while (i < index)
		{
			tmp = tmp->next;
			i++;
		}
	}
	else
	{
		while (i > index)
		{
			tmp = tmp->prev;
			i--;
		}
	}
	return (tmp);
}
