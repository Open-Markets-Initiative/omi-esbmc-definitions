// nsxaustralia/nets/marketdatafeed/NsxAustralia_Nets_MarketDataFeed_v4_2_55_Server.c
/*
 * Nation Stock Exchange of Australia NSX Market Data Feed
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

/* ---- Timestamp Message: 8 bytes ---------------------------------------------- */

/* This message is sent to provide the time since Epoch. It should be used in combination with the Timestamp field of individual messages to determine the exact time for each message. */
typedef struct {
  uint8_t nanosecond[8];  /* bytes 0 to 7 */
} TimestampMessage;

/* any Timestamp Message at all: every byte one the checker chooses */
static void any_timestamp_message(TimestampMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->nanosecond[i] = arbitrary(); }
}

/* Timestamp Message to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_timestamp_message(const TimestampMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->nanosecond[i]; }

  return at;
}

/* Timestamp Message off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_timestamp_message(TimestampMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->nanosecond[i] = wire[at++]; }

  return at;
}

/* what was read of Timestamp Message is what was written, byte for byte */
static void equal_timestamp_message(const TimestampMessage *read, const TimestampMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->nanosecond[i] == written->nanosecond[i]); }
}

/* Timestamp Message: written and read back, then read and written back */
static void check_timestamp_message(void) {
  TimestampMessage sent;
  TimestampMessage got;
  uint8_t wire[8];
  uint8_t again[8];

  any_timestamp_message(&sent);
  assert(encode_timestamp_message(&sent, wire, 0) == 8);
  assert(decode_timestamp_message(&got, wire, 0) == 8);
  equal_timestamp_message(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_timestamp_message(&got, wire, 0) == 8);
  assert(encode_timestamp_message(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- System Event Message: 61 bytes ------------------------------------------ */

/* This message will be sent to provide information about events that are scheduled or triggered by the system. Events may occur at Orderbook, Board, Board+Product or System level. */
typedef struct {
  uint8_t timestamp[4];       /* bytes 0 to 3 */
  uint8_t group[20];          /* bytes 4 to 23 */
  uint8_t product[12];        /* bytes 24 to 35 */
  uint8_t orderbook[4];       /* bytes 36 to 39 */
  uint8_t event_code[12];     /* bytes 40 to 51 */
  uint8_t event_status;       /* byte 52 */
  uint8_t scheduled_time[8];  /* bytes 53 to 60 */
} SystemEventMessage;

/* any System Event Message at all: every byte one the checker chooses */
static void any_system_event_message(SystemEventMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->group[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->product[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->orderbook[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->event_code[i] = arbitrary(); }
  record->event_status = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->scheduled_time[i] = arbitrary(); }
}

/* System Event Message to the wire: 61 bytes from at, returning where the next byte goes */
static size_t encode_system_event_message(const SystemEventMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->group[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->product[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->orderbook[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->event_code[i]; }
  wire[at++] = record->event_status;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->scheduled_time[i]; }

  return at;
}

/* System Event Message off the wire: 61 bytes from at, returning where the next byte lies */
static size_t decode_system_event_message(SystemEventMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->group[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->product[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->orderbook[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->event_code[i] = wire[at++]; }
  record->event_status = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->scheduled_time[i] = wire[at++]; }

  return at;
}

/* what was read of System Event Message is what was written, byte for byte */
static void equal_system_event_message(const SystemEventMessage *read, const SystemEventMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->group[i] == written->group[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->product[i] == written->product[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->orderbook[i] == written->orderbook[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->event_code[i] == written->event_code[i]); }
  assert(read->event_status == written->event_status);
  for (size_t i = 0; i < 8; i++) { assert(read->scheduled_time[i] == written->scheduled_time[i]); }
}

/* System Event Message: written and read back, then read and written back */
static void check_system_event_message(void) {
  SystemEventMessage sent;
  SystemEventMessage got;
  uint8_t wire[61];
  uint8_t again[61];

  any_system_event_message(&sent);
  assert(encode_system_event_message(&sent, wire, 0) == 61);
  assert(decode_system_event_message(&got, wire, 0) == 61);
  equal_system_event_message(&got, &sent);

  for (size_t i = 0; i < 61; i++) { wire[i] = arbitrary(); }
  assert(decode_system_event_message(&got, wire, 0) == 61);
  assert(encode_system_event_message(&got, again, 0) == 61);
  for (size_t i = 0; i < 61; i++) { assert(again[i] == wire[i]); }
}

/* ---- Price Tick Size Message: 24 bytes --------------------------------------- */

/* This message provides the price ticks (steps) for the orderbooks in the system. It should be used as a lookup from Orderbook Directory [R] messages. */
typedef struct {
  uint8_t timestamp[4];           /* bytes 0 to 3 */
  uint8_t tick_size_table_id[4];  /* bytes 4 to 7 */
  uint8_t tick_size[8];           /* bytes 8 to 15 */
  uint8_t price_start[8];         /* bytes 16 to 23 */
} PriceTickSizeMessage;

/* any Price Tick Size Message at all: every byte one the checker chooses */
static void any_price_tick_size_message(PriceTickSizeMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->tick_size_table_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->tick_size[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->price_start[i] = arbitrary(); }
}

/* Price Tick Size Message to the wire: 24 bytes from at, returning where the next byte goes */
static size_t encode_price_tick_size_message(const PriceTickSizeMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->tick_size_table_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->tick_size[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price_start[i]; }

  return at;
}

/* Price Tick Size Message off the wire: 24 bytes from at, returning where the next byte lies */
static size_t decode_price_tick_size_message(PriceTickSizeMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->tick_size_table_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->tick_size[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->price_start[i] = wire[at++]; }

  return at;
}

/* what was read of Price Tick Size Message is what was written, byte for byte */
static void equal_price_tick_size_message(const PriceTickSizeMessage *read, const PriceTickSizeMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->tick_size_table_id[i] == written->tick_size_table_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->tick_size[i] == written->tick_size[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->price_start[i] == written->price_start[i]); }
}

/* Price Tick Size Message: written and read back, then read and written back */
static void check_price_tick_size_message(void) {
  PriceTickSizeMessage sent;
  PriceTickSizeMessage got;
  uint8_t wire[24];
  uint8_t again[24];

  any_price_tick_size_message(&sent);
  assert(encode_price_tick_size_message(&sent, wire, 0) == 24);
  assert(decode_price_tick_size_message(&got, wire, 0) == 24);
  equal_price_tick_size_message(&got, &sent);

  for (size_t i = 0; i < 24; i++) { wire[i] = arbitrary(); }
  assert(decode_price_tick_size_message(&got, wire, 0) == 24);
  assert(encode_price_tick_size_message(&got, again, 0) == 24);
  for (size_t i = 0; i < 24; i++) { assert(again[i] == wire[i]); }
}

/* ---- Quantity Tick Size Message: 24 bytes ------------------------------------ */

/* This message provides the quantity ticks (steps) for the orderbooks in the system. It should be used as a lookup from Orderbook Directory [R] messages. */
typedef struct {
  uint8_t timestamp[4];           /* bytes 0 to 3 */
  uint8_t tick_size_table_id[4];  /* bytes 4 to 7 */
  uint8_t tick_size[8];           /* bytes 8 to 15 */
  uint8_t quantity_start[8];      /* bytes 16 to 23 */
} QuantityTickSizeMessage;

/* any Quantity Tick Size Message at all: every byte one the checker chooses */
static void any_quantity_tick_size_message(QuantityTickSizeMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->tick_size_table_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->tick_size[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->quantity_start[i] = arbitrary(); }
}

/* Quantity Tick Size Message to the wire: 24 bytes from at, returning where the next byte goes */
static size_t encode_quantity_tick_size_message(const QuantityTickSizeMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->tick_size_table_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->tick_size[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->quantity_start[i]; }

  return at;
}

/* Quantity Tick Size Message off the wire: 24 bytes from at, returning where the next byte lies */
static size_t decode_quantity_tick_size_message(QuantityTickSizeMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->tick_size_table_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->tick_size[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->quantity_start[i] = wire[at++]; }

  return at;
}

/* what was read of Quantity Tick Size Message is what was written, byte for byte */
static void equal_quantity_tick_size_message(const QuantityTickSizeMessage *read, const QuantityTickSizeMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->tick_size_table_id[i] == written->tick_size_table_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->tick_size[i] == written->tick_size[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->quantity_start[i] == written->quantity_start[i]); }
}

/* Quantity Tick Size Message: written and read back, then read and written back */
static void check_quantity_tick_size_message(void) {
  QuantityTickSizeMessage sent;
  QuantityTickSizeMessage got;
  uint8_t wire[24];
  uint8_t again[24];

  any_quantity_tick_size_message(&sent);
  assert(encode_quantity_tick_size_message(&sent, wire, 0) == 24);
  assert(decode_quantity_tick_size_message(&got, wire, 0) == 24);
  equal_quantity_tick_size_message(&got, &sent);

  for (size_t i = 0; i < 24; i++) { wire[i] = arbitrary(); }
  assert(decode_quantity_tick_size_message(&got, wire, 0) == 24);
  assert(encode_quantity_tick_size_message(&got, again, 0) == 24);
  for (size_t i = 0; i < 24; i++) { assert(again[i] == wire[i]); }
}

/* ---- Orderbook Directory Message: 320 bytes ---------------------------------- */

/* Orderbook Directory Messages are transmitted during the reference data spin. Static data messages are sent at the beginning of the feed and contain exchange reference information. */
typedef struct {
  uint8_t timestamp[4];                    /* bytes 0 to 3 */
  uint8_t orderbook[4];                    /* bytes 4 to 7 */
  uint8_t isin[12];                        /* bytes 8 to 19 */
  uint8_t security_code[100];              /* bytes 20 to 119 */
  uint8_t security_name[100];              /* bytes 120 to 219 */
  uint8_t currency[3];                     /* bytes 220 to 222 */
  uint8_t board[20];                       /* bytes 223 to 242 */
  uint8_t product[12];                     /* bytes 243 to 254 */
  uint8_t minimum_quantity[8];             /* bytes 255 to 262 */
  uint8_t quantity_tick_size_table_id[4];  /* bytes 263 to 266 */
  uint8_t quantity_decimals[4];            /* bytes 267 to 270 */
  uint8_t price_tick_size_table_id[4];     /* bytes 271 to 274 */
  uint8_t price_decimals[4];               /* bytes 275 to 278 */
  uint8_t listing[8];                      /* bytes 279 to 286 */
  uint8_t expiry[8];                       /* bytes 287 to 294 */
  uint8_t asset_type;                      /* byte 295 */
  uint8_t settle_date[4];                  /* bytes 296 to 299 */
  uint8_t reference_alpha_12[12];          /* bytes 300 to 311 */
  uint8_t remarks[8];                      /* bytes 312 to 319 */
} OrderbookDirectoryMessage;

/* any Orderbook Directory Message at all: every byte one the checker chooses */
static void any_orderbook_directory_message(OrderbookDirectoryMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->orderbook[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->isin[i] = arbitrary(); }
  for (size_t i = 0; i < 100; i++) { record->security_code[i] = arbitrary(); }
  for (size_t i = 0; i < 100; i++) { record->security_name[i] = arbitrary(); }
  for (size_t i = 0; i < 3; i++) { record->currency[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->board[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->product[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->minimum_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->quantity_tick_size_table_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->quantity_decimals[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->price_tick_size_table_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->price_decimals[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->listing[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->expiry[i] = arbitrary(); }
  record->asset_type = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->settle_date[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->reference_alpha_12[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->remarks[i] = arbitrary(); }
}

/* Orderbook Directory Message to the wire: 320 bytes from at, returning where the next byte goes */
static size_t encode_orderbook_directory_message(const OrderbookDirectoryMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->orderbook[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->isin[i]; }
  for (size_t i = 0; i < 100; i++) { wire[at++] = record->security_code[i]; }
  for (size_t i = 0; i < 100; i++) { wire[at++] = record->security_name[i]; }
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->currency[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->board[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->product[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->minimum_quantity[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->quantity_tick_size_table_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->quantity_decimals[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->price_tick_size_table_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->price_decimals[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->listing[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->expiry[i]; }
  wire[at++] = record->asset_type;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->settle_date[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->reference_alpha_12[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->remarks[i]; }

  return at;
}

/* Orderbook Directory Message off the wire: 320 bytes from at, returning where the next byte lies */
static size_t decode_orderbook_directory_message(OrderbookDirectoryMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->orderbook[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->isin[i] = wire[at++]; }
  for (size_t i = 0; i < 100; i++) { record->security_code[i] = wire[at++]; }
  for (size_t i = 0; i < 100; i++) { record->security_name[i] = wire[at++]; }
  for (size_t i = 0; i < 3; i++) { record->currency[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->board[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->product[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->minimum_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->quantity_tick_size_table_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->quantity_decimals[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->price_tick_size_table_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->price_decimals[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->listing[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->expiry[i] = wire[at++]; }
  record->asset_type = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->settle_date[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->reference_alpha_12[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->remarks[i] = wire[at++]; }

  return at;
}

/* what was read of Orderbook Directory Message is what was written, byte for byte */
static void equal_orderbook_directory_message(const OrderbookDirectoryMessage *read, const OrderbookDirectoryMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->orderbook[i] == written->orderbook[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->isin[i] == written->isin[i]); }
  for (size_t i = 0; i < 100; i++) { assert(read->security_code[i] == written->security_code[i]); }
  for (size_t i = 0; i < 100; i++) { assert(read->security_name[i] == written->security_name[i]); }
  for (size_t i = 0; i < 3; i++) { assert(read->currency[i] == written->currency[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->board[i] == written->board[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->product[i] == written->product[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->minimum_quantity[i] == written->minimum_quantity[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->quantity_tick_size_table_id[i] == written->quantity_tick_size_table_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->quantity_decimals[i] == written->quantity_decimals[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->price_tick_size_table_id[i] == written->price_tick_size_table_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->price_decimals[i] == written->price_decimals[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->listing[i] == written->listing[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->expiry[i] == written->expiry[i]); }
  assert(read->asset_type == written->asset_type);
  for (size_t i = 0; i < 4; i++) { assert(read->settle_date[i] == written->settle_date[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->reference_alpha_12[i] == written->reference_alpha_12[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->remarks[i] == written->remarks[i]); }
}

/* Orderbook Directory Message: written and read back, then read and written back */
static void check_orderbook_directory_message(void) {
  OrderbookDirectoryMessage sent;
  OrderbookDirectoryMessage got;
  uint8_t wire[320];
  uint8_t again[320];

  any_orderbook_directory_message(&sent);
  assert(encode_orderbook_directory_message(&sent, wire, 0) == 320);
  assert(decode_orderbook_directory_message(&got, wire, 0) == 320);
  equal_orderbook_directory_message(&got, &sent);

  for (size_t i = 0; i < 320; i++) { wire[i] = arbitrary(); }
  assert(decode_orderbook_directory_message(&got, wire, 0) == 320);
  assert(encode_orderbook_directory_message(&got, again, 0) == 320);
  for (size_t i = 0; i < 320; i++) { assert(again[i] == wire[i]); }
}

/* ---- Orderbook Trading Action Message: 10 bytes ------------------------------ */

/* This message indicates the current trading state of an orderbook. */
typedef struct {
  uint8_t timestamp[4];   /* bytes 0 to 3 */
  uint8_t orderbook[4];   /* bytes 4 to 7 */
  uint8_t trading_state;  /* byte 8 */
  uint8_t reason;         /* byte 9 */
} OrderbookTradingActionMessage;

/* any Orderbook Trading Action Message at all: every byte one the checker chooses */
static void any_orderbook_trading_action_message(OrderbookTradingActionMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->orderbook[i] = arbitrary(); }
  record->trading_state = arbitrary();
  record->reason = arbitrary();
}

/* Orderbook Trading Action Message to the wire: 10 bytes from at, returning where the next byte goes */
static size_t encode_orderbook_trading_action_message(const OrderbookTradingActionMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->orderbook[i]; }
  wire[at++] = record->trading_state;
  wire[at++] = record->reason;

  return at;
}

/* Orderbook Trading Action Message off the wire: 10 bytes from at, returning where the next byte lies */
static size_t decode_orderbook_trading_action_message(OrderbookTradingActionMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->orderbook[i] = wire[at++]; }
  record->trading_state = wire[at++];
  record->reason = wire[at++];

  return at;
}

/* what was read of Orderbook Trading Action Message is what was written, byte for byte */
static void equal_orderbook_trading_action_message(const OrderbookTradingActionMessage *read, const OrderbookTradingActionMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->orderbook[i] == written->orderbook[i]); }
  assert(read->trading_state == written->trading_state);
  assert(read->reason == written->reason);
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

/* ---- Orderbook Attribute Message: 18 bytes ----------------------------------- */

/* This message provides dynamic reference values for an orderbook. */
typedef struct {
  uint8_t timestamp[4];        /* bytes 0 to 3 */
  uint8_t orderbook[4];        /* bytes 4 to 7 */
  uint8_t attribute_value[8];  /* bytes 8 to 15 */
  uint8_t attribute_type;      /* byte 16 */
  uint8_t reason;              /* byte 17 */
} OrderbookAttributeMessage;

/* any Orderbook Attribute Message at all: every byte one the checker chooses */
static void any_orderbook_attribute_message(OrderbookAttributeMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->orderbook[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->attribute_value[i] = arbitrary(); }
  record->attribute_type = arbitrary();
  record->reason = arbitrary();
}

/* Orderbook Attribute Message to the wire: 18 bytes from at, returning where the next byte goes */
static size_t encode_orderbook_attribute_message(const OrderbookAttributeMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->orderbook[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->attribute_value[i]; }
  wire[at++] = record->attribute_type;
  wire[at++] = record->reason;

  return at;
}

/* Orderbook Attribute Message off the wire: 18 bytes from at, returning where the next byte lies */
static size_t decode_orderbook_attribute_message(OrderbookAttributeMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->orderbook[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->attribute_value[i] = wire[at++]; }
  record->attribute_type = wire[at++];
  record->reason = wire[at++];

  return at;
}

/* what was read of Orderbook Attribute Message is what was written, byte for byte */
static void equal_orderbook_attribute_message(const OrderbookAttributeMessage *read, const OrderbookAttributeMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->orderbook[i] == written->orderbook[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->attribute_value[i] == written->attribute_value[i]); }
  assert(read->attribute_type == written->attribute_type);
  assert(read->reason == written->reason);
}

/* Orderbook Attribute Message: written and read back, then read and written back */
static void check_orderbook_attribute_message(void) {
  OrderbookAttributeMessage sent;
  OrderbookAttributeMessage got;
  uint8_t wire[18];
  uint8_t again[18];

  any_orderbook_attribute_message(&sent);
  assert(encode_orderbook_attribute_message(&sent, wire, 0) == 18);
  assert(decode_orderbook_attribute_message(&got, wire, 0) == 18);
  equal_orderbook_attribute_message(&got, &sent);

  for (size_t i = 0; i < 18; i++) { wire[i] = arbitrary(); }
  assert(decode_orderbook_attribute_message(&got, wire, 0) == 18);
  assert(encode_orderbook_attribute_message(&got, again, 0) == 18);
  for (size_t i = 0; i < 18; i++) { assert(again[i] == wire[i]); }
}

/* ---- Firm Directory Message: 38 bytes ---------------------------------------- */

/* This message provides reference information about system participants. */
typedef struct {
  uint8_t timestamp[4];   /* bytes 0 to 3 */
  uint8_t firm_id[4];     /* bytes 4 to 7 */
  uint8_t firm_code[30];  /* bytes 8 to 37 */
} FirmDirectoryMessage;

/* any Firm Directory Message at all: every byte one the checker chooses */
static void any_firm_directory_message(FirmDirectoryMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->firm_id[i] = arbitrary(); }
  for (size_t i = 0; i < 30; i++) { record->firm_code[i] = arbitrary(); }
}

/* Firm Directory Message to the wire: 38 bytes from at, returning where the next byte goes */
static size_t encode_firm_directory_message(const FirmDirectoryMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->firm_id[i]; }
  for (size_t i = 0; i < 30; i++) { wire[at++] = record->firm_code[i]; }

  return at;
}

/* Firm Directory Message off the wire: 38 bytes from at, returning where the next byte lies */
static size_t decode_firm_directory_message(FirmDirectoryMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->firm_id[i] = wire[at++]; }
  for (size_t i = 0; i < 30; i++) { record->firm_code[i] = wire[at++]; }

  return at;
}

/* what was read of Firm Directory Message is what was written, byte for byte */
static void equal_firm_directory_message(const FirmDirectoryMessage *read, const FirmDirectoryMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->firm_id[i] == written->firm_id[i]); }
  for (size_t i = 0; i < 30; i++) { assert(read->firm_code[i] == written->firm_code[i]); }
}

/* Firm Directory Message: written and read back, then read and written back */
static void check_firm_directory_message(void) {
  FirmDirectoryMessage sent;
  FirmDirectoryMessage got;
  uint8_t wire[38];
  uint8_t again[38];

  any_firm_directory_message(&sent);
  assert(encode_firm_directory_message(&sent, wire, 0) == 38);
  assert(decode_firm_directory_message(&got, wire, 0) == 38);
  equal_firm_directory_message(&got, &sent);

  for (size_t i = 0; i < 38; i++) { wire[i] = arbitrary(); }
  assert(decode_firm_directory_message(&got, wire, 0) == 38);
  assert(encode_firm_directory_message(&got, again, 0) == 38);
  for (size_t i = 0; i < 38; i++) { assert(again[i] == wire[i]); }
}

/* ---- Add Order Message: 37 bytes --------------------------------------------- */

/* This message is sent when an order is added to the orderbook. */
typedef struct {
  uint8_t timestamp[4];     /* bytes 0 to 3 */
  uint8_t order_number[8];  /* bytes 4 to 11 */
  uint8_t order_verb;       /* byte 12 */
  uint8_t quantity[8];      /* bytes 13 to 20 */
  uint8_t orderbook[4];     /* bytes 21 to 24 */
  uint8_t price[8];         /* bytes 25 to 32 */
  uint8_t firm_id[4];       /* bytes 33 to 36 */
} AddOrderMessage;

/* any Add Order Message at all: every byte one the checker chooses */
static void any_add_order_message(AddOrderMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->order_number[i] = arbitrary(); }
  record->order_verb = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->orderbook[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->firm_id[i] = arbitrary(); }
}

/* Add Order Message to the wire: 37 bytes from at, returning where the next byte goes */
static size_t encode_add_order_message(const AddOrderMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_number[i]; }
  wire[at++] = record->order_verb;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->quantity[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->orderbook[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->firm_id[i]; }

  return at;
}

/* Add Order Message off the wire: 37 bytes from at, returning where the next byte lies */
static size_t decode_add_order_message(AddOrderMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->order_number[i] = wire[at++]; }
  record->order_verb = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->orderbook[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->firm_id[i] = wire[at++]; }

  return at;
}

/* what was read of Add Order Message is what was written, byte for byte */
static void equal_add_order_message(const AddOrderMessage *read, const AddOrderMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->order_number[i] == written->order_number[i]); }
  assert(read->order_verb == written->order_verb);
  for (size_t i = 0; i < 8; i++) { assert(read->quantity[i] == written->quantity[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->orderbook[i] == written->orderbook[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->price[i] == written->price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->firm_id[i] == written->firm_id[i]); }
}

/* Add Order Message: written and read back, then read and written back */
static void check_add_order_message(void) {
  AddOrderMessage sent;
  AddOrderMessage got;
  uint8_t wire[37];
  uint8_t again[37];

  any_add_order_message(&sent);
  assert(encode_add_order_message(&sent, wire, 0) == 37);
  assert(decode_add_order_message(&got, wire, 0) == 37);
  equal_add_order_message(&got, &sent);

  for (size_t i = 0; i < 37; i++) { wire[i] = arbitrary(); }
  assert(decode_add_order_message(&got, wire, 0) == 37);
  assert(encode_add_order_message(&got, again, 0) == 37);
  for (size_t i = 0; i < 37; i++) { assert(again[i] == wire[i]); }
}

/* ---- Order Executed Message: 33 bytes ---------------------------------------- */

/* This message is sent when an order on the book is executed in whole or in part. */
typedef struct {
  uint8_t timestamp[4];          /* bytes 0 to 3 */
  uint8_t order_number[8];       /* bytes 4 to 11 */
  uint8_t executed_quantity[8];  /* bytes 12 to 19 */
  uint8_t match_number[8];       /* bytes 20 to 27 */
  uint8_t printable;             /* byte 28 */
  uint8_t aggressor_firm_id[4];  /* bytes 29 to 32 */
} OrderExecutedMessage;

/* any Order Executed Message at all: every byte one the checker chooses */
static void any_order_executed_message(OrderExecutedMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->order_number[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->executed_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->match_number[i] = arbitrary(); }
  record->printable = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->aggressor_firm_id[i] = arbitrary(); }
}

/* Order Executed Message to the wire: 33 bytes from at, returning where the next byte goes */
static size_t encode_order_executed_message(const OrderExecutedMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_number[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->executed_quantity[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->match_number[i]; }
  wire[at++] = record->printable;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->aggressor_firm_id[i]; }

  return at;
}

/* Order Executed Message off the wire: 33 bytes from at, returning where the next byte lies */
static size_t decode_order_executed_message(OrderExecutedMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->order_number[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->executed_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->match_number[i] = wire[at++]; }
  record->printable = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->aggressor_firm_id[i] = wire[at++]; }

  return at;
}

/* what was read of Order Executed Message is what was written, byte for byte */
static void equal_order_executed_message(const OrderExecutedMessage *read, const OrderExecutedMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->order_number[i] == written->order_number[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->executed_quantity[i] == written->executed_quantity[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->match_number[i] == written->match_number[i]); }
  assert(read->printable == written->printable);
  for (size_t i = 0; i < 4; i++) { assert(read->aggressor_firm_id[i] == written->aggressor_firm_id[i]); }
}

/* Order Executed Message: written and read back, then read and written back */
static void check_order_executed_message(void) {
  OrderExecutedMessage sent;
  OrderExecutedMessage got;
  uint8_t wire[33];
  uint8_t again[33];

  any_order_executed_message(&sent);
  assert(encode_order_executed_message(&sent, wire, 0) == 33);
  assert(decode_order_executed_message(&got, wire, 0) == 33);
  equal_order_executed_message(&got, &sent);

  for (size_t i = 0; i < 33; i++) { wire[i] = arbitrary(); }
  assert(decode_order_executed_message(&got, wire, 0) == 33);
  assert(encode_order_executed_message(&got, again, 0) == 33);
  for (size_t i = 0; i < 33; i++) { assert(again[i] == wire[i]); }
}

/* ---- Order Executed With Price Message: 37 bytes ----------------------------- */

/* This message is sent when an order on the book is executed in whole or in part at a negotiated price different from the order price. */
typedef struct {
  uint8_t timestamp[4];          /* bytes 0 to 3 */
  uint8_t order_number[8];       /* bytes 4 to 11 */
  uint8_t executed_quantity[8];  /* bytes 12 to 19 */
  uint8_t match_number[8];       /* bytes 20 to 27 */
  uint8_t printable;             /* byte 28 */
  uint8_t execution_price[8];    /* bytes 29 to 36 */
} OrderExecutedWithPriceMessage;

/* any Order Executed With Price Message at all: every byte one the checker chooses */
static void any_order_executed_with_price_message(OrderExecutedWithPriceMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->order_number[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->executed_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->match_number[i] = arbitrary(); }
  record->printable = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->execution_price[i] = arbitrary(); }
}

/* Order Executed With Price Message to the wire: 37 bytes from at, returning where the next byte goes */
static size_t encode_order_executed_with_price_message(const OrderExecutedWithPriceMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_number[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->executed_quantity[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->match_number[i]; }
  wire[at++] = record->printable;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->execution_price[i]; }

  return at;
}

/* Order Executed With Price Message off the wire: 37 bytes from at, returning where the next byte lies */
static size_t decode_order_executed_with_price_message(OrderExecutedWithPriceMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->order_number[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->executed_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->match_number[i] = wire[at++]; }
  record->printable = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->execution_price[i] = wire[at++]; }

  return at;
}

/* what was read of Order Executed With Price Message is what was written, byte for byte */
static void equal_order_executed_with_price_message(const OrderExecutedWithPriceMessage *read, const OrderExecutedWithPriceMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->order_number[i] == written->order_number[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->executed_quantity[i] == written->executed_quantity[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->match_number[i] == written->match_number[i]); }
  assert(read->printable == written->printable);
  for (size_t i = 0; i < 8; i++) { assert(read->execution_price[i] == written->execution_price[i]); }
}

/* Order Executed With Price Message: written and read back, then read and written back */
static void check_order_executed_with_price_message(void) {
  OrderExecutedWithPriceMessage sent;
  OrderExecutedWithPriceMessage got;
  uint8_t wire[37];
  uint8_t again[37];

  any_order_executed_with_price_message(&sent);
  assert(encode_order_executed_with_price_message(&sent, wire, 0) == 37);
  assert(decode_order_executed_with_price_message(&got, wire, 0) == 37);
  equal_order_executed_with_price_message(&got, &sent);

  for (size_t i = 0; i < 37; i++) { wire[i] = arbitrary(); }
  assert(decode_order_executed_with_price_message(&got, wire, 0) == 37);
  assert(encode_order_executed_with_price_message(&got, again, 0) == 37);
  for (size_t i = 0; i < 37; i++) { assert(again[i] == wire[i]); }
}

/* ---- Broken Trade Message: 13 bytes ------------------------------------------ */

/* This message is sent when a trade is cancelled. */
typedef struct {
  uint8_t timestamp[4];     /* bytes 0 to 3 */
  uint8_t match_number[8];  /* bytes 4 to 11 */
  uint8_t reason;           /* byte 12 */
} BrokenTradeMessage;

/* any Broken Trade Message at all: every byte one the checker chooses */
static void any_broken_trade_message(BrokenTradeMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->match_number[i] = arbitrary(); }
  record->reason = arbitrary();
}

/* Broken Trade Message to the wire: 13 bytes from at, returning where the next byte goes */
static size_t encode_broken_trade_message(const BrokenTradeMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->match_number[i]; }
  wire[at++] = record->reason;

  return at;
}

/* Broken Trade Message off the wire: 13 bytes from at, returning where the next byte lies */
static size_t decode_broken_trade_message(BrokenTradeMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->match_number[i] = wire[at++]; }
  record->reason = wire[at++];

  return at;
}

/* what was read of Broken Trade Message is what was written, byte for byte */
static void equal_broken_trade_message(const BrokenTradeMessage *read, const BrokenTradeMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->match_number[i] == written->match_number[i]); }
  assert(read->reason == written->reason);
}

/* Broken Trade Message: written and read back, then read and written back */
static void check_broken_trade_message(void) {
  BrokenTradeMessage sent;
  BrokenTradeMessage got;
  uint8_t wire[13];
  uint8_t again[13];

  any_broken_trade_message(&sent);
  assert(encode_broken_trade_message(&sent, wire, 0) == 13);
  assert(decode_broken_trade_message(&got, wire, 0) == 13);
  equal_broken_trade_message(&got, &sent);

  for (size_t i = 0; i < 13; i++) { wire[i] = arbitrary(); }
  assert(decode_broken_trade_message(&got, wire, 0) == 13);
  assert(encode_broken_trade_message(&got, again, 0) == 13);
  for (size_t i = 0; i < 13; i++) { assert(again[i] == wire[i]); }
}

/* ---- Order Delete Message: 12 bytes ------------------------------------------ */

/* This message indicates when an order has been removed from the orderbook. */
typedef struct {
  uint8_t timestamp[4];     /* bytes 0 to 3 */
  uint8_t order_number[8];  /* bytes 4 to 11 */
} OrderDeleteMessage;

/* any Order Delete Message at all: every byte one the checker chooses */
static void any_order_delete_message(OrderDeleteMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->order_number[i] = arbitrary(); }
}

/* Order Delete Message to the wire: 12 bytes from at, returning where the next byte goes */
static size_t encode_order_delete_message(const OrderDeleteMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_number[i]; }

  return at;
}

/* Order Delete Message off the wire: 12 bytes from at, returning where the next byte lies */
static size_t decode_order_delete_message(OrderDeleteMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->order_number[i] = wire[at++]; }

  return at;
}

/* what was read of Order Delete Message is what was written, byte for byte */
static void equal_order_delete_message(const OrderDeleteMessage *read, const OrderDeleteMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->order_number[i] == written->order_number[i]); }
}

/* Order Delete Message: written and read back, then read and written back */
static void check_order_delete_message(void) {
  OrderDeleteMessage sent;
  OrderDeleteMessage got;
  uint8_t wire[12];
  uint8_t again[12];

  any_order_delete_message(&sent);
  assert(encode_order_delete_message(&sent, wire, 0) == 12);
  assert(decode_order_delete_message(&got, wire, 0) == 12);
  equal_order_delete_message(&got, &sent);

  for (size_t i = 0; i < 12; i++) { wire[i] = arbitrary(); }
  assert(decode_order_delete_message(&got, wire, 0) == 12);
  assert(encode_order_delete_message(&got, again, 0) == 12);
  for (size_t i = 0; i < 12; i++) { assert(again[i] == wire[i]); }
}

/* ---- Order Replace Message: 36 bytes ----------------------------------------- */

/* This message indicates when an order in the orderbook has been modified. */
typedef struct {
  uint8_t timestamp[4];              /* bytes 0 to 3 */
  uint8_t original_order_number[8];  /* bytes 4 to 11 */
  uint8_t new_order_number[8];       /* bytes 12 to 19 */
  uint8_t quantity[8];               /* bytes 20 to 27 */
  uint8_t price[8];                  /* bytes 28 to 35 */
} OrderReplaceMessage;

/* any Order Replace Message at all: every byte one the checker chooses */
static void any_order_replace_message(OrderReplaceMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->original_order_number[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->new_order_number[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->price[i] = arbitrary(); }
}

/* Order Replace Message to the wire: 36 bytes from at, returning where the next byte goes */
static size_t encode_order_replace_message(const OrderReplaceMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->original_order_number[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->new_order_number[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->quantity[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price[i]; }

  return at;
}

/* Order Replace Message off the wire: 36 bytes from at, returning where the next byte lies */
static size_t decode_order_replace_message(OrderReplaceMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->original_order_number[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->new_order_number[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->price[i] = wire[at++]; }

  return at;
}

/* what was read of Order Replace Message is what was written, byte for byte */
static void equal_order_replace_message(const OrderReplaceMessage *read, const OrderReplaceMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->original_order_number[i] == written->original_order_number[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->new_order_number[i] == written->new_order_number[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->quantity[i] == written->quantity[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->price[i] == written->price[i]); }
}

/* Order Replace Message: written and read back, then read and written back */
static void check_order_replace_message(void) {
  OrderReplaceMessage sent;
  OrderReplaceMessage got;
  uint8_t wire[36];
  uint8_t again[36];

  any_order_replace_message(&sent);
  assert(encode_order_replace_message(&sent, wire, 0) == 36);
  assert(decode_order_replace_message(&got, wire, 0) == 36);
  equal_order_replace_message(&got, &sent);

  for (size_t i = 0; i < 36; i++) { wire[i] = arbitrary(); }
  assert(decode_order_replace_message(&got, wire, 0) == 36);
  assert(encode_order_replace_message(&got, again, 0) == 36);
  for (size_t i = 0; i < 36; i++) { assert(again[i] == wire[i]); }
}

/* ---- Indicative Price Quantity Message: 57 bytes ----------------------------- */

/* This message provides auction information including the theoretical opening price and quantity. */
typedef struct {
  uint8_t timestamp[4];                     /* bytes 0 to 3 */
  uint8_t theoretical_opening_quantity[8];  /* bytes 4 to 11 */
  uint8_t orderbook[4];                     /* bytes 12 to 15 */
  uint8_t best_bid[8];                      /* bytes 16 to 23 */
  uint8_t best_offer[8];                    /* bytes 24 to 31 */
  uint8_t theoretical_opening_price[8];     /* bytes 32 to 39 */
  uint8_t cross_type;                       /* byte 40 */
  uint8_t best_bid_size[8];                 /* bytes 41 to 48 */
  uint8_t best_offer_size[8];               /* bytes 49 to 56 */
} IndicativePriceQuantityMessage;

/* any Indicative Price Quantity Message at all: every byte one the checker chooses */
static void any_indicative_price_quantity_message(IndicativePriceQuantityMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->theoretical_opening_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->orderbook[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->best_bid[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->best_offer[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->theoretical_opening_price[i] = arbitrary(); }
  record->cross_type = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->best_bid_size[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->best_offer_size[i] = arbitrary(); }
}

/* Indicative Price Quantity Message to the wire: 57 bytes from at, returning where the next byte goes */
static size_t encode_indicative_price_quantity_message(const IndicativePriceQuantityMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->theoretical_opening_quantity[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->orderbook[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->best_bid[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->best_offer[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->theoretical_opening_price[i]; }
  wire[at++] = record->cross_type;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->best_bid_size[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->best_offer_size[i]; }

  return at;
}

/* Indicative Price Quantity Message off the wire: 57 bytes from at, returning where the next byte lies */
static size_t decode_indicative_price_quantity_message(IndicativePriceQuantityMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->theoretical_opening_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->orderbook[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->best_bid[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->best_offer[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->theoretical_opening_price[i] = wire[at++]; }
  record->cross_type = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->best_bid_size[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->best_offer_size[i] = wire[at++]; }

  return at;
}

/* what was read of Indicative Price Quantity Message is what was written, byte for byte */
static void equal_indicative_price_quantity_message(const IndicativePriceQuantityMessage *read, const IndicativePriceQuantityMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->theoretical_opening_quantity[i] == written->theoretical_opening_quantity[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->orderbook[i] == written->orderbook[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->best_bid[i] == written->best_bid[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->best_offer[i] == written->best_offer[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->theoretical_opening_price[i] == written->theoretical_opening_price[i]); }
  assert(read->cross_type == written->cross_type);
  for (size_t i = 0; i < 8; i++) { assert(read->best_bid_size[i] == written->best_bid_size[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->best_offer_size[i] == written->best_offer_size[i]); }
}

/* Indicative Price Quantity Message: written and read back, then read and written back */
static void check_indicative_price_quantity_message(void) {
  IndicativePriceQuantityMessage sent;
  IndicativePriceQuantityMessage got;
  uint8_t wire[57];
  uint8_t again[57];

  any_indicative_price_quantity_message(&sent);
  assert(encode_indicative_price_quantity_message(&sent, wire, 0) == 57);
  assert(decode_indicative_price_quantity_message(&got, wire, 0) == 57);
  equal_indicative_price_quantity_message(&got, &sent);

  for (size_t i = 0; i < 57; i++) { wire[i] = arbitrary(); }
  assert(decode_indicative_price_quantity_message(&got, wire, 0) == 57);
  assert(encode_indicative_price_quantity_message(&got, again, 0) == 57);
  for (size_t i = 0; i < 57; i++) { assert(again[i] == wire[i]); }
}

/* ---- Trade Message: 43 bytes ------------------------------------------------- */

/* This message is sent to provide information about off-book matching. */
typedef struct {
  uint8_t timestamp[4];          /* bytes 0 to 3 */
  uint8_t executed_quantity[8];  /* bytes 4 to 11 */
  uint8_t orderbook[4];          /* bytes 12 to 15 */
  uint8_t printable;             /* byte 16 */
  uint8_t execution_price[8];    /* bytes 17 to 24 */
  uint8_t match_number[8];       /* bytes 25 to 32 */
  uint8_t trade_indicator;       /* byte 33 */
  uint8_t buy_firm_id[4];        /* bytes 34 to 37 */
  uint8_t sell_firm_id[4];       /* bytes 38 to 41 */
  uint8_t trade_source;          /* byte 42 */
} TradeMessage;

/* any Trade Message at all: every byte one the checker chooses */
static void any_trade_message(TradeMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->executed_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->orderbook[i] = arbitrary(); }
  record->printable = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->execution_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->match_number[i] = arbitrary(); }
  record->trade_indicator = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->buy_firm_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->sell_firm_id[i] = arbitrary(); }
  record->trade_source = arbitrary();
}

/* Trade Message to the wire: 43 bytes from at, returning where the next byte goes */
static size_t encode_trade_message(const TradeMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->executed_quantity[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->orderbook[i]; }
  wire[at++] = record->printable;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->execution_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->match_number[i]; }
  wire[at++] = record->trade_indicator;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->buy_firm_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->sell_firm_id[i]; }
  wire[at++] = record->trade_source;

  return at;
}

/* Trade Message off the wire: 43 bytes from at, returning where the next byte lies */
static size_t decode_trade_message(TradeMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->executed_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->orderbook[i] = wire[at++]; }
  record->printable = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->execution_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->match_number[i] = wire[at++]; }
  record->trade_indicator = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->buy_firm_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->sell_firm_id[i] = wire[at++]; }
  record->trade_source = wire[at++];

  return at;
}

/* what was read of Trade Message is what was written, byte for byte */
static void equal_trade_message(const TradeMessage *read, const TradeMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->executed_quantity[i] == written->executed_quantity[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->orderbook[i] == written->orderbook[i]); }
  assert(read->printable == written->printable);
  for (size_t i = 0; i < 8; i++) { assert(read->execution_price[i] == written->execution_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->match_number[i] == written->match_number[i]); }
  assert(read->trade_indicator == written->trade_indicator);
  for (size_t i = 0; i < 4; i++) { assert(read->buy_firm_id[i] == written->buy_firm_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->sell_firm_id[i] == written->sell_firm_id[i]); }
  assert(read->trade_source == written->trade_source);
}

/* Trade Message: written and read back, then read and written back */
static void check_trade_message(void) {
  TradeMessage sent;
  TradeMessage got;
  uint8_t wire[43];
  uint8_t again[43];

  any_trade_message(&sent);
  assert(encode_trade_message(&sent, wire, 0) == 43);
  assert(decode_trade_message(&got, wire, 0) == 43);
  equal_trade_message(&got, &sent);

  for (size_t i = 0; i < 43; i++) { wire[i] = arbitrary(); }
  assert(decode_trade_message(&got, wire, 0) == 43);
  assert(encode_trade_message(&got, again, 0) == 43);
  for (size_t i = 0; i < 43; i++) { assert(again[i] == wire[i]); }
}

/* ---- News Message: 891 bytes ------------------------------------------------- */

/* This message disseminates exchange news. */
typedef struct {
  uint8_t timestamp[4];                             /* bytes 0 to 3 */
  uint8_t orderbook[4];                             /* bytes 4 to 7 */
  uint8_t news_id[4];                               /* bytes 8 to 11 */
  uint8_t firm_code[30];                            /* bytes 12 to 41 */
  uint8_t title[81];                                /* bytes 42 to 122 */
  uint8_t reference_null_terminated_char_256[256];  /* bytes 123 to 378 */
  uint8_t news_text[512];                           /* bytes 379 to 890 */
} NewsMessage;

/* any News Message at all: every byte one the checker chooses */
static void any_news_message(NewsMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->orderbook[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->news_id[i] = arbitrary(); }
  for (size_t i = 0; i < 30; i++) { record->firm_code[i] = arbitrary(); }
  for (size_t i = 0; i < 81; i++) { record->title[i] = arbitrary(); }
  for (size_t i = 0; i < 256; i++) { record->reference_null_terminated_char_256[i] = arbitrary(); }
  for (size_t i = 0; i < 512; i++) { record->news_text[i] = arbitrary(); }
}

/* News Message to the wire: 891 bytes from at, returning where the next byte goes */
static size_t encode_news_message(const NewsMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->orderbook[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->news_id[i]; }
  for (size_t i = 0; i < 30; i++) { wire[at++] = record->firm_code[i]; }
  for (size_t i = 0; i < 81; i++) { wire[at++] = record->title[i]; }
  for (size_t i = 0; i < 256; i++) { wire[at++] = record->reference_null_terminated_char_256[i]; }
  for (size_t i = 0; i < 512; i++) { wire[at++] = record->news_text[i]; }

  return at;
}

/* News Message off the wire: 891 bytes from at, returning where the next byte lies */
static size_t decode_news_message(NewsMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->orderbook[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->news_id[i] = wire[at++]; }
  for (size_t i = 0; i < 30; i++) { record->firm_code[i] = wire[at++]; }
  for (size_t i = 0; i < 81; i++) { record->title[i] = wire[at++]; }
  for (size_t i = 0; i < 256; i++) { record->reference_null_terminated_char_256[i] = wire[at++]; }
  for (size_t i = 0; i < 512; i++) { record->news_text[i] = wire[at++]; }

  return at;
}

/* what was read of News Message is what was written, byte for byte */
static void equal_news_message(const NewsMessage *read, const NewsMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->orderbook[i] == written->orderbook[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->news_id[i] == written->news_id[i]); }
  for (size_t i = 0; i < 30; i++) { assert(read->firm_code[i] == written->firm_code[i]); }
  for (size_t i = 0; i < 81; i++) { assert(read->title[i] == written->title[i]); }
  for (size_t i = 0; i < 256; i++) { assert(read->reference_null_terminated_char_256[i] == written->reference_null_terminated_char_256[i]); }
  for (size_t i = 0; i < 512; i++) { assert(read->news_text[i] == written->news_text[i]); }
}

/* News Message: written and read back, then read and written back */
static void check_news_message(void) {
  NewsMessage sent;
  NewsMessage got;
  uint8_t wire[891];
  uint8_t again[891];

  any_news_message(&sent);
  assert(encode_news_message(&sent, wire, 0) == 891);
  assert(decode_news_message(&got, wire, 0) == 891);
  equal_news_message(&got, &sent);

  for (size_t i = 0; i < 891; i++) { wire[i] = arbitrary(); }
  assert(decode_news_message(&got, wire, 0) == 891);
  assert(encode_news_message(&got, again, 0) == 891);
  for (size_t i = 0; i < 891; i++) { assert(again[i] == wire[i]); }
}

/* ---- Index Member Directory Message: 20 bytes -------------------------------- */

/* This message provides details about index members and their respective weightings within an index. */
typedef struct {
  uint8_t timestamp[4];         /* bytes 0 to 3 */
  uint8_t index_orderbook[4];   /* bytes 4 to 7 */
  uint8_t member_orderbook[4];  /* bytes 8 to 11 */
  uint8_t weight[8];            /* bytes 12 to 19 */
} IndexMemberDirectoryMessage;

/* any Index Member Directory Message at all: every byte one the checker chooses */
static void any_index_member_directory_message(IndexMemberDirectoryMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->index_orderbook[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->member_orderbook[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->weight[i] = arbitrary(); }
}

/* Index Member Directory Message to the wire: 20 bytes from at, returning where the next byte goes */
static size_t encode_index_member_directory_message(const IndexMemberDirectoryMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->index_orderbook[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->member_orderbook[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->weight[i]; }

  return at;
}

/* Index Member Directory Message off the wire: 20 bytes from at, returning where the next byte lies */
static size_t decode_index_member_directory_message(IndexMemberDirectoryMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->index_orderbook[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->member_orderbook[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->weight[i] = wire[at++]; }

  return at;
}

/* what was read of Index Member Directory Message is what was written, byte for byte */
static void equal_index_member_directory_message(const IndexMemberDirectoryMessage *read, const IndexMemberDirectoryMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->index_orderbook[i] == written->index_orderbook[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->member_orderbook[i] == written->member_orderbook[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->weight[i] == written->weight[i]); }
}

/* Index Member Directory Message: written and read back, then read and written back */
static void check_index_member_directory_message(void) {
  IndexMemberDirectoryMessage sent;
  IndexMemberDirectoryMessage got;
  uint8_t wire[20];
  uint8_t again[20];

  any_index_member_directory_message(&sent);
  assert(encode_index_member_directory_message(&sent, wire, 0) == 20);
  assert(decode_index_member_directory_message(&got, wire, 0) == 20);
  equal_index_member_directory_message(&got, &sent);

  for (size_t i = 0; i < 20; i++) { wire[i] = arbitrary(); }
  assert(decode_index_member_directory_message(&got, wire, 0) == 20);
  assert(encode_index_member_directory_message(&got, again, 0) == 20);
  for (size_t i = 0; i < 20; i++) { assert(again[i] == wire[i]); }
}

/* ---- Index Value Message: 16 bytes ------------------------------------------- */

/* This message disseminates index values to market participants. */
typedef struct {
  uint8_t timestamp[4];        /* bytes 0 to 3 */
  uint8_t index_orderbook[4];  /* bytes 4 to 7 */
  uint8_t index_value[8];      /* bytes 8 to 15 */
} IndexValueMessage;

/* any Index Value Message at all: every byte one the checker chooses */
static void any_index_value_message(IndexValueMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->index_orderbook[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->index_value[i] = arbitrary(); }
}

/* Index Value Message to the wire: 16 bytes from at, returning where the next byte goes */
static size_t encode_index_value_message(const IndexValueMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->index_orderbook[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->index_value[i]; }

  return at;
}

/* Index Value Message off the wire: 16 bytes from at, returning where the next byte lies */
static size_t decode_index_value_message(IndexValueMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->index_orderbook[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->index_value[i] = wire[at++]; }

  return at;
}

/* what was read of Index Value Message is what was written, byte for byte */
static void equal_index_value_message(const IndexValueMessage *read, const IndexValueMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->index_orderbook[i] == written->index_orderbook[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->index_value[i] == written->index_value[i]); }
}

/* Index Value Message: written and read back, then read and written back */
static void check_index_value_message(void) {
  IndexValueMessage sent;
  IndexValueMessage got;
  uint8_t wire[16];
  uint8_t again[16];

  any_index_value_message(&sent);
  assert(encode_index_value_message(&sent, wire, 0) == 16);
  assert(decode_index_value_message(&got, wire, 0) == 16);
  equal_index_value_message(&got, &sent);

  for (size_t i = 0; i < 16; i++) { wire[i] = arbitrary(); }
  assert(decode_index_value_message(&got, wire, 0) == 16);
  assert(encode_index_value_message(&got, again, 0) == 16);
  for (size_t i = 0; i < 16; i++) { assert(again[i] == wire[i]); }
}

/* ---- What esbmc checks ------------------------------------------------------- */

/* every record of the protocol, each on its own buffers */
static void checks(void) {
  check_server_packet_header();
  check_login_accepted_packet();
  check_login_rejected_packet();
  check_timestamp_message();
  check_system_event_message();
  check_price_tick_size_message();
  check_quantity_tick_size_message();
  check_orderbook_directory_message();
  check_orderbook_trading_action_message();
  check_orderbook_attribute_message();
  check_firm_directory_message();
  check_add_order_message();
  check_order_executed_message();
  check_order_executed_with_price_message();
  check_broken_trade_message();
  check_order_delete_message();
  check_order_replace_message();
  check_indicative_price_quantity_message();
  check_trade_message();
  check_news_message();
  check_index_member_directory_message();
  check_index_value_message();
}

int main(void) {
#ifdef CONCRETE
  for (pattern = 0; pattern < 4; pattern++) { checks(); }
#else
  checks();
#endif

  return 0;
}
