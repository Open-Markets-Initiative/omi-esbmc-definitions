// cboe/c1options/marketdatafeed/C1Options_MarketDataFeed_v1_4_2.c
/*
 * Chicago Board Options Exchange Market Data Feed
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
 *   - a length prefix framing what follows
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

/* ---- Packet Header: 16 bytes ------------------------------------------------- */

typedef struct {
  uint8_t version;               /* byte 0 */
  uint8_t packet_length[2];      /* bytes 1 to 2 */
  uint8_t sending_time[8];       /* bytes 3 to 10 */
  uint8_t message_count;         /* byte 11 */
  uint8_t first_msg_seq_num[4];  /* bytes 12 to 15 */
} PacketHeader;

/* any Packet Header at all: every byte one the checker chooses */
static void any_packet_header(PacketHeader *record) {
  record->version = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->packet_length[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->sending_time[i] = arbitrary(); }
  record->message_count = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->first_msg_seq_num[i] = arbitrary(); }
}

/* Packet Header to the wire: 16 bytes from at, returning where the next byte goes */
static size_t encode_packet_header(const PacketHeader *record, uint8_t *wire, size_t at) {
  wire[at++] = record->version;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->packet_length[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->sending_time[i]; }
  wire[at++] = record->message_count;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->first_msg_seq_num[i]; }

  return at;
}

/* Packet Header off the wire: 16 bytes from at, returning where the next byte lies */
static size_t decode_packet_header(PacketHeader *record, const uint8_t *wire, size_t at) {
  record->version = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->packet_length[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->sending_time[i] = wire[at++]; }
  record->message_count = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->first_msg_seq_num[i] = wire[at++]; }

  return at;
}

/* what was read of Packet Header is what was written, byte for byte */
static void equal_packet_header(const PacketHeader *read, const PacketHeader *written) {
  assert(read->version == written->version);
  for (size_t i = 0; i < 2; i++) { assert(read->packet_length[i] == written->packet_length[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->sending_time[i] == written->sending_time[i]); }
  assert(read->message_count == written->message_count);
  for (size_t i = 0; i < 4; i++) { assert(read->first_msg_seq_num[i] == written->first_msg_seq_num[i]); }
}

/* Packet Header: written and read back, then read and written back */
static void check_packet_header(void) {
  PacketHeader sent;
  PacketHeader got;
  uint8_t wire[16];
  uint8_t again[16];

  any_packet_header(&sent);
  assert(encode_packet_header(&sent, wire, 0) == 16);
  assert(decode_packet_header(&got, wire, 0) == 16);
  equal_packet_header(&got, &sent);

  for (size_t i = 0; i < 16; i++) { wire[i] = arbitrary(); }
  assert(decode_packet_header(&got, wire, 0) == 16);
  assert(encode_packet_header(&got, again, 0) == 16);
  for (size_t i = 0; i < 16; i++) { assert(again[i] == wire[i]); }
}

/* ---- Message Header: 8 bytes ------------------------------------------------- */

typedef struct {
  uint8_t message_length[2];  /* bytes 0 to 1 */
  uint8_t template_id;        /* byte 2 */
  uint8_t message_type;       /* byte 3 */
  uint8_t msg_seq_num[4];     /* bytes 4 to 7 */
} MessageHeader;

/* any Message Header at all: every byte one the checker chooses */
static void any_message_header(MessageHeader *record) {
  for (size_t i = 0; i < 2; i++) { record->message_length[i] = arbitrary(); }
  record->template_id = arbitrary();
  record->message_type = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->msg_seq_num[i] = arbitrary(); }
}

/* Message Header to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_message_header(const MessageHeader *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->message_length[i]; }
  wire[at++] = record->template_id;
  wire[at++] = record->message_type;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->msg_seq_num[i]; }

  return at;
}

/* Message Header off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_message_header(MessageHeader *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->message_length[i] = wire[at++]; }
  record->template_id = wire[at++];
  record->message_type = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->msg_seq_num[i] = wire[at++]; }

  return at;
}

/* what was read of Message Header is what was written, byte for byte */
static void equal_message_header(const MessageHeader *read, const MessageHeader *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->message_length[i] == written->message_length[i]); }
  assert(read->template_id == written->template_id);
  assert(read->message_type == written->message_type);
  for (size_t i = 0; i < 4; i++) { assert(read->msg_seq_num[i] == written->msg_seq_num[i]); }
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

/* ---- Strike Price: 5 bytes --------------------------------------------------- */

typedef struct {
  uint8_t strike_price_exponent;     /* byte 0 */
  uint8_t strike_price_mantissa[4];  /* bytes 1 to 4 */
} StrikePrice;

/* any Strike Price at all: every byte one the checker chooses */
static void any_strike_price(StrikePrice *record) {
  record->strike_price_exponent = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->strike_price_mantissa[i] = arbitrary(); }
}

/* Strike Price to the wire: 5 bytes from at, returning where the next byte goes */
static size_t encode_strike_price(const StrikePrice *record, uint8_t *wire, size_t at) {
  wire[at++] = record->strike_price_exponent;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->strike_price_mantissa[i]; }

  return at;
}

/* Strike Price off the wire: 5 bytes from at, returning where the next byte lies */
static size_t decode_strike_price(StrikePrice *record, const uint8_t *wire, size_t at) {
  record->strike_price_exponent = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->strike_price_mantissa[i] = wire[at++]; }

  return at;
}

/* what was read of Strike Price is what was written, byte for byte */
static void equal_strike_price(const StrikePrice *read, const StrikePrice *written) {
  assert(read->strike_price_exponent == written->strike_price_exponent);
  for (size_t i = 0; i < 4; i++) { assert(read->strike_price_mantissa[i] == written->strike_price_mantissa[i]); }
}

/* Strike Price: written and read back, then read and written back */
static void check_strike_price(void) {
  StrikePrice sent;
  StrikePrice got;
  uint8_t wire[5];
  uint8_t again[5];

  any_strike_price(&sent);
  assert(encode_strike_price(&sent, wire, 0) == 5);
  assert(decode_strike_price(&got, wire, 0) == 5);
  equal_strike_price(&got, &sent);

  for (size_t i = 0; i < 5; i++) { wire[i] = arbitrary(); }
  assert(decode_strike_price(&got, wire, 0) == 5);
  assert(encode_strike_price(&got, again, 0) == 5);
  for (size_t i = 0; i < 5; i++) { assert(again[i] == wire[i]); }
}

/* ---- Minimum Strike Price Fraction: 5 bytes ---------------------------------- */

typedef struct {
  uint8_t minimum_strike_price_fraction_exponent;     /* byte 0 */
  uint8_t minimum_strike_price_fraction_mantissa[4];  /* bytes 1 to 4 */
} MinimumStrikePriceFraction;

/* any Minimum Strike Price Fraction at all: every byte one the checker chooses */
static void any_minimum_strike_price_fraction(MinimumStrikePriceFraction *record) {
  record->minimum_strike_price_fraction_exponent = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->minimum_strike_price_fraction_mantissa[i] = arbitrary(); }
}

/* Minimum Strike Price Fraction to the wire: 5 bytes from at, returning where the next byte goes */
static size_t encode_minimum_strike_price_fraction(const MinimumStrikePriceFraction *record, uint8_t *wire, size_t at) {
  wire[at++] = record->minimum_strike_price_fraction_exponent;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->minimum_strike_price_fraction_mantissa[i]; }

  return at;
}

/* Minimum Strike Price Fraction off the wire: 5 bytes from at, returning where the next byte lies */
static size_t decode_minimum_strike_price_fraction(MinimumStrikePriceFraction *record, const uint8_t *wire, size_t at) {
  record->minimum_strike_price_fraction_exponent = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->minimum_strike_price_fraction_mantissa[i] = wire[at++]; }

  return at;
}

/* what was read of Minimum Strike Price Fraction is what was written, byte for byte */
static void equal_minimum_strike_price_fraction(const MinimumStrikePriceFraction *read, const MinimumStrikePriceFraction *written) {
  assert(read->minimum_strike_price_fraction_exponent == written->minimum_strike_price_fraction_exponent);
  for (size_t i = 0; i < 4; i++) { assert(read->minimum_strike_price_fraction_mantissa[i] == written->minimum_strike_price_fraction_mantissa[i]); }
}

/* Minimum Strike Price Fraction: written and read back, then read and written back */
static void check_minimum_strike_price_fraction(void) {
  MinimumStrikePriceFraction sent;
  MinimumStrikePriceFraction got;
  uint8_t wire[5];
  uint8_t again[5];

  any_minimum_strike_price_fraction(&sent);
  assert(encode_minimum_strike_price_fraction(&sent, wire, 0) == 5);
  assert(decode_minimum_strike_price_fraction(&got, wire, 0) == 5);
  equal_minimum_strike_price_fraction(&got, &sent);

  for (size_t i = 0; i < 5; i++) { wire[i] = arbitrary(); }
  assert(decode_minimum_strike_price_fraction(&got, wire, 0) == 5);
  assert(encode_minimum_strike_price_fraction(&got, again, 0) == 5);
  for (size_t i = 0; i < 5; i++) { assert(again[i] == wire[i]); }
}

/* ---- Max Strike Price: 5 bytes ----------------------------------------------- */

typedef struct {
  uint8_t max_strike_price_exponent;     /* byte 0 */
  uint8_t max_strike_price_mantissa[4];  /* bytes 1 to 4 */
} MaxStrikePrice;

/* any Max Strike Price at all: every byte one the checker chooses */
static void any_max_strike_price(MaxStrikePrice *record) {
  record->max_strike_price_exponent = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->max_strike_price_mantissa[i] = arbitrary(); }
}

/* Max Strike Price to the wire: 5 bytes from at, returning where the next byte goes */
static size_t encode_max_strike_price(const MaxStrikePrice *record, uint8_t *wire, size_t at) {
  wire[at++] = record->max_strike_price_exponent;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->max_strike_price_mantissa[i]; }

  return at;
}

/* Max Strike Price off the wire: 5 bytes from at, returning where the next byte lies */
static size_t decode_max_strike_price(MaxStrikePrice *record, const uint8_t *wire, size_t at) {
  record->max_strike_price_exponent = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->max_strike_price_mantissa[i] = wire[at++]; }

  return at;
}

/* what was read of Max Strike Price is what was written, byte for byte */
static void equal_max_strike_price(const MaxStrikePrice *read, const MaxStrikePrice *written) {
  assert(read->max_strike_price_exponent == written->max_strike_price_exponent);
  for (size_t i = 0; i < 4; i++) { assert(read->max_strike_price_mantissa[i] == written->max_strike_price_mantissa[i]); }
}

/* Max Strike Price: written and read back, then read and written back */
static void check_max_strike_price(void) {
  MaxStrikePrice sent;
  MaxStrikePrice got;
  uint8_t wire[5];
  uint8_t again[5];

  any_max_strike_price(&sent);
  assert(encode_max_strike_price(&sent, wire, 0) == 5);
  assert(decode_max_strike_price(&got, wire, 0) == 5);
  equal_max_strike_price(&got, &sent);

  for (size_t i = 0; i < 5; i++) { wire[i] = arbitrary(); }
  assert(decode_max_strike_price(&got, wire, 0) == 5);
  assert(encode_max_strike_price(&got, again, 0) == 5);
  for (size_t i = 0; i < 5; i++) { assert(again[i] == wire[i]); }
}

/* ---- Premium Break Point: 5 bytes -------------------------------------------- */

typedef struct {
  uint8_t premium_break_point_exponent;     /* byte 0 */
  uint8_t premium_break_point_mantissa[4];  /* bytes 1 to 4 */
} PremiumBreakPoint;

/* any Premium Break Point at all: every byte one the checker chooses */
static void any_premium_break_point(PremiumBreakPoint *record) {
  record->premium_break_point_exponent = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->premium_break_point_mantissa[i] = arbitrary(); }
}

/* Premium Break Point to the wire: 5 bytes from at, returning where the next byte goes */
static size_t encode_premium_break_point(const PremiumBreakPoint *record, uint8_t *wire, size_t at) {
  wire[at++] = record->premium_break_point_exponent;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->premium_break_point_mantissa[i]; }

  return at;
}

/* Premium Break Point off the wire: 5 bytes from at, returning where the next byte lies */
static size_t decode_premium_break_point(PremiumBreakPoint *record, const uint8_t *wire, size_t at) {
  record->premium_break_point_exponent = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->premium_break_point_mantissa[i] = wire[at++]; }

  return at;
}

/* what was read of Premium Break Point is what was written, byte for byte */
static void equal_premium_break_point(const PremiumBreakPoint *read, const PremiumBreakPoint *written) {
  assert(read->premium_break_point_exponent == written->premium_break_point_exponent);
  for (size_t i = 0; i < 4; i++) { assert(read->premium_break_point_mantissa[i] == written->premium_break_point_mantissa[i]); }
}

/* Premium Break Point: written and read back, then read and written back */
static void check_premium_break_point(void) {
  PremiumBreakPoint sent;
  PremiumBreakPoint got;
  uint8_t wire[5];
  uint8_t again[5];

  any_premium_break_point(&sent);
  assert(encode_premium_break_point(&sent, wire, 0) == 5);
  assert(decode_premium_break_point(&got, wire, 0) == 5);
  equal_premium_break_point(&got, &sent);

  for (size_t i = 0; i < 5; i++) { wire[i] = arbitrary(); }
  assert(decode_premium_break_point(&got, wire, 0) == 5);
  assert(encode_premium_break_point(&got, again, 0) == 5);
  for (size_t i = 0; i < 5; i++) { assert(again[i] == wire[i]); }
}

/* ---- Minimum Above Premium Fraction: 5 bytes --------------------------------- */

typedef struct {
  uint8_t minimum_above_premium_fraction_exponent;     /* byte 0 */
  uint8_t minimum_above_premium_fraction_mantissa[4];  /* bytes 1 to 4 */
} MinimumAbovePremiumFraction;

/* any Minimum Above Premium Fraction at all: every byte one the checker chooses */
static void any_minimum_above_premium_fraction(MinimumAbovePremiumFraction *record) {
  record->minimum_above_premium_fraction_exponent = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->minimum_above_premium_fraction_mantissa[i] = arbitrary(); }
}

/* Minimum Above Premium Fraction to the wire: 5 bytes from at, returning where the next byte goes */
static size_t encode_minimum_above_premium_fraction(const MinimumAbovePremiumFraction *record, uint8_t *wire, size_t at) {
  wire[at++] = record->minimum_above_premium_fraction_exponent;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->minimum_above_premium_fraction_mantissa[i]; }

  return at;
}

/* Minimum Above Premium Fraction off the wire: 5 bytes from at, returning where the next byte lies */
static size_t decode_minimum_above_premium_fraction(MinimumAbovePremiumFraction *record, const uint8_t *wire, size_t at) {
  record->minimum_above_premium_fraction_exponent = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->minimum_above_premium_fraction_mantissa[i] = wire[at++]; }

  return at;
}

/* what was read of Minimum Above Premium Fraction is what was written, byte for byte */
static void equal_minimum_above_premium_fraction(const MinimumAbovePremiumFraction *read, const MinimumAbovePremiumFraction *written) {
  assert(read->minimum_above_premium_fraction_exponent == written->minimum_above_premium_fraction_exponent);
  for (size_t i = 0; i < 4; i++) { assert(read->minimum_above_premium_fraction_mantissa[i] == written->minimum_above_premium_fraction_mantissa[i]); }
}

/* Minimum Above Premium Fraction: written and read back, then read and written back */
static void check_minimum_above_premium_fraction(void) {
  MinimumAbovePremiumFraction sent;
  MinimumAbovePremiumFraction got;
  uint8_t wire[5];
  uint8_t again[5];

  any_minimum_above_premium_fraction(&sent);
  assert(encode_minimum_above_premium_fraction(&sent, wire, 0) == 5);
  assert(decode_minimum_above_premium_fraction(&got, wire, 0) == 5);
  equal_minimum_above_premium_fraction(&got, &sent);

  for (size_t i = 0; i < 5; i++) { wire[i] = arbitrary(); }
  assert(decode_minimum_above_premium_fraction(&got, wire, 0) == 5);
  assert(encode_minimum_above_premium_fraction(&got, again, 0) == 5);
  for (size_t i = 0; i < 5; i++) { assert(again[i] == wire[i]); }
}

/* ---- Minimum Below Premium Fraction: 5 bytes --------------------------------- */

typedef struct {
  uint8_t minimum_below_premium_fraction_exponent;     /* byte 0 */
  uint8_t minimum_below_premium_fraction_mantissa[4];  /* bytes 1 to 4 */
} MinimumBelowPremiumFraction;

/* any Minimum Below Premium Fraction at all: every byte one the checker chooses */
static void any_minimum_below_premium_fraction(MinimumBelowPremiumFraction *record) {
  record->minimum_below_premium_fraction_exponent = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->minimum_below_premium_fraction_mantissa[i] = arbitrary(); }
}

/* Minimum Below Premium Fraction to the wire: 5 bytes from at, returning where the next byte goes */
static size_t encode_minimum_below_premium_fraction(const MinimumBelowPremiumFraction *record, uint8_t *wire, size_t at) {
  wire[at++] = record->minimum_below_premium_fraction_exponent;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->minimum_below_premium_fraction_mantissa[i]; }

  return at;
}

/* Minimum Below Premium Fraction off the wire: 5 bytes from at, returning where the next byte lies */
static size_t decode_minimum_below_premium_fraction(MinimumBelowPremiumFraction *record, const uint8_t *wire, size_t at) {
  record->minimum_below_premium_fraction_exponent = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->minimum_below_premium_fraction_mantissa[i] = wire[at++]; }

  return at;
}

/* what was read of Minimum Below Premium Fraction is what was written, byte for byte */
static void equal_minimum_below_premium_fraction(const MinimumBelowPremiumFraction *read, const MinimumBelowPremiumFraction *written) {
  assert(read->minimum_below_premium_fraction_exponent == written->minimum_below_premium_fraction_exponent);
  for (size_t i = 0; i < 4; i++) { assert(read->minimum_below_premium_fraction_mantissa[i] == written->minimum_below_premium_fraction_mantissa[i]); }
}

/* Minimum Below Premium Fraction: written and read back, then read and written back */
static void check_minimum_below_premium_fraction(void) {
  MinimumBelowPremiumFraction sent;
  MinimumBelowPremiumFraction got;
  uint8_t wire[5];
  uint8_t again[5];

  any_minimum_below_premium_fraction(&sent);
  assert(encode_minimum_below_premium_fraction(&sent, wire, 0) == 5);
  assert(decode_minimum_below_premium_fraction(&got, wire, 0) == 5);
  equal_minimum_below_premium_fraction(&got, &sent);

  for (size_t i = 0; i < 5; i++) { wire[i] = arbitrary(); }
  assert(decode_minimum_below_premium_fraction(&got, wire, 0) == 5);
  assert(encode_minimum_below_premium_fraction(&got, again, 0) == 5);
  for (size_t i = 0; i < 5; i++) { assert(again[i] == wire[i]); }
}

/* ---- Md Entry Px: 5 bytes ---------------------------------------------------- */

typedef struct {
  uint8_t md_entry_px_exponent;     /* byte 0 */
  uint8_t md_entry_px_mantissa[4];  /* bytes 1 to 4 */
} MdEntryPx;

/* any Md Entry Px at all: every byte one the checker chooses */
static void any_md_entry_px(MdEntryPx *record) {
  record->md_entry_px_exponent = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->md_entry_px_mantissa[i] = arbitrary(); }
}

/* Md Entry Px to the wire: 5 bytes from at, returning where the next byte goes */
static size_t encode_md_entry_px(const MdEntryPx *record, uint8_t *wire, size_t at) {
  wire[at++] = record->md_entry_px_exponent;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->md_entry_px_mantissa[i]; }

  return at;
}

/* Md Entry Px off the wire: 5 bytes from at, returning where the next byte lies */
static size_t decode_md_entry_px(MdEntryPx *record, const uint8_t *wire, size_t at) {
  record->md_entry_px_exponent = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->md_entry_px_mantissa[i] = wire[at++]; }

  return at;
}

/* what was read of Md Entry Px is what was written, byte for byte */
static void equal_md_entry_px(const MdEntryPx *read, const MdEntryPx *written) {
  assert(read->md_entry_px_exponent == written->md_entry_px_exponent);
  for (size_t i = 0; i < 4; i++) { assert(read->md_entry_px_mantissa[i] == written->md_entry_px_mantissa[i]); }
}

/* Md Entry Px: written and read back, then read and written back */
static void check_md_entry_px(void) {
  MdEntryPx sent;
  MdEntryPx got;
  uint8_t wire[5];
  uint8_t again[5];

  any_md_entry_px(&sent);
  assert(encode_md_entry_px(&sent, wire, 0) == 5);
  assert(decode_md_entry_px(&got, wire, 0) == 5);
  equal_md_entry_px(&got, &sent);

  for (size_t i = 0; i < 5; i++) { wire[i] = arbitrary(); }
  assert(decode_md_entry_px(&got, wire, 0) == 5);
  assert(encode_md_entry_px(&got, again, 0) == 5);
  for (size_t i = 0; i < 5; i++) { assert(again[i] == wire[i]); }
}

/* ---- Prev Close Px: 5 bytes -------------------------------------------------- */

typedef struct {
  uint8_t prev_close_px_exponent;     /* byte 0 */
  uint8_t prev_close_px_mantissa[4];  /* bytes 1 to 4 */
} PrevClosePx;

/* any Prev Close Px at all: every byte one the checker chooses */
static void any_prev_close_px(PrevClosePx *record) {
  record->prev_close_px_exponent = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->prev_close_px_mantissa[i] = arbitrary(); }
}

/* Prev Close Px to the wire: 5 bytes from at, returning where the next byte goes */
static size_t encode_prev_close_px(const PrevClosePx *record, uint8_t *wire, size_t at) {
  wire[at++] = record->prev_close_px_exponent;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->prev_close_px_mantissa[i]; }

  return at;
}

/* Prev Close Px off the wire: 5 bytes from at, returning where the next byte lies */
static size_t decode_prev_close_px(PrevClosePx *record, const uint8_t *wire, size_t at) {
  record->prev_close_px_exponent = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->prev_close_px_mantissa[i] = wire[at++]; }

  return at;
}

/* what was read of Prev Close Px is what was written, byte for byte */
static void equal_prev_close_px(const PrevClosePx *read, const PrevClosePx *written) {
  assert(read->prev_close_px_exponent == written->prev_close_px_exponent);
  for (size_t i = 0; i < 4; i++) { assert(read->prev_close_px_mantissa[i] == written->prev_close_px_mantissa[i]); }
}

/* Prev Close Px: written and read back, then read and written back */
static void check_prev_close_px(void) {
  PrevClosePx sent;
  PrevClosePx got;
  uint8_t wire[5];
  uint8_t again[5];

  any_prev_close_px(&sent);
  assert(encode_prev_close_px(&sent, wire, 0) == 5);
  assert(decode_prev_close_px(&got, wire, 0) == 5);
  equal_prev_close_px(&got, &sent);

  for (size_t i = 0; i < 5; i++) { wire[i] = arbitrary(); }
  assert(decode_prev_close_px(&got, wire, 0) == 5);
  assert(encode_prev_close_px(&got, again, 0) == 5);
  for (size_t i = 0; i < 5; i++) { assert(again[i] == wire[i]); }
}

/* ---- Eop: 5 bytes ------------------------------------------------------------ */

typedef struct {
  uint8_t eop_exponent;     /* byte 0 */
  uint8_t eop_mantissa[4];  /* bytes 1 to 4 */
} Eop;

/* any Eop at all: every byte one the checker chooses */
static void any_eop(Eop *record) {
  record->eop_exponent = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->eop_mantissa[i] = arbitrary(); }
}

/* Eop to the wire: 5 bytes from at, returning where the next byte goes */
static size_t encode_eop(const Eop *record, uint8_t *wire, size_t at) {
  wire[at++] = record->eop_exponent;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->eop_mantissa[i]; }

  return at;
}

/* Eop off the wire: 5 bytes from at, returning where the next byte lies */
static size_t decode_eop(Eop *record, const uint8_t *wire, size_t at) {
  record->eop_exponent = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->eop_mantissa[i] = wire[at++]; }

  return at;
}

/* what was read of Eop is what was written, byte for byte */
static void equal_eop(const Eop *read, const Eop *written) {
  assert(read->eop_exponent == written->eop_exponent);
  for (size_t i = 0; i < 4; i++) { assert(read->eop_mantissa[i] == written->eop_mantissa[i]); }
}

/* Eop: written and read back, then read and written back */
static void check_eop(void) {
  Eop sent;
  Eop got;
  uint8_t wire[5];
  uint8_t again[5];

  any_eop(&sent);
  assert(encode_eop(&sent, wire, 0) == 5);
  assert(decode_eop(&got, wire, 0) == 5);
  equal_eop(&got, &sent);

  for (size_t i = 0; i < 5; i++) { wire[i] = arbitrary(); }
  assert(decode_eop(&got, wire, 0) == 5);
  assert(encode_eop(&got, again, 0) == 5);
  for (size_t i = 0; i < 5; i++) { assert(again[i] == wire[i]); }
}

/* ---- Expected Opening Price And Size Message: 19 bytes ----------------------- */

/* The EOP message contains expected opening price and size information for a security. */
typedef struct {
  uint8_t class_key[4];    /* bytes 0 to 3 */
  uint8_t security_id[4];  /* bytes 4 to 7 */
  Eop eop;                 /* bytes 8 to 12 */
  uint8_t eos[4];          /* bytes 13 to 16 */
  uint8_t eop_type;        /* byte 17 */
  uint8_t legal_market;    /* byte 18 */
} ExpectedOpeningPriceAndSizeMessage;

/* any Expected Opening Price And Size Message at all: every byte one the checker chooses */
static void any_expected_opening_price_and_size_message(ExpectedOpeningPriceAndSizeMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->class_key[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->security_id[i] = arbitrary(); }
  any_eop(&record->eop);
  for (size_t i = 0; i < 4; i++) { record->eos[i] = arbitrary(); }
  record->eop_type = arbitrary();
  record->legal_market = arbitrary();
}

/* Expected Opening Price And Size Message to the wire: 19 bytes from at, returning where the next byte goes */
static size_t encode_expected_opening_price_and_size_message(const ExpectedOpeningPriceAndSizeMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->class_key[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->security_id[i]; }
  at = encode_eop(&record->eop, wire, at);
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->eos[i]; }
  wire[at++] = record->eop_type;
  wire[at++] = record->legal_market;

  return at;
}

/* Expected Opening Price And Size Message off the wire: 19 bytes from at, returning where the next byte lies */
static size_t decode_expected_opening_price_and_size_message(ExpectedOpeningPriceAndSizeMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->class_key[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->security_id[i] = wire[at++]; }
  at = decode_eop(&record->eop, wire, at);
  for (size_t i = 0; i < 4; i++) { record->eos[i] = wire[at++]; }
  record->eop_type = wire[at++];
  record->legal_market = wire[at++];

  return at;
}

/* what was read of Expected Opening Price And Size Message is what was written, byte for byte */
static void equal_expected_opening_price_and_size_message(const ExpectedOpeningPriceAndSizeMessage *read, const ExpectedOpeningPriceAndSizeMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->class_key[i] == written->class_key[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->security_id[i] == written->security_id[i]); }
  equal_eop(&read->eop, &written->eop);
  for (size_t i = 0; i < 4; i++) { assert(read->eos[i] == written->eos[i]); }
  assert(read->eop_type == written->eop_type);
  assert(read->legal_market == written->legal_market);
}

/* Expected Opening Price And Size Message: written and read back, then read and written back */
static void check_expected_opening_price_and_size_message(void) {
  ExpectedOpeningPriceAndSizeMessage sent;
  ExpectedOpeningPriceAndSizeMessage got;
  uint8_t wire[19];
  uint8_t again[19];

  any_expected_opening_price_and_size_message(&sent);
  assert(encode_expected_opening_price_and_size_message(&sent, wire, 0) == 19);
  assert(decode_expected_opening_price_and_size_message(&got, wire, 0) == 19);
  equal_expected_opening_price_and_size_message(&got, &sent);

  for (size_t i = 0; i < 19; i++) { wire[i] = arbitrary(); }
  assert(decode_expected_opening_price_and_size_message(&got, wire, 0) == 19);
  assert(encode_expected_opening_price_and_size_message(&got, again, 0) == 19);
  for (size_t i = 0; i < 19; i++) { assert(again[i] == wire[i]); }
}

/* ---- Net Chg Prev Day: 5 bytes ----------------------------------------------- */

typedef struct {
  uint8_t net_chg_prev_day_exponent;     /* byte 0 */
  uint8_t net_chg_prev_day_mantissa[4];  /* bytes 1 to 4 */
} NetChgPrevDay;

/* any Net Chg Prev Day at all: every byte one the checker chooses */
static void any_net_chg_prev_day(NetChgPrevDay *record) {
  record->net_chg_prev_day_exponent = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->net_chg_prev_day_mantissa[i] = arbitrary(); }
}

/* Net Chg Prev Day to the wire: 5 bytes from at, returning where the next byte goes */
static size_t encode_net_chg_prev_day(const NetChgPrevDay *record, uint8_t *wire, size_t at) {
  wire[at++] = record->net_chg_prev_day_exponent;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->net_chg_prev_day_mantissa[i]; }

  return at;
}

/* Net Chg Prev Day off the wire: 5 bytes from at, returning where the next byte lies */
static size_t decode_net_chg_prev_day(NetChgPrevDay *record, const uint8_t *wire, size_t at) {
  record->net_chg_prev_day_exponent = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->net_chg_prev_day_mantissa[i] = wire[at++]; }

  return at;
}

/* what was read of Net Chg Prev Day is what was written, byte for byte */
static void equal_net_chg_prev_day(const NetChgPrevDay *read, const NetChgPrevDay *written) {
  assert(read->net_chg_prev_day_exponent == written->net_chg_prev_day_exponent);
  for (size_t i = 0; i < 4; i++) { assert(read->net_chg_prev_day_mantissa[i] == written->net_chg_prev_day_mantissa[i]); }
}

/* Net Chg Prev Day: written and read back, then read and written back */
static void check_net_chg_prev_day(void) {
  NetChgPrevDay sent;
  NetChgPrevDay got;
  uint8_t wire[5];
  uint8_t again[5];

  any_net_chg_prev_day(&sent);
  assert(encode_net_chg_prev_day(&sent, wire, 0) == 5);
  assert(decode_net_chg_prev_day(&got, wire, 0) == 5);
  equal_net_chg_prev_day(&got, &sent);

  for (size_t i = 0; i < 5; i++) { wire[i] = arbitrary(); }
  assert(decode_net_chg_prev_day(&got, wire, 0) == 5);
  assert(encode_net_chg_prev_day(&got, again, 0) == 5);
  for (size_t i = 0; i < 5; i++) { assert(again[i] == wire[i]); }
}

/* ---- Underlying Px: 5 bytes -------------------------------------------------- */

typedef struct {
  uint8_t underlying_px_exponent;     /* byte 0 */
  uint8_t underlying_px_mantissa[4];  /* bytes 1 to 4 */
} UnderlyingPx;

/* any Underlying Px at all: every byte one the checker chooses */
static void any_underlying_px(UnderlyingPx *record) {
  record->underlying_px_exponent = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->underlying_px_mantissa[i] = arbitrary(); }
}

/* Underlying Px to the wire: 5 bytes from at, returning where the next byte goes */
static size_t encode_underlying_px(const UnderlyingPx *record, uint8_t *wire, size_t at) {
  wire[at++] = record->underlying_px_exponent;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->underlying_px_mantissa[i]; }

  return at;
}

/* Underlying Px off the wire: 5 bytes from at, returning where the next byte lies */
static size_t decode_underlying_px(UnderlyingPx *record, const uint8_t *wire, size_t at) {
  record->underlying_px_exponent = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->underlying_px_mantissa[i] = wire[at++]; }

  return at;
}

/* what was read of Underlying Px is what was written, byte for byte */
static void equal_underlying_px(const UnderlyingPx *read, const UnderlyingPx *written) {
  assert(read->underlying_px_exponent == written->underlying_px_exponent);
  for (size_t i = 0; i < 4; i++) { assert(read->underlying_px_mantissa[i] == written->underlying_px_mantissa[i]); }
}

/* Underlying Px: written and read back, then read and written back */
static void check_underlying_px(void) {
  UnderlyingPx sent;
  UnderlyingPx got;
  uint8_t wire[5];
  uint8_t again[5];

  any_underlying_px(&sent);
  assert(encode_underlying_px(&sent, wire, 0) == 5);
  assert(decode_underlying_px(&got, wire, 0) == 5);
  equal_underlying_px(&got, &sent);

  for (size_t i = 0; i < 5; i++) { wire[i] = arbitrary(); }
  assert(decode_underlying_px(&got, wire, 0) == 5);
  assert(encode_underlying_px(&got, again, 0) == 5);
  for (size_t i = 0; i < 5; i++) { assert(again[i] == wire[i]); }
}

/* ---- Market Data Control Message: 1 byte ------------------------------------- */

/* Market Data Control messages mark the start and end of the end of session Summary and the end of session Settlement data transmissions. */
typedef struct {
  uint8_t md_control_type;  /* byte 0 */
} MarketDataControlMessage;

/* any Market Data Control Message at all: every byte one the checker chooses */
static void any_market_data_control_message(MarketDataControlMessage *record) {
  record->md_control_type = arbitrary();
}

/* Market Data Control Message to the wire: 1 byte from at, returning where the next byte goes */
static size_t encode_market_data_control_message(const MarketDataControlMessage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->md_control_type;

  return at;
}

/* Market Data Control Message off the wire: 1 byte from at, returning where the next byte lies */
static size_t decode_market_data_control_message(MarketDataControlMessage *record, const uint8_t *wire, size_t at) {
  record->md_control_type = wire[at++];

  return at;
}

/* what was read of Market Data Control Message is what was written, byte for byte */
static void equal_market_data_control_message(const MarketDataControlMessage *read, const MarketDataControlMessage *written) {
  assert(read->md_control_type == written->md_control_type);
}

/* Market Data Control Message: written and read back, then read and written back */
static void check_market_data_control_message(void) {
  MarketDataControlMessage sent;
  MarketDataControlMessage got;
  uint8_t wire[1];
  uint8_t again[1];

  any_market_data_control_message(&sent);
  assert(encode_market_data_control_message(&sent, wire, 0) == 1);
  assert(decode_market_data_control_message(&got, wire, 0) == 1);
  equal_market_data_control_message(&got, &sent);

  for (size_t i = 0; i < 1; i++) { wire[i] = arbitrary(); }
  assert(decode_market_data_control_message(&got, wire, 0) == 1);
  assert(encode_market_data_control_message(&got, again, 0) == 1);
  for (size_t i = 0; i < 1; i++) { assert(again[i] == wire[i]); }
}

/* ---- What esbmc checks ------------------------------------------------------- */

/* every record of the protocol, each on its own buffers */
static void checks(void) {
  check_packet_header();
  check_message_header();
  check_strike_price();
  check_minimum_strike_price_fraction();
  check_max_strike_price();
  check_premium_break_point();
  check_minimum_above_premium_fraction();
  check_minimum_below_premium_fraction();
  check_md_entry_px();
  check_prev_close_px();
  check_eop();
  check_expected_opening_price_and_size_message();
  check_net_chg_prev_day();
  check_underlying_px();
  check_market_data_control_message();
}

int main(void) {
#ifdef CONCRETE
  for (pattern = 0; pattern < 4; pattern++) { checks(); }
#else
  checks();
#endif

  return 0;
}
