// miax/pearlequities/depthofmarket/PearlEquities_DepthOfMarket_v1_3_c_Udp.c
/*
 * Miami International Holdings Depth Of Market
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
 *   - a field read in bits
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

/* ---- Mach Packet Header: 12 bytes -------------------------------------------- */

/* Mach packet header (12 bytes) */
typedef struct {
  uint8_t sequence_number[8];     /* bytes 0 to 7 */
  uint8_t mach_packet_length[2];  /* bytes 8 to 9 */
  uint8_t mach_packet_type;       /* byte 10 */
  uint8_t session_number;         /* byte 11 */
} MachPacketHeader;

/* any Mach Packet Header at all: every byte one the checker chooses */
static void any_mach_packet_header(MachPacketHeader *record) {
  for (size_t i = 0; i < 8; i++) { record->sequence_number[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->mach_packet_length[i] = arbitrary(); }
  record->mach_packet_type = arbitrary();
  record->session_number = arbitrary();
}

/* Mach Packet Header to the wire: 12 bytes from at, returning where the next byte goes */
static size_t encode_mach_packet_header(const MachPacketHeader *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->sequence_number[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->mach_packet_length[i]; }
  wire[at++] = record->mach_packet_type;
  wire[at++] = record->session_number;

  return at;
}

/* Mach Packet Header off the wire: 12 bytes from at, returning where the next byte lies */
static size_t decode_mach_packet_header(MachPacketHeader *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->sequence_number[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->mach_packet_length[i] = wire[at++]; }
  record->mach_packet_type = wire[at++];
  record->session_number = wire[at++];

  return at;
}

/* what was read of Mach Packet Header is what was written, byte for byte */
static void equal_mach_packet_header(const MachPacketHeader *read, const MachPacketHeader *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->sequence_number[i] == written->sequence_number[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->mach_packet_length[i] == written->mach_packet_length[i]); }
  assert(read->mach_packet_type == written->mach_packet_type);
  assert(read->session_number == written->session_number);
}

/* Mach Packet Header: written and read back, then read and written back */
static void check_mach_packet_header(void) {
  MachPacketHeader sent;
  MachPacketHeader got;
  uint8_t wire[12];
  uint8_t again[12];

  any_mach_packet_header(&sent);
  assert(encode_mach_packet_header(&sent, wire, 0) == 12);
  assert(decode_mach_packet_header(&got, wire, 0) == 12);
  equal_mach_packet_header(&got, &sent);

  for (size_t i = 0; i < 12; i++) { wire[i] = arbitrary(); }
  assert(decode_mach_packet_header(&got, wire, 0) == 12);
  assert(encode_mach_packet_header(&got, again, 0) == 12);
  for (size_t i = 0; i < 12; i++) { assert(again[i] == wire[i]); }
}

/* ---- System Time Message: 4 bytes -------------------------------------------- */

/* This message is used to disseminate the "seconds" part of the timestamp that is applicable to all messages that are sent in the current second. */
typedef struct {
  uint8_t seconds[4];  /* bytes 0 to 3 */
} SystemTimeMessage;

/* any System Time Message at all: every byte one the checker chooses */
static void any_system_time_message(SystemTimeMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->seconds[i] = arbitrary(); }
}

/* System Time Message to the wire: 4 bytes from at, returning where the next byte goes */
static size_t encode_system_time_message(const SystemTimeMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->seconds[i]; }

  return at;
}

/* System Time Message off the wire: 4 bytes from at, returning where the next byte lies */
static size_t decode_system_time_message(SystemTimeMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->seconds[i] = wire[at++]; }

  return at;
}

/* what was read of System Time Message is what was written, byte for byte */
static void equal_system_time_message(const SystemTimeMessage *read, const SystemTimeMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->seconds[i] == written->seconds[i]); }
}

/* System Time Message: written and read back, then read and written back */
static void check_system_time_message(void) {
  SystemTimeMessage sent;
  SystemTimeMessage got;
  uint8_t wire[4];
  uint8_t again[4];

  any_system_time_message(&sent);
  assert(encode_system_time_message(&sent, wire, 0) == 4);
  assert(decode_system_time_message(&got, wire, 0) == 4);
  equal_system_time_message(&got, &sent);

  for (size_t i = 0; i < 4; i++) { wire[i] = arbitrary(); }
  assert(decode_system_time_message(&got, wire, 0) == 4);
  assert(encode_system_time_message(&got, again, 0) == 4);
  for (size_t i = 0; i < 4; i++) { assert(again[i] == wire[i]); }
}

/* ---- Symbol Update Message: 41 bytes ----------------------------------------- */

/* This is the message format that will be used to disseminate all security symbols traded on MIAX Pearl Equities for the current trading session. The Symbol ID sent in this message will be disseminated in Depth of Market messages. */
typedef struct {
  uint8_t nanoseconds[4];           /* bytes 0 to 3 */
  uint8_t symbol_id[4];             /* bytes 4 to 7 */
  uint8_t ticker_symbol[11];        /* bytes 8 to 18 */
  uint8_t reserved_1;               /* byte 19 */
  uint8_t test_security_indicator;  /* byte 20 */
  uint8_t second_reserved_1;        /* byte 21 */
  uint8_t lot_size[2];              /* bytes 22 to 23 */
  uint8_t opening_time[8];          /* bytes 24 to 31 */
  uint8_t closing_time[8];          /* bytes 32 to 39 */
  uint8_t primary_market_code;      /* byte 40 */
} SymbolUpdateMessage;

/* any Symbol Update Message at all: every byte one the checker chooses */
static void any_symbol_update_message(SymbolUpdateMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->symbol_id[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->ticker_symbol[i] = arbitrary(); }
  record->reserved_1 = arbitrary();
  record->test_security_indicator = arbitrary();
  record->second_reserved_1 = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->lot_size[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->opening_time[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->closing_time[i] = arbitrary(); }
  record->primary_market_code = arbitrary();
}

/* Symbol Update Message to the wire: 41 bytes from at, returning where the next byte goes */
static size_t encode_symbol_update_message(const SymbolUpdateMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->nanoseconds[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->symbol_id[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->ticker_symbol[i]; }
  wire[at++] = record->reserved_1;
  wire[at++] = record->test_security_indicator;
  wire[at++] = record->second_reserved_1;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->lot_size[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->opening_time[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->closing_time[i]; }
  wire[at++] = record->primary_market_code;

  return at;
}

/* Symbol Update Message off the wire: 41 bytes from at, returning where the next byte lies */
static size_t decode_symbol_update_message(SymbolUpdateMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->symbol_id[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->ticker_symbol[i] = wire[at++]; }
  record->reserved_1 = wire[at++];
  record->test_security_indicator = wire[at++];
  record->second_reserved_1 = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->lot_size[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->opening_time[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->closing_time[i] = wire[at++]; }
  record->primary_market_code = wire[at++];

  return at;
}

/* what was read of Symbol Update Message is what was written, byte for byte */
static void equal_symbol_update_message(const SymbolUpdateMessage *read, const SymbolUpdateMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->nanoseconds[i] == written->nanoseconds[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->symbol_id[i] == written->symbol_id[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->ticker_symbol[i] == written->ticker_symbol[i]); }
  assert(read->reserved_1 == written->reserved_1);
  assert(read->test_security_indicator == written->test_security_indicator);
  assert(read->second_reserved_1 == written->second_reserved_1);
  for (size_t i = 0; i < 2; i++) { assert(read->lot_size[i] == written->lot_size[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->opening_time[i] == written->opening_time[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->closing_time[i] == written->closing_time[i]); }
  assert(read->primary_market_code == written->primary_market_code);
}

/* Symbol Update Message: written and read back, then read and written back */
static void check_symbol_update_message(void) {
  SymbolUpdateMessage sent;
  SymbolUpdateMessage got;
  uint8_t wire[41];
  uint8_t again[41];

  any_symbol_update_message(&sent);
  assert(encode_symbol_update_message(&sent, wire, 0) == 41);
  assert(decode_symbol_update_message(&got, wire, 0) == 41);
  equal_symbol_update_message(&got, &sent);

  for (size_t i = 0; i < 41; i++) { wire[i] = arbitrary(); }
  assert(decode_symbol_update_message(&got, wire, 0) == 41);
  assert(encode_symbol_update_message(&got, again, 0) == 41);
  for (size_t i = 0; i < 41; i++) { assert(again[i] == wire[i]); }
}

/* ---- System State Message: 14 bytes ------------------------------------------ */

/* This is the message format that will be used to notify firms of the state changes of the system. This is a notification that applies to all symbols on the feed. */
typedef struct {
  uint8_t nanoseconds[4];   /* bytes 0 to 3 */
  uint8_t do_m_version[8];  /* bytes 4 to 11 */
  uint8_t session_id;       /* byte 12 */
  uint8_t system_status;    /* byte 13 */
} SystemStateMessage;

/* any System State Message at all: every byte one the checker chooses */
static void any_system_state_message(SystemStateMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->do_m_version[i] = arbitrary(); }
  record->session_id = arbitrary();
  record->system_status = arbitrary();
}

/* System State Message to the wire: 14 bytes from at, returning where the next byte goes */
static size_t encode_system_state_message(const SystemStateMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->nanoseconds[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->do_m_version[i]; }
  wire[at++] = record->session_id;
  wire[at++] = record->system_status;

  return at;
}

/* System State Message off the wire: 14 bytes from at, returning where the next byte lies */
static size_t decode_system_state_message(SystemStateMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->do_m_version[i] = wire[at++]; }
  record->session_id = wire[at++];
  record->system_status = wire[at++];

  return at;
}

/* what was read of System State Message is what was written, byte for byte */
static void equal_system_state_message(const SystemStateMessage *read, const SystemStateMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->nanoseconds[i] == written->nanoseconds[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->do_m_version[i] == written->do_m_version[i]); }
  assert(read->session_id == written->session_id);
  assert(read->system_status == written->system_status);
}

/* System State Message: written and read back, then read and written back */
static void check_system_state_message(void) {
  SystemStateMessage sent;
  SystemStateMessage got;
  uint8_t wire[14];
  uint8_t again[14];

  any_system_state_message(&sent);
  assert(encode_system_state_message(&sent, wire, 0) == 14);
  assert(decode_system_state_message(&got, wire, 0) == 14);
  equal_system_state_message(&got, &sent);

  for (size_t i = 0; i < 14; i++) { wire[i] = arbitrary(); }
  assert(decode_system_state_message(&got, wire, 0) == 14);
  assert(encode_system_state_message(&got, again, 0) == 14);
  for (size_t i = 0; i < 14; i++) { assert(again[i] == wire[i]); }
}

/* ---- Security Trading Status Notification Message: 11 bytes ------------------ */

/* This message is used to notify firms of changes to the trading status of a particular security. */
typedef struct {
  uint8_t nanoseconds[4];          /* bytes 0 to 3 */
  uint8_t symbol_id[4];            /* bytes 4 to 7 */
  uint8_t trading_status;          /* byte 8 */
  uint8_t market_state;            /* byte 9 */
  uint8_t short_sale_restriction;  /* byte 10 */
} SecurityTradingStatusNotificationMessage;

/* any Security Trading Status Notification Message at all: every byte one the checker chooses */
static void any_security_trading_status_notification_message(SecurityTradingStatusNotificationMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->symbol_id[i] = arbitrary(); }
  record->trading_status = arbitrary();
  record->market_state = arbitrary();
  record->short_sale_restriction = arbitrary();
}

/* Security Trading Status Notification Message to the wire: 11 bytes from at, returning where the next byte goes */
static size_t encode_security_trading_status_notification_message(const SecurityTradingStatusNotificationMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->nanoseconds[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->symbol_id[i]; }
  wire[at++] = record->trading_status;
  wire[at++] = record->market_state;
  wire[at++] = record->short_sale_restriction;

  return at;
}

/* Security Trading Status Notification Message off the wire: 11 bytes from at, returning where the next byte lies */
static size_t decode_security_trading_status_notification_message(SecurityTradingStatusNotificationMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->symbol_id[i] = wire[at++]; }
  record->trading_status = wire[at++];
  record->market_state = wire[at++];
  record->short_sale_restriction = wire[at++];

  return at;
}

/* what was read of Security Trading Status Notification Message is what was written, byte for byte */
static void equal_security_trading_status_notification_message(const SecurityTradingStatusNotificationMessage *read, const SecurityTradingStatusNotificationMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->nanoseconds[i] == written->nanoseconds[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->symbol_id[i] == written->symbol_id[i]); }
  assert(read->trading_status == written->trading_status);
  assert(read->market_state == written->market_state);
  assert(read->short_sale_restriction == written->short_sale_restriction);
}

/* Security Trading Status Notification Message: written and read back, then read and written back */
static void check_security_trading_status_notification_message(void) {
  SecurityTradingStatusNotificationMessage sent;
  SecurityTradingStatusNotificationMessage got;
  uint8_t wire[11];
  uint8_t again[11];

  any_security_trading_status_notification_message(&sent);
  assert(encode_security_trading_status_notification_message(&sent, wire, 0) == 11);
  assert(decode_security_trading_status_notification_message(&got, wire, 0) == 11);
  equal_security_trading_status_notification_message(&got, &sent);

  for (size_t i = 0; i < 11; i++) { wire[i] = arbitrary(); }
  assert(decode_security_trading_status_notification_message(&got, wire, 0) == 11);
  assert(encode_security_trading_status_notification_message(&got, again, 0) == 11);
  for (size_t i = 0; i < 11; i++) { assert(again[i] == wire[i]); }
}

/* ---- Symbol Clear Message: 8 bytes ------------------------------------------- */

/* This message format is used to indicate that the MIAX Pearl Equities book for a symbol has been cleared of all orders. */
typedef struct {
  uint8_t nanoseconds[4];  /* bytes 0 to 3 */
  uint8_t symbol_id[4];    /* bytes 4 to 7 */
} SymbolClearMessage;

/* any Symbol Clear Message at all: every byte one the checker chooses */
static void any_symbol_clear_message(SymbolClearMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->symbol_id[i] = arbitrary(); }
}

/* Symbol Clear Message to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_symbol_clear_message(const SymbolClearMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->nanoseconds[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->symbol_id[i]; }

  return at;
}

/* Symbol Clear Message off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_symbol_clear_message(SymbolClearMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->symbol_id[i] = wire[at++]; }

  return at;
}

/* what was read of Symbol Clear Message is what was written, byte for byte */
static void equal_symbol_clear_message(const SymbolClearMessage *read, const SymbolClearMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->nanoseconds[i] == written->nanoseconds[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->symbol_id[i] == written->symbol_id[i]); }
}

/* Symbol Clear Message: written and read back, then read and written back */
static void check_symbol_clear_message(void) {
  SymbolClearMessage sent;
  SymbolClearMessage got;
  uint8_t wire[8];
  uint8_t again[8];

  any_symbol_clear_message(&sent);
  assert(encode_symbol_clear_message(&sent, wire, 0) == 8);
  assert(decode_symbol_clear_message(&got, wire, 0) == 8);
  equal_symbol_clear_message(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_symbol_clear_message(&got, wire, 0) == 8);
  assert(encode_symbol_clear_message(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Add Order Message: 33 bytes --------------------------------------------- */

/* This is the message format that will be used when a displayed order is received and added to MIAX Pearl Equities book. It includes an Order ID that is unique to the order across the exchange and across trading days. */
typedef struct {
  uint8_t nanoseconds[4];      /* bytes 0 to 3 */
  uint8_t symbol_id[4];        /* bytes 4 to 7 */
  uint8_t order_id[8];         /* bytes 8 to 15 */
  uint8_t order_side;          /* byte 16 */
  uint8_t price[8];            /* bytes 17 to 24 */
  uint8_t size[4];             /* bytes 25 to 28 */
  uint8_t attributable_id[4];  /* bytes 29 to 32 */
} AddOrderMessage;

/* any Add Order Message at all: every byte one the checker chooses */
static void any_add_order_message(AddOrderMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->symbol_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = arbitrary(); }
  record->order_side = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->size[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->attributable_id[i] = arbitrary(); }
}

/* Add Order Message to the wire: 33 bytes from at, returning where the next byte goes */
static size_t encode_add_order_message(const AddOrderMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->nanoseconds[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->symbol_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_id[i]; }
  wire[at++] = record->order_side;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->size[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->attributable_id[i]; }

  return at;
}

/* Add Order Message off the wire: 33 bytes from at, returning where the next byte lies */
static size_t decode_add_order_message(AddOrderMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->symbol_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = wire[at++]; }
  record->order_side = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->size[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->attributable_id[i] = wire[at++]; }

  return at;
}

/* what was read of Add Order Message is what was written, byte for byte */
static void equal_add_order_message(const AddOrderMessage *read, const AddOrderMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->nanoseconds[i] == written->nanoseconds[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->symbol_id[i] == written->symbol_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->order_id[i] == written->order_id[i]); }
  assert(read->order_side == written->order_side);
  for (size_t i = 0; i < 8; i++) { assert(read->price[i] == written->price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->size[i] == written->size[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->attributable_id[i] == written->attributable_id[i]); }
}

/* Add Order Message: written and read back, then read and written back */
static void check_add_order_message(void) {
  AddOrderMessage sent;
  AddOrderMessage got;
  uint8_t wire[33];
  uint8_t again[33];

  any_add_order_message(&sent);
  assert(encode_add_order_message(&sent, wire, 0) == 33);
  assert(decode_add_order_message(&got, wire, 0) == 33);
  equal_add_order_message(&got, &sent);

  for (size_t i = 0; i < 33; i++) { wire[i] = arbitrary(); }
  assert(decode_add_order_message(&got, wire, 0) == 33);
  assert(encode_add_order_message(&got, again, 0) == 33);
  for (size_t i = 0; i < 33; i++) { assert(again[i] == wire[i]); }
}

/* ---- Delete Order Message: 16 bytes ------------------------------------------ */

/* This message format is used to indicate that a displayed order has been removed from the MIAX Pearl Equities book. */
typedef struct {
  uint8_t nanoseconds[4];  /* bytes 0 to 3 */
  uint8_t symbol_id[4];    /* bytes 4 to 7 */
  uint8_t order_id[8];     /* bytes 8 to 15 */
} DeleteOrderMessage;

/* any Delete Order Message at all: every byte one the checker chooses */
static void any_delete_order_message(DeleteOrderMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->symbol_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = arbitrary(); }
}

/* Delete Order Message to the wire: 16 bytes from at, returning where the next byte goes */
static size_t encode_delete_order_message(const DeleteOrderMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->nanoseconds[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->symbol_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_id[i]; }

  return at;
}

/* Delete Order Message off the wire: 16 bytes from at, returning where the next byte lies */
static size_t decode_delete_order_message(DeleteOrderMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->symbol_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = wire[at++]; }

  return at;
}

/* what was read of Delete Order Message is what was written, byte for byte */
static void equal_delete_order_message(const DeleteOrderMessage *read, const DeleteOrderMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->nanoseconds[i] == written->nanoseconds[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->symbol_id[i] == written->symbol_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->order_id[i] == written->order_id[i]); }
}

/* Delete Order Message: written and read back, then read and written back */
static void check_delete_order_message(void) {
  DeleteOrderMessage sent;
  DeleteOrderMessage got;
  uint8_t wire[16];
  uint8_t again[16];

  any_delete_order_message(&sent);
  assert(encode_delete_order_message(&sent, wire, 0) == 16);
  assert(decode_delete_order_message(&got, wire, 0) == 16);
  equal_delete_order_message(&got, &sent);

  for (size_t i = 0; i < 16; i++) { wire[i] = arbitrary(); }
  assert(decode_delete_order_message(&got, wire, 0) == 16);
  assert(encode_delete_order_message(&got, again, 0) == 16);
  for (size_t i = 0; i < 16; i++) { assert(again[i] == wire[i]); }
}

/* ---- Trade Cancel Message: 29 bytes ------------------------------------------ */

/* This message format is used to publish cancellation of a trade which was previously published via an Order Execution Message or a Trade Message. */
typedef struct {
  uint8_t nanoseconds[4];     /* bytes 0 to 3 */
  uint8_t symbol_id[4];       /* bytes 4 to 7 */
  uint8_t trade_id[8];        /* bytes 8 to 15 */
  uint8_t correction_number;  /* byte 16 */
  uint8_t price[8];           /* bytes 17 to 24 */
  uint8_t size[4];            /* bytes 25 to 28 */
} TradeCancelMessage;

/* any Trade Cancel Message at all: every byte one the checker chooses */
static void any_trade_cancel_message(TradeCancelMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->symbol_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->trade_id[i] = arbitrary(); }
  record->correction_number = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->size[i] = arbitrary(); }
}

/* Trade Cancel Message to the wire: 29 bytes from at, returning where the next byte goes */
static size_t encode_trade_cancel_message(const TradeCancelMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->nanoseconds[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->symbol_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->trade_id[i]; }
  wire[at++] = record->correction_number;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->size[i]; }

  return at;
}

/* Trade Cancel Message off the wire: 29 bytes from at, returning where the next byte lies */
static size_t decode_trade_cancel_message(TradeCancelMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->symbol_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->trade_id[i] = wire[at++]; }
  record->correction_number = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->size[i] = wire[at++]; }

  return at;
}

/* what was read of Trade Cancel Message is what was written, byte for byte */
static void equal_trade_cancel_message(const TradeCancelMessage *read, const TradeCancelMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->nanoseconds[i] == written->nanoseconds[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->symbol_id[i] == written->symbol_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->trade_id[i] == written->trade_id[i]); }
  assert(read->correction_number == written->correction_number);
  for (size_t i = 0; i < 8; i++) { assert(read->price[i] == written->price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->size[i] == written->size[i]); }
}

/* Trade Cancel Message: written and read back, then read and written back */
static void check_trade_cancel_message(void) {
  TradeCancelMessage sent;
  TradeCancelMessage got;
  uint8_t wire[29];
  uint8_t again[29];

  any_trade_cancel_message(&sent);
  assert(encode_trade_cancel_message(&sent, wire, 0) == 29);
  assert(decode_trade_cancel_message(&got, wire, 0) == 29);
  equal_trade_cancel_message(&got, &sent);

  for (size_t i = 0; i < 29; i++) { wire[i] = arbitrary(); }
  assert(decode_trade_cancel_message(&got, wire, 0) == 29);
  assert(encode_trade_cancel_message(&got, again, 0) == 29);
  for (size_t i = 0; i < 29; i++) { assert(again[i] == wire[i]); }
}

/* ---- What esbmc checks ------------------------------------------------------- */

/* every record of the protocol, each on its own buffers */
static void checks(void) {
  check_mach_packet_header();
  check_system_time_message();
  check_symbol_update_message();
  check_system_state_message();
  check_security_trading_status_notification_message();
  check_symbol_clear_message();
  check_add_order_message();
  check_delete_order_message();
  check_trade_cancel_message();
}

int main(void) {
#ifdef CONCRETE
  for (pattern = 0; pattern < 4; pattern++) { checks(); }
#else
  checks();
#endif

  return 0;
}
