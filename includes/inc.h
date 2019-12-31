#ifndef INC_H
# define INC_H

# include "list.h"

t_list        *create_elem(void *data);
void    list_push_back(t_list **begin_list, void *data);
void    list_push_front(t_list **begin_list, void *data);
void    list_clear(t_list **begin_list);
void    list_foreach(t_list *begin_list, void (*f)(void *));
int        list_size(t_list *begin_list);
int     ft_putchar(char c);
void    putstr(char *str);
void    putnbr(int nb);
int     getchar(void);
char    *get_str(void);
int     ft_strcmp(char *s1, char *s2);
void    deleteChar(char* str, int pos);
void    user_input(t_list** input_list);
void    clear_list_of_lists(t_list** begin_list);
char    *ft_strdup(char *src);

#endif
