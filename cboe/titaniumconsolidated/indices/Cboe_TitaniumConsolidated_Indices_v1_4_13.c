// cboe/titaniumconsolidated/indices/Cboe_TitaniumConsolidated_Indices_v1_4_13.c
/*
 * Chicago Board Options Exchange Global Indices Feed
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

/* ---- Packet Header: 16 bytes ------------------------------------------------- */

/* Cgif packet header appearing once at the beginning of each packet */
typedef struct {
  uint8_t version;               /* byte 0 */
  uint8_t length[2];             /* bytes 1 to 2 */
  uint8_t sending_time[8];       /* bytes 3 to 10 */
  uint8_t number_of_messages;    /* byte 11 */
  uint8_t first_msg_seq_num[4];  /* bytes 12 to 15 */
} PacketHeader;

/* any Packet Header at all: every byte one the checker chooses */
static void any_packet_header(PacketHeader *record) {
  record->version = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->length[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->sending_time[i] = arbitrary(); }
  record->number_of_messages = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->first_msg_seq_num[i] = arbitrary(); }
}

/* Packet Header to the wire: 16 bytes from at, returning where the next byte goes */
static size_t encode_packet_header(const PacketHeader *record, uint8_t *wire, size_t at) {
  wire[at++] = record->version;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->length[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->sending_time[i]; }
  wire[at++] = record->number_of_messages;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->first_msg_seq_num[i]; }

  return at;
}

/* Packet Header off the wire: 16 bytes from at, returning where the next byte lies */
static size_t decode_packet_header(PacketHeader *record, const uint8_t *wire, size_t at) {
  record->version = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->length[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->sending_time[i] = wire[at++]; }
  record->number_of_messages = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->first_msg_seq_num[i] = wire[at++]; }

  return at;
}

/* what was read of Packet Header is what was written, byte for byte */
static void equal_packet_header(const PacketHeader *read, const PacketHeader *written) {
  assert(read->version == written->version);
  for (size_t i = 0; i < 2; i++) { assert(read->length[i] == written->length[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->sending_time[i] == written->sending_time[i]); }
  assert(read->number_of_messages == written->number_of_messages);
  for (size_t i = 0; i < 4; i++) { assert(read->first_msg_seq_num[i] == written->first_msg_seq_num[i]); }
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

/* ---- Message Header: 8 bytes ------------------------------------------------- */

/* Cgif Message Header common to all messages. Per spec section "Message Header": Length + Template ID + MessageType + MsgSeqNum, 8 bytes total. Template ID drives payload dispatch; MessageType is per-spec FIX-compliant market data type (may be shared across templates); MsgSeqNum is the per-channel monotonic sequence number. */
typedef struct {
  uint8_t message_length[2];  /* bytes 0 to 1 */
  uint8_t template_i_d;       /* byte 2 */
  uint8_t message_type;       /* byte 3 */
  uint8_t msg_seq_num[4];     /* bytes 4 to 7 */
} MessageHeader;

/* any Message Header at all: every byte one the checker chooses */
static void any_message_header(MessageHeader *record) {
  for (size_t i = 0; i < 2; i++) { record->message_length[i] = arbitrary(); }
  record->template_i_d = arbitrary();
  record->message_type = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->msg_seq_num[i] = arbitrary(); }
}

/* Message Header to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_message_header(const MessageHeader *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->message_length[i]; }
  wire[at++] = record->template_i_d;
  wire[at++] = record->message_type;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->msg_seq_num[i]; }

  return at;
}

/* Message Header off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_message_header(MessageHeader *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->message_length[i] = wire[at++]; }
  record->template_i_d = wire[at++];
  record->message_type = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->msg_seq_num[i] = wire[at++]; }

  return at;
}

/* what was read of Message Header is what was written, byte for byte */
static void equal_message_header(const MessageHeader *read, const MessageHeader *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->message_length[i] == written->message_length[i]); }
  assert(read->template_i_d == written->template_i_d);
  assert(read->message_type == written->message_type);
  for (size_t i = 0; i < 4; i++) { assert(read->msg_seq_num[i] == written->msg_seq_num[i]); }
}

/* Message Header: written and read back, then read and written back */
static void check_message_header(void) {
  MessageHeader sent;
  MessageHeader got;
  uint8_t wire[8];
  uint8_t again[8];

  any_message_header(&sent);
  assert(encode_message_header(&sent, wire, 0) == 8);
  assert(decode_message_header(&got, wire, 0) == 8);
  equal_message_header(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_message_header(&got, wire, 0) == 8);
  assert(encode_message_header(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Md Entry Px: 5 bytes ---------------------------------------------------- */

/* MDEntryPx */
typedef struct {
  uint8_t exponent;     /* byte 0 */
  uint8_t mantissa[4];  /* bytes 1 to 4 */
} MdEntryPx;

/* any Md Entry Px at all: every byte one the checker chooses */
static void any_md_entry_px(MdEntryPx *record) {
  record->exponent = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->mantissa[i] = arbitrary(); }
}

/* Md Entry Px to the wire: 5 bytes from at, returning where the next byte goes */
static size_t encode_md_entry_px(const MdEntryPx *record, uint8_t *wire, size_t at) {
  wire[at++] = record->exponent;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->mantissa[i]; }

  return at;
}

/* Md Entry Px off the wire: 5 bytes from at, returning where the next byte lies */
static size_t decode_md_entry_px(MdEntryPx *record, const uint8_t *wire, size_t at) {
  record->exponent = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->mantissa[i] = wire[at++]; }

  return at;
}

/* what was read of Md Entry Px is what was written, byte for byte */
static void equal_md_entry_px(const MdEntryPx *read, const MdEntryPx *written) {
  assert(read->exponent == written->exponent);
  for (size_t i = 0; i < 4; i++) { assert(read->mantissa[i] == written->mantissa[i]); }
}

/* Md Entry Px: written and read back, then read and written back */
static void check_md_entry_px(void) {
  MdEntryPx sent;
  MdEntryPx got;
  uint8_t wire[5];
  uint8_t again[5];

  any_md_entry_px(&sent);
  assert(encode_md_entry_px(&sent, wire, 0) == 5);
  assert(decode_md_entry_px(&got, wire, 0) == 5);
  equal_md_entry_px(&got, &sent);

  for (size_t i = 0; i < 5; i++) { wire[i] = arbitrary(); }
  assert(decode_md_entry_px(&got, wire, 0) == 5);
  assert(encode_md_entry_px(&got, again, 0) == 5);
  for (size_t i = 0; i < 5; i++) { assert(again[i] == wire[i]); }
}

/* ---- Effective Business Date: 9 bytes ---------------------------------------- */

/* EffectiveBusinessDate */
typedef struct {
  uint8_t byte_length;                       /* byte 0 */
  uint8_t effective_business_date_chars[8];  /* bytes 1 to 8 */
} EffectiveBusinessDate;

/* any Effective Business Date at all: every byte one the checker chooses */
static void any_effective_business_date(EffectiveBusinessDate *record) {
  record->byte_length = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->effective_business_date_chars[i] = arbitrary(); }
}

/* Effective Business Date to the wire: 9 bytes from at, returning where the next byte goes */
static size_t encode_effective_business_date(const EffectiveBusinessDate *record, uint8_t *wire, size_t at) {
  wire[at++] = record->byte_length;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->effective_business_date_chars[i]; }

  return at;
}

/* Effective Business Date off the wire: 9 bytes from at, returning where the next byte lies */
static size_t decode_effective_business_date(EffectiveBusinessDate *record, const uint8_t *wire, size_t at) {
  record->byte_length = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->effective_business_date_chars[i] = wire[at++]; }

  return at;
}

/* what was read of Effective Business Date is what was written, byte for byte */
static void equal_effective_business_date(const EffectiveBusinessDate *read, const EffectiveBusinessDate *written) {
  assert(read->byte_length == written->byte_length);
  for (size_t i = 0; i < 8; i++) { assert(read->effective_business_date_chars[i] == written->effective_business_date_chars[i]); }
}

/* Effective Business Date: written and read back, then read and written back */
static void check_effective_business_date(void) {
  EffectiveBusinessDate sent;
  EffectiveBusinessDate got;
  uint8_t wire[9];
  uint8_t again[9];

  any_effective_business_date(&sent);
  assert(encode_effective_business_date(&sent, wire, 0) == 9);
  assert(decode_effective_business_date(&got, wire, 0) == 9);
  equal_effective_business_date(&got, &sent);

  for (size_t i = 0; i < 9; i++) { wire[i] = arbitrary(); }
  assert(decode_effective_business_date(&got, wire, 0) == 9);
  assert(encode_effective_business_date(&got, again, 0) == 9);
  for (size_t i = 0; i < 9; i++) { assert(again[i] == wire[i]); }
}

/* ---- Date: 11 bytes ---------------------------------------------------------- */

/* Date */
typedef struct {
  uint8_t byte_length;     /* byte 0 */
  uint8_t date_chars[10];  /* bytes 1 to 10 */
} Date;

/* any Date at all: every byte one the checker chooses */
static void any_date(Date *record) {
  record->byte_length = arbitrary();
  for (size_t i = 0; i < 10; i++) { record->date_chars[i] = arbitrary(); }
}

/* Date to the wire: 11 bytes from at, returning where the next byte goes */
static size_t encode_date(const Date *record, uint8_t *wire, size_t at) {
  wire[at++] = record->byte_length;
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->date_chars[i]; }

  return at;
}

/* Date off the wire: 11 bytes from at, returning where the next byte lies */
static size_t decode_date(Date *record, const uint8_t *wire, size_t at) {
  record->byte_length = wire[at++];
  for (size_t i = 0; i < 10; i++) { record->date_chars[i] = wire[at++]; }

  return at;
}

/* what was read of Date is what was written, byte for byte */
static void equal_date(const Date *read, const Date *written) {
  assert(read->byte_length == written->byte_length);
  for (size_t i = 0; i < 10; i++) { assert(read->date_chars[i] == written->date_chars[i]); }
}

/* Date: written and read back, then read and written back */
static void check_date(void) {
  Date sent;
  Date got;
  uint8_t wire[11];
  uint8_t again[11];

  any_date(&sent);
  assert(encode_date(&sent, wire, 0) == 11);
  assert(decode_date(&got, wire, 0) == 11);
  equal_date(&got, &sent);

  for (size_t i = 0; i < 11; i++) { wire[i] = arbitrary(); }
  assert(decode_date(&got, wire, 0) == 11);
  assert(encode_date(&got, again, 0) == 11);
  for (size_t i = 0; i < 11; i++) { assert(again[i] == wire[i]); }
}

/* ---- What esbmc checks ------------------------------------------------------- */

/* every record of the protocol, each on its own buffers */
static void checks(void) {
  check_packet_header();
  check_message_header();
  check_md_entry_px();
  check_effective_business_date();
  check_date();
}

int main(void) {
#ifdef CONCRETE
  for (pattern = 0; pattern < 4; pattern++) { checks(); }
#else
  checks();
#endif

  return 0;
}
