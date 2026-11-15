// coinbase/coinbasederivatives/marketdataapi/CoinbaseDerivatives_MarketDataApi_v1_7.c
/*
 * Coinbase Market Data Api
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
 *   - a field read in bits
 *   - a run counted by a field
 *   - a block whose stated length holds more than its fields
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

/* ---- Message Header: 10 bytes ------------------------------------------------ */

/* Coinbase Sbe Market Data message header — frame length plus standard SBE header */
typedef struct {
  uint8_t frame_length[2];  /* bytes 0 to 1 */
  uint8_t block_length[2];  /* bytes 2 to 3 */
  uint8_t template_id[2];   /* bytes 4 to 5 */
  uint8_t schema_id[2];     /* bytes 6 to 7 */
  uint8_t version[2];       /* bytes 8 to 9 */
} MessageHeader;

/* any Message Header at all: every byte one the checker chooses */
static void any_message_header(MessageHeader *record) {
  for (size_t i = 0; i < 2; i++) { record->frame_length[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->block_length[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->template_id[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->schema_id[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->version[i] = arbitrary(); }
}

/* Message Header to the wire: 10 bytes from at, returning where the next byte goes */
static size_t encode_message_header(const MessageHeader *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->frame_length[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->block_length[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->template_id[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->schema_id[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->version[i]; }

  return at;
}

/* Message Header off the wire: 10 bytes from at, returning where the next byte lies */
static size_t decode_message_header(MessageHeader *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->frame_length[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->block_length[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->template_id[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->schema_id[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->version[i] = wire[at++]; }

  return at;
}

/* what was read of Message Header is what was written, byte for byte */
static void equal_message_header(const MessageHeader *read, const MessageHeader *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->frame_length[i] == written->frame_length[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->block_length[i] == written->block_length[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->template_id[i] == written->template_id[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->schema_id[i] == written->schema_id[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->version[i] == written->version[i]); }
}

/* Message Header: written and read back, then read and written back */
static void check_message_header(void) {
  MessageHeader sent;
  MessageHeader got;
  uint8_t wire[10];
  uint8_t again[10];

  any_message_header(&sent);
  assert(encode_message_header(&sent, wire, 0) == 10);
  assert(decode_message_header(&got, wire, 0) == 10);
  equal_message_header(&got, &sent);

  for (size_t i = 0; i < 10; i++) { wire[i] = arbitrary(); }
  assert(decode_message_header(&got, wire, 0) == 10);
  assert(encode_message_header(&got, again, 0) == 10);
  for (size_t i = 0; i < 10; i++) { assert(again[i] == wire[i]); }
}

/* ---- Instr Header: 22 bytes -------------------------------------------------- */

/* Instrument Header */
typedef struct {
  uint8_t instrument_flags;         /* byte 0 */
  uint8_t instrument_side;          /* byte 1 */
  uint8_t instrument_id[4];         /* bytes 2 to 5 */
  uint8_t instr_seq_num[4];         /* bytes 6 to 9 */
  uint8_t trading_session_date[2];  /* bytes 10 to 11 */
  uint8_t reserved[2];              /* bytes 12 to 13 */
  uint8_t transact_time[8];         /* bytes 14 to 21 */
} InstrHeader;

/* any Instr Header at all: every byte one the checker chooses */
static void any_instr_header(InstrHeader *record) {
  record->instrument_flags = arbitrary();
  record->instrument_side = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->instrument_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->instr_seq_num[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->trading_session_date[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->reserved[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->transact_time[i] = arbitrary(); }
}

/* Instr Header to the wire: 22 bytes from at, returning where the next byte goes */
static size_t encode_instr_header(const InstrHeader *record, uint8_t *wire, size_t at) {
  wire[at++] = record->instrument_flags;
  wire[at++] = record->instrument_side;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instr_seq_num[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->trading_session_date[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->reserved[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->transact_time[i]; }

  return at;
}

/* Instr Header off the wire: 22 bytes from at, returning where the next byte lies */
static size_t decode_instr_header(InstrHeader *record, const uint8_t *wire, size_t at) {
  record->instrument_flags = wire[at++];
  record->instrument_side = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->instrument_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->instr_seq_num[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->trading_session_date[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->reserved[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->transact_time[i] = wire[at++]; }

  return at;
}

/* what was read of Instr Header is what was written, byte for byte */
static void equal_instr_header(const InstrHeader *read, const InstrHeader *written) {
  assert(read->instrument_flags == written->instrument_flags);
  assert(read->instrument_side == written->instrument_side);
  for (size_t i = 0; i < 4; i++) { assert(read->instrument_id[i] == written->instrument_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->instr_seq_num[i] == written->instr_seq_num[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->trading_session_date[i] == written->trading_session_date[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->reserved[i] == written->reserved[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->transact_time[i] == written->transact_time[i]); }
}

/* Instr Header: written and read back, then read and written back */
static void check_instr_header(void) {
  InstrHeader sent;
  InstrHeader got;
  uint8_t wire[22];
  uint8_t again[22];

  any_instr_header(&sent);
  assert(encode_instr_header(&sent, wire, 0) == 22);
  assert(decode_instr_header(&got, wire, 0) == 22);
  equal_instr_header(&got, &sent);

  for (size_t i = 0; i < 22; i++) { wire[i] = arbitrary(); }
  assert(decode_instr_header(&got, wire, 0) == 22);
  assert(encode_instr_header(&got, again, 0) == 22);
  for (size_t i = 0; i < 22; i++) { assert(again[i] == wire[i]); }
}

/* ---- Logical Expiry: 8 bytes ------------------------------------------------- */

/* OutrightInstrumentDefinitionMessage */
typedef struct {
  uint8_t year[2];           /* bytes 0 to 1 */
  uint8_t month[2];          /* bytes 2 to 3 */
  uint8_t week_of_month[2];  /* bytes 4 to 5 */
  uint8_t day_of_month[2];   /* bytes 6 to 7 */
} LogicalExpiry;

/* any Logical Expiry at all: every byte one the checker chooses */
static void any_logical_expiry(LogicalExpiry *record) {
  for (size_t i = 0; i < 2; i++) { record->year[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->month[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->week_of_month[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->day_of_month[i] = arbitrary(); }
}

/* Logical Expiry to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_logical_expiry(const LogicalExpiry *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->year[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->month[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->week_of_month[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->day_of_month[i]; }

  return at;
}

/* Logical Expiry off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_logical_expiry(LogicalExpiry *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->year[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->month[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->week_of_month[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->day_of_month[i] = wire[at++]; }

  return at;
}

/* what was read of Logical Expiry is what was written, byte for byte */
static void equal_logical_expiry(const LogicalExpiry *read, const LogicalExpiry *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->year[i] == written->year[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->month[i] == written->month[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->week_of_month[i] == written->week_of_month[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->day_of_month[i] == written->day_of_month[i]); }
}

/* Logical Expiry: written and read back, then read and written back */
static void check_logical_expiry(void) {
  LogicalExpiry sent;
  LogicalExpiry got;
  uint8_t wire[8];
  uint8_t again[8];

  any_logical_expiry(&sent);
  assert(encode_logical_expiry(&sent, wire, 0) == 8);
  assert(decode_logical_expiry(&got, wire, 0) == 8);
  equal_logical_expiry(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_logical_expiry(&got, wire, 0) == 8);
  assert(encode_logical_expiry(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Trading Status Update Message: 39 bytes --------------------------------- */

/* TradingStatusUpdateMessage */
typedef struct {
  InstrHeader instr_header;     /* bytes 0 to 21 */
  uint8_t limit_down_price[8];  /* bytes 22 to 29 */
  uint8_t limit_up_price[8];    /* bytes 30 to 37 */
  uint8_t trading_status;       /* byte 38 */
} TradingStatusUpdateMessage;

/* any Trading Status Update Message at all: every byte one the checker chooses */
static void any_trading_status_update_message(TradingStatusUpdateMessage *record) {
  any_instr_header(&record->instr_header);
  for (size_t i = 0; i < 8; i++) { record->limit_down_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->limit_up_price[i] = arbitrary(); }
  record->trading_status = arbitrary();
}

/* Trading Status Update Message to the wire: 39 bytes from at, returning where the next byte goes */
static size_t encode_trading_status_update_message(const TradingStatusUpdateMessage *record, uint8_t *wire, size_t at) {
  at = encode_instr_header(&record->instr_header, wire, at);
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->limit_down_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->limit_up_price[i]; }
  wire[at++] = record->trading_status;

  return at;
}

/* Trading Status Update Message off the wire: 39 bytes from at, returning where the next byte lies */
static size_t decode_trading_status_update_message(TradingStatusUpdateMessage *record, const uint8_t *wire, size_t at) {
  at = decode_instr_header(&record->instr_header, wire, at);
  for (size_t i = 0; i < 8; i++) { record->limit_down_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->limit_up_price[i] = wire[at++]; }
  record->trading_status = wire[at++];

  return at;
}

/* what was read of Trading Status Update Message is what was written, byte for byte */
static void equal_trading_status_update_message(const TradingStatusUpdateMessage *read, const TradingStatusUpdateMessage *written) {
  equal_instr_header(&read->instr_header, &written->instr_header);
  for (size_t i = 0; i < 8; i++) { assert(read->limit_down_price[i] == written->limit_down_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->limit_up_price[i] == written->limit_up_price[i]); }
  assert(read->trading_status == written->trading_status);
}

/* Trading Status Update Message: written and read back, then read and written back */
static void check_trading_status_update_message(void) {
  TradingStatusUpdateMessage sent;
  TradingStatusUpdateMessage got;
  uint8_t wire[39];
  uint8_t again[39];

  any_trading_status_update_message(&sent);
  assert(encode_trading_status_update_message(&sent, wire, 0) == 39);
  assert(decode_trading_status_update_message(&got, wire, 0) == 39);
  equal_trading_status_update_message(&got, &sent);

  for (size_t i = 0; i < 39; i++) { wire[i] = arbitrary(); }
  assert(decode_trading_status_update_message(&got, wire, 0) == 39);
  assert(encode_trading_status_update_message(&got, again, 0) == 39);
  for (size_t i = 0; i < 39; i++) { assert(again[i] == wire[i]); }
}

/* ---- Order Put Message: 42 bytes --------------------------------------------- */

/* OrderPutMessage */
typedef struct {
  InstrHeader instr_header;  /* bytes 0 to 21 */
  uint8_t order_id[8];       /* bytes 22 to 29 */
  uint8_t price[8];          /* bytes 30 to 37 */
  uint8_t quantity[4];       /* bytes 38 to 41 */
} OrderPutMessage;

/* any Order Put Message at all: every byte one the checker chooses */
static void any_order_put_message(OrderPutMessage *record) {
  any_instr_header(&record->instr_header);
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->quantity[i] = arbitrary(); }
}

/* Order Put Message to the wire: 42 bytes from at, returning where the next byte goes */
static size_t encode_order_put_message(const OrderPutMessage *record, uint8_t *wire, size_t at) {
  at = encode_instr_header(&record->instr_header, wire, at);
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->quantity[i]; }

  return at;
}

/* Order Put Message off the wire: 42 bytes from at, returning where the next byte lies */
static size_t decode_order_put_message(OrderPutMessage *record, const uint8_t *wire, size_t at) {
  at = decode_instr_header(&record->instr_header, wire, at);
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->quantity[i] = wire[at++]; }

  return at;
}

/* what was read of Order Put Message is what was written, byte for byte */
static void equal_order_put_message(const OrderPutMessage *read, const OrderPutMessage *written) {
  equal_instr_header(&read->instr_header, &written->instr_header);
  for (size_t i = 0; i < 8; i++) { assert(read->order_id[i] == written->order_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->price[i] == written->price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->quantity[i] == written->quantity[i]); }
}

/* Order Put Message: written and read back, then read and written back */
static void check_order_put_message(void) {
  OrderPutMessage sent;
  OrderPutMessage got;
  uint8_t wire[42];
  uint8_t again[42];

  any_order_put_message(&sent);
  assert(encode_order_put_message(&sent, wire, 0) == 42);
  assert(decode_order_put_message(&got, wire, 0) == 42);
  equal_order_put_message(&got, &sent);

  for (size_t i = 0; i < 42; i++) { wire[i] = arbitrary(); }
  assert(decode_order_put_message(&got, wire, 0) == 42);
  assert(encode_order_put_message(&got, again, 0) == 42);
  for (size_t i = 0; i < 42; i++) { assert(again[i] == wire[i]); }
}

/* ---- Order Delete Message: 30 bytes ------------------------------------------ */

/* OrderDeleteMessage */
typedef struct {
  InstrHeader instr_header;  /* bytes 0 to 21 */
  uint8_t order_id[8];       /* bytes 22 to 29 */
} OrderDeleteMessage;

/* any Order Delete Message at all: every byte one the checker chooses */
static void any_order_delete_message(OrderDeleteMessage *record) {
  any_instr_header(&record->instr_header);
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = arbitrary(); }
}

/* Order Delete Message to the wire: 30 bytes from at, returning where the next byte goes */
static size_t encode_order_delete_message(const OrderDeleteMessage *record, uint8_t *wire, size_t at) {
  at = encode_instr_header(&record->instr_header, wire, at);
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_id[i]; }

  return at;
}

/* Order Delete Message off the wire: 30 bytes from at, returning where the next byte lies */
static size_t decode_order_delete_message(OrderDeleteMessage *record, const uint8_t *wire, size_t at) {
  at = decode_instr_header(&record->instr_header, wire, at);
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = wire[at++]; }

  return at;
}

/* what was read of Order Delete Message is what was written, byte for byte */
static void equal_order_delete_message(const OrderDeleteMessage *read, const OrderDeleteMessage *written) {
  equal_instr_header(&read->instr_header, &written->instr_header);
  for (size_t i = 0; i < 8; i++) { assert(read->order_id[i] == written->order_id[i]); }
}

/* Order Delete Message: written and read back, then read and written back */
static void check_order_delete_message(void) {
  OrderDeleteMessage sent;
  OrderDeleteMessage got;
  uint8_t wire[30];
  uint8_t again[30];

  any_order_delete_message(&sent);
  assert(encode_order_delete_message(&sent, wire, 0) == 30);
  assert(decode_order_delete_message(&got, wire, 0) == 30);
  equal_order_delete_message(&got, &sent);

  for (size_t i = 0; i < 30; i++) { wire[i] = arbitrary(); }
  assert(decode_order_delete_message(&got, wire, 0) == 30);
  assert(encode_order_delete_message(&got, again, 0) == 30);
  for (size_t i = 0; i < 30; i++) { assert(again[i] == wire[i]); }
}

/* ---- Implied Order Update Message: 46 bytes ---------------------------------- */

/* ImpliedOrderUpdateMessage */
typedef struct {
  InstrHeader instr_header;  /* bytes 0 to 21 */
  uint8_t best_price[8];     /* bytes 22 to 29 */
  uint8_t next_price[8];     /* bytes 30 to 37 */
  uint8_t best_qty[4];       /* bytes 38 to 41 */
  uint8_t next_qty[4];       /* bytes 42 to 45 */
} ImpliedOrderUpdateMessage;

/* any Implied Order Update Message at all: every byte one the checker chooses */
static void any_implied_order_update_message(ImpliedOrderUpdateMessage *record) {
  any_instr_header(&record->instr_header);
  for (size_t i = 0; i < 8; i++) { record->best_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->next_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->best_qty[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->next_qty[i] = arbitrary(); }
}

/* Implied Order Update Message to the wire: 46 bytes from at, returning where the next byte goes */
static size_t encode_implied_order_update_message(const ImpliedOrderUpdateMessage *record, uint8_t *wire, size_t at) {
  at = encode_instr_header(&record->instr_header, wire, at);
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->best_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->next_price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->best_qty[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->next_qty[i]; }

  return at;
}

/* Implied Order Update Message off the wire: 46 bytes from at, returning where the next byte lies */
static size_t decode_implied_order_update_message(ImpliedOrderUpdateMessage *record, const uint8_t *wire, size_t at) {
  at = decode_instr_header(&record->instr_header, wire, at);
  for (size_t i = 0; i < 8; i++) { record->best_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->next_price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->best_qty[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->next_qty[i] = wire[at++]; }

  return at;
}

/* what was read of Implied Order Update Message is what was written, byte for byte */
static void equal_implied_order_update_message(const ImpliedOrderUpdateMessage *read, const ImpliedOrderUpdateMessage *written) {
  equal_instr_header(&read->instr_header, &written->instr_header);
  for (size_t i = 0; i < 8; i++) { assert(read->best_price[i] == written->best_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->next_price[i] == written->next_price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->best_qty[i] == written->best_qty[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->next_qty[i] == written->next_qty[i]); }
}

/* Implied Order Update Message: written and read back, then read and written back */
static void check_implied_order_update_message(void) {
  ImpliedOrderUpdateMessage sent;
  ImpliedOrderUpdateMessage got;
  uint8_t wire[46];
  uint8_t again[46];

  any_implied_order_update_message(&sent);
  assert(encode_implied_order_update_message(&sent, wire, 0) == 46);
  assert(decode_implied_order_update_message(&got, wire, 0) == 46);
  equal_implied_order_update_message(&got, &sent);

  for (size_t i = 0; i < 46; i++) { wire[i] = arbitrary(); }
  assert(decode_implied_order_update_message(&got, wire, 0) == 46);
  assert(encode_implied_order_update_message(&got, again, 0) == 46);
  for (size_t i = 0; i < 46; i++) { assert(again[i] == wire[i]); }
}

/* ---- Trade Summary Message: 58 bytes ----------------------------------------- */

/* TradeSummaryMessage */
typedef struct {
  InstrHeader instr_header;           /* bytes 0 to 21 */
  uint8_t aggressor_order_id[8];      /* bytes 22 to 29 */
  uint8_t aggressor_receive_time[8];  /* bytes 30 to 37 */
  uint8_t vwap_price[8];              /* bytes 38 to 45 */
  uint8_t deepest_price[8];           /* bytes 46 to 53 */
  uint8_t quantity[4];                /* bytes 54 to 57 */
} TradeSummaryMessage;

/* any Trade Summary Message at all: every byte one the checker chooses */
static void any_trade_summary_message(TradeSummaryMessage *record) {
  any_instr_header(&record->instr_header);
  for (size_t i = 0; i < 8; i++) { record->aggressor_order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->aggressor_receive_time[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->vwap_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->deepest_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->quantity[i] = arbitrary(); }
}

/* Trade Summary Message to the wire: 58 bytes from at, returning where the next byte goes */
static size_t encode_trade_summary_message(const TradeSummaryMessage *record, uint8_t *wire, size_t at) {
  at = encode_instr_header(&record->instr_header, wire, at);
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->aggressor_order_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->aggressor_receive_time[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->vwap_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->deepest_price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->quantity[i]; }

  return at;
}

/* Trade Summary Message off the wire: 58 bytes from at, returning where the next byte lies */
static size_t decode_trade_summary_message(TradeSummaryMessage *record, const uint8_t *wire, size_t at) {
  at = decode_instr_header(&record->instr_header, wire, at);
  for (size_t i = 0; i < 8; i++) { record->aggressor_order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->aggressor_receive_time[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->vwap_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->deepest_price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->quantity[i] = wire[at++]; }

  return at;
}

/* what was read of Trade Summary Message is what was written, byte for byte */
static void equal_trade_summary_message(const TradeSummaryMessage *read, const TradeSummaryMessage *written) {
  equal_instr_header(&read->instr_header, &written->instr_header);
  for (size_t i = 0; i < 8; i++) { assert(read->aggressor_order_id[i] == written->aggressor_order_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->aggressor_receive_time[i] == written->aggressor_receive_time[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->vwap_price[i] == written->vwap_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->deepest_price[i] == written->deepest_price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->quantity[i] == written->quantity[i]); }
}

/* Trade Summary Message: written and read back, then read and written back */
static void check_trade_summary_message(void) {
  TradeSummaryMessage sent;
  TradeSummaryMessage got;
  uint8_t wire[58];
  uint8_t again[58];

  any_trade_summary_message(&sent);
  assert(encode_trade_summary_message(&sent, wire, 0) == 58);
  assert(decode_trade_summary_message(&got, wire, 0) == 58);
  equal_trade_summary_message(&got, &sent);

  for (size_t i = 0; i < 58; i++) { wire[i] = arbitrary(); }
  assert(decode_trade_summary_message(&got, wire, 0) == 58);
  assert(encode_trade_summary_message(&got, again, 0) == 58);
  for (size_t i = 0; i < 58; i++) { assert(again[i] == wire[i]); }
}

/* ---- Trade Message: 58 bytes ------------------------------------------------- */

/* TradeMessage */
typedef struct {
  InstrHeader instr_header;  /* bytes 0 to 21 */
  uint8_t match_id[8];       /* bytes 22 to 29 */
  uint8_t buy_order_id[8];   /* bytes 30 to 37 */
  uint8_t sell_order_id[8];  /* bytes 38 to 45 */
  uint8_t price[8];          /* bytes 46 to 53 */
  uint8_t quantity[4];       /* bytes 54 to 57 */
} TradeMessage;

/* any Trade Message at all: every byte one the checker chooses */
static void any_trade_message(TradeMessage *record) {
  any_instr_header(&record->instr_header);
  for (size_t i = 0; i < 8; i++) { record->match_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->buy_order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->sell_order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->quantity[i] = arbitrary(); }
}

/* Trade Message to the wire: 58 bytes from at, returning where the next byte goes */
static size_t encode_trade_message(const TradeMessage *record, uint8_t *wire, size_t at) {
  at = encode_instr_header(&record->instr_header, wire, at);
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->match_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->buy_order_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->sell_order_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->quantity[i]; }

  return at;
}

/* Trade Message off the wire: 58 bytes from at, returning where the next byte lies */
static size_t decode_trade_message(TradeMessage *record, const uint8_t *wire, size_t at) {
  at = decode_instr_header(&record->instr_header, wire, at);
  for (size_t i = 0; i < 8; i++) { record->match_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->buy_order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->sell_order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->quantity[i] = wire[at++]; }

  return at;
}

/* what was read of Trade Message is what was written, byte for byte */
static void equal_trade_message(const TradeMessage *read, const TradeMessage *written) {
  equal_instr_header(&read->instr_header, &written->instr_header);
  for (size_t i = 0; i < 8; i++) { assert(read->match_id[i] == written->match_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->buy_order_id[i] == written->buy_order_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->sell_order_id[i] == written->sell_order_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->price[i] == written->price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->quantity[i] == written->quantity[i]); }
}

/* Trade Message: written and read back, then read and written back */
static void check_trade_message(void) {
  TradeMessage sent;
  TradeMessage got;
  uint8_t wire[58];
  uint8_t again[58];

  any_trade_message(&sent);
  assert(encode_trade_message(&sent, wire, 0) == 58);
  assert(decode_trade_message(&got, wire, 0) == 58);
  equal_trade_message(&got, &sent);

  for (size_t i = 0; i < 58; i++) { wire[i] = arbitrary(); }
  assert(decode_trade_message(&got, wire, 0) == 58);
  assert(encode_trade_message(&got, again, 0) == 58);
  for (size_t i = 0; i < 58; i++) { assert(again[i] == wire[i]); }
}

/* ---- Trade Amend Message: 62 bytes ------------------------------------------- */

/* TradeAmendMessage */
typedef struct {
  InstrHeader instr_header;  /* bytes 0 to 21 */
  uint8_t match_id[8];       /* bytes 22 to 29 */
  uint8_t buy_order_id[8];   /* bytes 30 to 37 */
  uint8_t sell_order_id[8];  /* bytes 38 to 45 */
  uint8_t old_price[8];      /* bytes 46 to 53 */
  uint8_t new_price[8];      /* bytes 54 to 61 */
} TradeAmendMessage;

/* any Trade Amend Message at all: every byte one the checker chooses */
static void any_trade_amend_message(TradeAmendMessage *record) {
  any_instr_header(&record->instr_header);
  for (size_t i = 0; i < 8; i++) { record->match_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->buy_order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->sell_order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->old_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->new_price[i] = arbitrary(); }
}

/* Trade Amend Message to the wire: 62 bytes from at, returning where the next byte goes */
static size_t encode_trade_amend_message(const TradeAmendMessage *record, uint8_t *wire, size_t at) {
  at = encode_instr_header(&record->instr_header, wire, at);
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->match_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->buy_order_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->sell_order_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->old_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->new_price[i]; }

  return at;
}

/* Trade Amend Message off the wire: 62 bytes from at, returning where the next byte lies */
static size_t decode_trade_amend_message(TradeAmendMessage *record, const uint8_t *wire, size_t at) {
  at = decode_instr_header(&record->instr_header, wire, at);
  for (size_t i = 0; i < 8; i++) { record->match_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->buy_order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->sell_order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->old_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->new_price[i] = wire[at++]; }

  return at;
}

/* what was read of Trade Amend Message is what was written, byte for byte */
static void equal_trade_amend_message(const TradeAmendMessage *read, const TradeAmendMessage *written) {
  equal_instr_header(&read->instr_header, &written->instr_header);
  for (size_t i = 0; i < 8; i++) { assert(read->match_id[i] == written->match_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->buy_order_id[i] == written->buy_order_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->sell_order_id[i] == written->sell_order_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->old_price[i] == written->old_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->new_price[i] == written->new_price[i]); }
}

/* Trade Amend Message: written and read back, then read and written back */
static void check_trade_amend_message(void) {
  TradeAmendMessage sent;
  TradeAmendMessage got;
  uint8_t wire[62];
  uint8_t again[62];

  any_trade_amend_message(&sent);
  assert(encode_trade_amend_message(&sent, wire, 0) == 62);
  assert(decode_trade_amend_message(&got, wire, 0) == 62);
  equal_trade_amend_message(&got, &sent);

  for (size_t i = 0; i < 62; i++) { wire[i] = arbitrary(); }
  assert(decode_trade_amend_message(&got, wire, 0) == 62);
  assert(encode_trade_amend_message(&got, again, 0) == 62);
  for (size_t i = 0; i < 62; i++) { assert(again[i] == wire[i]); }
}

/* ---- Spread Trade Amend Message: 94 bytes ------------------------------------ */

/* SpreadTradeAmendMessage */
typedef struct {
  InstrHeader instr_header;    /* bytes 0 to 21 */
  uint8_t match_id[8];         /* bytes 22 to 29 */
  uint8_t buy_order_id[8];     /* bytes 30 to 37 */
  uint8_t sell_order_id[8];    /* bytes 38 to 45 */
  uint8_t old_price[8];        /* bytes 46 to 53 */
  uint8_t new_price[8];        /* bytes 54 to 61 */
  uint8_t old_leg_1_price[8];  /* bytes 62 to 69 */
  uint8_t new_leg_1_price[8];  /* bytes 70 to 77 */
  uint8_t old_leg_2_price[8];  /* bytes 78 to 85 */
  uint8_t new_leg_2_price[8];  /* bytes 86 to 93 */
} SpreadTradeAmendMessage;

/* any Spread Trade Amend Message at all: every byte one the checker chooses */
static void any_spread_trade_amend_message(SpreadTradeAmendMessage *record) {
  any_instr_header(&record->instr_header);
  for (size_t i = 0; i < 8; i++) { record->match_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->buy_order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->sell_order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->old_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->new_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->old_leg_1_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->new_leg_1_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->old_leg_2_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->new_leg_2_price[i] = arbitrary(); }
}

/* Spread Trade Amend Message to the wire: 94 bytes from at, returning where the next byte goes */
static size_t encode_spread_trade_amend_message(const SpreadTradeAmendMessage *record, uint8_t *wire, size_t at) {
  at = encode_instr_header(&record->instr_header, wire, at);
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->match_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->buy_order_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->sell_order_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->old_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->new_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->old_leg_1_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->new_leg_1_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->old_leg_2_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->new_leg_2_price[i]; }

  return at;
}

/* Spread Trade Amend Message off the wire: 94 bytes from at, returning where the next byte lies */
static size_t decode_spread_trade_amend_message(SpreadTradeAmendMessage *record, const uint8_t *wire, size_t at) {
  at = decode_instr_header(&record->instr_header, wire, at);
  for (size_t i = 0; i < 8; i++) { record->match_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->buy_order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->sell_order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->old_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->new_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->old_leg_1_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->new_leg_1_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->old_leg_2_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->new_leg_2_price[i] = wire[at++]; }

  return at;
}

/* what was read of Spread Trade Amend Message is what was written, byte for byte */
static void equal_spread_trade_amend_message(const SpreadTradeAmendMessage *read, const SpreadTradeAmendMessage *written) {
  equal_instr_header(&read->instr_header, &written->instr_header);
  for (size_t i = 0; i < 8; i++) { assert(read->match_id[i] == written->match_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->buy_order_id[i] == written->buy_order_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->sell_order_id[i] == written->sell_order_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->old_price[i] == written->old_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->new_price[i] == written->new_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->old_leg_1_price[i] == written->old_leg_1_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->new_leg_1_price[i] == written->new_leg_1_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->old_leg_2_price[i] == written->old_leg_2_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->new_leg_2_price[i] == written->new_leg_2_price[i]); }
}

/* Spread Trade Amend Message: written and read back, then read and written back */
static void check_spread_trade_amend_message(void) {
  SpreadTradeAmendMessage sent;
  SpreadTradeAmendMessage got;
  uint8_t wire[94];
  uint8_t again[94];

  any_spread_trade_amend_message(&sent);
  assert(encode_spread_trade_amend_message(&sent, wire, 0) == 94);
  assert(decode_spread_trade_amend_message(&got, wire, 0) == 94);
  equal_spread_trade_amend_message(&got, &sent);

  for (size_t i = 0; i < 94; i++) { wire[i] = arbitrary(); }
  assert(decode_spread_trade_amend_message(&got, wire, 0) == 94);
  assert(encode_spread_trade_amend_message(&got, again, 0) == 94);
  for (size_t i = 0; i < 94; i++) { assert(again[i] == wire[i]); }
}

/* ---- Trade Bust Message: 46 bytes -------------------------------------------- */

/* TradeBustMessage */
typedef struct {
  InstrHeader instr_header;  /* bytes 0 to 21 */
  uint8_t match_id[8];       /* bytes 22 to 29 */
  uint8_t buy_order_id[8];   /* bytes 30 to 37 */
  uint8_t sell_order_id[8];  /* bytes 38 to 45 */
} TradeBustMessage;

/* any Trade Bust Message at all: every byte one the checker chooses */
static void any_trade_bust_message(TradeBustMessage *record) {
  any_instr_header(&record->instr_header);
  for (size_t i = 0; i < 8; i++) { record->match_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->buy_order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->sell_order_id[i] = arbitrary(); }
}

/* Trade Bust Message to the wire: 46 bytes from at, returning where the next byte goes */
static size_t encode_trade_bust_message(const TradeBustMessage *record, uint8_t *wire, size_t at) {
  at = encode_instr_header(&record->instr_header, wire, at);
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->match_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->buy_order_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->sell_order_id[i]; }

  return at;
}

/* Trade Bust Message off the wire: 46 bytes from at, returning where the next byte lies */
static size_t decode_trade_bust_message(TradeBustMessage *record, const uint8_t *wire, size_t at) {
  at = decode_instr_header(&record->instr_header, wire, at);
  for (size_t i = 0; i < 8; i++) { record->match_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->buy_order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->sell_order_id[i] = wire[at++]; }

  return at;
}

/* what was read of Trade Bust Message is what was written, byte for byte */
static void equal_trade_bust_message(const TradeBustMessage *read, const TradeBustMessage *written) {
  equal_instr_header(&read->instr_header, &written->instr_header);
  for (size_t i = 0; i < 8; i++) { assert(read->match_id[i] == written->match_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->buy_order_id[i] == written->buy_order_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->sell_order_id[i] == written->sell_order_id[i]); }
}

/* Trade Bust Message: written and read back, then read and written back */
static void check_trade_bust_message(void) {
  TradeBustMessage sent;
  TradeBustMessage got;
  uint8_t wire[46];
  uint8_t again[46];

  any_trade_bust_message(&sent);
  assert(encode_trade_bust_message(&sent, wire, 0) == 46);
  assert(decode_trade_bust_message(&got, wire, 0) == 46);
  equal_trade_bust_message(&got, &sent);

  for (size_t i = 0; i < 46; i++) { wire[i] = arbitrary(); }
  assert(decode_trade_bust_message(&got, wire, 0) == 46);
  assert(encode_trade_bust_message(&got, again, 0) == 46);
  for (size_t i = 0; i < 46; i++) { assert(again[i] == wire[i]); }
}

/* ---- Market Stat Message: 31 bytes ------------------------------------------- */

/* MarketStatMessage */
typedef struct {
  InstrHeader instr_header;  /* bytes 0 to 21 */
  uint8_t price[8];          /* bytes 22 to 29 */
  uint8_t stat_type;         /* byte 30 */
} MarketStatMessage;

/* any Market Stat Message at all: every byte one the checker chooses */
static void any_market_stat_message(MarketStatMessage *record) {
  any_instr_header(&record->instr_header);
  for (size_t i = 0; i < 8; i++) { record->price[i] = arbitrary(); }
  record->stat_type = arbitrary();
}

/* Market Stat Message to the wire: 31 bytes from at, returning where the next byte goes */
static size_t encode_market_stat_message(const MarketStatMessage *record, uint8_t *wire, size_t at) {
  at = encode_instr_header(&record->instr_header, wire, at);
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price[i]; }
  wire[at++] = record->stat_type;

  return at;
}

/* Market Stat Message off the wire: 31 bytes from at, returning where the next byte lies */
static size_t decode_market_stat_message(MarketStatMessage *record, const uint8_t *wire, size_t at) {
  at = decode_instr_header(&record->instr_header, wire, at);
  for (size_t i = 0; i < 8; i++) { record->price[i] = wire[at++]; }
  record->stat_type = wire[at++];

  return at;
}

/* what was read of Market Stat Message is what was written, byte for byte */
static void equal_market_stat_message(const MarketStatMessage *read, const MarketStatMessage *written) {
  equal_instr_header(&read->instr_header, &written->instr_header);
  for (size_t i = 0; i < 8; i++) { assert(read->price[i] == written->price[i]); }
  assert(read->stat_type == written->stat_type);
}

/* Market Stat Message: written and read back, then read and written back */
static void check_market_stat_message(void) {
  MarketStatMessage sent;
  MarketStatMessage got;
  uint8_t wire[31];
  uint8_t again[31];

  any_market_stat_message(&sent);
  assert(encode_market_stat_message(&sent, wire, 0) == 31);
  assert(decode_market_stat_message(&got, wire, 0) == 31);
  equal_market_stat_message(&got, &sent);

  for (size_t i = 0; i < 31; i++) { wire[i] = arbitrary(); }
  assert(decode_market_stat_message(&got, wire, 0) == 31);
  assert(encode_market_stat_message(&got, again, 0) == 31);
  for (size_t i = 0; i < 31; i++) { assert(again[i] == wire[i]); }
}

/* ---- Trade Session Volume Message: 34 bytes ---------------------------------- */

/* TradeSessionVolumeMessage */
typedef struct {
  InstrHeader instr_header;  /* bytes 0 to 21 */
  uint8_t vwap_price[8];     /* bytes 22 to 29 */
  uint8_t trade_volume[4];   /* bytes 30 to 33 */
} TradeSessionVolumeMessage;

/* any Trade Session Volume Message at all: every byte one the checker chooses */
static void any_trade_session_volume_message(TradeSessionVolumeMessage *record) {
  any_instr_header(&record->instr_header);
  for (size_t i = 0; i < 8; i++) { record->vwap_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->trade_volume[i] = arbitrary(); }
}

/* Trade Session Volume Message to the wire: 34 bytes from at, returning where the next byte goes */
static size_t encode_trade_session_volume_message(const TradeSessionVolumeMessage *record, uint8_t *wire, size_t at) {
  at = encode_instr_header(&record->instr_header, wire, at);
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->vwap_price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->trade_volume[i]; }

  return at;
}

/* Trade Session Volume Message off the wire: 34 bytes from at, returning where the next byte lies */
static size_t decode_trade_session_volume_message(TradeSessionVolumeMessage *record, const uint8_t *wire, size_t at) {
  at = decode_instr_header(&record->instr_header, wire, at);
  for (size_t i = 0; i < 8; i++) { record->vwap_price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->trade_volume[i] = wire[at++]; }

  return at;
}

/* what was read of Trade Session Volume Message is what was written, byte for byte */
static void equal_trade_session_volume_message(const TradeSessionVolumeMessage *read, const TradeSessionVolumeMessage *written) {
  equal_instr_header(&read->instr_header, &written->instr_header);
  for (size_t i = 0; i < 8; i++) { assert(read->vwap_price[i] == written->vwap_price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->trade_volume[i] == written->trade_volume[i]); }
}

/* Trade Session Volume Message: written and read back, then read and written back */
static void check_trade_session_volume_message(void) {
  TradeSessionVolumeMessage sent;
  TradeSessionVolumeMessage got;
  uint8_t wire[34];
  uint8_t again[34];

  any_trade_session_volume_message(&sent);
  assert(encode_trade_session_volume_message(&sent, wire, 0) == 34);
  assert(decode_trade_session_volume_message(&got, wire, 0) == 34);
  equal_trade_session_volume_message(&got, &sent);

  for (size_t i = 0; i < 34; i++) { wire[i] = arbitrary(); }
  assert(decode_trade_session_volume_message(&got, wire, 0) == 34);
  assert(encode_trade_session_volume_message(&got, again, 0) == 34);
  for (size_t i = 0; i < 34; i++) { assert(again[i] == wire[i]); }
}

/* ---- Open Interest Message: 26 bytes ----------------------------------------- */

/* OpenInterestMessage */
typedef struct {
  InstrHeader instr_header;  /* bytes 0 to 21 */
  uint8_t quantity[4];       /* bytes 22 to 25 */
} OpenInterestMessage;

/* any Open Interest Message at all: every byte one the checker chooses */
static void any_open_interest_message(OpenInterestMessage *record) {
  any_instr_header(&record->instr_header);
  for (size_t i = 0; i < 4; i++) { record->quantity[i] = arbitrary(); }
}

/* Open Interest Message to the wire: 26 bytes from at, returning where the next byte goes */
static size_t encode_open_interest_message(const OpenInterestMessage *record, uint8_t *wire, size_t at) {
  at = encode_instr_header(&record->instr_header, wire, at);
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->quantity[i]; }

  return at;
}

/* Open Interest Message off the wire: 26 bytes from at, returning where the next byte lies */
static size_t decode_open_interest_message(OpenInterestMessage *record, const uint8_t *wire, size_t at) {
  at = decode_instr_header(&record->instr_header, wire, at);
  for (size_t i = 0; i < 4; i++) { record->quantity[i] = wire[at++]; }

  return at;
}

/* what was read of Open Interest Message is what was written, byte for byte */
static void equal_open_interest_message(const OpenInterestMessage *read, const OpenInterestMessage *written) {
  equal_instr_header(&read->instr_header, &written->instr_header);
  for (size_t i = 0; i < 4; i++) { assert(read->quantity[i] == written->quantity[i]); }
}

/* Open Interest Message: written and read back, then read and written back */
static void check_open_interest_message(void) {
  OpenInterestMessage sent;
  OpenInterestMessage got;
  uint8_t wire[26];
  uint8_t again[26];

  any_open_interest_message(&sent);
  assert(encode_open_interest_message(&sent, wire, 0) == 26);
  assert(decode_open_interest_message(&got, wire, 0) == 26);
  equal_open_interest_message(&got, &sent);

  for (size_t i = 0; i < 26; i++) { wire[i] = arbitrary(); }
  assert(decode_open_interest_message(&got, wire, 0) == 26);
  assert(encode_open_interest_message(&got, again, 0) == 26);
  for (size_t i = 0; i < 26; i++) { assert(again[i] == wire[i]); }
}

/* ---- Start Of Outright Instrument Snapshot Message: 130 bytes ---------------- */

/* StartOfOutrightInstrumentSnapshotMessage */
typedef struct {
  uint8_t snapshot_seq_num[2];            /* bytes 0 to 1 */
  uint8_t last_instr_seq_num[4];          /* bytes 2 to 5 */
  uint8_t symbol[24];                     /* bytes 6 to 29 */
  uint8_t product_code[8];                /* bytes 30 to 37 */
  uint8_t description[32];                /* bytes 38 to 69 */
  uint8_t tick_size[8];                   /* bytes 70 to 77 */
  uint8_t cfi_code[8];                    /* bytes 78 to 85 */
  uint8_t currency[8];                    /* bytes 86 to 93 */
  uint8_t product_id[4];                  /* bytes 94 to 97 */
  uint8_t old_contract_size[4];           /* bytes 98 to 101 */
  uint8_t order_count[4];                 /* bytes 102 to 105 */
  uint8_t first_trading_session_date[2];  /* bytes 106 to 107 */
  uint8_t last_trading_session_date[2];   /* bytes 108 to 109 */
  uint8_t trading_session_date[2];        /* bytes 110 to 111 */
  uint8_t product_group;                  /* byte 112 */
  uint8_t trading_status;                 /* byte 113 */
  uint8_t contract_size[8];               /* bytes 114 to 121 */
  LogicalExpiry logical_expiry;           /* bytes 122 to 129 */
} StartOfOutrightInstrumentSnapshotMessage;

/* any Start Of Outright Instrument Snapshot Message at all: every byte one the checker chooses */
static void any_start_of_outright_instrument_snapshot_message(StartOfOutrightInstrumentSnapshotMessage *record) {
  for (size_t i = 0; i < 2; i++) { record->snapshot_seq_num[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->last_instr_seq_num[i] = arbitrary(); }
  for (size_t i = 0; i < 24; i++) { record->symbol[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->product_code[i] = arbitrary(); }
  for (size_t i = 0; i < 32; i++) { record->description[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->tick_size[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->cfi_code[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->currency[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->product_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->old_contract_size[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->order_count[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->first_trading_session_date[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->last_trading_session_date[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->trading_session_date[i] = arbitrary(); }
  record->product_group = arbitrary();
  record->trading_status = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->contract_size[i] = arbitrary(); }
  any_logical_expiry(&record->logical_expiry);
}

/* Start Of Outright Instrument Snapshot Message to the wire: 130 bytes from at, returning where the next byte goes */
static size_t encode_start_of_outright_instrument_snapshot_message(const StartOfOutrightInstrumentSnapshotMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->snapshot_seq_num[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->last_instr_seq_num[i]; }
  for (size_t i = 0; i < 24; i++) { wire[at++] = record->symbol[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->product_code[i]; }
  for (size_t i = 0; i < 32; i++) { wire[at++] = record->description[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->tick_size[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->cfi_code[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->currency[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->product_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->old_contract_size[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->order_count[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->first_trading_session_date[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->last_trading_session_date[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->trading_session_date[i]; }
  wire[at++] = record->product_group;
  wire[at++] = record->trading_status;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->contract_size[i]; }
  at = encode_logical_expiry(&record->logical_expiry, wire, at);

  return at;
}

/* Start Of Outright Instrument Snapshot Message off the wire: 130 bytes from at, returning where the next byte lies */
static size_t decode_start_of_outright_instrument_snapshot_message(StartOfOutrightInstrumentSnapshotMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->snapshot_seq_num[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->last_instr_seq_num[i] = wire[at++]; }
  for (size_t i = 0; i < 24; i++) { record->symbol[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->product_code[i] = wire[at++]; }
  for (size_t i = 0; i < 32; i++) { record->description[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->tick_size[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->cfi_code[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->currency[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->product_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->old_contract_size[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->order_count[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->first_trading_session_date[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->last_trading_session_date[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->trading_session_date[i] = wire[at++]; }
  record->product_group = wire[at++];
  record->trading_status = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->contract_size[i] = wire[at++]; }
  at = decode_logical_expiry(&record->logical_expiry, wire, at);

  return at;
}

/* what was read of Start Of Outright Instrument Snapshot Message is what was written, byte for byte */
static void equal_start_of_outright_instrument_snapshot_message(const StartOfOutrightInstrumentSnapshotMessage *read, const StartOfOutrightInstrumentSnapshotMessage *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->snapshot_seq_num[i] == written->snapshot_seq_num[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->last_instr_seq_num[i] == written->last_instr_seq_num[i]); }
  for (size_t i = 0; i < 24; i++) { assert(read->symbol[i] == written->symbol[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->product_code[i] == written->product_code[i]); }
  for (size_t i = 0; i < 32; i++) { assert(read->description[i] == written->description[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->tick_size[i] == written->tick_size[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->cfi_code[i] == written->cfi_code[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->currency[i] == written->currency[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->product_id[i] == written->product_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->old_contract_size[i] == written->old_contract_size[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->order_count[i] == written->order_count[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->first_trading_session_date[i] == written->first_trading_session_date[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->last_trading_session_date[i] == written->last_trading_session_date[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->trading_session_date[i] == written->trading_session_date[i]); }
  assert(read->product_group == written->product_group);
  assert(read->trading_status == written->trading_status);
  for (size_t i = 0; i < 8; i++) { assert(read->contract_size[i] == written->contract_size[i]); }
  equal_logical_expiry(&read->logical_expiry, &written->logical_expiry);
}

/* Start Of Outright Instrument Snapshot Message: written and read back, then read and written back */
static void check_start_of_outright_instrument_snapshot_message(void) {
  StartOfOutrightInstrumentSnapshotMessage sent;
  StartOfOutrightInstrumentSnapshotMessage got;
  uint8_t wire[130];
  uint8_t again[130];

  any_start_of_outright_instrument_snapshot_message(&sent);
  assert(encode_start_of_outright_instrument_snapshot_message(&sent, wire, 0) == 130);
  assert(decode_start_of_outright_instrument_snapshot_message(&got, wire, 0) == 130);
  equal_start_of_outright_instrument_snapshot_message(&got, &sent);

  for (size_t i = 0; i < 130; i++) { wire[i] = arbitrary(); }
  assert(decode_start_of_outright_instrument_snapshot_message(&got, wire, 0) == 130);
  assert(encode_start_of_outright_instrument_snapshot_message(&got, again, 0) == 130);
  for (size_t i = 0; i < 130; i++) { assert(again[i] == wire[i]); }
}

/* ---- Start Of Spread Instrument Snapshot Message: 131 bytes ------------------ */

/* StartOfSpreadInstrumentSnapshotMessage */
typedef struct {
  uint8_t snapshot_seq_num[2];            /* bytes 0 to 1 */
  uint8_t last_instr_seq_num[4];          /* bytes 2 to 5 */
  uint8_t symbol[24];                     /* bytes 6 to 29 */
  uint8_t product_code[8];                /* bytes 30 to 37 */
  uint8_t description[32];                /* bytes 38 to 69 */
  uint8_t tick_size[8];                   /* bytes 70 to 77 */
  uint8_t cfi_code[8];                    /* bytes 78 to 85 */
  uint8_t currency[8];                    /* bytes 86 to 93 */
  uint8_t product_id[4];                  /* bytes 94 to 97 */
  uint8_t old_contract_size[4];           /* bytes 98 to 101 */
  uint8_t order_count[4];                 /* bytes 102 to 105 */
  uint8_t first_trading_session_date[2];  /* bytes 106 to 107 */
  uint8_t last_trading_session_date[2];   /* bytes 108 to 109 */
  uint8_t trading_session_date[2];        /* bytes 110 to 111 */
  uint8_t product_group;                  /* byte 112 */
  uint8_t trading_status;                 /* byte 113 */
  uint8_t leg_1_instrument_id[4];         /* bytes 114 to 117 */
  uint8_t leg_2_instrument_id[4];         /* bytes 118 to 121 */
  uint8_t spread_buy_convention;          /* byte 122 */
  LogicalExpiry logical_expiry;           /* bytes 123 to 130 */
} StartOfSpreadInstrumentSnapshotMessage;

/* any Start Of Spread Instrument Snapshot Message at all: every byte one the checker chooses */
static void any_start_of_spread_instrument_snapshot_message(StartOfSpreadInstrumentSnapshotMessage *record) {
  for (size_t i = 0; i < 2; i++) { record->snapshot_seq_num[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->last_instr_seq_num[i] = arbitrary(); }
  for (size_t i = 0; i < 24; i++) { record->symbol[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->product_code[i] = arbitrary(); }
  for (size_t i = 0; i < 32; i++) { record->description[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->tick_size[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->cfi_code[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->currency[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->product_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->old_contract_size[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->order_count[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->first_trading_session_date[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->last_trading_session_date[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->trading_session_date[i] = arbitrary(); }
  record->product_group = arbitrary();
  record->trading_status = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->leg_1_instrument_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->leg_2_instrument_id[i] = arbitrary(); }
  record->spread_buy_convention = arbitrary();
  any_logical_expiry(&record->logical_expiry);
}

/* Start Of Spread Instrument Snapshot Message to the wire: 131 bytes from at, returning where the next byte goes */
static size_t encode_start_of_spread_instrument_snapshot_message(const StartOfSpreadInstrumentSnapshotMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->snapshot_seq_num[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->last_instr_seq_num[i]; }
  for (size_t i = 0; i < 24; i++) { wire[at++] = record->symbol[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->product_code[i]; }
  for (size_t i = 0; i < 32; i++) { wire[at++] = record->description[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->tick_size[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->cfi_code[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->currency[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->product_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->old_contract_size[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->order_count[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->first_trading_session_date[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->last_trading_session_date[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->trading_session_date[i]; }
  wire[at++] = record->product_group;
  wire[at++] = record->trading_status;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->leg_1_instrument_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->leg_2_instrument_id[i]; }
  wire[at++] = record->spread_buy_convention;
  at = encode_logical_expiry(&record->logical_expiry, wire, at);

  return at;
}

/* Start Of Spread Instrument Snapshot Message off the wire: 131 bytes from at, returning where the next byte lies */
static size_t decode_start_of_spread_instrument_snapshot_message(StartOfSpreadInstrumentSnapshotMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->snapshot_seq_num[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->last_instr_seq_num[i] = wire[at++]; }
  for (size_t i = 0; i < 24; i++) { record->symbol[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->product_code[i] = wire[at++]; }
  for (size_t i = 0; i < 32; i++) { record->description[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->tick_size[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->cfi_code[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->currency[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->product_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->old_contract_size[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->order_count[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->first_trading_session_date[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->last_trading_session_date[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->trading_session_date[i] = wire[at++]; }
  record->product_group = wire[at++];
  record->trading_status = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->leg_1_instrument_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->leg_2_instrument_id[i] = wire[at++]; }
  record->spread_buy_convention = wire[at++];
  at = decode_logical_expiry(&record->logical_expiry, wire, at);

  return at;
}

/* what was read of Start Of Spread Instrument Snapshot Message is what was written, byte for byte */
static void equal_start_of_spread_instrument_snapshot_message(const StartOfSpreadInstrumentSnapshotMessage *read, const StartOfSpreadInstrumentSnapshotMessage *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->snapshot_seq_num[i] == written->snapshot_seq_num[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->last_instr_seq_num[i] == written->last_instr_seq_num[i]); }
  for (size_t i = 0; i < 24; i++) { assert(read->symbol[i] == written->symbol[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->product_code[i] == written->product_code[i]); }
  for (size_t i = 0; i < 32; i++) { assert(read->description[i] == written->description[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->tick_size[i] == written->tick_size[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->cfi_code[i] == written->cfi_code[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->currency[i] == written->currency[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->product_id[i] == written->product_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->old_contract_size[i] == written->old_contract_size[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->order_count[i] == written->order_count[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->first_trading_session_date[i] == written->first_trading_session_date[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->last_trading_session_date[i] == written->last_trading_session_date[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->trading_session_date[i] == written->trading_session_date[i]); }
  assert(read->product_group == written->product_group);
  assert(read->trading_status == written->trading_status);
  for (size_t i = 0; i < 4; i++) { assert(read->leg_1_instrument_id[i] == written->leg_1_instrument_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->leg_2_instrument_id[i] == written->leg_2_instrument_id[i]); }
  assert(read->spread_buy_convention == written->spread_buy_convention);
  equal_logical_expiry(&read->logical_expiry, &written->logical_expiry);
}

/* Start Of Spread Instrument Snapshot Message: written and read back, then read and written back */
static void check_start_of_spread_instrument_snapshot_message(void) {
  StartOfSpreadInstrumentSnapshotMessage sent;
  StartOfSpreadInstrumentSnapshotMessage got;
  uint8_t wire[131];
  uint8_t again[131];

  any_start_of_spread_instrument_snapshot_message(&sent);
  assert(encode_start_of_spread_instrument_snapshot_message(&sent, wire, 0) == 131);
  assert(decode_start_of_spread_instrument_snapshot_message(&got, wire, 0) == 131);
  equal_start_of_spread_instrument_snapshot_message(&got, &sent);

  for (size_t i = 0; i < 131; i++) { wire[i] = arbitrary(); }
  assert(decode_start_of_spread_instrument_snapshot_message(&got, wire, 0) == 131);
  assert(encode_start_of_spread_instrument_snapshot_message(&got, again, 0) == 131);
  for (size_t i = 0; i < 131; i++) { assert(again[i] == wire[i]); }
}

/* ---- Order Snapshot Message: 30 bytes ---------------------------------------- */

/* OrderSnapshotMessage */
typedef struct {
  uint8_t snapshot_seq_num[2];  /* bytes 0 to 1 */
  uint8_t quantity[4];          /* bytes 2 to 5 */
  uint8_t transact_time[8];     /* bytes 6 to 13 */
  uint8_t order_id[8];          /* bytes 14 to 21 */
  uint8_t price[8];             /* bytes 22 to 29 */
} OrderSnapshotMessage;

/* any Order Snapshot Message at all: every byte one the checker chooses */
static void any_order_snapshot_message(OrderSnapshotMessage *record) {
  for (size_t i = 0; i < 2; i++) { record->snapshot_seq_num[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->transact_time[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->price[i] = arbitrary(); }
}

/* Order Snapshot Message to the wire: 30 bytes from at, returning where the next byte goes */
static size_t encode_order_snapshot_message(const OrderSnapshotMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->snapshot_seq_num[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->quantity[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->transact_time[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price[i]; }

  return at;
}

/* Order Snapshot Message off the wire: 30 bytes from at, returning where the next byte lies */
static size_t decode_order_snapshot_message(OrderSnapshotMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->snapshot_seq_num[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->transact_time[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->price[i] = wire[at++]; }

  return at;
}

/* what was read of Order Snapshot Message is what was written, byte for byte */
static void equal_order_snapshot_message(const OrderSnapshotMessage *read, const OrderSnapshotMessage *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->snapshot_seq_num[i] == written->snapshot_seq_num[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->quantity[i] == written->quantity[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->transact_time[i] == written->transact_time[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->order_id[i] == written->order_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->price[i] == written->price[i]); }
}

/* Order Snapshot Message: written and read back, then read and written back */
static void check_order_snapshot_message(void) {
  OrderSnapshotMessage sent;
  OrderSnapshotMessage got;
  uint8_t wire[30];
  uint8_t again[30];

  any_order_snapshot_message(&sent);
  assert(encode_order_snapshot_message(&sent, wire, 0) == 30);
  assert(decode_order_snapshot_message(&got, wire, 0) == 30);
  equal_order_snapshot_message(&got, &sent);

  for (size_t i = 0; i < 30; i++) { wire[i] = arbitrary(); }
  assert(decode_order_snapshot_message(&got, wire, 0) == 30);
  assert(encode_order_snapshot_message(&got, again, 0) == 30);
  for (size_t i = 0; i < 30; i++) { assert(again[i] == wire[i]); }
}

/* ---- End Of Cycle Message: 4 bytes ------------------------------------------- */

/* EndOfCycleMessage */
typedef struct {
  uint8_t active_instrument_count[4];  /* bytes 0 to 3 */
} EndOfCycleMessage;

/* any End Of Cycle Message at all: every byte one the checker chooses */
static void any_end_of_cycle_message(EndOfCycleMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->active_instrument_count[i] = arbitrary(); }
}

/* End Of Cycle Message to the wire: 4 bytes from at, returning where the next byte goes */
static size_t encode_end_of_cycle_message(const EndOfCycleMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->active_instrument_count[i]; }

  return at;
}

/* End Of Cycle Message off the wire: 4 bytes from at, returning where the next byte lies */
static size_t decode_end_of_cycle_message(EndOfCycleMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->active_instrument_count[i] = wire[at++]; }

  return at;
}

/* what was read of End Of Cycle Message is what was written, byte for byte */
static void equal_end_of_cycle_message(const EndOfCycleMessage *read, const EndOfCycleMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->active_instrument_count[i] == written->active_instrument_count[i]); }
}

/* End Of Cycle Message: written and read back, then read and written back */
static void check_end_of_cycle_message(void) {
  EndOfCycleMessage sent;
  EndOfCycleMessage got;
  uint8_t wire[4];
  uint8_t again[4];

  any_end_of_cycle_message(&sent);
  assert(encode_end_of_cycle_message(&sent, wire, 0) == 4);
  assert(decode_end_of_cycle_message(&got, wire, 0) == 4);
  equal_end_of_cycle_message(&got, &sent);

  for (size_t i = 0; i < 4; i++) { wire[i] = arbitrary(); }
  assert(decode_end_of_cycle_message(&got, wire, 0) == 4);
  assert(encode_end_of_cycle_message(&got, again, 0) == 4);
  for (size_t i = 0; i < 4; i++) { assert(again[i] == wire[i]); }
}

/* ---- Retransmit Request Message: 9 bytes ------------------------------------- */

/* RetransmitRequestMessage */
typedef struct {
  uint8_t begin_seq_num[8];  /* bytes 0 to 7 */
  uint8_t message_count;     /* byte 8 */
} RetransmitRequestMessage;

/* any Retransmit Request Message at all: every byte one the checker chooses */
static void any_retransmit_request_message(RetransmitRequestMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->begin_seq_num[i] = arbitrary(); }
  record->message_count = arbitrary();
}

/* Retransmit Request Message to the wire: 9 bytes from at, returning where the next byte goes */
static size_t encode_retransmit_request_message(const RetransmitRequestMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->begin_seq_num[i]; }
  wire[at++] = record->message_count;

  return at;
}

/* Retransmit Request Message off the wire: 9 bytes from at, returning where the next byte lies */
static size_t decode_retransmit_request_message(RetransmitRequestMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->begin_seq_num[i] = wire[at++]; }
  record->message_count = wire[at++];

  return at;
}

/* what was read of Retransmit Request Message is what was written, byte for byte */
static void equal_retransmit_request_message(const RetransmitRequestMessage *read, const RetransmitRequestMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->begin_seq_num[i] == written->begin_seq_num[i]); }
  assert(read->message_count == written->message_count);
}

/* Retransmit Request Message: written and read back, then read and written back */
static void check_retransmit_request_message(void) {
  RetransmitRequestMessage sent;
  RetransmitRequestMessage got;
  uint8_t wire[9];
  uint8_t again[9];

  any_retransmit_request_message(&sent);
  assert(encode_retransmit_request_message(&sent, wire, 0) == 9);
  assert(decode_retransmit_request_message(&got, wire, 0) == 9);
  equal_retransmit_request_message(&got, &sent);

  for (size_t i = 0; i < 9; i++) { wire[i] = arbitrary(); }
  assert(decode_retransmit_request_message(&got, wire, 0) == 9);
  assert(encode_retransmit_request_message(&got, again, 0) == 9);
  for (size_t i = 0; i < 9; i++) { assert(again[i] == wire[i]); }
}

/* ---- Retransmit Reject Message: 49 bytes ------------------------------------- */

/* RetransmitRejectMessage */
typedef struct {
  uint8_t retry_delay_nanos[8];  /* bytes 0 to 7 */
  uint8_t details[40];           /* bytes 8 to 47 */
  uint8_t reason;                /* byte 48 */
} RetransmitRejectMessage;

/* any Retransmit Reject Message at all: every byte one the checker chooses */
static void any_retransmit_reject_message(RetransmitRejectMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->retry_delay_nanos[i] = arbitrary(); }
  for (size_t i = 0; i < 40; i++) { record->details[i] = arbitrary(); }
  record->reason = arbitrary();
}

/* Retransmit Reject Message to the wire: 49 bytes from at, returning where the next byte goes */
static size_t encode_retransmit_reject_message(const RetransmitRejectMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->retry_delay_nanos[i]; }
  for (size_t i = 0; i < 40; i++) { wire[at++] = record->details[i]; }
  wire[at++] = record->reason;

  return at;
}

/* Retransmit Reject Message off the wire: 49 bytes from at, returning where the next byte lies */
static size_t decode_retransmit_reject_message(RetransmitRejectMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->retry_delay_nanos[i] = wire[at++]; }
  for (size_t i = 0; i < 40; i++) { record->details[i] = wire[at++]; }
  record->reason = wire[at++];

  return at;
}

/* what was read of Retransmit Reject Message is what was written, byte for byte */
static void equal_retransmit_reject_message(const RetransmitRejectMessage *read, const RetransmitRejectMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->retry_delay_nanos[i] == written->retry_delay_nanos[i]); }
  for (size_t i = 0; i < 40; i++) { assert(read->details[i] == written->details[i]); }
  assert(read->reason == written->reason);
}

/* Retransmit Reject Message: written and read back, then read and written back */
static void check_retransmit_reject_message(void) {
  RetransmitRejectMessage sent;
  RetransmitRejectMessage got;
  uint8_t wire[49];
  uint8_t again[49];

  any_retransmit_reject_message(&sent);
  assert(encode_retransmit_reject_message(&sent, wire, 0) == 49);
  assert(decode_retransmit_reject_message(&got, wire, 0) == 49);
  equal_retransmit_reject_message(&got, &sent);

  for (size_t i = 0; i < 49; i++) { wire[i] = arbitrary(); }
  assert(decode_retransmit_reject_message(&got, wire, 0) == 49);
  assert(encode_retransmit_reject_message(&got, again, 0) == 49);
  for (size_t i = 0; i < 49; i++) { assert(again[i] == wire[i]); }
}

/* ---- What esbmc checks ------------------------------------------------------- */

/* every record of the protocol, each on its own buffers */
static void checks(void) {
  check_message_header();
  check_instr_header();
  check_logical_expiry();
  check_trading_status_update_message();
  check_order_put_message();
  check_order_delete_message();
  check_implied_order_update_message();
  check_trade_summary_message();
  check_trade_message();
  check_trade_amend_message();
  check_spread_trade_amend_message();
  check_trade_bust_message();
  check_market_stat_message();
  check_trade_session_volume_message();
  check_open_interest_message();
  check_start_of_outright_instrument_snapshot_message();
  check_start_of_spread_instrument_snapshot_message();
  check_order_snapshot_message();
  check_end_of_cycle_message();
  check_retransmit_request_message();
  check_retransmit_reject_message();
}

int main(void) {
#ifdef CONCRETE
  for (pattern = 0; pattern < 4; pattern++) { checks(); }
#else
  checks();
#endif

  return 0;
}
