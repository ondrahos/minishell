/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohosnedl <ohosnedl@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 13:21:43 by ohosnedl          #+#    #+#             */
/*   Updated: 2023/09/05 15:32:57 by ohosnedl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isalnum(int c)
{
	if ((c <= 'Z' && c >= 'A') || (c <= 'z' && c >= 'a')
		|| (c >= '0' && c <= '9'))
		return (1);
	return (0);
}
