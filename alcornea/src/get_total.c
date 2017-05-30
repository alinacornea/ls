/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_total.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alcornea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/06 18:29:02 by alcornea          #+#    #+#             */
/*   Updated: 2017/05/16 18:47:44 by kmurray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	check_time(time_t *ftime, t_data *data)
{
	char	*tmp;
	time_t	now;

	data->date = ft_strnew(21);
	tmp = ctime(ftime);
	if (time(&now) - *ftime < 15778463)
		data->date = ft_strncat(data->date, tmp + 4, 12);
	else
	{
		data->date = ft_strncat(data->date, tmp + 4, 7);
		data->date = ft_strcat(data->date, " ");
		data->date = ft_strncat(data->date, tmp + 20, 4);
	}
}

void	get_time(t_data *data, struct stat st)
{
	data->sec = st.st_mtime;
	data->nano_sec = st.st_mtimespec.tv_nsec;
}

size_t	get_total(char *path, t_data *data, t_posib *option)
{
	struct stat	st;
	char		*tmp;

	tmp = ft_strjoin(path, data->name);
	if (lstat(tmp, &st) == -1)
	{
		perror("lstat error");
		return (-1);
	}
	data->mode = check_permissions(st.st_mode);
	get_time(data, st);
	check_time(&data->sec, data);
	get_nlink(data, st.st_nlink);
	get_owner(data, st.st_uid);
	get_group(data, st.st_gid);
	get_size(data, st.st_size);
	if (data->mode[0] == 'l')
		get_link(data, path);
	ft_strdel(&tmp);
	if (data->name[0] != '.' || option->a)
		return (st.st_blocks);
	else
		return (-1);
}
