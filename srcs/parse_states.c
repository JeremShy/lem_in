#include <lem_in.h>

static void	go_to_next_line(char **ptr)
{
	while (**ptr != '\n' && **ptr)
		(*ptr)++;
	if (**ptr)
		(*ptr)++;
}

void	parse_ants(t_state *state, t_parse *parse_structure, char **ptr)
{
	int	nbr;

	if (**ptr == '#')
	{
		if (is_command(*ptr))
			parse_structure->error = 1;
		else
			go_to_next_line(ptr);
		return ;
	}
	nbr = ft_atoi(*ptr);
	if (nbr <= 0)
	{
		parse_structure->error = 1;
		return ;
	}
	parse_structure->nbr_ants = nbr;
	parse_structure->nbr_ants_start = nbr;
	printf("Nbr ants : %zu\n", parse_structure->nbr_ants);
	*state = STATE_ROOMS;
	go_to_next_line(ptr);
}

void	parse_rooms(t_state *state, t_parse *parse_structure, char **ptr)
{
	static	int	current = 0;
	char	**tab;

	if (**ptr == '#')
	{
		if (is_command(*ptr))
		{
			// quest ce que c'est la commande
			// ligne d'apres
			// mettre room_id a current + 1
		}
		else
		{
			go_to_next_line(ptr);
			return ;
		}
	}
	tab = ft_strsplit(*ptr, ' ');
	if (!tab)
	{
		parse_structure->error = 1;
		return ;
	}
	current++;
}

void	parse_pipes(t_state *state, t_parse *parse_structure, char **ptr)
{
	printf("in parse_pipes\n");
	*ptr = NULL;
}
