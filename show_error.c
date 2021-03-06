/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmelisan <gmelisan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/05 13:50:13 by gmelisan          #+#    #+#             */
/*   Updated: 2019/02/26 17:53:24 by gmelisan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	error_illegal_option(char *ft_ls_name, char option)
{
	ft_printf("%s: illegal option -- %c\n", ft_ls_name, option);
	ft_printf("usage: ft_ls [-Ralrt] [file ...]\n");
	exit(1);
}

void	error_common(char *fod)
{
	char *out;

	out = ft_strjoin("ft_ls: ", fod);
	perror(out);
	free(out);
}
