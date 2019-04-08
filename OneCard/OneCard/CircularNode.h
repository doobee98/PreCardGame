#pragma once
#include <deque>

template <typename T>
class CircularNode {
private:
	T data;
public:
	CircularNode<T>* prev;
	CircularNode<T>* next;

	CircularNode<T>(T data);
	operator T();
};

template <typename T>
CircularNode<T>::CircularNode<T>(T data) :
	data(data), prev(NULL), next(NULL) {}

template <typename T>
CircularNode<T>::operator T() {
	return data;
}