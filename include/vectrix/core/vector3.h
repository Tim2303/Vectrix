//
// Created by Timmimin on 05.07.2025.
//

#ifndef VECTRIX_VECTOR3_H
#define VECTRIX_VECTOR3_H

#include "vectrix/math/common.h"

#include "base_vector.h"

// vtx namespace
namespace vtx
{
    // Vector 3 class specialization
    template<typename T>
    class vector<T, 3> {
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
            T elements[3];

            // Dimension names
            struct {
                T X, Y, Z;
            };
        };

        // Class default constructor
        constexpr vector( ) = default;

        // One parameter constructor
        constexpr explicit vector( const T num ) noexcept {
            elements[2] = elements[1] = elements[0] = num;
        }

        // Variadic constructor (C++11-compatible)
        template<typename... Args>
        constexpr explicit vector(Args... args) noexcept {
            static_assert(sizeof...(Args) <= 3,
                    "Too many constructor arguments!");
            static_assert(all_convertible<Args...>::value,
                    "All arguments must be convertible to T");

            T* dst = elements;
            using expander = int[];
            (void)expander{0, ((void)(*dst++ = static_cast<T>(args)), 0)...};

#ifdef VTX_DEFAULT_FILL0
            for (size_t i = sizeof...(Args); i < 3; ++i)
                elements[i] = T(0);
#endif // VTX_DEFAULT_FILL0
        }

        // Initializer list constructor
        constexpr vector( std::initializer_list<T> list ) noexcept {
            size_t i = 0;
            for (T val : list) {
                if (i < 3)
                    elements[i++] = val;
            }
#ifdef VTX_DEFAULT_FILL0
            while (i < 3)
                elements[i++] = T(0);
#endif // VTX_DEFAULT_FILL0
        }

        // Vectors equality operator
        constexpr bool operator==( const vector &v ) const noexcept {
            return X == v.X && Y == v.Y && Z == v.Z;
        }

        // Vectors inequality operator
        constexpr bool operator!=( const vector &v ) const noexcept {
            return X != v.X || Y != v.Y || Z != v.Z;
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
            return elements + 3;
        }
        constexpr const T* end() const noexcept {
            return elements + 3;
        }

        // Component getter operator
        constexpr T operator[]( const size_t ind ) const {
#ifdef _DEBUG
            assert(ind < 3);
#endif // _DEBUG
            return elements[ind];
        }

        // Component reference getter operator
        constexpr T& operator[]( const size_t ind ) {
#ifdef _DEBUG
            assert(ind < 3);
#endif // _DEBUG
            return elements[ind];
        }

        // Negation operator
        constexpr vector operator-( ) const noexcept {
            return vector{-X, -Y, -Z};
        }

        // Addition operator
        constexpr vector operator+( const vector &v ) const noexcept {
            return vector{
                    X + v.X,
                    Y + v.Y,
                    Z + v.Z
            };
        }

        // Addition to current operator
        constexpr vector& operator+=( const vector &v ) noexcept {
            X += v.X;
            Y += v.Y;
            Z += v.Z;
            return *this;
        }

        // Subtraction operator
        constexpr vector operator-( const vector &v ) const noexcept {
            return vector{
                    X - v.X,
                    Y - v.Y,
                    Z - v.Z
            };
        }

        // Subtraction from current operator
        constexpr vector& operator-=( const vector &v ) noexcept {
            X -= v.X;
            Y -= v.Y;
            Z -= v.Z;
            return *this;
        }

        // Multiplication operator
        constexpr vector operator*( const vector &v ) const noexcept {
            return {
                    X * v.X,
                    Y * v.Y,
                    Z * v.Z
            };
        }

        // Multiplication with current operator
        constexpr vector& operator*=( const vector &v ) noexcept {
            X *= v.X;
            Y *= v.Y;
            Z *= v.Z;
            return *this;
        }

        // Multiplication operator
        constexpr vector operator*( const T n ) const noexcept {
            return vector{
                    X * n,
                    Y * n,
                    Z * n
            };
        }

        // Multiplication with current operator
        constexpr vector& operator*=( const T n ) noexcept {
            X *= n;
            Y *= n;
            Z *= n;
            return *this;
        }

        // Division operator
        constexpr vector operator/( const vector &v ) const noexcept {
            return vector{
                    X / v.X,
                    Y / v.Y,
                    Z / v.Z
            };
        }

        // Division from current operator
        constexpr vector& operator/=( const vector &v ) noexcept {
            X /= v.X;
            Y /= v.Y;
            Z /= v.Z;
            return *this;
        }

        // Division operator
        constexpr vector operator/( const T n ) const noexcept {
            return vector{
                    X / n,
                    Y / n,
                    Z / n
            };
        }

        // Division from current operator
        constexpr vector& operator/=( const T n ) noexcept {
            X /= n;
            Y /= n;
            Z /= n;
            return *this;
        }

        // Dot product function
        constexpr T dot( const vector& v ) const noexcept {
            return X * v.X + Y * v.Y + Z * v.Z;
        }

        // Dot product operator
        constexpr T operator&( const vector &v ) const noexcept {
            return dot(v);
        }

        // Vector cross multiplication function
        constexpr vector cross( const vector& v ) const noexcept {
            return vector{
                Y * v.Z - Z * v.Y,
                -X * v.Z + Z * v.X,
                X * v.Y - Y * v.X
            };
        }

        // Vector cross multiplication operator
        constexpr vector operator%( const vector &v ) const noexcept {
            return cross(v);
        }

        // Vector cross multiplication operator
        constexpr vector& operator%=( const vector &v ) noexcept {
            *this = cross(v);
            return *this;
        }

        // Vector length (sq)
        constexpr T squaredLength( ) const noexcept {
            return X * X + Y * Y + Z * Z;
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
            return vtx::math::max(X, Y, Z);
        }

        // Minimal component
        constexpr T minC( ) const noexcept {
            return vtx::math::min(X, Y, Z);
        }

        // Two vectors linear interpolation
        constexpr vector lerp( const vector &v, const T t ) const noexcept {
            return vector{
                    X + t * (v.X - X),
                    Y + t * (v.Y - Y),
                    Z + t * (v.Z - Z)
            };
        }

        // Find angle between vectors (in degrees)
        constexpr double Angle( const vector& v ) const noexcept
        {
            if (squaredLength() == 0 || v.squaredLength() == 0)
                return 0;
            return vtx::math::R2D * vtx::math::atan2(((*this).cross(v)).length(), (*this).dot(v));
        }

        // Maximal components vector
        constexpr vector maxV( const vector &v ) const noexcept {
            return vector{
                    vtx::math::max(X, v.X),
                    vtx::math::max(Y, v.Y),
                    vtx::math::max(Z, v.Z)
            };
        }

        // Minimal components vector
        constexpr vector minV( const vector &v ) const noexcept {
            return vector{
                    vtx::math::min(X, v.X),
                    vtx::math::min(Y, v.Y),
                    vtx::math::min(Z, v.Z)
            };
        }

        // Ceil vector components
        constexpr vector ceil( ) const noexcept {
            return vector{
                    vtx::math::ceil(X),
                    vtx::math::ceil(Y),
                    vtx::math::ceil(Z)
            };
        }

        // Floor vector components
        constexpr vector floor( ) const noexcept {
            return vector{
                    vtx::math::floor(X),
                    vtx::math::floor(Y),
                    vtx::math::floor(Z)
            };
        }

        // Vector components composition
        constexpr T volume( ) const noexcept {
            return X * Y * Z;
        }

        constexpr T sum() const noexcept {
            return X + Y + Z;
        }

        constexpr double avg() const noexcept {
            return sum() / (double)3;
        }

        constexpr size_t size() const noexcept {
            return 3;
        }

    }; // class vector

} // namespace vtx

#endif //VECTRIX_VECTOR3_H
