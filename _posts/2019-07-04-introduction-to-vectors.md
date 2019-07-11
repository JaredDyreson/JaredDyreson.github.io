---
layout: post
title:	Introduction to Vectors
categories: linuxsysadmin
---

Vectors

# Vectors

`std::vector` is one of many data containers in the C++ Standard Library. 
One notable difference is from other structures is it's ability to self expand and allow for more data to be added without the need to manually migrate data.
It closely resembles the class C-style array using raw pointers and the `std::array` STL container which is built on the prior example.
Where vectors excel in is the quick prepending and appending of data but fails to efficiently insert in data in an arbitrary location.

Here, you will explore the inner workings of how the `std::vector` is built at a basic level. 
The following methods and attributes were written to simulate their functionality but are nowhere near as efficient as the STL container used in productions.
To read that code, please refer to this [link](https://code.woboq.org/llvm/libcxx/include/vector.html) to the official source code.

**NOTE:** the following code which been adapted that was originally written by William McCarthy of California State University Fullerton. I take no credit for the code but do take credit for the documentation provided here on forward. All rights reserved.

## Attributes

### size_

The total size of the vector at any given time. Return type is `size_t` or `unsigned long int`.

### capacity_

The maximum size of the vector before it needs to be expanded. Return type is `size_t` or `unsigned long int`.

### data_

A C-style array with an templated type to allow for any data type to be used.

## Overloaded Operators

### []

```cpp
T vector<T>::operator[](size_t i) const { return data_[i]; }
```

```cpp
T& vector<T>::operator[](size_t i) { return data_[i]; }
```

Access elements directly like C-style arrays.
Two versions are declared, one for making direct edits to `data_` (non const) and one to retrieve members from `data_` (const).

### == 

```cpp
bool operator==(const vector<T>& a, const vector<T>& b){
	if(a.size() != b.size() || a.capacity() != b.capacity()) { return false; }
	for(size_t i = 0; i < a.capacity(); ++i){
		if(a[i] != b[i]) { return false; }
	}
	return true;
}

```

We first check if the `size_` or `capacity_` variables are not the same, returning false if either condition is fulfilled.
After that check, we loop through the `data_` member of both `learning::vector` class objects.
Once an element that does not match is found, we immediately return false.
Lastly, we return true if all other conditions are evaluated.

### !=

```cpp
bool operator!=(const vector<T>& a, const vector<T>& b) { return !(a==b); }
```

Calling the `==` operator will allow us to get a true or false response.
This response is then inverted and we have if it is *not* equal.

### `<<`

```cpp
std::ostream& operator<<(std::ostream& os, const vector<T>& iv) {
	for (auto val : iv) { os << val << " "; }
	return os;
}
```
We can directly call an `std::ostream` operator directly on the `learning::vector` class.
This includes and is not limited to:

- `std::cout`
- `std::ofstream`
- `std::ifstream`

This allows for printing out the content of the `data_` member variable to the console or files.
Note that we need to declare it with the `friend` keyword which allows the function direct access to private data members.
Also, we are passing in the `learning::vector` object as `const` which tells the `std::ostream` operator *not* to modify or make a copy in the function body.
Please refer to `External Links` for a more in depth explanation.

## Functions/Methods

**NOTE:** all functions are defined outside of the class body. This is referred to as declaring functions `inline` and it uses the `scope resolution operator(::)`. That operator is also used in times where `namespace` is important. For example, `std::string` where the string class belongs to the `namespace` std. `vector::<FUNCTION CALLED>` is telling the compiler that FUNCTION CALLED is apart of the `vector` class.

### Default Constructor

```cpp
vector() : vector(15){}
```

This constructor is a wrapper for the parameterized constructor. We are giving it a default size to load if no size is explicitly given; `15` in this case.

Example usage:

```cpp
learning::vector<int> a;
```

### Parameterized Constructor

```cpp
vector(size_t c): size_(0), capacity_(c), data_(new T[c]){}
```

Here we are giving the constructor a size we want the vector to be. 
In this case, we are using a member initialization list by giving each member variable an amount. 
Since there is nothing inside the vector at initialization, we give it the size of zero. 
Then, we pass the capacity directly to the variable `capacity_`. 
Lastly, we dynamically allocate an array on the heap and assigning the pointer returned by that allocation directly to `data_`.

Example usage: 

```cpp
learning::vector<int> a(100);
```

### Copy Constructor

```cpp
vector& operator=(const vector<T> &v){
	if (this != &other) { copy(other); }
	return *this;
}
```

The copy constructor relies on operator overloading for it to function. 
This is when an operator (`+`, `-`, `=`, `==`, etc) is redefined to serve a specific purpose in a class instance. 
You can overload the same operator in two distinct classes and they will function independent of one another.
Please refer to the `External Links` section for more information about operator overloading.
We first check if both instances of the vector class are not the same.
If they are distinct vectors, we can migrate the contents of variable on the **right** side of the equal sign into the variable on the **left** side of the equal sign.
Else, we return the object on the **left** side of the equal sign, telling the compiler that **left** is equal to itself.

Example usage:

```cpp
learning::vector a(100);
a.push_back(5); // content is now 5
learning::vector b(100); // empty
b = a; // b will now have the contents of 5 aswell
```

### Destructor

```cpp
vector<T>::~vector(){ 
	delete[] data_;
	data_ = nullptr;
}
```

Delete the contents of the `data_` array and set it's pointer to NULL preventing a dangling pointer.


### copy

```cpp
void vector<T>::copy(const vector<T>& other){
	if(data_ != nullptr) { delete[] data_; }
	size_ = other.size_;
	capacity_ = other.capacity_;
	data_ = new T[size_];
	std::copy(other.data_, other.data_+other.size_, data_);
}
```

`copy` is a helper function that allows for the "self-expanding" aspect of vectors to be implemented.
We check if the `data_` array is only a `nullptr` and will proceed to delete it if it points to some data. 
Notice the `delete` keyword has an extra `[]` which indicates that we want to "array delete".
`size_` and `capacity_` variables are the attributes to the current vector that will inherit the other vector's attributes.
Since we initially deleted the contents of the current `data_` we need to then allocate another array with the size of the new array.
Copying of the `data_` from one array to another is facilitated through `std::copy` which is apart of the `algorithm` header.

`std::copy`'s instantiation is as follows:

```cpp
std::copy(a, b, c);
// a --> points to the source of the new data (beginning of the array)
// b --> points to the source of the new data but at the end most point (end of the array)
// c --> points to the destination of where the new data will be copied (beginning of destination)
```

### size

```cpp
size_t vector<T>::size() const{ return size_; }
```

Return the current size of the vector, which is the number of elements currently being held, not the entire capacity. `size_t` is the return type.

### capacity

```cpp
size_t vector<T>::capacity() const { return capacity_; }
```

Return the capacity capability of the vector. `size_t` is the return type.

### print

```cpp
void vector<T>::print(){
	for(size_t i = 0; i < size_; ++i) { std::cout << data_[i] << std::endl; }
}
```

Iterate over the `data_` attribute and print each individual element. 
This does not utilize the begin() and end() functions which the overload `std::ostream` operator does.

### begin

```cpp
T* vector<T>::begin() const {return data_; }
```
Return a pointer to the beginning of the `data_` attribute. 
Can be used in a for each loop.

### end

```cpp
T* vector<T>::end() const { return data_+capacity_; }
```

Return a pointer to the end of the `data_` attribute. 
Can be used in a for each loop.

### front (non const)

```cpp
T& vector<T>::front(){ return operator[](0); }
```

Return the memory location where the beginning of the `data_` attribute.
This is used by the `[]` operator to make direct edits to the `learning::vector` class.

### front (const)

```cpp
T vector<T>::front() const { return operator[](0); }
```

Return the memory location where the beginning of the `data_` attribute.
This is used by the `[]` operator to retrieve a specific element in the `learning::vector`.


### back (non const)

```cpp
T& vector<T>::back(){ return operator[](capacity_ - 1); }
```

Return the memory location where the end of the `data_` attribute.
This is used by the `[]` operator to make direct edits to the `learning::vector` class.

### back (const)

```cpp
T vector<T>::back() const  { return operator[](capacity_ - 1); }
```

Return the memory location where the end of the `data_` attribute.
This is used by the `[]` operator to retrieve a specific element in the `learning::vector`.

### push_back

```cpp
void vector<T>::push_back(T val){
	if(size_ >= capacity_) { 
		resize(2*size_);
	}
	data_[size_++] = val;
}
```
Append one more element to the array.
If the size exceeds the capacity, we need to call `resize` to expand the array to make room for the data.

### pop_back

```cpp
void vector<T>::pop_back(){
	if(capacity_ == 0) { throw new std::invalid_argument("buffer underflow"); }
	else if(capacity_ <= (size_/2)){ resize(size_/2); } // reduce size
	data_[size_--] = T();
	
}
```

When capacity is zero we do not remove elements to prevent a segmentation fault.
We can reduce the size to save on memory if space is not being used.
Lastly, we set the last element to an empty instantiation of the data we have in our `data_` element.

### resize

```cpp
void learning::vector<T>::resize(size_t newsize) {
  if (capacity > newsize) { throw new std::invalid_argument("new buffer size too small for data"); }
  T* newdata = new T[newsize];
  std::copy(data_, data_ + size_, newdata);
  size_ = newsize;
  delete [] data_;
  data_ = newdata;
}
```

This function resizes the dynamically allocated `data_` member.
It checks if the newly presented size is less than the preexisting capacity and will fail if that condition returns true.
We then allocate a new array on the heap with the new size and we copy the old content from the previous `data_` element.
Our `size_` member is updated and we delete, the old `data_` member variable.
Lastly, the newly created array is assigned to the `data_` member.


### vector_test

```cpp
void vector_test(){
	learning::vector<float> iv;

	for (size_t i = 0; i < iv.size(); ++i) { iv.push_back(0.5 + 2 * i); }
	std::cout << "iv is: " << &iv << "   " << iv << "\n";
	assert(iv[0] == 0.5);
	assert(iv[iv.capacity() - 1] == 2 * (iv.size() - 1) + 0.5);

	learning::vector<float> iu(iv);
	std::cout << "after copy c'tor...\niu is: " << &iu << "   " << iu << "\n";
	assert(iv == iu);

	learning::vector<float> it;
	it = iu;
	std::cout << "after operator=...\nit is: " << &iu << "   " << iu << "\n";
	assert(it == iu);

	iv.push_back(90.9);
	iv.push_back(900.9);
	iv.push_back(90000.9);
	std::cout << "after adding more data, iv is now..." << iv << "\n";

	while (iv.size() > 5) {
	iv.pop_back();
	std::cout << "iv is now..." << iv << "\n";
	}

}
```



# External Links

- [Microsoft C++ Constructor Documentation](https://docs.microsoft.com/en-us/cpp/cpp/constructors-cpp?view=vs-2019)
- [TutorialsPoint Operator Overloading Section](https://www.tutorialspoint.com/cplusplus/cpp_overloading.htm)
- [Friend Declaration via cppreference](https://en.cppreference.com/w/cpp/language/friend)
- [How std::ostream operator functions in various scenarios](https://stackoverflow.com/questions/2828280/friend-functions-and-operator-overloading-what-is-the-proper-way-to-overlo)
