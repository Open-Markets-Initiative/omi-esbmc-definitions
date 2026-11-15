// bmv/bmvmarketdata/snapshot/BmvMarketData_Snapshot_v1_1_Client.c
/*
 * Bolsa Mexicana de Valores Bmv Market Data Snapshot
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

/* ---- Client Message Header: 2 bytes ------------------------------------------ */

/* Request length and message type */
typedef struct {
  uint8_t client_length;        /* byte 0 */
  uint8_t client_message_type;  /* byte 1 */
} ClientMessageHeader;

/* any Client Message Header at all: every byte one the checker chooses */
static void any_client_message_header(ClientMessageHeader *record) {
  record->client_length = arbitrary();
  record->client_message_type = arbitrary();
}

/* Client Message Header to the wire: 2 bytes from at, returning where the next byte goes */
static size_t encode_client_message_header(const ClientMessageHeader *record, uint8_t *wire, size_t at) {
  wire[at++] = record->client_length;
  wire[at++] = record->client_message_type;

  return at;
}

/* Client Message Header off the wire: 2 bytes from at, returning where the next byte lies */
static size_t decode_client_message_header(ClientMessageHeader *record, const uint8_t *wire, size_t at) {
  record->client_length = wire[at++];
  record->client_message_type = wire[at++];

  return at;
}

/* what was read of Client Message Header is what was written, byte for byte */
static void equal_client_message_header(const ClientMessageHeader *read, const ClientMessageHeader *written) {
  assert(read->client_length == written->client_length);
  assert(read->client_message_type == written->client_message_type);
}

/* Client Message Header: written and read back, then read and written back */
static void check_client_message_header(void) {
  ClientMessageHeader sent;
  ClientMessageHeader got;
  uint8_t wire[2];
  uint8_t again[2];

  any_client_message_header(&sent);
  assert(encode_client_message_header(&sent, wire, 0) == 2);
  assert(decode_client_message_header(&got, wire, 0) == 2);
  equal_client_message_header(&got, &sent);

  for (size_t i = 0; i < 2; i++) { wire[i] = arbitrary(); }
  assert(decode_client_message_header(&got, wire, 0) == 2);
  assert(encode_client_message_header(&got, again, 0) == 2);
  for (size_t i = 0; i < 2; i++) { assert(again[i] == wire[i]); }
}

/* ---- Login Message: 17 bytes ------------------------------------------------- */

/* Logs the consumer in to the replay or snapshot channel. */
typedef struct {
  uint8_t market_data_group;  /* byte 0 */
  uint8_t user[6];            /* bytes 1 to 6 */
  uint8_t password[10];       /* bytes 7 to 16 */
} LoginMessage;

/* any Login Message at all: every byte one the checker chooses */
static void any_login_message(LoginMessage *record) {
  record->market_data_group = arbitrary();
  for (size_t i = 0; i < 6; i++) { record->user[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->password[i] = arbitrary(); }
}

/* Login Message to the wire: 17 bytes from at, returning where the next byte goes */
static size_t encode_login_message(const LoginMessage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->market_data_group;
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->user[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->password[i]; }

  return at;
}

/* Login Message off the wire: 17 bytes from at, returning where the next byte lies */
static size_t decode_login_message(LoginMessage *record, const uint8_t *wire, size_t at) {
  record->market_data_group = wire[at++];
  for (size_t i = 0; i < 6; i++) { record->user[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->password[i] = wire[at++]; }

  return at;
}

/* what was read of Login Message is what was written, byte for byte */
static void equal_login_message(const LoginMessage *read, const LoginMessage *written) {
  assert(read->market_data_group == written->market_data_group);
  for (size_t i = 0; i < 6; i++) { assert(read->user[i] == written->user[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->password[i] == written->password[i]); }
}

/* Login Message: written and read back, then read and written back */
static void check_login_message(void) {
  LoginMessage sent;
  LoginMessage got;
  uint8_t wire[17];
  uint8_t again[17];

  any_login_message(&sent);
  assert(encode_login_message(&sent, wire, 0) == 17);
  assert(decode_login_message(&got, wire, 0) == 17);
  equal_login_message(&got, &sent);

  for (size_t i = 0; i < 17; i++) { wire[i] = arbitrary(); }
  assert(decode_login_message(&got, wire, 0) == 17);
  assert(encode_login_message(&got, again, 0) == 17);
  for (size_t i = 0; i < 17; i++) { assert(again[i] == wire[i]); }
}

/* ---- Replay Request Message: 7 bytes ----------------------------------------- */

/* Requests the replay of messages already published on a multicast group. */
typedef struct {
  uint8_t market_data_group;  /* byte 0 */
  uint8_t first_message[4];   /* bytes 1 to 4 */
  uint8_t quantity[2];        /* bytes 5 to 6 */
} ReplayRequestMessage;

/* any Replay Request Message at all: every byte one the checker chooses */
static void any_replay_request_message(ReplayRequestMessage *record) {
  record->market_data_group = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->first_message[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->quantity[i] = arbitrary(); }
}

/* Replay Request Message to the wire: 7 bytes from at, returning where the next byte goes */
static size_t encode_replay_request_message(const ReplayRequestMessage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->market_data_group;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->first_message[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->quantity[i]; }

  return at;
}

/* Replay Request Message off the wire: 7 bytes from at, returning where the next byte lies */
static size_t decode_replay_request_message(ReplayRequestMessage *record, const uint8_t *wire, size_t at) {
  record->market_data_group = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->first_message[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->quantity[i] = wire[at++]; }

  return at;
}

/* what was read of Replay Request Message is what was written, byte for byte */
static void equal_replay_request_message(const ReplayRequestMessage *read, const ReplayRequestMessage *written) {
  assert(read->market_data_group == written->market_data_group);
  for (size_t i = 0; i < 4; i++) { assert(read->first_message[i] == written->first_message[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->quantity[i] == written->quantity[i]); }
}

/* Replay Request Message: written and read back, then read and written back */
static void check_replay_request_message(void) {
  ReplayRequestMessage sent;
  ReplayRequestMessage got;
  uint8_t wire[7];
  uint8_t again[7];

  any_replay_request_message(&sent);
  assert(encode_replay_request_message(&sent, wire, 0) == 7);
  assert(decode_replay_request_message(&got, wire, 0) == 7);
  equal_replay_request_message(&got, &sent);

  for (size_t i = 0; i < 7; i++) { wire[i] = arbitrary(); }
  assert(decode_replay_request_message(&got, wire, 0) == 7);
  assert(encode_replay_request_message(&got, again, 0) == 7);
  for (size_t i = 0; i < 7; i++) { assert(again[i] == wire[i]); }
}

/* ---- Snapshot Request Message: 6 bytes --------------------------------------- */

/* Requests a snapshot of a multicast group. */
typedef struct {
  uint8_t market_data_group;  /* byte 0 */
  uint8_t instrument_id[4];   /* bytes 1 to 4 */
  uint8_t snapshot_type;      /* byte 5 */
} SnapshotRequestMessage;

/* any Snapshot Request Message at all: every byte one the checker chooses */
static void any_snapshot_request_message(SnapshotRequestMessage *record) {
  record->market_data_group = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->instrument_id[i] = arbitrary(); }
  record->snapshot_type = arbitrary();
}

/* Snapshot Request Message to the wire: 6 bytes from at, returning where the next byte goes */
static size_t encode_snapshot_request_message(const SnapshotRequestMessage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->market_data_group;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument_id[i]; }
  wire[at++] = record->snapshot_type;

  return at;
}

/* Snapshot Request Message off the wire: 6 bytes from at, returning where the next byte lies */
static size_t decode_snapshot_request_message(SnapshotRequestMessage *record, const uint8_t *wire, size_t at) {
  record->market_data_group = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->instrument_id[i] = wire[at++]; }
  record->snapshot_type = wire[at++];

  return at;
}

/* what was read of Snapshot Request Message is what was written, byte for byte */
static void equal_snapshot_request_message(const SnapshotRequestMessage *read, const SnapshotRequestMessage *written) {
  assert(read->market_data_group == written->market_data_group);
  for (size_t i = 0; i < 4; i++) { assert(read->instrument_id[i] == written->instrument_id[i]); }
  assert(read->snapshot_type == written->snapshot_type);
}

/* Snapshot Request Message: written and read back, then read and written back */
static void check_snapshot_request_message(void) {
  SnapshotRequestMessage sent;
  SnapshotRequestMessage got;
  uint8_t wire[6];
  uint8_t again[6];

  any_snapshot_request_message(&sent);
  assert(encode_snapshot_request_message(&sent, wire, 0) == 6);
  assert(decode_snapshot_request_message(&got, wire, 0) == 6);
  equal_snapshot_request_message(&got, &sent);

  for (size_t i = 0; i < 6; i++) { wire[i] = arbitrary(); }
  assert(decode_snapshot_request_message(&got, wire, 0) == 6);
  assert(encode_snapshot_request_message(&got, again, 0) == 6);
  for (size_t i = 0; i < 6; i++) { assert(again[i] == wire[i]); }
}

/* ---- Snapshot Indices Request Message: 11 bytes ------------------------------ */

/* Requests a snapshot of an index. */
typedef struct {
  uint8_t market_data_group;  /* byte 0 */
  uint8_t component[2];       /* bytes 1 to 2 */
  uint8_t recovery_hour[8];   /* bytes 3 to 10 */
} SnapshotIndicesRequestMessage;

/* any Snapshot Indices Request Message at all: every byte one the checker chooses */
static void any_snapshot_indices_request_message(SnapshotIndicesRequestMessage *record) {
  record->market_data_group = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->component[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->recovery_hour[i] = arbitrary(); }
}

/* Snapshot Indices Request Message to the wire: 11 bytes from at, returning where the next byte goes */
static size_t encode_snapshot_indices_request_message(const SnapshotIndicesRequestMessage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->market_data_group;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->component[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->recovery_hour[i]; }

  return at;
}

/* Snapshot Indices Request Message off the wire: 11 bytes from at, returning where the next byte lies */
static size_t decode_snapshot_indices_request_message(SnapshotIndicesRequestMessage *record, const uint8_t *wire, size_t at) {
  record->market_data_group = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->component[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->recovery_hour[i] = wire[at++]; }

  return at;
}

/* what was read of Snapshot Indices Request Message is what was written, byte for byte */
static void equal_snapshot_indices_request_message(const SnapshotIndicesRequestMessage *read, const SnapshotIndicesRequestMessage *written) {
  assert(read->market_data_group == written->market_data_group);
  for (size_t i = 0; i < 2; i++) { assert(read->component[i] == written->component[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->recovery_hour[i] == written->recovery_hour[i]); }
}

/* Snapshot Indices Request Message: written and read back, then read and written back */
static void check_snapshot_indices_request_message(void) {
  SnapshotIndicesRequestMessage sent;
  SnapshotIndicesRequestMessage got;
  uint8_t wire[11];
  uint8_t again[11];

  any_snapshot_indices_request_message(&sent);
  assert(encode_snapshot_indices_request_message(&sent, wire, 0) == 11);
  assert(decode_snapshot_indices_request_message(&got, wire, 0) == 11);
  equal_snapshot_indices_request_message(&got, &sent);

  for (size_t i = 0; i < 11; i++) { wire[i] = arbitrary(); }
  assert(decode_snapshot_indices_request_message(&got, wire, 0) == 11);
  assert(encode_snapshot_indices_request_message(&got, again, 0) == 11);
  for (size_t i = 0; i < 11; i++) { assert(again[i] == wire[i]); }
}

/* ---- Snapshot Consolidated Feed Request Message: 7 bytes --------------------- */

/* Requests a snapshot of a Consolidated Feed group. */
typedef struct {
  uint8_t market_data_group;  /* byte 0 */
  uint8_t instrument_id[4];   /* bytes 1 to 4 */
  uint8_t snapshot_type;      /* byte 5 */
  uint8_t origin;             /* byte 6 */
} SnapshotConsolidatedFeedRequestMessage;

/* any Snapshot Consolidated Feed Request Message at all: every byte one the checker chooses */
static void any_snapshot_consolidated_feed_request_message(SnapshotConsolidatedFeedRequestMessage *record) {
  record->market_data_group = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->instrument_id[i] = arbitrary(); }
  record->snapshot_type = arbitrary();
  record->origin = arbitrary();
}

/* Snapshot Consolidated Feed Request Message to the wire: 7 bytes from at, returning where the next byte goes */
static size_t encode_snapshot_consolidated_feed_request_message(const SnapshotConsolidatedFeedRequestMessage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->market_data_group;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument_id[i]; }
  wire[at++] = record->snapshot_type;
  wire[at++] = record->origin;

  return at;
}

/* Snapshot Consolidated Feed Request Message off the wire: 7 bytes from at, returning where the next byte lies */
static size_t decode_snapshot_consolidated_feed_request_message(SnapshotConsolidatedFeedRequestMessage *record, const uint8_t *wire, size_t at) {
  record->market_data_group = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->instrument_id[i] = wire[at++]; }
  record->snapshot_type = wire[at++];
  record->origin = wire[at++];

  return at;
}

/* what was read of Snapshot Consolidated Feed Request Message is what was written, byte for byte */
static void equal_snapshot_consolidated_feed_request_message(const SnapshotConsolidatedFeedRequestMessage *read, const SnapshotConsolidatedFeedRequestMessage *written) {
  assert(read->market_data_group == written->market_data_group);
  for (size_t i = 0; i < 4; i++) { assert(read->instrument_id[i] == written->instrument_id[i]); }
  assert(read->snapshot_type == written->snapshot_type);
  assert(read->origin == written->origin);
}

/* Snapshot Consolidated Feed Request Message: written and read back, then read and written back */
static void check_snapshot_consolidated_feed_request_message(void) {
  SnapshotConsolidatedFeedRequestMessage sent;
  SnapshotConsolidatedFeedRequestMessage got;
  uint8_t wire[7];
  uint8_t again[7];

  any_snapshot_consolidated_feed_request_message(&sent);
  assert(encode_snapshot_consolidated_feed_request_message(&sent, wire, 0) == 7);
  assert(decode_snapshot_consolidated_feed_request_message(&got, wire, 0) == 7);
  equal_snapshot_consolidated_feed_request_message(&got, &sent);

  for (size_t i = 0; i < 7; i++) { wire[i] = arbitrary(); }
  assert(decode_snapshot_consolidated_feed_request_message(&got, wire, 0) == 7);
  assert(encode_snapshot_consolidated_feed_request_message(&got, again, 0) == 7);
  for (size_t i = 0; i < 7; i++) { assert(again[i] == wire[i]); }
}

/* ---- What esbmc checks ------------------------------------------------------- */

/* every record of the protocol, each on its own buffers */
static void checks(void) {
  check_client_message_header();
  check_login_message();
  check_replay_request_message();
  check_snapshot_request_message();
  check_snapshot_indices_request_message();
  check_snapshot_consolidated_feed_request_message();
}

int main(void) {
#ifdef CONCRETE
  for (pattern = 0; pattern < 4; pattern++) { checks(); }
#else
  checks();
#endif

  return 0;
}
