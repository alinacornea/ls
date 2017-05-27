/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alcornea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/06 17:40:15 by alcornea          #+#    #+#             */
/*   Updated: 2017/05/16 21:37:14 by kmurray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void print_tree(t_data *data, t_posib *option)
{
		if (data->left)
			print_tree(data->left, option);
		if (option->l)
		{
			printf("%-10s %3s %-9s %-7s %6s %.12s %s",
			data->mode, data->nlink, data->uid, data->grp, \
			data->size, data->date, data->name);
			if (data->link != NULL)
				printf(" -> %s", data->link);
			printf("\n");
		}
		else
			printf("%s\n", data->name);
		if (data->right)
			print_tree(data->right, option);
}

void print(t_data **data, t_posib *option)
{
	t_data *tmp;

 	if(option->l)
	{
		ft_putstr("total ");
		ft_putnbr(option->total);
		ft_putchar('\n');
		option->total = 0;
	}
	tmp = *data;
	while(tmp)
	{
			print_tree(tmp, option);
		tmp = tmp->next;
	}
}
