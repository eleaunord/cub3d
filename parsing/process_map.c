
#include "cub3d.h"

static void check_map_walls(t_data *game)
{
    size_t i;
    size_t row_length;

    if (game->map_rows < 2)
        error_msg(game, "Map must have at least two rows.\n", EXIT_FAILURE);
    row_length = ft_strlen(game->map[0]);
    i = 0;
    while (i < row_length)
    {
        if (game->map[0][i] != '1')
            error_msg(game, "Top border of the map must be enclosed by walls.\n", EXIT_FAILURE);
        if (game->map[game->map_rows - 1][i] != '1')
            error_msg(game, "Bottom border of the map must be enclosed by walls.\n", EXIT_FAILURE);
        i++;
    }
    i = 1;
    while (i < game->map_rows - 1)
    {
        if (game->map[i][0] != '1')
            error_msg(game, "Left border of the map must be enclosed by walls.\n", EXIT_FAILURE);
        if (game->map[i][row_length - 1] != '1')
            error_msg(game, "Right border of the map must be enclosed by walls.\n", EXIT_FAILURE);
        i++;
    }
}

static void get_map_line(t_data *game, char *line, int *map_flag)
{
    if ((line[0] == '1' || line[0] == ' ') && is_all_set(game))
    {
        *map_flag = 1;
        fill_map(game, line);
    }
    else

        free(line);        
}

static void process_map_lines(t_data *game, int *map_flag)
{
    char *line;
    char *tmp_line;

    line = get_next_line(game->fd, 0);
    while (line != NULL)
    {
        if (is_empty_line(line) == true && *map_flag == 1)
        {
            free(line);
            get_next_line(game->fd, 1);
            error_msg(game, "Empty line in map.\n", EXIT_FAILURE);
        }
        tmp_line = ft_strtrim(line, "\r\n");
        free(line);
        if (tmp_line == NULL)
            error_msg(game, "Memory allocation failed for trimmed line.\n", EXIT_FAILURE);
        get_map_line(game, tmp_line, map_flag);
        line = get_next_line(game->fd, 0);
    }
}

void process_map(t_data *game, const char *file)
{
    int map_flag = 0;

    map_flag = 0;
    game->map = ft_calloc(game->map_rows, sizeof(char *));
    if (!game->map)
        error_msg(game, "Memory allocation failed for map.\n", EXIT_FAILURE);
    game->fd = open(file, O_RDONLY);
    if (game->fd < 0)
        error_msg(game, "Could not open map file.\n", EXIT_FAILURE);
    process_map_lines(game, &map_flag);
    if (game->hero == 0)
        error_msg(game, "Player missing.\n", EXIT_FAILURE);
    close(game->fd);
    check_map_walls(game);
    //error_msg(game, "Parsing done.\n", EXIT_SUCCESS);
}

// error_msg(game, "Parsing done.\n", EXIT_SUCCESS);