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