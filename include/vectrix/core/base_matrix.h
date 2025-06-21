//
// Created by Timmimin on 21.06.2025.
//

#ifndef VECTRIX_BASE_MATRIX_H
#define VECTRIX_BASE_MATRIX_H

#include "vectrix/math/common.h"
#include "base_vector.h"

// TODO: Vibecoded this file, needs and review

// vtx namespace
namespace vtx
{
    // Base matrix class of any size MxN
    template<typename T, size_t M, size_t N>
    class matrix {
    private:
        static_assert(M > 0 && N > 0,
                "Matrix dimensions M and N must be greater than zero");

        // Helper metafunction to check that all arguments are convertible to T
        template<typename... Args>
        struct all_convertible : std::true_type {};

        template<typename First, typename... Rest>
        struct all_convertible<First, Rest...> :
                std::integral_constant<bool,
                        std::is_convertible<First, T>::value &&
                        all_convertible<Rest...>::value> {};

    public:
        T elements[M][N];

        // Class default constructor
        constexpr matrix() = default;

        // One parameter constructor (fill matrix with value)
        constexpr explicit matrix(const T num) noexcept {
            for (size_t i = 0; i < M; ++i) {
                for (size_t j = 0; j < N; ++j) {
                    elements[i][j] = num;
                }
            }
        }

        // Variadic constructor (row-major order)
        template<typename... Args>
        constexpr explicit matrix(Args... args) noexcept {
            static_assert(sizeof...(Args) <= M * N,
                    "Too many constructor arguments!");
            static_assert(all_convertible<Args...>::value,
                    "All arguments must be convertible to T");

            T* dst = &elements[0][0];
            using expander = int[];
            (void)expander{0, ((void)(*dst++ = static_cast<T>(args)), 0)...};

            // Fill remaining elements with zero
            for (size_t i = sizeof...(Args); i < M * N; ++i) {
                dst[i] = T(0);
            }
        }

        // Initializer list constructor (row-major order)
        constexpr matrix(std::initializer_list<T> list) noexcept {
            size_t k = 0;
            for (T val : list) {
                if (k < M * N) {
                    elements[k / N][k % N] = val;
                    k++;
                }
            }
            // Fill remaining elements with zero
            for (; k < M * N; ++k) {
                elements[k / N][k % N] = T(0);
            }
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
                    // Fill remaining elements in row with zero
                    for (; j < N; ++j) {
                        elements[i][j] = T(0);
                    }
                    i++;
                }
            }
            // Fill remaining rows with zero
            for (; i < M; ++i) {
                for (size_t j = 0; j < N; ++j) {
                    elements[i][j] = T(0);
                }
            }
        }

        // Matrix equality operator
        constexpr bool operator==(const matrix &m) const noexcept {
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
        constexpr bool operator!=(const matrix &m) const noexcept {
            for (size_t i = 0; i < M; ++i) {
                for (size_t j = 0; j < N; ++j) {
                    if (m.elements[i][j] != elements[i][j]) {
                        return true;
                    }
                }
            }
            return false;
        }

        // Row access operator
        constexpr T* operator[](size_t row) noexcept {
#ifdef _DEBUG
            assert(row < M);
#endif
            return elements[row];
        }

        // Const row access operator
        constexpr const T* operator[](size_t row) const noexcept {
#ifdef _DEBUG
            assert(row < M);
#endif
            return elements[row];
        }

        // Element access (row, column)
        constexpr T& operator()(size_t row, size_t col) noexcept {
#ifdef _DEBUG
            assert(row < M && col < N);
#endif
            return elements[row][col];
        }

        // Const element access (row, column)
        constexpr T operator()(size_t row, size_t col) const noexcept {
#ifdef _DEBUG
            assert(row < M && col < N);
#endif
            return elements[row][col];
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

        // Addition operator
        constexpr matrix operator+(const matrix &m) const noexcept {
            matrix result;
            for (size_t i = 0; i < M; ++i) {
                for (size_t j = 0; j < N; ++j) {
                    result.elements[i][j] = elements[i][j] + m.elements[i][j];
                }
            }
            return result;
        }

        // Addition to current operator
        constexpr matrix& operator+=(const matrix &m) noexcept {
            for (size_t i = 0; i < M; ++i) {
                for (size_t j = 0; j < N; ++j) {
                    elements[i][j] += m.elements[i][j];
                }
            }
            return *this;
        }

        // Subtraction operator
        constexpr matrix operator-(const matrix &m) const noexcept {
            matrix result;
            for (size_t i = 0; i < M; ++i) {
                for (size_t j = 0; j < N; ++j) {
                    result.elements[i][j] = elements[i][j] - m.elements[i][j];
                }
            }
            return result;
        }

        // Subtraction from current operator
        constexpr matrix& operator-=(const matrix &m) noexcept {
            for (size_t i = 0; i < M; ++i) {
                for (size_t j = 0; j < N; ++j) {
                    elements[i][j] -= m.elements[i][j];
                }
            }
            return *this;
        }

        // Scalar multiplication operator
        constexpr matrix operator*(const T scalar) const noexcept {
            matrix result;
            for (size_t i = 0; i < M; ++i) {
                for (size_t j = 0; j < N; ++j) {
                    result.elements[i][j] = elements[i][j] * scalar;
                }
            }
            return result;
        }

        // Scalar multiplication with current operator
        constexpr matrix& operator*=(const T scalar) noexcept {
            for (size_t i = 0; i < M; ++i) {
                for (size_t j = 0; j < N; ++j) {
                    elements[i][j] *= scalar;
                }
            }
            return *this;
        }

        // Scalar division operator
        constexpr matrix operator/(const T scalar) const noexcept {
            matrix result;
            for (size_t i = 0; i < M; ++i) {
                for (size_t j = 0; j < N; ++j) {
                    result.elements[i][j] = elements[i][j] / scalar;
                }
            }
            return result;
        }

        // Scalar division with current operator
        constexpr matrix& operator/=(const T scalar) noexcept {
            for (size_t i = 0; i < M; ++i) {
                for (size_t j = 0; j < N; ++j) {
                    elements[i][j] /= scalar;
                }
            }
            return *this;
        }

        // Matrix multiplication (for compatible matrices)
        template<size_t P>
        constexpr matrix<T, M, P> operator*(const matrix<T, N, P> &m) const noexcept {
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
        constexpr matrix& operator*=(const matrix &m) noexcept {
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
            for (size_t i = 0; i < M; ++i) {
                for (size_t j = 0; j < N; ++j) {
                    result.elements[i][j] = (i == j) ? T(1) : T(0);
                }
            }
            return result;
        }

        // Determinant (only for square matrices)
        constexpr T determinant() const noexcept {
            static_assert(M == N, "Determinant is only defined for square matrices");

            if constexpr (M == 1) {
                return elements[0][0];
            }
            else if constexpr (M == 2) {
                return elements[0][0] * elements[1][1] - elements[0][1] * elements[1][0];
            }
            else if constexpr (M == 3) {
                return elements[0][0] * (elements[1][1] * elements[2][2] - elements[1][2] * elements[2][1]) -
                       elements[0][1] * (elements[1][0] * elements[2][2] - elements[1][2] * elements[2][0]) +
                       elements[0][2] * (elements[1][0] * elements[2][1] - elements[1][1] * elements[2][0]);
            }
            else if constexpr (M == 4) {
                // 4x4 determinant using Laplace expansion
                T det = T(0);
                for (size_t i = 0; i < 4; ++i) {
                    matrix<T, 3, 3> minor;
                    for (size_t j = 1; j < 4; ++j) {
                        size_t col = 0;
                        for (size_t k = 0; k < 4; ++k) {
                            if (k == i) continue;
                            minor[j-1][col] = elements[j][k];
                            ++col;
                        }
                    }
                    det += (i % 2 == 0 ? 1 : -1) * elements[0][i] * minor.determinant();
                }
                return det;
            }
            else {
                // General case for NxN matrices (using Laplace expansion)
                // Note: This is not the most efficient method for large matrices
                T det = T(0);
                for (size_t i = 0; i < N; ++i) {
                    matrix<T, M-1, N-1> minor;
                    for (size_t j = 1; j < M; ++j) {
                        size_t col = 0;
                        for (size_t k = 0; k < N; ++k) {
                            if (k == i) continue;
                            minor[j-1][col] = elements[j][k];
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

            if constexpr (M == 1) {
                return matrix(1 / elements[0][0]);
            }
            else if constexpr (M == 2) {
                T det = determinant();
                if (det == T(0)) return identity();

                return matrix(
                        elements[1][1] / det, -elements[0][1] / det,
                        -elements[1][0] / det, elements[0][0] / det
                );
            }
            else if constexpr (M == 3) {
                T det = determinant();
                if (det == T(0)) return identity();

                return matrix(
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
            else {
                // General case for NxN matrices (using adjugate matrix)
                // Note: This is not the most efficient method for large matrices
                T det = determinant();
                if (det == T(0)) return identity();

                matrix result;
                matrix<T, M-1, N-1> minor;

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
        constexpr T frobeniusNorm() const noexcept {
            T sum = T(0);
            for (size_t i = 0; i < M; ++i) {
                for (size_t j = 0; j < N; ++j) {
                    sum += elements[i][j] * elements[i][j];
                }
            }
            return sqrt(sum);
        }

        // Matrix-vector multiplication (for MxN matrix and Nx1 vector)
        constexpr vector<T, M> operator*(const vector<T, N> &v) const noexcept {
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

        // Special matrix constructors (static factory methods)

        // Translation matrix (for 4x4 matrices)
        template<size_t D = M, typename = typename std::enable_if<D == 4 && N == 4>::type>
        static constexpr matrix translation(const vector<T, 3> &trans) noexcept {
            return matrix(
                    1, 0, 0, trans[0],
                    0, 1, 0, trans[1],
                    0, 0, 1, trans[2],
                    0, 0, 0, 1
            );
        }

        // Scaling matrix (for 4x4 matrices)
        template<size_t D = M, typename = typename std::enable_if<D == 4 && N == 4>::type>
        static constexpr matrix scaling(const vector<T, 3> &scale) noexcept {
            return matrix(
                    scale[0], 0, 0, 0,
                    0, scale[1], 0, 0,
                    0, 0, scale[2], 0,
                    0, 0, 0, 1
            );
        }

        // Uniform scaling matrix (for 4x4 matrices)
        template<size_t D = M, typename = typename std::enable_if<D == 4 && N == 4>::type>
        static constexpr matrix scaling(T scale) noexcept {
            return matrix(
                    scale, 0, 0, 0,
                    0, scale, 0, 0,
                    0, 0, scale, 0,
                    0, 0, 0, 1
            );
        }

        // Rotation around X axis (for 4x4 matrices)
        template<size_t D = M, typename = typename std::enable_if<D == 4 && N == 4>::type>
        static constexpr matrix rotationX(T angle) noexcept {
            T c = cos(angle);
            T s = sin(angle);
            return matrix(
                    1, 0, 0, 0,
                    0, c, -s, 0,
                    0, s, c, 0,
                    0, 0, 0, 1
            );
        }

        // Rotation around Y axis (for 4x4 matrices)
        template<size_t D = M, typename = typename std::enable_if<D == 4 && N == 4>::type>
        static constexpr matrix rotationY(T angle) noexcept {
            T c = cos(angle);
            T s = sin(angle);
            return matrix(
                    c, 0, s, 0,
                    0, 1, 0, 0,
                    -s, 0, c, 0,
                    0, 0, 0, 1
            );
        }

        // Rotation around Z axis (for 4x4 matrices)
        template<size_t D = M, typename = typename std::enable_if<D == 4 && N == 4>::type>
        static constexpr matrix rotationZ(T angle) noexcept {
            T c = cos(angle);
            T s = sin(angle);
            return matrix(
                    c, -s, 0, 0,
                    s, c, 0, 0,
                    0, 0, 1, 0,
                    0, 0, 0, 1
            );
        }

        // View matrix (for 4x4 matrices)
        template<size_t D = M, typename = typename std::enable_if<D == 4 && N == 4>::type>
        static constexpr matrix view(const vector<T, 3> &eye, const vector<T, 3> &target, const vector<T, 3> &up) noexcept {
            vector<T, 3> z = (eye - target).normalized();
            vector<T, 3> x = (up % z).normalized();
            vector<T, 3> y = z % x;

            return matrix(
                    x[0], x[1], x[2], -x.dot(eye),
                    y[0], y[1], y[2], -y.dot(eye),
                    z[0], z[1], z[2], -z.dot(eye),
                    0, 0, 0, 1
            );
        }

        // Perspective projection matrix (for 4x4 matrices)
        template<size_t D = M, typename = typename std::enable_if<D == 4 && N == 4>::type>
        static constexpr matrix perspective(T fovY, T aspect, T near, T far) noexcept {
            T f = 1.0 / tan(fovY / 2.0);
            T nf = 1.0 / (near - far);

            return matrix(
                    f / aspect, 0, 0, 0,
                    0, f, 0, 0,
                    0, 0, (far + near) * nf, 2 * far * near * nf,
                    0, 0, -1, 0
            );
        }

        // Orthographic projection matrix (for 4x4 matrices)
        template<size_t D = M, typename = typename std::enable_if<D == 4 && N == 4>::type>
        static constexpr matrix orthographic(T left, T right, T bottom, T top, T near, T far) noexcept {
            T rl = 1.0 / (right - left);
            T tb = 1.0 / (top - bottom);
            T fn = 1.0 / (far - near);

            return matrix(
                    2 * rl, 0, 0, -(right + left) * rl,
                    0, 2 * tb, 0, -(top + bottom) * tb,
                    0, 0, -2 * fn, -(far + near) * fn,
                    0, 0, 0, 1
            );
        }

    }; // class matrix

} // namespace vtx

#endif //VECTRIX_BASE_MATRIX_H
