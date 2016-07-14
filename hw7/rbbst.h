/*
 * rbbst.h
 *
 * Date        Author    Notes
 * =====================================================
 * 2014-04-14  Kempe     Initial version
 * 2015-04-06  Redekopp  Updated formatting and removed
 *                         KeyExistsException
 */
#ifndef RBBST_H
#define RBBST_H
#include <iostream>
#include <exception>
#include <iostream>
#include <cstdlib>
#include "bst.h"
using namespace std;

/* -----------------------------------------------------
 * Red-Black Nodes and Search Tree
 ------------------------------------------------------*/

enum Color {red, black};

template <class KeyType, class ValueType>
class RedBlackNode : public Node<KeyType, ValueType>
{
public:
  RedBlackNode (KeyType k, ValueType v, RedBlackNode<KeyType, ValueType> *p)
    : Node<KeyType, ValueType> (k, v, p)
    { color = red; }
  
  virtual ~RedBlackNode () {}
  
  Color getColor () const
    { return color; }
  
  void setColor (Color c)
    { color = c; }
  
  virtual RedBlackNode<KeyType, ValueType> *getParent () const
    { return (RedBlackNode<KeyType,ValueType>*) this->_parent; }
  
  virtual RedBlackNode<KeyType, ValueType> *getLeft () const
    { return (RedBlackNode<KeyType,ValueType>*) this->_left; }
  
  virtual RedBlackNode<KeyType, ValueType> *getRight () const
    { return (RedBlackNode<KeyType,ValueType>*) this->_right; }
  
 protected:
  Color color;
};

/* -----------------------------------------------------
 * Red-Black Search Tree
 ------------------------------------------------------*/

template <class KeyType, class ValueType>
class RedBlackTree : public BinarySearchTree<KeyType, ValueType>
{
public:
  void insert (const std::pair<const KeyType, ValueType>& new_item)
  {
    Node<KeyType, ValueType>* curr = this->root;
    //empty tree
    if (curr == NULL){
      this->root = new RedBlackNode<KeyType, ValueType>(new_item.first, new_item.second, NULL);
      static_cast<RedBlackNode<KeyType, ValueType>*>(this->root)->setColor(black);
    }

    else{
      while(1){
        if (curr->getKey() == new_item.first){
          curr->setValue(new_item.second);
          return;
        }
        else if (curr->getKey() > new_item.first)
        {
          if (curr->getLeft() == NULL){
            break;
          }
          else{
            curr = curr->getLeft();
          }
        }
        else
        {
          if (curr->getRight() == NULL){
            break;
          }
          else{
            curr = curr->getRight();
          }
        }
      }

      RedBlackNode<KeyType, ValueType>* newNode = new RedBlackNode<KeyType, 
      ValueType>(new_item.first, new_item.second, static_cast<RedBlackNode<KeyType, ValueType>*>(curr));
      
      if (curr->getKey() > new_item.first){
        curr->setLeft(newNode);
      }
      else{
        curr->setRight(newNode);
      }
      //cout << "Test1" << endl;
      if (static_cast<RedBlackNode<KeyType, ValueType>*>(curr)->getColor() == red){
        fixTree(static_cast<RedBlackNode<KeyType, ValueType>*>(curr));
      }
    }
  }
  /* This one is yours to implement.
     It should insert the (key, value) pair to the tree, 
     making sure that it remains a valid Red-Black Tree.
     If the key is already in the tree
     (with a possibly different associated value),
     then it should overwrite the value with the new one.
     We strongly recommend defining suitable (private) helper functions. */

private:
  RedBlackNode<KeyType, ValueType>* findMyAunt(RedBlackNode<KeyType,ValueType>* curr)
  {
    RedBlackNode<KeyType, ValueType>* aunt;
    if (curr->getParent()->getLeft() != curr){
      aunt = curr->getParent()->getLeft();
    }
    else{
      aunt = curr->getParent()->getRight();
    }
    return aunt;
  }
  bool amIRight(RedBlackNode<KeyType, ValueType>* curr)
  {
    if(curr->getParent() != NULL){
      return curr->getParent()->getRight() == curr;
    }
    return false;
  }
  bool amILeft(RedBlackNode<KeyType, ValueType>* curr)
  {
    if(curr->getParent() != NULL){
      return curr->getParent()->getLeft() == curr;
    }
    return false;
  }
  //need to rotate parent over currGrand not curr
  void rightRot(RedBlackNode<KeyType, ValueType>* currParent)
  {
    //set grand and copy right
    RedBlackNode<KeyType, ValueType>* currGrand = currParent->getParent();
    RedBlackNode<KeyType, ValueType>* temp = currParent->getLeft()->getRight();

    currParent->setParent(currParent->getLeft());
    //reset outgoing pointers
    //cout << "he;;p" << endl;
    currParent->getLeft()->setRight(currParent);
    

    //reset grandpappy
    if(currGrand != NULL)
    {
      if(currGrand->getLeft() != currParent){
        currGrand->setRight(currParent->getLeft());
        //cout << "helo" << endl;
      }
      else{
        currGrand->setLeft(currParent->getLeft());
      }
      //for subtree orphan
      currParent->getLeft()->setParent(currGrand);
    }
    
    
    /*
    currParent->getLeft()->setRight(currParent);
    currParent->setParent(currParent->getLeft());
    */
    //cout << "hello" << endl;
    //reset opp set
    currParent->setLeft(temp);
    if(temp != NULL){
      temp->setParent(currParent);
    }


    // Root repair
    if(currParent == this->root){
      this->root = currParent->getParent();
    }

  }

  void leftRot(RedBlackNode<KeyType, ValueType>* currParent)
  {
    RedBlackNode<KeyType, ValueType>* temp = currParent->getRight()->getLeft();
    RedBlackNode<KeyType, ValueType>* currGrand = currParent->getParent();
    
    // Reset outgoing pointers
    currParent->setParent(currParent->getRight());
    currParent->getRight()->setLeft(currParent);
    

    // set grand
    if (currGrand != NULL)
    {
      if (currGrand->getLeft() != currParent){
        currGrand->setRight(currParent->getRight());
      }
        
      else{
        currGrand->setLeft(currParent->getRight());
      }

      currParent->getRight()->setParent(currGrand);
    }
    
    
    /*
    currParent->getLeft()->setRight(currParent);
    currParent->setParent(currParent->getLeft());
    */
    //cout << "hello" << endl;
    //reset opp set
    // copy over old left
    if(currParent->getRight()){
      currParent->setRight(temp);
      if (temp != NULL){
        temp->setParent(currParent);
      }
    }
    // Root repair
    if (currParent == this->root){
      this->root = currParent->getParent();
    }
  }

  void case45(RedBlackNode<KeyType, ValueType>* curr)
  {
    if (curr->getParent()->getLeft() == curr)
    {
      
      // zig zig
      if (curr->getLeft() && curr->getLeft()->getColor() == red)
      {

        rightRot(curr->getParent());
        curr->setColor(black);
        curr->getRight()->setColor(red);
      }

      // zig zag
      else
      {
        leftRot(curr);
        //cout << "hello2" << endl;
        rightRot(curr->getParent()->getParent());
        //cout << "hello3" << endl;
        curr->getParent()->setColor(black);
        curr->getParent()->getRight()->setColor(red);
      }

    }
    else
    {
      // Right red, left red - double rotate
      //cout << "hello2" << endl;
      if (curr->getLeft() && curr->getLeft()->getColor() == red)
      {
        rightRot(curr);
        //cout << "hello" << endl;
        leftRot(curr->getParent()->getParent());
        curr->getParent()->setColor(black);
        curr->getParent()->getLeft()->setColor(red);
      }
      // Right red, right red - single rotate
      else
      {
        leftRot(curr->getParent());
        curr->setColor(black);
        curr->getLeft()->setColor(red);
      }
    }
  }

  void fixTree(RedBlackNode<KeyType, ValueType>* curr)
  {
    //cout << "hello2" << endl;
    // CASW 3
    if (curr == this->root)
    {
      curr->setColor(black);
      return;
    }

    RedBlackNode<KeyType, ValueType>* uncle = findMyAunt(curr);

    // CASE 1/2
    if (uncle != NULL && uncle->getColor() == red)
    {
      uncle->setColor(black);
      curr->setColor(black);
      curr->getParent()->setColor(red);

      //now recurse to to adress higher problems
      if (curr->getParent() == this->root){
        fixTree(curr->getParent());
      }
      else if (curr->getParent()->getParent()->getColor() == red){
        fixTree(curr->getParent()->getParent());
      }
      else{}
    }


    // Red and black rotations
    else
    {
      //cout << "hello2" << endl;
      case45(curr);
    }
  }
};

#endif
