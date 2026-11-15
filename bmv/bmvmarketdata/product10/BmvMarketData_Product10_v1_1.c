// bmv/bmvmarketdata/product10/BmvMarketData_Product10_v1_1.c
/*
 * Bolsa Mexicana de Valores Bmv Market Data Product 10
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

/* ---- Best Offer Message: 18 bytes -------------------------------------------- */

/* Message sent by instrument when best offer changes in the electronic book. */
typedef struct {
  uint8_t instrument_number[4];  /* bytes 0 to 3 */
  uint8_t volume[4];             /* bytes 4 to 7 */
  uint8_t price_rate[8];         /* bytes 8 to 15 */
  uint8_t offer_direction;       /* byte 16 */
  uint8_t operation_type;        /* byte 17 */
} BestOfferMessage;

/* any Best Offer Message at all: every byte one the checker chooses */
static void any_best_offer_message(BestOfferMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->instrument_number[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->volume[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->price_rate[i] = arbitrary(); }
  record->offer_direction = arbitrary();
  record->operation_type = arbitrary();
}

/* Best Offer Message to the wire: 18 bytes from at, returning where the next byte goes */
static size_t encode_best_offer_message(const BestOfferMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument_number[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->volume[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price_rate[i]; }
  wire[at++] = record->offer_direction;
  wire[at++] = record->operation_type;

  return at;
}

/* Best Offer Message off the wire: 18 bytes from at, returning where the next byte lies */
static size_t decode_best_offer_message(BestOfferMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->instrument_number[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->volume[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->price_rate[i] = wire[at++]; }
  record->offer_direction = wire[at++];
  record->operation_type = wire[at++];

  return at;
}

/* what was read of Best Offer Message is what was written, byte for byte */
static void equal_best_offer_message(const BestOfferMessage *read, const BestOfferMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->instrument_number[i] == written->instrument_number[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->volume[i] == written->volume[i]); }
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

/* ---- Open Interest Message: 8 bytes ------------------------------------------ */

/* Open Interest */
typedef struct {
  uint8_t instrument_number[4];  /* bytes 0 to 3 */
  uint8_t open_interest[4];      /* bytes 4 to 7 */
} OpenInterestMessage;

/* any Open Interest Message at all: every byte one the checker chooses */
static void any_open_interest_message(OpenInterestMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->instrument_number[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->open_interest[i] = arbitrary(); }
}

/* Open Interest Message to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_open_interest_message(const OpenInterestMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument_number[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->open_interest[i]; }

  return at;
}

/* Open Interest Message off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_open_interest_message(OpenInterestMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->instrument_number[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->open_interest[i] = wire[at++]; }

  return at;
}

/* what was read of Open Interest Message is what was written, byte for byte */
static void equal_open_interest_message(const OpenInterestMessage *read, const OpenInterestMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->instrument_number[i] == written->instrument_number[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->open_interest[i] == written->open_interest[i]); }
}

/* Open Interest Message: written and read back, then read and written back */
static void check_open_interest_message(void) {
  OpenInterestMessage sent;
  OpenInterestMessage got;
  uint8_t wire[8];
  uint8_t again[8];

  any_open_interest_message(&sent);
  assert(encode_open_interest_message(&sent, wire, 0) == 8);
  assert(decode_open_interest_message(&got, wire, 0) == 8);
  equal_open_interest_message(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_open_interest_message(&got, wire, 0) == 8);
  assert(encode_open_interest_message(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Derivatives Market Trades Message: 43 bytes ----------------------------- */

/* Contains information on any MexDer accepted transaction. */
typedef struct {
  uint8_t instrument_number[4];    /* bytes 0 to 3 */
  uint8_t trade_time[8];           /* bytes 4 to 11 */
  uint8_t volume[4];               /* bytes 12 to 15 */
  uint8_t price_rate[8];           /* bytes 16 to 23 */
  uint8_t concertation_type;       /* byte 24 */
  uint8_t trade_number[4];         /* bytes 25 to 28 */
  uint8_t operation_type;          /* byte 29 */
  uint8_t amount[8];               /* bytes 30 to 37 */
  uint8_t parent_trade_number[4];  /* bytes 38 to 41 */
  uint8_t leg_type;                /* byte 42 */
} DerivativesMarketTradesMessage;

/* any Derivatives Market Trades Message at all: every byte one the checker chooses */
static void any_derivatives_market_trades_message(DerivativesMarketTradesMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->instrument_number[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->trade_time[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->volume[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->price_rate[i] = arbitrary(); }
  record->concertation_type = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->trade_number[i] = arbitrary(); }
  record->operation_type = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->amount[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->parent_trade_number[i] = arbitrary(); }
  record->leg_type = arbitrary();
}

/* Derivatives Market Trades Message to the wire: 43 bytes from at, returning where the next byte goes */
static size_t encode_derivatives_market_trades_message(const DerivativesMarketTradesMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument_number[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->trade_time[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->volume[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price_rate[i]; }
  wire[at++] = record->concertation_type;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->trade_number[i]; }
  wire[at++] = record->operation_type;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->amount[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->parent_trade_number[i]; }
  wire[at++] = record->leg_type;

  return at;
}

/* Derivatives Market Trades Message off the wire: 43 bytes from at, returning where the next byte lies */
static size_t decode_derivatives_market_trades_message(DerivativesMarketTradesMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->instrument_number[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->trade_time[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->volume[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->price_rate[i] = wire[at++]; }
  record->concertation_type = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->trade_number[i] = wire[at++]; }
  record->operation_type = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->amount[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->parent_trade_number[i] = wire[at++]; }
  record->leg_type = wire[at++];

  return at;
}

/* what was read of Derivatives Market Trades Message is what was written, byte for byte */
static void equal_derivatives_market_trades_message(const DerivativesMarketTradesMessage *read, const DerivativesMarketTradesMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->instrument_number[i] == written->instrument_number[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->trade_time[i] == written->trade_time[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->volume[i] == written->volume[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->price_rate[i] == written->price_rate[i]); }
  assert(read->concertation_type == written->concertation_type);
  for (size_t i = 0; i < 4; i++) { assert(read->trade_number[i] == written->trade_number[i]); }
  assert(read->operation_type == written->operation_type);
  for (size_t i = 0; i < 8; i++) { assert(read->amount[i] == written->amount[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->parent_trade_number[i] == written->parent_trade_number[i]); }
  assert(read->leg_type == written->leg_type);
}

/* Derivatives Market Trades Message: written and read back, then read and written back */
static void check_derivatives_market_trades_message(void) {
  DerivativesMarketTradesMessage sent;
  DerivativesMarketTradesMessage got;
  uint8_t wire[43];
  uint8_t again[43];

  any_derivatives_market_trades_message(&sent);
  assert(encode_derivatives_market_trades_message(&sent, wire, 0) == 43);
  assert(decode_derivatives_market_trades_message(&got, wire, 0) == 43);
  equal_derivatives_market_trades_message(&got, &sent);

  for (size_t i = 0; i < 43; i++) { wire[i] = arbitrary(); }
  assert(decode_derivatives_market_trades_message(&got, wire, 0) == 43);
  assert(encode_derivatives_market_trades_message(&got, again, 0) == 43);
  for (size_t i = 0; i < 43; i++) { assert(again[i] == wire[i]); }
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
  check_best_offer_message();
  check_open_interest_message();
  check_derivatives_market_trades_message();
}

int main(void) {
#ifdef CONCRETE
  for (pattern = 0; pattern < 4; pattern++) { checks(); }
#else
  checks();
#endif

  return 0;
}
