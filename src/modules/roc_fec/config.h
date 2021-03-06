/*
 * Copyright (c) 2015 Mikhail Baranov
 * Copyright (c) 2015 Victor Gaydov
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

//! @file roc_fec/config.h
//! @brief FEC code type options.

#ifndef ROC_FEC_CONFIG_H_
#define ROC_FEC_CONFIG_H_

#include "roc_core/stddefs.h"

namespace roc {
namespace fec {

//! FEC code type.
enum CodecType {
    //! FEC is disabled.
    NoCodec,

    //! OpenFEC Reed-Solomon.
    ReedSolomon8m,

    //! OpenFEC LDPC-Staircase.
    LDPCStaircase,

    //! Maximum for iterating through the enum.
    CodecTypeMax
};

//! FEC configuration.
struct Config {
    //! FEC codec.
    CodecType codec;

    //! Number of data packets in block.
    size_t n_source_packets;

    //! Number of FEC packets in block.
    size_t n_repair_packets;

    //! Seed for LDPC scheme.
    int32_t ldpc_prng_seed;

    //! N1 parameter LDPC scheme.
    uint8_t ldpc_N1;

    //! Configuration for ReedSolomon scheme.
    uint16_t rs_m;

    Config()
        : codec(NoCodec)
        , n_source_packets(20)
        , n_repair_packets(10)
        , ldpc_prng_seed(1297501556)
        , ldpc_N1(7)
        , rs_m(8) {
    }
};

} // namespace fec
} // namespace roc

#endif // ROC_FEC_CONFIG_H_
