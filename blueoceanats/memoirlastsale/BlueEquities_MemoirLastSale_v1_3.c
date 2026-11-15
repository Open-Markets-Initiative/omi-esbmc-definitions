// blueoceanats/memoirlastsale/BlueEquities_MemoirLastSale_v1_3.c
/*
 * Blue Ocean Technologies Member Order Information Record Last Sale
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
 *   - a length prefix framing what follows
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

/* The header every datagram opens with, naming the message type, the data session and the sequence the payload starts at */
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

/* ---- Instrument Directory Message: 35 bytes ---------------------------------- */

/* Maps a tradable security to the Security ID used in place of its ticker on every later message of the session; sent for all tradable securities at the start of the trading day */
typedef struct {
  uint8_t timestamp[8];    /* bytes 0 to 7 */
  uint8_t security_id[2];  /* bytes 8 to 9 */
  uint8_t symbol[6];       /* bytes 10 to 15 */
  uint8_t symbol_sfx[6];   /* bytes 16 to 21 */
  uint8_t round_lot[4];    /* bytes 22 to 25 */
  uint8_t is_test_symbol;  /* byte 26 */
  uint8_t mpv[8];          /* bytes 27 to 34 */
} InstrumentDirectoryMessage;

/* any Instrument Directory Message at all: every byte one the checker chooses */
static void any_instrument_directory_message(InstrumentDirectoryMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->security_id[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->symbol[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->symbol_sfx[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->round_lot[i] = arbitrary(); }
  record->is_test_symbol = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->mpv[i] = arbitrary(); }
}

/* Instrument Directory Message to the wire: 35 bytes from at, returning where the next byte goes */
static size_t encode_instrument_directory_message(const InstrumentDirectoryMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->security_id[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->symbol[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->symbol_sfx[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->round_lot[i]; }
  wire[at++] = record->is_test_symbol;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->mpv[i]; }

  return at;
}

/* Instrument Directory Message off the wire: 35 bytes from at, returning where the next byte lies */
static size_t decode_instrument_directory_message(InstrumentDirectoryMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->security_id[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->symbol[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->symbol_sfx[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->round_lot[i] = wire[at++]; }
  record->is_test_symbol = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->mpv[i] = wire[at++]; }

  return at;
}

/* what was read of Instrument Directory Message is what was written, byte for byte */
static void equal_instrument_directory_message(const InstrumentDirectoryMessage *read, const InstrumentDirectoryMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->security_id[i] == written->security_id[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->symbol[i] == written->symbol[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->symbol_sfx[i] == written->symbol_sfx[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->round_lot[i] == written->round_lot[i]); }
  assert(read->is_test_symbol == written->is_test_symbol);
  for (size_t i = 0; i < 8; i++) { assert(read->mpv[i] == written->mpv[i]); }
}

/* Instrument Directory Message: written and read back, then read and written back */
static void check_instrument_directory_message(void) {
  InstrumentDirectoryMessage sent;
  InstrumentDirectoryMessage got;
  uint8_t wire[35];
  uint8_t again[35];

  any_instrument_directory_message(&sent);
  assert(encode_instrument_directory_message(&sent, wire, 0) == 35);
  assert(decode_instrument_directory_message(&got, wire, 0) == 35);
  equal_instrument_directory_message(&got, &sent);

  for (size_t i = 0; i < 35; i++) { wire[i] = arbitrary(); }
  assert(decode_instrument_directory_message(&got, wire, 0) == 35);
  assert(encode_instrument_directory_message(&got, again, 0) == 35);
  for (size_t i = 0; i < 35; i++) { assert(again[i] == wire[i]); }
}

/* ---- Reg Sho Restriction Message: 11 bytes ----------------------------------- */

/* Indicates that a security is subject to the Rule 201 Regulation SHO short sale price restriction; may follow the Instrument Directory message when the restriction is already in effect */
typedef struct {
  uint8_t timestamp[8];            /* bytes 0 to 7 */
  uint8_t security_id[2];          /* bytes 8 to 9 */
  uint8_t short_sale_restriction;  /* byte 10 */
} RegShoRestrictionMessage;

/* any Reg Sho Restriction Message at all: every byte one the checker chooses */
static void any_reg_sho_restriction_message(RegShoRestrictionMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->security_id[i] = arbitrary(); }
  record->short_sale_restriction = arbitrary();
}

/* Reg Sho Restriction Message to the wire: 11 bytes from at, returning where the next byte goes */
static size_t encode_reg_sho_restriction_message(const RegShoRestrictionMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->security_id[i]; }
  wire[at++] = record->short_sale_restriction;

  return at;
}

/* Reg Sho Restriction Message off the wire: 11 bytes from at, returning where the next byte lies */
static size_t decode_reg_sho_restriction_message(RegShoRestrictionMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->security_id[i] = wire[at++]; }
  record->short_sale_restriction = wire[at++];

  return at;
}

/* what was read of Reg Sho Restriction Message is what was written, byte for byte */
static void equal_reg_sho_restriction_message(const RegShoRestrictionMessage *read, const RegShoRestrictionMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->security_id[i] == written->security_id[i]); }
  assert(read->short_sale_restriction == written->short_sale_restriction);
}

/* Reg Sho Restriction Message: written and read back, then read and written back */
static void check_reg_sho_restriction_message(void) {
  RegShoRestrictionMessage sent;
  RegShoRestrictionMessage got;
  uint8_t wire[11];
  uint8_t again[11];

  any_reg_sho_restriction_message(&sent);
  assert(encode_reg_sho_restriction_message(&sent, wire, 0) == 11);
  assert(decode_reg_sho_restriction_message(&got, wire, 0) == 11);
  equal_reg_sho_restriction_message(&got, &sent);

  for (size_t i = 0; i < 11; i++) { wire[i] = arbitrary(); }
  assert(decode_reg_sho_restriction_message(&got, wire, 0) == 11);
  assert(encode_reg_sho_restriction_message(&got, again, 0) == 11);
  for (size_t i = 0; i < 11; i++) { assert(again[i] == wire[i]); }
}

/* ---- Security Trading Status Message: 12 bytes ------------------------------- */

/* Current trading status of a security, halted or paused by the listing market over the Sip or by the exchange itself; assume Halted until one is received */
typedef struct {
  uint8_t timestamp[8];                    /* bytes 0 to 7 */
  uint8_t security_id[2];                  /* bytes 8 to 9 */
  uint8_t security_trading_status;         /* byte 10 */
  uint8_t security_trading_status_reason;  /* byte 11 */
} SecurityTradingStatusMessage;

/* any Security Trading Status Message at all: every byte one the checker chooses */
static void any_security_trading_status_message(SecurityTradingStatusMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->security_id[i] = arbitrary(); }
  record->security_trading_status = arbitrary();
  record->security_trading_status_reason = arbitrary();
}

/* Security Trading Status Message to the wire: 12 bytes from at, returning where the next byte goes */
static size_t encode_security_trading_status_message(const SecurityTradingStatusMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->security_id[i]; }
  wire[at++] = record->security_trading_status;
  wire[at++] = record->security_trading_status_reason;

  return at;
}

/* Security Trading Status Message off the wire: 12 bytes from at, returning where the next byte lies */
static size_t decode_security_trading_status_message(SecurityTradingStatusMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->security_id[i] = wire[at++]; }
  record->security_trading_status = wire[at++];
  record->security_trading_status_reason = wire[at++];

  return at;
}

/* what was read of Security Trading Status Message is what was written, byte for byte */
static void equal_security_trading_status_message(const SecurityTradingStatusMessage *read, const SecurityTradingStatusMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->security_id[i] == written->security_id[i]); }
  assert(read->security_trading_status == written->security_trading_status);
  assert(read->security_trading_status_reason == written->security_trading_status_reason);
}

/* Security Trading Status Message: written and read back, then read and written back */
static void check_security_trading_status_message(void) {
  SecurityTradingStatusMessage sent;
  SecurityTradingStatusMessage got;
  uint8_t wire[12];
  uint8_t again[12];

  any_security_trading_status_message(&sent);
  assert(encode_security_trading_status_message(&sent, wire, 0) == 12);
  assert(decode_security_trading_status_message(&got, wire, 0) == 12);
  equal_security_trading_status_message(&got, &sent);

  for (size_t i = 0; i < 12; i++) { wire[i] = arbitrary(); }
  assert(decode_security_trading_status_message(&got, wire, 0) == 12);
  assert(encode_security_trading_status_message(&got, again, 0) == 12);
  for (size_t i = 0; i < 12; i++) { assert(again[i] == wire[i]); }
}

/* ---- Trading Session Status Message: 9 bytes --------------------------------- */

/* The trading system has entered a new trading session */
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

/* ---- Trade Report Message: 34 bytes ------------------------------------------ */

/* An order on the book was executed in part or whole, reported with its sale conditions */
typedef struct {
  uint8_t timestamp[8];      /* bytes 0 to 7 */
  uint8_t security_id[2];    /* bytes 8 to 9 */
  uint8_t trade_id[8];       /* bytes 10 to 17 */
  uint8_t trade_qty[4];      /* bytes 18 to 21 */
  uint8_t trade_price[8];    /* bytes 22 to 29 */
  uint8_t sale_condition_1;  /* byte 30 */
  uint8_t sale_condition_2;  /* byte 31 */
  uint8_t sale_condition_3;  /* byte 32 */
  uint8_t sale_condition_4;  /* byte 33 */
} TradeReportMessage;

/* any Trade Report Message at all: every byte one the checker chooses */
static void any_trade_report_message(TradeReportMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->security_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->trade_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->trade_qty[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->trade_price[i] = arbitrary(); }
  record->sale_condition_1 = arbitrary();
  record->sale_condition_2 = arbitrary();
  record->sale_condition_3 = arbitrary();
  record->sale_condition_4 = arbitrary();
}

/* Trade Report Message to the wire: 34 bytes from at, returning where the next byte goes */
static size_t encode_trade_report_message(const TradeReportMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->security_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->trade_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->trade_qty[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->trade_price[i]; }
  wire[at++] = record->sale_condition_1;
  wire[at++] = record->sale_condition_2;
  wire[at++] = record->sale_condition_3;
  wire[at++] = record->sale_condition_4;

  return at;
}

/* Trade Report Message off the wire: 34 bytes from at, returning where the next byte lies */
static size_t decode_trade_report_message(TradeReportMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->security_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->trade_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->trade_qty[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->trade_price[i] = wire[at++]; }
  record->sale_condition_1 = wire[at++];
  record->sale_condition_2 = wire[at++];
  record->sale_condition_3 = wire[at++];
  record->sale_condition_4 = wire[at++];

  return at;
}

/* what was read of Trade Report Message is what was written, byte for byte */
static void equal_trade_report_message(const TradeReportMessage *read, const TradeReportMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->security_id[i] == written->security_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->trade_id[i] == written->trade_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->trade_qty[i] == written->trade_qty[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->trade_price[i] == written->trade_price[i]); }
  assert(read->sale_condition_1 == written->sale_condition_1);
  assert(read->sale_condition_2 == written->sale_condition_2);
  assert(read->sale_condition_3 == written->sale_condition_3);
  assert(read->sale_condition_4 == written->sale_condition_4);
}

/* Trade Report Message: written and read back, then read and written back */
static void check_trade_report_message(void) {
  TradeReportMessage sent;
  TradeReportMessage got;
  uint8_t wire[34];
  uint8_t again[34];

  any_trade_report_message(&sent);
  assert(encode_trade_report_message(&sent, wire, 0) == 34);
  assert(decode_trade_report_message(&got, wire, 0) == 34);
  equal_trade_report_message(&got, &sent);

  for (size_t i = 0; i < 34; i++) { wire[i] = arbitrary(); }
  assert(decode_trade_report_message(&got, wire, 0) == 34);
  assert(encode_trade_report_message(&got, again, 0) == 34);
  for (size_t i = 0; i < 34; i++) { assert(again[i] == wire[i]); }
}

/* ---- Trade Cancel Message: 34 bytes ------------------------------------------ */

/* The exchange busted an execution found to be clearly erroneous; a broken trade cannot be reinstated */
typedef struct {
  uint8_t timestamp[8];      /* bytes 0 to 7 */
  uint8_t security_id[2];    /* bytes 8 to 9 */
  uint8_t trade_id[8];       /* bytes 10 to 17 */
  uint8_t trade_qty[4];      /* bytes 18 to 21 */
  uint8_t last_price[8];     /* bytes 22 to 29 */
  uint8_t sale_condition_1;  /* byte 30 */
  uint8_t sale_condition_2;  /* byte 31 */
  uint8_t sale_condition_3;  /* byte 32 */
  uint8_t sale_condition_4;  /* byte 33 */
} TradeCancelMessage;

/* any Trade Cancel Message at all: every byte one the checker chooses */
static void any_trade_cancel_message(TradeCancelMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->security_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->trade_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->trade_qty[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->last_price[i] = arbitrary(); }
  record->sale_condition_1 = arbitrary();
  record->sale_condition_2 = arbitrary();
  record->sale_condition_3 = arbitrary();
  record->sale_condition_4 = arbitrary();
}

/* Trade Cancel Message to the wire: 34 bytes from at, returning where the next byte goes */
static size_t encode_trade_cancel_message(const TradeCancelMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->security_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->trade_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->trade_qty[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->last_price[i]; }
  wire[at++] = record->sale_condition_1;
  wire[at++] = record->sale_condition_2;
  wire[at++] = record->sale_condition_3;
  wire[at++] = record->sale_condition_4;

  return at;
}

/* Trade Cancel Message off the wire: 34 bytes from at, returning where the next byte lies */
static size_t decode_trade_cancel_message(TradeCancelMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->security_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->trade_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->trade_qty[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->last_price[i] = wire[at++]; }
  record->sale_condition_1 = wire[at++];
  record->sale_condition_2 = wire[at++];
  record->sale_condition_3 = wire[at++];
  record->sale_condition_4 = wire[at++];

  return at;
}

/* what was read of Trade Cancel Message is what was written, byte for byte */
static void equal_trade_cancel_message(const TradeCancelMessage *read, const TradeCancelMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->security_id[i] == written->security_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->trade_id[i] == written->trade_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->trade_qty[i] == written->trade_qty[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->last_price[i] == written->last_price[i]); }
  assert(read->sale_condition_1 == written->sale_condition_1);
  assert(read->sale_condition_2 == written->sale_condition_2);
  assert(read->sale_condition_3 == written->sale_condition_3);
  assert(read->sale_condition_4 == written->sale_condition_4);
}

/* Trade Cancel Message: written and read back, then read and written back */
static void check_trade_cancel_message(void) {
  TradeCancelMessage sent;
  TradeCancelMessage got;
  uint8_t wire[34];
  uint8_t again[34];

  any_trade_cancel_message(&sent);
  assert(encode_trade_cancel_message(&sent, wire, 0) == 34);
  assert(decode_trade_cancel_message(&got, wire, 0) == 34);
  equal_trade_cancel_message(&got, &sent);

  for (size_t i = 0; i < 34; i++) { wire[i] = arbitrary(); }
  assert(decode_trade_cancel_message(&got, wire, 0) == 34);
  assert(encode_trade_cancel_message(&got, again, 0) == 34);
  for (size_t i = 0; i < 34; i++) { assert(again[i] == wire[i]); }
}

/* ---- Trade Correct Message: 50 bytes ----------------------------------------- */

/* Trade cancellation or correction policy has altered the details of an existing trade, carrying both the original and the corrected values */
typedef struct {
  uint8_t timestamp[8];                /* bytes 0 to 7 */
  uint8_t security_id[2];              /* bytes 8 to 9 */
  uint8_t trade_id[8];                 /* bytes 10 to 17 */
  uint8_t original_trade_qty[4];       /* bytes 18 to 21 */
  uint8_t original_trade_price[8];     /* bytes 22 to 29 */
  uint8_t original_sale_condition_1;   /* byte 30 */
  uint8_t original_sale_condition_2;   /* byte 31 */
  uint8_t original_sale_condition_3;   /* byte 32 */
  uint8_t original_sale_condition_4;   /* byte 33 */
  uint8_t corrected_trade_qty[4];      /* bytes 34 to 37 */
  uint8_t corrected_trade_price[8];    /* bytes 38 to 45 */
  uint8_t corrected_sale_condition_1;  /* byte 46 */
  uint8_t corrected_sale_condition_2;  /* byte 47 */
  uint8_t corrected_sale_condition_3;  /* byte 48 */
  uint8_t corrected_sale_condition_4;  /* byte 49 */
} TradeCorrectMessage;

/* any Trade Correct Message at all: every byte one the checker chooses */
static void any_trade_correct_message(TradeCorrectMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->security_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->trade_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->original_trade_qty[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->original_trade_price[i] = arbitrary(); }
  record->original_sale_condition_1 = arbitrary();
  record->original_sale_condition_2 = arbitrary();
  record->original_sale_condition_3 = arbitrary();
  record->original_sale_condition_4 = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->corrected_trade_qty[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->corrected_trade_price[i] = arbitrary(); }
  record->corrected_sale_condition_1 = arbitrary();
  record->corrected_sale_condition_2 = arbitrary();
  record->corrected_sale_condition_3 = arbitrary();
  record->corrected_sale_condition_4 = arbitrary();
}

/* Trade Correct Message to the wire: 50 bytes from at, returning where the next byte goes */
static size_t encode_trade_correct_message(const TradeCorrectMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->security_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->trade_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->original_trade_qty[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->original_trade_price[i]; }
  wire[at++] = record->original_sale_condition_1;
  wire[at++] = record->original_sale_condition_2;
  wire[at++] = record->original_sale_condition_3;
  wire[at++] = record->original_sale_condition_4;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->corrected_trade_qty[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->corrected_trade_price[i]; }
  wire[at++] = record->corrected_sale_condition_1;
  wire[at++] = record->corrected_sale_condition_2;
  wire[at++] = record->corrected_sale_condition_3;
  wire[at++] = record->corrected_sale_condition_4;

  return at;
}

/* Trade Correct Message off the wire: 50 bytes from at, returning where the next byte lies */
static size_t decode_trade_correct_message(TradeCorrectMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->security_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->trade_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->original_trade_qty[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->original_trade_price[i] = wire[at++]; }
  record->original_sale_condition_1 = wire[at++];
  record->original_sale_condition_2 = wire[at++];
  record->original_sale_condition_3 = wire[at++];
  record->original_sale_condition_4 = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->corrected_trade_qty[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->corrected_trade_price[i] = wire[at++]; }
  record->corrected_sale_condition_1 = wire[at++];
  record->corrected_sale_condition_2 = wire[at++];
  record->corrected_sale_condition_3 = wire[at++];
  record->corrected_sale_condition_4 = wire[at++];

  return at;
}

/* what was read of Trade Correct Message is what was written, byte for byte */
static void equal_trade_correct_message(const TradeCorrectMessage *read, const TradeCorrectMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->security_id[i] == written->security_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->trade_id[i] == written->trade_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->original_trade_qty[i] == written->original_trade_qty[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->original_trade_price[i] == written->original_trade_price[i]); }
  assert(read->original_sale_condition_1 == written->original_sale_condition_1);
  assert(read->original_sale_condition_2 == written->original_sale_condition_2);
  assert(read->original_sale_condition_3 == written->original_sale_condition_3);
  assert(read->original_sale_condition_4 == written->original_sale_condition_4);
  for (size_t i = 0; i < 4; i++) { assert(read->corrected_trade_qty[i] == written->corrected_trade_qty[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->corrected_trade_price[i] == written->corrected_trade_price[i]); }
  assert(read->corrected_sale_condition_1 == written->corrected_sale_condition_1);
  assert(read->corrected_sale_condition_2 == written->corrected_sale_condition_2);
  assert(read->corrected_sale_condition_3 == written->corrected_sale_condition_3);
  assert(read->corrected_sale_condition_4 == written->corrected_sale_condition_4);
}

/* Trade Correct Message: written and read back, then read and written back */
static void check_trade_correct_message(void) {
  TradeCorrectMessage sent;
  TradeCorrectMessage got;
  uint8_t wire[50];
  uint8_t again[50];

  any_trade_correct_message(&sent);
  assert(encode_trade_correct_message(&sent, wire, 0) == 50);
  assert(decode_trade_correct_message(&got, wire, 0) == 50);
  equal_trade_correct_message(&got, &sent);

  for (size_t i = 0; i < 50; i++) { wire[i] = arbitrary(); }
  assert(decode_trade_correct_message(&got, wire, 0) == 50);
  assert(encode_trade_correct_message(&got, again, 0) == 50);
  for (size_t i = 0; i < 50; i++) { assert(again[i] == wire[i]); }
}

/* ---- What esbmc checks ------------------------------------------------------- */

/* every record of the protocol, each on its own buffers */
static void checks(void) {
  check_common_header();
  check_sbe_header();
  check_instrument_directory_message();
  check_reg_sho_restriction_message();
  check_security_trading_status_message();
  check_trading_session_status_message();
  check_trade_report_message();
  check_trade_cancel_message();
  check_trade_correct_message();
}

int main(void) {
#ifdef CONCRETE
  for (pattern = 0; pattern < 4; pattern++) { checks(); }
#else
  checks();
#endif

  return 0;
}
