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


    if (game->we != NULL && game->ea != NULL && game->so != NULL &&
        game->ceiling_color != 0 && game->floor_color != 0)
        return (true);
    else
        return (false);
}

void get_map_size(t_data *game, char *line)
{
    int line_len;

    line_len = ft_strlen(line);
    if (line_len > game->map_columns)
        game->map_columns = line_len;
    game->map_rows++;
}
static void process_file_line(t_data *game, char *line)
{
    game->line = NULL;
    if (ft_strchr(line, '.') || ft_strchr(line, ','))
        game->line = ft_strtrim(line, " \t\r");
    get_textures_and_colors(game->line, game);
    game->line_tmp = NULL;
    if (game->line)
        free(game->line);
    else if ((line[0] == '1' || line[0] == ' ') && is_all_set(game))
        get_map_size(game, line);
    else if (!is_empty_line(line))
    {
        //printf("Invalid line detected: '%s'\n", line);
        free(line);
        close(game->fd);
        error_msg(game, "Invalid line in input.\n", EXIT_FAILURE);
    }
    free(line);
}

void parse_file(t_data *game, const char *file)
{
    char *line;
    char *tmp_line;

    line = NULL;
    game->fd = open(file, O_RDONLY);
    if (game->fd < 0)
        error_msg(game, "Could not open map file.\n", EXIT_FAILURE);
    line = get_next_line(game->fd);
    
    while (line != NULL)
    {
        //printf("line : %s\n", tmp_line);
        tmp_line = ft_strtrim(line, "\r\n");
        //printf("temp : %s\n", tmp_line);
        free(line);
        process_file_line(game, tmp_line);
        line = get_next_line(game->fd);
    }
    close(game->fd);
    if (!is_all_set(game))
         error_msg(game, "Missing textures or colors in map file.\n", EXIT_FAILURE);
    // parse_map(game, file);
}
