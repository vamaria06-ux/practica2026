/*
template <class T>
struct List 
{
  T val;
  List<T>* next;
};
template <class T>
struct Vec 
{
  T* data;
  size_t s;
};

template <class T>
void clear(List<Vec<T>>* h)
{
  while (h)
  {
    delete[] h -> val.data; // в val лежит указатель на data vec удаление динамической памяти внутри вектора
    List<Vec<T>>* temp = h;
    h = h-> next;
    delete temp;
  }
};

template <class T>
Vec<T> copy(const Vec<T> &v)
{
  Vec<T> new_v; // создание нового вектора
  new_v.data = nullptr; // ???
  try
  {
    new_v.data = new T[v.s]; // выделение памяти для вектора данных исключение 
    for (size_t i = 0; i < v.s; ++i)
    {
      new_v.data[i] = v.data[i]; // искл оператор копир присваивание
    }
    new_v.s = v.s;
  } catch(...)
  {
    delete[] new_v.data;
    throw;
  }
  return new_v;
  
};

template <class T>
List<Vec<T>>* copy(const List<Vec<T>>* h) 
{
  if (!h)
  {
    return nullptr;
  }
  List<Vec<T>>* head = new List<Vec<T>> { copy(h ->val), nullptr}; // полная копия первого элемента 
  try
  {
    List<Vec<T>>* node = head;
    while(h ->next)
    {
      node -> next = new List<Vec<T>> {copy(h->next->val, nullptr)};
      h = h-next;
      node = node ->next;
    }
  }
  catch(const std::bad_alloc &)
  {
    clear(head);
    throw;
  }
  return head;
};

//базовая гарантия
template <class T>
struct List 
{
  T val;
  List<T>* next;
};
template <class T>
struct Vec 
{
  T* data;
  size_t s;
  cap; // объем выдел элементов
};


// строгая гарантия конвертация 
template <class T>
struct List 
{
  T val;
  List<T>* next;
};
template <class T>
struct Vec 
{
  T* data;
  size_t s;
  cap; // объем выдел элементов
};
// имитация итераторов с помощью методов
template<class T>
List<T>* next(List<T>* node)
{
  return node -> next;
};

template<class T>
bool hasNext(List<T>* node)
{
  return node->next != nullptr;
};

template<class T>
Vec<List<T>* > convert(List<Vec<T>>* h)
{

};
// пернос
*/
//задача
#include <cstddef>
template <class T>
struct List 
{
  T val;
  List<T>* next;
};
template <class T>
struct Vec 
{
  T* data;
  size_t s, cap; 
};

template <class T>
Vec<List<T>*> balanced_copy(Vec<List<T>*> v, size_t k)
{

};
