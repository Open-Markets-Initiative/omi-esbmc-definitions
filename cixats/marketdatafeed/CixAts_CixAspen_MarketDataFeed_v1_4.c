// cixats/marketdatafeed/CixAts_CixAspen_MarketDataFeed_v1_4.c
/*
 * CIX Trading Inc. CIX Market Data Feed
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

/* ---- Packet Header: 20 bytes ------------------------------------------------- */

typedef struct {
  uint8_t market_day_identifier[9];  /* bytes 0 to 8 */
  uint8_t feed_identifier;           /* byte 9 */
  uint8_t sequence[8];               /* bytes 10 to 17 */
  uint8_t count[2];                  /* bytes 18 to 19 */
} PacketHeader;

/* any Packet Header at all: every byte one the checker chooses */
static void any_packet_header(PacketHeader *record) {
  for (size_t i = 0; i < 9; i++) { record->market_day_identifier[i] = arbitrary(); }
  record->feed_identifier = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->sequence[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->count[i] = arbitrary(); }
}

/* Packet Header to the wire: 20 bytes from at, returning where the next byte goes */
static size_t encode_packet_header(const PacketHeader *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 9; i++) { wire[at++] = record->market_day_identifier[i]; }
  wire[at++] = record->feed_identifier;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->sequence[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->count[i]; }

  return at;
}

/* Packet Header off the wire: 20 bytes from at, returning where the next byte lies */
static size_t decode_packet_header(PacketHeader *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 9; i++) { record->market_day_identifier[i] = wire[at++]; }
  record->feed_identifier = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->sequence[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->count[i] = wire[at++]; }

  return at;
}

/* what was read of Packet Header is what was written, byte for byte */
static void equal_packet_header(const PacketHeader *read, const PacketHeader *written) {
  for (size_t i = 0; i < 9; i++) { assert(read->market_day_identifier[i] == written->market_day_identifier[i]); }
  assert(read->feed_identifier == written->feed_identifier);
  for (size_t i = 0; i < 8; i++) { assert(read->sequence[i] == written->sequence[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->count[i] == written->count[i]); }
}

/* Packet Header: written and read back, then read and written back */
static void check_packet_header(void) {
  PacketHeader sent;
  PacketHeader got;
  uint8_t wire[20];
  uint8_t again[20];

  any_packet_header(&sent);
  assert(encode_packet_header(&sent, wire, 0) == 20);
  assert(decode_packet_header(&got, wire, 0) == 20);
  equal_packet_header(&got, &sent);

  for (size_t i = 0; i < 20; i++) { wire[i] = arbitrary(); }
  assert(decode_packet_header(&got, wire, 0) == 20);
  assert(encode_packet_header(&got, again, 0) == 20);
  for (size_t i = 0; i < 20; i++) { assert(again[i] == wire[i]); }
}

/* ---- Message Header: 3 bytes ------------------------------------------------- */

/* Length of the message */
typedef struct {
  uint8_t length[2];     /* bytes 0 to 1 */
  uint8_t message_type;  /* byte 2 */
} MessageHeader;

/* any Message Header at all: every byte one the checker chooses */
static void any_message_header(MessageHeader *record) {
  for (size_t i = 0; i < 2; i++) { record->length[i] = arbitrary(); }
  record->message_type = arbitrary();
}

/* Message Header to the wire: 3 bytes from at, returning where the next byte goes */
static size_t encode_message_header(const MessageHeader *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->length[i]; }
  wire[at++] = record->message_type;

  return at;
}

/* Message Header off the wire: 3 bytes from at, returning where the next byte lies */
static size_t decode_message_header(MessageHeader *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->length[i] = wire[at++]; }
  record->message_type = wire[at++];

  return at;
}

/* what was read of Message Header is what was written, byte for byte */
static void equal_message_header(const MessageHeader *read, const MessageHeader *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->length[i] == written->length[i]); }
  assert(read->message_type == written->message_type);
}

/* Message Header: written and read back, then read and written back */
static void check_message_header(void) {
  MessageHeader sent;
  MessageHeader got;
  uint8_t wire[3];
  uint8_t again[3];

  any_message_header(&sent);
  assert(encode_message_header(&sent, wire, 0) == 3);
  assert(decode_message_header(&got, wire, 0) == 3);
  equal_message_header(&got, &sent);

  for (size_t i = 0; i < 3; i++) { wire[i] = arbitrary(); }
  assert(decode_message_header(&got, wire, 0) == 3);
  assert(encode_message_header(&got, again, 0) == 3);
  for (size_t i = 0; i < 3; i++) { assert(again[i] == wire[i]); }
}

/* ---- Market Event Message: 11 bytes ------------------------------------------ */

/* Transitions in the overall session state */
typedef struct {
  uint8_t reserved_2[2];  /* bytes 0 to 1 */
  uint8_t timestamp[8];   /* bytes 2 to 9 */
  uint8_t event;          /* byte 10 */
} MarketEventMessage;

/* any Market Event Message at all: every byte one the checker chooses */
static void any_market_event_message(MarketEventMessage *record) {
  for (size_t i = 0; i < 2; i++) { record->reserved_2[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
  record->event = arbitrary();
}

/* Market Event Message to the wire: 11 bytes from at, returning where the next byte goes */
static size_t encode_market_event_message(const MarketEventMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->reserved_2[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }
  wire[at++] = record->event;

  return at;
}

/* Market Event Message off the wire: 11 bytes from at, returning where the next byte lies */
static size_t decode_market_event_message(MarketEventMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->reserved_2[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }
  record->event = wire[at++];

  return at;
}

/* what was read of Market Event Message is what was written, byte for byte */
static void equal_market_event_message(const MarketEventMessage *read, const MarketEventMessage *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->reserved_2[i] == written->reserved_2[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  assert(read->event == written->event);
}

/* Market Event Message: written and read back, then read and written back */
static void check_market_event_message(void) {
  MarketEventMessage sent;
  MarketEventMessage got;
  uint8_t wire[11];
  uint8_t again[11];

  any_market_event_message(&sent);
  assert(encode_market_event_message(&sent, wire, 0) == 11);
  assert(decode_market_event_message(&got, wire, 0) == 11);
  equal_market_event_message(&got, &sent);

  for (size_t i = 0; i < 11; i++) { wire[i] = arbitrary(); }
  assert(decode_market_event_message(&got, wire, 0) == 11);
  assert(encode_market_event_message(&got, again, 0) == 11);
  for (size_t i = 0; i < 11; i++) { assert(again[i] == wire[i]); }
}

/* ---- Symbol Information Message: 26 bytes ------------------------------------ */

/* Reference data for each symbol that may be traded */
typedef struct {
  uint8_t timestamp[8];       /* bytes 0 to 7 */
  uint8_t symbol_id[2];       /* bytes 8 to 9 */
  uint8_t symbol[11];         /* bytes 10 to 20 */
  uint8_t listing_market;     /* byte 21 */
  uint8_t board_lot_size[4];  /* bytes 22 to 25 */
} SymbolInformationMessage;

/* any Symbol Information Message at all: every byte one the checker chooses */
static void any_symbol_information_message(SymbolInformationMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->symbol_id[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->symbol[i] = arbitrary(); }
  record->listing_market = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->board_lot_size[i] = arbitrary(); }
}

/* Symbol Information Message to the wire: 26 bytes from at, returning where the next byte goes */
static size_t encode_symbol_information_message(const SymbolInformationMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->symbol_id[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->symbol[i]; }
  wire[at++] = record->listing_market;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->board_lot_size[i]; }

  return at;
}

/* Symbol Information Message off the wire: 26 bytes from at, returning where the next byte lies */
static size_t decode_symbol_information_message(SymbolInformationMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->symbol_id[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->symbol[i] = wire[at++]; }
  record->listing_market = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->board_lot_size[i] = wire[at++]; }

  return at;
}

/* what was read of Symbol Information Message is what was written, byte for byte */
static void equal_symbol_information_message(const SymbolInformationMessage *read, const SymbolInformationMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->symbol_id[i] == written->symbol_id[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->symbol[i] == written->symbol[i]); }
  assert(read->listing_market == written->listing_market);
  for (size_t i = 0; i < 4; i++) { assert(read->board_lot_size[i] == written->board_lot_size[i]); }
}

/* Symbol Information Message: written and read back, then read and written back */
static void check_symbol_information_message(void) {
  SymbolInformationMessage sent;
  SymbolInformationMessage got;
  uint8_t wire[26];
  uint8_t again[26];

  any_symbol_information_message(&sent);
  assert(encode_symbol_information_message(&sent, wire, 0) == 26);
  assert(decode_symbol_information_message(&got, wire, 0) == 26);
  equal_symbol_information_message(&got, &sent);

  for (size_t i = 0; i < 26; i++) { wire[i] = arbitrary(); }
  assert(decode_symbol_information_message(&got, wire, 0) == 26);
  assert(encode_symbol_information_message(&got, again, 0) == 26);
  for (size_t i = 0; i < 26; i++) { assert(again[i] == wire[i]); }
}

/* ---- Symbol State Message: 27 bytes ------------------------------------------ */

/* Individual symbol trading state (halts) */
typedef struct {
  uint8_t timestamp[8];  /* bytes 0 to 7 */
  uint8_t symbol_id[2];  /* bytes 8 to 9 */
  uint8_t symbol[11];    /* bytes 10 to 20 */
  uint8_t state;         /* byte 21 */
  uint8_t reserved_1;    /* byte 22 */
  uint8_t info[4];       /* bytes 23 to 26 */
} SymbolStateMessage;

/* any Symbol State Message at all: every byte one the checker chooses */
static void any_symbol_state_message(SymbolStateMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->symbol_id[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->symbol[i] = arbitrary(); }
  record->state = arbitrary();
  record->reserved_1 = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->info[i] = arbitrary(); }
}

/* Symbol State Message to the wire: 27 bytes from at, returning where the next byte goes */
static size_t encode_symbol_state_message(const SymbolStateMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->symbol_id[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->symbol[i]; }
  wire[at++] = record->state;
  wire[at++] = record->reserved_1;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->info[i]; }

  return at;
}

/* Symbol State Message off the wire: 27 bytes from at, returning where the next byte lies */
static size_t decode_symbol_state_message(SymbolStateMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->symbol_id[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->symbol[i] = wire[at++]; }
  record->state = wire[at++];
  record->reserved_1 = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->info[i] = wire[at++]; }

  return at;
}

/* what was read of Symbol State Message is what was written, byte for byte */
static void equal_symbol_state_message(const SymbolStateMessage *read, const SymbolStateMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->symbol_id[i] == written->symbol_id[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->symbol[i] == written->symbol[i]); }
  assert(read->state == written->state);
  assert(read->reserved_1 == written->reserved_1);
  for (size_t i = 0; i < 4; i++) { assert(read->info[i] == written->info[i]); }
}

/* Symbol State Message: written and read back, then read and written back */
static void check_symbol_state_message(void) {
  SymbolStateMessage sent;
  SymbolStateMessage got;
  uint8_t wire[27];
  uint8_t again[27];

  any_symbol_state_message(&sent);
  assert(encode_symbol_state_message(&sent, wire, 0) == 27);
  assert(decode_symbol_state_message(&got, wire, 0) == 27);
  equal_symbol_state_message(&got, &sent);

  for (size_t i = 0; i < 27; i++) { wire[i] = arbitrary(); }
  assert(decode_symbol_state_message(&got, wire, 0) == 27);
  assert(encode_symbol_state_message(&got, again, 0) == 27);
  for (size_t i = 0; i < 27; i++) { assert(again[i] == wire[i]); }
}

/* ---- New Order Add Message: 50 bytes ----------------------------------------- */

/* A new resting order added to the book */
typedef struct {
  uint8_t timestamp[8];  /* bytes 0 to 7 */
  uint8_t symbol_id[2];  /* bytes 8 to 9 */
  uint8_t order_id[8];   /* bytes 10 to 17 */
  uint8_t side;          /* byte 18 */
  uint8_t quantity[8];   /* bytes 19 to 26 */
  uint8_t symbol[11];    /* bytes 27 to 37 */
  uint8_t price[8];      /* bytes 38 to 45 */
  uint8_t broker[3];     /* bytes 46 to 48 */
  uint8_t reserved_1;    /* byte 49 */
} NewOrderAddMessage;

/* any New Order Add Message at all: every byte one the checker chooses */
static void any_new_order_add_message(NewOrderAddMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->symbol_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = arbitrary(); }
  record->side = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->symbol[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->price[i] = arbitrary(); }
  for (size_t i = 0; i < 3; i++) { record->broker[i] = arbitrary(); }
  record->reserved_1 = arbitrary();
}

/* New Order Add Message to the wire: 50 bytes from at, returning where the next byte goes */
static size_t encode_new_order_add_message(const NewOrderAddMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->symbol_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_id[i]; }
  wire[at++] = record->side;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->quantity[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->symbol[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price[i]; }
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->broker[i]; }
  wire[at++] = record->reserved_1;

  return at;
}

/* New Order Add Message off the wire: 50 bytes from at, returning where the next byte lies */
static size_t decode_new_order_add_message(NewOrderAddMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->symbol_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = wire[at++]; }
  record->side = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->symbol[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->price[i] = wire[at++]; }
  for (size_t i = 0; i < 3; i++) { record->broker[i] = wire[at++]; }
  record->reserved_1 = wire[at++];

  return at;
}

/* what was read of New Order Add Message is what was written, byte for byte */
static void equal_new_order_add_message(const NewOrderAddMessage *read, const NewOrderAddMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->symbol_id[i] == written->symbol_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->order_id[i] == written->order_id[i]); }
  assert(read->side == written->side);
  for (size_t i = 0; i < 8; i++) { assert(read->quantity[i] == written->quantity[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->symbol[i] == written->symbol[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->price[i] == written->price[i]); }
  for (size_t i = 0; i < 3; i++) { assert(read->broker[i] == written->broker[i]); }
  assert(read->reserved_1 == written->reserved_1);
}

/* New Order Add Message: written and read back, then read and written back */
static void check_new_order_add_message(void) {
  NewOrderAddMessage sent;
  NewOrderAddMessage got;
  uint8_t wire[50];
  uint8_t again[50];

  any_new_order_add_message(&sent);
  assert(encode_new_order_add_message(&sent, wire, 0) == 50);
  assert(decode_new_order_add_message(&got, wire, 0) == 50);
  equal_new_order_add_message(&got, &sent);

  for (size_t i = 0; i < 50; i++) { wire[i] = arbitrary(); }
  assert(decode_new_order_add_message(&got, wire, 0) == 50);
  assert(encode_new_order_add_message(&got, again, 0) == 50);
  for (size_t i = 0; i < 50; i++) { assert(again[i] == wire[i]); }
}

/* ---- Order Partial Cancel Message: 24 bytes ---------------------------------- */

/* Part of a resting order is canceled */
typedef struct {
  uint8_t timestamp[8];          /* bytes 0 to 7 */
  uint8_t order_id[8];           /* bytes 8 to 15 */
  uint8_t quantity_canceled[8];  /* bytes 16 to 23 */
} OrderPartialCancelMessage;

/* any Order Partial Cancel Message at all: every byte one the checker chooses */
static void any_order_partial_cancel_message(OrderPartialCancelMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->quantity_canceled[i] = arbitrary(); }
}

/* Order Partial Cancel Message to the wire: 24 bytes from at, returning where the next byte goes */
static size_t encode_order_partial_cancel_message(const OrderPartialCancelMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->quantity_canceled[i]; }

  return at;
}

/* Order Partial Cancel Message off the wire: 24 bytes from at, returning where the next byte lies */
static size_t decode_order_partial_cancel_message(OrderPartialCancelMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->quantity_canceled[i] = wire[at++]; }

  return at;
}

/* what was read of Order Partial Cancel Message is what was written, byte for byte */
static void equal_order_partial_cancel_message(const OrderPartialCancelMessage *read, const OrderPartialCancelMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->order_id[i] == written->order_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->quantity_canceled[i] == written->quantity_canceled[i]); }
}

/* Order Partial Cancel Message: written and read back, then read and written back */
static void check_order_partial_cancel_message(void) {
  OrderPartialCancelMessage sent;
  OrderPartialCancelMessage got;
  uint8_t wire[24];
  uint8_t again[24];

  any_order_partial_cancel_message(&sent);
  assert(encode_order_partial_cancel_message(&sent, wire, 0) == 24);
  assert(decode_order_partial_cancel_message(&got, wire, 0) == 24);
  equal_order_partial_cancel_message(&got, &sent);

  for (size_t i = 0; i < 24; i++) { wire[i] = arbitrary(); }
  assert(decode_order_partial_cancel_message(&got, wire, 0) == 24);
  assert(encode_order_partial_cancel_message(&got, again, 0) == 24);
  for (size_t i = 0; i < 24; i++) { assert(again[i] == wire[i]); }
}

/* ---- Order Cancel All Message: 16 bytes -------------------------------------- */

/* Sent when the order is canceled in its entirety */
typedef struct {
  uint8_t timestamp[8];  /* bytes 0 to 7 */
  uint8_t order_id[8];   /* bytes 8 to 15 */
} OrderCancelAllMessage;

/* any Order Cancel All Message at all: every byte one the checker chooses */
static void any_order_cancel_all_message(OrderCancelAllMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = arbitrary(); }
}

/* Order Cancel All Message to the wire: 16 bytes from at, returning where the next byte goes */
static size_t encode_order_cancel_all_message(const OrderCancelAllMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_id[i]; }

  return at;
}

/* Order Cancel All Message off the wire: 16 bytes from at, returning where the next byte lies */
static size_t decode_order_cancel_all_message(OrderCancelAllMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = wire[at++]; }

  return at;
}

/* what was read of Order Cancel All Message is what was written, byte for byte */
static void equal_order_cancel_all_message(const OrderCancelAllMessage *read, const OrderCancelAllMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->order_id[i] == written->order_id[i]); }
}

/* Order Cancel All Message: written and read back, then read and written back */
static void check_order_cancel_all_message(void) {
  OrderCancelAllMessage sent;
  OrderCancelAllMessage got;
  uint8_t wire[16];
  uint8_t again[16];

  any_order_cancel_all_message(&sent);
  assert(encode_order_cancel_all_message(&sent, wire, 0) == 16);
  assert(decode_order_cancel_all_message(&got, wire, 0) == 16);
  equal_order_cancel_all_message(&got, &sent);

  for (size_t i = 0; i < 16; i++) { wire[i] = arbitrary(); }
  assert(decode_order_cancel_all_message(&got, wire, 0) == 16);
  assert(encode_order_cancel_all_message(&got, again, 0) == 16);
  for (size_t i = 0; i < 16; i++) { assert(again[i] == wire[i]); }
}

/* ---- Order Executed Message: 47 bytes ---------------------------------------- */

/* Sent when an order is executed */
typedef struct {
  uint8_t timestamp[8];      /* bytes 0 to 7 */
  uint8_t order_id[8];       /* bytes 8 to 15 */
  uint8_t quantity[8];       /* bytes 16 to 23 */
  uint8_t execution_id[8];   /* bytes 24 to 31 */
  uint8_t side;              /* byte 32 */
  uint8_t price[8];          /* bytes 33 to 40 */
  uint8_t broker[3];         /* bytes 41 to 43 */
  uint8_t contra_broker[3];  /* bytes 44 to 46 */
} OrderExecutedMessage;

/* any Order Executed Message at all: every byte one the checker chooses */
static void any_order_executed_message(OrderExecutedMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->execution_id[i] = arbitrary(); }
  record->side = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->price[i] = arbitrary(); }
  for (size_t i = 0; i < 3; i++) { record->broker[i] = arbitrary(); }
  for (size_t i = 0; i < 3; i++) { record->contra_broker[i] = arbitrary(); }
}

/* Order Executed Message to the wire: 47 bytes from at, returning where the next byte goes */
static size_t encode_order_executed_message(const OrderExecutedMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->quantity[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->execution_id[i]; }
  wire[at++] = record->side;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price[i]; }
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->broker[i]; }
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->contra_broker[i]; }

  return at;
}

/* Order Executed Message off the wire: 47 bytes from at, returning where the next byte lies */
static size_t decode_order_executed_message(OrderExecutedMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->execution_id[i] = wire[at++]; }
  record->side = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->price[i] = wire[at++]; }
  for (size_t i = 0; i < 3; i++) { record->broker[i] = wire[at++]; }
  for (size_t i = 0; i < 3; i++) { record->contra_broker[i] = wire[at++]; }

  return at;
}

/* what was read of Order Executed Message is what was written, byte for byte */
static void equal_order_executed_message(const OrderExecutedMessage *read, const OrderExecutedMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->order_id[i] == written->order_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->quantity[i] == written->quantity[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->execution_id[i] == written->execution_id[i]); }
  assert(read->side == written->side);
  for (size_t i = 0; i < 8; i++) { assert(read->price[i] == written->price[i]); }
  for (size_t i = 0; i < 3; i++) { assert(read->broker[i] == written->broker[i]); }
  for (size_t i = 0; i < 3; i++) { assert(read->contra_broker[i] == written->contra_broker[i]); }
}

/* Order Executed Message: written and read back, then read and written back */
static void check_order_executed_message(void) {
  OrderExecutedMessage sent;
  OrderExecutedMessage got;
  uint8_t wire[47];
  uint8_t again[47];

  any_order_executed_message(&sent);
  assert(encode_order_executed_message(&sent, wire, 0) == 47);
  assert(decode_order_executed_message(&got, wire, 0) == 47);
  equal_order_executed_message(&got, &sent);

  for (size_t i = 0; i < 47; i++) { wire[i] = arbitrary(); }
  assert(decode_order_executed_message(&got, wire, 0) == 47);
  assert(encode_order_executed_message(&got, again, 0) == 47);
  for (size_t i = 0; i < 47; i++) { assert(again[i] == wire[i]); }
}

/* ---- Trade Message: 60 bytes ------------------------------------------------- */

/* Sent when a hidden order is executed */
typedef struct {
  uint8_t symbol_id[2];      /* bytes 0 to 1 */
  uint8_t timestamp[8];      /* bytes 2 to 9 */
  uint8_t reserved_8[8];     /* bytes 10 to 17 */
  uint8_t side;              /* byte 18 */
  uint8_t shares[8];         /* bytes 19 to 26 */
  uint8_t symbol[11];        /* bytes 27 to 37 */
  uint8_t price[8];          /* bytes 38 to 45 */
  uint8_t execution_id[8];   /* bytes 46 to 53 */
  uint8_t broker[3];         /* bytes 54 to 56 */
  uint8_t contra_broker[3];  /* bytes 57 to 59 */
} TradeMessage;

/* any Trade Message at all: every byte one the checker chooses */
static void any_trade_message(TradeMessage *record) {
  for (size_t i = 0; i < 2; i++) { record->symbol_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->reserved_8[i] = arbitrary(); }
  record->side = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->shares[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->symbol[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->execution_id[i] = arbitrary(); }
  for (size_t i = 0; i < 3; i++) { record->broker[i] = arbitrary(); }
  for (size_t i = 0; i < 3; i++) { record->contra_broker[i] = arbitrary(); }
}

/* Trade Message to the wire: 60 bytes from at, returning where the next byte goes */
static size_t encode_trade_message(const TradeMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->symbol_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->reserved_8[i]; }
  wire[at++] = record->side;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->shares[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->symbol[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->execution_id[i]; }
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->broker[i]; }
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->contra_broker[i]; }

  return at;
}

/* Trade Message off the wire: 60 bytes from at, returning where the next byte lies */
static size_t decode_trade_message(TradeMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->symbol_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->reserved_8[i] = wire[at++]; }
  record->side = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->shares[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->symbol[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->execution_id[i] = wire[at++]; }
  for (size_t i = 0; i < 3; i++) { record->broker[i] = wire[at++]; }
  for (size_t i = 0; i < 3; i++) { record->contra_broker[i] = wire[at++]; }

  return at;
}

/* what was read of Trade Message is what was written, byte for byte */
static void equal_trade_message(const TradeMessage *read, const TradeMessage *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->symbol_id[i] == written->symbol_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->reserved_8[i] == written->reserved_8[i]); }
  assert(read->side == written->side);
  for (size_t i = 0; i < 8; i++) { assert(read->shares[i] == written->shares[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->symbol[i] == written->symbol[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->price[i] == written->price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->execution_id[i] == written->execution_id[i]); }
  for (size_t i = 0; i < 3; i++) { assert(read->broker[i] == written->broker[i]); }
  for (size_t i = 0; i < 3; i++) { assert(read->contra_broker[i] == written->contra_broker[i]); }
}

/* Trade Message: written and read back, then read and written back */
static void check_trade_message(void) {
  TradeMessage sent;
  TradeMessage got;
  uint8_t wire[60];
  uint8_t again[60];

  any_trade_message(&sent);
  assert(encode_trade_message(&sent, wire, 0) == 60);
  assert(decode_trade_message(&got, wire, 0) == 60);
  equal_trade_message(&got, &sent);

  for (size_t i = 0; i < 60; i++) { wire[i] = arbitrary(); }
  assert(decode_trade_message(&got, wire, 0) == 60);
  assert(encode_trade_message(&got, again, 0) == 60);
  for (size_t i = 0; i < 60; i++) { assert(again[i] == wire[i]); }
}

/* ---- Trade Cancel Message: 60 bytes ------------------------------------------ */

/* Sent whenever an execution on CIX ATS is cancelled */
typedef struct {
  uint8_t symbol_id[2];      /* bytes 0 to 1 */
  uint8_t timestamp[8];      /* bytes 2 to 9 */
  uint8_t reserved_8[8];     /* bytes 10 to 17 */
  uint8_t reserved_1;        /* byte 18 */
  uint8_t shares[8];         /* bytes 19 to 26 */
  uint8_t symbol[11];        /* bytes 27 to 37 */
  uint8_t price[8];          /* bytes 38 to 45 */
  uint8_t execution_id[8];   /* bytes 46 to 53 */
  uint8_t broker[3];         /* bytes 54 to 56 */
  uint8_t contra_broker[3];  /* bytes 57 to 59 */
} TradeCancelMessage;

/* any Trade Cancel Message at all: every byte one the checker chooses */
static void any_trade_cancel_message(TradeCancelMessage *record) {
  for (size_t i = 0; i < 2; i++) { record->symbol_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->reserved_8[i] = arbitrary(); }
  record->reserved_1 = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->shares[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->symbol[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->execution_id[i] = arbitrary(); }
  for (size_t i = 0; i < 3; i++) { record->broker[i] = arbitrary(); }
  for (size_t i = 0; i < 3; i++) { record->contra_broker[i] = arbitrary(); }
}

/* Trade Cancel Message to the wire: 60 bytes from at, returning where the next byte goes */
static size_t encode_trade_cancel_message(const TradeCancelMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->symbol_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->reserved_8[i]; }
  wire[at++] = record->reserved_1;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->shares[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->symbol[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->execution_id[i]; }
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->broker[i]; }
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->contra_broker[i]; }

  return at;
}

/* Trade Cancel Message off the wire: 60 bytes from at, returning where the next byte lies */
static size_t decode_trade_cancel_message(TradeCancelMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->symbol_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->reserved_8[i] = wire[at++]; }
  record->reserved_1 = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->shares[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->symbol[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->execution_id[i] = wire[at++]; }
  for (size_t i = 0; i < 3; i++) { record->broker[i] = wire[at++]; }
  for (size_t i = 0; i < 3; i++) { record->contra_broker[i] = wire[at++]; }

  return at;
}

/* what was read of Trade Cancel Message is what was written, byte for byte */
static void equal_trade_cancel_message(const TradeCancelMessage *read, const TradeCancelMessage *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->symbol_id[i] == written->symbol_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->reserved_8[i] == written->reserved_8[i]); }
  assert(read->reserved_1 == written->reserved_1);
  for (size_t i = 0; i < 8; i++) { assert(read->shares[i] == written->shares[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->symbol[i] == written->symbol[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->price[i] == written->price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->execution_id[i] == written->execution_id[i]); }
  for (size_t i = 0; i < 3; i++) { assert(read->broker[i] == written->broker[i]); }
  for (size_t i = 0; i < 3; i++) { assert(read->contra_broker[i] == written->contra_broker[i]); }
}

/* Trade Cancel Message: written and read back, then read and written back */
static void check_trade_cancel_message(void) {
  TradeCancelMessage sent;
  TradeCancelMessage got;
  uint8_t wire[60];
  uint8_t again[60];

  any_trade_cancel_message(&sent);
  assert(encode_trade_cancel_message(&sent, wire, 0) == 60);
  assert(decode_trade_cancel_message(&got, wire, 0) == 60);
  equal_trade_cancel_message(&got, &sent);

  for (size_t i = 0; i < 60; i++) { wire[i] = arbitrary(); }
  assert(decode_trade_cancel_message(&got, wire, 0) == 60);
  assert(encode_trade_cancel_message(&got, again, 0) == 60);
  for (size_t i = 0; i < 60; i++) { assert(again[i] == wire[i]); }
}

/* ---- Trade Correct Message: 84 bytes ----------------------------------------- */

/* Sent whenever an execution on CIX ATS is amended */
typedef struct {
  uint8_t symbol_id[2];                 /* bytes 0 to 1 */
  uint8_t timestamp[8];                 /* bytes 2 to 9 */
  uint8_t reserved_8[8];                /* bytes 10 to 17 */
  uint8_t reserved_1;                   /* byte 18 */
  uint8_t symbol[11];                   /* bytes 19 to 29 */
  uint8_t execution_id[8];              /* bytes 30 to 37 */
  uint8_t broker[3];                    /* bytes 38 to 40 */
  uint8_t contra_broker[3];             /* bytes 41 to 43 */
  uint8_t original_execution_id[8];     /* bytes 44 to 51 */
  uint8_t original_trade_price[8];      /* bytes 52 to 59 */
  uint8_t original_trade_quantity[8];   /* bytes 60 to 67 */
  uint8_t corrected_trade_price[8];     /* bytes 68 to 75 */
  uint8_t corrected_trade_quantity[8];  /* bytes 76 to 83 */
} TradeCorrectMessage;

/* any Trade Correct Message at all: every byte one the checker chooses */
static void any_trade_correct_message(TradeCorrectMessage *record) {
  for (size_t i = 0; i < 2; i++) { record->symbol_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->reserved_8[i] = arbitrary(); }
  record->reserved_1 = arbitrary();
  for (size_t i = 0; i < 11; i++) { record->symbol[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->execution_id[i] = arbitrary(); }
  for (size_t i = 0; i < 3; i++) { record->broker[i] = arbitrary(); }
  for (size_t i = 0; i < 3; i++) { record->contra_broker[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->original_execution_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->original_trade_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->original_trade_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->corrected_trade_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->corrected_trade_quantity[i] = arbitrary(); }
}

/* Trade Correct Message to the wire: 84 bytes from at, returning where the next byte goes */
static size_t encode_trade_correct_message(const TradeCorrectMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->symbol_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->reserved_8[i]; }
  wire[at++] = record->reserved_1;
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->symbol[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->execution_id[i]; }
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->broker[i]; }
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->contra_broker[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->original_execution_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->original_trade_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->original_trade_quantity[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->corrected_trade_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->corrected_trade_quantity[i]; }

  return at;
}

/* Trade Correct Message off the wire: 84 bytes from at, returning where the next byte lies */
static size_t decode_trade_correct_message(TradeCorrectMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->symbol_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->reserved_8[i] = wire[at++]; }
  record->reserved_1 = wire[at++];
  for (size_t i = 0; i < 11; i++) { record->symbol[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->execution_id[i] = wire[at++]; }
  for (size_t i = 0; i < 3; i++) { record->broker[i] = wire[at++]; }
  for (size_t i = 0; i < 3; i++) { record->contra_broker[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->original_execution_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->original_trade_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->original_trade_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->corrected_trade_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->corrected_trade_quantity[i] = wire[at++]; }

  return at;
}

/* what was read of Trade Correct Message is what was written, byte for byte */
static void equal_trade_correct_message(const TradeCorrectMessage *read, const TradeCorrectMessage *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->symbol_id[i] == written->symbol_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->reserved_8[i] == written->reserved_8[i]); }
  assert(read->reserved_1 == written->reserved_1);
  for (size_t i = 0; i < 11; i++) { assert(read->symbol[i] == written->symbol[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->execution_id[i] == written->execution_id[i]); }
  for (size_t i = 0; i < 3; i++) { assert(read->broker[i] == written->broker[i]); }
  for (size_t i = 0; i < 3; i++) { assert(read->contra_broker[i] == written->contra_broker[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->original_execution_id[i] == written->original_execution_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->original_trade_price[i] == written->original_trade_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->original_trade_quantity[i] == written->original_trade_quantity[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->corrected_trade_price[i] == written->corrected_trade_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->corrected_trade_quantity[i] == written->corrected_trade_quantity[i]); }
}

/* Trade Correct Message: written and read back, then read and written back */
static void check_trade_correct_message(void) {
  TradeCorrectMessage sent;
  TradeCorrectMessage got;
  uint8_t wire[84];
  uint8_t again[84];

  any_trade_correct_message(&sent);
  assert(encode_trade_correct_message(&sent, wire, 0) == 84);
  assert(decode_trade_correct_message(&got, wire, 0) == 84);
  equal_trade_correct_message(&got, &sent);

  for (size_t i = 0; i < 84; i++) { wire[i] = arbitrary(); }
  assert(decode_trade_correct_message(&got, wire, 0) == 84);
  assert(encode_trade_correct_message(&got, again, 0) == 84);
  for (size_t i = 0; i < 84; i++) { assert(again[i] == wire[i]); }
}

/* ---- What esbmc checks ------------------------------------------------------- */

/* every record of the protocol, each on its own buffers */
static void checks(void) {
  check_packet_header();
  check_message_header();
  check_market_event_message();
  check_symbol_information_message();
  check_symbol_state_message();
  check_new_order_add_message();
  check_order_partial_cancel_message();
  check_order_cancel_all_message();
  check_order_executed_message();
  check_trade_message();
  check_trade_cancel_message();
  check_trade_correct_message();
}

int main(void) {
#ifdef CONCRETE
  for (pattern = 0; pattern < 4; pattern++) { checks(); }
#else
  checks();
#endif

  return 0;
}
