/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsa-mora <dsa-mora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 15:04:26 by mtiago-s          #+#    #+#             */
/*   Updated: 2023/05/31 17:47:50 by dsa-mora         ###   ########.fr       */
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

void	syntax_error(char* str, char *input, int size)
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

void	treat_sep(char *input, int	i, int size, int *words)
{
	int temp;
	int	w;

	temp = 0;
	w = 0;
	if (*words == 0 && input[i] == '|' && input[i + 1] == '|')
		syntax_error("||", input, 2);
	else if (*words == 0 && input[i] == '|')
		syntax_error("|", input, 1);
	i += size;
	while (input[i])
	{
		if (check_sep_2(&input[i], &temp) && !w)
			syntax_error(&input[i], input, temp);
		else if (input[i] != 32)
			w++;
		i++;
	}
	if (!w)
		syntax_error("newline", input, 8);
}

void	delete_quotes(char **input, char c)
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
		if ((input[0][i] == '\'' || input[0][i] == '\"') && (!c || c == input[0][i]) && (!flag || flag == input[0][i]))
			c = input[0][i] * (c != input[0][i]);
		else
			temp[j++] = input[0][i];
		if (c)
			flag = c;			
	}
	free(*input);
	*input = temp;
}


// void	delete_quotes(char **input, char c)
// {
// 	char	*temp;
// 	int		i;
// 	int		j;
// 	int		flag;
	
// 	i = -1;
// 	j = 0;
// 	flag = 0;
// 	printf("<-- %s\n", *input);
// 	temp = ft_calloc(ft_strlen(*input) + 1, 1);
// 	if (!temp)
// 		return ;
// 	while (input[0][++i])
// 	{
// 		if (flag == 2 || input[0][i] != c)
// 			temp[j++] = input[0][i];
// 		else
// 			flag++;
// 	}
// 	printf("flag == %d\n", flag);
// 	if (flag == 2)
// 	{
// 		free(*input);
// 		*input = temp;
// 	}
// 	else
// 		free(temp);
// 	printf("--> %s\n", *input);
// }

void	treat_quotes(char *input, int i, int *flag)
{
	char	c;

	c = input[i];
	*flag = c;
	while (input[++i])
	{
		if (c == input[i])
			return ;
	}
	syntax_error(&c, input, 1);
}

void	syntax_treatment(char *input)
{
	int	i;
	int	j;
	int	words;
	int	flag;

	i = 0;
	j = 0;
	words = 0;
	flag = 0;
	if (!input)
		return ;
	while(input[i])
	{
		if (check_sep_2(&input[i], &j))
			treat_sep(input, i, j, &words);
		else if ((input[i] == '\"' && !flag) || (input[i] == '\'' && !flag))
			treat_quotes(input, i, &flag);
		else if (input[i] == flag)
			flag = 0;
		else if (input[i] != 32)
			words++;
		if (j == 2)
			i++;
		i++;
	}
}

