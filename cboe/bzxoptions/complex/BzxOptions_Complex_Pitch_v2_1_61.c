// cboe/bzxoptions/complex/BzxOptions_Complex_Pitch_v2_1_61.c
/*
 * Chicago Board Options Exchange Complex
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

/* ---- Time Message: 4 bytes --------------------------------------------------- */

/* A Time message is immediately generated and sent when there is a PITCH event for a given clock second. If there is no PITCH event for a given clock second, then no Time message is sent for that second. All subsequent time offset fields for the same unit will use the new Time value as the base until another Time message is received for the same unit. */
typedef struct {
  uint8_t time[4];  /* bytes 0 to 3 */
} TimeMessage;

/* any Time Message at all: every byte one the checker chooses */
static void any_time_message(TimeMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->time[i] = arbitrary(); }
}

/* Time Message to the wire: 4 bytes from at, returning where the next byte goes */
static size_t encode_time_message(const TimeMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->time[i]; }

  return at;
}

/* Time Message off the wire: 4 bytes from at, returning where the next byte lies */
static size_t decode_time_message(TimeMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->time[i] = wire[at++]; }

  return at;
}

/* what was read of Time Message is what was written, byte for byte */
static void equal_time_message(const TimeMessage *read, const TimeMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->time[i] == written->time[i]); }
}

/* Time Message: written and read back, then read and written back */
static void check_time_message(void) {
  TimeMessage sent;
  TimeMessage got;
  uint8_t wire[4];
  uint8_t again[4];

  any_time_message(&sent);
  assert(encode_time_message(&sent, wire, 0) == 4);
  assert(decode_time_message(&got, wire, 0) == 4);
  equal_time_message(&got, &sent);

  for (size_t i = 0; i < 4; i++) { wire[i] = arbitrary(); }
  assert(decode_time_message(&got, wire, 0) == 4);
  assert(encode_time_message(&got, again, 0) == 4);
  for (size_t i = 0; i < 4; i++) { assert(again[i] == wire[i]); }
}

/* ---- Unit Clear Message: 4 bytes --------------------------------------------- */

/* The Unit Clear message instructs feed recipients to clear all orders for the Cboe complex book in the unit specified in the Sequenced Unit Header. For Equities only, this message will be sent at startup each day. It would also be distributed in certain recovery events such as a data center fail-over. */
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

/* ---- Transaction Begin Message: 4 bytes -------------------------------------- */

/* The Transaction Begin message indicates any subsequent messages, up to the accompanying Transaction End message, are all part of the same transaction block. All PITCH messages corresponding to such an event would be included between a Transaction Begin and Transaction End. Any PITCH Message Type may be included in a transaction block and there is no guarantee that the messages apply to the same price level or even the same Symbol. Transaction Begin messages do not alter the book and can be ignored if messages are being used solely to build a book. */
typedef struct {
  uint8_t time_offset[4];  /* bytes 0 to 3 */
} TransactionBeginMessage;

/* any Transaction Begin Message at all: every byte one the checker chooses */
static void any_transaction_begin_message(TransactionBeginMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->time_offset[i] = arbitrary(); }
}

/* Transaction Begin Message to the wire: 4 bytes from at, returning where the next byte goes */
static size_t encode_transaction_begin_message(const TransactionBeginMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->time_offset[i]; }

  return at;
}

/* Transaction Begin Message off the wire: 4 bytes from at, returning where the next byte lies */
static size_t decode_transaction_begin_message(TransactionBeginMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->time_offset[i] = wire[at++]; }

  return at;
}

/* what was read of Transaction Begin Message is what was written, byte for byte */
static void equal_transaction_begin_message(const TransactionBeginMessage *read, const TransactionBeginMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->time_offset[i] == written->time_offset[i]); }
}

/* Transaction Begin Message: written and read back, then read and written back */
static void check_transaction_begin_message(void) {
  TransactionBeginMessage sent;
  TransactionBeginMessage got;
  uint8_t wire[4];
  uint8_t again[4];

  any_transaction_begin_message(&sent);
  assert(encode_transaction_begin_message(&sent, wire, 0) == 4);
  assert(decode_transaction_begin_message(&got, wire, 0) == 4);
  equal_transaction_begin_message(&got, &sent);

  for (size_t i = 0; i < 4; i++) { wire[i] = arbitrary(); }
  assert(decode_transaction_begin_message(&got, wire, 0) == 4);
  assert(encode_transaction_begin_message(&got, again, 0) == 4);
  for (size_t i = 0; i < 4; i++) { assert(again[i] == wire[i]); }
}

/* ---- Transaction End Message: 4 bytes ---------------------------------------- */

/* The Transaction End message indicates that a transaction indicated by a previous Transaction Begin message has completed. Transaction End messages do not alter the book and can be ignored if messages are being used solely to build a book. */
typedef struct {
  uint8_t time_offset[4];  /* bytes 0 to 3 */
} TransactionEndMessage;

/* any Transaction End Message at all: every byte one the checker chooses */
static void any_transaction_end_message(TransactionEndMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->time_offset[i] = arbitrary(); }
}

/* Transaction End Message to the wire: 4 bytes from at, returning where the next byte goes */
static size_t encode_transaction_end_message(const TransactionEndMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->time_offset[i]; }

  return at;
}

/* Transaction End Message off the wire: 4 bytes from at, returning where the next byte lies */
static size_t decode_transaction_end_message(TransactionEndMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->time_offset[i] = wire[at++]; }

  return at;
}

/* what was read of Transaction End Message is what was written, byte for byte */
static void equal_transaction_end_message(const TransactionEndMessage *read, const TransactionEndMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->time_offset[i] == written->time_offset[i]); }
}

/* Transaction End Message: written and read back, then read and written back */
static void check_transaction_end_message(void) {
  TransactionEndMessage sent;
  TransactionEndMessage got;
  uint8_t wire[4];
  uint8_t again[4];

  any_transaction_end_message(&sent);
  assert(encode_transaction_end_message(&sent, wire, 0) == 4);
  assert(decode_transaction_end_message(&got, wire, 0) == 4);
  equal_transaction_end_message(&got, &sent);

  for (size_t i = 0; i < 4; i++) { wire[i] = arbitrary(); }
  assert(decode_transaction_end_message(&got, wire, 0) == 4);
  assert(encode_transaction_end_message(&got, again, 0) == 4);
  for (size_t i = 0; i < 4; i++) { assert(again[i] == wire[i]); }
}

/* ---- Symbol Mapping Message: 36 bytes ---------------------------------------- */

/* A Symbol Mapping message is used to map the 6 character multicast feed symbol field to an OSI symbol and Underlying. These messages are not sequenced (sequence = 0) and are sent continuously through the day at variable rates as bandwidth allows. */
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

/* ---- Add Order Long Message: 32 bytes ---------------------------------------- */

/* An Add Order message represents a newly accepted visible order on the Cboe complex book. It includes a day-specific Order Id assigned by Cboe to the complex order. */
typedef struct {
  uint8_t time_offset[4];                  /* bytes 0 to 3 */
  uint8_t order_id[8];                     /* bytes 4 to 11 */
  uint8_t side_indicator;                  /* byte 12 */
  uint8_t quantity_long[4];                /* bytes 13 to 16 */
  uint8_t complex_instrument_id_short[6];  /* bytes 17 to 22 */
  uint8_t signed_price_long[8];            /* bytes 23 to 30 */
  uint8_t reserved_1;                      /* byte 31 */
} AddOrderLongMessage;

/* any Add Order Long Message at all: every byte one the checker chooses */
static void any_add_order_long_message(AddOrderLongMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->time_offset[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = arbitrary(); }
  record->side_indicator = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->quantity_long[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->complex_instrument_id_short[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->signed_price_long[i] = arbitrary(); }
  record->reserved_1 = arbitrary();
}

/* Add Order Long Message to the wire: 32 bytes from at, returning where the next byte goes */
static size_t encode_add_order_long_message(const AddOrderLongMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->time_offset[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_id[i]; }
  wire[at++] = record->side_indicator;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->quantity_long[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->complex_instrument_id_short[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->signed_price_long[i]; }
  wire[at++] = record->reserved_1;

  return at;
}

/* Add Order Long Message off the wire: 32 bytes from at, returning where the next byte lies */
static size_t decode_add_order_long_message(AddOrderLongMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->time_offset[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = wire[at++]; }
  record->side_indicator = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->quantity_long[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->complex_instrument_id_short[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->signed_price_long[i] = wire[at++]; }
  record->reserved_1 = wire[at++];

  return at;
}

/* what was read of Add Order Long Message is what was written, byte for byte */
static void equal_add_order_long_message(const AddOrderLongMessage *read, const AddOrderLongMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->time_offset[i] == written->time_offset[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->order_id[i] == written->order_id[i]); }
  assert(read->side_indicator == written->side_indicator);
  for (size_t i = 0; i < 4; i++) { assert(read->quantity_long[i] == written->quantity_long[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->complex_instrument_id_short[i] == written->complex_instrument_id_short[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->signed_price_long[i] == written->signed_price_long[i]); }
  assert(read->reserved_1 == written->reserved_1);
}

/* Add Order Long Message: written and read back, then read and written back */
static void check_add_order_long_message(void) {
  AddOrderLongMessage sent;
  AddOrderLongMessage got;
  uint8_t wire[32];
  uint8_t again[32];

  any_add_order_long_message(&sent);
  assert(encode_add_order_long_message(&sent, wire, 0) == 32);
  assert(decode_add_order_long_message(&got, wire, 0) == 32);
  equal_add_order_long_message(&got, &sent);

  for (size_t i = 0; i < 32; i++) { wire[i] = arbitrary(); }
  assert(decode_add_order_long_message(&got, wire, 0) == 32);
  assert(encode_add_order_long_message(&got, again, 0) == 32);
  for (size_t i = 0; i < 32; i++) { assert(again[i] == wire[i]); }
}

/* ---- Add Order Short Message: 24 bytes --------------------------------------- */

/* An Add Order Short message represents a newly accepted visible order on the Cboe complex book whose Price fits in a Binary Signed Short Price and Quantity fits in an unsigned 16-bit integer. */
typedef struct {
  uint8_t time_offset[4];                  /* bytes 0 to 3 */
  uint8_t order_id[8];                     /* bytes 4 to 11 */
  uint8_t side_indicator;                  /* byte 12 */
  uint8_t quantity_short[2];               /* bytes 13 to 14 */
  uint8_t complex_instrument_id_short[6];  /* bytes 15 to 20 */
  uint8_t signed_price_short[2];           /* bytes 21 to 22 */
  uint8_t reserved_1;                      /* byte 23 */
} AddOrderShortMessage;

/* any Add Order Short Message at all: every byte one the checker chooses */
static void any_add_order_short_message(AddOrderShortMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->time_offset[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = arbitrary(); }
  record->side_indicator = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->quantity_short[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->complex_instrument_id_short[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->signed_price_short[i] = arbitrary(); }
  record->reserved_1 = arbitrary();
}

/* Add Order Short Message to the wire: 24 bytes from at, returning where the next byte goes */
static size_t encode_add_order_short_message(const AddOrderShortMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->time_offset[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_id[i]; }
  wire[at++] = record->side_indicator;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->quantity_short[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->complex_instrument_id_short[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->signed_price_short[i]; }
  wire[at++] = record->reserved_1;

  return at;
}

/* Add Order Short Message off the wire: 24 bytes from at, returning where the next byte lies */
static size_t decode_add_order_short_message(AddOrderShortMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->time_offset[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = wire[at++]; }
  record->side_indicator = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->quantity_short[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->complex_instrument_id_short[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->signed_price_short[i] = wire[at++]; }
  record->reserved_1 = wire[at++];

  return at;
}

/* what was read of Add Order Short Message is what was written, byte for byte */
static void equal_add_order_short_message(const AddOrderShortMessage *read, const AddOrderShortMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->time_offset[i] == written->time_offset[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->order_id[i] == written->order_id[i]); }
  assert(read->side_indicator == written->side_indicator);
  for (size_t i = 0; i < 2; i++) { assert(read->quantity_short[i] == written->quantity_short[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->complex_instrument_id_short[i] == written->complex_instrument_id_short[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->signed_price_short[i] == written->signed_price_short[i]); }
  assert(read->reserved_1 == written->reserved_1);
}

/* Add Order Short Message: written and read back, then read and written back */
static void check_add_order_short_message(void) {
  AddOrderShortMessage sent;
  AddOrderShortMessage got;
  uint8_t wire[24];
  uint8_t again[24];

  any_add_order_short_message(&sent);
  assert(encode_add_order_short_message(&sent, wire, 0) == 24);
  assert(decode_add_order_short_message(&got, wire, 0) == 24);
  equal_add_order_short_message(&got, &sent);

  for (size_t i = 0; i < 24; i++) { wire[i] = arbitrary(); }
  assert(decode_add_order_short_message(&got, wire, 0) == 24);
  assert(encode_add_order_short_message(&got, again, 0) == 24);
  for (size_t i = 0; i < 24; i++) { assert(again[i] == wire[i]); }
}

/* ---- Add Order Expanded Message: 48 bytes ------------------------------------ */

/* An Add Order Expanded message represents a newly accepted visible order on the Cboe complex book and carries additional attribution fields (Participant ID, Customer Indicator, Client ID). */
typedef struct {
  uint8_t time_offset[4];                 /* bytes 0 to 3 */
  uint8_t order_id[8];                    /* bytes 4 to 11 */
  uint8_t side_indicator;                 /* byte 12 */
  uint8_t quantity_long[4];               /* bytes 13 to 16 */
  uint8_t complex_instrument_id_long[8];  /* bytes 17 to 24 */
  uint8_t signed_price_long[8];           /* bytes 25 to 32 */
  uint8_t reserved_1;                     /* byte 33 */
  uint8_t participant_id[4];              /* bytes 34 to 37 */
  uint8_t customer_indicator;             /* byte 38 */
  uint8_t client_id[4];                   /* bytes 39 to 42 */
  uint8_t reserved_5[5];                  /* bytes 43 to 47 */
} AddOrderExpandedMessage;

/* any Add Order Expanded Message at all: every byte one the checker chooses */
static void any_add_order_expanded_message(AddOrderExpandedMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->time_offset[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = arbitrary(); }
  record->side_indicator = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->quantity_long[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->complex_instrument_id_long[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->signed_price_long[i] = arbitrary(); }
  record->reserved_1 = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->participant_id[i] = arbitrary(); }
  record->customer_indicator = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->client_id[i] = arbitrary(); }
  for (size_t i = 0; i < 5; i++) { record->reserved_5[i] = arbitrary(); }
}

/* Add Order Expanded Message to the wire: 48 bytes from at, returning where the next byte goes */
static size_t encode_add_order_expanded_message(const AddOrderExpandedMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->time_offset[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_id[i]; }
  wire[at++] = record->side_indicator;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->quantity_long[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->complex_instrument_id_long[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->signed_price_long[i]; }
  wire[at++] = record->reserved_1;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->participant_id[i]; }
  wire[at++] = record->customer_indicator;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->client_id[i]; }
  for (size_t i = 0; i < 5; i++) { wire[at++] = record->reserved_5[i]; }

  return at;
}

/* Add Order Expanded Message off the wire: 48 bytes from at, returning where the next byte lies */
static size_t decode_add_order_expanded_message(AddOrderExpandedMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->time_offset[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = wire[at++]; }
  record->side_indicator = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->quantity_long[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->complex_instrument_id_long[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->signed_price_long[i] = wire[at++]; }
  record->reserved_1 = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->participant_id[i] = wire[at++]; }
  record->customer_indicator = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->client_id[i] = wire[at++]; }
  for (size_t i = 0; i < 5; i++) { record->reserved_5[i] = wire[at++]; }

  return at;
}

/* what was read of Add Order Expanded Message is what was written, byte for byte */
static void equal_add_order_expanded_message(const AddOrderExpandedMessage *read, const AddOrderExpandedMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->time_offset[i] == written->time_offset[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->order_id[i] == written->order_id[i]); }
  assert(read->side_indicator == written->side_indicator);
  for (size_t i = 0; i < 4; i++) { assert(read->quantity_long[i] == written->quantity_long[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->complex_instrument_id_long[i] == written->complex_instrument_id_long[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->signed_price_long[i] == written->signed_price_long[i]); }
  assert(read->reserved_1 == written->reserved_1);
  for (size_t i = 0; i < 4; i++) { assert(read->participant_id[i] == written->participant_id[i]); }
  assert(read->customer_indicator == written->customer_indicator);
  for (size_t i = 0; i < 4; i++) { assert(read->client_id[i] == written->client_id[i]); }
  for (size_t i = 0; i < 5; i++) { assert(read->reserved_5[i] == written->reserved_5[i]); }
}

/* Add Order Expanded Message: written and read back, then read and written back */
static void check_add_order_expanded_message(void) {
  AddOrderExpandedMessage sent;
  AddOrderExpandedMessage got;
  uint8_t wire[48];
  uint8_t again[48];

  any_add_order_expanded_message(&sent);
  assert(encode_add_order_expanded_message(&sent, wire, 0) == 48);
  assert(decode_add_order_expanded_message(&got, wire, 0) == 48);
  equal_add_order_expanded_message(&got, &sent);

  for (size_t i = 0; i < 48; i++) { wire[i] = arbitrary(); }
  assert(decode_add_order_expanded_message(&got, wire, 0) == 48);
  assert(encode_add_order_expanded_message(&got, again, 0) == 48);
  for (size_t i = 0; i < 48; i++) { assert(again[i] == wire[i]); }
}

/* ---- Order Executed Message: 25 bytes ---------------------------------------- */

/* Order Executed messages are sent when a visible complex order on the Cboe complex book is executed in whole or in part. The execution price equals the limit order price found in the original Add Order message or the limit order price in the latest Modify Order message referencing the Order Id. */
typedef struct {
  uint8_t time_offset[4];        /* bytes 0 to 3 */
  uint8_t order_id[8];           /* bytes 4 to 11 */
  uint8_t executed_quantity[4];  /* bytes 12 to 15 */
  uint8_t execution_id[8];       /* bytes 16 to 23 */
  uint8_t trade_condition;       /* byte 24 */
} OrderExecutedMessage;

/* any Order Executed Message at all: every byte one the checker chooses */
static void any_order_executed_message(OrderExecutedMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->time_offset[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->executed_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->execution_id[i] = arbitrary(); }
  record->trade_condition = arbitrary();
}

/* Order Executed Message to the wire: 25 bytes from at, returning where the next byte goes */
static size_t encode_order_executed_message(const OrderExecutedMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->time_offset[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->executed_quantity[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->execution_id[i]; }
  wire[at++] = record->trade_condition;

  return at;
}

/* Order Executed Message off the wire: 25 bytes from at, returning where the next byte lies */
static size_t decode_order_executed_message(OrderExecutedMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->time_offset[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->executed_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->execution_id[i] = wire[at++]; }
  record->trade_condition = wire[at++];

  return at;
}

/* what was read of Order Executed Message is what was written, byte for byte */
static void equal_order_executed_message(const OrderExecutedMessage *read, const OrderExecutedMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->time_offset[i] == written->time_offset[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->order_id[i] == written->order_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->executed_quantity[i] == written->executed_quantity[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->execution_id[i] == written->execution_id[i]); }
  assert(read->trade_condition == written->trade_condition);
}

/* Order Executed Message: written and read back, then read and written back */
static void check_order_executed_message(void) {
  OrderExecutedMessage sent;
  OrderExecutedMessage got;
  uint8_t wire[25];
  uint8_t again[25];

  any_order_executed_message(&sent);
  assert(encode_order_executed_message(&sent, wire, 0) == 25);
  assert(decode_order_executed_message(&got, wire, 0) == 25);
  equal_order_executed_message(&got, &sent);

  for (size_t i = 0; i < 25; i++) { wire[i] = arbitrary(); }
  assert(decode_order_executed_message(&got, wire, 0) == 25);
  assert(encode_order_executed_message(&got, again, 0) == 25);
  for (size_t i = 0; i < 25; i++) { assert(again[i] == wire[i]); }
}

/* ---- Order Executed At Price Size Message: 37 bytes -------------------------- */

/* Order Execution at Price/Size messages are sent when a complex order on the Cboe complex book is executed in whole or in part at a different price than the limit price on the original Add Order message or the limit order price in the latest Modify Order message referencing the Order Id. If the Remaining Quantity field contains a 0 the complex order should be completely removed from the complex book. Order Execution at Price/Size messages may also be sent in the event the existing size for Order Id is not equal to Executed Quantity + Remaining Quantity. In this case the complex order should be prioritized the same as a new complex order. */
typedef struct {
  uint8_t time_offset[4];         /* bytes 0 to 3 */
  uint8_t order_id[8];            /* bytes 4 to 11 */
  uint8_t executed_quantity[4];   /* bytes 12 to 15 */
  uint8_t remaining_quantity[4];  /* bytes 16 to 19 */
  uint8_t execution_id[8];        /* bytes 20 to 27 */
  uint8_t signed_price_long[8];   /* bytes 28 to 35 */
  uint8_t trade_condition;        /* byte 36 */
} OrderExecutedAtPriceSizeMessage;

/* any Order Executed At Price Size Message at all: every byte one the checker chooses */
static void any_order_executed_at_price_size_message(OrderExecutedAtPriceSizeMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->time_offset[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->executed_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->remaining_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->execution_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->signed_price_long[i] = arbitrary(); }
  record->trade_condition = arbitrary();
}

/* Order Executed At Price Size Message to the wire: 37 bytes from at, returning where the next byte goes */
static size_t encode_order_executed_at_price_size_message(const OrderExecutedAtPriceSizeMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->time_offset[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->executed_quantity[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->remaining_quantity[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->execution_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->signed_price_long[i]; }
  wire[at++] = record->trade_condition;

  return at;
}

/* Order Executed At Price Size Message off the wire: 37 bytes from at, returning where the next byte lies */
static size_t decode_order_executed_at_price_size_message(OrderExecutedAtPriceSizeMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->time_offset[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->executed_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->remaining_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->execution_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->signed_price_long[i] = wire[at++]; }
  record->trade_condition = wire[at++];

  return at;
}

/* what was read of Order Executed At Price Size Message is what was written, byte for byte */
static void equal_order_executed_at_price_size_message(const OrderExecutedAtPriceSizeMessage *read, const OrderExecutedAtPriceSizeMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->time_offset[i] == written->time_offset[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->order_id[i] == written->order_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->executed_quantity[i] == written->executed_quantity[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->remaining_quantity[i] == written->remaining_quantity[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->execution_id[i] == written->execution_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->signed_price_long[i] == written->signed_price_long[i]); }
  assert(read->trade_condition == written->trade_condition);
}

/* Order Executed At Price Size Message: written and read back, then read and written back */
static void check_order_executed_at_price_size_message(void) {
  OrderExecutedAtPriceSizeMessage sent;
  OrderExecutedAtPriceSizeMessage got;
  uint8_t wire[37];
  uint8_t again[37];

  any_order_executed_at_price_size_message(&sent);
  assert(encode_order_executed_at_price_size_message(&sent, wire, 0) == 37);
  assert(decode_order_executed_at_price_size_message(&got, wire, 0) == 37);
  equal_order_executed_at_price_size_message(&got, &sent);

  for (size_t i = 0; i < 37; i++) { wire[i] = arbitrary(); }
  assert(decode_order_executed_at_price_size_message(&got, wire, 0) == 37);
  assert(encode_order_executed_at_price_size_message(&got, again, 0) == 37);
  for (size_t i = 0; i < 37; i++) { assert(again[i] == wire[i]); }
}

/* ---- Reduce Size Long Message: 16 bytes -------------------------------------- */

/* Reduce Size messages are sent when a complex order on the Cboe complex book is partially reduced. */
typedef struct {
  uint8_t time_offset[4];             /* bytes 0 to 3 */
  uint8_t order_id[8];                /* bytes 4 to 11 */
  uint8_t canceled_quantity_long[4];  /* bytes 12 to 15 */
} ReduceSizeLongMessage;

/* any Reduce Size Long Message at all: every byte one the checker chooses */
static void any_reduce_size_long_message(ReduceSizeLongMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->time_offset[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->canceled_quantity_long[i] = arbitrary(); }
}

/* Reduce Size Long Message to the wire: 16 bytes from at, returning where the next byte goes */
static size_t encode_reduce_size_long_message(const ReduceSizeLongMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->time_offset[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->canceled_quantity_long[i]; }

  return at;
}

/* Reduce Size Long Message off the wire: 16 bytes from at, returning where the next byte lies */
static size_t decode_reduce_size_long_message(ReduceSizeLongMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->time_offset[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->canceled_quantity_long[i] = wire[at++]; }

  return at;
}

/* what was read of Reduce Size Long Message is what was written, byte for byte */
static void equal_reduce_size_long_message(const ReduceSizeLongMessage *read, const ReduceSizeLongMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->time_offset[i] == written->time_offset[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->order_id[i] == written->order_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->canceled_quantity_long[i] == written->canceled_quantity_long[i]); }
}

/* Reduce Size Long Message: written and read back, then read and written back */
static void check_reduce_size_long_message(void) {
  ReduceSizeLongMessage sent;
  ReduceSizeLongMessage got;
  uint8_t wire[16];
  uint8_t again[16];

  any_reduce_size_long_message(&sent);
  assert(encode_reduce_size_long_message(&sent, wire, 0) == 16);
  assert(decode_reduce_size_long_message(&got, wire, 0) == 16);
  equal_reduce_size_long_message(&got, &sent);

  for (size_t i = 0; i < 16; i++) { wire[i] = arbitrary(); }
  assert(decode_reduce_size_long_message(&got, wire, 0) == 16);
  assert(encode_reduce_size_long_message(&got, again, 0) == 16);
  for (size_t i = 0; i < 16; i++) { assert(again[i] == wire[i]); }
}

/* ---- Reduce Size Short Message: 14 bytes ------------------------------------- */

/* Reduce Size Short messages are sent when a complex order on the Cboe complex book is partially reduced and the canceled quantity fits in an unsigned 16-bit integer. */
typedef struct {
  uint8_t time_offset[4];              /* bytes 0 to 3 */
  uint8_t order_id[8];                 /* bytes 4 to 11 */
  uint8_t canceled_quantity_short[2];  /* bytes 12 to 13 */
} ReduceSizeShortMessage;

/* any Reduce Size Short Message at all: every byte one the checker chooses */
static void any_reduce_size_short_message(ReduceSizeShortMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->time_offset[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->canceled_quantity_short[i] = arbitrary(); }
}

/* Reduce Size Short Message to the wire: 14 bytes from at, returning where the next byte goes */
static size_t encode_reduce_size_short_message(const ReduceSizeShortMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->time_offset[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_id[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->canceled_quantity_short[i]; }

  return at;
}

/* Reduce Size Short Message off the wire: 14 bytes from at, returning where the next byte lies */
static size_t decode_reduce_size_short_message(ReduceSizeShortMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->time_offset[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->canceled_quantity_short[i] = wire[at++]; }

  return at;
}

/* what was read of Reduce Size Short Message is what was written, byte for byte */
static void equal_reduce_size_short_message(const ReduceSizeShortMessage *read, const ReduceSizeShortMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->time_offset[i] == written->time_offset[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->order_id[i] == written->order_id[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->canceled_quantity_short[i] == written->canceled_quantity_short[i]); }
}

/* Reduce Size Short Message: written and read back, then read and written back */
static void check_reduce_size_short_message(void) {
  ReduceSizeShortMessage sent;
  ReduceSizeShortMessage got;
  uint8_t wire[14];
  uint8_t again[14];

  any_reduce_size_short_message(&sent);
  assert(encode_reduce_size_short_message(&sent, wire, 0) == 14);
  assert(decode_reduce_size_short_message(&got, wire, 0) == 14);
  equal_reduce_size_short_message(&got, &sent);

  for (size_t i = 0; i < 14; i++) { wire[i] = arbitrary(); }
  assert(decode_reduce_size_short_message(&got, wire, 0) == 14);
  assert(encode_reduce_size_short_message(&got, again, 0) == 14);
  for (size_t i = 0; i < 14; i++) { assert(again[i] == wire[i]); }
}

/* ---- Modify Order Long Message: 25 bytes ------------------------------------- */

/* The Modify Order message is sent whenever an open complex order is visibly modified. The Order Id refers to the Order Id of the original Add Order message. Note that Modify Order messages that appear to be "no ops" (i.e. they do not appear to modify any relevant fields) will still lose priority. */
typedef struct {
  uint8_t time_offset[4];        /* bytes 0 to 3 */
  uint8_t order_id[8];           /* bytes 4 to 11 */
  uint8_t quantity_long[4];      /* bytes 12 to 15 */
  uint8_t signed_price_long[8];  /* bytes 16 to 23 */
  uint8_t reserved_1;            /* byte 24 */
} ModifyOrderLongMessage;

/* any Modify Order Long Message at all: every byte one the checker chooses */
static void any_modify_order_long_message(ModifyOrderLongMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->time_offset[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->quantity_long[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->signed_price_long[i] = arbitrary(); }
  record->reserved_1 = arbitrary();
}

/* Modify Order Long Message to the wire: 25 bytes from at, returning where the next byte goes */
static size_t encode_modify_order_long_message(const ModifyOrderLongMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->time_offset[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->quantity_long[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->signed_price_long[i]; }
  wire[at++] = record->reserved_1;

  return at;
}

/* Modify Order Long Message off the wire: 25 bytes from at, returning where the next byte lies */
static size_t decode_modify_order_long_message(ModifyOrderLongMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->time_offset[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->quantity_long[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->signed_price_long[i] = wire[at++]; }
  record->reserved_1 = wire[at++];

  return at;
}

/* what was read of Modify Order Long Message is what was written, byte for byte */
static void equal_modify_order_long_message(const ModifyOrderLongMessage *read, const ModifyOrderLongMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->time_offset[i] == written->time_offset[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->order_id[i] == written->order_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->quantity_long[i] == written->quantity_long[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->signed_price_long[i] == written->signed_price_long[i]); }
  assert(read->reserved_1 == written->reserved_1);
}

/* Modify Order Long Message: written and read back, then read and written back */
static void check_modify_order_long_message(void) {
  ModifyOrderLongMessage sent;
  ModifyOrderLongMessage got;
  uint8_t wire[25];
  uint8_t again[25];

  any_modify_order_long_message(&sent);
  assert(encode_modify_order_long_message(&sent, wire, 0) == 25);
  assert(decode_modify_order_long_message(&got, wire, 0) == 25);
  equal_modify_order_long_message(&got, &sent);

  for (size_t i = 0; i < 25; i++) { wire[i] = arbitrary(); }
  assert(decode_modify_order_long_message(&got, wire, 0) == 25);
  assert(encode_modify_order_long_message(&got, again, 0) == 25);
  for (size_t i = 0; i < 25; i++) { assert(again[i] == wire[i]); }
}

/* ---- Modify Order Short Message: 17 bytes ------------------------------------ */

/* The Modify Order Short message is sent whenever an open complex order is visibly modified and both the new price and quantity fit in short fields. */
typedef struct {
  uint8_t time_offset[4];         /* bytes 0 to 3 */
  uint8_t order_id[8];            /* bytes 4 to 11 */
  uint8_t quantity_short[2];      /* bytes 12 to 13 */
  uint8_t signed_price_short[2];  /* bytes 14 to 15 */
  uint8_t reserved_1;             /* byte 16 */
} ModifyOrderShortMessage;

/* any Modify Order Short Message at all: every byte one the checker chooses */
static void any_modify_order_short_message(ModifyOrderShortMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->time_offset[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->quantity_short[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->signed_price_short[i] = arbitrary(); }
  record->reserved_1 = arbitrary();
}

/* Modify Order Short Message to the wire: 17 bytes from at, returning where the next byte goes */
static size_t encode_modify_order_short_message(const ModifyOrderShortMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->time_offset[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_id[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->quantity_short[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->signed_price_short[i]; }
  wire[at++] = record->reserved_1;

  return at;
}

/* Modify Order Short Message off the wire: 17 bytes from at, returning where the next byte lies */
static size_t decode_modify_order_short_message(ModifyOrderShortMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->time_offset[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->quantity_short[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->signed_price_short[i] = wire[at++]; }
  record->reserved_1 = wire[at++];

  return at;
}

/* what was read of Modify Order Short Message is what was written, byte for byte */
static void equal_modify_order_short_message(const ModifyOrderShortMessage *read, const ModifyOrderShortMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->time_offset[i] == written->time_offset[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->order_id[i] == written->order_id[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->quantity_short[i] == written->quantity_short[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->signed_price_short[i] == written->signed_price_short[i]); }
  assert(read->reserved_1 == written->reserved_1);
}

/* Modify Order Short Message: written and read back, then read and written back */
static void check_modify_order_short_message(void) {
  ModifyOrderShortMessage sent;
  ModifyOrderShortMessage got;
  uint8_t wire[17];
  uint8_t again[17];

  any_modify_order_short_message(&sent);
  assert(encode_modify_order_short_message(&sent, wire, 0) == 17);
  assert(decode_modify_order_short_message(&got, wire, 0) == 17);
  equal_modify_order_short_message(&got, &sent);

  for (size_t i = 0; i < 17; i++) { wire[i] = arbitrary(); }
  assert(decode_modify_order_short_message(&got, wire, 0) == 17);
  assert(encode_modify_order_short_message(&got, again, 0) == 17);
  for (size_t i = 0; i < 17; i++) { assert(again[i] == wire[i]); }
}

/* ---- Delete Order Message: 12 bytes ------------------------------------------ */

/* The Delete Order message is sent whenever a booked order is cancelled or leaves the order book. The Order Id refers to the Order Id of the original Add Order message. An order that is deleted from the book may return to the book later under certain circumstances. Therefore, a Delete Order message does not indicate that a given Order Id will not be sent again on a subsequent Add Order message. */
typedef struct {
  uint8_t time_offset[4];  /* bytes 0 to 3 */
  uint8_t order_id[8];     /* bytes 4 to 11 */
} DeleteOrderMessage;

/* any Delete Order Message at all: every byte one the checker chooses */
static void any_delete_order_message(DeleteOrderMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->time_offset[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = arbitrary(); }
}

/* Delete Order Message to the wire: 12 bytes from at, returning where the next byte goes */
static size_t encode_delete_order_message(const DeleteOrderMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->time_offset[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_id[i]; }

  return at;
}

/* Delete Order Message off the wire: 12 bytes from at, returning where the next byte lies */
static size_t decode_delete_order_message(DeleteOrderMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->time_offset[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = wire[at++]; }

  return at;
}

/* what was read of Delete Order Message is what was written, byte for byte */
static void equal_delete_order_message(const DeleteOrderMessage *read, const DeleteOrderMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->time_offset[i] == written->time_offset[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->order_id[i] == written->order_id[i]); }
}

/* Delete Order Message: written and read back, then read and written back */
static void check_delete_order_message(void) {
  DeleteOrderMessage sent;
  DeleteOrderMessage got;
  uint8_t wire[12];
  uint8_t again[12];

  any_delete_order_message(&sent);
  assert(encode_delete_order_message(&sent, wire, 0) == 12);
  assert(decode_delete_order_message(&got, wire, 0) == 12);
  equal_delete_order_message(&got, &sent);

  for (size_t i = 0; i < 12; i++) { wire[i] = arbitrary(); }
  assert(decode_delete_order_message(&got, wire, 0) == 12);
  assert(encode_delete_order_message(&got, again, 0) == 12);
  for (size_t i = 0; i < 12; i++) { assert(again[i] == wire[i]); }
}

/* ---- Trade Long Message: 40 bytes -------------------------------------------- */

/* The Trade message provides information about executions of complex order auctions on the Cboe complex book. A Trade message can also be sent when an auction executes against a non-displayed order, such as a contra response. Trade messages are necessary to calculate Cboe execution-based data. Trade messages do not alter the complex book and can be ignored if messages are being used solely to build a complex book. No Add Order message is sent for complex auction orders, and thus, no order modification messages may be sent when complex auctions are executed. Instead, a Trade message is sent whenever a complex auction is executed in whole or in part. */
typedef struct {
  uint8_t time_offset[4];                  /* bytes 0 to 3 */
  uint8_t order_id[8];                     /* bytes 4 to 11 */
  uint8_t side_indicator;                  /* byte 12 */
  uint8_t quantity_long[4];                /* bytes 13 to 16 */
  uint8_t complex_instrument_id_short[6];  /* bytes 17 to 22 */
  uint8_t signed_price_long[8];            /* bytes 23 to 30 */
  uint8_t execution_id[8];                 /* bytes 31 to 38 */
  uint8_t trade_condition;                 /* byte 39 */
} TradeLongMessage;

/* any Trade Long Message at all: every byte one the checker chooses */
static void any_trade_long_message(TradeLongMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->time_offset[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = arbitrary(); }
  record->side_indicator = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->quantity_long[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->complex_instrument_id_short[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->signed_price_long[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->execution_id[i] = arbitrary(); }
  record->trade_condition = arbitrary();
}

/* Trade Long Message to the wire: 40 bytes from at, returning where the next byte goes */
static size_t encode_trade_long_message(const TradeLongMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->time_offset[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_id[i]; }
  wire[at++] = record->side_indicator;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->quantity_long[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->complex_instrument_id_short[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->signed_price_long[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->execution_id[i]; }
  wire[at++] = record->trade_condition;

  return at;
}

/* Trade Long Message off the wire: 40 bytes from at, returning where the next byte lies */
static size_t decode_trade_long_message(TradeLongMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->time_offset[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = wire[at++]; }
  record->side_indicator = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->quantity_long[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->complex_instrument_id_short[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->signed_price_long[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->execution_id[i] = wire[at++]; }
  record->trade_condition = wire[at++];

  return at;
}

/* what was read of Trade Long Message is what was written, byte for byte */
static void equal_trade_long_message(const TradeLongMessage *read, const TradeLongMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->time_offset[i] == written->time_offset[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->order_id[i] == written->order_id[i]); }
  assert(read->side_indicator == written->side_indicator);
  for (size_t i = 0; i < 4; i++) { assert(read->quantity_long[i] == written->quantity_long[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->complex_instrument_id_short[i] == written->complex_instrument_id_short[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->signed_price_long[i] == written->signed_price_long[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->execution_id[i] == written->execution_id[i]); }
  assert(read->trade_condition == written->trade_condition);
}

/* Trade Long Message: written and read back, then read and written back */
static void check_trade_long_message(void) {
  TradeLongMessage sent;
  TradeLongMessage got;
  uint8_t wire[40];
  uint8_t again[40];

  any_trade_long_message(&sent);
  assert(encode_trade_long_message(&sent, wire, 0) == 40);
  assert(decode_trade_long_message(&got, wire, 0) == 40);
  equal_trade_long_message(&got, &sent);

  for (size_t i = 0; i < 40; i++) { wire[i] = arbitrary(); }
  assert(decode_trade_long_message(&got, wire, 0) == 40);
  assert(encode_trade_long_message(&got, again, 0) == 40);
  for (size_t i = 0; i < 40; i++) { assert(again[i] == wire[i]); }
}

/* ---- Trade Short Message: 32 bytes ------------------------------------------- */

/* The Trade Short message is the short-price/short-quantity variant of the Trade message, used when both the execution price and quantity fit in short fields. */
typedef struct {
  uint8_t time_offset[4];                  /* bytes 0 to 3 */
  uint8_t order_id[8];                     /* bytes 4 to 11 */
  uint8_t side_indicator;                  /* byte 12 */
  uint8_t quantity_short[2];               /* bytes 13 to 14 */
  uint8_t complex_instrument_id_short[6];  /* bytes 15 to 20 */
  uint8_t signed_price_short[2];           /* bytes 21 to 22 */
  uint8_t execution_id[8];                 /* bytes 23 to 30 */
  uint8_t trade_condition;                 /* byte 31 */
} TradeShortMessage;

/* any Trade Short Message at all: every byte one the checker chooses */
static void any_trade_short_message(TradeShortMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->time_offset[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = arbitrary(); }
  record->side_indicator = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->quantity_short[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->complex_instrument_id_short[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->signed_price_short[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->execution_id[i] = arbitrary(); }
  record->trade_condition = arbitrary();
}

/* Trade Short Message to the wire: 32 bytes from at, returning where the next byte goes */
static size_t encode_trade_short_message(const TradeShortMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->time_offset[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_id[i]; }
  wire[at++] = record->side_indicator;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->quantity_short[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->complex_instrument_id_short[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->signed_price_short[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->execution_id[i]; }
  wire[at++] = record->trade_condition;

  return at;
}

/* Trade Short Message off the wire: 32 bytes from at, returning where the next byte lies */
static size_t decode_trade_short_message(TradeShortMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->time_offset[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = wire[at++]; }
  record->side_indicator = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->quantity_short[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->complex_instrument_id_short[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->signed_price_short[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->execution_id[i] = wire[at++]; }
  record->trade_condition = wire[at++];

  return at;
}

/* what was read of Trade Short Message is what was written, byte for byte */
static void equal_trade_short_message(const TradeShortMessage *read, const TradeShortMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->time_offset[i] == written->time_offset[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->order_id[i] == written->order_id[i]); }
  assert(read->side_indicator == written->side_indicator);
  for (size_t i = 0; i < 2; i++) { assert(read->quantity_short[i] == written->quantity_short[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->complex_instrument_id_short[i] == written->complex_instrument_id_short[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->signed_price_short[i] == written->signed_price_short[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->execution_id[i] == written->execution_id[i]); }
  assert(read->trade_condition == written->trade_condition);
}

/* Trade Short Message: written and read back, then read and written back */
static void check_trade_short_message(void) {
  TradeShortMessage sent;
  TradeShortMessage got;
  uint8_t wire[32];
  uint8_t again[32];

  any_trade_short_message(&sent);
  assert(encode_trade_short_message(&sent, wire, 0) == 32);
  assert(decode_trade_short_message(&got, wire, 0) == 32);
  equal_trade_short_message(&got, &sent);

  for (size_t i = 0; i < 32; i++) { wire[i] = arbitrary(); }
  assert(decode_trade_short_message(&got, wire, 0) == 32);
  assert(encode_trade_short_message(&got, again, 0) == 32);
  for (size_t i = 0; i < 32; i++) { assert(again[i] == wire[i]); }
}

/* ---- Auction Notification Message: 45 bytes ---------------------------------- */

/* Auction Notification messages are used to disseminate order details of a complex auction. Auctions will be available for a defined period of time known as the exposure period. */
typedef struct {
  uint8_t time_offset[4];                  /* bytes 0 to 3 */
  uint8_t complex_instrument_id_short[6];  /* bytes 4 to 9 */
  uint8_t auction_id[8];                   /* bytes 10 to 17 */
  uint8_t notification_auction_type;       /* byte 18 */
  uint8_t side;                            /* byte 19 */
  uint8_t signed_price_long[8];            /* bytes 20 to 27 */
  uint8_t quantity_long[4];                /* bytes 28 to 31 */
  uint8_t customer_indicator;              /* byte 32 */
  uint8_t participant_id[4];               /* bytes 33 to 36 */
  uint8_t auction_end_offset[4];           /* bytes 37 to 40 */
  uint8_t client_id[4];                    /* bytes 41 to 44 */
} AuctionNotificationMessage;

/* any Auction Notification Message at all: every byte one the checker chooses */
static void any_auction_notification_message(AuctionNotificationMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->time_offset[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->complex_instrument_id_short[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->auction_id[i] = arbitrary(); }
  record->notification_auction_type = arbitrary();
  record->side = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->signed_price_long[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->quantity_long[i] = arbitrary(); }
  record->customer_indicator = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->participant_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->auction_end_offset[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->client_id[i] = arbitrary(); }
}

/* Auction Notification Message to the wire: 45 bytes from at, returning where the next byte goes */
static size_t encode_auction_notification_message(const AuctionNotificationMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->time_offset[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->complex_instrument_id_short[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->auction_id[i]; }
  wire[at++] = record->notification_auction_type;
  wire[at++] = record->side;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->signed_price_long[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->quantity_long[i]; }
  wire[at++] = record->customer_indicator;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->participant_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->auction_end_offset[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->client_id[i]; }

  return at;
}

/* Auction Notification Message off the wire: 45 bytes from at, returning where the next byte lies */
static size_t decode_auction_notification_message(AuctionNotificationMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->time_offset[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->complex_instrument_id_short[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->auction_id[i] = wire[at++]; }
  record->notification_auction_type = wire[at++];
  record->side = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->signed_price_long[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->quantity_long[i] = wire[at++]; }
  record->customer_indicator = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->participant_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->auction_end_offset[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->client_id[i] = wire[at++]; }

  return at;
}

/* what was read of Auction Notification Message is what was written, byte for byte */
static void equal_auction_notification_message(const AuctionNotificationMessage *read, const AuctionNotificationMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->time_offset[i] == written->time_offset[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->complex_instrument_id_short[i] == written->complex_instrument_id_short[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->auction_id[i] == written->auction_id[i]); }
  assert(read->notification_auction_type == written->notification_auction_type);
  assert(read->side == written->side);
  for (size_t i = 0; i < 8; i++) { assert(read->signed_price_long[i] == written->signed_price_long[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->quantity_long[i] == written->quantity_long[i]); }
  assert(read->customer_indicator == written->customer_indicator);
  for (size_t i = 0; i < 4; i++) { assert(read->participant_id[i] == written->participant_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->auction_end_offset[i] == written->auction_end_offset[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->client_id[i] == written->client_id[i]); }
}

/* Auction Notification Message: written and read back, then read and written back */
static void check_auction_notification_message(void) {
  AuctionNotificationMessage sent;
  AuctionNotificationMessage got;
  uint8_t wire[45];
  uint8_t again[45];

  any_auction_notification_message(&sent);
  assert(encode_auction_notification_message(&sent, wire, 0) == 45);
  assert(decode_auction_notification_message(&got, wire, 0) == 45);
  equal_auction_notification_message(&got, &sent);

  for (size_t i = 0; i < 45; i++) { wire[i] = arbitrary(); }
  assert(decode_auction_notification_message(&got, wire, 0) == 45);
  assert(encode_auction_notification_message(&got, again, 0) == 45);
  for (size_t i = 0; i < 45; i++) { assert(again[i] == wire[i]); }
}

/* ---- Auction Cancel Message: 12 bytes ---------------------------------------- */

/* Auction Cancel messages are used to disseminate the cancelation of an earlier Auction Notification message as a result of a user cancelation of the original complex auction, a user modification request to change the complex auction price or increase the original complex auction quantity, a fading of the NBBO or to cancel any remaining complex auction quantity from the original Auction Notification following the complex auction termination. A user request to modify the complex auction price or to increase the original complex auction quantity will result in a cancelation of the complex auction followed by a new Auction Notification message. Auction Cancel messages will not be issued for complex auction quantity decrements. */
typedef struct {
  uint8_t time_offset[4];  /* bytes 0 to 3 */
  uint8_t auction_id[8];   /* bytes 4 to 11 */
} AuctionCancelMessage;

/* any Auction Cancel Message at all: every byte one the checker chooses */
static void any_auction_cancel_message(AuctionCancelMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->time_offset[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->auction_id[i] = arbitrary(); }
}

/* Auction Cancel Message to the wire: 12 bytes from at, returning where the next byte goes */
static size_t encode_auction_cancel_message(const AuctionCancelMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->time_offset[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->auction_id[i]; }

  return at;
}

/* Auction Cancel Message off the wire: 12 bytes from at, returning where the next byte lies */
static size_t decode_auction_cancel_message(AuctionCancelMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->time_offset[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->auction_id[i] = wire[at++]; }

  return at;
}

/* what was read of Auction Cancel Message is what was written, byte for byte */
static void equal_auction_cancel_message(const AuctionCancelMessage *read, const AuctionCancelMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->time_offset[i] == written->time_offset[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->auction_id[i] == written->auction_id[i]); }
}

/* Auction Cancel Message: written and read back, then read and written back */
static void check_auction_cancel_message(void) {
  AuctionCancelMessage sent;
  AuctionCancelMessage got;
  uint8_t wire[12];
  uint8_t again[12];

  any_auction_cancel_message(&sent);
  assert(encode_auction_cancel_message(&sent, wire, 0) == 12);
  assert(decode_auction_cancel_message(&got, wire, 0) == 12);
  equal_auction_cancel_message(&got, &sent);

  for (size_t i = 0; i < 12; i++) { wire[i] = arbitrary(); }
  assert(decode_auction_cancel_message(&got, wire, 0) == 12);
  assert(encode_auction_cancel_message(&got, again, 0) == 12);
  for (size_t i = 0; i < 12; i++) { assert(again[i] == wire[i]); }
}

/* ---- Auction Trade Message: 32 bytes ----------------------------------------- */

/* Auction Trade messages are used to disseminate executions resulting from a complex auction. */
typedef struct {
  uint8_t time_offset[4];        /* bytes 0 to 3 */
  uint8_t auction_id[8];         /* bytes 4 to 11 */
  uint8_t execution_id[8];       /* bytes 12 to 19 */
  uint8_t signed_price_long[8];  /* bytes 20 to 27 */
  uint8_t quantity_long[4];      /* bytes 28 to 31 */
} AuctionTradeMessage;

/* any Auction Trade Message at all: every byte one the checker chooses */
static void any_auction_trade_message(AuctionTradeMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->time_offset[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->auction_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->execution_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->signed_price_long[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->quantity_long[i] = arbitrary(); }
}

/* Auction Trade Message to the wire: 32 bytes from at, returning where the next byte goes */
static size_t encode_auction_trade_message(const AuctionTradeMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->time_offset[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->auction_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->execution_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->signed_price_long[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->quantity_long[i]; }

  return at;
}

/* Auction Trade Message off the wire: 32 bytes from at, returning where the next byte lies */
static size_t decode_auction_trade_message(AuctionTradeMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->time_offset[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->auction_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->execution_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->signed_price_long[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->quantity_long[i] = wire[at++]; }

  return at;
}

/* what was read of Auction Trade Message is what was written, byte for byte */
static void equal_auction_trade_message(const AuctionTradeMessage *read, const AuctionTradeMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->time_offset[i] == written->time_offset[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->auction_id[i] == written->auction_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->execution_id[i] == written->execution_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->signed_price_long[i] == written->signed_price_long[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->quantity_long[i] == written->quantity_long[i]); }
}

/* Auction Trade Message: written and read back, then read and written back */
static void check_auction_trade_message(void) {
  AuctionTradeMessage sent;
  AuctionTradeMessage got;
  uint8_t wire[32];
  uint8_t again[32];

  any_auction_trade_message(&sent);
  assert(encode_auction_trade_message(&sent, wire, 0) == 32);
  assert(decode_auction_trade_message(&got, wire, 0) == 32);
  equal_auction_trade_message(&got, &sent);

  for (size_t i = 0; i < 32; i++) { wire[i] = arbitrary(); }
  assert(decode_auction_trade_message(&got, wire, 0) == 32);
  assert(encode_auction_trade_message(&got, again, 0) == 32);
  for (size_t i = 0; i < 32; i++) { assert(again[i] == wire[i]); }
}

/* ---- Trading Status Message: 16 bytes ---------------------------------------- */

/* The Trading Status message is used to indicate the current trading status of a complex instrument. A Trading Status message will be sent whenever a complex instrument trading status changes. The Trading Status field will be used to represent the status of the RTH (9:30 a.m. ET - 4:15 p.m. ET) and Curb sessions. The GTH Trading Status field will be used to represent the status of series that trade during the GTH session (C1 Only). The GTH session runs from 8:15 p.m. to 9:25 a.m. ET for SPX and VIX series (C1 only). */
typedef struct {
  uint8_t time_offset[4];        /* bytes 0 to 3 */
  uint8_t complex_symbol_id[6];  /* bytes 4 to 9 */
  uint8_t reserved_2[2];         /* bytes 10 to 11 */
  uint8_t trading_status;        /* byte 12 */
  uint8_t reserved_1;            /* byte 13 */
  uint8_t gth_trading_status;    /* byte 14 */
  uint8_t second_reserved_1;     /* byte 15 */
} TradingStatusMessage;

/* any Trading Status Message at all: every byte one the checker chooses */
static void any_trading_status_message(TradingStatusMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->time_offset[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->complex_symbol_id[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->reserved_2[i] = arbitrary(); }
  record->trading_status = arbitrary();
  record->reserved_1 = arbitrary();
  record->gth_trading_status = arbitrary();
  record->second_reserved_1 = arbitrary();
}

/* Trading Status Message to the wire: 16 bytes from at, returning where the next byte goes */
static size_t encode_trading_status_message(const TradingStatusMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->time_offset[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->complex_symbol_id[i]; }
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
  for (size_t i = 0; i < 6; i++) { record->complex_symbol_id[i] = wire[at++]; }
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
  for (size_t i = 0; i < 6; i++) { assert(read->complex_symbol_id[i] == written->complex_symbol_id[i]); }
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

/* ---- Options Auction Update Message: 62 bytes -------------------------------- */

/* Options Auction Update messages are used to disseminate price and size information during the Opening and Re-Opening (halt) process for complex instruments. The Options Auction Update messages are sent every 5 seconds during an opening period. */
typedef struct {
  uint8_t time_offset[4];                   /* bytes 0 to 3 */
  uint8_t complex_instrument_id_long[8];    /* bytes 4 to 11 */
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
  for (size_t i = 0; i < 8; i++) { record->complex_instrument_id_long[i] = arbitrary(); }
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
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->complex_instrument_id_long[i]; }
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
  for (size_t i = 0; i < 8; i++) { record->complex_instrument_id_long[i] = wire[at++]; }
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
  for (size_t i = 0; i < 8; i++) { assert(read->complex_instrument_id_long[i] == written->complex_instrument_id_long[i]); }
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

/* Auction Summary messages are used to disseminate the results of an auction of a complex instrument. An Opening or Re-Opening Auction Summary message for each complex instrument is sent at the conclusion of its Opening or Re-Opening auction and represents Cboe opening price. */
typedef struct {
  uint8_t time_offset[4];                 /* bytes 0 to 3 */
  uint8_t complex_instrument_id_long[8];  /* bytes 4 to 11 */
  uint8_t auction_type;                   /* byte 12 */
  uint8_t signed_price_long[8];           /* bytes 13 to 20 */
  uint8_t quantity_long[4];               /* bytes 21 to 24 */
} AuctionSummaryMessage;

/* any Auction Summary Message at all: every byte one the checker chooses */
static void any_auction_summary_message(AuctionSummaryMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->time_offset[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->complex_instrument_id_long[i] = arbitrary(); }
  record->auction_type = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->signed_price_long[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->quantity_long[i] = arbitrary(); }
}

/* Auction Summary Message to the wire: 25 bytes from at, returning where the next byte goes */
static size_t encode_auction_summary_message(const AuctionSummaryMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->time_offset[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->complex_instrument_id_long[i]; }
  wire[at++] = record->auction_type;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->signed_price_long[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->quantity_long[i]; }

  return at;
}

/* Auction Summary Message off the wire: 25 bytes from at, returning where the next byte lies */
static size_t decode_auction_summary_message(AuctionSummaryMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->time_offset[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->complex_instrument_id_long[i] = wire[at++]; }
  record->auction_type = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->signed_price_long[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->quantity_long[i] = wire[at++]; }

  return at;
}

/* what was read of Auction Summary Message is what was written, byte for byte */
static void equal_auction_summary_message(const AuctionSummaryMessage *read, const AuctionSummaryMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->time_offset[i] == written->time_offset[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->complex_instrument_id_long[i] == written->complex_instrument_id_long[i]); }
  assert(read->auction_type == written->auction_type);
  for (size_t i = 0; i < 8; i++) { assert(read->signed_price_long[i] == written->signed_price_long[i]); }
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
  check_time_message();
  check_unit_clear_message();
  check_transaction_begin_message();
  check_transaction_end_message();
  check_symbol_mapping_message();
  check_add_order_long_message();
  check_add_order_short_message();
  check_add_order_expanded_message();
  check_order_executed_message();
  check_order_executed_at_price_size_message();
  check_reduce_size_long_message();
  check_reduce_size_short_message();
  check_modify_order_long_message();
  check_modify_order_short_message();
  check_delete_order_message();
  check_trade_long_message();
  check_trade_short_message();
  check_auction_notification_message();
  check_auction_cancel_message();
  check_auction_trade_message();
  check_trading_status_message();
  check_options_auction_update_message();
  check_auction_summary_message();
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
