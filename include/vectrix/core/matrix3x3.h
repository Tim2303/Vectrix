//
// Created by Timmimin on 30.06.2025.
//

#ifndef VECTRIX_MATRIX3X3_H
#define VECTRIX_MATRIX3X3_H

#include "base_matrix.h"

// vtx namespace
namespace vtx
{
    // Matrix 3x3 (tensor included) class specialization
    template<typename T>
    class matrix<T, 3, 3> {
    private:
        // Helper metafunction to check that all arguments are convertible to T
        template<typename... Args>
        struct all_convertible : std::true_type {};

        template<typename First, typename... Rest>
        struct all_convertible<First, Rest...> :
                std::integral_constant<bool,
                        std::is_convertible<First, T>::value &&
                        all_convertible<Rest...>::value> {};

    public:
        T elements[3][3];

        // Class default constructor
        constexpr matrix() = default;

        // One parameter constructor (fill matrix with value)
        constexpr explicit matrix( const T num ) noexcept {
            for (size_t i = 0; i < 3; ++i) {
                for (size_t j = 0; j < 3; ++j) {
                    elements[i][j] = num;
                }
            }
        }

        // Variadic constructor (row-major order)
        template<typename... Args>
        constexpr explicit matrix( Args... args ) noexcept {
            static_assert(sizeof...(Args) <= 3 * 3,
                    "Too many constructor arguments!");
            static_assert(all_convertible<Args...>::value,
                    "All arguments must be convertible to T");

            T* dst = &elements[0][0];
            using expander = int[];
            (void)expander{0, ((void)(*dst++ = static_cast<T>(args)), 0)...};

            // Fill remaining elements with zero
            dst = &elements[0][0];
            for (size_t i = sizeof...(Args); i < 3 * 3; ++i) {
                dst[i] = T(0);
            }
        }

        // Initializer list constructor (row-major order)
        constexpr matrix( std::initializer_list<T> list ) noexcept {
            size_t k = 0;
            for (T val : list) {
                if (k < 3 * 3) {
                    elements[k / 3][k % 3] = val;
                    k++;
                }
            }
            // Fill remaining elements with zero
            for (; k < 3 * 3; ++k) {
                elements[k / 3][k % 3] = T(0);
            }
        }

        // Row initializer list constructor
        constexpr matrix( std::initializer_list<std::initializer_list<T>> list ) noexcept {
            size_t i = 0;

            for (const auto &row : list) {
                if (i < 3) {
                    size_t j = 0;

                    for (T val : row) {
                        if (j < 3) {
                            elements[i][j] = val;
                            j++;
                        }
                    }
                    // Fill remaining elements in row with zero
                    for (; j < 3; ++j) {
                        elements[i][j] = T(0);
                    }
                    i++;
                }
            }

            // Fill remaining rows with zero
            for (; i < 3; ++i) {
                for (size_t j = 0; j < 3; ++j) {
                    elements[i][j] = T(0);
                }
            }
        }

        // Matrix equality operator
        constexpr bool operator==( const matrix &m ) const noexcept {
            for (size_t i = 0; i < 3; ++i) {
                for (size_t j = 0; j < 3; ++j) {
                    if (m.elements[i][j] != elements[i][j]) {
                        return false;
                    }
                }
            }

            return true;
        }

        // Matrix inequality operator
        constexpr bool operator!=(const matrix &m) const noexcept {
            for (size_t i = 0; i < 3; ++i) {
                for (size_t j = 0; j < 3; ++j) {
                    if (m.elements[i][j] != elements[i][j]) {
                        return true;
                    }
                }
            }

            return false;
        }

        // Row access operator
        constexpr T* operator[]( size_t row ) noexcept {
#ifdef _DEBUG
            assert(row < 3);
#endif
            return elements[row];
        }

        // Const row access operator
        constexpr const T* operator[]( size_t row ) const noexcept {
#ifdef _DEBUG
            assert(row < 3);
#endif
            return elements[row];
        }

        // Element access (row, column)
        constexpr T& operator()( size_t row, size_t col ) noexcept {
#ifdef _DEBUG
            assert(row < 3 && col < 3);
#endif
            return elements[row][col];
        }

        // Const element access (row, column)
        constexpr T operator()( size_t row, size_t col ) const noexcept {
#ifdef _DEBUG
            assert(row < 3 && col < 3);
#endif
            return elements[row][col];
        }

        // Pointer to data
        constexpr T* data() noexcept { return &elements[0][0]; }
        constexpr const T* data() const noexcept { return &elements[0][0]; }

        // Negation operator
        constexpr matrix operator-() const noexcept {
            matrix result;
            for (size_t i = 0; i < 3; ++i) {
                for (size_t j = 0; j < 3; ++j) {
                    result.elements[i][j] = -elements[i][j];
                }
            }

            return result;
        }

        // Addition operator
        constexpr matrix operator+( const matrix &m ) const noexcept {
            matrix result;
            for (size_t i = 0; i < 3; ++i) {
                for (size_t j = 0; j < 3; ++j) {
                    result.elements[i][j] = elements[i][j] + m.elements[i][j];
                }
            }

            return result;
        }

        // Addition to current operator
        constexpr matrix& operator+=( const matrix &m ) noexcept {
            for (size_t i = 0; i < 3; ++i) {
                for (size_t j = 0; j < 3; ++j) {
                    elements[i][j] += m.elements[i][j];
                }
            }

            return *this;
        }

        // Subtraction operator
        constexpr matrix operator-( const matrix &m ) const noexcept {
            matrix result;
            for (size_t i = 0; i < 3; ++i) {
                for (size_t j = 0; j < 3; ++j) {
                    result.elements[i][j] = elements[i][j] - m.elements[i][j];
                }
            }
            return result;
        }

        // Subtraction from current operator
        constexpr matrix& operator-=( const matrix &m ) noexcept {
            for (size_t i = 0; i < 3; ++i) {
                for (size_t j = 0; j < 3; ++j) {
                    elements[i][j] -= m.elements[i][j];
                }
            }

            return *this;
        }

        // Scalar multiplication operator
        constexpr matrix operator*( const T scalar ) const noexcept {
            matrix result;
            for (size_t i = 0; i < 3; ++i) {
                for (size_t j = 0; j < 3; ++j) {
                    result.elements[i][j] = elements[i][j] * scalar;
                }
            }

            return result;
        }

        // Scalar multiplication with current operator
        constexpr matrix& operator*=( const T scalar ) noexcept {
            for (size_t i = 0; i < 3; ++i) {
                for (size_t j = 0; j < 3; ++j) {
                    elements[i][j] *= scalar;
                }
            }

            return *this;
        }

        // Scalar division operator
        constexpr matrix operator/( const T scalar ) const noexcept {
            matrix result;
            for (size_t i = 0; i < 3; ++i) {
                for (size_t j = 0; j < 3; ++j) {
                    result.elements[i][j] = elements[i][j] / scalar;
                }
            }

            return result;
        }

        // Scalar division with current operator
        constexpr matrix& operator/=( const T scalar ) noexcept {
            for (size_t i = 0; i < 3; ++i) {
                for (size_t j = 0; j < 3; ++j) {
                    elements[i][j] /= scalar;
                }
            }

            return *this;
        }

        // Matrix multiplication (for compatible matrices)
        template<size_t P>
        constexpr matrix<T, 3, P> operator*( const matrix<T, 3, P> &m ) const noexcept {
            matrix<T, 3, P> result;

            for (size_t i = 0; i < 3; ++i) {
                for (size_t j = 0; j < P; ++j) {
                    T sum = T(0);
                    for (size_t k = 0; k < 3; ++k) {
                        sum += elements[i][k] * m.elements[k][j];
                    }
                    result.elements[i][j] = sum;
                }
            }

            return result;
        }

        // Matrix multiplication with current (only for square matrices)
        constexpr matrix& operator*=( const matrix &m ) noexcept {
            *this = *this * m;
            return *this;
        }

        // Transpose matrix
        constexpr matrix transpose() const noexcept {
            return matrix{
                    elements[0][0], elements[1][0], elements[2][0],
                    elements[0][1], elements[1][1], elements[2][1],
                    elements[0][2], elements[1][2], elements[2][2]
            };
        }

        // Identity matrix (only for square matrices)
        static constexpr matrix identity() noexcept {
            return matrix{
                1, 0, 0,
                0, 1, 0,
                0, 0, 1
            };
        }

        // Star tensor method
        static constexpr matrix star( const vector<T, 3> &v ) noexcept {
            return matrix{
                    0, v[2], v[1],
                    v[2], 0, -v[0],
                    -v[1], v[0], 0
            };
        }

        // Determinant (only for square matrices)
        constexpr T determinant() const noexcept {
            return elements[0][0] * (elements[1][1] * elements[2][2] - elements[1][2] * elements[2][1]) -
                   elements[0][1] * (elements[1][0] * elements[2][2] - elements[1][2] * elements[2][0]) +
                   elements[0][2] * (elements[1][0] * elements[2][1] - elements[1][1] * elements[2][0]);
        }

        // Inverse matrix (only for square matrices)
        constexpr matrix inverse() const noexcept {
            T det = determinant();
            if (det == T(0)) return matrix<T, 3, 3>::identity();

            return matrix<T, 3, 3>(
                    (elements[1][1] * elements[2][2] - elements[1][2] * elements[2][1]) / det,
                    (elements[0][2] * elements[2][1] - elements[0][1] * elements[2][2]) / det,
                    (elements[0][1] * elements[1][2] - elements[0][2] * elements[1][1]) / det,

                    (elements[1][2] * elements[2][0] - elements[1][0] * elements[2][2]) / det,
                    (elements[0][0] * elements[2][2] - elements[0][2] * elements[2][0]) / det,
                    (elements[0][2] * elements[1][0] - elements[0][0] * elements[1][2]) / det,

                    (elements[1][0] * elements[2][1] - elements[1][1] * elements[2][0]) / det,
                    (elements[0][1] * elements[2][0] - elements[0][0] * elements[2][1]) / det,
                    (elements[0][0] * elements[1][1] - elements[0][1] * elements[1][0]) / det
            );
        }

        // Trace (sum of diagonal elements, only for square matrices)
        constexpr T trace() const noexcept {
            return elements[0][0] + elements[1][1] + elements[2][2];
        }

        // Frobenius norm (square root of sum of squares of all elements)
        constexpr T frobeniusNorm() const noexcept {
            T sum = T(0);

            for (size_t i = 0; i < 3; ++i) {
                for (size_t j = 0; j < 3; ++j) {
                    sum += elements[i][j] * elements[i][j];
                }
            }

            return sqrt(sum);
        }

        // Matrix-vector multiplication (for MxN matrix and Nx1 vector)
        constexpr vector<T, 3> operator*( const vector<T, 3> &v ) const noexcept {
            vector<T, 3> result;

            for (size_t i = 0; i < 3; ++i) {
                T sum = T(0);
                for (size_t j = 0; j < 3; ++j) {
                    sum += elements[i][j] * v[j];
                }
                result[i] = sum;
            }

            return result;
        }

        constexpr size_t rows() const noexcept {
            return 3;
        }

        constexpr size_t cols() const noexcept {
            return 3;
        }

    }; // class matrix

    // Set other names for matrix 3x3
    template<typename T>
    using mat3x3 = matrix<T, 3, 3>;
    template<typename T>
    using tensor = matrix<T, 3, 3>;

} // namespace vtx

#endif //VECTRIX_MATRIX3X3_H
