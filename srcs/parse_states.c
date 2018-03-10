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
		return set_error(parse_structure);
	parse_structure->nbr_ants = nbr;
	parse_structure->nbr_ants_start = nbr;
	printf("Nbr ants : %zu\n", parse_structure->nbr_ants);
	*state = STATE_ROOMS;
	go_to_next_line(ptr);
}

static int	parse_rooms_is_command(char **ptr, int8_t ret, t_parse *parse_structure, int current)
{
	if (ret == 1)
	{
		if (parse_structure->start_room_id != -1)
		{
			parse_structure->error = 1;
			return (0);
		}
		parse_structure->start_room_id = current;
	}
	else
	{
		if (parse_structure->end_room_id != -1)
		{
			parse_structure->error = 1;
			return (0);
		}
		parse_structure->end_room_id = current;
	}
	go_to_next_line(ptr);
	if (**ptr == '#')
	{
		parse_structure->error = 1;
		return (0);
	}
	return (1);
}

void	parse_rooms(t_state *state, t_parse *parse_structure, char **ptr)
{
	static	int	current = 0;
	char	**tab;
	int8_t	ret;
	int8_t	count;
	int8_t	flag_start_end;

 	flag_start_end = 0;
	if (**ptr == '#')
	{
		if ((ret = is_command(*ptr)))
		{
			if (parse_rooms_is_command(ptr, ret, parse_structure, current) == 0)
				return ;
			flag_start_end = 1;
		}
		else
		{
			go_to_next_line(ptr);
			return ;
		}
	}
	tab = ft_strsplit_lem_in(*ptr, ' ');
 	if (!tab)
		return set_error(parse_structure);
	if ((count = count_dtab_len(tab)) != 3)
	{
		free_dtab(tab);
		if (!flag_start_end && count == 1)
		{
			*state = STATE_PIPES;
			return ;
		}
		return set_error(parse_structure);
	}
	if (!is_nombre_entier(tab[1]) || !is_nombre_entier(tab[2]))
	{
		free_dtab(tab);
		return set_error(parse_structure);
	}
	parse_structure->rooms[current] = (t_room){current, 0, ft_strdup(tab[0]),
		ft_atoi(tab[1]), ft_atoi(tab[2]), NULL};
	printf("Creating room %d with name = [%s], and coords = (%d, %d)\n", current, parse_structure->rooms[current].name, parse_structure->rooms[current].x, parse_structure->rooms[current].y);
	free_dtab(tab);
	go_to_next_line(ptr);
	current++;
}

void	parse_pipes(t_state *state, t_parse *parse_structure, char **ptr)
{
	printf("in parse_pipes\n");
	*ptr = NULL;
}
