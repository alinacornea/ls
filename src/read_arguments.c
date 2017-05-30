/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_arguments.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alcornea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/05 15:53:14 by alcornea          #+#    #+#             */
/*   Updated: 2017/05/16 19:09:45 by kmurray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	ft_strskipjoin(char **s1, char **s2)
{
	char *tmp;

	tmp = ft_strjoin(*s1, *s2);
	ft_strdel(s1);
	*s1 = ft_strdup(tmp);
	ft_strdel(&tmp);
}

void	set_option(char *str, t_posib *option)
{
	int i;

	i = 0;
	check_str(str);
	check_arg(*option);
	while (str[i])
	{
		if (str[i] == 'R')
			option->rec = 1;
		if (str[i] == 'a')
			option->a = 1;
		if (str[i] == 'l')
			option->l = 1;
		if (str[i] == 'r')
			option->r = 1;
		if (str[i] == 't')
			option->t = 1;
		if (str[i] == 'S')
			option->s = 1;
		if (str[i] == '1')
			option->one = 1;
		i++;
	}
}

char	*get_rid_of_dash(int num, char **av, int *ac)
{
	int		i;
	char	*str;
	char	*tmp;

	i = 1;
	str = ft_strnew(*ac);
	while (i < num && av[i][0] == '-' && av[i][1] != '\0')
	{
		if (ft_strcmp(av[i], "--") != 0)
		{
			tmp = ft_strdup(&av[i][1]);
			ft_strskipjoin(&str, &tmp);
			free(tmp);
		}
		else
		{
			(*ac)--;
			break ;
		}
		i++;
		(*ac)--;
	}
	(*ac)--;
	return (str);
}

void	get_arg_sec(int i, int num, t_posib *option, char **av)
{
	int j;

	j = 0;
	while (i < num)
	{
		option->path[j] = ft_strdup(av[i]);
		j++;
		i++;
		option->nb_path++;
	}
	option->path[j] = NULL;
}

char	*get_argument(int ac, char **av, t_posib *option)
{
	int		i;
	int		num;
	char	*str;

	num = ac;
	str = get_rid_of_dash(num, av, &ac);
	if ((option->path = (char **)malloc(sizeof(char *) *
	(((ac) == 0 ? 1 : ac) + 1))) == NULL)
		ft_error(1, "get argument");
	if (ac < 1)
	{
		option->path[0] = ft_strdup(".");
		option->path[1] = NULL;
		option->nb_path++;
		return (str);
	}
	i = num - ac;
	get_arg_sec(i, num, option, av);
	return (str);
}
