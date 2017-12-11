#ifndef ITERATOR_H
#define ITERATOR_H

#include "struct.h"
#include "list.h"
#include <queue>
#include <stack>
#include <typeinfo>
using namespace std;

template<class T>
class Iterator {
public:
  virtual void first() = 0;
  virtual void next() = 0;
  virtual T currentItem() const = 0;
  virtual bool isDone() const = 0;
};

template<class T>
class NullIterator :public Iterator<T>{
public:
  NullIterator(Term *n){}
  void first(){}
  void next(){}
  Term * currentItem() const{
      return nullptr;
  }
  bool isDone() const{
    return true;
  }

};

template<class T>
class StructIterator :public Iterator<T> {
public:
  friend class Struct;
  void first() {
    _index = 0;
  }

  Term* currentItem() const {
    return _list->args(_index);
  }

  bool isDone() const {
    return _index == _list->arity() ;
  }

  void next() {
    // std::cout << "Before: " << _index << "\n";
    if(!isDone()) _index++;
    // std::cout << "After: " << _index << "\n";
  }

private:
  StructIterator(Struct *s): _index(0), _list(s) {}
  int _index;
  Struct* _list;
};
//----------------------------------BFS DFS-----------------------------------

template<class T>
class BFSIterator :public Iterator<T> {
public:
  BFSIterator(T item): _index(0), _it(item->createIterator()) {}
  void first() {
    _it->first();
    _index = 0;
    while ( !_bfsQueue.empty())
      _bfsQueue.pop();

      
    while ( !_it->isDone()) {
      _bfsQueue.push(_it->currentItem());
      _it->next();
    }

  }

  Term* currentItem() const {
    return _bfsQueue.front();
  }

  bool isDone() const {
    return _bfsQueue.empty();
  }

  void next() {

    _insideArgs = _bfsQueue.front()->createIterator();
    _insideArgs->first();
    // std::cout << "_inside:" << _insideArgs->currentItem()->symbol() << "\n";
    while (!_insideArgs->isDone()) {
      _bfsQueue.push(_insideArgs->currentItem());
      // std::cout << "Q:" << _insideArgs->currentItem()->symbol() << "\n";
      _insideArgs->next();
    }
    if( !_bfsQueue.empty())_bfsQueue.pop();
  }

private:
  int _index;
  Iterator<T> * _it ;
  Iterator<T> * _insideArgs;
  std::queue<T> _bfsQueue; 
};

template<class T>
class DFSIterator :public Iterator<T> {
public:
  DFSIterator(T item): _index(0), _SorL(item),_it(item->createIterator()) {}
  void first() {
    _it->first();
    _index = 0;
    while( !_dfsStack.empty())
      _dfsStack.pop();

    std::stack<Term *> tempArgs ;
    while( !_it->isDone()) {
      tempArgs.push(_it->currentItem());
      _it->next();
    }
    while( !tempArgs.empty()) {
      _dfsStack.push(tempArgs.top());
      tempArgs.pop();
    }
  }

  Term* currentItem() const {
    return _dfsStack.top();
  }

  bool isDone() const {
    return _dfsStack.empty();
  }

  void next() {
    _insideArgs = _dfsStack.top()->createIterator();
    _insideArgs->first();
    _dfsStack.pop();
    if( !_insideArgs->isDone()) {
      std::stack<Term *> tempArgs ;
      while( !_insideArgs->isDone()) {
        tempArgs.push(_insideArgs->currentItem());
        _insideArgs->next();
      }
      while( !tempArgs.empty()) {
        _dfsStack.push(tempArgs.top());
        tempArgs.pop();
      }
    }
  }

private:
  int _index;
  T _SorL;
  Iterator<T> * _it ;
  Iterator<T> * _insideArgs;
  std::stack<Term *> _dfsStack;
};

//----------------------------------List Iterator-----------------------------


template<class T>
class ListIterator :public Iterator<T> {
public:
  ListIterator(List *list): _index(0), _list(list) {}

  void first() {
    _index = 0;
  }

  Term* currentItem() const {
    return _list->args(_index);
  }

  bool isDone() const {
    return _index == _list->arity();
  }

  void next() {
   if(!isDone()) _index++;
  }


private:
  int _index;
  List* _list;
};



#endif
