#include <gtest/gtest.h>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include "my_types.hh"
#include "fft.hh"


/*****************************************************************/
TEST(FFT, transform) {
  UInt N = 512;
  Matrix<complex> m(N);

  Real k = 2 * M_PI / N;
  for (auto&& entry : index(m)) {
    int i = std::get<0>(entry);
    int j = std::get<1>(entry);
    auto& val = std::get<2>(entry);
    val = cos(k * i);
  }

  Matrix<complex> res = FFT::transform(m);

  for (auto&& entry : index(res)) {
    int i = std::get<0>(entry);
    int j = std::get<1>(entry);
    auto& val = std::get<2>(entry);
    if (std::abs(val) > 1e-10)
      std::cout << i << "," << j << " = " << val << std::endl;

    if (i == 1 && j == 0)
      ASSERT_NEAR(std::abs(val), N * N / 2, 1e-10);
    else if (i == N - 1 && j == 0)
      ASSERT_NEAR(std::abs(val), N * N / 2, 1e-10);
    else
      ASSERT_NEAR(std::abs(val), 0, 1e-10);
  }
}
/*****************************************************************/

TEST(FFT, inverse_transform) {
  UInt N = 512;
  Matrix<complex> m(N);

  Real k = 2 * M_PI / N;
  for (auto&& entry : index(m)) {
    int i = std::get<0>(entry);
    int j = std::get<1>(entry);
    auto& val = std::get<2>(entry);
    if ((i == 1 && j == 0) || (i == N - 1 && j == 0)) {
      val = N * N / 2;
    } else {
      val = 0;
    }
  }

  Matrix<complex> res = FFT::itransform(m);

  for (auto&& entry : index(res)) {
    int i = std::get<0>(entry);
    int j = std::get<1>(entry);
    auto& val = std::get<2>(entry);
    ASSERT_NEAR(std::abs(val), std::abs(cos(k * i)), 1e-10);
  }
}


void testComputeFrequencies(UInt N) {

  std::string filename = "test_computeFrequencies_n_" + std::to_string(N) + ".txt";
  std::cout << filename << std::endl;

  // Populate reference frequency matrix from numpy generated file
  Matrix<std::complex<int>> freqs_ref(N);
  std::ifstream is(filename.c_str());

  if (is.is_open() == false) {
    std::cerr << "cannot open file" << std::endl;
    throw;
  }
  std::string line;
  double tmp;
  for (int i=0; i < N; ++i) {
    getline(is, line);
    std::stringstream sstr(line);
    for (int j = 0; j < N; ++j) {
        sstr >> tmp;
        freqs_ref(i, j) = std::complex<int>(tmp, 0);
    }
  }
  is.close();

  // Create frequency matrix with our own implementation
  Matrix<complex> freqs = FFT::computeFrequencies(N);

  // Compare the two matrices
  for (auto&& entry : index(freqs)) {
    int i = std::get<0>(entry);
    int j = std::get<1>(entry);
    auto& val = std::get<2>(entry);
    auto& ref = freqs_ref(i, j);
    ASSERT_NEAR(std::abs(val), std::abs(ref), 1e-10);
  }
}

TEST(FFT, compute_frequencies_even) { testComputeFrequencies(8); }
TEST(FFT, compute_frequencies_odd) { testComputeFrequencies(9); }
