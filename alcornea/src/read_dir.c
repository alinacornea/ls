/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_dir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alcornea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/05 19:01:04 by alcornea          #+#    #+#             */
/*   Updated: 2017/05/16 21:42:51 by kmurray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	get_total_file(char *bpath, t_data *data)
{
	struct stat st;

	if (lstat(bpath, &st) == -1)
	{
		perror("lstat error");
		exit(1);
	}
	data->mode = check_permissions(st.st_mode);
	get_time(data, st);
	check_time(&data->sec, data);
	get_nlink(data, st.st_nlink);
	get_owner(data, st.st_uid);
	get_group(data, st.st_gid);
	get_size(data, st.st_size);
	if (data->mode[0] == 'l')
		get_link(data, bpath);
}

t_data	*create_file(char *path, t_posib *option, t_data *data)
{
	t_data *new;

	new = NULL;
	new = (t_data*)malloc(sizeof(t_data));
	init_elements(new);
	new->name = path;
	get_total_file(path, new);
	insert_elem(&data, new, option);
	return (data);
}

int		stat_dir(char *path)
{
	struct stat st;

	if (stat(path, &st) == -1)
	{
		if (lstat(path, &st) == -1)
		{
			if (errno == ENOTDIR)
				return (0);
		}
	}
	else if (S_ISDIR(st.st_mode))
		return (1);
	else if (S_ISLNK(st.st_mode))
		return (2);
	else if (S_ISREG(st.st_mode))
		return (3);
	return (0);
}

t_data	*create_node(char *bpath, t_posib *option, DIR *dir, t_data *data)
{
	int				tmp;
	t_data			*new;
	struct dirent	*dp;

	tmp = 0;
	new = NULL;
	while ((dp = readdir(dir)) != NULL)
	{
		if (!option->a && dp->d_name[0] == '.')
			continue ;
		if (!(new = ft_memalloc(sizeof(t_data))))
		{
			perror("error in memory allocation");
			exit(1);
		}
		init_elements(new);
		if ((new->name = ft_strdup(dp->d_name)) == NULL)
			exit(ft_error(1, dp->d_name));
		if ((tmp = get_total(bpath, new, option)) == -1)
			continue;
		option->total += tmp;
		insert_elem(&data, new, option);
	}
	closedir(dir);
	return (data);
}

t_data	*read_directories(char *bpath, char *path, t_posib *option)
{
	DIR		*dir;
	t_data	*data;

	data = NULL;
	if ((dir = opendir(bpath)) == NULL)
	{
		if (errno == ENOENT || errno == ENOTDIR)
		{
			if (stat_dir(path) == 3)
			{
				data = create_file(path, option, data);
				print_tree(data, option);
				free_tree(data);
				ft_strdel(&bpath);
				return (NULL);
			}
		}
		ft_error(1, path);
		return (NULL);
	}
	data = create_node(bpath, option, dir, data);
	ft_strdel(&bpath);
	return (data);
}
