// nyse/nyseequities/openbook/NyseEquities_OpenBook_v2_1_b.c
/*
 * New York Stock Exchange Open Book
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
 *   - a length prefix framing what follows
 *   - a run counted by a field
 *   - a run filling what frames it
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

/* ---- Packet Header: 16 bytes ------------------------------------------------- */

typedef struct {
  uint8_t packet_size[2];       /* bytes 0 to 1 */
  uint8_t message_type[2];      /* bytes 2 to 3 */
  uint8_t sequence_number[4];   /* bytes 4 to 7 */
  uint8_t timestamp[4];         /* bytes 8 to 11 */
  uint8_t product_id;           /* byte 12 */
  uint8_t retransmission_flag;  /* byte 13 */
  uint8_t message_count;        /* byte 14 */
  uint8_t link_flag;            /* byte 15 */
} PacketHeader;

/* any Packet Header at all: every byte one the checker chooses */
static void any_packet_header(PacketHeader *record) {
  for (size_t i = 0; i < 2; i++) { record->packet_size[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->message_type[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->sequence_number[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->timestamp[i] = arbitrary(); }
  record->product_id = arbitrary();
  record->retransmission_flag = arbitrary();
  record->message_count = arbitrary();
  record->link_flag = arbitrary();
}

/* Packet Header to the wire: 16 bytes from at, returning where the next byte goes */
static size_t encode_packet_header(const PacketHeader *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->packet_size[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->message_type[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->sequence_number[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->timestamp[i]; }
  wire[at++] = record->product_id;
  wire[at++] = record->retransmission_flag;
  wire[at++] = record->message_count;
  wire[at++] = record->link_flag;

  return at;
}

/* Packet Header off the wire: 16 bytes from at, returning where the next byte lies */
static size_t decode_packet_header(PacketHeader *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->packet_size[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->message_type[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->sequence_number[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->timestamp[i] = wire[at++]; }
  record->product_id = wire[at++];
  record->retransmission_flag = wire[at++];
  record->message_count = wire[at++];
  record->link_flag = wire[at++];

  return at;
}

/* what was read of Packet Header is what was written, byte for byte */
static void equal_packet_header(const PacketHeader *read, const PacketHeader *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->packet_size[i] == written->packet_size[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->message_type[i] == written->message_type[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->sequence_number[i] == written->sequence_number[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  assert(read->product_id == written->product_id);
  assert(read->retransmission_flag == written->retransmission_flag);
  assert(read->message_count == written->message_count);
  assert(read->link_flag == written->link_flag);
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

/* ---- Sequence Number Reset Message: 4 bytes ---------------------------------- */

/* This message is sent to reset the Packet Sequence Number. */
typedef struct {
  uint8_t next_sequence_number[4];  /* bytes 0 to 3 */
} SequenceNumberResetMessage;

/* any Sequence Number Reset Message at all: every byte one the checker chooses */
static void any_sequence_number_reset_message(SequenceNumberResetMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->next_sequence_number[i] = arbitrary(); }
}

/* Sequence Number Reset Message to the wire: 4 bytes from at, returning where the next byte goes */
static size_t encode_sequence_number_reset_message(const SequenceNumberResetMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->next_sequence_number[i]; }

  return at;
}

/* Sequence Number Reset Message off the wire: 4 bytes from at, returning where the next byte lies */
static size_t decode_sequence_number_reset_message(SequenceNumberResetMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->next_sequence_number[i] = wire[at++]; }

  return at;
}

/* what was read of Sequence Number Reset Message is what was written, byte for byte */
static void equal_sequence_number_reset_message(const SequenceNumberResetMessage *read, const SequenceNumberResetMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->next_sequence_number[i] == written->next_sequence_number[i]); }
}

/* Sequence Number Reset Message: written and read back, then read and written back */
static void check_sequence_number_reset_message(void) {
  SequenceNumberResetMessage sent;
  SequenceNumberResetMessage got;
  uint8_t wire[4];
  uint8_t again[4];

  any_sequence_number_reset_message(&sent);
  assert(encode_sequence_number_reset_message(&sent, wire, 0) == 4);
  assert(decode_sequence_number_reset_message(&got, wire, 0) == 4);
  equal_sequence_number_reset_message(&got, &sent);

  for (size_t i = 0; i < 4; i++) { wire[i] = arbitrary(); }
  assert(decode_sequence_number_reset_message(&got, wire, 0) == 4);
  assert(encode_sequence_number_reset_message(&got, again, 0) == 4);
  for (size_t i = 0; i < 4; i++) { assert(again[i] == wire[i]); }
}

/* ---- Unavailable Message: 8 bytes -------------------------------------------- */

/* This message will be sent over the Retransmission multicast channels to inform the clients of unavailability of a range of messages for which they have requested a retransmission. */
typedef struct {
  uint8_t begin_seq_num[4];  /* bytes 0 to 3 */
  uint8_t end_seq_num[4];    /* bytes 4 to 7 */
} UnavailableMessage;

/* any Unavailable Message at all: every byte one the checker chooses */
static void any_unavailable_message(UnavailableMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->begin_seq_num[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->end_seq_num[i] = arbitrary(); }
}

/* Unavailable Message to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_unavailable_message(const UnavailableMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->begin_seq_num[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->end_seq_num[i]; }

  return at;
}

/* Unavailable Message off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_unavailable_message(UnavailableMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->begin_seq_num[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->end_seq_num[i] = wire[at++]; }

  return at;
}

/* what was read of Unavailable Message is what was written, byte for byte */
static void equal_unavailable_message(const UnavailableMessage *read, const UnavailableMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->begin_seq_num[i] == written->begin_seq_num[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->end_seq_num[i] == written->end_seq_num[i]); }
}

/* Unavailable Message: written and read back, then read and written back */
static void check_unavailable_message(void) {
  UnavailableMessage sent;
  UnavailableMessage got;
  uint8_t wire[8];
  uint8_t again[8];

  any_unavailable_message(&sent);
  assert(encode_unavailable_message(&sent, wire, 0) == 8);
  assert(decode_unavailable_message(&got, wire, 0) == 8);
  equal_unavailable_message(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_unavailable_message(&got, wire, 0) == 8);
  assert(encode_unavailable_message(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Request Response Message: 28 bytes -------------------------------------- */

/* This message will be sent immediately via TCP/IP in response to the client's request for a retransmission, refresh, or Symbol Index information. The requested information will follow in the appropriate retransmission or refresh channel. */
typedef struct {
  uint8_t source_seq_num[4];  /* bytes 0 to 3 */
  uint8_t source_id[20];      /* bytes 4 to 23 */
  uint8_t status;             /* byte 24 */
  uint8_t reject_reason;      /* byte 25 */
  uint8_t filler_2[2];        /* bytes 26 to 27 */
} RequestResponseMessage;

/* any Request Response Message at all: every byte one the checker chooses */
static void any_request_response_message(RequestResponseMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->source_seq_num[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->source_id[i] = arbitrary(); }
  record->status = arbitrary();
  record->reject_reason = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->filler_2[i] = arbitrary(); }
}

/* Request Response Message to the wire: 28 bytes from at, returning where the next byte goes */
static size_t encode_request_response_message(const RequestResponseMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->source_seq_num[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->source_id[i]; }
  wire[at++] = record->status;
  wire[at++] = record->reject_reason;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->filler_2[i]; }

  return at;
}

/* Request Response Message off the wire: 28 bytes from at, returning where the next byte lies */
static size_t decode_request_response_message(RequestResponseMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->source_seq_num[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->source_id[i] = wire[at++]; }
  record->status = wire[at++];
  record->reject_reason = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->filler_2[i] = wire[at++]; }

  return at;
}

/* what was read of Request Response Message is what was written, byte for byte */
static void equal_request_response_message(const RequestResponseMessage *read, const RequestResponseMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->source_seq_num[i] == written->source_seq_num[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->source_id[i] == written->source_id[i]); }
  assert(read->status == written->status);
  assert(read->reject_reason == written->reject_reason);
  for (size_t i = 0; i < 2; i++) { assert(read->filler_2[i] == written->filler_2[i]); }
}

/* Request Response Message: written and read back, then read and written back */
static void check_request_response_message(void) {
  RequestResponseMessage sent;
  RequestResponseMessage got;
  uint8_t wire[28];
  uint8_t again[28];

  any_request_response_message(&sent);
  assert(encode_request_response_message(&sent, wire, 0) == 28);
  assert(decode_request_response_message(&got, wire, 0) == 28);
  equal_request_response_message(&got, &sent);

  for (size_t i = 0; i < 28; i++) { wire[i] = arbitrary(); }
  assert(decode_request_response_message(&got, wire, 0) == 28);
  assert(encode_request_response_message(&got, again, 0) == 28);
  for (size_t i = 0; i < 28; i++) { assert(again[i] == wire[i]); }
}

/* ---- Retransmission Request Message: 28 bytes -------------------------------- */

/* This message is sent by clients to request a retransmission of missed packets. In response, a Request Response message (type 10) will be sent back over the Request TCP connection, and the retransmitted packets will be delivered over the Retransmission channels. */
typedef struct {
  uint8_t begin_seq_num[4];  /* bytes 0 to 3 */
  uint8_t end_seq_num[4];    /* bytes 4 to 7 */
  uint8_t source_id[20];     /* bytes 8 to 27 */
} RetransmissionRequestMessage;

/* any Retransmission Request Message at all: every byte one the checker chooses */
static void any_retransmission_request_message(RetransmissionRequestMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->begin_seq_num[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->end_seq_num[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->source_id[i] = arbitrary(); }
}

/* Retransmission Request Message to the wire: 28 bytes from at, returning where the next byte goes */
static size_t encode_retransmission_request_message(const RetransmissionRequestMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->begin_seq_num[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->end_seq_num[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->source_id[i]; }

  return at;
}

/* Retransmission Request Message off the wire: 28 bytes from at, returning where the next byte lies */
static size_t decode_retransmission_request_message(RetransmissionRequestMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->begin_seq_num[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->end_seq_num[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->source_id[i] = wire[at++]; }

  return at;
}

/* what was read of Retransmission Request Message is what was written, byte for byte */
static void equal_retransmission_request_message(const RetransmissionRequestMessage *read, const RetransmissionRequestMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->begin_seq_num[i] == written->begin_seq_num[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->end_seq_num[i] == written->end_seq_num[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->source_id[i] == written->source_id[i]); }
}

/* Retransmission Request Message: written and read back, then read and written back */
static void check_retransmission_request_message(void) {
  RetransmissionRequestMessage sent;
  RetransmissionRequestMessage got;
  uint8_t wire[28];
  uint8_t again[28];

  any_retransmission_request_message(&sent);
  assert(encode_retransmission_request_message(&sent, wire, 0) == 28);
  assert(decode_retransmission_request_message(&got, wire, 0) == 28);
  equal_retransmission_request_message(&got, &sent);

  for (size_t i = 0; i < 28; i++) { wire[i] = arbitrary(); }
  assert(decode_retransmission_request_message(&got, wire, 0) == 28);
  assert(encode_retransmission_request_message(&got, again, 0) == 28);
  for (size_t i = 0; i < 28; i++) { assert(again[i] == wire[i]); }
}

/* ---- Book Refresh Request Message: 36 bytes ---------------------------------- */

/* This message is sent by clients requesting a full book refresh. */
typedef struct {
  uint8_t symbol_16[16];  /* bytes 0 to 15 */
  uint8_t source_id[20];  /* bytes 16 to 35 */
} BookRefreshRequestMessage;

/* any Book Refresh Request Message at all: every byte one the checker chooses */
static void any_book_refresh_request_message(BookRefreshRequestMessage *record) {
  for (size_t i = 0; i < 16; i++) { record->symbol_16[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->source_id[i] = arbitrary(); }
}

/* Book Refresh Request Message to the wire: 36 bytes from at, returning where the next byte goes */
static size_t encode_book_refresh_request_message(const BookRefreshRequestMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->symbol_16[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->source_id[i]; }

  return at;
}

/* Book Refresh Request Message off the wire: 36 bytes from at, returning where the next byte lies */
static size_t decode_book_refresh_request_message(BookRefreshRequestMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 16; i++) { record->symbol_16[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->source_id[i] = wire[at++]; }

  return at;
}

/* what was read of Book Refresh Request Message is what was written, byte for byte */
static void equal_book_refresh_request_message(const BookRefreshRequestMessage *read, const BookRefreshRequestMessage *written) {
  for (size_t i = 0; i < 16; i++) { assert(read->symbol_16[i] == written->symbol_16[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->source_id[i] == written->source_id[i]); }
}

/* Book Refresh Request Message: written and read back, then read and written back */
static void check_book_refresh_request_message(void) {
  BookRefreshRequestMessage sent;
  BookRefreshRequestMessage got;
  uint8_t wire[36];
  uint8_t again[36];

  any_book_refresh_request_message(&sent);
  assert(encode_book_refresh_request_message(&sent, wire, 0) == 36);
  assert(decode_book_refresh_request_message(&got, wire, 0) == 36);
  equal_book_refresh_request_message(&got, &sent);

  for (size_t i = 0; i < 36; i++) { wire[i] = arbitrary(); }
  assert(decode_book_refresh_request_message(&got, wire, 0) == 36);
  assert(encode_book_refresh_request_message(&got, again, 0) == 36);
  for (size_t i = 0; i < 36; i++) { assert(again[i] == wire[i]); }
}

/* ---- Heartbeat Response Message: 20 bytes ------------------------------------ */

/* Clients that remain connected to the Request server intraday must respond within 120 seconds to any heartbeat received with a single message of this type in its own packet. This response demonstrates that the TCP connection is still alive and prevents the Request Server from closing the connection. */
typedef struct {
  uint8_t source_id[20];  /* bytes 0 to 19 */
} HeartbeatResponseMessage;

/* any Heartbeat Response Message at all: every byte one the checker chooses */
static void any_heartbeat_response_message(HeartbeatResponseMessage *record) {
  for (size_t i = 0; i < 20; i++) { record->source_id[i] = arbitrary(); }
}

/* Heartbeat Response Message to the wire: 20 bytes from at, returning where the next byte goes */
static size_t encode_heartbeat_response_message(const HeartbeatResponseMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->source_id[i]; }

  return at;
}

/* Heartbeat Response Message off the wire: 20 bytes from at, returning where the next byte lies */
static size_t decode_heartbeat_response_message(HeartbeatResponseMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 20; i++) { record->source_id[i] = wire[at++]; }

  return at;
}

/* what was read of Heartbeat Response Message is what was written, byte for byte */
static void equal_heartbeat_response_message(const HeartbeatResponseMessage *read, const HeartbeatResponseMessage *written) {
  for (size_t i = 0; i < 20; i++) { assert(read->source_id[i] == written->source_id[i]); }
}

/* Heartbeat Response Message: written and read back, then read and written back */
static void check_heartbeat_response_message(void) {
  HeartbeatResponseMessage sent;
  HeartbeatResponseMessage got;
  uint8_t wire[20];
  uint8_t again[20];

  any_heartbeat_response_message(&sent);
  assert(encode_heartbeat_response_message(&sent, wire, 0) == 20);
  assert(decode_heartbeat_response_message(&got, wire, 0) == 20);
  equal_heartbeat_response_message(&got, &sent);

  for (size_t i = 0; i < 20; i++) { wire[i] = arbitrary(); }
  assert(decode_heartbeat_response_message(&got, wire, 0) == 20);
  assert(encode_heartbeat_response_message(&got, again, 0) == 20);
  for (size_t i = 0; i < 20; i++) { assert(again[i] == wire[i]); }
}

/* ---- Extended Book Refresh Request Message: 26 bytes ------------------------- */

/* The Extended Book Refresh Request message allows the client to request a refresh by symbol index as opposed to symbol, and to request a refresh of all symbols in a channel. */
typedef struct {
  uint8_t source_id[20];    /* bytes 0 to 19 */
  uint8_t symbol_index[4];  /* bytes 20 to 23 */
  uint8_t msg_type[2];      /* bytes 24 to 25 */
} ExtendedBookRefreshRequestMessage;

/* any Extended Book Refresh Request Message at all: every byte one the checker chooses */
static void any_extended_book_refresh_request_message(ExtendedBookRefreshRequestMessage *record) {
  for (size_t i = 0; i < 20; i++) { record->source_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->symbol_index[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->msg_type[i] = arbitrary(); }
}

/* Extended Book Refresh Request Message to the wire: 26 bytes from at, returning where the next byte goes */
static size_t encode_extended_book_refresh_request_message(const ExtendedBookRefreshRequestMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->source_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->symbol_index[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->msg_type[i]; }

  return at;
}

/* Extended Book Refresh Request Message off the wire: 26 bytes from at, returning where the next byte lies */
static size_t decode_extended_book_refresh_request_message(ExtendedBookRefreshRequestMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 20; i++) { record->source_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->symbol_index[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->msg_type[i] = wire[at++]; }

  return at;
}

/* what was read of Extended Book Refresh Request Message is what was written, byte for byte */
static void equal_extended_book_refresh_request_message(const ExtendedBookRefreshRequestMessage *read, const ExtendedBookRefreshRequestMessage *written) {
  for (size_t i = 0; i < 20; i++) { assert(read->source_id[i] == written->source_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->symbol_index[i] == written->symbol_index[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->msg_type[i] == written->msg_type[i]); }
}

/* Extended Book Refresh Request Message: written and read back, then read and written back */
static void check_extended_book_refresh_request_message(void) {
  ExtendedBookRefreshRequestMessage sent;
  ExtendedBookRefreshRequestMessage got;
  uint8_t wire[26];
  uint8_t again[26];

  any_extended_book_refresh_request_message(&sent);
  assert(encode_extended_book_refresh_request_message(&sent, wire, 0) == 26);
  assert(decode_extended_book_refresh_request_message(&got, wire, 0) == 26);
  equal_extended_book_refresh_request_message(&got, &sent);

  for (size_t i = 0; i < 26; i++) { wire[i] = arbitrary(); }
  assert(decode_extended_book_refresh_request_message(&got, wire, 0) == 26);
  assert(encode_extended_book_refresh_request_message(&got, again, 0) == 26);
  for (size_t i = 0; i < 26; i++) { assert(again[i] == wire[i]); }
}

/* ---- Symbol Index Mapping Request Message: 24 bytes -------------------------- */

/* This message is sent by clients requesting a refresh of Symbol Index mapping information only. */
typedef struct {
  uint8_t source_id[20];    /* bytes 0 to 19 */
  uint8_t symbol_index[4];  /* bytes 20 to 23 */
} SymbolIndexMappingRequestMessage;

/* any Symbol Index Mapping Request Message at all: every byte one the checker chooses */
static void any_symbol_index_mapping_request_message(SymbolIndexMappingRequestMessage *record) {
  for (size_t i = 0; i < 20; i++) { record->source_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->symbol_index[i] = arbitrary(); }
}

/* Symbol Index Mapping Request Message to the wire: 24 bytes from at, returning where the next byte goes */
static size_t encode_symbol_index_mapping_request_message(const SymbolIndexMappingRequestMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->source_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->symbol_index[i]; }

  return at;
}

/* Symbol Index Mapping Request Message off the wire: 24 bytes from at, returning where the next byte lies */
static size_t decode_symbol_index_mapping_request_message(SymbolIndexMappingRequestMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 20; i++) { record->source_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->symbol_index[i] = wire[at++]; }

  return at;
}

/* what was read of Symbol Index Mapping Request Message is what was written, byte for byte */
static void equal_symbol_index_mapping_request_message(const SymbolIndexMappingRequestMessage *read, const SymbolIndexMappingRequestMessage *written) {
  for (size_t i = 0; i < 20; i++) { assert(read->source_id[i] == written->source_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->symbol_index[i] == written->symbol_index[i]); }
}

/* Symbol Index Mapping Request Message: written and read back, then read and written back */
static void check_symbol_index_mapping_request_message(void) {
  SymbolIndexMappingRequestMessage sent;
  SymbolIndexMappingRequestMessage got;
  uint8_t wire[24];
  uint8_t again[24];

  any_symbol_index_mapping_request_message(&sent);
  assert(encode_symbol_index_mapping_request_message(&sent, wire, 0) == 24);
  assert(decode_symbol_index_mapping_request_message(&got, wire, 0) == 24);
  equal_symbol_index_mapping_request_message(&got, &sent);

  for (size_t i = 0; i < 24; i++) { wire[i] = arbitrary(); }
  assert(decode_symbol_index_mapping_request_message(&got, wire, 0) == 24);
  assert(encode_symbol_index_mapping_request_message(&got, again, 0) == 24);
  for (size_t i = 0; i < 24; i++) { assert(again[i] == wire[i]); }
}

/* ---- What esbmc checks ------------------------------------------------------- */

/* every record of the protocol, each on its own buffers */
static void checks(void) {
  check_packet_header();
  check_sequence_number_reset_message();
  check_unavailable_message();
  check_request_response_message();
  check_retransmission_request_message();
  check_book_refresh_request_message();
  check_heartbeat_response_message();
  check_extended_book_refresh_request_message();
  check_symbol_index_mapping_request_message();
}

int main(void) {
#ifdef CONCRETE
  for (pattern = 0; pattern < 4; pattern++) { checks(); }
#else
  checks();
#endif

  return 0;
}
