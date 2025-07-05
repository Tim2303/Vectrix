//
// Created by Timmimin on 05.07.2025.
//

#ifndef VECTRIX_VECTOR2_H
#define VECTRIX_VECTOR2_H

#include "vectrix/math/common.h"

#include "base_vector.h"

// vtx namespace
namespace vtx
{
    // Vector 2 class specialization
    template<typename T>
    class vector<T, 2> {
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
            T elements[2];

            // Dimension names
            struct {
                T X, Y;
            };
        };

        // Class default constructor
        constexpr vector( ) = default;

        // One parameter constructor
        constexpr explicit vector( const T num ) noexcept {
            elements[1] = elements[0] = num;
        }

        // Variadic constructor (C++11-compatible)
        template<typename... Args>
        constexpr explicit vector(Args... args) noexcept {
            static_assert(sizeof...(Args) <= 2,
                    "Too many constructor arguments!");
            static_assert(all_convertible<Args...>::value,
                    "All arguments must be convertible to T");

            T* dst = elements;
            using expander = int[];
            (void)expander{0, ((void)(*dst++ = static_cast<T>(args)), 0)...};

#ifdef VTX_DEFAULT_FILL0
            for (size_t i = sizeof...(Args); i < 2; ++i)
                elements[i] = T(0);
#endif // VTX_DEFAULT_FILL0
        }

        // Initializer list constructor
        constexpr vector( std::initializer_list<T> list ) noexcept {
            size_t i = 0;
            for (T val : list) {
                if (i < 2)
                    elements[i++] = val;
            }
#ifdef VTX_DEFAULT_FILL0
            while (i < 2)
                elements[i++] = T(0);
#endif // VTX_DEFAULT_FILL0
        }

        // Vectors equality operator
        constexpr bool operator==( const vector &v ) const noexcept {
            return X == v.X && Y == v.Y;
        }

        // Vectors inequality operator
        constexpr bool operator!=( const vector &v ) const noexcept {
            return X != v.X || Y != v.Y;
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
            return elements + 2;
        }
        constexpr const T* end() const noexcept {
            return elements + 2;
        }

        // Component getter operator
        constexpr T operator[]( const size_t ind ) const {
#ifdef _DEBUG
            assert(ind < 2);
#endif // _DEBUG
            return elements[ind];
        }

        // Component reference getter operator
        constexpr T& operator[]( const size_t ind ) {
#ifdef _DEBUG
            assert(ind < 2);
#endif // _DEBUG
            return elements[ind];
        }

        // Negation operator
        constexpr vector operator-( ) const noexcept {
            return vector{-X, -Y};
        }

        // Addition operator
        constexpr vector operator+( const vector &v ) const noexcept {
            return vector{
                X + v.X,
                Y + v.Y
            };
        }

        // Addition to current operator
        constexpr vector& operator+=( const vector &v ) noexcept {
            X += v.X;
            Y += v.Y;
            return *this;
        }

        // Subtraction operator
        constexpr vector operator-( const vector &v ) const noexcept {
            return vector{
                X - v.X,
                Y - v.Y
            };
        }

        // Subtraction from current operator
        constexpr vector& operator-=( const vector &v ) noexcept {
            X -= v.X;
            Y -= v.Y;
            return *this;
        }

        // Multiplication operator
        constexpr vector operator*( const vector &v ) const noexcept {
            return {
                X * v.X,
                Y * v.Y
            };
        }

        // Multiplication with current operator
        constexpr vector& operator*=( const vector &v ) noexcept {
            X *= v.X;
            Y *= v.Y;
            return *this;
        }

        // Multiplication operator
        constexpr vector operator*( const T n ) const noexcept {
            return vector{
                X * n,
                Y * n
            };
        }

        // Multiplication with current operator
        constexpr vector& operator*=( const T n ) noexcept {
            X *= n;
            Y *= n;
            return *this;
        }

        // Division operator
        constexpr vector operator/( const vector &v ) const noexcept {
            return vector{
                X / v.X,
                Y / v.Y
            };
        }

        // Division from current operator
        constexpr vector& operator/=( const vector &v ) noexcept {
            X /= v.X;
            Y /= v.Y;
            return *this;
        }

        // Division operator
        constexpr vector operator/( const T n ) const noexcept {
            return vector{
                X / n,
                Y / n
            };
        }

        // Division from current operator
        constexpr vector& operator/=( const T n ) noexcept {
            X /= n;
            Y /= n;
            return *this;
        }

        // Dot product function
        constexpr T dot( const vector& v ) const noexcept {
            return X * v.X + Y * v.Y;
        }

        // Dot product operator
        constexpr T operator&( const vector &v ) const noexcept {
            return dot(v);
        }

        // Vector length (sq)
        constexpr T squaredLength( ) const noexcept {
            return X * X + Y * Y;
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
            return vtx::math::max(X, Y);
        }

        // Minimal component
        constexpr T minC( ) const noexcept {
            return vtx::math::min(X, Y);
        }

        // Two vectors linear interpolation
        constexpr vector lerp( const vector &v, const T t ) const noexcept {
            return vector{
                X + t * (v.X - X),
                Y + t * (v.Y - Y)
            };
        }

        // Maximal components vector
        constexpr vector maxV( const vector &v ) const noexcept {
            return vector{
                vtx::math::max(X, v.X),
                vtx::math::max(Y, v.Y)
            };
        }

        // Minimal components vector
        constexpr vector minV( const vector &v ) const noexcept {
            return vector{
                vtx::math::min(X, v.X),
                vtx::math::min(Y, v.Y)
            };
        }

        // Ceil vector components
        constexpr vector ceil( ) const noexcept {
            return vector{
                vtx::math::ceil(X),
                vtx::math::ceil(Y)
            };
        }

        // Floor vector components
        constexpr vector floor( ) const noexcept {
            return vector{
                vtx::math::floor(X),
                vtx::math::floor(Y)
            };
        }

        // Vector components composition
        constexpr T volume( ) const noexcept {
            return X * Y;
        }

        constexpr T sum() const noexcept {
            return X + Y;
        }

        constexpr double avg() const noexcept {
            return sum() / (double)2;
        }

        constexpr size_t size() const noexcept {
            return 2;
        }

    }; // class vector

} // namespace vtx

#endif //VECTRIX_VECTOR2_H
