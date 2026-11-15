// nasdaq/utp/input/Nasdaq_Utp_Input_v4_0_Server.c
/*
 * National Association of Securities Dealers Automated Quotations (Nasdaq)
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
 *   - a run counted by a field
 *   - a field of no fixed width
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

/* ---- Server Tcp Packet Header: 3 bytes --------------------------------------- */

/* Packet header of a packet sent by the server */
typedef struct {
  uint8_t packet_length[2];    /* bytes 0 to 1 */
  uint8_t server_packet_type;  /* byte 2 */
} ServerTcpPacketHeader;

/* any Server Tcp Packet Header at all: every byte one the checker chooses */
static void any_server_tcp_packet_header(ServerTcpPacketHeader *record) {
  for (size_t i = 0; i < 2; i++) { record->packet_length[i] = arbitrary(); }
  record->server_packet_type = arbitrary();
}

/* Server Tcp Packet Header to the wire: 3 bytes from at, returning where the next byte goes */
static size_t encode_server_tcp_packet_header(const ServerTcpPacketHeader *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->packet_length[i]; }
  wire[at++] = record->server_packet_type;

  return at;
}

/* Server Tcp Packet Header off the wire: 3 bytes from at, returning where the next byte lies */
static size_t decode_server_tcp_packet_header(ServerTcpPacketHeader *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->packet_length[i] = wire[at++]; }
  record->server_packet_type = wire[at++];

  return at;
}

/* what was read of Server Tcp Packet Header is what was written, byte for byte */
static void equal_server_tcp_packet_header(const ServerTcpPacketHeader *read, const ServerTcpPacketHeader *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->packet_length[i] == written->packet_length[i]); }
  assert(read->server_packet_type == written->server_packet_type);
}

/* Server Tcp Packet Header: written and read back, then read and written back */
static void check_server_tcp_packet_header(void) {
  ServerTcpPacketHeader sent;
  ServerTcpPacketHeader got;
  uint8_t wire[3];
  uint8_t again[3];

  any_server_tcp_packet_header(&sent);
  assert(encode_server_tcp_packet_header(&sent, wire, 0) == 3);
  assert(decode_server_tcp_packet_header(&got, wire, 0) == 3);
  equal_server_tcp_packet_header(&got, &sent);

  for (size_t i = 0; i < 3; i++) { wire[i] = arbitrary(); }
  assert(decode_server_tcp_packet_header(&got, wire, 0) == 3);
  assert(encode_server_tcp_packet_header(&got, again, 0) == 3);
  for (size_t i = 0; i < 3; i++) { assert(again[i] == wire[i]); }
}

/* ---- Message Header: 2 bytes ------------------------------------------------- */

/* UTP Participant Input message header — fixed Version + Message Category prefix common to inbound and return messages */
typedef struct {
  uint8_t version;           /* byte 0 */
  uint8_t message_category;  /* byte 1 */
} MessageHeader;

/* any Message Header at all: every byte one the checker chooses */
static void any_message_header(MessageHeader *record) {
  record->version = arbitrary();
  record->message_category = arbitrary();
}

/* Message Header to the wire: 2 bytes from at, returning where the next byte goes */
static size_t encode_message_header(const MessageHeader *record, uint8_t *wire, size_t at) {
  wire[at++] = record->version;
  wire[at++] = record->message_category;

  return at;
}

/* Message Header off the wire: 2 bytes from at, returning where the next byte lies */
static size_t decode_message_header(MessageHeader *record, const uint8_t *wire, size_t at) {
  record->version = wire[at++];
  record->message_category = wire[at++];

  return at;
}

/* what was read of Message Header is what was written, byte for byte */
static void equal_message_header(const MessageHeader *read, const MessageHeader *written) {
  assert(read->version == written->version);
  assert(read->message_category == written->message_category);
}

/* Message Header: written and read back, then read and written back */
static void check_message_header(void) {
  MessageHeader sent;
  MessageHeader got;
  uint8_t wire[2];
  uint8_t again[2];

  any_message_header(&sent);
  assert(encode_message_header(&sent, wire, 0) == 2);
  assert(decode_message_header(&got, wire, 0) == 2);
  equal_message_header(&got, &sent);

  for (size_t i = 0; i < 2; i++) { wire[i] = arbitrary(); }
  assert(decode_message_header(&got, wire, 0) == 2);
  assert(encode_message_header(&got, again, 0) == 2);
  for (size_t i = 0; i < 2; i++) { assert(again[i] == wire[i]); }
}

/* ---- Protected Exchange Quote Message Short Form Message: 41 bytes ----------- */

/* Short-format Exchange Quotation Message (QQ). Transmits Bid and Ask price and size from an Exchange to the SIP. */
typedef struct {
  uint8_t orig[2];            /* bytes 0 to 1 */
  uint8_t timestamp_1[8];     /* bytes 2 to 9 */
  uint8_t feed_sequence[8];   /* bytes 10 to 17 */
  uint8_t part_token[8];      /* bytes 18 to 25 */
  uint8_t symbol_short[5];    /* bytes 26 to 30 */
  uint8_t bid_short[2];       /* bytes 31 to 32 */
  uint8_t bid_size_short[2];  /* bytes 33 to 34 */
  uint8_t ask_short[2];       /* bytes 35 to 36 */
  uint8_t ask_size_short[2];  /* bytes 37 to 38 */
  uint8_t cond;               /* byte 39 */
  uint8_t rii;                /* byte 40 */
} ProtectedExchangeQuoteMessageShortFormMessage;

/* any Protected Exchange Quote Message Short Form Message at all: every byte one the checker chooses */
static void any_protected_exchange_quote_message_short_form_message(ProtectedExchangeQuoteMessageShortFormMessage *record) {
  for (size_t i = 0; i < 2; i++) { record->orig[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->timestamp_1[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->feed_sequence[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->part_token[i] = arbitrary(); }
  for (size_t i = 0; i < 5; i++) { record->symbol_short[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->bid_short[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->bid_size_short[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->ask_short[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->ask_size_short[i] = arbitrary(); }
  record->cond = arbitrary();
  record->rii = arbitrary();
}

/* Protected Exchange Quote Message Short Form Message to the wire: 41 bytes from at, returning where the next byte goes */
static size_t encode_protected_exchange_quote_message_short_form_message(const ProtectedExchangeQuoteMessageShortFormMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->orig[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp_1[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->feed_sequence[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->part_token[i]; }
  for (size_t i = 0; i < 5; i++) { wire[at++] = record->symbol_short[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->bid_short[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->bid_size_short[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->ask_short[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->ask_size_short[i]; }
  wire[at++] = record->cond;
  wire[at++] = record->rii;

  return at;
}

/* Protected Exchange Quote Message Short Form Message off the wire: 41 bytes from at, returning where the next byte lies */
static size_t decode_protected_exchange_quote_message_short_form_message(ProtectedExchangeQuoteMessageShortFormMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->orig[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->timestamp_1[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->feed_sequence[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->part_token[i] = wire[at++]; }
  for (size_t i = 0; i < 5; i++) { record->symbol_short[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->bid_short[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->bid_size_short[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->ask_short[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->ask_size_short[i] = wire[at++]; }
  record->cond = wire[at++];
  record->rii = wire[at++];

  return at;
}

/* what was read of Protected Exchange Quote Message Short Form Message is what was written, byte for byte */
static void equal_protected_exchange_quote_message_short_form_message(const ProtectedExchangeQuoteMessageShortFormMessage *read, const ProtectedExchangeQuoteMessageShortFormMessage *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->orig[i] == written->orig[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp_1[i] == written->timestamp_1[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->feed_sequence[i] == written->feed_sequence[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->part_token[i] == written->part_token[i]); }
  for (size_t i = 0; i < 5; i++) { assert(read->symbol_short[i] == written->symbol_short[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->bid_short[i] == written->bid_short[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->bid_size_short[i] == written->bid_size_short[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->ask_short[i] == written->ask_short[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->ask_size_short[i] == written->ask_size_short[i]); }
  assert(read->cond == written->cond);
  assert(read->rii == written->rii);
}

/* Protected Exchange Quote Message Short Form Message: written and read back, then read and written back */
static void check_protected_exchange_quote_message_short_form_message(void) {
  ProtectedExchangeQuoteMessageShortFormMessage sent;
  ProtectedExchangeQuoteMessageShortFormMessage got;
  uint8_t wire[41];
  uint8_t again[41];

  any_protected_exchange_quote_message_short_form_message(&sent);
  assert(encode_protected_exchange_quote_message_short_form_message(&sent, wire, 0) == 41);
  assert(decode_protected_exchange_quote_message_short_form_message(&got, wire, 0) == 41);
  equal_protected_exchange_quote_message_short_form_message(&got, &sent);

  for (size_t i = 0; i < 41; i++) { wire[i] = arbitrary(); }
  assert(decode_protected_exchange_quote_message_short_form_message(&got, wire, 0) == 41);
  assert(encode_protected_exchange_quote_message_short_form_message(&got, again, 0) == 41);
  for (size_t i = 0; i < 41; i++) { assert(again[i] == wire[i]); }
}

/* ---- Protected Exchange Quote Message Long Form Message: 63 bytes ------------ */

/* Long-format Exchange Quotation Message (QL). */
typedef struct {
  uint8_t orig[2];           /* bytes 0 to 1 */
  uint8_t timestamp_1[8];    /* bytes 2 to 9 */
  uint8_t feed_sequence[8];  /* bytes 10 to 17 */
  uint8_t part_token[8];     /* bytes 18 to 25 */
  uint8_t symbol_long[11];   /* bytes 26 to 36 */
  uint8_t bid_long[8];       /* bytes 37 to 44 */
  uint8_t bid_size_long[4];  /* bytes 45 to 48 */
  uint8_t ask_long[8];       /* bytes 49 to 56 */
  uint8_t ask_size_long[4];  /* bytes 57 to 60 */
  uint8_t cond;              /* byte 61 */
  uint8_t rii;               /* byte 62 */
} ProtectedExchangeQuoteMessageLongFormMessage;

/* any Protected Exchange Quote Message Long Form Message at all: every byte one the checker chooses */
static void any_protected_exchange_quote_message_long_form_message(ProtectedExchangeQuoteMessageLongFormMessage *record) {
  for (size_t i = 0; i < 2; i++) { record->orig[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->timestamp_1[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->feed_sequence[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->part_token[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->symbol_long[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->bid_long[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->bid_size_long[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->ask_long[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->ask_size_long[i] = arbitrary(); }
  record->cond = arbitrary();
  record->rii = arbitrary();
}

/* Protected Exchange Quote Message Long Form Message to the wire: 63 bytes from at, returning where the next byte goes */
static size_t encode_protected_exchange_quote_message_long_form_message(const ProtectedExchangeQuoteMessageLongFormMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->orig[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp_1[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->feed_sequence[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->part_token[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->symbol_long[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->bid_long[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->bid_size_long[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->ask_long[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->ask_size_long[i]; }
  wire[at++] = record->cond;
  wire[at++] = record->rii;

  return at;
}

/* Protected Exchange Quote Message Long Form Message off the wire: 63 bytes from at, returning where the next byte lies */
static size_t decode_protected_exchange_quote_message_long_form_message(ProtectedExchangeQuoteMessageLongFormMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->orig[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->timestamp_1[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->feed_sequence[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->part_token[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->symbol_long[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->bid_long[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->bid_size_long[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->ask_long[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->ask_size_long[i] = wire[at++]; }
  record->cond = wire[at++];
  record->rii = wire[at++];

  return at;
}

/* what was read of Protected Exchange Quote Message Long Form Message is what was written, byte for byte */
static void equal_protected_exchange_quote_message_long_form_message(const ProtectedExchangeQuoteMessageLongFormMessage *read, const ProtectedExchangeQuoteMessageLongFormMessage *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->orig[i] == written->orig[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp_1[i] == written->timestamp_1[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->feed_sequence[i] == written->feed_sequence[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->part_token[i] == written->part_token[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->symbol_long[i] == written->symbol_long[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->bid_long[i] == written->bid_long[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->bid_size_long[i] == written->bid_size_long[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->ask_long[i] == written->ask_long[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->ask_size_long[i] == written->ask_size_long[i]); }
  assert(read->cond == written->cond);
  assert(read->rii == written->rii);
}

/* Protected Exchange Quote Message Long Form Message: written and read back, then read and written back */
static void check_protected_exchange_quote_message_long_form_message(void) {
  ProtectedExchangeQuoteMessageLongFormMessage sent;
  ProtectedExchangeQuoteMessageLongFormMessage got;
  uint8_t wire[63];
  uint8_t again[63];

  any_protected_exchange_quote_message_long_form_message(&sent);
  assert(encode_protected_exchange_quote_message_long_form_message(&sent, wire, 0) == 63);
  assert(decode_protected_exchange_quote_message_long_form_message(&got, wire, 0) == 63);
  equal_protected_exchange_quote_message_long_form_message(&got, &sent);

  for (size_t i = 0; i < 63; i++) { wire[i] = arbitrary(); }
  assert(decode_protected_exchange_quote_message_long_form_message(&got, wire, 0) == 63);
  assert(encode_protected_exchange_quote_message_long_form_message(&got, again, 0) == 63);
  for (size_t i = 0; i < 63; i++) { assert(again[i] == wire[i]); }
}

/* ---- Finra Protected Quote Message With Bbo Info Message: 107 bytes ---------- */

/* FINRA BBO Quote Message w BBO Info (QG). */
typedef struct {
  uint8_t orig[2];           /* bytes 0 to 1 */
  uint8_t timestamp_1[8];    /* bytes 2 to 9 */
  uint8_t feed_sequence[8];  /* bytes 10 to 17 */
  uint8_t part_token[8];     /* bytes 18 to 25 */
  uint8_t timestamp_2[8];    /* bytes 26 to 33 */
  uint8_t symbol_long[11];   /* bytes 34 to 44 */
  uint8_t bid_long[8];       /* bytes 45 to 52 */
  uint8_t bid_size_long[4];  /* bytes 53 to 56 */
  uint8_t ask_long[8];       /* bytes 57 to 64 */
  uint8_t ask_size_long[4];  /* bytes 65 to 68 */
  uint8_t cond;              /* byte 69 */
  uint8_t mpid[4];           /* bytes 70 to 73 */
  uint8_t bbo_bid[8];        /* bytes 74 to 81 */
  uint8_t bbo_bid_size[4];   /* bytes 82 to 85 */
  uint8_t bbo_bid_mpid[4];   /* bytes 86 to 89 */
  uint8_t bbo_ask[8];        /* bytes 90 to 97 */
  uint8_t bbo_ask_size[4];   /* bytes 98 to 101 */
  uint8_t bbo_ask_mpid[4];   /* bytes 102 to 105 */
  uint8_t bbo_cond;          /* byte 106 */
} FinraProtectedQuoteMessageWithBboInfoMessage;

/* any Finra Protected Quote Message With Bbo Info Message at all: every byte one the checker chooses */
static void any_finra_protected_quote_message_with_bbo_info_message(FinraProtectedQuoteMessageWithBboInfoMessage *record) {
  for (size_t i = 0; i < 2; i++) { record->orig[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->timestamp_1[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->feed_sequence[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->part_token[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->timestamp_2[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->symbol_long[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->bid_long[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->bid_size_long[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->ask_long[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->ask_size_long[i] = arbitrary(); }
  record->cond = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->mpid[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->bbo_bid[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->bbo_bid_size[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->bbo_bid_mpid[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->bbo_ask[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->bbo_ask_size[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->bbo_ask_mpid[i] = arbitrary(); }
  record->bbo_cond = arbitrary();
}

/* Finra Protected Quote Message With Bbo Info Message to the wire: 107 bytes from at, returning where the next byte goes */
static size_t encode_finra_protected_quote_message_with_bbo_info_message(const FinraProtectedQuoteMessageWithBboInfoMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->orig[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp_1[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->feed_sequence[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->part_token[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp_2[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->symbol_long[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->bid_long[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->bid_size_long[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->ask_long[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->ask_size_long[i]; }
  wire[at++] = record->cond;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->mpid[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->bbo_bid[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->bbo_bid_size[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->bbo_bid_mpid[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->bbo_ask[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->bbo_ask_size[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->bbo_ask_mpid[i]; }
  wire[at++] = record->bbo_cond;

  return at;
}

/* Finra Protected Quote Message With Bbo Info Message off the wire: 107 bytes from at, returning where the next byte lies */
static size_t decode_finra_protected_quote_message_with_bbo_info_message(FinraProtectedQuoteMessageWithBboInfoMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->orig[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->timestamp_1[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->feed_sequence[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->part_token[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->timestamp_2[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->symbol_long[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->bid_long[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->bid_size_long[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->ask_long[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->ask_size_long[i] = wire[at++]; }
  record->cond = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->mpid[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->bbo_bid[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->bbo_bid_size[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->bbo_bid_mpid[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->bbo_ask[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->bbo_ask_size[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->bbo_ask_mpid[i] = wire[at++]; }
  record->bbo_cond = wire[at++];

  return at;
}

/* what was read of Finra Protected Quote Message With Bbo Info Message is what was written, byte for byte */
static void equal_finra_protected_quote_message_with_bbo_info_message(const FinraProtectedQuoteMessageWithBboInfoMessage *read, const FinraProtectedQuoteMessageWithBboInfoMessage *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->orig[i] == written->orig[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp_1[i] == written->timestamp_1[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->feed_sequence[i] == written->feed_sequence[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->part_token[i] == written->part_token[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp_2[i] == written->timestamp_2[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->symbol_long[i] == written->symbol_long[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->bid_long[i] == written->bid_long[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->bid_size_long[i] == written->bid_size_long[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->ask_long[i] == written->ask_long[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->ask_size_long[i] == written->ask_size_long[i]); }
  assert(read->cond == written->cond);
  for (size_t i = 0; i < 4; i++) { assert(read->mpid[i] == written->mpid[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->bbo_bid[i] == written->bbo_bid[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->bbo_bid_size[i] == written->bbo_bid_size[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->bbo_bid_mpid[i] == written->bbo_bid_mpid[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->bbo_ask[i] == written->bbo_ask[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->bbo_ask_size[i] == written->bbo_ask_size[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->bbo_ask_mpid[i] == written->bbo_ask_mpid[i]); }
  assert(read->bbo_cond == written->bbo_cond);
}

/* Finra Protected Quote Message With Bbo Info Message: written and read back, then read and written back */
static void check_finra_protected_quote_message_with_bbo_info_message(void) {
  FinraProtectedQuoteMessageWithBboInfoMessage sent;
  FinraProtectedQuoteMessageWithBboInfoMessage got;
  uint8_t wire[107];
  uint8_t again[107];

  any_finra_protected_quote_message_with_bbo_info_message(&sent);
  assert(encode_finra_protected_quote_message_with_bbo_info_message(&sent, wire, 0) == 107);
  assert(decode_finra_protected_quote_message_with_bbo_info_message(&got, wire, 0) == 107);
  equal_finra_protected_quote_message_with_bbo_info_message(&got, &sent);

  for (size_t i = 0; i < 107; i++) { wire[i] = arbitrary(); }
  assert(decode_finra_protected_quote_message_with_bbo_info_message(&got, wire, 0) == 107);
  assert(encode_finra_protected_quote_message_with_bbo_info_message(&got, again, 0) == 107);
  for (size_t i = 0; i < 107; i++) { assert(again[i] == wire[i]); }
}

/* ---- Finra Protected Quote Message Without Bbo Info Message: 75 bytes -------- */

/* FINRA BBO Quote Message without BBO Info (QF). */
typedef struct {
  uint8_t orig[2];           /* bytes 0 to 1 */
  uint8_t timestamp_1[8];    /* bytes 2 to 9 */
  uint8_t feed_sequence[8];  /* bytes 10 to 17 */
  uint8_t part_token[8];     /* bytes 18 to 25 */
  uint8_t timestamp_2[8];    /* bytes 26 to 33 */
  uint8_t symbol_long[11];   /* bytes 34 to 44 */
  uint8_t bid_long[8];       /* bytes 45 to 52 */
  uint8_t bid_size_long[4];  /* bytes 53 to 56 */
  uint8_t ask_long[8];       /* bytes 57 to 64 */
  uint8_t ask_size_long[4];  /* bytes 65 to 68 */
  uint8_t cond;              /* byte 69 */
  uint8_t mpid[4];           /* bytes 70 to 73 */
  uint8_t bbo_indicator;     /* byte 74 */
} FinraProtectedQuoteMessageWithoutBboInfoMessage;

/* any Finra Protected Quote Message Without Bbo Info Message at all: every byte one the checker chooses */
static void any_finra_protected_quote_message_without_bbo_info_message(FinraProtectedQuoteMessageWithoutBboInfoMessage *record) {
  for (size_t i = 0; i < 2; i++) { record->orig[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->timestamp_1[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->feed_sequence[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->part_token[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->timestamp_2[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->symbol_long[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->bid_long[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->bid_size_long[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->ask_long[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->ask_size_long[i] = arbitrary(); }
  record->cond = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->mpid[i] = arbitrary(); }
  record->bbo_indicator = arbitrary();
}

/* Finra Protected Quote Message Without Bbo Info Message to the wire: 75 bytes from at, returning where the next byte goes */
static size_t encode_finra_protected_quote_message_without_bbo_info_message(const FinraProtectedQuoteMessageWithoutBboInfoMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->orig[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp_1[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->feed_sequence[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->part_token[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp_2[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->symbol_long[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->bid_long[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->bid_size_long[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->ask_long[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->ask_size_long[i]; }
  wire[at++] = record->cond;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->mpid[i]; }
  wire[at++] = record->bbo_indicator;

  return at;
}

/* Finra Protected Quote Message Without Bbo Info Message off the wire: 75 bytes from at, returning where the next byte lies */
static size_t decode_finra_protected_quote_message_without_bbo_info_message(FinraProtectedQuoteMessageWithoutBboInfoMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->orig[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->timestamp_1[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->feed_sequence[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->part_token[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->timestamp_2[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->symbol_long[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->bid_long[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->bid_size_long[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->ask_long[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->ask_size_long[i] = wire[at++]; }
  record->cond = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->mpid[i] = wire[at++]; }
  record->bbo_indicator = wire[at++];

  return at;
}

/* what was read of Finra Protected Quote Message Without Bbo Info Message is what was written, byte for byte */
static void equal_finra_protected_quote_message_without_bbo_info_message(const FinraProtectedQuoteMessageWithoutBboInfoMessage *read, const FinraProtectedQuoteMessageWithoutBboInfoMessage *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->orig[i] == written->orig[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp_1[i] == written->timestamp_1[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->feed_sequence[i] == written->feed_sequence[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->part_token[i] == written->part_token[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp_2[i] == written->timestamp_2[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->symbol_long[i] == written->symbol_long[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->bid_long[i] == written->bid_long[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->bid_size_long[i] == written->bid_size_long[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->ask_long[i] == written->ask_long[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->ask_size_long[i] == written->ask_size_long[i]); }
  assert(read->cond == written->cond);
  for (size_t i = 0; i < 4; i++) { assert(read->mpid[i] == written->mpid[i]); }
  assert(read->bbo_indicator == written->bbo_indicator);
}

/* Finra Protected Quote Message Without Bbo Info Message: written and read back, then read and written back */
static void check_finra_protected_quote_message_without_bbo_info_message(void) {
  FinraProtectedQuoteMessageWithoutBboInfoMessage sent;
  FinraProtectedQuoteMessageWithoutBboInfoMessage got;
  uint8_t wire[75];
  uint8_t again[75];

  any_finra_protected_quote_message_without_bbo_info_message(&sent);
  assert(encode_finra_protected_quote_message_without_bbo_info_message(&sent, wire, 0) == 75);
  assert(decode_finra_protected_quote_message_without_bbo_info_message(&got, wire, 0) == 75);
  equal_finra_protected_quote_message_without_bbo_info_message(&got, &sent);

  for (size_t i = 0; i < 75; i++) { wire[i] = arbitrary(); }
  assert(decode_finra_protected_quote_message_without_bbo_info_message(&got, wire, 0) == 75);
  assert(encode_finra_protected_quote_message_without_bbo_info_message(&got, again, 0) == 75);
  for (size_t i = 0; i < 75; i++) { assert(again[i] == wire[i]); }
}

/* ---- Regular Trade Report Message: 69 bytes ---------------------------------- */

/* Regular Trade Report Message (TE). Carries whole-share last sale reports from an Exchange to the SIP. */
typedef struct {
  uint8_t orig[2];           /* bytes 0 to 1 */
  uint8_t timestamp_1[8];    /* bytes 2 to 9 */
  uint8_t feed_sequence[8];  /* bytes 10 to 17 */
  uint8_t part_token[8];     /* bytes 18 to 25 */
  uint8_t timestamp_2[8];    /* bytes 26 to 33 */
  uint8_t symbol_long[11];   /* bytes 34 to 44 */
  uint8_t trade_id[4];       /* bytes 45 to 48 */
  uint8_t tt_exempt;         /* byte 49 */
  uint8_t trcond[4];         /* bytes 50 to 53 */
  uint8_t ssday[2];          /* bytes 54 to 55 */
  uint8_t side;              /* byte 56 */
  uint8_t price[8];          /* bytes 57 to 64 */
  uint8_t volume[4];         /* bytes 65 to 68 */
} RegularTradeReportMessage;

/* any Regular Trade Report Message at all: every byte one the checker chooses */
static void any_regular_trade_report_message(RegularTradeReportMessage *record) {
  for (size_t i = 0; i < 2; i++) { record->orig[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->timestamp_1[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->feed_sequence[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->part_token[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->timestamp_2[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->symbol_long[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->trade_id[i] = arbitrary(); }
  record->tt_exempt = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->trcond[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->ssday[i] = arbitrary(); }
  record->side = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->volume[i] = arbitrary(); }
}

/* Regular Trade Report Message to the wire: 69 bytes from at, returning where the next byte goes */
static size_t encode_regular_trade_report_message(const RegularTradeReportMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->orig[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp_1[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->feed_sequence[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->part_token[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp_2[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->symbol_long[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->trade_id[i]; }
  wire[at++] = record->tt_exempt;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->trcond[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->ssday[i]; }
  wire[at++] = record->side;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->volume[i]; }

  return at;
}

/* Regular Trade Report Message off the wire: 69 bytes from at, returning where the next byte lies */
static size_t decode_regular_trade_report_message(RegularTradeReportMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->orig[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->timestamp_1[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->feed_sequence[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->part_token[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->timestamp_2[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->symbol_long[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->trade_id[i] = wire[at++]; }
  record->tt_exempt = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->trcond[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->ssday[i] = wire[at++]; }
  record->side = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->volume[i] = wire[at++]; }

  return at;
}

/* what was read of Regular Trade Report Message is what was written, byte for byte */
static void equal_regular_trade_report_message(const RegularTradeReportMessage *read, const RegularTradeReportMessage *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->orig[i] == written->orig[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp_1[i] == written->timestamp_1[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->feed_sequence[i] == written->feed_sequence[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->part_token[i] == written->part_token[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp_2[i] == written->timestamp_2[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->symbol_long[i] == written->symbol_long[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->trade_id[i] == written->trade_id[i]); }
  assert(read->tt_exempt == written->tt_exempt);
  for (size_t i = 0; i < 4; i++) { assert(read->trcond[i] == written->trcond[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->ssday[i] == written->ssday[i]); }
  assert(read->side == written->side);
  for (size_t i = 0; i < 8; i++) { assert(read->price[i] == written->price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->volume[i] == written->volume[i]); }
}

/* Regular Trade Report Message: written and read back, then read and written back */
static void check_regular_trade_report_message(void) {
  RegularTradeReportMessage sent;
  RegularTradeReportMessage got;
  uint8_t wire[69];
  uint8_t again[69];

  any_regular_trade_report_message(&sent);
  assert(encode_regular_trade_report_message(&sent, wire, 0) == 69);
  assert(decode_regular_trade_report_message(&got, wire, 0) == 69);
  equal_regular_trade_report_message(&got, &sent);

  for (size_t i = 0; i < 69; i++) { wire[i] = arbitrary(); }
  assert(decode_regular_trade_report_message(&got, wire, 0) == 69);
  assert(encode_regular_trade_report_message(&got, again, 0) == 69);
  for (size_t i = 0; i < 69; i++) { assert(again[i] == wire[i]); }
}

/* ---- Trade Cancel Error Message: 70 bytes ------------------------------------ */

/* Trade Cancel/Error Message (TI). Cancels or errors a previously delivered trade. */
typedef struct {
  uint8_t orig[2];           /* bytes 0 to 1 */
  uint8_t timestamp_1[8];    /* bytes 2 to 9 */
  uint8_t feed_sequence[8];  /* bytes 10 to 17 */
  uint8_t part_token[8];     /* bytes 18 to 25 */
  uint8_t timestamp_2[8];    /* bytes 26 to 33 */
  uint8_t symbol_long[11];   /* bytes 34 to 44 */
  uint8_t cancel_type;       /* byte 45 */
  uint8_t orig_trade_id[4];  /* bytes 46 to 49 */
  uint8_t orig_tt_exempt;    /* byte 50 */
  uint8_t orig_trcond[4];    /* bytes 51 to 54 */
  uint8_t orig_ssday[2];     /* bytes 55 to 56 */
  uint8_t orig_side;         /* byte 57 */
  uint8_t orig_price[8];     /* bytes 58 to 65 */
  uint8_t orig_volume[4];    /* bytes 66 to 69 */
} TradeCancelErrorMessage;

/* any Trade Cancel Error Message at all: every byte one the checker chooses */
static void any_trade_cancel_error_message(TradeCancelErrorMessage *record) {
  for (size_t i = 0; i < 2; i++) { record->orig[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->timestamp_1[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->feed_sequence[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->part_token[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->timestamp_2[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->symbol_long[i] = arbitrary(); }
  record->cancel_type = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->orig_trade_id[i] = arbitrary(); }
  record->orig_tt_exempt = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->orig_trcond[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->orig_ssday[i] = arbitrary(); }
  record->orig_side = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->orig_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->orig_volume[i] = arbitrary(); }
}

/* Trade Cancel Error Message to the wire: 70 bytes from at, returning where the next byte goes */
static size_t encode_trade_cancel_error_message(const TradeCancelErrorMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->orig[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp_1[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->feed_sequence[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->part_token[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp_2[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->symbol_long[i]; }
  wire[at++] = record->cancel_type;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->orig_trade_id[i]; }
  wire[at++] = record->orig_tt_exempt;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->orig_trcond[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->orig_ssday[i]; }
  wire[at++] = record->orig_side;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->orig_price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->orig_volume[i]; }

  return at;
}

/* Trade Cancel Error Message off the wire: 70 bytes from at, returning where the next byte lies */
static size_t decode_trade_cancel_error_message(TradeCancelErrorMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->orig[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->timestamp_1[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->feed_sequence[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->part_token[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->timestamp_2[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->symbol_long[i] = wire[at++]; }
  record->cancel_type = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->orig_trade_id[i] = wire[at++]; }
  record->orig_tt_exempt = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->orig_trcond[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->orig_ssday[i] = wire[at++]; }
  record->orig_side = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->orig_price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->orig_volume[i] = wire[at++]; }

  return at;
}

/* what was read of Trade Cancel Error Message is what was written, byte for byte */
static void equal_trade_cancel_error_message(const TradeCancelErrorMessage *read, const TradeCancelErrorMessage *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->orig[i] == written->orig[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp_1[i] == written->timestamp_1[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->feed_sequence[i] == written->feed_sequence[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->part_token[i] == written->part_token[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp_2[i] == written->timestamp_2[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->symbol_long[i] == written->symbol_long[i]); }
  assert(read->cancel_type == written->cancel_type);
  for (size_t i = 0; i < 4; i++) { assert(read->orig_trade_id[i] == written->orig_trade_id[i]); }
  assert(read->orig_tt_exempt == written->orig_tt_exempt);
  for (size_t i = 0; i < 4; i++) { assert(read->orig_trcond[i] == written->orig_trcond[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->orig_ssday[i] == written->orig_ssday[i]); }
  assert(read->orig_side == written->orig_side);
  for (size_t i = 0; i < 8; i++) { assert(read->orig_price[i] == written->orig_price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->orig_volume[i] == written->orig_volume[i]); }
}

/* Trade Cancel Error Message: written and read back, then read and written back */
static void check_trade_cancel_error_message(void) {
  TradeCancelErrorMessage sent;
  TradeCancelErrorMessage got;
  uint8_t wire[70];
  uint8_t again[70];

  any_trade_cancel_error_message(&sent);
  assert(encode_trade_cancel_error_message(&sent, wire, 0) == 70);
  assert(decode_trade_cancel_error_message(&got, wire, 0) == 70);
  equal_trade_cancel_error_message(&got, &sent);

  for (size_t i = 0; i < 70; i++) { wire[i] = arbitrary(); }
  assert(decode_trade_cancel_error_message(&got, wire, 0) == 70);
  assert(encode_trade_cancel_error_message(&got, again, 0) == 70);
  for (size_t i = 0; i < 70; i++) { assert(again[i] == wire[i]); }
}

/* ---- Trade Correction Message: 92 bytes -------------------------------------- */

/* Trade Correction Message (TJ). Corrects a previously delivered trade with new values. */
typedef struct {
  uint8_t orig[2];           /* bytes 0 to 1 */
  uint8_t timestamp_1[8];    /* bytes 2 to 9 */
  uint8_t feed_sequence[8];  /* bytes 10 to 17 */
  uint8_t part_token[8];     /* bytes 18 to 25 */
  uint8_t timestamp_2[8];    /* bytes 26 to 33 */
  uint8_t symbol_long[11];   /* bytes 34 to 44 */
  uint8_t trade_id[4];       /* bytes 45 to 48 */
  uint8_t orig_trade_id[4];  /* bytes 49 to 52 */
  uint8_t orig_tt_exempt;    /* byte 53 */
  uint8_t orig_trcond[4];    /* bytes 54 to 57 */
  uint8_t orig_ssday[2];     /* bytes 58 to 59 */
  uint8_t side;              /* byte 60 */
  uint8_t orig_price[8];     /* bytes 61 to 68 */
  uint8_t orig_volume[4];    /* bytes 69 to 72 */
  uint8_t new_tt_exempt;     /* byte 73 */
  uint8_t new_trcond[4];     /* bytes 74 to 77 */
  uint8_t new_ssday[2];      /* bytes 78 to 79 */
  uint8_t new_price[8];      /* bytes 80 to 87 */
  uint8_t new_volume[4];     /* bytes 88 to 91 */
} TradeCorrectionMessage;

/* any Trade Correction Message at all: every byte one the checker chooses */
static void any_trade_correction_message(TradeCorrectionMessage *record) {
  for (size_t i = 0; i < 2; i++) { record->orig[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->timestamp_1[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->feed_sequence[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->part_token[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->timestamp_2[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->symbol_long[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->trade_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->orig_trade_id[i] = arbitrary(); }
  record->orig_tt_exempt = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->orig_trcond[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->orig_ssday[i] = arbitrary(); }
  record->side = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->orig_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->orig_volume[i] = arbitrary(); }
  record->new_tt_exempt = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->new_trcond[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->new_ssday[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->new_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->new_volume[i] = arbitrary(); }
}

/* Trade Correction Message to the wire: 92 bytes from at, returning where the next byte goes */
static size_t encode_trade_correction_message(const TradeCorrectionMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->orig[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp_1[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->feed_sequence[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->part_token[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp_2[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->symbol_long[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->trade_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->orig_trade_id[i]; }
  wire[at++] = record->orig_tt_exempt;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->orig_trcond[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->orig_ssday[i]; }
  wire[at++] = record->side;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->orig_price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->orig_volume[i]; }
  wire[at++] = record->new_tt_exempt;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->new_trcond[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->new_ssday[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->new_price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->new_volume[i]; }

  return at;
}

/* Trade Correction Message off the wire: 92 bytes from at, returning where the next byte lies */
static size_t decode_trade_correction_message(TradeCorrectionMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->orig[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->timestamp_1[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->feed_sequence[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->part_token[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->timestamp_2[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->symbol_long[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->trade_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->orig_trade_id[i] = wire[at++]; }
  record->orig_tt_exempt = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->orig_trcond[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->orig_ssday[i] = wire[at++]; }
  record->side = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->orig_price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->orig_volume[i] = wire[at++]; }
  record->new_tt_exempt = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->new_trcond[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->new_ssday[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->new_price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->new_volume[i] = wire[at++]; }

  return at;
}

/* what was read of Trade Correction Message is what was written, byte for byte */
static void equal_trade_correction_message(const TradeCorrectionMessage *read, const TradeCorrectionMessage *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->orig[i] == written->orig[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp_1[i] == written->timestamp_1[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->feed_sequence[i] == written->feed_sequence[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->part_token[i] == written->part_token[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp_2[i] == written->timestamp_2[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->symbol_long[i] == written->symbol_long[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->trade_id[i] == written->trade_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->orig_trade_id[i] == written->orig_trade_id[i]); }
  assert(read->orig_tt_exempt == written->orig_tt_exempt);
  for (size_t i = 0; i < 4; i++) { assert(read->orig_trcond[i] == written->orig_trcond[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->orig_ssday[i] == written->orig_ssday[i]); }
  assert(read->side == written->side);
  for (size_t i = 0; i < 8; i++) { assert(read->orig_price[i] == written->orig_price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->orig_volume[i] == written->orig_volume[i]); }
  assert(read->new_tt_exempt == written->new_tt_exempt);
  for (size_t i = 0; i < 4; i++) { assert(read->new_trcond[i] == written->new_trcond[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->new_ssday[i] == written->new_ssday[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->new_price[i] == written->new_price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->new_volume[i] == written->new_volume[i]); }
}

/* Trade Correction Message: written and read back, then read and written back */
static void check_trade_correction_message(void) {
  TradeCorrectionMessage sent;
  TradeCorrectionMessage got;
  uint8_t wire[92];
  uint8_t again[92];

  any_trade_correction_message(&sent);
  assert(encode_trade_correction_message(&sent, wire, 0) == 92);
  assert(decode_trade_correction_message(&got, wire, 0) == 92);
  equal_trade_correction_message(&got, &sent);

  for (size_t i = 0; i < 92; i++) { wire[i] = arbitrary(); }
  assert(decode_trade_correction_message(&got, wire, 0) == 92);
  assert(encode_trade_correction_message(&got, again, 0) == 92);
  for (size_t i = 0; i < 92; i++) { assert(again[i] == wire[i]); }
}

/* ---- As Of Trade Report Message: 70 bytes ------------------------------------ */

/* As/Of Trade Report Message (TH). Reports a trade from a prior session date. */
typedef struct {
  uint8_t orig[2];           /* bytes 0 to 1 */
  uint8_t timestamp_1[8];    /* bytes 2 to 9 */
  uint8_t feed_sequence[8];  /* bytes 10 to 17 */
  uint8_t part_token[8];     /* bytes 18 to 25 */
  uint8_t symbol_long[11];   /* bytes 26 to 36 */
  uint8_t trade_id[4];       /* bytes 37 to 40 */
  uint8_t tt_exempt;         /* byte 41 */
  uint8_t trcond[4];         /* bytes 42 to 45 */
  uint8_t ssday[2];          /* bytes 46 to 47 */
  uint8_t side;              /* byte 48 */
  uint8_t price[8];          /* bytes 49 to 56 */
  uint8_t volume[4];         /* bytes 57 to 60 */
  uint8_t trade_time[8];     /* bytes 61 to 68 */
  uint8_t reversal;          /* byte 69 */
} AsOfTradeReportMessage;

/* any As Of Trade Report Message at all: every byte one the checker chooses */
static void any_as_of_trade_report_message(AsOfTradeReportMessage *record) {
  for (size_t i = 0; i < 2; i++) { record->orig[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->timestamp_1[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->feed_sequence[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->part_token[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->symbol_long[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->trade_id[i] = arbitrary(); }
  record->tt_exempt = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->trcond[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->ssday[i] = arbitrary(); }
  record->side = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->volume[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->trade_time[i] = arbitrary(); }
  record->reversal = arbitrary();
}

/* As Of Trade Report Message to the wire: 70 bytes from at, returning where the next byte goes */
static size_t encode_as_of_trade_report_message(const AsOfTradeReportMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->orig[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp_1[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->feed_sequence[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->part_token[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->symbol_long[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->trade_id[i]; }
  wire[at++] = record->tt_exempt;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->trcond[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->ssday[i]; }
  wire[at++] = record->side;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->volume[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->trade_time[i]; }
  wire[at++] = record->reversal;

  return at;
}

/* As Of Trade Report Message off the wire: 70 bytes from at, returning where the next byte lies */
static size_t decode_as_of_trade_report_message(AsOfTradeReportMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->orig[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->timestamp_1[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->feed_sequence[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->part_token[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->symbol_long[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->trade_id[i] = wire[at++]; }
  record->tt_exempt = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->trcond[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->ssday[i] = wire[at++]; }
  record->side = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->volume[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->trade_time[i] = wire[at++]; }
  record->reversal = wire[at++];

  return at;
}

/* what was read of As Of Trade Report Message is what was written, byte for byte */
static void equal_as_of_trade_report_message(const AsOfTradeReportMessage *read, const AsOfTradeReportMessage *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->orig[i] == written->orig[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp_1[i] == written->timestamp_1[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->feed_sequence[i] == written->feed_sequence[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->part_token[i] == written->part_token[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->symbol_long[i] == written->symbol_long[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->trade_id[i] == written->trade_id[i]); }
  assert(read->tt_exempt == written->tt_exempt);
  for (size_t i = 0; i < 4; i++) { assert(read->trcond[i] == written->trcond[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->ssday[i] == written->ssday[i]); }
  assert(read->side == written->side);
  for (size_t i = 0; i < 8; i++) { assert(read->price[i] == written->price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->volume[i] == written->volume[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->trade_time[i] == written->trade_time[i]); }
  assert(read->reversal == written->reversal);
}

/* As Of Trade Report Message: written and read back, then read and written back */
static void check_as_of_trade_report_message(void) {
  AsOfTradeReportMessage sent;
  AsOfTradeReportMessage got;
  uint8_t wire[70];
  uint8_t again[70];

  any_as_of_trade_report_message(&sent);
  assert(encode_as_of_trade_report_message(&sent, wire, 0) == 70);
  assert(decode_as_of_trade_report_message(&got, wire, 0) == 70);
  equal_as_of_trade_report_message(&got, &sent);

  for (size_t i = 0; i < 70; i++) { wire[i] = arbitrary(); }
  assert(decode_as_of_trade_report_message(&got, wire, 0) == 70);
  assert(encode_as_of_trade_report_message(&got, again, 0) == 70);
  for (size_t i = 0; i < 70; i++) { assert(again[i] == wire[i]); }
}

/* ---- Fractional Regular Trade Report Message: 73 bytes ----------------------- */

/* Fractional Regular Trade Report Message (TK). Last sale report with implied 6-decimal fractional volume. */
typedef struct {
  uint8_t orig[2];               /* bytes 0 to 1 */
  uint8_t timestamp_1[8];        /* bytes 2 to 9 */
  uint8_t feed_sequence[8];      /* bytes 10 to 17 */
  uint8_t part_token[8];         /* bytes 18 to 25 */
  uint8_t timestamp_2[8];        /* bytes 26 to 33 */
  uint8_t symbol_long[11];       /* bytes 34 to 44 */
  uint8_t trade_id[4];           /* bytes 45 to 48 */
  uint8_t tt_exempt;             /* byte 49 */
  uint8_t trcond[4];             /* bytes 50 to 53 */
  uint8_t ssday[2];              /* bytes 54 to 55 */
  uint8_t side;                  /* byte 56 */
  uint8_t price[8];              /* bytes 57 to 64 */
  uint8_t volume_fractional[8];  /* bytes 65 to 72 */
} FractionalRegularTradeReportMessage;

/* any Fractional Regular Trade Report Message at all: every byte one the checker chooses */
static void any_fractional_regular_trade_report_message(FractionalRegularTradeReportMessage *record) {
  for (size_t i = 0; i < 2; i++) { record->orig[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->timestamp_1[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->feed_sequence[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->part_token[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->timestamp_2[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->symbol_long[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->trade_id[i] = arbitrary(); }
  record->tt_exempt = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->trcond[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->ssday[i] = arbitrary(); }
  record->side = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->volume_fractional[i] = arbitrary(); }
}

/* Fractional Regular Trade Report Message to the wire: 73 bytes from at, returning where the next byte goes */
static size_t encode_fractional_regular_trade_report_message(const FractionalRegularTradeReportMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->orig[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp_1[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->feed_sequence[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->part_token[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp_2[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->symbol_long[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->trade_id[i]; }
  wire[at++] = record->tt_exempt;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->trcond[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->ssday[i]; }
  wire[at++] = record->side;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->volume_fractional[i]; }

  return at;
}

/* Fractional Regular Trade Report Message off the wire: 73 bytes from at, returning where the next byte lies */
static size_t decode_fractional_regular_trade_report_message(FractionalRegularTradeReportMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->orig[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->timestamp_1[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->feed_sequence[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->part_token[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->timestamp_2[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->symbol_long[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->trade_id[i] = wire[at++]; }
  record->tt_exempt = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->trcond[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->ssday[i] = wire[at++]; }
  record->side = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->volume_fractional[i] = wire[at++]; }

  return at;
}

/* what was read of Fractional Regular Trade Report Message is what was written, byte for byte */
static void equal_fractional_regular_trade_report_message(const FractionalRegularTradeReportMessage *read, const FractionalRegularTradeReportMessage *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->orig[i] == written->orig[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp_1[i] == written->timestamp_1[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->feed_sequence[i] == written->feed_sequence[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->part_token[i] == written->part_token[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp_2[i] == written->timestamp_2[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->symbol_long[i] == written->symbol_long[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->trade_id[i] == written->trade_id[i]); }
  assert(read->tt_exempt == written->tt_exempt);
  for (size_t i = 0; i < 4; i++) { assert(read->trcond[i] == written->trcond[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->ssday[i] == written->ssday[i]); }
  assert(read->side == written->side);
  for (size_t i = 0; i < 8; i++) { assert(read->price[i] == written->price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->volume_fractional[i] == written->volume_fractional[i]); }
}

/* Fractional Regular Trade Report Message: written and read back, then read and written back */
static void check_fractional_regular_trade_report_message(void) {
  FractionalRegularTradeReportMessage sent;
  FractionalRegularTradeReportMessage got;
  uint8_t wire[73];
  uint8_t again[73];

  any_fractional_regular_trade_report_message(&sent);
  assert(encode_fractional_regular_trade_report_message(&sent, wire, 0) == 73);
  assert(decode_fractional_regular_trade_report_message(&got, wire, 0) == 73);
  equal_fractional_regular_trade_report_message(&got, &sent);

  for (size_t i = 0; i < 73; i++) { wire[i] = arbitrary(); }
  assert(decode_fractional_regular_trade_report_message(&got, wire, 0) == 73);
  assert(encode_fractional_regular_trade_report_message(&got, again, 0) == 73);
  for (size_t i = 0; i < 73; i++) { assert(again[i] == wire[i]); }
}

/* ---- Fractional Trade Cancel Error Message: 74 bytes ------------------------- */

/* Fractional Trade Cancel/Error Message (TO). */
typedef struct {
  uint8_t orig[2];                    /* bytes 0 to 1 */
  uint8_t timestamp_1[8];             /* bytes 2 to 9 */
  uint8_t feed_sequence[8];           /* bytes 10 to 17 */
  uint8_t part_token[8];              /* bytes 18 to 25 */
  uint8_t timestamp_2[8];             /* bytes 26 to 33 */
  uint8_t symbol_long[11];            /* bytes 34 to 44 */
  uint8_t cancel_type;                /* byte 45 */
  uint8_t orig_trade_id[4];           /* bytes 46 to 49 */
  uint8_t orig_tt_exempt;             /* byte 50 */
  uint8_t orig_trcond[4];             /* bytes 51 to 54 */
  uint8_t orig_ssday[2];              /* bytes 55 to 56 */
  uint8_t orig_side;                  /* byte 57 */
  uint8_t orig_price[8];              /* bytes 58 to 65 */
  uint8_t orig_volume_fractional[8];  /* bytes 66 to 73 */
} FractionalTradeCancelErrorMessage;

/* any Fractional Trade Cancel Error Message at all: every byte one the checker chooses */
static void any_fractional_trade_cancel_error_message(FractionalTradeCancelErrorMessage *record) {
  for (size_t i = 0; i < 2; i++) { record->orig[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->timestamp_1[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->feed_sequence[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->part_token[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->timestamp_2[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->symbol_long[i] = arbitrary(); }
  record->cancel_type = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->orig_trade_id[i] = arbitrary(); }
  record->orig_tt_exempt = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->orig_trcond[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->orig_ssday[i] = arbitrary(); }
  record->orig_side = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->orig_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->orig_volume_fractional[i] = arbitrary(); }
}

/* Fractional Trade Cancel Error Message to the wire: 74 bytes from at, returning where the next byte goes */
static size_t encode_fractional_trade_cancel_error_message(const FractionalTradeCancelErrorMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->orig[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp_1[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->feed_sequence[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->part_token[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp_2[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->symbol_long[i]; }
  wire[at++] = record->cancel_type;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->orig_trade_id[i]; }
  wire[at++] = record->orig_tt_exempt;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->orig_trcond[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->orig_ssday[i]; }
  wire[at++] = record->orig_side;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->orig_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->orig_volume_fractional[i]; }

  return at;
}

/* Fractional Trade Cancel Error Message off the wire: 74 bytes from at, returning where the next byte lies */
static size_t decode_fractional_trade_cancel_error_message(FractionalTradeCancelErrorMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->orig[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->timestamp_1[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->feed_sequence[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->part_token[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->timestamp_2[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->symbol_long[i] = wire[at++]; }
  record->cancel_type = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->orig_trade_id[i] = wire[at++]; }
  record->orig_tt_exempt = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->orig_trcond[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->orig_ssday[i] = wire[at++]; }
  record->orig_side = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->orig_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->orig_volume_fractional[i] = wire[at++]; }

  return at;
}

/* what was read of Fractional Trade Cancel Error Message is what was written, byte for byte */
static void equal_fractional_trade_cancel_error_message(const FractionalTradeCancelErrorMessage *read, const FractionalTradeCancelErrorMessage *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->orig[i] == written->orig[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp_1[i] == written->timestamp_1[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->feed_sequence[i] == written->feed_sequence[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->part_token[i] == written->part_token[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp_2[i] == written->timestamp_2[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->symbol_long[i] == written->symbol_long[i]); }
  assert(read->cancel_type == written->cancel_type);
  for (size_t i = 0; i < 4; i++) { assert(read->orig_trade_id[i] == written->orig_trade_id[i]); }
  assert(read->orig_tt_exempt == written->orig_tt_exempt);
  for (size_t i = 0; i < 4; i++) { assert(read->orig_trcond[i] == written->orig_trcond[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->orig_ssday[i] == written->orig_ssday[i]); }
  assert(read->orig_side == written->orig_side);
  for (size_t i = 0; i < 8; i++) { assert(read->orig_price[i] == written->orig_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->orig_volume_fractional[i] == written->orig_volume_fractional[i]); }
}

/* Fractional Trade Cancel Error Message: written and read back, then read and written back */
static void check_fractional_trade_cancel_error_message(void) {
  FractionalTradeCancelErrorMessage sent;
  FractionalTradeCancelErrorMessage got;
  uint8_t wire[74];
  uint8_t again[74];

  any_fractional_trade_cancel_error_message(&sent);
  assert(encode_fractional_trade_cancel_error_message(&sent, wire, 0) == 74);
  assert(decode_fractional_trade_cancel_error_message(&got, wire, 0) == 74);
  equal_fractional_trade_cancel_error_message(&got, &sent);

  for (size_t i = 0; i < 74; i++) { wire[i] = arbitrary(); }
  assert(decode_fractional_trade_cancel_error_message(&got, wire, 0) == 74);
  assert(encode_fractional_trade_cancel_error_message(&got, again, 0) == 74);
  for (size_t i = 0; i < 74; i++) { assert(again[i] == wire[i]); }
}

/* ---- Fractional Trade Correction Message: 100 bytes -------------------------- */

/* Fractional Trade Correction Message (TP). */
typedef struct {
  uint8_t orig[2];                    /* bytes 0 to 1 */
  uint8_t timestamp_1[8];             /* bytes 2 to 9 */
  uint8_t feed_sequence[8];           /* bytes 10 to 17 */
  uint8_t part_token[8];              /* bytes 18 to 25 */
  uint8_t timestamp_2[8];             /* bytes 26 to 33 */
  uint8_t symbol_long[11];            /* bytes 34 to 44 */
  uint8_t trade_id[4];                /* bytes 45 to 48 */
  uint8_t orig_trade_id[4];           /* bytes 49 to 52 */
  uint8_t orig_tt_exempt;             /* byte 53 */
  uint8_t orig_trcond[4];             /* bytes 54 to 57 */
  uint8_t orig_ssday[2];              /* bytes 58 to 59 */
  uint8_t side;                       /* byte 60 */
  uint8_t orig_price[8];              /* bytes 61 to 68 */
  uint8_t orig_volume_fractional[8];  /* bytes 69 to 76 */
  uint8_t new_tt_exempt;              /* byte 77 */
  uint8_t new_trcond[4];              /* bytes 78 to 81 */
  uint8_t new_ssday[2];               /* bytes 82 to 83 */
  uint8_t new_price[8];               /* bytes 84 to 91 */
  uint8_t new_volume_fractional[8];   /* bytes 92 to 99 */
} FractionalTradeCorrectionMessage;

/* any Fractional Trade Correction Message at all: every byte one the checker chooses */
static void any_fractional_trade_correction_message(FractionalTradeCorrectionMessage *record) {
  for (size_t i = 0; i < 2; i++) { record->orig[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->timestamp_1[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->feed_sequence[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->part_token[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->timestamp_2[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->symbol_long[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->trade_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->orig_trade_id[i] = arbitrary(); }
  record->orig_tt_exempt = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->orig_trcond[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->orig_ssday[i] = arbitrary(); }
  record->side = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->orig_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->orig_volume_fractional[i] = arbitrary(); }
  record->new_tt_exempt = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->new_trcond[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->new_ssday[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->new_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->new_volume_fractional[i] = arbitrary(); }
}

/* Fractional Trade Correction Message to the wire: 100 bytes from at, returning where the next byte goes */
static size_t encode_fractional_trade_correction_message(const FractionalTradeCorrectionMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->orig[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp_1[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->feed_sequence[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->part_token[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp_2[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->symbol_long[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->trade_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->orig_trade_id[i]; }
  wire[at++] = record->orig_tt_exempt;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->orig_trcond[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->orig_ssday[i]; }
  wire[at++] = record->side;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->orig_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->orig_volume_fractional[i]; }
  wire[at++] = record->new_tt_exempt;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->new_trcond[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->new_ssday[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->new_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->new_volume_fractional[i]; }

  return at;
}

/* Fractional Trade Correction Message off the wire: 100 bytes from at, returning where the next byte lies */
static size_t decode_fractional_trade_correction_message(FractionalTradeCorrectionMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->orig[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->timestamp_1[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->feed_sequence[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->part_token[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->timestamp_2[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->symbol_long[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->trade_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->orig_trade_id[i] = wire[at++]; }
  record->orig_tt_exempt = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->orig_trcond[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->orig_ssday[i] = wire[at++]; }
  record->side = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->orig_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->orig_volume_fractional[i] = wire[at++]; }
  record->new_tt_exempt = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->new_trcond[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->new_ssday[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->new_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->new_volume_fractional[i] = wire[at++]; }

  return at;
}

/* what was read of Fractional Trade Correction Message is what was written, byte for byte */
static void equal_fractional_trade_correction_message(const FractionalTradeCorrectionMessage *read, const FractionalTradeCorrectionMessage *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->orig[i] == written->orig[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp_1[i] == written->timestamp_1[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->feed_sequence[i] == written->feed_sequence[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->part_token[i] == written->part_token[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp_2[i] == written->timestamp_2[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->symbol_long[i] == written->symbol_long[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->trade_id[i] == written->trade_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->orig_trade_id[i] == written->orig_trade_id[i]); }
  assert(read->orig_tt_exempt == written->orig_tt_exempt);
  for (size_t i = 0; i < 4; i++) { assert(read->orig_trcond[i] == written->orig_trcond[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->orig_ssday[i] == written->orig_ssday[i]); }
  assert(read->side == written->side);
  for (size_t i = 0; i < 8; i++) { assert(read->orig_price[i] == written->orig_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->orig_volume_fractional[i] == written->orig_volume_fractional[i]); }
  assert(read->new_tt_exempt == written->new_tt_exempt);
  for (size_t i = 0; i < 4; i++) { assert(read->new_trcond[i] == written->new_trcond[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->new_ssday[i] == written->new_ssday[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->new_price[i] == written->new_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->new_volume_fractional[i] == written->new_volume_fractional[i]); }
}

/* Fractional Trade Correction Message: written and read back, then read and written back */
static void check_fractional_trade_correction_message(void) {
  FractionalTradeCorrectionMessage sent;
  FractionalTradeCorrectionMessage got;
  uint8_t wire[100];
  uint8_t again[100];

  any_fractional_trade_correction_message(&sent);
  assert(encode_fractional_trade_correction_message(&sent, wire, 0) == 100);
  assert(decode_fractional_trade_correction_message(&got, wire, 0) == 100);
  equal_fractional_trade_correction_message(&got, &sent);

  for (size_t i = 0; i < 100; i++) { wire[i] = arbitrary(); }
  assert(decode_fractional_trade_correction_message(&got, wire, 0) == 100);
  assert(encode_fractional_trade_correction_message(&got, again, 0) == 100);
  for (size_t i = 0; i < 100; i++) { assert(again[i] == wire[i]); }
}

/* ---- Fractional As Of Trade Report Message: 74 bytes ------------------------- */

/* Fractional As/Of Trade Report Message (TQ). */
typedef struct {
  uint8_t orig[2];               /* bytes 0 to 1 */
  uint8_t timestamp_1[8];        /* bytes 2 to 9 */
  uint8_t feed_sequence[8];      /* bytes 10 to 17 */
  uint8_t part_token[8];         /* bytes 18 to 25 */
  uint8_t symbol_long[11];       /* bytes 26 to 36 */
  uint8_t trade_id[4];           /* bytes 37 to 40 */
  uint8_t tt_exempt;             /* byte 41 */
  uint8_t trcond[4];             /* bytes 42 to 45 */
  uint8_t ssday[2];              /* bytes 46 to 47 */
  uint8_t side;                  /* byte 48 */
  uint8_t price[8];              /* bytes 49 to 56 */
  uint8_t volume_fractional[8];  /* bytes 57 to 64 */
  uint8_t trade_time[8];         /* bytes 65 to 72 */
  uint8_t reversal;              /* byte 73 */
} FractionalAsOfTradeReportMessage;

/* any Fractional As Of Trade Report Message at all: every byte one the checker chooses */
static void any_fractional_as_of_trade_report_message(FractionalAsOfTradeReportMessage *record) {
  for (size_t i = 0; i < 2; i++) { record->orig[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->timestamp_1[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->feed_sequence[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->part_token[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->symbol_long[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->trade_id[i] = arbitrary(); }
  record->tt_exempt = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->trcond[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->ssday[i] = arbitrary(); }
  record->side = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->volume_fractional[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->trade_time[i] = arbitrary(); }
  record->reversal = arbitrary();
}

/* Fractional As Of Trade Report Message to the wire: 74 bytes from at, returning where the next byte goes */
static size_t encode_fractional_as_of_trade_report_message(const FractionalAsOfTradeReportMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->orig[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp_1[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->feed_sequence[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->part_token[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->symbol_long[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->trade_id[i]; }
  wire[at++] = record->tt_exempt;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->trcond[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->ssday[i]; }
  wire[at++] = record->side;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->volume_fractional[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->trade_time[i]; }
  wire[at++] = record->reversal;

  return at;
}

/* Fractional As Of Trade Report Message off the wire: 74 bytes from at, returning where the next byte lies */
static size_t decode_fractional_as_of_trade_report_message(FractionalAsOfTradeReportMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->orig[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->timestamp_1[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->feed_sequence[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->part_token[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->symbol_long[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->trade_id[i] = wire[at++]; }
  record->tt_exempt = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->trcond[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->ssday[i] = wire[at++]; }
  record->side = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->volume_fractional[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->trade_time[i] = wire[at++]; }
  record->reversal = wire[at++];

  return at;
}

/* what was read of Fractional As Of Trade Report Message is what was written, byte for byte */
static void equal_fractional_as_of_trade_report_message(const FractionalAsOfTradeReportMessage *read, const FractionalAsOfTradeReportMessage *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->orig[i] == written->orig[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp_1[i] == written->timestamp_1[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->feed_sequence[i] == written->feed_sequence[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->part_token[i] == written->part_token[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->symbol_long[i] == written->symbol_long[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->trade_id[i] == written->trade_id[i]); }
  assert(read->tt_exempt == written->tt_exempt);
  for (size_t i = 0; i < 4; i++) { assert(read->trcond[i] == written->trcond[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->ssday[i] == written->ssday[i]); }
  assert(read->side == written->side);
  for (size_t i = 0; i < 8; i++) { assert(read->price[i] == written->price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->volume_fractional[i] == written->volume_fractional[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->trade_time[i] == written->trade_time[i]); }
  assert(read->reversal == written->reversal);
}

/* Fractional As Of Trade Report Message: written and read back, then read and written back */
static void check_fractional_as_of_trade_report_message(void) {
  FractionalAsOfTradeReportMessage sent;
  FractionalAsOfTradeReportMessage got;
  uint8_t wire[74];
  uint8_t again[74];

  any_fractional_as_of_trade_report_message(&sent);
  assert(encode_fractional_as_of_trade_report_message(&sent, wire, 0) == 74);
  assert(decode_fractional_as_of_trade_report_message(&got, wire, 0) == 74);
  equal_fractional_as_of_trade_report_message(&got, &sent);

  for (size_t i = 0; i < 74; i++) { wire[i] = arbitrary(); }
  assert(decode_fractional_as_of_trade_report_message(&got, wire, 0) == 74);
  assert(encode_fractional_as_of_trade_report_message(&got, again, 0) == 74);
  for (size_t i = 0; i < 74; i++) { assert(again[i] == wire[i]); }
}

/* ---- Trading Action Message: 56 bytes ---------------------------------------- */

/* Trading Action Message (AO). Listing market notifies SIP of halts and other trading state events. */
typedef struct {
  uint8_t orig[2];             /* bytes 0 to 1 */
  uint8_t timestamp_1[8];      /* bytes 2 to 9 */
  uint8_t feed_sequence[8];    /* bytes 10 to 17 */
  uint8_t part_token[8];       /* bytes 18 to 25 */
  uint8_t symbol_long[11];     /* bytes 26 to 36 */
  uint8_t action;              /* byte 37 */
  uint8_t action_sequence[4];  /* bytes 38 to 41 */
  uint8_t action_time[8];      /* bytes 42 to 49 */
  uint8_t reason[6];           /* bytes 50 to 55 */
} TradingActionMessage;

/* any Trading Action Message at all: every byte one the checker chooses */
static void any_trading_action_message(TradingActionMessage *record) {
  for (size_t i = 0; i < 2; i++) { record->orig[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->timestamp_1[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->feed_sequence[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->part_token[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->symbol_long[i] = arbitrary(); }
  record->action = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->action_sequence[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->action_time[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->reason[i] = arbitrary(); }
}

/* Trading Action Message to the wire: 56 bytes from at, returning where the next byte goes */
static size_t encode_trading_action_message(const TradingActionMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->orig[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp_1[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->feed_sequence[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->part_token[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->symbol_long[i]; }
  wire[at++] = record->action;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->action_sequence[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->action_time[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->reason[i]; }

  return at;
}

/* Trading Action Message off the wire: 56 bytes from at, returning where the next byte lies */
static size_t decode_trading_action_message(TradingActionMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->orig[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->timestamp_1[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->feed_sequence[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->part_token[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->symbol_long[i] = wire[at++]; }
  record->action = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->action_sequence[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->action_time[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->reason[i] = wire[at++]; }

  return at;
}

/* what was read of Trading Action Message is what was written, byte for byte */
static void equal_trading_action_message(const TradingActionMessage *read, const TradingActionMessage *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->orig[i] == written->orig[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp_1[i] == written->timestamp_1[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->feed_sequence[i] == written->feed_sequence[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->part_token[i] == written->part_token[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->symbol_long[i] == written->symbol_long[i]); }
  assert(read->action == written->action);
  for (size_t i = 0; i < 4; i++) { assert(read->action_sequence[i] == written->action_sequence[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->action_time[i] == written->action_time[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->reason[i] == written->reason[i]); }
}

/* Trading Action Message: written and read back, then read and written back */
static void check_trading_action_message(void) {
  TradingActionMessage sent;
  TradingActionMessage got;
  uint8_t wire[56];
  uint8_t again[56];

  any_trading_action_message(&sent);
  assert(encode_trading_action_message(&sent, wire, 0) == 56);
  assert(decode_trading_action_message(&got, wire, 0) == 56);
  equal_trading_action_message(&got, &sent);

  for (size_t i = 0; i < 56; i++) { wire[i] = arbitrary(); }
  assert(decode_trading_action_message(&got, wire, 0) == 56);
  assert(encode_trading_action_message(&got, again, 0) == 56);
  for (size_t i = 0; i < 56; i++) { assert(again[i] == wire[i]); }
}

/* ---- Market Center Trading Action Message: 46 bytes -------------------------- */

/* Market Center Trading Action Message (AJ). Participant-specific trading halt on the participant's own market only. */
typedef struct {
  uint8_t orig[2];           /* bytes 0 to 1 */
  uint8_t timestamp_1[8];    /* bytes 2 to 9 */
  uint8_t feed_sequence[8];  /* bytes 10 to 17 */
  uint8_t part_token[8];     /* bytes 18 to 25 */
  uint8_t symbol_long[11];   /* bytes 26 to 36 */
  uint8_t action;            /* byte 37 */
  uint8_t action_time[8];    /* bytes 38 to 45 */
} MarketCenterTradingActionMessage;

/* any Market Center Trading Action Message at all: every byte one the checker chooses */
static void any_market_center_trading_action_message(MarketCenterTradingActionMessage *record) {
  for (size_t i = 0; i < 2; i++) { record->orig[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->timestamp_1[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->feed_sequence[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->part_token[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->symbol_long[i] = arbitrary(); }
  record->action = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->action_time[i] = arbitrary(); }
}

/* Market Center Trading Action Message to the wire: 46 bytes from at, returning where the next byte goes */
static size_t encode_market_center_trading_action_message(const MarketCenterTradingActionMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->orig[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp_1[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->feed_sequence[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->part_token[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->symbol_long[i]; }
  wire[at++] = record->action;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->action_time[i]; }

  return at;
}

/* Market Center Trading Action Message off the wire: 46 bytes from at, returning where the next byte lies */
static size_t decode_market_center_trading_action_message(MarketCenterTradingActionMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->orig[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->timestamp_1[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->feed_sequence[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->part_token[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->symbol_long[i] = wire[at++]; }
  record->action = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->action_time[i] = wire[at++]; }

  return at;
}

/* what was read of Market Center Trading Action Message is what was written, byte for byte */
static void equal_market_center_trading_action_message(const MarketCenterTradingActionMessage *read, const MarketCenterTradingActionMessage *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->orig[i] == written->orig[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp_1[i] == written->timestamp_1[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->feed_sequence[i] == written->feed_sequence[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->part_token[i] == written->part_token[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->symbol_long[i] == written->symbol_long[i]); }
  assert(read->action == written->action);
  for (size_t i = 0; i < 8; i++) { assert(read->action_time[i] == written->action_time[i]); }
}

/* Market Center Trading Action Message: written and read back, then read and written back */
static void check_market_center_trading_action_message(void) {
  MarketCenterTradingActionMessage sent;
  MarketCenterTradingActionMessage got;
  uint8_t wire[46];
  uint8_t again[46];

  any_market_center_trading_action_message(&sent);
  assert(encode_market_center_trading_action_message(&sent, wire, 0) == 46);
  assert(decode_market_center_trading_action_message(&got, wire, 0) == 46);
  equal_market_center_trading_action_message(&got, &sent);

  for (size_t i = 0; i < 46; i++) { wire[i] = arbitrary(); }
  assert(decode_market_center_trading_action_message(&got, wire, 0) == 46);
  assert(encode_market_center_trading_action_message(&got, again, 0) == 46);
  for (size_t i = 0; i < 46; i++) { assert(again[i] == wire[i]); }
}

/* ---- Market Center Mass Trading Action Message: 57 bytes --------------------- */

/* Market Center Mass Trading Action Message (AU). Applies action across a range of securities. No acknowledgement is returned. */
typedef struct {
  uint8_t orig[2];             /* bytes 0 to 1 */
  uint8_t timestamp_1[8];      /* bytes 2 to 9 */
  uint8_t feed_sequence[8];    /* bytes 10 to 17 */
  uint8_t part_token[8];       /* bytes 18 to 25 */
  uint8_t first_security[11];  /* bytes 26 to 36 */
  uint8_t last_security[11];   /* bytes 37 to 47 */
  uint8_t action;              /* byte 48 */
  uint8_t action_time[8];      /* bytes 49 to 56 */
} MarketCenterMassTradingActionMessage;

/* any Market Center Mass Trading Action Message at all: every byte one the checker chooses */
static void any_market_center_mass_trading_action_message(MarketCenterMassTradingActionMessage *record) {
  for (size_t i = 0; i < 2; i++) { record->orig[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->timestamp_1[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->feed_sequence[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->part_token[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->first_security[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->last_security[i] = arbitrary(); }
  record->action = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->action_time[i] = arbitrary(); }
}

/* Market Center Mass Trading Action Message to the wire: 57 bytes from at, returning where the next byte goes */
static size_t encode_market_center_mass_trading_action_message(const MarketCenterMassTradingActionMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->orig[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp_1[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->feed_sequence[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->part_token[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->first_security[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->last_security[i]; }
  wire[at++] = record->action;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->action_time[i]; }

  return at;
}

/* Market Center Mass Trading Action Message off the wire: 57 bytes from at, returning where the next byte lies */
static size_t decode_market_center_mass_trading_action_message(MarketCenterMassTradingActionMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->orig[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->timestamp_1[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->feed_sequence[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->part_token[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->first_security[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->last_security[i] = wire[at++]; }
  record->action = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->action_time[i] = wire[at++]; }

  return at;
}

/* what was read of Market Center Mass Trading Action Message is what was written, byte for byte */
static void equal_market_center_mass_trading_action_message(const MarketCenterMassTradingActionMessage *read, const MarketCenterMassTradingActionMessage *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->orig[i] == written->orig[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp_1[i] == written->timestamp_1[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->feed_sequence[i] == written->feed_sequence[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->part_token[i] == written->part_token[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->first_security[i] == written->first_security[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->last_security[i] == written->last_security[i]); }
  assert(read->action == written->action);
  for (size_t i = 0; i < 8; i++) { assert(read->action_time[i] == written->action_time[i]); }
}

/* Market Center Mass Trading Action Message: written and read back, then read and written back */
static void check_market_center_mass_trading_action_message(void) {
  MarketCenterMassTradingActionMessage sent;
  MarketCenterMassTradingActionMessage got;
  uint8_t wire[57];
  uint8_t again[57];

  any_market_center_mass_trading_action_message(&sent);
  assert(encode_market_center_mass_trading_action_message(&sent, wire, 0) == 57);
  assert(decode_market_center_mass_trading_action_message(&got, wire, 0) == 57);
  equal_market_center_mass_trading_action_message(&got, &sent);

  for (size_t i = 0; i < 57; i++) { wire[i] = arbitrary(); }
  assert(decode_market_center_mass_trading_action_message(&got, wire, 0) == 57);
  assert(encode_market_center_mass_trading_action_message(&got, again, 0) == 57);
  for (size_t i = 0; i < 57; i++) { assert(again[i] == wire[i]); }
}

/* ---- Reg Sho Short Sale Price Test Restricted Indicator Message: 38 bytes ---- */

/* Reg SHO Short Sale Price Test Restricted Indicator Message (AV). Notifies that a security has breached the short sale price test threshold. */
typedef struct {
  uint8_t orig[2];           /* bytes 0 to 1 */
  uint8_t timestamp_1[8];    /* bytes 2 to 9 */
  uint8_t feed_sequence[8];  /* bytes 10 to 17 */
  uint8_t part_token[8];     /* bytes 18 to 25 */
  uint8_t symbol_long[11];   /* bytes 26 to 36 */
  uint8_t action;            /* byte 37 */
} RegShoShortSalePriceTestRestrictedIndicatorMessage;

/* any Reg Sho Short Sale Price Test Restricted Indicator Message at all: every byte one the checker chooses */
static void any_reg_sho_short_sale_price_test_restricted_indicator_message(RegShoShortSalePriceTestRestrictedIndicatorMessage *record) {
  for (size_t i = 0; i < 2; i++) { record->orig[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->timestamp_1[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->feed_sequence[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->part_token[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->symbol_long[i] = arbitrary(); }
  record->action = arbitrary();
}

/* Reg Sho Short Sale Price Test Restricted Indicator Message to the wire: 38 bytes from at, returning where the next byte goes */
static size_t encode_reg_sho_short_sale_price_test_restricted_indicator_message(const RegShoShortSalePriceTestRestrictedIndicatorMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->orig[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp_1[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->feed_sequence[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->part_token[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->symbol_long[i]; }
  wire[at++] = record->action;

  return at;
}

/* Reg Sho Short Sale Price Test Restricted Indicator Message off the wire: 38 bytes from at, returning where the next byte lies */
static size_t decode_reg_sho_short_sale_price_test_restricted_indicator_message(RegShoShortSalePriceTestRestrictedIndicatorMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->orig[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->timestamp_1[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->feed_sequence[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->part_token[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->symbol_long[i] = wire[at++]; }
  record->action = wire[at++];

  return at;
}

/* what was read of Reg Sho Short Sale Price Test Restricted Indicator Message is what was written, byte for byte */
static void equal_reg_sho_short_sale_price_test_restricted_indicator_message(const RegShoShortSalePriceTestRestrictedIndicatorMessage *read, const RegShoShortSalePriceTestRestrictedIndicatorMessage *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->orig[i] == written->orig[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp_1[i] == written->timestamp_1[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->feed_sequence[i] == written->feed_sequence[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->part_token[i] == written->part_token[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->symbol_long[i] == written->symbol_long[i]); }
  assert(read->action == written->action);
}

/* Reg Sho Short Sale Price Test Restricted Indicator Message: written and read back, then read and written back */
static void check_reg_sho_short_sale_price_test_restricted_indicator_message(void) {
  RegShoShortSalePriceTestRestrictedIndicatorMessage sent;
  RegShoShortSalePriceTestRestrictedIndicatorMessage got;
  uint8_t wire[38];
  uint8_t again[38];

  any_reg_sho_short_sale_price_test_restricted_indicator_message(&sent);
  assert(encode_reg_sho_short_sale_price_test_restricted_indicator_message(&sent, wire, 0) == 38);
  assert(decode_reg_sho_short_sale_price_test_restricted_indicator_message(&got, wire, 0) == 38);
  equal_reg_sho_short_sale_price_test_restricted_indicator_message(&got, &sent);

  for (size_t i = 0; i < 38; i++) { wire[i] = arbitrary(); }
  assert(decode_reg_sho_short_sale_price_test_restricted_indicator_message(&got, wire, 0) == 38);
  assert(encode_reg_sho_short_sale_price_test_restricted_indicator_message(&got, again, 0) == 38);
  for (size_t i = 0; i < 38; i++) { assert(again[i] == wire[i]); }
}

/* ---- Opening Reference Midpoint Price Message: 45 bytes ---------------------- */

/* Opening Reference Midpoint Price Message (AM). Listing market provides midpoint reference price for LULD calculations. */
typedef struct {
  uint8_t orig[2];           /* bytes 0 to 1 */
  uint8_t timestamp_1[8];    /* bytes 2 to 9 */
  uint8_t feed_sequence[8];  /* bytes 10 to 17 */
  uint8_t part_token[8];     /* bytes 18 to 25 */
  uint8_t symbol_long[11];   /* bytes 26 to 36 */
  uint8_t price[8];          /* bytes 37 to 44 */
} OpeningReferenceMidpointPriceMessage;

/* any Opening Reference Midpoint Price Message at all: every byte one the checker chooses */
static void any_opening_reference_midpoint_price_message(OpeningReferenceMidpointPriceMessage *record) {
  for (size_t i = 0; i < 2; i++) { record->orig[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->timestamp_1[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->feed_sequence[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->part_token[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->symbol_long[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->price[i] = arbitrary(); }
}

/* Opening Reference Midpoint Price Message to the wire: 45 bytes from at, returning where the next byte goes */
static size_t encode_opening_reference_midpoint_price_message(const OpeningReferenceMidpointPriceMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->orig[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp_1[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->feed_sequence[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->part_token[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->symbol_long[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price[i]; }

  return at;
}

/* Opening Reference Midpoint Price Message off the wire: 45 bytes from at, returning where the next byte lies */
static size_t decode_opening_reference_midpoint_price_message(OpeningReferenceMidpointPriceMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->orig[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->timestamp_1[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->feed_sequence[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->part_token[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->symbol_long[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->price[i] = wire[at++]; }

  return at;
}

/* what was read of Opening Reference Midpoint Price Message is what was written, byte for byte */
static void equal_opening_reference_midpoint_price_message(const OpeningReferenceMidpointPriceMessage *read, const OpeningReferenceMidpointPriceMessage *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->orig[i] == written->orig[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp_1[i] == written->timestamp_1[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->feed_sequence[i] == written->feed_sequence[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->part_token[i] == written->part_token[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->symbol_long[i] == written->symbol_long[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->price[i] == written->price[i]); }
}

/* Opening Reference Midpoint Price Message: written and read back, then read and written back */
static void check_opening_reference_midpoint_price_message(void) {
  OpeningReferenceMidpointPriceMessage sent;
  OpeningReferenceMidpointPriceMessage got;
  uint8_t wire[45];
  uint8_t again[45];

  any_opening_reference_midpoint_price_message(&sent);
  assert(encode_opening_reference_midpoint_price_message(&sent, wire, 0) == 45);
  assert(decode_opening_reference_midpoint_price_message(&got, wire, 0) == 45);
  equal_opening_reference_midpoint_price_message(&got, &sent);

  for (size_t i = 0; i < 45; i++) { wire[i] = arbitrary(); }
  assert(decode_opening_reference_midpoint_price_message(&got, wire, 0) == 45);
  assert(encode_opening_reference_midpoint_price_message(&got, again, 0) == 45);
  for (size_t i = 0; i < 45; i++) { assert(again[i] == wire[i]); }
}

/* ---- T 1 Adjusted Closing Price Message: 45 bytes ---------------------------- */

/* T1 Adjusted Closing Price Message (AN). Listing market provides closing price for LULD calculations. */
typedef struct {
  uint8_t orig[2];           /* bytes 0 to 1 */
  uint8_t timestamp_1[8];    /* bytes 2 to 9 */
  uint8_t feed_sequence[8];  /* bytes 10 to 17 */
  uint8_t part_token[8];     /* bytes 18 to 25 */
  uint8_t symbol_long[11];   /* bytes 26 to 36 */
  uint8_t price[8];          /* bytes 37 to 44 */
} T1AdjustedClosingPriceMessage;

/* any T 1 Adjusted Closing Price Message at all: every byte one the checker chooses */
static void any_t1_adjusted_closing_price_message(T1AdjustedClosingPriceMessage *record) {
  for (size_t i = 0; i < 2; i++) { record->orig[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->timestamp_1[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->feed_sequence[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->part_token[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->symbol_long[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->price[i] = arbitrary(); }
}

/* T 1 Adjusted Closing Price Message to the wire: 45 bytes from at, returning where the next byte goes */
static size_t encode_t1_adjusted_closing_price_message(const T1AdjustedClosingPriceMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->orig[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp_1[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->feed_sequence[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->part_token[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->symbol_long[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price[i]; }

  return at;
}

/* T 1 Adjusted Closing Price Message off the wire: 45 bytes from at, returning where the next byte lies */
static size_t decode_t1_adjusted_closing_price_message(T1AdjustedClosingPriceMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->orig[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->timestamp_1[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->feed_sequence[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->part_token[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->symbol_long[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->price[i] = wire[at++]; }

  return at;
}

/* what was read of T 1 Adjusted Closing Price Message is what was written, byte for byte */
static void equal_t1_adjusted_closing_price_message(const T1AdjustedClosingPriceMessage *read, const T1AdjustedClosingPriceMessage *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->orig[i] == written->orig[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp_1[i] == written->timestamp_1[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->feed_sequence[i] == written->feed_sequence[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->part_token[i] == written->part_token[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->symbol_long[i] == written->symbol_long[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->price[i] == written->price[i]); }
}

/* T 1 Adjusted Closing Price Message: written and read back, then read and written back */
static void check_t1_adjusted_closing_price_message(void) {
  T1AdjustedClosingPriceMessage sent;
  T1AdjustedClosingPriceMessage got;
  uint8_t wire[45];
  uint8_t again[45];

  any_t1_adjusted_closing_price_message(&sent);
  assert(encode_t1_adjusted_closing_price_message(&sent, wire, 0) == 45);
  assert(decode_t1_adjusted_closing_price_message(&got, wire, 0) == 45);
  equal_t1_adjusted_closing_price_message(&got, &sent);

  for (size_t i = 0; i < 45; i++) { wire[i] = arbitrary(); }
  assert(decode_t1_adjusted_closing_price_message(&got, wire, 0) == 45);
  assert(encode_t1_adjusted_closing_price_message(&got, again, 0) == 45);
  for (size_t i = 0; i < 45; i++) { assert(again[i] == wire[i]); }
}

/* ---- Market Open Message: 26 bytes ------------------------------------------- */

/* Market Open Message (AX). Indicates participant quotes should be marked as opened. */
typedef struct {
  uint8_t orig[2];           /* bytes 0 to 1 */
  uint8_t timestamp_1[8];    /* bytes 2 to 9 */
  uint8_t feed_sequence[8];  /* bytes 10 to 17 */
  uint8_t part_token[8];     /* bytes 18 to 25 */
} MarketOpenMessage;

/* any Market Open Message at all: every byte one the checker chooses */
static void any_market_open_message(MarketOpenMessage *record) {
  for (size_t i = 0; i < 2; i++) { record->orig[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->timestamp_1[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->feed_sequence[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->part_token[i] = arbitrary(); }
}

/* Market Open Message to the wire: 26 bytes from at, returning where the next byte goes */
static size_t encode_market_open_message(const MarketOpenMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->orig[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp_1[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->feed_sequence[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->part_token[i]; }

  return at;
}

/* Market Open Message off the wire: 26 bytes from at, returning where the next byte lies */
static size_t decode_market_open_message(MarketOpenMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->orig[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->timestamp_1[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->feed_sequence[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->part_token[i] = wire[at++]; }

  return at;
}

/* what was read of Market Open Message is what was written, byte for byte */
static void equal_market_open_message(const MarketOpenMessage *read, const MarketOpenMessage *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->orig[i] == written->orig[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp_1[i] == written->timestamp_1[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->feed_sequence[i] == written->feed_sequence[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->part_token[i] == written->part_token[i]); }
}

/* Market Open Message: written and read back, then read and written back */
static void check_market_open_message(void) {
  MarketOpenMessage sent;
  MarketOpenMessage got;
  uint8_t wire[26];
  uint8_t again[26];

  any_market_open_message(&sent);
  assert(encode_market_open_message(&sent, wire, 0) == 26);
  assert(decode_market_open_message(&got, wire, 0) == 26);
  equal_market_open_message(&got, &sent);

  for (size_t i = 0; i < 26; i++) { wire[i] = arbitrary(); }
  assert(decode_market_open_message(&got, wire, 0) == 26);
  assert(encode_market_open_message(&got, again, 0) == 26);
  for (size_t i = 0; i < 26; i++) { assert(again[i] == wire[i]); }
}

/* ---- Market Closed Message: 26 bytes ----------------------------------------- */

/* Market Closed Message (AY). Indicates the trading session is ready to close. */
typedef struct {
  uint8_t orig[2];           /* bytes 0 to 1 */
  uint8_t timestamp_1[8];    /* bytes 2 to 9 */
  uint8_t feed_sequence[8];  /* bytes 10 to 17 */
  uint8_t part_token[8];     /* bytes 18 to 25 */
} MarketClosedMessage;

/* any Market Closed Message at all: every byte one the checker chooses */
static void any_market_closed_message(MarketClosedMessage *record) {
  for (size_t i = 0; i < 2; i++) { record->orig[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->timestamp_1[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->feed_sequence[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->part_token[i] = arbitrary(); }
}

/* Market Closed Message to the wire: 26 bytes from at, returning where the next byte goes */
static size_t encode_market_closed_message(const MarketClosedMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->orig[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp_1[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->feed_sequence[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->part_token[i]; }

  return at;
}

/* Market Closed Message off the wire: 26 bytes from at, returning where the next byte lies */
static size_t decode_market_closed_message(MarketClosedMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->orig[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->timestamp_1[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->feed_sequence[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->part_token[i] = wire[at++]; }

  return at;
}

/* what was read of Market Closed Message is what was written, byte for byte */
static void equal_market_closed_message(const MarketClosedMessage *read, const MarketClosedMessage *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->orig[i] == written->orig[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp_1[i] == written->timestamp_1[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->feed_sequence[i] == written->feed_sequence[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->part_token[i] == written->part_token[i]); }
}

/* Market Closed Message: written and read back, then read and written back */
static void check_market_closed_message(void) {
  MarketClosedMessage sent;
  MarketClosedMessage got;
  uint8_t wire[26];
  uint8_t again[26];

  any_market_closed_message(&sent);
  assert(encode_market_closed_message(&sent, wire, 0) == 26);
  assert(decode_market_closed_message(&got, wire, 0) == 26);
  equal_market_closed_message(&got, &sent);

  for (size_t i = 0; i < 26; i++) { wire[i] = arbitrary(); }
  assert(decode_market_closed_message(&got, wire, 0) == 26);
  assert(encode_market_closed_message(&got, again, 0) == 26);
  for (size_t i = 0; i < 26; i++) { assert(again[i] == wire[i]); }
}

/* ---- Auction Collar Message: 66 bytes ---------------------------------------- */

/* Auction Collar Message (AE). Listing market provides new Price Protection Limits used during LULD trading pauses (and during extended operational hours). */
typedef struct {
  uint8_t orig[2];                    /* bytes 0 to 1 */
  uint8_t timestamp_1[8];             /* bytes 2 to 9 */
  uint8_t feed_sequence[8];           /* bytes 10 to 17 */
  uint8_t part_token[8];              /* bytes 18 to 25 */
  uint8_t symbol_long[11];            /* bytes 26 to 36 */
  uint8_t action_sequence[4];         /* bytes 37 to 40 */
  uint8_t collar_reference_price[8];  /* bytes 41 to 48 */
  uint8_t collar_up_price[8];         /* bytes 49 to 56 */
  uint8_t collar_down_price[8];       /* bytes 57 to 64 */
  uint8_t collar_extension;           /* byte 65 */
} AuctionCollarMessage;

/* any Auction Collar Message at all: every byte one the checker chooses */
static void any_auction_collar_message(AuctionCollarMessage *record) {
  for (size_t i = 0; i < 2; i++) { record->orig[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->timestamp_1[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->feed_sequence[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->part_token[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->symbol_long[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->action_sequence[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->collar_reference_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->collar_up_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->collar_down_price[i] = arbitrary(); }
  record->collar_extension = arbitrary();
}

/* Auction Collar Message to the wire: 66 bytes from at, returning where the next byte goes */
static size_t encode_auction_collar_message(const AuctionCollarMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->orig[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp_1[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->feed_sequence[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->part_token[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->symbol_long[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->action_sequence[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->collar_reference_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->collar_up_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->collar_down_price[i]; }
  wire[at++] = record->collar_extension;

  return at;
}

/* Auction Collar Message off the wire: 66 bytes from at, returning where the next byte lies */
static size_t decode_auction_collar_message(AuctionCollarMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->orig[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->timestamp_1[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->feed_sequence[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->part_token[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->symbol_long[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->action_sequence[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->collar_reference_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->collar_up_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->collar_down_price[i] = wire[at++]; }
  record->collar_extension = wire[at++];

  return at;
}

/* what was read of Auction Collar Message is what was written, byte for byte */
static void equal_auction_collar_message(const AuctionCollarMessage *read, const AuctionCollarMessage *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->orig[i] == written->orig[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp_1[i] == written->timestamp_1[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->feed_sequence[i] == written->feed_sequence[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->part_token[i] == written->part_token[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->symbol_long[i] == written->symbol_long[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->action_sequence[i] == written->action_sequence[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->collar_reference_price[i] == written->collar_reference_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->collar_up_price[i] == written->collar_up_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->collar_down_price[i] == written->collar_down_price[i]); }
  assert(read->collar_extension == written->collar_extension);
}

/* Auction Collar Message: written and read back, then read and written back */
static void check_auction_collar_message(void) {
  AuctionCollarMessage sent;
  AuctionCollarMessage got;
  uint8_t wire[66];
  uint8_t again[66];

  any_auction_collar_message(&sent);
  assert(encode_auction_collar_message(&sent, wire, 0) == 66);
  assert(decode_auction_collar_message(&got, wire, 0) == 66);
  equal_auction_collar_message(&got, &sent);

  for (size_t i = 0; i < 66; i++) { wire[i] = arbitrary(); }
  assert(decode_auction_collar_message(&got, wire, 0) == 66);
  assert(encode_auction_collar_message(&got, again, 0) == 66);
  for (size_t i = 0; i < 66; i++) { assert(again[i] == wire[i]); }
}

/* ---- Sequence Inquiry Message: 26 bytes -------------------------------------- */

/* Sequence Inquiry Message (CC). Participant requests current expected sequence number from SIP. */
typedef struct {
  uint8_t orig[2];           /* bytes 0 to 1 */
  uint8_t timestamp_1[8];    /* bytes 2 to 9 */
  uint8_t feed_sequence[8];  /* bytes 10 to 17 */
  uint8_t part_token[8];     /* bytes 18 to 25 */
} SequenceInquiryMessage;

/* any Sequence Inquiry Message at all: every byte one the checker chooses */
static void any_sequence_inquiry_message(SequenceInquiryMessage *record) {
  for (size_t i = 0; i < 2; i++) { record->orig[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->timestamp_1[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->feed_sequence[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->part_token[i] = arbitrary(); }
}

/* Sequence Inquiry Message to the wire: 26 bytes from at, returning where the next byte goes */
static size_t encode_sequence_inquiry_message(const SequenceInquiryMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->orig[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp_1[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->feed_sequence[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->part_token[i]; }

  return at;
}

/* Sequence Inquiry Message off the wire: 26 bytes from at, returning where the next byte lies */
static size_t decode_sequence_inquiry_message(SequenceInquiryMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->orig[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->timestamp_1[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->feed_sequence[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->part_token[i] = wire[at++]; }

  return at;
}

/* what was read of Sequence Inquiry Message is what was written, byte for byte */
static void equal_sequence_inquiry_message(const SequenceInquiryMessage *read, const SequenceInquiryMessage *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->orig[i] == written->orig[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp_1[i] == written->timestamp_1[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->feed_sequence[i] == written->feed_sequence[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->part_token[i] == written->part_token[i]); }
}

/* Sequence Inquiry Message: written and read back, then read and written back */
static void check_sequence_inquiry_message(void) {
  SequenceInquiryMessage sent;
  SequenceInquiryMessage got;
  uint8_t wire[26];
  uint8_t again[26];

  any_sequence_inquiry_message(&sent);
  assert(encode_sequence_inquiry_message(&sent, wire, 0) == 26);
  assert(decode_sequence_inquiry_message(&got, wire, 0) == 26);
  equal_sequence_inquiry_message(&got, &sent);

  for (size_t i = 0; i < 26; i++) { wire[i] = arbitrary(); }
  assert(decode_sequence_inquiry_message(&got, wire, 0) == 26);
  assert(encode_sequence_inquiry_message(&got, again, 0) == 26);
  for (size_t i = 0; i < 26; i++) { assert(again[i] == wire[i]); }
}

/* ---- Symbol State Inquiry Message: 37 bytes ---------------------------------- */

/* Symbol State Inquiry Message (CS). Participant requests current per-symbol state from SIP. */
typedef struct {
  uint8_t orig[2];           /* bytes 0 to 1 */
  uint8_t timestamp_1[8];    /* bytes 2 to 9 */
  uint8_t feed_sequence[8];  /* bytes 10 to 17 */
  uint8_t part_token[8];     /* bytes 18 to 25 */
  uint8_t symbol_long[11];   /* bytes 26 to 36 */
} SymbolStateInquiryMessage;

/* any Symbol State Inquiry Message at all: every byte one the checker chooses */
static void any_symbol_state_inquiry_message(SymbolStateInquiryMessage *record) {
  for (size_t i = 0; i < 2; i++) { record->orig[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->timestamp_1[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->feed_sequence[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->part_token[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->symbol_long[i] = arbitrary(); }
}

/* Symbol State Inquiry Message to the wire: 37 bytes from at, returning where the next byte goes */
static size_t encode_symbol_state_inquiry_message(const SymbolStateInquiryMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->orig[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp_1[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->feed_sequence[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->part_token[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->symbol_long[i]; }

  return at;
}

/* Symbol State Inquiry Message off the wire: 37 bytes from at, returning where the next byte lies */
static size_t decode_symbol_state_inquiry_message(SymbolStateInquiryMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->orig[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->timestamp_1[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->feed_sequence[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->part_token[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->symbol_long[i] = wire[at++]; }

  return at;
}

/* what was read of Symbol State Inquiry Message is what was written, byte for byte */
static void equal_symbol_state_inquiry_message(const SymbolStateInquiryMessage *read, const SymbolStateInquiryMessage *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->orig[i] == written->orig[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp_1[i] == written->timestamp_1[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->feed_sequence[i] == written->feed_sequence[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->part_token[i] == written->part_token[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->symbol_long[i] == written->symbol_long[i]); }
}

/* Symbol State Inquiry Message: written and read back, then read and written back */
static void check_symbol_state_inquiry_message(void) {
  SymbolStateInquiryMessage sent;
  SymbolStateInquiryMessage got;
  uint8_t wire[37];
  uint8_t again[37];

  any_symbol_state_inquiry_message(&sent);
  assert(encode_symbol_state_inquiry_message(&sent, wire, 0) == 37);
  assert(decode_symbol_state_inquiry_message(&got, wire, 0) == 37);
  equal_symbol_state_inquiry_message(&got, &sent);

  for (size_t i = 0; i < 37; i++) { wire[i] = arbitrary(); }
  assert(decode_symbol_state_inquiry_message(&got, wire, 0) == 37);
  assert(encode_symbol_state_inquiry_message(&got, again, 0) == 37);
  for (size_t i = 0; i < 37; i++) { assert(again[i] == wire[i]); }
}

/* ---- End Of Participant Reporting Message: 26 bytes -------------------------- */

/* End Of Participant Reporting Message (CG). Participant signals it has finished reporting for the session. */
typedef struct {
  uint8_t orig[2];           /* bytes 0 to 1 */
  uint8_t timestamp_1[8];    /* bytes 2 to 9 */
  uint8_t feed_sequence[8];  /* bytes 10 to 17 */
  uint8_t part_token[8];     /* bytes 18 to 25 */
} EndOfParticipantReportingMessage;

/* any End Of Participant Reporting Message at all: every byte one the checker chooses */
static void any_end_of_participant_reporting_message(EndOfParticipantReportingMessage *record) {
  for (size_t i = 0; i < 2; i++) { record->orig[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->timestamp_1[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->feed_sequence[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->part_token[i] = arbitrary(); }
}

/* End Of Participant Reporting Message to the wire: 26 bytes from at, returning where the next byte goes */
static size_t encode_end_of_participant_reporting_message(const EndOfParticipantReportingMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->orig[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp_1[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->feed_sequence[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->part_token[i]; }

  return at;
}

/* End Of Participant Reporting Message off the wire: 26 bytes from at, returning where the next byte lies */
static size_t decode_end_of_participant_reporting_message(EndOfParticipantReportingMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->orig[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->timestamp_1[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->feed_sequence[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->part_token[i] = wire[at++]; }

  return at;
}

/* what was read of End Of Participant Reporting Message is what was written, byte for byte */
static void equal_end_of_participant_reporting_message(const EndOfParticipantReportingMessage *read, const EndOfParticipantReportingMessage *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->orig[i] == written->orig[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp_1[i] == written->timestamp_1[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->feed_sequence[i] == written->feed_sequence[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->part_token[i] == written->part_token[i]); }
}

/* End Of Participant Reporting Message: written and read back, then read and written back */
static void check_end_of_participant_reporting_message(void) {
  EndOfParticipantReportingMessage sent;
  EndOfParticipantReportingMessage got;
  uint8_t wire[26];
  uint8_t again[26];

  any_end_of_participant_reporting_message(&sent);
  assert(encode_end_of_participant_reporting_message(&sent, wire, 0) == 26);
  assert(decode_end_of_participant_reporting_message(&got, wire, 0) == 26);
  equal_end_of_participant_reporting_message(&got, &sent);

  for (size_t i = 0; i < 26; i++) { wire[i] = arbitrary(); }
  assert(decode_end_of_participant_reporting_message(&got, wire, 0) == 26);
  assert(encode_end_of_participant_reporting_message(&got, again, 0) == 26);
  for (size_t i = 0; i < 26; i++) { assert(again[i] == wire[i]); }
}

/* ---- Return Market Center Trading Action Acknowledgement Message: 30 bytes ---- */

/* Market Center Trading Action Acknowledgement Message (aJ). Acknowledges a Market Center Trading Action (AJ). */
typedef struct {
  uint8_t orig[2];          /* bytes 0 to 1 */
  uint8_t sip_time[8];      /* bytes 2 to 9 */
  uint8_t symbol_long[11];  /* bytes 10 to 20 */
  uint8_t action;           /* byte 21 */
  uint8_t action_time[8];   /* bytes 22 to 29 */
} ReturnMarketCenterTradingActionAcknowledgementMessage;

/* any Return Market Center Trading Action Acknowledgement Message at all: every byte one the checker chooses */
static void any_return_market_center_trading_action_acknowledgement_message(ReturnMarketCenterTradingActionAcknowledgementMessage *record) {
  for (size_t i = 0; i < 2; i++) { record->orig[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->sip_time[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->symbol_long[i] = arbitrary(); }
  record->action = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->action_time[i] = arbitrary(); }
}

/* Return Market Center Trading Action Acknowledgement Message to the wire: 30 bytes from at, returning where the next byte goes */
static size_t encode_return_market_center_trading_action_acknowledgement_message(const ReturnMarketCenterTradingActionAcknowledgementMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->orig[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->sip_time[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->symbol_long[i]; }
  wire[at++] = record->action;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->action_time[i]; }

  return at;
}

/* Return Market Center Trading Action Acknowledgement Message off the wire: 30 bytes from at, returning where the next byte lies */
static size_t decode_return_market_center_trading_action_acknowledgement_message(ReturnMarketCenterTradingActionAcknowledgementMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->orig[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->sip_time[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->symbol_long[i] = wire[at++]; }
  record->action = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->action_time[i] = wire[at++]; }

  return at;
}

/* what was read of Return Market Center Trading Action Acknowledgement Message is what was written, byte for byte */
static void equal_return_market_center_trading_action_acknowledgement_message(const ReturnMarketCenterTradingActionAcknowledgementMessage *read, const ReturnMarketCenterTradingActionAcknowledgementMessage *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->orig[i] == written->orig[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->sip_time[i] == written->sip_time[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->symbol_long[i] == written->symbol_long[i]); }
  assert(read->action == written->action);
  for (size_t i = 0; i < 8; i++) { assert(read->action_time[i] == written->action_time[i]); }
}

/* Return Market Center Trading Action Acknowledgement Message: written and read back, then read and written back */
static void check_return_market_center_trading_action_acknowledgement_message(void) {
  ReturnMarketCenterTradingActionAcknowledgementMessage sent;
  ReturnMarketCenterTradingActionAcknowledgementMessage got;
  uint8_t wire[30];
  uint8_t again[30];

  any_return_market_center_trading_action_acknowledgement_message(&sent);
  assert(encode_return_market_center_trading_action_acknowledgement_message(&sent, wire, 0) == 30);
  assert(decode_return_market_center_trading_action_acknowledgement_message(&got, wire, 0) == 30);
  equal_return_market_center_trading_action_acknowledgement_message(&got, &sent);

  for (size_t i = 0; i < 30; i++) { wire[i] = arbitrary(); }
  assert(decode_return_market_center_trading_action_acknowledgement_message(&got, wire, 0) == 30);
  assert(encode_return_market_center_trading_action_acknowledgement_message(&got, again, 0) == 30);
  for (size_t i = 0; i < 30; i++) { assert(again[i] == wire[i]); }
}

/* ---- Return Market Open Message: 10 bytes ------------------------------------ */

/* Return Market Open Message (aX). SIP confirms market is open. */
typedef struct {
  uint8_t orig[2];      /* bytes 0 to 1 */
  uint8_t sip_time[8];  /* bytes 2 to 9 */
} ReturnMarketOpenMessage;

/* any Return Market Open Message at all: every byte one the checker chooses */
static void any_return_market_open_message(ReturnMarketOpenMessage *record) {
  for (size_t i = 0; i < 2; i++) { record->orig[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->sip_time[i] = arbitrary(); }
}

/* Return Market Open Message to the wire: 10 bytes from at, returning where the next byte goes */
static size_t encode_return_market_open_message(const ReturnMarketOpenMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->orig[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->sip_time[i]; }

  return at;
}

/* Return Market Open Message off the wire: 10 bytes from at, returning where the next byte lies */
static size_t decode_return_market_open_message(ReturnMarketOpenMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->orig[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->sip_time[i] = wire[at++]; }

  return at;
}

/* what was read of Return Market Open Message is what was written, byte for byte */
static void equal_return_market_open_message(const ReturnMarketOpenMessage *read, const ReturnMarketOpenMessage *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->orig[i] == written->orig[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->sip_time[i] == written->sip_time[i]); }
}

/* Return Market Open Message: written and read back, then read and written back */
static void check_return_market_open_message(void) {
  ReturnMarketOpenMessage sent;
  ReturnMarketOpenMessage got;
  uint8_t wire[10];
  uint8_t again[10];

  any_return_market_open_message(&sent);
  assert(encode_return_market_open_message(&sent, wire, 0) == 10);
  assert(decode_return_market_open_message(&got, wire, 0) == 10);
  equal_return_market_open_message(&got, &sent);

  for (size_t i = 0; i < 10; i++) { wire[i] = arbitrary(); }
  assert(decode_return_market_open_message(&got, wire, 0) == 10);
  assert(encode_return_market_open_message(&got, again, 0) == 10);
  for (size_t i = 0; i < 10; i++) { assert(again[i] == wire[i]); }
}

/* ---- Return Market Closed Message: 10 bytes ---------------------------------- */

/* Return Market Closed Message (aY). SIP confirms market is closed. */
typedef struct {
  uint8_t orig[2];      /* bytes 0 to 1 */
  uint8_t sip_time[8];  /* bytes 2 to 9 */
} ReturnMarketClosedMessage;

/* any Return Market Closed Message at all: every byte one the checker chooses */
static void any_return_market_closed_message(ReturnMarketClosedMessage *record) {
  for (size_t i = 0; i < 2; i++) { record->orig[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->sip_time[i] = arbitrary(); }
}

/* Return Market Closed Message to the wire: 10 bytes from at, returning where the next byte goes */
static size_t encode_return_market_closed_message(const ReturnMarketClosedMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->orig[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->sip_time[i]; }

  return at;
}

/* Return Market Closed Message off the wire: 10 bytes from at, returning where the next byte lies */
static size_t decode_return_market_closed_message(ReturnMarketClosedMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->orig[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->sip_time[i] = wire[at++]; }

  return at;
}

/* what was read of Return Market Closed Message is what was written, byte for byte */
static void equal_return_market_closed_message(const ReturnMarketClosedMessage *read, const ReturnMarketClosedMessage *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->orig[i] == written->orig[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->sip_time[i] == written->sip_time[i]); }
}

/* Return Market Closed Message: written and read back, then read and written back */
static void check_return_market_closed_message(void) {
  ReturnMarketClosedMessage sent;
  ReturnMarketClosedMessage got;
  uint8_t wire[10];
  uint8_t again[10];

  any_return_market_closed_message(&sent);
  assert(encode_return_market_closed_message(&sent, wire, 0) == 10);
  assert(decode_return_market_closed_message(&got, wire, 0) == 10);
  equal_return_market_closed_message(&got, &sent);

  for (size_t i = 0; i < 10; i++) { wire[i] = arbitrary(); }
  assert(decode_return_market_closed_message(&got, wire, 0) == 10);
  assert(encode_return_market_closed_message(&got, again, 0) == 10);
  for (size_t i = 0; i < 10; i++) { assert(again[i] == wire[i]); }
}

/* ---- Reject Message: 29 bytes ------------------------------------------------ */

/* Reject Message (aR). SIP returns this message when an inbound message is rejected. syntaxViolation 'Y' indicates a syntax error and the port will be disconnected. */
typedef struct {
  uint8_t orig[2];           /* bytes 0 to 1 */
  uint8_t sip_time[8];       /* bytes 2 to 9 */
  uint8_t feed_sequence[8];  /* bytes 10 to 17 */
  uint8_t part_token[8];     /* bytes 18 to 25 */
  uint8_t reject_code[2];    /* bytes 26 to 27 */
  uint8_t syntax_violation;  /* byte 28 */
} RejectMessage;

/* any Reject Message at all: every byte one the checker chooses */
static void any_reject_message(RejectMessage *record) {
  for (size_t i = 0; i < 2; i++) { record->orig[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->sip_time[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->feed_sequence[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->part_token[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->reject_code[i] = arbitrary(); }
  record->syntax_violation = arbitrary();
}

/* Reject Message to the wire: 29 bytes from at, returning where the next byte goes */
static size_t encode_reject_message(const RejectMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->orig[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->sip_time[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->feed_sequence[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->part_token[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->reject_code[i]; }
  wire[at++] = record->syntax_violation;

  return at;
}

/* Reject Message off the wire: 29 bytes from at, returning where the next byte lies */
static size_t decode_reject_message(RejectMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->orig[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->sip_time[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->feed_sequence[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->part_token[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->reject_code[i] = wire[at++]; }
  record->syntax_violation = wire[at++];

  return at;
}

/* what was read of Reject Message is what was written, byte for byte */
static void equal_reject_message(const RejectMessage *read, const RejectMessage *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->orig[i] == written->orig[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->sip_time[i] == written->sip_time[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->feed_sequence[i] == written->feed_sequence[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->part_token[i] == written->part_token[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->reject_code[i] == written->reject_code[i]); }
  assert(read->syntax_violation == written->syntax_violation);
}

/* Reject Message: written and read back, then read and written back */
static void check_reject_message(void) {
  RejectMessage sent;
  RejectMessage got;
  uint8_t wire[29];
  uint8_t again[29];

  any_reject_message(&sent);
  assert(encode_reject_message(&sent, wire, 0) == 29);
  assert(decode_reject_message(&got, wire, 0) == 29);
  equal_reject_message(&got, &sent);

  for (size_t i = 0; i < 29; i++) { wire[i] = arbitrary(); }
  assert(decode_reject_message(&got, wire, 0) == 29);
  assert(encode_reject_message(&got, again, 0) == 29);
  for (size_t i = 0; i < 29; i++) { assert(again[i] == wire[i]); }
}

/* ---- Sequence Acknowledgement Message: 26 bytes ------------------------------ */

/* Sequence Acknowledgement Message (aK). SIP positively acknowledges receipt of an inbound message when the port is configured for acknowledgements. */
typedef struct {
  uint8_t orig[2];           /* bytes 0 to 1 */
  uint8_t sip_time[8];       /* bytes 2 to 9 */
  uint8_t feed_sequence[8];  /* bytes 10 to 17 */
  uint8_t part_token[8];     /* bytes 18 to 25 */
} SequenceAcknowledgementMessage;

/* any Sequence Acknowledgement Message at all: every byte one the checker chooses */
static void any_sequence_acknowledgement_message(SequenceAcknowledgementMessage *record) {
  for (size_t i = 0; i < 2; i++) { record->orig[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->sip_time[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->feed_sequence[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->part_token[i] = arbitrary(); }
}

/* Sequence Acknowledgement Message to the wire: 26 bytes from at, returning where the next byte goes */
static size_t encode_sequence_acknowledgement_message(const SequenceAcknowledgementMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->orig[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->sip_time[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->feed_sequence[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->part_token[i]; }

  return at;
}

/* Sequence Acknowledgement Message off the wire: 26 bytes from at, returning where the next byte lies */
static size_t decode_sequence_acknowledgement_message(SequenceAcknowledgementMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->orig[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->sip_time[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->feed_sequence[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->part_token[i] = wire[at++]; }

  return at;
}

/* what was read of Sequence Acknowledgement Message is what was written, byte for byte */
static void equal_sequence_acknowledgement_message(const SequenceAcknowledgementMessage *read, const SequenceAcknowledgementMessage *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->orig[i] == written->orig[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->sip_time[i] == written->sip_time[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->feed_sequence[i] == written->feed_sequence[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->part_token[i] == written->part_token[i]); }
}

/* Sequence Acknowledgement Message: written and read back, then read and written back */
static void check_sequence_acknowledgement_message(void) {
  SequenceAcknowledgementMessage sent;
  SequenceAcknowledgementMessage got;
  uint8_t wire[26];
  uint8_t again[26];

  any_sequence_acknowledgement_message(&sent);
  assert(encode_sequence_acknowledgement_message(&sent, wire, 0) == 26);
  assert(decode_sequence_acknowledgement_message(&got, wire, 0) == 26);
  equal_sequence_acknowledgement_message(&got, &sent);

  for (size_t i = 0; i < 26; i++) { wire[i] = arbitrary(); }
  assert(decode_sequence_acknowledgement_message(&got, wire, 0) == 26);
  assert(encode_sequence_acknowledgement_message(&got, again, 0) == 26);
  for (size_t i = 0; i < 26; i++) { assert(again[i] == wire[i]); }
}

/* ---- Participant Input Warning Message: 42 bytes ----------------------------- */

/* Participant Input Warning Message (aW). Sent when an inbound quote message would exceed odd-lot price-level limits. Carries the unprocessed price levels as attachments whose form is selected by olAttachmenType (2=Short, 3=Long, 5=ADF MPID). The attached price levels are not enumerated as Pdf.xml groups in this version — extend in a follow-up release when the loader's value-gated Optional rules are wired through Edits.xml. */
typedef struct {
  uint8_t orig[2];                 /* bytes 0 to 1 */
  uint8_t sip_time[8];             /* bytes 2 to 9 */
  uint8_t feed_sequence[8];        /* bytes 10 to 17 */
  uint8_t part_token[8];           /* bytes 18 to 25 */
  uint8_t warning_code[2];         /* bytes 26 to 27 */
  uint8_t symbol_long[11];         /* bytes 28 to 38 */
  uint8_t ol_attachmen_type;       /* byte 39 */
  uint8_t ol_attachment_count[2];  /* bytes 40 to 41 */
} ParticipantInputWarningMessage;

/* any Participant Input Warning Message at all: every byte one the checker chooses */
static void any_participant_input_warning_message(ParticipantInputWarningMessage *record) {
  for (size_t i = 0; i < 2; i++) { record->orig[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->sip_time[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->feed_sequence[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->part_token[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->warning_code[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->symbol_long[i] = arbitrary(); }
  record->ol_attachmen_type = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->ol_attachment_count[i] = arbitrary(); }
}

/* Participant Input Warning Message to the wire: 42 bytes from at, returning where the next byte goes */
static size_t encode_participant_input_warning_message(const ParticipantInputWarningMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->orig[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->sip_time[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->feed_sequence[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->part_token[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->warning_code[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->symbol_long[i]; }
  wire[at++] = record->ol_attachmen_type;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->ol_attachment_count[i]; }

  return at;
}

/* Participant Input Warning Message off the wire: 42 bytes from at, returning where the next byte lies */
static size_t decode_participant_input_warning_message(ParticipantInputWarningMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->orig[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->sip_time[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->feed_sequence[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->part_token[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->warning_code[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->symbol_long[i] = wire[at++]; }
  record->ol_attachmen_type = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->ol_attachment_count[i] = wire[at++]; }

  return at;
}

/* what was read of Participant Input Warning Message is what was written, byte for byte */
static void equal_participant_input_warning_message(const ParticipantInputWarningMessage *read, const ParticipantInputWarningMessage *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->orig[i] == written->orig[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->sip_time[i] == written->sip_time[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->feed_sequence[i] == written->feed_sequence[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->part_token[i] == written->part_token[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->warning_code[i] == written->warning_code[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->symbol_long[i] == written->symbol_long[i]); }
  assert(read->ol_attachmen_type == written->ol_attachmen_type);
  for (size_t i = 0; i < 2; i++) { assert(read->ol_attachment_count[i] == written->ol_attachment_count[i]); }
}

/* Participant Input Warning Message: written and read back, then read and written back */
static void check_participant_input_warning_message(void) {
  ParticipantInputWarningMessage sent;
  ParticipantInputWarningMessage got;
  uint8_t wire[42];
  uint8_t again[42];

  any_participant_input_warning_message(&sent);
  assert(encode_participant_input_warning_message(&sent, wire, 0) == 42);
  assert(decode_participant_input_warning_message(&got, wire, 0) == 42);
  equal_participant_input_warning_message(&got, &sent);

  for (size_t i = 0; i < 42; i++) { wire[i] = arbitrary(); }
  assert(decode_participant_input_warning_message(&got, wire, 0) == 42);
  assert(encode_participant_input_warning_message(&got, again, 0) == 42);
  for (size_t i = 0; i < 42; i++) { assert(again[i] == wire[i]); }
}

/* ---- Start Of Day Message: 10 bytes ------------------------------------------ */

/* Start Of Day Message (cE). SIP signals it is open and ready to receive messages from participants. */
typedef struct {
  uint8_t orig[2];      /* bytes 0 to 1 */
  uint8_t sip_time[8];  /* bytes 2 to 9 */
} StartOfDayMessage;

/* any Start Of Day Message at all: every byte one the checker chooses */
static void any_start_of_day_message(StartOfDayMessage *record) {
  for (size_t i = 0; i < 2; i++) { record->orig[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->sip_time[i] = arbitrary(); }
}

/* Start Of Day Message to the wire: 10 bytes from at, returning where the next byte goes */
static size_t encode_start_of_day_message(const StartOfDayMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->orig[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->sip_time[i]; }

  return at;
}

/* Start Of Day Message off the wire: 10 bytes from at, returning where the next byte lies */
static size_t decode_start_of_day_message(StartOfDayMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->orig[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->sip_time[i] = wire[at++]; }

  return at;
}

/* what was read of Start Of Day Message is what was written, byte for byte */
static void equal_start_of_day_message(const StartOfDayMessage *read, const StartOfDayMessage *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->orig[i] == written->orig[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->sip_time[i] == written->sip_time[i]); }
}

/* Start Of Day Message: written and read back, then read and written back */
static void check_start_of_day_message(void) {
  StartOfDayMessage sent;
  StartOfDayMessage got;
  uint8_t wire[10];
  uint8_t again[10];

  any_start_of_day_message(&sent);
  assert(encode_start_of_day_message(&sent, wire, 0) == 10);
  assert(decode_start_of_day_message(&got, wire, 0) == 10);
  equal_start_of_day_message(&got, &sent);

  for (size_t i = 0; i < 10; i++) { wire[i] = arbitrary(); }
  assert(decode_start_of_day_message(&got, wire, 0) == 10);
  assert(encode_start_of_day_message(&got, again, 0) == 10);
  for (size_t i = 0; i < 10; i++) { assert(again[i] == wire[i]); }
}

/* ---- End Of Day Message: 10 bytes -------------------------------------------- */

/* End Of Day Message (cF). SIP signals it has no further data or control messages for the day and is shutting down. */
typedef struct {
  uint8_t orig[2];      /* bytes 0 to 1 */
  uint8_t sip_time[8];  /* bytes 2 to 9 */
} EndOfDayMessage;

/* any End Of Day Message at all: every byte one the checker chooses */
static void any_end_of_day_message(EndOfDayMessage *record) {
  for (size_t i = 0; i < 2; i++) { record->orig[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->sip_time[i] = arbitrary(); }
}

/* End Of Day Message to the wire: 10 bytes from at, returning where the next byte goes */
static size_t encode_end_of_day_message(const EndOfDayMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->orig[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->sip_time[i]; }

  return at;
}

/* End Of Day Message off the wire: 10 bytes from at, returning where the next byte lies */
static size_t decode_end_of_day_message(EndOfDayMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->orig[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->sip_time[i] = wire[at++]; }

  return at;
}

/* what was read of End Of Day Message is what was written, byte for byte */
static void equal_end_of_day_message(const EndOfDayMessage *read, const EndOfDayMessage *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->orig[i] == written->orig[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->sip_time[i] == written->sip_time[i]); }
}

/* End Of Day Message: written and read back, then read and written back */
static void check_end_of_day_message(void) {
  EndOfDayMessage sent;
  EndOfDayMessage got;
  uint8_t wire[10];
  uint8_t again[10];

  any_end_of_day_message(&sent);
  assert(encode_end_of_day_message(&sent, wire, 0) == 10);
  assert(decode_end_of_day_message(&got, wire, 0) == 10);
  equal_end_of_day_message(&got, &sent);

  for (size_t i = 0; i < 10; i++) { wire[i] = arbitrary(); }
  assert(decode_end_of_day_message(&got, wire, 0) == 10);
  assert(encode_end_of_day_message(&got, again, 0) == 10);
  for (size_t i = 0; i < 10; i++) { assert(again[i] == wire[i]); }
}

/* ---- Sequence Inquiry Response Message: 27 bytes ----------------------------- */

/* Sequence Inquiry Response Message (cC). Sent unsequenced in response to a CC inquiry. Carries the next expected feedSequence, last partToken received, and the present SIP state. */
typedef struct {
  uint8_t orig[2];           /* bytes 0 to 1 */
  uint8_t sip_time[8];       /* bytes 2 to 9 */
  uint8_t feed_sequence[8];  /* bytes 10 to 17 */
  uint8_t part_token[8];     /* bytes 18 to 25 */
  uint8_t sip_state;         /* byte 26 */
} SequenceInquiryResponseMessage;

/* any Sequence Inquiry Response Message at all: every byte one the checker chooses */
static void any_sequence_inquiry_response_message(SequenceInquiryResponseMessage *record) {
  for (size_t i = 0; i < 2; i++) { record->orig[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->sip_time[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->feed_sequence[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->part_token[i] = arbitrary(); }
  record->sip_state = arbitrary();
}

/* Sequence Inquiry Response Message to the wire: 27 bytes from at, returning where the next byte goes */
static size_t encode_sequence_inquiry_response_message(const SequenceInquiryResponseMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->orig[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->sip_time[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->feed_sequence[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->part_token[i]; }
  wire[at++] = record->sip_state;

  return at;
}

/* Sequence Inquiry Response Message off the wire: 27 bytes from at, returning where the next byte lies */
static size_t decode_sequence_inquiry_response_message(SequenceInquiryResponseMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->orig[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->sip_time[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->feed_sequence[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->part_token[i] = wire[at++]; }
  record->sip_state = wire[at++];

  return at;
}

/* what was read of Sequence Inquiry Response Message is what was written, byte for byte */
static void equal_sequence_inquiry_response_message(const SequenceInquiryResponseMessage *read, const SequenceInquiryResponseMessage *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->orig[i] == written->orig[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->sip_time[i] == written->sip_time[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->feed_sequence[i] == written->feed_sequence[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->part_token[i] == written->part_token[i]); }
  assert(read->sip_state == written->sip_state);
}

/* Sequence Inquiry Response Message: written and read back, then read and written back */
static void check_sequence_inquiry_response_message(void) {
  SequenceInquiryResponseMessage sent;
  SequenceInquiryResponseMessage got;
  uint8_t wire[27];
  uint8_t again[27];

  any_sequence_inquiry_response_message(&sent);
  assert(encode_sequence_inquiry_response_message(&sent, wire, 0) == 27);
  assert(decode_sequence_inquiry_response_message(&got, wire, 0) == 27);
  equal_sequence_inquiry_response_message(&got, &sent);

  for (size_t i = 0; i < 27; i++) { wire[i] = arbitrary(); }
  assert(decode_sequence_inquiry_response_message(&got, wire, 0) == 27);
  assert(encode_sequence_inquiry_response_message(&got, again, 0) == 27);
  for (size_t i = 0; i < 27; i++) { assert(again[i] == wire[i]); }
}

/* ---- Symbol State Inquiry Response Message: 30 bytes ------------------------- */

/* Symbol State Inquiry Response Message (cS). Sent unsequenced in response to a CS inquiry. Carries next expected tradeId, next actionSequence, and the symbolState. */
typedef struct {
  uint8_t orig[2];                  /* bytes 0 to 1 */
  uint8_t sip_time[8];              /* bytes 2 to 9 */
  uint8_t symbol_long[11];          /* bytes 10 to 20 */
  uint8_t next_trade_id[4];         /* bytes 21 to 24 */
  uint8_t next_action_sequence[4];  /* bytes 25 to 28 */
  uint8_t symbol_state;             /* byte 29 */
} SymbolStateInquiryResponseMessage;

/* any Symbol State Inquiry Response Message at all: every byte one the checker chooses */
static void any_symbol_state_inquiry_response_message(SymbolStateInquiryResponseMessage *record) {
  for (size_t i = 0; i < 2; i++) { record->orig[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->sip_time[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->symbol_long[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->next_trade_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->next_action_sequence[i] = arbitrary(); }
  record->symbol_state = arbitrary();
}

/* Symbol State Inquiry Response Message to the wire: 30 bytes from at, returning where the next byte goes */
static size_t encode_symbol_state_inquiry_response_message(const SymbolStateInquiryResponseMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->orig[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->sip_time[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->symbol_long[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->next_trade_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->next_action_sequence[i]; }
  wire[at++] = record->symbol_state;

  return at;
}

/* Symbol State Inquiry Response Message off the wire: 30 bytes from at, returning where the next byte lies */
static size_t decode_symbol_state_inquiry_response_message(SymbolStateInquiryResponseMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->orig[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->sip_time[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->symbol_long[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->next_trade_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->next_action_sequence[i] = wire[at++]; }
  record->symbol_state = wire[at++];

  return at;
}

/* what was read of Symbol State Inquiry Response Message is what was written, byte for byte */
static void equal_symbol_state_inquiry_response_message(const SymbolStateInquiryResponseMessage *read, const SymbolStateInquiryResponseMessage *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->orig[i] == written->orig[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->sip_time[i] == written->sip_time[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->symbol_long[i] == written->symbol_long[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->next_trade_id[i] == written->next_trade_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->next_action_sequence[i] == written->next_action_sequence[i]); }
  assert(read->symbol_state == written->symbol_state);
}

/* Symbol State Inquiry Response Message: written and read back, then read and written back */
static void check_symbol_state_inquiry_response_message(void) {
  SymbolStateInquiryResponseMessage sent;
  SymbolStateInquiryResponseMessage got;
  uint8_t wire[30];
  uint8_t again[30];

  any_symbol_state_inquiry_response_message(&sent);
  assert(encode_symbol_state_inquiry_response_message(&sent, wire, 0) == 30);
  assert(decode_symbol_state_inquiry_response_message(&got, wire, 0) == 30);
  equal_symbol_state_inquiry_response_message(&got, &sent);

  for (size_t i = 0; i < 30; i++) { wire[i] = arbitrary(); }
  assert(decode_symbol_state_inquiry_response_message(&got, wire, 0) == 30);
  assert(encode_symbol_state_inquiry_response_message(&got, again, 0) == 30);
  for (size_t i = 0; i < 30; i++) { assert(again[i] == wire[i]); }
}

/* ---- Login Accepted Packet: 30 bytes ----------------------------------------- */

/* SoupBinTCP Login Accepted Packet */
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

/* SoupBinTCP Login Rejected Packet */
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

/* ---- What esbmc checks ------------------------------------------------------- */

/* every record of the protocol, each on its own buffers */
static void checks(void) {
  check_server_tcp_packet_header();
  check_message_header();
  check_protected_exchange_quote_message_short_form_message();
  check_protected_exchange_quote_message_long_form_message();
  check_finra_protected_quote_message_with_bbo_info_message();
  check_finra_protected_quote_message_without_bbo_info_message();
  check_regular_trade_report_message();
  check_trade_cancel_error_message();
  check_trade_correction_message();
  check_as_of_trade_report_message();
  check_fractional_regular_trade_report_message();
  check_fractional_trade_cancel_error_message();
  check_fractional_trade_correction_message();
  check_fractional_as_of_trade_report_message();
  check_trading_action_message();
  check_market_center_trading_action_message();
  check_market_center_mass_trading_action_message();
  check_reg_sho_short_sale_price_test_restricted_indicator_message();
  check_opening_reference_midpoint_price_message();
  check_t1_adjusted_closing_price_message();
  check_market_open_message();
  check_market_closed_message();
  check_auction_collar_message();
  check_sequence_inquiry_message();
  check_symbol_state_inquiry_message();
  check_end_of_participant_reporting_message();
  check_return_market_center_trading_action_acknowledgement_message();
  check_return_market_open_message();
  check_return_market_closed_message();
  check_reject_message();
  check_sequence_acknowledgement_message();
  check_participant_input_warning_message();
  check_start_of_day_message();
  check_end_of_day_message();
  check_sequence_inquiry_response_message();
  check_symbol_state_inquiry_response_message();
  check_login_accepted_packet();
  check_login_rejected_packet();
}

int main(void) {
#ifdef CONCRETE
  for (pattern = 0; pattern < 4; pattern++) { checks(); }
#else
  checks();
#endif

  return 0;
}
