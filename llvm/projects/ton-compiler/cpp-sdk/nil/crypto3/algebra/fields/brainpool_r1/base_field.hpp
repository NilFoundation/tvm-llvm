//---------------------------------------------------------------------------//
// Copyright (c) 2020 Mikhail Komarov <nemo@nil.foundation>
// Copyright (c) 2020 Nikita Kaskov <nbering@nil.foundation>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//---------------------------------------------------------------------------//

#ifndef CRYPTO3_ALGEBRA_FIELDS_BRAINPOOL_R1_BASE_FIELD_HPP
#define CRYPTO3_ALGEBRA_FIELDS_BRAINPOOL_R1_BASE_FIELD_HPP

#include <nil/crypto3/algebra/fields/detail/element/fp.hpp>
#include <nil/crypto3/algebra/fields/params.hpp>

#include <nil/crypto3/algebra/fields/field.hpp>

#include <nil/crypto3/algebra/detail/literals.hpp>

namespace nil {
    namespace crypto3 {
        namespace algebra {
            namespace fields {

                /*!
                 * @brief IETF IPsec groups
                 * @tparam ModulusBits
                 * @tparam GeneratorBits
                 */
                template<std::size_t ModulusBits, std::size_t GeneratorBits = CHAR_BIT>
                struct brainpool_r1_base_field : public field<ModulusBits, GeneratorBits> { };

                template<>
                struct brainpool_r1_base_field<160, CHAR_BIT> : public field<160, CHAR_BIT> {
                    typedef field<160, CHAR_BIT> policy_type;

                    constexpr static const std::size_t modulus_bits = policy_type::modulus_bits;
                    typedef typename policy_type::modulus_type modulus_type;

                    typedef typename policy_type::extended_modulus_type extended_modulus_type;

                    constexpr static const std::size_t number_bits = policy_type::number_bits;
                    typedef typename policy_type::number_type number_type;

                    constexpr static const modulus_type modulus = 0xE95E4A5F737059DC60DFC7AD95B3D8139515620F_cppui160;

                    constexpr static const std::size_t generator_bits = policy_type::generator_bits;
                    typedef typename policy_type::generator_type generator_type;

                    constexpr static const generator_type mul_generator = 0x03;

                    typedef typename detail::element_fp<params<brainpool_r1_base_field<160, CHAR_BIT>>> value_type;

                    constexpr static const std::size_t arity = 1;
                };

                template<>
                struct brainpool_r1_base_field<192, CHAR_BIT> : public field<192, CHAR_BIT> {
                    typedef field<192, CHAR_BIT> policy_type;

                    constexpr static const std::size_t modulus_bits = policy_type::modulus_bits;
                    typedef typename policy_type::modulus_type modulus_type;

                    typedef typename policy_type::extended_modulus_type extended_modulus_type;

                    constexpr static const modulus_type modulus =
                        0xC302F41D932A36CDA7A3463093D18DB78FCE476DE1A86297_cppui192;

                    constexpr static const std::size_t generator_bits = policy_type::generator_bits;
                    typedef typename policy_type::generator_type generator_type;

                    constexpr static const generator_type mul_generator = 0x03;

                    typedef typename detail::element_fp<params<brainpool_r1_base_field<192, CHAR_BIT>>> value_type;

                    constexpr static const std::size_t arity = 1;
                };

                template<>
                struct brainpool_r1_base_field<224, CHAR_BIT> : public field<224, CHAR_BIT> {
                    typedef field<224, CHAR_BIT> policy_type;

                    constexpr static const std::size_t modulus_bits = policy_type::modulus_bits;
                    typedef typename policy_type::modulus_type modulus_type;

                    typedef typename policy_type::extended_modulus_type extended_modulus_type;

                    constexpr static const modulus_type modulus =
                        0xD7C134AA264366862A18302575D1D787B09F075797DA89F57EC8C0FF_cppui224;

                    constexpr static const std::size_t generator_bits = policy_type::generator_bits;
                    typedef typename policy_type::generator_type generator_type;

                    constexpr static const generator_type mul_generator = 0x03;

                    typedef typename detail::element_fp<params<brainpool_r1_base_field<224, CHAR_BIT>>> value_type;

                    constexpr static const std::size_t arity = 1;
                };

                template<>
                struct brainpool_r1_base_field<256, CHAR_BIT> : public field<256, CHAR_BIT> {
                    typedef field<256, CHAR_BIT> policy_type;

                    constexpr static const std::size_t modulus_bits = policy_type::modulus_bits;
                    typedef typename policy_type::modulus_type modulus_type;

                    typedef typename policy_type::extended_modulus_type extended_modulus_type;

                    constexpr static const modulus_type modulus =
                        0xA9FB57DBA1EEA9BC3E660A909D838D726E3BF623D52620282013481D1F6E5377_cppui256;

                    constexpr static const std::size_t generator_bits = policy_type::generator_bits;
                    typedef typename policy_type::generator_type generator_type;

                    constexpr static const generator_type mul_generator = 0x03;

                    typedef typename detail::element_fp<params<brainpool_r1_base_field<256, CHAR_BIT>>> value_type;

                    constexpr static const std::size_t arity = 1;
                };

                template<>
                struct brainpool_r1_base_field<320, CHAR_BIT> : public field<320, CHAR_BIT> {
                    typedef field<320, CHAR_BIT> policy_type;

                    constexpr static const std::size_t modulus_bits = policy_type::modulus_bits;
                    typedef typename policy_type::modulus_type modulus_type;

                    typedef typename policy_type::extended_modulus_type extended_modulus_type;

                    constexpr static const modulus_type modulus =
                        0xD35E472036BC4FB7E13C785ED201E065F98FCFA6F6F40DEF4F92B9EC7893EC28FCD412B1F1B32E27_cppui320;

                    constexpr static const std::size_t generator_bits = policy_type::generator_bits;
                    typedef typename policy_type::generator_type generator_type;

                    constexpr static const generator_type mul_generator = 0x03;

                    typedef typename detail::element_fp<params<brainpool_r1_base_field<320, CHAR_BIT>>> value_type;

                    constexpr static const std::size_t arity = 1;
                };

                template<>
                struct brainpool_r1_base_field<384, CHAR_BIT> : public field<384, CHAR_BIT> {
                    typedef field<384, CHAR_BIT> policy_type;

                    constexpr static const std::size_t modulus_bits = policy_type::modulus_bits;
                    typedef typename policy_type::modulus_type modulus_type;

                    typedef typename policy_type::extended_modulus_type extended_modulus_type;

                    constexpr static const modulus_type modulus =
                        0x8CB91E82A3386D280F5D6F7E50E641DF152F7109ED5456B412B1DA197FB71123ACD3A729901D1A71874700133107EC53_cppui384;

                    constexpr static const std::size_t generator_bits = policy_type::generator_bits;
                    typedef typename policy_type::generator_type generator_type;

                    constexpr static const generator_type mul_generator = 0x03;

                    typedef typename detail::element_fp<params<brainpool_r1_base_field<384, CHAR_BIT>>> value_type;

                    constexpr static const std::size_t arity = 1;
                };

                template<>
                struct brainpool_r1_base_field<512, CHAR_BIT> : public field<512, CHAR_BIT> {
                    typedef field<512, CHAR_BIT> policy_type;

                    constexpr static const std::size_t modulus_bits = policy_type::modulus_bits;
                    typedef typename policy_type::modulus_type modulus_type;

                    typedef typename policy_type::extended_modulus_type extended_modulus_type;

                    constexpr static const modulus_type modulus =
                        0xAADD9DB8DBE9C48B3FD4E6AE33C9FC07CB308DB3B3C9D20ED6639CCA703308717D4D9B009BC66842AECDA12AE6A380E62881FF2F2D82C68528AA6056583A48F3_cppui512;

                    constexpr static const std::size_t generator_bits = policy_type::generator_bits;
                    typedef typename policy_type::generator_type generator_type;

                    constexpr static const generator_type mul_generator = 0x03;

                    typedef typename detail::element_fp<params<brainpool_r1_base_field<512, CHAR_BIT>>> value_type;

                    constexpr static const std::size_t arity = 1;
                };

                constexpr typename brainpool_r1_base_field<160, CHAR_BIT>::modulus_type const
                    brainpool_r1_base_field<160, CHAR_BIT>::modulus;
                constexpr typename brainpool_r1_base_field<192, CHAR_BIT>::modulus_type const
                    brainpool_r1_base_field<192, CHAR_BIT>::modulus;
                constexpr typename brainpool_r1_base_field<224, CHAR_BIT>::modulus_type const
                    brainpool_r1_base_field<224, CHAR_BIT>::modulus;
                constexpr typename brainpool_r1_base_field<256, CHAR_BIT>::modulus_type const
                    brainpool_r1_base_field<256, CHAR_BIT>::modulus;
                constexpr typename brainpool_r1_base_field<320, CHAR_BIT>::modulus_type const
                    brainpool_r1_base_field<320, CHAR_BIT>::modulus;
                constexpr typename brainpool_r1_base_field<384, CHAR_BIT>::modulus_type const
                    brainpool_r1_base_field<384, CHAR_BIT>::modulus;
                constexpr typename brainpool_r1_base_field<512, CHAR_BIT>::modulus_type const
                    brainpool_r1_base_field<512, CHAR_BIT>::modulus;

                constexpr typename brainpool_r1_base_field<160, CHAR_BIT>::generator_type const
                    brainpool_r1_base_field<160, CHAR_BIT>::mul_generator;
                constexpr typename brainpool_r1_base_field<192, CHAR_BIT>::generator_type const
                    brainpool_r1_base_field<192, CHAR_BIT>::mul_generator;
                constexpr typename brainpool_r1_base_field<224, CHAR_BIT>::generator_type const
                    brainpool_r1_base_field<224, CHAR_BIT>::mul_generator;
                constexpr typename brainpool_r1_base_field<256, CHAR_BIT>::generator_type const
                    brainpool_r1_base_field<256, CHAR_BIT>::mul_generator;
                constexpr typename brainpool_r1_base_field<320, CHAR_BIT>::generator_type const
                    brainpool_r1_base_field<320, CHAR_BIT>::mul_generator;
                constexpr typename brainpool_r1_base_field<384, CHAR_BIT>::generator_type const
                    brainpool_r1_base_field<384, CHAR_BIT>::mul_generator;
                constexpr typename brainpool_r1_base_field<512, CHAR_BIT>::generator_type const
                    brainpool_r1_base_field<512, CHAR_BIT>::mul_generator;

                template<std::size_t ModulusBits = 160, std::size_t GeneratorBits = CHAR_BIT>
                using brainpool_r1_fq = brainpool_r1_base_field<ModulusBits, GeneratorBits>;
                template<std::size_t ModulusBits = 192, std::size_t GeneratorBits = CHAR_BIT>
                using brainpool_r1_fq = brainpool_r1_base_field<ModulusBits, GeneratorBits>;
                template<std::size_t ModulusBits = 224, std::size_t GeneratorBits = CHAR_BIT>
                using brainpool_r1_fq = brainpool_r1_base_field<ModulusBits, GeneratorBits>;
                template<std::size_t ModulusBits = 256, std::size_t GeneratorBits = CHAR_BIT>
                using brainpool_r1_fq = brainpool_r1_base_field<ModulusBits, GeneratorBits>;
                template<std::size_t ModulusBits = 320, std::size_t GeneratorBits = CHAR_BIT>
                using brainpool_r1_fq = brainpool_r1_base_field<ModulusBits, GeneratorBits>;
                template<std::size_t ModulusBits = 384, std::size_t GeneratorBits = CHAR_BIT>
                using brainpool_r1_fq = brainpool_r1_base_field<ModulusBits, GeneratorBits>;
                template<std::size_t ModulusBits = 512, std::size_t GeneratorBits = CHAR_BIT>
                using brainpool_r1_fq = brainpool_r1_base_field<ModulusBits, GeneratorBits>;

                template<std::size_t ModulusBits = 160, std::size_t GeneratorBits = CHAR_BIT>
                using brainpool_r1 = brainpool_r1_base_field<ModulusBits, GeneratorBits>;
                template<std::size_t ModulusBits = 192, std::size_t GeneratorBits = CHAR_BIT>
                using brainpool_r1 = brainpool_r1_base_field<ModulusBits, GeneratorBits>;
                template<std::size_t ModulusBits = 224, std::size_t GeneratorBits = CHAR_BIT>
                using brainpool_r1 = brainpool_r1_base_field<ModulusBits, GeneratorBits>;
                template<std::size_t ModulusBits = 256, std::size_t GeneratorBits = CHAR_BIT>
                using brainpool_r1 = brainpool_r1_base_field<ModulusBits, GeneratorBits>;
                template<std::size_t ModulusBits = 320, std::size_t GeneratorBits = CHAR_BIT>
                using brainpool_r1 = brainpool_r1_base_field<ModulusBits, GeneratorBits>;
                template<std::size_t ModulusBits = 384, std::size_t GeneratorBits = CHAR_BIT>
                using brainpool_r1 = brainpool_r1_base_field<ModulusBits, GeneratorBits>;
                template<std::size_t ModulusBits = 512, std::size_t GeneratorBits = CHAR_BIT>
                using brainpool_r1 = brainpool_r1_base_field<ModulusBits, GeneratorBits>;

            }    // namespace fields
        }        // namespace algebra
    }            // namespace crypto3
}    // namespace nil

#endif    // ALGEBRA_FIELDS_BRAINPOOL_R1_BASE_FIELD_HPP
