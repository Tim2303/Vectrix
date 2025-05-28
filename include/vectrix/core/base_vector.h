//
// Created by Timmimin on 14.05.2025.
//

#ifndef VECTRIX_BASE_VECTOR_H
#define VECTRIX_BASE_VECTOR_H

// Library namespace
namespace vectrix
{
    // Base vector class of any size
    template<typename T, size_t N>
    class vector {
    private:

    public:
        T data[N];

        // Class default constructor
        constexpr vector( void ) = default;

        // One number constructor
        constexpr vector( const T num ) noexcept {
            for (size_t i = 0; i < N; ++i) {
                data[i] = num;
            }
        }

        template <typename... Args>
        constexpr vector(Args... args) noexcept {
            static_assert((std::is_convertible_v<Args, T> && ...),
                    "All arguments must be convertible to T!");

            size_t i = 0;
            ((i < N ? (data[i++] = args) : T(0)), ...);
            while (i < N) data[i++] = T(0);
        }


    }; /* End of 'vector' class */
} /* End of 'vectrix' namespace */

#endif //VECTRIX_BASE_VECTOR_H
