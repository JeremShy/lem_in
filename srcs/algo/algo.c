#include <lem_in.h>

int8_t	update_all_around(t_room *origin, t_parse *parse_structure)
{
	size_t	to_set;
	t_pipe	*pipe;
	t_room	*actual;
	int8_t		status; // -1 = no room, 0 = rooms, 1 = end encountered

	status = -1;
	to_set = origin->distance + 1;
	pipe = origin->pipes;
	while (pipe)
	{
		actual = pipe->other_side;
		if (parse_structure->start_room_id != actual->id && (actual->distance == 0 || actual->distance > to_set))
		{
			if (status != 1)
				status = 0;
			actual->distance = to_set;
		}
		if (!status && actual->id == parse_structure->end_room_id) // TODO : Return 1 serait mieux
			status = 1;
		pipe = pipe->next;
	}
	return (status);
}

int8_t	explore_and_set_with_nbr(size_t to_set, t_parse *parse_structure)
{
	int8_t		status; // -1 = no room, 0 = rooms, 1 = end encountered
	size_t	i;
	int8_t		tmp;

	status = -1;
	if (to_set == 1)
	{
		status = update_all_around(parse_structure->rooms + parse_structure->start_room_id, parse_structure);
		return (status);
	}

	i = 0;
	while (i < parse_structure->nbr_rooms)
	{
		if (parse_structure->rooms[i].distance == to_set - 1 && (int64_t)i != parse_structure->end_room_id)
		{
			tmp = update_all_around(parse_structure->rooms + i, parse_structure);
			if (tmp == 1)
				status = 1;
			else if (tmp == 0 && status != 1)
				status = 0;
		}
		i++;
	}
	return (status);
}

void	set_distances(t_parse *parse_structure)
{
	t_room	*start;
	size_t	actual_distance;
	int8_t	tmp;  // -1 = no room, 0 = rooms, 1 = end encountered

	start = parse_structure->rooms + parse_structure->start_room_id;
	actual_distance = 1;
	while (42)
	{
		tmp = explore_and_set_with_nbr(actual_distance, parse_structure);
		if (tmp == -1 && parse_structure->rooms[parse_structure->end_room_id].distance == 0)
			print_error_and_exit(5);
		else if (tmp == -1)
			return ;
		actual_distance++;
	}
}

void	explore_all_path(t_parse *parse_structure)
{

}

void	get_max_path(t_parse *parse_structure)
{
	size_t		pipe_start;
	size_t		pipe_end;
	t_pipe		*ptr;

	pipe_start = 0;
	pipe_end = 0;
	ptr = parse_structure->rooms[parse_structure->start_room_id].pipes;
	while (ptr)
	{
		pipe_start++;
		ptr = ptr->next;
	}
	ptr = parse_structure->rooms[parse_structure->end_room_id].pipes;
	while (ptr)
	{
		pipe_end++;
		ptr = ptr->next;
	}
	if (pipe_start > pipe_end)
		parse_structure->max_paths = pipe_end;
	else
		parse_structure->max_paths = pipe_start;
}

void	algorithm(t_parse *parse_structure)
{
	set_distances(parse_structure);
	print_all_rooms(parse_structure->rooms, parse_structure->nbr_rooms);
	get_max_path(parse_structure);
	explore_all_path(parse_structure);
}

// solution*	backtracking(t_room *depart, t_room *direction, t_path *chemin)
// {
// 	 if (!direction && y a plusieurs pipe)
// 	 {
// 		 solution *accumulateur;
// 		 while (y a des pipes)
// 		 	accumulateur.add(backtracking(depart, pipe));
// 		return (accumulateur);
// 	 }
// 	 else if (direction)
// 	 {
// 		 on avance de un
// 		 chemin.add(depart);
// 	 }
// 	 while (y a pas plusieurs pipe)
// 	 {
// 		 on avance
// 		 on ajoute la room en court au chemin
// 	 }
// 	 if (on est a la fin)
// 	 {
// 		return (chemin);
// 	 }
// 	 else // Alors on a plusieurs pipes
// 	 {
// 		 solution *accumulateur;
// 		 while (y a des pipes)
// 		 	accumulateur.add(backtracking(depart, pipe));
// 		return (accumulateur);
// 	 }
// }
