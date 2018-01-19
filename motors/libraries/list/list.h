#ifndef LIST_H
# define LIST_H

# define list_for_each(list) for(; list; list = list->get_next())

template <class T>
class List
{
public:
    List(T elem);
    void push_back(T elem);
    List<T>* get_next();
    T* get_elem();
private:
    List<T>* next;
    T elem;
};

# include "list.hxx"
#endif
