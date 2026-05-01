#include <cstddef>
#include <tuple>
#include <utility>

template <class T> struct BiTree
{
	T val;
	BiTree<T>* lt, * rt, * parent;
};
enum class Dir { fall_left, parent }; // эти типо как мы идем по дереву (тип перехода)
template <class T>
std::pair <size_t, BiTree<T>*> fall_left(BiTree<T>* root)
{
	size_t path = 0;
	while (root->lt)
	{
		root = root->lt;
		path++;
	}
	return { path, root };
}
template <class T>
std::pair <size_t, BiTree<T>*> parent(BiTree<T>* root)
{
	size_t path = 0;
	if (!root)
	{
		return { path,nullptr };
	}
	BiTree<T>* parent = root->parent;
	while (parent && parent->lt != root) // пока не найдем родителя и у него текущий узел находится слева
	{
		root = parent; // текущий узел делаем родителем
		parent = root->parent; // поднимаемся выше по родителю
		path++;
	}
	return { path, parent };
}
template<class T>
std::tuple<Dir, size_t , BiTree<T>*>nextStruct(BiTree<T>* root)
{
	if (!root)
	{
		return { Dir::parent, 0, nullptr };
	}
	if (root->rt)
	{
		auto result = fall_left(root->rt);
		return { Dir::fall_left, result.first, result.second }; // возвращаем тип перехода, длину и найденный узел
	}
	auto result = parent(root);
	return { Dir::parent, result.first, result.second };
}
template<class T>
bool isEqualStruct(BiTree<T>* lhs, BiTree<T>* rhs)
{
	auto lhs_begin = fall_left(lhs);
	auto rhs_begin = fall_left(rhs);
	if (lhs_begin.first != rhs_begin.first)
	{
		return false;
	}
	auto result = isEqualStructStart(lhs_begin.second, rhs_begin.second);
	return !std::get<0>(result)&& !std::get<1>(result);
}
template <class T>
bool includedStructStart(BiTree<T>* lhs_root, BiTree<T>* pattern)
{
	auto next_pattern = nextStruct(pattern);
	std::pair<size_t, BiTree<T>*> next_lhs;
	if (std::get<0>(next_pattern) == Dir::fall_left)
	{
		next_lhs = fall_left(lhs_root);
		if (std::get<0>(next_pattern) == Dir::fall_left)
		{
			next_lhs = fall_left(lhs_root);
		}
		else {
			next_lhs = parent(lhs_root);
		}
		while (std::get<1>(next_pattern) == std::get<1>(next_lhs))
		{
			next_pattern = nextStruct(std::get<2>(next_pattern));
			if (std::get<0>(next_pattern) == Dir::fall_left)
			{
				if (next_lhs.second->rt)
				{
					next_lhs = fall_left(next_lhs.second->rt);
				}
				else {
					return false;
				}
			}
			else {
				next_lhs = parent(next_lhs.second);
			}
		}
	}
	return !std::get<2>(next_pattern) && std::get<1>(next_pattern) == next_lhs.first;
}
template <class T>
bool includedStruct(BiTree<T>* lhs, BiTree<T>* pattern)
{
	pattern = fall_left(pattern).second;
	lhs = fall_left(lhs).second;
	while (lhs)
	{
		if (includedStructStart(lhs, pattern))
		{
			return true;
		}
		lhs = std::get <2> (nextStruct(lhs));
	}
	return false;
}

template <class T>
std::tuple<BiTree<T>*, BiTree<T>*,bool> isEqualStructIt(BiTree<T> * pattern_begin, BiTree<T>* pattern_end, BiTree<T> * tocheck);
