/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohosnedl <ohosnedl@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 13:36:08 by ohosnedl          #+#    #+#             */
/*   Updated: 2023/09/04 15:57:54 by ohosnedl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *str1, const void *str2, size_t n)
{
	unsigned char	*alt_str1;
	unsigned char	*alt_str2;
	size_t			i;

	alt_str1 = (unsigned char *)str1;
	alt_str2 = (unsigned char *)str2;
	i = 0;
	while (i < n)
	{
		if (alt_str1[i] != alt_str2[i])
			return (alt_str1[i] - alt_str2[i]);
		i++;
	}
	return (0);
}
