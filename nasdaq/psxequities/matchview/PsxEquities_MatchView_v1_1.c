// nasdaq/psxequities/matchview/PsxEquities_MatchView_v1_1.c
/*
 * National Association of Securities Dealers Automated Quotations (Nasdaq) Match View
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

/* ---- Packet Header: 16 bytes ------------------------------------------------- */

typedef struct {
  uint8_t session[10];         /* bytes 0 to 9 */
  uint8_t sequence_number[4];  /* bytes 10 to 13 */
  uint8_t message_count[2];    /* bytes 14 to 15 */
} PacketHeader;

/* any Packet Header at all: every byte one the checker chooses */
static void any_packet_header(PacketHeader *record) {
  for (size_t i = 0; i < 10; i++) { record->session[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->sequence_number[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->message_count[i] = arbitrary(); }
}

/* Packet Header to the wire: 16 bytes from at, returning where the next byte goes */
static size_t encode_packet_header(const PacketHeader *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->session[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->sequence_number[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->message_count[i]; }

  return at;
}

/* Packet Header off the wire: 16 bytes from at, returning where the next byte lies */
static size_t decode_packet_header(PacketHeader *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 10; i++) { record->session[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->sequence_number[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->message_count[i] = wire[at++]; }

  return at;
}

/* what was read of Packet Header is what was written, byte for byte */
static void equal_packet_header(const PacketHeader *read, const PacketHeader *written) {
  for (size_t i = 0; i < 10; i++) { assert(read->session[i] == written->session[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->sequence_number[i] == written->sequence_number[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->message_count[i] == written->message_count[i]); }
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

/* ---- Message Header: 9 bytes ------------------------------------------------- */

typedef struct {
  uint8_t timestamp[8];  /* bytes 0 to 7 */
  uint8_t message_type;  /* byte 8 */
} MessageHeader;

/* any Message Header at all: every byte one the checker chooses */
static void any_message_header(MessageHeader *record) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
  record->message_type = arbitrary();
}

/* Message Header to the wire: 9 bytes from at, returning where the next byte goes */
static size_t encode_message_header(const MessageHeader *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }
  wire[at++] = record->message_type;

  return at;
}

/* Message Header off the wire: 9 bytes from at, returning where the next byte lies */
static size_t decode_message_header(MessageHeader *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }
  record->message_type = wire[at++];

  return at;
}

/* what was read of Message Header is what was written, byte for byte */
static void equal_message_header(const MessageHeader *read, const MessageHeader *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  assert(read->message_type == written->message_type);
}

/* Message Header: written and read back, then read and written back */
static void check_message_header(void) {
  MessageHeader sent;
  MessageHeader got;
  uint8_t wire[9];
  uint8_t again[9];

  any_message_header(&sent);
  assert(encode_message_header(&sent, wire, 0) == 9);
  assert(decode_message_header(&got, wire, 0) == 9);
  equal_message_header(&got, &sent);

  for (size_t i = 0; i < 9; i++) { wire[i] = arbitrary(); }
  assert(decode_message_header(&got, wire, 0) == 9);
  assert(encode_message_header(&got, again, 0) == 9);
  for (size_t i = 0; i < 9; i++) { assert(again[i] == wire[i]); }
}

/* ---- Best Bid And Offer Message: 28 bytes ------------------------------------ */

/* What the Nasdaq PSX execution system sees as the prevailing best bid and offer of the other exchanges. For this feed, the only message type is "U". */
typedef struct {
  uint8_t symbol[8];      /* bytes 0 to 7 */
  uint8_t bid_price[10];  /* bytes 8 to 17 */
  uint8_t ask_price[10];  /* bytes 18 to 27 */
} BestBidAndOfferMessage;

/* any Best Bid And Offer Message at all: every byte one the checker chooses */
static void any_best_bid_and_offer_message(BestBidAndOfferMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->symbol[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->bid_price[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->ask_price[i] = arbitrary(); }
}

/* Best Bid And Offer Message to the wire: 28 bytes from at, returning where the next byte goes */
static size_t encode_best_bid_and_offer_message(const BestBidAndOfferMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->symbol[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->bid_price[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->ask_price[i]; }

  return at;
}

/* Best Bid And Offer Message off the wire: 28 bytes from at, returning where the next byte lies */
static size_t decode_best_bid_and_offer_message(BestBidAndOfferMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->symbol[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->bid_price[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->ask_price[i] = wire[at++]; }

  return at;
}

/* what was read of Best Bid And Offer Message is what was written, byte for byte */
static void equal_best_bid_and_offer_message(const BestBidAndOfferMessage *read, const BestBidAndOfferMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->symbol[i] == written->symbol[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->bid_price[i] == written->bid_price[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->ask_price[i] == written->ask_price[i]); }
}

/* Best Bid And Offer Message: written and read back, then read and written back */
static void check_best_bid_and_offer_message(void) {
  BestBidAndOfferMessage sent;
  BestBidAndOfferMessage got;
  uint8_t wire[28];
  uint8_t again[28];

  any_best_bid_and_offer_message(&sent);
  assert(encode_best_bid_and_offer_message(&sent, wire, 0) == 28);
  assert(decode_best_bid_and_offer_message(&got, wire, 0) == 28);
  equal_best_bid_and_offer_message(&got, &sent);

  for (size_t i = 0; i < 28; i++) { wire[i] = arbitrary(); }
  assert(decode_best_bid_and_offer_message(&got, wire, 0) == 28);
  assert(encode_best_bid_and_offer_message(&got, again, 0) == 28);
  for (size_t i = 0; i < 28; i++) { assert(again[i] == wire[i]); }
}

/* ---- What esbmc checks ------------------------------------------------------- */

/* every record of the protocol, each on its own buffers */
static void checks(void) {
  check_packet_header();
  check_message_header();
  check_best_bid_and_offer_message();
}

int main(void) {
#ifdef CONCRETE
  for (pattern = 0; pattern < 4; pattern++) { checks(); }
#else
  checks();
#endif

  return 0;
}
