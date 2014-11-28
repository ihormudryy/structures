#include <memory>

#ifndef NODE_H
#define NODE_H

using namespace std;

namespace customalgorythms
{
	
	template <typename T>
	class Node
	{

	//typedef unique_ptr<Node<T>> unique_ptr<Node<T>>;

	public:
		Node<T>();
        Node<T>(Node<T> &);
        ~Node<T>();
		void setNextNode(Node<T>*);
		void setPreviousNode(Node<T>*);
		Node<T>* getNextNode();
		Node<T>* getPreviousNode();
		void setValue(const T);
		T getValue();

	private:
		T value;
		Node<T>* next;
		Node<T>* prev;
	};

	template <typename T>
    Node<T>::Node()
		: value(NULL),
		prev(NULL),
		next(NULL)
	{
	}

    template <typename T>
    Node<T>::~Node()
    {
        //delete this->prev;
        //delete this->next;
        delete &this->value;
    }

    template <typename T>
    Node<T>::Node(Node<T>& node)
    {
        this->value = node.value;
        this->next = node.next;
        this->prev = node.prev;
    }

	template <typename T>
	void Node<T>::setValue(T val)
	{
		this->value = val;
	}

	template <typename T>
	T Node<T>::getValue()
	{
		return this->value;
	}

	template <typename T>
	Node<T>* Node<T>::getPreviousNode()
	{
		return this->prev;
	}

	template <typename T>
	Node<T>* Node<T>::getNextNode()
	{
		return this->next;
	}

	template <typename T>
	void Node<T>::setPreviousNode(Node<T>* node)
	{
		this->prev = node;
	}

	template <typename T>
	void Node<T>::setNextNode(Node<T>* node)
	{
		this->next = node;
	}

}

#endif // NODE_H
