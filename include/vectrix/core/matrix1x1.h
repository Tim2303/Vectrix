//
// Created by Timmimin on 26.06.2025.
//

#ifndef VECTRIX_MATRIX1X1_H
#define VECTRIX_MATRIX1X1_H

#include "base_matrix.h"

// vtx namespace
namespace vtx {
	// Matrix 1x1 class specialization
	template <typename T>
	class matrix<T, 1, 1> {
	public:
#ifndef VTX_NO_ZERO_INIT
		constexpr matrix() noexcept : elements{{ T(0) }} {}
#else
		constexpr matrix() = default;
#endif

		// One parameter constructor (fill matrix with value)
		constexpr explicit matrix(T num) noexcept : elements{{num}} {}

		// Matrix equality operator
		constexpr bool operator==(const matrix& m) const noexcept {
			return elements[0][0] == m.elements[0][0];
		}

		// Matrix inequality operator
		constexpr bool operator!=(const matrix& m) const noexcept {
			return elements[0][0] != m.elements[0][0];
		}

		// Row access operator
		constexpr T* operator[](size_t row) noexcept {
			assert(row == 0);
			return &elements[0][0];
		}

		// Const row access operator
		constexpr const T* operator[](size_t row) const noexcept {
			assert(row == 0);
			return &elements[0][0];
		}

		// Element access (row, column)
		constexpr T& operator()(size_t row, size_t col) noexcept {
			assert(row == 0 && col == 0);
			return elements[0][0];
		}

		// Const elements[0][0] access (row, column)
		constexpr const T& operator()(size_t row, size_t col) const noexcept {
			assert(row == 0 && col == 0);
			return elements[0][0];
		}

		// Pointer to data
		constexpr T* data() noexcept { return &elements[0][0]; }
		constexpr const T* data() const noexcept { return &elements[0][0]; }

		// Negation operator
		constexpr matrix operator-() const noexcept { return matrix(-elements[0][0]); }

		// Addition operator
		constexpr matrix operator+(const matrix& m) const noexcept {
			return matrix(elements[0][0] + m.elements[0][0]);
		}

		// Addition to current operator
		constexpr matrix& operator+=(const matrix& m) noexcept {
			elements[0][0] += m.elements[0][0];
			return *this;
		}

		// Subtraction operator
		constexpr matrix operator-(const matrix& m) const noexcept {
			return matrix(elements[0][0] - m.elements[0][0]);
		}

		// Subtraction from current operator
		constexpr matrix& operator-=(const matrix& m) noexcept {
			elements[0][0] -= m.elements[0][0];
			return *this;
		}

		// Scalar multiplication operator
		constexpr matrix operator*(const T scalar) const noexcept {
			return matrix(elements[0][0] * scalar);
		}

		// Scalar multiplication with current operator
		constexpr matrix& operator*=(const T scalar) noexcept {
			elements[0][0] *= scalar;
			return *this;
		}

		// Scalar division operator
		constexpr matrix operator/(const T scalar) const noexcept {
			return matrix(elements[0][0] / scalar);
		}

		// Scalar division with current operator
		constexpr matrix& operator/=(const T scalar) noexcept {
			elements[0][0] /= scalar;
			return *this;
		}

		// Matrix multiplication (for compatible matrices)
		template <size_t P>
		constexpr matrix<T, 1, P> operator*(matrix<T, 1, P> m) const noexcept {
			m *= elements[0][0];
			return m;
		}

		// Matrix multiplication with current (only for square matrices)
		constexpr matrix& operator*=(const matrix& m) noexcept {
			elements[0][0] *= m.elements[0][0];
			return *this;
		}

		// Identity
		static constexpr matrix identity() noexcept { return matrix(1); }

		// Determinant (only for square matrices)
		constexpr T determinant() const noexcept { return elements[0][0]; }

		// Inverse matrix (only for square matrices)
		constexpr matrix inverse() const noexcept { return matrix(1 / elements[0][0]); }

		// Trace (sum of diagonal elements, only for square matrices)
		constexpr T trace() const noexcept { return elements[0][0]; }

		// Frobenius norm (square root of sum of squares of all elements)
		constexpr T frobeniusNorm() const noexcept { return vtx::math::abs(elements[0][0]); }

		// Matrix-vector multiplication (for MxN matrix and Nx1 vector)
		constexpr vector<T, 1> operator*(const vector<T, 1>& v) const noexcept {
			return vector<T, 1>(elements[0][0] * v[0]);
		}

		static constexpr size_t rows() noexcept { return 1; }

		static constexpr size_t cols() noexcept { return 1; }

	private:
		T elements[1][1];

		template <typename, size_t, size_t>
		friend class matrix;

	};  // class matrix

	// Set other names for matrix 1x1
	template <typename T>
	using mat1x1 = matrix<T, 1, 1>;

}  // namespace vtx

#endif  // VECTRIX_MATRIX1X1_H
