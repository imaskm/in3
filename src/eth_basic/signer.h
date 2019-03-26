/** @file 
 * Ethereum Nanon verification.
 * */

#ifndef in3_signer_h__
#define in3_signer_h__

#include "../core/client/context.h"

int eth_sign(void* pk, d_signature_type_t type, bytes_t message, bytes_t account, uint8_t* dst);

int eth_set_pk_signer(in3_t* in3, bytes32_t pk);

int eth_handle_intern(in3_ctx_t* ctx, in3_response_t** response);

#endif