#include <memory>

#ifndef MAP_H
#define MAP_H

#pragma once

namespace customalgorithms
{
	/**
	* Map template class
	*/
	template <typename T1, typename T2>
	class Map
	{
	public:
		Map<T1, T2>( ){};
		Map<T1, T2>( Map<T1, T2>& _map );
		~Map<T1, T2>();
		T1& operator[](T2& key);
	private:

	};

	template <typename T1, typename T2>
	Map<T1, T2>::Map(Map<T1, T2>& _map)
	{
		
	}

	template <typename T1, typename T2>
	Map<T1, T2>::~Map( )
	{

	}
}

#endif // MAP_H
