#include "../minishell.h"

void	print_matrix(char **str, size_t i)
{
	size_t j;

	j = 0;
	while (str[j])
		j++;
	while (str[i])
	{
		if ((i + 1) != j)
			printf("%s ", str[i]);
		else 
			printf("%s", str[i]);
		i++;
	}
}

int	is_a_n(char letter)
{
	if (letter == 'n')
		return (1);
	return (0);
}

void	__exec_echo(char **env, t_list **lst)
{
	int 	i;
	int		flag;

	flag = 0;
	(void)env; 
	close_fds(lst, 1);
	if ((*lst)->content[1][0] == '-')
	{
		i = 1;
		while ((*lst)->content[1][i])
		{
			if (!(is_a_n((*lst)->content[1][i])))
			{
				flag++;
				break;
			}
			i++;
		}
		if (!flag)
			flag = 2;
	}
	if (flag == 1 || !flag)
	{
		print_matrix((*lst)->content, 1);
		printf("\n");
	}
	else if (flag == 2)
		print_matrix((*lst)->content, 2);
}
