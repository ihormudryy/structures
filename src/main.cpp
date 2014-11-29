#include <iostream>
#include "../include/linkedlist/linkedlist.h"
#include "../include/node/node.h"

using namespace customalgorythms;
using namespace std;

int main()
{
    Node<int>* current_node = new Node<int>();
    current_node->setValue(101);
    cout << (current_node->getValue() == 101);
    for (int i = 0; i < 10; i++)
    {
        Node<int>* new_node = new Node<int>();
        Node<int>* copy_node_ptr = new Node<int>();
        copy_node_ptr = current_node;
        new_node->setValue(i);
        new_node->setPreviousNode(copy_node_ptr);
        copy_node_ptr->setNextNode(new_node);
        current_node = new_node;
    }
    Node<int>* m_node = current_node->getPreviousNode();
    while (m_node->getPreviousNode() != NULL)
    {
        m_node = m_node->getPreviousNode();
        cout << m_node->getValue() << ", ";
    }

    cout << endl;

    LinkedList<int> list;
    for (int i = 0; i < 20; i++)
    {
        list.add(i % 5);
    }

    do
    {
        cout << list.get() << ", ";
    } while (list.next());

    cout << endl << endl << "Size "<< list.getSize() << endl;

    list.remove(7);
    list.remove(3);
    cout << endl << endl << "Size "<< list.getSize() << endl;
    do
    {
        cout << list.get() << ", ";
    } while (list.prev());

    list.remove(2, true);
    cout << endl << endl << "Size " << list.getSize() << endl;
    do
    {
        cout << list.get() << ", ";
    } while (list.next());

    do
    {
    } while (list.prev());

    list.addBefore(100, 1);
    cout << endl << endl << "Size " << list.getSize() << endl;
    do
    {
        cout << list.get() << ", ";
    } while (list.next());

    cout << endl << endl ;
    do
    {
        cout << list.get() << ", ";
    } while (list.prev());

    list.addAfter(1000001, 4);
    cout << endl << endl << "Size " << list.getSize() << endl;
    do
    {
        cout << list.get() << ", ";
    } while (list.next());

    cout << endl << endl ;
    do
    {
        cout << list.get() << ", ";
    } while (list.prev());

    return 0;
}

