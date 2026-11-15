// nse/nsecm/dropcopy/NseCm_DropCopy_v3_0_Server.c
/*
 * National Stock Exchange of India Ltd Drop Copy
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
 *   - a Composite rule
 *   - a field read in bits
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

/* ---- Packet Header: 22 bytes ------------------------------------------------- */

/* Drop copy twenty two byte packet header */
typedef struct {
  uint8_t packet_length[2];           /* bytes 0 to 1 */
  uint8_t packet_sequence_number[4];  /* bytes 2 to 5 */
  uint8_t checksum[16];               /* bytes 6 to 21 */
} PacketHeader;

/* any Packet Header at all: every byte one the checker chooses */
static void any_packet_header(PacketHeader *record) {
  for (size_t i = 0; i < 2; i++) { record->packet_length[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->packet_sequence_number[i] = arbitrary(); }
  for (size_t i = 0; i < 16; i++) { record->checksum[i] = arbitrary(); }
}

/* Packet Header to the wire: 22 bytes from at, returning where the next byte goes */
static size_t encode_packet_header(const PacketHeader *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->packet_length[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->packet_sequence_number[i]; }
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->checksum[i]; }

  return at;
}

/* Packet Header off the wire: 22 bytes from at, returning where the next byte lies */
static size_t decode_packet_header(PacketHeader *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->packet_length[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->packet_sequence_number[i] = wire[at++]; }
  for (size_t i = 0; i < 16; i++) { record->checksum[i] = wire[at++]; }

  return at;
}

/* what was read of Packet Header is what was written, byte for byte */
static void equal_packet_header(const PacketHeader *read, const PacketHeader *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->packet_length[i] == written->packet_length[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->packet_sequence_number[i] == written->packet_sequence_number[i]); }
  for (size_t i = 0; i < 16; i++) { assert(read->checksum[i] == written->checksum[i]); }
}

/* Packet Header: written and read back, then read and written back */
static void check_packet_header(void) {
  PacketHeader sent;
  PacketHeader got;
  uint8_t wire[22];
  uint8_t again[22];

  any_packet_header(&sent);
  assert(encode_packet_header(&sent, wire, 0) == 22);
  assert(decode_packet_header(&got, wire, 0) == 22);
  equal_packet_header(&got, &sent);

  for (size_t i = 0; i < 22; i++) { wire[i] = arbitrary(); }
  assert(decode_packet_header(&got, wire, 0) == 22);
  assert(encode_packet_header(&got, again, 0) == 22);
  for (size_t i = 0; i < 22; i++) { assert(again[i] == wire[i]); }
}

/* ---- Response Message Header: 2 bytes ---------------------------------------- */

/* RESPONSE_MESSAGE_HEADER, present once per packet however many messages are packed behind it */
typedef struct {
  uint8_t environment_type;       /* byte 0 */
  uint8_t compression_indicator;  /* byte 1 */
} ResponseMessageHeader;

/* any Response Message Header at all: every byte one the checker chooses */
static void any_response_message_header(ResponseMessageHeader *record) {
  record->environment_type = arbitrary();
  record->compression_indicator = arbitrary();
}

/* Response Message Header to the wire: 2 bytes from at, returning where the next byte goes */
static size_t encode_response_message_header(const ResponseMessageHeader *record, uint8_t *wire, size_t at) {
  wire[at++] = record->environment_type;
  wire[at++] = record->compression_indicator;

  return at;
}

/* Response Message Header off the wire: 2 bytes from at, returning where the next byte lies */
static size_t decode_response_message_header(ResponseMessageHeader *record, const uint8_t *wire, size_t at) {
  record->environment_type = wire[at++];
  record->compression_indicator = wire[at++];

  return at;
}

/* what was read of Response Message Header is what was written, byte for byte */
static void equal_response_message_header(const ResponseMessageHeader *read, const ResponseMessageHeader *written) {
  assert(read->environment_type == written->environment_type);
  assert(read->compression_indicator == written->compression_indicator);
}

/* Response Message Header: written and read back, then read and written back */
static void check_response_message_header(void) {
  ResponseMessageHeader sent;
  ResponseMessageHeader got;
  uint8_t wire[2];
  uint8_t again[2];

  any_response_message_header(&sent);
  assert(encode_response_message_header(&sent, wire, 0) == 2);
  assert(decode_response_message_header(&got, wire, 0) == 2);
  equal_response_message_header(&got, &sent);

  for (size_t i = 0; i < 2; i++) { wire[i] = arbitrary(); }
  assert(decode_response_message_header(&got, wire, 0) == 2);
  assert(encode_response_message_header(&got, again, 0) == 2);
  for (size_t i = 0; i < 2; i++) { assert(again[i] == wire[i]); }
}

/* ---- Message Header: 14 bytes ------------------------------------------------ */

/* MESSAGE_HEADER */
typedef struct {
  uint8_t transaction_code[2];  /* bytes 0 to 1 */
  uint8_t error_code[2];        /* bytes 2 to 3 */
  uint8_t sequence_number[8];   /* bytes 4 to 11 */
  uint8_t message_length[2];    /* bytes 12 to 13 */
} MessageHeader;

/* any Message Header at all: every byte one the checker chooses */
static void any_message_header(MessageHeader *record) {
  for (size_t i = 0; i < 2; i++) { record->transaction_code[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->error_code[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->sequence_number[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->message_length[i] = arbitrary(); }
}

/* Message Header to the wire: 14 bytes from at, returning where the next byte goes */
static size_t encode_message_header(const MessageHeader *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->transaction_code[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->error_code[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->sequence_number[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->message_length[i]; }

  return at;
}

/* Message Header off the wire: 14 bytes from at, returning where the next byte lies */
static size_t decode_message_header(MessageHeader *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->transaction_code[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->error_code[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->sequence_number[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->message_length[i] = wire[at++]; }

  return at;
}

/* what was read of Message Header is what was written, byte for byte */
static void equal_message_header(const MessageHeader *read, const MessageHeader *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->transaction_code[i] == written->transaction_code[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->error_code[i] == written->error_code[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->sequence_number[i] == written->sequence_number[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->message_length[i] == written->message_length[i]); }
}

/* Message Header: written and read back, then read and written back */
static void check_message_header(void) {
  MessageHeader sent;
  MessageHeader got;
  uint8_t wire[14];
  uint8_t again[14];

  any_message_header(&sent);
  assert(encode_message_header(&sent, wire, 0) == 14);
  assert(decode_message_header(&got, wire, 0) == 14);
  equal_message_header(&got, &sent);

  for (size_t i = 0; i < 14; i++) { wire[i] = arbitrary(); }
  assert(decode_message_header(&got, wire, 0) == 14);
  assert(encode_message_header(&got, again, 0) == 14);
  for (size_t i = 0; i < 14; i++) { assert(again[i] == wire[i]); }
}

/* ---- Ip Details Partition Wise: 26 bytes ------------------------------------- */

/* IP_DETAILS_PARTITION_WISE */
typedef struct {
  uint8_t ip_address[16];   /* bytes 0 to 15 */
  uint8_t port[4];          /* bytes 16 to 19 */
  uint8_t partition_id[6];  /* bytes 20 to 25 */
} IpDetailsPartitionWise;

/* any Ip Details Partition Wise at all: every byte one the checker chooses */
static void any_ip_details_partition_wise(IpDetailsPartitionWise *record) {
  for (size_t i = 0; i < 16; i++) { record->ip_address[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->port[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->partition_id[i] = arbitrary(); }
}

/* Ip Details Partition Wise to the wire: 26 bytes from at, returning where the next byte goes */
static size_t encode_ip_details_partition_wise(const IpDetailsPartitionWise *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->ip_address[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->port[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->partition_id[i]; }

  return at;
}

/* Ip Details Partition Wise off the wire: 26 bytes from at, returning where the next byte lies */
static size_t decode_ip_details_partition_wise(IpDetailsPartitionWise *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 16; i++) { record->ip_address[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->port[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->partition_id[i] = wire[at++]; }

  return at;
}

/* what was read of Ip Details Partition Wise is what was written, byte for byte */
static void equal_ip_details_partition_wise(const IpDetailsPartitionWise *read, const IpDetailsPartitionWise *written) {
  for (size_t i = 0; i < 16; i++) { assert(read->ip_address[i] == written->ip_address[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->port[i] == written->port[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->partition_id[i] == written->partition_id[i]); }
}

/* Ip Details Partition Wise: written and read back, then read and written back */
static void check_ip_details_partition_wise(void) {
  IpDetailsPartitionWise sent;
  IpDetailsPartitionWise got;
  uint8_t wire[26];
  uint8_t again[26];

  any_ip_details_partition_wise(&sent);
  assert(encode_ip_details_partition_wise(&sent, wire, 0) == 26);
  assert(decode_ip_details_partition_wise(&got, wire, 0) == 26);
  equal_ip_details_partition_wise(&got, &sent);

  for (size_t i = 0; i < 26; i++) { wire[i] = arbitrary(); }
  assert(decode_ip_details_partition_wise(&got, wire, 0) == 26);
  assert(encode_ip_details_partition_wise(&got, again, 0) == 26);
  for (size_t i = 0; i < 26; i++) { assert(again[i] == wire[i]); }
}

/* ---- Gr Response Message: 86 bytes ------------------------------------------- */

/* Returns the addresses of every partition the member must connect to, together with the session key and the cryptographic material for those connections */
typedef struct {
  uint8_t message_indicator[2];                      /* bytes 0 to 1 */
  uint8_t partition_count[2];                        /* bytes 2 to 3 */
  IpDetailsPartitionWise ip_details_partition_wise;  /* bytes 4 to 29 */
  uint8_t session_key[8];                            /* bytes 30 to 37 */
  uint8_t cryptographic_key[32];                     /* bytes 38 to 69 */
  uint8_t cryptographic_iv[16];                      /* bytes 70 to 85 */
} GrResponseMessage;

/* any Gr Response Message at all: every byte one the checker chooses */
static void any_gr_response_message(GrResponseMessage *record) {
  for (size_t i = 0; i < 2; i++) { record->message_indicator[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->partition_count[i] = arbitrary(); }
  any_ip_details_partition_wise(&record->ip_details_partition_wise);
  for (size_t i = 0; i < 8; i++) { record->session_key[i] = arbitrary(); }
  for (size_t i = 0; i < 32; i++) { record->cryptographic_key[i] = arbitrary(); }
  for (size_t i = 0; i < 16; i++) { record->cryptographic_iv[i] = arbitrary(); }
}

/* Gr Response Message to the wire: 86 bytes from at, returning where the next byte goes */
static size_t encode_gr_response_message(const GrResponseMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->message_indicator[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->partition_count[i]; }
  at = encode_ip_details_partition_wise(&record->ip_details_partition_wise, wire, at);
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->session_key[i]; }
  for (size_t i = 0; i < 32; i++) { wire[at++] = record->cryptographic_key[i]; }
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->cryptographic_iv[i]; }

  return at;
}

/* Gr Response Message off the wire: 86 bytes from at, returning where the next byte lies */
static size_t decode_gr_response_message(GrResponseMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->message_indicator[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->partition_count[i] = wire[at++]; }
  at = decode_ip_details_partition_wise(&record->ip_details_partition_wise, wire, at);
  for (size_t i = 0; i < 8; i++) { record->session_key[i] = wire[at++]; }
  for (size_t i = 0; i < 32; i++) { record->cryptographic_key[i] = wire[at++]; }
  for (size_t i = 0; i < 16; i++) { record->cryptographic_iv[i] = wire[at++]; }

  return at;
}

/* what was read of Gr Response Message is what was written, byte for byte */
static void equal_gr_response_message(const GrResponseMessage *read, const GrResponseMessage *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->message_indicator[i] == written->message_indicator[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->partition_count[i] == written->partition_count[i]); }
  equal_ip_details_partition_wise(&read->ip_details_partition_wise, &written->ip_details_partition_wise);
  for (size_t i = 0; i < 8; i++) { assert(read->session_key[i] == written->session_key[i]); }
  for (size_t i = 0; i < 32; i++) { assert(read->cryptographic_key[i] == written->cryptographic_key[i]); }
  for (size_t i = 0; i < 16; i++) { assert(read->cryptographic_iv[i] == written->cryptographic_iv[i]); }
}

/* Gr Response Message: written and read back, then read and written back */
static void check_gr_response_message(void) {
  GrResponseMessage sent;
  GrResponseMessage got;
  uint8_t wire[86];
  uint8_t again[86];

  any_gr_response_message(&sent);
  assert(encode_gr_response_message(&sent, wire, 0) == 86);
  assert(decode_gr_response_message(&got, wire, 0) == 86);
  equal_gr_response_message(&got, &sent);

  for (size_t i = 0; i < 86; i++) { wire[i] = arbitrary(); }
  assert(decode_gr_response_message(&got, wire, 0) == 86);
  assert(encode_gr_response_message(&got, again, 0) == 86);
  for (size_t i = 0; i < 86; i++) { assert(again[i] == wire[i]); }
}

/* ---- Dc Signon Out Message: 12 bytes ----------------------------------------- */

/* Confirms the logon, or terminates the connection when Error Code is set */
typedef struct {
  uint8_t user_id[4];              /* bytes 0 to 3 */
  uint8_t partition_id[6];         /* bytes 4 to 9 */
  uint8_t concurrent_login_id[2];  /* bytes 10 to 11 */
} DcSignonOutMessage;

/* any Dc Signon Out Message at all: every byte one the checker chooses */
static void any_dc_signon_out_message(DcSignonOutMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->user_id[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->partition_id[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->concurrent_login_id[i] = arbitrary(); }
}

/* Dc Signon Out Message to the wire: 12 bytes from at, returning where the next byte goes */
static size_t encode_dc_signon_out_message(const DcSignonOutMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->user_id[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->partition_id[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->concurrent_login_id[i]; }

  return at;
}

/* Dc Signon Out Message off the wire: 12 bytes from at, returning where the next byte lies */
static size_t decode_dc_signon_out_message(DcSignonOutMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->user_id[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->partition_id[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->concurrent_login_id[i] = wire[at++]; }

  return at;
}

/* what was read of Dc Signon Out Message is what was written, byte for byte */
static void equal_dc_signon_out_message(const DcSignonOutMessage *read, const DcSignonOutMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->user_id[i] == written->user_id[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->partition_id[i] == written->partition_id[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->concurrent_login_id[i] == written->concurrent_login_id[i]); }
}

/* Dc Signon Out Message: written and read back, then read and written back */
static void check_dc_signon_out_message(void) {
  DcSignonOutMessage sent;
  DcSignonOutMessage got;
  uint8_t wire[12];
  uint8_t again[12];

  any_dc_signon_out_message(&sent);
  assert(encode_dc_signon_out_message(&sent, wire, 0) == 12);
  assert(decode_dc_signon_out_message(&got, wire, 0) == 12);
  equal_dc_signon_out_message(&got, &sent);

  for (size_t i = 0; i < 12; i++) { wire[i] = arbitrary(); }
  assert(decode_dc_signon_out_message(&got, wire, 0) == 12);
  assert(encode_dc_signon_out_message(&got, again, 0) == 12);
  for (size_t i = 0; i < 12; i++) { assert(again[i] == wire[i]); }
}

/* ---- Dc Error Response Trade Message: 128 bytes ------------------------------ */

/* Rejects a trade only request, the reason given in the Error Code of the Message Header */
typedef struct {
  uint8_t error_message[128];  /* bytes 0 to 127 */
} DcErrorResponseTradeMessage;

/* any Dc Error Response Trade Message at all: every byte one the checker chooses */
static void any_dc_error_response_trade_message(DcErrorResponseTradeMessage *record) {
  for (size_t i = 0; i < 128; i++) { record->error_message[i] = arbitrary(); }
}

/* Dc Error Response Trade Message to the wire: 128 bytes from at, returning where the next byte goes */
static size_t encode_dc_error_response_trade_message(const DcErrorResponseTradeMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 128; i++) { wire[at++] = record->error_message[i]; }

  return at;
}

/* Dc Error Response Trade Message off the wire: 128 bytes from at, returning where the next byte lies */
static size_t decode_dc_error_response_trade_message(DcErrorResponseTradeMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 128; i++) { record->error_message[i] = wire[at++]; }

  return at;
}

/* what was read of Dc Error Response Trade Message is what was written, byte for byte */
static void equal_dc_error_response_trade_message(const DcErrorResponseTradeMessage *read, const DcErrorResponseTradeMessage *written) {
  for (size_t i = 0; i < 128; i++) { assert(read->error_message[i] == written->error_message[i]); }
}

/* Dc Error Response Trade Message: written and read back, then read and written back */
static void check_dc_error_response_trade_message(void) {
  DcErrorResponseTradeMessage sent;
  DcErrorResponseTradeMessage got;
  uint8_t wire[128];
  uint8_t again[128];

  any_dc_error_response_trade_message(&sent);
  assert(encode_dc_error_response_trade_message(&sent, wire, 0) == 128);
  assert(decode_dc_error_response_trade_message(&got, wire, 0) == 128);
  equal_dc_error_response_trade_message(&got, &sent);

  for (size_t i = 0; i < 128; i++) { wire[i] = arbitrary(); }
  assert(decode_dc_error_response_trade_message(&got, wire, 0) == 128);
  assert(encode_dc_error_response_trade_message(&got, again, 0) == 128);
  for (size_t i = 0; i < 128; i++) { assert(again[i] == wire[i]); }
}

/* ---- Dc Error Response Order Message: 128 bytes ------------------------------ */

/* Rejects an order and trade request, the reason given in the Error Code of the Message Header */
typedef struct {
  uint8_t error_message[128];  /* bytes 0 to 127 */
} DcErrorResponseOrderMessage;

/* any Dc Error Response Order Message at all: every byte one the checker chooses */
static void any_dc_error_response_order_message(DcErrorResponseOrderMessage *record) {
  for (size_t i = 0; i < 128; i++) { record->error_message[i] = arbitrary(); }
}

/* Dc Error Response Order Message to the wire: 128 bytes from at, returning where the next byte goes */
static size_t encode_dc_error_response_order_message(const DcErrorResponseOrderMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 128; i++) { wire[at++] = record->error_message[i]; }

  return at;
}

/* Dc Error Response Order Message off the wire: 128 bytes from at, returning where the next byte lies */
static size_t decode_dc_error_response_order_message(DcErrorResponseOrderMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 128; i++) { record->error_message[i] = wire[at++]; }

  return at;
}

/* what was read of Dc Error Response Order Message is what was written, byte for byte */
static void equal_dc_error_response_order_message(const DcErrorResponseOrderMessage *read, const DcErrorResponseOrderMessage *written) {
  for (size_t i = 0; i < 128; i++) { assert(read->error_message[i] == written->error_message[i]); }
}

/* Dc Error Response Order Message: written and read back, then read and written back */
static void check_dc_error_response_order_message(void) {
  DcErrorResponseOrderMessage sent;
  DcErrorResponseOrderMessage got;
  uint8_t wire[128];
  uint8_t again[128];

  any_dc_error_response_order_message(&sent);
  assert(encode_dc_error_response_order_message(&sent, wire, 0) == 128);
  assert(decode_dc_error_response_order_message(&got, wire, 0) == 128);
  equal_dc_error_response_order_message(&got, &sent);

  for (size_t i = 0; i < 128; i++) { wire[i] = arbitrary(); }
  assert(decode_dc_error_response_order_message(&got, wire, 0) == 128);
  assert(encode_dc_error_response_order_message(&got, again, 0) == 128);
  for (size_t i = 0; i < 128; i++) { assert(again[i] == wire[i]); }
}

/* ---- What esbmc checks ------------------------------------------------------- */

/* every record of the protocol, each on its own buffers */
static void checks(void) {
  check_packet_header();
  check_response_message_header();
  check_message_header();
  check_ip_details_partition_wise();
  check_gr_response_message();
  check_dc_signon_out_message();
  check_dc_error_response_trade_message();
  check_dc_error_response_order_message();
}

int main(void) {
#ifdef CONCRETE
  for (pattern = 0; pattern < 4; pattern++) { checks(); }
#else
  checks();
#endif

  return 0;
}
