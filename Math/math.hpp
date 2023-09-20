#pragma once

#include <array>
#include <cassert>
#include <cstdint>

namespace Math {
    /* basic data types */
    using u8 = std::uint8_t;
    using u16 = std::uint16_t;
    using u32 = std::uint32_t;
    using u64 = std::uint64_t;
    using usize = std::size_t;
    using b32 = u32;

    using i8 = std::int8_t;
    using i16 = std::int16_t;
    using i32 = std::int32_t;
    using i64 = std::int64_t;
    using isize = std::ptrdiff_t;

    using f32 = float;
    using f64 = double;

    namespace detail {
        /* vectors */
        template <typename T, usize N>
        struct GenericVector {
            std::array<T, N> array;

            constexpr inline T &operator[](usize i) noexcept {return array[i];}
            constexpr inline T const &operator[](usize i) const noexcept {return array[i];}

            auto operator==(GenericVector<T, N> const &other) const -> bool = default;
            auto operator!=(GenericVector<T, N> const &other) const -> bool = default;
        };

        template <typename T>
        struct GenericVector<T, 2> {
            T x, y;
            constexpr inline T & operator[](usize i) noexcept {
                switch (i) {
                    case 1: return y;
                    default: return x;
                }
            }

            constexpr inline T const & operator[](usize i) const noexcept {
                switch (i) {
                    case 1: return y;
                    default: return x;
                }
            }

            auto operator==(GenericVector<T,2> const & other) const -> bool = default;
            auto operator!=(GenericVector<T,2> const & other) const -> bool = default;
        };

        template <typename T>
        struct GenericVector<T, 3> {
            T x, y, z;
            constexpr inline T & operator[](usize i) noexcept {
                switch (i) {
                    case 1: return y;
                    case 2: return z;
                    default: return x;
                }
            }

            constexpr inline T const & operator[](usize i) const noexcept {
                switch (i) {
                    case 1: return y;
                    case 2: return z;
                    default: return x;
                }
            }

            auto operator==(GenericVector<T,3> const & other) const -> bool = default;
            auto operator!=(GenericVector<T,3> const & other) const -> bool = default;
        };

        template <typename T>
        struct GenericVector<T, 4> {
            T x, y, z, w;
            constexpr inline T & operator[](usize i) noexcept {
                switch (i) {
                    case 1: return y;
                    case 2: return z;
                    case 3: return w;
                    default: return x;
                }
            }

            constexpr inline T const & operator[](usize i) const noexcept {
                switch (i) {
                    case 1: return y;
                    case 2: return z;
                    case 3: return w;
                    default: return x;
                }
            }

            auto operator==(GenericVector<T,4> const & other) const -> bool = default;
            auto operator!=(GenericVector<T,4> const & other) const -> bool = default;
        };


        /* matrices */
        template <typename T, usize M, usize N>
        struct GenericMatrix : GenericVector<GenericVector<T, N>, M> {};
    }

    /* renaming */
    using b32vec2 = detail::GenericVector<b32, 2>;
    using b32vec3 = detail::GenericVector<b32, 3>;
    using b32vec4 = detail::GenericVector<b32, 4>;
    using f32vec2 = detail::GenericVector<f32, 2>;
    using f32mat2x2 = detail::GenericMatrix<f32, 2, 2>;
    using f32mat2x3 = detail::GenericMatrix<f32, 2, 3>;
    using f32mat2x4 = detail::GenericMatrix<f32, 2, 4>;
    using f64vec2 = detail::GenericVector<f64, 2>;
    using f64mat2x2 = detail::GenericMatrix<f64, 2, 2>;
    using f64mat2x3 = detail::GenericMatrix<f64, 2, 3>;
    using f64mat2x4 = detail::GenericMatrix<f64, 2, 4>;
    using f32vec3 = detail::GenericVector<f32, 3>;
    using f32mat3x2 = detail::GenericMatrix<f32, 3, 2>;
    using f32mat3x3 = detail::GenericMatrix<f32, 3, 3>;
    using f32mat3x4 = detail::GenericMatrix<f32, 3, 4>;
    using f64vec3 = detail::GenericVector<f64, 3>;
    using f64mat3x2 = detail::GenericMatrix<f64, 3, 2>;
    using f64mat3x3 = detail::GenericMatrix<f64, 3, 3>;
    using f64mat3x4 = detail::GenericMatrix<f64, 3, 4>;
    using f32vec4 = detail::GenericVector<f32, 4>;
    using f32mat4x2 = detail::GenericMatrix<f32, 4, 2>;
    using f32mat4x3 = detail::GenericMatrix<f32, 4, 3>;
    using f32mat4x4 = detail::GenericMatrix<f32, 4, 4>;
    using f64vec4 = detail::GenericVector<f64, 4>;
    using f64mat4x2 = detail::GenericMatrix<f64, 4, 2>;
    using f64mat4x3 = detail::GenericMatrix<f64, 4, 3>;
    using f64mat4x4 = detail::GenericMatrix<f64, 4, 4>;
    using i32vec2 = detail::GenericVector<i32, 2>;
    using i32mat2x2 = detail::GenericMatrix<i32, 2, 2>;
    using i32mat2x3 = detail::GenericMatrix<i32, 2, 3>;
    using i32mat2x4 = detail::GenericMatrix<i32, 2, 4>;
    using u32vec2 = detail::GenericVector<u32, 2>;
    using u32mat2x2 = detail::GenericMatrix<u32, 2, 2>;
    using u32mat2x3 = detail::GenericMatrix<u32, 2, 3>;
    using u32mat2x4 = detail::GenericMatrix<u32, 2, 4>;
    using i32vec3 = detail::GenericVector<i32, 3>;
    using i32mat3x2 = detail::GenericMatrix<i32, 3, 2>;
    using i32mat3x3 = detail::GenericMatrix<i32, 3, 3>;
    using i32mat3x4 = detail::GenericMatrix<i32, 3, 4>;
    using u32vec3 = detail::GenericVector<u32, 3>;
    using u32mat3x2 = detail::GenericMatrix<u32, 3, 2>;
    using u32mat3x3 = detail::GenericMatrix<u32, 3, 3>;
    using u32mat3x4 = detail::GenericMatrix<u32, 3, 4>;
    using i32vec4 = detail::GenericVector<i32, 4>;
    using i32mat4x2 = detail::GenericMatrix<i32, 4, 2>;
    using i32mat4x3 = detail::GenericMatrix<i32, 4, 3>;
    using i32mat4x4 = detail::GenericMatrix<i32, 4, 4>;
    using u32vec4 = detail::GenericVector<u32, 4>;
    using u32mat4x2 = detail::GenericMatrix<u32, 4, 2>;
    using u32mat4x3 = detail::GenericMatrix<u32, 4, 3>;
    using u32mat4x4 = detail::GenericMatrix<u32, 4, 4>;

    /* math operations */
    template <typename T, usize N>
    constexpr inline auto operator+(detail::GenericVector<T, N> const &a, detail::GenericVector<T, N> const &b) -> detail::GenericVector<T, N> {
        detail::GenericVector<T, N> result = {};
        for (usize i = 0; i < N; i++) {
            result[i] = a[i] + b[i];
        }
        return result;
    }

    template <typename T, usize N>
    constexpr inline auto operator-(detail::GenericVector<T, N> const &a, detail::GenericVector<T, N> const &b) -> detail::GenericVector<T, N> {
        detail::GenericVector<T, N> result = {};
        for (usize i = 0; i < N; i++) {
            result[i] = a[i] - b[i];
        }
        return result;
    }

    template <typename T, usize N>
    constexpr inline auto operator*(detail::GenericVector<T, N> const &a, detail::GenericVector<T, N> const &b) -> detail::GenericVector<T, N> {
        detail::GenericVector<T, N> result = {};
        for (usize i = 0; i < N; i++) {
            result[i] = a[i] * b[i];
        }
        return result;
    }

    template <typename T, usize N>
    constexpr inline auto operator/(detail::GenericVector<T, N> const &a, detail::GenericVector<T, N> const &b) -> detail::GenericVector<T, N> {
        detail::GenericVector<T, N> result = {};
        for (usize i = 0; i < N; i++) {
            result[i] = a[i] / b[i];
        }
        return result;
    }

    template <typename T, usize N>
    constexpr inline auto operator+(detail::GenericVector<T, N> const &a, T const &b) -> detail::GenericVector<T, N> {
        detail::GenericVector<T, N> result = {};
        for (usize i = 0; i < N; i++) {
            result[i] = a[i] + b;
        }
        return result;
    }

    template <typename T, usize N>
    constexpr inline auto operator-(detail::GenericVector<T, N> const &a, T const &b) -> detail::GenericVector<T, N> {
        detail::GenericVector<T, N> result = {};
        for (usize i = 0; i < N; i++) {
            result[i] = a[i] - b;
        }
        return result;
    }

    template <typename T, usize N>
    constexpr inline auto operator*(detail::GenericVector<T, N> const &a, T const &b) -> detail::GenericVector<T, N> {
        detail::GenericVector<T, N> result = {};
        for (usize i = 0; i < N; i++) {
            result[i] = a[i] * b;
        }
        return result;
    }

    template <typename T, usize N>
    constexpr inline auto operator/(detail::GenericVector<T, N> const &a, T const &b) -> detail::GenericVector<T, N> {
        detail::GenericVector<T, N> result = {};
        for (usize i = 0; i < N; i++) {
            result[i] = a[i] / b;
        }
        return result;
    }

    template <typename T, usize M, usize N, usize P>
    constexpr inline auto operator*(detail::GenericMatrix<T, M, N> const & a, detail::GenericMatrix<T, N, P> const & b) {
        auto c = detail::GenericMatrix<T, M, P>{};
        for (usize i = 0; i < M; ++i) {
            for (usize j = 0; j < P; ++j) {
                c[i][j] = 0;
                for (usize k = 0; k < N; ++k) {
                    c[i][j] += a[i][k] * b[k][j];
                }
            }
        }
        return c;
    }

    template <typename T, usize M, usize N>
    constexpr inline auto operator*(detail::GenericMatrix<T, M, N> const & a, detail::GenericVector<T, N> const & v) {
        auto c = detail::GenericVector<T, N>{};
        for (usize i = 0; i < M; ++i) {
            c[i] = 0;
            for (usize k = 0; k < N; ++k) {
                c[i] += a[i][k] * v[k];
            }
        }
        return c;
    }

    template <typename T, usize N, usize P>
    constexpr inline auto operator*(detail::GenericVector<T, N> const & v, detail::GenericMatrix<T, N, P> const & b) {
        auto c = detail::GenericVector<std::remove_cv_t<T>, N>{};
        for (usize j = 0; j < P; ++j) {
            c[j] = 0;
            for (usize k = 0; k < N; ++k) {
                c[j] += v[k] * b[k][j];
            }
        }
        return c;
    }

    /* mathematic functions */
    template <typename T, usize N>
    constexpr inline auto dot(detail::GenericVector<T, N> const &a, detail::GenericVector<T, N> const &b) -> T {
        T result;
        for (usize i = 0; i < N; i++) {
            result += a[i] * b[i];
        }
        return result;
    }
}