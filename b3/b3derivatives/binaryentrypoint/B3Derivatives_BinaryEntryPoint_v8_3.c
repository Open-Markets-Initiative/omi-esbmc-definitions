// b3/b3derivatives/binaryentrypoint/B3Derivatives_BinaryEntryPoint_v8_3.c
/*
 * Brasil, Bolsa, Balcão Binary Entry Point
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

/* ---- Simple Open Framing Header: 4 bytes ------------------------------------- */

/* Simple Open Framing Header */
typedef struct {
  uint8_t message_length[2];  /* bytes 0 to 1 */
  uint8_t encoding_type[2];   /* bytes 2 to 3 */
} SimpleOpenFramingHeader;

/* any Simple Open Framing Header at all: every byte one the checker chooses */
static void any_simple_open_framing_header(SimpleOpenFramingHeader *record) {
  for (size_t i = 0; i < 2; i++) { record->message_length[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->encoding_type[i] = arbitrary(); }
}

/* Simple Open Framing Header to the wire: 4 bytes from at, returning where the next byte goes */
static size_t encode_simple_open_framing_header(const SimpleOpenFramingHeader *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->message_length[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->encoding_type[i]; }

  return at;
}

/* Simple Open Framing Header off the wire: 4 bytes from at, returning where the next byte lies */
static size_t decode_simple_open_framing_header(SimpleOpenFramingHeader *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->message_length[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->encoding_type[i] = wire[at++]; }

  return at;
}

/* what was read of Simple Open Framing Header is what was written, byte for byte */
static void equal_simple_open_framing_header(const SimpleOpenFramingHeader *read, const SimpleOpenFramingHeader *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->message_length[i] == written->message_length[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->encoding_type[i] == written->encoding_type[i]); }
}

/* Simple Open Framing Header: written and read back, then read and written back */
static void check_simple_open_framing_header(void) {
  SimpleOpenFramingHeader sent;
  SimpleOpenFramingHeader got;
  uint8_t wire[4];
  uint8_t again[4];

  any_simple_open_framing_header(&sent);
  assert(encode_simple_open_framing_header(&sent, wire, 0) == 4);
  assert(decode_simple_open_framing_header(&got, wire, 0) == 4);
  equal_simple_open_framing_header(&got, &sent);

  for (size_t i = 0; i < 4; i++) { wire[i] = arbitrary(); }
  assert(decode_simple_open_framing_header(&got, wire, 0) == 4);
  assert(encode_simple_open_framing_header(&got, again, 0) == 4);
  for (size_t i = 0; i < 4; i++) { assert(again[i] == wire[i]); }
}

/* ---- Message Header: 8 bytes ------------------------------------------------- */

/* B3 Sbe message header — message identifiers and length of message root */
typedef struct {
  uint8_t block_length[2];  /* bytes 0 to 1 */
  uint8_t template_id[2];   /* bytes 2 to 3 */
  uint8_t schema_id[2];     /* bytes 4 to 5 */
  uint8_t version[2];       /* bytes 6 to 7 */
} MessageHeader;

/* any Message Header at all: every byte one the checker chooses */
static void any_message_header(MessageHeader *record) {
  for (size_t i = 0; i < 2; i++) { record->block_length[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->template_id[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->schema_id[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->version[i] = arbitrary(); }
}

/* Message Header to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_message_header(const MessageHeader *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->block_length[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->template_id[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->schema_id[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->version[i]; }

  return at;
}

/* Message Header off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_message_header(MessageHeader *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->block_length[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->template_id[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->schema_id[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->version[i] = wire[at++]; }

  return at;
}

/* what was read of Message Header is what was written, byte for byte */
static void equal_message_header(const MessageHeader *read, const MessageHeader *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->block_length[i] == written->block_length[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->template_id[i] == written->template_id[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->schema_id[i] == written->schema_id[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->version[i] == written->version[i]); }
}

/* Message Header: written and read back, then read and written back */
static void check_message_header(void) {
  MessageHeader sent;
  MessageHeader got;
  uint8_t wire[8];
  uint8_t again[8];

  any_message_header(&sent);
  assert(encode_message_header(&sent, wire, 0) == 8);
  assert(decode_message_header(&got, wire, 0) == 8);
  equal_message_header(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_message_header(&got, wire, 0) == 8);
  assert(encode_message_header(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Semantic Version: 4 bytes ----------------------------------------------- */

/* NegotiateResponseMessage */
typedef struct {
  uint8_t major_number;  /* byte 0 */
  uint8_t minor_number;  /* byte 1 */
  uint8_t patch_number;  /* byte 2 */
  uint8_t build_number;  /* byte 3 */
} SemanticVersion;

/* any Semantic Version at all: every byte one the checker chooses */
static void any_semantic_version(SemanticVersion *record) {
  record->major_number = arbitrary();
  record->minor_number = arbitrary();
  record->patch_number = arbitrary();
  record->build_number = arbitrary();
}

/* Semantic Version to the wire: 4 bytes from at, returning where the next byte goes */
static size_t encode_semantic_version(const SemanticVersion *record, uint8_t *wire, size_t at) {
  wire[at++] = record->major_number;
  wire[at++] = record->minor_number;
  wire[at++] = record->patch_number;
  wire[at++] = record->build_number;

  return at;
}

/* Semantic Version off the wire: 4 bytes from at, returning where the next byte lies */
static size_t decode_semantic_version(SemanticVersion *record, const uint8_t *wire, size_t at) {
  record->major_number = wire[at++];
  record->minor_number = wire[at++];
  record->patch_number = wire[at++];
  record->build_number = wire[at++];

  return at;
}

/* what was read of Semantic Version is what was written, byte for byte */
static void equal_semantic_version(const SemanticVersion *read, const SemanticVersion *written) {
  assert(read->major_number == written->major_number);
  assert(read->minor_number == written->minor_number);
  assert(read->patch_number == written->patch_number);
  assert(read->build_number == written->build_number);
}

/* Semantic Version: written and read back, then read and written back */
static void check_semantic_version(void) {
  SemanticVersion sent;
  SemanticVersion got;
  uint8_t wire[4];
  uint8_t again[4];

  any_semantic_version(&sent);
  assert(encode_semantic_version(&sent, wire, 0) == 4);
  assert(decode_semantic_version(&got, wire, 0) == 4);
  equal_semantic_version(&got, &sent);

  for (size_t i = 0; i < 4; i++) { wire[i] = arbitrary(); }
  assert(decode_semantic_version(&got, wire, 0) == 4);
  assert(encode_semantic_version(&got, again, 0) == 4);
  for (size_t i = 0; i < 4; i++) { assert(again[i] == wire[i]); }
}

/* ---- Negotiate Response Message: 28 bytes ------------------------------------ */

/* NegotiateResponseMessage */
typedef struct {
  uint8_t session_id[4];             /* bytes 0 to 3 */
  uint8_t session_ver_id[8];         /* bytes 4 to 11 */
  uint8_t request_timestamp[8];      /* bytes 12 to 19 */
  uint8_t entering_firm[4];          /* bytes 20 to 23 */
  SemanticVersion semantic_version;  /* bytes 24 to 27 */
} NegotiateResponseMessage;

/* any Negotiate Response Message at all: every byte one the checker chooses */
static void any_negotiate_response_message(NegotiateResponseMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->session_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->session_ver_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->request_timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->entering_firm[i] = arbitrary(); }
  any_semantic_version(&record->semantic_version);
}

/* Negotiate Response Message to the wire: 28 bytes from at, returning where the next byte goes */
static size_t encode_negotiate_response_message(const NegotiateResponseMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->session_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->session_ver_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->request_timestamp[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->entering_firm[i]; }
  at = encode_semantic_version(&record->semantic_version, wire, at);

  return at;
}

/* Negotiate Response Message off the wire: 28 bytes from at, returning where the next byte lies */
static size_t decode_negotiate_response_message(NegotiateResponseMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->session_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->session_ver_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->request_timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->entering_firm[i] = wire[at++]; }
  at = decode_semantic_version(&record->semantic_version, wire, at);

  return at;
}

/* what was read of Negotiate Response Message is what was written, byte for byte */
static void equal_negotiate_response_message(const NegotiateResponseMessage *read, const NegotiateResponseMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->session_id[i] == written->session_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->session_ver_id[i] == written->session_ver_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->request_timestamp[i] == written->request_timestamp[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->entering_firm[i] == written->entering_firm[i]); }
  equal_semantic_version(&read->semantic_version, &written->semantic_version);
}

/* Negotiate Response Message: written and read back, then read and written back */
static void check_negotiate_response_message(void) {
  NegotiateResponseMessage sent;
  NegotiateResponseMessage got;
  uint8_t wire[28];
  uint8_t again[28];

  any_negotiate_response_message(&sent);
  assert(encode_negotiate_response_message(&sent, wire, 0) == 28);
  assert(decode_negotiate_response_message(&got, wire, 0) == 28);
  equal_negotiate_response_message(&got, &sent);

  for (size_t i = 0; i < 28; i++) { wire[i] = arbitrary(); }
  assert(decode_negotiate_response_message(&got, wire, 0) == 28);
  assert(encode_negotiate_response_message(&got, again, 0) == 28);
  for (size_t i = 0; i < 28; i++) { assert(again[i] == wire[i]); }
}

/* ---- Negotiate Reject Message: 36 bytes -------------------------------------- */

/* NegotiateRejectMessage */
typedef struct {
  uint8_t session_id[4];              /* bytes 0 to 3 */
  uint8_t session_ver_id[8];          /* bytes 4 to 11 */
  uint8_t request_timestamp[8];       /* bytes 12 to 19 */
  uint8_t entering_firm_optional[4];  /* bytes 20 to 23 */
  uint8_t negotiation_reject_code;    /* byte 24 */
  uint8_t offset_25_padding_3[3];     /* bytes 25 to 27 */
  uint8_t current_session_ver_id[8];  /* bytes 28 to 35 */
} NegotiateRejectMessage;

/* any Negotiate Reject Message at all: every byte one the checker chooses */
static void any_negotiate_reject_message(NegotiateRejectMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->session_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->session_ver_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->request_timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->entering_firm_optional[i] = arbitrary(); }
  record->negotiation_reject_code = arbitrary();
  for (size_t i = 0; i < 3; i++) { record->offset_25_padding_3[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->current_session_ver_id[i] = arbitrary(); }
}

/* Negotiate Reject Message to the wire: 36 bytes from at, returning where the next byte goes */
static size_t encode_negotiate_reject_message(const NegotiateRejectMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->session_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->session_ver_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->request_timestamp[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->entering_firm_optional[i]; }
  wire[at++] = record->negotiation_reject_code;
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->offset_25_padding_3[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->current_session_ver_id[i]; }

  return at;
}

/* Negotiate Reject Message off the wire: 36 bytes from at, returning where the next byte lies */
static size_t decode_negotiate_reject_message(NegotiateRejectMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->session_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->session_ver_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->request_timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->entering_firm_optional[i] = wire[at++]; }
  record->negotiation_reject_code = wire[at++];
  for (size_t i = 0; i < 3; i++) { record->offset_25_padding_3[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->current_session_ver_id[i] = wire[at++]; }

  return at;
}

/* what was read of Negotiate Reject Message is what was written, byte for byte */
static void equal_negotiate_reject_message(const NegotiateRejectMessage *read, const NegotiateRejectMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->session_id[i] == written->session_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->session_ver_id[i] == written->session_ver_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->request_timestamp[i] == written->request_timestamp[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->entering_firm_optional[i] == written->entering_firm_optional[i]); }
  assert(read->negotiation_reject_code == written->negotiation_reject_code);
  for (size_t i = 0; i < 3; i++) { assert(read->offset_25_padding_3[i] == written->offset_25_padding_3[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->current_session_ver_id[i] == written->current_session_ver_id[i]); }
}

/* Negotiate Reject Message: written and read back, then read and written back */
static void check_negotiate_reject_message(void) {
  NegotiateRejectMessage sent;
  NegotiateRejectMessage got;
  uint8_t wire[36];
  uint8_t again[36];

  any_negotiate_reject_message(&sent);
  assert(encode_negotiate_reject_message(&sent, wire, 0) == 36);
  assert(decode_negotiate_reject_message(&got, wire, 0) == 36);
  equal_negotiate_reject_message(&got, &sent);

  for (size_t i = 0; i < 36; i++) { wire[i] = arbitrary(); }
  assert(decode_negotiate_reject_message(&got, wire, 0) == 36);
  assert(encode_negotiate_reject_message(&got, again, 0) == 36);
  for (size_t i = 0; i < 36; i++) { assert(again[i] == wire[i]); }
}

/* ---- Establish Ack Message: 36 bytes ----------------------------------------- */

/* EstablishAckMessage */
typedef struct {
  uint8_t session_id[4];            /* bytes 0 to 3 */
  uint8_t session_ver_id[8];        /* bytes 4 to 11 */
  uint8_t request_timestamp[8];     /* bytes 12 to 19 */
  uint8_t keep_alive_interval[8];   /* bytes 20 to 27 */
  uint8_t next_seq_no[4];           /* bytes 28 to 31 */
  uint8_t last_incoming_seq_no[4];  /* bytes 32 to 35 */
} EstablishAckMessage;

/* any Establish Ack Message at all: every byte one the checker chooses */
static void any_establish_ack_message(EstablishAckMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->session_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->session_ver_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->request_timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->keep_alive_interval[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->next_seq_no[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->last_incoming_seq_no[i] = arbitrary(); }
}

/* Establish Ack Message to the wire: 36 bytes from at, returning where the next byte goes */
static size_t encode_establish_ack_message(const EstablishAckMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->session_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->session_ver_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->request_timestamp[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->keep_alive_interval[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->next_seq_no[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->last_incoming_seq_no[i]; }

  return at;
}

/* Establish Ack Message off the wire: 36 bytes from at, returning where the next byte lies */
static size_t decode_establish_ack_message(EstablishAckMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->session_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->session_ver_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->request_timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->keep_alive_interval[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->next_seq_no[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->last_incoming_seq_no[i] = wire[at++]; }

  return at;
}

/* what was read of Establish Ack Message is what was written, byte for byte */
static void equal_establish_ack_message(const EstablishAckMessage *read, const EstablishAckMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->session_id[i] == written->session_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->session_ver_id[i] == written->session_ver_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->request_timestamp[i] == written->request_timestamp[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->keep_alive_interval[i] == written->keep_alive_interval[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->next_seq_no[i] == written->next_seq_no[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->last_incoming_seq_no[i] == written->last_incoming_seq_no[i]); }
}

/* Establish Ack Message: written and read back, then read and written back */
static void check_establish_ack_message(void) {
  EstablishAckMessage sent;
  EstablishAckMessage got;
  uint8_t wire[36];
  uint8_t again[36];

  any_establish_ack_message(&sent);
  assert(encode_establish_ack_message(&sent, wire, 0) == 36);
  assert(decode_establish_ack_message(&got, wire, 0) == 36);
  equal_establish_ack_message(&got, &sent);

  for (size_t i = 0; i < 36; i++) { wire[i] = arbitrary(); }
  assert(decode_establish_ack_message(&got, wire, 0) == 36);
  assert(encode_establish_ack_message(&got, again, 0) == 36);
  for (size_t i = 0; i < 36; i++) { assert(again[i] == wire[i]); }
}

/* ---- Establish Reject Message: 26 bytes -------------------------------------- */

/* EstablishRejectMessage */
typedef struct {
  uint8_t session_id[4];                     /* bytes 0 to 3 */
  uint8_t session_ver_id[8];                 /* bytes 4 to 11 */
  uint8_t request_timestamp[8];              /* bytes 12 to 19 */
  uint8_t establishment_reject_code;         /* byte 20 */
  uint8_t offset_21_padding_1;               /* byte 21 */
  uint8_t last_incoming_seq_no_optional[4];  /* bytes 22 to 25 */
} EstablishRejectMessage;

/* any Establish Reject Message at all: every byte one the checker chooses */
static void any_establish_reject_message(EstablishRejectMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->session_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->session_ver_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->request_timestamp[i] = arbitrary(); }
  record->establishment_reject_code = arbitrary();
  record->offset_21_padding_1 = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->last_incoming_seq_no_optional[i] = arbitrary(); }
}

/* Establish Reject Message to the wire: 26 bytes from at, returning where the next byte goes */
static size_t encode_establish_reject_message(const EstablishRejectMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->session_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->session_ver_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->request_timestamp[i]; }
  wire[at++] = record->establishment_reject_code;
  wire[at++] = record->offset_21_padding_1;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->last_incoming_seq_no_optional[i]; }

  return at;
}

/* Establish Reject Message off the wire: 26 bytes from at, returning where the next byte lies */
static size_t decode_establish_reject_message(EstablishRejectMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->session_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->session_ver_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->request_timestamp[i] = wire[at++]; }
  record->establishment_reject_code = wire[at++];
  record->offset_21_padding_1 = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->last_incoming_seq_no_optional[i] = wire[at++]; }

  return at;
}

/* what was read of Establish Reject Message is what was written, byte for byte */
static void equal_establish_reject_message(const EstablishRejectMessage *read, const EstablishRejectMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->session_id[i] == written->session_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->session_ver_id[i] == written->session_ver_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->request_timestamp[i] == written->request_timestamp[i]); }
  assert(read->establishment_reject_code == written->establishment_reject_code);
  assert(read->offset_21_padding_1 == written->offset_21_padding_1);
  for (size_t i = 0; i < 4; i++) { assert(read->last_incoming_seq_no_optional[i] == written->last_incoming_seq_no_optional[i]); }
}

/* Establish Reject Message: written and read back, then read and written back */
static void check_establish_reject_message(void) {
  EstablishRejectMessage sent;
  EstablishRejectMessage got;
  uint8_t wire[26];
  uint8_t again[26];

  any_establish_reject_message(&sent);
  assert(encode_establish_reject_message(&sent, wire, 0) == 26);
  assert(decode_establish_reject_message(&got, wire, 0) == 26);
  equal_establish_reject_message(&got, &sent);

  for (size_t i = 0; i < 26; i++) { wire[i] = arbitrary(); }
  assert(decode_establish_reject_message(&got, wire, 0) == 26);
  assert(encode_establish_reject_message(&got, again, 0) == 26);
  for (size_t i = 0; i < 26; i++) { assert(again[i] == wire[i]); }
}

/* ---- Terminate Message: 13 bytes --------------------------------------------- */

/* TerminateMessage */
typedef struct {
  uint8_t session_id[4];      /* bytes 0 to 3 */
  uint8_t session_ver_id[8];  /* bytes 4 to 11 */
  uint8_t termination_code;   /* byte 12 */
} TerminateMessage;

/* any Terminate Message at all: every byte one the checker chooses */
static void any_terminate_message(TerminateMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->session_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->session_ver_id[i] = arbitrary(); }
  record->termination_code = arbitrary();
}

/* Terminate Message to the wire: 13 bytes from at, returning where the next byte goes */
static size_t encode_terminate_message(const TerminateMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->session_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->session_ver_id[i]; }
  wire[at++] = record->termination_code;

  return at;
}

/* Terminate Message off the wire: 13 bytes from at, returning where the next byte lies */
static size_t decode_terminate_message(TerminateMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->session_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->session_ver_id[i] = wire[at++]; }
  record->termination_code = wire[at++];

  return at;
}

/* what was read of Terminate Message is what was written, byte for byte */
static void equal_terminate_message(const TerminateMessage *read, const TerminateMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->session_id[i] == written->session_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->session_ver_id[i] == written->session_ver_id[i]); }
  assert(read->termination_code == written->termination_code);
}

/* Terminate Message: written and read back, then read and written back */
static void check_terminate_message(void) {
  TerminateMessage sent;
  TerminateMessage got;
  uint8_t wire[13];
  uint8_t again[13];

  any_terminate_message(&sent);
  assert(encode_terminate_message(&sent, wire, 0) == 13);
  assert(decode_terminate_message(&got, wire, 0) == 13);
  equal_terminate_message(&got, &sent);

  for (size_t i = 0; i < 13; i++) { wire[i] = arbitrary(); }
  assert(decode_terminate_message(&got, wire, 0) == 13);
  assert(encode_terminate_message(&got, again, 0) == 13);
  for (size_t i = 0; i < 13; i++) { assert(again[i] == wire[i]); }
}

/* ---- Not Applied Message: 8 bytes -------------------------------------------- */

/* NotAppliedMessage */
typedef struct {
  uint8_t from_seq_no[4];  /* bytes 0 to 3 */
  uint8_t count[4];        /* bytes 4 to 7 */
} NotAppliedMessage;

/* any Not Applied Message at all: every byte one the checker chooses */
static void any_not_applied_message(NotAppliedMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->from_seq_no[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->count[i] = arbitrary(); }
}

/* Not Applied Message to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_not_applied_message(const NotAppliedMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->from_seq_no[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->count[i]; }

  return at;
}

/* Not Applied Message off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_not_applied_message(NotAppliedMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->from_seq_no[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->count[i] = wire[at++]; }

  return at;
}

/* what was read of Not Applied Message is what was written, byte for byte */
static void equal_not_applied_message(const NotAppliedMessage *read, const NotAppliedMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->from_seq_no[i] == written->from_seq_no[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->count[i] == written->count[i]); }
}

/* Not Applied Message: written and read back, then read and written back */
static void check_not_applied_message(void) {
  NotAppliedMessage sent;
  NotAppliedMessage got;
  uint8_t wire[8];
  uint8_t again[8];

  any_not_applied_message(&sent);
  assert(encode_not_applied_message(&sent, wire, 0) == 8);
  assert(decode_not_applied_message(&got, wire, 0) == 8);
  equal_not_applied_message(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_not_applied_message(&got, wire, 0) == 8);
  assert(encode_not_applied_message(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Sequence Message: 4 bytes ----------------------------------------------- */

/* SequenceMessage */
typedef struct {
  uint8_t next_seq_no[4];  /* bytes 0 to 3 */
} SequenceMessage;

/* any Sequence Message at all: every byte one the checker chooses */
static void any_sequence_message(SequenceMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->next_seq_no[i] = arbitrary(); }
}

/* Sequence Message to the wire: 4 bytes from at, returning where the next byte goes */
static size_t encode_sequence_message(const SequenceMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->next_seq_no[i]; }

  return at;
}

/* Sequence Message off the wire: 4 bytes from at, returning where the next byte lies */
static size_t decode_sequence_message(SequenceMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->next_seq_no[i] = wire[at++]; }

  return at;
}

/* what was read of Sequence Message is what was written, byte for byte */
static void equal_sequence_message(const SequenceMessage *read, const SequenceMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->next_seq_no[i] == written->next_seq_no[i]); }
}

/* Sequence Message: written and read back, then read and written back */
static void check_sequence_message(void) {
  SequenceMessage sent;
  SequenceMessage got;
  uint8_t wire[4];
  uint8_t again[4];

  any_sequence_message(&sent);
  assert(encode_sequence_message(&sent, wire, 0) == 4);
  assert(decode_sequence_message(&got, wire, 0) == 4);
  equal_sequence_message(&got, &sent);

  for (size_t i = 0; i < 4; i++) { wire[i] = arbitrary(); }
  assert(decode_sequence_message(&got, wire, 0) == 4);
  assert(encode_sequence_message(&got, again, 0) == 4);
  for (size_t i = 0; i < 4; i++) { assert(again[i] == wire[i]); }
}

/* ---- Retransmit Request Message: 20 bytes ------------------------------------ */

/* RetransmitRequestMessage */
typedef struct {
  uint8_t session_id[4];   /* bytes 0 to 3 */
  uint8_t timestamp[8];    /* bytes 4 to 11 */
  uint8_t from_seq_no[4];  /* bytes 12 to 15 */
  uint8_t count[4];        /* bytes 16 to 19 */
} RetransmitRequestMessage;

/* any Retransmit Request Message at all: every byte one the checker chooses */
static void any_retransmit_request_message(RetransmitRequestMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->session_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->from_seq_no[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->count[i] = arbitrary(); }
}

/* Retransmit Request Message to the wire: 20 bytes from at, returning where the next byte goes */
static size_t encode_retransmit_request_message(const RetransmitRequestMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->session_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->from_seq_no[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->count[i]; }

  return at;
}

/* Retransmit Request Message off the wire: 20 bytes from at, returning where the next byte lies */
static size_t decode_retransmit_request_message(RetransmitRequestMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->session_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->from_seq_no[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->count[i] = wire[at++]; }

  return at;
}

/* what was read of Retransmit Request Message is what was written, byte for byte */
static void equal_retransmit_request_message(const RetransmitRequestMessage *read, const RetransmitRequestMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->session_id[i] == written->session_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->from_seq_no[i] == written->from_seq_no[i]); }
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

/* ---- Retransmission Message: 20 bytes ---------------------------------------- */

/* RetransmissionMessage */
typedef struct {
  uint8_t session_id[4];         /* bytes 0 to 3 */
  uint8_t request_timestamp[8];  /* bytes 4 to 11 */
  uint8_t next_seq_no[4];        /* bytes 12 to 15 */
  uint8_t count[4];              /* bytes 16 to 19 */
} RetransmissionMessage;

/* any Retransmission Message at all: every byte one the checker chooses */
static void any_retransmission_message(RetransmissionMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->session_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->request_timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->next_seq_no[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->count[i] = arbitrary(); }
}

/* Retransmission Message to the wire: 20 bytes from at, returning where the next byte goes */
static size_t encode_retransmission_message(const RetransmissionMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->session_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->request_timestamp[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->next_seq_no[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->count[i]; }

  return at;
}

/* Retransmission Message off the wire: 20 bytes from at, returning where the next byte lies */
static size_t decode_retransmission_message(RetransmissionMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->session_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->request_timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->next_seq_no[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->count[i] = wire[at++]; }

  return at;
}

/* what was read of Retransmission Message is what was written, byte for byte */
static void equal_retransmission_message(const RetransmissionMessage *read, const RetransmissionMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->session_id[i] == written->session_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->request_timestamp[i] == written->request_timestamp[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->next_seq_no[i] == written->next_seq_no[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->count[i] == written->count[i]); }
}

/* Retransmission Message: written and read back, then read and written back */
static void check_retransmission_message(void) {
  RetransmissionMessage sent;
  RetransmissionMessage got;
  uint8_t wire[20];
  uint8_t again[20];

  any_retransmission_message(&sent);
  assert(encode_retransmission_message(&sent, wire, 0) == 20);
  assert(decode_retransmission_message(&got, wire, 0) == 20);
  equal_retransmission_message(&got, &sent);

  for (size_t i = 0; i < 20; i++) { wire[i] = arbitrary(); }
  assert(decode_retransmission_message(&got, wire, 0) == 20);
  assert(encode_retransmission_message(&got, again, 0) == 20);
  for (size_t i = 0; i < 20; i++) { assert(again[i] == wire[i]); }
}

/* ---- Retransmit Reject Message: 13 bytes ------------------------------------- */

/* RetransmitRejectMessage */
typedef struct {
  uint8_t session_id[4];           /* bytes 0 to 3 */
  uint8_t request_timestamp[8];    /* bytes 4 to 11 */
  uint8_t retransmit_reject_code;  /* byte 12 */
} RetransmitRejectMessage;

/* any Retransmit Reject Message at all: every byte one the checker chooses */
static void any_retransmit_reject_message(RetransmitRejectMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->session_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->request_timestamp[i] = arbitrary(); }
  record->retransmit_reject_code = arbitrary();
}

/* Retransmit Reject Message to the wire: 13 bytes from at, returning where the next byte goes */
static size_t encode_retransmit_reject_message(const RetransmitRejectMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->session_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->request_timestamp[i]; }
  wire[at++] = record->retransmit_reject_code;

  return at;
}

/* Retransmit Reject Message off the wire: 13 bytes from at, returning where the next byte lies */
static size_t decode_retransmit_reject_message(RetransmitRejectMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->session_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->request_timestamp[i] = wire[at++]; }
  record->retransmit_reject_code = wire[at++];

  return at;
}

/* what was read of Retransmit Reject Message is what was written, byte for byte */
static void equal_retransmit_reject_message(const RetransmitRejectMessage *read, const RetransmitRejectMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->session_id[i] == written->session_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->request_timestamp[i] == written->request_timestamp[i]); }
  assert(read->retransmit_reject_code == written->retransmit_reject_code);
}

/* Retransmit Reject Message: written and read back, then read and written back */
static void check_retransmit_reject_message(void) {
  RetransmitRejectMessage sent;
  RetransmitRejectMessage got;
  uint8_t wire[13];
  uint8_t again[13];

  any_retransmit_reject_message(&sent);
  assert(encode_retransmit_reject_message(&sent, wire, 0) == 13);
  assert(decode_retransmit_reject_message(&got, wire, 0) == 13);
  equal_retransmit_reject_message(&got, &sent);

  for (size_t i = 0; i < 13; i++) { wire[i] = arbitrary(); }
  assert(decode_retransmit_reject_message(&got, wire, 0) == 13);
  assert(encode_retransmit_reject_message(&got, again, 0) == 13);
  for (size_t i = 0; i < 13; i++) { assert(again[i] == wire[i]); }
}

/* ---- Inbound Business Header: 18 bytes --------------------------------------- */

/* InboundBusinessHeader */
typedef struct {
  uint8_t session_id[4];      /* bytes 0 to 3 */
  uint8_t msg_seq_num[4];     /* bytes 4 to 7 */
  uint8_t sending_time[8];    /* bytes 8 to 15 */
  uint8_t market_segment_id;  /* byte 16 */
  uint8_t padding;            /* byte 17 */
} InboundBusinessHeader;

/* any Inbound Business Header at all: every byte one the checker chooses */
static void any_inbound_business_header(InboundBusinessHeader *record) {
  for (size_t i = 0; i < 4; i++) { record->session_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->msg_seq_num[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->sending_time[i] = arbitrary(); }
  record->market_segment_id = arbitrary();
  record->padding = arbitrary();
}

/* Inbound Business Header to the wire: 18 bytes from at, returning where the next byte goes */
static size_t encode_inbound_business_header(const InboundBusinessHeader *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->session_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->msg_seq_num[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->sending_time[i]; }
  wire[at++] = record->market_segment_id;
  wire[at++] = record->padding;

  return at;
}

/* Inbound Business Header off the wire: 18 bytes from at, returning where the next byte lies */
static size_t decode_inbound_business_header(InboundBusinessHeader *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->session_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->msg_seq_num[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->sending_time[i] = wire[at++]; }
  record->market_segment_id = wire[at++];
  record->padding = wire[at++];

  return at;
}

/* what was read of Inbound Business Header is what was written, byte for byte */
static void equal_inbound_business_header(const InboundBusinessHeader *read, const InboundBusinessHeader *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->session_id[i] == written->session_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->msg_seq_num[i] == written->msg_seq_num[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->sending_time[i] == written->sending_time[i]); }
  assert(read->market_segment_id == written->market_segment_id);
  assert(read->padding == written->padding);
}

/* Inbound Business Header: written and read back, then read and written back */
static void check_inbound_business_header(void) {
  InboundBusinessHeader sent;
  InboundBusinessHeader got;
  uint8_t wire[18];
  uint8_t again[18];

  any_inbound_business_header(&sent);
  assert(encode_inbound_business_header(&sent, wire, 0) == 18);
  assert(decode_inbound_business_header(&got, wire, 0) == 18);
  equal_inbound_business_header(&got, &sent);

  for (size_t i = 0; i < 18; i++) { wire[i] = arbitrary(); }
  assert(decode_inbound_business_header(&got, wire, 0) == 18);
  assert(encode_inbound_business_header(&got, again, 0) == 18);
  for (size_t i = 0; i < 18; i++) { assert(again[i] == wire[i]); }
}

/* ---- Investor Id: 8 bytes ---------------------------------------------------- */

/* SimpleNewOrderMessage */
typedef struct {
  uint8_t prefix[2];              /* bytes 0 to 1 */
  uint8_t offset_2_padding_2[2];  /* bytes 2 to 3 */
  uint8_t document[4];            /* bytes 4 to 7 */
} InvestorId;

/* any Investor Id at all: every byte one the checker chooses */
static void any_investor_id(InvestorId *record) {
  for (size_t i = 0; i < 2; i++) { record->prefix[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->offset_2_padding_2[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->document[i] = arbitrary(); }
}

/* Investor Id to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_investor_id(const InvestorId *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->prefix[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->offset_2_padding_2[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->document[i]; }

  return at;
}

/* Investor Id off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_investor_id(InvestorId *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->prefix[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->offset_2_padding_2[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->document[i] = wire[at++]; }

  return at;
}

/* what was read of Investor Id is what was written, byte for byte */
static void equal_investor_id(const InvestorId *read, const InvestorId *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->prefix[i] == written->prefix[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->offset_2_padding_2[i] == written->offset_2_padding_2[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->document[i] == written->document[i]); }
}

/* Investor Id: written and read back, then read and written back */
static void check_investor_id(void) {
  InvestorId sent;
  InvestorId got;
  uint8_t wire[8];
  uint8_t again[8];

  any_investor_id(&sent);
  assert(encode_investor_id(&sent, wire, 0) == 8);
  assert(decode_investor_id(&got, wire, 0) == 8);
  equal_investor_id(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_investor_id(&got, wire, 0) == 8);
  assert(encode_investor_id(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Custodian Info: 12 bytes ------------------------------------------------ */

/* NewOrderSingleMessage */
typedef struct {
  uint8_t custodian[4];                /* bytes 0 to 3 */
  uint8_t custody_account[4];          /* bytes 4 to 7 */
  uint8_t custody_allocation_type[4];  /* bytes 8 to 11 */
} CustodianInfo;

/* any Custodian Info at all: every byte one the checker chooses */
static void any_custodian_info(CustodianInfo *record) {
  for (size_t i = 0; i < 4; i++) { record->custodian[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->custody_account[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->custody_allocation_type[i] = arbitrary(); }
}

/* Custodian Info to the wire: 12 bytes from at, returning where the next byte goes */
static size_t encode_custodian_info(const CustodianInfo *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->custodian[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->custody_account[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->custody_allocation_type[i]; }

  return at;
}

/* Custodian Info off the wire: 12 bytes from at, returning where the next byte lies */
static size_t decode_custodian_info(CustodianInfo *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->custodian[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->custody_account[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->custody_allocation_type[i] = wire[at++]; }

  return at;
}

/* what was read of Custodian Info is what was written, byte for byte */
static void equal_custodian_info(const CustodianInfo *read, const CustodianInfo *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->custodian[i] == written->custodian[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->custody_account[i] == written->custody_account[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->custody_allocation_type[i] == written->custody_allocation_type[i]); }
}

/* Custodian Info: written and read back, then read and written back */
static void check_custodian_info(void) {
  CustodianInfo sent;
  CustodianInfo got;
  uint8_t wire[12];
  uint8_t again[12];

  any_custodian_info(&sent);
  assert(encode_custodian_info(&sent, wire, 0) == 12);
  assert(decode_custodian_info(&got, wire, 0) == 12);
  equal_custodian_info(&got, &sent);

  for (size_t i = 0; i < 12; i++) { wire[i] = arbitrary(); }
  assert(decode_custodian_info(&got, wire, 0) == 12);
  assert(encode_custodian_info(&got, again, 0) == 12);
  for (size_t i = 0; i < 12; i++) { assert(again[i] == wire[i]); }
}

/* ---- Group Size Encoding: 3 bytes -------------------------------------------- */

/* GroupSizeEncoding */
typedef struct {
  uint8_t block_length[2];  /* bytes 0 to 1 */
  uint8_t num_in_group;     /* byte 2 */
} GroupSizeEncoding;

/* any Group Size Encoding at all: every byte one the checker chooses */
static void any_group_size_encoding(GroupSizeEncoding *record) {
  for (size_t i = 0; i < 2; i++) { record->block_length[i] = arbitrary(); }
  record->num_in_group = arbitrary();
}

/* Group Size Encoding to the wire: 3 bytes from at, returning where the next byte goes */
static size_t encode_group_size_encoding(const GroupSizeEncoding *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->block_length[i]; }
  wire[at++] = record->num_in_group;

  return at;
}

/* Group Size Encoding off the wire: 3 bytes from at, returning where the next byte lies */
static size_t decode_group_size_encoding(GroupSizeEncoding *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->block_length[i] = wire[at++]; }
  record->num_in_group = wire[at++];

  return at;
}

/* what was read of Group Size Encoding is what was written, byte for byte */
static void equal_group_size_encoding(const GroupSizeEncoding *read, const GroupSizeEncoding *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->block_length[i] == written->block_length[i]); }
  assert(read->num_in_group == written->num_in_group);
}

/* Group Size Encoding: written and read back, then read and written back */
static void check_group_size_encoding(void) {
  GroupSizeEncoding sent;
  GroupSizeEncoding got;
  uint8_t wire[3];
  uint8_t again[3];

  any_group_size_encoding(&sent);
  assert(encode_group_size_encoding(&sent, wire, 0) == 3);
  assert(decode_group_size_encoding(&got, wire, 0) == 3);
  equal_group_size_encoding(&got, &sent);

  for (size_t i = 0; i < 3; i++) { wire[i] = arbitrary(); }
  assert(decode_group_size_encoding(&got, wire, 0) == 3);
  assert(encode_group_size_encoding(&got, again, 0) == 3);
  for (size_t i = 0; i < 3; i++) { assert(again[i] == wire[i]); }
}

/* ---- Outbound Business Header: 18 bytes -------------------------------------- */

/* OutboundBusinessHeader */
typedef struct {
  uint8_t session_id[4];               /* bytes 0 to 3 */
  uint8_t msg_seq_num[4];              /* bytes 4 to 7 */
  uint8_t sending_time[8];             /* bytes 8 to 15 */
  uint8_t event_indicator;             /* byte 16 */
  uint8_t market_segment_id_optional;  /* byte 17 */
} OutboundBusinessHeader;

/* any Outbound Business Header at all: every byte one the checker chooses */
static void any_outbound_business_header(OutboundBusinessHeader *record) {
  for (size_t i = 0; i < 4; i++) { record->session_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->msg_seq_num[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->sending_time[i] = arbitrary(); }
  record->event_indicator = arbitrary();
  record->market_segment_id_optional = arbitrary();
}

/* Outbound Business Header to the wire: 18 bytes from at, returning where the next byte goes */
static size_t encode_outbound_business_header(const OutboundBusinessHeader *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->session_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->msg_seq_num[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->sending_time[i]; }
  wire[at++] = record->event_indicator;
  wire[at++] = record->market_segment_id_optional;

  return at;
}

/* Outbound Business Header off the wire: 18 bytes from at, returning where the next byte lies */
static size_t decode_outbound_business_header(OutboundBusinessHeader *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->session_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->msg_seq_num[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->sending_time[i] = wire[at++]; }
  record->event_indicator = wire[at++];
  record->market_segment_id_optional = wire[at++];

  return at;
}

/* what was read of Outbound Business Header is what was written, byte for byte */
static void equal_outbound_business_header(const OutboundBusinessHeader *read, const OutboundBusinessHeader *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->session_id[i] == written->session_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->msg_seq_num[i] == written->msg_seq_num[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->sending_time[i] == written->sending_time[i]); }
  assert(read->event_indicator == written->event_indicator);
  assert(read->market_segment_id_optional == written->market_segment_id_optional);
}

/* Outbound Business Header: written and read back, then read and written back */
static void check_outbound_business_header(void) {
  OutboundBusinessHeader sent;
  OutboundBusinessHeader got;
  uint8_t wire[18];
  uint8_t again[18];

  any_outbound_business_header(&sent);
  assert(encode_outbound_business_header(&sent, wire, 0) == 18);
  assert(decode_outbound_business_header(&got, wire, 0) == 18);
  equal_outbound_business_header(&got, &sent);

  for (size_t i = 0; i < 18; i++) { wire[i] = arbitrary(); }
  assert(decode_outbound_business_header(&got, wire, 0) == 18);
  assert(encode_outbound_business_header(&got, again, 0) == 18);
  for (size_t i = 0; i < 18; i++) { assert(again[i] == wire[i]); }
}

/* ---- Implied Event Id: 6 bytes ----------------------------------------------- */

/* ExecutionReport_TradeMessage */
typedef struct {
  uint8_t event_id[4];           /* bytes 0 to 3 */
  uint8_t no_related_trades[2];  /* bytes 4 to 5 */
} ImpliedEventId;

/* any Implied Event Id at all: every byte one the checker chooses */
static void any_implied_event_id(ImpliedEventId *record) {
  for (size_t i = 0; i < 4; i++) { record->event_id[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->no_related_trades[i] = arbitrary(); }
}

/* Implied Event Id to the wire: 6 bytes from at, returning where the next byte goes */
static size_t encode_implied_event_id(const ImpliedEventId *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->event_id[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->no_related_trades[i]; }

  return at;
}

/* Implied Event Id off the wire: 6 bytes from at, returning where the next byte lies */
static size_t decode_implied_event_id(ImpliedEventId *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->event_id[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->no_related_trades[i] = wire[at++]; }

  return at;
}

/* what was read of Implied Event Id is what was written, byte for byte */
static void equal_implied_event_id(const ImpliedEventId *read, const ImpliedEventId *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->event_id[i] == written->event_id[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->no_related_trades[i] == written->no_related_trades[i]); }
}

/* Implied Event Id: written and read back, then read and written back */
static void check_implied_event_id(void) {
  ImpliedEventId sent;
  ImpliedEventId got;
  uint8_t wire[6];
  uint8_t again[6];

  any_implied_event_id(&sent);
  assert(encode_implied_event_id(&sent, wire, 0) == 6);
  assert(decode_implied_event_id(&got, wire, 0) == 6);
  equal_implied_event_id(&got, &sent);

  for (size_t i = 0; i < 6; i++) { wire[i] = arbitrary(); }
  assert(decode_implied_event_id(&got, wire, 0) == 6);
  assert(encode_implied_event_id(&got, again, 0) == 6);
  for (size_t i = 0; i < 6; i++) { assert(again[i] == wire[i]); }
}

/* ---- Security Definition Response Message: 83 bytes -------------------------- */

/* SecurityDefinitionResponseMessage */
typedef struct {
  OutboundBusinessHeader outbound_business_header;  /* bytes 0 to 17 */
  uint8_t offset_18_padding_2[2];                   /* bytes 18 to 19 */
  uint8_t security_req_id[8];                       /* bytes 20 to 27 */
  uint8_t security_id_optional[8];                  /* bytes 28 to 35 */
  uint8_t security_response_type;                   /* byte 36 */
  uint8_t security_strategy_type[3];                /* bytes 37 to 39 */
  uint8_t symbol[20];                               /* bytes 40 to 59 */
  uint8_t security_response_id[8];                  /* bytes 60 to 67 */
  uint8_t sender_location[10];                      /* bytes 68 to 77 */
  uint8_t entering_trader[5];                       /* bytes 78 to 82 */
} SecurityDefinitionResponseMessage;

/* any Security Definition Response Message at all: every byte one the checker chooses */
static void any_security_definition_response_message(SecurityDefinitionResponseMessage *record) {
  any_outbound_business_header(&record->outbound_business_header);
  for (size_t i = 0; i < 2; i++) { record->offset_18_padding_2[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->security_req_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->security_id_optional[i] = arbitrary(); }
  record->security_response_type = arbitrary();
  for (size_t i = 0; i < 3; i++) { record->security_strategy_type[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->symbol[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->security_response_id[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->sender_location[i] = arbitrary(); }
  for (size_t i = 0; i < 5; i++) { record->entering_trader[i] = arbitrary(); }
}

/* Security Definition Response Message to the wire: 83 bytes from at, returning where the next byte goes */
static size_t encode_security_definition_response_message(const SecurityDefinitionResponseMessage *record, uint8_t *wire, size_t at) {
  at = encode_outbound_business_header(&record->outbound_business_header, wire, at);
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->offset_18_padding_2[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->security_req_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->security_id_optional[i]; }
  wire[at++] = record->security_response_type;
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->security_strategy_type[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->symbol[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->security_response_id[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->sender_location[i]; }
  for (size_t i = 0; i < 5; i++) { wire[at++] = record->entering_trader[i]; }

  return at;
}

/* Security Definition Response Message off the wire: 83 bytes from at, returning where the next byte lies */
static size_t decode_security_definition_response_message(SecurityDefinitionResponseMessage *record, const uint8_t *wire, size_t at) {
  at = decode_outbound_business_header(&record->outbound_business_header, wire, at);
  for (size_t i = 0; i < 2; i++) { record->offset_18_padding_2[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->security_req_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->security_id_optional[i] = wire[at++]; }
  record->security_response_type = wire[at++];
  for (size_t i = 0; i < 3; i++) { record->security_strategy_type[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->symbol[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->security_response_id[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->sender_location[i] = wire[at++]; }
  for (size_t i = 0; i < 5; i++) { record->entering_trader[i] = wire[at++]; }

  return at;
}

/* what was read of Security Definition Response Message is what was written, byte for byte */
static void equal_security_definition_response_message(const SecurityDefinitionResponseMessage *read, const SecurityDefinitionResponseMessage *written) {
  equal_outbound_business_header(&read->outbound_business_header, &written->outbound_business_header);
  for (size_t i = 0; i < 2; i++) { assert(read->offset_18_padding_2[i] == written->offset_18_padding_2[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->security_req_id[i] == written->security_req_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->security_id_optional[i] == written->security_id_optional[i]); }
  assert(read->security_response_type == written->security_response_type);
  for (size_t i = 0; i < 3; i++) { assert(read->security_strategy_type[i] == written->security_strategy_type[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->symbol[i] == written->symbol[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->security_response_id[i] == written->security_response_id[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->sender_location[i] == written->sender_location[i]); }
  for (size_t i = 0; i < 5; i++) { assert(read->entering_trader[i] == written->entering_trader[i]); }
}

/* Security Definition Response Message: written and read back, then read and written back */
static void check_security_definition_response_message(void) {
  SecurityDefinitionResponseMessage sent;
  SecurityDefinitionResponseMessage got;
  uint8_t wire[83];
  uint8_t again[83];

  any_security_definition_response_message(&sent);
  assert(encode_security_definition_response_message(&sent, wire, 0) == 83);
  assert(decode_security_definition_response_message(&got, wire, 0) == 83);
  equal_security_definition_response_message(&got, &sent);

  for (size_t i = 0; i < 83; i++) { wire[i] = arbitrary(); }
  assert(decode_security_definition_response_message(&got, wire, 0) == 83);
  assert(encode_security_definition_response_message(&got, again, 0) == 83);
  for (size_t i = 0; i < 83; i++) { assert(again[i] == wire[i]); }
}

/* ---- Bidirectional Business Header: 20 bytes --------------------------------- */

/* BidirectionalBusinessHeader */
typedef struct {
  uint8_t session_id[4];               /* bytes 0 to 3 */
  uint8_t msg_seq_num[4];              /* bytes 4 to 7 */
  uint8_t sending_time[8];             /* bytes 8 to 15 */
  uint8_t event_indicator;             /* byte 16 */
  uint8_t market_segment_id_optional;  /* byte 17 */
  uint8_t padding_char_2[2];           /* bytes 18 to 19 */
} BidirectionalBusinessHeader;

/* any Bidirectional Business Header at all: every byte one the checker chooses */
static void any_bidirectional_business_header(BidirectionalBusinessHeader *record) {
  for (size_t i = 0; i < 4; i++) { record->session_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->msg_seq_num[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->sending_time[i] = arbitrary(); }
  record->event_indicator = arbitrary();
  record->market_segment_id_optional = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->padding_char_2[i] = arbitrary(); }
}

/* Bidirectional Business Header to the wire: 20 bytes from at, returning where the next byte goes */
static size_t encode_bidirectional_business_header(const BidirectionalBusinessHeader *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->session_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->msg_seq_num[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->sending_time[i]; }
  wire[at++] = record->event_indicator;
  wire[at++] = record->market_segment_id_optional;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->padding_char_2[i]; }

  return at;
}

/* Bidirectional Business Header off the wire: 20 bytes from at, returning where the next byte lies */
static size_t decode_bidirectional_business_header(BidirectionalBusinessHeader *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->session_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->msg_seq_num[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->sending_time[i] = wire[at++]; }
  record->event_indicator = wire[at++];
  record->market_segment_id_optional = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->padding_char_2[i] = wire[at++]; }

  return at;
}

/* what was read of Bidirectional Business Header is what was written, byte for byte */
static void equal_bidirectional_business_header(const BidirectionalBusinessHeader *read, const BidirectionalBusinessHeader *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->session_id[i] == written->session_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->msg_seq_num[i] == written->msg_seq_num[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->sending_time[i] == written->sending_time[i]); }
  assert(read->event_indicator == written->event_indicator);
  assert(read->market_segment_id_optional == written->market_segment_id_optional);
  for (size_t i = 0; i < 2; i++) { assert(read->padding_char_2[i] == written->padding_char_2[i]); }
}

/* Bidirectional Business Header: written and read back, then read and written back */
static void check_bidirectional_business_header(void) {
  BidirectionalBusinessHeader sent;
  BidirectionalBusinessHeader got;
  uint8_t wire[20];
  uint8_t again[20];

  any_bidirectional_business_header(&sent);
  assert(encode_bidirectional_business_header(&sent, wire, 0) == 20);
  assert(decode_bidirectional_business_header(&got, wire, 0) == 20);
  equal_bidirectional_business_header(&got, &sent);

  for (size_t i = 0; i < 20; i++) { wire[i] = arbitrary(); }
  assert(decode_bidirectional_business_header(&got, wire, 0) == 20);
  assert(encode_bidirectional_business_header(&got, again, 0) == 20);
  for (size_t i = 0; i < 20; i++) { assert(again[i] == wire[i]); }
}

/* ---- Position Maintenance Cancel Request Message: 65 bytes ------------------- */

/* PositionMaintenanceCancelRequestMessage */
typedef struct {
  InboundBusinessHeader inbound_business_header;  /* bytes 0 to 17 */
  uint8_t pos_req_id[8];                          /* bytes 18 to 25 */
  uint8_t security_id[8];                         /* bytes 26 to 33 */
  uint8_t orig_pos_req_ref_id[8];                 /* bytes 34 to 41 */
  uint8_t pos_maint_rpt_ref_id[8];                /* bytes 42 to 49 */
  uint8_t sender_location[10];                    /* bytes 50 to 59 */
  uint8_t entering_trader[5];                     /* bytes 60 to 64 */
} PositionMaintenanceCancelRequestMessage;

/* any Position Maintenance Cancel Request Message at all: every byte one the checker chooses */
static void any_position_maintenance_cancel_request_message(PositionMaintenanceCancelRequestMessage *record) {
  any_inbound_business_header(&record->inbound_business_header);
  for (size_t i = 0; i < 8; i++) { record->pos_req_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->security_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->orig_pos_req_ref_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->pos_maint_rpt_ref_id[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->sender_location[i] = arbitrary(); }
  for (size_t i = 0; i < 5; i++) { record->entering_trader[i] = arbitrary(); }
}

/* Position Maintenance Cancel Request Message to the wire: 65 bytes from at, returning where the next byte goes */
static size_t encode_position_maintenance_cancel_request_message(const PositionMaintenanceCancelRequestMessage *record, uint8_t *wire, size_t at) {
  at = encode_inbound_business_header(&record->inbound_business_header, wire, at);
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->pos_req_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->security_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->orig_pos_req_ref_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->pos_maint_rpt_ref_id[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->sender_location[i]; }
  for (size_t i = 0; i < 5; i++) { wire[at++] = record->entering_trader[i]; }

  return at;
}

/* Position Maintenance Cancel Request Message off the wire: 65 bytes from at, returning where the next byte lies */
static size_t decode_position_maintenance_cancel_request_message(PositionMaintenanceCancelRequestMessage *record, const uint8_t *wire, size_t at) {
  at = decode_inbound_business_header(&record->inbound_business_header, wire, at);
  for (size_t i = 0; i < 8; i++) { record->pos_req_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->security_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->orig_pos_req_ref_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->pos_maint_rpt_ref_id[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->sender_location[i] = wire[at++]; }
  for (size_t i = 0; i < 5; i++) { record->entering_trader[i] = wire[at++]; }

  return at;
}

/* what was read of Position Maintenance Cancel Request Message is what was written, byte for byte */
static void equal_position_maintenance_cancel_request_message(const PositionMaintenanceCancelRequestMessage *read, const PositionMaintenanceCancelRequestMessage *written) {
  equal_inbound_business_header(&read->inbound_business_header, &written->inbound_business_header);
  for (size_t i = 0; i < 8; i++) { assert(read->pos_req_id[i] == written->pos_req_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->security_id[i] == written->security_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->orig_pos_req_ref_id[i] == written->orig_pos_req_ref_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->pos_maint_rpt_ref_id[i] == written->pos_maint_rpt_ref_id[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->sender_location[i] == written->sender_location[i]); }
  for (size_t i = 0; i < 5; i++) { assert(read->entering_trader[i] == written->entering_trader[i]); }
}

/* Position Maintenance Cancel Request Message: written and read back, then read and written back */
static void check_position_maintenance_cancel_request_message(void) {
  PositionMaintenanceCancelRequestMessage sent;
  PositionMaintenanceCancelRequestMessage got;
  uint8_t wire[65];
  uint8_t again[65];

  any_position_maintenance_cancel_request_message(&sent);
  assert(encode_position_maintenance_cancel_request_message(&sent, wire, 0) == 65);
  assert(decode_position_maintenance_cancel_request_message(&got, wire, 0) == 65);
  equal_position_maintenance_cancel_request_message(&got, &sent);

  for (size_t i = 0; i < 65; i++) { wire[i] = arbitrary(); }
  assert(decode_position_maintenance_cancel_request_message(&got, wire, 0) == 65);
  assert(encode_position_maintenance_cancel_request_message(&got, again, 0) == 65);
  for (size_t i = 0; i < 65; i++) { assert(again[i] == wire[i]); }
}

/* ---- Allocation Report Message: 84 bytes ------------------------------------- */

/* AllocationReportMessage */
typedef struct {
  OutboundBusinessHeader outbound_business_header;  /* bytes 0 to 17 */
  uint8_t alloc_id[8];                              /* bytes 18 to 25 */
  uint8_t security_id[8];                           /* bytes 26 to 33 */
  uint8_t alloc_report_id[8];                       /* bytes 34 to 41 */
  uint8_t alloc_trans_type;                         /* byte 42 */
  uint8_t alloc_report_type;                        /* byte 43 */
  uint8_t alloc_no_orders_type;                     /* byte 44 */
  uint8_t alloc_rej_code[4];                        /* bytes 45 to 48 */
  uint8_t quantity[8];                              /* bytes 49 to 56 */
  uint8_t alloc_status;                             /* byte 57 */
  uint8_t trade_date_optional[2];                   /* bytes 58 to 59 */
  uint8_t transact_time[8];                         /* bytes 60 to 67 */
  uint8_t side;                                     /* byte 68 */
  uint8_t sender_location[10];                      /* bytes 69 to 78 */
  uint8_t entering_trader[5];                       /* bytes 79 to 83 */
} AllocationReportMessage;

/* any Allocation Report Message at all: every byte one the checker chooses */
static void any_allocation_report_message(AllocationReportMessage *record) {
  any_outbound_business_header(&record->outbound_business_header);
  for (size_t i = 0; i < 8; i++) { record->alloc_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->security_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->alloc_report_id[i] = arbitrary(); }
  record->alloc_trans_type = arbitrary();
  record->alloc_report_type = arbitrary();
  record->alloc_no_orders_type = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->alloc_rej_code[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->quantity[i] = arbitrary(); }
  record->alloc_status = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->trade_date_optional[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->transact_time[i] = arbitrary(); }
  record->side = arbitrary();
  for (size_t i = 0; i < 10; i++) { record->sender_location[i] = arbitrary(); }
  for (size_t i = 0; i < 5; i++) { record->entering_trader[i] = arbitrary(); }
}

/* Allocation Report Message to the wire: 84 bytes from at, returning where the next byte goes */
static size_t encode_allocation_report_message(const AllocationReportMessage *record, uint8_t *wire, size_t at) {
  at = encode_outbound_business_header(&record->outbound_business_header, wire, at);
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->alloc_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->security_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->alloc_report_id[i]; }
  wire[at++] = record->alloc_trans_type;
  wire[at++] = record->alloc_report_type;
  wire[at++] = record->alloc_no_orders_type;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->alloc_rej_code[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->quantity[i]; }
  wire[at++] = record->alloc_status;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->trade_date_optional[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->transact_time[i]; }
  wire[at++] = record->side;
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->sender_location[i]; }
  for (size_t i = 0; i < 5; i++) { wire[at++] = record->entering_trader[i]; }

  return at;
}

/* Allocation Report Message off the wire: 84 bytes from at, returning where the next byte lies */
static size_t decode_allocation_report_message(AllocationReportMessage *record, const uint8_t *wire, size_t at) {
  at = decode_outbound_business_header(&record->outbound_business_header, wire, at);
  for (size_t i = 0; i < 8; i++) { record->alloc_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->security_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->alloc_report_id[i] = wire[at++]; }
  record->alloc_trans_type = wire[at++];
  record->alloc_report_type = wire[at++];
  record->alloc_no_orders_type = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->alloc_rej_code[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->quantity[i] = wire[at++]; }
  record->alloc_status = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->trade_date_optional[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->transact_time[i] = wire[at++]; }
  record->side = wire[at++];
  for (size_t i = 0; i < 10; i++) { record->sender_location[i] = wire[at++]; }
  for (size_t i = 0; i < 5; i++) { record->entering_trader[i] = wire[at++]; }

  return at;
}

/* what was read of Allocation Report Message is what was written, byte for byte */
static void equal_allocation_report_message(const AllocationReportMessage *read, const AllocationReportMessage *written) {
  equal_outbound_business_header(&read->outbound_business_header, &written->outbound_business_header);
  for (size_t i = 0; i < 8; i++) { assert(read->alloc_id[i] == written->alloc_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->security_id[i] == written->security_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->alloc_report_id[i] == written->alloc_report_id[i]); }
  assert(read->alloc_trans_type == written->alloc_trans_type);
  assert(read->alloc_report_type == written->alloc_report_type);
  assert(read->alloc_no_orders_type == written->alloc_no_orders_type);
  for (size_t i = 0; i < 4; i++) { assert(read->alloc_rej_code[i] == written->alloc_rej_code[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->quantity[i] == written->quantity[i]); }
  assert(read->alloc_status == written->alloc_status);
  for (size_t i = 0; i < 2; i++) { assert(read->trade_date_optional[i] == written->trade_date_optional[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->transact_time[i] == written->transact_time[i]); }
  assert(read->side == written->side);
  for (size_t i = 0; i < 10; i++) { assert(read->sender_location[i] == written->sender_location[i]); }
  for (size_t i = 0; i < 5; i++) { assert(read->entering_trader[i] == written->entering_trader[i]); }
}

/* Allocation Report Message: written and read back, then read and written back */
static void check_allocation_report_message(void) {
  AllocationReportMessage sent;
  AllocationReportMessage got;
  uint8_t wire[84];
  uint8_t again[84];

  any_allocation_report_message(&sent);
  assert(encode_allocation_report_message(&sent, wire, 0) == 84);
  assert(decode_allocation_report_message(&got, wire, 0) == 84);
  equal_allocation_report_message(&got, &sent);

  for (size_t i = 0; i < 84; i++) { wire[i] = arbitrary(); }
  assert(decode_allocation_report_message(&got, wire, 0) == 84);
  assert(encode_allocation_report_message(&got, again, 0) == 84);
  for (size_t i = 0; i < 84; i++) { assert(again[i] == wire[i]); }
}

/* ---- Order Mass Action Request Message: 54 bytes ----------------------------- */

/* OrderMassActionRequestMessage */
typedef struct {
  InboundBusinessHeader inbound_business_header;  /* bytes 0 to 17 */
  uint8_t mass_action_type;                       /* byte 18 */
  uint8_t mass_action_scope;                      /* byte 19 */
  uint8_t cl_ord_id[8];                           /* bytes 20 to 27 */
  uint8_t mass_cancel_restatement_reason;         /* byte 28 */
  uint8_t ord_tag_id;                             /* byte 29 */
  uint8_t side_optional;                          /* byte 30 */
  uint8_t offset_31_padding_1;                    /* byte 31 */
  uint8_t asset[6];                               /* bytes 32 to 37 */
  uint8_t security_id_optional[8];                /* bytes 38 to 45 */
  InvestorId investor_id;                         /* bytes 46 to 53 */
} OrderMassActionRequestMessage;

/* any Order Mass Action Request Message at all: every byte one the checker chooses */
static void any_order_mass_action_request_message(OrderMassActionRequestMessage *record) {
  any_inbound_business_header(&record->inbound_business_header);
  record->mass_action_type = arbitrary();
  record->mass_action_scope = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->cl_ord_id[i] = arbitrary(); }
  record->mass_cancel_restatement_reason = arbitrary();
  record->ord_tag_id = arbitrary();
  record->side_optional = arbitrary();
  record->offset_31_padding_1 = arbitrary();
  for (size_t i = 0; i < 6; i++) { record->asset[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->security_id_optional[i] = arbitrary(); }
  any_investor_id(&record->investor_id);
}

/* Order Mass Action Request Message to the wire: 54 bytes from at, returning where the next byte goes */
static size_t encode_order_mass_action_request_message(const OrderMassActionRequestMessage *record, uint8_t *wire, size_t at) {
  at = encode_inbound_business_header(&record->inbound_business_header, wire, at);
  wire[at++] = record->mass_action_type;
  wire[at++] = record->mass_action_scope;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->cl_ord_id[i]; }
  wire[at++] = record->mass_cancel_restatement_reason;
  wire[at++] = record->ord_tag_id;
  wire[at++] = record->side_optional;
  wire[at++] = record->offset_31_padding_1;
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->asset[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->security_id_optional[i]; }
  at = encode_investor_id(&record->investor_id, wire, at);

  return at;
}

/* Order Mass Action Request Message off the wire: 54 bytes from at, returning where the next byte lies */
static size_t decode_order_mass_action_request_message(OrderMassActionRequestMessage *record, const uint8_t *wire, size_t at) {
  at = decode_inbound_business_header(&record->inbound_business_header, wire, at);
  record->mass_action_type = wire[at++];
  record->mass_action_scope = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->cl_ord_id[i] = wire[at++]; }
  record->mass_cancel_restatement_reason = wire[at++];
  record->ord_tag_id = wire[at++];
  record->side_optional = wire[at++];
  record->offset_31_padding_1 = wire[at++];
  for (size_t i = 0; i < 6; i++) { record->asset[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->security_id_optional[i] = wire[at++]; }
  at = decode_investor_id(&record->investor_id, wire, at);

  return at;
}

/* what was read of Order Mass Action Request Message is what was written, byte for byte */
static void equal_order_mass_action_request_message(const OrderMassActionRequestMessage *read, const OrderMassActionRequestMessage *written) {
  equal_inbound_business_header(&read->inbound_business_header, &written->inbound_business_header);
  assert(read->mass_action_type == written->mass_action_type);
  assert(read->mass_action_scope == written->mass_action_scope);
  for (size_t i = 0; i < 8; i++) { assert(read->cl_ord_id[i] == written->cl_ord_id[i]); }
  assert(read->mass_cancel_restatement_reason == written->mass_cancel_restatement_reason);
  assert(read->ord_tag_id == written->ord_tag_id);
  assert(read->side_optional == written->side_optional);
  assert(read->offset_31_padding_1 == written->offset_31_padding_1);
  for (size_t i = 0; i < 6; i++) { assert(read->asset[i] == written->asset[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->security_id_optional[i] == written->security_id_optional[i]); }
  equal_investor_id(&read->investor_id, &written->investor_id);
}

/* Order Mass Action Request Message: written and read back, then read and written back */
static void check_order_mass_action_request_message(void) {
  OrderMassActionRequestMessage sent;
  OrderMassActionRequestMessage got;
  uint8_t wire[54];
  uint8_t again[54];

  any_order_mass_action_request_message(&sent);
  assert(encode_order_mass_action_request_message(&sent, wire, 0) == 54);
  assert(decode_order_mass_action_request_message(&got, wire, 0) == 54);
  equal_order_mass_action_request_message(&got, &sent);

  for (size_t i = 0; i < 54; i++) { wire[i] = arbitrary(); }
  assert(decode_order_mass_action_request_message(&got, wire, 0) == 54);
  assert(encode_order_mass_action_request_message(&got, again, 0) == 54);
  for (size_t i = 0; i < 54; i++) { assert(again[i] == wire[i]); }
}

/* ---- What esbmc checks ------------------------------------------------------- */

/* every record of the protocol, each on its own buffers */
static void checks(void) {
  check_simple_open_framing_header();
  check_message_header();
  check_semantic_version();
  check_negotiate_response_message();
  check_negotiate_reject_message();
  check_establish_ack_message();
  check_establish_reject_message();
  check_terminate_message();
  check_not_applied_message();
  check_sequence_message();
  check_retransmit_request_message();
  check_retransmission_message();
  check_retransmit_reject_message();
  check_inbound_business_header();
  check_investor_id();
  check_custodian_info();
  check_group_size_encoding();
  check_outbound_business_header();
  check_implied_event_id();
  check_security_definition_response_message();
  check_bidirectional_business_header();
  check_position_maintenance_cancel_request_message();
  check_allocation_report_message();
  check_order_mass_action_request_message();
}

int main(void) {
#ifdef CONCRETE
  for (pattern = 0; pattern < 4; pattern++) { checks(); }
#else
  checks();
#endif

  return 0;
}
