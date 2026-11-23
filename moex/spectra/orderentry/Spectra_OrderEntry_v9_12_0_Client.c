// moex/spectra/orderentry/Spectra_OrderEntry_v9_12_0_Client.c
/*
 * Moscow Exchange TWIME Spectra Order Entry
 *
 * Generated from the binary model. Every record is a run of fields, and esbmc checks two
 * claims of each, for every value its bytes can take rather than for chosen ones: that any
 * record written to the wire and read back is that record, and that any bytes read off the
 * wire and written back are those bytes. Each takes exactly the record's width, and no
 * write or read leaves the buffer it is made on.
 *
 * A field is the bytes it occupies. Nothing is read as an integer, so nothing is read in a
 * byte order, and no rule stated here depends on a value.
 *
 * Check the whole file:   esbmc <file>
 * Check one record:       esbmc <file> --function check_<record>
 *
 * Built with -DCONCRETE it is an ordinary program any C compiler runs: the bytes the
 * checker would choose are drawn from four patterns instead, so the definition can be
 * tried without the checker. That run is a test, and the checker's is the claim.
 *
 * What this definition does not state, and the model does:
 *   - a run filling what frames it
 *   - a field read in bits
 *   - a block whose stated length holds more than its fields
 *
 * License: MIT No Attribution
 */

#include <assert.h>
#include <stddef.h>
#include <stdint.h>

/* ---- Any byte ---------------------------------------------------------------- */

#ifdef CONCRETE

/* which pattern the bytes are drawn from, and how many have been drawn */
static unsigned pattern;
static size_t drawn;

/* a byte of the pattern: zero, a space, every bit set, or one more than the last */
static uint8_t arbitrary(void) {
  drawn++;

  switch (pattern) {
    case 0: return 0;
    case 1: return 32;
    case 2: return 255;
    default: return (uint8_t)(drawn % 256);
  }
}

#else

/* declared and never defined: a value the checker chooses */
unsigned char __VERIFIER_nondet_uchar(void);

/* a byte nobody chose, so what holds of it holds of all of them */
static uint8_t arbitrary(void) {
  return __VERIFIER_nondet_uchar();
}

#endif

/* ---- Sbe Header: 8 bytes ----------------------------------------------------- */

/* Message body length, message id, message scheme id and message scheme version */
typedef struct {
  uint8_t block_length[2];  /* bytes 0 to 1 */
  uint8_t template_id[2];   /* bytes 2 to 3 */
  uint8_t schema_id[2];     /* bytes 4 to 5 */
  uint8_t version[2];       /* bytes 6 to 7 */
} SbeHeader;

/* any Sbe Header at all: every byte one the checker chooses */
static void any_sbe_header(SbeHeader *record) {
  for (size_t i = 0; i < 2; i++) { record->block_length[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->template_id[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->schema_id[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->version[i] = arbitrary(); }
}

/* Sbe Header to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_sbe_header(const SbeHeader *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->block_length[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->template_id[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->schema_id[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->version[i]; }

  return at;
}

/* Sbe Header off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_sbe_header(SbeHeader *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->block_length[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->template_id[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->schema_id[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->version[i] = wire[at++]; }

  return at;
}

/* what was read of Sbe Header is what was written, byte for byte */
static void equal_sbe_header(const SbeHeader *read, const SbeHeader *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->block_length[i] == written->block_length[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->template_id[i] == written->template_id[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->schema_id[i] == written->schema_id[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->version[i] == written->version[i]); }
}

/* Sbe Header: written and read back, then read and written back */
static void check_sbe_header(void) {
  SbeHeader sent;
  SbeHeader got;
  uint8_t wire[8];
  uint8_t again[8];

  any_sbe_header(&sent);
  assert(encode_sbe_header(&sent, wire, 0) == 8);
  assert(decode_sbe_header(&got, wire, 0) == 8);
  equal_sbe_header(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_sbe_header(&got, wire, 0) == 8);
  assert(encode_sbe_header(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Establish Message: 32 bytes --------------------------------------------- */

/* EstablishMessage */
typedef struct {
  uint8_t timestamp[8];           /* bytes 0 to 7 */
  uint8_t keepalive_interval[4];  /* bytes 8 to 11 */
  uint8_t credentials[20];        /* bytes 12 to 31 */
} EstablishMessage;

/* any Establish Message at all: every byte one the checker chooses */
static void any_establish_message(EstablishMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->keepalive_interval[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->credentials[i] = arbitrary(); }
}

/* Establish Message to the wire: 32 bytes from at, returning where the next byte goes */
static size_t encode_establish_message(const EstablishMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->keepalive_interval[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->credentials[i]; }

  return at;
}

/* Establish Message off the wire: 32 bytes from at, returning where the next byte lies */
static size_t decode_establish_message(EstablishMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->keepalive_interval[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->credentials[i] = wire[at++]; }

  return at;
}

/* what was read of Establish Message is what was written, byte for byte */
static void equal_establish_message(const EstablishMessage *read, const EstablishMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->keepalive_interval[i] == written->keepalive_interval[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->credentials[i] == written->credentials[i]); }
}

/* Establish Message: written and read back, then read and written back */
static void check_establish_message(void) {
  EstablishMessage sent;
  EstablishMessage got;
  uint8_t wire[32];
  uint8_t again[32];

  any_establish_message(&sent);
  assert(encode_establish_message(&sent, wire, 0) == 32);
  assert(decode_establish_message(&got, wire, 0) == 32);
  equal_establish_message(&got, &sent);

  for (size_t i = 0; i < 32; i++) { wire[i] = arbitrary(); }
  assert(decode_establish_message(&got, wire, 0) == 32);
  assert(encode_establish_message(&got, again, 0) == 32);
  for (size_t i = 0; i < 32; i++) { assert(again[i] == wire[i]); }
}

/* ---- Terminate Message: 1 byte ----------------------------------------------- */

/* TerminateMessage */
typedef struct {
  uint8_t termination_code;  /* byte 0 */
} TerminateMessage;

/* any Terminate Message at all: every byte one the checker chooses */
static void any_terminate_message(TerminateMessage *record) {
  record->termination_code = arbitrary();
}

/* Terminate Message to the wire: 1 byte from at, returning where the next byte goes */
static size_t encode_terminate_message(const TerminateMessage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->termination_code;

  return at;
}

/* Terminate Message off the wire: 1 byte from at, returning where the next byte lies */
static size_t decode_terminate_message(TerminateMessage *record, const uint8_t *wire, size_t at) {
  record->termination_code = wire[at++];

  return at;
}

/* what was read of Terminate Message is what was written, byte for byte */
static void equal_terminate_message(const TerminateMessage *read, const TerminateMessage *written) {
  assert(read->termination_code == written->termination_code);
}

/* Terminate Message: written and read back, then read and written back */
static void check_terminate_message(void) {
  TerminateMessage sent;
  TerminateMessage got;
  uint8_t wire[1];
  uint8_t again[1];

  any_terminate_message(&sent);
  assert(encode_terminate_message(&sent, wire, 0) == 1);
  assert(decode_terminate_message(&got, wire, 0) == 1);
  equal_terminate_message(&got, &sent);

  for (size_t i = 0; i < 1; i++) { wire[i] = arbitrary(); }
  assert(decode_terminate_message(&got, wire, 0) == 1);
  assert(encode_terminate_message(&got, again, 0) == 1);
  for (size_t i = 0; i < 1; i++) { assert(again[i] == wire[i]); }
}

/* ---- Retransmit Request Message: 20 bytes ------------------------------------ */

/* RetransmitRequestMessage */
typedef struct {
  uint8_t timestamp[8];    /* bytes 0 to 7 */
  uint8_t from_seq_no[8];  /* bytes 8 to 15 */
  uint8_t count[4];        /* bytes 16 to 19 */
} RetransmitRequestMessage;

/* any Retransmit Request Message at all: every byte one the checker chooses */
static void any_retransmit_request_message(RetransmitRequestMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->from_seq_no[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->count[i] = arbitrary(); }
}

/* Retransmit Request Message to the wire: 20 bytes from at, returning where the next byte goes */
static size_t encode_retransmit_request_message(const RetransmitRequestMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->from_seq_no[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->count[i]; }

  return at;
}

/* Retransmit Request Message off the wire: 20 bytes from at, returning where the next byte lies */
static size_t decode_retransmit_request_message(RetransmitRequestMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->from_seq_no[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->count[i] = wire[at++]; }

  return at;
}

/* what was read of Retransmit Request Message is what was written, byte for byte */
static void equal_retransmit_request_message(const RetransmitRequestMessage *read, const RetransmitRequestMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->from_seq_no[i] == written->from_seq_no[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->count[i] == written->count[i]); }
}

/* Retransmit Request Message: written and read back, then read and written back */
static void check_retransmit_request_message(void) {
  RetransmitRequestMessage sent;
  RetransmitRequestMessage got;
  uint8_t wire[20];
  uint8_t again[20];

  any_retransmit_request_message(&sent);
  assert(encode_retransmit_request_message(&sent, wire, 0) == 20);
  assert(decode_retransmit_request_message(&got, wire, 0) == 20);
  equal_retransmit_request_message(&got, &sent);

  for (size_t i = 0; i < 20; i++) { wire[i] = arbitrary(); }
  assert(decode_retransmit_request_message(&got, wire, 0) == 20);
  assert(encode_retransmit_request_message(&got, again, 0) == 20);
  for (size_t i = 0; i < 20; i++) { assert(again[i] == wire[i]); }
}

/* ---- Sequence Message: 8 bytes ----------------------------------------------- */

/* SequenceMessage */
typedef struct {
  uint8_t next_seq_no[8];  /* bytes 0 to 7 */
} SequenceMessage;

/* any Sequence Message at all: every byte one the checker chooses */
static void any_sequence_message(SequenceMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->next_seq_no[i] = arbitrary(); }
}

/* Sequence Message to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_sequence_message(const SequenceMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->next_seq_no[i]; }

  return at;
}

/* Sequence Message off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_sequence_message(SequenceMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->next_seq_no[i] = wire[at++]; }

  return at;
}

/* what was read of Sequence Message is what was written, byte for byte */
static void equal_sequence_message(const SequenceMessage *read, const SequenceMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->next_seq_no[i] == written->next_seq_no[i]); }
}

/* Sequence Message: written and read back, then read and written back */
static void check_sequence_message(void) {
  SequenceMessage sent;
  SequenceMessage got;
  uint8_t wire[8];
  uint8_t again[8];

  any_sequence_message(&sent);
  assert(encode_sequence_message(&sent, wire, 0) == 8);
  assert(decode_sequence_message(&got, wire, 0) == 8);
  equal_sequence_message(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_sequence_message(&got, wire, 0) == 8);
  assert(encode_sequence_message(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Order Mass Cancel By Bf Limit Request Message: 15 bytes ----------------- */

/* OrderMassCancelByBFLimitRequestMessage */
typedef struct {
  uint8_t cl_ord_id[8];  /* bytes 0 to 7 */
  uint8_t account[7];    /* bytes 8 to 14 */
} OrderMassCancelByBfLimitRequestMessage;

/* any Order Mass Cancel By Bf Limit Request Message at all: every byte one the checker chooses */
static void any_order_mass_cancel_by_bf_limit_request_message(OrderMassCancelByBfLimitRequestMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->cl_ord_id[i] = arbitrary(); }
  for (size_t i = 0; i < 7; i++) { record->account[i] = arbitrary(); }
}

/* Order Mass Cancel By Bf Limit Request Message to the wire: 15 bytes from at, returning where the next byte goes */
static size_t encode_order_mass_cancel_by_bf_limit_request_message(const OrderMassCancelByBfLimitRequestMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->cl_ord_id[i]; }
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->account[i]; }

  return at;
}

/* Order Mass Cancel By Bf Limit Request Message off the wire: 15 bytes from at, returning where the next byte lies */
static size_t decode_order_mass_cancel_by_bf_limit_request_message(OrderMassCancelByBfLimitRequestMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->cl_ord_id[i] = wire[at++]; }
  for (size_t i = 0; i < 7; i++) { record->account[i] = wire[at++]; }

  return at;
}

/* what was read of Order Mass Cancel By Bf Limit Request Message is what was written, byte for byte */
static void equal_order_mass_cancel_by_bf_limit_request_message(const OrderMassCancelByBfLimitRequestMessage *read, const OrderMassCancelByBfLimitRequestMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->cl_ord_id[i] == written->cl_ord_id[i]); }
  for (size_t i = 0; i < 7; i++) { assert(read->account[i] == written->account[i]); }
}

/* Order Mass Cancel By Bf Limit Request Message: written and read back, then read and written back */
static void check_order_mass_cancel_by_bf_limit_request_message(void) {
  OrderMassCancelByBfLimitRequestMessage sent;
  OrderMassCancelByBfLimitRequestMessage got;
  uint8_t wire[15];
  uint8_t again[15];

  any_order_mass_cancel_by_bf_limit_request_message(&sent);
  assert(encode_order_mass_cancel_by_bf_limit_request_message(&sent, wire, 0) == 15);
  assert(decode_order_mass_cancel_by_bf_limit_request_message(&got, wire, 0) == 15);
  equal_order_mass_cancel_by_bf_limit_request_message(&got, &sent);

  for (size_t i = 0; i < 15; i++) { wire[i] = arbitrary(); }
  assert(decode_order_mass_cancel_by_bf_limit_request_message(&got, wire, 0) == 15);
  assert(encode_order_mass_cancel_by_bf_limit_request_message(&got, again, 0) == 15);
  for (size_t i = 0; i < 15; i++) { assert(again[i] == wire[i]); }
}

/* ---- What esbmc checks ------------------------------------------------------- */

/* every record of the protocol, each on its own buffers */
static void checks(void) {
  check_sbe_header();
  check_establish_message();
  check_terminate_message();
  check_retransmit_request_message();
  check_sequence_message();
  check_order_mass_cancel_by_bf_limit_request_message();
}

int main(void) {
#ifdef CONCRETE
  for (pattern = 0; pattern < 4; pattern++) { checks(); }
#else
  checks();
#endif

  return 0;
}
