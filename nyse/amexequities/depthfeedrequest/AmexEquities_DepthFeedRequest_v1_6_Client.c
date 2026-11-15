// nyse/amexequities/depthfeedrequest/AmexEquities_DepthFeedRequest_v1_6_Client.c
/*
 * New York Stock Exchange Depth Feed Request
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
 *   - a Reassemble rule
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

/* ---- Send Time: 8 bytes ------------------------------------------------------ */

/* The time when this packet was sent on the request channel */
typedef struct {
  uint8_t seconds[4];      /* bytes 0 to 3 */
  uint8_t nanoseconds[4];  /* bytes 4 to 7 */
} SendTime;

/* any Send Time at all: every byte one the checker chooses */
static void any_send_time(SendTime *record) {
  for (size_t i = 0; i < 4; i++) { record->seconds[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = arbitrary(); }
}

/* Send Time to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_send_time(const SendTime *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->seconds[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->nanoseconds[i]; }

  return at;
}

/* Send Time off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_send_time(SendTime *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->seconds[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = wire[at++]; }

  return at;
}

/* what was read of Send Time is what was written, byte for byte */
static void equal_send_time(const SendTime *read, const SendTime *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->seconds[i] == written->seconds[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->nanoseconds[i] == written->nanoseconds[i]); }
}

/* Send Time: written and read back, then read and written back */
static void check_send_time(void) {
  SendTime sent;
  SendTime got;
  uint8_t wire[8];
  uint8_t again[8];

  any_send_time(&sent);
  assert(encode_send_time(&sent, wire, 0) == 8);
  assert(decode_send_time(&got, wire, 0) == 8);
  equal_send_time(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_send_time(&got, wire, 0) == 8);
  assert(encode_send_time(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Packet Header: 16 bytes ------------------------------------------------- */

/* Pillar common client tcp packet header */
typedef struct {
  uint8_t pkt_size[2];    /* bytes 0 to 1 */
  uint8_t delivery_flag;  /* byte 2 */
  uint8_t number_msgs;    /* byte 3 */
  uint8_t seq_num[4];     /* bytes 4 to 7 */
  SendTime send_time;     /* bytes 8 to 15 */
} PacketHeader;

/* any Packet Header at all: every byte one the checker chooses */
static void any_packet_header(PacketHeader *record) {
  for (size_t i = 0; i < 2; i++) { record->pkt_size[i] = arbitrary(); }
  record->delivery_flag = arbitrary();
  record->number_msgs = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->seq_num[i] = arbitrary(); }
  any_send_time(&record->send_time);
}

/* Packet Header to the wire: 16 bytes from at, returning where the next byte goes */
static size_t encode_packet_header(const PacketHeader *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->pkt_size[i]; }
  wire[at++] = record->delivery_flag;
  wire[at++] = record->number_msgs;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->seq_num[i]; }
  at = encode_send_time(&record->send_time, wire, at);

  return at;
}

/* Packet Header off the wire: 16 bytes from at, returning where the next byte lies */
static size_t decode_packet_header(PacketHeader *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->pkt_size[i] = wire[at++]; }
  record->delivery_flag = wire[at++];
  record->number_msgs = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->seq_num[i] = wire[at++]; }
  at = decode_send_time(&record->send_time, wire, at);

  return at;
}

/* what was read of Packet Header is what was written, byte for byte */
static void equal_packet_header(const PacketHeader *read, const PacketHeader *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->pkt_size[i] == written->pkt_size[i]); }
  assert(read->delivery_flag == written->delivery_flag);
  assert(read->number_msgs == written->number_msgs);
  for (size_t i = 0; i < 4; i++) { assert(read->seq_num[i] == written->seq_num[i]); }
  equal_send_time(&read->send_time, &written->send_time);
}

/* Packet Header: written and read back, then read and written back */
static void check_packet_header(void) {
  PacketHeader sent;
  PacketHeader got;
  uint8_t wire[16];
  uint8_t again[16];

  any_packet_header(&sent);
  assert(encode_packet_header(&sent, wire, 0) == 16);
  assert(decode_packet_header(&got, wire, 0) == 16);
  equal_packet_header(&got, &sent);

  for (size_t i = 0; i < 16; i++) { wire[i] = arbitrary(); }
  assert(decode_packet_header(&got, wire, 0) == 16);
  assert(encode_packet_header(&got, again, 0) == 16);
  for (size_t i = 0; i < 16; i++) { assert(again[i] == wire[i]); }
}

/* ---- Message Header: 4 bytes ------------------------------------------------- */

/* Pillar message header */
typedef struct {
  uint8_t message_size[2];  /* bytes 0 to 1 */
  uint8_t message_type[2];  /* bytes 2 to 3 */
} MessageHeader;

/* any Message Header at all: every byte one the checker chooses */
static void any_message_header(MessageHeader *record) {
  for (size_t i = 0; i < 2; i++) { record->message_size[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->message_type[i] = arbitrary(); }
}

/* Message Header to the wire: 4 bytes from at, returning where the next byte goes */
static size_t encode_message_header(const MessageHeader *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->message_size[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->message_type[i]; }

  return at;
}

/* Message Header off the wire: 4 bytes from at, returning where the next byte lies */
static size_t decode_message_header(MessageHeader *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->message_size[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->message_type[i] = wire[at++]; }

  return at;
}

/* what was read of Message Header is what was written, byte for byte */
static void equal_message_header(const MessageHeader *read, const MessageHeader *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->message_size[i] == written->message_size[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->message_type[i] == written->message_type[i]); }
}

/* Message Header: written and read back, then read and written back */
static void check_message_header(void) {
  MessageHeader sent;
  MessageHeader got;
  uint8_t wire[4];
  uint8_t again[4];

  any_message_header(&sent);
  assert(encode_message_header(&sent, wire, 0) == 4);
  assert(decode_message_header(&got, wire, 0) == 4);
  equal_message_header(&got, &sent);

  for (size_t i = 0; i < 4; i++) { wire[i] = arbitrary(); }
  assert(decode_message_header(&got, wire, 0) == 4);
  assert(encode_message_header(&got, again, 0) == 4);
  for (size_t i = 0; i < 4; i++) { assert(again[i] == wire[i]); }
}

/* ---- Retransmission Request Message: 20 bytes -------------------------------- */

/* Clients who have experienced a sequence number gap and need a retransmission of the missed messages should send a Retransmission Request message via TCP to the Request Controller. */
typedef struct {
  uint8_t begin_seq_num[4];  /* bytes 0 to 3 */
  uint8_t end_seq_num[4];    /* bytes 4 to 7 */
  uint8_t source_id[10];     /* bytes 8 to 17 */
  uint8_t product_id;        /* byte 18 */
  uint8_t channel_id;        /* byte 19 */
} RetransmissionRequestMessage;

/* any Retransmission Request Message at all: every byte one the checker chooses */
static void any_retransmission_request_message(RetransmissionRequestMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->begin_seq_num[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->end_seq_num[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->source_id[i] = arbitrary(); }
  record->product_id = arbitrary();
  record->channel_id = arbitrary();
}

/* Retransmission Request Message to the wire: 20 bytes from at, returning where the next byte goes */
static size_t encode_retransmission_request_message(const RetransmissionRequestMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->begin_seq_num[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->end_seq_num[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->source_id[i]; }
  wire[at++] = record->product_id;
  wire[at++] = record->channel_id;

  return at;
}

/* Retransmission Request Message off the wire: 20 bytes from at, returning where the next byte lies */
static size_t decode_retransmission_request_message(RetransmissionRequestMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->begin_seq_num[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->end_seq_num[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->source_id[i] = wire[at++]; }
  record->product_id = wire[at++];
  record->channel_id = wire[at++];

  return at;
}

/* what was read of Retransmission Request Message is what was written, byte for byte */
static void equal_retransmission_request_message(const RetransmissionRequestMessage *read, const RetransmissionRequestMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->begin_seq_num[i] == written->begin_seq_num[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->end_seq_num[i] == written->end_seq_num[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->source_id[i] == written->source_id[i]); }
  assert(read->product_id == written->product_id);
  assert(read->channel_id == written->channel_id);
}

/* Retransmission Request Message: written and read back, then read and written back */
static void check_retransmission_request_message(void) {
  RetransmissionRequestMessage sent;
  RetransmissionRequestMessage got;
  uint8_t wire[20];
  uint8_t again[20];

  any_retransmission_request_message(&sent);
  assert(encode_retransmission_request_message(&sent, wire, 0) == 20);
  assert(decode_retransmission_request_message(&got, wire, 0) == 20);
  equal_retransmission_request_message(&got, &sent);

  for (size_t i = 0; i < 20; i++) { wire[i] = arbitrary(); }
  assert(decode_retransmission_request_message(&got, wire, 0) == 20);
  assert(encode_retransmission_request_message(&got, again, 0) == 20);
  for (size_t i = 0; i < 20; i++) { assert(again[i] == wire[i]); }
}

/* ---- Heartbeat Response Message: 10 bytes ------------------------------------ */

/* Clients who remain connected to the Retransmission Server intraday must respond to a Heartbeat with a Heartbeat Response message within 5 seconds. If no timely client response is received, the connection will be closed. */
typedef struct {
  uint8_t source_id[10];  /* bytes 0 to 9 */
} HeartbeatResponseMessage;

/* any Heartbeat Response Message at all: every byte one the checker chooses */
static void any_heartbeat_response_message(HeartbeatResponseMessage *record) {
  for (size_t i = 0; i < 10; i++) { record->source_id[i] = arbitrary(); }
}

/* Heartbeat Response Message to the wire: 10 bytes from at, returning where the next byte goes */
static size_t encode_heartbeat_response_message(const HeartbeatResponseMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->source_id[i]; }

  return at;
}

/* Heartbeat Response Message off the wire: 10 bytes from at, returning where the next byte lies */
static size_t decode_heartbeat_response_message(HeartbeatResponseMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 10; i++) { record->source_id[i] = wire[at++]; }

  return at;
}

/* what was read of Heartbeat Response Message is what was written, byte for byte */
static void equal_heartbeat_response_message(const HeartbeatResponseMessage *read, const HeartbeatResponseMessage *written) {
  for (size_t i = 0; i < 10; i++) { assert(read->source_id[i] == written->source_id[i]); }
}

/* Heartbeat Response Message: written and read back, then read and written back */
static void check_heartbeat_response_message(void) {
  HeartbeatResponseMessage sent;
  HeartbeatResponseMessage got;
  uint8_t wire[10];
  uint8_t again[10];

  any_heartbeat_response_message(&sent);
  assert(encode_heartbeat_response_message(&sent, wire, 0) == 10);
  assert(decode_heartbeat_response_message(&got, wire, 0) == 10);
  equal_heartbeat_response_message(&got, &sent);

  for (size_t i = 0; i < 10; i++) { wire[i] = arbitrary(); }
  assert(decode_heartbeat_response_message(&got, wire, 0) == 10);
  assert(encode_heartbeat_response_message(&got, again, 0) == 10);
  for (size_t i = 0; i < 10; i++) { assert(again[i] == wire[i]); }
}

/* ---- Symbol Index Mapping Request Message: 17 bytes -------------------------- */

/* This message is sent by clients via TCP/IP requesting the Symbol Index Mapping messages for one or all symbols in a specified channel. */
typedef struct {
  uint8_t symbol_index[4];    /* bytes 0 to 3 */
  uint8_t source_id[10];      /* bytes 4 to 13 */
  uint8_t product_id;         /* byte 14 */
  uint8_t channel_id;         /* byte 15 */
  uint8_t retransmit_method;  /* byte 16 */
} SymbolIndexMappingRequestMessage;

/* any Symbol Index Mapping Request Message at all: every byte one the checker chooses */
static void any_symbol_index_mapping_request_message(SymbolIndexMappingRequestMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->symbol_index[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->source_id[i] = arbitrary(); }
  record->product_id = arbitrary();
  record->channel_id = arbitrary();
  record->retransmit_method = arbitrary();
}

/* Symbol Index Mapping Request Message to the wire: 17 bytes from at, returning where the next byte goes */
static size_t encode_symbol_index_mapping_request_message(const SymbolIndexMappingRequestMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->symbol_index[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->source_id[i]; }
  wire[at++] = record->product_id;
  wire[at++] = record->channel_id;
  wire[at++] = record->retransmit_method;

  return at;
}

/* Symbol Index Mapping Request Message off the wire: 17 bytes from at, returning where the next byte lies */
static size_t decode_symbol_index_mapping_request_message(SymbolIndexMappingRequestMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->symbol_index[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->source_id[i] = wire[at++]; }
  record->product_id = wire[at++];
  record->channel_id = wire[at++];
  record->retransmit_method = wire[at++];

  return at;
}

/* what was read of Symbol Index Mapping Request Message is what was written, byte for byte */
static void equal_symbol_index_mapping_request_message(const SymbolIndexMappingRequestMessage *read, const SymbolIndexMappingRequestMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->symbol_index[i] == written->symbol_index[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->source_id[i] == written->source_id[i]); }
  assert(read->product_id == written->product_id);
  assert(read->channel_id == written->channel_id);
  assert(read->retransmit_method == written->retransmit_method);
}

/* Symbol Index Mapping Request Message: written and read back, then read and written back */
static void check_symbol_index_mapping_request_message(void) {
  SymbolIndexMappingRequestMessage sent;
  SymbolIndexMappingRequestMessage got;
  uint8_t wire[17];
  uint8_t again[17];

  any_symbol_index_mapping_request_message(&sent);
  assert(encode_symbol_index_mapping_request_message(&sent, wire, 0) == 17);
  assert(decode_symbol_index_mapping_request_message(&got, wire, 0) == 17);
  equal_symbol_index_mapping_request_message(&got, &sent);

  for (size_t i = 0; i < 17; i++) { wire[i] = arbitrary(); }
  assert(decode_symbol_index_mapping_request_message(&got, wire, 0) == 17);
  assert(encode_symbol_index_mapping_request_message(&got, again, 0) == 17);
  for (size_t i = 0; i < 17; i++) { assert(again[i] == wire[i]); }
}

/* ---- Refresh Request Message: 16 bytes --------------------------------------- */

/* Clients who have experienced a failure and need a refresh of the state of one or all symbols in a specific channel should send a Refresh Request message via TCP to the Request Controller. */
typedef struct {
  uint8_t symbol_index[4];  /* bytes 0 to 3 */
  uint8_t source_id[10];    /* bytes 4 to 13 */
  uint8_t product_id;       /* byte 14 */
  uint8_t channel_id;       /* byte 15 */
} RefreshRequestMessage;

/* any Refresh Request Message at all: every byte one the checker chooses */
static void any_refresh_request_message(RefreshRequestMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->symbol_index[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->source_id[i] = arbitrary(); }
  record->product_id = arbitrary();
  record->channel_id = arbitrary();
}

/* Refresh Request Message to the wire: 16 bytes from at, returning where the next byte goes */
static size_t encode_refresh_request_message(const RefreshRequestMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->symbol_index[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->source_id[i]; }
  wire[at++] = record->product_id;
  wire[at++] = record->channel_id;

  return at;
}

/* Refresh Request Message off the wire: 16 bytes from at, returning where the next byte lies */
static size_t decode_refresh_request_message(RefreshRequestMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->symbol_index[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->source_id[i] = wire[at++]; }
  record->product_id = wire[at++];
  record->channel_id = wire[at++];

  return at;
}

/* what was read of Refresh Request Message is what was written, byte for byte */
static void equal_refresh_request_message(const RefreshRequestMessage *read, const RefreshRequestMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->symbol_index[i] == written->symbol_index[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->source_id[i] == written->source_id[i]); }
  assert(read->product_id == written->product_id);
  assert(read->channel_id == written->channel_id);
}

/* Refresh Request Message: written and read back, then read and written back */
static void check_refresh_request_message(void) {
  RefreshRequestMessage sent;
  RefreshRequestMessage got;
  uint8_t wire[16];
  uint8_t again[16];

  any_refresh_request_message(&sent);
  assert(encode_refresh_request_message(&sent, wire, 0) == 16);
  assert(decode_refresh_request_message(&got, wire, 0) == 16);
  equal_refresh_request_message(&got, &sent);

  for (size_t i = 0; i < 16; i++) { wire[i] = arbitrary(); }
  assert(decode_refresh_request_message(&got, wire, 0) == 16);
  assert(encode_refresh_request_message(&got, again, 0) == 16);
  for (size_t i = 0; i < 16; i++) { assert(again[i] == wire[i]); }
}

/* ---- What esbmc checks ------------------------------------------------------- */

/* every record of the protocol, each on its own buffers */
static void checks(void) {
  check_send_time();
  check_packet_header();
  check_message_header();
  check_retransmission_request_message();
  check_heartbeat_response_message();
  check_symbol_index_mapping_request_message();
  check_refresh_request_message();
}

int main(void) {
#ifdef CONCRETE
  for (pattern = 0; pattern < 4; pattern++) { checks(); }
#else
  checks();
#endif

  return 0;
}
