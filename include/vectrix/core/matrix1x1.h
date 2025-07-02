//
// Created by Timmimin on 26.06.2025.
//

#ifndef VECTRIX_MATRIX1X1_H
#define VECTRIX_MATRIX1X1_H

#include "base_matrix.h"

// vtx namespace
namespace vtx
{
    // Matrix 1x1 class specialization
    template<typename T>
    class matrix<T, 1, 1> {
    public:
        T element;

        // Class default constructor
        constexpr matrix() = default;

        // One parameter constructor (fill matrix with value)
        constexpr explicit matrix( const T num ) noexcept {
            element = num;
        }

        // Matrix equality operator
        constexpr bool operator==( const matrix &m ) const noexcept {
            return element == m.element;
        }

        // Matrix inequality operator
        constexpr bool operator!=(const matrix &m) const noexcept {
            return element != m.element;
        }

        // Row access operator
        constexpr T* operator[]( size_t row ) noexcept {
#ifdef _DEBUG
            assert(row != 0);
#endif
            return &element;
        }

        // Const row access operator
        constexpr const T* operator[]( size_t row ) const noexcept {
#ifdef _DEBUG
            assert(row != 0);
#endif
            return element;
        }

        // Element access (row, column)
        constexpr T& operator()( size_t row, size_t col ) noexcept {
#ifdef _DEBUG
            assert(row != 0 && col != 0);
#endif
            return element;
        }

        // Const element access (row, column)
        constexpr T operator()( size_t row, size_t col ) const noexcept {
#ifdef _DEBUG
            assert(row != 0 && col != 0);
#endif
            return element;
        }

        // Pointer to data
        constexpr T* data() noexcept { return &element; }
        constexpr const T* data() const noexcept { return &element; }

        // Negation operator
        constexpr matrix operator-() const noexcept {
            return matrix(-element);
        }

        // Addition operator
        constexpr matrix operator+( const matrix &m ) const noexcept {
            return matrix(element + m.element);
        }

        // Addition to current operator
        constexpr matrix& operator+=( const matrix &m ) noexcept {
            element += m.element;
            return *this;
        }

        // Subtraction operator
        constexpr matrix operator-( const matrix &m ) const noexcept {
            return matrix(element - m.element);
        }

        // Subtraction from current operator
        constexpr matrix& operator-=( const matrix &m ) noexcept {
            element -= m.element;
            return *this;
        }

        // Scalar multiplication operator
        constexpr matrix operator*( const T scalar ) const noexcept {
            return matrix(element * scalar);
        }

        // Scalar multiplication with current operator
        constexpr matrix& operator*=( const T scalar ) noexcept {
            element *= scalar;
            return *this;
        }

        // Scalar division operator
        constexpr matrix operator/( const T scalar ) const noexcept {
            return matrix(element / scalar);
        }

        // Scalar division with current operator
        constexpr matrix& operator/=( const T scalar ) noexcept {
            element /= scalar;
            return *this;
        }

        // Matrix multiplication (for compatible matrices)
        template<size_t P>
        constexpr matrix<T, 1, P> operator*( const matrix<T, 1, P> &m ) const noexcept {
            matrix<T, 1, P> result;
            for (size_t j = 0; j < P; ++j) {
                result.elements[0][j] = element * m.elements[0][j];
            }

            return result;
        }

        // Matrix multiplication with current (only for square matrices)
        constexpr matrix& operator*=( const matrix &m ) noexcept {
            *this = *this * m;
            return *this;
        }

        // Identity matrix (only for square matrices)
        static constexpr matrix identity() noexcept {
            return matrix(1);
        }

        // Determinant (only for square matrices)
        constexpr T determinant() const noexcept {
            return element;
        }

        // Inverse matrix (only for square matrices)
        constexpr matrix inverse() const noexcept {
            return matrix(1 / element);
        }

        // Trace (sum of diagonal elements, only for square matrices)
        constexpr T trace() const noexcept {
            return element;
        }

        // Frobenius norm (square root of sum of squares of all elements)
        constexpr T frobeniusNorm() const noexcept {
            return element;
        }

        // Matrix-vector multiplication (for MxN matrix and Nx1 vector)
        constexpr vector<T, 1> operator*( const vector<T, 1> &v ) const noexcept {
            return vector<T, 1>(element * v[0]);
        }

        constexpr size_t rows() const noexcept {
            return 1;
        }

        constexpr size_t cols() const noexcept {
            return 1;
        }

    }; // class matrix

    // Set other names for matrix 1x1
    template<typename T>
    using mat1x1 = matrix<T, 1, 1>;

} // namespace vtx

#endif //VECTRIX_MATRIX1X1_H
