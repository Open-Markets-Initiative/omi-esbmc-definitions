// tmx/tsxalpha/level1/TsxAlpha_Level1_v2_1.c
/*
 * TMX Group Level 1
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

/* ---- Message Header: 22 bytes ------------------------------------------------ */

/* Twenty two byte ascii header carried on every Qrtmd message */
typedef struct {
  uint8_t message_length[4];          /* bytes 0 to 3 */
  uint8_t sequence_number[9];         /* bytes 4 to 12 */
  uint8_t service_identifier[3];      /* bytes 13 to 15 */
  uint8_t retransmission_identifier;  /* byte 16 */
  uint8_t continuation_identifier;    /* byte 17 */
  uint8_t message_type[2];            /* bytes 18 to 19 */
  uint8_t exchange_identifier[2];     /* bytes 20 to 21 */
} MessageHeader;

/* any Message Header at all: every byte one the checker chooses */
static void any_message_header(MessageHeader *record) {
  for (size_t i = 0; i < 4; i++) { record->message_length[i] = arbitrary(); }
  for (size_t i = 0; i < 9; i++) { record->sequence_number[i] = arbitrary(); }
  for (size_t i = 0; i < 3; i++) { record->service_identifier[i] = arbitrary(); }
  record->retransmission_identifier = arbitrary();
  record->continuation_identifier = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->message_type[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->exchange_identifier[i] = arbitrary(); }
}

/* Message Header to the wire: 22 bytes from at, returning where the next byte goes */
static size_t encode_message_header(const MessageHeader *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->message_length[i]; }
  for (size_t i = 0; i < 9; i++) { wire[at++] = record->sequence_number[i]; }
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->service_identifier[i]; }
  wire[at++] = record->retransmission_identifier;
  wire[at++] = record->continuation_identifier;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->message_type[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->exchange_identifier[i]; }

  return at;
}

/* Message Header off the wire: 22 bytes from at, returning where the next byte lies */
static size_t decode_message_header(MessageHeader *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->message_length[i] = wire[at++]; }
  for (size_t i = 0; i < 9; i++) { record->sequence_number[i] = wire[at++]; }
  for (size_t i = 0; i < 3; i++) { record->service_identifier[i] = wire[at++]; }
  record->retransmission_identifier = wire[at++];
  record->continuation_identifier = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->message_type[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->exchange_identifier[i] = wire[at++]; }

  return at;
}

/* what was read of Message Header is what was written, byte for byte */
static void equal_message_header(const MessageHeader *read, const MessageHeader *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->message_length[i] == written->message_length[i]); }
  for (size_t i = 0; i < 9; i++) { assert(read->sequence_number[i] == written->sequence_number[i]); }
  for (size_t i = 0; i < 3; i++) { assert(read->service_identifier[i] == written->service_identifier[i]); }
  assert(read->retransmission_identifier == written->retransmission_identifier);
  assert(read->continuation_identifier == written->continuation_identifier);
  for (size_t i = 0; i < 2; i++) { assert(read->message_type[i] == written->message_type[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->exchange_identifier[i] == written->exchange_identifier[i]); }
}

/* Message Header: written and read back, then read and written back */
static void check_message_header(void) {
  MessageHeader sent;
  MessageHeader got;
  uint8_t wire[22];
  uint8_t again[22];

  any_message_header(&sent);
  assert(encode_message_header(&sent, wire, 0) == 22);
  assert(decode_message_header(&got, wire, 0) == 22);
  equal_message_header(&got, &sent);

  for (size_t i = 0; i < 22; i++) { wire[i] = arbitrary(); }
  assert(decode_message_header(&got, wire, 0) == 22);
  assert(encode_message_header(&got, again, 0) == 22);
  for (size_t i = 0; i < 22; i++) { assert(again[i] == wire[i]); }
}

/* ---- Trade Message: 92 bytes ------------------------------------------------- */

/* A trade in an equity on the Alpha market. */
typedef struct {
  uint8_t symbol[12];                     /* bytes 0 to 11 */
  uint8_t volume[9];                      /* bytes 12 to 20 */
  uint8_t trade_price[11];                /* bytes 21 to 31 */
  uint8_t buyer_id[3];                    /* bytes 32 to 34 */
  uint8_t seller_id[3];                   /* bytes 35 to 37 */
  uint8_t trade_time_stamp[6];            /* bytes 38 to 43 */
  uint8_t last_sale[11];                  /* bytes 44 to 54 */
  uint8_t trade_id[9];                    /* bytes 55 to 63 */
  uint8_t cross_type;                     /* byte 64 */
  uint8_t bypass;                         /* byte 65 */
  uint8_t opening_trade;                  /* byte 66 */
  uint8_t settlement_terms;               /* byte 67 */
  uint8_t is_dark;                        /* byte 68 */
  uint8_t trading_system_time_stamp[23];  /* bytes 69 to 91 */
} TradeMessage;

/* any Trade Message at all: every byte one the checker chooses */
static void any_trade_message(TradeMessage *record) {
  for (size_t i = 0; i < 12; i++) { record->symbol[i] = arbitrary(); }
  for (size_t i = 0; i < 9; i++) { record->volume[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->trade_price[i] = arbitrary(); }
  for (size_t i = 0; i < 3; i++) { record->buyer_id[i] = arbitrary(); }
  for (size_t i = 0; i < 3; i++) { record->seller_id[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->trade_time_stamp[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->last_sale[i] = arbitrary(); }
  for (size_t i = 0; i < 9; i++) { record->trade_id[i] = arbitrary(); }
  record->cross_type = arbitrary();
  record->bypass = arbitrary();
  record->opening_trade = arbitrary();
  record->settlement_terms = arbitrary();
  record->is_dark = arbitrary();
  for (size_t i = 0; i < 23; i++) { record->trading_system_time_stamp[i] = arbitrary(); }
}

/* Trade Message to the wire: 92 bytes from at, returning where the next byte goes */
static size_t encode_trade_message(const TradeMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->symbol[i]; }
  for (size_t i = 0; i < 9; i++) { wire[at++] = record->volume[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->trade_price[i]; }
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->buyer_id[i]; }
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->seller_id[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->trade_time_stamp[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->last_sale[i]; }
  for (size_t i = 0; i < 9; i++) { wire[at++] = record->trade_id[i]; }
  wire[at++] = record->cross_type;
  wire[at++] = record->bypass;
  wire[at++] = record->opening_trade;
  wire[at++] = record->settlement_terms;
  wire[at++] = record->is_dark;
  for (size_t i = 0; i < 23; i++) { wire[at++] = record->trading_system_time_stamp[i]; }

  return at;
}

/* Trade Message off the wire: 92 bytes from at, returning where the next byte lies */
static size_t decode_trade_message(TradeMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 12; i++) { record->symbol[i] = wire[at++]; }
  for (size_t i = 0; i < 9; i++) { record->volume[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->trade_price[i] = wire[at++]; }
  for (size_t i = 0; i < 3; i++) { record->buyer_id[i] = wire[at++]; }
  for (size_t i = 0; i < 3; i++) { record->seller_id[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->trade_time_stamp[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->last_sale[i] = wire[at++]; }
  for (size_t i = 0; i < 9; i++) { record->trade_id[i] = wire[at++]; }
  record->cross_type = wire[at++];
  record->bypass = wire[at++];
  record->opening_trade = wire[at++];
  record->settlement_terms = wire[at++];
  record->is_dark = wire[at++];
  for (size_t i = 0; i < 23; i++) { record->trading_system_time_stamp[i] = wire[at++]; }

  return at;
}

/* what was read of Trade Message is what was written, byte for byte */
static void equal_trade_message(const TradeMessage *read, const TradeMessage *written) {
  for (size_t i = 0; i < 12; i++) { assert(read->symbol[i] == written->symbol[i]); }
  for (size_t i = 0; i < 9; i++) { assert(read->volume[i] == written->volume[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->trade_price[i] == written->trade_price[i]); }
  for (size_t i = 0; i < 3; i++) { assert(read->buyer_id[i] == written->buyer_id[i]); }
  for (size_t i = 0; i < 3; i++) { assert(read->seller_id[i] == written->seller_id[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->trade_time_stamp[i] == written->trade_time_stamp[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->last_sale[i] == written->last_sale[i]); }
  for (size_t i = 0; i < 9; i++) { assert(read->trade_id[i] == written->trade_id[i]); }
  assert(read->cross_type == written->cross_type);
  assert(read->bypass == written->bypass);
  assert(read->opening_trade == written->opening_trade);
  assert(read->settlement_terms == written->settlement_terms);
  assert(read->is_dark == written->is_dark);
  for (size_t i = 0; i < 23; i++) { assert(read->trading_system_time_stamp[i] == written->trading_system_time_stamp[i]); }
}

/* Trade Message: written and read back, then read and written back */
static void check_trade_message(void) {
  TradeMessage sent;
  TradeMessage got;
  uint8_t wire[92];
  uint8_t again[92];

  any_trade_message(&sent);
  assert(encode_trade_message(&sent, wire, 0) == 92);
  assert(decode_trade_message(&got, wire, 0) == 92);
  equal_trade_message(&got, &sent);

  for (size_t i = 0; i < 92; i++) { wire[i] = arbitrary(); }
  assert(decode_trade_message(&got, wire, 0) == 92);
  assert(encode_trade_message(&got, again, 0) == 92);
  for (size_t i = 0; i < 92; i++) { assert(again[i] == wire[i]); }
}

/* ---- Symbol Status Message: 136 bytes ---------------------------------------- */

/* Reference information for a symbol trading on the current day. */
typedef struct {
  uint8_t symbol[12];                     /* bytes 0 to 11 */
  uint8_t trading_system_time_stamp[23];  /* bytes 12 to 34 */
  uint8_t exchange_id[3];                 /* bytes 35 to 37 */
  uint8_t cusip[12];                      /* bytes 38 to 49 */
  uint8_t board_lot[9];                   /* bytes 50 to 58 */
  uint8_t currency;                       /* byte 59 */
  uint8_t face_value[9];                  /* bytes 60 to 68 */
  uint8_t last_sale[11];                  /* bytes 69 to 79 */
  uint8_t product_type;                   /* byte 80 */
  uint8_t symbol_name[40];                /* bytes 81 to 120 */
  uint8_t stock_group[2];                 /* bytes 121 to 122 */
  uint8_t stock_state[2];                 /* bytes 123 to 124 */
  uint8_t listing_market;                 /* byte 125 */
  uint8_t min_po_qty[9];                  /* bytes 126 to 134 */
  uint8_t test_symbol;                    /* byte 135 */
} SymbolStatusMessage;

/* any Symbol Status Message at all: every byte one the checker chooses */
static void any_symbol_status_message(SymbolStatusMessage *record) {
  for (size_t i = 0; i < 12; i++) { record->symbol[i] = arbitrary(); }
  for (size_t i = 0; i < 23; i++) { record->trading_system_time_stamp[i] = arbitrary(); }
  for (size_t i = 0; i < 3; i++) { record->exchange_id[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->cusip[i] = arbitrary(); }
  for (size_t i = 0; i < 9; i++) { record->board_lot[i] = arbitrary(); }
  record->currency = arbitrary();
  for (size_t i = 0; i < 9; i++) { record->face_value[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->last_sale[i] = arbitrary(); }
  record->product_type = arbitrary();
  for (size_t i = 0; i < 40; i++) { record->symbol_name[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->stock_group[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->stock_state[i] = arbitrary(); }
  record->listing_market = arbitrary();
  for (size_t i = 0; i < 9; i++) { record->min_po_qty[i] = arbitrary(); }
  record->test_symbol = arbitrary();
}

/* Symbol Status Message to the wire: 136 bytes from at, returning where the next byte goes */
static size_t encode_symbol_status_message(const SymbolStatusMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->symbol[i]; }
  for (size_t i = 0; i < 23; i++) { wire[at++] = record->trading_system_time_stamp[i]; }
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->exchange_id[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->cusip[i]; }
  for (size_t i = 0; i < 9; i++) { wire[at++] = record->board_lot[i]; }
  wire[at++] = record->currency;
  for (size_t i = 0; i < 9; i++) { wire[at++] = record->face_value[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->last_sale[i]; }
  wire[at++] = record->product_type;
  for (size_t i = 0; i < 40; i++) { wire[at++] = record->symbol_name[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->stock_group[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->stock_state[i]; }
  wire[at++] = record->listing_market;
  for (size_t i = 0; i < 9; i++) { wire[at++] = record->min_po_qty[i]; }
  wire[at++] = record->test_symbol;

  return at;
}

/* Symbol Status Message off the wire: 136 bytes from at, returning where the next byte lies */
static size_t decode_symbol_status_message(SymbolStatusMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 12; i++) { record->symbol[i] = wire[at++]; }
  for (size_t i = 0; i < 23; i++) { record->trading_system_time_stamp[i] = wire[at++]; }
  for (size_t i = 0; i < 3; i++) { record->exchange_id[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->cusip[i] = wire[at++]; }
  for (size_t i = 0; i < 9; i++) { record->board_lot[i] = wire[at++]; }
  record->currency = wire[at++];
  for (size_t i = 0; i < 9; i++) { record->face_value[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->last_sale[i] = wire[at++]; }
  record->product_type = wire[at++];
  for (size_t i = 0; i < 40; i++) { record->symbol_name[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->stock_group[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->stock_state[i] = wire[at++]; }
  record->listing_market = wire[at++];
  for (size_t i = 0; i < 9; i++) { record->min_po_qty[i] = wire[at++]; }
  record->test_symbol = wire[at++];

  return at;
}

/* what was read of Symbol Status Message is what was written, byte for byte */
static void equal_symbol_status_message(const SymbolStatusMessage *read, const SymbolStatusMessage *written) {
  for (size_t i = 0; i < 12; i++) { assert(read->symbol[i] == written->symbol[i]); }
  for (size_t i = 0; i < 23; i++) { assert(read->trading_system_time_stamp[i] == written->trading_system_time_stamp[i]); }
  for (size_t i = 0; i < 3; i++) { assert(read->exchange_id[i] == written->exchange_id[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->cusip[i] == written->cusip[i]); }
  for (size_t i = 0; i < 9; i++) { assert(read->board_lot[i] == written->board_lot[i]); }
  assert(read->currency == written->currency);
  for (size_t i = 0; i < 9; i++) { assert(read->face_value[i] == written->face_value[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->last_sale[i] == written->last_sale[i]); }
  assert(read->product_type == written->product_type);
  for (size_t i = 0; i < 40; i++) { assert(read->symbol_name[i] == written->symbol_name[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->stock_group[i] == written->stock_group[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->stock_state[i] == written->stock_state[i]); }
  assert(read->listing_market == written->listing_market);
  for (size_t i = 0; i < 9; i++) { assert(read->min_po_qty[i] == written->min_po_qty[i]); }
  assert(read->test_symbol == written->test_symbol);
}

/* Symbol Status Message: written and read back, then read and written back */
static void check_symbol_status_message(void) {
  SymbolStatusMessage sent;
  SymbolStatusMessage got;
  uint8_t wire[136];
  uint8_t again[136];

  any_symbol_status_message(&sent);
  assert(encode_symbol_status_message(&sent, wire, 0) == 136);
  assert(decode_symbol_status_message(&got, wire, 0) == 136);
  equal_symbol_status_message(&got, &sent);

  for (size_t i = 0; i < 136; i++) { wire[i] = arbitrary(); }
  assert(decode_symbol_status_message(&got, wire, 0) == 136);
  assert(encode_symbol_status_message(&got, again, 0) == 136);
  for (size_t i = 0; i < 136; i++) { assert(again[i] == wire[i]); }
}

/* ---- Stock State Message: 83 bytes ------------------------------------------- */

/* A change in the trading state of a stock. */
typedef struct {
  uint8_t symbol[12];                     /* bytes 0 to 11 */
  uint8_t trading_system_time_stamp[23];  /* bytes 12 to 34 */
  uint8_t comment[40];                    /* bytes 35 to 74 */
  uint8_t stock_state[2];                 /* bytes 75 to 76 */
  uint8_t opening_time[6];                /* bytes 77 to 82 */
} StockStateMessage;

/* any Stock State Message at all: every byte one the checker chooses */
static void any_stock_state_message(StockStateMessage *record) {
  for (size_t i = 0; i < 12; i++) { record->symbol[i] = arbitrary(); }
  for (size_t i = 0; i < 23; i++) { record->trading_system_time_stamp[i] = arbitrary(); }
  for (size_t i = 0; i < 40; i++) { record->comment[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->stock_state[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->opening_time[i] = arbitrary(); }
}

/* Stock State Message to the wire: 83 bytes from at, returning where the next byte goes */
static size_t encode_stock_state_message(const StockStateMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->symbol[i]; }
  for (size_t i = 0; i < 23; i++) { wire[at++] = record->trading_system_time_stamp[i]; }
  for (size_t i = 0; i < 40; i++) { wire[at++] = record->comment[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->stock_state[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->opening_time[i]; }

  return at;
}

/* Stock State Message off the wire: 83 bytes from at, returning where the next byte lies */
static size_t decode_stock_state_message(StockStateMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 12; i++) { record->symbol[i] = wire[at++]; }
  for (size_t i = 0; i < 23; i++) { record->trading_system_time_stamp[i] = wire[at++]; }
  for (size_t i = 0; i < 40; i++) { record->comment[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->stock_state[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->opening_time[i] = wire[at++]; }

  return at;
}

/* what was read of Stock State Message is what was written, byte for byte */
static void equal_stock_state_message(const StockStateMessage *read, const StockStateMessage *written) {
  for (size_t i = 0; i < 12; i++) { assert(read->symbol[i] == written->symbol[i]); }
  for (size_t i = 0; i < 23; i++) { assert(read->trading_system_time_stamp[i] == written->trading_system_time_stamp[i]); }
  for (size_t i = 0; i < 40; i++) { assert(read->comment[i] == written->comment[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->stock_state[i] == written->stock_state[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->opening_time[i] == written->opening_time[i]); }
}

/* Stock State Message: written and read back, then read and written back */
static void check_stock_state_message(void) {
  StockStateMessage sent;
  StockStateMessage got;
  uint8_t wire[83];
  uint8_t again[83];

  any_stock_state_message(&sent);
  assert(encode_stock_state_message(&sent, wire, 0) == 83);
  assert(decode_stock_state_message(&got, wire, 0) == 83);
  equal_stock_state_message(&got, &sent);

  for (size_t i = 0; i < 83; i++) { wire[i] = arbitrary(); }
  assert(decode_stock_state_message(&got, wire, 0) == 83);
  assert(encode_stock_state_message(&got, again, 0) == 83);
  for (size_t i = 0; i < 83; i++) { assert(again[i] == wire[i]); }
}

/* ---- Quote Message: 71 bytes ------------------------------------------------- */

/* Full update quote sent whenever either the bid or the ask has changed. */
typedef struct {
  uint8_t symbol[12];                     /* bytes 0 to 11 */
  uint8_t bid_price[9];                   /* bytes 12 to 20 */
  uint8_t bid_size[9];                    /* bytes 21 to 29 */
  uint8_t ask_price[9];                   /* bytes 30 to 38 */
  uint8_t ask_size[9];                    /* bytes 39 to 47 */
  uint8_t trading_system_time_stamp[23];  /* bytes 48 to 70 */
} QuoteMessage;

/* any Quote Message at all: every byte one the checker chooses */
static void any_quote_message(QuoteMessage *record) {
  for (size_t i = 0; i < 12; i++) { record->symbol[i] = arbitrary(); }
  for (size_t i = 0; i < 9; i++) { record->bid_price[i] = arbitrary(); }
  for (size_t i = 0; i < 9; i++) { record->bid_size[i] = arbitrary(); }
  for (size_t i = 0; i < 9; i++) { record->ask_price[i] = arbitrary(); }
  for (size_t i = 0; i < 9; i++) { record->ask_size[i] = arbitrary(); }
  for (size_t i = 0; i < 23; i++) { record->trading_system_time_stamp[i] = arbitrary(); }
}

/* Quote Message to the wire: 71 bytes from at, returning where the next byte goes */
static size_t encode_quote_message(const QuoteMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->symbol[i]; }
  for (size_t i = 0; i < 9; i++) { wire[at++] = record->bid_price[i]; }
  for (size_t i = 0; i < 9; i++) { wire[at++] = record->bid_size[i]; }
  for (size_t i = 0; i < 9; i++) { wire[at++] = record->ask_price[i]; }
  for (size_t i = 0; i < 9; i++) { wire[at++] = record->ask_size[i]; }
  for (size_t i = 0; i < 23; i++) { wire[at++] = record->trading_system_time_stamp[i]; }

  return at;
}

/* Quote Message off the wire: 71 bytes from at, returning where the next byte lies */
static size_t decode_quote_message(QuoteMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 12; i++) { record->symbol[i] = wire[at++]; }
  for (size_t i = 0; i < 9; i++) { record->bid_price[i] = wire[at++]; }
  for (size_t i = 0; i < 9; i++) { record->bid_size[i] = wire[at++]; }
  for (size_t i = 0; i < 9; i++) { record->ask_price[i] = wire[at++]; }
  for (size_t i = 0; i < 9; i++) { record->ask_size[i] = wire[at++]; }
  for (size_t i = 0; i < 23; i++) { record->trading_system_time_stamp[i] = wire[at++]; }

  return at;
}

/* what was read of Quote Message is what was written, byte for byte */
static void equal_quote_message(const QuoteMessage *read, const QuoteMessage *written) {
  for (size_t i = 0; i < 12; i++) { assert(read->symbol[i] == written->symbol[i]); }
  for (size_t i = 0; i < 9; i++) { assert(read->bid_price[i] == written->bid_price[i]); }
  for (size_t i = 0; i < 9; i++) { assert(read->bid_size[i] == written->bid_size[i]); }
  for (size_t i = 0; i < 9; i++) { assert(read->ask_price[i] == written->ask_price[i]); }
  for (size_t i = 0; i < 9; i++) { assert(read->ask_size[i] == written->ask_size[i]); }
  for (size_t i = 0; i < 23; i++) { assert(read->trading_system_time_stamp[i] == written->trading_system_time_stamp[i]); }
}

/* Quote Message: written and read back, then read and written back */
static void check_quote_message(void) {
  QuoteMessage sent;
  QuoteMessage got;
  uint8_t wire[71];
  uint8_t again[71];

  any_quote_message(&sent);
  assert(encode_quote_message(&sent, wire, 0) == 71);
  assert(decode_quote_message(&got, wire, 0) == 71);
  equal_quote_message(&got, &sent);

  for (size_t i = 0; i < 71; i++) { wire[i] = arbitrary(); }
  assert(decode_quote_message(&got, wire, 0) == 71);
  assert(encode_quote_message(&got, again, 0) == 71);
  for (size_t i = 0; i < 71; i++) { assert(again[i] == wire[i]); }
}

/* ---- General Message: 104 bytes ---------------------------------------------- */

/* Bulletin in textual format. */
typedef struct {
  uint8_t trading_system_time_stamp[23];  /* bytes 0 to 22 */
  uint8_t bulletin_indicator;             /* byte 23 */
  uint8_t message_text[80];               /* bytes 24 to 103 */
} GeneralMessage;

/* any General Message at all: every byte one the checker chooses */
static void any_general_message(GeneralMessage *record) {
  for (size_t i = 0; i < 23; i++) { record->trading_system_time_stamp[i] = arbitrary(); }
  record->bulletin_indicator = arbitrary();
  for (size_t i = 0; i < 80; i++) { record->message_text[i] = arbitrary(); }
}

/* General Message to the wire: 104 bytes from at, returning where the next byte goes */
static size_t encode_general_message(const GeneralMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 23; i++) { wire[at++] = record->trading_system_time_stamp[i]; }
  wire[at++] = record->bulletin_indicator;
  for (size_t i = 0; i < 80; i++) { wire[at++] = record->message_text[i]; }

  return at;
}

/* General Message off the wire: 104 bytes from at, returning where the next byte lies */
static size_t decode_general_message(GeneralMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 23; i++) { record->trading_system_time_stamp[i] = wire[at++]; }
  record->bulletin_indicator = wire[at++];
  for (size_t i = 0; i < 80; i++) { record->message_text[i] = wire[at++]; }

  return at;
}

/* what was read of General Message is what was written, byte for byte */
static void equal_general_message(const GeneralMessage *read, const GeneralMessage *written) {
  for (size_t i = 0; i < 23; i++) { assert(read->trading_system_time_stamp[i] == written->trading_system_time_stamp[i]); }
  assert(read->bulletin_indicator == written->bulletin_indicator);
  for (size_t i = 0; i < 80; i++) { assert(read->message_text[i] == written->message_text[i]); }
}

/* General Message: written and read back, then read and written back */
static void check_general_message(void) {
  GeneralMessage sent;
  GeneralMessage got;
  uint8_t wire[104];
  uint8_t again[104];

  any_general_message(&sent);
  assert(encode_general_message(&sent, wire, 0) == 104);
  assert(decode_general_message(&got, wire, 0) == 104);
  equal_general_message(&got, &sent);

  for (size_t i = 0; i < 104; i++) { wire[i] = arbitrary(); }
  assert(decode_general_message(&got, wire, 0) == 104);
  assert(encode_general_message(&got, again, 0) == 104);
  for (size_t i = 0; i < 104; i++) { assert(again[i] == wire[i]); }
}

/* ---- Trade Cancellation Message: 87 bytes ------------------------------------ */

/* Cancellation of a trade, reducing total volume, value and transactions by the amount of the cancellation. */
typedef struct {
  uint8_t symbol[12];                     /* bytes 0 to 11 */
  uint8_t volume[9];                      /* bytes 12 to 20 */
  uint8_t trade_price[11];                /* bytes 21 to 31 */
  uint8_t buyer_id[3];                    /* bytes 32 to 34 */
  uint8_t seller_id[3];                   /* bytes 35 to 37 */
  uint8_t trade_time_stamp[6];            /* bytes 38 to 43 */
  uint8_t original_trade_id[9];           /* bytes 44 to 52 */
  uint8_t last_sale[11];                  /* bytes 53 to 63 */
  uint8_t trading_system_time_stamp[23];  /* bytes 64 to 86 */
} TradeCancellationMessage;

/* any Trade Cancellation Message at all: every byte one the checker chooses */
static void any_trade_cancellation_message(TradeCancellationMessage *record) {
  for (size_t i = 0; i < 12; i++) { record->symbol[i] = arbitrary(); }
  for (size_t i = 0; i < 9; i++) { record->volume[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->trade_price[i] = arbitrary(); }
  for (size_t i = 0; i < 3; i++) { record->buyer_id[i] = arbitrary(); }
  for (size_t i = 0; i < 3; i++) { record->seller_id[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->trade_time_stamp[i] = arbitrary(); }
  for (size_t i = 0; i < 9; i++) { record->original_trade_id[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->last_sale[i] = arbitrary(); }
  for (size_t i = 0; i < 23; i++) { record->trading_system_time_stamp[i] = arbitrary(); }
}

/* Trade Cancellation Message to the wire: 87 bytes from at, returning where the next byte goes */
static size_t encode_trade_cancellation_message(const TradeCancellationMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->symbol[i]; }
  for (size_t i = 0; i < 9; i++) { wire[at++] = record->volume[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->trade_price[i]; }
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->buyer_id[i]; }
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->seller_id[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->trade_time_stamp[i]; }
  for (size_t i = 0; i < 9; i++) { wire[at++] = record->original_trade_id[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->last_sale[i]; }
  for (size_t i = 0; i < 23; i++) { wire[at++] = record->trading_system_time_stamp[i]; }

  return at;
}

/* Trade Cancellation Message off the wire: 87 bytes from at, returning where the next byte lies */
static size_t decode_trade_cancellation_message(TradeCancellationMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 12; i++) { record->symbol[i] = wire[at++]; }
  for (size_t i = 0; i < 9; i++) { record->volume[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->trade_price[i] = wire[at++]; }
  for (size_t i = 0; i < 3; i++) { record->buyer_id[i] = wire[at++]; }
  for (size_t i = 0; i < 3; i++) { record->seller_id[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->trade_time_stamp[i] = wire[at++]; }
  for (size_t i = 0; i < 9; i++) { record->original_trade_id[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->last_sale[i] = wire[at++]; }
  for (size_t i = 0; i < 23; i++) { record->trading_system_time_stamp[i] = wire[at++]; }

  return at;
}

/* what was read of Trade Cancellation Message is what was written, byte for byte */
static void equal_trade_cancellation_message(const TradeCancellationMessage *read, const TradeCancellationMessage *written) {
  for (size_t i = 0; i < 12; i++) { assert(read->symbol[i] == written->symbol[i]); }
  for (size_t i = 0; i < 9; i++) { assert(read->volume[i] == written->volume[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->trade_price[i] == written->trade_price[i]); }
  for (size_t i = 0; i < 3; i++) { assert(read->buyer_id[i] == written->buyer_id[i]); }
  for (size_t i = 0; i < 3; i++) { assert(read->seller_id[i] == written->seller_id[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->trade_time_stamp[i] == written->trade_time_stamp[i]); }
  for (size_t i = 0; i < 9; i++) { assert(read->original_trade_id[i] == written->original_trade_id[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->last_sale[i] == written->last_sale[i]); }
  for (size_t i = 0; i < 23; i++) { assert(read->trading_system_time_stamp[i] == written->trading_system_time_stamp[i]); }
}

/* Trade Cancellation Message: written and read back, then read and written back */
static void check_trade_cancellation_message(void) {
  TradeCancellationMessage sent;
  TradeCancellationMessage got;
  uint8_t wire[87];
  uint8_t again[87];

  any_trade_cancellation_message(&sent);
  assert(encode_trade_cancellation_message(&sent, wire, 0) == 87);
  assert(decode_trade_cancellation_message(&got, wire, 0) == 87);
  equal_trade_cancellation_message(&got, &sent);

  for (size_t i = 0; i < 87; i++) { wire[i] = arbitrary(); }
  assert(decode_trade_cancellation_message(&got, wire, 0) == 87);
  assert(encode_trade_cancellation_message(&got, again, 0) == 87);
  for (size_t i = 0; i < 87; i++) { assert(again[i] == wire[i]); }
}

/* ---- Market State Message: 26 bytes ------------------------------------------ */

/* The indication of the current market state for a stock group. */
typedef struct {
  uint8_t trading_system_time_stamp[23];  /* bytes 0 to 22 */
  uint8_t stock_group[2];                 /* bytes 23 to 24 */
  uint8_t market_state;                   /* byte 25 */
} MarketStateMessage;

/* any Market State Message at all: every byte one the checker chooses */
static void any_market_state_message(MarketStateMessage *record) {
  for (size_t i = 0; i < 23; i++) { record->trading_system_time_stamp[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->stock_group[i] = arbitrary(); }
  record->market_state = arbitrary();
}

/* Market State Message to the wire: 26 bytes from at, returning where the next byte goes */
static size_t encode_market_state_message(const MarketStateMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 23; i++) { wire[at++] = record->trading_system_time_stamp[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->stock_group[i]; }
  wire[at++] = record->market_state;

  return at;
}

/* Market State Message off the wire: 26 bytes from at, returning where the next byte lies */
static size_t decode_market_state_message(MarketStateMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 23; i++) { record->trading_system_time_stamp[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->stock_group[i] = wire[at++]; }
  record->market_state = wire[at++];

  return at;
}

/* what was read of Market State Message is what was written, byte for byte */
static void equal_market_state_message(const MarketStateMessage *read, const MarketStateMessage *written) {
  for (size_t i = 0; i < 23; i++) { assert(read->trading_system_time_stamp[i] == written->trading_system_time_stamp[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->stock_group[i] == written->stock_group[i]); }
  assert(read->market_state == written->market_state);
}

/* Market State Message: written and read back, then read and written back */
static void check_market_state_message(void) {
  MarketStateMessage sent;
  MarketStateMessage got;
  uint8_t wire[26];
  uint8_t again[26];

  any_market_state_message(&sent);
  assert(encode_market_state_message(&sent, wire, 0) == 26);
  assert(decode_market_state_message(&got, wire, 0) == 26);
  equal_market_state_message(&got, &sent);

  for (size_t i = 0; i < 26; i++) { wire[i] = arbitrary(); }
  assert(decode_market_state_message(&got, wire, 0) == 26);
  assert(encode_market_state_message(&got, again, 0) == 26);
  for (size_t i = 0; i < 26; i++) { assert(again[i] == wire[i]); }
}

/* ---- Trading Tier Status Message: 40 bytes ----------------------------------- */

/* Statistical information on the number of symbols and stock groups for the current trading day, sent at the beginning of each trading day. */
typedef struct {
  uint8_t exchange_id[3];                   /* bytes 0 to 2 */
  uint8_t total_number_of_symbols[5];       /* bytes 3 to 7 */
  uint8_t total_number_of_stock_groups[3];  /* bytes 8 to 10 */
  uint8_t trading_system_time_stamp[23];    /* bytes 11 to 33 */
  uint8_t trading_tier_id[6];               /* bytes 34 to 39 */
} TradingTierStatusMessage;

/* any Trading Tier Status Message at all: every byte one the checker chooses */
static void any_trading_tier_status_message(TradingTierStatusMessage *record) {
  for (size_t i = 0; i < 3; i++) { record->exchange_id[i] = arbitrary(); }
  for (size_t i = 0; i < 5; i++) { record->total_number_of_symbols[i] = arbitrary(); }
  for (size_t i = 0; i < 3; i++) { record->total_number_of_stock_groups[i] = arbitrary(); }
  for (size_t i = 0; i < 23; i++) { record->trading_system_time_stamp[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->trading_tier_id[i] = arbitrary(); }
}

/* Trading Tier Status Message to the wire: 40 bytes from at, returning where the next byte goes */
static size_t encode_trading_tier_status_message(const TradingTierStatusMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->exchange_id[i]; }
  for (size_t i = 0; i < 5; i++) { wire[at++] = record->total_number_of_symbols[i]; }
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->total_number_of_stock_groups[i]; }
  for (size_t i = 0; i < 23; i++) { wire[at++] = record->trading_system_time_stamp[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->trading_tier_id[i]; }

  return at;
}

/* Trading Tier Status Message off the wire: 40 bytes from at, returning where the next byte lies */
static size_t decode_trading_tier_status_message(TradingTierStatusMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 3; i++) { record->exchange_id[i] = wire[at++]; }
  for (size_t i = 0; i < 5; i++) { record->total_number_of_symbols[i] = wire[at++]; }
  for (size_t i = 0; i < 3; i++) { record->total_number_of_stock_groups[i] = wire[at++]; }
  for (size_t i = 0; i < 23; i++) { record->trading_system_time_stamp[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->trading_tier_id[i] = wire[at++]; }

  return at;
}

/* what was read of Trading Tier Status Message is what was written, byte for byte */
static void equal_trading_tier_status_message(const TradingTierStatusMessage *read, const TradingTierStatusMessage *written) {
  for (size_t i = 0; i < 3; i++) { assert(read->exchange_id[i] == written->exchange_id[i]); }
  for (size_t i = 0; i < 5; i++) { assert(read->total_number_of_symbols[i] == written->total_number_of_symbols[i]); }
  for (size_t i = 0; i < 3; i++) { assert(read->total_number_of_stock_groups[i] == written->total_number_of_stock_groups[i]); }
  for (size_t i = 0; i < 23; i++) { assert(read->trading_system_time_stamp[i] == written->trading_system_time_stamp[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->trading_tier_id[i] == written->trading_tier_id[i]); }
}

/* Trading Tier Status Message: written and read back, then read and written back */
static void check_trading_tier_status_message(void) {
  TradingTierStatusMessage sent;
  TradingTierStatusMessage got;
  uint8_t wire[40];
  uint8_t again[40];

  any_trading_tier_status_message(&sent);
  assert(encode_trading_tier_status_message(&sent, wire, 0) == 40);
  assert(decode_trading_tier_status_message(&got, wire, 0) == 40);
  equal_trading_tier_status_message(&got, &sent);

  for (size_t i = 0; i < 40; i++) { wire[i] = arbitrary(); }
  assert(decode_trading_tier_status_message(&got, wire, 0) == 40);
  assert(encode_trading_tier_status_message(&got, again, 0) == 40);
  for (size_t i = 0; i < 40; i++) { assert(again[i] == wire[i]); }
}

/* ---- Trade Correction Message: 101 bytes ------------------------------------- */

/* Correction of a trade already disseminated. */
typedef struct {
  uint8_t symbol[12];                     /* bytes 0 to 11 */
  uint8_t volume[9];                      /* bytes 12 to 20 */
  uint8_t trade_price[11];                /* bytes 21 to 31 */
  uint8_t buyer_id[3];                    /* bytes 32 to 34 */
  uint8_t seller_id[3];                   /* bytes 35 to 37 */
  uint8_t trade_time_stamp[6];            /* bytes 38 to 43 */
  uint8_t last_sale[11];                  /* bytes 44 to 54 */
  uint8_t trade_id[9];                    /* bytes 55 to 63 */
  uint8_t cross_type;                     /* byte 64 */
  uint8_t bypass;                         /* byte 65 */
  uint8_t opening_trade;                  /* byte 66 */
  uint8_t settlement_terms;               /* byte 67 */
  uint8_t original_trade_id[9];           /* bytes 68 to 76 */
  uint8_t is_dark;                        /* byte 77 */
  uint8_t trading_system_time_stamp[23];  /* bytes 78 to 100 */
} TradeCorrectionMessage;

/* any Trade Correction Message at all: every byte one the checker chooses */
static void any_trade_correction_message(TradeCorrectionMessage *record) {
  for (size_t i = 0; i < 12; i++) { record->symbol[i] = arbitrary(); }
  for (size_t i = 0; i < 9; i++) { record->volume[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->trade_price[i] = arbitrary(); }
  for (size_t i = 0; i < 3; i++) { record->buyer_id[i] = arbitrary(); }
  for (size_t i = 0; i < 3; i++) { record->seller_id[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->trade_time_stamp[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->last_sale[i] = arbitrary(); }
  for (size_t i = 0; i < 9; i++) { record->trade_id[i] = arbitrary(); }
  record->cross_type = arbitrary();
  record->bypass = arbitrary();
  record->opening_trade = arbitrary();
  record->settlement_terms = arbitrary();
  for (size_t i = 0; i < 9; i++) { record->original_trade_id[i] = arbitrary(); }
  record->is_dark = arbitrary();
  for (size_t i = 0; i < 23; i++) { record->trading_system_time_stamp[i] = arbitrary(); }
}

/* Trade Correction Message to the wire: 101 bytes from at, returning where the next byte goes */
static size_t encode_trade_correction_message(const TradeCorrectionMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->symbol[i]; }
  for (size_t i = 0; i < 9; i++) { wire[at++] = record->volume[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->trade_price[i]; }
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->buyer_id[i]; }
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->seller_id[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->trade_time_stamp[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->last_sale[i]; }
  for (size_t i = 0; i < 9; i++) { wire[at++] = record->trade_id[i]; }
  wire[at++] = record->cross_type;
  wire[at++] = record->bypass;
  wire[at++] = record->opening_trade;
  wire[at++] = record->settlement_terms;
  for (size_t i = 0; i < 9; i++) { wire[at++] = record->original_trade_id[i]; }
  wire[at++] = record->is_dark;
  for (size_t i = 0; i < 23; i++) { wire[at++] = record->trading_system_time_stamp[i]; }

  return at;
}

/* Trade Correction Message off the wire: 101 bytes from at, returning where the next byte lies */
static size_t decode_trade_correction_message(TradeCorrectionMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 12; i++) { record->symbol[i] = wire[at++]; }
  for (size_t i = 0; i < 9; i++) { record->volume[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->trade_price[i] = wire[at++]; }
  for (size_t i = 0; i < 3; i++) { record->buyer_id[i] = wire[at++]; }
  for (size_t i = 0; i < 3; i++) { record->seller_id[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->trade_time_stamp[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->last_sale[i] = wire[at++]; }
  for (size_t i = 0; i < 9; i++) { record->trade_id[i] = wire[at++]; }
  record->cross_type = wire[at++];
  record->bypass = wire[at++];
  record->opening_trade = wire[at++];
  record->settlement_terms = wire[at++];
  for (size_t i = 0; i < 9; i++) { record->original_trade_id[i] = wire[at++]; }
  record->is_dark = wire[at++];
  for (size_t i = 0; i < 23; i++) { record->trading_system_time_stamp[i] = wire[at++]; }

  return at;
}

/* what was read of Trade Correction Message is what was written, byte for byte */
static void equal_trade_correction_message(const TradeCorrectionMessage *read, const TradeCorrectionMessage *written) {
  for (size_t i = 0; i < 12; i++) { assert(read->symbol[i] == written->symbol[i]); }
  for (size_t i = 0; i < 9; i++) { assert(read->volume[i] == written->volume[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->trade_price[i] == written->trade_price[i]); }
  for (size_t i = 0; i < 3; i++) { assert(read->buyer_id[i] == written->buyer_id[i]); }
  for (size_t i = 0; i < 3; i++) { assert(read->seller_id[i] == written->seller_id[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->trade_time_stamp[i] == written->trade_time_stamp[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->last_sale[i] == written->last_sale[i]); }
  for (size_t i = 0; i < 9; i++) { assert(read->trade_id[i] == written->trade_id[i]); }
  assert(read->cross_type == written->cross_type);
  assert(read->bypass == written->bypass);
  assert(read->opening_trade == written->opening_trade);
  assert(read->settlement_terms == written->settlement_terms);
  for (size_t i = 0; i < 9; i++) { assert(read->original_trade_id[i] == written->original_trade_id[i]); }
  assert(read->is_dark == written->is_dark);
  for (size_t i = 0; i < 23; i++) { assert(read->trading_system_time_stamp[i] == written->trading_system_time_stamp[i]); }
}

/* Trade Correction Message: written and read back, then read and written back */
static void check_trade_correction_message(void) {
  TradeCorrectionMessage sent;
  TradeCorrectionMessage got;
  uint8_t wire[101];
  uint8_t again[101];

  any_trade_correction_message(&sent);
  assert(encode_trade_correction_message(&sent, wire, 0) == 101);
  assert(decode_trade_correction_message(&got, wire, 0) == 101);
  equal_trade_correction_message(&got, &sent);

  for (size_t i = 0; i < 101; i++) { wire[i] = arbitrary(); }
  assert(decode_trade_correction_message(&got, wire, 0) == 101);
  assert(encode_trade_correction_message(&got, again, 0) == 101);
  for (size_t i = 0; i < 101; i++) { assert(again[i] == wire[i]); }
}

/* ---- What esbmc checks ------------------------------------------------------- */

/* every record of the protocol, each on its own buffers */
static void checks(void) {
  check_message_header();
  check_trade_message();
  check_symbol_status_message();
  check_stock_state_message();
  check_quote_message();
  check_general_message();
  check_trade_cancellation_message();
  check_market_state_message();
  check_trading_tier_status_message();
  check_trade_correction_message();
}

int main(void) {
#ifdef CONCRETE
  for (pattern = 0; pattern < 4; pattern++) { checks(); }
#else
  checks();
#endif

  return 0;
}
