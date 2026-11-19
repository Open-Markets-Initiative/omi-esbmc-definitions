// siac/cts/output/Siac_Cts_Output_v2_10.c
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
 *   - a Checksum rule
 *   - a run counted by a field
 *   - the dispatch that chooses a message by its type
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

/* ---- Timestamp 1: 8 bytes ---------------------------------------------------- */

/* Timestamp 1 */
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

/* ---- Start Of End Of Day Summary Message: 22 bytes --------------------------- */

/* The Start of End of Day message signals the start of Consolidated End of Day Summary and Participant End of Day Summary message iterations */
typedef struct {
  uint8_t participant_id;                   /* byte 0 */
  Timestamp1 timestamp_1;                   /* bytes 1 to 8 */
  uint8_t message_id;                       /* byte 9 */
  uint8_t transaction_id[4];                /* bytes 10 to 13 */
  uint8_t participant_reference_number[8];  /* bytes 14 to 21 */
} StartOfEndOfDaySummaryMessage;

/* any Start Of End Of Day Summary Message at all: every byte one the checker chooses */
static void any_start_of_end_of_day_summary_message(StartOfEndOfDaySummaryMessage *record) {
  record->participant_id = arbitrary();
  any_timestamp1(&record->timestamp_1);
  record->message_id = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->transaction_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->participant_reference_number[i] = arbitrary(); }
}

/* Start Of End Of Day Summary Message to the wire: 22 bytes from at, returning where the next byte goes */
static size_t encode_start_of_end_of_day_summary_message(const StartOfEndOfDaySummaryMessage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->participant_id;
  at = encode_timestamp1(&record->timestamp_1, wire, at);
  wire[at++] = record->message_id;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->transaction_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->participant_reference_number[i]; }

  return at;
}

/* Start Of End Of Day Summary Message off the wire: 22 bytes from at, returning where the next byte lies */
static size_t decode_start_of_end_of_day_summary_message(StartOfEndOfDaySummaryMessage *record, const uint8_t *wire, size_t at) {
  record->participant_id = wire[at++];
  at = decode_timestamp1(&record->timestamp_1, wire, at);
  record->message_id = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->transaction_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->participant_reference_number[i] = wire[at++]; }

  return at;
}

/* what was read of Start Of End Of Day Summary Message is what was written, byte for byte */
static void equal_start_of_end_of_day_summary_message(const StartOfEndOfDaySummaryMessage *read, const StartOfEndOfDaySummaryMessage *written) {
  assert(read->participant_id == written->participant_id);
  equal_timestamp1(&read->timestamp_1, &written->timestamp_1);
  assert(read->message_id == written->message_id);
  for (size_t i = 0; i < 4; i++) { assert(read->transaction_id[i] == written->transaction_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->participant_reference_number[i] == written->participant_reference_number[i]); }
}

/* Start Of End Of Day Summary Message: written and read back, then read and written back */
static void check_start_of_end_of_day_summary_message(void) {
  StartOfEndOfDaySummaryMessage sent;
  StartOfEndOfDaySummaryMessage got;
  uint8_t wire[22];
  uint8_t again[22];

  any_start_of_end_of_day_summary_message(&sent);
  assert(encode_start_of_end_of_day_summary_message(&sent, wire, 0) == 22);
  assert(decode_start_of_end_of_day_summary_message(&got, wire, 0) == 22);
  equal_start_of_end_of_day_summary_message(&got, &sent);

  for (size_t i = 0; i < 22; i++) { wire[i] = arbitrary(); }
  assert(decode_start_of_end_of_day_summary_message(&got, wire, 0) == 22);
  assert(encode_start_of_end_of_day_summary_message(&got, again, 0) == 22);
  for (size_t i = 0; i < 22; i++) { assert(again[i] == wire[i]); }
}

/* ---- End Of End Of Day Summary Message: 22 bytes ----------------------------- */

/* The End of End of Day message signals the end of Consolidated End of Day Summary and Participant End of Day Summary message iterations */
typedef struct {
  uint8_t participant_id;                   /* byte 0 */
  Timestamp1 timestamp_1;                   /* bytes 1 to 8 */
  uint8_t message_id;                       /* byte 9 */
  uint8_t transaction_id[4];                /* bytes 10 to 13 */
  uint8_t participant_reference_number[8];  /* bytes 14 to 21 */
} EndOfEndOfDaySummaryMessage;

/* any End Of End Of Day Summary Message at all: every byte one the checker chooses */
static void any_end_of_end_of_day_summary_message(EndOfEndOfDaySummaryMessage *record) {
  record->participant_id = arbitrary();
  any_timestamp1(&record->timestamp_1);
  record->message_id = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->transaction_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->participant_reference_number[i] = arbitrary(); }
}

/* End Of End Of Day Summary Message to the wire: 22 bytes from at, returning where the next byte goes */
static size_t encode_end_of_end_of_day_summary_message(const EndOfEndOfDaySummaryMessage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->participant_id;
  at = encode_timestamp1(&record->timestamp_1, wire, at);
  wire[at++] = record->message_id;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->transaction_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->participant_reference_number[i]; }

  return at;
}

/* End Of End Of Day Summary Message off the wire: 22 bytes from at, returning where the next byte lies */
static size_t decode_end_of_end_of_day_summary_message(EndOfEndOfDaySummaryMessage *record, const uint8_t *wire, size_t at) {
  record->participant_id = wire[at++];
  at = decode_timestamp1(&record->timestamp_1, wire, at);
  record->message_id = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->transaction_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->participant_reference_number[i] = wire[at++]; }

  return at;
}

/* what was read of End Of End Of Day Summary Message is what was written, byte for byte */
static void equal_end_of_end_of_day_summary_message(const EndOfEndOfDaySummaryMessage *read, const EndOfEndOfDaySummaryMessage *written) {
  assert(read->participant_id == written->participant_id);
  equal_timestamp1(&read->timestamp_1, &written->timestamp_1);
  assert(read->message_id == written->message_id);
  for (size_t i = 0; i < 4; i++) { assert(read->transaction_id[i] == written->transaction_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->participant_reference_number[i] == written->participant_reference_number[i]); }
}

/* End Of End Of Day Summary Message: written and read back, then read and written back */
static void check_end_of_end_of_day_summary_message(void) {
  EndOfEndOfDaySummaryMessage sent;
  EndOfEndOfDaySummaryMessage got;
  uint8_t wire[22];
  uint8_t again[22];

  any_end_of_end_of_day_summary_message(&sent);
  assert(encode_end_of_end_of_day_summary_message(&sent, wire, 0) == 22);
  assert(decode_end_of_end_of_day_summary_message(&got, wire, 0) == 22);
  equal_end_of_end_of_day_summary_message(&got, &sent);

  for (size_t i = 0; i < 22; i++) { wire[i] = arbitrary(); }
  assert(decode_end_of_end_of_day_summary_message(&got, wire, 0) == 22);
  assert(encode_end_of_end_of_day_summary_message(&got, again, 0) == 22);
  for (size_t i = 0; i < 22; i++) { assert(again[i] == wire[i]); }
}

/* ---- Start Of Start Of Day Summary Message: 22 bytes ------------------------- */

/* The Start of Start of Day message signals the end of Consolidated End of Day Summary and Participant End of Day Summary message iterations */
typedef struct {
  uint8_t participant_id;                   /* byte 0 */
  Timestamp1 timestamp_1;                   /* bytes 1 to 8 */
  uint8_t message_id;                       /* byte 9 */
  uint8_t transaction_id[4];                /* bytes 10 to 13 */
  uint8_t participant_reference_number[8];  /* bytes 14 to 21 */
} StartOfStartOfDaySummaryMessage;

/* any Start Of Start Of Day Summary Message at all: every byte one the checker chooses */
static void any_start_of_start_of_day_summary_message(StartOfStartOfDaySummaryMessage *record) {
  record->participant_id = arbitrary();
  any_timestamp1(&record->timestamp_1);
  record->message_id = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->transaction_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->participant_reference_number[i] = arbitrary(); }
}

/* Start Of Start Of Day Summary Message to the wire: 22 bytes from at, returning where the next byte goes */
static size_t encode_start_of_start_of_day_summary_message(const StartOfStartOfDaySummaryMessage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->participant_id;
  at = encode_timestamp1(&record->timestamp_1, wire, at);
  wire[at++] = record->message_id;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->transaction_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->participant_reference_number[i]; }

  return at;
}

/* Start Of Start Of Day Summary Message off the wire: 22 bytes from at, returning where the next byte lies */
static size_t decode_start_of_start_of_day_summary_message(StartOfStartOfDaySummaryMessage *record, const uint8_t *wire, size_t at) {
  record->participant_id = wire[at++];
  at = decode_timestamp1(&record->timestamp_1, wire, at);
  record->message_id = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->transaction_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->participant_reference_number[i] = wire[at++]; }

  return at;
}

/* what was read of Start Of Start Of Day Summary Message is what was written, byte for byte */
static void equal_start_of_start_of_day_summary_message(const StartOfStartOfDaySummaryMessage *read, const StartOfStartOfDaySummaryMessage *written) {
  assert(read->participant_id == written->participant_id);
  equal_timestamp1(&read->timestamp_1, &written->timestamp_1);
  assert(read->message_id == written->message_id);
  for (size_t i = 0; i < 4; i++) { assert(read->transaction_id[i] == written->transaction_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->participant_reference_number[i] == written->participant_reference_number[i]); }
}

/* Start Of Start Of Day Summary Message: written and read back, then read and written back */
static void check_start_of_start_of_day_summary_message(void) {
  StartOfStartOfDaySummaryMessage sent;
  StartOfStartOfDaySummaryMessage got;
  uint8_t wire[22];
  uint8_t again[22];

  any_start_of_start_of_day_summary_message(&sent);
  assert(encode_start_of_start_of_day_summary_message(&sent, wire, 0) == 22);
  assert(decode_start_of_start_of_day_summary_message(&got, wire, 0) == 22);
  equal_start_of_start_of_day_summary_message(&got, &sent);

  for (size_t i = 0; i < 22; i++) { wire[i] = arbitrary(); }
  assert(decode_start_of_start_of_day_summary_message(&got, wire, 0) == 22);
  assert(encode_start_of_start_of_day_summary_message(&got, again, 0) == 22);
  for (size_t i = 0; i < 22; i++) { assert(again[i] == wire[i]); }
}

/* ---- End Of Start Of Day Summary Message: 22 bytes --------------------------- */

/* The End of Start of Day message signals the start of Start of Day Summary message iterations */
typedef struct {
  uint8_t participant_id;                   /* byte 0 */
  Timestamp1 timestamp_1;                   /* bytes 1 to 8 */
  uint8_t message_id;                       /* byte 9 */
  uint8_t transaction_id[4];                /* bytes 10 to 13 */
  uint8_t participant_reference_number[8];  /* bytes 14 to 21 */
} EndOfStartOfDaySummaryMessage;

/* any End Of Start Of Day Summary Message at all: every byte one the checker chooses */
static void any_end_of_start_of_day_summary_message(EndOfStartOfDaySummaryMessage *record) {
  record->participant_id = arbitrary();
  any_timestamp1(&record->timestamp_1);
  record->message_id = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->transaction_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->participant_reference_number[i] = arbitrary(); }
}

/* End Of Start Of Day Summary Message to the wire: 22 bytes from at, returning where the next byte goes */
static size_t encode_end_of_start_of_day_summary_message(const EndOfStartOfDaySummaryMessage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->participant_id;
  at = encode_timestamp1(&record->timestamp_1, wire, at);
  wire[at++] = record->message_id;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->transaction_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->participant_reference_number[i]; }

  return at;
}

/* End Of Start Of Day Summary Message off the wire: 22 bytes from at, returning where the next byte lies */
static size_t decode_end_of_start_of_day_summary_message(EndOfStartOfDaySummaryMessage *record, const uint8_t *wire, size_t at) {
  record->participant_id = wire[at++];
  at = decode_timestamp1(&record->timestamp_1, wire, at);
  record->message_id = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->transaction_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->participant_reference_number[i] = wire[at++]; }

  return at;
}

/* what was read of End Of Start Of Day Summary Message is what was written, byte for byte */
static void equal_end_of_start_of_day_summary_message(const EndOfStartOfDaySummaryMessage *read, const EndOfStartOfDaySummaryMessage *written) {
  assert(read->participant_id == written->participant_id);
  equal_timestamp1(&read->timestamp_1, &written->timestamp_1);
  assert(read->message_id == written->message_id);
  for (size_t i = 0; i < 4; i++) { assert(read->transaction_id[i] == written->transaction_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->participant_reference_number[i] == written->participant_reference_number[i]); }
}

/* End Of Start Of Day Summary Message: written and read back, then read and written back */
static void check_end_of_start_of_day_summary_message(void) {
  EndOfStartOfDaySummaryMessage sent;
  EndOfStartOfDaySummaryMessage got;
  uint8_t wire[22];
  uint8_t again[22];

  any_end_of_start_of_day_summary_message(&sent);
  assert(encode_end_of_start_of_day_summary_message(&sent, wire, 0) == 22);
  assert(decode_end_of_start_of_day_summary_message(&got, wire, 0) == 22);
  equal_end_of_start_of_day_summary_message(&got, &sent);

  for (size_t i = 0; i < 22; i++) { wire[i] = arbitrary(); }
  assert(decode_end_of_start_of_day_summary_message(&got, wire, 0) == 22);
  assert(encode_end_of_start_of_day_summary_message(&got, again, 0) == 22);
  for (size_t i = 0; i < 22; i++) { assert(again[i] == wire[i]); }
}

/* ---- Start Of Day Message: 22 bytes ------------------------------------------ */

/* The Start of Day message signals the start of normal data dissemination over the multicast lines */
typedef struct {
  uint8_t participant_id;                   /* byte 0 */
  Timestamp1 timestamp_1;                   /* bytes 1 to 8 */
  uint8_t message_id;                       /* byte 9 */
  uint8_t transaction_id[4];                /* bytes 10 to 13 */
  uint8_t participant_reference_number[8];  /* bytes 14 to 21 */
} StartOfDayMessage;

/* any Start Of Day Message at all: every byte one the checker chooses */
static void any_start_of_day_message(StartOfDayMessage *record) {
  record->participant_id = arbitrary();
  any_timestamp1(&record->timestamp_1);
  record->message_id = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->transaction_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->participant_reference_number[i] = arbitrary(); }
}

/* Start Of Day Message to the wire: 22 bytes from at, returning where the next byte goes */
static size_t encode_start_of_day_message(const StartOfDayMessage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->participant_id;
  at = encode_timestamp1(&record->timestamp_1, wire, at);
  wire[at++] = record->message_id;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->transaction_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->participant_reference_number[i]; }

  return at;
}

/* Start Of Day Message off the wire: 22 bytes from at, returning where the next byte lies */
static size_t decode_start_of_day_message(StartOfDayMessage *record, const uint8_t *wire, size_t at) {
  record->participant_id = wire[at++];
  at = decode_timestamp1(&record->timestamp_1, wire, at);
  record->message_id = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->transaction_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->participant_reference_number[i] = wire[at++]; }

  return at;
}

/* what was read of Start Of Day Message is what was written, byte for byte */
static void equal_start_of_day_message(const StartOfDayMessage *read, const StartOfDayMessage *written) {
  assert(read->participant_id == written->participant_id);
  equal_timestamp1(&read->timestamp_1, &written->timestamp_1);
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

/* ---- Reset Block Sequence Number Message: 22 bytes --------------------------- */

/* The Reset Block Sequence Number message is transmitted when the block sequence number on an output multicast line requires resetting. */
typedef struct {
  uint8_t participant_id;                   /* byte 0 */
  Timestamp1 timestamp_1;                   /* bytes 1 to 8 */
  uint8_t message_id;                       /* byte 9 */
  uint8_t transaction_id[4];                /* bytes 10 to 13 */
  uint8_t participant_reference_number[8];  /* bytes 14 to 21 */
} ResetBlockSequenceNumberMessage;

/* any Reset Block Sequence Number Message at all: every byte one the checker chooses */
static void any_reset_block_sequence_number_message(ResetBlockSequenceNumberMessage *record) {
  record->participant_id = arbitrary();
  any_timestamp1(&record->timestamp_1);
  record->message_id = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->transaction_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->participant_reference_number[i] = arbitrary(); }
}

/* Reset Block Sequence Number Message to the wire: 22 bytes from at, returning where the next byte goes */
static size_t encode_reset_block_sequence_number_message(const ResetBlockSequenceNumberMessage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->participant_id;
  at = encode_timestamp1(&record->timestamp_1, wire, at);
  wire[at++] = record->message_id;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->transaction_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->participant_reference_number[i]; }

  return at;
}

/* Reset Block Sequence Number Message off the wire: 22 bytes from at, returning where the next byte lies */
static size_t decode_reset_block_sequence_number_message(ResetBlockSequenceNumberMessage *record, const uint8_t *wire, size_t at) {
  record->participant_id = wire[at++];
  at = decode_timestamp1(&record->timestamp_1, wire, at);
  record->message_id = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->transaction_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->participant_reference_number[i] = wire[at++]; }

  return at;
}

/* what was read of Reset Block Sequence Number Message is what was written, byte for byte */
static void equal_reset_block_sequence_number_message(const ResetBlockSequenceNumberMessage *read, const ResetBlockSequenceNumberMessage *written) {
  assert(read->participant_id == written->participant_id);
  equal_timestamp1(&read->timestamp_1, &written->timestamp_1);
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

/* ---- Disaster Recovery Data Center Activation Message: 22 bytes -------------- */

/* The Disaster Recovery Data Center Activation message is transmitted to signify that the Consolidated Quotation System (CQS) has switched processing from the Primary Data Center to the Disaster Recovery Data Center */
typedef struct {
  uint8_t participant_id;                   /* byte 0 */
  Timestamp1 timestamp_1;                   /* bytes 1 to 8 */
  uint8_t message_id;                       /* byte 9 */
  uint8_t transaction_id[4];                /* bytes 10 to 13 */
  uint8_t participant_reference_number[8];  /* bytes 14 to 21 */
} DisasterRecoveryDataCenterActivationMessage;

/* any Disaster Recovery Data Center Activation Message at all: every byte one the checker chooses */
static void any_disaster_recovery_data_center_activation_message(DisasterRecoveryDataCenterActivationMessage *record) {
  record->participant_id = arbitrary();
  any_timestamp1(&record->timestamp_1);
  record->message_id = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->transaction_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->participant_reference_number[i] = arbitrary(); }
}

/* Disaster Recovery Data Center Activation Message to the wire: 22 bytes from at, returning where the next byte goes */
static size_t encode_disaster_recovery_data_center_activation_message(const DisasterRecoveryDataCenterActivationMessage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->participant_id;
  at = encode_timestamp1(&record->timestamp_1, wire, at);
  wire[at++] = record->message_id;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->transaction_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->participant_reference_number[i]; }

  return at;
}

/* Disaster Recovery Data Center Activation Message off the wire: 22 bytes from at, returning where the next byte lies */
static size_t decode_disaster_recovery_data_center_activation_message(DisasterRecoveryDataCenterActivationMessage *record, const uint8_t *wire, size_t at) {
  record->participant_id = wire[at++];
  at = decode_timestamp1(&record->timestamp_1, wire, at);
  record->message_id = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->transaction_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->participant_reference_number[i] = wire[at++]; }

  return at;
}

/* what was read of Disaster Recovery Data Center Activation Message is what was written, byte for byte */
static void equal_disaster_recovery_data_center_activation_message(const DisasterRecoveryDataCenterActivationMessage *read, const DisasterRecoveryDataCenterActivationMessage *written) {
  assert(read->participant_id == written->participant_id);
  equal_timestamp1(&read->timestamp_1, &written->timestamp_1);
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
  uint8_t participant_id;                   /* byte 0 */
  Timestamp1 timestamp_1;                   /* bytes 1 to 8 */
  uint8_t message_id;                       /* byte 9 */
  uint8_t transaction_id[4];                /* bytes 10 to 13 */
  uint8_t participant_reference_number[8];  /* bytes 14 to 21 */
} LineIntegrityMessage;

/* any Line Integrity Message at all: every byte one the checker chooses */
static void any_line_integrity_message(LineIntegrityMessage *record) {
  record->participant_id = arbitrary();
  any_timestamp1(&record->timestamp_1);
  record->message_id = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->transaction_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->participant_reference_number[i] = arbitrary(); }
}

/* Line Integrity Message to the wire: 22 bytes from at, returning where the next byte goes */
static size_t encode_line_integrity_message(const LineIntegrityMessage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->participant_id;
  at = encode_timestamp1(&record->timestamp_1, wire, at);
  wire[at++] = record->message_id;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->transaction_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->participant_reference_number[i]; }

  return at;
}

/* Line Integrity Message off the wire: 22 bytes from at, returning where the next byte lies */
static size_t decode_line_integrity_message(LineIntegrityMessage *record, const uint8_t *wire, size_t at) {
  record->participant_id = wire[at++];
  at = decode_timestamp1(&record->timestamp_1, wire, at);
  record->message_id = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->transaction_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->participant_reference_number[i] = wire[at++]; }

  return at;
}

/* what was read of Line Integrity Message is what was written, byte for byte */
static void equal_line_integrity_message(const LineIntegrityMessage *read, const LineIntegrityMessage *written) {
  assert(read->participant_id == written->participant_id);
  equal_timestamp1(&read->timestamp_1, &written->timestamp_1);
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
  uint8_t participant_id;                   /* byte 0 */
  Timestamp1 timestamp_1;                   /* bytes 1 to 8 */
  uint8_t message_id;                       /* byte 9 */
  uint8_t transaction_id[4];                /* bytes 10 to 13 */
  uint8_t participant_reference_number[8];  /* bytes 14 to 21 */
} EndOfDayMessage;

/* any End Of Day Message at all: every byte one the checker chooses */
static void any_end_of_day_message(EndOfDayMessage *record) {
  record->participant_id = arbitrary();
  any_timestamp1(&record->timestamp_1);
  record->message_id = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->transaction_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->participant_reference_number[i] = arbitrary(); }
}

/* End Of Day Message to the wire: 22 bytes from at, returning where the next byte goes */
static size_t encode_end_of_day_message(const EndOfDayMessage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->participant_id;
  at = encode_timestamp1(&record->timestamp_1, wire, at);
  wire[at++] = record->message_id;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->transaction_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->participant_reference_number[i]; }

  return at;
}

/* End Of Day Message off the wire: 22 bytes from at, returning where the next byte lies */
static size_t decode_end_of_day_message(EndOfDayMessage *record, const uint8_t *wire, size_t at) {
  record->participant_id = wire[at++];
  at = decode_timestamp1(&record->timestamp_1, wire, at);
  record->message_id = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->transaction_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->participant_reference_number[i] = wire[at++]; }

  return at;
}

/* what was read of End Of Day Message is what was written, byte for byte */
static void equal_end_of_day_message(const EndOfDayMessage *read, const EndOfDayMessage *written) {
  assert(read->participant_id == written->participant_id);
  equal_timestamp1(&read->timestamp_1, &written->timestamp_1);
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

/* ---- Index Message: 41 bytes ------------------------------------------------- */

/* The Index message contains the index and the index value */
typedef struct {
  uint8_t participant_id;                   /* byte 0 */
  Timestamp1 timestamp_1;                   /* bytes 1 to 8 */
  uint8_t message_id;                       /* byte 9 */
  uint8_t transaction_id[4];                /* bytes 10 to 13 */
  uint8_t participant_reference_number[8];  /* bytes 14 to 21 */
  uint8_t index_symbol[11];                 /* bytes 22 to 32 */
  uint8_t index_value[8];                   /* bytes 33 to 40 */
} IndexMessage;

/* any Index Message at all: every byte one the checker chooses */
static void any_index_message(IndexMessage *record) {
  record->participant_id = arbitrary();
  any_timestamp1(&record->timestamp_1);
  record->message_id = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->transaction_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->participant_reference_number[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->index_symbol[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->index_value[i] = arbitrary(); }
}

/* Index Message to the wire: 41 bytes from at, returning where the next byte goes */
static size_t encode_index_message(const IndexMessage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->participant_id;
  at = encode_timestamp1(&record->timestamp_1, wire, at);
  wire[at++] = record->message_id;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->transaction_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->participant_reference_number[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->index_symbol[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->index_value[i]; }

  return at;
}

/* Index Message off the wire: 41 bytes from at, returning where the next byte lies */
static size_t decode_index_message(IndexMessage *record, const uint8_t *wire, size_t at) {
  record->participant_id = wire[at++];
  at = decode_timestamp1(&record->timestamp_1, wire, at);
  record->message_id = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->transaction_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->participant_reference_number[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->index_symbol[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->index_value[i] = wire[at++]; }

  return at;
}

/* what was read of Index Message is what was written, byte for byte */
static void equal_index_message(const IndexMessage *read, const IndexMessage *written) {
  assert(read->participant_id == written->participant_id);
  equal_timestamp1(&read->timestamp_1, &written->timestamp_1);
  assert(read->message_id == written->message_id);
  for (size_t i = 0; i < 4; i++) { assert(read->transaction_id[i] == written->transaction_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->participant_reference_number[i] == written->participant_reference_number[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->index_symbol[i] == written->index_symbol[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->index_value[i] == written->index_value[i]); }
}

/* Index Message: written and read back, then read and written back */
static void check_index_message(void) {
  IndexMessage sent;
  IndexMessage got;
  uint8_t wire[41];
  uint8_t again[41];

  any_index_message(&sent);
  assert(encode_index_message(&sent, wire, 0) == 41);
  assert(decode_index_message(&got, wire, 0) == 41);
  equal_index_message(&got, &sent);

  for (size_t i = 0; i < 41; i++) { wire[i] = arbitrary(); }
  assert(decode_index_message(&got, wire, 0) == 41);
  assert(encode_index_message(&got, again, 0) == 41);
  for (size_t i = 0; i < 41; i++) { assert(again[i] == wire[i]); }
}

/* ---- Bid And Offer Index Message: 49 bytes ----------------------------------- */

/* The Bid and Offer Index message contains the index Bid and Offer index values */
typedef struct {
  uint8_t participant_id;                   /* byte 0 */
  Timestamp1 timestamp_1;                   /* bytes 1 to 8 */
  uint8_t message_id;                       /* byte 9 */
  uint8_t transaction_id[4];                /* bytes 10 to 13 */
  uint8_t participant_reference_number[8];  /* bytes 14 to 21 */
  uint8_t index_symbol[11];                 /* bytes 22 to 32 */
  uint8_t bid_index_value[8];               /* bytes 33 to 40 */
  uint8_t offer_index_value[8];             /* bytes 41 to 48 */
} BidAndOfferIndexMessage;

/* any Bid And Offer Index Message at all: every byte one the checker chooses */
static void any_bid_and_offer_index_message(BidAndOfferIndexMessage *record) {
  record->participant_id = arbitrary();
  any_timestamp1(&record->timestamp_1);
  record->message_id = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->transaction_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->participant_reference_number[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->index_symbol[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->bid_index_value[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->offer_index_value[i] = arbitrary(); }
}

/* Bid And Offer Index Message to the wire: 49 bytes from at, returning where the next byte goes */
static size_t encode_bid_and_offer_index_message(const BidAndOfferIndexMessage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->participant_id;
  at = encode_timestamp1(&record->timestamp_1, wire, at);
  wire[at++] = record->message_id;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->transaction_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->participant_reference_number[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->index_symbol[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->bid_index_value[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->offer_index_value[i]; }

  return at;
}

/* Bid And Offer Index Message off the wire: 49 bytes from at, returning where the next byte lies */
static size_t decode_bid_and_offer_index_message(BidAndOfferIndexMessage *record, const uint8_t *wire, size_t at) {
  record->participant_id = wire[at++];
  at = decode_timestamp1(&record->timestamp_1, wire, at);
  record->message_id = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->transaction_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->participant_reference_number[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->index_symbol[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->bid_index_value[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->offer_index_value[i] = wire[at++]; }

  return at;
}

/* what was read of Bid And Offer Index Message is what was written, byte for byte */
static void equal_bid_and_offer_index_message(const BidAndOfferIndexMessage *read, const BidAndOfferIndexMessage *written) {
  assert(read->participant_id == written->participant_id);
  equal_timestamp1(&read->timestamp_1, &written->timestamp_1);
  assert(read->message_id == written->message_id);
  for (size_t i = 0; i < 4; i++) { assert(read->transaction_id[i] == written->transaction_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->participant_reference_number[i] == written->participant_reference_number[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->index_symbol[i] == written->index_symbol[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->bid_index_value[i] == written->bid_index_value[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->offer_index_value[i] == written->offer_index_value[i]); }
}

/* Bid And Offer Index Message: written and read back, then read and written back */
static void check_bid_and_offer_index_message(void) {
  BidAndOfferIndexMessage sent;
  BidAndOfferIndexMessage got;
  uint8_t wire[49];
  uint8_t again[49];

  any_bid_and_offer_index_message(&sent);
  assert(encode_bid_and_offer_index_message(&sent, wire, 0) == 49);
  assert(decode_bid_and_offer_index_message(&got, wire, 0) == 49);
  equal_bid_and_offer_index_message(&got, &sent);

  for (size_t i = 0; i < 49; i++) { wire[i] = arbitrary(); }
  assert(decode_bid_and_offer_index_message(&got, wire, 0) == 49);
  assert(encode_bid_and_offer_index_message(&got, again, 0) == 49);
  for (size_t i = 0; i < 49; i++) { assert(again[i] == wire[i]); }
}

/* ---- Market Wide Circuit Breaker Decline Level Status Message: 47 bytes ------ */

/* The Market-Wide Circuit Breaker Decline Level Status message is used to report the calculated Level 1, Level 2 and Level 3 threshold values for the current trading day necessary to trigger a circuit breaker */
typedef struct {
  uint8_t participant_id;                   /* byte 0 */
  Timestamp1 timestamp_1;                   /* bytes 1 to 8 */
  uint8_t message_id;                       /* byte 9 */
  uint8_t transaction_id[4];                /* bytes 10 to 13 */
  uint8_t participant_reference_number[8];  /* bytes 14 to 21 */
  uint8_t mwcb_level_1[8];                  /* bytes 22 to 29 */
  uint8_t mwcb_level_2[8];                  /* bytes 30 to 37 */
  uint8_t mwcb_level_3[8];                  /* bytes 38 to 45 */
  uint8_t reserved;                         /* byte 46 */
} MarketWideCircuitBreakerDeclineLevelStatusMessage;

/* any Market Wide Circuit Breaker Decline Level Status Message at all: every byte one the checker chooses */
static void any_market_wide_circuit_breaker_decline_level_status_message(MarketWideCircuitBreakerDeclineLevelStatusMessage *record) {
  record->participant_id = arbitrary();
  any_timestamp1(&record->timestamp_1);
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
  at = encode_timestamp1(&record->timestamp_1, wire, at);
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
  at = decode_timestamp1(&record->timestamp_1, wire, at);
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
  equal_timestamp1(&read->timestamp_1, &written->timestamp_1);
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
  uint8_t participant_id;                               /* byte 0 */
  Timestamp1 timestamp_1;                               /* bytes 1 to 8 */
  uint8_t message_id;                                   /* byte 9 */
  uint8_t transaction_id[4];                            /* bytes 10 to 13 */
  uint8_t participant_reference_number[8];              /* bytes 14 to 21 */
  uint8_t market_wide_circuit_breaker_level_indicator;  /* byte 22 */
  uint8_t reserved;                                     /* byte 23 */
} MarketWideCircuitBreakerStatusMessage;

/* any Market Wide Circuit Breaker Status Message at all: every byte one the checker chooses */
static void any_market_wide_circuit_breaker_status_message(MarketWideCircuitBreakerStatusMessage *record) {
  record->participant_id = arbitrary();
  any_timestamp1(&record->timestamp_1);
  record->message_id = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->transaction_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->participant_reference_number[i] = arbitrary(); }
  record->market_wide_circuit_breaker_level_indicator = arbitrary();
  record->reserved = arbitrary();
}

/* Market Wide Circuit Breaker Status Message to the wire: 24 bytes from at, returning where the next byte goes */
static size_t encode_market_wide_circuit_breaker_status_message(const MarketWideCircuitBreakerStatusMessage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->participant_id;
  at = encode_timestamp1(&record->timestamp_1, wire, at);
  wire[at++] = record->message_id;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->transaction_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->participant_reference_number[i]; }
  wire[at++] = record->market_wide_circuit_breaker_level_indicator;
  wire[at++] = record->reserved;

  return at;
}

/* Market Wide Circuit Breaker Status Message off the wire: 24 bytes from at, returning where the next byte lies */
static size_t decode_market_wide_circuit_breaker_status_message(MarketWideCircuitBreakerStatusMessage *record, const uint8_t *wire, size_t at) {
  record->participant_id = wire[at++];
  at = decode_timestamp1(&record->timestamp_1, wire, at);
  record->message_id = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->transaction_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->participant_reference_number[i] = wire[at++]; }
  record->market_wide_circuit_breaker_level_indicator = wire[at++];
  record->reserved = wire[at++];

  return at;
}

/* what was read of Market Wide Circuit Breaker Status Message is what was written, byte for byte */
static void equal_market_wide_circuit_breaker_status_message(const MarketWideCircuitBreakerStatusMessage *read, const MarketWideCircuitBreakerStatusMessage *written) {
  assert(read->participant_id == written->participant_id);
  equal_timestamp1(&read->timestamp_1, &written->timestamp_1);
  assert(read->message_id == written->message_id);
  for (size_t i = 0; i < 4; i++) { assert(read->transaction_id[i] == written->transaction_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->participant_reference_number[i] == written->participant_reference_number[i]); }
  assert(read->market_wide_circuit_breaker_level_indicator == written->market_wide_circuit_breaker_level_indicator);
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

/* ---- Approximate Trades And Total Dollar Value Message: 34 bytes ------------- */

/* The Approximate Trades and Total Dollar Value message allows a Participant to report the total trades and total dollar value of trades at their respective market centers. */
typedef struct {
  uint8_t participant_id;                   /* byte 0 */
  Timestamp1 timestamp_1;                   /* bytes 1 to 8 */
  uint8_t message_id;                       /* byte 9 */
  uint8_t transaction_id[4];                /* bytes 10 to 13 */
  uint8_t participant_reference_number[8];  /* bytes 14 to 21 */
  uint8_t total_trades[4];                  /* bytes 22 to 25 */
  uint8_t dollar_value[8];                  /* bytes 26 to 33 */
} ApproximateTradesAndTotalDollarValueMessage;

/* any Approximate Trades And Total Dollar Value Message at all: every byte one the checker chooses */
static void any_approximate_trades_and_total_dollar_value_message(ApproximateTradesAndTotalDollarValueMessage *record) {
  record->participant_id = arbitrary();
  any_timestamp1(&record->timestamp_1);
  record->message_id = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->transaction_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->participant_reference_number[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->total_trades[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->dollar_value[i] = arbitrary(); }
}

/* Approximate Trades And Total Dollar Value Message to the wire: 34 bytes from at, returning where the next byte goes */
static size_t encode_approximate_trades_and_total_dollar_value_message(const ApproximateTradesAndTotalDollarValueMessage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->participant_id;
  at = encode_timestamp1(&record->timestamp_1, wire, at);
  wire[at++] = record->message_id;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->transaction_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->participant_reference_number[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->total_trades[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->dollar_value[i]; }

  return at;
}

/* Approximate Trades And Total Dollar Value Message off the wire: 34 bytes from at, returning where the next byte lies */
static size_t decode_approximate_trades_and_total_dollar_value_message(ApproximateTradesAndTotalDollarValueMessage *record, const uint8_t *wire, size_t at) {
  record->participant_id = wire[at++];
  at = decode_timestamp1(&record->timestamp_1, wire, at);
  record->message_id = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->transaction_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->participant_reference_number[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->total_trades[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->dollar_value[i] = wire[at++]; }

  return at;
}

/* what was read of Approximate Trades And Total Dollar Value Message is what was written, byte for byte */
static void equal_approximate_trades_and_total_dollar_value_message(const ApproximateTradesAndTotalDollarValueMessage *read, const ApproximateTradesAndTotalDollarValueMessage *written) {
  assert(read->participant_id == written->participant_id);
  equal_timestamp1(&read->timestamp_1, &written->timestamp_1);
  assert(read->message_id == written->message_id);
  for (size_t i = 0; i < 4; i++) { assert(read->transaction_id[i] == written->transaction_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->participant_reference_number[i] == written->participant_reference_number[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->total_trades[i] == written->total_trades[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->dollar_value[i] == written->dollar_value[i]); }
}

/* Approximate Trades And Total Dollar Value Message: written and read back, then read and written back */
static void check_approximate_trades_and_total_dollar_value_message(void) {
  ApproximateTradesAndTotalDollarValueMessage sent;
  ApproximateTradesAndTotalDollarValueMessage got;
  uint8_t wire[34];
  uint8_t again[34];

  any_approximate_trades_and_total_dollar_value_message(&sent);
  assert(encode_approximate_trades_and_total_dollar_value_message(&sent, wire, 0) == 34);
  assert(decode_approximate_trades_and_total_dollar_value_message(&got, wire, 0) == 34);
  equal_approximate_trades_and_total_dollar_value_message(&got, &sent);

  for (size_t i = 0; i < 34; i++) { wire[i] = arbitrary(); }
  assert(decode_approximate_trades_and_total_dollar_value_message(&got, wire, 0) == 34);
  assert(encode_approximate_trades_and_total_dollar_value_message(&got, again, 0) == 34);
  for (size_t i = 0; i < 34; i++) { assert(again[i] == wire[i]); }
}

/* ---- Crossing Session Summary Message: 46 bytes ------------------------------ */

/* The Crossing Session message is used to report the total volume and dollar value of trades transacted after the close of a Participant’s regular session. */
typedef struct {
  uint8_t participant_id;                              /* byte 0 */
  Timestamp1 timestamp_1;                              /* bytes 1 to 8 */
  uint8_t message_id;                                  /* byte 9 */
  uint8_t transaction_id[4];                           /* bytes 10 to 13 */
  uint8_t participant_reference_number[8];             /* bytes 14 to 21 */
  uint8_t crossing_session_i_total_trades_volume[8];   /* bytes 22 to 29 */
  uint8_t crossing_session_ii_dollar_value[8];         /* bytes 30 to 37 */
  uint8_t crossing_session_ii_total_trades_volume[8];  /* bytes 38 to 45 */
} CrossingSessionSummaryMessage;

/* any Crossing Session Summary Message at all: every byte one the checker chooses */
static void any_crossing_session_summary_message(CrossingSessionSummaryMessage *record) {
  record->participant_id = arbitrary();
  any_timestamp1(&record->timestamp_1);
  record->message_id = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->transaction_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->participant_reference_number[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->crossing_session_i_total_trades_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->crossing_session_ii_dollar_value[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->crossing_session_ii_total_trades_volume[i] = arbitrary(); }
}

/* Crossing Session Summary Message to the wire: 46 bytes from at, returning where the next byte goes */
static size_t encode_crossing_session_summary_message(const CrossingSessionSummaryMessage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->participant_id;
  at = encode_timestamp1(&record->timestamp_1, wire, at);
  wire[at++] = record->message_id;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->transaction_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->participant_reference_number[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->crossing_session_i_total_trades_volume[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->crossing_session_ii_dollar_value[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->crossing_session_ii_total_trades_volume[i]; }

  return at;
}

/* Crossing Session Summary Message off the wire: 46 bytes from at, returning where the next byte lies */
static size_t decode_crossing_session_summary_message(CrossingSessionSummaryMessage *record, const uint8_t *wire, size_t at) {
  record->participant_id = wire[at++];
  at = decode_timestamp1(&record->timestamp_1, wire, at);
  record->message_id = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->transaction_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->participant_reference_number[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->crossing_session_i_total_trades_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->crossing_session_ii_dollar_value[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->crossing_session_ii_total_trades_volume[i] = wire[at++]; }

  return at;
}

/* what was read of Crossing Session Summary Message is what was written, byte for byte */
static void equal_crossing_session_summary_message(const CrossingSessionSummaryMessage *read, const CrossingSessionSummaryMessage *written) {
  assert(read->participant_id == written->participant_id);
  equal_timestamp1(&read->timestamp_1, &written->timestamp_1);
  assert(read->message_id == written->message_id);
  for (size_t i = 0; i < 4; i++) { assert(read->transaction_id[i] == written->transaction_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->participant_reference_number[i] == written->participant_reference_number[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->crossing_session_i_total_trades_volume[i] == written->crossing_session_i_total_trades_volume[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->crossing_session_ii_dollar_value[i] == written->crossing_session_ii_dollar_value[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->crossing_session_ii_total_trades_volume[i] == written->crossing_session_ii_total_trades_volume[i]); }
}

/* Crossing Session Summary Message: written and read back, then read and written back */
static void check_crossing_session_summary_message(void) {
  CrossingSessionSummaryMessage sent;
  CrossingSessionSummaryMessage got;
  uint8_t wire[46];
  uint8_t again[46];

  any_crossing_session_summary_message(&sent);
  assert(encode_crossing_session_summary_message(&sent, wire, 0) == 46);
  assert(decode_crossing_session_summary_message(&got, wire, 0) == 46);
  equal_crossing_session_summary_message(&got, &sent);

  for (size_t i = 0; i < 46; i++) { wire[i] = arbitrary(); }
  assert(decode_crossing_session_summary_message(&got, wire, 0) == 46);
  assert(encode_crossing_session_summary_message(&got, again, 0) == 46);
  for (size_t i = 0; i < 46; i++) { assert(again[i] == wire[i]); }
}

/* ---- Sale Conditions: 4 bytes ------------------------------------------------ */

/* Sale Conditions */
typedef struct {
  uint8_t settlement_type;                  /* byte 0 */
  uint8_t trade_through_exempt_reason;      /* byte 1 */
  uint8_t extended_hours_or_sequence_type;  /* byte 2 */
  uint8_t sro_trade_detail;                 /* byte 3 */
} SaleConditions;

/* any Sale Conditions at all: every byte one the checker chooses */
static void any_sale_conditions(SaleConditions *record) {
  record->settlement_type = arbitrary();
  record->trade_through_exempt_reason = arbitrary();
  record->extended_hours_or_sequence_type = arbitrary();
  record->sro_trade_detail = arbitrary();
}

/* Sale Conditions to the wire: 4 bytes from at, returning where the next byte goes */
static size_t encode_sale_conditions(const SaleConditions *record, uint8_t *wire, size_t at) {
  wire[at++] = record->settlement_type;
  wire[at++] = record->trade_through_exempt_reason;
  wire[at++] = record->extended_hours_or_sequence_type;
  wire[at++] = record->sro_trade_detail;

  return at;
}

/* Sale Conditions off the wire: 4 bytes from at, returning where the next byte lies */
static size_t decode_sale_conditions(SaleConditions *record, const uint8_t *wire, size_t at) {
  record->settlement_type = wire[at++];
  record->trade_through_exempt_reason = wire[at++];
  record->extended_hours_or_sequence_type = wire[at++];
  record->sro_trade_detail = wire[at++];

  return at;
}

/* what was read of Sale Conditions is what was written, byte for byte */
static void equal_sale_conditions(const SaleConditions *read, const SaleConditions *written) {
  assert(read->settlement_type == written->settlement_type);
  assert(read->trade_through_exempt_reason == written->trade_through_exempt_reason);
  assert(read->extended_hours_or_sequence_type == written->extended_hours_or_sequence_type);
  assert(read->sro_trade_detail == written->sro_trade_detail);
}

/* Sale Conditions: written and read back, then read and written back */
static void check_sale_conditions(void) {
  SaleConditions sent;
  SaleConditions got;
  uint8_t wire[4];
  uint8_t again[4];

  any_sale_conditions(&sent);
  assert(encode_sale_conditions(&sent, wire, 0) == 4);
  assert(decode_sale_conditions(&got, wire, 0) == 4);
  equal_sale_conditions(&got, &sent);

  for (size_t i = 0; i < 4; i++) { wire[i] = arbitrary(); }
  assert(decode_sale_conditions(&got, wire, 0) == 4);
  assert(encode_sale_conditions(&got, again, 0) == 4);
  for (size_t i = 0; i < 4; i++) { assert(again[i] == wire[i]); }
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

/* ---- Prior Day Corrected Trade: 28 bytes ------------------------------------- */

/* Prior Day Corrected Trade */
typedef struct {
  SaleConditions sale_conditions;                          /* bytes 0 to 3 */
  uint8_t trade_price[8];                                  /* bytes 4 to 11 */
  uint8_t trade_volume[4];                                 /* bytes 12 to 15 */
  uint8_t sellers_sale_days;                               /* byte 16 */
  uint8_t stop_stock_indicator;                            /* byte 17 */
  uint8_t trade_through_exempt_indicator;                  /* byte 18 */
  uint8_t short_sale_restriction_indicator;                /* byte 19 */
  PriorDayTradeDateAndTime prior_day_trade_date_and_time;  /* bytes 20 to 27 */
} PriorDayCorrectedTrade;

/* any Prior Day Corrected Trade at all: every byte one the checker chooses */
static void any_prior_day_corrected_trade(PriorDayCorrectedTrade *record) {
  any_sale_conditions(&record->sale_conditions);
  for (size_t i = 0; i < 8; i++) { record->trade_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->trade_volume[i] = arbitrary(); }
  record->sellers_sale_days = arbitrary();
  record->stop_stock_indicator = arbitrary();
  record->trade_through_exempt_indicator = arbitrary();
  record->short_sale_restriction_indicator = arbitrary();
  any_prior_day_trade_date_and_time(&record->prior_day_trade_date_and_time);
}

/* Prior Day Corrected Trade to the wire: 28 bytes from at, returning where the next byte goes */
static size_t encode_prior_day_corrected_trade(const PriorDayCorrectedTrade *record, uint8_t *wire, size_t at) {
  at = encode_sale_conditions(&record->sale_conditions, wire, at);
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->trade_price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->trade_volume[i]; }
  wire[at++] = record->sellers_sale_days;
  wire[at++] = record->stop_stock_indicator;
  wire[at++] = record->trade_through_exempt_indicator;
  wire[at++] = record->short_sale_restriction_indicator;
  at = encode_prior_day_trade_date_and_time(&record->prior_day_trade_date_and_time, wire, at);

  return at;
}

/* Prior Day Corrected Trade off the wire: 28 bytes from at, returning where the next byte lies */
static size_t decode_prior_day_corrected_trade(PriorDayCorrectedTrade *record, const uint8_t *wire, size_t at) {
  at = decode_sale_conditions(&record->sale_conditions, wire, at);
  for (size_t i = 0; i < 8; i++) { record->trade_price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->trade_volume[i] = wire[at++]; }
  record->sellers_sale_days = wire[at++];
  record->stop_stock_indicator = wire[at++];
  record->trade_through_exempt_indicator = wire[at++];
  record->short_sale_restriction_indicator = wire[at++];
  at = decode_prior_day_trade_date_and_time(&record->prior_day_trade_date_and_time, wire, at);

  return at;
}

/* what was read of Prior Day Corrected Trade is what was written, byte for byte */
static void equal_prior_day_corrected_trade(const PriorDayCorrectedTrade *read, const PriorDayCorrectedTrade *written) {
  equal_sale_conditions(&read->sale_conditions, &written->sale_conditions);
  for (size_t i = 0; i < 8; i++) { assert(read->trade_price[i] == written->trade_price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->trade_volume[i] == written->trade_volume[i]); }
  assert(read->sellers_sale_days == written->sellers_sale_days);
  assert(read->stop_stock_indicator == written->stop_stock_indicator);
  assert(read->trade_through_exempt_indicator == written->trade_through_exempt_indicator);
  assert(read->short_sale_restriction_indicator == written->short_sale_restriction_indicator);
  equal_prior_day_trade_date_and_time(&read->prior_day_trade_date_and_time, &written->prior_day_trade_date_and_time);
}

/* Prior Day Corrected Trade: written and read back, then read and written back */
static void check_prior_day_corrected_trade(void) {
  PriorDayCorrectedTrade sent;
  PriorDayCorrectedTrade got;
  uint8_t wire[28];
  uint8_t again[28];

  any_prior_day_corrected_trade(&sent);
  assert(encode_prior_day_corrected_trade(&sent, wire, 0) == 28);
  assert(decode_prior_day_corrected_trade(&got, wire, 0) == 28);
  equal_prior_day_corrected_trade(&got, &sent);

  for (size_t i = 0; i < 28; i++) { wire[i] = arbitrary(); }
  assert(decode_prior_day_corrected_trade(&got, wire, 0) == 28);
  assert(encode_prior_day_corrected_trade(&got, again, 0) == 28);
  for (size_t i = 0; i < 28; i++) { assert(again[i] == wire[i]); }
}

/* ---- Prior Day Original Trade: 28 bytes -------------------------------------- */

/* Prior Day Original Trade */
typedef struct {
  SaleConditions sale_conditions;                          /* bytes 0 to 3 */
  uint8_t trade_price[8];                                  /* bytes 4 to 11 */
  uint8_t trade_volume[4];                                 /* bytes 12 to 15 */
  uint8_t sellers_sale_days;                               /* byte 16 */
  uint8_t stop_stock_indicator;                            /* byte 17 */
  uint8_t trade_through_exempt_indicator;                  /* byte 18 */
  uint8_t short_sale_restriction_indicator;                /* byte 19 */
  PriorDayTradeDateAndTime prior_day_trade_date_and_time;  /* bytes 20 to 27 */
} PriorDayOriginalTrade;

/* any Prior Day Original Trade at all: every byte one the checker chooses */
static void any_prior_day_original_trade(PriorDayOriginalTrade *record) {
  any_sale_conditions(&record->sale_conditions);
  for (size_t i = 0; i < 8; i++) { record->trade_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->trade_volume[i] = arbitrary(); }
  record->sellers_sale_days = arbitrary();
  record->stop_stock_indicator = arbitrary();
  record->trade_through_exempt_indicator = arbitrary();
  record->short_sale_restriction_indicator = arbitrary();
  any_prior_day_trade_date_and_time(&record->prior_day_trade_date_and_time);
}

/* Prior Day Original Trade to the wire: 28 bytes from at, returning where the next byte goes */
static size_t encode_prior_day_original_trade(const PriorDayOriginalTrade *record, uint8_t *wire, size_t at) {
  at = encode_sale_conditions(&record->sale_conditions, wire, at);
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->trade_price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->trade_volume[i]; }
  wire[at++] = record->sellers_sale_days;
  wire[at++] = record->stop_stock_indicator;
  wire[at++] = record->trade_through_exempt_indicator;
  wire[at++] = record->short_sale_restriction_indicator;
  at = encode_prior_day_trade_date_and_time(&record->prior_day_trade_date_and_time, wire, at);

  return at;
}

/* Prior Day Original Trade off the wire: 28 bytes from at, returning where the next byte lies */
static size_t decode_prior_day_original_trade(PriorDayOriginalTrade *record, const uint8_t *wire, size_t at) {
  at = decode_sale_conditions(&record->sale_conditions, wire, at);
  for (size_t i = 0; i < 8; i++) { record->trade_price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->trade_volume[i] = wire[at++]; }
  record->sellers_sale_days = wire[at++];
  record->stop_stock_indicator = wire[at++];
  record->trade_through_exempt_indicator = wire[at++];
  record->short_sale_restriction_indicator = wire[at++];
  at = decode_prior_day_trade_date_and_time(&record->prior_day_trade_date_and_time, wire, at);

  return at;
}

/* what was read of Prior Day Original Trade is what was written, byte for byte */
static void equal_prior_day_original_trade(const PriorDayOriginalTrade *read, const PriorDayOriginalTrade *written) {
  equal_sale_conditions(&read->sale_conditions, &written->sale_conditions);
  for (size_t i = 0; i < 8; i++) { assert(read->trade_price[i] == written->trade_price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->trade_volume[i] == written->trade_volume[i]); }
  assert(read->sellers_sale_days == written->sellers_sale_days);
  assert(read->stop_stock_indicator == written->stop_stock_indicator);
  assert(read->trade_through_exempt_indicator == written->trade_through_exempt_indicator);
  assert(read->short_sale_restriction_indicator == written->short_sale_restriction_indicator);
  equal_prior_day_trade_date_and_time(&read->prior_day_trade_date_and_time, &written->prior_day_trade_date_and_time);
}

/* Prior Day Original Trade: written and read back, then read and written back */
static void check_prior_day_original_trade(void) {
  PriorDayOriginalTrade sent;
  PriorDayOriginalTrade got;
  uint8_t wire[28];
  uint8_t again[28];

  any_prior_day_original_trade(&sent);
  assert(encode_prior_day_original_trade(&sent, wire, 0) == 28);
  assert(decode_prior_day_original_trade(&got, wire, 0) == 28);
  equal_prior_day_original_trade(&got, &sent);

  for (size_t i = 0; i < 28; i++) { wire[i] = arbitrary(); }
  assert(decode_prior_day_original_trade(&got, wire, 0) == 28);
  assert(encode_prior_day_original_trade(&got, again, 0) == 28);
  for (size_t i = 0; i < 28; i++) { assert(again[i] == wire[i]); }
}

/* ---- Prior Day Trade Correction Message: 91 bytes ---------------------------- */

/* Prior Day messages are used to report CTA eligible Equity, Local Issue or Bond trades, corrections, cancels or errors for transactions that occurred earlier than the current trading day and had not been reported */
typedef struct {
  uint8_t participant_id;                            /* byte 0 */
  Timestamp1 timestamp_1;                            /* bytes 1 to 8 */
  uint8_t message_id;                                /* byte 9 */
  uint8_t transaction_id[4];                         /* bytes 10 to 13 */
  uint8_t participant_reference_number[8];           /* bytes 14 to 21 */
  uint8_t security_symbol[11];                       /* bytes 22 to 32 */
  uint8_t instrument_type;                           /* byte 33 */
  PriorDayCorrectedTrade prior_day_corrected_trade;  /* bytes 34 to 61 */
  uint8_t trade_reporting_facility_id;               /* byte 62 */
  PriorDayOriginalTrade prior_day_original_trade;    /* bytes 63 to 90 */
} PriorDayTradeCorrectionMessage;

/* any Prior Day Trade Correction Message at all: every byte one the checker chooses */
static void any_prior_day_trade_correction_message(PriorDayTradeCorrectionMessage *record) {
  record->participant_id = arbitrary();
  any_timestamp1(&record->timestamp_1);
  record->message_id = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->transaction_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->participant_reference_number[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->security_symbol[i] = arbitrary(); }
  record->instrument_type = arbitrary();
  any_prior_day_corrected_trade(&record->prior_day_corrected_trade);
  record->trade_reporting_facility_id = arbitrary();
  any_prior_day_original_trade(&record->prior_day_original_trade);
}

/* Prior Day Trade Correction Message to the wire: 91 bytes from at, returning where the next byte goes */
static size_t encode_prior_day_trade_correction_message(const PriorDayTradeCorrectionMessage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->participant_id;
  at = encode_timestamp1(&record->timestamp_1, wire, at);
  wire[at++] = record->message_id;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->transaction_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->participant_reference_number[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->security_symbol[i]; }
  wire[at++] = record->instrument_type;
  at = encode_prior_day_corrected_trade(&record->prior_day_corrected_trade, wire, at);
  wire[at++] = record->trade_reporting_facility_id;
  at = encode_prior_day_original_trade(&record->prior_day_original_trade, wire, at);

  return at;
}

/* Prior Day Trade Correction Message off the wire: 91 bytes from at, returning where the next byte lies */
static size_t decode_prior_day_trade_correction_message(PriorDayTradeCorrectionMessage *record, const uint8_t *wire, size_t at) {
  record->participant_id = wire[at++];
  at = decode_timestamp1(&record->timestamp_1, wire, at);
  record->message_id = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->transaction_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->participant_reference_number[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->security_symbol[i] = wire[at++]; }
  record->instrument_type = wire[at++];
  at = decode_prior_day_corrected_trade(&record->prior_day_corrected_trade, wire, at);
  record->trade_reporting_facility_id = wire[at++];
  at = decode_prior_day_original_trade(&record->prior_day_original_trade, wire, at);

  return at;
}

/* what was read of Prior Day Trade Correction Message is what was written, byte for byte */
static void equal_prior_day_trade_correction_message(const PriorDayTradeCorrectionMessage *read, const PriorDayTradeCorrectionMessage *written) {
  assert(read->participant_id == written->participant_id);
  equal_timestamp1(&read->timestamp_1, &written->timestamp_1);
  assert(read->message_id == written->message_id);
  for (size_t i = 0; i < 4; i++) { assert(read->transaction_id[i] == written->transaction_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->participant_reference_number[i] == written->participant_reference_number[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->security_symbol[i] == written->security_symbol[i]); }
  assert(read->instrument_type == written->instrument_type);
  equal_prior_day_corrected_trade(&read->prior_day_corrected_trade, &written->prior_day_corrected_trade);
  assert(read->trade_reporting_facility_id == written->trade_reporting_facility_id);
  equal_prior_day_original_trade(&read->prior_day_original_trade, &written->prior_day_original_trade);
}

/* Prior Day Trade Correction Message: written and read back, then read and written back */
static void check_prior_day_trade_correction_message(void) {
  PriorDayTradeCorrectionMessage sent;
  PriorDayTradeCorrectionMessage got;
  uint8_t wire[91];
  uint8_t again[91];

  any_prior_day_trade_correction_message(&sent);
  assert(encode_prior_day_trade_correction_message(&sent, wire, 0) == 91);
  assert(decode_prior_day_trade_correction_message(&got, wire, 0) == 91);
  equal_prior_day_trade_correction_message(&got, &sent);

  for (size_t i = 0; i < 91; i++) { wire[i] = arbitrary(); }
  assert(decode_prior_day_trade_correction_message(&got, wire, 0) == 91);
  assert(encode_prior_day_trade_correction_message(&got, again, 0) == 91);
  for (size_t i = 0; i < 91; i++) { assert(again[i] == wire[i]); }
}

/* ---- Fractional Prior Day Corrected Trade: 32 bytes -------------------------- */

/* Fractional Prior Day Corrected Trade */
typedef struct {
  SaleConditions sale_conditions;                          /* bytes 0 to 3 */
  uint8_t trade_price[8];                                  /* bytes 4 to 11 */
  uint8_t fractional_trade_volume[8];                      /* bytes 12 to 19 */
  uint8_t sellers_sale_days;                               /* byte 20 */
  uint8_t stop_stock_indicator;                            /* byte 21 */
  uint8_t trade_through_exempt_indicator;                  /* byte 22 */
  uint8_t short_sale_restriction_indicator;                /* byte 23 */
  PriorDayTradeDateAndTime prior_day_trade_date_and_time;  /* bytes 24 to 31 */
} FractionalPriorDayCorrectedTrade;

/* any Fractional Prior Day Corrected Trade at all: every byte one the checker chooses */
static void any_fractional_prior_day_corrected_trade(FractionalPriorDayCorrectedTrade *record) {
  any_sale_conditions(&record->sale_conditions);
  for (size_t i = 0; i < 8; i++) { record->trade_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->fractional_trade_volume[i] = arbitrary(); }
  record->sellers_sale_days = arbitrary();
  record->stop_stock_indicator = arbitrary();
  record->trade_through_exempt_indicator = arbitrary();
  record->short_sale_restriction_indicator = arbitrary();
  any_prior_day_trade_date_and_time(&record->prior_day_trade_date_and_time);
}

/* Fractional Prior Day Corrected Trade to the wire: 32 bytes from at, returning where the next byte goes */
static size_t encode_fractional_prior_day_corrected_trade(const FractionalPriorDayCorrectedTrade *record, uint8_t *wire, size_t at) {
  at = encode_sale_conditions(&record->sale_conditions, wire, at);
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->trade_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->fractional_trade_volume[i]; }
  wire[at++] = record->sellers_sale_days;
  wire[at++] = record->stop_stock_indicator;
  wire[at++] = record->trade_through_exempt_indicator;
  wire[at++] = record->short_sale_restriction_indicator;
  at = encode_prior_day_trade_date_and_time(&record->prior_day_trade_date_and_time, wire, at);

  return at;
}

/* Fractional Prior Day Corrected Trade off the wire: 32 bytes from at, returning where the next byte lies */
static size_t decode_fractional_prior_day_corrected_trade(FractionalPriorDayCorrectedTrade *record, const uint8_t *wire, size_t at) {
  at = decode_sale_conditions(&record->sale_conditions, wire, at);
  for (size_t i = 0; i < 8; i++) { record->trade_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->fractional_trade_volume[i] = wire[at++]; }
  record->sellers_sale_days = wire[at++];
  record->stop_stock_indicator = wire[at++];
  record->trade_through_exempt_indicator = wire[at++];
  record->short_sale_restriction_indicator = wire[at++];
  at = decode_prior_day_trade_date_and_time(&record->prior_day_trade_date_and_time, wire, at);

  return at;
}

/* what was read of Fractional Prior Day Corrected Trade is what was written, byte for byte */
static void equal_fractional_prior_day_corrected_trade(const FractionalPriorDayCorrectedTrade *read, const FractionalPriorDayCorrectedTrade *written) {
  equal_sale_conditions(&read->sale_conditions, &written->sale_conditions);
  for (size_t i = 0; i < 8; i++) { assert(read->trade_price[i] == written->trade_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->fractional_trade_volume[i] == written->fractional_trade_volume[i]); }
  assert(read->sellers_sale_days == written->sellers_sale_days);
  assert(read->stop_stock_indicator == written->stop_stock_indicator);
  assert(read->trade_through_exempt_indicator == written->trade_through_exempt_indicator);
  assert(read->short_sale_restriction_indicator == written->short_sale_restriction_indicator);
  equal_prior_day_trade_date_and_time(&read->prior_day_trade_date_and_time, &written->prior_day_trade_date_and_time);
}

/* Fractional Prior Day Corrected Trade: written and read back, then read and written back */
static void check_fractional_prior_day_corrected_trade(void) {
  FractionalPriorDayCorrectedTrade sent;
  FractionalPriorDayCorrectedTrade got;
  uint8_t wire[32];
  uint8_t again[32];

  any_fractional_prior_day_corrected_trade(&sent);
  assert(encode_fractional_prior_day_corrected_trade(&sent, wire, 0) == 32);
  assert(decode_fractional_prior_day_corrected_trade(&got, wire, 0) == 32);
  equal_fractional_prior_day_corrected_trade(&got, &sent);

  for (size_t i = 0; i < 32; i++) { wire[i] = arbitrary(); }
  assert(decode_fractional_prior_day_corrected_trade(&got, wire, 0) == 32);
  assert(encode_fractional_prior_day_corrected_trade(&got, again, 0) == 32);
  for (size_t i = 0; i < 32; i++) { assert(again[i] == wire[i]); }
}

/* ---- Fractional Prior Day Original Trade: 32 bytes --------------------------- */

/* Fractional Prior Day Original Trade */
typedef struct {
  SaleConditions sale_conditions;                          /* bytes 0 to 3 */
  uint8_t trade_price[8];                                  /* bytes 4 to 11 */
  uint8_t fractional_trade_volume[8];                      /* bytes 12 to 19 */
  uint8_t sellers_sale_days;                               /* byte 20 */
  uint8_t stop_stock_indicator;                            /* byte 21 */
  uint8_t trade_through_exempt_indicator;                  /* byte 22 */
  uint8_t short_sale_restriction_indicator;                /* byte 23 */
  PriorDayTradeDateAndTime prior_day_trade_date_and_time;  /* bytes 24 to 31 */
} FractionalPriorDayOriginalTrade;

/* any Fractional Prior Day Original Trade at all: every byte one the checker chooses */
static void any_fractional_prior_day_original_trade(FractionalPriorDayOriginalTrade *record) {
  any_sale_conditions(&record->sale_conditions);
  for (size_t i = 0; i < 8; i++) { record->trade_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->fractional_trade_volume[i] = arbitrary(); }
  record->sellers_sale_days = arbitrary();
  record->stop_stock_indicator = arbitrary();
  record->trade_through_exempt_indicator = arbitrary();
  record->short_sale_restriction_indicator = arbitrary();
  any_prior_day_trade_date_and_time(&record->prior_day_trade_date_and_time);
}

/* Fractional Prior Day Original Trade to the wire: 32 bytes from at, returning where the next byte goes */
static size_t encode_fractional_prior_day_original_trade(const FractionalPriorDayOriginalTrade *record, uint8_t *wire, size_t at) {
  at = encode_sale_conditions(&record->sale_conditions, wire, at);
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->trade_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->fractional_trade_volume[i]; }
  wire[at++] = record->sellers_sale_days;
  wire[at++] = record->stop_stock_indicator;
  wire[at++] = record->trade_through_exempt_indicator;
  wire[at++] = record->short_sale_restriction_indicator;
  at = encode_prior_day_trade_date_and_time(&record->prior_day_trade_date_and_time, wire, at);

  return at;
}

/* Fractional Prior Day Original Trade off the wire: 32 bytes from at, returning where the next byte lies */
static size_t decode_fractional_prior_day_original_trade(FractionalPriorDayOriginalTrade *record, const uint8_t *wire, size_t at) {
  at = decode_sale_conditions(&record->sale_conditions, wire, at);
  for (size_t i = 0; i < 8; i++) { record->trade_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->fractional_trade_volume[i] = wire[at++]; }
  record->sellers_sale_days = wire[at++];
  record->stop_stock_indicator = wire[at++];
  record->trade_through_exempt_indicator = wire[at++];
  record->short_sale_restriction_indicator = wire[at++];
  at = decode_prior_day_trade_date_and_time(&record->prior_day_trade_date_and_time, wire, at);

  return at;
}

/* what was read of Fractional Prior Day Original Trade is what was written, byte for byte */
static void equal_fractional_prior_day_original_trade(const FractionalPriorDayOriginalTrade *read, const FractionalPriorDayOriginalTrade *written) {
  equal_sale_conditions(&read->sale_conditions, &written->sale_conditions);
  for (size_t i = 0; i < 8; i++) { assert(read->trade_price[i] == written->trade_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->fractional_trade_volume[i] == written->fractional_trade_volume[i]); }
  assert(read->sellers_sale_days == written->sellers_sale_days);
  assert(read->stop_stock_indicator == written->stop_stock_indicator);
  assert(read->trade_through_exempt_indicator == written->trade_through_exempt_indicator);
  assert(read->short_sale_restriction_indicator == written->short_sale_restriction_indicator);
  equal_prior_day_trade_date_and_time(&read->prior_day_trade_date_and_time, &written->prior_day_trade_date_and_time);
}

/* Fractional Prior Day Original Trade: written and read back, then read and written back */
static void check_fractional_prior_day_original_trade(void) {
  FractionalPriorDayOriginalTrade sent;
  FractionalPriorDayOriginalTrade got;
  uint8_t wire[32];
  uint8_t again[32];

  any_fractional_prior_day_original_trade(&sent);
  assert(encode_fractional_prior_day_original_trade(&sent, wire, 0) == 32);
  assert(decode_fractional_prior_day_original_trade(&got, wire, 0) == 32);
  equal_fractional_prior_day_original_trade(&got, &sent);

  for (size_t i = 0; i < 32; i++) { wire[i] = arbitrary(); }
  assert(decode_fractional_prior_day_original_trade(&got, wire, 0) == 32);
  assert(encode_fractional_prior_day_original_trade(&got, again, 0) == 32);
  for (size_t i = 0; i < 32; i++) { assert(again[i] == wire[i]); }
}

/* ---- Fractional Prior Day Trade Correction Message: 99 bytes ----------------- */

/* Prior Day messages are used to report CTA eligible Equity, Local Issue or Bond trades, corrections, cancels or errors for transactions that occurred earlier than the current trading day and had not been reported */
typedef struct {
  uint8_t participant_id;                                                 /* byte 0 */
  Timestamp1 timestamp_1;                                                 /* bytes 1 to 8 */
  uint8_t message_id;                                                     /* byte 9 */
  uint8_t transaction_id[4];                                              /* bytes 10 to 13 */
  uint8_t participant_reference_number[8];                                /* bytes 14 to 21 */
  uint8_t security_symbol[11];                                            /* bytes 22 to 32 */
  uint8_t instrument_type;                                                /* byte 33 */
  FractionalPriorDayCorrectedTrade fractional_prior_day_corrected_trade;  /* bytes 34 to 65 */
  uint8_t trade_reporting_facility_id;                                    /* byte 66 */
  FractionalPriorDayOriginalTrade fractional_prior_day_original_trade;    /* bytes 67 to 98 */
} FractionalPriorDayTradeCorrectionMessage;

/* any Fractional Prior Day Trade Correction Message at all: every byte one the checker chooses */
static void any_fractional_prior_day_trade_correction_message(FractionalPriorDayTradeCorrectionMessage *record) {
  record->participant_id = arbitrary();
  any_timestamp1(&record->timestamp_1);
  record->message_id = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->transaction_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->participant_reference_number[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->security_symbol[i] = arbitrary(); }
  record->instrument_type = arbitrary();
  any_fractional_prior_day_corrected_trade(&record->fractional_prior_day_corrected_trade);
  record->trade_reporting_facility_id = arbitrary();
  any_fractional_prior_day_original_trade(&record->fractional_prior_day_original_trade);
}

/* Fractional Prior Day Trade Correction Message to the wire: 99 bytes from at, returning where the next byte goes */
static size_t encode_fractional_prior_day_trade_correction_message(const FractionalPriorDayTradeCorrectionMessage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->participant_id;
  at = encode_timestamp1(&record->timestamp_1, wire, at);
  wire[at++] = record->message_id;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->transaction_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->participant_reference_number[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->security_symbol[i]; }
  wire[at++] = record->instrument_type;
  at = encode_fractional_prior_day_corrected_trade(&record->fractional_prior_day_corrected_trade, wire, at);
  wire[at++] = record->trade_reporting_facility_id;
  at = encode_fractional_prior_day_original_trade(&record->fractional_prior_day_original_trade, wire, at);

  return at;
}

/* Fractional Prior Day Trade Correction Message off the wire: 99 bytes from at, returning where the next byte lies */
static size_t decode_fractional_prior_day_trade_correction_message(FractionalPriorDayTradeCorrectionMessage *record, const uint8_t *wire, size_t at) {
  record->participant_id = wire[at++];
  at = decode_timestamp1(&record->timestamp_1, wire, at);
  record->message_id = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->transaction_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->participant_reference_number[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->security_symbol[i] = wire[at++]; }
  record->instrument_type = wire[at++];
  at = decode_fractional_prior_day_corrected_trade(&record->fractional_prior_day_corrected_trade, wire, at);
  record->trade_reporting_facility_id = wire[at++];
  at = decode_fractional_prior_day_original_trade(&record->fractional_prior_day_original_trade, wire, at);

  return at;
}

/* what was read of Fractional Prior Day Trade Correction Message is what was written, byte for byte */
static void equal_fractional_prior_day_trade_correction_message(const FractionalPriorDayTradeCorrectionMessage *read, const FractionalPriorDayTradeCorrectionMessage *written) {
  assert(read->participant_id == written->participant_id);
  equal_timestamp1(&read->timestamp_1, &written->timestamp_1);
  assert(read->message_id == written->message_id);
  for (size_t i = 0; i < 4; i++) { assert(read->transaction_id[i] == written->transaction_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->participant_reference_number[i] == written->participant_reference_number[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->security_symbol[i] == written->security_symbol[i]); }
  assert(read->instrument_type == written->instrument_type);
  equal_fractional_prior_day_corrected_trade(&read->fractional_prior_day_corrected_trade, &written->fractional_prior_day_corrected_trade);
  assert(read->trade_reporting_facility_id == written->trade_reporting_facility_id);
  equal_fractional_prior_day_original_trade(&read->fractional_prior_day_original_trade, &written->fractional_prior_day_original_trade);
}

/* Fractional Prior Day Trade Correction Message: written and read back, then read and written back */
static void check_fractional_prior_day_trade_correction_message(void) {
  FractionalPriorDayTradeCorrectionMessage sent;
  FractionalPriorDayTradeCorrectionMessage got;
  uint8_t wire[99];
  uint8_t again[99];

  any_fractional_prior_day_trade_correction_message(&sent);
  assert(encode_fractional_prior_day_trade_correction_message(&sent, wire, 0) == 99);
  assert(decode_fractional_prior_day_trade_correction_message(&got, wire, 0) == 99);
  equal_fractional_prior_day_trade_correction_message(&got, &sent);

  for (size_t i = 0; i < 99; i++) { wire[i] = arbitrary(); }
  assert(decode_fractional_prior_day_trade_correction_message(&got, wire, 0) == 99);
  assert(encode_fractional_prior_day_trade_correction_message(&got, again, 0) == 99);
  for (size_t i = 0; i < 99; i++) { assert(again[i] == wire[i]); }
}

/* ---- Prior Day Trade Message: 63 bytes --------------------------------------- */

/* The Prior Day Trade message is used to report a Cta Equity, Local Issue or Bond transaction which occurred earlier than the current trading day and was not reported. */
typedef struct {
  uint8_t participant_id;                                  /* byte 0 */
  Timestamp1 timestamp_1;                                  /* bytes 1 to 8 */
  uint8_t message_id;                                      /* byte 9 */
  uint8_t transaction_id[4];                               /* bytes 10 to 13 */
  uint8_t participant_reference_number[8];                 /* bytes 14 to 21 */
  uint8_t security_symbol[11];                             /* bytes 22 to 32 */
  uint8_t instrument_type;                                 /* byte 33 */
  SaleConditions sale_conditions;                          /* bytes 34 to 37 */
  uint8_t trade_price[8];                                  /* bytes 38 to 45 */
  uint8_t trade_volume[4];                                 /* bytes 46 to 49 */
  uint8_t sellers_sale_days;                               /* byte 50 */
  uint8_t stop_stock_indicator;                            /* byte 51 */
  uint8_t trade_through_exempt_indicator;                  /* byte 52 */
  uint8_t short_sale_restriction_indicator;                /* byte 53 */
  uint8_t trade_reporting_facility_id;                     /* byte 54 */
  PriorDayTradeDateAndTime prior_day_trade_date_and_time;  /* bytes 55 to 62 */
} PriorDayTradeMessage;

/* any Prior Day Trade Message at all: every byte one the checker chooses */
static void any_prior_day_trade_message(PriorDayTradeMessage *record) {
  record->participant_id = arbitrary();
  any_timestamp1(&record->timestamp_1);
  record->message_id = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->transaction_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->participant_reference_number[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->security_symbol[i] = arbitrary(); }
  record->instrument_type = arbitrary();
  any_sale_conditions(&record->sale_conditions);
  for (size_t i = 0; i < 8; i++) { record->trade_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->trade_volume[i] = arbitrary(); }
  record->sellers_sale_days = arbitrary();
  record->stop_stock_indicator = arbitrary();
  record->trade_through_exempt_indicator = arbitrary();
  record->short_sale_restriction_indicator = arbitrary();
  record->trade_reporting_facility_id = arbitrary();
  any_prior_day_trade_date_and_time(&record->prior_day_trade_date_and_time);
}

/* Prior Day Trade Message to the wire: 63 bytes from at, returning where the next byte goes */
static size_t encode_prior_day_trade_message(const PriorDayTradeMessage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->participant_id;
  at = encode_timestamp1(&record->timestamp_1, wire, at);
  wire[at++] = record->message_id;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->transaction_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->participant_reference_number[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->security_symbol[i]; }
  wire[at++] = record->instrument_type;
  at = encode_sale_conditions(&record->sale_conditions, wire, at);
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

/* Prior Day Trade Message off the wire: 63 bytes from at, returning where the next byte lies */
static size_t decode_prior_day_trade_message(PriorDayTradeMessage *record, const uint8_t *wire, size_t at) {
  record->participant_id = wire[at++];
  at = decode_timestamp1(&record->timestamp_1, wire, at);
  record->message_id = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->transaction_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->participant_reference_number[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->security_symbol[i] = wire[at++]; }
  record->instrument_type = wire[at++];
  at = decode_sale_conditions(&record->sale_conditions, wire, at);
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
  assert(read->participant_id == written->participant_id);
  equal_timestamp1(&read->timestamp_1, &written->timestamp_1);
  assert(read->message_id == written->message_id);
  for (size_t i = 0; i < 4; i++) { assert(read->transaction_id[i] == written->transaction_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->participant_reference_number[i] == written->participant_reference_number[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->security_symbol[i] == written->security_symbol[i]); }
  assert(read->instrument_type == written->instrument_type);
  equal_sale_conditions(&read->sale_conditions, &written->sale_conditions);
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
  uint8_t wire[63];
  uint8_t again[63];

  any_prior_day_trade_message(&sent);
  assert(encode_prior_day_trade_message(&sent, wire, 0) == 63);
  assert(decode_prior_day_trade_message(&got, wire, 0) == 63);
  equal_prior_day_trade_message(&got, &sent);

  for (size_t i = 0; i < 63; i++) { wire[i] = arbitrary(); }
  assert(decode_prior_day_trade_message(&got, wire, 0) == 63);
  assert(encode_prior_day_trade_message(&got, again, 0) == 63);
  for (size_t i = 0; i < 63; i++) { assert(again[i] == wire[i]); }
}

/* ---- Fractional Prior Day Trade Message: 67 bytes ---------------------------- */

/* The Prior Day Trade message is used to report a Cta Equity, Local Issue or Bond transaction which occurred earlier than the current trading day and was not reported. */
typedef struct {
  uint8_t participant_id;                                  /* byte 0 */
  Timestamp1 timestamp_1;                                  /* bytes 1 to 8 */
  uint8_t message_id;                                      /* byte 9 */
  uint8_t transaction_id[4];                               /* bytes 10 to 13 */
  uint8_t participant_reference_number[8];                 /* bytes 14 to 21 */
  uint8_t security_symbol[11];                             /* bytes 22 to 32 */
  uint8_t instrument_type;                                 /* byte 33 */
  SaleConditions sale_conditions;                          /* bytes 34 to 37 */
  uint8_t trade_price[8];                                  /* bytes 38 to 45 */
  uint8_t fractional_trade_volume[8];                      /* bytes 46 to 53 */
  uint8_t sellers_sale_days;                               /* byte 54 */
  uint8_t stop_stock_indicator;                            /* byte 55 */
  uint8_t trade_through_exempt_indicator;                  /* byte 56 */
  uint8_t short_sale_restriction_indicator;                /* byte 57 */
  uint8_t trade_reporting_facility_id;                     /* byte 58 */
  PriorDayTradeDateAndTime prior_day_trade_date_and_time;  /* bytes 59 to 66 */
} FractionalPriorDayTradeMessage;

/* any Fractional Prior Day Trade Message at all: every byte one the checker chooses */
static void any_fractional_prior_day_trade_message(FractionalPriorDayTradeMessage *record) {
  record->participant_id = arbitrary();
  any_timestamp1(&record->timestamp_1);
  record->message_id = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->transaction_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->participant_reference_number[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->security_symbol[i] = arbitrary(); }
  record->instrument_type = arbitrary();
  any_sale_conditions(&record->sale_conditions);
  for (size_t i = 0; i < 8; i++) { record->trade_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->fractional_trade_volume[i] = arbitrary(); }
  record->sellers_sale_days = arbitrary();
  record->stop_stock_indicator = arbitrary();
  record->trade_through_exempt_indicator = arbitrary();
  record->short_sale_restriction_indicator = arbitrary();
  record->trade_reporting_facility_id = arbitrary();
  any_prior_day_trade_date_and_time(&record->prior_day_trade_date_and_time);
}

/* Fractional Prior Day Trade Message to the wire: 67 bytes from at, returning where the next byte goes */
static size_t encode_fractional_prior_day_trade_message(const FractionalPriorDayTradeMessage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->participant_id;
  at = encode_timestamp1(&record->timestamp_1, wire, at);
  wire[at++] = record->message_id;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->transaction_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->participant_reference_number[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->security_symbol[i]; }
  wire[at++] = record->instrument_type;
  at = encode_sale_conditions(&record->sale_conditions, wire, at);
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

/* Fractional Prior Day Trade Message off the wire: 67 bytes from at, returning where the next byte lies */
static size_t decode_fractional_prior_day_trade_message(FractionalPriorDayTradeMessage *record, const uint8_t *wire, size_t at) {
  record->participant_id = wire[at++];
  at = decode_timestamp1(&record->timestamp_1, wire, at);
  record->message_id = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->transaction_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->participant_reference_number[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->security_symbol[i] = wire[at++]; }
  record->instrument_type = wire[at++];
  at = decode_sale_conditions(&record->sale_conditions, wire, at);
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
  assert(read->participant_id == written->participant_id);
  equal_timestamp1(&read->timestamp_1, &written->timestamp_1);
  assert(read->message_id == written->message_id);
  for (size_t i = 0; i < 4; i++) { assert(read->transaction_id[i] == written->transaction_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->participant_reference_number[i] == written->participant_reference_number[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->security_symbol[i] == written->security_symbol[i]); }
  assert(read->instrument_type == written->instrument_type);
  equal_sale_conditions(&read->sale_conditions, &written->sale_conditions);
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
  uint8_t wire[67];
  uint8_t again[67];

  any_fractional_prior_day_trade_message(&sent);
  assert(encode_fractional_prior_day_trade_message(&sent, wire, 0) == 67);
  assert(decode_fractional_prior_day_trade_message(&got, wire, 0) == 67);
  equal_fractional_prior_day_trade_message(&got, &sent);

  for (size_t i = 0; i < 67; i++) { wire[i] = arbitrary(); }
  assert(decode_fractional_prior_day_trade_message(&got, wire, 0) == 67);
  assert(encode_fractional_prior_day_trade_message(&got, again, 0) == 67);
  for (size_t i = 0; i < 67; i++) { assert(again[i] == wire[i]); }
}

/* ---- Prior Day Trade Cancel Error Message: 64 bytes -------------------------- */

/* The Prior Day Trade message is used to report a Cta Equity, Local Issue or Bond transaction which occurred earlier than the current trading day and was not reported. */
typedef struct {
  uint8_t participant_id;                                  /* byte 0 */
  Timestamp1 timestamp_1;                                  /* bytes 1 to 8 */
  uint8_t message_id;                                      /* byte 9 */
  uint8_t transaction_id[4];                               /* bytes 10 to 13 */
  uint8_t participant_reference_number[8];                 /* bytes 14 to 21 */
  uint8_t security_symbol[11];                             /* bytes 22 to 32 */
  uint8_t instrument_type;                                 /* byte 33 */
  SaleConditions sale_conditions;                          /* bytes 34 to 37 */
  uint8_t trade_price[8];                                  /* bytes 38 to 45 */
  uint8_t trade_volume[4];                                 /* bytes 46 to 49 */
  uint8_t sellers_sale_days;                               /* byte 50 */
  uint8_t stop_stock_indicator;                            /* byte 51 */
  uint8_t trade_through_exempt_indicator;                  /* byte 52 */
  uint8_t short_sale_restriction_indicator;                /* byte 53 */
  uint8_t trade_reporting_facility_id;                     /* byte 54 */
  PriorDayTradeDateAndTime prior_day_trade_date_and_time;  /* bytes 55 to 62 */
  uint8_t cancel_error_action;                             /* byte 63 */
} PriorDayTradeCancelErrorMessage;

/* any Prior Day Trade Cancel Error Message at all: every byte one the checker chooses */
static void any_prior_day_trade_cancel_error_message(PriorDayTradeCancelErrorMessage *record) {
  record->participant_id = arbitrary();
  any_timestamp1(&record->timestamp_1);
  record->message_id = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->transaction_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->participant_reference_number[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->security_symbol[i] = arbitrary(); }
  record->instrument_type = arbitrary();
  any_sale_conditions(&record->sale_conditions);
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

/* Prior Day Trade Cancel Error Message to the wire: 64 bytes from at, returning where the next byte goes */
static size_t encode_prior_day_trade_cancel_error_message(const PriorDayTradeCancelErrorMessage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->participant_id;
  at = encode_timestamp1(&record->timestamp_1, wire, at);
  wire[at++] = record->message_id;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->transaction_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->participant_reference_number[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->security_symbol[i]; }
  wire[at++] = record->instrument_type;
  at = encode_sale_conditions(&record->sale_conditions, wire, at);
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

/* Prior Day Trade Cancel Error Message off the wire: 64 bytes from at, returning where the next byte lies */
static size_t decode_prior_day_trade_cancel_error_message(PriorDayTradeCancelErrorMessage *record, const uint8_t *wire, size_t at) {
  record->participant_id = wire[at++];
  at = decode_timestamp1(&record->timestamp_1, wire, at);
  record->message_id = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->transaction_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->participant_reference_number[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->security_symbol[i] = wire[at++]; }
  record->instrument_type = wire[at++];
  at = decode_sale_conditions(&record->sale_conditions, wire, at);
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
  assert(read->participant_id == written->participant_id);
  equal_timestamp1(&read->timestamp_1, &written->timestamp_1);
  assert(read->message_id == written->message_id);
  for (size_t i = 0; i < 4; i++) { assert(read->transaction_id[i] == written->transaction_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->participant_reference_number[i] == written->participant_reference_number[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->security_symbol[i] == written->security_symbol[i]); }
  assert(read->instrument_type == written->instrument_type);
  equal_sale_conditions(&read->sale_conditions, &written->sale_conditions);
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
  uint8_t wire[64];
  uint8_t again[64];

  any_prior_day_trade_cancel_error_message(&sent);
  assert(encode_prior_day_trade_cancel_error_message(&sent, wire, 0) == 64);
  assert(decode_prior_day_trade_cancel_error_message(&got, wire, 0) == 64);
  equal_prior_day_trade_cancel_error_message(&got, &sent);

  for (size_t i = 0; i < 64; i++) { wire[i] = arbitrary(); }
  assert(decode_prior_day_trade_cancel_error_message(&got, wire, 0) == 64);
  assert(encode_prior_day_trade_cancel_error_message(&got, again, 0) == 64);
  for (size_t i = 0; i < 64; i++) { assert(again[i] == wire[i]); }
}

/* ---- Fractional Prior Day Trade Cancel Error Message: 68 bytes --------------- */

/* The Fractional Prior Day Trade message is used to report a Cta Equity, Local Issue or Bond transaction which occurred earlier than the current trading day and was not reported. */
typedef struct {
  uint8_t participant_id;                                  /* byte 0 */
  Timestamp1 timestamp_1;                                  /* bytes 1 to 8 */
  uint8_t message_id;                                      /* byte 9 */
  uint8_t transaction_id[4];                               /* bytes 10 to 13 */
  uint8_t participant_reference_number[8];                 /* bytes 14 to 21 */
  uint8_t security_symbol[11];                             /* bytes 22 to 32 */
  uint8_t instrument_type;                                 /* byte 33 */
  SaleConditions sale_conditions;                          /* bytes 34 to 37 */
  uint8_t trade_price[8];                                  /* bytes 38 to 45 */
  uint8_t fractional_trade_volume[8];                      /* bytes 46 to 53 */
  uint8_t sellers_sale_days;                               /* byte 54 */
  uint8_t stop_stock_indicator;                            /* byte 55 */
  uint8_t trade_through_exempt_indicator;                  /* byte 56 */
  uint8_t short_sale_restriction_indicator;                /* byte 57 */
  uint8_t trade_reporting_facility_id;                     /* byte 58 */
  PriorDayTradeDateAndTime prior_day_trade_date_and_time;  /* bytes 59 to 66 */
  uint8_t cancel_error_action;                             /* byte 67 */
} FractionalPriorDayTradeCancelErrorMessage;

/* any Fractional Prior Day Trade Cancel Error Message at all: every byte one the checker chooses */
static void any_fractional_prior_day_trade_cancel_error_message(FractionalPriorDayTradeCancelErrorMessage *record) {
  record->participant_id = arbitrary();
  any_timestamp1(&record->timestamp_1);
  record->message_id = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->transaction_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->participant_reference_number[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->security_symbol[i] = arbitrary(); }
  record->instrument_type = arbitrary();
  any_sale_conditions(&record->sale_conditions);
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

/* Fractional Prior Day Trade Cancel Error Message to the wire: 68 bytes from at, returning where the next byte goes */
static size_t encode_fractional_prior_day_trade_cancel_error_message(const FractionalPriorDayTradeCancelErrorMessage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->participant_id;
  at = encode_timestamp1(&record->timestamp_1, wire, at);
  wire[at++] = record->message_id;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->transaction_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->participant_reference_number[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->security_symbol[i]; }
  wire[at++] = record->instrument_type;
  at = encode_sale_conditions(&record->sale_conditions, wire, at);
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

/* Fractional Prior Day Trade Cancel Error Message off the wire: 68 bytes from at, returning where the next byte lies */
static size_t decode_fractional_prior_day_trade_cancel_error_message(FractionalPriorDayTradeCancelErrorMessage *record, const uint8_t *wire, size_t at) {
  record->participant_id = wire[at++];
  at = decode_timestamp1(&record->timestamp_1, wire, at);
  record->message_id = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->transaction_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->participant_reference_number[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->security_symbol[i] = wire[at++]; }
  record->instrument_type = wire[at++];
  at = decode_sale_conditions(&record->sale_conditions, wire, at);
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
  assert(read->participant_id == written->participant_id);
  equal_timestamp1(&read->timestamp_1, &written->timestamp_1);
  assert(read->message_id == written->message_id);
  for (size_t i = 0; i < 4; i++) { assert(read->transaction_id[i] == written->transaction_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->participant_reference_number[i] == written->participant_reference_number[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->security_symbol[i] == written->security_symbol[i]); }
  assert(read->instrument_type == written->instrument_type);
  equal_sale_conditions(&read->sale_conditions, &written->sale_conditions);
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
  uint8_t wire[68];
  uint8_t again[68];

  any_fractional_prior_day_trade_cancel_error_message(&sent);
  assert(encode_fractional_prior_day_trade_cancel_error_message(&sent, wire, 0) == 68);
  assert(decode_fractional_prior_day_trade_cancel_error_message(&got, wire, 0) == 68);
  equal_fractional_prior_day_trade_cancel_error_message(&got, &sent);

  for (size_t i = 0; i < 68; i++) { wire[i] = arbitrary(); }
  assert(decode_fractional_prior_day_trade_cancel_error_message(&got, wire, 0) == 68);
  assert(encode_fractional_prior_day_trade_cancel_error_message(&got, again, 0) == 68);
  for (size_t i = 0; i < 68; i++) { assert(again[i] == wire[i]); }
}

/* ---- Consolidated Start Of Day Summary Message: 51 bytes --------------------- */

/* The Consolidated Start of Day Summary messages are transmitted shortly after the Multicast Line ‘Start of Day’ message */
typedef struct {
  uint8_t participant_id;                         /* byte 0 */
  Timestamp1 timestamp_1;                         /* bytes 1 to 8 */
  uint8_t message_id;                             /* byte 9 */
  uint8_t transaction_id[4];                      /* bytes 10 to 13 */
  uint8_t participant_reference_number[8];        /* bytes 14 to 21 */
  uint8_t security_symbol[11];                    /* bytes 22 to 32 */
  uint8_t instrument_type;                        /* byte 33 */
  uint8_t summary_participant_id;                 /* byte 34 */
  uint8_t previous_close_price_date[4];           /* bytes 35 to 38 */
  uint8_t previous_close_price[8];                /* bytes 39 to 46 */
  uint8_t short_sale_restriction_indicator;       /* byte 47 */
  uint8_t primary_listing_market_participant_id;  /* byte 48 */
  uint8_t financial_status_indicator;             /* byte 49 */
  uint8_t number_of_participants;                 /* byte 50 */
} ConsolidatedStartOfDaySummaryMessage;

/* any Consolidated Start Of Day Summary Message at all: every byte one the checker chooses */
static void any_consolidated_start_of_day_summary_message(ConsolidatedStartOfDaySummaryMessage *record) {
  record->participant_id = arbitrary();
  any_timestamp1(&record->timestamp_1);
  record->message_id = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->transaction_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->participant_reference_number[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->security_symbol[i] = arbitrary(); }
  record->instrument_type = arbitrary();
  record->summary_participant_id = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->previous_close_price_date[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->previous_close_price[i] = arbitrary(); }
  record->short_sale_restriction_indicator = arbitrary();
  record->primary_listing_market_participant_id = arbitrary();
  record->financial_status_indicator = arbitrary();
  record->number_of_participants = arbitrary();
}

/* Consolidated Start Of Day Summary Message to the wire: 51 bytes from at, returning where the next byte goes */
static size_t encode_consolidated_start_of_day_summary_message(const ConsolidatedStartOfDaySummaryMessage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->participant_id;
  at = encode_timestamp1(&record->timestamp_1, wire, at);
  wire[at++] = record->message_id;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->transaction_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->participant_reference_number[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->security_symbol[i]; }
  wire[at++] = record->instrument_type;
  wire[at++] = record->summary_participant_id;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->previous_close_price_date[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->previous_close_price[i]; }
  wire[at++] = record->short_sale_restriction_indicator;
  wire[at++] = record->primary_listing_market_participant_id;
  wire[at++] = record->financial_status_indicator;
  wire[at++] = record->number_of_participants;

  return at;
}

/* Consolidated Start Of Day Summary Message off the wire: 51 bytes from at, returning where the next byte lies */
static size_t decode_consolidated_start_of_day_summary_message(ConsolidatedStartOfDaySummaryMessage *record, const uint8_t *wire, size_t at) {
  record->participant_id = wire[at++];
  at = decode_timestamp1(&record->timestamp_1, wire, at);
  record->message_id = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->transaction_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->participant_reference_number[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->security_symbol[i] = wire[at++]; }
  record->instrument_type = wire[at++];
  record->summary_participant_id = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->previous_close_price_date[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->previous_close_price[i] = wire[at++]; }
  record->short_sale_restriction_indicator = wire[at++];
  record->primary_listing_market_participant_id = wire[at++];
  record->financial_status_indicator = wire[at++];
  record->number_of_participants = wire[at++];

  return at;
}

/* what was read of Consolidated Start Of Day Summary Message is what was written, byte for byte */
static void equal_consolidated_start_of_day_summary_message(const ConsolidatedStartOfDaySummaryMessage *read, const ConsolidatedStartOfDaySummaryMessage *written) {
  assert(read->participant_id == written->participant_id);
  equal_timestamp1(&read->timestamp_1, &written->timestamp_1);
  assert(read->message_id == written->message_id);
  for (size_t i = 0; i < 4; i++) { assert(read->transaction_id[i] == written->transaction_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->participant_reference_number[i] == written->participant_reference_number[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->security_symbol[i] == written->security_symbol[i]); }
  assert(read->instrument_type == written->instrument_type);
  assert(read->summary_participant_id == written->summary_participant_id);
  for (size_t i = 0; i < 4; i++) { assert(read->previous_close_price_date[i] == written->previous_close_price_date[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->previous_close_price[i] == written->previous_close_price[i]); }
  assert(read->short_sale_restriction_indicator == written->short_sale_restriction_indicator);
  assert(read->primary_listing_market_participant_id == written->primary_listing_market_participant_id);
  assert(read->financial_status_indicator == written->financial_status_indicator);
  assert(read->number_of_participants == written->number_of_participants);
}

/* Consolidated Start Of Day Summary Message: written and read back, then read and written back */
static void check_consolidated_start_of_day_summary_message(void) {
  ConsolidatedStartOfDaySummaryMessage sent;
  ConsolidatedStartOfDaySummaryMessage got;
  uint8_t wire[51];
  uint8_t again[51];

  any_consolidated_start_of_day_summary_message(&sent);
  assert(encode_consolidated_start_of_day_summary_message(&sent, wire, 0) == 51);
  assert(decode_consolidated_start_of_day_summary_message(&got, wire, 0) == 51);
  equal_consolidated_start_of_day_summary_message(&got, &sent);

  for (size_t i = 0; i < 51; i++) { wire[i] = arbitrary(); }
  assert(decode_consolidated_start_of_day_summary_message(&got, wire, 0) == 51);
  assert(encode_consolidated_start_of_day_summary_message(&got, again, 0) == 51);
  for (size_t i = 0; i < 51; i++) { assert(again[i] == wire[i]); }
}

/* ---- Participant Start Of Day Summary Message: 47 bytes ---------------------- */

/* The Participant Start of Day Summary messages are transmitted shortly after the Multicast Line ‘Start of Day’ message */
typedef struct {
  uint8_t participant_id;                   /* byte 0 */
  Timestamp1 timestamp_1;                   /* bytes 1 to 8 */
  uint8_t message_id;                       /* byte 9 */
  uint8_t transaction_id[4];                /* bytes 10 to 13 */
  uint8_t participant_reference_number[8];  /* bytes 14 to 21 */
  uint8_t security_symbol[11];              /* bytes 22 to 32 */
  uint8_t instrument_type;                  /* byte 33 */
  uint8_t summary_participant_id;           /* byte 34 */
  uint8_t previous_close_price_date[4];     /* bytes 35 to 38 */
  uint8_t previous_close_price[8];          /* bytes 39 to 46 */
} ParticipantStartOfDaySummaryMessage;

/* any Participant Start Of Day Summary Message at all: every byte one the checker chooses */
static void any_participant_start_of_day_summary_message(ParticipantStartOfDaySummaryMessage *record) {
  record->participant_id = arbitrary();
  any_timestamp1(&record->timestamp_1);
  record->message_id = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->transaction_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->participant_reference_number[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->security_symbol[i] = arbitrary(); }
  record->instrument_type = arbitrary();
  record->summary_participant_id = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->previous_close_price_date[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->previous_close_price[i] = arbitrary(); }
}

/* Participant Start Of Day Summary Message to the wire: 47 bytes from at, returning where the next byte goes */
static size_t encode_participant_start_of_day_summary_message(const ParticipantStartOfDaySummaryMessage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->participant_id;
  at = encode_timestamp1(&record->timestamp_1, wire, at);
  wire[at++] = record->message_id;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->transaction_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->participant_reference_number[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->security_symbol[i]; }
  wire[at++] = record->instrument_type;
  wire[at++] = record->summary_participant_id;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->previous_close_price_date[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->previous_close_price[i]; }

  return at;
}

/* Participant Start Of Day Summary Message off the wire: 47 bytes from at, returning where the next byte lies */
static size_t decode_participant_start_of_day_summary_message(ParticipantStartOfDaySummaryMessage *record, const uint8_t *wire, size_t at) {
  record->participant_id = wire[at++];
  at = decode_timestamp1(&record->timestamp_1, wire, at);
  record->message_id = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->transaction_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->participant_reference_number[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->security_symbol[i] = wire[at++]; }
  record->instrument_type = wire[at++];
  record->summary_participant_id = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->previous_close_price_date[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->previous_close_price[i] = wire[at++]; }

  return at;
}

/* what was read of Participant Start Of Day Summary Message is what was written, byte for byte */
static void equal_participant_start_of_day_summary_message(const ParticipantStartOfDaySummaryMessage *read, const ParticipantStartOfDaySummaryMessage *written) {
  assert(read->participant_id == written->participant_id);
  equal_timestamp1(&read->timestamp_1, &written->timestamp_1);
  assert(read->message_id == written->message_id);
  for (size_t i = 0; i < 4; i++) { assert(read->transaction_id[i] == written->transaction_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->participant_reference_number[i] == written->participant_reference_number[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->security_symbol[i] == written->security_symbol[i]); }
  assert(read->instrument_type == written->instrument_type);
  assert(read->summary_participant_id == written->summary_participant_id);
  for (size_t i = 0; i < 4; i++) { assert(read->previous_close_price_date[i] == written->previous_close_price_date[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->previous_close_price[i] == written->previous_close_price[i]); }
}

/* Participant Start Of Day Summary Message: written and read back, then read and written back */
static void check_participant_start_of_day_summary_message(void) {
  ParticipantStartOfDaySummaryMessage sent;
  ParticipantStartOfDaySummaryMessage got;
  uint8_t wire[47];
  uint8_t again[47];

  any_participant_start_of_day_summary_message(&sent);
  assert(encode_participant_start_of_day_summary_message(&sent, wire, 0) == 47);
  assert(decode_participant_start_of_day_summary_message(&got, wire, 0) == 47);
  equal_participant_start_of_day_summary_message(&got, &sent);

  for (size_t i = 0; i < 47; i++) { wire[i] = arbitrary(); }
  assert(decode_participant_start_of_day_summary_message(&got, wire, 0) == 47);
  assert(encode_participant_start_of_day_summary_message(&got, again, 0) == 47);
  for (size_t i = 0; i < 47; i++) { assert(again[i] == wire[i]); }
}

/* ---- Consolidated End Of Day Summary Message: 75 bytes ----------------------- */

/* The Consolidated End of Day Summary messages are transmitted shortly before the "Goodnight" messages */
typedef struct {
  uint8_t participant_id;                         /* byte 0 */
  Timestamp1 timestamp_1;                         /* bytes 1 to 8 */
  uint8_t message_id;                             /* byte 9 */
  uint8_t transaction_id[4];                      /* bytes 10 to 13 */
  uint8_t participant_reference_number[8];        /* bytes 14 to 21 */
  uint8_t security_symbol[11];                    /* bytes 22 to 32 */
  uint8_t instrument_type;                        /* byte 33 */
  uint8_t last_participant_id;                    /* byte 34 */
  uint8_t previous_close_price_date[4];           /* bytes 35 to 38 */
  uint8_t last_price[8];                          /* bytes 39 to 46 */
  uint8_t high_price[8];                          /* bytes 47 to 54 */
  uint8_t low_price[8];                           /* bytes 55 to 62 */
  uint8_t total_volume[8];                        /* bytes 63 to 70 */
  uint8_t short_sale_restriction_indicator;       /* byte 71 */
  uint8_t primary_listing_market_participant_id;  /* byte 72 */
  uint8_t financial_status_indicator;             /* byte 73 */
  uint8_t number_of_participants;                 /* byte 74 */
} ConsolidatedEndOfDaySummaryMessage;

/* any Consolidated End Of Day Summary Message at all: every byte one the checker chooses */
static void any_consolidated_end_of_day_summary_message(ConsolidatedEndOfDaySummaryMessage *record) {
  record->participant_id = arbitrary();
  any_timestamp1(&record->timestamp_1);
  record->message_id = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->transaction_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->participant_reference_number[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->security_symbol[i] = arbitrary(); }
  record->instrument_type = arbitrary();
  record->last_participant_id = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->previous_close_price_date[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->last_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->high_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->low_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->total_volume[i] = arbitrary(); }
  record->short_sale_restriction_indicator = arbitrary();
  record->primary_listing_market_participant_id = arbitrary();
  record->financial_status_indicator = arbitrary();
  record->number_of_participants = arbitrary();
}

/* Consolidated End Of Day Summary Message to the wire: 75 bytes from at, returning where the next byte goes */
static size_t encode_consolidated_end_of_day_summary_message(const ConsolidatedEndOfDaySummaryMessage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->participant_id;
  at = encode_timestamp1(&record->timestamp_1, wire, at);
  wire[at++] = record->message_id;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->transaction_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->participant_reference_number[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->security_symbol[i]; }
  wire[at++] = record->instrument_type;
  wire[at++] = record->last_participant_id;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->previous_close_price_date[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->last_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->high_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->low_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->total_volume[i]; }
  wire[at++] = record->short_sale_restriction_indicator;
  wire[at++] = record->primary_listing_market_participant_id;
  wire[at++] = record->financial_status_indicator;
  wire[at++] = record->number_of_participants;

  return at;
}

/* Consolidated End Of Day Summary Message off the wire: 75 bytes from at, returning where the next byte lies */
static size_t decode_consolidated_end_of_day_summary_message(ConsolidatedEndOfDaySummaryMessage *record, const uint8_t *wire, size_t at) {
  record->participant_id = wire[at++];
  at = decode_timestamp1(&record->timestamp_1, wire, at);
  record->message_id = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->transaction_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->participant_reference_number[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->security_symbol[i] = wire[at++]; }
  record->instrument_type = wire[at++];
  record->last_participant_id = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->previous_close_price_date[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->last_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->high_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->low_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->total_volume[i] = wire[at++]; }
  record->short_sale_restriction_indicator = wire[at++];
  record->primary_listing_market_participant_id = wire[at++];
  record->financial_status_indicator = wire[at++];
  record->number_of_participants = wire[at++];

  return at;
}

/* what was read of Consolidated End Of Day Summary Message is what was written, byte for byte */
static void equal_consolidated_end_of_day_summary_message(const ConsolidatedEndOfDaySummaryMessage *read, const ConsolidatedEndOfDaySummaryMessage *written) {
  assert(read->participant_id == written->participant_id);
  equal_timestamp1(&read->timestamp_1, &written->timestamp_1);
  assert(read->message_id == written->message_id);
  for (size_t i = 0; i < 4; i++) { assert(read->transaction_id[i] == written->transaction_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->participant_reference_number[i] == written->participant_reference_number[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->security_symbol[i] == written->security_symbol[i]); }
  assert(read->instrument_type == written->instrument_type);
  assert(read->last_participant_id == written->last_participant_id);
  for (size_t i = 0; i < 4; i++) { assert(read->previous_close_price_date[i] == written->previous_close_price_date[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->last_price[i] == written->last_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->high_price[i] == written->high_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->low_price[i] == written->low_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->total_volume[i] == written->total_volume[i]); }
  assert(read->short_sale_restriction_indicator == written->short_sale_restriction_indicator);
  assert(read->primary_listing_market_participant_id == written->primary_listing_market_participant_id);
  assert(read->financial_status_indicator == written->financial_status_indicator);
  assert(read->number_of_participants == written->number_of_participants);
}

/* Consolidated End Of Day Summary Message: written and read back, then read and written back */
static void check_consolidated_end_of_day_summary_message(void) {
  ConsolidatedEndOfDaySummaryMessage sent;
  ConsolidatedEndOfDaySummaryMessage got;
  uint8_t wire[75];
  uint8_t again[75];

  any_consolidated_end_of_day_summary_message(&sent);
  assert(encode_consolidated_end_of_day_summary_message(&sent, wire, 0) == 75);
  assert(decode_consolidated_end_of_day_summary_message(&got, wire, 0) == 75);
  equal_consolidated_end_of_day_summary_message(&got, &sent);

  for (size_t i = 0; i < 75; i++) { wire[i] = arbitrary(); }
  assert(decode_consolidated_end_of_day_summary_message(&got, wire, 0) == 75);
  assert(encode_consolidated_end_of_day_summary_message(&got, again, 0) == 75);
  for (size_t i = 0; i < 75; i++) { assert(again[i] == wire[i]); }
}

/* ---- Fractional Consolidated End Of Day Summary Message: 75 bytes ------------ */

/* The Consolidated End of Day Summary messages are transmitted shortly before the "Goodnight" messages */
typedef struct {
  uint8_t participant_id;                         /* byte 0 */
  Timestamp1 timestamp_1;                         /* bytes 1 to 8 */
  uint8_t message_id;                             /* byte 9 */
  uint8_t transaction_id[4];                      /* bytes 10 to 13 */
  uint8_t participant_reference_number[8];        /* bytes 14 to 21 */
  uint8_t security_symbol[11];                    /* bytes 22 to 32 */
  uint8_t instrument_type;                        /* byte 33 */
  uint8_t last_participant_id;                    /* byte 34 */
  uint8_t previous_close_price_date[4];           /* bytes 35 to 38 */
  uint8_t last_price[8];                          /* bytes 39 to 46 */
  uint8_t high_price[8];                          /* bytes 47 to 54 */
  uint8_t low_price[8];                           /* bytes 55 to 62 */
  uint8_t fractional_total_volume[8];             /* bytes 63 to 70 */
  uint8_t short_sale_restriction_indicator;       /* byte 71 */
  uint8_t primary_listing_market_participant_id;  /* byte 72 */
  uint8_t financial_status_indicator;             /* byte 73 */
  uint8_t number_of_participants;                 /* byte 74 */
} FractionalConsolidatedEndOfDaySummaryMessage;

/* any Fractional Consolidated End Of Day Summary Message at all: every byte one the checker chooses */
static void any_fractional_consolidated_end_of_day_summary_message(FractionalConsolidatedEndOfDaySummaryMessage *record) {
  record->participant_id = arbitrary();
  any_timestamp1(&record->timestamp_1);
  record->message_id = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->transaction_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->participant_reference_number[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->security_symbol[i] = arbitrary(); }
  record->instrument_type = arbitrary();
  record->last_participant_id = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->previous_close_price_date[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->last_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->high_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->low_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->fractional_total_volume[i] = arbitrary(); }
  record->short_sale_restriction_indicator = arbitrary();
  record->primary_listing_market_participant_id = arbitrary();
  record->financial_status_indicator = arbitrary();
  record->number_of_participants = arbitrary();
}

/* Fractional Consolidated End Of Day Summary Message to the wire: 75 bytes from at, returning where the next byte goes */
static size_t encode_fractional_consolidated_end_of_day_summary_message(const FractionalConsolidatedEndOfDaySummaryMessage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->participant_id;
  at = encode_timestamp1(&record->timestamp_1, wire, at);
  wire[at++] = record->message_id;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->transaction_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->participant_reference_number[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->security_symbol[i]; }
  wire[at++] = record->instrument_type;
  wire[at++] = record->last_participant_id;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->previous_close_price_date[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->last_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->high_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->low_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->fractional_total_volume[i]; }
  wire[at++] = record->short_sale_restriction_indicator;
  wire[at++] = record->primary_listing_market_participant_id;
  wire[at++] = record->financial_status_indicator;
  wire[at++] = record->number_of_participants;

  return at;
}

/* Fractional Consolidated End Of Day Summary Message off the wire: 75 bytes from at, returning where the next byte lies */
static size_t decode_fractional_consolidated_end_of_day_summary_message(FractionalConsolidatedEndOfDaySummaryMessage *record, const uint8_t *wire, size_t at) {
  record->participant_id = wire[at++];
  at = decode_timestamp1(&record->timestamp_1, wire, at);
  record->message_id = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->transaction_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->participant_reference_number[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->security_symbol[i] = wire[at++]; }
  record->instrument_type = wire[at++];
  record->last_participant_id = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->previous_close_price_date[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->last_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->high_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->low_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->fractional_total_volume[i] = wire[at++]; }
  record->short_sale_restriction_indicator = wire[at++];
  record->primary_listing_market_participant_id = wire[at++];
  record->financial_status_indicator = wire[at++];
  record->number_of_participants = wire[at++];

  return at;
}

/* what was read of Fractional Consolidated End Of Day Summary Message is what was written, byte for byte */
static void equal_fractional_consolidated_end_of_day_summary_message(const FractionalConsolidatedEndOfDaySummaryMessage *read, const FractionalConsolidatedEndOfDaySummaryMessage *written) {
  assert(read->participant_id == written->participant_id);
  equal_timestamp1(&read->timestamp_1, &written->timestamp_1);
  assert(read->message_id == written->message_id);
  for (size_t i = 0; i < 4; i++) { assert(read->transaction_id[i] == written->transaction_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->participant_reference_number[i] == written->participant_reference_number[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->security_symbol[i] == written->security_symbol[i]); }
  assert(read->instrument_type == written->instrument_type);
  assert(read->last_participant_id == written->last_participant_id);
  for (size_t i = 0; i < 4; i++) { assert(read->previous_close_price_date[i] == written->previous_close_price_date[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->last_price[i] == written->last_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->high_price[i] == written->high_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->low_price[i] == written->low_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->fractional_total_volume[i] == written->fractional_total_volume[i]); }
  assert(read->short_sale_restriction_indicator == written->short_sale_restriction_indicator);
  assert(read->primary_listing_market_participant_id == written->primary_listing_market_participant_id);
  assert(read->financial_status_indicator == written->financial_status_indicator);
  assert(read->number_of_participants == written->number_of_participants);
}

/* Fractional Consolidated End Of Day Summary Message: written and read back, then read and written back */
static void check_fractional_consolidated_end_of_day_summary_message(void) {
  FractionalConsolidatedEndOfDaySummaryMessage sent;
  FractionalConsolidatedEndOfDaySummaryMessage got;
  uint8_t wire[75];
  uint8_t again[75];

  any_fractional_consolidated_end_of_day_summary_message(&sent);
  assert(encode_fractional_consolidated_end_of_day_summary_message(&sent, wire, 0) == 75);
  assert(decode_fractional_consolidated_end_of_day_summary_message(&got, wire, 0) == 75);
  equal_fractional_consolidated_end_of_day_summary_message(&got, &sent);

  for (size_t i = 0; i < 75; i++) { wire[i] = arbitrary(); }
  assert(decode_fractional_consolidated_end_of_day_summary_message(&got, wire, 0) == 75);
  assert(encode_fractional_consolidated_end_of_day_summary_message(&got, again, 0) == 75);
  for (size_t i = 0; i < 75; i++) { assert(again[i] == wire[i]); }
}

/* ---- Participant End Of Day Summary Message: 80 bytes ------------------------ */

/* The Participant End of Day Summary messages are transmitted shortly before the ‘Goodnight’ messages. */
typedef struct {
  uint8_t participant_id;                   /* byte 0 */
  Timestamp1 timestamp_1;                   /* bytes 1 to 8 */
  uint8_t message_id;                       /* byte 9 */
  uint8_t transaction_id[4];                /* bytes 10 to 13 */
  uint8_t participant_reference_number[8];  /* bytes 14 to 21 */
  uint8_t security_symbol[11];              /* bytes 22 to 32 */
  uint8_t instrument_type;                  /* byte 33 */
  uint8_t initiating_participant_id;        /* byte 34 */
  uint8_t previous_close_price_date[4];     /* bytes 35 to 38 */
  uint8_t last_price[8];                    /* bytes 39 to 46 */
  uint8_t high_price[8];                    /* bytes 47 to 54 */
  uint8_t low_price[8];                     /* bytes 55 to 62 */
  uint8_t open_price[8];                    /* bytes 63 to 70 */
  uint8_t total_volume[8];                  /* bytes 71 to 78 */
  uint8_t tick;                             /* byte 79 */
} ParticipantEndOfDaySummaryMessage;

/* any Participant End Of Day Summary Message at all: every byte one the checker chooses */
static void any_participant_end_of_day_summary_message(ParticipantEndOfDaySummaryMessage *record) {
  record->participant_id = arbitrary();
  any_timestamp1(&record->timestamp_1);
  record->message_id = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->transaction_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->participant_reference_number[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->security_symbol[i] = arbitrary(); }
  record->instrument_type = arbitrary();
  record->initiating_participant_id = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->previous_close_price_date[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->last_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->high_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->low_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->open_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->total_volume[i] = arbitrary(); }
  record->tick = arbitrary();
}

/* Participant End Of Day Summary Message to the wire: 80 bytes from at, returning where the next byte goes */
static size_t encode_participant_end_of_day_summary_message(const ParticipantEndOfDaySummaryMessage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->participant_id;
  at = encode_timestamp1(&record->timestamp_1, wire, at);
  wire[at++] = record->message_id;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->transaction_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->participant_reference_number[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->security_symbol[i]; }
  wire[at++] = record->instrument_type;
  wire[at++] = record->initiating_participant_id;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->previous_close_price_date[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->last_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->high_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->low_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->open_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->total_volume[i]; }
  wire[at++] = record->tick;

  return at;
}

/* Participant End Of Day Summary Message off the wire: 80 bytes from at, returning where the next byte lies */
static size_t decode_participant_end_of_day_summary_message(ParticipantEndOfDaySummaryMessage *record, const uint8_t *wire, size_t at) {
  record->participant_id = wire[at++];
  at = decode_timestamp1(&record->timestamp_1, wire, at);
  record->message_id = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->transaction_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->participant_reference_number[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->security_symbol[i] = wire[at++]; }
  record->instrument_type = wire[at++];
  record->initiating_participant_id = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->previous_close_price_date[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->last_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->high_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->low_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->open_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->total_volume[i] = wire[at++]; }
  record->tick = wire[at++];

  return at;
}

/* what was read of Participant End Of Day Summary Message is what was written, byte for byte */
static void equal_participant_end_of_day_summary_message(const ParticipantEndOfDaySummaryMessage *read, const ParticipantEndOfDaySummaryMessage *written) {
  assert(read->participant_id == written->participant_id);
  equal_timestamp1(&read->timestamp_1, &written->timestamp_1);
  assert(read->message_id == written->message_id);
  for (size_t i = 0; i < 4; i++) { assert(read->transaction_id[i] == written->transaction_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->participant_reference_number[i] == written->participant_reference_number[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->security_symbol[i] == written->security_symbol[i]); }
  assert(read->instrument_type == written->instrument_type);
  assert(read->initiating_participant_id == written->initiating_participant_id);
  for (size_t i = 0; i < 4; i++) { assert(read->previous_close_price_date[i] == written->previous_close_price_date[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->last_price[i] == written->last_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->high_price[i] == written->high_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->low_price[i] == written->low_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->open_price[i] == written->open_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->total_volume[i] == written->total_volume[i]); }
  assert(read->tick == written->tick);
}

/* Participant End Of Day Summary Message: written and read back, then read and written back */
static void check_participant_end_of_day_summary_message(void) {
  ParticipantEndOfDaySummaryMessage sent;
  ParticipantEndOfDaySummaryMessage got;
  uint8_t wire[80];
  uint8_t again[80];

  any_participant_end_of_day_summary_message(&sent);
  assert(encode_participant_end_of_day_summary_message(&sent, wire, 0) == 80);
  assert(decode_participant_end_of_day_summary_message(&got, wire, 0) == 80);
  equal_participant_end_of_day_summary_message(&got, &sent);

  for (size_t i = 0; i < 80; i++) { wire[i] = arbitrary(); }
  assert(decode_participant_end_of_day_summary_message(&got, wire, 0) == 80);
  assert(encode_participant_end_of_day_summary_message(&got, again, 0) == 80);
  for (size_t i = 0; i < 80; i++) { assert(again[i] == wire[i]); }
}

/* ---- Fractional Participant End Of Day Summary Message: 80 bytes ------------- */

/* The Participant End of Day Summary messages are transmitted shortly before the ‘Goodnight’ messages. */
typedef struct {
  uint8_t participant_id;                   /* byte 0 */
  Timestamp1 timestamp_1;                   /* bytes 1 to 8 */
  uint8_t message_id;                       /* byte 9 */
  uint8_t transaction_id[4];                /* bytes 10 to 13 */
  uint8_t participant_reference_number[8];  /* bytes 14 to 21 */
  uint8_t security_symbol[11];              /* bytes 22 to 32 */
  uint8_t instrument_type;                  /* byte 33 */
  uint8_t initiating_participant_id;        /* byte 34 */
  uint8_t previous_close_price_date[4];     /* bytes 35 to 38 */
  uint8_t last_price[8];                    /* bytes 39 to 46 */
  uint8_t high_price[8];                    /* bytes 47 to 54 */
  uint8_t low_price[8];                     /* bytes 55 to 62 */
  uint8_t open_price[8];                    /* bytes 63 to 70 */
  uint8_t fractional_total_volume[8];       /* bytes 71 to 78 */
  uint8_t tick;                             /* byte 79 */
} FractionalParticipantEndOfDaySummaryMessage;

/* any Fractional Participant End Of Day Summary Message at all: every byte one the checker chooses */
static void any_fractional_participant_end_of_day_summary_message(FractionalParticipantEndOfDaySummaryMessage *record) {
  record->participant_id = arbitrary();
  any_timestamp1(&record->timestamp_1);
  record->message_id = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->transaction_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->participant_reference_number[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->security_symbol[i] = arbitrary(); }
  record->instrument_type = arbitrary();
  record->initiating_participant_id = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->previous_close_price_date[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->last_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->high_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->low_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->open_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->fractional_total_volume[i] = arbitrary(); }
  record->tick = arbitrary();
}

/* Fractional Participant End Of Day Summary Message to the wire: 80 bytes from at, returning where the next byte goes */
static size_t encode_fractional_participant_end_of_day_summary_message(const FractionalParticipantEndOfDaySummaryMessage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->participant_id;
  at = encode_timestamp1(&record->timestamp_1, wire, at);
  wire[at++] = record->message_id;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->transaction_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->participant_reference_number[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->security_symbol[i]; }
  wire[at++] = record->instrument_type;
  wire[at++] = record->initiating_participant_id;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->previous_close_price_date[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->last_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->high_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->low_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->open_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->fractional_total_volume[i]; }
  wire[at++] = record->tick;

  return at;
}

/* Fractional Participant End Of Day Summary Message off the wire: 80 bytes from at, returning where the next byte lies */
static size_t decode_fractional_participant_end_of_day_summary_message(FractionalParticipantEndOfDaySummaryMessage *record, const uint8_t *wire, size_t at) {
  record->participant_id = wire[at++];
  at = decode_timestamp1(&record->timestamp_1, wire, at);
  record->message_id = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->transaction_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->participant_reference_number[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->security_symbol[i] = wire[at++]; }
  record->instrument_type = wire[at++];
  record->initiating_participant_id = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->previous_close_price_date[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->last_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->high_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->low_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->open_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->fractional_total_volume[i] = wire[at++]; }
  record->tick = wire[at++];

  return at;
}

/* what was read of Fractional Participant End Of Day Summary Message is what was written, byte for byte */
static void equal_fractional_participant_end_of_day_summary_message(const FractionalParticipantEndOfDaySummaryMessage *read, const FractionalParticipantEndOfDaySummaryMessage *written) {
  assert(read->participant_id == written->participant_id);
  equal_timestamp1(&read->timestamp_1, &written->timestamp_1);
  assert(read->message_id == written->message_id);
  for (size_t i = 0; i < 4; i++) { assert(read->transaction_id[i] == written->transaction_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->participant_reference_number[i] == written->participant_reference_number[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->security_symbol[i] == written->security_symbol[i]); }
  assert(read->instrument_type == written->instrument_type);
  assert(read->initiating_participant_id == written->initiating_participant_id);
  for (size_t i = 0; i < 4; i++) { assert(read->previous_close_price_date[i] == written->previous_close_price_date[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->last_price[i] == written->last_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->high_price[i] == written->high_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->low_price[i] == written->low_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->open_price[i] == written->open_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->fractional_total_volume[i] == written->fractional_total_volume[i]); }
  assert(read->tick == written->tick);
}

/* Fractional Participant End Of Day Summary Message: written and read back, then read and written back */
static void check_fractional_participant_end_of_day_summary_message(void) {
  FractionalParticipantEndOfDaySummaryMessage sent;
  FractionalParticipantEndOfDaySummaryMessage got;
  uint8_t wire[80];
  uint8_t again[80];

  any_fractional_participant_end_of_day_summary_message(&sent);
  assert(encode_fractional_participant_end_of_day_summary_message(&sent, wire, 0) == 80);
  assert(decode_fractional_participant_end_of_day_summary_message(&got, wire, 0) == 80);
  equal_fractional_participant_end_of_day_summary_message(&got, &sent);

  for (size_t i = 0; i < 80; i++) { wire[i] = arbitrary(); }
  assert(decode_fractional_participant_end_of_day_summary_message(&got, wire, 0) == 80);
  assert(encode_fractional_participant_end_of_day_summary_message(&got, again, 0) == 80);
  for (size_t i = 0; i < 80; i++) { assert(again[i] == wire[i]); }
}

/* ---- Auction Status Message: 124 bytes --------------------------------------- */

/* The Auction Status message is used when a Participant in a Cta eligible security, Local Issue or a Bond requires Auction Information */
typedef struct {
  uint8_t participant_id;                           /* byte 0 */
  Timestamp1 timestamp_1;                           /* bytes 1 to 8 */
  uint8_t message_id;                               /* byte 9 */
  uint8_t transaction_id[4];                        /* bytes 10 to 13 */
  uint8_t participant_reference_number[8];          /* bytes 14 to 21 */
  uint8_t security_symbol[11];                      /* bytes 22 to 32 */
  uint8_t instrument_type;                          /* byte 33 */
  uint8_t auction_collar_reference_price[8];        /* bytes 34 to 41 */
  uint8_t auction_collar_upper_threshold_price[8];  /* bytes 42 to 49 */
  uint8_t auction_collar_lower_threshold_price[8];  /* bytes 50 to 57 */
  uint8_t number_of_extensions;                     /* byte 58 */
  uint8_t short_sale_restriction_indicator;         /* byte 59 */
  uint8_t primary_listing_market_participant_id;    /* byte 60 */
  uint8_t financial_status_indicator;               /* byte 61 */
  uint8_t future_use[62];                           /* bytes 62 to 123 */
} AuctionStatusMessage;

/* any Auction Status Message at all: every byte one the checker chooses */
static void any_auction_status_message(AuctionStatusMessage *record) {
  record->participant_id = arbitrary();
  any_timestamp1(&record->timestamp_1);
  record->message_id = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->transaction_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->participant_reference_number[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->security_symbol[i] = arbitrary(); }
  record->instrument_type = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->auction_collar_reference_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->auction_collar_upper_threshold_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->auction_collar_lower_threshold_price[i] = arbitrary(); }
  record->number_of_extensions = arbitrary();
  record->short_sale_restriction_indicator = arbitrary();
  record->primary_listing_market_participant_id = arbitrary();
  record->financial_status_indicator = arbitrary();
  for (size_t i = 0; i < 62; i++) { record->future_use[i] = arbitrary(); }
}

/* Auction Status Message to the wire: 124 bytes from at, returning where the next byte goes */
static size_t encode_auction_status_message(const AuctionStatusMessage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->participant_id;
  at = encode_timestamp1(&record->timestamp_1, wire, at);
  wire[at++] = record->message_id;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->transaction_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->participant_reference_number[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->security_symbol[i]; }
  wire[at++] = record->instrument_type;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->auction_collar_reference_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->auction_collar_upper_threshold_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->auction_collar_lower_threshold_price[i]; }
  wire[at++] = record->number_of_extensions;
  wire[at++] = record->short_sale_restriction_indicator;
  wire[at++] = record->primary_listing_market_participant_id;
  wire[at++] = record->financial_status_indicator;
  for (size_t i = 0; i < 62; i++) { wire[at++] = record->future_use[i]; }

  return at;
}

/* Auction Status Message off the wire: 124 bytes from at, returning where the next byte lies */
static size_t decode_auction_status_message(AuctionStatusMessage *record, const uint8_t *wire, size_t at) {
  record->participant_id = wire[at++];
  at = decode_timestamp1(&record->timestamp_1, wire, at);
  record->message_id = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->transaction_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->participant_reference_number[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->security_symbol[i] = wire[at++]; }
  record->instrument_type = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->auction_collar_reference_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->auction_collar_upper_threshold_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->auction_collar_lower_threshold_price[i] = wire[at++]; }
  record->number_of_extensions = wire[at++];
  record->short_sale_restriction_indicator = wire[at++];
  record->primary_listing_market_participant_id = wire[at++];
  record->financial_status_indicator = wire[at++];
  for (size_t i = 0; i < 62; i++) { record->future_use[i] = wire[at++]; }

  return at;
}

/* what was read of Auction Status Message is what was written, byte for byte */
static void equal_auction_status_message(const AuctionStatusMessage *read, const AuctionStatusMessage *written) {
  assert(read->participant_id == written->participant_id);
  equal_timestamp1(&read->timestamp_1, &written->timestamp_1);
  assert(read->message_id == written->message_id);
  for (size_t i = 0; i < 4; i++) { assert(read->transaction_id[i] == written->transaction_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->participant_reference_number[i] == written->participant_reference_number[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->security_symbol[i] == written->security_symbol[i]); }
  assert(read->instrument_type == written->instrument_type);
  for (size_t i = 0; i < 8; i++) { assert(read->auction_collar_reference_price[i] == written->auction_collar_reference_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->auction_collar_upper_threshold_price[i] == written->auction_collar_upper_threshold_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->auction_collar_lower_threshold_price[i] == written->auction_collar_lower_threshold_price[i]); }
  assert(read->number_of_extensions == written->number_of_extensions);
  assert(read->short_sale_restriction_indicator == written->short_sale_restriction_indicator);
  assert(read->primary_listing_market_participant_id == written->primary_listing_market_participant_id);
  assert(read->financial_status_indicator == written->financial_status_indicator);
  for (size_t i = 0; i < 62; i++) { assert(read->future_use[i] == written->future_use[i]); }
}

/* Auction Status Message: written and read back, then read and written back */
static void check_auction_status_message(void) {
  AuctionStatusMessage sent;
  AuctionStatusMessage got;
  uint8_t wire[124];
  uint8_t again[124];

  any_auction_status_message(&sent);
  assert(encode_auction_status_message(&sent, wire, 0) == 124);
  assert(decode_auction_status_message(&got, wire, 0) == 124);
  equal_auction_status_message(&got, &sent);

  for (size_t i = 0; i < 124; i++) { wire[i] = arbitrary(); }
  assert(decode_auction_status_message(&got, wire, 0) == 124);
  assert(encode_auction_status_message(&got, again, 0) == 124);
  for (size_t i = 0; i < 124; i++) { assert(again[i] == wire[i]); }
}

/* ---- Corrected Trade: 20 bytes ----------------------------------------------- */

/* Corrected Trade */
typedef struct {
  SaleConditions sale_conditions;            /* bytes 0 to 3 */
  uint8_t trade_price[8];                    /* bytes 4 to 11 */
  uint8_t trade_volume[4];                   /* bytes 12 to 15 */
  uint8_t sellers_sale_days;                 /* byte 16 */
  uint8_t stop_stock_indicator;              /* byte 17 */
  uint8_t trade_through_exempt_indicator;    /* byte 18 */
  uint8_t short_sale_restriction_indicator;  /* byte 19 */
} CorrectedTrade;

/* any Corrected Trade at all: every byte one the checker chooses */
static void any_corrected_trade(CorrectedTrade *record) {
  any_sale_conditions(&record->sale_conditions);
  for (size_t i = 0; i < 8; i++) { record->trade_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->trade_volume[i] = arbitrary(); }
  record->sellers_sale_days = arbitrary();
  record->stop_stock_indicator = arbitrary();
  record->trade_through_exempt_indicator = arbitrary();
  record->short_sale_restriction_indicator = arbitrary();
}

/* Corrected Trade to the wire: 20 bytes from at, returning where the next byte goes */
static size_t encode_corrected_trade(const CorrectedTrade *record, uint8_t *wire, size_t at) {
  at = encode_sale_conditions(&record->sale_conditions, wire, at);
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->trade_price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->trade_volume[i]; }
  wire[at++] = record->sellers_sale_days;
  wire[at++] = record->stop_stock_indicator;
  wire[at++] = record->trade_through_exempt_indicator;
  wire[at++] = record->short_sale_restriction_indicator;

  return at;
}

/* Corrected Trade off the wire: 20 bytes from at, returning where the next byte lies */
static size_t decode_corrected_trade(CorrectedTrade *record, const uint8_t *wire, size_t at) {
  at = decode_sale_conditions(&record->sale_conditions, wire, at);
  for (size_t i = 0; i < 8; i++) { record->trade_price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->trade_volume[i] = wire[at++]; }
  record->sellers_sale_days = wire[at++];
  record->stop_stock_indicator = wire[at++];
  record->trade_through_exempt_indicator = wire[at++];
  record->short_sale_restriction_indicator = wire[at++];

  return at;
}

/* what was read of Corrected Trade is what was written, byte for byte */
static void equal_corrected_trade(const CorrectedTrade *read, const CorrectedTrade *written) {
  equal_sale_conditions(&read->sale_conditions, &written->sale_conditions);
  for (size_t i = 0; i < 8; i++) { assert(read->trade_price[i] == written->trade_price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->trade_volume[i] == written->trade_volume[i]); }
  assert(read->sellers_sale_days == written->sellers_sale_days);
  assert(read->stop_stock_indicator == written->stop_stock_indicator);
  assert(read->trade_through_exempt_indicator == written->trade_through_exempt_indicator);
  assert(read->short_sale_restriction_indicator == written->short_sale_restriction_indicator);
}

/* Corrected Trade: written and read back, then read and written back */
static void check_corrected_trade(void) {
  CorrectedTrade sent;
  CorrectedTrade got;
  uint8_t wire[20];
  uint8_t again[20];

  any_corrected_trade(&sent);
  assert(encode_corrected_trade(&sent, wire, 0) == 20);
  assert(decode_corrected_trade(&got, wire, 0) == 20);
  equal_corrected_trade(&got, &sent);

  for (size_t i = 0; i < 20; i++) { wire[i] = arbitrary(); }
  assert(decode_corrected_trade(&got, wire, 0) == 20);
  assert(encode_corrected_trade(&got, again, 0) == 20);
  for (size_t i = 0; i < 20; i++) { assert(again[i] == wire[i]); }
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

/* ---- Original Trade: 20 bytes ------------------------------------------------ */

/* Original Trade */
typedef struct {
  SaleConditions sale_conditions;            /* bytes 0 to 3 */
  uint8_t trade_price[8];                    /* bytes 4 to 11 */
  uint8_t trade_volume[4];                   /* bytes 12 to 15 */
  uint8_t sellers_sale_days;                 /* byte 16 */
  uint8_t stop_stock_indicator;              /* byte 17 */
  uint8_t trade_through_exempt_indicator;    /* byte 18 */
  uint8_t short_sale_restriction_indicator;  /* byte 19 */
} OriginalTrade;

/* any Original Trade at all: every byte one the checker chooses */
static void any_original_trade(OriginalTrade *record) {
  any_sale_conditions(&record->sale_conditions);
  for (size_t i = 0; i < 8; i++) { record->trade_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->trade_volume[i] = arbitrary(); }
  record->sellers_sale_days = arbitrary();
  record->stop_stock_indicator = arbitrary();
  record->trade_through_exempt_indicator = arbitrary();
  record->short_sale_restriction_indicator = arbitrary();
}

/* Original Trade to the wire: 20 bytes from at, returning where the next byte goes */
static size_t encode_original_trade(const OriginalTrade *record, uint8_t *wire, size_t at) {
  at = encode_sale_conditions(&record->sale_conditions, wire, at);
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->trade_price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->trade_volume[i]; }
  wire[at++] = record->sellers_sale_days;
  wire[at++] = record->stop_stock_indicator;
  wire[at++] = record->trade_through_exempt_indicator;
  wire[at++] = record->short_sale_restriction_indicator;

  return at;
}

/* Original Trade off the wire: 20 bytes from at, returning where the next byte lies */
static size_t decode_original_trade(OriginalTrade *record, const uint8_t *wire, size_t at) {
  at = decode_sale_conditions(&record->sale_conditions, wire, at);
  for (size_t i = 0; i < 8; i++) { record->trade_price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->trade_volume[i] = wire[at++]; }
  record->sellers_sale_days = wire[at++];
  record->stop_stock_indicator = wire[at++];
  record->trade_through_exempt_indicator = wire[at++];
  record->short_sale_restriction_indicator = wire[at++];

  return at;
}

/* what was read of Original Trade is what was written, byte for byte */
static void equal_original_trade(const OriginalTrade *read, const OriginalTrade *written) {
  equal_sale_conditions(&read->sale_conditions, &written->sale_conditions);
  for (size_t i = 0; i < 8; i++) { assert(read->trade_price[i] == written->trade_price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->trade_volume[i] == written->trade_volume[i]); }
  assert(read->sellers_sale_days == written->sellers_sale_days);
  assert(read->stop_stock_indicator == written->stop_stock_indicator);
  assert(read->trade_through_exempt_indicator == written->trade_through_exempt_indicator);
  assert(read->short_sale_restriction_indicator == written->short_sale_restriction_indicator);
}

/* Original Trade: written and read back, then read and written back */
static void check_original_trade(void) {
  OriginalTrade sent;
  OriginalTrade got;
  uint8_t wire[20];
  uint8_t again[20];

  any_original_trade(&sent);
  assert(encode_original_trade(&sent, wire, 0) == 20);
  assert(decode_original_trade(&got, wire, 0) == 20);
  equal_original_trade(&got, &sent);

  for (size_t i = 0; i < 20; i++) { wire[i] = arbitrary(); }
  assert(decode_original_trade(&got, wire, 0) == 20);
  assert(encode_original_trade(&got, again, 0) == 20);
  for (size_t i = 0; i < 20; i++) { assert(again[i] == wire[i]); }
}

/* ---- Consolidated Data: 34 bytes --------------------------------------------- */

/* Consolidated Data */
typedef struct {
  uint8_t previous_close_price_date[4];  /* bytes 0 to 3 */
  uint8_t last_participant_id;           /* byte 4 */
  uint8_t last_price[8];                 /* bytes 5 to 12 */
  uint8_t high_price[8];                 /* bytes 13 to 20 */
  uint8_t low_price[8];                  /* bytes 21 to 28 */
  uint8_t total_volume_short[4];         /* bytes 29 to 32 */
  uint8_t tick;                          /* byte 33 */
} ConsolidatedData;

/* any Consolidated Data at all: every byte one the checker chooses */
static void any_consolidated_data(ConsolidatedData *record) {
  for (size_t i = 0; i < 4; i++) { record->previous_close_price_date[i] = arbitrary(); }
  record->last_participant_id = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->last_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->high_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->low_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->total_volume_short[i] = arbitrary(); }
  record->tick = arbitrary();
}

/* Consolidated Data to the wire: 34 bytes from at, returning where the next byte goes */
static size_t encode_consolidated_data(const ConsolidatedData *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->previous_close_price_date[i]; }
  wire[at++] = record->last_participant_id;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->last_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->high_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->low_price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->total_volume_short[i]; }
  wire[at++] = record->tick;

  return at;
}

/* Consolidated Data off the wire: 34 bytes from at, returning where the next byte lies */
static size_t decode_consolidated_data(ConsolidatedData *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->previous_close_price_date[i] = wire[at++]; }
  record->last_participant_id = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->last_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->high_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->low_price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->total_volume_short[i] = wire[at++]; }
  record->tick = wire[at++];

  return at;
}

/* what was read of Consolidated Data is what was written, byte for byte */
static void equal_consolidated_data(const ConsolidatedData *read, const ConsolidatedData *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->previous_close_price_date[i] == written->previous_close_price_date[i]); }
  assert(read->last_participant_id == written->last_participant_id);
  for (size_t i = 0; i < 8; i++) { assert(read->last_price[i] == written->last_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->high_price[i] == written->high_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->low_price[i] == written->low_price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->total_volume_short[i] == written->total_volume_short[i]); }
  assert(read->tick == written->tick);
}

/* Consolidated Data: written and read back, then read and written back */
static void check_consolidated_data(void) {
  ConsolidatedData sent;
  ConsolidatedData got;
  uint8_t wire[34];
  uint8_t again[34];

  any_consolidated_data(&sent);
  assert(encode_consolidated_data(&sent, wire, 0) == 34);
  assert(decode_consolidated_data(&got, wire, 0) == 34);
  equal_consolidated_data(&got, &sent);

  for (size_t i = 0; i < 34; i++) { wire[i] = arbitrary(); }
  assert(decode_consolidated_data(&got, wire, 0) == 34);
  assert(encode_consolidated_data(&got, again, 0) == 34);
  for (size_t i = 0; i < 34; i++) { assert(again[i] == wire[i]); }
}

/* ---- Participant Data: 41 bytes ---------------------------------------------- */

/* Participant Data */
typedef struct {
  uint8_t previous_close_price_date[4];  /* bytes 0 to 3 */
  uint8_t last_price[8];                 /* bytes 4 to 11 */
  uint8_t high_price[8];                 /* bytes 12 to 19 */
  uint8_t low_price[8];                  /* bytes 20 to 27 */
  uint8_t open_price[8];                 /* bytes 28 to 35 */
  uint8_t total_volume_short[4];         /* bytes 36 to 39 */
  uint8_t tick;                          /* byte 40 */
} ParticipantData;

/* any Participant Data at all: every byte one the checker chooses */
static void any_participant_data(ParticipantData *record) {
  for (size_t i = 0; i < 4; i++) { record->previous_close_price_date[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->last_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->high_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->low_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->open_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->total_volume_short[i] = arbitrary(); }
  record->tick = arbitrary();
}

/* Participant Data to the wire: 41 bytes from at, returning where the next byte goes */
static size_t encode_participant_data(const ParticipantData *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->previous_close_price_date[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->last_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->high_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->low_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->open_price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->total_volume_short[i]; }
  wire[at++] = record->tick;

  return at;
}

/* Participant Data off the wire: 41 bytes from at, returning where the next byte lies */
static size_t decode_participant_data(ParticipantData *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->previous_close_price_date[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->last_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->high_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->low_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->open_price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->total_volume_short[i] = wire[at++]; }
  record->tick = wire[at++];

  return at;
}

/* what was read of Participant Data is what was written, byte for byte */
static void equal_participant_data(const ParticipantData *read, const ParticipantData *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->previous_close_price_date[i] == written->previous_close_price_date[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->last_price[i] == written->last_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->high_price[i] == written->high_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->low_price[i] == written->low_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->open_price[i] == written->open_price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->total_volume_short[i] == written->total_volume_short[i]); }
  assert(read->tick == written->tick);
}

/* Participant Data: written and read back, then read and written back */
static void check_participant_data(void) {
  ParticipantData sent;
  ParticipantData got;
  uint8_t wire[41];
  uint8_t again[41];

  any_participant_data(&sent);
  assert(encode_participant_data(&sent, wire, 0) == 41);
  assert(decode_participant_data(&got, wire, 0) == 41);
  equal_participant_data(&got, &sent);

  for (size_t i = 0; i < 41; i++) { wire[i] = arbitrary(); }
  assert(decode_participant_data(&got, wire, 0) == 41);
  assert(encode_participant_data(&got, again, 0) == 41);
  for (size_t i = 0; i < 41; i++) { assert(again[i] == wire[i]); }
}

/* ---- Trade Correction Message: 168 bytes ------------------------------------- */

/* The Trade Correction message is used to correct Cta eligible Equity, Local Issue or Bond information. */
typedef struct {
  uint8_t participant_id;                            /* byte 0 */
  Timestamp1 timestamp_1;                            /* bytes 1 to 8 */
  uint8_t message_id;                                /* byte 9 */
  uint8_t transaction_id[4];                         /* bytes 10 to 13 */
  uint8_t participant_reference_number[8];           /* bytes 14 to 21 */
  uint8_t security_symbol[11];                       /* bytes 22 to 32 */
  uint8_t instrument_type;                           /* byte 33 */
  CorrectedTrade corrected_trade;                    /* bytes 34 to 53 */
  uint8_t trade_reporting_facility_id;               /* byte 54 */
  Timestamp2 timestamp_2;                            /* bytes 55 to 62 */
  uint8_t original_participant_reference_number[8];  /* bytes 63 to 70 */
  OriginalTrade original_trade;                      /* bytes 71 to 90 */
  uint8_t primary_listing_market_participant_id;     /* byte 91 */
  uint8_t financial_status_indicator;                /* byte 92 */
  ConsolidatedData consolidated_data;                /* bytes 93 to 126 */
  ParticipantData participant_data;                  /* bytes 127 to 167 */
} TradeCorrectionMessage;

/* any Trade Correction Message at all: every byte one the checker chooses */
static void any_trade_correction_message(TradeCorrectionMessage *record) {
  record->participant_id = arbitrary();
  any_timestamp1(&record->timestamp_1);
  record->message_id = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->transaction_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->participant_reference_number[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->security_symbol[i] = arbitrary(); }
  record->instrument_type = arbitrary();
  any_corrected_trade(&record->corrected_trade);
  record->trade_reporting_facility_id = arbitrary();
  any_timestamp2(&record->timestamp_2);
  for (size_t i = 0; i < 8; i++) { record->original_participant_reference_number[i] = arbitrary(); }
  any_original_trade(&record->original_trade);
  record->primary_listing_market_participant_id = arbitrary();
  record->financial_status_indicator = arbitrary();
  any_consolidated_data(&record->consolidated_data);
  any_participant_data(&record->participant_data);
}

/* Trade Correction Message to the wire: 168 bytes from at, returning where the next byte goes */
static size_t encode_trade_correction_message(const TradeCorrectionMessage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->participant_id;
  at = encode_timestamp1(&record->timestamp_1, wire, at);
  wire[at++] = record->message_id;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->transaction_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->participant_reference_number[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->security_symbol[i]; }
  wire[at++] = record->instrument_type;
  at = encode_corrected_trade(&record->corrected_trade, wire, at);
  wire[at++] = record->trade_reporting_facility_id;
  at = encode_timestamp2(&record->timestamp_2, wire, at);
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->original_participant_reference_number[i]; }
  at = encode_original_trade(&record->original_trade, wire, at);
  wire[at++] = record->primary_listing_market_participant_id;
  wire[at++] = record->financial_status_indicator;
  at = encode_consolidated_data(&record->consolidated_data, wire, at);
  at = encode_participant_data(&record->participant_data, wire, at);

  return at;
}

/* Trade Correction Message off the wire: 168 bytes from at, returning where the next byte lies */
static size_t decode_trade_correction_message(TradeCorrectionMessage *record, const uint8_t *wire, size_t at) {
  record->participant_id = wire[at++];
  at = decode_timestamp1(&record->timestamp_1, wire, at);
  record->message_id = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->transaction_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->participant_reference_number[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->security_symbol[i] = wire[at++]; }
  record->instrument_type = wire[at++];
  at = decode_corrected_trade(&record->corrected_trade, wire, at);
  record->trade_reporting_facility_id = wire[at++];
  at = decode_timestamp2(&record->timestamp_2, wire, at);
  for (size_t i = 0; i < 8; i++) { record->original_participant_reference_number[i] = wire[at++]; }
  at = decode_original_trade(&record->original_trade, wire, at);
  record->primary_listing_market_participant_id = wire[at++];
  record->financial_status_indicator = wire[at++];
  at = decode_consolidated_data(&record->consolidated_data, wire, at);
  at = decode_participant_data(&record->participant_data, wire, at);

  return at;
}

/* what was read of Trade Correction Message is what was written, byte for byte */
static void equal_trade_correction_message(const TradeCorrectionMessage *read, const TradeCorrectionMessage *written) {
  assert(read->participant_id == written->participant_id);
  equal_timestamp1(&read->timestamp_1, &written->timestamp_1);
  assert(read->message_id == written->message_id);
  for (size_t i = 0; i < 4; i++) { assert(read->transaction_id[i] == written->transaction_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->participant_reference_number[i] == written->participant_reference_number[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->security_symbol[i] == written->security_symbol[i]); }
  assert(read->instrument_type == written->instrument_type);
  equal_corrected_trade(&read->corrected_trade, &written->corrected_trade);
  assert(read->trade_reporting_facility_id == written->trade_reporting_facility_id);
  equal_timestamp2(&read->timestamp_2, &written->timestamp_2);
  for (size_t i = 0; i < 8; i++) { assert(read->original_participant_reference_number[i] == written->original_participant_reference_number[i]); }
  equal_original_trade(&read->original_trade, &written->original_trade);
  assert(read->primary_listing_market_participant_id == written->primary_listing_market_participant_id);
  assert(read->financial_status_indicator == written->financial_status_indicator);
  equal_consolidated_data(&read->consolidated_data, &written->consolidated_data);
  equal_participant_data(&read->participant_data, &written->participant_data);
}

/* Trade Correction Message: written and read back, then read and written back */
static void check_trade_correction_message(void) {
  TradeCorrectionMessage sent;
  TradeCorrectionMessage got;
  uint8_t wire[168];
  uint8_t again[168];

  any_trade_correction_message(&sent);
  assert(encode_trade_correction_message(&sent, wire, 0) == 168);
  assert(decode_trade_correction_message(&got, wire, 0) == 168);
  equal_trade_correction_message(&got, &sent);

  for (size_t i = 0; i < 168; i++) { wire[i] = arbitrary(); }
  assert(decode_trade_correction_message(&got, wire, 0) == 168);
  assert(encode_trade_correction_message(&got, again, 0) == 168);
  for (size_t i = 0; i < 168; i++) { assert(again[i] == wire[i]); }
}

/* ---- Fractional Corrected Trade: 24 bytes ------------------------------------ */

/* Fractional Corrected Trade */
typedef struct {
  SaleConditions sale_conditions;            /* bytes 0 to 3 */
  uint8_t trade_price[8];                    /* bytes 4 to 11 */
  uint8_t fractional_trade_volume[8];        /* bytes 12 to 19 */
  uint8_t sellers_sale_days;                 /* byte 20 */
  uint8_t stop_stock_indicator;              /* byte 21 */
  uint8_t trade_through_exempt_indicator;    /* byte 22 */
  uint8_t short_sale_restriction_indicator;  /* byte 23 */
} FractionalCorrectedTrade;

/* any Fractional Corrected Trade at all: every byte one the checker chooses */
static void any_fractional_corrected_trade(FractionalCorrectedTrade *record) {
  any_sale_conditions(&record->sale_conditions);
  for (size_t i = 0; i < 8; i++) { record->trade_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->fractional_trade_volume[i] = arbitrary(); }
  record->sellers_sale_days = arbitrary();
  record->stop_stock_indicator = arbitrary();
  record->trade_through_exempt_indicator = arbitrary();
  record->short_sale_restriction_indicator = arbitrary();
}

/* Fractional Corrected Trade to the wire: 24 bytes from at, returning where the next byte goes */
static size_t encode_fractional_corrected_trade(const FractionalCorrectedTrade *record, uint8_t *wire, size_t at) {
  at = encode_sale_conditions(&record->sale_conditions, wire, at);
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->trade_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->fractional_trade_volume[i]; }
  wire[at++] = record->sellers_sale_days;
  wire[at++] = record->stop_stock_indicator;
  wire[at++] = record->trade_through_exempt_indicator;
  wire[at++] = record->short_sale_restriction_indicator;

  return at;
}

/* Fractional Corrected Trade off the wire: 24 bytes from at, returning where the next byte lies */
static size_t decode_fractional_corrected_trade(FractionalCorrectedTrade *record, const uint8_t *wire, size_t at) {
  at = decode_sale_conditions(&record->sale_conditions, wire, at);
  for (size_t i = 0; i < 8; i++) { record->trade_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->fractional_trade_volume[i] = wire[at++]; }
  record->sellers_sale_days = wire[at++];
  record->stop_stock_indicator = wire[at++];
  record->trade_through_exempt_indicator = wire[at++];
  record->short_sale_restriction_indicator = wire[at++];

  return at;
}

/* what was read of Fractional Corrected Trade is what was written, byte for byte */
static void equal_fractional_corrected_trade(const FractionalCorrectedTrade *read, const FractionalCorrectedTrade *written) {
  equal_sale_conditions(&read->sale_conditions, &written->sale_conditions);
  for (size_t i = 0; i < 8; i++) { assert(read->trade_price[i] == written->trade_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->fractional_trade_volume[i] == written->fractional_trade_volume[i]); }
  assert(read->sellers_sale_days == written->sellers_sale_days);
  assert(read->stop_stock_indicator == written->stop_stock_indicator);
  assert(read->trade_through_exempt_indicator == written->trade_through_exempt_indicator);
  assert(read->short_sale_restriction_indicator == written->short_sale_restriction_indicator);
}

/* Fractional Corrected Trade: written and read back, then read and written back */
static void check_fractional_corrected_trade(void) {
  FractionalCorrectedTrade sent;
  FractionalCorrectedTrade got;
  uint8_t wire[24];
  uint8_t again[24];

  any_fractional_corrected_trade(&sent);
  assert(encode_fractional_corrected_trade(&sent, wire, 0) == 24);
  assert(decode_fractional_corrected_trade(&got, wire, 0) == 24);
  equal_fractional_corrected_trade(&got, &sent);

  for (size_t i = 0; i < 24; i++) { wire[i] = arbitrary(); }
  assert(decode_fractional_corrected_trade(&got, wire, 0) == 24);
  assert(encode_fractional_corrected_trade(&got, again, 0) == 24);
  for (size_t i = 0; i < 24; i++) { assert(again[i] == wire[i]); }
}

/* ---- Fractional Original Trade: 24 bytes ------------------------------------- */

/* Fractional Original Trade */
typedef struct {
  SaleConditions sale_conditions;            /* bytes 0 to 3 */
  uint8_t trade_price[8];                    /* bytes 4 to 11 */
  uint8_t fractional_trade_volume[8];        /* bytes 12 to 19 */
  uint8_t sellers_sale_days;                 /* byte 20 */
  uint8_t stop_stock_indicator;              /* byte 21 */
  uint8_t trade_through_exempt_indicator;    /* byte 22 */
  uint8_t short_sale_restriction_indicator;  /* byte 23 */
} FractionalOriginalTrade;

/* any Fractional Original Trade at all: every byte one the checker chooses */
static void any_fractional_original_trade(FractionalOriginalTrade *record) {
  any_sale_conditions(&record->sale_conditions);
  for (size_t i = 0; i < 8; i++) { record->trade_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->fractional_trade_volume[i] = arbitrary(); }
  record->sellers_sale_days = arbitrary();
  record->stop_stock_indicator = arbitrary();
  record->trade_through_exempt_indicator = arbitrary();
  record->short_sale_restriction_indicator = arbitrary();
}

/* Fractional Original Trade to the wire: 24 bytes from at, returning where the next byte goes */
static size_t encode_fractional_original_trade(const FractionalOriginalTrade *record, uint8_t *wire, size_t at) {
  at = encode_sale_conditions(&record->sale_conditions, wire, at);
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->trade_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->fractional_trade_volume[i]; }
  wire[at++] = record->sellers_sale_days;
  wire[at++] = record->stop_stock_indicator;
  wire[at++] = record->trade_through_exempt_indicator;
  wire[at++] = record->short_sale_restriction_indicator;

  return at;
}

/* Fractional Original Trade off the wire: 24 bytes from at, returning where the next byte lies */
static size_t decode_fractional_original_trade(FractionalOriginalTrade *record, const uint8_t *wire, size_t at) {
  at = decode_sale_conditions(&record->sale_conditions, wire, at);
  for (size_t i = 0; i < 8; i++) { record->trade_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->fractional_trade_volume[i] = wire[at++]; }
  record->sellers_sale_days = wire[at++];
  record->stop_stock_indicator = wire[at++];
  record->trade_through_exempt_indicator = wire[at++];
  record->short_sale_restriction_indicator = wire[at++];

  return at;
}

/* what was read of Fractional Original Trade is what was written, byte for byte */
static void equal_fractional_original_trade(const FractionalOriginalTrade *read, const FractionalOriginalTrade *written) {
  equal_sale_conditions(&read->sale_conditions, &written->sale_conditions);
  for (size_t i = 0; i < 8; i++) { assert(read->trade_price[i] == written->trade_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->fractional_trade_volume[i] == written->fractional_trade_volume[i]); }
  assert(read->sellers_sale_days == written->sellers_sale_days);
  assert(read->stop_stock_indicator == written->stop_stock_indicator);
  assert(read->trade_through_exempt_indicator == written->trade_through_exempt_indicator);
  assert(read->short_sale_restriction_indicator == written->short_sale_restriction_indicator);
}

/* Fractional Original Trade: written and read back, then read and written back */
static void check_fractional_original_trade(void) {
  FractionalOriginalTrade sent;
  FractionalOriginalTrade got;
  uint8_t wire[24];
  uint8_t again[24];

  any_fractional_original_trade(&sent);
  assert(encode_fractional_original_trade(&sent, wire, 0) == 24);
  assert(decode_fractional_original_trade(&got, wire, 0) == 24);
  equal_fractional_original_trade(&got, &sent);

  for (size_t i = 0; i < 24; i++) { wire[i] = arbitrary(); }
  assert(decode_fractional_original_trade(&got, wire, 0) == 24);
  assert(encode_fractional_original_trade(&got, again, 0) == 24);
  for (size_t i = 0; i < 24; i++) { assert(again[i] == wire[i]); }
}

/* ---- Fractional Consolidated Data: 38 bytes ---------------------------------- */

/* Fractional Consolidated Data */
typedef struct {
  uint8_t previous_close_price_date[4];  /* bytes 0 to 3 */
  uint8_t last_participant_id;           /* byte 4 */
  uint8_t last_price[8];                 /* bytes 5 to 12 */
  uint8_t high_price[8];                 /* bytes 13 to 20 */
  uint8_t low_price[8];                  /* bytes 21 to 28 */
  uint8_t fractional_total_volume[8];    /* bytes 29 to 36 */
  uint8_t tick;                          /* byte 37 */
} FractionalConsolidatedData;

/* any Fractional Consolidated Data at all: every byte one the checker chooses */
static void any_fractional_consolidated_data(FractionalConsolidatedData *record) {
  for (size_t i = 0; i < 4; i++) { record->previous_close_price_date[i] = arbitrary(); }
  record->last_participant_id = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->last_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->high_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->low_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->fractional_total_volume[i] = arbitrary(); }
  record->tick = arbitrary();
}

/* Fractional Consolidated Data to the wire: 38 bytes from at, returning where the next byte goes */
static size_t encode_fractional_consolidated_data(const FractionalConsolidatedData *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->previous_close_price_date[i]; }
  wire[at++] = record->last_participant_id;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->last_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->high_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->low_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->fractional_total_volume[i]; }
  wire[at++] = record->tick;

  return at;
}

/* Fractional Consolidated Data off the wire: 38 bytes from at, returning where the next byte lies */
static size_t decode_fractional_consolidated_data(FractionalConsolidatedData *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->previous_close_price_date[i] = wire[at++]; }
  record->last_participant_id = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->last_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->high_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->low_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->fractional_total_volume[i] = wire[at++]; }
  record->tick = wire[at++];

  return at;
}

/* what was read of Fractional Consolidated Data is what was written, byte for byte */
static void equal_fractional_consolidated_data(const FractionalConsolidatedData *read, const FractionalConsolidatedData *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->previous_close_price_date[i] == written->previous_close_price_date[i]); }
  assert(read->last_participant_id == written->last_participant_id);
  for (size_t i = 0; i < 8; i++) { assert(read->last_price[i] == written->last_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->high_price[i] == written->high_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->low_price[i] == written->low_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->fractional_total_volume[i] == written->fractional_total_volume[i]); }
  assert(read->tick == written->tick);
}

/* Fractional Consolidated Data: written and read back, then read and written back */
static void check_fractional_consolidated_data(void) {
  FractionalConsolidatedData sent;
  FractionalConsolidatedData got;
  uint8_t wire[38];
  uint8_t again[38];

  any_fractional_consolidated_data(&sent);
  assert(encode_fractional_consolidated_data(&sent, wire, 0) == 38);
  assert(decode_fractional_consolidated_data(&got, wire, 0) == 38);
  equal_fractional_consolidated_data(&got, &sent);

  for (size_t i = 0; i < 38; i++) { wire[i] = arbitrary(); }
  assert(decode_fractional_consolidated_data(&got, wire, 0) == 38);
  assert(encode_fractional_consolidated_data(&got, again, 0) == 38);
  for (size_t i = 0; i < 38; i++) { assert(again[i] == wire[i]); }
}

/* ---- Fractional Participant Data: 45 bytes ----------------------------------- */

/* Fractional Participant Data */
typedef struct {
  uint8_t previous_close_price_date[4];  /* bytes 0 to 3 */
  uint8_t last_price[8];                 /* bytes 4 to 11 */
  uint8_t high_price[8];                 /* bytes 12 to 19 */
  uint8_t low_price[8];                  /* bytes 20 to 27 */
  uint8_t open_price[8];                 /* bytes 28 to 35 */
  uint8_t fractional_total_volume[8];    /* bytes 36 to 43 */
  uint8_t tick;                          /* byte 44 */
} FractionalParticipantData;

/* any Fractional Participant Data at all: every byte one the checker chooses */
static void any_fractional_participant_data(FractionalParticipantData *record) {
  for (size_t i = 0; i < 4; i++) { record->previous_close_price_date[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->last_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->high_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->low_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->open_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->fractional_total_volume[i] = arbitrary(); }
  record->tick = arbitrary();
}

/* Fractional Participant Data to the wire: 45 bytes from at, returning where the next byte goes */
static size_t encode_fractional_participant_data(const FractionalParticipantData *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->previous_close_price_date[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->last_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->high_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->low_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->open_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->fractional_total_volume[i]; }
  wire[at++] = record->tick;

  return at;
}

/* Fractional Participant Data off the wire: 45 bytes from at, returning where the next byte lies */
static size_t decode_fractional_participant_data(FractionalParticipantData *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->previous_close_price_date[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->last_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->high_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->low_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->open_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->fractional_total_volume[i] = wire[at++]; }
  record->tick = wire[at++];

  return at;
}

/* what was read of Fractional Participant Data is what was written, byte for byte */
static void equal_fractional_participant_data(const FractionalParticipantData *read, const FractionalParticipantData *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->previous_close_price_date[i] == written->previous_close_price_date[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->last_price[i] == written->last_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->high_price[i] == written->high_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->low_price[i] == written->low_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->open_price[i] == written->open_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->fractional_total_volume[i] == written->fractional_total_volume[i]); }
  assert(read->tick == written->tick);
}

/* Fractional Participant Data: written and read back, then read and written back */
static void check_fractional_participant_data(void) {
  FractionalParticipantData sent;
  FractionalParticipantData got;
  uint8_t wire[45];
  uint8_t again[45];

  any_fractional_participant_data(&sent);
  assert(encode_fractional_participant_data(&sent, wire, 0) == 45);
  assert(decode_fractional_participant_data(&got, wire, 0) == 45);
  equal_fractional_participant_data(&got, &sent);

  for (size_t i = 0; i < 45; i++) { wire[i] = arbitrary(); }
  assert(decode_fractional_participant_data(&got, wire, 0) == 45);
  assert(encode_fractional_participant_data(&got, again, 0) == 45);
  for (size_t i = 0; i < 45; i++) { assert(again[i] == wire[i]); }
}

/* ---- Fractional Trade Correction Message: 184 bytes -------------------------- */

/* The Trade Correction message is used to correct Cta eligible Equity, Local Issue or Bond information. */
typedef struct {
  uint8_t participant_id;                                   /* byte 0 */
  Timestamp1 timestamp_1;                                   /* bytes 1 to 8 */
  uint8_t message_id;                                       /* byte 9 */
  uint8_t transaction_id[4];                                /* bytes 10 to 13 */
  uint8_t participant_reference_number[8];                  /* bytes 14 to 21 */
  uint8_t security_symbol[11];                              /* bytes 22 to 32 */
  uint8_t instrument_type;                                  /* byte 33 */
  FractionalCorrectedTrade fractional_corrected_trade;      /* bytes 34 to 57 */
  uint8_t trade_reporting_facility_id;                      /* byte 58 */
  Timestamp2 timestamp_2;                                   /* bytes 59 to 66 */
  uint8_t original_participant_reference_number[8];         /* bytes 67 to 74 */
  FractionalOriginalTrade fractional_original_trade;        /* bytes 75 to 98 */
  uint8_t primary_listing_market_participant_id;            /* byte 99 */
  uint8_t financial_status_indicator;                       /* byte 100 */
  FractionalConsolidatedData fractional_consolidated_data;  /* bytes 101 to 138 */
  FractionalParticipantData fractional_participant_data;    /* bytes 139 to 183 */
} FractionalTradeCorrectionMessage;

/* any Fractional Trade Correction Message at all: every byte one the checker chooses */
static void any_fractional_trade_correction_message(FractionalTradeCorrectionMessage *record) {
  record->participant_id = arbitrary();
  any_timestamp1(&record->timestamp_1);
  record->message_id = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->transaction_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->participant_reference_number[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->security_symbol[i] = arbitrary(); }
  record->instrument_type = arbitrary();
  any_fractional_corrected_trade(&record->fractional_corrected_trade);
  record->trade_reporting_facility_id = arbitrary();
  any_timestamp2(&record->timestamp_2);
  for (size_t i = 0; i < 8; i++) { record->original_participant_reference_number[i] = arbitrary(); }
  any_fractional_original_trade(&record->fractional_original_trade);
  record->primary_listing_market_participant_id = arbitrary();
  record->financial_status_indicator = arbitrary();
  any_fractional_consolidated_data(&record->fractional_consolidated_data);
  any_fractional_participant_data(&record->fractional_participant_data);
}

/* Fractional Trade Correction Message to the wire: 184 bytes from at, returning where the next byte goes */
static size_t encode_fractional_trade_correction_message(const FractionalTradeCorrectionMessage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->participant_id;
  at = encode_timestamp1(&record->timestamp_1, wire, at);
  wire[at++] = record->message_id;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->transaction_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->participant_reference_number[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->security_symbol[i]; }
  wire[at++] = record->instrument_type;
  at = encode_fractional_corrected_trade(&record->fractional_corrected_trade, wire, at);
  wire[at++] = record->trade_reporting_facility_id;
  at = encode_timestamp2(&record->timestamp_2, wire, at);
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->original_participant_reference_number[i]; }
  at = encode_fractional_original_trade(&record->fractional_original_trade, wire, at);
  wire[at++] = record->primary_listing_market_participant_id;
  wire[at++] = record->financial_status_indicator;
  at = encode_fractional_consolidated_data(&record->fractional_consolidated_data, wire, at);
  at = encode_fractional_participant_data(&record->fractional_participant_data, wire, at);

  return at;
}

/* Fractional Trade Correction Message off the wire: 184 bytes from at, returning where the next byte lies */
static size_t decode_fractional_trade_correction_message(FractionalTradeCorrectionMessage *record, const uint8_t *wire, size_t at) {
  record->participant_id = wire[at++];
  at = decode_timestamp1(&record->timestamp_1, wire, at);
  record->message_id = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->transaction_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->participant_reference_number[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->security_symbol[i] = wire[at++]; }
  record->instrument_type = wire[at++];
  at = decode_fractional_corrected_trade(&record->fractional_corrected_trade, wire, at);
  record->trade_reporting_facility_id = wire[at++];
  at = decode_timestamp2(&record->timestamp_2, wire, at);
  for (size_t i = 0; i < 8; i++) { record->original_participant_reference_number[i] = wire[at++]; }
  at = decode_fractional_original_trade(&record->fractional_original_trade, wire, at);
  record->primary_listing_market_participant_id = wire[at++];
  record->financial_status_indicator = wire[at++];
  at = decode_fractional_consolidated_data(&record->fractional_consolidated_data, wire, at);
  at = decode_fractional_participant_data(&record->fractional_participant_data, wire, at);

  return at;
}

/* what was read of Fractional Trade Correction Message is what was written, byte for byte */
static void equal_fractional_trade_correction_message(const FractionalTradeCorrectionMessage *read, const FractionalTradeCorrectionMessage *written) {
  assert(read->participant_id == written->participant_id);
  equal_timestamp1(&read->timestamp_1, &written->timestamp_1);
  assert(read->message_id == written->message_id);
  for (size_t i = 0; i < 4; i++) { assert(read->transaction_id[i] == written->transaction_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->participant_reference_number[i] == written->participant_reference_number[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->security_symbol[i] == written->security_symbol[i]); }
  assert(read->instrument_type == written->instrument_type);
  equal_fractional_corrected_trade(&read->fractional_corrected_trade, &written->fractional_corrected_trade);
  assert(read->trade_reporting_facility_id == written->trade_reporting_facility_id);
  equal_timestamp2(&read->timestamp_2, &written->timestamp_2);
  for (size_t i = 0; i < 8; i++) { assert(read->original_participant_reference_number[i] == written->original_participant_reference_number[i]); }
  equal_fractional_original_trade(&read->fractional_original_trade, &written->fractional_original_trade);
  assert(read->primary_listing_market_participant_id == written->primary_listing_market_participant_id);
  assert(read->financial_status_indicator == written->financial_status_indicator);
  equal_fractional_consolidated_data(&read->fractional_consolidated_data, &written->fractional_consolidated_data);
  equal_fractional_participant_data(&read->fractional_participant_data, &written->fractional_participant_data);
}

/* Fractional Trade Correction Message: written and read back, then read and written back */
static void check_fractional_trade_correction_message(void) {
  FractionalTradeCorrectionMessage sent;
  FractionalTradeCorrectionMessage got;
  uint8_t wire[184];
  uint8_t again[184];

  any_fractional_trade_correction_message(&sent);
  assert(encode_fractional_trade_correction_message(&sent, wire, 0) == 184);
  assert(decode_fractional_trade_correction_message(&got, wire, 0) == 184);
  equal_fractional_trade_correction_message(&got, &sent);

  for (size_t i = 0; i < 184; i++) { wire[i] = arbitrary(); }
  assert(decode_fractional_trade_correction_message(&got, wire, 0) == 184);
  assert(encode_fractional_trade_correction_message(&got, again, 0) == 184);
  for (size_t i = 0; i < 184; i++) { assert(again[i] == wire[i]); }
}

/* ---- Long Trade Message: 68 bytes -------------------------------------------- */

/* The Long Trade message is used to report trade information for Cta eligible Equity, Local Issue or Bonds. */
typedef struct {
  uint8_t participant_id;                            /* byte 0 */
  Timestamp1 timestamp_1;                            /* bytes 1 to 8 */
  uint8_t message_id;                                /* byte 9 */
  uint8_t transaction_id[4];                         /* bytes 10 to 13 */
  uint8_t participant_reference_number[8];           /* bytes 14 to 21 */
  uint8_t security_symbol[11];                       /* bytes 22 to 32 */
  uint8_t instrument_type;                           /* byte 33 */
  SaleConditions sale_conditions;                    /* bytes 34 to 37 */
  uint8_t trade_price[8];                            /* bytes 38 to 45 */
  uint8_t trade_volume[4];                           /* bytes 46 to 49 */
  uint8_t sellers_sale_days;                         /* byte 50 */
  uint8_t stop_stock_indicator;                      /* byte 51 */
  uint8_t trade_through_exempt_indicator;            /* byte 52 */
  uint8_t trade_reporting_facility_id;               /* byte 53 */
  Timestamp2 timestamp_2;                            /* bytes 54 to 61 */
  uint8_t short_sale_restriction_indicator;          /* byte 62 */
  uint8_t primary_listing_market_participant_id;     /* byte 63 */
  uint8_t financial_status_indicator;                /* byte 64 */
  uint8_t held_trade_indicator;                      /* byte 65 */
  uint8_t consolidated_high_low_last_indicator;      /* byte 66 */
  uint8_t participant_open_high_low_last_indicator;  /* byte 67 */
} LongTradeMessage;

/* any Long Trade Message at all: every byte one the checker chooses */
static void any_long_trade_message(LongTradeMessage *record) {
  record->participant_id = arbitrary();
  any_timestamp1(&record->timestamp_1);
  record->message_id = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->transaction_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->participant_reference_number[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->security_symbol[i] = arbitrary(); }
  record->instrument_type = arbitrary();
  any_sale_conditions(&record->sale_conditions);
  for (size_t i = 0; i < 8; i++) { record->trade_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->trade_volume[i] = arbitrary(); }
  record->sellers_sale_days = arbitrary();
  record->stop_stock_indicator = arbitrary();
  record->trade_through_exempt_indicator = arbitrary();
  record->trade_reporting_facility_id = arbitrary();
  any_timestamp2(&record->timestamp_2);
  record->short_sale_restriction_indicator = arbitrary();
  record->primary_listing_market_participant_id = arbitrary();
  record->financial_status_indicator = arbitrary();
  record->held_trade_indicator = arbitrary();
  record->consolidated_high_low_last_indicator = arbitrary();
  record->participant_open_high_low_last_indicator = arbitrary();
}

/* Long Trade Message to the wire: 68 bytes from at, returning where the next byte goes */
static size_t encode_long_trade_message(const LongTradeMessage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->participant_id;
  at = encode_timestamp1(&record->timestamp_1, wire, at);
  wire[at++] = record->message_id;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->transaction_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->participant_reference_number[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->security_symbol[i]; }
  wire[at++] = record->instrument_type;
  at = encode_sale_conditions(&record->sale_conditions, wire, at);
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->trade_price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->trade_volume[i]; }
  wire[at++] = record->sellers_sale_days;
  wire[at++] = record->stop_stock_indicator;
  wire[at++] = record->trade_through_exempt_indicator;
  wire[at++] = record->trade_reporting_facility_id;
  at = encode_timestamp2(&record->timestamp_2, wire, at);
  wire[at++] = record->short_sale_restriction_indicator;
  wire[at++] = record->primary_listing_market_participant_id;
  wire[at++] = record->financial_status_indicator;
  wire[at++] = record->held_trade_indicator;
  wire[at++] = record->consolidated_high_low_last_indicator;
  wire[at++] = record->participant_open_high_low_last_indicator;

  return at;
}

/* Long Trade Message off the wire: 68 bytes from at, returning where the next byte lies */
static size_t decode_long_trade_message(LongTradeMessage *record, const uint8_t *wire, size_t at) {
  record->participant_id = wire[at++];
  at = decode_timestamp1(&record->timestamp_1, wire, at);
  record->message_id = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->transaction_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->participant_reference_number[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->security_symbol[i] = wire[at++]; }
  record->instrument_type = wire[at++];
  at = decode_sale_conditions(&record->sale_conditions, wire, at);
  for (size_t i = 0; i < 8; i++) { record->trade_price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->trade_volume[i] = wire[at++]; }
  record->sellers_sale_days = wire[at++];
  record->stop_stock_indicator = wire[at++];
  record->trade_through_exempt_indicator = wire[at++];
  record->trade_reporting_facility_id = wire[at++];
  at = decode_timestamp2(&record->timestamp_2, wire, at);
  record->short_sale_restriction_indicator = wire[at++];
  record->primary_listing_market_participant_id = wire[at++];
  record->financial_status_indicator = wire[at++];
  record->held_trade_indicator = wire[at++];
  record->consolidated_high_low_last_indicator = wire[at++];
  record->participant_open_high_low_last_indicator = wire[at++];

  return at;
}

/* what was read of Long Trade Message is what was written, byte for byte */
static void equal_long_trade_message(const LongTradeMessage *read, const LongTradeMessage *written) {
  assert(read->participant_id == written->participant_id);
  equal_timestamp1(&read->timestamp_1, &written->timestamp_1);
  assert(read->message_id == written->message_id);
  for (size_t i = 0; i < 4; i++) { assert(read->transaction_id[i] == written->transaction_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->participant_reference_number[i] == written->participant_reference_number[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->security_symbol[i] == written->security_symbol[i]); }
  assert(read->instrument_type == written->instrument_type);
  equal_sale_conditions(&read->sale_conditions, &written->sale_conditions);
  for (size_t i = 0; i < 8; i++) { assert(read->trade_price[i] == written->trade_price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->trade_volume[i] == written->trade_volume[i]); }
  assert(read->sellers_sale_days == written->sellers_sale_days);
  assert(read->stop_stock_indicator == written->stop_stock_indicator);
  assert(read->trade_through_exempt_indicator == written->trade_through_exempt_indicator);
  assert(read->trade_reporting_facility_id == written->trade_reporting_facility_id);
  equal_timestamp2(&read->timestamp_2, &written->timestamp_2);
  assert(read->short_sale_restriction_indicator == written->short_sale_restriction_indicator);
  assert(read->primary_listing_market_participant_id == written->primary_listing_market_participant_id);
  assert(read->financial_status_indicator == written->financial_status_indicator);
  assert(read->held_trade_indicator == written->held_trade_indicator);
  assert(read->consolidated_high_low_last_indicator == written->consolidated_high_low_last_indicator);
  assert(read->participant_open_high_low_last_indicator == written->participant_open_high_low_last_indicator);
}

/* Long Trade Message: written and read back, then read and written back */
static void check_long_trade_message(void) {
  LongTradeMessage sent;
  LongTradeMessage got;
  uint8_t wire[68];
  uint8_t again[68];

  any_long_trade_message(&sent);
  assert(encode_long_trade_message(&sent, wire, 0) == 68);
  assert(decode_long_trade_message(&got, wire, 0) == 68);
  equal_long_trade_message(&got, &sent);

  for (size_t i = 0; i < 68; i++) { wire[i] = arbitrary(); }
  assert(decode_long_trade_message(&got, wire, 0) == 68);
  assert(encode_long_trade_message(&got, again, 0) == 68);
  for (size_t i = 0; i < 68; i++) { assert(again[i] == wire[i]); }
}

/* ---- Fractional Long Trade Message: 72 bytes --------------------------------- */

/* The Long Trade message is used to report trade information for Cta eligible Equity, Local Issue or Bonds. */
typedef struct {
  uint8_t participant_id;                            /* byte 0 */
  Timestamp1 timestamp_1;                            /* bytes 1 to 8 */
  uint8_t message_id;                                /* byte 9 */
  uint8_t transaction_id[4];                         /* bytes 10 to 13 */
  uint8_t participant_reference_number[8];           /* bytes 14 to 21 */
  uint8_t security_symbol[11];                       /* bytes 22 to 32 */
  uint8_t instrument_type;                           /* byte 33 */
  SaleConditions sale_conditions;                    /* bytes 34 to 37 */
  uint8_t trade_price[8];                            /* bytes 38 to 45 */
  uint8_t fractional_trade_volume[8];                /* bytes 46 to 53 */
  uint8_t sellers_sale_days;                         /* byte 54 */
  uint8_t stop_stock_indicator;                      /* byte 55 */
  uint8_t trade_through_exempt_indicator;            /* byte 56 */
  uint8_t trade_reporting_facility_id;               /* byte 57 */
  Timestamp2 timestamp_2;                            /* bytes 58 to 65 */
  uint8_t short_sale_restriction_indicator;          /* byte 66 */
  uint8_t primary_listing_market_participant_id;     /* byte 67 */
  uint8_t financial_status_indicator;                /* byte 68 */
  uint8_t held_trade_indicator;                      /* byte 69 */
  uint8_t consolidated_high_low_last_indicator;      /* byte 70 */
  uint8_t participant_open_high_low_last_indicator;  /* byte 71 */
} FractionalLongTradeMessage;

/* any Fractional Long Trade Message at all: every byte one the checker chooses */
static void any_fractional_long_trade_message(FractionalLongTradeMessage *record) {
  record->participant_id = arbitrary();
  any_timestamp1(&record->timestamp_1);
  record->message_id = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->transaction_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->participant_reference_number[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->security_symbol[i] = arbitrary(); }
  record->instrument_type = arbitrary();
  any_sale_conditions(&record->sale_conditions);
  for (size_t i = 0; i < 8; i++) { record->trade_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->fractional_trade_volume[i] = arbitrary(); }
  record->sellers_sale_days = arbitrary();
  record->stop_stock_indicator = arbitrary();
  record->trade_through_exempt_indicator = arbitrary();
  record->trade_reporting_facility_id = arbitrary();
  any_timestamp2(&record->timestamp_2);
  record->short_sale_restriction_indicator = arbitrary();
  record->primary_listing_market_participant_id = arbitrary();
  record->financial_status_indicator = arbitrary();
  record->held_trade_indicator = arbitrary();
  record->consolidated_high_low_last_indicator = arbitrary();
  record->participant_open_high_low_last_indicator = arbitrary();
}

/* Fractional Long Trade Message to the wire: 72 bytes from at, returning where the next byte goes */
static size_t encode_fractional_long_trade_message(const FractionalLongTradeMessage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->participant_id;
  at = encode_timestamp1(&record->timestamp_1, wire, at);
  wire[at++] = record->message_id;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->transaction_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->participant_reference_number[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->security_symbol[i]; }
  wire[at++] = record->instrument_type;
  at = encode_sale_conditions(&record->sale_conditions, wire, at);
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->trade_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->fractional_trade_volume[i]; }
  wire[at++] = record->sellers_sale_days;
  wire[at++] = record->stop_stock_indicator;
  wire[at++] = record->trade_through_exempt_indicator;
  wire[at++] = record->trade_reporting_facility_id;
  at = encode_timestamp2(&record->timestamp_2, wire, at);
  wire[at++] = record->short_sale_restriction_indicator;
  wire[at++] = record->primary_listing_market_participant_id;
  wire[at++] = record->financial_status_indicator;
  wire[at++] = record->held_trade_indicator;
  wire[at++] = record->consolidated_high_low_last_indicator;
  wire[at++] = record->participant_open_high_low_last_indicator;

  return at;
}

/* Fractional Long Trade Message off the wire: 72 bytes from at, returning where the next byte lies */
static size_t decode_fractional_long_trade_message(FractionalLongTradeMessage *record, const uint8_t *wire, size_t at) {
  record->participant_id = wire[at++];
  at = decode_timestamp1(&record->timestamp_1, wire, at);
  record->message_id = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->transaction_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->participant_reference_number[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->security_symbol[i] = wire[at++]; }
  record->instrument_type = wire[at++];
  at = decode_sale_conditions(&record->sale_conditions, wire, at);
  for (size_t i = 0; i < 8; i++) { record->trade_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->fractional_trade_volume[i] = wire[at++]; }
  record->sellers_sale_days = wire[at++];
  record->stop_stock_indicator = wire[at++];
  record->trade_through_exempt_indicator = wire[at++];
  record->trade_reporting_facility_id = wire[at++];
  at = decode_timestamp2(&record->timestamp_2, wire, at);
  record->short_sale_restriction_indicator = wire[at++];
  record->primary_listing_market_participant_id = wire[at++];
  record->financial_status_indicator = wire[at++];
  record->held_trade_indicator = wire[at++];
  record->consolidated_high_low_last_indicator = wire[at++];
  record->participant_open_high_low_last_indicator = wire[at++];

  return at;
}

/* what was read of Fractional Long Trade Message is what was written, byte for byte */
static void equal_fractional_long_trade_message(const FractionalLongTradeMessage *read, const FractionalLongTradeMessage *written) {
  assert(read->participant_id == written->participant_id);
  equal_timestamp1(&read->timestamp_1, &written->timestamp_1);
  assert(read->message_id == written->message_id);
  for (size_t i = 0; i < 4; i++) { assert(read->transaction_id[i] == written->transaction_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->participant_reference_number[i] == written->participant_reference_number[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->security_symbol[i] == written->security_symbol[i]); }
  assert(read->instrument_type == written->instrument_type);
  equal_sale_conditions(&read->sale_conditions, &written->sale_conditions);
  for (size_t i = 0; i < 8; i++) { assert(read->trade_price[i] == written->trade_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->fractional_trade_volume[i] == written->fractional_trade_volume[i]); }
  assert(read->sellers_sale_days == written->sellers_sale_days);
  assert(read->stop_stock_indicator == written->stop_stock_indicator);
  assert(read->trade_through_exempt_indicator == written->trade_through_exempt_indicator);
  assert(read->trade_reporting_facility_id == written->trade_reporting_facility_id);
  equal_timestamp2(&read->timestamp_2, &written->timestamp_2);
  assert(read->short_sale_restriction_indicator == written->short_sale_restriction_indicator);
  assert(read->primary_listing_market_participant_id == written->primary_listing_market_participant_id);
  assert(read->financial_status_indicator == written->financial_status_indicator);
  assert(read->held_trade_indicator == written->held_trade_indicator);
  assert(read->consolidated_high_low_last_indicator == written->consolidated_high_low_last_indicator);
  assert(read->participant_open_high_low_last_indicator == written->participant_open_high_low_last_indicator);
}

/* Fractional Long Trade Message: written and read back, then read and written back */
static void check_fractional_long_trade_message(void) {
  FractionalLongTradeMessage sent;
  FractionalLongTradeMessage got;
  uint8_t wire[72];
  uint8_t again[72];

  any_fractional_long_trade_message(&sent);
  assert(encode_fractional_long_trade_message(&sent, wire, 0) == 72);
  assert(decode_fractional_long_trade_message(&got, wire, 0) == 72);
  equal_fractional_long_trade_message(&got, &sent);

  for (size_t i = 0; i < 72; i++) { wire[i] = arbitrary(); }
  assert(decode_fractional_long_trade_message(&got, wire, 0) == 72);
  assert(encode_fractional_long_trade_message(&got, again, 0) == 72);
  for (size_t i = 0; i < 72; i++) { assert(again[i] == wire[i]); }
}

/* ---- Trading Status Message: 72 bytes ---------------------------------------- */

/* The Trading Status message is transmitted when a Participant in a Cta eligible security, Local Issue or a Bond elects to notify CTS of an Opening Delay, a Trading Halt, a Trading Resume, a Price Indication or a Market Imbalance. */
typedef struct {
  uint8_t participant_id;                                   /* byte 0 */
  Timestamp1 timestamp_1;                                   /* bytes 1 to 8 */
  uint8_t message_id;                                       /* byte 9 */
  uint8_t transaction_id[4];                                /* bytes 10 to 13 */
  uint8_t participant_reference_number[8];                  /* bytes 14 to 21 */
  uint8_t security_symbol[11];                              /* bytes 22 to 32 */
  uint8_t instrument_type;                                  /* byte 33 */
  uint8_t last_price[8];                                    /* bytes 34 to 41 */
  uint8_t high_indication_price_upper_limit_price_band[8];  /* bytes 42 to 49 */
  uint8_t low_indication_price_lower_limit_price_band[8];   /* bytes 50 to 57 */
  uint8_t buy_volume[4];                                    /* bytes 58 to 61 */
  uint8_t sell_volume[4];                                   /* bytes 62 to 65 */
  uint8_t security_status;                                  /* byte 66 */
  uint8_t halt_reason;                                      /* byte 67 */
  uint8_t short_sale_restriction_indicator;                 /* byte 68 */
  uint8_t primary_listing_market_participant_id;            /* byte 69 */
  uint8_t financial_status_indicator;                       /* byte 70 */
  uint8_t limit_up_limit_down_indicator;                    /* byte 71 */
} TradingStatusMessage;

/* any Trading Status Message at all: every byte one the checker chooses */
static void any_trading_status_message(TradingStatusMessage *record) {
  record->participant_id = arbitrary();
  any_timestamp1(&record->timestamp_1);
  record->message_id = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->transaction_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->participant_reference_number[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->security_symbol[i] = arbitrary(); }
  record->instrument_type = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->last_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->high_indication_price_upper_limit_price_band[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->low_indication_price_lower_limit_price_band[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->buy_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->sell_volume[i] = arbitrary(); }
  record->security_status = arbitrary();
  record->halt_reason = arbitrary();
  record->short_sale_restriction_indicator = arbitrary();
  record->primary_listing_market_participant_id = arbitrary();
  record->financial_status_indicator = arbitrary();
  record->limit_up_limit_down_indicator = arbitrary();
}

/* Trading Status Message to the wire: 72 bytes from at, returning where the next byte goes */
static size_t encode_trading_status_message(const TradingStatusMessage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->participant_id;
  at = encode_timestamp1(&record->timestamp_1, wire, at);
  wire[at++] = record->message_id;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->transaction_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->participant_reference_number[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->security_symbol[i]; }
  wire[at++] = record->instrument_type;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->last_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->high_indication_price_upper_limit_price_band[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->low_indication_price_lower_limit_price_band[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->buy_volume[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->sell_volume[i]; }
  wire[at++] = record->security_status;
  wire[at++] = record->halt_reason;
  wire[at++] = record->short_sale_restriction_indicator;
  wire[at++] = record->primary_listing_market_participant_id;
  wire[at++] = record->financial_status_indicator;
  wire[at++] = record->limit_up_limit_down_indicator;

  return at;
}

/* Trading Status Message off the wire: 72 bytes from at, returning where the next byte lies */
static size_t decode_trading_status_message(TradingStatusMessage *record, const uint8_t *wire, size_t at) {
  record->participant_id = wire[at++];
  at = decode_timestamp1(&record->timestamp_1, wire, at);
  record->message_id = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->transaction_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->participant_reference_number[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->security_symbol[i] = wire[at++]; }
  record->instrument_type = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->last_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->high_indication_price_upper_limit_price_band[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->low_indication_price_lower_limit_price_band[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->buy_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->sell_volume[i] = wire[at++]; }
  record->security_status = wire[at++];
  record->halt_reason = wire[at++];
  record->short_sale_restriction_indicator = wire[at++];
  record->primary_listing_market_participant_id = wire[at++];
  record->financial_status_indicator = wire[at++];
  record->limit_up_limit_down_indicator = wire[at++];

  return at;
}

/* what was read of Trading Status Message is what was written, byte for byte */
static void equal_trading_status_message(const TradingStatusMessage *read, const TradingStatusMessage *written) {
  assert(read->participant_id == written->participant_id);
  equal_timestamp1(&read->timestamp_1, &written->timestamp_1);
  assert(read->message_id == written->message_id);
  for (size_t i = 0; i < 4; i++) { assert(read->transaction_id[i] == written->transaction_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->participant_reference_number[i] == written->participant_reference_number[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->security_symbol[i] == written->security_symbol[i]); }
  assert(read->instrument_type == written->instrument_type);
  for (size_t i = 0; i < 8; i++) { assert(read->last_price[i] == written->last_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->high_indication_price_upper_limit_price_band[i] == written->high_indication_price_upper_limit_price_band[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->low_indication_price_lower_limit_price_band[i] == written->low_indication_price_lower_limit_price_band[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->buy_volume[i] == written->buy_volume[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->sell_volume[i] == written->sell_volume[i]); }
  assert(read->security_status == written->security_status);
  assert(read->halt_reason == written->halt_reason);
  assert(read->short_sale_restriction_indicator == written->short_sale_restriction_indicator);
  assert(read->primary_listing_market_participant_id == written->primary_listing_market_participant_id);
  assert(read->financial_status_indicator == written->financial_status_indicator);
  assert(read->limit_up_limit_down_indicator == written->limit_up_limit_down_indicator);
}

/* Trading Status Message: written and read back, then read and written back */
static void check_trading_status_message(void) {
  TradingStatusMessage sent;
  TradingStatusMessage got;
  uint8_t wire[72];
  uint8_t again[72];

  any_trading_status_message(&sent);
  assert(encode_trading_status_message(&sent, wire, 0) == 72);
  assert(decode_trading_status_message(&got, wire, 0) == 72);
  equal_trading_status_message(&got, &sent);

  for (size_t i = 0; i < 72; i++) { wire[i] = arbitrary(); }
  assert(decode_trading_status_message(&got, wire, 0) == 72);
  assert(encode_trading_status_message(&got, again, 0) == 72);
  for (size_t i = 0; i < 72; i++) { assert(again[i] == wire[i]); }
}

/* ---- Short Trade Message: 36 bytes ------------------------------------------- */

/* The Short Trade message is used to report trade information for Cta eligible Equity only (not used for Local Issues or Bonds) if the trade meets message format requirements otherwise Long Trade message is used. */
typedef struct {
  uint8_t participant_id;                            /* byte 0 */
  Timestamp1 timestamp_1;                            /* bytes 1 to 8 */
  uint8_t message_id;                                /* byte 9 */
  uint8_t transaction_id[4];                         /* bytes 10 to 13 */
  uint8_t participant_reference_number[8];           /* bytes 14 to 21 */
  uint8_t security_symbol_short[5];                  /* bytes 22 to 26 */
  uint8_t sale_condition;                            /* byte 27 */
  uint8_t sale_condition_category;                   /* byte 28 */
  uint8_t trade_price_short[2];                      /* bytes 29 to 30 */
  uint8_t trade_volume_short[2];                     /* bytes 31 to 32 */
  uint8_t primary_listing_market_participant_id;     /* byte 33 */
  uint8_t consolidated_high_low_last_indicator;      /* byte 34 */
  uint8_t participant_open_high_low_last_indicator;  /* byte 35 */
} ShortTradeMessage;

/* any Short Trade Message at all: every byte one the checker chooses */
static void any_short_trade_message(ShortTradeMessage *record) {
  record->participant_id = arbitrary();
  any_timestamp1(&record->timestamp_1);
  record->message_id = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->transaction_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->participant_reference_number[i] = arbitrary(); }
  for (size_t i = 0; i < 5; i++) { record->security_symbol_short[i] = arbitrary(); }
  record->sale_condition = arbitrary();
  record->sale_condition_category = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->trade_price_short[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->trade_volume_short[i] = arbitrary(); }
  record->primary_listing_market_participant_id = arbitrary();
  record->consolidated_high_low_last_indicator = arbitrary();
  record->participant_open_high_low_last_indicator = arbitrary();
}

/* Short Trade Message to the wire: 36 bytes from at, returning where the next byte goes */
static size_t encode_short_trade_message(const ShortTradeMessage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->participant_id;
  at = encode_timestamp1(&record->timestamp_1, wire, at);
  wire[at++] = record->message_id;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->transaction_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->participant_reference_number[i]; }
  for (size_t i = 0; i < 5; i++) { wire[at++] = record->security_symbol_short[i]; }
  wire[at++] = record->sale_condition;
  wire[at++] = record->sale_condition_category;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->trade_price_short[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->trade_volume_short[i]; }
  wire[at++] = record->primary_listing_market_participant_id;
  wire[at++] = record->consolidated_high_low_last_indicator;
  wire[at++] = record->participant_open_high_low_last_indicator;

  return at;
}

/* Short Trade Message off the wire: 36 bytes from at, returning where the next byte lies */
static size_t decode_short_trade_message(ShortTradeMessage *record, const uint8_t *wire, size_t at) {
  record->participant_id = wire[at++];
  at = decode_timestamp1(&record->timestamp_1, wire, at);
  record->message_id = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->transaction_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->participant_reference_number[i] = wire[at++]; }
  for (size_t i = 0; i < 5; i++) { record->security_symbol_short[i] = wire[at++]; }
  record->sale_condition = wire[at++];
  record->sale_condition_category = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->trade_price_short[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->trade_volume_short[i] = wire[at++]; }
  record->primary_listing_market_participant_id = wire[at++];
  record->consolidated_high_low_last_indicator = wire[at++];
  record->participant_open_high_low_last_indicator = wire[at++];

  return at;
}

/* what was read of Short Trade Message is what was written, byte for byte */
static void equal_short_trade_message(const ShortTradeMessage *read, const ShortTradeMessage *written) {
  assert(read->participant_id == written->participant_id);
  equal_timestamp1(&read->timestamp_1, &written->timestamp_1);
  assert(read->message_id == written->message_id);
  for (size_t i = 0; i < 4; i++) { assert(read->transaction_id[i] == written->transaction_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->participant_reference_number[i] == written->participant_reference_number[i]); }
  for (size_t i = 0; i < 5; i++) { assert(read->security_symbol_short[i] == written->security_symbol_short[i]); }
  assert(read->sale_condition == written->sale_condition);
  assert(read->sale_condition_category == written->sale_condition_category);
  for (size_t i = 0; i < 2; i++) { assert(read->trade_price_short[i] == written->trade_price_short[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->trade_volume_short[i] == written->trade_volume_short[i]); }
  assert(read->primary_listing_market_participant_id == written->primary_listing_market_participant_id);
  assert(read->consolidated_high_low_last_indicator == written->consolidated_high_low_last_indicator);
  assert(read->participant_open_high_low_last_indicator == written->participant_open_high_low_last_indicator);
}

/* Short Trade Message: written and read back, then read and written back */
static void check_short_trade_message(void) {
  ShortTradeMessage sent;
  ShortTradeMessage got;
  uint8_t wire[36];
  uint8_t again[36];

  any_short_trade_message(&sent);
  assert(encode_short_trade_message(&sent, wire, 0) == 36);
  assert(decode_short_trade_message(&got, wire, 0) == 36);
  equal_short_trade_message(&got, &sent);

  for (size_t i = 0; i < 36; i++) { wire[i] = arbitrary(); }
  assert(decode_short_trade_message(&got, wire, 0) == 36);
  assert(encode_short_trade_message(&got, again, 0) == 36);
  for (size_t i = 0; i < 36; i++) { assert(again[i] == wire[i]); }
}

/* ---- Fractional Short Trade Message: 38 bytes -------------------------------- */

/* The Short Trade message is used to report trade information for Cta eligible Equity only (not used for Local Issues or Bonds) if the trade meets message format requirements otherwise Long Trade message is used. */
typedef struct {
  uint8_t participant_id;                            /* byte 0 */
  Timestamp1 timestamp_1;                            /* bytes 1 to 8 */
  uint8_t message_id;                                /* byte 9 */
  uint8_t transaction_id[4];                         /* bytes 10 to 13 */
  uint8_t participant_reference_number[8];           /* bytes 14 to 21 */
  uint8_t security_symbol_short[5];                  /* bytes 22 to 26 */
  uint8_t sale_condition;                            /* byte 27 */
  uint8_t sale_condition_category;                   /* byte 28 */
  uint8_t trade_price_short[2];                      /* bytes 29 to 30 */
  uint8_t fractional_trade_volume_short[4];          /* bytes 31 to 34 */
  uint8_t primary_listing_market_participant_id;     /* byte 35 */
  uint8_t consolidated_high_low_last_indicator;      /* byte 36 */
  uint8_t participant_open_high_low_last_indicator;  /* byte 37 */
} FractionalShortTradeMessage;

/* any Fractional Short Trade Message at all: every byte one the checker chooses */
static void any_fractional_short_trade_message(FractionalShortTradeMessage *record) {
  record->participant_id = arbitrary();
  any_timestamp1(&record->timestamp_1);
  record->message_id = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->transaction_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->participant_reference_number[i] = arbitrary(); }
  for (size_t i = 0; i < 5; i++) { record->security_symbol_short[i] = arbitrary(); }
  record->sale_condition = arbitrary();
  record->sale_condition_category = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->trade_price_short[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->fractional_trade_volume_short[i] = arbitrary(); }
  record->primary_listing_market_participant_id = arbitrary();
  record->consolidated_high_low_last_indicator = arbitrary();
  record->participant_open_high_low_last_indicator = arbitrary();
}

/* Fractional Short Trade Message to the wire: 38 bytes from at, returning where the next byte goes */
static size_t encode_fractional_short_trade_message(const FractionalShortTradeMessage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->participant_id;
  at = encode_timestamp1(&record->timestamp_1, wire, at);
  wire[at++] = record->message_id;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->transaction_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->participant_reference_number[i]; }
  for (size_t i = 0; i < 5; i++) { wire[at++] = record->security_symbol_short[i]; }
  wire[at++] = record->sale_condition;
  wire[at++] = record->sale_condition_category;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->trade_price_short[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->fractional_trade_volume_short[i]; }
  wire[at++] = record->primary_listing_market_participant_id;
  wire[at++] = record->consolidated_high_low_last_indicator;
  wire[at++] = record->participant_open_high_low_last_indicator;

  return at;
}

/* Fractional Short Trade Message off the wire: 38 bytes from at, returning where the next byte lies */
static size_t decode_fractional_short_trade_message(FractionalShortTradeMessage *record, const uint8_t *wire, size_t at) {
  record->participant_id = wire[at++];
  at = decode_timestamp1(&record->timestamp_1, wire, at);
  record->message_id = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->transaction_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->participant_reference_number[i] = wire[at++]; }
  for (size_t i = 0; i < 5; i++) { record->security_symbol_short[i] = wire[at++]; }
  record->sale_condition = wire[at++];
  record->sale_condition_category = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->trade_price_short[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->fractional_trade_volume_short[i] = wire[at++]; }
  record->primary_listing_market_participant_id = wire[at++];
  record->consolidated_high_low_last_indicator = wire[at++];
  record->participant_open_high_low_last_indicator = wire[at++];

  return at;
}

/* what was read of Fractional Short Trade Message is what was written, byte for byte */
static void equal_fractional_short_trade_message(const FractionalShortTradeMessage *read, const FractionalShortTradeMessage *written) {
  assert(read->participant_id == written->participant_id);
  equal_timestamp1(&read->timestamp_1, &written->timestamp_1);
  assert(read->message_id == written->message_id);
  for (size_t i = 0; i < 4; i++) { assert(read->transaction_id[i] == written->transaction_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->participant_reference_number[i] == written->participant_reference_number[i]); }
  for (size_t i = 0; i < 5; i++) { assert(read->security_symbol_short[i] == written->security_symbol_short[i]); }
  assert(read->sale_condition == written->sale_condition);
  assert(read->sale_condition_category == written->sale_condition_category);
  for (size_t i = 0; i < 2; i++) { assert(read->trade_price_short[i] == written->trade_price_short[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->fractional_trade_volume_short[i] == written->fractional_trade_volume_short[i]); }
  assert(read->primary_listing_market_participant_id == written->primary_listing_market_participant_id);
  assert(read->consolidated_high_low_last_indicator == written->consolidated_high_low_last_indicator);
  assert(read->participant_open_high_low_last_indicator == written->participant_open_high_low_last_indicator);
}

/* Fractional Short Trade Message: written and read back, then read and written back */
static void check_fractional_short_trade_message(void) {
  FractionalShortTradeMessage sent;
  FractionalShortTradeMessage got;
  uint8_t wire[38];
  uint8_t again[38];

  any_fractional_short_trade_message(&sent);
  assert(encode_fractional_short_trade_message(&sent, wire, 0) == 38);
  assert(decode_fractional_short_trade_message(&got, wire, 0) == 38);
  equal_fractional_short_trade_message(&got, &sent);

  for (size_t i = 0; i < 38; i++) { wire[i] = arbitrary(); }
  assert(decode_fractional_short_trade_message(&got, wire, 0) == 38);
  assert(encode_fractional_short_trade_message(&got, again, 0) == 38);
  for (size_t i = 0; i < 38; i++) { assert(again[i] == wire[i]); }
}

/* ---- Trade Cancel Error Message: 149 bytes ----------------------------------- */

/* The Trade Cancel/Error message is used cancel or error Cta eligible securities, Local Issues or Bond information. */
typedef struct {
  uint8_t participant_id;                            /* byte 0 */
  Timestamp1 timestamp_1;                            /* bytes 1 to 8 */
  uint8_t message_id;                                /* byte 9 */
  uint8_t transaction_id[4];                         /* bytes 10 to 13 */
  uint8_t participant_reference_number[8];           /* bytes 14 to 21 */
  uint8_t security_symbol[11];                       /* bytes 22 to 32 */
  uint8_t instrument_type;                           /* byte 33 */
  SaleConditions sale_conditions;                    /* bytes 34 to 37 */
  uint8_t trade_price[8];                            /* bytes 38 to 45 */
  uint8_t trade_volume[4];                           /* bytes 46 to 49 */
  uint8_t sellers_sale_days;                         /* byte 50 */
  uint8_t stop_stock_indicator;                      /* byte 51 */
  uint8_t trade_through_exempt_indicator;            /* byte 52 */
  uint8_t trade_reporting_facility_id;               /* byte 53 */
  uint8_t original_participant_reference_number[8];  /* bytes 54 to 61 */
  Timestamp2 timestamp_2;                            /* bytes 62 to 69 */
  uint8_t cancel_error_action;                       /* byte 70 */
  uint8_t short_sale_restriction_indicator;          /* byte 71 */
  uint8_t primary_listing_market_participant_id;     /* byte 72 */
  uint8_t financial_status_indicator;                /* byte 73 */
  ConsolidatedData consolidated_data;                /* bytes 74 to 107 */
  ParticipantData participant_data;                  /* bytes 108 to 148 */
} TradeCancelErrorMessage;

/* any Trade Cancel Error Message at all: every byte one the checker chooses */
static void any_trade_cancel_error_message(TradeCancelErrorMessage *record) {
  record->participant_id = arbitrary();
  any_timestamp1(&record->timestamp_1);
  record->message_id = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->transaction_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->participant_reference_number[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->security_symbol[i] = arbitrary(); }
  record->instrument_type = arbitrary();
  any_sale_conditions(&record->sale_conditions);
  for (size_t i = 0; i < 8; i++) { record->trade_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->trade_volume[i] = arbitrary(); }
  record->sellers_sale_days = arbitrary();
  record->stop_stock_indicator = arbitrary();
  record->trade_through_exempt_indicator = arbitrary();
  record->trade_reporting_facility_id = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->original_participant_reference_number[i] = arbitrary(); }
  any_timestamp2(&record->timestamp_2);
  record->cancel_error_action = arbitrary();
  record->short_sale_restriction_indicator = arbitrary();
  record->primary_listing_market_participant_id = arbitrary();
  record->financial_status_indicator = arbitrary();
  any_consolidated_data(&record->consolidated_data);
  any_participant_data(&record->participant_data);
}

/* Trade Cancel Error Message to the wire: 149 bytes from at, returning where the next byte goes */
static size_t encode_trade_cancel_error_message(const TradeCancelErrorMessage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->participant_id;
  at = encode_timestamp1(&record->timestamp_1, wire, at);
  wire[at++] = record->message_id;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->transaction_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->participant_reference_number[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->security_symbol[i]; }
  wire[at++] = record->instrument_type;
  at = encode_sale_conditions(&record->sale_conditions, wire, at);
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->trade_price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->trade_volume[i]; }
  wire[at++] = record->sellers_sale_days;
  wire[at++] = record->stop_stock_indicator;
  wire[at++] = record->trade_through_exempt_indicator;
  wire[at++] = record->trade_reporting_facility_id;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->original_participant_reference_number[i]; }
  at = encode_timestamp2(&record->timestamp_2, wire, at);
  wire[at++] = record->cancel_error_action;
  wire[at++] = record->short_sale_restriction_indicator;
  wire[at++] = record->primary_listing_market_participant_id;
  wire[at++] = record->financial_status_indicator;
  at = encode_consolidated_data(&record->consolidated_data, wire, at);
  at = encode_participant_data(&record->participant_data, wire, at);

  return at;
}

/* Trade Cancel Error Message off the wire: 149 bytes from at, returning where the next byte lies */
static size_t decode_trade_cancel_error_message(TradeCancelErrorMessage *record, const uint8_t *wire, size_t at) {
  record->participant_id = wire[at++];
  at = decode_timestamp1(&record->timestamp_1, wire, at);
  record->message_id = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->transaction_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->participant_reference_number[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->security_symbol[i] = wire[at++]; }
  record->instrument_type = wire[at++];
  at = decode_sale_conditions(&record->sale_conditions, wire, at);
  for (size_t i = 0; i < 8; i++) { record->trade_price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->trade_volume[i] = wire[at++]; }
  record->sellers_sale_days = wire[at++];
  record->stop_stock_indicator = wire[at++];
  record->trade_through_exempt_indicator = wire[at++];
  record->trade_reporting_facility_id = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->original_participant_reference_number[i] = wire[at++]; }
  at = decode_timestamp2(&record->timestamp_2, wire, at);
  record->cancel_error_action = wire[at++];
  record->short_sale_restriction_indicator = wire[at++];
  record->primary_listing_market_participant_id = wire[at++];
  record->financial_status_indicator = wire[at++];
  at = decode_consolidated_data(&record->consolidated_data, wire, at);
  at = decode_participant_data(&record->participant_data, wire, at);

  return at;
}

/* what was read of Trade Cancel Error Message is what was written, byte for byte */
static void equal_trade_cancel_error_message(const TradeCancelErrorMessage *read, const TradeCancelErrorMessage *written) {
  assert(read->participant_id == written->participant_id);
  equal_timestamp1(&read->timestamp_1, &written->timestamp_1);
  assert(read->message_id == written->message_id);
  for (size_t i = 0; i < 4; i++) { assert(read->transaction_id[i] == written->transaction_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->participant_reference_number[i] == written->participant_reference_number[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->security_symbol[i] == written->security_symbol[i]); }
  assert(read->instrument_type == written->instrument_type);
  equal_sale_conditions(&read->sale_conditions, &written->sale_conditions);
  for (size_t i = 0; i < 8; i++) { assert(read->trade_price[i] == written->trade_price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->trade_volume[i] == written->trade_volume[i]); }
  assert(read->sellers_sale_days == written->sellers_sale_days);
  assert(read->stop_stock_indicator == written->stop_stock_indicator);
  assert(read->trade_through_exempt_indicator == written->trade_through_exempt_indicator);
  assert(read->trade_reporting_facility_id == written->trade_reporting_facility_id);
  for (size_t i = 0; i < 8; i++) { assert(read->original_participant_reference_number[i] == written->original_participant_reference_number[i]); }
  equal_timestamp2(&read->timestamp_2, &written->timestamp_2);
  assert(read->cancel_error_action == written->cancel_error_action);
  assert(read->short_sale_restriction_indicator == written->short_sale_restriction_indicator);
  assert(read->primary_listing_market_participant_id == written->primary_listing_market_participant_id);
  assert(read->financial_status_indicator == written->financial_status_indicator);
  equal_consolidated_data(&read->consolidated_data, &written->consolidated_data);
  equal_participant_data(&read->participant_data, &written->participant_data);
}

/* Trade Cancel Error Message: written and read back, then read and written back */
static void check_trade_cancel_error_message(void) {
  TradeCancelErrorMessage sent;
  TradeCancelErrorMessage got;
  uint8_t wire[149];
  uint8_t again[149];

  any_trade_cancel_error_message(&sent);
  assert(encode_trade_cancel_error_message(&sent, wire, 0) == 149);
  assert(decode_trade_cancel_error_message(&got, wire, 0) == 149);
  equal_trade_cancel_error_message(&got, &sent);

  for (size_t i = 0; i < 149; i++) { wire[i] = arbitrary(); }
  assert(decode_trade_cancel_error_message(&got, wire, 0) == 149);
  assert(encode_trade_cancel_error_message(&got, again, 0) == 149);
  for (size_t i = 0; i < 149; i++) { assert(again[i] == wire[i]); }
}

/* ---- Fractional Trade Cancel Error Message: 161 bytes ------------------------ */

/* The Trade Cancel/Error message is used cancel or error Cta eligible securities, Local Issues or Bond information. */
typedef struct {
  uint8_t participant_id;                                   /* byte 0 */
  Timestamp1 timestamp_1;                                   /* bytes 1 to 8 */
  uint8_t message_id;                                       /* byte 9 */
  uint8_t transaction_id[4];                                /* bytes 10 to 13 */
  uint8_t participant_reference_number[8];                  /* bytes 14 to 21 */
  uint8_t security_symbol[11];                              /* bytes 22 to 32 */
  uint8_t instrument_type;                                  /* byte 33 */
  SaleConditions sale_conditions;                           /* bytes 34 to 37 */
  uint8_t trade_price[8];                                   /* bytes 38 to 45 */
  uint8_t fractional_trade_volume[8];                       /* bytes 46 to 53 */
  uint8_t sellers_sale_days;                                /* byte 54 */
  uint8_t stop_stock_indicator;                             /* byte 55 */
  uint8_t trade_through_exempt_indicator;                   /* byte 56 */
  uint8_t trade_reporting_facility_id;                      /* byte 57 */
  uint8_t original_participant_reference_number[8];         /* bytes 58 to 65 */
  Timestamp2 timestamp_2;                                   /* bytes 66 to 73 */
  uint8_t cancel_error_action;                              /* byte 74 */
  uint8_t short_sale_restriction_indicator;                 /* byte 75 */
  uint8_t primary_listing_market_participant_id;            /* byte 76 */
  uint8_t financial_status_indicator;                       /* byte 77 */
  FractionalConsolidatedData fractional_consolidated_data;  /* bytes 78 to 115 */
  FractionalParticipantData fractional_participant_data;    /* bytes 116 to 160 */
} FractionalTradeCancelErrorMessage;

/* any Fractional Trade Cancel Error Message at all: every byte one the checker chooses */
static void any_fractional_trade_cancel_error_message(FractionalTradeCancelErrorMessage *record) {
  record->participant_id = arbitrary();
  any_timestamp1(&record->timestamp_1);
  record->message_id = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->transaction_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->participant_reference_number[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->security_symbol[i] = arbitrary(); }
  record->instrument_type = arbitrary();
  any_sale_conditions(&record->sale_conditions);
  for (size_t i = 0; i < 8; i++) { record->trade_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->fractional_trade_volume[i] = arbitrary(); }
  record->sellers_sale_days = arbitrary();
  record->stop_stock_indicator = arbitrary();
  record->trade_through_exempt_indicator = arbitrary();
  record->trade_reporting_facility_id = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->original_participant_reference_number[i] = arbitrary(); }
  any_timestamp2(&record->timestamp_2);
  record->cancel_error_action = arbitrary();
  record->short_sale_restriction_indicator = arbitrary();
  record->primary_listing_market_participant_id = arbitrary();
  record->financial_status_indicator = arbitrary();
  any_fractional_consolidated_data(&record->fractional_consolidated_data);
  any_fractional_participant_data(&record->fractional_participant_data);
}

/* Fractional Trade Cancel Error Message to the wire: 161 bytes from at, returning where the next byte goes */
static size_t encode_fractional_trade_cancel_error_message(const FractionalTradeCancelErrorMessage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->participant_id;
  at = encode_timestamp1(&record->timestamp_1, wire, at);
  wire[at++] = record->message_id;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->transaction_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->participant_reference_number[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->security_symbol[i]; }
  wire[at++] = record->instrument_type;
  at = encode_sale_conditions(&record->sale_conditions, wire, at);
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->trade_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->fractional_trade_volume[i]; }
  wire[at++] = record->sellers_sale_days;
  wire[at++] = record->stop_stock_indicator;
  wire[at++] = record->trade_through_exempt_indicator;
  wire[at++] = record->trade_reporting_facility_id;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->original_participant_reference_number[i]; }
  at = encode_timestamp2(&record->timestamp_2, wire, at);
  wire[at++] = record->cancel_error_action;
  wire[at++] = record->short_sale_restriction_indicator;
  wire[at++] = record->primary_listing_market_participant_id;
  wire[at++] = record->financial_status_indicator;
  at = encode_fractional_consolidated_data(&record->fractional_consolidated_data, wire, at);
  at = encode_fractional_participant_data(&record->fractional_participant_data, wire, at);

  return at;
}

/* Fractional Trade Cancel Error Message off the wire: 161 bytes from at, returning where the next byte lies */
static size_t decode_fractional_trade_cancel_error_message(FractionalTradeCancelErrorMessage *record, const uint8_t *wire, size_t at) {
  record->participant_id = wire[at++];
  at = decode_timestamp1(&record->timestamp_1, wire, at);
  record->message_id = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->transaction_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->participant_reference_number[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->security_symbol[i] = wire[at++]; }
  record->instrument_type = wire[at++];
  at = decode_sale_conditions(&record->sale_conditions, wire, at);
  for (size_t i = 0; i < 8; i++) { record->trade_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->fractional_trade_volume[i] = wire[at++]; }
  record->sellers_sale_days = wire[at++];
  record->stop_stock_indicator = wire[at++];
  record->trade_through_exempt_indicator = wire[at++];
  record->trade_reporting_facility_id = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->original_participant_reference_number[i] = wire[at++]; }
  at = decode_timestamp2(&record->timestamp_2, wire, at);
  record->cancel_error_action = wire[at++];
  record->short_sale_restriction_indicator = wire[at++];
  record->primary_listing_market_participant_id = wire[at++];
  record->financial_status_indicator = wire[at++];
  at = decode_fractional_consolidated_data(&record->fractional_consolidated_data, wire, at);
  at = decode_fractional_participant_data(&record->fractional_participant_data, wire, at);

  return at;
}

/* what was read of Fractional Trade Cancel Error Message is what was written, byte for byte */
static void equal_fractional_trade_cancel_error_message(const FractionalTradeCancelErrorMessage *read, const FractionalTradeCancelErrorMessage *written) {
  assert(read->participant_id == written->participant_id);
  equal_timestamp1(&read->timestamp_1, &written->timestamp_1);
  assert(read->message_id == written->message_id);
  for (size_t i = 0; i < 4; i++) { assert(read->transaction_id[i] == written->transaction_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->participant_reference_number[i] == written->participant_reference_number[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->security_symbol[i] == written->security_symbol[i]); }
  assert(read->instrument_type == written->instrument_type);
  equal_sale_conditions(&read->sale_conditions, &written->sale_conditions);
  for (size_t i = 0; i < 8; i++) { assert(read->trade_price[i] == written->trade_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->fractional_trade_volume[i] == written->fractional_trade_volume[i]); }
  assert(read->sellers_sale_days == written->sellers_sale_days);
  assert(read->stop_stock_indicator == written->stop_stock_indicator);
  assert(read->trade_through_exempt_indicator == written->trade_through_exempt_indicator);
  assert(read->trade_reporting_facility_id == written->trade_reporting_facility_id);
  for (size_t i = 0; i < 8; i++) { assert(read->original_participant_reference_number[i] == written->original_participant_reference_number[i]); }
  equal_timestamp2(&read->timestamp_2, &written->timestamp_2);
  assert(read->cancel_error_action == written->cancel_error_action);
  assert(read->short_sale_restriction_indicator == written->short_sale_restriction_indicator);
  assert(read->primary_listing_market_participant_id == written->primary_listing_market_participant_id);
  assert(read->financial_status_indicator == written->financial_status_indicator);
  equal_fractional_consolidated_data(&read->fractional_consolidated_data, &written->fractional_consolidated_data);
  equal_fractional_participant_data(&read->fractional_participant_data, &written->fractional_participant_data);
}

/* Fractional Trade Cancel Error Message: written and read back, then read and written back */
static void check_fractional_trade_cancel_error_message(void) {
  FractionalTradeCancelErrorMessage sent;
  FractionalTradeCancelErrorMessage got;
  uint8_t wire[161];
  uint8_t again[161];

  any_fractional_trade_cancel_error_message(&sent);
  assert(encode_fractional_trade_cancel_error_message(&sent, wire, 0) == 161);
  assert(decode_fractional_trade_cancel_error_message(&got, wire, 0) == 161);
  equal_fractional_trade_cancel_error_message(&got, &sent);

  for (size_t i = 0; i < 161; i++) { wire[i] = arbitrary(); }
  assert(decode_fractional_trade_cancel_error_message(&got, wire, 0) == 161);
  assert(encode_fractional_trade_cancel_error_message(&got, again, 0) == 161);
  for (size_t i = 0; i < 161; i++) { assert(again[i] == wire[i]); }
}

/* ---- What esbmc checks ------------------------------------------------------- */

/* every record of the protocol, each on its own buffers */
static void checks(void) {
  check_sip_block_timestamp();
  check_timestamp1();
  check_start_of_end_of_day_summary_message();
  check_end_of_end_of_day_summary_message();
  check_start_of_start_of_day_summary_message();
  check_end_of_start_of_day_summary_message();
  check_start_of_day_message();
  check_reset_block_sequence_number_message();
  check_disaster_recovery_data_center_activation_message();
  check_line_integrity_message();
  check_end_of_day_message();
  check_index_message();
  check_bid_and_offer_index_message();
  check_market_wide_circuit_breaker_decline_level_status_message();
  check_market_wide_circuit_breaker_status_message();
  check_approximate_trades_and_total_dollar_value_message();
  check_crossing_session_summary_message();
  check_sale_conditions();
  check_prior_day_trade_date_and_time();
  check_prior_day_corrected_trade();
  check_prior_day_original_trade();
  check_prior_day_trade_correction_message();
  check_fractional_prior_day_corrected_trade();
  check_fractional_prior_day_original_trade();
  check_fractional_prior_day_trade_correction_message();
  check_prior_day_trade_message();
  check_fractional_prior_day_trade_message();
  check_prior_day_trade_cancel_error_message();
  check_fractional_prior_day_trade_cancel_error_message();
  check_consolidated_start_of_day_summary_message();
  check_participant_start_of_day_summary_message();
  check_consolidated_end_of_day_summary_message();
  check_fractional_consolidated_end_of_day_summary_message();
  check_participant_end_of_day_summary_message();
  check_fractional_participant_end_of_day_summary_message();
  check_auction_status_message();
  check_corrected_trade();
  check_timestamp2();
  check_original_trade();
  check_consolidated_data();
  check_participant_data();
  check_trade_correction_message();
  check_fractional_corrected_trade();
  check_fractional_original_trade();
  check_fractional_consolidated_data();
  check_fractional_participant_data();
  check_fractional_trade_correction_message();
  check_long_trade_message();
  check_fractional_long_trade_message();
  check_trading_status_message();
  check_short_trade_message();
  check_fractional_short_trade_message();
  check_trade_cancel_error_message();
  check_fractional_trade_cancel_error_message();
}

int main(void) {
#ifdef CONCRETE
  for (pattern = 0; pattern < 4; pattern++) { checks(); }
#else
  checks();
#endif

  return 0;
}
