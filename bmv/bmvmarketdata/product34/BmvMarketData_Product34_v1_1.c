// bmv/bmvmarketdata/product34/BmvMarketData_Product34_v1_1.c
/*
 * Bolsa Mexicana de Valores Bmv Market Data Product 34
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

/* ---- Big Picture Message: 37 bytes ------------------------------------------- */

/* Market share summary of the stock exchanges. */
typedef struct {
  uint8_t origin;                  /* byte 0 */
  uint8_t trades[4];               /* bytes 1 to 4 */
  uint8_t volume[8];               /* bytes 5 to 12 */
  uint8_t traded_value[8];         /* bytes 13 to 20 */
  uint8_t market_share_amount[4];  /* bytes 21 to 24 */
  uint8_t market_share_trades[4];  /* bytes 25 to 28 */
  uint8_t market;                  /* byte 29 */
  uint8_t sector;                  /* byte 30 */
  uint8_t instrument_number[4];    /* bytes 31 to 34 */
  uint8_t indices[2];              /* bytes 35 to 36 */
} BigPictureMessage;

/* any Big Picture Message at all: every byte one the checker chooses */
static void any_big_picture_message(BigPictureMessage *record) {
  record->origin = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->trades[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->volume[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->traded_value[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->market_share_amount[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->market_share_trades[i] = arbitrary(); }
  record->market = arbitrary();
  record->sector = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->instrument_number[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->indices[i] = arbitrary(); }
}

/* Big Picture Message to the wire: 37 bytes from at, returning where the next byte goes */
static size_t encode_big_picture_message(const BigPictureMessage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->origin;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->trades[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->volume[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->traded_value[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->market_share_amount[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->market_share_trades[i]; }
  wire[at++] = record->market;
  wire[at++] = record->sector;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument_number[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->indices[i]; }

  return at;
}

/* Big Picture Message off the wire: 37 bytes from at, returning where the next byte lies */
static size_t decode_big_picture_message(BigPictureMessage *record, const uint8_t *wire, size_t at) {
  record->origin = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->trades[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->volume[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->traded_value[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->market_share_amount[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->market_share_trades[i] = wire[at++]; }
  record->market = wire[at++];
  record->sector = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->instrument_number[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->indices[i] = wire[at++]; }

  return at;
}

/* what was read of Big Picture Message is what was written, byte for byte */
static void equal_big_picture_message(const BigPictureMessage *read, const BigPictureMessage *written) {
  assert(read->origin == written->origin);
  for (size_t i = 0; i < 4; i++) { assert(read->trades[i] == written->trades[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->volume[i] == written->volume[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->traded_value[i] == written->traded_value[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->market_share_amount[i] == written->market_share_amount[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->market_share_trades[i] == written->market_share_trades[i]); }
  assert(read->market == written->market);
  assert(read->sector == written->sector);
  for (size_t i = 0; i < 4; i++) { assert(read->instrument_number[i] == written->instrument_number[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->indices[i] == written->indices[i]); }
}

/* Big Picture Message: written and read back, then read and written back */
static void check_big_picture_message(void) {
  BigPictureMessage sent;
  BigPictureMessage got;
  uint8_t wire[37];
  uint8_t again[37];

  any_big_picture_message(&sent);
  assert(encode_big_picture_message(&sent, wire, 0) == 37);
  assert(decode_big_picture_message(&got, wire, 0) == 37);
  equal_big_picture_message(&got, &sent);

  for (size_t i = 0; i < 37; i++) { wire[i] = arbitrary(); }
  assert(decode_big_picture_message(&got, wire, 0) == 37);
  assert(encode_big_picture_message(&got, again, 0) == 37);
  for (size_t i = 0; i < 37; i++) { assert(again[i] == wire[i]); }
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

/* ---- Hour Tracker Message: 53 bytes ------------------------------------------ */

/* Trading performance evolution per hour. */
typedef struct {
  uint8_t origin;                   /* byte 0 */
  uint8_t trades[4];                /* bytes 1 to 4 */
  uint8_t volume[8];                /* bytes 5 to 12 */
  uint8_t traded_value[8];          /* bytes 13 to 20 */
  uint8_t spread_mxn[4];            /* bytes 21 to 24 */
  uint8_t spread_basis_points[4];   /* bytes 25 to 28 */
  uint8_t average_volume[8];        /* bytes 29 to 36 */
  uint8_t average_traded_value[8];  /* bytes 37 to 44 */
  uint8_t market;                   /* byte 45 */
  uint8_t sector;                   /* byte 46 */
  uint8_t instrument_number[4];     /* bytes 47 to 50 */
  uint8_t indices[2];               /* bytes 51 to 52 */
} HourTrackerMessage;

/* any Hour Tracker Message at all: every byte one the checker chooses */
static void any_hour_tracker_message(HourTrackerMessage *record) {
  record->origin = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->trades[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->volume[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->traded_value[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->spread_mxn[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->spread_basis_points[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->average_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->average_traded_value[i] = arbitrary(); }
  record->market = arbitrary();
  record->sector = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->instrument_number[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->indices[i] = arbitrary(); }
}

/* Hour Tracker Message to the wire: 53 bytes from at, returning where the next byte goes */
static size_t encode_hour_tracker_message(const HourTrackerMessage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->origin;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->trades[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->volume[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->traded_value[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->spread_mxn[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->spread_basis_points[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->average_volume[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->average_traded_value[i]; }
  wire[at++] = record->market;
  wire[at++] = record->sector;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument_number[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->indices[i]; }

  return at;
}

/* Hour Tracker Message off the wire: 53 bytes from at, returning where the next byte lies */
static size_t decode_hour_tracker_message(HourTrackerMessage *record, const uint8_t *wire, size_t at) {
  record->origin = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->trades[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->volume[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->traded_value[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->spread_mxn[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->spread_basis_points[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->average_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->average_traded_value[i] = wire[at++]; }
  record->market = wire[at++];
  record->sector = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->instrument_number[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->indices[i] = wire[at++]; }

  return at;
}

/* what was read of Hour Tracker Message is what was written, byte for byte */
static void equal_hour_tracker_message(const HourTrackerMessage *read, const HourTrackerMessage *written) {
  assert(read->origin == written->origin);
  for (size_t i = 0; i < 4; i++) { assert(read->trades[i] == written->trades[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->volume[i] == written->volume[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->traded_value[i] == written->traded_value[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->spread_mxn[i] == written->spread_mxn[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->spread_basis_points[i] == written->spread_basis_points[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->average_volume[i] == written->average_volume[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->average_traded_value[i] == written->average_traded_value[i]); }
  assert(read->market == written->market);
  assert(read->sector == written->sector);
  for (size_t i = 0; i < 4; i++) { assert(read->instrument_number[i] == written->instrument_number[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->indices[i] == written->indices[i]); }
}

/* Hour Tracker Message: written and read back, then read and written back */
static void check_hour_tracker_message(void) {
  HourTrackerMessage sent;
  HourTrackerMessage got;
  uint8_t wire[53];
  uint8_t again[53];

  any_hour_tracker_message(&sent);
  assert(encode_hour_tracker_message(&sent, wire, 0) == 53);
  assert(decode_hour_tracker_message(&got, wire, 0) == 53);
  equal_hour_tracker_message(&got, &sent);

  for (size_t i = 0; i < 53; i++) { wire[i] = arbitrary(); }
  assert(decode_hour_tracker_message(&got, wire, 0) == 53);
  assert(encode_hour_tracker_message(&got, again, 0) == 53);
  for (size_t i = 0; i < 53; i++) { assert(again[i] == wire[i]); }
}

/* ---- Message Ratio Message: 37 bytes ----------------------------------------- */

/* Message to trade ratio conversion. */
typedef struct {
  uint8_t origin;                /* byte 0 */
  uint8_t messages[4];           /* bytes 1 to 4 */
  uint8_t messages_bid[4];       /* bytes 5 to 8 */
  uint8_t messages_ask[4];       /* bytes 9 to 12 */
  uint8_t messages_modified[4];  /* bytes 13 to 16 */
  uint8_t messages_canceled[4];  /* bytes 17 to 20 */
  uint8_t trades[4];             /* bytes 21 to 24 */
  uint8_t ratio[4];              /* bytes 25 to 28 */
  uint8_t market;                /* byte 29 */
  uint8_t sector;                /* byte 30 */
  uint8_t instrument_number[4];  /* bytes 31 to 34 */
  uint8_t indices[2];            /* bytes 35 to 36 */
} MessageRatioMessage;

/* any Message Ratio Message at all: every byte one the checker chooses */
static void any_message_ratio_message(MessageRatioMessage *record) {
  record->origin = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->messages[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->messages_bid[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->messages_ask[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->messages_modified[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->messages_canceled[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->trades[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->ratio[i] = arbitrary(); }
  record->market = arbitrary();
  record->sector = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->instrument_number[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->indices[i] = arbitrary(); }
}

/* Message Ratio Message to the wire: 37 bytes from at, returning where the next byte goes */
static size_t encode_message_ratio_message(const MessageRatioMessage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->origin;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->messages[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->messages_bid[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->messages_ask[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->messages_modified[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->messages_canceled[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->trades[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->ratio[i]; }
  wire[at++] = record->market;
  wire[at++] = record->sector;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument_number[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->indices[i]; }

  return at;
}

/* Message Ratio Message off the wire: 37 bytes from at, returning where the next byte lies */
static size_t decode_message_ratio_message(MessageRatioMessage *record, const uint8_t *wire, size_t at) {
  record->origin = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->messages[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->messages_bid[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->messages_ask[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->messages_modified[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->messages_canceled[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->trades[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->ratio[i] = wire[at++]; }
  record->market = wire[at++];
  record->sector = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->instrument_number[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->indices[i] = wire[at++]; }

  return at;
}

/* what was read of Message Ratio Message is what was written, byte for byte */
static void equal_message_ratio_message(const MessageRatioMessage *read, const MessageRatioMessage *written) {
  assert(read->origin == written->origin);
  for (size_t i = 0; i < 4; i++) { assert(read->messages[i] == written->messages[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->messages_bid[i] == written->messages_bid[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->messages_ask[i] == written->messages_ask[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->messages_modified[i] == written->messages_modified[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->messages_canceled[i] == written->messages_canceled[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->trades[i] == written->trades[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->ratio[i] == written->ratio[i]); }
  assert(read->market == written->market);
  assert(read->sector == written->sector);
  for (size_t i = 0; i < 4; i++) { assert(read->instrument_number[i] == written->instrument_number[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->indices[i] == written->indices[i]); }
}

/* Message Ratio Message: written and read back, then read and written back */
static void check_message_ratio_message(void) {
  MessageRatioMessage sent;
  MessageRatioMessage got;
  uint8_t wire[37];
  uint8_t again[37];

  any_message_ratio_message(&sent);
  assert(encode_message_ratio_message(&sent, wire, 0) == 37);
  assert(decode_message_ratio_message(&got, wire, 0) == 37);
  equal_message_ratio_message(&got, &sent);

  for (size_t i = 0; i < 37; i++) { wire[i] = arbitrary(); }
  assert(decode_message_ratio_message(&got, wire, 0) == 37);
  assert(encode_message_ratio_message(&got, again, 0) == 37);
  for (size_t i = 0; i < 37; i++) { assert(again[i] == wire[i]); }
}

/* ---- What esbmc checks ------------------------------------------------------- */

/* every record of the protocol, each on its own buffers */
static void checks(void) {
  check_i_n_t_r_a_multicast_header();
  check_message_header();
  check_big_picture_message();
  check_benchmark_trade_message();
  check_hour_tracker_message();
  check_message_ratio_message();
}

int main(void) {
#ifdef CONCRETE
  for (pattern = 0; pattern < 4; pattern++) { checks(); }
#else
  checks();
#endif

  return 0;
}
