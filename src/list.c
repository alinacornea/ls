/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alcornea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/05 19:01:14 by alcornea          #+#    #+#             */
/*   Updated: 2017/05/16 21:25:58 by kmurray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char		*check_path(char *str)
{
	int		ret;
	char	buf[1024];

	ft_memset(buf, 0, sizeof(buf));
	if ((str[0] != '/' && str[1] != '/') && (str[0] != '.'))
		ft_strcpy(buf, "./");
	if ((ret = stat_dir(str) == 0))
		return (str);
	else
	{
		ft_strcat(buf, str);
		ft_strcat(buf, "/");
	}
	return (ft_strdup(buf));
}

static int	list_read(t_posib *option, char *path, t_data **data, int i)
{
	char	*bpath;
	int		ret;

	bpath = NULL;
	ret = stat_dir(path);
	if (((option->rec && i > 0) || option->nb_path > 1) && ret != 3)
	{
		if (i > 0)
			ft_putchar('\n');
		ft_putstr(path);
		ft_putstr(":\n");
	}
	bpath = check_path(path);
	if ((*data = read_directories(bpath, path, option)) == NULL)
		return (0);
	print(data, option);
	return (1);
}

void		recursive(t_data *elem, t_posib *option, char *path, int i)
{
	char	*tmp;
	char	*tmp2;

	if (elem->left)
		recursive(elem->left, option, path, i);
	if ((option->a || elem->name[0] != '.')
	&& ft_strcmp(elem->name, "..") != 0 &&
		ft_strcmp(elem->name, ".") != 0)
	{
		if (elem->mode[0] == 'd')
		{
			tmp = ft_strjoin(path, "/");
			tmp2 = ft_strjoin(tmp, elem->name);
			ft_strdel(&tmp);
			list_recursive(option, tmp2, i + 1);
			ft_strdel(&tmp2);
		}
	}
	if (elem->right)
		recursive(elem->right, option, path, i);
}

int			list_recursive(t_posib *option, char *path, int i)
{
	t_data *data;
	t_data *elem;

	data = NULL;
	if (list_read(option, path, &data, i) == 0)
		return (0);
	elem = data;
	if (!option->rec)
		free_tree(data);
	if (option->rec && elem != NULL)
	{
		recursive(elem, option, path, i);
		free_tree(elem);
	}
	return (0);
}

void		list(t_posib *option)
{
	int		i;
	t_data	*data;
	char	*tmp;

	i = 0;
	data = NULL;
	tmp = NULL;
	while (i < option->nb_path)
	{
		if (option->path[i] != NULL)
			list_recursive(option, option->path[i], i);
		i++;
	}
}
