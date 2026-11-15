// databento/normalized/Databento_MarketData_Normalized_v3_GatewayStream.c
/*
 * Databento Normalized
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
 *   - a length prefix framing what follows
 *   - a run counted by a field
 *   - a run filling what frames it
 *   - a field read in bits
 *   - a run of a stated number of entries
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

/* ---- Record Header: 16 bytes ------------------------------------------------- */

/* DBN common header of every record */
typedef struct {
  uint8_t record_length;     /* byte 0 */
  uint8_t rtype;             /* byte 1 */
  uint8_t publisher_id[2];   /* bytes 2 to 3 */
  uint8_t instrument_id[4];  /* bytes 4 to 7 */
  uint8_t ts_event[8];       /* bytes 8 to 15 */
} RecordHeader;

/* any Record Header at all: every byte one the checker chooses */
static void any_record_header(RecordHeader *record) {
  record->record_length = arbitrary();
  record->rtype = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->publisher_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->instrument_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->ts_event[i] = arbitrary(); }
}

/* Record Header to the wire: 16 bytes from at, returning where the next byte goes */
static size_t encode_record_header(const RecordHeader *record, uint8_t *wire, size_t at) {
  wire[at++] = record->record_length;
  wire[at++] = record->rtype;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->publisher_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->ts_event[i]; }

  return at;
}

/* Record Header off the wire: 16 bytes from at, returning where the next byte lies */
static size_t decode_record_header(RecordHeader *record, const uint8_t *wire, size_t at) {
  record->record_length = wire[at++];
  record->rtype = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->publisher_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->instrument_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->ts_event[i] = wire[at++]; }

  return at;
}

/* what was read of Record Header is what was written, byte for byte */
static void equal_record_header(const RecordHeader *read, const RecordHeader *written) {
  assert(read->record_length == written->record_length);
  assert(read->rtype == written->rtype);
  for (size_t i = 0; i < 2; i++) { assert(read->publisher_id[i] == written->publisher_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->instrument_id[i] == written->instrument_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->ts_event[i] == written->ts_event[i]); }
}

/* Record Header: written and read back, then read and written back */
static void check_record_header(void) {
  RecordHeader sent;
  RecordHeader got;
  uint8_t wire[16];
  uint8_t again[16];

  any_record_header(&sent);
  assert(encode_record_header(&sent, wire, 0) == 16);
  assert(decode_record_header(&got, wire, 0) == 16);
  equal_record_header(&got, &sent);

  for (size_t i = 0; i < 16; i++) { wire[i] = arbitrary(); }
  assert(decode_record_header(&got, wire, 0) == 16);
  assert(encode_record_header(&got, again, 0) == 16);
  for (size_t i = 0; i < 16; i++) { assert(again[i] == wire[i]); }
}

/* ---- Bid Ask Pair: 32 bytes -------------------------------------------------- */

/* A level */
typedef struct {
  uint8_t bid_px[8];  /* bytes 0 to 7 */
  uint8_t ask_px[8];  /* bytes 8 to 15 */
  uint8_t bid_sz[4];  /* bytes 16 to 19 */
  uint8_t ask_sz[4];  /* bytes 20 to 23 */
  uint8_t bid_ct[4];  /* bytes 24 to 27 */
  uint8_t ask_ct[4];  /* bytes 28 to 31 */
} BidAskPair;

/* any Bid Ask Pair at all: every byte one the checker chooses */
static void any_bid_ask_pair(BidAskPair *record) {
  for (size_t i = 0; i < 8; i++) { record->bid_px[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->ask_px[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->bid_sz[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->ask_sz[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->bid_ct[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->ask_ct[i] = arbitrary(); }
}

/* Bid Ask Pair to the wire: 32 bytes from at, returning where the next byte goes */
static size_t encode_bid_ask_pair(const BidAskPair *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->bid_px[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->ask_px[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->bid_sz[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->ask_sz[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->bid_ct[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->ask_ct[i]; }

  return at;
}

/* Bid Ask Pair off the wire: 32 bytes from at, returning where the next byte lies */
static size_t decode_bid_ask_pair(BidAskPair *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->bid_px[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->ask_px[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->bid_sz[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->ask_sz[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->bid_ct[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->ask_ct[i] = wire[at++]; }

  return at;
}

/* what was read of Bid Ask Pair is what was written, byte for byte */
static void equal_bid_ask_pair(const BidAskPair *read, const BidAskPair *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->bid_px[i] == written->bid_px[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->ask_px[i] == written->ask_px[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->bid_sz[i] == written->bid_sz[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->ask_sz[i] == written->ask_sz[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->bid_ct[i] == written->bid_ct[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->ask_ct[i] == written->ask_ct[i]); }
}

/* Bid Ask Pair: written and read back, then read and written back */
static void check_bid_ask_pair(void) {
  BidAskPair sent;
  BidAskPair got;
  uint8_t wire[32];
  uint8_t again[32];

  any_bid_ask_pair(&sent);
  assert(encode_bid_ask_pair(&sent, wire, 0) == 32);
  assert(decode_bid_ask_pair(&got, wire, 0) == 32);
  equal_bid_ask_pair(&got, &sent);

  for (size_t i = 0; i < 32; i++) { wire[i] = arbitrary(); }
  assert(decode_bid_ask_pair(&got, wire, 0) == 32);
  assert(encode_bid_ask_pair(&got, again, 0) == 32);
  for (size_t i = 0; i < 32; i++) { assert(again[i] == wire[i]); }
}

/* ---- Ohlcv Msg: 40 bytes ----------------------------------------------------- */

/* Open, high, low, close, and volume; the record of the ohlcv schemas */
typedef struct {
  uint8_t open[8];    /* bytes 0 to 7 */
  uint8_t high[8];    /* bytes 8 to 15 */
  uint8_t low[8];     /* bytes 16 to 23 */
  uint8_t close[8];   /* bytes 24 to 31 */
  uint8_t volume[8];  /* bytes 32 to 39 */
} OhlcvMsg;

/* any Ohlcv Msg at all: every byte one the checker chooses */
static void any_ohlcv_msg(OhlcvMsg *record) {
  for (size_t i = 0; i < 8; i++) { record->open[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->high[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->low[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->close[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->volume[i] = arbitrary(); }
}

/* Ohlcv Msg to the wire: 40 bytes from at, returning where the next byte goes */
static size_t encode_ohlcv_msg(const OhlcvMsg *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->open[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->high[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->low[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->close[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->volume[i]; }

  return at;
}

/* Ohlcv Msg off the wire: 40 bytes from at, returning where the next byte lies */
static size_t decode_ohlcv_msg(OhlcvMsg *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->open[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->high[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->low[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->close[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->volume[i] = wire[at++]; }

  return at;
}

/* what was read of Ohlcv Msg is what was written, byte for byte */
static void equal_ohlcv_msg(const OhlcvMsg *read, const OhlcvMsg *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->open[i] == written->open[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->high[i] == written->high[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->low[i] == written->low[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->close[i] == written->close[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->volume[i] == written->volume[i]); }
}

/* Ohlcv Msg: written and read back, then read and written back */
static void check_ohlcv_msg(void) {
  OhlcvMsg sent;
  OhlcvMsg got;
  uint8_t wire[40];
  uint8_t again[40];

  any_ohlcv_msg(&sent);
  assert(encode_ohlcv_msg(&sent, wire, 0) == 40);
  assert(decode_ohlcv_msg(&got, wire, 0) == 40);
  equal_ohlcv_msg(&got, &sent);

  for (size_t i = 0; i < 40; i++) { wire[i] = arbitrary(); }
  assert(decode_ohlcv_msg(&got, wire, 0) == 40);
  assert(encode_ohlcv_msg(&got, again, 0) == 40);
  for (size_t i = 0; i < 40; i++) { assert(again[i] == wire[i]); }
}

/* ---- Status Msg: 24 bytes ---------------------------------------------------- */

/* A trading status update message; the record of the status schema */
typedef struct {
  uint8_t ts_recv[8];                /* bytes 0 to 7 */
  uint8_t status_action[2];          /* bytes 8 to 9 */
  uint8_t status_reason[2];          /* bytes 10 to 11 */
  uint8_t trading_event[2];          /* bytes 12 to 13 */
  uint8_t is_trading;                /* byte 14 */
  uint8_t is_quoting;                /* byte 15 */
  uint8_t is_short_sell_restricted;  /* byte 16 */
  uint8_t reserved_7[7];             /* bytes 17 to 23 */
} StatusMsg;

/* any Status Msg at all: every byte one the checker chooses */
static void any_status_msg(StatusMsg *record) {
  for (size_t i = 0; i < 8; i++) { record->ts_recv[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->status_action[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->status_reason[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->trading_event[i] = arbitrary(); }
  record->is_trading = arbitrary();
  record->is_quoting = arbitrary();
  record->is_short_sell_restricted = arbitrary();
  for (size_t i = 0; i < 7; i++) { record->reserved_7[i] = arbitrary(); }
}

/* Status Msg to the wire: 24 bytes from at, returning where the next byte goes */
static size_t encode_status_msg(const StatusMsg *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->ts_recv[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->status_action[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->status_reason[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->trading_event[i]; }
  wire[at++] = record->is_trading;
  wire[at++] = record->is_quoting;
  wire[at++] = record->is_short_sell_restricted;
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->reserved_7[i]; }

  return at;
}

/* Status Msg off the wire: 24 bytes from at, returning where the next byte lies */
static size_t decode_status_msg(StatusMsg *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->ts_recv[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->status_action[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->status_reason[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->trading_event[i] = wire[at++]; }
  record->is_trading = wire[at++];
  record->is_quoting = wire[at++];
  record->is_short_sell_restricted = wire[at++];
  for (size_t i = 0; i < 7; i++) { record->reserved_7[i] = wire[at++]; }

  return at;
}

/* what was read of Status Msg is what was written, byte for byte */
static void equal_status_msg(const StatusMsg *read, const StatusMsg *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->ts_recv[i] == written->ts_recv[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->status_action[i] == written->status_action[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->status_reason[i] == written->status_reason[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->trading_event[i] == written->trading_event[i]); }
  assert(read->is_trading == written->is_trading);
  assert(read->is_quoting == written->is_quoting);
  assert(read->is_short_sell_restricted == written->is_short_sell_restricted);
  for (size_t i = 0; i < 7; i++) { assert(read->reserved_7[i] == written->reserved_7[i]); }
}

/* Status Msg: written and read back, then read and written back */
static void check_status_msg(void) {
  StatusMsg sent;
  StatusMsg got;
  uint8_t wire[24];
  uint8_t again[24];

  any_status_msg(&sent);
  assert(encode_status_msg(&sent, wire, 0) == 24);
  assert(decode_status_msg(&got, wire, 0) == 24);
  equal_status_msg(&got, &sent);

  for (size_t i = 0; i < 24; i++) { wire[i] = arbitrary(); }
  assert(decode_status_msg(&got, wire, 0) == 24);
  assert(encode_status_msg(&got, again, 0) == 24);
  for (size_t i = 0; i < 24; i++) { assert(again[i] == wire[i]); }
}

/* ---- Instrument Def Msg: 504 bytes ------------------------------------------- */

/* A definition of an instrument; the record of the definition schema */
typedef struct {
  uint8_t ts_recv[8];                      /* bytes 0 to 7 */
  uint8_t min_price_increment[8];          /* bytes 8 to 15 */
  uint8_t display_factor[8];               /* bytes 16 to 23 */
  uint8_t expiration[8];                   /* bytes 24 to 31 */
  uint8_t activation[8];                   /* bytes 32 to 39 */
  uint8_t high_limit_price[8];             /* bytes 40 to 47 */
  uint8_t low_limit_price[8];              /* bytes 48 to 55 */
  uint8_t max_price_variation[8];          /* bytes 56 to 63 */
  uint8_t unit_of_measure_qty[8];          /* bytes 64 to 71 */
  uint8_t min_price_increment_amount[8];   /* bytes 72 to 79 */
  uint8_t price_ratio[8];                  /* bytes 80 to 87 */
  uint8_t strike_price[8];                 /* bytes 88 to 95 */
  uint8_t raw_instrument_id[8];            /* bytes 96 to 103 */
  uint8_t leg_price[8];                    /* bytes 104 to 111 */
  uint8_t leg_delta[8];                    /* bytes 112 to 119 */
  uint8_t inst_attrib_value[4];            /* bytes 120 to 123 */
  uint8_t underlying_id[4];                /* bytes 124 to 127 */
  uint8_t market_depth_implied[4];         /* bytes 128 to 131 */
  uint8_t market_depth[4];                 /* bytes 132 to 135 */
  uint8_t market_segment_id[4];            /* bytes 136 to 139 */
  uint8_t max_trade_vol[4];                /* bytes 140 to 143 */
  uint8_t min_lot_size[4];                 /* bytes 144 to 147 */
  uint8_t min_lot_size_block[4];           /* bytes 148 to 151 */
  uint8_t min_lot_size_round_lot[4];       /* bytes 152 to 155 */
  uint8_t min_trade_vol[4];                /* bytes 156 to 159 */
  uint8_t contract_multiplier[4];          /* bytes 160 to 163 */
  uint8_t decay_quantity[4];               /* bytes 164 to 167 */
  uint8_t original_contract_size[4];       /* bytes 168 to 171 */
  uint8_t leg_instrument_id[4];            /* bytes 172 to 175 */
  uint8_t leg_ratio_price_numerator[4];    /* bytes 176 to 179 */
  uint8_t leg_ratio_price_denominator[4];  /* bytes 180 to 183 */
  uint8_t leg_ratio_qty_numerator[4];      /* bytes 184 to 187 */
  uint8_t leg_ratio_qty_denominator[4];    /* bytes 188 to 191 */
  uint8_t leg_underlying_id[4];            /* bytes 192 to 195 */
  uint8_t appl_id[2];                      /* bytes 196 to 197 */
  uint8_t maturity_year[2];                /* bytes 198 to 199 */
  uint8_t decay_start_date[2];             /* bytes 200 to 201 */
  uint8_t channel[2];                      /* bytes 202 to 203 */
  uint8_t leg_count[2];                    /* bytes 204 to 205 */
  uint8_t leg_index[2];                    /* bytes 206 to 207 */
  uint8_t currency[4];                     /* bytes 208 to 211 */
  uint8_t settl_currency[4];               /* bytes 212 to 215 */
  uint8_t secsubtype[6];                   /* bytes 216 to 221 */
  uint8_t raw_symbol[71];                  /* bytes 222 to 292 */
  uint8_t group[21];                       /* bytes 293 to 313 */
  uint8_t exchange[5];                     /* bytes 314 to 318 */
  uint8_t asset[11];                       /* bytes 319 to 329 */
  uint8_t cfi[7];                          /* bytes 330 to 336 */
  uint8_t security_type[7];                /* bytes 337 to 343 */
  uint8_t unit_of_measure[31];             /* bytes 344 to 374 */
  uint8_t underlying[21];                  /* bytes 375 to 395 */
  uint8_t strike_price_currency[4];        /* bytes 396 to 399 */
  uint8_t leg_raw_symbol[71];              /* bytes 400 to 470 */
  uint8_t instrument_class;                /* byte 471 */
  uint8_t match_algorithm;                 /* byte 472 */
  uint8_t main_fraction;                   /* byte 473 */
  uint8_t price_display_format;            /* byte 474 */
  uint8_t sub_fraction;                    /* byte 475 */
  uint8_t underlying_product;              /* byte 476 */
  uint8_t security_update_action;          /* byte 477 */
  uint8_t maturity_month;                  /* byte 478 */
  uint8_t maturity_day;                    /* byte 479 */
  uint8_t maturity_week;                   /* byte 480 */
  uint8_t user_defined_instrument;         /* byte 481 */
  uint8_t contract_multiplier_unit;        /* byte 482 */
  uint8_t flow_schedule_type;              /* byte 483 */
  uint8_t tick_rule;                       /* byte 484 */
  uint8_t leg_instrument_class;            /* byte 485 */
  uint8_t leg_side;                        /* byte 486 */
  uint8_t reserved_17[17];                 /* bytes 487 to 503 */
} InstrumentDefMsg;

/* any Instrument Def Msg at all: every byte one the checker chooses */
static void any_instrument_def_msg(InstrumentDefMsg *record) {
  for (size_t i = 0; i < 8; i++) { record->ts_recv[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->min_price_increment[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->display_factor[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->expiration[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->activation[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->high_limit_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->low_limit_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->max_price_variation[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->unit_of_measure_qty[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->min_price_increment_amount[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->price_ratio[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->strike_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->raw_instrument_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->leg_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->leg_delta[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->inst_attrib_value[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->underlying_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->market_depth_implied[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->market_depth[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->market_segment_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->max_trade_vol[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->min_lot_size[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->min_lot_size_block[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->min_lot_size_round_lot[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->min_trade_vol[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->contract_multiplier[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->decay_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->original_contract_size[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->leg_instrument_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->leg_ratio_price_numerator[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->leg_ratio_price_denominator[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->leg_ratio_qty_numerator[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->leg_ratio_qty_denominator[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->leg_underlying_id[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->appl_id[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->maturity_year[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->decay_start_date[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->channel[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->leg_count[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->leg_index[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->currency[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->settl_currency[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->secsubtype[i] = arbitrary(); }
  for (size_t i = 0; i < 71; i++) { record->raw_symbol[i] = arbitrary(); }
  for (size_t i = 0; i < 21; i++) { record->group[i] = arbitrary(); }
  for (size_t i = 0; i < 5; i++) { record->exchange[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->asset[i] = arbitrary(); }
  for (size_t i = 0; i < 7; i++) { record->cfi[i] = arbitrary(); }
  for (size_t i = 0; i < 7; i++) { record->security_type[i] = arbitrary(); }
  for (size_t i = 0; i < 31; i++) { record->unit_of_measure[i] = arbitrary(); }
  for (size_t i = 0; i < 21; i++) { record->underlying[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->strike_price_currency[i] = arbitrary(); }
  for (size_t i = 0; i < 71; i++) { record->leg_raw_symbol[i] = arbitrary(); }
  record->instrument_class = arbitrary();
  record->match_algorithm = arbitrary();
  record->main_fraction = arbitrary();
  record->price_display_format = arbitrary();
  record->sub_fraction = arbitrary();
  record->underlying_product = arbitrary();
  record->security_update_action = arbitrary();
  record->maturity_month = arbitrary();
  record->maturity_day = arbitrary();
  record->maturity_week = arbitrary();
  record->user_defined_instrument = arbitrary();
  record->contract_multiplier_unit = arbitrary();
  record->flow_schedule_type = arbitrary();
  record->tick_rule = arbitrary();
  record->leg_instrument_class = arbitrary();
  record->leg_side = arbitrary();
  for (size_t i = 0; i < 17; i++) { record->reserved_17[i] = arbitrary(); }
}

/* Instrument Def Msg to the wire: 504 bytes from at, returning where the next byte goes */
static size_t encode_instrument_def_msg(const InstrumentDefMsg *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->ts_recv[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->min_price_increment[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->display_factor[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->expiration[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->activation[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->high_limit_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->low_limit_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->max_price_variation[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->unit_of_measure_qty[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->min_price_increment_amount[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price_ratio[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->strike_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->raw_instrument_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->leg_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->leg_delta[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->inst_attrib_value[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->underlying_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->market_depth_implied[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->market_depth[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->market_segment_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->max_trade_vol[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->min_lot_size[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->min_lot_size_block[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->min_lot_size_round_lot[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->min_trade_vol[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->contract_multiplier[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->decay_quantity[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->original_contract_size[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->leg_instrument_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->leg_ratio_price_numerator[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->leg_ratio_price_denominator[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->leg_ratio_qty_numerator[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->leg_ratio_qty_denominator[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->leg_underlying_id[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->appl_id[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->maturity_year[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->decay_start_date[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->channel[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->leg_count[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->leg_index[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->currency[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->settl_currency[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->secsubtype[i]; }
  for (size_t i = 0; i < 71; i++) { wire[at++] = record->raw_symbol[i]; }
  for (size_t i = 0; i < 21; i++) { wire[at++] = record->group[i]; }
  for (size_t i = 0; i < 5; i++) { wire[at++] = record->exchange[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->asset[i]; }
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->cfi[i]; }
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->security_type[i]; }
  for (size_t i = 0; i < 31; i++) { wire[at++] = record->unit_of_measure[i]; }
  for (size_t i = 0; i < 21; i++) { wire[at++] = record->underlying[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->strike_price_currency[i]; }
  for (size_t i = 0; i < 71; i++) { wire[at++] = record->leg_raw_symbol[i]; }
  wire[at++] = record->instrument_class;
  wire[at++] = record->match_algorithm;
  wire[at++] = record->main_fraction;
  wire[at++] = record->price_display_format;
  wire[at++] = record->sub_fraction;
  wire[at++] = record->underlying_product;
  wire[at++] = record->security_update_action;
  wire[at++] = record->maturity_month;
  wire[at++] = record->maturity_day;
  wire[at++] = record->maturity_week;
  wire[at++] = record->user_defined_instrument;
  wire[at++] = record->contract_multiplier_unit;
  wire[at++] = record->flow_schedule_type;
  wire[at++] = record->tick_rule;
  wire[at++] = record->leg_instrument_class;
  wire[at++] = record->leg_side;
  for (size_t i = 0; i < 17; i++) { wire[at++] = record->reserved_17[i]; }

  return at;
}

/* Instrument Def Msg off the wire: 504 bytes from at, returning where the next byte lies */
static size_t decode_instrument_def_msg(InstrumentDefMsg *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->ts_recv[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->min_price_increment[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->display_factor[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->expiration[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->activation[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->high_limit_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->low_limit_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->max_price_variation[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->unit_of_measure_qty[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->min_price_increment_amount[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->price_ratio[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->strike_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->raw_instrument_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->leg_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->leg_delta[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->inst_attrib_value[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->underlying_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->market_depth_implied[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->market_depth[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->market_segment_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->max_trade_vol[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->min_lot_size[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->min_lot_size_block[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->min_lot_size_round_lot[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->min_trade_vol[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->contract_multiplier[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->decay_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->original_contract_size[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->leg_instrument_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->leg_ratio_price_numerator[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->leg_ratio_price_denominator[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->leg_ratio_qty_numerator[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->leg_ratio_qty_denominator[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->leg_underlying_id[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->appl_id[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->maturity_year[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->decay_start_date[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->channel[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->leg_count[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->leg_index[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->currency[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->settl_currency[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->secsubtype[i] = wire[at++]; }
  for (size_t i = 0; i < 71; i++) { record->raw_symbol[i] = wire[at++]; }
  for (size_t i = 0; i < 21; i++) { record->group[i] = wire[at++]; }
  for (size_t i = 0; i < 5; i++) { record->exchange[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->asset[i] = wire[at++]; }
  for (size_t i = 0; i < 7; i++) { record->cfi[i] = wire[at++]; }
  for (size_t i = 0; i < 7; i++) { record->security_type[i] = wire[at++]; }
  for (size_t i = 0; i < 31; i++) { record->unit_of_measure[i] = wire[at++]; }
  for (size_t i = 0; i < 21; i++) { record->underlying[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->strike_price_currency[i] = wire[at++]; }
  for (size_t i = 0; i < 71; i++) { record->leg_raw_symbol[i] = wire[at++]; }
  record->instrument_class = wire[at++];
  record->match_algorithm = wire[at++];
  record->main_fraction = wire[at++];
  record->price_display_format = wire[at++];
  record->sub_fraction = wire[at++];
  record->underlying_product = wire[at++];
  record->security_update_action = wire[at++];
  record->maturity_month = wire[at++];
  record->maturity_day = wire[at++];
  record->maturity_week = wire[at++];
  record->user_defined_instrument = wire[at++];
  record->contract_multiplier_unit = wire[at++];
  record->flow_schedule_type = wire[at++];
  record->tick_rule = wire[at++];
  record->leg_instrument_class = wire[at++];
  record->leg_side = wire[at++];
  for (size_t i = 0; i < 17; i++) { record->reserved_17[i] = wire[at++]; }

  return at;
}

/* what was read of Instrument Def Msg is what was written, byte for byte */
static void equal_instrument_def_msg(const InstrumentDefMsg *read, const InstrumentDefMsg *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->ts_recv[i] == written->ts_recv[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->min_price_increment[i] == written->min_price_increment[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->display_factor[i] == written->display_factor[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->expiration[i] == written->expiration[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->activation[i] == written->activation[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->high_limit_price[i] == written->high_limit_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->low_limit_price[i] == written->low_limit_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->max_price_variation[i] == written->max_price_variation[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->unit_of_measure_qty[i] == written->unit_of_measure_qty[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->min_price_increment_amount[i] == written->min_price_increment_amount[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->price_ratio[i] == written->price_ratio[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->strike_price[i] == written->strike_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->raw_instrument_id[i] == written->raw_instrument_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->leg_price[i] == written->leg_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->leg_delta[i] == written->leg_delta[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->inst_attrib_value[i] == written->inst_attrib_value[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->underlying_id[i] == written->underlying_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->market_depth_implied[i] == written->market_depth_implied[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->market_depth[i] == written->market_depth[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->market_segment_id[i] == written->market_segment_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->max_trade_vol[i] == written->max_trade_vol[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->min_lot_size[i] == written->min_lot_size[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->min_lot_size_block[i] == written->min_lot_size_block[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->min_lot_size_round_lot[i] == written->min_lot_size_round_lot[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->min_trade_vol[i] == written->min_trade_vol[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->contract_multiplier[i] == written->contract_multiplier[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->decay_quantity[i] == written->decay_quantity[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->original_contract_size[i] == written->original_contract_size[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->leg_instrument_id[i] == written->leg_instrument_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->leg_ratio_price_numerator[i] == written->leg_ratio_price_numerator[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->leg_ratio_price_denominator[i] == written->leg_ratio_price_denominator[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->leg_ratio_qty_numerator[i] == written->leg_ratio_qty_numerator[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->leg_ratio_qty_denominator[i] == written->leg_ratio_qty_denominator[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->leg_underlying_id[i] == written->leg_underlying_id[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->appl_id[i] == written->appl_id[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->maturity_year[i] == written->maturity_year[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->decay_start_date[i] == written->decay_start_date[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->channel[i] == written->channel[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->leg_count[i] == written->leg_count[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->leg_index[i] == written->leg_index[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->currency[i] == written->currency[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->settl_currency[i] == written->settl_currency[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->secsubtype[i] == written->secsubtype[i]); }
  for (size_t i = 0; i < 71; i++) { assert(read->raw_symbol[i] == written->raw_symbol[i]); }
  for (size_t i = 0; i < 21; i++) { assert(read->group[i] == written->group[i]); }
  for (size_t i = 0; i < 5; i++) { assert(read->exchange[i] == written->exchange[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->asset[i] == written->asset[i]); }
  for (size_t i = 0; i < 7; i++) { assert(read->cfi[i] == written->cfi[i]); }
  for (size_t i = 0; i < 7; i++) { assert(read->security_type[i] == written->security_type[i]); }
  for (size_t i = 0; i < 31; i++) { assert(read->unit_of_measure[i] == written->unit_of_measure[i]); }
  for (size_t i = 0; i < 21; i++) { assert(read->underlying[i] == written->underlying[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->strike_price_currency[i] == written->strike_price_currency[i]); }
  for (size_t i = 0; i < 71; i++) { assert(read->leg_raw_symbol[i] == written->leg_raw_symbol[i]); }
  assert(read->instrument_class == written->instrument_class);
  assert(read->match_algorithm == written->match_algorithm);
  assert(read->main_fraction == written->main_fraction);
  assert(read->price_display_format == written->price_display_format);
  assert(read->sub_fraction == written->sub_fraction);
  assert(read->underlying_product == written->underlying_product);
  assert(read->security_update_action == written->security_update_action);
  assert(read->maturity_month == written->maturity_month);
  assert(read->maturity_day == written->maturity_day);
  assert(read->maturity_week == written->maturity_week);
  assert(read->user_defined_instrument == written->user_defined_instrument);
  assert(read->contract_multiplier_unit == written->contract_multiplier_unit);
  assert(read->flow_schedule_type == written->flow_schedule_type);
  assert(read->tick_rule == written->tick_rule);
  assert(read->leg_instrument_class == written->leg_instrument_class);
  assert(read->leg_side == written->leg_side);
  for (size_t i = 0; i < 17; i++) { assert(read->reserved_17[i] == written->reserved_17[i]); }
}

/* Instrument Def Msg: written and read back, then read and written back */
static void check_instrument_def_msg(void) {
  InstrumentDefMsg sent;
  InstrumentDefMsg got;
  uint8_t wire[504];
  uint8_t again[504];

  any_instrument_def_msg(&sent);
  assert(encode_instrument_def_msg(&sent, wire, 0) == 504);
  assert(decode_instrument_def_msg(&got, wire, 0) == 504);
  equal_instrument_def_msg(&got, &sent);

  for (size_t i = 0; i < 504; i++) { wire[i] = arbitrary(); }
  assert(decode_instrument_def_msg(&got, wire, 0) == 504);
  assert(encode_instrument_def_msg(&got, again, 0) == 504);
  for (size_t i = 0; i < 504; i++) { assert(again[i] == wire[i]); }
}

/* ---- Imbalance Msg: 96 bytes ------------------------------------------------- */

/* An auction imbalance message; the record of the imbalance schema */
typedef struct {
  uint8_t ts_recv[8];                  /* bytes 0 to 7 */
  uint8_t ref_price[8];                /* bytes 8 to 15 */
  uint8_t auction_time[8];             /* bytes 16 to 23 */
  uint8_t cont_book_clr_price[8];      /* bytes 24 to 31 */
  uint8_t auct_interest_clr_price[8];  /* bytes 32 to 39 */
  uint8_t ssr_filling_price[8];        /* bytes 40 to 47 */
  uint8_t ind_match_price[8];          /* bytes 48 to 55 */
  uint8_t upper_collar[8];             /* bytes 56 to 63 */
  uint8_t lower_collar[8];             /* bytes 64 to 71 */
  uint8_t paired_qty[4];               /* bytes 72 to 75 */
  uint8_t total_imbalance_qty[4];      /* bytes 76 to 79 */
  uint8_t market_imbalance_qty[4];     /* bytes 80 to 83 */
  uint8_t unpaired_qty[4];             /* bytes 84 to 87 */
  uint8_t auction_type;                /* byte 88 */
  uint8_t side;                        /* byte 89 */
  uint8_t auction_status;              /* byte 90 */
  uint8_t freeze_status;               /* byte 91 */
  uint8_t num_extensions;              /* byte 92 */
  uint8_t unpaired_side;               /* byte 93 */
  uint8_t significant_imbalance;       /* byte 94 */
  uint8_t reserved_1;                  /* byte 95 */
} ImbalanceMsg;

/* any Imbalance Msg at all: every byte one the checker chooses */
static void any_imbalance_msg(ImbalanceMsg *record) {
  for (size_t i = 0; i < 8; i++) { record->ts_recv[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->ref_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->auction_time[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->cont_book_clr_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->auct_interest_clr_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->ssr_filling_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->ind_match_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->upper_collar[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->lower_collar[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->paired_qty[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->total_imbalance_qty[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->market_imbalance_qty[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->unpaired_qty[i] = arbitrary(); }
  record->auction_type = arbitrary();
  record->side = arbitrary();
  record->auction_status = arbitrary();
  record->freeze_status = arbitrary();
  record->num_extensions = arbitrary();
  record->unpaired_side = arbitrary();
  record->significant_imbalance = arbitrary();
  record->reserved_1 = arbitrary();
}

/* Imbalance Msg to the wire: 96 bytes from at, returning where the next byte goes */
static size_t encode_imbalance_msg(const ImbalanceMsg *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->ts_recv[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->ref_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->auction_time[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->cont_book_clr_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->auct_interest_clr_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->ssr_filling_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->ind_match_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->upper_collar[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->lower_collar[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->paired_qty[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->total_imbalance_qty[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->market_imbalance_qty[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->unpaired_qty[i]; }
  wire[at++] = record->auction_type;
  wire[at++] = record->side;
  wire[at++] = record->auction_status;
  wire[at++] = record->freeze_status;
  wire[at++] = record->num_extensions;
  wire[at++] = record->unpaired_side;
  wire[at++] = record->significant_imbalance;
  wire[at++] = record->reserved_1;

  return at;
}

/* Imbalance Msg off the wire: 96 bytes from at, returning where the next byte lies */
static size_t decode_imbalance_msg(ImbalanceMsg *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->ts_recv[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->ref_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->auction_time[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->cont_book_clr_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->auct_interest_clr_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->ssr_filling_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->ind_match_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->upper_collar[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->lower_collar[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->paired_qty[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->total_imbalance_qty[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->market_imbalance_qty[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->unpaired_qty[i] = wire[at++]; }
  record->auction_type = wire[at++];
  record->side = wire[at++];
  record->auction_status = wire[at++];
  record->freeze_status = wire[at++];
  record->num_extensions = wire[at++];
  record->unpaired_side = wire[at++];
  record->significant_imbalance = wire[at++];
  record->reserved_1 = wire[at++];

  return at;
}

/* what was read of Imbalance Msg is what was written, byte for byte */
static void equal_imbalance_msg(const ImbalanceMsg *read, const ImbalanceMsg *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->ts_recv[i] == written->ts_recv[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->ref_price[i] == written->ref_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->auction_time[i] == written->auction_time[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->cont_book_clr_price[i] == written->cont_book_clr_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->auct_interest_clr_price[i] == written->auct_interest_clr_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->ssr_filling_price[i] == written->ssr_filling_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->ind_match_price[i] == written->ind_match_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->upper_collar[i] == written->upper_collar[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->lower_collar[i] == written->lower_collar[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->paired_qty[i] == written->paired_qty[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->total_imbalance_qty[i] == written->total_imbalance_qty[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->market_imbalance_qty[i] == written->market_imbalance_qty[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->unpaired_qty[i] == written->unpaired_qty[i]); }
  assert(read->auction_type == written->auction_type);
  assert(read->side == written->side);
  assert(read->auction_status == written->auction_status);
  assert(read->freeze_status == written->freeze_status);
  assert(read->num_extensions == written->num_extensions);
  assert(read->unpaired_side == written->unpaired_side);
  assert(read->significant_imbalance == written->significant_imbalance);
  assert(read->reserved_1 == written->reserved_1);
}

/* Imbalance Msg: written and read back, then read and written back */
static void check_imbalance_msg(void) {
  ImbalanceMsg sent;
  ImbalanceMsg got;
  uint8_t wire[96];
  uint8_t again[96];

  any_imbalance_msg(&sent);
  assert(encode_imbalance_msg(&sent, wire, 0) == 96);
  assert(decode_imbalance_msg(&got, wire, 0) == 96);
  equal_imbalance_msg(&got, &sent);

  for (size_t i = 0; i < 96; i++) { wire[i] = arbitrary(); }
  assert(decode_imbalance_msg(&got, wire, 0) == 96);
  assert(encode_imbalance_msg(&got, again, 0) == 96);
  for (size_t i = 0; i < 96; i++) { assert(again[i] == wire[i]); }
}

/* ---- Error Msg: 304 bytes ---------------------------------------------------- */

/* An error message from the Databento Live Subscription Gateway (LSG) */
typedef struct {
  uint8_t err[302];    /* bytes 0 to 301 */
  uint8_t error_code;  /* byte 302 */
  uint8_t is_last;     /* byte 303 */
} ErrorMsg;

/* any Error Msg at all: every byte one the checker chooses */
static void any_error_msg(ErrorMsg *record) {
  for (size_t i = 0; i < 302; i++) { record->err[i] = arbitrary(); }
  record->error_code = arbitrary();
  record->is_last = arbitrary();
}

/* Error Msg to the wire: 304 bytes from at, returning where the next byte goes */
static size_t encode_error_msg(const ErrorMsg *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 302; i++) { wire[at++] = record->err[i]; }
  wire[at++] = record->error_code;
  wire[at++] = record->is_last;

  return at;
}

/* Error Msg off the wire: 304 bytes from at, returning where the next byte lies */
static size_t decode_error_msg(ErrorMsg *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 302; i++) { record->err[i] = wire[at++]; }
  record->error_code = wire[at++];
  record->is_last = wire[at++];

  return at;
}

/* what was read of Error Msg is what was written, byte for byte */
static void equal_error_msg(const ErrorMsg *read, const ErrorMsg *written) {
  for (size_t i = 0; i < 302; i++) { assert(read->err[i] == written->err[i]); }
  assert(read->error_code == written->error_code);
  assert(read->is_last == written->is_last);
}

/* Error Msg: written and read back, then read and written back */
static void check_error_msg(void) {
  ErrorMsg sent;
  ErrorMsg got;
  uint8_t wire[304];
  uint8_t again[304];

  any_error_msg(&sent);
  assert(encode_error_msg(&sent, wire, 0) == 304);
  assert(decode_error_msg(&got, wire, 0) == 304);
  equal_error_msg(&got, &sent);

  for (size_t i = 0; i < 304; i++) { wire[i] = arbitrary(); }
  assert(decode_error_msg(&got, wire, 0) == 304);
  assert(encode_error_msg(&got, again, 0) == 304);
  for (size_t i = 0; i < 304; i++) { assert(again[i] == wire[i]); }
}

/* ---- Symbol Mapping Msg: 160 bytes ------------------------------------------- */

/* A symbol mapping message, which maps a symbol of one SType to another */
typedef struct {
  uint8_t stype_in;              /* byte 0 */
  uint8_t stype_in_symbol[71];   /* bytes 1 to 71 */
  uint8_t stype_out;             /* byte 72 */
  uint8_t stype_out_symbol[71];  /* bytes 73 to 143 */
  uint8_t start_ts[8];           /* bytes 144 to 151 */
  uint8_t end_ts[8];             /* bytes 152 to 159 */
} SymbolMappingMsg;

/* any Symbol Mapping Msg at all: every byte one the checker chooses */
static void any_symbol_mapping_msg(SymbolMappingMsg *record) {
  record->stype_in = arbitrary();
  for (size_t i = 0; i < 71; i++) { record->stype_in_symbol[i] = arbitrary(); }
  record->stype_out = arbitrary();
  for (size_t i = 0; i < 71; i++) { record->stype_out_symbol[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->start_ts[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->end_ts[i] = arbitrary(); }
}

/* Symbol Mapping Msg to the wire: 160 bytes from at, returning where the next byte goes */
static size_t encode_symbol_mapping_msg(const SymbolMappingMsg *record, uint8_t *wire, size_t at) {
  wire[at++] = record->stype_in;
  for (size_t i = 0; i < 71; i++) { wire[at++] = record->stype_in_symbol[i]; }
  wire[at++] = record->stype_out;
  for (size_t i = 0; i < 71; i++) { wire[at++] = record->stype_out_symbol[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->start_ts[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->end_ts[i]; }

  return at;
}

/* Symbol Mapping Msg off the wire: 160 bytes from at, returning where the next byte lies */
static size_t decode_symbol_mapping_msg(SymbolMappingMsg *record, const uint8_t *wire, size_t at) {
  record->stype_in = wire[at++];
  for (size_t i = 0; i < 71; i++) { record->stype_in_symbol[i] = wire[at++]; }
  record->stype_out = wire[at++];
  for (size_t i = 0; i < 71; i++) { record->stype_out_symbol[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->start_ts[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->end_ts[i] = wire[at++]; }

  return at;
}

/* what was read of Symbol Mapping Msg is what was written, byte for byte */
static void equal_symbol_mapping_msg(const SymbolMappingMsg *read, const SymbolMappingMsg *written) {
  assert(read->stype_in == written->stype_in);
  for (size_t i = 0; i < 71; i++) { assert(read->stype_in_symbol[i] == written->stype_in_symbol[i]); }
  assert(read->stype_out == written->stype_out);
  for (size_t i = 0; i < 71; i++) { assert(read->stype_out_symbol[i] == written->stype_out_symbol[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->start_ts[i] == written->start_ts[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->end_ts[i] == written->end_ts[i]); }
}

/* Symbol Mapping Msg: written and read back, then read and written back */
static void check_symbol_mapping_msg(void) {
  SymbolMappingMsg sent;
  SymbolMappingMsg got;
  uint8_t wire[160];
  uint8_t again[160];

  any_symbol_mapping_msg(&sent);
  assert(encode_symbol_mapping_msg(&sent, wire, 0) == 160);
  assert(decode_symbol_mapping_msg(&got, wire, 0) == 160);
  equal_symbol_mapping_msg(&got, &sent);

  for (size_t i = 0; i < 160; i++) { wire[i] = arbitrary(); }
  assert(decode_symbol_mapping_msg(&got, wire, 0) == 160);
  assert(encode_symbol_mapping_msg(&got, again, 0) == 160);
  for (size_t i = 0; i < 160; i++) { assert(again[i] == wire[i]); }
}

/* ---- System Msg: 304 bytes --------------------------------------------------- */

/* A non-error message from the Databento Live Subscription Gateway (LSG); also used for heartbeating */
typedef struct {
  uint8_t msg[303];     /* bytes 0 to 302 */
  uint8_t system_code;  /* byte 303 */
} SystemMsg;

/* any System Msg at all: every byte one the checker chooses */
static void any_system_msg(SystemMsg *record) {
  for (size_t i = 0; i < 303; i++) { record->msg[i] = arbitrary(); }
  record->system_code = arbitrary();
}

/* System Msg to the wire: 304 bytes from at, returning where the next byte goes */
static size_t encode_system_msg(const SystemMsg *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 303; i++) { wire[at++] = record->msg[i]; }
  wire[at++] = record->system_code;

  return at;
}

/* System Msg off the wire: 304 bytes from at, returning where the next byte lies */
static size_t decode_system_msg(SystemMsg *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 303; i++) { record->msg[i] = wire[at++]; }
  record->system_code = wire[at++];

  return at;
}

/* what was read of System Msg is what was written, byte for byte */
static void equal_system_msg(const SystemMsg *read, const SystemMsg *written) {
  for (size_t i = 0; i < 303; i++) { assert(read->msg[i] == written->msg[i]); }
  assert(read->system_code == written->system_code);
}

/* System Msg: written and read back, then read and written back */
static void check_system_msg(void) {
  SystemMsg sent;
  SystemMsg got;
  uint8_t wire[304];
  uint8_t again[304];

  any_system_msg(&sent);
  assert(encode_system_msg(&sent, wire, 0) == 304);
  assert(decode_system_msg(&got, wire, 0) == 304);
  equal_system_msg(&got, &sent);

  for (size_t i = 0; i < 304; i++) { wire[i] = arbitrary(); }
  assert(decode_system_msg(&got, wire, 0) == 304);
  assert(encode_system_msg(&got, again, 0) == 304);
  for (size_t i = 0; i < 304; i++) { assert(again[i] == wire[i]); }
}

/* ---- Stat Msg: 64 bytes ------------------------------------------------------ */

/* A statistics message; the record of the statistics schema */
typedef struct {
  uint8_t ts_recv[8];       /* bytes 0 to 7 */
  uint8_t ts_ref[8];        /* bytes 8 to 15 */
  uint8_t price[8];         /* bytes 16 to 23 */
  uint8_t quantity[8];      /* bytes 24 to 31 */
  uint8_t sequence[4];      /* bytes 32 to 35 */
  uint8_t ts_in_delta[4];   /* bytes 36 to 39 */
  uint8_t stat_type[2];     /* bytes 40 to 41 */
  uint8_t channel[2];       /* bytes 42 to 43 */
  uint8_t update_action;    /* byte 44 */
  uint8_t stat_flags;       /* byte 45 */
  uint8_t reserved_18[18];  /* bytes 46 to 63 */
} StatMsg;

/* any Stat Msg at all: every byte one the checker chooses */
static void any_stat_msg(StatMsg *record) {
  for (size_t i = 0; i < 8; i++) { record->ts_recv[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->ts_ref[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->sequence[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->ts_in_delta[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->stat_type[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->channel[i] = arbitrary(); }
  record->update_action = arbitrary();
  record->stat_flags = arbitrary();
  for (size_t i = 0; i < 18; i++) { record->reserved_18[i] = arbitrary(); }
}

/* Stat Msg to the wire: 64 bytes from at, returning where the next byte goes */
static size_t encode_stat_msg(const StatMsg *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->ts_recv[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->ts_ref[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->quantity[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->sequence[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->ts_in_delta[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->stat_type[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->channel[i]; }
  wire[at++] = record->update_action;
  wire[at++] = record->stat_flags;
  for (size_t i = 0; i < 18; i++) { wire[at++] = record->reserved_18[i]; }

  return at;
}

/* Stat Msg off the wire: 64 bytes from at, returning where the next byte lies */
static size_t decode_stat_msg(StatMsg *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->ts_recv[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->ts_ref[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->sequence[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->ts_in_delta[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->stat_type[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->channel[i] = wire[at++]; }
  record->update_action = wire[at++];
  record->stat_flags = wire[at++];
  for (size_t i = 0; i < 18; i++) { record->reserved_18[i] = wire[at++]; }

  return at;
}

/* what was read of Stat Msg is what was written, byte for byte */
static void equal_stat_msg(const StatMsg *read, const StatMsg *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->ts_recv[i] == written->ts_recv[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->ts_ref[i] == written->ts_ref[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->price[i] == written->price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->quantity[i] == written->quantity[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->sequence[i] == written->sequence[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->ts_in_delta[i] == written->ts_in_delta[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->stat_type[i] == written->stat_type[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->channel[i] == written->channel[i]); }
  assert(read->update_action == written->update_action);
  assert(read->stat_flags == written->stat_flags);
  for (size_t i = 0; i < 18; i++) { assert(read->reserved_18[i] == written->reserved_18[i]); }
}

/* Stat Msg: written and read back, then read and written back */
static void check_stat_msg(void) {
  StatMsg sent;
  StatMsg got;
  uint8_t wire[64];
  uint8_t again[64];

  any_stat_msg(&sent);
  assert(encode_stat_msg(&sent, wire, 0) == 64);
  assert(decode_stat_msg(&got, wire, 0) == 64);
  equal_stat_msg(&got, &sent);

  for (size_t i = 0; i < 64; i++) { wire[i] = arbitrary(); }
  assert(decode_stat_msg(&got, wire, 0) == 64);
  assert(encode_stat_msg(&got, again, 0) == 64);
  for (size_t i = 0; i < 64; i++) { assert(again[i] == wire[i]); }
}

/* ---- Consolidated Bid Ask Pair: 32 bytes ------------------------------------- */

/* A price level consolidated from multiple venues */
typedef struct {
  uint8_t bid_px[8];             /* bytes 0 to 7 */
  uint8_t ask_px[8];             /* bytes 8 to 15 */
  uint8_t bid_sz[4];             /* bytes 16 to 19 */
  uint8_t ask_sz[4];             /* bytes 20 to 23 */
  uint8_t bid_pb[2];             /* bytes 24 to 25 */
  uint8_t reserved_2[2];         /* bytes 26 to 27 */
  uint8_t ask_pb[2];             /* bytes 28 to 29 */
  uint8_t second_reserved_2[2];  /* bytes 30 to 31 */
} ConsolidatedBidAskPair;

/* any Consolidated Bid Ask Pair at all: every byte one the checker chooses */
static void any_consolidated_bid_ask_pair(ConsolidatedBidAskPair *record) {
  for (size_t i = 0; i < 8; i++) { record->bid_px[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->ask_px[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->bid_sz[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->ask_sz[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->bid_pb[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->reserved_2[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->ask_pb[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->second_reserved_2[i] = arbitrary(); }
}

/* Consolidated Bid Ask Pair to the wire: 32 bytes from at, returning where the next byte goes */
static size_t encode_consolidated_bid_ask_pair(const ConsolidatedBidAskPair *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->bid_px[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->ask_px[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->bid_sz[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->ask_sz[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->bid_pb[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->reserved_2[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->ask_pb[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->second_reserved_2[i]; }

  return at;
}

/* Consolidated Bid Ask Pair off the wire: 32 bytes from at, returning where the next byte lies */
static size_t decode_consolidated_bid_ask_pair(ConsolidatedBidAskPair *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->bid_px[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->ask_px[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->bid_sz[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->ask_sz[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->bid_pb[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->reserved_2[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->ask_pb[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->second_reserved_2[i] = wire[at++]; }

  return at;
}

/* what was read of Consolidated Bid Ask Pair is what was written, byte for byte */
static void equal_consolidated_bid_ask_pair(const ConsolidatedBidAskPair *read, const ConsolidatedBidAskPair *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->bid_px[i] == written->bid_px[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->ask_px[i] == written->ask_px[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->bid_sz[i] == written->bid_sz[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->ask_sz[i] == written->ask_sz[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->bid_pb[i] == written->bid_pb[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->reserved_2[i] == written->reserved_2[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->ask_pb[i] == written->ask_pb[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->second_reserved_2[i] == written->second_reserved_2[i]); }
}

/* Consolidated Bid Ask Pair: written and read back, then read and written back */
static void check_consolidated_bid_ask_pair(void) {
  ConsolidatedBidAskPair sent;
  ConsolidatedBidAskPair got;
  uint8_t wire[32];
  uint8_t again[32];

  any_consolidated_bid_ask_pair(&sent);
  assert(encode_consolidated_bid_ask_pair(&sent, wire, 0) == 32);
  assert(decode_consolidated_bid_ask_pair(&got, wire, 0) == 32);
  equal_consolidated_bid_ask_pair(&got, &sent);

  for (size_t i = 0; i < 32; i++) { wire[i] = arbitrary(); }
  assert(decode_consolidated_bid_ask_pair(&got, wire, 0) == 32);
  assert(encode_consolidated_bid_ask_pair(&got, again, 0) == 32);
  for (size_t i = 0; i < 32; i++) { assert(again[i] == wire[i]); }
}

/* ---- What esbmc checks ------------------------------------------------------- */

/* every record of the protocol, each on its own buffers */
static void checks(void) {
  check_record_header();
  check_bid_ask_pair();
  check_ohlcv_msg();
  check_status_msg();
  check_instrument_def_msg();
  check_imbalance_msg();
  check_error_msg();
  check_symbol_mapping_msg();
  check_system_msg();
  check_stat_msg();
  check_consolidated_bid_ask_pair();
}

int main(void) {
#ifdef CONCRETE
  for (pattern = 0; pattern < 4; pattern++) { checks(); }
#else
  checks();
#endif

  return 0;
}
