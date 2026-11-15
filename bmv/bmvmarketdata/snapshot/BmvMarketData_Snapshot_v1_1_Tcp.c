// bmv/bmvmarketdata/snapshot/BmvMarketData_Snapshot_v1_1_Tcp.c
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

/* ---- INTRA Multicast Header: 17 bytes ---------------------------------------- */

/* BMV INTRA Multicast Header */
typedef struct {
  uint8_t length[2];           /* bytes 0 to 1 */
  uint8_t total_messages;      /* byte 2 */
  uint8_t market_data_group;   /* byte 3 */
  uint8_t session;             /* byte 4 */
  uint8_t sequence_number[4];  /* bytes 5 to 8 */
  uint8_t datetime[8];         /* bytes 9 to 16 */
} INTRAMulticastHeader;

/* any INTRA Multicast Header at all: every byte one the checker chooses */
static void any_i_n_t_r_a_multicast_header(INTRAMulticastHeader *record) {
  for (size_t i = 0; i < 2; i++) { record->length[i] = arbitrary(); }
  record->total_messages = arbitrary();
  record->market_data_group = arbitrary();
  record->session = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->sequence_number[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->datetime[i] = arbitrary(); }
}

/* INTRA Multicast Header to the wire: 17 bytes from at, returning where the next byte goes */
static size_t encode_i_n_t_r_a_multicast_header(const INTRAMulticastHeader *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->length[i]; }
  wire[at++] = record->total_messages;
  wire[at++] = record->market_data_group;
  wire[at++] = record->session;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->sequence_number[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->datetime[i]; }

  return at;
}

/* INTRA Multicast Header off the wire: 17 bytes from at, returning where the next byte lies */
static size_t decode_i_n_t_r_a_multicast_header(INTRAMulticastHeader *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->length[i] = wire[at++]; }
  record->total_messages = wire[at++];
  record->market_data_group = wire[at++];
  record->session = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->sequence_number[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->datetime[i] = wire[at++]; }

  return at;
}

/* what was read of INTRA Multicast Header is what was written, byte for byte */
static void equal_i_n_t_r_a_multicast_header(const INTRAMulticastHeader *read, const INTRAMulticastHeader *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->length[i] == written->length[i]); }
  assert(read->total_messages == written->total_messages);
  assert(read->market_data_group == written->market_data_group);
  assert(read->session == written->session);
  for (size_t i = 0; i < 4; i++) { assert(read->sequence_number[i] == written->sequence_number[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->datetime[i] == written->datetime[i]); }
}

/* INTRA Multicast Header: written and read back, then read and written back */
static void check_i_n_t_r_a_multicast_header(void) {
  INTRAMulticastHeader sent;
  INTRAMulticastHeader got;
  uint8_t wire[17];
  uint8_t again[17];

  any_i_n_t_r_a_multicast_header(&sent);
  assert(encode_i_n_t_r_a_multicast_header(&sent, wire, 0) == 17);
  assert(decode_i_n_t_r_a_multicast_header(&got, wire, 0) == 17);
  equal_i_n_t_r_a_multicast_header(&got, &sent);

  for (size_t i = 0; i < 17; i++) { wire[i] = arbitrary(); }
  assert(decode_i_n_t_r_a_multicast_header(&got, wire, 0) == 17);
  assert(encode_i_n_t_r_a_multicast_header(&got, again, 0) == 17);
  for (size_t i = 0; i < 17; i++) { assert(again[i] == wire[i]); }
}

/* ---- Message Header: 3 bytes ------------------------------------------------- */

/* Message length and message type */
typedef struct {
  uint8_t message_length[2];  /* bytes 0 to 1 */
  uint8_t message_type;       /* byte 2 */
} MessageHeader;

/* any Message Header at all: every byte one the checker chooses */
static void any_message_header(MessageHeader *record) {
  for (size_t i = 0; i < 2; i++) { record->message_length[i] = arbitrary(); }
  record->message_type = arbitrary();
}

/* Message Header to the wire: 3 bytes from at, returning where the next byte goes */
static size_t encode_message_header(const MessageHeader *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->message_length[i]; }
  wire[at++] = record->message_type;

  return at;
}

/* Message Header off the wire: 3 bytes from at, returning where the next byte lies */
static size_t decode_message_header(MessageHeader *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->message_length[i] = wire[at++]; }
  record->message_type = wire[at++];

  return at;
}

/* what was read of Message Header is what was written, byte for byte */
static void equal_message_header(const MessageHeader *read, const MessageHeader *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->message_length[i] == written->message_length[i]); }
  assert(read->message_type == written->message_type);
}

/* Message Header: written and read back, then read and written back */
static void check_message_header(void) {
  MessageHeader sent;
  MessageHeader got;
  uint8_t wire[3];
  uint8_t again[3];

  any_message_header(&sent);
  assert(encode_message_header(&sent, wire, 0) == 3);
  assert(decode_message_header(&got, wire, 0) == 3);
  equal_message_header(&got, &sent);

  for (size_t i = 0; i < 3; i++) { wire[i] = arbitrary(); }
  assert(decode_message_header(&got, wire, 0) == 3);
  assert(encode_message_header(&got, again, 0) == 3);
  for (size_t i = 0; i < 3; i++) { assert(again[i] == wire[i]); }
}

/* ---- Login Response Message: 1 byte ------------------------------------------ */

/* Answers a login request. */
typedef struct {
  uint8_t login_response_status;  /* byte 0 */
} LoginResponseMessage;

/* any Login Response Message at all: every byte one the checker chooses */
static void any_login_response_message(LoginResponseMessage *record) {
  record->login_response_status = arbitrary();
}

/* Login Response Message to the wire: 1 byte from at, returning where the next byte goes */
static size_t encode_login_response_message(const LoginResponseMessage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->login_response_status;

  return at;
}

/* Login Response Message off the wire: 1 byte from at, returning where the next byte lies */
static size_t decode_login_response_message(LoginResponseMessage *record, const uint8_t *wire, size_t at) {
  record->login_response_status = wire[at++];

  return at;
}

/* what was read of Login Response Message is what was written, byte for byte */
static void equal_login_response_message(const LoginResponseMessage *read, const LoginResponseMessage *written) {
  assert(read->login_response_status == written->login_response_status);
}

/* Login Response Message: written and read back, then read and written back */
static void check_login_response_message(void) {
  LoginResponseMessage sent;
  LoginResponseMessage got;
  uint8_t wire[1];
  uint8_t again[1];

  any_login_response_message(&sent);
  assert(encode_login_response_message(&sent, wire, 0) == 1);
  assert(decode_login_response_message(&got, wire, 0) == 1);
  equal_login_response_message(&got, &sent);

  for (size_t i = 0; i < 1; i++) { wire[i] = arbitrary(); }
  assert(decode_login_response_message(&got, wire, 0) == 1);
  assert(encode_login_response_message(&got, again, 0) == 1);
  for (size_t i = 0; i < 1; i++) { assert(again[i] == wire[i]); }
}

/* ---- Replay Response Message: 8 bytes ---------------------------------------- */

/* Answers a replay request; the replayed messages follow an accepted one. */
typedef struct {
  uint8_t market_data_group;       /* byte 0 */
  uint8_t first_message[4];        /* bytes 1 to 4 */
  uint8_t quantity[2];             /* bytes 5 to 6 */
  uint8_t replay_response_status;  /* byte 7 */
} ReplayResponseMessage;

/* any Replay Response Message at all: every byte one the checker chooses */
static void any_replay_response_message(ReplayResponseMessage *record) {
  record->market_data_group = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->first_message[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->quantity[i] = arbitrary(); }
  record->replay_response_status = arbitrary();
}

/* Replay Response Message to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_replay_response_message(const ReplayResponseMessage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->market_data_group;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->first_message[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->quantity[i]; }
  wire[at++] = record->replay_response_status;

  return at;
}

/* Replay Response Message off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_replay_response_message(ReplayResponseMessage *record, const uint8_t *wire, size_t at) {
  record->market_data_group = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->first_message[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->quantity[i] = wire[at++]; }
  record->replay_response_status = wire[at++];

  return at;
}

/* what was read of Replay Response Message is what was written, byte for byte */
static void equal_replay_response_message(const ReplayResponseMessage *read, const ReplayResponseMessage *written) {
  assert(read->market_data_group == written->market_data_group);
  for (size_t i = 0; i < 4; i++) { assert(read->first_message[i] == written->first_message[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->quantity[i] == written->quantity[i]); }
  assert(read->replay_response_status == written->replay_response_status);
}

/* Replay Response Message: written and read back, then read and written back */
static void check_replay_response_message(void) {
  ReplayResponseMessage sent;
  ReplayResponseMessage got;
  uint8_t wire[8];
  uint8_t again[8];

  any_replay_response_message(&sent);
  assert(encode_replay_response_message(&sent, wire, 0) == 8);
  assert(decode_replay_response_message(&got, wire, 0) == 8);
  equal_replay_response_message(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_replay_response_message(&got, wire, 0) == 8);
  assert(encode_replay_response_message(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Snapshot Response Message: 6 bytes -------------------------------------- */

/* Answers a snapshot request. */
typedef struct {
  uint8_t quantity_of_messages[4];   /* bytes 0 to 3 */
  uint8_t snapshot_response_status;  /* byte 4 */
  uint8_t snapshot_type;             /* byte 5 */
} SnapshotResponseMessage;

/* any Snapshot Response Message at all: every byte one the checker chooses */
static void any_snapshot_response_message(SnapshotResponseMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->quantity_of_messages[i] = arbitrary(); }
  record->snapshot_response_status = arbitrary();
  record->snapshot_type = arbitrary();
}

/* Snapshot Response Message to the wire: 6 bytes from at, returning where the next byte goes */
static size_t encode_snapshot_response_message(const SnapshotResponseMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->quantity_of_messages[i]; }
  wire[at++] = record->snapshot_response_status;
  wire[at++] = record->snapshot_type;

  return at;
}

/* Snapshot Response Message off the wire: 6 bytes from at, returning where the next byte lies */
static size_t decode_snapshot_response_message(SnapshotResponseMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->quantity_of_messages[i] = wire[at++]; }
  record->snapshot_response_status = wire[at++];
  record->snapshot_type = wire[at++];

  return at;
}

/* what was read of Snapshot Response Message is what was written, byte for byte */
static void equal_snapshot_response_message(const SnapshotResponseMessage *read, const SnapshotResponseMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->quantity_of_messages[i] == written->quantity_of_messages[i]); }
  assert(read->snapshot_response_status == written->snapshot_response_status);
  assert(read->snapshot_type == written->snapshot_type);
}

/* Snapshot Response Message: written and read back, then read and written back */
static void check_snapshot_response_message(void) {
  SnapshotResponseMessage sent;
  SnapshotResponseMessage got;
  uint8_t wire[6];
  uint8_t again[6];

  any_snapshot_response_message(&sent);
  assert(encode_snapshot_response_message(&sent, wire, 0) == 6);
  assert(decode_snapshot_response_message(&got, wire, 0) == 6);
  equal_snapshot_response_message(&got, &sent);

  for (size_t i = 0; i < 6; i++) { wire[i] = arbitrary(); }
  assert(decode_snapshot_response_message(&got, wire, 0) == 6);
  assert(encode_snapshot_response_message(&got, again, 0) == 6);
  for (size_t i = 0; i < 6; i++) { assert(again[i] == wire[i]); }
}

/* ---- Snapshot Complete Message: 6 bytes -------------------------------------- */

/* Ends a snapshot with the sequence number it synchronizes with on the online channel. */
typedef struct {
  uint8_t sequence_number[4];  /* bytes 0 to 3 */
  uint8_t market_data_group;   /* byte 4 */
  uint8_t snapshot_type;       /* byte 5 */
} SnapshotCompleteMessage;

/* any Snapshot Complete Message at all: every byte one the checker chooses */
static void any_snapshot_complete_message(SnapshotCompleteMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->sequence_number[i] = arbitrary(); }
  record->market_data_group = arbitrary();
  record->snapshot_type = arbitrary();
}

/* Snapshot Complete Message to the wire: 6 bytes from at, returning where the next byte goes */
static size_t encode_snapshot_complete_message(const SnapshotCompleteMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->sequence_number[i]; }
  wire[at++] = record->market_data_group;
  wire[at++] = record->snapshot_type;

  return at;
}

/* Snapshot Complete Message off the wire: 6 bytes from at, returning where the next byte lies */
static size_t decode_snapshot_complete_message(SnapshotCompleteMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->sequence_number[i] = wire[at++]; }
  record->market_data_group = wire[at++];
  record->snapshot_type = wire[at++];

  return at;
}

/* what was read of Snapshot Complete Message is what was written, byte for byte */
static void equal_snapshot_complete_message(const SnapshotCompleteMessage *read, const SnapshotCompleteMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->sequence_number[i] == written->sequence_number[i]); }
  assert(read->market_data_group == written->market_data_group);
  assert(read->snapshot_type == written->snapshot_type);
}

/* Snapshot Complete Message: written and read back, then read and written back */
static void check_snapshot_complete_message(void) {
  SnapshotCompleteMessage sent;
  SnapshotCompleteMessage got;
  uint8_t wire[6];
  uint8_t again[6];

  any_snapshot_complete_message(&sent);
  assert(encode_snapshot_complete_message(&sent, wire, 0) == 6);
  assert(decode_snapshot_complete_message(&got, wire, 0) == 6);
  equal_snapshot_complete_message(&got, &sent);

  for (size_t i = 0; i < 6; i++) { wire[i] = arbitrary(); }
  assert(decode_snapshot_complete_message(&got, wire, 0) == 6);
  assert(encode_snapshot_complete_message(&got, again, 0) == 6);
  for (size_t i = 0; i < 6; i++) { assert(again[i] == wire[i]); }
}

/* ---- Events System Message: 22 bytes ----------------------------------------- */

/* The system of events message is used to inform that an event has occurred, which needs to be of public domain. */
typedef struct {
  uint8_t instrument_number[4];  /* bytes 0 to 3 */
  uint8_t event_code;            /* byte 4 */
  uint8_t market;                /* byte 5 */
  uint8_t sending_time[8];       /* bytes 6 to 13 */
  uint8_t ending_time[8];        /* bytes 14 to 21 */
} EventsSystemMessage;

/* any Events System Message at all: every byte one the checker chooses */
static void any_events_system_message(EventsSystemMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->instrument_number[i] = arbitrary(); }
  record->event_code = arbitrary();
  record->market = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->sending_time[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->ending_time[i] = arbitrary(); }
}

/* Events System Message to the wire: 22 bytes from at, returning where the next byte goes */
static size_t encode_events_system_message(const EventsSystemMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument_number[i]; }
  wire[at++] = record->event_code;
  wire[at++] = record->market;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->sending_time[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->ending_time[i]; }

  return at;
}

/* Events System Message off the wire: 22 bytes from at, returning where the next byte lies */
static size_t decode_events_system_message(EventsSystemMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->instrument_number[i] = wire[at++]; }
  record->event_code = wire[at++];
  record->market = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->sending_time[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->ending_time[i] = wire[at++]; }

  return at;
}

/* what was read of Events System Message is what was written, byte for byte */
static void equal_events_system_message(const EventsSystemMessage *read, const EventsSystemMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->instrument_number[i] == written->instrument_number[i]); }
  assert(read->event_code == written->event_code);
  assert(read->market == written->market);
  for (size_t i = 0; i < 8; i++) { assert(read->sending_time[i] == written->sending_time[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->ending_time[i] == written->ending_time[i]); }
}

/* Events System Message: written and read back, then read and written back */
static void check_events_system_message(void) {
  EventsSystemMessage sent;
  EventsSystemMessage got;
  uint8_t wire[22];
  uint8_t again[22];

  any_events_system_message(&sent);
  assert(encode_events_system_message(&sent, wire, 0) == 22);
  assert(decode_events_system_message(&got, wire, 0) == 22);
  equal_events_system_message(&got, &sent);

  for (size_t i = 0; i < 22; i++) { wire[i] = arbitrary(); }
  assert(decode_events_system_message(&got, wire, 0) == 22);
  assert(encode_events_system_message(&got, again, 0) == 22);
  for (size_t i = 0; i < 22; i++) { assert(again[i] == wire[i]); }
}

/* ---- Trade Cancellation Message: 8 bytes ------------------------------------- */

/* This message is sent when a transaction is cancelled from the BMV system. */
typedef struct {
  uint8_t instrument_number[4];  /* bytes 0 to 3 */
  uint8_t trade_number[4];       /* bytes 4 to 7 */
} TradeCancellationMessage;

/* any Trade Cancellation Message at all: every byte one the checker chooses */
static void any_trade_cancellation_message(TradeCancellationMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->instrument_number[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->trade_number[i] = arbitrary(); }
}

/* Trade Cancellation Message to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_trade_cancellation_message(const TradeCancellationMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument_number[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->trade_number[i]; }

  return at;
}

/* Trade Cancellation Message off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_trade_cancellation_message(TradeCancellationMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->instrument_number[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->trade_number[i] = wire[at++]; }

  return at;
}

/* what was read of Trade Cancellation Message is what was written, byte for byte */
static void equal_trade_cancellation_message(const TradeCancellationMessage *read, const TradeCancellationMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->instrument_number[i] == written->instrument_number[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->trade_number[i] == written->trade_number[i]); }
}

/* Trade Cancellation Message: written and read back, then read and written back */
static void check_trade_cancellation_message(void) {
  TradeCancellationMessage sent;
  TradeCancellationMessage got;
  uint8_t wire[8];
  uint8_t again[8];

  any_trade_cancellation_message(&sent);
  assert(encode_trade_cancellation_message(&sent, wire, 0) == 8);
  assert(decode_trade_cancellation_message(&got, wire, 0) == 8);
  equal_trade_cancellation_message(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_trade_cancellation_message(&got, wire, 0) == 8);
  assert(encode_trade_cancellation_message(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Status Changes Message: 5 bytes ----------------------------------------- */

/* All instruments are in a certain status before and during trading session. */
typedef struct {
  uint8_t instrument_number[4];  /* bytes 0 to 3 */
  uint8_t instrument_status;     /* byte 4 */
} StatusChangesMessage;

/* any Status Changes Message at all: every byte one the checker chooses */
static void any_status_changes_message(StatusChangesMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->instrument_number[i] = arbitrary(); }
  record->instrument_status = arbitrary();
}

/* Status Changes Message to the wire: 5 bytes from at, returning where the next byte goes */
static size_t encode_status_changes_message(const StatusChangesMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument_number[i]; }
  wire[at++] = record->instrument_status;

  return at;
}

/* Status Changes Message off the wire: 5 bytes from at, returning where the next byte lies */
static size_t decode_status_changes_message(StatusChangesMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->instrument_number[i] = wire[at++]; }
  record->instrument_status = wire[at++];

  return at;
}

/* what was read of Status Changes Message is what was written, byte for byte */
static void equal_status_changes_message(const StatusChangesMessage *read, const StatusChangesMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->instrument_number[i] == written->instrument_number[i]); }
  assert(read->instrument_status == written->instrument_status);
}

/* Status Changes Message: written and read back, then read and written back */
static void check_status_changes_message(void) {
  StatusChangesMessage sent;
  StatusChangesMessage got;
  uint8_t wire[5];
  uint8_t again[5];

  any_status_changes_message(&sent);
  assert(encode_status_changes_message(&sent, wire, 0) == 5);
  assert(decode_status_changes_message(&got, wire, 0) == 5);
  equal_status_changes_message(&got, &sent);

  for (size_t i = 0; i < 5; i++) { wire[i] = arbitrary(); }
  assert(decode_status_changes_message(&got, wire, 0) == 5);
  assert(encode_status_changes_message(&got, again, 0) == 5);
  for (size_t i = 0; i < 5; i++) { assert(again[i] == wire[i]); }
}

/* ---- Weighted Average Price Settlement Prices Message: 20 bytes -------------- */

/* For equities market, this message will be sent for each operation containing weighted average price per instrument generated within WAP calculation period (last 20 minutes of trading). */
typedef struct {
  uint8_t instrument_number[4];       /* bytes 0 to 3 */
  uint8_t weighted_average_price[8];  /* bytes 4 to 11 */
  uint8_t volatility[8];              /* bytes 12 to 19 */
} WeightedAveragePriceSettlementPricesMessage;

/* any Weighted Average Price Settlement Prices Message at all: every byte one the checker chooses */
static void any_weighted_average_price_settlement_prices_message(WeightedAveragePriceSettlementPricesMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->instrument_number[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->weighted_average_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->volatility[i] = arbitrary(); }
}

/* Weighted Average Price Settlement Prices Message to the wire: 20 bytes from at, returning where the next byte goes */
static size_t encode_weighted_average_price_settlement_prices_message(const WeightedAveragePriceSettlementPricesMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument_number[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->weighted_average_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->volatility[i]; }

  return at;
}

/* Weighted Average Price Settlement Prices Message off the wire: 20 bytes from at, returning where the next byte lies */
static size_t decode_weighted_average_price_settlement_prices_message(WeightedAveragePriceSettlementPricesMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->instrument_number[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->weighted_average_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->volatility[i] = wire[at++]; }

  return at;
}

/* what was read of Weighted Average Price Settlement Prices Message is what was written, byte for byte */
static void equal_weighted_average_price_settlement_prices_message(const WeightedAveragePriceSettlementPricesMessage *read, const WeightedAveragePriceSettlementPricesMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->instrument_number[i] == written->instrument_number[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->weighted_average_price[i] == written->weighted_average_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->volatility[i] == written->volatility[i]); }
}

/* Weighted Average Price Settlement Prices Message: written and read back, then read and written back */
static void check_weighted_average_price_settlement_prices_message(void) {
  WeightedAveragePriceSettlementPricesMessage sent;
  WeightedAveragePriceSettlementPricesMessage got;
  uint8_t wire[20];
  uint8_t again[20];

  any_weighted_average_price_settlement_prices_message(&sent);
  assert(encode_weighted_average_price_settlement_prices_message(&sent, wire, 0) == 20);
  assert(decode_weighted_average_price_settlement_prices_message(&got, wire, 0) == 20);
  equal_weighted_average_price_settlement_prices_message(&got, &sent);

  for (size_t i = 0; i < 20; i++) { wire[i] = arbitrary(); }
  assert(decode_weighted_average_price_settlement_prices_message(&got, wire, 0) == 20);
  assert(encode_weighted_average_price_settlement_prices_message(&got, again, 0) == 20);
  for (size_t i = 0; i < 20; i++) { assert(again[i] == wire[i]); }
}

/* ---- Capital Trades Message: 51 bytes ---------------------------------------- */

/* Contains information on any BMV accepted transaction. */
typedef struct {
  uint8_t instrument_number[4];  /* bytes 0 to 3 */
  uint8_t trade_time[8];         /* bytes 4 to 11 */
  uint8_t volume_int_324[4];     /* bytes 12 to 15 */
  uint8_t price[8];              /* bytes 16 to 23 */
  uint8_t concertation_type;     /* byte 24 */
  uint8_t trade_number[4];       /* bytes 25 to 28 */
  uint8_t price_setter;          /* byte 29 */
  uint8_t operation_type;        /* byte 30 */
  uint8_t amount[8];             /* bytes 31 to 38 */
  uint8_t buy_alpha_5[5];        /* bytes 39 to 43 */
  uint8_t sell_alpha_5[5];       /* bytes 44 to 48 */
  uint8_t settlement;            /* byte 49 */
  uint8_t auction_indicator;     /* byte 50 */
} CapitalTradesMessage;

/* any Capital Trades Message at all: every byte one the checker chooses */
static void any_capital_trades_message(CapitalTradesMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->instrument_number[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->trade_time[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->volume_int_324[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->price[i] = arbitrary(); }
  record->concertation_type = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->trade_number[i] = arbitrary(); }
  record->price_setter = arbitrary();
  record->operation_type = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->amount[i] = arbitrary(); }
  for (size_t i = 0; i < 5; i++) { record->buy_alpha_5[i] = arbitrary(); }
  for (size_t i = 0; i < 5; i++) { record->sell_alpha_5[i] = arbitrary(); }
  record->settlement = arbitrary();
  record->auction_indicator = arbitrary();
}

/* Capital Trades Message to the wire: 51 bytes from at, returning where the next byte goes */
static size_t encode_capital_trades_message(const CapitalTradesMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument_number[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->trade_time[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->volume_int_324[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price[i]; }
  wire[at++] = record->concertation_type;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->trade_number[i]; }
  wire[at++] = record->price_setter;
  wire[at++] = record->operation_type;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->amount[i]; }
  for (size_t i = 0; i < 5; i++) { wire[at++] = record->buy_alpha_5[i]; }
  for (size_t i = 0; i < 5; i++) { wire[at++] = record->sell_alpha_5[i]; }
  wire[at++] = record->settlement;
  wire[at++] = record->auction_indicator;

  return at;
}

/* Capital Trades Message off the wire: 51 bytes from at, returning where the next byte lies */
static size_t decode_capital_trades_message(CapitalTradesMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->instrument_number[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->trade_time[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->volume_int_324[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->price[i] = wire[at++]; }
  record->concertation_type = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->trade_number[i] = wire[at++]; }
  record->price_setter = wire[at++];
  record->operation_type = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->amount[i] = wire[at++]; }
  for (size_t i = 0; i < 5; i++) { record->buy_alpha_5[i] = wire[at++]; }
  for (size_t i = 0; i < 5; i++) { record->sell_alpha_5[i] = wire[at++]; }
  record->settlement = wire[at++];
  record->auction_indicator = wire[at++];

  return at;
}

/* what was read of Capital Trades Message is what was written, byte for byte */
static void equal_capital_trades_message(const CapitalTradesMessage *read, const CapitalTradesMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->instrument_number[i] == written->instrument_number[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->trade_time[i] == written->trade_time[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->volume_int_324[i] == written->volume_int_324[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->price[i] == written->price[i]); }
  assert(read->concertation_type == written->concertation_type);
  for (size_t i = 0; i < 4; i++) { assert(read->trade_number[i] == written->trade_number[i]); }
  assert(read->price_setter == written->price_setter);
  assert(read->operation_type == written->operation_type);
  for (size_t i = 0; i < 8; i++) { assert(read->amount[i] == written->amount[i]); }
  for (size_t i = 0; i < 5; i++) { assert(read->buy_alpha_5[i] == written->buy_alpha_5[i]); }
  for (size_t i = 0; i < 5; i++) { assert(read->sell_alpha_5[i] == written->sell_alpha_5[i]); }
  assert(read->settlement == written->settlement);
  assert(read->auction_indicator == written->auction_indicator);
}

/* Capital Trades Message: written and read back, then read and written back */
static void check_capital_trades_message(void) {
  CapitalTradesMessage sent;
  CapitalTradesMessage got;
  uint8_t wire[51];
  uint8_t again[51];

  any_capital_trades_message(&sent);
  assert(encode_capital_trades_message(&sent, wire, 0) == 51);
  assert(decode_capital_trades_message(&got, wire, 0) == 51);
  equal_capital_trades_message(&got, &sent);

  for (size_t i = 0; i < 51; i++) { wire[i] = arbitrary(); }
  assert(decode_capital_trades_message(&got, wire, 0) == 51);
  assert(encode_capital_trades_message(&got, again, 0) == 51);
  for (size_t i = 0; i < 51; i++) { assert(again[i] == wire[i]); }
}

/* ---- Probable Allocation Price Message: 16 bytes ----------------------------- */

/* Sent during any auction type (Opening, Continuous, Volatility and Intraday) and only on instruments where there is already a virtual match or pre-allocation. */
typedef struct {
  uint8_t instrument_number[4];          /* bytes 0 to 3 */
  uint8_t probable_allocation_price[8];  /* bytes 4 to 11 */
  uint8_t volume_int_324[4];             /* bytes 12 to 15 */
} ProbableAllocationPriceMessage;

/* any Probable Allocation Price Message at all: every byte one the checker chooses */
static void any_probable_allocation_price_message(ProbableAllocationPriceMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->instrument_number[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->probable_allocation_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->volume_int_324[i] = arbitrary(); }
}

/* Probable Allocation Price Message to the wire: 16 bytes from at, returning where the next byte goes */
static size_t encode_probable_allocation_price_message(const ProbableAllocationPriceMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument_number[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->probable_allocation_price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->volume_int_324[i]; }

  return at;
}

/* Probable Allocation Price Message off the wire: 16 bytes from at, returning where the next byte lies */
static size_t decode_probable_allocation_price_message(ProbableAllocationPriceMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->instrument_number[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->probable_allocation_price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->volume_int_324[i] = wire[at++]; }

  return at;
}

/* what was read of Probable Allocation Price Message is what was written, byte for byte */
static void equal_probable_allocation_price_message(const ProbableAllocationPriceMessage *read, const ProbableAllocationPriceMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->instrument_number[i] == written->instrument_number[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->probable_allocation_price[i] == written->probable_allocation_price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->volume_int_324[i] == written->volume_int_324[i]); }
}

/* Probable Allocation Price Message: written and read back, then read and written back */
static void check_probable_allocation_price_message(void) {
  ProbableAllocationPriceMessage sent;
  ProbableAllocationPriceMessage got;
  uint8_t wire[16];
  uint8_t again[16];

  any_probable_allocation_price_message(&sent);
  assert(encode_probable_allocation_price_message(&sent, wire, 0) == 16);
  assert(decode_probable_allocation_price_message(&got, wire, 0) == 16);
  equal_probable_allocation_price_message(&got, &sent);

  for (size_t i = 0; i < 16; i++) { wire[i] = arbitrary(); }
  assert(decode_probable_allocation_price_message(&got, wire, 0) == 16);
  assert(encode_probable_allocation_price_message(&got, again, 0) == 16);
  for (size_t i = 0; i < 16; i++) { assert(again[i] == wire[i]); }
}

/* ---- Continuous Auctions Beginning Message: 20 bytes ------------------------- */

/* Sent at the moment one of the Continuous, Volatility or SIC auctions is generated. */
typedef struct {
  uint8_t instrument_number[4];          /* bytes 0 to 3 */
  uint8_t beginning_time_of_auction[8];  /* bytes 4 to 11 */
  uint8_t end_auction_time[8];           /* bytes 12 to 19 */
} ContinuousAuctionsBeginningMessage;

/* any Continuous Auctions Beginning Message at all: every byte one the checker chooses */
static void any_continuous_auctions_beginning_message(ContinuousAuctionsBeginningMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->instrument_number[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->beginning_time_of_auction[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->end_auction_time[i] = arbitrary(); }
}

/* Continuous Auctions Beginning Message to the wire: 20 bytes from at, returning where the next byte goes */
static size_t encode_continuous_auctions_beginning_message(const ContinuousAuctionsBeginningMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument_number[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->beginning_time_of_auction[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->end_auction_time[i]; }

  return at;
}

/* Continuous Auctions Beginning Message off the wire: 20 bytes from at, returning where the next byte lies */
static size_t decode_continuous_auctions_beginning_message(ContinuousAuctionsBeginningMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->instrument_number[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->beginning_time_of_auction[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->end_auction_time[i] = wire[at++]; }

  return at;
}

/* what was read of Continuous Auctions Beginning Message is what was written, byte for byte */
static void equal_continuous_auctions_beginning_message(const ContinuousAuctionsBeginningMessage *read, const ContinuousAuctionsBeginningMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->instrument_number[i] == written->instrument_number[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->beginning_time_of_auction[i] == written->beginning_time_of_auction[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->end_auction_time[i] == written->end_auction_time[i]); }
}

/* Continuous Auctions Beginning Message: written and read back, then read and written back */
static void check_continuous_auctions_beginning_message(void) {
  ContinuousAuctionsBeginningMessage sent;
  ContinuousAuctionsBeginningMessage got;
  uint8_t wire[20];
  uint8_t again[20];

  any_continuous_auctions_beginning_message(&sent);
  assert(encode_continuous_auctions_beginning_message(&sent, wire, 0) == 20);
  assert(decode_continuous_auctions_beginning_message(&got, wire, 0) == 20);
  equal_continuous_auctions_beginning_message(&got, &sent);

  for (size_t i = 0; i < 20; i++) { wire[i] = arbitrary(); }
  assert(decode_continuous_auctions_beginning_message(&got, wire, 0) == 20);
  assert(encode_continuous_auctions_beginning_message(&got, again, 0) == 20);
  for (size_t i = 0; i < 20; i++) { assert(again[i] == wire[i]); }
}

/* ---- Middle Price Existing Quotes Message: 5 bytes --------------------------- */

/* Generated when an instrument enters a posture in the hidden electronic Middle Price book. */
typedef struct {
  uint8_t instrument_number[4];  /* bytes 0 to 3 */
  uint8_t existing_postures;     /* byte 4 */
} MiddlePriceExistingQuotesMessage;

/* any Middle Price Existing Quotes Message at all: every byte one the checker chooses */
static void any_middle_price_existing_quotes_message(MiddlePriceExistingQuotesMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->instrument_number[i] = arbitrary(); }
  record->existing_postures = arbitrary();
}

/* Middle Price Existing Quotes Message to the wire: 5 bytes from at, returning where the next byte goes */
static size_t encode_middle_price_existing_quotes_message(const MiddlePriceExistingQuotesMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument_number[i]; }
  wire[at++] = record->existing_postures;

  return at;
}

/* Middle Price Existing Quotes Message off the wire: 5 bytes from at, returning where the next byte lies */
static size_t decode_middle_price_existing_quotes_message(MiddlePriceExistingQuotesMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->instrument_number[i] = wire[at++]; }
  record->existing_postures = wire[at++];

  return at;
}

/* what was read of Middle Price Existing Quotes Message is what was written, byte for byte */
static void equal_middle_price_existing_quotes_message(const MiddlePriceExistingQuotesMessage *read, const MiddlePriceExistingQuotesMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->instrument_number[i] == written->instrument_number[i]); }
  assert(read->existing_postures == written->existing_postures);
}

/* Middle Price Existing Quotes Message: written and read back, then read and written back */
static void check_middle_price_existing_quotes_message(void) {
  MiddlePriceExistingQuotesMessage sent;
  MiddlePriceExistingQuotesMessage got;
  uint8_t wire[5];
  uint8_t again[5];

  any_middle_price_existing_quotes_message(&sent);
  assert(encode_middle_price_existing_quotes_message(&sent, wire, 0) == 5);
  assert(decode_middle_price_existing_quotes_message(&got, wire, 0) == 5);
  equal_middle_price_existing_quotes_message(&got, &sent);

  for (size_t i = 0; i < 5; i++) { wire[i] = arbitrary(); }
  assert(decode_middle_price_existing_quotes_message(&got, wire, 0) == 5);
  assert(encode_middle_price_existing_quotes_message(&got, again, 0) == 5);
  for (size_t i = 0; i < 5; i++) { assert(again[i] == wire[i]); }
}

/* ---- Registry Operations Message: 61 bytes ----------------------------------- */

/* Sent whenever there is a debt or capital instrument placement. */
typedef struct {
  uint8_t instrument_number[4];  /* bytes 0 to 3 */
  uint8_t offer_type;            /* byte 4 */
  uint8_t income;                /* byte 5 */
  uint8_t value_type[4];         /* bytes 6 to 9 */
  uint8_t issuer[7];             /* bytes 10 to 16 */
  uint8_t series[6];             /* bytes 17 to 22 */
  uint8_t maximum_volume[8];     /* bytes 23 to 30 */
  uint8_t registered_volume[8];  /* bytes 31 to 38 */
  uint8_t price_rate[8];         /* bytes 39 to 46 */
  uint8_t settlement_date[8];    /* bytes 47 to 54 */
  uint8_t firm[5];               /* bytes 55 to 59 */
  uint8_t movement;              /* byte 60 */
} RegistryOperationsMessage;

/* any Registry Operations Message at all: every byte one the checker chooses */
static void any_registry_operations_message(RegistryOperationsMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->instrument_number[i] = arbitrary(); }
  record->offer_type = arbitrary();
  record->income = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->value_type[i] = arbitrary(); }
  for (size_t i = 0; i < 7; i++) { record->issuer[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->series[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->maximum_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->registered_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->price_rate[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->settlement_date[i] = arbitrary(); }
  for (size_t i = 0; i < 5; i++) { record->firm[i] = arbitrary(); }
  record->movement = arbitrary();
}

/* Registry Operations Message to the wire: 61 bytes from at, returning where the next byte goes */
static size_t encode_registry_operations_message(const RegistryOperationsMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument_number[i]; }
  wire[at++] = record->offer_type;
  wire[at++] = record->income;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->value_type[i]; }
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->issuer[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->series[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->maximum_volume[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->registered_volume[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price_rate[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->settlement_date[i]; }
  for (size_t i = 0; i < 5; i++) { wire[at++] = record->firm[i]; }
  wire[at++] = record->movement;

  return at;
}

/* Registry Operations Message off the wire: 61 bytes from at, returning where the next byte lies */
static size_t decode_registry_operations_message(RegistryOperationsMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->instrument_number[i] = wire[at++]; }
  record->offer_type = wire[at++];
  record->income = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->value_type[i] = wire[at++]; }
  for (size_t i = 0; i < 7; i++) { record->issuer[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->series[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->maximum_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->registered_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->price_rate[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->settlement_date[i] = wire[at++]; }
  for (size_t i = 0; i < 5; i++) { record->firm[i] = wire[at++]; }
  record->movement = wire[at++];

  return at;
}

/* what was read of Registry Operations Message is what was written, byte for byte */
static void equal_registry_operations_message(const RegistryOperationsMessage *read, const RegistryOperationsMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->instrument_number[i] == written->instrument_number[i]); }
  assert(read->offer_type == written->offer_type);
  assert(read->income == written->income);
  for (size_t i = 0; i < 4; i++) { assert(read->value_type[i] == written->value_type[i]); }
  for (size_t i = 0; i < 7; i++) { assert(read->issuer[i] == written->issuer[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->series[i] == written->series[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->maximum_volume[i] == written->maximum_volume[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->registered_volume[i] == written->registered_volume[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->price_rate[i] == written->price_rate[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->settlement_date[i] == written->settlement_date[i]); }
  for (size_t i = 0; i < 5; i++) { assert(read->firm[i] == written->firm[i]); }
  assert(read->movement == written->movement);
}

/* Registry Operations Message: written and read back, then read and written back */
static void check_registry_operations_message(void) {
  RegistryOperationsMessage sent;
  RegistryOperationsMessage got;
  uint8_t wire[61];
  uint8_t again[61];

  any_registry_operations_message(&sent);
  assert(encode_registry_operations_message(&sent, wire, 0) == 61);
  assert(decode_registry_operations_message(&got, wire, 0) == 61);
  equal_registry_operations_message(&got, &sent);

  for (size_t i = 0; i < 61; i++) { wire[i] = arbitrary(); }
  assert(decode_registry_operations_message(&got, wire, 0) == 61);
  assert(encode_registry_operations_message(&got, again, 0) == 61);
  for (size_t i = 0; i < 61; i++) { assert(again[i] == wire[i]); }
}

/* ---- Mutual Fund Trades Message: 52 bytes ------------------------------------ */

/* Contains any mutual funds operation realized. */
typedef struct {
  uint8_t instrument_number[4];             /* bytes 0 to 3 */
  uint8_t trade_date[8];                    /* bytes 4 to 11 */
  uint8_t price[8];                         /* bytes 12 to 19 */
  uint8_t book_value[8];                    /* bytes 20 to 27 */
  uint8_t number_of_sales_transactions[4];  /* bytes 28 to 31 */
  uint8_t sales_volume[8];                  /* bytes 32 to 39 */
  uint8_t number_of_buy_transactions[4];    /* bytes 40 to 43 */
  uint8_t buy_volume[8];                    /* bytes 44 to 51 */
} MutualFundTradesMessage;

/* any Mutual Fund Trades Message at all: every byte one the checker chooses */
static void any_mutual_fund_trades_message(MutualFundTradesMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->instrument_number[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->trade_date[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->book_value[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->number_of_sales_transactions[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->sales_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->number_of_buy_transactions[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->buy_volume[i] = arbitrary(); }
}

/* Mutual Fund Trades Message to the wire: 52 bytes from at, returning where the next byte goes */
static size_t encode_mutual_fund_trades_message(const MutualFundTradesMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument_number[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->trade_date[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->book_value[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->number_of_sales_transactions[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->sales_volume[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->number_of_buy_transactions[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->buy_volume[i]; }

  return at;
}

/* Mutual Fund Trades Message off the wire: 52 bytes from at, returning where the next byte lies */
static size_t decode_mutual_fund_trades_message(MutualFundTradesMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->instrument_number[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->trade_date[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->book_value[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->number_of_sales_transactions[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->sales_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->number_of_buy_transactions[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->buy_volume[i] = wire[at++]; }

  return at;
}

/* what was read of Mutual Fund Trades Message is what was written, byte for byte */
static void equal_mutual_fund_trades_message(const MutualFundTradesMessage *read, const MutualFundTradesMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->instrument_number[i] == written->instrument_number[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->trade_date[i] == written->trade_date[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->price[i] == written->price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->book_value[i] == written->book_value[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->number_of_sales_transactions[i] == written->number_of_sales_transactions[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->sales_volume[i] == written->sales_volume[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->number_of_buy_transactions[i] == written->number_of_buy_transactions[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->buy_volume[i] == written->buy_volume[i]); }
}

/* Mutual Fund Trades Message: written and read back, then read and written back */
static void check_mutual_fund_trades_message(void) {
  MutualFundTradesMessage sent;
  MutualFundTradesMessage got;
  uint8_t wire[52];
  uint8_t again[52];

  any_mutual_fund_trades_message(&sent);
  assert(encode_mutual_fund_trades_message(&sent, wire, 0) == 52);
  assert(decode_mutual_fund_trades_message(&got, wire, 0) == 52);
  equal_mutual_fund_trades_message(&got, &sent);

  for (size_t i = 0; i < 52; i++) { wire[i] = arbitrary(); }
  assert(decode_mutual_fund_trades_message(&got, wire, 0) == 52);
  assert(encode_mutual_fund_trades_message(&got, again, 0) == 52);
  for (size_t i = 0; i < 52; i++) { assert(again[i] == wire[i]); }
}

/* ---- Tradability Message: 64 bytes ------------------------------------------- */

/* Message sent every half hour during trading session, informing general tradability by instrument. */
typedef struct {
  uint8_t instrument_number[4];     /* bytes 0 to 3 */
  uint8_t number_of_operations[4];  /* bytes 4 to 7 */
  uint8_t volume_int_648[8];        /* bytes 8 to 15 */
  uint8_t amount[8];                /* bytes 16 to 23 */
  uint8_t opening_price[8];         /* bytes 24 to 31 */
  uint8_t maximum[8];               /* bytes 32 to 39 */
  uint8_t minimum[8];               /* bytes 40 to 47 */
  uint8_t average[8];               /* bytes 48 to 55 */
  uint8_t last[8];                  /* bytes 56 to 63 */
} TradabilityMessage;

/* any Tradability Message at all: every byte one the checker chooses */
static void any_tradability_message(TradabilityMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->instrument_number[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->number_of_operations[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->volume_int_648[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->amount[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->opening_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->maximum[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->minimum[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->average[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->last[i] = arbitrary(); }
}

/* Tradability Message to the wire: 64 bytes from at, returning where the next byte goes */
static size_t encode_tradability_message(const TradabilityMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument_number[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->number_of_operations[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->volume_int_648[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->amount[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->opening_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->maximum[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->minimum[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->average[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->last[i]; }

  return at;
}

/* Tradability Message off the wire: 64 bytes from at, returning where the next byte lies */
static size_t decode_tradability_message(TradabilityMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->instrument_number[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->number_of_operations[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->volume_int_648[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->amount[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->opening_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->maximum[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->minimum[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->average[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->last[i] = wire[at++]; }

  return at;
}

/* what was read of Tradability Message is what was written, byte for byte */
static void equal_tradability_message(const TradabilityMessage *read, const TradabilityMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->instrument_number[i] == written->instrument_number[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->number_of_operations[i] == written->number_of_operations[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->volume_int_648[i] == written->volume_int_648[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->amount[i] == written->amount[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->opening_price[i] == written->opening_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->maximum[i] == written->maximum[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->minimum[i] == written->minimum[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->average[i] == written->average[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->last[i] == written->last[i]); }
}

/* Tradability Message: written and read back, then read and written back */
static void check_tradability_message(void) {
  TradabilityMessage sent;
  TradabilityMessage got;
  uint8_t wire[64];
  uint8_t again[64];

  any_tradability_message(&sent);
  assert(encode_tradability_message(&sent, wire, 0) == 64);
  assert(decode_tradability_message(&got, wire, 0) == 64);
  equal_tradability_message(&got, &sent);

  for (size_t i = 0; i < 64; i++) { wire[i] = arbitrary(); }
  assert(decode_tradability_message(&got, wire, 0) == 64);
  assert(encode_tradability_message(&got, again, 0) == 64);
  for (size_t i = 0; i < 64; i++) { assert(again[i] == wire[i]); }
}

/* ---- Virtual Trades Message: 25 bytes ---------------------------------------- */

/* When an operation has been pre-assigned to the at closing and average day Price electronic books, a virtual trade message is sent, where also notifying of this operation. */
typedef struct {
  uint8_t instrument_number[4];   /* bytes 0 to 3 */
  uint8_t virtual_trades_status;  /* byte 4 */
  uint8_t operation_type;         /* byte 5 */
  uint8_t number[4];              /* bytes 6 to 9 */
  uint8_t volume_int_324[4];      /* bytes 10 to 13 */
  uint8_t concertation;           /* byte 14 */
  uint8_t buy_alpha_5[5];         /* bytes 15 to 19 */
  uint8_t sell_alpha_5[5];        /* bytes 20 to 24 */
} VirtualTradesMessage;

/* any Virtual Trades Message at all: every byte one the checker chooses */
static void any_virtual_trades_message(VirtualTradesMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->instrument_number[i] = arbitrary(); }
  record->virtual_trades_status = arbitrary();
  record->operation_type = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->number[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->volume_int_324[i] = arbitrary(); }
  record->concertation = arbitrary();
  for (size_t i = 0; i < 5; i++) { record->buy_alpha_5[i] = arbitrary(); }
  for (size_t i = 0; i < 5; i++) { record->sell_alpha_5[i] = arbitrary(); }
}

/* Virtual Trades Message to the wire: 25 bytes from at, returning where the next byte goes */
static size_t encode_virtual_trades_message(const VirtualTradesMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument_number[i]; }
  wire[at++] = record->virtual_trades_status;
  wire[at++] = record->operation_type;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->number[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->volume_int_324[i]; }
  wire[at++] = record->concertation;
  for (size_t i = 0; i < 5; i++) { wire[at++] = record->buy_alpha_5[i]; }
  for (size_t i = 0; i < 5; i++) { wire[at++] = record->sell_alpha_5[i]; }

  return at;
}

/* Virtual Trades Message off the wire: 25 bytes from at, returning where the next byte lies */
static size_t decode_virtual_trades_message(VirtualTradesMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->instrument_number[i] = wire[at++]; }
  record->virtual_trades_status = wire[at++];
  record->operation_type = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->number[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->volume_int_324[i] = wire[at++]; }
  record->concertation = wire[at++];
  for (size_t i = 0; i < 5; i++) { record->buy_alpha_5[i] = wire[at++]; }
  for (size_t i = 0; i < 5; i++) { record->sell_alpha_5[i] = wire[at++]; }

  return at;
}

/* what was read of Virtual Trades Message is what was written, byte for byte */
static void equal_virtual_trades_message(const VirtualTradesMessage *read, const VirtualTradesMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->instrument_number[i] == written->instrument_number[i]); }
  assert(read->virtual_trades_status == written->virtual_trades_status);
  assert(read->operation_type == written->operation_type);
  for (size_t i = 0; i < 4; i++) { assert(read->number[i] == written->number[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->volume_int_324[i] == written->volume_int_324[i]); }
  assert(read->concertation == written->concertation);
  for (size_t i = 0; i < 5; i++) { assert(read->buy_alpha_5[i] == written->buy_alpha_5[i]); }
  for (size_t i = 0; i < 5; i++) { assert(read->sell_alpha_5[i] == written->sell_alpha_5[i]); }
}

/* Virtual Trades Message: written and read back, then read and written back */
static void check_virtual_trades_message(void) {
  VirtualTradesMessage sent;
  VirtualTradesMessage got;
  uint8_t wire[25];
  uint8_t again[25];

  any_virtual_trades_message(&sent);
  assert(encode_virtual_trades_message(&sent, wire, 0) == 25);
  assert(decode_virtual_trades_message(&got, wire, 0) == 25);
  equal_virtual_trades_message(&got, &sent);

  for (size_t i = 0; i < 25; i++) { wire[i] = arbitrary(); }
  assert(decode_virtual_trades_message(&got, wire, 0) == 25);
  assert(encode_virtual_trades_message(&got, again, 0) == 25);
  for (size_t i = 0; i < 25; i++) { assert(again[i] == wire[i]); }
}

/* ---- Order Addition Message: 34 bytes ---------------------------------------- */

/* The moment an order is being accepted by the BMV central system; this message is diffused to the corresponding media. */
typedef struct {
  uint8_t instrument_number[4];  /* bytes 0 to 3 */
  uint8_t date_and_time[8];      /* bytes 4 to 11 */
  uint8_t number[4];             /* bytes 12 to 15 */
  uint8_t direction;             /* byte 16 */
  uint8_t volume_int_324[4];     /* bytes 17 to 20 */
  uint8_t price[8];              /* bytes 21 to 28 */
  uint8_t participant[5];        /* bytes 29 to 33 */
} OrderAdditionMessage;

/* any Order Addition Message at all: every byte one the checker chooses */
static void any_order_addition_message(OrderAdditionMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->instrument_number[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->date_and_time[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->number[i] = arbitrary(); }
  record->direction = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->volume_int_324[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->price[i] = arbitrary(); }
  for (size_t i = 0; i < 5; i++) { record->participant[i] = arbitrary(); }
}

/* Order Addition Message to the wire: 34 bytes from at, returning where the next byte goes */
static size_t encode_order_addition_message(const OrderAdditionMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument_number[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->date_and_time[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->number[i]; }
  wire[at++] = record->direction;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->volume_int_324[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price[i]; }
  for (size_t i = 0; i < 5; i++) { wire[at++] = record->participant[i]; }

  return at;
}

/* Order Addition Message off the wire: 34 bytes from at, returning where the next byte lies */
static size_t decode_order_addition_message(OrderAdditionMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->instrument_number[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->date_and_time[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->number[i] = wire[at++]; }
  record->direction = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->volume_int_324[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->price[i] = wire[at++]; }
  for (size_t i = 0; i < 5; i++) { record->participant[i] = wire[at++]; }

  return at;
}

/* what was read of Order Addition Message is what was written, byte for byte */
static void equal_order_addition_message(const OrderAdditionMessage *read, const OrderAdditionMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->instrument_number[i] == written->instrument_number[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->date_and_time[i] == written->date_and_time[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->number[i] == written->number[i]); }
  assert(read->direction == written->direction);
  for (size_t i = 0; i < 4; i++) { assert(read->volume_int_324[i] == written->volume_int_324[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->price[i] == written->price[i]); }
  for (size_t i = 0; i < 5; i++) { assert(read->participant[i] == written->participant[i]); }
}

/* Order Addition Message: written and read back, then read and written back */
static void check_order_addition_message(void) {
  OrderAdditionMessage sent;
  OrderAdditionMessage got;
  uint8_t wire[34];
  uint8_t again[34];

  any_order_addition_message(&sent);
  assert(encode_order_addition_message(&sent, wire, 0) == 34);
  assert(decode_order_addition_message(&got, wire, 0) == 34);
  equal_order_addition_message(&got, &sent);

  for (size_t i = 0; i < 34; i++) { wire[i] = arbitrary(); }
  assert(decode_order_addition_message(&got, wire, 0) == 34);
  assert(encode_order_addition_message(&got, again, 0) == 34);
  for (size_t i = 0; i < 34; i++) { assert(again[i] == wire[i]); }
}

/* ---- Execution Of Orders Message: 32 bytes ----------------------------------- */

/* The message is disseminated at the time there is a matching or closing in BMV’s electronic system. */
typedef struct {
  uint8_t instrument_number[4];  /* bytes 0 to 3 */
  uint8_t date[8];               /* bytes 4 to 11 */
  uint8_t number[4];             /* bytes 12 to 15 */
  uint8_t volume_int_324[4];     /* bytes 16 to 19 */
  uint8_t trade_number[4];       /* bytes 20 to 23 */
  uint8_t execution_price[8];    /* bytes 24 to 31 */
} ExecutionOfOrdersMessage;

/* any Execution Of Orders Message at all: every byte one the checker chooses */
static void any_execution_of_orders_message(ExecutionOfOrdersMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->instrument_number[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->date[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->number[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->volume_int_324[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->trade_number[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->execution_price[i] = arbitrary(); }
}

/* Execution Of Orders Message to the wire: 32 bytes from at, returning where the next byte goes */
static size_t encode_execution_of_orders_message(const ExecutionOfOrdersMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument_number[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->date[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->number[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->volume_int_324[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->trade_number[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->execution_price[i]; }

  return at;
}

/* Execution Of Orders Message off the wire: 32 bytes from at, returning where the next byte lies */
static size_t decode_execution_of_orders_message(ExecutionOfOrdersMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->instrument_number[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->date[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->number[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->volume_int_324[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->trade_number[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->execution_price[i] = wire[at++]; }

  return at;
}

/* what was read of Execution Of Orders Message is what was written, byte for byte */
static void equal_execution_of_orders_message(const ExecutionOfOrdersMessage *read, const ExecutionOfOrdersMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->instrument_number[i] == written->instrument_number[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->date[i] == written->date[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->number[i] == written->number[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->volume_int_324[i] == written->volume_int_324[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->trade_number[i] == written->trade_number[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->execution_price[i] == written->execution_price[i]); }
}

/* Execution Of Orders Message: written and read back, then read and written back */
static void check_execution_of_orders_message(void) {
  ExecutionOfOrdersMessage sent;
  ExecutionOfOrdersMessage got;
  uint8_t wire[32];
  uint8_t again[32];

  any_execution_of_orders_message(&sent);
  assert(encode_execution_of_orders_message(&sent, wire, 0) == 32);
  assert(decode_execution_of_orders_message(&got, wire, 0) == 32);
  equal_execution_of_orders_message(&got, &sent);

  for (size_t i = 0; i < 32; i++) { wire[i] = arbitrary(); }
  assert(decode_execution_of_orders_message(&got, wire, 0) == 32);
  assert(encode_execution_of_orders_message(&got, again, 0) == 32);
  for (size_t i = 0; i < 32; i++) { assert(again[i] == wire[i]); }
}

/* ---- Order Cancellation Message: 16 bytes ------------------------------------ */

/* This message fully eliminates the order from the trading floor. */
typedef struct {
  uint8_t instrument_number[4];  /* bytes 0 to 3 */
  uint8_t date[8];               /* bytes 4 to 11 */
  uint8_t number[4];             /* bytes 12 to 15 */
} OrderCancellationMessage;

/* any Order Cancellation Message at all: every byte one the checker chooses */
static void any_order_cancellation_message(OrderCancellationMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->instrument_number[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->date[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->number[i] = arbitrary(); }
}

/* Order Cancellation Message to the wire: 16 bytes from at, returning where the next byte goes */
static size_t encode_order_cancellation_message(const OrderCancellationMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument_number[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->date[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->number[i]; }

  return at;
}

/* Order Cancellation Message off the wire: 16 bytes from at, returning where the next byte lies */
static size_t decode_order_cancellation_message(OrderCancellationMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->instrument_number[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->date[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->number[i] = wire[at++]; }

  return at;
}

/* what was read of Order Cancellation Message is what was written, byte for byte */
static void equal_order_cancellation_message(const OrderCancellationMessage *read, const OrderCancellationMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->instrument_number[i] == written->instrument_number[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->date[i] == written->date[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->number[i] == written->number[i]); }
}

/* Order Cancellation Message: written and read back, then read and written back */
static void check_order_cancellation_message(void) {
  OrderCancellationMessage sent;
  OrderCancellationMessage got;
  uint8_t wire[16];
  uint8_t again[16];

  any_order_cancellation_message(&sent);
  assert(encode_order_cancellation_message(&sent, wire, 0) == 16);
  assert(decode_order_cancellation_message(&got, wire, 0) == 16);
  equal_order_cancellation_message(&got, &sent);

  for (size_t i = 0; i < 16; i++) { wire[i] = arbitrary(); }
  assert(decode_order_cancellation_message(&got, wire, 0) == 16);
  assert(encode_order_cancellation_message(&got, again, 0) == 16);
  for (size_t i = 0; i < 16; i++) { assert(again[i] == wire[i]); }
}

/* ---- Order Change Message: 41 bytes ------------------------------------------ */

/* Message sent when the order changes one of its data, the system allocates to it a new priority in the electronic book, the order to be replaced is identified with the original Instrument, Date and Number, the new allocation of priority in the electronic book appears in the New Date and Number fields. */
typedef struct {
  uint8_t instrument_number[4];  /* bytes 0 to 3 */
  uint8_t original_date[8];      /* bytes 4 to 11 */
  uint8_t original_number[4];    /* bytes 12 to 15 */
  uint8_t new_date[8];           /* bytes 16 to 23 */
  uint8_t new_number[4];         /* bytes 24 to 27 */
  uint8_t direction;             /* byte 28 */
  uint8_t volume_int_324[4];     /* bytes 29 to 32 */
  uint8_t price[8];              /* bytes 33 to 40 */
} OrderChangeMessage;

/* any Order Change Message at all: every byte one the checker chooses */
static void any_order_change_message(OrderChangeMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->instrument_number[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->original_date[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->original_number[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->new_date[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->new_number[i] = arbitrary(); }
  record->direction = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->volume_int_324[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->price[i] = arbitrary(); }
}

/* Order Change Message to the wire: 41 bytes from at, returning where the next byte goes */
static size_t encode_order_change_message(const OrderChangeMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument_number[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->original_date[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->original_number[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->new_date[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->new_number[i]; }
  wire[at++] = record->direction;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->volume_int_324[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price[i]; }

  return at;
}

/* Order Change Message off the wire: 41 bytes from at, returning where the next byte lies */
static size_t decode_order_change_message(OrderChangeMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->instrument_number[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->original_date[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->original_number[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->new_date[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->new_number[i] = wire[at++]; }
  record->direction = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->volume_int_324[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->price[i] = wire[at++]; }

  return at;
}

/* what was read of Order Change Message is what was written, byte for byte */
static void equal_order_change_message(const OrderChangeMessage *read, const OrderChangeMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->instrument_number[i] == written->instrument_number[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->original_date[i] == written->original_date[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->original_number[i] == written->original_number[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->new_date[i] == written->new_date[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->new_number[i] == written->new_number[i]); }
  assert(read->direction == written->direction);
  for (size_t i = 0; i < 4; i++) { assert(read->volume_int_324[i] == written->volume_int_324[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->price[i] == written->price[i]); }
}

/* Order Change Message: written and read back, then read and written back */
static void check_order_change_message(void) {
  OrderChangeMessage sent;
  OrderChangeMessage got;
  uint8_t wire[41];
  uint8_t again[41];

  any_order_change_message(&sent);
  assert(encode_order_change_message(&sent, wire, 0) == 41);
  assert(decode_order_change_message(&got, wire, 0) == 41);
  equal_order_change_message(&got, &sent);

  for (size_t i = 0; i < 41; i++) { wire[i] = arbitrary(); }
  assert(decode_order_change_message(&got, wire, 0) == 41);
  assert(encode_order_change_message(&got, again, 0) == 41);
  for (size_t i = 0; i < 41; i++) { assert(again[i] == wire[i]); }
}

/* ---- Best Offer Message: 18 bytes -------------------------------------------- */

/* Message sent by instrument when best offer changes in the electronic book. */
typedef struct {
  uint8_t instrument_number[4];  /* bytes 0 to 3 */
  uint8_t volume_int_324[4];     /* bytes 4 to 7 */
  uint8_t price_rate[8];         /* bytes 8 to 15 */
  uint8_t offer_direction;       /* byte 16 */
  uint8_t operation_type;        /* byte 17 */
} BestOfferMessage;

/* any Best Offer Message at all: every byte one the checker chooses */
static void any_best_offer_message(BestOfferMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->instrument_number[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->volume_int_324[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->price_rate[i] = arbitrary(); }
  record->offer_direction = arbitrary();
  record->operation_type = arbitrary();
}

/* Best Offer Message to the wire: 18 bytes from at, returning where the next byte goes */
static size_t encode_best_offer_message(const BestOfferMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument_number[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->volume_int_324[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price_rate[i]; }
  wire[at++] = record->offer_direction;
  wire[at++] = record->operation_type;

  return at;
}

/* Best Offer Message off the wire: 18 bytes from at, returning where the next byte lies */
static size_t decode_best_offer_message(BestOfferMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->instrument_number[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->volume_int_324[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->price_rate[i] = wire[at++]; }
  record->offer_direction = wire[at++];
  record->operation_type = wire[at++];

  return at;
}

/* what was read of Best Offer Message is what was written, byte for byte */
static void equal_best_offer_message(const BestOfferMessage *read, const BestOfferMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->instrument_number[i] == written->instrument_number[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->volume_int_324[i] == written->volume_int_324[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->price_rate[i] == written->price_rate[i]); }
  assert(read->offer_direction == written->offer_direction);
  assert(read->operation_type == written->operation_type);
}

/* Best Offer Message: written and read back, then read and written back */
static void check_best_offer_message(void) {
  BestOfferMessage sent;
  BestOfferMessage got;
  uint8_t wire[18];
  uint8_t again[18];

  any_best_offer_message(&sent);
  assert(encode_best_offer_message(&sent, wire, 0) == 18);
  assert(decode_best_offer_message(&got, wire, 0) == 18);
  equal_best_offer_message(&got, &sent);

  for (size_t i = 0; i < 18; i++) { wire[i] = arbitrary(); }
  assert(decode_best_offer_message(&got, wire, 0) == 18);
  assert(encode_best_offer_message(&got, again, 0) == 18);
  for (size_t i = 0; i < 18; i++) { assert(again[i] == wire[i]); }
}

/* ---- Public Offerings Message: 66 bytes -------------------------------------- */

/* Trade from a Public offering. */
typedef struct {
  uint8_t instrument_number[4];       /* bytes 0 to 3 */
  uint8_t number[4];                  /* bytes 4 to 7 */
  uint8_t volume_int_648[8];          /* bytes 8 to 15 */
  uint8_t discount_rate_or_price[8];  /* bytes 16 to 23 */
  uint8_t rate_of_return[4];          /* bytes 24 to 27 */
  uint8_t term_days[2];               /* bytes 28 to 29 */
  uint8_t currency_type;              /* byte 30 */
  uint8_t settlement;                 /* byte 31 */
  uint8_t buy_alpha_5[5];             /* bytes 32 to 36 */
  uint8_t sell_alpha_5[5];            /* bytes 37 to 41 */
  uint8_t placement_date[8];          /* bytes 42 to 49 */
  uint8_t issue_date[8];              /* bytes 50 to 57 */
  uint8_t maturity_date[8];           /* bytes 58 to 65 */
} PublicOfferingsMessage;

/* any Public Offerings Message at all: every byte one the checker chooses */
static void any_public_offerings_message(PublicOfferingsMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->instrument_number[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->number[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->volume_int_648[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->discount_rate_or_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->rate_of_return[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->term_days[i] = arbitrary(); }
  record->currency_type = arbitrary();
  record->settlement = arbitrary();
  for (size_t i = 0; i < 5; i++) { record->buy_alpha_5[i] = arbitrary(); }
  for (size_t i = 0; i < 5; i++) { record->sell_alpha_5[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->placement_date[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->issue_date[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->maturity_date[i] = arbitrary(); }
}

/* Public Offerings Message to the wire: 66 bytes from at, returning where the next byte goes */
static size_t encode_public_offerings_message(const PublicOfferingsMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument_number[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->number[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->volume_int_648[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->discount_rate_or_price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->rate_of_return[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->term_days[i]; }
  wire[at++] = record->currency_type;
  wire[at++] = record->settlement;
  for (size_t i = 0; i < 5; i++) { wire[at++] = record->buy_alpha_5[i]; }
  for (size_t i = 0; i < 5; i++) { wire[at++] = record->sell_alpha_5[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->placement_date[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->issue_date[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->maturity_date[i]; }

  return at;
}

/* Public Offerings Message off the wire: 66 bytes from at, returning where the next byte lies */
static size_t decode_public_offerings_message(PublicOfferingsMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->instrument_number[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->number[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->volume_int_648[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->discount_rate_or_price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->rate_of_return[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->term_days[i] = wire[at++]; }
  record->currency_type = wire[at++];
  record->settlement = wire[at++];
  for (size_t i = 0; i < 5; i++) { record->buy_alpha_5[i] = wire[at++]; }
  for (size_t i = 0; i < 5; i++) { record->sell_alpha_5[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->placement_date[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->issue_date[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->maturity_date[i] = wire[at++]; }

  return at;
}

/* what was read of Public Offerings Message is what was written, byte for byte */
static void equal_public_offerings_message(const PublicOfferingsMessage *read, const PublicOfferingsMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->instrument_number[i] == written->instrument_number[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->number[i] == written->number[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->volume_int_648[i] == written->volume_int_648[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->discount_rate_or_price[i] == written->discount_rate_or_price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->rate_of_return[i] == written->rate_of_return[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->term_days[i] == written->term_days[i]); }
  assert(read->currency_type == written->currency_type);
  assert(read->settlement == written->settlement);
  for (size_t i = 0; i < 5; i++) { assert(read->buy_alpha_5[i] == written->buy_alpha_5[i]); }
  for (size_t i = 0; i < 5; i++) { assert(read->sell_alpha_5[i] == written->sell_alpha_5[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->placement_date[i] == written->placement_date[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->issue_date[i] == written->issue_date[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->maturity_date[i] == written->maturity_date[i]); }
}

/* Public Offerings Message: written and read back, then read and written back */
static void check_public_offerings_message(void) {
  PublicOfferingsMessage sent;
  PublicOfferingsMessage got;
  uint8_t wire[66];
  uint8_t again[66];

  any_public_offerings_message(&sent);
  assert(encode_public_offerings_message(&sent, wire, 0) == 66);
  assert(decode_public_offerings_message(&got, wire, 0) == 66);
  equal_public_offerings_message(&got, &sent);

  for (size_t i = 0; i < 66; i++) { wire[i] = arbitrary(); }
  assert(decode_public_offerings_message(&got, wire, 0) == 66);
  assert(encode_public_offerings_message(&got, again, 0) == 66);
  for (size_t i = 0; i < 66; i++) { assert(again[i] == wire[i]); }
}

/* ---- Open Interest Message: 8 bytes ------------------------------------------ */

/* Open Interest */
typedef struct {
  uint8_t instrument_number[4];  /* bytes 0 to 3 */
  uint8_t open_interest[4];      /* bytes 4 to 7 */
} OpenInterestMessage;

/* any Open Interest Message at all: every byte one the checker chooses */
static void any_open_interest_message(OpenInterestMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->instrument_number[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->open_interest[i] = arbitrary(); }
}

/* Open Interest Message to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_open_interest_message(const OpenInterestMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument_number[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->open_interest[i]; }

  return at;
}

/* Open Interest Message off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_open_interest_message(OpenInterestMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->instrument_number[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->open_interest[i] = wire[at++]; }

  return at;
}

/* what was read of Open Interest Message is what was written, byte for byte */
static void equal_open_interest_message(const OpenInterestMessage *read, const OpenInterestMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->instrument_number[i] == written->instrument_number[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->open_interest[i] == written->open_interest[i]); }
}

/* Open Interest Message: written and read back, then read and written back */
static void check_open_interest_message(void) {
  OpenInterestMessage sent;
  OpenInterestMessage got;
  uint8_t wire[8];
  uint8_t again[8];

  any_open_interest_message(&sent);
  assert(encode_open_interest_message(&sent, wire, 0) == 8);
  assert(decode_open_interest_message(&got, wire, 0) == 8);
  equal_open_interest_message(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_open_interest_message(&got, wire, 0) == 8);
  assert(encode_open_interest_message(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Derivatives Market Trades Message: 43 bytes ----------------------------- */

/* Contains information on any MexDer accepted transaction. */
typedef struct {
  uint8_t instrument_number[4];    /* bytes 0 to 3 */
  uint8_t trade_time[8];           /* bytes 4 to 11 */
  uint8_t volume_int_324[4];       /* bytes 12 to 15 */
  uint8_t price_rate[8];           /* bytes 16 to 23 */
  uint8_t concertation_type;       /* byte 24 */
  uint8_t trade_number[4];         /* bytes 25 to 28 */
  uint8_t operation_type;          /* byte 29 */
  uint8_t amount[8];               /* bytes 30 to 37 */
  uint8_t parent_trade_number[4];  /* bytes 38 to 41 */
  uint8_t leg_type;                /* byte 42 */
} DerivativesMarketTradesMessage;

/* any Derivatives Market Trades Message at all: every byte one the checker chooses */
static void any_derivatives_market_trades_message(DerivativesMarketTradesMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->instrument_number[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->trade_time[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->volume_int_324[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->price_rate[i] = arbitrary(); }
  record->concertation_type = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->trade_number[i] = arbitrary(); }
  record->operation_type = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->amount[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->parent_trade_number[i] = arbitrary(); }
  record->leg_type = arbitrary();
}

/* Derivatives Market Trades Message to the wire: 43 bytes from at, returning where the next byte goes */
static size_t encode_derivatives_market_trades_message(const DerivativesMarketTradesMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument_number[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->trade_time[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->volume_int_324[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price_rate[i]; }
  wire[at++] = record->concertation_type;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->trade_number[i]; }
  wire[at++] = record->operation_type;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->amount[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->parent_trade_number[i]; }
  wire[at++] = record->leg_type;

  return at;
}

/* Derivatives Market Trades Message off the wire: 43 bytes from at, returning where the next byte lies */
static size_t decode_derivatives_market_trades_message(DerivativesMarketTradesMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->instrument_number[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->trade_time[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->volume_int_324[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->price_rate[i] = wire[at++]; }
  record->concertation_type = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->trade_number[i] = wire[at++]; }
  record->operation_type = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->amount[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->parent_trade_number[i] = wire[at++]; }
  record->leg_type = wire[at++];

  return at;
}

/* what was read of Derivatives Market Trades Message is what was written, byte for byte */
static void equal_derivatives_market_trades_message(const DerivativesMarketTradesMessage *read, const DerivativesMarketTradesMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->instrument_number[i] == written->instrument_number[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->trade_time[i] == written->trade_time[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->volume_int_324[i] == written->volume_int_324[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->price_rate[i] == written->price_rate[i]); }
  assert(read->concertation_type == written->concertation_type);
  for (size_t i = 0; i < 4; i++) { assert(read->trade_number[i] == written->trade_number[i]); }
  assert(read->operation_type == written->operation_type);
  for (size_t i = 0; i < 8; i++) { assert(read->amount[i] == written->amount[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->parent_trade_number[i] == written->parent_trade_number[i]); }
  assert(read->leg_type == written->leg_type);
}

/* Derivatives Market Trades Message: written and read back, then read and written back */
static void check_derivatives_market_trades_message(void) {
  DerivativesMarketTradesMessage sent;
  DerivativesMarketTradesMessage got;
  uint8_t wire[43];
  uint8_t again[43];

  any_derivatives_market_trades_message(&sent);
  assert(encode_derivatives_market_trades_message(&sent, wire, 0) == 43);
  assert(decode_derivatives_market_trades_message(&got, wire, 0) == 43);
  equal_derivatives_market_trades_message(&got, &sent);

  for (size_t i = 0; i < 43; i++) { wire[i] = arbitrary(); }
  assert(decode_derivatives_market_trades_message(&got, wire, 0) == 43);
  assert(encode_derivatives_market_trades_message(&got, again, 0) == 43);
  for (size_t i = 0; i < 43; i++) { assert(again[i] == wire[i]); }
}

/* ---- Statistics Of Instruments Message: 44 bytes ----------------------------- */

/* Update message from derivatives statistics sent each time there is an update on the trading floor at any level price. */
typedef struct {
  uint8_t instrument_number[4];          /* bytes 0 to 3 */
  uint8_t previous_settlement_price[8];  /* bytes 4 to 11 */
  uint8_t opening_price[8];              /* bytes 12 to 19 */
  uint8_t max_price_of_the_day[8];       /* bytes 20 to 27 */
  uint8_t lower_price_of_the_day[8];     /* bytes 28 to 35 */
  uint8_t last_price_of_the_day[8];      /* bytes 36 to 43 */
} StatisticsOfInstrumentsMessage;

/* any Statistics Of Instruments Message at all: every byte one the checker chooses */
static void any_statistics_of_instruments_message(StatisticsOfInstrumentsMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->instrument_number[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->previous_settlement_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->opening_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->max_price_of_the_day[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->lower_price_of_the_day[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->last_price_of_the_day[i] = arbitrary(); }
}

/* Statistics Of Instruments Message to the wire: 44 bytes from at, returning where the next byte goes */
static size_t encode_statistics_of_instruments_message(const StatisticsOfInstrumentsMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument_number[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->previous_settlement_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->opening_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->max_price_of_the_day[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->lower_price_of_the_day[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->last_price_of_the_day[i]; }

  return at;
}

/* Statistics Of Instruments Message off the wire: 44 bytes from at, returning where the next byte lies */
static size_t decode_statistics_of_instruments_message(StatisticsOfInstrumentsMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->instrument_number[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->previous_settlement_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->opening_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->max_price_of_the_day[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->lower_price_of_the_day[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->last_price_of_the_day[i] = wire[at++]; }

  return at;
}

/* what was read of Statistics Of Instruments Message is what was written, byte for byte */
static void equal_statistics_of_instruments_message(const StatisticsOfInstrumentsMessage *read, const StatisticsOfInstrumentsMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->instrument_number[i] == written->instrument_number[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->previous_settlement_price[i] == written->previous_settlement_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->opening_price[i] == written->opening_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->max_price_of_the_day[i] == written->max_price_of_the_day[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->lower_price_of_the_day[i] == written->lower_price_of_the_day[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->last_price_of_the_day[i] == written->last_price_of_the_day[i]); }
}

/* Statistics Of Instruments Message: written and read back, then read and written back */
static void check_statistics_of_instruments_message(void) {
  StatisticsOfInstrumentsMessage sent;
  StatisticsOfInstrumentsMessage got;
  uint8_t wire[44];
  uint8_t again[44];

  any_statistics_of_instruments_message(&sent);
  assert(encode_statistics_of_instruments_message(&sent, wire, 0) == 44);
  assert(decode_statistics_of_instruments_message(&got, wire, 0) == 44);
  equal_statistics_of_instruments_message(&got, &sent);

  for (size_t i = 0; i < 44; i++) { wire[i] = arbitrary(); }
  assert(decode_statistics_of_instruments_message(&got, wire, 0) == 44);
  assert(encode_statistics_of_instruments_message(&got, again, 0) == 44);
  for (size_t i = 0; i < 44; i++) { assert(again[i] == wire[i]); }
}

/* ---- General Indices Message: 33 bytes --------------------------------------- */

/* Information about the MSE Indices. */
typedef struct {
  uint8_t component[2];         /* bytes 0 to 1 */
  uint8_t sector;               /* byte 2 */
  uint8_t indices_hour[8];      /* bytes 3 to 10 */
  uint8_t volume_int_648[8];    /* bytes 11 to 18 */
  uint8_t indices_price_44[4];  /* bytes 19 to 22 */
  uint8_t variation[4];         /* bytes 23 to 26 */
  uint8_t percentage[4];        /* bytes 27 to 30 */
  uint8_t trend;                /* byte 31 */
  uint8_t indices_status;       /* byte 32 */
} GeneralIndicesMessage;

/* any General Indices Message at all: every byte one the checker chooses */
static void any_general_indices_message(GeneralIndicesMessage *record) {
  for (size_t i = 0; i < 2; i++) { record->component[i] = arbitrary(); }
  record->sector = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->indices_hour[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->volume_int_648[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->indices_price_44[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->variation[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->percentage[i] = arbitrary(); }
  record->trend = arbitrary();
  record->indices_status = arbitrary();
}

/* General Indices Message to the wire: 33 bytes from at, returning where the next byte goes */
static size_t encode_general_indices_message(const GeneralIndicesMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->component[i]; }
  wire[at++] = record->sector;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->indices_hour[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->volume_int_648[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->indices_price_44[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->variation[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->percentage[i]; }
  wire[at++] = record->trend;
  wire[at++] = record->indices_status;

  return at;
}

/* General Indices Message off the wire: 33 bytes from at, returning where the next byte lies */
static size_t decode_general_indices_message(GeneralIndicesMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->component[i] = wire[at++]; }
  record->sector = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->indices_hour[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->volume_int_648[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->indices_price_44[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->variation[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->percentage[i] = wire[at++]; }
  record->trend = wire[at++];
  record->indices_status = wire[at++];

  return at;
}

/* what was read of General Indices Message is what was written, byte for byte */
static void equal_general_indices_message(const GeneralIndicesMessage *read, const GeneralIndicesMessage *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->component[i] == written->component[i]); }
  assert(read->sector == written->sector);
  for (size_t i = 0; i < 8; i++) { assert(read->indices_hour[i] == written->indices_hour[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->volume_int_648[i] == written->volume_int_648[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->indices_price_44[i] == written->indices_price_44[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->variation[i] == written->variation[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->percentage[i] == written->percentage[i]); }
  assert(read->trend == written->trend);
  assert(read->indices_status == written->indices_status);
}

/* General Indices Message: written and read back, then read and written back */
static void check_general_indices_message(void) {
  GeneralIndicesMessage sent;
  GeneralIndicesMessage got;
  uint8_t wire[33];
  uint8_t again[33];

  any_general_indices_message(&sent);
  assert(encode_general_indices_message(&sent, wire, 0) == 33);
  assert(decode_general_indices_message(&got, wire, 0) == 33);
  equal_general_indices_message(&got, &sent);

  for (size_t i = 0; i < 33; i++) { wire[i] = arbitrary(); }
  assert(decode_general_indices_message(&got, wire, 0) == 33);
  assert(encode_general_indices_message(&got, again, 0) == 33);
  for (size_t i = 0; i < 33; i++) { assert(again[i] == wire[i]); }
}

/* ---- Indices Components Message: 57 bytes ------------------------------------ */

/* Indices components obtained during the day. */
typedef struct {
  uint8_t date[8];            /* bytes 0 to 7 */
  uint8_t component[2];       /* bytes 8 to 9 */
  uint8_t sector;             /* byte 10 */
  uint8_t type;               /* byte 11 */
  uint8_t issuer[7];          /* bytes 12 to 18 */
  uint8_t series[6];          /* bytes 19 to 24 */
  uint8_t indices_stocks[8];  /* bytes 25 to 32 */
  uint8_t last_price[8];      /* bytes 33 to 40 */
  uint8_t closing_price[8];   /* bytes 41 to 48 */
  uint8_t influence[8];       /* bytes 49 to 56 */
} IndicesComponentsMessage;

/* any Indices Components Message at all: every byte one the checker chooses */
static void any_indices_components_message(IndicesComponentsMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->date[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->component[i] = arbitrary(); }
  record->sector = arbitrary();
  record->type = arbitrary();
  for (size_t i = 0; i < 7; i++) { record->issuer[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->series[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->indices_stocks[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->last_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->closing_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->influence[i] = arbitrary(); }
}

/* Indices Components Message to the wire: 57 bytes from at, returning where the next byte goes */
static size_t encode_indices_components_message(const IndicesComponentsMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->date[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->component[i]; }
  wire[at++] = record->sector;
  wire[at++] = record->type;
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->issuer[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->series[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->indices_stocks[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->last_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->closing_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->influence[i]; }

  return at;
}

/* Indices Components Message off the wire: 57 bytes from at, returning where the next byte lies */
static size_t decode_indices_components_message(IndicesComponentsMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->date[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->component[i] = wire[at++]; }
  record->sector = wire[at++];
  record->type = wire[at++];
  for (size_t i = 0; i < 7; i++) { record->issuer[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->series[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->indices_stocks[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->last_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->closing_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->influence[i] = wire[at++]; }

  return at;
}

/* what was read of Indices Components Message is what was written, byte for byte */
static void equal_indices_components_message(const IndicesComponentsMessage *read, const IndicesComponentsMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->date[i] == written->date[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->component[i] == written->component[i]); }
  assert(read->sector == written->sector);
  assert(read->type == written->type);
  for (size_t i = 0; i < 7; i++) { assert(read->issuer[i] == written->issuer[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->series[i] == written->series[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->indices_stocks[i] == written->indices_stocks[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->last_price[i] == written->last_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->closing_price[i] == written->closing_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->influence[i] == written->influence[i]); }
}

/* Indices Components Message: written and read back, then read and written back */
static void check_indices_components_message(void) {
  IndicesComponentsMessage sent;
  IndicesComponentsMessage got;
  uint8_t wire[57];
  uint8_t again[57];

  any_indices_components_message(&sent);
  assert(encode_indices_components_message(&sent, wire, 0) == 57);
  assert(decode_indices_components_message(&got, wire, 0) == 57);
  equal_indices_components_message(&got, &sent);

  for (size_t i = 0; i < 57; i++) { wire[i] = arbitrary(); }
  assert(decode_indices_components_message(&got, wire, 0) == 57);
  assert(encode_indices_components_message(&got, again, 0) == 57);
  for (size_t i = 0; i < 57; i++) { assert(again[i] == wire[i]); }
}

/* ---- Inav Message: 12 bytes -------------------------------------------------- */

/* TRACS dissemination during continuous market trading hours. */
typedef struct {
  uint8_t trac_number[4];                /* bytes 0 to 3 */
  uint8_t theoretical_current_price[8];  /* bytes 4 to 11 */
} InavMessage;

/* any Inav Message at all: every byte one the checker chooses */
static void any_inav_message(InavMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->trac_number[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->theoretical_current_price[i] = arbitrary(); }
}

/* Inav Message to the wire: 12 bytes from at, returning where the next byte goes */
static size_t encode_inav_message(const InavMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->trac_number[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->theoretical_current_price[i]; }

  return at;
}

/* Inav Message off the wire: 12 bytes from at, returning where the next byte lies */
static size_t decode_inav_message(InavMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->trac_number[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->theoretical_current_price[i] = wire[at++]; }

  return at;
}

/* what was read of Inav Message is what was written, byte for byte */
static void equal_inav_message(const InavMessage *read, const InavMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->trac_number[i] == written->trac_number[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->theoretical_current_price[i] == written->theoretical_current_price[i]); }
}

/* Inav Message: written and read back, then read and written back */
static void check_inav_message(void) {
  InavMessage sent;
  InavMessage got;
  uint8_t wire[12];
  uint8_t again[12];

  any_inav_message(&sent);
  assert(encode_inav_message(&sent, wire, 0) == 12);
  assert(decode_inav_message(&got, wire, 0) == 12);
  equal_inav_message(&got, &sent);

  for (size_t i = 0; i < 12; i++) { wire[i] = arbitrary(); }
  assert(decode_inav_message(&got, wire, 0) == 12);
  assert(encode_inav_message(&got, again, 0) == 12);
  for (size_t i = 0; i < 12; i++) { assert(again[i] == wire[i]); }
}

/* ---- Dollar Buy Sell Message: 38 bytes --------------------------------------- */

/* Dollar Buy/Sell */
typedef struct {
  uint8_t posture_date[8];    /* bytes 0 to 7 */
  uint8_t currency[5];        /* bytes 8 to 12 */
  uint8_t dollar_side;        /* byte 13 */
  uint8_t buy_precio_88[8];   /* bytes 14 to 21 */
  uint8_t sell_precio_88[8];  /* bytes 22 to 29 */
  uint8_t last_deal[8];       /* bytes 30 to 37 */
} DollarBuySellMessage;

/* any Dollar Buy Sell Message at all: every byte one the checker chooses */
static void any_dollar_buy_sell_message(DollarBuySellMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->posture_date[i] = arbitrary(); }
  for (size_t i = 0; i < 5; i++) { record->currency[i] = arbitrary(); }
  record->dollar_side = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->buy_precio_88[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->sell_precio_88[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->last_deal[i] = arbitrary(); }
}

/* Dollar Buy Sell Message to the wire: 38 bytes from at, returning where the next byte goes */
static size_t encode_dollar_buy_sell_message(const DollarBuySellMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->posture_date[i]; }
  for (size_t i = 0; i < 5; i++) { wire[at++] = record->currency[i]; }
  wire[at++] = record->dollar_side;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->buy_precio_88[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->sell_precio_88[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->last_deal[i]; }

  return at;
}

/* Dollar Buy Sell Message off the wire: 38 bytes from at, returning where the next byte lies */
static size_t decode_dollar_buy_sell_message(DollarBuySellMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->posture_date[i] = wire[at++]; }
  for (size_t i = 0; i < 5; i++) { record->currency[i] = wire[at++]; }
  record->dollar_side = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->buy_precio_88[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->sell_precio_88[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->last_deal[i] = wire[at++]; }

  return at;
}

/* what was read of Dollar Buy Sell Message is what was written, byte for byte */
static void equal_dollar_buy_sell_message(const DollarBuySellMessage *read, const DollarBuySellMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->posture_date[i] == written->posture_date[i]); }
  for (size_t i = 0; i < 5; i++) { assert(read->currency[i] == written->currency[i]); }
  assert(read->dollar_side == written->dollar_side);
  for (size_t i = 0; i < 8; i++) { assert(read->buy_precio_88[i] == written->buy_precio_88[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->sell_precio_88[i] == written->sell_precio_88[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->last_deal[i] == written->last_deal[i]); }
}

/* Dollar Buy Sell Message: written and read back, then read and written back */
static void check_dollar_buy_sell_message(void) {
  DollarBuySellMessage sent;
  DollarBuySellMessage got;
  uint8_t wire[38];
  uint8_t again[38];

  any_dollar_buy_sell_message(&sent);
  assert(encode_dollar_buy_sell_message(&sent, wire, 0) == 38);
  assert(decode_dollar_buy_sell_message(&got, wire, 0) == 38);
  equal_dollar_buy_sell_message(&got, &sent);

  for (size_t i = 0; i < 38; i++) { wire[i] = arbitrary(); }
  assert(decode_dollar_buy_sell_message(&got, wire, 0) == 38);
  assert(encode_dollar_buy_sell_message(&got, again, 0) == 38);
  for (size_t i = 0; i < 38; i++) { assert(again[i] == wire[i]); }
}

/* ---- Short Sales Balances Per Instrument Message: 44 bytes ------------------- */

/* Short sales balances per instrument */
typedef struct {
  uint8_t instrument_number[4];  /* bytes 0 to 3 */
  uint8_t date[8];               /* bytes 4 to 11 */
  uint8_t previous_balance[8];   /* bytes 12 to 19 */
  uint8_t amount_traded[8];      /* bytes 20 to 27 */
  uint8_t buybacks[8];           /* bytes 28 to 35 */
  uint8_t current_balance[8];    /* bytes 36 to 43 */
} ShortSalesBalancesPerInstrumentMessage;

/* any Short Sales Balances Per Instrument Message at all: every byte one the checker chooses */
static void any_short_sales_balances_per_instrument_message(ShortSalesBalancesPerInstrumentMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->instrument_number[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->date[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->previous_balance[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->amount_traded[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->buybacks[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->current_balance[i] = arbitrary(); }
}

/* Short Sales Balances Per Instrument Message to the wire: 44 bytes from at, returning where the next byte goes */
static size_t encode_short_sales_balances_per_instrument_message(const ShortSalesBalancesPerInstrumentMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument_number[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->date[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->previous_balance[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->amount_traded[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->buybacks[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->current_balance[i]; }

  return at;
}

/* Short Sales Balances Per Instrument Message off the wire: 44 bytes from at, returning where the next byte lies */
static size_t decode_short_sales_balances_per_instrument_message(ShortSalesBalancesPerInstrumentMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->instrument_number[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->date[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->previous_balance[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->amount_traded[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->buybacks[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->current_balance[i] = wire[at++]; }

  return at;
}

/* what was read of Short Sales Balances Per Instrument Message is what was written, byte for byte */
static void equal_short_sales_balances_per_instrument_message(const ShortSalesBalancesPerInstrumentMessage *read, const ShortSalesBalancesPerInstrumentMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->instrument_number[i] == written->instrument_number[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->date[i] == written->date[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->previous_balance[i] == written->previous_balance[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->amount_traded[i] == written->amount_traded[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->buybacks[i] == written->buybacks[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->current_balance[i] == written->current_balance[i]); }
}

/* Short Sales Balances Per Instrument Message: written and read back, then read and written back */
static void check_short_sales_balances_per_instrument_message(void) {
  ShortSalesBalancesPerInstrumentMessage sent;
  ShortSalesBalancesPerInstrumentMessage got;
  uint8_t wire[44];
  uint8_t again[44];

  any_short_sales_balances_per_instrument_message(&sent);
  assert(encode_short_sales_balances_per_instrument_message(&sent, wire, 0) == 44);
  assert(decode_short_sales_balances_per_instrument_message(&got, wire, 0) == 44);
  equal_short_sales_balances_per_instrument_message(&got, &sent);

  for (size_t i = 0; i < 44; i++) { wire[i] = arbitrary(); }
  assert(decode_short_sales_balances_per_instrument_message(&got, wire, 0) == 44);
  assert(encode_short_sales_balances_per_instrument_message(&got, again, 0) == 44);
  for (size_t i = 0; i < 44; i++) { assert(again[i] == wire[i]); }
}

/* ---- Capital Market Multiples Message: 130 bytes ----------------------------- */

/* Capital Market Multiples */
typedef struct {
  uint8_t instrument_id[4];       /* bytes 0 to 3 */
  uint8_t multiple_type;          /* byte 4 */
  uint8_t registry_number;        /* byte 5 */
  uint8_t sector;                 /* byte 6 */
  uint8_t subsector;              /* byte 7 */
  uint8_t business_line;          /* byte 8 */
  uint8_t sub_line;               /* byte 9 */
  uint8_t pflepa_multiple[8];     /* bytes 10 to 17 */
  uint8_t pfepa_multiple[8];      /* bytes 18 to 25 */
  uint8_t ve_uaiida_multiple[8];  /* bytes 26 to 33 */
  uint8_t p_u[8];                 /* bytes 34 to 41 */
  uint8_t p_vl[8];                /* bytes 42 to 49 */
  uint8_t f_1_p_unoc[8];          /* bytes 50 to 57 */
  uint8_t f_2_p_unoc[8];          /* bytes 58 to 65 */
  uint8_t f_1_p_ue[8];            /* bytes 66 to 73 */
  uint8_t f_2_p_ue[8];            /* bytes 74 to 81 */
  uint8_t f_1_ve_uaiida[8];       /* bytes 82 to 89 */
  uint8_t f_2_ve_uaiida[8];       /* bytes 90 to 97 */
  uint8_t f_1_p_u[8];             /* bytes 98 to 105 */
  uint8_t f_2_p_u[8];             /* bytes 106 to 113 */
  uint8_t f_1_p_vl[8];            /* bytes 114 to 121 */
  uint8_t f_2_p_vl[8];            /* bytes 122 to 129 */
} CapitalMarketMultiplesMessage;

/* any Capital Market Multiples Message at all: every byte one the checker chooses */
static void any_capital_market_multiples_message(CapitalMarketMultiplesMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->instrument_id[i] = arbitrary(); }
  record->multiple_type = arbitrary();
  record->registry_number = arbitrary();
  record->sector = arbitrary();
  record->subsector = arbitrary();
  record->business_line = arbitrary();
  record->sub_line = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->pflepa_multiple[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->pfepa_multiple[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->ve_uaiida_multiple[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->p_u[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->p_vl[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->f_1_p_unoc[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->f_2_p_unoc[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->f_1_p_ue[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->f_2_p_ue[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->f_1_ve_uaiida[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->f_2_ve_uaiida[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->f_1_p_u[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->f_2_p_u[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->f_1_p_vl[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->f_2_p_vl[i] = arbitrary(); }
}

/* Capital Market Multiples Message to the wire: 130 bytes from at, returning where the next byte goes */
static size_t encode_capital_market_multiples_message(const CapitalMarketMultiplesMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument_id[i]; }
  wire[at++] = record->multiple_type;
  wire[at++] = record->registry_number;
  wire[at++] = record->sector;
  wire[at++] = record->subsector;
  wire[at++] = record->business_line;
  wire[at++] = record->sub_line;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->pflepa_multiple[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->pfepa_multiple[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->ve_uaiida_multiple[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->p_u[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->p_vl[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->f_1_p_unoc[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->f_2_p_unoc[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->f_1_p_ue[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->f_2_p_ue[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->f_1_ve_uaiida[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->f_2_ve_uaiida[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->f_1_p_u[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->f_2_p_u[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->f_1_p_vl[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->f_2_p_vl[i]; }

  return at;
}

/* Capital Market Multiples Message off the wire: 130 bytes from at, returning where the next byte lies */
static size_t decode_capital_market_multiples_message(CapitalMarketMultiplesMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->instrument_id[i] = wire[at++]; }
  record->multiple_type = wire[at++];
  record->registry_number = wire[at++];
  record->sector = wire[at++];
  record->subsector = wire[at++];
  record->business_line = wire[at++];
  record->sub_line = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->pflepa_multiple[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->pfepa_multiple[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->ve_uaiida_multiple[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->p_u[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->p_vl[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->f_1_p_unoc[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->f_2_p_unoc[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->f_1_p_ue[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->f_2_p_ue[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->f_1_ve_uaiida[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->f_2_ve_uaiida[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->f_1_p_u[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->f_2_p_u[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->f_1_p_vl[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->f_2_p_vl[i] = wire[at++]; }

  return at;
}

/* what was read of Capital Market Multiples Message is what was written, byte for byte */
static void equal_capital_market_multiples_message(const CapitalMarketMultiplesMessage *read, const CapitalMarketMultiplesMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->instrument_id[i] == written->instrument_id[i]); }
  assert(read->multiple_type == written->multiple_type);
  assert(read->registry_number == written->registry_number);
  assert(read->sector == written->sector);
  assert(read->subsector == written->subsector);
  assert(read->business_line == written->business_line);
  assert(read->sub_line == written->sub_line);
  for (size_t i = 0; i < 8; i++) { assert(read->pflepa_multiple[i] == written->pflepa_multiple[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->pfepa_multiple[i] == written->pfepa_multiple[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->ve_uaiida_multiple[i] == written->ve_uaiida_multiple[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->p_u[i] == written->p_u[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->p_vl[i] == written->p_vl[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->f_1_p_unoc[i] == written->f_1_p_unoc[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->f_2_p_unoc[i] == written->f_2_p_unoc[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->f_1_p_ue[i] == written->f_1_p_ue[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->f_2_p_ue[i] == written->f_2_p_ue[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->f_1_ve_uaiida[i] == written->f_1_ve_uaiida[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->f_2_ve_uaiida[i] == written->f_2_ve_uaiida[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->f_1_p_u[i] == written->f_1_p_u[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->f_2_p_u[i] == written->f_2_p_u[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->f_1_p_vl[i] == written->f_1_p_vl[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->f_2_p_vl[i] == written->f_2_p_vl[i]); }
}

/* Capital Market Multiples Message: written and read back, then read and written back */
static void check_capital_market_multiples_message(void) {
  CapitalMarketMultiplesMessage sent;
  CapitalMarketMultiplesMessage got;
  uint8_t wire[130];
  uint8_t again[130];

  any_capital_market_multiples_message(&sent);
  assert(encode_capital_market_multiples_message(&sent, wire, 0) == 130);
  assert(decode_capital_market_multiples_message(&got, wire, 0) == 130);
  equal_capital_market_multiples_message(&got, &sent);

  for (size_t i = 0; i < 130; i++) { wire[i] = arbitrary(); }
  assert(decode_capital_market_multiples_message(&got, wire, 0) == 130);
  assert(encode_capital_market_multiples_message(&got, again, 0) == 130);
  for (size_t i = 0; i < 130; i++) { assert(again[i] == wire[i]); }
}

/* ---- Benchmark Message: 149 bytes -------------------------------------------- */

/* Benchmark */
typedef struct {
  uint8_t benchmark_name[40];                      /* bytes 0 to 39 */
  uint8_t benchmark_date[8];                       /* bytes 40 to 47 */
  uint8_t outstanding[8];                          /* bytes 48 to 55 */
  uint8_t integer_amount[8];                       /* bytes 56 to 63 */
  uint8_t decimal_amount[4];                       /* bytes 64 to 67 */
  uint8_t indices_precio_88[8];                    /* bytes 68 to 75 */
  uint8_t indices_24[8];                           /* bytes 76 to 83 */
  uint8_t rebalance;                               /* byte 84 */
  uint8_t daily_performance[8];                    /* bytes 85 to 92 */
  uint8_t annual_performance[8];                   /* bytes 93 to 100 */
  uint8_t monthly_performance[8];                  /* bytes 101 to 108 */
  uint8_t last_12_months_performance[8];           /* bytes 109 to 116 */
  uint8_t v24_hours_daily_performance[8];          /* bytes 117 to 124 */
  uint8_t v24_hours_annual_performance[8];         /* bytes 125 to 132 */
  uint8_t v24_hours_monthly_performance[8];        /* bytes 133 to 140 */
  uint8_t last_12_months_24_hours_performance[8];  /* bytes 141 to 148 */
} BenchmarkMessage;

/* any Benchmark Message at all: every byte one the checker chooses */
static void any_benchmark_message(BenchmarkMessage *record) {
  for (size_t i = 0; i < 40; i++) { record->benchmark_name[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->benchmark_date[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->outstanding[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->integer_amount[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->decimal_amount[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->indices_precio_88[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->indices_24[i] = arbitrary(); }
  record->rebalance = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->daily_performance[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->annual_performance[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->monthly_performance[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->last_12_months_performance[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->v24_hours_daily_performance[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->v24_hours_annual_performance[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->v24_hours_monthly_performance[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->last_12_months_24_hours_performance[i] = arbitrary(); }
}

/* Benchmark Message to the wire: 149 bytes from at, returning where the next byte goes */
static size_t encode_benchmark_message(const BenchmarkMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 40; i++) { wire[at++] = record->benchmark_name[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->benchmark_date[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->outstanding[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->integer_amount[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->decimal_amount[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->indices_precio_88[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->indices_24[i]; }
  wire[at++] = record->rebalance;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->daily_performance[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->annual_performance[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->monthly_performance[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->last_12_months_performance[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->v24_hours_daily_performance[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->v24_hours_annual_performance[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->v24_hours_monthly_performance[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->last_12_months_24_hours_performance[i]; }

  return at;
}

/* Benchmark Message off the wire: 149 bytes from at, returning where the next byte lies */
static size_t decode_benchmark_message(BenchmarkMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 40; i++) { record->benchmark_name[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->benchmark_date[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->outstanding[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->integer_amount[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->decimal_amount[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->indices_precio_88[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->indices_24[i] = wire[at++]; }
  record->rebalance = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->daily_performance[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->annual_performance[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->monthly_performance[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->last_12_months_performance[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->v24_hours_daily_performance[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->v24_hours_annual_performance[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->v24_hours_monthly_performance[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->last_12_months_24_hours_performance[i] = wire[at++]; }

  return at;
}

/* what was read of Benchmark Message is what was written, byte for byte */
static void equal_benchmark_message(const BenchmarkMessage *read, const BenchmarkMessage *written) {
  for (size_t i = 0; i < 40; i++) { assert(read->benchmark_name[i] == written->benchmark_name[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->benchmark_date[i] == written->benchmark_date[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->outstanding[i] == written->outstanding[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->integer_amount[i] == written->integer_amount[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->decimal_amount[i] == written->decimal_amount[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->indices_precio_88[i] == written->indices_precio_88[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->indices_24[i] == written->indices_24[i]); }
  assert(read->rebalance == written->rebalance);
  for (size_t i = 0; i < 8; i++) { assert(read->daily_performance[i] == written->daily_performance[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->annual_performance[i] == written->annual_performance[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->monthly_performance[i] == written->monthly_performance[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->last_12_months_performance[i] == written->last_12_months_performance[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->v24_hours_daily_performance[i] == written->v24_hours_daily_performance[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->v24_hours_annual_performance[i] == written->v24_hours_annual_performance[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->v24_hours_monthly_performance[i] == written->v24_hours_monthly_performance[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->last_12_months_24_hours_performance[i] == written->last_12_months_24_hours_performance[i]); }
}

/* Benchmark Message: written and read back, then read and written back */
static void check_benchmark_message(void) {
  BenchmarkMessage sent;
  BenchmarkMessage got;
  uint8_t wire[149];
  uint8_t again[149];

  any_benchmark_message(&sent);
  assert(encode_benchmark_message(&sent, wire, 0) == 149);
  assert(decode_benchmark_message(&got, wire, 0) == 149);
  equal_benchmark_message(&got, &sent);

  for (size_t i = 0; i < 149; i++) { wire[i] = arbitrary(); }
  assert(decode_benchmark_message(&got, wire, 0) == 149);
  assert(encode_benchmark_message(&got, again, 0) == 149);
  for (size_t i = 0; i < 149; i++) { assert(again[i] == wire[i]); }
}

/* ---- Capitalization Rules Message: 39 bytes ---------------------------------- */

/* Capitalization Rules */
typedef struct {
  uint8_t instrument_number[4];          /* bytes 0 to 3 */
  uint8_t date_indicators[8];            /* bytes 4 to 11 */
  uint8_t bursatility_indices[4];        /* bytes 12 to 15 */
  uint8_t bursatility_indices_sign;      /* byte 16 */
  uint8_t beta_coefficient[8];           /* bytes 17 to 24 */
  uint8_t beta_coefficient_sign;         /* byte 25 */
  uint8_t correlation_coefficient[8];    /* bytes 26 to 33 */
  uint8_t correlation_coefficient_sign;  /* byte 34 */
  uint8_t delta_difference[4];           /* bytes 35 to 38 */
} CapitalizationRulesMessage;

/* any Capitalization Rules Message at all: every byte one the checker chooses */
static void any_capitalization_rules_message(CapitalizationRulesMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->instrument_number[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->date_indicators[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->bursatility_indices[i] = arbitrary(); }
  record->bursatility_indices_sign = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->beta_coefficient[i] = arbitrary(); }
  record->beta_coefficient_sign = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->correlation_coefficient[i] = arbitrary(); }
  record->correlation_coefficient_sign = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->delta_difference[i] = arbitrary(); }
}

/* Capitalization Rules Message to the wire: 39 bytes from at, returning where the next byte goes */
static size_t encode_capitalization_rules_message(const CapitalizationRulesMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument_number[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->date_indicators[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->bursatility_indices[i]; }
  wire[at++] = record->bursatility_indices_sign;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->beta_coefficient[i]; }
  wire[at++] = record->beta_coefficient_sign;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->correlation_coefficient[i]; }
  wire[at++] = record->correlation_coefficient_sign;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->delta_difference[i]; }

  return at;
}

/* Capitalization Rules Message off the wire: 39 bytes from at, returning where the next byte lies */
static size_t decode_capitalization_rules_message(CapitalizationRulesMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->instrument_number[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->date_indicators[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->bursatility_indices[i] = wire[at++]; }
  record->bursatility_indices_sign = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->beta_coefficient[i] = wire[at++]; }
  record->beta_coefficient_sign = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->correlation_coefficient[i] = wire[at++]; }
  record->correlation_coefficient_sign = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->delta_difference[i] = wire[at++]; }

  return at;
}

/* what was read of Capitalization Rules Message is what was written, byte for byte */
static void equal_capitalization_rules_message(const CapitalizationRulesMessage *read, const CapitalizationRulesMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->instrument_number[i] == written->instrument_number[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->date_indicators[i] == written->date_indicators[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->bursatility_indices[i] == written->bursatility_indices[i]); }
  assert(read->bursatility_indices_sign == written->bursatility_indices_sign);
  for (size_t i = 0; i < 8; i++) { assert(read->beta_coefficient[i] == written->beta_coefficient[i]); }
  assert(read->beta_coefficient_sign == written->beta_coefficient_sign);
  for (size_t i = 0; i < 8; i++) { assert(read->correlation_coefficient[i] == written->correlation_coefficient[i]); }
  assert(read->correlation_coefficient_sign == written->correlation_coefficient_sign);
  for (size_t i = 0; i < 4; i++) { assert(read->delta_difference[i] == written->delta_difference[i]); }
}

/* Capitalization Rules Message: written and read back, then read and written back */
static void check_capitalization_rules_message(void) {
  CapitalizationRulesMessage sent;
  CapitalizationRulesMessage got;
  uint8_t wire[39];
  uint8_t again[39];

  any_capitalization_rules_message(&sent);
  assert(encode_capitalization_rules_message(&sent, wire, 0) == 39);
  assert(decode_capitalization_rules_message(&got, wire, 0) == 39);
  equal_capitalization_rules_message(&got, &sent);

  for (size_t i = 0; i < 39; i++) { wire[i] = arbitrary(); }
  assert(decode_capitalization_rules_message(&got, wire, 0) == 39);
  assert(encode_capitalization_rules_message(&got, again, 0) == 39);
  for (size_t i = 0; i < 39; i++) { assert(again[i] == wire[i]); }
}

/* ---- Closing Price Origin Message: 13 bytes ---------------------------------- */

/* Closing price origin */
typedef struct {
  uint8_t instrument_number[4];  /* bytes 0 to 3 */
  uint8_t origin_price[8];       /* bytes 4 to 11 */
  uint8_t sending;               /* byte 12 */
} ClosingPriceOriginMessage;

/* any Closing Price Origin Message at all: every byte one the checker chooses */
static void any_closing_price_origin_message(ClosingPriceOriginMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->instrument_number[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->origin_price[i] = arbitrary(); }
  record->sending = arbitrary();
}

/* Closing Price Origin Message to the wire: 13 bytes from at, returning where the next byte goes */
static size_t encode_closing_price_origin_message(const ClosingPriceOriginMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument_number[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->origin_price[i]; }
  wire[at++] = record->sending;

  return at;
}

/* Closing Price Origin Message off the wire: 13 bytes from at, returning where the next byte lies */
static size_t decode_closing_price_origin_message(ClosingPriceOriginMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->instrument_number[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->origin_price[i] = wire[at++]; }
  record->sending = wire[at++];

  return at;
}

/* what was read of Closing Price Origin Message is what was written, byte for byte */
static void equal_closing_price_origin_message(const ClosingPriceOriginMessage *read, const ClosingPriceOriginMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->instrument_number[i] == written->instrument_number[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->origin_price[i] == written->origin_price[i]); }
  assert(read->sending == written->sending);
}

/* Closing Price Origin Message: written and read back, then read and written back */
static void check_closing_price_origin_message(void) {
  ClosingPriceOriginMessage sent;
  ClosingPriceOriginMessage got;
  uint8_t wire[13];
  uint8_t again[13];

  any_closing_price_origin_message(&sent);
  assert(encode_closing_price_origin_message(&sent, wire, 0) == 13);
  assert(decode_closing_price_origin_message(&got, wire, 0) == 13);
  equal_closing_price_origin_message(&got, &sent);

  for (size_t i = 0; i < 13; i++) { wire[i] = arbitrary(); }
  assert(decode_closing_price_origin_message(&got, wire, 0) == 13);
  assert(encode_closing_price_origin_message(&got, again, 0) == 13);
  for (size_t i = 0; i < 13; i++) { assert(again[i] == wire[i]); }
}

/* ---- Mutual Funds Trades Message: 53 bytes ----------------------------------- */

/* Any transaction made in mutual funds is reported. */
typedef struct {
  uint8_t instrument_number[4];          /* bytes 0 to 3 */
  uint8_t origin;                        /* byte 4 */
  uint8_t date_of_the_trade[8];          /* bytes 5 to 12 */
  uint8_t price[8];                      /* bytes 13 to 20 */
  uint8_t book_value[8];                 /* bytes 21 to 28 */
  uint8_t number_of_sales_trades[4];     /* bytes 29 to 32 */
  uint8_t sales_volume[8];               /* bytes 33 to 40 */
  uint8_t number_of_purchase_trades[4];  /* bytes 41 to 44 */
  uint8_t purchase_volume[8];            /* bytes 45 to 52 */
} MutualFundsTradesMessage;

/* any Mutual Funds Trades Message at all: every byte one the checker chooses */
static void any_mutual_funds_trades_message(MutualFundsTradesMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->instrument_number[i] = arbitrary(); }
  record->origin = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->date_of_the_trade[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->book_value[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->number_of_sales_trades[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->sales_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->number_of_purchase_trades[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->purchase_volume[i] = arbitrary(); }
}

/* Mutual Funds Trades Message to the wire: 53 bytes from at, returning where the next byte goes */
static size_t encode_mutual_funds_trades_message(const MutualFundsTradesMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument_number[i]; }
  wire[at++] = record->origin;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->date_of_the_trade[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->book_value[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->number_of_sales_trades[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->sales_volume[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->number_of_purchase_trades[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->purchase_volume[i]; }

  return at;
}

/* Mutual Funds Trades Message off the wire: 53 bytes from at, returning where the next byte lies */
static size_t decode_mutual_funds_trades_message(MutualFundsTradesMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->instrument_number[i] = wire[at++]; }
  record->origin = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->date_of_the_trade[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->book_value[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->number_of_sales_trades[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->sales_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->number_of_purchase_trades[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->purchase_volume[i] = wire[at++]; }

  return at;
}

/* what was read of Mutual Funds Trades Message is what was written, byte for byte */
static void equal_mutual_funds_trades_message(const MutualFundsTradesMessage *read, const MutualFundsTradesMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->instrument_number[i] == written->instrument_number[i]); }
  assert(read->origin == written->origin);
  for (size_t i = 0; i < 8; i++) { assert(read->date_of_the_trade[i] == written->date_of_the_trade[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->price[i] == written->price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->book_value[i] == written->book_value[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->number_of_sales_trades[i] == written->number_of_sales_trades[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->sales_volume[i] == written->sales_volume[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->number_of_purchase_trades[i] == written->number_of_purchase_trades[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->purchase_volume[i] == written->purchase_volume[i]); }
}

/* Mutual Funds Trades Message: written and read back, then read and written back */
static void check_mutual_funds_trades_message(void) {
  MutualFundsTradesMessage sent;
  MutualFundsTradesMessage got;
  uint8_t wire[53];
  uint8_t again[53];

  any_mutual_funds_trades_message(&sent);
  assert(encode_mutual_funds_trades_message(&sent, wire, 0) == 53);
  assert(decode_mutual_funds_trades_message(&got, wire, 0) == 53);
  equal_mutual_funds_trades_message(&got, &sent);

  for (size_t i = 0; i < 53; i++) { wire[i] = arbitrary(); }
  assert(decode_mutual_funds_trades_message(&got, wire, 0) == 53);
  assert(encode_mutual_funds_trades_message(&got, again, 0) == 53);
  for (size_t i = 0; i < 53; i++) { assert(again[i] == wire[i]); }
}

/* ---- Opening Of Continuous Auctions Message: 21 bytes ------------------------ */

/* The message is sent when one of the ongoing, volatility or SIC bidding sessions is generated. */
typedef struct {
  uint8_t instrument_number[4];             /* bytes 0 to 3 */
  uint8_t origin;                           /* byte 4 */
  uint8_t auction_session_startup_time[8];  /* bytes 5 to 12 */
  uint8_t auction_session_end_time[8];      /* bytes 13 to 20 */
} OpeningOfContinuousAuctionsMessage;

/* any Opening Of Continuous Auctions Message at all: every byte one the checker chooses */
static void any_opening_of_continuous_auctions_message(OpeningOfContinuousAuctionsMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->instrument_number[i] = arbitrary(); }
  record->origin = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->auction_session_startup_time[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->auction_session_end_time[i] = arbitrary(); }
}

/* Opening Of Continuous Auctions Message to the wire: 21 bytes from at, returning where the next byte goes */
static size_t encode_opening_of_continuous_auctions_message(const OpeningOfContinuousAuctionsMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument_number[i]; }
  wire[at++] = record->origin;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->auction_session_startup_time[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->auction_session_end_time[i]; }

  return at;
}

/* Opening Of Continuous Auctions Message off the wire: 21 bytes from at, returning where the next byte lies */
static size_t decode_opening_of_continuous_auctions_message(OpeningOfContinuousAuctionsMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->instrument_number[i] = wire[at++]; }
  record->origin = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->auction_session_startup_time[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->auction_session_end_time[i] = wire[at++]; }

  return at;
}

/* what was read of Opening Of Continuous Auctions Message is what was written, byte for byte */
static void equal_opening_of_continuous_auctions_message(const OpeningOfContinuousAuctionsMessage *read, const OpeningOfContinuousAuctionsMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->instrument_number[i] == written->instrument_number[i]); }
  assert(read->origin == written->origin);
  for (size_t i = 0; i < 8; i++) { assert(read->auction_session_startup_time[i] == written->auction_session_startup_time[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->auction_session_end_time[i] == written->auction_session_end_time[i]); }
}

/* Opening Of Continuous Auctions Message: written and read back, then read and written back */
static void check_opening_of_continuous_auctions_message(void) {
  OpeningOfContinuousAuctionsMessage sent;
  OpeningOfContinuousAuctionsMessage got;
  uint8_t wire[21];
  uint8_t again[21];

  any_opening_of_continuous_auctions_message(&sent);
  assert(encode_opening_of_continuous_auctions_message(&sent, wire, 0) == 21);
  assert(decode_opening_of_continuous_auctions_message(&got, wire, 0) == 21);
  equal_opening_of_continuous_auctions_message(&got, &sent);

  for (size_t i = 0; i < 21; i++) { wire[i] = arbitrary(); }
  assert(decode_opening_of_continuous_auctions_message(&got, wire, 0) == 21);
  assert(encode_opening_of_continuous_auctions_message(&got, again, 0) == 21);
  for (size_t i = 0; i < 21; i++) { assert(again[i] == wire[i]); }
}

/* ---- Existence Of Bids At Mid Price Message: 6 bytes ------------------------- */

/* This message is generated when an instrument enters a bid in the hidden electronic book At Mean Price. */
typedef struct {
  uint8_t instrument_number[4];  /* bytes 0 to 3 */
  uint8_t origin;                /* byte 4 */
  uint8_t bids_existing;         /* byte 5 */
} ExistenceOfBidsAtMidPriceMessage;

/* any Existence Of Bids At Mid Price Message at all: every byte one the checker chooses */
static void any_existence_of_bids_at_mid_price_message(ExistenceOfBidsAtMidPriceMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->instrument_number[i] = arbitrary(); }
  record->origin = arbitrary();
  record->bids_existing = arbitrary();
}

/* Existence Of Bids At Mid Price Message to the wire: 6 bytes from at, returning where the next byte goes */
static size_t encode_existence_of_bids_at_mid_price_message(const ExistenceOfBidsAtMidPriceMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument_number[i]; }
  wire[at++] = record->origin;
  wire[at++] = record->bids_existing;

  return at;
}

/* Existence Of Bids At Mid Price Message off the wire: 6 bytes from at, returning where the next byte lies */
static size_t decode_existence_of_bids_at_mid_price_message(ExistenceOfBidsAtMidPriceMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->instrument_number[i] = wire[at++]; }
  record->origin = wire[at++];
  record->bids_existing = wire[at++];

  return at;
}

/* what was read of Existence Of Bids At Mid Price Message is what was written, byte for byte */
static void equal_existence_of_bids_at_mid_price_message(const ExistenceOfBidsAtMidPriceMessage *read, const ExistenceOfBidsAtMidPriceMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->instrument_number[i] == written->instrument_number[i]); }
  assert(read->origin == written->origin);
  assert(read->bids_existing == written->bids_existing);
}

/* Existence Of Bids At Mid Price Message: written and read back, then read and written back */
static void check_existence_of_bids_at_mid_price_message(void) {
  ExistenceOfBidsAtMidPriceMessage sent;
  ExistenceOfBidsAtMidPriceMessage got;
  uint8_t wire[6];
  uint8_t again[6];

  any_existence_of_bids_at_mid_price_message(&sent);
  assert(encode_existence_of_bids_at_mid_price_message(&sent, wire, 0) == 6);
  assert(decode_existence_of_bids_at_mid_price_message(&got, wire, 0) == 6);
  equal_existence_of_bids_at_mid_price_message(&got, &sent);

  for (size_t i = 0; i < 6; i++) { wire[i] = arbitrary(); }
  assert(decode_existence_of_bids_at_mid_price_message(&got, wire, 0) == 6);
  assert(encode_existence_of_bids_at_mid_price_message(&got, again, 0) == 6);
  for (size_t i = 0; i < 6; i++) { assert(again[i] == wire[i]); }
}

/* ---- Catalogue Of Debt And Metals Instruments Message: 103 bytes ------------- */

/* Catalogue sent for instruments pertaining to the Local Fixed rate, Global Fixed rate and metals markets. */
typedef struct {
  uint8_t number_of_the_instrument[4];  /* bytes 0 to 3 */
  uint8_t origin;                       /* byte 4 */
  uint8_t type_of_value[2];             /* bytes 5 to 6 */
  uint8_t issuing_company[7];           /* bytes 7 to 13 */
  uint8_t issuance[6];                  /* bytes 14 to 19 */
  uint8_t date_of_issuance[8];          /* bytes 20 to 27 */
  uint8_t date_of_maturity[8];          /* bytes 28 to 35 */
  uint8_t price_rate_of_reference[8];   /* bytes 36 to 43 */
  uint8_t date_of_reference[8];         /* bytes 44 to 51 */
  uint8_t reference;                    /* byte 52 */
  uint8_t term_days[2];                 /* bytes 53 to 54 */
  uint8_t coupon_period[2];             /* bytes 55 to 56 */
  uint8_t isin[12];                     /* bytes 57 to 68 */
  uint8_t market;                       /* byte 69 */
  uint8_t current_nominal_value[8];     /* bytes 70 to 77 */
  uint8_t original_nominal_value[8];    /* bytes 78 to 85 */
  uint8_t outstanding_shares[8];        /* bytes 86 to 93 */
  uint8_t amount_placed[8];             /* bytes 94 to 101 */
  uint8_t trades_rate_price;            /* byte 102 */
} CatalogueOfDebtAndMetalsInstrumentsMessage;

/* any Catalogue Of Debt And Metals Instruments Message at all: every byte one the checker chooses */
static void any_catalogue_of_debt_and_metals_instruments_message(CatalogueOfDebtAndMetalsInstrumentsMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->number_of_the_instrument[i] = arbitrary(); }
  record->origin = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->type_of_value[i] = arbitrary(); }
  for (size_t i = 0; i < 7; i++) { record->issuing_company[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->issuance[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->date_of_issuance[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->date_of_maturity[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->price_rate_of_reference[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->date_of_reference[i] = arbitrary(); }
  record->reference = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->term_days[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->coupon_period[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->isin[i] = arbitrary(); }
  record->market = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->current_nominal_value[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->original_nominal_value[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->outstanding_shares[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->amount_placed[i] = arbitrary(); }
  record->trades_rate_price = arbitrary();
}

/* Catalogue Of Debt And Metals Instruments Message to the wire: 103 bytes from at, returning where the next byte goes */
static size_t encode_catalogue_of_debt_and_metals_instruments_message(const CatalogueOfDebtAndMetalsInstrumentsMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->number_of_the_instrument[i]; }
  wire[at++] = record->origin;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->type_of_value[i]; }
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->issuing_company[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->issuance[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->date_of_issuance[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->date_of_maturity[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price_rate_of_reference[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->date_of_reference[i]; }
  wire[at++] = record->reference;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->term_days[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->coupon_period[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->isin[i]; }
  wire[at++] = record->market;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->current_nominal_value[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->original_nominal_value[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->outstanding_shares[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->amount_placed[i]; }
  wire[at++] = record->trades_rate_price;

  return at;
}

/* Catalogue Of Debt And Metals Instruments Message off the wire: 103 bytes from at, returning where the next byte lies */
static size_t decode_catalogue_of_debt_and_metals_instruments_message(CatalogueOfDebtAndMetalsInstrumentsMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->number_of_the_instrument[i] = wire[at++]; }
  record->origin = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->type_of_value[i] = wire[at++]; }
  for (size_t i = 0; i < 7; i++) { record->issuing_company[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->issuance[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->date_of_issuance[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->date_of_maturity[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->price_rate_of_reference[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->date_of_reference[i] = wire[at++]; }
  record->reference = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->term_days[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->coupon_period[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->isin[i] = wire[at++]; }
  record->market = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->current_nominal_value[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->original_nominal_value[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->outstanding_shares[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->amount_placed[i] = wire[at++]; }
  record->trades_rate_price = wire[at++];

  return at;
}

/* what was read of Catalogue Of Debt And Metals Instruments Message is what was written, byte for byte */
static void equal_catalogue_of_debt_and_metals_instruments_message(const CatalogueOfDebtAndMetalsInstrumentsMessage *read, const CatalogueOfDebtAndMetalsInstrumentsMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->number_of_the_instrument[i] == written->number_of_the_instrument[i]); }
  assert(read->origin == written->origin);
  for (size_t i = 0; i < 2; i++) { assert(read->type_of_value[i] == written->type_of_value[i]); }
  for (size_t i = 0; i < 7; i++) { assert(read->issuing_company[i] == written->issuing_company[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->issuance[i] == written->issuance[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->date_of_issuance[i] == written->date_of_issuance[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->date_of_maturity[i] == written->date_of_maturity[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->price_rate_of_reference[i] == written->price_rate_of_reference[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->date_of_reference[i] == written->date_of_reference[i]); }
  assert(read->reference == written->reference);
  for (size_t i = 0; i < 2; i++) { assert(read->term_days[i] == written->term_days[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->coupon_period[i] == written->coupon_period[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->isin[i] == written->isin[i]); }
  assert(read->market == written->market);
  for (size_t i = 0; i < 8; i++) { assert(read->current_nominal_value[i] == written->current_nominal_value[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->original_nominal_value[i] == written->original_nominal_value[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->outstanding_shares[i] == written->outstanding_shares[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->amount_placed[i] == written->amount_placed[i]); }
  assert(read->trades_rate_price == written->trades_rate_price);
}

/* Catalogue Of Debt And Metals Instruments Message: written and read back, then read and written back */
static void check_catalogue_of_debt_and_metals_instruments_message(void) {
  CatalogueOfDebtAndMetalsInstrumentsMessage sent;
  CatalogueOfDebtAndMetalsInstrumentsMessage got;
  uint8_t wire[103];
  uint8_t again[103];

  any_catalogue_of_debt_and_metals_instruments_message(&sent);
  assert(encode_catalogue_of_debt_and_metals_instruments_message(&sent, wire, 0) == 103);
  assert(decode_catalogue_of_debt_and_metals_instruments_message(&got, wire, 0) == 103);
  equal_catalogue_of_debt_and_metals_instruments_message(&got, &sent);

  for (size_t i = 0; i < 103; i++) { wire[i] = arbitrary(); }
  assert(decode_catalogue_of_debt_and_metals_instruments_message(&got, wire, 0) == 103);
  assert(encode_catalogue_of_debt_and_metals_instruments_message(&got, again, 0) == 103);
  for (size_t i = 0; i < 103; i++) { assert(again[i] == wire[i]); }
}

/* ---- Catalog Sent For Instruments Belonging To Mutual Funds Message: 78 bytes ---- */

/* Catalogue sent for instrument pertaining to the investment companies. */
typedef struct {
  uint8_t number_of_the_instrument[4];  /* bytes 0 to 3 */
  uint8_t origin;                       /* byte 4 */
  uint8_t type_of_value[2];             /* bytes 5 to 6 */
  uint8_t issuing_company[7];           /* bytes 7 to 13 */
  uint8_t series[6];                    /* bytes 14 to 19 */
  uint8_t sector;                       /* byte 20 */
  uint8_t subsector;                    /* byte 21 */
  uint8_t industry;                     /* byte 22 */
  uint8_t sub_industry;                 /* byte 23 */
  uint8_t trading_company[10];          /* bytes 24 to 33 */
  uint8_t reference_price[8];           /* bytes 34 to 41 */
  uint8_t reference_date[8];            /* bytes 42 to 49 */
  uint8_t reference;                    /* byte 50 */
  uint8_t isin[12];                     /* bytes 51 to 62 */
  uint8_t rating[15];                   /* bytes 63 to 77 */
} CatalogSentForInstrumentsBelongingToMutualFundsMessage;

/* any Catalog Sent For Instruments Belonging To Mutual Funds Message at all: every byte one the checker chooses */
static void any_catalog_sent_for_instruments_belonging_to_mutual_funds_message(CatalogSentForInstrumentsBelongingToMutualFundsMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->number_of_the_instrument[i] = arbitrary(); }
  record->origin = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->type_of_value[i] = arbitrary(); }
  for (size_t i = 0; i < 7; i++) { record->issuing_company[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->series[i] = arbitrary(); }
  record->sector = arbitrary();
  record->subsector = arbitrary();
  record->industry = arbitrary();
  record->sub_industry = arbitrary();
  for (size_t i = 0; i < 10; i++) { record->trading_company[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->reference_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->reference_date[i] = arbitrary(); }
  record->reference = arbitrary();
  for (size_t i = 0; i < 12; i++) { record->isin[i] = arbitrary(); }
  for (size_t i = 0; i < 15; i++) { record->rating[i] = arbitrary(); }
}

/* Catalog Sent For Instruments Belonging To Mutual Funds Message to the wire: 78 bytes from at, returning where the next byte goes */
static size_t encode_catalog_sent_for_instruments_belonging_to_mutual_funds_message(const CatalogSentForInstrumentsBelongingToMutualFundsMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->number_of_the_instrument[i]; }
  wire[at++] = record->origin;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->type_of_value[i]; }
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->issuing_company[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->series[i]; }
  wire[at++] = record->sector;
  wire[at++] = record->subsector;
  wire[at++] = record->industry;
  wire[at++] = record->sub_industry;
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->trading_company[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->reference_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->reference_date[i]; }
  wire[at++] = record->reference;
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->isin[i]; }
  for (size_t i = 0; i < 15; i++) { wire[at++] = record->rating[i]; }

  return at;
}

/* Catalog Sent For Instruments Belonging To Mutual Funds Message off the wire: 78 bytes from at, returning where the next byte lies */
static size_t decode_catalog_sent_for_instruments_belonging_to_mutual_funds_message(CatalogSentForInstrumentsBelongingToMutualFundsMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->number_of_the_instrument[i] = wire[at++]; }
  record->origin = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->type_of_value[i] = wire[at++]; }
  for (size_t i = 0; i < 7; i++) { record->issuing_company[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->series[i] = wire[at++]; }
  record->sector = wire[at++];
  record->subsector = wire[at++];
  record->industry = wire[at++];
  record->sub_industry = wire[at++];
  for (size_t i = 0; i < 10; i++) { record->trading_company[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->reference_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->reference_date[i] = wire[at++]; }
  record->reference = wire[at++];
  for (size_t i = 0; i < 12; i++) { record->isin[i] = wire[at++]; }
  for (size_t i = 0; i < 15; i++) { record->rating[i] = wire[at++]; }

  return at;
}

/* what was read of Catalog Sent For Instruments Belonging To Mutual Funds Message is what was written, byte for byte */
static void equal_catalog_sent_for_instruments_belonging_to_mutual_funds_message(const CatalogSentForInstrumentsBelongingToMutualFundsMessage *read, const CatalogSentForInstrumentsBelongingToMutualFundsMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->number_of_the_instrument[i] == written->number_of_the_instrument[i]); }
  assert(read->origin == written->origin);
  for (size_t i = 0; i < 2; i++) { assert(read->type_of_value[i] == written->type_of_value[i]); }
  for (size_t i = 0; i < 7; i++) { assert(read->issuing_company[i] == written->issuing_company[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->series[i] == written->series[i]); }
  assert(read->sector == written->sector);
  assert(read->subsector == written->subsector);
  assert(read->industry == written->industry);
  assert(read->sub_industry == written->sub_industry);
  for (size_t i = 0; i < 10; i++) { assert(read->trading_company[i] == written->trading_company[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->reference_price[i] == written->reference_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->reference_date[i] == written->reference_date[i]); }
  assert(read->reference == written->reference);
  for (size_t i = 0; i < 12; i++) { assert(read->isin[i] == written->isin[i]); }
  for (size_t i = 0; i < 15; i++) { assert(read->rating[i] == written->rating[i]); }
}

/* Catalog Sent For Instruments Belonging To Mutual Funds Message: written and read back, then read and written back */
static void check_catalog_sent_for_instruments_belonging_to_mutual_funds_message(void) {
  CatalogSentForInstrumentsBelongingToMutualFundsMessage sent;
  CatalogSentForInstrumentsBelongingToMutualFundsMessage got;
  uint8_t wire[78];
  uint8_t again[78];

  any_catalog_sent_for_instruments_belonging_to_mutual_funds_message(&sent);
  assert(encode_catalog_sent_for_instruments_belonging_to_mutual_funds_message(&sent, wire, 0) == 78);
  assert(decode_catalog_sent_for_instruments_belonging_to_mutual_funds_message(&got, wire, 0) == 78);
  equal_catalog_sent_for_instruments_belonging_to_mutual_funds_message(&got, &sent);

  for (size_t i = 0; i < 78; i++) { wire[i] = arbitrary(); }
  assert(decode_catalog_sent_for_instruments_belonging_to_mutual_funds_message(&got, wire, 0) == 78);
  assert(encode_catalog_sent_for_instruments_belonging_to_mutual_funds_message(&got, again, 0) == 78);
  for (size_t i = 0; i < 78; i++) { assert(again[i] == wire[i]); }
}

/* ---- Weighted Average Price Message: 21 bytes -------------------------------- */

/* This message will have the weighted average price (WAP) per instrument and is sent for each transaction generated within the calculation period of the WAP (last 20 minutes of the trading session); when there are no more trades in this period, the message is sent with the Weighted Average Price in zeros. */
typedef struct {
  uint8_t instrument_number[4];       /* bytes 0 to 3 */
  uint8_t origin;                     /* byte 4 */
  uint8_t weighted_average_price[8];  /* bytes 5 to 12 */
  uint8_t volatility[8];              /* bytes 13 to 20 */
} WeightedAveragePriceMessage;

/* any Weighted Average Price Message at all: every byte one the checker chooses */
static void any_weighted_average_price_message(WeightedAveragePriceMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->instrument_number[i] = arbitrary(); }
  record->origin = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->weighted_average_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->volatility[i] = arbitrary(); }
}

/* Weighted Average Price Message to the wire: 21 bytes from at, returning where the next byte goes */
static size_t encode_weighted_average_price_message(const WeightedAveragePriceMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument_number[i]; }
  wire[at++] = record->origin;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->weighted_average_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->volatility[i]; }

  return at;
}

/* Weighted Average Price Message off the wire: 21 bytes from at, returning where the next byte lies */
static size_t decode_weighted_average_price_message(WeightedAveragePriceMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->instrument_number[i] = wire[at++]; }
  record->origin = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->weighted_average_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->volatility[i] = wire[at++]; }

  return at;
}

/* what was read of Weighted Average Price Message is what was written, byte for byte */
static void equal_weighted_average_price_message(const WeightedAveragePriceMessage *read, const WeightedAveragePriceMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->instrument_number[i] == written->instrument_number[i]); }
  assert(read->origin == written->origin);
  for (size_t i = 0; i < 8; i++) { assert(read->weighted_average_price[i] == written->weighted_average_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->volatility[i] == written->volatility[i]); }
}

/* Weighted Average Price Message: written and read back, then read and written back */
static void check_weighted_average_price_message(void) {
  WeightedAveragePriceMessage sent;
  WeightedAveragePriceMessage got;
  uint8_t wire[21];
  uint8_t again[21];

  any_weighted_average_price_message(&sent);
  assert(encode_weighted_average_price_message(&sent, wire, 0) == 21);
  assert(decode_weighted_average_price_message(&got, wire, 0) == 21);
  equal_weighted_average_price_message(&got, &sent);

  for (size_t i = 0; i < 21; i++) { wire[i] = arbitrary(); }
  assert(decode_weighted_average_price_message(&got, wire, 0) == 21);
  assert(encode_weighted_average_price_message(&got, again, 0) == 21);
  for (size_t i = 0; i < 21; i++) { assert(again[i] == wire[i]); }
}

/* ---- System Events Message: 31 bytes ----------------------------------------- */

/* The system events message is used to inform that an event has taken place, which needs to be disclosed to the public for its attention. */
typedef struct {
  uint8_t instrument_number[4];  /* bytes 0 to 3 */
  uint8_t origin;                /* byte 4 */
  uint8_t code_of_event;         /* byte 5 */
  uint8_t market;                /* byte 6 */
  uint8_t send_time[8];          /* bytes 7 to 14 */
  uint8_t end_time[8];           /* bytes 15 to 22 */
  uint8_t group[8];              /* bytes 23 to 30 */
} SystemEventsMessage;

/* any System Events Message at all: every byte one the checker chooses */
static void any_system_events_message(SystemEventsMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->instrument_number[i] = arbitrary(); }
  record->origin = arbitrary();
  record->code_of_event = arbitrary();
  record->market = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->send_time[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->end_time[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->group[i] = arbitrary(); }
}

/* System Events Message to the wire: 31 bytes from at, returning where the next byte goes */
static size_t encode_system_events_message(const SystemEventsMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument_number[i]; }
  wire[at++] = record->origin;
  wire[at++] = record->code_of_event;
  wire[at++] = record->market;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->send_time[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->end_time[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->group[i]; }

  return at;
}

/* System Events Message off the wire: 31 bytes from at, returning where the next byte lies */
static size_t decode_system_events_message(SystemEventsMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->instrument_number[i] = wire[at++]; }
  record->origin = wire[at++];
  record->code_of_event = wire[at++];
  record->market = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->send_time[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->end_time[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->group[i] = wire[at++]; }

  return at;
}

/* what was read of System Events Message is what was written, byte for byte */
static void equal_system_events_message(const SystemEventsMessage *read, const SystemEventsMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->instrument_number[i] == written->instrument_number[i]); }
  assert(read->origin == written->origin);
  assert(read->code_of_event == written->code_of_event);
  assert(read->market == written->market);
  for (size_t i = 0; i < 8; i++) { assert(read->send_time[i] == written->send_time[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->end_time[i] == written->end_time[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->group[i] == written->group[i]); }
}

/* System Events Message: written and read back, then read and written back */
static void check_system_events_message(void) {
  SystemEventsMessage sent;
  SystemEventsMessage got;
  uint8_t wire[31];
  uint8_t again[31];

  any_system_events_message(&sent);
  assert(encode_system_events_message(&sent, wire, 0) == 31);
  assert(decode_system_events_message(&got, wire, 0) == 31);
  equal_system_events_message(&got, &sent);

  for (size_t i = 0; i < 31; i++) { wire[i] = arbitrary(); }
  assert(decode_system_events_message(&got, wire, 0) == 31);
  assert(encode_system_events_message(&got, again, 0) == 31);
  for (size_t i = 0; i < 31; i++) { assert(again[i] == wire[i]); }
}

/* ---- Reference Price Message: 14 bytes --------------------------------------- */

/* This message is sent to define the reference price of an instrument. */
typedef struct {
  uint8_t instrument_number[4];  /* bytes 0 to 3 */
  uint8_t origin;                /* byte 4 */
  uint8_t price[8];              /* bytes 5 to 12 */
  uint8_t price_type;            /* byte 13 */
} ReferencePriceMessage;

/* any Reference Price Message at all: every byte one the checker chooses */
static void any_reference_price_message(ReferencePriceMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->instrument_number[i] = arbitrary(); }
  record->origin = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->price[i] = arbitrary(); }
  record->price_type = arbitrary();
}

/* Reference Price Message to the wire: 14 bytes from at, returning where the next byte goes */
static size_t encode_reference_price_message(const ReferencePriceMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument_number[i]; }
  wire[at++] = record->origin;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price[i]; }
  wire[at++] = record->price_type;

  return at;
}

/* Reference Price Message off the wire: 14 bytes from at, returning where the next byte lies */
static size_t decode_reference_price_message(ReferencePriceMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->instrument_number[i] = wire[at++]; }
  record->origin = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->price[i] = wire[at++]; }
  record->price_type = wire[at++];

  return at;
}

/* what was read of Reference Price Message is what was written, byte for byte */
static void equal_reference_price_message(const ReferencePriceMessage *read, const ReferencePriceMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->instrument_number[i] == written->instrument_number[i]); }
  assert(read->origin == written->origin);
  for (size_t i = 0; i < 8; i++) { assert(read->price[i] == written->price[i]); }
  assert(read->price_type == written->price_type);
}

/* Reference Price Message: written and read back, then read and written back */
static void check_reference_price_message(void) {
  ReferencePriceMessage sent;
  ReferencePriceMessage got;
  uint8_t wire[14];
  uint8_t again[14];

  any_reference_price_message(&sent);
  assert(encode_reference_price_message(&sent, wire, 0) == 14);
  assert(decode_reference_price_message(&got, wire, 0) == 14);
  equal_reference_price_message(&got, &sent);

  for (size_t i = 0; i < 14; i++) { wire[i] = arbitrary(); }
  assert(decode_reference_price_message(&got, wire, 0) == 14);
  assert(encode_reference_price_message(&got, again, 0) == 14);
  for (size_t i = 0; i < 14; i++) { assert(again[i] == wire[i]); }
}

/* ---- Changes In Status Message: 7 bytes -------------------------------------- */

/* This message is sent when there has been a change in the status of the instruments. */
typedef struct {
  uint8_t instrument_number[4];  /* bytes 0 to 3 */
  uint8_t origin;                /* byte 4 */
  uint8_t status;                /* byte 5 */
  uint8_t reason;                /* byte 6 */
} ChangesInStatusMessage;

/* any Changes In Status Message at all: every byte one the checker chooses */
static void any_changes_in_status_message(ChangesInStatusMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->instrument_number[i] = arbitrary(); }
  record->origin = arbitrary();
  record->status = arbitrary();
  record->reason = arbitrary();
}

/* Changes In Status Message to the wire: 7 bytes from at, returning where the next byte goes */
static size_t encode_changes_in_status_message(const ChangesInStatusMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument_number[i]; }
  wire[at++] = record->origin;
  wire[at++] = record->status;
  wire[at++] = record->reason;

  return at;
}

/* Changes In Status Message off the wire: 7 bytes from at, returning where the next byte lies */
static size_t decode_changes_in_status_message(ChangesInStatusMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->instrument_number[i] = wire[at++]; }
  record->origin = wire[at++];
  record->status = wire[at++];
  record->reason = wire[at++];

  return at;
}

/* what was read of Changes In Status Message is what was written, byte for byte */
static void equal_changes_in_status_message(const ChangesInStatusMessage *read, const ChangesInStatusMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->instrument_number[i] == written->instrument_number[i]); }
  assert(read->origin == written->origin);
  assert(read->status == written->status);
  assert(read->reason == written->reason);
}

/* Changes In Status Message: written and read back, then read and written back */
static void check_changes_in_status_message(void) {
  ChangesInStatusMessage sent;
  ChangesInStatusMessage got;
  uint8_t wire[7];
  uint8_t again[7];

  any_changes_in_status_message(&sent);
  assert(encode_changes_in_status_message(&sent, wire, 0) == 7);
  assert(decode_changes_in_status_message(&got, wire, 0) == 7);
  equal_changes_in_status_message(&got, &sent);

  for (size_t i = 0; i < 7; i++) { wire[i] = arbitrary(); }
  assert(decode_changes_in_status_message(&got, wire, 0) == 7);
  assert(encode_changes_in_status_message(&got, again, 0) == 7);
  for (size_t i = 0; i < 7; i++) { assert(again[i] == wire[i]); }
}

/* ---- Catalog For Instruments Belonging To The Capital Warrants Market Message: 66 bytes ---- */

/* Catalogue for instruments pertaining to the Equities Warrants market. */
typedef struct {
  uint8_t number_of_the_instrument[4];  /* bytes 0 to 3 */
  uint8_t origin;                       /* byte 4 */
  uint8_t type_of_value[2];             /* bytes 5 to 6 */
  uint8_t issuing_company[7];           /* bytes 7 to 13 */
  uint8_t series[6];                    /* bytes 14 to 19 */
  uint8_t type_of_warrant;              /* byte 20 */
  uint8_t date_of_maturity[8];          /* bytes 21 to 28 */
  uint8_t price_of_exercise[8];         /* bytes 29 to 36 */
  uint8_t reference_price[8];           /* bytes 37 to 44 */
  uint8_t reference_date[8];            /* bytes 45 to 52 */
  uint8_t reference;                    /* byte 53 */
  uint8_t isin[12];                     /* bytes 54 to 65 */
} CatalogForInstrumentsBelongingToTheCapitalWarrantsMarketMessage;

/* any Catalog For Instruments Belonging To The Capital Warrants Market Message at all: every byte one the checker chooses */
static void any_catalog_for_instruments_belonging_to_the_capital_warrants_market_message(CatalogForInstrumentsBelongingToTheCapitalWarrantsMarketMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->number_of_the_instrument[i] = arbitrary(); }
  record->origin = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->type_of_value[i] = arbitrary(); }
  for (size_t i = 0; i < 7; i++) { record->issuing_company[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->series[i] = arbitrary(); }
  record->type_of_warrant = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->date_of_maturity[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->price_of_exercise[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->reference_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->reference_date[i] = arbitrary(); }
  record->reference = arbitrary();
  for (size_t i = 0; i < 12; i++) { record->isin[i] = arbitrary(); }
}

/* Catalog For Instruments Belonging To The Capital Warrants Market Message to the wire: 66 bytes from at, returning where the next byte goes */
static size_t encode_catalog_for_instruments_belonging_to_the_capital_warrants_market_message(const CatalogForInstrumentsBelongingToTheCapitalWarrantsMarketMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->number_of_the_instrument[i]; }
  wire[at++] = record->origin;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->type_of_value[i]; }
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->issuing_company[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->series[i]; }
  wire[at++] = record->type_of_warrant;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->date_of_maturity[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price_of_exercise[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->reference_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->reference_date[i]; }
  wire[at++] = record->reference;
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->isin[i]; }

  return at;
}

/* Catalog For Instruments Belonging To The Capital Warrants Market Message off the wire: 66 bytes from at, returning where the next byte lies */
static size_t decode_catalog_for_instruments_belonging_to_the_capital_warrants_market_message(CatalogForInstrumentsBelongingToTheCapitalWarrantsMarketMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->number_of_the_instrument[i] = wire[at++]; }
  record->origin = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->type_of_value[i] = wire[at++]; }
  for (size_t i = 0; i < 7; i++) { record->issuing_company[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->series[i] = wire[at++]; }
  record->type_of_warrant = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->date_of_maturity[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->price_of_exercise[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->reference_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->reference_date[i] = wire[at++]; }
  record->reference = wire[at++];
  for (size_t i = 0; i < 12; i++) { record->isin[i] = wire[at++]; }

  return at;
}

/* what was read of Catalog For Instruments Belonging To The Capital Warrants Market Message is what was written, byte for byte */
static void equal_catalog_for_instruments_belonging_to_the_capital_warrants_market_message(const CatalogForInstrumentsBelongingToTheCapitalWarrantsMarketMessage *read, const CatalogForInstrumentsBelongingToTheCapitalWarrantsMarketMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->number_of_the_instrument[i] == written->number_of_the_instrument[i]); }
  assert(read->origin == written->origin);
  for (size_t i = 0; i < 2; i++) { assert(read->type_of_value[i] == written->type_of_value[i]); }
  for (size_t i = 0; i < 7; i++) { assert(read->issuing_company[i] == written->issuing_company[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->series[i] == written->series[i]); }
  assert(read->type_of_warrant == written->type_of_warrant);
  for (size_t i = 0; i < 8; i++) { assert(read->date_of_maturity[i] == written->date_of_maturity[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->price_of_exercise[i] == written->price_of_exercise[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->reference_price[i] == written->reference_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->reference_date[i] == written->reference_date[i]); }
  assert(read->reference == written->reference);
  for (size_t i = 0; i < 12; i++) { assert(read->isin[i] == written->isin[i]); }
}

/* Catalog For Instruments Belonging To The Capital Warrants Market Message: written and read back, then read and written back */
static void check_catalog_for_instruments_belonging_to_the_capital_warrants_market_message(void) {
  CatalogForInstrumentsBelongingToTheCapitalWarrantsMarketMessage sent;
  CatalogForInstrumentsBelongingToTheCapitalWarrantsMarketMessage got;
  uint8_t wire[66];
  uint8_t again[66];

  any_catalog_for_instruments_belonging_to_the_capital_warrants_market_message(&sent);
  assert(encode_catalog_for_instruments_belonging_to_the_capital_warrants_market_message(&sent, wire, 0) == 66);
  assert(decode_catalog_for_instruments_belonging_to_the_capital_warrants_market_message(&got, wire, 0) == 66);
  equal_catalog_for_instruments_belonging_to_the_capital_warrants_market_message(&got, &sent);

  for (size_t i = 0; i < 66; i++) { wire[i] = arbitrary(); }
  assert(decode_catalog_for_instruments_belonging_to_the_capital_warrants_market_message(&got, wire, 0) == 66);
  assert(encode_catalog_for_instruments_belonging_to_the_capital_warrants_market_message(&got, again, 0) == 66);
  for (size_t i = 0; i < 66; i++) { assert(again[i] == wire[i]); }
}

/* ---- Catalog Sent For Instruments Belonging To Capital Tracs Message: 82 bytes ---- */

/* Catalogue sent for instruments pertaining to the equities TRACS. */
typedef struct {
  uint8_t number_of_the_trac[4];          /* bytes 0 to 3 */
  uint8_t origin;                         /* byte 4 */
  uint8_t name_of_the_trac[8];            /* bytes 5 to 12 */
  uint8_t underlying_issuing_company[7];  /* bytes 13 to 19 */
  uint8_t underlying_series[6];           /* bytes 20 to 25 */
  uint8_t securities[8];                  /* bytes 26 to 33 */
  uint8_t excluded_securities[8];         /* bytes 34 to 41 */
  uint8_t price[8];                       /* bytes 42 to 49 */
  uint8_t component_in_cash[8];           /* bytes 50 to 57 */
  uint8_t excluded_value[8];              /* bytes 58 to 65 */
  uint8_t number_of_certificates[8];      /* bytes 66 to 73 */
  uint8_t theoretical_price[8];           /* bytes 74 to 81 */
} CatalogSentForInstrumentsBelongingToCapitalTracsMessage;

/* any Catalog Sent For Instruments Belonging To Capital Tracs Message at all: every byte one the checker chooses */
static void any_catalog_sent_for_instruments_belonging_to_capital_tracs_message(CatalogSentForInstrumentsBelongingToCapitalTracsMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->number_of_the_trac[i] = arbitrary(); }
  record->origin = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->name_of_the_trac[i] = arbitrary(); }
  for (size_t i = 0; i < 7; i++) { record->underlying_issuing_company[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->underlying_series[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->securities[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->excluded_securities[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->component_in_cash[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->excluded_value[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->number_of_certificates[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->theoretical_price[i] = arbitrary(); }
}

/* Catalog Sent For Instruments Belonging To Capital Tracs Message to the wire: 82 bytes from at, returning where the next byte goes */
static size_t encode_catalog_sent_for_instruments_belonging_to_capital_tracs_message(const CatalogSentForInstrumentsBelongingToCapitalTracsMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->number_of_the_trac[i]; }
  wire[at++] = record->origin;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->name_of_the_trac[i]; }
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->underlying_issuing_company[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->underlying_series[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->securities[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->excluded_securities[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->component_in_cash[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->excluded_value[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->number_of_certificates[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->theoretical_price[i]; }

  return at;
}

/* Catalog Sent For Instruments Belonging To Capital Tracs Message off the wire: 82 bytes from at, returning where the next byte lies */
static size_t decode_catalog_sent_for_instruments_belonging_to_capital_tracs_message(CatalogSentForInstrumentsBelongingToCapitalTracsMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->number_of_the_trac[i] = wire[at++]; }
  record->origin = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->name_of_the_trac[i] = wire[at++]; }
  for (size_t i = 0; i < 7; i++) { record->underlying_issuing_company[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->underlying_series[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->securities[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->excluded_securities[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->component_in_cash[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->excluded_value[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->number_of_certificates[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->theoretical_price[i] = wire[at++]; }

  return at;
}

/* what was read of Catalog Sent For Instruments Belonging To Capital Tracs Message is what was written, byte for byte */
static void equal_catalog_sent_for_instruments_belonging_to_capital_tracs_message(const CatalogSentForInstrumentsBelongingToCapitalTracsMessage *read, const CatalogSentForInstrumentsBelongingToCapitalTracsMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->number_of_the_trac[i] == written->number_of_the_trac[i]); }
  assert(read->origin == written->origin);
  for (size_t i = 0; i < 8; i++) { assert(read->name_of_the_trac[i] == written->name_of_the_trac[i]); }
  for (size_t i = 0; i < 7; i++) { assert(read->underlying_issuing_company[i] == written->underlying_issuing_company[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->underlying_series[i] == written->underlying_series[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->securities[i] == written->securities[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->excluded_securities[i] == written->excluded_securities[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->price[i] == written->price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->component_in_cash[i] == written->component_in_cash[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->excluded_value[i] == written->excluded_value[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->number_of_certificates[i] == written->number_of_certificates[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->theoretical_price[i] == written->theoretical_price[i]); }
}

/* Catalog Sent For Instruments Belonging To Capital Tracs Message: written and read back, then read and written back */
static void check_catalog_sent_for_instruments_belonging_to_capital_tracs_message(void) {
  CatalogSentForInstrumentsBelongingToCapitalTracsMessage sent;
  CatalogSentForInstrumentsBelongingToCapitalTracsMessage got;
  uint8_t wire[82];
  uint8_t again[82];

  any_catalog_sent_for_instruments_belonging_to_capital_tracs_message(&sent);
  assert(encode_catalog_sent_for_instruments_belonging_to_capital_tracs_message(&sent, wire, 0) == 82);
  assert(decode_catalog_sent_for_instruments_belonging_to_capital_tracs_message(&got, wire, 0) == 82);
  equal_catalog_sent_for_instruments_belonging_to_capital_tracs_message(&got, &sent);

  for (size_t i = 0; i < 82; i++) { wire[i] = arbitrary(); }
  assert(decode_catalog_sent_for_instruments_belonging_to_capital_tracs_message(&got, wire, 0) == 82);
  assert(encode_catalog_sent_for_instruments_belonging_to_capital_tracs_message(&got, again, 0) == 82);
  for (size_t i = 0; i < 82; i++) { assert(again[i] == wire[i]); }
}

/* ---- Consolidated Inav Message: 13 bytes ------------------------------------- */

/* Disclosure of the TRACS during the trading hours of the ongoing market. */
typedef struct {
  uint8_t number_of_the_trac[4];         /* bytes 0 to 3 */
  uint8_t origin;                        /* byte 4 */
  uint8_t current_theoretical_price[8];  /* bytes 5 to 12 */
} ConsolidatedInavMessage;

/* any Consolidated Inav Message at all: every byte one the checker chooses */
static void any_consolidated_inav_message(ConsolidatedInavMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->number_of_the_trac[i] = arbitrary(); }
  record->origin = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->current_theoretical_price[i] = arbitrary(); }
}

/* Consolidated Inav Message to the wire: 13 bytes from at, returning where the next byte goes */
static size_t encode_consolidated_inav_message(const ConsolidatedInavMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->number_of_the_trac[i]; }
  wire[at++] = record->origin;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->current_theoretical_price[i]; }

  return at;
}

/* Consolidated Inav Message off the wire: 13 bytes from at, returning where the next byte lies */
static size_t decode_consolidated_inav_message(ConsolidatedInavMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->number_of_the_trac[i] = wire[at++]; }
  record->origin = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->current_theoretical_price[i] = wire[at++]; }

  return at;
}

/* what was read of Consolidated Inav Message is what was written, byte for byte */
static void equal_consolidated_inav_message(const ConsolidatedInavMessage *read, const ConsolidatedInavMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->number_of_the_trac[i] == written->number_of_the_trac[i]); }
  assert(read->origin == written->origin);
  for (size_t i = 0; i < 8; i++) { assert(read->current_theoretical_price[i] == written->current_theoretical_price[i]); }
}

/* Consolidated Inav Message: written and read back, then read and written back */
static void check_consolidated_inav_message(void) {
  ConsolidatedInavMessage sent;
  ConsolidatedInavMessage got;
  uint8_t wire[13];
  uint8_t again[13];

  any_consolidated_inav_message(&sent);
  assert(encode_consolidated_inav_message(&sent, wire, 0) == 13);
  assert(decode_consolidated_inav_message(&got, wire, 0) == 13);
  equal_consolidated_inav_message(&got, &sent);

  for (size_t i = 0; i < 13; i++) { wire[i] = arbitrary(); }
  assert(decode_consolidated_inav_message(&got, wire, 0) == 13);
  assert(encode_consolidated_inav_message(&got, again, 0) == 13);
  for (size_t i = 0; i < 13; i++) { assert(again[i] == wire[i]); }
}

/* ---- Catalog For Instruments Belonging To The Local And Global Stock Market Message: 73 bytes ---- */

/* Catalog of instruments from the local and global stock markets. */
typedef struct {
  uint8_t mse_instrument_number[4];       /* bytes 0 to 3 */
  uint8_t value_of_type[2];               /* bytes 4 to 5 */
  uint8_t issuing_company[7];             /* bytes 6 to 12 */
  uint8_t series[6];                      /* bytes 13 to 18 */
  uint8_t last_price[8];                  /* bytes 19 to 26 */
  uint8_t ppp_weighted_average_price[8];  /* bytes 27 to 34 */
  uint8_t reference_date[8];              /* bytes 35 to 42 */
  uint8_t reference;                      /* byte 43 */
  uint8_t coupon_in_effect[2];            /* bytes 44 to 45 */
  uint8_t marketability;                  /* byte 46 */
  uint8_t numerical_marketability[4];     /* bytes 47 to 50 */
  uint8_t isin[12];                       /* bytes 51 to 62 */
  uint8_t market;                         /* byte 63 */
  uint8_t registered_values[8];           /* bytes 64 to 71 */
  uint8_t exchange;                       /* byte 72 */
} CatalogForInstrumentsBelongingToTheLocalAndGlobalStockMar_gc6yau;

/* any Catalog For Instruments Belonging To The Local And Global Stock Market Message at all: every byte one the checker chooses */
static void any_catalog_for_instruments_belonging_to_the_local_and_global_stock_mar_gc6yau(CatalogForInstrumentsBelongingToTheLocalAndGlobalStockMar_gc6yau *record) {
  for (size_t i = 0; i < 4; i++) { record->mse_instrument_number[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->value_of_type[i] = arbitrary(); }
  for (size_t i = 0; i < 7; i++) { record->issuing_company[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->series[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->last_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->ppp_weighted_average_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->reference_date[i] = arbitrary(); }
  record->reference = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->coupon_in_effect[i] = arbitrary(); }
  record->marketability = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->numerical_marketability[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->isin[i] = arbitrary(); }
  record->market = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->registered_values[i] = arbitrary(); }
  record->exchange = arbitrary();
}

/* Catalog For Instruments Belonging To The Local And Global Stock Market Message to the wire: 73 bytes from at, returning where the next byte goes */
static size_t encode_catalog_for_instruments_belonging_to_the_local_and_global_stock_mar_gc6yau(const CatalogForInstrumentsBelongingToTheLocalAndGlobalStockMar_gc6yau *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->mse_instrument_number[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->value_of_type[i]; }
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->issuing_company[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->series[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->last_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->ppp_weighted_average_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->reference_date[i]; }
  wire[at++] = record->reference;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->coupon_in_effect[i]; }
  wire[at++] = record->marketability;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->numerical_marketability[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->isin[i]; }
  wire[at++] = record->market;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->registered_values[i]; }
  wire[at++] = record->exchange;

  return at;
}

/* Catalog For Instruments Belonging To The Local And Global Stock Market Message off the wire: 73 bytes from at, returning where the next byte lies */
static size_t decode_catalog_for_instruments_belonging_to_the_local_and_global_stock_mar_gc6yau(CatalogForInstrumentsBelongingToTheLocalAndGlobalStockMar_gc6yau *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->mse_instrument_number[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->value_of_type[i] = wire[at++]; }
  for (size_t i = 0; i < 7; i++) { record->issuing_company[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->series[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->last_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->ppp_weighted_average_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->reference_date[i] = wire[at++]; }
  record->reference = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->coupon_in_effect[i] = wire[at++]; }
  record->marketability = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->numerical_marketability[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->isin[i] = wire[at++]; }
  record->market = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->registered_values[i] = wire[at++]; }
  record->exchange = wire[at++];

  return at;
}

/* what was read of Catalog For Instruments Belonging To The Local And Global Stock Market Message is what was written, byte for byte */
static void equal_catalog_for_instruments_belonging_to_the_local_and_global_stock_mar_gc6yau(const CatalogForInstrumentsBelongingToTheLocalAndGlobalStockMar_gc6yau *read, const CatalogForInstrumentsBelongingToTheLocalAndGlobalStockMar_gc6yau *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->mse_instrument_number[i] == written->mse_instrument_number[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->value_of_type[i] == written->value_of_type[i]); }
  for (size_t i = 0; i < 7; i++) { assert(read->issuing_company[i] == written->issuing_company[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->series[i] == written->series[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->last_price[i] == written->last_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->ppp_weighted_average_price[i] == written->ppp_weighted_average_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->reference_date[i] == written->reference_date[i]); }
  assert(read->reference == written->reference);
  for (size_t i = 0; i < 2; i++) { assert(read->coupon_in_effect[i] == written->coupon_in_effect[i]); }
  assert(read->marketability == written->marketability);
  for (size_t i = 0; i < 4; i++) { assert(read->numerical_marketability[i] == written->numerical_marketability[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->isin[i] == written->isin[i]); }
  assert(read->market == written->market);
  for (size_t i = 0; i < 8; i++) { assert(read->registered_values[i] == written->registered_values[i]); }
  assert(read->exchange == written->exchange);
}

/* Catalog For Instruments Belonging To The Local And Global Stock Market Message: written and read back, then read and written back */
static void check_catalog_for_instruments_belonging_to_the_local_and_global_stock_mar_gc6yau(void) {
  CatalogForInstrumentsBelongingToTheLocalAndGlobalStockMar_gc6yau sent;
  CatalogForInstrumentsBelongingToTheLocalAndGlobalStockMar_gc6yau got;
  uint8_t wire[73];
  uint8_t again[73];

  any_catalog_for_instruments_belonging_to_the_local_and_global_stock_mar_gc6yau(&sent);
  assert(encode_catalog_for_instruments_belonging_to_the_local_and_global_stock_mar_gc6yau(&sent, wire, 0) == 73);
  assert(decode_catalog_for_instruments_belonging_to_the_local_and_global_stock_mar_gc6yau(&got, wire, 0) == 73);
  equal_catalog_for_instruments_belonging_to_the_local_and_global_stock_mar_gc6yau(&got, &sent);

  for (size_t i = 0; i < 73; i++) { wire[i] = arbitrary(); }
  assert(decode_catalog_for_instruments_belonging_to_the_local_and_global_stock_mar_gc6yau(&got, wire, 0) == 73);
  assert(encode_catalog_for_instruments_belonging_to_the_local_and_global_stock_mar_gc6yau(&got, again, 0) == 73);
  for (size_t i = 0; i < 73; i++) { assert(again[i] == wire[i]); }
}

/* ---- Probable Price Of Allocation Message: 21 bytes -------------------------- */

/* The message is sent during any type of bidding (Opening, Ongoing, Volatility and Intraday) and only in the instruments where there already is a virtual term matching or pre-allotment. */
typedef struct {
  uint8_t instrument_number[4];             /* bytes 0 to 3 */
  uint8_t origin;                           /* byte 4 */
  uint8_t probable_price_of_allocation[8];  /* bytes 5 to 12 */
  uint8_t volume_int_648[8];                /* bytes 13 to 20 */
} ProbablePriceOfAllocationMessage;

/* any Probable Price Of Allocation Message at all: every byte one the checker chooses */
static void any_probable_price_of_allocation_message(ProbablePriceOfAllocationMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->instrument_number[i] = arbitrary(); }
  record->origin = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->probable_price_of_allocation[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->volume_int_648[i] = arbitrary(); }
}

/* Probable Price Of Allocation Message to the wire: 21 bytes from at, returning where the next byte goes */
static size_t encode_probable_price_of_allocation_message(const ProbablePriceOfAllocationMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument_number[i]; }
  wire[at++] = record->origin;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->probable_price_of_allocation[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->volume_int_648[i]; }

  return at;
}

/* Probable Price Of Allocation Message off the wire: 21 bytes from at, returning where the next byte lies */
static size_t decode_probable_price_of_allocation_message(ProbablePriceOfAllocationMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->instrument_number[i] = wire[at++]; }
  record->origin = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->probable_price_of_allocation[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->volume_int_648[i] = wire[at++]; }

  return at;
}

/* what was read of Probable Price Of Allocation Message is what was written, byte for byte */
static void equal_probable_price_of_allocation_message(const ProbablePriceOfAllocationMessage *read, const ProbablePriceOfAllocationMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->instrument_number[i] == written->instrument_number[i]); }
  assert(read->origin == written->origin);
  for (size_t i = 0; i < 8; i++) { assert(read->probable_price_of_allocation[i] == written->probable_price_of_allocation[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->volume_int_648[i] == written->volume_int_648[i]); }
}

/* Probable Price Of Allocation Message: written and read back, then read and written back */
static void check_probable_price_of_allocation_message(void) {
  ProbablePriceOfAllocationMessage sent;
  ProbablePriceOfAllocationMessage got;
  uint8_t wire[21];
  uint8_t again[21];

  any_probable_price_of_allocation_message(&sent);
  assert(encode_probable_price_of_allocation_message(&sent, wire, 0) == 21);
  assert(decode_probable_price_of_allocation_message(&got, wire, 0) == 21);
  equal_probable_price_of_allocation_message(&got, &sent);

  for (size_t i = 0; i < 21; i++) { wire[i] = arbitrary(); }
  assert(decode_probable_price_of_allocation_message(&got, wire, 0) == 21);
  assert(encode_probable_price_of_allocation_message(&got, again, 0) == 21);
  for (size_t i = 0; i < 21; i++) { assert(again[i] == wire[i]); }
}

/* ---- Relation Between Bmvbiva Instruments Message: 9 bytes ------------------- */

/* Relation between identifiers of instruments between BIVA and BMV. */
typedef struct {
  uint8_t number_of_the_bmv_instrument[4];  /* bytes 0 to 3 */
  uint8_t biva_instrument[4];               /* bytes 4 to 7 */
  uint8_t type_of_trading;                  /* byte 8 */
} RelationBetweenBmvbivaInstrumentsMessage;

/* any Relation Between Bmvbiva Instruments Message at all: every byte one the checker chooses */
static void any_relation_between_bmvbiva_instruments_message(RelationBetweenBmvbivaInstrumentsMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->number_of_the_bmv_instrument[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->biva_instrument[i] = arbitrary(); }
  record->type_of_trading = arbitrary();
}

/* Relation Between Bmvbiva Instruments Message to the wire: 9 bytes from at, returning where the next byte goes */
static size_t encode_relation_between_bmvbiva_instruments_message(const RelationBetweenBmvbivaInstrumentsMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->number_of_the_bmv_instrument[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->biva_instrument[i]; }
  wire[at++] = record->type_of_trading;

  return at;
}

/* Relation Between Bmvbiva Instruments Message off the wire: 9 bytes from at, returning where the next byte lies */
static size_t decode_relation_between_bmvbiva_instruments_message(RelationBetweenBmvbivaInstrumentsMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->number_of_the_bmv_instrument[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->biva_instrument[i] = wire[at++]; }
  record->type_of_trading = wire[at++];

  return at;
}

/* what was read of Relation Between Bmvbiva Instruments Message is what was written, byte for byte */
static void equal_relation_between_bmvbiva_instruments_message(const RelationBetweenBmvbivaInstrumentsMessage *read, const RelationBetweenBmvbivaInstrumentsMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->number_of_the_bmv_instrument[i] == written->number_of_the_bmv_instrument[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->biva_instrument[i] == written->biva_instrument[i]); }
  assert(read->type_of_trading == written->type_of_trading);
}

/* Relation Between Bmvbiva Instruments Message: written and read back, then read and written back */
static void check_relation_between_bmvbiva_instruments_message(void) {
  RelationBetweenBmvbivaInstrumentsMessage sent;
  RelationBetweenBmvbivaInstrumentsMessage got;
  uint8_t wire[9];
  uint8_t again[9];

  any_relation_between_bmvbiva_instruments_message(&sent);
  assert(encode_relation_between_bmvbiva_instruments_message(&sent, wire, 0) == 9);
  assert(decode_relation_between_bmvbiva_instruments_message(&got, wire, 0) == 9);
  equal_relation_between_bmvbiva_instruments_message(&got, &sent);

  for (size_t i = 0; i < 9; i++) { wire[i] = arbitrary(); }
  assert(decode_relation_between_bmvbiva_instruments_message(&got, wire, 0) == 9);
  assert(encode_relation_between_bmvbiva_instruments_message(&got, again, 0) == 9);
  for (size_t i = 0; i < 9; i++) { assert(again[i] == wire[i]); }
}

/* ---- Equities Market Trades Message: 61 bytes -------------------------------- */

/* Informs about any transaction which was accepted at the BMV or BIVA. */
typedef struct {
  uint8_t instrument_number[4];                /* bytes 0 to 3 */
  uint8_t origin;                              /* byte 4 */
  uint8_t time_of_the_trade[8];                /* bytes 5 to 12 */
  uint8_t volume_int_648[8];                   /* bytes 13 to 20 */
  uint8_t price[8];                            /* bytes 21 to 28 */
  uint8_t type_of_agreement;                   /* byte 29 */
  uint8_t consecutive_number_of_the_trade[8];  /* bytes 30 to 37 */
  uint8_t sets_price;                          /* byte 38 */
  uint8_t type_of_trading;                     /* byte 39 */
  uint8_t amount[8];                           /* bytes 40 to 47 */
  uint8_t purchases[5];                        /* bytes 48 to 52 */
  uint8_t sells[5];                            /* bytes 53 to 57 */
  uint8_t settlement;                          /* byte 58 */
  uint8_t auction_indicator;                   /* byte 59 */
  uint8_t indicator;                           /* byte 60 */
} EquitiesMarketTradesMessage;

/* any Equities Market Trades Message at all: every byte one the checker chooses */
static void any_equities_market_trades_message(EquitiesMarketTradesMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->instrument_number[i] = arbitrary(); }
  record->origin = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->time_of_the_trade[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->volume_int_648[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->price[i] = arbitrary(); }
  record->type_of_agreement = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->consecutive_number_of_the_trade[i] = arbitrary(); }
  record->sets_price = arbitrary();
  record->type_of_trading = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->amount[i] = arbitrary(); }
  for (size_t i = 0; i < 5; i++) { record->purchases[i] = arbitrary(); }
  for (size_t i = 0; i < 5; i++) { record->sells[i] = arbitrary(); }
  record->settlement = arbitrary();
  record->auction_indicator = arbitrary();
  record->indicator = arbitrary();
}

/* Equities Market Trades Message to the wire: 61 bytes from at, returning where the next byte goes */
static size_t encode_equities_market_trades_message(const EquitiesMarketTradesMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument_number[i]; }
  wire[at++] = record->origin;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->time_of_the_trade[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->volume_int_648[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price[i]; }
  wire[at++] = record->type_of_agreement;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->consecutive_number_of_the_trade[i]; }
  wire[at++] = record->sets_price;
  wire[at++] = record->type_of_trading;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->amount[i]; }
  for (size_t i = 0; i < 5; i++) { wire[at++] = record->purchases[i]; }
  for (size_t i = 0; i < 5; i++) { wire[at++] = record->sells[i]; }
  wire[at++] = record->settlement;
  wire[at++] = record->auction_indicator;
  wire[at++] = record->indicator;

  return at;
}

/* Equities Market Trades Message off the wire: 61 bytes from at, returning where the next byte lies */
static size_t decode_equities_market_trades_message(EquitiesMarketTradesMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->instrument_number[i] = wire[at++]; }
  record->origin = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->time_of_the_trade[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->volume_int_648[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->price[i] = wire[at++]; }
  record->type_of_agreement = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->consecutive_number_of_the_trade[i] = wire[at++]; }
  record->sets_price = wire[at++];
  record->type_of_trading = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->amount[i] = wire[at++]; }
  for (size_t i = 0; i < 5; i++) { record->purchases[i] = wire[at++]; }
  for (size_t i = 0; i < 5; i++) { record->sells[i] = wire[at++]; }
  record->settlement = wire[at++];
  record->auction_indicator = wire[at++];
  record->indicator = wire[at++];

  return at;
}

/* what was read of Equities Market Trades Message is what was written, byte for byte */
static void equal_equities_market_trades_message(const EquitiesMarketTradesMessage *read, const EquitiesMarketTradesMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->instrument_number[i] == written->instrument_number[i]); }
  assert(read->origin == written->origin);
  for (size_t i = 0; i < 8; i++) { assert(read->time_of_the_trade[i] == written->time_of_the_trade[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->volume_int_648[i] == written->volume_int_648[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->price[i] == written->price[i]); }
  assert(read->type_of_agreement == written->type_of_agreement);
  for (size_t i = 0; i < 8; i++) { assert(read->consecutive_number_of_the_trade[i] == written->consecutive_number_of_the_trade[i]); }
  assert(read->sets_price == written->sets_price);
  assert(read->type_of_trading == written->type_of_trading);
  for (size_t i = 0; i < 8; i++) { assert(read->amount[i] == written->amount[i]); }
  for (size_t i = 0; i < 5; i++) { assert(read->purchases[i] == written->purchases[i]); }
  for (size_t i = 0; i < 5; i++) { assert(read->sells[i] == written->sells[i]); }
  assert(read->settlement == written->settlement);
  assert(read->auction_indicator == written->auction_indicator);
  assert(read->indicator == written->indicator);
}

/* Equities Market Trades Message: written and read back, then read and written back */
static void check_equities_market_trades_message(void) {
  EquitiesMarketTradesMessage sent;
  EquitiesMarketTradesMessage got;
  uint8_t wire[61];
  uint8_t again[61];

  any_equities_market_trades_message(&sent);
  assert(encode_equities_market_trades_message(&sent, wire, 0) == 61);
  assert(decode_equities_market_trades_message(&got, wire, 0) == 61);
  equal_equities_market_trades_message(&got, &sent);

  for (size_t i = 0; i < 61; i++) { wire[i] = arbitrary(); }
  assert(decode_equities_market_trades_message(&got, wire, 0) == 61);
  assert(encode_equities_market_trades_message(&got, again, 0) == 61);
  for (size_t i = 0; i < 61; i++) { assert(again[i] == wire[i]); }
}

/* ---- Consolidated Trade Cancellation Message: 13 bytes ----------------------- */

/* This message in sent when a transaction is cancelled from BMV or BIVA system. */
typedef struct {
  uint8_t instrument_number[4];                /* bytes 0 to 3 */
  uint8_t origin;                              /* byte 4 */
  uint8_t consecutive_number_of_the_trade[8];  /* bytes 5 to 12 */
} ConsolidatedTradeCancellationMessage;

/* any Consolidated Trade Cancellation Message at all: every byte one the checker chooses */
static void any_consolidated_trade_cancellation_message(ConsolidatedTradeCancellationMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->instrument_number[i] = arbitrary(); }
  record->origin = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->consecutive_number_of_the_trade[i] = arbitrary(); }
}

/* Consolidated Trade Cancellation Message to the wire: 13 bytes from at, returning where the next byte goes */
static size_t encode_consolidated_trade_cancellation_message(const ConsolidatedTradeCancellationMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument_number[i]; }
  wire[at++] = record->origin;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->consecutive_number_of_the_trade[i]; }

  return at;
}

/* Consolidated Trade Cancellation Message off the wire: 13 bytes from at, returning where the next byte lies */
static size_t decode_consolidated_trade_cancellation_message(ConsolidatedTradeCancellationMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->instrument_number[i] = wire[at++]; }
  record->origin = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->consecutive_number_of_the_trade[i] = wire[at++]; }

  return at;
}

/* what was read of Consolidated Trade Cancellation Message is what was written, byte for byte */
static void equal_consolidated_trade_cancellation_message(const ConsolidatedTradeCancellationMessage *read, const ConsolidatedTradeCancellationMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->instrument_number[i] == written->instrument_number[i]); }
  assert(read->origin == written->origin);
  for (size_t i = 0; i < 8; i++) { assert(read->consecutive_number_of_the_trade[i] == written->consecutive_number_of_the_trade[i]); }
}

/* Consolidated Trade Cancellation Message: written and read back, then read and written back */
static void check_consolidated_trade_cancellation_message(void) {
  ConsolidatedTradeCancellationMessage sent;
  ConsolidatedTradeCancellationMessage got;
  uint8_t wire[13];
  uint8_t again[13];

  any_consolidated_trade_cancellation_message(&sent);
  assert(encode_consolidated_trade_cancellation_message(&sent, wire, 0) == 13);
  assert(decode_consolidated_trade_cancellation_message(&got, wire, 0) == 13);
  equal_consolidated_trade_cancellation_message(&got, &sent);

  for (size_t i = 0; i < 13; i++) { wire[i] = arbitrary(); }
  assert(decode_consolidated_trade_cancellation_message(&got, wire, 0) == 13);
  assert(encode_consolidated_trade_cancellation_message(&got, again, 0) == 13);
  for (size_t i = 0; i < 13; i++) { assert(again[i] == wire[i]); }
}

/* ---- Pricevolume Indicator Message: 38 bytes --------------------------------- */

/* Price/volume indicator for the messages coming from BIVA. */
typedef struct {
  uint8_t instrument_number[4];            /* bytes 0 to 3 */
  uint8_t origin;                          /* byte 4 */
  uint8_t probable_price_of_allotment[8];  /* bytes 5 to 12 */
  uint8_t volume_int_648[8];               /* bytes 13 to 20 */
  uint8_t best_selling_price[8];           /* bytes 21 to 28 */
  uint8_t best_purchasing_price[8];        /* bytes 29 to 36 */
  uint8_t type_of_cross_trading;           /* byte 37 */
} PricevolumeIndicatorMessage;

/* any Pricevolume Indicator Message at all: every byte one the checker chooses */
static void any_pricevolume_indicator_message(PricevolumeIndicatorMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->instrument_number[i] = arbitrary(); }
  record->origin = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->probable_price_of_allotment[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->volume_int_648[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->best_selling_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->best_purchasing_price[i] = arbitrary(); }
  record->type_of_cross_trading = arbitrary();
}

/* Pricevolume Indicator Message to the wire: 38 bytes from at, returning where the next byte goes */
static size_t encode_pricevolume_indicator_message(const PricevolumeIndicatorMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument_number[i]; }
  wire[at++] = record->origin;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->probable_price_of_allotment[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->volume_int_648[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->best_selling_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->best_purchasing_price[i]; }
  wire[at++] = record->type_of_cross_trading;

  return at;
}

/* Pricevolume Indicator Message off the wire: 38 bytes from at, returning where the next byte lies */
static size_t decode_pricevolume_indicator_message(PricevolumeIndicatorMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->instrument_number[i] = wire[at++]; }
  record->origin = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->probable_price_of_allotment[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->volume_int_648[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->best_selling_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->best_purchasing_price[i] = wire[at++]; }
  record->type_of_cross_trading = wire[at++];

  return at;
}

/* what was read of Pricevolume Indicator Message is what was written, byte for byte */
static void equal_pricevolume_indicator_message(const PricevolumeIndicatorMessage *read, const PricevolumeIndicatorMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->instrument_number[i] == written->instrument_number[i]); }
  assert(read->origin == written->origin);
  for (size_t i = 0; i < 8; i++) { assert(read->probable_price_of_allotment[i] == written->probable_price_of_allotment[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->volume_int_648[i] == written->volume_int_648[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->best_selling_price[i] == written->best_selling_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->best_purchasing_price[i] == written->best_purchasing_price[i]); }
  assert(read->type_of_cross_trading == written->type_of_cross_trading);
}

/* Pricevolume Indicator Message: written and read back, then read and written back */
static void check_pricevolume_indicator_message(void) {
  PricevolumeIndicatorMessage sent;
  PricevolumeIndicatorMessage got;
  uint8_t wire[38];
  uint8_t again[38];

  any_pricevolume_indicator_message(&sent);
  assert(encode_pricevolume_indicator_message(&sent, wire, 0) == 38);
  assert(decode_pricevolume_indicator_message(&got, wire, 0) == 38);
  equal_pricevolume_indicator_message(&got, &sent);

  for (size_t i = 0; i < 38; i++) { wire[i] = arbitrary(); }
  assert(decode_pricevolume_indicator_message(&got, wire, 0) == 38);
  assert(encode_pricevolume_indicator_message(&got, again, 0) == 38);
  for (size_t i = 0; i < 38; i++) { assert(again[i] == wire[i]); }
}

/* ---- Consolidated Execution Of Orders Message: 52 bytes ---------------------- */

/* The message is published when there is a term matching or closing in the electronic system of the BMV or BIVA. */
typedef struct {
  uint8_t instrument_number[4];                /* bytes 0 to 3 */
  uint8_t origin;                              /* byte 4 */
  uint8_t date[8];                             /* bytes 5 to 12 */
  uint8_t consecutive_number[8];               /* bytes 13 to 20 */
  uint8_t volume_int_648[8];                   /* bytes 21 to 28 */
  uint8_t consecutive_number_of_the_trade[8];  /* bytes 29 to 36 */
  uint8_t execution_price[8];                  /* bytes 37 to 44 */
  uint8_t indicator;                           /* byte 45 */
  uint8_t sets_price;                          /* byte 46 */
  uint8_t participant[5];                      /* bytes 47 to 51 */
} ConsolidatedExecutionOfOrdersMessage;

/* any Consolidated Execution Of Orders Message at all: every byte one the checker chooses */
static void any_consolidated_execution_of_orders_message(ConsolidatedExecutionOfOrdersMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->instrument_number[i] = arbitrary(); }
  record->origin = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->date[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->consecutive_number[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->volume_int_648[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->consecutive_number_of_the_trade[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->execution_price[i] = arbitrary(); }
  record->indicator = arbitrary();
  record->sets_price = arbitrary();
  for (size_t i = 0; i < 5; i++) { record->participant[i] = arbitrary(); }
}

/* Consolidated Execution Of Orders Message to the wire: 52 bytes from at, returning where the next byte goes */
static size_t encode_consolidated_execution_of_orders_message(const ConsolidatedExecutionOfOrdersMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument_number[i]; }
  wire[at++] = record->origin;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->date[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->consecutive_number[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->volume_int_648[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->consecutive_number_of_the_trade[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->execution_price[i]; }
  wire[at++] = record->indicator;
  wire[at++] = record->sets_price;
  for (size_t i = 0; i < 5; i++) { wire[at++] = record->participant[i]; }

  return at;
}

/* Consolidated Execution Of Orders Message off the wire: 52 bytes from at, returning where the next byte lies */
static size_t decode_consolidated_execution_of_orders_message(ConsolidatedExecutionOfOrdersMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->instrument_number[i] = wire[at++]; }
  record->origin = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->date[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->consecutive_number[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->volume_int_648[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->consecutive_number_of_the_trade[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->execution_price[i] = wire[at++]; }
  record->indicator = wire[at++];
  record->sets_price = wire[at++];
  for (size_t i = 0; i < 5; i++) { record->participant[i] = wire[at++]; }

  return at;
}

/* what was read of Consolidated Execution Of Orders Message is what was written, byte for byte */
static void equal_consolidated_execution_of_orders_message(const ConsolidatedExecutionOfOrdersMessage *read, const ConsolidatedExecutionOfOrdersMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->instrument_number[i] == written->instrument_number[i]); }
  assert(read->origin == written->origin);
  for (size_t i = 0; i < 8; i++) { assert(read->date[i] == written->date[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->consecutive_number[i] == written->consecutive_number[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->volume_int_648[i] == written->volume_int_648[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->consecutive_number_of_the_trade[i] == written->consecutive_number_of_the_trade[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->execution_price[i] == written->execution_price[i]); }
  assert(read->indicator == written->indicator);
  assert(read->sets_price == written->sets_price);
  for (size_t i = 0; i < 5; i++) { assert(read->participant[i] == written->participant[i]); }
}

/* Consolidated Execution Of Orders Message: written and read back, then read and written back */
static void check_consolidated_execution_of_orders_message(void) {
  ConsolidatedExecutionOfOrdersMessage sent;
  ConsolidatedExecutionOfOrdersMessage got;
  uint8_t wire[52];
  uint8_t again[52];

  any_consolidated_execution_of_orders_message(&sent);
  assert(encode_consolidated_execution_of_orders_message(&sent, wire, 0) == 52);
  assert(decode_consolidated_execution_of_orders_message(&got, wire, 0) == 52);
  equal_consolidated_execution_of_orders_message(&got, &sent);

  for (size_t i = 0; i < 52; i++) { wire[i] = arbitrary(); }
  assert(decode_consolidated_execution_of_orders_message(&got, wire, 0) == 52);
  assert(encode_consolidated_execution_of_orders_message(&got, again, 0) == 52);
  for (size_t i = 0; i < 52; i++) { assert(again[i] == wire[i]); }
}

/* ---- Registration Of Order Message: 43 bytes --------------------------------- */

/* When the order is accepted by the central system of the BMV or BIVA, this message is sent to the appropriate media. */
typedef struct {
  uint8_t instrument_number[4];   /* bytes 0 to 3 */
  uint8_t origin;                 /* byte 4 */
  uint8_t date_and_time[8];       /* bytes 5 to 12 */
  uint8_t consecutive_number[8];  /* bytes 13 to 20 */
  uint8_t direction;              /* byte 21 */
  uint8_t volume_int_648[8];      /* bytes 22 to 29 */
  uint8_t price[8];               /* bytes 30 to 37 */
  uint8_t participant[5];         /* bytes 38 to 42 */
} RegistrationOfOrderMessage;

/* any Registration Of Order Message at all: every byte one the checker chooses */
static void any_registration_of_order_message(RegistrationOfOrderMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->instrument_number[i] = arbitrary(); }
  record->origin = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->date_and_time[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->consecutive_number[i] = arbitrary(); }
  record->direction = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->volume_int_648[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->price[i] = arbitrary(); }
  for (size_t i = 0; i < 5; i++) { record->participant[i] = arbitrary(); }
}

/* Registration Of Order Message to the wire: 43 bytes from at, returning where the next byte goes */
static size_t encode_registration_of_order_message(const RegistrationOfOrderMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument_number[i]; }
  wire[at++] = record->origin;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->date_and_time[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->consecutive_number[i]; }
  wire[at++] = record->direction;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->volume_int_648[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price[i]; }
  for (size_t i = 0; i < 5; i++) { wire[at++] = record->participant[i]; }

  return at;
}

/* Registration Of Order Message off the wire: 43 bytes from at, returning where the next byte lies */
static size_t decode_registration_of_order_message(RegistrationOfOrderMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->instrument_number[i] = wire[at++]; }
  record->origin = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->date_and_time[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->consecutive_number[i] = wire[at++]; }
  record->direction = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->volume_int_648[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->price[i] = wire[at++]; }
  for (size_t i = 0; i < 5; i++) { record->participant[i] = wire[at++]; }

  return at;
}

/* what was read of Registration Of Order Message is what was written, byte for byte */
static void equal_registration_of_order_message(const RegistrationOfOrderMessage *read, const RegistrationOfOrderMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->instrument_number[i] == written->instrument_number[i]); }
  assert(read->origin == written->origin);
  for (size_t i = 0; i < 8; i++) { assert(read->date_and_time[i] == written->date_and_time[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->consecutive_number[i] == written->consecutive_number[i]); }
  assert(read->direction == written->direction);
  for (size_t i = 0; i < 8; i++) { assert(read->volume_int_648[i] == written->volume_int_648[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->price[i] == written->price[i]); }
  for (size_t i = 0; i < 5; i++) { assert(read->participant[i] == written->participant[i]); }
}

/* Registration Of Order Message: written and read back, then read and written back */
static void check_registration_of_order_message(void) {
  RegistrationOfOrderMessage sent;
  RegistrationOfOrderMessage got;
  uint8_t wire[43];
  uint8_t again[43];

  any_registration_of_order_message(&sent);
  assert(encode_registration_of_order_message(&sent, wire, 0) == 43);
  assert(decode_registration_of_order_message(&got, wire, 0) == 43);
  equal_registration_of_order_message(&got, &sent);

  for (size_t i = 0; i < 43; i++) { wire[i] = arbitrary(); }
  assert(decode_registration_of_order_message(&got, wire, 0) == 43);
  assert(encode_registration_of_order_message(&got, again, 0) == 43);
  for (size_t i = 0; i < 43; i++) { assert(again[i] == wire[i]); }
}

/* ---- Cancellations Of Orders Message: 21 bytes ------------------------------- */

/* This message deletes the trading floor order. */
typedef struct {
  uint8_t instrument_number[4];   /* bytes 0 to 3 */
  uint8_t origin;                 /* byte 4 */
  uint8_t date[8];                /* bytes 5 to 12 */
  uint8_t consecutive_number[8];  /* bytes 13 to 20 */
} CancellationsOfOrdersMessage;

/* any Cancellations Of Orders Message at all: every byte one the checker chooses */
static void any_cancellations_of_orders_message(CancellationsOfOrdersMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->instrument_number[i] = arbitrary(); }
  record->origin = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->date[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->consecutive_number[i] = arbitrary(); }
}

/* Cancellations Of Orders Message to the wire: 21 bytes from at, returning where the next byte goes */
static size_t encode_cancellations_of_orders_message(const CancellationsOfOrdersMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument_number[i]; }
  wire[at++] = record->origin;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->date[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->consecutive_number[i]; }

  return at;
}

/* Cancellations Of Orders Message off the wire: 21 bytes from at, returning where the next byte lies */
static size_t decode_cancellations_of_orders_message(CancellationsOfOrdersMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->instrument_number[i] = wire[at++]; }
  record->origin = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->date[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->consecutive_number[i] = wire[at++]; }

  return at;
}

/* what was read of Cancellations Of Orders Message is what was written, byte for byte */
static void equal_cancellations_of_orders_message(const CancellationsOfOrdersMessage *read, const CancellationsOfOrdersMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->instrument_number[i] == written->instrument_number[i]); }
  assert(read->origin == written->origin);
  for (size_t i = 0; i < 8; i++) { assert(read->date[i] == written->date[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->consecutive_number[i] == written->consecutive_number[i]); }
}

/* Cancellations Of Orders Message: written and read back, then read and written back */
static void check_cancellations_of_orders_message(void) {
  CancellationsOfOrdersMessage sent;
  CancellationsOfOrdersMessage got;
  uint8_t wire[21];
  uint8_t again[21];

  any_cancellations_of_orders_message(&sent);
  assert(encode_cancellations_of_orders_message(&sent, wire, 0) == 21);
  assert(decode_cancellations_of_orders_message(&got, wire, 0) == 21);
  equal_cancellations_of_orders_message(&got, &sent);

  for (size_t i = 0; i < 21; i++) { wire[i] = arbitrary(); }
  assert(decode_cancellations_of_orders_message(&got, wire, 0) == 21);
  assert(encode_cancellations_of_orders_message(&got, again, 0) == 21);
  for (size_t i = 0; i < 21; i++) { assert(again[i] == wire[i]); }
}

/* ---- Last Quote Message: 23 bytes -------------------------------------------- */

/* Message sent by instrument when the best bid is modified in the electronic book by the Origin Exchange; denotes the side that is modified, the sale or the purchase. */
typedef struct {
  uint8_t instrument_number[4];  /* bytes 0 to 3 */
  uint8_t origin;                /* byte 4 */
  uint8_t volume_int_648[8];     /* bytes 5 to 12 */
  uint8_t price_rate[8];         /* bytes 13 to 20 */
  uint8_t direction_of_the_bid;  /* byte 21 */
  uint8_t type_of_trading;       /* byte 22 */
} LastQuoteMessage;

/* any Last Quote Message at all: every byte one the checker chooses */
static void any_last_quote_message(LastQuoteMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->instrument_number[i] = arbitrary(); }
  record->origin = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->volume_int_648[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->price_rate[i] = arbitrary(); }
  record->direction_of_the_bid = arbitrary();
  record->type_of_trading = arbitrary();
}

/* Last Quote Message to the wire: 23 bytes from at, returning where the next byte goes */
static size_t encode_last_quote_message(const LastQuoteMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument_number[i]; }
  wire[at++] = record->origin;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->volume_int_648[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price_rate[i]; }
  wire[at++] = record->direction_of_the_bid;
  wire[at++] = record->type_of_trading;

  return at;
}

/* Last Quote Message off the wire: 23 bytes from at, returning where the next byte lies */
static size_t decode_last_quote_message(LastQuoteMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->instrument_number[i] = wire[at++]; }
  record->origin = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->volume_int_648[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->price_rate[i] = wire[at++]; }
  record->direction_of_the_bid = wire[at++];
  record->type_of_trading = wire[at++];

  return at;
}

/* what was read of Last Quote Message is what was written, byte for byte */
static void equal_last_quote_message(const LastQuoteMessage *read, const LastQuoteMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->instrument_number[i] == written->instrument_number[i]); }
  assert(read->origin == written->origin);
  for (size_t i = 0; i < 8; i++) { assert(read->volume_int_648[i] == written->volume_int_648[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->price_rate[i] == written->price_rate[i]); }
  assert(read->direction_of_the_bid == written->direction_of_the_bid);
  assert(read->type_of_trading == written->type_of_trading);
}

/* Last Quote Message: written and read back, then read and written back */
static void check_last_quote_message(void) {
  LastQuoteMessage sent;
  LastQuoteMessage got;
  uint8_t wire[23];
  uint8_t again[23];

  any_last_quote_message(&sent);
  assert(encode_last_quote_message(&sent, wire, 0) == 23);
  assert(decode_last_quote_message(&got, wire, 0) == 23);
  equal_last_quote_message(&got, &sent);

  for (size_t i = 0; i < 23; i++) { wire[i] = arbitrary(); }
  assert(decode_last_quote_message(&got, wire, 0) == 23);
  assert(encode_last_quote_message(&got, again, 0) == 23);
  for (size_t i = 0; i < 23; i++) { assert(again[i] == wire[i]); }
}

/* ---- What esbmc checks ------------------------------------------------------- */

/* every record of the protocol, each on its own buffers */
static void checks(void) {
  check_i_n_t_r_a_multicast_header();
  check_message_header();
  check_login_response_message();
  check_replay_response_message();
  check_snapshot_response_message();
  check_snapshot_complete_message();
  check_events_system_message();
  check_trade_cancellation_message();
  check_status_changes_message();
  check_weighted_average_price_settlement_prices_message();
  check_capital_trades_message();
  check_probable_allocation_price_message();
  check_continuous_auctions_beginning_message();
  check_middle_price_existing_quotes_message();
  check_registry_operations_message();
  check_mutual_fund_trades_message();
  check_tradability_message();
  check_virtual_trades_message();
  check_order_addition_message();
  check_execution_of_orders_message();
  check_order_cancellation_message();
  check_order_change_message();
  check_best_offer_message();
  check_public_offerings_message();
  check_open_interest_message();
  check_derivatives_market_trades_message();
  check_statistics_of_instruments_message();
  check_general_indices_message();
  check_indices_components_message();
  check_inav_message();
  check_dollar_buy_sell_message();
  check_short_sales_balances_per_instrument_message();
  check_capital_market_multiples_message();
  check_benchmark_message();
  check_capitalization_rules_message();
  check_closing_price_origin_message();
  check_mutual_funds_trades_message();
  check_opening_of_continuous_auctions_message();
  check_existence_of_bids_at_mid_price_message();
  check_catalogue_of_debt_and_metals_instruments_message();
  check_catalog_sent_for_instruments_belonging_to_mutual_funds_message();
  check_weighted_average_price_message();
  check_system_events_message();
  check_reference_price_message();
  check_changes_in_status_message();
  check_catalog_for_instruments_belonging_to_the_capital_warrants_market_message();
  check_catalog_sent_for_instruments_belonging_to_capital_tracs_message();
  check_consolidated_inav_message();
  check_catalog_for_instruments_belonging_to_the_local_and_global_stock_mar_gc6yau();
  check_probable_price_of_allocation_message();
  check_relation_between_bmvbiva_instruments_message();
  check_equities_market_trades_message();
  check_consolidated_trade_cancellation_message();
  check_pricevolume_indicator_message();
  check_consolidated_execution_of_orders_message();
  check_registration_of_order_message();
  check_cancellations_of_orders_message();
  check_last_quote_message();
}

int main(void) {
#ifdef CONCRETE
  for (pattern = 0; pattern < 4; pattern++) { checks(); }
#else
  checks();
#endif

  return 0;
}
