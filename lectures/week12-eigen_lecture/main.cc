#include <Eigen/Dense>
#include <Eigen/Sparse>
#include <array>
#include <iostream>
#include <memory>

void vectors() {

  // https://eigen.tuxfamily.org/dox/group__TutorialMatrixClass.html
  Eigen::VectorXd v(2);

  // https://eigen.tuxfamily.org/dox/group__TutorialMatrixArithmetic.html
  // arithmetic
  v(0) = 3;    // parentheses
  v[1] += 2.5; // or square brackets

  double res = v.transpose() * v;
  auto norm = v.norm();

  // access to shape
  std::cout << "nb_rows: " << v.rows() << std::endl;
  std::cout << "nb_cols: " << v.cols() << std::endl;
  std::cout << "size: " << v.size() << std::endl;

  // change size
  v.resize(10);

  // different types
  Eigen::VectorXi v_int(2);
  Eigen::VectorXf v_float(2);
  Eigen::VectorXcd v_complex_double(2);
  auto real_part = v_complex_double.real();
}

void vectors_init() {
  int N = 5;
  Eigen::VectorXd v(N);

  // v = np.array([1,2,3,4,5])
  v << 1, 2, 3, 4, 5;
  // v = np.random.random(N)
  v = Eigen::VectorXd::Random(N);
  // v = np.random.random(N)
  v = Eigen::VectorXd::LinSpaced(N, -1., 1.);
  // v = np.zeros(N)
  v = Eigen::VectorXd::Zero(N);
  // v = np.ones(N)
  v = Eigen::VectorXd::Ones(N);
  // v = np.ones(N)*42
  v = Eigen::VectorXd::Constant(N, 42.);
  v = Eigen::VectorXd::Ones(N) * 42.;
}

void matrices() {
  // https://eigen.tuxfamily.org/dox/group__TutorialMatrixClass.html
  Eigen::MatrixXd m(3, 3);

  // access to shape
  std::cout << "nb_rows: " << m.rows() << std::endl;
  std::cout << "nb_cols: " << m.cols() << std::endl;
  std::cout << "size: " << m.size() << std::endl;
  std::cout << "m = " << m << std::endl;
  std::cout << "m.T = " << m.transpose() << std::endl;

  // resize
  m.resize(10, 2);

  // other types
  Eigen::MatrixXcd m_complex_double(3, 3);
  Eigen::MatrixXi m_int(3, 3);
}

void vectors_static() {

  // variable size => dynamic allocation (of course!)
  Eigen::VectorXd v_undefined_size;
  // In Eigen, this is equivalent to
  Eigen::Matrix<double, -1, 1> v_undefined_size2;

  // Fixed-size (static allocation) are also possible
  Eigen::Vector4d v4; // Eigen::Matrix<double, 4, 1>
  Eigen::Vector3d v3; // Eigen::Matrix<double, 3, 1>
  Eigen::Vector2d v2; // Eigen::Matrix<double, 2, 1>
  Eigen::Matrix3d m;  // Eigen::Matrix<double, 3, 3>
}

void linalg() {
  // https://eigen.tuxfamily.org/dox/group__TutorialLinearAlgebra.html
  // https://eigen.tuxfamily.org/dox/group__TopicLinearAlgebraDecompositions.html
  Eigen::Vector3d v = Eigen::Vector3d::Ones();
  Eigen::Matrix3d m = Eigen::Vector3d::Constant(3).asDiagonal();

  // matrix vector multiplication
  auto res = m * v;

  std::cout << v << std::endl;
  std::cout << m << std::endl;
  std::cout << res << std::endl;

  // determinent
  auto det = m.determinant();
  // inversion
  auto inv = m.inverse();
  // norm
  auto norm = m.norm();

  // matrix LU factorization
  auto facto = m.fullPivLu();
  // system resolution
  auto res2 = facto.solve(res);
  std::cout << res2 << std::endl;
}

void blocks() {
  // https://eigen.tuxfamily.org/dox/group__TutorialBlockOperations.html

  Eigen::MatrixXd m(3, 3);
  m << 1, 2, 3, 4, 5, 6, 7, 8, 9;
  std::cout << m << std::endl;

  // extract a row
  auto row_1 = m.row(1);
  std::cout << row_1 << std::endl;
  // extract a column
  auto col_1 = m.col(1);
  std::cout << col_1 << std::endl;

  // extract static block of size 2x3 starting at position 1,0
  auto b_static = m.block<2, 3>(1, 0);
  std::cout << b_static << std::endl;

  // extract dynamic block of size 2x3 starting at position 1,0
  auto b_dynamic = m.block(1, 0, 2, 3);
  std::cout << b_dynamic << std::endl;
}

void maps() {

  // How to control the memory: maps

  // from a std vector
  std::vector<double> v{1, 2, 3, 4, 5, 6, 7, 8, 9};
  Eigen::Map<Eigen::Matrix3d> m(&v[0]);
  std::cout << "from vector: " << m << std::endl;

  // from a pointer vector
  auto *ptr = new double[9];
  Eigen::Map<Eigen::Matrix3d> m_ptr(ptr);
  std::cout << "from ptr: " << m_ptr << std::endl;

  // from a std::array
  std::array<double, 9> array;
  Eigen::Map<Eigen::Matrix3d> m_array(&array[0]);
  std::cout << "from array: " << m_array << std::endl;
}

void reshape() {

  // changing the representation, but not the memory support
  // m = np.array([[1,2,3], [4,5,6], [7,8,9]])
  Eigen::MatrixXd m(3, 3);
  m << 1, 2, 3, 4, 5, 6, 7, 8, 9;

  // m_reshape = m.reshape(9)
  Eigen::Map<Eigen::Matrix<double, 9, 1> > m_reshape(m.data());
  std::cout << "reshaping: " << m << "\n => " << m_reshape << std::endl;

  // Eigen is ColumnMajor, to force RowMajor (like python)
  Eigen::Matrix<double, 3, 3, Eigen::RowMajor> m2;
  m2 << 1, 2, 3, 4, 5, 6, 7, 8, 9;

  Eigen::Map<Eigen::VectorXd> m2_reshape(m2.data(), m2.size());
  std::cout << "reshaping: " << m2 << "\n => " << m2_reshape << std::endl;
}

void sparse_matrix() {
  // https://eigen.tuxfamily.org/dox/group__TutorialSparse.html
  // declares a column-major sparse matrix type of double

  Eigen::SparseMatrix<double> mat(3, 3);
  // set the sparse matrix as a diagonal
  mat = Eigen::Vector3d::Constant(3).asDiagonal();

  // set a constant vector filled with ones
  Eigen::Vector3d v = Eigen::Vector3d::Ones();
  mat.makeCompressed();

  // construct a sparse LV solver
  Eigen::SparseLU<Eigen::SparseMatrix<double>> solver;
  // do the LU factorization
  solver.compute(mat);
  
  if (solver.info() != Eigen::Success) {
    // decomposition failed
    return;
  }

  // solve the system
  auto x = solver.solve(v);
  if (solver.info() != Eigen::Success) {
    // solving failed
    return;
  }
  std::cout << x << std::endl;
}

void arrays() {
  // https://eigen.tuxfamily.org/dox/group__TutorialArrayClass.html
  // Arrays provide general purpose arrays
  // algebra is component-wise

  Eigen::ArrayXXd array(100, 3);
  Eigen::ArrayX3d array2(100, 3);

  auto res1 = array * array2; // component-wise operation
  auto res2 = array - array2; // component-wise operation
  auto res3 = array.col(0).sin();
  auto res4 = array.col(0).sqrt();
  // np.exp(array[:, 0])
  auto res5 = array.col(0).exp();
  // np.tanh(array[:, 0])
  auto res6 = array.col(0).tanh();
  
  // converting to matrix
  Eigen::MatrixXd res7 = array.matrix();
  // back to array
  Eigen::ArrayXXd res8 = res7.array();
}

template <typename Derived>
void template_function(const Eigen::EigenBase<Derived> &m) {
  std::cout << "nb_rows: " << m.rows() << std::endl;
  std::cout << "nb_cols: " << m.cols() << std::endl;
  std::cout << "size: " << m.size() << std::endl;
}

template <typename Derived>
void template_function_matrix(const Eigen::MatrixBase<Derived> &m) {
  std::cout << "nb_rows: " << m.rows() << std::endl;
  std::cout << "nb_cols: " << m.cols() << std::endl;
  std::cout << "size: " << m.size() << std::endl;
}

void generic_function(const Eigen::Ref<Eigen::ArrayXXd> &m) {
  std::cout << "nb_rows: " << m.rows() << std::endl;
  std::cout << "nb_cols: " << m.cols() << std::endl;
  std::cout << "size: " << m.size() << std::endl;
}

void generic_function_matrix(const Eigen::Ref<Eigen::MatrixXd> &m) {
  std::cout << "nb_rows: " << m.rows() << std::endl;
  std::cout << "nb_cols: " << m.cols() << std::endl;
  std::cout << "size: " << m.size() << std::endl;
}


void test_generic_function() {
  Eigen::Matrix3d A;
  Eigen::VectorXd v(20);
  Eigen::ArrayXXd a(20, 2);

  template_function(A);
  template_function(v);
  template_function(a);

  generic_function(A);
  generic_function(v);
  generic_function(a);
  
  template_function_matrix(A);
  generic_function_matrix(A);
}

int main() {
  vectors();
  vectors_init();
  matrices();
  vectors_static();
  linalg();
  blocks();
  maps();
  reshape();
  arrays();
  sparse_matrix();
  test_generic_function();
}
