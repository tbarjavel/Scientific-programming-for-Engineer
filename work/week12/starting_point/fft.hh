#ifndef FFT_HH
#define FFT_HH
/* ------------------------------------------------------ */
#include "matrix.hh"
#include "my_types.hh"
#include <fftw3.h>
/* ------------------------------------------------------ */

/**

This file defines an FFT structure that is a wrapper around the FFTW library.
In particular, it defines 3 functions to work with signals of complex numbers:
- the transform() function to compute the forward FFT of a complex signal
- the itransform() function to compute the inverse FFT of a complex signal
- the computeFrequencies() function to compute the sample frequencies of the
    forward FFT of a complex signal (i.e. the coordinates of the signal in the Fourier space).
    The Laplacian of these frequencies is then used to sovle the heat equation in the Fourier space.

*/
struct FFT {

  static Matrix<complex> transform(Matrix<complex>& m);
  static Matrix<complex> itransform(Matrix<complex>& m);

  static Matrix<complex> computeFrequencies(int size);

};

/* ------------------------------------------------------ */

inline Matrix<complex> FFT::transform(Matrix<complex>& m_in) {

  // Check memory allocation of input matrix
  if (m_in.data() == nullptr) {
    throw std::runtime_error("no memory allocated for m_in");
  }

  // Get matrix size and initialize output matrix
  int N = m_in.size();
  Matrix<complex> m_out(N);

  // Initialize input and output 2D signals
  auto in = (fftw_complex*) m_in.data();
  auto out = (fftw_complex*) m_out.data();

  // Create, execute and destroy FFT plan
  fftw_plan p = fftw_plan_dft_2d(N, N, in, out, FFTW_FORWARD, FFTW_ESTIMATE);
  fftw_execute(p);

  // Destroy plan
  fftw_destroy_plan(p);
  // fftw_free(in); fftw_free(out);

  // Return FFT matrix
  return m_out;
}

/* ------------------------------------------------------ */

inline Matrix<complex> FFT::itransform(Matrix<complex>& m_in) {

  // Check memory allocation of input matrix
  if (m_in.data() == nullptr) {
    throw std::runtime_error("no memory allocated for m_in");
  }

  // Get matrix size and initialize output matrix
  int N = m_in.size();
  Matrix<complex> m_out(N);

  // Initialize input and output 2D signals
  auto in = (fftw_complex*) m_in.data();
  auto out = (fftw_complex*) m_out.data();

  // Create, execute and destroy inverse FFT plan
  fftw_plan p = fftw_plan_dft_2d(N, N, in, out, FFTW_BACKWARD, FFTW_ESTIMATE);
  fftw_execute(p);

  // Destroy plan
  fftw_destroy_plan(p);
  // fftw_free(in); fftw_free(out);

  // Divide output matrix by factor N2 (needed for 2D arrays)
  m_out /= (N * N);

  // Return inverse FFT matrix
  return m_out;
}

/* ------------------------------------------------------ */

inline Matrix<complex> FFT::computeFrequencies(int size) {

  // Generate 1D frequency vector
  std::vector<float> vec(size);
  if (size % 2 == 0) {  // if size is even
    for (int i = 0; i < size / 2; ++i) {
      vec[i] = (float)i;
    }
    for (int i = size / 2; i < size; ++i) {
      vec[i] = -size / 2  + ((float)i - size / 2);
    }
  } else { // if size is odd
    for (int i = 0; i <= (size - 1) / 2; ++i) {
      vec[i] = (float)i;
    }
    for (int i = (size - 1) / 2 + 1; i < size; ++i) {
      vec[i] = -((size - 1) / 2 + 1)  + ((float)i - (size - 1) / 2);
    }
  }

  // Populate 2D matrix with frequencies vector
  Matrix<complex> m_out(size);
  for (int i = 0; i < size; ++i) {
    for (int j = 0; j < size; ++j) {
      m_out(i, j) = complex(vec[j], 0);
    }
  }

  return m_out;
}


#endif  // FFT_HH
