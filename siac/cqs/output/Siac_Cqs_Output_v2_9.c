// siac/cqs/output/Siac_Cqs_Output_v2_9.c
/*
 * The Securities Industry Automation Corporation Output
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
 *   - a run counted by a field
 *   - the dispatch that chooses a message by its type
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

/* ---- Sip Block Timestamp: 8 bytes -------------------------------------------- */

/* Sip Block Timestamp */
typedef struct {
  uint8_t seconds[4];      /* bytes 0 to 3 */
  uint8_t nanoseconds[4];  /* bytes 4 to 7 */
} SipBlockTimestamp;

/* any Sip Block Timestamp at all: every byte one the checker chooses */
static void any_sip_block_timestamp(SipBlockTimestamp *record) {
  for (size_t i = 0; i < 4; i++) { record->seconds[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = arbitrary(); }
}

/* Sip Block Timestamp to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_sip_block_timestamp(const SipBlockTimestamp *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->seconds[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->nanoseconds[i]; }

  return at;
}

/* Sip Block Timestamp off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_sip_block_timestamp(SipBlockTimestamp *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->seconds[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = wire[at++]; }

  return at;
}

/* what was read of Sip Block Timestamp is what was written, byte for byte */
static void equal_sip_block_timestamp(const SipBlockTimestamp *read, const SipBlockTimestamp *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->seconds[i] == written->seconds[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->nanoseconds[i] == written->nanoseconds[i]); }
}

/* Sip Block Timestamp: written and read back, then read and written back */
static void check_sip_block_timestamp(void) {
  SipBlockTimestamp sent;
  SipBlockTimestamp got;
  uint8_t wire[8];
  uint8_t again[8];

  any_sip_block_timestamp(&sent);
  assert(encode_sip_block_timestamp(&sent, wire, 0) == 8);
  assert(decode_sip_block_timestamp(&got, wire, 0) == 8);
  equal_sip_block_timestamp(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_sip_block_timestamp(&got, wire, 0) == 8);
  assert(encode_sip_block_timestamp(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Block Header: 20 bytes -------------------------------------------------- */

/* Cta Output packet header */
typedef struct {
  uint8_t version;                        /* byte 0 */
  uint8_t block_size[2];                  /* bytes 1 to 2 */
  uint8_t data_feed_indicator;            /* byte 3 */
  uint8_t retransmission_indicator;       /* byte 4 */
  uint8_t block_sequence_number[4];       /* bytes 5 to 8 */
  uint8_t messages_in_block;              /* byte 9 */
  SipBlockTimestamp sip_block_timestamp;  /* bytes 10 to 17 */
  uint8_t block_checksum[2];              /* bytes 18 to 19 */
} BlockHeader;

/* any Block Header at all: every byte one the checker chooses */
static void any_block_header(BlockHeader *record) {
  record->version = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->block_size[i] = arbitrary(); }
  record->data_feed_indicator = arbitrary();
  record->retransmission_indicator = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->block_sequence_number[i] = arbitrary(); }
  record->messages_in_block = arbitrary();
  any_sip_block_timestamp(&record->sip_block_timestamp);
  for (size_t i = 0; i < 2; i++) { record->block_checksum[i] = arbitrary(); }
}

/* Block Header to the wire: 20 bytes from at, returning where the next byte goes */
static size_t encode_block_header(const BlockHeader *record, uint8_t *wire, size_t at) {
  wire[at++] = record->version;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->block_size[i]; }
  wire[at++] = record->data_feed_indicator;
  wire[at++] = record->retransmission_indicator;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->block_sequence_number[i]; }
  wire[at++] = record->messages_in_block;
  at = encode_sip_block_timestamp(&record->sip_block_timestamp, wire, at);
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->block_checksum[i]; }

  return at;
}

/* Block Header off the wire: 20 bytes from at, returning where the next byte lies */
static size_t decode_block_header(BlockHeader *record, const uint8_t *wire, size_t at) {
  record->version = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->block_size[i] = wire[at++]; }
  record->data_feed_indicator = wire[at++];
  record->retransmission_indicator = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->block_sequence_number[i] = wire[at++]; }
  record->messages_in_block = wire[at++];
  at = decode_sip_block_timestamp(&record->sip_block_timestamp, wire, at);
  for (size_t i = 0; i < 2; i++) { record->block_checksum[i] = wire[at++]; }

  return at;
}

/* what was read of Block Header is what was written, byte for byte */
static void equal_block_header(const BlockHeader *read, const BlockHeader *written) {
  assert(read->version == written->version);
  for (size_t i = 0; i < 2; i++) { assert(read->block_size[i] == written->block_size[i]); }
  assert(read->data_feed_indicator == written->data_feed_indicator);
  assert(read->retransmission_indicator == written->retransmission_indicator);
  for (size_t i = 0; i < 4; i++) { assert(read->block_sequence_number[i] == written->block_sequence_number[i]); }
  assert(read->messages_in_block == written->messages_in_block);
  equal_sip_block_timestamp(&read->sip_block_timestamp, &written->sip_block_timestamp);
  for (size_t i = 0; i < 2; i++) { assert(read->block_checksum[i] == written->block_checksum[i]); }
}

/* Block Header: written and read back, then read and written back */
static void check_block_header(void) {
  BlockHeader sent;
  BlockHeader got;
  uint8_t wire[20];
  uint8_t again[20];

  any_block_header(&sent);
  assert(encode_block_header(&sent, wire, 0) == 20);
  assert(decode_block_header(&got, wire, 0) == 20);
  equal_block_header(&got, &sent);

  for (size_t i = 0; i < 20; i++) { wire[i] = arbitrary(); }
  assert(decode_block_header(&got, wire, 0) == 20);
  assert(encode_block_header(&got, again, 0) == 20);
  for (size_t i = 0; i < 20; i++) { assert(again[i] == wire[i]); }
}

/* ---- Participant Timestamp: 8 bytes ------------------------------------------ */

/* Participant Timestamp */
typedef struct {
  uint8_t seconds[4];      /* bytes 0 to 3 */
  uint8_t nanoseconds[4];  /* bytes 4 to 7 */
} ParticipantTimestamp;

/* any Participant Timestamp at all: every byte one the checker chooses */
static void any_participant_timestamp(ParticipantTimestamp *record) {
  for (size_t i = 0; i < 4; i++) { record->seconds[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = arbitrary(); }
}

/* Participant Timestamp to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_participant_timestamp(const ParticipantTimestamp *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->seconds[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->nanoseconds[i]; }

  return at;
}

/* Participant Timestamp off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_participant_timestamp(ParticipantTimestamp *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->seconds[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = wire[at++]; }

  return at;
}

/* what was read of Participant Timestamp is what was written, byte for byte */
static void equal_participant_timestamp(const ParticipantTimestamp *read, const ParticipantTimestamp *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->seconds[i] == written->seconds[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->nanoseconds[i] == written->nanoseconds[i]); }
}

/* Participant Timestamp: written and read back, then read and written back */
static void check_participant_timestamp(void) {
  ParticipantTimestamp sent;
  ParticipantTimestamp got;
  uint8_t wire[8];
  uint8_t again[8];

  any_participant_timestamp(&sent);
  assert(encode_participant_timestamp(&sent, wire, 0) == 8);
  assert(decode_participant_timestamp(&got, wire, 0) == 8);
  equal_participant_timestamp(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_participant_timestamp(&got, wire, 0) == 8);
  assert(encode_participant_timestamp(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Start Of Day Message: 22 bytes ------------------------------------------ */

/* The Start of Day message signals the start of normal data dissemination over the multicast lines */
typedef struct {
  uint8_t participant_id;                      /* byte 0 */
  ParticipantTimestamp participant_timestamp;  /* bytes 1 to 8 */
  uint8_t message_id;                          /* byte 9 */
  uint8_t transaction_id[4];                   /* bytes 10 to 13 */
  uint8_t participant_reference_number[8];     /* bytes 14 to 21 */
} StartOfDayMessage;

/* any Start Of Day Message at all: every byte one the checker chooses */
static void any_start_of_day_message(StartOfDayMessage *record) {
  record->participant_id = arbitrary();
  any_participant_timestamp(&record->participant_timestamp);
  record->message_id = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->transaction_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->participant_reference_number[i] = arbitrary(); }
}

/* Start Of Day Message to the wire: 22 bytes from at, returning where the next byte goes */
static size_t encode_start_of_day_message(const StartOfDayMessage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->participant_id;
  at = encode_participant_timestamp(&record->participant_timestamp, wire, at);
  wire[at++] = record->message_id;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->transaction_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->participant_reference_number[i]; }

  return at;
}

/* Start Of Day Message off the wire: 22 bytes from at, returning where the next byte lies */
static size_t decode_start_of_day_message(StartOfDayMessage *record, const uint8_t *wire, size_t at) {
  record->participant_id = wire[at++];
  at = decode_participant_timestamp(&record->participant_timestamp, wire, at);
  record->message_id = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->transaction_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->participant_reference_number[i] = wire[at++]; }

  return at;
}

/* what was read of Start Of Day Message is what was written, byte for byte */
static void equal_start_of_day_message(const StartOfDayMessage *read, const StartOfDayMessage *written) {
  assert(read->participant_id == written->participant_id);
  equal_participant_timestamp(&read->participant_timestamp, &written->participant_timestamp);
  assert(read->message_id == written->message_id);
  for (size_t i = 0; i < 4; i++) { assert(read->transaction_id[i] == written->transaction_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->participant_reference_number[i] == written->participant_reference_number[i]); }
}

/* Start Of Day Message: written and read back, then read and written back */
static void check_start_of_day_message(void) {
  StartOfDayMessage sent;
  StartOfDayMessage got;
  uint8_t wire[22];
  uint8_t again[22];

  any_start_of_day_message(&sent);
  assert(encode_start_of_day_message(&sent, wire, 0) == 22);
  assert(decode_start_of_day_message(&got, wire, 0) == 22);
  equal_start_of_day_message(&got, &sent);

  for (size_t i = 0; i < 22; i++) { wire[i] = arbitrary(); }
  assert(decode_start_of_day_message(&got, wire, 0) == 22);
  assert(encode_start_of_day_message(&got, again, 0) == 22);
  for (size_t i = 0; i < 22; i++) { assert(again[i] == wire[i]); }
}

/* ---- Finra Close Message: 22 bytes ------------------------------------------- */

/* The FINRA Close message is transmitted by FINRA to CQS to indicate the Close state of FINRA Market Maker(s). */
typedef struct {
  uint8_t participant_id;                      /* byte 0 */
  ParticipantTimestamp participant_timestamp;  /* bytes 1 to 8 */
  uint8_t message_id;                          /* byte 9 */
  uint8_t transaction_id[4];                   /* bytes 10 to 13 */
  uint8_t participant_reference_number[8];     /* bytes 14 to 21 */
} FinraCloseMessage;

/* any Finra Close Message at all: every byte one the checker chooses */
static void any_finra_close_message(FinraCloseMessage *record) {
  record->participant_id = arbitrary();
  any_participant_timestamp(&record->participant_timestamp);
  record->message_id = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->transaction_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->participant_reference_number[i] = arbitrary(); }
}

/* Finra Close Message to the wire: 22 bytes from at, returning where the next byte goes */
static size_t encode_finra_close_message(const FinraCloseMessage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->participant_id;
  at = encode_participant_timestamp(&record->participant_timestamp, wire, at);
  wire[at++] = record->message_id;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->transaction_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->participant_reference_number[i]; }

  return at;
}

/* Finra Close Message off the wire: 22 bytes from at, returning where the next byte lies */
static size_t decode_finra_close_message(FinraCloseMessage *record, const uint8_t *wire, size_t at) {
  record->participant_id = wire[at++];
  at = decode_participant_timestamp(&record->participant_timestamp, wire, at);
  record->message_id = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->transaction_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->participant_reference_number[i] = wire[at++]; }

  return at;
}

/* what was read of Finra Close Message is what was written, byte for byte */
static void equal_finra_close_message(const FinraCloseMessage *read, const FinraCloseMessage *written) {
  assert(read->participant_id == written->participant_id);
  equal_participant_timestamp(&read->participant_timestamp, &written->participant_timestamp);
  assert(read->message_id == written->message_id);
  for (size_t i = 0; i < 4; i++) { assert(read->transaction_id[i] == written->transaction_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->participant_reference_number[i] == written->participant_reference_number[i]); }
}

/* Finra Close Message: written and read back, then read and written back */
static void check_finra_close_message(void) {
  FinraCloseMessage sent;
  FinraCloseMessage got;
  uint8_t wire[22];
  uint8_t again[22];

  any_finra_close_message(&sent);
  assert(encode_finra_close_message(&sent, wire, 0) == 22);
  assert(decode_finra_close_message(&got, wire, 0) == 22);
  equal_finra_close_message(&got, &sent);

  for (size_t i = 0; i < 22; i++) { wire[i] = arbitrary(); }
  assert(decode_finra_close_message(&got, wire, 0) == 22);
  assert(encode_finra_close_message(&got, again, 0) == 22);
  for (size_t i = 0; i < 22; i++) { assert(again[i] == wire[i]); }
}

/* ---- Reset Block Sequence Number Message: 22 bytes --------------------------- */

/* The Reset Block Sequence Number message is transmitted when the block sequence number on an output multicast line requires resetting. */
typedef struct {
  uint8_t participant_id;                      /* byte 0 */
  ParticipantTimestamp participant_timestamp;  /* bytes 1 to 8 */
  uint8_t message_id;                          /* byte 9 */
  uint8_t transaction_id[4];                   /* bytes 10 to 13 */
  uint8_t participant_reference_number[8];     /* bytes 14 to 21 */
} ResetBlockSequenceNumberMessage;

/* any Reset Block Sequence Number Message at all: every byte one the checker chooses */
static void any_reset_block_sequence_number_message(ResetBlockSequenceNumberMessage *record) {
  record->participant_id = arbitrary();
  any_participant_timestamp(&record->participant_timestamp);
  record->message_id = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->transaction_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->participant_reference_number[i] = arbitrary(); }
}

/* Reset Block Sequence Number Message to the wire: 22 bytes from at, returning where the next byte goes */
static size_t encode_reset_block_sequence_number_message(const ResetBlockSequenceNumberMessage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->participant_id;
  at = encode_participant_timestamp(&record->participant_timestamp, wire, at);
  wire[at++] = record->message_id;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->transaction_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->participant_reference_number[i]; }

  return at;
}

/* Reset Block Sequence Number Message off the wire: 22 bytes from at, returning where the next byte lies */
static size_t decode_reset_block_sequence_number_message(ResetBlockSequenceNumberMessage *record, const uint8_t *wire, size_t at) {
  record->participant_id = wire[at++];
  at = decode_participant_timestamp(&record->participant_timestamp, wire, at);
  record->message_id = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->transaction_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->participant_reference_number[i] = wire[at++]; }

  return at;
}

/* what was read of Reset Block Sequence Number Message is what was written, byte for byte */
static void equal_reset_block_sequence_number_message(const ResetBlockSequenceNumberMessage *read, const ResetBlockSequenceNumberMessage *written) {
  assert(read->participant_id == written->participant_id);
  equal_participant_timestamp(&read->participant_timestamp, &written->participant_timestamp);
  assert(read->message_id == written->message_id);
  for (size_t i = 0; i < 4; i++) { assert(read->transaction_id[i] == written->transaction_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->participant_reference_number[i] == written->participant_reference_number[i]); }
}

/* Reset Block Sequence Number Message: written and read back, then read and written back */
static void check_reset_block_sequence_number_message(void) {
  ResetBlockSequenceNumberMessage sent;
  ResetBlockSequenceNumberMessage got;
  uint8_t wire[22];
  uint8_t again[22];

  any_reset_block_sequence_number_message(&sent);
  assert(encode_reset_block_sequence_number_message(&sent, wire, 0) == 22);
  assert(decode_reset_block_sequence_number_message(&got, wire, 0) == 22);
  equal_reset_block_sequence_number_message(&got, &sent);

  for (size_t i = 0; i < 22; i++) { wire[i] = arbitrary(); }
  assert(decode_reset_block_sequence_number_message(&got, wire, 0) == 22);
  assert(encode_reset_block_sequence_number_message(&got, again, 0) == 22);
  for (size_t i = 0; i < 22; i++) { assert(again[i] == wire[i]); }
}

/* ---- Finra Open Message: 22 bytes -------------------------------------------- */

/* The FINRA Open message is transmitted by FINRA to CQS */
typedef struct {
  uint8_t participant_id;                      /* byte 0 */
  ParticipantTimestamp participant_timestamp;  /* bytes 1 to 8 */
  uint8_t message_id;                          /* byte 9 */
  uint8_t transaction_id[4];                   /* bytes 10 to 13 */
  uint8_t participant_reference_number[8];     /* bytes 14 to 21 */
} FinraOpenMessage;

/* any Finra Open Message at all: every byte one the checker chooses */
static void any_finra_open_message(FinraOpenMessage *record) {
  record->participant_id = arbitrary();
  any_participant_timestamp(&record->participant_timestamp);
  record->message_id = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->transaction_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->participant_reference_number[i] = arbitrary(); }
}

/* Finra Open Message to the wire: 22 bytes from at, returning where the next byte goes */
static size_t encode_finra_open_message(const FinraOpenMessage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->participant_id;
  at = encode_participant_timestamp(&record->participant_timestamp, wire, at);
  wire[at++] = record->message_id;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->transaction_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->participant_reference_number[i]; }

  return at;
}

/* Finra Open Message off the wire: 22 bytes from at, returning where the next byte lies */
static size_t decode_finra_open_message(FinraOpenMessage *record, const uint8_t *wire, size_t at) {
  record->participant_id = wire[at++];
  at = decode_participant_timestamp(&record->participant_timestamp, wire, at);
  record->message_id = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->transaction_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->participant_reference_number[i] = wire[at++]; }

  return at;
}

/* what was read of Finra Open Message is what was written, byte for byte */
static void equal_finra_open_message(const FinraOpenMessage *read, const FinraOpenMessage *written) {
  assert(read->participant_id == written->participant_id);
  equal_participant_timestamp(&read->participant_timestamp, &written->participant_timestamp);
  assert(read->message_id == written->message_id);
  for (size_t i = 0; i < 4; i++) { assert(read->transaction_id[i] == written->transaction_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->participant_reference_number[i] == written->participant_reference_number[i]); }
}

/* Finra Open Message: written and read back, then read and written back */
static void check_finra_open_message(void) {
  FinraOpenMessage sent;
  FinraOpenMessage got;
  uint8_t wire[22];
  uint8_t again[22];

  any_finra_open_message(&sent);
  assert(encode_finra_open_message(&sent, wire, 0) == 22);
  assert(decode_finra_open_message(&got, wire, 0) == 22);
  equal_finra_open_message(&got, &sent);

  for (size_t i = 0; i < 22; i++) { wire[i] = arbitrary(); }
  assert(decode_finra_open_message(&got, wire, 0) == 22);
  assert(encode_finra_open_message(&got, again, 0) == 22);
  for (size_t i = 0; i < 22; i++) { assert(again[i] == wire[i]); }
}

/* ---- Disaster Recovery Data Center Activation Message: 22 bytes -------------- */

/* The Disaster Recovery Data Center Activation message is transmitted to signify that the Consolidated Quotation System (CQS) has switched processing from the Primary Data Center to the Disaster Recovery Data Center */
typedef struct {
  uint8_t participant_id;                      /* byte 0 */
  ParticipantTimestamp participant_timestamp;  /* bytes 1 to 8 */
  uint8_t message_id;                          /* byte 9 */
  uint8_t transaction_id[4];                   /* bytes 10 to 13 */
  uint8_t participant_reference_number[8];     /* bytes 14 to 21 */
} DisasterRecoveryDataCenterActivationMessage;

/* any Disaster Recovery Data Center Activation Message at all: every byte one the checker chooses */
static void any_disaster_recovery_data_center_activation_message(DisasterRecoveryDataCenterActivationMessage *record) {
  record->participant_id = arbitrary();
  any_participant_timestamp(&record->participant_timestamp);
  record->message_id = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->transaction_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->participant_reference_number[i] = arbitrary(); }
}

/* Disaster Recovery Data Center Activation Message to the wire: 22 bytes from at, returning where the next byte goes */
static size_t encode_disaster_recovery_data_center_activation_message(const DisasterRecoveryDataCenterActivationMessage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->participant_id;
  at = encode_participant_timestamp(&record->participant_timestamp, wire, at);
  wire[at++] = record->message_id;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->transaction_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->participant_reference_number[i]; }

  return at;
}

/* Disaster Recovery Data Center Activation Message off the wire: 22 bytes from at, returning where the next byte lies */
static size_t decode_disaster_recovery_data_center_activation_message(DisasterRecoveryDataCenterActivationMessage *record, const uint8_t *wire, size_t at) {
  record->participant_id = wire[at++];
  at = decode_participant_timestamp(&record->participant_timestamp, wire, at);
  record->message_id = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->transaction_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->participant_reference_number[i] = wire[at++]; }

  return at;
}

/* what was read of Disaster Recovery Data Center Activation Message is what was written, byte for byte */
static void equal_disaster_recovery_data_center_activation_message(const DisasterRecoveryDataCenterActivationMessage *read, const DisasterRecoveryDataCenterActivationMessage *written) {
  assert(read->participant_id == written->participant_id);
  equal_participant_timestamp(&read->participant_timestamp, &written->participant_timestamp);
  assert(read->message_id == written->message_id);
  for (size_t i = 0; i < 4; i++) { assert(read->transaction_id[i] == written->transaction_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->participant_reference_number[i] == written->participant_reference_number[i]); }
}

/* Disaster Recovery Data Center Activation Message: written and read back, then read and written back */
static void check_disaster_recovery_data_center_activation_message(void) {
  DisasterRecoveryDataCenterActivationMessage sent;
  DisasterRecoveryDataCenterActivationMessage got;
  uint8_t wire[22];
  uint8_t again[22];

  any_disaster_recovery_data_center_activation_message(&sent);
  assert(encode_disaster_recovery_data_center_activation_message(&sent, wire, 0) == 22);
  assert(decode_disaster_recovery_data_center_activation_message(&got, wire, 0) == 22);
  equal_disaster_recovery_data_center_activation_message(&got, &sent);

  for (size_t i = 0; i < 22; i++) { wire[i] = arbitrary(); }
  assert(decode_disaster_recovery_data_center_activation_message(&got, wire, 0) == 22);
  assert(encode_disaster_recovery_data_center_activation_message(&got, again, 0) == 22);
  for (size_t i = 0; i < 22; i++) { assert(again[i] == wire[i]); }
}

/* ---- Line Integrity Message: 22 bytes ---------------------------------------- */

/* The Line Integrity message is transmitted over the multicast lines at intervals of sixty (60) seconds to verify continued integrity of multicast transmission */
typedef struct {
  uint8_t participant_id;                      /* byte 0 */
  ParticipantTimestamp participant_timestamp;  /* bytes 1 to 8 */
  uint8_t message_id;                          /* byte 9 */
  uint8_t transaction_id[4];                   /* bytes 10 to 13 */
  uint8_t participant_reference_number[8];     /* bytes 14 to 21 */
} LineIntegrityMessage;

/* any Line Integrity Message at all: every byte one the checker chooses */
static void any_line_integrity_message(LineIntegrityMessage *record) {
  record->participant_id = arbitrary();
  any_participant_timestamp(&record->participant_timestamp);
  record->message_id = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->transaction_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->participant_reference_number[i] = arbitrary(); }
}

/* Line Integrity Message to the wire: 22 bytes from at, returning where the next byte goes */
static size_t encode_line_integrity_message(const LineIntegrityMessage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->participant_id;
  at = encode_participant_timestamp(&record->participant_timestamp, wire, at);
  wire[at++] = record->message_id;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->transaction_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->participant_reference_number[i]; }

  return at;
}

/* Line Integrity Message off the wire: 22 bytes from at, returning where the next byte lies */
static size_t decode_line_integrity_message(LineIntegrityMessage *record, const uint8_t *wire, size_t at) {
  record->participant_id = wire[at++];
  at = decode_participant_timestamp(&record->participant_timestamp, wire, at);
  record->message_id = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->transaction_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->participant_reference_number[i] = wire[at++]; }

  return at;
}

/* what was read of Line Integrity Message is what was written, byte for byte */
static void equal_line_integrity_message(const LineIntegrityMessage *read, const LineIntegrityMessage *written) {
  assert(read->participant_id == written->participant_id);
  equal_participant_timestamp(&read->participant_timestamp, &written->participant_timestamp);
  assert(read->message_id == written->message_id);
  for (size_t i = 0; i < 4; i++) { assert(read->transaction_id[i] == written->transaction_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->participant_reference_number[i] == written->participant_reference_number[i]); }
}

/* Line Integrity Message: written and read back, then read and written back */
static void check_line_integrity_message(void) {
  LineIntegrityMessage sent;
  LineIntegrityMessage got;
  uint8_t wire[22];
  uint8_t again[22];

  any_line_integrity_message(&sent);
  assert(encode_line_integrity_message(&sent, wire, 0) == 22);
  assert(decode_line_integrity_message(&got, wire, 0) == 22);
  equal_line_integrity_message(&got, &sent);

  for (size_t i = 0; i < 22; i++) { wire[i] = arbitrary(); }
  assert(decode_line_integrity_message(&got, wire, 0) == 22);
  assert(encode_line_integrity_message(&got, again, 0) == 22);
  for (size_t i = 0; i < 22; i++) { assert(again[i] == wire[i]); }
}

/* ---- End Of Day Message: 22 bytes -------------------------------------------- */

/* The End of Day message is transmitted over the multicast lines to advise all Data Recipients that there are no further messages of any type transmitted for the day */
typedef struct {
  uint8_t participant_id;                      /* byte 0 */
  ParticipantTimestamp participant_timestamp;  /* bytes 1 to 8 */
  uint8_t message_id;                          /* byte 9 */
  uint8_t transaction_id[4];                   /* bytes 10 to 13 */
  uint8_t participant_reference_number[8];     /* bytes 14 to 21 */
} EndOfDayMessage;

/* any End Of Day Message at all: every byte one the checker chooses */
static void any_end_of_day_message(EndOfDayMessage *record) {
  record->participant_id = arbitrary();
  any_participant_timestamp(&record->participant_timestamp);
  record->message_id = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->transaction_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->participant_reference_number[i] = arbitrary(); }
}

/* End Of Day Message to the wire: 22 bytes from at, returning where the next byte goes */
static size_t encode_end_of_day_message(const EndOfDayMessage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->participant_id;
  at = encode_participant_timestamp(&record->participant_timestamp, wire, at);
  wire[at++] = record->message_id;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->transaction_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->participant_reference_number[i]; }

  return at;
}

/* End Of Day Message off the wire: 22 bytes from at, returning where the next byte lies */
static size_t decode_end_of_day_message(EndOfDayMessage *record, const uint8_t *wire, size_t at) {
  record->participant_id = wire[at++];
  at = decode_participant_timestamp(&record->participant_timestamp, wire, at);
  record->message_id = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->transaction_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->participant_reference_number[i] = wire[at++]; }

  return at;
}

/* what was read of End Of Day Message is what was written, byte for byte */
static void equal_end_of_day_message(const EndOfDayMessage *read, const EndOfDayMessage *written) {
  assert(read->participant_id == written->participant_id);
  equal_participant_timestamp(&read->participant_timestamp, &written->participant_timestamp);
  assert(read->message_id == written->message_id);
  for (size_t i = 0; i < 4; i++) { assert(read->transaction_id[i] == written->transaction_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->participant_reference_number[i] == written->participant_reference_number[i]); }
}

/* End Of Day Message: written and read back, then read and written back */
static void check_end_of_day_message(void) {
  EndOfDayMessage sent;
  EndOfDayMessage got;
  uint8_t wire[22];
  uint8_t again[22];

  any_end_of_day_message(&sent);
  assert(encode_end_of_day_message(&sent, wire, 0) == 22);
  assert(decode_end_of_day_message(&got, wire, 0) == 22);
  equal_end_of_day_message(&got, &sent);

  for (size_t i = 0; i < 22; i++) { wire[i] = arbitrary(); }
  assert(decode_end_of_day_message(&got, wire, 0) == 22);
  assert(encode_end_of_day_message(&got, again, 0) == 22);
  for (size_t i = 0; i < 22; i++) { assert(again[i] == wire[i]); }
}

/* ---- Market Wide Circuit Breaker Decline Level Status Message: 47 bytes ------ */

/* The Market-Wide Circuit Breaker Decline Level Status message is used to report the calculated Level 1, Level 2 and Level 3 threshold values for the current trading day necessary to trigger a circuit breaker */
typedef struct {
  uint8_t participant_id;                      /* byte 0 */
  ParticipantTimestamp participant_timestamp;  /* bytes 1 to 8 */
  uint8_t message_id;                          /* byte 9 */
  uint8_t transaction_id[4];                   /* bytes 10 to 13 */
  uint8_t participant_reference_number[8];     /* bytes 14 to 21 */
  uint8_t mwcb_level_1[8];                     /* bytes 22 to 29 */
  uint8_t mwcb_level_2[8];                     /* bytes 30 to 37 */
  uint8_t mwcb_level_3[8];                     /* bytes 38 to 45 */
  uint8_t reserved;                            /* byte 46 */
} MarketWideCircuitBreakerDeclineLevelStatusMessage;

/* any Market Wide Circuit Breaker Decline Level Status Message at all: every byte one the checker chooses */
static void any_market_wide_circuit_breaker_decline_level_status_message(MarketWideCircuitBreakerDeclineLevelStatusMessage *record) {
  record->participant_id = arbitrary();
  any_participant_timestamp(&record->participant_timestamp);
  record->message_id = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->transaction_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->participant_reference_number[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->mwcb_level_1[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->mwcb_level_2[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->mwcb_level_3[i] = arbitrary(); }
  record->reserved = arbitrary();
}

/* Market Wide Circuit Breaker Decline Level Status Message to the wire: 47 bytes from at, returning where the next byte goes */
static size_t encode_market_wide_circuit_breaker_decline_level_status_message(const MarketWideCircuitBreakerDeclineLevelStatusMessage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->participant_id;
  at = encode_participant_timestamp(&record->participant_timestamp, wire, at);
  wire[at++] = record->message_id;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->transaction_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->participant_reference_number[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->mwcb_level_1[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->mwcb_level_2[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->mwcb_level_3[i]; }
  wire[at++] = record->reserved;

  return at;
}

/* Market Wide Circuit Breaker Decline Level Status Message off the wire: 47 bytes from at, returning where the next byte lies */
static size_t decode_market_wide_circuit_breaker_decline_level_status_message(MarketWideCircuitBreakerDeclineLevelStatusMessage *record, const uint8_t *wire, size_t at) {
  record->participant_id = wire[at++];
  at = decode_participant_timestamp(&record->participant_timestamp, wire, at);
  record->message_id = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->transaction_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->participant_reference_number[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->mwcb_level_1[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->mwcb_level_2[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->mwcb_level_3[i] = wire[at++]; }
  record->reserved = wire[at++];

  return at;
}

/* what was read of Market Wide Circuit Breaker Decline Level Status Message is what was written, byte for byte */
static void equal_market_wide_circuit_breaker_decline_level_status_message(const MarketWideCircuitBreakerDeclineLevelStatusMessage *read, const MarketWideCircuitBreakerDeclineLevelStatusMessage *written) {
  assert(read->participant_id == written->participant_id);
  equal_participant_timestamp(&read->participant_timestamp, &written->participant_timestamp);
  assert(read->message_id == written->message_id);
  for (size_t i = 0; i < 4; i++) { assert(read->transaction_id[i] == written->transaction_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->participant_reference_number[i] == written->participant_reference_number[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->mwcb_level_1[i] == written->mwcb_level_1[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->mwcb_level_2[i] == written->mwcb_level_2[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->mwcb_level_3[i] == written->mwcb_level_3[i]); }
  assert(read->reserved == written->reserved);
}

/* Market Wide Circuit Breaker Decline Level Status Message: written and read back, then read and written back */
static void check_market_wide_circuit_breaker_decline_level_status_message(void) {
  MarketWideCircuitBreakerDeclineLevelStatusMessage sent;
  MarketWideCircuitBreakerDeclineLevelStatusMessage got;
  uint8_t wire[47];
  uint8_t again[47];

  any_market_wide_circuit_breaker_decline_level_status_message(&sent);
  assert(encode_market_wide_circuit_breaker_decline_level_status_message(&sent, wire, 0) == 47);
  assert(decode_market_wide_circuit_breaker_decline_level_status_message(&got, wire, 0) == 47);
  equal_market_wide_circuit_breaker_decline_level_status_message(&got, &sent);

  for (size_t i = 0; i < 47; i++) { wire[i] = arbitrary(); }
  assert(decode_market_wide_circuit_breaker_decline_level_status_message(&got, wire, 0) == 47);
  assert(encode_market_wide_circuit_breaker_decline_level_status_message(&got, again, 0) == 47);
  for (size_t i = 0; i < 47; i++) { assert(again[i] == wire[i]); }
}

/* ---- Market Wide Circuit Breaker Status Message: 24 bytes -------------------- */

/* The Market-Wide Circuit Breaker Status message is used to report the Market-Wide Circuit Breaker threshold Level that has been breached. */
typedef struct {
  uint8_t participant_id;                      /* byte 0 */
  ParticipantTimestamp participant_timestamp;  /* bytes 1 to 8 */
  uint8_t message_id;                          /* byte 9 */
  uint8_t transaction_id[4];                   /* bytes 10 to 13 */
  uint8_t participant_reference_number[8];     /* bytes 14 to 21 */
  uint8_t mwcb_level_indicator;                /* byte 22 */
  uint8_t reserved;                            /* byte 23 */
} MarketWideCircuitBreakerStatusMessage;

/* any Market Wide Circuit Breaker Status Message at all: every byte one the checker chooses */
static void any_market_wide_circuit_breaker_status_message(MarketWideCircuitBreakerStatusMessage *record) {
  record->participant_id = arbitrary();
  any_participant_timestamp(&record->participant_timestamp);
  record->message_id = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->transaction_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->participant_reference_number[i] = arbitrary(); }
  record->mwcb_level_indicator = arbitrary();
  record->reserved = arbitrary();
}

/* Market Wide Circuit Breaker Status Message to the wire: 24 bytes from at, returning where the next byte goes */
static size_t encode_market_wide_circuit_breaker_status_message(const MarketWideCircuitBreakerStatusMessage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->participant_id;
  at = encode_participant_timestamp(&record->participant_timestamp, wire, at);
  wire[at++] = record->message_id;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->transaction_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->participant_reference_number[i]; }
  wire[at++] = record->mwcb_level_indicator;
  wire[at++] = record->reserved;

  return at;
}

/* Market Wide Circuit Breaker Status Message off the wire: 24 bytes from at, returning where the next byte lies */
static size_t decode_market_wide_circuit_breaker_status_message(MarketWideCircuitBreakerStatusMessage *record, const uint8_t *wire, size_t at) {
  record->participant_id = wire[at++];
  at = decode_participant_timestamp(&record->participant_timestamp, wire, at);
  record->message_id = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->transaction_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->participant_reference_number[i] = wire[at++]; }
  record->mwcb_level_indicator = wire[at++];
  record->reserved = wire[at++];

  return at;
}

/* what was read of Market Wide Circuit Breaker Status Message is what was written, byte for byte */
static void equal_market_wide_circuit_breaker_status_message(const MarketWideCircuitBreakerStatusMessage *read, const MarketWideCircuitBreakerStatusMessage *written) {
  assert(read->participant_id == written->participant_id);
  equal_participant_timestamp(&read->participant_timestamp, &written->participant_timestamp);
  assert(read->message_id == written->message_id);
  for (size_t i = 0; i < 4; i++) { assert(read->transaction_id[i] == written->transaction_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->participant_reference_number[i] == written->participant_reference_number[i]); }
  assert(read->mwcb_level_indicator == written->mwcb_level_indicator);
  assert(read->reserved == written->reserved);
}

/* Market Wide Circuit Breaker Status Message: written and read back, then read and written back */
static void check_market_wide_circuit_breaker_status_message(void) {
  MarketWideCircuitBreakerStatusMessage sent;
  MarketWideCircuitBreakerStatusMessage got;
  uint8_t wire[24];
  uint8_t again[24];

  any_market_wide_circuit_breaker_status_message(&sent);
  assert(encode_market_wide_circuit_breaker_status_message(&sent, wire, 0) == 24);
  assert(decode_market_wide_circuit_breaker_status_message(&got, wire, 0) == 24);
  equal_market_wide_circuit_breaker_status_message(&got, &sent);

  for (size_t i = 0; i < 24; i++) { wire[i] = arbitrary(); }
  assert(decode_market_wide_circuit_breaker_status_message(&got, wire, 0) == 24);
  assert(encode_market_wide_circuit_breaker_status_message(&got, again, 0) == 24);
  for (size_t i = 0; i < 24; i++) { assert(again[i] == wire[i]); }
}

/* ---- Auction Status Message: 63 bytes ---------------------------------------- */

/* The Auction Status message is used when a Participant in a Cta eligible security */
typedef struct {
  uint8_t participant_id;                           /* byte 0 */
  ParticipantTimestamp participant_timestamp;       /* bytes 1 to 8 */
  uint8_t message_id;                               /* byte 9 */
  uint8_t transaction_id[4];                        /* bytes 10 to 13 */
  uint8_t participant_reference_number[8];          /* bytes 14 to 21 */
  uint8_t security_symbol_long[11];                 /* bytes 22 to 32 */
  uint8_t instrument_type;                          /* byte 33 */
  uint8_t auction_collar_reference_price[8];        /* bytes 34 to 41 */
  uint8_t auction_collar_upper_threshold_price[8];  /* bytes 42 to 49 */
  uint8_t auction_collar_lower_threshold_price[8];  /* bytes 50 to 57 */
  uint8_t number_of_extensions;                     /* byte 58 */
  uint8_t short_sale_restriction_indicator;         /* byte 59 */
  uint8_t primary_listing_market_participant_id;    /* byte 60 */
  uint8_t financial_status_indicator;               /* byte 61 */
  uint8_t future;                                   /* byte 62 */
} AuctionStatusMessage;

/* any Auction Status Message at all: every byte one the checker chooses */
static void any_auction_status_message(AuctionStatusMessage *record) {
  record->participant_id = arbitrary();
  any_participant_timestamp(&record->participant_timestamp);
  record->message_id = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->transaction_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->participant_reference_number[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->security_symbol_long[i] = arbitrary(); }
  record->instrument_type = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->auction_collar_reference_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->auction_collar_upper_threshold_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->auction_collar_lower_threshold_price[i] = arbitrary(); }
  record->number_of_extensions = arbitrary();
  record->short_sale_restriction_indicator = arbitrary();
  record->primary_listing_market_participant_id = arbitrary();
  record->financial_status_indicator = arbitrary();
  record->future = arbitrary();
}

/* Auction Status Message to the wire: 63 bytes from at, returning where the next byte goes */
static size_t encode_auction_status_message(const AuctionStatusMessage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->participant_id;
  at = encode_participant_timestamp(&record->participant_timestamp, wire, at);
  wire[at++] = record->message_id;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->transaction_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->participant_reference_number[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->security_symbol_long[i]; }
  wire[at++] = record->instrument_type;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->auction_collar_reference_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->auction_collar_upper_threshold_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->auction_collar_lower_threshold_price[i]; }
  wire[at++] = record->number_of_extensions;
  wire[at++] = record->short_sale_restriction_indicator;
  wire[at++] = record->primary_listing_market_participant_id;
  wire[at++] = record->financial_status_indicator;
  wire[at++] = record->future;

  return at;
}

/* Auction Status Message off the wire: 63 bytes from at, returning where the next byte lies */
static size_t decode_auction_status_message(AuctionStatusMessage *record, const uint8_t *wire, size_t at) {
  record->participant_id = wire[at++];
  at = decode_participant_timestamp(&record->participant_timestamp, wire, at);
  record->message_id = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->transaction_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->participant_reference_number[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->security_symbol_long[i] = wire[at++]; }
  record->instrument_type = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->auction_collar_reference_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->auction_collar_upper_threshold_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->auction_collar_lower_threshold_price[i] = wire[at++]; }
  record->number_of_extensions = wire[at++];
  record->short_sale_restriction_indicator = wire[at++];
  record->primary_listing_market_participant_id = wire[at++];
  record->financial_status_indicator = wire[at++];
  record->future = wire[at++];

  return at;
}

/* what was read of Auction Status Message is what was written, byte for byte */
static void equal_auction_status_message(const AuctionStatusMessage *read, const AuctionStatusMessage *written) {
  assert(read->participant_id == written->participant_id);
  equal_participant_timestamp(&read->participant_timestamp, &written->participant_timestamp);
  assert(read->message_id == written->message_id);
  for (size_t i = 0; i < 4; i++) { assert(read->transaction_id[i] == written->transaction_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->participant_reference_number[i] == written->participant_reference_number[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->security_symbol_long[i] == written->security_symbol_long[i]); }
  assert(read->instrument_type == written->instrument_type);
  for (size_t i = 0; i < 8; i++) { assert(read->auction_collar_reference_price[i] == written->auction_collar_reference_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->auction_collar_upper_threshold_price[i] == written->auction_collar_upper_threshold_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->auction_collar_lower_threshold_price[i] == written->auction_collar_lower_threshold_price[i]); }
  assert(read->number_of_extensions == written->number_of_extensions);
  assert(read->short_sale_restriction_indicator == written->short_sale_restriction_indicator);
  assert(read->primary_listing_market_participant_id == written->primary_listing_market_participant_id);
  assert(read->financial_status_indicator == written->financial_status_indicator);
  assert(read->future == written->future);
}

/* Auction Status Message: written and read back, then read and written back */
static void check_auction_status_message(void) {
  AuctionStatusMessage sent;
  AuctionStatusMessage got;
  uint8_t wire[63];
  uint8_t again[63];

  any_auction_status_message(&sent);
  assert(encode_auction_status_message(&sent, wire, 0) == 63);
  assert(decode_auction_status_message(&got, wire, 0) == 63);
  equal_auction_status_message(&got, &sent);

  for (size_t i = 0; i < 63; i++) { wire[i] = arbitrary(); }
  assert(decode_auction_status_message(&got, wire, 0) == 63);
  assert(encode_auction_status_message(&got, again, 0) == 63);
  for (size_t i = 0; i < 63; i++) { assert(again[i] == wire[i]); }
}

/* ---- Adf Timestamp: 8 bytes -------------------------------------------------- */

/* Adf Timestamp */
typedef struct {
  uint8_t seconds[4];      /* bytes 0 to 3 */
  uint8_t nanoseconds[4];  /* bytes 4 to 7 */
} AdfTimestamp;

/* any Adf Timestamp at all: every byte one the checker chooses */
static void any_adf_timestamp(AdfTimestamp *record) {
  for (size_t i = 0; i < 4; i++) { record->seconds[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = arbitrary(); }
}

/* Adf Timestamp to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_adf_timestamp(const AdfTimestamp *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->seconds[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->nanoseconds[i]; }

  return at;
}

/* Adf Timestamp off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_adf_timestamp(AdfTimestamp *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->seconds[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = wire[at++]; }

  return at;
}

/* what was read of Adf Timestamp is what was written, byte for byte */
static void equal_adf_timestamp(const AdfTimestamp *read, const AdfTimestamp *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->seconds[i] == written->seconds[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->nanoseconds[i] == written->nanoseconds[i]); }
}

/* Adf Timestamp: written and read back, then read and written back */
static void check_adf_timestamp(void) {
  AdfTimestamp sent;
  AdfTimestamp got;
  uint8_t wire[8];
  uint8_t again[8];

  any_adf_timestamp(&sent);
  assert(encode_adf_timestamp(&sent, wire, 0) == 8);
  assert(decode_adf_timestamp(&got, wire, 0) == 8);
  equal_adf_timestamp(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_adf_timestamp(&got, wire, 0) == 8);
  assert(encode_adf_timestamp(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- What esbmc checks ------------------------------------------------------- */

/* every record of the protocol, each on its own buffers */
static void checks(void) {
  check_sip_block_timestamp();
  check_block_header();
  check_participant_timestamp();
  check_start_of_day_message();
  check_finra_close_message();
  check_reset_block_sequence_number_message();
  check_finra_open_message();
  check_disaster_recovery_data_center_activation_message();
  check_line_integrity_message();
  check_end_of_day_message();
  check_market_wide_circuit_breaker_decline_level_status_message();
  check_market_wide_circuit_breaker_status_message();
  check_auction_status_message();
  check_adf_timestamp();
}

int main(void) {
#ifdef CONCRETE
  for (pattern = 0; pattern < 4; pattern++) { checks(); }
#else
  checks();
#endif

  return 0;
}
