#include <iostream>
#include <string>
#include <array>
#include <cmath>
#include <complex>
#include <Eigen/Dense> 
#include <Eigen/LU>

// Namespace
using namespace std;

// function prototypes
string decomposicao_zyz(Eigen::Matrix2cd M);
Eigen::Matrix2cd Rz(double theta);
Eigen::Matrix2cd Ry(double theta);

// global variables
complex<double> i(0.0, 1.0);
complex<double> e = exp(1.0);

int main() {
    // Qubit |0⟩ - [1, 0]
    // Eigen::Vector2cd qubit0;
    // qubit0 << 1, 0;
    // std::cout << qubit0 << "\n";

    // // rotação π em Y
    // Eigen::Matrix2cd ry_pi = Ry(M_PI);

    // // fase global 
    // complex<double> globalPhase = 1; //exp(i * (M_PI / 2.0));

    // Eigen::Vector2cd Mr = globalPhase * ry_pi * qubit0;
    // std::cout << "\nresultado:\n\n" << Mr << "\n";

    complex<double> um_i(1.0 / sqrt(2), 1.0 / sqrt(2));
    complex<double> um_menos_i(1.0 / sqrt(2), -1.0 / sqrt(2));

    Eigen::Matrix2cd inputMatrix;
    inputMatrix << um_i, um_menos_i,
                   um_menos_i, um_i;

    cout << decomposicao_zyz(inputMatrix);

    return 0;
}

std::string decomposicao_zyz(Eigen::Matrix2cd M) {

    std::complex<double> a00 = M(0, 0);
    std::complex<double> a01 = M(0, 1);
    std::complex<double> a10 = M(1, 0);

    double x00 = std::arg(a00);
    double x01 = std::arg(-a01);
    double x10 = std::arg(a10);

    Eigen::Vector3d b;
    b << x00, x01, x10;

    cout << b << "\n";

    Eigen::Matrix3d A;
    A << 1, -0.5, -0.5,
         1, -0.5,  0.5,
         1,  0.5, -0.5;

    // Find x for Ax = b
    Eigen::Vector3d x = A.lu().solve(b);

    double alpha = x(0);
    double beta  = x(1);
    double delta = x(2);

    cout << "\nalpha: " << alpha << "\nbeta: " << beta << "\ndelta: " << delta << "\n";

    // TODO: return qasm text
    return "QASM not implemented!\n";
}

Eigen::Matrix2cd Ry(double theta) {
    Eigen::Matrix2cd matriz;
    matriz << cos(theta/2.0), -sin(theta/2.0),
              sin(theta/2.0),  cos(theta/2.0);
    return matriz;
}
Eigen::Matrix2cd Rz(double theta) {
    Eigen::Matrix2cd matriz;
    matriz << pow(e, -((theta/2) * i)), 0,
              0,  pow(e, ((theta/2) * i));
    return matriz;
}