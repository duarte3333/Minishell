/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtiago-s <mtiago-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 15:57:38 by mtiago-s          #+#    #+#             */
/*   Updated: 2023/05/26 16:58:37 by mtiago-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_sep(char *str, int *arr)
{
	arr[0] = 0;
	if ((str[0] == '<' && str[1] == '<') || (str[0] == '>' && str[1] == '>'))
		arr[0] = 2;
	else if (str[0] == '<' || str[0] == '>')
		arr[0] = 1;
	else if (str[0] == '|')
		arr[0] = 1;
	return (arr[0]);
}
/* Esta funcao faz o parsing do minishell 
Linha 47: -Se sep encontrado e se encontrado novamente desligado
		if (sep != *str) -> inicializa sep -> sep = 1
		if (sep == *str) -> reinicia sep -> sep = 0;
Linha 49: -Se seo = 0 e ' ' torna em 2 na str
Linha 51: -Se for um token {<, <<, >, >>, |} e sep = 0: 
		  meter um 3 na casa do separador (tem de ser o unico 3 até ver uma 
		  algo diferente de token -> len = 0).
		  -Se nao for um pipe e len>0 --> manter o elemento na str
		  -Se nao for um pipe e arr==2 --> manter o proximo, fazendo dois
		  -No final meter um 2 extra e len passa para 1
Linha 56: Incrementamos o str aqui para poupar linhas
Linha 61: -Caso geral: é ir colando as letras na string res e dizer que 
		  pode começar um novo token -> len = 0*/

void	parse(char *res, char *str, char sep, int *arr)
{
	int		len;

	len = 0;
	while (str && *str)
	{
		if ((*str == '\'' || *str == '\"') && (!sep || sep == *str))
			sep = (*str) * (sep != *str);
		else if (*str == ' ' && !sep)
			*str = 2;
		if (!sep && check_sep(str, arr))
		{
			*res++ = (3 - (*str != '|' || len != 0 || arr[1] == 0));
			if ((*str != '|' || !arr[1]) || len)
				*res++ = *str;
			if (str++ && *str != '|' && arr[0] == 2)
				*res++ = *str++;
			*res++ = 2;
			len++;
		}
		else if ((*str == 2 && arr[1]) || ((*str != 2 || *str++ != 2) && ++arr[1]))
		{	
			*res++ = *str++;
			len = 0;
		}
	}
}

//Example : wc | cat>out ls
//Output:   wc2322cat3>2out2ls

//Example : cat | "grep a" | >>> something
//Output:  cat2322"grep a"23223>>22>22something

//----------------------------------------------------------------
//--  "Makefile < cat"     -- Makefile < cat: command not found --
//----------------------------------------------------------------
//--  "< Makefile cat"     -- Faz here doc e escreve num        --
//--                       -- ficheiro chamado cat              --
//----------------------------------------------------------------
//--  < Makefile cat       --  Faz cat do Makefile no terminal  --
//----------------------------------------------------------------
//--< Makefile cat > out   -- Faz cat para um ficheiro out      --
//----------------------------------------------------------------
//--"< Makefilecat "< cat""-- < Makefilecat : command not found --
//----------------------------------------------------------------
//--    "ls"< cat""        --  Faz o ls no terminal             --
//----------------------------------------------------------------
//--  "Makefile"< ls"      --  Faz o here doc para lado nenhum  --
//----------------------------------------------------------------
//--     ls >>> cat        --  error near unexpected token `>'  --
//----------------------------------------------------------------
//--     ls <<< ola       --   executa o ls                     --
//----------------------------------------------------------------

char	*get_dollar_word(char *str, char **env) // se calhar esta funcao tem de fazer ja o search path para ver se e suposto retornar essa palavra
{
	int		i;
	int		j;
	char	*res;

	i = -1;
	while (str[++i])
	{
		if (i && str[i - 1] == '$' && str[i] != 32 && str[i] != '$')
		{
			j = 0;
			while (str[i + j] && str[i + j] != 32 && str[i + j] != '$')
				j++;
			if (!j)
				return (NULL);
			res = ft_calloc(j + 1, 1);
			while (--j != -1 && str[i + j])
				res[j] = str[i + j];
			if (search_env(env, res))
				return (res);
			else
				free(res);
		}
	}
	return (NULL);
}

int	how_many_dollars(char *str, char **env) // contagem de quantos $ serao subsituidos
{
	int		res;
	int		i;
	char	*temp;

	i = -1;
	res = 0;
	temp = NULL;
	while (str[++i])
	{
		if (str[i] == '$' && str[i + 1] && str[i + 1] != 32 && str[i + 1] != '$')
		{
			temp = get_dollar_word(&str[i], env);
			//printf("cmp s1 == %s s2 == %s tamanho == %zu\n", &str[i + 1], temp, ft_strlen(temp));
			if (temp && !ft_strncmp(&str[i + 1], temp, ft_strlen(temp)) && search_env(env, temp))
				res++;
			if (temp)
				free(temp);
			temp = NULL;
		}
	}
	return (res);
}

void	chg_dollar(char **str, char **env)
{
	int		i[3];
	char	*temp;
	char	*temp2;
	char	*temp3;
	char	*res;
	int		flag;

	if (!*str || !ft_strchr(*str, '$'))
		return ;
	temp = NULL;
	temp2 = NULL;
	res = *str;
	while (how_many_dollars(res, env))
	{
		i[0] = -1;
		i[1] = 0;
		i[2] = 0;
		flag = 0;
		temp3 = get_dollar_word(res, env);
		if (!temp3) //ISTO SIGNIFICA QUE NAO HAVIA NADA A SEGUIR AO $
		{
			printf("nothing after $\n");
			exit(1);
		}
		temp2 = search_env(env, temp3);
		if (!temp2) //ISTO SIGNIFICA QUE NAO HAVIA A VARIAVEL NO ENV
		{
			printf("nao existe no env\n");
			exit(2);
		}
		temp2 += ft_strlen(temp3) + 1;
		temp = ft_calloc(ft_strlen(temp2) + ft_strlen(res) + 1, 1);
		while (res[++i[0]]) // percorrer string anterior
		{
			if (res[i[0]] == '$' && !ft_strncmp(&res[i[0] + 1], temp3, ft_strlen(temp3)) &&!flag++ && ++i[0])
			{
				while (temp2[i[2]]) //copiar para string nova a parte que e para substituir
					temp[i[1]++] = temp2[i[2]++];
				while (res[i[0] + 1] && res[i[0] + 1] != 32) // avancar a palarva ex $PATH palavra = PATH
					i[0]++;
			}
			else // copiar o resto
				temp[i[1]++] = res[i[0]];
		}
		free(temp3);
		free (res);
		res = temp;
	}
	*str = res;
}
	
// }

// int main(int ac, char **av)
// {
// 	char *line = av[1];
// 	(void)ac;
// 	static char res[1000];
// 	printf("%s\n", av[1]);
// 	parse(res,line, 0, 0);
// 	printf("%s\n", res);
// }


int	main(int ac, char **av, char **env)
{
	(void)ac;
	char *input = ft_strdup(av[1]);
	chg_dollar(&input, env);
	//printf("%d\n", how_many_dollars(input, env));
	printf("%s\n", input);
	free(input);
}