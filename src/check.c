/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alcornea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/05 15:53:14 by alcornea          #+#    #+#             */
/*   Updated: 2017/05/16 19:09:45 by kmurray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void free_tree(t_data *data)
{
	if (data)
	{
		free_tree(data->left);
		ft_strdel(&data->name);
		ft_strdel(&data->mode);
		ft_strdel(&data->uid);
		ft_strdel(&data->grp);
		ft_strdel(&data->link);
		ft_strdel(&data->date);
		ft_strdel(&data->size);
		ft_strdel(&data->nlink);
		free_tree(data->right);
		free(data);
		data = NULL;
	}
}

int error(int nb, char *str)
{
	if (nb == 1)
	{
		ft_putstr_fd("ft_ls: ", 2);
		perror(str);
	}
	else if (nb == 2)
	{
		ft_putstr_fd("ft_ls: illegal option -- ", 2);
		ft_putchar_fd(str[0], 2);
		ft_putchar('\n');
		ft_putstr_fd("usage: ft_ls [-RSalrt] [file ...]", 2);
		ft_putendl("");
	}
	return (-1);
}

int check_str(char *str)
{
	int i;
	char *tmp;

	i = 0;
	tmp = "RSatlr";
	while (str[i])
	{
		if (ft_strchr(tmp, str[i]) == NULL)
			exit(error(2, &(str[i])));
		i++;
	}
	return (0);
}

int check_arg(t_posib option)
{
	int i;

	i = 0;
	while (i < option.nb_path)
	{
		if (option.path[i][0] == '\0')
		{
			errno = ENOENT;
			exit(error(1, "open"));
		}
		i++;
	}
	return (0);
}
