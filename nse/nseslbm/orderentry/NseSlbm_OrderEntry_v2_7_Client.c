// nse/nseslbm/orderentry/NseSlbm_OrderEntry_v2_7_Client.c
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
 *   - a Composite rule
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

/* ---- Update Local Database Request Message: 18 bytes ------------------------- */

/* Sent as UPDATE_LOCALDB_IN to request the local database download */
typedef struct {
  uint8_t last_update_security_time[4];     /* bytes 0 to 3 */
  uint8_t last_update_participant_time[4];  /* bytes 4 to 7 */
  uint8_t request_for_open_orders;          /* byte 8 */
  uint8_t reserved_1;                       /* byte 9 */
  uint8_t normal_market_status[2];          /* bytes 10 to 11 */
  uint8_t odd_lot_market_status[2];         /* bytes 12 to 13 */
  uint8_t spot_market_status[2];            /* bytes 14 to 15 */
  uint8_t auction_market_status[2];         /* bytes 16 to 17 */
} UpdateLocalDatabaseRequestMessage;

/* any Update Local Database Request Message at all: every byte one the checker chooses */
static void any_update_local_database_request_message(UpdateLocalDatabaseRequestMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->last_update_security_time[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->last_update_participant_time[i] = arbitrary(); }
  record->request_for_open_orders = arbitrary();
  record->reserved_1 = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->normal_market_status[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->odd_lot_market_status[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->spot_market_status[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->auction_market_status[i] = arbitrary(); }
}

/* Update Local Database Request Message to the wire: 18 bytes from at, returning where the next byte goes */
static size_t encode_update_local_database_request_message(const UpdateLocalDatabaseRequestMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->last_update_security_time[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->last_update_participant_time[i]; }
  wire[at++] = record->request_for_open_orders;
  wire[at++] = record->reserved_1;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->normal_market_status[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->odd_lot_market_status[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->spot_market_status[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->auction_market_status[i]; }

  return at;
}

/* Update Local Database Request Message off the wire: 18 bytes from at, returning where the next byte lies */
static size_t decode_update_local_database_request_message(UpdateLocalDatabaseRequestMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->last_update_security_time[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->last_update_participant_time[i] = wire[at++]; }
  record->request_for_open_orders = wire[at++];
  record->reserved_1 = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->normal_market_status[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->odd_lot_market_status[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->spot_market_status[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->auction_market_status[i] = wire[at++]; }

  return at;
}

/* what was read of Update Local Database Request Message is what was written, byte for byte */
static void equal_update_local_database_request_message(const UpdateLocalDatabaseRequestMessage *read, const UpdateLocalDatabaseRequestMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->last_update_security_time[i] == written->last_update_security_time[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->last_update_participant_time[i] == written->last_update_participant_time[i]); }
  assert(read->request_for_open_orders == written->request_for_open_orders);
  assert(read->reserved_1 == written->reserved_1);
  for (size_t i = 0; i < 2; i++) { assert(read->normal_market_status[i] == written->normal_market_status[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->odd_lot_market_status[i] == written->odd_lot_market_status[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->spot_market_status[i] == written->spot_market_status[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->auction_market_status[i] == written->auction_market_status[i]); }
}

/* Update Local Database Request Message: written and read back, then read and written back */
static void check_update_local_database_request_message(void) {
  UpdateLocalDatabaseRequestMessage sent;
  UpdateLocalDatabaseRequestMessage got;
  uint8_t wire[18];
  uint8_t again[18];

  any_update_local_database_request_message(&sent);
  assert(encode_update_local_database_request_message(&sent, wire, 0) == 18);
  assert(decode_update_local_database_request_message(&got, wire, 0) == 18);
  equal_update_local_database_request_message(&got, &sent);

  for (size_t i = 0; i < 18; i++) { wire[i] = arbitrary(); }
  assert(decode_update_local_database_request_message(&got, wire, 0) == 18);
  assert(encode_update_local_database_request_message(&got, again, 0) == 18);
  for (size_t i = 0; i < 18; i++) { assert(again[i] == wire[i]); }
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

/* ---- Trade Cancellation Request Message: 74 bytes ---------------------------- */

/* Sent as TRADE_CANCEL_IN to request cancellation of a trade */
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
} TradeCancellationRequestMessage;

/* any Trade Cancellation Request Message at all: every byte one the checker chooses */
static void any_trade_cancellation_request_message(TradeCancellationRequestMessage *record) {
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

/* Trade Cancellation Request Message to the wire: 74 bytes from at, returning where the next byte goes */
static size_t encode_trade_cancellation_request_message(const TradeCancellationRequestMessage *record, uint8_t *wire, size_t at) {
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

/* Trade Cancellation Request Message off the wire: 74 bytes from at, returning where the next byte lies */
static size_t decode_trade_cancellation_request_message(TradeCancellationRequestMessage *record, const uint8_t *wire, size_t at) {
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

/* what was read of Trade Cancellation Request Message is what was written, byte for byte */
static void equal_trade_cancellation_request_message(const TradeCancellationRequestMessage *read, const TradeCancellationRequestMessage *written) {
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

/* Trade Cancellation Request Message: written and read back, then read and written back */
static void check_trade_cancellation_request_message(void) {
  TradeCancellationRequestMessage sent;
  TradeCancellationRequestMessage got;
  uint8_t wire[74];
  uint8_t again[74];

  any_trade_cancellation_request_message(&sent);
  assert(encode_trade_cancellation_request_message(&sent, wire, 0) == 74);
  assert(decode_trade_cancellation_request_message(&got, wire, 0) == 74);
  equal_trade_cancellation_request_message(&got, &sent);

  for (size_t i = 0; i < 74; i++) { wire[i] = arbitrary(); }
  assert(decode_trade_cancellation_request_message(&got, wire, 0) == 74);
  assert(encode_trade_cancellation_request_message(&got, again, 0) == 74);
  for (size_t i = 0; i < 74; i++) { assert(again[i] == wire[i]); }
}

/* ---- Trade Modification Request Message: 74 bytes ---------------------------- */

/* Sent as TRADE_MOD_IN; trade modification is currently not allowed */
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
} TradeModificationRequestMessage;

/* any Trade Modification Request Message at all: every byte one the checker chooses */
static void any_trade_modification_request_message(TradeModificationRequestMessage *record) {
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

/* Trade Modification Request Message to the wire: 74 bytes from at, returning where the next byte goes */
static size_t encode_trade_modification_request_message(const TradeModificationRequestMessage *record, uint8_t *wire, size_t at) {
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

/* Trade Modification Request Message off the wire: 74 bytes from at, returning where the next byte lies */
static size_t decode_trade_modification_request_message(TradeModificationRequestMessage *record, const uint8_t *wire, size_t at) {
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

/* what was read of Trade Modification Request Message is what was written, byte for byte */
static void equal_trade_modification_request_message(const TradeModificationRequestMessage *read, const TradeModificationRequestMessage *written) {
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

/* Trade Modification Request Message: written and read back, then read and written back */
static void check_trade_modification_request_message(void) {
  TradeModificationRequestMessage sent;
  TradeModificationRequestMessage got;
  uint8_t wire[74];
  uint8_t again[74];

  any_trade_modification_request_message(&sent);
  assert(encode_trade_modification_request_message(&sent, wire, 0) == 74);
  assert(decode_trade_modification_request_message(&got, wire, 0) == 74);
  equal_trade_modification_request_message(&got, &sent);

  for (size_t i = 0; i < 74; i++) { wire[i] = arbitrary(); }
  assert(decode_trade_modification_request_message(&got, wire, 0) == 74);
  assert(encode_trade_modification_request_message(&got, again, 0) == 74);
  for (size_t i = 0; i < 74; i++) { assert(again[i] == wire[i]); }
}

/* ---- Gateway Router Request Message: 8 bytes --------------------------------- */

/* Sent as GR_REQUEST to the gateway router over a TLS connection */
typedef struct {
  uint8_t box_id[2];     /* bytes 0 to 1 */
  uint8_t broker_id[5];  /* bytes 2 to 6 */
  uint8_t filler;        /* byte 7 */
} GatewayRouterRequestMessage;

/* any Gateway Router Request Message at all: every byte one the checker chooses */
static void any_gateway_router_request_message(GatewayRouterRequestMessage *record) {
  for (size_t i = 0; i < 2; i++) { record->box_id[i] = arbitrary(); }
  for (size_t i = 0; i < 5; i++) { record->broker_id[i] = arbitrary(); }
  record->filler = arbitrary();
}

/* Gateway Router Request Message to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_gateway_router_request_message(const GatewayRouterRequestMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->box_id[i]; }
  for (size_t i = 0; i < 5; i++) { wire[at++] = record->broker_id[i]; }
  wire[at++] = record->filler;

  return at;
}

/* Gateway Router Request Message off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_gateway_router_request_message(GatewayRouterRequestMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->box_id[i] = wire[at++]; }
  for (size_t i = 0; i < 5; i++) { record->broker_id[i] = wire[at++]; }
  record->filler = wire[at++];

  return at;
}

/* what was read of Gateway Router Request Message is what was written, byte for byte */
static void equal_gateway_router_request_message(const GatewayRouterRequestMessage *read, const GatewayRouterRequestMessage *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->box_id[i] == written->box_id[i]); }
  for (size_t i = 0; i < 5; i++) { assert(read->broker_id[i] == written->broker_id[i]); }
  assert(read->filler == written->filler);
}

/* Gateway Router Request Message: written and read back, then read and written back */
static void check_gateway_router_request_message(void) {
  GatewayRouterRequestMessage sent;
  GatewayRouterRequestMessage got;
  uint8_t wire[8];
  uint8_t again[8];

  any_gateway_router_request_message(&sent);
  assert(encode_gateway_router_request_message(&sent, wire, 0) == 8);
  assert(decode_gateway_router_request_message(&got, wire, 0) == 8);
  equal_gateway_router_request_message(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_gateway_router_request_message(&got, wire, 0) == 8);
  assert(encode_gateway_router_request_message(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Secure Box Registration Request Message: 2 bytes ------------------------ */

/* Sent as SECURE_BOX_REGISTRATION_REQUEST_IN on the new connection to the allocated gateway server */
typedef struct {
  uint8_t box_id[2];  /* bytes 0 to 1 */
} SecureBoxRegistrationRequestMessage;

/* any Secure Box Registration Request Message at all: every byte one the checker chooses */
static void any_secure_box_registration_request_message(SecureBoxRegistrationRequestMessage *record) {
  for (size_t i = 0; i < 2; i++) { record->box_id[i] = arbitrary(); }
}

/* Secure Box Registration Request Message to the wire: 2 bytes from at, returning where the next byte goes */
static size_t encode_secure_box_registration_request_message(const SecureBoxRegistrationRequestMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->box_id[i]; }

  return at;
}

/* Secure Box Registration Request Message off the wire: 2 bytes from at, returning where the next byte lies */
static size_t decode_secure_box_registration_request_message(SecureBoxRegistrationRequestMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->box_id[i] = wire[at++]; }

  return at;
}

/* what was read of Secure Box Registration Request Message is what was written, byte for byte */
static void equal_secure_box_registration_request_message(const SecureBoxRegistrationRequestMessage *read, const SecureBoxRegistrationRequestMessage *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->box_id[i] == written->box_id[i]); }
}

/* Secure Box Registration Request Message: written and read back, then read and written back */
static void check_secure_box_registration_request_message(void) {
  SecureBoxRegistrationRequestMessage sent;
  SecureBoxRegistrationRequestMessage got;
  uint8_t wire[2];
  uint8_t again[2];

  any_secure_box_registration_request_message(&sent);
  assert(encode_secure_box_registration_request_message(&sent, wire, 0) == 2);
  assert(decode_secure_box_registration_request_message(&got, wire, 0) == 2);
  equal_secure_box_registration_request_message(&got, &sent);

  for (size_t i = 0; i < 2; i++) { wire[i] = arbitrary(); }
  assert(decode_secure_box_registration_request_message(&got, wire, 0) == 2);
  assert(encode_secure_box_registration_request_message(&got, again, 0) == 2);
  for (size_t i = 0; i < 2; i++) { assert(again[i] == wire[i]); }
}

/* ---- Box Sign On Request Message: 20 bytes ----------------------------------- */

/* Sent as BOX_SIGN_ON_REQUEST_IN, the first encrypted message on the box connection */
typedef struct {
  uint8_t box_id[2];       /* bytes 0 to 1 */
  uint8_t broker_id[5];    /* bytes 2 to 6 */
  uint8_t reserved_5[5];   /* bytes 7 to 11 */
  uint8_t session_key[8];  /* bytes 12 to 19 */
} BoxSignOnRequestMessage;

/* any Box Sign On Request Message at all: every byte one the checker chooses */
static void any_box_sign_on_request_message(BoxSignOnRequestMessage *record) {
  for (size_t i = 0; i < 2; i++) { record->box_id[i] = arbitrary(); }
  for (size_t i = 0; i < 5; i++) { record->broker_id[i] = arbitrary(); }
  for (size_t i = 0; i < 5; i++) { record->reserved_5[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->session_key[i] = arbitrary(); }
}

/* Box Sign On Request Message to the wire: 20 bytes from at, returning where the next byte goes */
static size_t encode_box_sign_on_request_message(const BoxSignOnRequestMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->box_id[i]; }
  for (size_t i = 0; i < 5; i++) { wire[at++] = record->broker_id[i]; }
  for (size_t i = 0; i < 5; i++) { wire[at++] = record->reserved_5[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->session_key[i]; }

  return at;
}

/* Box Sign On Request Message off the wire: 20 bytes from at, returning where the next byte lies */
static size_t decode_box_sign_on_request_message(BoxSignOnRequestMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->box_id[i] = wire[at++]; }
  for (size_t i = 0; i < 5; i++) { record->broker_id[i] = wire[at++]; }
  for (size_t i = 0; i < 5; i++) { record->reserved_5[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->session_key[i] = wire[at++]; }

  return at;
}

/* what was read of Box Sign On Request Message is what was written, byte for byte */
static void equal_box_sign_on_request_message(const BoxSignOnRequestMessage *read, const BoxSignOnRequestMessage *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->box_id[i] == written->box_id[i]); }
  for (size_t i = 0; i < 5; i++) { assert(read->broker_id[i] == written->broker_id[i]); }
  for (size_t i = 0; i < 5; i++) { assert(read->reserved_5[i] == written->reserved_5[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->session_key[i] == written->session_key[i]); }
}

/* Box Sign On Request Message: written and read back, then read and written back */
static void check_box_sign_on_request_message(void) {
  BoxSignOnRequestMessage sent;
  BoxSignOnRequestMessage got;
  uint8_t wire[20];
  uint8_t again[20];

  any_box_sign_on_request_message(&sent);
  assert(encode_box_sign_on_request_message(&sent, wire, 0) == 20);
  assert(decode_box_sign_on_request_message(&got, wire, 0) == 20);
  equal_box_sign_on_request_message(&got, &sent);

  for (size_t i = 0; i < 20; i++) { wire[i] = arbitrary(); }
  assert(decode_box_sign_on_request_message(&got, wire, 0) == 20);
  assert(encode_box_sign_on_request_message(&got, again, 0) == 20);
  for (size_t i = 0; i < 20; i++) { assert(again[i] == wire[i]); }
}

/* ---- What esbmc checks ------------------------------------------------------- */

/* every record of the protocol, each on its own buffers */
static void checks(void) {
  check_packet_header();
  check_message_header();
  check_update_local_database_request_message();
  check_sec_info();
  check_trade_cancellation_request_message();
  check_trade_modification_request_message();
  check_gateway_router_request_message();
  check_secure_box_registration_request_message();
  check_box_sign_on_request_message();
}

int main(void) {
#ifdef CONCRETE
  for (pattern = 0; pattern < 4; pattern++) { checks(); }
#else
  checks();
#endif

  return 0;
}
