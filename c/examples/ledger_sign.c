
#include <in3/client.h>   // the core client
#include <in3/eth_api.h>  // functions for direct api-access
#include <in3/in3_init.h> // if included the verifier will automaticly be initialized.
#include <in3/log.h>      // logging functions
#include <in3/signer.h>   // default signer implementation
#include <in3/utils.h>
#include <../src/api/signer/ledger-nano/ledger-incubed-signer/ledger_signer.h>
#include <stdio.h>



static void send_tx_api(in3_t* in3);

int main() {
  // create new incubed client
  in3_t* in3 = in3_for_chain(ETH_CHAIN_ID_MAINNET);

  // create a simple signer with this key
  eth_ledger_set_signer(in3);

  // send tx using API
  send_tx_api(in3);

  // cleanup client after usage
  in3_free(in3);
}


void send_tx_api(in3_t* in3) {
  // prepare parameters
  address_t to, from;
  hex_to_bytes("0x63FaC9201494f0bd17B9892B9fae4d52fe3BD377", -1, from, 20);
  hex_to_bytes("0xd46e8dd67c5d32be8058bb8eb970870f07244567", -1, to, 20);

  bytes_t* data = hex_to_new_bytes("d46e8dd67c5d32be8d46e8dd67c5d32be8058bb8eb970870f072445675058bb8eb970870f072445675", 82);

  // send the tx
  bytes_t* tx_hash = eth_sendTransaction(in3, from, to, OPTIONAL_T_VALUE(uint64_t, 0x96c0), OPTIONAL_T_VALUE(uint64_t, 0x9184e72a000), OPTIONAL_T_VALUE(uint256_t, to_uint256(0x9184e72a)), OPTIONAL_T_VALUE(bytes_t, *data), OPTIONAL_T_UNDEFINED(uint64_t));

  // if the result is null there was an error and we can get the latest error message from eth_last_error()
  if (!tx_hash)
    printf("error sending the tx : %s\n", eth_last_error());
  else {
    printf("Transaction hash: ");
    b_print(tx_hash);
    b_free(tx_hash);
  }
  b_free(data);
}
