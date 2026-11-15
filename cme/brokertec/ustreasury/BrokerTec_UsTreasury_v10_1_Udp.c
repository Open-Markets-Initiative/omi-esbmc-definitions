// cme/brokertec/ustreasury/BrokerTec_UsTreasury_v10_1_Udp.c
/*
 * CME Group Us Treasuries
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
 *   - a block whose stated length holds more than its fields
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

/* ---- Binary Packet Header: 12 bytes ------------------------------------------ */

/* Cme Mdp Packet Header */
typedef struct {
  uint8_t packet_sequence_number[4];  /* bytes 0 to 3 */
  uint8_t sending_time[8];            /* bytes 4 to 11 */
} BinaryPacketHeader;

/* any Binary Packet Header at all: every byte one the checker chooses */
static void any_binary_packet_header(BinaryPacketHeader *record) {
  for (size_t i = 0; i < 4; i++) { record->packet_sequence_number[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->sending_time[i] = arbitrary(); }
}

/* Binary Packet Header to the wire: 12 bytes from at, returning where the next byte goes */
static size_t encode_binary_packet_header(const BinaryPacketHeader *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->packet_sequence_number[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->sending_time[i]; }

  return at;
}

/* Binary Packet Header off the wire: 12 bytes from at, returning where the next byte lies */
static size_t decode_binary_packet_header(BinaryPacketHeader *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->packet_sequence_number[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->sending_time[i] = wire[at++]; }

  return at;
}

/* what was read of Binary Packet Header is what was written, byte for byte */
static void equal_binary_packet_header(const BinaryPacketHeader *read, const BinaryPacketHeader *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->packet_sequence_number[i] == written->packet_sequence_number[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->sending_time[i] == written->sending_time[i]); }
}

/* Binary Packet Header: written and read back, then read and written back */
static void check_binary_packet_header(void) {
  BinaryPacketHeader sent;
  BinaryPacketHeader got;
  uint8_t wire[12];
  uint8_t again[12];

  any_binary_packet_header(&sent);
  assert(encode_binary_packet_header(&sent, wire, 0) == 12);
  assert(decode_binary_packet_header(&got, wire, 0) == 12);
  equal_binary_packet_header(&got, &sent);

  for (size_t i = 0; i < 12; i++) { wire[i] = arbitrary(); }
  assert(decode_binary_packet_header(&got, wire, 0) == 12);
  assert(encode_binary_packet_header(&got, again, 0) == 12);
  for (size_t i = 0; i < 12; i++) { assert(again[i] == wire[i]); }
}

/* ---- Simple Binary Header: 8 bytes ------------------------------------------- */

/* Template ID and length of message root */
typedef struct {
  uint8_t block_length[2];  /* bytes 0 to 1 */
  uint8_t template_id[2];   /* bytes 2 to 3 */
  uint8_t schema_id[2];     /* bytes 4 to 5 */
  uint8_t version[2];       /* bytes 6 to 7 */
} SimpleBinaryHeader;

/* any Simple Binary Header at all: every byte one the checker chooses */
static void any_simple_binary_header(SimpleBinaryHeader *record) {
  for (size_t i = 0; i < 2; i++) { record->block_length[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->template_id[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->schema_id[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->version[i] = arbitrary(); }
}

/* Simple Binary Header to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_simple_binary_header(const SimpleBinaryHeader *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->block_length[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->template_id[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->schema_id[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->version[i]; }

  return at;
}

/* Simple Binary Header off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_simple_binary_header(SimpleBinaryHeader *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->block_length[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->template_id[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->schema_id[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->version[i] = wire[at++]; }

  return at;
}

/* what was read of Simple Binary Header is what was written, byte for byte */
static void equal_simple_binary_header(const SimpleBinaryHeader *read, const SimpleBinaryHeader *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->block_length[i] == written->block_length[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->template_id[i] == written->template_id[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->schema_id[i] == written->schema_id[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->version[i] == written->version[i]); }
}

/* Simple Binary Header: written and read back, then read and written back */
static void check_simple_binary_header(void) {
  SimpleBinaryHeader sent;
  SimpleBinaryHeader got;
  uint8_t wire[8];
  uint8_t again[8];

  any_simple_binary_header(&sent);
  assert(encode_simple_binary_header(&sent, wire, 0) == 8);
  assert(decode_simple_binary_header(&got, wire, 0) == 8);
  equal_simple_binary_header(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_simple_binary_header(&got, wire, 0) == 8);
  assert(encode_simple_binary_header(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Message Header: 10 bytes ------------------------------------------------ */

/* Message Size followed by the Simple Binary Header */
typedef struct {
  uint8_t message_size[2];                  /* bytes 0 to 1 */
  SimpleBinaryHeader simple_binary_header;  /* bytes 2 to 9 */
} MessageHeader;

/* any Message Header at all: every byte one the checker chooses */
static void any_message_header(MessageHeader *record) {
  for (size_t i = 0; i < 2; i++) { record->message_size[i] = arbitrary(); }
  any_simple_binary_header(&record->simple_binary_header);
}

/* Message Header to the wire: 10 bytes from at, returning where the next byte goes */
static size_t encode_message_header(const MessageHeader *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->message_size[i]; }
  at = encode_simple_binary_header(&record->simple_binary_header, wire, at);

  return at;
}

/* Message Header off the wire: 10 bytes from at, returning where the next byte lies */
static size_t decode_message_header(MessageHeader *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->message_size[i] = wire[at++]; }
  at = decode_simple_binary_header(&record->simple_binary_header, wire, at);

  return at;
}

/* what was read of Message Header is what was written, byte for byte */
static void equal_message_header(const MessageHeader *read, const MessageHeader *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->message_size[i] == written->message_size[i]); }
  equal_simple_binary_header(&read->simple_binary_header, &written->simple_binary_header);
}

/* Message Header: written and read back, then read and written back */
static void check_message_header(void) {
  MessageHeader sent;
  MessageHeader got;
  uint8_t wire[10];
  uint8_t again[10];

  any_message_header(&sent);
  assert(encode_message_header(&sent, wire, 0) == 10);
  assert(decode_message_header(&got, wire, 0) == 10);
  equal_message_header(&got, &sent);

  for (size_t i = 0; i < 10; i++) { wire[i] = arbitrary(); }
  assert(decode_message_header(&got, wire, 0) == 10);
  assert(encode_message_header(&got, again, 0) == 10);
  for (size_t i = 0; i < 10; i++) { assert(again[i] == wire[i]); }
}

/* ---- Group Size: 3 bytes ----------------------------------------------------- */

/* Repeating group dimensions */
typedef struct {
  uint8_t block_length[2];  /* bytes 0 to 1 */
  uint8_t num_in_group;     /* byte 2 */
} GroupSize;

/* any Group Size at all: every byte one the checker chooses */
static void any_group_size(GroupSize *record) {
  for (size_t i = 0; i < 2; i++) { record->block_length[i] = arbitrary(); }
  record->num_in_group = arbitrary();
}

/* Group Size to the wire: 3 bytes from at, returning where the next byte goes */
static size_t encode_group_size(const GroupSize *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->block_length[i]; }
  wire[at++] = record->num_in_group;

  return at;
}

/* Group Size off the wire: 3 bytes from at, returning where the next byte lies */
static size_t decode_group_size(GroupSize *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->block_length[i] = wire[at++]; }
  record->num_in_group = wire[at++];

  return at;
}

/* what was read of Group Size is what was written, byte for byte */
static void equal_group_size(const GroupSize *read, const GroupSize *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->block_length[i] == written->block_length[i]); }
  assert(read->num_in_group == written->num_in_group);
}

/* Group Size: written and read back, then read and written back */
static void check_group_size(void) {
  GroupSize sent;
  GroupSize got;
  uint8_t wire[3];
  uint8_t again[3];

  any_group_size(&sent);
  assert(encode_group_size(&sent, wire, 0) == 3);
  assert(decode_group_size(&got, wire, 0) == 3);
  equal_group_size(&got, &sent);

  for (size_t i = 0; i < 3; i++) { wire[i] = arbitrary(); }
  assert(decode_group_size(&got, wire, 0) == 3);
  assert(encode_group_size(&got, again, 0) == 3);
  for (size_t i = 0; i < 3; i++) { assert(again[i] == wire[i]); }
}

/* ---- Md Entry Px: 9 bytes ---------------------------------------------------- */

/* Number of data blocks */
typedef struct {
  uint8_t mantissa[8];  /* bytes 0 to 7 */
  uint8_t exponent;     /* byte 8 */
} MdEntryPx;

/* any Md Entry Px at all: every byte one the checker chooses */
static void any_md_entry_px(MdEntryPx *record) {
  for (size_t i = 0; i < 8; i++) { record->mantissa[i] = arbitrary(); }
  record->exponent = arbitrary();
}

/* Md Entry Px to the wire: 9 bytes from at, returning where the next byte goes */
static size_t encode_md_entry_px(const MdEntryPx *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->mantissa[i]; }
  wire[at++] = record->exponent;

  return at;
}

/* Md Entry Px off the wire: 9 bytes from at, returning where the next byte lies */
static size_t decode_md_entry_px(MdEntryPx *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->mantissa[i] = wire[at++]; }
  record->exponent = wire[at++];

  return at;
}

/* what was read of Md Entry Px is what was written, byte for byte */
static void equal_md_entry_px(const MdEntryPx *read, const MdEntryPx *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->mantissa[i] == written->mantissa[i]); }
  assert(read->exponent == written->exponent);
}

/* Md Entry Px: written and read back, then read and written back */
static void check_md_entry_px(void) {
  MdEntryPx sent;
  MdEntryPx got;
  uint8_t wire[9];
  uint8_t again[9];

  any_md_entry_px(&sent);
  assert(encode_md_entry_px(&sent, wire, 0) == 9);
  assert(decode_md_entry_px(&got, wire, 0) == 9);
  equal_md_entry_px(&got, &sent);

  for (size_t i = 0; i < 9; i++) { wire[i] = arbitrary(); }
  assert(decode_md_entry_px(&got, wire, 0) == 9);
  assert(encode_md_entry_px(&got, again, 0) == 9);
  for (size_t i = 0; i < 9; i++) { assert(again[i] == wire[i]); }
}

/* ---- Coupon Rate: 5 bytes ---------------------------------------------------- */

/* Number of data blocks */
typedef struct {
  uint8_t mantissa_32[4];  /* bytes 0 to 3 */
  uint8_t exponent;        /* byte 4 */
} CouponRate;

/* any Coupon Rate at all: every byte one the checker chooses */
static void any_coupon_rate(CouponRate *record) {
  for (size_t i = 0; i < 4; i++) { record->mantissa_32[i] = arbitrary(); }
  record->exponent = arbitrary();
}

/* Coupon Rate to the wire: 5 bytes from at, returning where the next byte goes */
static size_t encode_coupon_rate(const CouponRate *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->mantissa_32[i]; }
  wire[at++] = record->exponent;

  return at;
}

/* Coupon Rate off the wire: 5 bytes from at, returning where the next byte lies */
static size_t decode_coupon_rate(CouponRate *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->mantissa_32[i] = wire[at++]; }
  record->exponent = wire[at++];

  return at;
}

/* what was read of Coupon Rate is what was written, byte for byte */
static void equal_coupon_rate(const CouponRate *read, const CouponRate *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->mantissa_32[i] == written->mantissa_32[i]); }
  assert(read->exponent == written->exponent);
}

/* Coupon Rate: written and read back, then read and written back */
static void check_coupon_rate(void) {
  CouponRate sent;
  CouponRate got;
  uint8_t wire[5];
  uint8_t again[5];

  any_coupon_rate(&sent);
  assert(encode_coupon_rate(&sent, wire, 0) == 5);
  assert(decode_coupon_rate(&got, wire, 0) == 5);
  equal_coupon_rate(&got, &sent);

  for (size_t i = 0; i < 5; i++) { wire[i] = arbitrary(); }
  assert(decode_coupon_rate(&got, wire, 0) == 5);
  assert(encode_coupon_rate(&got, again, 0) == 5);
  for (size_t i = 0; i < 5; i++) { assert(again[i] == wire[i]); }
}

/* ---- What esbmc checks ------------------------------------------------------- */

/* every record of the protocol, each on its own buffers */
static void checks(void) {
  check_binary_packet_header();
  check_simple_binary_header();
  check_message_header();
  check_group_size();
  check_md_entry_px();
  check_coupon_rate();
}

int main(void) {
#ifdef CONCRETE
  for (pattern = 0; pattern < 4; pattern++) { checks(); }
#else
  checks();
#endif

  return 0;
}
