/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtiago-s <mtiago-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 16:57:31 by mtiago-s          #+#    #+#             */
/*   Updated: 2023/06/06 17:33:18 by mtiago-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	chg_dollar_loop(char **input, char **buf, int *i, int *j)
{
	while (input && input[0] && input[0][++i[0]])
	{
		if (input[0][i[0]] == '$' || j[0])
			buf[0][j[0]++] = input[0][i[0]];
		if ((j[0] && !is_alphnum(input[0][i[0] + 1]) && \
			!(j[0] == 1 && input[0][i[0] + 1] == '?')) || buf[0][1] == '?')
		{
			if (j[0] == 1)
			{
				buf[0][0] = 0;
				j[0] = 0;
			}
			else
				break ;
		}
	}
}

char	*chg_dollar(char *input, char **env)
{
	char	*buf;
	char	*new;
	char	*temp;
	int		i;
	int		j;

	i = -1;
	j = 0;
	buf = ft_calloc(1024, 1);
	chg_dollar_loop(&input, &buf, &i, &j);
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

void	expander_aux_loop(char ***division, char **env, int *i, int *k)
{
	int		j;
	char	**temp;
	char	*old;

	temp = NULL;
	temp = prepare(division[0][i[0]]);
	j = -1;
	while (temp[++j])
	{
		if (*temp[j] != '\'')
			temp[j] = chg_dollar(temp[j], env);
	}
	j = -1;
	while (temp[++j])
	{
		old = division[0][i[0] - k[0]];
		division[0][i[0] - k[0]] = ft_strjoin(old, temp[j]);
		free(old);
	}
	ft_free_matrix(&temp);
}

void	expander_aux(char ***division, char **env, int *i, int *k)
{
	while (division[0][++i[0]])
	{
		if (ft_strchr(division[0][i[0]], '\'') || \
		ft_strchr(division[0][i[0]], '\"'))
			expander_aux_loop(division, env, i, k);
		else
			division[0][i[0] - k[0]] = chg_dollar(division[0][i[0]], env);
		if (!division[0][i[0] - k[0]][0])
			free(division[0][i[0] - k[0]++]);
	}
}

char	**expander(char **division, char **env)
{
	int		i;
	int		k;

	i = -1;
	k = 0;
	expander_aux(&division, env, &i, &k);
	while (k)
		!(division[--i] = NULL) && k--;
	ft_free_matrix(&env);
	return (division);
}
