/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohosnedl <ohosnedl@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 16:31:19 by ohosnedl          #+#    #+#             */
/*   Updated: 2023/08/28 11:44:38 by ohosnedl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *str, int c)
{
	char	alt_c;
	char	*alt_str;
	int		i;

	i = 0;
	alt_str = (char *)str;
	alt_c = (char)c;
	if (!ft_isascii(alt_c))
		return (NULL);
	while (alt_str[i] != '\0' && alt_str[i] != alt_c)
		i++;
	if (alt_str[i] == alt_c)
		return (alt_str + i);
	return (NULL);
}
