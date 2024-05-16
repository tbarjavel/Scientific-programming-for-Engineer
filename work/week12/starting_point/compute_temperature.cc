#include <cmath>
#include "compute_temperature.hh"
#include "fft.hh"
#include "material_point.hh"

/* -------------------------------------------------------------------------- */

ComputeTemperature::ComputeTemperature(System& system, Real dt) : dt(dt) {

    // Get the number of material points
    this->N = system.getNbParticles();
    this->sqrtN = sqrt(this->N);

    // Resize matrices accordingly
    this->M_laplacian_q.resize(this->sqrtN);
    this->M_hr.resize(this->sqrtN);
    this->M_theta.resize(this->sqrtN);

    // Compute normalization factor
    this->norm = this->L / (2 * M_PI * this->sqrtN);

    // Compute Fourier domain frequencies
    Matrix<complex> M_q = FFT::computeFrequencies(this->sqrtN);

    // Compute the Laplacian of Fourier domain frequencies
    for (auto&& entry : index(this->M_laplacian_q)) {
        int i = std::get<0>(entry);
        int j = std::get<1>(entry);
        auto& laplacian_q = std::get<2>(entry);
        laplacian_q = pow(M_q(i, j).real() / this->norm, 2) + pow(M_q(j, i).real() / this->norm, 2);
        if (i == 0 && j == 0){
            laplacian_q = 1;
        }
    }
    M_laplacian_q /= this->N;

    // Populate the heat rate and heat source matrices
    Matrix<complex> M_hv(this->sqrtN);
    for (auto&& entry : index(M_hv)) {
        int i = std::get<0>(entry);
        int j = std::get<1>(entry);
        auto& hv = std::get<2>(entry);
        Particle& par = system.getParticle(i * this->sqrtN + j);
        auto& mp = static_cast<MaterialPoint&>(par);
        hv = mp.getHeatDistribution();
        this->M_hr(i, j) = mp.getHeatRate();
    }

    // Compute FFT of heat distribution matrix
    this->M_hv_hat = FFT::transform(M_hv);
    this->M_hv_hat(0, 0) = 0;
}


Matrix<complex> ComputeTemperature::computeDerivative(System& system) {

    // Fill in temperature matrix
    for (auto&& entry : index(this->M_theta)) {
        int i = std::get<0>(entry);
        int j = std::get<1>(entry);
        auto& theta = std::get<2>(entry);
        Particle& par = system.getParticle(i * this->sqrtN + j);
        auto& mp = static_cast<MaterialPoint&>(par);
        theta = mp.getTemperature();
    }

    // Apply FFT transformation to temperature matrix -> Fourier domain
    Matrix<complex> M_theta_hat = FFT::transform(M_theta);

    // Compute time derivative of temperature distribution in the Fourier domain
    Matrix<complex> M_dtheta_hat_dt(this->sqrtN);
    for (auto&& entry : index(M_dtheta_hat_dt)) {
        int i = std::get<0>(entry);
        int j = std::get<1>(entry);
        auto& dtheta_hat_dt = std::get<2>(entry);
        auto theta_hat = M_theta_hat(i, j);
        auto hv_hat = this->M_hv_hat(i, j);
        auto hr = this->M_hr(i, j);
        auto laplacian_q = this->M_laplacian_q(i, j);
        if (i == 0 && j == 0){
            theta_hat = 0;
        }
        dtheta_hat_dt = (hv_hat - hr * theta_hat * laplacian_q) / (pho * C);
    }

    // Compute inverse FFT to get time derivative of temperature distribution in the space domain
    Matrix<complex> M_dtheta_dt = FFT::itransform(M_dtheta_hat_dt);
    for (auto&& entry : index(M_dtheta_dt)) {
        int i = std::get<0>(entry);
        int j = std::get<1>(entry);
        auto& dtheta_dt = std::get<2>(entry);
    }

    return M_dtheta_dt;
}


void ComputeTemperature::compute(System& system) {

    Matrix<complex> M_dtheta_dt = this->computeDerivative(system);

    // Update the temperature of all the particles in our system
    for (auto&& entry : index(M_dtheta_dt)) {
        int i = std::get<0>(entry);
        int j = std::get<1>(entry);
        auto& dtheta_dt = std::get<2>(entry);

        Particle& par = system.getParticle(i * this->sqrtN + j);
        auto& mp = static_cast<MaterialPoint&>(par);

        mp.getTemperature() += dtheta_dt.real() * this->dt;
     }
}

/* -------------------------------------------------------------------------- */
