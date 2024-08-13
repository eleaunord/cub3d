#include "cub3d.h"

void get_textures_and_colors(char *line, t_data *game)
{
    if (line && line[0] == 'N' && line[1] == 'O')
        get_path_to_texture(N, line, game);
    else if (line && line[0] == 'S' && line[1] == 'O')
        get_path_to_texture(S, line, game);
    else if (line && line[0] == 'E' && line[1] == 'A')
        get_path_to_texture(E, line, game);
    else if (line && line[0] == 'W' && line[1] == 'E')
        get_path_to_texture(W, line, game);
    else if (line && line[0] == 'F')
        get_color_code(F, line, game);
    else if (line && line[0] == 'C')
        get_color_code(C, line, game);
    else if (line && line[0] != 'N' && line[0] != 'S' && line[0] != 'E' && line[0] != 'W' && line[0] != 'F' && line[0] != 'C')
        error_msg(game, "Invalid identifier format.\n", EXIT_FAILURE);
}

bool is_all_set(t_data *game)
{
    // if (game->we == NULL)
    //     printf("Debug: WE texture is not set\n");
    // if (game->ea == NULL)
    //     printf("Debug: EA texture is not set\n");
    // if (game->so == NULL)
    //     printf("Debug: SO texture is not set\n");
    // if (game->ceiling_color == 0)
    //     printf("Debug: Ceiling color is not set\n");
    // if (game->floor_color == 0)
    //     printf("Debug: Floor color is not set\n");

    if (game->we != NULL && game->ea != NULL && game->so != NULL && game->ceiling_color != 0 && game->floor_color != 0)
        return (true);
    else
        return (false);
}

void get_map_size(t_data *game, char *line)
{
    size_t line_len;

    line_len = ft_strlen(line);
    if (line_len > game->map_columns)
        game->map_columns = line_len;
    game->map_rows++;
}

static void process_file_line(t_data *game, char *line)
{
    game->line = NULL;

    if ((line[0] == '1' || line[0] == ' ') && is_all_set(game))
    {
        get_map_size(game, line);
    }
    if (ft_strchr(line, '.') || ft_strchr(line, ','))
        game->line = ft_strtrim(line, " \t\r");
    free(line);
    if (game->line)
    {
        //printf("Debug: Processing line: %s\n", game->line);
        get_textures_and_colors(game->line, game);
        free(game->line);
        game->line = NULL;
    }
}

void parse_file(t_data *game, const char *file)
{
    char *line;
    char *tmp_line;

    line = NULL;
    game->fd = open(file, O_RDONLY);
    if (game->fd < 0)
        error_msg(game, "Could not open map file.\n", EXIT_FAILURE);
    line = get_next_line(game->fd, 0);
    while (line != NULL)
    {
        tmp_line = ft_strtrim(line, "\r\n");
        if (tmp_line == NULL)
            error_msg(game, "Memory allocation failed for trimmed line.\n", EXIT_FAILURE);
        //printf("Debug: Read line: %s\n", tmp_line);
        free(line);
        process_file_line(game, tmp_line);
        line = get_next_line(game->fd, 0);
    }
    close(game->fd);
    if (is_all_set(game) == false)
        error_msg(game, "Missing elements in map file.\n", EXIT_FAILURE);
    process_map(game, file);
}
