---
layout: post
title:	Introduction to Vectors
categories: Data Structures Crash Course
---

# Vectors

`std::vector` is one of many data containers in the C++ Standard Library. 
One notable difference is from other structures is it's ability to self expand and allow for more data to be added without the need to manually migrate data.
It closely resembles the class C-style array using raw pointers and the `std::array` STL container which is built on the prior example.
Where vectors excel in is the quick prepending and appending of data but fails to efficiently insert in data in an arbitrary location.

Here, you will explore the inner workings of how the `std::vector` is built at a basic level. 
The following methods and attributes were written to simulate their functionality but are nowhere near as efficient as the STL container used in productions.
To read that code, please refer to this [link](https://code.woboq.org/llvm/libcxx/include/vector.html) to the official source code.

## Attributes

### size_

The total size of the vector at any given time. Return type is `size_t` or `unsigned long int`.

### capacity_

The maximum size of the vector before it needs to be expanded. Return type is `size_t` or `unsigned long int`.

### data_

A C-style array with an templated type to allow for any data type to be used.

## Functions/Methods

**NOTE:** all functions are defined outside of the class body. This is referred to as declaring functions `inline` and it uses the `scope resolution operator(::)`. That operator is also used in times where `namespace` is important. For example, `std::string` where the string class belongs to the `namespace` std. `vector::<FUNCTION CALLED>` is telling the compiler that FUNCTION CALLED is apart of the `vector` class.

### Default Constructor

```cpp
vector() : vector(15){}
```

This constructor is a wrapper for the parameterized constructor. We are giving it a default size to load if no size is explicitly given; `15` in this case.

### Parameterized Constructor

```cpp
vector(size_t c): size_(0), capacity_(c), data_(new T[c]){}
```

Here we are giving the constructor a size we want the vector to be. 
In this case, we are using a member initialization list by giving each member variable an amount. 
Since there is nothing inside the vector at initialization, we give it the size of zero. 
Then, we pass the capacity directly to the variable `capacity_`. 
Lastly, we dynamically allocate an array on the heap and assigning the pointer returned by that allocation directly to `data_`.


# External Links

- [Microsoft C++ Constructor Documentation](https://docs.microsoft.com/en-us/cpp/cpp/constructors-cpp?view=vs-2019)

