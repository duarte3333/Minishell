/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsa-mora <dsa-mora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 17:01:28 by mtiago-s          #+#    #+#             */
/*   Updated: 2023/05/10 15:26:52 by dsa-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*generate_list(char *input, char **env)
{
	int				i;
	t_list			*pre_list;
	char			**division;
	static char		*pre_split;

	//printf("{input} %s\n", input);
	//printf("{size} %i\n",ft_strlen(input));
	pre_split = ft_calloc((ft_strlen(input) * 3 + 1), 1);
	if (!pre_split)
		return (NULL);
	parse(pre_split, input, 0, 0);
	//printf("%s\n", pre_split);
	division = ft_split(pre_split, '3');
	pre_list = NULL;
	i = -1;
	while (division[++i])
	{
		//printf("{division} %s\n", division[i]);
		ft_lstadd_back(&pre_list, ft_lstnew(division[i], env));
		free(division[i]);
	}
	free(pre_split);
	free(division);
	return (pre_list);
}
void prompt(char **env)
{
	char	*input;
	t_list	*pre_list;

	while ((input = readline("$ ")) != NULL)
	{
		if (!strcmp(input, "exit"))
		{
			free(input);
			exit(0);
		}
		add_history(input);
		pre_list = generate_list(input, env);
		print_list(pre_list);
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

