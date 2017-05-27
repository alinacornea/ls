/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_info.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alcornea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/06 18:29:02 by alcornea          #+#    #+#             */
/*   Updated: 2017/05/16 18:47:44 by kmurray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void get_nlink(t_data *data, nlink_t nlink)
{
  char *tmp;

  tmp = ft_itoa(nlink);
  data->nlink = ft_strdup(tmp);
  ft_strdel(&tmp);
}

void get_owner(t_data *data, uid_t uid)
{
  char *tmp;
  struct passwd *pass;

  if ((pass = getpwuid(uid)) == NULL)
    tmp = ft_itoa(uid);
  else
    tmp = ft_strdup(pass->pw_name);
  data->uid = ft_strdup(tmp);
  ft_strdel(&tmp);
}

void get_group(t_data *data, gid_t git)
{
  char *tmp;
  struct group *grp;

  if ((grp = getgrgid(git)) == NULL)
    tmp = ft_itoa(git);
  else
    tmp = ft_strdup(grp->gr_name);
  data->grp = ft_strdup(tmp);
  ft_strdel(&tmp);
}

void get_size(t_data *data, off_t s)
{
  char *tmp;

  tmp = ft_itoa(s);
  data->size = ft_strdup(tmp);
  ft_strdel(&tmp);
}

void get_link(t_data *data, char *path)
{
  int ret;
  char *tmp;
  char buff[BUFF_SIZE];

  tmp = ft_strjoin(path, data->name);
  if ((ret = readlink(tmp, buff, BUFF_SIZE)) == -1)
    error(1, path);
  buff[ret] = '\0';
  data->link = ft_strdup(buff);
  ft_strdel(&tmp);
}
