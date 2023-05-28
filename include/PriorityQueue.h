#pragma once

#include <iostream>
#include <list>
#include <concepts>
#include <exception>


/*
* templated comperator for the priority queue
*/
template <typename T>
struct Comparator {
	/*
	* a-b > 0 --> a > b
	* a-b = 0 --> a = b
	* a-b < 0 --> a < b
	*/
	T operator()(const T& a, const T& b) const {
		return a - b;
	}
};


template <typename T>
class PriorityQueue {
   
public:

	/*
	* push an element into the queue
	* param elem: the element to be pushed
	*/
	void push(const T& elem)
	{
		// iterator to the first element of the queue
		// first element represents the highest priority
		auto it = m_pqueue.cbegin();

		// find the right position to insert elem based on the comparator
		while (it != m_pqueue.cend() && m_comparator(elem, *it) > 0) {
			++it;
		}
		m_pqueue.insert(it, elem);
	}

	/*
	* poll the first element from the queue (highest priority)
	* return the polled element or throw an exception if the queue is empty
	*/
	T poll()
	{
		if (m_pqueue.empty()) {
			throw std::out_of_range("Priority queue is empty!");
		}
		T top_priority = m_pqueue.front();
		m_pqueue.pop_front();
		return top_priority;
	}

private:
	std::list<T> m_pqueue;
	Comparator<T> m_comparator;
};
