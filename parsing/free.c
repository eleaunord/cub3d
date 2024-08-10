#include "cub3d.h"

void free_array(char **str)
{
    int i;

    if (!str)
        return;
    i = -1;
    while (str[++i])
        free(str[i]);
    free(str);
}