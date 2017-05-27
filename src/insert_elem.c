/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert_elem.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alcornea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/09 18:17:21 by alcornea          #+#    #+#             */
/*   Updated: 2017/05/09 18:59:49 by alcornea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"


void insert_elem(t_data **data, t_data *new, t_posib *option)
{
	long value;

	value = 0;
	if (*data == NULL)
		*data = new;
	else
	{
		if (option->s)
			value = new->size - (*data)->size;
		else if (option->t)
		{
			if (!(value = new->sec - (*data)->sec))
				value = new->nano_sec - (*data)->nano_sec;
		}
		if (!value)
			value = ft_strcmp((*data)->name, new->name);
		value = option->r ? value *= -1 : value;
		if (value > 0)
			insert_elem(&(*data)->left, new, option);
		else
			insert_elem(&(*data)->right, new, option);
	}
}
