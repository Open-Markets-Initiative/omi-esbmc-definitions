// bmv/bmvmarketdata/product40/BmvMarketData_Product40_v1_1.c
/*
 * Bolsa Mexicana de Valores Bmv Market Data Product 40
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

/* ---- Message Header: 4 bytes ------------------------------------------------- */

/* Message length and message type */
typedef struct {
  uint8_t message_length[2];  /* bytes 0 to 1 */
  uint8_t message_type[2];    /* bytes 2 to 3 */
} MessageHeader;

/* any Message Header at all: every byte one the checker chooses */
static void any_message_header(MessageHeader *record) {
  for (size_t i = 0; i < 2; i++) { record->message_length[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->message_type[i] = arbitrary(); }
}

/* Message Header to the wire: 4 bytes from at, returning where the next byte goes */
static size_t encode_message_header(const MessageHeader *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->message_length[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->message_type[i]; }

  return at;
}

/* Message Header off the wire: 4 bytes from at, returning where the next byte lies */
static size_t decode_message_header(MessageHeader *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->message_length[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->message_type[i] = wire[at++]; }

  return at;
}

/* what was read of Message Header is what was written, byte for byte */
static void equal_message_header(const MessageHeader *read, const MessageHeader *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->message_length[i] == written->message_length[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->message_type[i] == written->message_type[i]); }
}

/* Message Header: written and read back, then read and written back */
static void check_message_header(void) {
  MessageHeader sent;
  MessageHeader got;
  uint8_t wire[4];
  uint8_t again[4];

  any_message_header(&sent);
  assert(encode_message_header(&sent, wire, 0) == 4);
  assert(decode_message_header(&got, wire, 0) == 4);
  equal_message_header(&got, &sent);

  for (size_t i = 0; i < 4; i++) { wire[i] = arbitrary(); }
  assert(decode_message_header(&got, wire, 0) == 4);
  assert(encode_message_header(&got, again, 0) == 4);
  for (size_t i = 0; i < 4; i++) { assert(again[i] == wire[i]); }
}

/* ---- Catalog For Instruments Belonging To The Local And Global Stock Market Message: 111 bytes ---- */

/* It disseminates information on the local and global stock market. */
typedef struct {
  uint8_t instrument_number[4];      /* bytes 0 to 3 */
  uint8_t value_type[2];             /* bytes 4 to 5 */
  uint8_t issuer[7];                 /* bytes 6 to 12 */
  uint8_t series[6];                 /* bytes 13 to 18 */
  uint8_t last_price[8];             /* bytes 19 to 26 */
  uint8_t wap[8];                    /* bytes 27 to 34 */
  uint8_t closing_price[8];          /* bytes 35 to 42 */
  uint8_t reference_date[8];         /* bytes 43 to 50 */
  uint8_t reference[2];              /* bytes 51 to 52 */
  uint8_t current_coupon[2];         /* bytes 53 to 54 */
  uint8_t marketability[2];          /* bytes 55 to 56 */
  uint8_t numeric_marketability[4];  /* bytes 57 to 60 */
  uint8_t isin[12];                  /* bytes 61 to 72 */
  uint8_t market;                    /* byte 73 */
  uint8_t shares_outstanding[8];     /* bytes 74 to 81 */
  uint8_t blocks_amount[8];          /* bytes 82 to 89 */
  uint8_t exchange;                  /* byte 90 */
  uint8_t filler[20];                /* bytes 91 to 110 */
} CatalogForInstrumentsBelongingToTheLocalAndGlobalStockMar_gc6yau;

/* any Catalog For Instruments Belonging To The Local And Global Stock Market Message at all: every byte one the checker chooses */
static void any_catalog_for_instruments_belonging_to_the_local_and_global_stock_mar_gc6yau(CatalogForInstrumentsBelongingToTheLocalAndGlobalStockMar_gc6yau *record) {
  for (size_t i = 0; i < 4; i++) { record->instrument_number[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->value_type[i] = arbitrary(); }
  for (size_t i = 0; i < 7; i++) { record->issuer[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->series[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->last_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->wap[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->closing_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->reference_date[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->reference[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->current_coupon[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->marketability[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->numeric_marketability[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->isin[i] = arbitrary(); }
  record->market = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->shares_outstanding[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->blocks_amount[i] = arbitrary(); }
  record->exchange = arbitrary();
  for (size_t i = 0; i < 20; i++) { record->filler[i] = arbitrary(); }
}

/* Catalog For Instruments Belonging To The Local And Global Stock Market Message to the wire: 111 bytes from at, returning where the next byte goes */
static size_t encode_catalog_for_instruments_belonging_to_the_local_and_global_stock_mar_gc6yau(const CatalogForInstrumentsBelongingToTheLocalAndGlobalStockMar_gc6yau *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument_number[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->value_type[i]; }
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->issuer[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->series[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->last_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->wap[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->closing_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->reference_date[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->reference[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->current_coupon[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->marketability[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->numeric_marketability[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->isin[i]; }
  wire[at++] = record->market;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->shares_outstanding[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->blocks_amount[i]; }
  wire[at++] = record->exchange;
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->filler[i]; }

  return at;
}

/* Catalog For Instruments Belonging To The Local And Global Stock Market Message off the wire: 111 bytes from at, returning where the next byte lies */
static size_t decode_catalog_for_instruments_belonging_to_the_local_and_global_stock_mar_gc6yau(CatalogForInstrumentsBelongingToTheLocalAndGlobalStockMar_gc6yau *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->instrument_number[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->value_type[i] = wire[at++]; }
  for (size_t i = 0; i < 7; i++) { record->issuer[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->series[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->last_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->wap[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->closing_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->reference_date[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->reference[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->current_coupon[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->marketability[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->numeric_marketability[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->isin[i] = wire[at++]; }
  record->market = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->shares_outstanding[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->blocks_amount[i] = wire[at++]; }
  record->exchange = wire[at++];
  for (size_t i = 0; i < 20; i++) { record->filler[i] = wire[at++]; }

  return at;
}

/* what was read of Catalog For Instruments Belonging To The Local And Global Stock Market Message is what was written, byte for byte */
static void equal_catalog_for_instruments_belonging_to_the_local_and_global_stock_mar_gc6yau(const CatalogForInstrumentsBelongingToTheLocalAndGlobalStockMar_gc6yau *read, const CatalogForInstrumentsBelongingToTheLocalAndGlobalStockMar_gc6yau *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->instrument_number[i] == written->instrument_number[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->value_type[i] == written->value_type[i]); }
  for (size_t i = 0; i < 7; i++) { assert(read->issuer[i] == written->issuer[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->series[i] == written->series[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->last_price[i] == written->last_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->wap[i] == written->wap[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->closing_price[i] == written->closing_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->reference_date[i] == written->reference_date[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->reference[i] == written->reference[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->current_coupon[i] == written->current_coupon[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->marketability[i] == written->marketability[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->numeric_marketability[i] == written->numeric_marketability[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->isin[i] == written->isin[i]); }
  assert(read->market == written->market);
  for (size_t i = 0; i < 8; i++) { assert(read->shares_outstanding[i] == written->shares_outstanding[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->blocks_amount[i] == written->blocks_amount[i]); }
  assert(read->exchange == written->exchange);
  for (size_t i = 0; i < 20; i++) { assert(read->filler[i] == written->filler[i]); }
}

/* Catalog For Instruments Belonging To The Local And Global Stock Market Message: written and read back, then read and written back */
static void check_catalog_for_instruments_belonging_to_the_local_and_global_stock_mar_gc6yau(void) {
  CatalogForInstrumentsBelongingToTheLocalAndGlobalStockMar_gc6yau sent;
  CatalogForInstrumentsBelongingToTheLocalAndGlobalStockMar_gc6yau got;
  uint8_t wire[111];
  uint8_t again[111];

  any_catalog_for_instruments_belonging_to_the_local_and_global_stock_mar_gc6yau(&sent);
  assert(encode_catalog_for_instruments_belonging_to_the_local_and_global_stock_mar_gc6yau(&sent, wire, 0) == 111);
  assert(decode_catalog_for_instruments_belonging_to_the_local_and_global_stock_mar_gc6yau(&got, wire, 0) == 111);
  equal_catalog_for_instruments_belonging_to_the_local_and_global_stock_mar_gc6yau(&got, &sent);

  for (size_t i = 0; i < 111; i++) { wire[i] = arbitrary(); }
  assert(decode_catalog_for_instruments_belonging_to_the_local_and_global_stock_mar_gc6yau(&got, wire, 0) == 111);
  assert(encode_catalog_for_instruments_belonging_to_the_local_and_global_stock_mar_gc6yau(&got, again, 0) == 111);
  for (size_t i = 0; i < 111; i++) { assert(again[i] == wire[i]); }
}

/* ---- Catalog Of Instruments That Belong To The Debt Metals And Money Market Message: 124 bytes ---- */

/* Catalog of instruments that belong to the Debt, Metals and Money market */
typedef struct {
  uint8_t instrument_number[4];       /* bytes 0 to 3 */
  uint8_t value_type[2];              /* bytes 4 to 5 */
  uint8_t issuer[7];                  /* bytes 6 to 12 */
  uint8_t issue[6];                   /* bytes 13 to 18 */
  uint8_t issue_date[8];              /* bytes 19 to 26 */
  uint8_t maturity_date[8];           /* bytes 27 to 34 */
  uint8_t reference_pricerate[8];     /* bytes 35 to 42 */
  uint8_t reference_date[8];          /* bytes 43 to 50 */
  uint8_t reference[2];               /* bytes 51 to 52 */
  uint8_t term_days[2];               /* bytes 53 to 54 */
  uint8_t current_coupon[2];          /* bytes 55 to 56 */
  uint8_t isin[12];                   /* bytes 57 to 68 */
  uint8_t market;                     /* byte 69 */
  uint8_t current_nominal_value[8];   /* bytes 70 to 77 */
  uint8_t original_nominal_value[8];  /* bytes 78 to 85 */
  uint8_t outstanding_shares[8];      /* bytes 86 to 93 */
  uint8_t amount_placed[8];           /* bytes 94 to 101 */
  uint8_t operate_price_rate;         /* byte 102 */
  uint8_t exchange;                   /* byte 103 */
  uint8_t filler[20];                 /* bytes 104 to 123 */
} CatalogOfInstrumentsThatBelongToTheDebtMetalsAndMoneyMark_a9x5rm;

/* any Catalog Of Instruments That Belong To The Debt Metals And Money Market Message at all: every byte one the checker chooses */
static void any_catalog_of_instruments_that_belong_to_the_debt_metals_and_money_mark_a9x5rm(CatalogOfInstrumentsThatBelongToTheDebtMetalsAndMoneyMark_a9x5rm *record) {
  for (size_t i = 0; i < 4; i++) { record->instrument_number[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->value_type[i] = arbitrary(); }
  for (size_t i = 0; i < 7; i++) { record->issuer[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->issue[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->issue_date[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->maturity_date[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->reference_pricerate[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->reference_date[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->reference[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->term_days[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->current_coupon[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->isin[i] = arbitrary(); }
  record->market = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->current_nominal_value[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->original_nominal_value[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->outstanding_shares[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->amount_placed[i] = arbitrary(); }
  record->operate_price_rate = arbitrary();
  record->exchange = arbitrary();
  for (size_t i = 0; i < 20; i++) { record->filler[i] = arbitrary(); }
}

/* Catalog Of Instruments That Belong To The Debt Metals And Money Market Message to the wire: 124 bytes from at, returning where the next byte goes */
static size_t encode_catalog_of_instruments_that_belong_to_the_debt_metals_and_money_mark_a9x5rm(const CatalogOfInstrumentsThatBelongToTheDebtMetalsAndMoneyMark_a9x5rm *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument_number[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->value_type[i]; }
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->issuer[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->issue[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->issue_date[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->maturity_date[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->reference_pricerate[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->reference_date[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->reference[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->term_days[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->current_coupon[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->isin[i]; }
  wire[at++] = record->market;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->current_nominal_value[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->original_nominal_value[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->outstanding_shares[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->amount_placed[i]; }
  wire[at++] = record->operate_price_rate;
  wire[at++] = record->exchange;
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->filler[i]; }

  return at;
}

/* Catalog Of Instruments That Belong To The Debt Metals And Money Market Message off the wire: 124 bytes from at, returning where the next byte lies */
static size_t decode_catalog_of_instruments_that_belong_to_the_debt_metals_and_money_mark_a9x5rm(CatalogOfInstrumentsThatBelongToTheDebtMetalsAndMoneyMark_a9x5rm *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->instrument_number[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->value_type[i] = wire[at++]; }
  for (size_t i = 0; i < 7; i++) { record->issuer[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->issue[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->issue_date[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->maturity_date[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->reference_pricerate[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->reference_date[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->reference[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->term_days[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->current_coupon[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->isin[i] = wire[at++]; }
  record->market = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->current_nominal_value[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->original_nominal_value[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->outstanding_shares[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->amount_placed[i] = wire[at++]; }
  record->operate_price_rate = wire[at++];
  record->exchange = wire[at++];
  for (size_t i = 0; i < 20; i++) { record->filler[i] = wire[at++]; }

  return at;
}

/* what was read of Catalog Of Instruments That Belong To The Debt Metals And Money Market Message is what was written, byte for byte */
static void equal_catalog_of_instruments_that_belong_to_the_debt_metals_and_money_mark_a9x5rm(const CatalogOfInstrumentsThatBelongToTheDebtMetalsAndMoneyMark_a9x5rm *read, const CatalogOfInstrumentsThatBelongToTheDebtMetalsAndMoneyMark_a9x5rm *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->instrument_number[i] == written->instrument_number[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->value_type[i] == written->value_type[i]); }
  for (size_t i = 0; i < 7; i++) { assert(read->issuer[i] == written->issuer[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->issue[i] == written->issue[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->issue_date[i] == written->issue_date[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->maturity_date[i] == written->maturity_date[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->reference_pricerate[i] == written->reference_pricerate[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->reference_date[i] == written->reference_date[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->reference[i] == written->reference[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->term_days[i] == written->term_days[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->current_coupon[i] == written->current_coupon[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->isin[i] == written->isin[i]); }
  assert(read->market == written->market);
  for (size_t i = 0; i < 8; i++) { assert(read->current_nominal_value[i] == written->current_nominal_value[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->original_nominal_value[i] == written->original_nominal_value[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->outstanding_shares[i] == written->outstanding_shares[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->amount_placed[i] == written->amount_placed[i]); }
  assert(read->operate_price_rate == written->operate_price_rate);
  assert(read->exchange == written->exchange);
  for (size_t i = 0; i < 20; i++) { assert(read->filler[i] == written->filler[i]); }
}

/* Catalog Of Instruments That Belong To The Debt Metals And Money Market Message: written and read back, then read and written back */
static void check_catalog_of_instruments_that_belong_to_the_debt_metals_and_money_mark_a9x5rm(void) {
  CatalogOfInstrumentsThatBelongToTheDebtMetalsAndMoneyMark_a9x5rm sent;
  CatalogOfInstrumentsThatBelongToTheDebtMetalsAndMoneyMark_a9x5rm got;
  uint8_t wire[124];
  uint8_t again[124];

  any_catalog_of_instruments_that_belong_to_the_debt_metals_and_money_mark_a9x5rm(&sent);
  assert(encode_catalog_of_instruments_that_belong_to_the_debt_metals_and_money_mark_a9x5rm(&sent, wire, 0) == 124);
  assert(decode_catalog_of_instruments_that_belong_to_the_debt_metals_and_money_mark_a9x5rm(&got, wire, 0) == 124);
  equal_catalog_of_instruments_that_belong_to_the_debt_metals_and_money_mark_a9x5rm(&got, &sent);

  for (size_t i = 0; i < 124; i++) { wire[i] = arbitrary(); }
  assert(decode_catalog_of_instruments_that_belong_to_the_debt_metals_and_money_mark_a9x5rm(&got, wire, 0) == 124);
  assert(encode_catalog_of_instruments_that_belong_to_the_debt_metals_and_money_mark_a9x5rm(&got, again, 0) == 124);
  for (size_t i = 0; i < 124; i++) { assert(again[i] == wire[i]); }
}

/* ---- Catalog For Instruments Belonging To The Capital Warrants Market Message: 87 bytes ---- */

/* Catalog for instruments belonging to the capital warrants market */
typedef struct {
  uint8_t instrument_number[4];  /* bytes 0 to 3 */
  uint8_t value_type[2];         /* bytes 4 to 5 */
  uint8_t issuer[7];             /* bytes 6 to 12 */
  uint8_t series[6];             /* bytes 13 to 18 */
  uint8_t warrant_type;          /* byte 19 */
  uint8_t maturity_date[8];      /* bytes 20 to 27 */
  uint8_t exercise_price[8];     /* bytes 28 to 35 */
  uint8_t reference_price[8];    /* bytes 36 to 43 */
  uint8_t reference_date[8];     /* bytes 44 to 51 */
  uint8_t reference[2];          /* bytes 52 to 53 */
  uint8_t isin[12];              /* bytes 54 to 65 */
  uint8_t exchange;              /* byte 66 */
  uint8_t filler[20];            /* bytes 67 to 86 */
} CatalogForInstrumentsBelongingToTheCapitalWarrantsMarketMessage;

/* any Catalog For Instruments Belonging To The Capital Warrants Market Message at all: every byte one the checker chooses */
static void any_catalog_for_instruments_belonging_to_the_capital_warrants_market_message(CatalogForInstrumentsBelongingToTheCapitalWarrantsMarketMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->instrument_number[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->value_type[i] = arbitrary(); }
  for (size_t i = 0; i < 7; i++) { record->issuer[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->series[i] = arbitrary(); }
  record->warrant_type = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->maturity_date[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->exercise_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->reference_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->reference_date[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->reference[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->isin[i] = arbitrary(); }
  record->exchange = arbitrary();
  for (size_t i = 0; i < 20; i++) { record->filler[i] = arbitrary(); }
}

/* Catalog For Instruments Belonging To The Capital Warrants Market Message to the wire: 87 bytes from at, returning where the next byte goes */
static size_t encode_catalog_for_instruments_belonging_to_the_capital_warrants_market_message(const CatalogForInstrumentsBelongingToTheCapitalWarrantsMarketMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument_number[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->value_type[i]; }
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->issuer[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->series[i]; }
  wire[at++] = record->warrant_type;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->maturity_date[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->exercise_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->reference_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->reference_date[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->reference[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->isin[i]; }
  wire[at++] = record->exchange;
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->filler[i]; }

  return at;
}

/* Catalog For Instruments Belonging To The Capital Warrants Market Message off the wire: 87 bytes from at, returning where the next byte lies */
static size_t decode_catalog_for_instruments_belonging_to_the_capital_warrants_market_message(CatalogForInstrumentsBelongingToTheCapitalWarrantsMarketMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->instrument_number[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->value_type[i] = wire[at++]; }
  for (size_t i = 0; i < 7; i++) { record->issuer[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->series[i] = wire[at++]; }
  record->warrant_type = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->maturity_date[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->exercise_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->reference_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->reference_date[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->reference[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->isin[i] = wire[at++]; }
  record->exchange = wire[at++];
  for (size_t i = 0; i < 20; i++) { record->filler[i] = wire[at++]; }

  return at;
}

/* what was read of Catalog For Instruments Belonging To The Capital Warrants Market Message is what was written, byte for byte */
static void equal_catalog_for_instruments_belonging_to_the_capital_warrants_market_message(const CatalogForInstrumentsBelongingToTheCapitalWarrantsMarketMessage *read, const CatalogForInstrumentsBelongingToTheCapitalWarrantsMarketMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->instrument_number[i] == written->instrument_number[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->value_type[i] == written->value_type[i]); }
  for (size_t i = 0; i < 7; i++) { assert(read->issuer[i] == written->issuer[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->series[i] == written->series[i]); }
  assert(read->warrant_type == written->warrant_type);
  for (size_t i = 0; i < 8; i++) { assert(read->maturity_date[i] == written->maturity_date[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->exercise_price[i] == written->exercise_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->reference_price[i] == written->reference_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->reference_date[i] == written->reference_date[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->reference[i] == written->reference[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->isin[i] == written->isin[i]); }
  assert(read->exchange == written->exchange);
  for (size_t i = 0; i < 20; i++) { assert(read->filler[i] == written->filler[i]); }
}

/* Catalog For Instruments Belonging To The Capital Warrants Market Message: written and read back, then read and written back */
static void check_catalog_for_instruments_belonging_to_the_capital_warrants_market_message(void) {
  CatalogForInstrumentsBelongingToTheCapitalWarrantsMarketMessage sent;
  CatalogForInstrumentsBelongingToTheCapitalWarrantsMarketMessage got;
  uint8_t wire[87];
  uint8_t again[87];

  any_catalog_for_instruments_belonging_to_the_capital_warrants_market_message(&sent);
  assert(encode_catalog_for_instruments_belonging_to_the_capital_warrants_market_message(&sent, wire, 0) == 87);
  assert(decode_catalog_for_instruments_belonging_to_the_capital_warrants_market_message(&got, wire, 0) == 87);
  equal_catalog_for_instruments_belonging_to_the_capital_warrants_market_message(&got, &sent);

  for (size_t i = 0; i < 87; i++) { wire[i] = arbitrary(); }
  assert(decode_catalog_for_instruments_belonging_to_the_capital_warrants_market_message(&got, wire, 0) == 87);
  assert(encode_catalog_for_instruments_belonging_to_the_capital_warrants_market_message(&got, again, 0) == 87);
  for (size_t i = 0; i < 87; i++) { assert(again[i] == wire[i]); }
}

/* ---- Options Futures And Swaps Derivatives Market Instruments Catalog Message: 113 bytes ---- */

/* Options, futures and swaps derivatives market instruments catalog */
typedef struct {
  uint8_t instrument_number[4];           /* bytes 0 to 3 */
  uint8_t value_type[2];                  /* bytes 4 to 5 */
  uint8_t class[7];                       /* bytes 6 to 12 */
  uint8_t maturity[6];                    /* bytes 13 to 18 */
  uint8_t option_type;                    /* byte 19 */
  uint8_t exercise_price[8];              /* bytes 20 to 27 */
  uint8_t bid[8];                         /* bytes 28 to 35 */
  uint8_t prior_day_settlement_price[8];  /* bytes 36 to 43 */
  uint8_t last_day_of_operation[8];       /* bytes 44 to 51 */
  uint8_t maturity_date[8];               /* bytes 52 to 59 */
  uint8_t open_contracts[4];              /* bytes 60 to 63 */
  uint8_t contract_size[4];               /* bytes 64 to 67 */
  uint8_t product_code[12];               /* bytes 68 to 79 */
  uint8_t daily_maturity;                 /* byte 80 */
  uint8_t key_exercise_price[6];          /* bytes 81 to 86 */
  uint8_t cfi_code[6];                    /* bytes 87 to 92 */
  uint8_t filler[20];                     /* bytes 93 to 112 */
} OptionsFuturesAndSwapsDerivativesMarketInstrumentsCatalogMessage;

/* any Options Futures And Swaps Derivatives Market Instruments Catalog Message at all: every byte one the checker chooses */
static void any_options_futures_and_swaps_derivatives_market_instruments_catalog_message(OptionsFuturesAndSwapsDerivativesMarketInstrumentsCatalogMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->instrument_number[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->value_type[i] = arbitrary(); }
  for (size_t i = 0; i < 7; i++) { record->class[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->maturity[i] = arbitrary(); }
  record->option_type = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->exercise_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->bid[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->prior_day_settlement_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->last_day_of_operation[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->maturity_date[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->open_contracts[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->contract_size[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->product_code[i] = arbitrary(); }
  record->daily_maturity = arbitrary();
  for (size_t i = 0; i < 6; i++) { record->key_exercise_price[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->cfi_code[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->filler[i] = arbitrary(); }
}

/* Options Futures And Swaps Derivatives Market Instruments Catalog Message to the wire: 113 bytes from at, returning where the next byte goes */
static size_t encode_options_futures_and_swaps_derivatives_market_instruments_catalog_message(const OptionsFuturesAndSwapsDerivativesMarketInstrumentsCatalogMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument_number[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->value_type[i]; }
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->class[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->maturity[i]; }
  wire[at++] = record->option_type;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->exercise_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->bid[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->prior_day_settlement_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->last_day_of_operation[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->maturity_date[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->open_contracts[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->contract_size[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->product_code[i]; }
  wire[at++] = record->daily_maturity;
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->key_exercise_price[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->cfi_code[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->filler[i]; }

  return at;
}

/* Options Futures And Swaps Derivatives Market Instruments Catalog Message off the wire: 113 bytes from at, returning where the next byte lies */
static size_t decode_options_futures_and_swaps_derivatives_market_instruments_catalog_message(OptionsFuturesAndSwapsDerivativesMarketInstrumentsCatalogMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->instrument_number[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->value_type[i] = wire[at++]; }
  for (size_t i = 0; i < 7; i++) { record->class[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->maturity[i] = wire[at++]; }
  record->option_type = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->exercise_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->bid[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->prior_day_settlement_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->last_day_of_operation[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->maturity_date[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->open_contracts[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->contract_size[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->product_code[i] = wire[at++]; }
  record->daily_maturity = wire[at++];
  for (size_t i = 0; i < 6; i++) { record->key_exercise_price[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->cfi_code[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->filler[i] = wire[at++]; }

  return at;
}

/* what was read of Options Futures And Swaps Derivatives Market Instruments Catalog Message is what was written, byte for byte */
static void equal_options_futures_and_swaps_derivatives_market_instruments_catalog_message(const OptionsFuturesAndSwapsDerivativesMarketInstrumentsCatalogMessage *read, const OptionsFuturesAndSwapsDerivativesMarketInstrumentsCatalogMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->instrument_number[i] == written->instrument_number[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->value_type[i] == written->value_type[i]); }
  for (size_t i = 0; i < 7; i++) { assert(read->class[i] == written->class[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->maturity[i] == written->maturity[i]); }
  assert(read->option_type == written->option_type);
  for (size_t i = 0; i < 8; i++) { assert(read->exercise_price[i] == written->exercise_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->bid[i] == written->bid[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->prior_day_settlement_price[i] == written->prior_day_settlement_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->last_day_of_operation[i] == written->last_day_of_operation[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->maturity_date[i] == written->maturity_date[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->open_contracts[i] == written->open_contracts[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->contract_size[i] == written->contract_size[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->product_code[i] == written->product_code[i]); }
  assert(read->daily_maturity == written->daily_maturity);
  for (size_t i = 0; i < 6; i++) { assert(read->key_exercise_price[i] == written->key_exercise_price[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->cfi_code[i] == written->cfi_code[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->filler[i] == written->filler[i]); }
}

/* Options Futures And Swaps Derivatives Market Instruments Catalog Message: written and read back, then read and written back */
static void check_options_futures_and_swaps_derivatives_market_instruments_catalog_message(void) {
  OptionsFuturesAndSwapsDerivativesMarketInstrumentsCatalogMessage sent;
  OptionsFuturesAndSwapsDerivativesMarketInstrumentsCatalogMessage got;
  uint8_t wire[113];
  uint8_t again[113];

  any_options_futures_and_swaps_derivatives_market_instruments_catalog_message(&sent);
  assert(encode_options_futures_and_swaps_derivatives_market_instruments_catalog_message(&sent, wire, 0) == 113);
  assert(decode_options_futures_and_swaps_derivatives_market_instruments_catalog_message(&got, wire, 0) == 113);
  equal_options_futures_and_swaps_derivatives_market_instruments_catalog_message(&got, &sent);

  for (size_t i = 0; i < 113; i++) { wire[i] = arbitrary(); }
  assert(decode_options_futures_and_swaps_derivatives_market_instruments_catalog_message(&got, wire, 0) == 113);
  assert(encode_options_futures_and_swaps_derivatives_market_instruments_catalog_message(&got, again, 0) == 113);
  for (size_t i = 0; i < 113; i++) { assert(again[i] == wire[i]); }
}

/* ---- Catalog Sent For Instruments Belonging To Capital Tracs Message: 101 bytes ---- */

/* Catalog sent for instruments belonging to capital TRACS */
typedef struct {
  uint8_t trac_number[4];             /* bytes 0 to 3 */
  uint8_t trac_name[8];               /* bytes 4 to 11 */
  uint8_t underlying_issuer[7];       /* bytes 12 to 18 */
  uint8_t underlying_series[6];       /* bytes 19 to 24 */
  uint8_t securities[8];              /* bytes 25 to 32 */
  uint8_t excluded_securities[8];     /* bytes 33 to 40 */
  uint8_t price[8];                   /* bytes 41 to 48 */
  uint8_t cash_component[8];          /* bytes 49 to 56 */
  uint8_t excluded_value[8];          /* bytes 57 to 64 */
  uint8_t number_of_certificates[8];  /* bytes 65 to 72 */
  uint8_t theoretical_price[8];       /* bytes 73 to 80 */
  uint8_t filler[20];                 /* bytes 81 to 100 */
} CatalogSentForInstrumentsBelongingToCapitalTracsMessage;

/* any Catalog Sent For Instruments Belonging To Capital Tracs Message at all: every byte one the checker chooses */
static void any_catalog_sent_for_instruments_belonging_to_capital_tracs_message(CatalogSentForInstrumentsBelongingToCapitalTracsMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->trac_number[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->trac_name[i] = arbitrary(); }
  for (size_t i = 0; i < 7; i++) { record->underlying_issuer[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->underlying_series[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->securities[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->excluded_securities[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->cash_component[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->excluded_value[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->number_of_certificates[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->theoretical_price[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->filler[i] = arbitrary(); }
}

/* Catalog Sent For Instruments Belonging To Capital Tracs Message to the wire: 101 bytes from at, returning where the next byte goes */
static size_t encode_catalog_sent_for_instruments_belonging_to_capital_tracs_message(const CatalogSentForInstrumentsBelongingToCapitalTracsMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->trac_number[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->trac_name[i]; }
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->underlying_issuer[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->underlying_series[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->securities[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->excluded_securities[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->cash_component[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->excluded_value[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->number_of_certificates[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->theoretical_price[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->filler[i]; }

  return at;
}

/* Catalog Sent For Instruments Belonging To Capital Tracs Message off the wire: 101 bytes from at, returning where the next byte lies */
static size_t decode_catalog_sent_for_instruments_belonging_to_capital_tracs_message(CatalogSentForInstrumentsBelongingToCapitalTracsMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->trac_number[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->trac_name[i] = wire[at++]; }
  for (size_t i = 0; i < 7; i++) { record->underlying_issuer[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->underlying_series[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->securities[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->excluded_securities[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->cash_component[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->excluded_value[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->number_of_certificates[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->theoretical_price[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->filler[i] = wire[at++]; }

  return at;
}

/* what was read of Catalog Sent For Instruments Belonging To Capital Tracs Message is what was written, byte for byte */
static void equal_catalog_sent_for_instruments_belonging_to_capital_tracs_message(const CatalogSentForInstrumentsBelongingToCapitalTracsMessage *read, const CatalogSentForInstrumentsBelongingToCapitalTracsMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->trac_number[i] == written->trac_number[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->trac_name[i] == written->trac_name[i]); }
  for (size_t i = 0; i < 7; i++) { assert(read->underlying_issuer[i] == written->underlying_issuer[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->underlying_series[i] == written->underlying_series[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->securities[i] == written->securities[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->excluded_securities[i] == written->excluded_securities[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->price[i] == written->price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->cash_component[i] == written->cash_component[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->excluded_value[i] == written->excluded_value[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->number_of_certificates[i] == written->number_of_certificates[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->theoretical_price[i] == written->theoretical_price[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->filler[i] == written->filler[i]); }
}

/* Catalog Sent For Instruments Belonging To Capital Tracs Message: written and read back, then read and written back */
static void check_catalog_sent_for_instruments_belonging_to_capital_tracs_message(void) {
  CatalogSentForInstrumentsBelongingToCapitalTracsMessage sent;
  CatalogSentForInstrumentsBelongingToCapitalTracsMessage got;
  uint8_t wire[101];
  uint8_t again[101];

  any_catalog_sent_for_instruments_belonging_to_capital_tracs_message(&sent);
  assert(encode_catalog_sent_for_instruments_belonging_to_capital_tracs_message(&sent, wire, 0) == 101);
  assert(decode_catalog_sent_for_instruments_belonging_to_capital_tracs_message(&got, wire, 0) == 101);
  equal_catalog_sent_for_instruments_belonging_to_capital_tracs_message(&got, &sent);

  for (size_t i = 0; i < 101; i++) { wire[i] = arbitrary(); }
  assert(decode_catalog_sent_for_instruments_belonging_to_capital_tracs_message(&got, wire, 0) == 101);
  assert(encode_catalog_sent_for_instruments_belonging_to_capital_tracs_message(&got, again, 0) == 101);
  for (size_t i = 0; i < 101; i++) { assert(again[i] == wire[i]); }
}

/* ---- Catalog Sent For Instruments Belonging To Mutual Funds Message: 98 bytes ---- */

/* Catalog sent for instruments belonging to mutual funds */
typedef struct {
  uint8_t instrument_number[4];   /* bytes 0 to 3 */
  uint8_t value_type[2];          /* bytes 4 to 5 */
  uint8_t issuer[7];              /* bytes 6 to 12 */
  uint8_t series[6];              /* bytes 13 to 18 */
  uint8_t sector;                 /* byte 19 */
  uint8_t subsector;              /* byte 20 */
  uint8_t business_line;          /* byte 21 */
  uint8_t sub_line;               /* byte 22 */
  uint8_t operating_company[10];  /* bytes 23 to 32 */
  uint8_t reference_price[8];     /* bytes 33 to 40 */
  uint8_t reference_date[8];      /* bytes 41 to 48 */
  uint8_t reference[2];           /* bytes 49 to 50 */
  uint8_t isin[12];               /* bytes 51 to 62 */
  uint8_t rating[15];             /* bytes 63 to 77 */
  uint8_t filler[20];             /* bytes 78 to 97 */
} CatalogSentForInstrumentsBelongingToMutualFundsMessage;

/* any Catalog Sent For Instruments Belonging To Mutual Funds Message at all: every byte one the checker chooses */
static void any_catalog_sent_for_instruments_belonging_to_mutual_funds_message(CatalogSentForInstrumentsBelongingToMutualFundsMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->instrument_number[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->value_type[i] = arbitrary(); }
  for (size_t i = 0; i < 7; i++) { record->issuer[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->series[i] = arbitrary(); }
  record->sector = arbitrary();
  record->subsector = arbitrary();
  record->business_line = arbitrary();
  record->sub_line = arbitrary();
  for (size_t i = 0; i < 10; i++) { record->operating_company[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->reference_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->reference_date[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->reference[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->isin[i] = arbitrary(); }
  for (size_t i = 0; i < 15; i++) { record->rating[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->filler[i] = arbitrary(); }
}

/* Catalog Sent For Instruments Belonging To Mutual Funds Message to the wire: 98 bytes from at, returning where the next byte goes */
static size_t encode_catalog_sent_for_instruments_belonging_to_mutual_funds_message(const CatalogSentForInstrumentsBelongingToMutualFundsMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument_number[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->value_type[i]; }
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->issuer[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->series[i]; }
  wire[at++] = record->sector;
  wire[at++] = record->subsector;
  wire[at++] = record->business_line;
  wire[at++] = record->sub_line;
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->operating_company[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->reference_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->reference_date[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->reference[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->isin[i]; }
  for (size_t i = 0; i < 15; i++) { wire[at++] = record->rating[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->filler[i]; }

  return at;
}

/* Catalog Sent For Instruments Belonging To Mutual Funds Message off the wire: 98 bytes from at, returning where the next byte lies */
static size_t decode_catalog_sent_for_instruments_belonging_to_mutual_funds_message(CatalogSentForInstrumentsBelongingToMutualFundsMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->instrument_number[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->value_type[i] = wire[at++]; }
  for (size_t i = 0; i < 7; i++) { record->issuer[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->series[i] = wire[at++]; }
  record->sector = wire[at++];
  record->subsector = wire[at++];
  record->business_line = wire[at++];
  record->sub_line = wire[at++];
  for (size_t i = 0; i < 10; i++) { record->operating_company[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->reference_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->reference_date[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->reference[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->isin[i] = wire[at++]; }
  for (size_t i = 0; i < 15; i++) { record->rating[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->filler[i] = wire[at++]; }

  return at;
}

/* what was read of Catalog Sent For Instruments Belonging To Mutual Funds Message is what was written, byte for byte */
static void equal_catalog_sent_for_instruments_belonging_to_mutual_funds_message(const CatalogSentForInstrumentsBelongingToMutualFundsMessage *read, const CatalogSentForInstrumentsBelongingToMutualFundsMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->instrument_number[i] == written->instrument_number[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->value_type[i] == written->value_type[i]); }
  for (size_t i = 0; i < 7; i++) { assert(read->issuer[i] == written->issuer[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->series[i] == written->series[i]); }
  assert(read->sector == written->sector);
  assert(read->subsector == written->subsector);
  assert(read->business_line == written->business_line);
  assert(read->sub_line == written->sub_line);
  for (size_t i = 0; i < 10; i++) { assert(read->operating_company[i] == written->operating_company[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->reference_price[i] == written->reference_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->reference_date[i] == written->reference_date[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->reference[i] == written->reference[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->isin[i] == written->isin[i]); }
  for (size_t i = 0; i < 15; i++) { assert(read->rating[i] == written->rating[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->filler[i] == written->filler[i]); }
}

/* Catalog Sent For Instruments Belonging To Mutual Funds Message: written and read back, then read and written back */
static void check_catalog_sent_for_instruments_belonging_to_mutual_funds_message(void) {
  CatalogSentForInstrumentsBelongingToMutualFundsMessage sent;
  CatalogSentForInstrumentsBelongingToMutualFundsMessage got;
  uint8_t wire[98];
  uint8_t again[98];

  any_catalog_sent_for_instruments_belonging_to_mutual_funds_message(&sent);
  assert(encode_catalog_sent_for_instruments_belonging_to_mutual_funds_message(&sent, wire, 0) == 98);
  assert(decode_catalog_sent_for_instruments_belonging_to_mutual_funds_message(&got, wire, 0) == 98);
  equal_catalog_sent_for_instruments_belonging_to_mutual_funds_message(&got, &sent);

  for (size_t i = 0; i < 98; i++) { wire[i] = arbitrary(); }
  assert(decode_catalog_sent_for_instruments_belonging_to_mutual_funds_message(&got, wire, 0) == 98);
  assert(encode_catalog_sent_for_instruments_belonging_to_mutual_funds_message(&got, again, 0) == 98);
  for (size_t i = 0; i < 98; i++) { assert(again[i] == wire[i]); }
}

/* ---- Catalog Sent For Instruments Belonging To The Strategy Derivative Market Message: 74 bytes ---- */

/* Catalog sent for instruments belonging to the strategy derivative market */
typedef struct {
  uint8_t instrument_number[4];                /* bytes 0 to 3 */
  uint8_t value_type[2];                       /* bytes 4 to 5 */
  uint8_t class[7];                            /* bytes 6 to 12 */
  uint8_t maturity[6];                         /* bytes 13 to 18 */
  uint8_t type_of_strategy;                    /* byte 19 */
  uint8_t bid[8];                              /* bytes 20 to 27 */
  uint8_t last_date_operation[8];              /* bytes 28 to 35 */
  uint8_t maturity_date[8];                    /* bytes 36 to 43 */
  uint8_t short_leg_instrument_identifier[4];  /* bytes 44 to 47 */
  uint8_t long_leg_instruments_id[4];          /* bytes 48 to 51 */
  uint8_t frequency;                           /* byte 52 */
  uint8_t number_of_maturities;                /* byte 53 */
  uint8_t filler[20];                          /* bytes 54 to 73 */
} CatalogSentForInstrumentsBelongingToTheStrategyDerivative_nw7mmt;

/* any Catalog Sent For Instruments Belonging To The Strategy Derivative Market Message at all: every byte one the checker chooses */
static void any_catalog_sent_for_instruments_belonging_to_the_strategy_derivative_nw7mmt(CatalogSentForInstrumentsBelongingToTheStrategyDerivative_nw7mmt *record) {
  for (size_t i = 0; i < 4; i++) { record->instrument_number[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->value_type[i] = arbitrary(); }
  for (size_t i = 0; i < 7; i++) { record->class[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->maturity[i] = arbitrary(); }
  record->type_of_strategy = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->bid[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->last_date_operation[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->maturity_date[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->short_leg_instrument_identifier[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->long_leg_instruments_id[i] = arbitrary(); }
  record->frequency = arbitrary();
  record->number_of_maturities = arbitrary();
  for (size_t i = 0; i < 20; i++) { record->filler[i] = arbitrary(); }
}

/* Catalog Sent For Instruments Belonging To The Strategy Derivative Market Message to the wire: 74 bytes from at, returning where the next byte goes */
static size_t encode_catalog_sent_for_instruments_belonging_to_the_strategy_derivative_nw7mmt(const CatalogSentForInstrumentsBelongingToTheStrategyDerivative_nw7mmt *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument_number[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->value_type[i]; }
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->class[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->maturity[i]; }
  wire[at++] = record->type_of_strategy;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->bid[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->last_date_operation[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->maturity_date[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->short_leg_instrument_identifier[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->long_leg_instruments_id[i]; }
  wire[at++] = record->frequency;
  wire[at++] = record->number_of_maturities;
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->filler[i]; }

  return at;
}

/* Catalog Sent For Instruments Belonging To The Strategy Derivative Market Message off the wire: 74 bytes from at, returning where the next byte lies */
static size_t decode_catalog_sent_for_instruments_belonging_to_the_strategy_derivative_nw7mmt(CatalogSentForInstrumentsBelongingToTheStrategyDerivative_nw7mmt *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->instrument_number[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->value_type[i] = wire[at++]; }
  for (size_t i = 0; i < 7; i++) { record->class[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->maturity[i] = wire[at++]; }
  record->type_of_strategy = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->bid[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->last_date_operation[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->maturity_date[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->short_leg_instrument_identifier[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->long_leg_instruments_id[i] = wire[at++]; }
  record->frequency = wire[at++];
  record->number_of_maturities = wire[at++];
  for (size_t i = 0; i < 20; i++) { record->filler[i] = wire[at++]; }

  return at;
}

/* what was read of Catalog Sent For Instruments Belonging To The Strategy Derivative Market Message is what was written, byte for byte */
static void equal_catalog_sent_for_instruments_belonging_to_the_strategy_derivative_nw7mmt(const CatalogSentForInstrumentsBelongingToTheStrategyDerivative_nw7mmt *read, const CatalogSentForInstrumentsBelongingToTheStrategyDerivative_nw7mmt *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->instrument_number[i] == written->instrument_number[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->value_type[i] == written->value_type[i]); }
  for (size_t i = 0; i < 7; i++) { assert(read->class[i] == written->class[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->maturity[i] == written->maturity[i]); }
  assert(read->type_of_strategy == written->type_of_strategy);
  for (size_t i = 0; i < 8; i++) { assert(read->bid[i] == written->bid[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->last_date_operation[i] == written->last_date_operation[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->maturity_date[i] == written->maturity_date[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->short_leg_instrument_identifier[i] == written->short_leg_instrument_identifier[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->long_leg_instruments_id[i] == written->long_leg_instruments_id[i]); }
  assert(read->frequency == written->frequency);
  assert(read->number_of_maturities == written->number_of_maturities);
  for (size_t i = 0; i < 20; i++) { assert(read->filler[i] == written->filler[i]); }
}

/* Catalog Sent For Instruments Belonging To The Strategy Derivative Market Message: written and read back, then read and written back */
static void check_catalog_sent_for_instruments_belonging_to_the_strategy_derivative_nw7mmt(void) {
  CatalogSentForInstrumentsBelongingToTheStrategyDerivative_nw7mmt sent;
  CatalogSentForInstrumentsBelongingToTheStrategyDerivative_nw7mmt got;
  uint8_t wire[74];
  uint8_t again[74];

  any_catalog_sent_for_instruments_belonging_to_the_strategy_derivative_nw7mmt(&sent);
  assert(encode_catalog_sent_for_instruments_belonging_to_the_strategy_derivative_nw7mmt(&sent, wire, 0) == 74);
  assert(decode_catalog_sent_for_instruments_belonging_to_the_strategy_derivative_nw7mmt(&got, wire, 0) == 74);
  equal_catalog_sent_for_instruments_belonging_to_the_strategy_derivative_nw7mmt(&got, &sent);

  for (size_t i = 0; i < 74; i++) { wire[i] = arbitrary(); }
  assert(decode_catalog_sent_for_instruments_belonging_to_the_strategy_derivative_nw7mmt(&got, wire, 0) == 74);
  assert(encode_catalog_sent_for_instruments_belonging_to_the_strategy_derivative_nw7mmt(&got, again, 0) == 74);
  for (size_t i = 0; i < 74; i++) { assert(again[i] == wire[i]); }
}

/* ---- Underlying Value On Warrants Catalog Message: 63 bytes ------------------ */

/* Underlying value on warrants catalog */
typedef struct {
  uint8_t instrument_number[4];            /* bytes 0 to 3 */
  uint8_t issuer[7];                       /* bytes 4 to 10 */
  uint8_t series[6];                       /* bytes 11 to 16 */
  uint8_t value_type[2];                   /* bytes 17 to 18 */
  uint8_t underlying_issuer[7];            /* bytes 19 to 25 */
  uint8_t underlying_series[6];            /* bytes 26 to 31 */
  uint8_t underlying_value_type[2];        /* bytes 32 to 33 */
  uint8_t number_of_registered_values[8];  /* bytes 34 to 41 */
  uint8_t exchange;                        /* byte 42 */
  uint8_t filler[20];                      /* bytes 43 to 62 */
} UnderlyingValueOnWarrantsCatalogMessage;

/* any Underlying Value On Warrants Catalog Message at all: every byte one the checker chooses */
static void any_underlying_value_on_warrants_catalog_message(UnderlyingValueOnWarrantsCatalogMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->instrument_number[i] = arbitrary(); }
  for (size_t i = 0; i < 7; i++) { record->issuer[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->series[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->value_type[i] = arbitrary(); }
  for (size_t i = 0; i < 7; i++) { record->underlying_issuer[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->underlying_series[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->underlying_value_type[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->number_of_registered_values[i] = arbitrary(); }
  record->exchange = arbitrary();
  for (size_t i = 0; i < 20; i++) { record->filler[i] = arbitrary(); }
}

/* Underlying Value On Warrants Catalog Message to the wire: 63 bytes from at, returning where the next byte goes */
static size_t encode_underlying_value_on_warrants_catalog_message(const UnderlyingValueOnWarrantsCatalogMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument_number[i]; }
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->issuer[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->series[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->value_type[i]; }
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->underlying_issuer[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->underlying_series[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->underlying_value_type[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->number_of_registered_values[i]; }
  wire[at++] = record->exchange;
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->filler[i]; }

  return at;
}

/* Underlying Value On Warrants Catalog Message off the wire: 63 bytes from at, returning where the next byte lies */
static size_t decode_underlying_value_on_warrants_catalog_message(UnderlyingValueOnWarrantsCatalogMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->instrument_number[i] = wire[at++]; }
  for (size_t i = 0; i < 7; i++) { record->issuer[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->series[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->value_type[i] = wire[at++]; }
  for (size_t i = 0; i < 7; i++) { record->underlying_issuer[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->underlying_series[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->underlying_value_type[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->number_of_registered_values[i] = wire[at++]; }
  record->exchange = wire[at++];
  for (size_t i = 0; i < 20; i++) { record->filler[i] = wire[at++]; }

  return at;
}

/* what was read of Underlying Value On Warrants Catalog Message is what was written, byte for byte */
static void equal_underlying_value_on_warrants_catalog_message(const UnderlyingValueOnWarrantsCatalogMessage *read, const UnderlyingValueOnWarrantsCatalogMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->instrument_number[i] == written->instrument_number[i]); }
  for (size_t i = 0; i < 7; i++) { assert(read->issuer[i] == written->issuer[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->series[i] == written->series[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->value_type[i] == written->value_type[i]); }
  for (size_t i = 0; i < 7; i++) { assert(read->underlying_issuer[i] == written->underlying_issuer[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->underlying_series[i] == written->underlying_series[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->underlying_value_type[i] == written->underlying_value_type[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->number_of_registered_values[i] == written->number_of_registered_values[i]); }
  assert(read->exchange == written->exchange);
  for (size_t i = 0; i < 20; i++) { assert(read->filler[i] == written->filler[i]); }
}

/* Underlying Value On Warrants Catalog Message: written and read back, then read and written back */
static void check_underlying_value_on_warrants_catalog_message(void) {
  UnderlyingValueOnWarrantsCatalogMessage sent;
  UnderlyingValueOnWarrantsCatalogMessage got;
  uint8_t wire[63];
  uint8_t again[63];

  any_underlying_value_on_warrants_catalog_message(&sent);
  assert(encode_underlying_value_on_warrants_catalog_message(&sent, wire, 0) == 63);
  assert(decode_underlying_value_on_warrants_catalog_message(&got, wire, 0) == 63);
  equal_underlying_value_on_warrants_catalog_message(&got, &sent);

  for (size_t i = 0; i < 63; i++) { wire[i] = arbitrary(); }
  assert(decode_underlying_value_on_warrants_catalog_message(&got, wire, 0) == 63);
  assert(encode_underlying_value_on_warrants_catalog_message(&got, again, 0) == 63);
  for (size_t i = 0; i < 63; i++) { assert(again[i] == wire[i]); }
}

/* ---- What esbmc checks ------------------------------------------------------- */

/* every record of the protocol, each on its own buffers */
static void checks(void) {
  check_i_n_t_r_a_multicast_header();
  check_message_header();
  check_catalog_for_instruments_belonging_to_the_local_and_global_stock_mar_gc6yau();
  check_catalog_of_instruments_that_belong_to_the_debt_metals_and_money_mark_a9x5rm();
  check_catalog_for_instruments_belonging_to_the_capital_warrants_market_message();
  check_options_futures_and_swaps_derivatives_market_instruments_catalog_message();
  check_catalog_sent_for_instruments_belonging_to_capital_tracs_message();
  check_catalog_sent_for_instruments_belonging_to_mutual_funds_message();
  check_catalog_sent_for_instruments_belonging_to_the_strategy_derivative_nw7mmt();
  check_underlying_value_on_warrants_catalog_message();
}

int main(void) {
#ifdef CONCRETE
  for (pattern = 0; pattern < 4; pattern++) { checks(); }
#else
  checks();
#endif

  return 0;
}
