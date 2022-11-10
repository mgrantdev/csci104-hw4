#ifndef BST_H
#define BST_H

#include <iostream>
#include <exception>
#include <cstdlib>
#include <utility>
#include <stack>

/**
 * A templated class for a Node in a search tree.
 * The getters for parent/left/right are virtual so
 * that they can be overridden for future kinds of
 * search trees, such as Red Black trees, Splay trees,
 * and AVL trees.
 */
template <typename Key, typename Value>
class Node
{
public:
    Node(const Key &key, const Value &value, Node<Key, Value> *parent);
    virtual ~Node();

    const std::pair<const Key, Value> &getItem() const;
    std::pair<const Key, Value> &getItem();
    const Key &getKey() const;
    const Value &getValue() const;
    Value &getValue();

    virtual Node<Key, Value> *getParent() const;
    virtual Node<Key, Value> *getLeft() const;
    virtual Node<Key, Value> *getRight() const;

    void setParent(Node<Key, Value> *parent);
    void setLeft(Node<Key, Value> *left);
    void setRight(Node<Key, Value> *right);
    void setValue(const Value &value);

protected:
    std::pair<const Key, Value> item_;
    Node<Key, Value> *parent_;
    Node<Key, Value> *left_;
    Node<Key, Value> *right_;
};

/*
  -----------------------------------------
  Begin implementations for the Node class.
  -----------------------------------------
*/

/**
 * Explicit constructor for a node.
 */
template <typename Key, typename Value>
Node<Key, Value>::Node(const Key &key, const Value &value, Node<Key, Value> *parent) : item_(key, value),
                                                                                       parent_(parent),
                                                                                       left_(NULL),
                                                                                       right_(NULL)
{
}

/**
 * Destructor, which does not need to do anything since the pointers inside of a node
 * are only used as references to existing nodes. The nodes pointed to by parent/left/right
 * are freed by the BinarySearchTree.
 */
template <typename Key, typename Value>
Node<Key, Value>::~Node()
{
}

/**
 * A const getter for the item.
 */
template <typename Key, typename Value>
const std::pair<const Key, Value> &Node<Key, Value>::getItem() const
{
    return item_;
}

/**
 * A non-const getter for the item.
 */
template <typename Key, typename Value>
std::pair<const Key, Value> &Node<Key, Value>::getItem()
{
    return item_;
}

/**
 * A const getter for the key.
 */
template <typename Key, typename Value>
const Key &Node<Key, Value>::getKey() const
{
    return item_.first;
}

/**
 * A const getter for the value.
 */
template <typename Key, typename Value>
const Value &Node<Key, Value>::getValue() const
{
    return item_.second;
}

/**
 * A non-const getter for the value.
 */
template <typename Key, typename Value>
Value &Node<Key, Value>::getValue()
{
    return item_.second;
}

/**
 * An implementation of the virtual function for retreiving the parent.
 */
template <typename Key, typename Value>
Node<Key, Value> *Node<Key, Value>::getParent() const
{
    return parent_;
}

/**
 * An implementation of the virtual function for retreiving the left child.
 */
template <typename Key, typename Value>
Node<Key, Value> *Node<Key, Value>::getLeft() const
{
    return left_;
}

/**
 * An implementation of the virtual function for retreiving the right child.
 */
template <typename Key, typename Value>
Node<Key, Value> *Node<Key, Value>::getRight() const
{
    return right_;
}

/**
 * A setter for setting the parent of a node.
 */
template <typename Key, typename Value>
void Node<Key, Value>::setParent(Node<Key, Value> *parent)
{
    parent_ = parent;
}

/**
 * A setter for setting the left child of a node.
 */
template <typename Key, typename Value>
void Node<Key, Value>::setLeft(Node<Key, Value> *left)
{
    left_ = left;
}

/**
 * A setter for setting the right child of a node.
 */
template <typename Key, typename Value>
void Node<Key, Value>::setRight(Node<Key, Value> *right)
{
    right_ = right;
}

/**
 * A setter for the value of a node.
 */
template <typename Key, typename Value>
void Node<Key, Value>::setValue(const Value &value)
{
    item_.second = value;
}

/*
  ---------------------------------------
  End implementations for the Node class.
  ---------------------------------------
*/

/**
 * A templated unbalanced binary search tree.
 */
template <typename Key, typename Value>
class BinarySearchTree
{
public:
    BinarySearchTree();
    virtual ~BinarySearchTree();
    virtual void insert(const std::pair<const Key, Value> &keyValuePair);
    virtual void remove(const Key &key);
    void clear();
    void clearSubtree(Node<Key, Value> *n);
    Node<Key, Value> *insertHelper(Node<Key, Value> *n, const std::pair<const Key, Value> &keyValuePair);
    bool isBalanced() const;
    void print() const;
    bool empty() const;

    template <typename PPKey, typename PPValue>
    friend void prettyPrintBST(BinarySearchTree<PPKey, PPValue> &tree);

private:
    bool checkBalance(Node<Key, Value> *n) const;

public:
    /**
     * An internal iterator class for traversing the contents of the BST.
     */
    class iterator
    {
    public:
        iterator();

        std::pair<const Key, Value> &operator*() const;
        std::pair<const Key, Value> *operator->() const;

        bool operator==(const iterator &rhs) const;
        bool operator!=(const iterator &rhs) const;

        iterator &operator++();

    protected:
        friend class BinarySearchTree<Key, Value>;
        iterator(Node<Key, Value> *ptr);
        Node<Key, Value> *current_;
    };

public:
    iterator begin() const;
    iterator end() const;
    iterator find(const Key &key) const;
    Value &operator[](const Key &key);
    Value const &operator[](const Key &key) const;

protected:
    // Mandatory helper functions
    Node<Key, Value> *internalFind(const Key &k) const;
    Node<Key, Value> *getSmallestNode() const;
    static Node<Key, Value> *predecessor(Node<Key, Value> *current);
    // Note:  static means these functions don't have a "this" pointer
    //        and instead just use the input argument.

    // Provided helper functions
    virtual void printRoot(Node<Key, Value> *r) const;
    virtual void nodeSwap(Node<Key, Value> *n1, Node<Key, Value> *n2);

    // Add helper functions here
    Node<Key, Value> *getNode(const Key &k, Node<Key, Value> *n) const;
    int getHeight(Node<Key, Value>* n) const;

protected:
    Node<Key, Value> *root_;
    // You should not need other data members
};

/*
--------------------------------------------------------------
Begin implementations for the BinarySearchTree::iterator class.
---------------------------------------------------------------
*/

/**
 * Explicit constructor that initializes an iterator with a given node pointer.
 */
template <class Key, class Value>
BinarySearchTree<Key, Value>::iterator::iterator(Node<Key, Value> *ptr) : current_(ptr)
{
}

/**
 * A default constructor that initializes the iterator to NULL.
 */
template <class Key, class Value>
BinarySearchTree<Key, Value>::iterator::iterator() : current_(NULL)
{
}

/**
 * Provides access to the item.
 */
template <class Key, class Value>
std::pair<const Key, Value> &
BinarySearchTree<Key, Value>::iterator::operator*() const
{
    return current_->getItem();
}

/**
 * Provides access to the address of the item.
 */
template <class Key, class Value>
std::pair<const Key, Value> *
BinarySearchTree<Key, Value>::iterator::operator->() const
{
    return &(current_->getItem());
}

/**
 * Checks if 'this' iterator's internals have the same value
 * as 'rhs'
 */
template <class Key, class Value>
bool BinarySearchTree<Key, Value>::iterator::operator==(
    const BinarySearchTree<Key, Value>::iterator &rhs) const
{
    return this->current_ == rhs.current_;
}

/**
 * Checks if 'this' iterator's internals have a different value
 * as 'rhs'
 */
template <class Key, class Value>
bool BinarySearchTree<Key, Value>::iterator::operator!=(
    const BinarySearchTree<Key, Value>::iterator &rhs) const
{
    return this->current_ != rhs.current_;
}

/**
 * Advances the iterator's location using an in-order sequencing
 */
template <class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator &
BinarySearchTree<Key, Value>::iterator::operator++()
{
    // Base case: Return NULL iterator if current node is empty
    Node<Key, Value> *n = current_;
    if (n == NULL)
        return *this;

    // If right tree exists, find successor
    if (n->getRight() != NULL)
    {
        n = n->getRight();
        while (n->getLeft() != NULL)
        {
            n = n->getLeft();
        }
        current_ = n;
        return *this;
    }

    // Right subtree cases

    // If left child --> Return parent. Otherwise, return grandparent
    if (n->getParent() != NULL && n->getParent()->getLeft() == n)
        n = n->getParent();
    if (n->getParent() != NULL && n->getParent()->getRight() == n)
        n = n->getParent()->getParent();
    current_ = n;
    return *this;
}

/*
-------------------------------------------------------------
End implementations for the BinarySearchTree::iterator class.
-------------------------------------------------------------
*/

/*
-----------------------------------------------------
Begin implementations for the BinarySearchTree class.
-----------------------------------------------------
*/

/**
 * Default constructor for a BinarySearchTree, which sets the root to NULL.
 */
template <class Key, class Value>
BinarySearchTree<Key, Value>::BinarySearchTree()
{
    root_ = NULL;
}

template <typename Key, typename Value>
BinarySearchTree<Key, Value>::~BinarySearchTree()
{
    this->clear();
}

/**
 * Returns true if tree is empty
 */
template <class Key, class Value>
bool BinarySearchTree<Key, Value>::empty() const
{
    return root_ == NULL;
}

template <typename Key, typename Value>
void BinarySearchTree<Key, Value>::print() const
{
    printRoot(root_);
    std::cout << "\n";
}

/**
 * Returns an iterator to the "smallest" item in the tree
 */
template <class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator
BinarySearchTree<Key, Value>::begin() const
{
    BinarySearchTree<Key, Value>::iterator begin(getSmallestNode());
    return begin;
}

/**
 * Returns an iterator whose value means INVALID
 */
template <class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator
BinarySearchTree<Key, Value>::end() const
{
    BinarySearchTree<Key, Value>::iterator end(NULL);
    return end;
}

/**
 * Returns an iterator to the item with the given key, k
 * or the end iterator if k does not exist in the tree
 */
template <class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator
BinarySearchTree<Key, Value>::find(const Key &k) const
{
    Node<Key, Value> *curr = internalFind(k);
    BinarySearchTree<Key, Value>::iterator it(curr);
    return it;
}

/**
 * @precondition The key exists in the map
 * Returns the value associated with the key
 */
template <class Key, class Value>
Value &BinarySearchTree<Key, Value>::operator[](const Key &key)
{
    Node<Key, Value> *curr = internalFind(key);
    if (curr == NULL)
        throw std::out_of_range("Invalid key");
    return curr->getValue();
}
template <class Key, class Value>
Value const &BinarySearchTree<Key, Value>::operator[](const Key &key) const
{
    Node<Key, Value> *curr = internalFind(key);
    if (curr == NULL)
        throw std::out_of_range("Invalid key");
    return curr->getValue();
}

template <class Key, class Value>
Node<Key, Value> *BinarySearchTree<Key, Value>::insertHelper(Node<Key, Value> *n, const std::pair<const Key, Value> &keyValuePair)
{
    // @condition If child is null, return it first
    if (n == NULL) return n;

    Node<Key, Value> *c;
    // @condition If key is smaller, traverse left subtree
    if (keyValuePair.first < n->getKey())
    {
        c = insertHelper(n->getLeft(), keyValuePair);
    }
    else

        // @condition If key is larger, traverse right subtree
        if (keyValuePair.first < n->getKey())
        {
            c = insertHelper(n->getRight(), keyValuePair);
        }

    // @condition If key is the same, update value
    if (keyValuePair.first == n->getKey())
    {
        n->setValue(keyValuePair.second);
        return n;
    }

    // Return parent
    return n;
}

/**
 * An insert method to insert into a Binary Search Tree.
 * The tree will not remain balanced when inserting.
 * Recall: If key is already in the tree, you should
 * overwrite the current value with the updated value.
 */
template <class Key, class Value>
void BinarySearchTree<Key, Value>::insert(const std::pair<const Key, Value> &keyValuePair)
{
    // Create new root node if it doesn't exist
    if (root_ == NULL)
    {
        root_ = new Node<Key, Value>(keyValuePair.first, keyValuePair.second, NULL);
        return;
    }

    // Insert new node at proper location
    Node<Key, Value> *parent = insertHelper(root_, keyValuePair);
    Node<Key, Value> *newNode = new Node<Key, Value>(keyValuePair.first, keyValuePair.second, parent);
    if (keyValuePair.first < parent->getKey())
    {
        parent->setLeft(newNode);
    }
    else if (keyValuePair.first > parent->getKey())
    {
        parent->setRight(newNode);
    }
}

/**
 * A remove method to remove a specific key from a Binary Search Tree.
 * Recall: The writeup specifies that if a node has 2 children you
 * should swap with the predecessor and then remove.
 */
template <typename Key, typename Value>
void BinarySearchTree<Key, Value>::remove(const Key &key)
{
    Node<Key, Value> *n = internalFind(key);
    if (n == NULL)
        return;
    Node<Key, Value> *p = n->getParent();
    if (p->getLeft() == NULL && p->getRight() == NULL)
    {
        // @condition If leaf node, remove
        if (p == NULL)
            root_ = n; // root node case
        if (p != NULL)
        { // update parent
            if (p->getLeft() == n)
                p->setLeft(NULL);
            else
                p->setRight(NULL);
        }
        delete n;
    }
    else

        // 1 child case
        if ((p->getLeft() == NULL && p->getRight() == n) || (p->getLeft() == n && p->getLeft() == n))
        {
            if (p == NULL)
            { // if root, promote/update child
                n->setParent(NULL);
                root_ = n;
                delete n;
            }
            if (p != NULL) // If not root, find child and promote/update
            {
                // Find out which direction is the child and promote it
                if (p->getLeft() == n)
                {
                    delete n;
                    p->setLeft(n);
                }
                else
                {
                    delete n;
                    p->setRight(n);
                }
                n->setParent(p); // set new parent
            }
        }

     else // If 2 children, swap n with predecessor and delete n
        {
            Node<Key, Value> *pred = this->predecessor(n);
            nodeSwap(n, pred);

            // leaf node case: update predecessor parent
            if (n->getLeft() == NULL && n->getRight() == NULL) // Leaf node
            {
                 if (pred->getParent()->getLeft() == n) pred->getParent()->setLeft(NULL);
                else pred->getParent()->setRight(NULL);
                delete n;
            }

            // 1 child case: find child, promote and update
            else if ((n->getLeft() != NULL && n->getRight() == NULL) || (n->getLeft() == NULL && n->getRight() != NULL)) // 1 child
            {
                Node<Key, Value>* predChild = n->getLeft() != NULL ? n->getLeft() : n->getRight();
                if (pred->getParent()->getLeft() == n)
                {
                    delete n;
                    pred->getParent()->setLeft(predChild);
                }
                else
                {
                    delete n;
                    pred->getParent()->setRight(predChild);
                }
                predChild->setParent(pred->getParent());
            }
        }
}

/*
    Get maximum value in left subtree
*/
template <class Key, class Value>
Node<Key, Value> *
BinarySearchTree<Key, Value>::predecessor(Node<Key, Value> *current)
{
    // @summary If no node found at given position, return NULL
    if (current == NULL)
        return NULL;
    if (current->getLeft() == NULL)
        return NULL;

    // @summary Get max value of subtree
    Node<Key, Value> *p = current->getLeft();
    while (p->getRight() != NULL)
    {
        p = p->getRight();
    }
    return p;
}

/**
 * A method to remove all contents of the tree and
 * reset the values in the tree for use again.
 */
template <typename Key, typename Value>
void BinarySearchTree<Key, Value>::clear()
{
    // clear tree and reset root
    clearSubtree(root_);
    root_ = NULL;
}

/**
 * @brief
 * A helper function to remove nodes recursively
 */
template <typename Key, typename Value>
void BinarySearchTree<Key, Value>::clearSubtree(Node<Key, Value> *n)
{
    // Remove subtrees if they exist
    if (n != NULL)
    {
        clearSubtree(n->getRight());
        clearSubtree(n->getLeft());
    }
    delete n;
}

/**
 * A helper function to find the smallest node in the tree.
 */
template <typename Key, typename Value>
Node<Key, Value> *BinarySearchTree<Key, Value>::getSmallestNode() const
{
    // Base case: Return NULL if root is empty
    if (root_ == NULL)
        return NULL;

    // Otherwise, find/return the leftmost node
    Node<Key, Value> *n = root_;
    while (n->getLeft() != NULL)
    {
        n = n->getLeft();
    }
    return n;
}

/**
 * @brief Helper function to get node with given key
 *
 * @tparam Key
 * @tparam Value
 * @param key
 * @return Node<Key, Value>*
 */
template <typename Key, typename Value>
Node<Key, Value> *BinarySearchTree<Key, Value>::getNode(const Key &k, Node<Key, Value> *n) const
{
    // @condition If node is empty, return null
    if (n == NULL) 
        return NULL;

    // @condition If keys match, return node
    if (n->getKey() == k)
        return n;

    // @condition If key less than n, go left. Otherwise, go right
    if (n->getKey() > k)
        return getNode(k, n->getLeft());
    else
        return getNode(k, n->getRight());
}

/**
 * Helper function to find a node with given key, k and
 * return a pointer to it or NULL if no item with that key
 * exists
 */
template <typename Key, typename Value>
Node<Key, Value> *BinarySearchTree<Key, Value>::internalFind(const Key &key) const
{
    return this->getNode(key, root_);
}

// @summary Get height of tree
template <typename Key, typename Value>
int BinarySearchTree<Key, Value>::getHeight(Node<Key, Value>* n) const
{
    if (n == NULL) return 0;
    int leftHeight = getHeight(n->getLeft());
    int rightHeight = getHeight(n->getRight());
    return std::max(leftHeight, rightHeight) + 1;
}

/**
 * Check if tree is balanced
 * */
template <typename Key, typename Value>
bool BinarySearchTree<Key, Value>::checkBalance(Node<Key, Value> *n) const
{
    // @summary If n is empty, return true as default
    if (n == NULL)
        return true;

    // @summary Get height of each subtree and compare
    int LSubtreeHeight = getHeight(n->getLeft());
    int RSubtreeHeight = getHeight(n->getRight());
    if (abs(LSubtreeHeight - RSubtreeHeight) >= 2)
        return false;
    return checkBalance(n->getLeft()) && checkBalance(n->getRight());
}

/**
 * Return true iff the BST is balanced.
 */
template <typename Key, typename Value>
bool BinarySearchTree<Key, Value>::isBalanced() const
{
    return checkBalance(root_);
}

template <typename Key, typename Value>
void BinarySearchTree<Key, Value>::nodeSwap(Node<Key, Value> *n1, Node<Key, Value> *n2)
{
    if ((n1 == n2) || (n1 == NULL) || (n2 == NULL))
    {
        return;
    }
    Node<Key, Value> *n1p = n1->getParent();
    Node<Key, Value> *n1r = n1->getRight();
    Node<Key, Value> *n1lt = n1->getLeft();
    bool n1isLeft = false;
    if (n1p != NULL && (n1 == n1p->getLeft()))
        n1isLeft = true;
    Node<Key, Value> *n2p = n2->getParent();
    Node<Key, Value> *n2r = n2->getRight();
    Node<Key, Value> *n2lt = n2->getLeft();
    bool n2isLeft = false;
    if (n2p != NULL && (n2 == n2p->getLeft()))
        n2isLeft = true;

    Node<Key, Value> *temp;
    temp = n1->getParent();
    n1->setParent(n2->getParent());
    n2->setParent(temp);

    temp = n1->getLeft();
    n1->setLeft(n2->getLeft());
    n2->setLeft(temp);

    temp = n1->getRight();
    n1->setRight(n2->getRight());
    n2->setRight(temp);

    if ((n1r != NULL && n1r == n2))
    {
        n2->setRight(n1);
        n1->setParent(n2);
    }
    else if (n2r != NULL && n2r == n1)
    {
        n1->setRight(n2);
        n2->setParent(n1);
    }
    else if (n1lt != NULL && n1lt == n2)
    {
        n2->setLeft(n1);
        n1->setParent(n2);
    }
    else if (n2lt != NULL && n2lt == n1)
    {
        n1->setLeft(n2);
        n2->setParent(n1);
    }

    if (n1p != NULL && n1p != n2)
    {
        if (n1isLeft)
            n1p->setLeft(n2);
        else
            n1p->setRight(n2);
    }
    if (n1r != NULL && n1r != n2)
    {
        n1r->setParent(n2);
    }
    if (n1lt != NULL && n1lt != n2)
    {
        n1lt->setParent(n2);
    }

    if (n2p != NULL && n2p != n1)
    {
        if (n2isLeft)
            n2p->setLeft(n1);
        else
            n2p->setRight(n1);
    }
    if (n2r != NULL && n2r != n1)
    {
        n2r->setParent(n1);
    }
    if (n2lt != NULL && n2lt != n1)
    {
        n2lt->setParent(n1);
    }

    if (root_ == n1)
    {
        root_ = n2;
    }
    else if (root_ == n2)
    {
        root_ = n1;
    }
}

/**
 * Lastly, we are providing you with a print function,
   BinarySearchTree::printRoot().
   Just call it with a node to start printing at, e.g:
   this->printRoot(root_) // or any other node pointer

   It will print up to 5 levels of the tree rooted at the passed node,
   in ASCII graphics format.
   We hope it will make debugging easier!
  */

// include print function (in its own file because it's fairly long)
#include "print_bst.h"

/*
---------------------------------------------------
End implementations for the BinarySearchTree class.
---------------------------------------------------
*/

#endif
