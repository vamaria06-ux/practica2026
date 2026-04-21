template <class T> struct BiTree
{
	T val;
	BiTree<T>* lt, * rt, * parent;
};
enum Dir {fall_left, parent};
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
	if (!root)
	{
		return { path,nullptr };
	}
	size_t path = 0;
	BiTree<T> parent = root->parent;
	while (parent && parent->lt != root)
	{
		root = parent;
		parent = root->parent;
		path++;
	}
	return { path, parent };
}
template<class T>
std::tuple<Dir, size_t , BiTree<T>*>nextStruct(BiTree<T>* root)
{
	if (root->rt)
	{
		auto result = fall_left(root->rt);
		return { Dir::fall_left, result.first, result.second };
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
	auto ln = nextStruct(lhs_begin.second);
	auto rn = nextStruct(rhs_begin.second);
	while (std::get<0>(ln) == std::get<0>rn && std::get<1> rn == std::get<1> (ln) && std::get<2>(ln)&& std::get<2>(rn))
	{
		ln = nextStruct(std::get<2>(ln));
		rn = nextStruct(std::get<2>(rn));

	}
	return ln == rn;
}

template <class T>
bool includedStructStart(BiTree<T>* lhs_root, BiTree<T>* pattern)
{
	auto next_patern = nextStruct(pattern);
	std::pair<size_t, BiTree<T>*> next_lhs;
	if (std::get<0>(next_pattern) == Dir::fall_left)
	{
		next_lhs = fall_left(lhs_root);
		if (std::get<1>(next_pattern) == Dir::fall_left)
		{
			next_lhs = fall_left(lhs_root);
		}
		else {
			next_lhs = parent(lhs_root);
		}
		while (std::get<1>(next_pattern) == std::get<1>(next_lhs))
		{
			next_pattern = nextStruct(std::get<2>(next_pattern));
			if (std::get<1>(next_pattern) == Dir::fall_left)
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
		if (includedstructStart(lhs, pattern)
		{
			return true;
		}
		lhs = std::get <2> (nextStruct(lhs));
	}
	return false;
}

template <class T>
std::tuple<BiTree<T>*, BiTree<T>*,bool> isEqualStructIt(BiTree<T> * pattern_begin, BiTree<T>* pattern_end, BiTree<T> * tocheck);