// typename because T is dependent
template <typename T>
int no_dup_seq(T const &container)
{
	T tmp(container);
	typename T::const_iterator ite = tmp.end();
	std::sort(tmp.begin(), tmp.end());
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
int	is_sorted_seq(T const &container)
{
	typename T::const_iterator ite = container.end();
	typename T::const_iterator elem = std::adjacent_find(container.begin(), container.end(), std::greater<int>());

	// ite is returned if container is sorted
	int sorted = (elem == ite);
	if (sorted)
		FORMAT_ERR("Sequence is sorted.");

	return (sorted);
}
