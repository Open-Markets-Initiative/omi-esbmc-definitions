// cme/ebs/ilink3/Ebs_iLink3_v8_2_Server.c
/*
 * CME Group iLink 3
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
 *   - a field read in bits
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

/* Template ID and length of message root */
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

/* ---- Negotiation Reject: 68 bytes -------------------------------------------- */

/* The Negotiation Reject message is sent when CME rejects a Negotiate message sent by the customer. */
typedef struct {
  uint8_t reason[48];                 /* bytes 0 to 47 */
  uint8_t uuid[8];                    /* bytes 48 to 55 */
  uint8_t request_timestamp[8];       /* bytes 56 to 63 */
  uint8_t error_codes[2];             /* bytes 64 to 65 */
  uint8_t fault_tolerance_indicator;  /* byte 66 */
  uint8_t split_msg;                  /* byte 67 */
} NegotiationReject;

/* any Negotiation Reject at all: every byte one the checker chooses */
static void any_negotiation_reject(NegotiationReject *record) {
  for (size_t i = 0; i < 48; i++) { record->reason[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->uuid[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->request_timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->error_codes[i] = arbitrary(); }
  record->fault_tolerance_indicator = arbitrary();
  record->split_msg = arbitrary();
}

/* Negotiation Reject to the wire: 68 bytes from at, returning where the next byte goes */
static size_t encode_negotiation_reject(const NegotiationReject *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 48; i++) { wire[at++] = record->reason[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->uuid[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->request_timestamp[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->error_codes[i]; }
  wire[at++] = record->fault_tolerance_indicator;
  wire[at++] = record->split_msg;

  return at;
}

/* Negotiation Reject off the wire: 68 bytes from at, returning where the next byte lies */
static size_t decode_negotiation_reject(NegotiationReject *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 48; i++) { record->reason[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->uuid[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->request_timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->error_codes[i] = wire[at++]; }
  record->fault_tolerance_indicator = wire[at++];
  record->split_msg = wire[at++];

  return at;
}

/* what was read of Negotiation Reject is what was written, byte for byte */
static void equal_negotiation_reject(const NegotiationReject *read, const NegotiationReject *written) {
  for (size_t i = 0; i < 48; i++) { assert(read->reason[i] == written->reason[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->uuid[i] == written->uuid[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->request_timestamp[i] == written->request_timestamp[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->error_codes[i] == written->error_codes[i]); }
  assert(read->fault_tolerance_indicator == written->fault_tolerance_indicator);
  assert(read->split_msg == written->split_msg);
}

/* Negotiation Reject: written and read back, then read and written back */
static void check_negotiation_reject(void) {
  NegotiationReject sent;
  NegotiationReject got;
  uint8_t wire[68];
  uint8_t again[68];

  any_negotiation_reject(&sent);
  assert(encode_negotiation_reject(&sent, wire, 0) == 68);
  assert(decode_negotiation_reject(&got, wire, 0) == 68);
  equal_negotiation_reject(&got, &sent);

  for (size_t i = 0; i < 68; i++) { wire[i] = arbitrary(); }
  assert(decode_negotiation_reject(&got, wire, 0) == 68);
  assert(encode_negotiation_reject(&got, again, 0) == 68);
  for (size_t i = 0; i < 68; i++) { assert(again[i] == wire[i]); }
}

/* ---- Establishment Ack: 38 bytes --------------------------------------------- */

/* The Establishment Acknowledgment message is sent when an Establish message from a customer is accepted by CME. */
typedef struct {
  uint8_t uuid[8];                             /* bytes 0 to 7 */
  uint8_t request_timestamp[8];                /* bytes 8 to 15 */
  uint8_t next_seq_no[4];                      /* bytes 16 to 19 */
  uint8_t previous_seq_no[4];                  /* bytes 20 to 23 */
  uint8_t previous_uuid[8];                    /* bytes 24 to 31 */
  uint8_t keep_alive_interval[2];              /* bytes 32 to 33 */
  uint8_t secret_key_secure_id_expiration[2];  /* bytes 34 to 35 */
  uint8_t fault_tolerance_indicator;           /* byte 36 */
  uint8_t split_msg;                           /* byte 37 */
} EstablishmentAck;

/* any Establishment Ack at all: every byte one the checker chooses */
static void any_establishment_ack(EstablishmentAck *record) {
  for (size_t i = 0; i < 8; i++) { record->uuid[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->request_timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->next_seq_no[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->previous_seq_no[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->previous_uuid[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->keep_alive_interval[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->secret_key_secure_id_expiration[i] = arbitrary(); }
  record->fault_tolerance_indicator = arbitrary();
  record->split_msg = arbitrary();
}

/* Establishment Ack to the wire: 38 bytes from at, returning where the next byte goes */
static size_t encode_establishment_ack(const EstablishmentAck *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->uuid[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->request_timestamp[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->next_seq_no[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->previous_seq_no[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->previous_uuid[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->keep_alive_interval[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->secret_key_secure_id_expiration[i]; }
  wire[at++] = record->fault_tolerance_indicator;
  wire[at++] = record->split_msg;

  return at;
}

/* Establishment Ack off the wire: 38 bytes from at, returning where the next byte lies */
static size_t decode_establishment_ack(EstablishmentAck *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->uuid[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->request_timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->next_seq_no[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->previous_seq_no[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->previous_uuid[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->keep_alive_interval[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->secret_key_secure_id_expiration[i] = wire[at++]; }
  record->fault_tolerance_indicator = wire[at++];
  record->split_msg = wire[at++];

  return at;
}

/* what was read of Establishment Ack is what was written, byte for byte */
static void equal_establishment_ack(const EstablishmentAck *read, const EstablishmentAck *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->uuid[i] == written->uuid[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->request_timestamp[i] == written->request_timestamp[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->next_seq_no[i] == written->next_seq_no[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->previous_seq_no[i] == written->previous_seq_no[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->previous_uuid[i] == written->previous_uuid[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->keep_alive_interval[i] == written->keep_alive_interval[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->secret_key_secure_id_expiration[i] == written->secret_key_secure_id_expiration[i]); }
  assert(read->fault_tolerance_indicator == written->fault_tolerance_indicator);
  assert(read->split_msg == written->split_msg);
}

/* Establishment Ack: written and read back, then read and written back */
static void check_establishment_ack(void) {
  EstablishmentAck sent;
  EstablishmentAck got;
  uint8_t wire[38];
  uint8_t again[38];

  any_establishment_ack(&sent);
  assert(encode_establishment_ack(&sent, wire, 0) == 38);
  assert(decode_establishment_ack(&got, wire, 0) == 38);
  equal_establishment_ack(&got, &sent);

  for (size_t i = 0; i < 38; i++) { wire[i] = arbitrary(); }
  assert(decode_establishment_ack(&got, wire, 0) == 38);
  assert(encode_establishment_ack(&got, again, 0) == 38);
  for (size_t i = 0; i < 38; i++) { assert(again[i] == wire[i]); }
}

/* ---- Establishment Reject: 72 bytes ------------------------------------------ */

/* The Establishment Reject message is sent when an Establish message from the customer is rejected by CME. */
typedef struct {
  uint8_t reason[48];                 /* bytes 0 to 47 */
  uint8_t uuid[8];                    /* bytes 48 to 55 */
  uint8_t request_timestamp[8];       /* bytes 56 to 63 */
  uint8_t next_seq_no[4];             /* bytes 64 to 67 */
  uint8_t error_codes[2];             /* bytes 68 to 69 */
  uint8_t fault_tolerance_indicator;  /* byte 70 */
  uint8_t split_msg;                  /* byte 71 */
} EstablishmentReject;

/* any Establishment Reject at all: every byte one the checker chooses */
static void any_establishment_reject(EstablishmentReject *record) {
  for (size_t i = 0; i < 48; i++) { record->reason[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->uuid[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->request_timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->next_seq_no[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->error_codes[i] = arbitrary(); }
  record->fault_tolerance_indicator = arbitrary();
  record->split_msg = arbitrary();
}

/* Establishment Reject to the wire: 72 bytes from at, returning where the next byte goes */
static size_t encode_establishment_reject(const EstablishmentReject *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 48; i++) { wire[at++] = record->reason[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->uuid[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->request_timestamp[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->next_seq_no[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->error_codes[i]; }
  wire[at++] = record->fault_tolerance_indicator;
  wire[at++] = record->split_msg;

  return at;
}

/* Establishment Reject off the wire: 72 bytes from at, returning where the next byte lies */
static size_t decode_establishment_reject(EstablishmentReject *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 48; i++) { record->reason[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->uuid[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->request_timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->next_seq_no[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->error_codes[i] = wire[at++]; }
  record->fault_tolerance_indicator = wire[at++];
  record->split_msg = wire[at++];

  return at;
}

/* what was read of Establishment Reject is what was written, byte for byte */
static void equal_establishment_reject(const EstablishmentReject *read, const EstablishmentReject *written) {
  for (size_t i = 0; i < 48; i++) { assert(read->reason[i] == written->reason[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->uuid[i] == written->uuid[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->request_timestamp[i] == written->request_timestamp[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->next_seq_no[i] == written->next_seq_no[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->error_codes[i] == written->error_codes[i]); }
  assert(read->fault_tolerance_indicator == written->fault_tolerance_indicator);
  assert(read->split_msg == written->split_msg);
}

/* Establishment Reject: written and read back, then read and written back */
static void check_establishment_reject(void) {
  EstablishmentReject sent;
  EstablishmentReject got;
  uint8_t wire[72];
  uint8_t again[72];

  any_establishment_reject(&sent);
  assert(encode_establishment_reject(&sent, wire, 0) == 72);
  assert(decode_establishment_reject(&got, wire, 0) == 72);
  equal_establishment_reject(&got, &sent);

  for (size_t i = 0; i < 72; i++) { wire[i] = arbitrary(); }
  assert(decode_establishment_reject(&got, wire, 0) == 72);
  assert(encode_establishment_reject(&got, again, 0) == 72);
  for (size_t i = 0; i < 72; i++) { assert(again[i] == wire[i]); }
}

/* ---- Sequence: 14 bytes ------------------------------------------------------ */

/* The Sequence message is used in both Recoverable (CME to customer) and Idempotent (customer to CME) flows. */
typedef struct {
  uint8_t uuid[8];                     /* bytes 0 to 7 */
  uint8_t next_seq_no[4];              /* bytes 8 to 11 */
  uint8_t fault_tolerance_indicator;   /* byte 12 */
  uint8_t keep_alive_interval_lapsed;  /* byte 13 */
} Sequence;

/* any Sequence at all: every byte one the checker chooses */
static void any_sequence(Sequence *record) {
  for (size_t i = 0; i < 8; i++) { record->uuid[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->next_seq_no[i] = arbitrary(); }
  record->fault_tolerance_indicator = arbitrary();
  record->keep_alive_interval_lapsed = arbitrary();
}

/* Sequence to the wire: 14 bytes from at, returning where the next byte goes */
static size_t encode_sequence(const Sequence *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->uuid[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->next_seq_no[i]; }
  wire[at++] = record->fault_tolerance_indicator;
  wire[at++] = record->keep_alive_interval_lapsed;

  return at;
}

/* Sequence off the wire: 14 bytes from at, returning where the next byte lies */
static size_t decode_sequence(Sequence *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->uuid[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->next_seq_no[i] = wire[at++]; }
  record->fault_tolerance_indicator = wire[at++];
  record->keep_alive_interval_lapsed = wire[at++];

  return at;
}

/* what was read of Sequence is what was written, byte for byte */
static void equal_sequence(const Sequence *read, const Sequence *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->uuid[i] == written->uuid[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->next_seq_no[i] == written->next_seq_no[i]); }
  assert(read->fault_tolerance_indicator == written->fault_tolerance_indicator);
  assert(read->keep_alive_interval_lapsed == written->keep_alive_interval_lapsed);
}

/* Sequence: written and read back, then read and written back */
static void check_sequence(void) {
  Sequence sent;
  Sequence got;
  uint8_t wire[14];
  uint8_t again[14];

  any_sequence(&sent);
  assert(encode_sequence(&sent, wire, 0) == 14);
  assert(decode_sequence(&got, wire, 0) == 14);
  equal_sequence(&got, &sent);

  for (size_t i = 0; i < 14; i++) { wire[i] = arbitrary(); }
  assert(decode_sequence(&got, wire, 0) == 14);
  assert(encode_sequence(&got, again, 0) == 14);
  for (size_t i = 0; i < 14; i++) { assert(again[i] == wire[i]); }
}

/* ---- Terminate: 67 bytes ----------------------------------------------------- */

/* The Terminate message is sent to indicate that the sender is going to disconnect the TCP socket connection. */
typedef struct {
  uint8_t reason[48];            /* bytes 0 to 47 */
  uint8_t uuid[8];               /* bytes 48 to 55 */
  uint8_t request_timestamp[8];  /* bytes 56 to 63 */
  uint8_t error_codes[2];        /* bytes 64 to 65 */
  uint8_t split_msg;             /* byte 66 */
} Terminate;

/* any Terminate at all: every byte one the checker chooses */
static void any_terminate(Terminate *record) {
  for (size_t i = 0; i < 48; i++) { record->reason[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->uuid[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->request_timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->error_codes[i] = arbitrary(); }
  record->split_msg = arbitrary();
}

/* Terminate to the wire: 67 bytes from at, returning where the next byte goes */
static size_t encode_terminate(const Terminate *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 48; i++) { wire[at++] = record->reason[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->uuid[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->request_timestamp[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->error_codes[i]; }
  wire[at++] = record->split_msg;

  return at;
}

/* Terminate off the wire: 67 bytes from at, returning where the next byte lies */
static size_t decode_terminate(Terminate *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 48; i++) { record->reason[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->uuid[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->request_timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->error_codes[i] = wire[at++]; }
  record->split_msg = wire[at++];

  return at;
}

/* what was read of Terminate is what was written, byte for byte */
static void equal_terminate(const Terminate *read, const Terminate *written) {
  for (size_t i = 0; i < 48; i++) { assert(read->reason[i] == written->reason[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->uuid[i] == written->uuid[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->request_timestamp[i] == written->request_timestamp[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->error_codes[i] == written->error_codes[i]); }
  assert(read->split_msg == written->split_msg);
}

/* Terminate: written and read back, then read and written back */
static void check_terminate(void) {
  Terminate sent;
  Terminate got;
  uint8_t wire[67];
  uint8_t again[67];

  any_terminate(&sent);
  assert(encode_terminate(&sent, wire, 0) == 67);
  assert(decode_terminate(&got, wire, 0) == 67);
  equal_terminate(&got, &sent);

  for (size_t i = 0; i < 67; i++) { wire[i] = arbitrary(); }
  assert(decode_terminate(&got, wire, 0) == 67);
  assert(encode_terminate(&got, again, 0) == 67);
  for (size_t i = 0; i < 67; i++) { assert(again[i] == wire[i]); }
}

/* ---- Retransmission: 31 bytes ------------------------------------------------ */

/* The Retransmission message is sent when a Retransmit Request message from the customer is accepted by CME. */
typedef struct {
  uint8_t uuid[8];               /* bytes 0 to 7 */
  uint8_t last_uuid[8];          /* bytes 8 to 15 */
  uint8_t request_timestamp[8];  /* bytes 16 to 23 */
  uint8_t from_seq_no[4];        /* bytes 24 to 27 */
  uint8_t msg_count_16[2];       /* bytes 28 to 29 */
  uint8_t split_msg;             /* byte 30 */
} Retransmission;

/* any Retransmission at all: every byte one the checker chooses */
static void any_retransmission(Retransmission *record) {
  for (size_t i = 0; i < 8; i++) { record->uuid[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->last_uuid[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->request_timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->from_seq_no[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->msg_count_16[i] = arbitrary(); }
  record->split_msg = arbitrary();
}

/* Retransmission to the wire: 31 bytes from at, returning where the next byte goes */
static size_t encode_retransmission(const Retransmission *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->uuid[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->last_uuid[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->request_timestamp[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->from_seq_no[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->msg_count_16[i]; }
  wire[at++] = record->split_msg;

  return at;
}

/* Retransmission off the wire: 31 bytes from at, returning where the next byte lies */
static size_t decode_retransmission(Retransmission *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->uuid[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->last_uuid[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->request_timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->from_seq_no[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->msg_count_16[i] = wire[at++]; }
  record->split_msg = wire[at++];

  return at;
}

/* what was read of Retransmission is what was written, byte for byte */
static void equal_retransmission(const Retransmission *read, const Retransmission *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->uuid[i] == written->uuid[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->last_uuid[i] == written->last_uuid[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->request_timestamp[i] == written->request_timestamp[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->from_seq_no[i] == written->from_seq_no[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->msg_count_16[i] == written->msg_count_16[i]); }
  assert(read->split_msg == written->split_msg);
}

/* Retransmission: written and read back, then read and written back */
static void check_retransmission(void) {
  Retransmission sent;
  Retransmission got;
  uint8_t wire[31];
  uint8_t again[31];

  any_retransmission(&sent);
  assert(encode_retransmission(&sent, wire, 0) == 31);
  assert(decode_retransmission(&got, wire, 0) == 31);
  equal_retransmission(&got, &sent);

  for (size_t i = 0; i < 31; i++) { wire[i] = arbitrary(); }
  assert(decode_retransmission(&got, wire, 0) == 31);
  assert(encode_retransmission(&got, again, 0) == 31);
  for (size_t i = 0; i < 31; i++) { assert(again[i] == wire[i]); }
}

/* ---- Retransmit Reject: 75 bytes --------------------------------------------- */

/* CME Globex sends a Retransmit Reject message when a Retransmit Request message from the customer is rejected. */
typedef struct {
  uint8_t reason[48];            /* bytes 0 to 47 */
  uint8_t uuid[8];               /* bytes 48 to 55 */
  uint8_t last_uuid[8];          /* bytes 56 to 63 */
  uint8_t request_timestamp[8];  /* bytes 64 to 71 */
  uint8_t error_codes[2];        /* bytes 72 to 73 */
  uint8_t split_msg;             /* byte 74 */
} RetransmitReject;

/* any Retransmit Reject at all: every byte one the checker chooses */
static void any_retransmit_reject(RetransmitReject *record) {
  for (size_t i = 0; i < 48; i++) { record->reason[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->uuid[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->last_uuid[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->request_timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->error_codes[i] = arbitrary(); }
  record->split_msg = arbitrary();
}

/* Retransmit Reject to the wire: 75 bytes from at, returning where the next byte goes */
static size_t encode_retransmit_reject(const RetransmitReject *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 48; i++) { wire[at++] = record->reason[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->uuid[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->last_uuid[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->request_timestamp[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->error_codes[i]; }
  wire[at++] = record->split_msg;

  return at;
}

/* Retransmit Reject off the wire: 75 bytes from at, returning where the next byte lies */
static size_t decode_retransmit_reject(RetransmitReject *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 48; i++) { record->reason[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->uuid[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->last_uuid[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->request_timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->error_codes[i] = wire[at++]; }
  record->split_msg = wire[at++];

  return at;
}

/* what was read of Retransmit Reject is what was written, byte for byte */
static void equal_retransmit_reject(const RetransmitReject *read, const RetransmitReject *written) {
  for (size_t i = 0; i < 48; i++) { assert(read->reason[i] == written->reason[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->uuid[i] == written->uuid[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->last_uuid[i] == written->last_uuid[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->request_timestamp[i] == written->request_timestamp[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->error_codes[i] == written->error_codes[i]); }
  assert(read->split_msg == written->split_msg);
}

/* Retransmit Reject: written and read back, then read and written back */
static void check_retransmit_reject(void) {
  RetransmitReject sent;
  RetransmitReject got;
  uint8_t wire[75];
  uint8_t again[75];

  any_retransmit_reject(&sent);
  assert(encode_retransmit_reject(&sent, wire, 0) == 75);
  assert(decode_retransmit_reject(&got, wire, 0) == 75);
  equal_retransmit_reject(&got, &sent);

  for (size_t i = 0; i < 75; i++) { wire[i] = arbitrary(); }
  assert(decode_retransmit_reject(&got, wire, 0) == 75);
  assert(encode_retransmit_reject(&got, again, 0) == 75);
  for (size_t i = 0; i < 75; i++) { assert(again[i] == wire[i]); }
}

/* ---- Not Applied: 17 bytes --------------------------------------------------- */

/* The Not Applied message is sent when CME detects a sequence gap from the customer. */
typedef struct {
  uint8_t uuid[8];         /* bytes 0 to 7 */
  uint8_t from_seq_no[4];  /* bytes 8 to 11 */
  uint8_t msg_count[4];    /* bytes 12 to 15 */
  uint8_t split_msg;       /* byte 16 */
} NotApplied;

/* any Not Applied at all: every byte one the checker chooses */
static void any_not_applied(NotApplied *record) {
  for (size_t i = 0; i < 8; i++) { record->uuid[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->from_seq_no[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->msg_count[i] = arbitrary(); }
  record->split_msg = arbitrary();
}

/* Not Applied to the wire: 17 bytes from at, returning where the next byte goes */
static size_t encode_not_applied(const NotApplied *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->uuid[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->from_seq_no[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->msg_count[i]; }
  wire[at++] = record->split_msg;

  return at;
}

/* Not Applied off the wire: 17 bytes from at, returning where the next byte lies */
static size_t decode_not_applied(NotApplied *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->uuid[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->from_seq_no[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->msg_count[i] = wire[at++]; }
  record->split_msg = wire[at++];

  return at;
}

/* what was read of Not Applied is what was written, byte for byte */
static void equal_not_applied(const NotApplied *read, const NotApplied *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->uuid[i] == written->uuid[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->from_seq_no[i] == written->from_seq_no[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->msg_count[i] == written->msg_count[i]); }
  assert(read->split_msg == written->split_msg);
}

/* Not Applied: written and read back, then read and written back */
static void check_not_applied(void) {
  NotApplied sent;
  NotApplied got;
  uint8_t wire[17];
  uint8_t again[17];

  any_not_applied(&sent);
  assert(encode_not_applied(&sent, wire, 0) == 17);
  assert(decode_not_applied(&got, wire, 0) == 17);
  equal_not_applied(&got, &sent);

  for (size_t i = 0; i < 17; i++) { wire[i] = arbitrary(); }
  assert(decode_not_applied(&got, wire, 0) == 17);
  assert(encode_not_applied(&got, again, 0) == 17);
  for (size_t i = 0; i < 17; i++) { assert(again[i] == wire[i]); }
}

/* ---- Group Size: 3 bytes ----------------------------------------------------- */

/* Repeating group dimensions */
typedef struct {
  uint8_t block_length[2];  /* bytes 0 to 1 */
  uint8_t num_in_group;     /* byte 2 */
} GroupSize;

/* any Group Size at all: every byte one the checker chooses */
static void any_group_size(GroupSize *record) {
  for (size_t i = 0; i < 2; i++) { record->block_length[i] = arbitrary(); }
  record->num_in_group = arbitrary();
}

/* Group Size to the wire: 3 bytes from at, returning where the next byte goes */
static size_t encode_group_size(const GroupSize *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->block_length[i]; }
  wire[at++] = record->num_in_group;

  return at;
}

/* Group Size off the wire: 3 bytes from at, returning where the next byte lies */
static size_t decode_group_size(GroupSize *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->block_length[i] = wire[at++]; }
  record->num_in_group = wire[at++];

  return at;
}

/* what was read of Group Size is what was written, byte for byte */
static void equal_group_size(const GroupSize *read, const GroupSize *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->block_length[i] == written->block_length[i]); }
  assert(read->num_in_group == written->num_in_group);
}

/* Group Size: written and read back, then read and written back */
static void check_group_size(void) {
  GroupSize sent;
  GroupSize got;
  uint8_t wire[3];
  uint8_t again[3];

  any_group_size(&sent);
  assert(encode_group_size(&sent, wire, 0) == 3);
  assert(decode_group_size(&got, wire, 0) == 3);
  equal_group_size(&got, &sent);

  for (size_t i = 0; i < 3; i++) { wire[i] = arbitrary(); }
  assert(decode_group_size(&got, wire, 0) == 3);
  assert(encode_group_size(&got, again, 0) == 3);
  for (size_t i = 0; i < 3; i++) { assert(again[i] == wire[i]); }
}

/* ---- Business Reject: 330 bytes ---------------------------------------------- */

/* The Business Message Reject message can reject an application-level message, which fulfills session level rules but fails the business rules. */
typedef struct {
  uint8_t seq_num[4];                             /* bytes 0 to 3 */
  uint8_t uuid[8];                                /* bytes 4 to 11 */
  uint8_t text[256];                              /* bytes 12 to 267 */
  uint8_t sender_id_optional[20];                 /* bytes 268 to 287 */
  uint8_t party_details_list_req_id_optional[8];  /* bytes 288 to 295 */
  uint8_t sending_time_epoch[8];                  /* bytes 296 to 303 */
  uint8_t business_reject_ref_id[8];              /* bytes 304 to 311 */
  uint8_t location_optional[5];                   /* bytes 312 to 316 */
  uint8_t ref_seq_num[4];                         /* bytes 317 to 320 */
  uint8_t ref_tag_id[2];                          /* bytes 321 to 322 */
  uint8_t business_reject_reason[2];              /* bytes 323 to 324 */
  uint8_t ref_msg_type[2];                        /* bytes 325 to 326 */
  uint8_t poss_retrans_flag;                      /* byte 327 */
  uint8_t manual_order_indicator_optional;        /* byte 328 */
  uint8_t split_msg;                              /* byte 329 */
} BusinessReject;

/* any Business Reject at all: every byte one the checker chooses */
static void any_business_reject(BusinessReject *record) {
  for (size_t i = 0; i < 4; i++) { record->seq_num[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->uuid[i] = arbitrary(); }
  for (size_t i = 0; i < 256; i++) { record->text[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->sender_id_optional[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->party_details_list_req_id_optional[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->sending_time_epoch[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->business_reject_ref_id[i] = arbitrary(); }
  for (size_t i = 0; i < 5; i++) { record->location_optional[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->ref_seq_num[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->ref_tag_id[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->business_reject_reason[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->ref_msg_type[i] = arbitrary(); }
  record->poss_retrans_flag = arbitrary();
  record->manual_order_indicator_optional = arbitrary();
  record->split_msg = arbitrary();
}

/* Business Reject to the wire: 330 bytes from at, returning where the next byte goes */
static size_t encode_business_reject(const BusinessReject *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->seq_num[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->uuid[i]; }
  for (size_t i = 0; i < 256; i++) { wire[at++] = record->text[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->sender_id_optional[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->party_details_list_req_id_optional[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->sending_time_epoch[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->business_reject_ref_id[i]; }
  for (size_t i = 0; i < 5; i++) { wire[at++] = record->location_optional[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->ref_seq_num[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->ref_tag_id[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->business_reject_reason[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->ref_msg_type[i]; }
  wire[at++] = record->poss_retrans_flag;
  wire[at++] = record->manual_order_indicator_optional;
  wire[at++] = record->split_msg;

  return at;
}

/* Business Reject off the wire: 330 bytes from at, returning where the next byte lies */
static size_t decode_business_reject(BusinessReject *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->seq_num[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->uuid[i] = wire[at++]; }
  for (size_t i = 0; i < 256; i++) { record->text[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->sender_id_optional[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->party_details_list_req_id_optional[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->sending_time_epoch[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->business_reject_ref_id[i] = wire[at++]; }
  for (size_t i = 0; i < 5; i++) { record->location_optional[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->ref_seq_num[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->ref_tag_id[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->business_reject_reason[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->ref_msg_type[i] = wire[at++]; }
  record->poss_retrans_flag = wire[at++];
  record->manual_order_indicator_optional = wire[at++];
  record->split_msg = wire[at++];

  return at;
}

/* what was read of Business Reject is what was written, byte for byte */
static void equal_business_reject(const BusinessReject *read, const BusinessReject *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->seq_num[i] == written->seq_num[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->uuid[i] == written->uuid[i]); }
  for (size_t i = 0; i < 256; i++) { assert(read->text[i] == written->text[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->sender_id_optional[i] == written->sender_id_optional[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->party_details_list_req_id_optional[i] == written->party_details_list_req_id_optional[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->sending_time_epoch[i] == written->sending_time_epoch[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->business_reject_ref_id[i] == written->business_reject_ref_id[i]); }
  for (size_t i = 0; i < 5; i++) { assert(read->location_optional[i] == written->location_optional[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->ref_seq_num[i] == written->ref_seq_num[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->ref_tag_id[i] == written->ref_tag_id[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->business_reject_reason[i] == written->business_reject_reason[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->ref_msg_type[i] == written->ref_msg_type[i]); }
  assert(read->poss_retrans_flag == written->poss_retrans_flag);
  assert(read->manual_order_indicator_optional == written->manual_order_indicator_optional);
  assert(read->split_msg == written->split_msg);
}

/* Business Reject: written and read back, then read and written back */
static void check_business_reject(void) {
  BusinessReject sent;
  BusinessReject got;
  uint8_t wire[330];
  uint8_t again[330];

  any_business_reject(&sent);
  assert(encode_business_reject(&sent, wire, 0) == 330);
  assert(decode_business_reject(&got, wire, 0) == 330);
  equal_business_reject(&got, &sent);

  for (size_t i = 0; i < 330; i++) { wire[i] = arbitrary(); }
  assert(decode_business_reject(&got, wire, 0) == 330);
  assert(encode_business_reject(&got, again, 0) == 330);
  for (size_t i = 0; i < 330; i++) { assert(again[i] == wire[i]); }
}

/* ---- Volatility: 9 bytes ----------------------------------------------------- */

/* ExecutionReportTradeSpreadLeg */
typedef struct {
  uint8_t mantissa[8];  /* bytes 0 to 7 */
  uint8_t exponent;     /* byte 8 */
} Volatility;

/* any Volatility at all: every byte one the checker chooses */
static void any_volatility(Volatility *record) {
  for (size_t i = 0; i < 8; i++) { record->mantissa[i] = arbitrary(); }
  record->exponent = arbitrary();
}

/* Volatility to the wire: 9 bytes from at, returning where the next byte goes */
static size_t encode_volatility(const Volatility *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->mantissa[i]; }
  wire[at++] = record->exponent;

  return at;
}

/* Volatility off the wire: 9 bytes from at, returning where the next byte lies */
static size_t decode_volatility(Volatility *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->mantissa[i] = wire[at++]; }
  record->exponent = wire[at++];

  return at;
}

/* what was read of Volatility is what was written, byte for byte */
static void equal_volatility(const Volatility *read, const Volatility *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->mantissa[i] == written->mantissa[i]); }
  assert(read->exponent == written->exponent);
}

/* Volatility: written and read back, then read and written back */
static void check_volatility(void) {
  Volatility sent;
  Volatility got;
  uint8_t wire[9];
  uint8_t again[9];

  any_volatility(&sent);
  assert(encode_volatility(&sent, wire, 0) == 9);
  assert(decode_volatility(&got, wire, 0) == 9);
  equal_volatility(&got, &sent);

  for (size_t i = 0; i < 9; i++) { wire[i] = arbitrary(); }
  assert(decode_volatility(&got, wire, 0) == 9);
  assert(encode_volatility(&got, again, 0) == 9);
  for (size_t i = 0; i < 9; i++) { assert(again[i] == wire[i]); }
}

/* ---- Option Delta: 5 bytes --------------------------------------------------- */

/* ExecutionReportTradeSpreadLeg */
typedef struct {
  uint8_t mantissa_32[4];  /* bytes 0 to 3 */
  uint8_t exponent;        /* byte 4 */
} OptionDelta;

/* any Option Delta at all: every byte one the checker chooses */
static void any_option_delta(OptionDelta *record) {
  for (size_t i = 0; i < 4; i++) { record->mantissa_32[i] = arbitrary(); }
  record->exponent = arbitrary();
}

/* Option Delta to the wire: 5 bytes from at, returning where the next byte goes */
static size_t encode_option_delta(const OptionDelta *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->mantissa_32[i]; }
  wire[at++] = record->exponent;

  return at;
}

/* Option Delta off the wire: 5 bytes from at, returning where the next byte lies */
static size_t decode_option_delta(OptionDelta *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->mantissa_32[i] = wire[at++]; }
  record->exponent = wire[at++];

  return at;
}

/* what was read of Option Delta is what was written, byte for byte */
static void equal_option_delta(const OptionDelta *read, const OptionDelta *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->mantissa_32[i] == written->mantissa_32[i]); }
  assert(read->exponent == written->exponent);
}

/* Option Delta: written and read back, then read and written back */
static void check_option_delta(void) {
  OptionDelta sent;
  OptionDelta got;
  uint8_t wire[5];
  uint8_t again[5];

  any_option_delta(&sent);
  assert(encode_option_delta(&sent, wire, 0) == 5);
  assert(decode_option_delta(&got, wire, 0) == 5);
  equal_option_delta(&got, &sent);

  for (size_t i = 0; i < 5; i++) { wire[i] = arbitrary(); }
  assert(decode_option_delta(&got, wire, 0) == 5);
  assert(encode_option_delta(&got, again, 0) == 5);
  for (size_t i = 0; i < 5; i++) { assert(again[i] == wire[i]); }
}

/* ---- Time To Expiration: 5 bytes --------------------------------------------- */

/* ExecutionReportTradeSpreadLeg */
typedef struct {
  uint8_t mantissa_32[4];  /* bytes 0 to 3 */
  uint8_t exponent;        /* byte 4 */
} TimeToExpiration;

/* any Time To Expiration at all: every byte one the checker chooses */
static void any_time_to_expiration(TimeToExpiration *record) {
  for (size_t i = 0; i < 4; i++) { record->mantissa_32[i] = arbitrary(); }
  record->exponent = arbitrary();
}

/* Time To Expiration to the wire: 5 bytes from at, returning where the next byte goes */
static size_t encode_time_to_expiration(const TimeToExpiration *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->mantissa_32[i]; }
  wire[at++] = record->exponent;

  return at;
}

/* Time To Expiration off the wire: 5 bytes from at, returning where the next byte lies */
static size_t decode_time_to_expiration(TimeToExpiration *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->mantissa_32[i] = wire[at++]; }
  record->exponent = wire[at++];

  return at;
}

/* what was read of Time To Expiration is what was written, byte for byte */
static void equal_time_to_expiration(const TimeToExpiration *read, const TimeToExpiration *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->mantissa_32[i] == written->mantissa_32[i]); }
  assert(read->exponent == written->exponent);
}

/* Time To Expiration: written and read back, then read and written back */
static void check_time_to_expiration(void) {
  TimeToExpiration sent;
  TimeToExpiration got;
  uint8_t wire[5];
  uint8_t again[5];

  any_time_to_expiration(&sent);
  assert(encode_time_to_expiration(&sent, wire, 0) == 5);
  assert(decode_time_to_expiration(&got, wire, 0) == 5);
  equal_time_to_expiration(&got, &sent);

  for (size_t i = 0; i < 5; i++) { wire[i] = arbitrary(); }
  assert(decode_time_to_expiration(&got, wire, 0) == 5);
  assert(encode_time_to_expiration(&got, again, 0) == 5);
  for (size_t i = 0; i < 5; i++) { assert(again[i] == wire[i]); }
}

/* ---- Risk Free Rate: 5 bytes ------------------------------------------------- */

/* ExecutionReportTradeSpreadLeg */
typedef struct {
  uint8_t mantissa_32[4];  /* bytes 0 to 3 */
  uint8_t exponent;        /* byte 4 */
} RiskFreeRate;

/* any Risk Free Rate at all: every byte one the checker chooses */
static void any_risk_free_rate(RiskFreeRate *record) {
  for (size_t i = 0; i < 4; i++) { record->mantissa_32[i] = arbitrary(); }
  record->exponent = arbitrary();
}

/* Risk Free Rate to the wire: 5 bytes from at, returning where the next byte goes */
static size_t encode_risk_free_rate(const RiskFreeRate *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->mantissa_32[i]; }
  wire[at++] = record->exponent;

  return at;
}

/* Risk Free Rate off the wire: 5 bytes from at, returning where the next byte lies */
static size_t decode_risk_free_rate(RiskFreeRate *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->mantissa_32[i] = wire[at++]; }
  record->exponent = wire[at++];

  return at;
}

/* what was read of Risk Free Rate is what was written, byte for byte */
static void equal_risk_free_rate(const RiskFreeRate *read, const RiskFreeRate *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->mantissa_32[i] == written->mantissa_32[i]); }
  assert(read->exponent == written->exponent);
}

/* Risk Free Rate: written and read back, then read and written back */
static void check_risk_free_rate(void) {
  RiskFreeRate sent;
  RiskFreeRate got;
  uint8_t wire[5];
  uint8_t again[5];

  any_risk_free_rate(&sent);
  assert(encode_risk_free_rate(&sent, wire, 0) == 5);
  assert(decode_risk_free_rate(&got, wire, 0) == 5);
  equal_risk_free_rate(&got, &sent);

  for (size_t i = 0; i < 5; i++) { wire[i] = arbitrary(); }
  assert(decode_risk_free_rate(&got, wire, 0) == 5);
  assert(encode_risk_free_rate(&got, again, 0) == 5);
  for (size_t i = 0; i < 5; i++) { assert(again[i] == wire[i]); }
}

/* ---- Order Cancel Reject: 401 bytes ------------------------------------------ */

/* The Order Cancel Reject message is issued upon receipt of a cancel request message which cannot be honored. */
typedef struct {
  uint8_t seq_num[4];                    /* bytes 0 to 3 */
  uint8_t uuid[8];                       /* bytes 4 to 11 */
  uint8_t text[256];                     /* bytes 12 to 267 */
  uint8_t exec_id[40];                   /* bytes 268 to 307 */
  uint8_t sender_id[20];                 /* bytes 308 to 327 */
  uint8_t cl_ord_id[20];                 /* bytes 328 to 347 */
  uint8_t party_details_list_req_id[8];  /* bytes 348 to 355 */
  uint8_t order_id[8];                   /* bytes 356 to 363 */
  uint8_t transact_time[8];              /* bytes 364 to 371 */
  uint8_t sending_time_epoch[8];         /* bytes 372 to 379 */
  uint8_t order_request_id[8];           /* bytes 380 to 387 */
  uint8_t location[5];                   /* bytes 388 to 392 */
  uint8_t cxl_rej_reason[2];             /* bytes 393 to 394 */
  uint8_t delay_duration[2];             /* bytes 395 to 396 */
  uint8_t manual_order_indicator;        /* byte 397 */
  uint8_t poss_retrans_flag;             /* byte 398 */
  uint8_t split_msg;                     /* byte 399 */
  uint8_t liquidity_flag;                /* byte 400 */
} OrderCancelReject;

/* any Order Cancel Reject at all: every byte one the checker chooses */
static void any_order_cancel_reject(OrderCancelReject *record) {
  for (size_t i = 0; i < 4; i++) { record->seq_num[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->uuid[i] = arbitrary(); }
  for (size_t i = 0; i < 256; i++) { record->text[i] = arbitrary(); }
  for (size_t i = 0; i < 40; i++) { record->exec_id[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->sender_id[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->party_details_list_req_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->transact_time[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->sending_time_epoch[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->order_request_id[i] = arbitrary(); }
  for (size_t i = 0; i < 5; i++) { record->location[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->cxl_rej_reason[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->delay_duration[i] = arbitrary(); }
  record->manual_order_indicator = arbitrary();
  record->poss_retrans_flag = arbitrary();
  record->split_msg = arbitrary();
  record->liquidity_flag = arbitrary();
}

/* Order Cancel Reject to the wire: 401 bytes from at, returning where the next byte goes */
static size_t encode_order_cancel_reject(const OrderCancelReject *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->seq_num[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->uuid[i]; }
  for (size_t i = 0; i < 256; i++) { wire[at++] = record->text[i]; }
  for (size_t i = 0; i < 40; i++) { wire[at++] = record->exec_id[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->sender_id[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->cl_ord_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->party_details_list_req_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->transact_time[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->sending_time_epoch[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_request_id[i]; }
  for (size_t i = 0; i < 5; i++) { wire[at++] = record->location[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->cxl_rej_reason[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->delay_duration[i]; }
  wire[at++] = record->manual_order_indicator;
  wire[at++] = record->poss_retrans_flag;
  wire[at++] = record->split_msg;
  wire[at++] = record->liquidity_flag;

  return at;
}

/* Order Cancel Reject off the wire: 401 bytes from at, returning where the next byte lies */
static size_t decode_order_cancel_reject(OrderCancelReject *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->seq_num[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->uuid[i] = wire[at++]; }
  for (size_t i = 0; i < 256; i++) { record->text[i] = wire[at++]; }
  for (size_t i = 0; i < 40; i++) { record->exec_id[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->sender_id[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->party_details_list_req_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->transact_time[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->sending_time_epoch[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->order_request_id[i] = wire[at++]; }
  for (size_t i = 0; i < 5; i++) { record->location[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->cxl_rej_reason[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->delay_duration[i] = wire[at++]; }
  record->manual_order_indicator = wire[at++];
  record->poss_retrans_flag = wire[at++];
  record->split_msg = wire[at++];
  record->liquidity_flag = wire[at++];

  return at;
}

/* what was read of Order Cancel Reject is what was written, byte for byte */
static void equal_order_cancel_reject(const OrderCancelReject *read, const OrderCancelReject *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->seq_num[i] == written->seq_num[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->uuid[i] == written->uuid[i]); }
  for (size_t i = 0; i < 256; i++) { assert(read->text[i] == written->text[i]); }
  for (size_t i = 0; i < 40; i++) { assert(read->exec_id[i] == written->exec_id[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->sender_id[i] == written->sender_id[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->cl_ord_id[i] == written->cl_ord_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->party_details_list_req_id[i] == written->party_details_list_req_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->order_id[i] == written->order_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->transact_time[i] == written->transact_time[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->sending_time_epoch[i] == written->sending_time_epoch[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->order_request_id[i] == written->order_request_id[i]); }
  for (size_t i = 0; i < 5; i++) { assert(read->location[i] == written->location[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->cxl_rej_reason[i] == written->cxl_rej_reason[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->delay_duration[i] == written->delay_duration[i]); }
  assert(read->manual_order_indicator == written->manual_order_indicator);
  assert(read->poss_retrans_flag == written->poss_retrans_flag);
  assert(read->split_msg == written->split_msg);
  assert(read->liquidity_flag == written->liquidity_flag);
}

/* Order Cancel Reject: written and read back, then read and written back */
static void check_order_cancel_reject(void) {
  OrderCancelReject sent;
  OrderCancelReject got;
  uint8_t wire[401];
  uint8_t again[401];

  any_order_cancel_reject(&sent);
  assert(encode_order_cancel_reject(&sent, wire, 0) == 401);
  assert(decode_order_cancel_reject(&got, wire, 0) == 401);
  equal_order_cancel_reject(&got, &sent);

  for (size_t i = 0; i < 401; i++) { wire[i] = arbitrary(); }
  assert(decode_order_cancel_reject(&got, wire, 0) == 401);
  assert(encode_order_cancel_reject(&got, again, 0) == 401);
  for (size_t i = 0; i < 401; i++) { assert(again[i] == wire[i]); }
}

/* ---- Order Cancel Replace Reject: 401 bytes ---------------------------------- */

/* The Order Cancel Replace Reject message is issued upon receipt of a cancel replace request message that cannot be honored. */
typedef struct {
  uint8_t seq_num[4];                    /* bytes 0 to 3 */
  uint8_t uuid[8];                       /* bytes 4 to 11 */
  uint8_t text[256];                     /* bytes 12 to 267 */
  uint8_t exec_id[40];                   /* bytes 268 to 307 */
  uint8_t sender_id[20];                 /* bytes 308 to 327 */
  uint8_t cl_ord_id[20];                 /* bytes 328 to 347 */
  uint8_t party_details_list_req_id[8];  /* bytes 348 to 355 */
  uint8_t order_id[8];                   /* bytes 356 to 363 */
  uint8_t transact_time[8];              /* bytes 364 to 371 */
  uint8_t sending_time_epoch[8];         /* bytes 372 to 379 */
  uint8_t order_request_id[8];           /* bytes 380 to 387 */
  uint8_t location[5];                   /* bytes 388 to 392 */
  uint8_t cxl_rej_reason[2];             /* bytes 393 to 394 */
  uint8_t delay_duration[2];             /* bytes 395 to 396 */
  uint8_t manual_order_indicator;        /* byte 397 */
  uint8_t poss_retrans_flag;             /* byte 398 */
  uint8_t split_msg;                     /* byte 399 */
  uint8_t liquidity_flag;                /* byte 400 */
} OrderCancelReplaceReject;

/* any Order Cancel Replace Reject at all: every byte one the checker chooses */
static void any_order_cancel_replace_reject(OrderCancelReplaceReject *record) {
  for (size_t i = 0; i < 4; i++) { record->seq_num[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->uuid[i] = arbitrary(); }
  for (size_t i = 0; i < 256; i++) { record->text[i] = arbitrary(); }
  for (size_t i = 0; i < 40; i++) { record->exec_id[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->sender_id[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->party_details_list_req_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->transact_time[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->sending_time_epoch[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->order_request_id[i] = arbitrary(); }
  for (size_t i = 0; i < 5; i++) { record->location[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->cxl_rej_reason[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->delay_duration[i] = arbitrary(); }
  record->manual_order_indicator = arbitrary();
  record->poss_retrans_flag = arbitrary();
  record->split_msg = arbitrary();
  record->liquidity_flag = arbitrary();
}

/* Order Cancel Replace Reject to the wire: 401 bytes from at, returning where the next byte goes */
static size_t encode_order_cancel_replace_reject(const OrderCancelReplaceReject *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->seq_num[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->uuid[i]; }
  for (size_t i = 0; i < 256; i++) { wire[at++] = record->text[i]; }
  for (size_t i = 0; i < 40; i++) { wire[at++] = record->exec_id[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->sender_id[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->cl_ord_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->party_details_list_req_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->transact_time[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->sending_time_epoch[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_request_id[i]; }
  for (size_t i = 0; i < 5; i++) { wire[at++] = record->location[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->cxl_rej_reason[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->delay_duration[i]; }
  wire[at++] = record->manual_order_indicator;
  wire[at++] = record->poss_retrans_flag;
  wire[at++] = record->split_msg;
  wire[at++] = record->liquidity_flag;

  return at;
}

/* Order Cancel Replace Reject off the wire: 401 bytes from at, returning where the next byte lies */
static size_t decode_order_cancel_replace_reject(OrderCancelReplaceReject *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->seq_num[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->uuid[i] = wire[at++]; }
  for (size_t i = 0; i < 256; i++) { record->text[i] = wire[at++]; }
  for (size_t i = 0; i < 40; i++) { record->exec_id[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->sender_id[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->party_details_list_req_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->transact_time[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->sending_time_epoch[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->order_request_id[i] = wire[at++]; }
  for (size_t i = 0; i < 5; i++) { record->location[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->cxl_rej_reason[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->delay_duration[i] = wire[at++]; }
  record->manual_order_indicator = wire[at++];
  record->poss_retrans_flag = wire[at++];
  record->split_msg = wire[at++];
  record->liquidity_flag = wire[at++];

  return at;
}

/* what was read of Order Cancel Replace Reject is what was written, byte for byte */
static void equal_order_cancel_replace_reject(const OrderCancelReplaceReject *read, const OrderCancelReplaceReject *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->seq_num[i] == written->seq_num[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->uuid[i] == written->uuid[i]); }
  for (size_t i = 0; i < 256; i++) { assert(read->text[i] == written->text[i]); }
  for (size_t i = 0; i < 40; i++) { assert(read->exec_id[i] == written->exec_id[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->sender_id[i] == written->sender_id[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->cl_ord_id[i] == written->cl_ord_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->party_details_list_req_id[i] == written->party_details_list_req_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->order_id[i] == written->order_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->transact_time[i] == written->transact_time[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->sending_time_epoch[i] == written->sending_time_epoch[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->order_request_id[i] == written->order_request_id[i]); }
  for (size_t i = 0; i < 5; i++) { assert(read->location[i] == written->location[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->cxl_rej_reason[i] == written->cxl_rej_reason[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->delay_duration[i] == written->delay_duration[i]); }
  assert(read->manual_order_indicator == written->manual_order_indicator);
  assert(read->poss_retrans_flag == written->poss_retrans_flag);
  assert(read->split_msg == written->split_msg);
  assert(read->liquidity_flag == written->liquidity_flag);
}

/* Order Cancel Replace Reject: written and read back, then read and written back */
static void check_order_cancel_replace_reject(void) {
  OrderCancelReplaceReject sent;
  OrderCancelReplaceReject got;
  uint8_t wire[401];
  uint8_t again[401];

  any_order_cancel_replace_reject(&sent);
  assert(encode_order_cancel_replace_reject(&sent, wire, 0) == 401);
  assert(decode_order_cancel_replace_reject(&got, wire, 0) == 401);
  equal_order_cancel_replace_reject(&got, &sent);

  for (size_t i = 0; i < 401; i++) { wire[i] = arbitrary(); }
  assert(decode_order_cancel_replace_reject(&got, wire, 0) == 401);
  assert(encode_order_cancel_replace_reject(&got, again, 0) == 401);
  for (size_t i = 0; i < 401; i++) { assert(again[i] == wire[i]); }
}

/* ---- Request For Quote Ack: 350 bytes ---------------------------------------- */

/* Request for Quote Acknowledgment message is used in response to a Request for Quote message to either accept it or reject it. */
typedef struct {
  uint8_t seq_num[4];                    /* bytes 0 to 3 */
  uint8_t uuid[8];                       /* bytes 4 to 11 */
  uint8_t text[256];                     /* bytes 12 to 267 */
  uint8_t sender_id[20];                 /* bytes 268 to 287 */
  uint8_t exchange_quote_req_id[17];     /* bytes 288 to 304 */
  uint8_t party_details_list_req_id[8];  /* bytes 305 to 312 */
  uint8_t request_time[8];               /* bytes 313 to 320 */
  uint8_t sending_time_epoch[8];         /* bytes 321 to 328 */
  uint8_t quote_req_id[8];               /* bytes 329 to 336 */
  uint8_t location[5];                   /* bytes 337 to 341 */
  uint8_t quote_reject_reason[2];        /* bytes 342 to 343 */
  uint8_t delay_duration[2];             /* bytes 344 to 345 */
  uint8_t quote_ack_status;              /* byte 346 */
  uint8_t manual_order_indicator;        /* byte 347 */
  uint8_t split_msg;                     /* byte 348 */
  uint8_t poss_retrans_flag;             /* byte 349 */
} RequestForQuoteAck;

/* any Request For Quote Ack at all: every byte one the checker chooses */
static void any_request_for_quote_ack(RequestForQuoteAck *record) {
  for (size_t i = 0; i < 4; i++) { record->seq_num[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->uuid[i] = arbitrary(); }
  for (size_t i = 0; i < 256; i++) { record->text[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->sender_id[i] = arbitrary(); }
  for (size_t i = 0; i < 17; i++) { record->exchange_quote_req_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->party_details_list_req_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->request_time[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->sending_time_epoch[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->quote_req_id[i] = arbitrary(); }
  for (size_t i = 0; i < 5; i++) { record->location[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->quote_reject_reason[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->delay_duration[i] = arbitrary(); }
  record->quote_ack_status = arbitrary();
  record->manual_order_indicator = arbitrary();
  record->split_msg = arbitrary();
  record->poss_retrans_flag = arbitrary();
}

/* Request For Quote Ack to the wire: 350 bytes from at, returning where the next byte goes */
static size_t encode_request_for_quote_ack(const RequestForQuoteAck *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->seq_num[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->uuid[i]; }
  for (size_t i = 0; i < 256; i++) { wire[at++] = record->text[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->sender_id[i]; }
  for (size_t i = 0; i < 17; i++) { wire[at++] = record->exchange_quote_req_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->party_details_list_req_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->request_time[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->sending_time_epoch[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->quote_req_id[i]; }
  for (size_t i = 0; i < 5; i++) { wire[at++] = record->location[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->quote_reject_reason[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->delay_duration[i]; }
  wire[at++] = record->quote_ack_status;
  wire[at++] = record->manual_order_indicator;
  wire[at++] = record->split_msg;
  wire[at++] = record->poss_retrans_flag;

  return at;
}

/* Request For Quote Ack off the wire: 350 bytes from at, returning where the next byte lies */
static size_t decode_request_for_quote_ack(RequestForQuoteAck *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->seq_num[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->uuid[i] = wire[at++]; }
  for (size_t i = 0; i < 256; i++) { record->text[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->sender_id[i] = wire[at++]; }
  for (size_t i = 0; i < 17; i++) { record->exchange_quote_req_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->party_details_list_req_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->request_time[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->sending_time_epoch[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->quote_req_id[i] = wire[at++]; }
  for (size_t i = 0; i < 5; i++) { record->location[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->quote_reject_reason[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->delay_duration[i] = wire[at++]; }
  record->quote_ack_status = wire[at++];
  record->manual_order_indicator = wire[at++];
  record->split_msg = wire[at++];
  record->poss_retrans_flag = wire[at++];

  return at;
}

/* what was read of Request For Quote Ack is what was written, byte for byte */
static void equal_request_for_quote_ack(const RequestForQuoteAck *read, const RequestForQuoteAck *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->seq_num[i] == written->seq_num[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->uuid[i] == written->uuid[i]); }
  for (size_t i = 0; i < 256; i++) { assert(read->text[i] == written->text[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->sender_id[i] == written->sender_id[i]); }
  for (size_t i = 0; i < 17; i++) { assert(read->exchange_quote_req_id[i] == written->exchange_quote_req_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->party_details_list_req_id[i] == written->party_details_list_req_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->request_time[i] == written->request_time[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->sending_time_epoch[i] == written->sending_time_epoch[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->quote_req_id[i] == written->quote_req_id[i]); }
  for (size_t i = 0; i < 5; i++) { assert(read->location[i] == written->location[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->quote_reject_reason[i] == written->quote_reject_reason[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->delay_duration[i] == written->delay_duration[i]); }
  assert(read->quote_ack_status == written->quote_ack_status);
  assert(read->manual_order_indicator == written->manual_order_indicator);
  assert(read->split_msg == written->split_msg);
  assert(read->poss_retrans_flag == written->poss_retrans_flag);
}

/* Request For Quote Ack: written and read back, then read and written back */
static void check_request_for_quote_ack(void) {
  RequestForQuoteAck sent;
  RequestForQuoteAck got;
  uint8_t wire[350];
  uint8_t again[350];

  any_request_for_quote_ack(&sent);
  assert(encode_request_for_quote_ack(&sent, wire, 0) == 350);
  assert(decode_request_for_quote_ack(&got, wire, 0) == 350);
  equal_request_for_quote_ack(&got, &sent);

  for (size_t i = 0; i < 350; i++) { wire[i] = arbitrary(); }
  assert(decode_request_for_quote_ack(&got, wire, 0) == 350);
  assert(encode_request_for_quote_ack(&got, again, 0) == 350);
  for (size_t i = 0; i < 350; i++) { assert(again[i] == wire[i]); }
}

/* ---- Maturity Month Year: 5 bytes -------------------------------------------- */

/* SecurityDefinitionResponse */
typedef struct {
  uint8_t year[2];  /* bytes 0 to 1 */
  uint8_t month;    /* byte 2 */
  uint8_t day;      /* byte 3 */
  uint8_t week;     /* byte 4 */
} MaturityMonthYear;

/* any Maturity Month Year at all: every byte one the checker chooses */
static void any_maturity_month_year(MaturityMonthYear *record) {
  for (size_t i = 0; i < 2; i++) { record->year[i] = arbitrary(); }
  record->month = arbitrary();
  record->day = arbitrary();
  record->week = arbitrary();
}

/* Maturity Month Year to the wire: 5 bytes from at, returning where the next byte goes */
static size_t encode_maturity_month_year(const MaturityMonthYear *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->year[i]; }
  wire[at++] = record->month;
  wire[at++] = record->day;
  wire[at++] = record->week;

  return at;
}

/* Maturity Month Year off the wire: 5 bytes from at, returning where the next byte lies */
static size_t decode_maturity_month_year(MaturityMonthYear *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->year[i] = wire[at++]; }
  record->month = wire[at++];
  record->day = wire[at++];
  record->week = wire[at++];

  return at;
}

/* what was read of Maturity Month Year is what was written, byte for byte */
static void equal_maturity_month_year(const MaturityMonthYear *read, const MaturityMonthYear *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->year[i] == written->year[i]); }
  assert(read->month == written->month);
  assert(read->day == written->day);
  assert(read->week == written->week);
}

/* Maturity Month Year: written and read back, then read and written back */
static void check_maturity_month_year(void) {
  MaturityMonthYear sent;
  MaturityMonthYear got;
  uint8_t wire[5];
  uint8_t again[5];

  any_maturity_month_year(&sent);
  assert(encode_maturity_month_year(&sent, wire, 0) == 5);
  assert(decode_maturity_month_year(&got, wire, 0) == 5);
  equal_maturity_month_year(&got, &sent);

  for (size_t i = 0; i < 5; i++) { wire[i] = arbitrary(); }
  assert(decode_maturity_month_year(&got, wire, 0) == 5);
  assert(encode_maturity_month_year(&got, again, 0) == 5);
  for (size_t i = 0; i < 5; i++) { assert(again[i] == wire[i]); }
}

/* ---- Leg Option Delta: 5 bytes ----------------------------------------------- */

/* Up to 26 legs (i.e., repeating groups) supported for UDS for options. Up to 40 legs (i.e., repeating groups) supported for UDS for futures. Will be set to 0 for REPO */
typedef struct {
  uint8_t mantissa_32[4];  /* bytes 0 to 3 */
  uint8_t exponent;        /* byte 4 */
} LegOptionDelta;

/* any Leg Option Delta at all: every byte one the checker chooses */
static void any_leg_option_delta(LegOptionDelta *record) {
  for (size_t i = 0; i < 4; i++) { record->mantissa_32[i] = arbitrary(); }
  record->exponent = arbitrary();
}

/* Leg Option Delta to the wire: 5 bytes from at, returning where the next byte goes */
static size_t encode_leg_option_delta(const LegOptionDelta *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->mantissa_32[i]; }
  wire[at++] = record->exponent;

  return at;
}

/* Leg Option Delta off the wire: 5 bytes from at, returning where the next byte lies */
static size_t decode_leg_option_delta(LegOptionDelta *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->mantissa_32[i] = wire[at++]; }
  record->exponent = wire[at++];

  return at;
}

/* what was read of Leg Option Delta is what was written, byte for byte */
static void equal_leg_option_delta(const LegOptionDelta *read, const LegOptionDelta *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->mantissa_32[i] == written->mantissa_32[i]); }
  assert(read->exponent == written->exponent);
}

/* Leg Option Delta: written and read back, then read and written back */
static void check_leg_option_delta(void) {
  LegOptionDelta sent;
  LegOptionDelta got;
  uint8_t wire[5];
  uint8_t again[5];

  any_leg_option_delta(&sent);
  assert(encode_leg_option_delta(&sent, wire, 0) == 5);
  assert(decode_leg_option_delta(&got, wire, 0) == 5);
  equal_leg_option_delta(&got, &sent);

  for (size_t i = 0; i < 5; i++) { wire[i] = arbitrary(); }
  assert(decode_leg_option_delta(&got, wire, 0) == 5);
  assert(encode_leg_option_delta(&got, again, 0) == 5);
  for (size_t i = 0; i < 5; i++) { assert(again[i] == wire[i]); }
}

/* ---- What esbmc checks ------------------------------------------------------- */

/* every record of the protocol, each on its own buffers */
static void checks(void) {
  check_simple_open_framing_header();
  check_message_header();
  check_negotiation_reject();
  check_establishment_ack();
  check_establishment_reject();
  check_sequence();
  check_terminate();
  check_retransmission();
  check_retransmit_reject();
  check_not_applied();
  check_group_size();
  check_business_reject();
  check_volatility();
  check_option_delta();
  check_time_to_expiration();
  check_risk_free_rate();
  check_order_cancel_reject();
  check_order_cancel_replace_reject();
  check_request_for_quote_ack();
  check_maturity_month_year();
  check_leg_option_delta();
}

int main(void) {
#ifdef CONCRETE
  for (pattern = 0; pattern < 4; pattern++) { checks(); }
#else
  checks();
#endif

  return 0;
}
