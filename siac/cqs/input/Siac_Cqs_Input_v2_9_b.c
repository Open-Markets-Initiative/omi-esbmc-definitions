// siac/cqs/input/Siac_Cqs_Input_v2_9_b.c
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
 *   - a Integrity rule
 *   - a run counted by a field
 *   - a field present only on a condition
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

/* Used for all errors to notify a Participant that CQS has found an error in the Block Header, Message Header or Message body of a Participant Input message. */
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

/* Sent from CQS to a Participant in response to a Block Sequence Number Gap. The block will still be processed by CQS. */
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

/* Generated by CQS to a Participant in response to a Sequence Information and Message Count Inquiry message. Transmitted in a separate block. */
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

/* ---- Odd Lot Refresh Request Message: 30 bytes ------------------------------- */

/* Generated by CQS to a Participant in case of a CQS failure where CQS may inadvertently lose quotes previously reported by the Participant. Provides start and end symbol ranges for affected symbols. */
typedef struct {
  uint8_t security_symbol_begin_range[11];  /* bytes 0 to 10 */
  uint8_t security_symbol_end_range[11];    /* bytes 11 to 21 */
  uint8_t reserved_8[8];                    /* bytes 22 to 29 */
} OddLotRefreshRequestMessage;

/* any Odd Lot Refresh Request Message at all: every byte one the checker chooses */
static void any_odd_lot_refresh_request_message(OddLotRefreshRequestMessage *record) {
  for (size_t i = 0; i < 11; i++) { record->security_symbol_begin_range[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->security_symbol_end_range[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->reserved_8[i] = arbitrary(); }
}

/* Odd Lot Refresh Request Message to the wire: 30 bytes from at, returning where the next byte goes */
static size_t encode_odd_lot_refresh_request_message(const OddLotRefreshRequestMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->security_symbol_begin_range[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->security_symbol_end_range[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->reserved_8[i]; }

  return at;
}

/* Odd Lot Refresh Request Message off the wire: 30 bytes from at, returning where the next byte lies */
static size_t decode_odd_lot_refresh_request_message(OddLotRefreshRequestMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 11; i++) { record->security_symbol_begin_range[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->security_symbol_end_range[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->reserved_8[i] = wire[at++]; }

  return at;
}

/* what was read of Odd Lot Refresh Request Message is what was written, byte for byte */
static void equal_odd_lot_refresh_request_message(const OddLotRefreshRequestMessage *read, const OddLotRefreshRequestMessage *written) {
  for (size_t i = 0; i < 11; i++) { assert(read->security_symbol_begin_range[i] == written->security_symbol_begin_range[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->security_symbol_end_range[i] == written->security_symbol_end_range[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->reserved_8[i] == written->reserved_8[i]); }
}

/* Odd Lot Refresh Request Message: written and read back, then read and written back */
static void check_odd_lot_refresh_request_message(void) {
  OddLotRefreshRequestMessage sent;
  OddLotRefreshRequestMessage got;
  uint8_t wire[30];
  uint8_t again[30];

  any_odd_lot_refresh_request_message(&sent);
  assert(encode_odd_lot_refresh_request_message(&sent, wire, 0) == 30);
  assert(decode_odd_lot_refresh_request_message(&got, wire, 0) == 30);
  equal_odd_lot_refresh_request_message(&got, &sent);

  for (size_t i = 0; i < 30; i++) { wire[i] = arbitrary(); }
  assert(decode_odd_lot_refresh_request_message(&got, wire, 0) == 30);
  assert(encode_odd_lot_refresh_request_message(&got, again, 0) == 30);
  for (size_t i = 0; i < 30; i++) { assert(again[i] == wire[i]); }
}

/* ---- Test Message: 256 bytes ------------------------------------------------- */

/* Generated by CQS or a Participant to exercise the line and verify transmission integrity. Transmitted as the only message in a block. */
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

/* ---- Short Quote Message: 15 bytes ------------------------------------------- */

/* Reports Bid and Offer quote information for a CTA eligible Equity, Local Issue or Bond meeting the Short Quote criteria. Will be discontinued in favor of Round Lot Short Quote. */
typedef struct {
  uint8_t security_symbol_short[5];  /* bytes 0 to 4 */
  uint8_t bid_price_short[2];        /* bytes 5 to 6 */
  uint8_t bid_size_short[2];         /* bytes 7 to 8 */
  uint8_t offer_price_short[2];      /* bytes 9 to 10 */
  uint8_t offer_size_short[2];       /* bytes 11 to 12 */
  uint8_t reserved_2[2];             /* bytes 13 to 14 */
} ShortQuoteMessage;

/* any Short Quote Message at all: every byte one the checker chooses */
static void any_short_quote_message(ShortQuoteMessage *record) {
  for (size_t i = 0; i < 5; i++) { record->security_symbol_short[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->bid_price_short[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->bid_size_short[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->offer_price_short[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->offer_size_short[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->reserved_2[i] = arbitrary(); }
}

/* Short Quote Message to the wire: 15 bytes from at, returning where the next byte goes */
static size_t encode_short_quote_message(const ShortQuoteMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 5; i++) { wire[at++] = record->security_symbol_short[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->bid_price_short[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->bid_size_short[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->offer_price_short[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->offer_size_short[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->reserved_2[i]; }

  return at;
}

/* Short Quote Message off the wire: 15 bytes from at, returning where the next byte lies */
static size_t decode_short_quote_message(ShortQuoteMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 5; i++) { record->security_symbol_short[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->bid_price_short[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->bid_size_short[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->offer_price_short[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->offer_size_short[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->reserved_2[i] = wire[at++]; }

  return at;
}

/* what was read of Short Quote Message is what was written, byte for byte */
static void equal_short_quote_message(const ShortQuoteMessage *read, const ShortQuoteMessage *written) {
  for (size_t i = 0; i < 5; i++) { assert(read->security_symbol_short[i] == written->security_symbol_short[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->bid_price_short[i] == written->bid_price_short[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->bid_size_short[i] == written->bid_size_short[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->offer_price_short[i] == written->offer_price_short[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->offer_size_short[i] == written->offer_size_short[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->reserved_2[i] == written->reserved_2[i]); }
}

/* Short Quote Message: written and read back, then read and written back */
static void check_short_quote_message(void) {
  ShortQuoteMessage sent;
  ShortQuoteMessage got;
  uint8_t wire[15];
  uint8_t again[15];

  any_short_quote_message(&sent);
  assert(encode_short_quote_message(&sent, wire, 0) == 15);
  assert(decode_short_quote_message(&got, wire, 0) == 15);
  equal_short_quote_message(&got, &sent);

  for (size_t i = 0; i < 15; i++) { wire[i] = arbitrary(); }
  assert(decode_short_quote_message(&got, wire, 0) == 15);
  assert(encode_short_quote_message(&got, again, 0) == 15);
  for (size_t i = 0; i < 15; i++) { assert(again[i] == wire[i]); }
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

/* ---- Long Quote Message: 55 bytes -------------------------------------------- */

/* Reports quote information for a CTA eligible Equity, Local Issue or Bond. Used to report trading suspensions, price indications and trading range indications on the CQS input lines. Will be discontinued in favor of Round Lot Long Quote. */
typedef struct {
  uint8_t security_symbol[11];               /* bytes 0 to 10 */
  uint8_t instrument_type;                   /* byte 11 */
  uint8_t quote_condition;                   /* byte 12 */
  uint8_t security_status_indicator;         /* byte 13 */
  uint8_t bid_price[8];                      /* bytes 14 to 21 */
  uint8_t bid_size[4];                       /* bytes 22 to 25 */
  uint8_t offer_price[8];                    /* bytes 26 to 33 */
  uint8_t offer_size[4];                     /* bytes 34 to 37 */
  uint8_t retail_interest_indicator;         /* byte 38 */
  uint8_t settlement_condition;              /* byte 39 */
  uint8_t market_condition;                  /* byte 40 */
  uint8_t finra_market_maker_id[4];          /* bytes 41 to 44 */
  uint8_t finra_bbo_indicator;               /* byte 45 */
  Timestamp2 timestamp_2;                    /* bytes 46 to 53 */
  uint8_t short_sale_restriction_indicator;  /* byte 54 */
} LongQuoteMessage;

/* any Long Quote Message at all: every byte one the checker chooses */
static void any_long_quote_message(LongQuoteMessage *record) {
  for (size_t i = 0; i < 11; i++) { record->security_symbol[i] = arbitrary(); }
  record->instrument_type = arbitrary();
  record->quote_condition = arbitrary();
  record->security_status_indicator = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->bid_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->bid_size[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->offer_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->offer_size[i] = arbitrary(); }
  record->retail_interest_indicator = arbitrary();
  record->settlement_condition = arbitrary();
  record->market_condition = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->finra_market_maker_id[i] = arbitrary(); }
  record->finra_bbo_indicator = arbitrary();
  any_timestamp2(&record->timestamp_2);
  record->short_sale_restriction_indicator = arbitrary();
}

/* Long Quote Message to the wire: 55 bytes from at, returning where the next byte goes */
static size_t encode_long_quote_message(const LongQuoteMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->security_symbol[i]; }
  wire[at++] = record->instrument_type;
  wire[at++] = record->quote_condition;
  wire[at++] = record->security_status_indicator;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->bid_price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->bid_size[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->offer_price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->offer_size[i]; }
  wire[at++] = record->retail_interest_indicator;
  wire[at++] = record->settlement_condition;
  wire[at++] = record->market_condition;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->finra_market_maker_id[i]; }
  wire[at++] = record->finra_bbo_indicator;
  at = encode_timestamp2(&record->timestamp_2, wire, at);
  wire[at++] = record->short_sale_restriction_indicator;

  return at;
}

/* Long Quote Message off the wire: 55 bytes from at, returning where the next byte lies */
static size_t decode_long_quote_message(LongQuoteMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 11; i++) { record->security_symbol[i] = wire[at++]; }
  record->instrument_type = wire[at++];
  record->quote_condition = wire[at++];
  record->security_status_indicator = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->bid_price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->bid_size[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->offer_price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->offer_size[i] = wire[at++]; }
  record->retail_interest_indicator = wire[at++];
  record->settlement_condition = wire[at++];
  record->market_condition = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->finra_market_maker_id[i] = wire[at++]; }
  record->finra_bbo_indicator = wire[at++];
  at = decode_timestamp2(&record->timestamp_2, wire, at);
  record->short_sale_restriction_indicator = wire[at++];

  return at;
}

/* what was read of Long Quote Message is what was written, byte for byte */
static void equal_long_quote_message(const LongQuoteMessage *read, const LongQuoteMessage *written) {
  for (size_t i = 0; i < 11; i++) { assert(read->security_symbol[i] == written->security_symbol[i]); }
  assert(read->instrument_type == written->instrument_type);
  assert(read->quote_condition == written->quote_condition);
  assert(read->security_status_indicator == written->security_status_indicator);
  for (size_t i = 0; i < 8; i++) { assert(read->bid_price[i] == written->bid_price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->bid_size[i] == written->bid_size[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->offer_price[i] == written->offer_price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->offer_size[i] == written->offer_size[i]); }
  assert(read->retail_interest_indicator == written->retail_interest_indicator);
  assert(read->settlement_condition == written->settlement_condition);
  assert(read->market_condition == written->market_condition);
  for (size_t i = 0; i < 4; i++) { assert(read->finra_market_maker_id[i] == written->finra_market_maker_id[i]); }
  assert(read->finra_bbo_indicator == written->finra_bbo_indicator);
  equal_timestamp2(&read->timestamp_2, &written->timestamp_2);
  assert(read->short_sale_restriction_indicator == written->short_sale_restriction_indicator);
}

/* Long Quote Message: written and read back, then read and written back */
static void check_long_quote_message(void) {
  LongQuoteMessage sent;
  LongQuoteMessage got;
  uint8_t wire[55];
  uint8_t again[55];

  any_long_quote_message(&sent);
  assert(encode_long_quote_message(&sent, wire, 0) == 55);
  assert(decode_long_quote_message(&got, wire, 0) == 55);
  equal_long_quote_message(&got, &sent);

  for (size_t i = 0; i < 55; i++) { wire[i] = arbitrary(); }
  assert(decode_long_quote_message(&got, wire, 0) == 55);
  assert(encode_long_quote_message(&got, again, 0) == 55);
  for (size_t i = 0; i < 55; i++) { assert(again[i] == wire[i]); }
}

/* ---- Special Long Quote Message: 88 bytes ------------------------------------ */

/* Used only by FINRA ADF for CTA eligible Equity, Local Issue or Bond to identify the FINRA Best Bid and Best Offer at the Bid and/or Offer side. Will be discontinued in favor of Round Lot FINRA ADF Quote. */
typedef struct {
  uint8_t security_symbol[11];                  /* bytes 0 to 10 */
  uint8_t instrument_type;                      /* byte 11 */
  uint8_t quote_condition;                      /* byte 12 */
  uint8_t security_status_indicator;            /* byte 13 */
  uint8_t bid_price[8];                         /* bytes 14 to 21 */
  uint8_t bid_size[4];                          /* bytes 22 to 25 */
  uint8_t offer_price[8];                       /* bytes 26 to 33 */
  uint8_t offer_size[4];                        /* bytes 34 to 37 */
  uint8_t retail_interest_indicator;            /* byte 38 */
  uint8_t settlement_condition;                 /* byte 39 */
  uint8_t market_condition;                     /* byte 40 */
  uint8_t finra_market_maker_id[4];             /* bytes 41 to 44 */
  uint8_t finra_best_bid_quote_condition;       /* byte 45 */
  uint8_t finra_best_bid_price[8];              /* bytes 46 to 53 */
  uint8_t finra_best_bid_size[4];               /* bytes 54 to 57 */
  uint8_t finra_best_bid_market_maker_id[4];    /* bytes 58 to 61 */
  uint8_t finra_best_offer_quote_condition;     /* byte 62 */
  uint8_t finra_best_offer_price[8];            /* bytes 63 to 70 */
  uint8_t finra_best_offer_size[4];             /* bytes 71 to 74 */
  uint8_t finra_best_offer_market_maker_id[4];  /* bytes 75 to 78 */
  Timestamp2 timestamp_2;                       /* bytes 79 to 86 */
  uint8_t short_sale_restriction_indicator;     /* byte 87 */
} SpecialLongQuoteMessage;

/* any Special Long Quote Message at all: every byte one the checker chooses */
static void any_special_long_quote_message(SpecialLongQuoteMessage *record) {
  for (size_t i = 0; i < 11; i++) { record->security_symbol[i] = arbitrary(); }
  record->instrument_type = arbitrary();
  record->quote_condition = arbitrary();
  record->security_status_indicator = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->bid_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->bid_size[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->offer_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->offer_size[i] = arbitrary(); }
  record->retail_interest_indicator = arbitrary();
  record->settlement_condition = arbitrary();
  record->market_condition = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->finra_market_maker_id[i] = arbitrary(); }
  record->finra_best_bid_quote_condition = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->finra_best_bid_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->finra_best_bid_size[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->finra_best_bid_market_maker_id[i] = arbitrary(); }
  record->finra_best_offer_quote_condition = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->finra_best_offer_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->finra_best_offer_size[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->finra_best_offer_market_maker_id[i] = arbitrary(); }
  any_timestamp2(&record->timestamp_2);
  record->short_sale_restriction_indicator = arbitrary();
}

/* Special Long Quote Message to the wire: 88 bytes from at, returning where the next byte goes */
static size_t encode_special_long_quote_message(const SpecialLongQuoteMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->security_symbol[i]; }
  wire[at++] = record->instrument_type;
  wire[at++] = record->quote_condition;
  wire[at++] = record->security_status_indicator;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->bid_price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->bid_size[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->offer_price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->offer_size[i]; }
  wire[at++] = record->retail_interest_indicator;
  wire[at++] = record->settlement_condition;
  wire[at++] = record->market_condition;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->finra_market_maker_id[i]; }
  wire[at++] = record->finra_best_bid_quote_condition;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->finra_best_bid_price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->finra_best_bid_size[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->finra_best_bid_market_maker_id[i]; }
  wire[at++] = record->finra_best_offer_quote_condition;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->finra_best_offer_price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->finra_best_offer_size[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->finra_best_offer_market_maker_id[i]; }
  at = encode_timestamp2(&record->timestamp_2, wire, at);
  wire[at++] = record->short_sale_restriction_indicator;

  return at;
}

/* Special Long Quote Message off the wire: 88 bytes from at, returning where the next byte lies */
static size_t decode_special_long_quote_message(SpecialLongQuoteMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 11; i++) { record->security_symbol[i] = wire[at++]; }
  record->instrument_type = wire[at++];
  record->quote_condition = wire[at++];
  record->security_status_indicator = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->bid_price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->bid_size[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->offer_price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->offer_size[i] = wire[at++]; }
  record->retail_interest_indicator = wire[at++];
  record->settlement_condition = wire[at++];
  record->market_condition = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->finra_market_maker_id[i] = wire[at++]; }
  record->finra_best_bid_quote_condition = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->finra_best_bid_price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->finra_best_bid_size[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->finra_best_bid_market_maker_id[i] = wire[at++]; }
  record->finra_best_offer_quote_condition = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->finra_best_offer_price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->finra_best_offer_size[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->finra_best_offer_market_maker_id[i] = wire[at++]; }
  at = decode_timestamp2(&record->timestamp_2, wire, at);
  record->short_sale_restriction_indicator = wire[at++];

  return at;
}

/* what was read of Special Long Quote Message is what was written, byte for byte */
static void equal_special_long_quote_message(const SpecialLongQuoteMessage *read, const SpecialLongQuoteMessage *written) {
  for (size_t i = 0; i < 11; i++) { assert(read->security_symbol[i] == written->security_symbol[i]); }
  assert(read->instrument_type == written->instrument_type);
  assert(read->quote_condition == written->quote_condition);
  assert(read->security_status_indicator == written->security_status_indicator);
  for (size_t i = 0; i < 8; i++) { assert(read->bid_price[i] == written->bid_price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->bid_size[i] == written->bid_size[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->offer_price[i] == written->offer_price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->offer_size[i] == written->offer_size[i]); }
  assert(read->retail_interest_indicator == written->retail_interest_indicator);
  assert(read->settlement_condition == written->settlement_condition);
  assert(read->market_condition == written->market_condition);
  for (size_t i = 0; i < 4; i++) { assert(read->finra_market_maker_id[i] == written->finra_market_maker_id[i]); }
  assert(read->finra_best_bid_quote_condition == written->finra_best_bid_quote_condition);
  for (size_t i = 0; i < 8; i++) { assert(read->finra_best_bid_price[i] == written->finra_best_bid_price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->finra_best_bid_size[i] == written->finra_best_bid_size[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->finra_best_bid_market_maker_id[i] == written->finra_best_bid_market_maker_id[i]); }
  assert(read->finra_best_offer_quote_condition == written->finra_best_offer_quote_condition);
  for (size_t i = 0; i < 8; i++) { assert(read->finra_best_offer_price[i] == written->finra_best_offer_price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->finra_best_offer_size[i] == written->finra_best_offer_size[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->finra_best_offer_market_maker_id[i] == written->finra_best_offer_market_maker_id[i]); }
  equal_timestamp2(&read->timestamp_2, &written->timestamp_2);
  assert(read->short_sale_restriction_indicator == written->short_sale_restriction_indicator);
}

/* Special Long Quote Message: written and read back, then read and written back */
static void check_special_long_quote_message(void) {
  SpecialLongQuoteMessage sent;
  SpecialLongQuoteMessage got;
  uint8_t wire[88];
  uint8_t again[88];

  any_special_long_quote_message(&sent);
  assert(encode_special_long_quote_message(&sent, wire, 0) == 88);
  assert(decode_special_long_quote_message(&got, wire, 0) == 88);
  equal_special_long_quote_message(&got, &sent);

  for (size_t i = 0; i < 88; i++) { wire[i] = arbitrary(); }
  assert(decode_special_long_quote_message(&got, wire, 0) == 88);
  assert(encode_special_long_quote_message(&got, again, 0) == 88);
  for (size_t i = 0; i < 88; i++) { assert(again[i] == wire[i]); }
}

/* ---- Trading Status Message: 51 bytes ---------------------------------------- */

/* Allows a Participant that is the listing exchange to notify CQS of Trading Halts, Resumes, Indications, Imbalances, Short Sale Restriction Indicators and LULD Reference Prices. Bidirectional. Supported on both CQS and CTS input lines for redundancy. */
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

/* ---- What esbmc checks ------------------------------------------------------- */

/* every record of the protocol, each on its own buffers */
static void checks(void) {
  check_timestamp1();
  check_message_header();
  check_rejection_message();
  check_warning_message();
  check_sequence_information_and_message_count_response_message();
  check_odd_lot_refresh_request_message();
  check_test_message();
  check_auction_status_message();
  check_short_quote_message();
  check_timestamp2();
  check_long_quote_message();
  check_special_long_quote_message();
  check_trading_status_message();
}

int main(void) {
#ifdef CONCRETE
  for (pattern = 0; pattern < 4; pattern++) { checks(); }
#else
  checks();
#endif

  return 0;
}
