/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_longest.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmelisan <gmelisan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 17:23:05 by gmelisan          #+#    #+#             */
/*   Updated: 2019/02/26 17:27:49 by gmelisan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/*
**            1         2
**  012345678901234567890123456
** "Wed Jun 30 21:49:08 1993\n" ->
** year_flag ? "Jun 30 21:49" : "Jun 30  1993"
*/

static char			*convert_time(char *str, int year_flag)
{
	char	*res;
	int		i;
	int		len;

	res = ft_strnew(20);
	ft_memcpy(res, str + 4, 6);
	res[6] = ' ';
	if (year_flag)
	{
		i = 19;
		while (str[i] == ' ')
			i++;
		len = 0;
		while (str[i + len] != '\n' && str[i + len])
			len++;
		ft_memcpy(res + 7, str + i - 1, len + 1);
	}
	else
		ft_memcpy(res + 7, str + 11, 5);
	return (res);
}

static void			update_longest(t_name *names, int i,
										struct s_longest *longest)
{
	int		len;
	time_t	curtime;

	if (names[i].st.st_nlink > (t_ulint)longest->link)
		longest->link = names[i].st.st_nlink;
	if (names[i].st.st_size > longest->bytes)
		longest->bytes = names[i].st.st_size;
	curtime = time(NULL);
	if (ft_abs(curtime - names[i].st.st_mtime) < YEAR_BORDER)
		names[i].timestr = convert_time(ctime(&names[i].st.st_mtime), 0);
	else
		names[i].timestr = convert_time(ctime(&names[i].st.st_mtime), 1);
	len = ft_strlen(names[i].pw_name);
	if (len > longest->owner)
		longest->owner = len;
	len = ft_strlen(names[i].gr_name);
	if (len > longest->group)
		longest->group = len;
	if (is_device(names[i].st) && (get_major(names[i].st) > longest->sp_major))
		longest->sp_major = get_major(names[i].st);
	if (is_device(names[i].st) && (get_minor(names[i].st) > longest->sp_minor))
		longest->sp_minor = get_minor(names[i].st);
}

struct s_longest	get_longest(t_name *names, struct s_options options,
								int *total)
{
	int					i;
	struct s_longest	longest;

	bzero((void *)&longest, sizeof(longest));
	i = -1;
	*total = 0;
	while (names[++i].name)
	{
		if (!(options.all || names[i].name[0] != '.'))
			continue ;
		update_longest(names, i, &longest);
		*total += names[i].st.st_blocks;
	}
	longest.link = ft_cntdigits(longest.link, 10);
	longest.bytes = ft_cntdigits(longest.bytes, 10);
	if (longest.sp_major)
		longest.sp_major = ft_cntdigits(longest.sp_major, 10);
	if (longest.sp_minor)
		longest.sp_minor = ft_cntdigits(longest.sp_minor, 10);
	if (longest.sp_major || longest.sp_minor)
		longest.bytes = 9;
	return (longest);
}
