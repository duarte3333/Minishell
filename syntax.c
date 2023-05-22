/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtiago-s <mtiago-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 15:04:26 by mtiago-s          #+#    #+#             */
/*   Updated: 2023/05/22 15:39:12 by mtiago-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_sep(char *str, int *arr)
{
	//printf("entrou nesta funcao a str e:\n--%s--\n", str);
	arr[0] = 0;
	if ((str[0] == '<' && str[1] == '<') || (str[0] == '>' && str[1] == '>'))
		arr[0] = 2;
	else if (str[0] == '<' || str[0] == '>')
		arr[0] = 1;
	else if (str[0] == '|')
	{
		//printf("found a pipe\n");
		arr[0] = 1;
	}
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

void	treat_sep(char *input, int	i, int size, int *words) // tem que ser repensada
{
	int temp;
	int	w;

	temp = 0;
	w = 0;
	//printf("words == %d and string is %c a condicao e == %d\n", *words, input[i], (*words == 0 && input[i] == '|'));
	if (*words == 0 && input[i] == '|' && input[i + 1] == '|')
		syntax_error("||", input, 2);
	else if (*words == 0 && input[i] == '|')
	{
		//printf("syntax error found\n");
		syntax_error("|", input, 1);
	}
	// else if (input[i] == '>' && input[i + 1] == '>' && input[i + 2] == '>')
	// 	syntax_error(">", input);
	// else if (input[i] == '<' && input[i + 1] == '<' && input[i + 2] == '<')
	// 	syntax_error("<", input);
	// else if (input[i] == '>' && input[i + 1] == '>' && input[i + 2] == '>' && input[i + 3] == '>')
	// 	syntax_error(">>", input);
	// else if (input[i] == '<' && input[i + 1] == '<' && input[i + 2] == '<' && input[i + 3] == '<')
	// 	syntax_error("<<", input);
	i += size;
	while (input[i])
	{
		if (check_sep(&input[i], &temp) && !w)
			syntax_error(&input[i], input, temp);
		else if (input[i] != 32)
			w++;
		i++;
	}
	//*words = 0;
}

void	syntax_treatment(char *input)
{
	int	i;
	int	j;
	int	words;

	i = 0;
	j = 0;
	//talvez colocar tudo sem espacos para ser mais facil de fazer checks... no caso de >> >> e suposto dar '>>' mas assim nao vai dar
	words = 0;
	if (!input)
		return ;
	while(input[i])
	{
		if (check_sep(&input[i], &j))
		{
			//printf("going for treat_sep %s\n", &input[i]);
			treat_sep(input, i, j, &words);
		}
		// else if (input[i] == '\"' || input[i] == '\'')
		// 	treat_quotes(input, i, j);
		else if (input[i] != 32)
			words++;
		if (j == 2)
			i++;
		i++;
	}
}


int	main(int ac, char **av)
{
	(void)ac;
	syntax_treatment(av[1]);
}