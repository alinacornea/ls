/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alcornea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/18 20:26:43 by alcornea          #+#    #+#             */
/*   Updated: 2017/05/08 18:57:47 by alcornea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	init_args(t_posib *option)
{
	option->path = NULL;
	option->a = 0;
	option->t = 0;
	option->l = 0;
	option->r = 0;
	option->s = 0;
	option->one = 0;
	option->rec = 0;
	option->nb_path = 0;
	option->total = 0;
}

void	init_elements(t_data *elem)
{
	elem->sec = 0;
	elem->nano_sec = 0;
	elem->size = NULL;
	elem->date = NULL;
	elem->name = NULL;
	elem->mode = NULL;
	elem->nlink = NULL;
	elem->uid = NULL;
	elem->grp = NULL;
	elem->next = NULL;
	elem->right = NULL;
	elem->left = NULL;
	elem->link = NULL;
}

int		main(int argc, char **argv)
{
	char	*str;
	t_posib	option;

	init_args(&option);
	str = get_argument(argc, argv, &option);
	set_option(str, &option);
	if (option.nb_path > 1)
		sort_path(&(option.path), option.nb_path, option.r);
	list(&option);
	ft_strdel(&str);
	return (0);
}
