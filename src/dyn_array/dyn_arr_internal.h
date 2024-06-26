/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dyn_arr_internal.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alletond <alletond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 16:36:57 by alletond          #+#    #+#             */
/*   Updated: 2024/03/26 16:36:58 by alletond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DYN_ARR_INTERNAL_H
# define DYN_ARR_INTERNAL_H

# include <stdlib.h>

# define DYN_ARR_RESIZE_FACTOR 2
# define DYN_ARR_CAPACITY 8

struct s_dyn_arr
{
	size_t	capacity;
	size_t	len;
	void	**elements;
};

int	dyn_arr_resize(t_dyn_arr *arr);

#endif