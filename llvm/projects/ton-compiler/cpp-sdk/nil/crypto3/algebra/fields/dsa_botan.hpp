//---------------------------------------------------------------------------//
// Copyright (c) 2020 Mikhail Komarov <nemo@nil.foundation>
// Copyright (c) 2020 Nikita Kaskov <nbering@nil.foundation>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//---------------------------------------------------------------------------//

#ifndef CRYPTO3_ALGEBRA_FIELDS_DSA_BOTAN_HPP
#define CRYPTO3_ALGEBRA_FIELDS_DSA_BOTAN_HPP

#include <nil/crypto3/algebra/fields/detail/element/fp.hpp>

#include <nil/crypto3/algebra/fields/params.hpp>
#include <nil/crypto3/algebra/fields/field.hpp>

#include <nil/crypto3/algebra/detail/literals.hpp>

namespace nil {
    namespace crypto3 {
        namespace algebra {
            namespace fields {

                /*!
                 * @brief DSA group
                 * @tparam ModulusBits
                 * @tparam GeneratorBits
                 */
                template<std::size_t ModulusBits, std::size_t GeneratorBits = ModulusBits>
                struct dsa_botan : public field<ModulusBits, GeneratorBits> { };

                template<>
                struct dsa_botan<2048, 2048> : public field<2048, 2048> {
                    typedef field<2048, 2048> policy_type;

                    constexpr static const std::size_t modulus_bits = policy_type::modulus_bits;
                    typedef typename policy_type::modulus_type modulus_type;

                    typedef typename policy_type::extended_modulus_type extended_modulus_type;

                    constexpr static const std::size_t number_bits = policy_type::number_bits;
                    typedef typename policy_type::number_type number_type;

                    constexpr static const modulus_type modulus =
                        0x91C48A4FDFBCF7C02AE95E7DA126122B5DD2864F559B87E8E74A286D52F59BD1DE68DFD645D0E00C60C080031891980374EEB594A532BFD67B9A09EAC4B8663A07910E68F39465FB7040D25DF13932EBAC4347A530ECBA61C854F9B880D3C0C3660080587C45566DADE26BD5A394BE093B4C0F24B5AFFEF8EC6C5B3E57FB89025A9BC16769932131E16D3C94EFCAB18D0DF061203CC53E6103BC72D5594BFD40CA65380F44A9A851DCB075495FC033A8A58071A1BD78FE052F66555648EB4B719D2AFE8B4880F8DAD6F15818BA178F89274C870BE9B96EB08C46C40040CC2EFE1DFB1B1868DD319DE3C34A32A63AB6EB1224209A419680CC7902D1728D4DF9E1_cppui2048;

                    constexpr static const std::size_t generator_bits = policy_type::generator_bits;
                    typedef typename policy_type::generator_type generator_type;

                    constexpr static const generator_type mul_generator =
                        0xD9F5E0761B4DBD1833D6AB1A961A0996C5F22303F72D84C140F67C431D94AB5715BEA81A0C98D39CE4BCF78D6B9EBC895D34FE89D94091D5848615EF15F5E86F11D96F6C969E203DDFA58356420A49CB444B595B901A933CFE0767B594F18A07B7F91DECDBA446B88990F78F2FF91F2FE7CD43FD2E46D18EADA1F7BB6602C617F6EF3A4B284F2FD9BA10A36042DE8FA87A2CA36597FEC81157A1485E44041DF02830111CB880BBE6ED494814886F965CDC3135F5CCF1383728BF65B806F9692C0B10D6C4C09C75A6CA3B4013CB16AB2C105F6BE23AEA9000EAB2178985F972C98057E1C86E44E7218688EA4AE0F3636DCCA745C9DCD4E6AFFB67CCBC13D6131_cppui2048;

                    typedef typename detail::element_fp<params<dsa_botan<modulus_bits, generator_bits>>> value_type;

                    constexpr static const std::size_t arity = 1;
                };

                template<>
                struct dsa_botan<3072, 3072> : public field<3072, 3072> {
                    typedef field<3072, 3072> policy_type;

                    constexpr static const std::size_t modulus_bits = policy_type::modulus_bits;
                    typedef typename policy_type::modulus_type modulus_type;

                    constexpr static const modulus_type modulus =
                        0xE4B50880759663585E142460CA2D9DFF132F8AE4C840DDA3A2666889124FE5638B84E8A29B7AF3FA1209BE6BFC4B5072ED3B2B7387BAF3F857F478A80228EF3600B76B3DCFB61D20D34465B2506D2CAF87DF6E7DC0CE91BD2D167A46F6ADCC31C531E4F9C7ABBDB92ADDF35B0A806C66292A5F5E17E964DD099903733AC428AB35D80EA6F685BFBA8BE4068E5418AE5ECAD9E8FF073DE2B63E4E7EAD35C8A9B70B5BD47CFB88D373B66F37931939B0AB71BD5595809086DA0155337D185A0E4FB36A519B1B6202B8591E6002449CF1CD3A66384F6D2073B1CD73BECA93BAF1E1A6117D0238F222AE1ED7FED185A890E7F67FAB8FEB9753CC134A5183DFE87AE2595F7B5C2D9FBB42249FDD59513E1D3396B3EB2FD86684F285A8448FE757A029881C40760B94EF919BDF9740C38389599EC51A6E9BB519A8E068491E9CE0A2FCFE3CB60D66CF0DFAD20A8EC684048684A61444575BD1724D7352B44A760077B3BD6BD385CE5B0A7250CC0BF768DA82923806EB9CFBB138843731B618208C759B_cppui3072;

                    constexpr static const std::size_t generator_bits = policy_type::generator_bits;
                    typedef typename policy_type::generator_type generator_type;

                    constexpr static const generator_type mul_generator =
                        0x2BED21EEF83964A230AE89BBA71D9F7C39C52FC8229B4E3BC7E5944D329DA10F010EAC9E7BAF6C009FC4EB2960723E2B56DF4663E4C3AC800E9258DE2F7649D206782893F865EFCA498D2EEF30074EA5E8A7AB262712A4D94A2F3B0B9A92EE400FB38A3CC59A5DC7E436D5C004B22E35028381B51C93407EB32D4AE0FD42CB45E12D0ECEE8A26238EDE2082A7B1522113C66CEF8D745C6CF3CB945F84D2F4DE16D44A71DE198270E13F03553C88B8D323AD0B948A1BF2103A949979B6ED16FB5F3C953D95B7C8E88CA67DCF5A636FB9CA39D924215F7A884ED6C7EE3C96D8D9715427974B7C4351282E13D3773F7D28B452F10892A13C7587328DEA4827B6B369B2A8DC172ADC583F51F2A6598C5483E5BC467B02F91D059C402D18E2C2680F776AA06F49280A2C72C17CC42D5B6E740C5C4B1AB3C51C2ED092BE2A2D8B053AE5773D1425ED2B08F06E2DD50592DF1A478C15591CDFD11564FF88FF38B721D42392FDA473212DCFD8D2D88A976A00AFFE6FFFB430A359E64CA2B351CA2412394_cppui3072;

                    typedef typename detail::element_fp<params<dsa_botan<modulus_bits, generator_bits>>> value_type;

                    constexpr static const std::size_t arity = 1;
                };

                constexpr typename dsa_botan<2048, 2048>::modulus_type const dsa_botan<2048, 2048>::modulus;
                constexpr typename dsa_botan<3072, 3072>::modulus_type const dsa_botan<3072, 3072>::modulus;

                constexpr typename dsa_botan<2048, 2048>::generator_type const dsa_botan<2048, 2048>::mul_generator;
                constexpr typename dsa_botan<3072, 3072>::generator_type const dsa_botan<3072, 3072>::mul_generator;
            }    // namespace fields
        }        // namespace algebra
    }            // namespace crypto3
}    // namespace nil

#endif    // ALGEBRA_FIELDS_DSA_BOTAN_HPP
