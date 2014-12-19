#include <memory>

#ifndef NODE_H
#define NODE_H

using namespace std;

namespace customalgorithms
{
    /**
     * Class Node is used as a base class for all custom data structures
     * Using template possible to instantiate Node for any standard type e.g Node<double>
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
		Node<T>* getNextNode() const;
		Node<T>* getPreviousNode() const;
		void setValue(const T);
		T getValue();
		bool operator==(const Node<T>&);

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
	inline bool Node<T>::operator==(const Node<T>& other)
	{
		return other.value == this->value;
	}

    template <typename T>
    Node<T>::~Node()
    {
    }

    template <typename T>
    Node<T>::Node(const Node<T>& node)
    {
        value = node.value;
        next = node.next;
        prev = node.prev;
    }

    /**
     * Method setValue() is used for assigning certain value to node cell
     * @param typename value
     */
	template <typename T>
    void Node<T>::setValue(T val)
	{
        value = val;
	}

    /**
     * Method getValue() is used for getting current node value
     * @returns value as an object
     */
	template <typename T>
	T Node<T>::getValue()
	{
		return value;
	}

    /**
     * Get previous node
     * @returns pointer to previous node
     */
	template <typename T>
	Node<T>* Node<T>::getPreviousNode() const
	{
		return prev;
	}

    /**
     * Get next node
     * @returns pointer to next node
     */
	template <typename T>
	Node<T>* Node<T>::getNextNode() const
	{
		return next;
	}

    /**
     * Set previous node
     * @param pointer to node
     */
	template <typename T>
	void Node<T>::setPreviousNode(Node<T>* node)
	{
		prev = node;
	}

    /**
     * Set next node
     * @param pointer to node
     */
	template <typename T>
	void Node<T>::setNextNode(Node<T>* node)
	{
		next = node;
	}
}

#endif // NODE_H
