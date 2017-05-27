/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_permissions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alcornea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/08 14:48:50 by alcornea          #+#    #+#             */
/*   Updated: 2017/05/08 16:01:41 by alcornea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char check_type(mode_t mode)
{
  char perm;

  perm = '-';
  if (S_ISDIR(mode))
    perm = 'd';
  else if (S_ISREG(mode))
    perm = '-';
  else if (S_ISLNK(mode))
    perm = 'l';
  else if (S_ISBLK(mode))
    perm = 'b';
  else if (S_ISCHR(mode))
    perm = 'c';
  else if (S_ISSOCK(mode))
    perm = 's';
  else if (S_ISFIFO(mode))
    perm = 'p';
  return (perm);
}

char *check_permissions(mode_t mode)
{
  char *perm;

  perm = ft_strnew(10);
  perm = ft_memset(perm, '-', 10);
  perm[0] = check_type(mode);
  if (S_IRUSR & mode)
    perm[1] = 'r';
  if (S_IWUSR & mode)
    perm[2] = 'w';
  if (S_IXUSR & mode)
    perm[3] = 'x';
  if (S_IRGRP & mode)
    perm[4] = 'r';
  if (S_IWGRP & mode)
    perm[5] = 'w';
  if (S_IXGRP & mode)
    perm[6] = 'x';
  if (S_IROTH & mode)
    perm[7] = 'r';
  if (S_IWOTH & mode)
    perm[8] = 'w';
  if (S_IXOTH & mode)
    perm[9] = 'x';
  return(perm);
}
