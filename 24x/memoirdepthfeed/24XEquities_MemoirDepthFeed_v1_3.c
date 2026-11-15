// 24x/memoirdepthfeed/24XEquities_MemoirDepthFeed_v1_3.c
/*
 * 24 National Exchange Member Order Information Record Depth Feed
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

/* Memx Udp Common Header */
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

/* ---- Instrument Directory Message: 36 bytes ---------------------------------- */

/* InstrumentDirectoryMessage */
typedef struct {
  uint8_t timestamp[8];    /* bytes 0 to 7 */
  uint8_t security_id[2];  /* bytes 8 to 9 */
  uint8_t symbol[6];       /* bytes 10 to 15 */
  uint8_t symbol_sfx[6];   /* bytes 16 to 21 */
  uint8_t round_lot[4];    /* bytes 22 to 25 */
  uint8_t reserved;        /* byte 26 */
  uint8_t is_test_symbol;  /* byte 27 */
  uint8_t mpv[8];          /* bytes 28 to 35 */
} InstrumentDirectoryMessage;

/* any Instrument Directory Message at all: every byte one the checker chooses */
static void any_instrument_directory_message(InstrumentDirectoryMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->security_id[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->symbol[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->symbol_sfx[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->round_lot[i] = arbitrary(); }
  record->reserved = arbitrary();
  record->is_test_symbol = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->mpv[i] = arbitrary(); }
}

/* Instrument Directory Message to the wire: 36 bytes from at, returning where the next byte goes */
static size_t encode_instrument_directory_message(const InstrumentDirectoryMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->security_id[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->symbol[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->symbol_sfx[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->round_lot[i]; }
  wire[at++] = record->reserved;
  wire[at++] = record->is_test_symbol;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->mpv[i]; }

  return at;
}

/* Instrument Directory Message off the wire: 36 bytes from at, returning where the next byte lies */
static size_t decode_instrument_directory_message(InstrumentDirectoryMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->security_id[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->symbol[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->symbol_sfx[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->round_lot[i] = wire[at++]; }
  record->reserved = wire[at++];
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
  assert(read->reserved == written->reserved);
  assert(read->is_test_symbol == written->is_test_symbol);
  for (size_t i = 0; i < 8; i++) { assert(read->mpv[i] == written->mpv[i]); }
}

/* Instrument Directory Message: written and read back, then read and written back */
static void check_instrument_directory_message(void) {
  InstrumentDirectoryMessage sent;
  InstrumentDirectoryMessage got;
  uint8_t wire[36];
  uint8_t again[36];

  any_instrument_directory_message(&sent);
  assert(encode_instrument_directory_message(&sent, wire, 0) == 36);
  assert(decode_instrument_directory_message(&got, wire, 0) == 36);
  equal_instrument_directory_message(&got, &sent);

  for (size_t i = 0; i < 36; i++) { wire[i] = arbitrary(); }
  assert(decode_instrument_directory_message(&got, wire, 0) == 36);
  assert(encode_instrument_directory_message(&got, again, 0) == 36);
  for (size_t i = 0; i < 36; i++) { assert(again[i] == wire[i]); }
}

/* ---- Reg Sho Restriction Message: 11 bytes ----------------------------------- */

/* RegSHORestrictionMessage */
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

/* SecurityTradingStatusMessage */
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

/* ---- Order Added Message: 31 bytes ------------------------------------------- */

/* OrderAddedMessage */
typedef struct {
  uint8_t timestamp[8];    /* bytes 0 to 7 */
  uint8_t security_id[2];  /* bytes 8 to 9 */
  uint8_t order_id[8];     /* bytes 10 to 17 */
  uint8_t side;            /* byte 18 */
  uint8_t quantity[4];     /* bytes 19 to 22 */
  uint8_t price[8];        /* bytes 23 to 30 */
} OrderAddedMessage;

/* any Order Added Message at all: every byte one the checker chooses */
static void any_order_added_message(OrderAddedMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->security_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = arbitrary(); }
  record->side = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->price[i] = arbitrary(); }
}

/* Order Added Message to the wire: 31 bytes from at, returning where the next byte goes */
static size_t encode_order_added_message(const OrderAddedMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->security_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_id[i]; }
  wire[at++] = record->side;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->quantity[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price[i]; }

  return at;
}

/* Order Added Message off the wire: 31 bytes from at, returning where the next byte lies */
static size_t decode_order_added_message(OrderAddedMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->security_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = wire[at++]; }
  record->side = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->price[i] = wire[at++]; }

  return at;
}

/* what was read of Order Added Message is what was written, byte for byte */
static void equal_order_added_message(const OrderAddedMessage *read, const OrderAddedMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->security_id[i] == written->security_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->order_id[i] == written->order_id[i]); }
  assert(read->side == written->side);
  for (size_t i = 0; i < 4; i++) { assert(read->quantity[i] == written->quantity[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->price[i] == written->price[i]); }
}

/* Order Added Message: written and read back, then read and written back */
static void check_order_added_message(void) {
  OrderAddedMessage sent;
  OrderAddedMessage got;
  uint8_t wire[31];
  uint8_t again[31];

  any_order_added_message(&sent);
  assert(encode_order_added_message(&sent, wire, 0) == 31);
  assert(decode_order_added_message(&got, wire, 0) == 31);
  equal_order_added_message(&got, &sent);

  for (size_t i = 0; i < 31; i++) { wire[i] = arbitrary(); }
  assert(decode_order_added_message(&got, wire, 0) == 31);
  assert(encode_order_added_message(&got, again, 0) == 31);
  for (size_t i = 0; i < 31; i++) { assert(again[i] == wire[i]); }
}

/* ---- Order Deleted Message: 18 bytes ----------------------------------------- */

/* OrderDeletedMessage */
typedef struct {
  uint8_t timestamp[8];    /* bytes 0 to 7 */
  uint8_t security_id[2];  /* bytes 8 to 9 */
  uint8_t order_id[8];     /* bytes 10 to 17 */
} OrderDeletedMessage;

/* any Order Deleted Message at all: every byte one the checker chooses */
static void any_order_deleted_message(OrderDeletedMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->security_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = arbitrary(); }
}

/* Order Deleted Message to the wire: 18 bytes from at, returning where the next byte goes */
static size_t encode_order_deleted_message(const OrderDeletedMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->security_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_id[i]; }

  return at;
}

/* Order Deleted Message off the wire: 18 bytes from at, returning where the next byte lies */
static size_t decode_order_deleted_message(OrderDeletedMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->security_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = wire[at++]; }

  return at;
}

/* what was read of Order Deleted Message is what was written, byte for byte */
static void equal_order_deleted_message(const OrderDeletedMessage *read, const OrderDeletedMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->security_id[i] == written->security_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->order_id[i] == written->order_id[i]); }
}

/* Order Deleted Message: written and read back, then read and written back */
static void check_order_deleted_message(void) {
  OrderDeletedMessage sent;
  OrderDeletedMessage got;
  uint8_t wire[18];
  uint8_t again[18];

  any_order_deleted_message(&sent);
  assert(encode_order_deleted_message(&sent, wire, 0) == 18);
  assert(decode_order_deleted_message(&got, wire, 0) == 18);
  equal_order_deleted_message(&got, &sent);

  for (size_t i = 0; i < 18; i++) { wire[i] = arbitrary(); }
  assert(decode_order_deleted_message(&got, wire, 0) == 18);
  assert(encode_order_deleted_message(&got, again, 0) == 18);
  for (size_t i = 0; i < 18; i++) { assert(again[i] == wire[i]); }
}

/* ---- Order Reduced Message: 22 bytes ----------------------------------------- */

/* OrderReducedMessage */
typedef struct {
  uint8_t timestamp[8];    /* bytes 0 to 7 */
  uint8_t security_id[2];  /* bytes 8 to 9 */
  uint8_t order_id[8];     /* bytes 10 to 17 */
  uint8_t quantity[4];     /* bytes 18 to 21 */
} OrderReducedMessage;

/* any Order Reduced Message at all: every byte one the checker chooses */
static void any_order_reduced_message(OrderReducedMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->security_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->quantity[i] = arbitrary(); }
}

/* Order Reduced Message to the wire: 22 bytes from at, returning where the next byte goes */
static size_t encode_order_reduced_message(const OrderReducedMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->security_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->quantity[i]; }

  return at;
}

/* Order Reduced Message off the wire: 22 bytes from at, returning where the next byte lies */
static size_t decode_order_reduced_message(OrderReducedMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->security_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->quantity[i] = wire[at++]; }

  return at;
}

/* what was read of Order Reduced Message is what was written, byte for byte */
static void equal_order_reduced_message(const OrderReducedMessage *read, const OrderReducedMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->security_id[i] == written->security_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->order_id[i] == written->order_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->quantity[i] == written->quantity[i]); }
}

/* Order Reduced Message: written and read back, then read and written back */
static void check_order_reduced_message(void) {
  OrderReducedMessage sent;
  OrderReducedMessage got;
  uint8_t wire[22];
  uint8_t again[22];

  any_order_reduced_message(&sent);
  assert(encode_order_reduced_message(&sent, wire, 0) == 22);
  assert(decode_order_reduced_message(&got, wire, 0) == 22);
  equal_order_reduced_message(&got, &sent);

  for (size_t i = 0; i < 22; i++) { wire[i] = arbitrary(); }
  assert(decode_order_reduced_message(&got, wire, 0) == 22);
  assert(encode_order_reduced_message(&got, again, 0) == 22);
  for (size_t i = 0; i < 22; i++) { assert(again[i] == wire[i]); }
}

/* ---- Order Executed Message: 38 bytes ---------------------------------------- */

/* OrderExecutedMessage */
typedef struct {
  uint8_t timestamp[8];    /* bytes 0 to 7 */
  uint8_t security_id[2];  /* bytes 8 to 9 */
  uint8_t order_id[8];     /* bytes 10 to 17 */
  uint8_t trade_id[8];     /* bytes 18 to 25 */
  uint8_t quantity[4];     /* bytes 26 to 29 */
  uint8_t price[8];        /* bytes 30 to 37 */
} OrderExecutedMessage;

/* any Order Executed Message at all: every byte one the checker chooses */
static void any_order_executed_message(OrderExecutedMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->security_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->trade_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->price[i] = arbitrary(); }
}

/* Order Executed Message to the wire: 38 bytes from at, returning where the next byte goes */
static size_t encode_order_executed_message(const OrderExecutedMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->security_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->trade_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->quantity[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price[i]; }

  return at;
}

/* Order Executed Message off the wire: 38 bytes from at, returning where the next byte lies */
static size_t decode_order_executed_message(OrderExecutedMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->security_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->trade_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->price[i] = wire[at++]; }

  return at;
}

/* what was read of Order Executed Message is what was written, byte for byte */
static void equal_order_executed_message(const OrderExecutedMessage *read, const OrderExecutedMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->security_id[i] == written->security_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->order_id[i] == written->order_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->trade_id[i] == written->trade_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->quantity[i] == written->quantity[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->price[i] == written->price[i]); }
}

/* Order Executed Message: written and read back, then read and written back */
static void check_order_executed_message(void) {
  OrderExecutedMessage sent;
  OrderExecutedMessage got;
  uint8_t wire[38];
  uint8_t again[38];

  any_order_executed_message(&sent);
  assert(encode_order_executed_message(&sent, wire, 0) == 38);
  assert(decode_order_executed_message(&got, wire, 0) == 38);
  equal_order_executed_message(&got, &sent);

  for (size_t i = 0; i < 38; i++) { wire[i] = arbitrary(); }
  assert(decode_order_executed_message(&got, wire, 0) == 38);
  assert(encode_order_executed_message(&got, again, 0) == 38);
  for (size_t i = 0; i < 38; i++) { assert(again[i] == wire[i]); }
}

/* ---- Trade Message: 30 bytes ------------------------------------------------- */

/* TradeMessage */
typedef struct {
  uint8_t timestamp[8];    /* bytes 0 to 7 */
  uint8_t security_id[2];  /* bytes 8 to 9 */
  uint8_t trade_id[8];     /* bytes 10 to 17 */
  uint8_t quantity[4];     /* bytes 18 to 21 */
  uint8_t price[8];        /* bytes 22 to 29 */
} TradeMessage;

/* any Trade Message at all: every byte one the checker chooses */
static void any_trade_message(TradeMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->security_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->trade_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->price[i] = arbitrary(); }
}

/* Trade Message to the wire: 30 bytes from at, returning where the next byte goes */
static size_t encode_trade_message(const TradeMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->security_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->trade_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->quantity[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price[i]; }

  return at;
}

/* Trade Message off the wire: 30 bytes from at, returning where the next byte lies */
static size_t decode_trade_message(TradeMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->security_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->trade_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->price[i] = wire[at++]; }

  return at;
}

/* what was read of Trade Message is what was written, byte for byte */
static void equal_trade_message(const TradeMessage *read, const TradeMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->security_id[i] == written->security_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->trade_id[i] == written->trade_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->quantity[i] == written->quantity[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->price[i] == written->price[i]); }
}

/* Trade Message: written and read back, then read and written back */
static void check_trade_message(void) {
  TradeMessage sent;
  TradeMessage got;
  uint8_t wire[30];
  uint8_t again[30];

  any_trade_message(&sent);
  assert(encode_trade_message(&sent, wire, 0) == 30);
  assert(decode_trade_message(&got, wire, 0) == 30);
  equal_trade_message(&got, &sent);

  for (size_t i = 0; i < 30; i++) { wire[i] = arbitrary(); }
  assert(decode_trade_message(&got, wire, 0) == 30);
  assert(encode_trade_message(&got, again, 0) == 30);
  for (size_t i = 0; i < 30; i++) { assert(again[i] == wire[i]); }
}

/* ---- Broken Trade Message: 30 bytes ------------------------------------------ */

/* BrokenTradeMessage */
typedef struct {
  uint8_t timestamp[8];          /* bytes 0 to 7 */
  uint8_t security_id[2];        /* bytes 8 to 9 */
  uint8_t trade_id[8];           /* bytes 10 to 17 */
  uint8_t original_quantity[4];  /* bytes 18 to 21 */
  uint8_t original_price[8];     /* bytes 22 to 29 */
} BrokenTradeMessage;

/* any Broken Trade Message at all: every byte one the checker chooses */
static void any_broken_trade_message(BrokenTradeMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->security_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->trade_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->original_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->original_price[i] = arbitrary(); }
}

/* Broken Trade Message to the wire: 30 bytes from at, returning where the next byte goes */
static size_t encode_broken_trade_message(const BrokenTradeMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->security_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->trade_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->original_quantity[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->original_price[i]; }

  return at;
}

/* Broken Trade Message off the wire: 30 bytes from at, returning where the next byte lies */
static size_t decode_broken_trade_message(BrokenTradeMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->security_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->trade_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->original_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->original_price[i] = wire[at++]; }

  return at;
}

/* what was read of Broken Trade Message is what was written, byte for byte */
static void equal_broken_trade_message(const BrokenTradeMessage *read, const BrokenTradeMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->security_id[i] == written->security_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->trade_id[i] == written->trade_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->original_quantity[i] == written->original_quantity[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->original_price[i] == written->original_price[i]); }
}

/* Broken Trade Message: written and read back, then read and written back */
static void check_broken_trade_message(void) {
  BrokenTradeMessage sent;
  BrokenTradeMessage got;
  uint8_t wire[30];
  uint8_t again[30];

  any_broken_trade_message(&sent);
  assert(encode_broken_trade_message(&sent, wire, 0) == 30);
  assert(decode_broken_trade_message(&got, wire, 0) == 30);
  equal_broken_trade_message(&got, &sent);

  for (size_t i = 0; i < 30; i++) { wire[i] = arbitrary(); }
  assert(decode_broken_trade_message(&got, wire, 0) == 30);
  assert(encode_broken_trade_message(&got, again, 0) == 30);
  for (size_t i = 0; i < 30; i++) { assert(again[i] == wire[i]); }
}

/* ---- Corrected Trade Message: 42 bytes --------------------------------------- */

/* CorrectedTradeMessage */
typedef struct {
  uint8_t timestamp[8];           /* bytes 0 to 7 */
  uint8_t security_id[2];         /* bytes 8 to 9 */
  uint8_t trade_id[8];            /* bytes 10 to 17 */
  uint8_t original_quantity[4];   /* bytes 18 to 21 */
  uint8_t original_price[8];      /* bytes 22 to 29 */
  uint8_t corrected_quantity[4];  /* bytes 30 to 33 */
  uint8_t corrected_price[8];     /* bytes 34 to 41 */
} CorrectedTradeMessage;

/* any Corrected Trade Message at all: every byte one the checker chooses */
static void any_corrected_trade_message(CorrectedTradeMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->security_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->trade_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->original_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->original_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->corrected_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->corrected_price[i] = arbitrary(); }
}

/* Corrected Trade Message to the wire: 42 bytes from at, returning where the next byte goes */
static size_t encode_corrected_trade_message(const CorrectedTradeMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->security_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->trade_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->original_quantity[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->original_price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->corrected_quantity[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->corrected_price[i]; }

  return at;
}

/* Corrected Trade Message off the wire: 42 bytes from at, returning where the next byte lies */
static size_t decode_corrected_trade_message(CorrectedTradeMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->security_id[i] = wire[at++]; }
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
  for (size_t i = 0; i < 2; i++) { assert(read->security_id[i] == written->security_id[i]); }
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
  uint8_t wire[42];
  uint8_t again[42];

  any_corrected_trade_message(&sent);
  assert(encode_corrected_trade_message(&sent, wire, 0) == 42);
  assert(decode_corrected_trade_message(&got, wire, 0) == 42);
  equal_corrected_trade_message(&got, &sent);

  for (size_t i = 0; i < 42; i++) { wire[i] = arbitrary(); }
  assert(decode_corrected_trade_message(&got, wire, 0) == 42);
  assert(encode_corrected_trade_message(&got, again, 0) == 42);
  for (size_t i = 0; i < 42; i++) { assert(again[i] == wire[i]); }
}

/* ---- Clear Book Message: 10 bytes -------------------------------------------- */

/* ClearBookMessage */
typedef struct {
  uint8_t timestamp[8];    /* bytes 0 to 7 */
  uint8_t security_id[2];  /* bytes 8 to 9 */
} ClearBookMessage;

/* any Clear Book Message at all: every byte one the checker chooses */
static void any_clear_book_message(ClearBookMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->security_id[i] = arbitrary(); }
}

/* Clear Book Message to the wire: 10 bytes from at, returning where the next byte goes */
static size_t encode_clear_book_message(const ClearBookMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->security_id[i]; }

  return at;
}

/* Clear Book Message off the wire: 10 bytes from at, returning where the next byte lies */
static size_t decode_clear_book_message(ClearBookMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->security_id[i] = wire[at++]; }

  return at;
}

/* what was read of Clear Book Message is what was written, byte for byte */
static void equal_clear_book_message(const ClearBookMessage *read, const ClearBookMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->security_id[i] == written->security_id[i]); }
}

/* Clear Book Message: written and read back, then read and written back */
static void check_clear_book_message(void) {
  ClearBookMessage sent;
  ClearBookMessage got;
  uint8_t wire[10];
  uint8_t again[10];

  any_clear_book_message(&sent);
  assert(encode_clear_book_message(&sent, wire, 0) == 10);
  assert(decode_clear_book_message(&got, wire, 0) == 10);
  equal_clear_book_message(&got, &sent);

  for (size_t i = 0; i < 10; i++) { wire[i] = arbitrary(); }
  assert(decode_clear_book_message(&got, wire, 0) == 10);
  assert(encode_clear_book_message(&got, again, 0) == 10);
  for (size_t i = 0; i < 10; i++) { assert(again[i] == wire[i]); }
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

/* ---- What esbmc checks ------------------------------------------------------- */

/* every record of the protocol, each on its own buffers */
static void checks(void) {
  check_common_header();
  check_sbe_header();
  check_instrument_directory_message();
  check_reg_sho_restriction_message();
  check_security_trading_status_message();
  check_trading_session_status_message();
  check_order_added_message();
  check_order_deleted_message();
  check_order_reduced_message();
  check_order_executed_message();
  check_trade_message();
  check_broken_trade_message();
  check_corrected_trade_message();
  check_clear_book_message();
  check_snapshot_complete_message();
}

int main(void) {
#ifdef CONCRETE
  for (pattern = 0; pattern < 4; pattern++) { checks(); }
#else
  checks();
#endif

  return 0;
}
