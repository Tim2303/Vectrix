//
// Created by Timmimin on 14.05.2025.
//

#ifndef VECTRIX_BASE_VECTOR_H
#define VECTRIX_BASE_VECTOR_H

#include "vectrix/math/common.h"

// vtx namespace
namespace vtx
{
    // Base vector class of any size
    template<typename T, size_t N>
    class vector {
    private:
        static_assert(N > 0,
                "Vector dimension N must be greater than zero");

        // Helper metafunction to check that all arguments are convertible to T
        template<typename... Args>
        struct all_convertible : std::true_type {};

        template<typename First, typename... Rest>
        struct all_convertible<First, Rest...> :
                std::integral_constant<bool,
                        std::is_convertible<First, T>::value &&
                        all_convertible<Rest...>::value> {};

    public:
        T elements[N];

        // Class default constructor
        constexpr vector( ) = default;

        // One parameter constructor
        constexpr explicit vector( const T num ) noexcept {
            for (size_t i = 0; i < N; ++i) {
                elements[i] = num;
            }
        }

        // Variadic constructor (C++11-compatible)
        template<typename... Args>
        constexpr explicit vector(Args... args) noexcept {
            static_assert(sizeof...(Args) <= N,
                    "Too many constructor arguments!");
            static_assert(all_convertible<Args...>::value,
                    "All arguments must be convertible to T");

            T* dst = elements;
            using expander = int[];
            (void)expander{0, ((void)(*dst++ = static_cast<T>(args)), 0)...};

            for (size_t i = sizeof...(Args); i < N; ++i)
                elements[i] = T(0);
        }

        // Initializer list constructor
        constexpr vector( std::initializer_list<T> list ) noexcept {
            size_t i = 0;
            for (T val : list) {
                if (i < N)
                    elements[i++] = val;
            }
            while (i < N)
                elements[i++] = T(0);
        }

        // Vectors equality operator
        constexpr bool operator==( const vector &v ) const noexcept {
            for (size_t i = 0; i < N; ++i)
                if (v.elements[i] != elements[i])
                    return false;
            return true;
        }

        // Vectors inequality operator
        constexpr bool operator!=( const vector &v ) const noexcept {
            for (size_t i = 0; i < N; ++i)
                if (v.elements[i] != elements[i])
                    return true;
            return false;
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
            return elements + N;
        }
        constexpr const T* end() const noexcept {
            return elements + N;
        }

        // Component getter operator
        constexpr T operator[]( const size_t ind ) const {
#ifdef _DEBUG
            assert(ind < N);
#endif // _DEBUG
            return elements[ind];
        }

        // Component reference getter operator
        constexpr T & operator[]( const size_t ind ) {
#ifdef _DEBUG
            assert(ind < N);
#endif // _DEBUG
            return elements[ind];
        }

        // Negation operator
        constexpr vector operator-( ) const noexcept {
            vector result;
            for (size_t i = 0; i < N; ++i) {
                result.elements[i] = -elements[i];
            }

            return result;
        }

        // Addition operator
        constexpr vector operator+( const vector &v ) const noexcept {
            vector result;
            for (size_t i = 0; i < N; ++i) {
                result.elements[i] = elements[i] + v.elements[i];
            }

            return result;
        }

        // Addition to current operator
        constexpr vector operator+=( const vector &v ) noexcept {
            for (size_t i = 0; i < N; ++i) {
                elements[i] += v.elements[i];
            }

            return *this;
        }

        // Subtraction operator
        constexpr vector operator-( const vector &v ) const noexcept {
            vector result;
            for (size_t i = 0; i < N; ++i) {
                result.elements[i] = elements[i] - v.elements[i];
            }

            return result;
        }

        // Subtraction from current operator
        constexpr vector operator-=( const vector &v ) noexcept {
            for (size_t i = 0; i < N; ++i) {
                elements[i] -= v.elements[i];
            }

            return *this;
        }

        // Multiplication operator
        constexpr vector operator*( const vector &v ) const noexcept {
            vector result;
            for (size_t i = 0; i < N; ++i) {
                result.elements[i] = elements[i] * v.elements[i];
            }

            return result;
        }

        // Multiplication with current operator
        constexpr vector operator*=( const vector &v ) noexcept {
            for (size_t i = 0; i < N; ++i) {
                elements[i] *= v.elements[i];
            }

            return *this;
        }

        // Multiplication operator
        constexpr vector operator*( const T n ) const noexcept {
            vector result;
            for (size_t i = 0; i < N; ++i) {
                result.elements[i] = elements[i] * n;
            }

            return result;
        }

        // Multiplication with current operator
        constexpr vector operator*=( const T n ) noexcept {
            for (size_t i = 0; i < N; ++i) {
                elements[i] *= n;
            }

            return *this;
        }

        // Division operator
        constexpr vector operator/( const vector &v ) const noexcept {
            vector result;
            for (size_t i = 0; i < N; ++i) {
                result.elements[i] = elements[i] / v.elements[i];
            }

            return result;
        }

        // Division from current operator
        constexpr vector operator/=( const vector &v ) noexcept {
            for (size_t i = 0; i < N; ++i) {
                elements[i] /= v.elements[i];
            }

            return *this;
        }

        // Division operator
        constexpr vector operator/( const T n ) const noexcept {
            vector result;
            for (size_t i = 0; i < N; ++i) {
                result.elements[i] = elements[i] / n;
            }

            return result;
        }

        // Division from current operator
        constexpr vector operator/=( const T n ) noexcept {
            for (size_t i = 0; i < N; ++i) {
                elements[i] /= n;
            }

            return *this;
        }

        // Dot product operator
        constexpr T operator&( const vector &v ) const noexcept {
            return dot(v);
        }

        // Dot product function
        constexpr T dot( const vector& v ) const noexcept {
            T sum = T(0);
            for (size_t i = 0; i < N; ++i) {
                sum += elements[i] * v.elements[i];
            }

            return sum;
        }


        // Vector length (sq)
        constexpr T squaredLength( ) const noexcept {
            T sum = T(0);
            for (size_t i = 0; i < N; ++i) {
                sum += elements[i] * elements[i];
            }

            return sum;
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
        constexpr vector & normalize( ) noexcept {
            T len = length();
#ifdef _DEBUG
            assert(len != T(0));
#endif // _DEBUG
            return *this /= len;
        }

        // Maximal component
        constexpr T maxC( ) const noexcept {
            T mx = elements[0];
            for (size_t i = 1; i < N; ++i) {
                mx = vtx::math::max(mx, elements[i]);
            }

            return mx;
        }

        // Minimal component
        constexpr T minC( ) const noexcept {
            T mn = elements[0];
            for (size_t i = 1; i < N; ++i) {
                mn = vtx::math::min(mn, elements[i]);
            }

            return mn;
        }

        // Two vectors linear interpolation
        constexpr vector lerp( const vector &v, const T t ) const noexcept {
            vector res;
            for (size_t i = 0; i < N; ++i) {
                res.elements[i] = elements[i] + t * (v.elements[i] - elements[i]);
            }

            return res;
        }

        // Maximal components vector
        constexpr vector maxV( const vector &v ) const noexcept {
            vector res;
            for (size_t i = 0; i < N; ++i) {
                res.elements[i] = vtx::math::max(elements[i], v.elements[i]);
            }

            return res;
        }

        // Minimal components vector
        constexpr vector minV( const vector &v ) const noexcept {
            vector res;
            for (size_t i = 0; i < N; ++i) {
                res.elements[i] = vtx::math::min(elements[i], v.elements[i]);
            }

            return res;
        }

        // Ceil vector components
        constexpr vector ceil( ) const noexcept {
            vector res;
            for (size_t i = 0; i < N; ++i) {
                res.elements[i] = vtx::math::ceil(elements[i]);
            }

            return res;
        }

        // Floor vector components
        constexpr vector floor( ) const noexcept {
            vector res;
            for (size_t i = 0; i < N; ++i) {
                res.elements[i] = vtx::math::floor(elements[i]);
            }

            return res;
        }

        // Vector components composition
        constexpr T volume( ) const noexcept {
            T result = T(1);
            for (size_t i = 0; i < N; ++i) {
                result *= elements[i];
            }

            return result;
        }

        constexpr T sum() const noexcept {
            T s = T(0);
            for (size_t i = 0; i < N; ++i)
                s += elements[i];
            return s;
        }

        constexpr double avg() const noexcept {
            return sum() / (double)N;
        }


    }; // class vector

} // namespace vtx

#endif //VECTRIX_BASE_VECTOR_H
