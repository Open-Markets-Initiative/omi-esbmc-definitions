// aquis/snapshot/AquisStockExchange_Snapshot_v1_2_3.c
/*
 * Aquis Exchange Snapshot
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
 *   - a run counted by a field
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

/* ---- Packet Header: 1 byte --------------------------------------------------- */

/* Aquis udp packet header */
typedef struct {
  uint8_t message_count;  /* byte 0 */
} PacketHeader;

/* any Packet Header at all: every byte one the checker chooses */
static void any_packet_header(PacketHeader *record) {
  record->message_count = arbitrary();
}

/* Packet Header to the wire: 1 byte from at, returning where the next byte goes */
static size_t encode_packet_header(const PacketHeader *record, uint8_t *wire, size_t at) {
  wire[at++] = record->message_count;

  return at;
}

/* Packet Header off the wire: 1 byte from at, returning where the next byte lies */
static size_t decode_packet_header(PacketHeader *record, const uint8_t *wire, size_t at) {
  record->message_count = wire[at++];

  return at;
}

/* what was read of Packet Header is what was written, byte for byte */
static void equal_packet_header(const PacketHeader *read, const PacketHeader *written) {
  assert(read->message_count == written->message_count);
}

/* Packet Header: written and read back, then read and written back */
static void check_packet_header(void) {
  PacketHeader sent;
  PacketHeader got;
  uint8_t wire[1];
  uint8_t again[1];

  any_packet_header(&sent);
  assert(encode_packet_header(&sent, wire, 0) == 1);
  assert(decode_packet_header(&got, wire, 0) == 1);
  equal_packet_header(&got, &sent);

  for (size_t i = 0; i < 1; i++) { wire[i] = arbitrary(); }
  assert(decode_packet_header(&got, wire, 0) == 1);
  assert(encode_packet_header(&got, again, 0) == 1);
  for (size_t i = 0; i < 1; i++) { assert(again[i] == wire[i]); }
}

/* ---- Message Header: 6 bytes ------------------------------------------------- */

/* Aquis market data message header */
typedef struct {
  uint8_t msg_type;    /* byte 0 */
  uint8_t msg_length;  /* byte 1 */
  uint8_t seq_no[4];   /* bytes 2 to 5 */
} MessageHeader;

/* any Message Header at all: every byte one the checker chooses */
static void any_message_header(MessageHeader *record) {
  record->msg_type = arbitrary();
  record->msg_length = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->seq_no[i] = arbitrary(); }
}

/* Message Header to the wire: 6 bytes from at, returning where the next byte goes */
static size_t encode_message_header(const MessageHeader *record, uint8_t *wire, size_t at) {
  wire[at++] = record->msg_type;
  wire[at++] = record->msg_length;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->seq_no[i]; }

  return at;
}

/* Message Header off the wire: 6 bytes from at, returning where the next byte lies */
static size_t decode_message_header(MessageHeader *record, const uint8_t *wire, size_t at) {
  record->msg_type = wire[at++];
  record->msg_length = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->seq_no[i] = wire[at++]; }

  return at;
}

/* what was read of Message Header is what was written, byte for byte */
static void equal_message_header(const MessageHeader *read, const MessageHeader *written) {
  assert(read->msg_type == written->msg_type);
  assert(read->msg_length == written->msg_length);
  for (size_t i = 0; i < 4; i++) { assert(read->seq_no[i] == written->seq_no[i]); }
}

/* Message Header: written and read back, then read and written back */
static void check_message_header(void) {
  MessageHeader sent;
  MessageHeader got;
  uint8_t wire[6];
  uint8_t again[6];

  any_message_header(&sent);
  assert(encode_message_header(&sent, wire, 0) == 6);
  assert(decode_message_header(&got, wire, 0) == 6);
  equal_message_header(&got, &sent);

  for (size_t i = 0; i < 6; i++) { wire[i] = arbitrary(); }
  assert(decode_message_header(&got, wire, 0) == 6);
  assert(encode_message_header(&got, again, 0) == 6);
  for (size_t i = 0; i < 6; i++) { assert(again[i] == wire[i]); }
}

/* ---- Snapshot Start Message: 14 bytes ---------------------------------------- */

/* A Snapshot Start message is published as the first message in a snapshot to identify the sequence number in the continuous stream that this snapshot relates to. It also states the number of securities being reported in this snapshot. This message is only applicable to continuous trading. */
typedef struct {
  uint8_t stream_seq_no[4];   /* bytes 0 to 3 */
  uint8_t security_count[2];  /* bytes 4 to 5 */
  uint8_t timestamp[8];       /* bytes 6 to 13 */
} SnapshotStartMessage;

/* any Snapshot Start Message at all: every byte one the checker chooses */
static void any_snapshot_start_message(SnapshotStartMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->stream_seq_no[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->security_count[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
}

/* Snapshot Start Message to the wire: 14 bytes from at, returning where the next byte goes */
static size_t encode_snapshot_start_message(const SnapshotStartMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->stream_seq_no[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->security_count[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }

  return at;
}

/* Snapshot Start Message off the wire: 14 bytes from at, returning where the next byte lies */
static size_t decode_snapshot_start_message(SnapshotStartMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->stream_seq_no[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->security_count[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }

  return at;
}

/* what was read of Snapshot Start Message is what was written, byte for byte */
static void equal_snapshot_start_message(const SnapshotStartMessage *read, const SnapshotStartMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->stream_seq_no[i] == written->stream_seq_no[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->security_count[i] == written->security_count[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
}

/* Snapshot Start Message: written and read back, then read and written back */
static void check_snapshot_start_message(void) {
  SnapshotStartMessage sent;
  SnapshotStartMessage got;
  uint8_t wire[14];
  uint8_t again[14];

  any_snapshot_start_message(&sent);
  assert(encode_snapshot_start_message(&sent, wire, 0) == 14);
  assert(decode_snapshot_start_message(&got, wire, 0) == 14);
  equal_snapshot_start_message(&got, &sent);

  for (size_t i = 0; i < 14; i++) { wire[i] = arbitrary(); }
  assert(decode_snapshot_start_message(&got, wire, 0) == 14);
  assert(encode_snapshot_start_message(&got, again, 0) == 14);
  for (size_t i = 0; i < 14; i++) { assert(again[i] == wire[i]); }
}

/* ---- Book Entry Message: 19 bytes -------------------------------------------- */

/* An appropriate number of Book Entry messages is published after each Book Status message to provide details of each order and allow the book to be built. This message is only applicable to continuous trading. */
typedef struct {
  uint8_t security_id[2];  /* bytes 0 to 1 */
  uint8_t side;            /* byte 2 */
  uint8_t quantity[4];     /* bytes 3 to 6 */
  uint8_t price[8];        /* bytes 7 to 14 */
  uint8_t order_ref[4];    /* bytes 15 to 18 */
} BookEntryMessage;

/* any Book Entry Message at all: every byte one the checker chooses */
static void any_book_entry_message(BookEntryMessage *record) {
  for (size_t i = 0; i < 2; i++) { record->security_id[i] = arbitrary(); }
  record->side = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->order_ref[i] = arbitrary(); }
}

/* Book Entry Message to the wire: 19 bytes from at, returning where the next byte goes */
static size_t encode_book_entry_message(const BookEntryMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->security_id[i]; }
  wire[at++] = record->side;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->quantity[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->order_ref[i]; }

  return at;
}

/* Book Entry Message off the wire: 19 bytes from at, returning where the next byte lies */
static size_t decode_book_entry_message(BookEntryMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->security_id[i] = wire[at++]; }
  record->side = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->order_ref[i] = wire[at++]; }

  return at;
}

/* what was read of Book Entry Message is what was written, byte for byte */
static void equal_book_entry_message(const BookEntryMessage *read, const BookEntryMessage *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->security_id[i] == written->security_id[i]); }
  assert(read->side == written->side);
  for (size_t i = 0; i < 4; i++) { assert(read->quantity[i] == written->quantity[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->price[i] == written->price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->order_ref[i] == written->order_ref[i]); }
}

/* Book Entry Message: written and read back, then read and written back */
static void check_book_entry_message(void) {
  BookEntryMessage sent;
  BookEntryMessage got;
  uint8_t wire[19];
  uint8_t again[19];

  any_book_entry_message(&sent);
  assert(encode_book_entry_message(&sent, wire, 0) == 19);
  assert(decode_book_entry_message(&got, wire, 0) == 19);
  equal_book_entry_message(&got, &sent);

  for (size_t i = 0; i < 19; i++) { wire[i] = arbitrary(); }
  assert(decode_book_entry_message(&got, wire, 0) == 19);
  assert(encode_book_entry_message(&got, again, 0) == 19);
  for (size_t i = 0; i < 19; i++) { assert(again[i] == wire[i]); }
}

/* ---- What esbmc checks ------------------------------------------------------- */

/* every record of the protocol, each on its own buffers */
static void checks(void) {
  check_packet_header();
  check_message_header();
  check_snapshot_start_message();
  check_book_entry_message();
}

int main(void) {
#ifdef CONCRETE
  for (pattern = 0; pattern < 4; pattern++) { checks(); }
#else
  checks();
#endif

  return 0;
}
