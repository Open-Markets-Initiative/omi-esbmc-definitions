// coinbase/coinbasederivatives/session/CoinbaseDerivatives_Session_v1_2.c
/*
 * Coinbase
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
  uint8_t reason_string_64[64];  /* bytes 0 to 63 */
} LogoutMessage;

/* any Logout Message at all: every byte one the checker chooses */
static void any_logout_message(LogoutMessage *record) {
  for (size_t i = 0; i < 64; i++) { record->reason_string_64[i] = arbitrary(); }
}

/* Logout Message to the wire: 64 bytes from at, returning where the next byte goes */
static size_t encode_logout_message(const LogoutMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 64; i++) { wire[at++] = record->reason_string_64[i]; }

  return at;
}

/* Logout Message off the wire: 64 bytes from at, returning where the next byte lies */
static size_t decode_logout_message(LogoutMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 64; i++) { record->reason_string_64[i] = wire[at++]; }

  return at;
}

/* what was read of Logout Message is what was written, byte for byte */
static void equal_logout_message(const LogoutMessage *read, const LogoutMessage *written) {
  for (size_t i = 0; i < 64; i++) { assert(read->reason_string_64[i] == written->reason_string_64[i]); }
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
  uint8_t reason_string_64[64];  /* bytes 0 to 63 */
} LoggedOutMessage;

/* any Logged Out Message at all: every byte one the checker chooses */
static void any_logged_out_message(LoggedOutMessage *record) {
  for (size_t i = 0; i < 64; i++) { record->reason_string_64[i] = arbitrary(); }
}

/* Logged Out Message to the wire: 64 bytes from at, returning where the next byte goes */
static size_t encode_logged_out_message(const LoggedOutMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 64; i++) { wire[at++] = record->reason_string_64[i]; }

  return at;
}

/* Logged Out Message off the wire: 64 bytes from at, returning where the next byte lies */
static size_t decode_logged_out_message(LoggedOutMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 64; i++) { record->reason_string_64[i] = wire[at++]; }

  return at;
}

/* what was read of Logged Out Message is what was written, byte for byte */
static void equal_logged_out_message(const LoggedOutMessage *read, const LoggedOutMessage *written) {
  for (size_t i = 0; i < 64; i++) { assert(read->reason_string_64[i] == written->reason_string_64[i]); }
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

/* ---- Reject Message: 72 bytes ------------------------------------------------ */

/* RejectMessage */
typedef struct {
  uint8_t ref_sequence_number[4];   /* bytes 0 to 3 */
  uint8_t reason_reject_reason[4];  /* bytes 4 to 7 */
  uint8_t details[64];              /* bytes 8 to 71 */
} RejectMessage;

/* any Reject Message at all: every byte one the checker chooses */
static void any_reject_message(RejectMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->ref_sequence_number[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->reason_reject_reason[i] = arbitrary(); }
  for (size_t i = 0; i < 64; i++) { record->details[i] = arbitrary(); }
}

/* Reject Message to the wire: 72 bytes from at, returning where the next byte goes */
static size_t encode_reject_message(const RejectMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->ref_sequence_number[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->reason_reject_reason[i]; }
  for (size_t i = 0; i < 64; i++) { wire[at++] = record->details[i]; }

  return at;
}

/* Reject Message off the wire: 72 bytes from at, returning where the next byte lies */
static size_t decode_reject_message(RejectMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->ref_sequence_number[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->reason_reject_reason[i] = wire[at++]; }
  for (size_t i = 0; i < 64; i++) { record->details[i] = wire[at++]; }

  return at;
}

/* what was read of Reject Message is what was written, byte for byte */
static void equal_reject_message(const RejectMessage *read, const RejectMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->ref_sequence_number[i] == written->ref_sequence_number[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->reason_reject_reason[i] == written->reason_reject_reason[i]); }
  for (size_t i = 0; i < 64; i++) { assert(read->details[i] == written->details[i]); }
}

/* Reject Message: written and read back, then read and written back */
static void check_reject_message(void) {
  RejectMessage sent;
  RejectMessage got;
  uint8_t wire[72];
  uint8_t again[72];

  any_reject_message(&sent);
  assert(encode_reject_message(&sent, wire, 0) == 72);
  assert(decode_reject_message(&got, wire, 0) == 72);
  equal_reject_message(&got, &sent);

  for (size_t i = 0; i < 72; i++) { wire[i] = arbitrary(); }
  assert(decode_reject_message(&got, wire, 0) == 72);
  assert(encode_reject_message(&got, again, 0) == 72);
  for (size_t i = 0; i < 72; i++) { assert(again[i] == wire[i]); }
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
  check_reject_message();
}

int main(void) {
#ifdef CONCRETE
  for (pattern = 0; pattern < 4; pattern++) { checks(); }
#else
  checks();
#endif

  return 0;
}
