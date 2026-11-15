// cme/globex/streamlined/Cme_Globex_Streamlined_v5_8_Udp.c
/*
 * CME Group Streamlined Market Data
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
 *   - a field read in bits
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

/* ---- Admin Login: 1 byte ----------------------------------------------------- */

/* AdminLogin */
typedef struct {
  uint8_t heart_bt_int;  /* byte 0 */
} AdminLogin;

/* any Admin Login at all: every byte one the checker chooses */
static void any_admin_login(AdminLogin *record) {
  record->heart_bt_int = arbitrary();
}

/* Admin Login to the wire: 1 byte from at, returning where the next byte goes */
static size_t encode_admin_login(const AdminLogin *record, uint8_t *wire, size_t at) {
  wire[at++] = record->heart_bt_int;

  return at;
}

/* Admin Login off the wire: 1 byte from at, returning where the next byte lies */
static size_t decode_admin_login(AdminLogin *record, const uint8_t *wire, size_t at) {
  record->heart_bt_int = wire[at++];

  return at;
}

/* what was read of Admin Login is what was written, byte for byte */
static void equal_admin_login(const AdminLogin *read, const AdminLogin *written) {
  assert(read->heart_bt_int == written->heart_bt_int);
}

/* Admin Login: written and read back, then read and written back */
static void check_admin_login(void) {
  AdminLogin sent;
  AdminLogin got;
  uint8_t wire[1];
  uint8_t again[1];

  any_admin_login(&sent);
  assert(encode_admin_login(&sent, wire, 0) == 1);
  assert(decode_admin_login(&got, wire, 0) == 1);
  equal_admin_login(&got, &sent);

  for (size_t i = 0; i < 1; i++) { wire[i] = arbitrary(); }
  assert(decode_admin_login(&got, wire, 0) == 1);
  assert(encode_admin_login(&got, again, 0) == 1);
  for (size_t i = 0; i < 1; i++) { assert(again[i] == wire[i]); }
}

/* ---- Admin Logout: 180 bytes ------------------------------------------------- */

/* AdminLogout */
typedef struct {
  uint8_t text[180];  /* bytes 0 to 179 */
} AdminLogout;

/* any Admin Logout at all: every byte one the checker chooses */
static void any_admin_logout(AdminLogout *record) {
  for (size_t i = 0; i < 180; i++) { record->text[i] = arbitrary(); }
}

/* Admin Logout to the wire: 180 bytes from at, returning where the next byte goes */
static size_t encode_admin_logout(const AdminLogout *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 180; i++) { wire[at++] = record->text[i]; }

  return at;
}

/* Admin Logout off the wire: 180 bytes from at, returning where the next byte lies */
static size_t decode_admin_logout(AdminLogout *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 180; i++) { record->text[i] = wire[at++]; }

  return at;
}

/* what was read of Admin Logout is what was written, byte for byte */
static void equal_admin_logout(const AdminLogout *read, const AdminLogout *written) {
  for (size_t i = 0; i < 180; i++) { assert(read->text[i] == written->text[i]); }
}

/* Admin Logout: written and read back, then read and written back */
static void check_admin_logout(void) {
  AdminLogout sent;
  AdminLogout got;
  uint8_t wire[180];
  uint8_t again[180];

  any_admin_logout(&sent);
  assert(encode_admin_logout(&sent, wire, 0) == 180);
  assert(decode_admin_logout(&got, wire, 0) == 180);
  equal_admin_logout(&got, &sent);

  for (size_t i = 0; i < 180; i++) { wire[i] = arbitrary(); }
  assert(decode_admin_logout(&got, wire, 0) == 180);
  assert(encode_admin_logout(&got, again, 0) == 180);
  for (size_t i = 0; i < 180; i++) { assert(again[i] == wire[i]); }
}

/* ---- Group Size: 3 bytes ----------------------------------------------------- */

/* Repeating group dimensions */
typedef struct {
  uint8_t block_length[2];  /* bytes 0 to 1 */
  uint8_t num_in_group_8;   /* byte 2 */
} GroupSize;

/* any Group Size at all: every byte one the checker chooses */
static void any_group_size(GroupSize *record) {
  for (size_t i = 0; i < 2; i++) { record->block_length[i] = arbitrary(); }
  record->num_in_group_8 = arbitrary();
}

/* Group Size to the wire: 3 bytes from at, returning where the next byte goes */
static size_t encode_group_size(const GroupSize *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->block_length[i]; }
  wire[at++] = record->num_in_group_8;

  return at;
}

/* Group Size off the wire: 3 bytes from at, returning where the next byte lies */
static size_t decode_group_size(GroupSize *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->block_length[i] = wire[at++]; }
  record->num_in_group_8 = wire[at++];

  return at;
}

/* what was read of Group Size is what was written, byte for byte */
static void equal_group_size(const GroupSize *read, const GroupSize *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->block_length[i] == written->block_length[i]); }
  assert(read->num_in_group_8 == written->num_in_group_8);
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

/* ---- Md Entry Px Decimal Optional: 9 bytes ----------------------------------- */

/* Number of entries in Market Data message. */
typedef struct {
  uint8_t mantissa[8];        /* bytes 0 to 7 */
  uint8_t exponent_optional;  /* byte 8 */
} MdEntryPxDecimalOptional;

/* any Md Entry Px Decimal Optional at all: every byte one the checker chooses */
static void any_md_entry_px_decimal_optional(MdEntryPxDecimalOptional *record) {
  for (size_t i = 0; i < 8; i++) { record->mantissa[i] = arbitrary(); }
  record->exponent_optional = arbitrary();
}

/* Md Entry Px Decimal Optional to the wire: 9 bytes from at, returning where the next byte goes */
static size_t encode_md_entry_px_decimal_optional(const MdEntryPxDecimalOptional *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->mantissa[i]; }
  wire[at++] = record->exponent_optional;

  return at;
}

/* Md Entry Px Decimal Optional off the wire: 9 bytes from at, returning where the next byte lies */
static size_t decode_md_entry_px_decimal_optional(MdEntryPxDecimalOptional *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->mantissa[i] = wire[at++]; }
  record->exponent_optional = wire[at++];

  return at;
}

/* what was read of Md Entry Px Decimal Optional is what was written, byte for byte */
static void equal_md_entry_px_decimal_optional(const MdEntryPxDecimalOptional *read, const MdEntryPxDecimalOptional *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->mantissa[i] == written->mantissa[i]); }
  assert(read->exponent_optional == written->exponent_optional);
}

/* Md Entry Px Decimal Optional: written and read back, then read and written back */
static void check_md_entry_px_decimal_optional(void) {
  MdEntryPxDecimalOptional sent;
  MdEntryPxDecimalOptional got;
  uint8_t wire[9];
  uint8_t again[9];

  any_md_entry_px_decimal_optional(&sent);
  assert(encode_md_entry_px_decimal_optional(&sent, wire, 0) == 9);
  assert(decode_md_entry_px_decimal_optional(&got, wire, 0) == 9);
  equal_md_entry_px_decimal_optional(&got, &sent);

  for (size_t i = 0; i < 9; i++) { wire[i] = arbitrary(); }
  assert(decode_md_entry_px_decimal_optional(&got, wire, 0) == 9);
  assert(encode_md_entry_px_decimal_optional(&got, again, 0) == 9);
  for (size_t i = 0; i < 9; i++) { assert(again[i] == wire[i]); }
}

/* ---- Cal Fut Px Optional: 9 bytes -------------------------------------------- */

/* Number of entries in Market Data message. */
typedef struct {
  uint8_t mantissa[8];        /* bytes 0 to 7 */
  uint8_t exponent_optional;  /* byte 8 */
} CalFutPxOptional;

/* any Cal Fut Px Optional at all: every byte one the checker chooses */
static void any_cal_fut_px_optional(CalFutPxOptional *record) {
  for (size_t i = 0; i < 8; i++) { record->mantissa[i] = arbitrary(); }
  record->exponent_optional = arbitrary();
}

/* Cal Fut Px Optional to the wire: 9 bytes from at, returning where the next byte goes */
static size_t encode_cal_fut_px_optional(const CalFutPxOptional *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->mantissa[i]; }
  wire[at++] = record->exponent_optional;

  return at;
}

/* Cal Fut Px Optional off the wire: 9 bytes from at, returning where the next byte lies */
static size_t decode_cal_fut_px_optional(CalFutPxOptional *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->mantissa[i] = wire[at++]; }
  record->exponent_optional = wire[at++];

  return at;
}

/* what was read of Cal Fut Px Optional is what was written, byte for byte */
static void equal_cal_fut_px_optional(const CalFutPxOptional *read, const CalFutPxOptional *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->mantissa[i] == written->mantissa[i]); }
  assert(read->exponent_optional == written->exponent_optional);
}

/* Cal Fut Px Optional: written and read back, then read and written back */
static void check_cal_fut_px_optional(void) {
  CalFutPxOptional sent;
  CalFutPxOptional got;
  uint8_t wire[9];
  uint8_t again[9];

  any_cal_fut_px_optional(&sent);
  assert(encode_cal_fut_px_optional(&sent, wire, 0) == 9);
  assert(decode_cal_fut_px_optional(&got, wire, 0) == 9);
  equal_cal_fut_px_optional(&got, &sent);

  for (size_t i = 0; i < 9; i++) { wire[i] = arbitrary(); }
  assert(decode_cal_fut_px_optional(&got, wire, 0) == 9);
  assert(encode_cal_fut_px_optional(&got, again, 0) == 9);
  for (size_t i = 0; i < 9; i++) { assert(again[i] == wire[i]); }
}

/* ---- Coupon Rate Optional: 5 bytes ------------------------------------------- */

/* Number of entries in Market Data message. */
typedef struct {
  uint8_t mantissa_32[4];     /* bytes 0 to 3 */
  uint8_t exponent_optional;  /* byte 4 */
} CouponRateOptional;

/* any Coupon Rate Optional at all: every byte one the checker chooses */
static void any_coupon_rate_optional(CouponRateOptional *record) {
  for (size_t i = 0; i < 4; i++) { record->mantissa_32[i] = arbitrary(); }
  record->exponent_optional = arbitrary();
}

/* Coupon Rate Optional to the wire: 5 bytes from at, returning where the next byte goes */
static size_t encode_coupon_rate_optional(const CouponRateOptional *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->mantissa_32[i]; }
  wire[at++] = record->exponent_optional;

  return at;
}

/* Coupon Rate Optional off the wire: 5 bytes from at, returning where the next byte lies */
static size_t decode_coupon_rate_optional(CouponRateOptional *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->mantissa_32[i] = wire[at++]; }
  record->exponent_optional = wire[at++];

  return at;
}

/* what was read of Coupon Rate Optional is what was written, byte for byte */
static void equal_coupon_rate_optional(const CouponRateOptional *read, const CouponRateOptional *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->mantissa_32[i] == written->mantissa_32[i]); }
  assert(read->exponent_optional == written->exponent_optional);
}

/* Coupon Rate Optional: written and read back, then read and written back */
static void check_coupon_rate_optional(void) {
  CouponRateOptional sent;
  CouponRateOptional got;
  uint8_t wire[5];
  uint8_t again[5];

  any_coupon_rate_optional(&sent);
  assert(encode_coupon_rate_optional(&sent, wire, 0) == 5);
  assert(decode_coupon_rate_optional(&got, wire, 0) == 5);
  equal_coupon_rate_optional(&got, &sent);

  for (size_t i = 0; i < 5; i++) { wire[i] = arbitrary(); }
  assert(decode_coupon_rate_optional(&got, wire, 0) == 5);
  assert(encode_coupon_rate_optional(&got, again, 0) == 5);
  for (size_t i = 0; i < 5; i++) { assert(again[i] == wire[i]); }
}

/* ---- Fair Coupon Pct: 9 bytes ------------------------------------------------ */

/* Number of entries in Market Data message. */
typedef struct {
  uint8_t mantissa[8];        /* bytes 0 to 7 */
  uint8_t exponent_optional;  /* byte 8 */
} FairCouponPct;

/* any Fair Coupon Pct at all: every byte one the checker chooses */
static void any_fair_coupon_pct(FairCouponPct *record) {
  for (size_t i = 0; i < 8; i++) { record->mantissa[i] = arbitrary(); }
  record->exponent_optional = arbitrary();
}

/* Fair Coupon Pct to the wire: 9 bytes from at, returning where the next byte goes */
static size_t encode_fair_coupon_pct(const FairCouponPct *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->mantissa[i]; }
  wire[at++] = record->exponent_optional;

  return at;
}

/* Fair Coupon Pct off the wire: 9 bytes from at, returning where the next byte lies */
static size_t decode_fair_coupon_pct(FairCouponPct *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->mantissa[i] = wire[at++]; }
  record->exponent_optional = wire[at++];

  return at;
}

/* what was read of Fair Coupon Pct is what was written, byte for byte */
static void equal_fair_coupon_pct(const FairCouponPct *read, const FairCouponPct *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->mantissa[i] == written->mantissa[i]); }
  assert(read->exponent_optional == written->exponent_optional);
}

/* Fair Coupon Pct: written and read back, then read and written back */
static void check_fair_coupon_pct(void) {
  FairCouponPct sent;
  FairCouponPct got;
  uint8_t wire[9];
  uint8_t again[9];

  any_fair_coupon_pct(&sent);
  assert(encode_fair_coupon_pct(&sent, wire, 0) == 9);
  assert(decode_fair_coupon_pct(&got, wire, 0) == 9);
  equal_fair_coupon_pct(&got, &sent);

  for (size_t i = 0; i < 9; i++) { wire[i] = arbitrary(); }
  assert(decode_fair_coupon_pct(&got, wire, 0) == 9);
  assert(encode_fair_coupon_pct(&got, again, 0) == 9);
  for (size_t i = 0; i < 9; i++) { assert(again[i] == wire[i]); }
}

/* ---- Leg Purchase Rate: 9 bytes ---------------------------------------------- */

/* Number of entries in Market Data message. */
typedef struct {
  uint8_t mantissa[8];        /* bytes 0 to 7 */
  uint8_t exponent_optional;  /* byte 8 */
} LegPurchaseRate;

/* any Leg Purchase Rate at all: every byte one the checker chooses */
static void any_leg_purchase_rate(LegPurchaseRate *record) {
  for (size_t i = 0; i < 8; i++) { record->mantissa[i] = arbitrary(); }
  record->exponent_optional = arbitrary();
}

/* Leg Purchase Rate to the wire: 9 bytes from at, returning where the next byte goes */
static size_t encode_leg_purchase_rate(const LegPurchaseRate *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->mantissa[i]; }
  wire[at++] = record->exponent_optional;

  return at;
}

/* Leg Purchase Rate off the wire: 9 bytes from at, returning where the next byte lies */
static size_t decode_leg_purchase_rate(LegPurchaseRate *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->mantissa[i] = wire[at++]; }
  record->exponent_optional = wire[at++];

  return at;
}

/* what was read of Leg Purchase Rate is what was written, byte for byte */
static void equal_leg_purchase_rate(const LegPurchaseRate *read, const LegPurchaseRate *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->mantissa[i] == written->mantissa[i]); }
  assert(read->exponent_optional == written->exponent_optional);
}

/* Leg Purchase Rate: written and read back, then read and written back */
static void check_leg_purchase_rate(void) {
  LegPurchaseRate sent;
  LegPurchaseRate got;
  uint8_t wire[9];
  uint8_t again[9];

  any_leg_purchase_rate(&sent);
  assert(encode_leg_purchase_rate(&sent, wire, 0) == 9);
  assert(decode_leg_purchase_rate(&got, wire, 0) == 9);
  equal_leg_purchase_rate(&got, &sent);

  for (size_t i = 0; i < 9; i++) { wire[i] = arbitrary(); }
  assert(decode_leg_purchase_rate(&got, wire, 0) == 9);
  assert(encode_leg_purchase_rate(&got, again, 0) == 9);
  for (size_t i = 0; i < 9; i++) { assert(again[i] == wire[i]); }
}

/* ---- Fixed Npv: 9 bytes ------------------------------------------------------ */

/* Number of entries in Market Data message. */
typedef struct {
  uint8_t mantissa[8];        /* bytes 0 to 7 */
  uint8_t exponent_optional;  /* byte 8 */
} FixedNpv;

/* any Fixed Npv at all: every byte one the checker chooses */
static void any_fixed_npv(FixedNpv *record) {
  for (size_t i = 0; i < 8; i++) { record->mantissa[i] = arbitrary(); }
  record->exponent_optional = arbitrary();
}

/* Fixed Npv to the wire: 9 bytes from at, returning where the next byte goes */
static size_t encode_fixed_npv(const FixedNpv *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->mantissa[i]; }
  wire[at++] = record->exponent_optional;

  return at;
}

/* Fixed Npv off the wire: 9 bytes from at, returning where the next byte lies */
static size_t decode_fixed_npv(FixedNpv *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->mantissa[i] = wire[at++]; }
  record->exponent_optional = wire[at++];

  return at;
}

/* what was read of Fixed Npv is what was written, byte for byte */
static void equal_fixed_npv(const FixedNpv *read, const FixedNpv *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->mantissa[i] == written->mantissa[i]); }
  assert(read->exponent_optional == written->exponent_optional);
}

/* Fixed Npv: written and read back, then read and written back */
static void check_fixed_npv(void) {
  FixedNpv sent;
  FixedNpv got;
  uint8_t wire[9];
  uint8_t again[9];

  any_fixed_npv(&sent);
  assert(encode_fixed_npv(&sent, wire, 0) == 9);
  assert(decode_fixed_npv(&got, wire, 0) == 9);
  equal_fixed_npv(&got, &sent);

  for (size_t i = 0; i < 9; i++) { wire[i] = arbitrary(); }
  assert(decode_fixed_npv(&got, wire, 0) == 9);
  assert(encode_fixed_npv(&got, again, 0) == 9);
  for (size_t i = 0; i < 9; i++) { assert(again[i] == wire[i]); }
}

/* ---- Float Npv: 9 bytes ------------------------------------------------------ */

/* Number of entries in Market Data message. */
typedef struct {
  uint8_t mantissa[8];        /* bytes 0 to 7 */
  uint8_t exponent_optional;  /* byte 8 */
} FloatNpv;

/* any Float Npv at all: every byte one the checker chooses */
static void any_float_npv(FloatNpv *record) {
  for (size_t i = 0; i < 8; i++) { record->mantissa[i] = arbitrary(); }
  record->exponent_optional = arbitrary();
}

/* Float Npv to the wire: 9 bytes from at, returning where the next byte goes */
static size_t encode_float_npv(const FloatNpv *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->mantissa[i]; }
  wire[at++] = record->exponent_optional;

  return at;
}

/* Float Npv off the wire: 9 bytes from at, returning where the next byte lies */
static size_t decode_float_npv(FloatNpv *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->mantissa[i] = wire[at++]; }
  record->exponent_optional = wire[at++];

  return at;
}

/* what was read of Float Npv is what was written, byte for byte */
static void equal_float_npv(const FloatNpv *read, const FloatNpv *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->mantissa[i] == written->mantissa[i]); }
  assert(read->exponent_optional == written->exponent_optional);
}

/* Float Npv: written and read back, then read and written back */
static void check_float_npv(void) {
  FloatNpv sent;
  FloatNpv got;
  uint8_t wire[9];
  uint8_t again[9];

  any_float_npv(&sent);
  assert(encode_float_npv(&sent, wire, 0) == 9);
  assert(decode_float_npv(&got, wire, 0) == 9);
  equal_float_npv(&got, &sent);

  for (size_t i = 0; i < 9; i++) { wire[i] = arbitrary(); }
  assert(decode_float_npv(&got, wire, 0) == 9);
  assert(encode_float_npv(&got, again, 0) == 9);
  for (size_t i = 0; i < 9; i++) { assert(again[i] == wire[i]); }
}

/* ---- Npv: 9 bytes ------------------------------------------------------------ */

/* Number of entries in Market Data message. */
typedef struct {
  uint8_t mantissa[8];        /* bytes 0 to 7 */
  uint8_t exponent_optional;  /* byte 8 */
} Npv;

/* any Npv at all: every byte one the checker chooses */
static void any_npv(Npv *record) {
  for (size_t i = 0; i < 8; i++) { record->mantissa[i] = arbitrary(); }
  record->exponent_optional = arbitrary();
}

/* Npv to the wire: 9 bytes from at, returning where the next byte goes */
static size_t encode_npv(const Npv *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->mantissa[i]; }
  wire[at++] = record->exponent_optional;

  return at;
}

/* Npv off the wire: 9 bytes from at, returning where the next byte lies */
static size_t decode_npv(Npv *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->mantissa[i] = wire[at++]; }
  record->exponent_optional = wire[at++];

  return at;
}

/* what was read of Npv is what was written, byte for byte */
static void equal_npv(const Npv *read, const Npv *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->mantissa[i] == written->mantissa[i]); }
  assert(read->exponent_optional == written->exponent_optional);
}

/* Npv: written and read back, then read and written back */
static void check_npv(void) {
  Npv sent;
  Npv got;
  uint8_t wire[9];
  uint8_t again[9];

  any_npv(&sent);
  assert(encode_npv(&sent, wire, 0) == 9);
  assert(decode_npv(&got, wire, 0) == 9);
  equal_npv(&got, &sent);

  for (size_t i = 0; i < 9; i++) { wire[i] = arbitrary(); }
  assert(decode_npv(&got, wire, 0) == 9);
  assert(encode_npv(&got, again, 0) == 9);
  for (size_t i = 0; i < 9; i++) { assert(again[i] == wire[i]); }
}

/* ---- Accrued Coupons: 9 bytes ------------------------------------------------ */

/* Number of entries in Market Data message. */
typedef struct {
  uint8_t mantissa[8];        /* bytes 0 to 7 */
  uint8_t exponent_optional;  /* byte 8 */
} AccruedCoupons;

/* any Accrued Coupons at all: every byte one the checker chooses */
static void any_accrued_coupons(AccruedCoupons *record) {
  for (size_t i = 0; i < 8; i++) { record->mantissa[i] = arbitrary(); }
  record->exponent_optional = arbitrary();
}

/* Accrued Coupons to the wire: 9 bytes from at, returning where the next byte goes */
static size_t encode_accrued_coupons(const AccruedCoupons *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->mantissa[i]; }
  wire[at++] = record->exponent_optional;

  return at;
}

/* Accrued Coupons off the wire: 9 bytes from at, returning where the next byte lies */
static size_t decode_accrued_coupons(AccruedCoupons *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->mantissa[i] = wire[at++]; }
  record->exponent_optional = wire[at++];

  return at;
}

/* what was read of Accrued Coupons is what was written, byte for byte */
static void equal_accrued_coupons(const AccruedCoupons *read, const AccruedCoupons *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->mantissa[i] == written->mantissa[i]); }
  assert(read->exponent_optional == written->exponent_optional);
}

/* Accrued Coupons: written and read back, then read and written back */
static void check_accrued_coupons(void) {
  AccruedCoupons sent;
  AccruedCoupons got;
  uint8_t wire[9];
  uint8_t again[9];

  any_accrued_coupons(&sent);
  assert(encode_accrued_coupons(&sent, wire, 0) == 9);
  assert(decode_accrued_coupons(&got, wire, 0) == 9);
  equal_accrued_coupons(&got, &sent);

  for (size_t i = 0; i < 9; i++) { wire[i] = arbitrary(); }
  assert(decode_accrued_coupons(&got, wire, 0) == 9);
  assert(encode_accrued_coupons(&got, again, 0) == 9);
  for (size_t i = 0; i < 9; i++) { assert(again[i] == wire[i]); }
}

/* ---- Daily Incremental Eris Pai: 9 bytes ------------------------------------- */

/* Number of entries in Market Data message. */
typedef struct {
  uint8_t mantissa[8];        /* bytes 0 to 7 */
  uint8_t exponent_optional;  /* byte 8 */
} DailyIncrementalErisPai;

/* any Daily Incremental Eris Pai at all: every byte one the checker chooses */
static void any_daily_incremental_eris_pai(DailyIncrementalErisPai *record) {
  for (size_t i = 0; i < 8; i++) { record->mantissa[i] = arbitrary(); }
  record->exponent_optional = arbitrary();
}

/* Daily Incremental Eris Pai to the wire: 9 bytes from at, returning where the next byte goes */
static size_t encode_daily_incremental_eris_pai(const DailyIncrementalErisPai *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->mantissa[i]; }
  wire[at++] = record->exponent_optional;

  return at;
}

/* Daily Incremental Eris Pai off the wire: 9 bytes from at, returning where the next byte lies */
static size_t decode_daily_incremental_eris_pai(DailyIncrementalErisPai *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->mantissa[i] = wire[at++]; }
  record->exponent_optional = wire[at++];

  return at;
}

/* what was read of Daily Incremental Eris Pai is what was written, byte for byte */
static void equal_daily_incremental_eris_pai(const DailyIncrementalErisPai *read, const DailyIncrementalErisPai *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->mantissa[i] == written->mantissa[i]); }
  assert(read->exponent_optional == written->exponent_optional);
}

/* Daily Incremental Eris Pai: written and read back, then read and written back */
static void check_daily_incremental_eris_pai(void) {
  DailyIncrementalErisPai sent;
  DailyIncrementalErisPai got;
  uint8_t wire[9];
  uint8_t again[9];

  any_daily_incremental_eris_pai(&sent);
  assert(encode_daily_incremental_eris_pai(&sent, wire, 0) == 9);
  assert(decode_daily_incremental_eris_pai(&got, wire, 0) == 9);
  equal_daily_incremental_eris_pai(&got, &sent);

  for (size_t i = 0; i < 9; i++) { wire[i] = arbitrary(); }
  assert(decode_daily_incremental_eris_pai(&got, wire, 0) == 9);
  assert(encode_daily_incremental_eris_pai(&got, again, 0) == 9);
  for (size_t i = 0; i < 9; i++) { assert(again[i] == wire[i]); }
}

/* ---- Eris Pai: 9 bytes ------------------------------------------------------- */

/* Number of entries in Market Data message. */
typedef struct {
  uint8_t mantissa[8];        /* bytes 0 to 7 */
  uint8_t exponent_optional;  /* byte 8 */
} ErisPai;

/* any Eris Pai at all: every byte one the checker chooses */
static void any_eris_pai(ErisPai *record) {
  for (size_t i = 0; i < 8; i++) { record->mantissa[i] = arbitrary(); }
  record->exponent_optional = arbitrary();
}

/* Eris Pai to the wire: 9 bytes from at, returning where the next byte goes */
static size_t encode_eris_pai(const ErisPai *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->mantissa[i]; }
  wire[at++] = record->exponent_optional;

  return at;
}

/* Eris Pai off the wire: 9 bytes from at, returning where the next byte lies */
static size_t decode_eris_pai(ErisPai *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->mantissa[i] = wire[at++]; }
  record->exponent_optional = wire[at++];

  return at;
}

/* what was read of Eris Pai is what was written, byte for byte */
static void equal_eris_pai(const ErisPai *read, const ErisPai *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->mantissa[i] == written->mantissa[i]); }
  assert(read->exponent_optional == written->exponent_optional);
}

/* Eris Pai: written and read back, then read and written back */
static void check_eris_pai(void) {
  ErisPai sent;
  ErisPai got;
  uint8_t wire[9];
  uint8_t again[9];

  any_eris_pai(&sent);
  assert(encode_eris_pai(&sent, wire, 0) == 9);
  assert(decode_eris_pai(&got, wire, 0) == 9);
  equal_eris_pai(&got, &sent);

  for (size_t i = 0; i < 9; i++) { wire[i] = arbitrary(); }
  assert(decode_eris_pai(&got, wire, 0) == 9);
  assert(encode_eris_pai(&got, again, 0) == 9);
  for (size_t i = 0; i < 9; i++) { assert(again[i] == wire[i]); }
}

/* ---- Fed Funds Rate: 9 bytes ------------------------------------------------- */

/* Number of entries in Market Data message. */
typedef struct {
  uint8_t mantissa[8];        /* bytes 0 to 7 */
  uint8_t exponent_optional;  /* byte 8 */
} FedFundsRate;

/* any Fed Funds Rate at all: every byte one the checker chooses */
static void any_fed_funds_rate(FedFundsRate *record) {
  for (size_t i = 0; i < 8; i++) { record->mantissa[i] = arbitrary(); }
  record->exponent_optional = arbitrary();
}

/* Fed Funds Rate to the wire: 9 bytes from at, returning where the next byte goes */
static size_t encode_fed_funds_rate(const FedFundsRate *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->mantissa[i]; }
  wire[at++] = record->exponent_optional;

  return at;
}

/* Fed Funds Rate off the wire: 9 bytes from at, returning where the next byte lies */
static size_t decode_fed_funds_rate(FedFundsRate *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->mantissa[i] = wire[at++]; }
  record->exponent_optional = wire[at++];

  return at;
}

/* what was read of Fed Funds Rate is what was written, byte for byte */
static void equal_fed_funds_rate(const FedFundsRate *read, const FedFundsRate *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->mantissa[i] == written->mantissa[i]); }
  assert(read->exponent_optional == written->exponent_optional);
}

/* Fed Funds Rate: written and read back, then read and written back */
static void check_fed_funds_rate(void) {
  FedFundsRate sent;
  FedFundsRate got;
  uint8_t wire[9];
  uint8_t again[9];

  any_fed_funds_rate(&sent);
  assert(encode_fed_funds_rate(&sent, wire, 0) == 9);
  assert(decode_fed_funds_rate(&got, wire, 0) == 9);
  equal_fed_funds_rate(&got, &sent);

  for (size_t i = 0; i < 9; i++) { wire[i] = arbitrary(); }
  assert(decode_fed_funds_rate(&got, wire, 0) == 9);
  assert(encode_fed_funds_rate(&got, again, 0) == 9);
  for (size_t i = 0; i < 9; i++) { assert(again[i] == wire[i]); }
}

/* ---- Min Price Increment Optional: 9 bytes ----------------------------------- */

/* Number of entries in Market Data message. */
typedef struct {
  uint8_t mantissa[8];        /* bytes 0 to 7 */
  uint8_t exponent_optional;  /* byte 8 */
} MinPriceIncrementOptional;

/* any Min Price Increment Optional at all: every byte one the checker chooses */
static void any_min_price_increment_optional(MinPriceIncrementOptional *record) {
  for (size_t i = 0; i < 8; i++) { record->mantissa[i] = arbitrary(); }
  record->exponent_optional = arbitrary();
}

/* Min Price Increment Optional to the wire: 9 bytes from at, returning where the next byte goes */
static size_t encode_min_price_increment_optional(const MinPriceIncrementOptional *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->mantissa[i]; }
  wire[at++] = record->exponent_optional;

  return at;
}

/* Min Price Increment Optional off the wire: 9 bytes from at, returning where the next byte lies */
static size_t decode_min_price_increment_optional(MinPriceIncrementOptional *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->mantissa[i] = wire[at++]; }
  record->exponent_optional = wire[at++];

  return at;
}

/* what was read of Min Price Increment Optional is what was written, byte for byte */
static void equal_min_price_increment_optional(const MinPriceIncrementOptional *read, const MinPriceIncrementOptional *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->mantissa[i] == written->mantissa[i]); }
  assert(read->exponent_optional == written->exponent_optional);
}

/* Min Price Increment Optional: written and read back, then read and written back */
static void check_min_price_increment_optional(void) {
  MinPriceIncrementOptional sent;
  MinPriceIncrementOptional got;
  uint8_t wire[9];
  uint8_t again[9];

  any_min_price_increment_optional(&sent);
  assert(encode_min_price_increment_optional(&sent, wire, 0) == 9);
  assert(decode_min_price_increment_optional(&got, wire, 0) == 9);
  equal_min_price_increment_optional(&got, &sent);

  for (size_t i = 0; i < 9; i++) { wire[i] = arbitrary(); }
  assert(decode_min_price_increment_optional(&got, wire, 0) == 9);
  assert(encode_min_price_increment_optional(&got, again, 0) == 9);
  for (size_t i = 0; i < 9; i++) { assert(again[i] == wire[i]); }
}

/* ---- Fixed Payment: 9 bytes -------------------------------------------------- */

/* Number of entries in Market Data message. */
typedef struct {
  uint8_t mantissa[8];        /* bytes 0 to 7 */
  uint8_t exponent_optional;  /* byte 8 */
} FixedPayment;

/* any Fixed Payment at all: every byte one the checker chooses */
static void any_fixed_payment(FixedPayment *record) {
  for (size_t i = 0; i < 8; i++) { record->mantissa[i] = arbitrary(); }
  record->exponent_optional = arbitrary();
}

/* Fixed Payment to the wire: 9 bytes from at, returning where the next byte goes */
static size_t encode_fixed_payment(const FixedPayment *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->mantissa[i]; }
  wire[at++] = record->exponent_optional;

  return at;
}

/* Fixed Payment off the wire: 9 bytes from at, returning where the next byte lies */
static size_t decode_fixed_payment(FixedPayment *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->mantissa[i] = wire[at++]; }
  record->exponent_optional = wire[at++];

  return at;
}

/* what was read of Fixed Payment is what was written, byte for byte */
static void equal_fixed_payment(const FixedPayment *read, const FixedPayment *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->mantissa[i] == written->mantissa[i]); }
  assert(read->exponent_optional == written->exponent_optional);
}

/* Fixed Payment: written and read back, then read and written back */
static void check_fixed_payment(void) {
  FixedPayment sent;
  FixedPayment got;
  uint8_t wire[9];
  uint8_t again[9];

  any_fixed_payment(&sent);
  assert(encode_fixed_payment(&sent, wire, 0) == 9);
  assert(decode_fixed_payment(&got, wire, 0) == 9);
  equal_fixed_payment(&got, &sent);

  for (size_t i = 0; i < 9; i++) { wire[i] = arbitrary(); }
  assert(decode_fixed_payment(&got, wire, 0) == 9);
  assert(encode_fixed_payment(&got, again, 0) == 9);
  for (size_t i = 0; i < 9; i++) { assert(again[i] == wire[i]); }
}

/* ---- Floating Payment: 9 bytes ----------------------------------------------- */

/* Number of entries in Market Data message. */
typedef struct {
  uint8_t mantissa[8];        /* bytes 0 to 7 */
  uint8_t exponent_optional;  /* byte 8 */
} FloatingPayment;

/* any Floating Payment at all: every byte one the checker chooses */
static void any_floating_payment(FloatingPayment *record) {
  for (size_t i = 0; i < 8; i++) { record->mantissa[i] = arbitrary(); }
  record->exponent_optional = arbitrary();
}

/* Floating Payment to the wire: 9 bytes from at, returning where the next byte goes */
static size_t encode_floating_payment(const FloatingPayment *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->mantissa[i]; }
  wire[at++] = record->exponent_optional;

  return at;
}

/* Floating Payment off the wire: 9 bytes from at, returning where the next byte lies */
static size_t decode_floating_payment(FloatingPayment *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->mantissa[i] = wire[at++]; }
  record->exponent_optional = wire[at++];

  return at;
}

/* what was read of Floating Payment is what was written, byte for byte */
static void equal_floating_payment(const FloatingPayment *read, const FloatingPayment *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->mantissa[i] == written->mantissa[i]); }
  assert(read->exponent_optional == written->exponent_optional);
}

/* Floating Payment: written and read back, then read and written back */
static void check_floating_payment(void) {
  FloatingPayment sent;
  FloatingPayment got;
  uint8_t wire[9];
  uint8_t again[9];

  any_floating_payment(&sent);
  assert(encode_floating_payment(&sent, wire, 0) == 9);
  assert(decode_floating_payment(&got, wire, 0) == 9);
  equal_floating_payment(&got, &sent);

  for (size_t i = 0; i < 9; i++) { wire[i] = arbitrary(); }
  assert(decode_floating_payment(&got, wire, 0) == 9);
  assert(encode_floating_payment(&got, again, 0) == 9);
  for (size_t i = 0; i < 9; i++) { assert(again[i] == wire[i]); }
}

/* ---- Next Fixed Payment Amount: 9 bytes -------------------------------------- */

/* Number of entries in Market Data message. */
typedef struct {
  uint8_t mantissa[8];        /* bytes 0 to 7 */
  uint8_t exponent_optional;  /* byte 8 */
} NextFixedPaymentAmount;

/* any Next Fixed Payment Amount at all: every byte one the checker chooses */
static void any_next_fixed_payment_amount(NextFixedPaymentAmount *record) {
  for (size_t i = 0; i < 8; i++) { record->mantissa[i] = arbitrary(); }
  record->exponent_optional = arbitrary();
}

/* Next Fixed Payment Amount to the wire: 9 bytes from at, returning where the next byte goes */
static size_t encode_next_fixed_payment_amount(const NextFixedPaymentAmount *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->mantissa[i]; }
  wire[at++] = record->exponent_optional;

  return at;
}

/* Next Fixed Payment Amount off the wire: 9 bytes from at, returning where the next byte lies */
static size_t decode_next_fixed_payment_amount(NextFixedPaymentAmount *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->mantissa[i] = wire[at++]; }
  record->exponent_optional = wire[at++];

  return at;
}

/* what was read of Next Fixed Payment Amount is what was written, byte for byte */
static void equal_next_fixed_payment_amount(const NextFixedPaymentAmount *read, const NextFixedPaymentAmount *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->mantissa[i] == written->mantissa[i]); }
  assert(read->exponent_optional == written->exponent_optional);
}

/* Next Fixed Payment Amount: written and read back, then read and written back */
static void check_next_fixed_payment_amount(void) {
  NextFixedPaymentAmount sent;
  NextFixedPaymentAmount got;
  uint8_t wire[9];
  uint8_t again[9];

  any_next_fixed_payment_amount(&sent);
  assert(encode_next_fixed_payment_amount(&sent, wire, 0) == 9);
  assert(decode_next_fixed_payment_amount(&got, wire, 0) == 9);
  equal_next_fixed_payment_amount(&got, &sent);

  for (size_t i = 0; i < 9; i++) { wire[i] = arbitrary(); }
  assert(decode_next_fixed_payment_amount(&got, wire, 0) == 9);
  assert(encode_next_fixed_payment_amount(&got, again, 0) == 9);
  for (size_t i = 0; i < 9; i++) { assert(again[i] == wire[i]); }
}

/* ---- Next Floating Payment Amount: 9 bytes ----------------------------------- */

/* Number of entries in Market Data message. */
typedef struct {
  uint8_t mantissa[8];        /* bytes 0 to 7 */
  uint8_t exponent_optional;  /* byte 8 */
} NextFloatingPaymentAmount;

/* any Next Floating Payment Amount at all: every byte one the checker chooses */
static void any_next_floating_payment_amount(NextFloatingPaymentAmount *record) {
  for (size_t i = 0; i < 8; i++) { record->mantissa[i] = arbitrary(); }
  record->exponent_optional = arbitrary();
}

/* Next Floating Payment Amount to the wire: 9 bytes from at, returning where the next byte goes */
static size_t encode_next_floating_payment_amount(const NextFloatingPaymentAmount *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->mantissa[i]; }
  wire[at++] = record->exponent_optional;

  return at;
}

/* Next Floating Payment Amount off the wire: 9 bytes from at, returning where the next byte lies */
static size_t decode_next_floating_payment_amount(NextFloatingPaymentAmount *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->mantissa[i] = wire[at++]; }
  record->exponent_optional = wire[at++];

  return at;
}

/* what was read of Next Floating Payment Amount is what was written, byte for byte */
static void equal_next_floating_payment_amount(const NextFloatingPaymentAmount *read, const NextFloatingPaymentAmount *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->mantissa[i] == written->mantissa[i]); }
  assert(read->exponent_optional == written->exponent_optional);
}

/* Next Floating Payment Amount: written and read back, then read and written back */
static void check_next_floating_payment_amount(void) {
  NextFloatingPaymentAmount sent;
  NextFloatingPaymentAmount got;
  uint8_t wire[9];
  uint8_t again[9];

  any_next_floating_payment_amount(&sent);
  assert(encode_next_floating_payment_amount(&sent, wire, 0) == 9);
  assert(decode_next_floating_payment_amount(&got, wire, 0) == 9);
  equal_next_floating_payment_amount(&got, &sent);

  for (size_t i = 0; i < 9; i++) { wire[i] = arbitrary(); }
  assert(decode_next_floating_payment_amount(&got, wire, 0) == 9);
  assert(encode_next_floating_payment_amount(&got, again, 0) == 9);
  for (size_t i = 0; i < 9; i++) { assert(again[i] == wire[i]); }
}

/* ---- Previous Eris Pai: 9 bytes ---------------------------------------------- */

/* Number of entries in Market Data message. */
typedef struct {
  uint8_t mantissa[8];        /* bytes 0 to 7 */
  uint8_t exponent_optional;  /* byte 8 */
} PreviousErisPai;

/* any Previous Eris Pai at all: every byte one the checker chooses */
static void any_previous_eris_pai(PreviousErisPai *record) {
  for (size_t i = 0; i < 8; i++) { record->mantissa[i] = arbitrary(); }
  record->exponent_optional = arbitrary();
}

/* Previous Eris Pai to the wire: 9 bytes from at, returning where the next byte goes */
static size_t encode_previous_eris_pai(const PreviousErisPai *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->mantissa[i]; }
  wire[at++] = record->exponent_optional;

  return at;
}

/* Previous Eris Pai off the wire: 9 bytes from at, returning where the next byte lies */
static size_t decode_previous_eris_pai(PreviousErisPai *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->mantissa[i] = wire[at++]; }
  record->exponent_optional = wire[at++];

  return at;
}

/* what was read of Previous Eris Pai is what was written, byte for byte */
static void equal_previous_eris_pai(const PreviousErisPai *read, const PreviousErisPai *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->mantissa[i] == written->mantissa[i]); }
  assert(read->exponent_optional == written->exponent_optional);
}

/* Previous Eris Pai: written and read back, then read and written back */
static void check_previous_eris_pai(void) {
  PreviousErisPai sent;
  PreviousErisPai got;
  uint8_t wire[9];
  uint8_t again[9];

  any_previous_eris_pai(&sent);
  assert(encode_previous_eris_pai(&sent, wire, 0) == 9);
  assert(decode_previous_eris_pai(&got, wire, 0) == 9);
  equal_previous_eris_pai(&got, &sent);

  for (size_t i = 0; i < 9; i++) { wire[i] = arbitrary(); }
  assert(decode_previous_eris_pai(&got, wire, 0) == 9);
  assert(encode_previous_eris_pai(&got, again, 0) == 9);
  for (size_t i = 0; i < 9; i++) { assert(again[i] == wire[i]); }
}

/* ---- Leg Contract Multiplier: 9 bytes ---------------------------------------- */

/* Number of entries in Market Data message. */
typedef struct {
  uint8_t mantissa[8];        /* bytes 0 to 7 */
  uint8_t exponent_optional;  /* byte 8 */
} LegContractMultiplier;

/* any Leg Contract Multiplier at all: every byte one the checker chooses */
static void any_leg_contract_multiplier(LegContractMultiplier *record) {
  for (size_t i = 0; i < 8; i++) { record->mantissa[i] = arbitrary(); }
  record->exponent_optional = arbitrary();
}

/* Leg Contract Multiplier to the wire: 9 bytes from at, returning where the next byte goes */
static size_t encode_leg_contract_multiplier(const LegContractMultiplier *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->mantissa[i]; }
  wire[at++] = record->exponent_optional;

  return at;
}

/* Leg Contract Multiplier off the wire: 9 bytes from at, returning where the next byte lies */
static size_t decode_leg_contract_multiplier(LegContractMultiplier *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->mantissa[i] = wire[at++]; }
  record->exponent_optional = wire[at++];

  return at;
}

/* what was read of Leg Contract Multiplier is what was written, byte for byte */
static void equal_leg_contract_multiplier(const LegContractMultiplier *read, const LegContractMultiplier *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->mantissa[i] == written->mantissa[i]); }
  assert(read->exponent_optional == written->exponent_optional);
}

/* Leg Contract Multiplier: written and read back, then read and written back */
static void check_leg_contract_multiplier(void) {
  LegContractMultiplier sent;
  LegContractMultiplier got;
  uint8_t wire[9];
  uint8_t again[9];

  any_leg_contract_multiplier(&sent);
  assert(encode_leg_contract_multiplier(&sent, wire, 0) == 9);
  assert(decode_leg_contract_multiplier(&got, wire, 0) == 9);
  equal_leg_contract_multiplier(&got, &sent);

  for (size_t i = 0; i < 9; i++) { wire[i] = arbitrary(); }
  assert(decode_leg_contract_multiplier(&got, wire, 0) == 9);
  assert(encode_leg_contract_multiplier(&got, again, 0) == 9);
  for (size_t i = 0; i < 9; i++) { assert(again[i] == wire[i]); }
}

/* ---- P V 01: 9 bytes --------------------------------------------------------- */

/* Number of entries in Market Data message. */
typedef struct {
  uint8_t mantissa[8];        /* bytes 0 to 7 */
  uint8_t exponent_optional;  /* byte 8 */
} PV01;

/* any P V 01 at all: every byte one the checker chooses */
static void any_p_v01(PV01 *record) {
  for (size_t i = 0; i < 8; i++) { record->mantissa[i] = arbitrary(); }
  record->exponent_optional = arbitrary();
}

/* P V 01 to the wire: 9 bytes from at, returning where the next byte goes */
static size_t encode_p_v01(const PV01 *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->mantissa[i]; }
  wire[at++] = record->exponent_optional;

  return at;
}

/* P V 01 off the wire: 9 bytes from at, returning where the next byte lies */
static size_t decode_p_v01(PV01 *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->mantissa[i] = wire[at++]; }
  record->exponent_optional = wire[at++];

  return at;
}

/* what was read of P V 01 is what was written, byte for byte */
static void equal_p_v01(const PV01 *read, const PV01 *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->mantissa[i] == written->mantissa[i]); }
  assert(read->exponent_optional == written->exponent_optional);
}

/* P V 01: written and read back, then read and written back */
static void check_p_v01(void) {
  PV01 sent;
  PV01 got;
  uint8_t wire[9];
  uint8_t again[9];

  any_p_v01(&sent);
  assert(encode_p_v01(&sent, wire, 0) == 9);
  assert(decode_p_v01(&got, wire, 0) == 9);
  equal_p_v01(&got, &sent);

  for (size_t i = 0; i < 9; i++) { wire[i] = arbitrary(); }
  assert(decode_p_v01(&got, wire, 0) == 9);
  assert(encode_p_v01(&got, again, 0) == 9);
  for (size_t i = 0; i < 9; i++) { assert(again[i] == wire[i]); }
}

/* ---- D V 01: 9 bytes --------------------------------------------------------- */

/* Number of entries in Market Data message. */
typedef struct {
  uint8_t mantissa[8];        /* bytes 0 to 7 */
  uint8_t exponent_optional;  /* byte 8 */
} DV01;

/* any D V 01 at all: every byte one the checker chooses */
static void any_d_v01(DV01 *record) {
  for (size_t i = 0; i < 8; i++) { record->mantissa[i] = arbitrary(); }
  record->exponent_optional = arbitrary();
}

/* D V 01 to the wire: 9 bytes from at, returning where the next byte goes */
static size_t encode_d_v01(const DV01 *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->mantissa[i]; }
  wire[at++] = record->exponent_optional;

  return at;
}

/* D V 01 off the wire: 9 bytes from at, returning where the next byte lies */
static size_t decode_d_v01(DV01 *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->mantissa[i] = wire[at++]; }
  record->exponent_optional = wire[at++];

  return at;
}

/* what was read of D V 01 is what was written, byte for byte */
static void equal_d_v01(const DV01 *read, const DV01 *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->mantissa[i] == written->mantissa[i]); }
  assert(read->exponent_optional == written->exponent_optional);
}

/* D V 01: written and read back, then read and written back */
static void check_d_v01(void) {
  DV01 sent;
  DV01 got;
  uint8_t wire[9];
  uint8_t again[9];

  any_d_v01(&sent);
  assert(encode_d_v01(&sent, wire, 0) == 9);
  assert(decode_d_v01(&got, wire, 0) == 9);
  equal_d_v01(&got, &sent);

  for (size_t i = 0; i < 9; i++) { wire[i] = arbitrary(); }
  assert(decode_d_v01(&got, wire, 0) == 9);
  assert(encode_d_v01(&got, again, 0) == 9);
  for (size_t i = 0; i < 9; i++) { assert(again[i] == wire[i]); }
}

/* ---- Settlement Npv: 9 bytes ------------------------------------------------- */

/* Number of entries in Market Data message. */
typedef struct {
  uint8_t mantissa[8];        /* bytes 0 to 7 */
  uint8_t exponent_optional;  /* byte 8 */
} SettlementNpv;

/* any Settlement Npv at all: every byte one the checker chooses */
static void any_settlement_npv(SettlementNpv *record) {
  for (size_t i = 0; i < 8; i++) { record->mantissa[i] = arbitrary(); }
  record->exponent_optional = arbitrary();
}

/* Settlement Npv to the wire: 9 bytes from at, returning where the next byte goes */
static size_t encode_settlement_npv(const SettlementNpv *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->mantissa[i]; }
  wire[at++] = record->exponent_optional;

  return at;
}

/* Settlement Npv off the wire: 9 bytes from at, returning where the next byte lies */
static size_t decode_settlement_npv(SettlementNpv *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->mantissa[i] = wire[at++]; }
  record->exponent_optional = wire[at++];

  return at;
}

/* what was read of Settlement Npv is what was written, byte for byte */
static void equal_settlement_npv(const SettlementNpv *read, const SettlementNpv *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->mantissa[i] == written->mantissa[i]); }
  assert(read->exponent_optional == written->exponent_optional);
}

/* Settlement Npv: written and read back, then read and written back */
static void check_settlement_npv(void) {
  SettlementNpv sent;
  SettlementNpv got;
  uint8_t wire[9];
  uint8_t again[9];

  any_settlement_npv(&sent);
  assert(encode_settlement_npv(&sent, wire, 0) == 9);
  assert(decode_settlement_npv(&got, wire, 0) == 9);
  equal_settlement_npv(&got, &sent);

  for (size_t i = 0; i < 9; i++) { wire[i] = arbitrary(); }
  assert(decode_settlement_npv(&got, wire, 0) == 9);
  assert(encode_settlement_npv(&got, again, 0) == 9);
  for (size_t i = 0; i < 9; i++) { assert(again[i] == wire[i]); }
}

/* ---- Final Settlement Futures Price: 9 bytes --------------------------------- */

/* Number of entries in Market Data message. */
typedef struct {
  uint8_t mantissa[8];        /* bytes 0 to 7 */
  uint8_t exponent_optional;  /* byte 8 */
} FinalSettlementFuturesPrice;

/* any Final Settlement Futures Price at all: every byte one the checker chooses */
static void any_final_settlement_futures_price(FinalSettlementFuturesPrice *record) {
  for (size_t i = 0; i < 8; i++) { record->mantissa[i] = arbitrary(); }
  record->exponent_optional = arbitrary();
}

/* Final Settlement Futures Price to the wire: 9 bytes from at, returning where the next byte goes */
static size_t encode_final_settlement_futures_price(const FinalSettlementFuturesPrice *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->mantissa[i]; }
  wire[at++] = record->exponent_optional;

  return at;
}

/* Final Settlement Futures Price off the wire: 9 bytes from at, returning where the next byte lies */
static size_t decode_final_settlement_futures_price(FinalSettlementFuturesPrice *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->mantissa[i] = wire[at++]; }
  record->exponent_optional = wire[at++];

  return at;
}

/* what was read of Final Settlement Futures Price is what was written, byte for byte */
static void equal_final_settlement_futures_price(const FinalSettlementFuturesPrice *read, const FinalSettlementFuturesPrice *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->mantissa[i] == written->mantissa[i]); }
  assert(read->exponent_optional == written->exponent_optional);
}

/* Final Settlement Futures Price: written and read back, then read and written back */
static void check_final_settlement_futures_price(void) {
  FinalSettlementFuturesPrice sent;
  FinalSettlementFuturesPrice got;
  uint8_t wire[9];
  uint8_t again[9];

  any_final_settlement_futures_price(&sent);
  assert(encode_final_settlement_futures_price(&sent, wire, 0) == 9);
  assert(decode_final_settlement_futures_price(&got, wire, 0) == 9);
  equal_final_settlement_futures_price(&got, &sent);

  for (size_t i = 0; i < 9; i++) { wire[i] = arbitrary(); }
  assert(decode_final_settlement_futures_price(&got, wire, 0) == 9);
  assert(encode_final_settlement_futures_price(&got, again, 0) == 9);
  for (size_t i = 0; i < 9; i++) { assert(again[i] == wire[i]); }
}

/* ---- Maturity Month Year: 5 bytes -------------------------------------------- */

/* Number of entries in Market Data message. */
typedef struct {
  uint8_t year[2];  /* bytes 0 to 1 */
  uint8_t month;    /* byte 2 */
  uint8_t day;      /* byte 3 */
  uint8_t week;     /* byte 4 */
} MaturityMonthYear;

/* any Maturity Month Year at all: every byte one the checker chooses */
static void any_maturity_month_year(MaturityMonthYear *record) {
  for (size_t i = 0; i < 2; i++) { record->year[i] = arbitrary(); }
  record->month = arbitrary();
  record->day = arbitrary();
  record->week = arbitrary();
}

/* Maturity Month Year to the wire: 5 bytes from at, returning where the next byte goes */
static size_t encode_maturity_month_year(const MaturityMonthYear *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->year[i]; }
  wire[at++] = record->month;
  wire[at++] = record->day;
  wire[at++] = record->week;

  return at;
}

/* Maturity Month Year off the wire: 5 bytes from at, returning where the next byte lies */
static size_t decode_maturity_month_year(MaturityMonthYear *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->year[i] = wire[at++]; }
  record->month = wire[at++];
  record->day = wire[at++];
  record->week = wire[at++];

  return at;
}

/* what was read of Maturity Month Year is what was written, byte for byte */
static void equal_maturity_month_year(const MaturityMonthYear *read, const MaturityMonthYear *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->year[i] == written->year[i]); }
  assert(read->month == written->month);
  assert(read->day == written->day);
  assert(read->week == written->week);
}

/* Maturity Month Year: written and read back, then read and written back */
static void check_maturity_month_year(void) {
  MaturityMonthYear sent;
  MaturityMonthYear got;
  uint8_t wire[5];
  uint8_t again[5];

  any_maturity_month_year(&sent);
  assert(encode_maturity_month_year(&sent, wire, 0) == 5);
  assert(decode_maturity_month_year(&got, wire, 0) == 5);
  equal_maturity_month_year(&got, &sent);

  for (size_t i = 0; i < 5; i++) { wire[i] = arbitrary(); }
  assert(decode_maturity_month_year(&got, wire, 0) == 5);
  assert(encode_maturity_month_year(&got, again, 0) == 5);
  for (size_t i = 0; i < 5; i++) { assert(again[i] == wire[i]); }
}

/* ---- Underlying Maturity Month Year: 5 bytes --------------------------------- */

/* Number of underlying legs that make up the security */
typedef struct {
  uint8_t year[2];  /* bytes 0 to 1 */
  uint8_t month;    /* byte 2 */
  uint8_t day;      /* byte 3 */
  uint8_t week;     /* byte 4 */
} UnderlyingMaturityMonthYear;

/* any Underlying Maturity Month Year at all: every byte one the checker chooses */
static void any_underlying_maturity_month_year(UnderlyingMaturityMonthYear *record) {
  for (size_t i = 0; i < 2; i++) { record->year[i] = arbitrary(); }
  record->month = arbitrary();
  record->day = arbitrary();
  record->week = arbitrary();
}

/* Underlying Maturity Month Year to the wire: 5 bytes from at, returning where the next byte goes */
static size_t encode_underlying_maturity_month_year(const UnderlyingMaturityMonthYear *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->year[i]; }
  wire[at++] = record->month;
  wire[at++] = record->day;
  wire[at++] = record->week;

  return at;
}

/* Underlying Maturity Month Year off the wire: 5 bytes from at, returning where the next byte lies */
static size_t decode_underlying_maturity_month_year(UnderlyingMaturityMonthYear *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->year[i] = wire[at++]; }
  record->month = wire[at++];
  record->day = wire[at++];
  record->week = wire[at++];

  return at;
}

/* what was read of Underlying Maturity Month Year is what was written, byte for byte */
static void equal_underlying_maturity_month_year(const UnderlyingMaturityMonthYear *read, const UnderlyingMaturityMonthYear *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->year[i] == written->year[i]); }
  assert(read->month == written->month);
  assert(read->day == written->day);
  assert(read->week == written->week);
}

/* Underlying Maturity Month Year: written and read back, then read and written back */
static void check_underlying_maturity_month_year(void) {
  UnderlyingMaturityMonthYear sent;
  UnderlyingMaturityMonthYear got;
  uint8_t wire[5];
  uint8_t again[5];

  any_underlying_maturity_month_year(&sent);
  assert(encode_underlying_maturity_month_year(&sent, wire, 0) == 5);
  assert(decode_underlying_maturity_month_year(&got, wire, 0) == 5);
  equal_underlying_maturity_month_year(&got, &sent);

  for (size_t i = 0; i < 5; i++) { wire[i] = arbitrary(); }
  assert(decode_underlying_maturity_month_year(&got, wire, 0) == 5);
  assert(encode_underlying_maturity_month_year(&got, again, 0) == 5);
  for (size_t i = 0; i < 5; i++) { assert(again[i] == wire[i]); }
}

/* ---- Leg Maturity Month Year: 5 bytes ---------------------------------------- */

/* Number of legs (repeating groups) */
typedef struct {
  uint8_t year[2];  /* bytes 0 to 1 */
  uint8_t month;    /* byte 2 */
  uint8_t day;      /* byte 3 */
  uint8_t week;     /* byte 4 */
} LegMaturityMonthYear;

/* any Leg Maturity Month Year at all: every byte one the checker chooses */
static void any_leg_maturity_month_year(LegMaturityMonthYear *record) {
  for (size_t i = 0; i < 2; i++) { record->year[i] = arbitrary(); }
  record->month = arbitrary();
  record->day = arbitrary();
  record->week = arbitrary();
}

/* Leg Maturity Month Year to the wire: 5 bytes from at, returning where the next byte goes */
static size_t encode_leg_maturity_month_year(const LegMaturityMonthYear *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->year[i]; }
  wire[at++] = record->month;
  wire[at++] = record->day;
  wire[at++] = record->week;

  return at;
}

/* Leg Maturity Month Year off the wire: 5 bytes from at, returning where the next byte lies */
static size_t decode_leg_maturity_month_year(LegMaturityMonthYear *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->year[i] = wire[at++]; }
  record->month = wire[at++];
  record->day = wire[at++];
  record->week = wire[at++];

  return at;
}

/* what was read of Leg Maturity Month Year is what was written, byte for byte */
static void equal_leg_maturity_month_year(const LegMaturityMonthYear *read, const LegMaturityMonthYear *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->year[i] == written->year[i]); }
  assert(read->month == written->month);
  assert(read->day == written->day);
  assert(read->week == written->week);
}

/* Leg Maturity Month Year: written and read back, then read and written back */
static void check_leg_maturity_month_year(void) {
  LegMaturityMonthYear sent;
  LegMaturityMonthYear got;
  uint8_t wire[5];
  uint8_t again[5];

  any_leg_maturity_month_year(&sent);
  assert(encode_leg_maturity_month_year(&sent, wire, 0) == 5);
  assert(decode_leg_maturity_month_year(&got, wire, 0) == 5);
  equal_leg_maturity_month_year(&got, &sent);

  for (size_t i = 0; i < 5; i++) { wire[i] = arbitrary(); }
  assert(decode_leg_maturity_month_year(&got, wire, 0) == 5);
  assert(encode_leg_maturity_month_year(&got, again, 0) == 5);
  for (size_t i = 0; i < 5; i++) { assert(again[i] == wire[i]); }
}

/* ---- Group Size Encoding: 4 bytes -------------------------------------------- */

/* Repeating group dimensions */
typedef struct {
  uint8_t block_length[2];  /* bytes 0 to 1 */
  uint8_t num_in_group[2];  /* bytes 2 to 3 */
} GroupSizeEncoding;

/* any Group Size Encoding at all: every byte one the checker chooses */
static void any_group_size_encoding(GroupSizeEncoding *record) {
  for (size_t i = 0; i < 2; i++) { record->block_length[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->num_in_group[i] = arbitrary(); }
}

/* Group Size Encoding to the wire: 4 bytes from at, returning where the next byte goes */
static size_t encode_group_size_encoding(const GroupSizeEncoding *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->block_length[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->num_in_group[i]; }

  return at;
}

/* Group Size Encoding off the wire: 4 bytes from at, returning where the next byte lies */
static size_t decode_group_size_encoding(GroupSizeEncoding *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->block_length[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->num_in_group[i] = wire[at++]; }

  return at;
}

/* what was read of Group Size Encoding is what was written, byte for byte */
static void equal_group_size_encoding(const GroupSizeEncoding *read, const GroupSizeEncoding *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->block_length[i] == written->block_length[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->num_in_group[i] == written->num_in_group[i]); }
}

/* Group Size Encoding: written and read back, then read and written back */
static void check_group_size_encoding(void) {
  GroupSizeEncoding sent;
  GroupSizeEncoding got;
  uint8_t wire[4];
  uint8_t again[4];

  any_group_size_encoding(&sent);
  assert(encode_group_size_encoding(&sent, wire, 0) == 4);
  assert(decode_group_size_encoding(&got, wire, 0) == 4);
  equal_group_size_encoding(&got, &sent);

  for (size_t i = 0; i < 4; i++) { wire[i] = arbitrary(); }
  assert(decode_group_size_encoding(&got, wire, 0) == 4);
  assert(encode_group_size_encoding(&got, again, 0) == 4);
  for (size_t i = 0; i < 4; i++) { assert(again[i] == wire[i]); }
}

/* ---- Md Entry Px Decimal: 9 bytes -------------------------------------------- */

/* Number of entries in Market Data message */
typedef struct {
  uint8_t mantissa[8];  /* bytes 0 to 7 */
  uint8_t exponent;     /* byte 8 */
} MdEntryPxDecimal;

/* any Md Entry Px Decimal at all: every byte one the checker chooses */
static void any_md_entry_px_decimal(MdEntryPxDecimal *record) {
  for (size_t i = 0; i < 8; i++) { record->mantissa[i] = arbitrary(); }
  record->exponent = arbitrary();
}

/* Md Entry Px Decimal to the wire: 9 bytes from at, returning where the next byte goes */
static size_t encode_md_entry_px_decimal(const MdEntryPxDecimal *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->mantissa[i]; }
  wire[at++] = record->exponent;

  return at;
}

/* Md Entry Px Decimal off the wire: 9 bytes from at, returning where the next byte lies */
static size_t decode_md_entry_px_decimal(MdEntryPxDecimal *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->mantissa[i] = wire[at++]; }
  record->exponent = wire[at++];

  return at;
}

/* what was read of Md Entry Px Decimal is what was written, byte for byte */
static void equal_md_entry_px_decimal(const MdEntryPxDecimal *read, const MdEntryPxDecimal *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->mantissa[i] == written->mantissa[i]); }
  assert(read->exponent == written->exponent);
}

/* Md Entry Px Decimal: written and read back, then read and written back */
static void check_md_entry_px_decimal(void) {
  MdEntryPxDecimal sent;
  MdEntryPxDecimal got;
  uint8_t wire[9];
  uint8_t again[9];

  any_md_entry_px_decimal(&sent);
  assert(encode_md_entry_px_decimal(&sent, wire, 0) == 9);
  assert(decode_md_entry_px_decimal(&got, wire, 0) == 9);
  equal_md_entry_px_decimal(&got, &sent);

  for (size_t i = 0; i < 9; i++) { wire[i] = arbitrary(); }
  assert(decode_md_entry_px_decimal(&got, wire, 0) == 9);
  assert(encode_md_entry_px_decimal(&got, again, 0) == 9);
  for (size_t i = 0; i < 9; i++) { assert(again[i] == wire[i]); }
}

/* ---- Yield: 9 bytes ---------------------------------------------------------- */

/* Number of entries in Market Data message */
typedef struct {
  uint8_t mantissa[8];  /* bytes 0 to 7 */
  uint8_t exponent;     /* byte 8 */
} Yield;

/* any Yield at all: every byte one the checker chooses */
static void any_yield(Yield *record) {
  for (size_t i = 0; i < 8; i++) { record->mantissa[i] = arbitrary(); }
  record->exponent = arbitrary();
}

/* Yield to the wire: 9 bytes from at, returning where the next byte goes */
static size_t encode_yield(const Yield *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->mantissa[i]; }
  wire[at++] = record->exponent;

  return at;
}

/* Yield off the wire: 9 bytes from at, returning where the next byte lies */
static size_t decode_yield(Yield *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->mantissa[i] = wire[at++]; }
  record->exponent = wire[at++];

  return at;
}

/* what was read of Yield is what was written, byte for byte */
static void equal_yield(const Yield *read, const Yield *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->mantissa[i] == written->mantissa[i]); }
  assert(read->exponent == written->exponent);
}

/* Yield: written and read back, then read and written back */
static void check_yield(void) {
  Yield sent;
  Yield got;
  uint8_t wire[9];
  uint8_t again[9];

  any_yield(&sent);
  assert(encode_yield(&sent, wire, 0) == 9);
  assert(decode_yield(&got, wire, 0) == 9);
  equal_yield(&got, &sent);

  for (size_t i = 0; i < 9; i++) { wire[i] = arbitrary(); }
  assert(decode_yield(&got, wire, 0) == 9);
  assert(encode_yield(&got, again, 0) == 9);
  for (size_t i = 0; i < 9; i++) { assert(again[i] == wire[i]); }
}

/* ---- Net Chg Prev Day: 9 bytes ----------------------------------------------- */

/* Number of entries in Market Data message */
typedef struct {
  uint8_t mantissa[8];  /* bytes 0 to 7 */
  uint8_t exponent;     /* byte 8 */
} NetChgPrevDay;

/* any Net Chg Prev Day at all: every byte one the checker chooses */
static void any_net_chg_prev_day(NetChgPrevDay *record) {
  for (size_t i = 0; i < 8; i++) { record->mantissa[i] = arbitrary(); }
  record->exponent = arbitrary();
}

/* Net Chg Prev Day to the wire: 9 bytes from at, returning where the next byte goes */
static size_t encode_net_chg_prev_day(const NetChgPrevDay *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->mantissa[i]; }
  wire[at++] = record->exponent;

  return at;
}

/* Net Chg Prev Day off the wire: 9 bytes from at, returning where the next byte lies */
static size_t decode_net_chg_prev_day(NetChgPrevDay *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->mantissa[i] = wire[at++]; }
  record->exponent = wire[at++];

  return at;
}

/* what was read of Net Chg Prev Day is what was written, byte for byte */
static void equal_net_chg_prev_day(const NetChgPrevDay *read, const NetChgPrevDay *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->mantissa[i] == written->mantissa[i]); }
  assert(read->exponent == written->exponent);
}

/* Net Chg Prev Day: written and read back, then read and written back */
static void check_net_chg_prev_day(void) {
  NetChgPrevDay sent;
  NetChgPrevDay got;
  uint8_t wire[9];
  uint8_t again[9];

  any_net_chg_prev_day(&sent);
  assert(encode_net_chg_prev_day(&sent, wire, 0) == 9);
  assert(decode_net_chg_prev_day(&got, wire, 0) == 9);
  equal_net_chg_prev_day(&got, &sent);

  for (size_t i = 0; i < 9; i++) { wire[i] = arbitrary(); }
  assert(decode_net_chg_prev_day(&got, wire, 0) == 9);
  assert(encode_net_chg_prev_day(&got, again, 0) == 9);
  for (size_t i = 0; i < 9; i++) { assert(again[i] == wire[i]); }
}

/* ---- Net Pct Chg: 9 bytes ---------------------------------------------------- */

/* Number of entries in Market Data message */
typedef struct {
  uint8_t mantissa[8];  /* bytes 0 to 7 */
  uint8_t exponent;     /* byte 8 */
} NetPctChg;

/* any Net Pct Chg at all: every byte one the checker chooses */
static void any_net_pct_chg(NetPctChg *record) {
  for (size_t i = 0; i < 8; i++) { record->mantissa[i] = arbitrary(); }
  record->exponent = arbitrary();
}

/* Net Pct Chg to the wire: 9 bytes from at, returning where the next byte goes */
static size_t encode_net_pct_chg(const NetPctChg *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->mantissa[i]; }
  wire[at++] = record->exponent;

  return at;
}

/* Net Pct Chg off the wire: 9 bytes from at, returning where the next byte lies */
static size_t decode_net_pct_chg(NetPctChg *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->mantissa[i] = wire[at++]; }
  record->exponent = wire[at++];

  return at;
}

/* what was read of Net Pct Chg is what was written, byte for byte */
static void equal_net_pct_chg(const NetPctChg *read, const NetPctChg *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->mantissa[i] == written->mantissa[i]); }
  assert(read->exponent == written->exponent);
}

/* Net Pct Chg: written and read back, then read and written back */
static void check_net_pct_chg(void) {
  NetPctChg sent;
  NetPctChg got;
  uint8_t wire[9];
  uint8_t again[9];

  any_net_pct_chg(&sent);
  assert(encode_net_pct_chg(&sent, wire, 0) == 9);
  assert(decode_net_pct_chg(&got, wire, 0) == 9);
  equal_net_pct_chg(&got, &sent);

  for (size_t i = 0; i < 9; i++) { wire[i] = arbitrary(); }
  assert(decode_net_pct_chg(&got, wire, 0) == 9);
  assert(encode_net_pct_chg(&got, again, 0) == 9);
  for (size_t i = 0; i < 9; i++) { assert(again[i] == wire[i]); }
}

/* ---- Percent Trading: 9 bytes ------------------------------------------------ */

/* Number of entries in Market Data message */
typedef struct {
  uint8_t mantissa[8];  /* bytes 0 to 7 */
  uint8_t exponent;     /* byte 8 */
} PercentTrading;

/* any Percent Trading at all: every byte one the checker chooses */
static void any_percent_trading(PercentTrading *record) {
  for (size_t i = 0; i < 8; i++) { record->mantissa[i] = arbitrary(); }
  record->exponent = arbitrary();
}

/* Percent Trading to the wire: 9 bytes from at, returning where the next byte goes */
static size_t encode_percent_trading(const PercentTrading *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->mantissa[i]; }
  wire[at++] = record->exponent;

  return at;
}

/* Percent Trading off the wire: 9 bytes from at, returning where the next byte lies */
static size_t decode_percent_trading(PercentTrading *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->mantissa[i] = wire[at++]; }
  record->exponent = wire[at++];

  return at;
}

/* what was read of Percent Trading is what was written, byte for byte */
static void equal_percent_trading(const PercentTrading *read, const PercentTrading *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->mantissa[i] == written->mantissa[i]); }
  assert(read->exponent == written->exponent);
}

/* Percent Trading: written and read back, then read and written back */
static void check_percent_trading(void) {
  PercentTrading sent;
  PercentTrading got;
  uint8_t wire[9];
  uint8_t again[9];

  any_percent_trading(&sent);
  assert(encode_percent_trading(&sent, wire, 0) == 9);
  assert(decode_percent_trading(&got, wire, 0) == 9);
  equal_percent_trading(&got, &sent);

  for (size_t i = 0; i < 9; i++) { wire[i] = arbitrary(); }
  assert(decode_percent_trading(&got, wire, 0) == 9);
  assert(encode_percent_trading(&got, again, 0) == 9);
  for (size_t i = 0; i < 9; i++) { assert(again[i] == wire[i]); }
}

/* ---- Md Entry Size: 9 bytes -------------------------------------------------- */

/* Number of entries in Market Data message. */
typedef struct {
  uint8_t mantissa[8];  /* bytes 0 to 7 */
  uint8_t exponent;     /* byte 8 */
} MdEntrySize;

/* any Md Entry Size at all: every byte one the checker chooses */
static void any_md_entry_size(MdEntrySize *record) {
  for (size_t i = 0; i < 8; i++) { record->mantissa[i] = arbitrary(); }
  record->exponent = arbitrary();
}

/* Md Entry Size to the wire: 9 bytes from at, returning where the next byte goes */
static size_t encode_md_entry_size(const MdEntrySize *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->mantissa[i]; }
  wire[at++] = record->exponent;

  return at;
}

/* Md Entry Size off the wire: 9 bytes from at, returning where the next byte lies */
static size_t decode_md_entry_size(MdEntrySize *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->mantissa[i] = wire[at++]; }
  record->exponent = wire[at++];

  return at;
}

/* what was read of Md Entry Size is what was written, byte for byte */
static void equal_md_entry_size(const MdEntrySize *read, const MdEntrySize *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->mantissa[i] == written->mantissa[i]); }
  assert(read->exponent == written->exponent);
}

/* Md Entry Size: written and read back, then read and written back */
static void check_md_entry_size(void) {
  MdEntrySize sent;
  MdEntrySize got;
  uint8_t wire[9];
  uint8_t again[9];

  any_md_entry_size(&sent);
  assert(encode_md_entry_size(&sent, wire, 0) == 9);
  assert(decode_md_entry_size(&got, wire, 0) == 9);
  equal_md_entry_size(&got, &sent);

  for (size_t i = 0; i < 9; i++) { wire[i] = arbitrary(); }
  assert(decode_md_entry_size(&got, wire, 0) == 9);
  assert(encode_md_entry_size(&got, again, 0) == 9);
  for (size_t i = 0; i < 9; i++) { assert(again[i] == wire[i]); }
}

/* ---- Cal Fut Px: 9 bytes ----------------------------------------------------- */

/* Number of entries in Market Data message. */
typedef struct {
  uint8_t mantissa[8];  /* bytes 0 to 7 */
  uint8_t exponent;     /* byte 8 */
} CalFutPx;

/* any Cal Fut Px at all: every byte one the checker chooses */
static void any_cal_fut_px(CalFutPx *record) {
  for (size_t i = 0; i < 8; i++) { record->mantissa[i] = arbitrary(); }
  record->exponent = arbitrary();
}

/* Cal Fut Px to the wire: 9 bytes from at, returning where the next byte goes */
static size_t encode_cal_fut_px(const CalFutPx *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->mantissa[i]; }
  wire[at++] = record->exponent;

  return at;
}

/* Cal Fut Px off the wire: 9 bytes from at, returning where the next byte lies */
static size_t decode_cal_fut_px(CalFutPx *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->mantissa[i] = wire[at++]; }
  record->exponent = wire[at++];

  return at;
}

/* what was read of Cal Fut Px is what was written, byte for byte */
static void equal_cal_fut_px(const CalFutPx *read, const CalFutPx *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->mantissa[i] == written->mantissa[i]); }
  assert(read->exponent == written->exponent);
}

/* Cal Fut Px: written and read back, then read and written back */
static void check_cal_fut_px(void) {
  CalFutPx sent;
  CalFutPx got;
  uint8_t wire[9];
  uint8_t again[9];

  any_cal_fut_px(&sent);
  assert(encode_cal_fut_px(&sent, wire, 0) == 9);
  assert(decode_cal_fut_px(&got, wire, 0) == 9);
  equal_cal_fut_px(&got, &sent);

  for (size_t i = 0; i < 9; i++) { wire[i] = arbitrary(); }
  assert(decode_cal_fut_px(&got, wire, 0) == 9);
  assert(encode_cal_fut_px(&got, again, 0) == 9);
  for (size_t i = 0; i < 9; i++) { assert(again[i] == wire[i]); }
}

/* ---- Strike Price Decimal: 9 bytes ------------------------------------------- */

/* Number of entries in Market Data message. */
typedef struct {
  uint8_t mantissa[8];  /* bytes 0 to 7 */
  uint8_t exponent;     /* byte 8 */
} StrikePriceDecimal;

/* any Strike Price Decimal at all: every byte one the checker chooses */
static void any_strike_price_decimal(StrikePriceDecimal *record) {
  for (size_t i = 0; i < 8; i++) { record->mantissa[i] = arbitrary(); }
  record->exponent = arbitrary();
}

/* Strike Price Decimal to the wire: 9 bytes from at, returning where the next byte goes */
static size_t encode_strike_price_decimal(const StrikePriceDecimal *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->mantissa[i]; }
  wire[at++] = record->exponent;

  return at;
}

/* Strike Price Decimal off the wire: 9 bytes from at, returning where the next byte lies */
static size_t decode_strike_price_decimal(StrikePriceDecimal *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->mantissa[i] = wire[at++]; }
  record->exponent = wire[at++];

  return at;
}

/* what was read of Strike Price Decimal is what was written, byte for byte */
static void equal_strike_price_decimal(const StrikePriceDecimal *read, const StrikePriceDecimal *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->mantissa[i] == written->mantissa[i]); }
  assert(read->exponent == written->exponent);
}

/* Strike Price Decimal: written and read back, then read and written back */
static void check_strike_price_decimal(void) {
  StrikePriceDecimal sent;
  StrikePriceDecimal got;
  uint8_t wire[9];
  uint8_t again[9];

  any_strike_price_decimal(&sent);
  assert(encode_strike_price_decimal(&sent, wire, 0) == 9);
  assert(decode_strike_price_decimal(&got, wire, 0) == 9);
  equal_strike_price_decimal(&got, &sent);

  for (size_t i = 0; i < 9; i++) { wire[i] = arbitrary(); }
  assert(decode_strike_price_decimal(&got, wire, 0) == 9);
  assert(encode_strike_price_decimal(&got, again, 0) == 9);
  for (size_t i = 0; i < 9; i++) { assert(again[i] == wire[i]); }
}

/* ---- Unit Of Measure Qty Decimal: 9 bytes ------------------------------------ */

/* Number of entries in Market Data message. */
typedef struct {
  uint8_t mantissa[8];  /* bytes 0 to 7 */
  uint8_t exponent;     /* byte 8 */
} UnitOfMeasureQtyDecimal;

/* any Unit Of Measure Qty Decimal at all: every byte one the checker chooses */
static void any_unit_of_measure_qty_decimal(UnitOfMeasureQtyDecimal *record) {
  for (size_t i = 0; i < 8; i++) { record->mantissa[i] = arbitrary(); }
  record->exponent = arbitrary();
}

/* Unit Of Measure Qty Decimal to the wire: 9 bytes from at, returning where the next byte goes */
static size_t encode_unit_of_measure_qty_decimal(const UnitOfMeasureQtyDecimal *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->mantissa[i]; }
  wire[at++] = record->exponent;

  return at;
}

/* Unit Of Measure Qty Decimal off the wire: 9 bytes from at, returning where the next byte lies */
static size_t decode_unit_of_measure_qty_decimal(UnitOfMeasureQtyDecimal *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->mantissa[i] = wire[at++]; }
  record->exponent = wire[at++];

  return at;
}

/* what was read of Unit Of Measure Qty Decimal is what was written, byte for byte */
static void equal_unit_of_measure_qty_decimal(const UnitOfMeasureQtyDecimal *read, const UnitOfMeasureQtyDecimal *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->mantissa[i] == written->mantissa[i]); }
  assert(read->exponent == written->exponent);
}

/* Unit Of Measure Qty Decimal: written and read back, then read and written back */
static void check_unit_of_measure_qty_decimal(void) {
  UnitOfMeasureQtyDecimal sent;
  UnitOfMeasureQtyDecimal got;
  uint8_t wire[9];
  uint8_t again[9];

  any_unit_of_measure_qty_decimal(&sent);
  assert(encode_unit_of_measure_qty_decimal(&sent, wire, 0) == 9);
  assert(decode_unit_of_measure_qty_decimal(&got, wire, 0) == 9);
  equal_unit_of_measure_qty_decimal(&got, &sent);

  for (size_t i = 0; i < 9; i++) { wire[i] = arbitrary(); }
  assert(decode_unit_of_measure_qty_decimal(&got, wire, 0) == 9);
  assert(encode_unit_of_measure_qty_decimal(&got, again, 0) == 9);
  for (size_t i = 0; i < 9; i++) { assert(again[i] == wire[i]); }
}

/* ---- Min Price Increment: 9 bytes -------------------------------------------- */

/* MDInstrumentDefinitionEris */
typedef struct {
  uint8_t mantissa[8];  /* bytes 0 to 7 */
  uint8_t exponent;     /* byte 8 */
} MinPriceIncrement;

/* any Min Price Increment at all: every byte one the checker chooses */
static void any_min_price_increment(MinPriceIncrement *record) {
  for (size_t i = 0; i < 8; i++) { record->mantissa[i] = arbitrary(); }
  record->exponent = arbitrary();
}

/* Min Price Increment to the wire: 9 bytes from at, returning where the next byte goes */
static size_t encode_min_price_increment(const MinPriceIncrement *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->mantissa[i]; }
  wire[at++] = record->exponent;

  return at;
}

/* Min Price Increment off the wire: 9 bytes from at, returning where the next byte lies */
static size_t decode_min_price_increment(MinPriceIncrement *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->mantissa[i] = wire[at++]; }
  record->exponent = wire[at++];

  return at;
}

/* what was read of Min Price Increment is what was written, byte for byte */
static void equal_min_price_increment(const MinPriceIncrement *read, const MinPriceIncrement *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->mantissa[i] == written->mantissa[i]); }
  assert(read->exponent == written->exponent);
}

/* Min Price Increment: written and read back, then read and written back */
static void check_min_price_increment(void) {
  MinPriceIncrement sent;
  MinPriceIncrement got;
  uint8_t wire[9];
  uint8_t again[9];

  any_min_price_increment(&sent);
  assert(encode_min_price_increment(&sent, wire, 0) == 9);
  assert(decode_min_price_increment(&got, wire, 0) == 9);
  equal_min_price_increment(&got, &sent);

  for (size_t i = 0; i < 9; i++) { wire[i] = arbitrary(); }
  assert(decode_min_price_increment(&got, wire, 0) == 9);
  assert(encode_min_price_increment(&got, again, 0) == 9);
  for (size_t i = 0; i < 9; i++) { assert(again[i] == wire[i]); }
}

/* ---- Previous Fixing Rate: 9 bytes ------------------------------------------- */

/* Number of legs (repeating groups) */
typedef struct {
  uint8_t mantissa[8];  /* bytes 0 to 7 */
  uint8_t exponent;     /* byte 8 */
} PreviousFixingRate;

/* any Previous Fixing Rate at all: every byte one the checker chooses */
static void any_previous_fixing_rate(PreviousFixingRate *record) {
  for (size_t i = 0; i < 8; i++) { record->mantissa[i] = arbitrary(); }
  record->exponent = arbitrary();
}

/* Previous Fixing Rate to the wire: 9 bytes from at, returning where the next byte goes */
static size_t encode_previous_fixing_rate(const PreviousFixingRate *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->mantissa[i]; }
  wire[at++] = record->exponent;

  return at;
}

/* Previous Fixing Rate off the wire: 9 bytes from at, returning where the next byte lies */
static size_t decode_previous_fixing_rate(PreviousFixingRate *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->mantissa[i] = wire[at++]; }
  record->exponent = wire[at++];

  return at;
}

/* what was read of Previous Fixing Rate is what was written, byte for byte */
static void equal_previous_fixing_rate(const PreviousFixingRate *read, const PreviousFixingRate *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->mantissa[i] == written->mantissa[i]); }
  assert(read->exponent == written->exponent);
}

/* Previous Fixing Rate: written and read back, then read and written back */
static void check_previous_fixing_rate(void) {
  PreviousFixingRate sent;
  PreviousFixingRate got;
  uint8_t wire[9];
  uint8_t again[9];

  any_previous_fixing_rate(&sent);
  assert(encode_previous_fixing_rate(&sent, wire, 0) == 9);
  assert(decode_previous_fixing_rate(&got, wire, 0) == 9);
  equal_previous_fixing_rate(&got, &sent);

  for (size_t i = 0; i < 9; i++) { wire[i] = arbitrary(); }
  assert(decode_previous_fixing_rate(&got, wire, 0) == 9);
  assert(encode_previous_fixing_rate(&got, again, 0) == 9);
  for (size_t i = 0; i < 9; i++) { assert(again[i] == wire[i]); }
}

/* ---- Interpolation Factor: 9 bytes ------------------------------------------- */

/* Number of legs (repeating groups) */
typedef struct {
  uint8_t mantissa[8];  /* bytes 0 to 7 */
  uint8_t exponent;     /* byte 8 */
} InterpolationFactor;

/* any Interpolation Factor at all: every byte one the checker chooses */
static void any_interpolation_factor(InterpolationFactor *record) {
  for (size_t i = 0; i < 8; i++) { record->mantissa[i] = arbitrary(); }
  record->exponent = arbitrary();
}

/* Interpolation Factor to the wire: 9 bytes from at, returning where the next byte goes */
static size_t encode_interpolation_factor(const InterpolationFactor *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->mantissa[i]; }
  wire[at++] = record->exponent;

  return at;
}

/* Interpolation Factor off the wire: 9 bytes from at, returning where the next byte lies */
static size_t decode_interpolation_factor(InterpolationFactor *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->mantissa[i] = wire[at++]; }
  record->exponent = wire[at++];

  return at;
}

/* what was read of Interpolation Factor is what was written, byte for byte */
static void equal_interpolation_factor(const InterpolationFactor *read, const InterpolationFactor *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->mantissa[i] == written->mantissa[i]); }
  assert(read->exponent == written->exponent);
}

/* Interpolation Factor: written and read back, then read and written back */
static void check_interpolation_factor(void) {
  InterpolationFactor sent;
  InterpolationFactor got;
  uint8_t wire[9];
  uint8_t again[9];

  any_interpolation_factor(&sent);
  assert(encode_interpolation_factor(&sent, wire, 0) == 9);
  assert(decode_interpolation_factor(&got, wire, 0) == 9);
  equal_interpolation_factor(&got, &sent);

  for (size_t i = 0; i < 9; i++) { wire[i] = arbitrary(); }
  assert(decode_interpolation_factor(&got, wire, 0) == 9);
  assert(encode_interpolation_factor(&got, again, 0) == 9);
  for (size_t i = 0; i < 9; i++) { assert(again[i] == wire[i]); }
}

/* ---- What esbmc checks ------------------------------------------------------- */

/* every record of the protocol, each on its own buffers */
static void checks(void) {
  check_binary_packet_header();
  check_simple_binary_header();
  check_message_header();
  check_admin_login();
  check_admin_logout();
  check_group_size();
  check_md_entry_px_decimal_optional();
  check_cal_fut_px_optional();
  check_coupon_rate_optional();
  check_fair_coupon_pct();
  check_leg_purchase_rate();
  check_fixed_npv();
  check_float_npv();
  check_npv();
  check_accrued_coupons();
  check_daily_incremental_eris_pai();
  check_eris_pai();
  check_fed_funds_rate();
  check_min_price_increment_optional();
  check_fixed_payment();
  check_floating_payment();
  check_next_fixed_payment_amount();
  check_next_floating_payment_amount();
  check_previous_eris_pai();
  check_leg_contract_multiplier();
  check_p_v01();
  check_d_v01();
  check_settlement_npv();
  check_final_settlement_futures_price();
  check_maturity_month_year();
  check_underlying_maturity_month_year();
  check_leg_maturity_month_year();
  check_group_size_encoding();
  check_md_entry_px_decimal();
  check_yield();
  check_net_chg_prev_day();
  check_net_pct_chg();
  check_percent_trading();
  check_md_entry_size();
  check_cal_fut_px();
  check_strike_price_decimal();
  check_unit_of_measure_qty_decimal();
  check_min_price_increment();
  check_previous_fixing_rate();
  check_interpolation_factor();
}

int main(void) {
#ifdef CONCRETE
  for (pattern = 0; pattern < 4; pattern++) { checks(); }
#else
  checks();
#endif

  return 0;
}
