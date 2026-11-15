// bmv/bmvmarketdata/product18/BmvMarketData_Product18_v1_1.c
/*
 * Bolsa Mexicana de Valores Bmv Market Data Product 18
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

/* ---- Events System Message: 22 bytes ----------------------------------------- */

/* The system of events message is used to inform that an event has occurred, which needs to be of public domain. */
typedef struct {
  uint8_t instrument_number[4];  /* bytes 0 to 3 */
  uint8_t event_code;            /* byte 4 */
  uint8_t market;                /* byte 5 */
  uint8_t sending_time[8];       /* bytes 6 to 13 */
  uint8_t ending_time[8];        /* bytes 14 to 21 */
} EventsSystemMessage;

/* any Events System Message at all: every byte one the checker chooses */
static void any_events_system_message(EventsSystemMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->instrument_number[i] = arbitrary(); }
  record->event_code = arbitrary();
  record->market = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->sending_time[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->ending_time[i] = arbitrary(); }
}

/* Events System Message to the wire: 22 bytes from at, returning where the next byte goes */
static size_t encode_events_system_message(const EventsSystemMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument_number[i]; }
  wire[at++] = record->event_code;
  wire[at++] = record->market;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->sending_time[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->ending_time[i]; }

  return at;
}

/* Events System Message off the wire: 22 bytes from at, returning where the next byte lies */
static size_t decode_events_system_message(EventsSystemMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->instrument_number[i] = wire[at++]; }
  record->event_code = wire[at++];
  record->market = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->sending_time[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->ending_time[i] = wire[at++]; }

  return at;
}

/* what was read of Events System Message is what was written, byte for byte */
static void equal_events_system_message(const EventsSystemMessage *read, const EventsSystemMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->instrument_number[i] == written->instrument_number[i]); }
  assert(read->event_code == written->event_code);
  assert(read->market == written->market);
  for (size_t i = 0; i < 8; i++) { assert(read->sending_time[i] == written->sending_time[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->ending_time[i] == written->ending_time[i]); }
}

/* Events System Message: written and read back, then read and written back */
static void check_events_system_message(void) {
  EventsSystemMessage sent;
  EventsSystemMessage got;
  uint8_t wire[22];
  uint8_t again[22];

  any_events_system_message(&sent);
  assert(encode_events_system_message(&sent, wire, 0) == 22);
  assert(decode_events_system_message(&got, wire, 0) == 22);
  equal_events_system_message(&got, &sent);

  for (size_t i = 0; i < 22; i++) { wire[i] = arbitrary(); }
  assert(decode_events_system_message(&got, wire, 0) == 22);
  assert(encode_events_system_message(&got, again, 0) == 22);
  for (size_t i = 0; i < 22; i++) { assert(again[i] == wire[i]); }
}

/* ---- Trade Cancellation Message: 8 bytes ------------------------------------- */

/* This message is sent when a transaction is cancelled from the BMV system. */
typedef struct {
  uint8_t instrument_number[4];  /* bytes 0 to 3 */
  uint8_t trade_number[4];       /* bytes 4 to 7 */
} TradeCancellationMessage;

/* any Trade Cancellation Message at all: every byte one the checker chooses */
static void any_trade_cancellation_message(TradeCancellationMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->instrument_number[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->trade_number[i] = arbitrary(); }
}

/* Trade Cancellation Message to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_trade_cancellation_message(const TradeCancellationMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument_number[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->trade_number[i]; }

  return at;
}

/* Trade Cancellation Message off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_trade_cancellation_message(TradeCancellationMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->instrument_number[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->trade_number[i] = wire[at++]; }

  return at;
}

/* what was read of Trade Cancellation Message is what was written, byte for byte */
static void equal_trade_cancellation_message(const TradeCancellationMessage *read, const TradeCancellationMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->instrument_number[i] == written->instrument_number[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->trade_number[i] == written->trade_number[i]); }
}

/* Trade Cancellation Message: written and read back, then read and written back */
static void check_trade_cancellation_message(void) {
  TradeCancellationMessage sent;
  TradeCancellationMessage got;
  uint8_t wire[8];
  uint8_t again[8];

  any_trade_cancellation_message(&sent);
  assert(encode_trade_cancellation_message(&sent, wire, 0) == 8);
  assert(decode_trade_cancellation_message(&got, wire, 0) == 8);
  equal_trade_cancellation_message(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_trade_cancellation_message(&got, wire, 0) == 8);
  assert(encode_trade_cancellation_message(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Status Changes Message: 5 bytes ----------------------------------------- */

/* All instruments are in a certain status before and during trading session. */
typedef struct {
  uint8_t instrument_number[4];  /* bytes 0 to 3 */
  uint8_t instrument_status;     /* byte 4 */
} StatusChangesMessage;

/* any Status Changes Message at all: every byte one the checker chooses */
static void any_status_changes_message(StatusChangesMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->instrument_number[i] = arbitrary(); }
  record->instrument_status = arbitrary();
}

/* Status Changes Message to the wire: 5 bytes from at, returning where the next byte goes */
static size_t encode_status_changes_message(const StatusChangesMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument_number[i]; }
  wire[at++] = record->instrument_status;

  return at;
}

/* Status Changes Message off the wire: 5 bytes from at, returning where the next byte lies */
static size_t decode_status_changes_message(StatusChangesMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->instrument_number[i] = wire[at++]; }
  record->instrument_status = wire[at++];

  return at;
}

/* what was read of Status Changes Message is what was written, byte for byte */
static void equal_status_changes_message(const StatusChangesMessage *read, const StatusChangesMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->instrument_number[i] == written->instrument_number[i]); }
  assert(read->instrument_status == written->instrument_status);
}

/* Status Changes Message: written and read back, then read and written back */
static void check_status_changes_message(void) {
  StatusChangesMessage sent;
  StatusChangesMessage got;
  uint8_t wire[5];
  uint8_t again[5];

  any_status_changes_message(&sent);
  assert(encode_status_changes_message(&sent, wire, 0) == 5);
  assert(decode_status_changes_message(&got, wire, 0) == 5);
  equal_status_changes_message(&got, &sent);

  for (size_t i = 0; i < 5; i++) { wire[i] = arbitrary(); }
  assert(decode_status_changes_message(&got, wire, 0) == 5);
  assert(encode_status_changes_message(&got, again, 0) == 5);
  for (size_t i = 0; i < 5; i++) { assert(again[i] == wire[i]); }
}

/* ---- Weighted Average Price Settlement Prices Message: 20 bytes -------------- */

/* For equities market, this message will be sent for each operation containing weighted average price per instrument generated within WAP calculation period (last 20 minutes of trading). */
typedef struct {
  uint8_t instrument_number[4];       /* bytes 0 to 3 */
  uint8_t weighted_average_price[8];  /* bytes 4 to 11 */
  uint8_t volatility[8];              /* bytes 12 to 19 */
} WeightedAveragePriceSettlementPricesMessage;

/* any Weighted Average Price Settlement Prices Message at all: every byte one the checker chooses */
static void any_weighted_average_price_settlement_prices_message(WeightedAveragePriceSettlementPricesMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->instrument_number[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->weighted_average_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->volatility[i] = arbitrary(); }
}

/* Weighted Average Price Settlement Prices Message to the wire: 20 bytes from at, returning where the next byte goes */
static size_t encode_weighted_average_price_settlement_prices_message(const WeightedAveragePriceSettlementPricesMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument_number[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->weighted_average_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->volatility[i]; }

  return at;
}

/* Weighted Average Price Settlement Prices Message off the wire: 20 bytes from at, returning where the next byte lies */
static size_t decode_weighted_average_price_settlement_prices_message(WeightedAveragePriceSettlementPricesMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->instrument_number[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->weighted_average_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->volatility[i] = wire[at++]; }

  return at;
}

/* what was read of Weighted Average Price Settlement Prices Message is what was written, byte for byte */
static void equal_weighted_average_price_settlement_prices_message(const WeightedAveragePriceSettlementPricesMessage *read, const WeightedAveragePriceSettlementPricesMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->instrument_number[i] == written->instrument_number[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->weighted_average_price[i] == written->weighted_average_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->volatility[i] == written->volatility[i]); }
}

/* Weighted Average Price Settlement Prices Message: written and read back, then read and written back */
static void check_weighted_average_price_settlement_prices_message(void) {
  WeightedAveragePriceSettlementPricesMessage sent;
  WeightedAveragePriceSettlementPricesMessage got;
  uint8_t wire[20];
  uint8_t again[20];

  any_weighted_average_price_settlement_prices_message(&sent);
  assert(encode_weighted_average_price_settlement_prices_message(&sent, wire, 0) == 20);
  assert(decode_weighted_average_price_settlement_prices_message(&got, wire, 0) == 20);
  equal_weighted_average_price_settlement_prices_message(&got, &sent);

  for (size_t i = 0; i < 20; i++) { wire[i] = arbitrary(); }
  assert(decode_weighted_average_price_settlement_prices_message(&got, wire, 0) == 20);
  assert(encode_weighted_average_price_settlement_prices_message(&got, again, 0) == 20);
  for (size_t i = 0; i < 20; i++) { assert(again[i] == wire[i]); }
}

/* ---- Capital Trades Message: 51 bytes ---------------------------------------- */

/* Contains information on any BMV accepted transaction. */
typedef struct {
  uint8_t instrument_number[4];  /* bytes 0 to 3 */
  uint8_t trade_time[8];         /* bytes 4 to 11 */
  uint8_t volume_int_324[4];     /* bytes 12 to 15 */
  uint8_t price[8];              /* bytes 16 to 23 */
  uint8_t concertation_type;     /* byte 24 */
  uint8_t trade_number[4];       /* bytes 25 to 28 */
  uint8_t price_setter;          /* byte 29 */
  uint8_t operation_type;        /* byte 30 */
  uint8_t amount[8];             /* bytes 31 to 38 */
  uint8_t buy[5];                /* bytes 39 to 43 */
  uint8_t sell[5];               /* bytes 44 to 48 */
  uint8_t settlement;            /* byte 49 */
  uint8_t auction_indicator;     /* byte 50 */
} CapitalTradesMessage;

/* any Capital Trades Message at all: every byte one the checker chooses */
static void any_capital_trades_message(CapitalTradesMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->instrument_number[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->trade_time[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->volume_int_324[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->price[i] = arbitrary(); }
  record->concertation_type = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->trade_number[i] = arbitrary(); }
  record->price_setter = arbitrary();
  record->operation_type = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->amount[i] = arbitrary(); }
  for (size_t i = 0; i < 5; i++) { record->buy[i] = arbitrary(); }
  for (size_t i = 0; i < 5; i++) { record->sell[i] = arbitrary(); }
  record->settlement = arbitrary();
  record->auction_indicator = arbitrary();
}

/* Capital Trades Message to the wire: 51 bytes from at, returning where the next byte goes */
static size_t encode_capital_trades_message(const CapitalTradesMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument_number[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->trade_time[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->volume_int_324[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price[i]; }
  wire[at++] = record->concertation_type;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->trade_number[i]; }
  wire[at++] = record->price_setter;
  wire[at++] = record->operation_type;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->amount[i]; }
  for (size_t i = 0; i < 5; i++) { wire[at++] = record->buy[i]; }
  for (size_t i = 0; i < 5; i++) { wire[at++] = record->sell[i]; }
  wire[at++] = record->settlement;
  wire[at++] = record->auction_indicator;

  return at;
}

/* Capital Trades Message off the wire: 51 bytes from at, returning where the next byte lies */
static size_t decode_capital_trades_message(CapitalTradesMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->instrument_number[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->trade_time[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->volume_int_324[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->price[i] = wire[at++]; }
  record->concertation_type = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->trade_number[i] = wire[at++]; }
  record->price_setter = wire[at++];
  record->operation_type = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->amount[i] = wire[at++]; }
  for (size_t i = 0; i < 5; i++) { record->buy[i] = wire[at++]; }
  for (size_t i = 0; i < 5; i++) { record->sell[i] = wire[at++]; }
  record->settlement = wire[at++];
  record->auction_indicator = wire[at++];

  return at;
}

/* what was read of Capital Trades Message is what was written, byte for byte */
static void equal_capital_trades_message(const CapitalTradesMessage *read, const CapitalTradesMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->instrument_number[i] == written->instrument_number[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->trade_time[i] == written->trade_time[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->volume_int_324[i] == written->volume_int_324[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->price[i] == written->price[i]); }
  assert(read->concertation_type == written->concertation_type);
  for (size_t i = 0; i < 4; i++) { assert(read->trade_number[i] == written->trade_number[i]); }
  assert(read->price_setter == written->price_setter);
  assert(read->operation_type == written->operation_type);
  for (size_t i = 0; i < 8; i++) { assert(read->amount[i] == written->amount[i]); }
  for (size_t i = 0; i < 5; i++) { assert(read->buy[i] == written->buy[i]); }
  for (size_t i = 0; i < 5; i++) { assert(read->sell[i] == written->sell[i]); }
  assert(read->settlement == written->settlement);
  assert(read->auction_indicator == written->auction_indicator);
}

/* Capital Trades Message: written and read back, then read and written back */
static void check_capital_trades_message(void) {
  CapitalTradesMessage sent;
  CapitalTradesMessage got;
  uint8_t wire[51];
  uint8_t again[51];

  any_capital_trades_message(&sent);
  assert(encode_capital_trades_message(&sent, wire, 0) == 51);
  assert(decode_capital_trades_message(&got, wire, 0) == 51);
  equal_capital_trades_message(&got, &sent);

  for (size_t i = 0; i < 51; i++) { wire[i] = arbitrary(); }
  assert(decode_capital_trades_message(&got, wire, 0) == 51);
  assert(encode_capital_trades_message(&got, again, 0) == 51);
  for (size_t i = 0; i < 51; i++) { assert(again[i] == wire[i]); }
}

/* ---- Probable Allocation Price Message: 16 bytes ----------------------------- */

/* Sent during any auction type (Opening, Continuous, Volatility and Intraday) and only on instruments where there is already a virtual match or pre-allocation. */
typedef struct {
  uint8_t instrument_number[4];          /* bytes 0 to 3 */
  uint8_t probable_allocation_price[8];  /* bytes 4 to 11 */
  uint8_t volume_int_324[4];             /* bytes 12 to 15 */
} ProbableAllocationPriceMessage;

/* any Probable Allocation Price Message at all: every byte one the checker chooses */
static void any_probable_allocation_price_message(ProbableAllocationPriceMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->instrument_number[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->probable_allocation_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->volume_int_324[i] = arbitrary(); }
}

/* Probable Allocation Price Message to the wire: 16 bytes from at, returning where the next byte goes */
static size_t encode_probable_allocation_price_message(const ProbableAllocationPriceMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument_number[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->probable_allocation_price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->volume_int_324[i]; }

  return at;
}

/* Probable Allocation Price Message off the wire: 16 bytes from at, returning where the next byte lies */
static size_t decode_probable_allocation_price_message(ProbableAllocationPriceMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->instrument_number[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->probable_allocation_price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->volume_int_324[i] = wire[at++]; }

  return at;
}

/* what was read of Probable Allocation Price Message is what was written, byte for byte */
static void equal_probable_allocation_price_message(const ProbableAllocationPriceMessage *read, const ProbableAllocationPriceMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->instrument_number[i] == written->instrument_number[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->probable_allocation_price[i] == written->probable_allocation_price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->volume_int_324[i] == written->volume_int_324[i]); }
}

/* Probable Allocation Price Message: written and read back, then read and written back */
static void check_probable_allocation_price_message(void) {
  ProbableAllocationPriceMessage sent;
  ProbableAllocationPriceMessage got;
  uint8_t wire[16];
  uint8_t again[16];

  any_probable_allocation_price_message(&sent);
  assert(encode_probable_allocation_price_message(&sent, wire, 0) == 16);
  assert(decode_probable_allocation_price_message(&got, wire, 0) == 16);
  equal_probable_allocation_price_message(&got, &sent);

  for (size_t i = 0; i < 16; i++) { wire[i] = arbitrary(); }
  assert(decode_probable_allocation_price_message(&got, wire, 0) == 16);
  assert(encode_probable_allocation_price_message(&got, again, 0) == 16);
  for (size_t i = 0; i < 16; i++) { assert(again[i] == wire[i]); }
}

/* ---- Continuous Auctions Beginning Message: 20 bytes ------------------------- */

/* Sent at the moment one of the Continuous, Volatility or SIC auctions is generated. */
typedef struct {
  uint8_t instrument_number[4];          /* bytes 0 to 3 */
  uint8_t beginning_time_of_auction[8];  /* bytes 4 to 11 */
  uint8_t end_auction_time[8];           /* bytes 12 to 19 */
} ContinuousAuctionsBeginningMessage;

/* any Continuous Auctions Beginning Message at all: every byte one the checker chooses */
static void any_continuous_auctions_beginning_message(ContinuousAuctionsBeginningMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->instrument_number[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->beginning_time_of_auction[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->end_auction_time[i] = arbitrary(); }
}

/* Continuous Auctions Beginning Message to the wire: 20 bytes from at, returning where the next byte goes */
static size_t encode_continuous_auctions_beginning_message(const ContinuousAuctionsBeginningMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument_number[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->beginning_time_of_auction[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->end_auction_time[i]; }

  return at;
}

/* Continuous Auctions Beginning Message off the wire: 20 bytes from at, returning where the next byte lies */
static size_t decode_continuous_auctions_beginning_message(ContinuousAuctionsBeginningMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->instrument_number[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->beginning_time_of_auction[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->end_auction_time[i] = wire[at++]; }

  return at;
}

/* what was read of Continuous Auctions Beginning Message is what was written, byte for byte */
static void equal_continuous_auctions_beginning_message(const ContinuousAuctionsBeginningMessage *read, const ContinuousAuctionsBeginningMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->instrument_number[i] == written->instrument_number[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->beginning_time_of_auction[i] == written->beginning_time_of_auction[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->end_auction_time[i] == written->end_auction_time[i]); }
}

/* Continuous Auctions Beginning Message: written and read back, then read and written back */
static void check_continuous_auctions_beginning_message(void) {
  ContinuousAuctionsBeginningMessage sent;
  ContinuousAuctionsBeginningMessage got;
  uint8_t wire[20];
  uint8_t again[20];

  any_continuous_auctions_beginning_message(&sent);
  assert(encode_continuous_auctions_beginning_message(&sent, wire, 0) == 20);
  assert(decode_continuous_auctions_beginning_message(&got, wire, 0) == 20);
  equal_continuous_auctions_beginning_message(&got, &sent);

  for (size_t i = 0; i < 20; i++) { wire[i] = arbitrary(); }
  assert(decode_continuous_auctions_beginning_message(&got, wire, 0) == 20);
  assert(encode_continuous_auctions_beginning_message(&got, again, 0) == 20);
  for (size_t i = 0; i < 20; i++) { assert(again[i] == wire[i]); }
}

/* ---- Middle Price Existing Quotes Message: 5 bytes --------------------------- */

/* Generated when an instrument enters a posture in the hidden electronic Middle Price book. */
typedef struct {
  uint8_t instrument_number[4];  /* bytes 0 to 3 */
  uint8_t existing_postures;     /* byte 4 */
} MiddlePriceExistingQuotesMessage;

/* any Middle Price Existing Quotes Message at all: every byte one the checker chooses */
static void any_middle_price_existing_quotes_message(MiddlePriceExistingQuotesMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->instrument_number[i] = arbitrary(); }
  record->existing_postures = arbitrary();
}

/* Middle Price Existing Quotes Message to the wire: 5 bytes from at, returning where the next byte goes */
static size_t encode_middle_price_existing_quotes_message(const MiddlePriceExistingQuotesMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument_number[i]; }
  wire[at++] = record->existing_postures;

  return at;
}

/* Middle Price Existing Quotes Message off the wire: 5 bytes from at, returning where the next byte lies */
static size_t decode_middle_price_existing_quotes_message(MiddlePriceExistingQuotesMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->instrument_number[i] = wire[at++]; }
  record->existing_postures = wire[at++];

  return at;
}

/* what was read of Middle Price Existing Quotes Message is what was written, byte for byte */
static void equal_middle_price_existing_quotes_message(const MiddlePriceExistingQuotesMessage *read, const MiddlePriceExistingQuotesMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->instrument_number[i] == written->instrument_number[i]); }
  assert(read->existing_postures == written->existing_postures);
}

/* Middle Price Existing Quotes Message: written and read back, then read and written back */
static void check_middle_price_existing_quotes_message(void) {
  MiddlePriceExistingQuotesMessage sent;
  MiddlePriceExistingQuotesMessage got;
  uint8_t wire[5];
  uint8_t again[5];

  any_middle_price_existing_quotes_message(&sent);
  assert(encode_middle_price_existing_quotes_message(&sent, wire, 0) == 5);
  assert(decode_middle_price_existing_quotes_message(&got, wire, 0) == 5);
  equal_middle_price_existing_quotes_message(&got, &sent);

  for (size_t i = 0; i < 5; i++) { wire[i] = arbitrary(); }
  assert(decode_middle_price_existing_quotes_message(&got, wire, 0) == 5);
  assert(encode_middle_price_existing_quotes_message(&got, again, 0) == 5);
  for (size_t i = 0; i < 5; i++) { assert(again[i] == wire[i]); }
}

/* ---- Registry Operations Message: 61 bytes ----------------------------------- */

/* Sent whenever there is a debt or capital instrument placement. */
typedef struct {
  uint8_t instrument_number[4];  /* bytes 0 to 3 */
  uint8_t offer_type;            /* byte 4 */
  uint8_t income;                /* byte 5 */
  uint8_t value_type[4];         /* bytes 6 to 9 */
  uint8_t issuer[7];             /* bytes 10 to 16 */
  uint8_t series[6];             /* bytes 17 to 22 */
  uint8_t maximum_volume[8];     /* bytes 23 to 30 */
  uint8_t registered_volume[8];  /* bytes 31 to 38 */
  uint8_t price_rate[8];         /* bytes 39 to 46 */
  uint8_t settlement_date[8];    /* bytes 47 to 54 */
  uint8_t firm[5];               /* bytes 55 to 59 */
  uint8_t movement;              /* byte 60 */
} RegistryOperationsMessage;

/* any Registry Operations Message at all: every byte one the checker chooses */
static void any_registry_operations_message(RegistryOperationsMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->instrument_number[i] = arbitrary(); }
  record->offer_type = arbitrary();
  record->income = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->value_type[i] = arbitrary(); }
  for (size_t i = 0; i < 7; i++) { record->issuer[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->series[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->maximum_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->registered_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->price_rate[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->settlement_date[i] = arbitrary(); }
  for (size_t i = 0; i < 5; i++) { record->firm[i] = arbitrary(); }
  record->movement = arbitrary();
}

/* Registry Operations Message to the wire: 61 bytes from at, returning where the next byte goes */
static size_t encode_registry_operations_message(const RegistryOperationsMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument_number[i]; }
  wire[at++] = record->offer_type;
  wire[at++] = record->income;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->value_type[i]; }
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->issuer[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->series[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->maximum_volume[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->registered_volume[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price_rate[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->settlement_date[i]; }
  for (size_t i = 0; i < 5; i++) { wire[at++] = record->firm[i]; }
  wire[at++] = record->movement;

  return at;
}

/* Registry Operations Message off the wire: 61 bytes from at, returning where the next byte lies */
static size_t decode_registry_operations_message(RegistryOperationsMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->instrument_number[i] = wire[at++]; }
  record->offer_type = wire[at++];
  record->income = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->value_type[i] = wire[at++]; }
  for (size_t i = 0; i < 7; i++) { record->issuer[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->series[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->maximum_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->registered_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->price_rate[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->settlement_date[i] = wire[at++]; }
  for (size_t i = 0; i < 5; i++) { record->firm[i] = wire[at++]; }
  record->movement = wire[at++];

  return at;
}

/* what was read of Registry Operations Message is what was written, byte for byte */
static void equal_registry_operations_message(const RegistryOperationsMessage *read, const RegistryOperationsMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->instrument_number[i] == written->instrument_number[i]); }
  assert(read->offer_type == written->offer_type);
  assert(read->income == written->income);
  for (size_t i = 0; i < 4; i++) { assert(read->value_type[i] == written->value_type[i]); }
  for (size_t i = 0; i < 7; i++) { assert(read->issuer[i] == written->issuer[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->series[i] == written->series[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->maximum_volume[i] == written->maximum_volume[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->registered_volume[i] == written->registered_volume[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->price_rate[i] == written->price_rate[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->settlement_date[i] == written->settlement_date[i]); }
  for (size_t i = 0; i < 5; i++) { assert(read->firm[i] == written->firm[i]); }
  assert(read->movement == written->movement);
}

/* Registry Operations Message: written and read back, then read and written back */
static void check_registry_operations_message(void) {
  RegistryOperationsMessage sent;
  RegistryOperationsMessage got;
  uint8_t wire[61];
  uint8_t again[61];

  any_registry_operations_message(&sent);
  assert(encode_registry_operations_message(&sent, wire, 0) == 61);
  assert(decode_registry_operations_message(&got, wire, 0) == 61);
  equal_registry_operations_message(&got, &sent);

  for (size_t i = 0; i < 61; i++) { wire[i] = arbitrary(); }
  assert(decode_registry_operations_message(&got, wire, 0) == 61);
  assert(encode_registry_operations_message(&got, again, 0) == 61);
  for (size_t i = 0; i < 61; i++) { assert(again[i] == wire[i]); }
}

/* ---- Mutual Fund Trades Message: 52 bytes ------------------------------------ */

/* Contains any mutual funds operation realized. */
typedef struct {
  uint8_t instrument_number[4];             /* bytes 0 to 3 */
  uint8_t trade_date[8];                    /* bytes 4 to 11 */
  uint8_t price[8];                         /* bytes 12 to 19 */
  uint8_t book_value[8];                    /* bytes 20 to 27 */
  uint8_t number_of_sales_transactions[4];  /* bytes 28 to 31 */
  uint8_t sales_volume[8];                  /* bytes 32 to 39 */
  uint8_t number_of_buy_transactions[4];    /* bytes 40 to 43 */
  uint8_t buy_volume[8];                    /* bytes 44 to 51 */
} MutualFundTradesMessage;

/* any Mutual Fund Trades Message at all: every byte one the checker chooses */
static void any_mutual_fund_trades_message(MutualFundTradesMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->instrument_number[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->trade_date[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->book_value[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->number_of_sales_transactions[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->sales_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->number_of_buy_transactions[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->buy_volume[i] = arbitrary(); }
}

/* Mutual Fund Trades Message to the wire: 52 bytes from at, returning where the next byte goes */
static size_t encode_mutual_fund_trades_message(const MutualFundTradesMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument_number[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->trade_date[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->book_value[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->number_of_sales_transactions[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->sales_volume[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->number_of_buy_transactions[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->buy_volume[i]; }

  return at;
}

/* Mutual Fund Trades Message off the wire: 52 bytes from at, returning where the next byte lies */
static size_t decode_mutual_fund_trades_message(MutualFundTradesMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->instrument_number[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->trade_date[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->book_value[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->number_of_sales_transactions[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->sales_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->number_of_buy_transactions[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->buy_volume[i] = wire[at++]; }

  return at;
}

/* what was read of Mutual Fund Trades Message is what was written, byte for byte */
static void equal_mutual_fund_trades_message(const MutualFundTradesMessage *read, const MutualFundTradesMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->instrument_number[i] == written->instrument_number[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->trade_date[i] == written->trade_date[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->price[i] == written->price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->book_value[i] == written->book_value[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->number_of_sales_transactions[i] == written->number_of_sales_transactions[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->sales_volume[i] == written->sales_volume[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->number_of_buy_transactions[i] == written->number_of_buy_transactions[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->buy_volume[i] == written->buy_volume[i]); }
}

/* Mutual Fund Trades Message: written and read back, then read and written back */
static void check_mutual_fund_trades_message(void) {
  MutualFundTradesMessage sent;
  MutualFundTradesMessage got;
  uint8_t wire[52];
  uint8_t again[52];

  any_mutual_fund_trades_message(&sent);
  assert(encode_mutual_fund_trades_message(&sent, wire, 0) == 52);
  assert(decode_mutual_fund_trades_message(&got, wire, 0) == 52);
  equal_mutual_fund_trades_message(&got, &sent);

  for (size_t i = 0; i < 52; i++) { wire[i] = arbitrary(); }
  assert(decode_mutual_fund_trades_message(&got, wire, 0) == 52);
  assert(encode_mutual_fund_trades_message(&got, again, 0) == 52);
  for (size_t i = 0; i < 52; i++) { assert(again[i] == wire[i]); }
}

/* ---- Tradability Message: 64 bytes ------------------------------------------- */

/* Message sent every half hour during trading session, informing general tradability by instrument. */
typedef struct {
  uint8_t instrument_number[4];     /* bytes 0 to 3 */
  uint8_t number_of_operations[4];  /* bytes 4 to 7 */
  uint8_t volume_int_648[8];        /* bytes 8 to 15 */
  uint8_t amount[8];                /* bytes 16 to 23 */
  uint8_t opening_price[8];         /* bytes 24 to 31 */
  uint8_t maximum[8];               /* bytes 32 to 39 */
  uint8_t minimum[8];               /* bytes 40 to 47 */
  uint8_t average[8];               /* bytes 48 to 55 */
  uint8_t last[8];                  /* bytes 56 to 63 */
} TradabilityMessage;

/* any Tradability Message at all: every byte one the checker chooses */
static void any_tradability_message(TradabilityMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->instrument_number[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->number_of_operations[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->volume_int_648[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->amount[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->opening_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->maximum[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->minimum[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->average[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->last[i] = arbitrary(); }
}

/* Tradability Message to the wire: 64 bytes from at, returning where the next byte goes */
static size_t encode_tradability_message(const TradabilityMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument_number[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->number_of_operations[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->volume_int_648[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->amount[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->opening_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->maximum[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->minimum[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->average[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->last[i]; }

  return at;
}

/* Tradability Message off the wire: 64 bytes from at, returning where the next byte lies */
static size_t decode_tradability_message(TradabilityMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->instrument_number[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->number_of_operations[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->volume_int_648[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->amount[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->opening_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->maximum[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->minimum[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->average[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->last[i] = wire[at++]; }

  return at;
}

/* what was read of Tradability Message is what was written, byte for byte */
static void equal_tradability_message(const TradabilityMessage *read, const TradabilityMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->instrument_number[i] == written->instrument_number[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->number_of_operations[i] == written->number_of_operations[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->volume_int_648[i] == written->volume_int_648[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->amount[i] == written->amount[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->opening_price[i] == written->opening_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->maximum[i] == written->maximum[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->minimum[i] == written->minimum[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->average[i] == written->average[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->last[i] == written->last[i]); }
}

/* Tradability Message: written and read back, then read and written back */
static void check_tradability_message(void) {
  TradabilityMessage sent;
  TradabilityMessage got;
  uint8_t wire[64];
  uint8_t again[64];

  any_tradability_message(&sent);
  assert(encode_tradability_message(&sent, wire, 0) == 64);
  assert(decode_tradability_message(&got, wire, 0) == 64);
  equal_tradability_message(&got, &sent);

  for (size_t i = 0; i < 64; i++) { wire[i] = arbitrary(); }
  assert(decode_tradability_message(&got, wire, 0) == 64);
  assert(encode_tradability_message(&got, again, 0) == 64);
  for (size_t i = 0; i < 64; i++) { assert(again[i] == wire[i]); }
}

/* ---- Virtual Trades Message: 25 bytes ---------------------------------------- */

/* When an operation has been pre-assigned to the at closing and average day Price electronic books, a virtual trade message is sent, where also notifying of this operation. */
typedef struct {
  uint8_t instrument_number[4];   /* bytes 0 to 3 */
  uint8_t virtual_trades_status;  /* byte 4 */
  uint8_t operation_type;         /* byte 5 */
  uint8_t number[4];              /* bytes 6 to 9 */
  uint8_t volume_int_324[4];      /* bytes 10 to 13 */
  uint8_t concertation;           /* byte 14 */
  uint8_t buy[5];                 /* bytes 15 to 19 */
  uint8_t sell[5];                /* bytes 20 to 24 */
} VirtualTradesMessage;

/* any Virtual Trades Message at all: every byte one the checker chooses */
static void any_virtual_trades_message(VirtualTradesMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->instrument_number[i] = arbitrary(); }
  record->virtual_trades_status = arbitrary();
  record->operation_type = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->number[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->volume_int_324[i] = arbitrary(); }
  record->concertation = arbitrary();
  for (size_t i = 0; i < 5; i++) { record->buy[i] = arbitrary(); }
  for (size_t i = 0; i < 5; i++) { record->sell[i] = arbitrary(); }
}

/* Virtual Trades Message to the wire: 25 bytes from at, returning where the next byte goes */
static size_t encode_virtual_trades_message(const VirtualTradesMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument_number[i]; }
  wire[at++] = record->virtual_trades_status;
  wire[at++] = record->operation_type;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->number[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->volume_int_324[i]; }
  wire[at++] = record->concertation;
  for (size_t i = 0; i < 5; i++) { wire[at++] = record->buy[i]; }
  for (size_t i = 0; i < 5; i++) { wire[at++] = record->sell[i]; }

  return at;
}

/* Virtual Trades Message off the wire: 25 bytes from at, returning where the next byte lies */
static size_t decode_virtual_trades_message(VirtualTradesMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->instrument_number[i] = wire[at++]; }
  record->virtual_trades_status = wire[at++];
  record->operation_type = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->number[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->volume_int_324[i] = wire[at++]; }
  record->concertation = wire[at++];
  for (size_t i = 0; i < 5; i++) { record->buy[i] = wire[at++]; }
  for (size_t i = 0; i < 5; i++) { record->sell[i] = wire[at++]; }

  return at;
}

/* what was read of Virtual Trades Message is what was written, byte for byte */
static void equal_virtual_trades_message(const VirtualTradesMessage *read, const VirtualTradesMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->instrument_number[i] == written->instrument_number[i]); }
  assert(read->virtual_trades_status == written->virtual_trades_status);
  assert(read->operation_type == written->operation_type);
  for (size_t i = 0; i < 4; i++) { assert(read->number[i] == written->number[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->volume_int_324[i] == written->volume_int_324[i]); }
  assert(read->concertation == written->concertation);
  for (size_t i = 0; i < 5; i++) { assert(read->buy[i] == written->buy[i]); }
  for (size_t i = 0; i < 5; i++) { assert(read->sell[i] == written->sell[i]); }
}

/* Virtual Trades Message: written and read back, then read and written back */
static void check_virtual_trades_message(void) {
  VirtualTradesMessage sent;
  VirtualTradesMessage got;
  uint8_t wire[25];
  uint8_t again[25];

  any_virtual_trades_message(&sent);
  assert(encode_virtual_trades_message(&sent, wire, 0) == 25);
  assert(decode_virtual_trades_message(&got, wire, 0) == 25);
  equal_virtual_trades_message(&got, &sent);

  for (size_t i = 0; i < 25; i++) { wire[i] = arbitrary(); }
  assert(decode_virtual_trades_message(&got, wire, 0) == 25);
  assert(encode_virtual_trades_message(&got, again, 0) == 25);
  for (size_t i = 0; i < 25; i++) { assert(again[i] == wire[i]); }
}

/* ---- Best Offer Message: 18 bytes -------------------------------------------- */

/* Message sent by instrument when best offer changes in the electronic book. */
typedef struct {
  uint8_t instrument_number[4];  /* bytes 0 to 3 */
  uint8_t volume_int_324[4];     /* bytes 4 to 7 */
  uint8_t price_rate[8];         /* bytes 8 to 15 */
  uint8_t offer_direction;       /* byte 16 */
  uint8_t operation_type;        /* byte 17 */
} BestOfferMessage;

/* any Best Offer Message at all: every byte one the checker chooses */
static void any_best_offer_message(BestOfferMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->instrument_number[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->volume_int_324[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->price_rate[i] = arbitrary(); }
  record->offer_direction = arbitrary();
  record->operation_type = arbitrary();
}

/* Best Offer Message to the wire: 18 bytes from at, returning where the next byte goes */
static size_t encode_best_offer_message(const BestOfferMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument_number[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->volume_int_324[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price_rate[i]; }
  wire[at++] = record->offer_direction;
  wire[at++] = record->operation_type;

  return at;
}

/* Best Offer Message off the wire: 18 bytes from at, returning where the next byte lies */
static size_t decode_best_offer_message(BestOfferMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->instrument_number[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->volume_int_324[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->price_rate[i] = wire[at++]; }
  record->offer_direction = wire[at++];
  record->operation_type = wire[at++];

  return at;
}

/* what was read of Best Offer Message is what was written, byte for byte */
static void equal_best_offer_message(const BestOfferMessage *read, const BestOfferMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->instrument_number[i] == written->instrument_number[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->volume_int_324[i] == written->volume_int_324[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->price_rate[i] == written->price_rate[i]); }
  assert(read->offer_direction == written->offer_direction);
  assert(read->operation_type == written->operation_type);
}

/* Best Offer Message: written and read back, then read and written back */
static void check_best_offer_message(void) {
  BestOfferMessage sent;
  BestOfferMessage got;
  uint8_t wire[18];
  uint8_t again[18];

  any_best_offer_message(&sent);
  assert(encode_best_offer_message(&sent, wire, 0) == 18);
  assert(decode_best_offer_message(&got, wire, 0) == 18);
  equal_best_offer_message(&got, &sent);

  for (size_t i = 0; i < 18; i++) { wire[i] = arbitrary(); }
  assert(decode_best_offer_message(&got, wire, 0) == 18);
  assert(encode_best_offer_message(&got, again, 0) == 18);
  for (size_t i = 0; i < 18; i++) { assert(again[i] == wire[i]); }
}

/* ---- General Indices Message: 33 bytes --------------------------------------- */

/* Information about the MSE Indices. */
typedef struct {
  uint8_t component[2];       /* bytes 0 to 1 */
  uint8_t sector;             /* byte 2 */
  uint8_t indices_hour[8];    /* bytes 3 to 10 */
  uint8_t volume_int_648[8];  /* bytes 11 to 18 */
  uint8_t indices[4];         /* bytes 19 to 22 */
  uint8_t variation[4];       /* bytes 23 to 26 */
  uint8_t percentage[4];      /* bytes 27 to 30 */
  uint8_t trend;              /* byte 31 */
  uint8_t indices_status;     /* byte 32 */
} GeneralIndicesMessage;

/* any General Indices Message at all: every byte one the checker chooses */
static void any_general_indices_message(GeneralIndicesMessage *record) {
  for (size_t i = 0; i < 2; i++) { record->component[i] = arbitrary(); }
  record->sector = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->indices_hour[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->volume_int_648[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->indices[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->variation[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->percentage[i] = arbitrary(); }
  record->trend = arbitrary();
  record->indices_status = arbitrary();
}

/* General Indices Message to the wire: 33 bytes from at, returning where the next byte goes */
static size_t encode_general_indices_message(const GeneralIndicesMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->component[i]; }
  wire[at++] = record->sector;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->indices_hour[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->volume_int_648[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->indices[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->variation[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->percentage[i]; }
  wire[at++] = record->trend;
  wire[at++] = record->indices_status;

  return at;
}

/* General Indices Message off the wire: 33 bytes from at, returning where the next byte lies */
static size_t decode_general_indices_message(GeneralIndicesMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->component[i] = wire[at++]; }
  record->sector = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->indices_hour[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->volume_int_648[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->indices[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->variation[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->percentage[i] = wire[at++]; }
  record->trend = wire[at++];
  record->indices_status = wire[at++];

  return at;
}

/* what was read of General Indices Message is what was written, byte for byte */
static void equal_general_indices_message(const GeneralIndicesMessage *read, const GeneralIndicesMessage *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->component[i] == written->component[i]); }
  assert(read->sector == written->sector);
  for (size_t i = 0; i < 8; i++) { assert(read->indices_hour[i] == written->indices_hour[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->volume_int_648[i] == written->volume_int_648[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->indices[i] == written->indices[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->variation[i] == written->variation[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->percentage[i] == written->percentage[i]); }
  assert(read->trend == written->trend);
  assert(read->indices_status == written->indices_status);
}

/* General Indices Message: written and read back, then read and written back */
static void check_general_indices_message(void) {
  GeneralIndicesMessage sent;
  GeneralIndicesMessage got;
  uint8_t wire[33];
  uint8_t again[33];

  any_general_indices_message(&sent);
  assert(encode_general_indices_message(&sent, wire, 0) == 33);
  assert(decode_general_indices_message(&got, wire, 0) == 33);
  equal_general_indices_message(&got, &sent);

  for (size_t i = 0; i < 33; i++) { wire[i] = arbitrary(); }
  assert(decode_general_indices_message(&got, wire, 0) == 33);
  assert(encode_general_indices_message(&got, again, 0) == 33);
  for (size_t i = 0; i < 33; i++) { assert(again[i] == wire[i]); }
}

/* ---- Inav Message: 12 bytes -------------------------------------------------- */

/* TRACS dissemination during continuous market trading hours. */
typedef struct {
  uint8_t trac_number[4];                /* bytes 0 to 3 */
  uint8_t theoretical_current_price[8];  /* bytes 4 to 11 */
} InavMessage;

/* any Inav Message at all: every byte one the checker chooses */
static void any_inav_message(InavMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->trac_number[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->theoretical_current_price[i] = arbitrary(); }
}

/* Inav Message to the wire: 12 bytes from at, returning where the next byte goes */
static size_t encode_inav_message(const InavMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->trac_number[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->theoretical_current_price[i]; }

  return at;
}

/* Inav Message off the wire: 12 bytes from at, returning where the next byte lies */
static size_t decode_inav_message(InavMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->trac_number[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->theoretical_current_price[i] = wire[at++]; }

  return at;
}

/* what was read of Inav Message is what was written, byte for byte */
static void equal_inav_message(const InavMessage *read, const InavMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->trac_number[i] == written->trac_number[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->theoretical_current_price[i] == written->theoretical_current_price[i]); }
}

/* Inav Message: written and read back, then read and written back */
static void check_inav_message(void) {
  InavMessage sent;
  InavMessage got;
  uint8_t wire[12];
  uint8_t again[12];

  any_inav_message(&sent);
  assert(encode_inav_message(&sent, wire, 0) == 12);
  assert(decode_inav_message(&got, wire, 0) == 12);
  equal_inav_message(&got, &sent);

  for (size_t i = 0; i < 12; i++) { wire[i] = arbitrary(); }
  assert(decode_inav_message(&got, wire, 0) == 12);
  assert(encode_inav_message(&got, again, 0) == 12);
  for (size_t i = 0; i < 12; i++) { assert(again[i] == wire[i]); }
}

/* ---- What esbmc checks ------------------------------------------------------- */

/* every record of the protocol, each on its own buffers */
static void checks(void) {
  check_i_n_t_r_a_multicast_header();
  check_message_header();
  check_events_system_message();
  check_trade_cancellation_message();
  check_status_changes_message();
  check_weighted_average_price_settlement_prices_message();
  check_capital_trades_message();
  check_probable_allocation_price_message();
  check_continuous_auctions_beginning_message();
  check_middle_price_existing_quotes_message();
  check_registry_operations_message();
  check_mutual_fund_trades_message();
  check_tradability_message();
  check_virtual_trades_message();
  check_best_offer_message();
  check_general_indices_message();
  check_inav_message();
}

int main(void) {
#ifdef CONCRETE
  for (pattern = 0; pattern < 4; pattern++) { checks(); }
#else
  checks();
#endif

  return 0;
}
