// cboe/cfefutures/multicasttop/CfeFutures_MulticastTop_Pitch_v1_2_20.c
/*
 * Chicago Board Options Exchange Futures Multicast Top
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

/* ---- Time Reference Message: 16 bytes ---------------------------------------- */

/* The Time Reference message is used to provide a midnight reference point for recipients of the feed. It is sent whenever the system starts up and when the system crosses a midnight boundary. */
typedef struct {
  uint8_t midnight_reference[4];  /* bytes 0 to 3 */
  uint8_t time_reference[4];      /* bytes 4 to 7 */
  uint8_t time_offset[4];         /* bytes 8 to 11 */
  uint8_t trade_date[4];          /* bytes 12 to 15 */
} TimeReferenceMessage;

/* any Time Reference Message at all: every byte one the checker chooses */
static void any_time_reference_message(TimeReferenceMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->midnight_reference[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->time_reference[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->time_offset[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->trade_date[i] = arbitrary(); }
}

/* Time Reference Message to the wire: 16 bytes from at, returning where the next byte goes */
static size_t encode_time_reference_message(const TimeReferenceMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->midnight_reference[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->time_reference[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->time_offset[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->trade_date[i]; }

  return at;
}

/* Time Reference Message off the wire: 16 bytes from at, returning where the next byte lies */
static size_t decode_time_reference_message(TimeReferenceMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->midnight_reference[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->time_reference[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->time_offset[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->trade_date[i] = wire[at++]; }

  return at;
}

/* what was read of Time Reference Message is what was written, byte for byte */
static void equal_time_reference_message(const TimeReferenceMessage *read, const TimeReferenceMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->midnight_reference[i] == written->midnight_reference[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->time_reference[i] == written->time_reference[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->time_offset[i] == written->time_offset[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->trade_date[i] == written->trade_date[i]); }
}

/* Time Reference Message: written and read back, then read and written back */
static void check_time_reference_message(void) {
  TimeReferenceMessage sent;
  TimeReferenceMessage got;
  uint8_t wire[16];
  uint8_t again[16];

  any_time_reference_message(&sent);
  assert(encode_time_reference_message(&sent, wire, 0) == 16);
  assert(decode_time_reference_message(&got, wire, 0) == 16);
  equal_time_reference_message(&got, &sent);

  for (size_t i = 0; i < 16; i++) { wire[i] = arbitrary(); }
  assert(decode_time_reference_message(&got, wire, 0) == 16);
  assert(encode_time_reference_message(&got, again, 0) == 16);
  for (size_t i = 0; i < 16; i++) { assert(again[i] == wire[i]); }
}

/* ---- Time Message: 8 bytes --------------------------------------------------- */

/* A Time message is immediately generated and sent when there is a TOP event for a given clock second. */
typedef struct {
  uint8_t time_reference[4];  /* bytes 0 to 3 */
  uint8_t epoch_time[4];      /* bytes 4 to 7 */
} TimeMessage;

/* any Time Message at all: every byte one the checker chooses */
static void any_time_message(TimeMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->time_reference[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->epoch_time[i] = arbitrary(); }
}

/* Time Message to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_time_message(const TimeMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->time_reference[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->epoch_time[i]; }

  return at;
}

/* Time Message off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_time_message(TimeMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->time_reference[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->epoch_time[i] = wire[at++]; }

  return at;
}

/* what was read of Time Message is what was written, byte for byte */
static void equal_time_message(const TimeMessage *read, const TimeMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->time_reference[i] == written->time_reference[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->epoch_time[i] == written->epoch_time[i]); }
}

/* Time Message: written and read back, then read and written back */
static void check_time_message(void) {
  TimeMessage sent;
  TimeMessage got;
  uint8_t wire[8];
  uint8_t again[8];

  any_time_message(&sent);
  assert(encode_time_message(&sent, wire, 0) == 8);
  assert(decode_time_message(&got, wire, 0) == 8);
  equal_time_message(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_time_message(&got, wire, 0) == 8);
  assert(encode_time_message(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Unit Clear Message: 4 bytes --------------------------------------------- */

/* The Unit Clear message instructs feed recipients to clear all market snapshots for the CFE book in the unit specified in the Sequenced Unit Header message header. */
typedef struct {
  uint8_t time_offset[4];  /* bytes 0 to 3 */
} UnitClearMessage;

/* any Unit Clear Message at all: every byte one the checker chooses */
static void any_unit_clear_message(UnitClearMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->time_offset[i] = arbitrary(); }
}

/* Unit Clear Message to the wire: 4 bytes from at, returning where the next byte goes */
static size_t encode_unit_clear_message(const UnitClearMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->time_offset[i]; }

  return at;
}

/* Unit Clear Message off the wire: 4 bytes from at, returning where the next byte lies */
static size_t decode_unit_clear_message(UnitClearMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->time_offset[i] = wire[at++]; }

  return at;
}

/* what was read of Unit Clear Message is what was written, byte for byte */
static void equal_unit_clear_message(const UnitClearMessage *read, const UnitClearMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->time_offset[i] == written->time_offset[i]); }
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

/* ---- Futures Variance Symbol Mapping Message: 38 bytes ----------------------- */

/* The Futures Variance Symbol Mapping message is used to disseminate symbol reference data for S&P 500 Variance Futures (VA Futures) symbols. */
typedef struct {
  uint8_t time_offset[4];           /* bytes 0 to 3 */
  uint8_t unit_timestamp[4];        /* bytes 4 to 7 */
  uint8_t feed_symbol[6];           /* bytes 8 to 13 */
  uint8_t futures_symbol[12];       /* bytes 14 to 25 */
  uint8_t accrued_day_variance[8];  /* bytes 26 to 33 */
  uint8_t num_final_returns[2];     /* bytes 34 to 35 */
  uint8_t num_elapsed_returns[2];   /* bytes 36 to 37 */
} FuturesVarianceSymbolMappingMessage;

/* any Futures Variance Symbol Mapping Message at all: every byte one the checker chooses */
static void any_futures_variance_symbol_mapping_message(FuturesVarianceSymbolMappingMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->time_offset[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->unit_timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->feed_symbol[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->futures_symbol[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->accrued_day_variance[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->num_final_returns[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->num_elapsed_returns[i] = arbitrary(); }
}

/* Futures Variance Symbol Mapping Message to the wire: 38 bytes from at, returning where the next byte goes */
static size_t encode_futures_variance_symbol_mapping_message(const FuturesVarianceSymbolMappingMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->time_offset[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->unit_timestamp[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->feed_symbol[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->futures_symbol[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->accrued_day_variance[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->num_final_returns[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->num_elapsed_returns[i]; }

  return at;
}

/* Futures Variance Symbol Mapping Message off the wire: 38 bytes from at, returning where the next byte lies */
static size_t decode_futures_variance_symbol_mapping_message(FuturesVarianceSymbolMappingMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->time_offset[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->unit_timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->feed_symbol[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->futures_symbol[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->accrued_day_variance[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->num_final_returns[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->num_elapsed_returns[i] = wire[at++]; }

  return at;
}

/* what was read of Futures Variance Symbol Mapping Message is what was written, byte for byte */
static void equal_futures_variance_symbol_mapping_message(const FuturesVarianceSymbolMappingMessage *read, const FuturesVarianceSymbolMappingMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->time_offset[i] == written->time_offset[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->unit_timestamp[i] == written->unit_timestamp[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->feed_symbol[i] == written->feed_symbol[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->futures_symbol[i] == written->futures_symbol[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->accrued_day_variance[i] == written->accrued_day_variance[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->num_final_returns[i] == written->num_final_returns[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->num_elapsed_returns[i] == written->num_elapsed_returns[i]); }
}

/* Futures Variance Symbol Mapping Message: written and read back, then read and written back */
static void check_futures_variance_symbol_mapping_message(void) {
  FuturesVarianceSymbolMappingMessage sent;
  FuturesVarianceSymbolMappingMessage got;
  uint8_t wire[38];
  uint8_t again[38];

  any_futures_variance_symbol_mapping_message(&sent);
  assert(encode_futures_variance_symbol_mapping_message(&sent, wire, 0) == 38);
  assert(decode_futures_variance_symbol_mapping_message(&got, wire, 0) == 38);
  equal_futures_variance_symbol_mapping_message(&got, &sent);

  for (size_t i = 0; i < 38; i++) { wire[i] = arbitrary(); }
  assert(decode_futures_variance_symbol_mapping_message(&got, wire, 0) == 38);
  assert(encode_futures_variance_symbol_mapping_message(&got, again, 0) == 38);
  for (size_t i = 0; i < 38; i++) { assert(again[i] == wire[i]); }
}

/* ---- Price Limits Message: 26 bytes ------------------------------------------ */

/* The Price Limits message can be sent as a sequenced or un-sequenced message. It is sent out at the start of the session for products subject to price limits per the contract specifications. */
typedef struct {
  uint8_t time_offset[4];        /* bytes 0 to 3 */
  uint8_t symbol[6];             /* bytes 4 to 9 */
  uint8_t upper_price_limit[8];  /* bytes 10 to 17 */
  uint8_t lower_price_limit[8];  /* bytes 18 to 25 */
} PriceLimitsMessage;

/* any Price Limits Message at all: every byte one the checker chooses */
static void any_price_limits_message(PriceLimitsMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->time_offset[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->symbol[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->upper_price_limit[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->lower_price_limit[i] = arbitrary(); }
}

/* Price Limits Message to the wire: 26 bytes from at, returning where the next byte goes */
static size_t encode_price_limits_message(const PriceLimitsMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->time_offset[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->symbol[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->upper_price_limit[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->lower_price_limit[i]; }

  return at;
}

/* Price Limits Message off the wire: 26 bytes from at, returning where the next byte lies */
static size_t decode_price_limits_message(PriceLimitsMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->time_offset[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->symbol[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->upper_price_limit[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->lower_price_limit[i] = wire[at++]; }

  return at;
}

/* what was read of Price Limits Message is what was written, byte for byte */
static void equal_price_limits_message(const PriceLimitsMessage *read, const PriceLimitsMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->time_offset[i] == written->time_offset[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->symbol[i] == written->symbol[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->upper_price_limit[i] == written->upper_price_limit[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->lower_price_limit[i] == written->lower_price_limit[i]); }
}

/* Price Limits Message: written and read back, then read and written back */
static void check_price_limits_message(void) {
  PriceLimitsMessage sent;
  PriceLimitsMessage got;
  uint8_t wire[26];
  uint8_t again[26];

  any_price_limits_message(&sent);
  assert(encode_price_limits_message(&sent, wire, 0) == 26);
  assert(decode_price_limits_message(&got, wire, 0) == 26);
  equal_price_limits_message(&got, &sent);

  for (size_t i = 0; i < 26; i++) { wire[i] = arbitrary(); }
  assert(decode_price_limits_message(&got, wire, 0) == 26);
  assert(encode_price_limits_message(&got, again, 0) == 26);
  for (size_t i = 0; i < 26; i++) { assert(again[i] == wire[i]); }
}

/* ---- Market Snapshot Short Message: 35 bytes --------------------------------- */

/* A Market Snapshot message provides a snapshot of the price and size for the bid and ask, last trade price, total number of contracts traded, and the current trading status of a single symbol. */
typedef struct {
  uint8_t time_offset[4];             /* bytes 0 to 3 */
  uint8_t symbol[6];                  /* bytes 4 to 9 */
  uint8_t unit_timestamp[4];          /* bytes 10 to 13 */
  uint8_t bid_price_short[2];         /* bytes 14 to 15 */
  uint8_t bid_quantity_short[2];      /* bytes 16 to 17 */
  uint8_t ask_price_short[2];         /* bytes 18 to 19 */
  uint8_t ask_quantity_short[2];      /* bytes 20 to 21 */
  uint8_t last_trade_price_short[2];  /* bytes 22 to 23 */
  uint8_t last_trade_size_short[2];   /* bytes 24 to 25 */
  uint8_t last_trade_condition;       /* byte 26 */
  uint8_t total_volume[4];            /* bytes 27 to 30 */
  uint8_t trading_status;             /* byte 31 */
  uint8_t reserved_3[3];              /* bytes 32 to 34 */
} MarketSnapshotShortMessage;

/* any Market Snapshot Short Message at all: every byte one the checker chooses */
static void any_market_snapshot_short_message(MarketSnapshotShortMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->time_offset[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->symbol[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->unit_timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->bid_price_short[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->bid_quantity_short[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->ask_price_short[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->ask_quantity_short[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->last_trade_price_short[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->last_trade_size_short[i] = arbitrary(); }
  record->last_trade_condition = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->total_volume[i] = arbitrary(); }
  record->trading_status = arbitrary();
  for (size_t i = 0; i < 3; i++) { record->reserved_3[i] = arbitrary(); }
}

/* Market Snapshot Short Message to the wire: 35 bytes from at, returning where the next byte goes */
static size_t encode_market_snapshot_short_message(const MarketSnapshotShortMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->time_offset[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->symbol[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->unit_timestamp[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->bid_price_short[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->bid_quantity_short[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->ask_price_short[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->ask_quantity_short[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->last_trade_price_short[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->last_trade_size_short[i]; }
  wire[at++] = record->last_trade_condition;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->total_volume[i]; }
  wire[at++] = record->trading_status;
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->reserved_3[i]; }

  return at;
}

/* Market Snapshot Short Message off the wire: 35 bytes from at, returning where the next byte lies */
static size_t decode_market_snapshot_short_message(MarketSnapshotShortMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->time_offset[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->symbol[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->unit_timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->bid_price_short[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->bid_quantity_short[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->ask_price_short[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->ask_quantity_short[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->last_trade_price_short[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->last_trade_size_short[i] = wire[at++]; }
  record->last_trade_condition = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->total_volume[i] = wire[at++]; }
  record->trading_status = wire[at++];
  for (size_t i = 0; i < 3; i++) { record->reserved_3[i] = wire[at++]; }

  return at;
}

/* what was read of Market Snapshot Short Message is what was written, byte for byte */
static void equal_market_snapshot_short_message(const MarketSnapshotShortMessage *read, const MarketSnapshotShortMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->time_offset[i] == written->time_offset[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->symbol[i] == written->symbol[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->unit_timestamp[i] == written->unit_timestamp[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->bid_price_short[i] == written->bid_price_short[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->bid_quantity_short[i] == written->bid_quantity_short[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->ask_price_short[i] == written->ask_price_short[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->ask_quantity_short[i] == written->ask_quantity_short[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->last_trade_price_short[i] == written->last_trade_price_short[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->last_trade_size_short[i] == written->last_trade_size_short[i]); }
  assert(read->last_trade_condition == written->last_trade_condition);
  for (size_t i = 0; i < 4; i++) { assert(read->total_volume[i] == written->total_volume[i]); }
  assert(read->trading_status == written->trading_status);
  for (size_t i = 0; i < 3; i++) { assert(read->reserved_3[i] == written->reserved_3[i]); }
}

/* Market Snapshot Short Message: written and read back, then read and written back */
static void check_market_snapshot_short_message(void) {
  MarketSnapshotShortMessage sent;
  MarketSnapshotShortMessage got;
  uint8_t wire[35];
  uint8_t again[35];

  any_market_snapshot_short_message(&sent);
  assert(encode_market_snapshot_short_message(&sent, wire, 0) == 35);
  assert(decode_market_snapshot_short_message(&got, wire, 0) == 35);
  equal_market_snapshot_short_message(&got, &sent);

  for (size_t i = 0; i < 35; i++) { wire[i] = arbitrary(); }
  assert(decode_market_snapshot_short_message(&got, wire, 0) == 35);
  assert(encode_market_snapshot_short_message(&got, again, 0) == 35);
  for (size_t i = 0; i < 35; i++) { assert(again[i] == wire[i]); }
}

/* ---- Market Snapshot Long Message: 59 bytes ---------------------------------- */

/* A Market Snapshot message provides a snapshot of the price and size for the bid and ask, last trade price, total number of contracts traded, and the current trading status of a single symbol. */
typedef struct {
  uint8_t time_offset[4];            /* bytes 0 to 3 */
  uint8_t symbol[6];                 /* bytes 4 to 9 */
  uint8_t unit_timestamp[4];         /* bytes 10 to 13 */
  uint8_t bid_price_long[8];         /* bytes 14 to 21 */
  uint8_t bid_quantity_long[4];      /* bytes 22 to 25 */
  uint8_t ask_price_long[8];         /* bytes 26 to 33 */
  uint8_t ask_quantity_long[4];      /* bytes 34 to 37 */
  uint8_t last_trade_price_long[8];  /* bytes 38 to 45 */
  uint8_t last_trade_size_long[4];   /* bytes 46 to 49 */
  uint8_t last_trade_condition;      /* byte 50 */
  uint8_t total_volume[4];           /* bytes 51 to 54 */
  uint8_t trading_status;            /* byte 55 */
  uint8_t reserved_3[3];             /* bytes 56 to 58 */
} MarketSnapshotLongMessage;

/* any Market Snapshot Long Message at all: every byte one the checker chooses */
static void any_market_snapshot_long_message(MarketSnapshotLongMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->time_offset[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->symbol[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->unit_timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->bid_price_long[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->bid_quantity_long[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->ask_price_long[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->ask_quantity_long[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->last_trade_price_long[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->last_trade_size_long[i] = arbitrary(); }
  record->last_trade_condition = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->total_volume[i] = arbitrary(); }
  record->trading_status = arbitrary();
  for (size_t i = 0; i < 3; i++) { record->reserved_3[i] = arbitrary(); }
}

/* Market Snapshot Long Message to the wire: 59 bytes from at, returning where the next byte goes */
static size_t encode_market_snapshot_long_message(const MarketSnapshotLongMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->time_offset[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->symbol[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->unit_timestamp[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->bid_price_long[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->bid_quantity_long[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->ask_price_long[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->ask_quantity_long[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->last_trade_price_long[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->last_trade_size_long[i]; }
  wire[at++] = record->last_trade_condition;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->total_volume[i]; }
  wire[at++] = record->trading_status;
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->reserved_3[i]; }

  return at;
}

/* Market Snapshot Long Message off the wire: 59 bytes from at, returning where the next byte lies */
static size_t decode_market_snapshot_long_message(MarketSnapshotLongMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->time_offset[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->symbol[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->unit_timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->bid_price_long[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->bid_quantity_long[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->ask_price_long[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->ask_quantity_long[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->last_trade_price_long[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->last_trade_size_long[i] = wire[at++]; }
  record->last_trade_condition = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->total_volume[i] = wire[at++]; }
  record->trading_status = wire[at++];
  for (size_t i = 0; i < 3; i++) { record->reserved_3[i] = wire[at++]; }

  return at;
}

/* what was read of Market Snapshot Long Message is what was written, byte for byte */
static void equal_market_snapshot_long_message(const MarketSnapshotLongMessage *read, const MarketSnapshotLongMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->time_offset[i] == written->time_offset[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->symbol[i] == written->symbol[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->unit_timestamp[i] == written->unit_timestamp[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->bid_price_long[i] == written->bid_price_long[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->bid_quantity_long[i] == written->bid_quantity_long[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->ask_price_long[i] == written->ask_price_long[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->ask_quantity_long[i] == written->ask_quantity_long[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->last_trade_price_long[i] == written->last_trade_price_long[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->last_trade_size_long[i] == written->last_trade_size_long[i]); }
  assert(read->last_trade_condition == written->last_trade_condition);
  for (size_t i = 0; i < 4; i++) { assert(read->total_volume[i] == written->total_volume[i]); }
  assert(read->trading_status == written->trading_status);
  for (size_t i = 0; i < 3; i++) { assert(read->reserved_3[i] == written->reserved_3[i]); }
}

/* Market Snapshot Long Message: written and read back, then read and written back */
static void check_market_snapshot_long_message(void) {
  MarketSnapshotLongMessage sent;
  MarketSnapshotLongMessage got;
  uint8_t wire[59];
  uint8_t again[59];

  any_market_snapshot_long_message(&sent);
  assert(encode_market_snapshot_long_message(&sent, wire, 0) == 59);
  assert(decode_market_snapshot_long_message(&got, wire, 0) == 59);
  equal_market_snapshot_long_message(&got, &sent);

  for (size_t i = 0; i < 59; i++) { wire[i] = arbitrary(); }
  assert(decode_market_snapshot_long_message(&got, wire, 0) == 59);
  assert(encode_market_snapshot_long_message(&got, again, 0) == 59);
  for (size_t i = 0; i < 59; i++) { assert(again[i] == wire[i]); }
}

/* ---- Single Side Update Short Message: 15 bytes ------------------------------ */

/* Single Side Update messages provide an updated price and size for a single side of a Symbol. */
typedef struct {
  uint8_t time_offset[4];     /* bytes 0 to 3 */
  uint8_t symbol[6];          /* bytes 4 to 9 */
  uint8_t side;               /* byte 10 */
  uint8_t price_short[2];     /* bytes 11 to 12 */
  uint8_t quantity_short[2];  /* bytes 13 to 14 */
} SingleSideUpdateShortMessage;

/* any Single Side Update Short Message at all: every byte one the checker chooses */
static void any_single_side_update_short_message(SingleSideUpdateShortMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->time_offset[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->symbol[i] = arbitrary(); }
  record->side = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->price_short[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->quantity_short[i] = arbitrary(); }
}

/* Single Side Update Short Message to the wire: 15 bytes from at, returning where the next byte goes */
static size_t encode_single_side_update_short_message(const SingleSideUpdateShortMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->time_offset[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->symbol[i]; }
  wire[at++] = record->side;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->price_short[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->quantity_short[i]; }

  return at;
}

/* Single Side Update Short Message off the wire: 15 bytes from at, returning where the next byte lies */
static size_t decode_single_side_update_short_message(SingleSideUpdateShortMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->time_offset[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->symbol[i] = wire[at++]; }
  record->side = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->price_short[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->quantity_short[i] = wire[at++]; }

  return at;
}

/* what was read of Single Side Update Short Message is what was written, byte for byte */
static void equal_single_side_update_short_message(const SingleSideUpdateShortMessage *read, const SingleSideUpdateShortMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->time_offset[i] == written->time_offset[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->symbol[i] == written->symbol[i]); }
  assert(read->side == written->side);
  for (size_t i = 0; i < 2; i++) { assert(read->price_short[i] == written->price_short[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->quantity_short[i] == written->quantity_short[i]); }
}

/* Single Side Update Short Message: written and read back, then read and written back */
static void check_single_side_update_short_message(void) {
  SingleSideUpdateShortMessage sent;
  SingleSideUpdateShortMessage got;
  uint8_t wire[15];
  uint8_t again[15];

  any_single_side_update_short_message(&sent);
  assert(encode_single_side_update_short_message(&sent, wire, 0) == 15);
  assert(decode_single_side_update_short_message(&got, wire, 0) == 15);
  equal_single_side_update_short_message(&got, &sent);

  for (size_t i = 0; i < 15; i++) { wire[i] = arbitrary(); }
  assert(decode_single_side_update_short_message(&got, wire, 0) == 15);
  assert(encode_single_side_update_short_message(&got, again, 0) == 15);
  for (size_t i = 0; i < 15; i++) { assert(again[i] == wire[i]); }
}

/* ---- Single Side Update Long Message: 23 bytes ------------------------------- */

/* Single Side Update messages provide an updated price and size for a single side of a Symbol. */
typedef struct {
  uint8_t time_offset[4];    /* bytes 0 to 3 */
  uint8_t symbol[6];         /* bytes 4 to 9 */
  uint8_t side;              /* byte 10 */
  uint8_t price_long[8];     /* bytes 11 to 18 */
  uint8_t quantity_long[4];  /* bytes 19 to 22 */
} SingleSideUpdateLongMessage;

/* any Single Side Update Long Message at all: every byte one the checker chooses */
static void any_single_side_update_long_message(SingleSideUpdateLongMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->time_offset[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->symbol[i] = arbitrary(); }
  record->side = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->price_long[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->quantity_long[i] = arbitrary(); }
}

/* Single Side Update Long Message to the wire: 23 bytes from at, returning where the next byte goes */
static size_t encode_single_side_update_long_message(const SingleSideUpdateLongMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->time_offset[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->symbol[i]; }
  wire[at++] = record->side;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price_long[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->quantity_long[i]; }

  return at;
}

/* Single Side Update Long Message off the wire: 23 bytes from at, returning where the next byte lies */
static size_t decode_single_side_update_long_message(SingleSideUpdateLongMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->time_offset[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->symbol[i] = wire[at++]; }
  record->side = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->price_long[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->quantity_long[i] = wire[at++]; }

  return at;
}

/* what was read of Single Side Update Long Message is what was written, byte for byte */
static void equal_single_side_update_long_message(const SingleSideUpdateLongMessage *read, const SingleSideUpdateLongMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->time_offset[i] == written->time_offset[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->symbol[i] == written->symbol[i]); }
  assert(read->side == written->side);
  for (size_t i = 0; i < 8; i++) { assert(read->price_long[i] == written->price_long[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->quantity_long[i] == written->quantity_long[i]); }
}

/* Single Side Update Long Message: written and read back, then read and written back */
static void check_single_side_update_long_message(void) {
  SingleSideUpdateLongMessage sent;
  SingleSideUpdateLongMessage got;
  uint8_t wire[23];
  uint8_t again[23];

  any_single_side_update_long_message(&sent);
  assert(encode_single_side_update_long_message(&sent, wire, 0) == 23);
  assert(decode_single_side_update_long_message(&got, wire, 0) == 23);
  equal_single_side_update_long_message(&got, &sent);

  for (size_t i = 0; i < 23; i++) { wire[i] = arbitrary(); }
  assert(decode_single_side_update_long_message(&got, wire, 0) == 23);
  assert(encode_single_side_update_long_message(&got, again, 0) == 23);
  for (size_t i = 0; i < 23; i++) { assert(again[i] == wire[i]); }
}

/* ---- Two Side Update Short Message: 18 bytes --------------------------------- */

/* Two Side Update messages provide an updated price and size for both sides of a Symbol. */
typedef struct {
  uint8_t time_offset[4];         /* bytes 0 to 3 */
  uint8_t symbol[6];              /* bytes 4 to 9 */
  uint8_t bid_price_short[2];     /* bytes 10 to 11 */
  uint8_t bid_quantity_short[2];  /* bytes 12 to 13 */
  uint8_t ask_price_short[2];     /* bytes 14 to 15 */
  uint8_t ask_quantity_short[2];  /* bytes 16 to 17 */
} TwoSideUpdateShortMessage;

/* any Two Side Update Short Message at all: every byte one the checker chooses */
static void any_two_side_update_short_message(TwoSideUpdateShortMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->time_offset[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->symbol[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->bid_price_short[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->bid_quantity_short[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->ask_price_short[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->ask_quantity_short[i] = arbitrary(); }
}

/* Two Side Update Short Message to the wire: 18 bytes from at, returning where the next byte goes */
static size_t encode_two_side_update_short_message(const TwoSideUpdateShortMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->time_offset[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->symbol[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->bid_price_short[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->bid_quantity_short[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->ask_price_short[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->ask_quantity_short[i]; }

  return at;
}

/* Two Side Update Short Message off the wire: 18 bytes from at, returning where the next byte lies */
static size_t decode_two_side_update_short_message(TwoSideUpdateShortMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->time_offset[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->symbol[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->bid_price_short[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->bid_quantity_short[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->ask_price_short[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->ask_quantity_short[i] = wire[at++]; }

  return at;
}

/* what was read of Two Side Update Short Message is what was written, byte for byte */
static void equal_two_side_update_short_message(const TwoSideUpdateShortMessage *read, const TwoSideUpdateShortMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->time_offset[i] == written->time_offset[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->symbol[i] == written->symbol[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->bid_price_short[i] == written->bid_price_short[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->bid_quantity_short[i] == written->bid_quantity_short[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->ask_price_short[i] == written->ask_price_short[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->ask_quantity_short[i] == written->ask_quantity_short[i]); }
}

/* Two Side Update Short Message: written and read back, then read and written back */
static void check_two_side_update_short_message(void) {
  TwoSideUpdateShortMessage sent;
  TwoSideUpdateShortMessage got;
  uint8_t wire[18];
  uint8_t again[18];

  any_two_side_update_short_message(&sent);
  assert(encode_two_side_update_short_message(&sent, wire, 0) == 18);
  assert(decode_two_side_update_short_message(&got, wire, 0) == 18);
  equal_two_side_update_short_message(&got, &sent);

  for (size_t i = 0; i < 18; i++) { wire[i] = arbitrary(); }
  assert(decode_two_side_update_short_message(&got, wire, 0) == 18);
  assert(encode_two_side_update_short_message(&got, again, 0) == 18);
  for (size_t i = 0; i < 18; i++) { assert(again[i] == wire[i]); }
}

/* ---- Two Side Update Long Message: 34 bytes ---------------------------------- */

/* Two Side Update messages provide an updated price and size for both sides of a Symbol. */
typedef struct {
  uint8_t time_offset[4];        /* bytes 0 to 3 */
  uint8_t symbol[6];             /* bytes 4 to 9 */
  uint8_t bid_price_long[8];     /* bytes 10 to 17 */
  uint8_t bid_quantity_long[4];  /* bytes 18 to 21 */
  uint8_t ask_price_long[8];     /* bytes 22 to 29 */
  uint8_t ask_quantity_long[4];  /* bytes 30 to 33 */
} TwoSideUpdateLongMessage;

/* any Two Side Update Long Message at all: every byte one the checker chooses */
static void any_two_side_update_long_message(TwoSideUpdateLongMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->time_offset[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->symbol[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->bid_price_long[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->bid_quantity_long[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->ask_price_long[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->ask_quantity_long[i] = arbitrary(); }
}

/* Two Side Update Long Message to the wire: 34 bytes from at, returning where the next byte goes */
static size_t encode_two_side_update_long_message(const TwoSideUpdateLongMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->time_offset[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->symbol[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->bid_price_long[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->bid_quantity_long[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->ask_price_long[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->ask_quantity_long[i]; }

  return at;
}

/* Two Side Update Long Message off the wire: 34 bytes from at, returning where the next byte lies */
static size_t decode_two_side_update_long_message(TwoSideUpdateLongMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->time_offset[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->symbol[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->bid_price_long[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->bid_quantity_long[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->ask_price_long[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->ask_quantity_long[i] = wire[at++]; }

  return at;
}

/* what was read of Two Side Update Long Message is what was written, byte for byte */
static void equal_two_side_update_long_message(const TwoSideUpdateLongMessage *read, const TwoSideUpdateLongMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->time_offset[i] == written->time_offset[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->symbol[i] == written->symbol[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->bid_price_long[i] == written->bid_price_long[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->bid_quantity_long[i] == written->bid_quantity_long[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->ask_price_long[i] == written->ask_price_long[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->ask_quantity_long[i] == written->ask_quantity_long[i]); }
}

/* Two Side Update Long Message: written and read back, then read and written back */
static void check_two_side_update_long_message(void) {
  TwoSideUpdateLongMessage sent;
  TwoSideUpdateLongMessage got;
  uint8_t wire[34];
  uint8_t again[34];

  any_two_side_update_long_message(&sent);
  assert(encode_two_side_update_long_message(&sent, wire, 0) == 34);
  assert(decode_two_side_update_long_message(&got, wire, 0) == 34);
  equal_two_side_update_long_message(&got, &sent);

  for (size_t i = 0; i < 34; i++) { wire[i] = arbitrary(); }
  assert(decode_two_side_update_long_message(&got, wire, 0) == 34);
  assert(encode_two_side_update_long_message(&got, again, 0) == 34);
  for (size_t i = 0; i < 34; i++) { assert(again[i] == wire[i]); }
}

/* ---- Top Trade Message: 35 bytes --------------------------------------------- */

/* The TOP Trade message provides information about executions of orders on the CFE book. TOP Trade messages are necessary to calculate CFE execution-based data. */
typedef struct {
  uint8_t time_offset[4];    /* bytes 0 to 3 */
  uint8_t symbol[6];         /* bytes 4 to 9 */
  uint8_t quantity_long[4];  /* bytes 10 to 13 */
  uint8_t price_long[8];     /* bytes 14 to 21 */
  uint8_t execution_id[8];   /* bytes 22 to 29 */
  uint8_t total_volume[4];   /* bytes 30 to 33 */
  uint8_t trade_condition;   /* byte 34 */
} TopTradeMessage;

/* any Top Trade Message at all: every byte one the checker chooses */
static void any_top_trade_message(TopTradeMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->time_offset[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->symbol[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->quantity_long[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->price_long[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->execution_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->total_volume[i] = arbitrary(); }
  record->trade_condition = arbitrary();
}

/* Top Trade Message to the wire: 35 bytes from at, returning where the next byte goes */
static size_t encode_top_trade_message(const TopTradeMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->time_offset[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->symbol[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->quantity_long[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price_long[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->execution_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->total_volume[i]; }
  wire[at++] = record->trade_condition;

  return at;
}

/* Top Trade Message off the wire: 35 bytes from at, returning where the next byte lies */
static size_t decode_top_trade_message(TopTradeMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->time_offset[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->symbol[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->quantity_long[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->price_long[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->execution_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->total_volume[i] = wire[at++]; }
  record->trade_condition = wire[at++];

  return at;
}

/* what was read of Top Trade Message is what was written, byte for byte */
static void equal_top_trade_message(const TopTradeMessage *read, const TopTradeMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->time_offset[i] == written->time_offset[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->symbol[i] == written->symbol[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->quantity_long[i] == written->quantity_long[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->price_long[i] == written->price_long[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->execution_id[i] == written->execution_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->total_volume[i] == written->total_volume[i]); }
  assert(read->trade_condition == written->trade_condition);
}

/* Top Trade Message: written and read back, then read and written back */
static void check_top_trade_message(void) {
  TopTradeMessage sent;
  TopTradeMessage got;
  uint8_t wire[35];
  uint8_t again[35];

  any_top_trade_message(&sent);
  assert(encode_top_trade_message(&sent, wire, 0) == 35);
  assert(decode_top_trade_message(&got, wire, 0) == 35);
  equal_top_trade_message(&got, &sent);

  for (size_t i = 0; i < 35; i++) { wire[i] = arbitrary(); }
  assert(decode_top_trade_message(&got, wire, 0) == 35);
  assert(encode_top_trade_message(&got, again, 0) == 35);
  for (size_t i = 0; i < 35; i++) { assert(again[i] == wire[i]); }
}

/* ---- Settlement Message: 23 bytes -------------------------------------------- */

/* Settlement messages are used to provide information concerning indicative, approved, or corrected daily and final settlement prices for CFE products. */
typedef struct {
  uint8_t time_offset[4];       /* bytes 0 to 3 */
  uint8_t symbol[6];            /* bytes 4 to 9 */
  uint8_t trade_date[4];        /* bytes 10 to 13 */
  uint8_t settlement_price[8];  /* bytes 14 to 21 */
  uint8_t issue;                /* byte 22 */
} SettlementMessage;

/* any Settlement Message at all: every byte one the checker chooses */
static void any_settlement_message(SettlementMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->time_offset[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->symbol[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->trade_date[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->settlement_price[i] = arbitrary(); }
  record->issue = arbitrary();
}

/* Settlement Message to the wire: 23 bytes from at, returning where the next byte goes */
static size_t encode_settlement_message(const SettlementMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->time_offset[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->symbol[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->trade_date[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->settlement_price[i]; }
  wire[at++] = record->issue;

  return at;
}

/* Settlement Message off the wire: 23 bytes from at, returning where the next byte lies */
static size_t decode_settlement_message(SettlementMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->time_offset[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->symbol[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->trade_date[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->settlement_price[i] = wire[at++]; }
  record->issue = wire[at++];

  return at;
}

/* what was read of Settlement Message is what was written, byte for byte */
static void equal_settlement_message(const SettlementMessage *read, const SettlementMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->time_offset[i] == written->time_offset[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->symbol[i] == written->symbol[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->trade_date[i] == written->trade_date[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->settlement_price[i] == written->settlement_price[i]); }
  assert(read->issue == written->issue);
}

/* Settlement Message: written and read back, then read and written back */
static void check_settlement_message(void) {
  SettlementMessage sent;
  SettlementMessage got;
  uint8_t wire[23];
  uint8_t again[23];

  any_settlement_message(&sent);
  assert(encode_settlement_message(&sent, wire, 0) == 23);
  assert(decode_settlement_message(&got, wire, 0) == 23);
  equal_settlement_message(&got, &sent);

  for (size_t i = 0; i < 23; i++) { wire[i] = arbitrary(); }
  assert(decode_settlement_message(&got, wire, 0) == 23);
  assert(encode_settlement_message(&got, again, 0) == 23);
  for (size_t i = 0; i < 23; i++) { assert(again[i] == wire[i]); }
}

/* ---- Trading Status Message: 16 bytes ---------------------------------------- */

/* The Trading Status message is used to indicate the current trading status of a Futures contract. */
typedef struct {
  uint8_t time_offset[4];  /* bytes 0 to 3 */
  uint8_t symbol[6];       /* bytes 4 to 9 */
  uint8_t reserved_2[2];   /* bytes 10 to 11 */
  uint8_t trading_status;  /* byte 12 */
  uint8_t reserved_3[3];   /* bytes 13 to 15 */
} TradingStatusMessage;

/* any Trading Status Message at all: every byte one the checker chooses */
static void any_trading_status_message(TradingStatusMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->time_offset[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->symbol[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->reserved_2[i] = arbitrary(); }
  record->trading_status = arbitrary();
  for (size_t i = 0; i < 3; i++) { record->reserved_3[i] = arbitrary(); }
}

/* Trading Status Message to the wire: 16 bytes from at, returning where the next byte goes */
static size_t encode_trading_status_message(const TradingStatusMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->time_offset[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->symbol[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->reserved_2[i]; }
  wire[at++] = record->trading_status;
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->reserved_3[i]; }

  return at;
}

/* Trading Status Message off the wire: 16 bytes from at, returning where the next byte lies */
static size_t decode_trading_status_message(TradingStatusMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->time_offset[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->symbol[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->reserved_2[i] = wire[at++]; }
  record->trading_status = wire[at++];
  for (size_t i = 0; i < 3; i++) { record->reserved_3[i] = wire[at++]; }

  return at;
}

/* what was read of Trading Status Message is what was written, byte for byte */
static void equal_trading_status_message(const TradingStatusMessage *read, const TradingStatusMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->time_offset[i] == written->time_offset[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->symbol[i] == written->symbol[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->reserved_2[i] == written->reserved_2[i]); }
  assert(read->trading_status == written->trading_status);
  for (size_t i = 0; i < 3; i++) { assert(read->reserved_3[i] == written->reserved_3[i]); }
}

/* Trading Status Message: written and read back, then read and written back */
static void check_trading_status_message(void) {
  TradingStatusMessage sent;
  TradingStatusMessage got;
  uint8_t wire[16];
  uint8_t again[16];

  any_trading_status_message(&sent);
  assert(encode_trading_status_message(&sent, wire, 0) == 16);
  assert(decode_trading_status_message(&got, wire, 0) == 16);
  equal_trading_status_message(&got, &sent);

  for (size_t i = 0; i < 16; i++) { wire[i] = arbitrary(); }
  assert(decode_trading_status_message(&got, wire, 0) == 16);
  assert(encode_trading_status_message(&got, again, 0) == 16);
  for (size_t i = 0; i < 16; i++) { assert(again[i] == wire[i]); }
}

/* ---- Open Interest Message: 18 bytes ----------------------------------------- */

/* The Open Interest message is sent to communicate a symbol's open interest, usually for the prior trading date. */
typedef struct {
  uint8_t time_offset[4];    /* bytes 0 to 3 */
  uint8_t symbol[6];         /* bytes 4 to 9 */
  uint8_t trade_date[4];     /* bytes 10 to 13 */
  uint8_t open_interest[4];  /* bytes 14 to 17 */
} OpenInterestMessage;

/* any Open Interest Message at all: every byte one the checker chooses */
static void any_open_interest_message(OpenInterestMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->time_offset[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->symbol[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->trade_date[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->open_interest[i] = arbitrary(); }
}

/* Open Interest Message to the wire: 18 bytes from at, returning where the next byte goes */
static size_t encode_open_interest_message(const OpenInterestMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->time_offset[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->symbol[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->trade_date[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->open_interest[i]; }

  return at;
}

/* Open Interest Message off the wire: 18 bytes from at, returning where the next byte lies */
static size_t decode_open_interest_message(OpenInterestMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->time_offset[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->symbol[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->trade_date[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->open_interest[i] = wire[at++]; }

  return at;
}

/* what was read of Open Interest Message is what was written, byte for byte */
static void equal_open_interest_message(const OpenInterestMessage *read, const OpenInterestMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->time_offset[i] == written->time_offset[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->symbol[i] == written->symbol[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->trade_date[i] == written->trade_date[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->open_interest[i] == written->open_interest[i]); }
}

/* Open Interest Message: written and read back, then read and written back */
static void check_open_interest_message(void) {
  OpenInterestMessage sent;
  OpenInterestMessage got;
  uint8_t wire[18];
  uint8_t again[18];

  any_open_interest_message(&sent);
  assert(encode_open_interest_message(&sent, wire, 0) == 18);
  assert(decode_open_interest_message(&got, wire, 0) == 18);
  equal_open_interest_message(&got, &sent);

  for (size_t i = 0; i < 18; i++) { wire[i] = arbitrary(); }
  assert(decode_open_interest_message(&got, wire, 0) == 18);
  assert(encode_open_interest_message(&got, again, 0) == 18);
  for (size_t i = 0; i < 18; i++) { assert(again[i] == wire[i]); }
}

/* ---- End Of Session Message: 4 bytes ----------------------------------------- */

/* The End of Session message is sent for each unit when the unit shuts down. No more sequenced messages will be delivered for this unit, but heartbeats from the unit may be received. */
typedef struct {
  uint8_t time_offset[4];  /* bytes 0 to 3 */
} EndOfSessionMessage;

/* any End Of Session Message at all: every byte one the checker chooses */
static void any_end_of_session_message(EndOfSessionMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->time_offset[i] = arbitrary(); }
}

/* End Of Session Message to the wire: 4 bytes from at, returning where the next byte goes */
static size_t encode_end_of_session_message(const EndOfSessionMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->time_offset[i]; }

  return at;
}

/* End Of Session Message off the wire: 4 bytes from at, returning where the next byte lies */
static size_t decode_end_of_session_message(EndOfSessionMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->time_offset[i] = wire[at++]; }

  return at;
}

/* what was read of End Of Session Message is what was written, byte for byte */
static void equal_end_of_session_message(const EndOfSessionMessage *read, const EndOfSessionMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->time_offset[i] == written->time_offset[i]); }
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

/* ---- What esbmc checks ------------------------------------------------------- */

/* every record of the protocol, each on its own buffers */
static void checks(void) {
  check_packet_header();
  check_message_header();
  check_time_reference_message();
  check_time_message();
  check_unit_clear_message();
  check_futures_variance_symbol_mapping_message();
  check_price_limits_message();
  check_market_snapshot_short_message();
  check_market_snapshot_long_message();
  check_single_side_update_short_message();
  check_single_side_update_long_message();
  check_two_side_update_short_message();
  check_two_side_update_long_message();
  check_top_trade_message();
  check_settlement_message();
  check_trading_status_message();
  check_open_interest_message();
  check_end_of_session_message();
}

int main(void) {
#ifdef CONCRETE
  for (pattern = 0; pattern < 4; pattern++) { checks(); }
#else
  checks();
#endif

  return 0;
}
