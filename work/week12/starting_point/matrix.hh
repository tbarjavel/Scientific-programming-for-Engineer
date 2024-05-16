#ifndef MATRIX_HH
#define MATRIX_HH
/* ------------------------------------------------------ */
#include "my_types.hh"
#include <algorithm>
#include <array>
#include <tuple>
#include <vector>
/* ------------------------------------------------------ */
//The *matrix.hh* file defines several template classes to work with matrices of any data type.


/**
 * \Brief Allows iteration over a Matrix object
 *
 * This template is an abstract object allowing iteration over Matrix objects.
 *It contains a pointer to a Matrix object as well as a size and an index field referring to the size of the matrix and the current index.
 *It also contains several operators:
 *- the ++ operator handles iteration by just incrementing the index field
 *- the * operator (i.e. accessor) returns the content of the i-th element of the matrix (i.e. at the current index)
 *- the != operator checks for inequality of index fields between the current operator and another operator
 */
template <typename T>
struct MatrixIterator {
  MatrixIterator(UInt index, UInt size, T* ptr)
      : index(index), size(size), ptr(ptr){};

  T& operator*() { return ptr[index]; };

  void operator++() { index++; };

  bool operator!=(MatrixIterator& other) { return this->index != other.index; };

  int index, size;
  T* ptr;
};
/* ------------------------------------------------------ */

/**

\Brief Defines a matrix object with its own methods

This template is an abstract data type representing a 2D square (NxN) matrix.
Its underlying data container is a 1D std::vector.
It also contains several methods and operators:
- the size(), rows() and cols() methods all return the size (N) of the matrix, which is the square root of the number of elements in the 1D vector (NxN)
- the resize() method resizes the matrix by resizing the underlying data vector
- the accessor operator returns, for a pair of indexes (i, j), the element of the 1D vector at the corresponding serialized index (j * N + i)
- the /= operator handles element-wise division of the matrix by a scalar
- the data() method returns the underlying data vector
- the begin() and end() methods return iterator objects that can point to the first and last elements of the matrix, which can then be used in range for loop to iterate over the matrix elements.

*/
template <typename T>
struct Matrix {

  Matrix(){};
  Matrix(UInt size) { resize(size); };

  UInt rows() { return this->size(); };
  UInt cols() { return this->size(); };
  UInt size() { return std::sqrt(storage.size()); };

  void resize(UInt size) { storage.resize(size * size); }
  T& operator()(UInt i, UInt j) { return storage[j * this->size() + i]; }

  Matrix& operator/=(const T& c) {
    std::for_each(storage.begin(), storage.end(), [&c](auto& v) { v /= c; });
    return *this;
  };

  Matrix& operator*=(const T& c) {
    std::for_each(storage.begin(), storage.end(), [&c](auto& v) { v *= c; });
    return *this;
  };

  T* data() { return &storage[0]; };

  std::vector<T> storage;

  MatrixIterator<T> begin() {
    return MatrixIterator<T>(0, this->size(), this->data());
  };
  MatrixIterator<T> end() {
    return MatrixIterator<T>(storage.size(), this->size(), this->data());
  };
};

/* ------------------------------------------------------ */

/**
/Brief Iterates over the matrix indexes as tuples (i,j,x): (matrix indexes i, j and x the pointed element )

This template defines a more complex type of abstract operator that inherits from MatrixIterator,
but with overwritten accessor element that now returns a 3 elements (i, j, x) tuple, where x
is the pointed element, i and j represent the indexes of the element along both matrix dimensions.
*/
template <typename T>
struct MatrixIndexIterator : public MatrixIterator<T> {
  MatrixIndexIterator(UInt index, UInt size, T* ptr)
      : MatrixIterator<T>(index, size, ptr){};

  std::tuple<UInt, UInt, T&> operator*() {

    int i = this->index % this->size;
    int j = this->index / this->size;
    return std::tuple<UInt, UInt, T&>(i, j, this->ptr[this->index]);
  };
};

/* ------------------------------------------------------ */


/**
/Brief

This template defines a wrapper around the Matrix template in which the begin and end operators
are of type *MatrixIndexIterator*, and can then be used in different types of range for loops.
The index() method can be used to convert a "simple" Matrix object into an IndexedMatrix object.

Finally, the std::iterator_traits template is used to define the data type used by the MatrixIterator objects when they are then used in other parts of the code.

*/
template <typename T>
struct IndexedMatrix {

  IndexedMatrix(Matrix<T>& mat) : mat(mat){};

  MatrixIndexIterator<T> begin() {
    return MatrixIndexIterator<T>(0, mat.size(), mat.data());
  };
  MatrixIndexIterator<T> end() {
    return MatrixIndexIterator<T>(mat.storage.size(), mat.size(), mat.data());
  };

private:
  Matrix<T>& mat;
};
/* ------------------------------------------------------ */

template <typename T>
IndexedMatrix<T> index(Matrix<T>& mat) {
  return IndexedMatrix<T>(mat);
}
/* ------------------------------------------------------ */

namespace std {
  template <typename T>
  struct iterator_traits<MatrixIterator<T>> {
    using value_type = T;
  };
}

/* ------------------------------------------------------ */

#endif //MATRIX
