//---------------------------------------------------------------------------//
// Copyright (c) 2020 Mikhail Komarov <nemo@nil.foundation>
// Copyright (c) 2020 Nikita Kaskov <nbering@nil.foundation>
// Copyright (c) 2020 Ilias Khairullin <ilias@nil.foundation>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//---------------------------------------------------------------------------//

#ifndef CRYPTO3_ALGEBRA_VECTOR_CLASS_HPP
#define CRYPTO3_ALGEBRA_VECTOR_CLASS_HPP

#include <nil/crypto3/algebra/detail/same_value.hpp>
#include <nil/crypto3/algebra/detail/assert.hpp>

#include <array>
#include <cstddef>

namespace nil {
    namespace crypto3 {
        namespace algebra {

            /** @brief A container representing a vector
             *    @tparam T scalar type to contain
             *    @tparam N size of the vector
             *
             *    `vector` is a container representing a vector.
             *
             *    It is an aggregate type similar to `std::array`, and can be initialized with
             *    aggregate initialization or with the `make_vector` function.
             */
            template<typename T, std::size_t N>
            struct vector {
                static_assert(N != 0, "vector must contain at least one element");
                // CRYPTO3_DETAIL_ASSERT_ARITHMETIC(T)

                using value_type = T;
                using size_type = std::size_t;
                static constexpr size_type size = N;    ///< @brief size of the vector

                /** @name Element access */
                ///@{
                /** @brief access specified element
                 *    @param i position of the scalar element
                 *    @return the requested scalar element
                 *
                 *    Returns a reference to the scalar element in position `i`, without bounds checking.
                 */
                constexpr T &operator[](size_type i) noexcept {
                    return array[i];
                }

                /// @copydoc operator[]
                constexpr const T &operator[](size_type i) const noexcept {
                    return array[i];
                }
                ///@}

                /** @name Iterators */
                ///@{
                /** @brief returns an iterator to the beginning
                 *    @return an iterator to the beginning
                 *
                 *    Returns an iterator to the beginning of the vector.
                 */
                constexpr T *begin() noexcept {
                    return array;
                }

                /** @brief returns an iterator to the end
                 *    @return an iterator past the end
                 *
                 *    Returns an iterator to the end of the vector.
                 */
                constexpr T *end() noexcept {
                    return array + N;
                }

                /// @copydoc begin
                constexpr const T *cbegin() const noexcept {
                    return array;
                }

                /// @copydoc end
                constexpr const T *cend() const noexcept {
                    return array + N;
                }
                ///@}

                T array[N];    ///< @private
            };

            /** \addtogroup vector
             *    @{
             */

            /** @brief constructs a `vector` from arguments
             *    @param args scalar elements to combine into a vector
             *    @return a vector containing `args`
             *    @relatesalso vector
             *
             *    Constructs a vector from its arguments, checking that all arguments are of
             *    the same type.
             */
            template<typename... Args>
            constexpr decltype(auto) make_vector(Args... args) {
                return vector {args...};
            }

            /** @name vector deduction guides */
            ///@{

            /** @brief deduction guide for uniform initialization
             *    @relatesalso vector
             *
             *    This deduction guide allows vector to be constructed like this:
             *    \code{.cpp}
             *    vector v{1., 2.}; // deduces the type of v to be vector<double, 2>
             *    \endcode
             */
            template<typename T, typename... U>
            vector(T, U...) -> vector<std::enable_if_t<(std::is_same_v<T, U> && ...), T>, 1 + sizeof...(U)>;

            /** @brief deduction guide for aggregate initialization
             *    @relatesalso vector
             *
             *    This deduction guide allows vector to be constructed like this:
             *    \code{.cpp}
             *    vector v{{1., 2.}}; // deduces the type of v to be vector<double, 2>
             *    \endcode
             */
            template<typename T, std::size_t N>
            vector(const T (&)[N]) -> vector<T, N>;

            ///@}

            /** @}*/

        }    // namespace algebra
    }        // namespace crypto3
}    // namespace nil
#endif    // ALGEBRA_VECTOR_CLASS_HPP
