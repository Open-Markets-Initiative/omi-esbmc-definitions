// bmv/bmvmarketdata/product32/BmvMarketData_Product32_v1_1.c
/*
 * Bolsa Mexicana de Valores Bmv Market Data Product 32
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

/* ---- Effective Spread Message: 33 bytes -------------------------------------- */

/* Transaction cost analysis benchmark. */
typedef struct {
  uint8_t origin;                  /* byte 0 */
  uint8_t es_mxn[4];               /* bytes 1 to 4 */
  uint8_t es_basis_points[4];      /* bytes 5 to 8 */
  uint8_t es_mxn_bid[4];           /* bytes 9 to 12 */
  uint8_t es_basis_points_bid[4];  /* bytes 13 to 16 */
  uint8_t es_mxn_ask[4];           /* bytes 17 to 20 */
  uint8_t es_basis_points_ask[4];  /* bytes 21 to 24 */
  uint8_t market;                  /* byte 25 */
  uint8_t sector;                  /* byte 26 */
  uint8_t instrument_number[4];    /* bytes 27 to 30 */
  uint8_t indices[2];              /* bytes 31 to 32 */
} EffectiveSpreadMessage;

/* any Effective Spread Message at all: every byte one the checker chooses */
static void any_effective_spread_message(EffectiveSpreadMessage *record) {
  record->origin = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->es_mxn[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->es_basis_points[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->es_mxn_bid[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->es_basis_points_bid[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->es_mxn_ask[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->es_basis_points_ask[i] = arbitrary(); }
  record->market = arbitrary();
  record->sector = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->instrument_number[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->indices[i] = arbitrary(); }
}

/* Effective Spread Message to the wire: 33 bytes from at, returning where the next byte goes */
static size_t encode_effective_spread_message(const EffectiveSpreadMessage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->origin;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->es_mxn[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->es_basis_points[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->es_mxn_bid[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->es_basis_points_bid[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->es_mxn_ask[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->es_basis_points_ask[i]; }
  wire[at++] = record->market;
  wire[at++] = record->sector;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument_number[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->indices[i]; }

  return at;
}

/* Effective Spread Message off the wire: 33 bytes from at, returning where the next byte lies */
static size_t decode_effective_spread_message(EffectiveSpreadMessage *record, const uint8_t *wire, size_t at) {
  record->origin = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->es_mxn[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->es_basis_points[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->es_mxn_bid[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->es_basis_points_bid[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->es_mxn_ask[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->es_basis_points_ask[i] = wire[at++]; }
  record->market = wire[at++];
  record->sector = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->instrument_number[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->indices[i] = wire[at++]; }

  return at;
}

/* what was read of Effective Spread Message is what was written, byte for byte */
static void equal_effective_spread_message(const EffectiveSpreadMessage *read, const EffectiveSpreadMessage *written) {
  assert(read->origin == written->origin);
  for (size_t i = 0; i < 4; i++) { assert(read->es_mxn[i] == written->es_mxn[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->es_basis_points[i] == written->es_basis_points[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->es_mxn_bid[i] == written->es_mxn_bid[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->es_basis_points_bid[i] == written->es_basis_points_bid[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->es_mxn_ask[i] == written->es_mxn_ask[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->es_basis_points_ask[i] == written->es_basis_points_ask[i]); }
  assert(read->market == written->market);
  assert(read->sector == written->sector);
  for (size_t i = 0; i < 4; i++) { assert(read->instrument_number[i] == written->instrument_number[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->indices[i] == written->indices[i]); }
}

/* Effective Spread Message: written and read back, then read and written back */
static void check_effective_spread_message(void) {
  EffectiveSpreadMessage sent;
  EffectiveSpreadMessage got;
  uint8_t wire[33];
  uint8_t again[33];

  any_effective_spread_message(&sent);
  assert(encode_effective_spread_message(&sent, wire, 0) == 33);
  assert(decode_effective_spread_message(&got, wire, 0) == 33);
  equal_effective_spread_message(&got, &sent);

  for (size_t i = 0; i < 33; i++) { wire[i] = arbitrary(); }
  assert(decode_effective_spread_message(&got, wire, 0) == 33);
  assert(encode_effective_spread_message(&got, again, 0) == 33);
  for (size_t i = 0; i < 33; i++) { assert(again[i] == wire[i]); }
}

/* ---- Spread Quality Message: 21 bytes ---------------------------------------- */

/* Quality of the quoted spread throughout the session. */
typedef struct {
  uint8_t origin;                       /* byte 0 */
  uint8_t time_best_spread[4];          /* bytes 1 to 4 */
  uint8_t time_tie_best_spread[4];      /* bytes 5 to 8 */
  uint8_t time_without_best_spread[4];  /* bytes 9 to 12 */
  uint8_t market;                       /* byte 13 */
  uint8_t sector;                       /* byte 14 */
  uint8_t instrument_number[4];         /* bytes 15 to 18 */
  uint8_t indices[2];                   /* bytes 19 to 20 */
} SpreadQualityMessage;

/* any Spread Quality Message at all: every byte one the checker chooses */
static void any_spread_quality_message(SpreadQualityMessage *record) {
  record->origin = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->time_best_spread[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->time_tie_best_spread[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->time_without_best_spread[i] = arbitrary(); }
  record->market = arbitrary();
  record->sector = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->instrument_number[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->indices[i] = arbitrary(); }
}

/* Spread Quality Message to the wire: 21 bytes from at, returning where the next byte goes */
static size_t encode_spread_quality_message(const SpreadQualityMessage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->origin;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->time_best_spread[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->time_tie_best_spread[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->time_without_best_spread[i]; }
  wire[at++] = record->market;
  wire[at++] = record->sector;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument_number[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->indices[i]; }

  return at;
}

/* Spread Quality Message off the wire: 21 bytes from at, returning where the next byte lies */
static size_t decode_spread_quality_message(SpreadQualityMessage *record, const uint8_t *wire, size_t at) {
  record->origin = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->time_best_spread[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->time_tie_best_spread[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->time_without_best_spread[i] = wire[at++]; }
  record->market = wire[at++];
  record->sector = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->instrument_number[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->indices[i] = wire[at++]; }

  return at;
}

/* what was read of Spread Quality Message is what was written, byte for byte */
static void equal_spread_quality_message(const SpreadQualityMessage *read, const SpreadQualityMessage *written) {
  assert(read->origin == written->origin);
  for (size_t i = 0; i < 4; i++) { assert(read->time_best_spread[i] == written->time_best_spread[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->time_tie_best_spread[i] == written->time_tie_best_spread[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->time_without_best_spread[i] == written->time_without_best_spread[i]); }
  assert(read->market == written->market);
  assert(read->sector == written->sector);
  for (size_t i = 0; i < 4; i++) { assert(read->instrument_number[i] == written->instrument_number[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->indices[i] == written->indices[i]); }
}

/* Spread Quality Message: written and read back, then read and written back */
static void check_spread_quality_message(void) {
  SpreadQualityMessage sent;
  SpreadQualityMessage got;
  uint8_t wire[21];
  uint8_t again[21];

  any_spread_quality_message(&sent);
  assert(encode_spread_quality_message(&sent, wire, 0) == 21);
  assert(decode_spread_quality_message(&got, wire, 0) == 21);
  equal_spread_quality_message(&got, &sent);

  for (size_t i = 0; i < 21; i++) { wire[i] = arbitrary(); }
  assert(decode_spread_quality_message(&got, wire, 0) == 21);
  assert(encode_spread_quality_message(&got, again, 0) == 21);
  for (size_t i = 0; i < 21; i++) { assert(again[i] == wire[i]); }
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

/* ---- Quotes Quality Message: 15 bytes ---------------------------------------- */

/* Time proportion in which an Exchange maintains quotes on both sides, bid and ask. */
typedef struct {
  uint8_t origin;                /* byte 0 */
  uint8_t instruments[2];        /* bytes 1 to 2 */
  uint8_t time[4];               /* bytes 3 to 6 */
  uint8_t market;                /* byte 7 */
  uint8_t sector;                /* byte 8 */
  uint8_t instrument_number[4];  /* bytes 9 to 12 */
  uint8_t indices[2];            /* bytes 13 to 14 */
} QuotesQualityMessage;

/* any Quotes Quality Message at all: every byte one the checker chooses */
static void any_quotes_quality_message(QuotesQualityMessage *record) {
  record->origin = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->instruments[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->time[i] = arbitrary(); }
  record->market = arbitrary();
  record->sector = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->instrument_number[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->indices[i] = arbitrary(); }
}

/* Quotes Quality Message to the wire: 15 bytes from at, returning where the next byte goes */
static size_t encode_quotes_quality_message(const QuotesQualityMessage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->origin;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->instruments[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->time[i]; }
  wire[at++] = record->market;
  wire[at++] = record->sector;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument_number[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->indices[i]; }

  return at;
}

/* Quotes Quality Message off the wire: 15 bytes from at, returning where the next byte lies */
static size_t decode_quotes_quality_message(QuotesQualityMessage *record, const uint8_t *wire, size_t at) {
  record->origin = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->instruments[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->time[i] = wire[at++]; }
  record->market = wire[at++];
  record->sector = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->instrument_number[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->indices[i] = wire[at++]; }

  return at;
}

/* what was read of Quotes Quality Message is what was written, byte for byte */
static void equal_quotes_quality_message(const QuotesQualityMessage *read, const QuotesQualityMessage *written) {
  assert(read->origin == written->origin);
  for (size_t i = 0; i < 2; i++) { assert(read->instruments[i] == written->instruments[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->time[i] == written->time[i]); }
  assert(read->market == written->market);
  assert(read->sector == written->sector);
  for (size_t i = 0; i < 4; i++) { assert(read->instrument_number[i] == written->instrument_number[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->indices[i] == written->indices[i]); }
}

/* Quotes Quality Message: written and read back, then read and written back */
static void check_quotes_quality_message(void) {
  QuotesQualityMessage sent;
  QuotesQualityMessage got;
  uint8_t wire[15];
  uint8_t again[15];

  any_quotes_quality_message(&sent);
  assert(encode_quotes_quality_message(&sent, wire, 0) == 15);
  assert(decode_quotes_quality_message(&got, wire, 0) == 15);
  equal_quotes_quality_message(&got, &sent);

  for (size_t i = 0; i < 15; i++) { wire[i] = arbitrary(); }
  assert(decode_quotes_quality_message(&got, wire, 0) == 15);
  assert(encode_quotes_quality_message(&got, again, 0) == 15);
  for (size_t i = 0; i < 15; i++) { assert(again[i] == wire[i]); }
}

/* ---- What esbmc checks ------------------------------------------------------- */

/* every record of the protocol, each on its own buffers */
static void checks(void) {
  check_i_n_t_r_a_multicast_header();
  check_message_header();
  check_effective_spread_message();
  check_spread_quality_message();
  check_price_leaderboard_message();
  check_quotes_quality_message();
}

int main(void) {
#ifdef CONCRETE
  for (pattern = 0; pattern < 4; pattern++) { checks(); }
#else
  checks();
#endif

  return 0;
}
