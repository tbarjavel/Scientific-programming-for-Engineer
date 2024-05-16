#include <cmath>

#include "vector.hh"

Real& Vector::operator[](UInt i) {
  return this->values[i];
}
const Real& Vector::operator[](UInt i) const {
  return this->values[i];
}

Real Vector::squaredNorm() const {
  Real ss = 0.;
  for (UInt i = 0; i < this->dim; ++i) {
    ss += pow(this->values[i], 2);
  }
  return ss;
}

/* -------------------------------------------------------------------------- */

Vector& Vector::operator+=(const Vector& vec) {
  for (UInt i = 0; i < this->dim; ++i) {
    this->values[i] += vec[i];
  }
  return *this;
}

Vector& Vector::operator-=(const Vector& vec) {
  for (UInt i = 0; i < this->dim; ++i) {
    this->values[i] -= vec[i];
  }
  return *this;
}

Vector& Vector::operator*=(Real val) {
  for (UInt i = 0; i < this->dim; ++i) {
    this->values[i] *= val;
  }
  return *this;
}

Vector& Vector::operator/=(Real val) {
  for (UInt i = 0; i < this->dim; ++i) {
    this->values[i] /= val;
  }
  return *this;
}

/* -------------------------------------------------------------------------- */

Vector& Vector::operator=(const Vector& vec) {
  for (UInt i = 0; i < this->dim; ++i) {
    this->values[i] = vec[i];
  }
  return *this;
}

Vector& Vector::operator=(Real val) {
  for (UInt i = 0; i < this->dim; ++i) {
    this->values[i] = val;
  }
  return *this;
}

/* -------------------------------------------------------------------------- */

Vector operator+(const Vector& a, const Vector& b) {
  Vector v;
  for (UInt i = 0; i < a.dim; ++i) {
    v[i] =  a[i] + b[i];
  }
  return v;
}

Vector operator-(const Vector& a, const Vector& b) {
  Vector v;
  for (UInt i = 0; i < a.dim; ++i) {
    v[i] =  a[i] - b[i];
  }
  return v;
}

Vector operator*(const Vector& a, Real val) {
  Vector v;
  for (UInt i = 0; i < a.dim; ++i) {
    v[i] =  a[i] * val;
  }
  return v;
}

Vector operator*(Real val, const Vector& a) {
  Vector v;
  for (UInt i = 0; i < a.dim; ++i) {
    v[i] = val * a[i];
  }
  return v;
}

Vector operator/(const Vector& a, Real val) {
  Vector v;
  for (UInt i = 0; i < a.dim; ++i) {
    v[i] = a[i] / val;
  }
  return v;
}

/* -------------------------------------------------------------------------- */

/// standard output stream operator
std::ostream& operator<<(std::ostream& stream, const Vector& _this) {
  for (UInt i = 0; i < _this.dim-1; ++i) {
    stream << _this.values[i] << " ";
  }
  stream << _this.values[_this.dim-1];
  return stream;
}

/* -------------------------------------------------------------------------- */
/// standard input stream operator
std::istream& operator>>(std::istream& stream, Vector& _this) {
  for (UInt i = 0; i < _this.dim; ++i) {
    stream >> _this.values[i];
  }
  return stream;
}
