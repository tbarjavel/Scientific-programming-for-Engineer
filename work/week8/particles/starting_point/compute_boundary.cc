#include "compute_boundary.hh"
/* -------------------------------------------------------------------------- */
ComputeBoundary::ComputeBoundary(const Vector& xmin, const Vector& xmax)
    : xmin(xmin), xmax(xmax) {
  Vector d = xmax - xmin;
  for (UInt i = 0; i < Vector::dim; ++i)
    if (d[i] < 0) {
      std::cout << "XMax and XMin do not form a domain range" << std::endl;
      std::exit(1);
    }
}
/* -------------------------------------------------------------------------- */

void ComputeBoundary::compute(System& system) {
}

/* -------------------------------------------------------------------------- */
