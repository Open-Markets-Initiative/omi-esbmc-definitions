// cboe/cxaequities/multicasttopofbook/CxaEquities_MulticastTopOfBook_Pitch_v1_0_10.c
/*
 * Chicago Board Options Exchange Multicast Top Of Book
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
 *   - a run filling what frames it
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

/* ---- Packet Header: 8 bytes -------------------------------------------------- */

typedef struct {
  uint8_t length[2];      /* bytes 0 to 1 */
  uint8_t message_count;  /* byte 2 */
  uint8_t unit;           /* byte 3 */
  uint8_t sequence[4];    /* bytes 4 to 7 */
} PacketHeader;

/* any Packet Header at all: every byte one the checker chooses */
static void any_packet_header(PacketHeader *record) {
  for (size_t i = 0; i < 2; i++) { record->length[i] = arbitrary(); }
  record->message_count = arbitrary();
  record->unit = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->sequence[i] = arbitrary(); }
}

/* Packet Header to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_packet_header(const PacketHeader *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->length[i]; }
  wire[at++] = record->message_count;
  wire[at++] = record->unit;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->sequence[i]; }

  return at;
}

/* Packet Header off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_packet_header(PacketHeader *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->length[i] = wire[at++]; }
  record->message_count = wire[at++];
  record->unit = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->sequence[i] = wire[at++]; }

  return at;
}

/* what was read of Packet Header is what was written, byte for byte */
static void equal_packet_header(const PacketHeader *read, const PacketHeader *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->length[i] == written->length[i]); }
  assert(read->message_count == written->message_count);
  assert(read->unit == written->unit);
  for (size_t i = 0; i < 4; i++) { assert(read->sequence[i] == written->sequence[i]); }
}

/* Packet Header: written and read back, then read and written back */
static void check_packet_header(void) {
  PacketHeader sent;
  PacketHeader got;
  uint8_t wire[8];
  uint8_t again[8];

  any_packet_header(&sent);
  assert(encode_packet_header(&sent, wire, 0) == 8);
  assert(decode_packet_header(&got, wire, 0) == 8);
  equal_packet_header(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_packet_header(&got, wire, 0) == 8);
  assert(encode_packet_header(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Message Header: 2 bytes ------------------------------------------------- */

typedef struct {
  uint8_t message_length;  /* byte 0 */
  uint8_t message_type;    /* byte 1 */
} MessageHeader;

/* any Message Header at all: every byte one the checker chooses */
static void any_message_header(MessageHeader *record) {
  record->message_length = arbitrary();
  record->message_type = arbitrary();
}

/* Message Header to the wire: 2 bytes from at, returning where the next byte goes */
static size_t encode_message_header(const MessageHeader *record, uint8_t *wire, size_t at) {
  wire[at++] = record->message_length;
  wire[at++] = record->message_type;

  return at;
}

/* Message Header off the wire: 2 bytes from at, returning where the next byte lies */
static size_t decode_message_header(MessageHeader *record, const uint8_t *wire, size_t at) {
  record->message_length = wire[at++];
  record->message_type = wire[at++];

  return at;
}

/* what was read of Message Header is what was written, byte for byte */
static void equal_message_header(const MessageHeader *read, const MessageHeader *written) {
  assert(read->message_length == written->message_length);
  assert(read->message_type == written->message_type);
}

/* Message Header: written and read back, then read and written back */
static void check_message_header(void) {
  MessageHeader sent;
  MessageHeader got;
  uint8_t wire[2];
  uint8_t again[2];

  any_message_header(&sent);
  assert(encode_message_header(&sent, wire, 0) == 2);
  assert(decode_message_header(&got, wire, 0) == 2);
  equal_message_header(&got, &sent);

  for (size_t i = 0; i < 2; i++) { wire[i] = arbitrary(); }
  assert(decode_message_header(&got, wire, 0) == 2);
  assert(encode_message_header(&got, again, 0) == 2);
  for (size_t i = 0; i < 2; i++) { assert(again[i] == wire[i]); }
}

/* ---- Unit Clear Message: 4 bytes --------------------------------------------- */

/* Instructs feed recipients to clear all data for the CXA book in the unit specified in the Sequenced Unit Header. Distributed in rare recovery events such as a datacentre fail-over. */
typedef struct {
  uint8_t reserved_4[4];  /* bytes 0 to 3 */
} UnitClearMessage;

/* any Unit Clear Message at all: every byte one the checker chooses */
static void any_unit_clear_message(UnitClearMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->reserved_4[i] = arbitrary(); }
}

/* Unit Clear Message to the wire: 4 bytes from at, returning where the next byte goes */
static size_t encode_unit_clear_message(const UnitClearMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->reserved_4[i]; }

  return at;
}

/* Unit Clear Message off the wire: 4 bytes from at, returning where the next byte lies */
static size_t decode_unit_clear_message(UnitClearMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->reserved_4[i] = wire[at++]; }

  return at;
}

/* what was read of Unit Clear Message is what was written, byte for byte */
static void equal_unit_clear_message(const UnitClearMessage *read, const UnitClearMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->reserved_4[i] == written->reserved_4[i]); }
}

/* Unit Clear Message: written and read back, then read and written back */
static void check_unit_clear_message(void) {
  UnitClearMessage sent;
  UnitClearMessage got;
  uint8_t wire[4];
  uint8_t again[4];

  any_unit_clear_message(&sent);
  assert(encode_unit_clear_message(&sent, wire, 0) == 4);
  assert(decode_unit_clear_message(&got, wire, 0) == 4);
  equal_unit_clear_message(&got, &sent);

  for (size_t i = 0; i < 4; i++) { wire[i] = arbitrary(); }
  assert(decode_unit_clear_message(&got, wire, 0) == 4);
  assert(encode_unit_clear_message(&got, again, 0) == 4);
  for (size_t i = 0; i < 4; i++) { assert(again[i] == wire[i]); }
}

/* ---- Trading Status Message: 20 bytes ---------------------------------------- */

/* Indicates the current trading status of a security. A Trading Status message will be sent whenever trading status changes for a security. */
typedef struct {
  uint8_t timestamp[8];       /* bytes 0 to 7 */
  uint8_t symbol[6];          /* bytes 8 to 13 */
  uint8_t trading_status;     /* byte 14 */
  uint8_t market_id_code[4];  /* bytes 15 to 18 */
  uint8_t reserved_1;         /* byte 19 */
} TradingStatusMessage;

/* any Trading Status Message at all: every byte one the checker chooses */
static void any_trading_status_message(TradingStatusMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->symbol[i] = arbitrary(); }
  record->trading_status = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->market_id_code[i] = arbitrary(); }
  record->reserved_1 = arbitrary();
}

/* Trading Status Message to the wire: 20 bytes from at, returning where the next byte goes */
static size_t encode_trading_status_message(const TradingStatusMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->symbol[i]; }
  wire[at++] = record->trading_status;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->market_id_code[i]; }
  wire[at++] = record->reserved_1;

  return at;
}

/* Trading Status Message off the wire: 20 bytes from at, returning where the next byte lies */
static size_t decode_trading_status_message(TradingStatusMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->symbol[i] = wire[at++]; }
  record->trading_status = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->market_id_code[i] = wire[at++]; }
  record->reserved_1 = wire[at++];

  return at;
}

/* what was read of Trading Status Message is what was written, byte for byte */
static void equal_trading_status_message(const TradingStatusMessage *read, const TradingStatusMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->symbol[i] == written->symbol[i]); }
  assert(read->trading_status == written->trading_status);
  for (size_t i = 0; i < 4; i++) { assert(read->market_id_code[i] == written->market_id_code[i]); }
  assert(read->reserved_1 == written->reserved_1);
}

/* Trading Status Message: written and read back, then read and written back */
static void check_trading_status_message(void) {
  TradingStatusMessage sent;
  TradingStatusMessage got;
  uint8_t wire[20];
  uint8_t again[20];

  any_trading_status_message(&sent);
  assert(encode_trading_status_message(&sent, wire, 0) == 20);
  assert(decode_trading_status_message(&got, wire, 0) == 20);
  equal_trading_status_message(&got, &sent);

  for (size_t i = 0; i < 20; i++) { wire[i] = arbitrary(); }
  assert(decode_trading_status_message(&got, wire, 0) == 20);
  assert(encode_trading_status_message(&got, again, 0) == 20);
  for (size_t i = 0; i < 20; i++) { assert(again[i] == wire[i]); }
}

/* ---- Single Side Update Message: 28 bytes ------------------------------------ */

/* Provides an updated price and size for a single side of a Symbol. The side is denoted by the Side field. One Single Side Update message may reflect one or more updates to the inside book that were processed at the same time but will only be done so in a way that can be arbitrated between A/B feeds. */
typedef struct {
  uint8_t timestamp[8];  /* bytes 0 to 7 */
  uint8_t symbol[6];     /* bytes 8 to 13 */
  uint8_t side;          /* byte 14 */
  uint8_t price[8];      /* bytes 15 to 22 */
  uint8_t quantity[4];   /* bytes 23 to 26 */
  uint8_t reserved_1;    /* byte 27 */
} SingleSideUpdateMessage;

/* any Single Side Update Message at all: every byte one the checker chooses */
static void any_single_side_update_message(SingleSideUpdateMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->symbol[i] = arbitrary(); }
  record->side = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->quantity[i] = arbitrary(); }
  record->reserved_1 = arbitrary();
}

/* Single Side Update Message to the wire: 28 bytes from at, returning where the next byte goes */
static size_t encode_single_side_update_message(const SingleSideUpdateMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->symbol[i]; }
  wire[at++] = record->side;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->quantity[i]; }
  wire[at++] = record->reserved_1;

  return at;
}

/* Single Side Update Message off the wire: 28 bytes from at, returning where the next byte lies */
static size_t decode_single_side_update_message(SingleSideUpdateMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->symbol[i] = wire[at++]; }
  record->side = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->quantity[i] = wire[at++]; }
  record->reserved_1 = wire[at++];

  return at;
}

/* what was read of Single Side Update Message is what was written, byte for byte */
static void equal_single_side_update_message(const SingleSideUpdateMessage *read, const SingleSideUpdateMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->symbol[i] == written->symbol[i]); }
  assert(read->side == written->side);
  for (size_t i = 0; i < 8; i++) { assert(read->price[i] == written->price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->quantity[i] == written->quantity[i]); }
  assert(read->reserved_1 == written->reserved_1);
}

/* Single Side Update Message: written and read back, then read and written back */
static void check_single_side_update_message(void) {
  SingleSideUpdateMessage sent;
  SingleSideUpdateMessage got;
  uint8_t wire[28];
  uint8_t again[28];

  any_single_side_update_message(&sent);
  assert(encode_single_side_update_message(&sent, wire, 0) == 28);
  assert(decode_single_side_update_message(&got, wire, 0) == 28);
  equal_single_side_update_message(&got, &sent);

  for (size_t i = 0; i < 28; i++) { wire[i] = arbitrary(); }
  assert(decode_single_side_update_message(&got, wire, 0) == 28);
  assert(encode_single_side_update_message(&got, again, 0) == 28);
  for (size_t i = 0; i < 28; i++) { assert(again[i] == wire[i]); }
}

/* ---- Two Side Update Message: 40 bytes --------------------------------------- */

/* Provides an updated price and size for both sides of a Symbol. One Two Side Update message may reflect one or more updates to the inside book that were processed at the same time but will only be done so in a way that can be arbitrated between A/B feeds. */
typedef struct {
  uint8_t timestamp[8];       /* bytes 0 to 7 */
  uint8_t symbol[6];          /* bytes 8 to 13 */
  uint8_t bid_price[8];       /* bytes 14 to 21 */
  uint8_t bid_quantity[4];    /* bytes 22 to 25 */
  uint8_t reserved_1;         /* byte 26 */
  uint8_t ask_price[8];       /* bytes 27 to 34 */
  uint8_t ask_quantity[4];    /* bytes 35 to 38 */
  uint8_t second_reserved_1;  /* byte 39 */
} TwoSideUpdateMessage;

/* any Two Side Update Message at all: every byte one the checker chooses */
static void any_two_side_update_message(TwoSideUpdateMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->symbol[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->bid_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->bid_quantity[i] = arbitrary(); }
  record->reserved_1 = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->ask_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->ask_quantity[i] = arbitrary(); }
  record->second_reserved_1 = arbitrary();
}

/* Two Side Update Message to the wire: 40 bytes from at, returning where the next byte goes */
static size_t encode_two_side_update_message(const TwoSideUpdateMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->symbol[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->bid_price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->bid_quantity[i]; }
  wire[at++] = record->reserved_1;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->ask_price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->ask_quantity[i]; }
  wire[at++] = record->second_reserved_1;

  return at;
}

/* Two Side Update Message off the wire: 40 bytes from at, returning where the next byte lies */
static size_t decode_two_side_update_message(TwoSideUpdateMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->symbol[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->bid_price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->bid_quantity[i] = wire[at++]; }
  record->reserved_1 = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->ask_price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->ask_quantity[i] = wire[at++]; }
  record->second_reserved_1 = wire[at++];

  return at;
}

/* what was read of Two Side Update Message is what was written, byte for byte */
static void equal_two_side_update_message(const TwoSideUpdateMessage *read, const TwoSideUpdateMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->symbol[i] == written->symbol[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->bid_price[i] == written->bid_price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->bid_quantity[i] == written->bid_quantity[i]); }
  assert(read->reserved_1 == written->reserved_1);
  for (size_t i = 0; i < 8; i++) { assert(read->ask_price[i] == written->ask_price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->ask_quantity[i] == written->ask_quantity[i]); }
  assert(read->second_reserved_1 == written->second_reserved_1);
}

/* Two Side Update Message: written and read back, then read and written back */
static void check_two_side_update_message(void) {
  TwoSideUpdateMessage sent;
  TwoSideUpdateMessage got;
  uint8_t wire[40];
  uint8_t again[40];

  any_two_side_update_message(&sent);
  assert(encode_two_side_update_message(&sent, wire, 0) == 40);
  assert(decode_two_side_update_message(&got, wire, 0) == 40);
  equal_two_side_update_message(&got, &sent);

  for (size_t i = 0; i < 40; i++) { wire[i] = arbitrary(); }
  assert(decode_two_side_update_message(&got, wire, 0) == 40);
  assert(encode_two_side_update_message(&got, again, 0) == 40);
  for (size_t i = 0; i < 40; i++) { assert(again[i] == wire[i]); }
}

/* ---- Calculated Value Message: 31 bytes -------------------------------------- */

/* Sent when CXA calculates market values for a specified symbol or when a calculated market value is reported to CXA. The specified symbol may not trade on CXA, but instead could represent index or iNAV values reported to CXA from third parties as indicated by the Value Category field. The index values will be reported on each of the unitised CXA TOP feeds and are not specific to an individual unit. Calculated Value messages will be included in a spin response. */
typedef struct {
  uint8_t timestamp[8];        /* bytes 0 to 7 */
  uint8_t symbol[6];           /* bytes 8 to 13 */
  uint8_t value_category;      /* byte 14 */
  uint8_t value[8];            /* bytes 15 to 22 */
  uint8_t value_timestamp[8];  /* bytes 23 to 30 */
} CalculatedValueMessage;

/* any Calculated Value Message at all: every byte one the checker chooses */
static void any_calculated_value_message(CalculatedValueMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->symbol[i] = arbitrary(); }
  record->value_category = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->value[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->value_timestamp[i] = arbitrary(); }
}

/* Calculated Value Message to the wire: 31 bytes from at, returning where the next byte goes */
static size_t encode_calculated_value_message(const CalculatedValueMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->symbol[i]; }
  wire[at++] = record->value_category;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->value[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->value_timestamp[i]; }

  return at;
}

/* Calculated Value Message off the wire: 31 bytes from at, returning where the next byte lies */
static size_t decode_calculated_value_message(CalculatedValueMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->symbol[i] = wire[at++]; }
  record->value_category = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->value[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->value_timestamp[i] = wire[at++]; }

  return at;
}

/* what was read of Calculated Value Message is what was written, byte for byte */
static void equal_calculated_value_message(const CalculatedValueMessage *read, const CalculatedValueMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->symbol[i] == written->symbol[i]); }
  assert(read->value_category == written->value_category);
  for (size_t i = 0; i < 8; i++) { assert(read->value[i] == written->value[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->value_timestamp[i] == written->value_timestamp[i]); }
}

/* Calculated Value Message: written and read back, then read and written back */
static void check_calculated_value_message(void) {
  CalculatedValueMessage sent;
  CalculatedValueMessage got;
  uint8_t wire[31];
  uint8_t again[31];

  any_calculated_value_message(&sent);
  assert(encode_calculated_value_message(&sent, wire, 0) == 31);
  assert(decode_calculated_value_message(&got, wire, 0) == 31);
  equal_calculated_value_message(&got, &sent);

  for (size_t i = 0; i < 31; i++) { wire[i] = arbitrary(); }
  assert(decode_calculated_value_message(&got, wire, 0) == 31);
  assert(encode_calculated_value_message(&got, again, 0) == 31);
  for (size_t i = 0; i < 31; i++) { assert(again[i] == wire[i]); }
}

/* ---- End Of Session Message: 4 bytes ----------------------------------------- */

/* Sent for each unit when the unit shuts down. No more sequenced messages will be delivered for this unit, but heartbeats from the unit may be received. */
typedef struct {
  uint8_t reserved_4[4];  /* bytes 0 to 3 */
} EndOfSessionMessage;

/* any End Of Session Message at all: every byte one the checker chooses */
static void any_end_of_session_message(EndOfSessionMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->reserved_4[i] = arbitrary(); }
}

/* End Of Session Message to the wire: 4 bytes from at, returning where the next byte goes */
static size_t encode_end_of_session_message(const EndOfSessionMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->reserved_4[i]; }

  return at;
}

/* End Of Session Message off the wire: 4 bytes from at, returning where the next byte lies */
static size_t decode_end_of_session_message(EndOfSessionMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->reserved_4[i] = wire[at++]; }

  return at;
}

/* what was read of End Of Session Message is what was written, byte for byte */
static void equal_end_of_session_message(const EndOfSessionMessage *read, const EndOfSessionMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->reserved_4[i] == written->reserved_4[i]); }
}

/* End Of Session Message: written and read back, then read and written back */
static void check_end_of_session_message(void) {
  EndOfSessionMessage sent;
  EndOfSessionMessage got;
  uint8_t wire[4];
  uint8_t again[4];

  any_end_of_session_message(&sent);
  assert(encode_end_of_session_message(&sent, wire, 0) == 4);
  assert(decode_end_of_session_message(&got, wire, 0) == 4);
  equal_end_of_session_message(&got, &sent);

  for (size_t i = 0; i < 4; i++) { wire[i] = arbitrary(); }
  assert(decode_end_of_session_message(&got, wire, 0) == 4);
  assert(encode_end_of_session_message(&got, again, 0) == 4);
  for (size_t i = 0; i < 4; i++) { assert(again[i] == wire[i]); }
}

/* ---- Auction Update Message: 32 bytes ---------------------------------------- */

/* Sent during Pre-Open and Pre-Close trading states when a symbol has an order update which relates to an overlapping order book (where the best bid price is greater than or equal to the best ask price). Includes the potential number of shares and the indicative auction price if the symbol were to undergo an auction now. Only sent if there are updates to the Buy Shares, Sell Shares, or Indicative Price fields. */
typedef struct {
  uint8_t timestamp[8];         /* bytes 0 to 7 */
  uint8_t symbol[6];            /* bytes 8 to 13 */
  uint8_t auction_type;         /* byte 14 */
  uint8_t buy_shares[4];        /* bytes 15 to 18 */
  uint8_t sell_shares[4];       /* bytes 19 to 22 */
  uint8_t indicative_price[8];  /* bytes 23 to 30 */
  uint8_t reserved_1;           /* byte 31 */
} AuctionUpdateMessage;

/* any Auction Update Message at all: every byte one the checker chooses */
static void any_auction_update_message(AuctionUpdateMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->symbol[i] = arbitrary(); }
  record->auction_type = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->buy_shares[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->sell_shares[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->indicative_price[i] = arbitrary(); }
  record->reserved_1 = arbitrary();
}

/* Auction Update Message to the wire: 32 bytes from at, returning where the next byte goes */
static size_t encode_auction_update_message(const AuctionUpdateMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->symbol[i]; }
  wire[at++] = record->auction_type;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->buy_shares[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->sell_shares[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->indicative_price[i]; }
  wire[at++] = record->reserved_1;

  return at;
}

/* Auction Update Message off the wire: 32 bytes from at, returning where the next byte lies */
static size_t decode_auction_update_message(AuctionUpdateMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->symbol[i] = wire[at++]; }
  record->auction_type = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->buy_shares[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->sell_shares[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->indicative_price[i] = wire[at++]; }
  record->reserved_1 = wire[at++];

  return at;
}

/* what was read of Auction Update Message is what was written, byte for byte */
static void equal_auction_update_message(const AuctionUpdateMessage *read, const AuctionUpdateMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->symbol[i] == written->symbol[i]); }
  assert(read->auction_type == written->auction_type);
  for (size_t i = 0; i < 4; i++) { assert(read->buy_shares[i] == written->buy_shares[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->sell_shares[i] == written->sell_shares[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->indicative_price[i] == written->indicative_price[i]); }
  assert(read->reserved_1 == written->reserved_1);
}

/* Auction Update Message: written and read back, then read and written back */
static void check_auction_update_message(void) {
  AuctionUpdateMessage sent;
  AuctionUpdateMessage got;
  uint8_t wire[32];
  uint8_t again[32];

  any_auction_update_message(&sent);
  assert(encode_auction_update_message(&sent, wire, 0) == 32);
  assert(decode_auction_update_message(&got, wire, 0) == 32);
  equal_auction_update_message(&got, &sent);

  for (size_t i = 0; i < 32; i++) { wire[i] = arbitrary(); }
  assert(decode_auction_update_message(&got, wire, 0) == 32);
  assert(encode_auction_update_message(&got, again, 0) == 32);
  for (size_t i = 0; i < 32; i++) { assert(again[i] == wire[i]); }
}

/* ---- Auction Summary Message: 28 bytes --------------------------------------- */

/* Sent at the completion of the Auction per symbol and includes the Auction Price and Shares traded. If there is no overlapping order book at the time of the auction, no auction trades will result, however the Auction Summary message will still be disseminated and contain zeroes in the Price and Shares fields. */
typedef struct {
  uint8_t timestamp[8];  /* bytes 0 to 7 */
  uint8_t symbol[6];     /* bytes 8 to 13 */
  uint8_t auction_type;  /* byte 14 */
  uint8_t price[8];      /* bytes 15 to 22 */
  uint8_t shares[4];     /* bytes 23 to 26 */
  uint8_t reserved_1;    /* byte 27 */
} AuctionSummaryMessage;

/* any Auction Summary Message at all: every byte one the checker chooses */
static void any_auction_summary_message(AuctionSummaryMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->symbol[i] = arbitrary(); }
  record->auction_type = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->shares[i] = arbitrary(); }
  record->reserved_1 = arbitrary();
}

/* Auction Summary Message to the wire: 28 bytes from at, returning where the next byte goes */
static size_t encode_auction_summary_message(const AuctionSummaryMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->symbol[i]; }
  wire[at++] = record->auction_type;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->shares[i]; }
  wire[at++] = record->reserved_1;

  return at;
}

/* Auction Summary Message off the wire: 28 bytes from at, returning where the next byte lies */
static size_t decode_auction_summary_message(AuctionSummaryMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->symbol[i] = wire[at++]; }
  record->auction_type = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->shares[i] = wire[at++]; }
  record->reserved_1 = wire[at++];

  return at;
}

/* what was read of Auction Summary Message is what was written, byte for byte */
static void equal_auction_summary_message(const AuctionSummaryMessage *read, const AuctionSummaryMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->symbol[i] == written->symbol[i]); }
  assert(read->auction_type == written->auction_type);
  for (size_t i = 0; i < 8; i++) { assert(read->price[i] == written->price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->shares[i] == written->shares[i]); }
  assert(read->reserved_1 == written->reserved_1);
}

/* Auction Summary Message: written and read back, then read and written back */
static void check_auction_summary_message(void) {
  AuctionSummaryMessage sent;
  AuctionSummaryMessage got;
  uint8_t wire[28];
  uint8_t again[28];

  any_auction_summary_message(&sent);
  assert(encode_auction_summary_message(&sent, wire, 0) == 28);
  assert(decode_auction_summary_message(&got, wire, 0) == 28);
  equal_auction_summary_message(&got, &sent);

  for (size_t i = 0; i < 28; i++) { wire[i] = arbitrary(); }
  assert(decode_auction_summary_message(&got, wire, 0) == 28);
  assert(encode_auction_summary_message(&got, again, 0) == 28);
  for (size_t i = 0; i < 28; i++) { assert(again[i] == wire[i]); }
}

/* ---- What esbmc checks ------------------------------------------------------- */

/* every record of the protocol, each on its own buffers */
static void checks(void) {
  check_packet_header();
  check_message_header();
  check_unit_clear_message();
  check_trading_status_message();
  check_single_side_update_message();
  check_two_side_update_message();
  check_calculated_value_message();
  check_end_of_session_message();
  check_auction_update_message();
  check_auction_summary_message();
}

int main(void) {
#ifdef CONCRETE
  for (pattern = 0; pattern < 4; pattern++) { checks(); }
#else
  checks();
#endif

  return 0;
}
