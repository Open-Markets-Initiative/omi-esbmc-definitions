// biva/bivaequities/orderentry/BivaEquities_OrderEntry_v1_05_Server.c
/*
 * Bolsa Institucional de Valores Order Entry
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

/* ---- System Event Message: 9 bytes ------------------------------------------- */

/* System event message */
typedef struct {
  uint8_t timestamp[8];  /* bytes 0 to 7 */
  uint8_t event_code;    /* byte 8 */
} SystemEventMessage;

/* any System Event Message at all: every byte one the checker chooses */
static void any_system_event_message(SystemEventMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
  record->event_code = arbitrary();
}

/* System Event Message to the wire: 9 bytes from at, returning where the next byte goes */
static size_t encode_system_event_message(const SystemEventMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }
  wire[at++] = record->event_code;

  return at;
}

/* System Event Message off the wire: 9 bytes from at, returning where the next byte lies */
static size_t decode_system_event_message(SystemEventMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }
  record->event_code = wire[at++];

  return at;
}

/* what was read of System Event Message is what was written, byte for byte */
static void equal_system_event_message(const SystemEventMessage *read, const SystemEventMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  assert(read->event_code == written->event_code);
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

/* ---- Accepted Message: 59 bytes ---------------------------------------------- */

/* Accepted message echoing the data fields of the Enter Order Message */
typedef struct {
  uint8_t timestamp[8];               /* bytes 0 to 7 */
  uint8_t order_token[4];             /* bytes 8 to 11 */
  uint8_t account_type;               /* byte 12 */
  uint8_t account_id[4];              /* bytes 13 to 16 */
  uint8_t order_verb;                 /* byte 17 */
  uint8_t quantity[8];                /* bytes 18 to 25 */
  uint8_t orderbook[4];               /* bytes 26 to 29 */
  uint8_t price[4];                   /* bytes 30 to 33 */
  uint8_t time_in_force[4];           /* bytes 34 to 37 */
  uint8_t client_id[4];               /* bytes 38 to 41 */
  uint8_t order_reference_number[8];  /* bytes 42 to 49 */
  uint8_t minimum_quantity[8];        /* bytes 50 to 57 */
  uint8_t order_state;                /* byte 58 */
} AcceptedMessage;

/* any Accepted Message at all: every byte one the checker chooses */
static void any_accepted_message(AcceptedMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->order_token[i] = arbitrary(); }
  record->account_type = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->account_id[i] = arbitrary(); }
  record->order_verb = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->orderbook[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->time_in_force[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->client_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->order_reference_number[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->minimum_quantity[i] = arbitrary(); }
  record->order_state = arbitrary();
}

/* Accepted Message to the wire: 59 bytes from at, returning where the next byte goes */
static size_t encode_accepted_message(const AcceptedMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->order_token[i]; }
  wire[at++] = record->account_type;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->account_id[i]; }
  wire[at++] = record->order_verb;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->quantity[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->orderbook[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->time_in_force[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->client_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_reference_number[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->minimum_quantity[i]; }
  wire[at++] = record->order_state;

  return at;
}

/* Accepted Message off the wire: 59 bytes from at, returning where the next byte lies */
static size_t decode_accepted_message(AcceptedMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->order_token[i] = wire[at++]; }
  record->account_type = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->account_id[i] = wire[at++]; }
  record->order_verb = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->orderbook[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->time_in_force[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->client_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->order_reference_number[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->minimum_quantity[i] = wire[at++]; }
  record->order_state = wire[at++];

  return at;
}

/* what was read of Accepted Message is what was written, byte for byte */
static void equal_accepted_message(const AcceptedMessage *read, const AcceptedMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->order_token[i] == written->order_token[i]); }
  assert(read->account_type == written->account_type);
  for (size_t i = 0; i < 4; i++) { assert(read->account_id[i] == written->account_id[i]); }
  assert(read->order_verb == written->order_verb);
  for (size_t i = 0; i < 8; i++) { assert(read->quantity[i] == written->quantity[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->orderbook[i] == written->orderbook[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->price[i] == written->price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->time_in_force[i] == written->time_in_force[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->client_id[i] == written->client_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->order_reference_number[i] == written->order_reference_number[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->minimum_quantity[i] == written->minimum_quantity[i]); }
  assert(read->order_state == written->order_state);
}

/* Accepted Message: written and read back, then read and written back */
static void check_accepted_message(void) {
  AcceptedMessage sent;
  AcceptedMessage got;
  uint8_t wire[59];
  uint8_t again[59];

  any_accepted_message(&sent);
  assert(encode_accepted_message(&sent, wire, 0) == 59);
  assert(decode_accepted_message(&got, wire, 0) == 59);
  equal_accepted_message(&got, &sent);

  for (size_t i = 0; i < 59; i++) { wire[i] = arbitrary(); }
  assert(decode_accepted_message(&got, wire, 0) == 59);
  assert(encode_accepted_message(&got, again, 0) == 59);
  for (size_t i = 0; i < 59; i++) { assert(again[i] == wire[i]); }
}

/* ---- Replaced Message: 42 bytes ---------------------------------------------- */

/* Replaced message */
typedef struct {
  uint8_t timestamp[8];                /* bytes 0 to 7 */
  uint8_t replacement_order_token[4];  /* bytes 8 to 11 */
  uint8_t order_verb;                  /* byte 12 */
  uint8_t quantity[8];                 /* bytes 13 to 20 */
  uint8_t orderbook[4];                /* bytes 21 to 24 */
  uint8_t price[4];                    /* bytes 25 to 28 */
  uint8_t order_reference_number[8];   /* bytes 29 to 36 */
  uint8_t order_state;                 /* byte 37 */
  uint8_t previous_order_token[4];     /* bytes 38 to 41 */
} ReplacedMessage;

/* any Replaced Message at all: every byte one the checker chooses */
static void any_replaced_message(ReplacedMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->replacement_order_token[i] = arbitrary(); }
  record->order_verb = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->orderbook[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->order_reference_number[i] = arbitrary(); }
  record->order_state = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->previous_order_token[i] = arbitrary(); }
}

/* Replaced Message to the wire: 42 bytes from at, returning where the next byte goes */
static size_t encode_replaced_message(const ReplacedMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->replacement_order_token[i]; }
  wire[at++] = record->order_verb;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->quantity[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->orderbook[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_reference_number[i]; }
  wire[at++] = record->order_state;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->previous_order_token[i]; }

  return at;
}

/* Replaced Message off the wire: 42 bytes from at, returning where the next byte lies */
static size_t decode_replaced_message(ReplacedMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->replacement_order_token[i] = wire[at++]; }
  record->order_verb = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->orderbook[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->order_reference_number[i] = wire[at++]; }
  record->order_state = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->previous_order_token[i] = wire[at++]; }

  return at;
}

/* what was read of Replaced Message is what was written, byte for byte */
static void equal_replaced_message(const ReplacedMessage *read, const ReplacedMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->replacement_order_token[i] == written->replacement_order_token[i]); }
  assert(read->order_verb == written->order_verb);
  for (size_t i = 0; i < 8; i++) { assert(read->quantity[i] == written->quantity[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->orderbook[i] == written->orderbook[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->price[i] == written->price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->order_reference_number[i] == written->order_reference_number[i]); }
  assert(read->order_state == written->order_state);
  for (size_t i = 0; i < 4; i++) { assert(read->previous_order_token[i] == written->previous_order_token[i]); }
}

/* Replaced Message: written and read back, then read and written back */
static void check_replaced_message(void) {
  ReplacedMessage sent;
  ReplacedMessage got;
  uint8_t wire[42];
  uint8_t again[42];

  any_replaced_message(&sent);
  assert(encode_replaced_message(&sent, wire, 0) == 42);
  assert(decode_replaced_message(&got, wire, 0) == 42);
  equal_replaced_message(&got, &sent);

  for (size_t i = 0; i < 42; i++) { wire[i] = arbitrary(); }
  assert(decode_replaced_message(&got, wire, 0) == 42);
  assert(encode_replaced_message(&got, again, 0) == 42);
  for (size_t i = 0; i < 42; i++) { assert(again[i] == wire[i]); }
}

/* ---- Canceled Message: 21 bytes ---------------------------------------------- */

/* Canceled order message */
typedef struct {
  uint8_t timestamp[8];     /* bytes 0 to 7 */
  uint8_t order_token[4];   /* bytes 8 to 11 */
  uint8_t quantity[8];      /* bytes 12 to 19 */
  uint8_t canceled_reason;  /* byte 20 */
} CanceledMessage;

/* any Canceled Message at all: every byte one the checker chooses */
static void any_canceled_message(CanceledMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->order_token[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->quantity[i] = arbitrary(); }
  record->canceled_reason = arbitrary();
}

/* Canceled Message to the wire: 21 bytes from at, returning where the next byte goes */
static size_t encode_canceled_message(const CanceledMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->order_token[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->quantity[i]; }
  wire[at++] = record->canceled_reason;

  return at;
}

/* Canceled Message off the wire: 21 bytes from at, returning where the next byte lies */
static size_t decode_canceled_message(CanceledMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->order_token[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->quantity[i] = wire[at++]; }
  record->canceled_reason = wire[at++];

  return at;
}

/* what was read of Canceled Message is what was written, byte for byte */
static void equal_canceled_message(const CanceledMessage *read, const CanceledMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->order_token[i] == written->order_token[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->quantity[i] == written->quantity[i]); }
  assert(read->canceled_reason == written->canceled_reason);
}

/* Canceled Message: written and read back, then read and written back */
static void check_canceled_message(void) {
  CanceledMessage sent;
  CanceledMessage got;
  uint8_t wire[21];
  uint8_t again[21];

  any_canceled_message(&sent);
  assert(encode_canceled_message(&sent, wire, 0) == 21);
  assert(decode_canceled_message(&got, wire, 0) == 21);
  equal_canceled_message(&got, &sent);

  for (size_t i = 0; i < 21; i++) { wire[i] = arbitrary(); }
  assert(decode_canceled_message(&got, wire, 0) == 21);
  assert(encode_canceled_message(&got, again, 0) == 21);
  for (size_t i = 0; i < 21; i++) { assert(again[i] == wire[i]); }
}

/* ---- Executed Order Message: 37 bytes ---------------------------------------- */

/* Order executed message */
typedef struct {
  uint8_t timestamp[8];          /* bytes 0 to 7 */
  uint8_t order_token[4];        /* bytes 8 to 11 */
  uint8_t executed_quantity[8];  /* bytes 12 to 19 */
  uint8_t executed_price[4];     /* bytes 20 to 23 */
  uint8_t liquidity_flag;        /* byte 24 */
  uint8_t match_number[8];       /* bytes 25 to 32 */
  uint8_t counter_party_id[4];   /* bytes 33 to 36 */
} ExecutedOrderMessage;

/* any Executed Order Message at all: every byte one the checker chooses */
static void any_executed_order_message(ExecutedOrderMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->order_token[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->executed_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->executed_price[i] = arbitrary(); }
  record->liquidity_flag = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->match_number[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->counter_party_id[i] = arbitrary(); }
}

/* Executed Order Message to the wire: 37 bytes from at, returning where the next byte goes */
static size_t encode_executed_order_message(const ExecutedOrderMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->order_token[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->executed_quantity[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->executed_price[i]; }
  wire[at++] = record->liquidity_flag;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->match_number[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->counter_party_id[i]; }

  return at;
}

/* Executed Order Message off the wire: 37 bytes from at, returning where the next byte lies */
static size_t decode_executed_order_message(ExecutedOrderMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->order_token[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->executed_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->executed_price[i] = wire[at++]; }
  record->liquidity_flag = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->match_number[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->counter_party_id[i] = wire[at++]; }

  return at;
}

/* what was read of Executed Order Message is what was written, byte for byte */
static void equal_executed_order_message(const ExecutedOrderMessage *read, const ExecutedOrderMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->order_token[i] == written->order_token[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->executed_quantity[i] == written->executed_quantity[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->executed_price[i] == written->executed_price[i]); }
  assert(read->liquidity_flag == written->liquidity_flag);
  for (size_t i = 0; i < 8; i++) { assert(read->match_number[i] == written->match_number[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->counter_party_id[i] == written->counter_party_id[i]); }
}

/* Executed Order Message: written and read back, then read and written back */
static void check_executed_order_message(void) {
  ExecutedOrderMessage sent;
  ExecutedOrderMessage got;
  uint8_t wire[37];
  uint8_t again[37];

  any_executed_order_message(&sent);
  assert(encode_executed_order_message(&sent, wire, 0) == 37);
  assert(decode_executed_order_message(&got, wire, 0) == 37);
  equal_executed_order_message(&got, &sent);

  for (size_t i = 0; i < 37; i++) { wire[i] = arbitrary(); }
  assert(decode_executed_order_message(&got, wire, 0) == 37);
  assert(encode_executed_order_message(&got, again, 0) == 37);
  for (size_t i = 0; i < 37; i++) { assert(again[i] == wire[i]); }
}

/* ---- Broken Trade Message: 21 bytes ------------------------------------------ */

/* Broken trade message */
typedef struct {
  uint8_t timestamp[8];         /* bytes 0 to 7 */
  uint8_t order_token[4];       /* bytes 8 to 11 */
  uint8_t match_number[8];      /* bytes 12 to 19 */
  uint8_t broken_trade_reason;  /* byte 20 */
} BrokenTradeMessage;

/* any Broken Trade Message at all: every byte one the checker chooses */
static void any_broken_trade_message(BrokenTradeMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->order_token[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->match_number[i] = arbitrary(); }
  record->broken_trade_reason = arbitrary();
}

/* Broken Trade Message to the wire: 21 bytes from at, returning where the next byte goes */
static size_t encode_broken_trade_message(const BrokenTradeMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->order_token[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->match_number[i]; }
  wire[at++] = record->broken_trade_reason;

  return at;
}

/* Broken Trade Message off the wire: 21 bytes from at, returning where the next byte lies */
static size_t decode_broken_trade_message(BrokenTradeMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->order_token[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->match_number[i] = wire[at++]; }
  record->broken_trade_reason = wire[at++];

  return at;
}

/* what was read of Broken Trade Message is what was written, byte for byte */
static void equal_broken_trade_message(const BrokenTradeMessage *read, const BrokenTradeMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->order_token[i] == written->order_token[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->match_number[i] == written->match_number[i]); }
  assert(read->broken_trade_reason == written->broken_trade_reason);
}

/* Broken Trade Message: written and read back, then read and written back */
static void check_broken_trade_message(void) {
  BrokenTradeMessage sent;
  BrokenTradeMessage got;
  uint8_t wire[21];
  uint8_t again[21];

  any_broken_trade_message(&sent);
  assert(encode_broken_trade_message(&sent, wire, 0) == 21);
  assert(decode_broken_trade_message(&got, wire, 0) == 21);
  equal_broken_trade_message(&got, &sent);

  for (size_t i = 0; i < 21; i++) { wire[i] = arbitrary(); }
  assert(decode_broken_trade_message(&got, wire, 0) == 21);
  assert(encode_broken_trade_message(&got, again, 0) == 21);
  for (size_t i = 0; i < 21; i++) { assert(again[i] == wire[i]); }
}

/* ---- Rejected Order Message: 13 bytes ---------------------------------------- */

/* Rejected order message */
typedef struct {
  uint8_t timestamp[8];     /* bytes 0 to 7 */
  uint8_t order_token[4];   /* bytes 8 to 11 */
  uint8_t rejected_reason;  /* byte 12 */
} RejectedOrderMessage;

/* any Rejected Order Message at all: every byte one the checker chooses */
static void any_rejected_order_message(RejectedOrderMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->order_token[i] = arbitrary(); }
  record->rejected_reason = arbitrary();
}

/* Rejected Order Message to the wire: 13 bytes from at, returning where the next byte goes */
static size_t encode_rejected_order_message(const RejectedOrderMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->order_token[i]; }
  wire[at++] = record->rejected_reason;

  return at;
}

/* Rejected Order Message off the wire: 13 bytes from at, returning where the next byte lies */
static size_t decode_rejected_order_message(RejectedOrderMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->order_token[i] = wire[at++]; }
  record->rejected_reason = wire[at++];

  return at;
}

/* what was read of Rejected Order Message is what was written, byte for byte */
static void equal_rejected_order_message(const RejectedOrderMessage *read, const RejectedOrderMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->order_token[i] == written->order_token[i]); }
  assert(read->rejected_reason == written->rejected_reason);
}

/* Rejected Order Message: written and read back, then read and written back */
static void check_rejected_order_message(void) {
  RejectedOrderMessage sent;
  RejectedOrderMessage got;
  uint8_t wire[13];
  uint8_t again[13];

  any_rejected_order_message(&sent);
  assert(encode_rejected_order_message(&sent, wire, 0) == 13);
  assert(decode_rejected_order_message(&got, wire, 0) == 13);
  equal_rejected_order_message(&got, &sent);

  for (size_t i = 0; i < 13; i++) { wire[i] = arbitrary(); }
  assert(decode_rejected_order_message(&got, wire, 0) == 13);
  assert(encode_rejected_order_message(&got, again, 0) == 13);
  for (size_t i = 0; i < 13; i++) { assert(again[i] == wire[i]); }
}

/* ---- What esbmc checks ------------------------------------------------------- */

/* every record of the protocol, each on its own buffers */
static void checks(void) {
  check_server_packet_header();
  check_login_accepted_packet();
  check_login_rejected_packet();
  check_system_event_message();
  check_accepted_message();
  check_replaced_message();
  check_canceled_message();
  check_executed_order_message();
  check_broken_trade_message();
  check_rejected_order_message();
}

int main(void) {
#ifdef CONCRETE
  for (pattern = 0; pattern < 4; pattern++) { checks(); }
#else
  checks();
#endif

  return 0;
}
