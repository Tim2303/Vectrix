//
// Created by Timmimin on 06.07.2025.
//

#ifndef VECTRIX_QUATERNION_H
#define VECTRIX_QUATERNION_H

#include "vectrix/math/common.h"

#include "base_matrix.h"

// vtx namespace
namespace vtx {

    // Quaternion class specialization
    template<typename T>
    class quaternion {
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
        union {
            // Array view
            T elements[4];

            // Mathematical names
            struct {
                union {
                    vector<T, 3> Vec;
                    T X, Y, Z;
                };
                T W;
            };
        };

        // Class default constructor
        constexpr quaternion( ) = default;

        // One parameter constructor
        constexpr explicit quaternion( const T num ) noexcept {
            elements[3] = elements[2] = elements[1] = elements[0] = num;
        }

        // Variadic constructor (C++11-compatible)
        template<typename... Args>
        constexpr explicit quaternion(Args... args) noexcept {
            static_assert(sizeof...(Args) <= 4,
                    "Too many constructor arguments!");
            static_assert(all_convertible<Args...>::value,
                    "All arguments must be convertible to T");

            T* dst = elements;
            using expander = int[];
            (void)expander{0, ((void)(*dst++ = static_cast<T>(args)), 0)...};

#ifdef VTX_DEFAULT_FILL0
            for (size_t i = sizeof...(Args); i < 4; ++i)
                elements[i] = T(0);
#endif // VTX_DEFAULT_FILL0
        }

        // Initializer list constructor
        constexpr quaternion( std::initializer_list<T> list ) noexcept {
            size_t i = 0;
            for (T val : list) {
                if (i < 4)
                    elements[i++] = val;
            }
#ifdef VTX_DEFAULT_FILL0
            while (i < 4)
                elements[i++] = T(0);
#endif // VTX_DEFAULT_FILL0
        }

        // Vectors equality operator
        constexpr bool operator==( const quaternion& q ) const noexcept {
            return X == q.X && Y == q.Y && Z == q.Z && W == q.W;
        }

        // Vectors inequality operator
        constexpr bool operator!=( const quaternion& q ) const noexcept {
            return X != q.X || Y != q.Y || Z != q.Z || W != q.W;
        }

        // Pointer cast stl operators
        constexpr T* data() noexcept {
            return elements;
        }
        constexpr const T* data() const noexcept {
            return elements;
        }

        constexpr T* begin() noexcept {
            return elements;
        }
        constexpr const T* begin() const noexcept {
            return elements;
        }

        constexpr T* end() noexcept {
            return elements + 4;
        }
        constexpr const T* end() const noexcept {
            return elements + 4;
        }

        // Component getter operator
        constexpr T operator[]( const size_t ind ) const {
#ifdef _DEBUG
            assert(ind < 4);
#endif // _DEBUG
            return elements[ind];
        }

        // Component reference getter operator
        constexpr T& operator[]( const size_t ind ) {
#ifdef _DEBUG
            assert(ind < 4);
#endif // _DEBUG
            return elements[ind];
        }

        // Negation operator
        constexpr quaternion operator-( ) const noexcept {
            return quaternion{-X, -Y, -Z, -W};
        }

        // Addition operator
        constexpr quaternion operator+( const quaternion& q ) const noexcept {
            return quaternion{
                    X + q.X,
                    Y + q.Y,
                    Z + q.Z,
                    W + q.W
            };
        }

        // Addition to current operator
        constexpr quaternion& operator+=( const quaternion& q ) noexcept {
            X += q.X;
            Y += q.Y;
            Z += q.Z;
            W += q.W;
            return *this;
        }

        // Subtraction operator
        constexpr quaternion operator-( const quaternion& q ) const noexcept {
            return quaternion{
                    X - q.X,
                    Y - q.Y,
                    Z - q.Z,
                    W - q.W
            };
        }

        // Subtraction from current operator
        constexpr quaternion& operator-=( const quaternion& q ) noexcept {
            X -= q.X;
            Y -= q.Y;
            Z -= q.Z;
            W -= q.W;
            return *this;
        }

        // Multiplication operator
        constexpr quaternion operator*( const quaternion& q ) const noexcept {
            return {
                    W * q.X + X * q.W + Y * q.Z - Z * q.Y,
                    W * q.Y - X * q.Z + Y * q.W + Z * q.X,
                    W * q.Z + X * q.Y - Y * q.X + Z * q.W,
                    W * q.W - X * q.X - Y * q.Y - Z * q.Z
            };
        }

        // Multiplication with current operator
        constexpr quaternion& operator*=( const quaternion& q ) noexcept {
            const quaternion t = *this;

            X = t.W * q.X + t.X * q.W + t.Y * q.Z - t.Z * q.Y;
            Y = t.W * q.Y - t.X * q.Z + t.Y * q.W + t.Z * q.X;
            Z = t.W * q.Z + t.X * q.Y - t.Y * q.X + t.Z * q.W;
            W = t.W * q.W - t.X * q.X - t.Y * q.Y - t.Z * q.Z;
            return *this;
        }

        // Multiplication operator
        constexpr quaternion operator*( const T n ) const noexcept {
            return quaternion{
                    X * n,
                    Y * n,
                    Z * n,
                    W * n
            };
        }

        // Multiplication with current operator
        constexpr quaternion& operator*=( const T n ) noexcept {
            X *= n;
            Y *= n;
            Z *= n;
            W *= n;
            return *this;
        }

        // Division operator
        constexpr quaternion operator/( const quaternion& q ) const noexcept {
            return (*this) * (quaternion(-q.Vec, q.W) / q.squaredLength());
        }

        // Division from current operator
        constexpr quaternion& operator/=( const quaternion& q ) noexcept {
            *this = (*this) / q;
            return *this;
        }

        // Division operator
        constexpr quaternion operator/( const T n ) const noexcept {
            return quaternion{
                    X / n,
                    Y / n,
                    Z / n,
                    W / n
            };
        }

        // Division from current operator
        constexpr quaternion& operator/=( const T n ) noexcept {
            X /= n;
            Y /= n;
            Z /= n;
            W /= n;
            return *this;
        }

        // Quat length (sq)
        constexpr T squaredLength( ) const noexcept {
            return X * X + Y * Y + Z * Z + W * W;
        }

        // Quat length
        constexpr T length( ) const noexcept {
            return sqrt(squaredLength());
        }

        // Normalized Quat
        constexpr quaternion normalized( ) const noexcept {
            T len = length();
#ifdef _DEBUG
            assert(len != T(0));
#endif // _DEBUG
            return *this / len;
        }

        // Normalize current quat
        constexpr quaternion& normalize( ) noexcept {
            T len = length();
#ifdef _DEBUG
            assert(len != T(0));
#endif // _DEBUG
            return *this /= len;
        }

        // Maximal component
        constexpr T maxC( ) const noexcept {
            return vtx::math::max(X, Y, Z, W);
        }

        // Minimal component
        constexpr T minC( ) const noexcept {
            return vtx::math::min(X, Y, Z, W);
        }

        // Two quaternions linear interpolation
        constexpr quaternion lerp( const quaternion& q, const T t ) const noexcept {
            return quaternion{
                    X + t * (q.X - X),
                    Y + t * (q.Y - Y),
                    Z + t * (q.Z - Z),
                    W + t * (q.W - W)
            };
        }

        // Two quaternions square interpolation
        constexpr quaternion slerp( const quaternion& q, const T t ) const noexcept {
            T cos_a = W * q.W + X * q.X + Y * q.Y + Z * q.Z;
            quaternion a = *this, b = q;

            if (cos_a < 0)
                cos_a = -cos_a, b = -b;

            const T
                alpha = acos(cos_a),
                sin_a_rev = 1 / sin(alpha),
                sin_ta = sin(t * alpha),
                sin_1_ta = sin((1 - t) * alpha);

            return quat(
                    (a.X * sin_1_ta + b.X * sin_ta) * sin_a_rev,
                    (a.Y * sin_1_ta + b.Y * sin_ta) * sin_a_rev,
                    (a.Z * sin_1_ta + b.Z * sin_ta) * sin_a_rev,
                    (a.W * sin_1_ta + b.W * sin_ta) * sin_a_rev);
        }

        // Get rotation (around 3D vector by angle in degrees) quaternion
        constexpr static quaternion rotate( const vector<T, 3>& v, const T angleInDegree ) noexcept {
            return quaternion{
                    v * sin(angleInDegree / 2.0),
                    cos(angleInDegree / 2.0)
            };
        }

        // Get rotation (around 3D vector by angle in degrees) matrix
        constexpr matrix<T, 4, 4> rotateMatr( ) const noexcept {
            const T
                X2 = 2 * X * X,
                Y2 = 2 * Y * Y,
                Z2 = 2 * Z * Z,
                XZ = 2 * X * Z,
                XY = 2 * X * Y,
                YZ = 2 * Y * Z,
                WX = 2 * W * X,
                WY = 2 * W * Y,
                WZ = 2 * W * Z;

            return matrix<T, 4, 4>(
                    1 - Y2 - Z2, XY + WZ,     XZ - WY,     0,  // 1 string
                    XY - WZ,     1 - X2 - Z2, YZ + WX,     0,  // 2 string
                    XZ + WY,     YZ - WX,     1 - X2 - Y2, 0,  // 3 string
                    0,           0,           0,           1); // 4 string
        }

        // Get rotation (around 3D vector by angle in degrees) tensor
        constexpr matrix<T, 3, 3> rotateTensor( ) const noexcept {
            const T
                X2 = 2 * X * X,
                Y2 = 2 * Y * Y,
                Z2 = 2 * Z * Z,
                XY = 2 * X * Y,
                WZ = 2 * W * Z,
                WY = 2 * W * Y,
                XZ = 2 * X * Z,
                YZ = 2 * Y * Z,
                WX = 2 * W * X;

            return matrix<T, 3, 3>(
                    1 - Y2 - Z2, XY + WZ,     XZ - WY,      // 1 string
                    XY - WZ,     1 - X2 - Z2, YZ + WX,      // 2 string
                    XZ + WY,     YZ - WX,     1 - X2 - Y2); // 3 string
        }

        // Maximal components quat
        constexpr quaternion maxQ( const quaternion& q ) const noexcept {
            return quaternion{
                    vtx::math::max(X, q.X),
                    vtx::math::max(Y, q.Y),
                    vtx::math::max(Z, q.Z),
                    vtx::math::max(W, q.W)
            };
        }

        // Minimal components quat
        constexpr quaternion minQ( const quaternion& q ) const noexcept {
            return quaternion{
                    vtx::math::min(X, q.X),
                    vtx::math::min(Y, q.Y),
                    vtx::math::min(Z, q.Z),
                    vtx::math::min(W, q.W)
            };
        }

        // Ceil quat components
        constexpr quaternion ceil( ) const noexcept {
            return quaternion{
                    vtx::math::ceil(X),
                    vtx::math::ceil(Y),
                    vtx::math::ceil(Z),
                    vtx::math::ceil(W)
            };
        }

        // Floor quat components
        constexpr quaternion floor( ) const noexcept {
            return quaternion{
                    vtx::math::floor(X),
                    vtx::math::floor(Y),
                    vtx::math::floor(Z),
                    vtx::math::floor(W)
            };
        }

        // Vector components composition
        constexpr T volume( ) const noexcept {
            return X * Y * Z * W;
        }

        constexpr T sum() const noexcept {
            return X + Y + Z + W;
        }

        constexpr double avg() const noexcept {
            return sum() / (double)4;
        }

        constexpr size_t size() const noexcept {
            return 4;
        }

    }; // class quaternion

} // namespace vtx

#endif //VECTRIX_QUATERNION_H
