#ifndef priority_queue_h_
#define priority_queue_h_

#include <iostream>
#include <vector>
#include <cassert>
using namespace std;

template <class T>
class priority_queue {
private:
  std::vector<T> m_heap;

public:
  priority_queue() {}

  priority_queue(std::vector<T> const& values) {
    for (int i = 0; i < values.size(); ++i) {
      m_heap.push(values[i]);
    }
  }

  const T& top() const 
  {
    assert( !m_heap.empty() );
    return m_heap[0]; 
  }

  void push(const T& entry) {
    m_heap.push_back(entry);
    int m_size = m_heap.size();
    percolate_up(m_size-1);
  }

  void percolate_up(int current) {
    int parent = int(0.5* (current-1));
    while (current >= 0) {
      parent = int(0.5* (current-1));
      if (m_heap[current] < m_heap[parent]) {
        swap(m_heap[parent], m_heap[current]);
        current = parent;
      }
      else {
        break;
      }
    }
  }

  void pop() {
    assert(!m_heap.empty());
    int m_size = m_heap.size();
    m_heap[0] = m_heap[m_size-1];
    m_heap.pop_back();
    percolate_down(0, m_size);
  }

  void percolate_down(int root, int m_size) {
    int left = root*2 + 1;
    int right = root*2 + 2;
    while (left <= m_size-1) {
      int child;
      if (right <= m_size-1 && m_heap[right] < m_heap[left]) {
        child = right;
      }
      else {
        child = left;
      }
      if (m_heap[child] < m_heap[root]) {
        swap(child, root);
        root = child;
      }
      else {
        break;
      }
    }
  }

  int size() { return m_heap.size(); }
  bool empty() { return m_heap.empty(); }


  //  The following three functions are used for debugging.

  //  Check to see that internally the heap property is realized.
  bool check_heap() {
    return this->check_heap(this-> m_heap);
  }

  //  Check an external vector to see that the heap property is realized.
  bool check_heap(const std::vector<T>& heap) {
    for (int i = 0; i < heap.size(); ++i) {
      int left = i*2 + 1;
      int right = i*2 + 2;
      if ((left <= heap.size()-1 && heap[left] < heap[i])
          || (right <= heap.size()-1 && heap[right] < heap[i])) {
        return false;
      }
    }
    return true;
  }

  //  A utility to print the contents of the heap.  Use it for debugging.
  void print_heap( std::ostream & ostr )
  {
    for ( unsigned int i=0; i<m_heap.size(); ++i )
      ostr << i << ": " << m_heap[i] << std::endl;
  }
  
};

template <class T>
void heap_sort(std::vector<T>& v) {
  int v_size = v.size();
  heap_sort_helper(v, v_size);
}

void heap_sort_helper(std::vector<T>& v, int v_size) {
  for (int i = v_size/2 - 1; i >= 0; --i) {
    heap_sort_real(v, i, v_size);
  }
  for (int j = v_size-1; j >= 0; --j) {
    swap(v[0], v[j]);
    heap_sort_helper(v, 0, j);
  }
}

void heap_sort_helper(std::vector<T>& v, int tmp, int v_size) {
  int large, left = tmp*2+1; right = tmp*2+2;
  if (v_size > left && v[tmp] < v[left]) {
    large = left;
  }
  if (v_size > right && v[tmp] < v[right]) {
    large = right;
  }
  swap(v[large], v[tmp]);
  heap_sort_helper(v, large, v_size);
}

#endif
