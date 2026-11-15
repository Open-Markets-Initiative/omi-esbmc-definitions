// tmx/tsx/globalfx/Tsx_GlobalFx_v1_0.c
/*
 * TMX Group Global Fx Feed
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

/* ---- Bid Price: 5 bytes ------------------------------------------------------ */

/* Bid Price mantissa, which Bid Price Exponent scales. Zero for Tier Status Z */
typedef struct {
  uint8_t bid_price_mantissa[4];  /* bytes 0 to 3 */
  uint8_t bid_price_exponent;     /* byte 4 */
} BidPrice;

/* any Bid Price at all: every byte one the checker chooses */
static void any_bid_price(BidPrice *record) {
  for (size_t i = 0; i < 4; i++) { record->bid_price_mantissa[i] = arbitrary(); }
  record->bid_price_exponent = arbitrary();
}

/* Bid Price to the wire: 5 bytes from at, returning where the next byte goes */
static size_t encode_bid_price(const BidPrice *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->bid_price_mantissa[i]; }
  wire[at++] = record->bid_price_exponent;

  return at;
}

/* Bid Price off the wire: 5 bytes from at, returning where the next byte lies */
static size_t decode_bid_price(BidPrice *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->bid_price_mantissa[i] = wire[at++]; }
  record->bid_price_exponent = wire[at++];

  return at;
}

/* what was read of Bid Price is what was written, byte for byte */
static void equal_bid_price(const BidPrice *read, const BidPrice *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->bid_price_mantissa[i] == written->bid_price_mantissa[i]); }
  assert(read->bid_price_exponent == written->bid_price_exponent);
}

/* Bid Price: written and read back, then read and written back */
static void check_bid_price(void) {
  BidPrice sent;
  BidPrice got;
  uint8_t wire[5];
  uint8_t again[5];

  any_bid_price(&sent);
  assert(encode_bid_price(&sent, wire, 0) == 5);
  assert(decode_bid_price(&got, wire, 0) == 5);
  equal_bid_price(&got, &sent);

  for (size_t i = 0; i < 5; i++) { wire[i] = arbitrary(); }
  assert(decode_bid_price(&got, wire, 0) == 5);
  assert(encode_bid_price(&got, again, 0) == 5);
  for (size_t i = 0; i < 5; i++) { assert(again[i] == wire[i]); }
}

/* ---- Offer Price: 5 bytes ---------------------------------------------------- */

/* Offer Price mantissa, which Offer Price Exponent scales. Zero for Tier Status Z */
typedef struct {
  uint8_t offer_price_mantissa[4];  /* bytes 0 to 3 */
  uint8_t offer_price_exponent;     /* byte 4 */
} OfferPrice;

/* any Offer Price at all: every byte one the checker chooses */
static void any_offer_price(OfferPrice *record) {
  for (size_t i = 0; i < 4; i++) { record->offer_price_mantissa[i] = arbitrary(); }
  record->offer_price_exponent = arbitrary();
}

/* Offer Price to the wire: 5 bytes from at, returning where the next byte goes */
static size_t encode_offer_price(const OfferPrice *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->offer_price_mantissa[i]; }
  wire[at++] = record->offer_price_exponent;

  return at;
}

/* Offer Price off the wire: 5 bytes from at, returning where the next byte lies */
static size_t decode_offer_price(OfferPrice *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->offer_price_mantissa[i] = wire[at++]; }
  record->offer_price_exponent = wire[at++];

  return at;
}

/* what was read of Offer Price is what was written, byte for byte */
static void equal_offer_price(const OfferPrice *read, const OfferPrice *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->offer_price_mantissa[i] == written->offer_price_mantissa[i]); }
  assert(read->offer_price_exponent == written->offer_price_exponent);
}

/* Offer Price: written and read back, then read and written back */
static void check_offer_price(void) {
  OfferPrice sent;
  OfferPrice got;
  uint8_t wire[5];
  uint8_t again[5];

  any_offer_price(&sent);
  assert(encode_offer_price(&sent, wire, 0) == 5);
  assert(decode_offer_price(&got, wire, 0) == 5);
  equal_offer_price(&got, &sent);

  for (size_t i = 0; i < 5; i++) { wire[i] = arbitrary(); }
  assert(decode_offer_price(&got, wire, 0) == 5);
  assert(encode_offer_price(&got, again, 0) == 5);
  for (size_t i = 0; i < 5; i++) { assert(again[i] == wire[i]); }
}

/* ---- What esbmc checks ------------------------------------------------------- */

/* every record of the protocol, each on its own buffers */
static void checks(void) {
  check_bid_price();
  check_offer_price();
}

int main(void) {
#ifdef CONCRETE
  for (pattern = 0; pattern < 4; pattern++) { checks(); }
#else
  checks();
#endif

  return 0;
}
