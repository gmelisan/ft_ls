/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_spdevnum.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmelisan <gmelisan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 17:21:39 by gmelisan          #+#    #+#             */
/*   Updated: 2019/02/26 17:21:59 by gmelisan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/*
** Major/minor numbers:
**
** https://stackoverflow.com/questions/4309882/
** device-number-in-stat-command-output
**
** https://stackoverflow.com/questions/35392291/
** how-to-convert-between-a-dev-t-and-major-minor-device-numbers
*/

int		get_major(struct stat st)
{
	return ((int)(((t_uint)(st.st_rdev) >> 24) & 0xFF));
}

int		get_minor(struct stat st)
{
	return ((int)((st.st_rdev) & 0xFF));
}
