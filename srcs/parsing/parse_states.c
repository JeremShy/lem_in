#include <lem_in.h>

static void	go_to_next_line(char **ptr)
{
	while (**ptr && **ptr != '\n')
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
	// printf("Nbr ants : %zu\n", parse_structure->nbr_ants);
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
			if (parse_structure->start_room_id == -1 || parse_structure->end_room_id == -1)
				return (set_error(parse_structure));
			*state = STATE_PIPES;
			parse_structure->nbr_rooms = current;
			return ;
		}
		return set_error(parse_structure);
	}
	if (!is_nombre_entier(tab[1]) || !is_nombre_entier(tab[2]))
		return (set_error_and_free(tab, parse_structure));
	if (name_already_exists(tab[0], parse_structure->rooms, current))
		return (set_error_and_free(tab, parse_structure));
	parse_structure->rooms[current] = (t_room){current, 0, ft_strdup(tab[0]),
		ft_atoi(tab[1]), ft_atoi(tab[2]), NULL};
	// printf("Creating room %d with name = [%s], and coords = (%d, %d)\n", current, parse_structure->rooms[current].name, parse_structure->rooms[current].x, parse_structure->rooms[current].y);
	free_dtab(tab);
	go_to_next_line(ptr);
	current++;
}

void	parse_pipes(t_state *state, t_parse *parse_structure, char **ptr)
{
	char	**split;
	t_room	*r1;
	t_room	*r2;

	if (**ptr == '#')
	{
		if (is_command(*ptr))
			return set_error(parse_structure);
		go_to_next_line(ptr);
		if (**ptr == '\0')
		{
			*state = STATE_END;
			return ;
		}
		return ;
	}

	if (count_char('-', *ptr) != 1)
		return set_error(parse_structure);
	if ((split = ft_strsplit_lem_in(*ptr, '-')) == NULL)
		return set_error(parse_structure);
	if (count_dtab_len(split) != 2)
		return set_error_and_free(split, parse_structure);
	// printf("in parse_pipes\n");
	if ((r1 = find_room(split[0], parse_structure->rooms, parse_structure->nbr_rooms)) == NULL)
		return set_error_and_free(split, parse_structure);
	if ((r2 = find_room(split[1], parse_structure->rooms, parse_structure->nbr_rooms)) == NULL)
		return set_error_and_free(split, parse_structure);
	if (r1 == r2)
		return set_error_and_free(split, parse_structure);
	if (!add_pipe_to_rooms(r1, r2))
		return set_error_and_free(split, parse_structure);
	go_to_next_line(ptr);
	if (**ptr == '\0')
	{
		*state = STATE_END;
		return ;
	}

}
