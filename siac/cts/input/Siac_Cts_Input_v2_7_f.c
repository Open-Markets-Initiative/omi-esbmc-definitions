// siac/cts/input/Siac_Cts_Input_v2_7_f.c
/*
 * The Securities Industry Automation Corporation
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
 *   - a Reassemble rule
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

/* ---- Block Header: 10 bytes -------------------------------------------------- */

/* Cta participant input block header */
typedef struct {
  uint8_t version;                   /* byte 0 */
  uint8_t block_size[2];             /* bytes 1 to 2 */
  uint8_t block_sequence_number[4];  /* bytes 3 to 6 */
  uint8_t messages_in_block;         /* byte 7 */
  uint8_t block_checksum[2];         /* bytes 8 to 9 */
} BlockHeader;

/* any Block Header at all: every byte one the checker chooses */
static void any_block_header(BlockHeader *record) {
  record->version = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->block_size[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->block_sequence_number[i] = arbitrary(); }
  record->messages_in_block = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->block_checksum[i] = arbitrary(); }
}

/* Block Header to the wire: 10 bytes from at, returning where the next byte goes */
static size_t encode_block_header(const BlockHeader *record, uint8_t *wire, size_t at) {
  wire[at++] = record->version;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->block_size[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->block_sequence_number[i]; }
  wire[at++] = record->messages_in_block;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->block_checksum[i]; }

  return at;
}

/* Block Header off the wire: 10 bytes from at, returning where the next byte lies */
static size_t decode_block_header(BlockHeader *record, const uint8_t *wire, size_t at) {
  record->version = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->block_size[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->block_sequence_number[i] = wire[at++]; }
  record->messages_in_block = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->block_checksum[i] = wire[at++]; }

  return at;
}

/* what was read of Block Header is what was written, byte for byte */
static void equal_block_header(const BlockHeader *read, const BlockHeader *written) {
  assert(read->version == written->version);
  for (size_t i = 0; i < 2; i++) { assert(read->block_size[i] == written->block_size[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->block_sequence_number[i] == written->block_sequence_number[i]); }
  assert(read->messages_in_block == written->messages_in_block);
  for (size_t i = 0; i < 2; i++) { assert(read->block_checksum[i] == written->block_checksum[i]); }
}

/* Block Header: written and read back, then read and written back */
static void check_block_header(void) {
  BlockHeader sent;
  BlockHeader got;
  uint8_t wire[10];
  uint8_t again[10];

  any_block_header(&sent);
  assert(encode_block_header(&sent, wire, 0) == 10);
  assert(decode_block_header(&got, wire, 0) == 10);
  equal_block_header(&got, &sent);

  for (size_t i = 0; i < 10; i++) { wire[i] = arbitrary(); }
  assert(decode_block_header(&got, wire, 0) == 10);
  assert(encode_block_header(&got, again, 0) == 10);
  for (size_t i = 0; i < 10; i++) { assert(again[i] == wire[i]); }
}

/* ---- Timestamp 1: 8 bytes ---------------------------------------------------- */

/* Participant-provided timestamp */
typedef struct {
  uint8_t seconds[4];      /* bytes 0 to 3 */
  uint8_t nanoseconds[4];  /* bytes 4 to 7 */
} Timestamp1;

/* any Timestamp 1 at all: every byte one the checker chooses */
static void any_timestamp1(Timestamp1 *record) {
  for (size_t i = 0; i < 4; i++) { record->seconds[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = arbitrary(); }
}

/* Timestamp 1 to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_timestamp1(const Timestamp1 *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->seconds[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->nanoseconds[i]; }

  return at;
}

/* Timestamp 1 off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_timestamp1(Timestamp1 *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->seconds[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = wire[at++]; }

  return at;
}

/* what was read of Timestamp 1 is what was written, byte for byte */
static void equal_timestamp1(const Timestamp1 *read, const Timestamp1 *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->seconds[i] == written->seconds[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->nanoseconds[i] == written->nanoseconds[i]); }
}

/* Timestamp 1: written and read back, then read and written back */
static void check_timestamp1(void) {
  Timestamp1 sent;
  Timestamp1 got;
  uint8_t wire[8];
  uint8_t again[8];

  any_timestamp1(&sent);
  assert(encode_timestamp1(&sent, wire, 0) == 8);
  assert(decode_timestamp1(&got, wire, 0) == 8);
  equal_timestamp1(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_timestamp1(&got, wire, 0) == 8);
  assert(encode_timestamp1(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Message Header: 26 bytes ------------------------------------------------ */

/* Cta participant input message header (26 bytes) */
typedef struct {
  uint8_t message_length[2];                /* bytes 0 to 1 */
  uint8_t message_category;                 /* byte 2 */
  uint8_t message_type;                     /* byte 3 */
  uint8_t participant_i_d;                  /* byte 4 */
  Timestamp1 timestamp_1;                   /* bytes 5 to 12 */
  uint8_t message_i_d;                      /* byte 13 */
  uint8_t reserved[4];                      /* bytes 14 to 17 */
  uint8_t participant_reference_number[8];  /* bytes 18 to 25 */
} MessageHeader;

/* any Message Header at all: every byte one the checker chooses */
static void any_message_header(MessageHeader *record) {
  for (size_t i = 0; i < 2; i++) { record->message_length[i] = arbitrary(); }
  record->message_category = arbitrary();
  record->message_type = arbitrary();
  record->participant_i_d = arbitrary();
  any_timestamp1(&record->timestamp_1);
  record->message_i_d = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->reserved[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->participant_reference_number[i] = arbitrary(); }
}

/* Message Header to the wire: 26 bytes from at, returning where the next byte goes */
static size_t encode_message_header(const MessageHeader *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->message_length[i]; }
  wire[at++] = record->message_category;
  wire[at++] = record->message_type;
  wire[at++] = record->participant_i_d;
  at = encode_timestamp1(&record->timestamp_1, wire, at);
  wire[at++] = record->message_i_d;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->reserved[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->participant_reference_number[i]; }

  return at;
}

/* Message Header off the wire: 26 bytes from at, returning where the next byte lies */
static size_t decode_message_header(MessageHeader *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->message_length[i] = wire[at++]; }
  record->message_category = wire[at++];
  record->message_type = wire[at++];
  record->participant_i_d = wire[at++];
  at = decode_timestamp1(&record->timestamp_1, wire, at);
  record->message_i_d = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->reserved[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->participant_reference_number[i] = wire[at++]; }

  return at;
}

/* what was read of Message Header is what was written, byte for byte */
static void equal_message_header(const MessageHeader *read, const MessageHeader *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->message_length[i] == written->message_length[i]); }
  assert(read->message_category == written->message_category);
  assert(read->message_type == written->message_type);
  assert(read->participant_i_d == written->participant_i_d);
  equal_timestamp1(&read->timestamp_1, &written->timestamp_1);
  assert(read->message_i_d == written->message_i_d);
  for (size_t i = 0; i < 4; i++) { assert(read->reserved[i] == written->reserved[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->participant_reference_number[i] == written->participant_reference_number[i]); }
}

/* Message Header: written and read back, then read and written back */
static void check_message_header(void) {
  MessageHeader sent;
  MessageHeader got;
  uint8_t wire[26];
  uint8_t again[26];

  any_message_header(&sent);
  assert(encode_message_header(&sent, wire, 0) == 26);
  assert(decode_message_header(&got, wire, 0) == 26);
  equal_message_header(&got, &sent);

  for (size_t i = 0; i < 26; i++) { wire[i] = arbitrary(); }
  assert(decode_message_header(&got, wire, 0) == 26);
  assert(encode_message_header(&got, again, 0) == 26);
  for (size_t i = 0; i < 26; i++) { assert(again[i] == wire[i]); }
}

/* ---- Rejection Message: 14 bytes --------------------------------------------- */

/* Used for all errors to notify a Participant that CTS has found an error in the Block Header, Message Header or Message body of a Participant Input message. */
typedef struct {
  uint8_t error_code;                       /* byte 0 */
  uint8_t block_sequence_number[4];         /* bytes 1 to 4 */
  uint8_t participant_reference_number[8];  /* bytes 5 to 12 */
  uint8_t message_i_d;                      /* byte 13 */
} RejectionMessage;

/* any Rejection Message at all: every byte one the checker chooses */
static void any_rejection_message(RejectionMessage *record) {
  record->error_code = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->block_sequence_number[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->participant_reference_number[i] = arbitrary(); }
  record->message_i_d = arbitrary();
}

/* Rejection Message to the wire: 14 bytes from at, returning where the next byte goes */
static size_t encode_rejection_message(const RejectionMessage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->error_code;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->block_sequence_number[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->participant_reference_number[i]; }
  wire[at++] = record->message_i_d;

  return at;
}

/* Rejection Message off the wire: 14 bytes from at, returning where the next byte lies */
static size_t decode_rejection_message(RejectionMessage *record, const uint8_t *wire, size_t at) {
  record->error_code = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->block_sequence_number[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->participant_reference_number[i] = wire[at++]; }
  record->message_i_d = wire[at++];

  return at;
}

/* what was read of Rejection Message is what was written, byte for byte */
static void equal_rejection_message(const RejectionMessage *read, const RejectionMessage *written) {
  assert(read->error_code == written->error_code);
  for (size_t i = 0; i < 4; i++) { assert(read->block_sequence_number[i] == written->block_sequence_number[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->participant_reference_number[i] == written->participant_reference_number[i]); }
  assert(read->message_i_d == written->message_i_d);
}

/* Rejection Message: written and read back, then read and written back */
static void check_rejection_message(void) {
  RejectionMessage sent;
  RejectionMessage got;
  uint8_t wire[14];
  uint8_t again[14];

  any_rejection_message(&sent);
  assert(encode_rejection_message(&sent, wire, 0) == 14);
  assert(decode_rejection_message(&got, wire, 0) == 14);
  equal_rejection_message(&got, &sent);

  for (size_t i = 0; i < 14; i++) { wire[i] = arbitrary(); }
  assert(decode_rejection_message(&got, wire, 0) == 14);
  assert(encode_rejection_message(&got, again, 0) == 14);
  for (size_t i = 0; i < 14; i++) { assert(again[i] == wire[i]); }
}

/* ---- Warning Message: 12 bytes ----------------------------------------------- */

/* Sent from CTS to a Participant in response to a Block Sequence Number Gap. The block will still be processed by CTS. */
typedef struct {
  uint8_t previous_block_sequence_number[4];         /* bytes 0 to 3 */
  uint8_t previous_participant_reference_number[8];  /* bytes 4 to 11 */
} WarningMessage;

/* any Warning Message at all: every byte one the checker chooses */
static void any_warning_message(WarningMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->previous_block_sequence_number[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->previous_participant_reference_number[i] = arbitrary(); }
}

/* Warning Message to the wire: 12 bytes from at, returning where the next byte goes */
static size_t encode_warning_message(const WarningMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->previous_block_sequence_number[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->previous_participant_reference_number[i]; }

  return at;
}

/* Warning Message off the wire: 12 bytes from at, returning where the next byte lies */
static size_t decode_warning_message(WarningMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->previous_block_sequence_number[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->previous_participant_reference_number[i] = wire[at++]; }

  return at;
}

/* what was read of Warning Message is what was written, byte for byte */
static void equal_warning_message(const WarningMessage *read, const WarningMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->previous_block_sequence_number[i] == written->previous_block_sequence_number[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->previous_participant_reference_number[i] == written->previous_participant_reference_number[i]); }
}

/* Warning Message: written and read back, then read and written back */
static void check_warning_message(void) {
  WarningMessage sent;
  WarningMessage got;
  uint8_t wire[12];
  uint8_t again[12];

  any_warning_message(&sent);
  assert(encode_warning_message(&sent, wire, 0) == 12);
  assert(decode_warning_message(&got, wire, 0) == 12);
  equal_warning_message(&got, &sent);

  for (size_t i = 0; i < 12; i++) { wire[i] = arbitrary(); }
  assert(decode_warning_message(&got, wire, 0) == 12);
  assert(encode_warning_message(&got, again, 0) == 12);
  for (size_t i = 0; i < 12; i++) { assert(again[i] == wire[i]); }
}

/* ---- Sequence Information And Message Count Response Message: 20 bytes ------- */

/* Generated by CTS to a Participant in response to a Sequence Information and Message Count Inquiry message. Transmitted in a separate block. */
typedef struct {
  uint8_t current_block_sequence_number[4];      /* bytes 0 to 3 */
  uint8_t last_participant_reference_number[8];  /* bytes 4 to 11 */
  uint8_t message_count[8];                      /* bytes 12 to 19 */
} SequenceInformationAndMessageCountResponseMessage;

/* any Sequence Information And Message Count Response Message at all: every byte one the checker chooses */
static void any_sequence_information_and_message_count_response_message(SequenceInformationAndMessageCountResponseMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->current_block_sequence_number[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->last_participant_reference_number[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->message_count[i] = arbitrary(); }
}

/* Sequence Information And Message Count Response Message to the wire: 20 bytes from at, returning where the next byte goes */
static size_t encode_sequence_information_and_message_count_response_message(const SequenceInformationAndMessageCountResponseMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->current_block_sequence_number[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->last_participant_reference_number[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->message_count[i]; }

  return at;
}

/* Sequence Information And Message Count Response Message off the wire: 20 bytes from at, returning where the next byte lies */
static size_t decode_sequence_information_and_message_count_response_message(SequenceInformationAndMessageCountResponseMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->current_block_sequence_number[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->last_participant_reference_number[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->message_count[i] = wire[at++]; }

  return at;
}

/* what was read of Sequence Information And Message Count Response Message is what was written, byte for byte */
static void equal_sequence_information_and_message_count_response_message(const SequenceInformationAndMessageCountResponseMessage *read, const SequenceInformationAndMessageCountResponseMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->current_block_sequence_number[i] == written->current_block_sequence_number[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->last_participant_reference_number[i] == written->last_participant_reference_number[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->message_count[i] == written->message_count[i]); }
}

/* Sequence Information And Message Count Response Message: written and read back, then read and written back */
static void check_sequence_information_and_message_count_response_message(void) {
  SequenceInformationAndMessageCountResponseMessage sent;
  SequenceInformationAndMessageCountResponseMessage got;
  uint8_t wire[20];
  uint8_t again[20];

  any_sequence_information_and_message_count_response_message(&sent);
  assert(encode_sequence_information_and_message_count_response_message(&sent, wire, 0) == 20);
  assert(decode_sequence_information_and_message_count_response_message(&got, wire, 0) == 20);
  equal_sequence_information_and_message_count_response_message(&got, &sent);

  for (size_t i = 0; i < 20; i++) { wire[i] = arbitrary(); }
  assert(decode_sequence_information_and_message_count_response_message(&got, wire, 0) == 20);
  assert(encode_sequence_information_and_message_count_response_message(&got, again, 0) == 20);
  for (size_t i = 0; i < 20; i++) { assert(again[i] == wire[i]); }
}

/* ---- Test Message: 256 bytes ------------------------------------------------- */

/* Generated by CTS or a Participant to exercise the line and verify transmission integrity. Transmitted as the only message in a block. */
typedef struct {
  uint8_t data[256];  /* bytes 0 to 255 */
} TestMessage;

/* any Test Message at all: every byte one the checker chooses */
static void any_test_message(TestMessage *record) {
  for (size_t i = 0; i < 256; i++) { record->data[i] = arbitrary(); }
}

/* Test Message to the wire: 256 bytes from at, returning where the next byte goes */
static size_t encode_test_message(const TestMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 256; i++) { wire[at++] = record->data[i]; }

  return at;
}

/* Test Message off the wire: 256 bytes from at, returning where the next byte lies */
static size_t decode_test_message(TestMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 256; i++) { record->data[i] = wire[at++]; }

  return at;
}

/* what was read of Test Message is what was written, byte for byte */
static void equal_test_message(const TestMessage *read, const TestMessage *written) {
  for (size_t i = 0; i < 256; i++) { assert(read->data[i] == written->data[i]); }
}

/* Test Message: written and read back, then read and written back */
static void check_test_message(void) {
  TestMessage sent;
  TestMessage got;
  uint8_t wire[256];
  uint8_t again[256];

  any_test_message(&sent);
  assert(encode_test_message(&sent, wire, 0) == 256);
  assert(decode_test_message(&got, wire, 0) == 256);
  equal_test_message(&got, &sent);

  for (size_t i = 0; i < 256; i++) { wire[i] = arbitrary(); }
  assert(decode_test_message(&got, wire, 0) == 256);
  assert(encode_test_message(&got, again, 0) == 256);
  for (size_t i = 0; i < 256; i++) { assert(again[i] == wire[i]); }
}

/* ---- Index Message: 19 bytes ------------------------------------------------- */

/* Contains the index and the index value. */
typedef struct {
  uint8_t index_symbol[11];  /* bytes 0 to 10 */
  uint8_t index_value[8];    /* bytes 11 to 18 */
} IndexMessage;

/* any Index Message at all: every byte one the checker chooses */
static void any_index_message(IndexMessage *record) {
  for (size_t i = 0; i < 11; i++) { record->index_symbol[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->index_value[i] = arbitrary(); }
}

/* Index Message to the wire: 19 bytes from at, returning where the next byte goes */
static size_t encode_index_message(const IndexMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->index_symbol[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->index_value[i]; }

  return at;
}

/* Index Message off the wire: 19 bytes from at, returning where the next byte lies */
static size_t decode_index_message(IndexMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 11; i++) { record->index_symbol[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->index_value[i] = wire[at++]; }

  return at;
}

/* what was read of Index Message is what was written, byte for byte */
static void equal_index_message(const IndexMessage *read, const IndexMessage *written) {
  for (size_t i = 0; i < 11; i++) { assert(read->index_symbol[i] == written->index_symbol[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->index_value[i] == written->index_value[i]); }
}

/* Index Message: written and read back, then read and written back */
static void check_index_message(void) {
  IndexMessage sent;
  IndexMessage got;
  uint8_t wire[19];
  uint8_t again[19];

  any_index_message(&sent);
  assert(encode_index_message(&sent, wire, 0) == 19);
  assert(decode_index_message(&got, wire, 0) == 19);
  equal_index_message(&got, &sent);

  for (size_t i = 0; i < 19; i++) { wire[i] = arbitrary(); }
  assert(decode_index_message(&got, wire, 0) == 19);
  assert(encode_index_message(&got, again, 0) == 19);
  for (size_t i = 0; i < 19; i++) { assert(again[i] == wire[i]); }
}

/* ---- Bid And Offer Index Message: 27 bytes ----------------------------------- */

/* Contains the Bid and Offer index values. */
typedef struct {
  uint8_t index_symbol[11];      /* bytes 0 to 10 */
  uint8_t bid_index_value[8];    /* bytes 11 to 18 */
  uint8_t offer_index_value[8];  /* bytes 19 to 26 */
} BidAndOfferIndexMessage;

/* any Bid And Offer Index Message at all: every byte one the checker chooses */
static void any_bid_and_offer_index_message(BidAndOfferIndexMessage *record) {
  for (size_t i = 0; i < 11; i++) { record->index_symbol[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->bid_index_value[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->offer_index_value[i] = arbitrary(); }
}

/* Bid And Offer Index Message to the wire: 27 bytes from at, returning where the next byte goes */
static size_t encode_bid_and_offer_index_message(const BidAndOfferIndexMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->index_symbol[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->bid_index_value[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->offer_index_value[i]; }

  return at;
}

/* Bid And Offer Index Message off the wire: 27 bytes from at, returning where the next byte lies */
static size_t decode_bid_and_offer_index_message(BidAndOfferIndexMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 11; i++) { record->index_symbol[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->bid_index_value[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->offer_index_value[i] = wire[at++]; }

  return at;
}

/* what was read of Bid And Offer Index Message is what was written, byte for byte */
static void equal_bid_and_offer_index_message(const BidAndOfferIndexMessage *read, const BidAndOfferIndexMessage *written) {
  for (size_t i = 0; i < 11; i++) { assert(read->index_symbol[i] == written->index_symbol[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->bid_index_value[i] == written->bid_index_value[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->offer_index_value[i] == written->offer_index_value[i]); }
}

/* Bid And Offer Index Message: written and read back, then read and written back */
static void check_bid_and_offer_index_message(void) {
  BidAndOfferIndexMessage sent;
  BidAndOfferIndexMessage got;
  uint8_t wire[27];
  uint8_t again[27];

  any_bid_and_offer_index_message(&sent);
  assert(encode_bid_and_offer_index_message(&sent, wire, 0) == 27);
  assert(decode_bid_and_offer_index_message(&got, wire, 0) == 27);
  equal_bid_and_offer_index_message(&got, &sent);

  for (size_t i = 0; i < 27; i++) { wire[i] = arbitrary(); }
  assert(decode_bid_and_offer_index_message(&got, wire, 0) == 27);
  assert(encode_bid_and_offer_index_message(&got, again, 0) == 27);
  for (size_t i = 0; i < 27; i++) { assert(again[i] == wire[i]); }
}

/* ---- Approximate Trades And Total Dollar Value Message: 12 bytes ------------- */

/* Allows a Participant to report the total trades and total dollar value of trades at their respective market centers. */
typedef struct {
  uint8_t total_trades[4];  /* bytes 0 to 3 */
  uint8_t dollar_value[8];  /* bytes 4 to 11 */
} ApproximateTradesAndTotalDollarValueMessage;

/* any Approximate Trades And Total Dollar Value Message at all: every byte one the checker chooses */
static void any_approximate_trades_and_total_dollar_value_message(ApproximateTradesAndTotalDollarValueMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->total_trades[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->dollar_value[i] = arbitrary(); }
}

/* Approximate Trades And Total Dollar Value Message to the wire: 12 bytes from at, returning where the next byte goes */
static size_t encode_approximate_trades_and_total_dollar_value_message(const ApproximateTradesAndTotalDollarValueMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->total_trades[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->dollar_value[i]; }

  return at;
}

/* Approximate Trades And Total Dollar Value Message off the wire: 12 bytes from at, returning where the next byte lies */
static size_t decode_approximate_trades_and_total_dollar_value_message(ApproximateTradesAndTotalDollarValueMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->total_trades[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->dollar_value[i] = wire[at++]; }

  return at;
}

/* what was read of Approximate Trades And Total Dollar Value Message is what was written, byte for byte */
static void equal_approximate_trades_and_total_dollar_value_message(const ApproximateTradesAndTotalDollarValueMessage *read, const ApproximateTradesAndTotalDollarValueMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->total_trades[i] == written->total_trades[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->dollar_value[i] == written->dollar_value[i]); }
}

/* Approximate Trades And Total Dollar Value Message: written and read back, then read and written back */
static void check_approximate_trades_and_total_dollar_value_message(void) {
  ApproximateTradesAndTotalDollarValueMessage sent;
  ApproximateTradesAndTotalDollarValueMessage got;
  uint8_t wire[12];
  uint8_t again[12];

  any_approximate_trades_and_total_dollar_value_message(&sent);
  assert(encode_approximate_trades_and_total_dollar_value_message(&sent, wire, 0) == 12);
  assert(decode_approximate_trades_and_total_dollar_value_message(&got, wire, 0) == 12);
  equal_approximate_trades_and_total_dollar_value_message(&got, &sent);

  for (size_t i = 0; i < 12; i++) { wire[i] = arbitrary(); }
  assert(decode_approximate_trades_and_total_dollar_value_message(&got, wire, 0) == 12);
  assert(encode_approximate_trades_and_total_dollar_value_message(&got, again, 0) == 12);
  for (size_t i = 0; i < 12; i++) { assert(again[i] == wire[i]); }
}

/* ---- Crossing Session Message: 24 bytes -------------------------------------- */

/* Used to report the total volume and dollar value of trades transacted after the close of a Participant's regular session. */
typedef struct {
  uint8_t crossing_session_i_total_trades_volume[8];   /* bytes 0 to 7 */
  uint8_t crossing_session_ii_dollar_value[8];         /* bytes 8 to 15 */
  uint8_t crossing_session_ii_total_trades_volume[8];  /* bytes 16 to 23 */
} CrossingSessionMessage;

/* any Crossing Session Message at all: every byte one the checker chooses */
static void any_crossing_session_message(CrossingSessionMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->crossing_session_i_total_trades_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->crossing_session_ii_dollar_value[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->crossing_session_ii_total_trades_volume[i] = arbitrary(); }
}

/* Crossing Session Message to the wire: 24 bytes from at, returning where the next byte goes */
static size_t encode_crossing_session_message(const CrossingSessionMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->crossing_session_i_total_trades_volume[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->crossing_session_ii_dollar_value[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->crossing_session_ii_total_trades_volume[i]; }

  return at;
}

/* Crossing Session Message off the wire: 24 bytes from at, returning where the next byte lies */
static size_t decode_crossing_session_message(CrossingSessionMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->crossing_session_i_total_trades_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->crossing_session_ii_dollar_value[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->crossing_session_ii_total_trades_volume[i] = wire[at++]; }

  return at;
}

/* what was read of Crossing Session Message is what was written, byte for byte */
static void equal_crossing_session_message(const CrossingSessionMessage *read, const CrossingSessionMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->crossing_session_i_total_trades_volume[i] == written->crossing_session_i_total_trades_volume[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->crossing_session_ii_dollar_value[i] == written->crossing_session_ii_dollar_value[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->crossing_session_ii_total_trades_volume[i] == written->crossing_session_ii_total_trades_volume[i]); }
}

/* Crossing Session Message: written and read back, then read and written back */
static void check_crossing_session_message(void) {
  CrossingSessionMessage sent;
  CrossingSessionMessage got;
  uint8_t wire[24];
  uint8_t again[24];

  any_crossing_session_message(&sent);
  assert(encode_crossing_session_message(&sent, wire, 0) == 24);
  assert(decode_crossing_session_message(&got, wire, 0) == 24);
  equal_crossing_session_message(&got, &sent);

  for (size_t i = 0; i < 24; i++) { wire[i] = arbitrary(); }
  assert(decode_crossing_session_message(&got, wire, 0) == 24);
  assert(encode_crossing_session_message(&got, again, 0) == 24);
  for (size_t i = 0; i < 24; i++) { assert(again[i] == wire[i]); }
}

/* ---- Corrected Prior Day Trade Date And Time: 8 bytes ------------------------ */

/* Corrected Prior Day Trade Date and Time */
typedef struct {
  uint8_t seconds[4];      /* bytes 0 to 3 */
  uint8_t nanoseconds[4];  /* bytes 4 to 7 */
} CorrectedPriorDayTradeDateAndTime;

/* any Corrected Prior Day Trade Date And Time at all: every byte one the checker chooses */
static void any_corrected_prior_day_trade_date_and_time(CorrectedPriorDayTradeDateAndTime *record) {
  for (size_t i = 0; i < 4; i++) { record->seconds[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = arbitrary(); }
}

/* Corrected Prior Day Trade Date And Time to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_corrected_prior_day_trade_date_and_time(const CorrectedPriorDayTradeDateAndTime *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->seconds[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->nanoseconds[i]; }

  return at;
}

/* Corrected Prior Day Trade Date And Time off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_corrected_prior_day_trade_date_and_time(CorrectedPriorDayTradeDateAndTime *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->seconds[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = wire[at++]; }

  return at;
}

/* what was read of Corrected Prior Day Trade Date And Time is what was written, byte for byte */
static void equal_corrected_prior_day_trade_date_and_time(const CorrectedPriorDayTradeDateAndTime *read, const CorrectedPriorDayTradeDateAndTime *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->seconds[i] == written->seconds[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->nanoseconds[i] == written->nanoseconds[i]); }
}

/* Corrected Prior Day Trade Date And Time: written and read back, then read and written back */
static void check_corrected_prior_day_trade_date_and_time(void) {
  CorrectedPriorDayTradeDateAndTime sent;
  CorrectedPriorDayTradeDateAndTime got;
  uint8_t wire[8];
  uint8_t again[8];

  any_corrected_prior_day_trade_date_and_time(&sent);
  assert(encode_corrected_prior_day_trade_date_and_time(&sent, wire, 0) == 8);
  assert(decode_corrected_prior_day_trade_date_and_time(&got, wire, 0) == 8);
  equal_corrected_prior_day_trade_date_and_time(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_corrected_prior_day_trade_date_and_time(&got, wire, 0) == 8);
  assert(encode_corrected_prior_day_trade_date_and_time(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Original Prior Day Trade Date And Time: 8 bytes ------------------------- */

/* Original Prior Day Trade Date and Time */
typedef struct {
  uint8_t seconds[4];      /* bytes 0 to 3 */
  uint8_t nanoseconds[4];  /* bytes 4 to 7 */
} OriginalPriorDayTradeDateAndTime;

/* any Original Prior Day Trade Date And Time at all: every byte one the checker chooses */
static void any_original_prior_day_trade_date_and_time(OriginalPriorDayTradeDateAndTime *record) {
  for (size_t i = 0; i < 4; i++) { record->seconds[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = arbitrary(); }
}

/* Original Prior Day Trade Date And Time to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_original_prior_day_trade_date_and_time(const OriginalPriorDayTradeDateAndTime *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->seconds[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->nanoseconds[i]; }

  return at;
}

/* Original Prior Day Trade Date And Time off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_original_prior_day_trade_date_and_time(OriginalPriorDayTradeDateAndTime *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->seconds[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = wire[at++]; }

  return at;
}

/* what was read of Original Prior Day Trade Date And Time is what was written, byte for byte */
static void equal_original_prior_day_trade_date_and_time(const OriginalPriorDayTradeDateAndTime *read, const OriginalPriorDayTradeDateAndTime *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->seconds[i] == written->seconds[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->nanoseconds[i] == written->nanoseconds[i]); }
}

/* Original Prior Day Trade Date And Time: written and read back, then read and written back */
static void check_original_prior_day_trade_date_and_time(void) {
  OriginalPriorDayTradeDateAndTime sent;
  OriginalPriorDayTradeDateAndTime got;
  uint8_t wire[8];
  uint8_t again[8];

  any_original_prior_day_trade_date_and_time(&sent);
  assert(encode_original_prior_day_trade_date_and_time(&sent, wire, 0) == 8);
  assert(decode_original_prior_day_trade_date_and_time(&got, wire, 0) == 8);
  equal_original_prior_day_trade_date_and_time(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_original_prior_day_trade_date_and_time(&got, wire, 0) == 8);
  assert(encode_original_prior_day_trade_date_and_time(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Prior Day Trade Correction Message: 69 bytes ---------------------------- */

/* Used to correct a transaction originally reported earlier than the current day. */
typedef struct {
  uint8_t security_symbol[11];                                                /* bytes 0 to 10 */
  uint8_t instrument_type;                                                    /* byte 11 */
  uint8_t corrected_sale_condition[4];                                        /* bytes 12 to 15 */
  uint8_t corrected_trade_price[8];                                           /* bytes 16 to 23 */
  uint8_t corrected_trade_volume[4];                                          /* bytes 24 to 27 */
  uint8_t corrected_sellers_sale_days;                                        /* byte 28 */
  uint8_t corrected_stop_stock_indicator;                                     /* byte 29 */
  uint8_t corrected_trade_through_exempt_indicator;                           /* byte 30 */
  uint8_t corrected_short_sale_restriction_indicator;                         /* byte 31 */
  CorrectedPriorDayTradeDateAndTime corrected_prior_day_trade_date_and_time;  /* bytes 32 to 39 */
  uint8_t trade_reporting_facility_id;                                        /* byte 40 */
  uint8_t original_sale_condition[4];                                         /* bytes 41 to 44 */
  uint8_t original_trade_price[8];                                            /* bytes 45 to 52 */
  uint8_t original_trade_volume[4];                                           /* bytes 53 to 56 */
  uint8_t original_sellers_sale_days;                                         /* byte 57 */
  uint8_t original_stop_stock_indicator;                                      /* byte 58 */
  uint8_t original_trade_through_exempt_indicator;                            /* byte 59 */
  uint8_t original_short_sale_restriction_indicator;                          /* byte 60 */
  OriginalPriorDayTradeDateAndTime original_prior_day_trade_date_and_time;    /* bytes 61 to 68 */
} PriorDayTradeCorrectionMessage;

/* any Prior Day Trade Correction Message at all: every byte one the checker chooses */
static void any_prior_day_trade_correction_message(PriorDayTradeCorrectionMessage *record) {
  for (size_t i = 0; i < 11; i++) { record->security_symbol[i] = arbitrary(); }
  record->instrument_type = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->corrected_sale_condition[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->corrected_trade_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->corrected_trade_volume[i] = arbitrary(); }
  record->corrected_sellers_sale_days = arbitrary();
  record->corrected_stop_stock_indicator = arbitrary();
  record->corrected_trade_through_exempt_indicator = arbitrary();
  record->corrected_short_sale_restriction_indicator = arbitrary();
  any_corrected_prior_day_trade_date_and_time(&record->corrected_prior_day_trade_date_and_time);
  record->trade_reporting_facility_id = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->original_sale_condition[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->original_trade_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->original_trade_volume[i] = arbitrary(); }
  record->original_sellers_sale_days = arbitrary();
  record->original_stop_stock_indicator = arbitrary();
  record->original_trade_through_exempt_indicator = arbitrary();
  record->original_short_sale_restriction_indicator = arbitrary();
  any_original_prior_day_trade_date_and_time(&record->original_prior_day_trade_date_and_time);
}

/* Prior Day Trade Correction Message to the wire: 69 bytes from at, returning where the next byte goes */
static size_t encode_prior_day_trade_correction_message(const PriorDayTradeCorrectionMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->security_symbol[i]; }
  wire[at++] = record->instrument_type;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->corrected_sale_condition[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->corrected_trade_price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->corrected_trade_volume[i]; }
  wire[at++] = record->corrected_sellers_sale_days;
  wire[at++] = record->corrected_stop_stock_indicator;
  wire[at++] = record->corrected_trade_through_exempt_indicator;
  wire[at++] = record->corrected_short_sale_restriction_indicator;
  at = encode_corrected_prior_day_trade_date_and_time(&record->corrected_prior_day_trade_date_and_time, wire, at);
  wire[at++] = record->trade_reporting_facility_id;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->original_sale_condition[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->original_trade_price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->original_trade_volume[i]; }
  wire[at++] = record->original_sellers_sale_days;
  wire[at++] = record->original_stop_stock_indicator;
  wire[at++] = record->original_trade_through_exempt_indicator;
  wire[at++] = record->original_short_sale_restriction_indicator;
  at = encode_original_prior_day_trade_date_and_time(&record->original_prior_day_trade_date_and_time, wire, at);

  return at;
}

/* Prior Day Trade Correction Message off the wire: 69 bytes from at, returning where the next byte lies */
static size_t decode_prior_day_trade_correction_message(PriorDayTradeCorrectionMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 11; i++) { record->security_symbol[i] = wire[at++]; }
  record->instrument_type = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->corrected_sale_condition[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->corrected_trade_price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->corrected_trade_volume[i] = wire[at++]; }
  record->corrected_sellers_sale_days = wire[at++];
  record->corrected_stop_stock_indicator = wire[at++];
  record->corrected_trade_through_exempt_indicator = wire[at++];
  record->corrected_short_sale_restriction_indicator = wire[at++];
  at = decode_corrected_prior_day_trade_date_and_time(&record->corrected_prior_day_trade_date_and_time, wire, at);
  record->trade_reporting_facility_id = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->original_sale_condition[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->original_trade_price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->original_trade_volume[i] = wire[at++]; }
  record->original_sellers_sale_days = wire[at++];
  record->original_stop_stock_indicator = wire[at++];
  record->original_trade_through_exempt_indicator = wire[at++];
  record->original_short_sale_restriction_indicator = wire[at++];
  at = decode_original_prior_day_trade_date_and_time(&record->original_prior_day_trade_date_and_time, wire, at);

  return at;
}

/* what was read of Prior Day Trade Correction Message is what was written, byte for byte */
static void equal_prior_day_trade_correction_message(const PriorDayTradeCorrectionMessage *read, const PriorDayTradeCorrectionMessage *written) {
  for (size_t i = 0; i < 11; i++) { assert(read->security_symbol[i] == written->security_symbol[i]); }
  assert(read->instrument_type == written->instrument_type);
  for (size_t i = 0; i < 4; i++) { assert(read->corrected_sale_condition[i] == written->corrected_sale_condition[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->corrected_trade_price[i] == written->corrected_trade_price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->corrected_trade_volume[i] == written->corrected_trade_volume[i]); }
  assert(read->corrected_sellers_sale_days == written->corrected_sellers_sale_days);
  assert(read->corrected_stop_stock_indicator == written->corrected_stop_stock_indicator);
  assert(read->corrected_trade_through_exempt_indicator == written->corrected_trade_through_exempt_indicator);
  assert(read->corrected_short_sale_restriction_indicator == written->corrected_short_sale_restriction_indicator);
  equal_corrected_prior_day_trade_date_and_time(&read->corrected_prior_day_trade_date_and_time, &written->corrected_prior_day_trade_date_and_time);
  assert(read->trade_reporting_facility_id == written->trade_reporting_facility_id);
  for (size_t i = 0; i < 4; i++) { assert(read->original_sale_condition[i] == written->original_sale_condition[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->original_trade_price[i] == written->original_trade_price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->original_trade_volume[i] == written->original_trade_volume[i]); }
  assert(read->original_sellers_sale_days == written->original_sellers_sale_days);
  assert(read->original_stop_stock_indicator == written->original_stop_stock_indicator);
  assert(read->original_trade_through_exempt_indicator == written->original_trade_through_exempt_indicator);
  assert(read->original_short_sale_restriction_indicator == written->original_short_sale_restriction_indicator);
  equal_original_prior_day_trade_date_and_time(&read->original_prior_day_trade_date_and_time, &written->original_prior_day_trade_date_and_time);
}

/* Prior Day Trade Correction Message: written and read back, then read and written back */
static void check_prior_day_trade_correction_message(void) {
  PriorDayTradeCorrectionMessage sent;
  PriorDayTradeCorrectionMessage got;
  uint8_t wire[69];
  uint8_t again[69];

  any_prior_day_trade_correction_message(&sent);
  assert(encode_prior_day_trade_correction_message(&sent, wire, 0) == 69);
  assert(decode_prior_day_trade_correction_message(&got, wire, 0) == 69);
  equal_prior_day_trade_correction_message(&got, &sent);

  for (size_t i = 0; i < 69; i++) { wire[i] = arbitrary(); }
  assert(decode_prior_day_trade_correction_message(&got, wire, 0) == 69);
  assert(encode_prior_day_trade_correction_message(&got, again, 0) == 69);
  for (size_t i = 0; i < 69; i++) { assert(again[i] == wire[i]); }
}

/* ---- Fractional Prior Day Trade Correction Message: 77 bytes ----------------- */

/* Used to correct a prior day transaction when either the original or corrected volume is a fractional value. */
typedef struct {
  uint8_t security_symbol[11];                                                /* bytes 0 to 10 */
  uint8_t instrument_type;                                                    /* byte 11 */
  uint8_t corrected_sale_condition[4];                                        /* bytes 12 to 15 */
  uint8_t corrected_trade_price[8];                                           /* bytes 16 to 23 */
  uint8_t corrected_fractional_trade_volume[8];                               /* bytes 24 to 31 */
  uint8_t corrected_sellers_sale_days;                                        /* byte 32 */
  uint8_t corrected_stop_stock_indicator;                                     /* byte 33 */
  uint8_t corrected_trade_through_exempt_indicator;                           /* byte 34 */
  uint8_t corrected_short_sale_restriction_indicator;                         /* byte 35 */
  CorrectedPriorDayTradeDateAndTime corrected_prior_day_trade_date_and_time;  /* bytes 36 to 43 */
  uint8_t trade_reporting_facility_id;                                        /* byte 44 */
  uint8_t original_sale_condition[4];                                         /* bytes 45 to 48 */
  uint8_t original_trade_price[8];                                            /* bytes 49 to 56 */
  uint8_t original_fractional_trade_volume[8];                                /* bytes 57 to 64 */
  uint8_t original_sellers_sale_days;                                         /* byte 65 */
  uint8_t original_stop_stock_indicator;                                      /* byte 66 */
  uint8_t original_trade_through_exempt_indicator;                            /* byte 67 */
  uint8_t original_short_sale_restriction_indicator;                          /* byte 68 */
  OriginalPriorDayTradeDateAndTime original_prior_day_trade_date_and_time;    /* bytes 69 to 76 */
} FractionalPriorDayTradeCorrectionMessage;

/* any Fractional Prior Day Trade Correction Message at all: every byte one the checker chooses */
static void any_fractional_prior_day_trade_correction_message(FractionalPriorDayTradeCorrectionMessage *record) {
  for (size_t i = 0; i < 11; i++) { record->security_symbol[i] = arbitrary(); }
  record->instrument_type = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->corrected_sale_condition[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->corrected_trade_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->corrected_fractional_trade_volume[i] = arbitrary(); }
  record->corrected_sellers_sale_days = arbitrary();
  record->corrected_stop_stock_indicator = arbitrary();
  record->corrected_trade_through_exempt_indicator = arbitrary();
  record->corrected_short_sale_restriction_indicator = arbitrary();
  any_corrected_prior_day_trade_date_and_time(&record->corrected_prior_day_trade_date_and_time);
  record->trade_reporting_facility_id = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->original_sale_condition[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->original_trade_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->original_fractional_trade_volume[i] = arbitrary(); }
  record->original_sellers_sale_days = arbitrary();
  record->original_stop_stock_indicator = arbitrary();
  record->original_trade_through_exempt_indicator = arbitrary();
  record->original_short_sale_restriction_indicator = arbitrary();
  any_original_prior_day_trade_date_and_time(&record->original_prior_day_trade_date_and_time);
}

/* Fractional Prior Day Trade Correction Message to the wire: 77 bytes from at, returning where the next byte goes */
static size_t encode_fractional_prior_day_trade_correction_message(const FractionalPriorDayTradeCorrectionMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->security_symbol[i]; }
  wire[at++] = record->instrument_type;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->corrected_sale_condition[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->corrected_trade_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->corrected_fractional_trade_volume[i]; }
  wire[at++] = record->corrected_sellers_sale_days;
  wire[at++] = record->corrected_stop_stock_indicator;
  wire[at++] = record->corrected_trade_through_exempt_indicator;
  wire[at++] = record->corrected_short_sale_restriction_indicator;
  at = encode_corrected_prior_day_trade_date_and_time(&record->corrected_prior_day_trade_date_and_time, wire, at);
  wire[at++] = record->trade_reporting_facility_id;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->original_sale_condition[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->original_trade_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->original_fractional_trade_volume[i]; }
  wire[at++] = record->original_sellers_sale_days;
  wire[at++] = record->original_stop_stock_indicator;
  wire[at++] = record->original_trade_through_exempt_indicator;
  wire[at++] = record->original_short_sale_restriction_indicator;
  at = encode_original_prior_day_trade_date_and_time(&record->original_prior_day_trade_date_and_time, wire, at);

  return at;
}

/* Fractional Prior Day Trade Correction Message off the wire: 77 bytes from at, returning where the next byte lies */
static size_t decode_fractional_prior_day_trade_correction_message(FractionalPriorDayTradeCorrectionMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 11; i++) { record->security_symbol[i] = wire[at++]; }
  record->instrument_type = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->corrected_sale_condition[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->corrected_trade_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->corrected_fractional_trade_volume[i] = wire[at++]; }
  record->corrected_sellers_sale_days = wire[at++];
  record->corrected_stop_stock_indicator = wire[at++];
  record->corrected_trade_through_exempt_indicator = wire[at++];
  record->corrected_short_sale_restriction_indicator = wire[at++];
  at = decode_corrected_prior_day_trade_date_and_time(&record->corrected_prior_day_trade_date_and_time, wire, at);
  record->trade_reporting_facility_id = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->original_sale_condition[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->original_trade_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->original_fractional_trade_volume[i] = wire[at++]; }
  record->original_sellers_sale_days = wire[at++];
  record->original_stop_stock_indicator = wire[at++];
  record->original_trade_through_exempt_indicator = wire[at++];
  record->original_short_sale_restriction_indicator = wire[at++];
  at = decode_original_prior_day_trade_date_and_time(&record->original_prior_day_trade_date_and_time, wire, at);

  return at;
}

/* what was read of Fractional Prior Day Trade Correction Message is what was written, byte for byte */
static void equal_fractional_prior_day_trade_correction_message(const FractionalPriorDayTradeCorrectionMessage *read, const FractionalPriorDayTradeCorrectionMessage *written) {
  for (size_t i = 0; i < 11; i++) { assert(read->security_symbol[i] == written->security_symbol[i]); }
  assert(read->instrument_type == written->instrument_type);
  for (size_t i = 0; i < 4; i++) { assert(read->corrected_sale_condition[i] == written->corrected_sale_condition[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->corrected_trade_price[i] == written->corrected_trade_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->corrected_fractional_trade_volume[i] == written->corrected_fractional_trade_volume[i]); }
  assert(read->corrected_sellers_sale_days == written->corrected_sellers_sale_days);
  assert(read->corrected_stop_stock_indicator == written->corrected_stop_stock_indicator);
  assert(read->corrected_trade_through_exempt_indicator == written->corrected_trade_through_exempt_indicator);
  assert(read->corrected_short_sale_restriction_indicator == written->corrected_short_sale_restriction_indicator);
  equal_corrected_prior_day_trade_date_and_time(&read->corrected_prior_day_trade_date_and_time, &written->corrected_prior_day_trade_date_and_time);
  assert(read->trade_reporting_facility_id == written->trade_reporting_facility_id);
  for (size_t i = 0; i < 4; i++) { assert(read->original_sale_condition[i] == written->original_sale_condition[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->original_trade_price[i] == written->original_trade_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->original_fractional_trade_volume[i] == written->original_fractional_trade_volume[i]); }
  assert(read->original_sellers_sale_days == written->original_sellers_sale_days);
  assert(read->original_stop_stock_indicator == written->original_stop_stock_indicator);
  assert(read->original_trade_through_exempt_indicator == written->original_trade_through_exempt_indicator);
  assert(read->original_short_sale_restriction_indicator == written->original_short_sale_restriction_indicator);
  equal_original_prior_day_trade_date_and_time(&read->original_prior_day_trade_date_and_time, &written->original_prior_day_trade_date_and_time);
}

/* Fractional Prior Day Trade Correction Message: written and read back, then read and written back */
static void check_fractional_prior_day_trade_correction_message(void) {
  FractionalPriorDayTradeCorrectionMessage sent;
  FractionalPriorDayTradeCorrectionMessage got;
  uint8_t wire[77];
  uint8_t again[77];

  any_fractional_prior_day_trade_correction_message(&sent);
  assert(encode_fractional_prior_day_trade_correction_message(&sent, wire, 0) == 77);
  assert(decode_fractional_prior_day_trade_correction_message(&got, wire, 0) == 77);
  equal_fractional_prior_day_trade_correction_message(&got, &sent);

  for (size_t i = 0; i < 77; i++) { wire[i] = arbitrary(); }
  assert(decode_fractional_prior_day_trade_correction_message(&got, wire, 0) == 77);
  assert(encode_fractional_prior_day_trade_correction_message(&got, again, 0) == 77);
  for (size_t i = 0; i < 77; i++) { assert(again[i] == wire[i]); }
}

/* ---- Prior Day Trade Date And Time: 8 bytes ---------------------------------- */

/* Prior Day Trade Date and Time */
typedef struct {
  uint8_t seconds[4];      /* bytes 0 to 3 */
  uint8_t nanoseconds[4];  /* bytes 4 to 7 */
} PriorDayTradeDateAndTime;

/* any Prior Day Trade Date And Time at all: every byte one the checker chooses */
static void any_prior_day_trade_date_and_time(PriorDayTradeDateAndTime *record) {
  for (size_t i = 0; i < 4; i++) { record->seconds[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = arbitrary(); }
}

/* Prior Day Trade Date And Time to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_prior_day_trade_date_and_time(const PriorDayTradeDateAndTime *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->seconds[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->nanoseconds[i]; }

  return at;
}

/* Prior Day Trade Date And Time off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_prior_day_trade_date_and_time(PriorDayTradeDateAndTime *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->seconds[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = wire[at++]; }

  return at;
}

/* what was read of Prior Day Trade Date And Time is what was written, byte for byte */
static void equal_prior_day_trade_date_and_time(const PriorDayTradeDateAndTime *read, const PriorDayTradeDateAndTime *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->seconds[i] == written->seconds[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->nanoseconds[i] == written->nanoseconds[i]); }
}

/* Prior Day Trade Date And Time: written and read back, then read and written back */
static void check_prior_day_trade_date_and_time(void) {
  PriorDayTradeDateAndTime sent;
  PriorDayTradeDateAndTime got;
  uint8_t wire[8];
  uint8_t again[8];

  any_prior_day_trade_date_and_time(&sent);
  assert(encode_prior_day_trade_date_and_time(&sent, wire, 0) == 8);
  assert(decode_prior_day_trade_date_and_time(&got, wire, 0) == 8);
  equal_prior_day_trade_date_and_time(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_prior_day_trade_date_and_time(&got, wire, 0) == 8);
  assert(encode_prior_day_trade_date_and_time(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Prior Day Trade Message: 41 bytes --------------------------------------- */

/* Reports a CTA eligible Equity, Local Issue or Bond transaction which occurred earlier than the current trading day and was not reported. */
typedef struct {
  uint8_t security_symbol[11];                             /* bytes 0 to 10 */
  uint8_t instrument_type;                                 /* byte 11 */
  uint8_t sale_condition[4];                               /* bytes 12 to 15 */
  uint8_t trade_price[8];                                  /* bytes 16 to 23 */
  uint8_t trade_volume[4];                                 /* bytes 24 to 27 */
  uint8_t sellers_sale_days;                               /* byte 28 */
  uint8_t stop_stock_indicator;                            /* byte 29 */
  uint8_t trade_through_exempt_indicator;                  /* byte 30 */
  uint8_t short_sale_restriction_indicator;                /* byte 31 */
  uint8_t trade_reporting_facility_id;                     /* byte 32 */
  PriorDayTradeDateAndTime prior_day_trade_date_and_time;  /* bytes 33 to 40 */
} PriorDayTradeMessage;

/* any Prior Day Trade Message at all: every byte one the checker chooses */
static void any_prior_day_trade_message(PriorDayTradeMessage *record) {
  for (size_t i = 0; i < 11; i++) { record->security_symbol[i] = arbitrary(); }
  record->instrument_type = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->sale_condition[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->trade_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->trade_volume[i] = arbitrary(); }
  record->sellers_sale_days = arbitrary();
  record->stop_stock_indicator = arbitrary();
  record->trade_through_exempt_indicator = arbitrary();
  record->short_sale_restriction_indicator = arbitrary();
  record->trade_reporting_facility_id = arbitrary();
  any_prior_day_trade_date_and_time(&record->prior_day_trade_date_and_time);
}

/* Prior Day Trade Message to the wire: 41 bytes from at, returning where the next byte goes */
static size_t encode_prior_day_trade_message(const PriorDayTradeMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->security_symbol[i]; }
  wire[at++] = record->instrument_type;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->sale_condition[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->trade_price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->trade_volume[i]; }
  wire[at++] = record->sellers_sale_days;
  wire[at++] = record->stop_stock_indicator;
  wire[at++] = record->trade_through_exempt_indicator;
  wire[at++] = record->short_sale_restriction_indicator;
  wire[at++] = record->trade_reporting_facility_id;
  at = encode_prior_day_trade_date_and_time(&record->prior_day_trade_date_and_time, wire, at);

  return at;
}

/* Prior Day Trade Message off the wire: 41 bytes from at, returning where the next byte lies */
static size_t decode_prior_day_trade_message(PriorDayTradeMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 11; i++) { record->security_symbol[i] = wire[at++]; }
  record->instrument_type = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->sale_condition[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->trade_price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->trade_volume[i] = wire[at++]; }
  record->sellers_sale_days = wire[at++];
  record->stop_stock_indicator = wire[at++];
  record->trade_through_exempt_indicator = wire[at++];
  record->short_sale_restriction_indicator = wire[at++];
  record->trade_reporting_facility_id = wire[at++];
  at = decode_prior_day_trade_date_and_time(&record->prior_day_trade_date_and_time, wire, at);

  return at;
}

/* what was read of Prior Day Trade Message is what was written, byte for byte */
static void equal_prior_day_trade_message(const PriorDayTradeMessage *read, const PriorDayTradeMessage *written) {
  for (size_t i = 0; i < 11; i++) { assert(read->security_symbol[i] == written->security_symbol[i]); }
  assert(read->instrument_type == written->instrument_type);
  for (size_t i = 0; i < 4; i++) { assert(read->sale_condition[i] == written->sale_condition[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->trade_price[i] == written->trade_price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->trade_volume[i] == written->trade_volume[i]); }
  assert(read->sellers_sale_days == written->sellers_sale_days);
  assert(read->stop_stock_indicator == written->stop_stock_indicator);
  assert(read->trade_through_exempt_indicator == written->trade_through_exempt_indicator);
  assert(read->short_sale_restriction_indicator == written->short_sale_restriction_indicator);
  assert(read->trade_reporting_facility_id == written->trade_reporting_facility_id);
  equal_prior_day_trade_date_and_time(&read->prior_day_trade_date_and_time, &written->prior_day_trade_date_and_time);
}

/* Prior Day Trade Message: written and read back, then read and written back */
static void check_prior_day_trade_message(void) {
  PriorDayTradeMessage sent;
  PriorDayTradeMessage got;
  uint8_t wire[41];
  uint8_t again[41];

  any_prior_day_trade_message(&sent);
  assert(encode_prior_day_trade_message(&sent, wire, 0) == 41);
  assert(decode_prior_day_trade_message(&got, wire, 0) == 41);
  equal_prior_day_trade_message(&got, &sent);

  for (size_t i = 0; i < 41; i++) { wire[i] = arbitrary(); }
  assert(decode_prior_day_trade_message(&got, wire, 0) == 41);
  assert(encode_prior_day_trade_message(&got, again, 0) == 41);
  for (size_t i = 0; i < 41; i++) { assert(again[i] == wire[i]); }
}

/* ---- Fractional Prior Day Trade Message: 45 bytes ---------------------------- */

/* Reports a trade with fractional volume which occurred earlier than the current trading day and was not reported. */
typedef struct {
  uint8_t security_symbol[11];                             /* bytes 0 to 10 */
  uint8_t instrument_type;                                 /* byte 11 */
  uint8_t sale_condition[4];                               /* bytes 12 to 15 */
  uint8_t trade_price[8];                                  /* bytes 16 to 23 */
  uint8_t fractional_trade_volume[8];                      /* bytes 24 to 31 */
  uint8_t sellers_sale_days;                               /* byte 32 */
  uint8_t stop_stock_indicator;                            /* byte 33 */
  uint8_t trade_through_exempt_indicator;                  /* byte 34 */
  uint8_t short_sale_restriction_indicator;                /* byte 35 */
  uint8_t trade_reporting_facility_id;                     /* byte 36 */
  PriorDayTradeDateAndTime prior_day_trade_date_and_time;  /* bytes 37 to 44 */
} FractionalPriorDayTradeMessage;

/* any Fractional Prior Day Trade Message at all: every byte one the checker chooses */
static void any_fractional_prior_day_trade_message(FractionalPriorDayTradeMessage *record) {
  for (size_t i = 0; i < 11; i++) { record->security_symbol[i] = arbitrary(); }
  record->instrument_type = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->sale_condition[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->trade_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->fractional_trade_volume[i] = arbitrary(); }
  record->sellers_sale_days = arbitrary();
  record->stop_stock_indicator = arbitrary();
  record->trade_through_exempt_indicator = arbitrary();
  record->short_sale_restriction_indicator = arbitrary();
  record->trade_reporting_facility_id = arbitrary();
  any_prior_day_trade_date_and_time(&record->prior_day_trade_date_and_time);
}

/* Fractional Prior Day Trade Message to the wire: 45 bytes from at, returning where the next byte goes */
static size_t encode_fractional_prior_day_trade_message(const FractionalPriorDayTradeMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->security_symbol[i]; }
  wire[at++] = record->instrument_type;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->sale_condition[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->trade_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->fractional_trade_volume[i]; }
  wire[at++] = record->sellers_sale_days;
  wire[at++] = record->stop_stock_indicator;
  wire[at++] = record->trade_through_exempt_indicator;
  wire[at++] = record->short_sale_restriction_indicator;
  wire[at++] = record->trade_reporting_facility_id;
  at = encode_prior_day_trade_date_and_time(&record->prior_day_trade_date_and_time, wire, at);

  return at;
}

/* Fractional Prior Day Trade Message off the wire: 45 bytes from at, returning where the next byte lies */
static size_t decode_fractional_prior_day_trade_message(FractionalPriorDayTradeMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 11; i++) { record->security_symbol[i] = wire[at++]; }
  record->instrument_type = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->sale_condition[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->trade_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->fractional_trade_volume[i] = wire[at++]; }
  record->sellers_sale_days = wire[at++];
  record->stop_stock_indicator = wire[at++];
  record->trade_through_exempt_indicator = wire[at++];
  record->short_sale_restriction_indicator = wire[at++];
  record->trade_reporting_facility_id = wire[at++];
  at = decode_prior_day_trade_date_and_time(&record->prior_day_trade_date_and_time, wire, at);

  return at;
}

/* what was read of Fractional Prior Day Trade Message is what was written, byte for byte */
static void equal_fractional_prior_day_trade_message(const FractionalPriorDayTradeMessage *read, const FractionalPriorDayTradeMessage *written) {
  for (size_t i = 0; i < 11; i++) { assert(read->security_symbol[i] == written->security_symbol[i]); }
  assert(read->instrument_type == written->instrument_type);
  for (size_t i = 0; i < 4; i++) { assert(read->sale_condition[i] == written->sale_condition[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->trade_price[i] == written->trade_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->fractional_trade_volume[i] == written->fractional_trade_volume[i]); }
  assert(read->sellers_sale_days == written->sellers_sale_days);
  assert(read->stop_stock_indicator == written->stop_stock_indicator);
  assert(read->trade_through_exempt_indicator == written->trade_through_exempt_indicator);
  assert(read->short_sale_restriction_indicator == written->short_sale_restriction_indicator);
  assert(read->trade_reporting_facility_id == written->trade_reporting_facility_id);
  equal_prior_day_trade_date_and_time(&read->prior_day_trade_date_and_time, &written->prior_day_trade_date_and_time);
}

/* Fractional Prior Day Trade Message: written and read back, then read and written back */
static void check_fractional_prior_day_trade_message(void) {
  FractionalPriorDayTradeMessage sent;
  FractionalPriorDayTradeMessage got;
  uint8_t wire[45];
  uint8_t again[45];

  any_fractional_prior_day_trade_message(&sent);
  assert(encode_fractional_prior_day_trade_message(&sent, wire, 0) == 45);
  assert(decode_fractional_prior_day_trade_message(&got, wire, 0) == 45);
  equal_fractional_prior_day_trade_message(&got, &sent);

  for (size_t i = 0; i < 45; i++) { wire[i] = arbitrary(); }
  assert(decode_fractional_prior_day_trade_message(&got, wire, 0) == 45);
  assert(encode_fractional_prior_day_trade_message(&got, again, 0) == 45);
  for (size_t i = 0; i < 45; i++) { assert(again[i] == wire[i]); }
}

/* ---- Prior Day Trade Cancel Error Message: 42 bytes -------------------------- */

/* Used to cancel or error a trade or correction originally reported earlier than the current day. */
typedef struct {
  uint8_t security_symbol[11];                             /* bytes 0 to 10 */
  uint8_t instrument_type;                                 /* byte 11 */
  uint8_t sale_condition[4];                               /* bytes 12 to 15 */
  uint8_t trade_price[8];                                  /* bytes 16 to 23 */
  uint8_t trade_volume[4];                                 /* bytes 24 to 27 */
  uint8_t sellers_sale_days;                               /* byte 28 */
  uint8_t stop_stock_indicator;                            /* byte 29 */
  uint8_t trade_through_exempt_indicator;                  /* byte 30 */
  uint8_t short_sale_restriction_indicator;                /* byte 31 */
  uint8_t trade_reporting_facility_id;                     /* byte 32 */
  PriorDayTradeDateAndTime prior_day_trade_date_and_time;  /* bytes 33 to 40 */
  uint8_t cancel_error_action;                             /* byte 41 */
} PriorDayTradeCancelErrorMessage;

/* any Prior Day Trade Cancel Error Message at all: every byte one the checker chooses */
static void any_prior_day_trade_cancel_error_message(PriorDayTradeCancelErrorMessage *record) {
  for (size_t i = 0; i < 11; i++) { record->security_symbol[i] = arbitrary(); }
  record->instrument_type = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->sale_condition[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->trade_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->trade_volume[i] = arbitrary(); }
  record->sellers_sale_days = arbitrary();
  record->stop_stock_indicator = arbitrary();
  record->trade_through_exempt_indicator = arbitrary();
  record->short_sale_restriction_indicator = arbitrary();
  record->trade_reporting_facility_id = arbitrary();
  any_prior_day_trade_date_and_time(&record->prior_day_trade_date_and_time);
  record->cancel_error_action = arbitrary();
}

/* Prior Day Trade Cancel Error Message to the wire: 42 bytes from at, returning where the next byte goes */
static size_t encode_prior_day_trade_cancel_error_message(const PriorDayTradeCancelErrorMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->security_symbol[i]; }
  wire[at++] = record->instrument_type;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->sale_condition[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->trade_price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->trade_volume[i]; }
  wire[at++] = record->sellers_sale_days;
  wire[at++] = record->stop_stock_indicator;
  wire[at++] = record->trade_through_exempt_indicator;
  wire[at++] = record->short_sale_restriction_indicator;
  wire[at++] = record->trade_reporting_facility_id;
  at = encode_prior_day_trade_date_and_time(&record->prior_day_trade_date_and_time, wire, at);
  wire[at++] = record->cancel_error_action;

  return at;
}

/* Prior Day Trade Cancel Error Message off the wire: 42 bytes from at, returning where the next byte lies */
static size_t decode_prior_day_trade_cancel_error_message(PriorDayTradeCancelErrorMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 11; i++) { record->security_symbol[i] = wire[at++]; }
  record->instrument_type = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->sale_condition[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->trade_price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->trade_volume[i] = wire[at++]; }
  record->sellers_sale_days = wire[at++];
  record->stop_stock_indicator = wire[at++];
  record->trade_through_exempt_indicator = wire[at++];
  record->short_sale_restriction_indicator = wire[at++];
  record->trade_reporting_facility_id = wire[at++];
  at = decode_prior_day_trade_date_and_time(&record->prior_day_trade_date_and_time, wire, at);
  record->cancel_error_action = wire[at++];

  return at;
}

/* what was read of Prior Day Trade Cancel Error Message is what was written, byte for byte */
static void equal_prior_day_trade_cancel_error_message(const PriorDayTradeCancelErrorMessage *read, const PriorDayTradeCancelErrorMessage *written) {
  for (size_t i = 0; i < 11; i++) { assert(read->security_symbol[i] == written->security_symbol[i]); }
  assert(read->instrument_type == written->instrument_type);
  for (size_t i = 0; i < 4; i++) { assert(read->sale_condition[i] == written->sale_condition[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->trade_price[i] == written->trade_price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->trade_volume[i] == written->trade_volume[i]); }
  assert(read->sellers_sale_days == written->sellers_sale_days);
  assert(read->stop_stock_indicator == written->stop_stock_indicator);
  assert(read->trade_through_exempt_indicator == written->trade_through_exempt_indicator);
  assert(read->short_sale_restriction_indicator == written->short_sale_restriction_indicator);
  assert(read->trade_reporting_facility_id == written->trade_reporting_facility_id);
  equal_prior_day_trade_date_and_time(&read->prior_day_trade_date_and_time, &written->prior_day_trade_date_and_time);
  assert(read->cancel_error_action == written->cancel_error_action);
}

/* Prior Day Trade Cancel Error Message: written and read back, then read and written back */
static void check_prior_day_trade_cancel_error_message(void) {
  PriorDayTradeCancelErrorMessage sent;
  PriorDayTradeCancelErrorMessage got;
  uint8_t wire[42];
  uint8_t again[42];

  any_prior_day_trade_cancel_error_message(&sent);
  assert(encode_prior_day_trade_cancel_error_message(&sent, wire, 0) == 42);
  assert(decode_prior_day_trade_cancel_error_message(&got, wire, 0) == 42);
  equal_prior_day_trade_cancel_error_message(&got, &sent);

  for (size_t i = 0; i < 42; i++) { wire[i] = arbitrary(); }
  assert(decode_prior_day_trade_cancel_error_message(&got, wire, 0) == 42);
  assert(encode_prior_day_trade_cancel_error_message(&got, again, 0) == 42);
  for (size_t i = 0; i < 42; i++) { assert(again[i] == wire[i]); }
}

/* ---- Fractional Prior Day Trade Cancel Error Message: 46 bytes --------------- */

/* Reports the cancellation or error of a fractional trade or correction originally reported earlier than the current day. */
typedef struct {
  uint8_t security_symbol[11];                             /* bytes 0 to 10 */
  uint8_t instrument_type;                                 /* byte 11 */
  uint8_t sale_condition[4];                               /* bytes 12 to 15 */
  uint8_t trade_price[8];                                  /* bytes 16 to 23 */
  uint8_t fractional_trade_volume[8];                      /* bytes 24 to 31 */
  uint8_t sellers_sale_days;                               /* byte 32 */
  uint8_t stop_stock_indicator;                            /* byte 33 */
  uint8_t trade_through_exempt_indicator;                  /* byte 34 */
  uint8_t short_sale_restriction_indicator;                /* byte 35 */
  uint8_t trade_reporting_facility_id;                     /* byte 36 */
  PriorDayTradeDateAndTime prior_day_trade_date_and_time;  /* bytes 37 to 44 */
  uint8_t cancel_error_action;                             /* byte 45 */
} FractionalPriorDayTradeCancelErrorMessage;

/* any Fractional Prior Day Trade Cancel Error Message at all: every byte one the checker chooses */
static void any_fractional_prior_day_trade_cancel_error_message(FractionalPriorDayTradeCancelErrorMessage *record) {
  for (size_t i = 0; i < 11; i++) { record->security_symbol[i] = arbitrary(); }
  record->instrument_type = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->sale_condition[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->trade_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->fractional_trade_volume[i] = arbitrary(); }
  record->sellers_sale_days = arbitrary();
  record->stop_stock_indicator = arbitrary();
  record->trade_through_exempt_indicator = arbitrary();
  record->short_sale_restriction_indicator = arbitrary();
  record->trade_reporting_facility_id = arbitrary();
  any_prior_day_trade_date_and_time(&record->prior_day_trade_date_and_time);
  record->cancel_error_action = arbitrary();
}

/* Fractional Prior Day Trade Cancel Error Message to the wire: 46 bytes from at, returning where the next byte goes */
static size_t encode_fractional_prior_day_trade_cancel_error_message(const FractionalPriorDayTradeCancelErrorMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->security_symbol[i]; }
  wire[at++] = record->instrument_type;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->sale_condition[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->trade_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->fractional_trade_volume[i]; }
  wire[at++] = record->sellers_sale_days;
  wire[at++] = record->stop_stock_indicator;
  wire[at++] = record->trade_through_exempt_indicator;
  wire[at++] = record->short_sale_restriction_indicator;
  wire[at++] = record->trade_reporting_facility_id;
  at = encode_prior_day_trade_date_and_time(&record->prior_day_trade_date_and_time, wire, at);
  wire[at++] = record->cancel_error_action;

  return at;
}

/* Fractional Prior Day Trade Cancel Error Message off the wire: 46 bytes from at, returning where the next byte lies */
static size_t decode_fractional_prior_day_trade_cancel_error_message(FractionalPriorDayTradeCancelErrorMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 11; i++) { record->security_symbol[i] = wire[at++]; }
  record->instrument_type = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->sale_condition[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->trade_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->fractional_trade_volume[i] = wire[at++]; }
  record->sellers_sale_days = wire[at++];
  record->stop_stock_indicator = wire[at++];
  record->trade_through_exempt_indicator = wire[at++];
  record->short_sale_restriction_indicator = wire[at++];
  record->trade_reporting_facility_id = wire[at++];
  at = decode_prior_day_trade_date_and_time(&record->prior_day_trade_date_and_time, wire, at);
  record->cancel_error_action = wire[at++];

  return at;
}

/* what was read of Fractional Prior Day Trade Cancel Error Message is what was written, byte for byte */
static void equal_fractional_prior_day_trade_cancel_error_message(const FractionalPriorDayTradeCancelErrorMessage *read, const FractionalPriorDayTradeCancelErrorMessage *written) {
  for (size_t i = 0; i < 11; i++) { assert(read->security_symbol[i] == written->security_symbol[i]); }
  assert(read->instrument_type == written->instrument_type);
  for (size_t i = 0; i < 4; i++) { assert(read->sale_condition[i] == written->sale_condition[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->trade_price[i] == written->trade_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->fractional_trade_volume[i] == written->fractional_trade_volume[i]); }
  assert(read->sellers_sale_days == written->sellers_sale_days);
  assert(read->stop_stock_indicator == written->stop_stock_indicator);
  assert(read->trade_through_exempt_indicator == written->trade_through_exempt_indicator);
  assert(read->short_sale_restriction_indicator == written->short_sale_restriction_indicator);
  assert(read->trade_reporting_facility_id == written->trade_reporting_facility_id);
  equal_prior_day_trade_date_and_time(&read->prior_day_trade_date_and_time, &written->prior_day_trade_date_and_time);
  assert(read->cancel_error_action == written->cancel_error_action);
}

/* Fractional Prior Day Trade Cancel Error Message: written and read back, then read and written back */
static void check_fractional_prior_day_trade_cancel_error_message(void) {
  FractionalPriorDayTradeCancelErrorMessage sent;
  FractionalPriorDayTradeCancelErrorMessage got;
  uint8_t wire[46];
  uint8_t again[46];

  any_fractional_prior_day_trade_cancel_error_message(&sent);
  assert(encode_fractional_prior_day_trade_cancel_error_message(&sent, wire, 0) == 46);
  assert(decode_fractional_prior_day_trade_cancel_error_message(&got, wire, 0) == 46);
  equal_fractional_prior_day_trade_cancel_error_message(&got, &sent);

  for (size_t i = 0; i < 46; i++) { wire[i] = arbitrary(); }
  assert(decode_fractional_prior_day_trade_cancel_error_message(&got, wire, 0) == 46);
  assert(encode_fractional_prior_day_trade_cancel_error_message(&got, again, 0) == 46);
  for (size_t i = 0; i < 46; i++) { assert(again[i] == wire[i]); }
}

/* ---- Auction Status Message: 99 bytes ---------------------------------------- */

/* Transmitted when a Participant in a CTA eligible security requires Auction Information. Initial Auction Collar is published after the LULD Trading Pause. */
typedef struct {
  uint8_t security_symbol[11];                      /* bytes 0 to 10 */
  uint8_t instrument_type;                          /* byte 11 */
  uint8_t auction_collar_reference_price[8];        /* bytes 12 to 19 */
  uint8_t auction_collar_upper_threshold_price[8];  /* bytes 20 to 27 */
  uint8_t auction_collar_lower_threshold_price[8];  /* bytes 28 to 35 */
  uint8_t number_of_extensions;                     /* byte 36 */
  uint8_t reserved_62[62];                          /* bytes 37 to 98 */
} AuctionStatusMessage;

/* any Auction Status Message at all: every byte one the checker chooses */
static void any_auction_status_message(AuctionStatusMessage *record) {
  for (size_t i = 0; i < 11; i++) { record->security_symbol[i] = arbitrary(); }
  record->instrument_type = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->auction_collar_reference_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->auction_collar_upper_threshold_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->auction_collar_lower_threshold_price[i] = arbitrary(); }
  record->number_of_extensions = arbitrary();
  for (size_t i = 0; i < 62; i++) { record->reserved_62[i] = arbitrary(); }
}

/* Auction Status Message to the wire: 99 bytes from at, returning where the next byte goes */
static size_t encode_auction_status_message(const AuctionStatusMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->security_symbol[i]; }
  wire[at++] = record->instrument_type;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->auction_collar_reference_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->auction_collar_upper_threshold_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->auction_collar_lower_threshold_price[i]; }
  wire[at++] = record->number_of_extensions;
  for (size_t i = 0; i < 62; i++) { wire[at++] = record->reserved_62[i]; }

  return at;
}

/* Auction Status Message off the wire: 99 bytes from at, returning where the next byte lies */
static size_t decode_auction_status_message(AuctionStatusMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 11; i++) { record->security_symbol[i] = wire[at++]; }
  record->instrument_type = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->auction_collar_reference_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->auction_collar_upper_threshold_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->auction_collar_lower_threshold_price[i] = wire[at++]; }
  record->number_of_extensions = wire[at++];
  for (size_t i = 0; i < 62; i++) { record->reserved_62[i] = wire[at++]; }

  return at;
}

/* what was read of Auction Status Message is what was written, byte for byte */
static void equal_auction_status_message(const AuctionStatusMessage *read, const AuctionStatusMessage *written) {
  for (size_t i = 0; i < 11; i++) { assert(read->security_symbol[i] == written->security_symbol[i]); }
  assert(read->instrument_type == written->instrument_type);
  for (size_t i = 0; i < 8; i++) { assert(read->auction_collar_reference_price[i] == written->auction_collar_reference_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->auction_collar_upper_threshold_price[i] == written->auction_collar_upper_threshold_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->auction_collar_lower_threshold_price[i] == written->auction_collar_lower_threshold_price[i]); }
  assert(read->number_of_extensions == written->number_of_extensions);
  for (size_t i = 0; i < 62; i++) { assert(read->reserved_62[i] == written->reserved_62[i]); }
}

/* Auction Status Message: written and read back, then read and written back */
static void check_auction_status_message(void) {
  AuctionStatusMessage sent;
  AuctionStatusMessage got;
  uint8_t wire[99];
  uint8_t again[99];

  any_auction_status_message(&sent);
  assert(encode_auction_status_message(&sent, wire, 0) == 99);
  assert(decode_auction_status_message(&got, wire, 0) == 99);
  equal_auction_status_message(&got, &sent);

  for (size_t i = 0; i < 99; i++) { wire[i] = arbitrary(); }
  assert(decode_auction_status_message(&got, wire, 0) == 99);
  assert(encode_auction_status_message(&got, again, 0) == 99);
  for (size_t i = 0; i < 99; i++) { assert(again[i] == wire[i]); }
}

/* ---- Timestamp 2: 8 bytes ---------------------------------------------------- */

/* Timestamp 2 */
typedef struct {
  uint8_t seconds[4];      /* bytes 0 to 3 */
  uint8_t nanoseconds[4];  /* bytes 4 to 7 */
} Timestamp2;

/* any Timestamp 2 at all: every byte one the checker chooses */
static void any_timestamp2(Timestamp2 *record) {
  for (size_t i = 0; i < 4; i++) { record->seconds[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = arbitrary(); }
}

/* Timestamp 2 to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_timestamp2(const Timestamp2 *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->seconds[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->nanoseconds[i]; }

  return at;
}

/* Timestamp 2 off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_timestamp2(Timestamp2 *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->seconds[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = wire[at++]; }

  return at;
}

/* what was read of Timestamp 2 is what was written, byte for byte */
static void equal_timestamp2(const Timestamp2 *read, const Timestamp2 *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->seconds[i] == written->seconds[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->nanoseconds[i] == written->nanoseconds[i]); }
}

/* Timestamp 2: written and read back, then read and written back */
static void check_timestamp2(void) {
  Timestamp2 sent;
  Timestamp2 got;
  uint8_t wire[8];
  uint8_t again[8];

  any_timestamp2(&sent);
  assert(encode_timestamp2(&sent, wire, 0) == 8);
  assert(decode_timestamp2(&got, wire, 0) == 8);
  equal_timestamp2(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_timestamp2(&got, wire, 0) == 8);
  assert(encode_timestamp2(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Trade Correction Message: 49 bytes -------------------------------------- */

/* Used to correct CTA eligible Equity, Local Issue or Bond trade information. */
typedef struct {
  uint8_t security_symbol[11];                         /* bytes 0 to 10 */
  uint8_t instrument_type;                             /* byte 11 */
  uint8_t corrected_sale_condition[4];                 /* bytes 12 to 15 */
  uint8_t corrected_trade_price[8];                    /* bytes 16 to 23 */
  uint8_t corrected_trade_volume[4];                   /* bytes 24 to 27 */
  uint8_t corrected_sellers_sale_days;                 /* byte 28 */
  uint8_t corrected_stop_stock_indicator;              /* byte 29 */
  uint8_t corrected_trade_through_exempt_indicator;    /* byte 30 */
  uint8_t corrected_short_sale_restriction_indicator;  /* byte 31 */
  uint8_t trade_reporting_facility_id;                 /* byte 32 */
  Timestamp2 timestamp_2;                              /* bytes 33 to 40 */
  uint8_t original_participant_reference_number[8];    /* bytes 41 to 48 */
} TradeCorrectionMessage;

/* any Trade Correction Message at all: every byte one the checker chooses */
static void any_trade_correction_message(TradeCorrectionMessage *record) {
  for (size_t i = 0; i < 11; i++) { record->security_symbol[i] = arbitrary(); }
  record->instrument_type = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->corrected_sale_condition[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->corrected_trade_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->corrected_trade_volume[i] = arbitrary(); }
  record->corrected_sellers_sale_days = arbitrary();
  record->corrected_stop_stock_indicator = arbitrary();
  record->corrected_trade_through_exempt_indicator = arbitrary();
  record->corrected_short_sale_restriction_indicator = arbitrary();
  record->trade_reporting_facility_id = arbitrary();
  any_timestamp2(&record->timestamp_2);
  for (size_t i = 0; i < 8; i++) { record->original_participant_reference_number[i] = arbitrary(); }
}

/* Trade Correction Message to the wire: 49 bytes from at, returning where the next byte goes */
static size_t encode_trade_correction_message(const TradeCorrectionMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->security_symbol[i]; }
  wire[at++] = record->instrument_type;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->corrected_sale_condition[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->corrected_trade_price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->corrected_trade_volume[i]; }
  wire[at++] = record->corrected_sellers_sale_days;
  wire[at++] = record->corrected_stop_stock_indicator;
  wire[at++] = record->corrected_trade_through_exempt_indicator;
  wire[at++] = record->corrected_short_sale_restriction_indicator;
  wire[at++] = record->trade_reporting_facility_id;
  at = encode_timestamp2(&record->timestamp_2, wire, at);
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->original_participant_reference_number[i]; }

  return at;
}

/* Trade Correction Message off the wire: 49 bytes from at, returning where the next byte lies */
static size_t decode_trade_correction_message(TradeCorrectionMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 11; i++) { record->security_symbol[i] = wire[at++]; }
  record->instrument_type = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->corrected_sale_condition[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->corrected_trade_price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->corrected_trade_volume[i] = wire[at++]; }
  record->corrected_sellers_sale_days = wire[at++];
  record->corrected_stop_stock_indicator = wire[at++];
  record->corrected_trade_through_exempt_indicator = wire[at++];
  record->corrected_short_sale_restriction_indicator = wire[at++];
  record->trade_reporting_facility_id = wire[at++];
  at = decode_timestamp2(&record->timestamp_2, wire, at);
  for (size_t i = 0; i < 8; i++) { record->original_participant_reference_number[i] = wire[at++]; }

  return at;
}

/* what was read of Trade Correction Message is what was written, byte for byte */
static void equal_trade_correction_message(const TradeCorrectionMessage *read, const TradeCorrectionMessage *written) {
  for (size_t i = 0; i < 11; i++) { assert(read->security_symbol[i] == written->security_symbol[i]); }
  assert(read->instrument_type == written->instrument_type);
  for (size_t i = 0; i < 4; i++) { assert(read->corrected_sale_condition[i] == written->corrected_sale_condition[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->corrected_trade_price[i] == written->corrected_trade_price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->corrected_trade_volume[i] == written->corrected_trade_volume[i]); }
  assert(read->corrected_sellers_sale_days == written->corrected_sellers_sale_days);
  assert(read->corrected_stop_stock_indicator == written->corrected_stop_stock_indicator);
  assert(read->corrected_trade_through_exempt_indicator == written->corrected_trade_through_exempt_indicator);
  assert(read->corrected_short_sale_restriction_indicator == written->corrected_short_sale_restriction_indicator);
  assert(read->trade_reporting_facility_id == written->trade_reporting_facility_id);
  equal_timestamp2(&read->timestamp_2, &written->timestamp_2);
  for (size_t i = 0; i < 8; i++) { assert(read->original_participant_reference_number[i] == written->original_participant_reference_number[i]); }
}

/* Trade Correction Message: written and read back, then read and written back */
static void check_trade_correction_message(void) {
  TradeCorrectionMessage sent;
  TradeCorrectionMessage got;
  uint8_t wire[49];
  uint8_t again[49];

  any_trade_correction_message(&sent);
  assert(encode_trade_correction_message(&sent, wire, 0) == 49);
  assert(decode_trade_correction_message(&got, wire, 0) == 49);
  equal_trade_correction_message(&got, &sent);

  for (size_t i = 0; i < 49; i++) { wire[i] = arbitrary(); }
  assert(decode_trade_correction_message(&got, wire, 0) == 49);
  assert(encode_trade_correction_message(&got, again, 0) == 49);
  for (size_t i = 0; i < 49; i++) { assert(again[i] == wire[i]); }
}

/* ---- Fractional Trade Correction Message: 53 bytes --------------------------- */

/* Used to correct a trade when the corrected Trade Volume is a fractional value. */
typedef struct {
  uint8_t security_symbol[11];                         /* bytes 0 to 10 */
  uint8_t instrument_type;                             /* byte 11 */
  uint8_t corrected_sale_condition[4];                 /* bytes 12 to 15 */
  uint8_t corrected_trade_price[8];                    /* bytes 16 to 23 */
  uint8_t corrected_fractional_trade_volume[8];        /* bytes 24 to 31 */
  uint8_t corrected_sellers_sale_days;                 /* byte 32 */
  uint8_t corrected_stop_stock_indicator;              /* byte 33 */
  uint8_t corrected_trade_through_exempt_indicator;    /* byte 34 */
  uint8_t corrected_short_sale_restriction_indicator;  /* byte 35 */
  uint8_t trade_reporting_facility_id;                 /* byte 36 */
  Timestamp2 timestamp_2;                              /* bytes 37 to 44 */
  uint8_t original_participant_reference_number[8];    /* bytes 45 to 52 */
} FractionalTradeCorrectionMessage;

/* any Fractional Trade Correction Message at all: every byte one the checker chooses */
static void any_fractional_trade_correction_message(FractionalTradeCorrectionMessage *record) {
  for (size_t i = 0; i < 11; i++) { record->security_symbol[i] = arbitrary(); }
  record->instrument_type = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->corrected_sale_condition[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->corrected_trade_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->corrected_fractional_trade_volume[i] = arbitrary(); }
  record->corrected_sellers_sale_days = arbitrary();
  record->corrected_stop_stock_indicator = arbitrary();
  record->corrected_trade_through_exempt_indicator = arbitrary();
  record->corrected_short_sale_restriction_indicator = arbitrary();
  record->trade_reporting_facility_id = arbitrary();
  any_timestamp2(&record->timestamp_2);
  for (size_t i = 0; i < 8; i++) { record->original_participant_reference_number[i] = arbitrary(); }
}

/* Fractional Trade Correction Message to the wire: 53 bytes from at, returning where the next byte goes */
static size_t encode_fractional_trade_correction_message(const FractionalTradeCorrectionMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->security_symbol[i]; }
  wire[at++] = record->instrument_type;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->corrected_sale_condition[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->corrected_trade_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->corrected_fractional_trade_volume[i]; }
  wire[at++] = record->corrected_sellers_sale_days;
  wire[at++] = record->corrected_stop_stock_indicator;
  wire[at++] = record->corrected_trade_through_exempt_indicator;
  wire[at++] = record->corrected_short_sale_restriction_indicator;
  wire[at++] = record->trade_reporting_facility_id;
  at = encode_timestamp2(&record->timestamp_2, wire, at);
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->original_participant_reference_number[i]; }

  return at;
}

/* Fractional Trade Correction Message off the wire: 53 bytes from at, returning where the next byte lies */
static size_t decode_fractional_trade_correction_message(FractionalTradeCorrectionMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 11; i++) { record->security_symbol[i] = wire[at++]; }
  record->instrument_type = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->corrected_sale_condition[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->corrected_trade_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->corrected_fractional_trade_volume[i] = wire[at++]; }
  record->corrected_sellers_sale_days = wire[at++];
  record->corrected_stop_stock_indicator = wire[at++];
  record->corrected_trade_through_exempt_indicator = wire[at++];
  record->corrected_short_sale_restriction_indicator = wire[at++];
  record->trade_reporting_facility_id = wire[at++];
  at = decode_timestamp2(&record->timestamp_2, wire, at);
  for (size_t i = 0; i < 8; i++) { record->original_participant_reference_number[i] = wire[at++]; }

  return at;
}

/* what was read of Fractional Trade Correction Message is what was written, byte for byte */
static void equal_fractional_trade_correction_message(const FractionalTradeCorrectionMessage *read, const FractionalTradeCorrectionMessage *written) {
  for (size_t i = 0; i < 11; i++) { assert(read->security_symbol[i] == written->security_symbol[i]); }
  assert(read->instrument_type == written->instrument_type);
  for (size_t i = 0; i < 4; i++) { assert(read->corrected_sale_condition[i] == written->corrected_sale_condition[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->corrected_trade_price[i] == written->corrected_trade_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->corrected_fractional_trade_volume[i] == written->corrected_fractional_trade_volume[i]); }
  assert(read->corrected_sellers_sale_days == written->corrected_sellers_sale_days);
  assert(read->corrected_stop_stock_indicator == written->corrected_stop_stock_indicator);
  assert(read->corrected_trade_through_exempt_indicator == written->corrected_trade_through_exempt_indicator);
  assert(read->corrected_short_sale_restriction_indicator == written->corrected_short_sale_restriction_indicator);
  assert(read->trade_reporting_facility_id == written->trade_reporting_facility_id);
  equal_timestamp2(&read->timestamp_2, &written->timestamp_2);
  for (size_t i = 0; i < 8; i++) { assert(read->original_participant_reference_number[i] == written->original_participant_reference_number[i]); }
}

/* Fractional Trade Correction Message: written and read back, then read and written back */
static void check_fractional_trade_correction_message(void) {
  FractionalTradeCorrectionMessage sent;
  FractionalTradeCorrectionMessage got;
  uint8_t wire[53];
  uint8_t again[53];

  any_fractional_trade_correction_message(&sent);
  assert(encode_fractional_trade_correction_message(&sent, wire, 0) == 53);
  assert(decode_fractional_trade_correction_message(&got, wire, 0) == 53);
  equal_fractional_trade_correction_message(&got, &sent);

  for (size_t i = 0; i < 53; i++) { wire[i] = arbitrary(); }
  assert(decode_fractional_trade_correction_message(&got, wire, 0) == 53);
  assert(encode_fractional_trade_correction_message(&got, again, 0) == 53);
  for (size_t i = 0; i < 53; i++) { assert(again[i] == wire[i]); }
}

/* ---- Long Trade Message: 40 bytes -------------------------------------------- */

/* Used to report trade information for CTA eligible Equity, Local Issue or Bonds. */
typedef struct {
  uint8_t security_symbol[11];             /* bytes 0 to 10 */
  uint8_t instrument_type;                 /* byte 11 */
  uint8_t sale_condition[4];               /* bytes 12 to 15 */
  uint8_t trade_price[8];                  /* bytes 16 to 23 */
  uint8_t trade_volume[4];                 /* bytes 24 to 27 */
  uint8_t sellers_sale_days;               /* byte 28 */
  uint8_t stop_stock_indicator;            /* byte 29 */
  uint8_t trade_through_exempt_indicator;  /* byte 30 */
  uint8_t trade_reporting_facility_id;     /* byte 31 */
  Timestamp2 timestamp_2;                  /* bytes 32 to 39 */
} LongTradeMessage;

/* any Long Trade Message at all: every byte one the checker chooses */
static void any_long_trade_message(LongTradeMessage *record) {
  for (size_t i = 0; i < 11; i++) { record->security_symbol[i] = arbitrary(); }
  record->instrument_type = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->sale_condition[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->trade_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->trade_volume[i] = arbitrary(); }
  record->sellers_sale_days = arbitrary();
  record->stop_stock_indicator = arbitrary();
  record->trade_through_exempt_indicator = arbitrary();
  record->trade_reporting_facility_id = arbitrary();
  any_timestamp2(&record->timestamp_2);
}

/* Long Trade Message to the wire: 40 bytes from at, returning where the next byte goes */
static size_t encode_long_trade_message(const LongTradeMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->security_symbol[i]; }
  wire[at++] = record->instrument_type;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->sale_condition[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->trade_price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->trade_volume[i]; }
  wire[at++] = record->sellers_sale_days;
  wire[at++] = record->stop_stock_indicator;
  wire[at++] = record->trade_through_exempt_indicator;
  wire[at++] = record->trade_reporting_facility_id;
  at = encode_timestamp2(&record->timestamp_2, wire, at);

  return at;
}

/* Long Trade Message off the wire: 40 bytes from at, returning where the next byte lies */
static size_t decode_long_trade_message(LongTradeMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 11; i++) { record->security_symbol[i] = wire[at++]; }
  record->instrument_type = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->sale_condition[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->trade_price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->trade_volume[i] = wire[at++]; }
  record->sellers_sale_days = wire[at++];
  record->stop_stock_indicator = wire[at++];
  record->trade_through_exempt_indicator = wire[at++];
  record->trade_reporting_facility_id = wire[at++];
  at = decode_timestamp2(&record->timestamp_2, wire, at);

  return at;
}

/* what was read of Long Trade Message is what was written, byte for byte */
static void equal_long_trade_message(const LongTradeMessage *read, const LongTradeMessage *written) {
  for (size_t i = 0; i < 11; i++) { assert(read->security_symbol[i] == written->security_symbol[i]); }
  assert(read->instrument_type == written->instrument_type);
  for (size_t i = 0; i < 4; i++) { assert(read->sale_condition[i] == written->sale_condition[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->trade_price[i] == written->trade_price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->trade_volume[i] == written->trade_volume[i]); }
  assert(read->sellers_sale_days == written->sellers_sale_days);
  assert(read->stop_stock_indicator == written->stop_stock_indicator);
  assert(read->trade_through_exempt_indicator == written->trade_through_exempt_indicator);
  assert(read->trade_reporting_facility_id == written->trade_reporting_facility_id);
  equal_timestamp2(&read->timestamp_2, &written->timestamp_2);
}

/* Long Trade Message: written and read back, then read and written back */
static void check_long_trade_message(void) {
  LongTradeMessage sent;
  LongTradeMessage got;
  uint8_t wire[40];
  uint8_t again[40];

  any_long_trade_message(&sent);
  assert(encode_long_trade_message(&sent, wire, 0) == 40);
  assert(decode_long_trade_message(&got, wire, 0) == 40);
  equal_long_trade_message(&got, &sent);

  for (size_t i = 0; i < 40; i++) { wire[i] = arbitrary(); }
  assert(decode_long_trade_message(&got, wire, 0) == 40);
  assert(encode_long_trade_message(&got, again, 0) == 40);
  for (size_t i = 0; i < 40; i++) { assert(again[i] == wire[i]); }
}

/* ---- Fractional Long Trade Message: 44 bytes --------------------------------- */

/* Used to report trade information for CTA eligible Equity, Local Issues or Bonds in fractional volume. */
typedef struct {
  uint8_t security_symbol[11];             /* bytes 0 to 10 */
  uint8_t instrument_type;                 /* byte 11 */
  uint8_t sale_condition[4];               /* bytes 12 to 15 */
  uint8_t trade_price[8];                  /* bytes 16 to 23 */
  uint8_t fractional_trade_volume[8];      /* bytes 24 to 31 */
  uint8_t sellers_sale_days;               /* byte 32 */
  uint8_t stop_stock_indicator;            /* byte 33 */
  uint8_t trade_through_exempt_indicator;  /* byte 34 */
  uint8_t trade_reporting_facility_id;     /* byte 35 */
  Timestamp2 timestamp_2;                  /* bytes 36 to 43 */
} FractionalLongTradeMessage;

/* any Fractional Long Trade Message at all: every byte one the checker chooses */
static void any_fractional_long_trade_message(FractionalLongTradeMessage *record) {
  for (size_t i = 0; i < 11; i++) { record->security_symbol[i] = arbitrary(); }
  record->instrument_type = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->sale_condition[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->trade_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->fractional_trade_volume[i] = arbitrary(); }
  record->sellers_sale_days = arbitrary();
  record->stop_stock_indicator = arbitrary();
  record->trade_through_exempt_indicator = arbitrary();
  record->trade_reporting_facility_id = arbitrary();
  any_timestamp2(&record->timestamp_2);
}

/* Fractional Long Trade Message to the wire: 44 bytes from at, returning where the next byte goes */
static size_t encode_fractional_long_trade_message(const FractionalLongTradeMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->security_symbol[i]; }
  wire[at++] = record->instrument_type;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->sale_condition[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->trade_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->fractional_trade_volume[i]; }
  wire[at++] = record->sellers_sale_days;
  wire[at++] = record->stop_stock_indicator;
  wire[at++] = record->trade_through_exempt_indicator;
  wire[at++] = record->trade_reporting_facility_id;
  at = encode_timestamp2(&record->timestamp_2, wire, at);

  return at;
}

/* Fractional Long Trade Message off the wire: 44 bytes from at, returning where the next byte lies */
static size_t decode_fractional_long_trade_message(FractionalLongTradeMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 11; i++) { record->security_symbol[i] = wire[at++]; }
  record->instrument_type = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->sale_condition[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->trade_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->fractional_trade_volume[i] = wire[at++]; }
  record->sellers_sale_days = wire[at++];
  record->stop_stock_indicator = wire[at++];
  record->trade_through_exempt_indicator = wire[at++];
  record->trade_reporting_facility_id = wire[at++];
  at = decode_timestamp2(&record->timestamp_2, wire, at);

  return at;
}

/* what was read of Fractional Long Trade Message is what was written, byte for byte */
static void equal_fractional_long_trade_message(const FractionalLongTradeMessage *read, const FractionalLongTradeMessage *written) {
  for (size_t i = 0; i < 11; i++) { assert(read->security_symbol[i] == written->security_symbol[i]); }
  assert(read->instrument_type == written->instrument_type);
  for (size_t i = 0; i < 4; i++) { assert(read->sale_condition[i] == written->sale_condition[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->trade_price[i] == written->trade_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->fractional_trade_volume[i] == written->fractional_trade_volume[i]); }
  assert(read->sellers_sale_days == written->sellers_sale_days);
  assert(read->stop_stock_indicator == written->stop_stock_indicator);
  assert(read->trade_through_exempt_indicator == written->trade_through_exempt_indicator);
  assert(read->trade_reporting_facility_id == written->trade_reporting_facility_id);
  equal_timestamp2(&read->timestamp_2, &written->timestamp_2);
}

/* Fractional Long Trade Message: written and read back, then read and written back */
static void check_fractional_long_trade_message(void) {
  FractionalLongTradeMessage sent;
  FractionalLongTradeMessage got;
  uint8_t wire[44];
  uint8_t again[44];

  any_fractional_long_trade_message(&sent);
  assert(encode_fractional_long_trade_message(&sent, wire, 0) == 44);
  assert(decode_fractional_long_trade_message(&got, wire, 0) == 44);
  equal_fractional_long_trade_message(&got, &sent);

  for (size_t i = 0; i < 44; i++) { wire[i] = arbitrary(); }
  assert(decode_fractional_long_trade_message(&got, wire, 0) == 44);
  assert(encode_fractional_long_trade_message(&got, again, 0) == 44);
  for (size_t i = 0; i < 44; i++) { assert(again[i] == wire[i]); }
}

/* ---- Trading Status Message: 51 bytes ---------------------------------------- */

/* Allows a Participant that is the listing exchange to notify CTS of Trading Halts, Resumes, Indications, Imbalances, Short Sale Restriction Indicators and LULD Reference Prices. Bidirectional. */
typedef struct {
  uint8_t security_symbol[11];                                   /* bytes 0 to 10 */
  uint8_t instrument_type;                                       /* byte 11 */
  uint8_t last_price_opening_reopening_luld_reference_price[8];  /* bytes 12 to 19 */
  uint8_t high_indication_price_upper_limit_price_band[8];       /* bytes 20 to 27 */
  uint8_t low_indication_price_lower_limit_price_band[8];        /* bytes 28 to 35 */
  uint8_t buy_volume[4];                                         /* bytes 36 to 39 */
  uint8_t sell_volume[4];                                        /* bytes 40 to 43 */
  uint8_t security_status;                                       /* byte 44 */
  uint8_t halt_reason;                                           /* byte 45 */
  uint8_t short_sale_restriction_indicator;                      /* byte 46 */
  uint8_t trading_status_id[4];                                  /* bytes 47 to 50 */
} TradingStatusMessage;

/* any Trading Status Message at all: every byte one the checker chooses */
static void any_trading_status_message(TradingStatusMessage *record) {
  for (size_t i = 0; i < 11; i++) { record->security_symbol[i] = arbitrary(); }
  record->instrument_type = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->last_price_opening_reopening_luld_reference_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->high_indication_price_upper_limit_price_band[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->low_indication_price_lower_limit_price_band[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->buy_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->sell_volume[i] = arbitrary(); }
  record->security_status = arbitrary();
  record->halt_reason = arbitrary();
  record->short_sale_restriction_indicator = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->trading_status_id[i] = arbitrary(); }
}

/* Trading Status Message to the wire: 51 bytes from at, returning where the next byte goes */
static size_t encode_trading_status_message(const TradingStatusMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->security_symbol[i]; }
  wire[at++] = record->instrument_type;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->last_price_opening_reopening_luld_reference_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->high_indication_price_upper_limit_price_band[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->low_indication_price_lower_limit_price_band[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->buy_volume[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->sell_volume[i]; }
  wire[at++] = record->security_status;
  wire[at++] = record->halt_reason;
  wire[at++] = record->short_sale_restriction_indicator;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->trading_status_id[i]; }

  return at;
}

/* Trading Status Message off the wire: 51 bytes from at, returning where the next byte lies */
static size_t decode_trading_status_message(TradingStatusMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 11; i++) { record->security_symbol[i] = wire[at++]; }
  record->instrument_type = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->last_price_opening_reopening_luld_reference_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->high_indication_price_upper_limit_price_band[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->low_indication_price_lower_limit_price_band[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->buy_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->sell_volume[i] = wire[at++]; }
  record->security_status = wire[at++];
  record->halt_reason = wire[at++];
  record->short_sale_restriction_indicator = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->trading_status_id[i] = wire[at++]; }

  return at;
}

/* what was read of Trading Status Message is what was written, byte for byte */
static void equal_trading_status_message(const TradingStatusMessage *read, const TradingStatusMessage *written) {
  for (size_t i = 0; i < 11; i++) { assert(read->security_symbol[i] == written->security_symbol[i]); }
  assert(read->instrument_type == written->instrument_type);
  for (size_t i = 0; i < 8; i++) { assert(read->last_price_opening_reopening_luld_reference_price[i] == written->last_price_opening_reopening_luld_reference_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->high_indication_price_upper_limit_price_band[i] == written->high_indication_price_upper_limit_price_band[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->low_indication_price_lower_limit_price_band[i] == written->low_indication_price_lower_limit_price_band[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->buy_volume[i] == written->buy_volume[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->sell_volume[i] == written->sell_volume[i]); }
  assert(read->security_status == written->security_status);
  assert(read->halt_reason == written->halt_reason);
  assert(read->short_sale_restriction_indicator == written->short_sale_restriction_indicator);
  for (size_t i = 0; i < 4; i++) { assert(read->trading_status_id[i] == written->trading_status_id[i]); }
}

/* Trading Status Message: written and read back, then read and written back */
static void check_trading_status_message(void) {
  TradingStatusMessage sent;
  TradingStatusMessage got;
  uint8_t wire[51];
  uint8_t again[51];

  any_trading_status_message(&sent);
  assert(encode_trading_status_message(&sent, wire, 0) == 51);
  assert(decode_trading_status_message(&got, wire, 0) == 51);
  equal_trading_status_message(&got, &sent);

  for (size_t i = 0; i < 51; i++) { wire[i] = arbitrary(); }
  assert(decode_trading_status_message(&got, wire, 0) == 51);
  assert(encode_trading_status_message(&got, again, 0) == 51);
  for (size_t i = 0; i < 51; i++) { assert(again[i] == wire[i]); }
}

/* ---- Short Trade Message: 14 bytes ------------------------------------------- */

/* Reports trade information for CTA eligible Equity, Local Issues or Bonds when the trade meets all criteria for the compact Short format; otherwise the Long Trade message is used. */
typedef struct {
  uint8_t security_symbol_short[5];  /* bytes 0 to 4 */
  uint8_t sale_condition_short;      /* byte 5 */
  uint8_t sale_condition_category;   /* byte 6 */
  uint8_t trade_price_short[2];      /* bytes 7 to 8 */
  uint8_t trade_volume_short[2];     /* bytes 9 to 10 */
  uint8_t reserved_3[3];             /* bytes 11 to 13 */
} ShortTradeMessage;

/* any Short Trade Message at all: every byte one the checker chooses */
static void any_short_trade_message(ShortTradeMessage *record) {
  for (size_t i = 0; i < 5; i++) { record->security_symbol_short[i] = arbitrary(); }
  record->sale_condition_short = arbitrary();
  record->sale_condition_category = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->trade_price_short[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->trade_volume_short[i] = arbitrary(); }
  for (size_t i = 0; i < 3; i++) { record->reserved_3[i] = arbitrary(); }
}

/* Short Trade Message to the wire: 14 bytes from at, returning where the next byte goes */
static size_t encode_short_trade_message(const ShortTradeMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 5; i++) { wire[at++] = record->security_symbol_short[i]; }
  wire[at++] = record->sale_condition_short;
  wire[at++] = record->sale_condition_category;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->trade_price_short[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->trade_volume_short[i]; }
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->reserved_3[i]; }

  return at;
}

/* Short Trade Message off the wire: 14 bytes from at, returning where the next byte lies */
static size_t decode_short_trade_message(ShortTradeMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 5; i++) { record->security_symbol_short[i] = wire[at++]; }
  record->sale_condition_short = wire[at++];
  record->sale_condition_category = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->trade_price_short[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->trade_volume_short[i] = wire[at++]; }
  for (size_t i = 0; i < 3; i++) { record->reserved_3[i] = wire[at++]; }

  return at;
}

/* what was read of Short Trade Message is what was written, byte for byte */
static void equal_short_trade_message(const ShortTradeMessage *read, const ShortTradeMessage *written) {
  for (size_t i = 0; i < 5; i++) { assert(read->security_symbol_short[i] == written->security_symbol_short[i]); }
  assert(read->sale_condition_short == written->sale_condition_short);
  assert(read->sale_condition_category == written->sale_condition_category);
  for (size_t i = 0; i < 2; i++) { assert(read->trade_price_short[i] == written->trade_price_short[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->trade_volume_short[i] == written->trade_volume_short[i]); }
  for (size_t i = 0; i < 3; i++) { assert(read->reserved_3[i] == written->reserved_3[i]); }
}

/* Short Trade Message: written and read back, then read and written back */
static void check_short_trade_message(void) {
  ShortTradeMessage sent;
  ShortTradeMessage got;
  uint8_t wire[14];
  uint8_t again[14];

  any_short_trade_message(&sent);
  assert(encode_short_trade_message(&sent, wire, 0) == 14);
  assert(decode_short_trade_message(&got, wire, 0) == 14);
  equal_short_trade_message(&got, &sent);

  for (size_t i = 0; i < 14; i++) { wire[i] = arbitrary(); }
  assert(decode_short_trade_message(&got, wire, 0) == 14);
  assert(encode_short_trade_message(&got, again, 0) == 14);
  for (size_t i = 0; i < 14; i++) { assert(again[i] == wire[i]); }
}

/* ---- Fractional Short Trade Message: 16 bytes -------------------------------- */

/* Reports trade information with fractional volume when the trade meets all criteria for the compact Short format; otherwise the Long Trade or Fractional Long Trade message is used. */
typedef struct {
  uint8_t security_symbol_short[5];          /* bytes 0 to 4 */
  uint8_t sale_condition_short;              /* byte 5 */
  uint8_t sale_condition_category;           /* byte 6 */
  uint8_t trade_price_short[2];              /* bytes 7 to 8 */
  uint8_t fractional_trade_volume_short[4];  /* bytes 9 to 12 */
  uint8_t reserved_3[3];                     /* bytes 13 to 15 */
} FractionalShortTradeMessage;

/* any Fractional Short Trade Message at all: every byte one the checker chooses */
static void any_fractional_short_trade_message(FractionalShortTradeMessage *record) {
  for (size_t i = 0; i < 5; i++) { record->security_symbol_short[i] = arbitrary(); }
  record->sale_condition_short = arbitrary();
  record->sale_condition_category = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->trade_price_short[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->fractional_trade_volume_short[i] = arbitrary(); }
  for (size_t i = 0; i < 3; i++) { record->reserved_3[i] = arbitrary(); }
}

/* Fractional Short Trade Message to the wire: 16 bytes from at, returning where the next byte goes */
static size_t encode_fractional_short_trade_message(const FractionalShortTradeMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 5; i++) { wire[at++] = record->security_symbol_short[i]; }
  wire[at++] = record->sale_condition_short;
  wire[at++] = record->sale_condition_category;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->trade_price_short[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->fractional_trade_volume_short[i]; }
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->reserved_3[i]; }

  return at;
}

/* Fractional Short Trade Message off the wire: 16 bytes from at, returning where the next byte lies */
static size_t decode_fractional_short_trade_message(FractionalShortTradeMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 5; i++) { record->security_symbol_short[i] = wire[at++]; }
  record->sale_condition_short = wire[at++];
  record->sale_condition_category = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->trade_price_short[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->fractional_trade_volume_short[i] = wire[at++]; }
  for (size_t i = 0; i < 3; i++) { record->reserved_3[i] = wire[at++]; }

  return at;
}

/* what was read of Fractional Short Trade Message is what was written, byte for byte */
static void equal_fractional_short_trade_message(const FractionalShortTradeMessage *read, const FractionalShortTradeMessage *written) {
  for (size_t i = 0; i < 5; i++) { assert(read->security_symbol_short[i] == written->security_symbol_short[i]); }
  assert(read->sale_condition_short == written->sale_condition_short);
  assert(read->sale_condition_category == written->sale_condition_category);
  for (size_t i = 0; i < 2; i++) { assert(read->trade_price_short[i] == written->trade_price_short[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->fractional_trade_volume_short[i] == written->fractional_trade_volume_short[i]); }
  for (size_t i = 0; i < 3; i++) { assert(read->reserved_3[i] == written->reserved_3[i]); }
}

/* Fractional Short Trade Message: written and read back, then read and written back */
static void check_fractional_short_trade_message(void) {
  FractionalShortTradeMessage sent;
  FractionalShortTradeMessage got;
  uint8_t wire[16];
  uint8_t again[16];

  any_fractional_short_trade_message(&sent);
  assert(encode_fractional_short_trade_message(&sent, wire, 0) == 16);
  assert(decode_fractional_short_trade_message(&got, wire, 0) == 16);
  equal_fractional_short_trade_message(&got, &sent);

  for (size_t i = 0; i < 16; i++) { wire[i] = arbitrary(); }
  assert(decode_fractional_short_trade_message(&got, wire, 0) == 16);
  assert(encode_fractional_short_trade_message(&got, again, 0) == 16);
  for (size_t i = 0; i < 16; i++) { assert(again[i] == wire[i]); }
}

/* ---- Trade Cancel Error Message: 31 bytes ------------------------------------ */

/* Allows a Participant to cancel or error trade reports for CTA eligible Equity, Local Issue or Bond originally reported using a fixed message format. */
typedef struct {
  uint8_t security_symbol[11];                       /* bytes 0 to 10 */
  uint8_t instrument_type;                           /* byte 11 */
  uint8_t trade_through_exempt_indicator;            /* byte 12 */
  uint8_t trade_reporting_facility_id;               /* byte 13 */
  uint8_t original_participant_reference_number[8];  /* bytes 14 to 21 */
  Timestamp2 timestamp_2;                            /* bytes 22 to 29 */
  uint8_t cancel_error_action;                       /* byte 30 */
} TradeCancelErrorMessage;

/* any Trade Cancel Error Message at all: every byte one the checker chooses */
static void any_trade_cancel_error_message(TradeCancelErrorMessage *record) {
  for (size_t i = 0; i < 11; i++) { record->security_symbol[i] = arbitrary(); }
  record->instrument_type = arbitrary();
  record->trade_through_exempt_indicator = arbitrary();
  record->trade_reporting_facility_id = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->original_participant_reference_number[i] = arbitrary(); }
  any_timestamp2(&record->timestamp_2);
  record->cancel_error_action = arbitrary();
}

/* Trade Cancel Error Message to the wire: 31 bytes from at, returning where the next byte goes */
static size_t encode_trade_cancel_error_message(const TradeCancelErrorMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->security_symbol[i]; }
  wire[at++] = record->instrument_type;
  wire[at++] = record->trade_through_exempt_indicator;
  wire[at++] = record->trade_reporting_facility_id;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->original_participant_reference_number[i]; }
  at = encode_timestamp2(&record->timestamp_2, wire, at);
  wire[at++] = record->cancel_error_action;

  return at;
}

/* Trade Cancel Error Message off the wire: 31 bytes from at, returning where the next byte lies */
static size_t decode_trade_cancel_error_message(TradeCancelErrorMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 11; i++) { record->security_symbol[i] = wire[at++]; }
  record->instrument_type = wire[at++];
  record->trade_through_exempt_indicator = wire[at++];
  record->trade_reporting_facility_id = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->original_participant_reference_number[i] = wire[at++]; }
  at = decode_timestamp2(&record->timestamp_2, wire, at);
  record->cancel_error_action = wire[at++];

  return at;
}

/* what was read of Trade Cancel Error Message is what was written, byte for byte */
static void equal_trade_cancel_error_message(const TradeCancelErrorMessage *read, const TradeCancelErrorMessage *written) {
  for (size_t i = 0; i < 11; i++) { assert(read->security_symbol[i] == written->security_symbol[i]); }
  assert(read->instrument_type == written->instrument_type);
  assert(read->trade_through_exempt_indicator == written->trade_through_exempt_indicator);
  assert(read->trade_reporting_facility_id == written->trade_reporting_facility_id);
  for (size_t i = 0; i < 8; i++) { assert(read->original_participant_reference_number[i] == written->original_participant_reference_number[i]); }
  equal_timestamp2(&read->timestamp_2, &written->timestamp_2);
  assert(read->cancel_error_action == written->cancel_error_action);
}

/* Trade Cancel Error Message: written and read back, then read and written back */
static void check_trade_cancel_error_message(void) {
  TradeCancelErrorMessage sent;
  TradeCancelErrorMessage got;
  uint8_t wire[31];
  uint8_t again[31];

  any_trade_cancel_error_message(&sent);
  assert(encode_trade_cancel_error_message(&sent, wire, 0) == 31);
  assert(decode_trade_cancel_error_message(&got, wire, 0) == 31);
  equal_trade_cancel_error_message(&got, &sent);

  for (size_t i = 0; i < 31; i++) { wire[i] = arbitrary(); }
  assert(decode_trade_cancel_error_message(&got, wire, 0) == 31);
  assert(encode_trade_cancel_error_message(&got, again, 0) == 31);
  for (size_t i = 0; i < 31; i++) { assert(again[i] == wire[i]); }
}

/* ---- What esbmc checks ------------------------------------------------------- */

/* every record of the protocol, each on its own buffers */
static void checks(void) {
  check_block_header();
  check_timestamp1();
  check_message_header();
  check_rejection_message();
  check_warning_message();
  check_sequence_information_and_message_count_response_message();
  check_test_message();
  check_index_message();
  check_bid_and_offer_index_message();
  check_approximate_trades_and_total_dollar_value_message();
  check_crossing_session_message();
  check_corrected_prior_day_trade_date_and_time();
  check_original_prior_day_trade_date_and_time();
  check_prior_day_trade_correction_message();
  check_fractional_prior_day_trade_correction_message();
  check_prior_day_trade_date_and_time();
  check_prior_day_trade_message();
  check_fractional_prior_day_trade_message();
  check_prior_day_trade_cancel_error_message();
  check_fractional_prior_day_trade_cancel_error_message();
  check_auction_status_message();
  check_timestamp2();
  check_trade_correction_message();
  check_fractional_trade_correction_message();
  check_long_trade_message();
  check_fractional_long_trade_message();
  check_trading_status_message();
  check_short_trade_message();
  check_fractional_short_trade_message();
  check_trade_cancel_error_message();
}

int main(void) {
#ifdef CONCRETE
  for (pattern = 0; pattern < 4; pattern++) { checks(); }
#else
  checks();
#endif

  return 0;
}
