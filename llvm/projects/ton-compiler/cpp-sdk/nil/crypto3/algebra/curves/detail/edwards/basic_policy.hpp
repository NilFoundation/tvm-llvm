//---------------------------------------------------------------------------//
// Copyright (c) 2020 Mikhail Komarov <nemo@nil.foundation>
// Copyright (c) 2020 Nikita Kaskov <nbering@nil.foundation>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//---------------------------------------------------------------------------//

#ifndef CRYPTO3_ALGEBRA_CURVES_EDWARDS_BASIC_POLICY_HPP
#define CRYPTO3_ALGEBRA_CURVES_EDWARDS_BASIC_POLICY_HPP

#include <nil/crypto3/algebra/fields/edwards/base_field.hpp>
#include <nil/crypto3/algebra/fields/edwards/scalar_field.hpp>

#include <nil/crypto3/algebra/fields/fp3.hpp>
#include <nil/crypto3/algebra/fields/fp6_2over3.hpp>

#include <nil/crypto3/algebra/detail/literals.hpp>

namespace nil {
    namespace crypto3 {
        namespace algebra {
            namespace curves {
                namespace detail {

                    using namespace algebra;

                    template<std::size_t ModulusBits = 183, std::size_t GeneratorBits = CHAR_BIT>
                    struct edwards_basic_policy { };

                    template<>
                    struct edwards_basic_policy<183, CHAR_BIT> {
                        constexpr static const std::size_t base_field_bits = 183;
                        typedef fields::edwards_fq<base_field_bits, CHAR_BIT> g1_field_type;
                        using base_field_type = g1_field_type;
                        typedef typename fields::fp3<base_field_type> g2_field_type;
                        typedef typename fields::fp6_2over3<base_field_type> gt_field_type;

                        typedef typename base_field_type::modulus_type number_type;
                        typedef typename base_field_type::extended_modulus_type extended_number_type;

                        constexpr static const number_type base_field_modulus = base_field_type::modulus;

                        constexpr static const std::size_t scalar_field_bits = 183;
                        typedef fields::edwards_fr<scalar_field_bits, CHAR_BIT> scalar_field_type;
                        constexpr static const number_type scalar_field_modulus = scalar_field_type::modulus;

                        constexpr static const number_type p = base_field_modulus;
                        constexpr static const number_type q = scalar_field_modulus;

                        constexpr static const number_type a = 0x01;
                        constexpr static const number_type d = 0x64536D55979879327CF1306BB5A6277D254EF9776CE70_cppui179;
                    };

                    constexpr typename edwards_basic_policy<183, CHAR_BIT>::number_type const
                        edwards_basic_policy<183, CHAR_BIT>::base_field_modulus;

                    constexpr typename edwards_basic_policy<183, CHAR_BIT>::number_type const
                        edwards_basic_policy<183, CHAR_BIT>::scalar_field_modulus;

                    constexpr typename edwards_basic_policy<183, CHAR_BIT>::number_type const
                        edwards_basic_policy<183, CHAR_BIT>::a;

                    constexpr typename edwards_basic_policy<183, CHAR_BIT>::number_type const
                        edwards_basic_policy<183, CHAR_BIT>::d;

                    constexpr typename edwards_basic_policy<183, CHAR_BIT>::number_type const
                        edwards_basic_policy<183, CHAR_BIT>::p;

                    constexpr typename edwards_basic_policy<183, CHAR_BIT>::number_type const
                        edwards_basic_policy<183, CHAR_BIT>::q;

                }    // namespace detail
            }        // namespace curves
        }            // namespace algebra
    }                // namespace crypto3
}    // namespace nil

#endif    // ALGEBRA_CURVES_EDWARDS_BASIC_POLICY_HPP
