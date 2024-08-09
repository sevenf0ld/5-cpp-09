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
template <typename T>
void print_pair(T const &container)
{
	for (typename T::const_iterator it = container.begin(); it != container.end(); it++)
	{
		std::cout << "[ " << it->first << ", " << it->second << " ]" << std::endl;
	}
}
