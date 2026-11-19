// six/sixswissexchange/snapshot/SixSwissExchange_Snapshot_v1_24_0_Server.c
/*
 * SIX Swiss Exchange SIX Swiss Exchange IMI Orderbook Snapshot Recovery Service
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

/* ---- Time Stamp Seconds Message: 4 bytes ------------------------------------- */

/* Timestamp of seconds since midnight, used in combination with the nanoseconds timestamp of each message */
typedef struct {
  uint8_t second[4];  /* bytes 0 to 3 */
} TimeStampSecondsMessage;

/* any Time Stamp Seconds Message at all: every byte one the checker chooses */
static void any_time_stamp_seconds_message(TimeStampSecondsMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->second[i] = arbitrary(); }
}

/* Time Stamp Seconds Message to the wire: 4 bytes from at, returning where the next byte goes */
static size_t encode_time_stamp_seconds_message(const TimeStampSecondsMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->second[i]; }

  return at;
}

/* Time Stamp Seconds Message off the wire: 4 bytes from at, returning where the next byte lies */
static size_t decode_time_stamp_seconds_message(TimeStampSecondsMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->second[i] = wire[at++]; }

  return at;
}

/* what was read of Time Stamp Seconds Message is what was written, byte for byte */
static void equal_time_stamp_seconds_message(const TimeStampSecondsMessage *read, const TimeStampSecondsMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->second[i] == written->second[i]); }
}

/* Time Stamp Seconds Message: written and read back, then read and written back */
static void check_time_stamp_seconds_message(void) {
  TimeStampSecondsMessage sent;
  TimeStampSecondsMessage got;
  uint8_t wire[4];
  uint8_t again[4];

  any_time_stamp_seconds_message(&sent);
  assert(encode_time_stamp_seconds_message(&sent, wire, 0) == 4);
  assert(decode_time_stamp_seconds_message(&got, wire, 0) == 4);
  equal_time_stamp_seconds_message(&got, &sent);

  for (size_t i = 0; i < 4; i++) { wire[i] = arbitrary(); }
  assert(decode_time_stamp_seconds_message(&got, wire, 0) == 4);
  assert(encode_time_stamp_seconds_message(&got, again, 0) == 4);
  for (size_t i = 0; i < 4; i++) { assert(again[i] == wire[i]); }
}

/* ---- System Event Message: 17 bytes ------------------------------------------ */

/* Sent as a result of trade events at the system, group and Orderbook level */
typedef struct {
  uint8_t timestamp[4];  /* bytes 0 to 3 */
  uint8_t group[8];      /* bytes 4 to 11 */
  uint8_t event_code;    /* byte 12 */
  uint8_t orderbook[4];  /* bytes 13 to 16 */
} SystemEventMessage;

/* any System Event Message at all: every byte one the checker chooses */
static void any_system_event_message(SystemEventMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->group[i] = arbitrary(); }
  record->event_code = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->orderbook[i] = arbitrary(); }
}

/* System Event Message to the wire: 17 bytes from at, returning where the next byte goes */
static size_t encode_system_event_message(const SystemEventMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->group[i]; }
  wire[at++] = record->event_code;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->orderbook[i]; }

  return at;
}

/* System Event Message off the wire: 17 bytes from at, returning where the next byte lies */
static size_t decode_system_event_message(SystemEventMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->group[i] = wire[at++]; }
  record->event_code = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->orderbook[i] = wire[at++]; }

  return at;
}

/* what was read of System Event Message is what was written, byte for byte */
static void equal_system_event_message(const SystemEventMessage *read, const SystemEventMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->group[i] == written->group[i]); }
  assert(read->event_code == written->event_code);
  for (size_t i = 0; i < 4; i++) { assert(read->orderbook[i] == written->orderbook[i]); }
}

/* System Event Message: written and read back, then read and written back */
static void check_system_event_message(void) {
  SystemEventMessage sent;
  SystemEventMessage got;
  uint8_t wire[17];
  uint8_t again[17];

  any_system_event_message(&sent);
  assert(encode_system_event_message(&sent, wire, 0) == 17);
  assert(decode_system_event_message(&got, wire, 0) == 17);
  equal_system_event_message(&got, &sent);

  for (size_t i = 0; i < 17; i++) { wire[i] = arbitrary(); }
  assert(decode_system_event_message(&got, wire, 0) == 17);
  assert(encode_system_event_message(&got, again, 0) == 17);
  for (size_t i = 0; i < 17; i++) { assert(again[i] == wire[i]); }
}

/* ---- Quantity Tick Size Message: 16 bytes ------------------------------------ */

/* Shows the Quantity Tick (Category) of a Security */
typedef struct {
  uint8_t timestamp[4];               /* bytes 0 to 3 */
  uint8_t quantity_tick_table_id[4];  /* bytes 4 to 7 */
  uint8_t quantity_tick_size[4];      /* bytes 8 to 11 */
  uint8_t quantity_start[4];          /* bytes 12 to 15 */
} QuantityTickSizeMessage;

/* any Quantity Tick Size Message at all: every byte one the checker chooses */
static void any_quantity_tick_size_message(QuantityTickSizeMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->quantity_tick_table_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->quantity_tick_size[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->quantity_start[i] = arbitrary(); }
}

/* Quantity Tick Size Message to the wire: 16 bytes from at, returning where the next byte goes */
static size_t encode_quantity_tick_size_message(const QuantityTickSizeMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->quantity_tick_table_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->quantity_tick_size[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->quantity_start[i]; }

  return at;
}

/* Quantity Tick Size Message off the wire: 16 bytes from at, returning where the next byte lies */
static size_t decode_quantity_tick_size_message(QuantityTickSizeMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->quantity_tick_table_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->quantity_tick_size[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->quantity_start[i] = wire[at++]; }

  return at;
}

/* what was read of Quantity Tick Size Message is what was written, byte for byte */
static void equal_quantity_tick_size_message(const QuantityTickSizeMessage *read, const QuantityTickSizeMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->quantity_tick_table_id[i] == written->quantity_tick_table_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->quantity_tick_size[i] == written->quantity_tick_size[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->quantity_start[i] == written->quantity_start[i]); }
}

/* Quantity Tick Size Message: written and read back, then read and written back */
static void check_quantity_tick_size_message(void) {
  QuantityTickSizeMessage sent;
  QuantityTickSizeMessage got;
  uint8_t wire[16];
  uint8_t again[16];

  any_quantity_tick_size_message(&sent);
  assert(encode_quantity_tick_size_message(&sent, wire, 0) == 16);
  assert(decode_quantity_tick_size_message(&got, wire, 0) == 16);
  equal_quantity_tick_size_message(&got, &sent);

  for (size_t i = 0; i < 16; i++) { wire[i] = arbitrary(); }
  assert(decode_quantity_tick_size_message(&got, wire, 0) == 16);
  assert(encode_quantity_tick_size_message(&got, again, 0) == 16);
  for (size_t i = 0; i < 16; i++) { assert(again[i] == wire[i]); }
}

/* ---- Price Tick Size Message: 16 bytes --------------------------------------- */

/* Shows the Price Tick (Category) of a Security */
typedef struct {
  uint8_t timestamp[4];            /* bytes 0 to 3 */
  uint8_t price_tick_table_id[4];  /* bytes 4 to 7 */
  uint8_t price_tick_size[4];      /* bytes 8 to 11 */
  uint8_t price_start[4];          /* bytes 12 to 15 */
} PriceTickSizeMessage;

/* any Price Tick Size Message at all: every byte one the checker chooses */
static void any_price_tick_size_message(PriceTickSizeMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->price_tick_table_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->price_tick_size[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->price_start[i] = arbitrary(); }
}

/* Price Tick Size Message to the wire: 16 bytes from at, returning where the next byte goes */
static size_t encode_price_tick_size_message(const PriceTickSizeMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->price_tick_table_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->price_tick_size[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->price_start[i]; }

  return at;
}

/* Price Tick Size Message off the wire: 16 bytes from at, returning where the next byte lies */
static size_t decode_price_tick_size_message(PriceTickSizeMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->price_tick_table_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->price_tick_size[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->price_start[i] = wire[at++]; }

  return at;
}

/* what was read of Price Tick Size Message is what was written, byte for byte */
static void equal_price_tick_size_message(const PriceTickSizeMessage *read, const PriceTickSizeMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->price_tick_table_id[i] == written->price_tick_table_id[i]); }
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

/* ---- Orderbook Directory Message: 68 bytes ----------------------------------- */

/* Provides the basic reference data for the active Orderbooks for a specific OBM partition */
typedef struct {
  uint8_t timestamp[4];               /* bytes 0 to 3 */
  uint8_t orderbook[4];               /* bytes 4 to 7 */
  uint8_t price_type;                 /* byte 8 */
  uint8_t isin[12];                   /* bytes 9 to 20 */
  uint8_t currency[3];                /* bytes 21 to 23 */
  uint8_t group[8];                   /* bytes 24 to 31 */
  uint8_t minimum_quantity[4];        /* bytes 32 to 35 */
  uint8_t quantity_tick_table_id[4];  /* bytes 36 to 39 */
  uint8_t price_tick_table_id[4];     /* bytes 40 to 43 */
  uint8_t price_decimals[4];          /* bytes 44 to 47 */
  uint8_t delisting_date[4];          /* bytes 48 to 51 */
  uint8_t delisting_time[4];          /* bytes 52 to 55 */
  uint8_t qod_price_decimals[4];      /* bytes 56 to 59 */
  uint8_t security_exchange[4];       /* bytes 60 to 63 */
  uint8_t reference_exchange[4];      /* bytes 64 to 67 */
} OrderbookDirectoryMessage;

/* any Orderbook Directory Message at all: every byte one the checker chooses */
static void any_orderbook_directory_message(OrderbookDirectoryMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->orderbook[i] = arbitrary(); }
  record->price_type = arbitrary();
  for (size_t i = 0; i < 12; i++) { record->isin[i] = arbitrary(); }
  for (size_t i = 0; i < 3; i++) { record->currency[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->group[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->minimum_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->quantity_tick_table_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->price_tick_table_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->price_decimals[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->delisting_date[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->delisting_time[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->qod_price_decimals[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->security_exchange[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->reference_exchange[i] = arbitrary(); }
}

/* Orderbook Directory Message to the wire: 68 bytes from at, returning where the next byte goes */
static size_t encode_orderbook_directory_message(const OrderbookDirectoryMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->orderbook[i]; }
  wire[at++] = record->price_type;
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->isin[i]; }
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->currency[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->group[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->minimum_quantity[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->quantity_tick_table_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->price_tick_table_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->price_decimals[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->delisting_date[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->delisting_time[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->qod_price_decimals[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->security_exchange[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->reference_exchange[i]; }

  return at;
}

/* Orderbook Directory Message off the wire: 68 bytes from at, returning where the next byte lies */
static size_t decode_orderbook_directory_message(OrderbookDirectoryMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->orderbook[i] = wire[at++]; }
  record->price_type = wire[at++];
  for (size_t i = 0; i < 12; i++) { record->isin[i] = wire[at++]; }
  for (size_t i = 0; i < 3; i++) { record->currency[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->group[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->minimum_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->quantity_tick_table_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->price_tick_table_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->price_decimals[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->delisting_date[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->delisting_time[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->qod_price_decimals[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->security_exchange[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->reference_exchange[i] = wire[at++]; }

  return at;
}

/* what was read of Orderbook Directory Message is what was written, byte for byte */
static void equal_orderbook_directory_message(const OrderbookDirectoryMessage *read, const OrderbookDirectoryMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->orderbook[i] == written->orderbook[i]); }
  assert(read->price_type == written->price_type);
  for (size_t i = 0; i < 12; i++) { assert(read->isin[i] == written->isin[i]); }
  for (size_t i = 0; i < 3; i++) { assert(read->currency[i] == written->currency[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->group[i] == written->group[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->minimum_quantity[i] == written->minimum_quantity[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->quantity_tick_table_id[i] == written->quantity_tick_table_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->price_tick_table_id[i] == written->price_tick_table_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->price_decimals[i] == written->price_decimals[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->delisting_date[i] == written->delisting_date[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->delisting_time[i] == written->delisting_time[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->qod_price_decimals[i] == written->qod_price_decimals[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->security_exchange[i] == written->security_exchange[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->reference_exchange[i] == written->reference_exchange[i]); }
}

/* Orderbook Directory Message: written and read back, then read and written back */
static void check_orderbook_directory_message(void) {
  OrderbookDirectoryMessage sent;
  OrderbookDirectoryMessage got;
  uint8_t wire[68];
  uint8_t again[68];

  any_orderbook_directory_message(&sent);
  assert(encode_orderbook_directory_message(&sent, wire, 0) == 68);
  assert(decode_orderbook_directory_message(&got, wire, 0) == 68);
  equal_orderbook_directory_message(&got, &sent);

  for (size_t i = 0; i < 68; i++) { wire[i] = arbitrary(); }
  assert(decode_orderbook_directory_message(&got, wire, 0) == 68);
  assert(encode_orderbook_directory_message(&got, again, 0) == 68);
  for (size_t i = 0; i < 68; i++) { assert(again[i] == wire[i]); }
}

/* ---- Orderbook Trading Action Message: 10 bytes ------------------------------ */

/* Sent as a result of an Orderbook state or condition change */
typedef struct {
  uint8_t timestamp[4];    /* bytes 0 to 3 */
  uint8_t orderbook[4];    /* bytes 4 to 7 */
  uint8_t trading_state;   /* byte 8 */
  uint8_t book_condition;  /* byte 9 */
} OrderbookTradingActionMessage;

/* any Orderbook Trading Action Message at all: every byte one the checker chooses */
static void any_orderbook_trading_action_message(OrderbookTradingActionMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->orderbook[i] = arbitrary(); }
  record->trading_state = arbitrary();
  record->book_condition = arbitrary();
}

/* Orderbook Trading Action Message to the wire: 10 bytes from at, returning where the next byte goes */
static size_t encode_orderbook_trading_action_message(const OrderbookTradingActionMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->orderbook[i]; }
  wire[at++] = record->trading_state;
  wire[at++] = record->book_condition;

  return at;
}

/* Orderbook Trading Action Message off the wire: 10 bytes from at, returning where the next byte lies */
static size_t decode_orderbook_trading_action_message(OrderbookTradingActionMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->orderbook[i] = wire[at++]; }
  record->trading_state = wire[at++];
  record->book_condition = wire[at++];

  return at;
}

/* what was read of Orderbook Trading Action Message is what was written, byte for byte */
static void equal_orderbook_trading_action_message(const OrderbookTradingActionMessage *read, const OrderbookTradingActionMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->orderbook[i] == written->orderbook[i]); }
  assert(read->trading_state == written->trading_state);
  assert(read->book_condition == written->book_condition);
}

/* Orderbook Trading Action Message: written and read back, then read and written back */
static void check_orderbook_trading_action_message(void) {
  OrderbookTradingActionMessage sent;
  OrderbookTradingActionMessage got;
  uint8_t wire[10];
  uint8_t again[10];

  any_orderbook_trading_action_message(&sent);
  assert(encode_orderbook_trading_action_message(&sent, wire, 0) == 10);
  assert(decode_orderbook_trading_action_message(&got, wire, 0) == 10);
  equal_orderbook_trading_action_message(&got, &sent);

  for (size_t i = 0; i < 10; i++) { wire[i] = arbitrary(); }
  assert(decode_orderbook_trading_action_message(&got, wire, 0) == 10);
  assert(encode_orderbook_trading_action_message(&got, again, 0) == 10);
  for (size_t i = 0; i < 10; i++) { assert(again[i] == wire[i]); }
}

/* ---- Add Order Message: 25 bytes --------------------------------------------- */

/* A new order has been accepted and added to the book; an Order Number and Quantity of zero carries the reference price */
typedef struct {
  uint8_t timestamp[4];       /* bytes 0 to 3 */
  uint8_t order_number[8];    /* bytes 4 to 11 */
  uint8_t order_verb;         /* byte 12 */
  uint8_t order_quantity[4];  /* bytes 13 to 16 */
  uint8_t orderbook[4];       /* bytes 17 to 20 */
  uint8_t order_price[4];     /* bytes 21 to 24 */
} AddOrderMessage;

/* any Add Order Message at all: every byte one the checker chooses */
static void any_add_order_message(AddOrderMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->order_number[i] = arbitrary(); }
  record->order_verb = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->order_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->orderbook[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->order_price[i] = arbitrary(); }
}

/* Add Order Message to the wire: 25 bytes from at, returning where the next byte goes */
static size_t encode_add_order_message(const AddOrderMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_number[i]; }
  wire[at++] = record->order_verb;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->order_quantity[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->orderbook[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->order_price[i]; }

  return at;
}

/* Add Order Message off the wire: 25 bytes from at, returning where the next byte lies */
static size_t decode_add_order_message(AddOrderMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->order_number[i] = wire[at++]; }
  record->order_verb = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->order_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->orderbook[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->order_price[i] = wire[at++]; }

  return at;
}

/* what was read of Add Order Message is what was written, byte for byte */
static void equal_add_order_message(const AddOrderMessage *read, const AddOrderMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->order_number[i] == written->order_number[i]); }
  assert(read->order_verb == written->order_verb);
  for (size_t i = 0; i < 4; i++) { assert(read->order_quantity[i] == written->order_quantity[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->orderbook[i] == written->orderbook[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->order_price[i] == written->order_price[i]); }
}

/* Add Order Message: written and read back, then read and written back */
static void check_add_order_message(void) {
  AddOrderMessage sent;
  AddOrderMessage got;
  uint8_t wire[25];
  uint8_t again[25];

  any_add_order_message(&sent);
  assert(encode_add_order_message(&sent, wire, 0) == 25);
  assert(decode_add_order_message(&got, wire, 0) == 25);
  equal_add_order_message(&got, &sent);

  for (size_t i = 0; i < 25; i++) { wire[i] = arbitrary(); }
  assert(decode_add_order_message(&got, wire, 0) == 25);
  assert(encode_add_order_message(&got, again, 0) == 25);
  for (size_t i = 0; i < 25; i++) { assert(again[i] == wire[i]); }
}

/* ---- Indicative Price Quantity Message: 29 bytes ----------------------------- */

/* Sent during non-automatic matching periods telling the users what would happen if the book was uncrossed now */
typedef struct {
  uint8_t timestamp[4];                     /* bytes 0 to 3 */
  uint8_t theoretical_opening_quantity[8];  /* bytes 4 to 11 */
  uint8_t orderbook[4];                     /* bytes 12 to 15 */
  uint8_t best_bid[4];                      /* bytes 16 to 19 */
  uint8_t best_offer[4];                    /* bytes 20 to 23 */
  uint8_t theoretical_opening_price[4];     /* bytes 24 to 27 */
  uint8_t cross_type;                       /* byte 28 */
} IndicativePriceQuantityMessage;

/* any Indicative Price Quantity Message at all: every byte one the checker chooses */
static void any_indicative_price_quantity_message(IndicativePriceQuantityMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->theoretical_opening_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->orderbook[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->best_bid[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->best_offer[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->theoretical_opening_price[i] = arbitrary(); }
  record->cross_type = arbitrary();
}

/* Indicative Price Quantity Message to the wire: 29 bytes from at, returning where the next byte goes */
static size_t encode_indicative_price_quantity_message(const IndicativePriceQuantityMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->theoretical_opening_quantity[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->orderbook[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->best_bid[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->best_offer[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->theoretical_opening_price[i]; }
  wire[at++] = record->cross_type;

  return at;
}

/* Indicative Price Quantity Message off the wire: 29 bytes from at, returning where the next byte lies */
static size_t decode_indicative_price_quantity_message(IndicativePriceQuantityMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->theoretical_opening_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->orderbook[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->best_bid[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->best_offer[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->theoretical_opening_price[i] = wire[at++]; }
  record->cross_type = wire[at++];

  return at;
}

/* what was read of Indicative Price Quantity Message is what was written, byte for byte */
static void equal_indicative_price_quantity_message(const IndicativePriceQuantityMessage *read, const IndicativePriceQuantityMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->theoretical_opening_quantity[i] == written->theoretical_opening_quantity[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->orderbook[i] == written->orderbook[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->best_bid[i] == written->best_bid[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->best_offer[i] == written->best_offer[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->theoretical_opening_price[i] == written->theoretical_opening_price[i]); }
  assert(read->cross_type == written->cross_type);
}

/* Indicative Price Quantity Message: written and read back, then read and written back */
static void check_indicative_price_quantity_message(void) {
  IndicativePriceQuantityMessage sent;
  IndicativePriceQuantityMessage got;
  uint8_t wire[29];
  uint8_t again[29];

  any_indicative_price_quantity_message(&sent);
  assert(encode_indicative_price_quantity_message(&sent, wire, 0) == 29);
  assert(decode_indicative_price_quantity_message(&got, wire, 0) == 29);
  equal_indicative_price_quantity_message(&got, &sent);

  for (size_t i = 0; i < 29; i++) { wire[i] = arbitrary(); }
  assert(decode_indicative_price_quantity_message(&got, wire, 0) == 29);
  assert(encode_indicative_price_quantity_message(&got, again, 0) == 29);
  for (size_t i = 0; i < 29; i++) { assert(again[i] == wire[i]); }
}

/* ---- Glimpse Snapshot Message: 8 bytes --------------------------------------- */

/* The last message of the GLIMPSE snapshot */
typedef struct {
  uint8_t sequence_number[8];  /* bytes 0 to 7 */
} GlimpseSnapshotMessage;

/* any Glimpse Snapshot Message at all: every byte one the checker chooses */
static void any_glimpse_snapshot_message(GlimpseSnapshotMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->sequence_number[i] = arbitrary(); }
}

/* Glimpse Snapshot Message to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_glimpse_snapshot_message(const GlimpseSnapshotMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->sequence_number[i]; }

  return at;
}

/* Glimpse Snapshot Message off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_glimpse_snapshot_message(GlimpseSnapshotMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->sequence_number[i] = wire[at++]; }

  return at;
}

/* what was read of Glimpse Snapshot Message is what was written, byte for byte */
static void equal_glimpse_snapshot_message(const GlimpseSnapshotMessage *read, const GlimpseSnapshotMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->sequence_number[i] == written->sequence_number[i]); }
}

/* Glimpse Snapshot Message: written and read back, then read and written back */
static void check_glimpse_snapshot_message(void) {
  GlimpseSnapshotMessage sent;
  GlimpseSnapshotMessage got;
  uint8_t wire[8];
  uint8_t again[8];

  any_glimpse_snapshot_message(&sent);
  assert(encode_glimpse_snapshot_message(&sent, wire, 0) == 8);
  assert(decode_glimpse_snapshot_message(&got, wire, 0) == 8);
  equal_glimpse_snapshot_message(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_glimpse_snapshot_message(&got, wire, 0) == 8);
  assert(encode_glimpse_snapshot_message(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- What esbmc checks ------------------------------------------------------- */

/* every record of the protocol, each on its own buffers */
static void checks(void) {
  check_server_packet_header();
  check_login_accepted_packet();
  check_login_rejected_packet();
  check_time_stamp_seconds_message();
  check_system_event_message();
  check_quantity_tick_size_message();
  check_price_tick_size_message();
  check_orderbook_directory_message();
  check_orderbook_trading_action_message();
  check_add_order_message();
  check_indicative_price_quantity_message();
  check_glimpse_snapshot_message();
}

int main(void) {
#ifdef CONCRETE
  for (pattern = 0; pattern < 4; pattern++) { checks(); }
#else
  checks();
#endif

  return 0;
}
