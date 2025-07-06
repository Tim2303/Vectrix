//
// Created by Timmimin on 05.07.2025.
//

#ifndef VECTRIX_VECTOR4_H
#define VECTRIX_VECTOR4_H

#include "vectrix/math/common.h"

#include "base_vector.h"

// vtx namespace
namespace vtx
{
    // Vector 4 class specialization
    template<typename T>
    class vector<T, 4> {
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

            // Dimension names
            struct {
                T X, Y, Z, W;
            };
        };

        // Class default constructor
        constexpr vector( ) = default;

        // One parameter constructor
        constexpr explicit vector( const T num ) noexcept {
            elements[3] = elements[2] = elements[1] = elements[0] = num;
        }

        // Variadic constructor (C++11-compatible)
        template<typename... Args>
        constexpr explicit vector(Args... args) noexcept {
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
        constexpr vector( std::initializer_list<T> list ) noexcept {
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
        constexpr bool operator==( const vector &v ) const noexcept {
            return X == v.X && Y == v.Y && Z == v.Z && W == v.W;
        }

        // Vectors inequality operator
        constexpr bool operator!=( const vector &v ) const noexcept {
            return X != v.X || Y != v.Y || Z != v.Z || W != v.W;
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
        constexpr vector operator-( ) const noexcept {
            return vector{-X, -Y, -Z, -W};
        }

        // Addition operator
        constexpr vector operator+( const vector &v ) const noexcept {
            return vector{
                    X + v.X,
                    Y + v.Y,
                    Z + v.Z,
                    W + v.W
            };
        }

        // Addition to current operator
        constexpr vector& operator+=( const vector &v ) noexcept {
            X += v.X;
            Y += v.Y;
            Z += v.Z;
            W += v.W;
            return *this;
        }

        // Subtraction operator
        constexpr vector operator-( const vector &v ) const noexcept {
            return vector{
                    X - v.X,
                    Y - v.Y,
                    Z - v.Z,
                    W - v.W
            };
        }

        // Subtraction from current operator
        constexpr vector& operator-=( const vector &v ) noexcept {
            X -= v.X;
            Y -= v.Y;
            Z -= v.Z;
            W -= v.W;
            return *this;
        }

        // Multiplication operator
        constexpr vector operator*( const vector &v ) const noexcept {
            return {
                    X * v.X,
                    Y * v.Y,
                    Z * v.Z,
                    W * v.W
            };
        }

        // Multiplication with current operator
        constexpr vector& operator*=( const vector &v ) noexcept {
            X *= v.X;
            Y *= v.Y;
            Z *= v.Z;
            W *= v.W;
            return *this;
        }

        // Multiplication operator
        constexpr vector operator*( const T n ) const noexcept {
            return vector{
                    X * n,
                    Y * n,
                    Z * n,
                    W * n
            };
        }

        // Multiplication with current operator
        constexpr vector& operator*=( const T n ) noexcept {
            X *= n;
            Y *= n;
            Z *= n;
            W *= n;
            return *this;
        }

        // Division operator
        constexpr vector operator/( const vector &v ) const noexcept {
            return vector{
                    X / v.X,
                    Y / v.Y,
                    Z / v.Z,
                    W / v.W
            };
        }

        // Division from current operator
        constexpr vector& operator/=( const vector &v ) noexcept {
            X /= v.X;
            Y /= v.Y;
            Z /= v.Z;
            W /= v.W;
            return *this;
        }

        // Division operator
        constexpr vector operator/( const T n ) const noexcept {
            return vector{
                    X / n,
                    Y / n,
                    Z / n,
                    W / n
            };
        }

        // Division from current operator
        constexpr vector& operator/=( const T n ) noexcept {
            X /= n;
            Y /= n;
            Z /= n;
            W /= n;
            return *this;
        }

        // Dot product function
        constexpr T dot( const vector& v ) const noexcept {
            return X * v.X + Y * v.Y + Z * v.Z + W * v.W;
        }

        // Dot product operator
        constexpr T operator&( const vector &v ) const noexcept {
            return dot(v);
        }

        // Vector length (sq)
        constexpr T squaredLength( ) const noexcept {
            return X * X + Y * Y + Z * Z + W * W;
        }

        // Vector length
        constexpr T length( ) const noexcept {
            return sqrt(squaredLength());
        }

        // Normalized vector
        constexpr vector normalized( ) const noexcept {
            T len = length();
#ifdef _DEBUG
            assert(len != T(0));
#endif // _DEBUG
            return *this / len;
        }

        // Normalize current vector
        constexpr vector& normalize( ) noexcept {
            T len = length();
#ifdef _DEBUG
            assert(len != T(0));
#endif // _DEBUG
            return *this /= len;
        }

        // Maximal component
        constexpr T maxC( ) const noexcept {
            return vtx::math::max({X, Y, Z, W});
        }

        // Minimal component
        constexpr T minC( ) const noexcept {
            return vtx::math::min({X, Y, Z, W});
        }

        // Two vectors linear interpolation
        constexpr vector lerp( const vector &v, const T t ) const noexcept {
            return vector{
                    X + t * (v.X - X),
                    Y + t * (v.Y - Y),
                    Z + t * (v.Z - Z),
                    W + t * (v.W - W)
            };
        }

        // Create 4 byte number - BGRa color
        constexpr DWORD createBGRA( ) const noexcept
        {
            return ((DWORD)(((BYTE)(vtx::math::clamp<T>(Z, 0, 1) * 255) |
                             ((WORD)((BYTE)(vtx::math::clamp<T>(Y, 0, 1) * 255)) << 8)) |
                            (((DWORD)(BYTE)(vtx::math::clamp<T>(X, 0, 1) * 255)) << 16)) |
                    (((DWORD)(BYTE)(vtx::math::clamp<T>(W, 0, 1) * 255)) << 24));
        }

        // Create 4 byte number - RGBa color
        constexpr DWORD createRGBA( ) const noexcept
        {
            return ((DWORD)(((BYTE)(vtx::math::clamp<T>(X, 0, 1) * 255) |
                             ((WORD)((BYTE)(vtx::math::clamp<T>(Y, 0, 1) * 255)) << 8)) |
                            (((DWORD)(BYTE)(vtx::math::clamp<T>(Z, 0, 1) * 255)) << 16)) |
                    (((DWORD)(BYTE)(vtx::math::clamp<T>(W, 0, 1) * 255)) << 24));
        }

        // Maximal components vector
        constexpr vector maxV( const vector &v ) const noexcept {
            return vector{
                    vtx::math::max(X, v.X),
                    vtx::math::max(Y, v.Y),
                    vtx::math::max(Z, v.Z),
                    vtx::math::max(W, v.W)
            };
        }

        // Minimal components vector
        constexpr vector minV( const vector &v ) const noexcept {
            return vector{
                    vtx::math::min(X, v.X),
                    vtx::math::min(Y, v.Y),
                    vtx::math::min(Z, v.Z),
                    vtx::math::min(W, v.W)
            };
        }

        // Ceil vector components
        constexpr vector ceil( ) const noexcept {
            return vector{
                    vtx::math::ceil(X),
                    vtx::math::ceil(Y),
                    vtx::math::ceil(Z),
                    vtx::math::ceil(W)
            };
        }

        // Floor vector components
        constexpr vector floor( ) const noexcept {
            return vector{
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

    }; // class vector

    // Set other names for vector 4
    template<typename T>
    using vec4 = vector<T, 4>;

} // namespace vtx

#endif //VECTRIX_VECTOR4_H
