// moex/spectra/orderslogreplay/Spectra_OrdersLogReplay_v2_2_0_Client.c
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
 *   - a block whose stated length holds more than its fields
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

/* ---- Market Data Request Message: 8 bytes ------------------------------------ */

/* MarketDataRequestMessage */
typedef struct {
  uint8_t appl_beg_seq_num[4];  /* bytes 0 to 3 */
  uint8_t appl_end_seq_num[4];  /* bytes 4 to 7 */
} MarketDataRequestMessage;

/* any Market Data Request Message at all: every byte one the checker chooses */
static void any_market_data_request_message(MarketDataRequestMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->appl_beg_seq_num[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->appl_end_seq_num[i] = arbitrary(); }
}

/* Market Data Request Message to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_market_data_request_message(const MarketDataRequestMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->appl_beg_seq_num[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->appl_end_seq_num[i]; }

  return at;
}

/* Market Data Request Message off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_market_data_request_message(MarketDataRequestMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->appl_beg_seq_num[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->appl_end_seq_num[i] = wire[at++]; }

  return at;
}

/* what was read of Market Data Request Message is what was written, byte for byte */
static void equal_market_data_request_message(const MarketDataRequestMessage *read, const MarketDataRequestMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->appl_beg_seq_num[i] == written->appl_beg_seq_num[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->appl_end_seq_num[i] == written->appl_end_seq_num[i]); }
}

/* Market Data Request Message: written and read back, then read and written back */
static void check_market_data_request_message(void) {
  MarketDataRequestMessage sent;
  MarketDataRequestMessage got;
  uint8_t wire[8];
  uint8_t again[8];

  any_market_data_request_message(&sent);
  assert(encode_market_data_request_message(&sent, wire, 0) == 8);
  assert(decode_market_data_request_message(&got, wire, 0) == 8);
  equal_market_data_request_message(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_market_data_request_message(&got, wire, 0) == 8);
  assert(encode_market_data_request_message(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- What esbmc checks ------------------------------------------------------- */

/* every record of the protocol, each on its own buffers */
static void checks(void) {
  check_sbe_header();
  check_logout_message();
  check_market_data_request_message();
}

int main(void) {
#ifdef CONCRETE
  for (pattern = 0; pattern < 4; pattern++) { checks(); }
#else
  checks();
#endif

  return 0;
}
