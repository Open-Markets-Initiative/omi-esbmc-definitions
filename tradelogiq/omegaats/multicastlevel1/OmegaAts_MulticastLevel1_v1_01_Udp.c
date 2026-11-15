// tradelogiq/omegaats/multicastlevel1/OmegaAts_MulticastLevel1_v1_01_Udp.c
/*
 * Tradelogiq Markets Inc. Omega Multicast Level 1
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

/* ---- Packet Header: 20 bytes ------------------------------------------------- */

/* Tradelogiq Qtp Downstream Packet Header */
typedef struct {
  uint8_t session[10];         /* bytes 0 to 9 */
  uint8_t sequence_number[8];  /* bytes 10 to 17 */
  uint8_t message_count[2];    /* bytes 18 to 19 */
} PacketHeader;

/* any Packet Header at all: every byte one the checker chooses */
static void any_packet_header(PacketHeader *record) {
  for (size_t i = 0; i < 10; i++) { record->session[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->sequence_number[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->message_count[i] = arbitrary(); }
}

/* Packet Header to the wire: 20 bytes from at, returning where the next byte goes */
static size_t encode_packet_header(const PacketHeader *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->session[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->sequence_number[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->message_count[i]; }

  return at;
}

/* Packet Header off the wire: 20 bytes from at, returning where the next byte lies */
static size_t decode_packet_header(PacketHeader *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 10; i++) { record->session[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->sequence_number[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->message_count[i] = wire[at++]; }

  return at;
}

/* what was read of Packet Header is what was written, byte for byte */
static void equal_packet_header(const PacketHeader *read, const PacketHeader *written) {
  for (size_t i = 0; i < 10; i++) { assert(read->session[i] == written->session[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->sequence_number[i] == written->sequence_number[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->message_count[i] == written->message_count[i]); }
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

/* Tradelogiq Qtp Message Block Header */
typedef struct {
  uint8_t message_length[2];  /* bytes 0 to 1 */
  uint8_t message_type;       /* byte 2 */
} MessageHeader;

/* any Message Header at all: every byte one the checker chooses */
static void any_message_header(MessageHeader *record) {
  for (size_t i = 0; i < 2; i++) { record->message_length[i] = arbitrary(); }
  record->message_type = arbitrary();
}

/* Message Header to the wire: 3 bytes from at, returning where the next byte goes */
static size_t encode_message_header(const MessageHeader *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->message_length[i]; }
  wire[at++] = record->message_type;

  return at;
}

/* Message Header off the wire: 3 bytes from at, returning where the next byte lies */
static size_t decode_message_header(MessageHeader *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->message_length[i] = wire[at++]; }
  record->message_type = wire[at++];

  return at;
}

/* what was read of Message Header is what was written, byte for byte */
static void equal_message_header(const MessageHeader *read, const MessageHeader *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->message_length[i] == written->message_length[i]); }
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

/* ---- Quote Message: 43 bytes ------------------------------------------------- */

/* Tradelogiq's BBO will broadcast real-time updates every time Tradelogiq's top of book changes. */
typedef struct {
  uint8_t reserved_1;         /* byte 0 */
  uint8_t stock_symbol[10];   /* bytes 1 to 10 */
  uint8_t timestamp[8];       /* bytes 11 to 18 */
  uint8_t best_bid_price[8];  /* bytes 19 to 26 */
  uint8_t best_bid_size[4];   /* bytes 27 to 30 */
  uint8_t best_ask_price[8];  /* bytes 31 to 38 */
  uint8_t best_ask_size[4];   /* bytes 39 to 42 */
} QuoteMessage;

/* any Quote Message at all: every byte one the checker chooses */
static void any_quote_message(QuoteMessage *record) {
  record->reserved_1 = arbitrary();
  for (size_t i = 0; i < 10; i++) { record->stock_symbol[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->best_bid_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->best_bid_size[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->best_ask_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->best_ask_size[i] = arbitrary(); }
}

/* Quote Message to the wire: 43 bytes from at, returning where the next byte goes */
static size_t encode_quote_message(const QuoteMessage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->reserved_1;
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->stock_symbol[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->best_bid_price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->best_bid_size[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->best_ask_price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->best_ask_size[i]; }

  return at;
}

/* Quote Message off the wire: 43 bytes from at, returning where the next byte lies */
static size_t decode_quote_message(QuoteMessage *record, const uint8_t *wire, size_t at) {
  record->reserved_1 = wire[at++];
  for (size_t i = 0; i < 10; i++) { record->stock_symbol[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->best_bid_price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->best_bid_size[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->best_ask_price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->best_ask_size[i] = wire[at++]; }

  return at;
}

/* what was read of Quote Message is what was written, byte for byte */
static void equal_quote_message(const QuoteMessage *read, const QuoteMessage *written) {
  assert(read->reserved_1 == written->reserved_1);
  for (size_t i = 0; i < 10; i++) { assert(read->stock_symbol[i] == written->stock_symbol[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->best_bid_price[i] == written->best_bid_price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->best_bid_size[i] == written->best_bid_size[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->best_ask_price[i] == written->best_ask_price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->best_ask_size[i] == written->best_ask_size[i]); }
}

/* Quote Message: written and read back, then read and written back */
static void check_quote_message(void) {
  QuoteMessage sent;
  QuoteMessage got;
  uint8_t wire[43];
  uint8_t again[43];

  any_quote_message(&sent);
  assert(encode_quote_message(&sent, wire, 0) == 43);
  assert(decode_quote_message(&got, wire, 0) == 43);
  equal_quote_message(&got, &sent);

  for (size_t i = 0; i < 43; i++) { wire[i] = arbitrary(); }
  assert(decode_quote_message(&got, wire, 0) == 43);
  assert(encode_quote_message(&got, again, 0) == 43);
  for (size_t i = 0; i < 43; i++) { assert(again[i] == wire[i]); }
}

/* ---- Trade Report Message: 43 bytes ------------------------------------------ */

/* Relays all transactions available from or reported by Tradelogiq's two trading books for the current business day. */
typedef struct {
  uint8_t conditions[5];     /* bytes 0 to 4 */
  uint8_t stock_symbol[10];  /* bytes 5 to 14 */
  uint8_t timestamp[8];      /* bytes 15 to 22 */
  uint8_t trade_id[4];       /* bytes 23 to 26 */
  uint8_t trade_price[8];    /* bytes 27 to 34 */
  uint8_t trade_size[4];     /* bytes 35 to 38 */
  uint8_t buy_broker[2];     /* bytes 39 to 40 */
  uint8_t sell_broker[2];    /* bytes 41 to 42 */
} TradeReportMessage;

/* any Trade Report Message at all: every byte one the checker chooses */
static void any_trade_report_message(TradeReportMessage *record) {
  for (size_t i = 0; i < 5; i++) { record->conditions[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->stock_symbol[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->trade_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->trade_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->trade_size[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->buy_broker[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->sell_broker[i] = arbitrary(); }
}

/* Trade Report Message to the wire: 43 bytes from at, returning where the next byte goes */
static size_t encode_trade_report_message(const TradeReportMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 5; i++) { wire[at++] = record->conditions[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->stock_symbol[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->trade_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->trade_price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->trade_size[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->buy_broker[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->sell_broker[i]; }

  return at;
}

/* Trade Report Message off the wire: 43 bytes from at, returning where the next byte lies */
static size_t decode_trade_report_message(TradeReportMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 5; i++) { record->conditions[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->stock_symbol[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->trade_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->trade_price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->trade_size[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->buy_broker[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->sell_broker[i] = wire[at++]; }

  return at;
}

/* what was read of Trade Report Message is what was written, byte for byte */
static void equal_trade_report_message(const TradeReportMessage *read, const TradeReportMessage *written) {
  for (size_t i = 0; i < 5; i++) { assert(read->conditions[i] == written->conditions[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->stock_symbol[i] == written->stock_symbol[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->trade_id[i] == written->trade_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->trade_price[i] == written->trade_price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->trade_size[i] == written->trade_size[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->buy_broker[i] == written->buy_broker[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->sell_broker[i] == written->sell_broker[i]); }
}

/* Trade Report Message: written and read back, then read and written back */
static void check_trade_report_message(void) {
  TradeReportMessage sent;
  TradeReportMessage got;
  uint8_t wire[43];
  uint8_t again[43];

  any_trade_report_message(&sent);
  assert(encode_trade_report_message(&sent, wire, 0) == 43);
  assert(decode_trade_report_message(&got, wire, 0) == 43);
  equal_trade_report_message(&got, &sent);

  for (size_t i = 0; i < 43; i++) { wire[i] = arbitrary(); }
  assert(decode_trade_report_message(&got, wire, 0) == 43);
  assert(encode_trade_report_message(&got, again, 0) == 43);
  for (size_t i = 0; i < 43; i++) { assert(again[i] == wire[i]); }
}

/* ---- Trade Bust Message: 23 bytes -------------------------------------------- */

/* If trade is cancelled or busted during the day Trade Bust Message will be sent. */
typedef struct {
  uint8_t reserved_1;        /* byte 0 */
  uint8_t stock_symbol[10];  /* bytes 1 to 10 */
  uint8_t timestamp[8];      /* bytes 11 to 18 */
  uint8_t trade_id[4];       /* bytes 19 to 22 */
} TradeBustMessage;

/* any Trade Bust Message at all: every byte one the checker chooses */
static void any_trade_bust_message(TradeBustMessage *record) {
  record->reserved_1 = arbitrary();
  for (size_t i = 0; i < 10; i++) { record->stock_symbol[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->trade_id[i] = arbitrary(); }
}

/* Trade Bust Message to the wire: 23 bytes from at, returning where the next byte goes */
static size_t encode_trade_bust_message(const TradeBustMessage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->reserved_1;
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->stock_symbol[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->trade_id[i]; }

  return at;
}

/* Trade Bust Message off the wire: 23 bytes from at, returning where the next byte lies */
static size_t decode_trade_bust_message(TradeBustMessage *record, const uint8_t *wire, size_t at) {
  record->reserved_1 = wire[at++];
  for (size_t i = 0; i < 10; i++) { record->stock_symbol[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->trade_id[i] = wire[at++]; }

  return at;
}

/* what was read of Trade Bust Message is what was written, byte for byte */
static void equal_trade_bust_message(const TradeBustMessage *read, const TradeBustMessage *written) {
  assert(read->reserved_1 == written->reserved_1);
  for (size_t i = 0; i < 10; i++) { assert(read->stock_symbol[i] == written->stock_symbol[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->trade_id[i] == written->trade_id[i]); }
}

/* Trade Bust Message: written and read back, then read and written back */
static void check_trade_bust_message(void) {
  TradeBustMessage sent;
  TradeBustMessage got;
  uint8_t wire[23];
  uint8_t again[23];

  any_trade_bust_message(&sent);
  assert(encode_trade_bust_message(&sent, wire, 0) == 23);
  assert(decode_trade_bust_message(&got, wire, 0) == 23);
  equal_trade_bust_message(&got, &sent);

  for (size_t i = 0; i < 23; i++) { wire[i] = arbitrary(); }
  assert(decode_trade_bust_message(&got, wire, 0) == 23);
  assert(encode_trade_bust_message(&got, again, 0) == 23);
  for (size_t i = 0; i < 23; i++) { assert(again[i] == wire[i]); }
}

/* ---- Trade Correction Message: 47 bytes -------------------------------------- */

/* Trade amendments during the day will send this message. */
typedef struct {
  uint8_t reserved_1;                /* byte 0 */
  uint8_t stock_symbol[10];          /* bytes 1 to 10 */
  uint8_t timestamp[8];              /* bytes 11 to 18 */
  uint8_t original_trade_id[4];      /* bytes 19 to 22 */
  uint8_t original_trade_price[8];   /* bytes 23 to 30 */
  uint8_t original_trade_size[4];    /* bytes 31 to 34 */
  uint8_t corrected_trade_price[8];  /* bytes 35 to 42 */
  uint8_t corrected_trade_size[4];   /* bytes 43 to 46 */
} TradeCorrectionMessage;

/* any Trade Correction Message at all: every byte one the checker chooses */
static void any_trade_correction_message(TradeCorrectionMessage *record) {
  record->reserved_1 = arbitrary();
  for (size_t i = 0; i < 10; i++) { record->stock_symbol[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->original_trade_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->original_trade_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->original_trade_size[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->corrected_trade_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->corrected_trade_size[i] = arbitrary(); }
}

/* Trade Correction Message to the wire: 47 bytes from at, returning where the next byte goes */
static size_t encode_trade_correction_message(const TradeCorrectionMessage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->reserved_1;
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->stock_symbol[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->original_trade_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->original_trade_price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->original_trade_size[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->corrected_trade_price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->corrected_trade_size[i]; }

  return at;
}

/* Trade Correction Message off the wire: 47 bytes from at, returning where the next byte lies */
static size_t decode_trade_correction_message(TradeCorrectionMessage *record, const uint8_t *wire, size_t at) {
  record->reserved_1 = wire[at++];
  for (size_t i = 0; i < 10; i++) { record->stock_symbol[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->original_trade_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->original_trade_price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->original_trade_size[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->corrected_trade_price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->corrected_trade_size[i] = wire[at++]; }

  return at;
}

/* what was read of Trade Correction Message is what was written, byte for byte */
static void equal_trade_correction_message(const TradeCorrectionMessage *read, const TradeCorrectionMessage *written) {
  assert(read->reserved_1 == written->reserved_1);
  for (size_t i = 0; i < 10; i++) { assert(read->stock_symbol[i] == written->stock_symbol[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->original_trade_id[i] == written->original_trade_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->original_trade_price[i] == written->original_trade_price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->original_trade_size[i] == written->original_trade_size[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->corrected_trade_price[i] == written->corrected_trade_price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->corrected_trade_size[i] == written->corrected_trade_size[i]); }
}

/* Trade Correction Message: written and read back, then read and written back */
static void check_trade_correction_message(void) {
  TradeCorrectionMessage sent;
  TradeCorrectionMessage got;
  uint8_t wire[47];
  uint8_t again[47];

  any_trade_correction_message(&sent);
  assert(encode_trade_correction_message(&sent, wire, 0) == 47);
  assert(decode_trade_correction_message(&got, wire, 0) == 47);
  equal_trade_correction_message(&got, &sent);

  for (size_t i = 0; i < 47; i++) { wire[i] = arbitrary(); }
  assert(decode_trade_correction_message(&got, wire, 0) == 47);
  assert(encode_trade_correction_message(&got, again, 0) == 47);
  for (size_t i = 0; i < 47; i++) { assert(again[i] == wire[i]); }
}

/* ---- System Event Message: 11 bytes ------------------------------------------ */

/* The system event message is used to signal a market or a data feed handler event. */
typedef struct {
  uint8_t event_code;     /* byte 0 */
  uint8_t reserved_2[2];  /* bytes 1 to 2 */
  uint8_t timestamp[8];   /* bytes 3 to 10 */
} SystemEventMessage;

/* any System Event Message at all: every byte one the checker chooses */
static void any_system_event_message(SystemEventMessage *record) {
  record->event_code = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->reserved_2[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
}

/* System Event Message to the wire: 11 bytes from at, returning where the next byte goes */
static size_t encode_system_event_message(const SystemEventMessage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->event_code;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->reserved_2[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }

  return at;
}

/* System Event Message off the wire: 11 bytes from at, returning where the next byte lies */
static size_t decode_system_event_message(SystemEventMessage *record, const uint8_t *wire, size_t at) {
  record->event_code = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->reserved_2[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }

  return at;
}

/* what was read of System Event Message is what was written, byte for byte */
static void equal_system_event_message(const SystemEventMessage *read, const SystemEventMessage *written) {
  assert(read->event_code == written->event_code);
  for (size_t i = 0; i < 2; i++) { assert(read->reserved_2[i] == written->reserved_2[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
}

/* System Event Message: written and read back, then read and written back */
static void check_system_event_message(void) {
  SystemEventMessage sent;
  SystemEventMessage got;
  uint8_t wire[11];
  uint8_t again[11];

  any_system_event_message(&sent);
  assert(encode_system_event_message(&sent, wire, 0) == 11);
  assert(decode_system_event_message(&got, wire, 0) == 11);
  equal_system_event_message(&got, &sent);

  for (size_t i = 0; i < 11; i++) { wire[i] = arbitrary(); }
  assert(decode_system_event_message(&got, wire, 0) == 11);
  assert(encode_system_event_message(&got, again, 0) == 11);
  for (size_t i = 0; i < 11; i++) { assert(again[i] == wire[i]); }
}

/* ---- Stock Directory Message: 39 bytes --------------------------------------- */

/* At start of each trading day, OSI disseminates stock directory messages for supported securities. */
typedef struct {
  uint8_t market;              /* byte 0 */
  uint8_t stock[10];           /* bytes 1 to 10 */
  uint8_t timestamp[8];        /* bytes 11 to 18 */
  uint8_t board_lot_size[4];   /* bytes 19 to 22 */
  uint8_t instrument_id[2];    /* bytes 23 to 24 */
  uint8_t shortable;           /* byte 25 */
  uint8_t dividend_indicator;  /* byte 26 */
  uint8_t reserved_9[9];       /* bytes 27 to 35 */
  uint8_t currency[3];         /* bytes 36 to 38 */
} StockDirectoryMessage;

/* any Stock Directory Message at all: every byte one the checker chooses */
static void any_stock_directory_message(StockDirectoryMessage *record) {
  record->market = arbitrary();
  for (size_t i = 0; i < 10; i++) { record->stock[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->board_lot_size[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->instrument_id[i] = arbitrary(); }
  record->shortable = arbitrary();
  record->dividend_indicator = arbitrary();
  for (size_t i = 0; i < 9; i++) { record->reserved_9[i] = arbitrary(); }
  for (size_t i = 0; i < 3; i++) { record->currency[i] = arbitrary(); }
}

/* Stock Directory Message to the wire: 39 bytes from at, returning where the next byte goes */
static size_t encode_stock_directory_message(const StockDirectoryMessage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->market;
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->stock[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->board_lot_size[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->instrument_id[i]; }
  wire[at++] = record->shortable;
  wire[at++] = record->dividend_indicator;
  for (size_t i = 0; i < 9; i++) { wire[at++] = record->reserved_9[i]; }
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->currency[i]; }

  return at;
}

/* Stock Directory Message off the wire: 39 bytes from at, returning where the next byte lies */
static size_t decode_stock_directory_message(StockDirectoryMessage *record, const uint8_t *wire, size_t at) {
  record->market = wire[at++];
  for (size_t i = 0; i < 10; i++) { record->stock[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->board_lot_size[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->instrument_id[i] = wire[at++]; }
  record->shortable = wire[at++];
  record->dividend_indicator = wire[at++];
  for (size_t i = 0; i < 9; i++) { record->reserved_9[i] = wire[at++]; }
  for (size_t i = 0; i < 3; i++) { record->currency[i] = wire[at++]; }

  return at;
}

/* what was read of Stock Directory Message is what was written, byte for byte */
static void equal_stock_directory_message(const StockDirectoryMessage *read, const StockDirectoryMessage *written) {
  assert(read->market == written->market);
  for (size_t i = 0; i < 10; i++) { assert(read->stock[i] == written->stock[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->board_lot_size[i] == written->board_lot_size[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->instrument_id[i] == written->instrument_id[i]); }
  assert(read->shortable == written->shortable);
  assert(read->dividend_indicator == written->dividend_indicator);
  for (size_t i = 0; i < 9; i++) { assert(read->reserved_9[i] == written->reserved_9[i]); }
  for (size_t i = 0; i < 3; i++) { assert(read->currency[i] == written->currency[i]); }
}

/* Stock Directory Message: written and read back, then read and written back */
static void check_stock_directory_message(void) {
  StockDirectoryMessage sent;
  StockDirectoryMessage got;
  uint8_t wire[39];
  uint8_t again[39];

  any_stock_directory_message(&sent);
  assert(encode_stock_directory_message(&sent, wire, 0) == 39);
  assert(decode_stock_directory_message(&got, wire, 0) == 39);
  equal_stock_directory_message(&got, &sent);

  for (size_t i = 0; i < 39; i++) { wire[i] = arbitrary(); }
  assert(decode_stock_directory_message(&got, wire, 0) == 39);
  assert(encode_stock_directory_message(&got, again, 0) == 39);
  for (size_t i = 0; i < 39; i++) { assert(again[i] == wire[i]); }
}

/* ---- Extended Stock Directory Message: 71 bytes ------------------------------ */

/* Extended Stock Directory are for Special stock symbols eg warrants debentures rights. */
typedef struct {
  uint8_t market;             /* byte 0 */
  uint8_t stock[10];          /* bytes 1 to 10 */
  uint8_t timestamp[8];       /* bytes 11 to 18 */
  uint8_t board_lot_size[4];  /* bytes 19 to 22 */
  uint8_t instrument_id[2];   /* bytes 23 to 24 */
  uint8_t shortable;          /* byte 25 */
  uint8_t frequency;          /* byte 26 */
  uint8_t reserved_9[9];      /* bytes 27 to 35 */
  uint8_t currency[3];        /* bytes 36 to 38 */
  uint8_t security_type;      /* byte 39 */
  uint8_t expiry_date[8];     /* bytes 40 to 47 */
  uint8_t description[20];    /* bytes 48 to 67 */
  uint8_t reserved_3[3];      /* bytes 68 to 70 */
} ExtendedStockDirectoryMessage;

/* any Extended Stock Directory Message at all: every byte one the checker chooses */
static void any_extended_stock_directory_message(ExtendedStockDirectoryMessage *record) {
  record->market = arbitrary();
  for (size_t i = 0; i < 10; i++) { record->stock[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->board_lot_size[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->instrument_id[i] = arbitrary(); }
  record->shortable = arbitrary();
  record->frequency = arbitrary();
  for (size_t i = 0; i < 9; i++) { record->reserved_9[i] = arbitrary(); }
  for (size_t i = 0; i < 3; i++) { record->currency[i] = arbitrary(); }
  record->security_type = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->expiry_date[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->description[i] = arbitrary(); }
  for (size_t i = 0; i < 3; i++) { record->reserved_3[i] = arbitrary(); }
}

/* Extended Stock Directory Message to the wire: 71 bytes from at, returning where the next byte goes */
static size_t encode_extended_stock_directory_message(const ExtendedStockDirectoryMessage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->market;
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->stock[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->board_lot_size[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->instrument_id[i]; }
  wire[at++] = record->shortable;
  wire[at++] = record->frequency;
  for (size_t i = 0; i < 9; i++) { wire[at++] = record->reserved_9[i]; }
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->currency[i]; }
  wire[at++] = record->security_type;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->expiry_date[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->description[i]; }
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->reserved_3[i]; }

  return at;
}

/* Extended Stock Directory Message off the wire: 71 bytes from at, returning where the next byte lies */
static size_t decode_extended_stock_directory_message(ExtendedStockDirectoryMessage *record, const uint8_t *wire, size_t at) {
  record->market = wire[at++];
  for (size_t i = 0; i < 10; i++) { record->stock[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->board_lot_size[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->instrument_id[i] = wire[at++]; }
  record->shortable = wire[at++];
  record->frequency = wire[at++];
  for (size_t i = 0; i < 9; i++) { record->reserved_9[i] = wire[at++]; }
  for (size_t i = 0; i < 3; i++) { record->currency[i] = wire[at++]; }
  record->security_type = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->expiry_date[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->description[i] = wire[at++]; }
  for (size_t i = 0; i < 3; i++) { record->reserved_3[i] = wire[at++]; }

  return at;
}

/* what was read of Extended Stock Directory Message is what was written, byte for byte */
static void equal_extended_stock_directory_message(const ExtendedStockDirectoryMessage *read, const ExtendedStockDirectoryMessage *written) {
  assert(read->market == written->market);
  for (size_t i = 0; i < 10; i++) { assert(read->stock[i] == written->stock[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->board_lot_size[i] == written->board_lot_size[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->instrument_id[i] == written->instrument_id[i]); }
  assert(read->shortable == written->shortable);
  assert(read->frequency == written->frequency);
  for (size_t i = 0; i < 9; i++) { assert(read->reserved_9[i] == written->reserved_9[i]); }
  for (size_t i = 0; i < 3; i++) { assert(read->currency[i] == written->currency[i]); }
  assert(read->security_type == written->security_type);
  for (size_t i = 0; i < 8; i++) { assert(read->expiry_date[i] == written->expiry_date[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->description[i] == written->description[i]); }
  for (size_t i = 0; i < 3; i++) { assert(read->reserved_3[i] == written->reserved_3[i]); }
}

/* Extended Stock Directory Message: written and read back, then read and written back */
static void check_extended_stock_directory_message(void) {
  ExtendedStockDirectoryMessage sent;
  ExtendedStockDirectoryMessage got;
  uint8_t wire[71];
  uint8_t again[71];

  any_extended_stock_directory_message(&sent);
  assert(encode_extended_stock_directory_message(&sent, wire, 0) == 71);
  assert(decode_extended_stock_directory_message(&got, wire, 0) == 71);
  equal_extended_stock_directory_message(&got, &sent);

  for (size_t i = 0; i < 71; i++) { wire[i] = arbitrary(); }
  assert(decode_extended_stock_directory_message(&got, wire, 0) == 71);
  assert(encode_extended_stock_directory_message(&got, again, 0) == 71);
  for (size_t i = 0; i < 71; i++) { assert(again[i] == wire[i]); }
}

/* ---- Stock Status Message: 23 bytes ------------------------------------------ */

/* This message indicates the current trading status of a stock. */
typedef struct {
  uint8_t trading_state;  /* byte 0 */
  uint8_t stock[10];      /* bytes 1 to 10 */
  uint8_t timestamp[8];   /* bytes 11 to 18 */
  uint8_t reason[4];      /* bytes 19 to 22 */
} StockStatusMessage;

/* any Stock Status Message at all: every byte one the checker chooses */
static void any_stock_status_message(StockStatusMessage *record) {
  record->trading_state = arbitrary();
  for (size_t i = 0; i < 10; i++) { record->stock[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->reason[i] = arbitrary(); }
}

/* Stock Status Message to the wire: 23 bytes from at, returning where the next byte goes */
static size_t encode_stock_status_message(const StockStatusMessage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->trading_state;
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->stock[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->reason[i]; }

  return at;
}

/* Stock Status Message off the wire: 23 bytes from at, returning where the next byte lies */
static size_t decode_stock_status_message(StockStatusMessage *record, const uint8_t *wire, size_t at) {
  record->trading_state = wire[at++];
  for (size_t i = 0; i < 10; i++) { record->stock[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->reason[i] = wire[at++]; }

  return at;
}

/* what was read of Stock Status Message is what was written, byte for byte */
static void equal_stock_status_message(const StockStatusMessage *read, const StockStatusMessage *written) {
  assert(read->trading_state == written->trading_state);
  for (size_t i = 0; i < 10; i++) { assert(read->stock[i] == written->stock[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->reason[i] == written->reason[i]); }
}

/* Stock Status Message: written and read back, then read and written back */
static void check_stock_status_message(void) {
  StockStatusMessage sent;
  StockStatusMessage got;
  uint8_t wire[23];
  uint8_t again[23];

  any_stock_status_message(&sent);
  assert(encode_stock_status_message(&sent, wire, 0) == 23);
  assert(decode_stock_status_message(&got, wire, 0) == 23);
  equal_stock_status_message(&got, &sent);

  for (size_t i = 0; i < 23; i++) { wire[i] = arbitrary(); }
  assert(decode_stock_status_message(&got, wire, 0) == 23);
  assert(encode_stock_status_message(&got, again, 0) == 23);
  for (size_t i = 0; i < 23; i++) { assert(again[i] == wire[i]); }
}

/* ---- What esbmc checks ------------------------------------------------------- */

/* every record of the protocol, each on its own buffers */
static void checks(void) {
  check_packet_header();
  check_message_header();
  check_quote_message();
  check_trade_report_message();
  check_trade_bust_message();
  check_trade_correction_message();
  check_system_event_message();
  check_stock_directory_message();
  check_extended_stock_directory_message();
  check_stock_status_message();
}

int main(void) {
#ifdef CONCRETE
  for (pattern = 0; pattern < 4; pattern++) { checks(); }
#else
  checks();
#endif

  return 0;
}
