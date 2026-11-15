// tradelogiq/lynxats/snapshotrecovery/LynxAts_SnapshotRecovery_v1_09_Server.c
/*
 * Tradelogiq Markets Inc. Lynx Snapshot Recovery
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

/* ---- Server Packet Header: 3 bytes ------------------------------------------- */

/* Tradelogiq SoupTcp Server Packet Header */
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

/* The server sends a Login Accepted Packet in response to receiving a valid Login Request from the client */
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

/* The server sends this packet in response to an invalid Login Request Packet from the client and closes the socket connection */
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

/* The spin consists of a Start-Of-Messages event, Add Order messages and an End-Of-Messages event, after which the Reallocation Server disconnects. */
typedef struct {
  uint8_t event_code;     /* byte 0 */
  uint8_t reserved_2[2];  /* bytes 1 to 2 */
  uint8_t timestamp[8];   /* bytes 3 to 10 */
} SystemEventMessage;

/* any System Event Message at all: every byte one the checker chooses */
static void any_system_event_message(SystemEventMessage *record) {
  record->event_code = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->reserved_2[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
}

/* System Event Message to the wire: 11 bytes from at, returning where the next byte goes */
static size_t encode_system_event_message(const SystemEventMessage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->event_code;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->reserved_2[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }

  return at;
}

/* System Event Message off the wire: 11 bytes from at, returning where the next byte lies */
static size_t decode_system_event_message(SystemEventMessage *record, const uint8_t *wire, size_t at) {
  record->event_code = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->reserved_2[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }

  return at;
}

/* what was read of System Event Message is what was written, byte for byte */
static void equal_system_event_message(const SystemEventMessage *read, const SystemEventMessage *written) {
  assert(read->event_code == written->event_code);
  for (size_t i = 0; i < 2; i++) { assert(read->reserved_2[i] == written->reserved_2[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
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

/* ---- Stock Directory Message: 39 bytes --------------------------------------- */

/* A Requested Sequence Number of 1 returns the symbol spin, the Instrument Directory messages distributed early in the Tradelogiq start of day. */
typedef struct {
  uint8_t market;              /* byte 0 */
  uint8_t stock[10];           /* bytes 1 to 10 */
  uint8_t timestamp[8];        /* bytes 11 to 18 */
  uint8_t board_lot_size[4];   /* bytes 19 to 22 */
  uint8_t instrument_id[2];    /* bytes 23 to 24 */
  uint8_t shortable;           /* byte 25 */
  uint8_t dividend_indicator;  /* byte 26 */
  uint8_t reserved_9[9];       /* bytes 27 to 35 */
  uint8_t currency[3];         /* bytes 36 to 38 */
} StockDirectoryMessage;

/* any Stock Directory Message at all: every byte one the checker chooses */
static void any_stock_directory_message(StockDirectoryMessage *record) {
  record->market = arbitrary();
  for (size_t i = 0; i < 10; i++) { record->stock[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->board_lot_size[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->instrument_id[i] = arbitrary(); }
  record->shortable = arbitrary();
  record->dividend_indicator = arbitrary();
  for (size_t i = 0; i < 9; i++) { record->reserved_9[i] = arbitrary(); }
  for (size_t i = 0; i < 3; i++) { record->currency[i] = arbitrary(); }
}

/* Stock Directory Message to the wire: 39 bytes from at, returning where the next byte goes */
static size_t encode_stock_directory_message(const StockDirectoryMessage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->market;
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->stock[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->board_lot_size[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->instrument_id[i]; }
  wire[at++] = record->shortable;
  wire[at++] = record->dividend_indicator;
  for (size_t i = 0; i < 9; i++) { wire[at++] = record->reserved_9[i]; }
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->currency[i]; }

  return at;
}

/* Stock Directory Message off the wire: 39 bytes from at, returning where the next byte lies */
static size_t decode_stock_directory_message(StockDirectoryMessage *record, const uint8_t *wire, size_t at) {
  record->market = wire[at++];
  for (size_t i = 0; i < 10; i++) { record->stock[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->board_lot_size[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->instrument_id[i] = wire[at++]; }
  record->shortable = wire[at++];
  record->dividend_indicator = wire[at++];
  for (size_t i = 0; i < 9; i++) { record->reserved_9[i] = wire[at++]; }
  for (size_t i = 0; i < 3; i++) { record->currency[i] = wire[at++]; }

  return at;
}

/* what was read of Stock Directory Message is what was written, byte for byte */
static void equal_stock_directory_message(const StockDirectoryMessage *read, const StockDirectoryMessage *written) {
  assert(read->market == written->market);
  for (size_t i = 0; i < 10; i++) { assert(read->stock[i] == written->stock[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->board_lot_size[i] == written->board_lot_size[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->instrument_id[i] == written->instrument_id[i]); }
  assert(read->shortable == written->shortable);
  assert(read->dividend_indicator == written->dividend_indicator);
  for (size_t i = 0; i < 9; i++) { assert(read->reserved_9[i] == written->reserved_9[i]); }
  for (size_t i = 0; i < 3; i++) { assert(read->currency[i] == written->currency[i]); }
}

/* Stock Directory Message: written and read back, then read and written back */
static void check_stock_directory_message(void) {
  StockDirectoryMessage sent;
  StockDirectoryMessage got;
  uint8_t wire[39];
  uint8_t again[39];

  any_stock_directory_message(&sent);
  assert(encode_stock_directory_message(&sent, wire, 0) == 39);
  assert(decode_stock_directory_message(&got, wire, 0) == 39);
  equal_stock_directory_message(&got, &sent);

  for (size_t i = 0; i < 39; i++) { wire[i] = arbitrary(); }
  assert(decode_stock_directory_message(&got, wire, 0) == 39);
  assert(encode_stock_directory_message(&got, again, 0) == 39);
  for (size_t i = 0; i < 39; i++) { assert(again[i] == wire[i]); }
}

/* ---- Extended Stock Directory Message: 71 bytes ------------------------------ */

/* The symbol spin carries the Extended Stock Directory of bonds, debentures, rights, notes and warrants alongside the Stock Directory. */
typedef struct {
  uint8_t market;             /* byte 0 */
  uint8_t stock[10];          /* bytes 1 to 10 */
  uint8_t timestamp[8];       /* bytes 11 to 18 */
  uint8_t board_lot_size[4];  /* bytes 19 to 22 */
  uint8_t instrument_id[2];   /* bytes 23 to 24 */
  uint8_t shortable;          /* byte 25 */
  uint8_t frequency;          /* byte 26 */
  uint8_t reserved_9[9];      /* bytes 27 to 35 */
  uint8_t currency[3];        /* bytes 36 to 38 */
  uint8_t security_type;      /* byte 39 */
  uint8_t expiry_date[8];     /* bytes 40 to 47 */
  uint8_t description[20];    /* bytes 48 to 67 */
  uint8_t reserved_3[3];      /* bytes 68 to 70 */
} ExtendedStockDirectoryMessage;

/* any Extended Stock Directory Message at all: every byte one the checker chooses */
static void any_extended_stock_directory_message(ExtendedStockDirectoryMessage *record) {
  record->market = arbitrary();
  for (size_t i = 0; i < 10; i++) { record->stock[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->board_lot_size[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->instrument_id[i] = arbitrary(); }
  record->shortable = arbitrary();
  record->frequency = arbitrary();
  for (size_t i = 0; i < 9; i++) { record->reserved_9[i] = arbitrary(); }
  for (size_t i = 0; i < 3; i++) { record->currency[i] = arbitrary(); }
  record->security_type = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->expiry_date[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->description[i] = arbitrary(); }
  for (size_t i = 0; i < 3; i++) { record->reserved_3[i] = arbitrary(); }
}

/* Extended Stock Directory Message to the wire: 71 bytes from at, returning where the next byte goes */
static size_t encode_extended_stock_directory_message(const ExtendedStockDirectoryMessage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->market;
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->stock[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->board_lot_size[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->instrument_id[i]; }
  wire[at++] = record->shortable;
  wire[at++] = record->frequency;
  for (size_t i = 0; i < 9; i++) { wire[at++] = record->reserved_9[i]; }
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->currency[i]; }
  wire[at++] = record->security_type;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->expiry_date[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->description[i]; }
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->reserved_3[i]; }

  return at;
}

/* Extended Stock Directory Message off the wire: 71 bytes from at, returning where the next byte lies */
static size_t decode_extended_stock_directory_message(ExtendedStockDirectoryMessage *record, const uint8_t *wire, size_t at) {
  record->market = wire[at++];
  for (size_t i = 0; i < 10; i++) { record->stock[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->board_lot_size[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->instrument_id[i] = wire[at++]; }
  record->shortable = wire[at++];
  record->frequency = wire[at++];
  for (size_t i = 0; i < 9; i++) { record->reserved_9[i] = wire[at++]; }
  for (size_t i = 0; i < 3; i++) { record->currency[i] = wire[at++]; }
  record->security_type = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->expiry_date[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->description[i] = wire[at++]; }
  for (size_t i = 0; i < 3; i++) { record->reserved_3[i] = wire[at++]; }

  return at;
}

/* what was read of Extended Stock Directory Message is what was written, byte for byte */
static void equal_extended_stock_directory_message(const ExtendedStockDirectoryMessage *read, const ExtendedStockDirectoryMessage *written) {
  assert(read->market == written->market);
  for (size_t i = 0; i < 10; i++) { assert(read->stock[i] == written->stock[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->board_lot_size[i] == written->board_lot_size[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->instrument_id[i] == written->instrument_id[i]); }
  assert(read->shortable == written->shortable);
  assert(read->frequency == written->frequency);
  for (size_t i = 0; i < 9; i++) { assert(read->reserved_9[i] == written->reserved_9[i]); }
  for (size_t i = 0; i < 3; i++) { assert(read->currency[i] == written->currency[i]); }
  assert(read->security_type == written->security_type);
  for (size_t i = 0; i < 8; i++) { assert(read->expiry_date[i] == written->expiry_date[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->description[i] == written->description[i]); }
  for (size_t i = 0; i < 3; i++) { assert(read->reserved_3[i] == written->reserved_3[i]); }
}

/* Extended Stock Directory Message: written and read back, then read and written back */
static void check_extended_stock_directory_message(void) {
  ExtendedStockDirectoryMessage sent;
  ExtendedStockDirectoryMessage got;
  uint8_t wire[71];
  uint8_t again[71];

  any_extended_stock_directory_message(&sent);
  assert(encode_extended_stock_directory_message(&sent, wire, 0) == 71);
  assert(decode_extended_stock_directory_message(&got, wire, 0) == 71);
  equal_extended_stock_directory_message(&got, &sent);

  for (size_t i = 0; i < 71; i++) { wire[i] = arbitrary(); }
  assert(decode_extended_stock_directory_message(&got, wire, 0) == 71);
  assert(encode_extended_stock_directory_message(&got, again, 0) == 71);
  for (size_t i = 0; i < 71; i++) { assert(again[i] == wire[i]); }
}

/* ---- Stock Trading Action Message: 15 bytes ---------------------------------- */

/* If sequence 1 is used for the Sequenced Number field the reallocation server will return the symbol spin with the stock trading status messages before returning all open orders seen on the book. */
typedef struct {
  uint8_t trading_state;     /* byte 0 */
  uint8_t instrument_id[2];  /* bytes 1 to 2 */
  uint8_t timestamp[8];      /* bytes 3 to 10 */
  uint8_t reason[4];         /* bytes 11 to 14 */
} StockTradingActionMessage;

/* any Stock Trading Action Message at all: every byte one the checker chooses */
static void any_stock_trading_action_message(StockTradingActionMessage *record) {
  record->trading_state = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->instrument_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->reason[i] = arbitrary(); }
}

/* Stock Trading Action Message to the wire: 15 bytes from at, returning where the next byte goes */
static size_t encode_stock_trading_action_message(const StockTradingActionMessage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->trading_state;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->instrument_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->reason[i]; }

  return at;
}

/* Stock Trading Action Message off the wire: 15 bytes from at, returning where the next byte lies */
static size_t decode_stock_trading_action_message(StockTradingActionMessage *record, const uint8_t *wire, size_t at) {
  record->trading_state = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->instrument_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->reason[i] = wire[at++]; }

  return at;
}

/* what was read of Stock Trading Action Message is what was written, byte for byte */
static void equal_stock_trading_action_message(const StockTradingActionMessage *read, const StockTradingActionMessage *written) {
  assert(read->trading_state == written->trading_state);
  for (size_t i = 0; i < 2; i++) { assert(read->instrument_id[i] == written->instrument_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->reason[i] == written->reason[i]); }
}

/* Stock Trading Action Message: written and read back, then read and written back */
static void check_stock_trading_action_message(void) {
  StockTradingActionMessage sent;
  StockTradingActionMessage got;
  uint8_t wire[15];
  uint8_t again[15];

  any_stock_trading_action_message(&sent);
  assert(encode_stock_trading_action_message(&sent, wire, 0) == 15);
  assert(decode_stock_trading_action_message(&got, wire, 0) == 15);
  equal_stock_trading_action_message(&got, &sent);

  for (size_t i = 0; i < 15; i++) { wire[i] = arbitrary(); }
  assert(decode_stock_trading_action_message(&got, wire, 0) == 15);
  assert(encode_stock_trading_action_message(&got, again, 0) == 15);
  for (size_t i = 0; i < 15; i++) { assert(again[i] == wire[i]); }
}

/* ---- Add Order Message: 27 bytes --------------------------------------------- */

/* Only open orders are sent in the spin; the spin will not contain any message for an order which is no longer in the book. */
typedef struct {
  uint8_t buy_sell_indicator;         /* byte 0 */
  uint8_t instrument_id[2];           /* bytes 1 to 2 */
  uint8_t timestamp[8];               /* bytes 3 to 10 */
  uint8_t order_reference_number[4];  /* bytes 11 to 14 */
  uint8_t shares[4];                  /* bytes 15 to 18 */
  uint8_t price[4];                   /* bytes 19 to 22 */
  uint8_t exec_broker_id[2];          /* bytes 23 to 24 */
  uint8_t reserved_2[2];              /* bytes 25 to 26 */
} AddOrderMessage;

/* any Add Order Message at all: every byte one the checker chooses */
static void any_add_order_message(AddOrderMessage *record) {
  record->buy_sell_indicator = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->instrument_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->order_reference_number[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->shares[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->price[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->exec_broker_id[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->reserved_2[i] = arbitrary(); }
}

/* Add Order Message to the wire: 27 bytes from at, returning where the next byte goes */
static size_t encode_add_order_message(const AddOrderMessage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->buy_sell_indicator;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->instrument_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->order_reference_number[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->shares[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->price[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->exec_broker_id[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->reserved_2[i]; }

  return at;
}

/* Add Order Message off the wire: 27 bytes from at, returning where the next byte lies */
static size_t decode_add_order_message(AddOrderMessage *record, const uint8_t *wire, size_t at) {
  record->buy_sell_indicator = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->instrument_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->order_reference_number[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->shares[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->price[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->exec_broker_id[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->reserved_2[i] = wire[at++]; }

  return at;
}

/* what was read of Add Order Message is what was written, byte for byte */
static void equal_add_order_message(const AddOrderMessage *read, const AddOrderMessage *written) {
  assert(read->buy_sell_indicator == written->buy_sell_indicator);
  for (size_t i = 0; i < 2; i++) { assert(read->instrument_id[i] == written->instrument_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->order_reference_number[i] == written->order_reference_number[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->shares[i] == written->shares[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->price[i] == written->price[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->exec_broker_id[i] == written->exec_broker_id[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->reserved_2[i] == written->reserved_2[i]); }
}

/* Add Order Message: written and read back, then read and written back */
static void check_add_order_message(void) {
  AddOrderMessage sent;
  AddOrderMessage got;
  uint8_t wire[27];
  uint8_t again[27];

  any_add_order_message(&sent);
  assert(encode_add_order_message(&sent, wire, 0) == 27);
  assert(decode_add_order_message(&got, wire, 0) == 27);
  equal_add_order_message(&got, &sent);

  for (size_t i = 0; i < 27; i++) { wire[i] = arbitrary(); }
  assert(decode_add_order_message(&got, wire, 0) == 27);
  assert(encode_add_order_message(&got, again, 0) == 27);
  for (size_t i = 0; i < 27; i++) { assert(again[i] == wire[i]); }
}

/* ---- What esbmc checks ------------------------------------------------------- */

/* every record of the protocol, each on its own buffers */
static void checks(void) {
  check_server_packet_header();
  check_login_accepted_packet();
  check_login_rejected_packet();
  check_system_event_message();
  check_stock_directory_message();
  check_extended_stock_directory_message();
  check_stock_trading_action_message();
  check_add_order_message();
}

int main(void) {
#ifdef CONCRETE
  for (pattern = 0; pattern < 4; pattern++) { checks(); }
#else
  checks();
#endif

  return 0;
}
