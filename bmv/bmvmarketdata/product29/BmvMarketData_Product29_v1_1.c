// bmv/bmvmarketdata/product29/BmvMarketData_Product29_v1_1.c
/*
 * Bolsa Mexicana de Valores Bmv Market Data Product 29
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

/* ---- INTRA Multicast Header: 17 bytes ---------------------------------------- */

/* BMV INTRA Multicast Header */
typedef struct {
  uint8_t length[2];           /* bytes 0 to 1 */
  uint8_t total_messages;      /* byte 2 */
  uint8_t market_data_group;   /* byte 3 */
  uint8_t session;             /* byte 4 */
  uint8_t sequence_number[4];  /* bytes 5 to 8 */
  uint8_t datetime[8];         /* bytes 9 to 16 */
} INTRAMulticastHeader;

/* any INTRA Multicast Header at all: every byte one the checker chooses */
static void any_i_n_t_r_a_multicast_header(INTRAMulticastHeader *record) {
  for (size_t i = 0; i < 2; i++) { record->length[i] = arbitrary(); }
  record->total_messages = arbitrary();
  record->market_data_group = arbitrary();
  record->session = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->sequence_number[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->datetime[i] = arbitrary(); }
}

/* INTRA Multicast Header to the wire: 17 bytes from at, returning where the next byte goes */
static size_t encode_i_n_t_r_a_multicast_header(const INTRAMulticastHeader *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->length[i]; }
  wire[at++] = record->total_messages;
  wire[at++] = record->market_data_group;
  wire[at++] = record->session;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->sequence_number[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->datetime[i]; }

  return at;
}

/* INTRA Multicast Header off the wire: 17 bytes from at, returning where the next byte lies */
static size_t decode_i_n_t_r_a_multicast_header(INTRAMulticastHeader *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->length[i] = wire[at++]; }
  record->total_messages = wire[at++];
  record->market_data_group = wire[at++];
  record->session = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->sequence_number[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->datetime[i] = wire[at++]; }

  return at;
}

/* what was read of INTRA Multicast Header is what was written, byte for byte */
static void equal_i_n_t_r_a_multicast_header(const INTRAMulticastHeader *read, const INTRAMulticastHeader *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->length[i] == written->length[i]); }
  assert(read->total_messages == written->total_messages);
  assert(read->market_data_group == written->market_data_group);
  assert(read->session == written->session);
  for (size_t i = 0; i < 4; i++) { assert(read->sequence_number[i] == written->sequence_number[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->datetime[i] == written->datetime[i]); }
}

/* INTRA Multicast Header: written and read back, then read and written back */
static void check_i_n_t_r_a_multicast_header(void) {
  INTRAMulticastHeader sent;
  INTRAMulticastHeader got;
  uint8_t wire[17];
  uint8_t again[17];

  any_i_n_t_r_a_multicast_header(&sent);
  assert(encode_i_n_t_r_a_multicast_header(&sent, wire, 0) == 17);
  assert(decode_i_n_t_r_a_multicast_header(&got, wire, 0) == 17);
  equal_i_n_t_r_a_multicast_header(&got, &sent);

  for (size_t i = 0; i < 17; i++) { wire[i] = arbitrary(); }
  assert(decode_i_n_t_r_a_multicast_header(&got, wire, 0) == 17);
  assert(encode_i_n_t_r_a_multicast_header(&got, again, 0) == 17);
  for (size_t i = 0; i < 17; i++) { assert(again[i] == wire[i]); }
}

/* ---- Message Header: 3 bytes ------------------------------------------------- */

/* Message length and message type */
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

/* ---- Last Quote Message: 23 bytes -------------------------------------------- */

/* Message sent by instrument when the best bid is modified in the electronic book by the Origin Exchange; denotes the side that is modified, the sale or the purchase. */
typedef struct {
  uint8_t instrument_number[4];  /* bytes 0 to 3 */
  uint8_t origin;                /* byte 4 */
  uint8_t volume[8];             /* bytes 5 to 12 */
  uint8_t price_rate[8];         /* bytes 13 to 20 */
  uint8_t direction_of_the_bid;  /* byte 21 */
  uint8_t type_of_trading;       /* byte 22 */
} LastQuoteMessage;

/* any Last Quote Message at all: every byte one the checker chooses */
static void any_last_quote_message(LastQuoteMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->instrument_number[i] = arbitrary(); }
  record->origin = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->volume[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->price_rate[i] = arbitrary(); }
  record->direction_of_the_bid = arbitrary();
  record->type_of_trading = arbitrary();
}

/* Last Quote Message to the wire: 23 bytes from at, returning where the next byte goes */
static size_t encode_last_quote_message(const LastQuoteMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument_number[i]; }
  wire[at++] = record->origin;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->volume[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price_rate[i]; }
  wire[at++] = record->direction_of_the_bid;
  wire[at++] = record->type_of_trading;

  return at;
}

/* Last Quote Message off the wire: 23 bytes from at, returning where the next byte lies */
static size_t decode_last_quote_message(LastQuoteMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->instrument_number[i] = wire[at++]; }
  record->origin = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->volume[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->price_rate[i] = wire[at++]; }
  record->direction_of_the_bid = wire[at++];
  record->type_of_trading = wire[at++];

  return at;
}

/* what was read of Last Quote Message is what was written, byte for byte */
static void equal_last_quote_message(const LastQuoteMessage *read, const LastQuoteMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->instrument_number[i] == written->instrument_number[i]); }
  assert(read->origin == written->origin);
  for (size_t i = 0; i < 8; i++) { assert(read->volume[i] == written->volume[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->price_rate[i] == written->price_rate[i]); }
  assert(read->direction_of_the_bid == written->direction_of_the_bid);
  assert(read->type_of_trading == written->type_of_trading);
}

/* Last Quote Message: written and read back, then read and written back */
static void check_last_quote_message(void) {
  LastQuoteMessage sent;
  LastQuoteMessage got;
  uint8_t wire[23];
  uint8_t again[23];

  any_last_quote_message(&sent);
  assert(encode_last_quote_message(&sent, wire, 0) == 23);
  assert(decode_last_quote_message(&got, wire, 0) == 23);
  equal_last_quote_message(&got, &sent);

  for (size_t i = 0; i < 23; i++) { wire[i] = arbitrary(); }
  assert(decode_last_quote_message(&got, wire, 0) == 23);
  assert(encode_last_quote_message(&got, again, 0) == 23);
  for (size_t i = 0; i < 23; i++) { assert(again[i] == wire[i]); }
}

/* ---- Benchmark Trade Message: 25 bytes --------------------------------------- */

/* Trading statistics by trade. */
typedef struct {
  uint8_t origin;                   /* byte 0 */
  uint8_t average_volume[8];        /* bytes 1 to 8 */
  uint8_t average_traded_value[8];  /* bytes 9 to 16 */
  uint8_t market;                   /* byte 17 */
  uint8_t sector;                   /* byte 18 */
  uint8_t instrument_number[4];     /* bytes 19 to 22 */
  uint8_t indices[2];               /* bytes 23 to 24 */
} BenchmarkTradeMessage;

/* any Benchmark Trade Message at all: every byte one the checker chooses */
static void any_benchmark_trade_message(BenchmarkTradeMessage *record) {
  record->origin = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->average_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->average_traded_value[i] = arbitrary(); }
  record->market = arbitrary();
  record->sector = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->instrument_number[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->indices[i] = arbitrary(); }
}

/* Benchmark Trade Message to the wire: 25 bytes from at, returning where the next byte goes */
static size_t encode_benchmark_trade_message(const BenchmarkTradeMessage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->origin;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->average_volume[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->average_traded_value[i]; }
  wire[at++] = record->market;
  wire[at++] = record->sector;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument_number[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->indices[i]; }

  return at;
}

/* Benchmark Trade Message off the wire: 25 bytes from at, returning where the next byte lies */
static size_t decode_benchmark_trade_message(BenchmarkTradeMessage *record, const uint8_t *wire, size_t at) {
  record->origin = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->average_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->average_traded_value[i] = wire[at++]; }
  record->market = wire[at++];
  record->sector = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->instrument_number[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->indices[i] = wire[at++]; }

  return at;
}

/* what was read of Benchmark Trade Message is what was written, byte for byte */
static void equal_benchmark_trade_message(const BenchmarkTradeMessage *read, const BenchmarkTradeMessage *written) {
  assert(read->origin == written->origin);
  for (size_t i = 0; i < 8; i++) { assert(read->average_volume[i] == written->average_volume[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->average_traded_value[i] == written->average_traded_value[i]); }
  assert(read->market == written->market);
  assert(read->sector == written->sector);
  for (size_t i = 0; i < 4; i++) { assert(read->instrument_number[i] == written->instrument_number[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->indices[i] == written->indices[i]); }
}

/* Benchmark Trade Message: written and read back, then read and written back */
static void check_benchmark_trade_message(void) {
  BenchmarkTradeMessage sent;
  BenchmarkTradeMessage got;
  uint8_t wire[25];
  uint8_t again[25];

  any_benchmark_trade_message(&sent);
  assert(encode_benchmark_trade_message(&sent, wire, 0) == 25);
  assert(decode_benchmark_trade_message(&got, wire, 0) == 25);
  equal_benchmark_trade_message(&got, &sent);

  for (size_t i = 0; i < 25; i++) { wire[i] = arbitrary(); }
  assert(decode_benchmark_trade_message(&got, wire, 0) == 25);
  assert(encode_benchmark_trade_message(&got, again, 0) == 25);
  for (size_t i = 0; i < 25; i++) { assert(again[i] == wire[i]); }
}

/* ---- Price Leaderboard Message: 33 bytes ------------------------------------- */

/* Measures time proportion that a stock Exchange maintains the best bid and (or) ask throughout the session. */
typedef struct {
  uint8_t origin;                 /* byte 0 */
  uint8_t t_best_bid[4];          /* bytes 1 to 4 */
  uint8_t t_tie_best_bid[4];      /* bytes 5 to 8 */
  uint8_t t_without_best_bid[4];  /* bytes 9 to 12 */
  uint8_t t_best_ask[4];          /* bytes 13 to 16 */
  uint8_t t_tie_best_ask[4];      /* bytes 17 to 20 */
  uint8_t t_without_best_ask[4];  /* bytes 21 to 24 */
  uint8_t market;                 /* byte 25 */
  uint8_t sector;                 /* byte 26 */
  uint8_t instrument_number[4];   /* bytes 27 to 30 */
  uint8_t indices[2];             /* bytes 31 to 32 */
} PriceLeaderboardMessage;

/* any Price Leaderboard Message at all: every byte one the checker chooses */
static void any_price_leaderboard_message(PriceLeaderboardMessage *record) {
  record->origin = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->t_best_bid[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->t_tie_best_bid[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->t_without_best_bid[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->t_best_ask[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->t_tie_best_ask[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->t_without_best_ask[i] = arbitrary(); }
  record->market = arbitrary();
  record->sector = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->instrument_number[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->indices[i] = arbitrary(); }
}

/* Price Leaderboard Message to the wire: 33 bytes from at, returning where the next byte goes */
static size_t encode_price_leaderboard_message(const PriceLeaderboardMessage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->origin;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->t_best_bid[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->t_tie_best_bid[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->t_without_best_bid[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->t_best_ask[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->t_tie_best_ask[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->t_without_best_ask[i]; }
  wire[at++] = record->market;
  wire[at++] = record->sector;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument_number[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->indices[i]; }

  return at;
}

/* Price Leaderboard Message off the wire: 33 bytes from at, returning where the next byte lies */
static size_t decode_price_leaderboard_message(PriceLeaderboardMessage *record, const uint8_t *wire, size_t at) {
  record->origin = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->t_best_bid[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->t_tie_best_bid[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->t_without_best_bid[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->t_best_ask[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->t_tie_best_ask[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->t_without_best_ask[i] = wire[at++]; }
  record->market = wire[at++];
  record->sector = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->instrument_number[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->indices[i] = wire[at++]; }

  return at;
}

/* what was read of Price Leaderboard Message is what was written, byte for byte */
static void equal_price_leaderboard_message(const PriceLeaderboardMessage *read, const PriceLeaderboardMessage *written) {
  assert(read->origin == written->origin);
  for (size_t i = 0; i < 4; i++) { assert(read->t_best_bid[i] == written->t_best_bid[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->t_tie_best_bid[i] == written->t_tie_best_bid[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->t_without_best_bid[i] == written->t_without_best_bid[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->t_best_ask[i] == written->t_best_ask[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->t_tie_best_ask[i] == written->t_tie_best_ask[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->t_without_best_ask[i] == written->t_without_best_ask[i]); }
  assert(read->market == written->market);
  assert(read->sector == written->sector);
  for (size_t i = 0; i < 4; i++) { assert(read->instrument_number[i] == written->instrument_number[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->indices[i] == written->indices[i]); }
}

/* Price Leaderboard Message: written and read back, then read and written back */
static void check_price_leaderboard_message(void) {
  PriceLeaderboardMessage sent;
  PriceLeaderboardMessage got;
  uint8_t wire[33];
  uint8_t again[33];

  any_price_leaderboard_message(&sent);
  assert(encode_price_leaderboard_message(&sent, wire, 0) == 33);
  assert(decode_price_leaderboard_message(&got, wire, 0) == 33);
  equal_price_leaderboard_message(&got, &sent);

  for (size_t i = 0; i < 33; i++) { wire[i] = arbitrary(); }
  assert(decode_price_leaderboard_message(&got, wire, 0) == 33);
  assert(encode_price_leaderboard_message(&got, again, 0) == 33);
  for (size_t i = 0; i < 33; i++) { assert(again[i] == wire[i]); }
}

/* ---- Trading Sniper Message: 73 bytes ---------------------------------------- */

/* Quotes composition analysis, full and first ten depth levels */
typedef struct {
  uint8_t origin;                /* byte 0 */
  uint8_t depth_bid[8];          /* bytes 1 to 8 */
  uint8_t depth_ask[8];          /* bytes 9 to 16 */
  uint8_t depth_bid_10_l[8];     /* bytes 17 to 24 */
  uint8_t depth_ask_10_l[8];     /* bytes 25 to 32 */
  uint8_t vwp_bid_10_l[8];       /* bytes 33 to 40 */
  uint8_t vwp_ask_10_l[8];       /* bytes 41 to 48 */
  uint8_t vwp_bid[8];            /* bytes 49 to 56 */
  uint8_t vwp_ask[8];            /* bytes 57 to 64 */
  uint8_t market;                /* byte 65 */
  uint8_t sector;                /* byte 66 */
  uint8_t instrument_number[4];  /* bytes 67 to 70 */
  uint8_t indices[2];            /* bytes 71 to 72 */
} TradingSniperMessage;

/* any Trading Sniper Message at all: every byte one the checker chooses */
static void any_trading_sniper_message(TradingSniperMessage *record) {
  record->origin = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->depth_bid[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->depth_ask[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->depth_bid_10_l[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->depth_ask_10_l[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->vwp_bid_10_l[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->vwp_ask_10_l[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->vwp_bid[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->vwp_ask[i] = arbitrary(); }
  record->market = arbitrary();
  record->sector = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->instrument_number[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->indices[i] = arbitrary(); }
}

/* Trading Sniper Message to the wire: 73 bytes from at, returning where the next byte goes */
static size_t encode_trading_sniper_message(const TradingSniperMessage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->origin;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->depth_bid[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->depth_ask[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->depth_bid_10_l[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->depth_ask_10_l[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->vwp_bid_10_l[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->vwp_ask_10_l[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->vwp_bid[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->vwp_ask[i]; }
  wire[at++] = record->market;
  wire[at++] = record->sector;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument_number[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->indices[i]; }

  return at;
}

/* Trading Sniper Message off the wire: 73 bytes from at, returning where the next byte lies */
static size_t decode_trading_sniper_message(TradingSniperMessage *record, const uint8_t *wire, size_t at) {
  record->origin = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->depth_bid[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->depth_ask[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->depth_bid_10_l[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->depth_ask_10_l[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->vwp_bid_10_l[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->vwp_ask_10_l[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->vwp_bid[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->vwp_ask[i] = wire[at++]; }
  record->market = wire[at++];
  record->sector = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->instrument_number[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->indices[i] = wire[at++]; }

  return at;
}

/* what was read of Trading Sniper Message is what was written, byte for byte */
static void equal_trading_sniper_message(const TradingSniperMessage *read, const TradingSniperMessage *written) {
  assert(read->origin == written->origin);
  for (size_t i = 0; i < 8; i++) { assert(read->depth_bid[i] == written->depth_bid[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->depth_ask[i] == written->depth_ask[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->depth_bid_10_l[i] == written->depth_bid_10_l[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->depth_ask_10_l[i] == written->depth_ask_10_l[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->vwp_bid_10_l[i] == written->vwp_bid_10_l[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->vwp_ask_10_l[i] == written->vwp_ask_10_l[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->vwp_bid[i] == written->vwp_bid[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->vwp_ask[i] == written->vwp_ask[i]); }
  assert(read->market == written->market);
  assert(read->sector == written->sector);
  for (size_t i = 0; i < 4; i++) { assert(read->instrument_number[i] == written->instrument_number[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->indices[i] == written->indices[i]); }
}

/* Trading Sniper Message: written and read back, then read and written back */
static void check_trading_sniper_message(void) {
  TradingSniperMessage sent;
  TradingSniperMessage got;
  uint8_t wire[73];
  uint8_t again[73];

  any_trading_sniper_message(&sent);
  assert(encode_trading_sniper_message(&sent, wire, 0) == 73);
  assert(decode_trading_sniper_message(&got, wire, 0) == 73);
  equal_trading_sniper_message(&got, &sent);

  for (size_t i = 0; i < 73; i++) { wire[i] = arbitrary(); }
  assert(decode_trading_sniper_message(&got, wire, 0) == 73);
  assert(encode_trading_sniper_message(&got, again, 0) == 73);
  for (size_t i = 0; i < 73; i++) { assert(again[i] == wire[i]); }
}

/* ---- Depth At Best Prices Message: 25 bytes ---------------------------------- */

/* Identify the deepest quotes depth for the national best bid and offer. */
typedef struct {
  uint8_t origin;                /* byte 0 */
  uint8_t instruments_bb[2];     /* bytes 1 to 2 */
  uint8_t instruments_gv_bb[2];  /* bytes 3 to 4 */
  uint8_t ratio_v_at_bb[4];      /* bytes 5 to 8 */
  uint8_t instruments_ba[2];     /* bytes 9 to 10 */
  uint8_t instruments_gv_ba[2];  /* bytes 11 to 12 */
  uint8_t ratio_v_at_ba[4];      /* bytes 13 to 16 */
  uint8_t market;                /* byte 17 */
  uint8_t sector;                /* byte 18 */
  uint8_t instrument_number[4];  /* bytes 19 to 22 */
  uint8_t indices[2];            /* bytes 23 to 24 */
} DepthAtBestPricesMessage;

/* any Depth At Best Prices Message at all: every byte one the checker chooses */
static void any_depth_at_best_prices_message(DepthAtBestPricesMessage *record) {
  record->origin = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->instruments_bb[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->instruments_gv_bb[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->ratio_v_at_bb[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->instruments_ba[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->instruments_gv_ba[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->ratio_v_at_ba[i] = arbitrary(); }
  record->market = arbitrary();
  record->sector = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->instrument_number[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->indices[i] = arbitrary(); }
}

/* Depth At Best Prices Message to the wire: 25 bytes from at, returning where the next byte goes */
static size_t encode_depth_at_best_prices_message(const DepthAtBestPricesMessage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->origin;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->instruments_bb[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->instruments_gv_bb[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->ratio_v_at_bb[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->instruments_ba[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->instruments_gv_ba[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->ratio_v_at_ba[i]; }
  wire[at++] = record->market;
  wire[at++] = record->sector;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument_number[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->indices[i]; }

  return at;
}

/* Depth At Best Prices Message off the wire: 25 bytes from at, returning where the next byte lies */
static size_t decode_depth_at_best_prices_message(DepthAtBestPricesMessage *record, const uint8_t *wire, size_t at) {
  record->origin = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->instruments_bb[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->instruments_gv_bb[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->ratio_v_at_bb[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->instruments_ba[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->instruments_gv_ba[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->ratio_v_at_ba[i] = wire[at++]; }
  record->market = wire[at++];
  record->sector = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->instrument_number[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->indices[i] = wire[at++]; }

  return at;
}

/* what was read of Depth At Best Prices Message is what was written, byte for byte */
static void equal_depth_at_best_prices_message(const DepthAtBestPricesMessage *read, const DepthAtBestPricesMessage *written) {
  assert(read->origin == written->origin);
  for (size_t i = 0; i < 2; i++) { assert(read->instruments_bb[i] == written->instruments_bb[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->instruments_gv_bb[i] == written->instruments_gv_bb[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->ratio_v_at_bb[i] == written->ratio_v_at_bb[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->instruments_ba[i] == written->instruments_ba[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->instruments_gv_ba[i] == written->instruments_gv_ba[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->ratio_v_at_ba[i] == written->ratio_v_at_ba[i]); }
  assert(read->market == written->market);
  assert(read->sector == written->sector);
  for (size_t i = 0; i < 4; i++) { assert(read->instrument_number[i] == written->instrument_number[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->indices[i] == written->indices[i]); }
}

/* Depth At Best Prices Message: written and read back, then read and written back */
static void check_depth_at_best_prices_message(void) {
  DepthAtBestPricesMessage sent;
  DepthAtBestPricesMessage got;
  uint8_t wire[25];
  uint8_t again[25];

  any_depth_at_best_prices_message(&sent);
  assert(encode_depth_at_best_prices_message(&sent, wire, 0) == 25);
  assert(decode_depth_at_best_prices_message(&got, wire, 0) == 25);
  equal_depth_at_best_prices_message(&got, &sent);

  for (size_t i = 0; i < 25; i++) { wire[i] = arbitrary(); }
  assert(decode_depth_at_best_prices_message(&got, wire, 0) == 25);
  assert(encode_depth_at_best_prices_message(&got, again, 0) == 25);
  for (size_t i = 0; i < 25; i++) { assert(again[i] == wire[i]); }
}

/* ---- What esbmc checks ------------------------------------------------------- */

/* every record of the protocol, each on its own buffers */
static void checks(void) {
  check_i_n_t_r_a_multicast_header();
  check_message_header();
  check_last_quote_message();
  check_benchmark_trade_message();
  check_price_leaderboard_message();
  check_trading_sniper_message();
  check_depth_at_best_prices_message();
}

int main(void) {
#ifdef CONCRETE
  for (pattern = 0; pattern < 4; pattern++) { checks(); }
#else
  checks();
#endif

  return 0;
}
