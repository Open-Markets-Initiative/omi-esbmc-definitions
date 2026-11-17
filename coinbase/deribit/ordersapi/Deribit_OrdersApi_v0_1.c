// coinbase/deribit/ordersapi/Deribit_OrdersApi_v0_1.c
/*
 * Coinbase Orders Api
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
 *   - a field present only on a condition
 *   - a block whose stated length holds more than its fields
 *   - a run counted by a field
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

/* ---- Logon Message: 65 bytes ------------------------------------------------- */

/* LogonMessage */
typedef struct {
  uint8_t client_id[16];  /* bytes 0 to 15 */
  uint8_t secret[48];     /* bytes 16 to 63 */
  uint8_t reset_seq_num;  /* byte 64 */
} LogonMessage;

/* any Logon Message at all: every byte one the checker chooses */
static void any_logon_message(LogonMessage *record) {
  for (size_t i = 0; i < 16; i++) { record->client_id[i] = arbitrary(); }
  for (size_t i = 0; i < 48; i++) { record->secret[i] = arbitrary(); }
  record->reset_seq_num = arbitrary();
}

/* Logon Message to the wire: 65 bytes from at, returning where the next byte goes */
static size_t encode_logon_message(const LogonMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->client_id[i]; }
  for (size_t i = 0; i < 48; i++) { wire[at++] = record->secret[i]; }
  wire[at++] = record->reset_seq_num;

  return at;
}

/* Logon Message off the wire: 65 bytes from at, returning where the next byte lies */
static size_t decode_logon_message(LogonMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 16; i++) { record->client_id[i] = wire[at++]; }
  for (size_t i = 0; i < 48; i++) { record->secret[i] = wire[at++]; }
  record->reset_seq_num = wire[at++];

  return at;
}

/* what was read of Logon Message is what was written, byte for byte */
static void equal_logon_message(const LogonMessage *read, const LogonMessage *written) {
  for (size_t i = 0; i < 16; i++) { assert(read->client_id[i] == written->client_id[i]); }
  for (size_t i = 0; i < 48; i++) { assert(read->secret[i] == written->secret[i]); }
  assert(read->reset_seq_num == written->reset_seq_num);
}

/* Logon Message: written and read back, then read and written back */
static void check_logon_message(void) {
  LogonMessage sent;
  LogonMessage got;
  uint8_t wire[65];
  uint8_t again[65];

  any_logon_message(&sent);
  assert(encode_logon_message(&sent, wire, 0) == 65);
  assert(decode_logon_message(&got, wire, 0) == 65);
  equal_logon_message(&got, &sent);

  for (size_t i = 0; i < 65; i++) { wire[i] = arbitrary(); }
  assert(decode_logon_message(&got, wire, 0) == 65);
  assert(encode_logon_message(&got, again, 0) == 65);
  for (size_t i = 0; i < 65; i++) { assert(again[i] == wire[i]); }
}

/* ---- Logon Conf Message: 4 bytes --------------------------------------------- */

/* LogonConfMessage */
typedef struct {
  uint8_t heartbeat_interval_seconds[4];  /* bytes 0 to 3 */
} LogonConfMessage;

/* any Logon Conf Message at all: every byte one the checker chooses */
static void any_logon_conf_message(LogonConfMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->heartbeat_interval_seconds[i] = arbitrary(); }
}

/* Logon Conf Message to the wire: 4 bytes from at, returning where the next byte goes */
static size_t encode_logon_conf_message(const LogonConfMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->heartbeat_interval_seconds[i]; }

  return at;
}

/* Logon Conf Message off the wire: 4 bytes from at, returning where the next byte lies */
static size_t decode_logon_conf_message(LogonConfMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->heartbeat_interval_seconds[i] = wire[at++]; }

  return at;
}

/* what was read of Logon Conf Message is what was written, byte for byte */
static void equal_logon_conf_message(const LogonConfMessage *read, const LogonConfMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->heartbeat_interval_seconds[i] == written->heartbeat_interval_seconds[i]); }
}

/* Logon Conf Message: written and read back, then read and written back */
static void check_logon_conf_message(void) {
  LogonConfMessage sent;
  LogonConfMessage got;
  uint8_t wire[4];
  uint8_t again[4];

  any_logon_conf_message(&sent);
  assert(encode_logon_conf_message(&sent, wire, 0) == 4);
  assert(decode_logon_conf_message(&got, wire, 0) == 4);
  equal_logon_conf_message(&got, &sent);

  for (size_t i = 0; i < 4; i++) { wire[i] = arbitrary(); }
  assert(decode_logon_conf_message(&got, wire, 0) == 4);
  assert(encode_logon_conf_message(&got, again, 0) == 4);
  for (size_t i = 0; i < 4; i++) { assert(again[i] == wire[i]); }
}

/* ---- Heartbeat Message: 8 bytes ---------------------------------------------- */

/* HeartbeatMessage */
typedef struct {
  uint8_t correlation_id[8];  /* bytes 0 to 7 */
} HeartbeatMessage;

/* any Heartbeat Message at all: every byte one the checker chooses */
static void any_heartbeat_message(HeartbeatMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->correlation_id[i] = arbitrary(); }
}

/* Heartbeat Message to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_heartbeat_message(const HeartbeatMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->correlation_id[i]; }

  return at;
}

/* Heartbeat Message off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_heartbeat_message(HeartbeatMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->correlation_id[i] = wire[at++]; }

  return at;
}

/* what was read of Heartbeat Message is what was written, byte for byte */
static void equal_heartbeat_message(const HeartbeatMessage *read, const HeartbeatMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->correlation_id[i] == written->correlation_id[i]); }
}

/* Heartbeat Message: written and read back, then read and written back */
static void check_heartbeat_message(void) {
  HeartbeatMessage sent;
  HeartbeatMessage got;
  uint8_t wire[8];
  uint8_t again[8];

  any_heartbeat_message(&sent);
  assert(encode_heartbeat_message(&sent, wire, 0) == 8);
  assert(decode_heartbeat_message(&got, wire, 0) == 8);
  equal_heartbeat_message(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_heartbeat_message(&got, wire, 0) == 8);
  assert(encode_heartbeat_message(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Test Request Message: 8 bytes ------------------------------------------- */

/* TestRequestMessage */
typedef struct {
  uint8_t correlation_id[8];  /* bytes 0 to 7 */
} TestRequestMessage;

/* any Test Request Message at all: every byte one the checker chooses */
static void any_test_request_message(TestRequestMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->correlation_id[i] = arbitrary(); }
}

/* Test Request Message to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_test_request_message(const TestRequestMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->correlation_id[i]; }

  return at;
}

/* Test Request Message off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_test_request_message(TestRequestMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->correlation_id[i] = wire[at++]; }

  return at;
}

/* what was read of Test Request Message is what was written, byte for byte */
static void equal_test_request_message(const TestRequestMessage *read, const TestRequestMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->correlation_id[i] == written->correlation_id[i]); }
}

/* Test Request Message: written and read back, then read and written back */
static void check_test_request_message(void) {
  TestRequestMessage sent;
  TestRequestMessage got;
  uint8_t wire[8];
  uint8_t again[8];

  any_test_request_message(&sent);
  assert(encode_test_request_message(&sent, wire, 0) == 8);
  assert(decode_test_request_message(&got, wire, 0) == 8);
  equal_test_request_message(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_test_request_message(&got, wire, 0) == 8);
  assert(encode_test_request_message(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Resend Request Message: 16 bytes ---------------------------------------- */

/* ResendRequestMessage */
typedef struct {
  uint8_t from_sequence_number[8];  /* bytes 0 to 7 */
  uint8_t to_sequence_number[8];    /* bytes 8 to 15 */
} ResendRequestMessage;

/* any Resend Request Message at all: every byte one the checker chooses */
static void any_resend_request_message(ResendRequestMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->from_sequence_number[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->to_sequence_number[i] = arbitrary(); }
}

/* Resend Request Message to the wire: 16 bytes from at, returning where the next byte goes */
static size_t encode_resend_request_message(const ResendRequestMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->from_sequence_number[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->to_sequence_number[i]; }

  return at;
}

/* Resend Request Message off the wire: 16 bytes from at, returning where the next byte lies */
static size_t decode_resend_request_message(ResendRequestMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->from_sequence_number[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->to_sequence_number[i] = wire[at++]; }

  return at;
}

/* what was read of Resend Request Message is what was written, byte for byte */
static void equal_resend_request_message(const ResendRequestMessage *read, const ResendRequestMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->from_sequence_number[i] == written->from_sequence_number[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->to_sequence_number[i] == written->to_sequence_number[i]); }
}

/* Resend Request Message: written and read back, then read and written back */
static void check_resend_request_message(void) {
  ResendRequestMessage sent;
  ResendRequestMessage got;
  uint8_t wire[16];
  uint8_t again[16];

  any_resend_request_message(&sent);
  assert(encode_resend_request_message(&sent, wire, 0) == 16);
  assert(decode_resend_request_message(&got, wire, 0) == 16);
  equal_resend_request_message(&got, &sent);

  for (size_t i = 0; i < 16; i++) { wire[i] = arbitrary(); }
  assert(decode_resend_request_message(&got, wire, 0) == 16);
  assert(encode_resend_request_message(&got, again, 0) == 16);
  for (size_t i = 0; i < 16; i++) { assert(again[i] == wire[i]); }
}

/* ---- Gap Fill Message: 8 bytes ----------------------------------------------- */

/* GapFillMessage */
typedef struct {
  uint8_t new_sequence_number[8];  /* bytes 0 to 7 */
} GapFillMessage;

/* any Gap Fill Message at all: every byte one the checker chooses */
static void any_gap_fill_message(GapFillMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->new_sequence_number[i] = arbitrary(); }
}

/* Gap Fill Message to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_gap_fill_message(const GapFillMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->new_sequence_number[i]; }

  return at;
}

/* Gap Fill Message off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_gap_fill_message(GapFillMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->new_sequence_number[i] = wire[at++]; }

  return at;
}

/* what was read of Gap Fill Message is what was written, byte for byte */
static void equal_gap_fill_message(const GapFillMessage *read, const GapFillMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->new_sequence_number[i] == written->new_sequence_number[i]); }
}

/* Gap Fill Message: written and read back, then read and written back */
static void check_gap_fill_message(void) {
  GapFillMessage sent;
  GapFillMessage got;
  uint8_t wire[8];
  uint8_t again[8];

  any_gap_fill_message(&sent);
  assert(encode_gap_fill_message(&sent, wire, 0) == 8);
  assert(decode_gap_fill_message(&got, wire, 0) == 8);
  equal_gap_fill_message(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_gap_fill_message(&got, wire, 0) == 8);
  assert(encode_gap_fill_message(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Quantity: 9 bytes ------------------------------------------------------- */

/* NewOrderRequestMessage */
typedef struct {
  uint8_t mantissa[8];  /* bytes 0 to 7 */
  uint8_t exponent;     /* byte 8 */
} Quantity;

/* any Quantity at all: every byte one the checker chooses */
static void any_quantity(Quantity *record) {
  for (size_t i = 0; i < 8; i++) { record->mantissa[i] = arbitrary(); }
  record->exponent = arbitrary();
}

/* Quantity to the wire: 9 bytes from at, returning where the next byte goes */
static size_t encode_quantity(const Quantity *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->mantissa[i]; }
  wire[at++] = record->exponent;

  return at;
}

/* Quantity off the wire: 9 bytes from at, returning where the next byte lies */
static size_t decode_quantity(Quantity *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->mantissa[i] = wire[at++]; }
  record->exponent = wire[at++];

  return at;
}

/* what was read of Quantity is what was written, byte for byte */
static void equal_quantity(const Quantity *read, const Quantity *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->mantissa[i] == written->mantissa[i]); }
  assert(read->exponent == written->exponent);
}

/* Quantity: written and read back, then read and written back */
static void check_quantity(void) {
  Quantity sent;
  Quantity got;
  uint8_t wire[9];
  uint8_t again[9];

  any_quantity(&sent);
  assert(encode_quantity(&sent, wire, 0) == 9);
  assert(decode_quantity(&got, wire, 0) == 9);
  equal_quantity(&got, &sent);

  for (size_t i = 0; i < 9; i++) { wire[i] = arbitrary(); }
  assert(decode_quantity(&got, wire, 0) == 9);
  assert(encode_quantity(&got, again, 0) == 9);
  for (size_t i = 0; i < 9; i++) { assert(again[i] == wire[i]); }
}

/* ---- Show Qty: 9 bytes ------------------------------------------------------- */

/* NewOrderRequestMessage */
typedef struct {
  uint8_t mantissa_optional[8];  /* bytes 0 to 7 */
  uint8_t exponent;              /* byte 8 */
} ShowQty;

/* any Show Qty at all: every byte one the checker chooses */
static void any_show_qty(ShowQty *record) {
  for (size_t i = 0; i < 8; i++) { record->mantissa_optional[i] = arbitrary(); }
  record->exponent = arbitrary();
}

/* Show Qty to the wire: 9 bytes from at, returning where the next byte goes */
static size_t encode_show_qty(const ShowQty *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->mantissa_optional[i]; }
  wire[at++] = record->exponent;

  return at;
}

/* Show Qty off the wire: 9 bytes from at, returning where the next byte lies */
static size_t decode_show_qty(ShowQty *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->mantissa_optional[i] = wire[at++]; }
  record->exponent = wire[at++];

  return at;
}

/* what was read of Show Qty is what was written, byte for byte */
static void equal_show_qty(const ShowQty *read, const ShowQty *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->mantissa_optional[i] == written->mantissa_optional[i]); }
  assert(read->exponent == written->exponent);
}

/* Show Qty: written and read back, then read and written back */
static void check_show_qty(void) {
  ShowQty sent;
  ShowQty got;
  uint8_t wire[9];
  uint8_t again[9];

  any_show_qty(&sent);
  assert(encode_show_qty(&sent, wire, 0) == 9);
  assert(decode_show_qty(&got, wire, 0) == 9);
  equal_show_qty(&got, &sent);

  for (size_t i = 0; i < 9; i++) { wire[i] = arbitrary(); }
  assert(decode_show_qty(&got, wire, 0) == 9);
  assert(encode_show_qty(&got, again, 0) == 9);
  for (size_t i = 0; i < 9; i++) { assert(again[i] == wire[i]); }
}

/* ---- Cancel Order Request Message: 24 bytes ---------------------------------- */

/* CancelOrderRequestMessage */
typedef struct {
  uint8_t client_order_id[8];  /* bytes 0 to 7 */
  uint8_t correlation_id[8];   /* bytes 8 to 15 */
  uint8_t instrument_id[8];    /* bytes 16 to 23 */
} CancelOrderRequestMessage;

/* any Cancel Order Request Message at all: every byte one the checker chooses */
static void any_cancel_order_request_message(CancelOrderRequestMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->client_order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->correlation_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->instrument_id[i] = arbitrary(); }
}

/* Cancel Order Request Message to the wire: 24 bytes from at, returning where the next byte goes */
static size_t encode_cancel_order_request_message(const CancelOrderRequestMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->client_order_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->correlation_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->instrument_id[i]; }

  return at;
}

/* Cancel Order Request Message off the wire: 24 bytes from at, returning where the next byte lies */
static size_t decode_cancel_order_request_message(CancelOrderRequestMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->client_order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->correlation_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->instrument_id[i] = wire[at++]; }

  return at;
}

/* what was read of Cancel Order Request Message is what was written, byte for byte */
static void equal_cancel_order_request_message(const CancelOrderRequestMessage *read, const CancelOrderRequestMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->client_order_id[i] == written->client_order_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->correlation_id[i] == written->correlation_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->instrument_id[i] == written->instrument_id[i]); }
}

/* Cancel Order Request Message: written and read back, then read and written back */
static void check_cancel_order_request_message(void) {
  CancelOrderRequestMessage sent;
  CancelOrderRequestMessage got;
  uint8_t wire[24];
  uint8_t again[24];

  any_cancel_order_request_message(&sent);
  assert(encode_cancel_order_request_message(&sent, wire, 0) == 24);
  assert(decode_cancel_order_request_message(&got, wire, 0) == 24);
  equal_cancel_order_request_message(&got, &sent);

  for (size_t i = 0; i < 24; i++) { wire[i] = arbitrary(); }
  assert(decode_cancel_order_request_message(&got, wire, 0) == 24);
  assert(encode_cancel_order_request_message(&got, again, 0) == 24);
  for (size_t i = 0; i < 24; i++) { assert(again[i] == wire[i]); }
}

/* ---- Group Size Encoding: 4 bytes -------------------------------------------- */

/* groupSizeEncoding */
typedef struct {
  uint8_t block_length[2];  /* bytes 0 to 1 */
  uint8_t num_in_group[2];  /* bytes 2 to 3 */
} GroupSizeEncoding;

/* any Group Size Encoding at all: every byte one the checker chooses */
static void any_group_size_encoding(GroupSizeEncoding *record) {
  for (size_t i = 0; i < 2; i++) { record->block_length[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->num_in_group[i] = arbitrary(); }
}

/* Group Size Encoding to the wire: 4 bytes from at, returning where the next byte goes */
static size_t encode_group_size_encoding(const GroupSizeEncoding *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->block_length[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->num_in_group[i]; }

  return at;
}

/* Group Size Encoding off the wire: 4 bytes from at, returning where the next byte lies */
static size_t decode_group_size_encoding(GroupSizeEncoding *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->block_length[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->num_in_group[i] = wire[at++]; }

  return at;
}

/* what was read of Group Size Encoding is what was written, byte for byte */
static void equal_group_size_encoding(const GroupSizeEncoding *read, const GroupSizeEncoding *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->block_length[i] == written->block_length[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->num_in_group[i] == written->num_in_group[i]); }
}

/* Group Size Encoding: written and read back, then read and written back */
static void check_group_size_encoding(void) {
  GroupSizeEncoding sent;
  GroupSizeEncoding got;
  uint8_t wire[4];
  uint8_t again[4];

  any_group_size_encoding(&sent);
  assert(encode_group_size_encoding(&sent, wire, 0) == 4);
  assert(decode_group_size_encoding(&got, wire, 0) == 4);
  equal_group_size_encoding(&got, &sent);

  for (size_t i = 0; i < 4; i++) { wire[i] = arbitrary(); }
  assert(decode_group_size_encoding(&got, wire, 0) == 4);
  assert(encode_group_size_encoding(&got, again, 0) == 4);
  for (size_t i = 0; i < 4; i++) { assert(again[i] == wire[i]); }
}

/* ---- Bid Qty: 9 bytes -------------------------------------------------------- */

/* quotes */
typedef struct {
  uint8_t mantissa[8];  /* bytes 0 to 7 */
  uint8_t exponent;     /* byte 8 */
} BidQty;

/* any Bid Qty at all: every byte one the checker chooses */
static void any_bid_qty(BidQty *record) {
  for (size_t i = 0; i < 8; i++) { record->mantissa[i] = arbitrary(); }
  record->exponent = arbitrary();
}

/* Bid Qty to the wire: 9 bytes from at, returning where the next byte goes */
static size_t encode_bid_qty(const BidQty *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->mantissa[i]; }
  wire[at++] = record->exponent;

  return at;
}

/* Bid Qty off the wire: 9 bytes from at, returning where the next byte lies */
static size_t decode_bid_qty(BidQty *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->mantissa[i] = wire[at++]; }
  record->exponent = wire[at++];

  return at;
}

/* what was read of Bid Qty is what was written, byte for byte */
static void equal_bid_qty(const BidQty *read, const BidQty *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->mantissa[i] == written->mantissa[i]); }
  assert(read->exponent == written->exponent);
}

/* Bid Qty: written and read back, then read and written back */
static void check_bid_qty(void) {
  BidQty sent;
  BidQty got;
  uint8_t wire[9];
  uint8_t again[9];

  any_bid_qty(&sent);
  assert(encode_bid_qty(&sent, wire, 0) == 9);
  assert(decode_bid_qty(&got, wire, 0) == 9);
  equal_bid_qty(&got, &sent);

  for (size_t i = 0; i < 9; i++) { wire[i] = arbitrary(); }
  assert(decode_bid_qty(&got, wire, 0) == 9);
  assert(encode_bid_qty(&got, again, 0) == 9);
  for (size_t i = 0; i < 9; i++) { assert(again[i] == wire[i]); }
}

/* ---- Ask Qty: 9 bytes -------------------------------------------------------- */

/* quotes */
typedef struct {
  uint8_t mantissa[8];  /* bytes 0 to 7 */
  uint8_t exponent;     /* byte 8 */
} AskQty;

/* any Ask Qty at all: every byte one the checker chooses */
static void any_ask_qty(AskQty *record) {
  for (size_t i = 0; i < 8; i++) { record->mantissa[i] = arbitrary(); }
  record->exponent = arbitrary();
}

/* Ask Qty to the wire: 9 bytes from at, returning where the next byte goes */
static size_t encode_ask_qty(const AskQty *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->mantissa[i]; }
  wire[at++] = record->exponent;

  return at;
}

/* Ask Qty off the wire: 9 bytes from at, returning where the next byte lies */
static size_t decode_ask_qty(AskQty *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->mantissa[i] = wire[at++]; }
  record->exponent = wire[at++];

  return at;
}

/* what was read of Ask Qty is what was written, byte for byte */
static void equal_ask_qty(const AskQty *read, const AskQty *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->mantissa[i] == written->mantissa[i]); }
  assert(read->exponent == written->exponent);
}

/* Ask Qty: written and read back, then read and written back */
static void check_ask_qty(void) {
  AskQty sent;
  AskQty got;
  uint8_t wire[9];
  uint8_t again[9];

  any_ask_qty(&sent);
  assert(encode_ask_qty(&sent, wire, 0) == 9);
  assert(decode_ask_qty(&got, wire, 0) == 9);
  equal_ask_qty(&got, &sent);

  for (size_t i = 0; i < 9; i++) { wire[i] = arbitrary(); }
  assert(decode_ask_qty(&got, wire, 0) == 9);
  assert(encode_ask_qty(&got, again, 0) == 9);
  for (size_t i = 0; i < 9; i++) { assert(again[i] == wire[i]); }
}

/* ---- Mass Cancel Request Message: 26 bytes ----------------------------------- */

/* MassCancelRequestMessage */
typedef struct {
  uint8_t correlation_id[8];          /* bytes 0 to 7 */
  uint8_t currency_pair_id[8];        /* bytes 8 to 15 */
  uint8_t instrument_id_optional[8];  /* bytes 16 to 23 */
  uint8_t product_type;               /* byte 24 */
  uint8_t side;                       /* byte 25 */
} MassCancelRequestMessage;

/* any Mass Cancel Request Message at all: every byte one the checker chooses */
static void any_mass_cancel_request_message(MassCancelRequestMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->correlation_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->currency_pair_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->instrument_id_optional[i] = arbitrary(); }
  record->product_type = arbitrary();
  record->side = arbitrary();
}

/* Mass Cancel Request Message to the wire: 26 bytes from at, returning where the next byte goes */
static size_t encode_mass_cancel_request_message(const MassCancelRequestMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->correlation_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->currency_pair_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->instrument_id_optional[i]; }
  wire[at++] = record->product_type;
  wire[at++] = record->side;

  return at;
}

/* Mass Cancel Request Message off the wire: 26 bytes from at, returning where the next byte lies */
static size_t decode_mass_cancel_request_message(MassCancelRequestMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->correlation_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->currency_pair_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->instrument_id_optional[i] = wire[at++]; }
  record->product_type = wire[at++];
  record->side = wire[at++];

  return at;
}

/* what was read of Mass Cancel Request Message is what was written, byte for byte */
static void equal_mass_cancel_request_message(const MassCancelRequestMessage *read, const MassCancelRequestMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->correlation_id[i] == written->correlation_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->currency_pair_id[i] == written->currency_pair_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->instrument_id_optional[i] == written->instrument_id_optional[i]); }
  assert(read->product_type == written->product_type);
  assert(read->side == written->side);
}

/* Mass Cancel Request Message: written and read back, then read and written back */
static void check_mass_cancel_request_message(void) {
  MassCancelRequestMessage sent;
  MassCancelRequestMessage got;
  uint8_t wire[26];
  uint8_t again[26];

  any_mass_cancel_request_message(&sent);
  assert(encode_mass_cancel_request_message(&sent, wire, 0) == 26);
  assert(decode_mass_cancel_request_message(&got, wire, 0) == 26);
  equal_mass_cancel_request_message(&got, &sent);

  for (size_t i = 0; i < 26; i++) { wire[i] = arbitrary(); }
  assert(decode_mass_cancel_request_message(&got, wire, 0) == 26);
  assert(encode_mass_cancel_request_message(&got, again, 0) == 26);
  for (size_t i = 0; i < 26; i++) { assert(again[i] == wire[i]); }
}

/* ---- Mass Quote Cancel Request Message: 17 bytes ----------------------------- */

/* MassQuoteCancelRequestMessage */
typedef struct {
  uint8_t correlation_id[8];  /* bytes 0 to 7 */
  uint8_t mmp_group_id[8];    /* bytes 8 to 15 */
  uint8_t side;               /* byte 16 */
} MassQuoteCancelRequestMessage;

/* any Mass Quote Cancel Request Message at all: every byte one the checker chooses */
static void any_mass_quote_cancel_request_message(MassQuoteCancelRequestMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->correlation_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->mmp_group_id[i] = arbitrary(); }
  record->side = arbitrary();
}

/* Mass Quote Cancel Request Message to the wire: 17 bytes from at, returning where the next byte goes */
static size_t encode_mass_quote_cancel_request_message(const MassQuoteCancelRequestMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->correlation_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->mmp_group_id[i]; }
  wire[at++] = record->side;

  return at;
}

/* Mass Quote Cancel Request Message off the wire: 17 bytes from at, returning where the next byte lies */
static size_t decode_mass_quote_cancel_request_message(MassQuoteCancelRequestMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->correlation_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->mmp_group_id[i] = wire[at++]; }
  record->side = wire[at++];

  return at;
}

/* what was read of Mass Quote Cancel Request Message is what was written, byte for byte */
static void equal_mass_quote_cancel_request_message(const MassQuoteCancelRequestMessage *read, const MassQuoteCancelRequestMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->correlation_id[i] == written->correlation_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->mmp_group_id[i] == written->mmp_group_id[i]); }
  assert(read->side == written->side);
}

/* Mass Quote Cancel Request Message: written and read back, then read and written back */
static void check_mass_quote_cancel_request_message(void) {
  MassQuoteCancelRequestMessage sent;
  MassQuoteCancelRequestMessage got;
  uint8_t wire[17];
  uint8_t again[17];

  any_mass_quote_cancel_request_message(&sent);
  assert(encode_mass_quote_cancel_request_message(&sent, wire, 0) == 17);
  assert(decode_mass_quote_cancel_request_message(&got, wire, 0) == 17);
  equal_mass_quote_cancel_request_message(&got, &sent);

  for (size_t i = 0; i < 17; i++) { wire[i] = arbitrary(); }
  assert(decode_mass_quote_cancel_request_message(&got, wire, 0) == 17);
  assert(encode_mass_quote_cancel_request_message(&got, again, 0) == 17);
  for (size_t i = 0; i < 17; i++) { assert(again[i] == wire[i]); }
}

/* ---- Total Filled: 9 bytes --------------------------------------------------- */

/* NewOrderResponseMessage */
typedef struct {
  uint8_t mantissa[8];  /* bytes 0 to 7 */
  uint8_t exponent;     /* byte 8 */
} TotalFilled;

/* any Total Filled at all: every byte one the checker chooses */
static void any_total_filled(TotalFilled *record) {
  for (size_t i = 0; i < 8; i++) { record->mantissa[i] = arbitrary(); }
  record->exponent = arbitrary();
}

/* Total Filled to the wire: 9 bytes from at, returning where the next byte goes */
static size_t encode_total_filled(const TotalFilled *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->mantissa[i]; }
  wire[at++] = record->exponent;

  return at;
}

/* Total Filled off the wire: 9 bytes from at, returning where the next byte lies */
static size_t decode_total_filled(TotalFilled *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->mantissa[i] = wire[at++]; }
  record->exponent = wire[at++];

  return at;
}

/* what was read of Total Filled is what was written, byte for byte */
static void equal_total_filled(const TotalFilled *read, const TotalFilled *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->mantissa[i] == written->mantissa[i]); }
  assert(read->exponent == written->exponent);
}

/* Total Filled: written and read back, then read and written back */
static void check_total_filled(void) {
  TotalFilled sent;
  TotalFilled got;
  uint8_t wire[9];
  uint8_t again[9];

  any_total_filled(&sent);
  assert(encode_total_filled(&sent, wire, 0) == 9);
  assert(decode_total_filled(&got, wire, 0) == 9);
  equal_total_filled(&got, &sent);

  for (size_t i = 0; i < 9; i++) { wire[i] = arbitrary(); }
  assert(decode_total_filled(&got, wire, 0) == 9);
  assert(encode_total_filled(&got, again, 0) == 9);
  for (size_t i = 0; i < 9; i++) { assert(again[i] == wire[i]); }
}

/* ---- Visible Qty: 9 bytes ---------------------------------------------------- */

/* NewOrderResponseMessage */
typedef struct {
  uint8_t mantissa[8];  /* bytes 0 to 7 */
  uint8_t exponent;     /* byte 8 */
} VisibleQty;

/* any Visible Qty at all: every byte one the checker chooses */
static void any_visible_qty(VisibleQty *record) {
  for (size_t i = 0; i < 8; i++) { record->mantissa[i] = arbitrary(); }
  record->exponent = arbitrary();
}

/* Visible Qty to the wire: 9 bytes from at, returning where the next byte goes */
static size_t encode_visible_qty(const VisibleQty *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->mantissa[i]; }
  wire[at++] = record->exponent;

  return at;
}

/* Visible Qty off the wire: 9 bytes from at, returning where the next byte lies */
static size_t decode_visible_qty(VisibleQty *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->mantissa[i] = wire[at++]; }
  record->exponent = wire[at++];

  return at;
}

/* what was read of Visible Qty is what was written, byte for byte */
static void equal_visible_qty(const VisibleQty *read, const VisibleQty *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->mantissa[i] == written->mantissa[i]); }
  assert(read->exponent == written->exponent);
}

/* Visible Qty: written and read back, then read and written back */
static void check_visible_qty(void) {
  VisibleQty sent;
  VisibleQty got;
  uint8_t wire[9];
  uint8_t again[9];

  any_visible_qty(&sent);
  assert(encode_visible_qty(&sent, wire, 0) == 9);
  assert(decode_visible_qty(&got, wire, 0) == 9);
  equal_visible_qty(&got, &sent);

  for (size_t i = 0; i < 9; i++) { wire[i] = arbitrary(); }
  assert(decode_visible_qty(&got, wire, 0) == 9);
  assert(encode_visible_qty(&got, again, 0) == 9);
  for (size_t i = 0; i < 9; i++) { assert(again[i] == wire[i]); }
}

/* ---- Fill Qty: 9 bytes ------------------------------------------------------- */

/* fills */
typedef struct {
  uint8_t mantissa[8];  /* bytes 0 to 7 */
  uint8_t exponent;     /* byte 8 */
} FillQty;

/* any Fill Qty at all: every byte one the checker chooses */
static void any_fill_qty(FillQty *record) {
  for (size_t i = 0; i < 8; i++) { record->mantissa[i] = arbitrary(); }
  record->exponent = arbitrary();
}

/* Fill Qty to the wire: 9 bytes from at, returning where the next byte goes */
static size_t encode_fill_qty(const FillQty *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->mantissa[i]; }
  wire[at++] = record->exponent;

  return at;
}

/* Fill Qty off the wire: 9 bytes from at, returning where the next byte lies */
static size_t decode_fill_qty(FillQty *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->mantissa[i] = wire[at++]; }
  record->exponent = wire[at++];

  return at;
}

/* what was read of Fill Qty is what was written, byte for byte */
static void equal_fill_qty(const FillQty *read, const FillQty *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->mantissa[i] == written->mantissa[i]); }
  assert(read->exponent == written->exponent);
}

/* Fill Qty: written and read back, then read and written back */
static void check_fill_qty(void) {
  FillQty sent;
  FillQty got;
  uint8_t wire[9];
  uint8_t again[9];

  any_fill_qty(&sent);
  assert(encode_fill_qty(&sent, wire, 0) == 9);
  assert(decode_fill_qty(&got, wire, 0) == 9);
  equal_fill_qty(&got, &sent);

  for (size_t i = 0; i < 9; i++) { wire[i] = arbitrary(); }
  assert(decode_fill_qty(&got, wire, 0) == 9);
  assert(encode_fill_qty(&got, again, 0) == 9);
  for (size_t i = 0; i < 9; i++) { assert(again[i] == wire[i]); }
}

/* ---- Cancel Order Response Message: 56 bytes --------------------------------- */

/* CancelOrderResponseMessage */
typedef struct {
  uint8_t timestamp[8];        /* bytes 0 to 7 */
  uint8_t exec_id[8];          /* bytes 8 to 15 */
  uint8_t client_order_id[8];  /* bytes 16 to 23 */
  uint8_t correlation_id[8];   /* bytes 24 to 31 */
  uint8_t order_id[8];         /* bytes 32 to 39 */
  uint8_t instrument_id[8];    /* bytes 40 to 47 */
  uint8_t receive_time[8];     /* bytes 48 to 55 */
} CancelOrderResponseMessage;

/* any Cancel Order Response Message at all: every byte one the checker chooses */
static void any_cancel_order_response_message(CancelOrderResponseMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->exec_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->client_order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->correlation_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->instrument_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->receive_time[i] = arbitrary(); }
}

/* Cancel Order Response Message to the wire: 56 bytes from at, returning where the next byte goes */
static size_t encode_cancel_order_response_message(const CancelOrderResponseMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->exec_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->client_order_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->correlation_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->instrument_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->receive_time[i]; }

  return at;
}

/* Cancel Order Response Message off the wire: 56 bytes from at, returning where the next byte lies */
static size_t decode_cancel_order_response_message(CancelOrderResponseMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->exec_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->client_order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->correlation_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->instrument_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->receive_time[i] = wire[at++]; }

  return at;
}

/* what was read of Cancel Order Response Message is what was written, byte for byte */
static void equal_cancel_order_response_message(const CancelOrderResponseMessage *read, const CancelOrderResponseMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->exec_id[i] == written->exec_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->client_order_id[i] == written->client_order_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->correlation_id[i] == written->correlation_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->order_id[i] == written->order_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->instrument_id[i] == written->instrument_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->receive_time[i] == written->receive_time[i]); }
}

/* Cancel Order Response Message: written and read back, then read and written back */
static void check_cancel_order_response_message(void) {
  CancelOrderResponseMessage sent;
  CancelOrderResponseMessage got;
  uint8_t wire[56];
  uint8_t again[56];

  any_cancel_order_response_message(&sent);
  assert(encode_cancel_order_response_message(&sent, wire, 0) == 56);
  assert(decode_cancel_order_response_message(&got, wire, 0) == 56);
  equal_cancel_order_response_message(&got, &sent);

  for (size_t i = 0; i < 56; i++) { wire[i] = arbitrary(); }
  assert(decode_cancel_order_response_message(&got, wire, 0) == 56);
  assert(encode_cancel_order_response_message(&got, again, 0) == 56);
  for (size_t i = 0; i < 56; i++) { assert(again[i] == wire[i]); }
}

/* ---- Bid Filled Qty: 9 bytes ------------------------------------------------- */

/* quotes */
typedef struct {
  uint8_t mantissa[8];  /* bytes 0 to 7 */
  uint8_t exponent;     /* byte 8 */
} BidFilledQty;

/* any Bid Filled Qty at all: every byte one the checker chooses */
static void any_bid_filled_qty(BidFilledQty *record) {
  for (size_t i = 0; i < 8; i++) { record->mantissa[i] = arbitrary(); }
  record->exponent = arbitrary();
}

/* Bid Filled Qty to the wire: 9 bytes from at, returning where the next byte goes */
static size_t encode_bid_filled_qty(const BidFilledQty *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->mantissa[i]; }
  wire[at++] = record->exponent;

  return at;
}

/* Bid Filled Qty off the wire: 9 bytes from at, returning where the next byte lies */
static size_t decode_bid_filled_qty(BidFilledQty *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->mantissa[i] = wire[at++]; }
  record->exponent = wire[at++];

  return at;
}

/* what was read of Bid Filled Qty is what was written, byte for byte */
static void equal_bid_filled_qty(const BidFilledQty *read, const BidFilledQty *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->mantissa[i] == written->mantissa[i]); }
  assert(read->exponent == written->exponent);
}

/* Bid Filled Qty: written and read back, then read and written back */
static void check_bid_filled_qty(void) {
  BidFilledQty sent;
  BidFilledQty got;
  uint8_t wire[9];
  uint8_t again[9];

  any_bid_filled_qty(&sent);
  assert(encode_bid_filled_qty(&sent, wire, 0) == 9);
  assert(decode_bid_filled_qty(&got, wire, 0) == 9);
  equal_bid_filled_qty(&got, &sent);

  for (size_t i = 0; i < 9; i++) { wire[i] = arbitrary(); }
  assert(decode_bid_filled_qty(&got, wire, 0) == 9);
  assert(encode_bid_filled_qty(&got, again, 0) == 9);
  for (size_t i = 0; i < 9; i++) { assert(again[i] == wire[i]); }
}

/* ---- Ask Filled Qty: 9 bytes ------------------------------------------------- */

/* quotes */
typedef struct {
  uint8_t mantissa[8];  /* bytes 0 to 7 */
  uint8_t exponent;     /* byte 8 */
} AskFilledQty;

/* any Ask Filled Qty at all: every byte one the checker chooses */
static void any_ask_filled_qty(AskFilledQty *record) {
  for (size_t i = 0; i < 8; i++) { record->mantissa[i] = arbitrary(); }
  record->exponent = arbitrary();
}

/* Ask Filled Qty to the wire: 9 bytes from at, returning where the next byte goes */
static size_t encode_ask_filled_qty(const AskFilledQty *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->mantissa[i]; }
  wire[at++] = record->exponent;

  return at;
}

/* Ask Filled Qty off the wire: 9 bytes from at, returning where the next byte lies */
static size_t decode_ask_filled_qty(AskFilledQty *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->mantissa[i] = wire[at++]; }
  record->exponent = wire[at++];

  return at;
}

/* what was read of Ask Filled Qty is what was written, byte for byte */
static void equal_ask_filled_qty(const AskFilledQty *read, const AskFilledQty *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->mantissa[i] == written->mantissa[i]); }
  assert(read->exponent == written->exponent);
}

/* Ask Filled Qty: written and read back, then read and written back */
static void check_ask_filled_qty(void) {
  AskFilledQty sent;
  AskFilledQty got;
  uint8_t wire[9];
  uint8_t again[9];

  any_ask_filled_qty(&sent);
  assert(encode_ask_filled_qty(&sent, wire, 0) == 9);
  assert(decode_ask_filled_qty(&got, wire, 0) == 9);
  equal_ask_filled_qty(&got, &sent);

  for (size_t i = 0; i < 9; i++) { wire[i] = arbitrary(); }
  assert(decode_ask_filled_qty(&got, wire, 0) == 9);
  assert(encode_ask_filled_qty(&got, again, 0) == 9);
  for (size_t i = 0; i < 9; i++) { assert(again[i] == wire[i]); }
}

/* ---- Mass Cancel Response Message: 36 bytes ---------------------------------- */

/* MassCancelResponseMessage */
typedef struct {
  uint8_t timestamp[8];          /* bytes 0 to 7 */
  uint8_t exec_id[8];            /* bytes 8 to 15 */
  uint8_t correlation_id[8];     /* bytes 16 to 23 */
  uint8_t receive_time[8];       /* bytes 24 to 31 */
  uint8_t total_order_count[4];  /* bytes 32 to 35 */
} MassCancelResponseMessage;

/* any Mass Cancel Response Message at all: every byte one the checker chooses */
static void any_mass_cancel_response_message(MassCancelResponseMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->exec_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->correlation_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->receive_time[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->total_order_count[i] = arbitrary(); }
}

/* Mass Cancel Response Message to the wire: 36 bytes from at, returning where the next byte goes */
static size_t encode_mass_cancel_response_message(const MassCancelResponseMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->exec_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->correlation_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->receive_time[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->total_order_count[i]; }

  return at;
}

/* Mass Cancel Response Message off the wire: 36 bytes from at, returning where the next byte lies */
static size_t decode_mass_cancel_response_message(MassCancelResponseMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->exec_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->correlation_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->receive_time[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->total_order_count[i] = wire[at++]; }

  return at;
}

/* what was read of Mass Cancel Response Message is what was written, byte for byte */
static void equal_mass_cancel_response_message(const MassCancelResponseMessage *read, const MassCancelResponseMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->exec_id[i] == written->exec_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->correlation_id[i] == written->correlation_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->receive_time[i] == written->receive_time[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->total_order_count[i] == written->total_order_count[i]); }
}

/* Mass Cancel Response Message: written and read back, then read and written back */
static void check_mass_cancel_response_message(void) {
  MassCancelResponseMessage sent;
  MassCancelResponseMessage got;
  uint8_t wire[36];
  uint8_t again[36];

  any_mass_cancel_response_message(&sent);
  assert(encode_mass_cancel_response_message(&sent, wire, 0) == 36);
  assert(decode_mass_cancel_response_message(&got, wire, 0) == 36);
  equal_mass_cancel_response_message(&got, &sent);

  for (size_t i = 0; i < 36; i++) { wire[i] = arbitrary(); }
  assert(decode_mass_cancel_response_message(&got, wire, 0) == 36);
  assert(encode_mass_cancel_response_message(&got, again, 0) == 36);
  for (size_t i = 0; i < 36; i++) { assert(again[i] == wire[i]); }
}

/* ---- Mass Quote Mmp Triggered Message: 57 bytes ------------------------------ */

/* MassQuoteMmpTriggeredMessage */
typedef struct {
  uint8_t timestamp[8];       /* bytes 0 to 7 */
  uint8_t exec_id[8];         /* bytes 8 to 15 */
  uint8_t mmp_group_id[8];    /* bytes 16 to 23 */
  uint8_t frozen_until[8];    /* bytes 24 to 31 */
  uint8_t quantity_level[8];  /* bytes 32 to 39 */
  uint8_t vega_level[8];      /* bytes 40 to 47 */
  uint8_t delta_level[8];     /* bytes 48 to 55 */
  uint8_t trigger;            /* byte 56 */
} MassQuoteMmpTriggeredMessage;

/* any Mass Quote Mmp Triggered Message at all: every byte one the checker chooses */
static void any_mass_quote_mmp_triggered_message(MassQuoteMmpTriggeredMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->exec_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->mmp_group_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->frozen_until[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->quantity_level[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->vega_level[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->delta_level[i] = arbitrary(); }
  record->trigger = arbitrary();
}

/* Mass Quote Mmp Triggered Message to the wire: 57 bytes from at, returning where the next byte goes */
static size_t encode_mass_quote_mmp_triggered_message(const MassQuoteMmpTriggeredMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->exec_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->mmp_group_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->frozen_until[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->quantity_level[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->vega_level[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->delta_level[i]; }
  wire[at++] = record->trigger;

  return at;
}

/* Mass Quote Mmp Triggered Message off the wire: 57 bytes from at, returning where the next byte lies */
static size_t decode_mass_quote_mmp_triggered_message(MassQuoteMmpTriggeredMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->exec_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->mmp_group_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->frozen_until[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->quantity_level[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->vega_level[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->delta_level[i] = wire[at++]; }
  record->trigger = wire[at++];

  return at;
}

/* what was read of Mass Quote Mmp Triggered Message is what was written, byte for byte */
static void equal_mass_quote_mmp_triggered_message(const MassQuoteMmpTriggeredMessage *read, const MassQuoteMmpTriggeredMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->exec_id[i] == written->exec_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->mmp_group_id[i] == written->mmp_group_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->frozen_until[i] == written->frozen_until[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->quantity_level[i] == written->quantity_level[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->vega_level[i] == written->vega_level[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->delta_level[i] == written->delta_level[i]); }
  assert(read->trigger == written->trigger);
}

/* Mass Quote Mmp Triggered Message: written and read back, then read and written back */
static void check_mass_quote_mmp_triggered_message(void) {
  MassQuoteMmpTriggeredMessage sent;
  MassQuoteMmpTriggeredMessage got;
  uint8_t wire[57];
  uint8_t again[57];

  any_mass_quote_mmp_triggered_message(&sent);
  assert(encode_mass_quote_mmp_triggered_message(&sent, wire, 0) == 57);
  assert(decode_mass_quote_mmp_triggered_message(&got, wire, 0) == 57);
  equal_mass_quote_mmp_triggered_message(&got, &sent);

  for (size_t i = 0; i < 57; i++) { wire[i] = arbitrary(); }
  assert(decode_mass_quote_mmp_triggered_message(&got, wire, 0) == 57);
  assert(encode_mass_quote_mmp_triggered_message(&got, again, 0) == 57);
  for (size_t i = 0; i < 57; i++) { assert(again[i] == wire[i]); }
}

/* ---- Orders Mmp Triggered Message: 57 bytes ---------------------------------- */

/* OrdersMmpTriggeredMessage */
typedef struct {
  uint8_t timestamp[8];         /* bytes 0 to 7 */
  uint8_t exec_id[8];           /* bytes 8 to 15 */
  uint8_t currency_pair_id[8];  /* bytes 16 to 23 */
  uint8_t frozen_until[8];      /* bytes 24 to 31 */
  uint8_t quantity_level[8];    /* bytes 32 to 39 */
  uint8_t vega_level[8];        /* bytes 40 to 47 */
  uint8_t delta_level[8];       /* bytes 48 to 55 */
  uint8_t trigger;              /* byte 56 */
} OrdersMmpTriggeredMessage;

/* any Orders Mmp Triggered Message at all: every byte one the checker chooses */
static void any_orders_mmp_triggered_message(OrdersMmpTriggeredMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->exec_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->currency_pair_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->frozen_until[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->quantity_level[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->vega_level[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->delta_level[i] = arbitrary(); }
  record->trigger = arbitrary();
}

/* Orders Mmp Triggered Message to the wire: 57 bytes from at, returning where the next byte goes */
static size_t encode_orders_mmp_triggered_message(const OrdersMmpTriggeredMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->exec_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->currency_pair_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->frozen_until[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->quantity_level[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->vega_level[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->delta_level[i]; }
  wire[at++] = record->trigger;

  return at;
}

/* Orders Mmp Triggered Message off the wire: 57 bytes from at, returning where the next byte lies */
static size_t decode_orders_mmp_triggered_message(OrdersMmpTriggeredMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->exec_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->currency_pair_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->frozen_until[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->quantity_level[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->vega_level[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->delta_level[i] = wire[at++]; }
  record->trigger = wire[at++];

  return at;
}

/* what was read of Orders Mmp Triggered Message is what was written, byte for byte */
static void equal_orders_mmp_triggered_message(const OrdersMmpTriggeredMessage *read, const OrdersMmpTriggeredMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->exec_id[i] == written->exec_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->currency_pair_id[i] == written->currency_pair_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->frozen_until[i] == written->frozen_until[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->quantity_level[i] == written->quantity_level[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->vega_level[i] == written->vega_level[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->delta_level[i] == written->delta_level[i]); }
  assert(read->trigger == written->trigger);
}

/* Orders Mmp Triggered Message: written and read back, then read and written back */
static void check_orders_mmp_triggered_message(void) {
  OrdersMmpTriggeredMessage sent;
  OrdersMmpTriggeredMessage got;
  uint8_t wire[57];
  uint8_t again[57];

  any_orders_mmp_triggered_message(&sent);
  assert(encode_orders_mmp_triggered_message(&sent, wire, 0) == 57);
  assert(decode_orders_mmp_triggered_message(&got, wire, 0) == 57);
  equal_orders_mmp_triggered_message(&got, &sent);

  for (size_t i = 0; i < 57; i++) { wire[i] = arbitrary(); }
  assert(decode_orders_mmp_triggered_message(&got, wire, 0) == 57);
  assert(encode_orders_mmp_triggered_message(&got, again, 0) == 57);
  for (size_t i = 0; i < 57; i++) { assert(again[i] == wire[i]); }
}

/* ---- Mass Quote Mmp Unfrozen Message: 32 bytes ------------------------------- */

/* MassQuoteMmpUnfrozenMessage */
typedef struct {
  uint8_t timestamp[8];                /* bytes 0 to 7 */
  uint8_t exec_id[8];                  /* bytes 8 to 15 */
  uint8_t mmp_group_id[8];             /* bytes 16 to 23 */
  uint8_t correlation_id_optional[8];  /* bytes 24 to 31 */
} MassQuoteMmpUnfrozenMessage;

/* any Mass Quote Mmp Unfrozen Message at all: every byte one the checker chooses */
static void any_mass_quote_mmp_unfrozen_message(MassQuoteMmpUnfrozenMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->exec_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->mmp_group_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->correlation_id_optional[i] = arbitrary(); }
}

/* Mass Quote Mmp Unfrozen Message to the wire: 32 bytes from at, returning where the next byte goes */
static size_t encode_mass_quote_mmp_unfrozen_message(const MassQuoteMmpUnfrozenMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->exec_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->mmp_group_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->correlation_id_optional[i]; }

  return at;
}

/* Mass Quote Mmp Unfrozen Message off the wire: 32 bytes from at, returning where the next byte lies */
static size_t decode_mass_quote_mmp_unfrozen_message(MassQuoteMmpUnfrozenMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->exec_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->mmp_group_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->correlation_id_optional[i] = wire[at++]; }

  return at;
}

/* what was read of Mass Quote Mmp Unfrozen Message is what was written, byte for byte */
static void equal_mass_quote_mmp_unfrozen_message(const MassQuoteMmpUnfrozenMessage *read, const MassQuoteMmpUnfrozenMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->exec_id[i] == written->exec_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->mmp_group_id[i] == written->mmp_group_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->correlation_id_optional[i] == written->correlation_id_optional[i]); }
}

/* Mass Quote Mmp Unfrozen Message: written and read back, then read and written back */
static void check_mass_quote_mmp_unfrozen_message(void) {
  MassQuoteMmpUnfrozenMessage sent;
  MassQuoteMmpUnfrozenMessage got;
  uint8_t wire[32];
  uint8_t again[32];

  any_mass_quote_mmp_unfrozen_message(&sent);
  assert(encode_mass_quote_mmp_unfrozen_message(&sent, wire, 0) == 32);
  assert(decode_mass_quote_mmp_unfrozen_message(&got, wire, 0) == 32);
  equal_mass_quote_mmp_unfrozen_message(&got, &sent);

  for (size_t i = 0; i < 32; i++) { wire[i] = arbitrary(); }
  assert(decode_mass_quote_mmp_unfrozen_message(&got, wire, 0) == 32);
  assert(encode_mass_quote_mmp_unfrozen_message(&got, again, 0) == 32);
  for (size_t i = 0; i < 32; i++) { assert(again[i] == wire[i]); }
}

/* ---- Orders Mmp Unfrozen Message: 32 bytes ----------------------------------- */

/* OrdersMmpUnfrozenMessage */
typedef struct {
  uint8_t timestamp[8];                /* bytes 0 to 7 */
  uint8_t exec_id[8];                  /* bytes 8 to 15 */
  uint8_t currency_pair_id[8];         /* bytes 16 to 23 */
  uint8_t correlation_id_optional[8];  /* bytes 24 to 31 */
} OrdersMmpUnfrozenMessage;

/* any Orders Mmp Unfrozen Message at all: every byte one the checker chooses */
static void any_orders_mmp_unfrozen_message(OrdersMmpUnfrozenMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->exec_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->currency_pair_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->correlation_id_optional[i] = arbitrary(); }
}

/* Orders Mmp Unfrozen Message to the wire: 32 bytes from at, returning where the next byte goes */
static size_t encode_orders_mmp_unfrozen_message(const OrdersMmpUnfrozenMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->exec_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->currency_pair_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->correlation_id_optional[i]; }

  return at;
}

/* Orders Mmp Unfrozen Message off the wire: 32 bytes from at, returning where the next byte lies */
static size_t decode_orders_mmp_unfrozen_message(OrdersMmpUnfrozenMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->exec_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->currency_pair_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->correlation_id_optional[i] = wire[at++]; }

  return at;
}

/* what was read of Orders Mmp Unfrozen Message is what was written, byte for byte */
static void equal_orders_mmp_unfrozen_message(const OrdersMmpUnfrozenMessage *read, const OrdersMmpUnfrozenMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->exec_id[i] == written->exec_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->currency_pair_id[i] == written->currency_pair_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->correlation_id_optional[i] == written->correlation_id_optional[i]); }
}

/* Orders Mmp Unfrozen Message: written and read back, then read and written back */
static void check_orders_mmp_unfrozen_message(void) {
  OrdersMmpUnfrozenMessage sent;
  OrdersMmpUnfrozenMessage got;
  uint8_t wire[32];
  uint8_t again[32];

  any_orders_mmp_unfrozen_message(&sent);
  assert(encode_orders_mmp_unfrozen_message(&sent, wire, 0) == 32);
  assert(decode_orders_mmp_unfrozen_message(&got, wire, 0) == 32);
  equal_orders_mmp_unfrozen_message(&got, &sent);

  for (size_t i = 0; i < 32; i++) { wire[i] = arbitrary(); }
  assert(decode_orders_mmp_unfrozen_message(&got, wire, 0) == 32);
  assert(encode_orders_mmp_unfrozen_message(&got, again, 0) == 32);
  for (size_t i = 0; i < 32; i++) { assert(again[i] == wire[i]); }
}

/* ---- What esbmc checks ------------------------------------------------------- */

/* every record of the protocol, each on its own buffers */
static void checks(void) {
  check_logon_message();
  check_logon_conf_message();
  check_heartbeat_message();
  check_test_request_message();
  check_resend_request_message();
  check_gap_fill_message();
  check_quantity();
  check_show_qty();
  check_cancel_order_request_message();
  check_group_size_encoding();
  check_bid_qty();
  check_ask_qty();
  check_mass_cancel_request_message();
  check_mass_quote_cancel_request_message();
  check_total_filled();
  check_visible_qty();
  check_fill_qty();
  check_cancel_order_response_message();
  check_bid_filled_qty();
  check_ask_filled_qty();
  check_mass_cancel_response_message();
  check_mass_quote_mmp_triggered_message();
  check_orders_mmp_triggered_message();
  check_mass_quote_mmp_unfrozen_message();
  check_orders_mmp_unfrozen_message();
}

int main(void) {
#ifdef CONCRETE
  for (pattern = 0; pattern < 4; pattern++) { checks(); }
#else
  checks();
#endif

  return 0;
}
