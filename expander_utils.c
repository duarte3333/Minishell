/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtiago-s <mtiago-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 16:36:58 by mtiago-s          #+#    #+#             */
/*   Updated: 2023/06/06 16:42:22 by mtiago-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_alphnum(char c)
{
	if (c >= 'a' && c <= 'z')
		return (1);
	else if (c >= 'A' && c <= 'Z')
		return (1);
	else if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}

char	*prepare_string(char *str, int i, int size)
{
	char	*res;
	int		j;

	j = 0;
	i -= size - 1;
	res = ft_calloc(size + 1, 1);
	while (str[i] && j < size)
		res[j++] = str[i++];
	return (res);
}

char	**prepare(char *str)
{
	int		i;
	int		j;
	int		size;
	int		sep;
	char	**matrix;

	i = -1;
	j = 0;
	sep = -1;
	size = 0;
	matrix = ft_calloc(1024, sizeof(char *));
	while (str[++i])
	{
		if ((str[i] == '\'' || str[i] == '\"') && \
			(!sep || sep == str[i] || sep == -1))
			sep = (str[i]) * (sep != str[i]);
		if (++size && ((!sep && size) || ((str[i + 1] == '\'' \
			|| str[i + 1] == '\"') && sep < 0 && size)))
		{
			matrix[j++] = prepare_string(str, i, size);
			size = 0;
		}
	}
	*str = 0;
	return (matrix);
}
