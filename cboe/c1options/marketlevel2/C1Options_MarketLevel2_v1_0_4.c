// cboe/c1options/marketlevel2/C1Options_MarketLevel2_v1_0_4.c
/*
 * Chicago Board Options Exchange Market Level 2 Feed
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

/* ---- Security Status Message: 13 bytes --------------------------------------- */

/* Security Status messages contain the SecurityTradingStatus for a product */
typedef struct {
  uint8_t class_key[4];             /* bytes 0 to 3 */
  uint8_t security_id[4];           /* bytes 4 to 7 */
  uint8_t rpt_seq[4];               /* bytes 8 to 11 */
  uint8_t security_trading_status;  /* byte 12 */
} SecurityStatusMessage;

/* any Security Status Message at all: every byte one the checker chooses */
static void any_security_status_message(SecurityStatusMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->class_key[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->security_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->rpt_seq[i] = arbitrary(); }
  record->security_trading_status = arbitrary();
}

/* Security Status Message to the wire: 13 bytes from at, returning where the next byte goes */
static size_t encode_security_status_message(const SecurityStatusMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->class_key[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->security_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->rpt_seq[i]; }
  wire[at++] = record->security_trading_status;

  return at;
}

/* Security Status Message off the wire: 13 bytes from at, returning where the next byte lies */
static size_t decode_security_status_message(SecurityStatusMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->class_key[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->security_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->rpt_seq[i] = wire[at++]; }
  record->security_trading_status = wire[at++];

  return at;
}

/* what was read of Security Status Message is what was written, byte for byte */
static void equal_security_status_message(const SecurityStatusMessage *read, const SecurityStatusMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->class_key[i] == written->class_key[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->security_id[i] == written->security_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->rpt_seq[i] == written->rpt_seq[i]); }
  assert(read->security_trading_status == written->security_trading_status);
}

/* Security Status Message: written and read back, then read and written back */
static void check_security_status_message(void) {
  SecurityStatusMessage sent;
  SecurityStatusMessage got;
  uint8_t wire[13];
  uint8_t again[13];

  any_security_status_message(&sent);
  assert(encode_security_status_message(&sent, wire, 0) == 13);
  assert(decode_security_status_message(&got, wire, 0) == 13);
  equal_security_status_message(&got, &sent);

  for (size_t i = 0; i < 13; i++) { wire[i] = arbitrary(); }
  assert(decode_security_status_message(&got, wire, 0) == 13);
  assert(encode_security_status_message(&got, again, 0) == 13);
  for (size_t i = 0; i < 13; i++) { assert(again[i] == wire[i]); }
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
  check_security_status_message();
}

int main(void) {
#ifdef CONCRETE
  for (pattern = 0; pattern < 4; pattern++) { checks(); }
#else
  checks();
#endif

  return 0;
}
