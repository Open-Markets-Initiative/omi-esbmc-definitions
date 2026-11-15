// nasdaq/nomoptions/otto/NomOptions_Otto_v3_0_0_Server.c
/*
 * National Association of Securities Dealers Automated Quotations (Nasdaq) Ouch to Trade Options
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

/* System Event message informs of a market or a session-level event. */
typedef struct {
  uint8_t timestamp[8];  /* bytes 0 to 7 */
  uint8_t event_code;    /* byte 8 */
  uint8_t version;       /* byte 9 */
  uint8_t sub_version;   /* byte 10 */
} SystemEventMessage;

/* any System Event Message at all: every byte one the checker chooses */
static void any_system_event_message(SystemEventMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
  record->event_code = arbitrary();
  record->version = arbitrary();
  record->sub_version = arbitrary();
}

/* System Event Message to the wire: 11 bytes from at, returning where the next byte goes */
static size_t encode_system_event_message(const SystemEventMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }
  wire[at++] = record->event_code;
  wire[at++] = record->version;
  wire[at++] = record->sub_version;

  return at;
}

/* System Event Message off the wire: 11 bytes from at, returning where the next byte lies */
static size_t decode_system_event_message(SystemEventMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }
  record->event_code = wire[at++];
  record->version = wire[at++];
  record->sub_version = wire[at++];

  return at;
}

/* what was read of System Event Message is what was written, byte for byte */
static void equal_system_event_message(const SystemEventMessage *read, const SystemEventMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  assert(read->event_code == written->event_code);
  assert(read->version == written->version);
  assert(read->sub_version == written->sub_version);
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

/* ---- Simple Instrument Directory Message: 69 bytes --------------------------- */

/* At the start of each trading day and during intra-day market state changes, the system disseminates directory messages for all symbols trading on the system. */
typedef struct {
  uint8_t timestamp[8];        /* bytes 0 to 7 */
  uint8_t product_id[2];       /* bytes 8 to 9 */
  uint8_t product_name[13];    /* bytes 10 to 22 */
  uint8_t instrument_id[4];    /* bytes 23 to 26 */
  uint8_t expir_year;          /* byte 27 */
  uint8_t expir_mon;           /* byte 28 */
  uint8_t expir_day;           /* byte 29 */
  uint8_t strike_price[8];     /* bytes 30 to 37 */
  uint8_t option_type;         /* byte 38 */
  uint8_t closing_type;        /* byte 39 */
  uint8_t tradable;            /* byte 40 */
  uint8_t closing_only;        /* byte 41 */
  uint8_t contract_size[2];    /* bytes 42 to 43 */
  uint8_t mpv;                 /* byte 44 */
  uint8_t security_symbol[8];  /* bytes 45 to 52 */
  uint8_t reserved_16[16];     /* bytes 53 to 68 */
} SimpleInstrumentDirectoryMessage;

/* any Simple Instrument Directory Message at all: every byte one the checker chooses */
static void any_simple_instrument_directory_message(SimpleInstrumentDirectoryMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->product_id[i] = arbitrary(); }
  for (size_t i = 0; i < 13; i++) { record->product_name[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->instrument_id[i] = arbitrary(); }
  record->expir_year = arbitrary();
  record->expir_mon = arbitrary();
  record->expir_day = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->strike_price[i] = arbitrary(); }
  record->option_type = arbitrary();
  record->closing_type = arbitrary();
  record->tradable = arbitrary();
  record->closing_only = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->contract_size[i] = arbitrary(); }
  record->mpv = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->security_symbol[i] = arbitrary(); }
  for (size_t i = 0; i < 16; i++) { record->reserved_16[i] = arbitrary(); }
}

/* Simple Instrument Directory Message to the wire: 69 bytes from at, returning where the next byte goes */
static size_t encode_simple_instrument_directory_message(const SimpleInstrumentDirectoryMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->product_id[i]; }
  for (size_t i = 0; i < 13; i++) { wire[at++] = record->product_name[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument_id[i]; }
  wire[at++] = record->expir_year;
  wire[at++] = record->expir_mon;
  wire[at++] = record->expir_day;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->strike_price[i]; }
  wire[at++] = record->option_type;
  wire[at++] = record->closing_type;
  wire[at++] = record->tradable;
  wire[at++] = record->closing_only;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->contract_size[i]; }
  wire[at++] = record->mpv;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->security_symbol[i]; }
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->reserved_16[i]; }

  return at;
}

/* Simple Instrument Directory Message off the wire: 69 bytes from at, returning where the next byte lies */
static size_t decode_simple_instrument_directory_message(SimpleInstrumentDirectoryMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->product_id[i] = wire[at++]; }
  for (size_t i = 0; i < 13; i++) { record->product_name[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->instrument_id[i] = wire[at++]; }
  record->expir_year = wire[at++];
  record->expir_mon = wire[at++];
  record->expir_day = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->strike_price[i] = wire[at++]; }
  record->option_type = wire[at++];
  record->closing_type = wire[at++];
  record->tradable = wire[at++];
  record->closing_only = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->contract_size[i] = wire[at++]; }
  record->mpv = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->security_symbol[i] = wire[at++]; }
  for (size_t i = 0; i < 16; i++) { record->reserved_16[i] = wire[at++]; }

  return at;
}

/* what was read of Simple Instrument Directory Message is what was written, byte for byte */
static void equal_simple_instrument_directory_message(const SimpleInstrumentDirectoryMessage *read, const SimpleInstrumentDirectoryMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->product_id[i] == written->product_id[i]); }
  for (size_t i = 0; i < 13; i++) { assert(read->product_name[i] == written->product_name[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->instrument_id[i] == written->instrument_id[i]); }
  assert(read->expir_year == written->expir_year);
  assert(read->expir_mon == written->expir_mon);
  assert(read->expir_day == written->expir_day);
  for (size_t i = 0; i < 8; i++) { assert(read->strike_price[i] == written->strike_price[i]); }
  assert(read->option_type == written->option_type);
  assert(read->closing_type == written->closing_type);
  assert(read->tradable == written->tradable);
  assert(read->closing_only == written->closing_only);
  for (size_t i = 0; i < 2; i++) { assert(read->contract_size[i] == written->contract_size[i]); }
  assert(read->mpv == written->mpv);
  for (size_t i = 0; i < 8; i++) { assert(read->security_symbol[i] == written->security_symbol[i]); }
  for (size_t i = 0; i < 16; i++) { assert(read->reserved_16[i] == written->reserved_16[i]); }
}

/* Simple Instrument Directory Message: written and read back, then read and written back */
static void check_simple_instrument_directory_message(void) {
  SimpleInstrumentDirectoryMessage sent;
  SimpleInstrumentDirectoryMessage got;
  uint8_t wire[69];
  uint8_t again[69];

  any_simple_instrument_directory_message(&sent);
  assert(encode_simple_instrument_directory_message(&sent, wire, 0) == 69);
  assert(decode_simple_instrument_directory_message(&got, wire, 0) == 69);
  equal_simple_instrument_directory_message(&got, &sent);

  for (size_t i = 0; i < 69; i++) { wire[i] = arbitrary(); }
  assert(decode_simple_instrument_directory_message(&got, wire, 0) == 69);
  assert(encode_simple_instrument_directory_message(&got, again, 0) == 69);
  for (size_t i = 0; i < 69; i++) { assert(again[i] == wire[i]); }
}

/* ---- Instrument Trading Action Message: 15 bytes ----------------------------- */

/* This message notifies of changes to the trading status of an instrument. */
typedef struct {
  uint8_t timestamp[8];      /* bytes 0 to 7 */
  uint8_t product_id[2];     /* bytes 8 to 9 */
  uint8_t instrument_id[4];  /* bytes 10 to 13 */
  uint8_t trading_state;     /* byte 14 */
} InstrumentTradingActionMessage;

/* any Instrument Trading Action Message at all: every byte one the checker chooses */
static void any_instrument_trading_action_message(InstrumentTradingActionMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->product_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->instrument_id[i] = arbitrary(); }
  record->trading_state = arbitrary();
}

/* Instrument Trading Action Message to the wire: 15 bytes from at, returning where the next byte goes */
static size_t encode_instrument_trading_action_message(const InstrumentTradingActionMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->product_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument_id[i]; }
  wire[at++] = record->trading_state;

  return at;
}

/* Instrument Trading Action Message off the wire: 15 bytes from at, returning where the next byte lies */
static size_t decode_instrument_trading_action_message(InstrumentTradingActionMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->product_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->instrument_id[i] = wire[at++]; }
  record->trading_state = wire[at++];

  return at;
}

/* what was read of Instrument Trading Action Message is what was written, byte for byte */
static void equal_instrument_trading_action_message(const InstrumentTradingActionMessage *read, const InstrumentTradingActionMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->product_id[i] == written->product_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->instrument_id[i] == written->instrument_id[i]); }
  assert(read->trading_state == written->trading_state);
}

/* Instrument Trading Action Message: written and read back, then read and written back */
static void check_instrument_trading_action_message(void) {
  InstrumentTradingActionMessage sent;
  InstrumentTradingActionMessage got;
  uint8_t wire[15];
  uint8_t again[15];

  any_instrument_trading_action_message(&sent);
  assert(encode_instrument_trading_action_message(&sent, wire, 0) == 15);
  assert(decode_instrument_trading_action_message(&got, wire, 0) == 15);
  equal_instrument_trading_action_message(&got, &sent);

  for (size_t i = 0; i < 15; i++) { wire[i] = arbitrary(); }
  assert(decode_instrument_trading_action_message(&got, wire, 0) == 15);
  assert(encode_instrument_trading_action_message(&got, again, 0) == 15);
  for (size_t i = 0; i < 15; i++) { assert(again[i] == wire[i]); }
}

/* ---- Order Accepted Short Form Message: 65 bytes ----------------------------- */

/* This message is used to acknowledge a valid order submitted via New Order (Short Form). */
typedef struct {
  uint8_t timestamp[8];             /* bytes 0 to 7 */
  uint8_t firm_id[4];               /* bytes 8 to 11 */
  uint8_t instrument_id[4];         /* bytes 12 to 15 */
  uint8_t order_id[8];              /* bytes 16 to 23 */
  uint8_t cl_ord_id[16];            /* bytes 24 to 39 */
  uint8_t alo_inst;                 /* byte 40 */
  uint8_t iso;                      /* byte 41 */
  uint8_t side;                     /* byte 42 */
  uint8_t order_type;               /* byte 43 */
  uint8_t price[8];                 /* bytes 44 to 51 */
  uint8_t quantity_short[2];        /* bytes 52 to 53 */
  uint8_t tif;                      /* byte 54 */
  uint8_t capacity;                 /* byte 55 */
  uint8_t auction_type;             /* byte 56 */
  uint8_t auction_id[4];            /* bytes 57 to 60 */
  uint8_t price_protection;         /* byte 61 */
  uint8_t position_effect_mask[2];  /* bytes 62 to 63 */
  uint8_t stock_capacity;           /* byte 64 */
} OrderAcceptedShortFormMessage;

/* any Order Accepted Short Form Message at all: every byte one the checker chooses */
static void any_order_accepted_short_form_message(OrderAcceptedShortFormMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->firm_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->instrument_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 16; i++) { record->cl_ord_id[i] = arbitrary(); }
  record->alo_inst = arbitrary();
  record->iso = arbitrary();
  record->side = arbitrary();
  record->order_type = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->price[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->quantity_short[i] = arbitrary(); }
  record->tif = arbitrary();
  record->capacity = arbitrary();
  record->auction_type = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->auction_id[i] = arbitrary(); }
  record->price_protection = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->position_effect_mask[i] = arbitrary(); }
  record->stock_capacity = arbitrary();
}

/* Order Accepted Short Form Message to the wire: 65 bytes from at, returning where the next byte goes */
static size_t encode_order_accepted_short_form_message(const OrderAcceptedShortFormMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->firm_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_id[i]; }
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->cl_ord_id[i]; }
  wire[at++] = record->alo_inst;
  wire[at++] = record->iso;
  wire[at++] = record->side;
  wire[at++] = record->order_type;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->quantity_short[i]; }
  wire[at++] = record->tif;
  wire[at++] = record->capacity;
  wire[at++] = record->auction_type;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->auction_id[i]; }
  wire[at++] = record->price_protection;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->position_effect_mask[i]; }
  wire[at++] = record->stock_capacity;

  return at;
}

/* Order Accepted Short Form Message off the wire: 65 bytes from at, returning where the next byte lies */
static size_t decode_order_accepted_short_form_message(OrderAcceptedShortFormMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->firm_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->instrument_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 16; i++) { record->cl_ord_id[i] = wire[at++]; }
  record->alo_inst = wire[at++];
  record->iso = wire[at++];
  record->side = wire[at++];
  record->order_type = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->price[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->quantity_short[i] = wire[at++]; }
  record->tif = wire[at++];
  record->capacity = wire[at++];
  record->auction_type = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->auction_id[i] = wire[at++]; }
  record->price_protection = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->position_effect_mask[i] = wire[at++]; }
  record->stock_capacity = wire[at++];

  return at;
}

/* what was read of Order Accepted Short Form Message is what was written, byte for byte */
static void equal_order_accepted_short_form_message(const OrderAcceptedShortFormMessage *read, const OrderAcceptedShortFormMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->firm_id[i] == written->firm_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->instrument_id[i] == written->instrument_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->order_id[i] == written->order_id[i]); }
  for (size_t i = 0; i < 16; i++) { assert(read->cl_ord_id[i] == written->cl_ord_id[i]); }
  assert(read->alo_inst == written->alo_inst);
  assert(read->iso == written->iso);
  assert(read->side == written->side);
  assert(read->order_type == written->order_type);
  for (size_t i = 0; i < 8; i++) { assert(read->price[i] == written->price[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->quantity_short[i] == written->quantity_short[i]); }
  assert(read->tif == written->tif);
  assert(read->capacity == written->capacity);
  assert(read->auction_type == written->auction_type);
  for (size_t i = 0; i < 4; i++) { assert(read->auction_id[i] == written->auction_id[i]); }
  assert(read->price_protection == written->price_protection);
  for (size_t i = 0; i < 2; i++) { assert(read->position_effect_mask[i] == written->position_effect_mask[i]); }
  assert(read->stock_capacity == written->stock_capacity);
}

/* Order Accepted Short Form Message: written and read back, then read and written back */
static void check_order_accepted_short_form_message(void) {
  OrderAcceptedShortFormMessage sent;
  OrderAcceptedShortFormMessage got;
  uint8_t wire[65];
  uint8_t again[65];

  any_order_accepted_short_form_message(&sent);
  assert(encode_order_accepted_short_form_message(&sent, wire, 0) == 65);
  assert(decode_order_accepted_short_form_message(&got, wire, 0) == 65);
  equal_order_accepted_short_form_message(&got, &sent);

  for (size_t i = 0; i < 65; i++) { wire[i] = arbitrary(); }
  assert(decode_order_accepted_short_form_message(&got, wire, 0) == 65);
  assert(encode_order_accepted_short_form_message(&got, again, 0) == 65);
  for (size_t i = 0; i < 65; i++) { assert(again[i] == wire[i]); }
}

/* ---- Order Replaced Message: 100 bytes --------------------------------------- */

/* Acknowledges a Replace Order request. */
typedef struct {
  uint8_t timestamp[8];             /* bytes 0 to 7 */
  uint8_t firm_id[4];               /* bytes 8 to 11 */
  uint8_t instrument_id[4];         /* bytes 12 to 15 */
  uint8_t orig_order_id[8];         /* bytes 16 to 23 */
  uint8_t order_id[8];              /* bytes 24 to 31 */
  uint8_t orig_cl_ord_id[16];       /* bytes 32 to 47 */
  uint8_t cl_ord_id[16];            /* bytes 48 to 63 */
  uint8_t alo_inst;                 /* byte 64 */
  uint8_t iso;                      /* byte 65 */
  uint8_t side;                     /* byte 66 */
  uint8_t order_type;               /* byte 67 */
  uint8_t price[8];                 /* bytes 68 to 75 */
  uint8_t quantity[4];              /* bytes 76 to 79 */
  uint8_t tif;                      /* byte 80 */
  uint8_t cust_acct[10];            /* bytes 81 to 90 */
  uint8_t capacity;                 /* byte 91 */
  uint8_t auction_type;             /* byte 92 */
  uint8_t auction_id[4];            /* bytes 93 to 96 */
  uint8_t position_effect_mask[2];  /* bytes 97 to 98 */
  uint8_t price_protection;         /* byte 99 */
} OrderReplacedMessage;

/* any Order Replaced Message at all: every byte one the checker chooses */
static void any_order_replaced_message(OrderReplacedMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->firm_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->instrument_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->orig_order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 16; i++) { record->orig_cl_ord_id[i] = arbitrary(); }
  for (size_t i = 0; i < 16; i++) { record->cl_ord_id[i] = arbitrary(); }
  record->alo_inst = arbitrary();
  record->iso = arbitrary();
  record->side = arbitrary();
  record->order_type = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->quantity[i] = arbitrary(); }
  record->tif = arbitrary();
  for (size_t i = 0; i < 10; i++) { record->cust_acct[i] = arbitrary(); }
  record->capacity = arbitrary();
  record->auction_type = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->auction_id[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->position_effect_mask[i] = arbitrary(); }
  record->price_protection = arbitrary();
}

/* Order Replaced Message to the wire: 100 bytes from at, returning where the next byte goes */
static size_t encode_order_replaced_message(const OrderReplacedMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->firm_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->orig_order_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_id[i]; }
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->orig_cl_ord_id[i]; }
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->cl_ord_id[i]; }
  wire[at++] = record->alo_inst;
  wire[at++] = record->iso;
  wire[at++] = record->side;
  wire[at++] = record->order_type;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->quantity[i]; }
  wire[at++] = record->tif;
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->cust_acct[i]; }
  wire[at++] = record->capacity;
  wire[at++] = record->auction_type;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->auction_id[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->position_effect_mask[i]; }
  wire[at++] = record->price_protection;

  return at;
}

/* Order Replaced Message off the wire: 100 bytes from at, returning where the next byte lies */
static size_t decode_order_replaced_message(OrderReplacedMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->firm_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->instrument_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->orig_order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 16; i++) { record->orig_cl_ord_id[i] = wire[at++]; }
  for (size_t i = 0; i < 16; i++) { record->cl_ord_id[i] = wire[at++]; }
  record->alo_inst = wire[at++];
  record->iso = wire[at++];
  record->side = wire[at++];
  record->order_type = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->quantity[i] = wire[at++]; }
  record->tif = wire[at++];
  for (size_t i = 0; i < 10; i++) { record->cust_acct[i] = wire[at++]; }
  record->capacity = wire[at++];
  record->auction_type = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->auction_id[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->position_effect_mask[i] = wire[at++]; }
  record->price_protection = wire[at++];

  return at;
}

/* what was read of Order Replaced Message is what was written, byte for byte */
static void equal_order_replaced_message(const OrderReplacedMessage *read, const OrderReplacedMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->firm_id[i] == written->firm_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->instrument_id[i] == written->instrument_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->orig_order_id[i] == written->orig_order_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->order_id[i] == written->order_id[i]); }
  for (size_t i = 0; i < 16; i++) { assert(read->orig_cl_ord_id[i] == written->orig_cl_ord_id[i]); }
  for (size_t i = 0; i < 16; i++) { assert(read->cl_ord_id[i] == written->cl_ord_id[i]); }
  assert(read->alo_inst == written->alo_inst);
  assert(read->iso == written->iso);
  assert(read->side == written->side);
  assert(read->order_type == written->order_type);
  for (size_t i = 0; i < 8; i++) { assert(read->price[i] == written->price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->quantity[i] == written->quantity[i]); }
  assert(read->tif == written->tif);
  for (size_t i = 0; i < 10; i++) { assert(read->cust_acct[i] == written->cust_acct[i]); }
  assert(read->capacity == written->capacity);
  assert(read->auction_type == written->auction_type);
  for (size_t i = 0; i < 4; i++) { assert(read->auction_id[i] == written->auction_id[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->position_effect_mask[i] == written->position_effect_mask[i]); }
  assert(read->price_protection == written->price_protection);
}

/* Order Replaced Message: written and read back, then read and written back */
static void check_order_replaced_message(void) {
  OrderReplacedMessage sent;
  OrderReplacedMessage got;
  uint8_t wire[100];
  uint8_t again[100];

  any_order_replaced_message(&sent);
  assert(encode_order_replaced_message(&sent, wire, 0) == 100);
  assert(decode_order_replaced_message(&got, wire, 0) == 100);
  equal_order_replaced_message(&got, &sent);

  for (size_t i = 0; i < 100; i++) { wire[i] = arbitrary(); }
  assert(decode_order_replaced_message(&got, wire, 0) == 100);
  assert(encode_order_replaced_message(&got, again, 0) == 100);
  for (size_t i = 0; i < 100; i++) { assert(again[i] == wire[i]); }
}

/* ---- Order Canceled Message: 41 bytes ---------------------------------------- */

/* An Order Canceled Message informs you that an order has been fully canceled. This could be acknowledging a Cancel Order Message, or it could be the result of the order being canceled automatically by the system. */
typedef struct {
  uint8_t timestamp[8];      /* bytes 0 to 7 */
  uint8_t firm_id[4];        /* bytes 8 to 11 */
  uint8_t instrument_id[4];  /* bytes 12 to 15 */
  uint8_t order_id[8];       /* bytes 16 to 23 */
  uint8_t cl_ord_id[16];     /* bytes 24 to 39 */
  uint8_t cancel_reason;     /* byte 40 */
} OrderCanceledMessage;

/* any Order Canceled Message at all: every byte one the checker chooses */
static void any_order_canceled_message(OrderCanceledMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->firm_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->instrument_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 16; i++) { record->cl_ord_id[i] = arbitrary(); }
  record->cancel_reason = arbitrary();
}

/* Order Canceled Message to the wire: 41 bytes from at, returning where the next byte goes */
static size_t encode_order_canceled_message(const OrderCanceledMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->firm_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_id[i]; }
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->cl_ord_id[i]; }
  wire[at++] = record->cancel_reason;

  return at;
}

/* Order Canceled Message off the wire: 41 bytes from at, returning where the next byte lies */
static size_t decode_order_canceled_message(OrderCanceledMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->firm_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->instrument_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 16; i++) { record->cl_ord_id[i] = wire[at++]; }
  record->cancel_reason = wire[at++];

  return at;
}

/* what was read of Order Canceled Message is what was written, byte for byte */
static void equal_order_canceled_message(const OrderCanceledMessage *read, const OrderCanceledMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->firm_id[i] == written->firm_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->instrument_id[i] == written->instrument_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->order_id[i] == written->order_id[i]); }
  for (size_t i = 0; i < 16; i++) { assert(read->cl_ord_id[i] == written->cl_ord_id[i]); }
  assert(read->cancel_reason == written->cancel_reason);
}

/* Order Canceled Message: written and read back, then read and written back */
static void check_order_canceled_message(void) {
  OrderCanceledMessage sent;
  OrderCanceledMessage got;
  uint8_t wire[41];
  uint8_t again[41];

  any_order_canceled_message(&sent);
  assert(encode_order_canceled_message(&sent, wire, 0) == 41);
  assert(decode_order_canceled_message(&got, wire, 0) == 41);
  equal_order_canceled_message(&got, &sent);

  for (size_t i = 0; i < 41; i++) { wire[i] = arbitrary(); }
  assert(decode_order_canceled_message(&got, wire, 0) == 41);
  assert(encode_order_canceled_message(&got, again, 0) == 41);
  for (size_t i = 0; i < 41; i++) { assert(again[i] == wire[i]); }
}

/* ---- Order Executed Message: 72 bytes ---------------------------------------- */

/* Order Executed message reports an execution of an order for a simple instrument, a complex instrument, or an option or stock leg of a complex order. */
typedef struct {
  uint8_t timestamp[8];          /* bytes 0 to 7 */
  uint8_t firm_id[4];            /* bytes 8 to 11 */
  uint8_t product_id[2];         /* bytes 12 to 13 */
  uint8_t ord_exec_type;         /* byte 14 */
  uint8_t instrument_id[4];      /* bytes 15 to 18 */
  uint8_t leg_instrument_id[4];  /* bytes 19 to 22 */
  uint8_t leg_id;                /* byte 23 */
  uint8_t auction_type;          /* byte 24 */
  uint8_t order_id[8];           /* bytes 25 to 32 */
  uint8_t cl_ord_id[16];         /* bytes 33 to 48 */
  uint8_t cross_id[4];           /* bytes 49 to 52 */
  uint8_t match_id[4];           /* bytes 53 to 56 */
  uint8_t side;                  /* byte 57 */
  uint8_t stock_leg_short_sale;  /* byte 58 */
  uint8_t price[8];              /* bytes 59 to 66 */
  uint8_t quantity[4];           /* bytes 67 to 70 */
  uint8_t liquidity_ind;         /* byte 71 */
} OrderExecutedMessage;

/* any Order Executed Message at all: every byte one the checker chooses */
static void any_order_executed_message(OrderExecutedMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->firm_id[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->product_id[i] = arbitrary(); }
  record->ord_exec_type = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->instrument_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->leg_instrument_id[i] = arbitrary(); }
  record->leg_id = arbitrary();
  record->auction_type = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 16; i++) { record->cl_ord_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->cross_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->match_id[i] = arbitrary(); }
  record->side = arbitrary();
  record->stock_leg_short_sale = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->quantity[i] = arbitrary(); }
  record->liquidity_ind = arbitrary();
}

/* Order Executed Message to the wire: 72 bytes from at, returning where the next byte goes */
static size_t encode_order_executed_message(const OrderExecutedMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->firm_id[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->product_id[i]; }
  wire[at++] = record->ord_exec_type;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->leg_instrument_id[i]; }
  wire[at++] = record->leg_id;
  wire[at++] = record->auction_type;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_id[i]; }
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->cl_ord_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->cross_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->match_id[i]; }
  wire[at++] = record->side;
  wire[at++] = record->stock_leg_short_sale;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->quantity[i]; }
  wire[at++] = record->liquidity_ind;

  return at;
}

/* Order Executed Message off the wire: 72 bytes from at, returning where the next byte lies */
static size_t decode_order_executed_message(OrderExecutedMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->firm_id[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->product_id[i] = wire[at++]; }
  record->ord_exec_type = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->instrument_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->leg_instrument_id[i] = wire[at++]; }
  record->leg_id = wire[at++];
  record->auction_type = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 16; i++) { record->cl_ord_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->cross_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->match_id[i] = wire[at++]; }
  record->side = wire[at++];
  record->stock_leg_short_sale = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->quantity[i] = wire[at++]; }
  record->liquidity_ind = wire[at++];

  return at;
}

/* what was read of Order Executed Message is what was written, byte for byte */
static void equal_order_executed_message(const OrderExecutedMessage *read, const OrderExecutedMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->firm_id[i] == written->firm_id[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->product_id[i] == written->product_id[i]); }
  assert(read->ord_exec_type == written->ord_exec_type);
  for (size_t i = 0; i < 4; i++) { assert(read->instrument_id[i] == written->instrument_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->leg_instrument_id[i] == written->leg_instrument_id[i]); }
  assert(read->leg_id == written->leg_id);
  assert(read->auction_type == written->auction_type);
  for (size_t i = 0; i < 8; i++) { assert(read->order_id[i] == written->order_id[i]); }
  for (size_t i = 0; i < 16; i++) { assert(read->cl_ord_id[i] == written->cl_ord_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->cross_id[i] == written->cross_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->match_id[i] == written->match_id[i]); }
  assert(read->side == written->side);
  assert(read->stock_leg_short_sale == written->stock_leg_short_sale);
  for (size_t i = 0; i < 8; i++) { assert(read->price[i] == written->price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->quantity[i] == written->quantity[i]); }
  assert(read->liquidity_ind == written->liquidity_ind);
}

/* Order Executed Message: written and read back, then read and written back */
static void check_order_executed_message(void) {
  OrderExecutedMessage sent;
  OrderExecutedMessage got;
  uint8_t wire[72];
  uint8_t again[72];

  any_order_executed_message(&sent);
  assert(encode_order_executed_message(&sent, wire, 0) == 72);
  assert(decode_order_executed_message(&got, wire, 0) == 72);
  equal_order_executed_message(&got, &sent);

  for (size_t i = 0; i < 72; i++) { wire[i] = arbitrary(); }
  assert(decode_order_executed_message(&got, wire, 0) == 72);
  assert(encode_order_executed_message(&got, again, 0) == 72);
  for (size_t i = 0; i < 72; i++) { assert(again[i] == wire[i]); }
}

/* ---- Trade Details Message: 107 bytes ---------------------------------------- */

/* A Trade Details message contains additional details, specifically clearing information. This message is sent out with a nominal delay after Order Executed message. Trade Busts and Adjustments are made against individual MatchIds; Modify Trade results are reported with TransType B for the original trade and C for the new trades. */
typedef struct {
  uint8_t timestamp[8];          /* bytes 0 to 7 */
  uint8_t firm_id[4];            /* bytes 8 to 11 */
  uint8_t product_id[2];         /* bytes 12 to 13 */
  uint8_t ord_exec_type;         /* byte 14 */
  uint8_t instrument_id[4];      /* bytes 15 to 18 */
  uint8_t leg_instrument_id[4];  /* bytes 19 to 22 */
  uint8_t leg_id;                /* byte 23 */
  uint8_t trans_type;            /* byte 24 */
  uint8_t event_source;          /* byte 25 */
  uint8_t auction_type;          /* byte 26 */
  uint8_t order_id[8];           /* bytes 27 to 34 */
  uint8_t cl_ord_id[16];         /* bytes 35 to 50 */
  uint8_t cross_id[4];           /* bytes 51 to 54 */
  uint8_t match_id[4];           /* bytes 55 to 58 */
  uint8_t ref_match_id[4];       /* bytes 59 to 62 */
  uint8_t side;                  /* byte 63 */
  uint8_t stock_leg_short_sale;  /* byte 64 */
  uint8_t price[8];              /* bytes 65 to 72 */
  uint8_t quantity[4];           /* bytes 73 to 76 */
  uint8_t liquidity_ind;         /* byte 77 */
  uint8_t cmta[4];               /* bytes 78 to 81 */
  uint8_t clearing_account[4];   /* bytes 82 to 85 */
  uint8_t occ_account[4];        /* bytes 86 to 89 */
  uint8_t cust_acct[10];         /* bytes 90 to 99 */
  uint8_t stock_venue;           /* byte 100 */
  uint8_t stock_leg_mpid[4];     /* bytes 101 to 104 */
  uint8_t capacity;              /* byte 105 */
  uint8_t open_close;            /* byte 106 */
} TradeDetailsMessage;

/* any Trade Details Message at all: every byte one the checker chooses */
static void any_trade_details_message(TradeDetailsMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->firm_id[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->product_id[i] = arbitrary(); }
  record->ord_exec_type = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->instrument_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->leg_instrument_id[i] = arbitrary(); }
  record->leg_id = arbitrary();
  record->trans_type = arbitrary();
  record->event_source = arbitrary();
  record->auction_type = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 16; i++) { record->cl_ord_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->cross_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->match_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->ref_match_id[i] = arbitrary(); }
  record->side = arbitrary();
  record->stock_leg_short_sale = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->quantity[i] = arbitrary(); }
  record->liquidity_ind = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->cmta[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->clearing_account[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->occ_account[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->cust_acct[i] = arbitrary(); }
  record->stock_venue = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->stock_leg_mpid[i] = arbitrary(); }
  record->capacity = arbitrary();
  record->open_close = arbitrary();
}

/* Trade Details Message to the wire: 107 bytes from at, returning where the next byte goes */
static size_t encode_trade_details_message(const TradeDetailsMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->firm_id[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->product_id[i]; }
  wire[at++] = record->ord_exec_type;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->leg_instrument_id[i]; }
  wire[at++] = record->leg_id;
  wire[at++] = record->trans_type;
  wire[at++] = record->event_source;
  wire[at++] = record->auction_type;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_id[i]; }
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->cl_ord_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->cross_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->match_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->ref_match_id[i]; }
  wire[at++] = record->side;
  wire[at++] = record->stock_leg_short_sale;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->quantity[i]; }
  wire[at++] = record->liquidity_ind;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->cmta[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->clearing_account[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->occ_account[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->cust_acct[i]; }
  wire[at++] = record->stock_venue;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->stock_leg_mpid[i]; }
  wire[at++] = record->capacity;
  wire[at++] = record->open_close;

  return at;
}

/* Trade Details Message off the wire: 107 bytes from at, returning where the next byte lies */
static size_t decode_trade_details_message(TradeDetailsMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->firm_id[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->product_id[i] = wire[at++]; }
  record->ord_exec_type = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->instrument_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->leg_instrument_id[i] = wire[at++]; }
  record->leg_id = wire[at++];
  record->trans_type = wire[at++];
  record->event_source = wire[at++];
  record->auction_type = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 16; i++) { record->cl_ord_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->cross_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->match_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->ref_match_id[i] = wire[at++]; }
  record->side = wire[at++];
  record->stock_leg_short_sale = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->quantity[i] = wire[at++]; }
  record->liquidity_ind = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->cmta[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->clearing_account[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->occ_account[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->cust_acct[i] = wire[at++]; }
  record->stock_venue = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->stock_leg_mpid[i] = wire[at++]; }
  record->capacity = wire[at++];
  record->open_close = wire[at++];

  return at;
}

/* what was read of Trade Details Message is what was written, byte for byte */
static void equal_trade_details_message(const TradeDetailsMessage *read, const TradeDetailsMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->firm_id[i] == written->firm_id[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->product_id[i] == written->product_id[i]); }
  assert(read->ord_exec_type == written->ord_exec_type);
  for (size_t i = 0; i < 4; i++) { assert(read->instrument_id[i] == written->instrument_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->leg_instrument_id[i] == written->leg_instrument_id[i]); }
  assert(read->leg_id == written->leg_id);
  assert(read->trans_type == written->trans_type);
  assert(read->event_source == written->event_source);
  assert(read->auction_type == written->auction_type);
  for (size_t i = 0; i < 8; i++) { assert(read->order_id[i] == written->order_id[i]); }
  for (size_t i = 0; i < 16; i++) { assert(read->cl_ord_id[i] == written->cl_ord_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->cross_id[i] == written->cross_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->match_id[i] == written->match_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->ref_match_id[i] == written->ref_match_id[i]); }
  assert(read->side == written->side);
  assert(read->stock_leg_short_sale == written->stock_leg_short_sale);
  for (size_t i = 0; i < 8; i++) { assert(read->price[i] == written->price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->quantity[i] == written->quantity[i]); }
  assert(read->liquidity_ind == written->liquidity_ind);
  for (size_t i = 0; i < 4; i++) { assert(read->cmta[i] == written->cmta[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->clearing_account[i] == written->clearing_account[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->occ_account[i] == written->occ_account[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->cust_acct[i] == written->cust_acct[i]); }
  assert(read->stock_venue == written->stock_venue);
  for (size_t i = 0; i < 4; i++) { assert(read->stock_leg_mpid[i] == written->stock_leg_mpid[i]); }
  assert(read->capacity == written->capacity);
  assert(read->open_close == written->open_close);
}

/* Trade Details Message: written and read back, then read and written back */
static void check_trade_details_message(void) {
  TradeDetailsMessage sent;
  TradeDetailsMessage got;
  uint8_t wire[107];
  uint8_t again[107];

  any_trade_details_message(&sent);
  assert(encode_trade_details_message(&sent, wire, 0) == 107);
  assert(decode_trade_details_message(&got, wire, 0) == 107);
  equal_trade_details_message(&got, &sent);

  for (size_t i = 0; i < 107; i++) { wire[i] = arbitrary(); }
  assert(decode_trade_details_message(&got, wire, 0) == 107);
  assert(encode_trade_details_message(&got, again, 0) == 107);
  for (size_t i = 0; i < 107; i++) { assert(again[i] == wire[i]); }
}

/* ---- Cross Order Accepted Message: 169 bytes --------------------------------- */

/* Acknowledges a valid New Cross Order. The Primary Side and Contra Side blocks of the document are carried as Primary and Contra prefixed fields. */
typedef struct {
  uint8_t timestamp[8];                     /* bytes 0 to 7 */
  uint8_t firm_id[4];                       /* bytes 8 to 11 */
  uint8_t instrument_id[4];                 /* bytes 12 to 15 */
  uint8_t cross_type;                       /* byte 16 */
  uint8_t auction_type;                     /* byte 17 */
  uint8_t auction_id[4];                    /* bytes 18 to 21 */
  uint8_t auction_alloc_pct;                /* byte 22 */
  uint8_t side;                             /* byte 23 */
  uint8_t iso;                              /* byte 24 */
  uint8_t price_protection;                 /* byte 25 */
  uint8_t effective_time[8];                /* bytes 26 to 33 */
  uint8_t disclosure_mask;                  /* byte 34 */
  uint8_t primary_order_id[8];              /* bytes 35 to 42 */
  uint8_t primary_cl_ord_id[16];            /* bytes 43 to 58 */
  uint8_t primary_cmta[4];                  /* bytes 59 to 62 */
  uint8_t primary_clearing_account[4];      /* bytes 63 to 66 */
  uint8_t primary_occ_account[4];           /* bytes 67 to 70 */
  uint8_t primary_cust_acct[10];            /* bytes 71 to 80 */
  uint8_t primary_price[8];                 /* bytes 81 to 88 */
  uint8_t primary_quantity[4];              /* bytes 89 to 92 */
  uint8_t primary_capacity;                 /* byte 93 */
  uint8_t primary_position_effect_mask[2];  /* bytes 94 to 95 */
  uint8_t primary_stock_leg_short_sale;     /* byte 96 */
  uint8_t primary_stock_leg_mpid[4];        /* bytes 97 to 100 */
  uint8_t contra_order_id[8];               /* bytes 101 to 108 */
  uint8_t contra_cl_ord_id[16];             /* bytes 109 to 124 */
  uint8_t contra_cmta[4];                   /* bytes 125 to 128 */
  uint8_t contra_clearing_account[4];       /* bytes 129 to 132 */
  uint8_t contra_occ_account[4];            /* bytes 133 to 136 */
  uint8_t contra_cust_acct[10];             /* bytes 137 to 146 */
  uint8_t contra_order_type;                /* byte 147 */
  uint8_t contra_price[8];                  /* bytes 148 to 155 */
  uint8_t contra_quantity[4];               /* bytes 156 to 159 */
  uint8_t contra_capacity;                  /* byte 160 */
  uint8_t contra_position_effect_mask[2];   /* bytes 161 to 162 */
  uint8_t contra_stock_leg_short_sale;      /* byte 163 */
  uint8_t contra_stock_leg_mpid[4];         /* bytes 164 to 167 */
  uint8_t reserved_1;                       /* byte 168 */
} CrossOrderAcceptedMessage;

/* any Cross Order Accepted Message at all: every byte one the checker chooses */
static void any_cross_order_accepted_message(CrossOrderAcceptedMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->firm_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->instrument_id[i] = arbitrary(); }
  record->cross_type = arbitrary();
  record->auction_type = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->auction_id[i] = arbitrary(); }
  record->auction_alloc_pct = arbitrary();
  record->side = arbitrary();
  record->iso = arbitrary();
  record->price_protection = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->effective_time[i] = arbitrary(); }
  record->disclosure_mask = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->primary_order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 16; i++) { record->primary_cl_ord_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->primary_cmta[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->primary_clearing_account[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->primary_occ_account[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->primary_cust_acct[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->primary_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->primary_quantity[i] = arbitrary(); }
  record->primary_capacity = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->primary_position_effect_mask[i] = arbitrary(); }
  record->primary_stock_leg_short_sale = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->primary_stock_leg_mpid[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->contra_order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 16; i++) { record->contra_cl_ord_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->contra_cmta[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->contra_clearing_account[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->contra_occ_account[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->contra_cust_acct[i] = arbitrary(); }
  record->contra_order_type = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->contra_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->contra_quantity[i] = arbitrary(); }
  record->contra_capacity = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->contra_position_effect_mask[i] = arbitrary(); }
  record->contra_stock_leg_short_sale = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->contra_stock_leg_mpid[i] = arbitrary(); }
  record->reserved_1 = arbitrary();
}

/* Cross Order Accepted Message to the wire: 169 bytes from at, returning where the next byte goes */
static size_t encode_cross_order_accepted_message(const CrossOrderAcceptedMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->firm_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument_id[i]; }
  wire[at++] = record->cross_type;
  wire[at++] = record->auction_type;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->auction_id[i]; }
  wire[at++] = record->auction_alloc_pct;
  wire[at++] = record->side;
  wire[at++] = record->iso;
  wire[at++] = record->price_protection;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->effective_time[i]; }
  wire[at++] = record->disclosure_mask;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->primary_order_id[i]; }
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->primary_cl_ord_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->primary_cmta[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->primary_clearing_account[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->primary_occ_account[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->primary_cust_acct[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->primary_price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->primary_quantity[i]; }
  wire[at++] = record->primary_capacity;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->primary_position_effect_mask[i]; }
  wire[at++] = record->primary_stock_leg_short_sale;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->primary_stock_leg_mpid[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->contra_order_id[i]; }
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->contra_cl_ord_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->contra_cmta[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->contra_clearing_account[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->contra_occ_account[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->contra_cust_acct[i]; }
  wire[at++] = record->contra_order_type;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->contra_price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->contra_quantity[i]; }
  wire[at++] = record->contra_capacity;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->contra_position_effect_mask[i]; }
  wire[at++] = record->contra_stock_leg_short_sale;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->contra_stock_leg_mpid[i]; }
  wire[at++] = record->reserved_1;

  return at;
}

/* Cross Order Accepted Message off the wire: 169 bytes from at, returning where the next byte lies */
static size_t decode_cross_order_accepted_message(CrossOrderAcceptedMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->firm_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->instrument_id[i] = wire[at++]; }
  record->cross_type = wire[at++];
  record->auction_type = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->auction_id[i] = wire[at++]; }
  record->auction_alloc_pct = wire[at++];
  record->side = wire[at++];
  record->iso = wire[at++];
  record->price_protection = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->effective_time[i] = wire[at++]; }
  record->disclosure_mask = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->primary_order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 16; i++) { record->primary_cl_ord_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->primary_cmta[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->primary_clearing_account[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->primary_occ_account[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->primary_cust_acct[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->primary_price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->primary_quantity[i] = wire[at++]; }
  record->primary_capacity = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->primary_position_effect_mask[i] = wire[at++]; }
  record->primary_stock_leg_short_sale = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->primary_stock_leg_mpid[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->contra_order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 16; i++) { record->contra_cl_ord_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->contra_cmta[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->contra_clearing_account[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->contra_occ_account[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->contra_cust_acct[i] = wire[at++]; }
  record->contra_order_type = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->contra_price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->contra_quantity[i] = wire[at++]; }
  record->contra_capacity = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->contra_position_effect_mask[i] = wire[at++]; }
  record->contra_stock_leg_short_sale = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->contra_stock_leg_mpid[i] = wire[at++]; }
  record->reserved_1 = wire[at++];

  return at;
}

/* what was read of Cross Order Accepted Message is what was written, byte for byte */
static void equal_cross_order_accepted_message(const CrossOrderAcceptedMessage *read, const CrossOrderAcceptedMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->firm_id[i] == written->firm_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->instrument_id[i] == written->instrument_id[i]); }
  assert(read->cross_type == written->cross_type);
  assert(read->auction_type == written->auction_type);
  for (size_t i = 0; i < 4; i++) { assert(read->auction_id[i] == written->auction_id[i]); }
  assert(read->auction_alloc_pct == written->auction_alloc_pct);
  assert(read->side == written->side);
  assert(read->iso == written->iso);
  assert(read->price_protection == written->price_protection);
  for (size_t i = 0; i < 8; i++) { assert(read->effective_time[i] == written->effective_time[i]); }
  assert(read->disclosure_mask == written->disclosure_mask);
  for (size_t i = 0; i < 8; i++) { assert(read->primary_order_id[i] == written->primary_order_id[i]); }
  for (size_t i = 0; i < 16; i++) { assert(read->primary_cl_ord_id[i] == written->primary_cl_ord_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->primary_cmta[i] == written->primary_cmta[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->primary_clearing_account[i] == written->primary_clearing_account[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->primary_occ_account[i] == written->primary_occ_account[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->primary_cust_acct[i] == written->primary_cust_acct[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->primary_price[i] == written->primary_price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->primary_quantity[i] == written->primary_quantity[i]); }
  assert(read->primary_capacity == written->primary_capacity);
  for (size_t i = 0; i < 2; i++) { assert(read->primary_position_effect_mask[i] == written->primary_position_effect_mask[i]); }
  assert(read->primary_stock_leg_short_sale == written->primary_stock_leg_short_sale);
  for (size_t i = 0; i < 4; i++) { assert(read->primary_stock_leg_mpid[i] == written->primary_stock_leg_mpid[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->contra_order_id[i] == written->contra_order_id[i]); }
  for (size_t i = 0; i < 16; i++) { assert(read->contra_cl_ord_id[i] == written->contra_cl_ord_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->contra_cmta[i] == written->contra_cmta[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->contra_clearing_account[i] == written->contra_clearing_account[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->contra_occ_account[i] == written->contra_occ_account[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->contra_cust_acct[i] == written->contra_cust_acct[i]); }
  assert(read->contra_order_type == written->contra_order_type);
  for (size_t i = 0; i < 8; i++) { assert(read->contra_price[i] == written->contra_price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->contra_quantity[i] == written->contra_quantity[i]); }
  assert(read->contra_capacity == written->contra_capacity);
  for (size_t i = 0; i < 2; i++) { assert(read->contra_position_effect_mask[i] == written->contra_position_effect_mask[i]); }
  assert(read->contra_stock_leg_short_sale == written->contra_stock_leg_short_sale);
  for (size_t i = 0; i < 4; i++) { assert(read->contra_stock_leg_mpid[i] == written->contra_stock_leg_mpid[i]); }
  assert(read->reserved_1 == written->reserved_1);
}

/* Cross Order Accepted Message: written and read back, then read and written back */
static void check_cross_order_accepted_message(void) {
  CrossOrderAcceptedMessage sent;
  CrossOrderAcceptedMessage got;
  uint8_t wire[169];
  uint8_t again[169];

  any_cross_order_accepted_message(&sent);
  assert(encode_cross_order_accepted_message(&sent, wire, 0) == 169);
  assert(decode_cross_order_accepted_message(&got, wire, 0) == 169);
  equal_cross_order_accepted_message(&got, &sent);

  for (size_t i = 0; i < 169; i++) { wire[i] = arbitrary(); }
  assert(decode_cross_order_accepted_message(&got, wire, 0) == 169);
  assert(encode_cross_order_accepted_message(&got, again, 0) == 169);
  for (size_t i = 0; i < 169; i++) { assert(again[i] == wire[i]); }
}

/* ---- Member Kill Switch Notification Message: 33 bytes ----------------------- */

/* The Member Kill Switch Notification informs of a Member Kill Switch Request issued by this OTTO account, or a Kill Switch Action (User or System initiated) targeting Firm ID(s) associated with this OTTO account. */
typedef struct {
  uint8_t timestamp[8];       /* bytes 0 to 7 */
  uint8_t firm_id[4];         /* bytes 8 to 11 */
  uint8_t cl_request_id[16];  /* bytes 12 to 27 */
  uint8_t target_firm_id[4];  /* bytes 28 to 31 */
  uint8_t kill_action;        /* byte 32 */
} MemberKillSwitchNotificationMessage;

/* any Member Kill Switch Notification Message at all: every byte one the checker chooses */
static void any_member_kill_switch_notification_message(MemberKillSwitchNotificationMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->firm_id[i] = arbitrary(); }
  for (size_t i = 0; i < 16; i++) { record->cl_request_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->target_firm_id[i] = arbitrary(); }
  record->kill_action = arbitrary();
}

/* Member Kill Switch Notification Message to the wire: 33 bytes from at, returning where the next byte goes */
static size_t encode_member_kill_switch_notification_message(const MemberKillSwitchNotificationMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->firm_id[i]; }
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->cl_request_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->target_firm_id[i]; }
  wire[at++] = record->kill_action;

  return at;
}

/* Member Kill Switch Notification Message off the wire: 33 bytes from at, returning where the next byte lies */
static size_t decode_member_kill_switch_notification_message(MemberKillSwitchNotificationMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->firm_id[i] = wire[at++]; }
  for (size_t i = 0; i < 16; i++) { record->cl_request_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->target_firm_id[i] = wire[at++]; }
  record->kill_action = wire[at++];

  return at;
}

/* what was read of Member Kill Switch Notification Message is what was written, byte for byte */
static void equal_member_kill_switch_notification_message(const MemberKillSwitchNotificationMessage *read, const MemberKillSwitchNotificationMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->firm_id[i] == written->firm_id[i]); }
  for (size_t i = 0; i < 16; i++) { assert(read->cl_request_id[i] == written->cl_request_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->target_firm_id[i] == written->target_firm_id[i]); }
  assert(read->kill_action == written->kill_action);
}

/* Member Kill Switch Notification Message: written and read back, then read and written back */
static void check_member_kill_switch_notification_message(void) {
  MemberKillSwitchNotificationMessage sent;
  MemberKillSwitchNotificationMessage got;
  uint8_t wire[33];
  uint8_t again[33];

  any_member_kill_switch_notification_message(&sent);
  assert(encode_member_kill_switch_notification_message(&sent, wire, 0) == 33);
  assert(decode_member_kill_switch_notification_message(&got, wire, 0) == 33);
  equal_member_kill_switch_notification_message(&got, &sent);

  for (size_t i = 0; i < 33; i++) { wire[i] = arbitrary(); }
  assert(decode_member_kill_switch_notification_message(&got, wire, 0) == 33);
  assert(encode_member_kill_switch_notification_message(&got, again, 0) == 33);
  for (size_t i = 0; i < 33; i++) { assert(again[i] == wire[i]); }
}

/* ---- Mass Cancel Response Message: 36 bytes ---------------------------------- */

/* Mass Cancel Response is sent out upon completion of processing of a valid Mass Cancel Request. */
typedef struct {
  uint8_t timestamp[8];       /* bytes 0 to 7 */
  uint8_t firm_id[4];         /* bytes 8 to 11 */
  uint8_t cl_request_id[16];  /* bytes 12 to 27 */
  uint8_t num_canceled[4];    /* bytes 28 to 31 */
  uint8_t num_pending[4];     /* bytes 32 to 35 */
} MassCancelResponseMessage;

/* any Mass Cancel Response Message at all: every byte one the checker chooses */
static void any_mass_cancel_response_message(MassCancelResponseMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->firm_id[i] = arbitrary(); }
  for (size_t i = 0; i < 16; i++) { record->cl_request_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->num_canceled[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->num_pending[i] = arbitrary(); }
}

/* Mass Cancel Response Message to the wire: 36 bytes from at, returning where the next byte goes */
static size_t encode_mass_cancel_response_message(const MassCancelResponseMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->firm_id[i]; }
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->cl_request_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->num_canceled[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->num_pending[i]; }

  return at;
}

/* Mass Cancel Response Message off the wire: 36 bytes from at, returning where the next byte lies */
static size_t decode_mass_cancel_response_message(MassCancelResponseMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->firm_id[i] = wire[at++]; }
  for (size_t i = 0; i < 16; i++) { record->cl_request_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->num_canceled[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->num_pending[i] = wire[at++]; }

  return at;
}

/* what was read of Mass Cancel Response Message is what was written, byte for byte */
static void equal_mass_cancel_response_message(const MassCancelResponseMessage *read, const MassCancelResponseMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->firm_id[i] == written->firm_id[i]); }
  for (size_t i = 0; i < 16; i++) { assert(read->cl_request_id[i] == written->cl_request_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->num_canceled[i] == written->num_canceled[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->num_pending[i] == written->num_pending[i]); }
}

/* Mass Cancel Response Message: written and read back, then read and written back */
static void check_mass_cancel_response_message(void) {
  MassCancelResponseMessage sent;
  MassCancelResponseMessage got;
  uint8_t wire[36];
  uint8_t again[36];

  any_mass_cancel_response_message(&sent);
  assert(encode_mass_cancel_response_message(&sent, wire, 0) == 36);
  assert(decode_mass_cancel_response_message(&got, wire, 0) == 36);
  equal_mass_cancel_response_message(&got, &sent);

  for (size_t i = 0; i < 36; i++) { wire[i] = arbitrary(); }
  assert(decode_mass_cancel_response_message(&got, wire, 0) == 36);
  assert(encode_mass_cancel_response_message(&got, again, 0) == 36);
  for (size_t i = 0; i < 36; i++) { assert(again[i] == wire[i]); }
}

/* ---- Modify Trade Response Message: 56 bytes --------------------------------- */

/* Modify Trade Response is sent when a valid Modify Trade Request is accepted. */
typedef struct {
  uint8_t timestamp[8];       /* bytes 0 to 7 */
  uint8_t firm_id[4];         /* bytes 8 to 11 */
  uint8_t instrument_id[4];   /* bytes 12 to 15 */
  uint8_t cl_request_id[16];  /* bytes 16 to 31 */
  uint8_t cl_ord_id[16];      /* bytes 32 to 47 */
  uint8_t cross_id[4];        /* bytes 48 to 51 */
  uint8_t match_id[4];        /* bytes 52 to 55 */
} ModifyTradeResponseMessage;

/* any Modify Trade Response Message at all: every byte one the checker chooses */
static void any_modify_trade_response_message(ModifyTradeResponseMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->firm_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->instrument_id[i] = arbitrary(); }
  for (size_t i = 0; i < 16; i++) { record->cl_request_id[i] = arbitrary(); }
  for (size_t i = 0; i < 16; i++) { record->cl_ord_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->cross_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->match_id[i] = arbitrary(); }
}

/* Modify Trade Response Message to the wire: 56 bytes from at, returning where the next byte goes */
static size_t encode_modify_trade_response_message(const ModifyTradeResponseMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->firm_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument_id[i]; }
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->cl_request_id[i]; }
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->cl_ord_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->cross_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->match_id[i]; }

  return at;
}

/* Modify Trade Response Message off the wire: 56 bytes from at, returning where the next byte lies */
static size_t decode_modify_trade_response_message(ModifyTradeResponseMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->firm_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->instrument_id[i] = wire[at++]; }
  for (size_t i = 0; i < 16; i++) { record->cl_request_id[i] = wire[at++]; }
  for (size_t i = 0; i < 16; i++) { record->cl_ord_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->cross_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->match_id[i] = wire[at++]; }

  return at;
}

/* what was read of Modify Trade Response Message is what was written, byte for byte */
static void equal_modify_trade_response_message(const ModifyTradeResponseMessage *read, const ModifyTradeResponseMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->firm_id[i] == written->firm_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->instrument_id[i] == written->instrument_id[i]); }
  for (size_t i = 0; i < 16; i++) { assert(read->cl_request_id[i] == written->cl_request_id[i]); }
  for (size_t i = 0; i < 16; i++) { assert(read->cl_ord_id[i] == written->cl_ord_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->cross_id[i] == written->cross_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->match_id[i] == written->match_id[i]); }
}

/* Modify Trade Response Message: written and read back, then read and written back */
static void check_modify_trade_response_message(void) {
  ModifyTradeResponseMessage sent;
  ModifyTradeResponseMessage got;
  uint8_t wire[56];
  uint8_t again[56];

  any_modify_trade_response_message(&sent);
  assert(encode_modify_trade_response_message(&sent, wire, 0) == 56);
  assert(decode_modify_trade_response_message(&got, wire, 0) == 56);
  equal_modify_trade_response_message(&got, &sent);

  for (size_t i = 0; i < 56; i++) { wire[i] = arbitrary(); }
  assert(decode_modify_trade_response_message(&got, wire, 0) == 56);
  assert(encode_modify_trade_response_message(&got, again, 0) == 56);
  for (size_t i = 0; i < 56; i++) { assert(again[i] == wire[i]); }
}

/* ---- Reject Message: 27 bytes ------------------------------------------------ */

/* Reject is sent in response to a Request that is deemed invalid. Reject message contains error code explaining the reason for rejection. */
typedef struct {
  uint8_t timestamp[8];     /* bytes 0 to 7 */
  uint8_t reject_msg_type;  /* byte 8 */
  uint8_t cl_ord_id[16];    /* bytes 9 to 24 */
  uint8_t reject_code[2];   /* bytes 25 to 26 */
} RejectMessage;

/* any Reject Message at all: every byte one the checker chooses */
static void any_reject_message(RejectMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
  record->reject_msg_type = arbitrary();
  for (size_t i = 0; i < 16; i++) { record->cl_ord_id[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->reject_code[i] = arbitrary(); }
}

/* Reject Message to the wire: 27 bytes from at, returning where the next byte goes */
static size_t encode_reject_message(const RejectMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }
  wire[at++] = record->reject_msg_type;
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->cl_ord_id[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->reject_code[i]; }

  return at;
}

/* Reject Message off the wire: 27 bytes from at, returning where the next byte lies */
static size_t decode_reject_message(RejectMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }
  record->reject_msg_type = wire[at++];
  for (size_t i = 0; i < 16; i++) { record->cl_ord_id[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->reject_code[i] = wire[at++]; }

  return at;
}

/* what was read of Reject Message is what was written, byte for byte */
static void equal_reject_message(const RejectMessage *read, const RejectMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  assert(read->reject_msg_type == written->reject_msg_type);
  for (size_t i = 0; i < 16; i++) { assert(read->cl_ord_id[i] == written->cl_ord_id[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->reject_code[i] == written->reject_code[i]); }
}

/* Reject Message: written and read back, then read and written back */
static void check_reject_message(void) {
  RejectMessage sent;
  RejectMessage got;
  uint8_t wire[27];
  uint8_t again[27];

  any_reject_message(&sent);
  assert(encode_reject_message(&sent, wire, 0) == 27);
  assert(decode_reject_message(&got, wire, 0) == 27);
  equal_reject_message(&got, &sent);

  for (size_t i = 0; i < 27; i++) { wire[i] = arbitrary(); }
  assert(decode_reject_message(&got, wire, 0) == 27);
  assert(encode_reject_message(&got, again, 0) == 27);
  for (size_t i = 0; i < 27; i++) { assert(again[i] == wire[i]); }
}

/* ---- Pending Response Message: 34 bytes -------------------------------------- */

/* A Pending Response is sent by OTTO when a Request cannot be immediately, fully processed or validated, and indicates that the final status of the Request is not yet known (typically, any Request for a pending instrument). It is eventually followed by the Notification associated with the Request or a Reject. */
typedef struct {
  uint8_t timestamp[8];      /* bytes 0 to 7 */
  uint8_t firm_id[4];        /* bytes 8 to 11 */
  uint8_t instrument_id[4];  /* bytes 12 to 15 */
  uint8_t pending_msg_type;  /* byte 16 */
  uint8_t cl_ord_id[16];     /* bytes 17 to 32 */
  uint8_t pending_reason;    /* byte 33 */
} PendingResponseMessage;

/* any Pending Response Message at all: every byte one the checker chooses */
static void any_pending_response_message(PendingResponseMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->firm_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->instrument_id[i] = arbitrary(); }
  record->pending_msg_type = arbitrary();
  for (size_t i = 0; i < 16; i++) { record->cl_ord_id[i] = arbitrary(); }
  record->pending_reason = arbitrary();
}

/* Pending Response Message to the wire: 34 bytes from at, returning where the next byte goes */
static size_t encode_pending_response_message(const PendingResponseMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->firm_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument_id[i]; }
  wire[at++] = record->pending_msg_type;
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->cl_ord_id[i]; }
  wire[at++] = record->pending_reason;

  return at;
}

/* Pending Response Message off the wire: 34 bytes from at, returning where the next byte lies */
static size_t decode_pending_response_message(PendingResponseMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->firm_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->instrument_id[i] = wire[at++]; }
  record->pending_msg_type = wire[at++];
  for (size_t i = 0; i < 16; i++) { record->cl_ord_id[i] = wire[at++]; }
  record->pending_reason = wire[at++];

  return at;
}

/* what was read of Pending Response Message is what was written, byte for byte */
static void equal_pending_response_message(const PendingResponseMessage *read, const PendingResponseMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->firm_id[i] == written->firm_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->instrument_id[i] == written->instrument_id[i]); }
  assert(read->pending_msg_type == written->pending_msg_type);
  for (size_t i = 0; i < 16; i++) { assert(read->cl_ord_id[i] == written->cl_ord_id[i]); }
  assert(read->pending_reason == written->pending_reason);
}

/* Pending Response Message: written and read back, then read and written back */
static void check_pending_response_message(void) {
  PendingResponseMessage sent;
  PendingResponseMessage got;
  uint8_t wire[34];
  uint8_t again[34];

  any_pending_response_message(&sent);
  assert(encode_pending_response_message(&sent, wire, 0) == 34);
  assert(decode_pending_response_message(&got, wire, 0) == 34);
  equal_pending_response_message(&got, &sent);

  for (size_t i = 0; i < 34; i++) { wire[i] = arbitrary(); }
  assert(decode_pending_response_message(&got, wire, 0) == 34);
  assert(encode_pending_response_message(&got, again, 0) == 34);
  for (size_t i = 0; i < 34; i++) { assert(again[i] == wire[i]); }
}

/* ---- What esbmc checks ------------------------------------------------------- */

/* every record of the protocol, each on its own buffers */
static void checks(void) {
  check_server_packet_header();
  check_login_accepted_packet();
  check_login_rejected_packet();
  check_system_event_message();
  check_simple_instrument_directory_message();
  check_instrument_trading_action_message();
  check_order_accepted_short_form_message();
  check_order_replaced_message();
  check_order_canceled_message();
  check_order_executed_message();
  check_trade_details_message();
  check_cross_order_accepted_message();
  check_member_kill_switch_notification_message();
  check_mass_cancel_response_message();
  check_modify_trade_response_message();
  check_reject_message();
  check_pending_response_message();
}

int main(void) {
#ifdef CONCRETE
  for (pattern = 0; pattern < 4; pattern++) { checks(); }
#else
  checks();
#endif

  return 0;
}
