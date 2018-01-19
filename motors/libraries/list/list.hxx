#include "list.h"

template <class T>
List<T>::List(T elem)
{
    next = NULL;
    this->elem = elem;
}

template <class T>
void List<T>::push_back(T elem)
{
    List *cur_list = this;
    while (cur_list->next)
        cur_list = cur_list->next;
    cur_list->next = new List<T>(elem);
}

template <class T>
List<T>* List<T>::get_next()
{
    return next;
}

template <class T>
T* List<T>::get_elem()
{
    return &elem;
}
