#include <memory>

#ifndef NODE_H
#define NODE_H

using namespace std;

namespace customalgorythms
{
    /**
     * Class Node is used as a base class for all custom data structures
     * Using tamplate possible to instantiate Node for any stadart type e.g Node<double>
     */
	template <typename T>
	class Node
	{

	public:
		Node<T>();
        Node<T>(T);
        Node<T>(const Node<T> &);
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
    Node<T>::Node(T val)
        : value(val),
        prev(NULL),
        next(NULL)
    {
    }

    template <typename T>
    Node<T>::~Node()
    {
        //delete this->prev;
        //delete this->next;
        //delete &this->value;
    }

    template <typename T>
    Node<T>::Node(const Node<T>& node)
    {
        this->value = node.value;
        this->next = node.next;
        this->prev = node.prev;
    }

    /**
     * Method setValue() is used for assigning certain value to node cell
     * @param typename value
     */
	template <typename T>
	void Node<T>::setValue(T val)
	{
		this->value = val;
	}

    /**
     * Method getValue() is used for getting current node value
     * @returns value as an object
     */
	template <typename T>
	T Node<T>::getValue()
	{
		return this->value;
	}

    /**
     * Get previous node
     * @returns pointer to previous node
     */
	template <typename T>
	Node<T>* Node<T>::getPreviousNode()
	{
		return this->prev;
	}

    /**
     * Get next node
     * @returns pointer to next node
     */
	template <typename T>
	Node<T>* Node<T>::getNextNode()
	{
		return this->next;
	}

    /**
     * Set previous node
     * @param pointer to node
     */
	template <typename T>
	void Node<T>::setPreviousNode(Node<T>* node)
	{
		this->prev = node;
	}

    /**
     * Set next node
     * @param pointer to node
     */
	template <typename T>
	void Node<T>::setNextNode(Node<T>* node)
	{
		this->next = node;
	}

}

#endif // NODE_H
