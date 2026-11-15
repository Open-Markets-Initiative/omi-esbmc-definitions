// iex/iexoptions/marketdata/IexOptions_MarketData_v1_03.c
/*
 * Investors Exchange Market Data
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
 *   - a run filling what frames it
 *   - a block whose stated length holds more than its fields
 *   - a run counted by a field
 *   - a field present only on a condition
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

/* ---- Message Header: 8 bytes ------------------------------------------------- */

/* Iex Options Sbe message header — message identifiers and length of message root */
typedef struct {
  uint8_t block_length[2];  /* bytes 0 to 1 */
  uint8_t template_id[2];   /* bytes 2 to 3 */
  uint8_t schema_id[2];     /* bytes 4 to 5 */
  uint8_t version[2];       /* bytes 6 to 7 */
} MessageHeader;

/* any Message Header at all: every byte one the checker chooses */
static void any_message_header(MessageHeader *record) {
  for (size_t i = 0; i < 2; i++) { record->block_length[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->template_id[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->schema_id[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->version[i] = arbitrary(); }
}

/* Message Header to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_message_header(const MessageHeader *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->block_length[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->template_id[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->schema_id[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->version[i]; }

  return at;
}

/* Message Header off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_message_header(MessageHeader *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->block_length[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->template_id[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->schema_id[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->version[i] = wire[at++]; }

  return at;
}

/* what was read of Message Header is what was written, byte for byte */
static void equal_message_header(const MessageHeader *read, const MessageHeader *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->block_length[i] == written->block_length[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->template_id[i] == written->template_id[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->schema_id[i] == written->schema_id[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->version[i] == written->version[i]); }
}

/* Message Header: written and read back, then read and written back */
static void check_message_header(void) {
  MessageHeader sent;
  MessageHeader got;
  uint8_t wire[8];
  uint8_t again[8];

  any_message_header(&sent);
  assert(encode_message_header(&sent, wire, 0) == 8);
  assert(decode_message_header(&got, wire, 0) == 8);
  equal_message_header(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_message_header(&got, wire, 0) == 8);
  assert(encode_message_header(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Underlying Ref Data Message: 31 bytes ----------------------------------- */

/* UnderlyingRefDataMessage */
typedef struct {
  uint8_t time[8];                /* bytes 0 to 7 */
  uint8_t underlying_id[4];       /* bytes 8 to 11 */
  uint8_t underlying_symbol[16];  /* bytes 12 to 27 */
  uint8_t exchange_code;          /* byte 28 */
  uint8_t mpv_group;              /* byte 29 */
  uint8_t close_indicator;        /* byte 30 */
} UnderlyingRefDataMessage;

/* any Underlying Ref Data Message at all: every byte one the checker chooses */
static void any_underlying_ref_data_message(UnderlyingRefDataMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->time[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->underlying_id[i] = arbitrary(); }
  for (size_t i = 0; i < 16; i++) { record->underlying_symbol[i] = arbitrary(); }
  record->exchange_code = arbitrary();
  record->mpv_group = arbitrary();
  record->close_indicator = arbitrary();
}

/* Underlying Ref Data Message to the wire: 31 bytes from at, returning where the next byte goes */
static size_t encode_underlying_ref_data_message(const UnderlyingRefDataMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->time[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->underlying_id[i]; }
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->underlying_symbol[i]; }
  wire[at++] = record->exchange_code;
  wire[at++] = record->mpv_group;
  wire[at++] = record->close_indicator;

  return at;
}

/* Underlying Ref Data Message off the wire: 31 bytes from at, returning where the next byte lies */
static size_t decode_underlying_ref_data_message(UnderlyingRefDataMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->time[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->underlying_id[i] = wire[at++]; }
  for (size_t i = 0; i < 16; i++) { record->underlying_symbol[i] = wire[at++]; }
  record->exchange_code = wire[at++];
  record->mpv_group = wire[at++];
  record->close_indicator = wire[at++];

  return at;
}

/* what was read of Underlying Ref Data Message is what was written, byte for byte */
static void equal_underlying_ref_data_message(const UnderlyingRefDataMessage *read, const UnderlyingRefDataMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->time[i] == written->time[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->underlying_id[i] == written->underlying_id[i]); }
  for (size_t i = 0; i < 16; i++) { assert(read->underlying_symbol[i] == written->underlying_symbol[i]); }
  assert(read->exchange_code == written->exchange_code);
  assert(read->mpv_group == written->mpv_group);
  assert(read->close_indicator == written->close_indicator);
}

/* Underlying Ref Data Message: written and read back, then read and written back */
static void check_underlying_ref_data_message(void) {
  UnderlyingRefDataMessage sent;
  UnderlyingRefDataMessage got;
  uint8_t wire[31];
  uint8_t again[31];

  any_underlying_ref_data_message(&sent);
  assert(encode_underlying_ref_data_message(&sent, wire, 0) == 31);
  assert(decode_underlying_ref_data_message(&got, wire, 0) == 31);
  equal_underlying_ref_data_message(&got, &sent);

  for (size_t i = 0; i < 31; i++) { wire[i] = arbitrary(); }
  assert(decode_underlying_ref_data_message(&got, wire, 0) == 31);
  assert(encode_underlying_ref_data_message(&got, again, 0) == 31);
  for (size_t i = 0; i < 31; i++) { assert(again[i] == wire[i]); }
}

/* ---- Symbol Mapping Message: 68 bytes ---------------------------------------- */

/* SymbolMappingMessage */
typedef struct {
  uint8_t time[8];              /* bytes 0 to 7 */
  uint8_t instrument_id[4];     /* bytes 8 to 11 */
  uint8_t osi_symbol[32];       /* bytes 12 to 43 */
  uint8_t trading_ring;         /* byte 44 */
  uint8_t closing_only_series;  /* byte 45 */
  uint8_t underlying_id[4];     /* bytes 46 to 49 */
  uint8_t maturity_date[8];     /* bytes 50 to 57 */
  uint8_t option_type;          /* byte 58 */
  uint8_t strike_price[8];      /* bytes 59 to 66 */
  uint8_t orp_enablement;       /* byte 67 */
} SymbolMappingMessage;

/* any Symbol Mapping Message at all: every byte one the checker chooses */
static void any_symbol_mapping_message(SymbolMappingMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->time[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->instrument_id[i] = arbitrary(); }
  for (size_t i = 0; i < 32; i++) { record->osi_symbol[i] = arbitrary(); }
  record->trading_ring = arbitrary();
  record->closing_only_series = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->underlying_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->maturity_date[i] = arbitrary(); }
  record->option_type = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->strike_price[i] = arbitrary(); }
  record->orp_enablement = arbitrary();
}

/* Symbol Mapping Message to the wire: 68 bytes from at, returning where the next byte goes */
static size_t encode_symbol_mapping_message(const SymbolMappingMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->time[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument_id[i]; }
  for (size_t i = 0; i < 32; i++) { wire[at++] = record->osi_symbol[i]; }
  wire[at++] = record->trading_ring;
  wire[at++] = record->closing_only_series;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->underlying_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->maturity_date[i]; }
  wire[at++] = record->option_type;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->strike_price[i]; }
  wire[at++] = record->orp_enablement;

  return at;
}

/* Symbol Mapping Message off the wire: 68 bytes from at, returning where the next byte lies */
static size_t decode_symbol_mapping_message(SymbolMappingMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->time[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->instrument_id[i] = wire[at++]; }
  for (size_t i = 0; i < 32; i++) { record->osi_symbol[i] = wire[at++]; }
  record->trading_ring = wire[at++];
  record->closing_only_series = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->underlying_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->maturity_date[i] = wire[at++]; }
  record->option_type = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->strike_price[i] = wire[at++]; }
  record->orp_enablement = wire[at++];

  return at;
}

/* what was read of Symbol Mapping Message is what was written, byte for byte */
static void equal_symbol_mapping_message(const SymbolMappingMessage *read, const SymbolMappingMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->time[i] == written->time[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->instrument_id[i] == written->instrument_id[i]); }
  for (size_t i = 0; i < 32; i++) { assert(read->osi_symbol[i] == written->osi_symbol[i]); }
  assert(read->trading_ring == written->trading_ring);
  assert(read->closing_only_series == written->closing_only_series);
  for (size_t i = 0; i < 4; i++) { assert(read->underlying_id[i] == written->underlying_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->maturity_date[i] == written->maturity_date[i]); }
  assert(read->option_type == written->option_type);
  for (size_t i = 0; i < 8; i++) { assert(read->strike_price[i] == written->strike_price[i]); }
  assert(read->orp_enablement == written->orp_enablement);
}

/* Symbol Mapping Message: written and read back, then read and written back */
static void check_symbol_mapping_message(void) {
  SymbolMappingMessage sent;
  SymbolMappingMessage got;
  uint8_t wire[68];
  uint8_t again[68];

  any_symbol_mapping_message(&sent);
  assert(encode_symbol_mapping_message(&sent, wire, 0) == 68);
  assert(decode_symbol_mapping_message(&got, wire, 0) == 68);
  equal_symbol_mapping_message(&got, &sent);

  for (size_t i = 0; i < 68; i++) { wire[i] = arbitrary(); }
  assert(decode_symbol_mapping_message(&got, wire, 0) == 68);
  assert(encode_symbol_mapping_message(&got, again, 0) == 68);
  for (size_t i = 0; i < 68; i++) { assert(again[i] == wire[i]); }
}

/* ---- Instrument Clear Message: 12 bytes -------------------------------------- */

/* InstrumentClearMessage */
typedef struct {
  uint8_t time[8];           /* bytes 0 to 7 */
  uint8_t instrument_id[4];  /* bytes 8 to 11 */
} InstrumentClearMessage;

/* any Instrument Clear Message at all: every byte one the checker chooses */
static void any_instrument_clear_message(InstrumentClearMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->time[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->instrument_id[i] = arbitrary(); }
}

/* Instrument Clear Message to the wire: 12 bytes from at, returning where the next byte goes */
static size_t encode_instrument_clear_message(const InstrumentClearMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->time[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument_id[i]; }

  return at;
}

/* Instrument Clear Message off the wire: 12 bytes from at, returning where the next byte lies */
static size_t decode_instrument_clear_message(InstrumentClearMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->time[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->instrument_id[i] = wire[at++]; }

  return at;
}

/* what was read of Instrument Clear Message is what was written, byte for byte */
static void equal_instrument_clear_message(const InstrumentClearMessage *read, const InstrumentClearMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->time[i] == written->time[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->instrument_id[i] == written->instrument_id[i]); }
}

/* Instrument Clear Message: written and read back, then read and written back */
static void check_instrument_clear_message(void) {
  InstrumentClearMessage sent;
  InstrumentClearMessage got;
  uint8_t wire[12];
  uint8_t again[12];

  any_instrument_clear_message(&sent);
  assert(encode_instrument_clear_message(&sent, wire, 0) == 12);
  assert(decode_instrument_clear_message(&got, wire, 0) == 12);
  equal_instrument_clear_message(&got, &sent);

  for (size_t i = 0; i < 12; i++) { wire[i] = arbitrary(); }
  assert(decode_instrument_clear_message(&got, wire, 0) == 12);
  assert(encode_instrument_clear_message(&got, again, 0) == 12);
  for (size_t i = 0; i < 12; i++) { assert(again[i] == wire[i]); }
}

/* ---- Trading Status Message: 13 bytes ---------------------------------------- */

/* TradingStatusMessage */
typedef struct {
  uint8_t time[8];           /* bytes 0 to 7 */
  uint8_t instrument_id[4];  /* bytes 8 to 11 */
  uint8_t trading_status;    /* byte 12 */
} TradingStatusMessage;

/* any Trading Status Message at all: every byte one the checker chooses */
static void any_trading_status_message(TradingStatusMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->time[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->instrument_id[i] = arbitrary(); }
  record->trading_status = arbitrary();
}

/* Trading Status Message to the wire: 13 bytes from at, returning where the next byte goes */
static size_t encode_trading_status_message(const TradingStatusMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->time[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument_id[i]; }
  wire[at++] = record->trading_status;

  return at;
}

/* Trading Status Message off the wire: 13 bytes from at, returning where the next byte lies */
static size_t decode_trading_status_message(TradingStatusMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->time[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->instrument_id[i] = wire[at++]; }
  record->trading_status = wire[at++];

  return at;
}

/* what was read of Trading Status Message is what was written, byte for byte */
static void equal_trading_status_message(const TradingStatusMessage *read, const TradingStatusMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->time[i] == written->time[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->instrument_id[i] == written->instrument_id[i]); }
  assert(read->trading_status == written->trading_status);
}

/* Trading Status Message: written and read back, then read and written back */
static void check_trading_status_message(void) {
  TradingStatusMessage sent;
  TradingStatusMessage got;
  uint8_t wire[13];
  uint8_t again[13];

  any_trading_status_message(&sent);
  assert(encode_trading_status_message(&sent, wire, 0) == 13);
  assert(decode_trading_status_message(&got, wire, 0) == 13);
  equal_trading_status_message(&got, &sent);

  for (size_t i = 0; i < 13; i++) { wire[i] = arbitrary(); }
  assert(decode_trading_status_message(&got, wire, 0) == 13);
  assert(encode_trading_status_message(&got, again, 0) == 13);
  for (size_t i = 0; i < 13; i++) { assert(again[i] == wire[i]); }
}

/* ---- Options Auction Summary Message: 25 bytes ------------------------------- */

/* OptionsAuctionSummaryMessage */
typedef struct {
  uint8_t time[8];               /* bytes 0 to 7 */
  uint8_t instrument_id[4];      /* bytes 8 to 11 */
  uint8_t auction_summary_type;  /* byte 12 */
  uint8_t price[8];              /* bytes 13 to 20 */
  uint8_t contracts[4];          /* bytes 21 to 24 */
} OptionsAuctionSummaryMessage;

/* any Options Auction Summary Message at all: every byte one the checker chooses */
static void any_options_auction_summary_message(OptionsAuctionSummaryMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->time[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->instrument_id[i] = arbitrary(); }
  record->auction_summary_type = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->contracts[i] = arbitrary(); }
}

/* Options Auction Summary Message to the wire: 25 bytes from at, returning where the next byte goes */
static size_t encode_options_auction_summary_message(const OptionsAuctionSummaryMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->time[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument_id[i]; }
  wire[at++] = record->auction_summary_type;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->contracts[i]; }

  return at;
}

/* Options Auction Summary Message off the wire: 25 bytes from at, returning where the next byte lies */
static size_t decode_options_auction_summary_message(OptionsAuctionSummaryMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->time[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->instrument_id[i] = wire[at++]; }
  record->auction_summary_type = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->contracts[i] = wire[at++]; }

  return at;
}

/* what was read of Options Auction Summary Message is what was written, byte for byte */
static void equal_options_auction_summary_message(const OptionsAuctionSummaryMessage *read, const OptionsAuctionSummaryMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->time[i] == written->time[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->instrument_id[i] == written->instrument_id[i]); }
  assert(read->auction_summary_type == written->auction_summary_type);
  for (size_t i = 0; i < 8; i++) { assert(read->price[i] == written->price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->contracts[i] == written->contracts[i]); }
}

/* Options Auction Summary Message: written and read back, then read and written back */
static void check_options_auction_summary_message(void) {
  OptionsAuctionSummaryMessage sent;
  OptionsAuctionSummaryMessage got;
  uint8_t wire[25];
  uint8_t again[25];

  any_options_auction_summary_message(&sent);
  assert(encode_options_auction_summary_message(&sent, wire, 0) == 25);
  assert(decode_options_auction_summary_message(&got, wire, 0) == 25);
  equal_options_auction_summary_message(&got, &sent);

  for (size_t i = 0; i < 25; i++) { wire[i] = arbitrary(); }
  assert(decode_options_auction_summary_message(&got, wire, 0) == 25);
  assert(encode_options_auction_summary_message(&got, again, 0) == 25);
  for (size_t i = 0; i < 25; i++) { assert(again[i] == wire[i]); }
}

/* ---- Options Auction Width Update Message: 13 bytes -------------------------- */

/* OptionsAuctionWidthUpdateMessage */
typedef struct {
  uint8_t time[8];                  /* bytes 0 to 7 */
  uint8_t underlying_id[4];         /* bytes 8 to 11 */
  uint8_t quote_relief_multiplier;  /* byte 12 */
} OptionsAuctionWidthUpdateMessage;

/* any Options Auction Width Update Message at all: every byte one the checker chooses */
static void any_options_auction_width_update_message(OptionsAuctionWidthUpdateMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->time[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->underlying_id[i] = arbitrary(); }
  record->quote_relief_multiplier = arbitrary();
}

/* Options Auction Width Update Message to the wire: 13 bytes from at, returning where the next byte goes */
static size_t encode_options_auction_width_update_message(const OptionsAuctionWidthUpdateMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->time[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->underlying_id[i]; }
  wire[at++] = record->quote_relief_multiplier;

  return at;
}

/* Options Auction Width Update Message off the wire: 13 bytes from at, returning where the next byte lies */
static size_t decode_options_auction_width_update_message(OptionsAuctionWidthUpdateMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->time[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->underlying_id[i] = wire[at++]; }
  record->quote_relief_multiplier = wire[at++];

  return at;
}

/* what was read of Options Auction Width Update Message is what was written, byte for byte */
static void equal_options_auction_width_update_message(const OptionsAuctionWidthUpdateMessage *read, const OptionsAuctionWidthUpdateMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->time[i] == written->time[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->underlying_id[i] == written->underlying_id[i]); }
  assert(read->quote_relief_multiplier == written->quote_relief_multiplier);
}

/* Options Auction Width Update Message: written and read back, then read and written back */
static void check_options_auction_width_update_message(void) {
  OptionsAuctionWidthUpdateMessage sent;
  OptionsAuctionWidthUpdateMessage got;
  uint8_t wire[13];
  uint8_t again[13];

  any_options_auction_width_update_message(&sent);
  assert(encode_options_auction_width_update_message(&sent, wire, 0) == 13);
  assert(decode_options_auction_width_update_message(&got, wire, 0) == 13);
  equal_options_auction_width_update_message(&got, &sent);

  for (size_t i = 0; i < 13; i++) { wire[i] = arbitrary(); }
  assert(decode_options_auction_width_update_message(&got, wire, 0) == 13);
  assert(encode_options_auction_width_update_message(&got, again, 0) == 13);
  for (size_t i = 0; i < 13; i++) { assert(again[i] == wire[i]); }
}

/* ---- Liquidity Event Notification Message: 39 bytes -------------------------- */

/* LiquidityEventNotificationMessage */
typedef struct {
  uint8_t time[8];               /* bytes 0 to 7 */
  uint8_t instrument_id[4];      /* bytes 8 to 11 */
  uint8_t event_id[4];           /* bytes 12 to 15 */
  uint8_t liquidity_event_type;  /* byte 16 */
  uint8_t side;                  /* byte 17 */
  uint8_t price[8];              /* bytes 18 to 25 */
  uint8_t contracts[4];          /* bytes 26 to 29 */
  uint8_t capacity;              /* byte 30 */
  uint8_t participant_id[4];     /* bytes 31 to 34 */
  uint8_t event_end_offset[4];   /* bytes 35 to 38 */
} LiquidityEventNotificationMessage;

/* any Liquidity Event Notification Message at all: every byte one the checker chooses */
static void any_liquidity_event_notification_message(LiquidityEventNotificationMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->time[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->instrument_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->event_id[i] = arbitrary(); }
  record->liquidity_event_type = arbitrary();
  record->side = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->contracts[i] = arbitrary(); }
  record->capacity = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->participant_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->event_end_offset[i] = arbitrary(); }
}

/* Liquidity Event Notification Message to the wire: 39 bytes from at, returning where the next byte goes */
static size_t encode_liquidity_event_notification_message(const LiquidityEventNotificationMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->time[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->event_id[i]; }
  wire[at++] = record->liquidity_event_type;
  wire[at++] = record->side;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->contracts[i]; }
  wire[at++] = record->capacity;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->participant_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->event_end_offset[i]; }

  return at;
}

/* Liquidity Event Notification Message off the wire: 39 bytes from at, returning where the next byte lies */
static size_t decode_liquidity_event_notification_message(LiquidityEventNotificationMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->time[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->instrument_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->event_id[i] = wire[at++]; }
  record->liquidity_event_type = wire[at++];
  record->side = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->contracts[i] = wire[at++]; }
  record->capacity = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->participant_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->event_end_offset[i] = wire[at++]; }

  return at;
}

/* what was read of Liquidity Event Notification Message is what was written, byte for byte */
static void equal_liquidity_event_notification_message(const LiquidityEventNotificationMessage *read, const LiquidityEventNotificationMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->time[i] == written->time[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->instrument_id[i] == written->instrument_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->event_id[i] == written->event_id[i]); }
  assert(read->liquidity_event_type == written->liquidity_event_type);
  assert(read->side == written->side);
  for (size_t i = 0; i < 8; i++) { assert(read->price[i] == written->price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->contracts[i] == written->contracts[i]); }
  assert(read->capacity == written->capacity);
  for (size_t i = 0; i < 4; i++) { assert(read->participant_id[i] == written->participant_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->event_end_offset[i] == written->event_end_offset[i]); }
}

/* Liquidity Event Notification Message: written and read back, then read and written back */
static void check_liquidity_event_notification_message(void) {
  LiquidityEventNotificationMessage sent;
  LiquidityEventNotificationMessage got;
  uint8_t wire[39];
  uint8_t again[39];

  any_liquidity_event_notification_message(&sent);
  assert(encode_liquidity_event_notification_message(&sent, wire, 0) == 39);
  assert(decode_liquidity_event_notification_message(&got, wire, 0) == 39);
  equal_liquidity_event_notification_message(&got, &sent);

  for (size_t i = 0; i < 39; i++) { wire[i] = arbitrary(); }
  assert(decode_liquidity_event_notification_message(&got, wire, 0) == 39);
  assert(encode_liquidity_event_notification_message(&got, again, 0) == 39);
  for (size_t i = 0; i < 39; i++) { assert(again[i] == wire[i]); }
}

/* ---- Liquidity Event Execution Message: 36 bytes ----------------------------- */

/* LiquidityEventExecutionMessage */
typedef struct {
  uint8_t time[8];           /* bytes 0 to 7 */
  uint8_t instrument_id[4];  /* bytes 8 to 11 */
  uint8_t event_id[4];       /* bytes 12 to 15 */
  uint8_t trade_id[8];       /* bytes 16 to 23 */
  uint8_t price[8];          /* bytes 24 to 31 */
  uint8_t contracts[4];      /* bytes 32 to 35 */
} LiquidityEventExecutionMessage;

/* any Liquidity Event Execution Message at all: every byte one the checker chooses */
static void any_liquidity_event_execution_message(LiquidityEventExecutionMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->time[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->instrument_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->event_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->trade_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->contracts[i] = arbitrary(); }
}

/* Liquidity Event Execution Message to the wire: 36 bytes from at, returning where the next byte goes */
static size_t encode_liquidity_event_execution_message(const LiquidityEventExecutionMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->time[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->event_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->trade_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->contracts[i]; }

  return at;
}

/* Liquidity Event Execution Message off the wire: 36 bytes from at, returning where the next byte lies */
static size_t decode_liquidity_event_execution_message(LiquidityEventExecutionMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->time[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->instrument_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->event_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->trade_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->contracts[i] = wire[at++]; }

  return at;
}

/* what was read of Liquidity Event Execution Message is what was written, byte for byte */
static void equal_liquidity_event_execution_message(const LiquidityEventExecutionMessage *read, const LiquidityEventExecutionMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->time[i] == written->time[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->instrument_id[i] == written->instrument_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->event_id[i] == written->event_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->trade_id[i] == written->trade_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->price[i] == written->price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->contracts[i] == written->contracts[i]); }
}

/* Liquidity Event Execution Message: written and read back, then read and written back */
static void check_liquidity_event_execution_message(void) {
  LiquidityEventExecutionMessage sent;
  LiquidityEventExecutionMessage got;
  uint8_t wire[36];
  uint8_t again[36];

  any_liquidity_event_execution_message(&sent);
  assert(encode_liquidity_event_execution_message(&sent, wire, 0) == 36);
  assert(decode_liquidity_event_execution_message(&got, wire, 0) == 36);
  equal_liquidity_event_execution_message(&got, &sent);

  for (size_t i = 0; i < 36; i++) { wire[i] = arbitrary(); }
  assert(decode_liquidity_event_execution_message(&got, wire, 0) == 36);
  assert(encode_liquidity_event_execution_message(&got, again, 0) == 36);
  for (size_t i = 0; i < 36; i++) { assert(again[i] == wire[i]); }
}

/* ---- Liquidity Event Cancel Message: 16 bytes -------------------------------- */

/* LiquidityEventCancelMessage */
typedef struct {
  uint8_t time[8];           /* bytes 0 to 7 */
  uint8_t instrument_id[4];  /* bytes 8 to 11 */
  uint8_t event_id[4];       /* bytes 12 to 15 */
} LiquidityEventCancelMessage;

/* any Liquidity Event Cancel Message at all: every byte one the checker chooses */
static void any_liquidity_event_cancel_message(LiquidityEventCancelMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->time[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->instrument_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->event_id[i] = arbitrary(); }
}

/* Liquidity Event Cancel Message to the wire: 16 bytes from at, returning where the next byte goes */
static size_t encode_liquidity_event_cancel_message(const LiquidityEventCancelMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->time[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->event_id[i]; }

  return at;
}

/* Liquidity Event Cancel Message off the wire: 16 bytes from at, returning where the next byte lies */
static size_t decode_liquidity_event_cancel_message(LiquidityEventCancelMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->time[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->instrument_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->event_id[i] = wire[at++]; }

  return at;
}

/* what was read of Liquidity Event Cancel Message is what was written, byte for byte */
static void equal_liquidity_event_cancel_message(const LiquidityEventCancelMessage *read, const LiquidityEventCancelMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->time[i] == written->time[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->instrument_id[i] == written->instrument_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->event_id[i] == written->event_id[i]); }
}

/* Liquidity Event Cancel Message: written and read back, then read and written back */
static void check_liquidity_event_cancel_message(void) {
  LiquidityEventCancelMessage sent;
  LiquidityEventCancelMessage got;
  uint8_t wire[16];
  uint8_t again[16];

  any_liquidity_event_cancel_message(&sent);
  assert(encode_liquidity_event_cancel_message(&sent, wire, 0) == 16);
  assert(decode_liquidity_event_cancel_message(&got, wire, 0) == 16);
  equal_liquidity_event_cancel_message(&got, &sent);

  for (size_t i = 0; i < 16; i++) { wire[i] = arbitrary(); }
  assert(decode_liquidity_event_cancel_message(&got, wire, 0) == 16);
  assert(encode_liquidity_event_cancel_message(&got, again, 0) == 16);
  for (size_t i = 0; i < 16; i++) { assert(again[i] == wire[i]); }
}

/* ---- Add Order Non Customer Message: 33 bytes -------------------------------- */

/* AddOrderNonCustomerMessage */
typedef struct {
  uint8_t time[8];           /* bytes 0 to 7 */
  uint8_t instrument_id[4];  /* bytes 8 to 11 */
  uint8_t order_id[8];       /* bytes 12 to 19 */
  uint8_t side;              /* byte 20 */
  uint8_t price[8];          /* bytes 21 to 28 */
  uint8_t contracts[4];      /* bytes 29 to 32 */
} AddOrderNonCustomerMessage;

/* any Add Order Non Customer Message at all: every byte one the checker chooses */
static void any_add_order_non_customer_message(AddOrderNonCustomerMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->time[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->instrument_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = arbitrary(); }
  record->side = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->contracts[i] = arbitrary(); }
}

/* Add Order Non Customer Message to the wire: 33 bytes from at, returning where the next byte goes */
static size_t encode_add_order_non_customer_message(const AddOrderNonCustomerMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->time[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_id[i]; }
  wire[at++] = record->side;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->contracts[i]; }

  return at;
}

/* Add Order Non Customer Message off the wire: 33 bytes from at, returning where the next byte lies */
static size_t decode_add_order_non_customer_message(AddOrderNonCustomerMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->time[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->instrument_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = wire[at++]; }
  record->side = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->contracts[i] = wire[at++]; }

  return at;
}

/* what was read of Add Order Non Customer Message is what was written, byte for byte */
static void equal_add_order_non_customer_message(const AddOrderNonCustomerMessage *read, const AddOrderNonCustomerMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->time[i] == written->time[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->instrument_id[i] == written->instrument_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->order_id[i] == written->order_id[i]); }
  assert(read->side == written->side);
  for (size_t i = 0; i < 8; i++) { assert(read->price[i] == written->price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->contracts[i] == written->contracts[i]); }
}

/* Add Order Non Customer Message: written and read back, then read and written back */
static void check_add_order_non_customer_message(void) {
  AddOrderNonCustomerMessage sent;
  AddOrderNonCustomerMessage got;
  uint8_t wire[33];
  uint8_t again[33];

  any_add_order_non_customer_message(&sent);
  assert(encode_add_order_non_customer_message(&sent, wire, 0) == 33);
  assert(decode_add_order_non_customer_message(&got, wire, 0) == 33);
  equal_add_order_non_customer_message(&got, &sent);

  for (size_t i = 0; i < 33; i++) { wire[i] = arbitrary(); }
  assert(decode_add_order_non_customer_message(&got, wire, 0) == 33);
  assert(encode_add_order_non_customer_message(&got, again, 0) == 33);
  for (size_t i = 0; i < 33; i++) { assert(again[i] == wire[i]); }
}

/* ---- Add Order Customer Message: 34 bytes ------------------------------------ */

/* AddOrderCustomerMessage */
typedef struct {
  uint8_t time[8];             /* bytes 0 to 7 */
  uint8_t instrument_id[4];    /* bytes 8 to 11 */
  uint8_t order_id[8];         /* bytes 12 to 19 */
  uint8_t side;                /* byte 20 */
  uint8_t price[8];            /* bytes 21 to 28 */
  uint8_t contracts[4];        /* bytes 29 to 32 */
  uint8_t customer_indicator;  /* byte 33 */
} AddOrderCustomerMessage;

/* any Add Order Customer Message at all: every byte one the checker chooses */
static void any_add_order_customer_message(AddOrderCustomerMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->time[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->instrument_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = arbitrary(); }
  record->side = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->contracts[i] = arbitrary(); }
  record->customer_indicator = arbitrary();
}

/* Add Order Customer Message to the wire: 34 bytes from at, returning where the next byte goes */
static size_t encode_add_order_customer_message(const AddOrderCustomerMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->time[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_id[i]; }
  wire[at++] = record->side;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->contracts[i]; }
  wire[at++] = record->customer_indicator;

  return at;
}

/* Add Order Customer Message off the wire: 34 bytes from at, returning where the next byte lies */
static size_t decode_add_order_customer_message(AddOrderCustomerMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->time[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->instrument_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = wire[at++]; }
  record->side = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->contracts[i] = wire[at++]; }
  record->customer_indicator = wire[at++];

  return at;
}

/* what was read of Add Order Customer Message is what was written, byte for byte */
static void equal_add_order_customer_message(const AddOrderCustomerMessage *read, const AddOrderCustomerMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->time[i] == written->time[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->instrument_id[i] == written->instrument_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->order_id[i] == written->order_id[i]); }
  assert(read->side == written->side);
  for (size_t i = 0; i < 8; i++) { assert(read->price[i] == written->price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->contracts[i] == written->contracts[i]); }
  assert(read->customer_indicator == written->customer_indicator);
}

/* Add Order Customer Message: written and read back, then read and written back */
static void check_add_order_customer_message(void) {
  AddOrderCustomerMessage sent;
  AddOrderCustomerMessage got;
  uint8_t wire[34];
  uint8_t again[34];

  any_add_order_customer_message(&sent);
  assert(encode_add_order_customer_message(&sent, wire, 0) == 34);
  assert(decode_add_order_customer_message(&got, wire, 0) == 34);
  equal_add_order_customer_message(&got, &sent);

  for (size_t i = 0; i < 34; i++) { wire[i] = arbitrary(); }
  assert(decode_add_order_customer_message(&got, wire, 0) == 34);
  assert(encode_add_order_customer_message(&got, again, 0) == 34);
  for (size_t i = 0; i < 34; i++) { assert(again[i] == wire[i]); }
}

/* ---- Modify Order Message: 33 bytes ------------------------------------------ */

/* ModifyOrderMessage */
typedef struct {
  uint8_t time[8];           /* bytes 0 to 7 */
  uint8_t instrument_id[4];  /* bytes 8 to 11 */
  uint8_t order_id[8];       /* bytes 12 to 19 */
  uint8_t price[8];          /* bytes 20 to 27 */
  uint8_t contracts[4];      /* bytes 28 to 31 */
  uint8_t mod_flag;          /* byte 32 */
} ModifyOrderMessage;

/* any Modify Order Message at all: every byte one the checker chooses */
static void any_modify_order_message(ModifyOrderMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->time[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->instrument_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->contracts[i] = arbitrary(); }
  record->mod_flag = arbitrary();
}

/* Modify Order Message to the wire: 33 bytes from at, returning where the next byte goes */
static size_t encode_modify_order_message(const ModifyOrderMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->time[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->contracts[i]; }
  wire[at++] = record->mod_flag;

  return at;
}

/* Modify Order Message off the wire: 33 bytes from at, returning where the next byte lies */
static size_t decode_modify_order_message(ModifyOrderMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->time[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->instrument_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->contracts[i] = wire[at++]; }
  record->mod_flag = wire[at++];

  return at;
}

/* what was read of Modify Order Message is what was written, byte for byte */
static void equal_modify_order_message(const ModifyOrderMessage *read, const ModifyOrderMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->time[i] == written->time[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->instrument_id[i] == written->instrument_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->order_id[i] == written->order_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->price[i] == written->price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->contracts[i] == written->contracts[i]); }
  assert(read->mod_flag == written->mod_flag);
}

/* Modify Order Message: written and read back, then read and written back */
static void check_modify_order_message(void) {
  ModifyOrderMessage sent;
  ModifyOrderMessage got;
  uint8_t wire[33];
  uint8_t again[33];

  any_modify_order_message(&sent);
  assert(encode_modify_order_message(&sent, wire, 0) == 33);
  assert(decode_modify_order_message(&got, wire, 0) == 33);
  equal_modify_order_message(&got, &sent);

  for (size_t i = 0; i < 33; i++) { wire[i] = arbitrary(); }
  assert(decode_modify_order_message(&got, wire, 0) == 33);
  assert(encode_modify_order_message(&got, again, 0) == 33);
  for (size_t i = 0; i < 33; i++) { assert(again[i] == wire[i]); }
}

/* ---- Delete Order Message: 20 bytes ------------------------------------------ */

/* DeleteOrderMessage */
typedef struct {
  uint8_t time[8];           /* bytes 0 to 7 */
  uint8_t instrument_id[4];  /* bytes 8 to 11 */
  uint8_t order_id[8];       /* bytes 12 to 19 */
} DeleteOrderMessage;

/* any Delete Order Message at all: every byte one the checker chooses */
static void any_delete_order_message(DeleteOrderMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->time[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->instrument_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = arbitrary(); }
}

/* Delete Order Message to the wire: 20 bytes from at, returning where the next byte goes */
static size_t encode_delete_order_message(const DeleteOrderMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->time[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_id[i]; }

  return at;
}

/* Delete Order Message off the wire: 20 bytes from at, returning where the next byte lies */
static size_t decode_delete_order_message(DeleteOrderMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->time[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->instrument_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = wire[at++]; }

  return at;
}

/* what was read of Delete Order Message is what was written, byte for byte */
static void equal_delete_order_message(const DeleteOrderMessage *read, const DeleteOrderMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->time[i] == written->time[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->instrument_id[i] == written->instrument_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->order_id[i] == written->order_id[i]); }
}

/* Delete Order Message: written and read back, then read and written back */
static void check_delete_order_message(void) {
  DeleteOrderMessage sent;
  DeleteOrderMessage got;
  uint8_t wire[20];
  uint8_t again[20];

  any_delete_order_message(&sent);
  assert(encode_delete_order_message(&sent, wire, 0) == 20);
  assert(decode_delete_order_message(&got, wire, 0) == 20);
  equal_delete_order_message(&got, &sent);

  for (size_t i = 0; i < 20; i++) { wire[i] = arbitrary(); }
  assert(decode_delete_order_message(&got, wire, 0) == 20);
  assert(encode_delete_order_message(&got, again, 0) == 20);
  for (size_t i = 0; i < 20; i++) { assert(again[i] == wire[i]); }
}

/* ---- Order Execution Message: 45 bytes --------------------------------------- */

/* OrderExecutionMessage */
typedef struct {
  uint8_t time[8];                 /* bytes 0 to 7 */
  uint8_t instrument_id[4];        /* bytes 8 to 11 */
  uint8_t order_id[8];             /* bytes 12 to 19 */
  uint8_t trade_id[8];             /* bytes 20 to 27 */
  uint8_t price[8];                /* bytes 28 to 35 */
  uint8_t executed_contracts[4];   /* bytes 36 to 39 */
  uint8_t remaining_contracts[4];  /* bytes 40 to 43 */
  uint8_t trade_condition;         /* byte 44 */
} OrderExecutionMessage;

/* any Order Execution Message at all: every byte one the checker chooses */
static void any_order_execution_message(OrderExecutionMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->time[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->instrument_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->trade_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->executed_contracts[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->remaining_contracts[i] = arbitrary(); }
  record->trade_condition = arbitrary();
}

/* Order Execution Message to the wire: 45 bytes from at, returning where the next byte goes */
static size_t encode_order_execution_message(const OrderExecutionMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->time[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->trade_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->executed_contracts[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->remaining_contracts[i]; }
  wire[at++] = record->trade_condition;

  return at;
}

/* Order Execution Message off the wire: 45 bytes from at, returning where the next byte lies */
static size_t decode_order_execution_message(OrderExecutionMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->time[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->instrument_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->trade_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->executed_contracts[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->remaining_contracts[i] = wire[at++]; }
  record->trade_condition = wire[at++];

  return at;
}

/* what was read of Order Execution Message is what was written, byte for byte */
static void equal_order_execution_message(const OrderExecutionMessage *read, const OrderExecutionMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->time[i] == written->time[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->instrument_id[i] == written->instrument_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->order_id[i] == written->order_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->trade_id[i] == written->trade_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->price[i] == written->price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->executed_contracts[i] == written->executed_contracts[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->remaining_contracts[i] == written->remaining_contracts[i]); }
  assert(read->trade_condition == written->trade_condition);
}

/* Order Execution Message: written and read back, then read and written back */
static void check_order_execution_message(void) {
  OrderExecutionMessage sent;
  OrderExecutionMessage got;
  uint8_t wire[45];
  uint8_t again[45];

  any_order_execution_message(&sent);
  assert(encode_order_execution_message(&sent, wire, 0) == 45);
  assert(decode_order_execution_message(&got, wire, 0) == 45);
  equal_order_execution_message(&got, &sent);

  for (size_t i = 0; i < 45; i++) { wire[i] = arbitrary(); }
  assert(decode_order_execution_message(&got, wire, 0) == 45);
  assert(encode_order_execution_message(&got, again, 0) == 45);
  for (size_t i = 0; i < 45; i++) { assert(again[i] == wire[i]); }
}

/* ---- Deep Trade Break Message: 20 bytes -------------------------------------- */

/* DEEPTradeBreakMessage */
typedef struct {
  uint8_t time[8];           /* bytes 0 to 7 */
  uint8_t instrument_id[4];  /* bytes 8 to 11 */
  uint8_t trade_id[8];       /* bytes 12 to 19 */
} DeepTradeBreakMessage;

/* any Deep Trade Break Message at all: every byte one the checker chooses */
static void any_deep_trade_break_message(DeepTradeBreakMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->time[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->instrument_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->trade_id[i] = arbitrary(); }
}

/* Deep Trade Break Message to the wire: 20 bytes from at, returning where the next byte goes */
static size_t encode_deep_trade_break_message(const DeepTradeBreakMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->time[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->trade_id[i]; }

  return at;
}

/* Deep Trade Break Message off the wire: 20 bytes from at, returning where the next byte lies */
static size_t decode_deep_trade_break_message(DeepTradeBreakMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->time[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->instrument_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->trade_id[i] = wire[at++]; }

  return at;
}

/* what was read of Deep Trade Break Message is what was written, byte for byte */
static void equal_deep_trade_break_message(const DeepTradeBreakMessage *read, const DeepTradeBreakMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->time[i] == written->time[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->instrument_id[i] == written->instrument_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->trade_id[i] == written->trade_id[i]); }
}

/* Deep Trade Break Message: written and read back, then read and written back */
static void check_deep_trade_break_message(void) {
  DeepTradeBreakMessage sent;
  DeepTradeBreakMessage got;
  uint8_t wire[20];
  uint8_t again[20];

  any_deep_trade_break_message(&sent);
  assert(encode_deep_trade_break_message(&sent, wire, 0) == 20);
  assert(decode_deep_trade_break_message(&got, wire, 0) == 20);
  equal_deep_trade_break_message(&got, &sent);

  for (size_t i = 0; i < 20; i++) { wire[i] = arbitrary(); }
  assert(decode_deep_trade_break_message(&got, wire, 0) == 20);
  assert(encode_deep_trade_break_message(&got, again, 0) == 20);
  for (size_t i = 0; i < 20; i++) { assert(again[i] == wire[i]); }
}

/* ---- Quote Update No Customer Interest Message: 37 bytes --------------------- */

/* QuoteUpdateNoCustomerInterestMessage */
typedef struct {
  uint8_t time[8];             /* bytes 0 to 7 */
  uint8_t instrument_id[4];    /* bytes 8 to 11 */
  uint8_t bid_size[4];         /* bytes 12 to 15 */
  uint8_t bid_price[8];        /* bytes 16 to 23 */
  uint8_t ask_size[4];         /* bytes 24 to 27 */
  uint8_t ask_price[8];        /* bytes 28 to 35 */
  uint8_t status_status_type;  /* byte 36 */
} QuoteUpdateNoCustomerInterestMessage;

/* any Quote Update No Customer Interest Message at all: every byte one the checker chooses */
static void any_quote_update_no_customer_interest_message(QuoteUpdateNoCustomerInterestMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->time[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->instrument_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->bid_size[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->bid_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->ask_size[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->ask_price[i] = arbitrary(); }
  record->status_status_type = arbitrary();
}

/* Quote Update No Customer Interest Message to the wire: 37 bytes from at, returning where the next byte goes */
static size_t encode_quote_update_no_customer_interest_message(const QuoteUpdateNoCustomerInterestMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->time[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->bid_size[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->bid_price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->ask_size[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->ask_price[i]; }
  wire[at++] = record->status_status_type;

  return at;
}

/* Quote Update No Customer Interest Message off the wire: 37 bytes from at, returning where the next byte lies */
static size_t decode_quote_update_no_customer_interest_message(QuoteUpdateNoCustomerInterestMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->time[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->instrument_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->bid_size[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->bid_price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->ask_size[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->ask_price[i] = wire[at++]; }
  record->status_status_type = wire[at++];

  return at;
}

/* what was read of Quote Update No Customer Interest Message is what was written, byte for byte */
static void equal_quote_update_no_customer_interest_message(const QuoteUpdateNoCustomerInterestMessage *read, const QuoteUpdateNoCustomerInterestMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->time[i] == written->time[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->instrument_id[i] == written->instrument_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->bid_size[i] == written->bid_size[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->bid_price[i] == written->bid_price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->ask_size[i] == written->ask_size[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->ask_price[i] == written->ask_price[i]); }
  assert(read->status_status_type == written->status_status_type);
}

/* Quote Update No Customer Interest Message: written and read back, then read and written back */
static void check_quote_update_no_customer_interest_message(void) {
  QuoteUpdateNoCustomerInterestMessage sent;
  QuoteUpdateNoCustomerInterestMessage got;
  uint8_t wire[37];
  uint8_t again[37];

  any_quote_update_no_customer_interest_message(&sent);
  assert(encode_quote_update_no_customer_interest_message(&sent, wire, 0) == 37);
  assert(decode_quote_update_no_customer_interest_message(&got, wire, 0) == 37);
  equal_quote_update_no_customer_interest_message(&got, &sent);

  for (size_t i = 0; i < 37; i++) { wire[i] = arbitrary(); }
  assert(decode_quote_update_no_customer_interest_message(&got, wire, 0) == 37);
  assert(encode_quote_update_no_customer_interest_message(&got, again, 0) == 37);
  for (size_t i = 0; i < 37; i++) { assert(again[i] == wire[i]); }
}

/* ---- Quote Update Customer Interest Message: 45 bytes ------------------------ */

/* QuoteUpdateCustomerInterestMessage */
typedef struct {
  uint8_t time[8];               /* bytes 0 to 7 */
  uint8_t instrument_id[4];      /* bytes 8 to 11 */
  uint8_t bid_size[4];           /* bytes 12 to 15 */
  uint8_t bid_customer_size[4];  /* bytes 16 to 19 */
  uint8_t bid_price[8];          /* bytes 20 to 27 */
  uint8_t ask_size[4];           /* bytes 28 to 31 */
  uint8_t ask_customer_size[4];  /* bytes 32 to 35 */
  uint8_t ask_price[8];          /* bytes 36 to 43 */
  uint8_t status_status_type;    /* byte 44 */
} QuoteUpdateCustomerInterestMessage;

/* any Quote Update Customer Interest Message at all: every byte one the checker chooses */
static void any_quote_update_customer_interest_message(QuoteUpdateCustomerInterestMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->time[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->instrument_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->bid_size[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->bid_customer_size[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->bid_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->ask_size[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->ask_customer_size[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->ask_price[i] = arbitrary(); }
  record->status_status_type = arbitrary();
}

/* Quote Update Customer Interest Message to the wire: 45 bytes from at, returning where the next byte goes */
static size_t encode_quote_update_customer_interest_message(const QuoteUpdateCustomerInterestMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->time[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->bid_size[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->bid_customer_size[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->bid_price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->ask_size[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->ask_customer_size[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->ask_price[i]; }
  wire[at++] = record->status_status_type;

  return at;
}

/* Quote Update Customer Interest Message off the wire: 45 bytes from at, returning where the next byte lies */
static size_t decode_quote_update_customer_interest_message(QuoteUpdateCustomerInterestMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->time[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->instrument_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->bid_size[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->bid_customer_size[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->bid_price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->ask_size[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->ask_customer_size[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->ask_price[i] = wire[at++]; }
  record->status_status_type = wire[at++];

  return at;
}

/* what was read of Quote Update Customer Interest Message is what was written, byte for byte */
static void equal_quote_update_customer_interest_message(const QuoteUpdateCustomerInterestMessage *read, const QuoteUpdateCustomerInterestMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->time[i] == written->time[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->instrument_id[i] == written->instrument_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->bid_size[i] == written->bid_size[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->bid_customer_size[i] == written->bid_customer_size[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->bid_price[i] == written->bid_price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->ask_size[i] == written->ask_size[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->ask_customer_size[i] == written->ask_customer_size[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->ask_price[i] == written->ask_price[i]); }
  assert(read->status_status_type == written->status_status_type);
}

/* Quote Update Customer Interest Message: written and read back, then read and written back */
static void check_quote_update_customer_interest_message(void) {
  QuoteUpdateCustomerInterestMessage sent;
  QuoteUpdateCustomerInterestMessage got;
  uint8_t wire[45];
  uint8_t again[45];

  any_quote_update_customer_interest_message(&sent);
  assert(encode_quote_update_customer_interest_message(&sent, wire, 0) == 45);
  assert(decode_quote_update_customer_interest_message(&got, wire, 0) == 45);
  equal_quote_update_customer_interest_message(&got, &sent);

  for (size_t i = 0; i < 45; i++) { wire[i] = arbitrary(); }
  assert(decode_quote_update_customer_interest_message(&got, wire, 0) == 45);
  assert(encode_quote_update_customer_interest_message(&got, again, 0) == 45);
  for (size_t i = 0; i < 45; i++) { assert(again[i] == wire[i]); }
}

/* ---- Trade Message: 33 bytes ------------------------------------------------- */

/* TradeMessage */
typedef struct {
  uint8_t time[8];           /* bytes 0 to 7 */
  uint8_t instrument_id[4];  /* bytes 8 to 11 */
  uint8_t trade_id[8];       /* bytes 12 to 19 */
  uint8_t price[8];          /* bytes 20 to 27 */
  uint8_t contracts[4];      /* bytes 28 to 31 */
  uint8_t trade_condition;   /* byte 32 */
} TradeMessage;

/* any Trade Message at all: every byte one the checker chooses */
static void any_trade_message(TradeMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->time[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->instrument_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->trade_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->contracts[i] = arbitrary(); }
  record->trade_condition = arbitrary();
}

/* Trade Message to the wire: 33 bytes from at, returning where the next byte goes */
static size_t encode_trade_message(const TradeMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->time[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->trade_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->contracts[i]; }
  wire[at++] = record->trade_condition;

  return at;
}

/* Trade Message off the wire: 33 bytes from at, returning where the next byte lies */
static size_t decode_trade_message(TradeMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->time[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->instrument_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->trade_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->contracts[i] = wire[at++]; }
  record->trade_condition = wire[at++];

  return at;
}

/* what was read of Trade Message is what was written, byte for byte */
static void equal_trade_message(const TradeMessage *read, const TradeMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->time[i] == written->time[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->instrument_id[i] == written->instrument_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->trade_id[i] == written->trade_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->price[i] == written->price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->contracts[i] == written->contracts[i]); }
  assert(read->trade_condition == written->trade_condition);
}

/* Trade Message: written and read back, then read and written back */
static void check_trade_message(void) {
  TradeMessage sent;
  TradeMessage got;
  uint8_t wire[33];
  uint8_t again[33];

  any_trade_message(&sent);
  assert(encode_trade_message(&sent, wire, 0) == 33);
  assert(decode_trade_message(&got, wire, 0) == 33);
  equal_trade_message(&got, &sent);

  for (size_t i = 0; i < 33; i++) { wire[i] = arbitrary(); }
  assert(decode_trade_message(&got, wire, 0) == 33);
  assert(encode_trade_message(&got, again, 0) == 33);
  for (size_t i = 0; i < 33; i++) { assert(again[i] == wire[i]); }
}

/* ---- Trade Correction Message: 41 bytes -------------------------------------- */

/* TradeCorrectionMessage */
typedef struct {
  uint8_t time[8];               /* bytes 0 to 7 */
  uint8_t instrument_id[4];      /* bytes 8 to 11 */
  uint8_t original_trade_id[8];  /* bytes 12 to 19 */
  uint8_t trade_id[8];           /* bytes 20 to 27 */
  uint8_t price[8];              /* bytes 28 to 35 */
  uint8_t contracts[4];          /* bytes 36 to 39 */
  uint8_t trade_condition;       /* byte 40 */
} TradeCorrectionMessage;

/* any Trade Correction Message at all: every byte one the checker chooses */
static void any_trade_correction_message(TradeCorrectionMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->time[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->instrument_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->original_trade_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->trade_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->contracts[i] = arbitrary(); }
  record->trade_condition = arbitrary();
}

/* Trade Correction Message to the wire: 41 bytes from at, returning where the next byte goes */
static size_t encode_trade_correction_message(const TradeCorrectionMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->time[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->original_trade_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->trade_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->contracts[i]; }
  wire[at++] = record->trade_condition;

  return at;
}

/* Trade Correction Message off the wire: 41 bytes from at, returning where the next byte lies */
static size_t decode_trade_correction_message(TradeCorrectionMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->time[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->instrument_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->original_trade_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->trade_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->contracts[i] = wire[at++]; }
  record->trade_condition = wire[at++];

  return at;
}

/* what was read of Trade Correction Message is what was written, byte for byte */
static void equal_trade_correction_message(const TradeCorrectionMessage *read, const TradeCorrectionMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->time[i] == written->time[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->instrument_id[i] == written->instrument_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->original_trade_id[i] == written->original_trade_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->trade_id[i] == written->trade_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->price[i] == written->price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->contracts[i] == written->contracts[i]); }
  assert(read->trade_condition == written->trade_condition);
}

/* Trade Correction Message: written and read back, then read and written back */
static void check_trade_correction_message(void) {
  TradeCorrectionMessage sent;
  TradeCorrectionMessage got;
  uint8_t wire[41];
  uint8_t again[41];

  any_trade_correction_message(&sent);
  assert(encode_trade_correction_message(&sent, wire, 0) == 41);
  assert(decode_trade_correction_message(&got, wire, 0) == 41);
  equal_trade_correction_message(&got, &sent);

  for (size_t i = 0; i < 41; i++) { wire[i] = arbitrary(); }
  assert(decode_trade_correction_message(&got, wire, 0) == 41);
  assert(encode_trade_correction_message(&got, again, 0) == 41);
  for (size_t i = 0; i < 41; i++) { assert(again[i] == wire[i]); }
}

/* ---- Tops Trade Break Message: 21 bytes -------------------------------------- */

/* TOPSTradeBreakMessage */
typedef struct {
  uint8_t time[8];           /* bytes 0 to 7 */
  uint8_t instrument_id[4];  /* bytes 8 to 11 */
  uint8_t trade_id[8];       /* bytes 12 to 19 */
  uint8_t trade_condition;   /* byte 20 */
} TopsTradeBreakMessage;

/* any Tops Trade Break Message at all: every byte one the checker chooses */
static void any_tops_trade_break_message(TopsTradeBreakMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->time[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->instrument_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->trade_id[i] = arbitrary(); }
  record->trade_condition = arbitrary();
}

/* Tops Trade Break Message to the wire: 21 bytes from at, returning where the next byte goes */
static size_t encode_tops_trade_break_message(const TopsTradeBreakMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->time[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->trade_id[i]; }
  wire[at++] = record->trade_condition;

  return at;
}

/* Tops Trade Break Message off the wire: 21 bytes from at, returning where the next byte lies */
static size_t decode_tops_trade_break_message(TopsTradeBreakMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->time[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->instrument_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->trade_id[i] = wire[at++]; }
  record->trade_condition = wire[at++];

  return at;
}

/* what was read of Tops Trade Break Message is what was written, byte for byte */
static void equal_tops_trade_break_message(const TopsTradeBreakMessage *read, const TopsTradeBreakMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->time[i] == written->time[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->instrument_id[i] == written->instrument_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->trade_id[i] == written->trade_id[i]); }
  assert(read->trade_condition == written->trade_condition);
}

/* Tops Trade Break Message: written and read back, then read and written back */
static void check_tops_trade_break_message(void) {
  TopsTradeBreakMessage sent;
  TopsTradeBreakMessage got;
  uint8_t wire[21];
  uint8_t again[21];

  any_tops_trade_break_message(&sent);
  assert(encode_tops_trade_break_message(&sent, wire, 0) == 21);
  assert(decode_tops_trade_break_message(&got, wire, 0) == 21);
  equal_tops_trade_break_message(&got, &sent);

  for (size_t i = 0; i < 21; i++) { wire[i] = arbitrary(); }
  assert(decode_tops_trade_break_message(&got, wire, 0) == 21);
  assert(encode_tops_trade_break_message(&got, again, 0) == 21);
  for (size_t i = 0; i < 21; i++) { assert(again[i] == wire[i]); }
}

/* ---- Heartbeat Message: 12 bytes --------------------------------------------- */

/* HeartbeatMessage */
typedef struct {
  uint8_t channel_id[4];       /* bytes 0 to 3 */
  uint8_t sequence_number[8];  /* bytes 4 to 11 */
} HeartbeatMessage;

/* any Heartbeat Message at all: every byte one the checker chooses */
static void any_heartbeat_message(HeartbeatMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->channel_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->sequence_number[i] = arbitrary(); }
}

/* Heartbeat Message to the wire: 12 bytes from at, returning where the next byte goes */
static size_t encode_heartbeat_message(const HeartbeatMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->channel_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->sequence_number[i]; }

  return at;
}

/* Heartbeat Message off the wire: 12 bytes from at, returning where the next byte lies */
static size_t decode_heartbeat_message(HeartbeatMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->channel_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->sequence_number[i] = wire[at++]; }

  return at;
}

/* what was read of Heartbeat Message is what was written, byte for byte */
static void equal_heartbeat_message(const HeartbeatMessage *read, const HeartbeatMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->channel_id[i] == written->channel_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->sequence_number[i] == written->sequence_number[i]); }
}

/* Heartbeat Message: written and read back, then read and written back */
static void check_heartbeat_message(void) {
  HeartbeatMessage sent;
  HeartbeatMessage got;
  uint8_t wire[12];
  uint8_t again[12];

  any_heartbeat_message(&sent);
  assert(encode_heartbeat_message(&sent, wire, 0) == 12);
  assert(decode_heartbeat_message(&got, wire, 0) == 12);
  equal_heartbeat_message(&got, &sent);

  for (size_t i = 0; i < 12; i++) { wire[i] = arbitrary(); }
  assert(decode_heartbeat_message(&got, wire, 0) == 12);
  assert(encode_heartbeat_message(&got, again, 0) == 12);
  for (size_t i = 0; i < 12; i++) { assert(again[i] == wire[i]); }
}

/* ---- Message List Group Encoding: 2 bytes ------------------------------------ */

/* messageListGroupEncoding */
typedef struct {
  uint8_t block_length_short;  /* byte 0 */
  uint8_t num_in_group;        /* byte 1 */
} MessageListGroupEncoding;

/* any Message List Group Encoding at all: every byte one the checker chooses */
static void any_message_list_group_encoding(MessageListGroupEncoding *record) {
  record->block_length_short = arbitrary();
  record->num_in_group = arbitrary();
}

/* Message List Group Encoding to the wire: 2 bytes from at, returning where the next byte goes */
static size_t encode_message_list_group_encoding(const MessageListGroupEncoding *record, uint8_t *wire, size_t at) {
  wire[at++] = record->block_length_short;
  wire[at++] = record->num_in_group;

  return at;
}

/* Message List Group Encoding off the wire: 2 bytes from at, returning where the next byte lies */
static size_t decode_message_list_group_encoding(MessageListGroupEncoding *record, const uint8_t *wire, size_t at) {
  record->block_length_short = wire[at++];
  record->num_in_group = wire[at++];

  return at;
}

/* what was read of Message List Group Encoding is what was written, byte for byte */
static void equal_message_list_group_encoding(const MessageListGroupEncoding *read, const MessageListGroupEncoding *written) {
  assert(read->block_length_short == written->block_length_short);
  assert(read->num_in_group == written->num_in_group);
}

/* Message List Group Encoding: written and read back, then read and written back */
static void check_message_list_group_encoding(void) {
  MessageListGroupEncoding sent;
  MessageListGroupEncoding got;
  uint8_t wire[2];
  uint8_t again[2];

  any_message_list_group_encoding(&sent);
  assert(encode_message_list_group_encoding(&sent, wire, 0) == 2);
  assert(decode_message_list_group_encoding(&got, wire, 0) == 2);
  equal_message_list_group_encoding(&got, &sent);

  for (size_t i = 0; i < 2; i++) { wire[i] = arbitrary(); }
  assert(decode_message_list_group_encoding(&got, wire, 0) == 2);
  assert(encode_message_list_group_encoding(&got, again, 0) == 2);
  for (size_t i = 0; i < 2; i++) { assert(again[i] == wire[i]); }
}

/* ---- Session Shutdown Message: 12 bytes -------------------------------------- */

/* SessionShutdownMessage */
typedef struct {
  uint8_t channel_id[4];       /* bytes 0 to 3 */
  uint8_t sequence_number[8];  /* bytes 4 to 11 */
} SessionShutdownMessage;

/* any Session Shutdown Message at all: every byte one the checker chooses */
static void any_session_shutdown_message(SessionShutdownMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->channel_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->sequence_number[i] = arbitrary(); }
}

/* Session Shutdown Message to the wire: 12 bytes from at, returning where the next byte goes */
static size_t encode_session_shutdown_message(const SessionShutdownMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->channel_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->sequence_number[i]; }

  return at;
}

/* Session Shutdown Message off the wire: 12 bytes from at, returning where the next byte lies */
static size_t decode_session_shutdown_message(SessionShutdownMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->channel_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->sequence_number[i] = wire[at++]; }

  return at;
}

/* what was read of Session Shutdown Message is what was written, byte for byte */
static void equal_session_shutdown_message(const SessionShutdownMessage *read, const SessionShutdownMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->channel_id[i] == written->channel_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->sequence_number[i] == written->sequence_number[i]); }
}

/* Session Shutdown Message: written and read back, then read and written back */
static void check_session_shutdown_message(void) {
  SessionShutdownMessage sent;
  SessionShutdownMessage got;
  uint8_t wire[12];
  uint8_t again[12];

  any_session_shutdown_message(&sent);
  assert(encode_session_shutdown_message(&sent, wire, 0) == 12);
  assert(decode_session_shutdown_message(&got, wire, 0) == 12);
  equal_session_shutdown_message(&got, &sent);

  for (size_t i = 0; i < 12; i++) { wire[i] = arbitrary(); }
  assert(decode_session_shutdown_message(&got, wire, 0) == 12);
  assert(encode_session_shutdown_message(&got, again, 0) == 12);
  for (size_t i = 0; i < 12; i++) { assert(again[i] == wire[i]); }
}

/* ---- Retransmission Request Message: 41 bytes -------------------------------- */

/* RetransmissionRequestMessage */
typedef struct {
  uint8_t begin_sequence[8];  /* bytes 0 to 7 */
  uint8_t end_sequence[8];    /* bytes 8 to 15 */
  uint8_t logon_id[16];       /* bytes 16 to 31 */
  uint8_t request_id[4];      /* bytes 32 to 35 */
  uint8_t channel_id[4];      /* bytes 36 to 39 */
  uint8_t feed;               /* byte 40 */
} RetransmissionRequestMessage;

/* any Retransmission Request Message at all: every byte one the checker chooses */
static void any_retransmission_request_message(RetransmissionRequestMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->begin_sequence[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->end_sequence[i] = arbitrary(); }
  for (size_t i = 0; i < 16; i++) { record->logon_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->request_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->channel_id[i] = arbitrary(); }
  record->feed = arbitrary();
}

/* Retransmission Request Message to the wire: 41 bytes from at, returning where the next byte goes */
static size_t encode_retransmission_request_message(const RetransmissionRequestMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->begin_sequence[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->end_sequence[i]; }
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->logon_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->request_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->channel_id[i]; }
  wire[at++] = record->feed;

  return at;
}

/* Retransmission Request Message off the wire: 41 bytes from at, returning where the next byte lies */
static size_t decode_retransmission_request_message(RetransmissionRequestMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->begin_sequence[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->end_sequence[i] = wire[at++]; }
  for (size_t i = 0; i < 16; i++) { record->logon_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->request_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->channel_id[i] = wire[at++]; }
  record->feed = wire[at++];

  return at;
}

/* what was read of Retransmission Request Message is what was written, byte for byte */
static void equal_retransmission_request_message(const RetransmissionRequestMessage *read, const RetransmissionRequestMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->begin_sequence[i] == written->begin_sequence[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->end_sequence[i] == written->end_sequence[i]); }
  for (size_t i = 0; i < 16; i++) { assert(read->logon_id[i] == written->logon_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->request_id[i] == written->request_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->channel_id[i] == written->channel_id[i]); }
  assert(read->feed == written->feed);
}

/* Retransmission Request Message: written and read back, then read and written back */
static void check_retransmission_request_message(void) {
  RetransmissionRequestMessage sent;
  RetransmissionRequestMessage got;
  uint8_t wire[41];
  uint8_t again[41];

  any_retransmission_request_message(&sent);
  assert(encode_retransmission_request_message(&sent, wire, 0) == 41);
  assert(decode_retransmission_request_message(&got, wire, 0) == 41);
  equal_retransmission_request_message(&got, &sent);

  for (size_t i = 0; i < 41; i++) { wire[i] = arbitrary(); }
  assert(decode_retransmission_request_message(&got, wire, 0) == 41);
  assert(encode_retransmission_request_message(&got, again, 0) == 41);
  for (size_t i = 0; i < 41; i++) { assert(again[i] == wire[i]); }
}

/* ---- Retransmission Response Message: 26 bytes ------------------------------- */

/* RetransmissionResponseMessage */
typedef struct {
  uint8_t logon_id[16];                       /* bytes 0 to 15 */
  uint8_t request_id[4];                      /* bytes 16 to 19 */
  uint8_t channel_id[4];                      /* bytes 20 to 23 */
  uint8_t feed;                               /* byte 24 */
  uint8_t status_retransmission_status_type;  /* byte 25 */
} RetransmissionResponseMessage;

/* any Retransmission Response Message at all: every byte one the checker chooses */
static void any_retransmission_response_message(RetransmissionResponseMessage *record) {
  for (size_t i = 0; i < 16; i++) { record->logon_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->request_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->channel_id[i] = arbitrary(); }
  record->feed = arbitrary();
  record->status_retransmission_status_type = arbitrary();
}

/* Retransmission Response Message to the wire: 26 bytes from at, returning where the next byte goes */
static size_t encode_retransmission_response_message(const RetransmissionResponseMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->logon_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->request_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->channel_id[i]; }
  wire[at++] = record->feed;
  wire[at++] = record->status_retransmission_status_type;

  return at;
}

/* Retransmission Response Message off the wire: 26 bytes from at, returning where the next byte lies */
static size_t decode_retransmission_response_message(RetransmissionResponseMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 16; i++) { record->logon_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->request_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->channel_id[i] = wire[at++]; }
  record->feed = wire[at++];
  record->status_retransmission_status_type = wire[at++];

  return at;
}

/* what was read of Retransmission Response Message is what was written, byte for byte */
static void equal_retransmission_response_message(const RetransmissionResponseMessage *read, const RetransmissionResponseMessage *written) {
  for (size_t i = 0; i < 16; i++) { assert(read->logon_id[i] == written->logon_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->request_id[i] == written->request_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->channel_id[i] == written->channel_id[i]); }
  assert(read->feed == written->feed);
  assert(read->status_retransmission_status_type == written->status_retransmission_status_type);
}

/* Retransmission Response Message: written and read back, then read and written back */
static void check_retransmission_response_message(void) {
  RetransmissionResponseMessage sent;
  RetransmissionResponseMessage got;
  uint8_t wire[26];
  uint8_t again[26];

  any_retransmission_response_message(&sent);
  assert(encode_retransmission_response_message(&sent, wire, 0) == 26);
  assert(decode_retransmission_response_message(&got, wire, 0) == 26);
  equal_retransmission_response_message(&got, &sent);

  for (size_t i = 0; i < 26; i++) { wire[i] = arbitrary(); }
  assert(decode_retransmission_response_message(&got, wire, 0) == 26);
  assert(encode_retransmission_response_message(&got, again, 0) == 26);
  for (size_t i = 0; i < 26; i++) { assert(again[i] == wire[i]); }
}

/* ---- Snapshot Header Message: 20 bytes --------------------------------------- */

/* SnapshotHeaderMessage */
typedef struct {
  uint8_t snapshot_id[4];            /* bytes 0 to 3 */
  uint8_t current_packet_number[4];  /* bytes 4 to 7 */
  uint8_t total_packet_count[4];     /* bytes 8 to 11 */
  uint8_t as_of_sequence_number[8];  /* bytes 12 to 19 */
} SnapshotHeaderMessage;

/* any Snapshot Header Message at all: every byte one the checker chooses */
static void any_snapshot_header_message(SnapshotHeaderMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->snapshot_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->current_packet_number[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->total_packet_count[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->as_of_sequence_number[i] = arbitrary(); }
}

/* Snapshot Header Message to the wire: 20 bytes from at, returning where the next byte goes */
static size_t encode_snapshot_header_message(const SnapshotHeaderMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->snapshot_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->current_packet_number[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->total_packet_count[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->as_of_sequence_number[i]; }

  return at;
}

/* Snapshot Header Message off the wire: 20 bytes from at, returning where the next byte lies */
static size_t decode_snapshot_header_message(SnapshotHeaderMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->snapshot_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->current_packet_number[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->total_packet_count[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->as_of_sequence_number[i] = wire[at++]; }

  return at;
}

/* what was read of Snapshot Header Message is what was written, byte for byte */
static void equal_snapshot_header_message(const SnapshotHeaderMessage *read, const SnapshotHeaderMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->snapshot_id[i] == written->snapshot_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->current_packet_number[i] == written->current_packet_number[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->total_packet_count[i] == written->total_packet_count[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->as_of_sequence_number[i] == written->as_of_sequence_number[i]); }
}

/* Snapshot Header Message: written and read back, then read and written back */
static void check_snapshot_header_message(void) {
  SnapshotHeaderMessage sent;
  SnapshotHeaderMessage got;
  uint8_t wire[20];
  uint8_t again[20];

  any_snapshot_header_message(&sent);
  assert(encode_snapshot_header_message(&sent, wire, 0) == 20);
  assert(decode_snapshot_header_message(&got, wire, 0) == 20);
  equal_snapshot_header_message(&got, &sent);

  for (size_t i = 0; i < 20; i++) { wire[i] = arbitrary(); }
  assert(decode_snapshot_header_message(&got, wire, 0) == 20);
  assert(encode_snapshot_header_message(&got, again, 0) == 20);
  for (size_t i = 0; i < 20; i++) { assert(again[i] == wire[i]); }
}

/* ---- What esbmc checks ------------------------------------------------------- */

/* every record of the protocol, each on its own buffers */
static void checks(void) {
  check_message_header();
  check_underlying_ref_data_message();
  check_symbol_mapping_message();
  check_instrument_clear_message();
  check_trading_status_message();
  check_options_auction_summary_message();
  check_options_auction_width_update_message();
  check_liquidity_event_notification_message();
  check_liquidity_event_execution_message();
  check_liquidity_event_cancel_message();
  check_add_order_non_customer_message();
  check_add_order_customer_message();
  check_modify_order_message();
  check_delete_order_message();
  check_order_execution_message();
  check_deep_trade_break_message();
  check_quote_update_no_customer_interest_message();
  check_quote_update_customer_interest_message();
  check_trade_message();
  check_trade_correction_message();
  check_tops_trade_break_message();
  check_heartbeat_message();
  check_message_list_group_encoding();
  check_session_shutdown_message();
  check_retransmission_request_message();
  check_retransmission_response_message();
  check_snapshot_header_message();
}

int main(void) {
#ifdef CONCRETE
  for (pattern = 0; pattern < 4; pattern++) { checks(); }
#else
  checks();
#endif

  return 0;
}
