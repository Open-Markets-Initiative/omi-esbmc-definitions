// nasdaq/phlxoptions/quoting/PhlxOptions_Quoting_v9_0_Server.c
/*
 * National Association of Securities Dealers Automated Quotations (Nasdaq) Specialized Quote Interface
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

/* ---- Msar Accept Message: 30 bytes ------------------------------------------- */

/* The MSAR Request was accepted by the matching engine. Sequenced. */
typedef struct {
  uint8_t badge[4];          /* bytes 0 to 3 */
  uint8_t message_id[8];     /* bytes 4 to 11 */
  uint8_t instrument_id[4];  /* bytes 12 to 15 */
  uint8_t msar_type;         /* byte 16 */
  uint8_t auction_id[4];     /* bytes 17 to 20 */
  uint8_t price[4];          /* bytes 21 to 24 */
  uint8_t side;              /* byte 25 */
  uint8_t contracts[4];      /* bytes 26 to 29 */
} MsarAcceptMessage;

/* any Msar Accept Message at all: every byte one the checker chooses */
static void any_msar_accept_message(MsarAcceptMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->badge[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->message_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->instrument_id[i] = arbitrary(); }
  record->msar_type = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->auction_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->price[i] = arbitrary(); }
  record->side = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->contracts[i] = arbitrary(); }
}

/* Msar Accept Message to the wire: 30 bytes from at, returning where the next byte goes */
static size_t encode_msar_accept_message(const MsarAcceptMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->badge[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->message_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument_id[i]; }
  wire[at++] = record->msar_type;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->auction_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->price[i]; }
  wire[at++] = record->side;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->contracts[i]; }

  return at;
}

/* Msar Accept Message off the wire: 30 bytes from at, returning where the next byte lies */
static size_t decode_msar_accept_message(MsarAcceptMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->badge[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->message_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->instrument_id[i] = wire[at++]; }
  record->msar_type = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->auction_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->price[i] = wire[at++]; }
  record->side = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->contracts[i] = wire[at++]; }

  return at;
}

/* what was read of Msar Accept Message is what was written, byte for byte */
static void equal_msar_accept_message(const MsarAcceptMessage *read, const MsarAcceptMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->badge[i] == written->badge[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->message_id[i] == written->message_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->instrument_id[i] == written->instrument_id[i]); }
  assert(read->msar_type == written->msar_type);
  for (size_t i = 0; i < 4; i++) { assert(read->auction_id[i] == written->auction_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->price[i] == written->price[i]); }
  assert(read->side == written->side);
  for (size_t i = 0; i < 4; i++) { assert(read->contracts[i] == written->contracts[i]); }
}

/* Msar Accept Message: written and read back, then read and written back */
static void check_msar_accept_message(void) {
  MsarAcceptMessage sent;
  MsarAcceptMessage got;
  uint8_t wire[30];
  uint8_t again[30];

  any_msar_accept_message(&sent);
  assert(encode_msar_accept_message(&sent, wire, 0) == 30);
  assert(decode_msar_accept_message(&got, wire, 0) == 30);
  equal_msar_accept_message(&got, &sent);

  for (size_t i = 0; i < 30; i++) { wire[i] = arbitrary(); }
  assert(decode_msar_accept_message(&got, wire, 0) == 30);
  assert(encode_msar_accept_message(&got, again, 0) == 30);
  for (size_t i = 0; i < 30; i++) { assert(again[i] == wire[i]); }
}

/* ---- Msar Reject Message: 13 bytes ------------------------------------------- */

/* The MSAR Request is invalid and therefore rejected. Sequenced. */
typedef struct {
  uint8_t badge[4];       /* bytes 0 to 3 */
  uint8_t message_id[8];  /* bytes 4 to 11 */
  uint8_t status_code;    /* byte 12 */
} MsarRejectMessage;

/* any Msar Reject Message at all: every byte one the checker chooses */
static void any_msar_reject_message(MsarRejectMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->badge[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->message_id[i] = arbitrary(); }
  record->status_code = arbitrary();
}

/* Msar Reject Message to the wire: 13 bytes from at, returning where the next byte goes */
static size_t encode_msar_reject_message(const MsarRejectMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->badge[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->message_id[i]; }
  wire[at++] = record->status_code;

  return at;
}

/* Msar Reject Message off the wire: 13 bytes from at, returning where the next byte lies */
static size_t decode_msar_reject_message(MsarRejectMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->badge[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->message_id[i] = wire[at++]; }
  record->status_code = wire[at++];

  return at;
}

/* what was read of Msar Reject Message is what was written, byte for byte */
static void equal_msar_reject_message(const MsarRejectMessage *read, const MsarRejectMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->badge[i] == written->badge[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->message_id[i] == written->message_id[i]); }
  assert(read->status_code == written->status_code);
}

/* Msar Reject Message: written and read back, then read and written back */
static void check_msar_reject_message(void) {
  MsarRejectMessage sent;
  MsarRejectMessage got;
  uint8_t wire[13];
  uint8_t again[13];

  any_msar_reject_message(&sent);
  assert(encode_msar_reject_message(&sent, wire, 0) == 13);
  assert(decode_msar_reject_message(&got, wire, 0) == 13);
  equal_msar_reject_message(&got, &sent);

  for (size_t i = 0; i < 13; i++) { wire[i] = arbitrary(); }
  assert(decode_msar_reject_message(&got, wire, 0) == 13);
  assert(encode_msar_reject_message(&got, again, 0) == 13);
  for (size_t i = 0; i < 13; i++) { assert(again[i] == wire[i]); }
}

/* ---- Complex Msar Accept Message: 35 bytes ----------------------------------- */

/* The Complex MSAR Request was accepted by the matching engine. Sequenced. */
typedef struct {
  uint8_t badge[4];          /* bytes 0 to 3 */
  uint8_t message_id[8];     /* bytes 4 to 11 */
  uint8_t instrument_id[4];  /* bytes 12 to 15 */
  uint8_t msar_type;         /* byte 16 */
  uint8_t auction_id[4];     /* bytes 17 to 20 */
  uint8_t price[4];          /* bytes 21 to 24 */
  uint8_t side;              /* byte 25 */
  uint8_t contracts[4];      /* bytes 26 to 29 */
  uint8_t price_protection;  /* byte 30 */
  uint8_t reserved_4[4];     /* bytes 31 to 34 */
} ComplexMsarAcceptMessage;

/* any Complex Msar Accept Message at all: every byte one the checker chooses */
static void any_complex_msar_accept_message(ComplexMsarAcceptMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->badge[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->message_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->instrument_id[i] = arbitrary(); }
  record->msar_type = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->auction_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->price[i] = arbitrary(); }
  record->side = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->contracts[i] = arbitrary(); }
  record->price_protection = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->reserved_4[i] = arbitrary(); }
}

/* Complex Msar Accept Message to the wire: 35 bytes from at, returning where the next byte goes */
static size_t encode_complex_msar_accept_message(const ComplexMsarAcceptMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->badge[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->message_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument_id[i]; }
  wire[at++] = record->msar_type;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->auction_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->price[i]; }
  wire[at++] = record->side;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->contracts[i]; }
  wire[at++] = record->price_protection;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->reserved_4[i]; }

  return at;
}

/* Complex Msar Accept Message off the wire: 35 bytes from at, returning where the next byte lies */
static size_t decode_complex_msar_accept_message(ComplexMsarAcceptMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->badge[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->message_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->instrument_id[i] = wire[at++]; }
  record->msar_type = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->auction_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->price[i] = wire[at++]; }
  record->side = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->contracts[i] = wire[at++]; }
  record->price_protection = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->reserved_4[i] = wire[at++]; }

  return at;
}

/* what was read of Complex Msar Accept Message is what was written, byte for byte */
static void equal_complex_msar_accept_message(const ComplexMsarAcceptMessage *read, const ComplexMsarAcceptMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->badge[i] == written->badge[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->message_id[i] == written->message_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->instrument_id[i] == written->instrument_id[i]); }
  assert(read->msar_type == written->msar_type);
  for (size_t i = 0; i < 4; i++) { assert(read->auction_id[i] == written->auction_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->price[i] == written->price[i]); }
  assert(read->side == written->side);
  for (size_t i = 0; i < 4; i++) { assert(read->contracts[i] == written->contracts[i]); }
  assert(read->price_protection == written->price_protection);
  for (size_t i = 0; i < 4; i++) { assert(read->reserved_4[i] == written->reserved_4[i]); }
}

/* Complex Msar Accept Message: written and read back, then read and written back */
static void check_complex_msar_accept_message(void) {
  ComplexMsarAcceptMessage sent;
  ComplexMsarAcceptMessage got;
  uint8_t wire[35];
  uint8_t again[35];

  any_complex_msar_accept_message(&sent);
  assert(encode_complex_msar_accept_message(&sent, wire, 0) == 35);
  assert(decode_complex_msar_accept_message(&got, wire, 0) == 35);
  equal_complex_msar_accept_message(&got, &sent);

  for (size_t i = 0; i < 35; i++) { wire[i] = arbitrary(); }
  assert(decode_complex_msar_accept_message(&got, wire, 0) == 35);
  assert(encode_complex_msar_accept_message(&got, again, 0) == 35);
  for (size_t i = 0; i < 35; i++) { assert(again[i] == wire[i]); }
}

/* ---- Complex Msar Reject Message: 13 bytes ----------------------------------- */

/* The Complex MSAR Request is invalid and therefore rejected. Sequenced. */
typedef struct {
  uint8_t badge[4];       /* bytes 0 to 3 */
  uint8_t message_id[8];  /* bytes 4 to 11 */
  uint8_t status_code;    /* byte 12 */
} ComplexMsarRejectMessage;

/* any Complex Msar Reject Message at all: every byte one the checker chooses */
static void any_complex_msar_reject_message(ComplexMsarRejectMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->badge[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->message_id[i] = arbitrary(); }
  record->status_code = arbitrary();
}

/* Complex Msar Reject Message to the wire: 13 bytes from at, returning where the next byte goes */
static size_t encode_complex_msar_reject_message(const ComplexMsarRejectMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->badge[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->message_id[i]; }
  wire[at++] = record->status_code;

  return at;
}

/* Complex Msar Reject Message off the wire: 13 bytes from at, returning where the next byte lies */
static size_t decode_complex_msar_reject_message(ComplexMsarRejectMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->badge[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->message_id[i] = wire[at++]; }
  record->status_code = wire[at++];

  return at;
}

/* what was read of Complex Msar Reject Message is what was written, byte for byte */
static void equal_complex_msar_reject_message(const ComplexMsarRejectMessage *read, const ComplexMsarRejectMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->badge[i] == written->badge[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->message_id[i] == written->message_id[i]); }
  assert(read->status_code == written->status_code);
}

/* Complex Msar Reject Message: written and read back, then read and written back */
static void check_complex_msar_reject_message(void) {
  ComplexMsarRejectMessage sent;
  ComplexMsarRejectMessage got;
  uint8_t wire[13];
  uint8_t again[13];

  any_complex_msar_reject_message(&sent);
  assert(encode_complex_msar_reject_message(&sent, wire, 0) == 13);
  assert(decode_complex_msar_reject_message(&got, wire, 0) == 13);
  equal_complex_msar_reject_message(&got, &sent);

  for (size_t i = 0; i < 13; i++) { wire[i] = arbitrary(); }
  assert(decode_complex_msar_reject_message(&got, wire, 0) == 13);
  assert(encode_complex_msar_reject_message(&got, again, 0) == 13);
  for (size_t i = 0; i < 13; i++) { assert(again[i] == wire[i]); }
}

/* ---- Underlying Permission Notification Message: 26 bytes -------------------- */

/* Sent once per badge/underlying pair, typically right after the instrument directory messages, and intra-day when permissions change. Sequenced. */
typedef struct {
  uint8_t seconds[4];      /* bytes 0 to 3 */
  uint8_t nanoseconds[4];  /* bytes 4 to 7 */
  uint8_t badge[4];        /* bytes 8 to 11 */
  uint8_t underlying[13];  /* bytes 12 to 24 */
  uint8_t permitted;       /* byte 25 */
} UnderlyingPermissionNotificationMessage;

/* any Underlying Permission Notification Message at all: every byte one the checker chooses */
static void any_underlying_permission_notification_message(UnderlyingPermissionNotificationMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->seconds[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->badge[i] = arbitrary(); }
  for (size_t i = 0; i < 13; i++) { record->underlying[i] = arbitrary(); }
  record->permitted = arbitrary();
}

/* Underlying Permission Notification Message to the wire: 26 bytes from at, returning where the next byte goes */
static size_t encode_underlying_permission_notification_message(const UnderlyingPermissionNotificationMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->seconds[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->nanoseconds[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->badge[i]; }
  for (size_t i = 0; i < 13; i++) { wire[at++] = record->underlying[i]; }
  wire[at++] = record->permitted;

  return at;
}

/* Underlying Permission Notification Message off the wire: 26 bytes from at, returning where the next byte lies */
static size_t decode_underlying_permission_notification_message(UnderlyingPermissionNotificationMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->seconds[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->badge[i] = wire[at++]; }
  for (size_t i = 0; i < 13; i++) { record->underlying[i] = wire[at++]; }
  record->permitted = wire[at++];

  return at;
}

/* what was read of Underlying Permission Notification Message is what was written, byte for byte */
static void equal_underlying_permission_notification_message(const UnderlyingPermissionNotificationMessage *read, const UnderlyingPermissionNotificationMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->seconds[i] == written->seconds[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->nanoseconds[i] == written->nanoseconds[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->badge[i] == written->badge[i]); }
  for (size_t i = 0; i < 13; i++) { assert(read->underlying[i] == written->underlying[i]); }
  assert(read->permitted == written->permitted);
}

/* Underlying Permission Notification Message: written and read back, then read and written back */
static void check_underlying_permission_notification_message(void) {
  UnderlyingPermissionNotificationMessage sent;
  UnderlyingPermissionNotificationMessage got;
  uint8_t wire[26];
  uint8_t again[26];

  any_underlying_permission_notification_message(&sent);
  assert(encode_underlying_permission_notification_message(&sent, wire, 0) == 26);
  assert(decode_underlying_permission_notification_message(&got, wire, 0) == 26);
  equal_underlying_permission_notification_message(&got, &sent);

  for (size_t i = 0; i < 26; i++) { wire[i] = arbitrary(); }
  assert(decode_underlying_permission_notification_message(&got, wire, 0) == 26);
  assert(encode_underlying_permission_notification_message(&got, again, 0) == 26);
  for (size_t i = 0; i < 26; i++) { assert(again[i] == wire[i]); }
}

/* ---- Mm Parameter Definition Notification Message: 74 bytes ------------------ */

/* Optionally delivered participant per-underlying/instrument type configuration settings. Sequenced. */
typedef struct {
  uint8_t seconds[4];       /* bytes 0 to 3 */
  uint8_t nanoseconds[4];   /* bytes 4 to 7 */
  uint8_t badge[4];         /* bytes 8 to 11 */
  uint8_t instrument_type;  /* byte 12 */
  uint8_t underlying[13];   /* bytes 13 to 25 */
  uint8_t interval[2];      /* bytes 26 to 27 */
  uint8_t percentage[2];    /* bytes 28 to 29 */
  uint8_t cum_qty[4];       /* bytes 30 to 33 */
  uint8_t delta[4];         /* bytes 34 to 37 */
  uint8_t vega[4];          /* bytes 38 to 41 */
  uint8_t reserved_32[32];  /* bytes 42 to 73 */
} MmParameterDefinitionNotificationMessage;

/* any Mm Parameter Definition Notification Message at all: every byte one the checker chooses */
static void any_mm_parameter_definition_notification_message(MmParameterDefinitionNotificationMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->seconds[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->badge[i] = arbitrary(); }
  record->instrument_type = arbitrary();
  for (size_t i = 0; i < 13; i++) { record->underlying[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->interval[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->percentage[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->cum_qty[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->delta[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->vega[i] = arbitrary(); }
  for (size_t i = 0; i < 32; i++) { record->reserved_32[i] = arbitrary(); }
}

/* Mm Parameter Definition Notification Message to the wire: 74 bytes from at, returning where the next byte goes */
static size_t encode_mm_parameter_definition_notification_message(const MmParameterDefinitionNotificationMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->seconds[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->nanoseconds[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->badge[i]; }
  wire[at++] = record->instrument_type;
  for (size_t i = 0; i < 13; i++) { wire[at++] = record->underlying[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->interval[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->percentage[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->cum_qty[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->delta[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->vega[i]; }
  for (size_t i = 0; i < 32; i++) { wire[at++] = record->reserved_32[i]; }

  return at;
}

/* Mm Parameter Definition Notification Message off the wire: 74 bytes from at, returning where the next byte lies */
static size_t decode_mm_parameter_definition_notification_message(MmParameterDefinitionNotificationMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->seconds[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->badge[i] = wire[at++]; }
  record->instrument_type = wire[at++];
  for (size_t i = 0; i < 13; i++) { record->underlying[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->interval[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->percentage[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->cum_qty[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->delta[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->vega[i] = wire[at++]; }
  for (size_t i = 0; i < 32; i++) { record->reserved_32[i] = wire[at++]; }

  return at;
}

/* what was read of Mm Parameter Definition Notification Message is what was written, byte for byte */
static void equal_mm_parameter_definition_notification_message(const MmParameterDefinitionNotificationMessage *read, const MmParameterDefinitionNotificationMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->seconds[i] == written->seconds[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->nanoseconds[i] == written->nanoseconds[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->badge[i] == written->badge[i]); }
  assert(read->instrument_type == written->instrument_type);
  for (size_t i = 0; i < 13; i++) { assert(read->underlying[i] == written->underlying[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->interval[i] == written->interval[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->percentage[i] == written->percentage[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->cum_qty[i] == written->cum_qty[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->delta[i] == written->delta[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->vega[i] == written->vega[i]); }
  for (size_t i = 0; i < 32; i++) { assert(read->reserved_32[i] == written->reserved_32[i]); }
}

/* Mm Parameter Definition Notification Message: written and read back, then read and written back */
static void check_mm_parameter_definition_notification_message(void) {
  MmParameterDefinitionNotificationMessage sent;
  MmParameterDefinitionNotificationMessage got;
  uint8_t wire[74];
  uint8_t again[74];

  any_mm_parameter_definition_notification_message(&sent);
  assert(encode_mm_parameter_definition_notification_message(&sent, wire, 0) == 74);
  assert(decode_mm_parameter_definition_notification_message(&got, wire, 0) == 74);
  equal_mm_parameter_definition_notification_message(&got, &sent);

  for (size_t i = 0; i < 74; i++) { wire[i] = arbitrary(); }
  assert(decode_mm_parameter_definition_notification_message(&got, wire, 0) == 74);
  assert(encode_mm_parameter_definition_notification_message(&got, again, 0) == 74);
  for (size_t i = 0; i < 74; i++) { assert(again[i] == wire[i]); }
}

/* ---- Rapid Fire Config Notification Message: 33 bytes ------------------------ */

/* Rapid Fire/Curtailment Config Notification, Phlx, NOM and NTX only (replaced by MM Parameter Definition Notification for ISE, GEMX and MRX). Sequenced. */
typedef struct {
  uint8_t seconds[4];      /* bytes 0 to 3 */
  uint8_t nanoseconds[4];  /* bytes 4 to 7 */
  uint8_t badge[4];        /* bytes 8 to 11 */
  uint8_t underlying[13];  /* bytes 12 to 24 */
  uint8_t percentage[2];   /* bytes 25 to 26 */
  uint8_t interval[2];     /* bytes 27 to 28 */
  uint8_t volume[4];       /* bytes 29 to 32 */
} RapidFireConfigNotificationMessage;

/* any Rapid Fire Config Notification Message at all: every byte one the checker chooses */
static void any_rapid_fire_config_notification_message(RapidFireConfigNotificationMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->seconds[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->badge[i] = arbitrary(); }
  for (size_t i = 0; i < 13; i++) { record->underlying[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->percentage[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->interval[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->volume[i] = arbitrary(); }
}

/* Rapid Fire Config Notification Message to the wire: 33 bytes from at, returning where the next byte goes */
static size_t encode_rapid_fire_config_notification_message(const RapidFireConfigNotificationMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->seconds[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->nanoseconds[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->badge[i]; }
  for (size_t i = 0; i < 13; i++) { wire[at++] = record->underlying[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->percentage[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->interval[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->volume[i]; }

  return at;
}

/* Rapid Fire Config Notification Message off the wire: 33 bytes from at, returning where the next byte lies */
static size_t decode_rapid_fire_config_notification_message(RapidFireConfigNotificationMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->seconds[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->badge[i] = wire[at++]; }
  for (size_t i = 0; i < 13; i++) { record->underlying[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->percentage[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->interval[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->volume[i] = wire[at++]; }

  return at;
}

/* what was read of Rapid Fire Config Notification Message is what was written, byte for byte */
static void equal_rapid_fire_config_notification_message(const RapidFireConfigNotificationMessage *read, const RapidFireConfigNotificationMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->seconds[i] == written->seconds[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->nanoseconds[i] == written->nanoseconds[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->badge[i] == written->badge[i]); }
  for (size_t i = 0; i < 13; i++) { assert(read->underlying[i] == written->underlying[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->percentage[i] == written->percentage[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->interval[i] == written->interval[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->volume[i] == written->volume[i]); }
}

/* Rapid Fire Config Notification Message: written and read back, then read and written back */
static void check_rapid_fire_config_notification_message(void) {
  RapidFireConfigNotificationMessage sent;
  RapidFireConfigNotificationMessage got;
  uint8_t wire[33];
  uint8_t again[33];

  any_rapid_fire_config_notification_message(&sent);
  assert(encode_rapid_fire_config_notification_message(&sent, wire, 0) == 33);
  assert(decode_rapid_fire_config_notification_message(&got, wire, 0) == 33);
  equal_rapid_fire_config_notification_message(&got, &sent);

  for (size_t i = 0; i < 33; i++) { wire[i] = arbitrary(); }
  assert(decode_rapid_fire_config_notification_message(&got, wire, 0) == 33);
  assert(encode_rapid_fire_config_notification_message(&got, again, 0) == 33);
  for (size_t i = 0; i < 33; i++) { assert(again[i] == wire[i]); }
}

/* ---- Active Qp Self Replenishment Parameter Definition Notification Message: 61 bytes ---- */

/* Optionally delivered contract limit on the badges configured for ActiveQP. Sequenced. */
typedef struct {
  uint8_t seconds[4];             /* bytes 0 to 3 */
  uint8_t nanoseconds[4];         /* bytes 4 to 7 */
  uint8_t badge[4];               /* bytes 8 to 11 */
  uint8_t underlying[13];         /* bytes 12 to 24 */
  uint8_t set_contract_limit[4];  /* bytes 25 to 28 */
  uint8_t reserved_32[32];        /* bytes 29 to 60 */
} ActiveQpSelfReplenishmentParameterDefinitionNotificationMessage;

/* any Active Qp Self Replenishment Parameter Definition Notification Message at all: every byte one the checker chooses */
static void any_active_qp_self_replenishment_parameter_definition_notification_message(ActiveQpSelfReplenishmentParameterDefinitionNotificationMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->seconds[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->badge[i] = arbitrary(); }
  for (size_t i = 0; i < 13; i++) { record->underlying[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->set_contract_limit[i] = arbitrary(); }
  for (size_t i = 0; i < 32; i++) { record->reserved_32[i] = arbitrary(); }
}

/* Active Qp Self Replenishment Parameter Definition Notification Message to the wire: 61 bytes from at, returning where the next byte goes */
static size_t encode_active_qp_self_replenishment_parameter_definition_notification_message(const ActiveQpSelfReplenishmentParameterDefinitionNotificationMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->seconds[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->nanoseconds[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->badge[i]; }
  for (size_t i = 0; i < 13; i++) { wire[at++] = record->underlying[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->set_contract_limit[i]; }
  for (size_t i = 0; i < 32; i++) { wire[at++] = record->reserved_32[i]; }

  return at;
}

/* Active Qp Self Replenishment Parameter Definition Notification Message off the wire: 61 bytes from at, returning where the next byte lies */
static size_t decode_active_qp_self_replenishment_parameter_definition_notification_message(ActiveQpSelfReplenishmentParameterDefinitionNotificationMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->seconds[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->badge[i] = wire[at++]; }
  for (size_t i = 0; i < 13; i++) { record->underlying[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->set_contract_limit[i] = wire[at++]; }
  for (size_t i = 0; i < 32; i++) { record->reserved_32[i] = wire[at++]; }

  return at;
}

/* what was read of Active Qp Self Replenishment Parameter Definition Notification Message is what was written, byte for byte */
static void equal_active_qp_self_replenishment_parameter_definition_notification_message(const ActiveQpSelfReplenishmentParameterDefinitionNotificationMessage *read, const ActiveQpSelfReplenishmentParameterDefinitionNotificationMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->seconds[i] == written->seconds[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->nanoseconds[i] == written->nanoseconds[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->badge[i] == written->badge[i]); }
  for (size_t i = 0; i < 13; i++) { assert(read->underlying[i] == written->underlying[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->set_contract_limit[i] == written->set_contract_limit[i]); }
  for (size_t i = 0; i < 32; i++) { assert(read->reserved_32[i] == written->reserved_32[i]); }
}

/* Active Qp Self Replenishment Parameter Definition Notification Message: written and read back, then read and written back */
static void check_active_qp_self_replenishment_parameter_definition_notification_message(void) {
  ActiveQpSelfReplenishmentParameterDefinitionNotificationMessage sent;
  ActiveQpSelfReplenishmentParameterDefinitionNotificationMessage got;
  uint8_t wire[61];
  uint8_t again[61];

  any_active_qp_self_replenishment_parameter_definition_notification_message(&sent);
  assert(encode_active_qp_self_replenishment_parameter_definition_notification_message(&sent, wire, 0) == 61);
  assert(decode_active_qp_self_replenishment_parameter_definition_notification_message(&got, wire, 0) == 61);
  equal_active_qp_self_replenishment_parameter_definition_notification_message(&got, &sent);

  for (size_t i = 0; i < 61; i++) { wire[i] = arbitrary(); }
  assert(decode_active_qp_self_replenishment_parameter_definition_notification_message(&got, wire, 0) == 61);
  assert(encode_active_qp_self_replenishment_parameter_definition_notification_message(&got, again, 0) == 61);
  for (size_t i = 0; i < 61; i++) { assert(again[i] == wire[i]); }
}

/* ---- System Event Message: 11 bytes ------------------------------------------ */

/* Signals a market or data feed handler event. Sequenced. */
typedef struct {
  uint8_t seconds[4];      /* bytes 0 to 3 */
  uint8_t nanoseconds[4];  /* bytes 4 to 7 */
  uint8_t event_code;      /* byte 8 */
  uint8_t version;         /* byte 9 */
  uint8_t sub_version;     /* byte 10 */
} SystemEventMessage;

/* any System Event Message at all: every byte one the checker chooses */
static void any_system_event_message(SystemEventMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->seconds[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = arbitrary(); }
  record->event_code = arbitrary();
  record->version = arbitrary();
  record->sub_version = arbitrary();
}

/* System Event Message to the wire: 11 bytes from at, returning where the next byte goes */
static size_t encode_system_event_message(const SystemEventMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->seconds[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->nanoseconds[i]; }
  wire[at++] = record->event_code;
  wire[at++] = record->version;
  wire[at++] = record->sub_version;

  return at;
}

/* System Event Message off the wire: 11 bytes from at, returning where the next byte lies */
static size_t decode_system_event_message(SystemEventMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->seconds[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = wire[at++]; }
  record->event_code = wire[at++];
  record->version = wire[at++];
  record->sub_version = wire[at++];

  return at;
}

/* what was read of System Event Message is what was written, byte for byte */
static void equal_system_event_message(const SystemEventMessage *read, const SystemEventMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->seconds[i] == written->seconds[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->nanoseconds[i] == written->nanoseconds[i]); }
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

/* ---- Simple Instrument Directory Message: 59 bytes --------------------------- */

/* Disseminated at the start of each trading day for all symbols trading on the system, and intra-day when attributes change. Sequenced. */
typedef struct {
  uint8_t seconds[4];             /* bytes 0 to 3 */
  uint8_t nanoseconds[4];         /* bytes 4 to 7 */
  uint8_t instrument_id[4];       /* bytes 8 to 11 */
  uint8_t security_symbol[8];     /* bytes 12 to 19 */
  uint8_t expiration[2];          /* bytes 20 to 21 */
  uint8_t strike_price[4];        /* bytes 22 to 25 */
  uint8_t option_type;            /* byte 26 */
  uint8_t underlying_symbol[13];  /* bytes 27 to 39 */
  uint8_t closing_type;           /* byte 40 */
  uint8_t tradable;               /* byte 41 */
  uint8_t mpv;                    /* byte 42 */
  uint8_t reserved_16[16];        /* bytes 43 to 58 */
} SimpleInstrumentDirectoryMessage;

/* any Simple Instrument Directory Message at all: every byte one the checker chooses */
static void any_simple_instrument_directory_message(SimpleInstrumentDirectoryMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->seconds[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->instrument_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->security_symbol[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->expiration[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->strike_price[i] = arbitrary(); }
  record->option_type = arbitrary();
  for (size_t i = 0; i < 13; i++) { record->underlying_symbol[i] = arbitrary(); }
  record->closing_type = arbitrary();
  record->tradable = arbitrary();
  record->mpv = arbitrary();
  for (size_t i = 0; i < 16; i++) { record->reserved_16[i] = arbitrary(); }
}

/* Simple Instrument Directory Message to the wire: 59 bytes from at, returning where the next byte goes */
static size_t encode_simple_instrument_directory_message(const SimpleInstrumentDirectoryMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->seconds[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->nanoseconds[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->security_symbol[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->expiration[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->strike_price[i]; }
  wire[at++] = record->option_type;
  for (size_t i = 0; i < 13; i++) { wire[at++] = record->underlying_symbol[i]; }
  wire[at++] = record->closing_type;
  wire[at++] = record->tradable;
  wire[at++] = record->mpv;
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->reserved_16[i]; }

  return at;
}

/* Simple Instrument Directory Message off the wire: 59 bytes from at, returning where the next byte lies */
static size_t decode_simple_instrument_directory_message(SimpleInstrumentDirectoryMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->seconds[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->instrument_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->security_symbol[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->expiration[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->strike_price[i] = wire[at++]; }
  record->option_type = wire[at++];
  for (size_t i = 0; i < 13; i++) { record->underlying_symbol[i] = wire[at++]; }
  record->closing_type = wire[at++];
  record->tradable = wire[at++];
  record->mpv = wire[at++];
  for (size_t i = 0; i < 16; i++) { record->reserved_16[i] = wire[at++]; }

  return at;
}

/* what was read of Simple Instrument Directory Message is what was written, byte for byte */
static void equal_simple_instrument_directory_message(const SimpleInstrumentDirectoryMessage *read, const SimpleInstrumentDirectoryMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->seconds[i] == written->seconds[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->nanoseconds[i] == written->nanoseconds[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->instrument_id[i] == written->instrument_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->security_symbol[i] == written->security_symbol[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->expiration[i] == written->expiration[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->strike_price[i] == written->strike_price[i]); }
  assert(read->option_type == written->option_type);
  for (size_t i = 0; i < 13; i++) { assert(read->underlying_symbol[i] == written->underlying_symbol[i]); }
  assert(read->closing_type == written->closing_type);
  assert(read->tradable == written->tradable);
  assert(read->mpv == written->mpv);
  for (size_t i = 0; i < 16; i++) { assert(read->reserved_16[i] == written->reserved_16[i]); }
}

/* Simple Instrument Directory Message: written and read back, then read and written back */
static void check_simple_instrument_directory_message(void) {
  SimpleInstrumentDirectoryMessage sent;
  SimpleInstrumentDirectoryMessage got;
  uint8_t wire[59];
  uint8_t again[59];

  any_simple_instrument_directory_message(&sent);
  assert(encode_simple_instrument_directory_message(&sent, wire, 0) == 59);
  assert(decode_simple_instrument_directory_message(&got, wire, 0) == 59);
  equal_simple_instrument_directory_message(&got, &sent);

  for (size_t i = 0; i < 59; i++) { wire[i] = arbitrary(); }
  assert(decode_simple_instrument_directory_message(&got, wire, 0) == 59);
  assert(encode_simple_instrument_directory_message(&got, again, 0) == 59);
  for (size_t i = 0; i < 59; i++) { assert(again[i] == wire[i]); }
}

/* ---- Simple Instrument Trading Action Message: 13 bytes ---------------------- */

/* Relays changes in trading status for a simple instrument. Sequenced. */
typedef struct {
  uint8_t seconds[4];        /* bytes 0 to 3 */
  uint8_t nanoseconds[4];    /* bytes 4 to 7 */
  uint8_t instrument_id[4];  /* bytes 8 to 11 */
  uint8_t trading_state;     /* byte 12 */
} SimpleInstrumentTradingActionMessage;

/* any Simple Instrument Trading Action Message at all: every byte one the checker chooses */
static void any_simple_instrument_trading_action_message(SimpleInstrumentTradingActionMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->seconds[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->instrument_id[i] = arbitrary(); }
  record->trading_state = arbitrary();
}

/* Simple Instrument Trading Action Message to the wire: 13 bytes from at, returning where the next byte goes */
static size_t encode_simple_instrument_trading_action_message(const SimpleInstrumentTradingActionMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->seconds[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->nanoseconds[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument_id[i]; }
  wire[at++] = record->trading_state;

  return at;
}

/* Simple Instrument Trading Action Message off the wire: 13 bytes from at, returning where the next byte lies */
static size_t decode_simple_instrument_trading_action_message(SimpleInstrumentTradingActionMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->seconds[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->instrument_id[i] = wire[at++]; }
  record->trading_state = wire[at++];

  return at;
}

/* what was read of Simple Instrument Trading Action Message is what was written, byte for byte */
static void equal_simple_instrument_trading_action_message(const SimpleInstrumentTradingActionMessage *read, const SimpleInstrumentTradingActionMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->seconds[i] == written->seconds[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->nanoseconds[i] == written->nanoseconds[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->instrument_id[i] == written->instrument_id[i]); }
  assert(read->trading_state == written->trading_state);
}

/* Simple Instrument Trading Action Message: written and read back, then read and written back */
static void check_simple_instrument_trading_action_message(void) {
  SimpleInstrumentTradingActionMessage sent;
  SimpleInstrumentTradingActionMessage got;
  uint8_t wire[13];
  uint8_t again[13];

  any_simple_instrument_trading_action_message(&sent);
  assert(encode_simple_instrument_trading_action_message(&sent, wire, 0) == 13);
  assert(decode_simple_instrument_trading_action_message(&got, wire, 0) == 13);
  equal_simple_instrument_trading_action_message(&got, &sent);

  for (size_t i = 0; i < 13; i++) { wire[i] = arbitrary(); }
  assert(decode_simple_instrument_trading_action_message(&got, wire, 0) == 13);
  assert(encode_simple_instrument_trading_action_message(&got, again, 0) == 13);
  for (size_t i = 0; i < 13; i++) { assert(again[i] == wire[i]); }
}

/* ---- Complex Instrument Trading Action Message: 13 bytes --------------------- */

/* Relays changes in trading status for a complex strategy. Sequenced. */
typedef struct {
  uint8_t seconds[4];        /* bytes 0 to 3 */
  uint8_t nanoseconds[4];    /* bytes 4 to 7 */
  uint8_t instrument_id[4];  /* bytes 8 to 11 */
  uint8_t trading_state;     /* byte 12 */
} ComplexInstrumentTradingActionMessage;

/* any Complex Instrument Trading Action Message at all: every byte one the checker chooses */
static void any_complex_instrument_trading_action_message(ComplexInstrumentTradingActionMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->seconds[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->instrument_id[i] = arbitrary(); }
  record->trading_state = arbitrary();
}

/* Complex Instrument Trading Action Message to the wire: 13 bytes from at, returning where the next byte goes */
static size_t encode_complex_instrument_trading_action_message(const ComplexInstrumentTradingActionMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->seconds[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->nanoseconds[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument_id[i]; }
  wire[at++] = record->trading_state;

  return at;
}

/* Complex Instrument Trading Action Message off the wire: 13 bytes from at, returning where the next byte lies */
static size_t decode_complex_instrument_trading_action_message(ComplexInstrumentTradingActionMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->seconds[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->instrument_id[i] = wire[at++]; }
  record->trading_state = wire[at++];

  return at;
}

/* what was read of Complex Instrument Trading Action Message is what was written, byte for byte */
static void equal_complex_instrument_trading_action_message(const ComplexInstrumentTradingActionMessage *read, const ComplexInstrumentTradingActionMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->seconds[i] == written->seconds[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->nanoseconds[i] == written->nanoseconds[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->instrument_id[i] == written->instrument_id[i]); }
  assert(read->trading_state == written->trading_state);
}

/* Complex Instrument Trading Action Message: written and read back, then read and written back */
static void check_complex_instrument_trading_action_message(void) {
  ComplexInstrumentTradingActionMessage sent;
  ComplexInstrumentTradingActionMessage got;
  uint8_t wire[13];
  uint8_t again[13];

  any_complex_instrument_trading_action_message(&sent);
  assert(encode_complex_instrument_trading_action_message(&sent, wire, 0) == 13);
  assert(decode_complex_instrument_trading_action_message(&got, wire, 0) == 13);
  equal_complex_instrument_trading_action_message(&got, &sent);

  for (size_t i = 0; i < 13; i++) { wire[i] = arbitrary(); }
  assert(decode_complex_instrument_trading_action_message(&got, wire, 0) == 13);
  assert(encode_complex_instrument_trading_action_message(&got, again, 0) == 13);
  for (size_t i = 0; i < 13; i++) { assert(again[i] == wire[i]); }
}

/* ---- Simple Quote Execution Notification Message: 46 bytes ------------------- */

/* Informs the firm that its quote for a given simple instrument has been executed. Only sent if subscribed. Sequenced. */
typedef struct {
  uint8_t seconds[4];           /* bytes 0 to 3 */
  uint8_t nanoseconds[4];       /* bytes 4 to 7 */
  uint8_t badge[4];             /* bytes 8 to 11 */
  uint8_t instrument_id[4];     /* bytes 12 to 15 */
  uint8_t message_id[8];        /* bytes 16 to 23 */
  uint8_t auction_id[4];        /* bytes 24 to 27 */
  uint8_t price[4];             /* bytes 28 to 31 */
  uint8_t side;                 /* byte 32 */
  uint8_t contracts[4];         /* bytes 33 to 36 */
  uint8_t liquidity_indicator;  /* byte 37 */
  uint8_t cross_id[4];          /* bytes 38 to 41 */
  uint8_t match_id[4];          /* bytes 42 to 45 */
} SimpleQuoteExecutionNotificationMessage;

/* any Simple Quote Execution Notification Message at all: every byte one the checker chooses */
static void any_simple_quote_execution_notification_message(SimpleQuoteExecutionNotificationMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->seconds[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->badge[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->instrument_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->message_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->auction_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->price[i] = arbitrary(); }
  record->side = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->contracts[i] = arbitrary(); }
  record->liquidity_indicator = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->cross_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->match_id[i] = arbitrary(); }
}

/* Simple Quote Execution Notification Message to the wire: 46 bytes from at, returning where the next byte goes */
static size_t encode_simple_quote_execution_notification_message(const SimpleQuoteExecutionNotificationMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->seconds[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->nanoseconds[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->badge[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->message_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->auction_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->price[i]; }
  wire[at++] = record->side;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->contracts[i]; }
  wire[at++] = record->liquidity_indicator;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->cross_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->match_id[i]; }

  return at;
}

/* Simple Quote Execution Notification Message off the wire: 46 bytes from at, returning where the next byte lies */
static size_t decode_simple_quote_execution_notification_message(SimpleQuoteExecutionNotificationMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->seconds[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->badge[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->instrument_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->message_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->auction_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->price[i] = wire[at++]; }
  record->side = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->contracts[i] = wire[at++]; }
  record->liquidity_indicator = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->cross_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->match_id[i] = wire[at++]; }

  return at;
}

/* what was read of Simple Quote Execution Notification Message is what was written, byte for byte */
static void equal_simple_quote_execution_notification_message(const SimpleQuoteExecutionNotificationMessage *read, const SimpleQuoteExecutionNotificationMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->seconds[i] == written->seconds[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->nanoseconds[i] == written->nanoseconds[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->badge[i] == written->badge[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->instrument_id[i] == written->instrument_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->message_id[i] == written->message_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->auction_id[i] == written->auction_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->price[i] == written->price[i]); }
  assert(read->side == written->side);
  for (size_t i = 0; i < 4; i++) { assert(read->contracts[i] == written->contracts[i]); }
  assert(read->liquidity_indicator == written->liquidity_indicator);
  for (size_t i = 0; i < 4; i++) { assert(read->cross_id[i] == written->cross_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->match_id[i] == written->match_id[i]); }
}

/* Simple Quote Execution Notification Message: written and read back, then read and written back */
static void check_simple_quote_execution_notification_message(void) {
  SimpleQuoteExecutionNotificationMessage sent;
  SimpleQuoteExecutionNotificationMessage got;
  uint8_t wire[46];
  uint8_t again[46];

  any_simple_quote_execution_notification_message(&sent);
  assert(encode_simple_quote_execution_notification_message(&sent, wire, 0) == 46);
  assert(decode_simple_quote_execution_notification_message(&got, wire, 0) == 46);
  equal_simple_quote_execution_notification_message(&got, &sent);

  for (size_t i = 0; i < 46; i++) { wire[i] = arbitrary(); }
  assert(decode_simple_quote_execution_notification_message(&got, wire, 0) == 46);
  assert(encode_simple_quote_execution_notification_message(&got, again, 0) == 46);
  for (size_t i = 0; i < 46; i++) { assert(again[i] == wire[i]); }
}

/* ---- Complex Quote Execution Notification Message: 50 bytes ------------------ */

/* Informs the participant that its quote for a given complex instrument has been executed. Sequenced. */
typedef struct {
  uint8_t seconds[4];           /* bytes 0 to 3 */
  uint8_t nanoseconds[4];       /* bytes 4 to 7 */
  uint8_t badge[4];             /* bytes 8 to 11 */
  uint8_t message_id[8];        /* bytes 12 to 19 */
  uint8_t instrument_id[4];     /* bytes 20 to 23 */
  uint8_t auction_id[4];        /* bytes 24 to 27 */
  uint8_t price_6[8];           /* bytes 28 to 35 */
  uint8_t side;                 /* byte 36 */
  uint8_t contracts[4];         /* bytes 37 to 40 */
  uint8_t liquidity_indicator;  /* byte 41 */
  uint8_t cross_id[4];          /* bytes 42 to 45 */
  uint8_t match_id[4];          /* bytes 46 to 49 */
} ComplexQuoteExecutionNotificationMessage;

/* any Complex Quote Execution Notification Message at all: every byte one the checker chooses */
static void any_complex_quote_execution_notification_message(ComplexQuoteExecutionNotificationMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->seconds[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->badge[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->message_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->instrument_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->auction_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->price_6[i] = arbitrary(); }
  record->side = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->contracts[i] = arbitrary(); }
  record->liquidity_indicator = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->cross_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->match_id[i] = arbitrary(); }
}

/* Complex Quote Execution Notification Message to the wire: 50 bytes from at, returning where the next byte goes */
static size_t encode_complex_quote_execution_notification_message(const ComplexQuoteExecutionNotificationMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->seconds[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->nanoseconds[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->badge[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->message_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->auction_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price_6[i]; }
  wire[at++] = record->side;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->contracts[i]; }
  wire[at++] = record->liquidity_indicator;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->cross_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->match_id[i]; }

  return at;
}

/* Complex Quote Execution Notification Message off the wire: 50 bytes from at, returning where the next byte lies */
static size_t decode_complex_quote_execution_notification_message(ComplexQuoteExecutionNotificationMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->seconds[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->badge[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->message_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->instrument_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->auction_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->price_6[i] = wire[at++]; }
  record->side = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->contracts[i] = wire[at++]; }
  record->liquidity_indicator = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->cross_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->match_id[i] = wire[at++]; }

  return at;
}

/* what was read of Complex Quote Execution Notification Message is what was written, byte for byte */
static void equal_complex_quote_execution_notification_message(const ComplexQuoteExecutionNotificationMessage *read, const ComplexQuoteExecutionNotificationMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->seconds[i] == written->seconds[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->nanoseconds[i] == written->nanoseconds[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->badge[i] == written->badge[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->message_id[i] == written->message_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->instrument_id[i] == written->instrument_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->auction_id[i] == written->auction_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->price_6[i] == written->price_6[i]); }
  assert(read->side == written->side);
  for (size_t i = 0; i < 4; i++) { assert(read->contracts[i] == written->contracts[i]); }
  assert(read->liquidity_indicator == written->liquidity_indicator);
  for (size_t i = 0; i < 4; i++) { assert(read->cross_id[i] == written->cross_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->match_id[i] == written->match_id[i]); }
}

/* Complex Quote Execution Notification Message: written and read back, then read and written back */
static void check_complex_quote_execution_notification_message(void) {
  ComplexQuoteExecutionNotificationMessage sent;
  ComplexQuoteExecutionNotificationMessage got;
  uint8_t wire[50];
  uint8_t again[50];

  any_complex_quote_execution_notification_message(&sent);
  assert(encode_complex_quote_execution_notification_message(&sent, wire, 0) == 50);
  assert(decode_complex_quote_execution_notification_message(&got, wire, 0) == 50);
  equal_complex_quote_execution_notification_message(&got, &sent);

  for (size_t i = 0; i < 50; i++) { wire[i] = arbitrary(); }
  assert(decode_complex_quote_execution_notification_message(&got, wire, 0) == 50);
  assert(encode_complex_quote_execution_notification_message(&got, again, 0) == 50);
  for (size_t i = 0; i < 50; i++) { assert(again[i] == wire[i]); }
}

/* ---- Complex Quote Leg Execution Notification Message: 55 bytes -------------- */

/* Leg level execution of a quote in a complex instrument. Sequenced. */
typedef struct {
  uint8_t seconds[4];            /* bytes 0 to 3 */
  uint8_t nanoseconds[4];        /* bytes 4 to 7 */
  uint8_t badge[4];              /* bytes 8 to 11 */
  uint8_t message_id[8];         /* bytes 12 to 19 */
  uint8_t instrument_id[4];      /* bytes 20 to 23 */
  uint8_t leg_instrument_id[4];  /* bytes 24 to 27 */
  uint8_t leg_id;                /* byte 28 */
  uint8_t auction_id[4];         /* bytes 29 to 32 */
  uint8_t price_6[8];            /* bytes 33 to 40 */
  uint8_t side;                  /* byte 41 */
  uint8_t contracts[4];          /* bytes 42 to 45 */
  uint8_t liquidity_indicator;   /* byte 46 */
  uint8_t cross_id[4];           /* bytes 47 to 50 */
  uint8_t match_id[4];           /* bytes 51 to 54 */
} ComplexQuoteLegExecutionNotificationMessage;

/* any Complex Quote Leg Execution Notification Message at all: every byte one the checker chooses */
static void any_complex_quote_leg_execution_notification_message(ComplexQuoteLegExecutionNotificationMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->seconds[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->badge[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->message_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->instrument_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->leg_instrument_id[i] = arbitrary(); }
  record->leg_id = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->auction_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->price_6[i] = arbitrary(); }
  record->side = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->contracts[i] = arbitrary(); }
  record->liquidity_indicator = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->cross_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->match_id[i] = arbitrary(); }
}

/* Complex Quote Leg Execution Notification Message to the wire: 55 bytes from at, returning where the next byte goes */
static size_t encode_complex_quote_leg_execution_notification_message(const ComplexQuoteLegExecutionNotificationMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->seconds[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->nanoseconds[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->badge[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->message_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->leg_instrument_id[i]; }
  wire[at++] = record->leg_id;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->auction_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price_6[i]; }
  wire[at++] = record->side;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->contracts[i]; }
  wire[at++] = record->liquidity_indicator;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->cross_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->match_id[i]; }

  return at;
}

/* Complex Quote Leg Execution Notification Message off the wire: 55 bytes from at, returning where the next byte lies */
static size_t decode_complex_quote_leg_execution_notification_message(ComplexQuoteLegExecutionNotificationMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->seconds[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->badge[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->message_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->instrument_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->leg_instrument_id[i] = wire[at++]; }
  record->leg_id = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->auction_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->price_6[i] = wire[at++]; }
  record->side = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->contracts[i] = wire[at++]; }
  record->liquidity_indicator = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->cross_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->match_id[i] = wire[at++]; }

  return at;
}

/* what was read of Complex Quote Leg Execution Notification Message is what was written, byte for byte */
static void equal_complex_quote_leg_execution_notification_message(const ComplexQuoteLegExecutionNotificationMessage *read, const ComplexQuoteLegExecutionNotificationMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->seconds[i] == written->seconds[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->nanoseconds[i] == written->nanoseconds[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->badge[i] == written->badge[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->message_id[i] == written->message_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->instrument_id[i] == written->instrument_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->leg_instrument_id[i] == written->leg_instrument_id[i]); }
  assert(read->leg_id == written->leg_id);
  for (size_t i = 0; i < 4; i++) { assert(read->auction_id[i] == written->auction_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->price_6[i] == written->price_6[i]); }
  assert(read->side == written->side);
  for (size_t i = 0; i < 4; i++) { assert(read->contracts[i] == written->contracts[i]); }
  assert(read->liquidity_indicator == written->liquidity_indicator);
  for (size_t i = 0; i < 4; i++) { assert(read->cross_id[i] == written->cross_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->match_id[i] == written->match_id[i]); }
}

/* Complex Quote Leg Execution Notification Message: written and read back, then read and written back */
static void check_complex_quote_leg_execution_notification_message(void) {
  ComplexQuoteLegExecutionNotificationMessage sent;
  ComplexQuoteLegExecutionNotificationMessage got;
  uint8_t wire[55];
  uint8_t again[55];

  any_complex_quote_leg_execution_notification_message(&sent);
  assert(encode_complex_quote_leg_execution_notification_message(&sent, wire, 0) == 55);
  assert(decode_complex_quote_leg_execution_notification_message(&got, wire, 0) == 55);
  equal_complex_quote_leg_execution_notification_message(&got, &sent);

  for (size_t i = 0; i < 55; i++) { wire[i] = arbitrary(); }
  assert(decode_complex_quote_leg_execution_notification_message(&got, wire, 0) == 55);
  assert(encode_complex_quote_leg_execution_notification_message(&got, again, 0) == 55);
  for (size_t i = 0; i < 55; i++) { assert(again[i] == wire[i]); }
}

/* ---- Simple Msar Notification Message: 47 bytes ------------------------------ */

/* Execution Notification Message: the MSAR Request for a given simple instrument has been executed or cancelled. The Side field reflects the side being swept. Sequenced. */
typedef struct {
  uint8_t seconds[4];           /* bytes 0 to 3 */
  uint8_t nanoseconds[4];       /* bytes 4 to 7 */
  uint8_t badge[4];             /* bytes 8 to 11 */
  uint8_t instrument_id[4];     /* bytes 12 to 15 */
  uint8_t notification_type;    /* byte 16 */
  uint8_t message_id[8];        /* bytes 17 to 24 */
  uint8_t auction_id[4];        /* bytes 25 to 28 */
  uint8_t price[4];             /* bytes 29 to 32 */
  uint8_t side;                 /* byte 33 */
  uint8_t contracts[4];         /* bytes 34 to 37 */
  uint8_t liquidity_indicator;  /* byte 38 */
  uint8_t cross_id[4];          /* bytes 39 to 42 */
  uint8_t match_id[4];          /* bytes 43 to 46 */
} SimpleMsarNotificationMessage;

/* any Simple Msar Notification Message at all: every byte one the checker chooses */
static void any_simple_msar_notification_message(SimpleMsarNotificationMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->seconds[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->badge[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->instrument_id[i] = arbitrary(); }
  record->notification_type = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->message_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->auction_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->price[i] = arbitrary(); }
  record->side = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->contracts[i] = arbitrary(); }
  record->liquidity_indicator = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->cross_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->match_id[i] = arbitrary(); }
}

/* Simple Msar Notification Message to the wire: 47 bytes from at, returning where the next byte goes */
static size_t encode_simple_msar_notification_message(const SimpleMsarNotificationMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->seconds[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->nanoseconds[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->badge[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument_id[i]; }
  wire[at++] = record->notification_type;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->message_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->auction_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->price[i]; }
  wire[at++] = record->side;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->contracts[i]; }
  wire[at++] = record->liquidity_indicator;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->cross_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->match_id[i]; }

  return at;
}

/* Simple Msar Notification Message off the wire: 47 bytes from at, returning where the next byte lies */
static size_t decode_simple_msar_notification_message(SimpleMsarNotificationMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->seconds[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->badge[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->instrument_id[i] = wire[at++]; }
  record->notification_type = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->message_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->auction_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->price[i] = wire[at++]; }
  record->side = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->contracts[i] = wire[at++]; }
  record->liquidity_indicator = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->cross_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->match_id[i] = wire[at++]; }

  return at;
}

/* what was read of Simple Msar Notification Message is what was written, byte for byte */
static void equal_simple_msar_notification_message(const SimpleMsarNotificationMessage *read, const SimpleMsarNotificationMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->seconds[i] == written->seconds[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->nanoseconds[i] == written->nanoseconds[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->badge[i] == written->badge[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->instrument_id[i] == written->instrument_id[i]); }
  assert(read->notification_type == written->notification_type);
  for (size_t i = 0; i < 8; i++) { assert(read->message_id[i] == written->message_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->auction_id[i] == written->auction_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->price[i] == written->price[i]); }
  assert(read->side == written->side);
  for (size_t i = 0; i < 4; i++) { assert(read->contracts[i] == written->contracts[i]); }
  assert(read->liquidity_indicator == written->liquidity_indicator);
  for (size_t i = 0; i < 4; i++) { assert(read->cross_id[i] == written->cross_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->match_id[i] == written->match_id[i]); }
}

/* Simple Msar Notification Message: written and read back, then read and written back */
static void check_simple_msar_notification_message(void) {
  SimpleMsarNotificationMessage sent;
  SimpleMsarNotificationMessage got;
  uint8_t wire[47];
  uint8_t again[47];

  any_simple_msar_notification_message(&sent);
  assert(encode_simple_msar_notification_message(&sent, wire, 0) == 47);
  assert(decode_simple_msar_notification_message(&got, wire, 0) == 47);
  equal_simple_msar_notification_message(&got, &sent);

  for (size_t i = 0; i < 47; i++) { wire[i] = arbitrary(); }
  assert(decode_simple_msar_notification_message(&got, wire, 0) == 47);
  assert(encode_simple_msar_notification_message(&got, again, 0) == 47);
  for (size_t i = 0; i < 47; i++) { assert(again[i] == wire[i]); }
}

/* ---- Complex Msar Leg Notification Message: 61 bytes ------------------------- */

/* Leg-level information on the execution/out of an MSAR for a complex instrument. Precedes the corresponding Complex MSAR Notification. Sequenced. */
typedef struct {
  uint8_t seconds[4];            /* bytes 0 to 3 */
  uint8_t nanoseconds[4];        /* bytes 4 to 7 */
  uint8_t badge[4];              /* bytes 8 to 11 */
  uint8_t instrument_id[4];      /* bytes 12 to 15 */
  uint8_t leg_id;                /* byte 16 */
  uint8_t leg_instrument_id[4];  /* bytes 17 to 20 */
  uint8_t notification_type;     /* byte 21 */
  uint8_t message_id[8];         /* bytes 22 to 29 */
  uint8_t auction_id[4];         /* bytes 30 to 33 */
  uint8_t price[4];              /* bytes 34 to 37 */
  uint8_t side;                  /* byte 38 */
  uint8_t leg_side;              /* byte 39 */
  uint8_t contracts[4];          /* bytes 40 to 43 */
  uint8_t liquidity_indicator;   /* byte 44 */
  uint8_t cross_id[4];           /* bytes 45 to 48 */
  uint8_t match_id[4];           /* bytes 49 to 52 */
  uint8_t price_6[8];            /* bytes 53 to 60 */
} ComplexMsarLegNotificationMessage;

/* any Complex Msar Leg Notification Message at all: every byte one the checker chooses */
static void any_complex_msar_leg_notification_message(ComplexMsarLegNotificationMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->seconds[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->badge[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->instrument_id[i] = arbitrary(); }
  record->leg_id = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->leg_instrument_id[i] = arbitrary(); }
  record->notification_type = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->message_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->auction_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->price[i] = arbitrary(); }
  record->side = arbitrary();
  record->leg_side = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->contracts[i] = arbitrary(); }
  record->liquidity_indicator = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->cross_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->match_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->price_6[i] = arbitrary(); }
}

/* Complex Msar Leg Notification Message to the wire: 61 bytes from at, returning where the next byte goes */
static size_t encode_complex_msar_leg_notification_message(const ComplexMsarLegNotificationMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->seconds[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->nanoseconds[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->badge[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument_id[i]; }
  wire[at++] = record->leg_id;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->leg_instrument_id[i]; }
  wire[at++] = record->notification_type;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->message_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->auction_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->price[i]; }
  wire[at++] = record->side;
  wire[at++] = record->leg_side;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->contracts[i]; }
  wire[at++] = record->liquidity_indicator;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->cross_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->match_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price_6[i]; }

  return at;
}

/* Complex Msar Leg Notification Message off the wire: 61 bytes from at, returning where the next byte lies */
static size_t decode_complex_msar_leg_notification_message(ComplexMsarLegNotificationMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->seconds[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->badge[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->instrument_id[i] = wire[at++]; }
  record->leg_id = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->leg_instrument_id[i] = wire[at++]; }
  record->notification_type = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->message_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->auction_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->price[i] = wire[at++]; }
  record->side = wire[at++];
  record->leg_side = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->contracts[i] = wire[at++]; }
  record->liquidity_indicator = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->cross_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->match_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->price_6[i] = wire[at++]; }

  return at;
}

/* what was read of Complex Msar Leg Notification Message is what was written, byte for byte */
static void equal_complex_msar_leg_notification_message(const ComplexMsarLegNotificationMessage *read, const ComplexMsarLegNotificationMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->seconds[i] == written->seconds[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->nanoseconds[i] == written->nanoseconds[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->badge[i] == written->badge[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->instrument_id[i] == written->instrument_id[i]); }
  assert(read->leg_id == written->leg_id);
  for (size_t i = 0; i < 4; i++) { assert(read->leg_instrument_id[i] == written->leg_instrument_id[i]); }
  assert(read->notification_type == written->notification_type);
  for (size_t i = 0; i < 8; i++) { assert(read->message_id[i] == written->message_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->auction_id[i] == written->auction_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->price[i] == written->price[i]); }
  assert(read->side == written->side);
  assert(read->leg_side == written->leg_side);
  for (size_t i = 0; i < 4; i++) { assert(read->contracts[i] == written->contracts[i]); }
  assert(read->liquidity_indicator == written->liquidity_indicator);
  for (size_t i = 0; i < 4; i++) { assert(read->cross_id[i] == written->cross_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->match_id[i] == written->match_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->price_6[i] == written->price_6[i]); }
}

/* Complex Msar Leg Notification Message: written and read back, then read and written back */
static void check_complex_msar_leg_notification_message(void) {
  ComplexMsarLegNotificationMessage sent;
  ComplexMsarLegNotificationMessage got;
  uint8_t wire[61];
  uint8_t again[61];

  any_complex_msar_leg_notification_message(&sent);
  assert(encode_complex_msar_leg_notification_message(&sent, wire, 0) == 61);
  assert(decode_complex_msar_leg_notification_message(&got, wire, 0) == 61);
  equal_complex_msar_leg_notification_message(&got, &sent);

  for (size_t i = 0; i < 61; i++) { wire[i] = arbitrary(); }
  assert(decode_complex_msar_leg_notification_message(&got, wire, 0) == 61);
  assert(encode_complex_msar_leg_notification_message(&got, again, 0) == 61);
  for (size_t i = 0; i < 61; i++) { assert(again[i] == wire[i]); }
}

/* ---- Complex Msar Notification Message: 55 bytes ----------------------------- */

/* Complex MSAR Execution Notification: the Complex MSAR Request has been executed or cancelled. Sequenced. */
typedef struct {
  uint8_t seconds[4];           /* bytes 0 to 3 */
  uint8_t nanoseconds[4];       /* bytes 4 to 7 */
  uint8_t badge[4];             /* bytes 8 to 11 */
  uint8_t instrument_id[4];     /* bytes 12 to 15 */
  uint8_t notification_type;    /* byte 16 */
  uint8_t message_id[8];        /* bytes 17 to 24 */
  uint8_t auction_id[4];        /* bytes 25 to 28 */
  uint8_t price[4];             /* bytes 29 to 32 */
  uint8_t side;                 /* byte 33 */
  uint8_t contracts[4];         /* bytes 34 to 37 */
  uint8_t liquidity_indicator;  /* byte 38 */
  uint8_t cross_id[4];          /* bytes 39 to 42 */
  uint8_t match_id[4];          /* bytes 43 to 46 */
  uint8_t price_6[8];           /* bytes 47 to 54 */
} ComplexMsarNotificationMessage;

/* any Complex Msar Notification Message at all: every byte one the checker chooses */
static void any_complex_msar_notification_message(ComplexMsarNotificationMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->seconds[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->badge[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->instrument_id[i] = arbitrary(); }
  record->notification_type = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->message_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->auction_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->price[i] = arbitrary(); }
  record->side = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->contracts[i] = arbitrary(); }
  record->liquidity_indicator = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->cross_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->match_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->price_6[i] = arbitrary(); }
}

/* Complex Msar Notification Message to the wire: 55 bytes from at, returning where the next byte goes */
static size_t encode_complex_msar_notification_message(const ComplexMsarNotificationMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->seconds[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->nanoseconds[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->badge[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument_id[i]; }
  wire[at++] = record->notification_type;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->message_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->auction_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->price[i]; }
  wire[at++] = record->side;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->contracts[i]; }
  wire[at++] = record->liquidity_indicator;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->cross_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->match_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price_6[i]; }

  return at;
}

/* Complex Msar Notification Message off the wire: 55 bytes from at, returning where the next byte lies */
static size_t decode_complex_msar_notification_message(ComplexMsarNotificationMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->seconds[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->badge[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->instrument_id[i] = wire[at++]; }
  record->notification_type = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->message_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->auction_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->price[i] = wire[at++]; }
  record->side = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->contracts[i] = wire[at++]; }
  record->liquidity_indicator = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->cross_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->match_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->price_6[i] = wire[at++]; }

  return at;
}

/* what was read of Complex Msar Notification Message is what was written, byte for byte */
static void equal_complex_msar_notification_message(const ComplexMsarNotificationMessage *read, const ComplexMsarNotificationMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->seconds[i] == written->seconds[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->nanoseconds[i] == written->nanoseconds[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->badge[i] == written->badge[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->instrument_id[i] == written->instrument_id[i]); }
  assert(read->notification_type == written->notification_type);
  for (size_t i = 0; i < 8; i++) { assert(read->message_id[i] == written->message_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->auction_id[i] == written->auction_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->price[i] == written->price[i]); }
  assert(read->side == written->side);
  for (size_t i = 0; i < 4; i++) { assert(read->contracts[i] == written->contracts[i]); }
  assert(read->liquidity_indicator == written->liquidity_indicator);
  for (size_t i = 0; i < 4; i++) { assert(read->cross_id[i] == written->cross_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->match_id[i] == written->match_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->price_6[i] == written->price_6[i]); }
}

/* Complex Msar Notification Message: written and read back, then read and written back */
static void check_complex_msar_notification_message(void) {
  ComplexMsarNotificationMessage sent;
  ComplexMsarNotificationMessage got;
  uint8_t wire[55];
  uint8_t again[55];

  any_complex_msar_notification_message(&sent);
  assert(encode_complex_msar_notification_message(&sent, wire, 0) == 55);
  assert(decode_complex_msar_notification_message(&got, wire, 0) == 55);
  equal_complex_msar_notification_message(&got, &sent);

  for (size_t i = 0; i < 55; i++) { wire[i] = arbitrary(); }
  assert(decode_complex_msar_notification_message(&got, wire, 0) == 55);
  assert(encode_complex_msar_notification_message(&got, again, 0) == 55);
  for (size_t i = 0; i < 55; i++) { assert(again[i] == wire[i]); }
}

/* ---- Opening Rotation Quote Spread Multiplier Notification Message: 22 bytes ---- */

/* Quote Spread Multiplier Message: sent once per underlying permitted on the port and whenever the effective multiplier changes intraday. Sequenced. */
typedef struct {
  uint8_t seconds[4];             /* bytes 0 to 3 */
  uint8_t nanoseconds[4];         /* bytes 4 to 7 */
  uint8_t underlying_symbol[13];  /* bytes 8 to 20 */
  uint8_t multiplier;             /* byte 21 */
} OpeningRotationQuoteSpreadMultiplierNotificationMessage;

/* any Opening Rotation Quote Spread Multiplier Notification Message at all: every byte one the checker chooses */
static void any_opening_rotation_quote_spread_multiplier_notification_message(OpeningRotationQuoteSpreadMultiplierNotificationMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->seconds[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = arbitrary(); }
  for (size_t i = 0; i < 13; i++) { record->underlying_symbol[i] = arbitrary(); }
  record->multiplier = arbitrary();
}

/* Opening Rotation Quote Spread Multiplier Notification Message to the wire: 22 bytes from at, returning where the next byte goes */
static size_t encode_opening_rotation_quote_spread_multiplier_notification_message(const OpeningRotationQuoteSpreadMultiplierNotificationMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->seconds[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->nanoseconds[i]; }
  for (size_t i = 0; i < 13; i++) { wire[at++] = record->underlying_symbol[i]; }
  wire[at++] = record->multiplier;

  return at;
}

/* Opening Rotation Quote Spread Multiplier Notification Message off the wire: 22 bytes from at, returning where the next byte lies */
static size_t decode_opening_rotation_quote_spread_multiplier_notification_message(OpeningRotationQuoteSpreadMultiplierNotificationMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->seconds[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = wire[at++]; }
  for (size_t i = 0; i < 13; i++) { record->underlying_symbol[i] = wire[at++]; }
  record->multiplier = wire[at++];

  return at;
}

/* what was read of Opening Rotation Quote Spread Multiplier Notification Message is what was written, byte for byte */
static void equal_opening_rotation_quote_spread_multiplier_notification_message(const OpeningRotationQuoteSpreadMultiplierNotificationMessage *read, const OpeningRotationQuoteSpreadMultiplierNotificationMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->seconds[i] == written->seconds[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->nanoseconds[i] == written->nanoseconds[i]); }
  for (size_t i = 0; i < 13; i++) { assert(read->underlying_symbol[i] == written->underlying_symbol[i]); }
  assert(read->multiplier == written->multiplier);
}

/* Opening Rotation Quote Spread Multiplier Notification Message: written and read back, then read and written back */
static void check_opening_rotation_quote_spread_multiplier_notification_message(void) {
  OpeningRotationQuoteSpreadMultiplierNotificationMessage sent;
  OpeningRotationQuoteSpreadMultiplierNotificationMessage got;
  uint8_t wire[22];
  uint8_t again[22];

  any_opening_rotation_quote_spread_multiplier_notification_message(&sent);
  assert(encode_opening_rotation_quote_spread_multiplier_notification_message(&sent, wire, 0) == 22);
  assert(decode_opening_rotation_quote_spread_multiplier_notification_message(&got, wire, 0) == 22);
  equal_opening_rotation_quote_spread_multiplier_notification_message(&got, &sent);

  for (size_t i = 0; i < 22; i++) { wire[i] = arbitrary(); }
  assert(decode_opening_rotation_quote_spread_multiplier_notification_message(&got, wire, 0) == 22);
  assert(encode_opening_rotation_quote_spread_multiplier_notification_message(&got, again, 0) == 22);
  for (size_t i = 0; i < 22; i++) { assert(again[i] == wire[i]); }
}

/* ---- Notification Subscription Reply Message: 13 bytes ----------------------- */

/* Reply to a Notification Subscription Request. Unsequenced. */
typedef struct {
  uint8_t badge[4];       /* bytes 0 to 3 */
  uint8_t message_id[8];  /* bytes 4 to 11 */
  uint8_t status_code;    /* byte 12 */
} NotificationSubscriptionReplyMessage;

/* any Notification Subscription Reply Message at all: every byte one the checker chooses */
static void any_notification_subscription_reply_message(NotificationSubscriptionReplyMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->badge[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->message_id[i] = arbitrary(); }
  record->status_code = arbitrary();
}

/* Notification Subscription Reply Message to the wire: 13 bytes from at, returning where the next byte goes */
static size_t encode_notification_subscription_reply_message(const NotificationSubscriptionReplyMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->badge[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->message_id[i]; }
  wire[at++] = record->status_code;

  return at;
}

/* Notification Subscription Reply Message off the wire: 13 bytes from at, returning where the next byte lies */
static size_t decode_notification_subscription_reply_message(NotificationSubscriptionReplyMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->badge[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->message_id[i] = wire[at++]; }
  record->status_code = wire[at++];

  return at;
}

/* what was read of Notification Subscription Reply Message is what was written, byte for byte */
static void equal_notification_subscription_reply_message(const NotificationSubscriptionReplyMessage *read, const NotificationSubscriptionReplyMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->badge[i] == written->badge[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->message_id[i] == written->message_id[i]); }
  assert(read->status_code == written->status_code);
}

/* Notification Subscription Reply Message: written and read back, then read and written back */
static void check_notification_subscription_reply_message(void) {
  NotificationSubscriptionReplyMessage sent;
  NotificationSubscriptionReplyMessage got;
  uint8_t wire[13];
  uint8_t again[13];

  any_notification_subscription_reply_message(&sent);
  assert(encode_notification_subscription_reply_message(&sent, wire, 0) == 13);
  assert(decode_notification_subscription_reply_message(&got, wire, 0) == 13);
  equal_notification_subscription_reply_message(&got, &sent);

  for (size_t i = 0; i < 13; i++) { wire[i] = arbitrary(); }
  assert(decode_notification_subscription_reply_message(&got, wire, 0) == 13);
  assert(encode_notification_subscription_reply_message(&got, again, 0) == 13);
  for (size_t i = 0; i < 13; i++) { assert(again[i] == wire[i]); }
}

/* ---- Add Complex Instrument Reply Message: 13 bytes -------------------------- */

/* Response to the Add Complex Instrument Request (AC) indicating the validity of the request. Unsequenced. */
typedef struct {
  uint8_t badge[4];       /* bytes 0 to 3 */
  uint8_t message_id[8];  /* bytes 4 to 11 */
  uint8_t status_code;    /* byte 12 */
} AddComplexInstrumentReplyMessage;

/* any Add Complex Instrument Reply Message at all: every byte one the checker chooses */
static void any_add_complex_instrument_reply_message(AddComplexInstrumentReplyMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->badge[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->message_id[i] = arbitrary(); }
  record->status_code = arbitrary();
}

/* Add Complex Instrument Reply Message to the wire: 13 bytes from at, returning where the next byte goes */
static size_t encode_add_complex_instrument_reply_message(const AddComplexInstrumentReplyMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->badge[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->message_id[i]; }
  wire[at++] = record->status_code;

  return at;
}

/* Add Complex Instrument Reply Message off the wire: 13 bytes from at, returning where the next byte lies */
static size_t decode_add_complex_instrument_reply_message(AddComplexInstrumentReplyMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->badge[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->message_id[i] = wire[at++]; }
  record->status_code = wire[at++];

  return at;
}

/* what was read of Add Complex Instrument Reply Message is what was written, byte for byte */
static void equal_add_complex_instrument_reply_message(const AddComplexInstrumentReplyMessage *read, const AddComplexInstrumentReplyMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->badge[i] == written->badge[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->message_id[i] == written->message_id[i]); }
  assert(read->status_code == written->status_code);
}

/* Add Complex Instrument Reply Message: written and read back, then read and written back */
static void check_add_complex_instrument_reply_message(void) {
  AddComplexInstrumentReplyMessage sent;
  AddComplexInstrumentReplyMessage got;
  uint8_t wire[13];
  uint8_t again[13];

  any_add_complex_instrument_reply_message(&sent);
  assert(encode_add_complex_instrument_reply_message(&sent, wire, 0) == 13);
  assert(decode_add_complex_instrument_reply_message(&got, wire, 0) == 13);
  equal_add_complex_instrument_reply_message(&got, &sent);

  for (size_t i = 0; i < 13; i++) { wire[i] = arbitrary(); }
  assert(decode_add_complex_instrument_reply_message(&got, wire, 0) == 13);
  assert(encode_add_complex_instrument_reply_message(&got, again, 0) == 13);
  for (size_t i = 0; i < 13; i++) { assert(again[i] == wire[i]); }
}

/* ---- Mm Parameter Definition Reply Message: 13 bytes ------------------------- */

/* Response to the MM Parameter Definition Request (AE) indicating the validity of the request. Unsequenced. */
typedef struct {
  uint8_t badge[4];       /* bytes 0 to 3 */
  uint8_t message_id[8];  /* bytes 4 to 11 */
  uint8_t status_code;    /* byte 12 */
} MmParameterDefinitionReplyMessage;

/* any Mm Parameter Definition Reply Message at all: every byte one the checker chooses */
static void any_mm_parameter_definition_reply_message(MmParameterDefinitionReplyMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->badge[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->message_id[i] = arbitrary(); }
  record->status_code = arbitrary();
}

/* Mm Parameter Definition Reply Message to the wire: 13 bytes from at, returning where the next byte goes */
static size_t encode_mm_parameter_definition_reply_message(const MmParameterDefinitionReplyMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->badge[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->message_id[i]; }
  wire[at++] = record->status_code;

  return at;
}

/* Mm Parameter Definition Reply Message off the wire: 13 bytes from at, returning where the next byte lies */
static size_t decode_mm_parameter_definition_reply_message(MmParameterDefinitionReplyMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->badge[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->message_id[i] = wire[at++]; }
  record->status_code = wire[at++];

  return at;
}

/* what was read of Mm Parameter Definition Reply Message is what was written, byte for byte */
static void equal_mm_parameter_definition_reply_message(const MmParameterDefinitionReplyMessage *read, const MmParameterDefinitionReplyMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->badge[i] == written->badge[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->message_id[i] == written->message_id[i]); }
  assert(read->status_code == written->status_code);
}

/* Mm Parameter Definition Reply Message: written and read back, then read and written back */
static void check_mm_parameter_definition_reply_message(void) {
  MmParameterDefinitionReplyMessage sent;
  MmParameterDefinitionReplyMessage got;
  uint8_t wire[13];
  uint8_t again[13];

  any_mm_parameter_definition_reply_message(&sent);
  assert(encode_mm_parameter_definition_reply_message(&sent, wire, 0) == 13);
  assert(decode_mm_parameter_definition_reply_message(&got, wire, 0) == 13);
  equal_mm_parameter_definition_reply_message(&got, &sent);

  for (size_t i = 0; i < 13; i++) { wire[i] = arbitrary(); }
  assert(decode_mm_parameter_definition_reply_message(&got, wire, 0) == 13);
  assert(encode_mm_parameter_definition_reply_message(&got, again, 0) == 13);
  for (size_t i = 0; i < 13; i++) { assert(again[i] == wire[i]); }
}

/* ---- Active Qp Self Replenishment Set Limit Reply Message: 30 bytes ---------- */

/* Acknowledgement message for Set Limit Message. Unsequenced. */
typedef struct {
  uint8_t badge[4];               /* bytes 0 to 3 */
  uint8_t message_id[8];          /* bytes 4 to 11 */
  uint8_t underlying_symbol[13];  /* bytes 12 to 24 */
  uint8_t set_value[4];           /* bytes 25 to 28 */
  uint8_t status_code;            /* byte 29 */
} ActiveQpSelfReplenishmentSetLimitReplyMessage;

/* any Active Qp Self Replenishment Set Limit Reply Message at all: every byte one the checker chooses */
static void any_active_qp_self_replenishment_set_limit_reply_message(ActiveQpSelfReplenishmentSetLimitReplyMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->badge[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->message_id[i] = arbitrary(); }
  for (size_t i = 0; i < 13; i++) { record->underlying_symbol[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->set_value[i] = arbitrary(); }
  record->status_code = arbitrary();
}

/* Active Qp Self Replenishment Set Limit Reply Message to the wire: 30 bytes from at, returning where the next byte goes */
static size_t encode_active_qp_self_replenishment_set_limit_reply_message(const ActiveQpSelfReplenishmentSetLimitReplyMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->badge[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->message_id[i]; }
  for (size_t i = 0; i < 13; i++) { wire[at++] = record->underlying_symbol[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->set_value[i]; }
  wire[at++] = record->status_code;

  return at;
}

/* Active Qp Self Replenishment Set Limit Reply Message off the wire: 30 bytes from at, returning where the next byte lies */
static size_t decode_active_qp_self_replenishment_set_limit_reply_message(ActiveQpSelfReplenishmentSetLimitReplyMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->badge[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->message_id[i] = wire[at++]; }
  for (size_t i = 0; i < 13; i++) { record->underlying_symbol[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->set_value[i] = wire[at++]; }
  record->status_code = wire[at++];

  return at;
}

/* what was read of Active Qp Self Replenishment Set Limit Reply Message is what was written, byte for byte */
static void equal_active_qp_self_replenishment_set_limit_reply_message(const ActiveQpSelfReplenishmentSetLimitReplyMessage *read, const ActiveQpSelfReplenishmentSetLimitReplyMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->badge[i] == written->badge[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->message_id[i] == written->message_id[i]); }
  for (size_t i = 0; i < 13; i++) { assert(read->underlying_symbol[i] == written->underlying_symbol[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->set_value[i] == written->set_value[i]); }
  assert(read->status_code == written->status_code);
}

/* Active Qp Self Replenishment Set Limit Reply Message: written and read back, then read and written back */
static void check_active_qp_self_replenishment_set_limit_reply_message(void) {
  ActiveQpSelfReplenishmentSetLimitReplyMessage sent;
  ActiveQpSelfReplenishmentSetLimitReplyMessage got;
  uint8_t wire[30];
  uint8_t again[30];

  any_active_qp_self_replenishment_set_limit_reply_message(&sent);
  assert(encode_active_qp_self_replenishment_set_limit_reply_message(&sent, wire, 0) == 30);
  assert(decode_active_qp_self_replenishment_set_limit_reply_message(&got, wire, 0) == 30);
  equal_active_qp_self_replenishment_set_limit_reply_message(&got, &sent);

  for (size_t i = 0; i < 30; i++) { wire[i] = arbitrary(); }
  assert(decode_active_qp_self_replenishment_set_limit_reply_message(&got, wire, 0) == 30);
  assert(encode_active_qp_self_replenishment_set_limit_reply_message(&got, again, 0) == 30);
  for (size_t i = 0; i < 30; i++) { assert(again[i] == wire[i]); }
}

/* ---- Rapid Fire Config Reply Message: 5 bytes -------------------------------- */

/* Rapid-Fire Config Reply Message. Unsequenced. */
typedef struct {
  uint8_t badge[4];     /* bytes 0 to 3 */
  uint8_t status_code;  /* byte 4 */
} RapidFireConfigReplyMessage;

/* any Rapid Fire Config Reply Message at all: every byte one the checker chooses */
static void any_rapid_fire_config_reply_message(RapidFireConfigReplyMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->badge[i] = arbitrary(); }
  record->status_code = arbitrary();
}

/* Rapid Fire Config Reply Message to the wire: 5 bytes from at, returning where the next byte goes */
static size_t encode_rapid_fire_config_reply_message(const RapidFireConfigReplyMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->badge[i]; }
  wire[at++] = record->status_code;

  return at;
}

/* Rapid Fire Config Reply Message off the wire: 5 bytes from at, returning where the next byte lies */
static size_t decode_rapid_fire_config_reply_message(RapidFireConfigReplyMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->badge[i] = wire[at++]; }
  record->status_code = wire[at++];

  return at;
}

/* what was read of Rapid Fire Config Reply Message is what was written, byte for byte */
static void equal_rapid_fire_config_reply_message(const RapidFireConfigReplyMessage *read, const RapidFireConfigReplyMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->badge[i] == written->badge[i]); }
  assert(read->status_code == written->status_code);
}

/* Rapid Fire Config Reply Message: written and read back, then read and written back */
static void check_rapid_fire_config_reply_message(void) {
  RapidFireConfigReplyMessage sent;
  RapidFireConfigReplyMessage got;
  uint8_t wire[5];
  uint8_t again[5];

  any_rapid_fire_config_reply_message(&sent);
  assert(encode_rapid_fire_config_reply_message(&sent, wire, 0) == 5);
  assert(decode_rapid_fire_config_reply_message(&got, wire, 0) == 5);
  equal_rapid_fire_config_reply_message(&got, &sent);

  for (size_t i = 0; i < 5; i++) { wire[i] = arbitrary(); }
  assert(decode_rapid_fire_config_reply_message(&got, wire, 0) == 5);
  assert(encode_rapid_fire_config_reply_message(&got, again, 0) == 5);
  for (size_t i = 0; i < 5; i++) { assert(again[i] == wire[i]); }
}

/* ---- Underlying Purge Reply Message: 29 bytes -------------------------------- */

/* Underlying Purge Reply Message including SentTimestamp. Unsequenced. */
typedef struct {
  uint8_t badge[4];           /* bytes 0 to 3 */
  uint8_t message_id[8];      /* bytes 4 to 11 */
  uint8_t sent_timestamp[8];  /* bytes 12 to 19 */
  uint8_t status_code;        /* byte 20 */
  uint8_t sequence[8];        /* bytes 21 to 28 */
} UnderlyingPurgeReplyMessage;

/* any Underlying Purge Reply Message at all: every byte one the checker chooses */
static void any_underlying_purge_reply_message(UnderlyingPurgeReplyMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->badge[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->message_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->sent_timestamp[i] = arbitrary(); }
  record->status_code = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->sequence[i] = arbitrary(); }
}

/* Underlying Purge Reply Message to the wire: 29 bytes from at, returning where the next byte goes */
static size_t encode_underlying_purge_reply_message(const UnderlyingPurgeReplyMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->badge[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->message_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->sent_timestamp[i]; }
  wire[at++] = record->status_code;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->sequence[i]; }

  return at;
}

/* Underlying Purge Reply Message off the wire: 29 bytes from at, returning where the next byte lies */
static size_t decode_underlying_purge_reply_message(UnderlyingPurgeReplyMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->badge[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->message_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->sent_timestamp[i] = wire[at++]; }
  record->status_code = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->sequence[i] = wire[at++]; }

  return at;
}

/* what was read of Underlying Purge Reply Message is what was written, byte for byte */
static void equal_underlying_purge_reply_message(const UnderlyingPurgeReplyMessage *read, const UnderlyingPurgeReplyMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->badge[i] == written->badge[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->message_id[i] == written->message_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->sent_timestamp[i] == written->sent_timestamp[i]); }
  assert(read->status_code == written->status_code);
  for (size_t i = 0; i < 8; i++) { assert(read->sequence[i] == written->sequence[i]); }
}

/* Underlying Purge Reply Message: written and read back, then read and written back */
static void check_underlying_purge_reply_message(void) {
  UnderlyingPurgeReplyMessage sent;
  UnderlyingPurgeReplyMessage got;
  uint8_t wire[29];
  uint8_t again[29];

  any_underlying_purge_reply_message(&sent);
  assert(encode_underlying_purge_reply_message(&sent, wire, 0) == 29);
  assert(decode_underlying_purge_reply_message(&got, wire, 0) == 29);
  equal_underlying_purge_reply_message(&got, &sent);

  for (size_t i = 0; i < 29; i++) { wire[i] = arbitrary(); }
  assert(decode_underlying_purge_reply_message(&got, wire, 0) == 29);
  assert(encode_underlying_purge_reply_message(&got, again, 0) == 29);
  for (size_t i = 0; i < 29; i++) { assert(again[i] == wire[i]); }
}

/* ---- Market Reentry Reply Message: 21 bytes ---------------------------------- */

/* Market Reentry Reply Message. Unsequenced. */
typedef struct {
  uint8_t badge[4];       /* bytes 0 to 3 */
  uint8_t message_id[8];  /* bytes 4 to 11 */
  uint8_t status_code;    /* byte 12 */
  uint8_t reserved_8[8];  /* bytes 13 to 20 */
} MarketReentryReplyMessage;

/* any Market Reentry Reply Message at all: every byte one the checker chooses */
static void any_market_reentry_reply_message(MarketReentryReplyMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->badge[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->message_id[i] = arbitrary(); }
  record->status_code = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->reserved_8[i] = arbitrary(); }
}

/* Market Reentry Reply Message to the wire: 21 bytes from at, returning where the next byte goes */
static size_t encode_market_reentry_reply_message(const MarketReentryReplyMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->badge[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->message_id[i]; }
  wire[at++] = record->status_code;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->reserved_8[i]; }

  return at;
}

/* Market Reentry Reply Message off the wire: 21 bytes from at, returning where the next byte lies */
static size_t decode_market_reentry_reply_message(MarketReentryReplyMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->badge[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->message_id[i] = wire[at++]; }
  record->status_code = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->reserved_8[i] = wire[at++]; }

  return at;
}

/* what was read of Market Reentry Reply Message is what was written, byte for byte */
static void equal_market_reentry_reply_message(const MarketReentryReplyMessage *read, const MarketReentryReplyMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->badge[i] == written->badge[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->message_id[i] == written->message_id[i]); }
  assert(read->status_code == written->status_code);
  for (size_t i = 0; i < 8; i++) { assert(read->reserved_8[i] == written->reserved_8[i]); }
}

/* Market Reentry Reply Message: written and read back, then read and written back */
static void check_market_reentry_reply_message(void) {
  MarketReentryReplyMessage sent;
  MarketReentryReplyMessage got;
  uint8_t wire[21];
  uint8_t again[21];

  any_market_reentry_reply_message(&sent);
  assert(encode_market_reentry_reply_message(&sent, wire, 0) == 21);
  assert(decode_market_reentry_reply_message(&got, wire, 0) == 21);
  equal_market_reentry_reply_message(&got, &sent);

  for (size_t i = 0; i < 21; i++) { wire[i] = arbitrary(); }
  assert(decode_market_reentry_reply_message(&got, wire, 0) == 21);
  assert(encode_market_reentry_reply_message(&got, again, 0) == 21);
  for (size_t i = 0; i < 21; i++) { assert(again[i] == wire[i]); }
}

/* ---- Active Qp Self Replenishment Request Reentry Reply Message: 38 bytes ---- */

/* Acknowledgement for the ActiveQP Request/Reentry Message. Unsequenced. */
typedef struct {
  uint8_t badge[4];                          /* bytes 0 to 3 */
  uint8_t message_id[8];                     /* bytes 4 to 11 */
  uint8_t underlying_symbol[13];             /* bytes 12 to 24 */
  uint8_t status_code;                       /* byte 25 */
  uint8_t requested_replenishment_value[4];  /* bytes 26 to 29 */
  uint8_t active_counter_value[4];           /* bytes 30 to 33 */
  uint8_t set_contract_limit[4];             /* bytes 34 to 37 */
} ActiveQpSelfReplenishmentRequestReentryReplyMessage;

/* any Active Qp Self Replenishment Request Reentry Reply Message at all: every byte one the checker chooses */
static void any_active_qp_self_replenishment_request_reentry_reply_message(ActiveQpSelfReplenishmentRequestReentryReplyMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->badge[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->message_id[i] = arbitrary(); }
  for (size_t i = 0; i < 13; i++) { record->underlying_symbol[i] = arbitrary(); }
  record->status_code = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->requested_replenishment_value[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->active_counter_value[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->set_contract_limit[i] = arbitrary(); }
}

/* Active Qp Self Replenishment Request Reentry Reply Message to the wire: 38 bytes from at, returning where the next byte goes */
static size_t encode_active_qp_self_replenishment_request_reentry_reply_message(const ActiveQpSelfReplenishmentRequestReentryReplyMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->badge[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->message_id[i]; }
  for (size_t i = 0; i < 13; i++) { wire[at++] = record->underlying_symbol[i]; }
  wire[at++] = record->status_code;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->requested_replenishment_value[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->active_counter_value[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->set_contract_limit[i]; }

  return at;
}

/* Active Qp Self Replenishment Request Reentry Reply Message off the wire: 38 bytes from at, returning where the next byte lies */
static size_t decode_active_qp_self_replenishment_request_reentry_reply_message(ActiveQpSelfReplenishmentRequestReentryReplyMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->badge[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->message_id[i] = wire[at++]; }
  for (size_t i = 0; i < 13; i++) { record->underlying_symbol[i] = wire[at++]; }
  record->status_code = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->requested_replenishment_value[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->active_counter_value[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->set_contract_limit[i] = wire[at++]; }

  return at;
}

/* what was read of Active Qp Self Replenishment Request Reentry Reply Message is what was written, byte for byte */
static void equal_active_qp_self_replenishment_request_reentry_reply_message(const ActiveQpSelfReplenishmentRequestReentryReplyMessage *read, const ActiveQpSelfReplenishmentRequestReentryReplyMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->badge[i] == written->badge[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->message_id[i] == written->message_id[i]); }
  for (size_t i = 0; i < 13; i++) { assert(read->underlying_symbol[i] == written->underlying_symbol[i]); }
  assert(read->status_code == written->status_code);
  for (size_t i = 0; i < 4; i++) { assert(read->requested_replenishment_value[i] == written->requested_replenishment_value[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->active_counter_value[i] == written->active_counter_value[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->set_contract_limit[i] == written->set_contract_limit[i]); }
}

/* Active Qp Self Replenishment Request Reentry Reply Message: written and read back, then read and written back */
static void check_active_qp_self_replenishment_request_reentry_reply_message(void) {
  ActiveQpSelfReplenishmentRequestReentryReplyMessage sent;
  ActiveQpSelfReplenishmentRequestReentryReplyMessage got;
  uint8_t wire[38];
  uint8_t again[38];

  any_active_qp_self_replenishment_request_reentry_reply_message(&sent);
  assert(encode_active_qp_self_replenishment_request_reentry_reply_message(&sent, wire, 0) == 38);
  assert(decode_active_qp_self_replenishment_request_reentry_reply_message(&got, wire, 0) == 38);
  equal_active_qp_self_replenishment_request_reentry_reply_message(&got, &sent);

  for (size_t i = 0; i < 38; i++) { wire[i] = arbitrary(); }
  assert(decode_active_qp_self_replenishment_request_reentry_reply_message(&got, wire, 0) == 38);
  assert(encode_active_qp_self_replenishment_request_reentry_reply_message(&got, again, 0) == 38);
  for (size_t i = 0; i < 38; i++) { assert(again[i] == wire[i]); }
}

/* ---- Instrument Purge Notification Message: 49 bytes ------------------------- */

/* Informs the firm that its quotes for a given simple or complex instrument have been purged. Unsequenced. */
typedef struct {
  uint8_t seconds[4];        /* bytes 0 to 3 */
  uint8_t nanoseconds[4];    /* bytes 4 to 7 */
  uint8_t badge[4];          /* bytes 8 to 11 */
  uint8_t message_id[8];     /* bytes 12 to 19 */
  uint8_t instrument_id[4];  /* bytes 20 to 23 */
  uint8_t purge_reason;      /* byte 24 */
  uint8_t sequence[8];       /* bytes 25 to 32 */
  uint8_t reserved_16[16];   /* bytes 33 to 48 */
} InstrumentPurgeNotificationMessage;

/* any Instrument Purge Notification Message at all: every byte one the checker chooses */
static void any_instrument_purge_notification_message(InstrumentPurgeNotificationMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->seconds[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->badge[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->message_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->instrument_id[i] = arbitrary(); }
  record->purge_reason = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->sequence[i] = arbitrary(); }
  for (size_t i = 0; i < 16; i++) { record->reserved_16[i] = arbitrary(); }
}

/* Instrument Purge Notification Message to the wire: 49 bytes from at, returning where the next byte goes */
static size_t encode_instrument_purge_notification_message(const InstrumentPurgeNotificationMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->seconds[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->nanoseconds[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->badge[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->message_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument_id[i]; }
  wire[at++] = record->purge_reason;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->sequence[i]; }
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->reserved_16[i]; }

  return at;
}

/* Instrument Purge Notification Message off the wire: 49 bytes from at, returning where the next byte lies */
static size_t decode_instrument_purge_notification_message(InstrumentPurgeNotificationMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->seconds[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->badge[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->message_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->instrument_id[i] = wire[at++]; }
  record->purge_reason = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->sequence[i] = wire[at++]; }
  for (size_t i = 0; i < 16; i++) { record->reserved_16[i] = wire[at++]; }

  return at;
}

/* what was read of Instrument Purge Notification Message is what was written, byte for byte */
static void equal_instrument_purge_notification_message(const InstrumentPurgeNotificationMessage *read, const InstrumentPurgeNotificationMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->seconds[i] == written->seconds[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->nanoseconds[i] == written->nanoseconds[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->badge[i] == written->badge[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->message_id[i] == written->message_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->instrument_id[i] == written->instrument_id[i]); }
  assert(read->purge_reason == written->purge_reason);
  for (size_t i = 0; i < 8; i++) { assert(read->sequence[i] == written->sequence[i]); }
  for (size_t i = 0; i < 16; i++) { assert(read->reserved_16[i] == written->reserved_16[i]); }
}

/* Instrument Purge Notification Message: written and read back, then read and written back */
static void check_instrument_purge_notification_message(void) {
  InstrumentPurgeNotificationMessage sent;
  InstrumentPurgeNotificationMessage got;
  uint8_t wire[49];
  uint8_t again[49];

  any_instrument_purge_notification_message(&sent);
  assert(encode_instrument_purge_notification_message(&sent, wire, 0) == 49);
  assert(decode_instrument_purge_notification_message(&got, wire, 0) == 49);
  equal_instrument_purge_notification_message(&got, &sent);

  for (size_t i = 0; i < 49; i++) { wire[i] = arbitrary(); }
  assert(decode_instrument_purge_notification_message(&got, wire, 0) == 49);
  assert(encode_instrument_purge_notification_message(&got, again, 0) == 49);
  for (size_t i = 0; i < 49; i++) { assert(again[i] == wire[i]); }
}

/* ---- Underlying Purge Notification Message: 42 bytes ------------------------- */

/* Informs the firm that all the quotes for instruments associated with the given underlying have been purged (user request, Rapid Fire/ActiveQP risk protection or Kill-Switch). Unsequenced. */
typedef struct {
  uint8_t seconds[4];      /* bytes 0 to 3 */
  uint8_t nanoseconds[4];  /* bytes 4 to 7 */
  uint8_t badge[4];        /* bytes 8 to 11 */
  uint8_t underlying[13];  /* bytes 12 to 24 */
  uint8_t purge_reason;    /* byte 25 */
  uint8_t message_id[8];   /* bytes 26 to 33 */
  uint8_t sequence[8];     /* bytes 34 to 41 */
} UnderlyingPurgeNotificationMessage;

/* any Underlying Purge Notification Message at all: every byte one the checker chooses */
static void any_underlying_purge_notification_message(UnderlyingPurgeNotificationMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->seconds[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->badge[i] = arbitrary(); }
  for (size_t i = 0; i < 13; i++) { record->underlying[i] = arbitrary(); }
  record->purge_reason = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->message_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->sequence[i] = arbitrary(); }
}

/* Underlying Purge Notification Message to the wire: 42 bytes from at, returning where the next byte goes */
static size_t encode_underlying_purge_notification_message(const UnderlyingPurgeNotificationMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->seconds[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->nanoseconds[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->badge[i]; }
  for (size_t i = 0; i < 13; i++) { wire[at++] = record->underlying[i]; }
  wire[at++] = record->purge_reason;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->message_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->sequence[i]; }

  return at;
}

/* Underlying Purge Notification Message off the wire: 42 bytes from at, returning where the next byte lies */
static size_t decode_underlying_purge_notification_message(UnderlyingPurgeNotificationMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->seconds[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->badge[i] = wire[at++]; }
  for (size_t i = 0; i < 13; i++) { record->underlying[i] = wire[at++]; }
  record->purge_reason = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->message_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->sequence[i] = wire[at++]; }

  return at;
}

/* what was read of Underlying Purge Notification Message is what was written, byte for byte */
static void equal_underlying_purge_notification_message(const UnderlyingPurgeNotificationMessage *read, const UnderlyingPurgeNotificationMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->seconds[i] == written->seconds[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->nanoseconds[i] == written->nanoseconds[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->badge[i] == written->badge[i]); }
  for (size_t i = 0; i < 13; i++) { assert(read->underlying[i] == written->underlying[i]); }
  assert(read->purge_reason == written->purge_reason);
  for (size_t i = 0; i < 8; i++) { assert(read->message_id[i] == written->message_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->sequence[i] == written->sequence[i]); }
}

/* Underlying Purge Notification Message: written and read back, then read and written back */
static void check_underlying_purge_notification_message(void) {
  UnderlyingPurgeNotificationMessage sent;
  UnderlyingPurgeNotificationMessage got;
  uint8_t wire[42];
  uint8_t again[42];

  any_underlying_purge_notification_message(&sent);
  assert(encode_underlying_purge_notification_message(&sent, wire, 0) == 42);
  assert(decode_underlying_purge_notification_message(&got, wire, 0) == 42);
  equal_underlying_purge_notification_message(&got, &sent);

  for (size_t i = 0; i < 42; i++) { wire[i] = arbitrary(); }
  assert(decode_underlying_purge_notification_message(&got, wire, 0) == 42);
  assert(encode_underlying_purge_notification_message(&got, again, 0) == 42);
  for (size_t i = 0; i < 42; i++) { assert(again[i] == wire[i]); }
}

/* ---- Market Reentry Notification Message: 42 bytes --------------------------- */

/* Informs that risk protection triggered by rapid fire/purge has been reset for the specified scope. Unsequenced. */
typedef struct {
  uint8_t seconds[4];             /* bytes 0 to 3 */
  uint8_t nanoseconds[4];         /* bytes 4 to 7 */
  uint8_t badge[4];               /* bytes 8 to 11 */
  uint8_t underlying_symbol[13];  /* bytes 12 to 24 */
  uint8_t reentry_scope;          /* byte 25 */
  uint8_t message_id[8];          /* bytes 26 to 33 */
  uint8_t reserved_8[8];          /* bytes 34 to 41 */
} MarketReentryNotificationMessage;

/* any Market Reentry Notification Message at all: every byte one the checker chooses */
static void any_market_reentry_notification_message(MarketReentryNotificationMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->seconds[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->badge[i] = arbitrary(); }
  for (size_t i = 0; i < 13; i++) { record->underlying_symbol[i] = arbitrary(); }
  record->reentry_scope = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->message_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->reserved_8[i] = arbitrary(); }
}

/* Market Reentry Notification Message to the wire: 42 bytes from at, returning where the next byte goes */
static size_t encode_market_reentry_notification_message(const MarketReentryNotificationMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->seconds[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->nanoseconds[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->badge[i]; }
  for (size_t i = 0; i < 13; i++) { wire[at++] = record->underlying_symbol[i]; }
  wire[at++] = record->reentry_scope;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->message_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->reserved_8[i]; }

  return at;
}

/* Market Reentry Notification Message off the wire: 42 bytes from at, returning where the next byte lies */
static size_t decode_market_reentry_notification_message(MarketReentryNotificationMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->seconds[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->badge[i] = wire[at++]; }
  for (size_t i = 0; i < 13; i++) { record->underlying_symbol[i] = wire[at++]; }
  record->reentry_scope = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->message_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->reserved_8[i] = wire[at++]; }

  return at;
}

/* what was read of Market Reentry Notification Message is what was written, byte for byte */
static void equal_market_reentry_notification_message(const MarketReentryNotificationMessage *read, const MarketReentryNotificationMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->seconds[i] == written->seconds[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->nanoseconds[i] == written->nanoseconds[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->badge[i] == written->badge[i]); }
  for (size_t i = 0; i < 13; i++) { assert(read->underlying_symbol[i] == written->underlying_symbol[i]); }
  assert(read->reentry_scope == written->reentry_scope);
  for (size_t i = 0; i < 8; i++) { assert(read->message_id[i] == written->message_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->reserved_8[i] == written->reserved_8[i]); }
}

/* Market Reentry Notification Message: written and read back, then read and written back */
static void check_market_reentry_notification_message(void) {
  MarketReentryNotificationMessage sent;
  MarketReentryNotificationMessage got;
  uint8_t wire[42];
  uint8_t again[42];

  any_market_reentry_notification_message(&sent);
  assert(encode_market_reentry_notification_message(&sent, wire, 0) == 42);
  assert(decode_market_reentry_notification_message(&got, wire, 0) == 42);
  equal_market_reentry_notification_message(&got, &sent);

  for (size_t i = 0; i < 42; i++) { wire[i] = arbitrary(); }
  assert(decode_market_reentry_notification_message(&got, wire, 0) == 42);
  assert(encode_market_reentry_notification_message(&got, again, 0) == 42);
  for (size_t i = 0; i < 42; i++) { assert(again[i] == wire[i]); }
}

/* ---- What esbmc checks ------------------------------------------------------- */

/* every record of the protocol, each on its own buffers */
static void checks(void) {
  check_server_packet_header();
  check_login_accepted_packet();
  check_login_rejected_packet();
  check_msar_accept_message();
  check_msar_reject_message();
  check_complex_msar_accept_message();
  check_complex_msar_reject_message();
  check_underlying_permission_notification_message();
  check_mm_parameter_definition_notification_message();
  check_rapid_fire_config_notification_message();
  check_active_qp_self_replenishment_parameter_definition_notification_message();
  check_system_event_message();
  check_simple_instrument_directory_message();
  check_simple_instrument_trading_action_message();
  check_complex_instrument_trading_action_message();
  check_simple_quote_execution_notification_message();
  check_complex_quote_execution_notification_message();
  check_complex_quote_leg_execution_notification_message();
  check_simple_msar_notification_message();
  check_complex_msar_leg_notification_message();
  check_complex_msar_notification_message();
  check_opening_rotation_quote_spread_multiplier_notification_message();
  check_notification_subscription_reply_message();
  check_add_complex_instrument_reply_message();
  check_mm_parameter_definition_reply_message();
  check_active_qp_self_replenishment_set_limit_reply_message();
  check_rapid_fire_config_reply_message();
  check_underlying_purge_reply_message();
  check_market_reentry_reply_message();
  check_active_qp_self_replenishment_request_reentry_reply_message();
  check_instrument_purge_notification_message();
  check_underlying_purge_notification_message();
  check_market_reentry_notification_message();
}

int main(void) {
#ifdef CONCRETE
  for (pattern = 0; pattern < 4; pattern++) { checks(); }
#else
  checks();
#endif

  return 0;
}
