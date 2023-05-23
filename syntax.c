/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtiago-s <mtiago-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 15:04:26 by mtiago-s          #+#    #+#             */
/*   Updated: 2023/05/23 16:23:21 by mtiago-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_sep(char *str, int *arr)
{
	arr[0] = 0;
	if ((str[0] == '<' && str[1] == '<') || (str[0] == '>' && str[1] == '>'))
		arr[0] = 2;
	else if (str[0] == '<' || str[0] == '>')
		arr[0] = 1;
	else if (str[0] == '|')
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
	// if (input)
	// 	free(input);
	exit(0);
	//prompt(g->env);
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
		if (check_sep(&input[i], &temp) && !w)
			syntax_error(&input[i], input, temp);
		else if (input[i] != 32)
			w++;
		i++;
	}
}

void	treat_quotes(char *input, int i)
{
	char	c;

	c = input[i];
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

	i = 0;
	j = 0;
	words = 0;
	if (!input)
		return ;
	while(input[i])
	{
		if (check_sep(&input[i], &j))
			treat_sep(input, i, j, &words);
		else if (input[i] == '\"' || input[i] == '\'')
			treat_quotes(input, i);
		else if (input[i] != 32)
			words++;
		if (j == 2)
			i++;
		i++;
	}
}


int	main(void)
{
	syntax_treatment("\' ola eu sou o tiago");
}