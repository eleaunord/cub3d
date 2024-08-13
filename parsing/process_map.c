
#include "cub3d.h"

void check_map_walls(t_data *game)
{
    size_t i;
    size_t row_length = ft_strlen(game->map[0]);

    if (game->map_rows < 2)
        error_msg(game, "Map must have at least two rows.\n", EXIT_FAILURE);

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

static char *trim_and_check_line(char *line, t_data *game)
{
    char *trimmed_line = ft_strtrim(line, "\r\n");
    if (!trimmed_line)
    {
        free(line);
        error_msg(game, "Memory allocation failed for trimmed line.\n", EXIT_FAILURE);
    }
    //printf("Trimmed line: '%s'\n", trimmed_line);
    return trimmed_line;
}

static int find_row_index(t_data *game)
{
    size_t row_index = 0;
    while (row_index < game->map_rows && game->map[row_index] != NULL)
        row_index++;

    if (row_index >= game->map_rows)
        error_msg(game, "Too many map rows.\n", EXIT_FAILURE);

    return row_index;
}
static void allocate_map_row(t_data *game, int row_index, char *trimmed_line)
{
    game->map[row_index] = ft_calloc(game->map_columns + 1, sizeof(char));
    if (!game->map[row_index])
    {
        free(trimmed_line);
        error_msg(game, "Memory allocation failed for map row.\n", EXIT_FAILURE);
    }
}
static void copy_line_to_map(t_data *game, int row_index, char *trimmed_line)
{
    size_t j = 0;
    size_t trimmed_length = strlen(trimmed_line);
    while (j < trimmed_length)
    {
        if (trimmed_line[j] == ' ')
        {
            game->map[row_index][j] = '1'; // Replace spaces with walls
        }
        else if (is_valid_char(game, trimmed_line[j]))
        {
            game->map[row_index][j] = trimmed_line[j]; // Copy valid characters
        }
        else
        {

            printf("Invalid character detected: '%c' at map[%d][%ld]\n", trimmed_line[j], row_index, j);
            free(trimmed_line);
            free_map(game);
            error_msg(game, "Invalid character in map line.\n", EXIT_FAILURE);
        }
        j++;
    }

    // Fill the remaining columns with '1' if trimmed_line is shorter
    while (j < game->map_columns)
    {
        game->map[row_index][j] = '1'; // Fill with walls
        j++;
    }
    game->map[row_index][j] = '\0'; // Null-terminate the row
}

void fill_map(t_data *game, char *line)
{
    char *trimmed_line;
    int row_index;

    trimmed_line = trim_and_check_line(line, game);
    free(line);
    if (game->map_rows <= 0)
    {
        free(trimmed_line);
        error_msg(game, "Map rows not set properly.\n", EXIT_FAILURE);
    }
    row_index = find_row_index(game);
    //printf("Debug: Fill map, row_index: %d\n", row_index);
    allocate_map_row(game, row_index, trimmed_line);
    copy_line_to_map(game, row_index, trimmed_line);
    free(trimmed_line);
}


static void get_map_line(t_data *game, char *line, int *map_flag)
{
    // Process only if it's a map line (starting with '1' or spaces)
    //printf("Debug: Get map line: '%s'\n", line);
    if ((line[0] == '1' || line[0] == ' ') && is_all_set(game))
    {
        //printf("map line : %s\n", line);
        *map_flag = 1;
        fill_map(game, line);
    }
    else
        free(line);
}
void process_map(t_data *game, const char *file)
{
    char *line;
    char *tmp_line;
    int map_flag;

    map_flag = 0;
    game->map = ft_calloc(game->map_rows, sizeof(char *));
    if (!game->map)
        error_msg(game, "Memory allocation failed for map.\n", EXIT_FAILURE);

    game->fd = open(file, O_RDONLY);
    if (game->fd < 0)
        error_msg(game, "Could not open map file.\n", EXIT_FAILURE);

    line = get_next_line(game->fd, 0);
    while (line != NULL)
    {
        if (is_empty_line(line) == true && map_flag == 1)
        {
            free(line);
            error_msg(game, "Empty line in map.\n", EXIT_FAILURE);
        }
        tmp_line = ft_strtrim(line, "\r\n");
        free(line);
        if (tmp_line == NULL)
            error_msg(game, "Memory allocation failed for trimmed line.\n", EXIT_FAILURE);
        //printf("Debug: Processed line: '%s'\n", tmp_line);
        get_map_line(game, tmp_line, &map_flag);
        line = get_next_line(game->fd, 0);
    }
    if (game->hero == 0)
        error_msg(game, "Player missing.\n", EXIT_FAILURE);
    close(game->fd);
    check_map_walls(game);
    error_msg(game, "Parsing done.\n", EXIT_SUCCESS);
}
