/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtiago-s <mtiago-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 16:57:31 by mtiago-s          #+#    #+#             */
/*   Updated: 2023/06/01 15:48:29 by mtiago-s         ###   ########.fr       */
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

char	*chg_dollar(char *input, char **env)
{
	char	*buf;
	char 	*new;
	char	*temp;
	int		j;
	int		i;

	
	i = -1;
	j = 0;
	buf = ft_calloc(1024, 1);
	while (input[++i])
	{
		if (input[i] == '$' || j)
			buf[j++] = input[i];
		if ((j && !is_alphnum(input[i + 1]) && !(j == 1 && input[i + 1] == '?')) || buf[1] == '?')
		{
			if (j == 1)
			{
				buf[0] = 0;
				j = 0;
			}
			else
				break ;
		}
	}
	if (!j)
	{
		free(buf);
		return (input);
	}
	temp = search_env(env, buf + 1);
	new = ft_replacement(input, buf, temp);
	if (*(buf + 1) == '?')
		free(temp);
	free(input);
	free(buf);
	return (chg_dollar(new, env));
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
		if ((str[i] == '\'' || str[i] == '\"') && (!sep || sep == str[i] || sep == -1))
			sep = (str[i]) * (sep != str[i]);
		size++;
		if ((!sep && size) || ((str[i + 1] == '\'' || str[i + 1] == '\"') && sep < 0 && size))
		{
			matrix[j++] = prepare_string(str, i, size);
			size = 0;
		}
	}
	*str = 0;
	return (matrix);
}

char	**expander(char **division, char **env)
{
	int		i;
	int		j;
	int		k;
	char	**temp;
	char	*old;

	i = -1;
	temp = NULL;
	k = 0;
	while (division[++i])
	{
		if (ft_strchr(division[i], '\'') || ft_strchr(division[i], '\"'))
		{
			temp = prepare(division[i]);
			j = -1;
			while (temp[++j])
			{
				if (*temp[j] != '\'')
					temp[j] = chg_dollar(temp[j], env);
			}
			j = -1;
			while (temp[++j])
			{
				old = division[i - k];
				division[i - k] = ft_strjoin(old, temp[j]);
				free(old);
			}
			ft_free_matrix(&temp);
		}
		else
			division[i - k] = chg_dollar(division[i], env);
		if (!division[i - k][0])
			k++;
	}
	while (k)
	{
		i--;
		division[i] = NULL;
		k--;
	}
	ft_free_matrix(&env);
	return (division);
}
