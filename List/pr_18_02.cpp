#include <cstddef>
template <class T>
struct Vector {
  T* data ;
  size_t s ;
};

template <class T>
struct VecIt {
  T* data;
  size_t s, i;
};

template <class T>
VecIt<T> begin (VecIt<T> v)
{
  return {v.data, v.s, 0}
};
template <class T>
bool hasNext (VecIt<T> it)
{
  return it.s != it.i;
};

template <class T>
VecIt<T> next (VecIt<T> it)
{
  it.i++;
  return it; // копия итератор по значению
};

template <class T>
T& value(VecIt<T> it) // перегрузка *??
{
  it.i;
  return it.data[it.i];
};

template <class T>
VecIt<T> begin (Vec<T> v)
{
  return {v.data, v.s}
};
template <class T>
bool hasNext (VecIt<T> it)
{
  return it.s; // ? почему it.s != it.i
};
   
template <class T>
VecIt<T> next (VecIt<T> it)
{
  it.data++; it.s--;
  return it; 
};

template <class T>
T& value(VecIt<T> it) 
{
  return *(it.data);
};
template <class T>
VecIt<T> end(VecIt<T> v)
{
  return {v.data + v.s; 0}
};

template <class T>
struct VecRIt {
  T* data;
  size_t s, i;
};

template <class T>
VecRIt<T> rbegin(Vec<T> v)
{
  return {v.data; v.s; v.s};
};
template<class T>
T& value(VecRIt<T> it)
{
  return it.data[it.i-1;];
};

template <class T>
bool hasPrev(VecRIt<T> it)
{
  return it.i;
};

template <class T>
VecRIt<T> prev(VecRIt<T> it)
{
  it.i--;
  return it;
};

// двунаправленный итератор
template <class T>
struct List{
  T val;
  List<T> *next;
};
template <class T>
size_t size(const List<T>* h)
{
  size_t count = 0;
  while (h)
  {
    ++count;
    h = h->hext;
  }
};

template<class T>
void clear (List<T>* h)
{
  while(h)
  {
    List<T>* n = h->next;
    delete h;
    h = n;
  }
};

template <class T>
size_t size(const List<T*>* h)
{
  size_t count = 0;
  while (h)
  {
    count += h -> val ? 1:0;
    h = h->hext;
  }
};
template<class T>
void clear (List<T*>* h)
{
  while(h)
  {
    List<T*>* n = h->next;
    delete h -> val;
    delete h;
    h = n;
  }
};

template <class T>
size_t size (const List <const List <T> *>* h)
{
  size_t count = 0;
  while (h)
  {
    count += size<T>(h -> val);
    h = h -> next;
  }
  return count;
}

template <class T>
void clear (const List <const List <T> *>* h )
{
  while (h)
  {
    clear<T>(h -> val);
    List < List <T>*>* n = h -> next;
    delete h;
    h = n;
  }
}

template <class T>
struct List {
  T val; List<T>* next;
};
template <class T>
struct Vec
{
  T* data;
  size_t size;
};

template<class T>
size_t size(Vec <const List <T>*> v)
{
  size_t count = 0;
  for ( size_t i=0; i < v.size; ++i)
  {
    count += size<T>(v.data[i]);
  }
  return count;
};
template <class T>
void clear (Vec <List <T> *> v)
{
  for (sizi_t i =0; i< v.size; ++i)
  {
    clear<T>(v.data[i]);
  }
};

