/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtiago-s <mtiago-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 17:01:28 by mtiago-s          #+#    #+#             */
/*   Updated: 2023/05/03 18:54:19 by mtiago-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_list(t_list *list)
{
	while (list)
	{
		printf("\n[content] %s\n", list->content);
		printf("[fd in] %i\n", list->fd[0]);
		printf("[fd out] %i\n", list->fd[1]);
		list = list->next;
	}
}

t_list	*generate_list(char *input)
{
	int		i;
	int		j;
	t_list	*pre_list;
	char 	**division;

	division = ft_split(input, '|');
	pre_list = NULL;
	i = -1;
	while (division[++i])
	{
		ft_lstadd_back(&pre_list, ft_lstnew(division[i]));
	}
	return (pre_list);
}

int	main(int ac, char **av, char **env)
{
	char	*input;
	t_list	*pre_list;

	(void)ac;
	(void)av;
	(void)env;
	while ((input = readline("> ")) != NULL)
	{
		if (!strcmp(input, "exit"))
		{
			free(input);
			exit(0);
		}
		pre_list = generate_list(input);
		print_list(pre_list);
		free(input);
	}
}

