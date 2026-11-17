// nse/nseslbm/orderentry/NseSlbm_OrderEntry_v2_7_Server.c
/*
 * National Stock Exchange of India Ltd Order Entry
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
 *   - the dispatch that chooses a message by its type
 *   - a Composite rule
 *   - a field read in bits
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

/* ---- Packet Header: 22 bytes ------------------------------------------------- */

/* Direct interface twenty two byte packet header */
typedef struct {
  uint8_t packet_length[2];           /* bytes 0 to 1 */
  uint8_t packet_sequence_number[4];  /* bytes 2 to 5 */
  uint8_t checksum[16];               /* bytes 6 to 21 */
} PacketHeader;

/* any Packet Header at all: every byte one the checker chooses */
static void any_packet_header(PacketHeader *record) {
  for (size_t i = 0; i < 2; i++) { record->packet_length[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->packet_sequence_number[i] = arbitrary(); }
  for (size_t i = 0; i < 16; i++) { record->checksum[i] = arbitrary(); }
}

/* Packet Header to the wire: 22 bytes from at, returning where the next byte goes */
static size_t encode_packet_header(const PacketHeader *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->packet_length[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->packet_sequence_number[i]; }
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->checksum[i]; }

  return at;
}

/* Packet Header off the wire: 22 bytes from at, returning where the next byte lies */
static size_t decode_packet_header(PacketHeader *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->packet_length[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->packet_sequence_number[i] = wire[at++]; }
  for (size_t i = 0; i < 16; i++) { record->checksum[i] = wire[at++]; }

  return at;
}

/* what was read of Packet Header is what was written, byte for byte */
static void equal_packet_header(const PacketHeader *read, const PacketHeader *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->packet_length[i] == written->packet_length[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->packet_sequence_number[i] == written->packet_sequence_number[i]); }
  for (size_t i = 0; i < 16; i++) { assert(read->checksum[i] == written->checksum[i]); }
}

/* Packet Header: written and read back, then read and written back */
static void check_packet_header(void) {
  PacketHeader sent;
  PacketHeader got;
  uint8_t wire[22];
  uint8_t again[22];

  any_packet_header(&sent);
  assert(encode_packet_header(&sent, wire, 0) == 22);
  assert(decode_packet_header(&got, wire, 0) == 22);
  equal_packet_header(&got, &sent);

  for (size_t i = 0; i < 22; i++) { wire[i] = arbitrary(); }
  assert(decode_packet_header(&got, wire, 0) == 22);
  assert(encode_packet_header(&got, again, 0) == 22);
  for (size_t i = 0; i < 22; i++) { assert(again[i] == wire[i]); }
}

/* ---- Message Header: 40 bytes ------------------------------------------------ */

/* MESSAGE_HEADER */
typedef struct {
  uint8_t transaction_code[2];  /* bytes 0 to 1 */
  uint8_t log_time[4];          /* bytes 2 to 5 */
  uint8_t alpha_char[2];        /* bytes 6 to 7 */
  uint8_t trader_id[4];         /* bytes 8 to 11 */
  uint8_t error_code[2];        /* bytes 12 to 13 */
  uint8_t header_timestamp[8];  /* bytes 14 to 21 */
  uint8_t time_stamp_1[8];      /* bytes 22 to 29 */
  uint8_t time_stamp_2[8];      /* bytes 30 to 37 */
  uint8_t message_length[2];    /* bytes 38 to 39 */
} MessageHeader;

/* any Message Header at all: every byte one the checker chooses */
static void any_message_header(MessageHeader *record) {
  for (size_t i = 0; i < 2; i++) { record->transaction_code[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->log_time[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->alpha_char[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->trader_id[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->error_code[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->header_timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->time_stamp_1[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->time_stamp_2[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->message_length[i] = arbitrary(); }
}

/* Message Header to the wire: 40 bytes from at, returning where the next byte goes */
static size_t encode_message_header(const MessageHeader *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->transaction_code[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->log_time[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->alpha_char[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->trader_id[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->error_code[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->header_timestamp[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->time_stamp_1[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->time_stamp_2[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->message_length[i]; }

  return at;
}

/* Message Header off the wire: 40 bytes from at, returning where the next byte lies */
static size_t decode_message_header(MessageHeader *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->transaction_code[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->log_time[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->alpha_char[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->trader_id[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->error_code[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->header_timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->time_stamp_1[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->time_stamp_2[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->message_length[i] = wire[at++]; }

  return at;
}

/* what was read of Message Header is what was written, byte for byte */
static void equal_message_header(const MessageHeader *read, const MessageHeader *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->transaction_code[i] == written->transaction_code[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->log_time[i] == written->log_time[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->alpha_char[i] == written->alpha_char[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->trader_id[i] == written->trader_id[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->error_code[i] == written->error_code[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->header_timestamp[i] == written->header_timestamp[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->time_stamp_1[i] == written->time_stamp_1[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->time_stamp_2[i] == written->time_stamp_2[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->message_length[i] == written->message_length[i]); }
}

/* Message Header: written and read back, then read and written back */
static void check_message_header(void) {
  MessageHeader sent;
  MessageHeader got;
  uint8_t wire[40];
  uint8_t again[40];

  any_message_header(&sent);
  assert(encode_message_header(&sent, wire, 0) == 40);
  assert(decode_message_header(&got, wire, 0) == 40);
  equal_message_header(&got, &sent);

  for (size_t i = 0; i < 40; i++) { wire[i] = arbitrary(); }
  assert(decode_message_header(&got, wire, 0) == 40);
  assert(encode_message_header(&got, again, 0) == 40);
  for (size_t i = 0; i < 40; i++) { assert(again[i] == wire[i]); }
}

/* ---- Sec Info: 12 bytes ------------------------------------------------------ */

/* SEC_INFO */
typedef struct {
  uint8_t symbol[10];  /* bytes 0 to 9 */
  uint8_t series[2];   /* bytes 10 to 11 */
} SecInfo;

/* any Sec Info at all: every byte one the checker chooses */
static void any_sec_info(SecInfo *record) {
  for (size_t i = 0; i < 10; i++) { record->symbol[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->series[i] = arbitrary(); }
}

/* Sec Info to the wire: 12 bytes from at, returning where the next byte goes */
static size_t encode_sec_info(const SecInfo *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->symbol[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->series[i]; }

  return at;
}

/* Sec Info off the wire: 12 bytes from at, returning where the next byte lies */
static size_t decode_sec_info(SecInfo *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 10; i++) { record->symbol[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->series[i] = wire[at++]; }

  return at;
}

/* what was read of Sec Info is what was written, byte for byte */
static void equal_sec_info(const SecInfo *read, const SecInfo *written) {
  for (size_t i = 0; i < 10; i++) { assert(read->symbol[i] == written->symbol[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->series[i] == written->series[i]); }
}

/* Sec Info: written and read back, then read and written back */
static void check_sec_info(void) {
  SecInfo sent;
  SecInfo got;
  uint8_t wire[12];
  uint8_t again[12];

  any_sec_info(&sent);
  assert(encode_sec_info(&sent, wire, 0) == 12);
  assert(decode_sec_info(&got, wire, 0) == 12);
  equal_sec_info(&got, &sent);

  for (size_t i = 0; i < 12; i++) { wire[i] = arbitrary(); }
  assert(decode_sec_info(&got, wire, 0) == 12);
  assert(encode_sec_info(&got, again, 0) == 12);
  for (size_t i = 0; i < 12; i++) { assert(again[i] == wire[i]); }
}

/* ---- Logon Error Body: 140 bytes --------------------------------------------- */

/* Logon Error Body */
typedef struct {
  SecInfo sec_info;            /* bytes 0 to 11 */
  uint8_t error_message[128];  /* bytes 12 to 139 */
} LogonErrorBody;

/* any Logon Error Body at all: every byte one the checker chooses */
static void any_logon_error_body(LogonErrorBody *record) {
  any_sec_info(&record->sec_info);
  for (size_t i = 0; i < 128; i++) { record->error_message[i] = arbitrary(); }
}

/* Logon Error Body to the wire: 140 bytes from at, returning where the next byte goes */
static size_t encode_logon_error_body(const LogonErrorBody *record, uint8_t *wire, size_t at) {
  at = encode_sec_info(&record->sec_info, wire, at);
  for (size_t i = 0; i < 128; i++) { wire[at++] = record->error_message[i]; }

  return at;
}

/* Logon Error Body off the wire: 140 bytes from at, returning where the next byte lies */
static size_t decode_logon_error_body(LogonErrorBody *record, const uint8_t *wire, size_t at) {
  at = decode_sec_info(&record->sec_info, wire, at);
  for (size_t i = 0; i < 128; i++) { record->error_message[i] = wire[at++]; }

  return at;
}

/* what was read of Logon Error Body is what was written, byte for byte */
static void equal_logon_error_body(const LogonErrorBody *read, const LogonErrorBody *written) {
  equal_sec_info(&read->sec_info, &written->sec_info);
  for (size_t i = 0; i < 128; i++) { assert(read->error_message[i] == written->error_message[i]); }
}

/* Logon Error Body: written and read back, then read and written back */
static void check_logon_error_body(void) {
  LogonErrorBody sent;
  LogonErrorBody got;
  uint8_t wire[140];
  uint8_t again[140];

  any_logon_error_body(&sent);
  assert(encode_logon_error_body(&sent, wire, 0) == 140);
  assert(decode_logon_error_body(&got, wire, 0) == 140);
  equal_logon_error_body(&got, &sent);

  for (size_t i = 0; i < 140; i++) { wire[i] = arbitrary(); }
  assert(decode_logon_error_body(&got, wire, 0) == 140);
  assert(encode_logon_error_body(&got, again, 0) == 140);
  for (size_t i = 0; i < 140; i++) { assert(again[i] == wire[i]); }
}

/* ---- Update Local Database Header Message: 2 bytes --------------------------- */

/* Sent as UPDATE_LOCALDB_HEADER to signal that the local database download is starting */
typedef struct {
  uint8_t reserved_2[2];  /* bytes 0 to 1 */
} UpdateLocalDatabaseHeaderMessage;

/* any Update Local Database Header Message at all: every byte one the checker chooses */
static void any_update_local_database_header_message(UpdateLocalDatabaseHeaderMessage *record) {
  for (size_t i = 0; i < 2; i++) { record->reserved_2[i] = arbitrary(); }
}

/* Update Local Database Header Message to the wire: 2 bytes from at, returning where the next byte goes */
static size_t encode_update_local_database_header_message(const UpdateLocalDatabaseHeaderMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->reserved_2[i]; }

  return at;
}

/* Update Local Database Header Message off the wire: 2 bytes from at, returning where the next byte lies */
static size_t decode_update_local_database_header_message(UpdateLocalDatabaseHeaderMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->reserved_2[i] = wire[at++]; }

  return at;
}

/* what was read of Update Local Database Header Message is what was written, byte for byte */
static void equal_update_local_database_header_message(const UpdateLocalDatabaseHeaderMessage *read, const UpdateLocalDatabaseHeaderMessage *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->reserved_2[i] == written->reserved_2[i]); }
}

/* Update Local Database Header Message: written and read back, then read and written back */
static void check_update_local_database_header_message(void) {
  UpdateLocalDatabaseHeaderMessage sent;
  UpdateLocalDatabaseHeaderMessage got;
  uint8_t wire[2];
  uint8_t again[2];

  any_update_local_database_header_message(&sent);
  assert(encode_update_local_database_header_message(&sent, wire, 0) == 2);
  assert(decode_update_local_database_header_message(&got, wire, 0) == 2);
  equal_update_local_database_header_message(&got, &sent);

  for (size_t i = 0; i < 2; i++) { wire[i] = arbitrary(); }
  assert(decode_update_local_database_header_message(&got, wire, 0) == 2);
  assert(encode_update_local_database_header_message(&got, again, 0) == 2);
  for (size_t i = 0; i < 2; i++) { assert(again[i] == wire[i]); }
}

/* ---- Update Local Database Trailer Message: 2 bytes -------------------------- */

/* Sent as UPDATE_LOCALDB_TRAILER to signal that the local database download is complete */
typedef struct {
  uint8_t reserved_2[2];  /* bytes 0 to 1 */
} UpdateLocalDatabaseTrailerMessage;

/* any Update Local Database Trailer Message at all: every byte one the checker chooses */
static void any_update_local_database_trailer_message(UpdateLocalDatabaseTrailerMessage *record) {
  for (size_t i = 0; i < 2; i++) { record->reserved_2[i] = arbitrary(); }
}

/* Update Local Database Trailer Message to the wire: 2 bytes from at, returning where the next byte goes */
static size_t encode_update_local_database_trailer_message(const UpdateLocalDatabaseTrailerMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->reserved_2[i]; }

  return at;
}

/* Update Local Database Trailer Message off the wire: 2 bytes from at, returning where the next byte lies */
static size_t decode_update_local_database_trailer_message(UpdateLocalDatabaseTrailerMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->reserved_2[i] = wire[at++]; }

  return at;
}

/* what was read of Update Local Database Trailer Message is what was written, byte for byte */
static void equal_update_local_database_trailer_message(const UpdateLocalDatabaseTrailerMessage *read, const UpdateLocalDatabaseTrailerMessage *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->reserved_2[i] == written->reserved_2[i]); }
}

/* Update Local Database Trailer Message: written and read back, then read and written back */
static void check_update_local_database_trailer_message(void) {
  UpdateLocalDatabaseTrailerMessage sent;
  UpdateLocalDatabaseTrailerMessage got;
  uint8_t wire[2];
  uint8_t again[2];

  any_update_local_database_trailer_message(&sent);
  assert(encode_update_local_database_trailer_message(&sent, wire, 0) == 2);
  assert(decode_update_local_database_trailer_message(&got, wire, 0) == 2);
  equal_update_local_database_trailer_message(&got, &sent);

  for (size_t i = 0; i < 2; i++) { wire[i] = arbitrary(); }
  assert(decode_update_local_database_trailer_message(&got, wire, 0) == 2);
  assert(encode_update_local_database_trailer_message(&got, again, 0) == 2);
  for (size_t i = 0; i < 2; i++) { assert(again[i] == wire[i]); }
}

/* ---- Trade Cancellation Requested Response Message: 74 bytes ----------------- */

/* Sent as TRADE_CANCEL_OUT to acknowledge that the request reached the trading system */
typedef struct {
  SecInfo sec_info;                   /* bytes 0 to 11 */
  uint8_t reverse_leg_settl_date[4];  /* bytes 12 to 15 */
  uint8_t l_fill_number[4];           /* bytes 16 to 19 */
  uint8_t l_fill_qty[4];              /* bytes 20 to 23 */
  uint8_t l_fill_price[4];            /* bytes 24 to 27 */
  uint8_t i_mkt_type[2];              /* bytes 28 to 29 */
  uint8_t l_new_volume[4];            /* bytes 30 to 33 */
  uint8_t buy_participant_id[12];     /* bytes 34 to 45 */
  uint8_t sell_participant_id[12];    /* bytes 46 to 57 */
  uint8_t buy_broker_id[5];           /* bytes 58 to 62 */
  uint8_t sell_broker_id[5];          /* bytes 63 to 67 */
  uint8_t trader_id[4];               /* bytes 68 to 71 */
  uint8_t requested_by[2];            /* bytes 72 to 73 */
} TradeCancellationRequestedResponseMessage;

/* any Trade Cancellation Requested Response Message at all: every byte one the checker chooses */
static void any_trade_cancellation_requested_response_message(TradeCancellationRequestedResponseMessage *record) {
  any_sec_info(&record->sec_info);
  for (size_t i = 0; i < 4; i++) { record->reverse_leg_settl_date[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->l_fill_number[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->l_fill_qty[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->l_fill_price[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->i_mkt_type[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->l_new_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->buy_participant_id[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->sell_participant_id[i] = arbitrary(); }
  for (size_t i = 0; i < 5; i++) { record->buy_broker_id[i] = arbitrary(); }
  for (size_t i = 0; i < 5; i++) { record->sell_broker_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->trader_id[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->requested_by[i] = arbitrary(); }
}

/* Trade Cancellation Requested Response Message to the wire: 74 bytes from at, returning where the next byte goes */
static size_t encode_trade_cancellation_requested_response_message(const TradeCancellationRequestedResponseMessage *record, uint8_t *wire, size_t at) {
  at = encode_sec_info(&record->sec_info, wire, at);
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->reverse_leg_settl_date[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->l_fill_number[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->l_fill_qty[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->l_fill_price[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->i_mkt_type[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->l_new_volume[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->buy_participant_id[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->sell_participant_id[i]; }
  for (size_t i = 0; i < 5; i++) { wire[at++] = record->buy_broker_id[i]; }
  for (size_t i = 0; i < 5; i++) { wire[at++] = record->sell_broker_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->trader_id[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->requested_by[i]; }

  return at;
}

/* Trade Cancellation Requested Response Message off the wire: 74 bytes from at, returning where the next byte lies */
static size_t decode_trade_cancellation_requested_response_message(TradeCancellationRequestedResponseMessage *record, const uint8_t *wire, size_t at) {
  at = decode_sec_info(&record->sec_info, wire, at);
  for (size_t i = 0; i < 4; i++) { record->reverse_leg_settl_date[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->l_fill_number[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->l_fill_qty[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->l_fill_price[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->i_mkt_type[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->l_new_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->buy_participant_id[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->sell_participant_id[i] = wire[at++]; }
  for (size_t i = 0; i < 5; i++) { record->buy_broker_id[i] = wire[at++]; }
  for (size_t i = 0; i < 5; i++) { record->sell_broker_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->trader_id[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->requested_by[i] = wire[at++]; }

  return at;
}

/* what was read of Trade Cancellation Requested Response Message is what was written, byte for byte */
static void equal_trade_cancellation_requested_response_message(const TradeCancellationRequestedResponseMessage *read, const TradeCancellationRequestedResponseMessage *written) {
  equal_sec_info(&read->sec_info, &written->sec_info);
  for (size_t i = 0; i < 4; i++) { assert(read->reverse_leg_settl_date[i] == written->reverse_leg_settl_date[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->l_fill_number[i] == written->l_fill_number[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->l_fill_qty[i] == written->l_fill_qty[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->l_fill_price[i] == written->l_fill_price[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->i_mkt_type[i] == written->i_mkt_type[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->l_new_volume[i] == written->l_new_volume[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->buy_participant_id[i] == written->buy_participant_id[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->sell_participant_id[i] == written->sell_participant_id[i]); }
  for (size_t i = 0; i < 5; i++) { assert(read->buy_broker_id[i] == written->buy_broker_id[i]); }
  for (size_t i = 0; i < 5; i++) { assert(read->sell_broker_id[i] == written->sell_broker_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->trader_id[i] == written->trader_id[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->requested_by[i] == written->requested_by[i]); }
}

/* Trade Cancellation Requested Response Message: written and read back, then read and written back */
static void check_trade_cancellation_requested_response_message(void) {
  TradeCancellationRequestedResponseMessage sent;
  TradeCancellationRequestedResponseMessage got;
  uint8_t wire[74];
  uint8_t again[74];

  any_trade_cancellation_requested_response_message(&sent);
  assert(encode_trade_cancellation_requested_response_message(&sent, wire, 0) == 74);
  assert(decode_trade_cancellation_requested_response_message(&got, wire, 0) == 74);
  equal_trade_cancellation_requested_response_message(&got, &sent);

  for (size_t i = 0; i < 74; i++) { wire[i] = arbitrary(); }
  assert(decode_trade_cancellation_requested_response_message(&got, wire, 0) == 74);
  assert(encode_trade_cancellation_requested_response_message(&got, again, 0) == 74);
  for (size_t i = 0; i < 74; i++) { assert(again[i] == wire[i]); }
}

/* ---- Trade Cancellation Error Message: 74 bytes ------------------------------ */

/* Sent as TRADE_ERROR when an error is detected in the request */
typedef struct {
  SecInfo sec_info;                   /* bytes 0 to 11 */
  uint8_t reverse_leg_settl_date[4];  /* bytes 12 to 15 */
  uint8_t l_fill_number[4];           /* bytes 16 to 19 */
  uint8_t l_fill_qty[4];              /* bytes 20 to 23 */
  uint8_t l_fill_price[4];            /* bytes 24 to 27 */
  uint8_t i_mkt_type[2];              /* bytes 28 to 29 */
  uint8_t l_new_volume[4];            /* bytes 30 to 33 */
  uint8_t buy_participant_id[12];     /* bytes 34 to 45 */
  uint8_t sell_participant_id[12];    /* bytes 46 to 57 */
  uint8_t buy_broker_id[5];           /* bytes 58 to 62 */
  uint8_t sell_broker_id[5];          /* bytes 63 to 67 */
  uint8_t trader_id[4];               /* bytes 68 to 71 */
  uint8_t requested_by[2];            /* bytes 72 to 73 */
} TradeCancellationErrorMessage;

/* any Trade Cancellation Error Message at all: every byte one the checker chooses */
static void any_trade_cancellation_error_message(TradeCancellationErrorMessage *record) {
  any_sec_info(&record->sec_info);
  for (size_t i = 0; i < 4; i++) { record->reverse_leg_settl_date[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->l_fill_number[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->l_fill_qty[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->l_fill_price[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->i_mkt_type[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->l_new_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->buy_participant_id[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->sell_participant_id[i] = arbitrary(); }
  for (size_t i = 0; i < 5; i++) { record->buy_broker_id[i] = arbitrary(); }
  for (size_t i = 0; i < 5; i++) { record->sell_broker_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->trader_id[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->requested_by[i] = arbitrary(); }
}

/* Trade Cancellation Error Message to the wire: 74 bytes from at, returning where the next byte goes */
static size_t encode_trade_cancellation_error_message(const TradeCancellationErrorMessage *record, uint8_t *wire, size_t at) {
  at = encode_sec_info(&record->sec_info, wire, at);
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->reverse_leg_settl_date[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->l_fill_number[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->l_fill_qty[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->l_fill_price[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->i_mkt_type[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->l_new_volume[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->buy_participant_id[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->sell_participant_id[i]; }
  for (size_t i = 0; i < 5; i++) { wire[at++] = record->buy_broker_id[i]; }
  for (size_t i = 0; i < 5; i++) { wire[at++] = record->sell_broker_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->trader_id[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->requested_by[i]; }

  return at;
}

/* Trade Cancellation Error Message off the wire: 74 bytes from at, returning where the next byte lies */
static size_t decode_trade_cancellation_error_message(TradeCancellationErrorMessage *record, const uint8_t *wire, size_t at) {
  at = decode_sec_info(&record->sec_info, wire, at);
  for (size_t i = 0; i < 4; i++) { record->reverse_leg_settl_date[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->l_fill_number[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->l_fill_qty[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->l_fill_price[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->i_mkt_type[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->l_new_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->buy_participant_id[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->sell_participant_id[i] = wire[at++]; }
  for (size_t i = 0; i < 5; i++) { record->buy_broker_id[i] = wire[at++]; }
  for (size_t i = 0; i < 5; i++) { record->sell_broker_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->trader_id[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->requested_by[i] = wire[at++]; }

  return at;
}

/* what was read of Trade Cancellation Error Message is what was written, byte for byte */
static void equal_trade_cancellation_error_message(const TradeCancellationErrorMessage *read, const TradeCancellationErrorMessage *written) {
  equal_sec_info(&read->sec_info, &written->sec_info);
  for (size_t i = 0; i < 4; i++) { assert(read->reverse_leg_settl_date[i] == written->reverse_leg_settl_date[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->l_fill_number[i] == written->l_fill_number[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->l_fill_qty[i] == written->l_fill_qty[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->l_fill_price[i] == written->l_fill_price[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->i_mkt_type[i] == written->i_mkt_type[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->l_new_volume[i] == written->l_new_volume[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->buy_participant_id[i] == written->buy_participant_id[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->sell_participant_id[i] == written->sell_participant_id[i]); }
  for (size_t i = 0; i < 5; i++) { assert(read->buy_broker_id[i] == written->buy_broker_id[i]); }
  for (size_t i = 0; i < 5; i++) { assert(read->sell_broker_id[i] == written->sell_broker_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->trader_id[i] == written->trader_id[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->requested_by[i] == written->requested_by[i]); }
}

/* Trade Cancellation Error Message: written and read back, then read and written back */
static void check_trade_cancellation_error_message(void) {
  TradeCancellationErrorMessage sent;
  TradeCancellationErrorMessage got;
  uint8_t wire[74];
  uint8_t again[74];

  any_trade_cancellation_error_message(&sent);
  assert(encode_trade_cancellation_error_message(&sent, wire, 0) == 74);
  assert(decode_trade_cancellation_error_message(&got, wire, 0) == 74);
  equal_trade_cancellation_error_message(&got, &sent);

  for (size_t i = 0; i < 74; i++) { wire[i] = arbitrary(); }
  assert(decode_trade_cancellation_error_message(&got, wire, 0) == 74);
  assert(encode_trade_cancellation_error_message(&got, again, 0) == 74);
  for (size_t i = 0; i < 74; i++) { assert(again[i] == wire[i]); }
}

/* ---- Trade Modification Requested Response Message: 74 bytes ----------------- */

/* Sent as TRADE_MOD_OUT; trade modification is currently not allowed */
typedef struct {
  SecInfo sec_info;                   /* bytes 0 to 11 */
  uint8_t reverse_leg_settl_date[4];  /* bytes 12 to 15 */
  uint8_t l_fill_number[4];           /* bytes 16 to 19 */
  uint8_t l_fill_qty[4];              /* bytes 20 to 23 */
  uint8_t l_fill_price[4];            /* bytes 24 to 27 */
  uint8_t i_mkt_type[2];              /* bytes 28 to 29 */
  uint8_t l_new_volume[4];            /* bytes 30 to 33 */
  uint8_t buy_participant_id[12];     /* bytes 34 to 45 */
  uint8_t sell_participant_id[12];    /* bytes 46 to 57 */
  uint8_t buy_broker_id[5];           /* bytes 58 to 62 */
  uint8_t sell_broker_id[5];          /* bytes 63 to 67 */
  uint8_t trader_id[4];               /* bytes 68 to 71 */
  uint8_t requested_by[2];            /* bytes 72 to 73 */
} TradeModificationRequestedResponseMessage;

/* any Trade Modification Requested Response Message at all: every byte one the checker chooses */
static void any_trade_modification_requested_response_message(TradeModificationRequestedResponseMessage *record) {
  any_sec_info(&record->sec_info);
  for (size_t i = 0; i < 4; i++) { record->reverse_leg_settl_date[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->l_fill_number[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->l_fill_qty[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->l_fill_price[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->i_mkt_type[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->l_new_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->buy_participant_id[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->sell_participant_id[i] = arbitrary(); }
  for (size_t i = 0; i < 5; i++) { record->buy_broker_id[i] = arbitrary(); }
  for (size_t i = 0; i < 5; i++) { record->sell_broker_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->trader_id[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->requested_by[i] = arbitrary(); }
}

/* Trade Modification Requested Response Message to the wire: 74 bytes from at, returning where the next byte goes */
static size_t encode_trade_modification_requested_response_message(const TradeModificationRequestedResponseMessage *record, uint8_t *wire, size_t at) {
  at = encode_sec_info(&record->sec_info, wire, at);
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->reverse_leg_settl_date[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->l_fill_number[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->l_fill_qty[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->l_fill_price[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->i_mkt_type[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->l_new_volume[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->buy_participant_id[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->sell_participant_id[i]; }
  for (size_t i = 0; i < 5; i++) { wire[at++] = record->buy_broker_id[i]; }
  for (size_t i = 0; i < 5; i++) { wire[at++] = record->sell_broker_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->trader_id[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->requested_by[i]; }

  return at;
}

/* Trade Modification Requested Response Message off the wire: 74 bytes from at, returning where the next byte lies */
static size_t decode_trade_modification_requested_response_message(TradeModificationRequestedResponseMessage *record, const uint8_t *wire, size_t at) {
  at = decode_sec_info(&record->sec_info, wire, at);
  for (size_t i = 0; i < 4; i++) { record->reverse_leg_settl_date[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->l_fill_number[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->l_fill_qty[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->l_fill_price[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->i_mkt_type[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->l_new_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->buy_participant_id[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->sell_participant_id[i] = wire[at++]; }
  for (size_t i = 0; i < 5; i++) { record->buy_broker_id[i] = wire[at++]; }
  for (size_t i = 0; i < 5; i++) { record->sell_broker_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->trader_id[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->requested_by[i] = wire[at++]; }

  return at;
}

/* what was read of Trade Modification Requested Response Message is what was written, byte for byte */
static void equal_trade_modification_requested_response_message(const TradeModificationRequestedResponseMessage *read, const TradeModificationRequestedResponseMessage *written) {
  equal_sec_info(&read->sec_info, &written->sec_info);
  for (size_t i = 0; i < 4; i++) { assert(read->reverse_leg_settl_date[i] == written->reverse_leg_settl_date[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->l_fill_number[i] == written->l_fill_number[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->l_fill_qty[i] == written->l_fill_qty[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->l_fill_price[i] == written->l_fill_price[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->i_mkt_type[i] == written->i_mkt_type[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->l_new_volume[i] == written->l_new_volume[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->buy_participant_id[i] == written->buy_participant_id[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->sell_participant_id[i] == written->sell_participant_id[i]); }
  for (size_t i = 0; i < 5; i++) { assert(read->buy_broker_id[i] == written->buy_broker_id[i]); }
  for (size_t i = 0; i < 5; i++) { assert(read->sell_broker_id[i] == written->sell_broker_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->trader_id[i] == written->trader_id[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->requested_by[i] == written->requested_by[i]); }
}

/* Trade Modification Requested Response Message: written and read back, then read and written back */
static void check_trade_modification_requested_response_message(void) {
  TradeModificationRequestedResponseMessage sent;
  TradeModificationRequestedResponseMessage got;
  uint8_t wire[74];
  uint8_t again[74];

  any_trade_modification_requested_response_message(&sent);
  assert(encode_trade_modification_requested_response_message(&sent, wire, 0) == 74);
  assert(decode_trade_modification_requested_response_message(&got, wire, 0) == 74);
  equal_trade_modification_requested_response_message(&got, &sent);

  for (size_t i = 0; i < 74; i++) { wire[i] = arbitrary(); }
  assert(decode_trade_modification_requested_response_message(&got, wire, 0) == 74);
  assert(encode_trade_modification_requested_response_message(&got, again, 0) == 74);
  for (size_t i = 0; i < 74; i++) { assert(again[i] == wire[i]); }
}

/* ---- Control Message To Trader Message: 249 bytes ---------------------------- */

/* Sent as CTRL_MSG_TO_TRADER for a message from NSE-Control to a particular user, and for a counter party's trade cancellation request */
typedef struct {
  uint8_t trader_id[4];    /* bytes 0 to 3 */
  uint8_t action_code[3];  /* bytes 4 to 6 */
  uint8_t reserved_1;      /* byte 7 */
  uint8_t msg_length[2];   /* bytes 8 to 9 */
  uint8_t msg[239];        /* bytes 10 to 248 */
} ControlMessageToTraderMessage;

/* any Control Message To Trader Message at all: every byte one the checker chooses */
static void any_control_message_to_trader_message(ControlMessageToTraderMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->trader_id[i] = arbitrary(); }
  for (size_t i = 0; i < 3; i++) { record->action_code[i] = arbitrary(); }
  record->reserved_1 = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->msg_length[i] = arbitrary(); }
  for (size_t i = 0; i < 239; i++) { record->msg[i] = arbitrary(); }
}

/* Control Message To Trader Message to the wire: 249 bytes from at, returning where the next byte goes */
static size_t encode_control_message_to_trader_message(const ControlMessageToTraderMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->trader_id[i]; }
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->action_code[i]; }
  wire[at++] = record->reserved_1;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->msg_length[i]; }
  for (size_t i = 0; i < 239; i++) { wire[at++] = record->msg[i]; }

  return at;
}

/* Control Message To Trader Message off the wire: 249 bytes from at, returning where the next byte lies */
static size_t decode_control_message_to_trader_message(ControlMessageToTraderMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->trader_id[i] = wire[at++]; }
  for (size_t i = 0; i < 3; i++) { record->action_code[i] = wire[at++]; }
  record->reserved_1 = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->msg_length[i] = wire[at++]; }
  for (size_t i = 0; i < 239; i++) { record->msg[i] = wire[at++]; }

  return at;
}

/* what was read of Control Message To Trader Message is what was written, byte for byte */
static void equal_control_message_to_trader_message(const ControlMessageToTraderMessage *read, const ControlMessageToTraderMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->trader_id[i] == written->trader_id[i]); }
  for (size_t i = 0; i < 3; i++) { assert(read->action_code[i] == written->action_code[i]); }
  assert(read->reserved_1 == written->reserved_1);
  for (size_t i = 0; i < 2; i++) { assert(read->msg_length[i] == written->msg_length[i]); }
  for (size_t i = 0; i < 239; i++) { assert(read->msg[i] == written->msg[i]); }
}

/* Control Message To Trader Message: written and read back, then read and written back */
static void check_control_message_to_trader_message(void) {
  ControlMessageToTraderMessage sent;
  ControlMessageToTraderMessage got;
  uint8_t wire[249];
  uint8_t again[249];

  any_control_message_to_trader_message(&sent);
  assert(encode_control_message_to_trader_message(&sent, wire, 0) == 249);
  assert(decode_control_message_to_trader_message(&got, wire, 0) == 249);
  equal_control_message_to_trader_message(&got, &sent);

  for (size_t i = 0; i < 249; i++) { wire[i] = arbitrary(); }
  assert(decode_control_message_to_trader_message(&got, wire, 0) == 249);
  assert(encode_control_message_to_trader_message(&got, again, 0) == 249);
  for (size_t i = 0; i < 249; i++) { assert(again[i] == wire[i]); }
}

/* ---- Error Response Message: 140 bytes --------------------------------------- */

/* Sent as ERROR_RESPONSE_OUT when the Error Code of the header is not zero */
typedef struct {
  SecInfo sec_info;            /* bytes 0 to 11 */
  uint8_t error_message[128];  /* bytes 12 to 139 */
} ErrorResponseMessage;

/* any Error Response Message at all: every byte one the checker chooses */
static void any_error_response_message(ErrorResponseMessage *record) {
  any_sec_info(&record->sec_info);
  for (size_t i = 0; i < 128; i++) { record->error_message[i] = arbitrary(); }
}

/* Error Response Message to the wire: 140 bytes from at, returning where the next byte goes */
static size_t encode_error_response_message(const ErrorResponseMessage *record, uint8_t *wire, size_t at) {
  at = encode_sec_info(&record->sec_info, wire, at);
  for (size_t i = 0; i < 128; i++) { wire[at++] = record->error_message[i]; }

  return at;
}

/* Error Response Message off the wire: 140 bytes from at, returning where the next byte lies */
static size_t decode_error_response_message(ErrorResponseMessage *record, const uint8_t *wire, size_t at) {
  at = decode_sec_info(&record->sec_info, wire, at);
  for (size_t i = 0; i < 128; i++) { record->error_message[i] = wire[at++]; }

  return at;
}

/* what was read of Error Response Message is what was written, byte for byte */
static void equal_error_response_message(const ErrorResponseMessage *read, const ErrorResponseMessage *written) {
  equal_sec_info(&read->sec_info, &written->sec_info);
  for (size_t i = 0; i < 128; i++) { assert(read->error_message[i] == written->error_message[i]); }
}

/* Error Response Message: written and read back, then read and written back */
static void check_error_response_message(void) {
  ErrorResponseMessage sent;
  ErrorResponseMessage got;
  uint8_t wire[140];
  uint8_t again[140];

  any_error_response_message(&sent);
  assert(encode_error_response_message(&sent, wire, 0) == 140);
  assert(decode_error_response_message(&got, wire, 0) == 140);
  equal_error_response_message(&got, &sent);

  for (size_t i = 0; i < 140; i++) { wire[i] = arbitrary(); }
  assert(decode_error_response_message(&got, wire, 0) == 140);
  assert(encode_error_response_message(&got, again, 0) == 140);
  for (size_t i = 0; i < 140; i++) { assert(again[i] == wire[i]); }
}

/* ---- Gateway Router Response Message: 84 bytes ------------------------------- */

/* Sent as GR_RESPONSE with the allocated gateway server, its session key and the cryptographic key and vector */
typedef struct {
  uint8_t box_id[2];                                   /* bytes 0 to 1 */
  uint8_t broker_id[5];                                /* bytes 2 to 6 */
  uint8_t filler;                                      /* byte 7 */
  uint8_t ip_address[16];                              /* bytes 8 to 23 */
  uint8_t port[4];                                     /* bytes 24 to 27 */
  uint8_t session_key[8];                              /* bytes 28 to 35 */
  uint8_t cryptographic_key[32];                       /* bytes 36 to 67 */
  uint8_t cryptographic_iv_initialization_vector[16];  /* bytes 68 to 83 */
} GatewayRouterResponseMessage;

/* any Gateway Router Response Message at all: every byte one the checker chooses */
static void any_gateway_router_response_message(GatewayRouterResponseMessage *record) {
  for (size_t i = 0; i < 2; i++) { record->box_id[i] = arbitrary(); }
  for (size_t i = 0; i < 5; i++) { record->broker_id[i] = arbitrary(); }
  record->filler = arbitrary();
  for (size_t i = 0; i < 16; i++) { record->ip_address[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->port[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->session_key[i] = arbitrary(); }
  for (size_t i = 0; i < 32; i++) { record->cryptographic_key[i] = arbitrary(); }
  for (size_t i = 0; i < 16; i++) { record->cryptographic_iv_initialization_vector[i] = arbitrary(); }
}

/* Gateway Router Response Message to the wire: 84 bytes from at, returning where the next byte goes */
static size_t encode_gateway_router_response_message(const GatewayRouterResponseMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->box_id[i]; }
  for (size_t i = 0; i < 5; i++) { wire[at++] = record->broker_id[i]; }
  wire[at++] = record->filler;
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->ip_address[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->port[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->session_key[i]; }
  for (size_t i = 0; i < 32; i++) { wire[at++] = record->cryptographic_key[i]; }
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->cryptographic_iv_initialization_vector[i]; }

  return at;
}

/* Gateway Router Response Message off the wire: 84 bytes from at, returning where the next byte lies */
static size_t decode_gateway_router_response_message(GatewayRouterResponseMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->box_id[i] = wire[at++]; }
  for (size_t i = 0; i < 5; i++) { record->broker_id[i] = wire[at++]; }
  record->filler = wire[at++];
  for (size_t i = 0; i < 16; i++) { record->ip_address[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->port[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->session_key[i] = wire[at++]; }
  for (size_t i = 0; i < 32; i++) { record->cryptographic_key[i] = wire[at++]; }
  for (size_t i = 0; i < 16; i++) { record->cryptographic_iv_initialization_vector[i] = wire[at++]; }

  return at;
}

/* what was read of Gateway Router Response Message is what was written, byte for byte */
static void equal_gateway_router_response_message(const GatewayRouterResponseMessage *read, const GatewayRouterResponseMessage *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->box_id[i] == written->box_id[i]); }
  for (size_t i = 0; i < 5; i++) { assert(read->broker_id[i] == written->broker_id[i]); }
  assert(read->filler == written->filler);
  for (size_t i = 0; i < 16; i++) { assert(read->ip_address[i] == written->ip_address[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->port[i] == written->port[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->session_key[i] == written->session_key[i]); }
  for (size_t i = 0; i < 32; i++) { assert(read->cryptographic_key[i] == written->cryptographic_key[i]); }
  for (size_t i = 0; i < 16; i++) { assert(read->cryptographic_iv_initialization_vector[i] == written->cryptographic_iv_initialization_vector[i]); }
}

/* Gateway Router Response Message: written and read back, then read and written back */
static void check_gateway_router_response_message(void) {
  GatewayRouterResponseMessage sent;
  GatewayRouterResponseMessage got;
  uint8_t wire[84];
  uint8_t again[84];

  any_gateway_router_response_message(&sent);
  assert(encode_gateway_router_response_message(&sent, wire, 0) == 84);
  assert(decode_gateway_router_response_message(&got, wire, 0) == 84);
  equal_gateway_router_response_message(&got, &sent);

  for (size_t i = 0; i < 84; i++) { wire[i] = arbitrary(); }
  assert(decode_gateway_router_response_message(&got, wire, 0) == 84);
  assert(encode_gateway_router_response_message(&got, again, 0) == 84);
  for (size_t i = 0; i < 84; i++) { assert(again[i] == wire[i]); }
}

/* ---- Box Sign On Response Message: 12 bytes ---------------------------------- */

/* Sent as BOX_SIGN_ON_REQUEST_OUT; an error terminates the box connection */
typedef struct {
  uint8_t box_id[2];        /* bytes 0 to 1 */
  uint8_t reserved_10[10];  /* bytes 2 to 11 */
} BoxSignOnResponseMessage;

/* any Box Sign On Response Message at all: every byte one the checker chooses */
static void any_box_sign_on_response_message(BoxSignOnResponseMessage *record) {
  for (size_t i = 0; i < 2; i++) { record->box_id[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->reserved_10[i] = arbitrary(); }
}

/* Box Sign On Response Message to the wire: 12 bytes from at, returning where the next byte goes */
static size_t encode_box_sign_on_response_message(const BoxSignOnResponseMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->box_id[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->reserved_10[i]; }

  return at;
}

/* Box Sign On Response Message off the wire: 12 bytes from at, returning where the next byte lies */
static size_t decode_box_sign_on_response_message(BoxSignOnResponseMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->box_id[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->reserved_10[i] = wire[at++]; }

  return at;
}

/* what was read of Box Sign On Response Message is what was written, byte for byte */
static void equal_box_sign_on_response_message(const BoxSignOnResponseMessage *read, const BoxSignOnResponseMessage *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->box_id[i] == written->box_id[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->reserved_10[i] == written->reserved_10[i]); }
}

/* Box Sign On Response Message: written and read back, then read and written back */
static void check_box_sign_on_response_message(void) {
  BoxSignOnResponseMessage sent;
  BoxSignOnResponseMessage got;
  uint8_t wire[12];
  uint8_t again[12];

  any_box_sign_on_response_message(&sent);
  assert(encode_box_sign_on_response_message(&sent, wire, 0) == 12);
  assert(decode_box_sign_on_response_message(&got, wire, 0) == 12);
  equal_box_sign_on_response_message(&got, &sent);

  for (size_t i = 0; i < 12; i++) { wire[i] = arbitrary(); }
  assert(decode_box_sign_on_response_message(&got, wire, 0) == 12);
  assert(encode_box_sign_on_response_message(&got, again, 0) == 12);
  for (size_t i = 0; i < 12; i++) { assert(again[i] == wire[i]); }
}

/* ---- Box Sign Off Message: 2 bytes ------------------------------------------- */

/* Sent as BOX_SIGN_OFF with an error code when the exchange terminates the connection */
typedef struct {
  uint8_t box_id[2];  /* bytes 0 to 1 */
} BoxSignOffMessage;

/* any Box Sign Off Message at all: every byte one the checker chooses */
static void any_box_sign_off_message(BoxSignOffMessage *record) {
  for (size_t i = 0; i < 2; i++) { record->box_id[i] = arbitrary(); }
}

/* Box Sign Off Message to the wire: 2 bytes from at, returning where the next byte goes */
static size_t encode_box_sign_off_message(const BoxSignOffMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->box_id[i]; }

  return at;
}

/* Box Sign Off Message off the wire: 2 bytes from at, returning where the next byte lies */
static size_t decode_box_sign_off_message(BoxSignOffMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->box_id[i] = wire[at++]; }

  return at;
}

/* what was read of Box Sign Off Message is what was written, byte for byte */
static void equal_box_sign_off_message(const BoxSignOffMessage *read, const BoxSignOffMessage *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->box_id[i] == written->box_id[i]); }
}

/* Box Sign Off Message: written and read back, then read and written back */
static void check_box_sign_off_message(void) {
  BoxSignOffMessage sent;
  BoxSignOffMessage got;
  uint8_t wire[2];
  uint8_t again[2];

  any_box_sign_off_message(&sent);
  assert(encode_box_sign_off_message(&sent, wire, 0) == 2);
  assert(decode_box_sign_off_message(&got, wire, 0) == 2);
  equal_box_sign_off_message(&got, &sent);

  for (size_t i = 0; i < 2; i++) { wire[i] = arbitrary(); }
  assert(decode_box_sign_off_message(&got, wire, 0) == 2);
  assert(encode_box_sign_off_message(&got, again, 0) == 2);
  for (size_t i = 0; i < 2; i++) { assert(again[i] == wire[i]); }
}

/* ---- What esbmc checks ------------------------------------------------------- */

/* every record of the protocol, each on its own buffers */
static void checks(void) {
  check_packet_header();
  check_message_header();
  check_sec_info();
  check_logon_error_body();
  check_update_local_database_header_message();
  check_update_local_database_trailer_message();
  check_trade_cancellation_requested_response_message();
  check_trade_cancellation_error_message();
  check_trade_modification_requested_response_message();
  check_control_message_to_trader_message();
  check_error_response_message();
  check_gateway_router_response_message();
  check_box_sign_on_response_message();
  check_box_sign_off_message();
}

int main(void) {
#ifdef CONCRETE
  for (pattern = 0; pattern < 4; pattern++) { checks(); }
#else
  checks();
#endif

  return 0;
}
