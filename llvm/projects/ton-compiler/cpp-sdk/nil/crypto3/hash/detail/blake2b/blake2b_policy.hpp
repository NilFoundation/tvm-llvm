//---------------------------------------------------------------------------//
// Copyright (c) 2018-2020 Mikhail Komarov <nemo@nil.foundation>
// Copyright (c) 2020 Nikita Kaskov <nbering@nil.foundation>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//---------------------------------------------------------------------------//

#ifndef CRYPTO3_BLAKE2B_POLICY_HPP
#define CRYPTO3_BLAKE2B_POLICY_HPP

#include <nil/crypto3/detail/static_digest.hpp>
#include <nil/crypto3/detail/basic_functions.hpp>

namespace nil {
    namespace crypto3 {
        namespace hashes {
            namespace detail {
                template<std::size_t DigestBits>
                struct blake2b_policy : public ::nil::crypto3::detail::basic_functions<64> {

                    constexpr static const std::size_t state_bits = 512;
                    constexpr static const std::size_t state_words = state_bits / word_bits;
                    typedef std::array<word_type, state_words> state_type;

                    constexpr static const std::size_t block_bits = 1024;
                    constexpr static const std::size_t block_words = block_bits / word_bits;
                    typedef std::array<word_type, block_words> block_type;

                    constexpr static const std::size_t length_bits = word_bits;

                    typedef typename stream_endian::little_octet_big_bit digest_endian;

                    constexpr static const std::size_t digest_bits = DigestBits;
                    typedef static_digest<digest_bits> digest_type;

                    constexpr static const std::size_t rounds = 12;

                    struct iv_generator {
                        state_type const &operator()() const {
                            constexpr static const state_type H0 = {
                                {0x6a09e667f3bcc908, 0xbb67ae8584caa73b, 0x3c6ef372fe94f82b, 0xa54ff53a5f1d36f1,
                                 0x510e527fade682d1, 0x9b05688c2b3e6c1f, 0x1f83d9abfb41bd6b, 0x5be0cd19137e2179}};
                            return H0;
                        }
                    };

                    constexpr static const std::size_t salt_bits = 64;
                    typedef typename boost::uint_t<salt_bits>::exact salt_type;
                    constexpr static const salt_type salt_value = 0xFFFFFFFFFFFFFFFF;
                };
            }    // namespace detail
        }        // namespace hashes
    }            // namespace crypto3
}    // namespace nil

#endif    // CRYPTO3_BLAKE2B_POLICY_HPP
