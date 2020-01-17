#include "inc.h"
#include "list.h"
#include "element.h"
#include <stdlib.h>
#include <fcntl.h>

void print_str(void* str)
{
    putstr(str);
    putstr("\n");
}

int str_len(char* str)
{
    int len;
    
    len = 0;
    while (str[len] != '\0')
        len++;
    return (len);
}

int is_plus(char* str)
{
    if (*str == '+')
        return 1;
    return 0;
}

int is_implication(char* str)
{
    if (*str == '=' && *str + 1 == '>')
        return 1;
    return 0;
}

void reform_str(char* str)
{
    int counter1, counter2;
    
    for (counter1 = 0; str[counter1] != '\0'; counter1++)
    {
        if (is_implication(&str[counter1]))
        {
            for (counter2 = counter1; str[counter2] != '+' && counter2 != -1; counter2--) {}
            if (str[counter2 + 1] == '-')
            {
                deleteChar(str, counter1);
                str[counter1] = '+';
                deleteChar(str, counter2 + 1);
            } else {
                for (counter2 = counter1; str[counter2] != '+' && counter2 != -1; counter2--)
                    str[counter2 + 1] = str[counter2];
                str[counter2 + 1] = '-';
                str[counter1 + 1] = '+';
            }
        }
    }
}

t_list* listFromStr(char* str)
{
    int         charCounter, wordCharCounter;
    t_list*     list;
    char*       word;
    t_element*  data;
    int znak;
    int start;
    
    list = 0;
    word = 0;
    start = 0;
    wordCharCounter = 0;
    word = (char*)malloc(str_len(str) + 2);
    reform_str(str);
    if (str[0] == '-')
    {
        znak = 1;
        start++;
    } else
        znak = 0;
    for (charCounter = start; str[charCounter] != '\0'; charCounter++)
    {
        if (is_plus(&str[charCounter]))
        {
            data = (t_element*)malloc(sizeof(t_element));
            word[wordCharCounter] = '\0';
            data->name = word;
            data->znak = znak;
            znak = 0;
            list_push_back(&list, data);
            data = 0;
            wordCharCounter = 0;
            word = 0;
            word = (char*)malloc(str_len(str) + 2);
            if (str[charCounter + 1] == '-')
            {
                znak = (znak + 1) % 2;
                deleteChar(str, charCounter + 1);
            }
        } else {
            word[wordCharCounter] = str[charCounter];
            wordCharCounter++;
        }
    }
    data = (t_element*)malloc(sizeof(t_element));
    word[wordCharCounter] = '\0';
    data->name = word;
    data->znak = znak;
    list_push_back(&list, data);
    return list;
}

void print_element(t_list* list)
{
    if (((t_element*)list->data)->from1)
    {
        putnbr(((t_element*)list->data)->from1);
        putstr(" + ");
        putnbr(((t_element*)list->data)->from2);
        putstr(" -> ");
    }
    putnbr(((t_element*)list->data)->id);
    putstr(") ");
    while (list)
    {
        if (((t_element *)(list->data))->znak == 1)
            ft_putchar('-');
        putstr(((t_element *)(list->data))->name);
        if (list->next)
            putstr(" + ");
        list = list->next;
    }
    ft_putchar('\n');
}

void deleteDublicates(t_list *counter1)
{
    t_list *counter2;
    t_list *suiside;
    
    while (counter1)
    {
        counter2 = counter1;
        while (counter2->next)
        {
            if (ft_strcmp(((t_element*)(counter1->data))->name, ((t_element*)(counter2->next->data))->name) == 0 && ((t_element*)(counter1->data))->znak == ((t_element*)(counter2->next->data))->znak)
            {
                suiside = counter2->next;
                counter2->next = counter2->next->next;
                free(suiside->data);
                free(suiside);
            }
            else
                counter2 = counter2->next;
        }
        counter1 = counter1->next;
    }
}


void fillData(t_list* begin_list)
{
    t_list *counter_el;
    int counter;

    counter = 1;
    counter_el = begin_list;
    while (counter_el)
    {
        counter_el->data = listFromStr(counter_el->data);
        ((t_element*)((t_list*)counter_el->data)->data)->id = counter;
        ((t_element*)((t_list*)counter_el->data)->data)->from1 = 0;
        ((t_element*)((t_list*)counter_el->data)->data)->from2 = 0;
        deleteDublicates(counter_el->data);
        counter_el = counter_el->next;
        counter++;
    }
}

void printData(t_list* begin_list)
{
    t_list *counter_el1;

    counter_el1 = begin_list;
    while (counter_el1)
    {
        print_element(counter_el1->data);
        counter_el1 = counter_el1->next;
    }
}

t_list* merge(t_list* ad, t_list* ev, int curId)
{
    t_element* newElement;
    t_list* adam;
    t_list* eva;
    t_list* child;
    int add;
    
    adam = ad;
    child = 0;
    while(adam)
    {
        eva = ev;
        add = 1;
        while(eva)
        {
            if (ft_strcmp(((t_element*)(adam->data))->name, ((t_element*)(eva->data))->name) == 0 && ((t_element*)(adam->data))->znak != ((t_element*)(eva->data))->znak)
            {
                add = 0;
                break;
            }
            eva = eva->next;
        }
        if (add)
        {
            newElement = (t_element*)malloc(sizeof(t_element));
            newElement->name = ((t_element*)(adam->data))->name;
            newElement->znak = ((t_element*)(adam->data))->znak;
            list_push_back(&child, newElement);
            newElement = 0;
        }
        adam = adam->next;
    }
    
    eva = ev;
    while(eva)
    {
        adam = ad;
        add = 1;
        while(adam)
        {
            if (ft_strcmp(((t_element*)(eva->data))->name, ((t_element*)(adam->data))->name) == 0 && ((t_element*)(eva->data))->znak != ((t_element*)(adam->data))->znak)
            {
                add = 0;
                break;
            }
            adam = adam->next;
        }
        if (add)
        {
            newElement = (t_element*)malloc(sizeof(t_element));
            newElement->name = ((t_element*)(eva->data))->name;
            newElement->znak = ((t_element*)(eva->data))->znak;
            list_push_back(&child, newElement);
            newElement = 0;
        }
        eva = eva->next;
    }
    
    if (child)
    {
        ((t_element*)child->data)->id = curId;
        ((t_element*)child->data)->from1 = ((t_element*)ad->data)->id;
        ((t_element*)child->data)->from2 = ((t_element*)ev->data)->id;
    }
    
    return child;
}

int is_mergable(t_list* ad, t_list* ev)
{
    t_list* adam;
    t_list* eva;
    int     dif;
    
    dif = 0;
    adam = ad;
    while(adam)
    {
        eva = ev;
        while(eva)
        {
            if (ft_strcmp(((t_element*)(adam->data))->name, ((t_element*)(eva->data))->name) == 0 && ((t_element*)(adam->data))->znak != ((t_element*)(eva->data))->znak)
            {
                dif++;
            }
            eva = eva->next;
        }
        adam = adam->next;
    }
    
    eva = ev;
    while(eva)
    {
        adam = ad;
        while(adam)
        {
            if (ft_strcmp(((t_element*)(eva->data))->name, ((t_element*)(adam->data))->name) == 0 && ((t_element*)(eva->data))->znak != ((t_element*)(adam->data))->znak)
            {
                dif++;
            }
            adam = adam->next;
        }
        eva = eva->next;
    }
    
    if (dif == 2)
        return 1;
    return 0;
}

int same(t_list* first, t_list* second)
{
    int in;
    t_list* counter1;
    t_list* counter2;
    
    counter1 = first;
    counter2 = second;
    while (counter1 && counter2)
    {
        counter1 = counter1->next;
        counter2 = counter2->next;
    }
    if (counter1 != 0 || counter2 != 0)
        return 0;
    for (counter1 = first; counter1; counter1 = counter1->next)
    {
        in = 0;
        for (counter2 = second; counter2; counter2 = counter2->next)
            if (ft_strcmp(((t_element*)(counter1->data))->name, ((t_element*)(counter2->data))->name) == 0 && ((t_element*)(counter1->data))->znak == ((t_element*)(counter2->data))->znak)
                in = 1;
        if (!in)
            return 0;
    }
    return 1;
}


int is_in_list(t_list *data, t_list *new)
{
    t_list* counter;
    
    for (counter = data; counter; counter = counter->next)
        if (same(counter->data, new))
            return 1;
    return 0;
}

void count(t_list **list, t_list *statement)
{
    t_list* counter1;
    t_list* counter2;
    t_list* newEl;
    int curId;
    
    curId = list_size(*list);
    for (counter1 = *list; counter1; counter1 = counter1->next)
        for (counter2 = *list; counter2 != counter1; counter2 = counter2->next)
            if (is_mergable(counter1->data, counter2->data))
            {
                newEl = merge(counter1->data, counter2->data, ++curId);
                deleteDublicates(newEl);
                if (newEl && !is_in_list(*list, newEl))
                {
                    list_push_back(list, newEl);
                    if (same(newEl, statement))
                        return ;
                }
            }
}

void invert(char* str)
{
    int counter;
    
    if (str[0] == '-')
        deleteChar(str, 0);
    else
    {
        counter = str_len(str);
        while (--counter > -1)
            str[counter + 1] = str[counter];
        str[0] = '-';
    }
}

int list_consists_statement(t_list* list, t_list* statement)
{
    t_list *counter_el;

    counter_el = list;
    while (counter_el)
    {
        if (same(statement, counter_el->data))
            return ((t_element*)((t_list*)counter_el->data)->data)->id;
        counter_el = counter_el->next;
    }
    return 0;
}

void print_answer2_rec(t_list *list, int st, t_list **answer)
{
    t_list *counter_el;

    counter_el = list;
    while (counter_el)
    {
        if (st == ((t_element*)((t_list*)counter_el->data)->data)->id)
        {
            if (((t_element*)((t_list*)counter_el->data)->data)->from1)
            {
                print_answer2_rec(list, ((t_element*)((t_list*)counter_el->data)->data)->from1, answer);
                print_answer2_rec(list, ((t_element*)((t_list*)counter_el->data)->data)->from2, answer);
                list_push_back(answer, counter_el->data);
            }
            break;
        }
        counter_el = counter_el->next;
    }
}

void change_all_answer(t_list *answer, int old, int new)
{
    int counter;
    t_list *list_counter;
    
    counter = new;
    counter = new;
    for (list_counter = answer; list_counter && counter; list_counter = list_counter->next)
        if (((t_element*)((t_list*)(list_counter->data))->data)->from1 == old)
            ((t_element*)((t_list*)(list_counter->data))->data)->from1 = new;
        else if (((t_element*)((t_list*)(list_counter->data))->data)->from2 == old)
            ((t_element*)((t_list*)(list_counter->data))->data)->from2 = new;
        else if (((t_element*)((t_list*)(list_counter->data))->data)->id == old)
            ((t_element*)((t_list*)(list_counter->data))->data)->id = new;
}

int count_base(t_list *list)
{
    int answer;
    
    answer = 1;
    while (list && ((t_element*)((t_list*)(list->data))->data)->from1 == 0)
    {
        answer++;
        list = list->next;
    }
    return answer;
}

void print_answer2(t_list *list, int st)
{
    t_list *list_counter;
    t_list *answer;
    int counter;
    
    answer = 0;
    counter = count_base(list);
    print_answer2_rec(list, st, &answer);
    list_counter = answer;
    while(list_counter)
    {
        if (((t_element*)((t_list*)(list_counter->data))->data)->id != counter)
            change_all_answer(answer, ((t_element*)((t_list*)(list_counter->data))->data)->id, counter);
        list_counter = list_counter->next;
        counter++;
    }
    printData(answer);
}

void get_file_data(t_list **list, char *fname)
{
    int        fl;
    int        size;
    char    buf[1];
    char    *word;
    int     len;
    int     st;

    st = 0;
    len = 0;
    size = 1;
    fl = open(fname, O_RDONLY);
    if (fl < 0)
        return ;
    while (size)
    {
        size = read(fl, buf, 1);
        len++;
    }
    close(fl);
    word = (char*)malloc(len * 2 + 1);
    len = 0;
    size = 1;
    fl = open(fname, O_RDONLY);
    while (size)
    {
        size = read(fl, buf, 1);
        if (buf[0] == '\n')
        {
            word[len] = '\0';
            word[len + 1] = '\0';
            list_push_back(list, (word + st));
            st = len + 2;
            len++;
        } else
            word[len] = buf[0];
        len++;
    }
    close(fl);
}

void machine_input(t_list** list, int argc, char** argv)
{
    int counter;
    int frp;
    
    frp = 1;
    counter = 0;
    while (++counter < argc - 1)
        if (ft_strcmp(argv[counter], "--f"))
            list_push_back(list, ft_strdup(argv[counter]));
        else
        {
            frp = 0;
            get_file_data(list, argv[++counter]);
        }
    if (frp)
        list_push_front(list, ft_strdup(argv[counter]));
}

int main(int argc, char *argv[])
{
    t_list* list;
    t_list* statement;
    int ans;
    
    list = 0;
    if (argc > 1)
        machine_input(&list, argc, argv);
    else
        user_input(&list);
    statement = listFromStr(list->data);
    invert(list->data);
    fillData(list);
    printData(list);
    if (!list_consists_statement(list, statement))
        count(&list, statement);
    ans = list_consists_statement(list, statement);
    if (ans)
    {
        print_answer2(list, ans);
        putstr("1 + ");
        putnbr(list_consists_statement(list, statement));
        putstr(" -> 0\n");
    }
    else
        print_str("false");
    clear_list_of_lists(&list);
    list_clear(&statement);
    return (0);
}
