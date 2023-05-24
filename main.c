/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtiago-s <mtiago-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 17:01:28 by mtiago-s          #+#    #+#             */
/*   Updated: 2023/05/24 17:01:24 by mtiago-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

struct global	g_data;

t_list	*generate_list(char *input)
{
	t_list			*list;
	char			**division;
	char			*pre_split;
	int				array[2];

	pre_split = ft_calloc((ft_strlen(input) * 3 + 1), 1);
	if (!pre_split)
		return (NULL);
	array[0] = 0;
	array[1] = 0;
	parse(pre_split, input, 0, array);
	//printf("%s\n", pre_split);
	division = ft_split(pre_split, 2);
	list = NULL;
	list = ft_lstnew(ft_matrixlen(division));
	redirection(list, division);
	free(pre_split);
	free(division);
	return (list);
}

void	prompt(char **env)
{
	char	*input;
	t_list	*list;

	while (1)
	{
		input = readline("$ ");// colocar if input != a newline fazer o resto
		if (!input || !ft_strcmp(input, "exit"))
		{
			if(input)
				free(input);
			exit(0);
		}
		add_history(input);
		syntax_treatment(input);
		list = generate_list(input);
		//print_list(list);
		if (list->content[0])
			execution(list, env);
		ft_free_list(&list);
		free(input);
	}
}

int	main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	g_data.env = ft_matrixdup(env);
	prompt(env);
}
