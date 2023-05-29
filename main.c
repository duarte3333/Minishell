/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsa-mora <dsa-mora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 17:01:28 by mtiago-s          #+#    #+#             */
/*   Updated: 2023/05/29 21:01:11 by dsa-mora         ###   ########.fr       */
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

void	prompt(char **env_og)
{
	char	*input;
	t_list	*list;

	while (1)
	{
		input = readline("$ ");// colocar if input != a newline fazer o resto
		if (!input)
		{
			if(input)
				free(input);
			ft_free_env(&g_data.env);
			exit(0);
		}
		add_history(input);
		syntax_treatment(input);
		list = generate_list(input);
		//print_list(list);
		if (list->content[0])
			execution(list, env_og);
		ft_free_list(&list);
		free(input);
	}
}

int	main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	g_data.env = get_env(env);
	g_data.env_og = env;
	prompt(env);
}


//Comandos que nao funcionam
// cd  | cd
// ls  | cd
// cd  | ls
// pwd | cat
// cat | exit | cat | wc
// export | grep ola
// export AS=dads
// ASDA=assa [no search]
// AS=dads [str_pos_head]

//O que falta:
// Export
// Unset
// Acabar expander
// Acrescentar $? ao expander
// Mudar OLDPWD no exec_cd
// Sinais CTRL-C
// Criar funcao que passa nosso env de t_env para char** env
// Evitar o fork para alguns comandos
