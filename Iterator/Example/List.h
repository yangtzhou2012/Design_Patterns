#ifndef _LIST_H_
#define _LIST_H_

#include "LinearStruct.h"

template <typename T>
class ListIterator;

template <typename T>
struct Node
{
	T data;
	Node *prev;
	Node *next;

	Node() : prev(this), next(this) {}
};

template <typename T>
class List : public LinearStruct<T>
{
public:
	List();
	virtual ~List();

	virtual bool PushFront(const T &item);
	virtual bool PopFront(void);
	virtual bool PushBack(const T &item);
	virtual bool PopBack(void);

	virtual T* Front(void);
	virtual const T* Front(void) const;
	virtual T* Back(void);
	virtual const T* Back(void) const;

	virtual int Size(void) const;

	virtual ListIterator<T>* CreateIterator(void);

protected:
	Node<T> *head;
	int count;

private:
	bool Init(void);

	friend class ListIterator<T>;
};

template <typename T>
class ListIterator : public LinearIterator<T>
{
public:
	ListIterator(const List<T> *l);

	virtual void First(void);
	virtual void Next(void);
	virtual bool IsDone(void);
	virtual T* CurrentItem(void);

protected:
	const List<T> *list;
	Node<T> *current;
};

template <typename T>
List<T>::List()
{
	Init();
}

template <typename T>
List<T>::~List()
{
	if (head) {
		Node<T> *p1 = head->prev;
		Node<T> *p2 = NULL;

		while (p1 != head) {
			p2 = p1->prev;
			delete p1;
			p1 = p2;
		}
		delete head;
	}
}

template <typename T>
bool List<T>::Init(void)
{
	head = new Node<T>;
	count = 0;
	return (head ? true : false);
}

template <typename T>
bool List<T>::PushFront(const T &item)
{
	if (head) {
		Node<T> *insItem = new Node<T>;

		if (insItem) {
			Node<T> *first = head->next;
			insItem->data = item;
			head->next = insItem;
			insItem->prev = head;
			first->prev = insItem;
			insItem->next = first;
			count++;
			return true;
		}
	}

	return false;
}

template <typename T>
bool List<T>::PopFront(void)
{
	if (head) {
		Node<T> *first = head->next;

		if (first != head) {
			Node<T> *second = first->next;
			head->next = second;
			second->prev = head;
			delete first;
			count--;
			return true;
		}
	}

	return false;
}

template <typename T>
bool List<T>::PushBack(const T &item)
{
	if (head) {
		Node<T> *insItem = new Node<T>;

		if (insItem) {
			Node<T> *tail = head->prev;
			insItem->data = item;
			tail->next = insItem;
			insItem->prev = tail;
			head->prev = insItem;
			insItem->next = head;
			count++;
			return true;
		}
	}

	return false;
}

template <typename T>
bool List<T>::PopBack(void)
{
	if (head) {
		Node<T> *tail = head->prev;

		if (tail != head) {
			Node<T> *tail2 = tail->prev;
			tail2->next = head;
			head->prev = tail2;
			delete tail;
			count--;
			return true;
		}
	}

	return false;
}

template <typename T>
T* List<T>::Front(void)
{
	if (head) {
		Node<T> *first = head->next;
		if (first != head)
			return &(first->data);
	}

	return NULL;
}

template <typename T>
const T* List<T>::Front(void) const
{
	if (head) {
		Node<T> *first = head->next;
		if (first != head)
			return &(first->data);
	}

	return NULL;
}

template <typename T>
T* List<T>::Back(void)
{
	if (head) {
		Node<T> *tail = head->prev;
		if (tail != head)
			return &(tail->data);
	}

	return NULL;
}

template <typename T>
const T* List<T>::Back(void) const
{
	if (head) {
		Node<T> *tail = head->prev;
		if (tail != head)
			return &(tail->data);
	}

	return NULL;
}

template <typename T>
int List<T>::Size(void) const
{
	return count;
}

template <typename T>
ListIterator<T>* List<T>::CreateIterator(void)
{
	return (new ListIterator<T>(this));
}

template <typename T>
ListIterator<T>::ListIterator(const List<T> *l) : list(l), current(NULL)
{
	if (list && list->head)
		current = list->head->next;
}

template <typename T>
void ListIterator<T>::First(void)
{
	if (list && list->head)
		current = list->head->next;
	else
		current = NULL;
}

template <typename T>
void ListIterator<T>::Next(void)
{
	current = current->next;
}

template <typename T>
bool ListIterator<T>::IsDone(void)
{
	if (list && list->head)
		return (current == list->head ? true : false);
	else
		return true;
}

template <typename T>
T* ListIterator<T>::CurrentItem(void)
{
	if (!IsDone() && current)
		return &(current->data);
	else
		return NULL;
}

#endif // _LIST_H_
