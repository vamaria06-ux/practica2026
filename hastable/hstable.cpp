#include <cstddef>
template <class Key, class T, class Hash, class Equal>
struct HasTable
{
  using Value = std::pair<Key,T>;
  size_t size;
  size_t capacity;
  Value ** slots; // массив из указателей на данных
};
template <class K, class T, class HS, class EQ>
size_t psl(const HasTable<K,T,HS,EQ>& table,typename HasTable<K,T,HS,EQ>::Value** value)
{
  Hash hasher;
  szie_t home - hasher(*value->fisrt) % table.capacity;
  size_t ind = value - table.slots;
  if (ind > home)
  {
    return ind - home;
  }
  return table.capacyty - (home - ind);
}
template <class K, class T,, class Hash, class Equal>
typename HashTable<K,T,Hash,Equal>::Value** find (const HashTable)