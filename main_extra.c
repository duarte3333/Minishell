/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_extra.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtiago-s <mtiago-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 17:01:28 by mtiago-s          #+#    #+#             */
/*   Updated: 2023/05/09 18:43:39 by mtiago-s         ###   ########.fr       */
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
void	classifier(char *div, t_list *pre_list)
{
	int		i;
	char	*temp;
	char 	**post;

	i = -1;
	temp = NULL;
	post = ft_split(div, ' ');
	while (post[++i])
	{
		//printf("post %s\n", post[i]);
		if (!strcmp(post[i], "<"))
			i++;
		else if (!strcmp(post[i], ">"))
			i++;
		else if (!strcmp(post[i], "<<"))
			i++;
		else if (!strcmp(post[i], "<<"))
			i++;
		else
		{
			if (!temp)
				temp = post[i];
			else
			{
				temp = ft_strjoin(temp, " ");
				temp = ft_strjoin(temp, post[i]);
				//printf("temp %s\n", temp);
			}
		}
	}
	ft_lstadd_back(&pre_list, ft_lstnew(temp));
	print_list(pre_list);
}

t_list	*generate_list(char *input)
{
	int		i;
	int		j;
	t_list	*pre_list;
	char 	**division;
	char 	**post_division;

	division = ft_split(input, '|');
	pre_list = NULL;
	i = -1;
	while (division[++i])
		classifier(division[i], pre_list);
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
		//print_list(pre_list);
		free(input);
	}
}

