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
	if (!root)
	{
		return { path, nullptr };
	}
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
std::tuple<BiTree<T>*, BiTree<T>*, bool> isEqualStructStart(BiTree<T>* lhs_start, BiTree<T>* rhs_start)
{
	auto ln = nextStruct(lhs_start);
	auto rn = nextStruct(rhs_start);
	while (std::get<0>(ln) == std::get<0>(rn) &&
		std::get<1>(ln) == std::get<1>(rn) &&
		std::get<2>(ln) && std::get<2>(rn))
	{
		ln = nextStruct(std::get<2>(ln));
		rn = nextStruct(std::get<2>(rn));
	}
	bool dir = std::get<0>(ln) == std::get<0>(rn);
	return { std::get<2>(ln), std::get<2>(rn), dir };
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
	return !std::get<0>(result) && !std::get<1>(result);
}
template <class T>
bool includedStruct(BiTree<T>* lhs, BiTree<T>* pattern)
{
	BiTree<T>* pattern_begin = fall_left(pattern).second;
	BiTree<T>* lhs_curr = fall_left(lhs).second;
	while (lhs_curr)
	{
		auto result = isEqualStructStart(lhs_curr, pattern_begin);
		if (!std::get<1>(result) && std::get<2>(result))
		{
			return true;
		}
		lhs_curr = std::get<2>(nextStruct(lhs_curr));
	}
	return false;
}

template <class T>
BiTree<T>* prev(BiTree<T>* curr)
{
	if (!curr)
	{
		return nullptr;
	}
	BiTree<T>* next = curr;
	if (next->lt)
	{
		next = next->lt;
		while (next->rt)
		{
			next = next->rt;
		}
		return next;
	}
	BiTree<T>* parent = next->parent;
	while (parent && parent->rt != next)
	{
		next = parent;
		parent = next->parent;
	}
	return parent;
}

template <class T>
std::pair<BiTree<T>*, BiTree<T>*> inclusionStart(BiTree<T>* lhs_start, BiTree<T>* pattern)
{
	BiTree<T>* pattern_begin = fall_left(pattern).second;
	BiTree<T>* lhs_curr = lhs_start;
	while (lhs_curr)
	{
		auto result = isEqualStructStart(lhs_curr, pattern_begin);
		if (!std::get<1>(result) && std::get<2>(result))
		{
			BiTree<T>* last_lhs_next = std::get<0>(result);
			if (!last_lhs_next)
			{
				BiTree<T>* lhs_end = lhs_curr;
				while (lhs_end->rt)
				{
					lhs_end = lhs_end->rt;
				}
				return { lhs_curr, lhs_end };
			}
			BiTree<T>* lhs_end = prev(last_lhs_next);
			return { lhs_curr, lhs_end };
		}
		lhs_curr = std::get<2>(nextStruct(lhs_curr));
	}
	return { nullptr, nullptr };
}

template <class T>
std::pair<BiTree<T>*, BiTree<T>*> inclusion(BiTree<T>* lhs, BiTree<T>* pattern)
{
	return inclusionStart(fall_left(lhs).second, pattern);
}

template <class T>
struct InclusionIt
{
	std::pair<BiTree<T>*, BiTree<T>*> incl;
};

template <class T>
InclusionIt<T> begin(BiTree<T>* lhs, BiTree<T>* pattern)
{
	return { inclusion(lhs, pattern) };
}

template <class T>
InclusionIt<T> next(InclusionIt<T> curr, BiTree<T>* pattern)
{
	if (!curr.incl.first)
	{
		return curr;
	}
	BiTree<T>* search_start = std::get<2>(nextStruct(curr.incl.first));
	return { inclusionStart(search_start, pattern) };
}

template <class T>
bool hasNext(InclusionIt<T> curr, BiTree<T>* pattern)
{
	return next(curr, pattern).incl.first;
}
