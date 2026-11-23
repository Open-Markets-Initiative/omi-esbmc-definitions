// moex/spectra/orderentry/Spectra_OrderEntry_v9_12_0_Server.c
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

/* ---- Establishment Ack Message: 20 bytes ------------------------------------- */

/* EstablishmentAckMessage */
typedef struct {
  uint8_t request_timestamp[8];   /* bytes 0 to 7 */
  uint8_t keepalive_interval[4];  /* bytes 8 to 11 */
  uint8_t next_seq_no[8];         /* bytes 12 to 19 */
} EstablishmentAckMessage;

/* any Establishment Ack Message at all: every byte one the checker chooses */
static void any_establishment_ack_message(EstablishmentAckMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->request_timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->keepalive_interval[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->next_seq_no[i] = arbitrary(); }
}

/* Establishment Ack Message to the wire: 20 bytes from at, returning where the next byte goes */
static size_t encode_establishment_ack_message(const EstablishmentAckMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->request_timestamp[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->keepalive_interval[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->next_seq_no[i]; }

  return at;
}

/* Establishment Ack Message off the wire: 20 bytes from at, returning where the next byte lies */
static size_t decode_establishment_ack_message(EstablishmentAckMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->request_timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->keepalive_interval[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->next_seq_no[i] = wire[at++]; }

  return at;
}

/* what was read of Establishment Ack Message is what was written, byte for byte */
static void equal_establishment_ack_message(const EstablishmentAckMessage *read, const EstablishmentAckMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->request_timestamp[i] == written->request_timestamp[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->keepalive_interval[i] == written->keepalive_interval[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->next_seq_no[i] == written->next_seq_no[i]); }
}

/* Establishment Ack Message: written and read back, then read and written back */
static void check_establishment_ack_message(void) {
  EstablishmentAckMessage sent;
  EstablishmentAckMessage got;
  uint8_t wire[20];
  uint8_t again[20];

  any_establishment_ack_message(&sent);
  assert(encode_establishment_ack_message(&sent, wire, 0) == 20);
  assert(decode_establishment_ack_message(&got, wire, 0) == 20);
  equal_establishment_ack_message(&got, &sent);

  for (size_t i = 0; i < 20; i++) { wire[i] = arbitrary(); }
  assert(decode_establishment_ack_message(&got, wire, 0) == 20);
  assert(encode_establishment_ack_message(&got, again, 0) == 20);
  for (size_t i = 0; i < 20; i++) { assert(again[i] == wire[i]); }
}

/* ---- Establishment Reject Message: 9 bytes ----------------------------------- */

/* EstablishmentRejectMessage */
typedef struct {
  uint8_t request_timestamp[8];       /* bytes 0 to 7 */
  uint8_t establishment_reject_code;  /* byte 8 */
} EstablishmentRejectMessage;

/* any Establishment Reject Message at all: every byte one the checker chooses */
static void any_establishment_reject_message(EstablishmentRejectMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->request_timestamp[i] = arbitrary(); }
  record->establishment_reject_code = arbitrary();
}

/* Establishment Reject Message to the wire: 9 bytes from at, returning where the next byte goes */
static size_t encode_establishment_reject_message(const EstablishmentRejectMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->request_timestamp[i]; }
  wire[at++] = record->establishment_reject_code;

  return at;
}

/* Establishment Reject Message off the wire: 9 bytes from at, returning where the next byte lies */
static size_t decode_establishment_reject_message(EstablishmentRejectMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->request_timestamp[i] = wire[at++]; }
  record->establishment_reject_code = wire[at++];

  return at;
}

/* what was read of Establishment Reject Message is what was written, byte for byte */
static void equal_establishment_reject_message(const EstablishmentRejectMessage *read, const EstablishmentRejectMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->request_timestamp[i] == written->request_timestamp[i]); }
  assert(read->establishment_reject_code == written->establishment_reject_code);
}

/* Establishment Reject Message: written and read back, then read and written back */
static void check_establishment_reject_message(void) {
  EstablishmentRejectMessage sent;
  EstablishmentRejectMessage got;
  uint8_t wire[9];
  uint8_t again[9];

  any_establishment_reject_message(&sent);
  assert(encode_establishment_reject_message(&sent, wire, 0) == 9);
  assert(decode_establishment_reject_message(&got, wire, 0) == 9);
  equal_establishment_reject_message(&got, &sent);

  for (size_t i = 0; i < 9; i++) { wire[i] = arbitrary(); }
  assert(decode_establishment_reject_message(&got, wire, 0) == 9);
  assert(encode_establishment_reject_message(&got, again, 0) == 9);
  for (size_t i = 0; i < 9; i++) { assert(again[i] == wire[i]); }
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

/* ---- Retransmission Message: 20 bytes ---------------------------------------- */

/* RetransmissionMessage */
typedef struct {
  uint8_t next_seq_no[8];        /* bytes 0 to 7 */
  uint8_t request_timestamp[8];  /* bytes 8 to 15 */
  uint8_t count[4];              /* bytes 16 to 19 */
} RetransmissionMessage;

/* any Retransmission Message at all: every byte one the checker chooses */
static void any_retransmission_message(RetransmissionMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->next_seq_no[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->request_timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->count[i] = arbitrary(); }
}

/* Retransmission Message to the wire: 20 bytes from at, returning where the next byte goes */
static size_t encode_retransmission_message(const RetransmissionMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->next_seq_no[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->request_timestamp[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->count[i]; }

  return at;
}

/* Retransmission Message off the wire: 20 bytes from at, returning where the next byte lies */
static size_t decode_retransmission_message(RetransmissionMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->next_seq_no[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->request_timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->count[i] = wire[at++]; }

  return at;
}

/* what was read of Retransmission Message is what was written, byte for byte */
static void equal_retransmission_message(const RetransmissionMessage *read, const RetransmissionMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->next_seq_no[i] == written->next_seq_no[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->request_timestamp[i] == written->request_timestamp[i]); }
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

/* ---- Flood Reject Message: 16 bytes ------------------------------------------ */

/* FloodRejectMessage */
typedef struct {
  uint8_t cl_ord_id[8];       /* bytes 0 to 7 */
  uint8_t queue_size[4];      /* bytes 8 to 11 */
  uint8_t penalty_remain[4];  /* bytes 12 to 15 */
} FloodRejectMessage;

/* any Flood Reject Message at all: every byte one the checker chooses */
static void any_flood_reject_message(FloodRejectMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->cl_ord_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->queue_size[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->penalty_remain[i] = arbitrary(); }
}

/* Flood Reject Message to the wire: 16 bytes from at, returning where the next byte goes */
static size_t encode_flood_reject_message(const FloodRejectMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->cl_ord_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->queue_size[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->penalty_remain[i]; }

  return at;
}

/* Flood Reject Message off the wire: 16 bytes from at, returning where the next byte lies */
static size_t decode_flood_reject_message(FloodRejectMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->cl_ord_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->queue_size[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->penalty_remain[i] = wire[at++]; }

  return at;
}

/* what was read of Flood Reject Message is what was written, byte for byte */
static void equal_flood_reject_message(const FloodRejectMessage *read, const FloodRejectMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->cl_ord_id[i] == written->cl_ord_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->queue_size[i] == written->queue_size[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->penalty_remain[i] == written->penalty_remain[i]); }
}

/* Flood Reject Message: written and read back, then read and written back */
static void check_flood_reject_message(void) {
  FloodRejectMessage sent;
  FloodRejectMessage got;
  uint8_t wire[16];
  uint8_t again[16];

  any_flood_reject_message(&sent);
  assert(encode_flood_reject_message(&sent, wire, 0) == 16);
  assert(decode_flood_reject_message(&got, wire, 0) == 16);
  equal_flood_reject_message(&got, &sent);

  for (size_t i = 0; i < 16; i++) { wire[i] = arbitrary(); }
  assert(decode_flood_reject_message(&got, wire, 0) == 16);
  assert(encode_flood_reject_message(&got, again, 0) == 16);
  for (size_t i = 0; i < 16; i++) { assert(again[i] == wire[i]); }
}

/* ---- Session Reject Message: 13 bytes ---------------------------------------- */

/* SessionRejectMessage */
typedef struct {
  uint8_t cl_ord_id[8];           /* bytes 0 to 7 */
  uint8_t ref_tag_id[4];          /* bytes 8 to 11 */
  uint8_t session_reject_reason;  /* byte 12 */
} SessionRejectMessage;

/* any Session Reject Message at all: every byte one the checker chooses */
static void any_session_reject_message(SessionRejectMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->cl_ord_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->ref_tag_id[i] = arbitrary(); }
  record->session_reject_reason = arbitrary();
}

/* Session Reject Message to the wire: 13 bytes from at, returning where the next byte goes */
static size_t encode_session_reject_message(const SessionRejectMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->cl_ord_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->ref_tag_id[i]; }
  wire[at++] = record->session_reject_reason;

  return at;
}

/* Session Reject Message off the wire: 13 bytes from at, returning where the next byte lies */
static size_t decode_session_reject_message(SessionRejectMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->cl_ord_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->ref_tag_id[i] = wire[at++]; }
  record->session_reject_reason = wire[at++];

  return at;
}

/* what was read of Session Reject Message is what was written, byte for byte */
static void equal_session_reject_message(const SessionRejectMessage *read, const SessionRejectMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->cl_ord_id[i] == written->cl_ord_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->ref_tag_id[i] == written->ref_tag_id[i]); }
  assert(read->session_reject_reason == written->session_reject_reason);
}

/* Session Reject Message: written and read back, then read and written back */
static void check_session_reject_message(void) {
  SessionRejectMessage sent;
  SessionRejectMessage got;
  uint8_t wire[13];
  uint8_t again[13];

  any_session_reject_message(&sent);
  assert(encode_session_reject_message(&sent, wire, 0) == 13);
  assert(decode_session_reject_message(&got, wire, 0) == 13);
  equal_session_reject_message(&got, &sent);

  for (size_t i = 0; i < 13; i++) { wire[i] = arbitrary(); }
  assert(decode_session_reject_message(&got, wire, 0) == 13);
  assert(encode_session_reject_message(&got, again, 0) == 13);
  for (size_t i = 0; i < 13; i++) { assert(again[i] == wire[i]); }
}

/* ---- Business Message Reject Message: 20 bytes ------------------------------- */

/* BusinessMessageRejectMessage */
typedef struct {
  uint8_t cl_ord_id[8];       /* bytes 0 to 7 */
  uint8_t timestamp[8];       /* bytes 8 to 15 */
  uint8_t ord_rej_reason[4];  /* bytes 16 to 19 */
} BusinessMessageRejectMessage;

/* any Business Message Reject Message at all: every byte one the checker chooses */
static void any_business_message_reject_message(BusinessMessageRejectMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->cl_ord_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->ord_rej_reason[i] = arbitrary(); }
}

/* Business Message Reject Message to the wire: 20 bytes from at, returning where the next byte goes */
static size_t encode_business_message_reject_message(const BusinessMessageRejectMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->cl_ord_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->ord_rej_reason[i]; }

  return at;
}

/* Business Message Reject Message off the wire: 20 bytes from at, returning where the next byte lies */
static size_t decode_business_message_reject_message(BusinessMessageRejectMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->cl_ord_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->ord_rej_reason[i] = wire[at++]; }

  return at;
}

/* what was read of Business Message Reject Message is what was written, byte for byte */
static void equal_business_message_reject_message(const BusinessMessageRejectMessage *read, const BusinessMessageRejectMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->cl_ord_id[i] == written->cl_ord_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->ord_rej_reason[i] == written->ord_rej_reason[i]); }
}

/* Business Message Reject Message: written and read back, then read and written back */
static void check_business_message_reject_message(void) {
  BusinessMessageRejectMessage sent;
  BusinessMessageRejectMessage got;
  uint8_t wire[20];
  uint8_t again[20];

  any_business_message_reject_message(&sent);
  assert(encode_business_message_reject_message(&sent, wire, 0) == 20);
  assert(decode_business_message_reject_message(&got, wire, 0) == 20);
  equal_business_message_reject_message(&got, &sent);

  for (size_t i = 0; i < 20; i++) { wire[i] = arbitrary(); }
  assert(decode_business_message_reject_message(&got, wire, 0) == 20);
  assert(encode_business_message_reject_message(&got, again, 0) == 20);
  for (size_t i = 0; i < 20; i++) { assert(again[i] == wire[i]); }
}

/* ---- Order Mass Cancel Response Message: 20 bytes ---------------------------- */

/* OrderMassCancelResponseMessage */
typedef struct {
  uint8_t cl_ord_id[8];              /* bytes 0 to 7 */
  uint8_t timestamp[8];              /* bytes 8 to 15 */
  uint8_t total_affected_orders[4];  /* bytes 16 to 19 */
} OrderMassCancelResponseMessage;

/* any Order Mass Cancel Response Message at all: every byte one the checker chooses */
static void any_order_mass_cancel_response_message(OrderMassCancelResponseMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->cl_ord_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->total_affected_orders[i] = arbitrary(); }
}

/* Order Mass Cancel Response Message to the wire: 20 bytes from at, returning where the next byte goes */
static size_t encode_order_mass_cancel_response_message(const OrderMassCancelResponseMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->cl_ord_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->total_affected_orders[i]; }

  return at;
}

/* Order Mass Cancel Response Message off the wire: 20 bytes from at, returning where the next byte lies */
static size_t decode_order_mass_cancel_response_message(OrderMassCancelResponseMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->cl_ord_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->total_affected_orders[i] = wire[at++]; }

  return at;
}

/* what was read of Order Mass Cancel Response Message is what was written, byte for byte */
static void equal_order_mass_cancel_response_message(const OrderMassCancelResponseMessage *read, const OrderMassCancelResponseMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->cl_ord_id[i] == written->cl_ord_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->total_affected_orders[i] == written->total_affected_orders[i]); }
}

/* Order Mass Cancel Response Message: written and read back, then read and written back */
static void check_order_mass_cancel_response_message(void) {
  OrderMassCancelResponseMessage sent;
  OrderMassCancelResponseMessage got;
  uint8_t wire[20];
  uint8_t again[20];

  any_order_mass_cancel_response_message(&sent);
  assert(encode_order_mass_cancel_response_message(&sent, wire, 0) == 20);
  assert(decode_order_mass_cancel_response_message(&got, wire, 0) == 20);
  equal_order_mass_cancel_response_message(&got, &sent);

  for (size_t i = 0; i < 20; i++) { wire[i] = arbitrary(); }
  assert(decode_order_mass_cancel_response_message(&got, wire, 0) == 20);
  assert(encode_order_mass_cancel_response_message(&got, again, 0) == 20);
  for (size_t i = 0; i < 20; i++) { assert(again[i] == wire[i]); }
}

/* ---- Empty Book Message: 12 bytes -------------------------------------------- */

/* EmptyBookMessage */
typedef struct {
  uint8_t timestamp[8];           /* bytes 0 to 7 */
  uint8_t trading_session_id[4];  /* bytes 8 to 11 */
} EmptyBookMessage;

/* any Empty Book Message at all: every byte one the checker chooses */
static void any_empty_book_message(EmptyBookMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->trading_session_id[i] = arbitrary(); }
}

/* Empty Book Message to the wire: 12 bytes from at, returning where the next byte goes */
static size_t encode_empty_book_message(const EmptyBookMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->trading_session_id[i]; }

  return at;
}

/* Empty Book Message off the wire: 12 bytes from at, returning where the next byte lies */
static size_t decode_empty_book_message(EmptyBookMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->trading_session_id[i] = wire[at++]; }

  return at;
}

/* what was read of Empty Book Message is what was written, byte for byte */
static void equal_empty_book_message(const EmptyBookMessage *read, const EmptyBookMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->trading_session_id[i] == written->trading_session_id[i]); }
}

/* Empty Book Message: written and read back, then read and written back */
static void check_empty_book_message(void) {
  EmptyBookMessage sent;
  EmptyBookMessage got;
  uint8_t wire[12];
  uint8_t again[12];

  any_empty_book_message(&sent);
  assert(encode_empty_book_message(&sent, wire, 0) == 12);
  assert(decode_empty_book_message(&got, wire, 0) == 12);
  equal_empty_book_message(&got, &sent);

  for (size_t i = 0; i < 12; i++) { wire[i] = arbitrary(); }
  assert(decode_empty_book_message(&got, wire, 0) == 12);
  assert(encode_empty_book_message(&got, again, 0) == 12);
  for (size_t i = 0; i < 12; i++) { assert(again[i] == wire[i]); }
}

/* ---- System Event Message: 21 bytes ------------------------------------------ */

/* SystemEventMessage */
typedef struct {
  uint8_t timestamp[8];           /* bytes 0 to 7 */
  uint8_t event_id[8];            /* bytes 8 to 15 */
  uint8_t trading_session_id[4];  /* bytes 16 to 19 */
  uint8_t trad_ses_event;         /* byte 20 */
} SystemEventMessage;

/* any System Event Message at all: every byte one the checker chooses */
static void any_system_event_message(SystemEventMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->event_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->trading_session_id[i] = arbitrary(); }
  record->trad_ses_event = arbitrary();
}

/* System Event Message to the wire: 21 bytes from at, returning where the next byte goes */
static size_t encode_system_event_message(const SystemEventMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->event_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->trading_session_id[i]; }
  wire[at++] = record->trad_ses_event;

  return at;
}

/* System Event Message off the wire: 21 bytes from at, returning where the next byte lies */
static size_t decode_system_event_message(SystemEventMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->event_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->trading_session_id[i] = wire[at++]; }
  record->trad_ses_event = wire[at++];

  return at;
}

/* what was read of System Event Message is what was written, byte for byte */
static void equal_system_event_message(const SystemEventMessage *read, const SystemEventMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->event_id[i] == written->event_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->trading_session_id[i] == written->trading_session_id[i]); }
  assert(read->trad_ses_event == written->trad_ses_event);
}

/* System Event Message: written and read back, then read and written back */
static void check_system_event_message(void) {
  SystemEventMessage sent;
  SystemEventMessage got;
  uint8_t wire[21];
  uint8_t again[21];

  any_system_event_message(&sent);
  assert(encode_system_event_message(&sent, wire, 0) == 21);
  assert(decode_system_event_message(&got, wire, 0) == 21);
  equal_system_event_message(&got, &sent);

  for (size_t i = 0; i < 21; i++) { wire[i] = arbitrary(); }
  assert(decode_system_event_message(&got, wire, 0) == 21);
  assert(encode_system_event_message(&got, again, 0) == 21);
  for (size_t i = 0; i < 21; i++) { assert(again[i] == wire[i]); }
}

/* ---- What esbmc checks ------------------------------------------------------- */

/* every record of the protocol, each on its own buffers */
static void checks(void) {
  check_sbe_header();
  check_establishment_ack_message();
  check_establishment_reject_message();
  check_terminate_message();
  check_retransmission_message();
  check_sequence_message();
  check_flood_reject_message();
  check_session_reject_message();
  check_business_message_reject_message();
  check_order_mass_cancel_response_message();
  check_empty_book_message();
  check_system_event_message();
}

int main(void) {
#ifdef CONCRETE
  for (pattern = 0; pattern < 4; pattern++) { checks(); }
#else
  checks();
#endif

  return 0;
}
