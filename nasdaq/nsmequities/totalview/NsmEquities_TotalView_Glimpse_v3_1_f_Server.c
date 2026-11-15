// nasdaq/nsmequities/totalview/NsmEquities_TotalView_Glimpse_v3_1_f_Server.c
/*
 * National Association of Securities Dealers Automated Quotations (Nasdaq) TotalView Itch
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
 *   - a field filling what is left of what holds it
 *   - the dispatch that chooses a message by its type
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

/* ---- Server Packet Header: 1 byte -------------------------------------------- */

/* SoupTcp Packet Header sent by the server */
typedef struct {
  uint8_t server_packet_type;  /* byte 0 */
} ServerPacketHeader;

/* any Server Packet Header at all: every byte one the checker chooses */
static void any_server_packet_header(ServerPacketHeader *record) {
  record->server_packet_type = arbitrary();
}

/* Server Packet Header to the wire: 1 byte from at, returning where the next byte goes */
static size_t encode_server_packet_header(const ServerPacketHeader *record, uint8_t *wire, size_t at) {
  wire[at++] = record->server_packet_type;

  return at;
}

/* Server Packet Header off the wire: 1 byte from at, returning where the next byte lies */
static size_t decode_server_packet_header(ServerPacketHeader *record, const uint8_t *wire, size_t at) {
  record->server_packet_type = wire[at++];

  return at;
}

/* what was read of Server Packet Header is what was written, byte for byte */
static void equal_server_packet_header(const ServerPacketHeader *read, const ServerPacketHeader *written) {
  assert(read->server_packet_type == written->server_packet_type);
}

/* Server Packet Header: written and read back, then read and written back */
static void check_server_packet_header(void) {
  ServerPacketHeader sent;
  ServerPacketHeader got;
  uint8_t wire[1];
  uint8_t again[1];

  any_server_packet_header(&sent);
  assert(encode_server_packet_header(&sent, wire, 0) == 1);
  assert(decode_server_packet_header(&got, wire, 0) == 1);
  equal_server_packet_header(&got, &sent);

  for (size_t i = 0; i < 1; i++) { wire[i] = arbitrary(); }
  assert(decode_server_packet_header(&got, wire, 0) == 1);
  assert(encode_server_packet_header(&got, again, 0) == 1);
  for (size_t i = 0; i < 1; i++) { assert(again[i] == wire[i]); }
}

/* ---- Login Accepted Packet: 30 bytes ----------------------------------------- */

/* The SoupTcp server sends a Login Accepted Packet in response to receiving a valid Login Request  from the client. */
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

/* The SoupTcp server sends this packet in response to an invalid Login Request Packet from the client. */
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

/* ---- Sequenced Message Header: 1 byte ---------------------------------------- */

/* Time and type carried ahead of every sequenced Itch message */
typedef struct {
  uint8_t message_type;  /* byte 0 */
} SequencedMessageHeader;

/* any Sequenced Message Header at all: every byte one the checker chooses */
static void any_sequenced_message_header(SequencedMessageHeader *record) {
  record->message_type = arbitrary();
}

/* Sequenced Message Header to the wire: 1 byte from at, returning where the next byte goes */
static size_t encode_sequenced_message_header(const SequencedMessageHeader *record, uint8_t *wire, size_t at) {
  wire[at++] = record->message_type;

  return at;
}

/* Sequenced Message Header off the wire: 1 byte from at, returning where the next byte lies */
static size_t decode_sequenced_message_header(SequencedMessageHeader *record, const uint8_t *wire, size_t at) {
  record->message_type = wire[at++];

  return at;
}

/* what was read of Sequenced Message Header is what was written, byte for byte */
static void equal_sequenced_message_header(const SequencedMessageHeader *read, const SequencedMessageHeader *written) {
  assert(read->message_type == written->message_type);
}

/* Sequenced Message Header: written and read back, then read and written back */
static void check_sequenced_message_header(void) {
  SequencedMessageHeader sent;
  SequencedMessageHeader got;
  uint8_t wire[1];
  uint8_t again[1];

  any_sequenced_message_header(&sent);
  assert(encode_sequenced_message_header(&sent, wire, 0) == 1);
  assert(decode_sequenced_message_header(&got, wire, 0) == 1);
  equal_sequenced_message_header(&got, &sent);

  for (size_t i = 0; i < 1; i++) { wire[i] = arbitrary(); }
  assert(decode_sequenced_message_header(&got, wire, 0) == 1);
  assert(encode_sequenced_message_header(&got, again, 0) == 1);
  for (size_t i = 0; i < 1; i++) { assert(again[i] == wire[i]); }
}

/* ---- Seconds Message: 5 bytes ------------------------------------------------ */

/* This message is sent every second for which at least one NASDAQ GLIMPSE 3.1f / NASDAQ TotalView-ITCH 3.1f message is being generated. */
typedef struct {
  uint8_t second[5];  /* bytes 0 to 4 */
} SecondsMessage;

/* any Seconds Message at all: every byte one the checker chooses */
static void any_seconds_message(SecondsMessage *record) {
  for (size_t i = 0; i < 5; i++) { record->second[i] = arbitrary(); }
}

/* Seconds Message to the wire: 5 bytes from at, returning where the next byte goes */
static size_t encode_seconds_message(const SecondsMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 5; i++) { wire[at++] = record->second[i]; }

  return at;
}

/* Seconds Message off the wire: 5 bytes from at, returning where the next byte lies */
static size_t decode_seconds_message(SecondsMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 5; i++) { record->second[i] = wire[at++]; }

  return at;
}

/* what was read of Seconds Message is what was written, byte for byte */
static void equal_seconds_message(const SecondsMessage *read, const SecondsMessage *written) {
  for (size_t i = 0; i < 5; i++) { assert(read->second[i] == written->second[i]); }
}

/* Seconds Message: written and read back, then read and written back */
static void check_seconds_message(void) {
  SecondsMessage sent;
  SecondsMessage got;
  uint8_t wire[5];
  uint8_t again[5];

  any_seconds_message(&sent);
  assert(encode_seconds_message(&sent, wire, 0) == 5);
  assert(decode_seconds_message(&got, wire, 0) == 5);
  equal_seconds_message(&got, &sent);

  for (size_t i = 0; i < 5; i++) { wire[i] = arbitrary(); }
  assert(decode_seconds_message(&got, wire, 0) == 5);
  assert(encode_seconds_message(&got, again, 0) == 5);
  for (size_t i = 0; i < 5; i++) { assert(again[i] == wire[i]); }
}

/* ---- Milliseconds Message: 3 bytes ------------------------------------------- */

/* This message is sent every millisecond for which at least one NASDAQ GLIMPSE 3.1f / NASDAQ TotalView-ITCH 3.1f message is being generated. */
typedef struct {
  uint8_t millisecond[3];  /* bytes 0 to 2 */
} MillisecondsMessage;

/* any Milliseconds Message at all: every byte one the checker chooses */
static void any_milliseconds_message(MillisecondsMessage *record) {
  for (size_t i = 0; i < 3; i++) { record->millisecond[i] = arbitrary(); }
}

/* Milliseconds Message to the wire: 3 bytes from at, returning where the next byte goes */
static size_t encode_milliseconds_message(const MillisecondsMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->millisecond[i]; }

  return at;
}

/* Milliseconds Message off the wire: 3 bytes from at, returning where the next byte lies */
static size_t decode_milliseconds_message(MillisecondsMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 3; i++) { record->millisecond[i] = wire[at++]; }

  return at;
}

/* what was read of Milliseconds Message is what was written, byte for byte */
static void equal_milliseconds_message(const MillisecondsMessage *read, const MillisecondsMessage *written) {
  for (size_t i = 0; i < 3; i++) { assert(read->millisecond[i] == written->millisecond[i]); }
}

/* Milliseconds Message: written and read back, then read and written back */
static void check_milliseconds_message(void) {
  MillisecondsMessage sent;
  MillisecondsMessage got;
  uint8_t wire[3];
  uint8_t again[3];

  any_milliseconds_message(&sent);
  assert(encode_milliseconds_message(&sent, wire, 0) == 3);
  assert(decode_milliseconds_message(&got, wire, 0) == 3);
  equal_milliseconds_message(&got, &sent);

  for (size_t i = 0; i < 3; i++) { wire[i] = arbitrary(); }
  assert(decode_milliseconds_message(&got, wire, 0) == 3);
  assert(encode_milliseconds_message(&got, again, 0) == 3);
  for (size_t i = 0; i < 3; i++) { assert(again[i] == wire[i]); }
}

/* ---- System Event Message: 1 byte -------------------------------------------- */

/* NASDAQ GLIMPSE product is designed to support the same system event messages as the NASDAQ TotalView-ITCH feed. On GLIMPSE, NASDAQ will send out system event messages for those events that occurred up to the time of the GLIMPSE snapshot request. */
typedef struct {
  uint8_t event_code;  /* byte 0 */
} SystemEventMessage;

/* any System Event Message at all: every byte one the checker chooses */
static void any_system_event_message(SystemEventMessage *record) {
  record->event_code = arbitrary();
}

/* System Event Message to the wire: 1 byte from at, returning where the next byte goes */
static size_t encode_system_event_message(const SystemEventMessage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->event_code;

  return at;
}

/* System Event Message off the wire: 1 byte from at, returning where the next byte lies */
static size_t decode_system_event_message(SystemEventMessage *record, const uint8_t *wire, size_t at) {
  record->event_code = wire[at++];

  return at;
}

/* what was read of System Event Message is what was written, byte for byte */
static void equal_system_event_message(const SystemEventMessage *read, const SystemEventMessage *written) {
  assert(read->event_code == written->event_code);
}

/* System Event Message: written and read back, then read and written back */
static void check_system_event_message(void) {
  SystemEventMessage sent;
  SystemEventMessage got;
  uint8_t wire[1];
  uint8_t again[1];

  any_system_event_message(&sent);
  assert(encode_system_event_message(&sent, wire, 0) == 1);
  assert(decode_system_event_message(&got, wire, 0) == 1);
  equal_system_event_message(&got, &sent);

  for (size_t i = 0; i < 1; i++) { wire[i] = arbitrary(); }
  assert(decode_system_event_message(&got, wire, 0) == 1);
  assert(encode_system_event_message(&got, again, 0) == 1);
  for (size_t i = 0; i < 1; i++) { assert(again[i] == wire[i]); }
}

/* ---- Add Order Message: 36 bytes --------------------------------------------- */

/* Add Order - No MPID Attribution Message. This message will be generated for unattributed orders accepted by the NASDAQ system. */
typedef struct {
  uint8_t order_reference_number[12];  /* bytes 0 to 11 */
  uint8_t buy_sell_indicator;          /* byte 12 */
  uint8_t shares[6];                   /* bytes 13 to 18 */
  uint8_t stock[6];                    /* bytes 19 to 24 */
  uint8_t price[10];                   /* bytes 25 to 34 */
  uint8_t display;                     /* byte 35 */
} AddOrderMessage;

/* any Add Order Message at all: every byte one the checker chooses */
static void any_add_order_message(AddOrderMessage *record) {
  for (size_t i = 0; i < 12; i++) { record->order_reference_number[i] = arbitrary(); }
  record->buy_sell_indicator = arbitrary();
  for (size_t i = 0; i < 6; i++) { record->shares[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->stock[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->price[i] = arbitrary(); }
  record->display = arbitrary();
}

/* Add Order Message to the wire: 36 bytes from at, returning where the next byte goes */
static size_t encode_add_order_message(const AddOrderMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->order_reference_number[i]; }
  wire[at++] = record->buy_sell_indicator;
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->shares[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->stock[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->price[i]; }
  wire[at++] = record->display;

  return at;
}

/* Add Order Message off the wire: 36 bytes from at, returning where the next byte lies */
static size_t decode_add_order_message(AddOrderMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 12; i++) { record->order_reference_number[i] = wire[at++]; }
  record->buy_sell_indicator = wire[at++];
  for (size_t i = 0; i < 6; i++) { record->shares[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->stock[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->price[i] = wire[at++]; }
  record->display = wire[at++];

  return at;
}

/* what was read of Add Order Message is what was written, byte for byte */
static void equal_add_order_message(const AddOrderMessage *read, const AddOrderMessage *written) {
  for (size_t i = 0; i < 12; i++) { assert(read->order_reference_number[i] == written->order_reference_number[i]); }
  assert(read->buy_sell_indicator == written->buy_sell_indicator);
  for (size_t i = 0; i < 6; i++) { assert(read->shares[i] == written->shares[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->stock[i] == written->stock[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->price[i] == written->price[i]); }
  assert(read->display == written->display);
}

/* Add Order Message: written and read back, then read and written back */
static void check_add_order_message(void) {
  AddOrderMessage sent;
  AddOrderMessage got;
  uint8_t wire[36];
  uint8_t again[36];

  any_add_order_message(&sent);
  assert(encode_add_order_message(&sent, wire, 0) == 36);
  assert(decode_add_order_message(&got, wire, 0) == 36);
  equal_add_order_message(&got, &sent);

  for (size_t i = 0; i < 36; i++) { wire[i] = arbitrary(); }
  assert(decode_add_order_message(&got, wire, 0) == 36);
  assert(encode_add_order_message(&got, again, 0) == 36);
  for (size_t i = 0; i < 36; i++) { assert(again[i] == wire[i]); }
}

/* ---- Add Order Mpid Attribution Message: 39 bytes ---------------------------- */

/* Add Order - MPID Attribution Message. This message will be generated for attributed orders and quotations accepted by the NASDAQ system. */
typedef struct {
  uint8_t order_reference_number[12];  /* bytes 0 to 11 */
  uint8_t buy_sell_indicator;          /* byte 12 */
  uint8_t shares[6];                   /* bytes 13 to 18 */
  uint8_t stock[6];                    /* bytes 19 to 24 */
  uint8_t price[10];                   /* bytes 25 to 34 */
  uint8_t attribution[4];              /* bytes 35 to 38 */
} AddOrderMpidAttributionMessage;

/* any Add Order Mpid Attribution Message at all: every byte one the checker chooses */
static void any_add_order_mpid_attribution_message(AddOrderMpidAttributionMessage *record) {
  for (size_t i = 0; i < 12; i++) { record->order_reference_number[i] = arbitrary(); }
  record->buy_sell_indicator = arbitrary();
  for (size_t i = 0; i < 6; i++) { record->shares[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->stock[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->attribution[i] = arbitrary(); }
}

/* Add Order Mpid Attribution Message to the wire: 39 bytes from at, returning where the next byte goes */
static size_t encode_add_order_mpid_attribution_message(const AddOrderMpidAttributionMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->order_reference_number[i]; }
  wire[at++] = record->buy_sell_indicator;
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->shares[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->stock[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->attribution[i]; }

  return at;
}

/* Add Order Mpid Attribution Message off the wire: 39 bytes from at, returning where the next byte lies */
static size_t decode_add_order_mpid_attribution_message(AddOrderMpidAttributionMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 12; i++) { record->order_reference_number[i] = wire[at++]; }
  record->buy_sell_indicator = wire[at++];
  for (size_t i = 0; i < 6; i++) { record->shares[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->stock[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->attribution[i] = wire[at++]; }

  return at;
}

/* what was read of Add Order Mpid Attribution Message is what was written, byte for byte */
static void equal_add_order_mpid_attribution_message(const AddOrderMpidAttributionMessage *read, const AddOrderMpidAttributionMessage *written) {
  for (size_t i = 0; i < 12; i++) { assert(read->order_reference_number[i] == written->order_reference_number[i]); }
  assert(read->buy_sell_indicator == written->buy_sell_indicator);
  for (size_t i = 0; i < 6; i++) { assert(read->shares[i] == written->shares[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->stock[i] == written->stock[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->price[i] == written->price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->attribution[i] == written->attribution[i]); }
}

/* Add Order Mpid Attribution Message: written and read back, then read and written back */
static void check_add_order_mpid_attribution_message(void) {
  AddOrderMpidAttributionMessage sent;
  AddOrderMpidAttributionMessage got;
  uint8_t wire[39];
  uint8_t again[39];

  any_add_order_mpid_attribution_message(&sent);
  assert(encode_add_order_mpid_attribution_message(&sent, wire, 0) == 39);
  assert(decode_add_order_mpid_attribution_message(&got, wire, 0) == 39);
  equal_add_order_mpid_attribution_message(&got, &sent);

  for (size_t i = 0; i < 39; i++) { wire[i] = arbitrary(); }
  assert(decode_add_order_mpid_attribution_message(&got, wire, 0) == 39);
  assert(encode_add_order_mpid_attribution_message(&got, again, 0) == 39);
  for (size_t i = 0; i < 39; i++) { assert(again[i] == wire[i]); }
}

/* ---- End Of Snapshot Message: 20 bytes --------------------------------------- */

/* The Snapshot message reflects the NASDAQ TotalView-ITCH 3.1f sequence number at the time that the GLIMPSE 3.1f spin was requested. */
typedef struct {
  uint8_t itch_sequence_number[20];  /* bytes 0 to 19 */
} EndOfSnapshotMessage;

/* any End Of Snapshot Message at all: every byte one the checker chooses */
static void any_end_of_snapshot_message(EndOfSnapshotMessage *record) {
  for (size_t i = 0; i < 20; i++) { record->itch_sequence_number[i] = arbitrary(); }
}

/* End Of Snapshot Message to the wire: 20 bytes from at, returning where the next byte goes */
static size_t encode_end_of_snapshot_message(const EndOfSnapshotMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->itch_sequence_number[i]; }

  return at;
}

/* End Of Snapshot Message off the wire: 20 bytes from at, returning where the next byte lies */
static size_t decode_end_of_snapshot_message(EndOfSnapshotMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 20; i++) { record->itch_sequence_number[i] = wire[at++]; }

  return at;
}

/* what was read of End Of Snapshot Message is what was written, byte for byte */
static void equal_end_of_snapshot_message(const EndOfSnapshotMessage *read, const EndOfSnapshotMessage *written) {
  for (size_t i = 0; i < 20; i++) { assert(read->itch_sequence_number[i] == written->itch_sequence_number[i]); }
}

/* End Of Snapshot Message: written and read back, then read and written back */
static void check_end_of_snapshot_message(void) {
  EndOfSnapshotMessage sent;
  EndOfSnapshotMessage got;
  uint8_t wire[20];
  uint8_t again[20];

  any_end_of_snapshot_message(&sent);
  assert(encode_end_of_snapshot_message(&sent, wire, 0) == 20);
  assert(decode_end_of_snapshot_message(&got, wire, 0) == 20);
  equal_end_of_snapshot_message(&got, &sent);

  for (size_t i = 0; i < 20; i++) { wire[i] = arbitrary(); }
  assert(decode_end_of_snapshot_message(&got, wire, 0) == 20);
  assert(encode_end_of_snapshot_message(&got, again, 0) == 20);
  for (size_t i = 0; i < 20; i++) { assert(again[i] == wire[i]); }
}

/* ---- What esbmc checks ------------------------------------------------------- */

/* every record of the protocol, each on its own buffers */
static void checks(void) {
  check_server_packet_header();
  check_login_accepted_packet();
  check_login_rejected_packet();
  check_sequenced_message_header();
  check_seconds_message();
  check_milliseconds_message();
  check_system_event_message();
  check_add_order_message();
  check_add_order_mpid_attribution_message();
  check_end_of_snapshot_message();
}

int main(void) {
#ifdef CONCRETE
  for (pattern = 0; pattern < 4; pattern++) { checks(); }
#else
  checks();
#endif

  return 0;
}
