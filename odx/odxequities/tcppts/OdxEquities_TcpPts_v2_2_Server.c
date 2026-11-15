// odx/odxequities/tcppts/OdxEquities_TcpPts_v2_2_Server.c
/*
 * Osaka Digital Exchange Tcp Proprietary Trading System
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
 *   - a length prefix framing what follows
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

/* ---- Server Packet Header: 3 bytes ------------------------------------------- */

/* Packet header of a packet sent by the server */
typedef struct {
  uint8_t packet_length[2];    /* bytes 0 to 1 */
  uint8_t server_packet_type;  /* byte 2 */
} ServerPacketHeader;

/* any Server Packet Header at all: every byte one the checker chooses */
static void any_server_packet_header(ServerPacketHeader *record) {
  for (size_t i = 0; i < 2; i++) { record->packet_length[i] = arbitrary(); }
  record->server_packet_type = arbitrary();
}

/* Server Packet Header to the wire: 3 bytes from at, returning where the next byte goes */
static size_t encode_server_packet_header(const ServerPacketHeader *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->packet_length[i]; }
  wire[at++] = record->server_packet_type;

  return at;
}

/* Server Packet Header off the wire: 3 bytes from at, returning where the next byte lies */
static size_t decode_server_packet_header(ServerPacketHeader *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->packet_length[i] = wire[at++]; }
  record->server_packet_type = wire[at++];

  return at;
}

/* what was read of Server Packet Header is what was written, byte for byte */
static void equal_server_packet_header(const ServerPacketHeader *read, const ServerPacketHeader *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->packet_length[i] == written->packet_length[i]); }
  assert(read->server_packet_type == written->server_packet_type);
}

/* Server Packet Header: written and read back, then read and written back */
static void check_server_packet_header(void) {
  ServerPacketHeader sent;
  ServerPacketHeader got;
  uint8_t wire[3];
  uint8_t again[3];

  any_server_packet_header(&sent);
  assert(encode_server_packet_header(&sent, wire, 0) == 3);
  assert(decode_server_packet_header(&got, wire, 0) == 3);
  equal_server_packet_header(&got, &sent);

  for (size_t i = 0; i < 3; i++) { wire[i] = arbitrary(); }
  assert(decode_server_packet_header(&got, wire, 0) == 3);
  assert(encode_server_packet_header(&got, again, 0) == 3);
  for (size_t i = 0; i < 3; i++) { assert(again[i] == wire[i]); }
}

/* ---- Login Accepted Packet: 30 bytes ----------------------------------------- */

/* The SoupBinTCP server sends a Login Accepted Packet in response to receiving a valid Login Request from the client */
typedef struct {
  uint8_t accepted_session[10];          /* bytes 0 to 9 */
  uint8_t accepted_sequence_number[20];  /* bytes 10 to 29 */
} LoginAcceptedPacket;

/* any Login Accepted Packet at all: every byte one the checker chooses */
static void any_login_accepted_packet(LoginAcceptedPacket *record) {
  for (size_t i = 0; i < 10; i++) { record->accepted_session[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->accepted_sequence_number[i] = arbitrary(); }
}

/* Login Accepted Packet to the wire: 30 bytes from at, returning where the next byte goes */
static size_t encode_login_accepted_packet(const LoginAcceptedPacket *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->accepted_session[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->accepted_sequence_number[i]; }

  return at;
}

/* Login Accepted Packet off the wire: 30 bytes from at, returning where the next byte lies */
static size_t decode_login_accepted_packet(LoginAcceptedPacket *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 10; i++) { record->accepted_session[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->accepted_sequence_number[i] = wire[at++]; }

  return at;
}

/* what was read of Login Accepted Packet is what was written, byte for byte */
static void equal_login_accepted_packet(const LoginAcceptedPacket *read, const LoginAcceptedPacket *written) {
  for (size_t i = 0; i < 10; i++) { assert(read->accepted_session[i] == written->accepted_session[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->accepted_sequence_number[i] == written->accepted_sequence_number[i]); }
}

/* Login Accepted Packet: written and read back, then read and written back */
static void check_login_accepted_packet(void) {
  LoginAcceptedPacket sent;
  LoginAcceptedPacket got;
  uint8_t wire[30];
  uint8_t again[30];

  any_login_accepted_packet(&sent);
  assert(encode_login_accepted_packet(&sent, wire, 0) == 30);
  assert(decode_login_accepted_packet(&got, wire, 0) == 30);
  equal_login_accepted_packet(&got, &sent);

  for (size_t i = 0; i < 30; i++) { wire[i] = arbitrary(); }
  assert(decode_login_accepted_packet(&got, wire, 0) == 30);
  assert(encode_login_accepted_packet(&got, again, 0) == 30);
  for (size_t i = 0; i < 30; i++) { assert(again[i] == wire[i]); }
}

/* ---- Login Rejected Packet: 1 byte ------------------------------------------- */

/* The SoupBinTCP server sends this packet in response to an invalid Login Request Packet from the client */
typedef struct {
  uint8_t reject_reason_code;  /* byte 0 */
} LoginRejectedPacket;

/* any Login Rejected Packet at all: every byte one the checker chooses */
static void any_login_rejected_packet(LoginRejectedPacket *record) {
  record->reject_reason_code = arbitrary();
}

/* Login Rejected Packet to the wire: 1 byte from at, returning where the next byte goes */
static size_t encode_login_rejected_packet(const LoginRejectedPacket *record, uint8_t *wire, size_t at) {
  wire[at++] = record->reject_reason_code;

  return at;
}

/* Login Rejected Packet off the wire: 1 byte from at, returning where the next byte lies */
static size_t decode_login_rejected_packet(LoginRejectedPacket *record, const uint8_t *wire, size_t at) {
  record->reject_reason_code = wire[at++];

  return at;
}

/* what was read of Login Rejected Packet is what was written, byte for byte */
static void equal_login_rejected_packet(const LoginRejectedPacket *read, const LoginRejectedPacket *written) {
  assert(read->reject_reason_code == written->reject_reason_code);
}

/* Login Rejected Packet: written and read back, then read and written back */
static void check_login_rejected_packet(void) {
  LoginRejectedPacket sent;
  LoginRejectedPacket got;
  uint8_t wire[1];
  uint8_t again[1];

  any_login_rejected_packet(&sent);
  assert(encode_login_rejected_packet(&sent, wire, 0) == 1);
  assert(decode_login_rejected_packet(&got, wire, 0) == 1);
  equal_login_rejected_packet(&got, &sent);

  for (size_t i = 0; i < 1; i++) { wire[i] = arbitrary(); }
  assert(decode_login_rejected_packet(&got, wire, 0) == 1);
  assert(encode_login_rejected_packet(&got, again, 0) == 1);
  for (size_t i = 0; i < 1; i++) { assert(again[i] == wire[i]); }
}

/* ---- Seconds Message: 4 bytes ------------------------------------------------ */

/* Reflects the number of seconds past midnight */
typedef struct {
  uint8_t seconds[4];  /* bytes 0 to 3 */
} SecondsMessage;

/* any Seconds Message at all: every byte one the checker chooses */
static void any_seconds_message(SecondsMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->seconds[i] = arbitrary(); }
}

/* Seconds Message to the wire: 4 bytes from at, returning where the next byte goes */
static size_t encode_seconds_message(const SecondsMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->seconds[i]; }

  return at;
}

/* Seconds Message off the wire: 4 bytes from at, returning where the next byte lies */
static size_t decode_seconds_message(SecondsMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->seconds[i] = wire[at++]; }

  return at;
}

/* what was read of Seconds Message is what was written, byte for byte */
static void equal_seconds_message(const SecondsMessage *read, const SecondsMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->seconds[i] == written->seconds[i]); }
}

/* Seconds Message: written and read back, then read and written back */
static void check_seconds_message(void) {
  SecondsMessage sent;
  SecondsMessage got;
  uint8_t wire[4];
  uint8_t again[4];

  any_seconds_message(&sent);
  assert(encode_seconds_message(&sent, wire, 0) == 4);
  assert(decode_seconds_message(&got, wire, 0) == 4);
  equal_seconds_message(&got, &sent);

  for (size_t i = 0; i < 4; i++) { wire[i] = arbitrary(); }
  assert(decode_seconds_message(&got, wire, 0) == 4);
  assert(encode_seconds_message(&got, again, 0) == 4);
  for (size_t i = 0; i < 4; i++) { assert(again[i] == wire[i]); }
}

/* ---- System Event Message: 9 bytes ------------------------------------------- */

/* System Event Messages signal data feed, system and market events */
typedef struct {
  uint8_t nanoseconds[4];  /* bytes 0 to 3 */
  uint8_t group[4];        /* bytes 4 to 7 */
  uint8_t system_event;    /* byte 8 */
} SystemEventMessage;

/* any System Event Message at all: every byte one the checker chooses */
static void any_system_event_message(SystemEventMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->group[i] = arbitrary(); }
  record->system_event = arbitrary();
}

/* System Event Message to the wire: 9 bytes from at, returning where the next byte goes */
static size_t encode_system_event_message(const SystemEventMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->nanoseconds[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->group[i]; }
  wire[at++] = record->system_event;

  return at;
}

/* System Event Message off the wire: 9 bytes from at, returning where the next byte lies */
static size_t decode_system_event_message(SystemEventMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->group[i] = wire[at++]; }
  record->system_event = wire[at++];

  return at;
}

/* what was read of System Event Message is what was written, byte for byte */
static void equal_system_event_message(const SystemEventMessage *read, const SystemEventMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->nanoseconds[i] == written->nanoseconds[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->group[i] == written->group[i]); }
  assert(read->system_event == written->system_event);
}

/* System Event Message: written and read back, then read and written back */
static void check_system_event_message(void) {
  SystemEventMessage sent;
  SystemEventMessage got;
  uint8_t wire[9];
  uint8_t again[9];

  any_system_event_message(&sent);
  assert(encode_system_event_message(&sent, wire, 0) == 9);
  assert(decode_system_event_message(&got, wire, 0) == 9);
  equal_system_event_message(&got, &sent);

  for (size_t i = 0; i < 9; i++) { wire[i] = arbitrary(); }
  assert(decode_system_event_message(&got, wire, 0) == 9);
  assert(encode_system_event_message(&got, again, 0) == 9);
  for (size_t i = 0; i < 9; i++) { assert(again[i] == wire[i]); }
}

/* ---- Price Tick Size Message: 16 bytes --------------------------------------- */

/* The Price Tick Size Message is used to communicate tick size information for a given price range */
typedef struct {
  uint8_t nanoseconds[4];               /* bytes 0 to 3 */
  uint8_t price_tick_size_table_id[4];  /* bytes 4 to 7 */
  uint8_t price_tick_size[4];           /* bytes 8 to 11 */
  uint8_t price_start[4];               /* bytes 12 to 15 */
} PriceTickSizeMessage;

/* any Price Tick Size Message at all: every byte one the checker chooses */
static void any_price_tick_size_message(PriceTickSizeMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->price_tick_size_table_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->price_tick_size[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->price_start[i] = arbitrary(); }
}

/* Price Tick Size Message to the wire: 16 bytes from at, returning where the next byte goes */
static size_t encode_price_tick_size_message(const PriceTickSizeMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->nanoseconds[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->price_tick_size_table_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->price_tick_size[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->price_start[i]; }

  return at;
}

/* Price Tick Size Message off the wire: 16 bytes from at, returning where the next byte lies */
static size_t decode_price_tick_size_message(PriceTickSizeMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->price_tick_size_table_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->price_tick_size[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->price_start[i] = wire[at++]; }

  return at;
}

/* what was read of Price Tick Size Message is what was written, byte for byte */
static void equal_price_tick_size_message(const PriceTickSizeMessage *read, const PriceTickSizeMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->nanoseconds[i] == written->nanoseconds[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->price_tick_size_table_id[i] == written->price_tick_size_table_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->price_tick_size[i] == written->price_tick_size[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->price_start[i] == written->price_start[i]); }
}

/* Price Tick Size Message: written and read back, then read and written back */
static void check_price_tick_size_message(void) {
  PriceTickSizeMessage sent;
  PriceTickSizeMessage got;
  uint8_t wire[16];
  uint8_t again[16];

  any_price_tick_size_message(&sent);
  assert(encode_price_tick_size_message(&sent, wire, 0) == 16);
  assert(decode_price_tick_size_message(&got, wire, 0) == 16);
  equal_price_tick_size_message(&got, &sent);

  for (size_t i = 0; i < 16; i++) { wire[i] = arbitrary(); }
  assert(decode_price_tick_size_message(&got, wire, 0) == 16);
  assert(encode_price_tick_size_message(&got, again, 0) == 16);
  for (size_t i = 0; i < 16; i++) { assert(again[i] == wire[i]); }
}

/* ---- Orderbook Directory Message: 44 bytes ----------------------------------- */

/* The Orderbook Directory Message is used to disseminate orderbook information for all active orderbooks */
typedef struct {
  uint8_t nanoseconds[4];               /* bytes 0 to 3 */
  uint8_t orderbook_id[4];              /* bytes 4 to 7 */
  uint8_t orderbook_code[12];           /* bytes 8 to 19 */
  uint8_t group[4];                     /* bytes 20 to 23 */
  uint8_t round_lot_size[4];            /* bytes 24 to 27 */
  uint8_t price_tick_size_table_id[4];  /* bytes 28 to 31 */
  uint8_t price_decimals[4];            /* bytes 32 to 35 */
  uint8_t upper_price_limit[4];         /* bytes 36 to 39 */
  uint8_t lower_price_limit[4];         /* bytes 40 to 43 */
} OrderbookDirectoryMessage;

/* any Orderbook Directory Message at all: every byte one the checker chooses */
static void any_orderbook_directory_message(OrderbookDirectoryMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->orderbook_id[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->orderbook_code[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->group[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->round_lot_size[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->price_tick_size_table_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->price_decimals[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->upper_price_limit[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->lower_price_limit[i] = arbitrary(); }
}

/* Orderbook Directory Message to the wire: 44 bytes from at, returning where the next byte goes */
static size_t encode_orderbook_directory_message(const OrderbookDirectoryMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->nanoseconds[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->orderbook_id[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->orderbook_code[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->group[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->round_lot_size[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->price_tick_size_table_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->price_decimals[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->upper_price_limit[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->lower_price_limit[i]; }

  return at;
}

/* Orderbook Directory Message off the wire: 44 bytes from at, returning where the next byte lies */
static size_t decode_orderbook_directory_message(OrderbookDirectoryMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->orderbook_id[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->orderbook_code[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->group[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->round_lot_size[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->price_tick_size_table_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->price_decimals[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->upper_price_limit[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->lower_price_limit[i] = wire[at++]; }

  return at;
}

/* what was read of Orderbook Directory Message is what was written, byte for byte */
static void equal_orderbook_directory_message(const OrderbookDirectoryMessage *read, const OrderbookDirectoryMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->nanoseconds[i] == written->nanoseconds[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->orderbook_id[i] == written->orderbook_id[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->orderbook_code[i] == written->orderbook_code[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->group[i] == written->group[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->round_lot_size[i] == written->round_lot_size[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->price_tick_size_table_id[i] == written->price_tick_size_table_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->price_decimals[i] == written->price_decimals[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->upper_price_limit[i] == written->upper_price_limit[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->lower_price_limit[i] == written->lower_price_limit[i]); }
}

/* Orderbook Directory Message: written and read back, then read and written back */
static void check_orderbook_directory_message(void) {
  OrderbookDirectoryMessage sent;
  OrderbookDirectoryMessage got;
  uint8_t wire[44];
  uint8_t again[44];

  any_orderbook_directory_message(&sent);
  assert(encode_orderbook_directory_message(&sent, wire, 0) == 44);
  assert(decode_orderbook_directory_message(&got, wire, 0) == 44);
  equal_orderbook_directory_message(&got, &sent);

  for (size_t i = 0; i < 44; i++) { wire[i] = arbitrary(); }
  assert(decode_orderbook_directory_message(&got, wire, 0) == 44);
  assert(encode_orderbook_directory_message(&got, again, 0) == 44);
  for (size_t i = 0; i < 44; i++) { assert(again[i] == wire[i]); }
}

/* ---- Trading State Message: 13 bytes ----------------------------------------- */

/* The Trading State Message is used to indicate the current trading state of an orderbook */
typedef struct {
  uint8_t nanoseconds[4];   /* bytes 0 to 3 */
  uint8_t orderbook_id[4];  /* bytes 4 to 7 */
  uint8_t group[4];         /* bytes 8 to 11 */
  uint8_t trading_state;    /* byte 12 */
} TradingStateMessage;

/* any Trading State Message at all: every byte one the checker chooses */
static void any_trading_state_message(TradingStateMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->orderbook_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->group[i] = arbitrary(); }
  record->trading_state = arbitrary();
}

/* Trading State Message to the wire: 13 bytes from at, returning where the next byte goes */
static size_t encode_trading_state_message(const TradingStateMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->nanoseconds[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->orderbook_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->group[i]; }
  wire[at++] = record->trading_state;

  return at;
}

/* Trading State Message off the wire: 13 bytes from at, returning where the next byte lies */
static size_t decode_trading_state_message(TradingStateMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->orderbook_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->group[i] = wire[at++]; }
  record->trading_state = wire[at++];

  return at;
}

/* what was read of Trading State Message is what was written, byte for byte */
static void equal_trading_state_message(const TradingStateMessage *read, const TradingStateMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->nanoseconds[i] == written->nanoseconds[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->orderbook_id[i] == written->orderbook_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->group[i] == written->group[i]); }
  assert(read->trading_state == written->trading_state);
}

/* Trading State Message: written and read back, then read and written back */
static void check_trading_state_message(void) {
  TradingStateMessage sent;
  TradingStateMessage got;
  uint8_t wire[13];
  uint8_t again[13];

  any_trading_state_message(&sent);
  assert(encode_trading_state_message(&sent, wire, 0) == 13);
  assert(decode_trading_state_message(&got, wire, 0) == 13);
  equal_trading_state_message(&got, &sent);

  for (size_t i = 0; i < 13; i++) { wire[i] = arbitrary(); }
  assert(decode_trading_state_message(&got, wire, 0) == 13);
  assert(encode_trading_state_message(&got, again, 0) == 13);
  for (size_t i = 0; i < 13; i++) { assert(again[i] == wire[i]); }
}

/* ---- Short Selling Price Restriction State Message: 13 bytes ----------------- */

/* The Short Selling Price Restriction State Message is used to indicate the current short selling price restriction state of an orderbook */
typedef struct {
  uint8_t nanoseconds[4];       /* bytes 0 to 3 */
  uint8_t orderbook_id[4];      /* bytes 4 to 7 */
  uint8_t group[4];             /* bytes 8 to 11 */
  uint8_t short_selling_state;  /* byte 12 */
} ShortSellingPriceRestrictionStateMessage;

/* any Short Selling Price Restriction State Message at all: every byte one the checker chooses */
static void any_short_selling_price_restriction_state_message(ShortSellingPriceRestrictionStateMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->orderbook_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->group[i] = arbitrary(); }
  record->short_selling_state = arbitrary();
}

/* Short Selling Price Restriction State Message to the wire: 13 bytes from at, returning where the next byte goes */
static size_t encode_short_selling_price_restriction_state_message(const ShortSellingPriceRestrictionStateMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->nanoseconds[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->orderbook_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->group[i]; }
  wire[at++] = record->short_selling_state;

  return at;
}

/* Short Selling Price Restriction State Message off the wire: 13 bytes from at, returning where the next byte lies */
static size_t decode_short_selling_price_restriction_state_message(ShortSellingPriceRestrictionStateMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->orderbook_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->group[i] = wire[at++]; }
  record->short_selling_state = wire[at++];

  return at;
}

/* what was read of Short Selling Price Restriction State Message is what was written, byte for byte */
static void equal_short_selling_price_restriction_state_message(const ShortSellingPriceRestrictionStateMessage *read, const ShortSellingPriceRestrictionStateMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->nanoseconds[i] == written->nanoseconds[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->orderbook_id[i] == written->orderbook_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->group[i] == written->group[i]); }
  assert(read->short_selling_state == written->short_selling_state);
}

/* Short Selling Price Restriction State Message: written and read back, then read and written back */
static void check_short_selling_price_restriction_state_message(void) {
  ShortSellingPriceRestrictionStateMessage sent;
  ShortSellingPriceRestrictionStateMessage got;
  uint8_t wire[13];
  uint8_t again[13];

  any_short_selling_price_restriction_state_message(&sent);
  assert(encode_short_selling_price_restriction_state_message(&sent, wire, 0) == 13);
  assert(decode_short_selling_price_restriction_state_message(&got, wire, 0) == 13);
  equal_short_selling_price_restriction_state_message(&got, &sent);

  for (size_t i = 0; i < 13; i++) { wire[i] = arbitrary(); }
  assert(decode_short_selling_price_restriction_state_message(&got, wire, 0) == 13);
  assert(encode_short_selling_price_restriction_state_message(&got, again, 0) == 13);
  for (size_t i = 0; i < 13; i++) { assert(again[i] == wire[i]); }
}

/* ---- Order Added Message: 29 bytes ------------------------------------------- */

/* An Order Added Message is generated each time a new order is accepted by the ODX PTS execution system */
typedef struct {
  uint8_t nanoseconds[4];      /* bytes 0 to 3 */
  uint8_t order_number[8];     /* bytes 4 to 11 */
  uint8_t buy_sell_indicator;  /* byte 12 */
  uint8_t quantity[4];         /* bytes 13 to 16 */
  uint8_t orderbook_id[4];     /* bytes 17 to 20 */
  uint8_t group[4];            /* bytes 21 to 24 */
  uint8_t price[4];            /* bytes 25 to 28 */
} OrderAddedMessage;

/* any Order Added Message at all: every byte one the checker chooses */
static void any_order_added_message(OrderAddedMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->order_number[i] = arbitrary(); }
  record->buy_sell_indicator = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->orderbook_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->group[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->price[i] = arbitrary(); }
}

/* Order Added Message to the wire: 29 bytes from at, returning where the next byte goes */
static size_t encode_order_added_message(const OrderAddedMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->nanoseconds[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_number[i]; }
  wire[at++] = record->buy_sell_indicator;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->quantity[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->orderbook_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->group[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->price[i]; }

  return at;
}

/* Order Added Message off the wire: 29 bytes from at, returning where the next byte lies */
static size_t decode_order_added_message(OrderAddedMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->order_number[i] = wire[at++]; }
  record->buy_sell_indicator = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->orderbook_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->group[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->price[i] = wire[at++]; }

  return at;
}

/* what was read of Order Added Message is what was written, byte for byte */
static void equal_order_added_message(const OrderAddedMessage *read, const OrderAddedMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->nanoseconds[i] == written->nanoseconds[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->order_number[i] == written->order_number[i]); }
  assert(read->buy_sell_indicator == written->buy_sell_indicator);
  for (size_t i = 0; i < 4; i++) { assert(read->quantity[i] == written->quantity[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->orderbook_id[i] == written->orderbook_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->group[i] == written->group[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->price[i] == written->price[i]); }
}

/* Order Added Message: written and read back, then read and written back */
static void check_order_added_message(void) {
  OrderAddedMessage sent;
  OrderAddedMessage got;
  uint8_t wire[29];
  uint8_t again[29];

  any_order_added_message(&sent);
  assert(encode_order_added_message(&sent, wire, 0) == 29);
  assert(decode_order_added_message(&got, wire, 0) == 29);
  equal_order_added_message(&got, &sent);

  for (size_t i = 0; i < 29; i++) { wire[i] = arbitrary(); }
  assert(decode_order_added_message(&got, wire, 0) == 29);
  assert(encode_order_added_message(&got, again, 0) == 29);
  for (size_t i = 0; i < 29; i++) { assert(again[i] == wire[i]); }
}

/* ---- Order Executed Message: 24 bytes ---------------------------------------- */

/* An Order Executed Message is sent whenever an order on the book is executed in whole or in part */
typedef struct {
  uint8_t nanoseconds[4];        /* bytes 0 to 3 */
  uint8_t order_number[8];       /* bytes 4 to 11 */
  uint8_t executed_quantity[4];  /* bytes 12 to 15 */
  uint8_t match_number[8];       /* bytes 16 to 23 */
} OrderExecutedMessage;

/* any Order Executed Message at all: every byte one the checker chooses */
static void any_order_executed_message(OrderExecutedMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->order_number[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->executed_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->match_number[i] = arbitrary(); }
}

/* Order Executed Message to the wire: 24 bytes from at, returning where the next byte goes */
static size_t encode_order_executed_message(const OrderExecutedMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->nanoseconds[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_number[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->executed_quantity[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->match_number[i]; }

  return at;
}

/* Order Executed Message off the wire: 24 bytes from at, returning where the next byte lies */
static size_t decode_order_executed_message(OrderExecutedMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->order_number[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->executed_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->match_number[i] = wire[at++]; }

  return at;
}

/* what was read of Order Executed Message is what was written, byte for byte */
static void equal_order_executed_message(const OrderExecutedMessage *read, const OrderExecutedMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->nanoseconds[i] == written->nanoseconds[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->order_number[i] == written->order_number[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->executed_quantity[i] == written->executed_quantity[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->match_number[i] == written->match_number[i]); }
}

/* Order Executed Message: written and read back, then read and written back */
static void check_order_executed_message(void) {
  OrderExecutedMessage sent;
  OrderExecutedMessage got;
  uint8_t wire[24];
  uint8_t again[24];

  any_order_executed_message(&sent);
  assert(encode_order_executed_message(&sent, wire, 0) == 24);
  assert(decode_order_executed_message(&got, wire, 0) == 24);
  equal_order_executed_message(&got, &sent);

  for (size_t i = 0; i < 24; i++) { wire[i] = arbitrary(); }
  assert(decode_order_executed_message(&got, wire, 0) == 24);
  assert(encode_order_executed_message(&got, again, 0) == 24);
  for (size_t i = 0; i < 24; i++) { assert(again[i] == wire[i]); }
}

/* ---- Order Deleted Message: 12 bytes ----------------------------------------- */

/* An Order Deleted Message is sent whenever an order on the book is cancelled */
typedef struct {
  uint8_t nanoseconds[4];   /* bytes 0 to 3 */
  uint8_t order_number[8];  /* bytes 4 to 11 */
} OrderDeletedMessage;

/* any Order Deleted Message at all: every byte one the checker chooses */
static void any_order_deleted_message(OrderDeletedMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->order_number[i] = arbitrary(); }
}

/* Order Deleted Message to the wire: 12 bytes from at, returning where the next byte goes */
static size_t encode_order_deleted_message(const OrderDeletedMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->nanoseconds[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_number[i]; }

  return at;
}

/* Order Deleted Message off the wire: 12 bytes from at, returning where the next byte lies */
static size_t decode_order_deleted_message(OrderDeletedMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->order_number[i] = wire[at++]; }

  return at;
}

/* what was read of Order Deleted Message is what was written, byte for byte */
static void equal_order_deleted_message(const OrderDeletedMessage *read, const OrderDeletedMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->nanoseconds[i] == written->nanoseconds[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->order_number[i] == written->order_number[i]); }
}

/* Order Deleted Message: written and read back, then read and written back */
static void check_order_deleted_message(void) {
  OrderDeletedMessage sent;
  OrderDeletedMessage got;
  uint8_t wire[12];
  uint8_t again[12];

  any_order_deleted_message(&sent);
  assert(encode_order_deleted_message(&sent, wire, 0) == 12);
  assert(decode_order_deleted_message(&got, wire, 0) == 12);
  equal_order_deleted_message(&got, &sent);

  for (size_t i = 0; i < 12; i++) { wire[i] = arbitrary(); }
  assert(decode_order_deleted_message(&got, wire, 0) == 12);
  assert(encode_order_deleted_message(&got, again, 0) == 12);
  for (size_t i = 0; i < 12; i++) { assert(again[i] == wire[i]); }
}

/* ---- Order Replaced Message: 28 bytes ---------------------------------------- */

/* An Order Replaced Message is sent whenever an order on the book is replaced */
typedef struct {
  uint8_t nanoseconds[4];            /* bytes 0 to 3 */
  uint8_t original_order_number[8];  /* bytes 4 to 11 */
  uint8_t new_order_number[8];       /* bytes 12 to 19 */
  uint8_t quantity[4];               /* bytes 20 to 23 */
  uint8_t price[4];                  /* bytes 24 to 27 */
} OrderReplacedMessage;

/* any Order Replaced Message at all: every byte one the checker chooses */
static void any_order_replaced_message(OrderReplacedMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->original_order_number[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->new_order_number[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->price[i] = arbitrary(); }
}

/* Order Replaced Message to the wire: 28 bytes from at, returning where the next byte goes */
static size_t encode_order_replaced_message(const OrderReplacedMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->nanoseconds[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->original_order_number[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->new_order_number[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->quantity[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->price[i]; }

  return at;
}

/* Order Replaced Message off the wire: 28 bytes from at, returning where the next byte lies */
static size_t decode_order_replaced_message(OrderReplacedMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->original_order_number[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->new_order_number[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->price[i] = wire[at++]; }

  return at;
}

/* what was read of Order Replaced Message is what was written, byte for byte */
static void equal_order_replaced_message(const OrderReplacedMessage *read, const OrderReplacedMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->nanoseconds[i] == written->nanoseconds[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->original_order_number[i] == written->original_order_number[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->new_order_number[i] == written->new_order_number[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->quantity[i] == written->quantity[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->price[i] == written->price[i]); }
}

/* Order Replaced Message: written and read back, then read and written back */
static void check_order_replaced_message(void) {
  OrderReplacedMessage sent;
  OrderReplacedMessage got;
  uint8_t wire[28];
  uint8_t again[28];

  any_order_replaced_message(&sent);
  assert(encode_order_replaced_message(&sent, wire, 0) == 28);
  assert(decode_order_replaced_message(&got, wire, 0) == 28);
  equal_order_replaced_message(&got, &sent);

  for (size_t i = 0; i < 28; i++) { wire[i] = arbitrary(); }
  assert(decode_order_replaced_message(&got, wire, 0) == 28);
  assert(encode_order_replaced_message(&got, again, 0) == 28);
  for (size_t i = 0; i < 28; i++) { assert(again[i] == wire[i]); }
}

/* ---- What esbmc checks ------------------------------------------------------- */

/* every record of the protocol, each on its own buffers */
static void checks(void) {
  check_server_packet_header();
  check_login_accepted_packet();
  check_login_rejected_packet();
  check_seconds_message();
  check_system_event_message();
  check_price_tick_size_message();
  check_orderbook_directory_message();
  check_trading_state_message();
  check_short_selling_price_restriction_state_message();
  check_order_added_message();
  check_order_executed_message();
  check_order_deleted_message();
  check_order_replaced_message();
}

int main(void) {
#ifdef CONCRETE
  for (pattern = 0; pattern < 4; pattern++) { checks(); }
#else
  checks();
#endif

  return 0;
}
