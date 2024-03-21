/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohosnedl <ohosnedl@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 15:13:36 by ohosnedl          #+#    #+#             */
/*   Updated: 2023/08/29 10:55:25 by ohosnedl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_count_digits(int n)
{
	size_t	i;

	i = 1;
	while (n / 10)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	char	*new_str;
	size_t	num_digits;
	int		num;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	num = n;
	num_digits = ft_count_digits(n);
	if (n < 0)
	{
		num *= -1;
		num_digits++;
	}
	new_str = (char *)malloc(sizeof(char) * num_digits + 1);
	if (!new_str)
		return (NULL);
	*(new_str + num_digits) = '\0';
	while (num_digits--)
	{
		*(new_str + num_digits) = num % 10 + '0';
		num = num / 10;
	}
	if (n < 0)
		*(new_str + 0) = '-';
	return (new_str);
}
