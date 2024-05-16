#include "vector.hh"

Real& Vector::operator[](UInt i) {
}
const Real& Vector::operator[](UInt i) const {
}

Real Vector::squaredNorm() const {
}

/* -------------------------------------------------------------------------- */

Vector& Vector::operator+=(const Vector& vec) {
  return *this;
}

Vector& Vector::operator-=(const Vector& vec) {
  return *this;
}

Vector& Vector::operator*=(Real val) {
  return *this;
}

Vector& Vector::operator/=(Real val) {
  return *this;
}

/* -------------------------------------------------------------------------- */

Vector& Vector::operator=(const Vector& vec) {
  return *this;
}

Vector& Vector::operator=(Real val) {
  return *this;
}

/* -------------------------------------------------------------------------- */

Vector operator+(const Vector& a, const Vector& b) {
}

Vector operator-(const Vector& a, const Vector& b) {
}

Vector operator*(const Vector& a, Real val) {
}

Vector operator*(Real val, const Vector& a) {
  return a * val;
}

Vector operator/(const Vector& a, Real val) {
}

/* -------------------------------------------------------------------------- */

/// standard output stream operator
std::ostream& operator<<(std::ostream& stream, const Vector& _this) {
  return stream;
}

/* -------------------------------------------------------------------------- */
/// standard input stream operator
std::istream& operator>>(std::istream& stream, Vector& _this) {
  return stream;
}
