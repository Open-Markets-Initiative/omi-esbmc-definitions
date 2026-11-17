// moex/spectra/orderslogreplay/Spectra_OrdersLogReplay_v9_9_0_Server.c
/*
 * Moscow Exchange SIMBA Spectra Orders Log Historical Replay
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
 *   - a field read in bits
 *   - the dispatch that chooses a message by its type
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

/* ---- Sbe Header: 8 bytes ----------------------------------------------------- */

/* Root block length, message template id, message schema id and schema version */
typedef struct {
  uint8_t block_length[2];  /* bytes 0 to 1 */
  uint8_t template_id[2];   /* bytes 2 to 3 */
  uint8_t schema_id[2];     /* bytes 4 to 5 */
  uint8_t version[2];       /* bytes 6 to 7 */
} SbeHeader;

/* any Sbe Header at all: every byte one the checker chooses */
static void any_sbe_header(SbeHeader *record) {
  for (size_t i = 0; i < 2; i++) { record->block_length[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->template_id[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->schema_id[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->version[i] = arbitrary(); }
}

/* Sbe Header to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_sbe_header(const SbeHeader *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->block_length[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->template_id[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->schema_id[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->version[i]; }

  return at;
}

/* Sbe Header off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_sbe_header(SbeHeader *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->block_length[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->template_id[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->schema_id[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->version[i] = wire[at++]; }

  return at;
}

/* what was read of Sbe Header is what was written, byte for byte */
static void equal_sbe_header(const SbeHeader *read, const SbeHeader *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->block_length[i] == written->block_length[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->template_id[i] == written->template_id[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->schema_id[i] == written->schema_id[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->version[i] == written->version[i]); }
}

/* Sbe Header: written and read back, then read and written back */
static void check_sbe_header(void) {
  SbeHeader sent;
  SbeHeader got;
  uint8_t wire[8];
  uint8_t again[8];

  any_sbe_header(&sent);
  assert(encode_sbe_header(&sent, wire, 0) == 8);
  assert(decode_sbe_header(&got, wire, 0) == 8);
  equal_sbe_header(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_sbe_header(&got, wire, 0) == 8);
  assert(encode_sbe_header(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Logout Message: 256 bytes ----------------------------------------------- */

/* LogoutMessage */
typedef struct {
  uint8_t text[256];  /* bytes 0 to 255 */
} LogoutMessage;

/* any Logout Message at all: every byte one the checker chooses */
static void any_logout_message(LogoutMessage *record) {
  for (size_t i = 0; i < 256; i++) { record->text[i] = arbitrary(); }
}

/* Logout Message to the wire: 256 bytes from at, returning where the next byte goes */
static size_t encode_logout_message(const LogoutMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 256; i++) { wire[at++] = record->text[i]; }

  return at;
}

/* Logout Message off the wire: 256 bytes from at, returning where the next byte lies */
static size_t decode_logout_message(LogoutMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 256; i++) { record->text[i] = wire[at++]; }

  return at;
}

/* what was read of Logout Message is what was written, byte for byte */
static void equal_logout_message(const LogoutMessage *read, const LogoutMessage *written) {
  for (size_t i = 0; i < 256; i++) { assert(read->text[i] == written->text[i]); }
}

/* Logout Message: written and read back, then read and written back */
static void check_logout_message(void) {
  LogoutMessage sent;
  LogoutMessage got;
  uint8_t wire[256];
  uint8_t again[256];

  any_logout_message(&sent);
  assert(encode_logout_message(&sent, wire, 0) == 256);
  assert(decode_logout_message(&got, wire, 0) == 256);
  equal_logout_message(&got, &sent);

  for (size_t i = 0; i < 256; i++) { wire[i] = arbitrary(); }
  assert(decode_logout_message(&got, wire, 0) == 256);
  assert(encode_logout_message(&got, again, 0) == 256);
  for (size_t i = 0; i < 256; i++) { assert(again[i] == wire[i]); }
}

/* ---- Incremental Packet Header: 12 bytes ------------------------------------- */

/* MarketDataDummyMessage */
typedef struct {
  uint8_t transact_time[8];                         /* bytes 0 to 7 */
  uint8_t exchange_trading_session_id_optional[4];  /* bytes 8 to 11 */
} IncrementalPacketHeader;

/* any Incremental Packet Header at all: every byte one the checker chooses */
static void any_incremental_packet_header(IncrementalPacketHeader *record) {
  for (size_t i = 0; i < 8; i++) { record->transact_time[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->exchange_trading_session_id_optional[i] = arbitrary(); }
}

/* Incremental Packet Header to the wire: 12 bytes from at, returning where the next byte goes */
static size_t encode_incremental_packet_header(const IncrementalPacketHeader *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->transact_time[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->exchange_trading_session_id_optional[i]; }

  return at;
}

/* Incremental Packet Header off the wire: 12 bytes from at, returning where the next byte lies */
static size_t decode_incremental_packet_header(IncrementalPacketHeader *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->transact_time[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->exchange_trading_session_id_optional[i] = wire[at++]; }

  return at;
}

/* what was read of Incremental Packet Header is what was written, byte for byte */
static void equal_incremental_packet_header(const IncrementalPacketHeader *read, const IncrementalPacketHeader *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->transact_time[i] == written->transact_time[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->exchange_trading_session_id_optional[i] == written->exchange_trading_session_id_optional[i]); }
}

/* Incremental Packet Header: written and read back, then read and written back */
static void check_incremental_packet_header(void) {
  IncrementalPacketHeader sent;
  IncrementalPacketHeader got;
  uint8_t wire[12];
  uint8_t again[12];

  any_incremental_packet_header(&sent);
  assert(encode_incremental_packet_header(&sent, wire, 0) == 12);
  assert(decode_incremental_packet_header(&got, wire, 0) == 12);
  equal_incremental_packet_header(&got, &sent);

  for (size_t i = 0; i < 12; i++) { wire[i] = arbitrary(); }
  assert(decode_incremental_packet_header(&got, wire, 0) == 12);
  assert(encode_incremental_packet_header(&got, again, 0) == 12);
  for (size_t i = 0; i < 12; i++) { assert(again[i] == wire[i]); }
}

/* ---- Group Size: 3 bytes ----------------------------------------------------- */

/* groupSize */
typedef struct {
  uint8_t block_length[2];      /* bytes 0 to 1 */
  uint8_t num_in_group_uint_8;  /* byte 2 */
} GroupSize;

/* any Group Size at all: every byte one the checker chooses */
static void any_group_size(GroupSize *record) {
  for (size_t i = 0; i < 2; i++) { record->block_length[i] = arbitrary(); }
  record->num_in_group_uint_8 = arbitrary();
}

/* Group Size to the wire: 3 bytes from at, returning where the next byte goes */
static size_t encode_group_size(const GroupSize *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->block_length[i]; }
  wire[at++] = record->num_in_group_uint_8;

  return at;
}

/* Group Size off the wire: 3 bytes from at, returning where the next byte lies */
static size_t decode_group_size(GroupSize *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->block_length[i] = wire[at++]; }
  record->num_in_group_uint_8 = wire[at++];

  return at;
}

/* what was read of Group Size is what was written, byte for byte */
static void equal_group_size(const GroupSize *read, const GroupSize *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->block_length[i] == written->block_length[i]); }
  assert(read->num_in_group_uint_8 == written->num_in_group_uint_8);
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

/* ---- Empty Book Message: 4 bytes --------------------------------------------- */

/* EmptyBookMessage */
typedef struct {
  uint8_t last_msg_seq_num_processed_optional[4];  /* bytes 0 to 3 */
} EmptyBookMessage;

/* any Empty Book Message at all: every byte one the checker chooses */
static void any_empty_book_message(EmptyBookMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->last_msg_seq_num_processed_optional[i] = arbitrary(); }
}

/* Empty Book Message to the wire: 4 bytes from at, returning where the next byte goes */
static size_t encode_empty_book_message(const EmptyBookMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->last_msg_seq_num_processed_optional[i]; }

  return at;
}

/* Empty Book Message off the wire: 4 bytes from at, returning where the next byte lies */
static size_t decode_empty_book_message(EmptyBookMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->last_msg_seq_num_processed_optional[i] = wire[at++]; }

  return at;
}

/* what was read of Empty Book Message is what was written, byte for byte */
static void equal_empty_book_message(const EmptyBookMessage *read, const EmptyBookMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->last_msg_seq_num_processed_optional[i] == written->last_msg_seq_num_processed_optional[i]); }
}

/* Empty Book Message: written and read back, then read and written back */
static void check_empty_book_message(void) {
  EmptyBookMessage sent;
  EmptyBookMessage got;
  uint8_t wire[4];
  uint8_t again[4];

  any_empty_book_message(&sent);
  assert(encode_empty_book_message(&sent, wire, 0) == 4);
  assert(decode_empty_book_message(&got, wire, 0) == 4);
  equal_empty_book_message(&got, &sent);

  for (size_t i = 0; i < 4; i++) { wire[i] = arbitrary(); }
  assert(decode_empty_book_message(&got, wire, 0) == 4);
  assert(encode_empty_book_message(&got, again, 0) == 4);
  for (size_t i = 0; i < 4; i++) { assert(again[i] == wire[i]); }
}

/* ---- What esbmc checks ------------------------------------------------------- */

/* every record of the protocol, each on its own buffers */
static void checks(void) {
  check_sbe_header();
  check_logout_message();
  check_incremental_packet_header();
  check_group_size();
  check_empty_book_message();
}

int main(void) {
#ifdef CONCRETE
  for (pattern = 0; pattern < 4; pattern++) { checks(); }
#else
  checks();
#endif

  return 0;
}
