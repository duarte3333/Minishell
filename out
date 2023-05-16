/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtiago-s <mtiago-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 17:01:28 by mtiago-s          #+#    #+#             */
/*   Updated: 2023/05/16 12:33:41 by mtiago-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

struct global g;

t_list	*generate_list(char *input, char **env)
{
	t_list			*pre_list;
	char			**division;
	static char		*pre_split;
	int				array[2];

	//printf("{input} %s\n", input);
	//printf("{size} %i\n",ft_strlen(input));
	pre_split = ft_calloc((ft_strlen(input) * 3 + 1), 1);
	if (!pre_split)
		return (NULL);
	array[0] = 0;
	array[1] = 0;
	parse(pre_split, input, 0, array);
	//printf("%s\n", pre_split);
	division = ft_split(pre_split, 2);
	pre_list = NULL;
	pre_list = ft_lstnew(ft_matrixlen(division), env);
	redirection(pre_list, division, env);
	free(pre_split);
	free(division);
	//print_list(pre_list);
	return (pre_list);
}

void prompt(char **env)
{
	char	*input;
	t_list	*pre_list;

	while ((input = readline("$ ")) != NULL)
	{
		g.fd[0] = 0;
		g.fd[1] = 1;
		if (!strcmp(input, "exit"))
		{
			free(input);
			exit(0);
		}
		add_history(input);
		pre_list = generate_list(input, env);
		print_list(pre_list);
		if (pre_list->content[0])
			execution(pre_list, env);
		ft_free_list(&pre_list);
		free(input);
	}
}

int	main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	prompt(env);
}

