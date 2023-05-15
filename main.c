/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtiago-s <mtiago-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 17:01:28 by mtiago-s          #+#    #+#             */
/*   Updated: 2023/05/15 20:54:47 by mtiago-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

struct s_global
{
	int			status;
	char		**env;
	int			fd[2];
}	t_global;

int	ft_matrixlen(char **matrix)
{
	int	i;

	i = 0;
	while (matrix[i] && matrix[i][0] != 3)
		i++;
	return (i);
}

t_list	*generate_list(char *input, char **env)
{
	int				i;
	t_list			*pre_list;
	char			**division;
	static char		*pre_split;
	int				array[2];
	t_list			*temp;
	int				j;

	//printf("{input} %s\n", input);
	//printf("{size} %i\n",ft_strlen(input));
	pre_split = ft_calloc((ft_strlen(input) * 3 + 1), 1);
	if (!pre_split)
		return (NULL);
	array[0] = 0;
	array[1] = 0;
	parse(pre_split, input, 0, array);
	printf("%s\n", pre_split);
	division = ft_split(pre_split, 2);
	pre_list = NULL;
	i = -1;
	pre_list = ft_lstnew(ft_matrixlen(division), env);
	temp = pre_list;
	j = 0;
	while (division[++i])
	{
		printf("palavra nr %d\n", i);
		if (division[i][0] == 3)
		{
			printf("mais um no\n");
			ft_lstadd_back(&pre_list, ft_lstnew(ft_matrixlen(&division[i + 1]), env));
			if (temp->next)
				temp = temp->next;
			j = 0;
		}
		/* else if (!ft_strncmp(division[i], "<<", 2))
			t_global.fd[0] = ft_here_doc(*lst, i); */
		else  if (!ft_strncmp(division[i], ">>", 2))
		{
			if (t_global.fd[1] > 2) // replicar para o resto
				close(t_global.fd[1]);
			t_global.fd[1]  = open(division[++i], O_WRONLY | O_APPEND | O_CREAT, 0644);
		}
		else if (!ft_strncmp(division[i], "<", 1))
			t_global.fd[0] = open(division[++i], O_RDONLY, 0644);
		else if (!ft_strncmp(division[i], ">", 1))
			t_global.fd[1] = open(division[++i], O_WRONLY | O_TRUNC | O_CREAT, 0644);
		else
		{
			printf("div: %s\n", division[i]);
			temp->content[j] = ft_strdup(division[i]);
			printf("list: %s\n", temp->content[j]);
			j++;
		}
		
		/* if (*temp)
			ft_lstadd_back(&pre_list, ft_lstnew(temp, env));
		else
			free(temp); */
		free(division[i]);
	}
	free(pre_split);
	free(division);
	print_list(pre_list);
	exit(1);
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

