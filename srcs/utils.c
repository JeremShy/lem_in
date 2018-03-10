#include <lem_in.h>

void	print_error_and_exit(int nbr)
{
	perror("lem_in");
	write(1, "ERROR\n", sizeof("ERROR\n") - 1);
	exit(nbr);
}

void	print_and_exit(int nbr)
{
	write(1, "ERROR\n", sizeof("ERROR\n") - 1);
	exit(nbr);
}

void	set_error(t_parse *parse_structure)
{
	parse_structure->error = 1;
	return ;
}

void	free_dtab(char	**tab)
{
	int	i;

	i = 0;
	while(tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

size_t	count_dtab_len(char **tab)
{
	size_t	i;

	i = 0;
	while(tab[i])
		i++;
	return (i);
}

void	print_dtab(char **tab)
{
	size_t	i = 0;

	while (tab[i])
	{
		printf("tab[%zu] = %s\n", i, tab[i]);
		i++;
	}
}
