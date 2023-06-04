/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duarte33 <duarte33@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 15:04:26 by mtiago-s          #+#    #+#             */
/*   Updated: 2023/06/03 14:30:26 by duarte33         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_sep_2(char *str, int *arr)
{
	arr[0] = 0;
	if ((str[0] == '<' && str[1] == '<') || (str[0] == '>' && str[1] == '>'))
		arr[0] = 2;
	else if (str[0] == '<' || str[0] == '>')
		arr[0] = 1;
	else if (str[0] == '|')
		arr[0] = 1;
	else if (str[0] == ';')
		arr[0] = 1;
	return (arr[0]);
}

void	syntax_error(char *str, char *input, int size)
{
	int	i;

	i = -1;
	write(2, "minishell: syntax error near unexpected token `", 47);
	while (size != 0 && str[++i])
	{
		write(2, &str[i], 1);
		size--;
	}
	write(2, "\'\n", 2);
	if (input)
		free(input);
	g_data.status = 2;
	prompt(g_data.env_og);
}

void	treat_sep(char *input, int i, int size, int *words)
{
	int	temp;
	int	w;
	int	sep;

	temp = 0;
	w = 0;
	sep = 0;
	if (input[i] == '|')
		sep = input[i];
	if (input[i] == '|' && input[i + 1] == '|')
		syntax_error("||", input, 2);
	else if (*words == 0 && input[i] == '|')
		syntax_error("|", input, 1);
	i += size;
	while (input[i])
	{
		if (!sep && check_sep_2(&input[i], &temp) && !w)
			syntax_error(&input[i], input, temp);
		else if (input[i] != 32)
			w++;
		i++;
	}
	if (!w)
		syntax_error("newline", input, 8);
}

void	delete_quotes_string(char **input, char c)
{
	char	*temp;
	int		i;
	int		j;
	int		flag;

	i = -1;
	j = 0;
	flag = 0;
	temp = ft_calloc(ft_strlen(*input) + 1, 1);
	if (!temp)
		return ;
	while (input[0][++i])
	{
		if ((input[0][i] == '\'' || input[0][i] == '\"') \
			&& (!c || c == input[0][i]) && (!flag || flag == input[0][i]))
			c = input[0][i] * (c != input[0][i]);
		else
			temp[j++] = input[0][i];
		if (c)
			flag = c;
		else
			flag = 0;
	}
	free(*input);
	*input = temp;
}

// void	syntax_treatment(char *input)
// {
// 	int	i;
// 	int	j;
// 	int	words;
// 	int	flag;
// 	int	sep;

// 	i = 0;
// 	j = 0;
// 	words = 0;
// 	flag = 0;
// 	sep = 0;
// 	if (!input)
// 		return ;
// 	while (input[i])
// 	{
// 		if ((input[i] == '\'' || input[i] == '\"') && (!sep || sep == input[i]))
// 			sep = (input[i]) * (sep != input[i]);
// 		if (!sep && check_sep_2(&input[i], &j))
// 			treat_sep(input, i, j, &words);
// 		else if ((input[i] == '\"' && !flag) || (input[i] == '\'' && !flag))
// 			treat_quotes(input, i, &flag);
// 		else if (input[i] == flag)
// 			flag = 0;
// 		else if (input[i] != 32)
// 			words++;
// 		if (j == 2)
// 			i++;
// 		i++;
// 	}
// }

// i -> arr[0]
// j -> arr[1]
// words -> arr[2]
// flag -> arr[3]
// sep -> arr[4]

void	syntax_treatment(char *input)
{
	int	*arr;

	arr = (int *)ft_calloc(5, sizeof(int));
	if (!input)
		return ;
	while (input[arr[0]])
	{
		if ((input[arr[0]] == '\'' || input[arr[0]] == '\"') \
			&& (!arr[4] || arr[4] == input[arr[0]]))
			arr[4] = (input[arr[0]]) * (arr[4] != input[arr[0]]);
		if (!arr[4] && check_sep_2(&input[arr[0]], &(arr[1])))
			treat_sep(input, arr[0], arr[1], &(arr[2]));
		else if ((input[arr[0]] == '\"' && !arr[3]) || \
			(input[arr[0]] == '\'' && !arr[3]))
			treat_quotes(input, arr[0], &arr[3]);
		else if (input[arr[0]] == arr[3])
			arr[3] = 0;
		else if (input[arr[0]] != 32)
			(arr[2])++;
		if (arr[1] == 2)
			(arr[0])++;
		(arr[0])++;
	}
	free(arr);
}
