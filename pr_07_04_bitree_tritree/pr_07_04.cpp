template <class T>
struct BiTree
{
  T val;
  BiTree<T> *lt, *rt, *parent;
};
template <class T>
BiTree<T>* minimum(BiTree<T> * root)
{
  if(!root)
  {
    return root;
  }
  while (root -> left)
  {
    root = root - left;
  }
  return root;
}
template<class T, class F>
F traverse (BiTree<T>* root, F f)
{
  if (!root)
  {
    return f;
  }
  root = minimum(root);
  BiTree<T> next = minimum(root);
  while (next)
  {
    f(next -> val);
    if (next -> rt)
    {
      next = next -> rt;
      next = minimum(next);
    }
    else
    {
      BiTree<T> * parent = next -> parent;
      while (parent && parent -> lt != next)
      {
        next = parent;
        parent = next -> parent;
      }
      next = parent;
    }
  }
  return f;
}
template <class T>
struct BiTreeIt
{
  BiTreeIt<T> * curr;
};
template <class T>
T & value (BiTreeIt<T> it)
{
  return it.curr -> val;
}
template <class T>
BiTreeIt<T> next(BiTreeIt<T> it)
{
  BiTreeIt<T>* next = it.curr;
  if (next -> rt)
  {
    next = next -> rt;
    next = minimum(next);
  }
  else
  {
    BiTree<T> * parent = next -> parent;
    while (parent && parent -> lt != next)
    {
      next = parent;
      parent = next -> parent;
    }
    next = parent;
  }
  return {next};
}
template <class T>
BiTree<T>* maximum(BiTree<T> * root)
{
  if(!root)
  {
    return root;
  }
  while (root -> rt)
  {
    root = root - rt;
  }
  return root;
}
template <class T>
BiTreeIt<T> prev(BiTreeIt<T> it)
{
  BiTreeIt<T>* next = it.curr;
  if (next -> lt)
  {
    next = next -> lt;
    next = maximum(next);
  }
  else
  {
    BiTree<T> * parent = next -> parent;
    while (parent && parent -> rt != next)
    {
      next = parent;
      parent = next -> parent;
    }
    next = parent;
  }
  return {next};
}
template <class T>
bool hasNwxt (BiTreeIt<T> it)
{
  return next(it).curr;
}
template <class T>
bool hasPrev (BiTreeIt<T> it)
{
  return prev(it).curr;
}
template <class T>
struct TriTree
{
  T val0, val1;
  TriTree<T> * lt,* rt, * mid,* parent;
};
template <class T>
struct TriTreeIt
{
  size_t s;
  TriTree<T> * curr;
};
template <class T>
T& value (TriTree<T> it)
{
  if (it.s == 0)
  {
    return it.curr -> val0;
  }
  return it.curr -> val1;
}
template <class T>
TriTree<T>* maximum(BiTree<T> * root)
{
  if(!root)
  {
    return root;
  }
  while (root -> rt)
  {
    root = root - rt;
  }
  return root;
}
template <class T>
TriTree<T>* minimum(BiTree<T> * root)
{
  if(!root)
  {
    return root;
  }
  while (root -> left)
  {
    root = root - left;
  }
  return root;
}
template <class T>
TriTreeIt<T> next(TriTreeIt<T> it)
{
  TriTree<T> * next = it.curr;
  size_t ind = it.s;
  if(!next)
  {
    return it;
  }
  if ( ind == 0)
  {
    if (next -> mid)
    {
      next = next -> mid;
      next = minimum(next);
      ind = 0;
    }
    else
    {
      ind = 1;
    }
  }
  else
  {
    if(next ->rt)
    {
      next = next -> rt;
      next = minimum(next);
      ind = 0;
    }
    else
    {
      TriTree<T> * parent = next -> parent;
      while (parent)
      {
        if(parent -> lt == next)
        {
          ind = 0;
          break;
        }
        if(parent -> mid == next)
        {
          ind = 1;
          break
        }
        next = parent;
        parent = next -> parent;
      }
      next = parent;
    }
  }
  return {ind, next};
}
template <class T>
TriTreeIt<T> prev (TriTreeIt<T> it)
{
  TriTree<T> * next = it.curr;
  size_t ind = it.s;
  if(!next)
  {
    return it;
  }
  if ( ind == 1)
  {
    if (next -> mid)
    {
      next = next -> mid;
      next = maximum(next);
      ind = 1;
    }
    else
    {
      ind = 1;
    }
  }
  else
  {
    if(next ->lt)
    {
      next = next -> lt;
      next = maximum(next);
      ind = 1;
    }
    else
    {
      TriTree<T> * parent = next -> parent;
      while (parent)
      {
        if(parent -> rt == next)
        {
          ind = 1;
          break;
        }
        if(parent -> mid == next)
        {
          ind = 0;
          break
        }
        next = parent;
        parent = next -> parent;
      }
      next = parent;
    }
  }
  return {ind, next};
}
template <class T>
bool hasNext (TriTreeIt<T> it)
{
  return next(it).curr;
}
template <class T>
bool hasPrev(TriTreeIt<T> it)
{
  return prev(it).curr;
}
