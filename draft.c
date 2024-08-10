// texture
void get_textures_and_colors(char *line, t_data *game)
{

    // north 
    if (line && line[0] == 'N' && line[1] == 'O')
        ft_path_texture(line, &game->no, game, 2);
    // south 
    else if (line && line[0] == 'S' && line[1] == 'O')
        ft_path_texture(line, &game->so, game, 2);
    // west 
    else if (line && line[0] == 'E' && line[1] == 'A')
        ft_path_texture(line, &game->ea, game, 2);
    // east 
    else if (line && line[0] == 'W' && line[1] == 'E')
        ft_path_texture(line, &game->we, game, 2);
    // floor 
    else if (line && line[0] == 'F')
        ft_path_texture(line, &game->floor, game, 1);
    // floor
    else if (line && line[0] == 'C')
        ft_path_texture(line, &game->ceiling, game, 1);
    else if (line && line[0] != 'N' && line[0] != 'S' && line[0] != 'E' && line[0] != 'W' && line[0] != 'F' && line[0] != 'C')
        game->error = 2;
}