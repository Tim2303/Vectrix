//
// Created by Timmimin on 14.05.2025.
//

#ifndef VECTRIX_BASE_VECTOR_H
#define VECTRIX_BASE_VECTOR_H

#include "vectrix/math/common.h"

// Library namespace
namespace vtx
{
    // Base vector class of any size
    template<typename T, size_t N>
    class vector {
    public:
        T data[N];

        // Class default constructor
        constexpr vector( void ) = default;

        // One parameter constructor
        constexpr vector( const T num ) noexcept {
            for (size_t i = 0; i < N; ++i) {
                data[i] = num;
            }
        }

        // Multiple parameters constructor
        template <typename... Args>
        constexpr vector( Args... args ) noexcept {
            static_assert((std::is_convertible_v<Args, T> && ...),
                    "All arguments must be convertible to T!");

            size_t i = 0;
            ((i < N ? (data[i++] = args) : T(0)), ...);
            while (i < N) data[i++] = T(0);
        }

        // Vectors equality operator
        constexpr bool operator==( const vector<T, N> &v ) noexcept {
            for (size_t i = 0; i < N; ++i)
                if (v.data[i] != data[i])
                    return false;
            return true;
        }

        // Vectors unequality operator
        constexpr bool operator!=( const vector<T, N> &v ) noexcept {
            for (size_t i = 0; i < N; ++i)
                if (v.data[i] != data[i])
                    return true;
            return false;
        }

        // Pointer cast operator
        constexpr operator Type*( VOID ) const noexcept {
            return &data[0];
        }

        // Component getter operator
        constexpr Type operator[]( const size_t ind ) const {
            return *(&data[0] + ind);
        }

        // Component reference getter operator
        constexpr Type & operator[]( const size_t ind ) {
            return *(&data[0] + ind);
        }

        // Negate operator
        constexpr vector<T, N> operator-( void ) const noexcept {
            vector<T, N> result;
            for (size_t i = 0; i < N; ++i) {
                result.data[i] = -data[i];
            }

            return result;
        }

        // Addition operator
        constexpr vector<T, N> operator+( const vector<T, N> &v ) const noexcept {
            vector<T, N> result;
            for (size_t i = 0; i < N; ++i) {
                result.data[i] = data[i] + v.data[i];
            }

            return result;
        }

        // Addition to current operator
        constexpr vector<T, N> operator+=( const vector<T, N> &v ) noexcept {
            for (size_t i = 0; i < N; ++i) {
                data[i] += v.data[i];
            }

            return *this;
        }

        // Subtraction operator
        constexpr vector<T, N> operator-( const vector<T, N> &v ) const noexcept {
            vector<T, N> result;
            for (size_t i = 0; i < N; ++i) {
                result.data[i] = data[i] - v.data[i];
            }

            return result;
        }

        // Subtraction from current operator
        constexpr vector<T, N> operator-=( const vector<T, N> &v ) noexcept {
            for (size_t i = 0; i < N; ++i) {
                data[i] -= v.data[i];
            }

            return *this;
        }

        // Multiplication operator
        constexpr vector<T, N> operator*( const vector<T, N> &v ) const noexcept {
            vector<T, N> result;
            for (size_t i = 0; i < N; ++i) {
                result.data[i] = data[i] * v.data[i];
            }

            return result;
        }

        // Multiplication with current operator
        constexpr vector<T, N> operator*=( const vector<T, N> &v ) noexcept {
            for (size_t i = 0; i < N; ++i) {
                data[i] *= v.data[i];
            }

            return *this;
        }

        // Multiplication operator
        constexpr vector<T, N> operator*( const T n ) const noexcept {
            vector<T, N> result;
            for (size_t i = 0; i < N; ++i) {
                result.data[i] = data[i] * n;
            }

            return result;
        }

        // Multiplication with current operator
        constexpr vector<T, N> operator*=( const T n ) noexcept {
            for (size_t i = 0; i < N; ++i) {
                data[i] *= n;
            }

            return *this;
        }

        // Division operator
        constexpr vector<T, N> operator/( const vector<T, N> &v ) const noexcept {
            vector<T, N> result;
            for (size_t i = 0; i < N; ++i) {
                result.data[i] = data[i] / v.data[i];
            }

            return result;
        }

        // Division from current operator
        constexpr vector<T, N> operator/=( const vector<T, N> &v ) noexcept {
            for (size_t i = 0; i < N; ++i) {
                data[i] /= v.data[i];
            }

            return *this;
        }

        // Division operator
        constexpr vector<T, N> operator/( const T n ) const noexcept {
            vector<T, N> result;
            for (size_t i = 0; i < N; ++i) {
                result.data[i] = data[i] / n;
            }

            return result;
        }

        // Division from current operator
        constexpr vector<T, N> operator/=( const T n ) noexcept {
            for (size_t i = 0; i < N; ++i) {
                data[i] /= n;
            }

            return *this;
        }

        // Dot product operator
        constexpr T operator&( const vector<T, N> &v ) const noexcept {
            T sum = 0;
            for (size_t i = 0; i < N; ++i) {
                sum += data[i] * v.data[i];
            }

            return sum;
        }

        // Vector length (sq)
        constexpr T length2( void ) const noexcept {
            T sum = 0;
            for (size_t i = 0; i < N; ++i) {
                sum += data[i] * data[i];
            }

            return sum;
        }

        // Vector length
        constexpr T length( void ) const noexcept {
            T sum = 0;
            for (size_t i = 0; i < N; ++i) {
                sum += data[i] * data[i];
            }

            return sqrt(sum);
        }

        // Normalized vector
        constexpr vector<T, N> normalized( void ) const noexcept {
            return *this / length();
        }

        // Normalize current vector
        constexpr vector<T, N> & normalize( void ) noexcept {
            return *this /= length();
        }

        // Maximal component
        constexpr T maxC( void ) const noexcept {
            T mx = data[0];
            for (size_t i = 1; i < N; ++i) {
                mx = max(mx, data[i]);
            }

            return mx;
        }

        // Minimal component
        constexpr T minC( void ) const noexcept {
            T mn = data[0];
            for (size_t i = 1; i < N; ++i) {
                mn = min(mn, data[i]);
            }

            return mn;
        }

        // Two vectors linear interpolation
        constexpr vector<T, N> lerp( const vector<T, N> &v, const T coef ) const noexcept {
            vector<T, N> res;
            for (size_t i = 0; i < N; ++i) {
                res.data[i] = data[i] + coef * (v.data[i] - data[i]);
            }

            return res;
        }

        // Maximal components vector
        constexpr vector<T, N> maxV( const vector<T, N> &v ) const noexcept {
            vector<T, N> res;
            for (size_t i = 0; i < N; ++i) {
                res[i] = max(data[i], v.data[i]);
            }

            return res;
        }

        // Minimal components vector
        constexpr vector<T, N> minV( const vector<T, N> &v ) const noexcept {
            vector<T, N> res;
            for (size_t i = 0; i < N; ++i) {
                res[i] = min(data[i], v.data[i]);
            }

            return res;
        }


        /// TODO: Other from file Z:\CPP\mth\tcr_mth_vec3.h


    }; // class vector

} // namespace vtx

#endif //VECTRIX_BASE_VECTOR_H
