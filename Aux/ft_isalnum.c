/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsa-mora <dsa-mora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 18:45:12 by dsa-mora          #+#    #+#             */
/*   Updated: 2023/06/06 16:56:57 by dsa-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/* Verifica se toda a string tem elementos char 
que sejam alfabumericos */
int	ft_str_islanum(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		if (!ft_isalnum(str[i]))
			return (0);
		i++;
	}
	return (1);
}

/* Verica se um elemento e alfanumerico */
int	ft_isalnum(int i)
{
	if ((i >= '0' && i <= '9'))
		return (1);
	else if ((i >= 'a' && i <= 'z') || (i >= 'A' && i <= 'Z'))
		return (1);
	return (0);
}

/* Verifica se um elemento e um digito */
int	ft_isdigit(int i)
{
	if ((i >= '0' && i <= '9'))
		return (1);
	return (0);
}
