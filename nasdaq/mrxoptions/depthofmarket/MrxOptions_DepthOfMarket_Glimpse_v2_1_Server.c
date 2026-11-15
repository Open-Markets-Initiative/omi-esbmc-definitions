// nasdaq/mrxoptions/depthofmarket/MrxOptions_DepthOfMarket_Glimpse_v2_1_Server.c
/*
 * National Association of Securities Dealers Automated Quotations (Nasdaq) Depth Of Market
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

/* ---- System Event Message: 11 bytes ------------------------------------------ */

/* The system event message type is used to signal a market or data feed handler event. */
typedef struct {
  uint8_t tracking_number[2];  /* bytes 0 to 1 */
  uint8_t timestamp[8];        /* bytes 2 to 9 */
  uint8_t event_code;          /* byte 10 */
} SystemEventMessage;

/* any System Event Message at all: every byte one the checker chooses */
static void any_system_event_message(SystemEventMessage *record) {
  for (size_t i = 0; i < 2; i++) { record->tracking_number[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
  record->event_code = arbitrary();
}

/* System Event Message to the wire: 11 bytes from at, returning where the next byte goes */
static size_t encode_system_event_message(const SystemEventMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->tracking_number[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }
  wire[at++] = record->event_code;

  return at;
}

/* System Event Message off the wire: 11 bytes from at, returning where the next byte lies */
static size_t decode_system_event_message(SystemEventMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->tracking_number[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }
  record->event_code = wire[at++];

  return at;
}

/* what was read of System Event Message is what was written, byte for byte */
static void equal_system_event_message(const SystemEventMessage *read, const SystemEventMessage *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->tracking_number[i] == written->tracking_number[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  assert(read->event_code == written->event_code);
}

/* System Event Message: written and read back, then read and written back */
static void check_system_event_message(void) {
  SystemEventMessage sent;
  SystemEventMessage got;
  uint8_t wire[11];
  uint8_t again[11];

  any_system_event_message(&sent);
  assert(encode_system_event_message(&sent, wire, 0) == 11);
  assert(decode_system_event_message(&got, wire, 0) == 11);
  equal_system_event_message(&got, &sent);

  for (size_t i = 0; i < 11; i++) { wire[i] = arbitrary(); }
  assert(decode_system_event_message(&got, wire, 0) == 11);
  assert(encode_system_event_message(&got, again, 0) == 11);
  for (size_t i = 0; i < 11; i++) { assert(again[i] == wire[i]); }
}

/* ---- Derivative Directory Message: 62 bytes ---------------------------------- */

/* Derivative Directory Message for active options symbols. */
typedef struct {
  uint8_t tracking_number[2];        /* bytes 0 to 1 */
  uint8_t timestamp[8];              /* bytes 2 to 9 */
  uint8_t instrument_id[4];          /* bytes 10 to 13 */
  uint8_t security_symbol[8];        /* bytes 14 to 21 */
  uint8_t expiration_year;           /* byte 22 */
  uint8_t expiration_month;          /* byte 23 */
  uint8_t expiration_day;            /* byte 24 */
  uint8_t explicit_strike_price[4];  /* bytes 25 to 28 */
  uint8_t option_type;               /* byte 29 */
  uint8_t underlying_symbol[13];     /* bytes 30 to 42 */
  uint8_t closing_type;              /* byte 43 */
  uint8_t tradable;                  /* byte 44 */
  uint8_t mpv;                       /* byte 45 */
  uint8_t reserved_16[16];           /* bytes 46 to 61 */
} DerivativeDirectoryMessage;

/* any Derivative Directory Message at all: every byte one the checker chooses */
static void any_derivative_directory_message(DerivativeDirectoryMessage *record) {
  for (size_t i = 0; i < 2; i++) { record->tracking_number[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->instrument_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->security_symbol[i] = arbitrary(); }
  record->expiration_year = arbitrary();
  record->expiration_month = arbitrary();
  record->expiration_day = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->explicit_strike_price[i] = arbitrary(); }
  record->option_type = arbitrary();
  for (size_t i = 0; i < 13; i++) { record->underlying_symbol[i] = arbitrary(); }
  record->closing_type = arbitrary();
  record->tradable = arbitrary();
  record->mpv = arbitrary();
  for (size_t i = 0; i < 16; i++) { record->reserved_16[i] = arbitrary(); }
}

/* Derivative Directory Message to the wire: 62 bytes from at, returning where the next byte goes */
static size_t encode_derivative_directory_message(const DerivativeDirectoryMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->tracking_number[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->security_symbol[i]; }
  wire[at++] = record->expiration_year;
  wire[at++] = record->expiration_month;
  wire[at++] = record->expiration_day;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->explicit_strike_price[i]; }
  wire[at++] = record->option_type;
  for (size_t i = 0; i < 13; i++) { wire[at++] = record->underlying_symbol[i]; }
  wire[at++] = record->closing_type;
  wire[at++] = record->tradable;
  wire[at++] = record->mpv;
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->reserved_16[i]; }

  return at;
}

/* Derivative Directory Message off the wire: 62 bytes from at, returning where the next byte lies */
static size_t decode_derivative_directory_message(DerivativeDirectoryMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->tracking_number[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->instrument_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->security_symbol[i] = wire[at++]; }
  record->expiration_year = wire[at++];
  record->expiration_month = wire[at++];
  record->expiration_day = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->explicit_strike_price[i] = wire[at++]; }
  record->option_type = wire[at++];
  for (size_t i = 0; i < 13; i++) { record->underlying_symbol[i] = wire[at++]; }
  record->closing_type = wire[at++];
  record->tradable = wire[at++];
  record->mpv = wire[at++];
  for (size_t i = 0; i < 16; i++) { record->reserved_16[i] = wire[at++]; }

  return at;
}

/* what was read of Derivative Directory Message is what was written, byte for byte */
static void equal_derivative_directory_message(const DerivativeDirectoryMessage *read, const DerivativeDirectoryMessage *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->tracking_number[i] == written->tracking_number[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->instrument_id[i] == written->instrument_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->security_symbol[i] == written->security_symbol[i]); }
  assert(read->expiration_year == written->expiration_year);
  assert(read->expiration_month == written->expiration_month);
  assert(read->expiration_day == written->expiration_day);
  for (size_t i = 0; i < 4; i++) { assert(read->explicit_strike_price[i] == written->explicit_strike_price[i]); }
  assert(read->option_type == written->option_type);
  for (size_t i = 0; i < 13; i++) { assert(read->underlying_symbol[i] == written->underlying_symbol[i]); }
  assert(read->closing_type == written->closing_type);
  assert(read->tradable == written->tradable);
  assert(read->mpv == written->mpv);
  for (size_t i = 0; i < 16; i++) { assert(read->reserved_16[i] == written->reserved_16[i]); }
}

/* Derivative Directory Message: written and read back, then read and written back */
static void check_derivative_directory_message(void) {
  DerivativeDirectoryMessage sent;
  DerivativeDirectoryMessage got;
  uint8_t wire[62];
  uint8_t again[62];

  any_derivative_directory_message(&sent);
  assert(encode_derivative_directory_message(&sent, wire, 0) == 62);
  assert(decode_derivative_directory_message(&got, wire, 0) == 62);
  equal_derivative_directory_message(&got, &sent);

  for (size_t i = 0; i < 62; i++) { wire[i] = arbitrary(); }
  assert(decode_derivative_directory_message(&got, wire, 0) == 62);
  assert(encode_derivative_directory_message(&got, again, 0) == 62);
  for (size_t i = 0; i < 62; i++) { assert(again[i] == wire[i]); }
}

/* ---- Trading Action Message: 15 bytes ---------------------------------------- */

/* The options system uses this administrative message to indicate the current trading status of an index or equity option within the options market. */
typedef struct {
  uint8_t tracking_number[2];     /* bytes 0 to 1 */
  uint8_t timestamp[8];           /* bytes 2 to 9 */
  uint8_t instrument_id[4];       /* bytes 10 to 13 */
  uint8_t current_trading_state;  /* byte 14 */
} TradingActionMessage;

/* any Trading Action Message at all: every byte one the checker chooses */
static void any_trading_action_message(TradingActionMessage *record) {
  for (size_t i = 0; i < 2; i++) { record->tracking_number[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->instrument_id[i] = arbitrary(); }
  record->current_trading_state = arbitrary();
}

/* Trading Action Message to the wire: 15 bytes from at, returning where the next byte goes */
static size_t encode_trading_action_message(const TradingActionMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->tracking_number[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument_id[i]; }
  wire[at++] = record->current_trading_state;

  return at;
}

/* Trading Action Message off the wire: 15 bytes from at, returning where the next byte lies */
static size_t decode_trading_action_message(TradingActionMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->tracking_number[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->instrument_id[i] = wire[at++]; }
  record->current_trading_state = wire[at++];

  return at;
}

/* what was read of Trading Action Message is what was written, byte for byte */
static void equal_trading_action_message(const TradingActionMessage *read, const TradingActionMessage *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->tracking_number[i] == written->tracking_number[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->instrument_id[i] == written->instrument_id[i]); }
  assert(read->current_trading_state == written->current_trading_state);
}

/* Trading Action Message: written and read back, then read and written back */
static void check_trading_action_message(void) {
  TradingActionMessage sent;
  TradingActionMessage got;
  uint8_t wire[15];
  uint8_t again[15];

  any_trading_action_message(&sent);
  assert(encode_trading_action_message(&sent, wire, 0) == 15);
  assert(decode_trading_action_message(&got, wire, 0) == 15);
  equal_trading_action_message(&got, &sent);

  for (size_t i = 0; i < 15; i++) { wire[i] = arbitrary(); }
  assert(decode_trading_action_message(&got, wire, 0) == 15);
  assert(encode_trading_action_message(&got, again, 0) == 15);
  for (size_t i = 0; i < 15; i++) { assert(again[i] == wire[i]); }
}

/* ---- Add Order Short Form Message: 32 bytes ---------------------------------- */

/* An Add Order Message indicates that a new order has been accepted and was added to the displayable book. */
typedef struct {
  uint8_t tracking_number[2];         /* bytes 0 to 1 */
  uint8_t timestamp[8];               /* bytes 2 to 9 */
  uint8_t instrument_id[4];           /* bytes 10 to 13 */
  uint8_t order_reference_number[8];  /* bytes 14 to 21 */
  uint8_t side;                       /* byte 22 */
  uint8_t order_capacity;             /* byte 23 */
  uint8_t price_short[2];             /* bytes 24 to 25 */
  uint8_t volume_short[2];            /* bytes 26 to 27 */
  uint8_t reserved_4[4];              /* bytes 28 to 31 */
} AddOrderShortFormMessage;

/* any Add Order Short Form Message at all: every byte one the checker chooses */
static void any_add_order_short_form_message(AddOrderShortFormMessage *record) {
  for (size_t i = 0; i < 2; i++) { record->tracking_number[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->instrument_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->order_reference_number[i] = arbitrary(); }
  record->side = arbitrary();
  record->order_capacity = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->price_short[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->volume_short[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->reserved_4[i] = arbitrary(); }
}

/* Add Order Short Form Message to the wire: 32 bytes from at, returning where the next byte goes */
static size_t encode_add_order_short_form_message(const AddOrderShortFormMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->tracking_number[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_reference_number[i]; }
  wire[at++] = record->side;
  wire[at++] = record->order_capacity;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->price_short[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->volume_short[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->reserved_4[i]; }

  return at;
}

/* Add Order Short Form Message off the wire: 32 bytes from at, returning where the next byte lies */
static size_t decode_add_order_short_form_message(AddOrderShortFormMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->tracking_number[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->instrument_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->order_reference_number[i] = wire[at++]; }
  record->side = wire[at++];
  record->order_capacity = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->price_short[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->volume_short[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->reserved_4[i] = wire[at++]; }

  return at;
}

/* what was read of Add Order Short Form Message is what was written, byte for byte */
static void equal_add_order_short_form_message(const AddOrderShortFormMessage *read, const AddOrderShortFormMessage *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->tracking_number[i] == written->tracking_number[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->instrument_id[i] == written->instrument_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->order_reference_number[i] == written->order_reference_number[i]); }
  assert(read->side == written->side);
  assert(read->order_capacity == written->order_capacity);
  for (size_t i = 0; i < 2; i++) { assert(read->price_short[i] == written->price_short[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->volume_short[i] == written->volume_short[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->reserved_4[i] == written->reserved_4[i]); }
}

/* Add Order Short Form Message: written and read back, then read and written back */
static void check_add_order_short_form_message(void) {
  AddOrderShortFormMessage sent;
  AddOrderShortFormMessage got;
  uint8_t wire[32];
  uint8_t again[32];

  any_add_order_short_form_message(&sent);
  assert(encode_add_order_short_form_message(&sent, wire, 0) == 32);
  assert(decode_add_order_short_form_message(&got, wire, 0) == 32);
  equal_add_order_short_form_message(&got, &sent);

  for (size_t i = 0; i < 32; i++) { wire[i] = arbitrary(); }
  assert(decode_add_order_short_form_message(&got, wire, 0) == 32);
  assert(encode_add_order_short_form_message(&got, again, 0) == 32);
  for (size_t i = 0; i < 32; i++) { assert(again[i] == wire[i]); }
}

/* ---- Add Order Long Form Message: 36 bytes ----------------------------------- */

/* An Add Order Message indicates that a new order has been accepted and was added to the displayable book. */
typedef struct {
  uint8_t tracking_number[2];         /* bytes 0 to 1 */
  uint8_t timestamp[8];               /* bytes 2 to 9 */
  uint8_t instrument_id[4];           /* bytes 10 to 13 */
  uint8_t order_reference_number[8];  /* bytes 14 to 21 */
  uint8_t side;                       /* byte 22 */
  uint8_t order_capacity;             /* byte 23 */
  uint8_t price_long[4];              /* bytes 24 to 27 */
  uint8_t volume_long[4];             /* bytes 28 to 31 */
  uint8_t reserved_4[4];              /* bytes 32 to 35 */
} AddOrderLongFormMessage;

/* any Add Order Long Form Message at all: every byte one the checker chooses */
static void any_add_order_long_form_message(AddOrderLongFormMessage *record) {
  for (size_t i = 0; i < 2; i++) { record->tracking_number[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->instrument_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->order_reference_number[i] = arbitrary(); }
  record->side = arbitrary();
  record->order_capacity = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->price_long[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->volume_long[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->reserved_4[i] = arbitrary(); }
}

/* Add Order Long Form Message to the wire: 36 bytes from at, returning where the next byte goes */
static size_t encode_add_order_long_form_message(const AddOrderLongFormMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->tracking_number[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_reference_number[i]; }
  wire[at++] = record->side;
  wire[at++] = record->order_capacity;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->price_long[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->volume_long[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->reserved_4[i]; }

  return at;
}

/* Add Order Long Form Message off the wire: 36 bytes from at, returning where the next byte lies */
static size_t decode_add_order_long_form_message(AddOrderLongFormMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->tracking_number[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->instrument_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->order_reference_number[i] = wire[at++]; }
  record->side = wire[at++];
  record->order_capacity = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->price_long[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->volume_long[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->reserved_4[i] = wire[at++]; }

  return at;
}

/* what was read of Add Order Long Form Message is what was written, byte for byte */
static void equal_add_order_long_form_message(const AddOrderLongFormMessage *read, const AddOrderLongFormMessage *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->tracking_number[i] == written->tracking_number[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->instrument_id[i] == written->instrument_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->order_reference_number[i] == written->order_reference_number[i]); }
  assert(read->side == written->side);
  assert(read->order_capacity == written->order_capacity);
  for (size_t i = 0; i < 4; i++) { assert(read->price_long[i] == written->price_long[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->volume_long[i] == written->volume_long[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->reserved_4[i] == written->reserved_4[i]); }
}

/* Add Order Long Form Message: written and read back, then read and written back */
static void check_add_order_long_form_message(void) {
  AddOrderLongFormMessage sent;
  AddOrderLongFormMessage got;
  uint8_t wire[36];
  uint8_t again[36];

  any_add_order_long_form_message(&sent);
  assert(encode_add_order_long_form_message(&sent, wire, 0) == 36);
  assert(decode_add_order_long_form_message(&got, wire, 0) == 36);
  equal_add_order_long_form_message(&got, &sent);

  for (size_t i = 0; i < 36; i++) { wire[i] = arbitrary(); }
  assert(decode_add_order_long_form_message(&got, wire, 0) == 36);
  assert(encode_add_order_long_form_message(&got, again, 0) == 36);
  for (size_t i = 0; i < 36; i++) { assert(again[i] == wire[i]); }
}

/* ---- Add Quote Short Form Message: 38 bytes ---------------------------------- */

/* An Add Quote Message indicates that a new quote has been accepted and was added to the displayable book. */
typedef struct {
  uint8_t tracking_number[2];       /* bytes 0 to 1 */
  uint8_t timestamp[8];             /* bytes 2 to 9 */
  uint8_t instrument_id[4];         /* bytes 10 to 13 */
  uint8_t bid_reference_number[8];  /* bytes 14 to 21 */
  uint8_t ask_reference_number[8];  /* bytes 22 to 29 */
  uint8_t bid_price_short[2];       /* bytes 30 to 31 */
  uint8_t bid_size_short[2];        /* bytes 32 to 33 */
  uint8_t ask_price_short[2];       /* bytes 34 to 35 */
  uint8_t ask_size_short[2];        /* bytes 36 to 37 */
} AddQuoteShortFormMessage;

/* any Add Quote Short Form Message at all: every byte one the checker chooses */
static void any_add_quote_short_form_message(AddQuoteShortFormMessage *record) {
  for (size_t i = 0; i < 2; i++) { record->tracking_number[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->instrument_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->bid_reference_number[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->ask_reference_number[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->bid_price_short[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->bid_size_short[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->ask_price_short[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->ask_size_short[i] = arbitrary(); }
}

/* Add Quote Short Form Message to the wire: 38 bytes from at, returning where the next byte goes */
static size_t encode_add_quote_short_form_message(const AddQuoteShortFormMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->tracking_number[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->bid_reference_number[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->ask_reference_number[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->bid_price_short[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->bid_size_short[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->ask_price_short[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->ask_size_short[i]; }

  return at;
}

/* Add Quote Short Form Message off the wire: 38 bytes from at, returning where the next byte lies */
static size_t decode_add_quote_short_form_message(AddQuoteShortFormMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->tracking_number[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->instrument_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->bid_reference_number[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->ask_reference_number[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->bid_price_short[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->bid_size_short[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->ask_price_short[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->ask_size_short[i] = wire[at++]; }

  return at;
}

/* what was read of Add Quote Short Form Message is what was written, byte for byte */
static void equal_add_quote_short_form_message(const AddQuoteShortFormMessage *read, const AddQuoteShortFormMessage *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->tracking_number[i] == written->tracking_number[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->instrument_id[i] == written->instrument_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->bid_reference_number[i] == written->bid_reference_number[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->ask_reference_number[i] == written->ask_reference_number[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->bid_price_short[i] == written->bid_price_short[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->bid_size_short[i] == written->bid_size_short[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->ask_price_short[i] == written->ask_price_short[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->ask_size_short[i] == written->ask_size_short[i]); }
}

/* Add Quote Short Form Message: written and read back, then read and written back */
static void check_add_quote_short_form_message(void) {
  AddQuoteShortFormMessage sent;
  AddQuoteShortFormMessage got;
  uint8_t wire[38];
  uint8_t again[38];

  any_add_quote_short_form_message(&sent);
  assert(encode_add_quote_short_form_message(&sent, wire, 0) == 38);
  assert(decode_add_quote_short_form_message(&got, wire, 0) == 38);
  equal_add_quote_short_form_message(&got, &sent);

  for (size_t i = 0; i < 38; i++) { wire[i] = arbitrary(); }
  assert(decode_add_quote_short_form_message(&got, wire, 0) == 38);
  assert(encode_add_quote_short_form_message(&got, again, 0) == 38);
  for (size_t i = 0; i < 38; i++) { assert(again[i] == wire[i]); }
}

/* ---- Add Quote Long Form Message: 46 bytes ----------------------------------- */

/* An Add Quote Message indicates that a new quote has been accepted and was added to the displayable book. */
typedef struct {
  uint8_t tracking_number[2];       /* bytes 0 to 1 */
  uint8_t timestamp[8];             /* bytes 2 to 9 */
  uint8_t instrument_id[4];         /* bytes 10 to 13 */
  uint8_t bid_reference_number[8];  /* bytes 14 to 21 */
  uint8_t ask_reference_number[8];  /* bytes 22 to 29 */
  uint8_t bid_price_long[4];        /* bytes 30 to 33 */
  uint8_t bid_size_long[4];         /* bytes 34 to 37 */
  uint8_t ask_price_long[4];        /* bytes 38 to 41 */
  uint8_t ask_size_long[4];         /* bytes 42 to 45 */
} AddQuoteLongFormMessage;

/* any Add Quote Long Form Message at all: every byte one the checker chooses */
static void any_add_quote_long_form_message(AddQuoteLongFormMessage *record) {
  for (size_t i = 0; i < 2; i++) { record->tracking_number[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->instrument_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->bid_reference_number[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->ask_reference_number[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->bid_price_long[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->bid_size_long[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->ask_price_long[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->ask_size_long[i] = arbitrary(); }
}

/* Add Quote Long Form Message to the wire: 46 bytes from at, returning where the next byte goes */
static size_t encode_add_quote_long_form_message(const AddQuoteLongFormMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->tracking_number[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->bid_reference_number[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->ask_reference_number[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->bid_price_long[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->bid_size_long[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->ask_price_long[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->ask_size_long[i]; }

  return at;
}

/* Add Quote Long Form Message off the wire: 46 bytes from at, returning where the next byte lies */
static size_t decode_add_quote_long_form_message(AddQuoteLongFormMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->tracking_number[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->instrument_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->bid_reference_number[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->ask_reference_number[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->bid_price_long[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->bid_size_long[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->ask_price_long[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->ask_size_long[i] = wire[at++]; }

  return at;
}

/* what was read of Add Quote Long Form Message is what was written, byte for byte */
static void equal_add_quote_long_form_message(const AddQuoteLongFormMessage *read, const AddQuoteLongFormMessage *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->tracking_number[i] == written->tracking_number[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->instrument_id[i] == written->instrument_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->bid_reference_number[i] == written->bid_reference_number[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->ask_reference_number[i] == written->ask_reference_number[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->bid_price_long[i] == written->bid_price_long[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->bid_size_long[i] == written->bid_size_long[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->ask_price_long[i] == written->ask_price_long[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->ask_size_long[i] == written->ask_size_long[i]); }
}

/* Add Quote Long Form Message: written and read back, then read and written back */
static void check_add_quote_long_form_message(void) {
  AddQuoteLongFormMessage sent;
  AddQuoteLongFormMessage got;
  uint8_t wire[46];
  uint8_t again[46];

  any_add_quote_long_form_message(&sent);
  assert(encode_add_quote_long_form_message(&sent, wire, 0) == 46);
  assert(decode_add_quote_long_form_message(&got, wire, 0) == 46);
  equal_add_quote_long_form_message(&got, &sent);

  for (size_t i = 0; i < 46; i++) { wire[i] = arbitrary(); }
  assert(decode_add_quote_long_form_message(&got, wire, 0) == 46);
  assert(encode_add_quote_long_form_message(&got, again, 0) == 46);
  for (size_t i = 0; i < 46; i++) { assert(again[i] == wire[i]); }
}

/* ---- Snapshot Message: 20 bytes ---------------------------------------------- */

/* The Snapshot message reflects the Depth of Market sequence number at the time the GLIMPSE spin was requested. */
typedef struct {
  uint8_t sequence_number[20];  /* bytes 0 to 19 */
} SnapshotMessage;

/* any Snapshot Message at all: every byte one the checker chooses */
static void any_snapshot_message(SnapshotMessage *record) {
  for (size_t i = 0; i < 20; i++) { record->sequence_number[i] = arbitrary(); }
}

/* Snapshot Message to the wire: 20 bytes from at, returning where the next byte goes */
static size_t encode_snapshot_message(const SnapshotMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->sequence_number[i]; }

  return at;
}

/* Snapshot Message off the wire: 20 bytes from at, returning where the next byte lies */
static size_t decode_snapshot_message(SnapshotMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 20; i++) { record->sequence_number[i] = wire[at++]; }

  return at;
}

/* what was read of Snapshot Message is what was written, byte for byte */
static void equal_snapshot_message(const SnapshotMessage *read, const SnapshotMessage *written) {
  for (size_t i = 0; i < 20; i++) { assert(read->sequence_number[i] == written->sequence_number[i]); }
}

/* Snapshot Message: written and read back, then read and written back */
static void check_snapshot_message(void) {
  SnapshotMessage sent;
  SnapshotMessage got;
  uint8_t wire[20];
  uint8_t again[20];

  any_snapshot_message(&sent);
  assert(encode_snapshot_message(&sent, wire, 0) == 20);
  assert(decode_snapshot_message(&got, wire, 0) == 20);
  equal_snapshot_message(&got, &sent);

  for (size_t i = 0; i < 20; i++) { wire[i] = arbitrary(); }
  assert(decode_snapshot_message(&got, wire, 0) == 20);
  assert(encode_snapshot_message(&got, again, 0) == 20);
  for (size_t i = 0; i < 20; i++) { assert(again[i] == wire[i]); }
}

/* ---- What esbmc checks ------------------------------------------------------- */

/* every record of the protocol, each on its own buffers */
static void checks(void) {
  check_server_packet_header();
  check_login_accepted_packet();
  check_login_rejected_packet();
  check_system_event_message();
  check_derivative_directory_message();
  check_trading_action_message();
  check_add_order_short_form_message();
  check_add_order_long_form_message();
  check_add_quote_short_form_message();
  check_add_quote_long_form_message();
  check_snapshot_message();
}

int main(void) {
#ifdef CONCRETE
  for (pattern = 0; pattern < 4; pattern++) { checks(); }
#else
  checks();
#endif

  return 0;
}
