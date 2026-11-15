// tmx/mx/solamulticast/Mx_SolaMulticast_v1_12_2.c
/*
 * TMX Group Sola Multicast
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
 *   - the dispatch that chooses a message by its type
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

/* ---- Message Header: 11 bytes ------------------------------------------------ */

/* Hsvf Udp Market Data Packet Header */
typedef struct {
  uint8_t sequence_number[9];  /* bytes 0 to 8 */
  uint8_t message_type[2];     /* bytes 9 to 10 */
} MessageHeader;

/* any Message Header at all: every byte one the checker chooses */
static void any_message_header(MessageHeader *record) {
  for (size_t i = 0; i < 9; i++) { record->sequence_number[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->message_type[i] = arbitrary(); }
}

/* Message Header to the wire: 11 bytes from at, returning where the next byte goes */
static size_t encode_message_header(const MessageHeader *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 9; i++) { wire[at++] = record->sequence_number[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->message_type[i]; }

  return at;
}

/* Message Header off the wire: 11 bytes from at, returning where the next byte lies */
static size_t decode_message_header(MessageHeader *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 9; i++) { record->sequence_number[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->message_type[i] = wire[at++]; }

  return at;
}

/* what was read of Message Header is what was written, byte for byte */
static void equal_message_header(const MessageHeader *read, const MessageHeader *written) {
  for (size_t i = 0; i < 9; i++) { assert(read->sequence_number[i] == written->sequence_number[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->message_type[i] == written->message_type[i]); }
}

/* Message Header: written and read back, then read and written back */
static void check_message_header(void) {
  MessageHeader sent;
  MessageHeader got;
  uint8_t wire[11];
  uint8_t again[11];

  any_message_header(&sent);
  assert(encode_message_header(&sent, wire, 0) == 11);
  assert(decode_message_header(&got, wire, 0) == 11);
  equal_message_header(&got, &sent);

  for (size_t i = 0; i < 11; i++) { wire[i] = arbitrary(); }
  assert(decode_message_header(&got, wire, 0) == 11);
  assert(encode_message_header(&got, again, 0) == 11);
  for (size_t i = 0; i < 11; i++) { assert(again[i] == wire[i]); }
}

/* ---- Long Message Header: 12 bytes ------------------------------------------- */

/* The guide states these fields once, as Table 3: Long Message Header, for every message the eight Table 2 frames do not. Sequence Number and Message Type are read by the packet, so they are not repeated here. */
typedef struct {
  uint8_t message_timestamp[12];  /* bytes 0 to 11 */
} LongMessageHeader;

/* any Long Message Header at all: every byte one the checker chooses */
static void any_long_message_header(LongMessageHeader *record) {
  for (size_t i = 0; i < 12; i++) { record->message_timestamp[i] = arbitrary(); }
}

/* Long Message Header to the wire: 12 bytes from at, returning where the next byte goes */
static size_t encode_long_message_header(const LongMessageHeader *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->message_timestamp[i]; }

  return at;
}

/* Long Message Header off the wire: 12 bytes from at, returning where the next byte lies */
static size_t decode_long_message_header(LongMessageHeader *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 12; i++) { record->message_timestamp[i] = wire[at++]; }

  return at;
}

/* what was read of Long Message Header is what was written, byte for byte */
static void equal_long_message_header(const LongMessageHeader *read, const LongMessageHeader *written) {
  for (size_t i = 0; i < 12; i++) { assert(read->message_timestamp[i] == written->message_timestamp[i]); }
}

/* Long Message Header: written and read back, then read and written back */
static void check_long_message_header(void) {
  LongMessageHeader sent;
  LongMessageHeader got;
  uint8_t wire[12];
  uint8_t again[12];

  any_long_message_header(&sent);
  assert(encode_long_message_header(&sent, wire, 0) == 12);
  assert(decode_long_message_header(&got, wire, 0) == 12);
  equal_long_message_header(&got, &sent);

  for (size_t i = 0; i < 12; i++) { wire[i] = arbitrary(); }
  assert(decode_long_message_header(&got, wire, 0) == 12);
  assert(encode_long_message_header(&got, again, 0) == 12);
  for (size_t i = 0; i < 12; i++) { assert(again[i] == wire[i]); }
}

/* ---- Strike Price Negative Whole Pair: 8 bytes ------------------------------- */

typedef struct {
  uint8_t raw_strike_price[7];              /* bytes 0 to 6 */
  uint8_t strike_price_fraction_indicator;  /* byte 7 */
} StrikePriceNegativeWholePair;

/* any Strike Price Negative Whole Pair at all: every byte one the checker chooses */
static void any_strike_price_negative_whole_pair(StrikePriceNegativeWholePair *record) {
  for (size_t i = 0; i < 7; i++) { record->raw_strike_price[i] = arbitrary(); }
  record->strike_price_fraction_indicator = arbitrary();
}

/* Strike Price Negative Whole Pair to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_strike_price_negative_whole_pair(const StrikePriceNegativeWholePair *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->raw_strike_price[i]; }
  wire[at++] = record->strike_price_fraction_indicator;

  return at;
}

/* Strike Price Negative Whole Pair off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_strike_price_negative_whole_pair(StrikePriceNegativeWholePair *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { record->raw_strike_price[i] = wire[at++]; }
  record->strike_price_fraction_indicator = wire[at++];

  return at;
}

/* what was read of Strike Price Negative Whole Pair is what was written, byte for byte */
static void equal_strike_price_negative_whole_pair(const StrikePriceNegativeWholePair *read, const StrikePriceNegativeWholePair *written) {
  for (size_t i = 0; i < 7; i++) { assert(read->raw_strike_price[i] == written->raw_strike_price[i]); }
  assert(read->strike_price_fraction_indicator == written->strike_price_fraction_indicator);
}

/* Strike Price Negative Whole Pair: written and read back, then read and written back */
static void check_strike_price_negative_whole_pair(void) {
  StrikePriceNegativeWholePair sent;
  StrikePriceNegativeWholePair got;
  uint8_t wire[8];
  uint8_t again[8];

  any_strike_price_negative_whole_pair(&sent);
  assert(encode_strike_price_negative_whole_pair(&sent, wire, 0) == 8);
  assert(decode_strike_price_negative_whole_pair(&got, wire, 0) == 8);
  equal_strike_price_negative_whole_pair(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_strike_price_negative_whole_pair(&got, wire, 0) == 8);
  assert(encode_strike_price_negative_whole_pair(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Strike Price Negative Ten Pair: 8 bytes --------------------------------- */

typedef struct {
  uint8_t raw_strike_price[7];              /* bytes 0 to 6 */
  uint8_t strike_price_fraction_indicator;  /* byte 7 */
} StrikePriceNegativeTenPair;

/* any Strike Price Negative Ten Pair at all: every byte one the checker chooses */
static void any_strike_price_negative_ten_pair(StrikePriceNegativeTenPair *record) {
  for (size_t i = 0; i < 7; i++) { record->raw_strike_price[i] = arbitrary(); }
  record->strike_price_fraction_indicator = arbitrary();
}

/* Strike Price Negative Ten Pair to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_strike_price_negative_ten_pair(const StrikePriceNegativeTenPair *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->raw_strike_price[i]; }
  wire[at++] = record->strike_price_fraction_indicator;

  return at;
}

/* Strike Price Negative Ten Pair off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_strike_price_negative_ten_pair(StrikePriceNegativeTenPair *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { record->raw_strike_price[i] = wire[at++]; }
  record->strike_price_fraction_indicator = wire[at++];

  return at;
}

/* what was read of Strike Price Negative Ten Pair is what was written, byte for byte */
static void equal_strike_price_negative_ten_pair(const StrikePriceNegativeTenPair *read, const StrikePriceNegativeTenPair *written) {
  for (size_t i = 0; i < 7; i++) { assert(read->raw_strike_price[i] == written->raw_strike_price[i]); }
  assert(read->strike_price_fraction_indicator == written->strike_price_fraction_indicator);
}

/* Strike Price Negative Ten Pair: written and read back, then read and written back */
static void check_strike_price_negative_ten_pair(void) {
  StrikePriceNegativeTenPair sent;
  StrikePriceNegativeTenPair got;
  uint8_t wire[8];
  uint8_t again[8];

  any_strike_price_negative_ten_pair(&sent);
  assert(encode_strike_price_negative_ten_pair(&sent, wire, 0) == 8);
  assert(decode_strike_price_negative_ten_pair(&got, wire, 0) == 8);
  equal_strike_price_negative_ten_pair(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_strike_price_negative_ten_pair(&got, wire, 0) == 8);
  assert(encode_strike_price_negative_ten_pair(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Strike Price Negative Hundred Pair: 8 bytes ----------------------------- */

typedef struct {
  uint8_t raw_strike_price[7];              /* bytes 0 to 6 */
  uint8_t strike_price_fraction_indicator;  /* byte 7 */
} StrikePriceNegativeHundredPair;

/* any Strike Price Negative Hundred Pair at all: every byte one the checker chooses */
static void any_strike_price_negative_hundred_pair(StrikePriceNegativeHundredPair *record) {
  for (size_t i = 0; i < 7; i++) { record->raw_strike_price[i] = arbitrary(); }
  record->strike_price_fraction_indicator = arbitrary();
}

/* Strike Price Negative Hundred Pair to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_strike_price_negative_hundred_pair(const StrikePriceNegativeHundredPair *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->raw_strike_price[i]; }
  wire[at++] = record->strike_price_fraction_indicator;

  return at;
}

/* Strike Price Negative Hundred Pair off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_strike_price_negative_hundred_pair(StrikePriceNegativeHundredPair *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { record->raw_strike_price[i] = wire[at++]; }
  record->strike_price_fraction_indicator = wire[at++];

  return at;
}

/* what was read of Strike Price Negative Hundred Pair is what was written, byte for byte */
static void equal_strike_price_negative_hundred_pair(const StrikePriceNegativeHundredPair *read, const StrikePriceNegativeHundredPair *written) {
  for (size_t i = 0; i < 7; i++) { assert(read->raw_strike_price[i] == written->raw_strike_price[i]); }
  assert(read->strike_price_fraction_indicator == written->strike_price_fraction_indicator);
}

/* Strike Price Negative Hundred Pair: written and read back, then read and written back */
static void check_strike_price_negative_hundred_pair(void) {
  StrikePriceNegativeHundredPair sent;
  StrikePriceNegativeHundredPair got;
  uint8_t wire[8];
  uint8_t again[8];

  any_strike_price_negative_hundred_pair(&sent);
  assert(encode_strike_price_negative_hundred_pair(&sent, wire, 0) == 8);
  assert(decode_strike_price_negative_hundred_pair(&got, wire, 0) == 8);
  equal_strike_price_negative_hundred_pair(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_strike_price_negative_hundred_pair(&got, wire, 0) == 8);
  assert(encode_strike_price_negative_hundred_pair(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Strike Price Negative Thousand Pair: 8 bytes ---------------------------- */

typedef struct {
  uint8_t raw_strike_price[7];              /* bytes 0 to 6 */
  uint8_t strike_price_fraction_indicator;  /* byte 7 */
} StrikePriceNegativeThousandPair;

/* any Strike Price Negative Thousand Pair at all: every byte one the checker chooses */
static void any_strike_price_negative_thousand_pair(StrikePriceNegativeThousandPair *record) {
  for (size_t i = 0; i < 7; i++) { record->raw_strike_price[i] = arbitrary(); }
  record->strike_price_fraction_indicator = arbitrary();
}

/* Strike Price Negative Thousand Pair to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_strike_price_negative_thousand_pair(const StrikePriceNegativeThousandPair *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->raw_strike_price[i]; }
  wire[at++] = record->strike_price_fraction_indicator;

  return at;
}

/* Strike Price Negative Thousand Pair off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_strike_price_negative_thousand_pair(StrikePriceNegativeThousandPair *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { record->raw_strike_price[i] = wire[at++]; }
  record->strike_price_fraction_indicator = wire[at++];

  return at;
}

/* what was read of Strike Price Negative Thousand Pair is what was written, byte for byte */
static void equal_strike_price_negative_thousand_pair(const StrikePriceNegativeThousandPair *read, const StrikePriceNegativeThousandPair *written) {
  for (size_t i = 0; i < 7; i++) { assert(read->raw_strike_price[i] == written->raw_strike_price[i]); }
  assert(read->strike_price_fraction_indicator == written->strike_price_fraction_indicator);
}

/* Strike Price Negative Thousand Pair: written and read back, then read and written back */
static void check_strike_price_negative_thousand_pair(void) {
  StrikePriceNegativeThousandPair sent;
  StrikePriceNegativeThousandPair got;
  uint8_t wire[8];
  uint8_t again[8];

  any_strike_price_negative_thousand_pair(&sent);
  assert(encode_strike_price_negative_thousand_pair(&sent, wire, 0) == 8);
  assert(decode_strike_price_negative_thousand_pair(&got, wire, 0) == 8);
  equal_strike_price_negative_thousand_pair(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_strike_price_negative_thousand_pair(&got, wire, 0) == 8);
  assert(encode_strike_price_negative_thousand_pair(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Strike Price Negative Ten Thousand Pair: 8 bytes ------------------------ */

typedef struct {
  uint8_t raw_strike_price[7];              /* bytes 0 to 6 */
  uint8_t strike_price_fraction_indicator;  /* byte 7 */
} StrikePriceNegativeTenThousandPair;

/* any Strike Price Negative Ten Thousand Pair at all: every byte one the checker chooses */
static void any_strike_price_negative_ten_thousand_pair(StrikePriceNegativeTenThousandPair *record) {
  for (size_t i = 0; i < 7; i++) { record->raw_strike_price[i] = arbitrary(); }
  record->strike_price_fraction_indicator = arbitrary();
}

/* Strike Price Negative Ten Thousand Pair to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_strike_price_negative_ten_thousand_pair(const StrikePriceNegativeTenThousandPair *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->raw_strike_price[i]; }
  wire[at++] = record->strike_price_fraction_indicator;

  return at;
}

/* Strike Price Negative Ten Thousand Pair off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_strike_price_negative_ten_thousand_pair(StrikePriceNegativeTenThousandPair *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { record->raw_strike_price[i] = wire[at++]; }
  record->strike_price_fraction_indicator = wire[at++];

  return at;
}

/* what was read of Strike Price Negative Ten Thousand Pair is what was written, byte for byte */
static void equal_strike_price_negative_ten_thousand_pair(const StrikePriceNegativeTenThousandPair *read, const StrikePriceNegativeTenThousandPair *written) {
  for (size_t i = 0; i < 7; i++) { assert(read->raw_strike_price[i] == written->raw_strike_price[i]); }
  assert(read->strike_price_fraction_indicator == written->strike_price_fraction_indicator);
}

/* Strike Price Negative Ten Thousand Pair: written and read back, then read and written back */
static void check_strike_price_negative_ten_thousand_pair(void) {
  StrikePriceNegativeTenThousandPair sent;
  StrikePriceNegativeTenThousandPair got;
  uint8_t wire[8];
  uint8_t again[8];

  any_strike_price_negative_ten_thousand_pair(&sent);
  assert(encode_strike_price_negative_ten_thousand_pair(&sent, wire, 0) == 8);
  assert(decode_strike_price_negative_ten_thousand_pair(&got, wire, 0) == 8);
  equal_strike_price_negative_ten_thousand_pair(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_strike_price_negative_ten_thousand_pair(&got, wire, 0) == 8);
  assert(encode_strike_price_negative_ten_thousand_pair(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Strike Price Negative Hundred Thousand Pair: 8 bytes -------------------- */

typedef struct {
  uint8_t raw_strike_price[7];              /* bytes 0 to 6 */
  uint8_t strike_price_fraction_indicator;  /* byte 7 */
} StrikePriceNegativeHundredThousandPair;

/* any Strike Price Negative Hundred Thousand Pair at all: every byte one the checker chooses */
static void any_strike_price_negative_hundred_thousand_pair(StrikePriceNegativeHundredThousandPair *record) {
  for (size_t i = 0; i < 7; i++) { record->raw_strike_price[i] = arbitrary(); }
  record->strike_price_fraction_indicator = arbitrary();
}

/* Strike Price Negative Hundred Thousand Pair to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_strike_price_negative_hundred_thousand_pair(const StrikePriceNegativeHundredThousandPair *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->raw_strike_price[i]; }
  wire[at++] = record->strike_price_fraction_indicator;

  return at;
}

/* Strike Price Negative Hundred Thousand Pair off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_strike_price_negative_hundred_thousand_pair(StrikePriceNegativeHundredThousandPair *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { record->raw_strike_price[i] = wire[at++]; }
  record->strike_price_fraction_indicator = wire[at++];

  return at;
}

/* what was read of Strike Price Negative Hundred Thousand Pair is what was written, byte for byte */
static void equal_strike_price_negative_hundred_thousand_pair(const StrikePriceNegativeHundredThousandPair *read, const StrikePriceNegativeHundredThousandPair *written) {
  for (size_t i = 0; i < 7; i++) { assert(read->raw_strike_price[i] == written->raw_strike_price[i]); }
  assert(read->strike_price_fraction_indicator == written->strike_price_fraction_indicator);
}

/* Strike Price Negative Hundred Thousand Pair: written and read back, then read and written back */
static void check_strike_price_negative_hundred_thousand_pair(void) {
  StrikePriceNegativeHundredThousandPair sent;
  StrikePriceNegativeHundredThousandPair got;
  uint8_t wire[8];
  uint8_t again[8];

  any_strike_price_negative_hundred_thousand_pair(&sent);
  assert(encode_strike_price_negative_hundred_thousand_pair(&sent, wire, 0) == 8);
  assert(decode_strike_price_negative_hundred_thousand_pair(&got, wire, 0) == 8);
  equal_strike_price_negative_hundred_thousand_pair(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_strike_price_negative_hundred_thousand_pair(&got, wire, 0) == 8);
  assert(encode_strike_price_negative_hundred_thousand_pair(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Strike Price Negative Million Pair: 8 bytes ----------------------------- */

typedef struct {
  uint8_t raw_strike_price[7];              /* bytes 0 to 6 */
  uint8_t strike_price_fraction_indicator;  /* byte 7 */
} StrikePriceNegativeMillionPair;

/* any Strike Price Negative Million Pair at all: every byte one the checker chooses */
static void any_strike_price_negative_million_pair(StrikePriceNegativeMillionPair *record) {
  for (size_t i = 0; i < 7; i++) { record->raw_strike_price[i] = arbitrary(); }
  record->strike_price_fraction_indicator = arbitrary();
}

/* Strike Price Negative Million Pair to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_strike_price_negative_million_pair(const StrikePriceNegativeMillionPair *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->raw_strike_price[i]; }
  wire[at++] = record->strike_price_fraction_indicator;

  return at;
}

/* Strike Price Negative Million Pair off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_strike_price_negative_million_pair(StrikePriceNegativeMillionPair *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { record->raw_strike_price[i] = wire[at++]; }
  record->strike_price_fraction_indicator = wire[at++];

  return at;
}

/* what was read of Strike Price Negative Million Pair is what was written, byte for byte */
static void equal_strike_price_negative_million_pair(const StrikePriceNegativeMillionPair *read, const StrikePriceNegativeMillionPair *written) {
  for (size_t i = 0; i < 7; i++) { assert(read->raw_strike_price[i] == written->raw_strike_price[i]); }
  assert(read->strike_price_fraction_indicator == written->strike_price_fraction_indicator);
}

/* Strike Price Negative Million Pair: written and read back, then read and written back */
static void check_strike_price_negative_million_pair(void) {
  StrikePriceNegativeMillionPair sent;
  StrikePriceNegativeMillionPair got;
  uint8_t wire[8];
  uint8_t again[8];

  any_strike_price_negative_million_pair(&sent);
  assert(encode_strike_price_negative_million_pair(&sent, wire, 0) == 8);
  assert(decode_strike_price_negative_million_pair(&got, wire, 0) == 8);
  equal_strike_price_negative_million_pair(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_strike_price_negative_million_pair(&got, wire, 0) == 8);
  assert(encode_strike_price_negative_million_pair(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Strike Price Numeric Pair: 8 bytes -------------------------------------- */

typedef struct {
  uint8_t strike_price[7];                  /* bytes 0 to 6 */
  uint8_t strike_price_fraction_indicator;  /* byte 7 */
} StrikePriceNumericPair;

/* any Strike Price Numeric Pair at all: every byte one the checker chooses */
static void any_strike_price_numeric_pair(StrikePriceNumericPair *record) {
  for (size_t i = 0; i < 7; i++) { record->strike_price[i] = arbitrary(); }
  record->strike_price_fraction_indicator = arbitrary();
}

/* Strike Price Numeric Pair to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_strike_price_numeric_pair(const StrikePriceNumericPair *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->strike_price[i]; }
  wire[at++] = record->strike_price_fraction_indicator;

  return at;
}

/* Strike Price Numeric Pair off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_strike_price_numeric_pair(StrikePriceNumericPair *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { record->strike_price[i] = wire[at++]; }
  record->strike_price_fraction_indicator = wire[at++];

  return at;
}

/* what was read of Strike Price Numeric Pair is what was written, byte for byte */
static void equal_strike_price_numeric_pair(const StrikePriceNumericPair *read, const StrikePriceNumericPair *written) {
  for (size_t i = 0; i < 7; i++) { assert(read->strike_price[i] == written->strike_price[i]); }
  assert(read->strike_price_fraction_indicator == written->strike_price_fraction_indicator);
}

/* Strike Price Numeric Pair: written and read back, then read and written back */
static void check_strike_price_numeric_pair(void) {
  StrikePriceNumericPair sent;
  StrikePriceNumericPair got;
  uint8_t wire[8];
  uint8_t again[8];

  any_strike_price_numeric_pair(&sent);
  assert(encode_strike_price_numeric_pair(&sent, wire, 0) == 8);
  assert(decode_strike_price_numeric_pair(&got, wire, 0) == 8);
  equal_strike_price_numeric_pair(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_strike_price_numeric_pair(&got, wire, 0) == 8);
  assert(encode_strike_price_numeric_pair(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Trade Price Negative Whole Pair: 8 bytes -------------------------------- */

typedef struct {
  uint8_t raw_trade_price[7];              /* bytes 0 to 6 */
  uint8_t trade_price_fraction_indicator;  /* byte 7 */
} TradePriceNegativeWholePair;

/* any Trade Price Negative Whole Pair at all: every byte one the checker chooses */
static void any_trade_price_negative_whole_pair(TradePriceNegativeWholePair *record) {
  for (size_t i = 0; i < 7; i++) { record->raw_trade_price[i] = arbitrary(); }
  record->trade_price_fraction_indicator = arbitrary();
}

/* Trade Price Negative Whole Pair to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_trade_price_negative_whole_pair(const TradePriceNegativeWholePair *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->raw_trade_price[i]; }
  wire[at++] = record->trade_price_fraction_indicator;

  return at;
}

/* Trade Price Negative Whole Pair off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_trade_price_negative_whole_pair(TradePriceNegativeWholePair *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { record->raw_trade_price[i] = wire[at++]; }
  record->trade_price_fraction_indicator = wire[at++];

  return at;
}

/* what was read of Trade Price Negative Whole Pair is what was written, byte for byte */
static void equal_trade_price_negative_whole_pair(const TradePriceNegativeWholePair *read, const TradePriceNegativeWholePair *written) {
  for (size_t i = 0; i < 7; i++) { assert(read->raw_trade_price[i] == written->raw_trade_price[i]); }
  assert(read->trade_price_fraction_indicator == written->trade_price_fraction_indicator);
}

/* Trade Price Negative Whole Pair: written and read back, then read and written back */
static void check_trade_price_negative_whole_pair(void) {
  TradePriceNegativeWholePair sent;
  TradePriceNegativeWholePair got;
  uint8_t wire[8];
  uint8_t again[8];

  any_trade_price_negative_whole_pair(&sent);
  assert(encode_trade_price_negative_whole_pair(&sent, wire, 0) == 8);
  assert(decode_trade_price_negative_whole_pair(&got, wire, 0) == 8);
  equal_trade_price_negative_whole_pair(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_trade_price_negative_whole_pair(&got, wire, 0) == 8);
  assert(encode_trade_price_negative_whole_pair(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Trade Price Negative Ten Pair: 8 bytes ---------------------------------- */

typedef struct {
  uint8_t raw_trade_price[7];              /* bytes 0 to 6 */
  uint8_t trade_price_fraction_indicator;  /* byte 7 */
} TradePriceNegativeTenPair;

/* any Trade Price Negative Ten Pair at all: every byte one the checker chooses */
static void any_trade_price_negative_ten_pair(TradePriceNegativeTenPair *record) {
  for (size_t i = 0; i < 7; i++) { record->raw_trade_price[i] = arbitrary(); }
  record->trade_price_fraction_indicator = arbitrary();
}

/* Trade Price Negative Ten Pair to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_trade_price_negative_ten_pair(const TradePriceNegativeTenPair *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->raw_trade_price[i]; }
  wire[at++] = record->trade_price_fraction_indicator;

  return at;
}

/* Trade Price Negative Ten Pair off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_trade_price_negative_ten_pair(TradePriceNegativeTenPair *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { record->raw_trade_price[i] = wire[at++]; }
  record->trade_price_fraction_indicator = wire[at++];

  return at;
}

/* what was read of Trade Price Negative Ten Pair is what was written, byte for byte */
static void equal_trade_price_negative_ten_pair(const TradePriceNegativeTenPair *read, const TradePriceNegativeTenPair *written) {
  for (size_t i = 0; i < 7; i++) { assert(read->raw_trade_price[i] == written->raw_trade_price[i]); }
  assert(read->trade_price_fraction_indicator == written->trade_price_fraction_indicator);
}

/* Trade Price Negative Ten Pair: written and read back, then read and written back */
static void check_trade_price_negative_ten_pair(void) {
  TradePriceNegativeTenPair sent;
  TradePriceNegativeTenPair got;
  uint8_t wire[8];
  uint8_t again[8];

  any_trade_price_negative_ten_pair(&sent);
  assert(encode_trade_price_negative_ten_pair(&sent, wire, 0) == 8);
  assert(decode_trade_price_negative_ten_pair(&got, wire, 0) == 8);
  equal_trade_price_negative_ten_pair(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_trade_price_negative_ten_pair(&got, wire, 0) == 8);
  assert(encode_trade_price_negative_ten_pair(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Trade Price Negative Hundred Pair: 8 bytes ------------------------------ */

typedef struct {
  uint8_t raw_trade_price[7];              /* bytes 0 to 6 */
  uint8_t trade_price_fraction_indicator;  /* byte 7 */
} TradePriceNegativeHundredPair;

/* any Trade Price Negative Hundred Pair at all: every byte one the checker chooses */
static void any_trade_price_negative_hundred_pair(TradePriceNegativeHundredPair *record) {
  for (size_t i = 0; i < 7; i++) { record->raw_trade_price[i] = arbitrary(); }
  record->trade_price_fraction_indicator = arbitrary();
}

/* Trade Price Negative Hundred Pair to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_trade_price_negative_hundred_pair(const TradePriceNegativeHundredPair *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->raw_trade_price[i]; }
  wire[at++] = record->trade_price_fraction_indicator;

  return at;
}

/* Trade Price Negative Hundred Pair off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_trade_price_negative_hundred_pair(TradePriceNegativeHundredPair *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { record->raw_trade_price[i] = wire[at++]; }
  record->trade_price_fraction_indicator = wire[at++];

  return at;
}

/* what was read of Trade Price Negative Hundred Pair is what was written, byte for byte */
static void equal_trade_price_negative_hundred_pair(const TradePriceNegativeHundredPair *read, const TradePriceNegativeHundredPair *written) {
  for (size_t i = 0; i < 7; i++) { assert(read->raw_trade_price[i] == written->raw_trade_price[i]); }
  assert(read->trade_price_fraction_indicator == written->trade_price_fraction_indicator);
}

/* Trade Price Negative Hundred Pair: written and read back, then read and written back */
static void check_trade_price_negative_hundred_pair(void) {
  TradePriceNegativeHundredPair sent;
  TradePriceNegativeHundredPair got;
  uint8_t wire[8];
  uint8_t again[8];

  any_trade_price_negative_hundred_pair(&sent);
  assert(encode_trade_price_negative_hundred_pair(&sent, wire, 0) == 8);
  assert(decode_trade_price_negative_hundred_pair(&got, wire, 0) == 8);
  equal_trade_price_negative_hundred_pair(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_trade_price_negative_hundred_pair(&got, wire, 0) == 8);
  assert(encode_trade_price_negative_hundred_pair(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Trade Price Negative Thousand Pair: 8 bytes ----------------------------- */

typedef struct {
  uint8_t raw_trade_price[7];              /* bytes 0 to 6 */
  uint8_t trade_price_fraction_indicator;  /* byte 7 */
} TradePriceNegativeThousandPair;

/* any Trade Price Negative Thousand Pair at all: every byte one the checker chooses */
static void any_trade_price_negative_thousand_pair(TradePriceNegativeThousandPair *record) {
  for (size_t i = 0; i < 7; i++) { record->raw_trade_price[i] = arbitrary(); }
  record->trade_price_fraction_indicator = arbitrary();
}

/* Trade Price Negative Thousand Pair to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_trade_price_negative_thousand_pair(const TradePriceNegativeThousandPair *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->raw_trade_price[i]; }
  wire[at++] = record->trade_price_fraction_indicator;

  return at;
}

/* Trade Price Negative Thousand Pair off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_trade_price_negative_thousand_pair(TradePriceNegativeThousandPair *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { record->raw_trade_price[i] = wire[at++]; }
  record->trade_price_fraction_indicator = wire[at++];

  return at;
}

/* what was read of Trade Price Negative Thousand Pair is what was written, byte for byte */
static void equal_trade_price_negative_thousand_pair(const TradePriceNegativeThousandPair *read, const TradePriceNegativeThousandPair *written) {
  for (size_t i = 0; i < 7; i++) { assert(read->raw_trade_price[i] == written->raw_trade_price[i]); }
  assert(read->trade_price_fraction_indicator == written->trade_price_fraction_indicator);
}

/* Trade Price Negative Thousand Pair: written and read back, then read and written back */
static void check_trade_price_negative_thousand_pair(void) {
  TradePriceNegativeThousandPair sent;
  TradePriceNegativeThousandPair got;
  uint8_t wire[8];
  uint8_t again[8];

  any_trade_price_negative_thousand_pair(&sent);
  assert(encode_trade_price_negative_thousand_pair(&sent, wire, 0) == 8);
  assert(decode_trade_price_negative_thousand_pair(&got, wire, 0) == 8);
  equal_trade_price_negative_thousand_pair(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_trade_price_negative_thousand_pair(&got, wire, 0) == 8);
  assert(encode_trade_price_negative_thousand_pair(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Trade Price Negative Ten Thousand Pair: 8 bytes ------------------------- */

typedef struct {
  uint8_t raw_trade_price[7];              /* bytes 0 to 6 */
  uint8_t trade_price_fraction_indicator;  /* byte 7 */
} TradePriceNegativeTenThousandPair;

/* any Trade Price Negative Ten Thousand Pair at all: every byte one the checker chooses */
static void any_trade_price_negative_ten_thousand_pair(TradePriceNegativeTenThousandPair *record) {
  for (size_t i = 0; i < 7; i++) { record->raw_trade_price[i] = arbitrary(); }
  record->trade_price_fraction_indicator = arbitrary();
}

/* Trade Price Negative Ten Thousand Pair to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_trade_price_negative_ten_thousand_pair(const TradePriceNegativeTenThousandPair *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->raw_trade_price[i]; }
  wire[at++] = record->trade_price_fraction_indicator;

  return at;
}

/* Trade Price Negative Ten Thousand Pair off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_trade_price_negative_ten_thousand_pair(TradePriceNegativeTenThousandPair *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { record->raw_trade_price[i] = wire[at++]; }
  record->trade_price_fraction_indicator = wire[at++];

  return at;
}

/* what was read of Trade Price Negative Ten Thousand Pair is what was written, byte for byte */
static void equal_trade_price_negative_ten_thousand_pair(const TradePriceNegativeTenThousandPair *read, const TradePriceNegativeTenThousandPair *written) {
  for (size_t i = 0; i < 7; i++) { assert(read->raw_trade_price[i] == written->raw_trade_price[i]); }
  assert(read->trade_price_fraction_indicator == written->trade_price_fraction_indicator);
}

/* Trade Price Negative Ten Thousand Pair: written and read back, then read and written back */
static void check_trade_price_negative_ten_thousand_pair(void) {
  TradePriceNegativeTenThousandPair sent;
  TradePriceNegativeTenThousandPair got;
  uint8_t wire[8];
  uint8_t again[8];

  any_trade_price_negative_ten_thousand_pair(&sent);
  assert(encode_trade_price_negative_ten_thousand_pair(&sent, wire, 0) == 8);
  assert(decode_trade_price_negative_ten_thousand_pair(&got, wire, 0) == 8);
  equal_trade_price_negative_ten_thousand_pair(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_trade_price_negative_ten_thousand_pair(&got, wire, 0) == 8);
  assert(encode_trade_price_negative_ten_thousand_pair(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Trade Price Negative Hundred Thousand Pair: 8 bytes --------------------- */

typedef struct {
  uint8_t raw_trade_price[7];              /* bytes 0 to 6 */
  uint8_t trade_price_fraction_indicator;  /* byte 7 */
} TradePriceNegativeHundredThousandPair;

/* any Trade Price Negative Hundred Thousand Pair at all: every byte one the checker chooses */
static void any_trade_price_negative_hundred_thousand_pair(TradePriceNegativeHundredThousandPair *record) {
  for (size_t i = 0; i < 7; i++) { record->raw_trade_price[i] = arbitrary(); }
  record->trade_price_fraction_indicator = arbitrary();
}

/* Trade Price Negative Hundred Thousand Pair to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_trade_price_negative_hundred_thousand_pair(const TradePriceNegativeHundredThousandPair *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->raw_trade_price[i]; }
  wire[at++] = record->trade_price_fraction_indicator;

  return at;
}

/* Trade Price Negative Hundred Thousand Pair off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_trade_price_negative_hundred_thousand_pair(TradePriceNegativeHundredThousandPair *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { record->raw_trade_price[i] = wire[at++]; }
  record->trade_price_fraction_indicator = wire[at++];

  return at;
}

/* what was read of Trade Price Negative Hundred Thousand Pair is what was written, byte for byte */
static void equal_trade_price_negative_hundred_thousand_pair(const TradePriceNegativeHundredThousandPair *read, const TradePriceNegativeHundredThousandPair *written) {
  for (size_t i = 0; i < 7; i++) { assert(read->raw_trade_price[i] == written->raw_trade_price[i]); }
  assert(read->trade_price_fraction_indicator == written->trade_price_fraction_indicator);
}

/* Trade Price Negative Hundred Thousand Pair: written and read back, then read and written back */
static void check_trade_price_negative_hundred_thousand_pair(void) {
  TradePriceNegativeHundredThousandPair sent;
  TradePriceNegativeHundredThousandPair got;
  uint8_t wire[8];
  uint8_t again[8];

  any_trade_price_negative_hundred_thousand_pair(&sent);
  assert(encode_trade_price_negative_hundred_thousand_pair(&sent, wire, 0) == 8);
  assert(decode_trade_price_negative_hundred_thousand_pair(&got, wire, 0) == 8);
  equal_trade_price_negative_hundred_thousand_pair(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_trade_price_negative_hundred_thousand_pair(&got, wire, 0) == 8);
  assert(encode_trade_price_negative_hundred_thousand_pair(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Trade Price Negative Million Pair: 8 bytes ------------------------------ */

typedef struct {
  uint8_t raw_trade_price[7];              /* bytes 0 to 6 */
  uint8_t trade_price_fraction_indicator;  /* byte 7 */
} TradePriceNegativeMillionPair;

/* any Trade Price Negative Million Pair at all: every byte one the checker chooses */
static void any_trade_price_negative_million_pair(TradePriceNegativeMillionPair *record) {
  for (size_t i = 0; i < 7; i++) { record->raw_trade_price[i] = arbitrary(); }
  record->trade_price_fraction_indicator = arbitrary();
}

/* Trade Price Negative Million Pair to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_trade_price_negative_million_pair(const TradePriceNegativeMillionPair *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->raw_trade_price[i]; }
  wire[at++] = record->trade_price_fraction_indicator;

  return at;
}

/* Trade Price Negative Million Pair off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_trade_price_negative_million_pair(TradePriceNegativeMillionPair *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { record->raw_trade_price[i] = wire[at++]; }
  record->trade_price_fraction_indicator = wire[at++];

  return at;
}

/* what was read of Trade Price Negative Million Pair is what was written, byte for byte */
static void equal_trade_price_negative_million_pair(const TradePriceNegativeMillionPair *read, const TradePriceNegativeMillionPair *written) {
  for (size_t i = 0; i < 7; i++) { assert(read->raw_trade_price[i] == written->raw_trade_price[i]); }
  assert(read->trade_price_fraction_indicator == written->trade_price_fraction_indicator);
}

/* Trade Price Negative Million Pair: written and read back, then read and written back */
static void check_trade_price_negative_million_pair(void) {
  TradePriceNegativeMillionPair sent;
  TradePriceNegativeMillionPair got;
  uint8_t wire[8];
  uint8_t again[8];

  any_trade_price_negative_million_pair(&sent);
  assert(encode_trade_price_negative_million_pair(&sent, wire, 0) == 8);
  assert(decode_trade_price_negative_million_pair(&got, wire, 0) == 8);
  equal_trade_price_negative_million_pair(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_trade_price_negative_million_pair(&got, wire, 0) == 8);
  assert(encode_trade_price_negative_million_pair(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Trade Price Numeric Pair: 8 bytes --------------------------------------- */

typedef struct {
  uint8_t trade_price[7];                  /* bytes 0 to 6 */
  uint8_t trade_price_fraction_indicator;  /* byte 7 */
} TradePriceNumericPair;

/* any Trade Price Numeric Pair at all: every byte one the checker chooses */
static void any_trade_price_numeric_pair(TradePriceNumericPair *record) {
  for (size_t i = 0; i < 7; i++) { record->trade_price[i] = arbitrary(); }
  record->trade_price_fraction_indicator = arbitrary();
}

/* Trade Price Numeric Pair to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_trade_price_numeric_pair(const TradePriceNumericPair *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->trade_price[i]; }
  wire[at++] = record->trade_price_fraction_indicator;

  return at;
}

/* Trade Price Numeric Pair off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_trade_price_numeric_pair(TradePriceNumericPair *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { record->trade_price[i] = wire[at++]; }
  record->trade_price_fraction_indicator = wire[at++];

  return at;
}

/* what was read of Trade Price Numeric Pair is what was written, byte for byte */
static void equal_trade_price_numeric_pair(const TradePriceNumericPair *read, const TradePriceNumericPair *written) {
  for (size_t i = 0; i < 7; i++) { assert(read->trade_price[i] == written->trade_price[i]); }
  assert(read->trade_price_fraction_indicator == written->trade_price_fraction_indicator);
}

/* Trade Price Numeric Pair: written and read back, then read and written back */
static void check_trade_price_numeric_pair(void) {
  TradePriceNumericPair sent;
  TradePriceNumericPair got;
  uint8_t wire[8];
  uint8_t again[8];

  any_trade_price_numeric_pair(&sent);
  assert(encode_trade_price_numeric_pair(&sent, wire, 0) == 8);
  assert(decode_trade_price_numeric_pair(&got, wire, 0) == 8);
  equal_trade_price_numeric_pair(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_trade_price_numeric_pair(&got, wire, 0) == 8);
  assert(encode_trade_price_numeric_pair(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Net Change Negative Whole Pair: 8 bytes --------------------------------- */

typedef struct {
  uint8_t raw_net_change[7];              /* bytes 0 to 6 */
  uint8_t net_change_fraction_indicator;  /* byte 7 */
} NetChangeNegativeWholePair;

/* any Net Change Negative Whole Pair at all: every byte one the checker chooses */
static void any_net_change_negative_whole_pair(NetChangeNegativeWholePair *record) {
  for (size_t i = 0; i < 7; i++) { record->raw_net_change[i] = arbitrary(); }
  record->net_change_fraction_indicator = arbitrary();
}

/* Net Change Negative Whole Pair to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_net_change_negative_whole_pair(const NetChangeNegativeWholePair *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->raw_net_change[i]; }
  wire[at++] = record->net_change_fraction_indicator;

  return at;
}

/* Net Change Negative Whole Pair off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_net_change_negative_whole_pair(NetChangeNegativeWholePair *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { record->raw_net_change[i] = wire[at++]; }
  record->net_change_fraction_indicator = wire[at++];

  return at;
}

/* what was read of Net Change Negative Whole Pair is what was written, byte for byte */
static void equal_net_change_negative_whole_pair(const NetChangeNegativeWholePair *read, const NetChangeNegativeWholePair *written) {
  for (size_t i = 0; i < 7; i++) { assert(read->raw_net_change[i] == written->raw_net_change[i]); }
  assert(read->net_change_fraction_indicator == written->net_change_fraction_indicator);
}

/* Net Change Negative Whole Pair: written and read back, then read and written back */
static void check_net_change_negative_whole_pair(void) {
  NetChangeNegativeWholePair sent;
  NetChangeNegativeWholePair got;
  uint8_t wire[8];
  uint8_t again[8];

  any_net_change_negative_whole_pair(&sent);
  assert(encode_net_change_negative_whole_pair(&sent, wire, 0) == 8);
  assert(decode_net_change_negative_whole_pair(&got, wire, 0) == 8);
  equal_net_change_negative_whole_pair(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_net_change_negative_whole_pair(&got, wire, 0) == 8);
  assert(encode_net_change_negative_whole_pair(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Net Change Negative Ten Pair: 8 bytes ----------------------------------- */

typedef struct {
  uint8_t raw_net_change[7];              /* bytes 0 to 6 */
  uint8_t net_change_fraction_indicator;  /* byte 7 */
} NetChangeNegativeTenPair;

/* any Net Change Negative Ten Pair at all: every byte one the checker chooses */
static void any_net_change_negative_ten_pair(NetChangeNegativeTenPair *record) {
  for (size_t i = 0; i < 7; i++) { record->raw_net_change[i] = arbitrary(); }
  record->net_change_fraction_indicator = arbitrary();
}

/* Net Change Negative Ten Pair to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_net_change_negative_ten_pair(const NetChangeNegativeTenPair *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->raw_net_change[i]; }
  wire[at++] = record->net_change_fraction_indicator;

  return at;
}

/* Net Change Negative Ten Pair off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_net_change_negative_ten_pair(NetChangeNegativeTenPair *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { record->raw_net_change[i] = wire[at++]; }
  record->net_change_fraction_indicator = wire[at++];

  return at;
}

/* what was read of Net Change Negative Ten Pair is what was written, byte for byte */
static void equal_net_change_negative_ten_pair(const NetChangeNegativeTenPair *read, const NetChangeNegativeTenPair *written) {
  for (size_t i = 0; i < 7; i++) { assert(read->raw_net_change[i] == written->raw_net_change[i]); }
  assert(read->net_change_fraction_indicator == written->net_change_fraction_indicator);
}

/* Net Change Negative Ten Pair: written and read back, then read and written back */
static void check_net_change_negative_ten_pair(void) {
  NetChangeNegativeTenPair sent;
  NetChangeNegativeTenPair got;
  uint8_t wire[8];
  uint8_t again[8];

  any_net_change_negative_ten_pair(&sent);
  assert(encode_net_change_negative_ten_pair(&sent, wire, 0) == 8);
  assert(decode_net_change_negative_ten_pair(&got, wire, 0) == 8);
  equal_net_change_negative_ten_pair(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_net_change_negative_ten_pair(&got, wire, 0) == 8);
  assert(encode_net_change_negative_ten_pair(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Net Change Negative Hundred Pair: 8 bytes ------------------------------- */

typedef struct {
  uint8_t raw_net_change[7];              /* bytes 0 to 6 */
  uint8_t net_change_fraction_indicator;  /* byte 7 */
} NetChangeNegativeHundredPair;

/* any Net Change Negative Hundred Pair at all: every byte one the checker chooses */
static void any_net_change_negative_hundred_pair(NetChangeNegativeHundredPair *record) {
  for (size_t i = 0; i < 7; i++) { record->raw_net_change[i] = arbitrary(); }
  record->net_change_fraction_indicator = arbitrary();
}

/* Net Change Negative Hundred Pair to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_net_change_negative_hundred_pair(const NetChangeNegativeHundredPair *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->raw_net_change[i]; }
  wire[at++] = record->net_change_fraction_indicator;

  return at;
}

/* Net Change Negative Hundred Pair off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_net_change_negative_hundred_pair(NetChangeNegativeHundredPair *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { record->raw_net_change[i] = wire[at++]; }
  record->net_change_fraction_indicator = wire[at++];

  return at;
}

/* what was read of Net Change Negative Hundred Pair is what was written, byte for byte */
static void equal_net_change_negative_hundred_pair(const NetChangeNegativeHundredPair *read, const NetChangeNegativeHundredPair *written) {
  for (size_t i = 0; i < 7; i++) { assert(read->raw_net_change[i] == written->raw_net_change[i]); }
  assert(read->net_change_fraction_indicator == written->net_change_fraction_indicator);
}

/* Net Change Negative Hundred Pair: written and read back, then read and written back */
static void check_net_change_negative_hundred_pair(void) {
  NetChangeNegativeHundredPair sent;
  NetChangeNegativeHundredPair got;
  uint8_t wire[8];
  uint8_t again[8];

  any_net_change_negative_hundred_pair(&sent);
  assert(encode_net_change_negative_hundred_pair(&sent, wire, 0) == 8);
  assert(decode_net_change_negative_hundred_pair(&got, wire, 0) == 8);
  equal_net_change_negative_hundred_pair(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_net_change_negative_hundred_pair(&got, wire, 0) == 8);
  assert(encode_net_change_negative_hundred_pair(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Net Change Negative Thousand Pair: 8 bytes ------------------------------ */

typedef struct {
  uint8_t raw_net_change[7];              /* bytes 0 to 6 */
  uint8_t net_change_fraction_indicator;  /* byte 7 */
} NetChangeNegativeThousandPair;

/* any Net Change Negative Thousand Pair at all: every byte one the checker chooses */
static void any_net_change_negative_thousand_pair(NetChangeNegativeThousandPair *record) {
  for (size_t i = 0; i < 7; i++) { record->raw_net_change[i] = arbitrary(); }
  record->net_change_fraction_indicator = arbitrary();
}

/* Net Change Negative Thousand Pair to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_net_change_negative_thousand_pair(const NetChangeNegativeThousandPair *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->raw_net_change[i]; }
  wire[at++] = record->net_change_fraction_indicator;

  return at;
}

/* Net Change Negative Thousand Pair off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_net_change_negative_thousand_pair(NetChangeNegativeThousandPair *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { record->raw_net_change[i] = wire[at++]; }
  record->net_change_fraction_indicator = wire[at++];

  return at;
}

/* what was read of Net Change Negative Thousand Pair is what was written, byte for byte */
static void equal_net_change_negative_thousand_pair(const NetChangeNegativeThousandPair *read, const NetChangeNegativeThousandPair *written) {
  for (size_t i = 0; i < 7; i++) { assert(read->raw_net_change[i] == written->raw_net_change[i]); }
  assert(read->net_change_fraction_indicator == written->net_change_fraction_indicator);
}

/* Net Change Negative Thousand Pair: written and read back, then read and written back */
static void check_net_change_negative_thousand_pair(void) {
  NetChangeNegativeThousandPair sent;
  NetChangeNegativeThousandPair got;
  uint8_t wire[8];
  uint8_t again[8];

  any_net_change_negative_thousand_pair(&sent);
  assert(encode_net_change_negative_thousand_pair(&sent, wire, 0) == 8);
  assert(decode_net_change_negative_thousand_pair(&got, wire, 0) == 8);
  equal_net_change_negative_thousand_pair(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_net_change_negative_thousand_pair(&got, wire, 0) == 8);
  assert(encode_net_change_negative_thousand_pair(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Net Change Negative Ten Thousand Pair: 8 bytes -------------------------- */

typedef struct {
  uint8_t raw_net_change[7];              /* bytes 0 to 6 */
  uint8_t net_change_fraction_indicator;  /* byte 7 */
} NetChangeNegativeTenThousandPair;

/* any Net Change Negative Ten Thousand Pair at all: every byte one the checker chooses */
static void any_net_change_negative_ten_thousand_pair(NetChangeNegativeTenThousandPair *record) {
  for (size_t i = 0; i < 7; i++) { record->raw_net_change[i] = arbitrary(); }
  record->net_change_fraction_indicator = arbitrary();
}

/* Net Change Negative Ten Thousand Pair to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_net_change_negative_ten_thousand_pair(const NetChangeNegativeTenThousandPair *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->raw_net_change[i]; }
  wire[at++] = record->net_change_fraction_indicator;

  return at;
}

/* Net Change Negative Ten Thousand Pair off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_net_change_negative_ten_thousand_pair(NetChangeNegativeTenThousandPair *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { record->raw_net_change[i] = wire[at++]; }
  record->net_change_fraction_indicator = wire[at++];

  return at;
}

/* what was read of Net Change Negative Ten Thousand Pair is what was written, byte for byte */
static void equal_net_change_negative_ten_thousand_pair(const NetChangeNegativeTenThousandPair *read, const NetChangeNegativeTenThousandPair *written) {
  for (size_t i = 0; i < 7; i++) { assert(read->raw_net_change[i] == written->raw_net_change[i]); }
  assert(read->net_change_fraction_indicator == written->net_change_fraction_indicator);
}

/* Net Change Negative Ten Thousand Pair: written and read back, then read and written back */
static void check_net_change_negative_ten_thousand_pair(void) {
  NetChangeNegativeTenThousandPair sent;
  NetChangeNegativeTenThousandPair got;
  uint8_t wire[8];
  uint8_t again[8];

  any_net_change_negative_ten_thousand_pair(&sent);
  assert(encode_net_change_negative_ten_thousand_pair(&sent, wire, 0) == 8);
  assert(decode_net_change_negative_ten_thousand_pair(&got, wire, 0) == 8);
  equal_net_change_negative_ten_thousand_pair(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_net_change_negative_ten_thousand_pair(&got, wire, 0) == 8);
  assert(encode_net_change_negative_ten_thousand_pair(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Net Change Negative Hundred Thousand Pair: 8 bytes ---------------------- */

typedef struct {
  uint8_t raw_net_change[7];              /* bytes 0 to 6 */
  uint8_t net_change_fraction_indicator;  /* byte 7 */
} NetChangeNegativeHundredThousandPair;

/* any Net Change Negative Hundred Thousand Pair at all: every byte one the checker chooses */
static void any_net_change_negative_hundred_thousand_pair(NetChangeNegativeHundredThousandPair *record) {
  for (size_t i = 0; i < 7; i++) { record->raw_net_change[i] = arbitrary(); }
  record->net_change_fraction_indicator = arbitrary();
}

/* Net Change Negative Hundred Thousand Pair to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_net_change_negative_hundred_thousand_pair(const NetChangeNegativeHundredThousandPair *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->raw_net_change[i]; }
  wire[at++] = record->net_change_fraction_indicator;

  return at;
}

/* Net Change Negative Hundred Thousand Pair off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_net_change_negative_hundred_thousand_pair(NetChangeNegativeHundredThousandPair *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { record->raw_net_change[i] = wire[at++]; }
  record->net_change_fraction_indicator = wire[at++];

  return at;
}

/* what was read of Net Change Negative Hundred Thousand Pair is what was written, byte for byte */
static void equal_net_change_negative_hundred_thousand_pair(const NetChangeNegativeHundredThousandPair *read, const NetChangeNegativeHundredThousandPair *written) {
  for (size_t i = 0; i < 7; i++) { assert(read->raw_net_change[i] == written->raw_net_change[i]); }
  assert(read->net_change_fraction_indicator == written->net_change_fraction_indicator);
}

/* Net Change Negative Hundred Thousand Pair: written and read back, then read and written back */
static void check_net_change_negative_hundred_thousand_pair(void) {
  NetChangeNegativeHundredThousandPair sent;
  NetChangeNegativeHundredThousandPair got;
  uint8_t wire[8];
  uint8_t again[8];

  any_net_change_negative_hundred_thousand_pair(&sent);
  assert(encode_net_change_negative_hundred_thousand_pair(&sent, wire, 0) == 8);
  assert(decode_net_change_negative_hundred_thousand_pair(&got, wire, 0) == 8);
  equal_net_change_negative_hundred_thousand_pair(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_net_change_negative_hundred_thousand_pair(&got, wire, 0) == 8);
  assert(encode_net_change_negative_hundred_thousand_pair(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Net Change Negative Million Pair: 8 bytes ------------------------------- */

typedef struct {
  uint8_t raw_net_change[7];              /* bytes 0 to 6 */
  uint8_t net_change_fraction_indicator;  /* byte 7 */
} NetChangeNegativeMillionPair;

/* any Net Change Negative Million Pair at all: every byte one the checker chooses */
static void any_net_change_negative_million_pair(NetChangeNegativeMillionPair *record) {
  for (size_t i = 0; i < 7; i++) { record->raw_net_change[i] = arbitrary(); }
  record->net_change_fraction_indicator = arbitrary();
}

/* Net Change Negative Million Pair to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_net_change_negative_million_pair(const NetChangeNegativeMillionPair *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->raw_net_change[i]; }
  wire[at++] = record->net_change_fraction_indicator;

  return at;
}

/* Net Change Negative Million Pair off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_net_change_negative_million_pair(NetChangeNegativeMillionPair *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { record->raw_net_change[i] = wire[at++]; }
  record->net_change_fraction_indicator = wire[at++];

  return at;
}

/* what was read of Net Change Negative Million Pair is what was written, byte for byte */
static void equal_net_change_negative_million_pair(const NetChangeNegativeMillionPair *read, const NetChangeNegativeMillionPair *written) {
  for (size_t i = 0; i < 7; i++) { assert(read->raw_net_change[i] == written->raw_net_change[i]); }
  assert(read->net_change_fraction_indicator == written->net_change_fraction_indicator);
}

/* Net Change Negative Million Pair: written and read back, then read and written back */
static void check_net_change_negative_million_pair(void) {
  NetChangeNegativeMillionPair sent;
  NetChangeNegativeMillionPair got;
  uint8_t wire[8];
  uint8_t again[8];

  any_net_change_negative_million_pair(&sent);
  assert(encode_net_change_negative_million_pair(&sent, wire, 0) == 8);
  assert(decode_net_change_negative_million_pair(&got, wire, 0) == 8);
  equal_net_change_negative_million_pair(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_net_change_negative_million_pair(&got, wire, 0) == 8);
  assert(encode_net_change_negative_million_pair(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Net Change Numeric Pair: 8 bytes ---------------------------------------- */

typedef struct {
  uint8_t net_change[7];                  /* bytes 0 to 6 */
  uint8_t net_change_fraction_indicator;  /* byte 7 */
} NetChangeNumericPair;

/* any Net Change Numeric Pair at all: every byte one the checker chooses */
static void any_net_change_numeric_pair(NetChangeNumericPair *record) {
  for (size_t i = 0; i < 7; i++) { record->net_change[i] = arbitrary(); }
  record->net_change_fraction_indicator = arbitrary();
}

/* Net Change Numeric Pair to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_net_change_numeric_pair(const NetChangeNumericPair *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->net_change[i]; }
  wire[at++] = record->net_change_fraction_indicator;

  return at;
}

/* Net Change Numeric Pair off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_net_change_numeric_pair(NetChangeNumericPair *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { record->net_change[i] = wire[at++]; }
  record->net_change_fraction_indicator = wire[at++];

  return at;
}

/* what was read of Net Change Numeric Pair is what was written, byte for byte */
static void equal_net_change_numeric_pair(const NetChangeNumericPair *read, const NetChangeNumericPair *written) {
  for (size_t i = 0; i < 7; i++) { assert(read->net_change[i] == written->net_change[i]); }
  assert(read->net_change_fraction_indicator == written->net_change_fraction_indicator);
}

/* Net Change Numeric Pair: written and read back, then read and written back */
static void check_net_change_numeric_pair(void) {
  NetChangeNumericPair sent;
  NetChangeNumericPair got;
  uint8_t wire[8];
  uint8_t again[8];

  any_net_change_numeric_pair(&sent);
  assert(encode_net_change_numeric_pair(&sent, wire, 0) == 8);
  assert(decode_net_change_numeric_pair(&got, wire, 0) == 8);
  equal_net_change_numeric_pair(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_net_change_numeric_pair(&got, wire, 0) == 8);
  assert(encode_net_change_numeric_pair(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Net Change Future Options Trade Message Negative Whole Pair: 8 bytes ---- */

typedef struct {
  uint8_t raw_net_change_future_options_trade_message[7];  /* bytes 0 to 6 */
  uint8_t net_change_fraction_indicator;                   /* byte 7 */
} NetChangeFutureOptionsTradeMessageNegativeWholePair;

/* any Net Change Future Options Trade Message Negative Whole Pair at all: every byte one the checker chooses */
static void any_net_change_future_options_trade_message_negative_whole_pair(NetChangeFutureOptionsTradeMessageNegativeWholePair *record) {
  for (size_t i = 0; i < 7; i++) { record->raw_net_change_future_options_trade_message[i] = arbitrary(); }
  record->net_change_fraction_indicator = arbitrary();
}

/* Net Change Future Options Trade Message Negative Whole Pair to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_net_change_future_options_trade_message_negative_whole_pair(const NetChangeFutureOptionsTradeMessageNegativeWholePair *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->raw_net_change_future_options_trade_message[i]; }
  wire[at++] = record->net_change_fraction_indicator;

  return at;
}

/* Net Change Future Options Trade Message Negative Whole Pair off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_net_change_future_options_trade_message_negative_whole_pair(NetChangeFutureOptionsTradeMessageNegativeWholePair *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { record->raw_net_change_future_options_trade_message[i] = wire[at++]; }
  record->net_change_fraction_indicator = wire[at++];

  return at;
}

/* what was read of Net Change Future Options Trade Message Negative Whole Pair is what was written, byte for byte */
static void equal_net_change_future_options_trade_message_negative_whole_pair(const NetChangeFutureOptionsTradeMessageNegativeWholePair *read, const NetChangeFutureOptionsTradeMessageNegativeWholePair *written) {
  for (size_t i = 0; i < 7; i++) { assert(read->raw_net_change_future_options_trade_message[i] == written->raw_net_change_future_options_trade_message[i]); }
  assert(read->net_change_fraction_indicator == written->net_change_fraction_indicator);
}

/* Net Change Future Options Trade Message Negative Whole Pair: written and read back, then read and written back */
static void check_net_change_future_options_trade_message_negative_whole_pair(void) {
  NetChangeFutureOptionsTradeMessageNegativeWholePair sent;
  NetChangeFutureOptionsTradeMessageNegativeWholePair got;
  uint8_t wire[8];
  uint8_t again[8];

  any_net_change_future_options_trade_message_negative_whole_pair(&sent);
  assert(encode_net_change_future_options_trade_message_negative_whole_pair(&sent, wire, 0) == 8);
  assert(decode_net_change_future_options_trade_message_negative_whole_pair(&got, wire, 0) == 8);
  equal_net_change_future_options_trade_message_negative_whole_pair(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_net_change_future_options_trade_message_negative_whole_pair(&got, wire, 0) == 8);
  assert(encode_net_change_future_options_trade_message_negative_whole_pair(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Net Change Future Options Trade Message Negative Ten Pair: 8 bytes ------ */

typedef struct {
  uint8_t raw_net_change_future_options_trade_message[7];  /* bytes 0 to 6 */
  uint8_t net_change_fraction_indicator;                   /* byte 7 */
} NetChangeFutureOptionsTradeMessageNegativeTenPair;

/* any Net Change Future Options Trade Message Negative Ten Pair at all: every byte one the checker chooses */
static void any_net_change_future_options_trade_message_negative_ten_pair(NetChangeFutureOptionsTradeMessageNegativeTenPair *record) {
  for (size_t i = 0; i < 7; i++) { record->raw_net_change_future_options_trade_message[i] = arbitrary(); }
  record->net_change_fraction_indicator = arbitrary();
}

/* Net Change Future Options Trade Message Negative Ten Pair to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_net_change_future_options_trade_message_negative_ten_pair(const NetChangeFutureOptionsTradeMessageNegativeTenPair *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->raw_net_change_future_options_trade_message[i]; }
  wire[at++] = record->net_change_fraction_indicator;

  return at;
}

/* Net Change Future Options Trade Message Negative Ten Pair off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_net_change_future_options_trade_message_negative_ten_pair(NetChangeFutureOptionsTradeMessageNegativeTenPair *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { record->raw_net_change_future_options_trade_message[i] = wire[at++]; }
  record->net_change_fraction_indicator = wire[at++];

  return at;
}

/* what was read of Net Change Future Options Trade Message Negative Ten Pair is what was written, byte for byte */
static void equal_net_change_future_options_trade_message_negative_ten_pair(const NetChangeFutureOptionsTradeMessageNegativeTenPair *read, const NetChangeFutureOptionsTradeMessageNegativeTenPair *written) {
  for (size_t i = 0; i < 7; i++) { assert(read->raw_net_change_future_options_trade_message[i] == written->raw_net_change_future_options_trade_message[i]); }
  assert(read->net_change_fraction_indicator == written->net_change_fraction_indicator);
}

/* Net Change Future Options Trade Message Negative Ten Pair: written and read back, then read and written back */
static void check_net_change_future_options_trade_message_negative_ten_pair(void) {
  NetChangeFutureOptionsTradeMessageNegativeTenPair sent;
  NetChangeFutureOptionsTradeMessageNegativeTenPair got;
  uint8_t wire[8];
  uint8_t again[8];

  any_net_change_future_options_trade_message_negative_ten_pair(&sent);
  assert(encode_net_change_future_options_trade_message_negative_ten_pair(&sent, wire, 0) == 8);
  assert(decode_net_change_future_options_trade_message_negative_ten_pair(&got, wire, 0) == 8);
  equal_net_change_future_options_trade_message_negative_ten_pair(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_net_change_future_options_trade_message_negative_ten_pair(&got, wire, 0) == 8);
  assert(encode_net_change_future_options_trade_message_negative_ten_pair(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Net Change Future Options Trade Message Negative Hundred Pair: 8 bytes ---- */

typedef struct {
  uint8_t raw_net_change_future_options_trade_message[7];  /* bytes 0 to 6 */
  uint8_t net_change_fraction_indicator;                   /* byte 7 */
} NetChangeFutureOptionsTradeMessageNegativeHundredPair;

/* any Net Change Future Options Trade Message Negative Hundred Pair at all: every byte one the checker chooses */
static void any_net_change_future_options_trade_message_negative_hundred_pair(NetChangeFutureOptionsTradeMessageNegativeHundredPair *record) {
  for (size_t i = 0; i < 7; i++) { record->raw_net_change_future_options_trade_message[i] = arbitrary(); }
  record->net_change_fraction_indicator = arbitrary();
}

/* Net Change Future Options Trade Message Negative Hundred Pair to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_net_change_future_options_trade_message_negative_hundred_pair(const NetChangeFutureOptionsTradeMessageNegativeHundredPair *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->raw_net_change_future_options_trade_message[i]; }
  wire[at++] = record->net_change_fraction_indicator;

  return at;
}

/* Net Change Future Options Trade Message Negative Hundred Pair off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_net_change_future_options_trade_message_negative_hundred_pair(NetChangeFutureOptionsTradeMessageNegativeHundredPair *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { record->raw_net_change_future_options_trade_message[i] = wire[at++]; }
  record->net_change_fraction_indicator = wire[at++];

  return at;
}

/* what was read of Net Change Future Options Trade Message Negative Hundred Pair is what was written, byte for byte */
static void equal_net_change_future_options_trade_message_negative_hundred_pair(const NetChangeFutureOptionsTradeMessageNegativeHundredPair *read, const NetChangeFutureOptionsTradeMessageNegativeHundredPair *written) {
  for (size_t i = 0; i < 7; i++) { assert(read->raw_net_change_future_options_trade_message[i] == written->raw_net_change_future_options_trade_message[i]); }
  assert(read->net_change_fraction_indicator == written->net_change_fraction_indicator);
}

/* Net Change Future Options Trade Message Negative Hundred Pair: written and read back, then read and written back */
static void check_net_change_future_options_trade_message_negative_hundred_pair(void) {
  NetChangeFutureOptionsTradeMessageNegativeHundredPair sent;
  NetChangeFutureOptionsTradeMessageNegativeHundredPair got;
  uint8_t wire[8];
  uint8_t again[8];

  any_net_change_future_options_trade_message_negative_hundred_pair(&sent);
  assert(encode_net_change_future_options_trade_message_negative_hundred_pair(&sent, wire, 0) == 8);
  assert(decode_net_change_future_options_trade_message_negative_hundred_pair(&got, wire, 0) == 8);
  equal_net_change_future_options_trade_message_negative_hundred_pair(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_net_change_future_options_trade_message_negative_hundred_pair(&got, wire, 0) == 8);
  assert(encode_net_change_future_options_trade_message_negative_hundred_pair(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Net Change Future Options Trade Message Negative Thousand Pair: 8 bytes ---- */

typedef struct {
  uint8_t raw_net_change_future_options_trade_message[7];  /* bytes 0 to 6 */
  uint8_t net_change_fraction_indicator;                   /* byte 7 */
} NetChangeFutureOptionsTradeMessageNegativeThousandPair;

/* any Net Change Future Options Trade Message Negative Thousand Pair at all: every byte one the checker chooses */
static void any_net_change_future_options_trade_message_negative_thousand_pair(NetChangeFutureOptionsTradeMessageNegativeThousandPair *record) {
  for (size_t i = 0; i < 7; i++) { record->raw_net_change_future_options_trade_message[i] = arbitrary(); }
  record->net_change_fraction_indicator = arbitrary();
}

/* Net Change Future Options Trade Message Negative Thousand Pair to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_net_change_future_options_trade_message_negative_thousand_pair(const NetChangeFutureOptionsTradeMessageNegativeThousandPair *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->raw_net_change_future_options_trade_message[i]; }
  wire[at++] = record->net_change_fraction_indicator;

  return at;
}

/* Net Change Future Options Trade Message Negative Thousand Pair off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_net_change_future_options_trade_message_negative_thousand_pair(NetChangeFutureOptionsTradeMessageNegativeThousandPair *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { record->raw_net_change_future_options_trade_message[i] = wire[at++]; }
  record->net_change_fraction_indicator = wire[at++];

  return at;
}

/* what was read of Net Change Future Options Trade Message Negative Thousand Pair is what was written, byte for byte */
static void equal_net_change_future_options_trade_message_negative_thousand_pair(const NetChangeFutureOptionsTradeMessageNegativeThousandPair *read, const NetChangeFutureOptionsTradeMessageNegativeThousandPair *written) {
  for (size_t i = 0; i < 7; i++) { assert(read->raw_net_change_future_options_trade_message[i] == written->raw_net_change_future_options_trade_message[i]); }
  assert(read->net_change_fraction_indicator == written->net_change_fraction_indicator);
}

/* Net Change Future Options Trade Message Negative Thousand Pair: written and read back, then read and written back */
static void check_net_change_future_options_trade_message_negative_thousand_pair(void) {
  NetChangeFutureOptionsTradeMessageNegativeThousandPair sent;
  NetChangeFutureOptionsTradeMessageNegativeThousandPair got;
  uint8_t wire[8];
  uint8_t again[8];

  any_net_change_future_options_trade_message_negative_thousand_pair(&sent);
  assert(encode_net_change_future_options_trade_message_negative_thousand_pair(&sent, wire, 0) == 8);
  assert(decode_net_change_future_options_trade_message_negative_thousand_pair(&got, wire, 0) == 8);
  equal_net_change_future_options_trade_message_negative_thousand_pair(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_net_change_future_options_trade_message_negative_thousand_pair(&got, wire, 0) == 8);
  assert(encode_net_change_future_options_trade_message_negative_thousand_pair(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Net Change Future Options Trade Message Negative Ten Thousand Pair: 8 bytes ---- */

typedef struct {
  uint8_t raw_net_change_future_options_trade_message[7];  /* bytes 0 to 6 */
  uint8_t net_change_fraction_indicator;                   /* byte 7 */
} NetChangeFutureOptionsTradeMessageNegativeTenThousandPair;

/* any Net Change Future Options Trade Message Negative Ten Thousand Pair at all: every byte one the checker chooses */
static void any_net_change_future_options_trade_message_negative_ten_thousand_pair(NetChangeFutureOptionsTradeMessageNegativeTenThousandPair *record) {
  for (size_t i = 0; i < 7; i++) { record->raw_net_change_future_options_trade_message[i] = arbitrary(); }
  record->net_change_fraction_indicator = arbitrary();
}

/* Net Change Future Options Trade Message Negative Ten Thousand Pair to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_net_change_future_options_trade_message_negative_ten_thousand_pair(const NetChangeFutureOptionsTradeMessageNegativeTenThousandPair *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->raw_net_change_future_options_trade_message[i]; }
  wire[at++] = record->net_change_fraction_indicator;

  return at;
}

/* Net Change Future Options Trade Message Negative Ten Thousand Pair off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_net_change_future_options_trade_message_negative_ten_thousand_pair(NetChangeFutureOptionsTradeMessageNegativeTenThousandPair *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { record->raw_net_change_future_options_trade_message[i] = wire[at++]; }
  record->net_change_fraction_indicator = wire[at++];

  return at;
}

/* what was read of Net Change Future Options Trade Message Negative Ten Thousand Pair is what was written, byte for byte */
static void equal_net_change_future_options_trade_message_negative_ten_thousand_pair(const NetChangeFutureOptionsTradeMessageNegativeTenThousandPair *read, const NetChangeFutureOptionsTradeMessageNegativeTenThousandPair *written) {
  for (size_t i = 0; i < 7; i++) { assert(read->raw_net_change_future_options_trade_message[i] == written->raw_net_change_future_options_trade_message[i]); }
  assert(read->net_change_fraction_indicator == written->net_change_fraction_indicator);
}

/* Net Change Future Options Trade Message Negative Ten Thousand Pair: written and read back, then read and written back */
static void check_net_change_future_options_trade_message_negative_ten_thousand_pair(void) {
  NetChangeFutureOptionsTradeMessageNegativeTenThousandPair sent;
  NetChangeFutureOptionsTradeMessageNegativeTenThousandPair got;
  uint8_t wire[8];
  uint8_t again[8];

  any_net_change_future_options_trade_message_negative_ten_thousand_pair(&sent);
  assert(encode_net_change_future_options_trade_message_negative_ten_thousand_pair(&sent, wire, 0) == 8);
  assert(decode_net_change_future_options_trade_message_negative_ten_thousand_pair(&got, wire, 0) == 8);
  equal_net_change_future_options_trade_message_negative_ten_thousand_pair(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_net_change_future_options_trade_message_negative_ten_thousand_pair(&got, wire, 0) == 8);
  assert(encode_net_change_future_options_trade_message_negative_ten_thousand_pair(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Net Change Future Options Trade Message Negative Hundred Thousand Pair: 8 bytes ---- */

typedef struct {
  uint8_t raw_net_change_future_options_trade_message[7];  /* bytes 0 to 6 */
  uint8_t net_change_fraction_indicator;                   /* byte 7 */
} NetChangeFutureOptionsTradeMessageNegativeHundredThousandPair;

/* any Net Change Future Options Trade Message Negative Hundred Thousand Pair at all: every byte one the checker chooses */
static void any_net_change_future_options_trade_message_negative_hundred_thousand_pair(NetChangeFutureOptionsTradeMessageNegativeHundredThousandPair *record) {
  for (size_t i = 0; i < 7; i++) { record->raw_net_change_future_options_trade_message[i] = arbitrary(); }
  record->net_change_fraction_indicator = arbitrary();
}

/* Net Change Future Options Trade Message Negative Hundred Thousand Pair to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_net_change_future_options_trade_message_negative_hundred_thousand_pair(const NetChangeFutureOptionsTradeMessageNegativeHundredThousandPair *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->raw_net_change_future_options_trade_message[i]; }
  wire[at++] = record->net_change_fraction_indicator;

  return at;
}

/* Net Change Future Options Trade Message Negative Hundred Thousand Pair off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_net_change_future_options_trade_message_negative_hundred_thousand_pair(NetChangeFutureOptionsTradeMessageNegativeHundredThousandPair *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { record->raw_net_change_future_options_trade_message[i] = wire[at++]; }
  record->net_change_fraction_indicator = wire[at++];

  return at;
}

/* what was read of Net Change Future Options Trade Message Negative Hundred Thousand Pair is what was written, byte for byte */
static void equal_net_change_future_options_trade_message_negative_hundred_thousand_pair(const NetChangeFutureOptionsTradeMessageNegativeHundredThousandPair *read, const NetChangeFutureOptionsTradeMessageNegativeHundredThousandPair *written) {
  for (size_t i = 0; i < 7; i++) { assert(read->raw_net_change_future_options_trade_message[i] == written->raw_net_change_future_options_trade_message[i]); }
  assert(read->net_change_fraction_indicator == written->net_change_fraction_indicator);
}

/* Net Change Future Options Trade Message Negative Hundred Thousand Pair: written and read back, then read and written back */
static void check_net_change_future_options_trade_message_negative_hundred_thousand_pair(void) {
  NetChangeFutureOptionsTradeMessageNegativeHundredThousandPair sent;
  NetChangeFutureOptionsTradeMessageNegativeHundredThousandPair got;
  uint8_t wire[8];
  uint8_t again[8];

  any_net_change_future_options_trade_message_negative_hundred_thousand_pair(&sent);
  assert(encode_net_change_future_options_trade_message_negative_hundred_thousand_pair(&sent, wire, 0) == 8);
  assert(decode_net_change_future_options_trade_message_negative_hundred_thousand_pair(&got, wire, 0) == 8);
  equal_net_change_future_options_trade_message_negative_hundred_thousand_pair(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_net_change_future_options_trade_message_negative_hundred_thousand_pair(&got, wire, 0) == 8);
  assert(encode_net_change_future_options_trade_message_negative_hundred_thousand_pair(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Net Change Future Options Trade Message Negative Million Pair: 8 bytes ---- */

typedef struct {
  uint8_t raw_net_change_future_options_trade_message[7];  /* bytes 0 to 6 */
  uint8_t net_change_fraction_indicator;                   /* byte 7 */
} NetChangeFutureOptionsTradeMessageNegativeMillionPair;

/* any Net Change Future Options Trade Message Negative Million Pair at all: every byte one the checker chooses */
static void any_net_change_future_options_trade_message_negative_million_pair(NetChangeFutureOptionsTradeMessageNegativeMillionPair *record) {
  for (size_t i = 0; i < 7; i++) { record->raw_net_change_future_options_trade_message[i] = arbitrary(); }
  record->net_change_fraction_indicator = arbitrary();
}

/* Net Change Future Options Trade Message Negative Million Pair to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_net_change_future_options_trade_message_negative_million_pair(const NetChangeFutureOptionsTradeMessageNegativeMillionPair *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->raw_net_change_future_options_trade_message[i]; }
  wire[at++] = record->net_change_fraction_indicator;

  return at;
}

/* Net Change Future Options Trade Message Negative Million Pair off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_net_change_future_options_trade_message_negative_million_pair(NetChangeFutureOptionsTradeMessageNegativeMillionPair *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { record->raw_net_change_future_options_trade_message[i] = wire[at++]; }
  record->net_change_fraction_indicator = wire[at++];

  return at;
}

/* what was read of Net Change Future Options Trade Message Negative Million Pair is what was written, byte for byte */
static void equal_net_change_future_options_trade_message_negative_million_pair(const NetChangeFutureOptionsTradeMessageNegativeMillionPair *read, const NetChangeFutureOptionsTradeMessageNegativeMillionPair *written) {
  for (size_t i = 0; i < 7; i++) { assert(read->raw_net_change_future_options_trade_message[i] == written->raw_net_change_future_options_trade_message[i]); }
  assert(read->net_change_fraction_indicator == written->net_change_fraction_indicator);
}

/* Net Change Future Options Trade Message Negative Million Pair: written and read back, then read and written back */
static void check_net_change_future_options_trade_message_negative_million_pair(void) {
  NetChangeFutureOptionsTradeMessageNegativeMillionPair sent;
  NetChangeFutureOptionsTradeMessageNegativeMillionPair got;
  uint8_t wire[8];
  uint8_t again[8];

  any_net_change_future_options_trade_message_negative_million_pair(&sent);
  assert(encode_net_change_future_options_trade_message_negative_million_pair(&sent, wire, 0) == 8);
  assert(decode_net_change_future_options_trade_message_negative_million_pair(&got, wire, 0) == 8);
  equal_net_change_future_options_trade_message_negative_million_pair(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_net_change_future_options_trade_message_negative_million_pair(&got, wire, 0) == 8);
  assert(encode_net_change_future_options_trade_message_negative_million_pair(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Net Change Future Options Trade Message Numeric Pair: 8 bytes ----------- */

typedef struct {
  uint8_t net_change[7];                  /* bytes 0 to 6 */
  uint8_t net_change_fraction_indicator;  /* byte 7 */
} NetChangeFutureOptionsTradeMessageNumericPair;

/* any Net Change Future Options Trade Message Numeric Pair at all: every byte one the checker chooses */
static void any_net_change_future_options_trade_message_numeric_pair(NetChangeFutureOptionsTradeMessageNumericPair *record) {
  for (size_t i = 0; i < 7; i++) { record->net_change[i] = arbitrary(); }
  record->net_change_fraction_indicator = arbitrary();
}

/* Net Change Future Options Trade Message Numeric Pair to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_net_change_future_options_trade_message_numeric_pair(const NetChangeFutureOptionsTradeMessageNumericPair *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->net_change[i]; }
  wire[at++] = record->net_change_fraction_indicator;

  return at;
}

/* Net Change Future Options Trade Message Numeric Pair off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_net_change_future_options_trade_message_numeric_pair(NetChangeFutureOptionsTradeMessageNumericPair *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { record->net_change[i] = wire[at++]; }
  record->net_change_fraction_indicator = wire[at++];

  return at;
}

/* what was read of Net Change Future Options Trade Message Numeric Pair is what was written, byte for byte */
static void equal_net_change_future_options_trade_message_numeric_pair(const NetChangeFutureOptionsTradeMessageNumericPair *read, const NetChangeFutureOptionsTradeMessageNumericPair *written) {
  for (size_t i = 0; i < 7; i++) { assert(read->net_change[i] == written->net_change[i]); }
  assert(read->net_change_fraction_indicator == written->net_change_fraction_indicator);
}

/* Net Change Future Options Trade Message Numeric Pair: written and read back, then read and written back */
static void check_net_change_future_options_trade_message_numeric_pair(void) {
  NetChangeFutureOptionsTradeMessageNumericPair sent;
  NetChangeFutureOptionsTradeMessageNumericPair got;
  uint8_t wire[8];
  uint8_t again[8];

  any_net_change_future_options_trade_message_numeric_pair(&sent);
  assert(encode_net_change_future_options_trade_message_numeric_pair(&sent, wire, 0) == 8);
  assert(decode_net_change_future_options_trade_message_numeric_pair(&got, wire, 0) == 8);
  equal_net_change_future_options_trade_message_numeric_pair(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_net_change_future_options_trade_message_numeric_pair(&got, wire, 0) == 8);
  assert(encode_net_change_future_options_trade_message_numeric_pair(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Future Product: 11 bytes ------------------------------------------------ */

/* The guide states the future product once and every futures message carries it. */
typedef struct {
  uint8_t root_symbol[6];  /* bytes 0 to 5 */
  uint8_t symbol_month;    /* byte 6 */
  uint8_t symbol_year[2];  /* bytes 7 to 8 */
  uint8_t expiry_day[2];   /* bytes 9 to 10 */
} FutureProduct;

/* any Future Product at all: every byte one the checker chooses */
static void any_future_product(FutureProduct *record) {
  for (size_t i = 0; i < 6; i++) { record->root_symbol[i] = arbitrary(); }
  record->symbol_month = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->symbol_year[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->expiry_day[i] = arbitrary(); }
}

/* Future Product to the wire: 11 bytes from at, returning where the next byte goes */
static size_t encode_future_product(const FutureProduct *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->root_symbol[i]; }
  wire[at++] = record->symbol_month;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->symbol_year[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->expiry_day[i]; }

  return at;
}

/* Future Product off the wire: 11 bytes from at, returning where the next byte lies */
static size_t decode_future_product(FutureProduct *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 6; i++) { record->root_symbol[i] = wire[at++]; }
  record->symbol_month = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->symbol_year[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->expiry_day[i] = wire[at++]; }

  return at;
}

/* what was read of Future Product is what was written, byte for byte */
static void equal_future_product(const FutureProduct *read, const FutureProduct *written) {
  for (size_t i = 0; i < 6; i++) { assert(read->root_symbol[i] == written->root_symbol[i]); }
  assert(read->symbol_month == written->symbol_month);
  for (size_t i = 0; i < 2; i++) { assert(read->symbol_year[i] == written->symbol_year[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->expiry_day[i] == written->expiry_day[i]); }
}

/* Future Product: written and read back, then read and written back */
static void check_future_product(void) {
  FutureProduct sent;
  FutureProduct got;
  uint8_t wire[11];
  uint8_t again[11];

  any_future_product(&sent);
  assert(encode_future_product(&sent, wire, 0) == 11);
  assert(decode_future_product(&got, wire, 0) == 11);
  equal_future_product(&got, &sent);

  for (size_t i = 0; i < 11; i++) { wire[i] = arbitrary(); }
  assert(decode_future_product(&got, wire, 0) == 11);
  assert(encode_future_product(&got, again, 0) == 11);
  for (size_t i = 0; i < 11; i++) { assert(again[i] == wire[i]); }
}

/* ---- Futures Request For Quote Rfq Message: 33 bytes ------------------------- */

/* Futures Request for Quote (RFQ) message */
typedef struct {
  LongMessageHeader long_message_header;  /* bytes 0 to 11 */
  uint8_t exchange_id;                    /* byte 12 */
  FutureProduct future_product;           /* bytes 13 to 23 */
  uint8_t requested_size[8];              /* bytes 24 to 31 */
  uint8_t requested_market_side;          /* byte 32 */
} FuturesRequestForQuoteRfqMessage;

/* any Futures Request For Quote Rfq Message at all: every byte one the checker chooses */
static void any_futures_request_for_quote_rfq_message(FuturesRequestForQuoteRfqMessage *record) {
  any_long_message_header(&record->long_message_header);
  record->exchange_id = arbitrary();
  any_future_product(&record->future_product);
  for (size_t i = 0; i < 8; i++) { record->requested_size[i] = arbitrary(); }
  record->requested_market_side = arbitrary();
}

/* Futures Request For Quote Rfq Message to the wire: 33 bytes from at, returning where the next byte goes */
static size_t encode_futures_request_for_quote_rfq_message(const FuturesRequestForQuoteRfqMessage *record, uint8_t *wire, size_t at) {
  at = encode_long_message_header(&record->long_message_header, wire, at);
  wire[at++] = record->exchange_id;
  at = encode_future_product(&record->future_product, wire, at);
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->requested_size[i]; }
  wire[at++] = record->requested_market_side;

  return at;
}

/* Futures Request For Quote Rfq Message off the wire: 33 bytes from at, returning where the next byte lies */
static size_t decode_futures_request_for_quote_rfq_message(FuturesRequestForQuoteRfqMessage *record, const uint8_t *wire, size_t at) {
  at = decode_long_message_header(&record->long_message_header, wire, at);
  record->exchange_id = wire[at++];
  at = decode_future_product(&record->future_product, wire, at);
  for (size_t i = 0; i < 8; i++) { record->requested_size[i] = wire[at++]; }
  record->requested_market_side = wire[at++];

  return at;
}

/* what was read of Futures Request For Quote Rfq Message is what was written, byte for byte */
static void equal_futures_request_for_quote_rfq_message(const FuturesRequestForQuoteRfqMessage *read, const FuturesRequestForQuoteRfqMessage *written) {
  equal_long_message_header(&read->long_message_header, &written->long_message_header);
  assert(read->exchange_id == written->exchange_id);
  equal_future_product(&read->future_product, &written->future_product);
  for (size_t i = 0; i < 8; i++) { assert(read->requested_size[i] == written->requested_size[i]); }
  assert(read->requested_market_side == written->requested_market_side);
}

/* Futures Request For Quote Rfq Message: written and read back, then read and written back */
static void check_futures_request_for_quote_rfq_message(void) {
  FuturesRequestForQuoteRfqMessage sent;
  FuturesRequestForQuoteRfqMessage got;
  uint8_t wire[33];
  uint8_t again[33];

  any_futures_request_for_quote_rfq_message(&sent);
  assert(encode_futures_request_for_quote_rfq_message(&sent, wire, 0) == 33);
  assert(decode_futures_request_for_quote_rfq_message(&got, wire, 0) == 33);
  equal_futures_request_for_quote_rfq_message(&got, &sent);

  for (size_t i = 0; i < 33; i++) { wire[i] = arbitrary(); }
  assert(decode_futures_request_for_quote_rfq_message(&got, wire, 0) == 33);
  assert(encode_futures_request_for_quote_rfq_message(&got, again, 0) == 33);
  for (size_t i = 0; i < 33; i++) { assert(again[i] == wire[i]); }
}

/* ---- Strategy Request For Quote Rfq Message: 52 bytes ------------------------ */

/* Strategy Request for Quote (RFQ) message */
typedef struct {
  LongMessageHeader long_message_header;  /* bytes 0 to 11 */
  uint8_t exchange_id;                    /* byte 12 */
  uint8_t symbol[30];                     /* bytes 13 to 42 */
  uint8_t requested_size[8];              /* bytes 43 to 50 */
  uint8_t requested_market_side;          /* byte 51 */
} StrategyRequestForQuoteRfqMessage;

/* any Strategy Request For Quote Rfq Message at all: every byte one the checker chooses */
static void any_strategy_request_for_quote_rfq_message(StrategyRequestForQuoteRfqMessage *record) {
  any_long_message_header(&record->long_message_header);
  record->exchange_id = arbitrary();
  for (size_t i = 0; i < 30; i++) { record->symbol[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->requested_size[i] = arbitrary(); }
  record->requested_market_side = arbitrary();
}

/* Strategy Request For Quote Rfq Message to the wire: 52 bytes from at, returning where the next byte goes */
static size_t encode_strategy_request_for_quote_rfq_message(const StrategyRequestForQuoteRfqMessage *record, uint8_t *wire, size_t at) {
  at = encode_long_message_header(&record->long_message_header, wire, at);
  wire[at++] = record->exchange_id;
  for (size_t i = 0; i < 30; i++) { wire[at++] = record->symbol[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->requested_size[i]; }
  wire[at++] = record->requested_market_side;

  return at;
}

/* Strategy Request For Quote Rfq Message off the wire: 52 bytes from at, returning where the next byte lies */
static size_t decode_strategy_request_for_quote_rfq_message(StrategyRequestForQuoteRfqMessage *record, const uint8_t *wire, size_t at) {
  at = decode_long_message_header(&record->long_message_header, wire, at);
  record->exchange_id = wire[at++];
  for (size_t i = 0; i < 30; i++) { record->symbol[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->requested_size[i] = wire[at++]; }
  record->requested_market_side = wire[at++];

  return at;
}

/* what was read of Strategy Request For Quote Rfq Message is what was written, byte for byte */
static void equal_strategy_request_for_quote_rfq_message(const StrategyRequestForQuoteRfqMessage *read, const StrategyRequestForQuoteRfqMessage *written) {
  equal_long_message_header(&read->long_message_header, &written->long_message_header);
  assert(read->exchange_id == written->exchange_id);
  for (size_t i = 0; i < 30; i++) { assert(read->symbol[i] == written->symbol[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->requested_size[i] == written->requested_size[i]); }
  assert(read->requested_market_side == written->requested_market_side);
}

/* Strategy Request For Quote Rfq Message: written and read back, then read and written back */
static void check_strategy_request_for_quote_rfq_message(void) {
  StrategyRequestForQuoteRfqMessage sent;
  StrategyRequestForQuoteRfqMessage got;
  uint8_t wire[52];
  uint8_t again[52];

  any_strategy_request_for_quote_rfq_message(&sent);
  assert(encode_strategy_request_for_quote_rfq_message(&sent, wire, 0) == 52);
  assert(decode_strategy_request_for_quote_rfq_message(&got, wire, 0) == 52);
  equal_strategy_request_for_quote_rfq_message(&got, &sent);

  for (size_t i = 0; i < 52; i++) { wire[i] = arbitrary(); }
  assert(decode_strategy_request_for_quote_rfq_message(&got, wire, 0) == 52);
  assert(encode_strategy_request_for_quote_rfq_message(&got, again, 0) == 52);
  for (size_t i = 0; i < 52; i++) { assert(again[i] == wire[i]); }
}

/* ---- Strike Price Schedule Notice Negative Whole Pair: 8 bytes --------------- */

typedef struct {
  uint8_t raw_strike_price_schedule_notice[7];  /* bytes 0 to 6 */
  uint8_t strike_price_fraction_indicator;      /* byte 7 */
} StrikePriceScheduleNoticeNegativeWholePair;

/* any Strike Price Schedule Notice Negative Whole Pair at all: every byte one the checker chooses */
static void any_strike_price_schedule_notice_negative_whole_pair(StrikePriceScheduleNoticeNegativeWholePair *record) {
  for (size_t i = 0; i < 7; i++) { record->raw_strike_price_schedule_notice[i] = arbitrary(); }
  record->strike_price_fraction_indicator = arbitrary();
}

/* Strike Price Schedule Notice Negative Whole Pair to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_strike_price_schedule_notice_negative_whole_pair(const StrikePriceScheduleNoticeNegativeWholePair *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->raw_strike_price_schedule_notice[i]; }
  wire[at++] = record->strike_price_fraction_indicator;

  return at;
}

/* Strike Price Schedule Notice Negative Whole Pair off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_strike_price_schedule_notice_negative_whole_pair(StrikePriceScheduleNoticeNegativeWholePair *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { record->raw_strike_price_schedule_notice[i] = wire[at++]; }
  record->strike_price_fraction_indicator = wire[at++];

  return at;
}

/* what was read of Strike Price Schedule Notice Negative Whole Pair is what was written, byte for byte */
static void equal_strike_price_schedule_notice_negative_whole_pair(const StrikePriceScheduleNoticeNegativeWholePair *read, const StrikePriceScheduleNoticeNegativeWholePair *written) {
  for (size_t i = 0; i < 7; i++) { assert(read->raw_strike_price_schedule_notice[i] == written->raw_strike_price_schedule_notice[i]); }
  assert(read->strike_price_fraction_indicator == written->strike_price_fraction_indicator);
}

/* Strike Price Schedule Notice Negative Whole Pair: written and read back, then read and written back */
static void check_strike_price_schedule_notice_negative_whole_pair(void) {
  StrikePriceScheduleNoticeNegativeWholePair sent;
  StrikePriceScheduleNoticeNegativeWholePair got;
  uint8_t wire[8];
  uint8_t again[8];

  any_strike_price_schedule_notice_negative_whole_pair(&sent);
  assert(encode_strike_price_schedule_notice_negative_whole_pair(&sent, wire, 0) == 8);
  assert(decode_strike_price_schedule_notice_negative_whole_pair(&got, wire, 0) == 8);
  equal_strike_price_schedule_notice_negative_whole_pair(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_strike_price_schedule_notice_negative_whole_pair(&got, wire, 0) == 8);
  assert(encode_strike_price_schedule_notice_negative_whole_pair(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Strike Price Schedule Notice Negative Ten Pair: 8 bytes ----------------- */

typedef struct {
  uint8_t raw_strike_price_schedule_notice[7];  /* bytes 0 to 6 */
  uint8_t strike_price_fraction_indicator;      /* byte 7 */
} StrikePriceScheduleNoticeNegativeTenPair;

/* any Strike Price Schedule Notice Negative Ten Pair at all: every byte one the checker chooses */
static void any_strike_price_schedule_notice_negative_ten_pair(StrikePriceScheduleNoticeNegativeTenPair *record) {
  for (size_t i = 0; i < 7; i++) { record->raw_strike_price_schedule_notice[i] = arbitrary(); }
  record->strike_price_fraction_indicator = arbitrary();
}

/* Strike Price Schedule Notice Negative Ten Pair to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_strike_price_schedule_notice_negative_ten_pair(const StrikePriceScheduleNoticeNegativeTenPair *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->raw_strike_price_schedule_notice[i]; }
  wire[at++] = record->strike_price_fraction_indicator;

  return at;
}

/* Strike Price Schedule Notice Negative Ten Pair off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_strike_price_schedule_notice_negative_ten_pair(StrikePriceScheduleNoticeNegativeTenPair *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { record->raw_strike_price_schedule_notice[i] = wire[at++]; }
  record->strike_price_fraction_indicator = wire[at++];

  return at;
}

/* what was read of Strike Price Schedule Notice Negative Ten Pair is what was written, byte for byte */
static void equal_strike_price_schedule_notice_negative_ten_pair(const StrikePriceScheduleNoticeNegativeTenPair *read, const StrikePriceScheduleNoticeNegativeTenPair *written) {
  for (size_t i = 0; i < 7; i++) { assert(read->raw_strike_price_schedule_notice[i] == written->raw_strike_price_schedule_notice[i]); }
  assert(read->strike_price_fraction_indicator == written->strike_price_fraction_indicator);
}

/* Strike Price Schedule Notice Negative Ten Pair: written and read back, then read and written back */
static void check_strike_price_schedule_notice_negative_ten_pair(void) {
  StrikePriceScheduleNoticeNegativeTenPair sent;
  StrikePriceScheduleNoticeNegativeTenPair got;
  uint8_t wire[8];
  uint8_t again[8];

  any_strike_price_schedule_notice_negative_ten_pair(&sent);
  assert(encode_strike_price_schedule_notice_negative_ten_pair(&sent, wire, 0) == 8);
  assert(decode_strike_price_schedule_notice_negative_ten_pair(&got, wire, 0) == 8);
  equal_strike_price_schedule_notice_negative_ten_pair(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_strike_price_schedule_notice_negative_ten_pair(&got, wire, 0) == 8);
  assert(encode_strike_price_schedule_notice_negative_ten_pair(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Strike Price Schedule Notice Negative Hundred Pair: 8 bytes ------------- */

typedef struct {
  uint8_t raw_strike_price_schedule_notice[7];  /* bytes 0 to 6 */
  uint8_t strike_price_fraction_indicator;      /* byte 7 */
} StrikePriceScheduleNoticeNegativeHundredPair;

/* any Strike Price Schedule Notice Negative Hundred Pair at all: every byte one the checker chooses */
static void any_strike_price_schedule_notice_negative_hundred_pair(StrikePriceScheduleNoticeNegativeHundredPair *record) {
  for (size_t i = 0; i < 7; i++) { record->raw_strike_price_schedule_notice[i] = arbitrary(); }
  record->strike_price_fraction_indicator = arbitrary();
}

/* Strike Price Schedule Notice Negative Hundred Pair to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_strike_price_schedule_notice_negative_hundred_pair(const StrikePriceScheduleNoticeNegativeHundredPair *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->raw_strike_price_schedule_notice[i]; }
  wire[at++] = record->strike_price_fraction_indicator;

  return at;
}

/* Strike Price Schedule Notice Negative Hundred Pair off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_strike_price_schedule_notice_negative_hundred_pair(StrikePriceScheduleNoticeNegativeHundredPair *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { record->raw_strike_price_schedule_notice[i] = wire[at++]; }
  record->strike_price_fraction_indicator = wire[at++];

  return at;
}

/* what was read of Strike Price Schedule Notice Negative Hundred Pair is what was written, byte for byte */
static void equal_strike_price_schedule_notice_negative_hundred_pair(const StrikePriceScheduleNoticeNegativeHundredPair *read, const StrikePriceScheduleNoticeNegativeHundredPair *written) {
  for (size_t i = 0; i < 7; i++) { assert(read->raw_strike_price_schedule_notice[i] == written->raw_strike_price_schedule_notice[i]); }
  assert(read->strike_price_fraction_indicator == written->strike_price_fraction_indicator);
}

/* Strike Price Schedule Notice Negative Hundred Pair: written and read back, then read and written back */
static void check_strike_price_schedule_notice_negative_hundred_pair(void) {
  StrikePriceScheduleNoticeNegativeHundredPair sent;
  StrikePriceScheduleNoticeNegativeHundredPair got;
  uint8_t wire[8];
  uint8_t again[8];

  any_strike_price_schedule_notice_negative_hundred_pair(&sent);
  assert(encode_strike_price_schedule_notice_negative_hundred_pair(&sent, wire, 0) == 8);
  assert(decode_strike_price_schedule_notice_negative_hundred_pair(&got, wire, 0) == 8);
  equal_strike_price_schedule_notice_negative_hundred_pair(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_strike_price_schedule_notice_negative_hundred_pair(&got, wire, 0) == 8);
  assert(encode_strike_price_schedule_notice_negative_hundred_pair(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Strike Price Schedule Notice Negative Thousand Pair: 8 bytes ------------ */

typedef struct {
  uint8_t raw_strike_price_schedule_notice[7];  /* bytes 0 to 6 */
  uint8_t strike_price_fraction_indicator;      /* byte 7 */
} StrikePriceScheduleNoticeNegativeThousandPair;

/* any Strike Price Schedule Notice Negative Thousand Pair at all: every byte one the checker chooses */
static void any_strike_price_schedule_notice_negative_thousand_pair(StrikePriceScheduleNoticeNegativeThousandPair *record) {
  for (size_t i = 0; i < 7; i++) { record->raw_strike_price_schedule_notice[i] = arbitrary(); }
  record->strike_price_fraction_indicator = arbitrary();
}

/* Strike Price Schedule Notice Negative Thousand Pair to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_strike_price_schedule_notice_negative_thousand_pair(const StrikePriceScheduleNoticeNegativeThousandPair *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->raw_strike_price_schedule_notice[i]; }
  wire[at++] = record->strike_price_fraction_indicator;

  return at;
}

/* Strike Price Schedule Notice Negative Thousand Pair off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_strike_price_schedule_notice_negative_thousand_pair(StrikePriceScheduleNoticeNegativeThousandPair *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { record->raw_strike_price_schedule_notice[i] = wire[at++]; }
  record->strike_price_fraction_indicator = wire[at++];

  return at;
}

/* what was read of Strike Price Schedule Notice Negative Thousand Pair is what was written, byte for byte */
static void equal_strike_price_schedule_notice_negative_thousand_pair(const StrikePriceScheduleNoticeNegativeThousandPair *read, const StrikePriceScheduleNoticeNegativeThousandPair *written) {
  for (size_t i = 0; i < 7; i++) { assert(read->raw_strike_price_schedule_notice[i] == written->raw_strike_price_schedule_notice[i]); }
  assert(read->strike_price_fraction_indicator == written->strike_price_fraction_indicator);
}

/* Strike Price Schedule Notice Negative Thousand Pair: written and read back, then read and written back */
static void check_strike_price_schedule_notice_negative_thousand_pair(void) {
  StrikePriceScheduleNoticeNegativeThousandPair sent;
  StrikePriceScheduleNoticeNegativeThousandPair got;
  uint8_t wire[8];
  uint8_t again[8];

  any_strike_price_schedule_notice_negative_thousand_pair(&sent);
  assert(encode_strike_price_schedule_notice_negative_thousand_pair(&sent, wire, 0) == 8);
  assert(decode_strike_price_schedule_notice_negative_thousand_pair(&got, wire, 0) == 8);
  equal_strike_price_schedule_notice_negative_thousand_pair(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_strike_price_schedule_notice_negative_thousand_pair(&got, wire, 0) == 8);
  assert(encode_strike_price_schedule_notice_negative_thousand_pair(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Strike Price Schedule Notice Negative Ten Thousand Pair: 8 bytes -------- */

typedef struct {
  uint8_t raw_strike_price_schedule_notice[7];  /* bytes 0 to 6 */
  uint8_t strike_price_fraction_indicator;      /* byte 7 */
} StrikePriceScheduleNoticeNegativeTenThousandPair;

/* any Strike Price Schedule Notice Negative Ten Thousand Pair at all: every byte one the checker chooses */
static void any_strike_price_schedule_notice_negative_ten_thousand_pair(StrikePriceScheduleNoticeNegativeTenThousandPair *record) {
  for (size_t i = 0; i < 7; i++) { record->raw_strike_price_schedule_notice[i] = arbitrary(); }
  record->strike_price_fraction_indicator = arbitrary();
}

/* Strike Price Schedule Notice Negative Ten Thousand Pair to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_strike_price_schedule_notice_negative_ten_thousand_pair(const StrikePriceScheduleNoticeNegativeTenThousandPair *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->raw_strike_price_schedule_notice[i]; }
  wire[at++] = record->strike_price_fraction_indicator;

  return at;
}

/* Strike Price Schedule Notice Negative Ten Thousand Pair off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_strike_price_schedule_notice_negative_ten_thousand_pair(StrikePriceScheduleNoticeNegativeTenThousandPair *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { record->raw_strike_price_schedule_notice[i] = wire[at++]; }
  record->strike_price_fraction_indicator = wire[at++];

  return at;
}

/* what was read of Strike Price Schedule Notice Negative Ten Thousand Pair is what was written, byte for byte */
static void equal_strike_price_schedule_notice_negative_ten_thousand_pair(const StrikePriceScheduleNoticeNegativeTenThousandPair *read, const StrikePriceScheduleNoticeNegativeTenThousandPair *written) {
  for (size_t i = 0; i < 7; i++) { assert(read->raw_strike_price_schedule_notice[i] == written->raw_strike_price_schedule_notice[i]); }
  assert(read->strike_price_fraction_indicator == written->strike_price_fraction_indicator);
}

/* Strike Price Schedule Notice Negative Ten Thousand Pair: written and read back, then read and written back */
static void check_strike_price_schedule_notice_negative_ten_thousand_pair(void) {
  StrikePriceScheduleNoticeNegativeTenThousandPair sent;
  StrikePriceScheduleNoticeNegativeTenThousandPair got;
  uint8_t wire[8];
  uint8_t again[8];

  any_strike_price_schedule_notice_negative_ten_thousand_pair(&sent);
  assert(encode_strike_price_schedule_notice_negative_ten_thousand_pair(&sent, wire, 0) == 8);
  assert(decode_strike_price_schedule_notice_negative_ten_thousand_pair(&got, wire, 0) == 8);
  equal_strike_price_schedule_notice_negative_ten_thousand_pair(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_strike_price_schedule_notice_negative_ten_thousand_pair(&got, wire, 0) == 8);
  assert(encode_strike_price_schedule_notice_negative_ten_thousand_pair(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Strike Price Schedule Notice Negative Hundred Thousand Pair: 8 bytes ---- */

typedef struct {
  uint8_t raw_strike_price_schedule_notice[7];  /* bytes 0 to 6 */
  uint8_t strike_price_fraction_indicator;      /* byte 7 */
} StrikePriceScheduleNoticeNegativeHundredThousandPair;

/* any Strike Price Schedule Notice Negative Hundred Thousand Pair at all: every byte one the checker chooses */
static void any_strike_price_schedule_notice_negative_hundred_thousand_pair(StrikePriceScheduleNoticeNegativeHundredThousandPair *record) {
  for (size_t i = 0; i < 7; i++) { record->raw_strike_price_schedule_notice[i] = arbitrary(); }
  record->strike_price_fraction_indicator = arbitrary();
}

/* Strike Price Schedule Notice Negative Hundred Thousand Pair to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_strike_price_schedule_notice_negative_hundred_thousand_pair(const StrikePriceScheduleNoticeNegativeHundredThousandPair *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->raw_strike_price_schedule_notice[i]; }
  wire[at++] = record->strike_price_fraction_indicator;

  return at;
}

/* Strike Price Schedule Notice Negative Hundred Thousand Pair off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_strike_price_schedule_notice_negative_hundred_thousand_pair(StrikePriceScheduleNoticeNegativeHundredThousandPair *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { record->raw_strike_price_schedule_notice[i] = wire[at++]; }
  record->strike_price_fraction_indicator = wire[at++];

  return at;
}

/* what was read of Strike Price Schedule Notice Negative Hundred Thousand Pair is what was written, byte for byte */
static void equal_strike_price_schedule_notice_negative_hundred_thousand_pair(const StrikePriceScheduleNoticeNegativeHundredThousandPair *read, const StrikePriceScheduleNoticeNegativeHundredThousandPair *written) {
  for (size_t i = 0; i < 7; i++) { assert(read->raw_strike_price_schedule_notice[i] == written->raw_strike_price_schedule_notice[i]); }
  assert(read->strike_price_fraction_indicator == written->strike_price_fraction_indicator);
}

/* Strike Price Schedule Notice Negative Hundred Thousand Pair: written and read back, then read and written back */
static void check_strike_price_schedule_notice_negative_hundred_thousand_pair(void) {
  StrikePriceScheduleNoticeNegativeHundredThousandPair sent;
  StrikePriceScheduleNoticeNegativeHundredThousandPair got;
  uint8_t wire[8];
  uint8_t again[8];

  any_strike_price_schedule_notice_negative_hundred_thousand_pair(&sent);
  assert(encode_strike_price_schedule_notice_negative_hundred_thousand_pair(&sent, wire, 0) == 8);
  assert(decode_strike_price_schedule_notice_negative_hundred_thousand_pair(&got, wire, 0) == 8);
  equal_strike_price_schedule_notice_negative_hundred_thousand_pair(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_strike_price_schedule_notice_negative_hundred_thousand_pair(&got, wire, 0) == 8);
  assert(encode_strike_price_schedule_notice_negative_hundred_thousand_pair(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Strike Price Schedule Notice Negative Million Pair: 8 bytes ------------- */

typedef struct {
  uint8_t raw_strike_price_schedule_notice[7];  /* bytes 0 to 6 */
  uint8_t strike_price_fraction_indicator;      /* byte 7 */
} StrikePriceScheduleNoticeNegativeMillionPair;

/* any Strike Price Schedule Notice Negative Million Pair at all: every byte one the checker chooses */
static void any_strike_price_schedule_notice_negative_million_pair(StrikePriceScheduleNoticeNegativeMillionPair *record) {
  for (size_t i = 0; i < 7; i++) { record->raw_strike_price_schedule_notice[i] = arbitrary(); }
  record->strike_price_fraction_indicator = arbitrary();
}

/* Strike Price Schedule Notice Negative Million Pair to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_strike_price_schedule_notice_negative_million_pair(const StrikePriceScheduleNoticeNegativeMillionPair *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->raw_strike_price_schedule_notice[i]; }
  wire[at++] = record->strike_price_fraction_indicator;

  return at;
}

/* Strike Price Schedule Notice Negative Million Pair off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_strike_price_schedule_notice_negative_million_pair(StrikePriceScheduleNoticeNegativeMillionPair *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { record->raw_strike_price_schedule_notice[i] = wire[at++]; }
  record->strike_price_fraction_indicator = wire[at++];

  return at;
}

/* what was read of Strike Price Schedule Notice Negative Million Pair is what was written, byte for byte */
static void equal_strike_price_schedule_notice_negative_million_pair(const StrikePriceScheduleNoticeNegativeMillionPair *read, const StrikePriceScheduleNoticeNegativeMillionPair *written) {
  for (size_t i = 0; i < 7; i++) { assert(read->raw_strike_price_schedule_notice[i] == written->raw_strike_price_schedule_notice[i]); }
  assert(read->strike_price_fraction_indicator == written->strike_price_fraction_indicator);
}

/* Strike Price Schedule Notice Negative Million Pair: written and read back, then read and written back */
static void check_strike_price_schedule_notice_negative_million_pair(void) {
  StrikePriceScheduleNoticeNegativeMillionPair sent;
  StrikePriceScheduleNoticeNegativeMillionPair got;
  uint8_t wire[8];
  uint8_t again[8];

  any_strike_price_schedule_notice_negative_million_pair(&sent);
  assert(encode_strike_price_schedule_notice_negative_million_pair(&sent, wire, 0) == 8);
  assert(decode_strike_price_schedule_notice_negative_million_pair(&got, wire, 0) == 8);
  equal_strike_price_schedule_notice_negative_million_pair(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_strike_price_schedule_notice_negative_million_pair(&got, wire, 0) == 8);
  assert(encode_strike_price_schedule_notice_negative_million_pair(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Strike Price Schedule Notice Numeric Pair: 8 bytes ---------------------- */

typedef struct {
  uint8_t strike_price_schedule_notice[7];  /* bytes 0 to 6 */
  uint8_t strike_price_fraction_indicator;  /* byte 7 */
} StrikePriceScheduleNoticeNumericPair;

/* any Strike Price Schedule Notice Numeric Pair at all: every byte one the checker chooses */
static void any_strike_price_schedule_notice_numeric_pair(StrikePriceScheduleNoticeNumericPair *record) {
  for (size_t i = 0; i < 7; i++) { record->strike_price_schedule_notice[i] = arbitrary(); }
  record->strike_price_fraction_indicator = arbitrary();
}

/* Strike Price Schedule Notice Numeric Pair to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_strike_price_schedule_notice_numeric_pair(const StrikePriceScheduleNoticeNumericPair *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->strike_price_schedule_notice[i]; }
  wire[at++] = record->strike_price_fraction_indicator;

  return at;
}

/* Strike Price Schedule Notice Numeric Pair off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_strike_price_schedule_notice_numeric_pair(StrikePriceScheduleNoticeNumericPair *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { record->strike_price_schedule_notice[i] = wire[at++]; }
  record->strike_price_fraction_indicator = wire[at++];

  return at;
}

/* what was read of Strike Price Schedule Notice Numeric Pair is what was written, byte for byte */
static void equal_strike_price_schedule_notice_numeric_pair(const StrikePriceScheduleNoticeNumericPair *read, const StrikePriceScheduleNoticeNumericPair *written) {
  for (size_t i = 0; i < 7; i++) { assert(read->strike_price_schedule_notice[i] == written->strike_price_schedule_notice[i]); }
  assert(read->strike_price_fraction_indicator == written->strike_price_fraction_indicator);
}

/* Strike Price Schedule Notice Numeric Pair: written and read back, then read and written back */
static void check_strike_price_schedule_notice_numeric_pair(void) {
  StrikePriceScheduleNoticeNumericPair sent;
  StrikePriceScheduleNoticeNumericPair got;
  uint8_t wire[8];
  uint8_t again[8];

  any_strike_price_schedule_notice_numeric_pair(&sent);
  assert(encode_strike_price_schedule_notice_numeric_pair(&sent, wire, 0) == 8);
  assert(decode_strike_price_schedule_notice_numeric_pair(&got, wire, 0) == 8);
  equal_strike_price_schedule_notice_numeric_pair(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_strike_price_schedule_notice_numeric_pair(&got, wire, 0) == 8);
  assert(encode_strike_price_schedule_notice_numeric_pair(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Instrument Schedule Notice Future Message: 31 bytes --------------------- */

/* Instrument Schedule Notice Future message */
typedef struct {
  LongMessageHeader long_message_header;    /* bytes 0 to 11 */
  uint8_t exchange_id;                      /* byte 12 */
  FutureProduct future_product;             /* bytes 13 to 23 */
  uint8_t series_status;                    /* byte 24 */
  uint8_t scheduled_status_change_time[6];  /* bytes 25 to 30 */
} InstrumentScheduleNoticeFutureMessage;

/* any Instrument Schedule Notice Future Message at all: every byte one the checker chooses */
static void any_instrument_schedule_notice_future_message(InstrumentScheduleNoticeFutureMessage *record) {
  any_long_message_header(&record->long_message_header);
  record->exchange_id = arbitrary();
  any_future_product(&record->future_product);
  record->series_status = arbitrary();
  for (size_t i = 0; i < 6; i++) { record->scheduled_status_change_time[i] = arbitrary(); }
}

/* Instrument Schedule Notice Future Message to the wire: 31 bytes from at, returning where the next byte goes */
static size_t encode_instrument_schedule_notice_future_message(const InstrumentScheduleNoticeFutureMessage *record, uint8_t *wire, size_t at) {
  at = encode_long_message_header(&record->long_message_header, wire, at);
  wire[at++] = record->exchange_id;
  at = encode_future_product(&record->future_product, wire, at);
  wire[at++] = record->series_status;
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->scheduled_status_change_time[i]; }

  return at;
}

/* Instrument Schedule Notice Future Message off the wire: 31 bytes from at, returning where the next byte lies */
static size_t decode_instrument_schedule_notice_future_message(InstrumentScheduleNoticeFutureMessage *record, const uint8_t *wire, size_t at) {
  at = decode_long_message_header(&record->long_message_header, wire, at);
  record->exchange_id = wire[at++];
  at = decode_future_product(&record->future_product, wire, at);
  record->series_status = wire[at++];
  for (size_t i = 0; i < 6; i++) { record->scheduled_status_change_time[i] = wire[at++]; }

  return at;
}

/* what was read of Instrument Schedule Notice Future Message is what was written, byte for byte */
static void equal_instrument_schedule_notice_future_message(const InstrumentScheduleNoticeFutureMessage *read, const InstrumentScheduleNoticeFutureMessage *written) {
  equal_long_message_header(&read->long_message_header, &written->long_message_header);
  assert(read->exchange_id == written->exchange_id);
  equal_future_product(&read->future_product, &written->future_product);
  assert(read->series_status == written->series_status);
  for (size_t i = 0; i < 6; i++) { assert(read->scheduled_status_change_time[i] == written->scheduled_status_change_time[i]); }
}

/* Instrument Schedule Notice Future Message: written and read back, then read and written back */
static void check_instrument_schedule_notice_future_message(void) {
  InstrumentScheduleNoticeFutureMessage sent;
  InstrumentScheduleNoticeFutureMessage got;
  uint8_t wire[31];
  uint8_t again[31];

  any_instrument_schedule_notice_future_message(&sent);
  assert(encode_instrument_schedule_notice_future_message(&sent, wire, 0) == 31);
  assert(decode_instrument_schedule_notice_future_message(&got, wire, 0) == 31);
  equal_instrument_schedule_notice_future_message(&got, &sent);

  for (size_t i = 0; i < 31; i++) { wire[i] = arbitrary(); }
  assert(decode_instrument_schedule_notice_future_message(&got, wire, 0) == 31);
  assert(encode_instrument_schedule_notice_future_message(&got, again, 0) == 31);
  for (size_t i = 0; i < 31; i++) { assert(again[i] == wire[i]); }
}

/* ---- Instrument Schedule Notice Strategy Message: 50 bytes ------------------- */

/* Instrument Schedule Notice Strategy message */
typedef struct {
  LongMessageHeader long_message_header;    /* bytes 0 to 11 */
  uint8_t exchange_id;                      /* byte 12 */
  uint8_t strategy_symbol[30];              /* bytes 13 to 42 */
  uint8_t series_status;                    /* byte 43 */
  uint8_t scheduled_status_change_time[6];  /* bytes 44 to 49 */
} InstrumentScheduleNoticeStrategyMessage;

/* any Instrument Schedule Notice Strategy Message at all: every byte one the checker chooses */
static void any_instrument_schedule_notice_strategy_message(InstrumentScheduleNoticeStrategyMessage *record) {
  any_long_message_header(&record->long_message_header);
  record->exchange_id = arbitrary();
  for (size_t i = 0; i < 30; i++) { record->strategy_symbol[i] = arbitrary(); }
  record->series_status = arbitrary();
  for (size_t i = 0; i < 6; i++) { record->scheduled_status_change_time[i] = arbitrary(); }
}

/* Instrument Schedule Notice Strategy Message to the wire: 50 bytes from at, returning where the next byte goes */
static size_t encode_instrument_schedule_notice_strategy_message(const InstrumentScheduleNoticeStrategyMessage *record, uint8_t *wire, size_t at) {
  at = encode_long_message_header(&record->long_message_header, wire, at);
  wire[at++] = record->exchange_id;
  for (size_t i = 0; i < 30; i++) { wire[at++] = record->strategy_symbol[i]; }
  wire[at++] = record->series_status;
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->scheduled_status_change_time[i]; }

  return at;
}

/* Instrument Schedule Notice Strategy Message off the wire: 50 bytes from at, returning where the next byte lies */
static size_t decode_instrument_schedule_notice_strategy_message(InstrumentScheduleNoticeStrategyMessage *record, const uint8_t *wire, size_t at) {
  at = decode_long_message_header(&record->long_message_header, wire, at);
  record->exchange_id = wire[at++];
  for (size_t i = 0; i < 30; i++) { record->strategy_symbol[i] = wire[at++]; }
  record->series_status = wire[at++];
  for (size_t i = 0; i < 6; i++) { record->scheduled_status_change_time[i] = wire[at++]; }

  return at;
}

/* what was read of Instrument Schedule Notice Strategy Message is what was written, byte for byte */
static void equal_instrument_schedule_notice_strategy_message(const InstrumentScheduleNoticeStrategyMessage *read, const InstrumentScheduleNoticeStrategyMessage *written) {
  equal_long_message_header(&read->long_message_header, &written->long_message_header);
  assert(read->exchange_id == written->exchange_id);
  for (size_t i = 0; i < 30; i++) { assert(read->strategy_symbol[i] == written->strategy_symbol[i]); }
  assert(read->series_status == written->series_status);
  for (size_t i = 0; i < 6; i++) { assert(read->scheduled_status_change_time[i] == written->scheduled_status_change_time[i]); }
}

/* Instrument Schedule Notice Strategy Message: written and read back, then read and written back */
static void check_instrument_schedule_notice_strategy_message(void) {
  InstrumentScheduleNoticeStrategyMessage sent;
  InstrumentScheduleNoticeStrategyMessage got;
  uint8_t wire[50];
  uint8_t again[50];

  any_instrument_schedule_notice_strategy_message(&sent);
  assert(encode_instrument_schedule_notice_strategy_message(&sent, wire, 0) == 50);
  assert(decode_instrument_schedule_notice_strategy_message(&got, wire, 0) == 50);
  equal_instrument_schedule_notice_strategy_message(&got, &sent);

  for (size_t i = 0; i < 50; i++) { wire[i] = arbitrary(); }
  assert(decode_instrument_schedule_notice_strategy_message(&got, wire, 0) == 50);
  assert(encode_instrument_schedule_notice_strategy_message(&got, again, 0) == 50);
  for (size_t i = 0; i < 50; i++) { assert(again[i] == wire[i]); }
}

/* ---- Bid Price Quote Opening Pair: 8 bytes ----------------------------------- */

typedef struct {
  uint8_t bid_price_quote_opening[7];    /* bytes 0 to 6 */
  uint8_t bid_price_fraction_indicator;  /* byte 7 */
} BidPriceQuoteOpeningPair;

/* any Bid Price Quote Opening Pair at all: every byte one the checker chooses */
static void any_bid_price_quote_opening_pair(BidPriceQuoteOpeningPair *record) {
  for (size_t i = 0; i < 7; i++) { record->bid_price_quote_opening[i] = arbitrary(); }
  record->bid_price_fraction_indicator = arbitrary();
}

/* Bid Price Quote Opening Pair to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_bid_price_quote_opening_pair(const BidPriceQuoteOpeningPair *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->bid_price_quote_opening[i]; }
  wire[at++] = record->bid_price_fraction_indicator;

  return at;
}

/* Bid Price Quote Opening Pair off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_bid_price_quote_opening_pair(BidPriceQuoteOpeningPair *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { record->bid_price_quote_opening[i] = wire[at++]; }
  record->bid_price_fraction_indicator = wire[at++];

  return at;
}

/* what was read of Bid Price Quote Opening Pair is what was written, byte for byte */
static void equal_bid_price_quote_opening_pair(const BidPriceQuoteOpeningPair *read, const BidPriceQuoteOpeningPair *written) {
  for (size_t i = 0; i < 7; i++) { assert(read->bid_price_quote_opening[i] == written->bid_price_quote_opening[i]); }
  assert(read->bid_price_fraction_indicator == written->bid_price_fraction_indicator);
}

/* Bid Price Quote Opening Pair: written and read back, then read and written back */
static void check_bid_price_quote_opening_pair(void) {
  BidPriceQuoteOpeningPair sent;
  BidPriceQuoteOpeningPair got;
  uint8_t wire[8];
  uint8_t again[8];

  any_bid_price_quote_opening_pair(&sent);
  assert(encode_bid_price_quote_opening_pair(&sent, wire, 0) == 8);
  assert(decode_bid_price_quote_opening_pair(&got, wire, 0) == 8);
  equal_bid_price_quote_opening_pair(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_bid_price_quote_opening_pair(&got, wire, 0) == 8);
  assert(encode_bid_price_quote_opening_pair(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Bid Price Quote Numeric Negative Whole Pair: 8 bytes -------------------- */

typedef struct {
  uint8_t raw_bid_price_quote_numeric[7];  /* bytes 0 to 6 */
  uint8_t bid_price_fraction_indicator;    /* byte 7 */
} BidPriceQuoteNumericNegativeWholePair;

/* any Bid Price Quote Numeric Negative Whole Pair at all: every byte one the checker chooses */
static void any_bid_price_quote_numeric_negative_whole_pair(BidPriceQuoteNumericNegativeWholePair *record) {
  for (size_t i = 0; i < 7; i++) { record->raw_bid_price_quote_numeric[i] = arbitrary(); }
  record->bid_price_fraction_indicator = arbitrary();
}

/* Bid Price Quote Numeric Negative Whole Pair to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_bid_price_quote_numeric_negative_whole_pair(const BidPriceQuoteNumericNegativeWholePair *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->raw_bid_price_quote_numeric[i]; }
  wire[at++] = record->bid_price_fraction_indicator;

  return at;
}

/* Bid Price Quote Numeric Negative Whole Pair off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_bid_price_quote_numeric_negative_whole_pair(BidPriceQuoteNumericNegativeWholePair *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { record->raw_bid_price_quote_numeric[i] = wire[at++]; }
  record->bid_price_fraction_indicator = wire[at++];

  return at;
}

/* what was read of Bid Price Quote Numeric Negative Whole Pair is what was written, byte for byte */
static void equal_bid_price_quote_numeric_negative_whole_pair(const BidPriceQuoteNumericNegativeWholePair *read, const BidPriceQuoteNumericNegativeWholePair *written) {
  for (size_t i = 0; i < 7; i++) { assert(read->raw_bid_price_quote_numeric[i] == written->raw_bid_price_quote_numeric[i]); }
  assert(read->bid_price_fraction_indicator == written->bid_price_fraction_indicator);
}

/* Bid Price Quote Numeric Negative Whole Pair: written and read back, then read and written back */
static void check_bid_price_quote_numeric_negative_whole_pair(void) {
  BidPriceQuoteNumericNegativeWholePair sent;
  BidPriceQuoteNumericNegativeWholePair got;
  uint8_t wire[8];
  uint8_t again[8];

  any_bid_price_quote_numeric_negative_whole_pair(&sent);
  assert(encode_bid_price_quote_numeric_negative_whole_pair(&sent, wire, 0) == 8);
  assert(decode_bid_price_quote_numeric_negative_whole_pair(&got, wire, 0) == 8);
  equal_bid_price_quote_numeric_negative_whole_pair(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_bid_price_quote_numeric_negative_whole_pair(&got, wire, 0) == 8);
  assert(encode_bid_price_quote_numeric_negative_whole_pair(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Bid Price Quote Numeric Negative Ten Pair: 8 bytes ---------------------- */

typedef struct {
  uint8_t raw_bid_price_quote_numeric[7];  /* bytes 0 to 6 */
  uint8_t bid_price_fraction_indicator;    /* byte 7 */
} BidPriceQuoteNumericNegativeTenPair;

/* any Bid Price Quote Numeric Negative Ten Pair at all: every byte one the checker chooses */
static void any_bid_price_quote_numeric_negative_ten_pair(BidPriceQuoteNumericNegativeTenPair *record) {
  for (size_t i = 0; i < 7; i++) { record->raw_bid_price_quote_numeric[i] = arbitrary(); }
  record->bid_price_fraction_indicator = arbitrary();
}

/* Bid Price Quote Numeric Negative Ten Pair to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_bid_price_quote_numeric_negative_ten_pair(const BidPriceQuoteNumericNegativeTenPair *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->raw_bid_price_quote_numeric[i]; }
  wire[at++] = record->bid_price_fraction_indicator;

  return at;
}

/* Bid Price Quote Numeric Negative Ten Pair off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_bid_price_quote_numeric_negative_ten_pair(BidPriceQuoteNumericNegativeTenPair *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { record->raw_bid_price_quote_numeric[i] = wire[at++]; }
  record->bid_price_fraction_indicator = wire[at++];

  return at;
}

/* what was read of Bid Price Quote Numeric Negative Ten Pair is what was written, byte for byte */
static void equal_bid_price_quote_numeric_negative_ten_pair(const BidPriceQuoteNumericNegativeTenPair *read, const BidPriceQuoteNumericNegativeTenPair *written) {
  for (size_t i = 0; i < 7; i++) { assert(read->raw_bid_price_quote_numeric[i] == written->raw_bid_price_quote_numeric[i]); }
  assert(read->bid_price_fraction_indicator == written->bid_price_fraction_indicator);
}

/* Bid Price Quote Numeric Negative Ten Pair: written and read back, then read and written back */
static void check_bid_price_quote_numeric_negative_ten_pair(void) {
  BidPriceQuoteNumericNegativeTenPair sent;
  BidPriceQuoteNumericNegativeTenPair got;
  uint8_t wire[8];
  uint8_t again[8];

  any_bid_price_quote_numeric_negative_ten_pair(&sent);
  assert(encode_bid_price_quote_numeric_negative_ten_pair(&sent, wire, 0) == 8);
  assert(decode_bid_price_quote_numeric_negative_ten_pair(&got, wire, 0) == 8);
  equal_bid_price_quote_numeric_negative_ten_pair(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_bid_price_quote_numeric_negative_ten_pair(&got, wire, 0) == 8);
  assert(encode_bid_price_quote_numeric_negative_ten_pair(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Bid Price Quote Numeric Negative Hundred Pair: 8 bytes ------------------ */

typedef struct {
  uint8_t raw_bid_price_quote_numeric[7];  /* bytes 0 to 6 */
  uint8_t bid_price_fraction_indicator;    /* byte 7 */
} BidPriceQuoteNumericNegativeHundredPair;

/* any Bid Price Quote Numeric Negative Hundred Pair at all: every byte one the checker chooses */
static void any_bid_price_quote_numeric_negative_hundred_pair(BidPriceQuoteNumericNegativeHundredPair *record) {
  for (size_t i = 0; i < 7; i++) { record->raw_bid_price_quote_numeric[i] = arbitrary(); }
  record->bid_price_fraction_indicator = arbitrary();
}

/* Bid Price Quote Numeric Negative Hundred Pair to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_bid_price_quote_numeric_negative_hundred_pair(const BidPriceQuoteNumericNegativeHundredPair *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->raw_bid_price_quote_numeric[i]; }
  wire[at++] = record->bid_price_fraction_indicator;

  return at;
}

/* Bid Price Quote Numeric Negative Hundred Pair off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_bid_price_quote_numeric_negative_hundred_pair(BidPriceQuoteNumericNegativeHundredPair *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { record->raw_bid_price_quote_numeric[i] = wire[at++]; }
  record->bid_price_fraction_indicator = wire[at++];

  return at;
}

/* what was read of Bid Price Quote Numeric Negative Hundred Pair is what was written, byte for byte */
static void equal_bid_price_quote_numeric_negative_hundred_pair(const BidPriceQuoteNumericNegativeHundredPair *read, const BidPriceQuoteNumericNegativeHundredPair *written) {
  for (size_t i = 0; i < 7; i++) { assert(read->raw_bid_price_quote_numeric[i] == written->raw_bid_price_quote_numeric[i]); }
  assert(read->bid_price_fraction_indicator == written->bid_price_fraction_indicator);
}

/* Bid Price Quote Numeric Negative Hundred Pair: written and read back, then read and written back */
static void check_bid_price_quote_numeric_negative_hundred_pair(void) {
  BidPriceQuoteNumericNegativeHundredPair sent;
  BidPriceQuoteNumericNegativeHundredPair got;
  uint8_t wire[8];
  uint8_t again[8];

  any_bid_price_quote_numeric_negative_hundred_pair(&sent);
  assert(encode_bid_price_quote_numeric_negative_hundred_pair(&sent, wire, 0) == 8);
  assert(decode_bid_price_quote_numeric_negative_hundred_pair(&got, wire, 0) == 8);
  equal_bid_price_quote_numeric_negative_hundred_pair(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_bid_price_quote_numeric_negative_hundred_pair(&got, wire, 0) == 8);
  assert(encode_bid_price_quote_numeric_negative_hundred_pair(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Bid Price Quote Numeric Negative Thousand Pair: 8 bytes ----------------- */

typedef struct {
  uint8_t raw_bid_price_quote_numeric[7];  /* bytes 0 to 6 */
  uint8_t bid_price_fraction_indicator;    /* byte 7 */
} BidPriceQuoteNumericNegativeThousandPair;

/* any Bid Price Quote Numeric Negative Thousand Pair at all: every byte one the checker chooses */
static void any_bid_price_quote_numeric_negative_thousand_pair(BidPriceQuoteNumericNegativeThousandPair *record) {
  for (size_t i = 0; i < 7; i++) { record->raw_bid_price_quote_numeric[i] = arbitrary(); }
  record->bid_price_fraction_indicator = arbitrary();
}

/* Bid Price Quote Numeric Negative Thousand Pair to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_bid_price_quote_numeric_negative_thousand_pair(const BidPriceQuoteNumericNegativeThousandPair *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->raw_bid_price_quote_numeric[i]; }
  wire[at++] = record->bid_price_fraction_indicator;

  return at;
}

/* Bid Price Quote Numeric Negative Thousand Pair off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_bid_price_quote_numeric_negative_thousand_pair(BidPriceQuoteNumericNegativeThousandPair *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { record->raw_bid_price_quote_numeric[i] = wire[at++]; }
  record->bid_price_fraction_indicator = wire[at++];

  return at;
}

/* what was read of Bid Price Quote Numeric Negative Thousand Pair is what was written, byte for byte */
static void equal_bid_price_quote_numeric_negative_thousand_pair(const BidPriceQuoteNumericNegativeThousandPair *read, const BidPriceQuoteNumericNegativeThousandPair *written) {
  for (size_t i = 0; i < 7; i++) { assert(read->raw_bid_price_quote_numeric[i] == written->raw_bid_price_quote_numeric[i]); }
  assert(read->bid_price_fraction_indicator == written->bid_price_fraction_indicator);
}

/* Bid Price Quote Numeric Negative Thousand Pair: written and read back, then read and written back */
static void check_bid_price_quote_numeric_negative_thousand_pair(void) {
  BidPriceQuoteNumericNegativeThousandPair sent;
  BidPriceQuoteNumericNegativeThousandPair got;
  uint8_t wire[8];
  uint8_t again[8];

  any_bid_price_quote_numeric_negative_thousand_pair(&sent);
  assert(encode_bid_price_quote_numeric_negative_thousand_pair(&sent, wire, 0) == 8);
  assert(decode_bid_price_quote_numeric_negative_thousand_pair(&got, wire, 0) == 8);
  equal_bid_price_quote_numeric_negative_thousand_pair(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_bid_price_quote_numeric_negative_thousand_pair(&got, wire, 0) == 8);
  assert(encode_bid_price_quote_numeric_negative_thousand_pair(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Bid Price Quote Numeric Negative Ten Thousand Pair: 8 bytes ------------- */

typedef struct {
  uint8_t raw_bid_price_quote_numeric[7];  /* bytes 0 to 6 */
  uint8_t bid_price_fraction_indicator;    /* byte 7 */
} BidPriceQuoteNumericNegativeTenThousandPair;

/* any Bid Price Quote Numeric Negative Ten Thousand Pair at all: every byte one the checker chooses */
static void any_bid_price_quote_numeric_negative_ten_thousand_pair(BidPriceQuoteNumericNegativeTenThousandPair *record) {
  for (size_t i = 0; i < 7; i++) { record->raw_bid_price_quote_numeric[i] = arbitrary(); }
  record->bid_price_fraction_indicator = arbitrary();
}

/* Bid Price Quote Numeric Negative Ten Thousand Pair to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_bid_price_quote_numeric_negative_ten_thousand_pair(const BidPriceQuoteNumericNegativeTenThousandPair *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->raw_bid_price_quote_numeric[i]; }
  wire[at++] = record->bid_price_fraction_indicator;

  return at;
}

/* Bid Price Quote Numeric Negative Ten Thousand Pair off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_bid_price_quote_numeric_negative_ten_thousand_pair(BidPriceQuoteNumericNegativeTenThousandPair *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { record->raw_bid_price_quote_numeric[i] = wire[at++]; }
  record->bid_price_fraction_indicator = wire[at++];

  return at;
}

/* what was read of Bid Price Quote Numeric Negative Ten Thousand Pair is what was written, byte for byte */
static void equal_bid_price_quote_numeric_negative_ten_thousand_pair(const BidPriceQuoteNumericNegativeTenThousandPair *read, const BidPriceQuoteNumericNegativeTenThousandPair *written) {
  for (size_t i = 0; i < 7; i++) { assert(read->raw_bid_price_quote_numeric[i] == written->raw_bid_price_quote_numeric[i]); }
  assert(read->bid_price_fraction_indicator == written->bid_price_fraction_indicator);
}

/* Bid Price Quote Numeric Negative Ten Thousand Pair: written and read back, then read and written back */
static void check_bid_price_quote_numeric_negative_ten_thousand_pair(void) {
  BidPriceQuoteNumericNegativeTenThousandPair sent;
  BidPriceQuoteNumericNegativeTenThousandPair got;
  uint8_t wire[8];
  uint8_t again[8];

  any_bid_price_quote_numeric_negative_ten_thousand_pair(&sent);
  assert(encode_bid_price_quote_numeric_negative_ten_thousand_pair(&sent, wire, 0) == 8);
  assert(decode_bid_price_quote_numeric_negative_ten_thousand_pair(&got, wire, 0) == 8);
  equal_bid_price_quote_numeric_negative_ten_thousand_pair(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_bid_price_quote_numeric_negative_ten_thousand_pair(&got, wire, 0) == 8);
  assert(encode_bid_price_quote_numeric_negative_ten_thousand_pair(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Bid Price Quote Numeric Negative Hundred Thousand Pair: 8 bytes --------- */

typedef struct {
  uint8_t raw_bid_price_quote_numeric[7];  /* bytes 0 to 6 */
  uint8_t bid_price_fraction_indicator;    /* byte 7 */
} BidPriceQuoteNumericNegativeHundredThousandPair;

/* any Bid Price Quote Numeric Negative Hundred Thousand Pair at all: every byte one the checker chooses */
static void any_bid_price_quote_numeric_negative_hundred_thousand_pair(BidPriceQuoteNumericNegativeHundredThousandPair *record) {
  for (size_t i = 0; i < 7; i++) { record->raw_bid_price_quote_numeric[i] = arbitrary(); }
  record->bid_price_fraction_indicator = arbitrary();
}

/* Bid Price Quote Numeric Negative Hundred Thousand Pair to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_bid_price_quote_numeric_negative_hundred_thousand_pair(const BidPriceQuoteNumericNegativeHundredThousandPair *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->raw_bid_price_quote_numeric[i]; }
  wire[at++] = record->bid_price_fraction_indicator;

  return at;
}

/* Bid Price Quote Numeric Negative Hundred Thousand Pair off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_bid_price_quote_numeric_negative_hundred_thousand_pair(BidPriceQuoteNumericNegativeHundredThousandPair *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { record->raw_bid_price_quote_numeric[i] = wire[at++]; }
  record->bid_price_fraction_indicator = wire[at++];

  return at;
}

/* what was read of Bid Price Quote Numeric Negative Hundred Thousand Pair is what was written, byte for byte */
static void equal_bid_price_quote_numeric_negative_hundred_thousand_pair(const BidPriceQuoteNumericNegativeHundredThousandPair *read, const BidPriceQuoteNumericNegativeHundredThousandPair *written) {
  for (size_t i = 0; i < 7; i++) { assert(read->raw_bid_price_quote_numeric[i] == written->raw_bid_price_quote_numeric[i]); }
  assert(read->bid_price_fraction_indicator == written->bid_price_fraction_indicator);
}

/* Bid Price Quote Numeric Negative Hundred Thousand Pair: written and read back, then read and written back */
static void check_bid_price_quote_numeric_negative_hundred_thousand_pair(void) {
  BidPriceQuoteNumericNegativeHundredThousandPair sent;
  BidPriceQuoteNumericNegativeHundredThousandPair got;
  uint8_t wire[8];
  uint8_t again[8];

  any_bid_price_quote_numeric_negative_hundred_thousand_pair(&sent);
  assert(encode_bid_price_quote_numeric_negative_hundred_thousand_pair(&sent, wire, 0) == 8);
  assert(decode_bid_price_quote_numeric_negative_hundred_thousand_pair(&got, wire, 0) == 8);
  equal_bid_price_quote_numeric_negative_hundred_thousand_pair(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_bid_price_quote_numeric_negative_hundred_thousand_pair(&got, wire, 0) == 8);
  assert(encode_bid_price_quote_numeric_negative_hundred_thousand_pair(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Bid Price Quote Numeric Negative Million Pair: 8 bytes ------------------ */

typedef struct {
  uint8_t raw_bid_price_quote_numeric[7];  /* bytes 0 to 6 */
  uint8_t bid_price_fraction_indicator;    /* byte 7 */
} BidPriceQuoteNumericNegativeMillionPair;

/* any Bid Price Quote Numeric Negative Million Pair at all: every byte one the checker chooses */
static void any_bid_price_quote_numeric_negative_million_pair(BidPriceQuoteNumericNegativeMillionPair *record) {
  for (size_t i = 0; i < 7; i++) { record->raw_bid_price_quote_numeric[i] = arbitrary(); }
  record->bid_price_fraction_indicator = arbitrary();
}

/* Bid Price Quote Numeric Negative Million Pair to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_bid_price_quote_numeric_negative_million_pair(const BidPriceQuoteNumericNegativeMillionPair *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->raw_bid_price_quote_numeric[i]; }
  wire[at++] = record->bid_price_fraction_indicator;

  return at;
}

/* Bid Price Quote Numeric Negative Million Pair off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_bid_price_quote_numeric_negative_million_pair(BidPriceQuoteNumericNegativeMillionPair *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { record->raw_bid_price_quote_numeric[i] = wire[at++]; }
  record->bid_price_fraction_indicator = wire[at++];

  return at;
}

/* what was read of Bid Price Quote Numeric Negative Million Pair is what was written, byte for byte */
static void equal_bid_price_quote_numeric_negative_million_pair(const BidPriceQuoteNumericNegativeMillionPair *read, const BidPriceQuoteNumericNegativeMillionPair *written) {
  for (size_t i = 0; i < 7; i++) { assert(read->raw_bid_price_quote_numeric[i] == written->raw_bid_price_quote_numeric[i]); }
  assert(read->bid_price_fraction_indicator == written->bid_price_fraction_indicator);
}

/* Bid Price Quote Numeric Negative Million Pair: written and read back, then read and written back */
static void check_bid_price_quote_numeric_negative_million_pair(void) {
  BidPriceQuoteNumericNegativeMillionPair sent;
  BidPriceQuoteNumericNegativeMillionPair got;
  uint8_t wire[8];
  uint8_t again[8];

  any_bid_price_quote_numeric_negative_million_pair(&sent);
  assert(encode_bid_price_quote_numeric_negative_million_pair(&sent, wire, 0) == 8);
  assert(decode_bid_price_quote_numeric_negative_million_pair(&got, wire, 0) == 8);
  equal_bid_price_quote_numeric_negative_million_pair(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_bid_price_quote_numeric_negative_million_pair(&got, wire, 0) == 8);
  assert(encode_bid_price_quote_numeric_negative_million_pair(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Bid Price Quote Numeric Pair: 8 bytes ----------------------------------- */

typedef struct {
  uint8_t bid_price_quote_numeric[7];    /* bytes 0 to 6 */
  uint8_t bid_price_fraction_indicator;  /* byte 7 */
} BidPriceQuoteNumericPair;

/* any Bid Price Quote Numeric Pair at all: every byte one the checker chooses */
static void any_bid_price_quote_numeric_pair(BidPriceQuoteNumericPair *record) {
  for (size_t i = 0; i < 7; i++) { record->bid_price_quote_numeric[i] = arbitrary(); }
  record->bid_price_fraction_indicator = arbitrary();
}

/* Bid Price Quote Numeric Pair to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_bid_price_quote_numeric_pair(const BidPriceQuoteNumericPair *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->bid_price_quote_numeric[i]; }
  wire[at++] = record->bid_price_fraction_indicator;

  return at;
}

/* Bid Price Quote Numeric Pair off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_bid_price_quote_numeric_pair(BidPriceQuoteNumericPair *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { record->bid_price_quote_numeric[i] = wire[at++]; }
  record->bid_price_fraction_indicator = wire[at++];

  return at;
}

/* what was read of Bid Price Quote Numeric Pair is what was written, byte for byte */
static void equal_bid_price_quote_numeric_pair(const BidPriceQuoteNumericPair *read, const BidPriceQuoteNumericPair *written) {
  for (size_t i = 0; i < 7; i++) { assert(read->bid_price_quote_numeric[i] == written->bid_price_quote_numeric[i]); }
  assert(read->bid_price_fraction_indicator == written->bid_price_fraction_indicator);
}

/* Bid Price Quote Numeric Pair: written and read back, then read and written back */
static void check_bid_price_quote_numeric_pair(void) {
  BidPriceQuoteNumericPair sent;
  BidPriceQuoteNumericPair got;
  uint8_t wire[8];
  uint8_t again[8];

  any_bid_price_quote_numeric_pair(&sent);
  assert(encode_bid_price_quote_numeric_pair(&sent, wire, 0) == 8);
  assert(decode_bid_price_quote_numeric_pair(&got, wire, 0) == 8);
  equal_bid_price_quote_numeric_pair(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_bid_price_quote_numeric_pair(&got, wire, 0) == 8);
  assert(encode_bid_price_quote_numeric_pair(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Ask Price Quote Opening Pair: 8 bytes ----------------------------------- */

typedef struct {
  uint8_t ask_price_quote_opening[7];    /* bytes 0 to 6 */
  uint8_t ask_price_fraction_indicator;  /* byte 7 */
} AskPriceQuoteOpeningPair;

/* any Ask Price Quote Opening Pair at all: every byte one the checker chooses */
static void any_ask_price_quote_opening_pair(AskPriceQuoteOpeningPair *record) {
  for (size_t i = 0; i < 7; i++) { record->ask_price_quote_opening[i] = arbitrary(); }
  record->ask_price_fraction_indicator = arbitrary();
}

/* Ask Price Quote Opening Pair to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_ask_price_quote_opening_pair(const AskPriceQuoteOpeningPair *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->ask_price_quote_opening[i]; }
  wire[at++] = record->ask_price_fraction_indicator;

  return at;
}

/* Ask Price Quote Opening Pair off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_ask_price_quote_opening_pair(AskPriceQuoteOpeningPair *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { record->ask_price_quote_opening[i] = wire[at++]; }
  record->ask_price_fraction_indicator = wire[at++];

  return at;
}

/* what was read of Ask Price Quote Opening Pair is what was written, byte for byte */
static void equal_ask_price_quote_opening_pair(const AskPriceQuoteOpeningPair *read, const AskPriceQuoteOpeningPair *written) {
  for (size_t i = 0; i < 7; i++) { assert(read->ask_price_quote_opening[i] == written->ask_price_quote_opening[i]); }
  assert(read->ask_price_fraction_indicator == written->ask_price_fraction_indicator);
}

/* Ask Price Quote Opening Pair: written and read back, then read and written back */
static void check_ask_price_quote_opening_pair(void) {
  AskPriceQuoteOpeningPair sent;
  AskPriceQuoteOpeningPair got;
  uint8_t wire[8];
  uint8_t again[8];

  any_ask_price_quote_opening_pair(&sent);
  assert(encode_ask_price_quote_opening_pair(&sent, wire, 0) == 8);
  assert(decode_ask_price_quote_opening_pair(&got, wire, 0) == 8);
  equal_ask_price_quote_opening_pair(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_ask_price_quote_opening_pair(&got, wire, 0) == 8);
  assert(encode_ask_price_quote_opening_pair(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Ask Price Quote Numeric Negative Whole Pair: 8 bytes -------------------- */

typedef struct {
  uint8_t raw_ask_price_quote_numeric[7];  /* bytes 0 to 6 */
  uint8_t ask_price_fraction_indicator;    /* byte 7 */
} AskPriceQuoteNumericNegativeWholePair;

/* any Ask Price Quote Numeric Negative Whole Pair at all: every byte one the checker chooses */
static void any_ask_price_quote_numeric_negative_whole_pair(AskPriceQuoteNumericNegativeWholePair *record) {
  for (size_t i = 0; i < 7; i++) { record->raw_ask_price_quote_numeric[i] = arbitrary(); }
  record->ask_price_fraction_indicator = arbitrary();
}

/* Ask Price Quote Numeric Negative Whole Pair to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_ask_price_quote_numeric_negative_whole_pair(const AskPriceQuoteNumericNegativeWholePair *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->raw_ask_price_quote_numeric[i]; }
  wire[at++] = record->ask_price_fraction_indicator;

  return at;
}

/* Ask Price Quote Numeric Negative Whole Pair off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_ask_price_quote_numeric_negative_whole_pair(AskPriceQuoteNumericNegativeWholePair *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { record->raw_ask_price_quote_numeric[i] = wire[at++]; }
  record->ask_price_fraction_indicator = wire[at++];

  return at;
}

/* what was read of Ask Price Quote Numeric Negative Whole Pair is what was written, byte for byte */
static void equal_ask_price_quote_numeric_negative_whole_pair(const AskPriceQuoteNumericNegativeWholePair *read, const AskPriceQuoteNumericNegativeWholePair *written) {
  for (size_t i = 0; i < 7; i++) { assert(read->raw_ask_price_quote_numeric[i] == written->raw_ask_price_quote_numeric[i]); }
  assert(read->ask_price_fraction_indicator == written->ask_price_fraction_indicator);
}

/* Ask Price Quote Numeric Negative Whole Pair: written and read back, then read and written back */
static void check_ask_price_quote_numeric_negative_whole_pair(void) {
  AskPriceQuoteNumericNegativeWholePair sent;
  AskPriceQuoteNumericNegativeWholePair got;
  uint8_t wire[8];
  uint8_t again[8];

  any_ask_price_quote_numeric_negative_whole_pair(&sent);
  assert(encode_ask_price_quote_numeric_negative_whole_pair(&sent, wire, 0) == 8);
  assert(decode_ask_price_quote_numeric_negative_whole_pair(&got, wire, 0) == 8);
  equal_ask_price_quote_numeric_negative_whole_pair(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_ask_price_quote_numeric_negative_whole_pair(&got, wire, 0) == 8);
  assert(encode_ask_price_quote_numeric_negative_whole_pair(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Ask Price Quote Numeric Negative Ten Pair: 8 bytes ---------------------- */

typedef struct {
  uint8_t raw_ask_price_quote_numeric[7];  /* bytes 0 to 6 */
  uint8_t ask_price_fraction_indicator;    /* byte 7 */
} AskPriceQuoteNumericNegativeTenPair;

/* any Ask Price Quote Numeric Negative Ten Pair at all: every byte one the checker chooses */
static void any_ask_price_quote_numeric_negative_ten_pair(AskPriceQuoteNumericNegativeTenPair *record) {
  for (size_t i = 0; i < 7; i++) { record->raw_ask_price_quote_numeric[i] = arbitrary(); }
  record->ask_price_fraction_indicator = arbitrary();
}

/* Ask Price Quote Numeric Negative Ten Pair to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_ask_price_quote_numeric_negative_ten_pair(const AskPriceQuoteNumericNegativeTenPair *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->raw_ask_price_quote_numeric[i]; }
  wire[at++] = record->ask_price_fraction_indicator;

  return at;
}

/* Ask Price Quote Numeric Negative Ten Pair off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_ask_price_quote_numeric_negative_ten_pair(AskPriceQuoteNumericNegativeTenPair *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { record->raw_ask_price_quote_numeric[i] = wire[at++]; }
  record->ask_price_fraction_indicator = wire[at++];

  return at;
}

/* what was read of Ask Price Quote Numeric Negative Ten Pair is what was written, byte for byte */
static void equal_ask_price_quote_numeric_negative_ten_pair(const AskPriceQuoteNumericNegativeTenPair *read, const AskPriceQuoteNumericNegativeTenPair *written) {
  for (size_t i = 0; i < 7; i++) { assert(read->raw_ask_price_quote_numeric[i] == written->raw_ask_price_quote_numeric[i]); }
  assert(read->ask_price_fraction_indicator == written->ask_price_fraction_indicator);
}

/* Ask Price Quote Numeric Negative Ten Pair: written and read back, then read and written back */
static void check_ask_price_quote_numeric_negative_ten_pair(void) {
  AskPriceQuoteNumericNegativeTenPair sent;
  AskPriceQuoteNumericNegativeTenPair got;
  uint8_t wire[8];
  uint8_t again[8];

  any_ask_price_quote_numeric_negative_ten_pair(&sent);
  assert(encode_ask_price_quote_numeric_negative_ten_pair(&sent, wire, 0) == 8);
  assert(decode_ask_price_quote_numeric_negative_ten_pair(&got, wire, 0) == 8);
  equal_ask_price_quote_numeric_negative_ten_pair(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_ask_price_quote_numeric_negative_ten_pair(&got, wire, 0) == 8);
  assert(encode_ask_price_quote_numeric_negative_ten_pair(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Ask Price Quote Numeric Negative Hundred Pair: 8 bytes ------------------ */

typedef struct {
  uint8_t raw_ask_price_quote_numeric[7];  /* bytes 0 to 6 */
  uint8_t ask_price_fraction_indicator;    /* byte 7 */
} AskPriceQuoteNumericNegativeHundredPair;

/* any Ask Price Quote Numeric Negative Hundred Pair at all: every byte one the checker chooses */
static void any_ask_price_quote_numeric_negative_hundred_pair(AskPriceQuoteNumericNegativeHundredPair *record) {
  for (size_t i = 0; i < 7; i++) { record->raw_ask_price_quote_numeric[i] = arbitrary(); }
  record->ask_price_fraction_indicator = arbitrary();
}

/* Ask Price Quote Numeric Negative Hundred Pair to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_ask_price_quote_numeric_negative_hundred_pair(const AskPriceQuoteNumericNegativeHundredPair *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->raw_ask_price_quote_numeric[i]; }
  wire[at++] = record->ask_price_fraction_indicator;

  return at;
}

/* Ask Price Quote Numeric Negative Hundred Pair off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_ask_price_quote_numeric_negative_hundred_pair(AskPriceQuoteNumericNegativeHundredPair *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { record->raw_ask_price_quote_numeric[i] = wire[at++]; }
  record->ask_price_fraction_indicator = wire[at++];

  return at;
}

/* what was read of Ask Price Quote Numeric Negative Hundred Pair is what was written, byte for byte */
static void equal_ask_price_quote_numeric_negative_hundred_pair(const AskPriceQuoteNumericNegativeHundredPair *read, const AskPriceQuoteNumericNegativeHundredPair *written) {
  for (size_t i = 0; i < 7; i++) { assert(read->raw_ask_price_quote_numeric[i] == written->raw_ask_price_quote_numeric[i]); }
  assert(read->ask_price_fraction_indicator == written->ask_price_fraction_indicator);
}

/* Ask Price Quote Numeric Negative Hundred Pair: written and read back, then read and written back */
static void check_ask_price_quote_numeric_negative_hundred_pair(void) {
  AskPriceQuoteNumericNegativeHundredPair sent;
  AskPriceQuoteNumericNegativeHundredPair got;
  uint8_t wire[8];
  uint8_t again[8];

  any_ask_price_quote_numeric_negative_hundred_pair(&sent);
  assert(encode_ask_price_quote_numeric_negative_hundred_pair(&sent, wire, 0) == 8);
  assert(decode_ask_price_quote_numeric_negative_hundred_pair(&got, wire, 0) == 8);
  equal_ask_price_quote_numeric_negative_hundred_pair(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_ask_price_quote_numeric_negative_hundred_pair(&got, wire, 0) == 8);
  assert(encode_ask_price_quote_numeric_negative_hundred_pair(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Ask Price Quote Numeric Negative Thousand Pair: 8 bytes ----------------- */

typedef struct {
  uint8_t raw_ask_price_quote_numeric[7];  /* bytes 0 to 6 */
  uint8_t ask_price_fraction_indicator;    /* byte 7 */
} AskPriceQuoteNumericNegativeThousandPair;

/* any Ask Price Quote Numeric Negative Thousand Pair at all: every byte one the checker chooses */
static void any_ask_price_quote_numeric_negative_thousand_pair(AskPriceQuoteNumericNegativeThousandPair *record) {
  for (size_t i = 0; i < 7; i++) { record->raw_ask_price_quote_numeric[i] = arbitrary(); }
  record->ask_price_fraction_indicator = arbitrary();
}

/* Ask Price Quote Numeric Negative Thousand Pair to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_ask_price_quote_numeric_negative_thousand_pair(const AskPriceQuoteNumericNegativeThousandPair *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->raw_ask_price_quote_numeric[i]; }
  wire[at++] = record->ask_price_fraction_indicator;

  return at;
}

/* Ask Price Quote Numeric Negative Thousand Pair off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_ask_price_quote_numeric_negative_thousand_pair(AskPriceQuoteNumericNegativeThousandPair *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { record->raw_ask_price_quote_numeric[i] = wire[at++]; }
  record->ask_price_fraction_indicator = wire[at++];

  return at;
}

/* what was read of Ask Price Quote Numeric Negative Thousand Pair is what was written, byte for byte */
static void equal_ask_price_quote_numeric_negative_thousand_pair(const AskPriceQuoteNumericNegativeThousandPair *read, const AskPriceQuoteNumericNegativeThousandPair *written) {
  for (size_t i = 0; i < 7; i++) { assert(read->raw_ask_price_quote_numeric[i] == written->raw_ask_price_quote_numeric[i]); }
  assert(read->ask_price_fraction_indicator == written->ask_price_fraction_indicator);
}

/* Ask Price Quote Numeric Negative Thousand Pair: written and read back, then read and written back */
static void check_ask_price_quote_numeric_negative_thousand_pair(void) {
  AskPriceQuoteNumericNegativeThousandPair sent;
  AskPriceQuoteNumericNegativeThousandPair got;
  uint8_t wire[8];
  uint8_t again[8];

  any_ask_price_quote_numeric_negative_thousand_pair(&sent);
  assert(encode_ask_price_quote_numeric_negative_thousand_pair(&sent, wire, 0) == 8);
  assert(decode_ask_price_quote_numeric_negative_thousand_pair(&got, wire, 0) == 8);
  equal_ask_price_quote_numeric_negative_thousand_pair(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_ask_price_quote_numeric_negative_thousand_pair(&got, wire, 0) == 8);
  assert(encode_ask_price_quote_numeric_negative_thousand_pair(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Ask Price Quote Numeric Negative Ten Thousand Pair: 8 bytes ------------- */

typedef struct {
  uint8_t raw_ask_price_quote_numeric[7];  /* bytes 0 to 6 */
  uint8_t ask_price_fraction_indicator;    /* byte 7 */
} AskPriceQuoteNumericNegativeTenThousandPair;

/* any Ask Price Quote Numeric Negative Ten Thousand Pair at all: every byte one the checker chooses */
static void any_ask_price_quote_numeric_negative_ten_thousand_pair(AskPriceQuoteNumericNegativeTenThousandPair *record) {
  for (size_t i = 0; i < 7; i++) { record->raw_ask_price_quote_numeric[i] = arbitrary(); }
  record->ask_price_fraction_indicator = arbitrary();
}

/* Ask Price Quote Numeric Negative Ten Thousand Pair to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_ask_price_quote_numeric_negative_ten_thousand_pair(const AskPriceQuoteNumericNegativeTenThousandPair *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->raw_ask_price_quote_numeric[i]; }
  wire[at++] = record->ask_price_fraction_indicator;

  return at;
}

/* Ask Price Quote Numeric Negative Ten Thousand Pair off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_ask_price_quote_numeric_negative_ten_thousand_pair(AskPriceQuoteNumericNegativeTenThousandPair *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { record->raw_ask_price_quote_numeric[i] = wire[at++]; }
  record->ask_price_fraction_indicator = wire[at++];

  return at;
}

/* what was read of Ask Price Quote Numeric Negative Ten Thousand Pair is what was written, byte for byte */
static void equal_ask_price_quote_numeric_negative_ten_thousand_pair(const AskPriceQuoteNumericNegativeTenThousandPair *read, const AskPriceQuoteNumericNegativeTenThousandPair *written) {
  for (size_t i = 0; i < 7; i++) { assert(read->raw_ask_price_quote_numeric[i] == written->raw_ask_price_quote_numeric[i]); }
  assert(read->ask_price_fraction_indicator == written->ask_price_fraction_indicator);
}

/* Ask Price Quote Numeric Negative Ten Thousand Pair: written and read back, then read and written back */
static void check_ask_price_quote_numeric_negative_ten_thousand_pair(void) {
  AskPriceQuoteNumericNegativeTenThousandPair sent;
  AskPriceQuoteNumericNegativeTenThousandPair got;
  uint8_t wire[8];
  uint8_t again[8];

  any_ask_price_quote_numeric_negative_ten_thousand_pair(&sent);
  assert(encode_ask_price_quote_numeric_negative_ten_thousand_pair(&sent, wire, 0) == 8);
  assert(decode_ask_price_quote_numeric_negative_ten_thousand_pair(&got, wire, 0) == 8);
  equal_ask_price_quote_numeric_negative_ten_thousand_pair(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_ask_price_quote_numeric_negative_ten_thousand_pair(&got, wire, 0) == 8);
  assert(encode_ask_price_quote_numeric_negative_ten_thousand_pair(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Ask Price Quote Numeric Negative Hundred Thousand Pair: 8 bytes --------- */

typedef struct {
  uint8_t raw_ask_price_quote_numeric[7];  /* bytes 0 to 6 */
  uint8_t ask_price_fraction_indicator;    /* byte 7 */
} AskPriceQuoteNumericNegativeHundredThousandPair;

/* any Ask Price Quote Numeric Negative Hundred Thousand Pair at all: every byte one the checker chooses */
static void any_ask_price_quote_numeric_negative_hundred_thousand_pair(AskPriceQuoteNumericNegativeHundredThousandPair *record) {
  for (size_t i = 0; i < 7; i++) { record->raw_ask_price_quote_numeric[i] = arbitrary(); }
  record->ask_price_fraction_indicator = arbitrary();
}

/* Ask Price Quote Numeric Negative Hundred Thousand Pair to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_ask_price_quote_numeric_negative_hundred_thousand_pair(const AskPriceQuoteNumericNegativeHundredThousandPair *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->raw_ask_price_quote_numeric[i]; }
  wire[at++] = record->ask_price_fraction_indicator;

  return at;
}

/* Ask Price Quote Numeric Negative Hundred Thousand Pair off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_ask_price_quote_numeric_negative_hundred_thousand_pair(AskPriceQuoteNumericNegativeHundredThousandPair *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { record->raw_ask_price_quote_numeric[i] = wire[at++]; }
  record->ask_price_fraction_indicator = wire[at++];

  return at;
}

/* what was read of Ask Price Quote Numeric Negative Hundred Thousand Pair is what was written, byte for byte */
static void equal_ask_price_quote_numeric_negative_hundred_thousand_pair(const AskPriceQuoteNumericNegativeHundredThousandPair *read, const AskPriceQuoteNumericNegativeHundredThousandPair *written) {
  for (size_t i = 0; i < 7; i++) { assert(read->raw_ask_price_quote_numeric[i] == written->raw_ask_price_quote_numeric[i]); }
  assert(read->ask_price_fraction_indicator == written->ask_price_fraction_indicator);
}

/* Ask Price Quote Numeric Negative Hundred Thousand Pair: written and read back, then read and written back */
static void check_ask_price_quote_numeric_negative_hundred_thousand_pair(void) {
  AskPriceQuoteNumericNegativeHundredThousandPair sent;
  AskPriceQuoteNumericNegativeHundredThousandPair got;
  uint8_t wire[8];
  uint8_t again[8];

  any_ask_price_quote_numeric_negative_hundred_thousand_pair(&sent);
  assert(encode_ask_price_quote_numeric_negative_hundred_thousand_pair(&sent, wire, 0) == 8);
  assert(decode_ask_price_quote_numeric_negative_hundred_thousand_pair(&got, wire, 0) == 8);
  equal_ask_price_quote_numeric_negative_hundred_thousand_pair(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_ask_price_quote_numeric_negative_hundred_thousand_pair(&got, wire, 0) == 8);
  assert(encode_ask_price_quote_numeric_negative_hundred_thousand_pair(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Ask Price Quote Numeric Negative Million Pair: 8 bytes ------------------ */

typedef struct {
  uint8_t raw_ask_price_quote_numeric[7];  /* bytes 0 to 6 */
  uint8_t ask_price_fraction_indicator;    /* byte 7 */
} AskPriceQuoteNumericNegativeMillionPair;

/* any Ask Price Quote Numeric Negative Million Pair at all: every byte one the checker chooses */
static void any_ask_price_quote_numeric_negative_million_pair(AskPriceQuoteNumericNegativeMillionPair *record) {
  for (size_t i = 0; i < 7; i++) { record->raw_ask_price_quote_numeric[i] = arbitrary(); }
  record->ask_price_fraction_indicator = arbitrary();
}

/* Ask Price Quote Numeric Negative Million Pair to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_ask_price_quote_numeric_negative_million_pair(const AskPriceQuoteNumericNegativeMillionPair *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->raw_ask_price_quote_numeric[i]; }
  wire[at++] = record->ask_price_fraction_indicator;

  return at;
}

/* Ask Price Quote Numeric Negative Million Pair off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_ask_price_quote_numeric_negative_million_pair(AskPriceQuoteNumericNegativeMillionPair *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { record->raw_ask_price_quote_numeric[i] = wire[at++]; }
  record->ask_price_fraction_indicator = wire[at++];

  return at;
}

/* what was read of Ask Price Quote Numeric Negative Million Pair is what was written, byte for byte */
static void equal_ask_price_quote_numeric_negative_million_pair(const AskPriceQuoteNumericNegativeMillionPair *read, const AskPriceQuoteNumericNegativeMillionPair *written) {
  for (size_t i = 0; i < 7; i++) { assert(read->raw_ask_price_quote_numeric[i] == written->raw_ask_price_quote_numeric[i]); }
  assert(read->ask_price_fraction_indicator == written->ask_price_fraction_indicator);
}

/* Ask Price Quote Numeric Negative Million Pair: written and read back, then read and written back */
static void check_ask_price_quote_numeric_negative_million_pair(void) {
  AskPriceQuoteNumericNegativeMillionPair sent;
  AskPriceQuoteNumericNegativeMillionPair got;
  uint8_t wire[8];
  uint8_t again[8];

  any_ask_price_quote_numeric_negative_million_pair(&sent);
  assert(encode_ask_price_quote_numeric_negative_million_pair(&sent, wire, 0) == 8);
  assert(decode_ask_price_quote_numeric_negative_million_pair(&got, wire, 0) == 8);
  equal_ask_price_quote_numeric_negative_million_pair(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_ask_price_quote_numeric_negative_million_pair(&got, wire, 0) == 8);
  assert(encode_ask_price_quote_numeric_negative_million_pair(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Ask Price Quote Numeric Pair: 8 bytes ----------------------------------- */

typedef struct {
  uint8_t ask_price_quote_numeric[7];    /* bytes 0 to 6 */
  uint8_t ask_price_fraction_indicator;  /* byte 7 */
} AskPriceQuoteNumericPair;

/* any Ask Price Quote Numeric Pair at all: every byte one the checker chooses */
static void any_ask_price_quote_numeric_pair(AskPriceQuoteNumericPair *record) {
  for (size_t i = 0; i < 7; i++) { record->ask_price_quote_numeric[i] = arbitrary(); }
  record->ask_price_fraction_indicator = arbitrary();
}

/* Ask Price Quote Numeric Pair to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_ask_price_quote_numeric_pair(const AskPriceQuoteNumericPair *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->ask_price_quote_numeric[i]; }
  wire[at++] = record->ask_price_fraction_indicator;

  return at;
}

/* Ask Price Quote Numeric Pair off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_ask_price_quote_numeric_pair(AskPriceQuoteNumericPair *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { record->ask_price_quote_numeric[i] = wire[at++]; }
  record->ask_price_fraction_indicator = wire[at++];

  return at;
}

/* what was read of Ask Price Quote Numeric Pair is what was written, byte for byte */
static void equal_ask_price_quote_numeric_pair(const AskPriceQuoteNumericPair *read, const AskPriceQuoteNumericPair *written) {
  for (size_t i = 0; i < 7; i++) { assert(read->ask_price_quote_numeric[i] == written->ask_price_quote_numeric[i]); }
  assert(read->ask_price_fraction_indicator == written->ask_price_fraction_indicator);
}

/* Ask Price Quote Numeric Pair: written and read back, then read and written back */
static void check_ask_price_quote_numeric_pair(void) {
  AskPriceQuoteNumericPair sent;
  AskPriceQuoteNumericPair got;
  uint8_t wire[8];
  uint8_t again[8];

  any_ask_price_quote_numeric_pair(&sent);
  assert(encode_ask_price_quote_numeric_pair(&sent, wire, 0) == 8);
  assert(decode_ask_price_quote_numeric_pair(&got, wire, 0) == 8);
  equal_ask_price_quote_numeric_pair(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_ask_price_quote_numeric_pair(&got, wire, 0) == 8);
  assert(encode_ask_price_quote_numeric_pair(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Ask Price Futures Depth Market Depth Level HF Opening Pair: 8 bytes ----- */

typedef struct {
  uint8_t ask_price_futures_depth_opening[7];  /* bytes 0 to 6 */
  uint8_t ask_price_fraction_indicator;        /* byte 7 */
} AskPriceFuturesDepthMarketDepthLevelHFOpeningPair;

/* any Ask Price Futures Depth Market Depth Level HF Opening Pair at all: every byte one the checker chooses */
static void any_ask_price_futures_depth_market_depth_level_h_f_opening_pair(AskPriceFuturesDepthMarketDepthLevelHFOpeningPair *record) {
  for (size_t i = 0; i < 7; i++) { record->ask_price_futures_depth_opening[i] = arbitrary(); }
  record->ask_price_fraction_indicator = arbitrary();
}

/* Ask Price Futures Depth Market Depth Level HF Opening Pair to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_ask_price_futures_depth_market_depth_level_h_f_opening_pair(const AskPriceFuturesDepthMarketDepthLevelHFOpeningPair *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->ask_price_futures_depth_opening[i]; }
  wire[at++] = record->ask_price_fraction_indicator;

  return at;
}

/* Ask Price Futures Depth Market Depth Level HF Opening Pair off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_ask_price_futures_depth_market_depth_level_h_f_opening_pair(AskPriceFuturesDepthMarketDepthLevelHFOpeningPair *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { record->ask_price_futures_depth_opening[i] = wire[at++]; }
  record->ask_price_fraction_indicator = wire[at++];

  return at;
}

/* what was read of Ask Price Futures Depth Market Depth Level HF Opening Pair is what was written, byte for byte */
static void equal_ask_price_futures_depth_market_depth_level_h_f_opening_pair(const AskPriceFuturesDepthMarketDepthLevelHFOpeningPair *read, const AskPriceFuturesDepthMarketDepthLevelHFOpeningPair *written) {
  for (size_t i = 0; i < 7; i++) { assert(read->ask_price_futures_depth_opening[i] == written->ask_price_futures_depth_opening[i]); }
  assert(read->ask_price_fraction_indicator == written->ask_price_fraction_indicator);
}

/* Ask Price Futures Depth Market Depth Level HF Opening Pair: written and read back, then read and written back */
static void check_ask_price_futures_depth_market_depth_level_h_f_opening_pair(void) {
  AskPriceFuturesDepthMarketDepthLevelHFOpeningPair sent;
  AskPriceFuturesDepthMarketDepthLevelHFOpeningPair got;
  uint8_t wire[8];
  uint8_t again[8];

  any_ask_price_futures_depth_market_depth_level_h_f_opening_pair(&sent);
  assert(encode_ask_price_futures_depth_market_depth_level_h_f_opening_pair(&sent, wire, 0) == 8);
  assert(decode_ask_price_futures_depth_market_depth_level_h_f_opening_pair(&got, wire, 0) == 8);
  equal_ask_price_futures_depth_market_depth_level_h_f_opening_pair(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_ask_price_futures_depth_market_depth_level_h_f_opening_pair(&got, wire, 0) == 8);
  assert(encode_ask_price_futures_depth_market_depth_level_h_f_opening_pair(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Ask Price Futures Depth Numeric Negative Whole Pair: 8 bytes ------------ */

typedef struct {
  uint8_t raw_ask_price_futures_depth_numeric[7];  /* bytes 0 to 6 */
  uint8_t ask_price_fraction_indicator;            /* byte 7 */
} AskPriceFuturesDepthNumericNegativeWholePair;

/* any Ask Price Futures Depth Numeric Negative Whole Pair at all: every byte one the checker chooses */
static void any_ask_price_futures_depth_numeric_negative_whole_pair(AskPriceFuturesDepthNumericNegativeWholePair *record) {
  for (size_t i = 0; i < 7; i++) { record->raw_ask_price_futures_depth_numeric[i] = arbitrary(); }
  record->ask_price_fraction_indicator = arbitrary();
}

/* Ask Price Futures Depth Numeric Negative Whole Pair to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_ask_price_futures_depth_numeric_negative_whole_pair(const AskPriceFuturesDepthNumericNegativeWholePair *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->raw_ask_price_futures_depth_numeric[i]; }
  wire[at++] = record->ask_price_fraction_indicator;

  return at;
}

/* Ask Price Futures Depth Numeric Negative Whole Pair off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_ask_price_futures_depth_numeric_negative_whole_pair(AskPriceFuturesDepthNumericNegativeWholePair *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { record->raw_ask_price_futures_depth_numeric[i] = wire[at++]; }
  record->ask_price_fraction_indicator = wire[at++];

  return at;
}

/* what was read of Ask Price Futures Depth Numeric Negative Whole Pair is what was written, byte for byte */
static void equal_ask_price_futures_depth_numeric_negative_whole_pair(const AskPriceFuturesDepthNumericNegativeWholePair *read, const AskPriceFuturesDepthNumericNegativeWholePair *written) {
  for (size_t i = 0; i < 7; i++) { assert(read->raw_ask_price_futures_depth_numeric[i] == written->raw_ask_price_futures_depth_numeric[i]); }
  assert(read->ask_price_fraction_indicator == written->ask_price_fraction_indicator);
}

/* Ask Price Futures Depth Numeric Negative Whole Pair: written and read back, then read and written back */
static void check_ask_price_futures_depth_numeric_negative_whole_pair(void) {
  AskPriceFuturesDepthNumericNegativeWholePair sent;
  AskPriceFuturesDepthNumericNegativeWholePair got;
  uint8_t wire[8];
  uint8_t again[8];

  any_ask_price_futures_depth_numeric_negative_whole_pair(&sent);
  assert(encode_ask_price_futures_depth_numeric_negative_whole_pair(&sent, wire, 0) == 8);
  assert(decode_ask_price_futures_depth_numeric_negative_whole_pair(&got, wire, 0) == 8);
  equal_ask_price_futures_depth_numeric_negative_whole_pair(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_ask_price_futures_depth_numeric_negative_whole_pair(&got, wire, 0) == 8);
  assert(encode_ask_price_futures_depth_numeric_negative_whole_pair(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Ask Price Futures Depth Numeric Negative Ten Pair: 8 bytes -------------- */

typedef struct {
  uint8_t raw_ask_price_futures_depth_numeric[7];  /* bytes 0 to 6 */
  uint8_t ask_price_fraction_indicator;            /* byte 7 */
} AskPriceFuturesDepthNumericNegativeTenPair;

/* any Ask Price Futures Depth Numeric Negative Ten Pair at all: every byte one the checker chooses */
static void any_ask_price_futures_depth_numeric_negative_ten_pair(AskPriceFuturesDepthNumericNegativeTenPair *record) {
  for (size_t i = 0; i < 7; i++) { record->raw_ask_price_futures_depth_numeric[i] = arbitrary(); }
  record->ask_price_fraction_indicator = arbitrary();
}

/* Ask Price Futures Depth Numeric Negative Ten Pair to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_ask_price_futures_depth_numeric_negative_ten_pair(const AskPriceFuturesDepthNumericNegativeTenPair *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->raw_ask_price_futures_depth_numeric[i]; }
  wire[at++] = record->ask_price_fraction_indicator;

  return at;
}

/* Ask Price Futures Depth Numeric Negative Ten Pair off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_ask_price_futures_depth_numeric_negative_ten_pair(AskPriceFuturesDepthNumericNegativeTenPair *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { record->raw_ask_price_futures_depth_numeric[i] = wire[at++]; }
  record->ask_price_fraction_indicator = wire[at++];

  return at;
}

/* what was read of Ask Price Futures Depth Numeric Negative Ten Pair is what was written, byte for byte */
static void equal_ask_price_futures_depth_numeric_negative_ten_pair(const AskPriceFuturesDepthNumericNegativeTenPair *read, const AskPriceFuturesDepthNumericNegativeTenPair *written) {
  for (size_t i = 0; i < 7; i++) { assert(read->raw_ask_price_futures_depth_numeric[i] == written->raw_ask_price_futures_depth_numeric[i]); }
  assert(read->ask_price_fraction_indicator == written->ask_price_fraction_indicator);
}

/* Ask Price Futures Depth Numeric Negative Ten Pair: written and read back, then read and written back */
static void check_ask_price_futures_depth_numeric_negative_ten_pair(void) {
  AskPriceFuturesDepthNumericNegativeTenPair sent;
  AskPriceFuturesDepthNumericNegativeTenPair got;
  uint8_t wire[8];
  uint8_t again[8];

  any_ask_price_futures_depth_numeric_negative_ten_pair(&sent);
  assert(encode_ask_price_futures_depth_numeric_negative_ten_pair(&sent, wire, 0) == 8);
  assert(decode_ask_price_futures_depth_numeric_negative_ten_pair(&got, wire, 0) == 8);
  equal_ask_price_futures_depth_numeric_negative_ten_pair(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_ask_price_futures_depth_numeric_negative_ten_pair(&got, wire, 0) == 8);
  assert(encode_ask_price_futures_depth_numeric_negative_ten_pair(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Ask Price Futures Depth Numeric Negative Hundred Pair: 8 bytes ---------- */

typedef struct {
  uint8_t raw_ask_price_futures_depth_numeric[7];  /* bytes 0 to 6 */
  uint8_t ask_price_fraction_indicator;            /* byte 7 */
} AskPriceFuturesDepthNumericNegativeHundredPair;

/* any Ask Price Futures Depth Numeric Negative Hundred Pair at all: every byte one the checker chooses */
static void any_ask_price_futures_depth_numeric_negative_hundred_pair(AskPriceFuturesDepthNumericNegativeHundredPair *record) {
  for (size_t i = 0; i < 7; i++) { record->raw_ask_price_futures_depth_numeric[i] = arbitrary(); }
  record->ask_price_fraction_indicator = arbitrary();
}

/* Ask Price Futures Depth Numeric Negative Hundred Pair to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_ask_price_futures_depth_numeric_negative_hundred_pair(const AskPriceFuturesDepthNumericNegativeHundredPair *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->raw_ask_price_futures_depth_numeric[i]; }
  wire[at++] = record->ask_price_fraction_indicator;

  return at;
}

/* Ask Price Futures Depth Numeric Negative Hundred Pair off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_ask_price_futures_depth_numeric_negative_hundred_pair(AskPriceFuturesDepthNumericNegativeHundredPair *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { record->raw_ask_price_futures_depth_numeric[i] = wire[at++]; }
  record->ask_price_fraction_indicator = wire[at++];

  return at;
}

/* what was read of Ask Price Futures Depth Numeric Negative Hundred Pair is what was written, byte for byte */
static void equal_ask_price_futures_depth_numeric_negative_hundred_pair(const AskPriceFuturesDepthNumericNegativeHundredPair *read, const AskPriceFuturesDepthNumericNegativeHundredPair *written) {
  for (size_t i = 0; i < 7; i++) { assert(read->raw_ask_price_futures_depth_numeric[i] == written->raw_ask_price_futures_depth_numeric[i]); }
  assert(read->ask_price_fraction_indicator == written->ask_price_fraction_indicator);
}

/* Ask Price Futures Depth Numeric Negative Hundred Pair: written and read back, then read and written back */
static void check_ask_price_futures_depth_numeric_negative_hundred_pair(void) {
  AskPriceFuturesDepthNumericNegativeHundredPair sent;
  AskPriceFuturesDepthNumericNegativeHundredPair got;
  uint8_t wire[8];
  uint8_t again[8];

  any_ask_price_futures_depth_numeric_negative_hundred_pair(&sent);
  assert(encode_ask_price_futures_depth_numeric_negative_hundred_pair(&sent, wire, 0) == 8);
  assert(decode_ask_price_futures_depth_numeric_negative_hundred_pair(&got, wire, 0) == 8);
  equal_ask_price_futures_depth_numeric_negative_hundred_pair(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_ask_price_futures_depth_numeric_negative_hundred_pair(&got, wire, 0) == 8);
  assert(encode_ask_price_futures_depth_numeric_negative_hundred_pair(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Ask Price Futures Depth Numeric Negative Thousand Pair: 8 bytes --------- */

typedef struct {
  uint8_t raw_ask_price_futures_depth_numeric[7];  /* bytes 0 to 6 */
  uint8_t ask_price_fraction_indicator;            /* byte 7 */
} AskPriceFuturesDepthNumericNegativeThousandPair;

/* any Ask Price Futures Depth Numeric Negative Thousand Pair at all: every byte one the checker chooses */
static void any_ask_price_futures_depth_numeric_negative_thousand_pair(AskPriceFuturesDepthNumericNegativeThousandPair *record) {
  for (size_t i = 0; i < 7; i++) { record->raw_ask_price_futures_depth_numeric[i] = arbitrary(); }
  record->ask_price_fraction_indicator = arbitrary();
}

/* Ask Price Futures Depth Numeric Negative Thousand Pair to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_ask_price_futures_depth_numeric_negative_thousand_pair(const AskPriceFuturesDepthNumericNegativeThousandPair *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->raw_ask_price_futures_depth_numeric[i]; }
  wire[at++] = record->ask_price_fraction_indicator;

  return at;
}

/* Ask Price Futures Depth Numeric Negative Thousand Pair off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_ask_price_futures_depth_numeric_negative_thousand_pair(AskPriceFuturesDepthNumericNegativeThousandPair *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { record->raw_ask_price_futures_depth_numeric[i] = wire[at++]; }
  record->ask_price_fraction_indicator = wire[at++];

  return at;
}

/* what was read of Ask Price Futures Depth Numeric Negative Thousand Pair is what was written, byte for byte */
static void equal_ask_price_futures_depth_numeric_negative_thousand_pair(const AskPriceFuturesDepthNumericNegativeThousandPair *read, const AskPriceFuturesDepthNumericNegativeThousandPair *written) {
  for (size_t i = 0; i < 7; i++) { assert(read->raw_ask_price_futures_depth_numeric[i] == written->raw_ask_price_futures_depth_numeric[i]); }
  assert(read->ask_price_fraction_indicator == written->ask_price_fraction_indicator);
}

/* Ask Price Futures Depth Numeric Negative Thousand Pair: written and read back, then read and written back */
static void check_ask_price_futures_depth_numeric_negative_thousand_pair(void) {
  AskPriceFuturesDepthNumericNegativeThousandPair sent;
  AskPriceFuturesDepthNumericNegativeThousandPair got;
  uint8_t wire[8];
  uint8_t again[8];

  any_ask_price_futures_depth_numeric_negative_thousand_pair(&sent);
  assert(encode_ask_price_futures_depth_numeric_negative_thousand_pair(&sent, wire, 0) == 8);
  assert(decode_ask_price_futures_depth_numeric_negative_thousand_pair(&got, wire, 0) == 8);
  equal_ask_price_futures_depth_numeric_negative_thousand_pair(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_ask_price_futures_depth_numeric_negative_thousand_pair(&got, wire, 0) == 8);
  assert(encode_ask_price_futures_depth_numeric_negative_thousand_pair(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Ask Price Futures Depth Numeric Negative Ten Thousand Pair: 8 bytes ----- */

typedef struct {
  uint8_t raw_ask_price_futures_depth_numeric[7];  /* bytes 0 to 6 */
  uint8_t ask_price_fraction_indicator;            /* byte 7 */
} AskPriceFuturesDepthNumericNegativeTenThousandPair;

/* any Ask Price Futures Depth Numeric Negative Ten Thousand Pair at all: every byte one the checker chooses */
static void any_ask_price_futures_depth_numeric_negative_ten_thousand_pair(AskPriceFuturesDepthNumericNegativeTenThousandPair *record) {
  for (size_t i = 0; i < 7; i++) { record->raw_ask_price_futures_depth_numeric[i] = arbitrary(); }
  record->ask_price_fraction_indicator = arbitrary();
}

/* Ask Price Futures Depth Numeric Negative Ten Thousand Pair to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_ask_price_futures_depth_numeric_negative_ten_thousand_pair(const AskPriceFuturesDepthNumericNegativeTenThousandPair *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->raw_ask_price_futures_depth_numeric[i]; }
  wire[at++] = record->ask_price_fraction_indicator;

  return at;
}

/* Ask Price Futures Depth Numeric Negative Ten Thousand Pair off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_ask_price_futures_depth_numeric_negative_ten_thousand_pair(AskPriceFuturesDepthNumericNegativeTenThousandPair *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { record->raw_ask_price_futures_depth_numeric[i] = wire[at++]; }
  record->ask_price_fraction_indicator = wire[at++];

  return at;
}

/* what was read of Ask Price Futures Depth Numeric Negative Ten Thousand Pair is what was written, byte for byte */
static void equal_ask_price_futures_depth_numeric_negative_ten_thousand_pair(const AskPriceFuturesDepthNumericNegativeTenThousandPair *read, const AskPriceFuturesDepthNumericNegativeTenThousandPair *written) {
  for (size_t i = 0; i < 7; i++) { assert(read->raw_ask_price_futures_depth_numeric[i] == written->raw_ask_price_futures_depth_numeric[i]); }
  assert(read->ask_price_fraction_indicator == written->ask_price_fraction_indicator);
}

/* Ask Price Futures Depth Numeric Negative Ten Thousand Pair: written and read back, then read and written back */
static void check_ask_price_futures_depth_numeric_negative_ten_thousand_pair(void) {
  AskPriceFuturesDepthNumericNegativeTenThousandPair sent;
  AskPriceFuturesDepthNumericNegativeTenThousandPair got;
  uint8_t wire[8];
  uint8_t again[8];

  any_ask_price_futures_depth_numeric_negative_ten_thousand_pair(&sent);
  assert(encode_ask_price_futures_depth_numeric_negative_ten_thousand_pair(&sent, wire, 0) == 8);
  assert(decode_ask_price_futures_depth_numeric_negative_ten_thousand_pair(&got, wire, 0) == 8);
  equal_ask_price_futures_depth_numeric_negative_ten_thousand_pair(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_ask_price_futures_depth_numeric_negative_ten_thousand_pair(&got, wire, 0) == 8);
  assert(encode_ask_price_futures_depth_numeric_negative_ten_thousand_pair(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Ask Price Futures Depth Numeric Negative Hundred Thousand Pair: 8 bytes ---- */

typedef struct {
  uint8_t raw_ask_price_futures_depth_numeric[7];  /* bytes 0 to 6 */
  uint8_t ask_price_fraction_indicator;            /* byte 7 */
} AskPriceFuturesDepthNumericNegativeHundredThousandPair;

/* any Ask Price Futures Depth Numeric Negative Hundred Thousand Pair at all: every byte one the checker chooses */
static void any_ask_price_futures_depth_numeric_negative_hundred_thousand_pair(AskPriceFuturesDepthNumericNegativeHundredThousandPair *record) {
  for (size_t i = 0; i < 7; i++) { record->raw_ask_price_futures_depth_numeric[i] = arbitrary(); }
  record->ask_price_fraction_indicator = arbitrary();
}

/* Ask Price Futures Depth Numeric Negative Hundred Thousand Pair to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_ask_price_futures_depth_numeric_negative_hundred_thousand_pair(const AskPriceFuturesDepthNumericNegativeHundredThousandPair *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->raw_ask_price_futures_depth_numeric[i]; }
  wire[at++] = record->ask_price_fraction_indicator;

  return at;
}

/* Ask Price Futures Depth Numeric Negative Hundred Thousand Pair off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_ask_price_futures_depth_numeric_negative_hundred_thousand_pair(AskPriceFuturesDepthNumericNegativeHundredThousandPair *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { record->raw_ask_price_futures_depth_numeric[i] = wire[at++]; }
  record->ask_price_fraction_indicator = wire[at++];

  return at;
}

/* what was read of Ask Price Futures Depth Numeric Negative Hundred Thousand Pair is what was written, byte for byte */
static void equal_ask_price_futures_depth_numeric_negative_hundred_thousand_pair(const AskPriceFuturesDepthNumericNegativeHundredThousandPair *read, const AskPriceFuturesDepthNumericNegativeHundredThousandPair *written) {
  for (size_t i = 0; i < 7; i++) { assert(read->raw_ask_price_futures_depth_numeric[i] == written->raw_ask_price_futures_depth_numeric[i]); }
  assert(read->ask_price_fraction_indicator == written->ask_price_fraction_indicator);
}

/* Ask Price Futures Depth Numeric Negative Hundred Thousand Pair: written and read back, then read and written back */
static void check_ask_price_futures_depth_numeric_negative_hundred_thousand_pair(void) {
  AskPriceFuturesDepthNumericNegativeHundredThousandPair sent;
  AskPriceFuturesDepthNumericNegativeHundredThousandPair got;
  uint8_t wire[8];
  uint8_t again[8];

  any_ask_price_futures_depth_numeric_negative_hundred_thousand_pair(&sent);
  assert(encode_ask_price_futures_depth_numeric_negative_hundred_thousand_pair(&sent, wire, 0) == 8);
  assert(decode_ask_price_futures_depth_numeric_negative_hundred_thousand_pair(&got, wire, 0) == 8);
  equal_ask_price_futures_depth_numeric_negative_hundred_thousand_pair(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_ask_price_futures_depth_numeric_negative_hundred_thousand_pair(&got, wire, 0) == 8);
  assert(encode_ask_price_futures_depth_numeric_negative_hundred_thousand_pair(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Ask Price Futures Depth Numeric Negative Million Pair: 8 bytes ---------- */

typedef struct {
  uint8_t raw_ask_price_futures_depth_numeric[7];  /* bytes 0 to 6 */
  uint8_t ask_price_fraction_indicator;            /* byte 7 */
} AskPriceFuturesDepthNumericNegativeMillionPair;

/* any Ask Price Futures Depth Numeric Negative Million Pair at all: every byte one the checker chooses */
static void any_ask_price_futures_depth_numeric_negative_million_pair(AskPriceFuturesDepthNumericNegativeMillionPair *record) {
  for (size_t i = 0; i < 7; i++) { record->raw_ask_price_futures_depth_numeric[i] = arbitrary(); }
  record->ask_price_fraction_indicator = arbitrary();
}

/* Ask Price Futures Depth Numeric Negative Million Pair to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_ask_price_futures_depth_numeric_negative_million_pair(const AskPriceFuturesDepthNumericNegativeMillionPair *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->raw_ask_price_futures_depth_numeric[i]; }
  wire[at++] = record->ask_price_fraction_indicator;

  return at;
}

/* Ask Price Futures Depth Numeric Negative Million Pair off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_ask_price_futures_depth_numeric_negative_million_pair(AskPriceFuturesDepthNumericNegativeMillionPair *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { record->raw_ask_price_futures_depth_numeric[i] = wire[at++]; }
  record->ask_price_fraction_indicator = wire[at++];

  return at;
}

/* what was read of Ask Price Futures Depth Numeric Negative Million Pair is what was written, byte for byte */
static void equal_ask_price_futures_depth_numeric_negative_million_pair(const AskPriceFuturesDepthNumericNegativeMillionPair *read, const AskPriceFuturesDepthNumericNegativeMillionPair *written) {
  for (size_t i = 0; i < 7; i++) { assert(read->raw_ask_price_futures_depth_numeric[i] == written->raw_ask_price_futures_depth_numeric[i]); }
  assert(read->ask_price_fraction_indicator == written->ask_price_fraction_indicator);
}

/* Ask Price Futures Depth Numeric Negative Million Pair: written and read back, then read and written back */
static void check_ask_price_futures_depth_numeric_negative_million_pair(void) {
  AskPriceFuturesDepthNumericNegativeMillionPair sent;
  AskPriceFuturesDepthNumericNegativeMillionPair got;
  uint8_t wire[8];
  uint8_t again[8];

  any_ask_price_futures_depth_numeric_negative_million_pair(&sent);
  assert(encode_ask_price_futures_depth_numeric_negative_million_pair(&sent, wire, 0) == 8);
  assert(decode_ask_price_futures_depth_numeric_negative_million_pair(&got, wire, 0) == 8);
  equal_ask_price_futures_depth_numeric_negative_million_pair(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_ask_price_futures_depth_numeric_negative_million_pair(&got, wire, 0) == 8);
  assert(encode_ask_price_futures_depth_numeric_negative_million_pair(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Ask Price Futures Depth Market Depth Level HF Numeric Pair: 8 bytes ----- */

typedef struct {
  uint8_t ask_price_futures_depth_numeric[7];  /* bytes 0 to 6 */
  uint8_t ask_price_fraction_indicator;        /* byte 7 */
} AskPriceFuturesDepthMarketDepthLevelHFNumericPair;

/* any Ask Price Futures Depth Market Depth Level HF Numeric Pair at all: every byte one the checker chooses */
static void any_ask_price_futures_depth_market_depth_level_h_f_numeric_pair(AskPriceFuturesDepthMarketDepthLevelHFNumericPair *record) {
  for (size_t i = 0; i < 7; i++) { record->ask_price_futures_depth_numeric[i] = arbitrary(); }
  record->ask_price_fraction_indicator = arbitrary();
}

/* Ask Price Futures Depth Market Depth Level HF Numeric Pair to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_ask_price_futures_depth_market_depth_level_h_f_numeric_pair(const AskPriceFuturesDepthMarketDepthLevelHFNumericPair *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->ask_price_futures_depth_numeric[i]; }
  wire[at++] = record->ask_price_fraction_indicator;

  return at;
}

/* Ask Price Futures Depth Market Depth Level HF Numeric Pair off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_ask_price_futures_depth_market_depth_level_h_f_numeric_pair(AskPriceFuturesDepthMarketDepthLevelHFNumericPair *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { record->ask_price_futures_depth_numeric[i] = wire[at++]; }
  record->ask_price_fraction_indicator = wire[at++];

  return at;
}

/* what was read of Ask Price Futures Depth Market Depth Level HF Numeric Pair is what was written, byte for byte */
static void equal_ask_price_futures_depth_market_depth_level_h_f_numeric_pair(const AskPriceFuturesDepthMarketDepthLevelHFNumericPair *read, const AskPriceFuturesDepthMarketDepthLevelHFNumericPair *written) {
  for (size_t i = 0; i < 7; i++) { assert(read->ask_price_futures_depth_numeric[i] == written->ask_price_futures_depth_numeric[i]); }
  assert(read->ask_price_fraction_indicator == written->ask_price_fraction_indicator);
}

/* Ask Price Futures Depth Market Depth Level HF Numeric Pair: written and read back, then read and written back */
static void check_ask_price_futures_depth_market_depth_level_h_f_numeric_pair(void) {
  AskPriceFuturesDepthMarketDepthLevelHFNumericPair sent;
  AskPriceFuturesDepthMarketDepthLevelHFNumericPair got;
  uint8_t wire[8];
  uint8_t again[8];

  any_ask_price_futures_depth_market_depth_level_h_f_numeric_pair(&sent);
  assert(encode_ask_price_futures_depth_market_depth_level_h_f_numeric_pair(&sent, wire, 0) == 8);
  assert(decode_ask_price_futures_depth_market_depth_level_h_f_numeric_pair(&got, wire, 0) == 8);
  equal_ask_price_futures_depth_market_depth_level_h_f_numeric_pair(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_ask_price_futures_depth_market_depth_level_h_f_numeric_pair(&got, wire, 0) == 8);
  assert(encode_ask_price_futures_depth_market_depth_level_h_f_numeric_pair(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Price Negative Whole Pair: 8 bytes -------------------------------------- */

typedef struct {
  uint8_t raw_price[7];              /* bytes 0 to 6 */
  uint8_t price_fraction_indicator;  /* byte 7 */
} PriceNegativeWholePair;

/* any Price Negative Whole Pair at all: every byte one the checker chooses */
static void any_price_negative_whole_pair(PriceNegativeWholePair *record) {
  for (size_t i = 0; i < 7; i++) { record->raw_price[i] = arbitrary(); }
  record->price_fraction_indicator = arbitrary();
}

/* Price Negative Whole Pair to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_price_negative_whole_pair(const PriceNegativeWholePair *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->raw_price[i]; }
  wire[at++] = record->price_fraction_indicator;

  return at;
}

/* Price Negative Whole Pair off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_price_negative_whole_pair(PriceNegativeWholePair *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { record->raw_price[i] = wire[at++]; }
  record->price_fraction_indicator = wire[at++];

  return at;
}

/* what was read of Price Negative Whole Pair is what was written, byte for byte */
static void equal_price_negative_whole_pair(const PriceNegativeWholePair *read, const PriceNegativeWholePair *written) {
  for (size_t i = 0; i < 7; i++) { assert(read->raw_price[i] == written->raw_price[i]); }
  assert(read->price_fraction_indicator == written->price_fraction_indicator);
}

/* Price Negative Whole Pair: written and read back, then read and written back */
static void check_price_negative_whole_pair(void) {
  PriceNegativeWholePair sent;
  PriceNegativeWholePair got;
  uint8_t wire[8];
  uint8_t again[8];

  any_price_negative_whole_pair(&sent);
  assert(encode_price_negative_whole_pair(&sent, wire, 0) == 8);
  assert(decode_price_negative_whole_pair(&got, wire, 0) == 8);
  equal_price_negative_whole_pair(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_price_negative_whole_pair(&got, wire, 0) == 8);
  assert(encode_price_negative_whole_pair(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Price Negative Ten Pair: 8 bytes ---------------------------------------- */

typedef struct {
  uint8_t raw_price[7];              /* bytes 0 to 6 */
  uint8_t price_fraction_indicator;  /* byte 7 */
} PriceNegativeTenPair;

/* any Price Negative Ten Pair at all: every byte one the checker chooses */
static void any_price_negative_ten_pair(PriceNegativeTenPair *record) {
  for (size_t i = 0; i < 7; i++) { record->raw_price[i] = arbitrary(); }
  record->price_fraction_indicator = arbitrary();
}

/* Price Negative Ten Pair to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_price_negative_ten_pair(const PriceNegativeTenPair *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->raw_price[i]; }
  wire[at++] = record->price_fraction_indicator;

  return at;
}

/* Price Negative Ten Pair off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_price_negative_ten_pair(PriceNegativeTenPair *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { record->raw_price[i] = wire[at++]; }
  record->price_fraction_indicator = wire[at++];

  return at;
}

/* what was read of Price Negative Ten Pair is what was written, byte for byte */
static void equal_price_negative_ten_pair(const PriceNegativeTenPair *read, const PriceNegativeTenPair *written) {
  for (size_t i = 0; i < 7; i++) { assert(read->raw_price[i] == written->raw_price[i]); }
  assert(read->price_fraction_indicator == written->price_fraction_indicator);
}

/* Price Negative Ten Pair: written and read back, then read and written back */
static void check_price_negative_ten_pair(void) {
  PriceNegativeTenPair sent;
  PriceNegativeTenPair got;
  uint8_t wire[8];
  uint8_t again[8];

  any_price_negative_ten_pair(&sent);
  assert(encode_price_negative_ten_pair(&sent, wire, 0) == 8);
  assert(decode_price_negative_ten_pair(&got, wire, 0) == 8);
  equal_price_negative_ten_pair(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_price_negative_ten_pair(&got, wire, 0) == 8);
  assert(encode_price_negative_ten_pair(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Price Negative Hundred Pair: 8 bytes ------------------------------------ */

typedef struct {
  uint8_t raw_price[7];              /* bytes 0 to 6 */
  uint8_t price_fraction_indicator;  /* byte 7 */
} PriceNegativeHundredPair;

/* any Price Negative Hundred Pair at all: every byte one the checker chooses */
static void any_price_negative_hundred_pair(PriceNegativeHundredPair *record) {
  for (size_t i = 0; i < 7; i++) { record->raw_price[i] = arbitrary(); }
  record->price_fraction_indicator = arbitrary();
}

/* Price Negative Hundred Pair to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_price_negative_hundred_pair(const PriceNegativeHundredPair *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->raw_price[i]; }
  wire[at++] = record->price_fraction_indicator;

  return at;
}

/* Price Negative Hundred Pair off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_price_negative_hundred_pair(PriceNegativeHundredPair *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { record->raw_price[i] = wire[at++]; }
  record->price_fraction_indicator = wire[at++];

  return at;
}

/* what was read of Price Negative Hundred Pair is what was written, byte for byte */
static void equal_price_negative_hundred_pair(const PriceNegativeHundredPair *read, const PriceNegativeHundredPair *written) {
  for (size_t i = 0; i < 7; i++) { assert(read->raw_price[i] == written->raw_price[i]); }
  assert(read->price_fraction_indicator == written->price_fraction_indicator);
}

/* Price Negative Hundred Pair: written and read back, then read and written back */
static void check_price_negative_hundred_pair(void) {
  PriceNegativeHundredPair sent;
  PriceNegativeHundredPair got;
  uint8_t wire[8];
  uint8_t again[8];

  any_price_negative_hundred_pair(&sent);
  assert(encode_price_negative_hundred_pair(&sent, wire, 0) == 8);
  assert(decode_price_negative_hundred_pair(&got, wire, 0) == 8);
  equal_price_negative_hundred_pair(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_price_negative_hundred_pair(&got, wire, 0) == 8);
  assert(encode_price_negative_hundred_pair(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Price Negative Thousand Pair: 8 bytes ----------------------------------- */

typedef struct {
  uint8_t raw_price[7];              /* bytes 0 to 6 */
  uint8_t price_fraction_indicator;  /* byte 7 */
} PriceNegativeThousandPair;

/* any Price Negative Thousand Pair at all: every byte one the checker chooses */
static void any_price_negative_thousand_pair(PriceNegativeThousandPair *record) {
  for (size_t i = 0; i < 7; i++) { record->raw_price[i] = arbitrary(); }
  record->price_fraction_indicator = arbitrary();
}

/* Price Negative Thousand Pair to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_price_negative_thousand_pair(const PriceNegativeThousandPair *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->raw_price[i]; }
  wire[at++] = record->price_fraction_indicator;

  return at;
}

/* Price Negative Thousand Pair off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_price_negative_thousand_pair(PriceNegativeThousandPair *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { record->raw_price[i] = wire[at++]; }
  record->price_fraction_indicator = wire[at++];

  return at;
}

/* what was read of Price Negative Thousand Pair is what was written, byte for byte */
static void equal_price_negative_thousand_pair(const PriceNegativeThousandPair *read, const PriceNegativeThousandPair *written) {
  for (size_t i = 0; i < 7; i++) { assert(read->raw_price[i] == written->raw_price[i]); }
  assert(read->price_fraction_indicator == written->price_fraction_indicator);
}

/* Price Negative Thousand Pair: written and read back, then read and written back */
static void check_price_negative_thousand_pair(void) {
  PriceNegativeThousandPair sent;
  PriceNegativeThousandPair got;
  uint8_t wire[8];
  uint8_t again[8];

  any_price_negative_thousand_pair(&sent);
  assert(encode_price_negative_thousand_pair(&sent, wire, 0) == 8);
  assert(decode_price_negative_thousand_pair(&got, wire, 0) == 8);
  equal_price_negative_thousand_pair(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_price_negative_thousand_pair(&got, wire, 0) == 8);
  assert(encode_price_negative_thousand_pair(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Price Negative Ten Thousand Pair: 8 bytes ------------------------------- */

typedef struct {
  uint8_t raw_price[7];              /* bytes 0 to 6 */
  uint8_t price_fraction_indicator;  /* byte 7 */
} PriceNegativeTenThousandPair;

/* any Price Negative Ten Thousand Pair at all: every byte one the checker chooses */
static void any_price_negative_ten_thousand_pair(PriceNegativeTenThousandPair *record) {
  for (size_t i = 0; i < 7; i++) { record->raw_price[i] = arbitrary(); }
  record->price_fraction_indicator = arbitrary();
}

/* Price Negative Ten Thousand Pair to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_price_negative_ten_thousand_pair(const PriceNegativeTenThousandPair *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->raw_price[i]; }
  wire[at++] = record->price_fraction_indicator;

  return at;
}

/* Price Negative Ten Thousand Pair off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_price_negative_ten_thousand_pair(PriceNegativeTenThousandPair *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { record->raw_price[i] = wire[at++]; }
  record->price_fraction_indicator = wire[at++];

  return at;
}

/* what was read of Price Negative Ten Thousand Pair is what was written, byte for byte */
static void equal_price_negative_ten_thousand_pair(const PriceNegativeTenThousandPair *read, const PriceNegativeTenThousandPair *written) {
  for (size_t i = 0; i < 7; i++) { assert(read->raw_price[i] == written->raw_price[i]); }
  assert(read->price_fraction_indicator == written->price_fraction_indicator);
}

/* Price Negative Ten Thousand Pair: written and read back, then read and written back */
static void check_price_negative_ten_thousand_pair(void) {
  PriceNegativeTenThousandPair sent;
  PriceNegativeTenThousandPair got;
  uint8_t wire[8];
  uint8_t again[8];

  any_price_negative_ten_thousand_pair(&sent);
  assert(encode_price_negative_ten_thousand_pair(&sent, wire, 0) == 8);
  assert(decode_price_negative_ten_thousand_pair(&got, wire, 0) == 8);
  equal_price_negative_ten_thousand_pair(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_price_negative_ten_thousand_pair(&got, wire, 0) == 8);
  assert(encode_price_negative_ten_thousand_pair(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Price Negative Hundred Thousand Pair: 8 bytes --------------------------- */

typedef struct {
  uint8_t raw_price[7];              /* bytes 0 to 6 */
  uint8_t price_fraction_indicator;  /* byte 7 */
} PriceNegativeHundredThousandPair;

/* any Price Negative Hundred Thousand Pair at all: every byte one the checker chooses */
static void any_price_negative_hundred_thousand_pair(PriceNegativeHundredThousandPair *record) {
  for (size_t i = 0; i < 7; i++) { record->raw_price[i] = arbitrary(); }
  record->price_fraction_indicator = arbitrary();
}

/* Price Negative Hundred Thousand Pair to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_price_negative_hundred_thousand_pair(const PriceNegativeHundredThousandPair *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->raw_price[i]; }
  wire[at++] = record->price_fraction_indicator;

  return at;
}

/* Price Negative Hundred Thousand Pair off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_price_negative_hundred_thousand_pair(PriceNegativeHundredThousandPair *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { record->raw_price[i] = wire[at++]; }
  record->price_fraction_indicator = wire[at++];

  return at;
}

/* what was read of Price Negative Hundred Thousand Pair is what was written, byte for byte */
static void equal_price_negative_hundred_thousand_pair(const PriceNegativeHundredThousandPair *read, const PriceNegativeHundredThousandPair *written) {
  for (size_t i = 0; i < 7; i++) { assert(read->raw_price[i] == written->raw_price[i]); }
  assert(read->price_fraction_indicator == written->price_fraction_indicator);
}

/* Price Negative Hundred Thousand Pair: written and read back, then read and written back */
static void check_price_negative_hundred_thousand_pair(void) {
  PriceNegativeHundredThousandPair sent;
  PriceNegativeHundredThousandPair got;
  uint8_t wire[8];
  uint8_t again[8];

  any_price_negative_hundred_thousand_pair(&sent);
  assert(encode_price_negative_hundred_thousand_pair(&sent, wire, 0) == 8);
  assert(decode_price_negative_hundred_thousand_pair(&got, wire, 0) == 8);
  equal_price_negative_hundred_thousand_pair(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_price_negative_hundred_thousand_pair(&got, wire, 0) == 8);
  assert(encode_price_negative_hundred_thousand_pair(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Price Negative Million Pair: 8 bytes ------------------------------------ */

typedef struct {
  uint8_t raw_price[7];              /* bytes 0 to 6 */
  uint8_t price_fraction_indicator;  /* byte 7 */
} PriceNegativeMillionPair;

/* any Price Negative Million Pair at all: every byte one the checker chooses */
static void any_price_negative_million_pair(PriceNegativeMillionPair *record) {
  for (size_t i = 0; i < 7; i++) { record->raw_price[i] = arbitrary(); }
  record->price_fraction_indicator = arbitrary();
}

/* Price Negative Million Pair to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_price_negative_million_pair(const PriceNegativeMillionPair *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->raw_price[i]; }
  wire[at++] = record->price_fraction_indicator;

  return at;
}

/* Price Negative Million Pair off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_price_negative_million_pair(PriceNegativeMillionPair *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { record->raw_price[i] = wire[at++]; }
  record->price_fraction_indicator = wire[at++];

  return at;
}

/* what was read of Price Negative Million Pair is what was written, byte for byte */
static void equal_price_negative_million_pair(const PriceNegativeMillionPair *read, const PriceNegativeMillionPair *written) {
  for (size_t i = 0; i < 7; i++) { assert(read->raw_price[i] == written->raw_price[i]); }
  assert(read->price_fraction_indicator == written->price_fraction_indicator);
}

/* Price Negative Million Pair: written and read back, then read and written back */
static void check_price_negative_million_pair(void) {
  PriceNegativeMillionPair sent;
  PriceNegativeMillionPair got;
  uint8_t wire[8];
  uint8_t again[8];

  any_price_negative_million_pair(&sent);
  assert(encode_price_negative_million_pair(&sent, wire, 0) == 8);
  assert(decode_price_negative_million_pair(&got, wire, 0) == 8);
  equal_price_negative_million_pair(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_price_negative_million_pair(&got, wire, 0) == 8);
  assert(encode_price_negative_million_pair(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Price Numeric Pair: 8 bytes --------------------------------------------- */

typedef struct {
  uint8_t price[7];                  /* bytes 0 to 6 */
  uint8_t price_fraction_indicator;  /* byte 7 */
} PriceNumericPair;

/* any Price Numeric Pair at all: every byte one the checker chooses */
static void any_price_numeric_pair(PriceNumericPair *record) {
  for (size_t i = 0; i < 7; i++) { record->price[i] = arbitrary(); }
  record->price_fraction_indicator = arbitrary();
}

/* Price Numeric Pair to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_price_numeric_pair(const PriceNumericPair *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->price[i]; }
  wire[at++] = record->price_fraction_indicator;

  return at;
}

/* Price Numeric Pair off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_price_numeric_pair(PriceNumericPair *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { record->price[i] = wire[at++]; }
  record->price_fraction_indicator = wire[at++];

  return at;
}

/* what was read of Price Numeric Pair is what was written, byte for byte */
static void equal_price_numeric_pair(const PriceNumericPair *read, const PriceNumericPair *written) {
  for (size_t i = 0; i < 7; i++) { assert(read->price[i] == written->price[i]); }
  assert(read->price_fraction_indicator == written->price_fraction_indicator);
}

/* Price Numeric Pair: written and read back, then read and written back */
static void check_price_numeric_pair(void) {
  PriceNumericPair sent;
  PriceNumericPair got;
  uint8_t wire[8];
  uint8_t again[8];

  any_price_numeric_pair(&sent);
  assert(encode_price_numeric_pair(&sent, wire, 0) == 8);
  assert(decode_price_numeric_pair(&got, wire, 0) == 8);
  equal_price_numeric_pair(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_price_numeric_pair(&got, wire, 0) == 8);
  assert(encode_price_numeric_pair(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Maximum Threshold Price Negative Whole Pair: 8 bytes -------------------- */

typedef struct {
  uint8_t raw_maximum_threshold_price[7];              /* bytes 0 to 6 */
  uint8_t maximum_threshold_price_fraction_indicator;  /* byte 7 */
} MaximumThresholdPriceNegativeWholePair;

/* any Maximum Threshold Price Negative Whole Pair at all: every byte one the checker chooses */
static void any_maximum_threshold_price_negative_whole_pair(MaximumThresholdPriceNegativeWholePair *record) {
  for (size_t i = 0; i < 7; i++) { record->raw_maximum_threshold_price[i] = arbitrary(); }
  record->maximum_threshold_price_fraction_indicator = arbitrary();
}

/* Maximum Threshold Price Negative Whole Pair to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_maximum_threshold_price_negative_whole_pair(const MaximumThresholdPriceNegativeWholePair *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->raw_maximum_threshold_price[i]; }
  wire[at++] = record->maximum_threshold_price_fraction_indicator;

  return at;
}

/* Maximum Threshold Price Negative Whole Pair off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_maximum_threshold_price_negative_whole_pair(MaximumThresholdPriceNegativeWholePair *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { record->raw_maximum_threshold_price[i] = wire[at++]; }
  record->maximum_threshold_price_fraction_indicator = wire[at++];

  return at;
}

/* what was read of Maximum Threshold Price Negative Whole Pair is what was written, byte for byte */
static void equal_maximum_threshold_price_negative_whole_pair(const MaximumThresholdPriceNegativeWholePair *read, const MaximumThresholdPriceNegativeWholePair *written) {
  for (size_t i = 0; i < 7; i++) { assert(read->raw_maximum_threshold_price[i] == written->raw_maximum_threshold_price[i]); }
  assert(read->maximum_threshold_price_fraction_indicator == written->maximum_threshold_price_fraction_indicator);
}

/* Maximum Threshold Price Negative Whole Pair: written and read back, then read and written back */
static void check_maximum_threshold_price_negative_whole_pair(void) {
  MaximumThresholdPriceNegativeWholePair sent;
  MaximumThresholdPriceNegativeWholePair got;
  uint8_t wire[8];
  uint8_t again[8];

  any_maximum_threshold_price_negative_whole_pair(&sent);
  assert(encode_maximum_threshold_price_negative_whole_pair(&sent, wire, 0) == 8);
  assert(decode_maximum_threshold_price_negative_whole_pair(&got, wire, 0) == 8);
  equal_maximum_threshold_price_negative_whole_pair(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_maximum_threshold_price_negative_whole_pair(&got, wire, 0) == 8);
  assert(encode_maximum_threshold_price_negative_whole_pair(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Maximum Threshold Price Negative Ten Pair: 8 bytes ---------------------- */

typedef struct {
  uint8_t raw_maximum_threshold_price[7];              /* bytes 0 to 6 */
  uint8_t maximum_threshold_price_fraction_indicator;  /* byte 7 */
} MaximumThresholdPriceNegativeTenPair;

/* any Maximum Threshold Price Negative Ten Pair at all: every byte one the checker chooses */
static void any_maximum_threshold_price_negative_ten_pair(MaximumThresholdPriceNegativeTenPair *record) {
  for (size_t i = 0; i < 7; i++) { record->raw_maximum_threshold_price[i] = arbitrary(); }
  record->maximum_threshold_price_fraction_indicator = arbitrary();
}

/* Maximum Threshold Price Negative Ten Pair to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_maximum_threshold_price_negative_ten_pair(const MaximumThresholdPriceNegativeTenPair *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->raw_maximum_threshold_price[i]; }
  wire[at++] = record->maximum_threshold_price_fraction_indicator;

  return at;
}

/* Maximum Threshold Price Negative Ten Pair off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_maximum_threshold_price_negative_ten_pair(MaximumThresholdPriceNegativeTenPair *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { record->raw_maximum_threshold_price[i] = wire[at++]; }
  record->maximum_threshold_price_fraction_indicator = wire[at++];

  return at;
}

/* what was read of Maximum Threshold Price Negative Ten Pair is what was written, byte for byte */
static void equal_maximum_threshold_price_negative_ten_pair(const MaximumThresholdPriceNegativeTenPair *read, const MaximumThresholdPriceNegativeTenPair *written) {
  for (size_t i = 0; i < 7; i++) { assert(read->raw_maximum_threshold_price[i] == written->raw_maximum_threshold_price[i]); }
  assert(read->maximum_threshold_price_fraction_indicator == written->maximum_threshold_price_fraction_indicator);
}

/* Maximum Threshold Price Negative Ten Pair: written and read back, then read and written back */
static void check_maximum_threshold_price_negative_ten_pair(void) {
  MaximumThresholdPriceNegativeTenPair sent;
  MaximumThresholdPriceNegativeTenPair got;
  uint8_t wire[8];
  uint8_t again[8];

  any_maximum_threshold_price_negative_ten_pair(&sent);
  assert(encode_maximum_threshold_price_negative_ten_pair(&sent, wire, 0) == 8);
  assert(decode_maximum_threshold_price_negative_ten_pair(&got, wire, 0) == 8);
  equal_maximum_threshold_price_negative_ten_pair(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_maximum_threshold_price_negative_ten_pair(&got, wire, 0) == 8);
  assert(encode_maximum_threshold_price_negative_ten_pair(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Maximum Threshold Price Negative Hundred Pair: 8 bytes ------------------ */

typedef struct {
  uint8_t raw_maximum_threshold_price[7];              /* bytes 0 to 6 */
  uint8_t maximum_threshold_price_fraction_indicator;  /* byte 7 */
} MaximumThresholdPriceNegativeHundredPair;

/* any Maximum Threshold Price Negative Hundred Pair at all: every byte one the checker chooses */
static void any_maximum_threshold_price_negative_hundred_pair(MaximumThresholdPriceNegativeHundredPair *record) {
  for (size_t i = 0; i < 7; i++) { record->raw_maximum_threshold_price[i] = arbitrary(); }
  record->maximum_threshold_price_fraction_indicator = arbitrary();
}

/* Maximum Threshold Price Negative Hundred Pair to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_maximum_threshold_price_negative_hundred_pair(const MaximumThresholdPriceNegativeHundredPair *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->raw_maximum_threshold_price[i]; }
  wire[at++] = record->maximum_threshold_price_fraction_indicator;

  return at;
}

/* Maximum Threshold Price Negative Hundred Pair off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_maximum_threshold_price_negative_hundred_pair(MaximumThresholdPriceNegativeHundredPair *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { record->raw_maximum_threshold_price[i] = wire[at++]; }
  record->maximum_threshold_price_fraction_indicator = wire[at++];

  return at;
}

/* what was read of Maximum Threshold Price Negative Hundred Pair is what was written, byte for byte */
static void equal_maximum_threshold_price_negative_hundred_pair(const MaximumThresholdPriceNegativeHundredPair *read, const MaximumThresholdPriceNegativeHundredPair *written) {
  for (size_t i = 0; i < 7; i++) { assert(read->raw_maximum_threshold_price[i] == written->raw_maximum_threshold_price[i]); }
  assert(read->maximum_threshold_price_fraction_indicator == written->maximum_threshold_price_fraction_indicator);
}

/* Maximum Threshold Price Negative Hundred Pair: written and read back, then read and written back */
static void check_maximum_threshold_price_negative_hundred_pair(void) {
  MaximumThresholdPriceNegativeHundredPair sent;
  MaximumThresholdPriceNegativeHundredPair got;
  uint8_t wire[8];
  uint8_t again[8];

  any_maximum_threshold_price_negative_hundred_pair(&sent);
  assert(encode_maximum_threshold_price_negative_hundred_pair(&sent, wire, 0) == 8);
  assert(decode_maximum_threshold_price_negative_hundred_pair(&got, wire, 0) == 8);
  equal_maximum_threshold_price_negative_hundred_pair(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_maximum_threshold_price_negative_hundred_pair(&got, wire, 0) == 8);
  assert(encode_maximum_threshold_price_negative_hundred_pair(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Maximum Threshold Price Negative Thousand Pair: 8 bytes ----------------- */

typedef struct {
  uint8_t raw_maximum_threshold_price[7];              /* bytes 0 to 6 */
  uint8_t maximum_threshold_price_fraction_indicator;  /* byte 7 */
} MaximumThresholdPriceNegativeThousandPair;

/* any Maximum Threshold Price Negative Thousand Pair at all: every byte one the checker chooses */
static void any_maximum_threshold_price_negative_thousand_pair(MaximumThresholdPriceNegativeThousandPair *record) {
  for (size_t i = 0; i < 7; i++) { record->raw_maximum_threshold_price[i] = arbitrary(); }
  record->maximum_threshold_price_fraction_indicator = arbitrary();
}

/* Maximum Threshold Price Negative Thousand Pair to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_maximum_threshold_price_negative_thousand_pair(const MaximumThresholdPriceNegativeThousandPair *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->raw_maximum_threshold_price[i]; }
  wire[at++] = record->maximum_threshold_price_fraction_indicator;

  return at;
}

/* Maximum Threshold Price Negative Thousand Pair off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_maximum_threshold_price_negative_thousand_pair(MaximumThresholdPriceNegativeThousandPair *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { record->raw_maximum_threshold_price[i] = wire[at++]; }
  record->maximum_threshold_price_fraction_indicator = wire[at++];

  return at;
}

/* what was read of Maximum Threshold Price Negative Thousand Pair is what was written, byte for byte */
static void equal_maximum_threshold_price_negative_thousand_pair(const MaximumThresholdPriceNegativeThousandPair *read, const MaximumThresholdPriceNegativeThousandPair *written) {
  for (size_t i = 0; i < 7; i++) { assert(read->raw_maximum_threshold_price[i] == written->raw_maximum_threshold_price[i]); }
  assert(read->maximum_threshold_price_fraction_indicator == written->maximum_threshold_price_fraction_indicator);
}

/* Maximum Threshold Price Negative Thousand Pair: written and read back, then read and written back */
static void check_maximum_threshold_price_negative_thousand_pair(void) {
  MaximumThresholdPriceNegativeThousandPair sent;
  MaximumThresholdPriceNegativeThousandPair got;
  uint8_t wire[8];
  uint8_t again[8];

  any_maximum_threshold_price_negative_thousand_pair(&sent);
  assert(encode_maximum_threshold_price_negative_thousand_pair(&sent, wire, 0) == 8);
  assert(decode_maximum_threshold_price_negative_thousand_pair(&got, wire, 0) == 8);
  equal_maximum_threshold_price_negative_thousand_pair(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_maximum_threshold_price_negative_thousand_pair(&got, wire, 0) == 8);
  assert(encode_maximum_threshold_price_negative_thousand_pair(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Maximum Threshold Price Negative Ten Thousand Pair: 8 bytes ------------- */

typedef struct {
  uint8_t raw_maximum_threshold_price[7];              /* bytes 0 to 6 */
  uint8_t maximum_threshold_price_fraction_indicator;  /* byte 7 */
} MaximumThresholdPriceNegativeTenThousandPair;

/* any Maximum Threshold Price Negative Ten Thousand Pair at all: every byte one the checker chooses */
static void any_maximum_threshold_price_negative_ten_thousand_pair(MaximumThresholdPriceNegativeTenThousandPair *record) {
  for (size_t i = 0; i < 7; i++) { record->raw_maximum_threshold_price[i] = arbitrary(); }
  record->maximum_threshold_price_fraction_indicator = arbitrary();
}

/* Maximum Threshold Price Negative Ten Thousand Pair to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_maximum_threshold_price_negative_ten_thousand_pair(const MaximumThresholdPriceNegativeTenThousandPair *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->raw_maximum_threshold_price[i]; }
  wire[at++] = record->maximum_threshold_price_fraction_indicator;

  return at;
}

/* Maximum Threshold Price Negative Ten Thousand Pair off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_maximum_threshold_price_negative_ten_thousand_pair(MaximumThresholdPriceNegativeTenThousandPair *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { record->raw_maximum_threshold_price[i] = wire[at++]; }
  record->maximum_threshold_price_fraction_indicator = wire[at++];

  return at;
}

/* what was read of Maximum Threshold Price Negative Ten Thousand Pair is what was written, byte for byte */
static void equal_maximum_threshold_price_negative_ten_thousand_pair(const MaximumThresholdPriceNegativeTenThousandPair *read, const MaximumThresholdPriceNegativeTenThousandPair *written) {
  for (size_t i = 0; i < 7; i++) { assert(read->raw_maximum_threshold_price[i] == written->raw_maximum_threshold_price[i]); }
  assert(read->maximum_threshold_price_fraction_indicator == written->maximum_threshold_price_fraction_indicator);
}

/* Maximum Threshold Price Negative Ten Thousand Pair: written and read back, then read and written back */
static void check_maximum_threshold_price_negative_ten_thousand_pair(void) {
  MaximumThresholdPriceNegativeTenThousandPair sent;
  MaximumThresholdPriceNegativeTenThousandPair got;
  uint8_t wire[8];
  uint8_t again[8];

  any_maximum_threshold_price_negative_ten_thousand_pair(&sent);
  assert(encode_maximum_threshold_price_negative_ten_thousand_pair(&sent, wire, 0) == 8);
  assert(decode_maximum_threshold_price_negative_ten_thousand_pair(&got, wire, 0) == 8);
  equal_maximum_threshold_price_negative_ten_thousand_pair(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_maximum_threshold_price_negative_ten_thousand_pair(&got, wire, 0) == 8);
  assert(encode_maximum_threshold_price_negative_ten_thousand_pair(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Maximum Threshold Price Negative Hundred Thousand Pair: 8 bytes --------- */

typedef struct {
  uint8_t raw_maximum_threshold_price[7];              /* bytes 0 to 6 */
  uint8_t maximum_threshold_price_fraction_indicator;  /* byte 7 */
} MaximumThresholdPriceNegativeHundredThousandPair;

/* any Maximum Threshold Price Negative Hundred Thousand Pair at all: every byte one the checker chooses */
static void any_maximum_threshold_price_negative_hundred_thousand_pair(MaximumThresholdPriceNegativeHundredThousandPair *record) {
  for (size_t i = 0; i < 7; i++) { record->raw_maximum_threshold_price[i] = arbitrary(); }
  record->maximum_threshold_price_fraction_indicator = arbitrary();
}

/* Maximum Threshold Price Negative Hundred Thousand Pair to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_maximum_threshold_price_negative_hundred_thousand_pair(const MaximumThresholdPriceNegativeHundredThousandPair *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->raw_maximum_threshold_price[i]; }
  wire[at++] = record->maximum_threshold_price_fraction_indicator;

  return at;
}

/* Maximum Threshold Price Negative Hundred Thousand Pair off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_maximum_threshold_price_negative_hundred_thousand_pair(MaximumThresholdPriceNegativeHundredThousandPair *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { record->raw_maximum_threshold_price[i] = wire[at++]; }
  record->maximum_threshold_price_fraction_indicator = wire[at++];

  return at;
}

/* what was read of Maximum Threshold Price Negative Hundred Thousand Pair is what was written, byte for byte */
static void equal_maximum_threshold_price_negative_hundred_thousand_pair(const MaximumThresholdPriceNegativeHundredThousandPair *read, const MaximumThresholdPriceNegativeHundredThousandPair *written) {
  for (size_t i = 0; i < 7; i++) { assert(read->raw_maximum_threshold_price[i] == written->raw_maximum_threshold_price[i]); }
  assert(read->maximum_threshold_price_fraction_indicator == written->maximum_threshold_price_fraction_indicator);
}

/* Maximum Threshold Price Negative Hundred Thousand Pair: written and read back, then read and written back */
static void check_maximum_threshold_price_negative_hundred_thousand_pair(void) {
  MaximumThresholdPriceNegativeHundredThousandPair sent;
  MaximumThresholdPriceNegativeHundredThousandPair got;
  uint8_t wire[8];
  uint8_t again[8];

  any_maximum_threshold_price_negative_hundred_thousand_pair(&sent);
  assert(encode_maximum_threshold_price_negative_hundred_thousand_pair(&sent, wire, 0) == 8);
  assert(decode_maximum_threshold_price_negative_hundred_thousand_pair(&got, wire, 0) == 8);
  equal_maximum_threshold_price_negative_hundred_thousand_pair(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_maximum_threshold_price_negative_hundred_thousand_pair(&got, wire, 0) == 8);
  assert(encode_maximum_threshold_price_negative_hundred_thousand_pair(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Maximum Threshold Price Negative Million Pair: 8 bytes ------------------ */

typedef struct {
  uint8_t raw_maximum_threshold_price[7];              /* bytes 0 to 6 */
  uint8_t maximum_threshold_price_fraction_indicator;  /* byte 7 */
} MaximumThresholdPriceNegativeMillionPair;

/* any Maximum Threshold Price Negative Million Pair at all: every byte one the checker chooses */
static void any_maximum_threshold_price_negative_million_pair(MaximumThresholdPriceNegativeMillionPair *record) {
  for (size_t i = 0; i < 7; i++) { record->raw_maximum_threshold_price[i] = arbitrary(); }
  record->maximum_threshold_price_fraction_indicator = arbitrary();
}

/* Maximum Threshold Price Negative Million Pair to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_maximum_threshold_price_negative_million_pair(const MaximumThresholdPriceNegativeMillionPair *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->raw_maximum_threshold_price[i]; }
  wire[at++] = record->maximum_threshold_price_fraction_indicator;

  return at;
}

/* Maximum Threshold Price Negative Million Pair off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_maximum_threshold_price_negative_million_pair(MaximumThresholdPriceNegativeMillionPair *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { record->raw_maximum_threshold_price[i] = wire[at++]; }
  record->maximum_threshold_price_fraction_indicator = wire[at++];

  return at;
}

/* what was read of Maximum Threshold Price Negative Million Pair is what was written, byte for byte */
static void equal_maximum_threshold_price_negative_million_pair(const MaximumThresholdPriceNegativeMillionPair *read, const MaximumThresholdPriceNegativeMillionPair *written) {
  for (size_t i = 0; i < 7; i++) { assert(read->raw_maximum_threshold_price[i] == written->raw_maximum_threshold_price[i]); }
  assert(read->maximum_threshold_price_fraction_indicator == written->maximum_threshold_price_fraction_indicator);
}

/* Maximum Threshold Price Negative Million Pair: written and read back, then read and written back */
static void check_maximum_threshold_price_negative_million_pair(void) {
  MaximumThresholdPriceNegativeMillionPair sent;
  MaximumThresholdPriceNegativeMillionPair got;
  uint8_t wire[8];
  uint8_t again[8];

  any_maximum_threshold_price_negative_million_pair(&sent);
  assert(encode_maximum_threshold_price_negative_million_pair(&sent, wire, 0) == 8);
  assert(decode_maximum_threshold_price_negative_million_pair(&got, wire, 0) == 8);
  equal_maximum_threshold_price_negative_million_pair(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_maximum_threshold_price_negative_million_pair(&got, wire, 0) == 8);
  assert(encode_maximum_threshold_price_negative_million_pair(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Maximum Threshold Price Numeric Pair: 8 bytes --------------------------- */

typedef struct {
  uint8_t maximum_threshold_price[7];                  /* bytes 0 to 6 */
  uint8_t maximum_threshold_price_fraction_indicator;  /* byte 7 */
} MaximumThresholdPriceNumericPair;

/* any Maximum Threshold Price Numeric Pair at all: every byte one the checker chooses */
static void any_maximum_threshold_price_numeric_pair(MaximumThresholdPriceNumericPair *record) {
  for (size_t i = 0; i < 7; i++) { record->maximum_threshold_price[i] = arbitrary(); }
  record->maximum_threshold_price_fraction_indicator = arbitrary();
}

/* Maximum Threshold Price Numeric Pair to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_maximum_threshold_price_numeric_pair(const MaximumThresholdPriceNumericPair *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->maximum_threshold_price[i]; }
  wire[at++] = record->maximum_threshold_price_fraction_indicator;

  return at;
}

/* Maximum Threshold Price Numeric Pair off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_maximum_threshold_price_numeric_pair(MaximumThresholdPriceNumericPair *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { record->maximum_threshold_price[i] = wire[at++]; }
  record->maximum_threshold_price_fraction_indicator = wire[at++];

  return at;
}

/* what was read of Maximum Threshold Price Numeric Pair is what was written, byte for byte */
static void equal_maximum_threshold_price_numeric_pair(const MaximumThresholdPriceNumericPair *read, const MaximumThresholdPriceNumericPair *written) {
  for (size_t i = 0; i < 7; i++) { assert(read->maximum_threshold_price[i] == written->maximum_threshold_price[i]); }
  assert(read->maximum_threshold_price_fraction_indicator == written->maximum_threshold_price_fraction_indicator);
}

/* Maximum Threshold Price Numeric Pair: written and read back, then read and written back */
static void check_maximum_threshold_price_numeric_pair(void) {
  MaximumThresholdPriceNumericPair sent;
  MaximumThresholdPriceNumericPair got;
  uint8_t wire[8];
  uint8_t again[8];

  any_maximum_threshold_price_numeric_pair(&sent);
  assert(encode_maximum_threshold_price_numeric_pair(&sent, wire, 0) == 8);
  assert(decode_maximum_threshold_price_numeric_pair(&got, wire, 0) == 8);
  equal_maximum_threshold_price_numeric_pair(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_maximum_threshold_price_numeric_pair(&got, wire, 0) == 8);
  assert(encode_maximum_threshold_price_numeric_pair(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Minimum Threshold Price Negative Whole Pair: 8 bytes -------------------- */

typedef struct {
  uint8_t raw_minimum_threshold_price[7];              /* bytes 0 to 6 */
  uint8_t minimum_threshold_price_fraction_indicator;  /* byte 7 */
} MinimumThresholdPriceNegativeWholePair;

/* any Minimum Threshold Price Negative Whole Pair at all: every byte one the checker chooses */
static void any_minimum_threshold_price_negative_whole_pair(MinimumThresholdPriceNegativeWholePair *record) {
  for (size_t i = 0; i < 7; i++) { record->raw_minimum_threshold_price[i] = arbitrary(); }
  record->minimum_threshold_price_fraction_indicator = arbitrary();
}

/* Minimum Threshold Price Negative Whole Pair to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_minimum_threshold_price_negative_whole_pair(const MinimumThresholdPriceNegativeWholePair *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->raw_minimum_threshold_price[i]; }
  wire[at++] = record->minimum_threshold_price_fraction_indicator;

  return at;
}

/* Minimum Threshold Price Negative Whole Pair off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_minimum_threshold_price_negative_whole_pair(MinimumThresholdPriceNegativeWholePair *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { record->raw_minimum_threshold_price[i] = wire[at++]; }
  record->minimum_threshold_price_fraction_indicator = wire[at++];

  return at;
}

/* what was read of Minimum Threshold Price Negative Whole Pair is what was written, byte for byte */
static void equal_minimum_threshold_price_negative_whole_pair(const MinimumThresholdPriceNegativeWholePair *read, const MinimumThresholdPriceNegativeWholePair *written) {
  for (size_t i = 0; i < 7; i++) { assert(read->raw_minimum_threshold_price[i] == written->raw_minimum_threshold_price[i]); }
  assert(read->minimum_threshold_price_fraction_indicator == written->minimum_threshold_price_fraction_indicator);
}

/* Minimum Threshold Price Negative Whole Pair: written and read back, then read and written back */
static void check_minimum_threshold_price_negative_whole_pair(void) {
  MinimumThresholdPriceNegativeWholePair sent;
  MinimumThresholdPriceNegativeWholePair got;
  uint8_t wire[8];
  uint8_t again[8];

  any_minimum_threshold_price_negative_whole_pair(&sent);
  assert(encode_minimum_threshold_price_negative_whole_pair(&sent, wire, 0) == 8);
  assert(decode_minimum_threshold_price_negative_whole_pair(&got, wire, 0) == 8);
  equal_minimum_threshold_price_negative_whole_pair(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_minimum_threshold_price_negative_whole_pair(&got, wire, 0) == 8);
  assert(encode_minimum_threshold_price_negative_whole_pair(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Minimum Threshold Price Negative Ten Pair: 8 bytes ---------------------- */

typedef struct {
  uint8_t raw_minimum_threshold_price[7];              /* bytes 0 to 6 */
  uint8_t minimum_threshold_price_fraction_indicator;  /* byte 7 */
} MinimumThresholdPriceNegativeTenPair;

/* any Minimum Threshold Price Negative Ten Pair at all: every byte one the checker chooses */
static void any_minimum_threshold_price_negative_ten_pair(MinimumThresholdPriceNegativeTenPair *record) {
  for (size_t i = 0; i < 7; i++) { record->raw_minimum_threshold_price[i] = arbitrary(); }
  record->minimum_threshold_price_fraction_indicator = arbitrary();
}

/* Minimum Threshold Price Negative Ten Pair to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_minimum_threshold_price_negative_ten_pair(const MinimumThresholdPriceNegativeTenPair *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->raw_minimum_threshold_price[i]; }
  wire[at++] = record->minimum_threshold_price_fraction_indicator;

  return at;
}

/* Minimum Threshold Price Negative Ten Pair off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_minimum_threshold_price_negative_ten_pair(MinimumThresholdPriceNegativeTenPair *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { record->raw_minimum_threshold_price[i] = wire[at++]; }
  record->minimum_threshold_price_fraction_indicator = wire[at++];

  return at;
}

/* what was read of Minimum Threshold Price Negative Ten Pair is what was written, byte for byte */
static void equal_minimum_threshold_price_negative_ten_pair(const MinimumThresholdPriceNegativeTenPair *read, const MinimumThresholdPriceNegativeTenPair *written) {
  for (size_t i = 0; i < 7; i++) { assert(read->raw_minimum_threshold_price[i] == written->raw_minimum_threshold_price[i]); }
  assert(read->minimum_threshold_price_fraction_indicator == written->minimum_threshold_price_fraction_indicator);
}

/* Minimum Threshold Price Negative Ten Pair: written and read back, then read and written back */
static void check_minimum_threshold_price_negative_ten_pair(void) {
  MinimumThresholdPriceNegativeTenPair sent;
  MinimumThresholdPriceNegativeTenPair got;
  uint8_t wire[8];
  uint8_t again[8];

  any_minimum_threshold_price_negative_ten_pair(&sent);
  assert(encode_minimum_threshold_price_negative_ten_pair(&sent, wire, 0) == 8);
  assert(decode_minimum_threshold_price_negative_ten_pair(&got, wire, 0) == 8);
  equal_minimum_threshold_price_negative_ten_pair(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_minimum_threshold_price_negative_ten_pair(&got, wire, 0) == 8);
  assert(encode_minimum_threshold_price_negative_ten_pair(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Minimum Threshold Price Negative Hundred Pair: 8 bytes ------------------ */

typedef struct {
  uint8_t raw_minimum_threshold_price[7];              /* bytes 0 to 6 */
  uint8_t minimum_threshold_price_fraction_indicator;  /* byte 7 */
} MinimumThresholdPriceNegativeHundredPair;

/* any Minimum Threshold Price Negative Hundred Pair at all: every byte one the checker chooses */
static void any_minimum_threshold_price_negative_hundred_pair(MinimumThresholdPriceNegativeHundredPair *record) {
  for (size_t i = 0; i < 7; i++) { record->raw_minimum_threshold_price[i] = arbitrary(); }
  record->minimum_threshold_price_fraction_indicator = arbitrary();
}

/* Minimum Threshold Price Negative Hundred Pair to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_minimum_threshold_price_negative_hundred_pair(const MinimumThresholdPriceNegativeHundredPair *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->raw_minimum_threshold_price[i]; }
  wire[at++] = record->minimum_threshold_price_fraction_indicator;

  return at;
}

/* Minimum Threshold Price Negative Hundred Pair off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_minimum_threshold_price_negative_hundred_pair(MinimumThresholdPriceNegativeHundredPair *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { record->raw_minimum_threshold_price[i] = wire[at++]; }
  record->minimum_threshold_price_fraction_indicator = wire[at++];

  return at;
}

/* what was read of Minimum Threshold Price Negative Hundred Pair is what was written, byte for byte */
static void equal_minimum_threshold_price_negative_hundred_pair(const MinimumThresholdPriceNegativeHundredPair *read, const MinimumThresholdPriceNegativeHundredPair *written) {
  for (size_t i = 0; i < 7; i++) { assert(read->raw_minimum_threshold_price[i] == written->raw_minimum_threshold_price[i]); }
  assert(read->minimum_threshold_price_fraction_indicator == written->minimum_threshold_price_fraction_indicator);
}

/* Minimum Threshold Price Negative Hundred Pair: written and read back, then read and written back */
static void check_minimum_threshold_price_negative_hundred_pair(void) {
  MinimumThresholdPriceNegativeHundredPair sent;
  MinimumThresholdPriceNegativeHundredPair got;
  uint8_t wire[8];
  uint8_t again[8];

  any_minimum_threshold_price_negative_hundred_pair(&sent);
  assert(encode_minimum_threshold_price_negative_hundred_pair(&sent, wire, 0) == 8);
  assert(decode_minimum_threshold_price_negative_hundred_pair(&got, wire, 0) == 8);
  equal_minimum_threshold_price_negative_hundred_pair(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_minimum_threshold_price_negative_hundred_pair(&got, wire, 0) == 8);
  assert(encode_minimum_threshold_price_negative_hundred_pair(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Minimum Threshold Price Negative Thousand Pair: 8 bytes ----------------- */

typedef struct {
  uint8_t raw_minimum_threshold_price[7];              /* bytes 0 to 6 */
  uint8_t minimum_threshold_price_fraction_indicator;  /* byte 7 */
} MinimumThresholdPriceNegativeThousandPair;

/* any Minimum Threshold Price Negative Thousand Pair at all: every byte one the checker chooses */
static void any_minimum_threshold_price_negative_thousand_pair(MinimumThresholdPriceNegativeThousandPair *record) {
  for (size_t i = 0; i < 7; i++) { record->raw_minimum_threshold_price[i] = arbitrary(); }
  record->minimum_threshold_price_fraction_indicator = arbitrary();
}

/* Minimum Threshold Price Negative Thousand Pair to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_minimum_threshold_price_negative_thousand_pair(const MinimumThresholdPriceNegativeThousandPair *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->raw_minimum_threshold_price[i]; }
  wire[at++] = record->minimum_threshold_price_fraction_indicator;

  return at;
}

/* Minimum Threshold Price Negative Thousand Pair off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_minimum_threshold_price_negative_thousand_pair(MinimumThresholdPriceNegativeThousandPair *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { record->raw_minimum_threshold_price[i] = wire[at++]; }
  record->minimum_threshold_price_fraction_indicator = wire[at++];

  return at;
}

/* what was read of Minimum Threshold Price Negative Thousand Pair is what was written, byte for byte */
static void equal_minimum_threshold_price_negative_thousand_pair(const MinimumThresholdPriceNegativeThousandPair *read, const MinimumThresholdPriceNegativeThousandPair *written) {
  for (size_t i = 0; i < 7; i++) { assert(read->raw_minimum_threshold_price[i] == written->raw_minimum_threshold_price[i]); }
  assert(read->minimum_threshold_price_fraction_indicator == written->minimum_threshold_price_fraction_indicator);
}

/* Minimum Threshold Price Negative Thousand Pair: written and read back, then read and written back */
static void check_minimum_threshold_price_negative_thousand_pair(void) {
  MinimumThresholdPriceNegativeThousandPair sent;
  MinimumThresholdPriceNegativeThousandPair got;
  uint8_t wire[8];
  uint8_t again[8];

  any_minimum_threshold_price_negative_thousand_pair(&sent);
  assert(encode_minimum_threshold_price_negative_thousand_pair(&sent, wire, 0) == 8);
  assert(decode_minimum_threshold_price_negative_thousand_pair(&got, wire, 0) == 8);
  equal_minimum_threshold_price_negative_thousand_pair(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_minimum_threshold_price_negative_thousand_pair(&got, wire, 0) == 8);
  assert(encode_minimum_threshold_price_negative_thousand_pair(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Minimum Threshold Price Negative Ten Thousand Pair: 8 bytes ------------- */

typedef struct {
  uint8_t raw_minimum_threshold_price[7];              /* bytes 0 to 6 */
  uint8_t minimum_threshold_price_fraction_indicator;  /* byte 7 */
} MinimumThresholdPriceNegativeTenThousandPair;

/* any Minimum Threshold Price Negative Ten Thousand Pair at all: every byte one the checker chooses */
static void any_minimum_threshold_price_negative_ten_thousand_pair(MinimumThresholdPriceNegativeTenThousandPair *record) {
  for (size_t i = 0; i < 7; i++) { record->raw_minimum_threshold_price[i] = arbitrary(); }
  record->minimum_threshold_price_fraction_indicator = arbitrary();
}

/* Minimum Threshold Price Negative Ten Thousand Pair to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_minimum_threshold_price_negative_ten_thousand_pair(const MinimumThresholdPriceNegativeTenThousandPair *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->raw_minimum_threshold_price[i]; }
  wire[at++] = record->minimum_threshold_price_fraction_indicator;

  return at;
}

/* Minimum Threshold Price Negative Ten Thousand Pair off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_minimum_threshold_price_negative_ten_thousand_pair(MinimumThresholdPriceNegativeTenThousandPair *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { record->raw_minimum_threshold_price[i] = wire[at++]; }
  record->minimum_threshold_price_fraction_indicator = wire[at++];

  return at;
}

/* what was read of Minimum Threshold Price Negative Ten Thousand Pair is what was written, byte for byte */
static void equal_minimum_threshold_price_negative_ten_thousand_pair(const MinimumThresholdPriceNegativeTenThousandPair *read, const MinimumThresholdPriceNegativeTenThousandPair *written) {
  for (size_t i = 0; i < 7; i++) { assert(read->raw_minimum_threshold_price[i] == written->raw_minimum_threshold_price[i]); }
  assert(read->minimum_threshold_price_fraction_indicator == written->minimum_threshold_price_fraction_indicator);
}

/* Minimum Threshold Price Negative Ten Thousand Pair: written and read back, then read and written back */
static void check_minimum_threshold_price_negative_ten_thousand_pair(void) {
  MinimumThresholdPriceNegativeTenThousandPair sent;
  MinimumThresholdPriceNegativeTenThousandPair got;
  uint8_t wire[8];
  uint8_t again[8];

  any_minimum_threshold_price_negative_ten_thousand_pair(&sent);
  assert(encode_minimum_threshold_price_negative_ten_thousand_pair(&sent, wire, 0) == 8);
  assert(decode_minimum_threshold_price_negative_ten_thousand_pair(&got, wire, 0) == 8);
  equal_minimum_threshold_price_negative_ten_thousand_pair(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_minimum_threshold_price_negative_ten_thousand_pair(&got, wire, 0) == 8);
  assert(encode_minimum_threshold_price_negative_ten_thousand_pair(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Minimum Threshold Price Negative Hundred Thousand Pair: 8 bytes --------- */

typedef struct {
  uint8_t raw_minimum_threshold_price[7];              /* bytes 0 to 6 */
  uint8_t minimum_threshold_price_fraction_indicator;  /* byte 7 */
} MinimumThresholdPriceNegativeHundredThousandPair;

/* any Minimum Threshold Price Negative Hundred Thousand Pair at all: every byte one the checker chooses */
static void any_minimum_threshold_price_negative_hundred_thousand_pair(MinimumThresholdPriceNegativeHundredThousandPair *record) {
  for (size_t i = 0; i < 7; i++) { record->raw_minimum_threshold_price[i] = arbitrary(); }
  record->minimum_threshold_price_fraction_indicator = arbitrary();
}

/* Minimum Threshold Price Negative Hundred Thousand Pair to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_minimum_threshold_price_negative_hundred_thousand_pair(const MinimumThresholdPriceNegativeHundredThousandPair *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->raw_minimum_threshold_price[i]; }
  wire[at++] = record->minimum_threshold_price_fraction_indicator;

  return at;
}

/* Minimum Threshold Price Negative Hundred Thousand Pair off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_minimum_threshold_price_negative_hundred_thousand_pair(MinimumThresholdPriceNegativeHundredThousandPair *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { record->raw_minimum_threshold_price[i] = wire[at++]; }
  record->minimum_threshold_price_fraction_indicator = wire[at++];

  return at;
}

/* what was read of Minimum Threshold Price Negative Hundred Thousand Pair is what was written, byte for byte */
static void equal_minimum_threshold_price_negative_hundred_thousand_pair(const MinimumThresholdPriceNegativeHundredThousandPair *read, const MinimumThresholdPriceNegativeHundredThousandPair *written) {
  for (size_t i = 0; i < 7; i++) { assert(read->raw_minimum_threshold_price[i] == written->raw_minimum_threshold_price[i]); }
  assert(read->minimum_threshold_price_fraction_indicator == written->minimum_threshold_price_fraction_indicator);
}

/* Minimum Threshold Price Negative Hundred Thousand Pair: written and read back, then read and written back */
static void check_minimum_threshold_price_negative_hundred_thousand_pair(void) {
  MinimumThresholdPriceNegativeHundredThousandPair sent;
  MinimumThresholdPriceNegativeHundredThousandPair got;
  uint8_t wire[8];
  uint8_t again[8];

  any_minimum_threshold_price_negative_hundred_thousand_pair(&sent);
  assert(encode_minimum_threshold_price_negative_hundred_thousand_pair(&sent, wire, 0) == 8);
  assert(decode_minimum_threshold_price_negative_hundred_thousand_pair(&got, wire, 0) == 8);
  equal_minimum_threshold_price_negative_hundred_thousand_pair(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_minimum_threshold_price_negative_hundred_thousand_pair(&got, wire, 0) == 8);
  assert(encode_minimum_threshold_price_negative_hundred_thousand_pair(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Minimum Threshold Price Negative Million Pair: 8 bytes ------------------ */

typedef struct {
  uint8_t raw_minimum_threshold_price[7];              /* bytes 0 to 6 */
  uint8_t minimum_threshold_price_fraction_indicator;  /* byte 7 */
} MinimumThresholdPriceNegativeMillionPair;

/* any Minimum Threshold Price Negative Million Pair at all: every byte one the checker chooses */
static void any_minimum_threshold_price_negative_million_pair(MinimumThresholdPriceNegativeMillionPair *record) {
  for (size_t i = 0; i < 7; i++) { record->raw_minimum_threshold_price[i] = arbitrary(); }
  record->minimum_threshold_price_fraction_indicator = arbitrary();
}

/* Minimum Threshold Price Negative Million Pair to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_minimum_threshold_price_negative_million_pair(const MinimumThresholdPriceNegativeMillionPair *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->raw_minimum_threshold_price[i]; }
  wire[at++] = record->minimum_threshold_price_fraction_indicator;

  return at;
}

/* Minimum Threshold Price Negative Million Pair off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_minimum_threshold_price_negative_million_pair(MinimumThresholdPriceNegativeMillionPair *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { record->raw_minimum_threshold_price[i] = wire[at++]; }
  record->minimum_threshold_price_fraction_indicator = wire[at++];

  return at;
}

/* what was read of Minimum Threshold Price Negative Million Pair is what was written, byte for byte */
static void equal_minimum_threshold_price_negative_million_pair(const MinimumThresholdPriceNegativeMillionPair *read, const MinimumThresholdPriceNegativeMillionPair *written) {
  for (size_t i = 0; i < 7; i++) { assert(read->raw_minimum_threshold_price[i] == written->raw_minimum_threshold_price[i]); }
  assert(read->minimum_threshold_price_fraction_indicator == written->minimum_threshold_price_fraction_indicator);
}

/* Minimum Threshold Price Negative Million Pair: written and read back, then read and written back */
static void check_minimum_threshold_price_negative_million_pair(void) {
  MinimumThresholdPriceNegativeMillionPair sent;
  MinimumThresholdPriceNegativeMillionPair got;
  uint8_t wire[8];
  uint8_t again[8];

  any_minimum_threshold_price_negative_million_pair(&sent);
  assert(encode_minimum_threshold_price_negative_million_pair(&sent, wire, 0) == 8);
  assert(decode_minimum_threshold_price_negative_million_pair(&got, wire, 0) == 8);
  equal_minimum_threshold_price_negative_million_pair(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_minimum_threshold_price_negative_million_pair(&got, wire, 0) == 8);
  assert(encode_minimum_threshold_price_negative_million_pair(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Minimum Threshold Price Numeric Pair: 8 bytes --------------------------- */

typedef struct {
  uint8_t minimum_threshold_price[7];                  /* bytes 0 to 6 */
  uint8_t minimum_threshold_price_fraction_indicator;  /* byte 7 */
} MinimumThresholdPriceNumericPair;

/* any Minimum Threshold Price Numeric Pair at all: every byte one the checker chooses */
static void any_minimum_threshold_price_numeric_pair(MinimumThresholdPriceNumericPair *record) {
  for (size_t i = 0; i < 7; i++) { record->minimum_threshold_price[i] = arbitrary(); }
  record->minimum_threshold_price_fraction_indicator = arbitrary();
}

/* Minimum Threshold Price Numeric Pair to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_minimum_threshold_price_numeric_pair(const MinimumThresholdPriceNumericPair *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->minimum_threshold_price[i]; }
  wire[at++] = record->minimum_threshold_price_fraction_indicator;

  return at;
}

/* Minimum Threshold Price Numeric Pair off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_minimum_threshold_price_numeric_pair(MinimumThresholdPriceNumericPair *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { record->minimum_threshold_price[i] = wire[at++]; }
  record->minimum_threshold_price_fraction_indicator = wire[at++];

  return at;
}

/* what was read of Minimum Threshold Price Numeric Pair is what was written, byte for byte */
static void equal_minimum_threshold_price_numeric_pair(const MinimumThresholdPriceNumericPair *read, const MinimumThresholdPriceNumericPair *written) {
  for (size_t i = 0; i < 7; i++) { assert(read->minimum_threshold_price[i] == written->minimum_threshold_price[i]); }
  assert(read->minimum_threshold_price_fraction_indicator == written->minimum_threshold_price_fraction_indicator);
}

/* Minimum Threshold Price Numeric Pair: written and read back, then read and written back */
static void check_minimum_threshold_price_numeric_pair(void) {
  MinimumThresholdPriceNumericPair sent;
  MinimumThresholdPriceNumericPair got;
  uint8_t wire[8];
  uint8_t again[8];

  any_minimum_threshold_price_numeric_pair(&sent);
  assert(encode_minimum_threshold_price_numeric_pair(&sent, wire, 0) == 8);
  assert(decode_minimum_threshold_price_numeric_pair(&got, wire, 0) == 8);
  equal_minimum_threshold_price_numeric_pair(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_minimum_threshold_price_numeric_pair(&got, wire, 0) == 8);
  assert(encode_minimum_threshold_price_numeric_pair(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Tick Increment Numeric Pair: 8 bytes ------------------------------------ */

typedef struct {
  uint8_t tick_increment_numeric[7];          /* bytes 0 to 6 */
  uint8_t tick_increment_fraction_indicator;  /* byte 7 */
} TickIncrementNumericPair;

/* any Tick Increment Numeric Pair at all: every byte one the checker chooses */
static void any_tick_increment_numeric_pair(TickIncrementNumericPair *record) {
  for (size_t i = 0; i < 7; i++) { record->tick_increment_numeric[i] = arbitrary(); }
  record->tick_increment_fraction_indicator = arbitrary();
}

/* Tick Increment Numeric Pair to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_tick_increment_numeric_pair(const TickIncrementNumericPair *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->tick_increment_numeric[i]; }
  wire[at++] = record->tick_increment_fraction_indicator;

  return at;
}

/* Tick Increment Numeric Pair off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_tick_increment_numeric_pair(TickIncrementNumericPair *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { record->tick_increment_numeric[i] = wire[at++]; }
  record->tick_increment_fraction_indicator = wire[at++];

  return at;
}

/* what was read of Tick Increment Numeric Pair is what was written, byte for byte */
static void equal_tick_increment_numeric_pair(const TickIncrementNumericPair *read, const TickIncrementNumericPair *written) {
  for (size_t i = 0; i < 7; i++) { assert(read->tick_increment_numeric[i] == written->tick_increment_numeric[i]); }
  assert(read->tick_increment_fraction_indicator == written->tick_increment_fraction_indicator);
}

/* Tick Increment Numeric Pair: written and read back, then read and written back */
static void check_tick_increment_numeric_pair(void) {
  TickIncrementNumericPair sent;
  TickIncrementNumericPair got;
  uint8_t wire[8];
  uint8_t again[8];

  any_tick_increment_numeric_pair(&sent);
  assert(encode_tick_increment_numeric_pair(&sent, wire, 0) == 8);
  assert(decode_tick_increment_numeric_pair(&got, wire, 0) == 8);
  equal_tick_increment_numeric_pair(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_tick_increment_numeric_pair(&got, wire, 0) == 8);
  assert(encode_tick_increment_numeric_pair(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Tick Increment Numeric Negative Whole Pair: 8 bytes --------------------- */

typedef struct {
  uint8_t raw_tick_increment_numeric[7];      /* bytes 0 to 6 */
  uint8_t tick_increment_fraction_indicator;  /* byte 7 */
} TickIncrementNumericNegativeWholePair;

/* any Tick Increment Numeric Negative Whole Pair at all: every byte one the checker chooses */
static void any_tick_increment_numeric_negative_whole_pair(TickIncrementNumericNegativeWholePair *record) {
  for (size_t i = 0; i < 7; i++) { record->raw_tick_increment_numeric[i] = arbitrary(); }
  record->tick_increment_fraction_indicator = arbitrary();
}

/* Tick Increment Numeric Negative Whole Pair to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_tick_increment_numeric_negative_whole_pair(const TickIncrementNumericNegativeWholePair *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->raw_tick_increment_numeric[i]; }
  wire[at++] = record->tick_increment_fraction_indicator;

  return at;
}

/* Tick Increment Numeric Negative Whole Pair off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_tick_increment_numeric_negative_whole_pair(TickIncrementNumericNegativeWholePair *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { record->raw_tick_increment_numeric[i] = wire[at++]; }
  record->tick_increment_fraction_indicator = wire[at++];

  return at;
}

/* what was read of Tick Increment Numeric Negative Whole Pair is what was written, byte for byte */
static void equal_tick_increment_numeric_negative_whole_pair(const TickIncrementNumericNegativeWholePair *read, const TickIncrementNumericNegativeWholePair *written) {
  for (size_t i = 0; i < 7; i++) { assert(read->raw_tick_increment_numeric[i] == written->raw_tick_increment_numeric[i]); }
  assert(read->tick_increment_fraction_indicator == written->tick_increment_fraction_indicator);
}

/* Tick Increment Numeric Negative Whole Pair: written and read back, then read and written back */
static void check_tick_increment_numeric_negative_whole_pair(void) {
  TickIncrementNumericNegativeWholePair sent;
  TickIncrementNumericNegativeWholePair got;
  uint8_t wire[8];
  uint8_t again[8];

  any_tick_increment_numeric_negative_whole_pair(&sent);
  assert(encode_tick_increment_numeric_negative_whole_pair(&sent, wire, 0) == 8);
  assert(decode_tick_increment_numeric_negative_whole_pair(&got, wire, 0) == 8);
  equal_tick_increment_numeric_negative_whole_pair(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_tick_increment_numeric_negative_whole_pair(&got, wire, 0) == 8);
  assert(encode_tick_increment_numeric_negative_whole_pair(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Tick Increment Numeric Negative Ten Pair: 8 bytes ----------------------- */

typedef struct {
  uint8_t raw_tick_increment_numeric[7];      /* bytes 0 to 6 */
  uint8_t tick_increment_fraction_indicator;  /* byte 7 */
} TickIncrementNumericNegativeTenPair;

/* any Tick Increment Numeric Negative Ten Pair at all: every byte one the checker chooses */
static void any_tick_increment_numeric_negative_ten_pair(TickIncrementNumericNegativeTenPair *record) {
  for (size_t i = 0; i < 7; i++) { record->raw_tick_increment_numeric[i] = arbitrary(); }
  record->tick_increment_fraction_indicator = arbitrary();
}

/* Tick Increment Numeric Negative Ten Pair to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_tick_increment_numeric_negative_ten_pair(const TickIncrementNumericNegativeTenPair *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->raw_tick_increment_numeric[i]; }
  wire[at++] = record->tick_increment_fraction_indicator;

  return at;
}

/* Tick Increment Numeric Negative Ten Pair off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_tick_increment_numeric_negative_ten_pair(TickIncrementNumericNegativeTenPair *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { record->raw_tick_increment_numeric[i] = wire[at++]; }
  record->tick_increment_fraction_indicator = wire[at++];

  return at;
}

/* what was read of Tick Increment Numeric Negative Ten Pair is what was written, byte for byte */
static void equal_tick_increment_numeric_negative_ten_pair(const TickIncrementNumericNegativeTenPair *read, const TickIncrementNumericNegativeTenPair *written) {
  for (size_t i = 0; i < 7; i++) { assert(read->raw_tick_increment_numeric[i] == written->raw_tick_increment_numeric[i]); }
  assert(read->tick_increment_fraction_indicator == written->tick_increment_fraction_indicator);
}

/* Tick Increment Numeric Negative Ten Pair: written and read back, then read and written back */
static void check_tick_increment_numeric_negative_ten_pair(void) {
  TickIncrementNumericNegativeTenPair sent;
  TickIncrementNumericNegativeTenPair got;
  uint8_t wire[8];
  uint8_t again[8];

  any_tick_increment_numeric_negative_ten_pair(&sent);
  assert(encode_tick_increment_numeric_negative_ten_pair(&sent, wire, 0) == 8);
  assert(decode_tick_increment_numeric_negative_ten_pair(&got, wire, 0) == 8);
  equal_tick_increment_numeric_negative_ten_pair(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_tick_increment_numeric_negative_ten_pair(&got, wire, 0) == 8);
  assert(encode_tick_increment_numeric_negative_ten_pair(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Tick Increment Numeric Negative Hundred Pair: 8 bytes ------------------- */

typedef struct {
  uint8_t raw_tick_increment_numeric[7];      /* bytes 0 to 6 */
  uint8_t tick_increment_fraction_indicator;  /* byte 7 */
} TickIncrementNumericNegativeHundredPair;

/* any Tick Increment Numeric Negative Hundred Pair at all: every byte one the checker chooses */
static void any_tick_increment_numeric_negative_hundred_pair(TickIncrementNumericNegativeHundredPair *record) {
  for (size_t i = 0; i < 7; i++) { record->raw_tick_increment_numeric[i] = arbitrary(); }
  record->tick_increment_fraction_indicator = arbitrary();
}

/* Tick Increment Numeric Negative Hundred Pair to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_tick_increment_numeric_negative_hundred_pair(const TickIncrementNumericNegativeHundredPair *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->raw_tick_increment_numeric[i]; }
  wire[at++] = record->tick_increment_fraction_indicator;

  return at;
}

/* Tick Increment Numeric Negative Hundred Pair off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_tick_increment_numeric_negative_hundred_pair(TickIncrementNumericNegativeHundredPair *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { record->raw_tick_increment_numeric[i] = wire[at++]; }
  record->tick_increment_fraction_indicator = wire[at++];

  return at;
}

/* what was read of Tick Increment Numeric Negative Hundred Pair is what was written, byte for byte */
static void equal_tick_increment_numeric_negative_hundred_pair(const TickIncrementNumericNegativeHundredPair *read, const TickIncrementNumericNegativeHundredPair *written) {
  for (size_t i = 0; i < 7; i++) { assert(read->raw_tick_increment_numeric[i] == written->raw_tick_increment_numeric[i]); }
  assert(read->tick_increment_fraction_indicator == written->tick_increment_fraction_indicator);
}

/* Tick Increment Numeric Negative Hundred Pair: written and read back, then read and written back */
static void check_tick_increment_numeric_negative_hundred_pair(void) {
  TickIncrementNumericNegativeHundredPair sent;
  TickIncrementNumericNegativeHundredPair got;
  uint8_t wire[8];
  uint8_t again[8];

  any_tick_increment_numeric_negative_hundred_pair(&sent);
  assert(encode_tick_increment_numeric_negative_hundred_pair(&sent, wire, 0) == 8);
  assert(decode_tick_increment_numeric_negative_hundred_pair(&got, wire, 0) == 8);
  equal_tick_increment_numeric_negative_hundred_pair(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_tick_increment_numeric_negative_hundred_pair(&got, wire, 0) == 8);
  assert(encode_tick_increment_numeric_negative_hundred_pair(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Tick Increment Numeric Negative Thousand Pair: 8 bytes ------------------ */

typedef struct {
  uint8_t raw_tick_increment_numeric[7];      /* bytes 0 to 6 */
  uint8_t tick_increment_fraction_indicator;  /* byte 7 */
} TickIncrementNumericNegativeThousandPair;

/* any Tick Increment Numeric Negative Thousand Pair at all: every byte one the checker chooses */
static void any_tick_increment_numeric_negative_thousand_pair(TickIncrementNumericNegativeThousandPair *record) {
  for (size_t i = 0; i < 7; i++) { record->raw_tick_increment_numeric[i] = arbitrary(); }
  record->tick_increment_fraction_indicator = arbitrary();
}

/* Tick Increment Numeric Negative Thousand Pair to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_tick_increment_numeric_negative_thousand_pair(const TickIncrementNumericNegativeThousandPair *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->raw_tick_increment_numeric[i]; }
  wire[at++] = record->tick_increment_fraction_indicator;

  return at;
}

/* Tick Increment Numeric Negative Thousand Pair off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_tick_increment_numeric_negative_thousand_pair(TickIncrementNumericNegativeThousandPair *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { record->raw_tick_increment_numeric[i] = wire[at++]; }
  record->tick_increment_fraction_indicator = wire[at++];

  return at;
}

/* what was read of Tick Increment Numeric Negative Thousand Pair is what was written, byte for byte */
static void equal_tick_increment_numeric_negative_thousand_pair(const TickIncrementNumericNegativeThousandPair *read, const TickIncrementNumericNegativeThousandPair *written) {
  for (size_t i = 0; i < 7; i++) { assert(read->raw_tick_increment_numeric[i] == written->raw_tick_increment_numeric[i]); }
  assert(read->tick_increment_fraction_indicator == written->tick_increment_fraction_indicator);
}

/* Tick Increment Numeric Negative Thousand Pair: written and read back, then read and written back */
static void check_tick_increment_numeric_negative_thousand_pair(void) {
  TickIncrementNumericNegativeThousandPair sent;
  TickIncrementNumericNegativeThousandPair got;
  uint8_t wire[8];
  uint8_t again[8];

  any_tick_increment_numeric_negative_thousand_pair(&sent);
  assert(encode_tick_increment_numeric_negative_thousand_pair(&sent, wire, 0) == 8);
  assert(decode_tick_increment_numeric_negative_thousand_pair(&got, wire, 0) == 8);
  equal_tick_increment_numeric_negative_thousand_pair(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_tick_increment_numeric_negative_thousand_pair(&got, wire, 0) == 8);
  assert(encode_tick_increment_numeric_negative_thousand_pair(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Tick Increment Numeric Negative Ten Thousand Pair: 8 bytes -------------- */

typedef struct {
  uint8_t raw_tick_increment_numeric[7];      /* bytes 0 to 6 */
  uint8_t tick_increment_fraction_indicator;  /* byte 7 */
} TickIncrementNumericNegativeTenThousandPair;

/* any Tick Increment Numeric Negative Ten Thousand Pair at all: every byte one the checker chooses */
static void any_tick_increment_numeric_negative_ten_thousand_pair(TickIncrementNumericNegativeTenThousandPair *record) {
  for (size_t i = 0; i < 7; i++) { record->raw_tick_increment_numeric[i] = arbitrary(); }
  record->tick_increment_fraction_indicator = arbitrary();
}

/* Tick Increment Numeric Negative Ten Thousand Pair to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_tick_increment_numeric_negative_ten_thousand_pair(const TickIncrementNumericNegativeTenThousandPair *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->raw_tick_increment_numeric[i]; }
  wire[at++] = record->tick_increment_fraction_indicator;

  return at;
}

/* Tick Increment Numeric Negative Ten Thousand Pair off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_tick_increment_numeric_negative_ten_thousand_pair(TickIncrementNumericNegativeTenThousandPair *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { record->raw_tick_increment_numeric[i] = wire[at++]; }
  record->tick_increment_fraction_indicator = wire[at++];

  return at;
}

/* what was read of Tick Increment Numeric Negative Ten Thousand Pair is what was written, byte for byte */
static void equal_tick_increment_numeric_negative_ten_thousand_pair(const TickIncrementNumericNegativeTenThousandPair *read, const TickIncrementNumericNegativeTenThousandPair *written) {
  for (size_t i = 0; i < 7; i++) { assert(read->raw_tick_increment_numeric[i] == written->raw_tick_increment_numeric[i]); }
  assert(read->tick_increment_fraction_indicator == written->tick_increment_fraction_indicator);
}

/* Tick Increment Numeric Negative Ten Thousand Pair: written and read back, then read and written back */
static void check_tick_increment_numeric_negative_ten_thousand_pair(void) {
  TickIncrementNumericNegativeTenThousandPair sent;
  TickIncrementNumericNegativeTenThousandPair got;
  uint8_t wire[8];
  uint8_t again[8];

  any_tick_increment_numeric_negative_ten_thousand_pair(&sent);
  assert(encode_tick_increment_numeric_negative_ten_thousand_pair(&sent, wire, 0) == 8);
  assert(decode_tick_increment_numeric_negative_ten_thousand_pair(&got, wire, 0) == 8);
  equal_tick_increment_numeric_negative_ten_thousand_pair(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_tick_increment_numeric_negative_ten_thousand_pair(&got, wire, 0) == 8);
  assert(encode_tick_increment_numeric_negative_ten_thousand_pair(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Tick Increment Numeric Negative Hundred Thousand Pair: 8 bytes ---------- */

typedef struct {
  uint8_t raw_tick_increment_numeric[7];      /* bytes 0 to 6 */
  uint8_t tick_increment_fraction_indicator;  /* byte 7 */
} TickIncrementNumericNegativeHundredThousandPair;

/* any Tick Increment Numeric Negative Hundred Thousand Pair at all: every byte one the checker chooses */
static void any_tick_increment_numeric_negative_hundred_thousand_pair(TickIncrementNumericNegativeHundredThousandPair *record) {
  for (size_t i = 0; i < 7; i++) { record->raw_tick_increment_numeric[i] = arbitrary(); }
  record->tick_increment_fraction_indicator = arbitrary();
}

/* Tick Increment Numeric Negative Hundred Thousand Pair to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_tick_increment_numeric_negative_hundred_thousand_pair(const TickIncrementNumericNegativeHundredThousandPair *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->raw_tick_increment_numeric[i]; }
  wire[at++] = record->tick_increment_fraction_indicator;

  return at;
}

/* Tick Increment Numeric Negative Hundred Thousand Pair off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_tick_increment_numeric_negative_hundred_thousand_pair(TickIncrementNumericNegativeHundredThousandPair *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { record->raw_tick_increment_numeric[i] = wire[at++]; }
  record->tick_increment_fraction_indicator = wire[at++];

  return at;
}

/* what was read of Tick Increment Numeric Negative Hundred Thousand Pair is what was written, byte for byte */
static void equal_tick_increment_numeric_negative_hundred_thousand_pair(const TickIncrementNumericNegativeHundredThousandPair *read, const TickIncrementNumericNegativeHundredThousandPair *written) {
  for (size_t i = 0; i < 7; i++) { assert(read->raw_tick_increment_numeric[i] == written->raw_tick_increment_numeric[i]); }
  assert(read->tick_increment_fraction_indicator == written->tick_increment_fraction_indicator);
}

/* Tick Increment Numeric Negative Hundred Thousand Pair: written and read back, then read and written back */
static void check_tick_increment_numeric_negative_hundred_thousand_pair(void) {
  TickIncrementNumericNegativeHundredThousandPair sent;
  TickIncrementNumericNegativeHundredThousandPair got;
  uint8_t wire[8];
  uint8_t again[8];

  any_tick_increment_numeric_negative_hundred_thousand_pair(&sent);
  assert(encode_tick_increment_numeric_negative_hundred_thousand_pair(&sent, wire, 0) == 8);
  assert(decode_tick_increment_numeric_negative_hundred_thousand_pair(&got, wire, 0) == 8);
  equal_tick_increment_numeric_negative_hundred_thousand_pair(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_tick_increment_numeric_negative_hundred_thousand_pair(&got, wire, 0) == 8);
  assert(encode_tick_increment_numeric_negative_hundred_thousand_pair(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Tick Increment Numeric Negative Million Pair: 8 bytes ------------------- */

typedef struct {
  uint8_t raw_tick_increment_numeric[7];      /* bytes 0 to 6 */
  uint8_t tick_increment_fraction_indicator;  /* byte 7 */
} TickIncrementNumericNegativeMillionPair;

/* any Tick Increment Numeric Negative Million Pair at all: every byte one the checker chooses */
static void any_tick_increment_numeric_negative_million_pair(TickIncrementNumericNegativeMillionPair *record) {
  for (size_t i = 0; i < 7; i++) { record->raw_tick_increment_numeric[i] = arbitrary(); }
  record->tick_increment_fraction_indicator = arbitrary();
}

/* Tick Increment Numeric Negative Million Pair to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_tick_increment_numeric_negative_million_pair(const TickIncrementNumericNegativeMillionPair *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->raw_tick_increment_numeric[i]; }
  wire[at++] = record->tick_increment_fraction_indicator;

  return at;
}

/* Tick Increment Numeric Negative Million Pair off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_tick_increment_numeric_negative_million_pair(TickIncrementNumericNegativeMillionPair *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { record->raw_tick_increment_numeric[i] = wire[at++]; }
  record->tick_increment_fraction_indicator = wire[at++];

  return at;
}

/* what was read of Tick Increment Numeric Negative Million Pair is what was written, byte for byte */
static void equal_tick_increment_numeric_negative_million_pair(const TickIncrementNumericNegativeMillionPair *read, const TickIncrementNumericNegativeMillionPair *written) {
  for (size_t i = 0; i < 7; i++) { assert(read->raw_tick_increment_numeric[i] == written->raw_tick_increment_numeric[i]); }
  assert(read->tick_increment_fraction_indicator == written->tick_increment_fraction_indicator);
}

/* Tick Increment Numeric Negative Million Pair: written and read back, then read and written back */
static void check_tick_increment_numeric_negative_million_pair(void) {
  TickIncrementNumericNegativeMillionPair sent;
  TickIncrementNumericNegativeMillionPair got;
  uint8_t wire[8];
  uint8_t again[8];

  any_tick_increment_numeric_negative_million_pair(&sent);
  assert(encode_tick_increment_numeric_negative_million_pair(&sent, wire, 0) == 8);
  assert(decode_tick_increment_numeric_negative_million_pair(&got, wire, 0) == 8);
  equal_tick_increment_numeric_negative_million_pair(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_tick_increment_numeric_negative_million_pair(&got, wire, 0) == 8);
  assert(encode_tick_increment_numeric_negative_million_pair(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Tick Increment Raw Pair: 8 bytes ---------------------------------------- */

typedef struct {
  uint8_t tick_increment_raw[7];              /* bytes 0 to 6 */
  uint8_t tick_increment_fraction_indicator;  /* byte 7 */
} TickIncrementRawPair;

/* any Tick Increment Raw Pair at all: every byte one the checker chooses */
static void any_tick_increment_raw_pair(TickIncrementRawPair *record) {
  for (size_t i = 0; i < 7; i++) { record->tick_increment_raw[i] = arbitrary(); }
  record->tick_increment_fraction_indicator = arbitrary();
}

/* Tick Increment Raw Pair to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_tick_increment_raw_pair(const TickIncrementRawPair *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->tick_increment_raw[i]; }
  wire[at++] = record->tick_increment_fraction_indicator;

  return at;
}

/* Tick Increment Raw Pair off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_tick_increment_raw_pair(TickIncrementRawPair *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { record->tick_increment_raw[i] = wire[at++]; }
  record->tick_increment_fraction_indicator = wire[at++];

  return at;
}

/* what was read of Tick Increment Raw Pair is what was written, byte for byte */
static void equal_tick_increment_raw_pair(const TickIncrementRawPair *read, const TickIncrementRawPair *written) {
  for (size_t i = 0; i < 7; i++) { assert(read->tick_increment_raw[i] == written->tick_increment_raw[i]); }
  assert(read->tick_increment_fraction_indicator == written->tick_increment_fraction_indicator);
}

/* Tick Increment Raw Pair: written and read back, then read and written back */
static void check_tick_increment_raw_pair(void) {
  TickIncrementRawPair sent;
  TickIncrementRawPair got;
  uint8_t wire[8];
  uint8_t again[8];

  any_tick_increment_raw_pair(&sent);
  assert(encode_tick_increment_raw_pair(&sent, wire, 0) == 8);
  assert(decode_tick_increment_raw_pair(&got, wire, 0) == 8);
  equal_tick_increment_raw_pair(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_tick_increment_raw_pair(&got, wire, 0) == 8);
  assert(encode_tick_increment_raw_pair(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Tick Value Negative Whole Pair: 8 bytes --------------------------------- */

typedef struct {
  uint8_t raw_tick_value[7];              /* bytes 0 to 6 */
  uint8_t tick_value_fraction_indicator;  /* byte 7 */
} TickValueNegativeWholePair;

/* any Tick Value Negative Whole Pair at all: every byte one the checker chooses */
static void any_tick_value_negative_whole_pair(TickValueNegativeWholePair *record) {
  for (size_t i = 0; i < 7; i++) { record->raw_tick_value[i] = arbitrary(); }
  record->tick_value_fraction_indicator = arbitrary();
}

/* Tick Value Negative Whole Pair to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_tick_value_negative_whole_pair(const TickValueNegativeWholePair *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->raw_tick_value[i]; }
  wire[at++] = record->tick_value_fraction_indicator;

  return at;
}

/* Tick Value Negative Whole Pair off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_tick_value_negative_whole_pair(TickValueNegativeWholePair *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { record->raw_tick_value[i] = wire[at++]; }
  record->tick_value_fraction_indicator = wire[at++];

  return at;
}

/* what was read of Tick Value Negative Whole Pair is what was written, byte for byte */
static void equal_tick_value_negative_whole_pair(const TickValueNegativeWholePair *read, const TickValueNegativeWholePair *written) {
  for (size_t i = 0; i < 7; i++) { assert(read->raw_tick_value[i] == written->raw_tick_value[i]); }
  assert(read->tick_value_fraction_indicator == written->tick_value_fraction_indicator);
}

/* Tick Value Negative Whole Pair: written and read back, then read and written back */
static void check_tick_value_negative_whole_pair(void) {
  TickValueNegativeWholePair sent;
  TickValueNegativeWholePair got;
  uint8_t wire[8];
  uint8_t again[8];

  any_tick_value_negative_whole_pair(&sent);
  assert(encode_tick_value_negative_whole_pair(&sent, wire, 0) == 8);
  assert(decode_tick_value_negative_whole_pair(&got, wire, 0) == 8);
  equal_tick_value_negative_whole_pair(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_tick_value_negative_whole_pair(&got, wire, 0) == 8);
  assert(encode_tick_value_negative_whole_pair(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Tick Value Negative Ten Pair: 8 bytes ----------------------------------- */

typedef struct {
  uint8_t raw_tick_value[7];              /* bytes 0 to 6 */
  uint8_t tick_value_fraction_indicator;  /* byte 7 */
} TickValueNegativeTenPair;

/* any Tick Value Negative Ten Pair at all: every byte one the checker chooses */
static void any_tick_value_negative_ten_pair(TickValueNegativeTenPair *record) {
  for (size_t i = 0; i < 7; i++) { record->raw_tick_value[i] = arbitrary(); }
  record->tick_value_fraction_indicator = arbitrary();
}

/* Tick Value Negative Ten Pair to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_tick_value_negative_ten_pair(const TickValueNegativeTenPair *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->raw_tick_value[i]; }
  wire[at++] = record->tick_value_fraction_indicator;

  return at;
}

/* Tick Value Negative Ten Pair off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_tick_value_negative_ten_pair(TickValueNegativeTenPair *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { record->raw_tick_value[i] = wire[at++]; }
  record->tick_value_fraction_indicator = wire[at++];

  return at;
}

/* what was read of Tick Value Negative Ten Pair is what was written, byte for byte */
static void equal_tick_value_negative_ten_pair(const TickValueNegativeTenPair *read, const TickValueNegativeTenPair *written) {
  for (size_t i = 0; i < 7; i++) { assert(read->raw_tick_value[i] == written->raw_tick_value[i]); }
  assert(read->tick_value_fraction_indicator == written->tick_value_fraction_indicator);
}

/* Tick Value Negative Ten Pair: written and read back, then read and written back */
static void check_tick_value_negative_ten_pair(void) {
  TickValueNegativeTenPair sent;
  TickValueNegativeTenPair got;
  uint8_t wire[8];
  uint8_t again[8];

  any_tick_value_negative_ten_pair(&sent);
  assert(encode_tick_value_negative_ten_pair(&sent, wire, 0) == 8);
  assert(decode_tick_value_negative_ten_pair(&got, wire, 0) == 8);
  equal_tick_value_negative_ten_pair(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_tick_value_negative_ten_pair(&got, wire, 0) == 8);
  assert(encode_tick_value_negative_ten_pair(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Tick Value Negative Hundred Pair: 8 bytes ------------------------------- */

typedef struct {
  uint8_t raw_tick_value[7];              /* bytes 0 to 6 */
  uint8_t tick_value_fraction_indicator;  /* byte 7 */
} TickValueNegativeHundredPair;

/* any Tick Value Negative Hundred Pair at all: every byte one the checker chooses */
static void any_tick_value_negative_hundred_pair(TickValueNegativeHundredPair *record) {
  for (size_t i = 0; i < 7; i++) { record->raw_tick_value[i] = arbitrary(); }
  record->tick_value_fraction_indicator = arbitrary();
}

/* Tick Value Negative Hundred Pair to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_tick_value_negative_hundred_pair(const TickValueNegativeHundredPair *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->raw_tick_value[i]; }
  wire[at++] = record->tick_value_fraction_indicator;

  return at;
}

/* Tick Value Negative Hundred Pair off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_tick_value_negative_hundred_pair(TickValueNegativeHundredPair *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { record->raw_tick_value[i] = wire[at++]; }
  record->tick_value_fraction_indicator = wire[at++];

  return at;
}

/* what was read of Tick Value Negative Hundred Pair is what was written, byte for byte */
static void equal_tick_value_negative_hundred_pair(const TickValueNegativeHundredPair *read, const TickValueNegativeHundredPair *written) {
  for (size_t i = 0; i < 7; i++) { assert(read->raw_tick_value[i] == written->raw_tick_value[i]); }
  assert(read->tick_value_fraction_indicator == written->tick_value_fraction_indicator);
}

/* Tick Value Negative Hundred Pair: written and read back, then read and written back */
static void check_tick_value_negative_hundred_pair(void) {
  TickValueNegativeHundredPair sent;
  TickValueNegativeHundredPair got;
  uint8_t wire[8];
  uint8_t again[8];

  any_tick_value_negative_hundred_pair(&sent);
  assert(encode_tick_value_negative_hundred_pair(&sent, wire, 0) == 8);
  assert(decode_tick_value_negative_hundred_pair(&got, wire, 0) == 8);
  equal_tick_value_negative_hundred_pair(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_tick_value_negative_hundred_pair(&got, wire, 0) == 8);
  assert(encode_tick_value_negative_hundred_pair(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Tick Value Negative Thousand Pair: 8 bytes ------------------------------ */

typedef struct {
  uint8_t raw_tick_value[7];              /* bytes 0 to 6 */
  uint8_t tick_value_fraction_indicator;  /* byte 7 */
} TickValueNegativeThousandPair;

/* any Tick Value Negative Thousand Pair at all: every byte one the checker chooses */
static void any_tick_value_negative_thousand_pair(TickValueNegativeThousandPair *record) {
  for (size_t i = 0; i < 7; i++) { record->raw_tick_value[i] = arbitrary(); }
  record->tick_value_fraction_indicator = arbitrary();
}

/* Tick Value Negative Thousand Pair to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_tick_value_negative_thousand_pair(const TickValueNegativeThousandPair *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->raw_tick_value[i]; }
  wire[at++] = record->tick_value_fraction_indicator;

  return at;
}

/* Tick Value Negative Thousand Pair off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_tick_value_negative_thousand_pair(TickValueNegativeThousandPair *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { record->raw_tick_value[i] = wire[at++]; }
  record->tick_value_fraction_indicator = wire[at++];

  return at;
}

/* what was read of Tick Value Negative Thousand Pair is what was written, byte for byte */
static void equal_tick_value_negative_thousand_pair(const TickValueNegativeThousandPair *read, const TickValueNegativeThousandPair *written) {
  for (size_t i = 0; i < 7; i++) { assert(read->raw_tick_value[i] == written->raw_tick_value[i]); }
  assert(read->tick_value_fraction_indicator == written->tick_value_fraction_indicator);
}

/* Tick Value Negative Thousand Pair: written and read back, then read and written back */
static void check_tick_value_negative_thousand_pair(void) {
  TickValueNegativeThousandPair sent;
  TickValueNegativeThousandPair got;
  uint8_t wire[8];
  uint8_t again[8];

  any_tick_value_negative_thousand_pair(&sent);
  assert(encode_tick_value_negative_thousand_pair(&sent, wire, 0) == 8);
  assert(decode_tick_value_negative_thousand_pair(&got, wire, 0) == 8);
  equal_tick_value_negative_thousand_pair(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_tick_value_negative_thousand_pair(&got, wire, 0) == 8);
  assert(encode_tick_value_negative_thousand_pair(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Tick Value Negative Ten Thousand Pair: 8 bytes -------------------------- */

typedef struct {
  uint8_t raw_tick_value[7];              /* bytes 0 to 6 */
  uint8_t tick_value_fraction_indicator;  /* byte 7 */
} TickValueNegativeTenThousandPair;

/* any Tick Value Negative Ten Thousand Pair at all: every byte one the checker chooses */
static void any_tick_value_negative_ten_thousand_pair(TickValueNegativeTenThousandPair *record) {
  for (size_t i = 0; i < 7; i++) { record->raw_tick_value[i] = arbitrary(); }
  record->tick_value_fraction_indicator = arbitrary();
}

/* Tick Value Negative Ten Thousand Pair to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_tick_value_negative_ten_thousand_pair(const TickValueNegativeTenThousandPair *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->raw_tick_value[i]; }
  wire[at++] = record->tick_value_fraction_indicator;

  return at;
}

/* Tick Value Negative Ten Thousand Pair off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_tick_value_negative_ten_thousand_pair(TickValueNegativeTenThousandPair *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { record->raw_tick_value[i] = wire[at++]; }
  record->tick_value_fraction_indicator = wire[at++];

  return at;
}

/* what was read of Tick Value Negative Ten Thousand Pair is what was written, byte for byte */
static void equal_tick_value_negative_ten_thousand_pair(const TickValueNegativeTenThousandPair *read, const TickValueNegativeTenThousandPair *written) {
  for (size_t i = 0; i < 7; i++) { assert(read->raw_tick_value[i] == written->raw_tick_value[i]); }
  assert(read->tick_value_fraction_indicator == written->tick_value_fraction_indicator);
}

/* Tick Value Negative Ten Thousand Pair: written and read back, then read and written back */
static void check_tick_value_negative_ten_thousand_pair(void) {
  TickValueNegativeTenThousandPair sent;
  TickValueNegativeTenThousandPair got;
  uint8_t wire[8];
  uint8_t again[8];

  any_tick_value_negative_ten_thousand_pair(&sent);
  assert(encode_tick_value_negative_ten_thousand_pair(&sent, wire, 0) == 8);
  assert(decode_tick_value_negative_ten_thousand_pair(&got, wire, 0) == 8);
  equal_tick_value_negative_ten_thousand_pair(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_tick_value_negative_ten_thousand_pair(&got, wire, 0) == 8);
  assert(encode_tick_value_negative_ten_thousand_pair(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Tick Value Negative Hundred Thousand Pair: 8 bytes ---------------------- */

typedef struct {
  uint8_t raw_tick_value[7];              /* bytes 0 to 6 */
  uint8_t tick_value_fraction_indicator;  /* byte 7 */
} TickValueNegativeHundredThousandPair;

/* any Tick Value Negative Hundred Thousand Pair at all: every byte one the checker chooses */
static void any_tick_value_negative_hundred_thousand_pair(TickValueNegativeHundredThousandPair *record) {
  for (size_t i = 0; i < 7; i++) { record->raw_tick_value[i] = arbitrary(); }
  record->tick_value_fraction_indicator = arbitrary();
}

/* Tick Value Negative Hundred Thousand Pair to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_tick_value_negative_hundred_thousand_pair(const TickValueNegativeHundredThousandPair *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->raw_tick_value[i]; }
  wire[at++] = record->tick_value_fraction_indicator;

  return at;
}

/* Tick Value Negative Hundred Thousand Pair off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_tick_value_negative_hundred_thousand_pair(TickValueNegativeHundredThousandPair *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { record->raw_tick_value[i] = wire[at++]; }
  record->tick_value_fraction_indicator = wire[at++];

  return at;
}

/* what was read of Tick Value Negative Hundred Thousand Pair is what was written, byte for byte */
static void equal_tick_value_negative_hundred_thousand_pair(const TickValueNegativeHundredThousandPair *read, const TickValueNegativeHundredThousandPair *written) {
  for (size_t i = 0; i < 7; i++) { assert(read->raw_tick_value[i] == written->raw_tick_value[i]); }
  assert(read->tick_value_fraction_indicator == written->tick_value_fraction_indicator);
}

/* Tick Value Negative Hundred Thousand Pair: written and read back, then read and written back */
static void check_tick_value_negative_hundred_thousand_pair(void) {
  TickValueNegativeHundredThousandPair sent;
  TickValueNegativeHundredThousandPair got;
  uint8_t wire[8];
  uint8_t again[8];

  any_tick_value_negative_hundred_thousand_pair(&sent);
  assert(encode_tick_value_negative_hundred_thousand_pair(&sent, wire, 0) == 8);
  assert(decode_tick_value_negative_hundred_thousand_pair(&got, wire, 0) == 8);
  equal_tick_value_negative_hundred_thousand_pair(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_tick_value_negative_hundred_thousand_pair(&got, wire, 0) == 8);
  assert(encode_tick_value_negative_hundred_thousand_pair(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Tick Value Negative Million Pair: 8 bytes ------------------------------- */

typedef struct {
  uint8_t raw_tick_value[7];              /* bytes 0 to 6 */
  uint8_t tick_value_fraction_indicator;  /* byte 7 */
} TickValueNegativeMillionPair;

/* any Tick Value Negative Million Pair at all: every byte one the checker chooses */
static void any_tick_value_negative_million_pair(TickValueNegativeMillionPair *record) {
  for (size_t i = 0; i < 7; i++) { record->raw_tick_value[i] = arbitrary(); }
  record->tick_value_fraction_indicator = arbitrary();
}

/* Tick Value Negative Million Pair to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_tick_value_negative_million_pair(const TickValueNegativeMillionPair *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->raw_tick_value[i]; }
  wire[at++] = record->tick_value_fraction_indicator;

  return at;
}

/* Tick Value Negative Million Pair off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_tick_value_negative_million_pair(TickValueNegativeMillionPair *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { record->raw_tick_value[i] = wire[at++]; }
  record->tick_value_fraction_indicator = wire[at++];

  return at;
}

/* what was read of Tick Value Negative Million Pair is what was written, byte for byte */
static void equal_tick_value_negative_million_pair(const TickValueNegativeMillionPair *read, const TickValueNegativeMillionPair *written) {
  for (size_t i = 0; i < 7; i++) { assert(read->raw_tick_value[i] == written->raw_tick_value[i]); }
  assert(read->tick_value_fraction_indicator == written->tick_value_fraction_indicator);
}

/* Tick Value Negative Million Pair: written and read back, then read and written back */
static void check_tick_value_negative_million_pair(void) {
  TickValueNegativeMillionPair sent;
  TickValueNegativeMillionPair got;
  uint8_t wire[8];
  uint8_t again[8];

  any_tick_value_negative_million_pair(&sent);
  assert(encode_tick_value_negative_million_pair(&sent, wire, 0) == 8);
  assert(decode_tick_value_negative_million_pair(&got, wire, 0) == 8);
  equal_tick_value_negative_million_pair(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_tick_value_negative_million_pair(&got, wire, 0) == 8);
  assert(encode_tick_value_negative_million_pair(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Tick Value Numeric Pair: 8 bytes ---------------------------------------- */

typedef struct {
  uint8_t tick_value[7];                  /* bytes 0 to 6 */
  uint8_t tick_value_fraction_indicator;  /* byte 7 */
} TickValueNumericPair;

/* any Tick Value Numeric Pair at all: every byte one the checker chooses */
static void any_tick_value_numeric_pair(TickValueNumericPair *record) {
  for (size_t i = 0; i < 7; i++) { record->tick_value[i] = arbitrary(); }
  record->tick_value_fraction_indicator = arbitrary();
}

/* Tick Value Numeric Pair to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_tick_value_numeric_pair(const TickValueNumericPair *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->tick_value[i]; }
  wire[at++] = record->tick_value_fraction_indicator;

  return at;
}

/* Tick Value Numeric Pair off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_tick_value_numeric_pair(TickValueNumericPair *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { record->tick_value[i] = wire[at++]; }
  record->tick_value_fraction_indicator = wire[at++];

  return at;
}

/* what was read of Tick Value Numeric Pair is what was written, byte for byte */
static void equal_tick_value_numeric_pair(const TickValueNumericPair *read, const TickValueNumericPair *written) {
  for (size_t i = 0; i < 7; i++) { assert(read->tick_value[i] == written->tick_value[i]); }
  assert(read->tick_value_fraction_indicator == written->tick_value_fraction_indicator);
}

/* Tick Value Numeric Pair: written and read back, then read and written back */
static void check_tick_value_numeric_pair(void) {
  TickValueNumericPair sent;
  TickValueNumericPair got;
  uint8_t wire[8];
  uint8_t again[8];

  any_tick_value_numeric_pair(&sent);
  assert(encode_tick_value_numeric_pair(&sent, wire, 0) == 8);
  assert(decode_tick_value_numeric_pair(&got, wire, 0) == 8);
  equal_tick_value_numeric_pair(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_tick_value_numeric_pair(&got, wire, 0) == 8);
  assert(encode_tick_value_numeric_pair(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Underlying Instrument Keys Message: 49 bytes ---------------------------- */

/* The 'Underlying Instrument Keys' message will be the first messages sent during the day. There is no 'Underlying Summary' message attached to the 'Instrument Keys' messages */
typedef struct {
  LongMessageHeader long_message_header;  /* bytes 0 to 11 */
  uint8_t exchange_id;                    /* byte 12 */
  uint8_t group_instrument[2];            /* bytes 13 to 14 */
  uint8_t instrument[4];                  /* bytes 15 to 18 */
  uint8_t instrument_external_code[30];   /* bytes 19 to 48 */
} UnderlyingInstrumentKeysMessage;

/* any Underlying Instrument Keys Message at all: every byte one the checker chooses */
static void any_underlying_instrument_keys_message(UnderlyingInstrumentKeysMessage *record) {
  any_long_message_header(&record->long_message_header);
  record->exchange_id = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->group_instrument[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->instrument[i] = arbitrary(); }
  for (size_t i = 0; i < 30; i++) { record->instrument_external_code[i] = arbitrary(); }
}

/* Underlying Instrument Keys Message to the wire: 49 bytes from at, returning where the next byte goes */
static size_t encode_underlying_instrument_keys_message(const UnderlyingInstrumentKeysMessage *record, uint8_t *wire, size_t at) {
  at = encode_long_message_header(&record->long_message_header, wire, at);
  wire[at++] = record->exchange_id;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->group_instrument[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument[i]; }
  for (size_t i = 0; i < 30; i++) { wire[at++] = record->instrument_external_code[i]; }

  return at;
}

/* Underlying Instrument Keys Message off the wire: 49 bytes from at, returning where the next byte lies */
static size_t decode_underlying_instrument_keys_message(UnderlyingInstrumentKeysMessage *record, const uint8_t *wire, size_t at) {
  at = decode_long_message_header(&record->long_message_header, wire, at);
  record->exchange_id = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->group_instrument[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->instrument[i] = wire[at++]; }
  for (size_t i = 0; i < 30; i++) { record->instrument_external_code[i] = wire[at++]; }

  return at;
}

/* what was read of Underlying Instrument Keys Message is what was written, byte for byte */
static void equal_underlying_instrument_keys_message(const UnderlyingInstrumentKeysMessage *read, const UnderlyingInstrumentKeysMessage *written) {
  equal_long_message_header(&read->long_message_header, &written->long_message_header);
  assert(read->exchange_id == written->exchange_id);
  for (size_t i = 0; i < 2; i++) { assert(read->group_instrument[i] == written->group_instrument[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->instrument[i] == written->instrument[i]); }
  for (size_t i = 0; i < 30; i++) { assert(read->instrument_external_code[i] == written->instrument_external_code[i]); }
}

/* Underlying Instrument Keys Message: written and read back, then read and written back */
static void check_underlying_instrument_keys_message(void) {
  UnderlyingInstrumentKeysMessage sent;
  UnderlyingInstrumentKeysMessage got;
  uint8_t wire[49];
  uint8_t again[49];

  any_underlying_instrument_keys_message(&sent);
  assert(encode_underlying_instrument_keys_message(&sent, wire, 0) == 49);
  assert(decode_underlying_instrument_keys_message(&got, wire, 0) == 49);
  equal_underlying_instrument_keys_message(&got, &sent);

  for (size_t i = 0; i < 49; i++) { wire[i] = arbitrary(); }
  assert(decode_underlying_instrument_keys_message(&got, wire, 0) == 49);
  assert(encode_underlying_instrument_keys_message(&got, again, 0) == 49);
  for (size_t i = 0; i < 49; i++) { assert(again[i] == wire[i]); }
}

/* ---- Maximum Threshold Price Futures Negative Whole Pair: 8 bytes ------------ */

typedef struct {
  uint8_t raw_maximum_threshold_price_futures[7];      /* bytes 0 to 6 */
  uint8_t maximum_threshold_price_fraction_indicator;  /* byte 7 */
} MaximumThresholdPriceFuturesNegativeWholePair;

/* any Maximum Threshold Price Futures Negative Whole Pair at all: every byte one the checker chooses */
static void any_maximum_threshold_price_futures_negative_whole_pair(MaximumThresholdPriceFuturesNegativeWholePair *record) {
  for (size_t i = 0; i < 7; i++) { record->raw_maximum_threshold_price_futures[i] = arbitrary(); }
  record->maximum_threshold_price_fraction_indicator = arbitrary();
}

/* Maximum Threshold Price Futures Negative Whole Pair to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_maximum_threshold_price_futures_negative_whole_pair(const MaximumThresholdPriceFuturesNegativeWholePair *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->raw_maximum_threshold_price_futures[i]; }
  wire[at++] = record->maximum_threshold_price_fraction_indicator;

  return at;
}

/* Maximum Threshold Price Futures Negative Whole Pair off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_maximum_threshold_price_futures_negative_whole_pair(MaximumThresholdPriceFuturesNegativeWholePair *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { record->raw_maximum_threshold_price_futures[i] = wire[at++]; }
  record->maximum_threshold_price_fraction_indicator = wire[at++];

  return at;
}

/* what was read of Maximum Threshold Price Futures Negative Whole Pair is what was written, byte for byte */
static void equal_maximum_threshold_price_futures_negative_whole_pair(const MaximumThresholdPriceFuturesNegativeWholePair *read, const MaximumThresholdPriceFuturesNegativeWholePair *written) {
  for (size_t i = 0; i < 7; i++) { assert(read->raw_maximum_threshold_price_futures[i] == written->raw_maximum_threshold_price_futures[i]); }
  assert(read->maximum_threshold_price_fraction_indicator == written->maximum_threshold_price_fraction_indicator);
}

/* Maximum Threshold Price Futures Negative Whole Pair: written and read back, then read and written back */
static void check_maximum_threshold_price_futures_negative_whole_pair(void) {
  MaximumThresholdPriceFuturesNegativeWholePair sent;
  MaximumThresholdPriceFuturesNegativeWholePair got;
  uint8_t wire[8];
  uint8_t again[8];

  any_maximum_threshold_price_futures_negative_whole_pair(&sent);
  assert(encode_maximum_threshold_price_futures_negative_whole_pair(&sent, wire, 0) == 8);
  assert(decode_maximum_threshold_price_futures_negative_whole_pair(&got, wire, 0) == 8);
  equal_maximum_threshold_price_futures_negative_whole_pair(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_maximum_threshold_price_futures_negative_whole_pair(&got, wire, 0) == 8);
  assert(encode_maximum_threshold_price_futures_negative_whole_pair(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Maximum Threshold Price Futures Negative Ten Pair: 8 bytes -------------- */

typedef struct {
  uint8_t raw_maximum_threshold_price_futures[7];      /* bytes 0 to 6 */
  uint8_t maximum_threshold_price_fraction_indicator;  /* byte 7 */
} MaximumThresholdPriceFuturesNegativeTenPair;

/* any Maximum Threshold Price Futures Negative Ten Pair at all: every byte one the checker chooses */
static void any_maximum_threshold_price_futures_negative_ten_pair(MaximumThresholdPriceFuturesNegativeTenPair *record) {
  for (size_t i = 0; i < 7; i++) { record->raw_maximum_threshold_price_futures[i] = arbitrary(); }
  record->maximum_threshold_price_fraction_indicator = arbitrary();
}

/* Maximum Threshold Price Futures Negative Ten Pair to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_maximum_threshold_price_futures_negative_ten_pair(const MaximumThresholdPriceFuturesNegativeTenPair *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->raw_maximum_threshold_price_futures[i]; }
  wire[at++] = record->maximum_threshold_price_fraction_indicator;

  return at;
}

/* Maximum Threshold Price Futures Negative Ten Pair off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_maximum_threshold_price_futures_negative_ten_pair(MaximumThresholdPriceFuturesNegativeTenPair *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { record->raw_maximum_threshold_price_futures[i] = wire[at++]; }
  record->maximum_threshold_price_fraction_indicator = wire[at++];

  return at;
}

/* what was read of Maximum Threshold Price Futures Negative Ten Pair is what was written, byte for byte */
static void equal_maximum_threshold_price_futures_negative_ten_pair(const MaximumThresholdPriceFuturesNegativeTenPair *read, const MaximumThresholdPriceFuturesNegativeTenPair *written) {
  for (size_t i = 0; i < 7; i++) { assert(read->raw_maximum_threshold_price_futures[i] == written->raw_maximum_threshold_price_futures[i]); }
  assert(read->maximum_threshold_price_fraction_indicator == written->maximum_threshold_price_fraction_indicator);
}

/* Maximum Threshold Price Futures Negative Ten Pair: written and read back, then read and written back */
static void check_maximum_threshold_price_futures_negative_ten_pair(void) {
  MaximumThresholdPriceFuturesNegativeTenPair sent;
  MaximumThresholdPriceFuturesNegativeTenPair got;
  uint8_t wire[8];
  uint8_t again[8];

  any_maximum_threshold_price_futures_negative_ten_pair(&sent);
  assert(encode_maximum_threshold_price_futures_negative_ten_pair(&sent, wire, 0) == 8);
  assert(decode_maximum_threshold_price_futures_negative_ten_pair(&got, wire, 0) == 8);
  equal_maximum_threshold_price_futures_negative_ten_pair(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_maximum_threshold_price_futures_negative_ten_pair(&got, wire, 0) == 8);
  assert(encode_maximum_threshold_price_futures_negative_ten_pair(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Maximum Threshold Price Futures Negative Hundred Pair: 8 bytes ---------- */

typedef struct {
  uint8_t raw_maximum_threshold_price_futures[7];      /* bytes 0 to 6 */
  uint8_t maximum_threshold_price_fraction_indicator;  /* byte 7 */
} MaximumThresholdPriceFuturesNegativeHundredPair;

/* any Maximum Threshold Price Futures Negative Hundred Pair at all: every byte one the checker chooses */
static void any_maximum_threshold_price_futures_negative_hundred_pair(MaximumThresholdPriceFuturesNegativeHundredPair *record) {
  for (size_t i = 0; i < 7; i++) { record->raw_maximum_threshold_price_futures[i] = arbitrary(); }
  record->maximum_threshold_price_fraction_indicator = arbitrary();
}

/* Maximum Threshold Price Futures Negative Hundred Pair to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_maximum_threshold_price_futures_negative_hundred_pair(const MaximumThresholdPriceFuturesNegativeHundredPair *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->raw_maximum_threshold_price_futures[i]; }
  wire[at++] = record->maximum_threshold_price_fraction_indicator;

  return at;
}

/* Maximum Threshold Price Futures Negative Hundred Pair off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_maximum_threshold_price_futures_negative_hundred_pair(MaximumThresholdPriceFuturesNegativeHundredPair *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { record->raw_maximum_threshold_price_futures[i] = wire[at++]; }
  record->maximum_threshold_price_fraction_indicator = wire[at++];

  return at;
}

/* what was read of Maximum Threshold Price Futures Negative Hundred Pair is what was written, byte for byte */
static void equal_maximum_threshold_price_futures_negative_hundred_pair(const MaximumThresholdPriceFuturesNegativeHundredPair *read, const MaximumThresholdPriceFuturesNegativeHundredPair *written) {
  for (size_t i = 0; i < 7; i++) { assert(read->raw_maximum_threshold_price_futures[i] == written->raw_maximum_threshold_price_futures[i]); }
  assert(read->maximum_threshold_price_fraction_indicator == written->maximum_threshold_price_fraction_indicator);
}

/* Maximum Threshold Price Futures Negative Hundred Pair: written and read back, then read and written back */
static void check_maximum_threshold_price_futures_negative_hundred_pair(void) {
  MaximumThresholdPriceFuturesNegativeHundredPair sent;
  MaximumThresholdPriceFuturesNegativeHundredPair got;
  uint8_t wire[8];
  uint8_t again[8];

  any_maximum_threshold_price_futures_negative_hundred_pair(&sent);
  assert(encode_maximum_threshold_price_futures_negative_hundred_pair(&sent, wire, 0) == 8);
  assert(decode_maximum_threshold_price_futures_negative_hundred_pair(&got, wire, 0) == 8);
  equal_maximum_threshold_price_futures_negative_hundred_pair(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_maximum_threshold_price_futures_negative_hundred_pair(&got, wire, 0) == 8);
  assert(encode_maximum_threshold_price_futures_negative_hundred_pair(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Maximum Threshold Price Futures Negative Thousand Pair: 8 bytes --------- */

typedef struct {
  uint8_t raw_maximum_threshold_price_futures[7];      /* bytes 0 to 6 */
  uint8_t maximum_threshold_price_fraction_indicator;  /* byte 7 */
} MaximumThresholdPriceFuturesNegativeThousandPair;

/* any Maximum Threshold Price Futures Negative Thousand Pair at all: every byte one the checker chooses */
static void any_maximum_threshold_price_futures_negative_thousand_pair(MaximumThresholdPriceFuturesNegativeThousandPair *record) {
  for (size_t i = 0; i < 7; i++) { record->raw_maximum_threshold_price_futures[i] = arbitrary(); }
  record->maximum_threshold_price_fraction_indicator = arbitrary();
}

/* Maximum Threshold Price Futures Negative Thousand Pair to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_maximum_threshold_price_futures_negative_thousand_pair(const MaximumThresholdPriceFuturesNegativeThousandPair *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->raw_maximum_threshold_price_futures[i]; }
  wire[at++] = record->maximum_threshold_price_fraction_indicator;

  return at;
}

/* Maximum Threshold Price Futures Negative Thousand Pair off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_maximum_threshold_price_futures_negative_thousand_pair(MaximumThresholdPriceFuturesNegativeThousandPair *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { record->raw_maximum_threshold_price_futures[i] = wire[at++]; }
  record->maximum_threshold_price_fraction_indicator = wire[at++];

  return at;
}

/* what was read of Maximum Threshold Price Futures Negative Thousand Pair is what was written, byte for byte */
static void equal_maximum_threshold_price_futures_negative_thousand_pair(const MaximumThresholdPriceFuturesNegativeThousandPair *read, const MaximumThresholdPriceFuturesNegativeThousandPair *written) {
  for (size_t i = 0; i < 7; i++) { assert(read->raw_maximum_threshold_price_futures[i] == written->raw_maximum_threshold_price_futures[i]); }
  assert(read->maximum_threshold_price_fraction_indicator == written->maximum_threshold_price_fraction_indicator);
}

/* Maximum Threshold Price Futures Negative Thousand Pair: written and read back, then read and written back */
static void check_maximum_threshold_price_futures_negative_thousand_pair(void) {
  MaximumThresholdPriceFuturesNegativeThousandPair sent;
  MaximumThresholdPriceFuturesNegativeThousandPair got;
  uint8_t wire[8];
  uint8_t again[8];

  any_maximum_threshold_price_futures_negative_thousand_pair(&sent);
  assert(encode_maximum_threshold_price_futures_negative_thousand_pair(&sent, wire, 0) == 8);
  assert(decode_maximum_threshold_price_futures_negative_thousand_pair(&got, wire, 0) == 8);
  equal_maximum_threshold_price_futures_negative_thousand_pair(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_maximum_threshold_price_futures_negative_thousand_pair(&got, wire, 0) == 8);
  assert(encode_maximum_threshold_price_futures_negative_thousand_pair(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Maximum Threshold Price Futures Negative Ten Thousand Pair: 8 bytes ----- */

typedef struct {
  uint8_t raw_maximum_threshold_price_futures[7];      /* bytes 0 to 6 */
  uint8_t maximum_threshold_price_fraction_indicator;  /* byte 7 */
} MaximumThresholdPriceFuturesNegativeTenThousandPair;

/* any Maximum Threshold Price Futures Negative Ten Thousand Pair at all: every byte one the checker chooses */
static void any_maximum_threshold_price_futures_negative_ten_thousand_pair(MaximumThresholdPriceFuturesNegativeTenThousandPair *record) {
  for (size_t i = 0; i < 7; i++) { record->raw_maximum_threshold_price_futures[i] = arbitrary(); }
  record->maximum_threshold_price_fraction_indicator = arbitrary();
}

/* Maximum Threshold Price Futures Negative Ten Thousand Pair to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_maximum_threshold_price_futures_negative_ten_thousand_pair(const MaximumThresholdPriceFuturesNegativeTenThousandPair *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->raw_maximum_threshold_price_futures[i]; }
  wire[at++] = record->maximum_threshold_price_fraction_indicator;

  return at;
}

/* Maximum Threshold Price Futures Negative Ten Thousand Pair off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_maximum_threshold_price_futures_negative_ten_thousand_pair(MaximumThresholdPriceFuturesNegativeTenThousandPair *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { record->raw_maximum_threshold_price_futures[i] = wire[at++]; }
  record->maximum_threshold_price_fraction_indicator = wire[at++];

  return at;
}

/* what was read of Maximum Threshold Price Futures Negative Ten Thousand Pair is what was written, byte for byte */
static void equal_maximum_threshold_price_futures_negative_ten_thousand_pair(const MaximumThresholdPriceFuturesNegativeTenThousandPair *read, const MaximumThresholdPriceFuturesNegativeTenThousandPair *written) {
  for (size_t i = 0; i < 7; i++) { assert(read->raw_maximum_threshold_price_futures[i] == written->raw_maximum_threshold_price_futures[i]); }
  assert(read->maximum_threshold_price_fraction_indicator == written->maximum_threshold_price_fraction_indicator);
}

/* Maximum Threshold Price Futures Negative Ten Thousand Pair: written and read back, then read and written back */
static void check_maximum_threshold_price_futures_negative_ten_thousand_pair(void) {
  MaximumThresholdPriceFuturesNegativeTenThousandPair sent;
  MaximumThresholdPriceFuturesNegativeTenThousandPair got;
  uint8_t wire[8];
  uint8_t again[8];

  any_maximum_threshold_price_futures_negative_ten_thousand_pair(&sent);
  assert(encode_maximum_threshold_price_futures_negative_ten_thousand_pair(&sent, wire, 0) == 8);
  assert(decode_maximum_threshold_price_futures_negative_ten_thousand_pair(&got, wire, 0) == 8);
  equal_maximum_threshold_price_futures_negative_ten_thousand_pair(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_maximum_threshold_price_futures_negative_ten_thousand_pair(&got, wire, 0) == 8);
  assert(encode_maximum_threshold_price_futures_negative_ten_thousand_pair(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Maximum Threshold Price Futures Negative Hundred Thousand Pair: 8 bytes ---- */

typedef struct {
  uint8_t raw_maximum_threshold_price_futures[7];      /* bytes 0 to 6 */
  uint8_t maximum_threshold_price_fraction_indicator;  /* byte 7 */
} MaximumThresholdPriceFuturesNegativeHundredThousandPair;

/* any Maximum Threshold Price Futures Negative Hundred Thousand Pair at all: every byte one the checker chooses */
static void any_maximum_threshold_price_futures_negative_hundred_thousand_pair(MaximumThresholdPriceFuturesNegativeHundredThousandPair *record) {
  for (size_t i = 0; i < 7; i++) { record->raw_maximum_threshold_price_futures[i] = arbitrary(); }
  record->maximum_threshold_price_fraction_indicator = arbitrary();
}

/* Maximum Threshold Price Futures Negative Hundred Thousand Pair to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_maximum_threshold_price_futures_negative_hundred_thousand_pair(const MaximumThresholdPriceFuturesNegativeHundredThousandPair *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->raw_maximum_threshold_price_futures[i]; }
  wire[at++] = record->maximum_threshold_price_fraction_indicator;

  return at;
}

/* Maximum Threshold Price Futures Negative Hundred Thousand Pair off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_maximum_threshold_price_futures_negative_hundred_thousand_pair(MaximumThresholdPriceFuturesNegativeHundredThousandPair *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { record->raw_maximum_threshold_price_futures[i] = wire[at++]; }
  record->maximum_threshold_price_fraction_indicator = wire[at++];

  return at;
}

/* what was read of Maximum Threshold Price Futures Negative Hundred Thousand Pair is what was written, byte for byte */
static void equal_maximum_threshold_price_futures_negative_hundred_thousand_pair(const MaximumThresholdPriceFuturesNegativeHundredThousandPair *read, const MaximumThresholdPriceFuturesNegativeHundredThousandPair *written) {
  for (size_t i = 0; i < 7; i++) { assert(read->raw_maximum_threshold_price_futures[i] == written->raw_maximum_threshold_price_futures[i]); }
  assert(read->maximum_threshold_price_fraction_indicator == written->maximum_threshold_price_fraction_indicator);
}

/* Maximum Threshold Price Futures Negative Hundred Thousand Pair: written and read back, then read and written back */
static void check_maximum_threshold_price_futures_negative_hundred_thousand_pair(void) {
  MaximumThresholdPriceFuturesNegativeHundredThousandPair sent;
  MaximumThresholdPriceFuturesNegativeHundredThousandPair got;
  uint8_t wire[8];
  uint8_t again[8];

  any_maximum_threshold_price_futures_negative_hundred_thousand_pair(&sent);
  assert(encode_maximum_threshold_price_futures_negative_hundred_thousand_pair(&sent, wire, 0) == 8);
  assert(decode_maximum_threshold_price_futures_negative_hundred_thousand_pair(&got, wire, 0) == 8);
  equal_maximum_threshold_price_futures_negative_hundred_thousand_pair(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_maximum_threshold_price_futures_negative_hundred_thousand_pair(&got, wire, 0) == 8);
  assert(encode_maximum_threshold_price_futures_negative_hundred_thousand_pair(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Maximum Threshold Price Futures Negative Million Pair: 8 bytes ---------- */

typedef struct {
  uint8_t raw_maximum_threshold_price_futures[7];      /* bytes 0 to 6 */
  uint8_t maximum_threshold_price_fraction_indicator;  /* byte 7 */
} MaximumThresholdPriceFuturesNegativeMillionPair;

/* any Maximum Threshold Price Futures Negative Million Pair at all: every byte one the checker chooses */
static void any_maximum_threshold_price_futures_negative_million_pair(MaximumThresholdPriceFuturesNegativeMillionPair *record) {
  for (size_t i = 0; i < 7; i++) { record->raw_maximum_threshold_price_futures[i] = arbitrary(); }
  record->maximum_threshold_price_fraction_indicator = arbitrary();
}

/* Maximum Threshold Price Futures Negative Million Pair to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_maximum_threshold_price_futures_negative_million_pair(const MaximumThresholdPriceFuturesNegativeMillionPair *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->raw_maximum_threshold_price_futures[i]; }
  wire[at++] = record->maximum_threshold_price_fraction_indicator;

  return at;
}

/* Maximum Threshold Price Futures Negative Million Pair off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_maximum_threshold_price_futures_negative_million_pair(MaximumThresholdPriceFuturesNegativeMillionPair *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { record->raw_maximum_threshold_price_futures[i] = wire[at++]; }
  record->maximum_threshold_price_fraction_indicator = wire[at++];

  return at;
}

/* what was read of Maximum Threshold Price Futures Negative Million Pair is what was written, byte for byte */
static void equal_maximum_threshold_price_futures_negative_million_pair(const MaximumThresholdPriceFuturesNegativeMillionPair *read, const MaximumThresholdPriceFuturesNegativeMillionPair *written) {
  for (size_t i = 0; i < 7; i++) { assert(read->raw_maximum_threshold_price_futures[i] == written->raw_maximum_threshold_price_futures[i]); }
  assert(read->maximum_threshold_price_fraction_indicator == written->maximum_threshold_price_fraction_indicator);
}

/* Maximum Threshold Price Futures Negative Million Pair: written and read back, then read and written back */
static void check_maximum_threshold_price_futures_negative_million_pair(void) {
  MaximumThresholdPriceFuturesNegativeMillionPair sent;
  MaximumThresholdPriceFuturesNegativeMillionPair got;
  uint8_t wire[8];
  uint8_t again[8];

  any_maximum_threshold_price_futures_negative_million_pair(&sent);
  assert(encode_maximum_threshold_price_futures_negative_million_pair(&sent, wire, 0) == 8);
  assert(decode_maximum_threshold_price_futures_negative_million_pair(&got, wire, 0) == 8);
  equal_maximum_threshold_price_futures_negative_million_pair(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_maximum_threshold_price_futures_negative_million_pair(&got, wire, 0) == 8);
  assert(encode_maximum_threshold_price_futures_negative_million_pair(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Maximum Threshold Price Futures Numeric Pair: 8 bytes ------------------- */

typedef struct {
  uint8_t maximum_threshold_price_futures[7];          /* bytes 0 to 6 */
  uint8_t maximum_threshold_price_fraction_indicator;  /* byte 7 */
} MaximumThresholdPriceFuturesNumericPair;

/* any Maximum Threshold Price Futures Numeric Pair at all: every byte one the checker chooses */
static void any_maximum_threshold_price_futures_numeric_pair(MaximumThresholdPriceFuturesNumericPair *record) {
  for (size_t i = 0; i < 7; i++) { record->maximum_threshold_price_futures[i] = arbitrary(); }
  record->maximum_threshold_price_fraction_indicator = arbitrary();
}

/* Maximum Threshold Price Futures Numeric Pair to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_maximum_threshold_price_futures_numeric_pair(const MaximumThresholdPriceFuturesNumericPair *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->maximum_threshold_price_futures[i]; }
  wire[at++] = record->maximum_threshold_price_fraction_indicator;

  return at;
}

/* Maximum Threshold Price Futures Numeric Pair off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_maximum_threshold_price_futures_numeric_pair(MaximumThresholdPriceFuturesNumericPair *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { record->maximum_threshold_price_futures[i] = wire[at++]; }
  record->maximum_threshold_price_fraction_indicator = wire[at++];

  return at;
}

/* what was read of Maximum Threshold Price Futures Numeric Pair is what was written, byte for byte */
static void equal_maximum_threshold_price_futures_numeric_pair(const MaximumThresholdPriceFuturesNumericPair *read, const MaximumThresholdPriceFuturesNumericPair *written) {
  for (size_t i = 0; i < 7; i++) { assert(read->maximum_threshold_price_futures[i] == written->maximum_threshold_price_futures[i]); }
  assert(read->maximum_threshold_price_fraction_indicator == written->maximum_threshold_price_fraction_indicator);
}

/* Maximum Threshold Price Futures Numeric Pair: written and read back, then read and written back */
static void check_maximum_threshold_price_futures_numeric_pair(void) {
  MaximumThresholdPriceFuturesNumericPair sent;
  MaximumThresholdPriceFuturesNumericPair got;
  uint8_t wire[8];
  uint8_t again[8];

  any_maximum_threshold_price_futures_numeric_pair(&sent);
  assert(encode_maximum_threshold_price_futures_numeric_pair(&sent, wire, 0) == 8);
  assert(decode_maximum_threshold_price_futures_numeric_pair(&got, wire, 0) == 8);
  equal_maximum_threshold_price_futures_numeric_pair(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_maximum_threshold_price_futures_numeric_pair(&got, wire, 0) == 8);
  assert(encode_maximum_threshold_price_futures_numeric_pair(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Minimum Threshold Price Futures Negative Whole Pair: 8 bytes ------------ */

typedef struct {
  uint8_t raw_minimum_threshold_price_futures[7];      /* bytes 0 to 6 */
  uint8_t minimum_threshold_price_fraction_indicator;  /* byte 7 */
} MinimumThresholdPriceFuturesNegativeWholePair;

/* any Minimum Threshold Price Futures Negative Whole Pair at all: every byte one the checker chooses */
static void any_minimum_threshold_price_futures_negative_whole_pair(MinimumThresholdPriceFuturesNegativeWholePair *record) {
  for (size_t i = 0; i < 7; i++) { record->raw_minimum_threshold_price_futures[i] = arbitrary(); }
  record->minimum_threshold_price_fraction_indicator = arbitrary();
}

/* Minimum Threshold Price Futures Negative Whole Pair to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_minimum_threshold_price_futures_negative_whole_pair(const MinimumThresholdPriceFuturesNegativeWholePair *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->raw_minimum_threshold_price_futures[i]; }
  wire[at++] = record->minimum_threshold_price_fraction_indicator;

  return at;
}

/* Minimum Threshold Price Futures Negative Whole Pair off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_minimum_threshold_price_futures_negative_whole_pair(MinimumThresholdPriceFuturesNegativeWholePair *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { record->raw_minimum_threshold_price_futures[i] = wire[at++]; }
  record->minimum_threshold_price_fraction_indicator = wire[at++];

  return at;
}

/* what was read of Minimum Threshold Price Futures Negative Whole Pair is what was written, byte for byte */
static void equal_minimum_threshold_price_futures_negative_whole_pair(const MinimumThresholdPriceFuturesNegativeWholePair *read, const MinimumThresholdPriceFuturesNegativeWholePair *written) {
  for (size_t i = 0; i < 7; i++) { assert(read->raw_minimum_threshold_price_futures[i] == written->raw_minimum_threshold_price_futures[i]); }
  assert(read->minimum_threshold_price_fraction_indicator == written->minimum_threshold_price_fraction_indicator);
}

/* Minimum Threshold Price Futures Negative Whole Pair: written and read back, then read and written back */
static void check_minimum_threshold_price_futures_negative_whole_pair(void) {
  MinimumThresholdPriceFuturesNegativeWholePair sent;
  MinimumThresholdPriceFuturesNegativeWholePair got;
  uint8_t wire[8];
  uint8_t again[8];

  any_minimum_threshold_price_futures_negative_whole_pair(&sent);
  assert(encode_minimum_threshold_price_futures_negative_whole_pair(&sent, wire, 0) == 8);
  assert(decode_minimum_threshold_price_futures_negative_whole_pair(&got, wire, 0) == 8);
  equal_minimum_threshold_price_futures_negative_whole_pair(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_minimum_threshold_price_futures_negative_whole_pair(&got, wire, 0) == 8);
  assert(encode_minimum_threshold_price_futures_negative_whole_pair(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Minimum Threshold Price Futures Negative Ten Pair: 8 bytes -------------- */

typedef struct {
  uint8_t raw_minimum_threshold_price_futures[7];      /* bytes 0 to 6 */
  uint8_t minimum_threshold_price_fraction_indicator;  /* byte 7 */
} MinimumThresholdPriceFuturesNegativeTenPair;

/* any Minimum Threshold Price Futures Negative Ten Pair at all: every byte one the checker chooses */
static void any_minimum_threshold_price_futures_negative_ten_pair(MinimumThresholdPriceFuturesNegativeTenPair *record) {
  for (size_t i = 0; i < 7; i++) { record->raw_minimum_threshold_price_futures[i] = arbitrary(); }
  record->minimum_threshold_price_fraction_indicator = arbitrary();
}

/* Minimum Threshold Price Futures Negative Ten Pair to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_minimum_threshold_price_futures_negative_ten_pair(const MinimumThresholdPriceFuturesNegativeTenPair *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->raw_minimum_threshold_price_futures[i]; }
  wire[at++] = record->minimum_threshold_price_fraction_indicator;

  return at;
}

/* Minimum Threshold Price Futures Negative Ten Pair off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_minimum_threshold_price_futures_negative_ten_pair(MinimumThresholdPriceFuturesNegativeTenPair *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { record->raw_minimum_threshold_price_futures[i] = wire[at++]; }
  record->minimum_threshold_price_fraction_indicator = wire[at++];

  return at;
}

/* what was read of Minimum Threshold Price Futures Negative Ten Pair is what was written, byte for byte */
static void equal_minimum_threshold_price_futures_negative_ten_pair(const MinimumThresholdPriceFuturesNegativeTenPair *read, const MinimumThresholdPriceFuturesNegativeTenPair *written) {
  for (size_t i = 0; i < 7; i++) { assert(read->raw_minimum_threshold_price_futures[i] == written->raw_minimum_threshold_price_futures[i]); }
  assert(read->minimum_threshold_price_fraction_indicator == written->minimum_threshold_price_fraction_indicator);
}

/* Minimum Threshold Price Futures Negative Ten Pair: written and read back, then read and written back */
static void check_minimum_threshold_price_futures_negative_ten_pair(void) {
  MinimumThresholdPriceFuturesNegativeTenPair sent;
  MinimumThresholdPriceFuturesNegativeTenPair got;
  uint8_t wire[8];
  uint8_t again[8];

  any_minimum_threshold_price_futures_negative_ten_pair(&sent);
  assert(encode_minimum_threshold_price_futures_negative_ten_pair(&sent, wire, 0) == 8);
  assert(decode_minimum_threshold_price_futures_negative_ten_pair(&got, wire, 0) == 8);
  equal_minimum_threshold_price_futures_negative_ten_pair(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_minimum_threshold_price_futures_negative_ten_pair(&got, wire, 0) == 8);
  assert(encode_minimum_threshold_price_futures_negative_ten_pair(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Minimum Threshold Price Futures Negative Hundred Pair: 8 bytes ---------- */

typedef struct {
  uint8_t raw_minimum_threshold_price_futures[7];      /* bytes 0 to 6 */
  uint8_t minimum_threshold_price_fraction_indicator;  /* byte 7 */
} MinimumThresholdPriceFuturesNegativeHundredPair;

/* any Minimum Threshold Price Futures Negative Hundred Pair at all: every byte one the checker chooses */
static void any_minimum_threshold_price_futures_negative_hundred_pair(MinimumThresholdPriceFuturesNegativeHundredPair *record) {
  for (size_t i = 0; i < 7; i++) { record->raw_minimum_threshold_price_futures[i] = arbitrary(); }
  record->minimum_threshold_price_fraction_indicator = arbitrary();
}

/* Minimum Threshold Price Futures Negative Hundred Pair to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_minimum_threshold_price_futures_negative_hundred_pair(const MinimumThresholdPriceFuturesNegativeHundredPair *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->raw_minimum_threshold_price_futures[i]; }
  wire[at++] = record->minimum_threshold_price_fraction_indicator;

  return at;
}

/* Minimum Threshold Price Futures Negative Hundred Pair off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_minimum_threshold_price_futures_negative_hundred_pair(MinimumThresholdPriceFuturesNegativeHundredPair *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { record->raw_minimum_threshold_price_futures[i] = wire[at++]; }
  record->minimum_threshold_price_fraction_indicator = wire[at++];

  return at;
}

/* what was read of Minimum Threshold Price Futures Negative Hundred Pair is what was written, byte for byte */
static void equal_minimum_threshold_price_futures_negative_hundred_pair(const MinimumThresholdPriceFuturesNegativeHundredPair *read, const MinimumThresholdPriceFuturesNegativeHundredPair *written) {
  for (size_t i = 0; i < 7; i++) { assert(read->raw_minimum_threshold_price_futures[i] == written->raw_minimum_threshold_price_futures[i]); }
  assert(read->minimum_threshold_price_fraction_indicator == written->minimum_threshold_price_fraction_indicator);
}

/* Minimum Threshold Price Futures Negative Hundred Pair: written and read back, then read and written back */
static void check_minimum_threshold_price_futures_negative_hundred_pair(void) {
  MinimumThresholdPriceFuturesNegativeHundredPair sent;
  MinimumThresholdPriceFuturesNegativeHundredPair got;
  uint8_t wire[8];
  uint8_t again[8];

  any_minimum_threshold_price_futures_negative_hundred_pair(&sent);
  assert(encode_minimum_threshold_price_futures_negative_hundred_pair(&sent, wire, 0) == 8);
  assert(decode_minimum_threshold_price_futures_negative_hundred_pair(&got, wire, 0) == 8);
  equal_minimum_threshold_price_futures_negative_hundred_pair(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_minimum_threshold_price_futures_negative_hundred_pair(&got, wire, 0) == 8);
  assert(encode_minimum_threshold_price_futures_negative_hundred_pair(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Minimum Threshold Price Futures Negative Thousand Pair: 8 bytes --------- */

typedef struct {
  uint8_t raw_minimum_threshold_price_futures[7];      /* bytes 0 to 6 */
  uint8_t minimum_threshold_price_fraction_indicator;  /* byte 7 */
} MinimumThresholdPriceFuturesNegativeThousandPair;

/* any Minimum Threshold Price Futures Negative Thousand Pair at all: every byte one the checker chooses */
static void any_minimum_threshold_price_futures_negative_thousand_pair(MinimumThresholdPriceFuturesNegativeThousandPair *record) {
  for (size_t i = 0; i < 7; i++) { record->raw_minimum_threshold_price_futures[i] = arbitrary(); }
  record->minimum_threshold_price_fraction_indicator = arbitrary();
}

/* Minimum Threshold Price Futures Negative Thousand Pair to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_minimum_threshold_price_futures_negative_thousand_pair(const MinimumThresholdPriceFuturesNegativeThousandPair *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->raw_minimum_threshold_price_futures[i]; }
  wire[at++] = record->minimum_threshold_price_fraction_indicator;

  return at;
}

/* Minimum Threshold Price Futures Negative Thousand Pair off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_minimum_threshold_price_futures_negative_thousand_pair(MinimumThresholdPriceFuturesNegativeThousandPair *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { record->raw_minimum_threshold_price_futures[i] = wire[at++]; }
  record->minimum_threshold_price_fraction_indicator = wire[at++];

  return at;
}

/* what was read of Minimum Threshold Price Futures Negative Thousand Pair is what was written, byte for byte */
static void equal_minimum_threshold_price_futures_negative_thousand_pair(const MinimumThresholdPriceFuturesNegativeThousandPair *read, const MinimumThresholdPriceFuturesNegativeThousandPair *written) {
  for (size_t i = 0; i < 7; i++) { assert(read->raw_minimum_threshold_price_futures[i] == written->raw_minimum_threshold_price_futures[i]); }
  assert(read->minimum_threshold_price_fraction_indicator == written->minimum_threshold_price_fraction_indicator);
}

/* Minimum Threshold Price Futures Negative Thousand Pair: written and read back, then read and written back */
static void check_minimum_threshold_price_futures_negative_thousand_pair(void) {
  MinimumThresholdPriceFuturesNegativeThousandPair sent;
  MinimumThresholdPriceFuturesNegativeThousandPair got;
  uint8_t wire[8];
  uint8_t again[8];

  any_minimum_threshold_price_futures_negative_thousand_pair(&sent);
  assert(encode_minimum_threshold_price_futures_negative_thousand_pair(&sent, wire, 0) == 8);
  assert(decode_minimum_threshold_price_futures_negative_thousand_pair(&got, wire, 0) == 8);
  equal_minimum_threshold_price_futures_negative_thousand_pair(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_minimum_threshold_price_futures_negative_thousand_pair(&got, wire, 0) == 8);
  assert(encode_minimum_threshold_price_futures_negative_thousand_pair(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Minimum Threshold Price Futures Negative Ten Thousand Pair: 8 bytes ----- */

typedef struct {
  uint8_t raw_minimum_threshold_price_futures[7];      /* bytes 0 to 6 */
  uint8_t minimum_threshold_price_fraction_indicator;  /* byte 7 */
} MinimumThresholdPriceFuturesNegativeTenThousandPair;

/* any Minimum Threshold Price Futures Negative Ten Thousand Pair at all: every byte one the checker chooses */
static void any_minimum_threshold_price_futures_negative_ten_thousand_pair(MinimumThresholdPriceFuturesNegativeTenThousandPair *record) {
  for (size_t i = 0; i < 7; i++) { record->raw_minimum_threshold_price_futures[i] = arbitrary(); }
  record->minimum_threshold_price_fraction_indicator = arbitrary();
}

/* Minimum Threshold Price Futures Negative Ten Thousand Pair to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_minimum_threshold_price_futures_negative_ten_thousand_pair(const MinimumThresholdPriceFuturesNegativeTenThousandPair *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->raw_minimum_threshold_price_futures[i]; }
  wire[at++] = record->minimum_threshold_price_fraction_indicator;

  return at;
}

/* Minimum Threshold Price Futures Negative Ten Thousand Pair off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_minimum_threshold_price_futures_negative_ten_thousand_pair(MinimumThresholdPriceFuturesNegativeTenThousandPair *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { record->raw_minimum_threshold_price_futures[i] = wire[at++]; }
  record->minimum_threshold_price_fraction_indicator = wire[at++];

  return at;
}

/* what was read of Minimum Threshold Price Futures Negative Ten Thousand Pair is what was written, byte for byte */
static void equal_minimum_threshold_price_futures_negative_ten_thousand_pair(const MinimumThresholdPriceFuturesNegativeTenThousandPair *read, const MinimumThresholdPriceFuturesNegativeTenThousandPair *written) {
  for (size_t i = 0; i < 7; i++) { assert(read->raw_minimum_threshold_price_futures[i] == written->raw_minimum_threshold_price_futures[i]); }
  assert(read->minimum_threshold_price_fraction_indicator == written->minimum_threshold_price_fraction_indicator);
}

/* Minimum Threshold Price Futures Negative Ten Thousand Pair: written and read back, then read and written back */
static void check_minimum_threshold_price_futures_negative_ten_thousand_pair(void) {
  MinimumThresholdPriceFuturesNegativeTenThousandPair sent;
  MinimumThresholdPriceFuturesNegativeTenThousandPair got;
  uint8_t wire[8];
  uint8_t again[8];

  any_minimum_threshold_price_futures_negative_ten_thousand_pair(&sent);
  assert(encode_minimum_threshold_price_futures_negative_ten_thousand_pair(&sent, wire, 0) == 8);
  assert(decode_minimum_threshold_price_futures_negative_ten_thousand_pair(&got, wire, 0) == 8);
  equal_minimum_threshold_price_futures_negative_ten_thousand_pair(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_minimum_threshold_price_futures_negative_ten_thousand_pair(&got, wire, 0) == 8);
  assert(encode_minimum_threshold_price_futures_negative_ten_thousand_pair(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Minimum Threshold Price Futures Negative Hundred Thousand Pair: 8 bytes ---- */

typedef struct {
  uint8_t raw_minimum_threshold_price_futures[7];      /* bytes 0 to 6 */
  uint8_t minimum_threshold_price_fraction_indicator;  /* byte 7 */
} MinimumThresholdPriceFuturesNegativeHundredThousandPair;

/* any Minimum Threshold Price Futures Negative Hundred Thousand Pair at all: every byte one the checker chooses */
static void any_minimum_threshold_price_futures_negative_hundred_thousand_pair(MinimumThresholdPriceFuturesNegativeHundredThousandPair *record) {
  for (size_t i = 0; i < 7; i++) { record->raw_minimum_threshold_price_futures[i] = arbitrary(); }
  record->minimum_threshold_price_fraction_indicator = arbitrary();
}

/* Minimum Threshold Price Futures Negative Hundred Thousand Pair to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_minimum_threshold_price_futures_negative_hundred_thousand_pair(const MinimumThresholdPriceFuturesNegativeHundredThousandPair *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->raw_minimum_threshold_price_futures[i]; }
  wire[at++] = record->minimum_threshold_price_fraction_indicator;

  return at;
}

/* Minimum Threshold Price Futures Negative Hundred Thousand Pair off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_minimum_threshold_price_futures_negative_hundred_thousand_pair(MinimumThresholdPriceFuturesNegativeHundredThousandPair *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { record->raw_minimum_threshold_price_futures[i] = wire[at++]; }
  record->minimum_threshold_price_fraction_indicator = wire[at++];

  return at;
}

/* what was read of Minimum Threshold Price Futures Negative Hundred Thousand Pair is what was written, byte for byte */
static void equal_minimum_threshold_price_futures_negative_hundred_thousand_pair(const MinimumThresholdPriceFuturesNegativeHundredThousandPair *read, const MinimumThresholdPriceFuturesNegativeHundredThousandPair *written) {
  for (size_t i = 0; i < 7; i++) { assert(read->raw_minimum_threshold_price_futures[i] == written->raw_minimum_threshold_price_futures[i]); }
  assert(read->minimum_threshold_price_fraction_indicator == written->minimum_threshold_price_fraction_indicator);
}

/* Minimum Threshold Price Futures Negative Hundred Thousand Pair: written and read back, then read and written back */
static void check_minimum_threshold_price_futures_negative_hundred_thousand_pair(void) {
  MinimumThresholdPriceFuturesNegativeHundredThousandPair sent;
  MinimumThresholdPriceFuturesNegativeHundredThousandPair got;
  uint8_t wire[8];
  uint8_t again[8];

  any_minimum_threshold_price_futures_negative_hundred_thousand_pair(&sent);
  assert(encode_minimum_threshold_price_futures_negative_hundred_thousand_pair(&sent, wire, 0) == 8);
  assert(decode_minimum_threshold_price_futures_negative_hundred_thousand_pair(&got, wire, 0) == 8);
  equal_minimum_threshold_price_futures_negative_hundred_thousand_pair(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_minimum_threshold_price_futures_negative_hundred_thousand_pair(&got, wire, 0) == 8);
  assert(encode_minimum_threshold_price_futures_negative_hundred_thousand_pair(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Minimum Threshold Price Futures Negative Million Pair: 8 bytes ---------- */

typedef struct {
  uint8_t raw_minimum_threshold_price_futures[7];      /* bytes 0 to 6 */
  uint8_t minimum_threshold_price_fraction_indicator;  /* byte 7 */
} MinimumThresholdPriceFuturesNegativeMillionPair;

/* any Minimum Threshold Price Futures Negative Million Pair at all: every byte one the checker chooses */
static void any_minimum_threshold_price_futures_negative_million_pair(MinimumThresholdPriceFuturesNegativeMillionPair *record) {
  for (size_t i = 0; i < 7; i++) { record->raw_minimum_threshold_price_futures[i] = arbitrary(); }
  record->minimum_threshold_price_fraction_indicator = arbitrary();
}

/* Minimum Threshold Price Futures Negative Million Pair to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_minimum_threshold_price_futures_negative_million_pair(const MinimumThresholdPriceFuturesNegativeMillionPair *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->raw_minimum_threshold_price_futures[i]; }
  wire[at++] = record->minimum_threshold_price_fraction_indicator;

  return at;
}

/* Minimum Threshold Price Futures Negative Million Pair off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_minimum_threshold_price_futures_negative_million_pair(MinimumThresholdPriceFuturesNegativeMillionPair *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { record->raw_minimum_threshold_price_futures[i] = wire[at++]; }
  record->minimum_threshold_price_fraction_indicator = wire[at++];

  return at;
}

/* what was read of Minimum Threshold Price Futures Negative Million Pair is what was written, byte for byte */
static void equal_minimum_threshold_price_futures_negative_million_pair(const MinimumThresholdPriceFuturesNegativeMillionPair *read, const MinimumThresholdPriceFuturesNegativeMillionPair *written) {
  for (size_t i = 0; i < 7; i++) { assert(read->raw_minimum_threshold_price_futures[i] == written->raw_minimum_threshold_price_futures[i]); }
  assert(read->minimum_threshold_price_fraction_indicator == written->minimum_threshold_price_fraction_indicator);
}

/* Minimum Threshold Price Futures Negative Million Pair: written and read back, then read and written back */
static void check_minimum_threshold_price_futures_negative_million_pair(void) {
  MinimumThresholdPriceFuturesNegativeMillionPair sent;
  MinimumThresholdPriceFuturesNegativeMillionPair got;
  uint8_t wire[8];
  uint8_t again[8];

  any_minimum_threshold_price_futures_negative_million_pair(&sent);
  assert(encode_minimum_threshold_price_futures_negative_million_pair(&sent, wire, 0) == 8);
  assert(decode_minimum_threshold_price_futures_negative_million_pair(&got, wire, 0) == 8);
  equal_minimum_threshold_price_futures_negative_million_pair(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_minimum_threshold_price_futures_negative_million_pair(&got, wire, 0) == 8);
  assert(encode_minimum_threshold_price_futures_negative_million_pair(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Minimum Threshold Price Futures Numeric Pair: 8 bytes ------------------- */

typedef struct {
  uint8_t minimum_threshold_price_futures[7];          /* bytes 0 to 6 */
  uint8_t minimum_threshold_price_fraction_indicator;  /* byte 7 */
} MinimumThresholdPriceFuturesNumericPair;

/* any Minimum Threshold Price Futures Numeric Pair at all: every byte one the checker chooses */
static void any_minimum_threshold_price_futures_numeric_pair(MinimumThresholdPriceFuturesNumericPair *record) {
  for (size_t i = 0; i < 7; i++) { record->minimum_threshold_price_futures[i] = arbitrary(); }
  record->minimum_threshold_price_fraction_indicator = arbitrary();
}

/* Minimum Threshold Price Futures Numeric Pair to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_minimum_threshold_price_futures_numeric_pair(const MinimumThresholdPriceFuturesNumericPair *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->minimum_threshold_price_futures[i]; }
  wire[at++] = record->minimum_threshold_price_fraction_indicator;

  return at;
}

/* Minimum Threshold Price Futures Numeric Pair off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_minimum_threshold_price_futures_numeric_pair(MinimumThresholdPriceFuturesNumericPair *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { record->minimum_threshold_price_futures[i] = wire[at++]; }
  record->minimum_threshold_price_fraction_indicator = wire[at++];

  return at;
}

/* what was read of Minimum Threshold Price Futures Numeric Pair is what was written, byte for byte */
static void equal_minimum_threshold_price_futures_numeric_pair(const MinimumThresholdPriceFuturesNumericPair *read, const MinimumThresholdPriceFuturesNumericPair *written) {
  for (size_t i = 0; i < 7; i++) { assert(read->minimum_threshold_price_futures[i] == written->minimum_threshold_price_futures[i]); }
  assert(read->minimum_threshold_price_fraction_indicator == written->minimum_threshold_price_fraction_indicator);
}

/* Minimum Threshold Price Futures Numeric Pair: written and read back, then read and written back */
static void check_minimum_threshold_price_futures_numeric_pair(void) {
  MinimumThresholdPriceFuturesNumericPair sent;
  MinimumThresholdPriceFuturesNumericPair got;
  uint8_t wire[8];
  uint8_t again[8];

  any_minimum_threshold_price_futures_numeric_pair(&sent);
  assert(encode_minimum_threshold_price_futures_numeric_pair(&sent, wire, 0) == 8);
  assert(decode_minimum_threshold_price_futures_numeric_pair(&got, wire, 0) == 8);
  equal_minimum_threshold_price_futures_numeric_pair(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_minimum_threshold_price_futures_numeric_pair(&got, wire, 0) == 8);
  assert(encode_minimum_threshold_price_futures_numeric_pair(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Associated Product: 11 bytes -------------------------------------------- */

/* Associated future product symbology */
typedef struct {
  uint8_t root_symbol[6];  /* bytes 0 to 5 */
  uint8_t symbol_month;    /* byte 6 */
  uint8_t symbol_year[2];  /* bytes 7 to 8 */
  uint8_t expiry_day[2];   /* bytes 9 to 10 */
} AssociatedProduct;

/* any Associated Product at all: every byte one the checker chooses */
static void any_associated_product(AssociatedProduct *record) {
  for (size_t i = 0; i < 6; i++) { record->root_symbol[i] = arbitrary(); }
  record->symbol_month = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->symbol_year[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->expiry_day[i] = arbitrary(); }
}

/* Associated Product to the wire: 11 bytes from at, returning where the next byte goes */
static size_t encode_associated_product(const AssociatedProduct *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->root_symbol[i]; }
  wire[at++] = record->symbol_month;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->symbol_year[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->expiry_day[i]; }

  return at;
}

/* Associated Product off the wire: 11 bytes from at, returning where the next byte lies */
static size_t decode_associated_product(AssociatedProduct *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 6; i++) { record->root_symbol[i] = wire[at++]; }
  record->symbol_month = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->symbol_year[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->expiry_day[i] = wire[at++]; }

  return at;
}

/* what was read of Associated Product is what was written, byte for byte */
static void equal_associated_product(const AssociatedProduct *read, const AssociatedProduct *written) {
  for (size_t i = 0; i < 6; i++) { assert(read->root_symbol[i] == written->root_symbol[i]); }
  assert(read->symbol_month == written->symbol_month);
  for (size_t i = 0; i < 2; i++) { assert(read->symbol_year[i] == written->symbol_year[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->expiry_day[i] == written->expiry_day[i]); }
}

/* Associated Product: written and read back, then read and written back */
static void check_associated_product(void) {
  AssociatedProduct sent;
  AssociatedProduct got;
  uint8_t wire[11];
  uint8_t again[11];

  any_associated_product(&sent);
  assert(encode_associated_product(&sent, wire, 0) == 11);
  assert(decode_associated_product(&got, wire, 0) == 11);
  equal_associated_product(&got, &sent);

  for (size_t i = 0; i < 11; i++) { wire[i] = arbitrary(); }
  assert(decode_associated_product(&got, wire, 0) == 11);
  assert(encode_associated_product(&got, again, 0) == 11);
  for (size_t i = 0; i < 11; i++) { assert(again[i] == wire[i]); }
}

/* ---- Bid Price Summary Negative Whole Pair: 8 bytes -------------------------- */

typedef struct {
  uint8_t raw_bid_price_summary[7];      /* bytes 0 to 6 */
  uint8_t bid_price_fraction_indicator;  /* byte 7 */
} BidPriceSummaryNegativeWholePair;

/* any Bid Price Summary Negative Whole Pair at all: every byte one the checker chooses */
static void any_bid_price_summary_negative_whole_pair(BidPriceSummaryNegativeWholePair *record) {
  for (size_t i = 0; i < 7; i++) { record->raw_bid_price_summary[i] = arbitrary(); }
  record->bid_price_fraction_indicator = arbitrary();
}

/* Bid Price Summary Negative Whole Pair to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_bid_price_summary_negative_whole_pair(const BidPriceSummaryNegativeWholePair *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->raw_bid_price_summary[i]; }
  wire[at++] = record->bid_price_fraction_indicator;

  return at;
}

/* Bid Price Summary Negative Whole Pair off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_bid_price_summary_negative_whole_pair(BidPriceSummaryNegativeWholePair *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { record->raw_bid_price_summary[i] = wire[at++]; }
  record->bid_price_fraction_indicator = wire[at++];

  return at;
}

/* what was read of Bid Price Summary Negative Whole Pair is what was written, byte for byte */
static void equal_bid_price_summary_negative_whole_pair(const BidPriceSummaryNegativeWholePair *read, const BidPriceSummaryNegativeWholePair *written) {
  for (size_t i = 0; i < 7; i++) { assert(read->raw_bid_price_summary[i] == written->raw_bid_price_summary[i]); }
  assert(read->bid_price_fraction_indicator == written->bid_price_fraction_indicator);
}

/* Bid Price Summary Negative Whole Pair: written and read back, then read and written back */
static void check_bid_price_summary_negative_whole_pair(void) {
  BidPriceSummaryNegativeWholePair sent;
  BidPriceSummaryNegativeWholePair got;
  uint8_t wire[8];
  uint8_t again[8];

  any_bid_price_summary_negative_whole_pair(&sent);
  assert(encode_bid_price_summary_negative_whole_pair(&sent, wire, 0) == 8);
  assert(decode_bid_price_summary_negative_whole_pair(&got, wire, 0) == 8);
  equal_bid_price_summary_negative_whole_pair(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_bid_price_summary_negative_whole_pair(&got, wire, 0) == 8);
  assert(encode_bid_price_summary_negative_whole_pair(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Bid Price Summary Negative Ten Pair: 8 bytes ---------------------------- */

typedef struct {
  uint8_t raw_bid_price_summary[7];      /* bytes 0 to 6 */
  uint8_t bid_price_fraction_indicator;  /* byte 7 */
} BidPriceSummaryNegativeTenPair;

/* any Bid Price Summary Negative Ten Pair at all: every byte one the checker chooses */
static void any_bid_price_summary_negative_ten_pair(BidPriceSummaryNegativeTenPair *record) {
  for (size_t i = 0; i < 7; i++) { record->raw_bid_price_summary[i] = arbitrary(); }
  record->bid_price_fraction_indicator = arbitrary();
}

/* Bid Price Summary Negative Ten Pair to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_bid_price_summary_negative_ten_pair(const BidPriceSummaryNegativeTenPair *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->raw_bid_price_summary[i]; }
  wire[at++] = record->bid_price_fraction_indicator;

  return at;
}

/* Bid Price Summary Negative Ten Pair off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_bid_price_summary_negative_ten_pair(BidPriceSummaryNegativeTenPair *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { record->raw_bid_price_summary[i] = wire[at++]; }
  record->bid_price_fraction_indicator = wire[at++];

  return at;
}

/* what was read of Bid Price Summary Negative Ten Pair is what was written, byte for byte */
static void equal_bid_price_summary_negative_ten_pair(const BidPriceSummaryNegativeTenPair *read, const BidPriceSummaryNegativeTenPair *written) {
  for (size_t i = 0; i < 7; i++) { assert(read->raw_bid_price_summary[i] == written->raw_bid_price_summary[i]); }
  assert(read->bid_price_fraction_indicator == written->bid_price_fraction_indicator);
}

/* Bid Price Summary Negative Ten Pair: written and read back, then read and written back */
static void check_bid_price_summary_negative_ten_pair(void) {
  BidPriceSummaryNegativeTenPair sent;
  BidPriceSummaryNegativeTenPair got;
  uint8_t wire[8];
  uint8_t again[8];

  any_bid_price_summary_negative_ten_pair(&sent);
  assert(encode_bid_price_summary_negative_ten_pair(&sent, wire, 0) == 8);
  assert(decode_bid_price_summary_negative_ten_pair(&got, wire, 0) == 8);
  equal_bid_price_summary_negative_ten_pair(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_bid_price_summary_negative_ten_pair(&got, wire, 0) == 8);
  assert(encode_bid_price_summary_negative_ten_pair(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Bid Price Summary Negative Hundred Pair: 8 bytes ------------------------ */

typedef struct {
  uint8_t raw_bid_price_summary[7];      /* bytes 0 to 6 */
  uint8_t bid_price_fraction_indicator;  /* byte 7 */
} BidPriceSummaryNegativeHundredPair;

/* any Bid Price Summary Negative Hundred Pair at all: every byte one the checker chooses */
static void any_bid_price_summary_negative_hundred_pair(BidPriceSummaryNegativeHundredPair *record) {
  for (size_t i = 0; i < 7; i++) { record->raw_bid_price_summary[i] = arbitrary(); }
  record->bid_price_fraction_indicator = arbitrary();
}

/* Bid Price Summary Negative Hundred Pair to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_bid_price_summary_negative_hundred_pair(const BidPriceSummaryNegativeHundredPair *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->raw_bid_price_summary[i]; }
  wire[at++] = record->bid_price_fraction_indicator;

  return at;
}

/* Bid Price Summary Negative Hundred Pair off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_bid_price_summary_negative_hundred_pair(BidPriceSummaryNegativeHundredPair *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { record->raw_bid_price_summary[i] = wire[at++]; }
  record->bid_price_fraction_indicator = wire[at++];

  return at;
}

/* what was read of Bid Price Summary Negative Hundred Pair is what was written, byte for byte */
static void equal_bid_price_summary_negative_hundred_pair(const BidPriceSummaryNegativeHundredPair *read, const BidPriceSummaryNegativeHundredPair *written) {
  for (size_t i = 0; i < 7; i++) { assert(read->raw_bid_price_summary[i] == written->raw_bid_price_summary[i]); }
  assert(read->bid_price_fraction_indicator == written->bid_price_fraction_indicator);
}

/* Bid Price Summary Negative Hundred Pair: written and read back, then read and written back */
static void check_bid_price_summary_negative_hundred_pair(void) {
  BidPriceSummaryNegativeHundredPair sent;
  BidPriceSummaryNegativeHundredPair got;
  uint8_t wire[8];
  uint8_t again[8];

  any_bid_price_summary_negative_hundred_pair(&sent);
  assert(encode_bid_price_summary_negative_hundred_pair(&sent, wire, 0) == 8);
  assert(decode_bid_price_summary_negative_hundred_pair(&got, wire, 0) == 8);
  equal_bid_price_summary_negative_hundred_pair(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_bid_price_summary_negative_hundred_pair(&got, wire, 0) == 8);
  assert(encode_bid_price_summary_negative_hundred_pair(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Bid Price Summary Negative Thousand Pair: 8 bytes ----------------------- */

typedef struct {
  uint8_t raw_bid_price_summary[7];      /* bytes 0 to 6 */
  uint8_t bid_price_fraction_indicator;  /* byte 7 */
} BidPriceSummaryNegativeThousandPair;

/* any Bid Price Summary Negative Thousand Pair at all: every byte one the checker chooses */
static void any_bid_price_summary_negative_thousand_pair(BidPriceSummaryNegativeThousandPair *record) {
  for (size_t i = 0; i < 7; i++) { record->raw_bid_price_summary[i] = arbitrary(); }
  record->bid_price_fraction_indicator = arbitrary();
}

/* Bid Price Summary Negative Thousand Pair to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_bid_price_summary_negative_thousand_pair(const BidPriceSummaryNegativeThousandPair *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->raw_bid_price_summary[i]; }
  wire[at++] = record->bid_price_fraction_indicator;

  return at;
}

/* Bid Price Summary Negative Thousand Pair off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_bid_price_summary_negative_thousand_pair(BidPriceSummaryNegativeThousandPair *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { record->raw_bid_price_summary[i] = wire[at++]; }
  record->bid_price_fraction_indicator = wire[at++];

  return at;
}

/* what was read of Bid Price Summary Negative Thousand Pair is what was written, byte for byte */
static void equal_bid_price_summary_negative_thousand_pair(const BidPriceSummaryNegativeThousandPair *read, const BidPriceSummaryNegativeThousandPair *written) {
  for (size_t i = 0; i < 7; i++) { assert(read->raw_bid_price_summary[i] == written->raw_bid_price_summary[i]); }
  assert(read->bid_price_fraction_indicator == written->bid_price_fraction_indicator);
}

/* Bid Price Summary Negative Thousand Pair: written and read back, then read and written back */
static void check_bid_price_summary_negative_thousand_pair(void) {
  BidPriceSummaryNegativeThousandPair sent;
  BidPriceSummaryNegativeThousandPair got;
  uint8_t wire[8];
  uint8_t again[8];

  any_bid_price_summary_negative_thousand_pair(&sent);
  assert(encode_bid_price_summary_negative_thousand_pair(&sent, wire, 0) == 8);
  assert(decode_bid_price_summary_negative_thousand_pair(&got, wire, 0) == 8);
  equal_bid_price_summary_negative_thousand_pair(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_bid_price_summary_negative_thousand_pair(&got, wire, 0) == 8);
  assert(encode_bid_price_summary_negative_thousand_pair(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Bid Price Summary Negative Ten Thousand Pair: 8 bytes ------------------- */

typedef struct {
  uint8_t raw_bid_price_summary[7];      /* bytes 0 to 6 */
  uint8_t bid_price_fraction_indicator;  /* byte 7 */
} BidPriceSummaryNegativeTenThousandPair;

/* any Bid Price Summary Negative Ten Thousand Pair at all: every byte one the checker chooses */
static void any_bid_price_summary_negative_ten_thousand_pair(BidPriceSummaryNegativeTenThousandPair *record) {
  for (size_t i = 0; i < 7; i++) { record->raw_bid_price_summary[i] = arbitrary(); }
  record->bid_price_fraction_indicator = arbitrary();
}

/* Bid Price Summary Negative Ten Thousand Pair to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_bid_price_summary_negative_ten_thousand_pair(const BidPriceSummaryNegativeTenThousandPair *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->raw_bid_price_summary[i]; }
  wire[at++] = record->bid_price_fraction_indicator;

  return at;
}

/* Bid Price Summary Negative Ten Thousand Pair off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_bid_price_summary_negative_ten_thousand_pair(BidPriceSummaryNegativeTenThousandPair *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { record->raw_bid_price_summary[i] = wire[at++]; }
  record->bid_price_fraction_indicator = wire[at++];

  return at;
}

/* what was read of Bid Price Summary Negative Ten Thousand Pair is what was written, byte for byte */
static void equal_bid_price_summary_negative_ten_thousand_pair(const BidPriceSummaryNegativeTenThousandPair *read, const BidPriceSummaryNegativeTenThousandPair *written) {
  for (size_t i = 0; i < 7; i++) { assert(read->raw_bid_price_summary[i] == written->raw_bid_price_summary[i]); }
  assert(read->bid_price_fraction_indicator == written->bid_price_fraction_indicator);
}

/* Bid Price Summary Negative Ten Thousand Pair: written and read back, then read and written back */
static void check_bid_price_summary_negative_ten_thousand_pair(void) {
  BidPriceSummaryNegativeTenThousandPair sent;
  BidPriceSummaryNegativeTenThousandPair got;
  uint8_t wire[8];
  uint8_t again[8];

  any_bid_price_summary_negative_ten_thousand_pair(&sent);
  assert(encode_bid_price_summary_negative_ten_thousand_pair(&sent, wire, 0) == 8);
  assert(decode_bid_price_summary_negative_ten_thousand_pair(&got, wire, 0) == 8);
  equal_bid_price_summary_negative_ten_thousand_pair(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_bid_price_summary_negative_ten_thousand_pair(&got, wire, 0) == 8);
  assert(encode_bid_price_summary_negative_ten_thousand_pair(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Bid Price Summary Negative Hundred Thousand Pair: 8 bytes --------------- */

typedef struct {
  uint8_t raw_bid_price_summary[7];      /* bytes 0 to 6 */
  uint8_t bid_price_fraction_indicator;  /* byte 7 */
} BidPriceSummaryNegativeHundredThousandPair;

/* any Bid Price Summary Negative Hundred Thousand Pair at all: every byte one the checker chooses */
static void any_bid_price_summary_negative_hundred_thousand_pair(BidPriceSummaryNegativeHundredThousandPair *record) {
  for (size_t i = 0; i < 7; i++) { record->raw_bid_price_summary[i] = arbitrary(); }
  record->bid_price_fraction_indicator = arbitrary();
}

/* Bid Price Summary Negative Hundred Thousand Pair to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_bid_price_summary_negative_hundred_thousand_pair(const BidPriceSummaryNegativeHundredThousandPair *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->raw_bid_price_summary[i]; }
  wire[at++] = record->bid_price_fraction_indicator;

  return at;
}

/* Bid Price Summary Negative Hundred Thousand Pair off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_bid_price_summary_negative_hundred_thousand_pair(BidPriceSummaryNegativeHundredThousandPair *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { record->raw_bid_price_summary[i] = wire[at++]; }
  record->bid_price_fraction_indicator = wire[at++];

  return at;
}

/* what was read of Bid Price Summary Negative Hundred Thousand Pair is what was written, byte for byte */
static void equal_bid_price_summary_negative_hundred_thousand_pair(const BidPriceSummaryNegativeHundredThousandPair *read, const BidPriceSummaryNegativeHundredThousandPair *written) {
  for (size_t i = 0; i < 7; i++) { assert(read->raw_bid_price_summary[i] == written->raw_bid_price_summary[i]); }
  assert(read->bid_price_fraction_indicator == written->bid_price_fraction_indicator);
}

/* Bid Price Summary Negative Hundred Thousand Pair: written and read back, then read and written back */
static void check_bid_price_summary_negative_hundred_thousand_pair(void) {
  BidPriceSummaryNegativeHundredThousandPair sent;
  BidPriceSummaryNegativeHundredThousandPair got;
  uint8_t wire[8];
  uint8_t again[8];

  any_bid_price_summary_negative_hundred_thousand_pair(&sent);
  assert(encode_bid_price_summary_negative_hundred_thousand_pair(&sent, wire, 0) == 8);
  assert(decode_bid_price_summary_negative_hundred_thousand_pair(&got, wire, 0) == 8);
  equal_bid_price_summary_negative_hundred_thousand_pair(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_bid_price_summary_negative_hundred_thousand_pair(&got, wire, 0) == 8);
  assert(encode_bid_price_summary_negative_hundred_thousand_pair(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Bid Price Summary Negative Million Pair: 8 bytes ------------------------ */

typedef struct {
  uint8_t raw_bid_price_summary[7];      /* bytes 0 to 6 */
  uint8_t bid_price_fraction_indicator;  /* byte 7 */
} BidPriceSummaryNegativeMillionPair;

/* any Bid Price Summary Negative Million Pair at all: every byte one the checker chooses */
static void any_bid_price_summary_negative_million_pair(BidPriceSummaryNegativeMillionPair *record) {
  for (size_t i = 0; i < 7; i++) { record->raw_bid_price_summary[i] = arbitrary(); }
  record->bid_price_fraction_indicator = arbitrary();
}

/* Bid Price Summary Negative Million Pair to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_bid_price_summary_negative_million_pair(const BidPriceSummaryNegativeMillionPair *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->raw_bid_price_summary[i]; }
  wire[at++] = record->bid_price_fraction_indicator;

  return at;
}

/* Bid Price Summary Negative Million Pair off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_bid_price_summary_negative_million_pair(BidPriceSummaryNegativeMillionPair *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { record->raw_bid_price_summary[i] = wire[at++]; }
  record->bid_price_fraction_indicator = wire[at++];

  return at;
}

/* what was read of Bid Price Summary Negative Million Pair is what was written, byte for byte */
static void equal_bid_price_summary_negative_million_pair(const BidPriceSummaryNegativeMillionPair *read, const BidPriceSummaryNegativeMillionPair *written) {
  for (size_t i = 0; i < 7; i++) { assert(read->raw_bid_price_summary[i] == written->raw_bid_price_summary[i]); }
  assert(read->bid_price_fraction_indicator == written->bid_price_fraction_indicator);
}

/* Bid Price Summary Negative Million Pair: written and read back, then read and written back */
static void check_bid_price_summary_negative_million_pair(void) {
  BidPriceSummaryNegativeMillionPair sent;
  BidPriceSummaryNegativeMillionPair got;
  uint8_t wire[8];
  uint8_t again[8];

  any_bid_price_summary_negative_million_pair(&sent);
  assert(encode_bid_price_summary_negative_million_pair(&sent, wire, 0) == 8);
  assert(decode_bid_price_summary_negative_million_pair(&got, wire, 0) == 8);
  equal_bid_price_summary_negative_million_pair(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_bid_price_summary_negative_million_pair(&got, wire, 0) == 8);
  assert(encode_bid_price_summary_negative_million_pair(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Bid Price Summary Numeric Pair: 8 bytes --------------------------------- */

typedef struct {
  uint8_t bid_price_summary[7];          /* bytes 0 to 6 */
  uint8_t bid_price_fraction_indicator;  /* byte 7 */
} BidPriceSummaryNumericPair;

/* any Bid Price Summary Numeric Pair at all: every byte one the checker chooses */
static void any_bid_price_summary_numeric_pair(BidPriceSummaryNumericPair *record) {
  for (size_t i = 0; i < 7; i++) { record->bid_price_summary[i] = arbitrary(); }
  record->bid_price_fraction_indicator = arbitrary();
}

/* Bid Price Summary Numeric Pair to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_bid_price_summary_numeric_pair(const BidPriceSummaryNumericPair *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->bid_price_summary[i]; }
  wire[at++] = record->bid_price_fraction_indicator;

  return at;
}

/* Bid Price Summary Numeric Pair off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_bid_price_summary_numeric_pair(BidPriceSummaryNumericPair *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { record->bid_price_summary[i] = wire[at++]; }
  record->bid_price_fraction_indicator = wire[at++];

  return at;
}

/* what was read of Bid Price Summary Numeric Pair is what was written, byte for byte */
static void equal_bid_price_summary_numeric_pair(const BidPriceSummaryNumericPair *read, const BidPriceSummaryNumericPair *written) {
  for (size_t i = 0; i < 7; i++) { assert(read->bid_price_summary[i] == written->bid_price_summary[i]); }
  assert(read->bid_price_fraction_indicator == written->bid_price_fraction_indicator);
}

/* Bid Price Summary Numeric Pair: written and read back, then read and written back */
static void check_bid_price_summary_numeric_pair(void) {
  BidPriceSummaryNumericPair sent;
  BidPriceSummaryNumericPair got;
  uint8_t wire[8];
  uint8_t again[8];

  any_bid_price_summary_numeric_pair(&sent);
  assert(encode_bid_price_summary_numeric_pair(&sent, wire, 0) == 8);
  assert(decode_bid_price_summary_numeric_pair(&got, wire, 0) == 8);
  equal_bid_price_summary_numeric_pair(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_bid_price_summary_numeric_pair(&got, wire, 0) == 8);
  assert(encode_bid_price_summary_numeric_pair(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Ask Price Summary Negative Whole Pair: 8 bytes -------------------------- */

typedef struct {
  uint8_t raw_ask_price_summary[7];      /* bytes 0 to 6 */
  uint8_t ask_price_fraction_indicator;  /* byte 7 */
} AskPriceSummaryNegativeWholePair;

/* any Ask Price Summary Negative Whole Pair at all: every byte one the checker chooses */
static void any_ask_price_summary_negative_whole_pair(AskPriceSummaryNegativeWholePair *record) {
  for (size_t i = 0; i < 7; i++) { record->raw_ask_price_summary[i] = arbitrary(); }
  record->ask_price_fraction_indicator = arbitrary();
}

/* Ask Price Summary Negative Whole Pair to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_ask_price_summary_negative_whole_pair(const AskPriceSummaryNegativeWholePair *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->raw_ask_price_summary[i]; }
  wire[at++] = record->ask_price_fraction_indicator;

  return at;
}

/* Ask Price Summary Negative Whole Pair off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_ask_price_summary_negative_whole_pair(AskPriceSummaryNegativeWholePair *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { record->raw_ask_price_summary[i] = wire[at++]; }
  record->ask_price_fraction_indicator = wire[at++];

  return at;
}

/* what was read of Ask Price Summary Negative Whole Pair is what was written, byte for byte */
static void equal_ask_price_summary_negative_whole_pair(const AskPriceSummaryNegativeWholePair *read, const AskPriceSummaryNegativeWholePair *written) {
  for (size_t i = 0; i < 7; i++) { assert(read->raw_ask_price_summary[i] == written->raw_ask_price_summary[i]); }
  assert(read->ask_price_fraction_indicator == written->ask_price_fraction_indicator);
}

/* Ask Price Summary Negative Whole Pair: written and read back, then read and written back */
static void check_ask_price_summary_negative_whole_pair(void) {
  AskPriceSummaryNegativeWholePair sent;
  AskPriceSummaryNegativeWholePair got;
  uint8_t wire[8];
  uint8_t again[8];

  any_ask_price_summary_negative_whole_pair(&sent);
  assert(encode_ask_price_summary_negative_whole_pair(&sent, wire, 0) == 8);
  assert(decode_ask_price_summary_negative_whole_pair(&got, wire, 0) == 8);
  equal_ask_price_summary_negative_whole_pair(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_ask_price_summary_negative_whole_pair(&got, wire, 0) == 8);
  assert(encode_ask_price_summary_negative_whole_pair(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Ask Price Summary Negative Ten Pair: 8 bytes ---------------------------- */

typedef struct {
  uint8_t raw_ask_price_summary[7];      /* bytes 0 to 6 */
  uint8_t ask_price_fraction_indicator;  /* byte 7 */
} AskPriceSummaryNegativeTenPair;

/* any Ask Price Summary Negative Ten Pair at all: every byte one the checker chooses */
static void any_ask_price_summary_negative_ten_pair(AskPriceSummaryNegativeTenPair *record) {
  for (size_t i = 0; i < 7; i++) { record->raw_ask_price_summary[i] = arbitrary(); }
  record->ask_price_fraction_indicator = arbitrary();
}

/* Ask Price Summary Negative Ten Pair to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_ask_price_summary_negative_ten_pair(const AskPriceSummaryNegativeTenPair *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->raw_ask_price_summary[i]; }
  wire[at++] = record->ask_price_fraction_indicator;

  return at;
}

/* Ask Price Summary Negative Ten Pair off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_ask_price_summary_negative_ten_pair(AskPriceSummaryNegativeTenPair *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { record->raw_ask_price_summary[i] = wire[at++]; }
  record->ask_price_fraction_indicator = wire[at++];

  return at;
}

/* what was read of Ask Price Summary Negative Ten Pair is what was written, byte for byte */
static void equal_ask_price_summary_negative_ten_pair(const AskPriceSummaryNegativeTenPair *read, const AskPriceSummaryNegativeTenPair *written) {
  for (size_t i = 0; i < 7; i++) { assert(read->raw_ask_price_summary[i] == written->raw_ask_price_summary[i]); }
  assert(read->ask_price_fraction_indicator == written->ask_price_fraction_indicator);
}

/* Ask Price Summary Negative Ten Pair: written and read back, then read and written back */
static void check_ask_price_summary_negative_ten_pair(void) {
  AskPriceSummaryNegativeTenPair sent;
  AskPriceSummaryNegativeTenPair got;
  uint8_t wire[8];
  uint8_t again[8];

  any_ask_price_summary_negative_ten_pair(&sent);
  assert(encode_ask_price_summary_negative_ten_pair(&sent, wire, 0) == 8);
  assert(decode_ask_price_summary_negative_ten_pair(&got, wire, 0) == 8);
  equal_ask_price_summary_negative_ten_pair(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_ask_price_summary_negative_ten_pair(&got, wire, 0) == 8);
  assert(encode_ask_price_summary_negative_ten_pair(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Ask Price Summary Negative Hundred Pair: 8 bytes ------------------------ */

typedef struct {
  uint8_t raw_ask_price_summary[7];      /* bytes 0 to 6 */
  uint8_t ask_price_fraction_indicator;  /* byte 7 */
} AskPriceSummaryNegativeHundredPair;

/* any Ask Price Summary Negative Hundred Pair at all: every byte one the checker chooses */
static void any_ask_price_summary_negative_hundred_pair(AskPriceSummaryNegativeHundredPair *record) {
  for (size_t i = 0; i < 7; i++) { record->raw_ask_price_summary[i] = arbitrary(); }
  record->ask_price_fraction_indicator = arbitrary();
}

/* Ask Price Summary Negative Hundred Pair to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_ask_price_summary_negative_hundred_pair(const AskPriceSummaryNegativeHundredPair *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->raw_ask_price_summary[i]; }
  wire[at++] = record->ask_price_fraction_indicator;

  return at;
}

/* Ask Price Summary Negative Hundred Pair off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_ask_price_summary_negative_hundred_pair(AskPriceSummaryNegativeHundredPair *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { record->raw_ask_price_summary[i] = wire[at++]; }
  record->ask_price_fraction_indicator = wire[at++];

  return at;
}

/* what was read of Ask Price Summary Negative Hundred Pair is what was written, byte for byte */
static void equal_ask_price_summary_negative_hundred_pair(const AskPriceSummaryNegativeHundredPair *read, const AskPriceSummaryNegativeHundredPair *written) {
  for (size_t i = 0; i < 7; i++) { assert(read->raw_ask_price_summary[i] == written->raw_ask_price_summary[i]); }
  assert(read->ask_price_fraction_indicator == written->ask_price_fraction_indicator);
}

/* Ask Price Summary Negative Hundred Pair: written and read back, then read and written back */
static void check_ask_price_summary_negative_hundred_pair(void) {
  AskPriceSummaryNegativeHundredPair sent;
  AskPriceSummaryNegativeHundredPair got;
  uint8_t wire[8];
  uint8_t again[8];

  any_ask_price_summary_negative_hundred_pair(&sent);
  assert(encode_ask_price_summary_negative_hundred_pair(&sent, wire, 0) == 8);
  assert(decode_ask_price_summary_negative_hundred_pair(&got, wire, 0) == 8);
  equal_ask_price_summary_negative_hundred_pair(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_ask_price_summary_negative_hundred_pair(&got, wire, 0) == 8);
  assert(encode_ask_price_summary_negative_hundred_pair(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Ask Price Summary Negative Thousand Pair: 8 bytes ----------------------- */

typedef struct {
  uint8_t raw_ask_price_summary[7];      /* bytes 0 to 6 */
  uint8_t ask_price_fraction_indicator;  /* byte 7 */
} AskPriceSummaryNegativeThousandPair;

/* any Ask Price Summary Negative Thousand Pair at all: every byte one the checker chooses */
static void any_ask_price_summary_negative_thousand_pair(AskPriceSummaryNegativeThousandPair *record) {
  for (size_t i = 0; i < 7; i++) { record->raw_ask_price_summary[i] = arbitrary(); }
  record->ask_price_fraction_indicator = arbitrary();
}

/* Ask Price Summary Negative Thousand Pair to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_ask_price_summary_negative_thousand_pair(const AskPriceSummaryNegativeThousandPair *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->raw_ask_price_summary[i]; }
  wire[at++] = record->ask_price_fraction_indicator;

  return at;
}

/* Ask Price Summary Negative Thousand Pair off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_ask_price_summary_negative_thousand_pair(AskPriceSummaryNegativeThousandPair *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { record->raw_ask_price_summary[i] = wire[at++]; }
  record->ask_price_fraction_indicator = wire[at++];

  return at;
}

/* what was read of Ask Price Summary Negative Thousand Pair is what was written, byte for byte */
static void equal_ask_price_summary_negative_thousand_pair(const AskPriceSummaryNegativeThousandPair *read, const AskPriceSummaryNegativeThousandPair *written) {
  for (size_t i = 0; i < 7; i++) { assert(read->raw_ask_price_summary[i] == written->raw_ask_price_summary[i]); }
  assert(read->ask_price_fraction_indicator == written->ask_price_fraction_indicator);
}

/* Ask Price Summary Negative Thousand Pair: written and read back, then read and written back */
static void check_ask_price_summary_negative_thousand_pair(void) {
  AskPriceSummaryNegativeThousandPair sent;
  AskPriceSummaryNegativeThousandPair got;
  uint8_t wire[8];
  uint8_t again[8];

  any_ask_price_summary_negative_thousand_pair(&sent);
  assert(encode_ask_price_summary_negative_thousand_pair(&sent, wire, 0) == 8);
  assert(decode_ask_price_summary_negative_thousand_pair(&got, wire, 0) == 8);
  equal_ask_price_summary_negative_thousand_pair(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_ask_price_summary_negative_thousand_pair(&got, wire, 0) == 8);
  assert(encode_ask_price_summary_negative_thousand_pair(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Ask Price Summary Negative Ten Thousand Pair: 8 bytes ------------------- */

typedef struct {
  uint8_t raw_ask_price_summary[7];      /* bytes 0 to 6 */
  uint8_t ask_price_fraction_indicator;  /* byte 7 */
} AskPriceSummaryNegativeTenThousandPair;

/* any Ask Price Summary Negative Ten Thousand Pair at all: every byte one the checker chooses */
static void any_ask_price_summary_negative_ten_thousand_pair(AskPriceSummaryNegativeTenThousandPair *record) {
  for (size_t i = 0; i < 7; i++) { record->raw_ask_price_summary[i] = arbitrary(); }
  record->ask_price_fraction_indicator = arbitrary();
}

/* Ask Price Summary Negative Ten Thousand Pair to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_ask_price_summary_negative_ten_thousand_pair(const AskPriceSummaryNegativeTenThousandPair *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->raw_ask_price_summary[i]; }
  wire[at++] = record->ask_price_fraction_indicator;

  return at;
}

/* Ask Price Summary Negative Ten Thousand Pair off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_ask_price_summary_negative_ten_thousand_pair(AskPriceSummaryNegativeTenThousandPair *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { record->raw_ask_price_summary[i] = wire[at++]; }
  record->ask_price_fraction_indicator = wire[at++];

  return at;
}

/* what was read of Ask Price Summary Negative Ten Thousand Pair is what was written, byte for byte */
static void equal_ask_price_summary_negative_ten_thousand_pair(const AskPriceSummaryNegativeTenThousandPair *read, const AskPriceSummaryNegativeTenThousandPair *written) {
  for (size_t i = 0; i < 7; i++) { assert(read->raw_ask_price_summary[i] == written->raw_ask_price_summary[i]); }
  assert(read->ask_price_fraction_indicator == written->ask_price_fraction_indicator);
}

/* Ask Price Summary Negative Ten Thousand Pair: written and read back, then read and written back */
static void check_ask_price_summary_negative_ten_thousand_pair(void) {
  AskPriceSummaryNegativeTenThousandPair sent;
  AskPriceSummaryNegativeTenThousandPair got;
  uint8_t wire[8];
  uint8_t again[8];

  any_ask_price_summary_negative_ten_thousand_pair(&sent);
  assert(encode_ask_price_summary_negative_ten_thousand_pair(&sent, wire, 0) == 8);
  assert(decode_ask_price_summary_negative_ten_thousand_pair(&got, wire, 0) == 8);
  equal_ask_price_summary_negative_ten_thousand_pair(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_ask_price_summary_negative_ten_thousand_pair(&got, wire, 0) == 8);
  assert(encode_ask_price_summary_negative_ten_thousand_pair(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Ask Price Summary Negative Hundred Thousand Pair: 8 bytes --------------- */

typedef struct {
  uint8_t raw_ask_price_summary[7];      /* bytes 0 to 6 */
  uint8_t ask_price_fraction_indicator;  /* byte 7 */
} AskPriceSummaryNegativeHundredThousandPair;

/* any Ask Price Summary Negative Hundred Thousand Pair at all: every byte one the checker chooses */
static void any_ask_price_summary_negative_hundred_thousand_pair(AskPriceSummaryNegativeHundredThousandPair *record) {
  for (size_t i = 0; i < 7; i++) { record->raw_ask_price_summary[i] = arbitrary(); }
  record->ask_price_fraction_indicator = arbitrary();
}

/* Ask Price Summary Negative Hundred Thousand Pair to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_ask_price_summary_negative_hundred_thousand_pair(const AskPriceSummaryNegativeHundredThousandPair *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->raw_ask_price_summary[i]; }
  wire[at++] = record->ask_price_fraction_indicator;

  return at;
}

/* Ask Price Summary Negative Hundred Thousand Pair off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_ask_price_summary_negative_hundred_thousand_pair(AskPriceSummaryNegativeHundredThousandPair *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { record->raw_ask_price_summary[i] = wire[at++]; }
  record->ask_price_fraction_indicator = wire[at++];

  return at;
}

/* what was read of Ask Price Summary Negative Hundred Thousand Pair is what was written, byte for byte */
static void equal_ask_price_summary_negative_hundred_thousand_pair(const AskPriceSummaryNegativeHundredThousandPair *read, const AskPriceSummaryNegativeHundredThousandPair *written) {
  for (size_t i = 0; i < 7; i++) { assert(read->raw_ask_price_summary[i] == written->raw_ask_price_summary[i]); }
  assert(read->ask_price_fraction_indicator == written->ask_price_fraction_indicator);
}

/* Ask Price Summary Negative Hundred Thousand Pair: written and read back, then read and written back */
static void check_ask_price_summary_negative_hundred_thousand_pair(void) {
  AskPriceSummaryNegativeHundredThousandPair sent;
  AskPriceSummaryNegativeHundredThousandPair got;
  uint8_t wire[8];
  uint8_t again[8];

  any_ask_price_summary_negative_hundred_thousand_pair(&sent);
  assert(encode_ask_price_summary_negative_hundred_thousand_pair(&sent, wire, 0) == 8);
  assert(decode_ask_price_summary_negative_hundred_thousand_pair(&got, wire, 0) == 8);
  equal_ask_price_summary_negative_hundred_thousand_pair(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_ask_price_summary_negative_hundred_thousand_pair(&got, wire, 0) == 8);
  assert(encode_ask_price_summary_negative_hundred_thousand_pair(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Ask Price Summary Negative Million Pair: 8 bytes ------------------------ */

typedef struct {
  uint8_t raw_ask_price_summary[7];      /* bytes 0 to 6 */
  uint8_t ask_price_fraction_indicator;  /* byte 7 */
} AskPriceSummaryNegativeMillionPair;

/* any Ask Price Summary Negative Million Pair at all: every byte one the checker chooses */
static void any_ask_price_summary_negative_million_pair(AskPriceSummaryNegativeMillionPair *record) {
  for (size_t i = 0; i < 7; i++) { record->raw_ask_price_summary[i] = arbitrary(); }
  record->ask_price_fraction_indicator = arbitrary();
}

/* Ask Price Summary Negative Million Pair to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_ask_price_summary_negative_million_pair(const AskPriceSummaryNegativeMillionPair *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->raw_ask_price_summary[i]; }
  wire[at++] = record->ask_price_fraction_indicator;

  return at;
}

/* Ask Price Summary Negative Million Pair off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_ask_price_summary_negative_million_pair(AskPriceSummaryNegativeMillionPair *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { record->raw_ask_price_summary[i] = wire[at++]; }
  record->ask_price_fraction_indicator = wire[at++];

  return at;
}

/* what was read of Ask Price Summary Negative Million Pair is what was written, byte for byte */
static void equal_ask_price_summary_negative_million_pair(const AskPriceSummaryNegativeMillionPair *read, const AskPriceSummaryNegativeMillionPair *written) {
  for (size_t i = 0; i < 7; i++) { assert(read->raw_ask_price_summary[i] == written->raw_ask_price_summary[i]); }
  assert(read->ask_price_fraction_indicator == written->ask_price_fraction_indicator);
}

/* Ask Price Summary Negative Million Pair: written and read back, then read and written back */
static void check_ask_price_summary_negative_million_pair(void) {
  AskPriceSummaryNegativeMillionPair sent;
  AskPriceSummaryNegativeMillionPair got;
  uint8_t wire[8];
  uint8_t again[8];

  any_ask_price_summary_negative_million_pair(&sent);
  assert(encode_ask_price_summary_negative_million_pair(&sent, wire, 0) == 8);
  assert(decode_ask_price_summary_negative_million_pair(&got, wire, 0) == 8);
  equal_ask_price_summary_negative_million_pair(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_ask_price_summary_negative_million_pair(&got, wire, 0) == 8);
  assert(encode_ask_price_summary_negative_million_pair(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Ask Price Summary Numeric Pair: 8 bytes --------------------------------- */

typedef struct {
  uint8_t ask_price_summary[7];          /* bytes 0 to 6 */
  uint8_t ask_price_fraction_indicator;  /* byte 7 */
} AskPriceSummaryNumericPair;

/* any Ask Price Summary Numeric Pair at all: every byte one the checker chooses */
static void any_ask_price_summary_numeric_pair(AskPriceSummaryNumericPair *record) {
  for (size_t i = 0; i < 7; i++) { record->ask_price_summary[i] = arbitrary(); }
  record->ask_price_fraction_indicator = arbitrary();
}

/* Ask Price Summary Numeric Pair to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_ask_price_summary_numeric_pair(const AskPriceSummaryNumericPair *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->ask_price_summary[i]; }
  wire[at++] = record->ask_price_fraction_indicator;

  return at;
}

/* Ask Price Summary Numeric Pair off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_ask_price_summary_numeric_pair(AskPriceSummaryNumericPair *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { record->ask_price_summary[i] = wire[at++]; }
  record->ask_price_fraction_indicator = wire[at++];

  return at;
}

/* what was read of Ask Price Summary Numeric Pair is what was written, byte for byte */
static void equal_ask_price_summary_numeric_pair(const AskPriceSummaryNumericPair *read, const AskPriceSummaryNumericPair *written) {
  for (size_t i = 0; i < 7; i++) { assert(read->ask_price_summary[i] == written->ask_price_summary[i]); }
  assert(read->ask_price_fraction_indicator == written->ask_price_fraction_indicator);
}

/* Ask Price Summary Numeric Pair: written and read back, then read and written back */
static void check_ask_price_summary_numeric_pair(void) {
  AskPriceSummaryNumericPair sent;
  AskPriceSummaryNumericPair got;
  uint8_t wire[8];
  uint8_t again[8];

  any_ask_price_summary_numeric_pair(&sent);
  assert(encode_ask_price_summary_numeric_pair(&sent, wire, 0) == 8);
  assert(decode_ask_price_summary_numeric_pair(&got, wire, 0) == 8);
  equal_ask_price_summary_numeric_pair(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_ask_price_summary_numeric_pair(&got, wire, 0) == 8);
  assert(encode_ask_price_summary_numeric_pair(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Last Price Negative Whole Pair: 8 bytes --------------------------------- */

typedef struct {
  uint8_t raw_last_price[7];              /* bytes 0 to 6 */
  uint8_t last_price_fraction_indicator;  /* byte 7 */
} LastPriceNegativeWholePair;

/* any Last Price Negative Whole Pair at all: every byte one the checker chooses */
static void any_last_price_negative_whole_pair(LastPriceNegativeWholePair *record) {
  for (size_t i = 0; i < 7; i++) { record->raw_last_price[i] = arbitrary(); }
  record->last_price_fraction_indicator = arbitrary();
}

/* Last Price Negative Whole Pair to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_last_price_negative_whole_pair(const LastPriceNegativeWholePair *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->raw_last_price[i]; }
  wire[at++] = record->last_price_fraction_indicator;

  return at;
}

/* Last Price Negative Whole Pair off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_last_price_negative_whole_pair(LastPriceNegativeWholePair *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { record->raw_last_price[i] = wire[at++]; }
  record->last_price_fraction_indicator = wire[at++];

  return at;
}

/* what was read of Last Price Negative Whole Pair is what was written, byte for byte */
static void equal_last_price_negative_whole_pair(const LastPriceNegativeWholePair *read, const LastPriceNegativeWholePair *written) {
  for (size_t i = 0; i < 7; i++) { assert(read->raw_last_price[i] == written->raw_last_price[i]); }
  assert(read->last_price_fraction_indicator == written->last_price_fraction_indicator);
}

/* Last Price Negative Whole Pair: written and read back, then read and written back */
static void check_last_price_negative_whole_pair(void) {
  LastPriceNegativeWholePair sent;
  LastPriceNegativeWholePair got;
  uint8_t wire[8];
  uint8_t again[8];

  any_last_price_negative_whole_pair(&sent);
  assert(encode_last_price_negative_whole_pair(&sent, wire, 0) == 8);
  assert(decode_last_price_negative_whole_pair(&got, wire, 0) == 8);
  equal_last_price_negative_whole_pair(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_last_price_negative_whole_pair(&got, wire, 0) == 8);
  assert(encode_last_price_negative_whole_pair(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Last Price Negative Ten Pair: 8 bytes ----------------------------------- */

typedef struct {
  uint8_t raw_last_price[7];              /* bytes 0 to 6 */
  uint8_t last_price_fraction_indicator;  /* byte 7 */
} LastPriceNegativeTenPair;

/* any Last Price Negative Ten Pair at all: every byte one the checker chooses */
static void any_last_price_negative_ten_pair(LastPriceNegativeTenPair *record) {
  for (size_t i = 0; i < 7; i++) { record->raw_last_price[i] = arbitrary(); }
  record->last_price_fraction_indicator = arbitrary();
}

/* Last Price Negative Ten Pair to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_last_price_negative_ten_pair(const LastPriceNegativeTenPair *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->raw_last_price[i]; }
  wire[at++] = record->last_price_fraction_indicator;

  return at;
}

/* Last Price Negative Ten Pair off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_last_price_negative_ten_pair(LastPriceNegativeTenPair *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { record->raw_last_price[i] = wire[at++]; }
  record->last_price_fraction_indicator = wire[at++];

  return at;
}

/* what was read of Last Price Negative Ten Pair is what was written, byte for byte */
static void equal_last_price_negative_ten_pair(const LastPriceNegativeTenPair *read, const LastPriceNegativeTenPair *written) {
  for (size_t i = 0; i < 7; i++) { assert(read->raw_last_price[i] == written->raw_last_price[i]); }
  assert(read->last_price_fraction_indicator == written->last_price_fraction_indicator);
}

/* Last Price Negative Ten Pair: written and read back, then read and written back */
static void check_last_price_negative_ten_pair(void) {
  LastPriceNegativeTenPair sent;
  LastPriceNegativeTenPair got;
  uint8_t wire[8];
  uint8_t again[8];

  any_last_price_negative_ten_pair(&sent);
  assert(encode_last_price_negative_ten_pair(&sent, wire, 0) == 8);
  assert(decode_last_price_negative_ten_pair(&got, wire, 0) == 8);
  equal_last_price_negative_ten_pair(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_last_price_negative_ten_pair(&got, wire, 0) == 8);
  assert(encode_last_price_negative_ten_pair(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Last Price Negative Hundred Pair: 8 bytes ------------------------------- */

typedef struct {
  uint8_t raw_last_price[7];              /* bytes 0 to 6 */
  uint8_t last_price_fraction_indicator;  /* byte 7 */
} LastPriceNegativeHundredPair;

/* any Last Price Negative Hundred Pair at all: every byte one the checker chooses */
static void any_last_price_negative_hundred_pair(LastPriceNegativeHundredPair *record) {
  for (size_t i = 0; i < 7; i++) { record->raw_last_price[i] = arbitrary(); }
  record->last_price_fraction_indicator = arbitrary();
}

/* Last Price Negative Hundred Pair to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_last_price_negative_hundred_pair(const LastPriceNegativeHundredPair *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->raw_last_price[i]; }
  wire[at++] = record->last_price_fraction_indicator;

  return at;
}

/* Last Price Negative Hundred Pair off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_last_price_negative_hundred_pair(LastPriceNegativeHundredPair *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { record->raw_last_price[i] = wire[at++]; }
  record->last_price_fraction_indicator = wire[at++];

  return at;
}

/* what was read of Last Price Negative Hundred Pair is what was written, byte for byte */
static void equal_last_price_negative_hundred_pair(const LastPriceNegativeHundredPair *read, const LastPriceNegativeHundredPair *written) {
  for (size_t i = 0; i < 7; i++) { assert(read->raw_last_price[i] == written->raw_last_price[i]); }
  assert(read->last_price_fraction_indicator == written->last_price_fraction_indicator);
}

/* Last Price Negative Hundred Pair: written and read back, then read and written back */
static void check_last_price_negative_hundred_pair(void) {
  LastPriceNegativeHundredPair sent;
  LastPriceNegativeHundredPair got;
  uint8_t wire[8];
  uint8_t again[8];

  any_last_price_negative_hundred_pair(&sent);
  assert(encode_last_price_negative_hundred_pair(&sent, wire, 0) == 8);
  assert(decode_last_price_negative_hundred_pair(&got, wire, 0) == 8);
  equal_last_price_negative_hundred_pair(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_last_price_negative_hundred_pair(&got, wire, 0) == 8);
  assert(encode_last_price_negative_hundred_pair(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Last Price Negative Thousand Pair: 8 bytes ------------------------------ */

typedef struct {
  uint8_t raw_last_price[7];              /* bytes 0 to 6 */
  uint8_t last_price_fraction_indicator;  /* byte 7 */
} LastPriceNegativeThousandPair;

/* any Last Price Negative Thousand Pair at all: every byte one the checker chooses */
static void any_last_price_negative_thousand_pair(LastPriceNegativeThousandPair *record) {
  for (size_t i = 0; i < 7; i++) { record->raw_last_price[i] = arbitrary(); }
  record->last_price_fraction_indicator = arbitrary();
}

/* Last Price Negative Thousand Pair to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_last_price_negative_thousand_pair(const LastPriceNegativeThousandPair *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->raw_last_price[i]; }
  wire[at++] = record->last_price_fraction_indicator;

  return at;
}

/* Last Price Negative Thousand Pair off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_last_price_negative_thousand_pair(LastPriceNegativeThousandPair *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { record->raw_last_price[i] = wire[at++]; }
  record->last_price_fraction_indicator = wire[at++];

  return at;
}

/* what was read of Last Price Negative Thousand Pair is what was written, byte for byte */
static void equal_last_price_negative_thousand_pair(const LastPriceNegativeThousandPair *read, const LastPriceNegativeThousandPair *written) {
  for (size_t i = 0; i < 7; i++) { assert(read->raw_last_price[i] == written->raw_last_price[i]); }
  assert(read->last_price_fraction_indicator == written->last_price_fraction_indicator);
}

/* Last Price Negative Thousand Pair: written and read back, then read and written back */
static void check_last_price_negative_thousand_pair(void) {
  LastPriceNegativeThousandPair sent;
  LastPriceNegativeThousandPair got;
  uint8_t wire[8];
  uint8_t again[8];

  any_last_price_negative_thousand_pair(&sent);
  assert(encode_last_price_negative_thousand_pair(&sent, wire, 0) == 8);
  assert(decode_last_price_negative_thousand_pair(&got, wire, 0) == 8);
  equal_last_price_negative_thousand_pair(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_last_price_negative_thousand_pair(&got, wire, 0) == 8);
  assert(encode_last_price_negative_thousand_pair(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Last Price Negative Ten Thousand Pair: 8 bytes -------------------------- */

typedef struct {
  uint8_t raw_last_price[7];              /* bytes 0 to 6 */
  uint8_t last_price_fraction_indicator;  /* byte 7 */
} LastPriceNegativeTenThousandPair;

/* any Last Price Negative Ten Thousand Pair at all: every byte one the checker chooses */
static void any_last_price_negative_ten_thousand_pair(LastPriceNegativeTenThousandPair *record) {
  for (size_t i = 0; i < 7; i++) { record->raw_last_price[i] = arbitrary(); }
  record->last_price_fraction_indicator = arbitrary();
}

/* Last Price Negative Ten Thousand Pair to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_last_price_negative_ten_thousand_pair(const LastPriceNegativeTenThousandPair *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->raw_last_price[i]; }
  wire[at++] = record->last_price_fraction_indicator;

  return at;
}

/* Last Price Negative Ten Thousand Pair off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_last_price_negative_ten_thousand_pair(LastPriceNegativeTenThousandPair *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { record->raw_last_price[i] = wire[at++]; }
  record->last_price_fraction_indicator = wire[at++];

  return at;
}

/* what was read of Last Price Negative Ten Thousand Pair is what was written, byte for byte */
static void equal_last_price_negative_ten_thousand_pair(const LastPriceNegativeTenThousandPair *read, const LastPriceNegativeTenThousandPair *written) {
  for (size_t i = 0; i < 7; i++) { assert(read->raw_last_price[i] == written->raw_last_price[i]); }
  assert(read->last_price_fraction_indicator == written->last_price_fraction_indicator);
}

/* Last Price Negative Ten Thousand Pair: written and read back, then read and written back */
static void check_last_price_negative_ten_thousand_pair(void) {
  LastPriceNegativeTenThousandPair sent;
  LastPriceNegativeTenThousandPair got;
  uint8_t wire[8];
  uint8_t again[8];

  any_last_price_negative_ten_thousand_pair(&sent);
  assert(encode_last_price_negative_ten_thousand_pair(&sent, wire, 0) == 8);
  assert(decode_last_price_negative_ten_thousand_pair(&got, wire, 0) == 8);
  equal_last_price_negative_ten_thousand_pair(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_last_price_negative_ten_thousand_pair(&got, wire, 0) == 8);
  assert(encode_last_price_negative_ten_thousand_pair(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Last Price Negative Hundred Thousand Pair: 8 bytes ---------------------- */

typedef struct {
  uint8_t raw_last_price[7];              /* bytes 0 to 6 */
  uint8_t last_price_fraction_indicator;  /* byte 7 */
} LastPriceNegativeHundredThousandPair;

/* any Last Price Negative Hundred Thousand Pair at all: every byte one the checker chooses */
static void any_last_price_negative_hundred_thousand_pair(LastPriceNegativeHundredThousandPair *record) {
  for (size_t i = 0; i < 7; i++) { record->raw_last_price[i] = arbitrary(); }
  record->last_price_fraction_indicator = arbitrary();
}

/* Last Price Negative Hundred Thousand Pair to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_last_price_negative_hundred_thousand_pair(const LastPriceNegativeHundredThousandPair *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->raw_last_price[i]; }
  wire[at++] = record->last_price_fraction_indicator;

  return at;
}

/* Last Price Negative Hundred Thousand Pair off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_last_price_negative_hundred_thousand_pair(LastPriceNegativeHundredThousandPair *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { record->raw_last_price[i] = wire[at++]; }
  record->last_price_fraction_indicator = wire[at++];

  return at;
}

/* what was read of Last Price Negative Hundred Thousand Pair is what was written, byte for byte */
static void equal_last_price_negative_hundred_thousand_pair(const LastPriceNegativeHundredThousandPair *read, const LastPriceNegativeHundredThousandPair *written) {
  for (size_t i = 0; i < 7; i++) { assert(read->raw_last_price[i] == written->raw_last_price[i]); }
  assert(read->last_price_fraction_indicator == written->last_price_fraction_indicator);
}

/* Last Price Negative Hundred Thousand Pair: written and read back, then read and written back */
static void check_last_price_negative_hundred_thousand_pair(void) {
  LastPriceNegativeHundredThousandPair sent;
  LastPriceNegativeHundredThousandPair got;
  uint8_t wire[8];
  uint8_t again[8];

  any_last_price_negative_hundred_thousand_pair(&sent);
  assert(encode_last_price_negative_hundred_thousand_pair(&sent, wire, 0) == 8);
  assert(decode_last_price_negative_hundred_thousand_pair(&got, wire, 0) == 8);
  equal_last_price_negative_hundred_thousand_pair(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_last_price_negative_hundred_thousand_pair(&got, wire, 0) == 8);
  assert(encode_last_price_negative_hundred_thousand_pair(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Last Price Negative Million Pair: 8 bytes ------------------------------- */

typedef struct {
  uint8_t raw_last_price[7];              /* bytes 0 to 6 */
  uint8_t last_price_fraction_indicator;  /* byte 7 */
} LastPriceNegativeMillionPair;

/* any Last Price Negative Million Pair at all: every byte one the checker chooses */
static void any_last_price_negative_million_pair(LastPriceNegativeMillionPair *record) {
  for (size_t i = 0; i < 7; i++) { record->raw_last_price[i] = arbitrary(); }
  record->last_price_fraction_indicator = arbitrary();
}

/* Last Price Negative Million Pair to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_last_price_negative_million_pair(const LastPriceNegativeMillionPair *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->raw_last_price[i]; }
  wire[at++] = record->last_price_fraction_indicator;

  return at;
}

/* Last Price Negative Million Pair off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_last_price_negative_million_pair(LastPriceNegativeMillionPair *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { record->raw_last_price[i] = wire[at++]; }
  record->last_price_fraction_indicator = wire[at++];

  return at;
}

/* what was read of Last Price Negative Million Pair is what was written, byte for byte */
static void equal_last_price_negative_million_pair(const LastPriceNegativeMillionPair *read, const LastPriceNegativeMillionPair *written) {
  for (size_t i = 0; i < 7; i++) { assert(read->raw_last_price[i] == written->raw_last_price[i]); }
  assert(read->last_price_fraction_indicator == written->last_price_fraction_indicator);
}

/* Last Price Negative Million Pair: written and read back, then read and written back */
static void check_last_price_negative_million_pair(void) {
  LastPriceNegativeMillionPair sent;
  LastPriceNegativeMillionPair got;
  uint8_t wire[8];
  uint8_t again[8];

  any_last_price_negative_million_pair(&sent);
  assert(encode_last_price_negative_million_pair(&sent, wire, 0) == 8);
  assert(decode_last_price_negative_million_pair(&got, wire, 0) == 8);
  equal_last_price_negative_million_pair(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_last_price_negative_million_pair(&got, wire, 0) == 8);
  assert(encode_last_price_negative_million_pair(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Last Price Numeric Pair: 8 bytes ---------------------------------------- */

typedef struct {
  uint8_t last_price[7];                  /* bytes 0 to 6 */
  uint8_t last_price_fraction_indicator;  /* byte 7 */
} LastPriceNumericPair;

/* any Last Price Numeric Pair at all: every byte one the checker chooses */
static void any_last_price_numeric_pair(LastPriceNumericPair *record) {
  for (size_t i = 0; i < 7; i++) { record->last_price[i] = arbitrary(); }
  record->last_price_fraction_indicator = arbitrary();
}

/* Last Price Numeric Pair to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_last_price_numeric_pair(const LastPriceNumericPair *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->last_price[i]; }
  wire[at++] = record->last_price_fraction_indicator;

  return at;
}

/* Last Price Numeric Pair off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_last_price_numeric_pair(LastPriceNumericPair *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { record->last_price[i] = wire[at++]; }
  record->last_price_fraction_indicator = wire[at++];

  return at;
}

/* what was read of Last Price Numeric Pair is what was written, byte for byte */
static void equal_last_price_numeric_pair(const LastPriceNumericPair *read, const LastPriceNumericPair *written) {
  for (size_t i = 0; i < 7; i++) { assert(read->last_price[i] == written->last_price[i]); }
  assert(read->last_price_fraction_indicator == written->last_price_fraction_indicator);
}

/* Last Price Numeric Pair: written and read back, then read and written back */
static void check_last_price_numeric_pair(void) {
  LastPriceNumericPair sent;
  LastPriceNumericPair got;
  uint8_t wire[8];
  uint8_t again[8];

  any_last_price_numeric_pair(&sent);
  assert(encode_last_price_numeric_pair(&sent, wire, 0) == 8);
  assert(decode_last_price_numeric_pair(&got, wire, 0) == 8);
  equal_last_price_numeric_pair(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_last_price_numeric_pair(&got, wire, 0) == 8);
  assert(encode_last_price_numeric_pair(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Open Price Negative Whole Pair: 8 bytes --------------------------------- */

typedef struct {
  uint8_t raw_open_price[7];              /* bytes 0 to 6 */
  uint8_t open_price_fraction_indicator;  /* byte 7 */
} OpenPriceNegativeWholePair;

/* any Open Price Negative Whole Pair at all: every byte one the checker chooses */
static void any_open_price_negative_whole_pair(OpenPriceNegativeWholePair *record) {
  for (size_t i = 0; i < 7; i++) { record->raw_open_price[i] = arbitrary(); }
  record->open_price_fraction_indicator = arbitrary();
}

/* Open Price Negative Whole Pair to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_open_price_negative_whole_pair(const OpenPriceNegativeWholePair *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->raw_open_price[i]; }
  wire[at++] = record->open_price_fraction_indicator;

  return at;
}

/* Open Price Negative Whole Pair off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_open_price_negative_whole_pair(OpenPriceNegativeWholePair *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { record->raw_open_price[i] = wire[at++]; }
  record->open_price_fraction_indicator = wire[at++];

  return at;
}

/* what was read of Open Price Negative Whole Pair is what was written, byte for byte */
static void equal_open_price_negative_whole_pair(const OpenPriceNegativeWholePair *read, const OpenPriceNegativeWholePair *written) {
  for (size_t i = 0; i < 7; i++) { assert(read->raw_open_price[i] == written->raw_open_price[i]); }
  assert(read->open_price_fraction_indicator == written->open_price_fraction_indicator);
}

/* Open Price Negative Whole Pair: written and read back, then read and written back */
static void check_open_price_negative_whole_pair(void) {
  OpenPriceNegativeWholePair sent;
  OpenPriceNegativeWholePair got;
  uint8_t wire[8];
  uint8_t again[8];

  any_open_price_negative_whole_pair(&sent);
  assert(encode_open_price_negative_whole_pair(&sent, wire, 0) == 8);
  assert(decode_open_price_negative_whole_pair(&got, wire, 0) == 8);
  equal_open_price_negative_whole_pair(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_open_price_negative_whole_pair(&got, wire, 0) == 8);
  assert(encode_open_price_negative_whole_pair(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Open Price Negative Ten Pair: 8 bytes ----------------------------------- */

typedef struct {
  uint8_t raw_open_price[7];              /* bytes 0 to 6 */
  uint8_t open_price_fraction_indicator;  /* byte 7 */
} OpenPriceNegativeTenPair;

/* any Open Price Negative Ten Pair at all: every byte one the checker chooses */
static void any_open_price_negative_ten_pair(OpenPriceNegativeTenPair *record) {
  for (size_t i = 0; i < 7; i++) { record->raw_open_price[i] = arbitrary(); }
  record->open_price_fraction_indicator = arbitrary();
}

/* Open Price Negative Ten Pair to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_open_price_negative_ten_pair(const OpenPriceNegativeTenPair *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->raw_open_price[i]; }
  wire[at++] = record->open_price_fraction_indicator;

  return at;
}

/* Open Price Negative Ten Pair off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_open_price_negative_ten_pair(OpenPriceNegativeTenPair *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { record->raw_open_price[i] = wire[at++]; }
  record->open_price_fraction_indicator = wire[at++];

  return at;
}

/* what was read of Open Price Negative Ten Pair is what was written, byte for byte */
static void equal_open_price_negative_ten_pair(const OpenPriceNegativeTenPair *read, const OpenPriceNegativeTenPair *written) {
  for (size_t i = 0; i < 7; i++) { assert(read->raw_open_price[i] == written->raw_open_price[i]); }
  assert(read->open_price_fraction_indicator == written->open_price_fraction_indicator);
}

/* Open Price Negative Ten Pair: written and read back, then read and written back */
static void check_open_price_negative_ten_pair(void) {
  OpenPriceNegativeTenPair sent;
  OpenPriceNegativeTenPair got;
  uint8_t wire[8];
  uint8_t again[8];

  any_open_price_negative_ten_pair(&sent);
  assert(encode_open_price_negative_ten_pair(&sent, wire, 0) == 8);
  assert(decode_open_price_negative_ten_pair(&got, wire, 0) == 8);
  equal_open_price_negative_ten_pair(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_open_price_negative_ten_pair(&got, wire, 0) == 8);
  assert(encode_open_price_negative_ten_pair(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Open Price Negative Hundred Pair: 8 bytes ------------------------------- */

typedef struct {
  uint8_t raw_open_price[7];              /* bytes 0 to 6 */
  uint8_t open_price_fraction_indicator;  /* byte 7 */
} OpenPriceNegativeHundredPair;

/* any Open Price Negative Hundred Pair at all: every byte one the checker chooses */
static void any_open_price_negative_hundred_pair(OpenPriceNegativeHundredPair *record) {
  for (size_t i = 0; i < 7; i++) { record->raw_open_price[i] = arbitrary(); }
  record->open_price_fraction_indicator = arbitrary();
}

/* Open Price Negative Hundred Pair to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_open_price_negative_hundred_pair(const OpenPriceNegativeHundredPair *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->raw_open_price[i]; }
  wire[at++] = record->open_price_fraction_indicator;

  return at;
}

/* Open Price Negative Hundred Pair off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_open_price_negative_hundred_pair(OpenPriceNegativeHundredPair *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { record->raw_open_price[i] = wire[at++]; }
  record->open_price_fraction_indicator = wire[at++];

  return at;
}

/* what was read of Open Price Negative Hundred Pair is what was written, byte for byte */
static void equal_open_price_negative_hundred_pair(const OpenPriceNegativeHundredPair *read, const OpenPriceNegativeHundredPair *written) {
  for (size_t i = 0; i < 7; i++) { assert(read->raw_open_price[i] == written->raw_open_price[i]); }
  assert(read->open_price_fraction_indicator == written->open_price_fraction_indicator);
}

/* Open Price Negative Hundred Pair: written and read back, then read and written back */
static void check_open_price_negative_hundred_pair(void) {
  OpenPriceNegativeHundredPair sent;
  OpenPriceNegativeHundredPair got;
  uint8_t wire[8];
  uint8_t again[8];

  any_open_price_negative_hundred_pair(&sent);
  assert(encode_open_price_negative_hundred_pair(&sent, wire, 0) == 8);
  assert(decode_open_price_negative_hundred_pair(&got, wire, 0) == 8);
  equal_open_price_negative_hundred_pair(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_open_price_negative_hundred_pair(&got, wire, 0) == 8);
  assert(encode_open_price_negative_hundred_pair(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Open Price Negative Thousand Pair: 8 bytes ------------------------------ */

typedef struct {
  uint8_t raw_open_price[7];              /* bytes 0 to 6 */
  uint8_t open_price_fraction_indicator;  /* byte 7 */
} OpenPriceNegativeThousandPair;

/* any Open Price Negative Thousand Pair at all: every byte one the checker chooses */
static void any_open_price_negative_thousand_pair(OpenPriceNegativeThousandPair *record) {
  for (size_t i = 0; i < 7; i++) { record->raw_open_price[i] = arbitrary(); }
  record->open_price_fraction_indicator = arbitrary();
}

/* Open Price Negative Thousand Pair to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_open_price_negative_thousand_pair(const OpenPriceNegativeThousandPair *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->raw_open_price[i]; }
  wire[at++] = record->open_price_fraction_indicator;

  return at;
}

/* Open Price Negative Thousand Pair off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_open_price_negative_thousand_pair(OpenPriceNegativeThousandPair *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { record->raw_open_price[i] = wire[at++]; }
  record->open_price_fraction_indicator = wire[at++];

  return at;
}

/* what was read of Open Price Negative Thousand Pair is what was written, byte for byte */
static void equal_open_price_negative_thousand_pair(const OpenPriceNegativeThousandPair *read, const OpenPriceNegativeThousandPair *written) {
  for (size_t i = 0; i < 7; i++) { assert(read->raw_open_price[i] == written->raw_open_price[i]); }
  assert(read->open_price_fraction_indicator == written->open_price_fraction_indicator);
}

/* Open Price Negative Thousand Pair: written and read back, then read and written back */
static void check_open_price_negative_thousand_pair(void) {
  OpenPriceNegativeThousandPair sent;
  OpenPriceNegativeThousandPair got;
  uint8_t wire[8];
  uint8_t again[8];

  any_open_price_negative_thousand_pair(&sent);
  assert(encode_open_price_negative_thousand_pair(&sent, wire, 0) == 8);
  assert(decode_open_price_negative_thousand_pair(&got, wire, 0) == 8);
  equal_open_price_negative_thousand_pair(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_open_price_negative_thousand_pair(&got, wire, 0) == 8);
  assert(encode_open_price_negative_thousand_pair(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Open Price Negative Ten Thousand Pair: 8 bytes -------------------------- */

typedef struct {
  uint8_t raw_open_price[7];              /* bytes 0 to 6 */
  uint8_t open_price_fraction_indicator;  /* byte 7 */
} OpenPriceNegativeTenThousandPair;

/* any Open Price Negative Ten Thousand Pair at all: every byte one the checker chooses */
static void any_open_price_negative_ten_thousand_pair(OpenPriceNegativeTenThousandPair *record) {
  for (size_t i = 0; i < 7; i++) { record->raw_open_price[i] = arbitrary(); }
  record->open_price_fraction_indicator = arbitrary();
}

/* Open Price Negative Ten Thousand Pair to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_open_price_negative_ten_thousand_pair(const OpenPriceNegativeTenThousandPair *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->raw_open_price[i]; }
  wire[at++] = record->open_price_fraction_indicator;

  return at;
}

/* Open Price Negative Ten Thousand Pair off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_open_price_negative_ten_thousand_pair(OpenPriceNegativeTenThousandPair *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { record->raw_open_price[i] = wire[at++]; }
  record->open_price_fraction_indicator = wire[at++];

  return at;
}

/* what was read of Open Price Negative Ten Thousand Pair is what was written, byte for byte */
static void equal_open_price_negative_ten_thousand_pair(const OpenPriceNegativeTenThousandPair *read, const OpenPriceNegativeTenThousandPair *written) {
  for (size_t i = 0; i < 7; i++) { assert(read->raw_open_price[i] == written->raw_open_price[i]); }
  assert(read->open_price_fraction_indicator == written->open_price_fraction_indicator);
}

/* Open Price Negative Ten Thousand Pair: written and read back, then read and written back */
static void check_open_price_negative_ten_thousand_pair(void) {
  OpenPriceNegativeTenThousandPair sent;
  OpenPriceNegativeTenThousandPair got;
  uint8_t wire[8];
  uint8_t again[8];

  any_open_price_negative_ten_thousand_pair(&sent);
  assert(encode_open_price_negative_ten_thousand_pair(&sent, wire, 0) == 8);
  assert(decode_open_price_negative_ten_thousand_pair(&got, wire, 0) == 8);
  equal_open_price_negative_ten_thousand_pair(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_open_price_negative_ten_thousand_pair(&got, wire, 0) == 8);
  assert(encode_open_price_negative_ten_thousand_pair(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Open Price Negative Hundred Thousand Pair: 8 bytes ---------------------- */

typedef struct {
  uint8_t raw_open_price[7];              /* bytes 0 to 6 */
  uint8_t open_price_fraction_indicator;  /* byte 7 */
} OpenPriceNegativeHundredThousandPair;

/* any Open Price Negative Hundred Thousand Pair at all: every byte one the checker chooses */
static void any_open_price_negative_hundred_thousand_pair(OpenPriceNegativeHundredThousandPair *record) {
  for (size_t i = 0; i < 7; i++) { record->raw_open_price[i] = arbitrary(); }
  record->open_price_fraction_indicator = arbitrary();
}

/* Open Price Negative Hundred Thousand Pair to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_open_price_negative_hundred_thousand_pair(const OpenPriceNegativeHundredThousandPair *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->raw_open_price[i]; }
  wire[at++] = record->open_price_fraction_indicator;

  return at;
}

/* Open Price Negative Hundred Thousand Pair off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_open_price_negative_hundred_thousand_pair(OpenPriceNegativeHundredThousandPair *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { record->raw_open_price[i] = wire[at++]; }
  record->open_price_fraction_indicator = wire[at++];

  return at;
}

/* what was read of Open Price Negative Hundred Thousand Pair is what was written, byte for byte */
static void equal_open_price_negative_hundred_thousand_pair(const OpenPriceNegativeHundredThousandPair *read, const OpenPriceNegativeHundredThousandPair *written) {
  for (size_t i = 0; i < 7; i++) { assert(read->raw_open_price[i] == written->raw_open_price[i]); }
  assert(read->open_price_fraction_indicator == written->open_price_fraction_indicator);
}

/* Open Price Negative Hundred Thousand Pair: written and read back, then read and written back */
static void check_open_price_negative_hundred_thousand_pair(void) {
  OpenPriceNegativeHundredThousandPair sent;
  OpenPriceNegativeHundredThousandPair got;
  uint8_t wire[8];
  uint8_t again[8];

  any_open_price_negative_hundred_thousand_pair(&sent);
  assert(encode_open_price_negative_hundred_thousand_pair(&sent, wire, 0) == 8);
  assert(decode_open_price_negative_hundred_thousand_pair(&got, wire, 0) == 8);
  equal_open_price_negative_hundred_thousand_pair(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_open_price_negative_hundred_thousand_pair(&got, wire, 0) == 8);
  assert(encode_open_price_negative_hundred_thousand_pair(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Open Price Negative Million Pair: 8 bytes ------------------------------- */

typedef struct {
  uint8_t raw_open_price[7];              /* bytes 0 to 6 */
  uint8_t open_price_fraction_indicator;  /* byte 7 */
} OpenPriceNegativeMillionPair;

/* any Open Price Negative Million Pair at all: every byte one the checker chooses */
static void any_open_price_negative_million_pair(OpenPriceNegativeMillionPair *record) {
  for (size_t i = 0; i < 7; i++) { record->raw_open_price[i] = arbitrary(); }
  record->open_price_fraction_indicator = arbitrary();
}

/* Open Price Negative Million Pair to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_open_price_negative_million_pair(const OpenPriceNegativeMillionPair *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->raw_open_price[i]; }
  wire[at++] = record->open_price_fraction_indicator;

  return at;
}

/* Open Price Negative Million Pair off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_open_price_negative_million_pair(OpenPriceNegativeMillionPair *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { record->raw_open_price[i] = wire[at++]; }
  record->open_price_fraction_indicator = wire[at++];

  return at;
}

/* what was read of Open Price Negative Million Pair is what was written, byte for byte */
static void equal_open_price_negative_million_pair(const OpenPriceNegativeMillionPair *read, const OpenPriceNegativeMillionPair *written) {
  for (size_t i = 0; i < 7; i++) { assert(read->raw_open_price[i] == written->raw_open_price[i]); }
  assert(read->open_price_fraction_indicator == written->open_price_fraction_indicator);
}

/* Open Price Negative Million Pair: written and read back, then read and written back */
static void check_open_price_negative_million_pair(void) {
  OpenPriceNegativeMillionPair sent;
  OpenPriceNegativeMillionPair got;
  uint8_t wire[8];
  uint8_t again[8];

  any_open_price_negative_million_pair(&sent);
  assert(encode_open_price_negative_million_pair(&sent, wire, 0) == 8);
  assert(decode_open_price_negative_million_pair(&got, wire, 0) == 8);
  equal_open_price_negative_million_pair(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_open_price_negative_million_pair(&got, wire, 0) == 8);
  assert(encode_open_price_negative_million_pair(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Open Price Numeric Pair: 8 bytes ---------------------------------------- */

typedef struct {
  uint8_t open_price[7];                  /* bytes 0 to 6 */
  uint8_t open_price_fraction_indicator;  /* byte 7 */
} OpenPriceNumericPair;

/* any Open Price Numeric Pair at all: every byte one the checker chooses */
static void any_open_price_numeric_pair(OpenPriceNumericPair *record) {
  for (size_t i = 0; i < 7; i++) { record->open_price[i] = arbitrary(); }
  record->open_price_fraction_indicator = arbitrary();
}

/* Open Price Numeric Pair to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_open_price_numeric_pair(const OpenPriceNumericPair *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->open_price[i]; }
  wire[at++] = record->open_price_fraction_indicator;

  return at;
}

/* Open Price Numeric Pair off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_open_price_numeric_pair(OpenPriceNumericPair *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { record->open_price[i] = wire[at++]; }
  record->open_price_fraction_indicator = wire[at++];

  return at;
}

/* what was read of Open Price Numeric Pair is what was written, byte for byte */
static void equal_open_price_numeric_pair(const OpenPriceNumericPair *read, const OpenPriceNumericPair *written) {
  for (size_t i = 0; i < 7; i++) { assert(read->open_price[i] == written->open_price[i]); }
  assert(read->open_price_fraction_indicator == written->open_price_fraction_indicator);
}

/* Open Price Numeric Pair: written and read back, then read and written back */
static void check_open_price_numeric_pair(void) {
  OpenPriceNumericPair sent;
  OpenPriceNumericPair got;
  uint8_t wire[8];
  uint8_t again[8];

  any_open_price_numeric_pair(&sent);
  assert(encode_open_price_numeric_pair(&sent, wire, 0) == 8);
  assert(decode_open_price_numeric_pair(&got, wire, 0) == 8);
  equal_open_price_numeric_pair(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_open_price_numeric_pair(&got, wire, 0) == 8);
  assert(encode_open_price_numeric_pair(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- High Price Negative Whole Pair: 8 bytes --------------------------------- */

typedef struct {
  uint8_t raw_high_price[7];              /* bytes 0 to 6 */
  uint8_t high_price_fraction_indicator;  /* byte 7 */
} HighPriceNegativeWholePair;

/* any High Price Negative Whole Pair at all: every byte one the checker chooses */
static void any_high_price_negative_whole_pair(HighPriceNegativeWholePair *record) {
  for (size_t i = 0; i < 7; i++) { record->raw_high_price[i] = arbitrary(); }
  record->high_price_fraction_indicator = arbitrary();
}

/* High Price Negative Whole Pair to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_high_price_negative_whole_pair(const HighPriceNegativeWholePair *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->raw_high_price[i]; }
  wire[at++] = record->high_price_fraction_indicator;

  return at;
}

/* High Price Negative Whole Pair off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_high_price_negative_whole_pair(HighPriceNegativeWholePair *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { record->raw_high_price[i] = wire[at++]; }
  record->high_price_fraction_indicator = wire[at++];

  return at;
}

/* what was read of High Price Negative Whole Pair is what was written, byte for byte */
static void equal_high_price_negative_whole_pair(const HighPriceNegativeWholePair *read, const HighPriceNegativeWholePair *written) {
  for (size_t i = 0; i < 7; i++) { assert(read->raw_high_price[i] == written->raw_high_price[i]); }
  assert(read->high_price_fraction_indicator == written->high_price_fraction_indicator);
}

/* High Price Negative Whole Pair: written and read back, then read and written back */
static void check_high_price_negative_whole_pair(void) {
  HighPriceNegativeWholePair sent;
  HighPriceNegativeWholePair got;
  uint8_t wire[8];
  uint8_t again[8];

  any_high_price_negative_whole_pair(&sent);
  assert(encode_high_price_negative_whole_pair(&sent, wire, 0) == 8);
  assert(decode_high_price_negative_whole_pair(&got, wire, 0) == 8);
  equal_high_price_negative_whole_pair(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_high_price_negative_whole_pair(&got, wire, 0) == 8);
  assert(encode_high_price_negative_whole_pair(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- High Price Negative Ten Pair: 8 bytes ----------------------------------- */

typedef struct {
  uint8_t raw_high_price[7];              /* bytes 0 to 6 */
  uint8_t high_price_fraction_indicator;  /* byte 7 */
} HighPriceNegativeTenPair;

/* any High Price Negative Ten Pair at all: every byte one the checker chooses */
static void any_high_price_negative_ten_pair(HighPriceNegativeTenPair *record) {
  for (size_t i = 0; i < 7; i++) { record->raw_high_price[i] = arbitrary(); }
  record->high_price_fraction_indicator = arbitrary();
}

/* High Price Negative Ten Pair to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_high_price_negative_ten_pair(const HighPriceNegativeTenPair *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->raw_high_price[i]; }
  wire[at++] = record->high_price_fraction_indicator;

  return at;
}

/* High Price Negative Ten Pair off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_high_price_negative_ten_pair(HighPriceNegativeTenPair *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { record->raw_high_price[i] = wire[at++]; }
  record->high_price_fraction_indicator = wire[at++];

  return at;
}

/* what was read of High Price Negative Ten Pair is what was written, byte for byte */
static void equal_high_price_negative_ten_pair(const HighPriceNegativeTenPair *read, const HighPriceNegativeTenPair *written) {
  for (size_t i = 0; i < 7; i++) { assert(read->raw_high_price[i] == written->raw_high_price[i]); }
  assert(read->high_price_fraction_indicator == written->high_price_fraction_indicator);
}

/* High Price Negative Ten Pair: written and read back, then read and written back */
static void check_high_price_negative_ten_pair(void) {
  HighPriceNegativeTenPair sent;
  HighPriceNegativeTenPair got;
  uint8_t wire[8];
  uint8_t again[8];

  any_high_price_negative_ten_pair(&sent);
  assert(encode_high_price_negative_ten_pair(&sent, wire, 0) == 8);
  assert(decode_high_price_negative_ten_pair(&got, wire, 0) == 8);
  equal_high_price_negative_ten_pair(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_high_price_negative_ten_pair(&got, wire, 0) == 8);
  assert(encode_high_price_negative_ten_pair(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- High Price Negative Hundred Pair: 8 bytes ------------------------------- */

typedef struct {
  uint8_t raw_high_price[7];              /* bytes 0 to 6 */
  uint8_t high_price_fraction_indicator;  /* byte 7 */
} HighPriceNegativeHundredPair;

/* any High Price Negative Hundred Pair at all: every byte one the checker chooses */
static void any_high_price_negative_hundred_pair(HighPriceNegativeHundredPair *record) {
  for (size_t i = 0; i < 7; i++) { record->raw_high_price[i] = arbitrary(); }
  record->high_price_fraction_indicator = arbitrary();
}

/* High Price Negative Hundred Pair to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_high_price_negative_hundred_pair(const HighPriceNegativeHundredPair *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->raw_high_price[i]; }
  wire[at++] = record->high_price_fraction_indicator;

  return at;
}

/* High Price Negative Hundred Pair off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_high_price_negative_hundred_pair(HighPriceNegativeHundredPair *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { record->raw_high_price[i] = wire[at++]; }
  record->high_price_fraction_indicator = wire[at++];

  return at;
}

/* what was read of High Price Negative Hundred Pair is what was written, byte for byte */
static void equal_high_price_negative_hundred_pair(const HighPriceNegativeHundredPair *read, const HighPriceNegativeHundredPair *written) {
  for (size_t i = 0; i < 7; i++) { assert(read->raw_high_price[i] == written->raw_high_price[i]); }
  assert(read->high_price_fraction_indicator == written->high_price_fraction_indicator);
}

/* High Price Negative Hundred Pair: written and read back, then read and written back */
static void check_high_price_negative_hundred_pair(void) {
  HighPriceNegativeHundredPair sent;
  HighPriceNegativeHundredPair got;
  uint8_t wire[8];
  uint8_t again[8];

  any_high_price_negative_hundred_pair(&sent);
  assert(encode_high_price_negative_hundred_pair(&sent, wire, 0) == 8);
  assert(decode_high_price_negative_hundred_pair(&got, wire, 0) == 8);
  equal_high_price_negative_hundred_pair(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_high_price_negative_hundred_pair(&got, wire, 0) == 8);
  assert(encode_high_price_negative_hundred_pair(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- High Price Negative Thousand Pair: 8 bytes ------------------------------ */

typedef struct {
  uint8_t raw_high_price[7];              /* bytes 0 to 6 */
  uint8_t high_price_fraction_indicator;  /* byte 7 */
} HighPriceNegativeThousandPair;

/* any High Price Negative Thousand Pair at all: every byte one the checker chooses */
static void any_high_price_negative_thousand_pair(HighPriceNegativeThousandPair *record) {
  for (size_t i = 0; i < 7; i++) { record->raw_high_price[i] = arbitrary(); }
  record->high_price_fraction_indicator = arbitrary();
}

/* High Price Negative Thousand Pair to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_high_price_negative_thousand_pair(const HighPriceNegativeThousandPair *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->raw_high_price[i]; }
  wire[at++] = record->high_price_fraction_indicator;

  return at;
}

/* High Price Negative Thousand Pair off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_high_price_negative_thousand_pair(HighPriceNegativeThousandPair *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { record->raw_high_price[i] = wire[at++]; }
  record->high_price_fraction_indicator = wire[at++];

  return at;
}

/* what was read of High Price Negative Thousand Pair is what was written, byte for byte */
static void equal_high_price_negative_thousand_pair(const HighPriceNegativeThousandPair *read, const HighPriceNegativeThousandPair *written) {
  for (size_t i = 0; i < 7; i++) { assert(read->raw_high_price[i] == written->raw_high_price[i]); }
  assert(read->high_price_fraction_indicator == written->high_price_fraction_indicator);
}

/* High Price Negative Thousand Pair: written and read back, then read and written back */
static void check_high_price_negative_thousand_pair(void) {
  HighPriceNegativeThousandPair sent;
  HighPriceNegativeThousandPair got;
  uint8_t wire[8];
  uint8_t again[8];

  any_high_price_negative_thousand_pair(&sent);
  assert(encode_high_price_negative_thousand_pair(&sent, wire, 0) == 8);
  assert(decode_high_price_negative_thousand_pair(&got, wire, 0) == 8);
  equal_high_price_negative_thousand_pair(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_high_price_negative_thousand_pair(&got, wire, 0) == 8);
  assert(encode_high_price_negative_thousand_pair(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- High Price Negative Ten Thousand Pair: 8 bytes -------------------------- */

typedef struct {
  uint8_t raw_high_price[7];              /* bytes 0 to 6 */
  uint8_t high_price_fraction_indicator;  /* byte 7 */
} HighPriceNegativeTenThousandPair;

/* any High Price Negative Ten Thousand Pair at all: every byte one the checker chooses */
static void any_high_price_negative_ten_thousand_pair(HighPriceNegativeTenThousandPair *record) {
  for (size_t i = 0; i < 7; i++) { record->raw_high_price[i] = arbitrary(); }
  record->high_price_fraction_indicator = arbitrary();
}

/* High Price Negative Ten Thousand Pair to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_high_price_negative_ten_thousand_pair(const HighPriceNegativeTenThousandPair *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->raw_high_price[i]; }
  wire[at++] = record->high_price_fraction_indicator;

  return at;
}

/* High Price Negative Ten Thousand Pair off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_high_price_negative_ten_thousand_pair(HighPriceNegativeTenThousandPair *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { record->raw_high_price[i] = wire[at++]; }
  record->high_price_fraction_indicator = wire[at++];

  return at;
}

/* what was read of High Price Negative Ten Thousand Pair is what was written, byte for byte */
static void equal_high_price_negative_ten_thousand_pair(const HighPriceNegativeTenThousandPair *read, const HighPriceNegativeTenThousandPair *written) {
  for (size_t i = 0; i < 7; i++) { assert(read->raw_high_price[i] == written->raw_high_price[i]); }
  assert(read->high_price_fraction_indicator == written->high_price_fraction_indicator);
}

/* High Price Negative Ten Thousand Pair: written and read back, then read and written back */
static void check_high_price_negative_ten_thousand_pair(void) {
  HighPriceNegativeTenThousandPair sent;
  HighPriceNegativeTenThousandPair got;
  uint8_t wire[8];
  uint8_t again[8];

  any_high_price_negative_ten_thousand_pair(&sent);
  assert(encode_high_price_negative_ten_thousand_pair(&sent, wire, 0) == 8);
  assert(decode_high_price_negative_ten_thousand_pair(&got, wire, 0) == 8);
  equal_high_price_negative_ten_thousand_pair(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_high_price_negative_ten_thousand_pair(&got, wire, 0) == 8);
  assert(encode_high_price_negative_ten_thousand_pair(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- High Price Negative Hundred Thousand Pair: 8 bytes ---------------------- */

typedef struct {
  uint8_t raw_high_price[7];              /* bytes 0 to 6 */
  uint8_t high_price_fraction_indicator;  /* byte 7 */
} HighPriceNegativeHundredThousandPair;

/* any High Price Negative Hundred Thousand Pair at all: every byte one the checker chooses */
static void any_high_price_negative_hundred_thousand_pair(HighPriceNegativeHundredThousandPair *record) {
  for (size_t i = 0; i < 7; i++) { record->raw_high_price[i] = arbitrary(); }
  record->high_price_fraction_indicator = arbitrary();
}

/* High Price Negative Hundred Thousand Pair to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_high_price_negative_hundred_thousand_pair(const HighPriceNegativeHundredThousandPair *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->raw_high_price[i]; }
  wire[at++] = record->high_price_fraction_indicator;

  return at;
}

/* High Price Negative Hundred Thousand Pair off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_high_price_negative_hundred_thousand_pair(HighPriceNegativeHundredThousandPair *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { record->raw_high_price[i] = wire[at++]; }
  record->high_price_fraction_indicator = wire[at++];

  return at;
}

/* what was read of High Price Negative Hundred Thousand Pair is what was written, byte for byte */
static void equal_high_price_negative_hundred_thousand_pair(const HighPriceNegativeHundredThousandPair *read, const HighPriceNegativeHundredThousandPair *written) {
  for (size_t i = 0; i < 7; i++) { assert(read->raw_high_price[i] == written->raw_high_price[i]); }
  assert(read->high_price_fraction_indicator == written->high_price_fraction_indicator);
}

/* High Price Negative Hundred Thousand Pair: written and read back, then read and written back */
static void check_high_price_negative_hundred_thousand_pair(void) {
  HighPriceNegativeHundredThousandPair sent;
  HighPriceNegativeHundredThousandPair got;
  uint8_t wire[8];
  uint8_t again[8];

  any_high_price_negative_hundred_thousand_pair(&sent);
  assert(encode_high_price_negative_hundred_thousand_pair(&sent, wire, 0) == 8);
  assert(decode_high_price_negative_hundred_thousand_pair(&got, wire, 0) == 8);
  equal_high_price_negative_hundred_thousand_pair(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_high_price_negative_hundred_thousand_pair(&got, wire, 0) == 8);
  assert(encode_high_price_negative_hundred_thousand_pair(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- High Price Negative Million Pair: 8 bytes ------------------------------- */

typedef struct {
  uint8_t raw_high_price[7];              /* bytes 0 to 6 */
  uint8_t high_price_fraction_indicator;  /* byte 7 */
} HighPriceNegativeMillionPair;

/* any High Price Negative Million Pair at all: every byte one the checker chooses */
static void any_high_price_negative_million_pair(HighPriceNegativeMillionPair *record) {
  for (size_t i = 0; i < 7; i++) { record->raw_high_price[i] = arbitrary(); }
  record->high_price_fraction_indicator = arbitrary();
}

/* High Price Negative Million Pair to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_high_price_negative_million_pair(const HighPriceNegativeMillionPair *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->raw_high_price[i]; }
  wire[at++] = record->high_price_fraction_indicator;

  return at;
}

/* High Price Negative Million Pair off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_high_price_negative_million_pair(HighPriceNegativeMillionPair *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { record->raw_high_price[i] = wire[at++]; }
  record->high_price_fraction_indicator = wire[at++];

  return at;
}

/* what was read of High Price Negative Million Pair is what was written, byte for byte */
static void equal_high_price_negative_million_pair(const HighPriceNegativeMillionPair *read, const HighPriceNegativeMillionPair *written) {
  for (size_t i = 0; i < 7; i++) { assert(read->raw_high_price[i] == written->raw_high_price[i]); }
  assert(read->high_price_fraction_indicator == written->high_price_fraction_indicator);
}

/* High Price Negative Million Pair: written and read back, then read and written back */
static void check_high_price_negative_million_pair(void) {
  HighPriceNegativeMillionPair sent;
  HighPriceNegativeMillionPair got;
  uint8_t wire[8];
  uint8_t again[8];

  any_high_price_negative_million_pair(&sent);
  assert(encode_high_price_negative_million_pair(&sent, wire, 0) == 8);
  assert(decode_high_price_negative_million_pair(&got, wire, 0) == 8);
  equal_high_price_negative_million_pair(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_high_price_negative_million_pair(&got, wire, 0) == 8);
  assert(encode_high_price_negative_million_pair(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- High Price Numeric Pair: 8 bytes ---------------------------------------- */

typedef struct {
  uint8_t high_price[7];                  /* bytes 0 to 6 */
  uint8_t high_price_fraction_indicator;  /* byte 7 */
} HighPriceNumericPair;

/* any High Price Numeric Pair at all: every byte one the checker chooses */
static void any_high_price_numeric_pair(HighPriceNumericPair *record) {
  for (size_t i = 0; i < 7; i++) { record->high_price[i] = arbitrary(); }
  record->high_price_fraction_indicator = arbitrary();
}

/* High Price Numeric Pair to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_high_price_numeric_pair(const HighPriceNumericPair *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->high_price[i]; }
  wire[at++] = record->high_price_fraction_indicator;

  return at;
}

/* High Price Numeric Pair off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_high_price_numeric_pair(HighPriceNumericPair *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { record->high_price[i] = wire[at++]; }
  record->high_price_fraction_indicator = wire[at++];

  return at;
}

/* what was read of High Price Numeric Pair is what was written, byte for byte */
static void equal_high_price_numeric_pair(const HighPriceNumericPair *read, const HighPriceNumericPair *written) {
  for (size_t i = 0; i < 7; i++) { assert(read->high_price[i] == written->high_price[i]); }
  assert(read->high_price_fraction_indicator == written->high_price_fraction_indicator);
}

/* High Price Numeric Pair: written and read back, then read and written back */
static void check_high_price_numeric_pair(void) {
  HighPriceNumericPair sent;
  HighPriceNumericPair got;
  uint8_t wire[8];
  uint8_t again[8];

  any_high_price_numeric_pair(&sent);
  assert(encode_high_price_numeric_pair(&sent, wire, 0) == 8);
  assert(decode_high_price_numeric_pair(&got, wire, 0) == 8);
  equal_high_price_numeric_pair(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_high_price_numeric_pair(&got, wire, 0) == 8);
  assert(encode_high_price_numeric_pair(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Low Price Negative Whole Pair: 8 bytes ---------------------------------- */

typedef struct {
  uint8_t raw_low_price[7];              /* bytes 0 to 6 */
  uint8_t low_price_fraction_indicator;  /* byte 7 */
} LowPriceNegativeWholePair;

/* any Low Price Negative Whole Pair at all: every byte one the checker chooses */
static void any_low_price_negative_whole_pair(LowPriceNegativeWholePair *record) {
  for (size_t i = 0; i < 7; i++) { record->raw_low_price[i] = arbitrary(); }
  record->low_price_fraction_indicator = arbitrary();
}

/* Low Price Negative Whole Pair to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_low_price_negative_whole_pair(const LowPriceNegativeWholePair *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->raw_low_price[i]; }
  wire[at++] = record->low_price_fraction_indicator;

  return at;
}

/* Low Price Negative Whole Pair off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_low_price_negative_whole_pair(LowPriceNegativeWholePair *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { record->raw_low_price[i] = wire[at++]; }
  record->low_price_fraction_indicator = wire[at++];

  return at;
}

/* what was read of Low Price Negative Whole Pair is what was written, byte for byte */
static void equal_low_price_negative_whole_pair(const LowPriceNegativeWholePair *read, const LowPriceNegativeWholePair *written) {
  for (size_t i = 0; i < 7; i++) { assert(read->raw_low_price[i] == written->raw_low_price[i]); }
  assert(read->low_price_fraction_indicator == written->low_price_fraction_indicator);
}

/* Low Price Negative Whole Pair: written and read back, then read and written back */
static void check_low_price_negative_whole_pair(void) {
  LowPriceNegativeWholePair sent;
  LowPriceNegativeWholePair got;
  uint8_t wire[8];
  uint8_t again[8];

  any_low_price_negative_whole_pair(&sent);
  assert(encode_low_price_negative_whole_pair(&sent, wire, 0) == 8);
  assert(decode_low_price_negative_whole_pair(&got, wire, 0) == 8);
  equal_low_price_negative_whole_pair(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_low_price_negative_whole_pair(&got, wire, 0) == 8);
  assert(encode_low_price_negative_whole_pair(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Low Price Negative Ten Pair: 8 bytes ------------------------------------ */

typedef struct {
  uint8_t raw_low_price[7];              /* bytes 0 to 6 */
  uint8_t low_price_fraction_indicator;  /* byte 7 */
} LowPriceNegativeTenPair;

/* any Low Price Negative Ten Pair at all: every byte one the checker chooses */
static void any_low_price_negative_ten_pair(LowPriceNegativeTenPair *record) {
  for (size_t i = 0; i < 7; i++) { record->raw_low_price[i] = arbitrary(); }
  record->low_price_fraction_indicator = arbitrary();
}

/* Low Price Negative Ten Pair to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_low_price_negative_ten_pair(const LowPriceNegativeTenPair *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->raw_low_price[i]; }
  wire[at++] = record->low_price_fraction_indicator;

  return at;
}

/* Low Price Negative Ten Pair off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_low_price_negative_ten_pair(LowPriceNegativeTenPair *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { record->raw_low_price[i] = wire[at++]; }
  record->low_price_fraction_indicator = wire[at++];

  return at;
}

/* what was read of Low Price Negative Ten Pair is what was written, byte for byte */
static void equal_low_price_negative_ten_pair(const LowPriceNegativeTenPair *read, const LowPriceNegativeTenPair *written) {
  for (size_t i = 0; i < 7; i++) { assert(read->raw_low_price[i] == written->raw_low_price[i]); }
  assert(read->low_price_fraction_indicator == written->low_price_fraction_indicator);
}

/* Low Price Negative Ten Pair: written and read back, then read and written back */
static void check_low_price_negative_ten_pair(void) {
  LowPriceNegativeTenPair sent;
  LowPriceNegativeTenPair got;
  uint8_t wire[8];
  uint8_t again[8];

  any_low_price_negative_ten_pair(&sent);
  assert(encode_low_price_negative_ten_pair(&sent, wire, 0) == 8);
  assert(decode_low_price_negative_ten_pair(&got, wire, 0) == 8);
  equal_low_price_negative_ten_pair(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_low_price_negative_ten_pair(&got, wire, 0) == 8);
  assert(encode_low_price_negative_ten_pair(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Low Price Negative Hundred Pair: 8 bytes -------------------------------- */

typedef struct {
  uint8_t raw_low_price[7];              /* bytes 0 to 6 */
  uint8_t low_price_fraction_indicator;  /* byte 7 */
} LowPriceNegativeHundredPair;

/* any Low Price Negative Hundred Pair at all: every byte one the checker chooses */
static void any_low_price_negative_hundred_pair(LowPriceNegativeHundredPair *record) {
  for (size_t i = 0; i < 7; i++) { record->raw_low_price[i] = arbitrary(); }
  record->low_price_fraction_indicator = arbitrary();
}

/* Low Price Negative Hundred Pair to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_low_price_negative_hundred_pair(const LowPriceNegativeHundredPair *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->raw_low_price[i]; }
  wire[at++] = record->low_price_fraction_indicator;

  return at;
}

/* Low Price Negative Hundred Pair off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_low_price_negative_hundred_pair(LowPriceNegativeHundredPair *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { record->raw_low_price[i] = wire[at++]; }
  record->low_price_fraction_indicator = wire[at++];

  return at;
}

/* what was read of Low Price Negative Hundred Pair is what was written, byte for byte */
static void equal_low_price_negative_hundred_pair(const LowPriceNegativeHundredPair *read, const LowPriceNegativeHundredPair *written) {
  for (size_t i = 0; i < 7; i++) { assert(read->raw_low_price[i] == written->raw_low_price[i]); }
  assert(read->low_price_fraction_indicator == written->low_price_fraction_indicator);
}

/* Low Price Negative Hundred Pair: written and read back, then read and written back */
static void check_low_price_negative_hundred_pair(void) {
  LowPriceNegativeHundredPair sent;
  LowPriceNegativeHundredPair got;
  uint8_t wire[8];
  uint8_t again[8];

  any_low_price_negative_hundred_pair(&sent);
  assert(encode_low_price_negative_hundred_pair(&sent, wire, 0) == 8);
  assert(decode_low_price_negative_hundred_pair(&got, wire, 0) == 8);
  equal_low_price_negative_hundred_pair(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_low_price_negative_hundred_pair(&got, wire, 0) == 8);
  assert(encode_low_price_negative_hundred_pair(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Low Price Negative Thousand Pair: 8 bytes ------------------------------- */

typedef struct {
  uint8_t raw_low_price[7];              /* bytes 0 to 6 */
  uint8_t low_price_fraction_indicator;  /* byte 7 */
} LowPriceNegativeThousandPair;

/* any Low Price Negative Thousand Pair at all: every byte one the checker chooses */
static void any_low_price_negative_thousand_pair(LowPriceNegativeThousandPair *record) {
  for (size_t i = 0; i < 7; i++) { record->raw_low_price[i] = arbitrary(); }
  record->low_price_fraction_indicator = arbitrary();
}

/* Low Price Negative Thousand Pair to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_low_price_negative_thousand_pair(const LowPriceNegativeThousandPair *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->raw_low_price[i]; }
  wire[at++] = record->low_price_fraction_indicator;

  return at;
}

/* Low Price Negative Thousand Pair off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_low_price_negative_thousand_pair(LowPriceNegativeThousandPair *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { record->raw_low_price[i] = wire[at++]; }
  record->low_price_fraction_indicator = wire[at++];

  return at;
}

/* what was read of Low Price Negative Thousand Pair is what was written, byte for byte */
static void equal_low_price_negative_thousand_pair(const LowPriceNegativeThousandPair *read, const LowPriceNegativeThousandPair *written) {
  for (size_t i = 0; i < 7; i++) { assert(read->raw_low_price[i] == written->raw_low_price[i]); }
  assert(read->low_price_fraction_indicator == written->low_price_fraction_indicator);
}

/* Low Price Negative Thousand Pair: written and read back, then read and written back */
static void check_low_price_negative_thousand_pair(void) {
  LowPriceNegativeThousandPair sent;
  LowPriceNegativeThousandPair got;
  uint8_t wire[8];
  uint8_t again[8];

  any_low_price_negative_thousand_pair(&sent);
  assert(encode_low_price_negative_thousand_pair(&sent, wire, 0) == 8);
  assert(decode_low_price_negative_thousand_pair(&got, wire, 0) == 8);
  equal_low_price_negative_thousand_pair(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_low_price_negative_thousand_pair(&got, wire, 0) == 8);
  assert(encode_low_price_negative_thousand_pair(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Low Price Negative Ten Thousand Pair: 8 bytes --------------------------- */

typedef struct {
  uint8_t raw_low_price[7];              /* bytes 0 to 6 */
  uint8_t low_price_fraction_indicator;  /* byte 7 */
} LowPriceNegativeTenThousandPair;

/* any Low Price Negative Ten Thousand Pair at all: every byte one the checker chooses */
static void any_low_price_negative_ten_thousand_pair(LowPriceNegativeTenThousandPair *record) {
  for (size_t i = 0; i < 7; i++) { record->raw_low_price[i] = arbitrary(); }
  record->low_price_fraction_indicator = arbitrary();
}

/* Low Price Negative Ten Thousand Pair to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_low_price_negative_ten_thousand_pair(const LowPriceNegativeTenThousandPair *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->raw_low_price[i]; }
  wire[at++] = record->low_price_fraction_indicator;

  return at;
}

/* Low Price Negative Ten Thousand Pair off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_low_price_negative_ten_thousand_pair(LowPriceNegativeTenThousandPair *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { record->raw_low_price[i] = wire[at++]; }
  record->low_price_fraction_indicator = wire[at++];

  return at;
}

/* what was read of Low Price Negative Ten Thousand Pair is what was written, byte for byte */
static void equal_low_price_negative_ten_thousand_pair(const LowPriceNegativeTenThousandPair *read, const LowPriceNegativeTenThousandPair *written) {
  for (size_t i = 0; i < 7; i++) { assert(read->raw_low_price[i] == written->raw_low_price[i]); }
  assert(read->low_price_fraction_indicator == written->low_price_fraction_indicator);
}

/* Low Price Negative Ten Thousand Pair: written and read back, then read and written back */
static void check_low_price_negative_ten_thousand_pair(void) {
  LowPriceNegativeTenThousandPair sent;
  LowPriceNegativeTenThousandPair got;
  uint8_t wire[8];
  uint8_t again[8];

  any_low_price_negative_ten_thousand_pair(&sent);
  assert(encode_low_price_negative_ten_thousand_pair(&sent, wire, 0) == 8);
  assert(decode_low_price_negative_ten_thousand_pair(&got, wire, 0) == 8);
  equal_low_price_negative_ten_thousand_pair(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_low_price_negative_ten_thousand_pair(&got, wire, 0) == 8);
  assert(encode_low_price_negative_ten_thousand_pair(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Low Price Negative Hundred Thousand Pair: 8 bytes ----------------------- */

typedef struct {
  uint8_t raw_low_price[7];              /* bytes 0 to 6 */
  uint8_t low_price_fraction_indicator;  /* byte 7 */
} LowPriceNegativeHundredThousandPair;

/* any Low Price Negative Hundred Thousand Pair at all: every byte one the checker chooses */
static void any_low_price_negative_hundred_thousand_pair(LowPriceNegativeHundredThousandPair *record) {
  for (size_t i = 0; i < 7; i++) { record->raw_low_price[i] = arbitrary(); }
  record->low_price_fraction_indicator = arbitrary();
}

/* Low Price Negative Hundred Thousand Pair to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_low_price_negative_hundred_thousand_pair(const LowPriceNegativeHundredThousandPair *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->raw_low_price[i]; }
  wire[at++] = record->low_price_fraction_indicator;

  return at;
}

/* Low Price Negative Hundred Thousand Pair off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_low_price_negative_hundred_thousand_pair(LowPriceNegativeHundredThousandPair *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { record->raw_low_price[i] = wire[at++]; }
  record->low_price_fraction_indicator = wire[at++];

  return at;
}

/* what was read of Low Price Negative Hundred Thousand Pair is what was written, byte for byte */
static void equal_low_price_negative_hundred_thousand_pair(const LowPriceNegativeHundredThousandPair *read, const LowPriceNegativeHundredThousandPair *written) {
  for (size_t i = 0; i < 7; i++) { assert(read->raw_low_price[i] == written->raw_low_price[i]); }
  assert(read->low_price_fraction_indicator == written->low_price_fraction_indicator);
}

/* Low Price Negative Hundred Thousand Pair: written and read back, then read and written back */
static void check_low_price_negative_hundred_thousand_pair(void) {
  LowPriceNegativeHundredThousandPair sent;
  LowPriceNegativeHundredThousandPair got;
  uint8_t wire[8];
  uint8_t again[8];

  any_low_price_negative_hundred_thousand_pair(&sent);
  assert(encode_low_price_negative_hundred_thousand_pair(&sent, wire, 0) == 8);
  assert(decode_low_price_negative_hundred_thousand_pair(&got, wire, 0) == 8);
  equal_low_price_negative_hundred_thousand_pair(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_low_price_negative_hundred_thousand_pair(&got, wire, 0) == 8);
  assert(encode_low_price_negative_hundred_thousand_pair(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Low Price Negative Million Pair: 8 bytes -------------------------------- */

typedef struct {
  uint8_t raw_low_price[7];              /* bytes 0 to 6 */
  uint8_t low_price_fraction_indicator;  /* byte 7 */
} LowPriceNegativeMillionPair;

/* any Low Price Negative Million Pair at all: every byte one the checker chooses */
static void any_low_price_negative_million_pair(LowPriceNegativeMillionPair *record) {
  for (size_t i = 0; i < 7; i++) { record->raw_low_price[i] = arbitrary(); }
  record->low_price_fraction_indicator = arbitrary();
}

/* Low Price Negative Million Pair to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_low_price_negative_million_pair(const LowPriceNegativeMillionPair *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->raw_low_price[i]; }
  wire[at++] = record->low_price_fraction_indicator;

  return at;
}

/* Low Price Negative Million Pair off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_low_price_negative_million_pair(LowPriceNegativeMillionPair *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { record->raw_low_price[i] = wire[at++]; }
  record->low_price_fraction_indicator = wire[at++];

  return at;
}

/* what was read of Low Price Negative Million Pair is what was written, byte for byte */
static void equal_low_price_negative_million_pair(const LowPriceNegativeMillionPair *read, const LowPriceNegativeMillionPair *written) {
  for (size_t i = 0; i < 7; i++) { assert(read->raw_low_price[i] == written->raw_low_price[i]); }
  assert(read->low_price_fraction_indicator == written->low_price_fraction_indicator);
}

/* Low Price Negative Million Pair: written and read back, then read and written back */
static void check_low_price_negative_million_pair(void) {
  LowPriceNegativeMillionPair sent;
  LowPriceNegativeMillionPair got;
  uint8_t wire[8];
  uint8_t again[8];

  any_low_price_negative_million_pair(&sent);
  assert(encode_low_price_negative_million_pair(&sent, wire, 0) == 8);
  assert(decode_low_price_negative_million_pair(&got, wire, 0) == 8);
  equal_low_price_negative_million_pair(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_low_price_negative_million_pair(&got, wire, 0) == 8);
  assert(encode_low_price_negative_million_pair(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Low Price Numeric Pair: 8 bytes ----------------------------------------- */

typedef struct {
  uint8_t low_price[7];                  /* bytes 0 to 6 */
  uint8_t low_price_fraction_indicator;  /* byte 7 */
} LowPriceNumericPair;

/* any Low Price Numeric Pair at all: every byte one the checker chooses */
static void any_low_price_numeric_pair(LowPriceNumericPair *record) {
  for (size_t i = 0; i < 7; i++) { record->low_price[i] = arbitrary(); }
  record->low_price_fraction_indicator = arbitrary();
}

/* Low Price Numeric Pair to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_low_price_numeric_pair(const LowPriceNumericPair *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->low_price[i]; }
  wire[at++] = record->low_price_fraction_indicator;

  return at;
}

/* Low Price Numeric Pair off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_low_price_numeric_pair(LowPriceNumericPair *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { record->low_price[i] = wire[at++]; }
  record->low_price_fraction_indicator = wire[at++];

  return at;
}

/* what was read of Low Price Numeric Pair is what was written, byte for byte */
static void equal_low_price_numeric_pair(const LowPriceNumericPair *read, const LowPriceNumericPair *written) {
  for (size_t i = 0; i < 7; i++) { assert(read->low_price[i] == written->low_price[i]); }
  assert(read->low_price_fraction_indicator == written->low_price_fraction_indicator);
}

/* Low Price Numeric Pair: written and read back, then read and written back */
static void check_low_price_numeric_pair(void) {
  LowPriceNumericPair sent;
  LowPriceNumericPair got;
  uint8_t wire[8];
  uint8_t again[8];

  any_low_price_numeric_pair(&sent);
  assert(encode_low_price_numeric_pair(&sent, wire, 0) == 8);
  assert(decode_low_price_numeric_pair(&got, wire, 0) == 8);
  equal_low_price_numeric_pair(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_low_price_numeric_pair(&got, wire, 0) == 8);
  assert(encode_low_price_numeric_pair(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Settlement Price Negative Whole Pair: 8 bytes --------------------------- */

typedef struct {
  uint8_t raw_settlement_price[7];              /* bytes 0 to 6 */
  uint8_t settlement_price_fraction_indicator;  /* byte 7 */
} SettlementPriceNegativeWholePair;

/* any Settlement Price Negative Whole Pair at all: every byte one the checker chooses */
static void any_settlement_price_negative_whole_pair(SettlementPriceNegativeWholePair *record) {
  for (size_t i = 0; i < 7; i++) { record->raw_settlement_price[i] = arbitrary(); }
  record->settlement_price_fraction_indicator = arbitrary();
}

/* Settlement Price Negative Whole Pair to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_settlement_price_negative_whole_pair(const SettlementPriceNegativeWholePair *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->raw_settlement_price[i]; }
  wire[at++] = record->settlement_price_fraction_indicator;

  return at;
}

/* Settlement Price Negative Whole Pair off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_settlement_price_negative_whole_pair(SettlementPriceNegativeWholePair *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { record->raw_settlement_price[i] = wire[at++]; }
  record->settlement_price_fraction_indicator = wire[at++];

  return at;
}

/* what was read of Settlement Price Negative Whole Pair is what was written, byte for byte */
static void equal_settlement_price_negative_whole_pair(const SettlementPriceNegativeWholePair *read, const SettlementPriceNegativeWholePair *written) {
  for (size_t i = 0; i < 7; i++) { assert(read->raw_settlement_price[i] == written->raw_settlement_price[i]); }
  assert(read->settlement_price_fraction_indicator == written->settlement_price_fraction_indicator);
}

/* Settlement Price Negative Whole Pair: written and read back, then read and written back */
static void check_settlement_price_negative_whole_pair(void) {
  SettlementPriceNegativeWholePair sent;
  SettlementPriceNegativeWholePair got;
  uint8_t wire[8];
  uint8_t again[8];

  any_settlement_price_negative_whole_pair(&sent);
  assert(encode_settlement_price_negative_whole_pair(&sent, wire, 0) == 8);
  assert(decode_settlement_price_negative_whole_pair(&got, wire, 0) == 8);
  equal_settlement_price_negative_whole_pair(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_settlement_price_negative_whole_pair(&got, wire, 0) == 8);
  assert(encode_settlement_price_negative_whole_pair(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Settlement Price Negative Ten Pair: 8 bytes ----------------------------- */

typedef struct {
  uint8_t raw_settlement_price[7];              /* bytes 0 to 6 */
  uint8_t settlement_price_fraction_indicator;  /* byte 7 */
} SettlementPriceNegativeTenPair;

/* any Settlement Price Negative Ten Pair at all: every byte one the checker chooses */
static void any_settlement_price_negative_ten_pair(SettlementPriceNegativeTenPair *record) {
  for (size_t i = 0; i < 7; i++) { record->raw_settlement_price[i] = arbitrary(); }
  record->settlement_price_fraction_indicator = arbitrary();
}

/* Settlement Price Negative Ten Pair to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_settlement_price_negative_ten_pair(const SettlementPriceNegativeTenPair *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->raw_settlement_price[i]; }
  wire[at++] = record->settlement_price_fraction_indicator;

  return at;
}

/* Settlement Price Negative Ten Pair off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_settlement_price_negative_ten_pair(SettlementPriceNegativeTenPair *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { record->raw_settlement_price[i] = wire[at++]; }
  record->settlement_price_fraction_indicator = wire[at++];

  return at;
}

/* what was read of Settlement Price Negative Ten Pair is what was written, byte for byte */
static void equal_settlement_price_negative_ten_pair(const SettlementPriceNegativeTenPair *read, const SettlementPriceNegativeTenPair *written) {
  for (size_t i = 0; i < 7; i++) { assert(read->raw_settlement_price[i] == written->raw_settlement_price[i]); }
  assert(read->settlement_price_fraction_indicator == written->settlement_price_fraction_indicator);
}

/* Settlement Price Negative Ten Pair: written and read back, then read and written back */
static void check_settlement_price_negative_ten_pair(void) {
  SettlementPriceNegativeTenPair sent;
  SettlementPriceNegativeTenPair got;
  uint8_t wire[8];
  uint8_t again[8];

  any_settlement_price_negative_ten_pair(&sent);
  assert(encode_settlement_price_negative_ten_pair(&sent, wire, 0) == 8);
  assert(decode_settlement_price_negative_ten_pair(&got, wire, 0) == 8);
  equal_settlement_price_negative_ten_pair(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_settlement_price_negative_ten_pair(&got, wire, 0) == 8);
  assert(encode_settlement_price_negative_ten_pair(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Settlement Price Negative Hundred Pair: 8 bytes ------------------------- */

typedef struct {
  uint8_t raw_settlement_price[7];              /* bytes 0 to 6 */
  uint8_t settlement_price_fraction_indicator;  /* byte 7 */
} SettlementPriceNegativeHundredPair;

/* any Settlement Price Negative Hundred Pair at all: every byte one the checker chooses */
static void any_settlement_price_negative_hundred_pair(SettlementPriceNegativeHundredPair *record) {
  for (size_t i = 0; i < 7; i++) { record->raw_settlement_price[i] = arbitrary(); }
  record->settlement_price_fraction_indicator = arbitrary();
}

/* Settlement Price Negative Hundred Pair to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_settlement_price_negative_hundred_pair(const SettlementPriceNegativeHundredPair *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->raw_settlement_price[i]; }
  wire[at++] = record->settlement_price_fraction_indicator;

  return at;
}

/* Settlement Price Negative Hundred Pair off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_settlement_price_negative_hundred_pair(SettlementPriceNegativeHundredPair *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { record->raw_settlement_price[i] = wire[at++]; }
  record->settlement_price_fraction_indicator = wire[at++];

  return at;
}

/* what was read of Settlement Price Negative Hundred Pair is what was written, byte for byte */
static void equal_settlement_price_negative_hundred_pair(const SettlementPriceNegativeHundredPair *read, const SettlementPriceNegativeHundredPair *written) {
  for (size_t i = 0; i < 7; i++) { assert(read->raw_settlement_price[i] == written->raw_settlement_price[i]); }
  assert(read->settlement_price_fraction_indicator == written->settlement_price_fraction_indicator);
}

/* Settlement Price Negative Hundred Pair: written and read back, then read and written back */
static void check_settlement_price_negative_hundred_pair(void) {
  SettlementPriceNegativeHundredPair sent;
  SettlementPriceNegativeHundredPair got;
  uint8_t wire[8];
  uint8_t again[8];

  any_settlement_price_negative_hundred_pair(&sent);
  assert(encode_settlement_price_negative_hundred_pair(&sent, wire, 0) == 8);
  assert(decode_settlement_price_negative_hundred_pair(&got, wire, 0) == 8);
  equal_settlement_price_negative_hundred_pair(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_settlement_price_negative_hundred_pair(&got, wire, 0) == 8);
  assert(encode_settlement_price_negative_hundred_pair(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Settlement Price Negative Thousand Pair: 8 bytes ------------------------ */

typedef struct {
  uint8_t raw_settlement_price[7];              /* bytes 0 to 6 */
  uint8_t settlement_price_fraction_indicator;  /* byte 7 */
} SettlementPriceNegativeThousandPair;

/* any Settlement Price Negative Thousand Pair at all: every byte one the checker chooses */
static void any_settlement_price_negative_thousand_pair(SettlementPriceNegativeThousandPair *record) {
  for (size_t i = 0; i < 7; i++) { record->raw_settlement_price[i] = arbitrary(); }
  record->settlement_price_fraction_indicator = arbitrary();
}

/* Settlement Price Negative Thousand Pair to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_settlement_price_negative_thousand_pair(const SettlementPriceNegativeThousandPair *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->raw_settlement_price[i]; }
  wire[at++] = record->settlement_price_fraction_indicator;

  return at;
}

/* Settlement Price Negative Thousand Pair off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_settlement_price_negative_thousand_pair(SettlementPriceNegativeThousandPair *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { record->raw_settlement_price[i] = wire[at++]; }
  record->settlement_price_fraction_indicator = wire[at++];

  return at;
}

/* what was read of Settlement Price Negative Thousand Pair is what was written, byte for byte */
static void equal_settlement_price_negative_thousand_pair(const SettlementPriceNegativeThousandPair *read, const SettlementPriceNegativeThousandPair *written) {
  for (size_t i = 0; i < 7; i++) { assert(read->raw_settlement_price[i] == written->raw_settlement_price[i]); }
  assert(read->settlement_price_fraction_indicator == written->settlement_price_fraction_indicator);
}

/* Settlement Price Negative Thousand Pair: written and read back, then read and written back */
static void check_settlement_price_negative_thousand_pair(void) {
  SettlementPriceNegativeThousandPair sent;
  SettlementPriceNegativeThousandPair got;
  uint8_t wire[8];
  uint8_t again[8];

  any_settlement_price_negative_thousand_pair(&sent);
  assert(encode_settlement_price_negative_thousand_pair(&sent, wire, 0) == 8);
  assert(decode_settlement_price_negative_thousand_pair(&got, wire, 0) == 8);
  equal_settlement_price_negative_thousand_pair(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_settlement_price_negative_thousand_pair(&got, wire, 0) == 8);
  assert(encode_settlement_price_negative_thousand_pair(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Settlement Price Negative Ten Thousand Pair: 8 bytes -------------------- */

typedef struct {
  uint8_t raw_settlement_price[7];              /* bytes 0 to 6 */
  uint8_t settlement_price_fraction_indicator;  /* byte 7 */
} SettlementPriceNegativeTenThousandPair;

/* any Settlement Price Negative Ten Thousand Pair at all: every byte one the checker chooses */
static void any_settlement_price_negative_ten_thousand_pair(SettlementPriceNegativeTenThousandPair *record) {
  for (size_t i = 0; i < 7; i++) { record->raw_settlement_price[i] = arbitrary(); }
  record->settlement_price_fraction_indicator = arbitrary();
}

/* Settlement Price Negative Ten Thousand Pair to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_settlement_price_negative_ten_thousand_pair(const SettlementPriceNegativeTenThousandPair *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->raw_settlement_price[i]; }
  wire[at++] = record->settlement_price_fraction_indicator;

  return at;
}

/* Settlement Price Negative Ten Thousand Pair off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_settlement_price_negative_ten_thousand_pair(SettlementPriceNegativeTenThousandPair *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { record->raw_settlement_price[i] = wire[at++]; }
  record->settlement_price_fraction_indicator = wire[at++];

  return at;
}

/* what was read of Settlement Price Negative Ten Thousand Pair is what was written, byte for byte */
static void equal_settlement_price_negative_ten_thousand_pair(const SettlementPriceNegativeTenThousandPair *read, const SettlementPriceNegativeTenThousandPair *written) {
  for (size_t i = 0; i < 7; i++) { assert(read->raw_settlement_price[i] == written->raw_settlement_price[i]); }
  assert(read->settlement_price_fraction_indicator == written->settlement_price_fraction_indicator);
}

/* Settlement Price Negative Ten Thousand Pair: written and read back, then read and written back */
static void check_settlement_price_negative_ten_thousand_pair(void) {
  SettlementPriceNegativeTenThousandPair sent;
  SettlementPriceNegativeTenThousandPair got;
  uint8_t wire[8];
  uint8_t again[8];

  any_settlement_price_negative_ten_thousand_pair(&sent);
  assert(encode_settlement_price_negative_ten_thousand_pair(&sent, wire, 0) == 8);
  assert(decode_settlement_price_negative_ten_thousand_pair(&got, wire, 0) == 8);
  equal_settlement_price_negative_ten_thousand_pair(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_settlement_price_negative_ten_thousand_pair(&got, wire, 0) == 8);
  assert(encode_settlement_price_negative_ten_thousand_pair(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Settlement Price Negative Hundred Thousand Pair: 8 bytes ---------------- */

typedef struct {
  uint8_t raw_settlement_price[7];              /* bytes 0 to 6 */
  uint8_t settlement_price_fraction_indicator;  /* byte 7 */
} SettlementPriceNegativeHundredThousandPair;

/* any Settlement Price Negative Hundred Thousand Pair at all: every byte one the checker chooses */
static void any_settlement_price_negative_hundred_thousand_pair(SettlementPriceNegativeHundredThousandPair *record) {
  for (size_t i = 0; i < 7; i++) { record->raw_settlement_price[i] = arbitrary(); }
  record->settlement_price_fraction_indicator = arbitrary();
}

/* Settlement Price Negative Hundred Thousand Pair to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_settlement_price_negative_hundred_thousand_pair(const SettlementPriceNegativeHundredThousandPair *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->raw_settlement_price[i]; }
  wire[at++] = record->settlement_price_fraction_indicator;

  return at;
}

/* Settlement Price Negative Hundred Thousand Pair off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_settlement_price_negative_hundred_thousand_pair(SettlementPriceNegativeHundredThousandPair *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { record->raw_settlement_price[i] = wire[at++]; }
  record->settlement_price_fraction_indicator = wire[at++];

  return at;
}

/* what was read of Settlement Price Negative Hundred Thousand Pair is what was written, byte for byte */
static void equal_settlement_price_negative_hundred_thousand_pair(const SettlementPriceNegativeHundredThousandPair *read, const SettlementPriceNegativeHundredThousandPair *written) {
  for (size_t i = 0; i < 7; i++) { assert(read->raw_settlement_price[i] == written->raw_settlement_price[i]); }
  assert(read->settlement_price_fraction_indicator == written->settlement_price_fraction_indicator);
}

/* Settlement Price Negative Hundred Thousand Pair: written and read back, then read and written back */
static void check_settlement_price_negative_hundred_thousand_pair(void) {
  SettlementPriceNegativeHundredThousandPair sent;
  SettlementPriceNegativeHundredThousandPair got;
  uint8_t wire[8];
  uint8_t again[8];

  any_settlement_price_negative_hundred_thousand_pair(&sent);
  assert(encode_settlement_price_negative_hundred_thousand_pair(&sent, wire, 0) == 8);
  assert(decode_settlement_price_negative_hundred_thousand_pair(&got, wire, 0) == 8);
  equal_settlement_price_negative_hundred_thousand_pair(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_settlement_price_negative_hundred_thousand_pair(&got, wire, 0) == 8);
  assert(encode_settlement_price_negative_hundred_thousand_pair(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Settlement Price Negative Million Pair: 8 bytes ------------------------- */

typedef struct {
  uint8_t raw_settlement_price[7];              /* bytes 0 to 6 */
  uint8_t settlement_price_fraction_indicator;  /* byte 7 */
} SettlementPriceNegativeMillionPair;

/* any Settlement Price Negative Million Pair at all: every byte one the checker chooses */
static void any_settlement_price_negative_million_pair(SettlementPriceNegativeMillionPair *record) {
  for (size_t i = 0; i < 7; i++) { record->raw_settlement_price[i] = arbitrary(); }
  record->settlement_price_fraction_indicator = arbitrary();
}

/* Settlement Price Negative Million Pair to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_settlement_price_negative_million_pair(const SettlementPriceNegativeMillionPair *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->raw_settlement_price[i]; }
  wire[at++] = record->settlement_price_fraction_indicator;

  return at;
}

/* Settlement Price Negative Million Pair off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_settlement_price_negative_million_pair(SettlementPriceNegativeMillionPair *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { record->raw_settlement_price[i] = wire[at++]; }
  record->settlement_price_fraction_indicator = wire[at++];

  return at;
}

/* what was read of Settlement Price Negative Million Pair is what was written, byte for byte */
static void equal_settlement_price_negative_million_pair(const SettlementPriceNegativeMillionPair *read, const SettlementPriceNegativeMillionPair *written) {
  for (size_t i = 0; i < 7; i++) { assert(read->raw_settlement_price[i] == written->raw_settlement_price[i]); }
  assert(read->settlement_price_fraction_indicator == written->settlement_price_fraction_indicator);
}

/* Settlement Price Negative Million Pair: written and read back, then read and written back */
static void check_settlement_price_negative_million_pair(void) {
  SettlementPriceNegativeMillionPair sent;
  SettlementPriceNegativeMillionPair got;
  uint8_t wire[8];
  uint8_t again[8];

  any_settlement_price_negative_million_pair(&sent);
  assert(encode_settlement_price_negative_million_pair(&sent, wire, 0) == 8);
  assert(decode_settlement_price_negative_million_pair(&got, wire, 0) == 8);
  equal_settlement_price_negative_million_pair(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_settlement_price_negative_million_pair(&got, wire, 0) == 8);
  assert(encode_settlement_price_negative_million_pair(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Settlement Price Numeric Pair: 8 bytes ---------------------------------- */

typedef struct {
  uint8_t settlement_price[7];                  /* bytes 0 to 6 */
  uint8_t settlement_price_fraction_indicator;  /* byte 7 */
} SettlementPriceNumericPair;

/* any Settlement Price Numeric Pair at all: every byte one the checker chooses */
static void any_settlement_price_numeric_pair(SettlementPriceNumericPair *record) {
  for (size_t i = 0; i < 7; i++) { record->settlement_price[i] = arbitrary(); }
  record->settlement_price_fraction_indicator = arbitrary();
}

/* Settlement Price Numeric Pair to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_settlement_price_numeric_pair(const SettlementPriceNumericPair *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->settlement_price[i]; }
  wire[at++] = record->settlement_price_fraction_indicator;

  return at;
}

/* Settlement Price Numeric Pair off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_settlement_price_numeric_pair(SettlementPriceNumericPair *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { record->settlement_price[i] = wire[at++]; }
  record->settlement_price_fraction_indicator = wire[at++];

  return at;
}

/* what was read of Settlement Price Numeric Pair is what was written, byte for byte */
static void equal_settlement_price_numeric_pair(const SettlementPriceNumericPair *read, const SettlementPriceNumericPair *written) {
  for (size_t i = 0; i < 7; i++) { assert(read->settlement_price[i] == written->settlement_price[i]); }
  assert(read->settlement_price_fraction_indicator == written->settlement_price_fraction_indicator);
}

/* Settlement Price Numeric Pair: written and read back, then read and written back */
static void check_settlement_price_numeric_pair(void) {
  SettlementPriceNumericPair sent;
  SettlementPriceNumericPair got;
  uint8_t wire[8];
  uint8_t again[8];

  any_settlement_price_numeric_pair(&sent);
  assert(encode_settlement_price_numeric_pair(&sent, wire, 0) == 8);
  assert(decode_settlement_price_numeric_pair(&got, wire, 0) == 8);
  equal_settlement_price_numeric_pair(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_settlement_price_numeric_pair(&got, wire, 0) == 8);
  assert(encode_settlement_price_numeric_pair(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Previous Settlement Price Negative Whole Pair: 8 bytes ------------------ */

typedef struct {
  uint8_t raw_previous_settlement_price[7];              /* bytes 0 to 6 */
  uint8_t previous_settlement_price_fraction_indicator;  /* byte 7 */
} PreviousSettlementPriceNegativeWholePair;

/* any Previous Settlement Price Negative Whole Pair at all: every byte one the checker chooses */
static void any_previous_settlement_price_negative_whole_pair(PreviousSettlementPriceNegativeWholePair *record) {
  for (size_t i = 0; i < 7; i++) { record->raw_previous_settlement_price[i] = arbitrary(); }
  record->previous_settlement_price_fraction_indicator = arbitrary();
}

/* Previous Settlement Price Negative Whole Pair to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_previous_settlement_price_negative_whole_pair(const PreviousSettlementPriceNegativeWholePair *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->raw_previous_settlement_price[i]; }
  wire[at++] = record->previous_settlement_price_fraction_indicator;

  return at;
}

/* Previous Settlement Price Negative Whole Pair off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_previous_settlement_price_negative_whole_pair(PreviousSettlementPriceNegativeWholePair *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { record->raw_previous_settlement_price[i] = wire[at++]; }
  record->previous_settlement_price_fraction_indicator = wire[at++];

  return at;
}

/* what was read of Previous Settlement Price Negative Whole Pair is what was written, byte for byte */
static void equal_previous_settlement_price_negative_whole_pair(const PreviousSettlementPriceNegativeWholePair *read, const PreviousSettlementPriceNegativeWholePair *written) {
  for (size_t i = 0; i < 7; i++) { assert(read->raw_previous_settlement_price[i] == written->raw_previous_settlement_price[i]); }
  assert(read->previous_settlement_price_fraction_indicator == written->previous_settlement_price_fraction_indicator);
}

/* Previous Settlement Price Negative Whole Pair: written and read back, then read and written back */
static void check_previous_settlement_price_negative_whole_pair(void) {
  PreviousSettlementPriceNegativeWholePair sent;
  PreviousSettlementPriceNegativeWholePair got;
  uint8_t wire[8];
  uint8_t again[8];

  any_previous_settlement_price_negative_whole_pair(&sent);
  assert(encode_previous_settlement_price_negative_whole_pair(&sent, wire, 0) == 8);
  assert(decode_previous_settlement_price_negative_whole_pair(&got, wire, 0) == 8);
  equal_previous_settlement_price_negative_whole_pair(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_previous_settlement_price_negative_whole_pair(&got, wire, 0) == 8);
  assert(encode_previous_settlement_price_negative_whole_pair(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Previous Settlement Price Negative Ten Pair: 8 bytes -------------------- */

typedef struct {
  uint8_t raw_previous_settlement_price[7];              /* bytes 0 to 6 */
  uint8_t previous_settlement_price_fraction_indicator;  /* byte 7 */
} PreviousSettlementPriceNegativeTenPair;

/* any Previous Settlement Price Negative Ten Pair at all: every byte one the checker chooses */
static void any_previous_settlement_price_negative_ten_pair(PreviousSettlementPriceNegativeTenPair *record) {
  for (size_t i = 0; i < 7; i++) { record->raw_previous_settlement_price[i] = arbitrary(); }
  record->previous_settlement_price_fraction_indicator = arbitrary();
}

/* Previous Settlement Price Negative Ten Pair to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_previous_settlement_price_negative_ten_pair(const PreviousSettlementPriceNegativeTenPair *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->raw_previous_settlement_price[i]; }
  wire[at++] = record->previous_settlement_price_fraction_indicator;

  return at;
}

/* Previous Settlement Price Negative Ten Pair off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_previous_settlement_price_negative_ten_pair(PreviousSettlementPriceNegativeTenPair *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { record->raw_previous_settlement_price[i] = wire[at++]; }
  record->previous_settlement_price_fraction_indicator = wire[at++];

  return at;
}

/* what was read of Previous Settlement Price Negative Ten Pair is what was written, byte for byte */
static void equal_previous_settlement_price_negative_ten_pair(const PreviousSettlementPriceNegativeTenPair *read, const PreviousSettlementPriceNegativeTenPair *written) {
  for (size_t i = 0; i < 7; i++) { assert(read->raw_previous_settlement_price[i] == written->raw_previous_settlement_price[i]); }
  assert(read->previous_settlement_price_fraction_indicator == written->previous_settlement_price_fraction_indicator);
}

/* Previous Settlement Price Negative Ten Pair: written and read back, then read and written back */
static void check_previous_settlement_price_negative_ten_pair(void) {
  PreviousSettlementPriceNegativeTenPair sent;
  PreviousSettlementPriceNegativeTenPair got;
  uint8_t wire[8];
  uint8_t again[8];

  any_previous_settlement_price_negative_ten_pair(&sent);
  assert(encode_previous_settlement_price_negative_ten_pair(&sent, wire, 0) == 8);
  assert(decode_previous_settlement_price_negative_ten_pair(&got, wire, 0) == 8);
  equal_previous_settlement_price_negative_ten_pair(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_previous_settlement_price_negative_ten_pair(&got, wire, 0) == 8);
  assert(encode_previous_settlement_price_negative_ten_pair(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Previous Settlement Price Negative Hundred Pair: 8 bytes ---------------- */

typedef struct {
  uint8_t raw_previous_settlement_price[7];              /* bytes 0 to 6 */
  uint8_t previous_settlement_price_fraction_indicator;  /* byte 7 */
} PreviousSettlementPriceNegativeHundredPair;

/* any Previous Settlement Price Negative Hundred Pair at all: every byte one the checker chooses */
static void any_previous_settlement_price_negative_hundred_pair(PreviousSettlementPriceNegativeHundredPair *record) {
  for (size_t i = 0; i < 7; i++) { record->raw_previous_settlement_price[i] = arbitrary(); }
  record->previous_settlement_price_fraction_indicator = arbitrary();
}

/* Previous Settlement Price Negative Hundred Pair to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_previous_settlement_price_negative_hundred_pair(const PreviousSettlementPriceNegativeHundredPair *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->raw_previous_settlement_price[i]; }
  wire[at++] = record->previous_settlement_price_fraction_indicator;

  return at;
}

/* Previous Settlement Price Negative Hundred Pair off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_previous_settlement_price_negative_hundred_pair(PreviousSettlementPriceNegativeHundredPair *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { record->raw_previous_settlement_price[i] = wire[at++]; }
  record->previous_settlement_price_fraction_indicator = wire[at++];

  return at;
}

/* what was read of Previous Settlement Price Negative Hundred Pair is what was written, byte for byte */
static void equal_previous_settlement_price_negative_hundred_pair(const PreviousSettlementPriceNegativeHundredPair *read, const PreviousSettlementPriceNegativeHundredPair *written) {
  for (size_t i = 0; i < 7; i++) { assert(read->raw_previous_settlement_price[i] == written->raw_previous_settlement_price[i]); }
  assert(read->previous_settlement_price_fraction_indicator == written->previous_settlement_price_fraction_indicator);
}

/* Previous Settlement Price Negative Hundred Pair: written and read back, then read and written back */
static void check_previous_settlement_price_negative_hundred_pair(void) {
  PreviousSettlementPriceNegativeHundredPair sent;
  PreviousSettlementPriceNegativeHundredPair got;
  uint8_t wire[8];
  uint8_t again[8];

  any_previous_settlement_price_negative_hundred_pair(&sent);
  assert(encode_previous_settlement_price_negative_hundred_pair(&sent, wire, 0) == 8);
  assert(decode_previous_settlement_price_negative_hundred_pair(&got, wire, 0) == 8);
  equal_previous_settlement_price_negative_hundred_pair(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_previous_settlement_price_negative_hundred_pair(&got, wire, 0) == 8);
  assert(encode_previous_settlement_price_negative_hundred_pair(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Previous Settlement Price Negative Thousand Pair: 8 bytes --------------- */

typedef struct {
  uint8_t raw_previous_settlement_price[7];              /* bytes 0 to 6 */
  uint8_t previous_settlement_price_fraction_indicator;  /* byte 7 */
} PreviousSettlementPriceNegativeThousandPair;

/* any Previous Settlement Price Negative Thousand Pair at all: every byte one the checker chooses */
static void any_previous_settlement_price_negative_thousand_pair(PreviousSettlementPriceNegativeThousandPair *record) {
  for (size_t i = 0; i < 7; i++) { record->raw_previous_settlement_price[i] = arbitrary(); }
  record->previous_settlement_price_fraction_indicator = arbitrary();
}

/* Previous Settlement Price Negative Thousand Pair to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_previous_settlement_price_negative_thousand_pair(const PreviousSettlementPriceNegativeThousandPair *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->raw_previous_settlement_price[i]; }
  wire[at++] = record->previous_settlement_price_fraction_indicator;

  return at;
}

/* Previous Settlement Price Negative Thousand Pair off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_previous_settlement_price_negative_thousand_pair(PreviousSettlementPriceNegativeThousandPair *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { record->raw_previous_settlement_price[i] = wire[at++]; }
  record->previous_settlement_price_fraction_indicator = wire[at++];

  return at;
}

/* what was read of Previous Settlement Price Negative Thousand Pair is what was written, byte for byte */
static void equal_previous_settlement_price_negative_thousand_pair(const PreviousSettlementPriceNegativeThousandPair *read, const PreviousSettlementPriceNegativeThousandPair *written) {
  for (size_t i = 0; i < 7; i++) { assert(read->raw_previous_settlement_price[i] == written->raw_previous_settlement_price[i]); }
  assert(read->previous_settlement_price_fraction_indicator == written->previous_settlement_price_fraction_indicator);
}

/* Previous Settlement Price Negative Thousand Pair: written and read back, then read and written back */
static void check_previous_settlement_price_negative_thousand_pair(void) {
  PreviousSettlementPriceNegativeThousandPair sent;
  PreviousSettlementPriceNegativeThousandPair got;
  uint8_t wire[8];
  uint8_t again[8];

  any_previous_settlement_price_negative_thousand_pair(&sent);
  assert(encode_previous_settlement_price_negative_thousand_pair(&sent, wire, 0) == 8);
  assert(decode_previous_settlement_price_negative_thousand_pair(&got, wire, 0) == 8);
  equal_previous_settlement_price_negative_thousand_pair(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_previous_settlement_price_negative_thousand_pair(&got, wire, 0) == 8);
  assert(encode_previous_settlement_price_negative_thousand_pair(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Previous Settlement Price Negative Ten Thousand Pair: 8 bytes ----------- */

typedef struct {
  uint8_t raw_previous_settlement_price[7];              /* bytes 0 to 6 */
  uint8_t previous_settlement_price_fraction_indicator;  /* byte 7 */
} PreviousSettlementPriceNegativeTenThousandPair;

/* any Previous Settlement Price Negative Ten Thousand Pair at all: every byte one the checker chooses */
static void any_previous_settlement_price_negative_ten_thousand_pair(PreviousSettlementPriceNegativeTenThousandPair *record) {
  for (size_t i = 0; i < 7; i++) { record->raw_previous_settlement_price[i] = arbitrary(); }
  record->previous_settlement_price_fraction_indicator = arbitrary();
}

/* Previous Settlement Price Negative Ten Thousand Pair to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_previous_settlement_price_negative_ten_thousand_pair(const PreviousSettlementPriceNegativeTenThousandPair *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->raw_previous_settlement_price[i]; }
  wire[at++] = record->previous_settlement_price_fraction_indicator;

  return at;
}

/* Previous Settlement Price Negative Ten Thousand Pair off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_previous_settlement_price_negative_ten_thousand_pair(PreviousSettlementPriceNegativeTenThousandPair *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { record->raw_previous_settlement_price[i] = wire[at++]; }
  record->previous_settlement_price_fraction_indicator = wire[at++];

  return at;
}

/* what was read of Previous Settlement Price Negative Ten Thousand Pair is what was written, byte for byte */
static void equal_previous_settlement_price_negative_ten_thousand_pair(const PreviousSettlementPriceNegativeTenThousandPair *read, const PreviousSettlementPriceNegativeTenThousandPair *written) {
  for (size_t i = 0; i < 7; i++) { assert(read->raw_previous_settlement_price[i] == written->raw_previous_settlement_price[i]); }
  assert(read->previous_settlement_price_fraction_indicator == written->previous_settlement_price_fraction_indicator);
}

/* Previous Settlement Price Negative Ten Thousand Pair: written and read back, then read and written back */
static void check_previous_settlement_price_negative_ten_thousand_pair(void) {
  PreviousSettlementPriceNegativeTenThousandPair sent;
  PreviousSettlementPriceNegativeTenThousandPair got;
  uint8_t wire[8];
  uint8_t again[8];

  any_previous_settlement_price_negative_ten_thousand_pair(&sent);
  assert(encode_previous_settlement_price_negative_ten_thousand_pair(&sent, wire, 0) == 8);
  assert(decode_previous_settlement_price_negative_ten_thousand_pair(&got, wire, 0) == 8);
  equal_previous_settlement_price_negative_ten_thousand_pair(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_previous_settlement_price_negative_ten_thousand_pair(&got, wire, 0) == 8);
  assert(encode_previous_settlement_price_negative_ten_thousand_pair(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Previous Settlement Price Negative Hundred Thousand Pair: 8 bytes ------- */

typedef struct {
  uint8_t raw_previous_settlement_price[7];              /* bytes 0 to 6 */
  uint8_t previous_settlement_price_fraction_indicator;  /* byte 7 */
} PreviousSettlementPriceNegativeHundredThousandPair;

/* any Previous Settlement Price Negative Hundred Thousand Pair at all: every byte one the checker chooses */
static void any_previous_settlement_price_negative_hundred_thousand_pair(PreviousSettlementPriceNegativeHundredThousandPair *record) {
  for (size_t i = 0; i < 7; i++) { record->raw_previous_settlement_price[i] = arbitrary(); }
  record->previous_settlement_price_fraction_indicator = arbitrary();
}

/* Previous Settlement Price Negative Hundred Thousand Pair to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_previous_settlement_price_negative_hundred_thousand_pair(const PreviousSettlementPriceNegativeHundredThousandPair *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->raw_previous_settlement_price[i]; }
  wire[at++] = record->previous_settlement_price_fraction_indicator;

  return at;
}

/* Previous Settlement Price Negative Hundred Thousand Pair off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_previous_settlement_price_negative_hundred_thousand_pair(PreviousSettlementPriceNegativeHundredThousandPair *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { record->raw_previous_settlement_price[i] = wire[at++]; }
  record->previous_settlement_price_fraction_indicator = wire[at++];

  return at;
}

/* what was read of Previous Settlement Price Negative Hundred Thousand Pair is what was written, byte for byte */
static void equal_previous_settlement_price_negative_hundred_thousand_pair(const PreviousSettlementPriceNegativeHundredThousandPair *read, const PreviousSettlementPriceNegativeHundredThousandPair *written) {
  for (size_t i = 0; i < 7; i++) { assert(read->raw_previous_settlement_price[i] == written->raw_previous_settlement_price[i]); }
  assert(read->previous_settlement_price_fraction_indicator == written->previous_settlement_price_fraction_indicator);
}

/* Previous Settlement Price Negative Hundred Thousand Pair: written and read back, then read and written back */
static void check_previous_settlement_price_negative_hundred_thousand_pair(void) {
  PreviousSettlementPriceNegativeHundredThousandPair sent;
  PreviousSettlementPriceNegativeHundredThousandPair got;
  uint8_t wire[8];
  uint8_t again[8];

  any_previous_settlement_price_negative_hundred_thousand_pair(&sent);
  assert(encode_previous_settlement_price_negative_hundred_thousand_pair(&sent, wire, 0) == 8);
  assert(decode_previous_settlement_price_negative_hundred_thousand_pair(&got, wire, 0) == 8);
  equal_previous_settlement_price_negative_hundred_thousand_pair(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_previous_settlement_price_negative_hundred_thousand_pair(&got, wire, 0) == 8);
  assert(encode_previous_settlement_price_negative_hundred_thousand_pair(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Previous Settlement Price Negative Million Pair: 8 bytes ---------------- */

typedef struct {
  uint8_t raw_previous_settlement_price[7];              /* bytes 0 to 6 */
  uint8_t previous_settlement_price_fraction_indicator;  /* byte 7 */
} PreviousSettlementPriceNegativeMillionPair;

/* any Previous Settlement Price Negative Million Pair at all: every byte one the checker chooses */
static void any_previous_settlement_price_negative_million_pair(PreviousSettlementPriceNegativeMillionPair *record) {
  for (size_t i = 0; i < 7; i++) { record->raw_previous_settlement_price[i] = arbitrary(); }
  record->previous_settlement_price_fraction_indicator = arbitrary();
}

/* Previous Settlement Price Negative Million Pair to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_previous_settlement_price_negative_million_pair(const PreviousSettlementPriceNegativeMillionPair *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->raw_previous_settlement_price[i]; }
  wire[at++] = record->previous_settlement_price_fraction_indicator;

  return at;
}

/* Previous Settlement Price Negative Million Pair off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_previous_settlement_price_negative_million_pair(PreviousSettlementPriceNegativeMillionPair *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { record->raw_previous_settlement_price[i] = wire[at++]; }
  record->previous_settlement_price_fraction_indicator = wire[at++];

  return at;
}

/* what was read of Previous Settlement Price Negative Million Pair is what was written, byte for byte */
static void equal_previous_settlement_price_negative_million_pair(const PreviousSettlementPriceNegativeMillionPair *read, const PreviousSettlementPriceNegativeMillionPair *written) {
  for (size_t i = 0; i < 7; i++) { assert(read->raw_previous_settlement_price[i] == written->raw_previous_settlement_price[i]); }
  assert(read->previous_settlement_price_fraction_indicator == written->previous_settlement_price_fraction_indicator);
}

/* Previous Settlement Price Negative Million Pair: written and read back, then read and written back */
static void check_previous_settlement_price_negative_million_pair(void) {
  PreviousSettlementPriceNegativeMillionPair sent;
  PreviousSettlementPriceNegativeMillionPair got;
  uint8_t wire[8];
  uint8_t again[8];

  any_previous_settlement_price_negative_million_pair(&sent);
  assert(encode_previous_settlement_price_negative_million_pair(&sent, wire, 0) == 8);
  assert(decode_previous_settlement_price_negative_million_pair(&got, wire, 0) == 8);
  equal_previous_settlement_price_negative_million_pair(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_previous_settlement_price_negative_million_pair(&got, wire, 0) == 8);
  assert(encode_previous_settlement_price_negative_million_pair(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Previous Settlement Price Numeric Pair: 8 bytes ------------------------- */

typedef struct {
  uint8_t previous_settlement_price[7];                  /* bytes 0 to 6 */
  uint8_t previous_settlement_price_fraction_indicator;  /* byte 7 */
} PreviousSettlementPriceNumericPair;

/* any Previous Settlement Price Numeric Pair at all: every byte one the checker chooses */
static void any_previous_settlement_price_numeric_pair(PreviousSettlementPriceNumericPair *record) {
  for (size_t i = 0; i < 7; i++) { record->previous_settlement_price[i] = arbitrary(); }
  record->previous_settlement_price_fraction_indicator = arbitrary();
}

/* Previous Settlement Price Numeric Pair to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_previous_settlement_price_numeric_pair(const PreviousSettlementPriceNumericPair *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->previous_settlement_price[i]; }
  wire[at++] = record->previous_settlement_price_fraction_indicator;

  return at;
}

/* Previous Settlement Price Numeric Pair off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_previous_settlement_price_numeric_pair(PreviousSettlementPriceNumericPair *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { record->previous_settlement_price[i] = wire[at++]; }
  record->previous_settlement_price_fraction_indicator = wire[at++];

  return at;
}

/* what was read of Previous Settlement Price Numeric Pair is what was written, byte for byte */
static void equal_previous_settlement_price_numeric_pair(const PreviousSettlementPriceNumericPair *read, const PreviousSettlementPriceNumericPair *written) {
  for (size_t i = 0; i < 7; i++) { assert(read->previous_settlement_price[i] == written->previous_settlement_price[i]); }
  assert(read->previous_settlement_price_fraction_indicator == written->previous_settlement_price_fraction_indicator);
}

/* Previous Settlement Price Numeric Pair: written and read back, then read and written back */
static void check_previous_settlement_price_numeric_pair(void) {
  PreviousSettlementPriceNumericPair sent;
  PreviousSettlementPriceNumericPair got;
  uint8_t wire[8];
  uint8_t again[8];

  any_previous_settlement_price_numeric_pair(&sent);
  assert(encode_previous_settlement_price_numeric_pair(&sent, wire, 0) == 8);
  assert(decode_previous_settlement_price_numeric_pair(&got, wire, 0) == 8);
  equal_previous_settlement_price_numeric_pair(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_previous_settlement_price_numeric_pair(&got, wire, 0) == 8);
  assert(encode_previous_settlement_price_numeric_pair(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Opening Price Negative Whole Pair: 8 bytes ------------------------------ */

typedef struct {
  uint8_t raw_opening_price[7];              /* bytes 0 to 6 */
  uint8_t opening_price_fraction_indicator;  /* byte 7 */
} OpeningPriceNegativeWholePair;

/* any Opening Price Negative Whole Pair at all: every byte one the checker chooses */
static void any_opening_price_negative_whole_pair(OpeningPriceNegativeWholePair *record) {
  for (size_t i = 0; i < 7; i++) { record->raw_opening_price[i] = arbitrary(); }
  record->opening_price_fraction_indicator = arbitrary();
}

/* Opening Price Negative Whole Pair to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_opening_price_negative_whole_pair(const OpeningPriceNegativeWholePair *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->raw_opening_price[i]; }
  wire[at++] = record->opening_price_fraction_indicator;

  return at;
}

/* Opening Price Negative Whole Pair off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_opening_price_negative_whole_pair(OpeningPriceNegativeWholePair *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { record->raw_opening_price[i] = wire[at++]; }
  record->opening_price_fraction_indicator = wire[at++];

  return at;
}

/* what was read of Opening Price Negative Whole Pair is what was written, byte for byte */
static void equal_opening_price_negative_whole_pair(const OpeningPriceNegativeWholePair *read, const OpeningPriceNegativeWholePair *written) {
  for (size_t i = 0; i < 7; i++) { assert(read->raw_opening_price[i] == written->raw_opening_price[i]); }
  assert(read->opening_price_fraction_indicator == written->opening_price_fraction_indicator);
}

/* Opening Price Negative Whole Pair: written and read back, then read and written back */
static void check_opening_price_negative_whole_pair(void) {
  OpeningPriceNegativeWholePair sent;
  OpeningPriceNegativeWholePair got;
  uint8_t wire[8];
  uint8_t again[8];

  any_opening_price_negative_whole_pair(&sent);
  assert(encode_opening_price_negative_whole_pair(&sent, wire, 0) == 8);
  assert(decode_opening_price_negative_whole_pair(&got, wire, 0) == 8);
  equal_opening_price_negative_whole_pair(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_opening_price_negative_whole_pair(&got, wire, 0) == 8);
  assert(encode_opening_price_negative_whole_pair(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Opening Price Negative Ten Pair: 8 bytes -------------------------------- */

typedef struct {
  uint8_t raw_opening_price[7];              /* bytes 0 to 6 */
  uint8_t opening_price_fraction_indicator;  /* byte 7 */
} OpeningPriceNegativeTenPair;

/* any Opening Price Negative Ten Pair at all: every byte one the checker chooses */
static void any_opening_price_negative_ten_pair(OpeningPriceNegativeTenPair *record) {
  for (size_t i = 0; i < 7; i++) { record->raw_opening_price[i] = arbitrary(); }
  record->opening_price_fraction_indicator = arbitrary();
}

/* Opening Price Negative Ten Pair to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_opening_price_negative_ten_pair(const OpeningPriceNegativeTenPair *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->raw_opening_price[i]; }
  wire[at++] = record->opening_price_fraction_indicator;

  return at;
}

/* Opening Price Negative Ten Pair off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_opening_price_negative_ten_pair(OpeningPriceNegativeTenPair *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { record->raw_opening_price[i] = wire[at++]; }
  record->opening_price_fraction_indicator = wire[at++];

  return at;
}

/* what was read of Opening Price Negative Ten Pair is what was written, byte for byte */
static void equal_opening_price_negative_ten_pair(const OpeningPriceNegativeTenPair *read, const OpeningPriceNegativeTenPair *written) {
  for (size_t i = 0; i < 7; i++) { assert(read->raw_opening_price[i] == written->raw_opening_price[i]); }
  assert(read->opening_price_fraction_indicator == written->opening_price_fraction_indicator);
}

/* Opening Price Negative Ten Pair: written and read back, then read and written back */
static void check_opening_price_negative_ten_pair(void) {
  OpeningPriceNegativeTenPair sent;
  OpeningPriceNegativeTenPair got;
  uint8_t wire[8];
  uint8_t again[8];

  any_opening_price_negative_ten_pair(&sent);
  assert(encode_opening_price_negative_ten_pair(&sent, wire, 0) == 8);
  assert(decode_opening_price_negative_ten_pair(&got, wire, 0) == 8);
  equal_opening_price_negative_ten_pair(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_opening_price_negative_ten_pair(&got, wire, 0) == 8);
  assert(encode_opening_price_negative_ten_pair(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Opening Price Negative Hundred Pair: 8 bytes ---------------------------- */

typedef struct {
  uint8_t raw_opening_price[7];              /* bytes 0 to 6 */
  uint8_t opening_price_fraction_indicator;  /* byte 7 */
} OpeningPriceNegativeHundredPair;

/* any Opening Price Negative Hundred Pair at all: every byte one the checker chooses */
static void any_opening_price_negative_hundred_pair(OpeningPriceNegativeHundredPair *record) {
  for (size_t i = 0; i < 7; i++) { record->raw_opening_price[i] = arbitrary(); }
  record->opening_price_fraction_indicator = arbitrary();
}

/* Opening Price Negative Hundred Pair to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_opening_price_negative_hundred_pair(const OpeningPriceNegativeHundredPair *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->raw_opening_price[i]; }
  wire[at++] = record->opening_price_fraction_indicator;

  return at;
}

/* Opening Price Negative Hundred Pair off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_opening_price_negative_hundred_pair(OpeningPriceNegativeHundredPair *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { record->raw_opening_price[i] = wire[at++]; }
  record->opening_price_fraction_indicator = wire[at++];

  return at;
}

/* what was read of Opening Price Negative Hundred Pair is what was written, byte for byte */
static void equal_opening_price_negative_hundred_pair(const OpeningPriceNegativeHundredPair *read, const OpeningPriceNegativeHundredPair *written) {
  for (size_t i = 0; i < 7; i++) { assert(read->raw_opening_price[i] == written->raw_opening_price[i]); }
  assert(read->opening_price_fraction_indicator == written->opening_price_fraction_indicator);
}

/* Opening Price Negative Hundred Pair: written and read back, then read and written back */
static void check_opening_price_negative_hundred_pair(void) {
  OpeningPriceNegativeHundredPair sent;
  OpeningPriceNegativeHundredPair got;
  uint8_t wire[8];
  uint8_t again[8];

  any_opening_price_negative_hundred_pair(&sent);
  assert(encode_opening_price_negative_hundred_pair(&sent, wire, 0) == 8);
  assert(decode_opening_price_negative_hundred_pair(&got, wire, 0) == 8);
  equal_opening_price_negative_hundred_pair(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_opening_price_negative_hundred_pair(&got, wire, 0) == 8);
  assert(encode_opening_price_negative_hundred_pair(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Opening Price Negative Thousand Pair: 8 bytes --------------------------- */

typedef struct {
  uint8_t raw_opening_price[7];              /* bytes 0 to 6 */
  uint8_t opening_price_fraction_indicator;  /* byte 7 */
} OpeningPriceNegativeThousandPair;

/* any Opening Price Negative Thousand Pair at all: every byte one the checker chooses */
static void any_opening_price_negative_thousand_pair(OpeningPriceNegativeThousandPair *record) {
  for (size_t i = 0; i < 7; i++) { record->raw_opening_price[i] = arbitrary(); }
  record->opening_price_fraction_indicator = arbitrary();
}

/* Opening Price Negative Thousand Pair to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_opening_price_negative_thousand_pair(const OpeningPriceNegativeThousandPair *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->raw_opening_price[i]; }
  wire[at++] = record->opening_price_fraction_indicator;

  return at;
}

/* Opening Price Negative Thousand Pair off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_opening_price_negative_thousand_pair(OpeningPriceNegativeThousandPair *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { record->raw_opening_price[i] = wire[at++]; }
  record->opening_price_fraction_indicator = wire[at++];

  return at;
}

/* what was read of Opening Price Negative Thousand Pair is what was written, byte for byte */
static void equal_opening_price_negative_thousand_pair(const OpeningPriceNegativeThousandPair *read, const OpeningPriceNegativeThousandPair *written) {
  for (size_t i = 0; i < 7; i++) { assert(read->raw_opening_price[i] == written->raw_opening_price[i]); }
  assert(read->opening_price_fraction_indicator == written->opening_price_fraction_indicator);
}

/* Opening Price Negative Thousand Pair: written and read back, then read and written back */
static void check_opening_price_negative_thousand_pair(void) {
  OpeningPriceNegativeThousandPair sent;
  OpeningPriceNegativeThousandPair got;
  uint8_t wire[8];
  uint8_t again[8];

  any_opening_price_negative_thousand_pair(&sent);
  assert(encode_opening_price_negative_thousand_pair(&sent, wire, 0) == 8);
  assert(decode_opening_price_negative_thousand_pair(&got, wire, 0) == 8);
  equal_opening_price_negative_thousand_pair(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_opening_price_negative_thousand_pair(&got, wire, 0) == 8);
  assert(encode_opening_price_negative_thousand_pair(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Opening Price Negative Ten Thousand Pair: 8 bytes ----------------------- */

typedef struct {
  uint8_t raw_opening_price[7];              /* bytes 0 to 6 */
  uint8_t opening_price_fraction_indicator;  /* byte 7 */
} OpeningPriceNegativeTenThousandPair;

/* any Opening Price Negative Ten Thousand Pair at all: every byte one the checker chooses */
static void any_opening_price_negative_ten_thousand_pair(OpeningPriceNegativeTenThousandPair *record) {
  for (size_t i = 0; i < 7; i++) { record->raw_opening_price[i] = arbitrary(); }
  record->opening_price_fraction_indicator = arbitrary();
}

/* Opening Price Negative Ten Thousand Pair to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_opening_price_negative_ten_thousand_pair(const OpeningPriceNegativeTenThousandPair *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->raw_opening_price[i]; }
  wire[at++] = record->opening_price_fraction_indicator;

  return at;
}

/* Opening Price Negative Ten Thousand Pair off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_opening_price_negative_ten_thousand_pair(OpeningPriceNegativeTenThousandPair *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { record->raw_opening_price[i] = wire[at++]; }
  record->opening_price_fraction_indicator = wire[at++];

  return at;
}

/* what was read of Opening Price Negative Ten Thousand Pair is what was written, byte for byte */
static void equal_opening_price_negative_ten_thousand_pair(const OpeningPriceNegativeTenThousandPair *read, const OpeningPriceNegativeTenThousandPair *written) {
  for (size_t i = 0; i < 7; i++) { assert(read->raw_opening_price[i] == written->raw_opening_price[i]); }
  assert(read->opening_price_fraction_indicator == written->opening_price_fraction_indicator);
}

/* Opening Price Negative Ten Thousand Pair: written and read back, then read and written back */
static void check_opening_price_negative_ten_thousand_pair(void) {
  OpeningPriceNegativeTenThousandPair sent;
  OpeningPriceNegativeTenThousandPair got;
  uint8_t wire[8];
  uint8_t again[8];

  any_opening_price_negative_ten_thousand_pair(&sent);
  assert(encode_opening_price_negative_ten_thousand_pair(&sent, wire, 0) == 8);
  assert(decode_opening_price_negative_ten_thousand_pair(&got, wire, 0) == 8);
  equal_opening_price_negative_ten_thousand_pair(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_opening_price_negative_ten_thousand_pair(&got, wire, 0) == 8);
  assert(encode_opening_price_negative_ten_thousand_pair(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Opening Price Negative Hundred Thousand Pair: 8 bytes ------------------- */

typedef struct {
  uint8_t raw_opening_price[7];              /* bytes 0 to 6 */
  uint8_t opening_price_fraction_indicator;  /* byte 7 */
} OpeningPriceNegativeHundredThousandPair;

/* any Opening Price Negative Hundred Thousand Pair at all: every byte one the checker chooses */
static void any_opening_price_negative_hundred_thousand_pair(OpeningPriceNegativeHundredThousandPair *record) {
  for (size_t i = 0; i < 7; i++) { record->raw_opening_price[i] = arbitrary(); }
  record->opening_price_fraction_indicator = arbitrary();
}

/* Opening Price Negative Hundred Thousand Pair to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_opening_price_negative_hundred_thousand_pair(const OpeningPriceNegativeHundredThousandPair *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->raw_opening_price[i]; }
  wire[at++] = record->opening_price_fraction_indicator;

  return at;
}

/* Opening Price Negative Hundred Thousand Pair off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_opening_price_negative_hundred_thousand_pair(OpeningPriceNegativeHundredThousandPair *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { record->raw_opening_price[i] = wire[at++]; }
  record->opening_price_fraction_indicator = wire[at++];

  return at;
}

/* what was read of Opening Price Negative Hundred Thousand Pair is what was written, byte for byte */
static void equal_opening_price_negative_hundred_thousand_pair(const OpeningPriceNegativeHundredThousandPair *read, const OpeningPriceNegativeHundredThousandPair *written) {
  for (size_t i = 0; i < 7; i++) { assert(read->raw_opening_price[i] == written->raw_opening_price[i]); }
  assert(read->opening_price_fraction_indicator == written->opening_price_fraction_indicator);
}

/* Opening Price Negative Hundred Thousand Pair: written and read back, then read and written back */
static void check_opening_price_negative_hundred_thousand_pair(void) {
  OpeningPriceNegativeHundredThousandPair sent;
  OpeningPriceNegativeHundredThousandPair got;
  uint8_t wire[8];
  uint8_t again[8];

  any_opening_price_negative_hundred_thousand_pair(&sent);
  assert(encode_opening_price_negative_hundred_thousand_pair(&sent, wire, 0) == 8);
  assert(decode_opening_price_negative_hundred_thousand_pair(&got, wire, 0) == 8);
  equal_opening_price_negative_hundred_thousand_pair(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_opening_price_negative_hundred_thousand_pair(&got, wire, 0) == 8);
  assert(encode_opening_price_negative_hundred_thousand_pair(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Opening Price Negative Million Pair: 8 bytes ---------------------------- */

typedef struct {
  uint8_t raw_opening_price[7];              /* bytes 0 to 6 */
  uint8_t opening_price_fraction_indicator;  /* byte 7 */
} OpeningPriceNegativeMillionPair;

/* any Opening Price Negative Million Pair at all: every byte one the checker chooses */
static void any_opening_price_negative_million_pair(OpeningPriceNegativeMillionPair *record) {
  for (size_t i = 0; i < 7; i++) { record->raw_opening_price[i] = arbitrary(); }
  record->opening_price_fraction_indicator = arbitrary();
}

/* Opening Price Negative Million Pair to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_opening_price_negative_million_pair(const OpeningPriceNegativeMillionPair *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->raw_opening_price[i]; }
  wire[at++] = record->opening_price_fraction_indicator;

  return at;
}

/* Opening Price Negative Million Pair off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_opening_price_negative_million_pair(OpeningPriceNegativeMillionPair *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { record->raw_opening_price[i] = wire[at++]; }
  record->opening_price_fraction_indicator = wire[at++];

  return at;
}

/* what was read of Opening Price Negative Million Pair is what was written, byte for byte */
static void equal_opening_price_negative_million_pair(const OpeningPriceNegativeMillionPair *read, const OpeningPriceNegativeMillionPair *written) {
  for (size_t i = 0; i < 7; i++) { assert(read->raw_opening_price[i] == written->raw_opening_price[i]); }
  assert(read->opening_price_fraction_indicator == written->opening_price_fraction_indicator);
}

/* Opening Price Negative Million Pair: written and read back, then read and written back */
static void check_opening_price_negative_million_pair(void) {
  OpeningPriceNegativeMillionPair sent;
  OpeningPriceNegativeMillionPair got;
  uint8_t wire[8];
  uint8_t again[8];

  any_opening_price_negative_million_pair(&sent);
  assert(encode_opening_price_negative_million_pair(&sent, wire, 0) == 8);
  assert(decode_opening_price_negative_million_pair(&got, wire, 0) == 8);
  equal_opening_price_negative_million_pair(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_opening_price_negative_million_pair(&got, wire, 0) == 8);
  assert(encode_opening_price_negative_million_pair(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Opening Price Numeric Pair: 8 bytes ------------------------------------- */

typedef struct {
  uint8_t opening_price[7];                  /* bytes 0 to 6 */
  uint8_t opening_price_fraction_indicator;  /* byte 7 */
} OpeningPriceNumericPair;

/* any Opening Price Numeric Pair at all: every byte one the checker chooses */
static void any_opening_price_numeric_pair(OpeningPriceNumericPair *record) {
  for (size_t i = 0; i < 7; i++) { record->opening_price[i] = arbitrary(); }
  record->opening_price_fraction_indicator = arbitrary();
}

/* Opening Price Numeric Pair to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_opening_price_numeric_pair(const OpeningPriceNumericPair *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->opening_price[i]; }
  wire[at++] = record->opening_price_fraction_indicator;

  return at;
}

/* Opening Price Numeric Pair off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_opening_price_numeric_pair(OpeningPriceNumericPair *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { record->opening_price[i] = wire[at++]; }
  record->opening_price_fraction_indicator = wire[at++];

  return at;
}

/* what was read of Opening Price Numeric Pair is what was written, byte for byte */
static void equal_opening_price_numeric_pair(const OpeningPriceNumericPair *read, const OpeningPriceNumericPair *written) {
  for (size_t i = 0; i < 7; i++) { assert(read->opening_price[i] == written->opening_price[i]); }
  assert(read->opening_price_fraction_indicator == written->opening_price_fraction_indicator);
}

/* Opening Price Numeric Pair: written and read back, then read and written back */
static void check_opening_price_numeric_pair(void) {
  OpeningPriceNumericPair sent;
  OpeningPriceNumericPair got;
  uint8_t wire[8];
  uint8_t again[8];

  any_opening_price_numeric_pair(&sent);
  assert(encode_opening_price_numeric_pair(&sent, wire, 0) == 8);
  assert(decode_opening_price_numeric_pair(&got, wire, 0) == 8);
  equal_opening_price_numeric_pair(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_opening_price_numeric_pair(&got, wire, 0) == 8);
  assert(encode_opening_price_numeric_pair(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Settlement Price Future Options Summary Message Negative Whole Pair: 8 bytes ---- */

typedef struct {
  uint8_t raw_settlement_price_future_options_summary_message[7];  /* bytes 0 to 6 */
  uint8_t settlement_price_fraction_indicator;                     /* byte 7 */
} SettlementPriceFutureOptionsSummaryMessageNegativeWholePair;

/* any Settlement Price Future Options Summary Message Negative Whole Pair at all: every byte one the checker chooses */
static void any_settlement_price_future_options_summary_message_negative_whole_pair(SettlementPriceFutureOptionsSummaryMessageNegativeWholePair *record) {
  for (size_t i = 0; i < 7; i++) { record->raw_settlement_price_future_options_summary_message[i] = arbitrary(); }
  record->settlement_price_fraction_indicator = arbitrary();
}

/* Settlement Price Future Options Summary Message Negative Whole Pair to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_settlement_price_future_options_summary_message_negative_whole_pair(const SettlementPriceFutureOptionsSummaryMessageNegativeWholePair *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->raw_settlement_price_future_options_summary_message[i]; }
  wire[at++] = record->settlement_price_fraction_indicator;

  return at;
}

/* Settlement Price Future Options Summary Message Negative Whole Pair off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_settlement_price_future_options_summary_message_negative_whole_pair(SettlementPriceFutureOptionsSummaryMessageNegativeWholePair *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { record->raw_settlement_price_future_options_summary_message[i] = wire[at++]; }
  record->settlement_price_fraction_indicator = wire[at++];

  return at;
}

/* what was read of Settlement Price Future Options Summary Message Negative Whole Pair is what was written, byte for byte */
static void equal_settlement_price_future_options_summary_message_negative_whole_pair(const SettlementPriceFutureOptionsSummaryMessageNegativeWholePair *read, const SettlementPriceFutureOptionsSummaryMessageNegativeWholePair *written) {
  for (size_t i = 0; i < 7; i++) { assert(read->raw_settlement_price_future_options_summary_message[i] == written->raw_settlement_price_future_options_summary_message[i]); }
  assert(read->settlement_price_fraction_indicator == written->settlement_price_fraction_indicator);
}

/* Settlement Price Future Options Summary Message Negative Whole Pair: written and read back, then read and written back */
static void check_settlement_price_future_options_summary_message_negative_whole_pair(void) {
  SettlementPriceFutureOptionsSummaryMessageNegativeWholePair sent;
  SettlementPriceFutureOptionsSummaryMessageNegativeWholePair got;
  uint8_t wire[8];
  uint8_t again[8];

  any_settlement_price_future_options_summary_message_negative_whole_pair(&sent);
  assert(encode_settlement_price_future_options_summary_message_negative_whole_pair(&sent, wire, 0) == 8);
  assert(decode_settlement_price_future_options_summary_message_negative_whole_pair(&got, wire, 0) == 8);
  equal_settlement_price_future_options_summary_message_negative_whole_pair(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_settlement_price_future_options_summary_message_negative_whole_pair(&got, wire, 0) == 8);
  assert(encode_settlement_price_future_options_summary_message_negative_whole_pair(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Settlement Price Future Options Summary Message Negative Ten Pair: 8 bytes ---- */

typedef struct {
  uint8_t raw_settlement_price_future_options_summary_message[7];  /* bytes 0 to 6 */
  uint8_t settlement_price_fraction_indicator;                     /* byte 7 */
} SettlementPriceFutureOptionsSummaryMessageNegativeTenPair;

/* any Settlement Price Future Options Summary Message Negative Ten Pair at all: every byte one the checker chooses */
static void any_settlement_price_future_options_summary_message_negative_ten_pair(SettlementPriceFutureOptionsSummaryMessageNegativeTenPair *record) {
  for (size_t i = 0; i < 7; i++) { record->raw_settlement_price_future_options_summary_message[i] = arbitrary(); }
  record->settlement_price_fraction_indicator = arbitrary();
}

/* Settlement Price Future Options Summary Message Negative Ten Pair to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_settlement_price_future_options_summary_message_negative_ten_pair(const SettlementPriceFutureOptionsSummaryMessageNegativeTenPair *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->raw_settlement_price_future_options_summary_message[i]; }
  wire[at++] = record->settlement_price_fraction_indicator;

  return at;
}

/* Settlement Price Future Options Summary Message Negative Ten Pair off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_settlement_price_future_options_summary_message_negative_ten_pair(SettlementPriceFutureOptionsSummaryMessageNegativeTenPair *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { record->raw_settlement_price_future_options_summary_message[i] = wire[at++]; }
  record->settlement_price_fraction_indicator = wire[at++];

  return at;
}

/* what was read of Settlement Price Future Options Summary Message Negative Ten Pair is what was written, byte for byte */
static void equal_settlement_price_future_options_summary_message_negative_ten_pair(const SettlementPriceFutureOptionsSummaryMessageNegativeTenPair *read, const SettlementPriceFutureOptionsSummaryMessageNegativeTenPair *written) {
  for (size_t i = 0; i < 7; i++) { assert(read->raw_settlement_price_future_options_summary_message[i] == written->raw_settlement_price_future_options_summary_message[i]); }
  assert(read->settlement_price_fraction_indicator == written->settlement_price_fraction_indicator);
}

/* Settlement Price Future Options Summary Message Negative Ten Pair: written and read back, then read and written back */
static void check_settlement_price_future_options_summary_message_negative_ten_pair(void) {
  SettlementPriceFutureOptionsSummaryMessageNegativeTenPair sent;
  SettlementPriceFutureOptionsSummaryMessageNegativeTenPair got;
  uint8_t wire[8];
  uint8_t again[8];

  any_settlement_price_future_options_summary_message_negative_ten_pair(&sent);
  assert(encode_settlement_price_future_options_summary_message_negative_ten_pair(&sent, wire, 0) == 8);
  assert(decode_settlement_price_future_options_summary_message_negative_ten_pair(&got, wire, 0) == 8);
  equal_settlement_price_future_options_summary_message_negative_ten_pair(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_settlement_price_future_options_summary_message_negative_ten_pair(&got, wire, 0) == 8);
  assert(encode_settlement_price_future_options_summary_message_negative_ten_pair(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Settlement Price Future Options Summary Message Negative Hundred Pair: 8 bytes ---- */

typedef struct {
  uint8_t raw_settlement_price_future_options_summary_message[7];  /* bytes 0 to 6 */
  uint8_t settlement_price_fraction_indicator;                     /* byte 7 */
} SettlementPriceFutureOptionsSummaryMessageNegativeHundredPair;

/* any Settlement Price Future Options Summary Message Negative Hundred Pair at all: every byte one the checker chooses */
static void any_settlement_price_future_options_summary_message_negative_hundred_pair(SettlementPriceFutureOptionsSummaryMessageNegativeHundredPair *record) {
  for (size_t i = 0; i < 7; i++) { record->raw_settlement_price_future_options_summary_message[i] = arbitrary(); }
  record->settlement_price_fraction_indicator = arbitrary();
}

/* Settlement Price Future Options Summary Message Negative Hundred Pair to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_settlement_price_future_options_summary_message_negative_hundred_pair(const SettlementPriceFutureOptionsSummaryMessageNegativeHundredPair *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->raw_settlement_price_future_options_summary_message[i]; }
  wire[at++] = record->settlement_price_fraction_indicator;

  return at;
}

/* Settlement Price Future Options Summary Message Negative Hundred Pair off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_settlement_price_future_options_summary_message_negative_hundred_pair(SettlementPriceFutureOptionsSummaryMessageNegativeHundredPair *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { record->raw_settlement_price_future_options_summary_message[i] = wire[at++]; }
  record->settlement_price_fraction_indicator = wire[at++];

  return at;
}

/* what was read of Settlement Price Future Options Summary Message Negative Hundred Pair is what was written, byte for byte */
static void equal_settlement_price_future_options_summary_message_negative_hundred_pair(const SettlementPriceFutureOptionsSummaryMessageNegativeHundredPair *read, const SettlementPriceFutureOptionsSummaryMessageNegativeHundredPair *written) {
  for (size_t i = 0; i < 7; i++) { assert(read->raw_settlement_price_future_options_summary_message[i] == written->raw_settlement_price_future_options_summary_message[i]); }
  assert(read->settlement_price_fraction_indicator == written->settlement_price_fraction_indicator);
}

/* Settlement Price Future Options Summary Message Negative Hundred Pair: written and read back, then read and written back */
static void check_settlement_price_future_options_summary_message_negative_hundred_pair(void) {
  SettlementPriceFutureOptionsSummaryMessageNegativeHundredPair sent;
  SettlementPriceFutureOptionsSummaryMessageNegativeHundredPair got;
  uint8_t wire[8];
  uint8_t again[8];

  any_settlement_price_future_options_summary_message_negative_hundred_pair(&sent);
  assert(encode_settlement_price_future_options_summary_message_negative_hundred_pair(&sent, wire, 0) == 8);
  assert(decode_settlement_price_future_options_summary_message_negative_hundred_pair(&got, wire, 0) == 8);
  equal_settlement_price_future_options_summary_message_negative_hundred_pair(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_settlement_price_future_options_summary_message_negative_hundred_pair(&got, wire, 0) == 8);
  assert(encode_settlement_price_future_options_summary_message_negative_hundred_pair(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Settlement Price Future Options Summary Message Negative Thousand Pair: 8 bytes ---- */

typedef struct {
  uint8_t raw_settlement_price_future_options_summary_message[7];  /* bytes 0 to 6 */
  uint8_t settlement_price_fraction_indicator;                     /* byte 7 */
} SettlementPriceFutureOptionsSummaryMessageNegativeThousandPair;

/* any Settlement Price Future Options Summary Message Negative Thousand Pair at all: every byte one the checker chooses */
static void any_settlement_price_future_options_summary_message_negative_thousand_pair(SettlementPriceFutureOptionsSummaryMessageNegativeThousandPair *record) {
  for (size_t i = 0; i < 7; i++) { record->raw_settlement_price_future_options_summary_message[i] = arbitrary(); }
  record->settlement_price_fraction_indicator = arbitrary();
}

/* Settlement Price Future Options Summary Message Negative Thousand Pair to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_settlement_price_future_options_summary_message_negative_thousand_pair(const SettlementPriceFutureOptionsSummaryMessageNegativeThousandPair *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->raw_settlement_price_future_options_summary_message[i]; }
  wire[at++] = record->settlement_price_fraction_indicator;

  return at;
}

/* Settlement Price Future Options Summary Message Negative Thousand Pair off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_settlement_price_future_options_summary_message_negative_thousand_pair(SettlementPriceFutureOptionsSummaryMessageNegativeThousandPair *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { record->raw_settlement_price_future_options_summary_message[i] = wire[at++]; }
  record->settlement_price_fraction_indicator = wire[at++];

  return at;
}

/* what was read of Settlement Price Future Options Summary Message Negative Thousand Pair is what was written, byte for byte */
static void equal_settlement_price_future_options_summary_message_negative_thousand_pair(const SettlementPriceFutureOptionsSummaryMessageNegativeThousandPair *read, const SettlementPriceFutureOptionsSummaryMessageNegativeThousandPair *written) {
  for (size_t i = 0; i < 7; i++) { assert(read->raw_settlement_price_future_options_summary_message[i] == written->raw_settlement_price_future_options_summary_message[i]); }
  assert(read->settlement_price_fraction_indicator == written->settlement_price_fraction_indicator);
}

/* Settlement Price Future Options Summary Message Negative Thousand Pair: written and read back, then read and written back */
static void check_settlement_price_future_options_summary_message_negative_thousand_pair(void) {
  SettlementPriceFutureOptionsSummaryMessageNegativeThousandPair sent;
  SettlementPriceFutureOptionsSummaryMessageNegativeThousandPair got;
  uint8_t wire[8];
  uint8_t again[8];

  any_settlement_price_future_options_summary_message_negative_thousand_pair(&sent);
  assert(encode_settlement_price_future_options_summary_message_negative_thousand_pair(&sent, wire, 0) == 8);
  assert(decode_settlement_price_future_options_summary_message_negative_thousand_pair(&got, wire, 0) == 8);
  equal_settlement_price_future_options_summary_message_negative_thousand_pair(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_settlement_price_future_options_summary_message_negative_thousand_pair(&got, wire, 0) == 8);
  assert(encode_settlement_price_future_options_summary_message_negative_thousand_pair(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Settlement Price Future Options Summary Message Negative Ten Thousand Pair: 8 bytes ---- */

typedef struct {
  uint8_t raw_settlement_price_future_options_summary_message[7];  /* bytes 0 to 6 */
  uint8_t settlement_price_fraction_indicator;                     /* byte 7 */
} SettlementPriceFutureOptionsSummaryMessageNegativeTenThou_4kdujz;

/* any Settlement Price Future Options Summary Message Negative Ten Thousand Pair at all: every byte one the checker chooses */
static void any_settlement_price_future_options_summary_message_negative_ten_thou_4kdujz(SettlementPriceFutureOptionsSummaryMessageNegativeTenThou_4kdujz *record) {
  for (size_t i = 0; i < 7; i++) { record->raw_settlement_price_future_options_summary_message[i] = arbitrary(); }
  record->settlement_price_fraction_indicator = arbitrary();
}

/* Settlement Price Future Options Summary Message Negative Ten Thousand Pair to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_settlement_price_future_options_summary_message_negative_ten_thou_4kdujz(const SettlementPriceFutureOptionsSummaryMessageNegativeTenThou_4kdujz *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->raw_settlement_price_future_options_summary_message[i]; }
  wire[at++] = record->settlement_price_fraction_indicator;

  return at;
}

/* Settlement Price Future Options Summary Message Negative Ten Thousand Pair off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_settlement_price_future_options_summary_message_negative_ten_thou_4kdujz(SettlementPriceFutureOptionsSummaryMessageNegativeTenThou_4kdujz *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { record->raw_settlement_price_future_options_summary_message[i] = wire[at++]; }
  record->settlement_price_fraction_indicator = wire[at++];

  return at;
}

/* what was read of Settlement Price Future Options Summary Message Negative Ten Thousand Pair is what was written, byte for byte */
static void equal_settlement_price_future_options_summary_message_negative_ten_thou_4kdujz(const SettlementPriceFutureOptionsSummaryMessageNegativeTenThou_4kdujz *read, const SettlementPriceFutureOptionsSummaryMessageNegativeTenThou_4kdujz *written) {
  for (size_t i = 0; i < 7; i++) { assert(read->raw_settlement_price_future_options_summary_message[i] == written->raw_settlement_price_future_options_summary_message[i]); }
  assert(read->settlement_price_fraction_indicator == written->settlement_price_fraction_indicator);
}

/* Settlement Price Future Options Summary Message Negative Ten Thousand Pair: written and read back, then read and written back */
static void check_settlement_price_future_options_summary_message_negative_ten_thou_4kdujz(void) {
  SettlementPriceFutureOptionsSummaryMessageNegativeTenThou_4kdujz sent;
  SettlementPriceFutureOptionsSummaryMessageNegativeTenThou_4kdujz got;
  uint8_t wire[8];
  uint8_t again[8];

  any_settlement_price_future_options_summary_message_negative_ten_thou_4kdujz(&sent);
  assert(encode_settlement_price_future_options_summary_message_negative_ten_thou_4kdujz(&sent, wire, 0) == 8);
  assert(decode_settlement_price_future_options_summary_message_negative_ten_thou_4kdujz(&got, wire, 0) == 8);
  equal_settlement_price_future_options_summary_message_negative_ten_thou_4kdujz(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_settlement_price_future_options_summary_message_negative_ten_thou_4kdujz(&got, wire, 0) == 8);
  assert(encode_settlement_price_future_options_summary_message_negative_ten_thou_4kdujz(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Settlement Price Future Options Summary Message Negative Hundred Thousand Pair: 8 bytes ---- */

typedef struct {
  uint8_t raw_settlement_price_future_options_summary_message[7];  /* bytes 0 to 6 */
  uint8_t settlement_price_fraction_indicator;                     /* byte 7 */
} SettlementPriceFutureOptionsSummaryMessageNegativeHundred_84tec0;

/* any Settlement Price Future Options Summary Message Negative Hundred Thousand Pair at all: every byte one the checker chooses */
static void any_settlement_price_future_options_summary_message_negative_hundred_84tec0(SettlementPriceFutureOptionsSummaryMessageNegativeHundred_84tec0 *record) {
  for (size_t i = 0; i < 7; i++) { record->raw_settlement_price_future_options_summary_message[i] = arbitrary(); }
  record->settlement_price_fraction_indicator = arbitrary();
}

/* Settlement Price Future Options Summary Message Negative Hundred Thousand Pair to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_settlement_price_future_options_summary_message_negative_hundred_84tec0(const SettlementPriceFutureOptionsSummaryMessageNegativeHundred_84tec0 *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->raw_settlement_price_future_options_summary_message[i]; }
  wire[at++] = record->settlement_price_fraction_indicator;

  return at;
}

/* Settlement Price Future Options Summary Message Negative Hundred Thousand Pair off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_settlement_price_future_options_summary_message_negative_hundred_84tec0(SettlementPriceFutureOptionsSummaryMessageNegativeHundred_84tec0 *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { record->raw_settlement_price_future_options_summary_message[i] = wire[at++]; }
  record->settlement_price_fraction_indicator = wire[at++];

  return at;
}

/* what was read of Settlement Price Future Options Summary Message Negative Hundred Thousand Pair is what was written, byte for byte */
static void equal_settlement_price_future_options_summary_message_negative_hundred_84tec0(const SettlementPriceFutureOptionsSummaryMessageNegativeHundred_84tec0 *read, const SettlementPriceFutureOptionsSummaryMessageNegativeHundred_84tec0 *written) {
  for (size_t i = 0; i < 7; i++) { assert(read->raw_settlement_price_future_options_summary_message[i] == written->raw_settlement_price_future_options_summary_message[i]); }
  assert(read->settlement_price_fraction_indicator == written->settlement_price_fraction_indicator);
}

/* Settlement Price Future Options Summary Message Negative Hundred Thousand Pair: written and read back, then read and written back */
static void check_settlement_price_future_options_summary_message_negative_hundred_84tec0(void) {
  SettlementPriceFutureOptionsSummaryMessageNegativeHundred_84tec0 sent;
  SettlementPriceFutureOptionsSummaryMessageNegativeHundred_84tec0 got;
  uint8_t wire[8];
  uint8_t again[8];

  any_settlement_price_future_options_summary_message_negative_hundred_84tec0(&sent);
  assert(encode_settlement_price_future_options_summary_message_negative_hundred_84tec0(&sent, wire, 0) == 8);
  assert(decode_settlement_price_future_options_summary_message_negative_hundred_84tec0(&got, wire, 0) == 8);
  equal_settlement_price_future_options_summary_message_negative_hundred_84tec0(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_settlement_price_future_options_summary_message_negative_hundred_84tec0(&got, wire, 0) == 8);
  assert(encode_settlement_price_future_options_summary_message_negative_hundred_84tec0(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Settlement Price Future Options Summary Message Negative Million Pair: 8 bytes ---- */

typedef struct {
  uint8_t raw_settlement_price_future_options_summary_message[7];  /* bytes 0 to 6 */
  uint8_t settlement_price_fraction_indicator;                     /* byte 7 */
} SettlementPriceFutureOptionsSummaryMessageNegativeMillionPair;

/* any Settlement Price Future Options Summary Message Negative Million Pair at all: every byte one the checker chooses */
static void any_settlement_price_future_options_summary_message_negative_million_pair(SettlementPriceFutureOptionsSummaryMessageNegativeMillionPair *record) {
  for (size_t i = 0; i < 7; i++) { record->raw_settlement_price_future_options_summary_message[i] = arbitrary(); }
  record->settlement_price_fraction_indicator = arbitrary();
}

/* Settlement Price Future Options Summary Message Negative Million Pair to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_settlement_price_future_options_summary_message_negative_million_pair(const SettlementPriceFutureOptionsSummaryMessageNegativeMillionPair *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->raw_settlement_price_future_options_summary_message[i]; }
  wire[at++] = record->settlement_price_fraction_indicator;

  return at;
}

/* Settlement Price Future Options Summary Message Negative Million Pair off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_settlement_price_future_options_summary_message_negative_million_pair(SettlementPriceFutureOptionsSummaryMessageNegativeMillionPair *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { record->raw_settlement_price_future_options_summary_message[i] = wire[at++]; }
  record->settlement_price_fraction_indicator = wire[at++];

  return at;
}

/* what was read of Settlement Price Future Options Summary Message Negative Million Pair is what was written, byte for byte */
static void equal_settlement_price_future_options_summary_message_negative_million_pair(const SettlementPriceFutureOptionsSummaryMessageNegativeMillionPair *read, const SettlementPriceFutureOptionsSummaryMessageNegativeMillionPair *written) {
  for (size_t i = 0; i < 7; i++) { assert(read->raw_settlement_price_future_options_summary_message[i] == written->raw_settlement_price_future_options_summary_message[i]); }
  assert(read->settlement_price_fraction_indicator == written->settlement_price_fraction_indicator);
}

/* Settlement Price Future Options Summary Message Negative Million Pair: written and read back, then read and written back */
static void check_settlement_price_future_options_summary_message_negative_million_pair(void) {
  SettlementPriceFutureOptionsSummaryMessageNegativeMillionPair sent;
  SettlementPriceFutureOptionsSummaryMessageNegativeMillionPair got;
  uint8_t wire[8];
  uint8_t again[8];

  any_settlement_price_future_options_summary_message_negative_million_pair(&sent);
  assert(encode_settlement_price_future_options_summary_message_negative_million_pair(&sent, wire, 0) == 8);
  assert(decode_settlement_price_future_options_summary_message_negative_million_pair(&got, wire, 0) == 8);
  equal_settlement_price_future_options_summary_message_negative_million_pair(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_settlement_price_future_options_summary_message_negative_million_pair(&got, wire, 0) == 8);
  assert(encode_settlement_price_future_options_summary_message_negative_million_pair(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Settlement Price Future Options Summary Message Numeric Pair: 8 bytes ---- */

typedef struct {
  uint8_t settlement_price[7];                  /* bytes 0 to 6 */
  uint8_t settlement_price_fraction_indicator;  /* byte 7 */
} SettlementPriceFutureOptionsSummaryMessageNumericPair;

/* any Settlement Price Future Options Summary Message Numeric Pair at all: every byte one the checker chooses */
static void any_settlement_price_future_options_summary_message_numeric_pair(SettlementPriceFutureOptionsSummaryMessageNumericPair *record) {
  for (size_t i = 0; i < 7; i++) { record->settlement_price[i] = arbitrary(); }
  record->settlement_price_fraction_indicator = arbitrary();
}

/* Settlement Price Future Options Summary Message Numeric Pair to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_settlement_price_future_options_summary_message_numeric_pair(const SettlementPriceFutureOptionsSummaryMessageNumericPair *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->settlement_price[i]; }
  wire[at++] = record->settlement_price_fraction_indicator;

  return at;
}

/* Settlement Price Future Options Summary Message Numeric Pair off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_settlement_price_future_options_summary_message_numeric_pair(SettlementPriceFutureOptionsSummaryMessageNumericPair *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { record->settlement_price[i] = wire[at++]; }
  record->settlement_price_fraction_indicator = wire[at++];

  return at;
}

/* what was read of Settlement Price Future Options Summary Message Numeric Pair is what was written, byte for byte */
static void equal_settlement_price_future_options_summary_message_numeric_pair(const SettlementPriceFutureOptionsSummaryMessageNumericPair *read, const SettlementPriceFutureOptionsSummaryMessageNumericPair *written) {
  for (size_t i = 0; i < 7; i++) { assert(read->settlement_price[i] == written->settlement_price[i]); }
  assert(read->settlement_price_fraction_indicator == written->settlement_price_fraction_indicator);
}

/* Settlement Price Future Options Summary Message Numeric Pair: written and read back, then read and written back */
static void check_settlement_price_future_options_summary_message_numeric_pair(void) {
  SettlementPriceFutureOptionsSummaryMessageNumericPair sent;
  SettlementPriceFutureOptionsSummaryMessageNumericPair got;
  uint8_t wire[8];
  uint8_t again[8];

  any_settlement_price_future_options_summary_message_numeric_pair(&sent);
  assert(encode_settlement_price_future_options_summary_message_numeric_pair(&sent, wire, 0) == 8);
  assert(decode_settlement_price_future_options_summary_message_numeric_pair(&got, wire, 0) == 8);
  equal_settlement_price_future_options_summary_message_numeric_pair(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_settlement_price_future_options_summary_message_numeric_pair(&got, wire, 0) == 8);
  assert(encode_settlement_price_future_options_summary_message_numeric_pair(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Previous Settlement Negative Whole Pair: 8 bytes ------------------------ */

typedef struct {
  uint8_t raw_previous_settlement[7];              /* bytes 0 to 6 */
  uint8_t previous_settlement_fraction_indicator;  /* byte 7 */
} PreviousSettlementNegativeWholePair;

/* any Previous Settlement Negative Whole Pair at all: every byte one the checker chooses */
static void any_previous_settlement_negative_whole_pair(PreviousSettlementNegativeWholePair *record) {
  for (size_t i = 0; i < 7; i++) { record->raw_previous_settlement[i] = arbitrary(); }
  record->previous_settlement_fraction_indicator = arbitrary();
}

/* Previous Settlement Negative Whole Pair to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_previous_settlement_negative_whole_pair(const PreviousSettlementNegativeWholePair *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->raw_previous_settlement[i]; }
  wire[at++] = record->previous_settlement_fraction_indicator;

  return at;
}

/* Previous Settlement Negative Whole Pair off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_previous_settlement_negative_whole_pair(PreviousSettlementNegativeWholePair *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { record->raw_previous_settlement[i] = wire[at++]; }
  record->previous_settlement_fraction_indicator = wire[at++];

  return at;
}

/* what was read of Previous Settlement Negative Whole Pair is what was written, byte for byte */
static void equal_previous_settlement_negative_whole_pair(const PreviousSettlementNegativeWholePair *read, const PreviousSettlementNegativeWholePair *written) {
  for (size_t i = 0; i < 7; i++) { assert(read->raw_previous_settlement[i] == written->raw_previous_settlement[i]); }
  assert(read->previous_settlement_fraction_indicator == written->previous_settlement_fraction_indicator);
}

/* Previous Settlement Negative Whole Pair: written and read back, then read and written back */
static void check_previous_settlement_negative_whole_pair(void) {
  PreviousSettlementNegativeWholePair sent;
  PreviousSettlementNegativeWholePair got;
  uint8_t wire[8];
  uint8_t again[8];

  any_previous_settlement_negative_whole_pair(&sent);
  assert(encode_previous_settlement_negative_whole_pair(&sent, wire, 0) == 8);
  assert(decode_previous_settlement_negative_whole_pair(&got, wire, 0) == 8);
  equal_previous_settlement_negative_whole_pair(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_previous_settlement_negative_whole_pair(&got, wire, 0) == 8);
  assert(encode_previous_settlement_negative_whole_pair(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Previous Settlement Negative Ten Pair: 8 bytes -------------------------- */

typedef struct {
  uint8_t raw_previous_settlement[7];              /* bytes 0 to 6 */
  uint8_t previous_settlement_fraction_indicator;  /* byte 7 */
} PreviousSettlementNegativeTenPair;

/* any Previous Settlement Negative Ten Pair at all: every byte one the checker chooses */
static void any_previous_settlement_negative_ten_pair(PreviousSettlementNegativeTenPair *record) {
  for (size_t i = 0; i < 7; i++) { record->raw_previous_settlement[i] = arbitrary(); }
  record->previous_settlement_fraction_indicator = arbitrary();
}

/* Previous Settlement Negative Ten Pair to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_previous_settlement_negative_ten_pair(const PreviousSettlementNegativeTenPair *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->raw_previous_settlement[i]; }
  wire[at++] = record->previous_settlement_fraction_indicator;

  return at;
}

/* Previous Settlement Negative Ten Pair off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_previous_settlement_negative_ten_pair(PreviousSettlementNegativeTenPair *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { record->raw_previous_settlement[i] = wire[at++]; }
  record->previous_settlement_fraction_indicator = wire[at++];

  return at;
}

/* what was read of Previous Settlement Negative Ten Pair is what was written, byte for byte */
static void equal_previous_settlement_negative_ten_pair(const PreviousSettlementNegativeTenPair *read, const PreviousSettlementNegativeTenPair *written) {
  for (size_t i = 0; i < 7; i++) { assert(read->raw_previous_settlement[i] == written->raw_previous_settlement[i]); }
  assert(read->previous_settlement_fraction_indicator == written->previous_settlement_fraction_indicator);
}

/* Previous Settlement Negative Ten Pair: written and read back, then read and written back */
static void check_previous_settlement_negative_ten_pair(void) {
  PreviousSettlementNegativeTenPair sent;
  PreviousSettlementNegativeTenPair got;
  uint8_t wire[8];
  uint8_t again[8];

  any_previous_settlement_negative_ten_pair(&sent);
  assert(encode_previous_settlement_negative_ten_pair(&sent, wire, 0) == 8);
  assert(decode_previous_settlement_negative_ten_pair(&got, wire, 0) == 8);
  equal_previous_settlement_negative_ten_pair(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_previous_settlement_negative_ten_pair(&got, wire, 0) == 8);
  assert(encode_previous_settlement_negative_ten_pair(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Previous Settlement Negative Hundred Pair: 8 bytes ---------------------- */

typedef struct {
  uint8_t raw_previous_settlement[7];              /* bytes 0 to 6 */
  uint8_t previous_settlement_fraction_indicator;  /* byte 7 */
} PreviousSettlementNegativeHundredPair;

/* any Previous Settlement Negative Hundred Pair at all: every byte one the checker chooses */
static void any_previous_settlement_negative_hundred_pair(PreviousSettlementNegativeHundredPair *record) {
  for (size_t i = 0; i < 7; i++) { record->raw_previous_settlement[i] = arbitrary(); }
  record->previous_settlement_fraction_indicator = arbitrary();
}

/* Previous Settlement Negative Hundred Pair to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_previous_settlement_negative_hundred_pair(const PreviousSettlementNegativeHundredPair *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->raw_previous_settlement[i]; }
  wire[at++] = record->previous_settlement_fraction_indicator;

  return at;
}

/* Previous Settlement Negative Hundred Pair off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_previous_settlement_negative_hundred_pair(PreviousSettlementNegativeHundredPair *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { record->raw_previous_settlement[i] = wire[at++]; }
  record->previous_settlement_fraction_indicator = wire[at++];

  return at;
}

/* what was read of Previous Settlement Negative Hundred Pair is what was written, byte for byte */
static void equal_previous_settlement_negative_hundred_pair(const PreviousSettlementNegativeHundredPair *read, const PreviousSettlementNegativeHundredPair *written) {
  for (size_t i = 0; i < 7; i++) { assert(read->raw_previous_settlement[i] == written->raw_previous_settlement[i]); }
  assert(read->previous_settlement_fraction_indicator == written->previous_settlement_fraction_indicator);
}

/* Previous Settlement Negative Hundred Pair: written and read back, then read and written back */
static void check_previous_settlement_negative_hundred_pair(void) {
  PreviousSettlementNegativeHundredPair sent;
  PreviousSettlementNegativeHundredPair got;
  uint8_t wire[8];
  uint8_t again[8];

  any_previous_settlement_negative_hundred_pair(&sent);
  assert(encode_previous_settlement_negative_hundred_pair(&sent, wire, 0) == 8);
  assert(decode_previous_settlement_negative_hundred_pair(&got, wire, 0) == 8);
  equal_previous_settlement_negative_hundred_pair(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_previous_settlement_negative_hundred_pair(&got, wire, 0) == 8);
  assert(encode_previous_settlement_negative_hundred_pair(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Previous Settlement Negative Thousand Pair: 8 bytes --------------------- */

typedef struct {
  uint8_t raw_previous_settlement[7];              /* bytes 0 to 6 */
  uint8_t previous_settlement_fraction_indicator;  /* byte 7 */
} PreviousSettlementNegativeThousandPair;

/* any Previous Settlement Negative Thousand Pair at all: every byte one the checker chooses */
static void any_previous_settlement_negative_thousand_pair(PreviousSettlementNegativeThousandPair *record) {
  for (size_t i = 0; i < 7; i++) { record->raw_previous_settlement[i] = arbitrary(); }
  record->previous_settlement_fraction_indicator = arbitrary();
}

/* Previous Settlement Negative Thousand Pair to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_previous_settlement_negative_thousand_pair(const PreviousSettlementNegativeThousandPair *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->raw_previous_settlement[i]; }
  wire[at++] = record->previous_settlement_fraction_indicator;

  return at;
}

/* Previous Settlement Negative Thousand Pair off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_previous_settlement_negative_thousand_pair(PreviousSettlementNegativeThousandPair *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { record->raw_previous_settlement[i] = wire[at++]; }
  record->previous_settlement_fraction_indicator = wire[at++];

  return at;
}

/* what was read of Previous Settlement Negative Thousand Pair is what was written, byte for byte */
static void equal_previous_settlement_negative_thousand_pair(const PreviousSettlementNegativeThousandPair *read, const PreviousSettlementNegativeThousandPair *written) {
  for (size_t i = 0; i < 7; i++) { assert(read->raw_previous_settlement[i] == written->raw_previous_settlement[i]); }
  assert(read->previous_settlement_fraction_indicator == written->previous_settlement_fraction_indicator);
}

/* Previous Settlement Negative Thousand Pair: written and read back, then read and written back */
static void check_previous_settlement_negative_thousand_pair(void) {
  PreviousSettlementNegativeThousandPair sent;
  PreviousSettlementNegativeThousandPair got;
  uint8_t wire[8];
  uint8_t again[8];

  any_previous_settlement_negative_thousand_pair(&sent);
  assert(encode_previous_settlement_negative_thousand_pair(&sent, wire, 0) == 8);
  assert(decode_previous_settlement_negative_thousand_pair(&got, wire, 0) == 8);
  equal_previous_settlement_negative_thousand_pair(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_previous_settlement_negative_thousand_pair(&got, wire, 0) == 8);
  assert(encode_previous_settlement_negative_thousand_pair(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Previous Settlement Negative Ten Thousand Pair: 8 bytes ----------------- */

typedef struct {
  uint8_t raw_previous_settlement[7];              /* bytes 0 to 6 */
  uint8_t previous_settlement_fraction_indicator;  /* byte 7 */
} PreviousSettlementNegativeTenThousandPair;

/* any Previous Settlement Negative Ten Thousand Pair at all: every byte one the checker chooses */
static void any_previous_settlement_negative_ten_thousand_pair(PreviousSettlementNegativeTenThousandPair *record) {
  for (size_t i = 0; i < 7; i++) { record->raw_previous_settlement[i] = arbitrary(); }
  record->previous_settlement_fraction_indicator = arbitrary();
}

/* Previous Settlement Negative Ten Thousand Pair to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_previous_settlement_negative_ten_thousand_pair(const PreviousSettlementNegativeTenThousandPair *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->raw_previous_settlement[i]; }
  wire[at++] = record->previous_settlement_fraction_indicator;

  return at;
}

/* Previous Settlement Negative Ten Thousand Pair off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_previous_settlement_negative_ten_thousand_pair(PreviousSettlementNegativeTenThousandPair *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { record->raw_previous_settlement[i] = wire[at++]; }
  record->previous_settlement_fraction_indicator = wire[at++];

  return at;
}

/* what was read of Previous Settlement Negative Ten Thousand Pair is what was written, byte for byte */
static void equal_previous_settlement_negative_ten_thousand_pair(const PreviousSettlementNegativeTenThousandPair *read, const PreviousSettlementNegativeTenThousandPair *written) {
  for (size_t i = 0; i < 7; i++) { assert(read->raw_previous_settlement[i] == written->raw_previous_settlement[i]); }
  assert(read->previous_settlement_fraction_indicator == written->previous_settlement_fraction_indicator);
}

/* Previous Settlement Negative Ten Thousand Pair: written and read back, then read and written back */
static void check_previous_settlement_negative_ten_thousand_pair(void) {
  PreviousSettlementNegativeTenThousandPair sent;
  PreviousSettlementNegativeTenThousandPair got;
  uint8_t wire[8];
  uint8_t again[8];

  any_previous_settlement_negative_ten_thousand_pair(&sent);
  assert(encode_previous_settlement_negative_ten_thousand_pair(&sent, wire, 0) == 8);
  assert(decode_previous_settlement_negative_ten_thousand_pair(&got, wire, 0) == 8);
  equal_previous_settlement_negative_ten_thousand_pair(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_previous_settlement_negative_ten_thousand_pair(&got, wire, 0) == 8);
  assert(encode_previous_settlement_negative_ten_thousand_pair(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Previous Settlement Negative Hundred Thousand Pair: 8 bytes ------------- */

typedef struct {
  uint8_t raw_previous_settlement[7];              /* bytes 0 to 6 */
  uint8_t previous_settlement_fraction_indicator;  /* byte 7 */
} PreviousSettlementNegativeHundredThousandPair;

/* any Previous Settlement Negative Hundred Thousand Pair at all: every byte one the checker chooses */
static void any_previous_settlement_negative_hundred_thousand_pair(PreviousSettlementNegativeHundredThousandPair *record) {
  for (size_t i = 0; i < 7; i++) { record->raw_previous_settlement[i] = arbitrary(); }
  record->previous_settlement_fraction_indicator = arbitrary();
}

/* Previous Settlement Negative Hundred Thousand Pair to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_previous_settlement_negative_hundred_thousand_pair(const PreviousSettlementNegativeHundredThousandPair *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->raw_previous_settlement[i]; }
  wire[at++] = record->previous_settlement_fraction_indicator;

  return at;
}

/* Previous Settlement Negative Hundred Thousand Pair off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_previous_settlement_negative_hundred_thousand_pair(PreviousSettlementNegativeHundredThousandPair *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { record->raw_previous_settlement[i] = wire[at++]; }
  record->previous_settlement_fraction_indicator = wire[at++];

  return at;
}

/* what was read of Previous Settlement Negative Hundred Thousand Pair is what was written, byte for byte */
static void equal_previous_settlement_negative_hundred_thousand_pair(const PreviousSettlementNegativeHundredThousandPair *read, const PreviousSettlementNegativeHundredThousandPair *written) {
  for (size_t i = 0; i < 7; i++) { assert(read->raw_previous_settlement[i] == written->raw_previous_settlement[i]); }
  assert(read->previous_settlement_fraction_indicator == written->previous_settlement_fraction_indicator);
}

/* Previous Settlement Negative Hundred Thousand Pair: written and read back, then read and written back */
static void check_previous_settlement_negative_hundred_thousand_pair(void) {
  PreviousSettlementNegativeHundredThousandPair sent;
  PreviousSettlementNegativeHundredThousandPair got;
  uint8_t wire[8];
  uint8_t again[8];

  any_previous_settlement_negative_hundred_thousand_pair(&sent);
  assert(encode_previous_settlement_negative_hundred_thousand_pair(&sent, wire, 0) == 8);
  assert(decode_previous_settlement_negative_hundred_thousand_pair(&got, wire, 0) == 8);
  equal_previous_settlement_negative_hundred_thousand_pair(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_previous_settlement_negative_hundred_thousand_pair(&got, wire, 0) == 8);
  assert(encode_previous_settlement_negative_hundred_thousand_pair(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Previous Settlement Negative Million Pair: 8 bytes ---------------------- */

typedef struct {
  uint8_t raw_previous_settlement[7];              /* bytes 0 to 6 */
  uint8_t previous_settlement_fraction_indicator;  /* byte 7 */
} PreviousSettlementNegativeMillionPair;

/* any Previous Settlement Negative Million Pair at all: every byte one the checker chooses */
static void any_previous_settlement_negative_million_pair(PreviousSettlementNegativeMillionPair *record) {
  for (size_t i = 0; i < 7; i++) { record->raw_previous_settlement[i] = arbitrary(); }
  record->previous_settlement_fraction_indicator = arbitrary();
}

/* Previous Settlement Negative Million Pair to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_previous_settlement_negative_million_pair(const PreviousSettlementNegativeMillionPair *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->raw_previous_settlement[i]; }
  wire[at++] = record->previous_settlement_fraction_indicator;

  return at;
}

/* Previous Settlement Negative Million Pair off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_previous_settlement_negative_million_pair(PreviousSettlementNegativeMillionPair *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { record->raw_previous_settlement[i] = wire[at++]; }
  record->previous_settlement_fraction_indicator = wire[at++];

  return at;
}

/* what was read of Previous Settlement Negative Million Pair is what was written, byte for byte */
static void equal_previous_settlement_negative_million_pair(const PreviousSettlementNegativeMillionPair *read, const PreviousSettlementNegativeMillionPair *written) {
  for (size_t i = 0; i < 7; i++) { assert(read->raw_previous_settlement[i] == written->raw_previous_settlement[i]); }
  assert(read->previous_settlement_fraction_indicator == written->previous_settlement_fraction_indicator);
}

/* Previous Settlement Negative Million Pair: written and read back, then read and written back */
static void check_previous_settlement_negative_million_pair(void) {
  PreviousSettlementNegativeMillionPair sent;
  PreviousSettlementNegativeMillionPair got;
  uint8_t wire[8];
  uint8_t again[8];

  any_previous_settlement_negative_million_pair(&sent);
  assert(encode_previous_settlement_negative_million_pair(&sent, wire, 0) == 8);
  assert(decode_previous_settlement_negative_million_pair(&got, wire, 0) == 8);
  equal_previous_settlement_negative_million_pair(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_previous_settlement_negative_million_pair(&got, wire, 0) == 8);
  assert(encode_previous_settlement_negative_million_pair(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Previous Settlement Numeric Pair: 8 bytes ------------------------------- */

typedef struct {
  uint8_t previous_settlement[7];                  /* bytes 0 to 6 */
  uint8_t previous_settlement_fraction_indicator;  /* byte 7 */
} PreviousSettlementNumericPair;

/* any Previous Settlement Numeric Pair at all: every byte one the checker chooses */
static void any_previous_settlement_numeric_pair(PreviousSettlementNumericPair *record) {
  for (size_t i = 0; i < 7; i++) { record->previous_settlement[i] = arbitrary(); }
  record->previous_settlement_fraction_indicator = arbitrary();
}

/* Previous Settlement Numeric Pair to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_previous_settlement_numeric_pair(const PreviousSettlementNumericPair *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->previous_settlement[i]; }
  wire[at++] = record->previous_settlement_fraction_indicator;

  return at;
}

/* Previous Settlement Numeric Pair off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_previous_settlement_numeric_pair(PreviousSettlementNumericPair *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { record->previous_settlement[i] = wire[at++]; }
  record->previous_settlement_fraction_indicator = wire[at++];

  return at;
}

/* what was read of Previous Settlement Numeric Pair is what was written, byte for byte */
static void equal_previous_settlement_numeric_pair(const PreviousSettlementNumericPair *read, const PreviousSettlementNumericPair *written) {
  for (size_t i = 0; i < 7; i++) { assert(read->previous_settlement[i] == written->previous_settlement[i]); }
  assert(read->previous_settlement_fraction_indicator == written->previous_settlement_fraction_indicator);
}

/* Previous Settlement Numeric Pair: written and read back, then read and written back */
static void check_previous_settlement_numeric_pair(void) {
  PreviousSettlementNumericPair sent;
  PreviousSettlementNumericPair got;
  uint8_t wire[8];
  uint8_t again[8];

  any_previous_settlement_numeric_pair(&sent);
  assert(encode_previous_settlement_numeric_pair(&sent, wire, 0) == 8);
  assert(decode_previous_settlement_numeric_pair(&got, wire, 0) == 8);
  equal_previous_settlement_numeric_pair(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_previous_settlement_numeric_pair(&got, wire, 0) == 8);
  assert(encode_previous_settlement_numeric_pair(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- External Price At Source Negative Whole Pair: 8 bytes ------------------- */

typedef struct {
  uint8_t raw_external_price_at_source[7];    /* bytes 0 to 6 */
  uint8_t external_price_fraction_indicator;  /* byte 7 */
} ExternalPriceAtSourceNegativeWholePair;

/* any External Price At Source Negative Whole Pair at all: every byte one the checker chooses */
static void any_external_price_at_source_negative_whole_pair(ExternalPriceAtSourceNegativeWholePair *record) {
  for (size_t i = 0; i < 7; i++) { record->raw_external_price_at_source[i] = arbitrary(); }
  record->external_price_fraction_indicator = arbitrary();
}

/* External Price At Source Negative Whole Pair to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_external_price_at_source_negative_whole_pair(const ExternalPriceAtSourceNegativeWholePair *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->raw_external_price_at_source[i]; }
  wire[at++] = record->external_price_fraction_indicator;

  return at;
}

/* External Price At Source Negative Whole Pair off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_external_price_at_source_negative_whole_pair(ExternalPriceAtSourceNegativeWholePair *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { record->raw_external_price_at_source[i] = wire[at++]; }
  record->external_price_fraction_indicator = wire[at++];

  return at;
}

/* what was read of External Price At Source Negative Whole Pair is what was written, byte for byte */
static void equal_external_price_at_source_negative_whole_pair(const ExternalPriceAtSourceNegativeWholePair *read, const ExternalPriceAtSourceNegativeWholePair *written) {
  for (size_t i = 0; i < 7; i++) { assert(read->raw_external_price_at_source[i] == written->raw_external_price_at_source[i]); }
  assert(read->external_price_fraction_indicator == written->external_price_fraction_indicator);
}

/* External Price At Source Negative Whole Pair: written and read back, then read and written back */
static void check_external_price_at_source_negative_whole_pair(void) {
  ExternalPriceAtSourceNegativeWholePair sent;
  ExternalPriceAtSourceNegativeWholePair got;
  uint8_t wire[8];
  uint8_t again[8];

  any_external_price_at_source_negative_whole_pair(&sent);
  assert(encode_external_price_at_source_negative_whole_pair(&sent, wire, 0) == 8);
  assert(decode_external_price_at_source_negative_whole_pair(&got, wire, 0) == 8);
  equal_external_price_at_source_negative_whole_pair(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_external_price_at_source_negative_whole_pair(&got, wire, 0) == 8);
  assert(encode_external_price_at_source_negative_whole_pair(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- External Price At Source Negative Ten Pair: 8 bytes --------------------- */

typedef struct {
  uint8_t raw_external_price_at_source[7];    /* bytes 0 to 6 */
  uint8_t external_price_fraction_indicator;  /* byte 7 */
} ExternalPriceAtSourceNegativeTenPair;

/* any External Price At Source Negative Ten Pair at all: every byte one the checker chooses */
static void any_external_price_at_source_negative_ten_pair(ExternalPriceAtSourceNegativeTenPair *record) {
  for (size_t i = 0; i < 7; i++) { record->raw_external_price_at_source[i] = arbitrary(); }
  record->external_price_fraction_indicator = arbitrary();
}

/* External Price At Source Negative Ten Pair to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_external_price_at_source_negative_ten_pair(const ExternalPriceAtSourceNegativeTenPair *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->raw_external_price_at_source[i]; }
  wire[at++] = record->external_price_fraction_indicator;

  return at;
}

/* External Price At Source Negative Ten Pair off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_external_price_at_source_negative_ten_pair(ExternalPriceAtSourceNegativeTenPair *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { record->raw_external_price_at_source[i] = wire[at++]; }
  record->external_price_fraction_indicator = wire[at++];

  return at;
}

/* what was read of External Price At Source Negative Ten Pair is what was written, byte for byte */
static void equal_external_price_at_source_negative_ten_pair(const ExternalPriceAtSourceNegativeTenPair *read, const ExternalPriceAtSourceNegativeTenPair *written) {
  for (size_t i = 0; i < 7; i++) { assert(read->raw_external_price_at_source[i] == written->raw_external_price_at_source[i]); }
  assert(read->external_price_fraction_indicator == written->external_price_fraction_indicator);
}

/* External Price At Source Negative Ten Pair: written and read back, then read and written back */
static void check_external_price_at_source_negative_ten_pair(void) {
  ExternalPriceAtSourceNegativeTenPair sent;
  ExternalPriceAtSourceNegativeTenPair got;
  uint8_t wire[8];
  uint8_t again[8];

  any_external_price_at_source_negative_ten_pair(&sent);
  assert(encode_external_price_at_source_negative_ten_pair(&sent, wire, 0) == 8);
  assert(decode_external_price_at_source_negative_ten_pair(&got, wire, 0) == 8);
  equal_external_price_at_source_negative_ten_pair(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_external_price_at_source_negative_ten_pair(&got, wire, 0) == 8);
  assert(encode_external_price_at_source_negative_ten_pair(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- External Price At Source Negative Hundred Pair: 8 bytes ----------------- */

typedef struct {
  uint8_t raw_external_price_at_source[7];    /* bytes 0 to 6 */
  uint8_t external_price_fraction_indicator;  /* byte 7 */
} ExternalPriceAtSourceNegativeHundredPair;

/* any External Price At Source Negative Hundred Pair at all: every byte one the checker chooses */
static void any_external_price_at_source_negative_hundred_pair(ExternalPriceAtSourceNegativeHundredPair *record) {
  for (size_t i = 0; i < 7; i++) { record->raw_external_price_at_source[i] = arbitrary(); }
  record->external_price_fraction_indicator = arbitrary();
}

/* External Price At Source Negative Hundred Pair to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_external_price_at_source_negative_hundred_pair(const ExternalPriceAtSourceNegativeHundredPair *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->raw_external_price_at_source[i]; }
  wire[at++] = record->external_price_fraction_indicator;

  return at;
}

/* External Price At Source Negative Hundred Pair off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_external_price_at_source_negative_hundred_pair(ExternalPriceAtSourceNegativeHundredPair *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { record->raw_external_price_at_source[i] = wire[at++]; }
  record->external_price_fraction_indicator = wire[at++];

  return at;
}

/* what was read of External Price At Source Negative Hundred Pair is what was written, byte for byte */
static void equal_external_price_at_source_negative_hundred_pair(const ExternalPriceAtSourceNegativeHundredPair *read, const ExternalPriceAtSourceNegativeHundredPair *written) {
  for (size_t i = 0; i < 7; i++) { assert(read->raw_external_price_at_source[i] == written->raw_external_price_at_source[i]); }
  assert(read->external_price_fraction_indicator == written->external_price_fraction_indicator);
}

/* External Price At Source Negative Hundred Pair: written and read back, then read and written back */
static void check_external_price_at_source_negative_hundred_pair(void) {
  ExternalPriceAtSourceNegativeHundredPair sent;
  ExternalPriceAtSourceNegativeHundredPair got;
  uint8_t wire[8];
  uint8_t again[8];

  any_external_price_at_source_negative_hundred_pair(&sent);
  assert(encode_external_price_at_source_negative_hundred_pair(&sent, wire, 0) == 8);
  assert(decode_external_price_at_source_negative_hundred_pair(&got, wire, 0) == 8);
  equal_external_price_at_source_negative_hundred_pair(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_external_price_at_source_negative_hundred_pair(&got, wire, 0) == 8);
  assert(encode_external_price_at_source_negative_hundred_pair(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- External Price At Source Negative Thousand Pair: 8 bytes ---------------- */

typedef struct {
  uint8_t raw_external_price_at_source[7];    /* bytes 0 to 6 */
  uint8_t external_price_fraction_indicator;  /* byte 7 */
} ExternalPriceAtSourceNegativeThousandPair;

/* any External Price At Source Negative Thousand Pair at all: every byte one the checker chooses */
static void any_external_price_at_source_negative_thousand_pair(ExternalPriceAtSourceNegativeThousandPair *record) {
  for (size_t i = 0; i < 7; i++) { record->raw_external_price_at_source[i] = arbitrary(); }
  record->external_price_fraction_indicator = arbitrary();
}

/* External Price At Source Negative Thousand Pair to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_external_price_at_source_negative_thousand_pair(const ExternalPriceAtSourceNegativeThousandPair *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->raw_external_price_at_source[i]; }
  wire[at++] = record->external_price_fraction_indicator;

  return at;
}

/* External Price At Source Negative Thousand Pair off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_external_price_at_source_negative_thousand_pair(ExternalPriceAtSourceNegativeThousandPair *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { record->raw_external_price_at_source[i] = wire[at++]; }
  record->external_price_fraction_indicator = wire[at++];

  return at;
}

/* what was read of External Price At Source Negative Thousand Pair is what was written, byte for byte */
static void equal_external_price_at_source_negative_thousand_pair(const ExternalPriceAtSourceNegativeThousandPair *read, const ExternalPriceAtSourceNegativeThousandPair *written) {
  for (size_t i = 0; i < 7; i++) { assert(read->raw_external_price_at_source[i] == written->raw_external_price_at_source[i]); }
  assert(read->external_price_fraction_indicator == written->external_price_fraction_indicator);
}

/* External Price At Source Negative Thousand Pair: written and read back, then read and written back */
static void check_external_price_at_source_negative_thousand_pair(void) {
  ExternalPriceAtSourceNegativeThousandPair sent;
  ExternalPriceAtSourceNegativeThousandPair got;
  uint8_t wire[8];
  uint8_t again[8];

  any_external_price_at_source_negative_thousand_pair(&sent);
  assert(encode_external_price_at_source_negative_thousand_pair(&sent, wire, 0) == 8);
  assert(decode_external_price_at_source_negative_thousand_pair(&got, wire, 0) == 8);
  equal_external_price_at_source_negative_thousand_pair(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_external_price_at_source_negative_thousand_pair(&got, wire, 0) == 8);
  assert(encode_external_price_at_source_negative_thousand_pair(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- External Price At Source Negative Ten Thousand Pair: 8 bytes ------------ */

typedef struct {
  uint8_t raw_external_price_at_source[7];    /* bytes 0 to 6 */
  uint8_t external_price_fraction_indicator;  /* byte 7 */
} ExternalPriceAtSourceNegativeTenThousandPair;

/* any External Price At Source Negative Ten Thousand Pair at all: every byte one the checker chooses */
static void any_external_price_at_source_negative_ten_thousand_pair(ExternalPriceAtSourceNegativeTenThousandPair *record) {
  for (size_t i = 0; i < 7; i++) { record->raw_external_price_at_source[i] = arbitrary(); }
  record->external_price_fraction_indicator = arbitrary();
}

/* External Price At Source Negative Ten Thousand Pair to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_external_price_at_source_negative_ten_thousand_pair(const ExternalPriceAtSourceNegativeTenThousandPair *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->raw_external_price_at_source[i]; }
  wire[at++] = record->external_price_fraction_indicator;

  return at;
}

/* External Price At Source Negative Ten Thousand Pair off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_external_price_at_source_negative_ten_thousand_pair(ExternalPriceAtSourceNegativeTenThousandPair *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { record->raw_external_price_at_source[i] = wire[at++]; }
  record->external_price_fraction_indicator = wire[at++];

  return at;
}

/* what was read of External Price At Source Negative Ten Thousand Pair is what was written, byte for byte */
static void equal_external_price_at_source_negative_ten_thousand_pair(const ExternalPriceAtSourceNegativeTenThousandPair *read, const ExternalPriceAtSourceNegativeTenThousandPair *written) {
  for (size_t i = 0; i < 7; i++) { assert(read->raw_external_price_at_source[i] == written->raw_external_price_at_source[i]); }
  assert(read->external_price_fraction_indicator == written->external_price_fraction_indicator);
}

/* External Price At Source Negative Ten Thousand Pair: written and read back, then read and written back */
static void check_external_price_at_source_negative_ten_thousand_pair(void) {
  ExternalPriceAtSourceNegativeTenThousandPair sent;
  ExternalPriceAtSourceNegativeTenThousandPair got;
  uint8_t wire[8];
  uint8_t again[8];

  any_external_price_at_source_negative_ten_thousand_pair(&sent);
  assert(encode_external_price_at_source_negative_ten_thousand_pair(&sent, wire, 0) == 8);
  assert(decode_external_price_at_source_negative_ten_thousand_pair(&got, wire, 0) == 8);
  equal_external_price_at_source_negative_ten_thousand_pair(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_external_price_at_source_negative_ten_thousand_pair(&got, wire, 0) == 8);
  assert(encode_external_price_at_source_negative_ten_thousand_pair(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- External Price At Source Negative Hundred Thousand Pair: 8 bytes -------- */

typedef struct {
  uint8_t raw_external_price_at_source[7];    /* bytes 0 to 6 */
  uint8_t external_price_fraction_indicator;  /* byte 7 */
} ExternalPriceAtSourceNegativeHundredThousandPair;

/* any External Price At Source Negative Hundred Thousand Pair at all: every byte one the checker chooses */
static void any_external_price_at_source_negative_hundred_thousand_pair(ExternalPriceAtSourceNegativeHundredThousandPair *record) {
  for (size_t i = 0; i < 7; i++) { record->raw_external_price_at_source[i] = arbitrary(); }
  record->external_price_fraction_indicator = arbitrary();
}

/* External Price At Source Negative Hundred Thousand Pair to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_external_price_at_source_negative_hundred_thousand_pair(const ExternalPriceAtSourceNegativeHundredThousandPair *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->raw_external_price_at_source[i]; }
  wire[at++] = record->external_price_fraction_indicator;

  return at;
}

/* External Price At Source Negative Hundred Thousand Pair off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_external_price_at_source_negative_hundred_thousand_pair(ExternalPriceAtSourceNegativeHundredThousandPair *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { record->raw_external_price_at_source[i] = wire[at++]; }
  record->external_price_fraction_indicator = wire[at++];

  return at;
}

/* what was read of External Price At Source Negative Hundred Thousand Pair is what was written, byte for byte */
static void equal_external_price_at_source_negative_hundred_thousand_pair(const ExternalPriceAtSourceNegativeHundredThousandPair *read, const ExternalPriceAtSourceNegativeHundredThousandPair *written) {
  for (size_t i = 0; i < 7; i++) { assert(read->raw_external_price_at_source[i] == written->raw_external_price_at_source[i]); }
  assert(read->external_price_fraction_indicator == written->external_price_fraction_indicator);
}

/* External Price At Source Negative Hundred Thousand Pair: written and read back, then read and written back */
static void check_external_price_at_source_negative_hundred_thousand_pair(void) {
  ExternalPriceAtSourceNegativeHundredThousandPair sent;
  ExternalPriceAtSourceNegativeHundredThousandPair got;
  uint8_t wire[8];
  uint8_t again[8];

  any_external_price_at_source_negative_hundred_thousand_pair(&sent);
  assert(encode_external_price_at_source_negative_hundred_thousand_pair(&sent, wire, 0) == 8);
  assert(decode_external_price_at_source_negative_hundred_thousand_pair(&got, wire, 0) == 8);
  equal_external_price_at_source_negative_hundred_thousand_pair(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_external_price_at_source_negative_hundred_thousand_pair(&got, wire, 0) == 8);
  assert(encode_external_price_at_source_negative_hundred_thousand_pair(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- External Price At Source Negative Million Pair: 8 bytes ----------------- */

typedef struct {
  uint8_t raw_external_price_at_source[7];    /* bytes 0 to 6 */
  uint8_t external_price_fraction_indicator;  /* byte 7 */
} ExternalPriceAtSourceNegativeMillionPair;

/* any External Price At Source Negative Million Pair at all: every byte one the checker chooses */
static void any_external_price_at_source_negative_million_pair(ExternalPriceAtSourceNegativeMillionPair *record) {
  for (size_t i = 0; i < 7; i++) { record->raw_external_price_at_source[i] = arbitrary(); }
  record->external_price_fraction_indicator = arbitrary();
}

/* External Price At Source Negative Million Pair to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_external_price_at_source_negative_million_pair(const ExternalPriceAtSourceNegativeMillionPair *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->raw_external_price_at_source[i]; }
  wire[at++] = record->external_price_fraction_indicator;

  return at;
}

/* External Price At Source Negative Million Pair off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_external_price_at_source_negative_million_pair(ExternalPriceAtSourceNegativeMillionPair *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { record->raw_external_price_at_source[i] = wire[at++]; }
  record->external_price_fraction_indicator = wire[at++];

  return at;
}

/* what was read of External Price At Source Negative Million Pair is what was written, byte for byte */
static void equal_external_price_at_source_negative_million_pair(const ExternalPriceAtSourceNegativeMillionPair *read, const ExternalPriceAtSourceNegativeMillionPair *written) {
  for (size_t i = 0; i < 7; i++) { assert(read->raw_external_price_at_source[i] == written->raw_external_price_at_source[i]); }
  assert(read->external_price_fraction_indicator == written->external_price_fraction_indicator);
}

/* External Price At Source Negative Million Pair: written and read back, then read and written back */
static void check_external_price_at_source_negative_million_pair(void) {
  ExternalPriceAtSourceNegativeMillionPair sent;
  ExternalPriceAtSourceNegativeMillionPair got;
  uint8_t wire[8];
  uint8_t again[8];

  any_external_price_at_source_negative_million_pair(&sent);
  assert(encode_external_price_at_source_negative_million_pair(&sent, wire, 0) == 8);
  assert(decode_external_price_at_source_negative_million_pair(&got, wire, 0) == 8);
  equal_external_price_at_source_negative_million_pair(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_external_price_at_source_negative_million_pair(&got, wire, 0) == 8);
  assert(encode_external_price_at_source_negative_million_pair(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- External Price At Source Numeric Pair: 8 bytes -------------------------- */

typedef struct {
  uint8_t external_price_at_source[7];        /* bytes 0 to 6 */
  uint8_t external_price_fraction_indicator;  /* byte 7 */
} ExternalPriceAtSourceNumericPair;

/* any External Price At Source Numeric Pair at all: every byte one the checker chooses */
static void any_external_price_at_source_numeric_pair(ExternalPriceAtSourceNumericPair *record) {
  for (size_t i = 0; i < 7; i++) { record->external_price_at_source[i] = arbitrary(); }
  record->external_price_fraction_indicator = arbitrary();
}

/* External Price At Source Numeric Pair to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_external_price_at_source_numeric_pair(const ExternalPriceAtSourceNumericPair *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->external_price_at_source[i]; }
  wire[at++] = record->external_price_fraction_indicator;

  return at;
}

/* External Price At Source Numeric Pair off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_external_price_at_source_numeric_pair(ExternalPriceAtSourceNumericPair *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { record->external_price_at_source[i] = wire[at++]; }
  record->external_price_fraction_indicator = wire[at++];

  return at;
}

/* what was read of External Price At Source Numeric Pair is what was written, byte for byte */
static void equal_external_price_at_source_numeric_pair(const ExternalPriceAtSourceNumericPair *read, const ExternalPriceAtSourceNumericPair *written) {
  for (size_t i = 0; i < 7; i++) { assert(read->external_price_at_source[i] == written->external_price_at_source[i]); }
  assert(read->external_price_fraction_indicator == written->external_price_fraction_indicator);
}

/* External Price At Source Numeric Pair: written and read back, then read and written back */
static void check_external_price_at_source_numeric_pair(void) {
  ExternalPriceAtSourceNumericPair sent;
  ExternalPriceAtSourceNumericPair got;
  uint8_t wire[8];
  uint8_t again[8];

  any_external_price_at_source_numeric_pair(&sent);
  assert(encode_external_price_at_source_numeric_pair(&sent, wire, 0) == 8);
  assert(decode_external_price_at_source_numeric_pair(&got, wire, 0) == 8);
  equal_external_price_at_source_numeric_pair(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_external_price_at_source_numeric_pair(&got, wire, 0) == 8);
  assert(encode_external_price_at_source_numeric_pair(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Beginning Of Options Summary Message: 13 bytes -------------------------- */

/* This message indicates that the beginning and the end of day N: Option Summary messages are to follow. Other messages (such as bulletins) can be interspersed with the summaries. */
typedef struct {
  LongMessageHeader long_message_header;  /* bytes 0 to 11 */
  uint8_t exchange_id;                    /* byte 12 */
} BeginningOfOptionsSummaryMessage;

/* any Beginning Of Options Summary Message at all: every byte one the checker chooses */
static void any_beginning_of_options_summary_message(BeginningOfOptionsSummaryMessage *record) {
  any_long_message_header(&record->long_message_header);
  record->exchange_id = arbitrary();
}

/* Beginning Of Options Summary Message to the wire: 13 bytes from at, returning where the next byte goes */
static size_t encode_beginning_of_options_summary_message(const BeginningOfOptionsSummaryMessage *record, uint8_t *wire, size_t at) {
  at = encode_long_message_header(&record->long_message_header, wire, at);
  wire[at++] = record->exchange_id;

  return at;
}

/* Beginning Of Options Summary Message off the wire: 13 bytes from at, returning where the next byte lies */
static size_t decode_beginning_of_options_summary_message(BeginningOfOptionsSummaryMessage *record, const uint8_t *wire, size_t at) {
  at = decode_long_message_header(&record->long_message_header, wire, at);
  record->exchange_id = wire[at++];

  return at;
}

/* what was read of Beginning Of Options Summary Message is what was written, byte for byte */
static void equal_beginning_of_options_summary_message(const BeginningOfOptionsSummaryMessage *read, const BeginningOfOptionsSummaryMessage *written) {
  equal_long_message_header(&read->long_message_header, &written->long_message_header);
  assert(read->exchange_id == written->exchange_id);
}

/* Beginning Of Options Summary Message: written and read back, then read and written back */
static void check_beginning_of_options_summary_message(void) {
  BeginningOfOptionsSummaryMessage sent;
  BeginningOfOptionsSummaryMessage got;
  uint8_t wire[13];
  uint8_t again[13];

  any_beginning_of_options_summary_message(&sent);
  assert(encode_beginning_of_options_summary_message(&sent, wire, 0) == 13);
  assert(decode_beginning_of_options_summary_message(&got, wire, 0) == 13);
  equal_beginning_of_options_summary_message(&got, &sent);

  for (size_t i = 0; i < 13; i++) { wire[i] = arbitrary(); }
  assert(decode_beginning_of_options_summary_message(&got, wire, 0) == 13);
  assert(encode_beginning_of_options_summary_message(&got, again, 0) == 13);
  for (size_t i = 0; i < 13; i++) { assert(again[i] == wire[i]); }
}

/* ---- Beginning Of Future Options Summary Message: 13 bytes ------------------- */

/* This message indicates that the beginning and the end of day NB: Future Options Summary messages are to follow. Other messages (such as bulletins) can be interspersed with the summaries. */
typedef struct {
  LongMessageHeader long_message_header;  /* bytes 0 to 11 */
  uint8_t exchange_id;                    /* byte 12 */
} BeginningOfFutureOptionsSummaryMessage;

/* any Beginning Of Future Options Summary Message at all: every byte one the checker chooses */
static void any_beginning_of_future_options_summary_message(BeginningOfFutureOptionsSummaryMessage *record) {
  any_long_message_header(&record->long_message_header);
  record->exchange_id = arbitrary();
}

/* Beginning Of Future Options Summary Message to the wire: 13 bytes from at, returning where the next byte goes */
static size_t encode_beginning_of_future_options_summary_message(const BeginningOfFutureOptionsSummaryMessage *record, uint8_t *wire, size_t at) {
  at = encode_long_message_header(&record->long_message_header, wire, at);
  wire[at++] = record->exchange_id;

  return at;
}

/* Beginning Of Future Options Summary Message off the wire: 13 bytes from at, returning where the next byte lies */
static size_t decode_beginning_of_future_options_summary_message(BeginningOfFutureOptionsSummaryMessage *record, const uint8_t *wire, size_t at) {
  at = decode_long_message_header(&record->long_message_header, wire, at);
  record->exchange_id = wire[at++];

  return at;
}

/* what was read of Beginning Of Future Options Summary Message is what was written, byte for byte */
static void equal_beginning_of_future_options_summary_message(const BeginningOfFutureOptionsSummaryMessage *read, const BeginningOfFutureOptionsSummaryMessage *written) {
  equal_long_message_header(&read->long_message_header, &written->long_message_header);
  assert(read->exchange_id == written->exchange_id);
}

/* Beginning Of Future Options Summary Message: written and read back, then read and written back */
static void check_beginning_of_future_options_summary_message(void) {
  BeginningOfFutureOptionsSummaryMessage sent;
  BeginningOfFutureOptionsSummaryMessage got;
  uint8_t wire[13];
  uint8_t again[13];

  any_beginning_of_future_options_summary_message(&sent);
  assert(encode_beginning_of_future_options_summary_message(&sent, wire, 0) == 13);
  assert(decode_beginning_of_future_options_summary_message(&got, wire, 0) == 13);
  equal_beginning_of_future_options_summary_message(&got, &sent);

  for (size_t i = 0; i < 13; i++) { wire[i] = arbitrary(); }
  assert(decode_beginning_of_future_options_summary_message(&got, wire, 0) == 13);
  assert(encode_beginning_of_future_options_summary_message(&got, again, 0) == 13);
  for (size_t i = 0; i < 13; i++) { assert(again[i] == wire[i]); }
}

/* ---- Beginning Of Futures Summary Message: 13 bytes -------------------------- */

/* This message indicates that the beginning or end-of-day NF: Future Summary messages are to follow. Other messages can be interspersed with the summaries. */
typedef struct {
  LongMessageHeader long_message_header;  /* bytes 0 to 11 */
  uint8_t exchange_id;                    /* byte 12 */
} BeginningOfFuturesSummaryMessage;

/* any Beginning Of Futures Summary Message at all: every byte one the checker chooses */
static void any_beginning_of_futures_summary_message(BeginningOfFuturesSummaryMessage *record) {
  any_long_message_header(&record->long_message_header);
  record->exchange_id = arbitrary();
}

/* Beginning Of Futures Summary Message to the wire: 13 bytes from at, returning where the next byte goes */
static size_t encode_beginning_of_futures_summary_message(const BeginningOfFuturesSummaryMessage *record, uint8_t *wire, size_t at) {
  at = encode_long_message_header(&record->long_message_header, wire, at);
  wire[at++] = record->exchange_id;

  return at;
}

/* Beginning Of Futures Summary Message off the wire: 13 bytes from at, returning where the next byte lies */
static size_t decode_beginning_of_futures_summary_message(BeginningOfFuturesSummaryMessage *record, const uint8_t *wire, size_t at) {
  at = decode_long_message_header(&record->long_message_header, wire, at);
  record->exchange_id = wire[at++];

  return at;
}

/* what was read of Beginning Of Futures Summary Message is what was written, byte for byte */
static void equal_beginning_of_futures_summary_message(const BeginningOfFuturesSummaryMessage *read, const BeginningOfFuturesSummaryMessage *written) {
  equal_long_message_header(&read->long_message_header, &written->long_message_header);
  assert(read->exchange_id == written->exchange_id);
}

/* Beginning Of Futures Summary Message: written and read back, then read and written back */
static void check_beginning_of_futures_summary_message(void) {
  BeginningOfFuturesSummaryMessage sent;
  BeginningOfFuturesSummaryMessage got;
  uint8_t wire[13];
  uint8_t again[13];

  any_beginning_of_futures_summary_message(&sent);
  assert(encode_beginning_of_futures_summary_message(&sent, wire, 0) == 13);
  assert(decode_beginning_of_futures_summary_message(&got, wire, 0) == 13);
  equal_beginning_of_futures_summary_message(&got, &sent);

  for (size_t i = 0; i < 13; i++) { wire[i] = arbitrary(); }
  assert(decode_beginning_of_futures_summary_message(&got, wire, 0) == 13);
  assert(encode_beginning_of_futures_summary_message(&got, again, 0) == 13);
  for (size_t i = 0; i < 13; i++) { assert(again[i] == wire[i]); }
}

/* ---- Beginning Of Strategy Summary Message: 13 bytes ------------------------- */

/* This message indicates that the beginning or the end of day NS: Strategy Summary messages are to follow. Other messages can be interspersed with the summaries. */
typedef struct {
  LongMessageHeader long_message_header;  /* bytes 0 to 11 */
  uint8_t exchange_id;                    /* byte 12 */
} BeginningOfStrategySummaryMessage;

/* any Beginning Of Strategy Summary Message at all: every byte one the checker chooses */
static void any_beginning_of_strategy_summary_message(BeginningOfStrategySummaryMessage *record) {
  any_long_message_header(&record->long_message_header);
  record->exchange_id = arbitrary();
}

/* Beginning Of Strategy Summary Message to the wire: 13 bytes from at, returning where the next byte goes */
static size_t encode_beginning_of_strategy_summary_message(const BeginningOfStrategySummaryMessage *record, uint8_t *wire, size_t at) {
  at = encode_long_message_header(&record->long_message_header, wire, at);
  wire[at++] = record->exchange_id;

  return at;
}

/* Beginning Of Strategy Summary Message off the wire: 13 bytes from at, returning where the next byte lies */
static size_t decode_beginning_of_strategy_summary_message(BeginningOfStrategySummaryMessage *record, const uint8_t *wire, size_t at) {
  at = decode_long_message_header(&record->long_message_header, wire, at);
  record->exchange_id = wire[at++];

  return at;
}

/* what was read of Beginning Of Strategy Summary Message is what was written, byte for byte */
static void equal_beginning_of_strategy_summary_message(const BeginningOfStrategySummaryMessage *read, const BeginningOfStrategySummaryMessage *written) {
  equal_long_message_header(&read->long_message_header, &written->long_message_header);
  assert(read->exchange_id == written->exchange_id);
}

/* Beginning Of Strategy Summary Message: written and read back, then read and written back */
static void check_beginning_of_strategy_summary_message(void) {
  BeginningOfStrategySummaryMessage sent;
  BeginningOfStrategySummaryMessage got;
  uint8_t wire[13];
  uint8_t again[13];

  any_beginning_of_strategy_summary_message(&sent);
  assert(encode_beginning_of_strategy_summary_message(&sent, wire, 0) == 13);
  assert(decode_beginning_of_strategy_summary_message(&got, wire, 0) == 13);
  equal_beginning_of_strategy_summary_message(&got, &sent);

  for (size_t i = 0; i < 13; i++) { wire[i] = arbitrary(); }
  assert(decode_beginning_of_strategy_summary_message(&got, wire, 0) == 13);
  assert(encode_beginning_of_strategy_summary_message(&got, again, 0) == 13);
  for (size_t i = 0; i < 13; i++) { assert(again[i] == wire[i]); }
}

/* ---- Group Status Message: 20 bytes ------------------------------------------ */

/* This message will be sent when a group of trading instruments enters a new status. */
typedef struct {
  LongMessageHeader long_message_header;  /* bytes 0 to 11 */
  uint8_t exchange_id;                    /* byte 12 */
  uint8_t root_symbol_group[6];           /* bytes 13 to 18 */
  uint8_t group_status;                   /* byte 19 */
} GroupStatusMessage;

/* any Group Status Message at all: every byte one the checker chooses */
static void any_group_status_message(GroupStatusMessage *record) {
  any_long_message_header(&record->long_message_header);
  record->exchange_id = arbitrary();
  for (size_t i = 0; i < 6; i++) { record->root_symbol_group[i] = arbitrary(); }
  record->group_status = arbitrary();
}

/* Group Status Message to the wire: 20 bytes from at, returning where the next byte goes */
static size_t encode_group_status_message(const GroupStatusMessage *record, uint8_t *wire, size_t at) {
  at = encode_long_message_header(&record->long_message_header, wire, at);
  wire[at++] = record->exchange_id;
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->root_symbol_group[i]; }
  wire[at++] = record->group_status;

  return at;
}

/* Group Status Message off the wire: 20 bytes from at, returning where the next byte lies */
static size_t decode_group_status_message(GroupStatusMessage *record, const uint8_t *wire, size_t at) {
  at = decode_long_message_header(&record->long_message_header, wire, at);
  record->exchange_id = wire[at++];
  for (size_t i = 0; i < 6; i++) { record->root_symbol_group[i] = wire[at++]; }
  record->group_status = wire[at++];

  return at;
}

/* what was read of Group Status Message is what was written, byte for byte */
static void equal_group_status_message(const GroupStatusMessage *read, const GroupStatusMessage *written) {
  equal_long_message_header(&read->long_message_header, &written->long_message_header);
  assert(read->exchange_id == written->exchange_id);
  for (size_t i = 0; i < 6; i++) { assert(read->root_symbol_group[i] == written->root_symbol_group[i]); }
  assert(read->group_status == written->group_status);
}

/* Group Status Message: written and read back, then read and written back */
static void check_group_status_message(void) {
  GroupStatusMessage sent;
  GroupStatusMessage got;
  uint8_t wire[20];
  uint8_t again[20];

  any_group_status_message(&sent);
  assert(encode_group_status_message(&sent, wire, 0) == 20);
  assert(decode_group_status_message(&got, wire, 0) == 20);
  equal_group_status_message(&got, &sent);

  for (size_t i = 0; i < 20; i++) { wire[i] = arbitrary(); }
  assert(decode_group_status_message(&got, wire, 0) == 20);
  assert(encode_group_status_message(&got, again, 0) == 20);
  for (size_t i = 0; i < 20; i++) { assert(again[i] == wire[i]); }
}

/* ---- Group Status Strategies Message: 16 bytes ------------------------------- */

/* This message will be sent when a strategy group of trading instruments enters a new status. All strategies have a predetermined group that can be found in the JS: Strategy Instrument Keys message. */
typedef struct {
  LongMessageHeader long_message_header;  /* bytes 0 to 11 */
  uint8_t exchange_id;                    /* byte 12 */
  uint8_t group_instrument[2];            /* bytes 13 to 14 */
  uint8_t group_status;                   /* byte 15 */
} GroupStatusStrategiesMessage;

/* any Group Status Strategies Message at all: every byte one the checker chooses */
static void any_group_status_strategies_message(GroupStatusStrategiesMessage *record) {
  any_long_message_header(&record->long_message_header);
  record->exchange_id = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->group_instrument[i] = arbitrary(); }
  record->group_status = arbitrary();
}

/* Group Status Strategies Message to the wire: 16 bytes from at, returning where the next byte goes */
static size_t encode_group_status_strategies_message(const GroupStatusStrategiesMessage *record, uint8_t *wire, size_t at) {
  at = encode_long_message_header(&record->long_message_header, wire, at);
  wire[at++] = record->exchange_id;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->group_instrument[i]; }
  wire[at++] = record->group_status;

  return at;
}

/* Group Status Strategies Message off the wire: 16 bytes from at, returning where the next byte lies */
static size_t decode_group_status_strategies_message(GroupStatusStrategiesMessage *record, const uint8_t *wire, size_t at) {
  at = decode_long_message_header(&record->long_message_header, wire, at);
  record->exchange_id = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->group_instrument[i] = wire[at++]; }
  record->group_status = wire[at++];

  return at;
}

/* what was read of Group Status Strategies Message is what was written, byte for byte */
static void equal_group_status_strategies_message(const GroupStatusStrategiesMessage *read, const GroupStatusStrategiesMessage *written) {
  equal_long_message_header(&read->long_message_header, &written->long_message_header);
  assert(read->exchange_id == written->exchange_id);
  for (size_t i = 0; i < 2; i++) { assert(read->group_instrument[i] == written->group_instrument[i]); }
  assert(read->group_status == written->group_status);
}

/* Group Status Strategies Message: written and read back, then read and written back */
static void check_group_status_strategies_message(void) {
  GroupStatusStrategiesMessage sent;
  GroupStatusStrategiesMessage got;
  uint8_t wire[16];
  uint8_t again[16];

  any_group_status_strategies_message(&sent);
  assert(encode_group_status_strategies_message(&sent, wire, 0) == 16);
  assert(decode_group_status_strategies_message(&got, wire, 0) == 16);
  equal_group_status_strategies_message(&got, &sent);

  for (size_t i = 0; i < 16; i++) { wire[i] = arbitrary(); }
  assert(decode_group_status_strategies_message(&got, wire, 0) == 16);
  assert(encode_group_status_strategies_message(&got, again, 0) == 16);
  for (size_t i = 0; i < 16; i++) { assert(again[i] == wire[i]); }
}

/* ---- Regular Text Bulletin: 80 bytes ----------------------------------------- */

/* Bulletin Type 1, which the Bulletin Type field selects. */
typedef struct {
  uint8_t regular_bulletin_contents[79];  /* bytes 0 to 78 */
  uint8_t continue_marker;                /* byte 79 */
} RegularTextBulletin;

/* any Regular Text Bulletin at all: every byte one the checker chooses */
static void any_regular_text_bulletin(RegularTextBulletin *record) {
  for (size_t i = 0; i < 79; i++) { record->regular_bulletin_contents[i] = arbitrary(); }
  record->continue_marker = arbitrary();
}

/* Regular Text Bulletin to the wire: 80 bytes from at, returning where the next byte goes */
static size_t encode_regular_text_bulletin(const RegularTextBulletin *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 79; i++) { wire[at++] = record->regular_bulletin_contents[i]; }
  wire[at++] = record->continue_marker;

  return at;
}

/* Regular Text Bulletin off the wire: 80 bytes from at, returning where the next byte lies */
static size_t decode_regular_text_bulletin(RegularTextBulletin *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 79; i++) { record->regular_bulletin_contents[i] = wire[at++]; }
  record->continue_marker = wire[at++];

  return at;
}

/* what was read of Regular Text Bulletin is what was written, byte for byte */
static void equal_regular_text_bulletin(const RegularTextBulletin *read, const RegularTextBulletin *written) {
  for (size_t i = 0; i < 79; i++) { assert(read->regular_bulletin_contents[i] == written->regular_bulletin_contents[i]); }
  assert(read->continue_marker == written->continue_marker);
}

/* Regular Text Bulletin: written and read back, then read and written back */
static void check_regular_text_bulletin(void) {
  RegularTextBulletin sent;
  RegularTextBulletin got;
  uint8_t wire[80];
  uint8_t again[80];

  any_regular_text_bulletin(&sent);
  assert(encode_regular_text_bulletin(&sent, wire, 0) == 80);
  assert(decode_regular_text_bulletin(&got, wire, 0) == 80);
  equal_regular_text_bulletin(&got, &sent);

  for (size_t i = 0; i < 80; i++) { wire[i] = arbitrary(); }
  assert(decode_regular_text_bulletin(&got, wire, 0) == 80);
  assert(encode_regular_text_bulletin(&got, again, 0) == 80);
  for (size_t i = 0; i < 80; i++) { assert(again[i] == wire[i]); }
}

/* ---- Special Text Bulletin: 80 bytes ----------------------------------------- */

/* This bulletin type will be used for bulletins relating to a specific trading instrument. */
typedef struct {
  uint8_t symbol[30];                     /* bytes 0 to 29 */
  uint8_t special_bulletin_contents[49];  /* bytes 30 to 78 */
  uint8_t continue_marker;                /* byte 79 */
} SpecialTextBulletin;

/* any Special Text Bulletin at all: every byte one the checker chooses */
static void any_special_text_bulletin(SpecialTextBulletin *record) {
  for (size_t i = 0; i < 30; i++) { record->symbol[i] = arbitrary(); }
  for (size_t i = 0; i < 49; i++) { record->special_bulletin_contents[i] = arbitrary(); }
  record->continue_marker = arbitrary();
}

/* Special Text Bulletin to the wire: 80 bytes from at, returning where the next byte goes */
static size_t encode_special_text_bulletin(const SpecialTextBulletin *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 30; i++) { wire[at++] = record->symbol[i]; }
  for (size_t i = 0; i < 49; i++) { wire[at++] = record->special_bulletin_contents[i]; }
  wire[at++] = record->continue_marker;

  return at;
}

/* Special Text Bulletin off the wire: 80 bytes from at, returning where the next byte lies */
static size_t decode_special_text_bulletin(SpecialTextBulletin *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 30; i++) { record->symbol[i] = wire[at++]; }
  for (size_t i = 0; i < 49; i++) { record->special_bulletin_contents[i] = wire[at++]; }
  record->continue_marker = wire[at++];

  return at;
}

/* what was read of Special Text Bulletin is what was written, byte for byte */
static void equal_special_text_bulletin(const SpecialTextBulletin *read, const SpecialTextBulletin *written) {
  for (size_t i = 0; i < 30; i++) { assert(read->symbol[i] == written->symbol[i]); }
  for (size_t i = 0; i < 49; i++) { assert(read->special_bulletin_contents[i] == written->special_bulletin_contents[i]); }
  assert(read->continue_marker == written->continue_marker);
}

/* Special Text Bulletin: written and read back, then read and written back */
static void check_special_text_bulletin(void) {
  SpecialTextBulletin sent;
  SpecialTextBulletin got;
  uint8_t wire[80];
  uint8_t again[80];

  any_special_text_bulletin(&sent);
  assert(encode_special_text_bulletin(&sent, wire, 0) == 80);
  assert(decode_special_text_bulletin(&got, wire, 0) == 80);
  equal_special_text_bulletin(&got, &sent);

  for (size_t i = 0; i < 80; i++) { wire[i] = arbitrary(); }
  assert(decode_special_text_bulletin(&got, wire, 0) == 80);
  assert(encode_special_text_bulletin(&got, again, 0) == 80);
  for (size_t i = 0; i < 80; i++) { assert(again[i] == wire[i]); }
}

/* ---- End Of Sales Message: 19 bytes ------------------------------------------ */

/* The S: End of Sales message is sent when there is no more trading activity to be transmitted. This occurs after the closing of the market. */
typedef struct {
  LongMessageHeader long_message_header;  /* bytes 0 to 11 */
  uint8_t reserved;                       /* byte 12 */
  uint8_t time[6];                        /* bytes 13 to 18 */
} EndOfSalesMessage;

/* any End Of Sales Message at all: every byte one the checker chooses */
static void any_end_of_sales_message(EndOfSalesMessage *record) {
  any_long_message_header(&record->long_message_header);
  record->reserved = arbitrary();
  for (size_t i = 0; i < 6; i++) { record->time[i] = arbitrary(); }
}

/* End Of Sales Message to the wire: 19 bytes from at, returning where the next byte goes */
static size_t encode_end_of_sales_message(const EndOfSalesMessage *record, uint8_t *wire, size_t at) {
  at = encode_long_message_header(&record->long_message_header, wire, at);
  wire[at++] = record->reserved;
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->time[i]; }

  return at;
}

/* End Of Sales Message off the wire: 19 bytes from at, returning where the next byte lies */
static size_t decode_end_of_sales_message(EndOfSalesMessage *record, const uint8_t *wire, size_t at) {
  at = decode_long_message_header(&record->long_message_header, wire, at);
  record->reserved = wire[at++];
  for (size_t i = 0; i < 6; i++) { record->time[i] = wire[at++]; }

  return at;
}

/* what was read of End Of Sales Message is what was written, byte for byte */
static void equal_end_of_sales_message(const EndOfSalesMessage *read, const EndOfSalesMessage *written) {
  equal_long_message_header(&read->long_message_header, &written->long_message_header);
  assert(read->reserved == written->reserved);
  for (size_t i = 0; i < 6; i++) { assert(read->time[i] == written->time[i]); }
}

/* End Of Sales Message: written and read back, then read and written back */
static void check_end_of_sales_message(void) {
  EndOfSalesMessage sent;
  EndOfSalesMessage got;
  uint8_t wire[19];
  uint8_t again[19];

  any_end_of_sales_message(&sent);
  assert(encode_end_of_sales_message(&sent, wire, 0) == 19);
  assert(decode_end_of_sales_message(&got, wire, 0) == 19);
  equal_end_of_sales_message(&got, &sent);

  for (size_t i = 0; i < 19; i++) { wire[i] = arbitrary(); }
  assert(decode_end_of_sales_message(&got, wire, 0) == 19);
  assert(encode_end_of_sales_message(&got, again, 0) == 19);
  for (size_t i = 0; i < 19; i++) { assert(again[i] == wire[i]); }
}

/* ---- Min Price Negative Whole Pair: 8 bytes ---------------------------------- */

typedef struct {
  uint8_t raw_min_price[7];              /* bytes 0 to 6 */
  uint8_t min_price_fraction_indicator;  /* byte 7 */
} MinPriceNegativeWholePair;

/* any Min Price Negative Whole Pair at all: every byte one the checker chooses */
static void any_min_price_negative_whole_pair(MinPriceNegativeWholePair *record) {
  for (size_t i = 0; i < 7; i++) { record->raw_min_price[i] = arbitrary(); }
  record->min_price_fraction_indicator = arbitrary();
}

/* Min Price Negative Whole Pair to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_min_price_negative_whole_pair(const MinPriceNegativeWholePair *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->raw_min_price[i]; }
  wire[at++] = record->min_price_fraction_indicator;

  return at;
}

/* Min Price Negative Whole Pair off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_min_price_negative_whole_pair(MinPriceNegativeWholePair *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { record->raw_min_price[i] = wire[at++]; }
  record->min_price_fraction_indicator = wire[at++];

  return at;
}

/* what was read of Min Price Negative Whole Pair is what was written, byte for byte */
static void equal_min_price_negative_whole_pair(const MinPriceNegativeWholePair *read, const MinPriceNegativeWholePair *written) {
  for (size_t i = 0; i < 7; i++) { assert(read->raw_min_price[i] == written->raw_min_price[i]); }
  assert(read->min_price_fraction_indicator == written->min_price_fraction_indicator);
}

/* Min Price Negative Whole Pair: written and read back, then read and written back */
static void check_min_price_negative_whole_pair(void) {
  MinPriceNegativeWholePair sent;
  MinPriceNegativeWholePair got;
  uint8_t wire[8];
  uint8_t again[8];

  any_min_price_negative_whole_pair(&sent);
  assert(encode_min_price_negative_whole_pair(&sent, wire, 0) == 8);
  assert(decode_min_price_negative_whole_pair(&got, wire, 0) == 8);
  equal_min_price_negative_whole_pair(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_min_price_negative_whole_pair(&got, wire, 0) == 8);
  assert(encode_min_price_negative_whole_pair(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Min Price Negative Ten Pair: 8 bytes ------------------------------------ */

typedef struct {
  uint8_t raw_min_price[7];              /* bytes 0 to 6 */
  uint8_t min_price_fraction_indicator;  /* byte 7 */
} MinPriceNegativeTenPair;

/* any Min Price Negative Ten Pair at all: every byte one the checker chooses */
static void any_min_price_negative_ten_pair(MinPriceNegativeTenPair *record) {
  for (size_t i = 0; i < 7; i++) { record->raw_min_price[i] = arbitrary(); }
  record->min_price_fraction_indicator = arbitrary();
}

/* Min Price Negative Ten Pair to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_min_price_negative_ten_pair(const MinPriceNegativeTenPair *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->raw_min_price[i]; }
  wire[at++] = record->min_price_fraction_indicator;

  return at;
}

/* Min Price Negative Ten Pair off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_min_price_negative_ten_pair(MinPriceNegativeTenPair *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { record->raw_min_price[i] = wire[at++]; }
  record->min_price_fraction_indicator = wire[at++];

  return at;
}

/* what was read of Min Price Negative Ten Pair is what was written, byte for byte */
static void equal_min_price_negative_ten_pair(const MinPriceNegativeTenPair *read, const MinPriceNegativeTenPair *written) {
  for (size_t i = 0; i < 7; i++) { assert(read->raw_min_price[i] == written->raw_min_price[i]); }
  assert(read->min_price_fraction_indicator == written->min_price_fraction_indicator);
}

/* Min Price Negative Ten Pair: written and read back, then read and written back */
static void check_min_price_negative_ten_pair(void) {
  MinPriceNegativeTenPair sent;
  MinPriceNegativeTenPair got;
  uint8_t wire[8];
  uint8_t again[8];

  any_min_price_negative_ten_pair(&sent);
  assert(encode_min_price_negative_ten_pair(&sent, wire, 0) == 8);
  assert(decode_min_price_negative_ten_pair(&got, wire, 0) == 8);
  equal_min_price_negative_ten_pair(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_min_price_negative_ten_pair(&got, wire, 0) == 8);
  assert(encode_min_price_negative_ten_pair(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Min Price Negative Hundred Pair: 8 bytes -------------------------------- */

typedef struct {
  uint8_t raw_min_price[7];              /* bytes 0 to 6 */
  uint8_t min_price_fraction_indicator;  /* byte 7 */
} MinPriceNegativeHundredPair;

/* any Min Price Negative Hundred Pair at all: every byte one the checker chooses */
static void any_min_price_negative_hundred_pair(MinPriceNegativeHundredPair *record) {
  for (size_t i = 0; i < 7; i++) { record->raw_min_price[i] = arbitrary(); }
  record->min_price_fraction_indicator = arbitrary();
}

/* Min Price Negative Hundred Pair to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_min_price_negative_hundred_pair(const MinPriceNegativeHundredPair *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->raw_min_price[i]; }
  wire[at++] = record->min_price_fraction_indicator;

  return at;
}

/* Min Price Negative Hundred Pair off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_min_price_negative_hundred_pair(MinPriceNegativeHundredPair *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { record->raw_min_price[i] = wire[at++]; }
  record->min_price_fraction_indicator = wire[at++];

  return at;
}

/* what was read of Min Price Negative Hundred Pair is what was written, byte for byte */
static void equal_min_price_negative_hundred_pair(const MinPriceNegativeHundredPair *read, const MinPriceNegativeHundredPair *written) {
  for (size_t i = 0; i < 7; i++) { assert(read->raw_min_price[i] == written->raw_min_price[i]); }
  assert(read->min_price_fraction_indicator == written->min_price_fraction_indicator);
}

/* Min Price Negative Hundred Pair: written and read back, then read and written back */
static void check_min_price_negative_hundred_pair(void) {
  MinPriceNegativeHundredPair sent;
  MinPriceNegativeHundredPair got;
  uint8_t wire[8];
  uint8_t again[8];

  any_min_price_negative_hundred_pair(&sent);
  assert(encode_min_price_negative_hundred_pair(&sent, wire, 0) == 8);
  assert(decode_min_price_negative_hundred_pair(&got, wire, 0) == 8);
  equal_min_price_negative_hundred_pair(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_min_price_negative_hundred_pair(&got, wire, 0) == 8);
  assert(encode_min_price_negative_hundred_pair(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Min Price Negative Thousand Pair: 8 bytes ------------------------------- */

typedef struct {
  uint8_t raw_min_price[7];              /* bytes 0 to 6 */
  uint8_t min_price_fraction_indicator;  /* byte 7 */
} MinPriceNegativeThousandPair;

/* any Min Price Negative Thousand Pair at all: every byte one the checker chooses */
static void any_min_price_negative_thousand_pair(MinPriceNegativeThousandPair *record) {
  for (size_t i = 0; i < 7; i++) { record->raw_min_price[i] = arbitrary(); }
  record->min_price_fraction_indicator = arbitrary();
}

/* Min Price Negative Thousand Pair to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_min_price_negative_thousand_pair(const MinPriceNegativeThousandPair *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->raw_min_price[i]; }
  wire[at++] = record->min_price_fraction_indicator;

  return at;
}

/* Min Price Negative Thousand Pair off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_min_price_negative_thousand_pair(MinPriceNegativeThousandPair *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { record->raw_min_price[i] = wire[at++]; }
  record->min_price_fraction_indicator = wire[at++];

  return at;
}

/* what was read of Min Price Negative Thousand Pair is what was written, byte for byte */
static void equal_min_price_negative_thousand_pair(const MinPriceNegativeThousandPair *read, const MinPriceNegativeThousandPair *written) {
  for (size_t i = 0; i < 7; i++) { assert(read->raw_min_price[i] == written->raw_min_price[i]); }
  assert(read->min_price_fraction_indicator == written->min_price_fraction_indicator);
}

/* Min Price Negative Thousand Pair: written and read back, then read and written back */
static void check_min_price_negative_thousand_pair(void) {
  MinPriceNegativeThousandPair sent;
  MinPriceNegativeThousandPair got;
  uint8_t wire[8];
  uint8_t again[8];

  any_min_price_negative_thousand_pair(&sent);
  assert(encode_min_price_negative_thousand_pair(&sent, wire, 0) == 8);
  assert(decode_min_price_negative_thousand_pair(&got, wire, 0) == 8);
  equal_min_price_negative_thousand_pair(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_min_price_negative_thousand_pair(&got, wire, 0) == 8);
  assert(encode_min_price_negative_thousand_pair(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Min Price Negative Ten Thousand Pair: 8 bytes --------------------------- */

typedef struct {
  uint8_t raw_min_price[7];              /* bytes 0 to 6 */
  uint8_t min_price_fraction_indicator;  /* byte 7 */
} MinPriceNegativeTenThousandPair;

/* any Min Price Negative Ten Thousand Pair at all: every byte one the checker chooses */
static void any_min_price_negative_ten_thousand_pair(MinPriceNegativeTenThousandPair *record) {
  for (size_t i = 0; i < 7; i++) { record->raw_min_price[i] = arbitrary(); }
  record->min_price_fraction_indicator = arbitrary();
}

/* Min Price Negative Ten Thousand Pair to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_min_price_negative_ten_thousand_pair(const MinPriceNegativeTenThousandPair *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->raw_min_price[i]; }
  wire[at++] = record->min_price_fraction_indicator;

  return at;
}

/* Min Price Negative Ten Thousand Pair off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_min_price_negative_ten_thousand_pair(MinPriceNegativeTenThousandPair *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { record->raw_min_price[i] = wire[at++]; }
  record->min_price_fraction_indicator = wire[at++];

  return at;
}

/* what was read of Min Price Negative Ten Thousand Pair is what was written, byte for byte */
static void equal_min_price_negative_ten_thousand_pair(const MinPriceNegativeTenThousandPair *read, const MinPriceNegativeTenThousandPair *written) {
  for (size_t i = 0; i < 7; i++) { assert(read->raw_min_price[i] == written->raw_min_price[i]); }
  assert(read->min_price_fraction_indicator == written->min_price_fraction_indicator);
}

/* Min Price Negative Ten Thousand Pair: written and read back, then read and written back */
static void check_min_price_negative_ten_thousand_pair(void) {
  MinPriceNegativeTenThousandPair sent;
  MinPriceNegativeTenThousandPair got;
  uint8_t wire[8];
  uint8_t again[8];

  any_min_price_negative_ten_thousand_pair(&sent);
  assert(encode_min_price_negative_ten_thousand_pair(&sent, wire, 0) == 8);
  assert(decode_min_price_negative_ten_thousand_pair(&got, wire, 0) == 8);
  equal_min_price_negative_ten_thousand_pair(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_min_price_negative_ten_thousand_pair(&got, wire, 0) == 8);
  assert(encode_min_price_negative_ten_thousand_pair(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Min Price Negative Hundred Thousand Pair: 8 bytes ----------------------- */

typedef struct {
  uint8_t raw_min_price[7];              /* bytes 0 to 6 */
  uint8_t min_price_fraction_indicator;  /* byte 7 */
} MinPriceNegativeHundredThousandPair;

/* any Min Price Negative Hundred Thousand Pair at all: every byte one the checker chooses */
static void any_min_price_negative_hundred_thousand_pair(MinPriceNegativeHundredThousandPair *record) {
  for (size_t i = 0; i < 7; i++) { record->raw_min_price[i] = arbitrary(); }
  record->min_price_fraction_indicator = arbitrary();
}

/* Min Price Negative Hundred Thousand Pair to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_min_price_negative_hundred_thousand_pair(const MinPriceNegativeHundredThousandPair *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->raw_min_price[i]; }
  wire[at++] = record->min_price_fraction_indicator;

  return at;
}

/* Min Price Negative Hundred Thousand Pair off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_min_price_negative_hundred_thousand_pair(MinPriceNegativeHundredThousandPair *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { record->raw_min_price[i] = wire[at++]; }
  record->min_price_fraction_indicator = wire[at++];

  return at;
}

/* what was read of Min Price Negative Hundred Thousand Pair is what was written, byte for byte */
static void equal_min_price_negative_hundred_thousand_pair(const MinPriceNegativeHundredThousandPair *read, const MinPriceNegativeHundredThousandPair *written) {
  for (size_t i = 0; i < 7; i++) { assert(read->raw_min_price[i] == written->raw_min_price[i]); }
  assert(read->min_price_fraction_indicator == written->min_price_fraction_indicator);
}

/* Min Price Negative Hundred Thousand Pair: written and read back, then read and written back */
static void check_min_price_negative_hundred_thousand_pair(void) {
  MinPriceNegativeHundredThousandPair sent;
  MinPriceNegativeHundredThousandPair got;
  uint8_t wire[8];
  uint8_t again[8];

  any_min_price_negative_hundred_thousand_pair(&sent);
  assert(encode_min_price_negative_hundred_thousand_pair(&sent, wire, 0) == 8);
  assert(decode_min_price_negative_hundred_thousand_pair(&got, wire, 0) == 8);
  equal_min_price_negative_hundred_thousand_pair(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_min_price_negative_hundred_thousand_pair(&got, wire, 0) == 8);
  assert(encode_min_price_negative_hundred_thousand_pair(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Min Price Negative Million Pair: 8 bytes -------------------------------- */

typedef struct {
  uint8_t raw_min_price[7];              /* bytes 0 to 6 */
  uint8_t min_price_fraction_indicator;  /* byte 7 */
} MinPriceNegativeMillionPair;

/* any Min Price Negative Million Pair at all: every byte one the checker chooses */
static void any_min_price_negative_million_pair(MinPriceNegativeMillionPair *record) {
  for (size_t i = 0; i < 7; i++) { record->raw_min_price[i] = arbitrary(); }
  record->min_price_fraction_indicator = arbitrary();
}

/* Min Price Negative Million Pair to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_min_price_negative_million_pair(const MinPriceNegativeMillionPair *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->raw_min_price[i]; }
  wire[at++] = record->min_price_fraction_indicator;

  return at;
}

/* Min Price Negative Million Pair off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_min_price_negative_million_pair(MinPriceNegativeMillionPair *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { record->raw_min_price[i] = wire[at++]; }
  record->min_price_fraction_indicator = wire[at++];

  return at;
}

/* what was read of Min Price Negative Million Pair is what was written, byte for byte */
static void equal_min_price_negative_million_pair(const MinPriceNegativeMillionPair *read, const MinPriceNegativeMillionPair *written) {
  for (size_t i = 0; i < 7; i++) { assert(read->raw_min_price[i] == written->raw_min_price[i]); }
  assert(read->min_price_fraction_indicator == written->min_price_fraction_indicator);
}

/* Min Price Negative Million Pair: written and read back, then read and written back */
static void check_min_price_negative_million_pair(void) {
  MinPriceNegativeMillionPair sent;
  MinPriceNegativeMillionPair got;
  uint8_t wire[8];
  uint8_t again[8];

  any_min_price_negative_million_pair(&sent);
  assert(encode_min_price_negative_million_pair(&sent, wire, 0) == 8);
  assert(decode_min_price_negative_million_pair(&got, wire, 0) == 8);
  equal_min_price_negative_million_pair(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_min_price_negative_million_pair(&got, wire, 0) == 8);
  assert(encode_min_price_negative_million_pair(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Min Price Numeric Pair: 8 bytes ----------------------------------------- */

typedef struct {
  uint8_t min_price[7];                  /* bytes 0 to 6 */
  uint8_t min_price_fraction_indicator;  /* byte 7 */
} MinPriceNumericPair;

/* any Min Price Numeric Pair at all: every byte one the checker chooses */
static void any_min_price_numeric_pair(MinPriceNumericPair *record) {
  for (size_t i = 0; i < 7; i++) { record->min_price[i] = arbitrary(); }
  record->min_price_fraction_indicator = arbitrary();
}

/* Min Price Numeric Pair to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_min_price_numeric_pair(const MinPriceNumericPair *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->min_price[i]; }
  wire[at++] = record->min_price_fraction_indicator;

  return at;
}

/* Min Price Numeric Pair off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_min_price_numeric_pair(MinPriceNumericPair *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { record->min_price[i] = wire[at++]; }
  record->min_price_fraction_indicator = wire[at++];

  return at;
}

/* what was read of Min Price Numeric Pair is what was written, byte for byte */
static void equal_min_price_numeric_pair(const MinPriceNumericPair *read, const MinPriceNumericPair *written) {
  for (size_t i = 0; i < 7; i++) { assert(read->min_price[i] == written->min_price[i]); }
  assert(read->min_price_fraction_indicator == written->min_price_fraction_indicator);
}

/* Min Price Numeric Pair: written and read back, then read and written back */
static void check_min_price_numeric_pair(void) {
  MinPriceNumericPair sent;
  MinPriceNumericPair got;
  uint8_t wire[8];
  uint8_t again[8];

  any_min_price_numeric_pair(&sent);
  assert(encode_min_price_numeric_pair(&sent, wire, 0) == 8);
  assert(decode_min_price_numeric_pair(&got, wire, 0) == 8);
  equal_min_price_numeric_pair(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_min_price_numeric_pair(&got, wire, 0) == 8);
  assert(encode_min_price_numeric_pair(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Tick Price Negative Whole Pair: 8 bytes --------------------------------- */

typedef struct {
  uint8_t raw_tick_price[7];              /* bytes 0 to 6 */
  uint8_t tick_price_fraction_indicator;  /* byte 7 */
} TickPriceNegativeWholePair;

/* any Tick Price Negative Whole Pair at all: every byte one the checker chooses */
static void any_tick_price_negative_whole_pair(TickPriceNegativeWholePair *record) {
  for (size_t i = 0; i < 7; i++) { record->raw_tick_price[i] = arbitrary(); }
  record->tick_price_fraction_indicator = arbitrary();
}

/* Tick Price Negative Whole Pair to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_tick_price_negative_whole_pair(const TickPriceNegativeWholePair *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->raw_tick_price[i]; }
  wire[at++] = record->tick_price_fraction_indicator;

  return at;
}

/* Tick Price Negative Whole Pair off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_tick_price_negative_whole_pair(TickPriceNegativeWholePair *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { record->raw_tick_price[i] = wire[at++]; }
  record->tick_price_fraction_indicator = wire[at++];

  return at;
}

/* what was read of Tick Price Negative Whole Pair is what was written, byte for byte */
static void equal_tick_price_negative_whole_pair(const TickPriceNegativeWholePair *read, const TickPriceNegativeWholePair *written) {
  for (size_t i = 0; i < 7; i++) { assert(read->raw_tick_price[i] == written->raw_tick_price[i]); }
  assert(read->tick_price_fraction_indicator == written->tick_price_fraction_indicator);
}

/* Tick Price Negative Whole Pair: written and read back, then read and written back */
static void check_tick_price_negative_whole_pair(void) {
  TickPriceNegativeWholePair sent;
  TickPriceNegativeWholePair got;
  uint8_t wire[8];
  uint8_t again[8];

  any_tick_price_negative_whole_pair(&sent);
  assert(encode_tick_price_negative_whole_pair(&sent, wire, 0) == 8);
  assert(decode_tick_price_negative_whole_pair(&got, wire, 0) == 8);
  equal_tick_price_negative_whole_pair(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_tick_price_negative_whole_pair(&got, wire, 0) == 8);
  assert(encode_tick_price_negative_whole_pair(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Tick Price Negative Ten Pair: 8 bytes ----------------------------------- */

typedef struct {
  uint8_t raw_tick_price[7];              /* bytes 0 to 6 */
  uint8_t tick_price_fraction_indicator;  /* byte 7 */
} TickPriceNegativeTenPair;

/* any Tick Price Negative Ten Pair at all: every byte one the checker chooses */
static void any_tick_price_negative_ten_pair(TickPriceNegativeTenPair *record) {
  for (size_t i = 0; i < 7; i++) { record->raw_tick_price[i] = arbitrary(); }
  record->tick_price_fraction_indicator = arbitrary();
}

/* Tick Price Negative Ten Pair to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_tick_price_negative_ten_pair(const TickPriceNegativeTenPair *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->raw_tick_price[i]; }
  wire[at++] = record->tick_price_fraction_indicator;

  return at;
}

/* Tick Price Negative Ten Pair off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_tick_price_negative_ten_pair(TickPriceNegativeTenPair *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { record->raw_tick_price[i] = wire[at++]; }
  record->tick_price_fraction_indicator = wire[at++];

  return at;
}

/* what was read of Tick Price Negative Ten Pair is what was written, byte for byte */
static void equal_tick_price_negative_ten_pair(const TickPriceNegativeTenPair *read, const TickPriceNegativeTenPair *written) {
  for (size_t i = 0; i < 7; i++) { assert(read->raw_tick_price[i] == written->raw_tick_price[i]); }
  assert(read->tick_price_fraction_indicator == written->tick_price_fraction_indicator);
}

/* Tick Price Negative Ten Pair: written and read back, then read and written back */
static void check_tick_price_negative_ten_pair(void) {
  TickPriceNegativeTenPair sent;
  TickPriceNegativeTenPair got;
  uint8_t wire[8];
  uint8_t again[8];

  any_tick_price_negative_ten_pair(&sent);
  assert(encode_tick_price_negative_ten_pair(&sent, wire, 0) == 8);
  assert(decode_tick_price_negative_ten_pair(&got, wire, 0) == 8);
  equal_tick_price_negative_ten_pair(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_tick_price_negative_ten_pair(&got, wire, 0) == 8);
  assert(encode_tick_price_negative_ten_pair(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Tick Price Negative Hundred Pair: 8 bytes ------------------------------- */

typedef struct {
  uint8_t raw_tick_price[7];              /* bytes 0 to 6 */
  uint8_t tick_price_fraction_indicator;  /* byte 7 */
} TickPriceNegativeHundredPair;

/* any Tick Price Negative Hundred Pair at all: every byte one the checker chooses */
static void any_tick_price_negative_hundred_pair(TickPriceNegativeHundredPair *record) {
  for (size_t i = 0; i < 7; i++) { record->raw_tick_price[i] = arbitrary(); }
  record->tick_price_fraction_indicator = arbitrary();
}

/* Tick Price Negative Hundred Pair to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_tick_price_negative_hundred_pair(const TickPriceNegativeHundredPair *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->raw_tick_price[i]; }
  wire[at++] = record->tick_price_fraction_indicator;

  return at;
}

/* Tick Price Negative Hundred Pair off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_tick_price_negative_hundred_pair(TickPriceNegativeHundredPair *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { record->raw_tick_price[i] = wire[at++]; }
  record->tick_price_fraction_indicator = wire[at++];

  return at;
}

/* what was read of Tick Price Negative Hundred Pair is what was written, byte for byte */
static void equal_tick_price_negative_hundred_pair(const TickPriceNegativeHundredPair *read, const TickPriceNegativeHundredPair *written) {
  for (size_t i = 0; i < 7; i++) { assert(read->raw_tick_price[i] == written->raw_tick_price[i]); }
  assert(read->tick_price_fraction_indicator == written->tick_price_fraction_indicator);
}

/* Tick Price Negative Hundred Pair: written and read back, then read and written back */
static void check_tick_price_negative_hundred_pair(void) {
  TickPriceNegativeHundredPair sent;
  TickPriceNegativeHundredPair got;
  uint8_t wire[8];
  uint8_t again[8];

  any_tick_price_negative_hundred_pair(&sent);
  assert(encode_tick_price_negative_hundred_pair(&sent, wire, 0) == 8);
  assert(decode_tick_price_negative_hundred_pair(&got, wire, 0) == 8);
  equal_tick_price_negative_hundred_pair(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_tick_price_negative_hundred_pair(&got, wire, 0) == 8);
  assert(encode_tick_price_negative_hundred_pair(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Tick Price Negative Thousand Pair: 8 bytes ------------------------------ */

typedef struct {
  uint8_t raw_tick_price[7];              /* bytes 0 to 6 */
  uint8_t tick_price_fraction_indicator;  /* byte 7 */
} TickPriceNegativeThousandPair;

/* any Tick Price Negative Thousand Pair at all: every byte one the checker chooses */
static void any_tick_price_negative_thousand_pair(TickPriceNegativeThousandPair *record) {
  for (size_t i = 0; i < 7; i++) { record->raw_tick_price[i] = arbitrary(); }
  record->tick_price_fraction_indicator = arbitrary();
}

/* Tick Price Negative Thousand Pair to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_tick_price_negative_thousand_pair(const TickPriceNegativeThousandPair *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->raw_tick_price[i]; }
  wire[at++] = record->tick_price_fraction_indicator;

  return at;
}

/* Tick Price Negative Thousand Pair off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_tick_price_negative_thousand_pair(TickPriceNegativeThousandPair *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { record->raw_tick_price[i] = wire[at++]; }
  record->tick_price_fraction_indicator = wire[at++];

  return at;
}

/* what was read of Tick Price Negative Thousand Pair is what was written, byte for byte */
static void equal_tick_price_negative_thousand_pair(const TickPriceNegativeThousandPair *read, const TickPriceNegativeThousandPair *written) {
  for (size_t i = 0; i < 7; i++) { assert(read->raw_tick_price[i] == written->raw_tick_price[i]); }
  assert(read->tick_price_fraction_indicator == written->tick_price_fraction_indicator);
}

/* Tick Price Negative Thousand Pair: written and read back, then read and written back */
static void check_tick_price_negative_thousand_pair(void) {
  TickPriceNegativeThousandPair sent;
  TickPriceNegativeThousandPair got;
  uint8_t wire[8];
  uint8_t again[8];

  any_tick_price_negative_thousand_pair(&sent);
  assert(encode_tick_price_negative_thousand_pair(&sent, wire, 0) == 8);
  assert(decode_tick_price_negative_thousand_pair(&got, wire, 0) == 8);
  equal_tick_price_negative_thousand_pair(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_tick_price_negative_thousand_pair(&got, wire, 0) == 8);
  assert(encode_tick_price_negative_thousand_pair(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Tick Price Negative Ten Thousand Pair: 8 bytes -------------------------- */

typedef struct {
  uint8_t raw_tick_price[7];              /* bytes 0 to 6 */
  uint8_t tick_price_fraction_indicator;  /* byte 7 */
} TickPriceNegativeTenThousandPair;

/* any Tick Price Negative Ten Thousand Pair at all: every byte one the checker chooses */
static void any_tick_price_negative_ten_thousand_pair(TickPriceNegativeTenThousandPair *record) {
  for (size_t i = 0; i < 7; i++) { record->raw_tick_price[i] = arbitrary(); }
  record->tick_price_fraction_indicator = arbitrary();
}

/* Tick Price Negative Ten Thousand Pair to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_tick_price_negative_ten_thousand_pair(const TickPriceNegativeTenThousandPair *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->raw_tick_price[i]; }
  wire[at++] = record->tick_price_fraction_indicator;

  return at;
}

/* Tick Price Negative Ten Thousand Pair off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_tick_price_negative_ten_thousand_pair(TickPriceNegativeTenThousandPair *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { record->raw_tick_price[i] = wire[at++]; }
  record->tick_price_fraction_indicator = wire[at++];

  return at;
}

/* what was read of Tick Price Negative Ten Thousand Pair is what was written, byte for byte */
static void equal_tick_price_negative_ten_thousand_pair(const TickPriceNegativeTenThousandPair *read, const TickPriceNegativeTenThousandPair *written) {
  for (size_t i = 0; i < 7; i++) { assert(read->raw_tick_price[i] == written->raw_tick_price[i]); }
  assert(read->tick_price_fraction_indicator == written->tick_price_fraction_indicator);
}

/* Tick Price Negative Ten Thousand Pair: written and read back, then read and written back */
static void check_tick_price_negative_ten_thousand_pair(void) {
  TickPriceNegativeTenThousandPair sent;
  TickPriceNegativeTenThousandPair got;
  uint8_t wire[8];
  uint8_t again[8];

  any_tick_price_negative_ten_thousand_pair(&sent);
  assert(encode_tick_price_negative_ten_thousand_pair(&sent, wire, 0) == 8);
  assert(decode_tick_price_negative_ten_thousand_pair(&got, wire, 0) == 8);
  equal_tick_price_negative_ten_thousand_pair(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_tick_price_negative_ten_thousand_pair(&got, wire, 0) == 8);
  assert(encode_tick_price_negative_ten_thousand_pair(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Tick Price Negative Hundred Thousand Pair: 8 bytes ---------------------- */

typedef struct {
  uint8_t raw_tick_price[7];              /* bytes 0 to 6 */
  uint8_t tick_price_fraction_indicator;  /* byte 7 */
} TickPriceNegativeHundredThousandPair;

/* any Tick Price Negative Hundred Thousand Pair at all: every byte one the checker chooses */
static void any_tick_price_negative_hundred_thousand_pair(TickPriceNegativeHundredThousandPair *record) {
  for (size_t i = 0; i < 7; i++) { record->raw_tick_price[i] = arbitrary(); }
  record->tick_price_fraction_indicator = arbitrary();
}

/* Tick Price Negative Hundred Thousand Pair to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_tick_price_negative_hundred_thousand_pair(const TickPriceNegativeHundredThousandPair *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->raw_tick_price[i]; }
  wire[at++] = record->tick_price_fraction_indicator;

  return at;
}

/* Tick Price Negative Hundred Thousand Pair off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_tick_price_negative_hundred_thousand_pair(TickPriceNegativeHundredThousandPair *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { record->raw_tick_price[i] = wire[at++]; }
  record->tick_price_fraction_indicator = wire[at++];

  return at;
}

/* what was read of Tick Price Negative Hundred Thousand Pair is what was written, byte for byte */
static void equal_tick_price_negative_hundred_thousand_pair(const TickPriceNegativeHundredThousandPair *read, const TickPriceNegativeHundredThousandPair *written) {
  for (size_t i = 0; i < 7; i++) { assert(read->raw_tick_price[i] == written->raw_tick_price[i]); }
  assert(read->tick_price_fraction_indicator == written->tick_price_fraction_indicator);
}

/* Tick Price Negative Hundred Thousand Pair: written and read back, then read and written back */
static void check_tick_price_negative_hundred_thousand_pair(void) {
  TickPriceNegativeHundredThousandPair sent;
  TickPriceNegativeHundredThousandPair got;
  uint8_t wire[8];
  uint8_t again[8];

  any_tick_price_negative_hundred_thousand_pair(&sent);
  assert(encode_tick_price_negative_hundred_thousand_pair(&sent, wire, 0) == 8);
  assert(decode_tick_price_negative_hundred_thousand_pair(&got, wire, 0) == 8);
  equal_tick_price_negative_hundred_thousand_pair(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_tick_price_negative_hundred_thousand_pair(&got, wire, 0) == 8);
  assert(encode_tick_price_negative_hundred_thousand_pair(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Tick Price Negative Million Pair: 8 bytes ------------------------------- */

typedef struct {
  uint8_t raw_tick_price[7];              /* bytes 0 to 6 */
  uint8_t tick_price_fraction_indicator;  /* byte 7 */
} TickPriceNegativeMillionPair;

/* any Tick Price Negative Million Pair at all: every byte one the checker chooses */
static void any_tick_price_negative_million_pair(TickPriceNegativeMillionPair *record) {
  for (size_t i = 0; i < 7; i++) { record->raw_tick_price[i] = arbitrary(); }
  record->tick_price_fraction_indicator = arbitrary();
}

/* Tick Price Negative Million Pair to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_tick_price_negative_million_pair(const TickPriceNegativeMillionPair *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->raw_tick_price[i]; }
  wire[at++] = record->tick_price_fraction_indicator;

  return at;
}

/* Tick Price Negative Million Pair off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_tick_price_negative_million_pair(TickPriceNegativeMillionPair *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { record->raw_tick_price[i] = wire[at++]; }
  record->tick_price_fraction_indicator = wire[at++];

  return at;
}

/* what was read of Tick Price Negative Million Pair is what was written, byte for byte */
static void equal_tick_price_negative_million_pair(const TickPriceNegativeMillionPair *read, const TickPriceNegativeMillionPair *written) {
  for (size_t i = 0; i < 7; i++) { assert(read->raw_tick_price[i] == written->raw_tick_price[i]); }
  assert(read->tick_price_fraction_indicator == written->tick_price_fraction_indicator);
}

/* Tick Price Negative Million Pair: written and read back, then read and written back */
static void check_tick_price_negative_million_pair(void) {
  TickPriceNegativeMillionPair sent;
  TickPriceNegativeMillionPair got;
  uint8_t wire[8];
  uint8_t again[8];

  any_tick_price_negative_million_pair(&sent);
  assert(encode_tick_price_negative_million_pair(&sent, wire, 0) == 8);
  assert(decode_tick_price_negative_million_pair(&got, wire, 0) == 8);
  equal_tick_price_negative_million_pair(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_tick_price_negative_million_pair(&got, wire, 0) == 8);
  assert(encode_tick_price_negative_million_pair(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Tick Price Numeric Pair: 8 bytes ---------------------------------------- */

typedef struct {
  uint8_t tick_price[7];                  /* bytes 0 to 6 */
  uint8_t tick_price_fraction_indicator;  /* byte 7 */
} TickPriceNumericPair;

/* any Tick Price Numeric Pair at all: every byte one the checker chooses */
static void any_tick_price_numeric_pair(TickPriceNumericPair *record) {
  for (size_t i = 0; i < 7; i++) { record->tick_price[i] = arbitrary(); }
  record->tick_price_fraction_indicator = arbitrary();
}

/* Tick Price Numeric Pair to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_tick_price_numeric_pair(const TickPriceNumericPair *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->tick_price[i]; }
  wire[at++] = record->tick_price_fraction_indicator;

  return at;
}

/* Tick Price Numeric Pair off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_tick_price_numeric_pair(TickPriceNumericPair *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { record->tick_price[i] = wire[at++]; }
  record->tick_price_fraction_indicator = wire[at++];

  return at;
}

/* what was read of Tick Price Numeric Pair is what was written, byte for byte */
static void equal_tick_price_numeric_pair(const TickPriceNumericPair *read, const TickPriceNumericPair *written) {
  for (size_t i = 0; i < 7; i++) { assert(read->tick_price[i] == written->tick_price[i]); }
  assert(read->tick_price_fraction_indicator == written->tick_price_fraction_indicator);
}

/* Tick Price Numeric Pair: written and read back, then read and written back */
static void check_tick_price_numeric_pair(void) {
  TickPriceNumericPair sent;
  TickPriceNumericPair got;
  uint8_t wire[8];
  uint8_t again[8];

  any_tick_price_numeric_pair(&sent);
  assert(encode_tick_price_numeric_pair(&sent, wire, 0) == 8);
  assert(decode_tick_price_numeric_pair(&got, wire, 0) == 8);
  equal_tick_price_numeric_pair(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_tick_price_numeric_pair(&got, wire, 0) == 8);
  assert(encode_tick_price_numeric_pair(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- End Of Transmission Message: 19 bytes ----------------------------------- */

/* This message will be sent daily to indicate that the day’s transmission is complete. No HSVF messages will be transmitted afterwards. Transmission will resume the following day. */
typedef struct {
  LongMessageHeader long_message_header;  /* bytes 0 to 11 */
  uint8_t exchange_id;                    /* byte 12 */
  uint8_t time[6];                        /* bytes 13 to 18 */
} EndOfTransmissionMessage;

/* any End Of Transmission Message at all: every byte one the checker chooses */
static void any_end_of_transmission_message(EndOfTransmissionMessage *record) {
  any_long_message_header(&record->long_message_header);
  record->exchange_id = arbitrary();
  for (size_t i = 0; i < 6; i++) { record->time[i] = arbitrary(); }
}

/* End Of Transmission Message to the wire: 19 bytes from at, returning where the next byte goes */
static size_t encode_end_of_transmission_message(const EndOfTransmissionMessage *record, uint8_t *wire, size_t at) {
  at = encode_long_message_header(&record->long_message_header, wire, at);
  wire[at++] = record->exchange_id;
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->time[i]; }

  return at;
}

/* End Of Transmission Message off the wire: 19 bytes from at, returning where the next byte lies */
static size_t decode_end_of_transmission_message(EndOfTransmissionMessage *record, const uint8_t *wire, size_t at) {
  at = decode_long_message_header(&record->long_message_header, wire, at);
  record->exchange_id = wire[at++];
  for (size_t i = 0; i < 6; i++) { record->time[i] = wire[at++]; }

  return at;
}

/* what was read of End Of Transmission Message is what was written, byte for byte */
static void equal_end_of_transmission_message(const EndOfTransmissionMessage *read, const EndOfTransmissionMessage *written) {
  equal_long_message_header(&read->long_message_header, &written->long_message_header);
  assert(read->exchange_id == written->exchange_id);
  for (size_t i = 0; i < 6; i++) { assert(read->time[i] == written->time[i]); }
}

/* End Of Transmission Message: written and read back, then read and written back */
static void check_end_of_transmission_message(void) {
  EndOfTransmissionMessage sent;
  EndOfTransmissionMessage got;
  uint8_t wire[19];
  uint8_t again[19];

  any_end_of_transmission_message(&sent);
  assert(encode_end_of_transmission_message(&sent, wire, 0) == 19);
  assert(decode_end_of_transmission_message(&got, wire, 0) == 19);
  equal_end_of_transmission_message(&got, &sent);

  for (size_t i = 0; i < 19; i++) { wire[i] = arbitrary(); }
  assert(decode_end_of_transmission_message(&got, wire, 0) == 19);
  assert(encode_end_of_transmission_message(&got, again, 0) == 19);
  for (size_t i = 0; i < 19; i++) { assert(again[i] == wire[i]); }
}

/* ---- Circuit Assurance Message: 18 bytes ------------------------------------- */

/* This message is sent out if no messages are sent by SAM for more than one minute after the broadcast has started (i.e., at the termination of the Test Loop message). This will be an assurance that the line is up. This message will continue to be sent until the U: End of Transmission message is sent. The Circuit Assurance message will repeat the sequence number of the previous record transmitted (except if it is a re-transmit message), i.e. it will not increase the sequence number. */
typedef struct {
  LongMessageHeader long_message_header;  /* bytes 0 to 11 */
  uint8_t time[6];                        /* bytes 12 to 17 */
} CircuitAssuranceMessage;

/* any Circuit Assurance Message at all: every byte one the checker chooses */
static void any_circuit_assurance_message(CircuitAssuranceMessage *record) {
  any_long_message_header(&record->long_message_header);
  for (size_t i = 0; i < 6; i++) { record->time[i] = arbitrary(); }
}

/* Circuit Assurance Message to the wire: 18 bytes from at, returning where the next byte goes */
static size_t encode_circuit_assurance_message(const CircuitAssuranceMessage *record, uint8_t *wire, size_t at) {
  at = encode_long_message_header(&record->long_message_header, wire, at);
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->time[i]; }

  return at;
}

/* Circuit Assurance Message off the wire: 18 bytes from at, returning where the next byte lies */
static size_t decode_circuit_assurance_message(CircuitAssuranceMessage *record, const uint8_t *wire, size_t at) {
  at = decode_long_message_header(&record->long_message_header, wire, at);
  for (size_t i = 0; i < 6; i++) { record->time[i] = wire[at++]; }

  return at;
}

/* what was read of Circuit Assurance Message is what was written, byte for byte */
static void equal_circuit_assurance_message(const CircuitAssuranceMessage *read, const CircuitAssuranceMessage *written) {
  equal_long_message_header(&read->long_message_header, &written->long_message_header);
  for (size_t i = 0; i < 6; i++) { assert(read->time[i] == written->time[i]); }
}

/* Circuit Assurance Message: written and read back, then read and written back */
static void check_circuit_assurance_message(void) {
  CircuitAssuranceMessage sent;
  CircuitAssuranceMessage got;
  uint8_t wire[18];
  uint8_t again[18];

  any_circuit_assurance_message(&sent);
  assert(encode_circuit_assurance_message(&sent, wire, 0) == 18);
  assert(decode_circuit_assurance_message(&got, wire, 0) == 18);
  equal_circuit_assurance_message(&got, &sent);

  for (size_t i = 0; i < 18; i++) { wire[i] = arbitrary(); }
  assert(decode_circuit_assurance_message(&got, wire, 0) == 18);
  assert(encode_circuit_assurance_message(&got, again, 0) == 18);
  for (size_t i = 0; i < 18; i++) { assert(again[i] == wire[i]); }
}

/* ---- What esbmc checks ------------------------------------------------------- */

/* every record of the protocol, each on its own buffers */
static void checks(void) {
  check_message_header();
  check_long_message_header();
  check_strike_price_negative_whole_pair();
  check_strike_price_negative_ten_pair();
  check_strike_price_negative_hundred_pair();
  check_strike_price_negative_thousand_pair();
  check_strike_price_negative_ten_thousand_pair();
  check_strike_price_negative_hundred_thousand_pair();
  check_strike_price_negative_million_pair();
  check_strike_price_numeric_pair();
  check_trade_price_negative_whole_pair();
  check_trade_price_negative_ten_pair();
  check_trade_price_negative_hundred_pair();
  check_trade_price_negative_thousand_pair();
  check_trade_price_negative_ten_thousand_pair();
  check_trade_price_negative_hundred_thousand_pair();
  check_trade_price_negative_million_pair();
  check_trade_price_numeric_pair();
  check_net_change_negative_whole_pair();
  check_net_change_negative_ten_pair();
  check_net_change_negative_hundred_pair();
  check_net_change_negative_thousand_pair();
  check_net_change_negative_ten_thousand_pair();
  check_net_change_negative_hundred_thousand_pair();
  check_net_change_negative_million_pair();
  check_net_change_numeric_pair();
  check_net_change_future_options_trade_message_negative_whole_pair();
  check_net_change_future_options_trade_message_negative_ten_pair();
  check_net_change_future_options_trade_message_negative_hundred_pair();
  check_net_change_future_options_trade_message_negative_thousand_pair();
  check_net_change_future_options_trade_message_negative_ten_thousand_pair();
  check_net_change_future_options_trade_message_negative_hundred_thousand_pair();
  check_net_change_future_options_trade_message_negative_million_pair();
  check_net_change_future_options_trade_message_numeric_pair();
  check_future_product();
  check_futures_request_for_quote_rfq_message();
  check_strategy_request_for_quote_rfq_message();
  check_strike_price_schedule_notice_negative_whole_pair();
  check_strike_price_schedule_notice_negative_ten_pair();
  check_strike_price_schedule_notice_negative_hundred_pair();
  check_strike_price_schedule_notice_negative_thousand_pair();
  check_strike_price_schedule_notice_negative_ten_thousand_pair();
  check_strike_price_schedule_notice_negative_hundred_thousand_pair();
  check_strike_price_schedule_notice_negative_million_pair();
  check_strike_price_schedule_notice_numeric_pair();
  check_instrument_schedule_notice_future_message();
  check_instrument_schedule_notice_strategy_message();
  check_bid_price_quote_opening_pair();
  check_bid_price_quote_numeric_negative_whole_pair();
  check_bid_price_quote_numeric_negative_ten_pair();
  check_bid_price_quote_numeric_negative_hundred_pair();
  check_bid_price_quote_numeric_negative_thousand_pair();
  check_bid_price_quote_numeric_negative_ten_thousand_pair();
  check_bid_price_quote_numeric_negative_hundred_thousand_pair();
  check_bid_price_quote_numeric_negative_million_pair();
  check_bid_price_quote_numeric_pair();
  check_ask_price_quote_opening_pair();
  check_ask_price_quote_numeric_negative_whole_pair();
  check_ask_price_quote_numeric_negative_ten_pair();
  check_ask_price_quote_numeric_negative_hundred_pair();
  check_ask_price_quote_numeric_negative_thousand_pair();
  check_ask_price_quote_numeric_negative_ten_thousand_pair();
  check_ask_price_quote_numeric_negative_hundred_thousand_pair();
  check_ask_price_quote_numeric_negative_million_pair();
  check_ask_price_quote_numeric_pair();
  check_ask_price_futures_depth_market_depth_level_h_f_opening_pair();
  check_ask_price_futures_depth_numeric_negative_whole_pair();
  check_ask_price_futures_depth_numeric_negative_ten_pair();
  check_ask_price_futures_depth_numeric_negative_hundred_pair();
  check_ask_price_futures_depth_numeric_negative_thousand_pair();
  check_ask_price_futures_depth_numeric_negative_ten_thousand_pair();
  check_ask_price_futures_depth_numeric_negative_hundred_thousand_pair();
  check_ask_price_futures_depth_numeric_negative_million_pair();
  check_ask_price_futures_depth_market_depth_level_h_f_numeric_pair();
  check_price_negative_whole_pair();
  check_price_negative_ten_pair();
  check_price_negative_hundred_pair();
  check_price_negative_thousand_pair();
  check_price_negative_ten_thousand_pair();
  check_price_negative_hundred_thousand_pair();
  check_price_negative_million_pair();
  check_price_numeric_pair();
  check_maximum_threshold_price_negative_whole_pair();
  check_maximum_threshold_price_negative_ten_pair();
  check_maximum_threshold_price_negative_hundred_pair();
  check_maximum_threshold_price_negative_thousand_pair();
  check_maximum_threshold_price_negative_ten_thousand_pair();
  check_maximum_threshold_price_negative_hundred_thousand_pair();
  check_maximum_threshold_price_negative_million_pair();
  check_maximum_threshold_price_numeric_pair();
  check_minimum_threshold_price_negative_whole_pair();
  check_minimum_threshold_price_negative_ten_pair();
  check_minimum_threshold_price_negative_hundred_pair();
  check_minimum_threshold_price_negative_thousand_pair();
  check_minimum_threshold_price_negative_ten_thousand_pair();
  check_minimum_threshold_price_negative_hundred_thousand_pair();
  check_minimum_threshold_price_negative_million_pair();
  check_minimum_threshold_price_numeric_pair();
  check_tick_increment_numeric_pair();
  check_tick_increment_numeric_negative_whole_pair();
  check_tick_increment_numeric_negative_ten_pair();
  check_tick_increment_numeric_negative_hundred_pair();
  check_tick_increment_numeric_negative_thousand_pair();
  check_tick_increment_numeric_negative_ten_thousand_pair();
  check_tick_increment_numeric_negative_hundred_thousand_pair();
  check_tick_increment_numeric_negative_million_pair();
  check_tick_increment_raw_pair();
  check_tick_value_negative_whole_pair();
  check_tick_value_negative_ten_pair();
  check_tick_value_negative_hundred_pair();
  check_tick_value_negative_thousand_pair();
  check_tick_value_negative_ten_thousand_pair();
  check_tick_value_negative_hundred_thousand_pair();
  check_tick_value_negative_million_pair();
  check_tick_value_numeric_pair();
  check_underlying_instrument_keys_message();
  check_maximum_threshold_price_futures_negative_whole_pair();
  check_maximum_threshold_price_futures_negative_ten_pair();
  check_maximum_threshold_price_futures_negative_hundred_pair();
  check_maximum_threshold_price_futures_negative_thousand_pair();
  check_maximum_threshold_price_futures_negative_ten_thousand_pair();
  check_maximum_threshold_price_futures_negative_hundred_thousand_pair();
  check_maximum_threshold_price_futures_negative_million_pair();
  check_maximum_threshold_price_futures_numeric_pair();
  check_minimum_threshold_price_futures_negative_whole_pair();
  check_minimum_threshold_price_futures_negative_ten_pair();
  check_minimum_threshold_price_futures_negative_hundred_pair();
  check_minimum_threshold_price_futures_negative_thousand_pair();
  check_minimum_threshold_price_futures_negative_ten_thousand_pair();
  check_minimum_threshold_price_futures_negative_hundred_thousand_pair();
  check_minimum_threshold_price_futures_negative_million_pair();
  check_minimum_threshold_price_futures_numeric_pair();
  check_associated_product();
  check_bid_price_summary_negative_whole_pair();
  check_bid_price_summary_negative_ten_pair();
  check_bid_price_summary_negative_hundred_pair();
  check_bid_price_summary_negative_thousand_pair();
  check_bid_price_summary_negative_ten_thousand_pair();
  check_bid_price_summary_negative_hundred_thousand_pair();
  check_bid_price_summary_negative_million_pair();
  check_bid_price_summary_numeric_pair();
  check_ask_price_summary_negative_whole_pair();
  check_ask_price_summary_negative_ten_pair();
  check_ask_price_summary_negative_hundred_pair();
  check_ask_price_summary_negative_thousand_pair();
  check_ask_price_summary_negative_ten_thousand_pair();
  check_ask_price_summary_negative_hundred_thousand_pair();
  check_ask_price_summary_negative_million_pair();
  check_ask_price_summary_numeric_pair();
  check_last_price_negative_whole_pair();
  check_last_price_negative_ten_pair();
  check_last_price_negative_hundred_pair();
  check_last_price_negative_thousand_pair();
  check_last_price_negative_ten_thousand_pair();
  check_last_price_negative_hundred_thousand_pair();
  check_last_price_negative_million_pair();
  check_last_price_numeric_pair();
  check_open_price_negative_whole_pair();
  check_open_price_negative_ten_pair();
  check_open_price_negative_hundred_pair();
  check_open_price_negative_thousand_pair();
  check_open_price_negative_ten_thousand_pair();
  check_open_price_negative_hundred_thousand_pair();
  check_open_price_negative_million_pair();
  check_open_price_numeric_pair();
  check_high_price_negative_whole_pair();
  check_high_price_negative_ten_pair();
  check_high_price_negative_hundred_pair();
  check_high_price_negative_thousand_pair();
  check_high_price_negative_ten_thousand_pair();
  check_high_price_negative_hundred_thousand_pair();
  check_high_price_negative_million_pair();
  check_high_price_numeric_pair();
  check_low_price_negative_whole_pair();
  check_low_price_negative_ten_pair();
  check_low_price_negative_hundred_pair();
  check_low_price_negative_thousand_pair();
  check_low_price_negative_ten_thousand_pair();
  check_low_price_negative_hundred_thousand_pair();
  check_low_price_negative_million_pair();
  check_low_price_numeric_pair();
  check_settlement_price_negative_whole_pair();
  check_settlement_price_negative_ten_pair();
  check_settlement_price_negative_hundred_pair();
  check_settlement_price_negative_thousand_pair();
  check_settlement_price_negative_ten_thousand_pair();
  check_settlement_price_negative_hundred_thousand_pair();
  check_settlement_price_negative_million_pair();
  check_settlement_price_numeric_pair();
  check_previous_settlement_price_negative_whole_pair();
  check_previous_settlement_price_negative_ten_pair();
  check_previous_settlement_price_negative_hundred_pair();
  check_previous_settlement_price_negative_thousand_pair();
  check_previous_settlement_price_negative_ten_thousand_pair();
  check_previous_settlement_price_negative_hundred_thousand_pair();
  check_previous_settlement_price_negative_million_pair();
  check_previous_settlement_price_numeric_pair();
  check_opening_price_negative_whole_pair();
  check_opening_price_negative_ten_pair();
  check_opening_price_negative_hundred_pair();
  check_opening_price_negative_thousand_pair();
  check_opening_price_negative_ten_thousand_pair();
  check_opening_price_negative_hundred_thousand_pair();
  check_opening_price_negative_million_pair();
  check_opening_price_numeric_pair();
  check_settlement_price_future_options_summary_message_negative_whole_pair();
  check_settlement_price_future_options_summary_message_negative_ten_pair();
  check_settlement_price_future_options_summary_message_negative_hundred_pair();
  check_settlement_price_future_options_summary_message_negative_thousand_pair();
  check_settlement_price_future_options_summary_message_negative_ten_thou_4kdujz();
  check_settlement_price_future_options_summary_message_negative_hundred_84tec0();
  check_settlement_price_future_options_summary_message_negative_million_pair();
  check_settlement_price_future_options_summary_message_numeric_pair();
  check_previous_settlement_negative_whole_pair();
  check_previous_settlement_negative_ten_pair();
  check_previous_settlement_negative_hundred_pair();
  check_previous_settlement_negative_thousand_pair();
  check_previous_settlement_negative_ten_thousand_pair();
  check_previous_settlement_negative_hundred_thousand_pair();
  check_previous_settlement_negative_million_pair();
  check_previous_settlement_numeric_pair();
  check_external_price_at_source_negative_whole_pair();
  check_external_price_at_source_negative_ten_pair();
  check_external_price_at_source_negative_hundred_pair();
  check_external_price_at_source_negative_thousand_pair();
  check_external_price_at_source_negative_ten_thousand_pair();
  check_external_price_at_source_negative_hundred_thousand_pair();
  check_external_price_at_source_negative_million_pair();
  check_external_price_at_source_numeric_pair();
  check_beginning_of_options_summary_message();
  check_beginning_of_future_options_summary_message();
  check_beginning_of_futures_summary_message();
  check_beginning_of_strategy_summary_message();
  check_group_status_message();
  check_group_status_strategies_message();
  check_regular_text_bulletin();
  check_special_text_bulletin();
  check_end_of_sales_message();
  check_min_price_negative_whole_pair();
  check_min_price_negative_ten_pair();
  check_min_price_negative_hundred_pair();
  check_min_price_negative_thousand_pair();
  check_min_price_negative_ten_thousand_pair();
  check_min_price_negative_hundred_thousand_pair();
  check_min_price_negative_million_pair();
  check_min_price_numeric_pair();
  check_tick_price_negative_whole_pair();
  check_tick_price_negative_ten_pair();
  check_tick_price_negative_hundred_pair();
  check_tick_price_negative_thousand_pair();
  check_tick_price_negative_ten_thousand_pair();
  check_tick_price_negative_hundred_thousand_pair();
  check_tick_price_negative_million_pair();
  check_tick_price_numeric_pair();
  check_end_of_transmission_message();
  check_circuit_assurance_message();
}

int main(void) {
#ifdef CONCRETE
  for (pattern = 0; pattern < 4; pattern++) { checks(); }
#else
  checks();
#endif

  return 0;
}
