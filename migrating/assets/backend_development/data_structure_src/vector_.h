//
//  vector_.h
//  intvector
//
//  Created by William McCarthy on 9/5/18.
//  Copyright © 2018 William McCarthy. All rights reserved.
//

#ifndef vector__h
#define vector__h

#include <iostream>
#include <algorithm>
#include <string>
#include <cassert>

using std::cout;
using std::ostream;

// example of a template function (not used in this file)
template <typename T>
T max_(T a, T b) { return (a > b) ? a : b; }

#define MIN_VECTOR_SIZE   10

// forward declarations needed for class vector_ and friend functions
template <typename T> class vector_;
template <typename T> ostream& operator<<(ostream& os, const vector_<T>& iv);
template <typename T> bool operator==(const vector_<T>& a, const vector_<T>& b);
template <typename T> bool operator!=(const vector_<T>& a, const vector_<T>& b);


template <typename T>
class vector_ {
public:
  vector_();
  vector_(size_t size);
  vector_(const vector_& other);
  vector_& operator=(const vector_& other);
  ~vector_();
  
  size_t size() const;
  size_t length() const;
  
  T* begin() const;
  T* end() const;
  
  T front() const;
  T& front();
  
  T back() const;
  T& back();
  
  void push_back(T val);
  void pop_back();
  
  T  operator[](size_t i) const;
  T& operator[](size_t i);
  
  friend bool operator== <>(const vector_<T>& a, const vector_<T>& b);
  friend bool operator!= <>(const vector_<T>& a, const vector_<T>& b);
  
  friend ostream& operator<< <>(ostream& os, const vector_<T>& iv);  // note operator<< <>(...)
  
private:
  void copy(const vector_& other);
  void resize(size_t newsize);
  
private:
  size_t size_;
  size_t length_;
  T* data_;
};

template <typename T> vector_<T>::vector_() : vector_(MIN_VECTOR_SIZE) {}
template <typename T> vector_<T>::vector_(size_t size)
: size_(size), length_(0), data_(new T[size_]) {}
template <typename T> vector_<T>::vector_(const vector_<T>& other) : data_(nullptr) { copy(other); }
template <typename T>
vector_<T>& vector_<T>::operator=(const vector_<T>& other) {
  if (this != &other) { copy(other); }
  return *this;
}
template <typename T>
vector_<T>::~vector_() {    // this is the pointer to the object instance
  cout << "deleting " << this << "...\n";
  delete [] data_;
}

template <typename T> size_t vector_<T>::size() const { return size_; }
template <typename T> size_t vector_<T>::length() const { return length_; }

template <typename T> T* vector_<T>::begin() const { return data_; }
template <typename T> T* vector_<T>::end() const { return data_ + length_; }

template <typename T> T vector_<T>::front() const { return operator[](0); }
template <typename T> T& vector_<T>::front()      { return operator[](0); }

template <typename T> T vector_<T>::back() const  { return operator[](length_ - 1); }
template <typename T> T& vector_<T>::back()       { return operator[](length_ - 1); }

template <typename T>
void vector_<T>::push_back(T val) {
  if (length_ >= size_) { resize(2 * size_); }
  data_[length_++] = val;
}

template <typename T>
void vector_<T>::pop_back() {
  if (length_ == 0) { throw new std::invalid_argument("Buffer underflow"); }
  else if (length_ <= size_ / 2) {
    resize( size_ / 2);  // reduce capacity
  }
  data_[length_--] = T();
}

template <typename T> T vector_<T>::operator[](size_t i) const { return data_[i]; }
template <typename T> T& vector_<T>::operator[](size_t i) { return data_[i]; }

template <typename T>
bool operator==(const vector_<T>& a, const vector_<T>& b) {
  if (a.size() != b.size() || a.length() != b.length()) { return false; }
  for (size_t i = 0; i < a.length(); ++i) {
    if (a[i] != b[i]) { return false; }
  }
  return true;
}
template <typename T> bool operator!=(const vector_<T>& a, const vector_<T>& b) { return !(a == b); }

// in the implementation, we just say: operator<<(...) --- not operator<< <>(...)
template <typename T> ostream& operator<<(ostream& os, const vector_<T>& iv) {
  if (iv.length_ == 0) { return os << "vector_<T> is empty"; }
  
  for (auto val : iv) { // note: need begin() and end() functions to use auto
    os << val << " ";
  }
  return os;
}

// HELPER FUNCTIONS  ==================================================
template <typename T>
void vector_<T>::copy(const vector_<T>& other) {
  if (data_ != nullptr) { delete[] data_; }
  
  size_ = other.size_;
  length_ = other.length_;
  data_ = new T[size_];
  std::copy(other.data_, other.data_ + other.size_, data_);
}

template <typename T>
void vector_<T>::resize(size_t newsize) {
  if (length_ > newsize) { throw new std::invalid_argument("new buffer size too small for data"); }
  
  cout << "=========== Resizing from " << size_ << " to " << newsize << "...\n";
  T* newdata = new T[newsize];
  std::copy(data_, data_ + size_, newdata);
  size_ = newsize;
      // no change in length
  delete [] data_;
  data_ = newdata;
}

// TEST CODE ==================================================
void test_vector_() {
  vector_<float> iv;
  
  for (int i = 0; i < iv.size(); ++i) { iv.push_back(0.5 + 2 * i); }
  cout << "iv is: " << &iv << "   " << iv << "\n";
  assert(iv[0] == 0.5);
  assert(iv[iv.length() - 1] == 2 * (iv.size() - 1) + 0.5);
  
  vector_<float> iu(iv);
  cout << "after copy c'tor...\niu is: " << &iu << "   " << iu << "\n";
  assert(iv == iu);
  
  vector_<float> it;
  it = iu;
  cout << "after operator=...\nit is: " << &iu << "   " << iu << "\n";
  assert(it == iu);
  
  iv.push_back(90.9);
  iv.push_back(900.9);
  iv.push_back(90000.9);
  cout << "after adding more data, iv is now..." << iv << "\n";
  
  while (iv.size() > 5) {
    iv.pop_back();
    cout << "iv is now..." << iv << "\n";
  }
}



#endif /* vector__h */
