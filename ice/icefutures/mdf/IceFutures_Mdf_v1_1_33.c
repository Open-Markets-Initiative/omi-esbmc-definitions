// ice/icefutures/mdf/IceFutures_Mdf_v1_1_33.c
/*
 * Intercontinental Exchange Multicast Data Feed
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

/* ---- Packet Header: 16 bytes ------------------------------------------------- */

/* iMpact Upd market data packet header */
typedef struct {
  uint8_t session[2];         /* bytes 0 to 1 */
  uint8_t sequence[4];        /* bytes 2 to 5 */
  uint8_t number_of_msgs[2];  /* bytes 6 to 7 */
  uint8_t sent_date_time[8];  /* bytes 8 to 15 */
} PacketHeader;

/* any Packet Header at all: every byte one the checker chooses */
static void any_packet_header(PacketHeader *record) {
  for (size_t i = 0; i < 2; i++) { record->session[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->sequence[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->number_of_msgs[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->sent_date_time[i] = arbitrary(); }
}

/* Packet Header to the wire: 16 bytes from at, returning where the next byte goes */
static size_t encode_packet_header(const PacketHeader *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->session[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->sequence[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->number_of_msgs[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->sent_date_time[i]; }

  return at;
}

/* Packet Header off the wire: 16 bytes from at, returning where the next byte lies */
static size_t decode_packet_header(PacketHeader *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->session[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->sequence[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->number_of_msgs[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->sent_date_time[i] = wire[at++]; }

  return at;
}

/* what was read of Packet Header is what was written, byte for byte */
static void equal_packet_header(const PacketHeader *read, const PacketHeader *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->session[i] == written->session[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->sequence[i] == written->sequence[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->number_of_msgs[i] == written->number_of_msgs[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->sent_date_time[i] == written->sent_date_time[i]); }
}

/* Packet Header: written and read back, then read and written back */
static void check_packet_header(void) {
  PacketHeader sent;
  PacketHeader got;
  uint8_t wire[16];
  uint8_t again[16];

  any_packet_header(&sent);
  assert(encode_packet_header(&sent, wire, 0) == 16);
  assert(decode_packet_header(&got, wire, 0) == 16);
  equal_packet_header(&got, &sent);

  for (size_t i = 0; i < 16; i++) { wire[i] = arbitrary(); }
  assert(decode_packet_header(&got, wire, 0) == 16);
  assert(encode_packet_header(&got, again, 0) == 16);
  for (size_t i = 0; i < 16; i++) { assert(again[i] == wire[i]); }
}

/* ---- Message Header: 3 bytes ------------------------------------------------- */

/* iMpact message header */
typedef struct {
  uint8_t message_type;  /* byte 0 */
  uint8_t length[2];     /* bytes 1 to 2 */
} MessageHeader;

/* any Message Header at all: every byte one the checker chooses */
static void any_message_header(MessageHeader *record) {
  record->message_type = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->length[i] = arbitrary(); }
}

/* Message Header to the wire: 3 bytes from at, returning where the next byte goes */
static size_t encode_message_header(const MessageHeader *record, uint8_t *wire, size_t at) {
  wire[at++] = record->message_type;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->length[i]; }

  return at;
}

/* Message Header off the wire: 3 bytes from at, returning where the next byte lies */
static size_t decode_message_header(MessageHeader *record, const uint8_t *wire, size_t at) {
  record->message_type = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->length[i] = wire[at++]; }

  return at;
}

/* what was read of Message Header is what was written, byte for byte */
static void equal_message_header(const MessageHeader *read, const MessageHeader *written) {
  assert(read->message_type == written->message_type);
  for (size_t i = 0; i < 2; i++) { assert(read->length[i] == written->length[i]); }
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

/* ---- Market Snapshot Message: 133 bytes -------------------------------------- */

/* The market snapshot message is the same for full order depth and price level snapshot channel. */
typedef struct {
  uint8_t market_id[4];                                   /* bytes 0 to 3 */
  uint8_t market_type[2];                                 /* bytes 4 to 5 */
  uint8_t trading_status;                                 /* byte 6 */
  uint8_t volume[4];                                      /* bytes 7 to 10 */
  uint8_t block_volume[4];                                /* bytes 11 to 14 */
  uint8_t efs_volume[4];                                  /* bytes 15 to 18 */
  uint8_t efp_volume[4];                                  /* bytes 19 to 22 */
  uint8_t open_interest[4];                               /* bytes 23 to 26 */
  uint8_t opening_price[8];                               /* bytes 27 to 34 */
  uint8_t settlement_price_with_deal_price_precision[8];  /* bytes 35 to 42 */
  uint8_t high[8];                                        /* bytes 43 to 50 */
  uint8_t low[8];                                         /* bytes 51 to 58 */
  uint8_t vwap[8];                                        /* bytes 59 to 66 */
  uint8_t num_of_book_entries[4];                         /* bytes 67 to 70 */
  uint8_t last_trade_price[8];                            /* bytes 71 to 78 */
  uint8_t last_trade_quantity[4];                         /* bytes 79 to 82 */
  uint8_t last_trade_date_time[8];                        /* bytes 83 to 90 */
  uint8_t settle_price_date_time[8];                      /* bytes 91 to 98 */
  uint8_t last_message_sequence_id[4];                    /* bytes 99 to 102 */
  uint8_t reserved_2[2];                                  /* bytes 103 to 104 */
  uint8_t open_interest_date[10];                         /* bytes 105 to 114 */
  uint8_t is_settle_price_official;                       /* byte 115 */
  uint8_t settlement_price[8];                            /* bytes 116 to 123 */
  uint8_t has_previous_day_settlement_price;              /* byte 124 */
  uint8_t previous_day_settlement_price[8];               /* bytes 125 to 132 */
} MarketSnapshotMessage;

/* any Market Snapshot Message at all: every byte one the checker chooses */
static void any_market_snapshot_message(MarketSnapshotMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->market_id[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->market_type[i] = arbitrary(); }
  record->trading_status = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->volume[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->block_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->efs_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->efp_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->open_interest[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->opening_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->settlement_price_with_deal_price_precision[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->high[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->low[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->vwap[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->num_of_book_entries[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->last_trade_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->last_trade_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->last_trade_date_time[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->settle_price_date_time[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->last_message_sequence_id[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->reserved_2[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->open_interest_date[i] = arbitrary(); }
  record->is_settle_price_official = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->settlement_price[i] = arbitrary(); }
  record->has_previous_day_settlement_price = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->previous_day_settlement_price[i] = arbitrary(); }
}

/* Market Snapshot Message to the wire: 133 bytes from at, returning where the next byte goes */
static size_t encode_market_snapshot_message(const MarketSnapshotMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->market_id[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->market_type[i]; }
  wire[at++] = record->trading_status;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->volume[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->block_volume[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->efs_volume[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->efp_volume[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->open_interest[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->opening_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->settlement_price_with_deal_price_precision[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->high[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->low[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->vwap[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->num_of_book_entries[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->last_trade_price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->last_trade_quantity[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->last_trade_date_time[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->settle_price_date_time[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->last_message_sequence_id[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->reserved_2[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->open_interest_date[i]; }
  wire[at++] = record->is_settle_price_official;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->settlement_price[i]; }
  wire[at++] = record->has_previous_day_settlement_price;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->previous_day_settlement_price[i]; }

  return at;
}

/* Market Snapshot Message off the wire: 133 bytes from at, returning where the next byte lies */
static size_t decode_market_snapshot_message(MarketSnapshotMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->market_id[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->market_type[i] = wire[at++]; }
  record->trading_status = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->volume[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->block_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->efs_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->efp_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->open_interest[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->opening_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->settlement_price_with_deal_price_precision[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->high[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->low[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->vwap[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->num_of_book_entries[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->last_trade_price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->last_trade_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->last_trade_date_time[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->settle_price_date_time[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->last_message_sequence_id[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->reserved_2[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->open_interest_date[i] = wire[at++]; }
  record->is_settle_price_official = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->settlement_price[i] = wire[at++]; }
  record->has_previous_day_settlement_price = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->previous_day_settlement_price[i] = wire[at++]; }

  return at;
}

/* what was read of Market Snapshot Message is what was written, byte for byte */
static void equal_market_snapshot_message(const MarketSnapshotMessage *read, const MarketSnapshotMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->market_id[i] == written->market_id[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->market_type[i] == written->market_type[i]); }
  assert(read->trading_status == written->trading_status);
  for (size_t i = 0; i < 4; i++) { assert(read->volume[i] == written->volume[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->block_volume[i] == written->block_volume[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->efs_volume[i] == written->efs_volume[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->efp_volume[i] == written->efp_volume[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->open_interest[i] == written->open_interest[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->opening_price[i] == written->opening_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->settlement_price_with_deal_price_precision[i] == written->settlement_price_with_deal_price_precision[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->high[i] == written->high[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->low[i] == written->low[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->vwap[i] == written->vwap[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->num_of_book_entries[i] == written->num_of_book_entries[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->last_trade_price[i] == written->last_trade_price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->last_trade_quantity[i] == written->last_trade_quantity[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->last_trade_date_time[i] == written->last_trade_date_time[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->settle_price_date_time[i] == written->settle_price_date_time[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->last_message_sequence_id[i] == written->last_message_sequence_id[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->reserved_2[i] == written->reserved_2[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->open_interest_date[i] == written->open_interest_date[i]); }
  assert(read->is_settle_price_official == written->is_settle_price_official);
  for (size_t i = 0; i < 8; i++) { assert(read->settlement_price[i] == written->settlement_price[i]); }
  assert(read->has_previous_day_settlement_price == written->has_previous_day_settlement_price);
  for (size_t i = 0; i < 8; i++) { assert(read->previous_day_settlement_price[i] == written->previous_day_settlement_price[i]); }
}

/* Market Snapshot Message: written and read back, then read and written back */
static void check_market_snapshot_message(void) {
  MarketSnapshotMessage sent;
  MarketSnapshotMessage got;
  uint8_t wire[133];
  uint8_t again[133];

  any_market_snapshot_message(&sent);
  assert(encode_market_snapshot_message(&sent, wire, 0) == 133);
  assert(decode_market_snapshot_message(&got, wire, 0) == 133);
  equal_market_snapshot_message(&got, &sent);

  for (size_t i = 0; i < 133; i++) { wire[i] = arbitrary(); }
  assert(decode_market_snapshot_message(&got, wire, 0) == 133);
  assert(encode_market_snapshot_message(&got, again, 0) == 133);
  for (size_t i = 0; i < 133; i++) { assert(again[i] == wire[i]); }
}

/* ---- Trade Message: 46 bytes ------------------------------------------------- */

/* A trade with IsSystemPricedLeg equal to ‘Y’ should not be used for the last price, High, Low and Open. Also please refer to Appendix B on how to handle market stats for given OffTradeMarketType. This message will not be sent for trades in Endex Spot markets. */
typedef struct {
  uint8_t market_id[4];                      /* bytes 0 to 3 */
  uint8_t trade_id[8];                       /* bytes 4 to 11 */
  uint8_t is_system_priced_leg;              /* byte 12 */
  uint8_t price[8];                          /* bytes 13 to 20 */
  uint8_t quantity[4];                       /* bytes 21 to 24 */
  uint8_t off_market_trade_indicator;        /* byte 25 */
  uint8_t transact_date_time[8];             /* bytes 26 to 33 */
  uint8_t system_priced_leg_type;            /* byte 34 */
  uint8_t is_implied_spread_at_market_open;  /* byte 35 */
  uint8_t is_adjusted_trade;                 /* byte 36 */
  uint8_t aggressor_side;                    /* byte 37 */
  uint8_t extra_flags;                       /* byte 38 */
  uint8_t off_market_trade_type[3];          /* bytes 39 to 41 */
  uint8_t sequence_within_millis[4];         /* bytes 42 to 45 */
} TradeMessage;

/* any Trade Message at all: every byte one the checker chooses */
static void any_trade_message(TradeMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->market_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->trade_id[i] = arbitrary(); }
  record->is_system_priced_leg = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->quantity[i] = arbitrary(); }
  record->off_market_trade_indicator = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->transact_date_time[i] = arbitrary(); }
  record->system_priced_leg_type = arbitrary();
  record->is_implied_spread_at_market_open = arbitrary();
  record->is_adjusted_trade = arbitrary();
  record->aggressor_side = arbitrary();
  record->extra_flags = arbitrary();
  for (size_t i = 0; i < 3; i++) { record->off_market_trade_type[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->sequence_within_millis[i] = arbitrary(); }
}

/* Trade Message to the wire: 46 bytes from at, returning where the next byte goes */
static size_t encode_trade_message(const TradeMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->market_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->trade_id[i]; }
  wire[at++] = record->is_system_priced_leg;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->quantity[i]; }
  wire[at++] = record->off_market_trade_indicator;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->transact_date_time[i]; }
  wire[at++] = record->system_priced_leg_type;
  wire[at++] = record->is_implied_spread_at_market_open;
  wire[at++] = record->is_adjusted_trade;
  wire[at++] = record->aggressor_side;
  wire[at++] = record->extra_flags;
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->off_market_trade_type[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->sequence_within_millis[i]; }

  return at;
}

/* Trade Message off the wire: 46 bytes from at, returning where the next byte lies */
static size_t decode_trade_message(TradeMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->market_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->trade_id[i] = wire[at++]; }
  record->is_system_priced_leg = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->quantity[i] = wire[at++]; }
  record->off_market_trade_indicator = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->transact_date_time[i] = wire[at++]; }
  record->system_priced_leg_type = wire[at++];
  record->is_implied_spread_at_market_open = wire[at++];
  record->is_adjusted_trade = wire[at++];
  record->aggressor_side = wire[at++];
  record->extra_flags = wire[at++];
  for (size_t i = 0; i < 3; i++) { record->off_market_trade_type[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->sequence_within_millis[i] = wire[at++]; }

  return at;
}

/* what was read of Trade Message is what was written, byte for byte */
static void equal_trade_message(const TradeMessage *read, const TradeMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->market_id[i] == written->market_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->trade_id[i] == written->trade_id[i]); }
  assert(read->is_system_priced_leg == written->is_system_priced_leg);
  for (size_t i = 0; i < 8; i++) { assert(read->price[i] == written->price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->quantity[i] == written->quantity[i]); }
  assert(read->off_market_trade_indicator == written->off_market_trade_indicator);
  for (size_t i = 0; i < 8; i++) { assert(read->transact_date_time[i] == written->transact_date_time[i]); }
  assert(read->system_priced_leg_type == written->system_priced_leg_type);
  assert(read->is_implied_spread_at_market_open == written->is_implied_spread_at_market_open);
  assert(read->is_adjusted_trade == written->is_adjusted_trade);
  assert(read->aggressor_side == written->aggressor_side);
  assert(read->extra_flags == written->extra_flags);
  for (size_t i = 0; i < 3; i++) { assert(read->off_market_trade_type[i] == written->off_market_trade_type[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->sequence_within_millis[i] == written->sequence_within_millis[i]); }
}

/* Trade Message: written and read back, then read and written back */
static void check_trade_message(void) {
  TradeMessage sent;
  TradeMessage got;
  uint8_t wire[46];
  uint8_t again[46];

  any_trade_message(&sent);
  assert(encode_trade_message(&sent, wire, 0) == 46);
  assert(decode_trade_message(&got, wire, 0) == 46);
  equal_trade_message(&got, &sent);

  for (size_t i = 0; i < 46; i++) { wire[i] = arbitrary(); }
  assert(decode_trade_message(&got, wire, 0) == 46);
  assert(encode_trade_message(&got, again, 0) == 46);
  for (size_t i = 0; i < 46; i++) { assert(again[i] == wire[i]); }
}

/* ---- Spot Market Trade Message: 50 bytes ------------------------------------- */

/* This message will be sent only upon trade in spot markets and it will be rendered on spot market channels. */
typedef struct {
  uint8_t market_id[4];                 /* bytes 0 to 3 */
  uint8_t trade_id[8];                  /* bytes 4 to 11 */
  uint8_t price[8];                     /* bytes 12 to 19 */
  uint8_t quantity[4];                  /* bytes 20 to 23 */
  uint8_t transact_date_time[8];        /* bytes 24 to 31 */
  uint8_t extra_flags;                  /* byte 32 */
  uint8_t delivery_begin_date_time[8];  /* bytes 33 to 40 */
  uint8_t delivery_end_date_time[8];    /* bytes 41 to 48 */
  uint8_t is_system_priced_leg;         /* byte 49 */
} SpotMarketTradeMessage;

/* any Spot Market Trade Message at all: every byte one the checker chooses */
static void any_spot_market_trade_message(SpotMarketTradeMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->market_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->trade_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->transact_date_time[i] = arbitrary(); }
  record->extra_flags = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->delivery_begin_date_time[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->delivery_end_date_time[i] = arbitrary(); }
  record->is_system_priced_leg = arbitrary();
}

/* Spot Market Trade Message to the wire: 50 bytes from at, returning where the next byte goes */
static size_t encode_spot_market_trade_message(const SpotMarketTradeMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->market_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->trade_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->quantity[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->transact_date_time[i]; }
  wire[at++] = record->extra_flags;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->delivery_begin_date_time[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->delivery_end_date_time[i]; }
  wire[at++] = record->is_system_priced_leg;

  return at;
}

/* Spot Market Trade Message off the wire: 50 bytes from at, returning where the next byte lies */
static size_t decode_spot_market_trade_message(SpotMarketTradeMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->market_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->trade_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->transact_date_time[i] = wire[at++]; }
  record->extra_flags = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->delivery_begin_date_time[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->delivery_end_date_time[i] = wire[at++]; }
  record->is_system_priced_leg = wire[at++];

  return at;
}

/* what was read of Spot Market Trade Message is what was written, byte for byte */
static void equal_spot_market_trade_message(const SpotMarketTradeMessage *read, const SpotMarketTradeMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->market_id[i] == written->market_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->trade_id[i] == written->trade_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->price[i] == written->price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->quantity[i] == written->quantity[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->transact_date_time[i] == written->transact_date_time[i]); }
  assert(read->extra_flags == written->extra_flags);
  for (size_t i = 0; i < 8; i++) { assert(read->delivery_begin_date_time[i] == written->delivery_begin_date_time[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->delivery_end_date_time[i] == written->delivery_end_date_time[i]); }
  assert(read->is_system_priced_leg == written->is_system_priced_leg);
}

/* Spot Market Trade Message: written and read back, then read and written back */
static void check_spot_market_trade_message(void) {
  SpotMarketTradeMessage sent;
  SpotMarketTradeMessage got;
  uint8_t wire[50];
  uint8_t again[50];

  any_spot_market_trade_message(&sent);
  assert(encode_spot_market_trade_message(&sent, wire, 0) == 50);
  assert(decode_spot_market_trade_message(&got, wire, 0) == 50);
  equal_spot_market_trade_message(&got, &sent);

  for (size_t i = 0; i < 50; i++) { wire[i] = arbitrary(); }
  assert(decode_spot_market_trade_message(&got, wire, 0) == 50);
  assert(encode_spot_market_trade_message(&got, again, 0) == 50);
  for (size_t i = 0; i < 50; i++) { assert(again[i] == wire[i]); }
}

/* ---- Investigated Trade Message: 37 bytes ------------------------------------ */

/* This message is sent when a trade is put under investigation or the investigation is completed. Client can use the market ID and order ID to find and flag the original trade if needed. */
typedef struct {
  uint8_t market_id[4];                /* bytes 0 to 3 */
  uint8_t trade_id[8];                 /* bytes 4 to 11 */
  uint8_t price[8];                    /* bytes 12 to 19 */
  uint8_t quantity[4];                 /* bytes 20 to 23 */
  uint8_t off_market_trade_indicator;  /* byte 24 */
  uint8_t message_date_time[8];        /* bytes 25 to 32 */
  uint8_t investigation_status;        /* byte 33 */
  uint8_t off_market_trade_type[3];    /* bytes 34 to 36 */
} InvestigatedTradeMessage;

/* any Investigated Trade Message at all: every byte one the checker chooses */
static void any_investigated_trade_message(InvestigatedTradeMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->market_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->trade_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->quantity[i] = arbitrary(); }
  record->off_market_trade_indicator = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->message_date_time[i] = arbitrary(); }
  record->investigation_status = arbitrary();
  for (size_t i = 0; i < 3; i++) { record->off_market_trade_type[i] = arbitrary(); }
}

/* Investigated Trade Message to the wire: 37 bytes from at, returning where the next byte goes */
static size_t encode_investigated_trade_message(const InvestigatedTradeMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->market_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->trade_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->quantity[i]; }
  wire[at++] = record->off_market_trade_indicator;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->message_date_time[i]; }
  wire[at++] = record->investigation_status;
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->off_market_trade_type[i]; }

  return at;
}

/* Investigated Trade Message off the wire: 37 bytes from at, returning where the next byte lies */
static size_t decode_investigated_trade_message(InvestigatedTradeMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->market_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->trade_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->quantity[i] = wire[at++]; }
  record->off_market_trade_indicator = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->message_date_time[i] = wire[at++]; }
  record->investigation_status = wire[at++];
  for (size_t i = 0; i < 3; i++) { record->off_market_trade_type[i] = wire[at++]; }

  return at;
}

/* what was read of Investigated Trade Message is what was written, byte for byte */
static void equal_investigated_trade_message(const InvestigatedTradeMessage *read, const InvestigatedTradeMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->market_id[i] == written->market_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->trade_id[i] == written->trade_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->price[i] == written->price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->quantity[i] == written->quantity[i]); }
  assert(read->off_market_trade_indicator == written->off_market_trade_indicator);
  for (size_t i = 0; i < 8; i++) { assert(read->message_date_time[i] == written->message_date_time[i]); }
  assert(read->investigation_status == written->investigation_status);
  for (size_t i = 0; i < 3; i++) { assert(read->off_market_trade_type[i] == written->off_market_trade_type[i]); }
}

/* Investigated Trade Message: written and read back, then read and written back */
static void check_investigated_trade_message(void) {
  InvestigatedTradeMessage sent;
  InvestigatedTradeMessage got;
  uint8_t wire[37];
  uint8_t again[37];

  any_investigated_trade_message(&sent);
  assert(encode_investigated_trade_message(&sent, wire, 0) == 37);
  assert(decode_investigated_trade_message(&got, wire, 0) == 37);
  equal_investigated_trade_message(&got, &sent);

  for (size_t i = 0; i < 37; i++) { wire[i] = arbitrary(); }
  assert(decode_investigated_trade_message(&got, wire, 0) == 37);
  assert(encode_investigated_trade_message(&got, again, 0) == 37);
  for (size_t i = 0; i < 37; i++) { assert(again[i] == wire[i]); }
}

/* ---- Cancelled Trade Message: 36 bytes --------------------------------------- */

/* This message is sent when a trade is cancelled. */
typedef struct {
  uint8_t market_id[4];                /* bytes 0 to 3 */
  uint8_t trade_id[8];                 /* bytes 4 to 11 */
  uint8_t price[8];                    /* bytes 12 to 19 */
  uint8_t quantity[4];                 /* bytes 20 to 23 */
  uint8_t off_market_trade_indicator;  /* byte 24 */
  uint8_t message_date_time[8];        /* bytes 25 to 32 */
  uint8_t off_market_trade_type[3];    /* bytes 33 to 35 */
} CancelledTradeMessage;

/* any Cancelled Trade Message at all: every byte one the checker chooses */
static void any_cancelled_trade_message(CancelledTradeMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->market_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->trade_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->quantity[i] = arbitrary(); }
  record->off_market_trade_indicator = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->message_date_time[i] = arbitrary(); }
  for (size_t i = 0; i < 3; i++) { record->off_market_trade_type[i] = arbitrary(); }
}

/* Cancelled Trade Message to the wire: 36 bytes from at, returning where the next byte goes */
static size_t encode_cancelled_trade_message(const CancelledTradeMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->market_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->trade_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->quantity[i]; }
  wire[at++] = record->off_market_trade_indicator;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->message_date_time[i]; }
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->off_market_trade_type[i]; }

  return at;
}

/* Cancelled Trade Message off the wire: 36 bytes from at, returning where the next byte lies */
static size_t decode_cancelled_trade_message(CancelledTradeMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->market_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->trade_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->quantity[i] = wire[at++]; }
  record->off_market_trade_indicator = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->message_date_time[i] = wire[at++]; }
  for (size_t i = 0; i < 3; i++) { record->off_market_trade_type[i] = wire[at++]; }

  return at;
}

/* what was read of Cancelled Trade Message is what was written, byte for byte */
static void equal_cancelled_trade_message(const CancelledTradeMessage *read, const CancelledTradeMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->market_id[i] == written->market_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->trade_id[i] == written->trade_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->price[i] == written->price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->quantity[i] == written->quantity[i]); }
  assert(read->off_market_trade_indicator == written->off_market_trade_indicator);
  for (size_t i = 0; i < 8; i++) { assert(read->message_date_time[i] == written->message_date_time[i]); }
  for (size_t i = 0; i < 3; i++) { assert(read->off_market_trade_type[i] == written->off_market_trade_type[i]); }
}

/* Cancelled Trade Message: written and read back, then read and written back */
static void check_cancelled_trade_message(void) {
  CancelledTradeMessage sent;
  CancelledTradeMessage got;
  uint8_t wire[36];
  uint8_t again[36];

  any_cancelled_trade_message(&sent);
  assert(encode_cancelled_trade_message(&sent, wire, 0) == 36);
  assert(decode_cancelled_trade_message(&got, wire, 0) == 36);
  equal_cancelled_trade_message(&got, &sent);

  for (size_t i = 0; i < 36; i++) { wire[i] = arbitrary(); }
  assert(decode_cancelled_trade_message(&got, wire, 0) == 36);
  assert(encode_cancelled_trade_message(&got, again, 0) == 36);
  for (size_t i = 0; i < 36; i++) { assert(again[i] == wire[i]); }
}

/* ---- Market Statistics Message: 52 bytes ------------------------------------- */

/* This is usually sent after a trade or cancelled trade message. */
typedef struct {
  uint8_t market_id[4];          /* bytes 0 to 3 */
  uint8_t volume[4];             /* bytes 4 to 7 */
  uint8_t block_volume[4];       /* bytes 8 to 11 */
  uint8_t efs_volume[4];         /* bytes 12 to 15 */
  uint8_t efp_volume[4];         /* bytes 16 to 19 */
  uint8_t high[8];               /* bytes 20 to 27 */
  uint8_t low[8];                /* bytes 28 to 35 */
  uint8_t vwap[8];               /* bytes 36 to 43 */
  uint8_t message_date_time[8];  /* bytes 44 to 51 */
} MarketStatisticsMessage;

/* any Market Statistics Message at all: every byte one the checker chooses */
static void any_market_statistics_message(MarketStatisticsMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->market_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->volume[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->block_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->efs_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->efp_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->high[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->low[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->vwap[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->message_date_time[i] = arbitrary(); }
}

/* Market Statistics Message to the wire: 52 bytes from at, returning where the next byte goes */
static size_t encode_market_statistics_message(const MarketStatisticsMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->market_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->volume[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->block_volume[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->efs_volume[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->efp_volume[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->high[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->low[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->vwap[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->message_date_time[i]; }

  return at;
}

/* Market Statistics Message off the wire: 52 bytes from at, returning where the next byte lies */
static size_t decode_market_statistics_message(MarketStatisticsMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->market_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->volume[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->block_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->efs_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->efp_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->high[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->low[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->vwap[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->message_date_time[i] = wire[at++]; }

  return at;
}

/* what was read of Market Statistics Message is what was written, byte for byte */
static void equal_market_statistics_message(const MarketStatisticsMessage *read, const MarketStatisticsMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->market_id[i] == written->market_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->volume[i] == written->volume[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->block_volume[i] == written->block_volume[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->efs_volume[i] == written->efs_volume[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->efp_volume[i] == written->efp_volume[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->high[i] == written->high[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->low[i] == written->low[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->vwap[i] == written->vwap[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->message_date_time[i] == written->message_date_time[i]); }
}

/* Market Statistics Message: written and read back, then read and written back */
static void check_market_statistics_message(void) {
  MarketStatisticsMessage sent;
  MarketStatisticsMessage got;
  uint8_t wire[52];
  uint8_t again[52];

  any_market_statistics_message(&sent);
  assert(encode_market_statistics_message(&sent, wire, 0) == 52);
  assert(decode_market_statistics_message(&got, wire, 0) == 52);
  equal_market_statistics_message(&got, &sent);

  for (size_t i = 0; i < 52; i++) { wire[i] = arbitrary(); }
  assert(decode_market_statistics_message(&got, wire, 0) == 52);
  assert(encode_market_statistics_message(&got, again, 0) == 52);
  for (size_t i = 0; i < 52; i++) { assert(again[i] == wire[i]); }
}

/* ---- Market State Change Message: 13 bytes ----------------------------------- */

/* Market State Change Message */
typedef struct {
  uint8_t market_id[4];          /* bytes 0 to 3 */
  uint8_t trading_status;        /* byte 4 */
  uint8_t message_date_time[8];  /* bytes 5 to 12 */
} MarketStateChangeMessage;

/* any Market State Change Message at all: every byte one the checker chooses */
static void any_market_state_change_message(MarketStateChangeMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->market_id[i] = arbitrary(); }
  record->trading_status = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->message_date_time[i] = arbitrary(); }
}

/* Market State Change Message to the wire: 13 bytes from at, returning where the next byte goes */
static size_t encode_market_state_change_message(const MarketStateChangeMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->market_id[i]; }
  wire[at++] = record->trading_status;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->message_date_time[i]; }

  return at;
}

/* Market State Change Message off the wire: 13 bytes from at, returning where the next byte lies */
static size_t decode_market_state_change_message(MarketStateChangeMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->market_id[i] = wire[at++]; }
  record->trading_status = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->message_date_time[i] = wire[at++]; }

  return at;
}

/* what was read of Market State Change Message is what was written, byte for byte */
static void equal_market_state_change_message(const MarketStateChangeMessage *read, const MarketStateChangeMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->market_id[i] == written->market_id[i]); }
  assert(read->trading_status == written->trading_status);
  for (size_t i = 0; i < 8; i++) { assert(read->message_date_time[i] == written->message_date_time[i]); }
}

/* Market State Change Message: written and read back, then read and written back */
static void check_market_state_change_message(void) {
  MarketStateChangeMessage sent;
  MarketStateChangeMessage got;
  uint8_t wire[13];
  uint8_t again[13];

  any_market_state_change_message(&sent);
  assert(encode_market_state_change_message(&sent, wire, 0) == 13);
  assert(decode_market_state_change_message(&got, wire, 0) == 13);
  equal_market_state_change_message(&got, &sent);

  for (size_t i = 0; i < 13; i++) { wire[i] = arbitrary(); }
  assert(decode_market_state_change_message(&got, wire, 0) == 13);
  assert(encode_market_state_change_message(&got, again, 0) == 13);
  for (size_t i = 0; i < 13; i++) { assert(again[i] == wire[i]); }
}

/* ---- System Text Message: 1008 bytes ----------------------------------------- */

/* System Text Message */
typedef struct {
  uint8_t text_message[200];            /* bytes 0 to 199 */
  uint8_t message_date_time[8];         /* bytes 200 to 207 */
  uint8_t text_message_extra_fld[800];  /* bytes 208 to 1007 */
} SystemTextMessage;

/* any System Text Message at all: every byte one the checker chooses */
static void any_system_text_message(SystemTextMessage *record) {
  for (size_t i = 0; i < 200; i++) { record->text_message[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->message_date_time[i] = arbitrary(); }
  for (size_t i = 0; i < 800; i++) { record->text_message_extra_fld[i] = arbitrary(); }
}

/* System Text Message to the wire: 1008 bytes from at, returning where the next byte goes */
static size_t encode_system_text_message(const SystemTextMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 200; i++) { wire[at++] = record->text_message[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->message_date_time[i]; }
  for (size_t i = 0; i < 800; i++) { wire[at++] = record->text_message_extra_fld[i]; }

  return at;
}

/* System Text Message off the wire: 1008 bytes from at, returning where the next byte lies */
static size_t decode_system_text_message(SystemTextMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 200; i++) { record->text_message[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->message_date_time[i] = wire[at++]; }
  for (size_t i = 0; i < 800; i++) { record->text_message_extra_fld[i] = wire[at++]; }

  return at;
}

/* what was read of System Text Message is what was written, byte for byte */
static void equal_system_text_message(const SystemTextMessage *read, const SystemTextMessage *written) {
  for (size_t i = 0; i < 200; i++) { assert(read->text_message[i] == written->text_message[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->message_date_time[i] == written->message_date_time[i]); }
  for (size_t i = 0; i < 800; i++) { assert(read->text_message_extra_fld[i] == written->text_message_extra_fld[i]); }
}

/* System Text Message: written and read back, then read and written back */
static void check_system_text_message(void) {
  SystemTextMessage sent;
  SystemTextMessage got;
  uint8_t wire[1008];
  uint8_t again[1008];

  any_system_text_message(&sent);
  assert(encode_system_text_message(&sent, wire, 0) == 1008);
  assert(decode_system_text_message(&got, wire, 0) == 1008);
  equal_system_text_message(&got, &sent);

  for (size_t i = 0; i < 1008; i++) { wire[i] = arbitrary(); }
  assert(decode_system_text_message(&got, wire, 0) == 1008);
  assert(encode_system_text_message(&got, again, 0) == 1008);
  for (size_t i = 0; i < 1008; i++) { assert(again[i] == wire[i]); }
}

/* ---- Open Interest Message: 30 bytes ----------------------------------------- */

/* Open Interest Message */
typedef struct {
  uint8_t market_id[4];             /* bytes 0 to 3 */
  uint8_t open_interest[4];         /* bytes 4 to 7 */
  uint8_t open_interest_change[4];  /* bytes 8 to 11 */
  uint8_t message_date_time[8];     /* bytes 12 to 19 */
  uint8_t open_interest_date[10];   /* bytes 20 to 29 */
} OpenInterestMessage;

/* any Open Interest Message at all: every byte one the checker chooses */
static void any_open_interest_message(OpenInterestMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->market_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->open_interest[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->open_interest_change[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->message_date_time[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->open_interest_date[i] = arbitrary(); }
}

/* Open Interest Message to the wire: 30 bytes from at, returning where the next byte goes */
static size_t encode_open_interest_message(const OpenInterestMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->market_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->open_interest[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->open_interest_change[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->message_date_time[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->open_interest_date[i]; }

  return at;
}

/* Open Interest Message off the wire: 30 bytes from at, returning where the next byte lies */
static size_t decode_open_interest_message(OpenInterestMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->market_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->open_interest[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->open_interest_change[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->message_date_time[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->open_interest_date[i] = wire[at++]; }

  return at;
}

/* what was read of Open Interest Message is what was written, byte for byte */
static void equal_open_interest_message(const OpenInterestMessage *read, const OpenInterestMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->market_id[i] == written->market_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->open_interest[i] == written->open_interest[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->open_interest_change[i] == written->open_interest_change[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->message_date_time[i] == written->message_date_time[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->open_interest_date[i] == written->open_interest_date[i]); }
}

/* Open Interest Message: written and read back, then read and written back */
static void check_open_interest_message(void) {
  OpenInterestMessage sent;
  OpenInterestMessage got;
  uint8_t wire[30];
  uint8_t again[30];

  any_open_interest_message(&sent);
  assert(encode_open_interest_message(&sent, wire, 0) == 30);
  assert(decode_open_interest_message(&got, wire, 0) == 30);
  equal_open_interest_message(&got, &sent);

  for (size_t i = 0; i < 30; i++) { wire[i] = arbitrary(); }
  assert(decode_open_interest_message(&got, wire, 0) == 30);
  assert(encode_open_interest_message(&got, again, 0) == 30);
  for (size_t i = 0; i < 30; i++) { assert(again[i] == wire[i]); }
}

/* ---- Open Price Message: 20 bytes -------------------------------------------- */

/* Open Price Message */
typedef struct {
  uint8_t market_id[4];          /* bytes 0 to 3 */
  uint8_t open_price[8];         /* bytes 4 to 11 */
  uint8_t message_date_time[8];  /* bytes 12 to 19 */
} OpenPriceMessage;

/* any Open Price Message at all: every byte one the checker chooses */
static void any_open_price_message(OpenPriceMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->market_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->open_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->message_date_time[i] = arbitrary(); }
}

/* Open Price Message to the wire: 20 bytes from at, returning where the next byte goes */
static size_t encode_open_price_message(const OpenPriceMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->market_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->open_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->message_date_time[i]; }

  return at;
}

/* Open Price Message off the wire: 20 bytes from at, returning where the next byte lies */
static size_t decode_open_price_message(OpenPriceMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->market_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->open_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->message_date_time[i] = wire[at++]; }

  return at;
}

/* what was read of Open Price Message is what was written, byte for byte */
static void equal_open_price_message(const OpenPriceMessage *read, const OpenPriceMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->market_id[i] == written->market_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->open_price[i] == written->open_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->message_date_time[i] == written->message_date_time[i]); }
}

/* Open Price Message: written and read back, then read and written back */
static void check_open_price_message(void) {
  OpenPriceMessage sent;
  OpenPriceMessage got;
  uint8_t wire[20];
  uint8_t again[20];

  any_open_price_message(&sent);
  assert(encode_open_price_message(&sent, wire, 0) == 20);
  assert(decode_open_price_message(&got, wire, 0) == 20);
  equal_open_price_message(&got, &sent);

  for (size_t i = 0; i < 20; i++) { wire[i] = arbitrary(); }
  assert(decode_open_price_message(&got, wire, 0) == 20);
  assert(encode_open_price_message(&got, again, 0) == 20);
  for (size_t i = 0; i < 20; i++) { assert(again[i] == wire[i]); }
}

/* ---- Close Price Message: 20 bytes ------------------------------------------- */

/* Close Price Message */
typedef struct {
  uint8_t market_id[4];          /* bytes 0 to 3 */
  uint8_t close_price[8];        /* bytes 4 to 11 */
  uint8_t message_date_time[8];  /* bytes 12 to 19 */
} ClosePriceMessage;

/* any Close Price Message at all: every byte one the checker chooses */
static void any_close_price_message(ClosePriceMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->market_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->close_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->message_date_time[i] = arbitrary(); }
}

/* Close Price Message to the wire: 20 bytes from at, returning where the next byte goes */
static size_t encode_close_price_message(const ClosePriceMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->market_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->close_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->message_date_time[i]; }

  return at;
}

/* Close Price Message off the wire: 20 bytes from at, returning where the next byte lies */
static size_t decode_close_price_message(ClosePriceMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->market_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->close_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->message_date_time[i] = wire[at++]; }

  return at;
}

/* what was read of Close Price Message is what was written, byte for byte */
static void equal_close_price_message(const ClosePriceMessage *read, const ClosePriceMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->market_id[i] == written->market_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->close_price[i] == written->close_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->message_date_time[i] == written->message_date_time[i]); }
}

/* Close Price Message: written and read back, then read and written back */
static void check_close_price_message(void) {
  ClosePriceMessage sent;
  ClosePriceMessage got;
  uint8_t wire[20];
  uint8_t again[20];

  any_close_price_message(&sent);
  assert(encode_close_price_message(&sent, wire, 0) == 20);
  assert(decode_close_price_message(&got, wire, 0) == 20);
  equal_close_price_message(&got, &sent);

  for (size_t i = 0; i < 20; i++) { wire[i] = arbitrary(); }
  assert(decode_close_price_message(&got, wire, 0) == 20);
  assert(encode_close_price_message(&got, again, 0) == 20);
  for (size_t i = 0; i < 20; i++) { assert(again[i] == wire[i]); }
}

/* ---- Settlement Price Message: 37 bytes -------------------------------------- */

/* Settlement prices could be official or unofficial. For a given market, the exchange usually sends out unofficial price before the official one. */
typedef struct {
  uint8_t market_id[4];                                   /* bytes 0 to 3 */
  uint8_t settlement_price_with_deal_price_precision[8];  /* bytes 4 to 11 */
  uint8_t message_date_time[8];                           /* bytes 12 to 19 */
  uint8_t is_official;                                    /* byte 20 */
  uint8_t valuation_date_time[8];                         /* bytes 21 to 28 */
  uint8_t settlement_price[8];                            /* bytes 29 to 36 */
} SettlementPriceMessage;

/* any Settlement Price Message at all: every byte one the checker chooses */
static void any_settlement_price_message(SettlementPriceMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->market_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->settlement_price_with_deal_price_precision[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->message_date_time[i] = arbitrary(); }
  record->is_official = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->valuation_date_time[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->settlement_price[i] = arbitrary(); }
}

/* Settlement Price Message to the wire: 37 bytes from at, returning where the next byte goes */
static size_t encode_settlement_price_message(const SettlementPriceMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->market_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->settlement_price_with_deal_price_precision[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->message_date_time[i]; }
  wire[at++] = record->is_official;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->valuation_date_time[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->settlement_price[i]; }

  return at;
}

/* Settlement Price Message off the wire: 37 bytes from at, returning where the next byte lies */
static size_t decode_settlement_price_message(SettlementPriceMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->market_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->settlement_price_with_deal_price_precision[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->message_date_time[i] = wire[at++]; }
  record->is_official = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->valuation_date_time[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->settlement_price[i] = wire[at++]; }

  return at;
}

/* what was read of Settlement Price Message is what was written, byte for byte */
static void equal_settlement_price_message(const SettlementPriceMessage *read, const SettlementPriceMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->market_id[i] == written->market_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->settlement_price_with_deal_price_precision[i] == written->settlement_price_with_deal_price_precision[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->message_date_time[i] == written->message_date_time[i]); }
  assert(read->is_official == written->is_official);
  for (size_t i = 0; i < 8; i++) { assert(read->valuation_date_time[i] == written->valuation_date_time[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->settlement_price[i] == written->settlement_price[i]); }
}

/* Settlement Price Message: written and read back, then read and written back */
static void check_settlement_price_message(void) {
  SettlementPriceMessage sent;
  SettlementPriceMessage got;
  uint8_t wire[37];
  uint8_t again[37];

  any_settlement_price_message(&sent);
  assert(encode_settlement_price_message(&sent, wire, 0) == 37);
  assert(decode_settlement_price_message(&got, wire, 0) == 37);
  equal_settlement_price_message(&got, &sent);

  for (size_t i = 0; i < 37; i++) { wire[i] = arbitrary(); }
  assert(decode_settlement_price_message(&got, wire, 0) == 37);
  assert(encode_settlement_price_message(&got, again, 0) == 37);
  for (size_t i = 0; i < 37; i++) { assert(again[i] == wire[i]); }
}

/* ---- Index Prices Message: 61 bytes ------------------------------------------ */

/* The exchange sends out Marker/Index Prices when there is an update. */
typedef struct {
  uint8_t market_id[4];                      /* bytes 0 to 3 */
  uint8_t price[8];                          /* bytes 4 to 11 */
  uint8_t short_name[30];                    /* bytes 12 to 41 */
  uint8_t published_date_time[8];            /* bytes 42 to 49 */
  uint8_t valuation_date_applying_date[10];  /* bytes 50 to 59 */
  uint8_t status;                            /* byte 60 */
} IndexPricesMessage;

/* any Index Prices Message at all: every byte one the checker chooses */
static void any_index_prices_message(IndexPricesMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->market_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->price[i] = arbitrary(); }
  for (size_t i = 0; i < 30; i++) { record->short_name[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->published_date_time[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->valuation_date_applying_date[i] = arbitrary(); }
  record->status = arbitrary();
}

/* Index Prices Message to the wire: 61 bytes from at, returning where the next byte goes */
static size_t encode_index_prices_message(const IndexPricesMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->market_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price[i]; }
  for (size_t i = 0; i < 30; i++) { wire[at++] = record->short_name[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->published_date_time[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->valuation_date_applying_date[i]; }
  wire[at++] = record->status;

  return at;
}

/* Index Prices Message off the wire: 61 bytes from at, returning where the next byte lies */
static size_t decode_index_prices_message(IndexPricesMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->market_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->price[i] = wire[at++]; }
  for (size_t i = 0; i < 30; i++) { record->short_name[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->published_date_time[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->valuation_date_applying_date[i] = wire[at++]; }
  record->status = wire[at++];

  return at;
}

/* what was read of Index Prices Message is what was written, byte for byte */
static void equal_index_prices_message(const IndexPricesMessage *read, const IndexPricesMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->market_id[i] == written->market_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->price[i] == written->price[i]); }
  for (size_t i = 0; i < 30; i++) { assert(read->short_name[i] == written->short_name[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->published_date_time[i] == written->published_date_time[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->valuation_date_applying_date[i] == written->valuation_date_applying_date[i]); }
  assert(read->status == written->status);
}

/* Index Prices Message: written and read back, then read and written back */
static void check_index_prices_message(void) {
  IndexPricesMessage sent;
  IndexPricesMessage got;
  uint8_t wire[61];
  uint8_t again[61];

  any_index_prices_message(&sent);
  assert(encode_index_prices_message(&sent, wire, 0) == 61);
  assert(decode_index_prices_message(&got, wire, 0) == 61);
  equal_index_prices_message(&got, &sent);

  for (size_t i = 0; i < 61; i++) { wire[i] = arbitrary(); }
  assert(decode_index_prices_message(&got, wire, 0) == 61);
  assert(encode_index_prices_message(&got, again, 0) == 61);
  for (size_t i = 0; i < 61; i++) { assert(again[i] == wire[i]); }
}

/* ---- End Of Day Market Summary Message: 80 bytes ----------------------------- */

/* The message is streamed to client when market is closed and settlement price is available for the current trading day. */
typedef struct {
  uint8_t market_id[4];                                   /* bytes 0 to 3 */
  uint8_t volume[4];                                      /* bytes 4 to 7 */
  uint8_t block_volume[4];                                /* bytes 8 to 11 */
  uint8_t efs_volume[4];                                  /* bytes 12 to 15 */
  uint8_t efp_volume[4];                                  /* bytes 16 to 19 */
  uint8_t opening_price[8];                               /* bytes 20 to 27 */
  uint8_t high[8];                                        /* bytes 28 to 35 */
  uint8_t low[8];                                         /* bytes 36 to 43 */
  uint8_t vwap[8];                                        /* bytes 44 to 51 */
  uint8_t settlement_price_with_deal_price_precision[8];  /* bytes 52 to 59 */
  uint8_t open_interest[4];                               /* bytes 60 to 63 */
  uint8_t message_date_time[8];                           /* bytes 64 to 71 */
  uint8_t settlement_price[8];                            /* bytes 72 to 79 */
} EndOfDayMarketSummaryMessage;

/* any End Of Day Market Summary Message at all: every byte one the checker chooses */
static void any_end_of_day_market_summary_message(EndOfDayMarketSummaryMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->market_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->volume[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->block_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->efs_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->efp_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->opening_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->high[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->low[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->vwap[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->settlement_price_with_deal_price_precision[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->open_interest[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->message_date_time[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->settlement_price[i] = arbitrary(); }
}

/* End Of Day Market Summary Message to the wire: 80 bytes from at, returning where the next byte goes */
static size_t encode_end_of_day_market_summary_message(const EndOfDayMarketSummaryMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->market_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->volume[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->block_volume[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->efs_volume[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->efp_volume[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->opening_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->high[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->low[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->vwap[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->settlement_price_with_deal_price_precision[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->open_interest[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->message_date_time[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->settlement_price[i]; }

  return at;
}

/* End Of Day Market Summary Message off the wire: 80 bytes from at, returning where the next byte lies */
static size_t decode_end_of_day_market_summary_message(EndOfDayMarketSummaryMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->market_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->volume[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->block_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->efs_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->efp_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->opening_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->high[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->low[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->vwap[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->settlement_price_with_deal_price_precision[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->open_interest[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->message_date_time[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->settlement_price[i] = wire[at++]; }

  return at;
}

/* what was read of End Of Day Market Summary Message is what was written, byte for byte */
static void equal_end_of_day_market_summary_message(const EndOfDayMarketSummaryMessage *read, const EndOfDayMarketSummaryMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->market_id[i] == written->market_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->volume[i] == written->volume[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->block_volume[i] == written->block_volume[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->efs_volume[i] == written->efs_volume[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->efp_volume[i] == written->efp_volume[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->opening_price[i] == written->opening_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->high[i] == written->high[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->low[i] == written->low[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->vwap[i] == written->vwap[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->settlement_price_with_deal_price_precision[i] == written->settlement_price_with_deal_price_precision[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->open_interest[i] == written->open_interest[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->message_date_time[i] == written->message_date_time[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->settlement_price[i] == written->settlement_price[i]); }
}

/* End Of Day Market Summary Message: written and read back, then read and written back */
static void check_end_of_day_market_summary_message(void) {
  EndOfDayMarketSummaryMessage sent;
  EndOfDayMarketSummaryMessage got;
  uint8_t wire[80];
  uint8_t again[80];

  any_end_of_day_market_summary_message(&sent);
  assert(encode_end_of_day_market_summary_message(&sent, wire, 0) == 80);
  assert(decode_end_of_day_market_summary_message(&got, wire, 0) == 80);
  equal_end_of_day_market_summary_message(&got, &sent);

  for (size_t i = 0; i < 80; i++) { wire[i] = arbitrary(); }
  assert(decode_end_of_day_market_summary_message(&got, wire, 0) == 80);
  assert(encode_end_of_day_market_summary_message(&got, again, 0) == 80);
  for (size_t i = 0; i < 80; i++) { assert(again[i] == wire[i]); }
}

/* ---- Market Event Message: 13 bytes ------------------------------------------ */

/* End of Day Market Summary Message */
typedef struct {
  uint8_t market_id[4];          /* bytes 0 to 3 */
  uint8_t event_type;            /* byte 4 */
  uint8_t message_date_time[8];  /* bytes 5 to 12 */
} MarketEventMessage;

/* any Market Event Message at all: every byte one the checker chooses */
static void any_market_event_message(MarketEventMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->market_id[i] = arbitrary(); }
  record->event_type = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->message_date_time[i] = arbitrary(); }
}

/* Market Event Message to the wire: 13 bytes from at, returning where the next byte goes */
static size_t encode_market_event_message(const MarketEventMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->market_id[i]; }
  wire[at++] = record->event_type;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->message_date_time[i]; }

  return at;
}

/* Market Event Message off the wire: 13 bytes from at, returning where the next byte lies */
static size_t decode_market_event_message(MarketEventMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->market_id[i] = wire[at++]; }
  record->event_type = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->message_date_time[i] = wire[at++]; }

  return at;
}

/* what was read of Market Event Message is what was written, byte for byte */
static void equal_market_event_message(const MarketEventMessage *read, const MarketEventMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->market_id[i] == written->market_id[i]); }
  assert(read->event_type == written->event_type);
  for (size_t i = 0; i < 8; i++) { assert(read->message_date_time[i] == written->message_date_time[i]); }
}

/* Market Event Message: written and read back, then read and written back */
static void check_market_event_message(void) {
  MarketEventMessage sent;
  MarketEventMessage got;
  uint8_t wire[13];
  uint8_t again[13];

  any_market_event_message(&sent);
  assert(encode_market_event_message(&sent, wire, 0) == 13);
  assert(decode_market_event_message(&got, wire, 0) == 13);
  equal_market_event_message(&got, &sent);

  for (size_t i = 0; i < 13; i++) { wire[i] = arbitrary(); }
  assert(decode_market_event_message(&got, wire, 0) == 13);
  assert(encode_market_event_message(&got, again, 0) == 13);
  for (size_t i = 0; i < 13; i++) { assert(again[i] == wire[i]); }
}

/* ---- Pre Open Price Indicator Message: 25 bytes ------------------------------ */

/* This message contains the estimate of what the opening price could be, based on the orders in the market or previous settlement price. */
typedef struct {
  uint8_t market_id[4];          /* bytes 0 to 3 */
  uint8_t pre_open_price[8];     /* bytes 4 to 11 */
  uint8_t message_date_time[8];  /* bytes 12 to 19 */
  uint8_t has_pre_open_volume;   /* byte 20 */
  uint8_t pre_open_volume[4];    /* bytes 21 to 24 */
} PreOpenPriceIndicatorMessage;

/* any Pre Open Price Indicator Message at all: every byte one the checker chooses */
static void any_pre_open_price_indicator_message(PreOpenPriceIndicatorMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->market_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->pre_open_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->message_date_time[i] = arbitrary(); }
  record->has_pre_open_volume = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->pre_open_volume[i] = arbitrary(); }
}

/* Pre Open Price Indicator Message to the wire: 25 bytes from at, returning where the next byte goes */
static size_t encode_pre_open_price_indicator_message(const PreOpenPriceIndicatorMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->market_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->pre_open_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->message_date_time[i]; }
  wire[at++] = record->has_pre_open_volume;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->pre_open_volume[i]; }

  return at;
}

/* Pre Open Price Indicator Message off the wire: 25 bytes from at, returning where the next byte lies */
static size_t decode_pre_open_price_indicator_message(PreOpenPriceIndicatorMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->market_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->pre_open_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->message_date_time[i] = wire[at++]; }
  record->has_pre_open_volume = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->pre_open_volume[i] = wire[at++]; }

  return at;
}

/* what was read of Pre Open Price Indicator Message is what was written, byte for byte */
static void equal_pre_open_price_indicator_message(const PreOpenPriceIndicatorMessage *read, const PreOpenPriceIndicatorMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->market_id[i] == written->market_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->pre_open_price[i] == written->pre_open_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->message_date_time[i] == written->message_date_time[i]); }
  assert(read->has_pre_open_volume == written->has_pre_open_volume);
  for (size_t i = 0; i < 4; i++) { assert(read->pre_open_volume[i] == written->pre_open_volume[i]); }
}

/* Pre Open Price Indicator Message: written and read back, then read and written back */
static void check_pre_open_price_indicator_message(void) {
  PreOpenPriceIndicatorMessage sent;
  PreOpenPriceIndicatorMessage got;
  uint8_t wire[25];
  uint8_t again[25];

  any_pre_open_price_indicator_message(&sent);
  assert(encode_pre_open_price_indicator_message(&sent, wire, 0) == 25);
  assert(decode_pre_open_price_indicator_message(&got, wire, 0) == 25);
  equal_pre_open_price_indicator_message(&got, &sent);

  for (size_t i = 0; i < 25; i++) { wire[i] = arbitrary(); }
  assert(decode_pre_open_price_indicator_message(&got, wire, 0) == 25);
  assert(encode_pre_open_price_indicator_message(&got, again, 0) == 25);
  for (size_t i = 0; i < 25; i++) { assert(again[i] == wire[i]); }
}

/* ---- Strip Info Message: 88 bytes -------------------------------------------- */

/* This message will be sent out if there is strip date change during the trading session. If client does not care about strip date changes, client should ignore these messages. */
typedef struct {
  uint8_t old_strip_id[2];  /* bytes 0 to 1 */
  uint8_t strip_type[20];   /* bytes 2 to 21 */
  uint8_t begin_year[2];    /* bytes 22 to 23 */
  uint8_t begin_month[2];   /* bytes 24 to 25 */
  uint8_t begin_day[2];     /* bytes 26 to 27 */
  uint8_t end_year[2];      /* bytes 28 to 29 */
  uint8_t end_month[2];     /* bytes 30 to 31 */
  uint8_t end_day[2];       /* bytes 32 to 33 */
  uint8_t strip_info[50];   /* bytes 34 to 83 */
  uint8_t strip_id[4];      /* bytes 84 to 87 */
} StripInfoMessage;

/* any Strip Info Message at all: every byte one the checker chooses */
static void any_strip_info_message(StripInfoMessage *record) {
  for (size_t i = 0; i < 2; i++) { record->old_strip_id[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->strip_type[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->begin_year[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->begin_month[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->begin_day[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->end_year[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->end_month[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->end_day[i] = arbitrary(); }
  for (size_t i = 0; i < 50; i++) { record->strip_info[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->strip_id[i] = arbitrary(); }
}

/* Strip Info Message to the wire: 88 bytes from at, returning where the next byte goes */
static size_t encode_strip_info_message(const StripInfoMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->old_strip_id[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->strip_type[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->begin_year[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->begin_month[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->begin_day[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->end_year[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->end_month[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->end_day[i]; }
  for (size_t i = 0; i < 50; i++) { wire[at++] = record->strip_info[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->strip_id[i]; }

  return at;
}

/* Strip Info Message off the wire: 88 bytes from at, returning where the next byte lies */
static size_t decode_strip_info_message(StripInfoMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->old_strip_id[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->strip_type[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->begin_year[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->begin_month[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->begin_day[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->end_year[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->end_month[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->end_day[i] = wire[at++]; }
  for (size_t i = 0; i < 50; i++) { record->strip_info[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->strip_id[i] = wire[at++]; }

  return at;
}

/* what was read of Strip Info Message is what was written, byte for byte */
static void equal_strip_info_message(const StripInfoMessage *read, const StripInfoMessage *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->old_strip_id[i] == written->old_strip_id[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->strip_type[i] == written->strip_type[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->begin_year[i] == written->begin_year[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->begin_month[i] == written->begin_month[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->begin_day[i] == written->begin_day[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->end_year[i] == written->end_year[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->end_month[i] == written->end_month[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->end_day[i] == written->end_day[i]); }
  for (size_t i = 0; i < 50; i++) { assert(read->strip_info[i] == written->strip_info[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->strip_id[i] == written->strip_id[i]); }
}

/* Strip Info Message: written and read back, then read and written back */
static void check_strip_info_message(void) {
  StripInfoMessage sent;
  StripInfoMessage got;
  uint8_t wire[88];
  uint8_t again[88];

  any_strip_info_message(&sent);
  assert(encode_strip_info_message(&sent, wire, 0) == 88);
  assert(decode_strip_info_message(&got, wire, 0) == 88);
  equal_strip_info_message(&got, &sent);

  for (size_t i = 0; i < 88; i++) { wire[i] = arbitrary(); }
  assert(decode_strip_info_message(&got, wire, 0) == 88);
  assert(encode_strip_info_message(&got, again, 0) == 88);
  for (size_t i = 0; i < 88; i++) { assert(again[i] == wire[i]); }
}

/* ---- Interval Price Limit Notification Message: 34 bytes --------------------- */

/* Interval Price Limit (IPL) might be enabled for certain markets. IPL check is to prevent sudden movements (in both directions) in the market during a short period of time. */
typedef struct {
  uint8_t market_id[4];               /* bytes 0 to 3 */
  uint8_t ipl_hold_type;              /* byte 4 */
  uint8_t notification_date_time[8];  /* bytes 5 to 12 */
  uint8_t is_up;                      /* byte 13 */
  uint8_t ipl_hold_duration[4];       /* bytes 14 to 17 */
  uint8_t ipl_up[8];                  /* bytes 18 to 25 */
  uint8_t ipl_down[8];                /* bytes 26 to 33 */
} IntervalPriceLimitNotificationMessage;

/* any Interval Price Limit Notification Message at all: every byte one the checker chooses */
static void any_interval_price_limit_notification_message(IntervalPriceLimitNotificationMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->market_id[i] = arbitrary(); }
  record->ipl_hold_type = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->notification_date_time[i] = arbitrary(); }
  record->is_up = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->ipl_hold_duration[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->ipl_up[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->ipl_down[i] = arbitrary(); }
}

/* Interval Price Limit Notification Message to the wire: 34 bytes from at, returning where the next byte goes */
static size_t encode_interval_price_limit_notification_message(const IntervalPriceLimitNotificationMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->market_id[i]; }
  wire[at++] = record->ipl_hold_type;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->notification_date_time[i]; }
  wire[at++] = record->is_up;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->ipl_hold_duration[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->ipl_up[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->ipl_down[i]; }

  return at;
}

/* Interval Price Limit Notification Message off the wire: 34 bytes from at, returning where the next byte lies */
static size_t decode_interval_price_limit_notification_message(IntervalPriceLimitNotificationMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->market_id[i] = wire[at++]; }
  record->ipl_hold_type = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->notification_date_time[i] = wire[at++]; }
  record->is_up = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->ipl_hold_duration[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->ipl_up[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->ipl_down[i] = wire[at++]; }

  return at;
}

/* what was read of Interval Price Limit Notification Message is what was written, byte for byte */
static void equal_interval_price_limit_notification_message(const IntervalPriceLimitNotificationMessage *read, const IntervalPriceLimitNotificationMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->market_id[i] == written->market_id[i]); }
  assert(read->ipl_hold_type == written->ipl_hold_type);
  for (size_t i = 0; i < 8; i++) { assert(read->notification_date_time[i] == written->notification_date_time[i]); }
  assert(read->is_up == written->is_up);
  for (size_t i = 0; i < 4; i++) { assert(read->ipl_hold_duration[i] == written->ipl_hold_duration[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->ipl_up[i] == written->ipl_up[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->ipl_down[i] == written->ipl_down[i]); }
}

/* Interval Price Limit Notification Message: written and read back, then read and written back */
static void check_interval_price_limit_notification_message(void) {
  IntervalPriceLimitNotificationMessage sent;
  IntervalPriceLimitNotificationMessage got;
  uint8_t wire[34];
  uint8_t again[34];

  any_interval_price_limit_notification_message(&sent);
  assert(encode_interval_price_limit_notification_message(&sent, wire, 0) == 34);
  assert(decode_interval_price_limit_notification_message(&got, wire, 0) == 34);
  equal_interval_price_limit_notification_message(&got, &sent);

  for (size_t i = 0; i < 34; i++) { wire[i] = arbitrary(); }
  assert(decode_interval_price_limit_notification_message(&got, wire, 0) == 34);
  assert(encode_interval_price_limit_notification_message(&got, again, 0) == 34);
  for (size_t i = 0; i < 34; i++) { assert(again[i] == wire[i]); }
}

/* ---- New Expiry Message: 503 bytes ------------------------------------------- */

/* New Expiry message will be sent out when a new equity market is created during the day. */
typedef struct {
  uint8_t market_id[4];                            /* bytes 0 to 3 */
  uint8_t market_type_id[2];                       /* bytes 4 to 5 */
  uint8_t order_price_denominator;                 /* byte 6 */
  uint8_t increment_price[4];                      /* bytes 7 to 10 */
  uint8_t increment_qty[4];                        /* bytes 11 to 14 */
  uint8_t lot_size[4];                             /* bytes 15 to 18 */
  uint8_t market_desc[120];                        /* bytes 19 to 138 */
  uint8_t maturity_year[2];                        /* bytes 139 to 140 */
  uint8_t maturity_month[2];                       /* bytes 141 to 142 */
  uint8_t maturity_day[2];                         /* bytes 143 to 144 */
  uint8_t deal_price_denominator;                  /* byte 145 */
  uint8_t min_qty[4];                              /* bytes 146 to 149 */
  uint8_t unit_quantity[4];                        /* bytes 150 to 153 */
  uint8_t currency[20];                            /* bytes 154 to 173 */
  uint8_t cleared_alias[15];                       /* bytes 174 to 188 */
  uint8_t min_price[8];                            /* bytes 189 to 196 */
  uint8_t max_price[8];                            /* bytes 197 to 204 */
  uint8_t product_id[4];                           /* bytes 205 to 208 */
  uint8_t product_name[62];                        /* bytes 209 to 270 */
  uint8_t hub_id[4];                               /* bytes 271 to 274 */
  uint8_t hub_alias[80];                           /* bytes 275 to 354 */
  uint8_t strip_id[4];                             /* bytes 355 to 358 */
  uint8_t strip_name[39];                          /* bytes 359 to 397 */
  uint8_t settle_price_denominator;                /* byte 398 */
  uint8_t mic_code[4];                             /* bytes 399 to 402 */
  uint8_t unit_qty_denominator;                    /* byte 403 */
  uint8_t off_exchange_increment_qty_denominator;  /* byte 404 */
  uint8_t off_exchange_increment_qty[4];           /* bytes 405 to 408 */
  uint8_t off_exchange_increment_price[4];         /* bytes 409 to 412 */
  uint8_t off_exchange_increment_option_price[4];  /* bytes 413 to 416 */
  uint8_t contract_symbol[35];                     /* bytes 417 to 451 */
  uint8_t isin[12];                                /* bytes 452 to 463 */
  uint8_t num_decimals_options_price;              /* byte 464 */
  uint8_t hedge_market_id[4];                      /* bytes 465 to 468 */
  uint8_t settlement_type;                         /* byte 469 */
  uint8_t gt_allowed;                              /* byte 470 */
  uint8_t cross_order_supported;                   /* byte 471 */
  uint8_t unit_of_measure[30];                     /* bytes 472 to 501 */
  uint8_t mifid_regulated_market;                  /* byte 502 */
} NewExpiryMessage;

/* any New Expiry Message at all: every byte one the checker chooses */
static void any_new_expiry_message(NewExpiryMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->market_id[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->market_type_id[i] = arbitrary(); }
  record->order_price_denominator = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->increment_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->increment_qty[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->lot_size[i] = arbitrary(); }
  for (size_t i = 0; i < 120; i++) { record->market_desc[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->maturity_year[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->maturity_month[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->maturity_day[i] = arbitrary(); }
  record->deal_price_denominator = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->min_qty[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->unit_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->currency[i] = arbitrary(); }
  for (size_t i = 0; i < 15; i++) { record->cleared_alias[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->min_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->max_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->product_id[i] = arbitrary(); }
  for (size_t i = 0; i < 62; i++) { record->product_name[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->hub_id[i] = arbitrary(); }
  for (size_t i = 0; i < 80; i++) { record->hub_alias[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->strip_id[i] = arbitrary(); }
  for (size_t i = 0; i < 39; i++) { record->strip_name[i] = arbitrary(); }
  record->settle_price_denominator = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->mic_code[i] = arbitrary(); }
  record->unit_qty_denominator = arbitrary();
  record->off_exchange_increment_qty_denominator = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->off_exchange_increment_qty[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->off_exchange_increment_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->off_exchange_increment_option_price[i] = arbitrary(); }
  for (size_t i = 0; i < 35; i++) { record->contract_symbol[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->isin[i] = arbitrary(); }
  record->num_decimals_options_price = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->hedge_market_id[i] = arbitrary(); }
  record->settlement_type = arbitrary();
  record->gt_allowed = arbitrary();
  record->cross_order_supported = arbitrary();
  for (size_t i = 0; i < 30; i++) { record->unit_of_measure[i] = arbitrary(); }
  record->mifid_regulated_market = arbitrary();
}

/* New Expiry Message to the wire: 503 bytes from at, returning where the next byte goes */
static size_t encode_new_expiry_message(const NewExpiryMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->market_id[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->market_type_id[i]; }
  wire[at++] = record->order_price_denominator;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->increment_price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->increment_qty[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->lot_size[i]; }
  for (size_t i = 0; i < 120; i++) { wire[at++] = record->market_desc[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->maturity_year[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->maturity_month[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->maturity_day[i]; }
  wire[at++] = record->deal_price_denominator;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->min_qty[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->unit_quantity[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->currency[i]; }
  for (size_t i = 0; i < 15; i++) { wire[at++] = record->cleared_alias[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->min_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->max_price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->product_id[i]; }
  for (size_t i = 0; i < 62; i++) { wire[at++] = record->product_name[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->hub_id[i]; }
  for (size_t i = 0; i < 80; i++) { wire[at++] = record->hub_alias[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->strip_id[i]; }
  for (size_t i = 0; i < 39; i++) { wire[at++] = record->strip_name[i]; }
  wire[at++] = record->settle_price_denominator;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->mic_code[i]; }
  wire[at++] = record->unit_qty_denominator;
  wire[at++] = record->off_exchange_increment_qty_denominator;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->off_exchange_increment_qty[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->off_exchange_increment_price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->off_exchange_increment_option_price[i]; }
  for (size_t i = 0; i < 35; i++) { wire[at++] = record->contract_symbol[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->isin[i]; }
  wire[at++] = record->num_decimals_options_price;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->hedge_market_id[i]; }
  wire[at++] = record->settlement_type;
  wire[at++] = record->gt_allowed;
  wire[at++] = record->cross_order_supported;
  for (size_t i = 0; i < 30; i++) { wire[at++] = record->unit_of_measure[i]; }
  wire[at++] = record->mifid_regulated_market;

  return at;
}

/* New Expiry Message off the wire: 503 bytes from at, returning where the next byte lies */
static size_t decode_new_expiry_message(NewExpiryMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->market_id[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->market_type_id[i] = wire[at++]; }
  record->order_price_denominator = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->increment_price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->increment_qty[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->lot_size[i] = wire[at++]; }
  for (size_t i = 0; i < 120; i++) { record->market_desc[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->maturity_year[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->maturity_month[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->maturity_day[i] = wire[at++]; }
  record->deal_price_denominator = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->min_qty[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->unit_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->currency[i] = wire[at++]; }
  for (size_t i = 0; i < 15; i++) { record->cleared_alias[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->min_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->max_price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->product_id[i] = wire[at++]; }
  for (size_t i = 0; i < 62; i++) { record->product_name[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->hub_id[i] = wire[at++]; }
  for (size_t i = 0; i < 80; i++) { record->hub_alias[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->strip_id[i] = wire[at++]; }
  for (size_t i = 0; i < 39; i++) { record->strip_name[i] = wire[at++]; }
  record->settle_price_denominator = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->mic_code[i] = wire[at++]; }
  record->unit_qty_denominator = wire[at++];
  record->off_exchange_increment_qty_denominator = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->off_exchange_increment_qty[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->off_exchange_increment_price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->off_exchange_increment_option_price[i] = wire[at++]; }
  for (size_t i = 0; i < 35; i++) { record->contract_symbol[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->isin[i] = wire[at++]; }
  record->num_decimals_options_price = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->hedge_market_id[i] = wire[at++]; }
  record->settlement_type = wire[at++];
  record->gt_allowed = wire[at++];
  record->cross_order_supported = wire[at++];
  for (size_t i = 0; i < 30; i++) { record->unit_of_measure[i] = wire[at++]; }
  record->mifid_regulated_market = wire[at++];

  return at;
}

/* what was read of New Expiry Message is what was written, byte for byte */
static void equal_new_expiry_message(const NewExpiryMessage *read, const NewExpiryMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->market_id[i] == written->market_id[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->market_type_id[i] == written->market_type_id[i]); }
  assert(read->order_price_denominator == written->order_price_denominator);
  for (size_t i = 0; i < 4; i++) { assert(read->increment_price[i] == written->increment_price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->increment_qty[i] == written->increment_qty[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->lot_size[i] == written->lot_size[i]); }
  for (size_t i = 0; i < 120; i++) { assert(read->market_desc[i] == written->market_desc[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->maturity_year[i] == written->maturity_year[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->maturity_month[i] == written->maturity_month[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->maturity_day[i] == written->maturity_day[i]); }
  assert(read->deal_price_denominator == written->deal_price_denominator);
  for (size_t i = 0; i < 4; i++) { assert(read->min_qty[i] == written->min_qty[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->unit_quantity[i] == written->unit_quantity[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->currency[i] == written->currency[i]); }
  for (size_t i = 0; i < 15; i++) { assert(read->cleared_alias[i] == written->cleared_alias[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->min_price[i] == written->min_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->max_price[i] == written->max_price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->product_id[i] == written->product_id[i]); }
  for (size_t i = 0; i < 62; i++) { assert(read->product_name[i] == written->product_name[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->hub_id[i] == written->hub_id[i]); }
  for (size_t i = 0; i < 80; i++) { assert(read->hub_alias[i] == written->hub_alias[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->strip_id[i] == written->strip_id[i]); }
  for (size_t i = 0; i < 39; i++) { assert(read->strip_name[i] == written->strip_name[i]); }
  assert(read->settle_price_denominator == written->settle_price_denominator);
  for (size_t i = 0; i < 4; i++) { assert(read->mic_code[i] == written->mic_code[i]); }
  assert(read->unit_qty_denominator == written->unit_qty_denominator);
  assert(read->off_exchange_increment_qty_denominator == written->off_exchange_increment_qty_denominator);
  for (size_t i = 0; i < 4; i++) { assert(read->off_exchange_increment_qty[i] == written->off_exchange_increment_qty[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->off_exchange_increment_price[i] == written->off_exchange_increment_price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->off_exchange_increment_option_price[i] == written->off_exchange_increment_option_price[i]); }
  for (size_t i = 0; i < 35; i++) { assert(read->contract_symbol[i] == written->contract_symbol[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->isin[i] == written->isin[i]); }
  assert(read->num_decimals_options_price == written->num_decimals_options_price);
  for (size_t i = 0; i < 4; i++) { assert(read->hedge_market_id[i] == written->hedge_market_id[i]); }
  assert(read->settlement_type == written->settlement_type);
  assert(read->gt_allowed == written->gt_allowed);
  assert(read->cross_order_supported == written->cross_order_supported);
  for (size_t i = 0; i < 30; i++) { assert(read->unit_of_measure[i] == written->unit_of_measure[i]); }
  assert(read->mifid_regulated_market == written->mifid_regulated_market);
}

/* New Expiry Message: written and read back, then read and written back */
static void check_new_expiry_message(void) {
  NewExpiryMessage sent;
  NewExpiryMessage got;
  uint8_t wire[503];
  uint8_t again[503];

  any_new_expiry_message(&sent);
  assert(encode_new_expiry_message(&sent, wire, 0) == 503);
  assert(decode_new_expiry_message(&got, wire, 0) == 503);
  equal_new_expiry_message(&got, &sent);

  for (size_t i = 0; i < 503; i++) { wire[i] = arbitrary(); }
  assert(decode_new_expiry_message(&got, wire, 0) == 503);
  assert(encode_new_expiry_message(&got, again, 0) == 503);
  for (size_t i = 0; i < 503; i++) { assert(again[i] == wire[i]); }
}

/* ---- Market Snapshot Order Message: 41 bytes --------------------------------- */

/* This message is for orders in snapshot only. It is different from the order message for incremental updates. */
typedef struct {
  uint8_t market_id[4];               /* bytes 0 to 3 */
  uint8_t order_id[8];                /* bytes 4 to 11 */
  uint8_t order_sequence_id[2];       /* bytes 12 to 13 */
  uint8_t side;                       /* byte 14 */
  uint8_t price[8];                   /* bytes 15 to 22 */
  uint8_t quantity[4];                /* bytes 23 to 26 */
  uint8_t is_implied;                 /* byte 27 */
  uint8_t is_rfq;                     /* byte 28 */
  uint8_t order_entry_date_time[8];   /* bytes 29 to 36 */
  uint8_t sequence_within_millis[4];  /* bytes 37 to 40 */
} MarketSnapshotOrderMessage;

/* any Market Snapshot Order Message at all: every byte one the checker chooses */
static void any_market_snapshot_order_message(MarketSnapshotOrderMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->market_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->order_sequence_id[i] = arbitrary(); }
  record->side = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->quantity[i] = arbitrary(); }
  record->is_implied = arbitrary();
  record->is_rfq = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->order_entry_date_time[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->sequence_within_millis[i] = arbitrary(); }
}

/* Market Snapshot Order Message to the wire: 41 bytes from at, returning where the next byte goes */
static size_t encode_market_snapshot_order_message(const MarketSnapshotOrderMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->market_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_id[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->order_sequence_id[i]; }
  wire[at++] = record->side;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->quantity[i]; }
  wire[at++] = record->is_implied;
  wire[at++] = record->is_rfq;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_entry_date_time[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->sequence_within_millis[i]; }

  return at;
}

/* Market Snapshot Order Message off the wire: 41 bytes from at, returning where the next byte lies */
static size_t decode_market_snapshot_order_message(MarketSnapshotOrderMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->market_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->order_sequence_id[i] = wire[at++]; }
  record->side = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->quantity[i] = wire[at++]; }
  record->is_implied = wire[at++];
  record->is_rfq = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->order_entry_date_time[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->sequence_within_millis[i] = wire[at++]; }

  return at;
}

/* what was read of Market Snapshot Order Message is what was written, byte for byte */
static void equal_market_snapshot_order_message(const MarketSnapshotOrderMessage *read, const MarketSnapshotOrderMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->market_id[i] == written->market_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->order_id[i] == written->order_id[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->order_sequence_id[i] == written->order_sequence_id[i]); }
  assert(read->side == written->side);
  for (size_t i = 0; i < 8; i++) { assert(read->price[i] == written->price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->quantity[i] == written->quantity[i]); }
  assert(read->is_implied == written->is_implied);
  assert(read->is_rfq == written->is_rfq);
  for (size_t i = 0; i < 8; i++) { assert(read->order_entry_date_time[i] == written->order_entry_date_time[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->sequence_within_millis[i] == written->sequence_within_millis[i]); }
}

/* Market Snapshot Order Message: written and read back, then read and written back */
static void check_market_snapshot_order_message(void) {
  MarketSnapshotOrderMessage sent;
  MarketSnapshotOrderMessage got;
  uint8_t wire[41];
  uint8_t again[41];

  any_market_snapshot_order_message(&sent);
  assert(encode_market_snapshot_order_message(&sent, wire, 0) == 41);
  assert(decode_market_snapshot_order_message(&got, wire, 0) == 41);
  equal_market_snapshot_order_message(&got, &sent);

  for (size_t i = 0; i < 41; i++) { wire[i] = arbitrary(); }
  assert(decode_market_snapshot_order_message(&got, wire, 0) == 41);
  assert(encode_market_snapshot_order_message(&got, again, 0) == 41);
  for (size_t i = 0; i < 41; i++) { assert(again[i] == wire[i]); }
}

/* ---- Add Or Modify Order Message: 50 bytes ----------------------------------- */

/* Client should add the order to book if it is not there already. Otherwise, just overwrite the existing order. */
typedef struct {
  uint8_t market_id[4];               /* bytes 0 to 3 */
  uint8_t order_id[8];                /* bytes 4 to 11 */
  uint8_t order_sequence_id[2];       /* bytes 12 to 13 */
  uint8_t side;                       /* byte 14 */
  uint8_t price[8];                   /* bytes 15 to 22 */
  uint8_t quantity[4];                /* bytes 23 to 26 */
  uint8_t is_implied;                 /* byte 27 */
  uint8_t is_rfq;                     /* byte 28 */
  uint8_t order_entry_date_time[8];   /* bytes 29 to 36 */
  uint8_t extra_flags;                /* byte 37 */
  uint8_t sequence_within_millis[4];  /* bytes 38 to 41 */
  uint8_t modification_timestamp[8];  /* bytes 42 to 49 */
} AddOrModifyOrderMessage;

/* any Add Or Modify Order Message at all: every byte one the checker chooses */
static void any_add_or_modify_order_message(AddOrModifyOrderMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->market_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->order_sequence_id[i] = arbitrary(); }
  record->side = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->quantity[i] = arbitrary(); }
  record->is_implied = arbitrary();
  record->is_rfq = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->order_entry_date_time[i] = arbitrary(); }
  record->extra_flags = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->sequence_within_millis[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->modification_timestamp[i] = arbitrary(); }
}

/* Add Or Modify Order Message to the wire: 50 bytes from at, returning where the next byte goes */
static size_t encode_add_or_modify_order_message(const AddOrModifyOrderMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->market_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_id[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->order_sequence_id[i]; }
  wire[at++] = record->side;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->quantity[i]; }
  wire[at++] = record->is_implied;
  wire[at++] = record->is_rfq;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_entry_date_time[i]; }
  wire[at++] = record->extra_flags;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->sequence_within_millis[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->modification_timestamp[i]; }

  return at;
}

/* Add Or Modify Order Message off the wire: 50 bytes from at, returning where the next byte lies */
static size_t decode_add_or_modify_order_message(AddOrModifyOrderMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->market_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->order_sequence_id[i] = wire[at++]; }
  record->side = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->quantity[i] = wire[at++]; }
  record->is_implied = wire[at++];
  record->is_rfq = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->order_entry_date_time[i] = wire[at++]; }
  record->extra_flags = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->sequence_within_millis[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->modification_timestamp[i] = wire[at++]; }

  return at;
}

/* what was read of Add Or Modify Order Message is what was written, byte for byte */
static void equal_add_or_modify_order_message(const AddOrModifyOrderMessage *read, const AddOrModifyOrderMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->market_id[i] == written->market_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->order_id[i] == written->order_id[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->order_sequence_id[i] == written->order_sequence_id[i]); }
  assert(read->side == written->side);
  for (size_t i = 0; i < 8; i++) { assert(read->price[i] == written->price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->quantity[i] == written->quantity[i]); }
  assert(read->is_implied == written->is_implied);
  assert(read->is_rfq == written->is_rfq);
  for (size_t i = 0; i < 8; i++) { assert(read->order_entry_date_time[i] == written->order_entry_date_time[i]); }
  assert(read->extra_flags == written->extra_flags);
  for (size_t i = 0; i < 4; i++) { assert(read->sequence_within_millis[i] == written->sequence_within_millis[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->modification_timestamp[i] == written->modification_timestamp[i]); }
}

/* Add Or Modify Order Message: written and read back, then read and written back */
static void check_add_or_modify_order_message(void) {
  AddOrModifyOrderMessage sent;
  AddOrModifyOrderMessage got;
  uint8_t wire[50];
  uint8_t again[50];

  any_add_or_modify_order_message(&sent);
  assert(encode_add_or_modify_order_message(&sent, wire, 0) == 50);
  assert(decode_add_or_modify_order_message(&got, wire, 0) == 50);
  equal_add_or_modify_order_message(&got, &sent);

  for (size_t i = 0; i < 50; i++) { wire[i] = arbitrary(); }
  assert(decode_add_or_modify_order_message(&got, wire, 0) == 50);
  assert(encode_add_or_modify_order_message(&got, again, 0) == 50);
  for (size_t i = 0; i < 50; i++) { assert(again[i] == wire[i]); }
}

/* ---- Delete Order Message: 24 bytes ------------------------------------------ */

/* Upon receipt of this message, client should remove the order from its local book. */
typedef struct {
  uint8_t market_id[4];               /* bytes 0 to 3 */
  uint8_t order_id[8];                /* bytes 4 to 11 */
  uint8_t message_date_time[8];       /* bytes 12 to 19 */
  uint8_t sequence_within_millis[4];  /* bytes 20 to 23 */
} DeleteOrderMessage;

/* any Delete Order Message at all: every byte one the checker chooses */
static void any_delete_order_message(DeleteOrderMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->market_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->message_date_time[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->sequence_within_millis[i] = arbitrary(); }
}

/* Delete Order Message to the wire: 24 bytes from at, returning where the next byte goes */
static size_t encode_delete_order_message(const DeleteOrderMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->market_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->message_date_time[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->sequence_within_millis[i]; }

  return at;
}

/* Delete Order Message off the wire: 24 bytes from at, returning where the next byte lies */
static size_t decode_delete_order_message(DeleteOrderMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->market_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->message_date_time[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->sequence_within_millis[i] = wire[at++]; }

  return at;
}

/* what was read of Delete Order Message is what was written, byte for byte */
static void equal_delete_order_message(const DeleteOrderMessage *read, const DeleteOrderMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->market_id[i] == written->market_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->order_id[i] == written->order_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->message_date_time[i] == written->message_date_time[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->sequence_within_millis[i] == written->sequence_within_millis[i]); }
}

/* Delete Order Message: written and read back, then read and written back */
static void check_delete_order_message(void) {
  DeleteOrderMessage sent;
  DeleteOrderMessage got;
  uint8_t wire[24];
  uint8_t again[24];

  any_delete_order_message(&sent);
  assert(encode_delete_order_message(&sent, wire, 0) == 24);
  assert(decode_delete_order_message(&got, wire, 0) == 24);
  equal_delete_order_message(&got, &sent);

  for (size_t i = 0; i < 24; i++) { wire[i] = arbitrary(); }
  assert(decode_delete_order_message(&got, wire, 0) == 24);
  assert(encode_delete_order_message(&got, again, 0) == 24);
  for (size_t i = 0; i < 24; i++) { assert(again[i] == wire[i]); }
}

/* ---- Message Bundle Marker: 1 byte ------------------------------------------- */

/* This message indicates where a bundle of messages starts or ends. */
typedef struct {
  uint8_t start_or_end;  /* byte 0 */
} MessageBundleMarker;

/* any Message Bundle Marker at all: every byte one the checker chooses */
static void any_message_bundle_marker(MessageBundleMarker *record) {
  record->start_or_end = arbitrary();
}

/* Message Bundle Marker to the wire: 1 byte from at, returning where the next byte goes */
static size_t encode_message_bundle_marker(const MessageBundleMarker *record, uint8_t *wire, size_t at) {
  wire[at++] = record->start_or_end;

  return at;
}

/* Message Bundle Marker off the wire: 1 byte from at, returning where the next byte lies */
static size_t decode_message_bundle_marker(MessageBundleMarker *record, const uint8_t *wire, size_t at) {
  record->start_or_end = wire[at++];

  return at;
}

/* what was read of Message Bundle Marker is what was written, byte for byte */
static void equal_message_bundle_marker(const MessageBundleMarker *read, const MessageBundleMarker *written) {
  assert(read->start_or_end == written->start_or_end);
}

/* Message Bundle Marker: written and read back, then read and written back */
static void check_message_bundle_marker(void) {
  MessageBundleMarker sent;
  MessageBundleMarker got;
  uint8_t wire[1];
  uint8_t again[1];

  any_message_bundle_marker(&sent);
  assert(encode_message_bundle_marker(&sent, wire, 0) == 1);
  assert(decode_message_bundle_marker(&got, wire, 0) == 1);
  equal_message_bundle_marker(&got, &sent);

  for (size_t i = 0; i < 1; i++) { wire[i] = arbitrary(); }
  assert(decode_message_bundle_marker(&got, wire, 0) == 1);
  assert(encode_message_bundle_marker(&got, again, 0) == 1);
  for (size_t i = 0; i < 1; i++) { assert(again[i] == wire[i]); }
}

/* ---- Fixing Transition Message: 25 bytes ------------------------------------- */

/* This message supports ICE Benchmark Administration’s (IBA) electronic Gold Auction and it is disseminated when there is a transition of the fixing market. */
typedef struct {
  uint8_t market_id[4];                /* bytes 0 to 3 */
  uint8_t status;                      /* byte 4 */
  uint8_t auction_end_time[8];         /* bytes 5 to 12 */
  uint8_t threshold_imbalance_qty[4];  /* bytes 13 to 16 */
  uint8_t message_date_time[8];        /* bytes 17 to 24 */
} FixingTransitionMessage;

/* any Fixing Transition Message at all: every byte one the checker chooses */
static void any_fixing_transition_message(FixingTransitionMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->market_id[i] = arbitrary(); }
  record->status = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->auction_end_time[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->threshold_imbalance_qty[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->message_date_time[i] = arbitrary(); }
}

/* Fixing Transition Message to the wire: 25 bytes from at, returning where the next byte goes */
static size_t encode_fixing_transition_message(const FixingTransitionMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->market_id[i]; }
  wire[at++] = record->status;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->auction_end_time[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->threshold_imbalance_qty[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->message_date_time[i]; }

  return at;
}

/* Fixing Transition Message off the wire: 25 bytes from at, returning where the next byte lies */
static size_t decode_fixing_transition_message(FixingTransitionMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->market_id[i] = wire[at++]; }
  record->status = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->auction_end_time[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->threshold_imbalance_qty[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->message_date_time[i] = wire[at++]; }

  return at;
}

/* what was read of Fixing Transition Message is what was written, byte for byte */
static void equal_fixing_transition_message(const FixingTransitionMessage *read, const FixingTransitionMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->market_id[i] == written->market_id[i]); }
  assert(read->status == written->status);
  for (size_t i = 0; i < 8; i++) { assert(read->auction_end_time[i] == written->auction_end_time[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->threshold_imbalance_qty[i] == written->threshold_imbalance_qty[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->message_date_time[i] == written->message_date_time[i]); }
}

/* Fixing Transition Message: written and read back, then read and written back */
static void check_fixing_transition_message(void) {
  FixingTransitionMessage sent;
  FixingTransitionMessage got;
  uint8_t wire[25];
  uint8_t again[25];

  any_fixing_transition_message(&sent);
  assert(encode_fixing_transition_message(&sent, wire, 0) == 25);
  assert(decode_fixing_transition_message(&got, wire, 0) == 25);
  equal_fixing_transition_message(&got, &sent);

  for (size_t i = 0; i < 25; i++) { wire[i] = arbitrary(); }
  assert(decode_fixing_transition_message(&got, wire, 0) == 25);
  assert(encode_fixing_transition_message(&got, again, 0) == 25);
  for (size_t i = 0; i < 25; i++) { assert(again[i] == wire[i]); }
}

/* ---- Fixing Lockdown Message: 78 bytes --------------------------------------- */

/* This message supports ICE Benchmark Administration’s (IBA) electronic Gold Auction and it is disseminated when there is a transition of the fixing market. */
typedef struct {
  uint8_t market_id[4];          /* bytes 0 to 3 */
  uint8_t auction_date[10];      /* bytes 4 to 13 */
  uint8_t message_date_time[8];  /* bytes 14 to 21 */
  uint8_t description[20];       /* bytes 22 to 41 */
  uint8_t round[2];              /* bytes 42 to 43 */
  uint8_t agg_bid_qty[4];        /* bytes 44 to 47 */
  uint8_t agg_offer_qty[4];      /* bytes 48 to 51 */
  uint8_t usd_price[8];          /* bytes 52 to 59 */
  uint8_t is_balanced;           /* byte 60 */
  uint8_t is_final;              /* byte 61 */
  uint8_t gbp_price[8];          /* bytes 62 to 69 */
  uint8_t eur_price[8];          /* bytes 70 to 77 */
} FixingLockdownMessage;

/* any Fixing Lockdown Message at all: every byte one the checker chooses */
static void any_fixing_lockdown_message(FixingLockdownMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->market_id[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->auction_date[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->message_date_time[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->description[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->round[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->agg_bid_qty[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->agg_offer_qty[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->usd_price[i] = arbitrary(); }
  record->is_balanced = arbitrary();
  record->is_final = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->gbp_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->eur_price[i] = arbitrary(); }
}

/* Fixing Lockdown Message to the wire: 78 bytes from at, returning where the next byte goes */
static size_t encode_fixing_lockdown_message(const FixingLockdownMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->market_id[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->auction_date[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->message_date_time[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->description[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->round[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->agg_bid_qty[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->agg_offer_qty[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->usd_price[i]; }
  wire[at++] = record->is_balanced;
  wire[at++] = record->is_final;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->gbp_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->eur_price[i]; }

  return at;
}

/* Fixing Lockdown Message off the wire: 78 bytes from at, returning where the next byte lies */
static size_t decode_fixing_lockdown_message(FixingLockdownMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->market_id[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->auction_date[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->message_date_time[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->description[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->round[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->agg_bid_qty[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->agg_offer_qty[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->usd_price[i] = wire[at++]; }
  record->is_balanced = wire[at++];
  record->is_final = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->gbp_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->eur_price[i] = wire[at++]; }

  return at;
}

/* what was read of Fixing Lockdown Message is what was written, byte for byte */
static void equal_fixing_lockdown_message(const FixingLockdownMessage *read, const FixingLockdownMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->market_id[i] == written->market_id[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->auction_date[i] == written->auction_date[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->message_date_time[i] == written->message_date_time[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->description[i] == written->description[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->round[i] == written->round[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->agg_bid_qty[i] == written->agg_bid_qty[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->agg_offer_qty[i] == written->agg_offer_qty[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->usd_price[i] == written->usd_price[i]); }
  assert(read->is_balanced == written->is_balanced);
  assert(read->is_final == written->is_final);
  for (size_t i = 0; i < 8; i++) { assert(read->gbp_price[i] == written->gbp_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->eur_price[i] == written->eur_price[i]); }
}

/* Fixing Lockdown Message: written and read back, then read and written back */
static void check_fixing_lockdown_message(void) {
  FixingLockdownMessage sent;
  FixingLockdownMessage got;
  uint8_t wire[78];
  uint8_t again[78];

  any_fixing_lockdown_message(&sent);
  assert(encode_fixing_lockdown_message(&sent, wire, 0) == 78);
  assert(decode_fixing_lockdown_message(&got, wire, 0) == 78);
  equal_fixing_lockdown_message(&got, &sent);

  for (size_t i = 0; i < 78; i++) { wire[i] = arbitrary(); }
  assert(decode_fixing_lockdown_message(&got, wire, 0) == 78);
  assert(encode_fixing_lockdown_message(&got, again, 0) == 78);
  for (size_t i = 0; i < 78; i++) { assert(again[i] == wire[i]); }
}

/* ---- Fixing Indicative Price Message Message: 25 bytes ----------------------- */

/* This message supports ICE Benchmark Administration’s (IBA) electronic Gold and Silver Auction and is disseminated at the end of the final auction when the final price is published */
typedef struct {
  uint8_t market_id[4];                /* bytes 0 to 3 */
  uint8_t iba_currency[3];             /* bytes 4 to 6 */
  uint8_t price[8];                    /* bytes 7 to 14 */
  uint8_t price_in_gram[8];            /* bytes 15 to 22 */
  uint8_t num_decimals_price;          /* byte 23 */
  uint8_t num_decimals_price_in_gram;  /* byte 24 */
} FixingIndicativePriceMessageMessage;

/* any Fixing Indicative Price Message Message at all: every byte one the checker chooses */
static void any_fixing_indicative_price_message_message(FixingIndicativePriceMessageMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->market_id[i] = arbitrary(); }
  for (size_t i = 0; i < 3; i++) { record->iba_currency[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->price_in_gram[i] = arbitrary(); }
  record->num_decimals_price = arbitrary();
  record->num_decimals_price_in_gram = arbitrary();
}

/* Fixing Indicative Price Message Message to the wire: 25 bytes from at, returning where the next byte goes */
static size_t encode_fixing_indicative_price_message_message(const FixingIndicativePriceMessageMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->market_id[i]; }
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->iba_currency[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price_in_gram[i]; }
  wire[at++] = record->num_decimals_price;
  wire[at++] = record->num_decimals_price_in_gram;

  return at;
}

/* Fixing Indicative Price Message Message off the wire: 25 bytes from at, returning where the next byte lies */
static size_t decode_fixing_indicative_price_message_message(FixingIndicativePriceMessageMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->market_id[i] = wire[at++]; }
  for (size_t i = 0; i < 3; i++) { record->iba_currency[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->price_in_gram[i] = wire[at++]; }
  record->num_decimals_price = wire[at++];
  record->num_decimals_price_in_gram = wire[at++];

  return at;
}

/* what was read of Fixing Indicative Price Message Message is what was written, byte for byte */
static void equal_fixing_indicative_price_message_message(const FixingIndicativePriceMessageMessage *read, const FixingIndicativePriceMessageMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->market_id[i] == written->market_id[i]); }
  for (size_t i = 0; i < 3; i++) { assert(read->iba_currency[i] == written->iba_currency[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->price[i] == written->price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->price_in_gram[i] == written->price_in_gram[i]); }
  assert(read->num_decimals_price == written->num_decimals_price);
  assert(read->num_decimals_price_in_gram == written->num_decimals_price_in_gram);
}

/* Fixing Indicative Price Message Message: written and read back, then read and written back */
static void check_fixing_indicative_price_message_message(void) {
  FixingIndicativePriceMessageMessage sent;
  FixingIndicativePriceMessageMessage got;
  uint8_t wire[25];
  uint8_t again[25];

  any_fixing_indicative_price_message_message(&sent);
  assert(encode_fixing_indicative_price_message_message(&sent, wire, 0) == 25);
  assert(decode_fixing_indicative_price_message_message(&got, wire, 0) == 25);
  equal_fixing_indicative_price_message_message(&got, &sent);

  for (size_t i = 0; i < 25; i++) { wire[i] = arbitrary(); }
  assert(decode_fixing_indicative_price_message_message(&got, wire, 0) == 25);
  assert(encode_fixing_indicative_price_message_message(&got, again, 0) == 25);
  for (size_t i = 0; i < 25; i++) { assert(again[i] == wire[i]); }
}

/* ---- Market Snapshot Price Level Message: 26 bytes --------------------------- */

/* This message is for price level in snapshot only. */
typedef struct {
  uint8_t market_id[4];            /* bytes 0 to 3 */
  uint8_t side;                    /* byte 4 */
  uint8_t price_level_position;    /* byte 5 */
  uint8_t price[8];                /* bytes 6 to 13 */
  uint8_t quantity[4];             /* bytes 14 to 17 */
  uint8_t order_count[2];          /* bytes 18 to 19 */
  uint8_t implied_quantity[4];     /* bytes 20 to 23 */
  uint8_t implied_order_count[2];  /* bytes 24 to 25 */
} MarketSnapshotPriceLevelMessage;

/* any Market Snapshot Price Level Message at all: every byte one the checker chooses */
static void any_market_snapshot_price_level_message(MarketSnapshotPriceLevelMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->market_id[i] = arbitrary(); }
  record->side = arbitrary();
  record->price_level_position = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->order_count[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->implied_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->implied_order_count[i] = arbitrary(); }
}

/* Market Snapshot Price Level Message to the wire: 26 bytes from at, returning where the next byte goes */
static size_t encode_market_snapshot_price_level_message(const MarketSnapshotPriceLevelMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->market_id[i]; }
  wire[at++] = record->side;
  wire[at++] = record->price_level_position;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->quantity[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->order_count[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->implied_quantity[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->implied_order_count[i]; }

  return at;
}

/* Market Snapshot Price Level Message off the wire: 26 bytes from at, returning where the next byte lies */
static size_t decode_market_snapshot_price_level_message(MarketSnapshotPriceLevelMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->market_id[i] = wire[at++]; }
  record->side = wire[at++];
  record->price_level_position = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->order_count[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->implied_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->implied_order_count[i] = wire[at++]; }

  return at;
}

/* what was read of Market Snapshot Price Level Message is what was written, byte for byte */
static void equal_market_snapshot_price_level_message(const MarketSnapshotPriceLevelMessage *read, const MarketSnapshotPriceLevelMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->market_id[i] == written->market_id[i]); }
  assert(read->side == written->side);
  assert(read->price_level_position == written->price_level_position);
  for (size_t i = 0; i < 8; i++) { assert(read->price[i] == written->price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->quantity[i] == written->quantity[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->order_count[i] == written->order_count[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->implied_quantity[i] == written->implied_quantity[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->implied_order_count[i] == written->implied_order_count[i]); }
}

/* Market Snapshot Price Level Message: written and read back, then read and written back */
static void check_market_snapshot_price_level_message(void) {
  MarketSnapshotPriceLevelMessage sent;
  MarketSnapshotPriceLevelMessage got;
  uint8_t wire[26];
  uint8_t again[26];

  any_market_snapshot_price_level_message(&sent);
  assert(encode_market_snapshot_price_level_message(&sent, wire, 0) == 26);
  assert(decode_market_snapshot_price_level_message(&got, wire, 0) == 26);
  equal_market_snapshot_price_level_message(&got, &sent);

  for (size_t i = 0; i < 26; i++) { wire[i] = arbitrary(); }
  assert(decode_market_snapshot_price_level_message(&got, wire, 0) == 26);
  assert(encode_market_snapshot_price_level_message(&got, again, 0) == 26);
  for (size_t i = 0; i < 26; i++) { assert(again[i] == wire[i]); }
}

/* ---- Add Price Level Message: 34 bytes --------------------------------------- */

/* Upon receipt of this message, client should add/insert a price level at the specified position in the book for the given market, and push down the price levels that were previously at or below that position. */
typedef struct {
  uint8_t market_id[4];            /* bytes 0 to 3 */
  uint8_t side;                    /* byte 4 */
  uint8_t price_level_position;    /* byte 5 */
  uint8_t price[8];                /* bytes 6 to 13 */
  uint8_t quantity[4];             /* bytes 14 to 17 */
  uint8_t order_count[2];          /* bytes 18 to 19 */
  uint8_t implied_quantity[4];     /* bytes 20 to 23 */
  uint8_t implied_order_count[2];  /* bytes 24 to 25 */
  uint8_t timestamp[8];            /* bytes 26 to 33 */
} AddPriceLevelMessage;

/* any Add Price Level Message at all: every byte one the checker chooses */
static void any_add_price_level_message(AddPriceLevelMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->market_id[i] = arbitrary(); }
  record->side = arbitrary();
  record->price_level_position = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->order_count[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->implied_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->implied_order_count[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
}

/* Add Price Level Message to the wire: 34 bytes from at, returning where the next byte goes */
static size_t encode_add_price_level_message(const AddPriceLevelMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->market_id[i]; }
  wire[at++] = record->side;
  wire[at++] = record->price_level_position;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->quantity[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->order_count[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->implied_quantity[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->implied_order_count[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }

  return at;
}

/* Add Price Level Message off the wire: 34 bytes from at, returning where the next byte lies */
static size_t decode_add_price_level_message(AddPriceLevelMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->market_id[i] = wire[at++]; }
  record->side = wire[at++];
  record->price_level_position = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->order_count[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->implied_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->implied_order_count[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }

  return at;
}

/* what was read of Add Price Level Message is what was written, byte for byte */
static void equal_add_price_level_message(const AddPriceLevelMessage *read, const AddPriceLevelMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->market_id[i] == written->market_id[i]); }
  assert(read->side == written->side);
  assert(read->price_level_position == written->price_level_position);
  for (size_t i = 0; i < 8; i++) { assert(read->price[i] == written->price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->quantity[i] == written->quantity[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->order_count[i] == written->order_count[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->implied_quantity[i] == written->implied_quantity[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->implied_order_count[i] == written->implied_order_count[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
}

/* Add Price Level Message: written and read back, then read and written back */
static void check_add_price_level_message(void) {
  AddPriceLevelMessage sent;
  AddPriceLevelMessage got;
  uint8_t wire[34];
  uint8_t again[34];

  any_add_price_level_message(&sent);
  assert(encode_add_price_level_message(&sent, wire, 0) == 34);
  assert(decode_add_price_level_message(&got, wire, 0) == 34);
  equal_add_price_level_message(&got, &sent);

  for (size_t i = 0; i < 34; i++) { wire[i] = arbitrary(); }
  assert(decode_add_price_level_message(&got, wire, 0) == 34);
  assert(encode_add_price_level_message(&got, again, 0) == 34);
  for (size_t i = 0; i < 34; i++) { assert(again[i] == wire[i]); }
}

/* ---- Change Price Level Message: 34 bytes ------------------------------------ */

/* Upon receipt of this message, client should update the price level at the specified position in its book for the given market. */
typedef struct {
  uint8_t market_id[4];            /* bytes 0 to 3 */
  uint8_t side;                    /* byte 4 */
  uint8_t price_level_position;    /* byte 5 */
  uint8_t price[8];                /* bytes 6 to 13 */
  uint8_t quantity[4];             /* bytes 14 to 17 */
  uint8_t order_count[2];          /* bytes 18 to 19 */
  uint8_t implied_quantity[4];     /* bytes 20 to 23 */
  uint8_t implied_order_count[2];  /* bytes 24 to 25 */
  uint8_t timestamp[8];            /* bytes 26 to 33 */
} ChangePriceLevelMessage;

/* any Change Price Level Message at all: every byte one the checker chooses */
static void any_change_price_level_message(ChangePriceLevelMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->market_id[i] = arbitrary(); }
  record->side = arbitrary();
  record->price_level_position = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->order_count[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->implied_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->implied_order_count[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
}

/* Change Price Level Message to the wire: 34 bytes from at, returning where the next byte goes */
static size_t encode_change_price_level_message(const ChangePriceLevelMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->market_id[i]; }
  wire[at++] = record->side;
  wire[at++] = record->price_level_position;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->quantity[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->order_count[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->implied_quantity[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->implied_order_count[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }

  return at;
}

/* Change Price Level Message off the wire: 34 bytes from at, returning where the next byte lies */
static size_t decode_change_price_level_message(ChangePriceLevelMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->market_id[i] = wire[at++]; }
  record->side = wire[at++];
  record->price_level_position = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->order_count[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->implied_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->implied_order_count[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }

  return at;
}

/* what was read of Change Price Level Message is what was written, byte for byte */
static void equal_change_price_level_message(const ChangePriceLevelMessage *read, const ChangePriceLevelMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->market_id[i] == written->market_id[i]); }
  assert(read->side == written->side);
  assert(read->price_level_position == written->price_level_position);
  for (size_t i = 0; i < 8; i++) { assert(read->price[i] == written->price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->quantity[i] == written->quantity[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->order_count[i] == written->order_count[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->implied_quantity[i] == written->implied_quantity[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->implied_order_count[i] == written->implied_order_count[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
}

/* Change Price Level Message: written and read back, then read and written back */
static void check_change_price_level_message(void) {
  ChangePriceLevelMessage sent;
  ChangePriceLevelMessage got;
  uint8_t wire[34];
  uint8_t again[34];

  any_change_price_level_message(&sent);
  assert(encode_change_price_level_message(&sent, wire, 0) == 34);
  assert(decode_change_price_level_message(&got, wire, 0) == 34);
  equal_change_price_level_message(&got, &sent);

  for (size_t i = 0; i < 34; i++) { wire[i] = arbitrary(); }
  assert(decode_change_price_level_message(&got, wire, 0) == 34);
  assert(encode_change_price_level_message(&got, again, 0) == 34);
  for (size_t i = 0; i < 34; i++) { assert(again[i] == wire[i]); }
}

/* ---- Delete Price Level Message: 14 bytes ------------------------------------ */

/* Upon receipt of this message, client should remove the price level at the specified position in its book for the given market. */
typedef struct {
  uint8_t market_id[4];          /* bytes 0 to 3 */
  uint8_t side;                  /* byte 4 */
  uint8_t price_level_position;  /* byte 5 */
  uint8_t timestamp[8];          /* bytes 6 to 13 */
} DeletePriceLevelMessage;

/* any Delete Price Level Message at all: every byte one the checker chooses */
static void any_delete_price_level_message(DeletePriceLevelMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->market_id[i] = arbitrary(); }
  record->side = arbitrary();
  record->price_level_position = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
}

/* Delete Price Level Message to the wire: 14 bytes from at, returning where the next byte goes */
static size_t encode_delete_price_level_message(const DeletePriceLevelMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->market_id[i]; }
  wire[at++] = record->side;
  wire[at++] = record->price_level_position;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }

  return at;
}

/* Delete Price Level Message off the wire: 14 bytes from at, returning where the next byte lies */
static size_t decode_delete_price_level_message(DeletePriceLevelMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->market_id[i] = wire[at++]; }
  record->side = wire[at++];
  record->price_level_position = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }

  return at;
}

/* what was read of Delete Price Level Message is what was written, byte for byte */
static void equal_delete_price_level_message(const DeletePriceLevelMessage *read, const DeletePriceLevelMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->market_id[i] == written->market_id[i]); }
  assert(read->side == written->side);
  assert(read->price_level_position == written->price_level_position);
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
}

/* Delete Price Level Message: written and read back, then read and written back */
static void check_delete_price_level_message(void) {
  DeletePriceLevelMessage sent;
  DeletePriceLevelMessage got;
  uint8_t wire[14];
  uint8_t again[14];

  any_delete_price_level_message(&sent);
  assert(encode_delete_price_level_message(&sent, wire, 0) == 14);
  assert(decode_delete_price_level_message(&got, wire, 0) == 14);
  equal_delete_price_level_message(&got, &sent);

  for (size_t i = 0; i < 14; i++) { wire[i] = arbitrary(); }
  assert(decode_delete_price_level_message(&got, wire, 0) == 14);
  assert(encode_delete_price_level_message(&got, again, 0) == 14);
  for (size_t i = 0; i < 14; i++) { assert(again[i] == wire[i]); }
}

/* ---- New Options Market Definition Message: 322 bytes ------------------------ */

/* New Options Market Definition messages will be sent out when new options markets are created. */
typedef struct {
  uint8_t market_id[4];                 /* bytes 0 to 3 */
  uint8_t underlying_market_id[4];      /* bytes 4 to 7 */
  uint8_t futures_contract_symbol[70];  /* bytes 8 to 77 */
  uint8_t trading_status;               /* byte 78 */
  uint8_t order_price_denominator;      /* byte 79 */
  uint8_t increment_qty[4];             /* bytes 80 to 83 */
  uint8_t lot_size[4];                  /* bytes 84 to 87 */
  uint8_t market_desc[120];             /* bytes 88 to 207 */
  uint8_t option_type;                  /* byte 208 */
  uint8_t strike_price[8];              /* bytes 209 to 216 */
  uint8_t deal_price_denominator;       /* byte 217 */
  uint8_t min_qty[4];                   /* bytes 218 to 221 */
  uint8_t currency[20];                 /* bytes 222 to 241 */
  uint8_t num_decimals_strike_price;    /* byte 242 */
  uint8_t min_options_price[8];         /* bytes 243 to 250 */
  uint8_t max_options_price[8];         /* bytes 251 to 258 */
  uint8_t increment_premium_price[4];   /* bytes 259 to 262 */
  uint8_t options_expiration_year[2];   /* bytes 263 to 264 */
  uint8_t options_expiration_month[2];  /* bytes 265 to 266 */
  uint8_t options_expiration_day[2];    /* bytes 267 to 268 */
  uint8_t options_style;                /* byte 269 */
  uint8_t options_expiration_type;      /* byte 270 */
  uint8_t hedge_market_id[4];           /* bytes 271 to 274 */
  uint8_t settle_price_denominator;     /* byte 275 */
  uint8_t unit_qty_denominator;         /* byte 276 */
  uint8_t tick_value[8];                /* bytes 277 to 284 */
  uint8_t flex_allowed;                 /* byte 285 */
  uint8_t settlement_type;              /* byte 286 */
  uint8_t is_block_only;                /* byte 287 */
  uint8_t gt_allowed;                   /* byte 288 */
  uint8_t cross_order_supported;        /* byte 289 */
  uint8_t guaranteed_cross_supported;   /* byte 290 */
  uint8_t unit_of_measure[30];          /* bytes 291 to 320 */
  uint8_t mifid_regulated_market;       /* byte 321 */
} NewOptionsMarketDefinitionMessage;

/* any New Options Market Definition Message at all: every byte one the checker chooses */
static void any_new_options_market_definition_message(NewOptionsMarketDefinitionMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->market_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->underlying_market_id[i] = arbitrary(); }
  for (size_t i = 0; i < 70; i++) { record->futures_contract_symbol[i] = arbitrary(); }
  record->trading_status = arbitrary();
  record->order_price_denominator = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->increment_qty[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->lot_size[i] = arbitrary(); }
  for (size_t i = 0; i < 120; i++) { record->market_desc[i] = arbitrary(); }
  record->option_type = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->strike_price[i] = arbitrary(); }
  record->deal_price_denominator = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->min_qty[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->currency[i] = arbitrary(); }
  record->num_decimals_strike_price = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->min_options_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->max_options_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->increment_premium_price[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->options_expiration_year[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->options_expiration_month[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->options_expiration_day[i] = arbitrary(); }
  record->options_style = arbitrary();
  record->options_expiration_type = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->hedge_market_id[i] = arbitrary(); }
  record->settle_price_denominator = arbitrary();
  record->unit_qty_denominator = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->tick_value[i] = arbitrary(); }
  record->flex_allowed = arbitrary();
  record->settlement_type = arbitrary();
  record->is_block_only = arbitrary();
  record->gt_allowed = arbitrary();
  record->cross_order_supported = arbitrary();
  record->guaranteed_cross_supported = arbitrary();
  for (size_t i = 0; i < 30; i++) { record->unit_of_measure[i] = arbitrary(); }
  record->mifid_regulated_market = arbitrary();
}

/* New Options Market Definition Message to the wire: 322 bytes from at, returning where the next byte goes */
static size_t encode_new_options_market_definition_message(const NewOptionsMarketDefinitionMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->market_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->underlying_market_id[i]; }
  for (size_t i = 0; i < 70; i++) { wire[at++] = record->futures_contract_symbol[i]; }
  wire[at++] = record->trading_status;
  wire[at++] = record->order_price_denominator;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->increment_qty[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->lot_size[i]; }
  for (size_t i = 0; i < 120; i++) { wire[at++] = record->market_desc[i]; }
  wire[at++] = record->option_type;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->strike_price[i]; }
  wire[at++] = record->deal_price_denominator;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->min_qty[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->currency[i]; }
  wire[at++] = record->num_decimals_strike_price;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->min_options_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->max_options_price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->increment_premium_price[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->options_expiration_year[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->options_expiration_month[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->options_expiration_day[i]; }
  wire[at++] = record->options_style;
  wire[at++] = record->options_expiration_type;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->hedge_market_id[i]; }
  wire[at++] = record->settle_price_denominator;
  wire[at++] = record->unit_qty_denominator;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->tick_value[i]; }
  wire[at++] = record->flex_allowed;
  wire[at++] = record->settlement_type;
  wire[at++] = record->is_block_only;
  wire[at++] = record->gt_allowed;
  wire[at++] = record->cross_order_supported;
  wire[at++] = record->guaranteed_cross_supported;
  for (size_t i = 0; i < 30; i++) { wire[at++] = record->unit_of_measure[i]; }
  wire[at++] = record->mifid_regulated_market;

  return at;
}

/* New Options Market Definition Message off the wire: 322 bytes from at, returning where the next byte lies */
static size_t decode_new_options_market_definition_message(NewOptionsMarketDefinitionMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->market_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->underlying_market_id[i] = wire[at++]; }
  for (size_t i = 0; i < 70; i++) { record->futures_contract_symbol[i] = wire[at++]; }
  record->trading_status = wire[at++];
  record->order_price_denominator = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->increment_qty[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->lot_size[i] = wire[at++]; }
  for (size_t i = 0; i < 120; i++) { record->market_desc[i] = wire[at++]; }
  record->option_type = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->strike_price[i] = wire[at++]; }
  record->deal_price_denominator = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->min_qty[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->currency[i] = wire[at++]; }
  record->num_decimals_strike_price = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->min_options_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->max_options_price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->increment_premium_price[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->options_expiration_year[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->options_expiration_month[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->options_expiration_day[i] = wire[at++]; }
  record->options_style = wire[at++];
  record->options_expiration_type = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->hedge_market_id[i] = wire[at++]; }
  record->settle_price_denominator = wire[at++];
  record->unit_qty_denominator = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->tick_value[i] = wire[at++]; }
  record->flex_allowed = wire[at++];
  record->settlement_type = wire[at++];
  record->is_block_only = wire[at++];
  record->gt_allowed = wire[at++];
  record->cross_order_supported = wire[at++];
  record->guaranteed_cross_supported = wire[at++];
  for (size_t i = 0; i < 30; i++) { record->unit_of_measure[i] = wire[at++]; }
  record->mifid_regulated_market = wire[at++];

  return at;
}

/* what was read of New Options Market Definition Message is what was written, byte for byte */
static void equal_new_options_market_definition_message(const NewOptionsMarketDefinitionMessage *read, const NewOptionsMarketDefinitionMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->market_id[i] == written->market_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->underlying_market_id[i] == written->underlying_market_id[i]); }
  for (size_t i = 0; i < 70; i++) { assert(read->futures_contract_symbol[i] == written->futures_contract_symbol[i]); }
  assert(read->trading_status == written->trading_status);
  assert(read->order_price_denominator == written->order_price_denominator);
  for (size_t i = 0; i < 4; i++) { assert(read->increment_qty[i] == written->increment_qty[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->lot_size[i] == written->lot_size[i]); }
  for (size_t i = 0; i < 120; i++) { assert(read->market_desc[i] == written->market_desc[i]); }
  assert(read->option_type == written->option_type);
  for (size_t i = 0; i < 8; i++) { assert(read->strike_price[i] == written->strike_price[i]); }
  assert(read->deal_price_denominator == written->deal_price_denominator);
  for (size_t i = 0; i < 4; i++) { assert(read->min_qty[i] == written->min_qty[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->currency[i] == written->currency[i]); }
  assert(read->num_decimals_strike_price == written->num_decimals_strike_price);
  for (size_t i = 0; i < 8; i++) { assert(read->min_options_price[i] == written->min_options_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->max_options_price[i] == written->max_options_price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->increment_premium_price[i] == written->increment_premium_price[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->options_expiration_year[i] == written->options_expiration_year[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->options_expiration_month[i] == written->options_expiration_month[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->options_expiration_day[i] == written->options_expiration_day[i]); }
  assert(read->options_style == written->options_style);
  assert(read->options_expiration_type == written->options_expiration_type);
  for (size_t i = 0; i < 4; i++) { assert(read->hedge_market_id[i] == written->hedge_market_id[i]); }
  assert(read->settle_price_denominator == written->settle_price_denominator);
  assert(read->unit_qty_denominator == written->unit_qty_denominator);
  for (size_t i = 0; i < 8; i++) { assert(read->tick_value[i] == written->tick_value[i]); }
  assert(read->flex_allowed == written->flex_allowed);
  assert(read->settlement_type == written->settlement_type);
  assert(read->is_block_only == written->is_block_only);
  assert(read->gt_allowed == written->gt_allowed);
  assert(read->cross_order_supported == written->cross_order_supported);
  assert(read->guaranteed_cross_supported == written->guaranteed_cross_supported);
  for (size_t i = 0; i < 30; i++) { assert(read->unit_of_measure[i] == written->unit_of_measure[i]); }
  assert(read->mifid_regulated_market == written->mifid_regulated_market);
}

/* New Options Market Definition Message: written and read back, then read and written back */
static void check_new_options_market_definition_message(void) {
  NewOptionsMarketDefinitionMessage sent;
  NewOptionsMarketDefinitionMessage got;
  uint8_t wire[322];
  uint8_t again[322];

  any_new_options_market_definition_message(&sent);
  assert(encode_new_options_market_definition_message(&sent, wire, 0) == 322);
  assert(decode_new_options_market_definition_message(&got, wire, 0) == 322);
  equal_new_options_market_definition_message(&got, &sent);

  for (size_t i = 0; i < 322; i++) { wire[i] = arbitrary(); }
  assert(decode_new_options_market_definition_message(&got, wire, 0) == 322);
  assert(encode_new_options_market_definition_message(&got, again, 0) == 322);
  for (size_t i = 0; i < 322; i++) { assert(again[i] == wire[i]); }
}

/* ---- Rfq Message: 31 bytes --------------------------------------------------- */

/* Request for Quote Message. */
typedef struct {
  uint8_t market_id[4];             /* bytes 0 to 3 */
  uint8_t message_timestamp[8];     /* bytes 4 to 11 */
  uint8_t rfq_system_id[8];         /* bytes 12 to 19 */
  uint8_t market_type_id[2];        /* bytes 20 to 21 */
  uint8_t underlying_market_id[4];  /* bytes 22 to 25 */
  uint8_t quantity[4];              /* bytes 26 to 29 */
  uint8_t side;                     /* byte 30 */
} RfqMessage;

/* any Rfq Message at all: every byte one the checker chooses */
static void any_rfq_message(RfqMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->market_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->message_timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->rfq_system_id[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->market_type_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->underlying_market_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->quantity[i] = arbitrary(); }
  record->side = arbitrary();
}

/* Rfq Message to the wire: 31 bytes from at, returning where the next byte goes */
static size_t encode_rfq_message(const RfqMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->market_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->message_timestamp[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->rfq_system_id[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->market_type_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->underlying_market_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->quantity[i]; }
  wire[at++] = record->side;

  return at;
}

/* Rfq Message off the wire: 31 bytes from at, returning where the next byte lies */
static size_t decode_rfq_message(RfqMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->market_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->message_timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->rfq_system_id[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->market_type_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->underlying_market_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->quantity[i] = wire[at++]; }
  record->side = wire[at++];

  return at;
}

/* what was read of Rfq Message is what was written, byte for byte */
static void equal_rfq_message(const RfqMessage *read, const RfqMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->market_id[i] == written->market_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->message_timestamp[i] == written->message_timestamp[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->rfq_system_id[i] == written->rfq_system_id[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->market_type_id[i] == written->market_type_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->underlying_market_id[i] == written->underlying_market_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->quantity[i] == written->quantity[i]); }
  assert(read->side == written->side);
}

/* Rfq Message: written and read back, then read and written back */
static void check_rfq_message(void) {
  RfqMessage sent;
  RfqMessage got;
  uint8_t wire[31];
  uint8_t again[31];

  any_rfq_message(&sent);
  assert(encode_rfq_message(&sent, wire, 0) == 31);
  assert(decode_rfq_message(&got, wire, 0) == 31);
  equal_rfq_message(&got, &sent);

  for (size_t i = 0; i < 31; i++) { wire[i] = arbitrary(); }
  assert(decode_rfq_message(&got, wire, 0) == 31);
  assert(encode_rfq_message(&got, again, 0) == 31);
  for (size_t i = 0; i < 31; i++) { assert(again[i] == wire[i]); }
}

/* ---- Option Open Interest Message: 26 bytes ---------------------------------- */

/* Option Open Interest Message */
typedef struct {
  uint8_t market_id[4];            /* bytes 0 to 3 */
  uint8_t open_interest[4];        /* bytes 4 to 7 */
  uint8_t message_date_time[8];    /* bytes 8 to 15 */
  uint8_t open_interest_date[10];  /* bytes 16 to 25 */
} OptionOpenInterestMessage;

/* any Option Open Interest Message at all: every byte one the checker chooses */
static void any_option_open_interest_message(OptionOpenInterestMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->market_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->open_interest[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->message_date_time[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->open_interest_date[i] = arbitrary(); }
}

/* Option Open Interest Message to the wire: 26 bytes from at, returning where the next byte goes */
static size_t encode_option_open_interest_message(const OptionOpenInterestMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->market_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->open_interest[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->message_date_time[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->open_interest_date[i]; }

  return at;
}

/* Option Open Interest Message off the wire: 26 bytes from at, returning where the next byte lies */
static size_t decode_option_open_interest_message(OptionOpenInterestMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->market_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->open_interest[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->message_date_time[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->open_interest_date[i] = wire[at++]; }

  return at;
}

/* what was read of Option Open Interest Message is what was written, byte for byte */
static void equal_option_open_interest_message(const OptionOpenInterestMessage *read, const OptionOpenInterestMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->market_id[i] == written->market_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->open_interest[i] == written->open_interest[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->message_date_time[i] == written->message_date_time[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->open_interest_date[i] == written->open_interest_date[i]); }
}

/* Option Open Interest Message: written and read back, then read and written back */
static void check_option_open_interest_message(void) {
  OptionOpenInterestMessage sent;
  OptionOpenInterestMessage got;
  uint8_t wire[26];
  uint8_t again[26];

  any_option_open_interest_message(&sent);
  assert(encode_option_open_interest_message(&sent, wire, 0) == 26);
  assert(decode_option_open_interest_message(&got, wire, 0) == 26);
  equal_option_open_interest_message(&got, &sent);

  for (size_t i = 0; i < 26; i++) { wire[i] = arbitrary(); }
  assert(decode_option_open_interest_message(&got, wire, 0) == 26);
  assert(encode_option_open_interest_message(&got, again, 0) == 26);
  for (size_t i = 0; i < 26; i++) { assert(again[i] == wire[i]); }
}

/* ---- Option Settlement Price Message: 53 bytes ------------------------------- */

/* Option settlement prices could be official or unofficial. For a given market, the exchange usually sends out unofficial price before the official one. */
typedef struct {
  uint8_t market_id[4];                                   /* bytes 0 to 3 */
  uint8_t settlement_price_with_deal_price_precision[8];  /* bytes 4 to 11 */
  uint8_t message_date_time[8];                           /* bytes 12 to 19 */
  uint8_t is_official;                                    /* byte 20 */
  uint8_t valuation_date_time[8];                         /* bytes 21 to 28 */
  uint8_t volatility[8];                                  /* bytes 29 to 36 */
  uint8_t settlement_price[8];                            /* bytes 37 to 44 */
  uint8_t delta[8];                                       /* bytes 45 to 52 */
} OptionSettlementPriceMessage;

/* any Option Settlement Price Message at all: every byte one the checker chooses */
static void any_option_settlement_price_message(OptionSettlementPriceMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->market_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->settlement_price_with_deal_price_precision[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->message_date_time[i] = arbitrary(); }
  record->is_official = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->valuation_date_time[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->volatility[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->settlement_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->delta[i] = arbitrary(); }
}

/* Option Settlement Price Message to the wire: 53 bytes from at, returning where the next byte goes */
static size_t encode_option_settlement_price_message(const OptionSettlementPriceMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->market_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->settlement_price_with_deal_price_precision[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->message_date_time[i]; }
  wire[at++] = record->is_official;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->valuation_date_time[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->volatility[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->settlement_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->delta[i]; }

  return at;
}

/* Option Settlement Price Message off the wire: 53 bytes from at, returning where the next byte lies */
static size_t decode_option_settlement_price_message(OptionSettlementPriceMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->market_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->settlement_price_with_deal_price_precision[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->message_date_time[i] = wire[at++]; }
  record->is_official = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->valuation_date_time[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->volatility[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->settlement_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->delta[i] = wire[at++]; }

  return at;
}

/* what was read of Option Settlement Price Message is what was written, byte for byte */
static void equal_option_settlement_price_message(const OptionSettlementPriceMessage *read, const OptionSettlementPriceMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->market_id[i] == written->market_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->settlement_price_with_deal_price_precision[i] == written->settlement_price_with_deal_price_precision[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->message_date_time[i] == written->message_date_time[i]); }
  assert(read->is_official == written->is_official);
  for (size_t i = 0; i < 8; i++) { assert(read->valuation_date_time[i] == written->valuation_date_time[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->volatility[i] == written->volatility[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->settlement_price[i] == written->settlement_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->delta[i] == written->delta[i]); }
}

/* Option Settlement Price Message: written and read back, then read and written back */
static void check_option_settlement_price_message(void) {
  OptionSettlementPriceMessage sent;
  OptionSettlementPriceMessage got;
  uint8_t wire[53];
  uint8_t again[53];

  any_option_settlement_price_message(&sent);
  assert(encode_option_settlement_price_message(&sent, wire, 0) == 53);
  assert(decode_option_settlement_price_message(&got, wire, 0) == 53);
  equal_option_settlement_price_message(&got, &sent);

  for (size_t i = 0; i < 53; i++) { wire[i] = arbitrary(); }
  assert(decode_option_settlement_price_message(&got, wire, 0) == 53);
  assert(encode_option_settlement_price_message(&got, again, 0) == 53);
  for (size_t i = 0; i < 53; i++) { assert(again[i] == wire[i]); }
}

/* ---- Old Style Options Trade And Market Stats Message: 83 bytes -------------- */

/* Option settlement prices could be official or unofficial. For a given market, the exchange usually sends out unofficial price before the official one. */
typedef struct {
  uint8_t underlying_market_id[4];     /* bytes 0 to 3 */
  uint8_t trade_id[8];                 /* bytes 4 to 11 */
  uint8_t price[8];                    /* bytes 12 to 19 */
  uint8_t quantity[4];                 /* bytes 20 to 23 */
  uint8_t off_market_trade_indicator;  /* byte 24 */
  uint8_t transact_date_time[8];       /* bytes 25 to 32 */
  uint8_t option_type;                 /* byte 33 */
  uint8_t strike_price[8];             /* bytes 34 to 41 */
  uint8_t event_code;                  /* byte 42 */
  uint8_t total_volume[4];             /* bytes 43 to 46 */
  uint8_t block_volume[4];             /* bytes 47 to 50 */
  uint8_t efs_volume[4];               /* bytes 51 to 54 */
  uint8_t efp_volume[4];               /* bytes 55 to 58 */
  uint8_t high[8];                     /* bytes 59 to 66 */
  uint8_t low[8];                      /* bytes 67 to 74 */
  uint8_t vwap[8];                     /* bytes 75 to 82 */
} OldStyleOptionsTradeAndMarketStatsMessage;

/* any Old Style Options Trade And Market Stats Message at all: every byte one the checker chooses */
static void any_old_style_options_trade_and_market_stats_message(OldStyleOptionsTradeAndMarketStatsMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->underlying_market_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->trade_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->quantity[i] = arbitrary(); }
  record->off_market_trade_indicator = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->transact_date_time[i] = arbitrary(); }
  record->option_type = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->strike_price[i] = arbitrary(); }
  record->event_code = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->total_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->block_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->efs_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->efp_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->high[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->low[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->vwap[i] = arbitrary(); }
}

/* Old Style Options Trade And Market Stats Message to the wire: 83 bytes from at, returning where the next byte goes */
static size_t encode_old_style_options_trade_and_market_stats_message(const OldStyleOptionsTradeAndMarketStatsMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->underlying_market_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->trade_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->quantity[i]; }
  wire[at++] = record->off_market_trade_indicator;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->transact_date_time[i]; }
  wire[at++] = record->option_type;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->strike_price[i]; }
  wire[at++] = record->event_code;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->total_volume[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->block_volume[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->efs_volume[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->efp_volume[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->high[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->low[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->vwap[i]; }

  return at;
}

/* Old Style Options Trade And Market Stats Message off the wire: 83 bytes from at, returning where the next byte lies */
static size_t decode_old_style_options_trade_and_market_stats_message(OldStyleOptionsTradeAndMarketStatsMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->underlying_market_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->trade_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->quantity[i] = wire[at++]; }
  record->off_market_trade_indicator = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->transact_date_time[i] = wire[at++]; }
  record->option_type = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->strike_price[i] = wire[at++]; }
  record->event_code = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->total_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->block_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->efs_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->efp_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->high[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->low[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->vwap[i] = wire[at++]; }

  return at;
}

/* what was read of Old Style Options Trade And Market Stats Message is what was written, byte for byte */
static void equal_old_style_options_trade_and_market_stats_message(const OldStyleOptionsTradeAndMarketStatsMessage *read, const OldStyleOptionsTradeAndMarketStatsMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->underlying_market_id[i] == written->underlying_market_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->trade_id[i] == written->trade_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->price[i] == written->price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->quantity[i] == written->quantity[i]); }
  assert(read->off_market_trade_indicator == written->off_market_trade_indicator);
  for (size_t i = 0; i < 8; i++) { assert(read->transact_date_time[i] == written->transact_date_time[i]); }
  assert(read->option_type == written->option_type);
  for (size_t i = 0; i < 8; i++) { assert(read->strike_price[i] == written->strike_price[i]); }
  assert(read->event_code == written->event_code);
  for (size_t i = 0; i < 4; i++) { assert(read->total_volume[i] == written->total_volume[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->block_volume[i] == written->block_volume[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->efs_volume[i] == written->efs_volume[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->efp_volume[i] == written->efp_volume[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->high[i] == written->high[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->low[i] == written->low[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->vwap[i] == written->vwap[i]); }
}

/* Old Style Options Trade And Market Stats Message: written and read back, then read and written back */
static void check_old_style_options_trade_and_market_stats_message(void) {
  OldStyleOptionsTradeAndMarketStatsMessage sent;
  OldStyleOptionsTradeAndMarketStatsMessage got;
  uint8_t wire[83];
  uint8_t again[83];

  any_old_style_options_trade_and_market_stats_message(&sent);
  assert(encode_old_style_options_trade_and_market_stats_message(&sent, wire, 0) == 83);
  assert(decode_old_style_options_trade_and_market_stats_message(&got, wire, 0) == 83);
  equal_old_style_options_trade_and_market_stats_message(&got, &sent);

  for (size_t i = 0; i < 83; i++) { wire[i] = arbitrary(); }
  assert(decode_old_style_options_trade_and_market_stats_message(&got, wire, 0) == 83);
  assert(encode_old_style_options_trade_and_market_stats_message(&got, again, 0) == 83);
  for (size_t i = 0; i < 83; i++) { assert(again[i] == wire[i]); }
}

/* ---- What esbmc checks ------------------------------------------------------- */

/* every record of the protocol, each on its own buffers */
static void checks(void) {
  check_packet_header();
  check_message_header();
  check_market_snapshot_message();
  check_trade_message();
  check_spot_market_trade_message();
  check_investigated_trade_message();
  check_cancelled_trade_message();
  check_market_statistics_message();
  check_market_state_change_message();
  check_system_text_message();
  check_open_interest_message();
  check_open_price_message();
  check_close_price_message();
  check_settlement_price_message();
  check_index_prices_message();
  check_end_of_day_market_summary_message();
  check_market_event_message();
  check_pre_open_price_indicator_message();
  check_strip_info_message();
  check_interval_price_limit_notification_message();
  check_new_expiry_message();
  check_market_snapshot_order_message();
  check_add_or_modify_order_message();
  check_delete_order_message();
  check_message_bundle_marker();
  check_fixing_transition_message();
  check_fixing_lockdown_message();
  check_fixing_indicative_price_message_message();
  check_market_snapshot_price_level_message();
  check_add_price_level_message();
  check_change_price_level_message();
  check_delete_price_level_message();
  check_new_options_market_definition_message();
  check_rfq_message();
  check_option_open_interest_message();
  check_option_settlement_price_message();
  check_old_style_options_trade_and_market_stats_message();
}

int main(void) {
#ifdef CONCRETE
  for (pattern = 0; pattern < 4; pattern++) { checks(); }
#else
  checks();
#endif

  return 0;
}
