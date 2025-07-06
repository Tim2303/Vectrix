//
// Created by Timmimin on 30.06.2025.
//

#ifndef VECTRIX_MATRIX4X4_H
#define VECTRIX_MATRIX4X4_H

#include "base_matrix.h"
#include "vector3.h"

// vtx namespace
namespace vtx
{
    // Matrix 4x4 class specialization
    template<typename T>
    class matrix<T, 4, 4> {
    private:
        // Helper metafunction to check that all arguments are convertible to T
        template<typename... Args>
        struct all_convertible : std::true_type {};

        template<typename First, typename... Rest>
        struct all_convertible<First, Rest...> :
                std::integral_constant<bool,
                        std::is_convertible<First, T>::value &&
                        all_convertible<Rest...>::value> {};

        constexpr T det3x3(
                const T E00, const T E01, const T E02,
                const T E10, const T E11, const T E12,
                const T E20, const T E21, const T E22) const noexcept {
            return E00 * (E11 * E22 - E12 * E21) - E01 * (E10 * E22 - E12 * E20) + E02 * (E10 * E21 - E11 * E20);
        }

    public:
        T elements[4][4];

        // Class default constructor
        constexpr matrix() = default;

        // One parameter constructor (fill matrix with value)
        constexpr explicit matrix( const T num ) noexcept {
            for (auto & element : elements) {
                for (size_t j = 0; j < 4; ++j) {
                    element[j] = num;
                }
            }
        }

        // Variadic constructor (row-major order)
        template<typename... Args>
        constexpr explicit matrix( Args... args ) noexcept {
            static_assert(sizeof...(Args) <= 4 * 4,
                    "Too many constructor arguments!");
            static_assert(all_convertible<Args...>::value,
                    "All arguments must be convertible to T");

            T* dst = &elements[0][0];
            using expander = int[];
            (void)expander{0, ((void)(*dst++ = static_cast<T>(args)), 0)...};

            // Fill remaining elements with zero
#ifdef VTX_DEFAULT_FILL0
            dst = &elements[0][0];
            for (size_t i = sizeof...(Args); i < 4 * 4; ++i) {
                dst[i] = T(0);
            }
#endif // VTX_DEFAULT_FILL0
        }

        // Initializer list constructor (row-major order)
        constexpr matrix( std::initializer_list<T> list ) noexcept {
            size_t k = 0;
            for (T val : list) {
                if (k < 4 * 4) {
                    elements[k / 4][k % 4] = val;
                    k++;
                }
            }

            // Fill remaining elements with zero
#ifdef VTX_DEFAULT_FILL0
            for (; k < 4 * 4; ++k) {
                elements[k / 4][k % 4] = T(0);
            }
#endif // VTX_DEFAULT_FILL0
        }

        // Row initializer list constructor
        constexpr matrix( std::initializer_list<std::initializer_list<T>> list ) noexcept {
            size_t i = 0;

            for (const auto &row : list) {
                if (i < 4) {
                    size_t j = 0;

                    for (T val : row) {
                        if (j < 4) {
                            elements[i][j] = val;
                            j++;
                        }
                    }
                    // Fill remaining elements in row with zero
                    for (; j < 4; ++j) {
                        elements[i][j] = T(0);
                    }
                    i++;
                }
            }

            // Fill remaining rows with zero
#ifdef VTX_DEFAULT_FILL0
            for (; i < 4; ++i) {
                for (size_t j = 0; j < 4; ++j) {
                    elements[i][j] = T(0);
                }
            }
#endif // VTX_DEFAULT_FILL0
        }

        // Matrix equality operator
        constexpr bool operator==( const matrix& m ) const noexcept {
            for (size_t i = 0; i < 4; ++i) {
                for (size_t j = 0; j < 4; ++j) {
                    if (m.elements[i][j] != elements[i][j]) {
                        return false;
                    }
                }
            }

            return true;
        }

        // Matrix inequality operator
        constexpr bool operator!=( const matrix& m ) const noexcept {
            for (size_t i = 0; i < 4; ++i) {
                for (size_t j = 0; j < 4; ++j) {
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
            assert(row < 4);
#endif
            return elements[row];
        }

        // Const row access operator
        constexpr const T* operator[]( size_t row ) const noexcept {
#ifdef _DEBUG
            assert(row < 4);
#endif
            return elements[row];
        }

        // Element access (row, column)
        constexpr T& operator()( size_t row, size_t col ) noexcept {
#ifdef _DEBUG
            assert(row < 4 && col < 4);
#endif
            return elements[row][col];
        }

        // Const element access (row, column)
        constexpr T operator()( size_t row, size_t col ) const noexcept {
#ifdef _DEBUG
            assert(row < 4 && col < 4);
#endif
            return elements[row][col];
        }

        // Pointer to data
        constexpr T* data() noexcept { return elements[0]; }
        constexpr const T* data() const noexcept { return elements[0]; }

        // Negation operator
        constexpr matrix operator-() const noexcept {
            matrix result;
            for (size_t i = 0; i < 4; ++i) {
                for (size_t j = 0; j < 4; ++j) {
                    result.elements[i][j] = -elements[i][j];
                }
            }

            return result;
        }

        // Addition operator
        constexpr matrix operator+( const matrix& m ) const noexcept {
            matrix result;
            for (size_t i = 0; i < 4; ++i) {
                for (size_t j = 0; j < 4; ++j) {
                    result.elements[i][j] = elements[i][j] + m.elements[i][j];
                }
            }

            return result;
        }

        // Addition to current operator
        constexpr matrix& operator+=( const matrix& m ) noexcept {
            for (size_t i = 0; i < 4; ++i) {
                for (size_t j = 0; j < 4; ++j) {
                    elements[i][j] += m.elements[i][j];
                }
            }

            return *this;
        }

        // Subtraction operator
        constexpr matrix operator-( const matrix& m ) const noexcept {
            matrix result;
            for (size_t i = 0; i < 4; ++i) {
                for (size_t j = 0; j < 4; ++j) {
                    result.elements[i][j] = elements[i][j] - m.elements[i][j];
                }
            }
            return result;
        }

        // Subtraction from current operator
        constexpr matrix& operator-=( const matrix& m ) noexcept {
            for (size_t i = 0; i < 4; ++i) {
                for (size_t j = 0; j < 4; ++j) {
                    elements[i][j] -= m.elements[i][j];
                }
            }

            return *this;
        }

        // Scalar multiplication operator
        constexpr matrix operator*( const T scalar ) const noexcept {
            matrix result;
            for (size_t i = 0; i < 4; ++i) {
                for (size_t j = 0; j < 4; ++j) {
                    result.elements[i][j] = elements[i][j] * scalar;
                }
            }

            return result;
        }

        // Scalar multiplication with current operator
        constexpr matrix& operator*=( const T scalar ) noexcept {
            for (auto & element : elements) {
                for (size_t j = 0; j < 4; ++j) {
                    element[j] *= scalar;
                }
            }

            return *this;
        }

        // Scalar division operator
        constexpr matrix operator/( const T scalar ) const noexcept {
            matrix result;
            for (size_t i = 0; i < 4; ++i) {
                for (size_t j = 0; j < 4; ++j) {
                    result.elements[i][j] = elements[i][j] / scalar;
                }
            }

            return result;
        }

        // Scalar division with current operator
        constexpr matrix& operator/=( const T scalar ) noexcept {
            for (auto & element : elements) {
                for (size_t j = 0; j < 4; ++j) {
                    element[j] /= scalar;
                }
            }

            return *this;
        }

        // Matrix multiplication (for compatible matrices)
        template<size_t P>
        constexpr matrix<T, 4, P> operator*( const matrix<T, 4, P>& m ) const noexcept {
            matrix<T, 4, P> result;

            for (size_t i = 0; i < 4; ++i) {
                for (size_t j = 0; j < P; ++j) {
                    T sum = T(0);
                    for (size_t k = 0; k < 4; ++k) {
                        sum += elements[i][k] * m.elements[k][j];
                    }
                    result.elements[i][j] = sum;
                }
            }

            return result;
        }

        // Matrix multiplication with current (only for square matrices)
        constexpr matrix& operator*=( const matrix& m ) noexcept {
            *this = *this * m;
            return *this;
        }

        // Transpose matrix
        constexpr matrix transpose() const noexcept {
            return matrix{
                    elements[0][0], elements[1][0], elements[2][0], elements[3][0],
                    elements[0][1], elements[1][1], elements[2][1], elements[3][1],
                    elements[0][2], elements[1][2], elements[2][2], elements[3][2],
                    elements[0][3], elements[1][3], elements[2][3], elements[3][3]
            };
        }

        // Identity matrix (only for square matrices)
        static constexpr matrix identity() noexcept {
            return matrix{
                    1, 0, 0, 0,
                    0, 1, 0, 0,
                    0, 0, 1, 0,
                    0, 0, 0, 1
            };
        }

        // Determinant (only for square matrices)
        constexpr T determinant() const noexcept {
            return
                +elements[0][0] * det3x3(
                    elements[1][1], elements[1][2], elements[1][3],
                    elements[2][1], elements[2][2], elements[2][3],
                    elements[3][1], elements[3][2], elements[3][3]) +
                -elements[0][1] * det3x3(
                    elements[1][0], elements[1][2], elements[1][3],
                    elements[2][0], elements[2][2], elements[2][3],
                    elements[3][0], elements[3][2], elements[3][3]) +
                +elements[0][2] * det3x3(
                    elements[1][0], elements[1][1], elements[1][3],
                    elements[2][0], elements[2][1], elements[2][3],
                    elements[3][0], elements[3][1], elements[3][3]) +
                -elements[0][3] * det3x3(
                    elements[1][0], elements[1][1], elements[1][2],
                    elements[2][0], elements[2][1], elements[2][2],
                    elements[3][0], elements[3][1], elements[3][2]);
        }

        // Inverse matrix (only for square matrices)
        constexpr matrix inverse() const noexcept {
            T det = determinant();
            if (det == T(0)) return identity();

            return matrix{
                // 01, 02, 03, 04
                    det3x3(elements[1][1], elements[1][2], elements[1][3],
                            elements[2][1], elements[2][2], elements[2][3],
                            elements[3][1], elements[3][2], elements[3][3]) / det,
                    -det3x3(elements[1][0], elements[1][2], elements[1][3],
                            elements[2][0], elements[2][2], elements[2][3],
                            elements[3][0], elements[3][2], elements[3][3]) / det,
                    det3x3(elements[1][0], elements[1][1], elements[1][3],
                            elements[2][0], elements[2][1], elements[2][3],
                            elements[3][0], elements[3][1], elements[3][3]) / det,
                    -det3x3(elements[1][0], elements[1][1], elements[1][2],
                            elements[2][0], elements[2][1], elements[2][2],
                            elements[3][0], elements[3][1], elements[3][2]) / det,
                // 10, 11, 12, 13
                    -det3x3(elements[0][1], elements[0][2], elements[0][3],
                            elements[2][1], elements[2][2], elements[2][3],
                            elements[3][1], elements[3][2], elements[3][3]) / det,
                    det3x3(elements[0][0], elements[0][2], elements[0][3],
                            elements[2][0], elements[2][2], elements[2][3],
                            elements[3][0], elements[3][2], elements[3][3]) / det,
                    -det3x3(elements[0][0], elements[0][1], elements[0][3],
                            elements[2][0], elements[2][1], elements[2][3],
                            elements[3][0], elements[3][1], elements[3][3]) / det,
                    det3x3(elements[0][0], elements[0][1], elements[0][2],
                            elements[2][0], elements[2][1], elements[2][2],
                            elements[3][0], elements[3][1], elements[3][2]) / det,
                // 20, 21, 22, 23
                    det3x3(elements[0][1], elements[0][2], elements[0][3],
                            elements[1][1], elements[1][2], elements[1][3],
                            elements[3][1], elements[3][2], elements[3][3]) / det,
                    -det3x3(elements[0][0], elements[0][2], elements[0][3],
                            elements[1][0], elements[1][2], elements[1][3],
                            elements[3][0], elements[3][2], elements[3][3]) / det,
                    det3x3(elements[0][0], elements[0][1], elements[0][3],
                            elements[1][0], elements[1][1], elements[1][3],
                            elements[3][0], elements[3][1], elements[3][3]) / det,
                    -det3x3(elements[0][0], elements[0][1], elements[0][2],
                            elements[1][0], elements[1][1], elements[1][2],
                            elements[3][0], elements[3][1], elements[3][2]) / det,
                // 30, 31, 32, 33
                    -det3x3(elements[0][1], elements[0][2], elements[0][3],
                            elements[1][1], elements[1][2], elements[1][3],
                            elements[2][1], elements[2][2], elements[2][3]) / det,
                    det3x3(elements[0][0], elements[0][2], elements[0][3],
                            elements[1][0], elements[1][2], elements[1][3],
                            elements[2][0], elements[2][2], elements[2][3]) / det,
                    -det3x3(elements[0][0], elements[0][1], elements[0][3],
                            elements[1][0], elements[1][1], elements[1][3],
                            elements[2][0], elements[2][1], elements[2][3]) / det,
                    det3x3(elements[0][0], elements[0][1], elements[0][2],
                            elements[1][0], elements[1][1], elements[1][2],
                            elements[2][0], elements[2][1], elements[2][2]) / det
            };
        }

        // Trace (sum of diagonal elements, only for square matrices)
        constexpr T trace() const noexcept {
            return elements[0][0] + elements[1][1] + elements[2][2] + elements[3][3];
        }

        // Frobenius norm (square root of sum of squares of all elements)
        constexpr T frobeniusNorm() const noexcept {
            T sum = T(0);

            for (auto & element : elements) {
                for (size_t j = 0; j < 4; ++j) {
                    sum += element[j] * element[j];
                }
            }

            return sqrt(sum);
        }

        // Matrix-vector multiplication (for MxN matrix and Nx1 vector)
        constexpr vector<T, 4> operator*( const vector<T, 4>& v ) const noexcept {
            vector<T, 4> result;

            for (size_t i = 0; i < 4; ++i) {
                T sum = T(0);
                for (size_t j = 0; j < 4; ++j) {
                    sum += elements[i][j] * v[j];
                }
                result[i] = sum;
            }

            return result;
        }

        constexpr size_t rows() const noexcept {
            return 4;
        }

        constexpr size_t cols() const noexcept {
            return 4;
        }

        //*******************
        // Geometry functions
        //*******************

        // Rotate matrix around X-axis
        constexpr static matrix rotateX( const T angleInDegree ) noexcept {
            const T co = vtx::math::cos(vtx::math::D2R * angleInDegree), si = vtx::math::sin(vtx::math::D2R * angleInDegree);
            return matrix{
                1, 0, 0, 0,
                0, co, si, 0,
                0, -si, co, 0,
                0, 0, 0, 1
            };
        }

        // Rotate matrix around Y-axis
        constexpr static matrix rotateY( const T angleInDegree ) noexcept {
            const T co = vtx::math::cos(vtx::math::D2R * angleInDegree), si = vtx::math::sin(vtx::math::D2R * angleInDegree);
            return matrix{
                co, 0, -si, 0,
                0, 1, 0, 0,
                si, 0, co, 0,
                0, 0, 0, 1
            };
        }

        // Rotate matrix around Z-axis
        constexpr static matrix rotateZ( const T angleInDegree ) noexcept {
            const T co = vtx::math::cos(vtx::math::D2R * angleInDegree), si = vtx::math::sin(vtx::math::D2R * angleInDegree);
            return matrix{
                co, si, 0, 0,
                -si, co, 0, 0,
                0, 0, 1, 0,
                0, 0, 0, 1
            };
        }

        // Rotate matrix around given axis
        constexpr static matrix rotate( const vector<T, 3>& v, const T angleInDegree ) noexcept {
            const T co = vtx::math::cos(vtx::math::D2R * angleInDegree), si = vtx::math::sin(vtx::math::D2R * angleInDegree);
            return matrix{
                // 1
                co + v[0] * v[0] * (1 - co),
                v[0] * v[1] * (1 - co) + v[2] * si,
                v[0] * v[2] * (1 - co) - v[1] * si,
                0,
                // 2
                v[0] * v[1] * (1 - co) - v[2] * si,
                co + v[1] * v[1] * (1 - co),
                v[2] * v[1] * (1 - co) + v[0] * si,
                0,
                // 3
                v[0] * v[2] * (1 - co) + v[1] * si,
                v[2] * v[1] * (1 - co) - v[0] * si,
                co + v[2] * v[2] * (1 - co),
                0,
                // 4
                0, 0, 0, 1
            };
        }

        // Translate matrix by given vector
        constexpr static matrix translate( const vector<T, 3>& v ) noexcept {
            return matrix{
                1, 0, 0, 0,
                0, 1, 0, 0,
                0, 0, 1, 0,
                v[0], v[1], v[2], 1
            };
        }

        // Scale matrix by given scale-factor
        constexpr static matrix scale( const T sc ) noexcept {
            return matrix{
                sc, 0, 0, 0,
                0, sc, 0, 0,
                0, 0, sc, 0,
                0, 0, 0, 1
            };
        }

        // Scale matrix by given vector scale-factor
        constexpr static matrix scale( const vector<T, 3>& v ) noexcept {
            return matrix{
                v[0], 0, 0, 0,
                0, v[1], 0, 0,
                0, 0, v[2], 0,
                0, 0, 0, 1
            };
        }

        // Transform matrix for point
        constexpr vector<T, 3> transformPoint( const vector<T, 3>& v ) const noexcept {
            return vector<T, 3>{
                v[0] * elements[0][0] + v[1] * elements[1][0] + v[2] * elements[2][0] + elements[3][0],
                v[0] * elements[0][1] + v[1] * elements[1][1] + v[2] * elements[2][1] + elements[3][1],
                v[0] * elements[0][2] + v[1] * elements[1][2] + v[2] * elements[2][2] + elements[3][2]
            };
        }

        // Transform matrix for vector
        constexpr vector<T, 3> transformVector( const vector<T, 3>& v ) const noexcept {
            return vector<T, 3>{
                v[0] * elements[0][0] + v[1] * elements[1][0] + v[2] * elements[2][0],
                v[0] * elements[0][1] + v[1] * elements[1][1] + v[2] * elements[2][1],
                v[0] * elements[0][2] + v[1] * elements[1][2] + v[2] * elements[2][2]
            };
        }

        // Transform matrix for normal
        constexpr vector<T, 3> transformNormal( const vector<T, 3>& v ) const noexcept {
            const matrix M = inverse().transpose();
            return vector<T, 3>{
                    v[0] * M[0][0] + v[1] * M[1][0] + v[2] * M[2][0],
                    v[0] * M[0][1] + v[1] * M[1][1] + v[2] * M[2][1],
                    v[0] * M[0][2] + v[1] * M[1][2] + v[2] * M[2][2]
            };
        }

        // Transform matrix 4x4
        constexpr vector<T, 3> transform4x4( const vector<T, 3>& v ) const {
            const auto w = 1 / (v[0] * elements[0][3] + v[1] * elements[1][3] + v[2] * elements[2][3] + elements[3][3]);
            return vector<T, 3>{
                (v[0] * elements[0][0] + v[1] * elements[1][0] + v[2] * elements[2][0] + elements[3][0]) * w,
                (v[0] * elements[0][1] + v[1] * elements[1][1] + v[2] * elements[2][1] + elements[3][1]) * w,
                (v[0] * elements[0][2] + v[1] * elements[1][2] + v[2] * elements[2][2] + elements[3][2]) * w
            };
        }

        //*******************************
        // Projection-view-ortho matrices
        //*******************************

        // View matrix
        constexpr static matrix view( const vector<T, 3>& loc, const vector<T, 3>& at, const vector<T, 3>& up ) noexcept {
            const vector<T, 3> Dir = (at - loc).normalize(), Right = (Dir.cross(up)).normalize(), Up1 = Right % Dir;
            return matrix{
                    Right[0], Up1[0], -Dir[0], 0,
                    Right[1], Up1[1], -Dir[1], 0,
                    Right[2], Up1[2], -Dir[2], 0,
                    -loc & Right, -loc & Up1, loc & Dir, 1
            };
        }

        // Orthogonal matrix
        constexpr static matrix ortho(
                const T left,   const T right,
                const T bottom, const T top,
                const T near,   const T far ) {
            return matrix{
                2 / (right - left), 0, 0, 0,
                0, 2 / (top - bottom), 0, 0,
                0, 0, -2 / (far - near), 0,
                -(left + right) / (right - left), -(top + bottom) / (top - bottom), -(far + near) / (far - near), 1
            };
        }

        // Frustum matrix
        constexpr static matrix frustum(
                const T left, const T right, const T top,
                const T bottom, const T near, const T far ) {
            return matrix{
                2 * near / (right - left), 0, 0, 0,
                0, 2 * near / (top - bottom), 0, 0,
                (right + left) / (right - left), (top + bottom) / (top - bottom), (far + near) / (near - far), -1,
                0, 0, 2 * near * far / (near - far), 0
            };
        }

    }; // class matrix

    // Set other names for matrix 4x4
    template<typename T>
    using mat4x4 = matrix<T, 4, 4>;

} // namespace vtx

#endif //VECTRIX_MATRIX4X4_H
