// bmv/bmvmarketdata/product25/BmvMarketData_Product25_v1_1.c
/*
 * Bolsa Mexicana de Valores Bmv Market Data Product 25
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

/* ---- Mutual Funds Trades Message: 53 bytes ----------------------------------- */

/* Any transaction made in mutual funds is reported. */
typedef struct {
  uint8_t instrument_number[4];          /* bytes 0 to 3 */
  uint8_t origin;                        /* byte 4 */
  uint8_t date_of_the_trade[8];          /* bytes 5 to 12 */
  uint8_t price[8];                      /* bytes 13 to 20 */
  uint8_t book_value[8];                 /* bytes 21 to 28 */
  uint8_t number_of_sales_trades[4];     /* bytes 29 to 32 */
  uint8_t sales_volume[8];               /* bytes 33 to 40 */
  uint8_t number_of_purchase_trades[4];  /* bytes 41 to 44 */
  uint8_t purchase_volume[8];            /* bytes 45 to 52 */
} MutualFundsTradesMessage;

/* any Mutual Funds Trades Message at all: every byte one the checker chooses */
static void any_mutual_funds_trades_message(MutualFundsTradesMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->instrument_number[i] = arbitrary(); }
  record->origin = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->date_of_the_trade[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->book_value[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->number_of_sales_trades[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->sales_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->number_of_purchase_trades[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->purchase_volume[i] = arbitrary(); }
}

/* Mutual Funds Trades Message to the wire: 53 bytes from at, returning where the next byte goes */
static size_t encode_mutual_funds_trades_message(const MutualFundsTradesMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument_number[i]; }
  wire[at++] = record->origin;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->date_of_the_trade[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->book_value[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->number_of_sales_trades[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->sales_volume[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->number_of_purchase_trades[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->purchase_volume[i]; }

  return at;
}

/* Mutual Funds Trades Message off the wire: 53 bytes from at, returning where the next byte lies */
static size_t decode_mutual_funds_trades_message(MutualFundsTradesMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->instrument_number[i] = wire[at++]; }
  record->origin = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->date_of_the_trade[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->book_value[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->number_of_sales_trades[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->sales_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->number_of_purchase_trades[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->purchase_volume[i] = wire[at++]; }

  return at;
}

/* what was read of Mutual Funds Trades Message is what was written, byte for byte */
static void equal_mutual_funds_trades_message(const MutualFundsTradesMessage *read, const MutualFundsTradesMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->instrument_number[i] == written->instrument_number[i]); }
  assert(read->origin == written->origin);
  for (size_t i = 0; i < 8; i++) { assert(read->date_of_the_trade[i] == written->date_of_the_trade[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->price[i] == written->price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->book_value[i] == written->book_value[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->number_of_sales_trades[i] == written->number_of_sales_trades[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->sales_volume[i] == written->sales_volume[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->number_of_purchase_trades[i] == written->number_of_purchase_trades[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->purchase_volume[i] == written->purchase_volume[i]); }
}

/* Mutual Funds Trades Message: written and read back, then read and written back */
static void check_mutual_funds_trades_message(void) {
  MutualFundsTradesMessage sent;
  MutualFundsTradesMessage got;
  uint8_t wire[53];
  uint8_t again[53];

  any_mutual_funds_trades_message(&sent);
  assert(encode_mutual_funds_trades_message(&sent, wire, 0) == 53);
  assert(decode_mutual_funds_trades_message(&got, wire, 0) == 53);
  equal_mutual_funds_trades_message(&got, &sent);

  for (size_t i = 0; i < 53; i++) { wire[i] = arbitrary(); }
  assert(decode_mutual_funds_trades_message(&got, wire, 0) == 53);
  assert(encode_mutual_funds_trades_message(&got, again, 0) == 53);
  for (size_t i = 0; i < 53; i++) { assert(again[i] == wire[i]); }
}

/* ---- Opening Of Continuous Auctions Message: 21 bytes ------------------------ */

/* The message is sent when one of the ongoing, volatility or SIC bidding sessions is generated. */
typedef struct {
  uint8_t instrument_number[4];             /* bytes 0 to 3 */
  uint8_t origin;                           /* byte 4 */
  uint8_t auction_session_startup_time[8];  /* bytes 5 to 12 */
  uint8_t auction_session_end_time[8];      /* bytes 13 to 20 */
} OpeningOfContinuousAuctionsMessage;

/* any Opening Of Continuous Auctions Message at all: every byte one the checker chooses */
static void any_opening_of_continuous_auctions_message(OpeningOfContinuousAuctionsMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->instrument_number[i] = arbitrary(); }
  record->origin = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->auction_session_startup_time[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->auction_session_end_time[i] = arbitrary(); }
}

/* Opening Of Continuous Auctions Message to the wire: 21 bytes from at, returning where the next byte goes */
static size_t encode_opening_of_continuous_auctions_message(const OpeningOfContinuousAuctionsMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument_number[i]; }
  wire[at++] = record->origin;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->auction_session_startup_time[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->auction_session_end_time[i]; }

  return at;
}

/* Opening Of Continuous Auctions Message off the wire: 21 bytes from at, returning where the next byte lies */
static size_t decode_opening_of_continuous_auctions_message(OpeningOfContinuousAuctionsMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->instrument_number[i] = wire[at++]; }
  record->origin = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->auction_session_startup_time[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->auction_session_end_time[i] = wire[at++]; }

  return at;
}

/* what was read of Opening Of Continuous Auctions Message is what was written, byte for byte */
static void equal_opening_of_continuous_auctions_message(const OpeningOfContinuousAuctionsMessage *read, const OpeningOfContinuousAuctionsMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->instrument_number[i] == written->instrument_number[i]); }
  assert(read->origin == written->origin);
  for (size_t i = 0; i < 8; i++) { assert(read->auction_session_startup_time[i] == written->auction_session_startup_time[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->auction_session_end_time[i] == written->auction_session_end_time[i]); }
}

/* Opening Of Continuous Auctions Message: written and read back, then read and written back */
static void check_opening_of_continuous_auctions_message(void) {
  OpeningOfContinuousAuctionsMessage sent;
  OpeningOfContinuousAuctionsMessage got;
  uint8_t wire[21];
  uint8_t again[21];

  any_opening_of_continuous_auctions_message(&sent);
  assert(encode_opening_of_continuous_auctions_message(&sent, wire, 0) == 21);
  assert(decode_opening_of_continuous_auctions_message(&got, wire, 0) == 21);
  equal_opening_of_continuous_auctions_message(&got, &sent);

  for (size_t i = 0; i < 21; i++) { wire[i] = arbitrary(); }
  assert(decode_opening_of_continuous_auctions_message(&got, wire, 0) == 21);
  assert(encode_opening_of_continuous_auctions_message(&got, again, 0) == 21);
  for (size_t i = 0; i < 21; i++) { assert(again[i] == wire[i]); }
}

/* ---- Existence Of Bids At Mid Price Message: 6 bytes ------------------------- */

/* This message is generated when an instrument enters a bid in the hidden electronic book At Mean Price. */
typedef struct {
  uint8_t instrument_number[4];  /* bytes 0 to 3 */
  uint8_t origin;                /* byte 4 */
  uint8_t bids_existing;         /* byte 5 */
} ExistenceOfBidsAtMidPriceMessage;

/* any Existence Of Bids At Mid Price Message at all: every byte one the checker chooses */
static void any_existence_of_bids_at_mid_price_message(ExistenceOfBidsAtMidPriceMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->instrument_number[i] = arbitrary(); }
  record->origin = arbitrary();
  record->bids_existing = arbitrary();
}

/* Existence Of Bids At Mid Price Message to the wire: 6 bytes from at, returning where the next byte goes */
static size_t encode_existence_of_bids_at_mid_price_message(const ExistenceOfBidsAtMidPriceMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument_number[i]; }
  wire[at++] = record->origin;
  wire[at++] = record->bids_existing;

  return at;
}

/* Existence Of Bids At Mid Price Message off the wire: 6 bytes from at, returning where the next byte lies */
static size_t decode_existence_of_bids_at_mid_price_message(ExistenceOfBidsAtMidPriceMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->instrument_number[i] = wire[at++]; }
  record->origin = wire[at++];
  record->bids_existing = wire[at++];

  return at;
}

/* what was read of Existence Of Bids At Mid Price Message is what was written, byte for byte */
static void equal_existence_of_bids_at_mid_price_message(const ExistenceOfBidsAtMidPriceMessage *read, const ExistenceOfBidsAtMidPriceMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->instrument_number[i] == written->instrument_number[i]); }
  assert(read->origin == written->origin);
  assert(read->bids_existing == written->bids_existing);
}

/* Existence Of Bids At Mid Price Message: written and read back, then read and written back */
static void check_existence_of_bids_at_mid_price_message(void) {
  ExistenceOfBidsAtMidPriceMessage sent;
  ExistenceOfBidsAtMidPriceMessage got;
  uint8_t wire[6];
  uint8_t again[6];

  any_existence_of_bids_at_mid_price_message(&sent);
  assert(encode_existence_of_bids_at_mid_price_message(&sent, wire, 0) == 6);
  assert(decode_existence_of_bids_at_mid_price_message(&got, wire, 0) == 6);
  equal_existence_of_bids_at_mid_price_message(&got, &sent);

  for (size_t i = 0; i < 6; i++) { wire[i] = arbitrary(); }
  assert(decode_existence_of_bids_at_mid_price_message(&got, wire, 0) == 6);
  assert(encode_existence_of_bids_at_mid_price_message(&got, again, 0) == 6);
  for (size_t i = 0; i < 6; i++) { assert(again[i] == wire[i]); }
}

/* ---- Catalogue Of Debt And Metals Instruments Message: 103 bytes ------------- */

/* Catalogue sent for instruments pertaining to the Local Fixed rate, Global Fixed rate and metals markets. */
typedef struct {
  uint8_t number_of_the_instrument[4];  /* bytes 0 to 3 */
  uint8_t origin;                       /* byte 4 */
  uint8_t type_of_value[2];             /* bytes 5 to 6 */
  uint8_t issuing_company[7];           /* bytes 7 to 13 */
  uint8_t issuance[6];                  /* bytes 14 to 19 */
  uint8_t date_of_issuance[8];          /* bytes 20 to 27 */
  uint8_t date_of_maturity[8];          /* bytes 28 to 35 */
  uint8_t price_rate_of_reference[8];   /* bytes 36 to 43 */
  uint8_t date_of_reference[8];         /* bytes 44 to 51 */
  uint8_t reference;                    /* byte 52 */
  uint8_t term_days[2];                 /* bytes 53 to 54 */
  uint8_t coupon_period[2];             /* bytes 55 to 56 */
  uint8_t isin[12];                     /* bytes 57 to 68 */
  uint8_t market;                       /* byte 69 */
  uint8_t current_nominal_value[8];     /* bytes 70 to 77 */
  uint8_t original_nominal_value[8];    /* bytes 78 to 85 */
  uint8_t outstanding_shares[8];        /* bytes 86 to 93 */
  uint8_t amount_placed[8];             /* bytes 94 to 101 */
  uint8_t trades_rate_price;            /* byte 102 */
} CatalogueOfDebtAndMetalsInstrumentsMessage;

/* any Catalogue Of Debt And Metals Instruments Message at all: every byte one the checker chooses */
static void any_catalogue_of_debt_and_metals_instruments_message(CatalogueOfDebtAndMetalsInstrumentsMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->number_of_the_instrument[i] = arbitrary(); }
  record->origin = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->type_of_value[i] = arbitrary(); }
  for (size_t i = 0; i < 7; i++) { record->issuing_company[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->issuance[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->date_of_issuance[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->date_of_maturity[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->price_rate_of_reference[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->date_of_reference[i] = arbitrary(); }
  record->reference = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->term_days[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->coupon_period[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->isin[i] = arbitrary(); }
  record->market = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->current_nominal_value[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->original_nominal_value[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->outstanding_shares[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->amount_placed[i] = arbitrary(); }
  record->trades_rate_price = arbitrary();
}

/* Catalogue Of Debt And Metals Instruments Message to the wire: 103 bytes from at, returning where the next byte goes */
static size_t encode_catalogue_of_debt_and_metals_instruments_message(const CatalogueOfDebtAndMetalsInstrumentsMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->number_of_the_instrument[i]; }
  wire[at++] = record->origin;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->type_of_value[i]; }
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->issuing_company[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->issuance[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->date_of_issuance[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->date_of_maturity[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price_rate_of_reference[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->date_of_reference[i]; }
  wire[at++] = record->reference;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->term_days[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->coupon_period[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->isin[i]; }
  wire[at++] = record->market;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->current_nominal_value[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->original_nominal_value[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->outstanding_shares[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->amount_placed[i]; }
  wire[at++] = record->trades_rate_price;

  return at;
}

/* Catalogue Of Debt And Metals Instruments Message off the wire: 103 bytes from at, returning where the next byte lies */
static size_t decode_catalogue_of_debt_and_metals_instruments_message(CatalogueOfDebtAndMetalsInstrumentsMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->number_of_the_instrument[i] = wire[at++]; }
  record->origin = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->type_of_value[i] = wire[at++]; }
  for (size_t i = 0; i < 7; i++) { record->issuing_company[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->issuance[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->date_of_issuance[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->date_of_maturity[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->price_rate_of_reference[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->date_of_reference[i] = wire[at++]; }
  record->reference = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->term_days[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->coupon_period[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->isin[i] = wire[at++]; }
  record->market = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->current_nominal_value[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->original_nominal_value[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->outstanding_shares[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->amount_placed[i] = wire[at++]; }
  record->trades_rate_price = wire[at++];

  return at;
}

/* what was read of Catalogue Of Debt And Metals Instruments Message is what was written, byte for byte */
static void equal_catalogue_of_debt_and_metals_instruments_message(const CatalogueOfDebtAndMetalsInstrumentsMessage *read, const CatalogueOfDebtAndMetalsInstrumentsMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->number_of_the_instrument[i] == written->number_of_the_instrument[i]); }
  assert(read->origin == written->origin);
  for (size_t i = 0; i < 2; i++) { assert(read->type_of_value[i] == written->type_of_value[i]); }
  for (size_t i = 0; i < 7; i++) { assert(read->issuing_company[i] == written->issuing_company[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->issuance[i] == written->issuance[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->date_of_issuance[i] == written->date_of_issuance[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->date_of_maturity[i] == written->date_of_maturity[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->price_rate_of_reference[i] == written->price_rate_of_reference[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->date_of_reference[i] == written->date_of_reference[i]); }
  assert(read->reference == written->reference);
  for (size_t i = 0; i < 2; i++) { assert(read->term_days[i] == written->term_days[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->coupon_period[i] == written->coupon_period[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->isin[i] == written->isin[i]); }
  assert(read->market == written->market);
  for (size_t i = 0; i < 8; i++) { assert(read->current_nominal_value[i] == written->current_nominal_value[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->original_nominal_value[i] == written->original_nominal_value[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->outstanding_shares[i] == written->outstanding_shares[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->amount_placed[i] == written->amount_placed[i]); }
  assert(read->trades_rate_price == written->trades_rate_price);
}

/* Catalogue Of Debt And Metals Instruments Message: written and read back, then read and written back */
static void check_catalogue_of_debt_and_metals_instruments_message(void) {
  CatalogueOfDebtAndMetalsInstrumentsMessage sent;
  CatalogueOfDebtAndMetalsInstrumentsMessage got;
  uint8_t wire[103];
  uint8_t again[103];

  any_catalogue_of_debt_and_metals_instruments_message(&sent);
  assert(encode_catalogue_of_debt_and_metals_instruments_message(&sent, wire, 0) == 103);
  assert(decode_catalogue_of_debt_and_metals_instruments_message(&got, wire, 0) == 103);
  equal_catalogue_of_debt_and_metals_instruments_message(&got, &sent);

  for (size_t i = 0; i < 103; i++) { wire[i] = arbitrary(); }
  assert(decode_catalogue_of_debt_and_metals_instruments_message(&got, wire, 0) == 103);
  assert(encode_catalogue_of_debt_and_metals_instruments_message(&got, again, 0) == 103);
  for (size_t i = 0; i < 103; i++) { assert(again[i] == wire[i]); }
}

/* ---- Catalog Sent For Instruments Belonging To Mutual Funds Message: 78 bytes ---- */

/* Catalogue sent for instrument pertaining to the investment companies. */
typedef struct {
  uint8_t number_of_the_instrument[4];  /* bytes 0 to 3 */
  uint8_t origin;                       /* byte 4 */
  uint8_t type_of_value[2];             /* bytes 5 to 6 */
  uint8_t issuing_company[7];           /* bytes 7 to 13 */
  uint8_t series[6];                    /* bytes 14 to 19 */
  uint8_t sector;                       /* byte 20 */
  uint8_t sub_sector;                   /* byte 21 */
  uint8_t industry;                     /* byte 22 */
  uint8_t sub_industry;                 /* byte 23 */
  uint8_t trading_company[10];          /* bytes 24 to 33 */
  uint8_t reference_price[8];           /* bytes 34 to 41 */
  uint8_t reference_date[8];            /* bytes 42 to 49 */
  uint8_t reference;                    /* byte 50 */
  uint8_t isin[12];                     /* bytes 51 to 62 */
  uint8_t rating[15];                   /* bytes 63 to 77 */
} CatalogSentForInstrumentsBelongingToMutualFundsMessage;

/* any Catalog Sent For Instruments Belonging To Mutual Funds Message at all: every byte one the checker chooses */
static void any_catalog_sent_for_instruments_belonging_to_mutual_funds_message(CatalogSentForInstrumentsBelongingToMutualFundsMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->number_of_the_instrument[i] = arbitrary(); }
  record->origin = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->type_of_value[i] = arbitrary(); }
  for (size_t i = 0; i < 7; i++) { record->issuing_company[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->series[i] = arbitrary(); }
  record->sector = arbitrary();
  record->sub_sector = arbitrary();
  record->industry = arbitrary();
  record->sub_industry = arbitrary();
  for (size_t i = 0; i < 10; i++) { record->trading_company[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->reference_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->reference_date[i] = arbitrary(); }
  record->reference = arbitrary();
  for (size_t i = 0; i < 12; i++) { record->isin[i] = arbitrary(); }
  for (size_t i = 0; i < 15; i++) { record->rating[i] = arbitrary(); }
}

/* Catalog Sent For Instruments Belonging To Mutual Funds Message to the wire: 78 bytes from at, returning where the next byte goes */
static size_t encode_catalog_sent_for_instruments_belonging_to_mutual_funds_message(const CatalogSentForInstrumentsBelongingToMutualFundsMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->number_of_the_instrument[i]; }
  wire[at++] = record->origin;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->type_of_value[i]; }
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->issuing_company[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->series[i]; }
  wire[at++] = record->sector;
  wire[at++] = record->sub_sector;
  wire[at++] = record->industry;
  wire[at++] = record->sub_industry;
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->trading_company[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->reference_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->reference_date[i]; }
  wire[at++] = record->reference;
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->isin[i]; }
  for (size_t i = 0; i < 15; i++) { wire[at++] = record->rating[i]; }

  return at;
}

/* Catalog Sent For Instruments Belonging To Mutual Funds Message off the wire: 78 bytes from at, returning where the next byte lies */
static size_t decode_catalog_sent_for_instruments_belonging_to_mutual_funds_message(CatalogSentForInstrumentsBelongingToMutualFundsMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->number_of_the_instrument[i] = wire[at++]; }
  record->origin = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->type_of_value[i] = wire[at++]; }
  for (size_t i = 0; i < 7; i++) { record->issuing_company[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->series[i] = wire[at++]; }
  record->sector = wire[at++];
  record->sub_sector = wire[at++];
  record->industry = wire[at++];
  record->sub_industry = wire[at++];
  for (size_t i = 0; i < 10; i++) { record->trading_company[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->reference_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->reference_date[i] = wire[at++]; }
  record->reference = wire[at++];
  for (size_t i = 0; i < 12; i++) { record->isin[i] = wire[at++]; }
  for (size_t i = 0; i < 15; i++) { record->rating[i] = wire[at++]; }

  return at;
}

/* what was read of Catalog Sent For Instruments Belonging To Mutual Funds Message is what was written, byte for byte */
static void equal_catalog_sent_for_instruments_belonging_to_mutual_funds_message(const CatalogSentForInstrumentsBelongingToMutualFundsMessage *read, const CatalogSentForInstrumentsBelongingToMutualFundsMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->number_of_the_instrument[i] == written->number_of_the_instrument[i]); }
  assert(read->origin == written->origin);
  for (size_t i = 0; i < 2; i++) { assert(read->type_of_value[i] == written->type_of_value[i]); }
  for (size_t i = 0; i < 7; i++) { assert(read->issuing_company[i] == written->issuing_company[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->series[i] == written->series[i]); }
  assert(read->sector == written->sector);
  assert(read->sub_sector == written->sub_sector);
  assert(read->industry == written->industry);
  assert(read->sub_industry == written->sub_industry);
  for (size_t i = 0; i < 10; i++) { assert(read->trading_company[i] == written->trading_company[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->reference_price[i] == written->reference_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->reference_date[i] == written->reference_date[i]); }
  assert(read->reference == written->reference);
  for (size_t i = 0; i < 12; i++) { assert(read->isin[i] == written->isin[i]); }
  for (size_t i = 0; i < 15; i++) { assert(read->rating[i] == written->rating[i]); }
}

/* Catalog Sent For Instruments Belonging To Mutual Funds Message: written and read back, then read and written back */
static void check_catalog_sent_for_instruments_belonging_to_mutual_funds_message(void) {
  CatalogSentForInstrumentsBelongingToMutualFundsMessage sent;
  CatalogSentForInstrumentsBelongingToMutualFundsMessage got;
  uint8_t wire[78];
  uint8_t again[78];

  any_catalog_sent_for_instruments_belonging_to_mutual_funds_message(&sent);
  assert(encode_catalog_sent_for_instruments_belonging_to_mutual_funds_message(&sent, wire, 0) == 78);
  assert(decode_catalog_sent_for_instruments_belonging_to_mutual_funds_message(&got, wire, 0) == 78);
  equal_catalog_sent_for_instruments_belonging_to_mutual_funds_message(&got, &sent);

  for (size_t i = 0; i < 78; i++) { wire[i] = arbitrary(); }
  assert(decode_catalog_sent_for_instruments_belonging_to_mutual_funds_message(&got, wire, 0) == 78);
  assert(encode_catalog_sent_for_instruments_belonging_to_mutual_funds_message(&got, again, 0) == 78);
  for (size_t i = 0; i < 78; i++) { assert(again[i] == wire[i]); }
}

/* ---- Weighted Average Price Message: 21 bytes -------------------------------- */

/* This message will have the weighted average price (WAP) per instrument and is sent for each transaction generated within the calculation period of the WAP (last 20 minutes of the trading session); when there are no more trades in this period, the message is sent with the Weighted Average Price in zeros. */
typedef struct {
  uint8_t instrument_number[4];       /* bytes 0 to 3 */
  uint8_t origin;                     /* byte 4 */
  uint8_t weighted_average_price[8];  /* bytes 5 to 12 */
  uint8_t volatility[8];              /* bytes 13 to 20 */
} WeightedAveragePriceMessage;

/* any Weighted Average Price Message at all: every byte one the checker chooses */
static void any_weighted_average_price_message(WeightedAveragePriceMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->instrument_number[i] = arbitrary(); }
  record->origin = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->weighted_average_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->volatility[i] = arbitrary(); }
}

/* Weighted Average Price Message to the wire: 21 bytes from at, returning where the next byte goes */
static size_t encode_weighted_average_price_message(const WeightedAveragePriceMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument_number[i]; }
  wire[at++] = record->origin;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->weighted_average_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->volatility[i]; }

  return at;
}

/* Weighted Average Price Message off the wire: 21 bytes from at, returning where the next byte lies */
static size_t decode_weighted_average_price_message(WeightedAveragePriceMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->instrument_number[i] = wire[at++]; }
  record->origin = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->weighted_average_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->volatility[i] = wire[at++]; }

  return at;
}

/* what was read of Weighted Average Price Message is what was written, byte for byte */
static void equal_weighted_average_price_message(const WeightedAveragePriceMessage *read, const WeightedAveragePriceMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->instrument_number[i] == written->instrument_number[i]); }
  assert(read->origin == written->origin);
  for (size_t i = 0; i < 8; i++) { assert(read->weighted_average_price[i] == written->weighted_average_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->volatility[i] == written->volatility[i]); }
}

/* Weighted Average Price Message: written and read back, then read and written back */
static void check_weighted_average_price_message(void) {
  WeightedAveragePriceMessage sent;
  WeightedAveragePriceMessage got;
  uint8_t wire[21];
  uint8_t again[21];

  any_weighted_average_price_message(&sent);
  assert(encode_weighted_average_price_message(&sent, wire, 0) == 21);
  assert(decode_weighted_average_price_message(&got, wire, 0) == 21);
  equal_weighted_average_price_message(&got, &sent);

  for (size_t i = 0; i < 21; i++) { wire[i] = arbitrary(); }
  assert(decode_weighted_average_price_message(&got, wire, 0) == 21);
  assert(encode_weighted_average_price_message(&got, again, 0) == 21);
  for (size_t i = 0; i < 21; i++) { assert(again[i] == wire[i]); }
}

/* ---- System Events Message: 31 bytes ----------------------------------------- */

/* The system events message is used to inform that an event has taken place, which needs to be disclosed to the public for its attention. */
typedef struct {
  uint8_t instrument_number[4];  /* bytes 0 to 3 */
  uint8_t origin;                /* byte 4 */
  uint8_t code_of_event;         /* byte 5 */
  uint8_t market;                /* byte 6 */
  uint8_t send_time[8];          /* bytes 7 to 14 */
  uint8_t end_time[8];           /* bytes 15 to 22 */
  uint8_t group[8];              /* bytes 23 to 30 */
} SystemEventsMessage;

/* any System Events Message at all: every byte one the checker chooses */
static void any_system_events_message(SystemEventsMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->instrument_number[i] = arbitrary(); }
  record->origin = arbitrary();
  record->code_of_event = arbitrary();
  record->market = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->send_time[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->end_time[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->group[i] = arbitrary(); }
}

/* System Events Message to the wire: 31 bytes from at, returning where the next byte goes */
static size_t encode_system_events_message(const SystemEventsMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument_number[i]; }
  wire[at++] = record->origin;
  wire[at++] = record->code_of_event;
  wire[at++] = record->market;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->send_time[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->end_time[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->group[i]; }

  return at;
}

/* System Events Message off the wire: 31 bytes from at, returning where the next byte lies */
static size_t decode_system_events_message(SystemEventsMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->instrument_number[i] = wire[at++]; }
  record->origin = wire[at++];
  record->code_of_event = wire[at++];
  record->market = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->send_time[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->end_time[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->group[i] = wire[at++]; }

  return at;
}

/* what was read of System Events Message is what was written, byte for byte */
static void equal_system_events_message(const SystemEventsMessage *read, const SystemEventsMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->instrument_number[i] == written->instrument_number[i]); }
  assert(read->origin == written->origin);
  assert(read->code_of_event == written->code_of_event);
  assert(read->market == written->market);
  for (size_t i = 0; i < 8; i++) { assert(read->send_time[i] == written->send_time[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->end_time[i] == written->end_time[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->group[i] == written->group[i]); }
}

/* System Events Message: written and read back, then read and written back */
static void check_system_events_message(void) {
  SystemEventsMessage sent;
  SystemEventsMessage got;
  uint8_t wire[31];
  uint8_t again[31];

  any_system_events_message(&sent);
  assert(encode_system_events_message(&sent, wire, 0) == 31);
  assert(decode_system_events_message(&got, wire, 0) == 31);
  equal_system_events_message(&got, &sent);

  for (size_t i = 0; i < 31; i++) { wire[i] = arbitrary(); }
  assert(decode_system_events_message(&got, wire, 0) == 31);
  assert(encode_system_events_message(&got, again, 0) == 31);
  for (size_t i = 0; i < 31; i++) { assert(again[i] == wire[i]); }
}

/* ---- Reference Price Message: 14 bytes --------------------------------------- */

/* This message is sent to define the reference price of an instrument. */
typedef struct {
  uint8_t instrument_number[4];  /* bytes 0 to 3 */
  uint8_t origin;                /* byte 4 */
  uint8_t price[8];              /* bytes 5 to 12 */
  uint8_t price_type;            /* byte 13 */
} ReferencePriceMessage;

/* any Reference Price Message at all: every byte one the checker chooses */
static void any_reference_price_message(ReferencePriceMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->instrument_number[i] = arbitrary(); }
  record->origin = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->price[i] = arbitrary(); }
  record->price_type = arbitrary();
}

/* Reference Price Message to the wire: 14 bytes from at, returning where the next byte goes */
static size_t encode_reference_price_message(const ReferencePriceMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument_number[i]; }
  wire[at++] = record->origin;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price[i]; }
  wire[at++] = record->price_type;

  return at;
}

/* Reference Price Message off the wire: 14 bytes from at, returning where the next byte lies */
static size_t decode_reference_price_message(ReferencePriceMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->instrument_number[i] = wire[at++]; }
  record->origin = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->price[i] = wire[at++]; }
  record->price_type = wire[at++];

  return at;
}

/* what was read of Reference Price Message is what was written, byte for byte */
static void equal_reference_price_message(const ReferencePriceMessage *read, const ReferencePriceMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->instrument_number[i] == written->instrument_number[i]); }
  assert(read->origin == written->origin);
  for (size_t i = 0; i < 8; i++) { assert(read->price[i] == written->price[i]); }
  assert(read->price_type == written->price_type);
}

/* Reference Price Message: written and read back, then read and written back */
static void check_reference_price_message(void) {
  ReferencePriceMessage sent;
  ReferencePriceMessage got;
  uint8_t wire[14];
  uint8_t again[14];

  any_reference_price_message(&sent);
  assert(encode_reference_price_message(&sent, wire, 0) == 14);
  assert(decode_reference_price_message(&got, wire, 0) == 14);
  equal_reference_price_message(&got, &sent);

  for (size_t i = 0; i < 14; i++) { wire[i] = arbitrary(); }
  assert(decode_reference_price_message(&got, wire, 0) == 14);
  assert(encode_reference_price_message(&got, again, 0) == 14);
  for (size_t i = 0; i < 14; i++) { assert(again[i] == wire[i]); }
}

/* ---- Changes In Status Message: 7 bytes -------------------------------------- */

/* This message is sent when there has been a change in the status of the instruments. */
typedef struct {
  uint8_t instrument_number[4];  /* bytes 0 to 3 */
  uint8_t origin;                /* byte 4 */
  uint8_t status;                /* byte 5 */
  uint8_t reason;                /* byte 6 */
} ChangesInStatusMessage;

/* any Changes In Status Message at all: every byte one the checker chooses */
static void any_changes_in_status_message(ChangesInStatusMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->instrument_number[i] = arbitrary(); }
  record->origin = arbitrary();
  record->status = arbitrary();
  record->reason = arbitrary();
}

/* Changes In Status Message to the wire: 7 bytes from at, returning where the next byte goes */
static size_t encode_changes_in_status_message(const ChangesInStatusMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument_number[i]; }
  wire[at++] = record->origin;
  wire[at++] = record->status;
  wire[at++] = record->reason;

  return at;
}

/* Changes In Status Message off the wire: 7 bytes from at, returning where the next byte lies */
static size_t decode_changes_in_status_message(ChangesInStatusMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->instrument_number[i] = wire[at++]; }
  record->origin = wire[at++];
  record->status = wire[at++];
  record->reason = wire[at++];

  return at;
}

/* what was read of Changes In Status Message is what was written, byte for byte */
static void equal_changes_in_status_message(const ChangesInStatusMessage *read, const ChangesInStatusMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->instrument_number[i] == written->instrument_number[i]); }
  assert(read->origin == written->origin);
  assert(read->status == written->status);
  assert(read->reason == written->reason);
}

/* Changes In Status Message: written and read back, then read and written back */
static void check_changes_in_status_message(void) {
  ChangesInStatusMessage sent;
  ChangesInStatusMessage got;
  uint8_t wire[7];
  uint8_t again[7];

  any_changes_in_status_message(&sent);
  assert(encode_changes_in_status_message(&sent, wire, 0) == 7);
  assert(decode_changes_in_status_message(&got, wire, 0) == 7);
  equal_changes_in_status_message(&got, &sent);

  for (size_t i = 0; i < 7; i++) { wire[i] = arbitrary(); }
  assert(decode_changes_in_status_message(&got, wire, 0) == 7);
  assert(encode_changes_in_status_message(&got, again, 0) == 7);
  for (size_t i = 0; i < 7; i++) { assert(again[i] == wire[i]); }
}

/* ---- Catalog For Instruments Belonging To The Capital Warrants Market Message: 66 bytes ---- */

/* Catalogue for instruments pertaining to the Equities Warrants market. */
typedef struct {
  uint8_t number_of_the_instrument[4];  /* bytes 0 to 3 */
  uint8_t origin;                       /* byte 4 */
  uint8_t type_of_value[2];             /* bytes 5 to 6 */
  uint8_t issuing_company[7];           /* bytes 7 to 13 */
  uint8_t series[6];                    /* bytes 14 to 19 */
  uint8_t type_of_warrant;              /* byte 20 */
  uint8_t date_of_maturity[8];          /* bytes 21 to 28 */
  uint8_t price_of_exercise[8];         /* bytes 29 to 36 */
  uint8_t reference_price[8];           /* bytes 37 to 44 */
  uint8_t reference_date[8];            /* bytes 45 to 52 */
  uint8_t reference;                    /* byte 53 */
  uint8_t isin[12];                     /* bytes 54 to 65 */
} CatalogForInstrumentsBelongingToTheCapitalWarrantsMarketMessage;

/* any Catalog For Instruments Belonging To The Capital Warrants Market Message at all: every byte one the checker chooses */
static void any_catalog_for_instruments_belonging_to_the_capital_warrants_market_message(CatalogForInstrumentsBelongingToTheCapitalWarrantsMarketMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->number_of_the_instrument[i] = arbitrary(); }
  record->origin = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->type_of_value[i] = arbitrary(); }
  for (size_t i = 0; i < 7; i++) { record->issuing_company[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->series[i] = arbitrary(); }
  record->type_of_warrant = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->date_of_maturity[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->price_of_exercise[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->reference_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->reference_date[i] = arbitrary(); }
  record->reference = arbitrary();
  for (size_t i = 0; i < 12; i++) { record->isin[i] = arbitrary(); }
}

/* Catalog For Instruments Belonging To The Capital Warrants Market Message to the wire: 66 bytes from at, returning where the next byte goes */
static size_t encode_catalog_for_instruments_belonging_to_the_capital_warrants_market_message(const CatalogForInstrumentsBelongingToTheCapitalWarrantsMarketMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->number_of_the_instrument[i]; }
  wire[at++] = record->origin;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->type_of_value[i]; }
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->issuing_company[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->series[i]; }
  wire[at++] = record->type_of_warrant;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->date_of_maturity[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price_of_exercise[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->reference_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->reference_date[i]; }
  wire[at++] = record->reference;
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->isin[i]; }

  return at;
}

/* Catalog For Instruments Belonging To The Capital Warrants Market Message off the wire: 66 bytes from at, returning where the next byte lies */
static size_t decode_catalog_for_instruments_belonging_to_the_capital_warrants_market_message(CatalogForInstrumentsBelongingToTheCapitalWarrantsMarketMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->number_of_the_instrument[i] = wire[at++]; }
  record->origin = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->type_of_value[i] = wire[at++]; }
  for (size_t i = 0; i < 7; i++) { record->issuing_company[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->series[i] = wire[at++]; }
  record->type_of_warrant = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->date_of_maturity[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->price_of_exercise[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->reference_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->reference_date[i] = wire[at++]; }
  record->reference = wire[at++];
  for (size_t i = 0; i < 12; i++) { record->isin[i] = wire[at++]; }

  return at;
}

/* what was read of Catalog For Instruments Belonging To The Capital Warrants Market Message is what was written, byte for byte */
static void equal_catalog_for_instruments_belonging_to_the_capital_warrants_market_message(const CatalogForInstrumentsBelongingToTheCapitalWarrantsMarketMessage *read, const CatalogForInstrumentsBelongingToTheCapitalWarrantsMarketMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->number_of_the_instrument[i] == written->number_of_the_instrument[i]); }
  assert(read->origin == written->origin);
  for (size_t i = 0; i < 2; i++) { assert(read->type_of_value[i] == written->type_of_value[i]); }
  for (size_t i = 0; i < 7; i++) { assert(read->issuing_company[i] == written->issuing_company[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->series[i] == written->series[i]); }
  assert(read->type_of_warrant == written->type_of_warrant);
  for (size_t i = 0; i < 8; i++) { assert(read->date_of_maturity[i] == written->date_of_maturity[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->price_of_exercise[i] == written->price_of_exercise[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->reference_price[i] == written->reference_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->reference_date[i] == written->reference_date[i]); }
  assert(read->reference == written->reference);
  for (size_t i = 0; i < 12; i++) { assert(read->isin[i] == written->isin[i]); }
}

/* Catalog For Instruments Belonging To The Capital Warrants Market Message: written and read back, then read and written back */
static void check_catalog_for_instruments_belonging_to_the_capital_warrants_market_message(void) {
  CatalogForInstrumentsBelongingToTheCapitalWarrantsMarketMessage sent;
  CatalogForInstrumentsBelongingToTheCapitalWarrantsMarketMessage got;
  uint8_t wire[66];
  uint8_t again[66];

  any_catalog_for_instruments_belonging_to_the_capital_warrants_market_message(&sent);
  assert(encode_catalog_for_instruments_belonging_to_the_capital_warrants_market_message(&sent, wire, 0) == 66);
  assert(decode_catalog_for_instruments_belonging_to_the_capital_warrants_market_message(&got, wire, 0) == 66);
  equal_catalog_for_instruments_belonging_to_the_capital_warrants_market_message(&got, &sent);

  for (size_t i = 0; i < 66; i++) { wire[i] = arbitrary(); }
  assert(decode_catalog_for_instruments_belonging_to_the_capital_warrants_market_message(&got, wire, 0) == 66);
  assert(encode_catalog_for_instruments_belonging_to_the_capital_warrants_market_message(&got, again, 0) == 66);
  for (size_t i = 0; i < 66; i++) { assert(again[i] == wire[i]); }
}

/* ---- Catalog Sent For Instruments Belonging To Capital Tracs Message: 82 bytes ---- */

/* Catalogue sent for instruments pertaining to the equities TRACS. */
typedef struct {
  uint8_t number_of_the_trac[4];          /* bytes 0 to 3 */
  uint8_t origin;                         /* byte 4 */
  uint8_t name_of_the_trac[8];            /* bytes 5 to 12 */
  uint8_t underlying_issuing_company[7];  /* bytes 13 to 19 */
  uint8_t underlying_series[6];           /* bytes 20 to 25 */
  uint8_t securities[8];                  /* bytes 26 to 33 */
  uint8_t excluded_securities[8];         /* bytes 34 to 41 */
  uint8_t price[8];                       /* bytes 42 to 49 */
  uint8_t component_in_cash[8];           /* bytes 50 to 57 */
  uint8_t excluded_value[8];              /* bytes 58 to 65 */
  uint8_t number_of_certificates[8];      /* bytes 66 to 73 */
  uint8_t theoretical_price[8];           /* bytes 74 to 81 */
} CatalogSentForInstrumentsBelongingToCapitalTracsMessage;

/* any Catalog Sent For Instruments Belonging To Capital Tracs Message at all: every byte one the checker chooses */
static void any_catalog_sent_for_instruments_belonging_to_capital_tracs_message(CatalogSentForInstrumentsBelongingToCapitalTracsMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->number_of_the_trac[i] = arbitrary(); }
  record->origin = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->name_of_the_trac[i] = arbitrary(); }
  for (size_t i = 0; i < 7; i++) { record->underlying_issuing_company[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->underlying_series[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->securities[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->excluded_securities[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->component_in_cash[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->excluded_value[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->number_of_certificates[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->theoretical_price[i] = arbitrary(); }
}

/* Catalog Sent For Instruments Belonging To Capital Tracs Message to the wire: 82 bytes from at, returning where the next byte goes */
static size_t encode_catalog_sent_for_instruments_belonging_to_capital_tracs_message(const CatalogSentForInstrumentsBelongingToCapitalTracsMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->number_of_the_trac[i]; }
  wire[at++] = record->origin;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->name_of_the_trac[i]; }
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->underlying_issuing_company[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->underlying_series[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->securities[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->excluded_securities[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->component_in_cash[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->excluded_value[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->number_of_certificates[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->theoretical_price[i]; }

  return at;
}

/* Catalog Sent For Instruments Belonging To Capital Tracs Message off the wire: 82 bytes from at, returning where the next byte lies */
static size_t decode_catalog_sent_for_instruments_belonging_to_capital_tracs_message(CatalogSentForInstrumentsBelongingToCapitalTracsMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->number_of_the_trac[i] = wire[at++]; }
  record->origin = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->name_of_the_trac[i] = wire[at++]; }
  for (size_t i = 0; i < 7; i++) { record->underlying_issuing_company[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->underlying_series[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->securities[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->excluded_securities[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->component_in_cash[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->excluded_value[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->number_of_certificates[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->theoretical_price[i] = wire[at++]; }

  return at;
}

/* what was read of Catalog Sent For Instruments Belonging To Capital Tracs Message is what was written, byte for byte */
static void equal_catalog_sent_for_instruments_belonging_to_capital_tracs_message(const CatalogSentForInstrumentsBelongingToCapitalTracsMessage *read, const CatalogSentForInstrumentsBelongingToCapitalTracsMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->number_of_the_trac[i] == written->number_of_the_trac[i]); }
  assert(read->origin == written->origin);
  for (size_t i = 0; i < 8; i++) { assert(read->name_of_the_trac[i] == written->name_of_the_trac[i]); }
  for (size_t i = 0; i < 7; i++) { assert(read->underlying_issuing_company[i] == written->underlying_issuing_company[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->underlying_series[i] == written->underlying_series[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->securities[i] == written->securities[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->excluded_securities[i] == written->excluded_securities[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->price[i] == written->price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->component_in_cash[i] == written->component_in_cash[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->excluded_value[i] == written->excluded_value[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->number_of_certificates[i] == written->number_of_certificates[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->theoretical_price[i] == written->theoretical_price[i]); }
}

/* Catalog Sent For Instruments Belonging To Capital Tracs Message: written and read back, then read and written back */
static void check_catalog_sent_for_instruments_belonging_to_capital_tracs_message(void) {
  CatalogSentForInstrumentsBelongingToCapitalTracsMessage sent;
  CatalogSentForInstrumentsBelongingToCapitalTracsMessage got;
  uint8_t wire[82];
  uint8_t again[82];

  any_catalog_sent_for_instruments_belonging_to_capital_tracs_message(&sent);
  assert(encode_catalog_sent_for_instruments_belonging_to_capital_tracs_message(&sent, wire, 0) == 82);
  assert(decode_catalog_sent_for_instruments_belonging_to_capital_tracs_message(&got, wire, 0) == 82);
  equal_catalog_sent_for_instruments_belonging_to_capital_tracs_message(&got, &sent);

  for (size_t i = 0; i < 82; i++) { wire[i] = arbitrary(); }
  assert(decode_catalog_sent_for_instruments_belonging_to_capital_tracs_message(&got, wire, 0) == 82);
  assert(encode_catalog_sent_for_instruments_belonging_to_capital_tracs_message(&got, again, 0) == 82);
  for (size_t i = 0; i < 82; i++) { assert(again[i] == wire[i]); }
}

/* ---- Consolidated Inav Message: 13 bytes ------------------------------------- */

/* Disclosure of the TRACS during the trading hours of the ongoing market. */
typedef struct {
  uint8_t number_of_the_trac[4];         /* bytes 0 to 3 */
  uint8_t origin;                        /* byte 4 */
  uint8_t current_theoretical_price[8];  /* bytes 5 to 12 */
} ConsolidatedInavMessage;

/* any Consolidated Inav Message at all: every byte one the checker chooses */
static void any_consolidated_inav_message(ConsolidatedInavMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->number_of_the_trac[i] = arbitrary(); }
  record->origin = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->current_theoretical_price[i] = arbitrary(); }
}

/* Consolidated Inav Message to the wire: 13 bytes from at, returning where the next byte goes */
static size_t encode_consolidated_inav_message(const ConsolidatedInavMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->number_of_the_trac[i]; }
  wire[at++] = record->origin;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->current_theoretical_price[i]; }

  return at;
}

/* Consolidated Inav Message off the wire: 13 bytes from at, returning where the next byte lies */
static size_t decode_consolidated_inav_message(ConsolidatedInavMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->number_of_the_trac[i] = wire[at++]; }
  record->origin = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->current_theoretical_price[i] = wire[at++]; }

  return at;
}

/* what was read of Consolidated Inav Message is what was written, byte for byte */
static void equal_consolidated_inav_message(const ConsolidatedInavMessage *read, const ConsolidatedInavMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->number_of_the_trac[i] == written->number_of_the_trac[i]); }
  assert(read->origin == written->origin);
  for (size_t i = 0; i < 8; i++) { assert(read->current_theoretical_price[i] == written->current_theoretical_price[i]); }
}

/* Consolidated Inav Message: written and read back, then read and written back */
static void check_consolidated_inav_message(void) {
  ConsolidatedInavMessage sent;
  ConsolidatedInavMessage got;
  uint8_t wire[13];
  uint8_t again[13];

  any_consolidated_inav_message(&sent);
  assert(encode_consolidated_inav_message(&sent, wire, 0) == 13);
  assert(decode_consolidated_inav_message(&got, wire, 0) == 13);
  equal_consolidated_inav_message(&got, &sent);

  for (size_t i = 0; i < 13; i++) { wire[i] = arbitrary(); }
  assert(decode_consolidated_inav_message(&got, wire, 0) == 13);
  assert(encode_consolidated_inav_message(&got, again, 0) == 13);
  for (size_t i = 0; i < 13; i++) { assert(again[i] == wire[i]); }
}

/* ---- Catalog For Instruments Belonging To The Local And Global Stock Market Message: 73 bytes ---- */

/* Catalog of instruments from the local and global stock markets. */
typedef struct {
  uint8_t mse_instrument_number[4];       /* bytes 0 to 3 */
  uint8_t value_of_type[2];               /* bytes 4 to 5 */
  uint8_t issuing_company[7];             /* bytes 6 to 12 */
  uint8_t series[6];                      /* bytes 13 to 18 */
  uint8_t last_price[8];                  /* bytes 19 to 26 */
  uint8_t ppp_weighted_average_price[8];  /* bytes 27 to 34 */
  uint8_t reference_date[8];              /* bytes 35 to 42 */
  uint8_t reference;                      /* byte 43 */
  uint8_t coupon_in_effect[2];            /* bytes 44 to 45 */
  uint8_t marketability;                  /* byte 46 */
  uint8_t numerical_marketability[4];     /* bytes 47 to 50 */
  uint8_t isin[12];                       /* bytes 51 to 62 */
  uint8_t market;                         /* byte 63 */
  uint8_t registered_values[8];           /* bytes 64 to 71 */
  uint8_t exchange;                       /* byte 72 */
} CatalogForInstrumentsBelongingToTheLocalAndGlobalStockMar_gc6yau;

/* any Catalog For Instruments Belonging To The Local And Global Stock Market Message at all: every byte one the checker chooses */
static void any_catalog_for_instruments_belonging_to_the_local_and_global_stock_mar_gc6yau(CatalogForInstrumentsBelongingToTheLocalAndGlobalStockMar_gc6yau *record) {
  for (size_t i = 0; i < 4; i++) { record->mse_instrument_number[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->value_of_type[i] = arbitrary(); }
  for (size_t i = 0; i < 7; i++) { record->issuing_company[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->series[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->last_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->ppp_weighted_average_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->reference_date[i] = arbitrary(); }
  record->reference = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->coupon_in_effect[i] = arbitrary(); }
  record->marketability = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->numerical_marketability[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->isin[i] = arbitrary(); }
  record->market = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->registered_values[i] = arbitrary(); }
  record->exchange = arbitrary();
}

/* Catalog For Instruments Belonging To The Local And Global Stock Market Message to the wire: 73 bytes from at, returning where the next byte goes */
static size_t encode_catalog_for_instruments_belonging_to_the_local_and_global_stock_mar_gc6yau(const CatalogForInstrumentsBelongingToTheLocalAndGlobalStockMar_gc6yau *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->mse_instrument_number[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->value_of_type[i]; }
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->issuing_company[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->series[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->last_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->ppp_weighted_average_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->reference_date[i]; }
  wire[at++] = record->reference;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->coupon_in_effect[i]; }
  wire[at++] = record->marketability;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->numerical_marketability[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->isin[i]; }
  wire[at++] = record->market;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->registered_values[i]; }
  wire[at++] = record->exchange;

  return at;
}

/* Catalog For Instruments Belonging To The Local And Global Stock Market Message off the wire: 73 bytes from at, returning where the next byte lies */
static size_t decode_catalog_for_instruments_belonging_to_the_local_and_global_stock_mar_gc6yau(CatalogForInstrumentsBelongingToTheLocalAndGlobalStockMar_gc6yau *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->mse_instrument_number[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->value_of_type[i] = wire[at++]; }
  for (size_t i = 0; i < 7; i++) { record->issuing_company[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->series[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->last_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->ppp_weighted_average_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->reference_date[i] = wire[at++]; }
  record->reference = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->coupon_in_effect[i] = wire[at++]; }
  record->marketability = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->numerical_marketability[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->isin[i] = wire[at++]; }
  record->market = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->registered_values[i] = wire[at++]; }
  record->exchange = wire[at++];

  return at;
}

/* what was read of Catalog For Instruments Belonging To The Local And Global Stock Market Message is what was written, byte for byte */
static void equal_catalog_for_instruments_belonging_to_the_local_and_global_stock_mar_gc6yau(const CatalogForInstrumentsBelongingToTheLocalAndGlobalStockMar_gc6yau *read, const CatalogForInstrumentsBelongingToTheLocalAndGlobalStockMar_gc6yau *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->mse_instrument_number[i] == written->mse_instrument_number[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->value_of_type[i] == written->value_of_type[i]); }
  for (size_t i = 0; i < 7; i++) { assert(read->issuing_company[i] == written->issuing_company[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->series[i] == written->series[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->last_price[i] == written->last_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->ppp_weighted_average_price[i] == written->ppp_weighted_average_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->reference_date[i] == written->reference_date[i]); }
  assert(read->reference == written->reference);
  for (size_t i = 0; i < 2; i++) { assert(read->coupon_in_effect[i] == written->coupon_in_effect[i]); }
  assert(read->marketability == written->marketability);
  for (size_t i = 0; i < 4; i++) { assert(read->numerical_marketability[i] == written->numerical_marketability[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->isin[i] == written->isin[i]); }
  assert(read->market == written->market);
  for (size_t i = 0; i < 8; i++) { assert(read->registered_values[i] == written->registered_values[i]); }
  assert(read->exchange == written->exchange);
}

/* Catalog For Instruments Belonging To The Local And Global Stock Market Message: written and read back, then read and written back */
static void check_catalog_for_instruments_belonging_to_the_local_and_global_stock_mar_gc6yau(void) {
  CatalogForInstrumentsBelongingToTheLocalAndGlobalStockMar_gc6yau sent;
  CatalogForInstrumentsBelongingToTheLocalAndGlobalStockMar_gc6yau got;
  uint8_t wire[73];
  uint8_t again[73];

  any_catalog_for_instruments_belonging_to_the_local_and_global_stock_mar_gc6yau(&sent);
  assert(encode_catalog_for_instruments_belonging_to_the_local_and_global_stock_mar_gc6yau(&sent, wire, 0) == 73);
  assert(decode_catalog_for_instruments_belonging_to_the_local_and_global_stock_mar_gc6yau(&got, wire, 0) == 73);
  equal_catalog_for_instruments_belonging_to_the_local_and_global_stock_mar_gc6yau(&got, &sent);

  for (size_t i = 0; i < 73; i++) { wire[i] = arbitrary(); }
  assert(decode_catalog_for_instruments_belonging_to_the_local_and_global_stock_mar_gc6yau(&got, wire, 0) == 73);
  assert(encode_catalog_for_instruments_belonging_to_the_local_and_global_stock_mar_gc6yau(&got, again, 0) == 73);
  for (size_t i = 0; i < 73; i++) { assert(again[i] == wire[i]); }
}

/* ---- Probable Price Of Allocation Message: 21 bytes -------------------------- */

/* The message is sent during any type of bidding (Opening, Ongoing, Volatility and Intraday) and only in the instruments where there already is a virtual term matching or pre-allotment. */
typedef struct {
  uint8_t instrument_number[4];             /* bytes 0 to 3 */
  uint8_t origin;                           /* byte 4 */
  uint8_t probable_price_of_allocation[8];  /* bytes 5 to 12 */
  uint8_t volume[8];                        /* bytes 13 to 20 */
} ProbablePriceOfAllocationMessage;

/* any Probable Price Of Allocation Message at all: every byte one the checker chooses */
static void any_probable_price_of_allocation_message(ProbablePriceOfAllocationMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->instrument_number[i] = arbitrary(); }
  record->origin = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->probable_price_of_allocation[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->volume[i] = arbitrary(); }
}

/* Probable Price Of Allocation Message to the wire: 21 bytes from at, returning where the next byte goes */
static size_t encode_probable_price_of_allocation_message(const ProbablePriceOfAllocationMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument_number[i]; }
  wire[at++] = record->origin;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->probable_price_of_allocation[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->volume[i]; }

  return at;
}

/* Probable Price Of Allocation Message off the wire: 21 bytes from at, returning where the next byte lies */
static size_t decode_probable_price_of_allocation_message(ProbablePriceOfAllocationMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->instrument_number[i] = wire[at++]; }
  record->origin = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->probable_price_of_allocation[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->volume[i] = wire[at++]; }

  return at;
}

/* what was read of Probable Price Of Allocation Message is what was written, byte for byte */
static void equal_probable_price_of_allocation_message(const ProbablePriceOfAllocationMessage *read, const ProbablePriceOfAllocationMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->instrument_number[i] == written->instrument_number[i]); }
  assert(read->origin == written->origin);
  for (size_t i = 0; i < 8; i++) { assert(read->probable_price_of_allocation[i] == written->probable_price_of_allocation[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->volume[i] == written->volume[i]); }
}

/* Probable Price Of Allocation Message: written and read back, then read and written back */
static void check_probable_price_of_allocation_message(void) {
  ProbablePriceOfAllocationMessage sent;
  ProbablePriceOfAllocationMessage got;
  uint8_t wire[21];
  uint8_t again[21];

  any_probable_price_of_allocation_message(&sent);
  assert(encode_probable_price_of_allocation_message(&sent, wire, 0) == 21);
  assert(decode_probable_price_of_allocation_message(&got, wire, 0) == 21);
  equal_probable_price_of_allocation_message(&got, &sent);

  for (size_t i = 0; i < 21; i++) { wire[i] = arbitrary(); }
  assert(decode_probable_price_of_allocation_message(&got, wire, 0) == 21);
  assert(encode_probable_price_of_allocation_message(&got, again, 0) == 21);
  for (size_t i = 0; i < 21; i++) { assert(again[i] == wire[i]); }
}

/* ---- Relation Between Bmvbiva Instruments Message: 9 bytes ------------------- */

/* Relation between identifiers of instruments between BIVA and BMV. */
typedef struct {
  uint8_t number_of_the_bmv_instrument[4];  /* bytes 0 to 3 */
  uint8_t biva_instrument[4];               /* bytes 4 to 7 */
  uint8_t type_of_trading;                  /* byte 8 */
} RelationBetweenBmvbivaInstrumentsMessage;

/* any Relation Between Bmvbiva Instruments Message at all: every byte one the checker chooses */
static void any_relation_between_bmvbiva_instruments_message(RelationBetweenBmvbivaInstrumentsMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->number_of_the_bmv_instrument[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->biva_instrument[i] = arbitrary(); }
  record->type_of_trading = arbitrary();
}

/* Relation Between Bmvbiva Instruments Message to the wire: 9 bytes from at, returning where the next byte goes */
static size_t encode_relation_between_bmvbiva_instruments_message(const RelationBetweenBmvbivaInstrumentsMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->number_of_the_bmv_instrument[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->biva_instrument[i]; }
  wire[at++] = record->type_of_trading;

  return at;
}

/* Relation Between Bmvbiva Instruments Message off the wire: 9 bytes from at, returning where the next byte lies */
static size_t decode_relation_between_bmvbiva_instruments_message(RelationBetweenBmvbivaInstrumentsMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->number_of_the_bmv_instrument[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->biva_instrument[i] = wire[at++]; }
  record->type_of_trading = wire[at++];

  return at;
}

/* what was read of Relation Between Bmvbiva Instruments Message is what was written, byte for byte */
static void equal_relation_between_bmvbiva_instruments_message(const RelationBetweenBmvbivaInstrumentsMessage *read, const RelationBetweenBmvbivaInstrumentsMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->number_of_the_bmv_instrument[i] == written->number_of_the_bmv_instrument[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->biva_instrument[i] == written->biva_instrument[i]); }
  assert(read->type_of_trading == written->type_of_trading);
}

/* Relation Between Bmvbiva Instruments Message: written and read back, then read and written back */
static void check_relation_between_bmvbiva_instruments_message(void) {
  RelationBetweenBmvbivaInstrumentsMessage sent;
  RelationBetweenBmvbivaInstrumentsMessage got;
  uint8_t wire[9];
  uint8_t again[9];

  any_relation_between_bmvbiva_instruments_message(&sent);
  assert(encode_relation_between_bmvbiva_instruments_message(&sent, wire, 0) == 9);
  assert(decode_relation_between_bmvbiva_instruments_message(&got, wire, 0) == 9);
  equal_relation_between_bmvbiva_instruments_message(&got, &sent);

  for (size_t i = 0; i < 9; i++) { wire[i] = arbitrary(); }
  assert(decode_relation_between_bmvbiva_instruments_message(&got, wire, 0) == 9);
  assert(encode_relation_between_bmvbiva_instruments_message(&got, again, 0) == 9);
  for (size_t i = 0; i < 9; i++) { assert(again[i] == wire[i]); }
}

/* ---- Equities Market Trades Message: 61 bytes -------------------------------- */

/* Informs about any transaction which was accepted at the BMV or BIVA. */
typedef struct {
  uint8_t instrument_number[4];                /* bytes 0 to 3 */
  uint8_t origin;                              /* byte 4 */
  uint8_t time_of_the_trade[8];                /* bytes 5 to 12 */
  uint8_t volume[8];                           /* bytes 13 to 20 */
  uint8_t price[8];                            /* bytes 21 to 28 */
  uint8_t type_of_agreement;                   /* byte 29 */
  uint8_t consecutive_number_of_the_trade[8];  /* bytes 30 to 37 */
  uint8_t sets_price;                          /* byte 38 */
  uint8_t type_of_trading;                     /* byte 39 */
  uint8_t amount[8];                           /* bytes 40 to 47 */
  uint8_t purchases[5];                        /* bytes 48 to 52 */
  uint8_t sells[5];                            /* bytes 53 to 57 */
  uint8_t settlement;                          /* byte 58 */
  uint8_t auction_indicator;                   /* byte 59 */
  uint8_t indicator;                           /* byte 60 */
} EquitiesMarketTradesMessage;

/* any Equities Market Trades Message at all: every byte one the checker chooses */
static void any_equities_market_trades_message(EquitiesMarketTradesMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->instrument_number[i] = arbitrary(); }
  record->origin = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->time_of_the_trade[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->volume[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->price[i] = arbitrary(); }
  record->type_of_agreement = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->consecutive_number_of_the_trade[i] = arbitrary(); }
  record->sets_price = arbitrary();
  record->type_of_trading = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->amount[i] = arbitrary(); }
  for (size_t i = 0; i < 5; i++) { record->purchases[i] = arbitrary(); }
  for (size_t i = 0; i < 5; i++) { record->sells[i] = arbitrary(); }
  record->settlement = arbitrary();
  record->auction_indicator = arbitrary();
  record->indicator = arbitrary();
}

/* Equities Market Trades Message to the wire: 61 bytes from at, returning where the next byte goes */
static size_t encode_equities_market_trades_message(const EquitiesMarketTradesMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument_number[i]; }
  wire[at++] = record->origin;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->time_of_the_trade[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->volume[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price[i]; }
  wire[at++] = record->type_of_agreement;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->consecutive_number_of_the_trade[i]; }
  wire[at++] = record->sets_price;
  wire[at++] = record->type_of_trading;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->amount[i]; }
  for (size_t i = 0; i < 5; i++) { wire[at++] = record->purchases[i]; }
  for (size_t i = 0; i < 5; i++) { wire[at++] = record->sells[i]; }
  wire[at++] = record->settlement;
  wire[at++] = record->auction_indicator;
  wire[at++] = record->indicator;

  return at;
}

/* Equities Market Trades Message off the wire: 61 bytes from at, returning where the next byte lies */
static size_t decode_equities_market_trades_message(EquitiesMarketTradesMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->instrument_number[i] = wire[at++]; }
  record->origin = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->time_of_the_trade[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->volume[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->price[i] = wire[at++]; }
  record->type_of_agreement = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->consecutive_number_of_the_trade[i] = wire[at++]; }
  record->sets_price = wire[at++];
  record->type_of_trading = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->amount[i] = wire[at++]; }
  for (size_t i = 0; i < 5; i++) { record->purchases[i] = wire[at++]; }
  for (size_t i = 0; i < 5; i++) { record->sells[i] = wire[at++]; }
  record->settlement = wire[at++];
  record->auction_indicator = wire[at++];
  record->indicator = wire[at++];

  return at;
}

/* what was read of Equities Market Trades Message is what was written, byte for byte */
static void equal_equities_market_trades_message(const EquitiesMarketTradesMessage *read, const EquitiesMarketTradesMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->instrument_number[i] == written->instrument_number[i]); }
  assert(read->origin == written->origin);
  for (size_t i = 0; i < 8; i++) { assert(read->time_of_the_trade[i] == written->time_of_the_trade[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->volume[i] == written->volume[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->price[i] == written->price[i]); }
  assert(read->type_of_agreement == written->type_of_agreement);
  for (size_t i = 0; i < 8; i++) { assert(read->consecutive_number_of_the_trade[i] == written->consecutive_number_of_the_trade[i]); }
  assert(read->sets_price == written->sets_price);
  assert(read->type_of_trading == written->type_of_trading);
  for (size_t i = 0; i < 8; i++) { assert(read->amount[i] == written->amount[i]); }
  for (size_t i = 0; i < 5; i++) { assert(read->purchases[i] == written->purchases[i]); }
  for (size_t i = 0; i < 5; i++) { assert(read->sells[i] == written->sells[i]); }
  assert(read->settlement == written->settlement);
  assert(read->auction_indicator == written->auction_indicator);
  assert(read->indicator == written->indicator);
}

/* Equities Market Trades Message: written and read back, then read and written back */
static void check_equities_market_trades_message(void) {
  EquitiesMarketTradesMessage sent;
  EquitiesMarketTradesMessage got;
  uint8_t wire[61];
  uint8_t again[61];

  any_equities_market_trades_message(&sent);
  assert(encode_equities_market_trades_message(&sent, wire, 0) == 61);
  assert(decode_equities_market_trades_message(&got, wire, 0) == 61);
  equal_equities_market_trades_message(&got, &sent);

  for (size_t i = 0; i < 61; i++) { wire[i] = arbitrary(); }
  assert(decode_equities_market_trades_message(&got, wire, 0) == 61);
  assert(encode_equities_market_trades_message(&got, again, 0) == 61);
  for (size_t i = 0; i < 61; i++) { assert(again[i] == wire[i]); }
}

/* ---- Consolidated Trade Cancellation Message: 13 bytes ----------------------- */

/* This message in sent when a transaction is cancelled from BMV or BIVA system. */
typedef struct {
  uint8_t instrument_number[4];                /* bytes 0 to 3 */
  uint8_t origin;                              /* byte 4 */
  uint8_t consecutive_number_of_the_trade[8];  /* bytes 5 to 12 */
} ConsolidatedTradeCancellationMessage;

/* any Consolidated Trade Cancellation Message at all: every byte one the checker chooses */
static void any_consolidated_trade_cancellation_message(ConsolidatedTradeCancellationMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->instrument_number[i] = arbitrary(); }
  record->origin = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->consecutive_number_of_the_trade[i] = arbitrary(); }
}

/* Consolidated Trade Cancellation Message to the wire: 13 bytes from at, returning where the next byte goes */
static size_t encode_consolidated_trade_cancellation_message(const ConsolidatedTradeCancellationMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument_number[i]; }
  wire[at++] = record->origin;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->consecutive_number_of_the_trade[i]; }

  return at;
}

/* Consolidated Trade Cancellation Message off the wire: 13 bytes from at, returning where the next byte lies */
static size_t decode_consolidated_trade_cancellation_message(ConsolidatedTradeCancellationMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->instrument_number[i] = wire[at++]; }
  record->origin = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->consecutive_number_of_the_trade[i] = wire[at++]; }

  return at;
}

/* what was read of Consolidated Trade Cancellation Message is what was written, byte for byte */
static void equal_consolidated_trade_cancellation_message(const ConsolidatedTradeCancellationMessage *read, const ConsolidatedTradeCancellationMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->instrument_number[i] == written->instrument_number[i]); }
  assert(read->origin == written->origin);
  for (size_t i = 0; i < 8; i++) { assert(read->consecutive_number_of_the_trade[i] == written->consecutive_number_of_the_trade[i]); }
}

/* Consolidated Trade Cancellation Message: written and read back, then read and written back */
static void check_consolidated_trade_cancellation_message(void) {
  ConsolidatedTradeCancellationMessage sent;
  ConsolidatedTradeCancellationMessage got;
  uint8_t wire[13];
  uint8_t again[13];

  any_consolidated_trade_cancellation_message(&sent);
  assert(encode_consolidated_trade_cancellation_message(&sent, wire, 0) == 13);
  assert(decode_consolidated_trade_cancellation_message(&got, wire, 0) == 13);
  equal_consolidated_trade_cancellation_message(&got, &sent);

  for (size_t i = 0; i < 13; i++) { wire[i] = arbitrary(); }
  assert(decode_consolidated_trade_cancellation_message(&got, wire, 0) == 13);
  assert(encode_consolidated_trade_cancellation_message(&got, again, 0) == 13);
  for (size_t i = 0; i < 13; i++) { assert(again[i] == wire[i]); }
}

/* ---- What esbmc checks ------------------------------------------------------- */

/* every record of the protocol, each on its own buffers */
static void checks(void) {
  check_i_n_t_r_a_multicast_header();
  check_message_header();
  check_mutual_funds_trades_message();
  check_opening_of_continuous_auctions_message();
  check_existence_of_bids_at_mid_price_message();
  check_catalogue_of_debt_and_metals_instruments_message();
  check_catalog_sent_for_instruments_belonging_to_mutual_funds_message();
  check_weighted_average_price_message();
  check_system_events_message();
  check_reference_price_message();
  check_changes_in_status_message();
  check_catalog_for_instruments_belonging_to_the_capital_warrants_market_message();
  check_catalog_sent_for_instruments_belonging_to_capital_tracs_message();
  check_consolidated_inav_message();
  check_catalog_for_instruments_belonging_to_the_local_and_global_stock_mar_gc6yau();
  check_probable_price_of_allocation_message();
  check_relation_between_bmvbiva_instruments_message();
  check_equities_market_trades_message();
  check_consolidated_trade_cancellation_message();
}

int main(void) {
#ifdef CONCRETE
  for (pattern = 0; pattern < 4; pattern++) { checks(); }
#else
  checks();
#endif

  return 0;
}
