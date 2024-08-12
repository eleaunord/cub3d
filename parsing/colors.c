#include "cub3d.h"

static void check_commas(t_data *game, char *line, int *i)
{
    int count;
    int start_index = *i; // Save the starting index

    //printf("i at the stqrt :%d\n", start_index);
    count = 0;
    while (line[*i] != '\0')
    {
        if (line[*i] == ',')
            count++;
        (*i)++;
    }
    //printf("comma count :%d\n", count);
    if (count != 2)
        error_msg(game, "Invalid color format.\n", EXIT_FAILURE);

    *i = start_index; // Reset *i to the original position
}

static void check_color_format(t_data *game, char *line, int *i, int *rgb)
{
    int j;

    check_commas(game, line, i);
    j = 0;
    while (line[*i] != '\0')
    {
        while (line[*i] != '\0' && is_space(line[*i]))
            (*i)++;
        // printf("Character: %c (ASCII: %d)\n", line[*i], line[*i]);
        // printf("Index: %d\n", *i);
        // printf("Line: %s\n", line);
        if (line[*i] == ',')
        {
            (*i)++;
            continue; // Move to the next character
        }
        if (!ft_isdigit(line[*i]))
        {
            //printf("Non-digit character detected: %c (ASCII: %d)\n", line[*i], line[*i]);
            error_msg(game, "Invalid color value digit.\n", EXIT_FAILURE);
        }

        while (line[*i] != '\0' && ft_isdigit(line[*i]))
        {
            rgb[j] = rgb[j] * 10 + (line[*i] - '0');
            (*i)++;
        }
        //printf("RGB[%d]:%d\n", j, rgb[j]);
        if (rgb[j] > 255 || rgb[j] < 0)
            error_msg(game, "Invalid color value.\n", EXIT_FAILURE);
        j++;
        if (j == 3 && line[*i] != '\0')
        {
            //printf("j :%d\n", j);
            error_msg(game, "Invalid color format.\n", EXIT_FAILURE);
        }
            
    }
    //printf("j at the end :%d\n", j);
    if (j != 3)
        error_msg(game, "Invalid color format.\n", EXIT_FAILURE);
}

void get_color_code(t_identifier color, char *line, t_data *game)
{
    int i;
    int rgb[3];
    int color_hex;

    rgb[0] = 0;
    rgb[1] = 0;
    rgb[2] = 0;
    if (is_already_loaded(game, color) == true)
        error_msg(game, "Color is already loaded.\n", EXIT_FAILURE);
    i = 1;
    while (line[i] != '\0' && is_space(line[i]))
        i++;
    check_color_format(game, line, &i, rgb);
    color_hex = (rgb[0] << 16) | (rgb[1] << 8) | rgb[2];
    if (color == F)
    {
        //printf("floor get color code");
        game->floor_color = color_hex;    
    }
          
    else if (color== C)
    {
        //printf("ceil get color code");
        game->ceiling_color = color_hex;
    }
       
}