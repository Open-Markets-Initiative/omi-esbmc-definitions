// cboe/c1options/multicasttop/C1Options_MulticastTop_Pitch_v1_2_54.c
/*
 * Chicago Board Options Exchange Multicast Top
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

/* ---- Time Reference Message: 16 bytes ---------------------------------------- */

/* C1 Options Only. The Time Reference message is used to provide a midnight reference point for recipients of the feed. It is sent whenever the system starts up and when the system crosses a midnight boundary. All subsequent Time messages for the same unit will use the last Midnight Reference until another Time Reference message is received for that unit. The Time Reference message includes the Trade Date, so most other sequenced messages will not include that information. Time Reference messages will be included in a spin response. */
typedef struct {
  uint8_t midnight_reference[4];  /* bytes 0 to 3 */
  uint8_t time[4];                /* bytes 4 to 7 */
  uint8_t time_offset[4];         /* bytes 8 to 11 */
  uint8_t trade_date[4];          /* bytes 12 to 15 */
} TimeReferenceMessage;

/* any Time Reference Message at all: every byte one the checker chooses */
static void any_time_reference_message(TimeReferenceMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->midnight_reference[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->time[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->time_offset[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->trade_date[i] = arbitrary(); }
}

/* Time Reference Message to the wire: 16 bytes from at, returning where the next byte goes */
static size_t encode_time_reference_message(const TimeReferenceMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->midnight_reference[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->time[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->time_offset[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->trade_date[i]; }

  return at;
}

/* Time Reference Message off the wire: 16 bytes from at, returning where the next byte lies */
static size_t decode_time_reference_message(TimeReferenceMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->midnight_reference[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->time[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->time_offset[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->trade_date[i] = wire[at++]; }

  return at;
}

/* what was read of Time Reference Message is what was written, byte for byte */
static void equal_time_reference_message(const TimeReferenceMessage *read, const TimeReferenceMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->midnight_reference[i] == written->midnight_reference[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->time[i] == written->time[i]); }
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

/* A Time message is immediately generated and sent when there is a Top event for a given clock second. If there is no Top event for a given clock second, then no Time message is sent for that second. All subsequent time offset fields for the same unit will use the new Time value as the base until another Time message is received for the same unit. The Time field is the number of seconds relative to midnight Eastern Time, which is provided in the Time Reference message. On C1 only, the Time message will also include the Epoch Time field, which is the current time represented as the number of whole seconds since the Epoch (midnight January 1, 1970). */
typedef struct {
  uint8_t time[4];        /* bytes 0 to 3 */
  uint8_t epoch_time[4];  /* bytes 4 to 7 */
} TimeMessage;

/* any Time Message at all: every byte one the checker chooses */
static void any_time_message(TimeMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->time[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->epoch_time[i] = arbitrary(); }
}

/* Time Message to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_time_message(const TimeMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->time[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->epoch_time[i]; }

  return at;
}

/* Time Message off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_time_message(TimeMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->time[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->epoch_time[i] = wire[at++]; }

  return at;
}

/* what was read of Time Message is what was written, byte for byte */
static void equal_time_message(const TimeMessage *read, const TimeMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->time[i] == written->time[i]); }
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

/* The Unit Clear message instructs feed recipients to clear all market snapshots for the book in the unit specified in the Sequenced Unit Header. This message will be sent at startup each day. It would also be distributed in certain recovery events such as a data center fail-over. */
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

/* ---- Symbol Mapping Message: 36 bytes ---------------------------------------- */

/* A Symbol Mapping message is sent as an unsequenced message. One unsequenced Symbol Mapping message for each Symbol is sent in a continuous loop as bandwidth allows. */
typedef struct {
  uint8_t feed_symbol[6];    /* bytes 0 to 5 */
  uint8_t osi_symbol[21];    /* bytes 6 to 26 */
  uint8_t symbol_condition;  /* byte 27 */
  uint8_t underlying[8];     /* bytes 28 to 35 */
} SymbolMappingMessage;

/* any Symbol Mapping Message at all: every byte one the checker chooses */
static void any_symbol_mapping_message(SymbolMappingMessage *record) {
  for (size_t i = 0; i < 6; i++) { record->feed_symbol[i] = arbitrary(); }
  for (size_t i = 0; i < 21; i++) { record->osi_symbol[i] = arbitrary(); }
  record->symbol_condition = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->underlying[i] = arbitrary(); }
}

/* Symbol Mapping Message to the wire: 36 bytes from at, returning where the next byte goes */
static size_t encode_symbol_mapping_message(const SymbolMappingMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->feed_symbol[i]; }
  for (size_t i = 0; i < 21; i++) { wire[at++] = record->osi_symbol[i]; }
  wire[at++] = record->symbol_condition;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->underlying[i]; }

  return at;
}

/* Symbol Mapping Message off the wire: 36 bytes from at, returning where the next byte lies */
static size_t decode_symbol_mapping_message(SymbolMappingMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 6; i++) { record->feed_symbol[i] = wire[at++]; }
  for (size_t i = 0; i < 21; i++) { record->osi_symbol[i] = wire[at++]; }
  record->symbol_condition = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->underlying[i] = wire[at++]; }

  return at;
}

/* what was read of Symbol Mapping Message is what was written, byte for byte */
static void equal_symbol_mapping_message(const SymbolMappingMessage *read, const SymbolMappingMessage *written) {
  for (size_t i = 0; i < 6; i++) { assert(read->feed_symbol[i] == written->feed_symbol[i]); }
  for (size_t i = 0; i < 21; i++) { assert(read->osi_symbol[i] == written->osi_symbol[i]); }
  assert(read->symbol_condition == written->symbol_condition);
  for (size_t i = 0; i < 8; i++) { assert(read->underlying[i] == written->underlying[i]); }
}

/* Symbol Mapping Message: written and read back, then read and written back */
static void check_symbol_mapping_message(void) {
  SymbolMappingMessage sent;
  SymbolMappingMessage got;
  uint8_t wire[36];
  uint8_t again[36];

  any_symbol_mapping_message(&sent);
  assert(encode_symbol_mapping_message(&sent, wire, 0) == 36);
  assert(decode_symbol_mapping_message(&got, wire, 0) == 36);
  equal_symbol_mapping_message(&got, &sent);

  for (size_t i = 0; i < 36; i++) { wire[i] = arbitrary(); }
  assert(decode_symbol_mapping_message(&got, wire, 0) == 36);
  assert(encode_symbol_mapping_message(&got, again, 0) == 36);
  for (size_t i = 0; i < 36; i++) { assert(again[i] == wire[i]); }
}

/* ---- Top Trade Message: 35 bytes --------------------------------------------- */

/* The Top Trade message provides information about executions of orders on the book. Top Trade messages are necessary to calculate execution-based data. Top Trade messages do not alter the book. One or more Single Side Update Expanded or Two Side Update Expanded messages will follow a Top Trade message to reflect the updated book. The Top Trade message sends the trade price, trade quantity, execution id, and trade condition of a trade as well as the cumulative volume for the trading session. The Trade Condition value of X (Trade Break) is sent whenever an execution is broken. Trade breaks will contain the Symbol, Quantity, Price, and Execution Id of the original trade. */
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

/* ---- Options Auction Update Message: 62 bytes -------------------------------- */

/* Options Auction Update messages are used to disseminate price and size information and Composite Market bid and offer prices during Opening and Re-Opening (halt) auctions. The Auction Update messages are sent every five seconds during an opening period. */
typedef struct {
  uint8_t time_offset[4];                   /* bytes 0 to 3 */
  uint8_t expanded_symbol[8];               /* bytes 4 to 11 */
  uint8_t auction_type;                     /* byte 12 */
  uint8_t reference_price[8];               /* bytes 13 to 20 */
  uint8_t buy_contracts[4];                 /* bytes 21 to 24 */
  uint8_t sell_contracts[4];                /* bytes 25 to 28 */
  uint8_t indicative_price[8];              /* bytes 29 to 36 */
  uint8_t auction_only_price[8];            /* bytes 37 to 44 */
  uint8_t opening_condition;                /* byte 45 */
  uint8_t composite_market_bid_price[8];    /* bytes 46 to 53 */
  uint8_t composite_market_offer_price[8];  /* bytes 54 to 61 */
} OptionsAuctionUpdateMessage;

/* any Options Auction Update Message at all: every byte one the checker chooses */
static void any_options_auction_update_message(OptionsAuctionUpdateMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->time_offset[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->expanded_symbol[i] = arbitrary(); }
  record->auction_type = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->reference_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->buy_contracts[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->sell_contracts[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->indicative_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->auction_only_price[i] = arbitrary(); }
  record->opening_condition = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->composite_market_bid_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->composite_market_offer_price[i] = arbitrary(); }
}

/* Options Auction Update Message to the wire: 62 bytes from at, returning where the next byte goes */
static size_t encode_options_auction_update_message(const OptionsAuctionUpdateMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->time_offset[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->expanded_symbol[i]; }
  wire[at++] = record->auction_type;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->reference_price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->buy_contracts[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->sell_contracts[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->indicative_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->auction_only_price[i]; }
  wire[at++] = record->opening_condition;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->composite_market_bid_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->composite_market_offer_price[i]; }

  return at;
}

/* Options Auction Update Message off the wire: 62 bytes from at, returning where the next byte lies */
static size_t decode_options_auction_update_message(OptionsAuctionUpdateMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->time_offset[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->expanded_symbol[i] = wire[at++]; }
  record->auction_type = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->reference_price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->buy_contracts[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->sell_contracts[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->indicative_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->auction_only_price[i] = wire[at++]; }
  record->opening_condition = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->composite_market_bid_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->composite_market_offer_price[i] = wire[at++]; }

  return at;
}

/* what was read of Options Auction Update Message is what was written, byte for byte */
static void equal_options_auction_update_message(const OptionsAuctionUpdateMessage *read, const OptionsAuctionUpdateMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->time_offset[i] == written->time_offset[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->expanded_symbol[i] == written->expanded_symbol[i]); }
  assert(read->auction_type == written->auction_type);
  for (size_t i = 0; i < 8; i++) { assert(read->reference_price[i] == written->reference_price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->buy_contracts[i] == written->buy_contracts[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->sell_contracts[i] == written->sell_contracts[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->indicative_price[i] == written->indicative_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->auction_only_price[i] == written->auction_only_price[i]); }
  assert(read->opening_condition == written->opening_condition);
  for (size_t i = 0; i < 8; i++) { assert(read->composite_market_bid_price[i] == written->composite_market_bid_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->composite_market_offer_price[i] == written->composite_market_offer_price[i]); }
}

/* Options Auction Update Message: written and read back, then read and written back */
static void check_options_auction_update_message(void) {
  OptionsAuctionUpdateMessage sent;
  OptionsAuctionUpdateMessage got;
  uint8_t wire[62];
  uint8_t again[62];

  any_options_auction_update_message(&sent);
  assert(encode_options_auction_update_message(&sent, wire, 0) == 62);
  assert(decode_options_auction_update_message(&got, wire, 0) == 62);
  equal_options_auction_update_message(&got, &sent);

  for (size_t i = 0; i < 62; i++) { wire[i] = arbitrary(); }
  assert(decode_options_auction_update_message(&got, wire, 0) == 62);
  assert(encode_options_auction_update_message(&got, again, 0) == 62);
  for (size_t i = 0; i < 62; i++) { assert(again[i] == wire[i]); }
}

/* ---- Auction Summary Message: 25 bytes --------------------------------------- */

/* Auction Summary messages are used to disseminate the results of an auction. An Opening or Re-Opening Auction Summary message for each symbol is sent at the conclusion of its Opening or Re-Opening auction and represents the Cboe opening price. */
typedef struct {
  uint8_t time_offset[4];    /* bytes 0 to 3 */
  uint8_t symbol_id[8];      /* bytes 4 to 11 */
  uint8_t auction_type;      /* byte 12 */
  uint8_t price_long[8];     /* bytes 13 to 20 */
  uint8_t quantity_long[4];  /* bytes 21 to 24 */
} AuctionSummaryMessage;

/* any Auction Summary Message at all: every byte one the checker chooses */
static void any_auction_summary_message(AuctionSummaryMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->time_offset[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->symbol_id[i] = arbitrary(); }
  record->auction_type = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->price_long[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->quantity_long[i] = arbitrary(); }
}

/* Auction Summary Message to the wire: 25 bytes from at, returning where the next byte goes */
static size_t encode_auction_summary_message(const AuctionSummaryMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->time_offset[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->symbol_id[i]; }
  wire[at++] = record->auction_type;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price_long[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->quantity_long[i]; }

  return at;
}

/* Auction Summary Message off the wire: 25 bytes from at, returning where the next byte lies */
static size_t decode_auction_summary_message(AuctionSummaryMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->time_offset[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->symbol_id[i] = wire[at++]; }
  record->auction_type = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->price_long[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->quantity_long[i] = wire[at++]; }

  return at;
}

/* what was read of Auction Summary Message is what was written, byte for byte */
static void equal_auction_summary_message(const AuctionSummaryMessage *read, const AuctionSummaryMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->time_offset[i] == written->time_offset[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->symbol_id[i] == written->symbol_id[i]); }
  assert(read->auction_type == written->auction_type);
  for (size_t i = 0; i < 8; i++) { assert(read->price_long[i] == written->price_long[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->quantity_long[i] == written->quantity_long[i]); }
}

/* Auction Summary Message: written and read back, then read and written back */
static void check_auction_summary_message(void) {
  AuctionSummaryMessage sent;
  AuctionSummaryMessage got;
  uint8_t wire[25];
  uint8_t again[25];

  any_auction_summary_message(&sent);
  assert(encode_auction_summary_message(&sent, wire, 0) == 25);
  assert(decode_auction_summary_message(&got, wire, 0) == 25);
  equal_auction_summary_message(&got, &sent);

  for (size_t i = 0; i < 25; i++) { wire[i] = arbitrary(); }
  assert(decode_auction_summary_message(&got, wire, 0) == 25);
  assert(encode_auction_summary_message(&got, again, 0) == 25);
  for (size_t i = 0; i < 25; i++) { assert(again[i] == wire[i]); }
}

/* ---- Trading Status Message: 16 bytes ---------------------------------------- */

/* The Trading Status message is used to indicate the current trading status of an options contract. A Trading Status message will be sent whenever a security's trading status changes. The Trading Status field will be used to represent the status of the RTH (9:30 a.m. ET - 4:15 p.m. ET) and Curb sessions. The GTH Trading Status field will be used to represent the status of series that trade during the GTH session. The GTH session runs from 8:15 p.m. to 9:25 a.m. ET for GTH-eligible Products (C1 only). */
typedef struct {
  uint8_t time_offset[4];      /* bytes 0 to 3 */
  uint8_t symbol[6];           /* bytes 4 to 9 */
  uint8_t reserved_2[2];       /* bytes 10 to 11 */
  uint8_t trading_status;      /* byte 12 */
  uint8_t reserved_1;          /* byte 13 */
  uint8_t gth_trading_status;  /* byte 14 */
  uint8_t second_reserved_1;   /* byte 15 */
} TradingStatusMessage;

/* any Trading Status Message at all: every byte one the checker chooses */
static void any_trading_status_message(TradingStatusMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->time_offset[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->symbol[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->reserved_2[i] = arbitrary(); }
  record->trading_status = arbitrary();
  record->reserved_1 = arbitrary();
  record->gth_trading_status = arbitrary();
  record->second_reserved_1 = arbitrary();
}

/* Trading Status Message to the wire: 16 bytes from at, returning where the next byte goes */
static size_t encode_trading_status_message(const TradingStatusMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->time_offset[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->symbol[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->reserved_2[i]; }
  wire[at++] = record->trading_status;
  wire[at++] = record->reserved_1;
  wire[at++] = record->gth_trading_status;
  wire[at++] = record->second_reserved_1;

  return at;
}

/* Trading Status Message off the wire: 16 bytes from at, returning where the next byte lies */
static size_t decode_trading_status_message(TradingStatusMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->time_offset[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->symbol[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->reserved_2[i] = wire[at++]; }
  record->trading_status = wire[at++];
  record->reserved_1 = wire[at++];
  record->gth_trading_status = wire[at++];
  record->second_reserved_1 = wire[at++];

  return at;
}

/* what was read of Trading Status Message is what was written, byte for byte */
static void equal_trading_status_message(const TradingStatusMessage *read, const TradingStatusMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->time_offset[i] == written->time_offset[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->symbol[i] == written->symbol[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->reserved_2[i] == written->reserved_2[i]); }
  assert(read->trading_status == written->trading_status);
  assert(read->reserved_1 == written->reserved_1);
  assert(read->gth_trading_status == written->gth_trading_status);
  assert(read->second_reserved_1 == written->second_reserved_1);
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

/* ---- Width Update Message: 17 bytes ------------------------------------------ */

/* C1, C2, and EDGX Options Only. The Width Update message is used to communicate opening quote width multiplier. This message will be sent in the event that the exchange decides to change the quote width multiplier on a per underlying basis. */
typedef struct {
  uint8_t time_offset[4];  /* bytes 0 to 3 */
  uint8_t underlying[8];   /* bytes 4 to 11 */
  uint8_t width_type;      /* byte 12 */
  uint8_t multiplier[4];   /* bytes 13 to 16 */
} WidthUpdateMessage;

/* any Width Update Message at all: every byte one the checker chooses */
static void any_width_update_message(WidthUpdateMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->time_offset[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->underlying[i] = arbitrary(); }
  record->width_type = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->multiplier[i] = arbitrary(); }
}

/* Width Update Message to the wire: 17 bytes from at, returning where the next byte goes */
static size_t encode_width_update_message(const WidthUpdateMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->time_offset[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->underlying[i]; }
  wire[at++] = record->width_type;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->multiplier[i]; }

  return at;
}

/* Width Update Message off the wire: 17 bytes from at, returning where the next byte lies */
static size_t decode_width_update_message(WidthUpdateMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->time_offset[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->underlying[i] = wire[at++]; }
  record->width_type = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->multiplier[i] = wire[at++]; }

  return at;
}

/* what was read of Width Update Message is what was written, byte for byte */
static void equal_width_update_message(const WidthUpdateMessage *read, const WidthUpdateMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->time_offset[i] == written->time_offset[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->underlying[i] == written->underlying[i]); }
  assert(read->width_type == written->width_type);
  for (size_t i = 0; i < 4; i++) { assert(read->multiplier[i] == written->multiplier[i]); }
}

/* Width Update Message: written and read back, then read and written back */
static void check_width_update_message(void) {
  WidthUpdateMessage sent;
  WidthUpdateMessage got;
  uint8_t wire[17];
  uint8_t again[17];

  any_width_update_message(&sent);
  assert(encode_width_update_message(&sent, wire, 0) == 17);
  assert(decode_width_update_message(&got, wire, 0) == 17);
  equal_width_update_message(&got, &sent);

  for (size_t i = 0; i < 17; i++) { wire[i] = arbitrary(); }
  assert(decode_width_update_message(&got, wire, 0) == 17);
  assert(encode_width_update_message(&got, again, 0) == 17);
  for (size_t i = 0; i < 17; i++) { assert(again[i] == wire[i]); }
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

/* ---- Soq Strike Range Update Message: 40 bytes ------------------------------- */

/* C1 Options Only. The SOQ Strike Range Update message is only available on the C1 Exchange. This message disseminates the minimum and maximum strike prices of the price range used to calculate the Special Opening Quote (SOQ) on a Volatility Settlement date. In the event that multiple distinct SOQ calculations occur on the same day, the applicable SOQ is differentiated by the SOQ Identifier field, which is set to the CSMi symbol on which the final settlement SOQ value is disseminated. */
typedef struct {
  uint8_t time_offset[4];         /* bytes 0 to 3 */
  uint8_t soq_identifier[20];     /* bytes 4 to 23 */
  uint8_t lower_strike_price[8];  /* bytes 24 to 31 */
  uint8_t upper_strike_price[8];  /* bytes 32 to 39 */
} SoqStrikeRangeUpdateMessage;

/* any Soq Strike Range Update Message at all: every byte one the checker chooses */
static void any_soq_strike_range_update_message(SoqStrikeRangeUpdateMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->time_offset[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->soq_identifier[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->lower_strike_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->upper_strike_price[i] = arbitrary(); }
}

/* Soq Strike Range Update Message to the wire: 40 bytes from at, returning where the next byte goes */
static size_t encode_soq_strike_range_update_message(const SoqStrikeRangeUpdateMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->time_offset[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->soq_identifier[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->lower_strike_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->upper_strike_price[i]; }

  return at;
}

/* Soq Strike Range Update Message off the wire: 40 bytes from at, returning where the next byte lies */
static size_t decode_soq_strike_range_update_message(SoqStrikeRangeUpdateMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->time_offset[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->soq_identifier[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->lower_strike_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->upper_strike_price[i] = wire[at++]; }

  return at;
}

/* what was read of Soq Strike Range Update Message is what was written, byte for byte */
static void equal_soq_strike_range_update_message(const SoqStrikeRangeUpdateMessage *read, const SoqStrikeRangeUpdateMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->time_offset[i] == written->time_offset[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->soq_identifier[i] == written->soq_identifier[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->lower_strike_price[i] == written->lower_strike_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->upper_strike_price[i] == written->upper_strike_price[i]); }
}

/* Soq Strike Range Update Message: written and read back, then read and written back */
static void check_soq_strike_range_update_message(void) {
  SoqStrikeRangeUpdateMessage sent;
  SoqStrikeRangeUpdateMessage got;
  uint8_t wire[40];
  uint8_t again[40];

  any_soq_strike_range_update_message(&sent);
  assert(encode_soq_strike_range_update_message(&sent, wire, 0) == 40);
  assert(decode_soq_strike_range_update_message(&got, wire, 0) == 40);
  equal_soq_strike_range_update_message(&got, &sent);

  for (size_t i = 0; i < 40; i++) { wire[i] = arbitrary(); }
  assert(decode_soq_strike_range_update_message(&got, wire, 0) == 40);
  assert(encode_soq_strike_range_update_message(&got, again, 0) == 40);
  for (size_t i = 0; i < 40; i++) { assert(again[i] == wire[i]); }
}

/* ---- Constituent Symbol Mapping Message: 56 bytes ---------------------------- */

/* C1 Options Only. The Constituent Symbol Mapping message is used to communicate which options series (if any) are Constituent Series in a Volatility Settlement Special Opening Quote (SOQ). The message is identical to the Symbol Mapping message with the addition of the SOQ Identifier field, which is set to the CSMi symbol on which the final settlement SOQ value is disseminated. The Constituent Symbol Mapping message is sent as an unsequenced message with one message sent for each Constituent Series in a continuous loop as bandwidth allows. */
typedef struct {
  uint8_t feed_symbol[6];      /* bytes 0 to 5 */
  uint8_t osi_symbol[21];      /* bytes 6 to 26 */
  uint8_t symbol_condition;    /* byte 27 */
  uint8_t underlying[8];       /* bytes 28 to 35 */
  uint8_t soq_identifier[20];  /* bytes 36 to 55 */
} ConstituentSymbolMappingMessage;

/* any Constituent Symbol Mapping Message at all: every byte one the checker chooses */
static void any_constituent_symbol_mapping_message(ConstituentSymbolMappingMessage *record) {
  for (size_t i = 0; i < 6; i++) { record->feed_symbol[i] = arbitrary(); }
  for (size_t i = 0; i < 21; i++) { record->osi_symbol[i] = arbitrary(); }
  record->symbol_condition = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->underlying[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->soq_identifier[i] = arbitrary(); }
}

/* Constituent Symbol Mapping Message to the wire: 56 bytes from at, returning where the next byte goes */
static size_t encode_constituent_symbol_mapping_message(const ConstituentSymbolMappingMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->feed_symbol[i]; }
  for (size_t i = 0; i < 21; i++) { wire[at++] = record->osi_symbol[i]; }
  wire[at++] = record->symbol_condition;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->underlying[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->soq_identifier[i]; }

  return at;
}

/* Constituent Symbol Mapping Message off the wire: 56 bytes from at, returning where the next byte lies */
static size_t decode_constituent_symbol_mapping_message(ConstituentSymbolMappingMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 6; i++) { record->feed_symbol[i] = wire[at++]; }
  for (size_t i = 0; i < 21; i++) { record->osi_symbol[i] = wire[at++]; }
  record->symbol_condition = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->underlying[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->soq_identifier[i] = wire[at++]; }

  return at;
}

/* what was read of Constituent Symbol Mapping Message is what was written, byte for byte */
static void equal_constituent_symbol_mapping_message(const ConstituentSymbolMappingMessage *read, const ConstituentSymbolMappingMessage *written) {
  for (size_t i = 0; i < 6; i++) { assert(read->feed_symbol[i] == written->feed_symbol[i]); }
  for (size_t i = 0; i < 21; i++) { assert(read->osi_symbol[i] == written->osi_symbol[i]); }
  assert(read->symbol_condition == written->symbol_condition);
  for (size_t i = 0; i < 8; i++) { assert(read->underlying[i] == written->underlying[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->soq_identifier[i] == written->soq_identifier[i]); }
}

/* Constituent Symbol Mapping Message: written and read back, then read and written back */
static void check_constituent_symbol_mapping_message(void) {
  ConstituentSymbolMappingMessage sent;
  ConstituentSymbolMappingMessage got;
  uint8_t wire[56];
  uint8_t again[56];

  any_constituent_symbol_mapping_message(&sent);
  assert(encode_constituent_symbol_mapping_message(&sent, wire, 0) == 56);
  assert(decode_constituent_symbol_mapping_message(&got, wire, 0) == 56);
  equal_constituent_symbol_mapping_message(&got, &sent);

  for (size_t i = 0; i < 56; i++) { wire[i] = arbitrary(); }
  assert(decode_constituent_symbol_mapping_message(&got, wire, 0) == 56);
  assert(encode_constituent_symbol_mapping_message(&got, again, 0) == 56);
  for (size_t i = 0; i < 56; i++) { assert(again[i] == wire[i]); }
}

/* ---- What esbmc checks ------------------------------------------------------- */

/* every record of the protocol, each on its own buffers */
static void checks(void) {
  check_packet_header();
  check_message_header();
  check_time_reference_message();
  check_time_message();
  check_unit_clear_message();
  check_symbol_mapping_message();
  check_top_trade_message();
  check_options_auction_update_message();
  check_auction_summary_message();
  check_trading_status_message();
  check_width_update_message();
  check_end_of_session_message();
  check_soq_strike_range_update_message();
  check_constituent_symbol_mapping_message();
}

int main(void) {
#ifdef CONCRETE
  for (pattern = 0; pattern < 4; pattern++) { checks(); }
#else
  checks();
#endif

  return 0;
}
