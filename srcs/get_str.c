#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int        getchar(void)
{
    char    buf[1];
    char    *bufp;
    int        i;

    i = read(0, buf, 1);
    bufp = buf;
    if (--i >= 0)
    {
        return (*bufp++);
    }
    return (-1);
}

char    *clone_valika(char *str, int size)
{
    char    *new_str;
    int        counter;

    counter = 0;
    new_str = (char*)malloc(size * 2 * sizeof(char));
    while (counter < size)
    {
        new_str[counter] = str[counter];
        counter++;
    }
    free(str);
    return (new_str);
}

char    *get_str(void)
{
    char    *str;
    int        str_size;
    int        counter;

    counter = 0;
    str_size = 1;
    str = (char*)malloc(sizeof(char));
    str[0] = getchar();
    while (str[counter] != '\n')
    {
        counter++;
        if (counter >= str_size)
        {
            str = clone_valika(str, str_size);
            str_size = str_size * 2;
        }
        str[counter] = getchar();
    }
    str[counter] = '\0';
    return (str);
}
