/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohosnedl <ohosnedl@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 14:54:37 by ohosnedl          #+#    #+#             */
/*   Updated: 2023/08/28 12:20:18 by ohosnedl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	char	*alt_s;
	char	alt_c;

	i = ft_strlen(s);
	alt_s = (char *)s;
	alt_c = (char)c;
	if (!ft_isascii(alt_c))
		return (NULL);
	while (i != 0 && alt_s[i] != alt_c)
		i--;
	if (alt_s[i] == alt_c)
		return (alt_s + i);
	return (NULL);
}
