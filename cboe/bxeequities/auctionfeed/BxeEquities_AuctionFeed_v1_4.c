// cboe/bxeequities/auctionfeed/BxeEquities_AuctionFeed_v1_4.c
/*
 * Chicago Board Options Exchange Auction Feed
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
 *   - the dispatch that chooses a message by its type
 *   - a field filling what is left of what holds it
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

/* ---- Debug Packet: 1 byte ---------------------------------------------------- */

/* Debug packets are intended to provide human readable text that may aid in debugging problems. */
typedef struct {
  uint8_t text;  /* byte 0 */
} DebugPacket;

/* any Debug Packet at all: every byte one the checker chooses */
static void any_debug_packet(DebugPacket *record) {
  record->text = arbitrary();
}

/* Debug Packet to the wire: 1 byte from at, returning where the next byte goes */
static size_t encode_debug_packet(const DebugPacket *record, uint8_t *wire, size_t at) {
  wire[at++] = record->text;

  return at;
}

/* Debug Packet off the wire: 1 byte from at, returning where the next byte lies */
static size_t decode_debug_packet(DebugPacket *record, const uint8_t *wire, size_t at) {
  record->text = wire[at++];

  return at;
}

/* what was read of Debug Packet is what was written, byte for byte */
static void equal_debug_packet(const DebugPacket *read, const DebugPacket *written) {
  assert(read->text == written->text);
}

/* Debug Packet: written and read back, then read and written back */
static void check_debug_packet(void) {
  DebugPacket sent;
  DebugPacket got;
  uint8_t wire[1];
  uint8_t again[1];

  any_debug_packet(&sent);
  assert(encode_debug_packet(&sent, wire, 0) == 1);
  assert(decode_debug_packet(&got, wire, 0) == 1);
  equal_debug_packet(&got, &sent);

  for (size_t i = 0; i < 1; i++) { wire[i] = arbitrary(); }
  assert(decode_debug_packet(&got, wire, 0) == 1);
  assert(encode_debug_packet(&got, again, 0) == 1);
  for (size_t i = 0; i < 1; i++) { assert(again[i] == wire[i]); }
}

/* ---- Login Accepted Packet: 20 bytes ----------------------------------------- */

/* The Soup 2.0 server sends a Login Accepted Packet in response to receiving a valid Login Request  from the client. */
typedef struct {
  uint8_t session[10];          /* bytes 0 to 9 */
  uint8_t sequence_number[10];  /* bytes 10 to 19 */
} LoginAcceptedPacket;

/* any Login Accepted Packet at all: every byte one the checker chooses */
static void any_login_accepted_packet(LoginAcceptedPacket *record) {
  for (size_t i = 0; i < 10; i++) { record->session[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->sequence_number[i] = arbitrary(); }
}

/* Login Accepted Packet to the wire: 20 bytes from at, returning where the next byte goes */
static size_t encode_login_accepted_packet(const LoginAcceptedPacket *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->session[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->sequence_number[i]; }

  return at;
}

/* Login Accepted Packet off the wire: 20 bytes from at, returning where the next byte lies */
static size_t decode_login_accepted_packet(LoginAcceptedPacket *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 10; i++) { record->session[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->sequence_number[i] = wire[at++]; }

  return at;
}

/* what was read of Login Accepted Packet is what was written, byte for byte */
static void equal_login_accepted_packet(const LoginAcceptedPacket *read, const LoginAcceptedPacket *written) {
  for (size_t i = 0; i < 10; i++) { assert(read->session[i] == written->session[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->sequence_number[i] == written->sequence_number[i]); }
}

/* Login Accepted Packet: written and read back, then read and written back */
static void check_login_accepted_packet(void) {
  LoginAcceptedPacket sent;
  LoginAcceptedPacket got;
  uint8_t wire[20];
  uint8_t again[20];

  any_login_accepted_packet(&sent);
  assert(encode_login_accepted_packet(&sent, wire, 0) == 20);
  assert(decode_login_accepted_packet(&got, wire, 0) == 20);
  equal_login_accepted_packet(&got, &sent);

  for (size_t i = 0; i < 20; i++) { wire[i] = arbitrary(); }
  assert(decode_login_accepted_packet(&got, wire, 0) == 20);
  assert(encode_login_accepted_packet(&got, again, 0) == 20);
  for (size_t i = 0; i < 20; i++) { assert(again[i] == wire[i]); }
}

/* ---- Login Rejected Packet: 1 byte ------------------------------------------- */

/* The Soup 2.0 server sends this packet in response to an invalid Login Request Packet from the client. */
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

/* ---- Sequenced Message Header: 9 bytes --------------------------------------- */

/* Cboe Europe ASCII Soup sequenced message header */
typedef struct {
  uint8_t timestamp[8];            /* bytes 0 to 7 */
  uint8_t sequenced_message_type;  /* byte 8 */
} SequencedMessageHeader;

/* any Sequenced Message Header at all: every byte one the checker chooses */
static void any_sequenced_message_header(SequencedMessageHeader *record) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
  record->sequenced_message_type = arbitrary();
}

/* Sequenced Message Header to the wire: 9 bytes from at, returning where the next byte goes */
static size_t encode_sequenced_message_header(const SequencedMessageHeader *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }
  wire[at++] = record->sequenced_message_type;

  return at;
}

/* Sequenced Message Header off the wire: 9 bytes from at, returning where the next byte lies */
static size_t decode_sequenced_message_header(SequencedMessageHeader *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }
  record->sequenced_message_type = wire[at++];

  return at;
}

/* what was read of Sequenced Message Header is what was written, byte for byte */
static void equal_sequenced_message_header(const SequencedMessageHeader *read, const SequencedMessageHeader *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  assert(read->sequenced_message_type == written->sequenced_message_type);
}

/* Sequenced Message Header: written and read back, then read and written back */
static void check_sequenced_message_header(void) {
  SequencedMessageHeader sent;
  SequencedMessageHeader got;
  uint8_t wire[9];
  uint8_t again[9];

  any_sequenced_message_header(&sent);
  assert(encode_sequenced_message_header(&sent, wire, 0) == 9);
  assert(decode_sequenced_message_header(&got, wire, 0) == 9);
  equal_sequenced_message_header(&got, &sent);

  for (size_t i = 0; i < 9; i++) { wire[i] = arbitrary(); }
  assert(decode_sequenced_message_header(&got, wire, 0) == 9);
  assert(encode_sequenced_message_header(&got, again, 0) == 9);
  for (size_t i = 0; i < 9; i++) { assert(again[i] == wire[i]); }
}

/* ---- Auction Update Message: 59 bytes ---------------------------------------- */

/* Disseminates indicative price and size information during auctions for Cboe auction-eligible securities. */
typedef struct {
  uint8_t symbol[8];              /* bytes 0 to 7 */
  uint8_t auction_type;           /* byte 8 */
  uint8_t reference_price[19];    /* bytes 9 to 27 */
  uint8_t indicative_price[19];   /* bytes 28 to 46 */
  uint8_t indicative_shares[10];  /* bytes 47 to 56 */
  uint8_t outside_tolerance;      /* byte 57 */
  uint8_t includes_primary;       /* byte 58 */
} AuctionUpdateMessage;

/* any Auction Update Message at all: every byte one the checker chooses */
static void any_auction_update_message(AuctionUpdateMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->symbol[i] = arbitrary(); }
  record->auction_type = arbitrary();
  for (size_t i = 0; i < 19; i++) { record->reference_price[i] = arbitrary(); }
  for (size_t i = 0; i < 19; i++) { record->indicative_price[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->indicative_shares[i] = arbitrary(); }
  record->outside_tolerance = arbitrary();
  record->includes_primary = arbitrary();
}

/* Auction Update Message to the wire: 59 bytes from at, returning where the next byte goes */
static size_t encode_auction_update_message(const AuctionUpdateMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->symbol[i]; }
  wire[at++] = record->auction_type;
  for (size_t i = 0; i < 19; i++) { wire[at++] = record->reference_price[i]; }
  for (size_t i = 0; i < 19; i++) { wire[at++] = record->indicative_price[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->indicative_shares[i]; }
  wire[at++] = record->outside_tolerance;
  wire[at++] = record->includes_primary;

  return at;
}

/* Auction Update Message off the wire: 59 bytes from at, returning where the next byte lies */
static size_t decode_auction_update_message(AuctionUpdateMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->symbol[i] = wire[at++]; }
  record->auction_type = wire[at++];
  for (size_t i = 0; i < 19; i++) { record->reference_price[i] = wire[at++]; }
  for (size_t i = 0; i < 19; i++) { record->indicative_price[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->indicative_shares[i] = wire[at++]; }
  record->outside_tolerance = wire[at++];
  record->includes_primary = wire[at++];

  return at;
}

/* what was read of Auction Update Message is what was written, byte for byte */
static void equal_auction_update_message(const AuctionUpdateMessage *read, const AuctionUpdateMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->symbol[i] == written->symbol[i]); }
  assert(read->auction_type == written->auction_type);
  for (size_t i = 0; i < 19; i++) { assert(read->reference_price[i] == written->reference_price[i]); }
  for (size_t i = 0; i < 19; i++) { assert(read->indicative_price[i] == written->indicative_price[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->indicative_shares[i] == written->indicative_shares[i]); }
  assert(read->outside_tolerance == written->outside_tolerance);
  assert(read->includes_primary == written->includes_primary);
}

/* Auction Update Message: written and read back, then read and written back */
static void check_auction_update_message(void) {
  AuctionUpdateMessage sent;
  AuctionUpdateMessage got;
  uint8_t wire[59];
  uint8_t again[59];

  any_auction_update_message(&sent);
  assert(encode_auction_update_message(&sent, wire, 0) == 59);
  assert(decode_auction_update_message(&got, wire, 0) == 59);
  equal_auction_update_message(&got, &sent);

  for (size_t i = 0; i < 59; i++) { wire[i] = arbitrary(); }
  assert(decode_auction_update_message(&got, wire, 0) == 59);
  assert(encode_auction_update_message(&got, again, 0) == 59);
  for (size_t i = 0; i < 59; i++) { assert(again[i] == wire[i]); }
}

/* ---- Auction Summary Message: 38 bytes --------------------------------------- */

/* Disseminates the results of an auction in a Cboe auction-eligible security. */
typedef struct {
  uint8_t symbol[8];     /* bytes 0 to 7 */
  uint8_t auction_type;  /* byte 8 */
  uint8_t price[19];     /* bytes 9 to 27 */
  uint8_t shares[10];    /* bytes 28 to 37 */
} AuctionSummaryMessage;

/* any Auction Summary Message at all: every byte one the checker chooses */
static void any_auction_summary_message(AuctionSummaryMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->symbol[i] = arbitrary(); }
  record->auction_type = arbitrary();
  for (size_t i = 0; i < 19; i++) { record->price[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->shares[i] = arbitrary(); }
}

/* Auction Summary Message to the wire: 38 bytes from at, returning where the next byte goes */
static size_t encode_auction_summary_message(const AuctionSummaryMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->symbol[i]; }
  wire[at++] = record->auction_type;
  for (size_t i = 0; i < 19; i++) { wire[at++] = record->price[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->shares[i]; }

  return at;
}

/* Auction Summary Message off the wire: 38 bytes from at, returning where the next byte lies */
static size_t decode_auction_summary_message(AuctionSummaryMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->symbol[i] = wire[at++]; }
  record->auction_type = wire[at++];
  for (size_t i = 0; i < 19; i++) { record->price[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->shares[i] = wire[at++]; }

  return at;
}

/* what was read of Auction Summary Message is what was written, byte for byte */
static void equal_auction_summary_message(const AuctionSummaryMessage *read, const AuctionSummaryMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->symbol[i] == written->symbol[i]); }
  assert(read->auction_type == written->auction_type);
  for (size_t i = 0; i < 19; i++) { assert(read->price[i] == written->price[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->shares[i] == written->shares[i]); }
}

/* Auction Summary Message: written and read back, then read and written back */
static void check_auction_summary_message(void) {
  AuctionSummaryMessage sent;
  AuctionSummaryMessage got;
  uint8_t wire[38];
  uint8_t again[38];

  any_auction_summary_message(&sent);
  assert(encode_auction_summary_message(&sent, wire, 0) == 38);
  assert(decode_auction_summary_message(&got, wire, 0) == 38);
  equal_auction_summary_message(&got, &sent);

  for (size_t i = 0; i < 38; i++) { wire[i] = arbitrary(); }
  assert(decode_auction_summary_message(&got, wire, 0) == 38);
  assert(encode_auction_summary_message(&got, again, 0) == 38);
  for (size_t i = 0; i < 38; i++) { assert(again[i] == wire[i]); }
}

/* ---- Login Request Packet: 36 bytes ------------------------------------------ */

/* The Soup 2.0 client must send a Login Request Packet immediately upon establishing a new TCP/IP socket connection to the server. */
typedef struct {
  uint8_t username[6];                    /* bytes 0 to 5 */
  uint8_t password[10];                   /* bytes 6 to 15 */
  uint8_t requested_session[10];          /* bytes 16 to 25 */
  uint8_t requested_sequence_number[10];  /* bytes 26 to 35 */
} LoginRequestPacket;

/* any Login Request Packet at all: every byte one the checker chooses */
static void any_login_request_packet(LoginRequestPacket *record) {
  for (size_t i = 0; i < 6; i++) { record->username[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->password[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->requested_session[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->requested_sequence_number[i] = arbitrary(); }
}

/* Login Request Packet to the wire: 36 bytes from at, returning where the next byte goes */
static size_t encode_login_request_packet(const LoginRequestPacket *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->username[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->password[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->requested_session[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->requested_sequence_number[i]; }

  return at;
}

/* Login Request Packet off the wire: 36 bytes from at, returning where the next byte lies */
static size_t decode_login_request_packet(LoginRequestPacket *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 6; i++) { record->username[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->password[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->requested_session[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->requested_sequence_number[i] = wire[at++]; }

  return at;
}

/* what was read of Login Request Packet is what was written, byte for byte */
static void equal_login_request_packet(const LoginRequestPacket *read, const LoginRequestPacket *written) {
  for (size_t i = 0; i < 6; i++) { assert(read->username[i] == written->username[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->password[i] == written->password[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->requested_session[i] == written->requested_session[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->requested_sequence_number[i] == written->requested_sequence_number[i]); }
}

/* Login Request Packet: written and read back, then read and written back */
static void check_login_request_packet(void) {
  LoginRequestPacket sent;
  LoginRequestPacket got;
  uint8_t wire[36];
  uint8_t again[36];

  any_login_request_packet(&sent);
  assert(encode_login_request_packet(&sent, wire, 0) == 36);
  assert(decode_login_request_packet(&got, wire, 0) == 36);
  equal_login_request_packet(&got, &sent);

  for (size_t i = 0; i < 36; i++) { wire[i] = arbitrary(); }
  assert(decode_login_request_packet(&got, wire, 0) == 36);
  assert(encode_login_request_packet(&got, again, 0) == 36);
  for (size_t i = 0; i < 36; i++) { assert(again[i] == wire[i]); }
}

/* ---- What esbmc checks ------------------------------------------------------- */

/* every record of the protocol, each on its own buffers */
static void checks(void) {
  check_debug_packet();
  check_login_accepted_packet();
  check_login_rejected_packet();
  check_sequenced_message_header();
  check_auction_update_message();
  check_auction_summary_message();
  check_login_request_packet();
}

int main(void) {
#ifdef CONCRETE
  for (pattern = 0; pattern < 4; pattern++) { checks(); }
#else
  checks();
#endif

  return 0;
}
