double *get_scalar() {

  double *v = new double;
  return v;
}

double *get_vector(int n) {

  double *v = new double[n];
  return v;
}

int main() {

  double *scalar = get_scalar();
  // ... do what I need
  delete scalar;

  double *vector = get_vector(10);
  // ... do what I need
  delete[] vector;
}