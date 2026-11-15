// memx/memxoptions/memoirdepth/MemxOptions_MemoirDepth_v1_3.c
/*
 * The Members Exchange Member Order Information Record Depth
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
 *   - a run counted by a field
 *   - a field read in bits
 *   - a block whose stated length holds more than its fields
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

/* ---- Common Header: 18 bytes ------------------------------------------------- */

/* Common Header */
typedef struct {
  uint8_t message_type;        /* byte 0 */
  uint8_t header_length;       /* byte 1 */
  uint8_t session_id[8];       /* bytes 2 to 9 */
  uint8_t sequence_number[8];  /* bytes 10 to 17 */
} CommonHeader;

/* any Common Header at all: every byte one the checker chooses */
static void any_common_header(CommonHeader *record) {
  record->message_type = arbitrary();
  record->header_length = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->session_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->sequence_number[i] = arbitrary(); }
}

/* Common Header to the wire: 18 bytes from at, returning where the next byte goes */
static size_t encode_common_header(const CommonHeader *record, uint8_t *wire, size_t at) {
  wire[at++] = record->message_type;
  wire[at++] = record->header_length;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->session_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->sequence_number[i]; }

  return at;
}

/* Common Header off the wire: 18 bytes from at, returning where the next byte lies */
static size_t decode_common_header(CommonHeader *record, const uint8_t *wire, size_t at) {
  record->message_type = wire[at++];
  record->header_length = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->session_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->sequence_number[i] = wire[at++]; }

  return at;
}

/* what was read of Common Header is what was written, byte for byte */
static void equal_common_header(const CommonHeader *read, const CommonHeader *written) {
  assert(read->message_type == written->message_type);
  assert(read->header_length == written->header_length);
  for (size_t i = 0; i < 8; i++) { assert(read->session_id[i] == written->session_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->sequence_number[i] == written->sequence_number[i]); }
}

/* Common Header: written and read back, then read and written back */
static void check_common_header(void) {
  CommonHeader sent;
  CommonHeader got;
  uint8_t wire[18];
  uint8_t again[18];

  any_common_header(&sent);
  assert(encode_common_header(&sent, wire, 0) == 18);
  assert(decode_common_header(&got, wire, 0) == 18);
  equal_common_header(&got, &sent);

  for (size_t i = 0; i < 18; i++) { wire[i] = arbitrary(); }
  assert(decode_common_header(&got, wire, 0) == 18);
  assert(encode_common_header(&got, again, 0) == 18);
  for (size_t i = 0; i < 18; i++) { assert(again[i] == wire[i]); }
}

/* ---- Sbe Header: 6 bytes ----------------------------------------------------- */

/* Sbe Header */
typedef struct {
  uint8_t block_length[2];  /* bytes 0 to 1 */
  uint8_t template_id;      /* byte 2 */
  uint8_t schema_id;        /* byte 3 */
  uint8_t version[2];       /* bytes 4 to 5 */
} SbeHeader;

/* any Sbe Header at all: every byte one the checker chooses */
static void any_sbe_header(SbeHeader *record) {
  for (size_t i = 0; i < 2; i++) { record->block_length[i] = arbitrary(); }
  record->template_id = arbitrary();
  record->schema_id = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->version[i] = arbitrary(); }
}

/* Sbe Header to the wire: 6 bytes from at, returning where the next byte goes */
static size_t encode_sbe_header(const SbeHeader *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->block_length[i]; }
  wire[at++] = record->template_id;
  wire[at++] = record->schema_id;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->version[i]; }

  return at;
}

/* Sbe Header off the wire: 6 bytes from at, returning where the next byte lies */
static size_t decode_sbe_header(SbeHeader *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->block_length[i] = wire[at++]; }
  record->template_id = wire[at++];
  record->schema_id = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->version[i] = wire[at++]; }

  return at;
}

/* what was read of Sbe Header is what was written, byte for byte */
static void equal_sbe_header(const SbeHeader *read, const SbeHeader *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->block_length[i] == written->block_length[i]); }
  assert(read->template_id == written->template_id);
  assert(read->schema_id == written->schema_id);
  for (size_t i = 0; i < 2; i++) { assert(read->version[i] == written->version[i]); }
}

/* Sbe Header: written and read back, then read and written back */
static void check_sbe_header(void) {
  SbeHeader sent;
  SbeHeader got;
  uint8_t wire[6];
  uint8_t again[6];

  any_sbe_header(&sent);
  assert(encode_sbe_header(&sent, wire, 0) == 6);
  assert(decode_sbe_header(&got, wire, 0) == 6);
  equal_sbe_header(&got, &sent);

  for (size_t i = 0; i < 6; i++) { wire[i] = arbitrary(); }
  assert(decode_sbe_header(&got, wire, 0) == 6);
  assert(encode_sbe_header(&got, again, 0) == 6);
  for (size_t i = 0; i < 6; i++) { assert(again[i] == wire[i]); }
}

/* ---- Instrument Directory Message: 56 bytes ---------------------------------- */

/* InstrumentDirectoryMessage */
typedef struct {
  uint8_t timestamp[8];          /* bytes 0 to 7 */
  uint8_t symbol[8];             /* bytes 8 to 15 */
  uint8_t options_product_type;  /* byte 16 */
  uint8_t underlier[6];          /* bytes 17 to 22 */
  uint8_t osi_root[6];           /* bytes 23 to 28 */
  uint8_t maturity_date[8];      /* bytes 29 to 36 */
  uint8_t strike_put_or_call;    /* byte 37 */
  uint8_t strike_price[8];       /* bytes 38 to 45 */
  uint8_t closing_only;          /* byte 46 */
  uint8_t closing_time[8];       /* bytes 47 to 54 */
  uint8_t is_test_symbol;        /* byte 55 */
} InstrumentDirectoryMessage;

/* any Instrument Directory Message at all: every byte one the checker chooses */
static void any_instrument_directory_message(InstrumentDirectoryMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->symbol[i] = arbitrary(); }
  record->options_product_type = arbitrary();
  for (size_t i = 0; i < 6; i++) { record->underlier[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->osi_root[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->maturity_date[i] = arbitrary(); }
  record->strike_put_or_call = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->strike_price[i] = arbitrary(); }
  record->closing_only = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->closing_time[i] = arbitrary(); }
  record->is_test_symbol = arbitrary();
}

/* Instrument Directory Message to the wire: 56 bytes from at, returning where the next byte goes */
static size_t encode_instrument_directory_message(const InstrumentDirectoryMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->symbol[i]; }
  wire[at++] = record->options_product_type;
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->underlier[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->osi_root[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->maturity_date[i]; }
  wire[at++] = record->strike_put_or_call;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->strike_price[i]; }
  wire[at++] = record->closing_only;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->closing_time[i]; }
  wire[at++] = record->is_test_symbol;

  return at;
}

/* Instrument Directory Message off the wire: 56 bytes from at, returning where the next byte lies */
static size_t decode_instrument_directory_message(InstrumentDirectoryMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->symbol[i] = wire[at++]; }
  record->options_product_type = wire[at++];
  for (size_t i = 0; i < 6; i++) { record->underlier[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->osi_root[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->maturity_date[i] = wire[at++]; }
  record->strike_put_or_call = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->strike_price[i] = wire[at++]; }
  record->closing_only = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->closing_time[i] = wire[at++]; }
  record->is_test_symbol = wire[at++];

  return at;
}

/* what was read of Instrument Directory Message is what was written, byte for byte */
static void equal_instrument_directory_message(const InstrumentDirectoryMessage *read, const InstrumentDirectoryMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->symbol[i] == written->symbol[i]); }
  assert(read->options_product_type == written->options_product_type);
  for (size_t i = 0; i < 6; i++) { assert(read->underlier[i] == written->underlier[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->osi_root[i] == written->osi_root[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->maturity_date[i] == written->maturity_date[i]); }
  assert(read->strike_put_or_call == written->strike_put_or_call);
  for (size_t i = 0; i < 8; i++) { assert(read->strike_price[i] == written->strike_price[i]); }
  assert(read->closing_only == written->closing_only);
  for (size_t i = 0; i < 8; i++) { assert(read->closing_time[i] == written->closing_time[i]); }
  assert(read->is_test_symbol == written->is_test_symbol);
}

/* Instrument Directory Message: written and read back, then read and written back */
static void check_instrument_directory_message(void) {
  InstrumentDirectoryMessage sent;
  InstrumentDirectoryMessage got;
  uint8_t wire[56];
  uint8_t again[56];

  any_instrument_directory_message(&sent);
  assert(encode_instrument_directory_message(&sent, wire, 0) == 56);
  assert(decode_instrument_directory_message(&got, wire, 0) == 56);
  equal_instrument_directory_message(&got, &sent);

  for (size_t i = 0; i < 56; i++) { wire[i] = arbitrary(); }
  assert(decode_instrument_directory_message(&got, wire, 0) == 56);
  assert(encode_instrument_directory_message(&got, again, 0) == 56);
  for (size_t i = 0; i < 56; i++) { assert(again[i] == wire[i]); }
}

/* ---- Instrument Trading Status Message: 18 bytes ----------------------------- */

/* InstrumentTradingStatusMessage */
typedef struct {
  uint8_t timestamp[8];                      /* bytes 0 to 7 */
  uint8_t symbol[8];                         /* bytes 8 to 15 */
  uint8_t instrument_trading_status;         /* byte 16 */
  uint8_t instrument_trading_status_reason;  /* byte 17 */
} InstrumentTradingStatusMessage;

/* any Instrument Trading Status Message at all: every byte one the checker chooses */
static void any_instrument_trading_status_message(InstrumentTradingStatusMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->symbol[i] = arbitrary(); }
  record->instrument_trading_status = arbitrary();
  record->instrument_trading_status_reason = arbitrary();
}

/* Instrument Trading Status Message to the wire: 18 bytes from at, returning where the next byte goes */
static size_t encode_instrument_trading_status_message(const InstrumentTradingStatusMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->symbol[i]; }
  wire[at++] = record->instrument_trading_status;
  wire[at++] = record->instrument_trading_status_reason;

  return at;
}

/* Instrument Trading Status Message off the wire: 18 bytes from at, returning where the next byte lies */
static size_t decode_instrument_trading_status_message(InstrumentTradingStatusMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->symbol[i] = wire[at++]; }
  record->instrument_trading_status = wire[at++];
  record->instrument_trading_status_reason = wire[at++];

  return at;
}

/* what was read of Instrument Trading Status Message is what was written, byte for byte */
static void equal_instrument_trading_status_message(const InstrumentTradingStatusMessage *read, const InstrumentTradingStatusMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->symbol[i] == written->symbol[i]); }
  assert(read->instrument_trading_status == written->instrument_trading_status);
  assert(read->instrument_trading_status_reason == written->instrument_trading_status_reason);
}

/* Instrument Trading Status Message: written and read back, then read and written back */
static void check_instrument_trading_status_message(void) {
  InstrumentTradingStatusMessage sent;
  InstrumentTradingStatusMessage got;
  uint8_t wire[18];
  uint8_t again[18];

  any_instrument_trading_status_message(&sent);
  assert(encode_instrument_trading_status_message(&sent, wire, 0) == 18);
  assert(decode_instrument_trading_status_message(&got, wire, 0) == 18);
  equal_instrument_trading_status_message(&got, &sent);

  for (size_t i = 0; i < 18; i++) { wire[i] = arbitrary(); }
  assert(decode_instrument_trading_status_message(&got, wire, 0) == 18);
  assert(encode_instrument_trading_status_message(&got, again, 0) == 18);
  for (size_t i = 0; i < 18; i++) { assert(again[i] == wire[i]); }
}

/* ---- Trading Session Status Message: 9 bytes --------------------------------- */

/* TradingSessionStatusMessage */
typedef struct {
  uint8_t timestamp[8];     /* bytes 0 to 7 */
  uint8_t trading_session;  /* byte 8 */
} TradingSessionStatusMessage;

/* any Trading Session Status Message at all: every byte one the checker chooses */
static void any_trading_session_status_message(TradingSessionStatusMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
  record->trading_session = arbitrary();
}

/* Trading Session Status Message to the wire: 9 bytes from at, returning where the next byte goes */
static size_t encode_trading_session_status_message(const TradingSessionStatusMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }
  wire[at++] = record->trading_session;

  return at;
}

/* Trading Session Status Message off the wire: 9 bytes from at, returning where the next byte lies */
static size_t decode_trading_session_status_message(TradingSessionStatusMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }
  record->trading_session = wire[at++];

  return at;
}

/* what was read of Trading Session Status Message is what was written, byte for byte */
static void equal_trading_session_status_message(const TradingSessionStatusMessage *read, const TradingSessionStatusMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  assert(read->trading_session == written->trading_session);
}

/* Trading Session Status Message: written and read back, then read and written back */
static void check_trading_session_status_message(void) {
  TradingSessionStatusMessage sent;
  TradingSessionStatusMessage got;
  uint8_t wire[9];
  uint8_t again[9];

  any_trading_session_status_message(&sent);
  assert(encode_trading_session_status_message(&sent, wire, 0) == 9);
  assert(decode_trading_session_status_message(&got, wire, 0) == 9);
  equal_trading_session_status_message(&got, &sent);

  for (size_t i = 0; i < 9; i++) { wire[i] = arbitrary(); }
  assert(decode_trading_session_status_message(&got, wire, 0) == 9);
  assert(encode_trading_session_status_message(&got, again, 0) == 9);
  for (size_t i = 0; i < 9; i++) { assert(again[i] == wire[i]); }
}

/* ---- Broken Trade Message: 36 bytes ------------------------------------------ */

/* BrokenTradeMessage */
typedef struct {
  uint8_t timestamp[8];          /* bytes 0 to 7 */
  uint8_t symbol[8];             /* bytes 8 to 15 */
  uint8_t trade_id[8];           /* bytes 16 to 23 */
  uint8_t original_quantity[4];  /* bytes 24 to 27 */
  uint8_t original_price[8];     /* bytes 28 to 35 */
} BrokenTradeMessage;

/* any Broken Trade Message at all: every byte one the checker chooses */
static void any_broken_trade_message(BrokenTradeMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->symbol[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->trade_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->original_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->original_price[i] = arbitrary(); }
}

/* Broken Trade Message to the wire: 36 bytes from at, returning where the next byte goes */
static size_t encode_broken_trade_message(const BrokenTradeMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->symbol[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->trade_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->original_quantity[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->original_price[i]; }

  return at;
}

/* Broken Trade Message off the wire: 36 bytes from at, returning where the next byte lies */
static size_t decode_broken_trade_message(BrokenTradeMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->symbol[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->trade_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->original_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->original_price[i] = wire[at++]; }

  return at;
}

/* what was read of Broken Trade Message is what was written, byte for byte */
static void equal_broken_trade_message(const BrokenTradeMessage *read, const BrokenTradeMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->symbol[i] == written->symbol[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->trade_id[i] == written->trade_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->original_quantity[i] == written->original_quantity[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->original_price[i] == written->original_price[i]); }
}

/* Broken Trade Message: written and read back, then read and written back */
static void check_broken_trade_message(void) {
  BrokenTradeMessage sent;
  BrokenTradeMessage got;
  uint8_t wire[36];
  uint8_t again[36];

  any_broken_trade_message(&sent);
  assert(encode_broken_trade_message(&sent, wire, 0) == 36);
  assert(decode_broken_trade_message(&got, wire, 0) == 36);
  equal_broken_trade_message(&got, &sent);

  for (size_t i = 0; i < 36; i++) { wire[i] = arbitrary(); }
  assert(decode_broken_trade_message(&got, wire, 0) == 36);
  assert(encode_broken_trade_message(&got, again, 0) == 36);
  for (size_t i = 0; i < 36; i++) { assert(again[i] == wire[i]); }
}

/* ---- Corrected Trade Message: 48 bytes --------------------------------------- */

/* CorrectedTradeMessage */
typedef struct {
  uint8_t timestamp[8];           /* bytes 0 to 7 */
  uint8_t symbol[8];              /* bytes 8 to 15 */
  uint8_t trade_id[8];            /* bytes 16 to 23 */
  uint8_t original_quantity[4];   /* bytes 24 to 27 */
  uint8_t original_price[8];      /* bytes 28 to 35 */
  uint8_t corrected_quantity[4];  /* bytes 36 to 39 */
  uint8_t corrected_price[8];     /* bytes 40 to 47 */
} CorrectedTradeMessage;

/* any Corrected Trade Message at all: every byte one the checker chooses */
static void any_corrected_trade_message(CorrectedTradeMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->symbol[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->trade_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->original_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->original_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->corrected_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->corrected_price[i] = arbitrary(); }
}

/* Corrected Trade Message to the wire: 48 bytes from at, returning where the next byte goes */
static size_t encode_corrected_trade_message(const CorrectedTradeMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->symbol[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->trade_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->original_quantity[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->original_price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->corrected_quantity[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->corrected_price[i]; }

  return at;
}

/* Corrected Trade Message off the wire: 48 bytes from at, returning where the next byte lies */
static size_t decode_corrected_trade_message(CorrectedTradeMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->symbol[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->trade_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->original_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->original_price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->corrected_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->corrected_price[i] = wire[at++]; }

  return at;
}

/* what was read of Corrected Trade Message is what was written, byte for byte */
static void equal_corrected_trade_message(const CorrectedTradeMessage *read, const CorrectedTradeMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->symbol[i] == written->symbol[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->trade_id[i] == written->trade_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->original_quantity[i] == written->original_quantity[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->original_price[i] == written->original_price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->corrected_quantity[i] == written->corrected_quantity[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->corrected_price[i] == written->corrected_price[i]); }
}

/* Corrected Trade Message: written and read back, then read and written back */
static void check_corrected_trade_message(void) {
  CorrectedTradeMessage sent;
  CorrectedTradeMessage got;
  uint8_t wire[48];
  uint8_t again[48];

  any_corrected_trade_message(&sent);
  assert(encode_corrected_trade_message(&sent, wire, 0) == 48);
  assert(decode_corrected_trade_message(&got, wire, 0) == 48);
  equal_corrected_trade_message(&got, &sent);

  for (size_t i = 0; i < 48; i++) { wire[i] = arbitrary(); }
  assert(decode_corrected_trade_message(&got, wire, 0) == 48);
  assert(encode_corrected_trade_message(&got, again, 0) == 48);
  for (size_t i = 0; i < 48; i++) { assert(again[i] == wire[i]); }
}

/* ---- Snapshot Complete Message: 16 bytes ------------------------------------- */

/* SnapshotCompleteMessage */
typedef struct {
  uint8_t timestamp[8];              /* bytes 0 to 7 */
  uint8_t as_of_sequence_number[8];  /* bytes 8 to 15 */
} SnapshotCompleteMessage;

/* any Snapshot Complete Message at all: every byte one the checker chooses */
static void any_snapshot_complete_message(SnapshotCompleteMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->as_of_sequence_number[i] = arbitrary(); }
}

/* Snapshot Complete Message to the wire: 16 bytes from at, returning where the next byte goes */
static size_t encode_snapshot_complete_message(const SnapshotCompleteMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->as_of_sequence_number[i]; }

  return at;
}

/* Snapshot Complete Message off the wire: 16 bytes from at, returning where the next byte lies */
static size_t decode_snapshot_complete_message(SnapshotCompleteMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->as_of_sequence_number[i] = wire[at++]; }

  return at;
}

/* what was read of Snapshot Complete Message is what was written, byte for byte */
static void equal_snapshot_complete_message(const SnapshotCompleteMessage *read, const SnapshotCompleteMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->as_of_sequence_number[i] == written->as_of_sequence_number[i]); }
}

/* Snapshot Complete Message: written and read back, then read and written back */
static void check_snapshot_complete_message(void) {
  SnapshotCompleteMessage sent;
  SnapshotCompleteMessage got;
  uint8_t wire[16];
  uint8_t again[16];

  any_snapshot_complete_message(&sent);
  assert(encode_snapshot_complete_message(&sent, wire, 0) == 16);
  assert(decode_snapshot_complete_message(&got, wire, 0) == 16);
  equal_snapshot_complete_message(&got, &sent);

  for (size_t i = 0; i < 16; i++) { wire[i] = arbitrary(); }
  assert(decode_snapshot_complete_message(&got, wire, 0) == 16);
  assert(encode_snapshot_complete_message(&got, again, 0) == 16);
  for (size_t i = 0; i < 16; i++) { assert(again[i] == wire[i]); }
}

/* ---- Order Added Short Message: 29 bytes ------------------------------------- */

/* OrderAddedShortMessage */
typedef struct {
  uint8_t timestamp[8];       /* bytes 0 to 7 */
  uint8_t symbol[8];          /* bytes 8 to 15 */
  uint8_t order_id[8];        /* bytes 16 to 23 */
  uint8_t side;               /* byte 24 */
  uint8_t quantity_short[2];  /* bytes 25 to 26 */
  uint8_t price_short[2];     /* bytes 27 to 28 */
} OrderAddedShortMessage;

/* any Order Added Short Message at all: every byte one the checker chooses */
static void any_order_added_short_message(OrderAddedShortMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->symbol[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = arbitrary(); }
  record->side = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->quantity_short[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->price_short[i] = arbitrary(); }
}

/* Order Added Short Message to the wire: 29 bytes from at, returning where the next byte goes */
static size_t encode_order_added_short_message(const OrderAddedShortMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->symbol[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_id[i]; }
  wire[at++] = record->side;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->quantity_short[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->price_short[i]; }

  return at;
}

/* Order Added Short Message off the wire: 29 bytes from at, returning where the next byte lies */
static size_t decode_order_added_short_message(OrderAddedShortMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->symbol[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = wire[at++]; }
  record->side = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->quantity_short[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->price_short[i] = wire[at++]; }

  return at;
}

/* what was read of Order Added Short Message is what was written, byte for byte */
static void equal_order_added_short_message(const OrderAddedShortMessage *read, const OrderAddedShortMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->symbol[i] == written->symbol[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->order_id[i] == written->order_id[i]); }
  assert(read->side == written->side);
  for (size_t i = 0; i < 2; i++) { assert(read->quantity_short[i] == written->quantity_short[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->price_short[i] == written->price_short[i]); }
}

/* Order Added Short Message: written and read back, then read and written back */
static void check_order_added_short_message(void) {
  OrderAddedShortMessage sent;
  OrderAddedShortMessage got;
  uint8_t wire[29];
  uint8_t again[29];

  any_order_added_short_message(&sent);
  assert(encode_order_added_short_message(&sent, wire, 0) == 29);
  assert(decode_order_added_short_message(&got, wire, 0) == 29);
  equal_order_added_short_message(&got, &sent);

  for (size_t i = 0; i < 29; i++) { wire[i] = arbitrary(); }
  assert(decode_order_added_short_message(&got, wire, 0) == 29);
  assert(encode_order_added_short_message(&got, again, 0) == 29);
  for (size_t i = 0; i < 29; i++) { assert(again[i] == wire[i]); }
}

/* ---- Order Added Long Message: 37 bytes -------------------------------------- */

/* OrderAddedLongMessage */
typedef struct {
  uint8_t timestamp[8];  /* bytes 0 to 7 */
  uint8_t symbol[8];     /* bytes 8 to 15 */
  uint8_t order_id[8];   /* bytes 16 to 23 */
  uint8_t side;          /* byte 24 */
  uint8_t quantity[4];   /* bytes 25 to 28 */
  uint8_t price[8];      /* bytes 29 to 36 */
} OrderAddedLongMessage;

/* any Order Added Long Message at all: every byte one the checker chooses */
static void any_order_added_long_message(OrderAddedLongMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->symbol[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = arbitrary(); }
  record->side = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->price[i] = arbitrary(); }
}

/* Order Added Long Message to the wire: 37 bytes from at, returning where the next byte goes */
static size_t encode_order_added_long_message(const OrderAddedLongMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->symbol[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_id[i]; }
  wire[at++] = record->side;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->quantity[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price[i]; }

  return at;
}

/* Order Added Long Message off the wire: 37 bytes from at, returning where the next byte lies */
static size_t decode_order_added_long_message(OrderAddedLongMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->symbol[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = wire[at++]; }
  record->side = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->price[i] = wire[at++]; }

  return at;
}

/* what was read of Order Added Long Message is what was written, byte for byte */
static void equal_order_added_long_message(const OrderAddedLongMessage *read, const OrderAddedLongMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->symbol[i] == written->symbol[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->order_id[i] == written->order_id[i]); }
  assert(read->side == written->side);
  for (size_t i = 0; i < 4; i++) { assert(read->quantity[i] == written->quantity[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->price[i] == written->price[i]); }
}

/* Order Added Long Message: written and read back, then read and written back */
static void check_order_added_long_message(void) {
  OrderAddedLongMessage sent;
  OrderAddedLongMessage got;
  uint8_t wire[37];
  uint8_t again[37];

  any_order_added_long_message(&sent);
  assert(encode_order_added_long_message(&sent, wire, 0) == 37);
  assert(decode_order_added_long_message(&got, wire, 0) == 37);
  equal_order_added_long_message(&got, &sent);

  for (size_t i = 0; i < 37; i++) { wire[i] = arbitrary(); }
  assert(decode_order_added_long_message(&got, wire, 0) == 37);
  assert(encode_order_added_long_message(&got, again, 0) == 37);
  for (size_t i = 0; i < 37; i++) { assert(again[i] == wire[i]); }
}

/* ---- Order Added Extended Message: 38 bytes ---------------------------------- */

/* OrderAddedExtendedMessage */
typedef struct {
  uint8_t timestamp[8];    /* bytes 0 to 7 */
  uint8_t symbol[8];       /* bytes 8 to 15 */
  uint8_t order_capacity;  /* byte 16 */
  uint8_t order_id[8];     /* bytes 17 to 24 */
  uint8_t side;            /* byte 25 */
  uint8_t quantity[4];     /* bytes 26 to 29 */
  uint8_t price[8];        /* bytes 30 to 37 */
} OrderAddedExtendedMessage;

/* any Order Added Extended Message at all: every byte one the checker chooses */
static void any_order_added_extended_message(OrderAddedExtendedMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->symbol[i] = arbitrary(); }
  record->order_capacity = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = arbitrary(); }
  record->side = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->price[i] = arbitrary(); }
}

/* Order Added Extended Message to the wire: 38 bytes from at, returning where the next byte goes */
static size_t encode_order_added_extended_message(const OrderAddedExtendedMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->symbol[i]; }
  wire[at++] = record->order_capacity;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_id[i]; }
  wire[at++] = record->side;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->quantity[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price[i]; }

  return at;
}

/* Order Added Extended Message off the wire: 38 bytes from at, returning where the next byte lies */
static size_t decode_order_added_extended_message(OrderAddedExtendedMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->symbol[i] = wire[at++]; }
  record->order_capacity = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = wire[at++]; }
  record->side = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->price[i] = wire[at++]; }

  return at;
}

/* what was read of Order Added Extended Message is what was written, byte for byte */
static void equal_order_added_extended_message(const OrderAddedExtendedMessage *read, const OrderAddedExtendedMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->symbol[i] == written->symbol[i]); }
  assert(read->order_capacity == written->order_capacity);
  for (size_t i = 0; i < 8; i++) { assert(read->order_id[i] == written->order_id[i]); }
  assert(read->side == written->side);
  for (size_t i = 0; i < 4; i++) { assert(read->quantity[i] == written->quantity[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->price[i] == written->price[i]); }
}

/* Order Added Extended Message: written and read back, then read and written back */
static void check_order_added_extended_message(void) {
  OrderAddedExtendedMessage sent;
  OrderAddedExtendedMessage got;
  uint8_t wire[38];
  uint8_t again[38];

  any_order_added_extended_message(&sent);
  assert(encode_order_added_extended_message(&sent, wire, 0) == 38);
  assert(decode_order_added_extended_message(&got, wire, 0) == 38);
  equal_order_added_extended_message(&got, &sent);

  for (size_t i = 0; i < 38; i++) { wire[i] = arbitrary(); }
  assert(decode_order_added_extended_message(&got, wire, 0) == 38);
  assert(encode_order_added_extended_message(&got, again, 0) == 38);
  for (size_t i = 0; i < 38; i++) { assert(again[i] == wire[i]); }
}

/* ---- Order Deleted Message: 25 bytes ----------------------------------------- */

/* OrderDeletedMessage */
typedef struct {
  uint8_t timestamp[8];    /* bytes 0 to 7 */
  uint8_t symbol[8];       /* bytes 8 to 15 */
  uint8_t order_capacity;  /* byte 16 */
  uint8_t order_id[8];     /* bytes 17 to 24 */
} OrderDeletedMessage;

/* any Order Deleted Message at all: every byte one the checker chooses */
static void any_order_deleted_message(OrderDeletedMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->symbol[i] = arbitrary(); }
  record->order_capacity = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = arbitrary(); }
}

/* Order Deleted Message to the wire: 25 bytes from at, returning where the next byte goes */
static size_t encode_order_deleted_message(const OrderDeletedMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->symbol[i]; }
  wire[at++] = record->order_capacity;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_id[i]; }

  return at;
}

/* Order Deleted Message off the wire: 25 bytes from at, returning where the next byte lies */
static size_t decode_order_deleted_message(OrderDeletedMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->symbol[i] = wire[at++]; }
  record->order_capacity = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = wire[at++]; }

  return at;
}

/* what was read of Order Deleted Message is what was written, byte for byte */
static void equal_order_deleted_message(const OrderDeletedMessage *read, const OrderDeletedMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->symbol[i] == written->symbol[i]); }
  assert(read->order_capacity == written->order_capacity);
  for (size_t i = 0; i < 8; i++) { assert(read->order_id[i] == written->order_id[i]); }
}

/* Order Deleted Message: written and read back, then read and written back */
static void check_order_deleted_message(void) {
  OrderDeletedMessage sent;
  OrderDeletedMessage got;
  uint8_t wire[25];
  uint8_t again[25];

  any_order_deleted_message(&sent);
  assert(encode_order_deleted_message(&sent, wire, 0) == 25);
  assert(decode_order_deleted_message(&got, wire, 0) == 25);
  equal_order_deleted_message(&got, &sent);

  for (size_t i = 0; i < 25; i++) { wire[i] = arbitrary(); }
  assert(decode_order_deleted_message(&got, wire, 0) == 25);
  assert(encode_order_deleted_message(&got, again, 0) == 25);
  for (size_t i = 0; i < 25; i++) { assert(again[i] == wire[i]); }
}

/* ---- Order Reduced Message: 42 bytes ----------------------------------------- */

/* OrderReducedMessage */
typedef struct {
  uint8_t timestamp[8];         /* bytes 0 to 7 */
  uint8_t symbol[8];            /* bytes 8 to 15 */
  uint8_t order_capacity;       /* byte 16 */
  uint8_t order_id[8];          /* bytes 17 to 24 */
  uint8_t side;                 /* byte 25 */
  uint8_t quantity[4];          /* bytes 26 to 29 */
  uint8_t price[8];             /* bytes 30 to 37 */
  uint8_t quantity_reduced[4];  /* bytes 38 to 41 */
} OrderReducedMessage;

/* any Order Reduced Message at all: every byte one the checker chooses */
static void any_order_reduced_message(OrderReducedMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->symbol[i] = arbitrary(); }
  record->order_capacity = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = arbitrary(); }
  record->side = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->quantity_reduced[i] = arbitrary(); }
}

/* Order Reduced Message to the wire: 42 bytes from at, returning where the next byte goes */
static size_t encode_order_reduced_message(const OrderReducedMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->symbol[i]; }
  wire[at++] = record->order_capacity;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_id[i]; }
  wire[at++] = record->side;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->quantity[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->quantity_reduced[i]; }

  return at;
}

/* Order Reduced Message off the wire: 42 bytes from at, returning where the next byte lies */
static size_t decode_order_reduced_message(OrderReducedMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->symbol[i] = wire[at++]; }
  record->order_capacity = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = wire[at++]; }
  record->side = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->quantity_reduced[i] = wire[at++]; }

  return at;
}

/* what was read of Order Reduced Message is what was written, byte for byte */
static void equal_order_reduced_message(const OrderReducedMessage *read, const OrderReducedMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->symbol[i] == written->symbol[i]); }
  assert(read->order_capacity == written->order_capacity);
  for (size_t i = 0; i < 8; i++) { assert(read->order_id[i] == written->order_id[i]); }
  assert(read->side == written->side);
  for (size_t i = 0; i < 4; i++) { assert(read->quantity[i] == written->quantity[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->price[i] == written->price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->quantity_reduced[i] == written->quantity_reduced[i]); }
}

/* Order Reduced Message: written and read back, then read and written back */
static void check_order_reduced_message(void) {
  OrderReducedMessage sent;
  OrderReducedMessage got;
  uint8_t wire[42];
  uint8_t again[42];

  any_order_reduced_message(&sent);
  assert(encode_order_reduced_message(&sent, wire, 0) == 42);
  assert(decode_order_reduced_message(&got, wire, 0) == 42);
  equal_order_reduced_message(&got, &sent);

  for (size_t i = 0; i < 42; i++) { wire[i] = arbitrary(); }
  assert(decode_order_reduced_message(&got, wire, 0) == 42);
  assert(encode_order_reduced_message(&got, again, 0) == 42);
  for (size_t i = 0; i < 42; i++) { assert(again[i] == wire[i]); }
}

/* ---- Clear Book Message: 16 bytes -------------------------------------------- */

/* ClearBookMessage */
typedef struct {
  uint8_t timestamp[8];  /* bytes 0 to 7 */
  uint8_t symbol[8];     /* bytes 8 to 15 */
} ClearBookMessage;

/* any Clear Book Message at all: every byte one the checker chooses */
static void any_clear_book_message(ClearBookMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->symbol[i] = arbitrary(); }
}

/* Clear Book Message to the wire: 16 bytes from at, returning where the next byte goes */
static size_t encode_clear_book_message(const ClearBookMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->symbol[i]; }

  return at;
}

/* Clear Book Message off the wire: 16 bytes from at, returning where the next byte lies */
static size_t decode_clear_book_message(ClearBookMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->symbol[i] = wire[at++]; }

  return at;
}

/* what was read of Clear Book Message is what was written, byte for byte */
static void equal_clear_book_message(const ClearBookMessage *read, const ClearBookMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->symbol[i] == written->symbol[i]); }
}

/* Clear Book Message: written and read back, then read and written back */
static void check_clear_book_message(void) {
  ClearBookMessage sent;
  ClearBookMessage got;
  uint8_t wire[16];
  uint8_t again[16];

  any_clear_book_message(&sent);
  assert(encode_clear_book_message(&sent, wire, 0) == 16);
  assert(decode_clear_book_message(&got, wire, 0) == 16);
  equal_clear_book_message(&got, &sent);

  for (size_t i = 0; i < 16; i++) { wire[i] = arbitrary(); }
  assert(decode_clear_book_message(&got, wire, 0) == 16);
  assert(encode_clear_book_message(&got, again, 0) == 16);
  for (size_t i = 0; i < 16; i++) { assert(again[i] == wire[i]); }
}

/* ---- What esbmc checks ------------------------------------------------------- */

/* every record of the protocol, each on its own buffers */
static void checks(void) {
  check_common_header();
  check_sbe_header();
  check_instrument_directory_message();
  check_instrument_trading_status_message();
  check_trading_session_status_message();
  check_broken_trade_message();
  check_corrected_trade_message();
  check_snapshot_complete_message();
  check_order_added_short_message();
  check_order_added_long_message();
  check_order_added_extended_message();
  check_order_deleted_message();
  check_order_reduced_message();
  check_clear_book_message();
}

int main(void) {
#ifdef CONCRETE
  for (pattern = 0; pattern < 4; pattern++) { checks(); }
#else
  checks();
#endif

  return 0;
}
