//---------------------------------------------------------------------------//
// Copyright (c) 2020 Mikhail Komarov <nemo@nil.foundation>
// Copyright (c) 2020 Nikita Kaskov <nbering@nil.foundation>
// Copyright (c) 2020 Ilias Khairullin <ilias@nil.foundation>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//---------------------------------------------------------------------------//

#ifndef CRYPTO3_ALGEBRA_VECTOR_OPERATORS_HPP
#define CRYPTO3_ALGEBRA_VECTOR_OPERATORS_HPP

#include <nil/crypto3/algebra/vector/vector.hpp>

namespace nil {
    namespace crypto3 {
        namespace algebra {

            /** \addtogroup vector
             *  @{
             */

            /** @brief checks equality of two vectors
             *  @param a an N-vector of type T
             *  @param b an N-vector of type T
             *  @return true if and only if \f$ \textbf{a}_i = \textbf{b}_i\ \forall i \in 1\ .. N \f$
             *
             *  Checks the equality of two vectors.
             */
            template<typename T, std::size_t N>
            constexpr bool operator==(const vector<T, N> &a, const vector<T, N> &b) {
                for (std::size_t i = 0; i < vector<T, N>::size; ++i) {
                    if (a[i] != b[i])
                        return false;
                }
                return true;
            }

            /** @brief checks inequality of two vectors
             *  @param a an N-vector of type T
             *  @param b an N-vector of type T
             *  @return false if and only if \f$ \textbf{a}_i = \textbf{b}_i\ \forall i \in 1\ .. N \f$
             *
             *  Checks the inequality of two vectors.
             */
            template<typename T, std::size_t N>
            constexpr bool operator!=(const vector<T, N> &a, const vector<T, N> &b) {
                return !(a == b);
            }

            /** @brief computes the sum of a vector and a scalar
             *  @param v an N-vector of type T
             *  @param a a scalar of type T
             *  @return \f$ \textbf{v} + a \f$ such that \f$ \left(\textbf{v} + a\right)_i = \textbf{v}_i + a \f$
             *
             *  Computes the sum of a vector and a scalar.
             */
            template<typename T, std::size_t N>
            constexpr vector<T, N> operator+(const vector<T, N> &v, T a) {
                return elementwise([a](T x) { return x + a; }, v);
            }

            /** @brief computes the sum of a vector and a scalar
             *  @param a a scalar of type T
             *  @param v an N-vector of type T
             *  @return \f$ a + \textbf{v} \f$ such that \f$ \left(a + \textbf{v}\right)_i = a + \textbf{v}_i \f$
             *
             *  Computes the sum of a vector and a scalar.
             */
            template<typename T, std::size_t N>
            constexpr vector<T, N> operator+(T a, const vector<T, N> &v) {
                return elementwise([a](T x) { return a + x; }, v);
            }

            /** @brief computes the vector sum
             *  @param a an N-vector of type T
             *  @param b an N-vector of type T
             *  @return \f$ \textbf{a} + \textbf{b} \f$ such that \f$ \left(\textbf{a} + \textbf{b}\right)_i =
             * \textbf{a}_i
             * + \textbf{b}_i \f$
             *
             *  Computes the vector sum.
             */
            template<typename T, std::size_t N>
            constexpr vector<T, N> operator+(const vector<T, N> &a, const vector<T, N> &b) {
                return elementwise(std::plus<T>(), a, b);
            }

            /** @brief computes the product of a vector and a scalar
             *  @param v an N-vector of type T
             *  @param a a scalar of type T
             *  @return \f$ \textbf{v}a \f$ such that \f$ \left(\textbf{v}a\right)_i = \textbf{v}_i a \f$
             *
             *  Computes the product of a vector and a scalar.
             */
            template<typename T, std::size_t N>
            constexpr vector<T, N> operator*(const vector<T, N> &v, T a) {
                return elementwise([a](T x) { return x * a; }, v);
            }

            /** @brief computes the product of a vector and a scalar
             *  @param a a scalar of type T
             *  @param v an N-vector of type T
             *  @return \f$ a\textbf{v} \f$ such that \f$ \left(a\textbf{v}\right)_i = a\textbf{v}_i \f$
             *
             *  Computes the product of a vector and a scalar.
             */
            template<typename T, std::size_t N>
            constexpr vector<T, N> operator*(T a, const vector<T, N> &v) {
                return elementwise([a](T x) { return a * x; }, v);
            }

            /** @brief computes the Hadamard product
             *  @param a an N-vector of type T
             *  @param b an N-vector of type T
             *  @return \f$ \textbf{a} \circ \textbf{b} \f$ such that \f$ \left(\textbf{a} \circ \textbf{b}\right)_i =
             * \textbf{a}_i \textbf{b}_i \f$
             *
             *  Computes the Hadamard, or elementwise, product of two vectors.
             */
            template<typename T, std::size_t N>
            constexpr vector<T, N> operator*(const vector<T, N> &a, const vector<T, N> &b) {
                return elementwise(std::multiplies<T>(), a, b);
            }

            /** @brief computes the quotient between a vector and a scalar
             *  @param v an N-vector of type T
             *  @param a a scalar of type T
             *  @return \f$ \textbf{v}/a \f$ such that \f$ \left(\textbf{v}/a\right)_i = \frac{\textbf{v}_i}{a} \f$
             *
             *  Computes division between a vector and a scalar.
             */
            template<typename T, std::size_t N>
            constexpr vector<T, N> operator/(T a, const vector<T, N> &v) {
                return elementwise([a](T x) { return a / x; }, v);
            }

            /** @brief computes the elementwise vector quotient
             *  @param a an N-vector of type T
             *  @param b an N-vector of type T
             *  @return \f$ \textbf{a} \circ \textbf{b}' \f$ such that \f$ {\textbf{b}_i}' =
             * \left(\textbf{b}_i\right)^{-1}\f$ and \f$ \left(\textbf{a} \circ \textbf{b}'\right)_i = \textbf{a}_i
             * {\textbf{b}'}_i \f$
             *
             *  Computes elementwise division between two vectors
             */
            template<typename T, std::size_t N>
            constexpr vector<T, N> operator/(const vector<T, N> &a, const vector<T, N> &b) {
                return elementwise(std::divides<T>(), a, b);
            }

            /** }@*/

        }    // namespace algebra
    }        // namespace crypto3
}    // namespace nil
#endif    // ALGEBRA_VECTOR_OPERATORS_HPP
