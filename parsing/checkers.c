
#include "cub3d.h"

bool is_valid_char(t_data *game, char c)
{
    if (ft_strchr("01NSEW", c))
    {
        if (ft_isalpha(c))
        {
            if (game->hero > 0)
            {
                printf("Multiple hero positions found!\n");
                return (false);
            }
            game->hero++;
             //printf("game hero : %d\n", game->hero);
        }
        return (true);
    }
    //printf("Invalid character detected: %c\n", c);
    return (false);
}

bool check_args(int argc, const char **argv)
{
    int i;
    const char *extension;

    if (argc != 2 || !argv || !(argv[1]))
        return (false);
    extension = argv[1];
    i = ft_strlen(extension);
    if (i < 5)
        return (false);
    if (!(extension[i - 1] == 'b' &&
          extension[i - 2] == 'u' &&
          extension[i - 3] == 'c' &&
          extension[i - 4] == '.'))
        return (false);
    return (true);
}

bool is_already_loaded(t_data *game, t_identifier elem)
{
    if (elem == N && game->no)
        return (true);
    else if (elem == S && game->so)
        return (true);
    else if (elem == W && game->we)
        return (true);
    else if (elem == E && game->ea)
        return (true);
    else if (elem == F && game->floor_color != -1)
        return (true);
    else if (elem == C && game->ceiling_color != -1)
        return (true);
    return (false);
}

int is_xpm(char *path)
{
    int len;
    char *filename;

    filename = ft_strrchr(path, '/');
    if (filename)
        filename++;
    else
        filename = path;
    len = ft_strlen(filename);
    if (len <= 4 || ft_strcmp(filename + len - 4, ".xpm") != 0)
        return (1);
    return (0);
}
int is_space(char c)
{
    if (c == ' ' || (c >= 9 && c <= 13))
        return (1);
    return (0);
}

bool is_empty_line(char *line)
{
    while (*line != '\0')
    {
        // Check for spaces, tabs, newline, and carriage return
        if (*line != ' ' && *line != '\t' && *line != '\n' && *line != '\r')
            return (false);
        line++;
    }
    return (true);
}
