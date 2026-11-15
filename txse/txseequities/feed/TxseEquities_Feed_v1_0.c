// txse/txseequities/feed/TxseEquities_Feed_v1_0.c
/*
 * Texas Stock Exchange FEED Full-Depth Market Data
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

/* ---- Udp Header: 19 bytes ---------------------------------------------------- */

/* Rake Udp packet header */
typedef struct {
  uint8_t session[8];        /* bytes 0 to 7 */
  uint8_t sequence[8];       /* bytes 8 to 15 */
  uint8_t message_count[2];  /* bytes 16 to 17 */
  uint8_t packet_type;       /* byte 18 */
} UdpHeader;

/* any Udp Header at all: every byte one the checker chooses */
static void any_udp_header(UdpHeader *record) {
  for (size_t i = 0; i < 8; i++) { record->session[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->sequence[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->message_count[i] = arbitrary(); }
  record->packet_type = arbitrary();
}

/* Udp Header to the wire: 19 bytes from at, returning where the next byte goes */
static size_t encode_udp_header(const UdpHeader *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->session[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->sequence[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->message_count[i]; }
  wire[at++] = record->packet_type;

  return at;
}

/* Udp Header off the wire: 19 bytes from at, returning where the next byte lies */
static size_t decode_udp_header(UdpHeader *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->session[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->sequence[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->message_count[i] = wire[at++]; }
  record->packet_type = wire[at++];

  return at;
}

/* what was read of Udp Header is what was written, byte for byte */
static void equal_udp_header(const UdpHeader *read, const UdpHeader *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->session[i] == written->session[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->sequence[i] == written->sequence[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->message_count[i] == written->message_count[i]); }
  assert(read->packet_type == written->packet_type);
}

/* Udp Header: written and read back, then read and written back */
static void check_udp_header(void) {
  UdpHeader sent;
  UdpHeader got;
  uint8_t wire[19];
  uint8_t again[19];

  any_udp_header(&sent);
  assert(encode_udp_header(&sent, wire, 0) == 19);
  assert(decode_udp_header(&got, wire, 0) == 19);
  equal_udp_header(&got, &sent);

  for (size_t i = 0; i < 19; i++) { wire[i] = arbitrary(); }
  assert(decode_udp_header(&got, wire, 0) == 19);
  assert(encode_udp_header(&got, again, 0) == 19);
  for (size_t i = 0; i < 19; i++) { assert(again[i] == wire[i]); }
}

/* ---- Delete Order Message: 18 bytes ------------------------------------------ */

/* Details for an order deleted in its entirety from the TXSE book. */
typedef struct {
  uint8_t transact_time[8];  /* bytes 0 to 7 */
  uint8_t symbol_id[2];      /* bytes 8 to 9 */
  uint8_t order_id[8];       /* bytes 10 to 17 */
} DeleteOrderMessage;

/* any Delete Order Message at all: every byte one the checker chooses */
static void any_delete_order_message(DeleteOrderMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->transact_time[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->symbol_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = arbitrary(); }
}

/* Delete Order Message to the wire: 18 bytes from at, returning where the next byte goes */
static size_t encode_delete_order_message(const DeleteOrderMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->transact_time[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->symbol_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_id[i]; }

  return at;
}

/* Delete Order Message off the wire: 18 bytes from at, returning where the next byte lies */
static size_t decode_delete_order_message(DeleteOrderMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->transact_time[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->symbol_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = wire[at++]; }

  return at;
}

/* what was read of Delete Order Message is what was written, byte for byte */
static void equal_delete_order_message(const DeleteOrderMessage *read, const DeleteOrderMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->transact_time[i] == written->transact_time[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->symbol_id[i] == written->symbol_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->order_id[i] == written->order_id[i]); }
}

/* Delete Order Message: written and read back, then read and written back */
static void check_delete_order_message(void) {
  DeleteOrderMessage sent;
  DeleteOrderMessage got;
  uint8_t wire[18];
  uint8_t again[18];

  any_delete_order_message(&sent);
  assert(encode_delete_order_message(&sent, wire, 0) == 18);
  assert(decode_delete_order_message(&got, wire, 0) == 18);
  equal_delete_order_message(&got, &sent);

  for (size_t i = 0; i < 18; i++) { wire[i] = arbitrary(); }
  assert(decode_delete_order_message(&got, wire, 0) == 18);
  assert(encode_delete_order_message(&got, again, 0) == 18);
  for (size_t i = 0; i < 18; i++) { assert(again[i] == wire[i]); }
}

/* ---- Execute Order Message: 30 bytes ----------------------------------------- */

/* Indicates that an order displayed on the TXSE book has executed in part or in full at its previously displayed price. */
typedef struct {
  uint8_t transact_time[8];  /* bytes 0 to 7 */
  uint8_t symbol_id[2];      /* bytes 8 to 9 */
  uint8_t order_id[8];       /* bytes 10 to 17 */
  uint8_t qty[4];            /* bytes 18 to 21 */
  uint8_t exec_id[8];        /* bytes 22 to 29 */
} ExecuteOrderMessage;

/* any Execute Order Message at all: every byte one the checker chooses */
static void any_execute_order_message(ExecuteOrderMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->transact_time[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->symbol_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->qty[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->exec_id[i] = arbitrary(); }
}

/* Execute Order Message to the wire: 30 bytes from at, returning where the next byte goes */
static size_t encode_execute_order_message(const ExecuteOrderMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->transact_time[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->symbol_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->qty[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->exec_id[i]; }

  return at;
}

/* Execute Order Message off the wire: 30 bytes from at, returning where the next byte lies */
static size_t decode_execute_order_message(ExecuteOrderMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->transact_time[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->symbol_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->qty[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->exec_id[i] = wire[at++]; }

  return at;
}

/* what was read of Execute Order Message is what was written, byte for byte */
static void equal_execute_order_message(const ExecuteOrderMessage *read, const ExecuteOrderMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->transact_time[i] == written->transact_time[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->symbol_id[i] == written->symbol_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->order_id[i] == written->order_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->qty[i] == written->qty[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->exec_id[i] == written->exec_id[i]); }
}

/* Execute Order Message: written and read back, then read and written back */
static void check_execute_order_message(void) {
  ExecuteOrderMessage sent;
  ExecuteOrderMessage got;
  uint8_t wire[30];
  uint8_t again[30];

  any_execute_order_message(&sent);
  assert(encode_execute_order_message(&sent, wire, 0) == 30);
  assert(decode_execute_order_message(&got, wire, 0) == 30);
  equal_execute_order_message(&got, &sent);

  for (size_t i = 0; i < 30; i++) { wire[i] = arbitrary(); }
  assert(decode_execute_order_message(&got, wire, 0) == 30);
  assert(encode_execute_order_message(&got, again, 0) == 30);
  for (size_t i = 0; i < 30; i++) { assert(again[i] == wire[i]); }
}

/* ---- Modify Size Down Message: 22 bytes -------------------------------------- */

/* Modify an order by reducing its size without losing priority on the TXSE book. */
typedef struct {
  uint8_t transact_time[8];  /* bytes 0 to 7 */
  uint8_t symbol_id[2];      /* bytes 8 to 9 */
  uint8_t order_id[8];       /* bytes 10 to 17 */
  uint8_t qty[4];            /* bytes 18 to 21 */
} ModifySizeDownMessage;

/* any Modify Size Down Message at all: every byte one the checker chooses */
static void any_modify_size_down_message(ModifySizeDownMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->transact_time[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->symbol_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->qty[i] = arbitrary(); }
}

/* Modify Size Down Message to the wire: 22 bytes from at, returning where the next byte goes */
static size_t encode_modify_size_down_message(const ModifySizeDownMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->transact_time[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->symbol_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->qty[i]; }

  return at;
}

/* Modify Size Down Message off the wire: 22 bytes from at, returning where the next byte lies */
static size_t decode_modify_size_down_message(ModifySizeDownMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->transact_time[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->symbol_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->qty[i] = wire[at++]; }

  return at;
}

/* what was read of Modify Size Down Message is what was written, byte for byte */
static void equal_modify_size_down_message(const ModifySizeDownMessage *read, const ModifySizeDownMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->transact_time[i] == written->transact_time[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->symbol_id[i] == written->symbol_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->order_id[i] == written->order_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->qty[i] == written->qty[i]); }
}

/* Modify Size Down Message: written and read back, then read and written back */
static void check_modify_size_down_message(void) {
  ModifySizeDownMessage sent;
  ModifySizeDownMessage got;
  uint8_t wire[22];
  uint8_t again[22];

  any_modify_size_down_message(&sent);
  assert(encode_modify_size_down_message(&sent, wire, 0) == 22);
  assert(decode_modify_size_down_message(&got, wire, 0) == 22);
  equal_modify_size_down_message(&got, &sent);

  for (size_t i = 0; i < 22; i++) { wire[i] = arbitrary(); }
  assert(decode_modify_size_down_message(&got, wire, 0) == 22);
  assert(encode_modify_size_down_message(&got, again, 0) == 22);
  for (size_t i = 0; i < 22; i++) { assert(again[i] == wire[i]); }
}

/* ---- Replace Order Message: 38 bytes ----------------------------------------- */

/* Replace an order, possibly changing price level and size (which can increase), losing priority on the TXSE book. */
typedef struct {
  uint8_t transact_time[8];  /* bytes 0 to 7 */
  uint8_t symbol_id[2];      /* bytes 8 to 9 */
  uint8_t old_order_id[8];   /* bytes 10 to 17 */
  uint8_t new_order_id[8];   /* bytes 18 to 25 */
  uint8_t price[8];          /* bytes 26 to 33 */
  uint8_t qty[4];            /* bytes 34 to 37 */
} ReplaceOrderMessage;

/* any Replace Order Message at all: every byte one the checker chooses */
static void any_replace_order_message(ReplaceOrderMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->transact_time[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->symbol_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->old_order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->new_order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->qty[i] = arbitrary(); }
}

/* Replace Order Message to the wire: 38 bytes from at, returning where the next byte goes */
static size_t encode_replace_order_message(const ReplaceOrderMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->transact_time[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->symbol_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->old_order_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->new_order_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->qty[i]; }

  return at;
}

/* Replace Order Message off the wire: 38 bytes from at, returning where the next byte lies */
static size_t decode_replace_order_message(ReplaceOrderMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->transact_time[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->symbol_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->old_order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->new_order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->qty[i] = wire[at++]; }

  return at;
}

/* what was read of Replace Order Message is what was written, byte for byte */
static void equal_replace_order_message(const ReplaceOrderMessage *read, const ReplaceOrderMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->transact_time[i] == written->transact_time[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->symbol_id[i] == written->symbol_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->old_order_id[i] == written->old_order_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->new_order_id[i] == written->new_order_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->price[i] == written->price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->qty[i] == written->qty[i]); }
}

/* Replace Order Message: written and read back, then read and written back */
static void check_replace_order_message(void) {
  ReplaceOrderMessage sent;
  ReplaceOrderMessage got;
  uint8_t wire[38];
  uint8_t again[38];

  any_replace_order_message(&sent);
  assert(encode_replace_order_message(&sent, wire, 0) == 38);
  assert(decode_replace_order_message(&got, wire, 0) == 38);
  equal_replace_order_message(&got, &sent);

  for (size_t i = 0; i < 38; i++) { wire[i] = arbitrary(); }
  assert(decode_replace_order_message(&got, wire, 0) == 38);
  assert(encode_replace_order_message(&got, again, 0) == 38);
  for (size_t i = 0; i < 38; i++) { assert(again[i] == wire[i]); }
}

/* ---- Trade Message: 30 bytes ------------------------------------------------- */

/* Execution of non-displayed liquidity. */
typedef struct {
  uint8_t transact_time[8];  /* bytes 0 to 7 */
  uint8_t symbol_id[2];      /* bytes 8 to 9 */
  uint8_t price[8];          /* bytes 10 to 17 */
  uint8_t qty[4];            /* bytes 18 to 21 */
  uint8_t exec_id[8];        /* bytes 22 to 29 */
} TradeMessage;

/* any Trade Message at all: every byte one the checker chooses */
static void any_trade_message(TradeMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->transact_time[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->symbol_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->qty[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->exec_id[i] = arbitrary(); }
}

/* Trade Message to the wire: 30 bytes from at, returning where the next byte goes */
static size_t encode_trade_message(const TradeMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->transact_time[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->symbol_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->qty[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->exec_id[i]; }

  return at;
}

/* Trade Message off the wire: 30 bytes from at, returning where the next byte lies */
static size_t decode_trade_message(TradeMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->transact_time[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->symbol_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->qty[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->exec_id[i] = wire[at++]; }

  return at;
}

/* what was read of Trade Message is what was written, byte for byte */
static void equal_trade_message(const TradeMessage *read, const TradeMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->transact_time[i] == written->transact_time[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->symbol_id[i] == written->symbol_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->price[i] == written->price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->qty[i] == written->qty[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->exec_id[i] == written->exec_id[i]); }
}

/* Trade Message: written and read back, then read and written back */
static void check_trade_message(void) {
  TradeMessage sent;
  TradeMessage got;
  uint8_t wire[30];
  uint8_t again[30];

  any_trade_message(&sent);
  assert(encode_trade_message(&sent, wire, 0) == 30);
  assert(decode_trade_message(&got, wire, 0) == 30);
  equal_trade_message(&got, &sent);

  for (size_t i = 0; i < 30; i++) { wire[i] = arbitrary(); }
  assert(decode_trade_message(&got, wire, 0) == 30);
  assert(encode_trade_message(&got, again, 0) == 30);
  for (size_t i = 0; i < 30; i++) { assert(again[i] == wire[i]); }
}

/* ---- Break Trade Message: 18 bytes ------------------------------------------- */

/* Break a previous trade or execution by execution identifier. */
typedef struct {
  uint8_t transact_time[8];  /* bytes 0 to 7 */
  uint8_t symbol_id[2];      /* bytes 8 to 9 */
  uint8_t exec_id[8];        /* bytes 10 to 17 */
} BreakTradeMessage;

/* any Break Trade Message at all: every byte one the checker chooses */
static void any_break_trade_message(BreakTradeMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->transact_time[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->symbol_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->exec_id[i] = arbitrary(); }
}

/* Break Trade Message to the wire: 18 bytes from at, returning where the next byte goes */
static size_t encode_break_trade_message(const BreakTradeMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->transact_time[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->symbol_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->exec_id[i]; }

  return at;
}

/* Break Trade Message off the wire: 18 bytes from at, returning where the next byte lies */
static size_t decode_break_trade_message(BreakTradeMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->transact_time[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->symbol_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->exec_id[i] = wire[at++]; }

  return at;
}

/* what was read of Break Trade Message is what was written, byte for byte */
static void equal_break_trade_message(const BreakTradeMessage *read, const BreakTradeMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->transact_time[i] == written->transact_time[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->symbol_id[i] == written->symbol_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->exec_id[i] == written->exec_id[i]); }
}

/* Break Trade Message: written and read back, then read and written back */
static void check_break_trade_message(void) {
  BreakTradeMessage sent;
  BreakTradeMessage got;
  uint8_t wire[18];
  uint8_t again[18];

  any_break_trade_message(&sent);
  assert(encode_break_trade_message(&sent, wire, 0) == 18);
  assert(decode_break_trade_message(&got, wire, 0) == 18);
  equal_break_trade_message(&got, &sent);

  for (size_t i = 0; i < 18; i++) { wire[i] = arbitrary(); }
  assert(decode_break_trade_message(&got, wire, 0) == 18);
  assert(encode_break_trade_message(&got, again, 0) == 18);
  for (size_t i = 0; i < 18; i++) { assert(again[i] == wire[i]); }
}

/* ---- Auction Preamble Message: 32 bytes -------------------------------------- */

/* Published every 5 seconds during the Accumulation Period to indicate projected auction size. Reports the matched volume and excess side that would result if the auction crossed at that moment, considering only Auction-Only orders; the Continuous Book is excluded. Emitted for OPENING and CLOSING auction types only. Not emitted for HALT or IPO auctions, which proceed directly to the Band Window phase at onset (see AuctionBandWindow). */
typedef struct {
  uint8_t transact_time[8];     /* bytes 0 to 7 */
  uint8_t symbol_id[2];         /* bytes 8 to 9 */
  uint8_t auction_type;         /* byte 10 */
  uint8_t auction_start[8];     /* bytes 11 to 18 */
  uint8_t matched_shares[4];    /* bytes 19 to 22 */
  uint8_t excess_auction_side;  /* byte 23 */
  uint8_t reserved_8[8];        /* bytes 24 to 31 */
} AuctionPreambleMessage;

/* any Auction Preamble Message at all: every byte one the checker chooses */
static void any_auction_preamble_message(AuctionPreambleMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->transact_time[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->symbol_id[i] = arbitrary(); }
  record->auction_type = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->auction_start[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->matched_shares[i] = arbitrary(); }
  record->excess_auction_side = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->reserved_8[i] = arbitrary(); }
}

/* Auction Preamble Message to the wire: 32 bytes from at, returning where the next byte goes */
static size_t encode_auction_preamble_message(const AuctionPreambleMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->transact_time[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->symbol_id[i]; }
  wire[at++] = record->auction_type;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->auction_start[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->matched_shares[i]; }
  wire[at++] = record->excess_auction_side;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->reserved_8[i]; }

  return at;
}

/* Auction Preamble Message off the wire: 32 bytes from at, returning where the next byte lies */
static size_t decode_auction_preamble_message(AuctionPreambleMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->transact_time[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->symbol_id[i] = wire[at++]; }
  record->auction_type = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->auction_start[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->matched_shares[i] = wire[at++]; }
  record->excess_auction_side = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->reserved_8[i] = wire[at++]; }

  return at;
}

/* what was read of Auction Preamble Message is what was written, byte for byte */
static void equal_auction_preamble_message(const AuctionPreambleMessage *read, const AuctionPreambleMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->transact_time[i] == written->transact_time[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->symbol_id[i] == written->symbol_id[i]); }
  assert(read->auction_type == written->auction_type);
  for (size_t i = 0; i < 8; i++) { assert(read->auction_start[i] == written->auction_start[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->matched_shares[i] == written->matched_shares[i]); }
  assert(read->excess_auction_side == written->excess_auction_side);
  for (size_t i = 0; i < 8; i++) { assert(read->reserved_8[i] == written->reserved_8[i]); }
}

/* Auction Preamble Message: written and read back, then read and written back */
static void check_auction_preamble_message(void) {
  AuctionPreambleMessage sent;
  AuctionPreambleMessage got;
  uint8_t wire[32];
  uint8_t again[32];

  any_auction_preamble_message(&sent);
  assert(encode_auction_preamble_message(&sent, wire, 0) == 32);
  assert(decode_auction_preamble_message(&got, wire, 0) == 32);
  equal_auction_preamble_message(&got, &sent);

  for (size_t i = 0; i < 32; i++) { wire[i] = arbitrary(); }
  assert(decode_auction_preamble_message(&got, wire, 0) == 32);
  assert(encode_auction_preamble_message(&got, again, 0) == 32);
  for (size_t i = 0; i < 32; i++) { assert(again[i] == wire[i]); }
}

/* ---- Auction Band Window Message: 60 bytes ----------------------------------- */

/* Published every 5 seconds during the Band Window to report Auction-Only volume positioned at each Participation Band boundary. The Participation Band is a volatility-based price range; its derivation methodology is described in the Participation Bands specification. Auction-Only orders entered during the Band Window that are priced outside the band have their price adjusted to the nearest boundary. The Continuous Book is excluded. Volume counting at boundaries: a limit order is counted at each boundary price at which it would be eligible to execute; a market order is counted at both boundaries. Example: a limit buy at $10.05 counts at the lower boundary if lower = $10.05, but not at the upper boundary if upper = $10.10. */
typedef struct {
  uint8_t transact_time[8];             /* bytes 0 to 7 */
  uint8_t symbol_id[2];                 /* bytes 8 to 9 */
  uint8_t auction_type;                 /* byte 10 */
  uint8_t auction_start[8];             /* bytes 11 to 18 */
  uint8_t extension_cycle_count;        /* byte 19 */
  uint8_t lower_participation_band[8];  /* bytes 20 to 27 */
  uint8_t buy_shares_at_lower[4];       /* bytes 28 to 31 */
  uint8_t sell_shares_at_lower[4];      /* bytes 32 to 35 */
  uint8_t upper_participation_band[8];  /* bytes 36 to 43 */
  uint8_t buy_shares_at_upper[4];       /* bytes 44 to 47 */
  uint8_t sell_shares_at_upper[4];      /* bytes 48 to 51 */
  uint8_t reserved_8[8];                /* bytes 52 to 59 */
} AuctionBandWindowMessage;

/* any Auction Band Window Message at all: every byte one the checker chooses */
static void any_auction_band_window_message(AuctionBandWindowMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->transact_time[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->symbol_id[i] = arbitrary(); }
  record->auction_type = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->auction_start[i] = arbitrary(); }
  record->extension_cycle_count = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->lower_participation_band[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->buy_shares_at_lower[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->sell_shares_at_lower[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->upper_participation_band[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->buy_shares_at_upper[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->sell_shares_at_upper[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->reserved_8[i] = arbitrary(); }
}

/* Auction Band Window Message to the wire: 60 bytes from at, returning where the next byte goes */
static size_t encode_auction_band_window_message(const AuctionBandWindowMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->transact_time[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->symbol_id[i]; }
  wire[at++] = record->auction_type;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->auction_start[i]; }
  wire[at++] = record->extension_cycle_count;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->lower_participation_band[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->buy_shares_at_lower[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->sell_shares_at_lower[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->upper_participation_band[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->buy_shares_at_upper[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->sell_shares_at_upper[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->reserved_8[i]; }

  return at;
}

/* Auction Band Window Message off the wire: 60 bytes from at, returning where the next byte lies */
static size_t decode_auction_band_window_message(AuctionBandWindowMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->transact_time[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->symbol_id[i] = wire[at++]; }
  record->auction_type = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->auction_start[i] = wire[at++]; }
  record->extension_cycle_count = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->lower_participation_band[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->buy_shares_at_lower[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->sell_shares_at_lower[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->upper_participation_band[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->buy_shares_at_upper[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->sell_shares_at_upper[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->reserved_8[i] = wire[at++]; }

  return at;
}

/* what was read of Auction Band Window Message is what was written, byte for byte */
static void equal_auction_band_window_message(const AuctionBandWindowMessage *read, const AuctionBandWindowMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->transact_time[i] == written->transact_time[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->symbol_id[i] == written->symbol_id[i]); }
  assert(read->auction_type == written->auction_type);
  for (size_t i = 0; i < 8; i++) { assert(read->auction_start[i] == written->auction_start[i]); }
  assert(read->extension_cycle_count == written->extension_cycle_count);
  for (size_t i = 0; i < 8; i++) { assert(read->lower_participation_band[i] == written->lower_participation_band[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->buy_shares_at_lower[i] == written->buy_shares_at_lower[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->sell_shares_at_lower[i] == written->sell_shares_at_lower[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->upper_participation_band[i] == written->upper_participation_band[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->buy_shares_at_upper[i] == written->buy_shares_at_upper[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->sell_shares_at_upper[i] == written->sell_shares_at_upper[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->reserved_8[i] == written->reserved_8[i]); }
}

/* Auction Band Window Message: written and read back, then read and written back */
static void check_auction_band_window_message(void) {
  AuctionBandWindowMessage sent;
  AuctionBandWindowMessage got;
  uint8_t wire[60];
  uint8_t again[60];

  any_auction_band_window_message(&sent);
  assert(encode_auction_band_window_message(&sent, wire, 0) == 60);
  assert(decode_auction_band_window_message(&got, wire, 0) == 60);
  equal_auction_band_window_message(&got, &sent);

  for (size_t i = 0; i < 60; i++) { wire[i] = arbitrary(); }
  assert(decode_auction_band_window_message(&got, wire, 0) == 60);
  assert(encode_auction_band_window_message(&got, again, 0) == 60);
  for (size_t i = 0; i < 60; i++) { assert(again[i] == wire[i]); }
}

/* ---- Auction Print Message: 31 bytes ----------------------------------------- */

/* Summary of an auction cross. Emitted before any per-order auction execution messages for the same cross. Universal lifecycle terminator — emitted for every auction. Encoding: (a) matchedShares > 0 with a valid auctionPrice indicates a normal cross; (b) matchedShares = 0 with a valid auctionPrice indicates a zero-share completion (e.g., halt-into-close default or demand failure); (c) matchedShares = 0 with auctionPrice = CANCELED_SENTINEL indicates a canceled auction. Where the feed publishes per-order auction executions, those executions share this message's execId. */
typedef struct {
  uint8_t transact_time[8];   /* bytes 0 to 7 */
  uint8_t symbol_id[2];       /* bytes 8 to 9 */
  uint8_t auction_type;       /* byte 10 */
  uint8_t auction_price[8];   /* bytes 11 to 18 */
  uint8_t matched_shares[4];  /* bytes 19 to 22 */
  uint8_t exec_id[8];         /* bytes 23 to 30 */
} AuctionPrintMessage;

/* any Auction Print Message at all: every byte one the checker chooses */
static void any_auction_print_message(AuctionPrintMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->transact_time[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->symbol_id[i] = arbitrary(); }
  record->auction_type = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->auction_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->matched_shares[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->exec_id[i] = arbitrary(); }
}

/* Auction Print Message to the wire: 31 bytes from at, returning where the next byte goes */
static size_t encode_auction_print_message(const AuctionPrintMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->transact_time[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->symbol_id[i]; }
  wire[at++] = record->auction_type;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->auction_price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->matched_shares[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->exec_id[i]; }

  return at;
}

/* Auction Print Message off the wire: 31 bytes from at, returning where the next byte lies */
static size_t decode_auction_print_message(AuctionPrintMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->transact_time[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->symbol_id[i] = wire[at++]; }
  record->auction_type = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->auction_price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->matched_shares[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->exec_id[i] = wire[at++]; }

  return at;
}

/* what was read of Auction Print Message is what was written, byte for byte */
static void equal_auction_print_message(const AuctionPrintMessage *read, const AuctionPrintMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->transact_time[i] == written->transact_time[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->symbol_id[i] == written->symbol_id[i]); }
  assert(read->auction_type == written->auction_type);
  for (size_t i = 0; i < 8; i++) { assert(read->auction_price[i] == written->auction_price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->matched_shares[i] == written->matched_shares[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->exec_id[i] == written->exec_id[i]); }
}

/* Auction Print Message: written and read back, then read and written back */
static void check_auction_print_message(void) {
  AuctionPrintMessage sent;
  AuctionPrintMessage got;
  uint8_t wire[31];
  uint8_t again[31];

  any_auction_print_message(&sent);
  assert(encode_auction_print_message(&sent, wire, 0) == 31);
  assert(decode_auction_print_message(&got, wire, 0) == 31);
  equal_auction_print_message(&got, &sent);

  for (size_t i = 0; i < 31; i++) { wire[i] = arbitrary(); }
  assert(decode_auction_print_message(&got, wire, 0) == 31);
  assert(encode_auction_print_message(&got, again, 0) == 31);
  for (size_t i = 0; i < 31; i++) { assert(again[i] == wire[i]); }
}

/* ---- What esbmc checks ------------------------------------------------------- */

/* every record of the protocol, each on its own buffers */
static void checks(void) {
  check_udp_header();
  check_delete_order_message();
  check_execute_order_message();
  check_modify_size_down_message();
  check_replace_order_message();
  check_trade_message();
  check_break_trade_message();
  check_auction_preamble_message();
  check_auction_band_window_message();
  check_auction_print_message();
}

int main(void) {
#ifdef CONCRETE
  for (pattern = 0; pattern < 4; pattern++) { checks(); }
#else
  checks();
#endif

  return 0;
}
