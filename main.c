/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtiago-s <mtiago-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 17:01:28 by mtiago-s          #+#    #+#             */
/*   Updated: 2023/05/12 14:30:46 by mtiago-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*generate_list(char *input, char **env)
{
	int				i;
	t_list			*pre_list;
	char			**division;
	static char		*pre_split;
	int				array[2];
	char			**temp;

	//printf("{input} %s\n", input);
	//printf("{size} %i\n",ft_strlen(input));
	pre_split = ft_calloc((ft_strlen(input) * 3 + 1), 1);
	if (!pre_split)
		return (NULL);
	array[0] = 0;
	array[1] = 0;
	parse(pre_split, input, 0, array);
	//printf("%s\n", pre_split);
	division = ft_split(pre_split, 3);
	pre_list = NULL;
	i = -1;
	while (division[++i])
	{
		//printf("{division} %s\n", division[i]);
		temp = ft_split(division[i], 2);
		// if (*temp)
			ft_lstadd_back(&pre_list, ft_lstnew(temp, env));
		// else
		// 	free(temp);
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
		unlink(".temp");
	}
}

int	main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	prompt(env);
}

