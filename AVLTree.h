#include <string>
#include <iostream>
#include <cassert>
#include <stdexcept>
#include <iostream>
#include <queue>
#include <vector>
#include <cstdlib>
#include <functional>

#ifndef AVLTREE_H
#define AVLTREE_H

using namespace std;

/**
 * Reports an exception in an AVL Tree
 * @author Duncan
 * @since 99-99-9999
 */
class AVLTreeException
{
private:
   string message;    
public:
   /**
    * Constructs an instance of <code>AVLTreeException</code> with the
    * specified detail message.
    * @param msg the detail message.
    */
   AVLTreeException(const string& aMessage)
   {
      message = aMessage;
   } 
   /**
    * Returns a message
    * @return a message
    */
   string what() const
   {
      return message;
   }
};

/**
 * Describes operations on an AVLTree
 * @param <E> the data type
 * @author William Duncan
 * @see AVLTreeException
 * <pre>
 * Date: 99-99-9999
 * CSC 3102 Programming Project # 2
 * Instructor: Dr. Duncan 
 *
 * DO NOT REMOVE THIS NOTICE (GNU GPL V2):
 * Contact Information: duncan@csc.lsu.edu
 * Copyright (c) 2026 William E. Duncan
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>
 * </pre>
 */
template <typename E>
class AVLTree
{
private:  
    typedef enum _BalancedFactor{LH=-1,EH,RH} BalancedFactor;   
    typedef std::function<void(const E&)> FuncType;

    class Node
    {
    public:
       /**
          Constructs a node with a given data value.
          @param s the data to store in this node
       */
       Node(E s);
    private:
       /**
        * the data in this node
        */    
       E data;
       /**
        * the left child    
        */
       Node * left;
       /**
        * the right child
        */
       Node * right;
       /**
        * the balanced factor of this node
        */
       BalancedFactor bal;
      friend class AVLTree<E>;
    }; 

    // --------------------------
    // Private Members
    // --------------------------

    /**
     * the root of this tree
     */
    Node* root;
    /**
     * the size of this tree
     */
    int count;   
    /**
     * A trichotomous integer-value comparator lambda function; that is,
     * it compares two elements of this AVL tree and returns a negative
     * integer when the first is less than the second; 0, when they are equal;
     * otherwise, a positive integer
     */
    std::function<int(E,E)> cmp = nullptr;

    /**
     * An auxiliary function that recursively frees the memory
     * allocated for the nodes of this tree.
     * @param subtreeRoot a root of this subtree
     */
    void recDestroy(Node* subtreeRoot);

    Node* insert(Node* curRoot, Node* newNode, bool& taller);
    Node* leftBalance(Node* curRoot, bool& taller);
    Node* rightBalance(Node* curRoot, bool& taller);
    Node* rotateLeft(Node* node);
    Node* rotateRight(Node* node);
    void traverse(Node* node, FuncType func);
    Node* remove(Node* node,const E& key, bool& shorter, bool& success);
    Node* deleteRightBalance(Node* node, bool& shorter);
    Node* deleteLeftBalance(Node* node, bool& shorter);

    // --------------------------
    // Private helpers
    // --------------------------
    int height(Node* node) const;
    int diameter(Node* node) const;
    bool isFull(Node* node) const;
    bool isComplete(Node* node, int index) const;

public:
    // --------------------------
    // Public interface
    // --------------------------
    AVLTree();
    AVLTree<E>(std::function<int(E,E)> fn);   
    ~AVLTree();

    bool isEmpty() const;
    void insert(const E& obj);
    bool inTree(const E& item) const;
    void remove(const E& item);
    const E& retrieve(const E& key) const throw (AVLTreeException);
    void traverse(FuncType func);
    void levelOrder(FuncType func);
    int size() const;
    int height() const;
    int diameter() const;
    bool isFull() const;   
    bool isComplete() const;   
};

#endif // AVLTREE_H