// coinbase/coinbasederivatives/ordersapi/CoinbaseDerivatives_OrdersApi_v1_3.c
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
 *   - the dispatch that chooses a message by its type
 *   - a field present only on a condition
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

/* ---- Logon Message: 49 bytes ------------------------------------------------- */

/* LogonMessage */
typedef struct {
  uint8_t username[16];   /* bytes 0 to 15 */
  uint8_t password[32];   /* bytes 16 to 47 */
  uint8_t reset_seq_num;  /* byte 48 */
} LogonMessage;

/* any Logon Message at all: every byte one the checker chooses */
static void any_logon_message(LogonMessage *record) {
  for (size_t i = 0; i < 16; i++) { record->username[i] = arbitrary(); }
  for (size_t i = 0; i < 32; i++) { record->password[i] = arbitrary(); }
  record->reset_seq_num = arbitrary();
}

/* Logon Message to the wire: 49 bytes from at, returning where the next byte goes */
static size_t encode_logon_message(const LogonMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->username[i]; }
  for (size_t i = 0; i < 32; i++) { wire[at++] = record->password[i]; }
  wire[at++] = record->reset_seq_num;

  return at;
}

/* Logon Message off the wire: 49 bytes from at, returning where the next byte lies */
static size_t decode_logon_message(LogonMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 16; i++) { record->username[i] = wire[at++]; }
  for (size_t i = 0; i < 32; i++) { record->password[i] = wire[at++]; }
  record->reset_seq_num = wire[at++];

  return at;
}

/* what was read of Logon Message is what was written, byte for byte */
static void equal_logon_message(const LogonMessage *read, const LogonMessage *written) {
  for (size_t i = 0; i < 16; i++) { assert(read->username[i] == written->username[i]); }
  for (size_t i = 0; i < 32; i++) { assert(read->password[i] == written->password[i]); }
  assert(read->reset_seq_num == written->reset_seq_num);
}

/* Logon Message: written and read back, then read and written back */
static void check_logon_message(void) {
  LogonMessage sent;
  LogonMessage got;
  uint8_t wire[49];
  uint8_t again[49];

  any_logon_message(&sent);
  assert(encode_logon_message(&sent, wire, 0) == 49);
  assert(decode_logon_message(&got, wire, 0) == 49);
  equal_logon_message(&got, &sent);

  for (size_t i = 0; i < 49; i++) { wire[i] = arbitrary(); }
  assert(decode_logon_message(&got, wire, 0) == 49);
  assert(encode_logon_message(&got, again, 0) == 49);
  for (size_t i = 0; i < 49; i++) { assert(again[i] == wire[i]); }
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

/* ---- Logout Message: 64 bytes ------------------------------------------------ */

/* LogoutMessage */
typedef struct {
  uint8_t reason[64];  /* bytes 0 to 63 */
} LogoutMessage;

/* any Logout Message at all: every byte one the checker chooses */
static void any_logout_message(LogoutMessage *record) {
  for (size_t i = 0; i < 64; i++) { record->reason[i] = arbitrary(); }
}

/* Logout Message to the wire: 64 bytes from at, returning where the next byte goes */
static size_t encode_logout_message(const LogoutMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 64; i++) { wire[at++] = record->reason[i]; }

  return at;
}

/* Logout Message off the wire: 64 bytes from at, returning where the next byte lies */
static size_t decode_logout_message(LogoutMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 64; i++) { record->reason[i] = wire[at++]; }

  return at;
}

/* what was read of Logout Message is what was written, byte for byte */
static void equal_logout_message(const LogoutMessage *read, const LogoutMessage *written) {
  for (size_t i = 0; i < 64; i++) { assert(read->reason[i] == written->reason[i]); }
}

/* Logout Message: written and read back, then read and written back */
static void check_logout_message(void) {
  LogoutMessage sent;
  LogoutMessage got;
  uint8_t wire[64];
  uint8_t again[64];

  any_logout_message(&sent);
  assert(encode_logout_message(&sent, wire, 0) == 64);
  assert(decode_logout_message(&got, wire, 0) == 64);
  equal_logout_message(&got, &sent);

  for (size_t i = 0; i < 64; i++) { wire[i] = arbitrary(); }
  assert(decode_logout_message(&got, wire, 0) == 64);
  assert(encode_logout_message(&got, again, 0) == 64);
  for (size_t i = 0; i < 64; i++) { assert(again[i] == wire[i]); }
}

/* ---- Logged Out Message: 64 bytes -------------------------------------------- */

/* LoggedOutMessage */
typedef struct {
  uint8_t reason[64];  /* bytes 0 to 63 */
} LoggedOutMessage;

/* any Logged Out Message at all: every byte one the checker chooses */
static void any_logged_out_message(LoggedOutMessage *record) {
  for (size_t i = 0; i < 64; i++) { record->reason[i] = arbitrary(); }
}

/* Logged Out Message to the wire: 64 bytes from at, returning where the next byte goes */
static size_t encode_logged_out_message(const LoggedOutMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 64; i++) { wire[at++] = record->reason[i]; }

  return at;
}

/* Logged Out Message off the wire: 64 bytes from at, returning where the next byte lies */
static size_t decode_logged_out_message(LoggedOutMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 64; i++) { record->reason[i] = wire[at++]; }

  return at;
}

/* what was read of Logged Out Message is what was written, byte for byte */
static void equal_logged_out_message(const LoggedOutMessage *read, const LoggedOutMessage *written) {
  for (size_t i = 0; i < 64; i++) { assert(read->reason[i] == written->reason[i]); }
}

/* Logged Out Message: written and read back, then read and written back */
static void check_logged_out_message(void) {
  LoggedOutMessage sent;
  LoggedOutMessage got;
  uint8_t wire[64];
  uint8_t again[64];

  any_logged_out_message(&sent);
  assert(encode_logged_out_message(&sent, wire, 0) == 64);
  assert(decode_logged_out_message(&got, wire, 0) == 64);
  equal_logged_out_message(&got, &sent);

  for (size_t i = 0; i < 64; i++) { wire[i] = arbitrary(); }
  assert(decode_logged_out_message(&got, wire, 0) == 64);
  assert(encode_logged_out_message(&got, again, 0) == 64);
  for (size_t i = 0; i < 64; i++) { assert(again[i] == wire[i]); }
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

/* ---- Resend Request Message: 8 bytes ----------------------------------------- */

/* ResendRequestMessage */
typedef struct {
  uint8_t from_sequence_number[4];  /* bytes 0 to 3 */
  uint8_t to_sequence_number[4];    /* bytes 4 to 7 */
} ResendRequestMessage;

/* any Resend Request Message at all: every byte one the checker chooses */
static void any_resend_request_message(ResendRequestMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->from_sequence_number[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->to_sequence_number[i] = arbitrary(); }
}

/* Resend Request Message to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_resend_request_message(const ResendRequestMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->from_sequence_number[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->to_sequence_number[i]; }

  return at;
}

/* Resend Request Message off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_resend_request_message(ResendRequestMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->from_sequence_number[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->to_sequence_number[i] = wire[at++]; }

  return at;
}

/* what was read of Resend Request Message is what was written, byte for byte */
static void equal_resend_request_message(const ResendRequestMessage *read, const ResendRequestMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->from_sequence_number[i] == written->from_sequence_number[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->to_sequence_number[i] == written->to_sequence_number[i]); }
}

/* Resend Request Message: written and read back, then read and written back */
static void check_resend_request_message(void) {
  ResendRequestMessage sent;
  ResendRequestMessage got;
  uint8_t wire[8];
  uint8_t again[8];

  any_resend_request_message(&sent);
  assert(encode_resend_request_message(&sent, wire, 0) == 8);
  assert(decode_resend_request_message(&got, wire, 0) == 8);
  equal_resend_request_message(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_resend_request_message(&got, wire, 0) == 8);
  assert(encode_resend_request_message(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Gap Fill Message: 8 bytes ----------------------------------------------- */

/* GapFillMessage */
typedef struct {
  uint8_t new_sequence_number[4];  /* bytes 0 to 3 */
  uint8_t gap_fill_padding[4];     /* bytes 4 to 7 */
} GapFillMessage;

/* any Gap Fill Message at all: every byte one the checker chooses */
static void any_gap_fill_message(GapFillMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->new_sequence_number[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->gap_fill_padding[i] = arbitrary(); }
}

/* Gap Fill Message to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_gap_fill_message(const GapFillMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->new_sequence_number[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->gap_fill_padding[i]; }

  return at;
}

/* Gap Fill Message off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_gap_fill_message(GapFillMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->new_sequence_number[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->gap_fill_padding[i] = wire[at++]; }

  return at;
}

/* what was read of Gap Fill Message is what was written, byte for byte */
static void equal_gap_fill_message(const GapFillMessage *read, const GapFillMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->new_sequence_number[i] == written->new_sequence_number[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->gap_fill_padding[i] == written->gap_fill_padding[i]); }
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

/* ---- Instrument Info Request Message: 8 bytes -------------------------------- */

/* InstrumentInfoRequestMessage */
typedef struct {
  uint8_t correlation_id[8];  /* bytes 0 to 7 */
} InstrumentInfoRequestMessage;

/* any Instrument Info Request Message at all: every byte one the checker chooses */
static void any_instrument_info_request_message(InstrumentInfoRequestMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->correlation_id[i] = arbitrary(); }
}

/* Instrument Info Request Message to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_instrument_info_request_message(const InstrumentInfoRequestMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->correlation_id[i]; }

  return at;
}

/* Instrument Info Request Message off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_instrument_info_request_message(InstrumentInfoRequestMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->correlation_id[i] = wire[at++]; }

  return at;
}

/* what was read of Instrument Info Request Message is what was written, byte for byte */
static void equal_instrument_info_request_message(const InstrumentInfoRequestMessage *read, const InstrumentInfoRequestMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->correlation_id[i] == written->correlation_id[i]); }
}

/* Instrument Info Request Message: written and read back, then read and written back */
static void check_instrument_info_request_message(void) {
  InstrumentInfoRequestMessage sent;
  InstrumentInfoRequestMessage got;
  uint8_t wire[8];
  uint8_t again[8];

  any_instrument_info_request_message(&sent);
  assert(encode_instrument_info_request_message(&sent, wire, 0) == 8);
  assert(decode_instrument_info_request_message(&got, wire, 0) == 8);
  equal_instrument_info_request_message(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_instrument_info_request_message(&got, wire, 0) == 8);
  assert(encode_instrument_info_request_message(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Instrument Info Message: 48 bytes --------------------------------------- */

/* InstrumentInfoMessage */
typedef struct {
  uint8_t correlation_id[8];  /* bytes 0 to 7 */
  uint8_t instrument_id[4];   /* bytes 8 to 11 */
  uint8_t security_type;      /* byte 12 */
  uint8_t instrument_status;  /* byte 13 */
  uint8_t is_last_message;    /* byte 14 */
  uint8_t reserved_byte;      /* byte 15 */
  uint8_t symbol[32];         /* bytes 16 to 47 */
} InstrumentInfoMessage;

/* any Instrument Info Message at all: every byte one the checker chooses */
static void any_instrument_info_message(InstrumentInfoMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->correlation_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->instrument_id[i] = arbitrary(); }
  record->security_type = arbitrary();
  record->instrument_status = arbitrary();
  record->is_last_message = arbitrary();
  record->reserved_byte = arbitrary();
  for (size_t i = 0; i < 32; i++) { record->symbol[i] = arbitrary(); }
}

/* Instrument Info Message to the wire: 48 bytes from at, returning where the next byte goes */
static size_t encode_instrument_info_message(const InstrumentInfoMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->correlation_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument_id[i]; }
  wire[at++] = record->security_type;
  wire[at++] = record->instrument_status;
  wire[at++] = record->is_last_message;
  wire[at++] = record->reserved_byte;
  for (size_t i = 0; i < 32; i++) { wire[at++] = record->symbol[i]; }

  return at;
}

/* Instrument Info Message off the wire: 48 bytes from at, returning where the next byte lies */
static size_t decode_instrument_info_message(InstrumentInfoMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->correlation_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->instrument_id[i] = wire[at++]; }
  record->security_type = wire[at++];
  record->instrument_status = wire[at++];
  record->is_last_message = wire[at++];
  record->reserved_byte = wire[at++];
  for (size_t i = 0; i < 32; i++) { record->symbol[i] = wire[at++]; }

  return at;
}

/* what was read of Instrument Info Message is what was written, byte for byte */
static void equal_instrument_info_message(const InstrumentInfoMessage *read, const InstrumentInfoMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->correlation_id[i] == written->correlation_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->instrument_id[i] == written->instrument_id[i]); }
  assert(read->security_type == written->security_type);
  assert(read->instrument_status == written->instrument_status);
  assert(read->is_last_message == written->is_last_message);
  assert(read->reserved_byte == written->reserved_byte);
  for (size_t i = 0; i < 32; i++) { assert(read->symbol[i] == written->symbol[i]); }
}

/* Instrument Info Message: written and read back, then read and written back */
static void check_instrument_info_message(void) {
  InstrumentInfoMessage sent;
  InstrumentInfoMessage got;
  uint8_t wire[48];
  uint8_t again[48];

  any_instrument_info_message(&sent);
  assert(encode_instrument_info_message(&sent, wire, 0) == 48);
  assert(decode_instrument_info_message(&got, wire, 0) == 48);
  equal_instrument_info_message(&got, &sent);

  for (size_t i = 0; i < 48; i++) { wire[i] = arbitrary(); }
  assert(decode_instrument_info_message(&got, wire, 0) == 48);
  assert(encode_instrument_info_message(&got, again, 0) == 48);
  for (size_t i = 0; i < 48; i++) { assert(again[i] == wire[i]); }
}

/* ---- Set Account Message: 24 bytes ------------------------------------------- */

/* SetAccountMessage */
typedef struct {
  uint8_t correlation_id[8];  /* bytes 0 to 7 */
  uint8_t account[16];        /* bytes 8 to 23 */
} SetAccountMessage;

/* any Set Account Message at all: every byte one the checker chooses */
static void any_set_account_message(SetAccountMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->correlation_id[i] = arbitrary(); }
  for (size_t i = 0; i < 16; i++) { record->account[i] = arbitrary(); }
}

/* Set Account Message to the wire: 24 bytes from at, returning where the next byte goes */
static size_t encode_set_account_message(const SetAccountMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->correlation_id[i]; }
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->account[i]; }

  return at;
}

/* Set Account Message off the wire: 24 bytes from at, returning where the next byte lies */
static size_t decode_set_account_message(SetAccountMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->correlation_id[i] = wire[at++]; }
  for (size_t i = 0; i < 16; i++) { record->account[i] = wire[at++]; }

  return at;
}

/* what was read of Set Account Message is what was written, byte for byte */
static void equal_set_account_message(const SetAccountMessage *read, const SetAccountMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->correlation_id[i] == written->correlation_id[i]); }
  for (size_t i = 0; i < 16; i++) { assert(read->account[i] == written->account[i]); }
}

/* Set Account Message: written and read back, then read and written back */
static void check_set_account_message(void) {
  SetAccountMessage sent;
  SetAccountMessage got;
  uint8_t wire[24];
  uint8_t again[24];

  any_set_account_message(&sent);
  assert(encode_set_account_message(&sent, wire, 0) == 24);
  assert(decode_set_account_message(&got, wire, 0) == 24);
  equal_set_account_message(&got, &sent);

  for (size_t i = 0; i < 24; i++) { wire[i] = arbitrary(); }
  assert(decode_set_account_message(&got, wire, 0) == 24);
  assert(encode_set_account_message(&got, again, 0) == 24);
  for (size_t i = 0; i < 24; i++) { assert(again[i] == wire[i]); }
}

/* ---- Set Trader Message: 24 bytes -------------------------------------------- */

/* SetTraderMessage */
typedef struct {
  uint8_t correlation_id[8];  /* bytes 0 to 7 */
  uint8_t trader[16];         /* bytes 8 to 23 */
} SetTraderMessage;

/* any Set Trader Message at all: every byte one the checker chooses */
static void any_set_trader_message(SetTraderMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->correlation_id[i] = arbitrary(); }
  for (size_t i = 0; i < 16; i++) { record->trader[i] = arbitrary(); }
}

/* Set Trader Message to the wire: 24 bytes from at, returning where the next byte goes */
static size_t encode_set_trader_message(const SetTraderMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->correlation_id[i]; }
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->trader[i]; }

  return at;
}

/* Set Trader Message off the wire: 24 bytes from at, returning where the next byte lies */
static size_t decode_set_trader_message(SetTraderMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->correlation_id[i] = wire[at++]; }
  for (size_t i = 0; i < 16; i++) { record->trader[i] = wire[at++]; }

  return at;
}

/* what was read of Set Trader Message is what was written, byte for byte */
static void equal_set_trader_message(const SetTraderMessage *read, const SetTraderMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->correlation_id[i] == written->correlation_id[i]); }
  for (size_t i = 0; i < 16; i++) { assert(read->trader[i] == written->trader[i]); }
}

/* Set Trader Message: written and read back, then read and written back */
static void check_set_trader_message(void) {
  SetTraderMessage sent;
  SetTraderMessage got;
  uint8_t wire[24];
  uint8_t again[24];

  any_set_trader_message(&sent);
  assert(encode_set_trader_message(&sent, wire, 0) == 24);
  assert(decode_set_trader_message(&got, wire, 0) == 24);
  equal_set_trader_message(&got, &sent);

  for (size_t i = 0; i < 24; i++) { wire[i] = arbitrary(); }
  assert(decode_set_trader_message(&got, wire, 0) == 24);
  assert(encode_set_trader_message(&got, again, 0) == 24);
  for (size_t i = 0; i < 24; i++) { assert(again[i] == wire[i]); }
}

/* ---- Set Ack Message: 8 bytes ------------------------------------------------ */

/* SetAckMessage */
typedef struct {
  uint8_t correlation_id[8];  /* bytes 0 to 7 */
} SetAckMessage;

/* any Set Ack Message at all: every byte one the checker chooses */
static void any_set_ack_message(SetAckMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->correlation_id[i] = arbitrary(); }
}

/* Set Ack Message to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_set_ack_message(const SetAckMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->correlation_id[i]; }

  return at;
}

/* Set Ack Message off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_set_ack_message(SetAckMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->correlation_id[i] = wire[at++]; }

  return at;
}

/* what was read of Set Ack Message is what was written, byte for byte */
static void equal_set_ack_message(const SetAckMessage *read, const SetAckMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->correlation_id[i] == written->correlation_id[i]); }
}

/* Set Ack Message: written and read back, then read and written back */
static void check_set_ack_message(void) {
  SetAckMessage sent;
  SetAckMessage got;
  uint8_t wire[8];
  uint8_t again[8];

  any_set_ack_message(&sent);
  assert(encode_set_ack_message(&sent, wire, 0) == 8);
  assert(decode_set_ack_message(&got, wire, 0) == 8);
  equal_set_ack_message(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_set_ack_message(&got, wire, 0) == 8);
  assert(encode_set_ack_message(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- New Order Message: 33 bytes --------------------------------------------- */

/* NewOrderMessage */
typedef struct {
  uint8_t client_order_id[8];  /* bytes 0 to 7 */
  uint8_t correlation_id[8];   /* bytes 8 to 15 */
  uint8_t limit_price[8];      /* bytes 16 to 23 */
  uint8_t quantity[4];         /* bytes 24 to 27 */
  uint8_t instrument_id[4];    /* bytes 28 to 31 */
  uint8_t side;                /* byte 32 */
} NewOrderMessage;

/* any New Order Message at all: every byte one the checker chooses */
static void any_new_order_message(NewOrderMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->client_order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->correlation_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->limit_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->instrument_id[i] = arbitrary(); }
  record->side = arbitrary();
}

/* New Order Message to the wire: 33 bytes from at, returning where the next byte goes */
static size_t encode_new_order_message(const NewOrderMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->client_order_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->correlation_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->limit_price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->quantity[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument_id[i]; }
  wire[at++] = record->side;

  return at;
}

/* New Order Message off the wire: 33 bytes from at, returning where the next byte lies */
static size_t decode_new_order_message(NewOrderMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->client_order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->correlation_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->limit_price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->instrument_id[i] = wire[at++]; }
  record->side = wire[at++];

  return at;
}

/* what was read of New Order Message is what was written, byte for byte */
static void equal_new_order_message(const NewOrderMessage *read, const NewOrderMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->client_order_id[i] == written->client_order_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->correlation_id[i] == written->correlation_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->limit_price[i] == written->limit_price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->quantity[i] == written->quantity[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->instrument_id[i] == written->instrument_id[i]); }
  assert(read->side == written->side);
}

/* New Order Message: written and read back, then read and written back */
static void check_new_order_message(void) {
  NewOrderMessage sent;
  NewOrderMessage got;
  uint8_t wire[33];
  uint8_t again[33];

  any_new_order_message(&sent);
  assert(encode_new_order_message(&sent, wire, 0) == 33);
  assert(decode_new_order_message(&got, wire, 0) == 33);
  equal_new_order_message(&got, &sent);

  for (size_t i = 0; i < 33; i++) { wire[i] = arbitrary(); }
  assert(decode_new_order_message(&got, wire, 0) == 33);
  assert(encode_new_order_message(&got, again, 0) == 33);
  for (size_t i = 0; i < 33; i++) { assert(again[i] == wire[i]); }
}

/* ---- Order Entered Message: 48 bytes ----------------------------------------- */

/* OrderEnteredMessage */
typedef struct {
  uint8_t timestamp[8];        /* bytes 0 to 7 */
  uint8_t exec_id[8];          /* bytes 8 to 15 */
  uint8_t client_order_id[8];  /* bytes 16 to 23 */
  uint8_t correlation_id[8];   /* bytes 24 to 31 */
  uint8_t order_id[8];         /* bytes 32 to 39 */
  uint8_t receive_time[8];     /* bytes 40 to 47 */
} OrderEnteredMessage;

/* any Order Entered Message at all: every byte one the checker chooses */
static void any_order_entered_message(OrderEnteredMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->exec_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->client_order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->correlation_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->receive_time[i] = arbitrary(); }
}

/* Order Entered Message to the wire: 48 bytes from at, returning where the next byte goes */
static size_t encode_order_entered_message(const OrderEnteredMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->exec_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->client_order_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->correlation_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->receive_time[i]; }

  return at;
}

/* Order Entered Message off the wire: 48 bytes from at, returning where the next byte lies */
static size_t decode_order_entered_message(OrderEnteredMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->exec_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->client_order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->correlation_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->receive_time[i] = wire[at++]; }

  return at;
}

/* what was read of Order Entered Message is what was written, byte for byte */
static void equal_order_entered_message(const OrderEnteredMessage *read, const OrderEnteredMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->exec_id[i] == written->exec_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->client_order_id[i] == written->client_order_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->correlation_id[i] == written->correlation_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->order_id[i] == written->order_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->receive_time[i] == written->receive_time[i]); }
}

/* Order Entered Message: written and read back, then read and written back */
static void check_order_entered_message(void) {
  OrderEnteredMessage sent;
  OrderEnteredMessage got;
  uint8_t wire[48];
  uint8_t again[48];

  any_order_entered_message(&sent);
  assert(encode_order_entered_message(&sent, wire, 0) == 48);
  assert(decode_order_entered_message(&got, wire, 0) == 48);
  equal_order_entered_message(&got, &sent);

  for (size_t i = 0; i < 48; i++) { wire[i] = arbitrary(); }
  assert(decode_order_entered_message(&got, wire, 0) == 48);
  assert(encode_order_entered_message(&got, again, 0) == 48);
  for (size_t i = 0; i < 48; i++) { assert(again[i] == wire[i]); }
}

/* ---- Replace Order Message: 32 bytes ----------------------------------------- */

/* ReplaceOrderMessage */
typedef struct {
  uint8_t client_order_id[8];  /* bytes 0 to 7 */
  uint8_t correlation_id[8];   /* bytes 8 to 15 */
  uint8_t new_limit_price[8];  /* bytes 16 to 23 */
  uint8_t new_quantity[4];     /* bytes 24 to 27 */
  uint8_t instrument_id[4];    /* bytes 28 to 31 */
} ReplaceOrderMessage;

/* any Replace Order Message at all: every byte one the checker chooses */
static void any_replace_order_message(ReplaceOrderMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->client_order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->correlation_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->new_limit_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->new_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->instrument_id[i] = arbitrary(); }
}

/* Replace Order Message to the wire: 32 bytes from at, returning where the next byte goes */
static size_t encode_replace_order_message(const ReplaceOrderMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->client_order_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->correlation_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->new_limit_price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->new_quantity[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument_id[i]; }

  return at;
}

/* Replace Order Message off the wire: 32 bytes from at, returning where the next byte lies */
static size_t decode_replace_order_message(ReplaceOrderMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->client_order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->correlation_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->new_limit_price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->new_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->instrument_id[i] = wire[at++]; }

  return at;
}

/* what was read of Replace Order Message is what was written, byte for byte */
static void equal_replace_order_message(const ReplaceOrderMessage *read, const ReplaceOrderMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->client_order_id[i] == written->client_order_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->correlation_id[i] == written->correlation_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->new_limit_price[i] == written->new_limit_price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->new_quantity[i] == written->new_quantity[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->instrument_id[i] == written->instrument_id[i]); }
}

/* Replace Order Message: written and read back, then read and written back */
static void check_replace_order_message(void) {
  ReplaceOrderMessage sent;
  ReplaceOrderMessage got;
  uint8_t wire[32];
  uint8_t again[32];

  any_replace_order_message(&sent);
  assert(encode_replace_order_message(&sent, wire, 0) == 32);
  assert(decode_replace_order_message(&got, wire, 0) == 32);
  equal_replace_order_message(&got, &sent);

  for (size_t i = 0; i < 32; i++) { wire[i] = arbitrary(); }
  assert(decode_replace_order_message(&got, wire, 0) == 32);
  assert(encode_replace_order_message(&got, again, 0) == 32);
  for (size_t i = 0; i < 32; i++) { assert(again[i] == wire[i]); }
}

/* ---- Stream Order Message: 41 bytes ------------------------------------------ */

/* StreamOrderMessage */
typedef struct {
  uint8_t client_order_id[8];         /* bytes 0 to 7 */
  uint8_t correlation_id[8];          /* bytes 8 to 15 */
  uint8_t last_processed_fill_id[8];  /* bytes 16 to 23 */
  uint8_t limit_price[8];             /* bytes 24 to 31 */
  uint8_t quantity[4];                /* bytes 32 to 35 */
  uint8_t instrument_id[4];           /* bytes 36 to 39 */
  uint8_t side;                       /* byte 40 */
} StreamOrderMessage;

/* any Stream Order Message at all: every byte one the checker chooses */
static void any_stream_order_message(StreamOrderMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->client_order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->correlation_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->last_processed_fill_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->limit_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->instrument_id[i] = arbitrary(); }
  record->side = arbitrary();
}

/* Stream Order Message to the wire: 41 bytes from at, returning where the next byte goes */
static size_t encode_stream_order_message(const StreamOrderMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->client_order_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->correlation_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->last_processed_fill_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->limit_price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->quantity[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument_id[i]; }
  wire[at++] = record->side;

  return at;
}

/* Stream Order Message off the wire: 41 bytes from at, returning where the next byte lies */
static size_t decode_stream_order_message(StreamOrderMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->client_order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->correlation_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->last_processed_fill_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->limit_price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->instrument_id[i] = wire[at++]; }
  record->side = wire[at++];

  return at;
}

/* what was read of Stream Order Message is what was written, byte for byte */
static void equal_stream_order_message(const StreamOrderMessage *read, const StreamOrderMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->client_order_id[i] == written->client_order_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->correlation_id[i] == written->correlation_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->last_processed_fill_id[i] == written->last_processed_fill_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->limit_price[i] == written->limit_price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->quantity[i] == written->quantity[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->instrument_id[i] == written->instrument_id[i]); }
  assert(read->side == written->side);
}

/* Stream Order Message: written and read back, then read and written back */
static void check_stream_order_message(void) {
  StreamOrderMessage sent;
  StreamOrderMessage got;
  uint8_t wire[41];
  uint8_t again[41];

  any_stream_order_message(&sent);
  assert(encode_stream_order_message(&sent, wire, 0) == 41);
  assert(decode_stream_order_message(&got, wire, 0) == 41);
  equal_stream_order_message(&got, &sent);

  for (size_t i = 0; i < 41; i++) { wire[i] = arbitrary(); }
  assert(decode_stream_order_message(&got, wire, 0) == 41);
  assert(encode_stream_order_message(&got, again, 0) == 41);
  for (size_t i = 0; i < 41; i++) { assert(again[i] == wire[i]); }
}

/* ---- Order Reject Message: 80 bytes ------------------------------------------ */

/* OrderRejectMessage */
typedef struct {
  uint8_t timestamp[8];              /* bytes 0 to 7 */
  uint8_t client_order_id[8];        /* bytes 8 to 15 */
  uint8_t correlation_id[8];         /* bytes 16 to 23 */
  uint8_t order_id_optional[8];      /* bytes 24 to 31 */
  uint8_t order_reject_reason;       /* byte 32 */
  uint8_t order_reject_details[47];  /* bytes 33 to 79 */
} OrderRejectMessage;

/* any Order Reject Message at all: every byte one the checker chooses */
static void any_order_reject_message(OrderRejectMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->client_order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->correlation_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->order_id_optional[i] = arbitrary(); }
  record->order_reject_reason = arbitrary();
  for (size_t i = 0; i < 47; i++) { record->order_reject_details[i] = arbitrary(); }
}

/* Order Reject Message to the wire: 80 bytes from at, returning where the next byte goes */
static size_t encode_order_reject_message(const OrderRejectMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->client_order_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->correlation_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_id_optional[i]; }
  wire[at++] = record->order_reject_reason;
  for (size_t i = 0; i < 47; i++) { wire[at++] = record->order_reject_details[i]; }

  return at;
}

/* Order Reject Message off the wire: 80 bytes from at, returning where the next byte lies */
static size_t decode_order_reject_message(OrderRejectMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->client_order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->correlation_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->order_id_optional[i] = wire[at++]; }
  record->order_reject_reason = wire[at++];
  for (size_t i = 0; i < 47; i++) { record->order_reject_details[i] = wire[at++]; }

  return at;
}

/* what was read of Order Reject Message is what was written, byte for byte */
static void equal_order_reject_message(const OrderRejectMessage *read, const OrderRejectMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->client_order_id[i] == written->client_order_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->correlation_id[i] == written->correlation_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->order_id_optional[i] == written->order_id_optional[i]); }
  assert(read->order_reject_reason == written->order_reject_reason);
  for (size_t i = 0; i < 47; i++) { assert(read->order_reject_details[i] == written->order_reject_details[i]); }
}

/* Order Reject Message: written and read back, then read and written back */
static void check_order_reject_message(void) {
  OrderRejectMessage sent;
  OrderRejectMessage got;
  uint8_t wire[80];
  uint8_t again[80];

  any_order_reject_message(&sent);
  assert(encode_order_reject_message(&sent, wire, 0) == 80);
  assert(decode_order_reject_message(&got, wire, 0) == 80);
  equal_order_reject_message(&got, &sent);

  for (size_t i = 0; i < 80; i++) { wire[i] = arbitrary(); }
  assert(decode_order_reject_message(&got, wire, 0) == 80);
  assert(encode_order_reject_message(&got, again, 0) == 80);
  for (size_t i = 0; i < 80; i++) { assert(again[i] == wire[i]); }
}

/* ---- Order Replaced Message: 60 bytes ---------------------------------------- */

/* OrderReplacedMessage */
typedef struct {
  uint8_t timestamp[8];        /* bytes 0 to 7 */
  uint8_t exec_id[8];          /* bytes 8 to 15 */
  uint8_t client_order_id[8];  /* bytes 16 to 23 */
  uint8_t correlation_id[8];   /* bytes 24 to 31 */
  uint8_t order_id[8];         /* bytes 32 to 39 */
  uint8_t receive_time[8];     /* bytes 40 to 47 */
  uint8_t total_filled[4];     /* bytes 48 to 51 */
  uint8_t available_qty[4];    /* bytes 52 to 55 */
  uint8_t instrument_id[4];    /* bytes 56 to 59 */
} OrderReplacedMessage;

/* any Order Replaced Message at all: every byte one the checker chooses */
static void any_order_replaced_message(OrderReplacedMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->exec_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->client_order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->correlation_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->receive_time[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->total_filled[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->available_qty[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->instrument_id[i] = arbitrary(); }
}

/* Order Replaced Message to the wire: 60 bytes from at, returning where the next byte goes */
static size_t encode_order_replaced_message(const OrderReplacedMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->exec_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->client_order_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->correlation_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->receive_time[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->total_filled[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->available_qty[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument_id[i]; }

  return at;
}

/* Order Replaced Message off the wire: 60 bytes from at, returning where the next byte lies */
static size_t decode_order_replaced_message(OrderReplacedMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->exec_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->client_order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->correlation_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->receive_time[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->total_filled[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->available_qty[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->instrument_id[i] = wire[at++]; }

  return at;
}

/* what was read of Order Replaced Message is what was written, byte for byte */
static void equal_order_replaced_message(const OrderReplacedMessage *read, const OrderReplacedMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->exec_id[i] == written->exec_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->client_order_id[i] == written->client_order_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->correlation_id[i] == written->correlation_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->order_id[i] == written->order_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->receive_time[i] == written->receive_time[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->total_filled[i] == written->total_filled[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->available_qty[i] == written->available_qty[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->instrument_id[i] == written->instrument_id[i]); }
}

/* Order Replaced Message: written and read back, then read and written back */
static void check_order_replaced_message(void) {
  OrderReplacedMessage sent;
  OrderReplacedMessage got;
  uint8_t wire[60];
  uint8_t again[60];

  any_order_replaced_message(&sent);
  assert(encode_order_replaced_message(&sent, wire, 0) == 60);
  assert(decode_order_replaced_message(&got, wire, 0) == 60);
  equal_order_replaced_message(&got, &sent);

  for (size_t i = 0; i < 60; i++) { wire[i] = arbitrary(); }
  assert(decode_order_replaced_message(&got, wire, 0) == 60);
  assert(encode_order_replaced_message(&got, again, 0) == 60);
  for (size_t i = 0; i < 60; i++) { assert(again[i] == wire[i]); }
}

/* ---- Cancel Order Message: 20 bytes ------------------------------------------ */

/* CancelOrderMessage */
typedef struct {
  uint8_t client_order_id[8];  /* bytes 0 to 7 */
  uint8_t correlation_id[8];   /* bytes 8 to 15 */
  uint8_t instrument_id[4];    /* bytes 16 to 19 */
} CancelOrderMessage;

/* any Cancel Order Message at all: every byte one the checker chooses */
static void any_cancel_order_message(CancelOrderMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->client_order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->correlation_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->instrument_id[i] = arbitrary(); }
}

/* Cancel Order Message to the wire: 20 bytes from at, returning where the next byte goes */
static size_t encode_cancel_order_message(const CancelOrderMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->client_order_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->correlation_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument_id[i]; }

  return at;
}

/* Cancel Order Message off the wire: 20 bytes from at, returning where the next byte lies */
static size_t decode_cancel_order_message(CancelOrderMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->client_order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->correlation_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->instrument_id[i] = wire[at++]; }

  return at;
}

/* what was read of Cancel Order Message is what was written, byte for byte */
static void equal_cancel_order_message(const CancelOrderMessage *read, const CancelOrderMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->client_order_id[i] == written->client_order_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->correlation_id[i] == written->correlation_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->instrument_id[i] == written->instrument_id[i]); }
}

/* Cancel Order Message: written and read back, then read and written back */
static void check_cancel_order_message(void) {
  CancelOrderMessage sent;
  CancelOrderMessage got;
  uint8_t wire[20];
  uint8_t again[20];

  any_cancel_order_message(&sent);
  assert(encode_cancel_order_message(&sent, wire, 0) == 20);
  assert(decode_cancel_order_message(&got, wire, 0) == 20);
  equal_cancel_order_message(&got, &sent);

  for (size_t i = 0; i < 20; i++) { wire[i] = arbitrary(); }
  assert(decode_cancel_order_message(&got, wire, 0) == 20);
  assert(encode_cancel_order_message(&got, again, 0) == 20);
  for (size_t i = 0; i < 20; i++) { assert(again[i] == wire[i]); }
}

/* ---- Order Canceled Message: 57 bytes ---------------------------------------- */

/* OrderCanceledMessage */
typedef struct {
  uint8_t timestamp[8];        /* bytes 0 to 7 */
  uint8_t exec_id[8];          /* bytes 8 to 15 */
  uint8_t client_order_id[8];  /* bytes 16 to 23 */
  uint8_t correlation_id[8];   /* bytes 24 to 31 */
  uint8_t order_id[8];         /* bytes 32 to 39 */
  uint8_t receive_time[8];     /* bytes 40 to 47 */
  uint8_t total_filled[4];     /* bytes 48 to 51 */
  uint8_t instrument_id[4];    /* bytes 52 to 55 */
  uint8_t cancel_reason;       /* byte 56 */
} OrderCanceledMessage;

/* any Order Canceled Message at all: every byte one the checker chooses */
static void any_order_canceled_message(OrderCanceledMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->exec_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->client_order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->correlation_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->receive_time[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->total_filled[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->instrument_id[i] = arbitrary(); }
  record->cancel_reason = arbitrary();
}

/* Order Canceled Message to the wire: 57 bytes from at, returning where the next byte goes */
static size_t encode_order_canceled_message(const OrderCanceledMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->exec_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->client_order_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->correlation_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->receive_time[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->total_filled[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument_id[i]; }
  wire[at++] = record->cancel_reason;

  return at;
}

/* Order Canceled Message off the wire: 57 bytes from at, returning where the next byte lies */
static size_t decode_order_canceled_message(OrderCanceledMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->exec_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->client_order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->correlation_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->receive_time[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->total_filled[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->instrument_id[i] = wire[at++]; }
  record->cancel_reason = wire[at++];

  return at;
}

/* what was read of Order Canceled Message is what was written, byte for byte */
static void equal_order_canceled_message(const OrderCanceledMessage *read, const OrderCanceledMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->exec_id[i] == written->exec_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->client_order_id[i] == written->client_order_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->correlation_id[i] == written->correlation_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->order_id[i] == written->order_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->receive_time[i] == written->receive_time[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->total_filled[i] == written->total_filled[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->instrument_id[i] == written->instrument_id[i]); }
  assert(read->cancel_reason == written->cancel_reason);
}

/* Order Canceled Message: written and read back, then read and written back */
static void check_order_canceled_message(void) {
  OrderCanceledMessage sent;
  OrderCanceledMessage got;
  uint8_t wire[57];
  uint8_t again[57];

  any_order_canceled_message(&sent);
  assert(encode_order_canceled_message(&sent, wire, 0) == 57);
  assert(decode_order_canceled_message(&got, wire, 0) == 57);
  equal_order_canceled_message(&got, &sent);

  for (size_t i = 0; i < 57; i++) { wire[i] = arbitrary(); }
  assert(decode_order_canceled_message(&got, wire, 0) == 57);
  assert(encode_order_canceled_message(&got, again, 0) == 57);
  for (size_t i = 0; i < 57; i++) { assert(again[i] == wire[i]); }
}

/* ---- Cancel Order Reject Message: 64 bytes ----------------------------------- */

/* CancelOrderRejectMessage */
typedef struct {
  uint8_t timestamp[8];                     /* bytes 0 to 7 */
  uint8_t client_order_id[8];               /* bytes 8 to 15 */
  uint8_t correlation_id[8];                /* bytes 16 to 23 */
  uint8_t order_id_optional[8];             /* bytes 24 to 31 */
  uint8_t cancel_order_reject_reason;       /* byte 32 */
  uint8_t cancel_order_reject_details[31];  /* bytes 33 to 63 */
} CancelOrderRejectMessage;

/* any Cancel Order Reject Message at all: every byte one the checker chooses */
static void any_cancel_order_reject_message(CancelOrderRejectMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->client_order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->correlation_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->order_id_optional[i] = arbitrary(); }
  record->cancel_order_reject_reason = arbitrary();
  for (size_t i = 0; i < 31; i++) { record->cancel_order_reject_details[i] = arbitrary(); }
}

/* Cancel Order Reject Message to the wire: 64 bytes from at, returning where the next byte goes */
static size_t encode_cancel_order_reject_message(const CancelOrderRejectMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->client_order_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->correlation_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_id_optional[i]; }
  wire[at++] = record->cancel_order_reject_reason;
  for (size_t i = 0; i < 31; i++) { wire[at++] = record->cancel_order_reject_details[i]; }

  return at;
}

/* Cancel Order Reject Message off the wire: 64 bytes from at, returning where the next byte lies */
static size_t decode_cancel_order_reject_message(CancelOrderRejectMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->client_order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->correlation_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->order_id_optional[i] = wire[at++]; }
  record->cancel_order_reject_reason = wire[at++];
  for (size_t i = 0; i < 31; i++) { record->cancel_order_reject_details[i] = wire[at++]; }

  return at;
}

/* what was read of Cancel Order Reject Message is what was written, byte for byte */
static void equal_cancel_order_reject_message(const CancelOrderRejectMessage *read, const CancelOrderRejectMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->client_order_id[i] == written->client_order_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->correlation_id[i] == written->correlation_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->order_id_optional[i] == written->order_id_optional[i]); }
  assert(read->cancel_order_reject_reason == written->cancel_order_reject_reason);
  for (size_t i = 0; i < 31; i++) { assert(read->cancel_order_reject_details[i] == written->cancel_order_reject_details[i]); }
}

/* Cancel Order Reject Message: written and read back, then read and written back */
static void check_cancel_order_reject_message(void) {
  CancelOrderRejectMessage sent;
  CancelOrderRejectMessage got;
  uint8_t wire[64];
  uint8_t again[64];

  any_cancel_order_reject_message(&sent);
  assert(encode_cancel_order_reject_message(&sent, wire, 0) == 64);
  assert(decode_cancel_order_reject_message(&got, wire, 0) == 64);
  equal_cancel_order_reject_message(&got, &sent);

  for (size_t i = 0; i < 64; i++) { wire[i] = arbitrary(); }
  assert(decode_cancel_order_reject_message(&got, wire, 0) == 64);
  assert(encode_cancel_order_reject_message(&got, again, 0) == 64);
  for (size_t i = 0; i < 64; i++) { assert(again[i] == wire[i]); }
}

/* ---- Mass Cancel Order Message: 23 bytes ------------------------------------- */

/* MassCancelOrderMessage */
typedef struct {
  uint8_t correlation_id[8];     /* bytes 0 to 7 */
  uint8_t limit_price[8];        /* bytes 8 to 15 */
  uint8_t instrument_id[4];      /* bytes 16 to 19 */
  uint8_t side;                  /* byte 20 */
  uint8_t current_session_only;  /* byte 21 */
  uint8_t request_trading_lock;  /* byte 22 */
} MassCancelOrderMessage;

/* any Mass Cancel Order Message at all: every byte one the checker chooses */
static void any_mass_cancel_order_message(MassCancelOrderMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->correlation_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->limit_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->instrument_id[i] = arbitrary(); }
  record->side = arbitrary();
  record->current_session_only = arbitrary();
  record->request_trading_lock = arbitrary();
}

/* Mass Cancel Order Message to the wire: 23 bytes from at, returning where the next byte goes */
static size_t encode_mass_cancel_order_message(const MassCancelOrderMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->correlation_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->limit_price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument_id[i]; }
  wire[at++] = record->side;
  wire[at++] = record->current_session_only;
  wire[at++] = record->request_trading_lock;

  return at;
}

/* Mass Cancel Order Message off the wire: 23 bytes from at, returning where the next byte lies */
static size_t decode_mass_cancel_order_message(MassCancelOrderMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->correlation_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->limit_price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->instrument_id[i] = wire[at++]; }
  record->side = wire[at++];
  record->current_session_only = wire[at++];
  record->request_trading_lock = wire[at++];

  return at;
}

/* what was read of Mass Cancel Order Message is what was written, byte for byte */
static void equal_mass_cancel_order_message(const MassCancelOrderMessage *read, const MassCancelOrderMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->correlation_id[i] == written->correlation_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->limit_price[i] == written->limit_price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->instrument_id[i] == written->instrument_id[i]); }
  assert(read->side == written->side);
  assert(read->current_session_only == written->current_session_only);
  assert(read->request_trading_lock == written->request_trading_lock);
}

/* Mass Cancel Order Message: written and read back, then read and written back */
static void check_mass_cancel_order_message(void) {
  MassCancelOrderMessage sent;
  MassCancelOrderMessage got;
  uint8_t wire[23];
  uint8_t again[23];

  any_mass_cancel_order_message(&sent);
  assert(encode_mass_cancel_order_message(&sent, wire, 0) == 23);
  assert(decode_mass_cancel_order_message(&got, wire, 0) == 23);
  equal_mass_cancel_order_message(&got, &sent);

  for (size_t i = 0; i < 23; i++) { wire[i] = arbitrary(); }
  assert(decode_mass_cancel_order_message(&got, wire, 0) == 23);
  assert(encode_mass_cancel_order_message(&got, again, 0) == 23);
  for (size_t i = 0; i < 23; i++) { assert(again[i] == wire[i]); }
}

/* ---- Mass Cancel Order Ack Message: 30 bytes --------------------------------- */

/* MassCancelOrderAckMessage */
typedef struct {
  uint8_t timestamp[8];          /* bytes 0 to 7 */
  uint8_t exec_id[8];            /* bytes 8 to 15 */
  uint8_t correlation_id[8];     /* bytes 16 to 23 */
  uint8_t canceled_count[4];     /* bytes 24 to 27 */
  uint8_t only_current_session;  /* byte 28 */
  uint8_t trading_lock_applied;  /* byte 29 */
} MassCancelOrderAckMessage;

/* any Mass Cancel Order Ack Message at all: every byte one the checker chooses */
static void any_mass_cancel_order_ack_message(MassCancelOrderAckMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->exec_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->correlation_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->canceled_count[i] = arbitrary(); }
  record->only_current_session = arbitrary();
  record->trading_lock_applied = arbitrary();
}

/* Mass Cancel Order Ack Message to the wire: 30 bytes from at, returning where the next byte goes */
static size_t encode_mass_cancel_order_ack_message(const MassCancelOrderAckMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->exec_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->correlation_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->canceled_count[i]; }
  wire[at++] = record->only_current_session;
  wire[at++] = record->trading_lock_applied;

  return at;
}

/* Mass Cancel Order Ack Message off the wire: 30 bytes from at, returning where the next byte lies */
static size_t decode_mass_cancel_order_ack_message(MassCancelOrderAckMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->exec_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->correlation_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->canceled_count[i] = wire[at++]; }
  record->only_current_session = wire[at++];
  record->trading_lock_applied = wire[at++];

  return at;
}

/* what was read of Mass Cancel Order Ack Message is what was written, byte for byte */
static void equal_mass_cancel_order_ack_message(const MassCancelOrderAckMessage *read, const MassCancelOrderAckMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->exec_id[i] == written->exec_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->correlation_id[i] == written->correlation_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->canceled_count[i] == written->canceled_count[i]); }
  assert(read->only_current_session == written->only_current_session);
  assert(read->trading_lock_applied == written->trading_lock_applied);
}

/* Mass Cancel Order Ack Message: written and read back, then read and written back */
static void check_mass_cancel_order_ack_message(void) {
  MassCancelOrderAckMessage sent;
  MassCancelOrderAckMessage got;
  uint8_t wire[30];
  uint8_t again[30];

  any_mass_cancel_order_ack_message(&sent);
  assert(encode_mass_cancel_order_ack_message(&sent, wire, 0) == 30);
  assert(decode_mass_cancel_order_ack_message(&got, wire, 0) == 30);
  equal_mass_cancel_order_ack_message(&got, &sent);

  for (size_t i = 0; i < 30; i++) { wire[i] = arbitrary(); }
  assert(decode_mass_cancel_order_ack_message(&got, wire, 0) == 30);
  assert(encode_mass_cancel_order_ack_message(&got, again, 0) == 30);
  for (size_t i = 0; i < 30; i++) { assert(again[i] == wire[i]); }
}

/* ---- Mass Cancel Order Reject Message: 48 bytes ------------------------------ */

/* MassCancelOrderRejectMessage */
typedef struct {
  uint8_t timestamp[8];       /* bytes 0 to 7 */
  uint8_t correlation_id[8];  /* bytes 8 to 15 */
  uint8_t error_message[32];  /* bytes 16 to 47 */
} MassCancelOrderRejectMessage;

/* any Mass Cancel Order Reject Message at all: every byte one the checker chooses */
static void any_mass_cancel_order_reject_message(MassCancelOrderRejectMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->correlation_id[i] = arbitrary(); }
  for (size_t i = 0; i < 32; i++) { record->error_message[i] = arbitrary(); }
}

/* Mass Cancel Order Reject Message to the wire: 48 bytes from at, returning where the next byte goes */
static size_t encode_mass_cancel_order_reject_message(const MassCancelOrderRejectMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->correlation_id[i]; }
  for (size_t i = 0; i < 32; i++) { wire[at++] = record->error_message[i]; }

  return at;
}

/* Mass Cancel Order Reject Message off the wire: 48 bytes from at, returning where the next byte lies */
static size_t decode_mass_cancel_order_reject_message(MassCancelOrderRejectMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->correlation_id[i] = wire[at++]; }
  for (size_t i = 0; i < 32; i++) { record->error_message[i] = wire[at++]; }

  return at;
}

/* what was read of Mass Cancel Order Reject Message is what was written, byte for byte */
static void equal_mass_cancel_order_reject_message(const MassCancelOrderRejectMessage *read, const MassCancelOrderRejectMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->correlation_id[i] == written->correlation_id[i]); }
  for (size_t i = 0; i < 32; i++) { assert(read->error_message[i] == written->error_message[i]); }
}

/* Mass Cancel Order Reject Message: written and read back, then read and written back */
static void check_mass_cancel_order_reject_message(void) {
  MassCancelOrderRejectMessage sent;
  MassCancelOrderRejectMessage got;
  uint8_t wire[48];
  uint8_t again[48];

  any_mass_cancel_order_reject_message(&sent);
  assert(encode_mass_cancel_order_reject_message(&sent, wire, 0) == 48);
  assert(decode_mass_cancel_order_reject_message(&got, wire, 0) == 48);
  equal_mass_cancel_order_reject_message(&got, &sent);

  for (size_t i = 0; i < 48; i++) { wire[i] = arbitrary(); }
  assert(decode_mass_cancel_order_reject_message(&got, wire, 0) == 48);
  assert(encode_mass_cancel_order_reject_message(&got, again, 0) == 48);
  for (size_t i = 0; i < 48; i++) { assert(again[i] == wire[i]); }
}

/* ---- Unlock Trading Message: 9 bytes ----------------------------------------- */

/* UnlockTradingMessage */
typedef struct {
  uint8_t correlation_id[8];     /* bytes 0 to 7 */
  uint8_t current_session_only;  /* byte 8 */
} UnlockTradingMessage;

/* any Unlock Trading Message at all: every byte one the checker chooses */
static void any_unlock_trading_message(UnlockTradingMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->correlation_id[i] = arbitrary(); }
  record->current_session_only = arbitrary();
}

/* Unlock Trading Message to the wire: 9 bytes from at, returning where the next byte goes */
static size_t encode_unlock_trading_message(const UnlockTradingMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->correlation_id[i]; }
  wire[at++] = record->current_session_only;

  return at;
}

/* Unlock Trading Message off the wire: 9 bytes from at, returning where the next byte lies */
static size_t decode_unlock_trading_message(UnlockTradingMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->correlation_id[i] = wire[at++]; }
  record->current_session_only = wire[at++];

  return at;
}

/* what was read of Unlock Trading Message is what was written, byte for byte */
static void equal_unlock_trading_message(const UnlockTradingMessage *read, const UnlockTradingMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->correlation_id[i] == written->correlation_id[i]); }
  assert(read->current_session_only == written->current_session_only);
}

/* Unlock Trading Message: written and read back, then read and written back */
static void check_unlock_trading_message(void) {
  UnlockTradingMessage sent;
  UnlockTradingMessage got;
  uint8_t wire[9];
  uint8_t again[9];

  any_unlock_trading_message(&sent);
  assert(encode_unlock_trading_message(&sent, wire, 0) == 9);
  assert(decode_unlock_trading_message(&got, wire, 0) == 9);
  equal_unlock_trading_message(&got, &sent);

  for (size_t i = 0; i < 9; i++) { wire[i] = arbitrary(); }
  assert(decode_unlock_trading_message(&got, wire, 0) == 9);
  assert(encode_unlock_trading_message(&got, again, 0) == 9);
  for (size_t i = 0; i < 9; i++) { assert(again[i] == wire[i]); }
}

/* ---- Unlock Trading Ack Message: 20 bytes ------------------------------------ */

/* UnlockTradingAckMessage */
typedef struct {
  uint8_t timestamp[8];           /* bytes 0 to 7 */
  uint8_t correlation_id[8];      /* bytes 8 to 15 */
  uint8_t num_users_affected[4];  /* bytes 16 to 19 */
} UnlockTradingAckMessage;

/* any Unlock Trading Ack Message at all: every byte one the checker chooses */
static void any_unlock_trading_ack_message(UnlockTradingAckMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->correlation_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->num_users_affected[i] = arbitrary(); }
}

/* Unlock Trading Ack Message to the wire: 20 bytes from at, returning where the next byte goes */
static size_t encode_unlock_trading_ack_message(const UnlockTradingAckMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->correlation_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->num_users_affected[i]; }

  return at;
}

/* Unlock Trading Ack Message off the wire: 20 bytes from at, returning where the next byte lies */
static size_t decode_unlock_trading_ack_message(UnlockTradingAckMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->correlation_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->num_users_affected[i] = wire[at++]; }

  return at;
}

/* what was read of Unlock Trading Ack Message is what was written, byte for byte */
static void equal_unlock_trading_ack_message(const UnlockTradingAckMessage *read, const UnlockTradingAckMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->correlation_id[i] == written->correlation_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->num_users_affected[i] == written->num_users_affected[i]); }
}

/* Unlock Trading Ack Message: written and read back, then read and written back */
static void check_unlock_trading_ack_message(void) {
  UnlockTradingAckMessage sent;
  UnlockTradingAckMessage got;
  uint8_t wire[20];
  uint8_t again[20];

  any_unlock_trading_ack_message(&sent);
  assert(encode_unlock_trading_ack_message(&sent, wire, 0) == 20);
  assert(decode_unlock_trading_ack_message(&got, wire, 0) == 20);
  equal_unlock_trading_ack_message(&got, &sent);

  for (size_t i = 0; i < 20; i++) { wire[i] = arbitrary(); }
  assert(decode_unlock_trading_ack_message(&got, wire, 0) == 20);
  assert(encode_unlock_trading_ack_message(&got, again, 0) == 20);
  for (size_t i = 0; i < 20; i++) { assert(again[i] == wire[i]); }
}

/* ---- Unlock Trading Reject Message: 48 bytes --------------------------------- */

/* UnlockTradingRejectMessage */
typedef struct {
  uint8_t timestamp[8];       /* bytes 0 to 7 */
  uint8_t correlation_id[8];  /* bytes 8 to 15 */
  uint8_t error_message[32];  /* bytes 16 to 47 */
} UnlockTradingRejectMessage;

/* any Unlock Trading Reject Message at all: every byte one the checker chooses */
static void any_unlock_trading_reject_message(UnlockTradingRejectMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->correlation_id[i] = arbitrary(); }
  for (size_t i = 0; i < 32; i++) { record->error_message[i] = arbitrary(); }
}

/* Unlock Trading Reject Message to the wire: 48 bytes from at, returning where the next byte goes */
static size_t encode_unlock_trading_reject_message(const UnlockTradingRejectMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->correlation_id[i]; }
  for (size_t i = 0; i < 32; i++) { wire[at++] = record->error_message[i]; }

  return at;
}

/* Unlock Trading Reject Message off the wire: 48 bytes from at, returning where the next byte lies */
static size_t decode_unlock_trading_reject_message(UnlockTradingRejectMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->correlation_id[i] = wire[at++]; }
  for (size_t i = 0; i < 32; i++) { record->error_message[i] = wire[at++]; }

  return at;
}

/* what was read of Unlock Trading Reject Message is what was written, byte for byte */
static void equal_unlock_trading_reject_message(const UnlockTradingRejectMessage *read, const UnlockTradingRejectMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->correlation_id[i] == written->correlation_id[i]); }
  for (size_t i = 0; i < 32; i++) { assert(read->error_message[i] == written->error_message[i]); }
}

/* Unlock Trading Reject Message: written and read back, then read and written back */
static void check_unlock_trading_reject_message(void) {
  UnlockTradingRejectMessage sent;
  UnlockTradingRejectMessage got;
  uint8_t wire[48];
  uint8_t again[48];

  any_unlock_trading_reject_message(&sent);
  assert(encode_unlock_trading_reject_message(&sent, wire, 0) == 48);
  assert(decode_unlock_trading_reject_message(&got, wire, 0) == 48);
  equal_unlock_trading_reject_message(&got, &sent);

  for (size_t i = 0; i < 48; i++) { wire[i] = arbitrary(); }
  assert(decode_unlock_trading_reject_message(&got, wire, 0) == 48);
  assert(encode_unlock_trading_reject_message(&got, again, 0) == 48);
  for (size_t i = 0; i < 48; i++) { assert(again[i] == wire[i]); }
}

/* ---- Order Filled Message: 81 bytes ------------------------------------------ */

/* OrderFilledMessage */
typedef struct {
  uint8_t timestamp[8];        /* bytes 0 to 7 */
  uint8_t exec_id[8];          /* bytes 8 to 15 */
  uint8_t match_id[8];         /* bytes 16 to 23 */
  uint8_t client_order_id[8];  /* bytes 24 to 31 */
  uint8_t correlation_id[8];   /* bytes 32 to 39 */
  uint8_t order_id[8];         /* bytes 40 to 47 */
  uint8_t filled_vwap[8];      /* bytes 48 to 55 */
  uint8_t total_filled[4];     /* bytes 56 to 59 */
  uint8_t available_qty[4];    /* bytes 60 to 63 */
  uint8_t fill_price[8];       /* bytes 64 to 71 */
  uint8_t fill_qty[4];         /* bytes 72 to 75 */
  uint8_t instrument_id[4];    /* bytes 76 to 79 */
  uint8_t is_aggressor;        /* byte 80 */
} OrderFilledMessage;

/* any Order Filled Message at all: every byte one the checker chooses */
static void any_order_filled_message(OrderFilledMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->exec_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->match_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->client_order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->correlation_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->filled_vwap[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->total_filled[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->available_qty[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->fill_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->fill_qty[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->instrument_id[i] = arbitrary(); }
  record->is_aggressor = arbitrary();
}

/* Order Filled Message to the wire: 81 bytes from at, returning where the next byte goes */
static size_t encode_order_filled_message(const OrderFilledMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->exec_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->match_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->client_order_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->correlation_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->filled_vwap[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->total_filled[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->available_qty[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->fill_price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->fill_qty[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument_id[i]; }
  wire[at++] = record->is_aggressor;

  return at;
}

/* Order Filled Message off the wire: 81 bytes from at, returning where the next byte lies */
static size_t decode_order_filled_message(OrderFilledMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->exec_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->match_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->client_order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->correlation_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->filled_vwap[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->total_filled[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->available_qty[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->fill_price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->fill_qty[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->instrument_id[i] = wire[at++]; }
  record->is_aggressor = wire[at++];

  return at;
}

/* what was read of Order Filled Message is what was written, byte for byte */
static void equal_order_filled_message(const OrderFilledMessage *read, const OrderFilledMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->exec_id[i] == written->exec_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->match_id[i] == written->match_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->client_order_id[i] == written->client_order_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->correlation_id[i] == written->correlation_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->order_id[i] == written->order_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->filled_vwap[i] == written->filled_vwap[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->total_filled[i] == written->total_filled[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->available_qty[i] == written->available_qty[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->fill_price[i] == written->fill_price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->fill_qty[i] == written->fill_qty[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->instrument_id[i] == written->instrument_id[i]); }
  assert(read->is_aggressor == written->is_aggressor);
}

/* Order Filled Message: written and read back, then read and written back */
static void check_order_filled_message(void) {
  OrderFilledMessage sent;
  OrderFilledMessage got;
  uint8_t wire[81];
  uint8_t again[81];

  any_order_filled_message(&sent);
  assert(encode_order_filled_message(&sent, wire, 0) == 81);
  assert(decode_order_filled_message(&got, wire, 0) == 81);
  equal_order_filled_message(&got, &sent);

  for (size_t i = 0; i < 81; i++) { wire[i] = arbitrary(); }
  assert(decode_order_filled_message(&got, wire, 0) == 81);
  assert(encode_order_filled_message(&got, again, 0) == 81);
  for (size_t i = 0; i < 81; i++) { assert(again[i] == wire[i]); }
}

/* ---- Spread Order Filled Message: 97 bytes ----------------------------------- */

/* SpreadOrderFilledMessage */
typedef struct {
  uint8_t timestamp[8];         /* bytes 0 to 7 */
  uint8_t exec_id[8];           /* bytes 8 to 15 */
  uint8_t match_id[8];          /* bytes 16 to 23 */
  uint8_t client_order_id[8];   /* bytes 24 to 31 */
  uint8_t correlation_id[8];    /* bytes 32 to 39 */
  uint8_t order_id[8];          /* bytes 40 to 47 */
  uint8_t filled_vwap[8];       /* bytes 48 to 55 */
  uint8_t total_filled[4];      /* bytes 56 to 59 */
  uint8_t available_qty[4];     /* bytes 60 to 63 */
  uint8_t fill_price[8];        /* bytes 64 to 71 */
  uint8_t leg_1_fill_price[8];  /* bytes 72 to 79 */
  uint8_t leg_2_fill_price[8];  /* bytes 80 to 87 */
  uint8_t fill_qty[4];          /* bytes 88 to 91 */
  uint8_t instrument_id[4];     /* bytes 92 to 95 */
  uint8_t is_aggressor;         /* byte 96 */
} SpreadOrderFilledMessage;

/* any Spread Order Filled Message at all: every byte one the checker chooses */
static void any_spread_order_filled_message(SpreadOrderFilledMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->exec_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->match_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->client_order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->correlation_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->filled_vwap[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->total_filled[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->available_qty[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->fill_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->leg_1_fill_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->leg_2_fill_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->fill_qty[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->instrument_id[i] = arbitrary(); }
  record->is_aggressor = arbitrary();
}

/* Spread Order Filled Message to the wire: 97 bytes from at, returning where the next byte goes */
static size_t encode_spread_order_filled_message(const SpreadOrderFilledMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->exec_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->match_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->client_order_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->correlation_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->filled_vwap[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->total_filled[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->available_qty[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->fill_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->leg_1_fill_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->leg_2_fill_price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->fill_qty[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument_id[i]; }
  wire[at++] = record->is_aggressor;

  return at;
}

/* Spread Order Filled Message off the wire: 97 bytes from at, returning where the next byte lies */
static size_t decode_spread_order_filled_message(SpreadOrderFilledMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->exec_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->match_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->client_order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->correlation_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->filled_vwap[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->total_filled[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->available_qty[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->fill_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->leg_1_fill_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->leg_2_fill_price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->fill_qty[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->instrument_id[i] = wire[at++]; }
  record->is_aggressor = wire[at++];

  return at;
}

/* what was read of Spread Order Filled Message is what was written, byte for byte */
static void equal_spread_order_filled_message(const SpreadOrderFilledMessage *read, const SpreadOrderFilledMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->exec_id[i] == written->exec_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->match_id[i] == written->match_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->client_order_id[i] == written->client_order_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->correlation_id[i] == written->correlation_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->order_id[i] == written->order_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->filled_vwap[i] == written->filled_vwap[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->total_filled[i] == written->total_filled[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->available_qty[i] == written->available_qty[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->fill_price[i] == written->fill_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->leg_1_fill_price[i] == written->leg_1_fill_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->leg_2_fill_price[i] == written->leg_2_fill_price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->fill_qty[i] == written->fill_qty[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->instrument_id[i] == written->instrument_id[i]); }
  assert(read->is_aggressor == written->is_aggressor);
}

/* Spread Order Filled Message: written and read back, then read and written back */
static void check_spread_order_filled_message(void) {
  SpreadOrderFilledMessage sent;
  SpreadOrderFilledMessage got;
  uint8_t wire[97];
  uint8_t again[97];

  any_spread_order_filled_message(&sent);
  assert(encode_spread_order_filled_message(&sent, wire, 0) == 97);
  assert(decode_spread_order_filled_message(&got, wire, 0) == 97);
  equal_spread_order_filled_message(&got, &sent);

  for (size_t i = 0; i < 97; i++) { wire[i] = arbitrary(); }
  assert(decode_spread_order_filled_message(&got, wire, 0) == 97);
  assert(encode_spread_order_filled_message(&got, again, 0) == 97);
  for (size_t i = 0; i < 97; i++) { assert(again[i] == wire[i]); }
}

/* ---- Last Exec Id Request Message: 8 bytes ----------------------------------- */

/* LastExecIdRequestMessage */
typedef struct {
  uint8_t correlation_id[8];  /* bytes 0 to 7 */
} LastExecIdRequestMessage;

/* any Last Exec Id Request Message at all: every byte one the checker chooses */
static void any_last_exec_id_request_message(LastExecIdRequestMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->correlation_id[i] = arbitrary(); }
}

/* Last Exec Id Request Message to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_last_exec_id_request_message(const LastExecIdRequestMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->correlation_id[i]; }

  return at;
}

/* Last Exec Id Request Message off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_last_exec_id_request_message(LastExecIdRequestMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->correlation_id[i] = wire[at++]; }

  return at;
}

/* what was read of Last Exec Id Request Message is what was written, byte for byte */
static void equal_last_exec_id_request_message(const LastExecIdRequestMessage *read, const LastExecIdRequestMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->correlation_id[i] == written->correlation_id[i]); }
}

/* Last Exec Id Request Message: written and read back, then read and written back */
static void check_last_exec_id_request_message(void) {
  LastExecIdRequestMessage sent;
  LastExecIdRequestMessage got;
  uint8_t wire[8];
  uint8_t again[8];

  any_last_exec_id_request_message(&sent);
  assert(encode_last_exec_id_request_message(&sent, wire, 0) == 8);
  assert(decode_last_exec_id_request_message(&got, wire, 0) == 8);
  equal_last_exec_id_request_message(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_last_exec_id_request_message(&got, wire, 0) == 8);
  assert(encode_last_exec_id_request_message(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Last Exec Id Message: 24 bytes ------------------------------------------ */

/* LastExecIdMessage */
typedef struct {
  uint8_t timestamp[8];       /* bytes 0 to 7 */
  uint8_t last_exec_id[8];    /* bytes 8 to 15 */
  uint8_t correlation_id[8];  /* bytes 16 to 23 */
} LastExecIdMessage;

/* any Last Exec Id Message at all: every byte one the checker chooses */
static void any_last_exec_id_message(LastExecIdMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->last_exec_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->correlation_id[i] = arbitrary(); }
}

/* Last Exec Id Message to the wire: 24 bytes from at, returning where the next byte goes */
static size_t encode_last_exec_id_message(const LastExecIdMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->last_exec_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->correlation_id[i]; }

  return at;
}

/* Last Exec Id Message off the wire: 24 bytes from at, returning where the next byte lies */
static size_t decode_last_exec_id_message(LastExecIdMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->last_exec_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->correlation_id[i] = wire[at++]; }

  return at;
}

/* what was read of Last Exec Id Message is what was written, byte for byte */
static void equal_last_exec_id_message(const LastExecIdMessage *read, const LastExecIdMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->last_exec_id[i] == written->last_exec_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->correlation_id[i] == written->correlation_id[i]); }
}

/* Last Exec Id Message: written and read back, then read and written back */
static void check_last_exec_id_message(void) {
  LastExecIdMessage sent;
  LastExecIdMessage got;
  uint8_t wire[24];
  uint8_t again[24];

  any_last_exec_id_message(&sent);
  assert(encode_last_exec_id_message(&sent, wire, 0) == 24);
  assert(decode_last_exec_id_message(&got, wire, 0) == 24);
  equal_last_exec_id_message(&got, &sent);

  for (size_t i = 0; i < 24; i++) { wire[i] = arbitrary(); }
  assert(decode_last_exec_id_message(&got, wire, 0) == 24);
  assert(encode_last_exec_id_message(&got, again, 0) == 24);
  for (size_t i = 0; i < 24; i++) { assert(again[i] == wire[i]); }
}

/* ---- Event Resend Request Message: 24 bytes ---------------------------------- */

/* EventResendRequestMessage */
typedef struct {
  uint8_t correlation_id[8];  /* bytes 0 to 7 */
  uint8_t begin_exec_id[8];   /* bytes 8 to 15 */
  uint8_t end_exec_id[8];     /* bytes 16 to 23 */
} EventResendRequestMessage;

/* any Event Resend Request Message at all: every byte one the checker chooses */
static void any_event_resend_request_message(EventResendRequestMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->correlation_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->begin_exec_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->end_exec_id[i] = arbitrary(); }
}

/* Event Resend Request Message to the wire: 24 bytes from at, returning where the next byte goes */
static size_t encode_event_resend_request_message(const EventResendRequestMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->correlation_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->begin_exec_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->end_exec_id[i]; }

  return at;
}

/* Event Resend Request Message off the wire: 24 bytes from at, returning where the next byte lies */
static size_t decode_event_resend_request_message(EventResendRequestMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->correlation_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->begin_exec_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->end_exec_id[i] = wire[at++]; }

  return at;
}

/* what was read of Event Resend Request Message is what was written, byte for byte */
static void equal_event_resend_request_message(const EventResendRequestMessage *read, const EventResendRequestMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->correlation_id[i] == written->correlation_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->begin_exec_id[i] == written->begin_exec_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->end_exec_id[i] == written->end_exec_id[i]); }
}

/* Event Resend Request Message: written and read back, then read and written back */
static void check_event_resend_request_message(void) {
  EventResendRequestMessage sent;
  EventResendRequestMessage got;
  uint8_t wire[24];
  uint8_t again[24];

  any_event_resend_request_message(&sent);
  assert(encode_event_resend_request_message(&sent, wire, 0) == 24);
  assert(decode_event_resend_request_message(&got, wire, 0) == 24);
  equal_event_resend_request_message(&got, &sent);

  for (size_t i = 0; i < 24; i++) { wire[i] = arbitrary(); }
  assert(decode_event_resend_request_message(&got, wire, 0) == 24);
  assert(encode_event_resend_request_message(&got, again, 0) == 24);
  for (size_t i = 0; i < 24; i++) { assert(again[i] == wire[i]); }
}

/* ---- Event Resend Complete Message: 12 bytes --------------------------------- */

/* EventResendCompleteMessage */
typedef struct {
  uint8_t correlation_id[8];      /* bytes 0 to 7 */
  uint8_t resent_event_count[4];  /* bytes 8 to 11 */
} EventResendCompleteMessage;

/* any Event Resend Complete Message at all: every byte one the checker chooses */
static void any_event_resend_complete_message(EventResendCompleteMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->correlation_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->resent_event_count[i] = arbitrary(); }
}

/* Event Resend Complete Message to the wire: 12 bytes from at, returning where the next byte goes */
static size_t encode_event_resend_complete_message(const EventResendCompleteMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->correlation_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->resent_event_count[i]; }

  return at;
}

/* Event Resend Complete Message off the wire: 12 bytes from at, returning where the next byte lies */
static size_t decode_event_resend_complete_message(EventResendCompleteMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->correlation_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->resent_event_count[i] = wire[at++]; }

  return at;
}

/* what was read of Event Resend Complete Message is what was written, byte for byte */
static void equal_event_resend_complete_message(const EventResendCompleteMessage *read, const EventResendCompleteMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->correlation_id[i] == written->correlation_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->resent_event_count[i] == written->resent_event_count[i]); }
}

/* Event Resend Complete Message: written and read back, then read and written back */
static void check_event_resend_complete_message(void) {
  EventResendCompleteMessage sent;
  EventResendCompleteMessage got;
  uint8_t wire[12];
  uint8_t again[12];

  any_event_resend_complete_message(&sent);
  assert(encode_event_resend_complete_message(&sent, wire, 0) == 12);
  assert(decode_event_resend_complete_message(&got, wire, 0) == 12);
  equal_event_resend_complete_message(&got, &sent);

  for (size_t i = 0; i < 12; i++) { wire[i] = arbitrary(); }
  assert(decode_event_resend_complete_message(&got, wire, 0) == 12);
  assert(encode_event_resend_complete_message(&got, again, 0) == 12);
  for (size_t i = 0; i < 12; i++) { assert(again[i] == wire[i]); }
}

/* ---- Event Resend Reject Message: 32 bytes ----------------------------------- */

/* EventResendRejectMessage */
typedef struct {
  uint8_t correlation_id[8];                /* bytes 0 to 7 */
  uint8_t resend_reject_reason;             /* byte 8 */
  uint8_t event_resend_reject_details[23];  /* bytes 9 to 31 */
} EventResendRejectMessage;

/* any Event Resend Reject Message at all: every byte one the checker chooses */
static void any_event_resend_reject_message(EventResendRejectMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->correlation_id[i] = arbitrary(); }
  record->resend_reject_reason = arbitrary();
  for (size_t i = 0; i < 23; i++) { record->event_resend_reject_details[i] = arbitrary(); }
}

/* Event Resend Reject Message to the wire: 32 bytes from at, returning where the next byte goes */
static size_t encode_event_resend_reject_message(const EventResendRejectMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->correlation_id[i]; }
  wire[at++] = record->resend_reject_reason;
  for (size_t i = 0; i < 23; i++) { wire[at++] = record->event_resend_reject_details[i]; }

  return at;
}

/* Event Resend Reject Message off the wire: 32 bytes from at, returning where the next byte lies */
static size_t decode_event_resend_reject_message(EventResendRejectMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->correlation_id[i] = wire[at++]; }
  record->resend_reject_reason = wire[at++];
  for (size_t i = 0; i < 23; i++) { record->event_resend_reject_details[i] = wire[at++]; }

  return at;
}

/* what was read of Event Resend Reject Message is what was written, byte for byte */
static void equal_event_resend_reject_message(const EventResendRejectMessage *read, const EventResendRejectMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->correlation_id[i] == written->correlation_id[i]); }
  assert(read->resend_reject_reason == written->resend_reject_reason);
  for (size_t i = 0; i < 23; i++) { assert(read->event_resend_reject_details[i] == written->event_resend_reject_details[i]); }
}

/* Event Resend Reject Message: written and read back, then read and written back */
static void check_event_resend_reject_message(void) {
  EventResendRejectMessage sent;
  EventResendRejectMessage got;
  uint8_t wire[32];
  uint8_t again[32];

  any_event_resend_reject_message(&sent);
  assert(encode_event_resend_reject_message(&sent, wire, 0) == 32);
  assert(decode_event_resend_reject_message(&got, wire, 0) == 32);
  equal_event_resend_reject_message(&got, &sent);

  for (size_t i = 0; i < 32; i++) { wire[i] = arbitrary(); }
  assert(decode_event_resend_reject_message(&got, wire, 0) == 32);
  assert(encode_event_resend_reject_message(&got, again, 0) == 32);
  for (size_t i = 0; i < 32; i++) { assert(again[i] == wire[i]); }
}

/* ---- What esbmc checks ------------------------------------------------------- */

/* every record of the protocol, each on its own buffers */
static void checks(void) {
  check_logon_message();
  check_logon_conf_message();
  check_logout_message();
  check_logged_out_message();
  check_heartbeat_message();
  check_test_request_message();
  check_resend_request_message();
  check_gap_fill_message();
  check_instrument_info_request_message();
  check_instrument_info_message();
  check_set_account_message();
  check_set_trader_message();
  check_set_ack_message();
  check_new_order_message();
  check_order_entered_message();
  check_replace_order_message();
  check_stream_order_message();
  check_order_reject_message();
  check_order_replaced_message();
  check_cancel_order_message();
  check_order_canceled_message();
  check_cancel_order_reject_message();
  check_mass_cancel_order_message();
  check_mass_cancel_order_ack_message();
  check_mass_cancel_order_reject_message();
  check_unlock_trading_message();
  check_unlock_trading_ack_message();
  check_unlock_trading_reject_message();
  check_order_filled_message();
  check_spread_order_filled_message();
  check_last_exec_id_request_message();
  check_last_exec_id_message();
  check_event_resend_request_message();
  check_event_resend_complete_message();
  check_event_resend_reject_message();
}

int main(void) {
#ifdef CONCRETE
  for (pattern = 0; pattern < 4; pattern++) { checks(); }
#else
  checks();
#endif

  return 0;
}
