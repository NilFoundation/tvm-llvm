//---------------------------------------------------------------------------//
// Copyright (c) 2020 Mikhail Komarov <nemo@nil.foundation>
// Copyright (c) 2020 Nikita Kaskov <nbering@nil.foundation>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//---------------------------------------------------------------------------//

#ifndef CRYPTO3_ALGEBRA_CURVES_BLS12_BASIC_POLICY_HPP
#define CRYPTO3_ALGEBRA_CURVES_BLS12_BASIC_POLICY_HPP

#include <nil/crypto3/algebra/fields/bls12/base_field.hpp>
#include <nil/crypto3/algebra/fields/bls12/scalar_field.hpp>

#include <nil/crypto3/algebra/fields/fp2.hpp>
#include <nil/crypto3/algebra/fields/fp12_2over3over2.hpp>

#include <nil/crypto3/algebra/detail/literals.hpp>

namespace nil {
    namespace crypto3 {
        namespace algebra {
            namespace curves {
                namespace detail {

                    using namespace algebra;

                    template<std::size_t ModulusBits = 381, std::size_t GeneratorBits = CHAR_BIT>
                    struct bls12_basic_policy { };

                    template<>
                    struct bls12_basic_policy<381, CHAR_BIT> {
                        constexpr static const std::size_t base_field_bits = 381;
                        typedef fields::bls12_fq<base_field_bits, CHAR_BIT> g1_field_type;
                        using base_field_type = g1_field_type;
                        typedef typename fields::fp2<base_field_type> g2_field_type;
                        typedef typename fields::fp12_2over3over2<base_field_type> gt_field_type;

                        typedef typename base_field_type::modulus_type number_type;
                        typedef typename base_field_type::extended_modulus_type extended_number_type;

                        constexpr static const number_type base_field_modulus = base_field_type::modulus;

                        constexpr static const std::size_t scalar_field_bits = 381;    // actually, 255
                        typedef fields::bls12_fr<scalar_field_bits, CHAR_BIT> scalar_field_type;
                        constexpr static const number_type scalar_field_modulus = scalar_field_type::modulus;

                        constexpr static const number_type p = base_field_modulus;
                        constexpr static const number_type q = scalar_field_modulus;

                        constexpr static const number_type a = number_type(0x00);
                        constexpr static const number_type b = number_type(0x04);
                    };

                    template<>
                    struct bls12_basic_policy<377, CHAR_BIT> {
                        constexpr static const std::size_t base_field_bits = 377;
                        typedef fields::bls12_fq<base_field_bits, CHAR_BIT> g1_field_type;
                        using base_field_type = g1_field_type;
                        typedef typename fields::fp2<base_field_type> g2_field_type;
                        typedef typename fields::fp12_2over3over2<base_field_type> gt_field_type;

                        typedef typename base_field_type::modulus_type number_type;
                        constexpr static const number_type base_field_modulus = base_field_type::modulus;
                        typedef typename base_field_type::extended_modulus_type extended_number_type;

                        constexpr static const std::size_t scalar_field_bits = 377;    // actually, 253
                        typedef fields::bls12_fr<scalar_field_bits, CHAR_BIT> scalar_field_type;
                        constexpr static const number_type scalar_field_modulus = scalar_field_type::modulus;

                        constexpr static const number_type p = base_field_modulus;
                        constexpr static const number_type q = scalar_field_modulus;

                        constexpr static const number_type a = number_type(0x00);
                        constexpr static const number_type b = number_type(0x01);
                    };

                    constexpr typename bls12_basic_policy<381, CHAR_BIT>::number_type const
                        bls12_basic_policy<381, CHAR_BIT>::a;
                    constexpr typename bls12_basic_policy<377, CHAR_BIT>::number_type const
                        bls12_basic_policy<377, CHAR_BIT>::a;

                    constexpr typename bls12_basic_policy<381, CHAR_BIT>::number_type const
                        bls12_basic_policy<381, CHAR_BIT>::b;
                    constexpr typename bls12_basic_policy<377, CHAR_BIT>::number_type const
                        bls12_basic_policy<377, CHAR_BIT>::b;

                    constexpr typename std::size_t const bls12_basic_policy<381, CHAR_BIT>::base_field_bits;
                    constexpr typename std::size_t const bls12_basic_policy<377, CHAR_BIT>::base_field_bits;

                    constexpr typename std::size_t const bls12_basic_policy<381, CHAR_BIT>::scalar_field_bits;
                    constexpr typename std::size_t const bls12_basic_policy<377, CHAR_BIT>::scalar_field_bits;

                    constexpr typename bls12_basic_policy<381, CHAR_BIT>::number_type const
                        bls12_basic_policy<381, CHAR_BIT>::p;
                    constexpr typename bls12_basic_policy<377, CHAR_BIT>::number_type const
                        bls12_basic_policy<377, CHAR_BIT>::p;

                    constexpr typename bls12_basic_policy<381, CHAR_BIT>::number_type const
                        bls12_basic_policy<381, CHAR_BIT>::q;
                    constexpr typename bls12_basic_policy<377, CHAR_BIT>::number_type const
                        bls12_basic_policy<377, CHAR_BIT>::q;

                }    // namespace detail
            }        // namespace curves
        }            // namespace algebra
    }                // namespace crypto3
}    // namespace nil
#endif    // ALGEBRA_CURVES_BLS12_BASIC_POLICY_HPP