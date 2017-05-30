/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alcornea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/18 20:27:40 by alcornea          #+#    #+#             */
/*   Updated: 2017/04/18 20:28:50 by alcornea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include <stdio.h>
# include <stdlib.h>
# include "libft.h"
# include <dirent.h>
# include <sys/errno.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <grp.h>
# include <uuid/uuid.h>
# include <sys/types.h>
# include <pwd.h>
# include <time.h>

typedef struct		s_posib
{
	char			a;
	char			l;
	char			r;
	char			t;
	char			s;
	char			rec;
	char			one;
	char			**path;
	char			*p_name;
	int				nb_path;
	size_t			total;
}					t_posib;

typedef struct		s_data
{
	char			*name;
	char			*mode;
	char			*nlink;
	char			*uid;
	char			*grp;
	char			*size;
	char			*link;
	char			*date;
	long			nano_sec;
	time_t			sec;
	struct stat		st;
	struct s_data	*next;
	struct s_data	*left;
	struct s_data	*right;
}					t_data;

char				*get_argument(int ac, char **av, t_posib *option);
void				set_option(char *str, t_posib *option);
void				init_elements(t_data *elem);
void				list(t_posib *option);
t_data				*read_directories(char *bpath, char *path, t_posib *option);
size_t				get_total(char *path, t_data *data, t_posib *option);
char				*check_permissions(mode_t mode);
void				insert_elem(t_data **idata, t_data *new, t_posib *option);
int					list_recursive(t_posib *option, char *path, int i);
void				print(t_data **data, t_posib *option);
void				print_tree(t_data *data, t_posib *option);
void				sort_path(char ***str, int size, char r);
int					stat_dir(char *path);
void				get_nlink(t_data *data, nlink_t nlink);
void				get_owner(t_data *data, uid_t uid);
void				get_group(t_data *data, gid_t git);
void				get_size(t_data *data, off_t s);
void				get_link(t_data *data, char *path);
void				check_time(time_t *ftime, t_data *data);
void				get_time(t_data *data, struct stat st);
t_data				*create_file(char *path, t_posib *option, t_data *data);
int					ft_error(int nb, char *str);
int					check_str(char *str);
int					check_arg(t_posib option);
void				free_tree(t_data *data);

#endif
