#pragma once


#ifndef LAB_STACK
#define LAB_STACK


#include <iostream>
#include <QDebug>
#include <QString>
#define START_ALLOC 8

template<typename T>
class stack {
private:
	T *arr_data;
	int curr, allocated;

	void increaseCapacity();
public:
	stack();
	~stack();

	void push(const T& item);
	T pop();
	int count();
    int find(const T& search_item);
	friend std::ostream & operator<<(std::ostream & out, const stack<T> &container);
    friend const QDebug & operator<<(const QDebug & out, const stack<T> &container);
    QString print();
};


template<typename T>
void stack<T>::increaseCapacity() {
	T *new_memory = new T[allocated * 2];
	for (int i = 0; i <= curr; i++)
		new_memory[i] = arr_data[i];
	delete[] arr_data;
	arr_data = new_memory;
	allocated *= 2;
}

template<typename T>
stack<T>::stack() {
	arr_data = new T[START_ALLOC];
	curr = -1;
	allocated = START_ALLOC;
}

template<typename T>
stack<T>::~stack() {
	delete[] arr_data;
}

template<typename T>
void stack<T>::push(const T& item) {
	if (curr + 1 == allocated)
		increaseCapacity();
	arr_data[++curr] = item;
}

template<typename T>
T stack<T>::pop() {
	if (curr == -1)
		return T();
	return arr_data[curr--];
}

template<typename T>
int stack<T>::count() {
	return curr + 1;
}

template<typename T>
int stack<T>::find(const T& search_item) {
	for (int i = 0; i <= curr; i++) {
		if (search_item == arr_data[i])
			return i;
	}
	return -1;
}

template<typename T>
std::ostream & operator<<(std::ostream & out, const stack<T> &container) {
	for (int i = 0; i < container.curr; i++)
		out << container.arr_data[i] << ' ';
	out << container.arr_data[container.curr];
	return out;
}

template<typename T>
const QDebug & operator<<(const QDebug & out, const stack<T> &container) {
//    for (int i = 0; i < container.curr; i++)
//        out << container.arr_data[i] << ' ';
//    out << container.arr_data[container.curr];
    return out;
}

template<typename T>
QString stack<T>::print() {
    QString str;
    QTextStream stream(&str);
    for (int i = 0; i < curr; i++)
        stream << arr_data[i] << ' ';
    stream << arr_data[curr];
    Q_ASSERT(stream.string() != nullptr);
    return str;
}


#endif // !LAB_STACK

