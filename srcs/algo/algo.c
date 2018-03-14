#include <lem_in.h>

int8_t	update_all_around(t_room *origin, t_parse *parse_structure)
{
	size_t	to_set;
	t_pipe	*pipe;
	t_room	*actual;
	int8_t		end_encountered;

	to_set = origin->distance + 1;
	pipe = origin->pipes;
	end_encountered = 0;
	while (pipe)
	{
		actual = pipe->other_side;
		if (parse_structure->start_room_id != actual->id && (actual->distance == 0 || actual->distance > to_set))
			actual->distance = to_set;
		if (!end_encountered && actual->id == parse_structure->end_room_id) // TODO : Return 1 serait mieux
			end_encountered = 1;
		pipe = pipe->next;
	}
	return (end_encountered);
}

int8_t	explore_and_set_with_nbr(size_t to_set, t_parse *parse_structure)
{
	int8_t	end_encountered;
	size_t	i;

	end_encountered = 0;
	if (to_set == 1)
	{
		if (update_all_around(parse_structure->rooms + parse_structure->start_room_id, parse_structure) == 1)
			end_encountered = 1;
		return (end_encountered);
	}

	i = 0;
	while (i < parse_structure->nbr_rooms)
	{
		if (parse_structure->rooms[i].distance == to_set - 1)
		{
			if (update_all_around(parse_structure->rooms + i, parse_structure) == 1)
				end_encountered = 1;
		}
		i++;
	}
	return (end_encountered);
}

void	set_distances(t_parse *parse_structure)
{
	t_room	*start;
	size_t	actual_distance;

	start = parse_structure->rooms + parse_structure->start_room_id;
	ft_printf("Start room : \n");
	print_room(start);
	actual_distance = 1;
	while (42)
	{
		explore_and_set_with_nbr(actual_distance, parse_structure);
		actual_distance++;
	}
}

void	algorithm(t_parse *parse_structure)
{
	set_distances(parse_structure);
}
