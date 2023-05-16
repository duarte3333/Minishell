/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtiago-s <mtiago-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 16:25:18 by mtiago-s          #+#    #+#             */
/*   Updated: 2023/05/09 18:54:59 by mtiago-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while ((s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0') && i < n - 1)
		i++;
	if (n == 0)
		return (0);
	else
		return ((unsigned char) s1[i] - (unsigned char) s2[i]);
}
