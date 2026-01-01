//
// Created by Timmimin on 21.06.2025.
//

#ifndef VECTRIX_BASE_MATRIX_H
#define VECTRIX_BASE_MATRIX_H

#include "base_vector.h"
#include "vectrix/math/common.h"

namespace vtx {

	template <typename T, size_t M, size_t N>
	class matrix {
	public:
#ifndef VTX_NO_ZERO_INIT
		constexpr matrix() noexcept : elements{} {}
#else
		constexpr matrix() = default;
#endif  // VTX_NO_ZERO_INIT

		// One parameter constructor (fill matrix with value)
		constexpr explicit matrix(T num) noexcept {
			for (size_t i = 0; i < M; ++i) {
				for (size_t j = 0; j < N; ++j) {
					elements[i][j] = num;
				}
			}
		}

		// Get all elements in array class
		// TODO: Move to utility header?
		constexpr std::array<T, M * N> array() const noexcept {
			return to_array_impl(std::make_index_sequence<M * N>{});
		}

		// Initializer list constructor (row-major order)
		constexpr matrix(std::initializer_list<T> list) noexcept {
			assert(list.size() <= M * N);

			size_t k = 0;
			for (T val : list) {
				if (k < M * N) {
					elements[k / N][k % N] = val;
					k++;
				}
			}

#ifndef VTX_NO_ZERO_INIT
			for (; k < M * N; ++k) {
				elements[k / N][k % N] = T(0);
			}
#endif  // VTX_NO_ZERO_INIT
		}

		// Row initializer list constructor
		constexpr matrix(std::initializer_list<std::initializer_list<T>> list) noexcept {
			size_t i = 0;

			for (const auto& row : list) {
				if (i < M) {
					size_t j = 0;

					for (T val : row) {
						if (j < N) {
							elements[i][j] = val;
							j++;
						}
					}

					for (; j < N; ++j) {
						elements[i][j] = T(0);
					}
					i++;
				}
			}

#ifndef VTX_NO_ZERO_INIT
			for (; i < M; ++i) {
				for (size_t j = 0; j < N; ++j) {
					elements[i][j] = T(0);
				}
			}
#endif  // VTX_NO_ZERO_INIT
		}

		// Matrix equality operator
		constexpr bool operator==(const matrix& m) const noexcept {
			for (size_t i = 0; i < M; ++i) {
				for (size_t j = 0; j < N; ++j) {
					if (m.elements[i][j] != elements[i][j]) {
						return false;
					}
				}
			}

			return true;
		}

		// Matrix inequality operator
		constexpr bool operator!=(const matrix& m) const noexcept { return !(*this == m); }

		// Row access operator
		constexpr T* operator[](size_t row) noexcept {
			assert(row < M);
			return elements[row];
		}

		// Const row access operator
		constexpr const T* operator[](size_t row) const noexcept {
			assert(row < M);
			return elements[row];
		}

		// Element access (row, column)
		constexpr T& operator()(size_t row, size_t col) noexcept {
			assert(row < M && col < N);
			return elements[row][col];
		}

		// Const element access (row, column)
		constexpr const T& operator()(size_t row, size_t col) const noexcept {
			assert(row < M && col < N);
			return elements[row][col];
		}

		// Get inner block from matrix
		// <a, b> - block sizes
		// (size_t a1, size_t b1) - left block angle indices
		// TODO: Move to high-level methods module?
		template <size_t a, size_t b>
		constexpr matrix<T, a, b> block(size_t a1, size_t b1) const noexcept {
			matrix<T, a, b> m;
			// TODO: Bounds check
			for (size_t i = 0; i < a; ++i)
				for (size_t j = 0; j < b; ++j) m[i][j] = elements[a1 + i][b1 + j];

			return m;
		}

		// Pointer to data
		constexpr T* data() noexcept { return &elements[0][0]; }
		constexpr const T* data() const noexcept { return &elements[0][0]; }

		// Negation operator
		constexpr matrix operator-() const noexcept {
			matrix result;
			for (size_t i = 0; i < M; ++i) {
				for (size_t j = 0; j < N; ++j) {
					result.elements[i][j] = -elements[i][j];
				}
			}

			return result;
		}

		// Addition to current operator
		constexpr matrix& operator+=(const matrix& m) noexcept {
			for (size_t i = 0; i < M; ++i) {
				for (size_t j = 0; j < N; ++j) {
					elements[i][j] += m.elements[i][j];
				}
			}

			return *this;
		}

		// Addition operator
		constexpr matrix operator+(matrix m) const noexcept {
			matrix result = *this;
			result += m;
			return result;
		}

		// Subtraction from current operator
		constexpr matrix& operator-=(const matrix& m) noexcept {
			for (size_t i = 0; i < M; ++i) {
				for (size_t j = 0; j < N; ++j) {
					elements[i][j] -= m.elements[i][j];
				}
			}

			return *this;
		}

		// Subtraction operator
		constexpr matrix operator-(const matrix& m) const noexcept {
			matrix result = *this;
			result -= m;
			return result;
		}

		// Scalar multiplication with current operator
		constexpr matrix& operator*=(T scalar) noexcept {
			for (size_t i = 0; i < M; ++i) {
				for (size_t j = 0; j < N; ++j) {
					elements[i][j] *= scalar;
				}
			}

			return *this;
		}

		// Scalar multiplication operator
		constexpr matrix operator*(T scalar) const noexcept {
			matrix result = *this;
			result *= scalar;
			return result;
		}

		// Scalar division with current operator
		constexpr matrix& operator/=(T scalar) noexcept {
			for (size_t i = 0; i < M; ++i) {
				for (size_t j = 0; j < N; ++j) {
					elements[i][j] /= scalar;
				}
			}

			return *this;
		}

		// Scalar division operator
		constexpr matrix operator/(T scalar) const noexcept {
			matrix result = *this;
			result /= scalar;
			return result;
		}

		// Matrix multiplication (for compatible matrices)
		template <size_t P>
		constexpr matrix<T, M, P> operator*(const matrix<T, N, P>& m) const noexcept {
			matrix<T, M, P> result;

			for (size_t i = 0; i < M; ++i) {
				for (size_t j = 0; j < P; ++j) {
					T sum = T(0);
					for (size_t k = 0; k < N; ++k) {
						sum += elements[i][k] * m.elements[k][j];
					}
					result.elements[i][j] = sum;
				}
			}

			return result;
		}

		// Matrix multiplication with current (only for square matrices)
		constexpr matrix& operator*=(const matrix& m) noexcept {
			static_assert(M == N, "Matrix must be square for *= operator");
			*this = *this * m;
			return *this;
		}

		// Transpose matrix
		constexpr matrix<T, N, M> transpose() const noexcept {
			matrix<T, N, M> result;

			for (size_t i = 0; i < M; ++i) {
				for (size_t j = 0; j < N; ++j) {
					result.elements[j][i] = elements[i][j];
				}
			}

			return result;
		}

		// Identity matrix (only for square matrices)
		static constexpr matrix identity() noexcept {
			static_assert(M == N, "Identity matrix must be square");
			matrix result;

#ifndef VTX_NO_ZERO_INIT
			for (size_t i = 0; i < M; ++i) {
				result.elements[i][i] = T(1);
			}
#else   // VTX_NO_ZERO_INIT
			for (size_t i = 0; i < M; ++i) {
				for (size_t j = 0; j < N; ++j) {
					result.elements[i][j] = (i == j) ? T(1) : T(0);
				}
			}
#endif  // VTX_NO_ZERO_INIT

			return result;
		}

		// Determinant (only for square matrices)
		constexpr T determinant() const noexcept {
			static_assert(M == N, "Determinant is only defined for square matrices");

			if VTX_CONSTEXPR_IF (M == 3) {
				return elements[0][0] *
				    (elements[1][1] * elements[2][2] - elements[1][2] * elements[2][1]) -
				    elements[0][1] *
				    (elements[1][0] * elements[2][2] - elements[1][2] * elements[2][0]) +
				    elements[0][2] *
				    (elements[1][0] * elements[2][1] - elements[1][1] * elements[2][0]);
			} else {
				// General case for NxN matrices (using Laplace expansion)
				// Note: This is not the most efficient method for large matrices
				// TODO: Move to high-level methods module?
				T det = T(0);
				for (size_t i = 0; i < N; ++i) {
					matrix<T, M - 1, N - 1> minor;
					for (size_t j = 1; j < M; ++j) {
						size_t col = 0;
						for (size_t k = 0; k < N; ++k) {
							if (k == i) continue;
							minor[j - 1][col] = elements[j][k];
							++col;
						}
					}
					det += (i % 2 == 0 ? 1 : -1) * elements[0][i] * minor.determinant();
				}
				return det;
			}
		}

		// Inverse matrix (only for square matrices)
		constexpr matrix inverse() const noexcept {
			static_assert(M == N, "Inverse is only defined for square matrices");

			if VTX_CONSTEXPR_IF (M == 3) {
				T det = determinant();
				if (det == T(0)) return identity();

				return matrix<T, 3, 3>(
				    (elements[1][1] * elements[2][2] - elements[1][2] * elements[2][1]) / det,
				    (elements[0][2] * elements[2][1] - elements[0][1] * elements[2][2]) / det,
				    (elements[0][1] * elements[1][2] - elements[0][2] * elements[1][1]) / det,

				    (elements[1][2] * elements[2][0] - elements[1][0] * elements[2][2]) / det,
				    (elements[0][0] * elements[2][2] - elements[0][2] * elements[2][0]) / det,
				    (elements[0][2] * elements[1][0] - elements[0][0] * elements[1][2]) / det,

				    (elements[1][0] * elements[2][1] - elements[1][1] * elements[2][0]) / det,
				    (elements[0][1] * elements[2][0] - elements[0][0] * elements[2][1]) / det,
				    (elements[0][0] * elements[1][1] - elements[0][1] * elements[1][0]) / det);
			} else {
				// General case for NxN matrices (using adjugate matrix)
				// Note: This is not the most efficient method for large matrices
				// TODO: Move to high-level methods module?
				T det = determinant();
				if (det == T(0)) return identity();

				matrix result;
				matrix<T, M - 1, N - 1> minor;

				for (size_t i = 0; i < M; ++i) {
					for (size_t j = 0; j < N; ++j) {
						// Create minor matrix
						size_t minor_row = 0;
						for (size_t k = 0; k < M; ++k) {
							if (k == i) continue;
							size_t minor_col = 0;
							for (size_t l = 0; l < N; ++l) {
								if (l == j) continue;
								minor[minor_row][minor_col] = elements[k][l];
								++minor_col;
							}
							++minor_row;
						}

						// Calculate cofactor
						T cofactor = minor.determinant();
						if ((i + j) % 2 != 0) {
							cofactor = -cofactor;
						}

						// Transpose (adjugate)
						result[j][i] = cofactor / det;
					}
				}

				return result;
			}
		}

		// Trace (sum of diagonal elements, only for square matrices)
		constexpr T trace() const noexcept {
			static_assert(M == N, "Trace is only defined for square matrices");
			T sum = T(0);

			for (size_t i = 0; i < M; ++i) {
				sum += elements[i][i];
			}

			return sum;
		}

		// Frobenius norm (square root of sum of squares of all elements)
		// TODO: Move to utility header?
		constexpr T frobeniusNorm() const noexcept {
			T sum = T(0);

			for (const auto row : elements) {
				for (const auto element : row) {
					sum += element * element;
				}
			}

			return vtx::sqrt(sum);
		}

		// Matrix-vector multiplication (for MxN matrix and Nx1 vector)
		constexpr vector<T, M> operator*(const vector<T, N>& v) const noexcept {
			vector<T, M> result;

			for (size_t i = 0; i < M; ++i) {
				T sum = T(0);
				for (size_t j = 0; j < N; ++j) {
					sum += elements[i][j] * v[j];
				}
				result[i] = sum;
			}

			return result;
		}

		constexpr size_t rows() const noexcept { return M; }

		constexpr size_t cols() const noexcept { return N; }

	private:
		T elements[M][N];
		static_assert(M > 0 && N > 0, "Matrix dimensions M and N must be greater than zero");

		template <typename, size_t, size_t>
		friend class matrix;

		// Helper metafunction to check that all arguments are convertible to T
		template <typename... Args>
		struct all_convertible : std::true_type {};

		template <typename First, typename... Rest>
		struct all_convertible<First, Rest...>
		    : std::integral_constant<bool,
		          std::is_convertible<First, T>::value && all_convertible<Rest...>::value> {};

		template <size_t... Is>
		constexpr std::array<T, M * N> to_array_impl(std::index_sequence<Is...>) const noexcept {
			return {(data()[Is])...};
		}

	};  // class matrix

}  // namespace vtx

#endif  // VECTRIX_BASE_MATRIX_H
