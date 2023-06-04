/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duarte33 <duarte33@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 10:05:58 by dsa-mora          #+#    #+#             */
/*   Updated: 2023/06/04 20:22:47 by duarte33         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/* Esta funcao recebe duas strings e faz a concatenação de ambas
ou seja, junta-as */
char	*ft_strjoin(char *s1, char const *s2)
{
	int		size_concat;
	char	*concat;
	int		i;
	int		j;

	i = -1;
	j = -1;
	size_concat = ft_strlen(s1) + ft_strlen(s2);
	concat = (char *)ft_calloc((size_concat + 1), sizeof(char));
	while (s1[++i])
		concat[i] = s1[i];
	while (s2[++j])
		concat[i + j] = s2[j];
	return (concat);
}
