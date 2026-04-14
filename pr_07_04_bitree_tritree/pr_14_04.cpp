template <class T>
struct BiTree
{
  T val;
  BiTree<T> *lt, *rt, * parent;
};
// next. hasnext, fall_left
template <class T>
BiTree<T>* fall_left(BiTree<T>* r)
{
  if (!r)
  {
    return r;
  }
  while (r -> lt)
  {
    r = r->lt;
  }
  return r;
}
template <class T, class Cmp>
bool isEqual(BiTree<T>* lhs, BiTree<T>* rhs, Cmp cmp)
{
  if (!rhs && !lhs) return true;
  if (!rhs || !lhs) return false; // лучше это вынести в отдельную функцию
  assert(rhs&&lhs);
  BiTree<T>* blhs = fall_left(lhs);
  BiTree<T>* brhs = fall_left(rhs);
  while (hasNext(blhs) && hasNext(brhs)) // пока есть след эл у обоих деревьев
  {
    if (!equal(cmp, blhs -> val, brhs -> val)) // не равны деревья
    {
      return false;
    }
    blhs = next(blhs);
    brhs = next(brhs);
  }
  return !hasNext(blhs) && !hasNext(brhs);
}
// Входит ли одно дерево в другое
template <class T, class Cmp>
bool included(BiTree<T> * origin, BiTree<T>* rhs) // проверяем входит лм rhs в origin, потом можно переиспользовать
{
  if (!rhs) return true; // если дерево пустое, то оно входит
  if (!origin) return false;
  BiTree<T> * brhs = fall_left(rhs);
  BiTree<T>* b = find(origin, brhs -> val, cmp);
  return isEqualRange(brhs, brhs -> val,b, cmp);
}
template <class T,class Cmp>
BiTree<T> * find (BiTree<T> * r, T val, Cmp cmp);
template<class T, class Cmp>
bool isEqual (BiTree<T>* lhs, BiTree<T>* rhs, Cmp cmp)
{
  BiTree<T> * b1 = fall_left(lhs);
  BiTree<T> * b2 = fall_legt(rhs);
  return isEqualRange(b1, nullptr, b2, cmp);
}
template <class T, class Cmp>
bool isEqualRange (BiTree<T> * b1, BiTree<T> * e1, BiTree<T> * b2, Cmp cmp)
{
  while (b1 != e1 && hasNext(b2))
  {
    if (!equal(b1 -> val,b2 -> val,cmp)) return false;
    b1 = next(b1);
    b2 = next(b2);
  }
  return (b1 == e1);
}