/* ============================================================================== */
/* 								error handling									  */
/* ============================================================================== */
// typename because T is dependent
template <typename T>
int no_dup_seq(T const &container)
{
	T tmp(container);
	typename T::const_iterator ite = tmp.end();
	// fast random access
	std::sort(tmp.begin(), tmp.end());
	// bidirectional sequential access
	//tmp.sort();

	typename T::const_iterator elem = std::adjacent_find(tmp.begin(), tmp.end());
	// ite is returned if no identical pairs are found
	int no_dup = (elem == ite);
	if (no_dup == FALSE)
	{
		std::ostringstream dup_strm;
		dup_strm << *elem;
		FORMAT_ERR("Duplicate found: " + dup_strm.str());
		//throw std::invalid_argument("Duplicate found: " + dup_strm.str());
	}

	return (no_dup);
}

template <typename T>
int is_sorted_seq(T const &container)
{
	typename T::const_iterator ite = container.end();
	typename T::const_iterator elem = std::adjacent_find(container.begin(), container.end(), std::greater<int>());

	// ite is returned if container is sorted
	int sorted = (elem == ite);
	if (sorted)
		FORMAT_ERR("Sequence is sorted.");
		//throw std::invalid_argument("Sequence is sorted.");

	return (sorted);
}

/* ============================================================================== */
/* 						ford-johnson merge insertion function					  */
/* ============================================================================== */
template <typename T>
int is_odd(T const &container)
{
	size_t container_size = container.size();
	int odd = (container_size % 2 != 0);

	return (odd);
}

template <typename P, typename T>
P group_pairs(T const &container)
{
	int_pair tmp_pair;
	P ret_pair;

	for (typename T::const_iterator it = container.begin(); it != container.end(); it++)
	{
		int fir = *it;
		it++;
		int sec = *it;
		tmp_pair = std::make_pair(fir, sec);
		ret_pair.push_back(tmp_pair);
	}

	return (ret_pair);
}

template <typename P>
void sort_descending(P &container_pairs)
{
	for (typename P::iterator it = container_pairs.begin(); it != container_pairs.end(); it++)
	{
		//if (it->second > it->first)
		//	std::swap(it->second, it->first);
		if (it->second > it->first)
		{
			int tmp = it->first;
			it->first = it->second;
			it->second = tmp;
		}
	}
}

// merge sort (refer to top-down implementation using lists)
// (source: https://en.wikipedia.org/wiki/Merge_sort)
template <typename P>
void merge_sort(P &container_pairs)
{
	size_t n = container_pairs.size();
	if (n <= 1)
		return ;

	//typename P::const_iterator it = container_pairs.begin();
	typename P::iterator it = container_pairs.begin();
	size_t distance_to_mid = n / 2;
	std::advance(it, distance_to_mid);

	P half_left(container_pairs.begin(), it);
	merge_sort(half_left);

	P half_right(it, container_pairs.end());
	merge_sort(half_right);

	merge(half_left, half_right, container_pairs);
}

// can't check if halves are empty because pop_front (member function of list but not vector) is required
// front member functions are present in both
// would require using advance to shift the iterator by one (increment / to the right)
// must then access only the first elem on each iteration of the loop
// requires an iterator but fails to check if halves are empty regardless because there is no way to pop_front a vector unless the half is reassigned each time which seems unnecessary and unintelligent
template <typename P>
void merge(P const &left, P const &right, P &container_pairs)
{
	container_pairs.clear();

	typename P::const_iterator it_l = left.begin();
	typename P::const_iterator it_r = right.begin();

	while (it_l != left.end() && it_r != right.end())
	{
		if (it_l->first < it_r->first)
		{
			container_pairs.push_back(*it_l);
			it_l++;
		}
		else
		{
			container_pairs.push_back(*it_r);
			it_r++;
		}
	}

	for (; it_l != left.end(); it_l++)
		container_pairs.push_back(*it_l);
	for (; it_r != right.end(); it_r++)
		container_pairs.push_back(*it_r);
}

template <typename T, typename P>
T create_sorted_seq(P const &container_pairs)
{
	T sorted_seq;

	typename P::const_iterator it = container_pairs.begin();

	if (it != container_pairs.end())
		sorted_seq.push_back(it->second);
	for (; it != container_pairs.end(); it++)
		sorted_seq.push_back(it->first);

	return (sorted_seq);
}

template <typename T, typename P>
//T create_pend_seq(P container_pairs)
T create_pend_seq(P const &container_pairs)
{
	T pending;

	//typename P::iterator it = std::next(container_pairs.begin());
	typename P::const_iterator it = container_pairs.begin();
	std::advance(it, 1);

	for (; it != container_pairs.end(); it++)
		pending.push_back(it->second);

	return (pending);
}

template <typename T>
void insert_pend_into_sorted(T &sorted, T &pend)
{
	// get pend using jacobsthal using pend size
		// iterate until jacobsthal-th index in pend
	// insert into sorted using binary search

	while (1)
	{
		size_t n = pend.size();
		int index = PmergeMe::generate_jacobsthal_seq(n);
		// if index is out of container bounds
		if (index >= static_cast<int>(n))
			break ;

		typename T::iterator to_insert = pend.begin();
		std::advance(to_insert, index);
		sorted.insert(std::lower_bound(sorted.begin(), sorted.end(), *to_insert), *to_insert);
	}

	for (typename T::iterator it = pend.begin(); it != pend.end(); it++)
		sorted.insert(std::lower_bound(sorted.begin(), sorted.end(), *it), *it);
}

/*
template <typename T>
typename T::iterator binary_search(T &container, size_t n, int target) 
{
	std::cout << AC_MAGENTA << "target: " << target
			  << AC_NORMAL << std::endl;

	typename T::iterator it = container.begin();
	typename T::iterator ite = container.end();
	while (it != ite)
	{
		typename T::iterator elem = container.begin();
		typename T::iterator itm = container.begin();
		std::advance(itm, n / 2);
		for (; elem != itm; elem++)
			;
		// search through the right
		if (*elem < target)
			it = ++itm;
		// search through the left
		else if (*elem > target)
			ite = --itm;
		else
			return (itm);
		it++;
	}
	return (container.end());
}
*/

/* ============================================================================== */
/* 									temporary helper							  */
/* ============================================================================== */
	/*
	//for (size_t i = 0; i < vec_pair.size(); i++)
	for (std::vector<int_pair>::iterator it = vec_pair.begin(); it != vec_pair.end(); it++)
	{
		//std::cout << vec_pair[i].first << ", " << vec_pair[i].second << std::endl;
		//std::cout << vec_pair.at(i).first << ", " << vec_pair.at(i).second << std::endl;
		std::cout << it->first << ", " << it->second << std::endl;
	}
	*/
	/*
	for (std::list<int_pair>::iterator it = lst_pair.begin(); it != lst_pair.end(); it++)
	{
		std::cout << it->first << ", " << it->second << std::endl;
	}
	*/
template <typename P>
void print_pair(P const &container)
{
	for (typename P::const_iterator it = container.begin(); it != container.end(); it++)
	{
		std::cout << "[ " << it->first << ", " << it->second << " ]" << std::endl;
	}
}
