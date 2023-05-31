/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtiago-s <mtiago-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 16:57:31 by mtiago-s          #+#    #+#             */
/*   Updated: 2023/05/31 20:36:10 by mtiago-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// char	*get_dollar_word(char *str, char **env) // se calhar esta funcao tem de fazer ja o search path para ver se e suposto retornar essa palavra
// {
// 	int		i;
// 	int		j;
// 	char	*res;

// 	i = -1;
// 	while (str[++i])
// 	{
// 		if (i && str[i - 1] == '$' && str[i] != 32 && str[i] != '$')
// 		{
// 			j = 0;
// 			while (str[i + j] && str[i + j] != 32 && str[i + j] != '$')
// 				j++;
// 			if (!j)
// 				return (NULL);
// 			res = ft_calloc(j + 1, 1);
// 			while (--j != -1 && str[i + j])
// 				res[j] = str[i + j];
// 			if (search_env(env, res))
// 				return (res);
// 			else
// 				free(res);
// 		}
// 	}
// 	return (NULL);
// }

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

// int	how_many_dollars(char *str, char **env) // contagem de quantos $ serao subsituidos
// {
// 	int		res;
// 	int		i;
// 	char	*temp;

// 	i = -1;
// 	res = 0;
// 	temp = NULL;
// 	while (str[++i])
// 	{
// 		if (str[i] == '$' && str[i + 1] && str[i + 1] != 32 && str[i + 1] != '$')
// 		{
// 			temp = get_dollar_word(&str[i], env);
// 			if (temp && !ft_strncmp(&str[i + 1], temp, ft_strlen(temp)) && search_env(env, temp))
// 				res++;
// 			if (temp)
// 				free(temp);
// 			temp = NULL;
// 		}
// 	}
// 	return (res);
// }

// void	chg_dollar_loop(int *i, char **temp, char *res, int flag)
// {
// 	while (res[++i[0]]) // percorrer string anterior
// 	{
// 		if (res[i[0]] == '$' && !ft_strncmp(&res[i[0] + 1], temp[2], ft_strlen(temp[2])) &&!flag++ && ++i[0])
// 		{
// 			while (temp[1][i[2]]) //copiar para string nova a parte que e para substituir
// 				temp[0][i[1]++] = temp[1][i[2]++];
// 			while (res[i[0] + 1] && res[i[0] + 1] != 32 && res[i[0] + 1] != '$') // avancar a palarva ex $PATH palavra = PATH
// 				i[0]++;
// 		}
// 		else // copiar o resto
// 			temp[0][i[1]++] = res[i[0]];
// 	}
// }

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
			break ;
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

char	**expander(char **divison, char **env)
{
	int		i;
	int		j;
	char	**temp;
	char	*old;

	i = -1;
	temp = NULL;
	while (divison[++i])
	{
		if (ft_strchr(divison[i], '\'') || ft_strchr(divison[i], '\"'))
		{
			temp = prepare(divison[i]);
			j = -1;
			// int k = -1;
			// while (temp[++k])
			// 	printf("-> %s\n", temp[k]);
			while (temp[++j])
			{
				if (*temp[j] != '\'')
					temp[j] = chg_dollar(temp[j], env);
			}
			j = -1;
			while (temp[++j])
			{
				old = divison[i];
				divison[i] = ft_strjoin(old, temp[j]);
				free(old);
			}
			ft_free_matrix(&temp);
		}
		else
			divison[i] = chg_dollar(divison[i], env);
	}
	ft_free_matrix(&env);
	return (divison);
}


// void	chg_dollar(char **str, char **env)
// {
// 	int		i[3];
// 	char	*temp[3];
// 	char	*res;
// 	int		flag;

// 	if (!*str || !ft_strchr(*str, '$'))
// 		return ;
// 	res = *str;
// 	while (how_many_dollars(res, env))
// 	{
// 		i[0] = -1;
// 		i[1] = 0;
// 		i[2] = 0;
// 		flag = 0;
// 		temp[2] = get_dollar_word(res, env);
// 		temp[1] = search_env(env, temp[2]) + ft_strlen(temp[2]) + 1;
// 		temp[0] = ft_calloc(ft_strlen(temp[1]) + ft_strlen(res) + 1, 1);
// 		chg_dollar_loop(i, temp, res, flag);
// 		free(temp[2]);
// 		free (res);
// 		res = temp[0];
// 	}
// 	*str = res;
// }

// int	main(int ac, char **av, char **env)
// {
// 	(void)ac;
// 	char *input = ft_strdup(av[1]);
// 	chg_dollar(&input, env);
// 	//printf("%d\n", how_many_dollars(input, env));
// 	printf("%s\n", input);
// 	free(input);
// }
