#pragma once
#include <deque>
#include <map>
#include <vector>
#include <list>
#ifndef NiFrameVector_h__
#define NiFrameVector_h__

namespace nfe
{
	template < typename T >
	struct vector
	{
		typedef typename std::vector<T> type;
		typedef typename std::vector<T>::iterator iterator;
		typedef typename std::vector<T>::const_iterator const_iterator;
		typedef typename std::vector<T>::reverse_iterator reverse_iterator;
		typedef typename std::vector<T>::const_reverse_iterator const_reverse_iterator;
	};

	template < typename Key, typename Value >
	struct map
	{
		typedef typename std::map< Key, Value > type;
		typedef typename std::map< Key, Value >::iterator iterator;
		typedef typename std::map< Key, Value >::const_iterator const_iterator;
		typedef typename std::map< Key, Value >::reverse_iterator reverse_iterator;
		typedef typename std::map< Key, Value >::const_reverse_iterator const_reverse_iterator;
	};

	template < typename T >
	struct list
	{
		typedef typename std::list<T> type;
		typedef typename std::list<T>::iterator iterator;
		typedef typename std::list<T>::const_iterator const_iterator;
		typedef typename std::list<T>::reverse_iterator reverse_iterator;
		typedef typename std::list<T>::const_reverse_iterator const_reverse_iterator;
	};

	template < typename T >
	struct deque
	{
		typedef typename std::deque<T> type;
		typedef typename std::deque<T>::iterator iterator;
		typedef typename std::deque<T>::const_iterator const_iterator;
		typedef typename std::deque<T>::reverse_iterator reverse_iterator;
		typedef typename std::deque<T>::const_reverse_iterator const_reverse_iterator;
	};
}

#endif // NiFrameVector_h__