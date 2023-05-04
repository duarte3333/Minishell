/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtiago-s <mtiago-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 17:01:28 by mtiago-s          #+#    #+#             */
/*   Updated: 2023/05/04 15:53:03 by mtiago-s         ###   ########.fr       */
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

//ls -l | < Makefile cat | cat > out
void	classifier(char *div, t_list **pre_list)
{
	int		i;
	char	*temp;
	char 	**post;

	i = -1;
	temp = NULL;
	post = ft_split(div, '2');
	printf("post %s\n", post[0]);
	ft_lstadd_back(pre_list, ft_lstnew(ft_split(post, '2')));
	//print_list(pre_list);
}

t_list	*generate_list(char *input)
{
	int				i;
	t_list			*pre_list;
	char 			**division;
	static char 	*pre_split;

	printf("{input} %s\n", input);
	printf("{size} %i\n",ft_strlen(input));
	pre_split = (char *)malloc(sizeof(char) * (ft_strlen(input) * 2) + 1);
	pre_split[(ft_strlen(input) * 2)] = NULL;
	parse(pre_split, input, 0, 0);
	printf("{pre_split} %s\n", pre_split);
	division = ft_split("wc322>>22>", '3');
	free(pre_split);
	pre_list = NULL;
	i = -1;
	while (division[++i])
	{
		printf("{division} %s\n", division[i]);
		ft_lstadd_back(pre_list, ft_lstnew(ft_split(div, '2')));

		classifier(division[i], &pre_list);
		free(division[i]);
	}
	free(division);
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

