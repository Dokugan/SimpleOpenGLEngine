#pragma once
#include <vector>

template <typename T>
bool FindInVector(std::vector<T>* collection, T value)
{
	typename std::vector<T>::iterator it = std::find(collection->begin(), collection->end(), value);
	if (it != collection->end())
	{
		return true;
	}
	return false;
}
