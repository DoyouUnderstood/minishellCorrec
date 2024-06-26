/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_list_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alletond <alletond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 18:10:37 by alletond          #+#    #+#             */
/*   Updated: 2024/03/26 18:10:38 by alletond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "word_list.h"

#include <stdlib.h>

#include "libft.h"

/** Returns the last node of the word list,
 * or NULL for an empty list.
*/
t_word_list	*word_list_last(t_word_list *list)
{
	if (!list)
		return (NULL);
	while (list->next)
		list = list->next;
	return (list);
}

/** Returns the number of elements in a word list
 * 
*/
int	word_list_len(t_word_list *list)
{
	int	i;

	i = 0;
	while (list)
	{
		i++;
		list = list->next;
	}
	return (i);
}

/** Returns the node at the given index,
 * or NULL if the index is out of bounds.
 * 
*/
t_word_list	*word_list_at(t_word_list *list, size_t index)
{
	size_t	i;

	i = 0;
	while (i < index && list)
	{
		i++;
		list = list->next;
	}
	return (list);
}

/** Appends addition to list
 * 
*/
void	word_list_append(t_word_list **list, t_word_list *addition)
{
	if (!addition)
		return ;
	if (!*list)
		*list = addition;
	else
		word_list_last(*list)->next = addition;
}
