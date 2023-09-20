#pragma once

#include <array>
#include <cassert>
#include <cstdint>
#include <Eigen/Eigen>

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

    /* vectors */
    template <typename T, usize N>
    struct GenericVector {
        std::array<T, N> array;
        constexpr T &operator[](usize i) noexcept {return array[i];}
        constexpr T const &operator[](usize i) const noexcept {return array[i];}
        auto operator==(GenericVector<T, N> const &other) const -> bool = default;
        auto operator!=(GenericVector<T, N> const &other) const -> bool = default;
    };


    template <typename T>
    struct GenericVector<T, 2> {
        T x;
        T y;
        constexpr T & operator[](usize i) noexcept {
            switch (i) {
                case 1: return y;
                default: return x;
            }
        }
        constexpr T const & operator[](usize i) const noexcept {
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
        constexpr T & operator[](usize i) noexcept {
            switch (i) {
                case 1: return y;
                case 2: return z;
                default: return x;
            }
        }
        constexpr T const & operator[](usize i) const noexcept {
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
        constexpr T & operator[](usize i) noexcept {
            switch (i) {
                case 1: return y;
                case 2: return z;
                case 3: return w;
                default: return x;
            }
        }
        constexpr T const & operator[](usize i) const noexcept {
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

    /* renaming */
    using b32vec2 = GenericVector<b32, 2>;
    using b32vec3 = GenericVector<b32, 3>;
    using b32vec4 = GenericVector<b32, 4>;
    using f32vec2 = GenericVector<f32, 2>;
    using f32mat2x2 = GenericMatrix<f32, 2, 2>;
    using f32mat2x3 = GenericMatrix<f32, 2, 3>;
    using f32mat2x4 = GenericMatrix<f32, 2, 4>;
    using f64vec2 = GenericVector<f64, 2>;
    using f64mat2x2 = GenericMatrix<f64, 2, 2>;
    using f64mat2x3 = GenericMatrix<f64, 2, 3>;
    using f64mat2x4 = GenericMatrix<f64, 2, 4>;
    using f32vec3 = GenericVector<f32, 3>;
    using f32mat3x2 = GenericMatrix<f32, 3, 2>;
    using f32mat3x3 = GenericMatrix<f32, 3, 3>;
    using f32mat3x4 = GenericMatrix<f32, 3, 4>;
    using f64vec3 = GenericVector<f64, 3>;
    using f64mat3x2 = GenericMatrix<f64, 3, 2>;
    using f64mat3x3 = GenericMatrix<f64, 3, 3>;
    using f64mat3x4 = GenericMatrix<f64, 3, 4>;
    using f32vec4 = GenericVector<f32, 4>;
    using f32mat4x2 = GenericMatrix<f32, 4, 2>;
    using f32mat4x3 = GenericMatrix<f32, 4, 3>;
    using f32mat4x4 = GenericMatrix<f32, 4, 4>;
    using f64vec4 = GenericVector<f64, 4>;
    using f64mat4x2 = GenericMatrix<f64, 4, 2>;
    using f64mat4x3 = GenericMatrix<f64, 4, 3>;
    using f64mat4x4 = GenericMatrix<f64, 4, 4>;
    using i32vec2 = GenericVector<i32, 2>;
    using i32mat2x2 = GenericMatrix<i32, 2, 2>;
    using i32mat2x3 = GenericMatrix<i32, 2, 3>;
    using i32mat2x4 = GenericMatrix<i32, 2, 4>;
    using u32vec2 = GenericVector<u32, 2>;
    using u32mat2x2 = GenericMatrix<u32, 2, 2>;
    using u32mat2x3 = GenericMatrix<u32, 2, 3>;
    using u32mat2x4 = GenericMatrix<u32, 2, 4>;
    using i32vec3 = GenericVector<i32, 3>;
    using i32mat3x2 = GenericMatrix<i32, 3, 2>;
    using i32mat3x3 = GenericMatrix<i32, 3, 3>;
    using i32mat3x4 = GenericMatrix<i32, 3, 4>;
    using u32vec3 = GenericVector<u32, 3>;
    using u32mat3x2 = GenericMatrix<u32, 3, 2>;
    using u32mat3x3 = GenericMatrix<u32, 3, 3>;
    using u32mat3x4 = GenericMatrix<u32, 3, 4>;
    using i32vec4 = GenericVector<i32, 4>;
    using i32mat4x2 = GenericMatrix<i32, 4, 2>;
    using i32mat4x3 = GenericMatrix<i32, 4, 3>;
    using i32mat4x4 = GenericMatrix<i32, 4, 4>;
    using u32vec4 = GenericVector<u32, 4>;
    using u32mat4x2 = GenericMatrix<u32, 4, 2>;
    using u32mat4x3 = GenericMatrix<u32, 4, 3>;
    using u32mat4x4 = GenericMatrix<u32, 4, 4>;

    /* math operations */
    template <typename T, usize N>
    constexpr auto operator+(GenericVector<T, N> const &a, GenericVector<T, N> const &b) -> GenericVector<T, N> {
        GenericVector<T, N> result;
        for (usize i = 0; i < N; i++) {
            result[i] = a[i] + b[i];
        }
        return result;
    }

    template <typename T, usize N>
    constexpr auto operator-(GenericVector<T, N> const &a, GenericVector<T, N> const &b) -> GenericVector<T, N> {
        GenericVector<T, N> result;
        for (usize i = 0; i < N; i++) {
            result[i] = a[i] - b[i];
        }
        return result;
    }

    template <typename T, usize N>
    constexpr auto operator*(GenericVector<T, N> const &a, GenericVector<T, N> const &b) -> GenericVector<T, N> {
        GenericVector<T, N> result;
        for (usize i = 0; i < N; i++) {
            result[i] = a[i] * b[i];
        }
        return result;
    }

    template <typename T, usize N>
    constexpr auto operator/(GenericVector<T, N> const &a, GenericVector<T, N> const &b) -> GenericVector<T, N> {
        GenericVector<T, N> result;
        for (usize i = 0; i < N; i++) {
            result[i] = a[i] / b[i];
        }
        return result;
    }

    template <typename T, usize N>
    constexpr auto dot(GenericVector<T, N> const &a, GenericVector<T, N> const &b) -> T {
        T result;
        for (usize i = 0; i < N; i++) {
            result += a[i] * b[i];
        }
        return result;
    }

    template <typename T, usize N>
    constexpr auto operator+(GenericVector<T, N> const &a, T const &b) -> GenericVector<T, N> {
        GenericVector<T, N> result;
        for (usize i = 0; i < N; i++) {
            result[i] = a[i] + b;
        }
        return result;
    }

    template <typename T, usize N>
    constexpr auto operator-(GenericVector<T, N> const &a, T const &b) -> GenericVector<T, N> {
        GenericVector<T, N> result;
        for (usize i = 0; i < N; i++) {
            result[i] = a[i] - b;
        }
        return result;
    }

    template <typename T, usize N>
    constexpr auto operator*(GenericVector<T, N> const &a, T const &b) -> GenericVector<T, N> {
        GenericVector<T, N> result;
        for (usize i = 0; i < N; i++) {
            result[i] = a[i] * b;
        }
        return result;
    }

    template <typename T, usize N>
    constexpr auto operator/(GenericVector<T, N> const &a, T const &b) -> GenericVector<T, N> {
        GenericVector<T, N> result;
        for (usize i = 0; i < N; i++) {
            result[i] = a[i] / b;
        }
        return result;
    }
}