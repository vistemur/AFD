#include "inc.h"

void user_input(t_list** input_list)
{
    int enterf;
    
    enterf = 1;
    while (enterf)
    {
        putstr("enter str: ");
        list_push_back(input_list, get_str());
        putstr("enter another formula? (y/n)\n");
        if (get_str()[0] != 'y')
            enterf = 0;
    }
    putstr("enter statement: ");
    list_push_front(input_list, get_str());
}
