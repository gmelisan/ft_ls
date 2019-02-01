/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmelisan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/17 16:41:05 by gmelisan          #+#    #+#             */
/*   Updated: 2018/12/19 16:36:23 by gmelisan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

void	*ft_realloc(void **ptr, size_t oldsize, size_t newsize)
{
	void	*ret;

	ret = ft_memalloc(newsize);
	if (!ret)
		return (NULL);
	if (ptr)
	{
		ft_memcpy(ret, *ptr, oldsize < newsize ? oldsize : newsize);
		free(*ptr);
		*ptr = ret;
	}
	return (ret);
}
