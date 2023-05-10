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

void	print_list(t_list *list)
{
	if (!list)
		printf("empty list\n");
	while (list)
	{
		int	i;
		
		i = -1;
		printf("[p] %p", list);
		printf("\n[content]: ");
		while (list->content[++i])
			printf("{%s}, ", list->content[i]);
		printf("\n");
		printf("[fd in] %i\n", list->fd[0]);
		printf("[fd out] %i\n", list->fd[1]);
		list = list->next;
	}
}

void	ft_free_list(t_list **lst)
{
	t_list	*temp;
	int		i;

	while (*lst)
	{
		i = -1;
		temp = (*lst)->next;
		ft_free_matrix(&(*lst)->content);
		free((*lst)->content);
		free(*lst);
		*lst = temp;
	}
}

//ls -l | < Makefile cat | cat > out

t_list	*generate_list(char *input)
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
		ft_lstadd_back(&pre_list, ft_lstnew(division[i]));
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
		pre_list = generate_list(input);
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

