#pragma once

#include <iostream>
template <typename T>
class List
{
	struct Node;

public:
    template <typename ItemType>
    class TemplateIterator;
    using iterator = TemplateIterator<T>;
    using const_iterator = TemplateIterator<const T>;

public:
	List();
	~List();
	
	iterator begin();
	iterator end();
	const_iterator begin() const;
	const_iterator end() const;
	
	int size() const;
	void clear();
	void append(const T& value);
	void print() const;

private:
	int m_size = 0;
	Node* m_head = nullptr;
	Node* m_tail = nullptr;
};

template <typename T>
struct List<T>::Node
{
	Node(Node* next = nullptr, Node* prev = nullptr);
	Node(const T& value, Node* next = nullptr, Node* prev = nullptr);

	T value;
	Node* next = nullptr;
	Node* prev = nullptr;
};


template <typename T>
template <typename ItemType>
class List<T>::TemplateIterator
{
public:
    using value_type = ItemType;
    using reference = ItemType&;
    using pointer = ItemType*;
    using iterator_category = std::bidirectional_iterator_tag;
    using difference_type = int;
    
    TemplateIterator(Node* node);
    
    ItemType& operator*();
    const ItemType& operator*() const;
    TemplateIterator operator++();
    TemplateIterator operator--();
    TemplateIterator operator++(int);
    TemplateIterator operator--(int);
    bool operator==(const TemplateIterator& other) const;
    bool operator!=(const TemplateIterator& other) const;

protected:
    Node* m_node = nullptr;
};


