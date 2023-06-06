/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtiago-s <mtiago-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 17:01:28 by mtiago-s          #+#    #+#             */
/*   Updated: 2023/06/06 18:11:21 by mtiago-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

struct s_global	g_data;

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
	division = ft_split(pre_split, 2);
	division = expander(division, ft_env_lst_to_arr(g_data.env));
	list = NULL;
	list = ft_lstnew(ft_matrixlen(division));
	redirection(list, division);
	free(pre_split);
	free(division);
	return (list);
}

void	prompt(void)
{
	char	*input;
	t_list	*list;

	while (1)
	{
		g_data.interrupted = 0;
		input = readline("$ ");
		if (!input)
		{
			if (input)
				free(input);
			ft_free_env(&g_data.env);
			exit(0);
		}
		add_history(input);
		syntax_treatment(input);
		list = generate_list(input);
		if (!input[0] || !list->content[0] || !list->content[0][0])
			g_data.status = 0;
		if (list->content[0] && !g_data.interrupted)
			execution(list);
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
	g_data.status = 0;
	g_data.hd = 0;
	rl_catch_signals = 0;
	signals_default();
	prompt();
}

//Comandos malucos
// <>
// cat /dev/random | head
// < Makefile < main.c cat > out > out2
// << ola << oi << lol << final cat
// << EOF cat
// cat << EOF
// cd  | cd
// ls  | cd
// cd  | ls
// pwd | cat
// cat | exit | cat | wc
// cat >
// exit 300
// export | grep ola (ola nao tá no env; e tem de dar print declare -x ola)
// export new (variavel nova) ; nao pode tar no env
// export new=a (variavel nova) ; ja pode tar no env
// export LOL=lala ROR=rara
// unset LOL ROR
// export "HI =hi"
// echo ""''

//O que falta:
//Ctrl-D no here doc

// DONE
// Export DONE
// Criar funcao que passa nosso env de t_env para char** env DONE
// Evitar o fork para alguns comandos DONE
// Acabar expander DONE
// Acrescentar $? ao expander DONE
// Resolver aspas do echo """""""" DONE
// Unset DONE
// Mudar OLDPWD no exec_cd - POR CHECKAR NA ESCOLA DONE
// Sinais CTRL-C DONE
// Overflow do exit DONE