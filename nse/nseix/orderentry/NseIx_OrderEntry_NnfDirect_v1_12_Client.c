// nse/nseix/orderentry/NseIx_OrderEntry_NnfDirect_v1_12_Client.c
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
 *   - a Integrity rule
 *   - a Composite rule
 *   - a field read in bits
 *   - a run of a stated number of entries
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

/* ---- Packet Header: 6 bytes -------------------------------------------------- */

/* Packet Length and Sequence number, the first six bytes of the direct interface's twenty two byte packet header; its last sixteen open each packet body branch */
typedef struct {
  uint8_t packet_length[2];           /* bytes 0 to 1 */
  uint8_t packet_sequence_number[4];  /* bytes 2 to 5 */
} PacketHeader;

/* any Packet Header at all: every byte one the checker chooses */
static void any_packet_header(PacketHeader *record) {
  for (size_t i = 0; i < 2; i++) { record->packet_length[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->packet_sequence_number[i] = arbitrary(); }
}

/* Packet Header to the wire: 6 bytes from at, returning where the next byte goes */
static size_t encode_packet_header(const PacketHeader *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->packet_length[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->packet_sequence_number[i]; }

  return at;
}

/* Packet Header off the wire: 6 bytes from at, returning where the next byte lies */
static size_t decode_packet_header(PacketHeader *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->packet_length[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->packet_sequence_number[i] = wire[at++]; }

  return at;
}

/* what was read of Packet Header is what was written, byte for byte */
static void equal_packet_header(const PacketHeader *read, const PacketHeader *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->packet_length[i] == written->packet_length[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->packet_sequence_number[i] == written->packet_sequence_number[i]); }
}

/* Packet Header: written and read back, then read and written back */
static void check_packet_header(void) {
  PacketHeader sent;
  PacketHeader got;
  uint8_t wire[6];
  uint8_t again[6];

  any_packet_header(&sent);
  assert(encode_packet_header(&sent, wire, 0) == 6);
  assert(decode_packet_header(&got, wire, 0) == 6);
  equal_packet_header(&got, &sent);

  for (size_t i = 0; i < 6; i++) { wire[i] = arbitrary(); }
  assert(decode_packet_header(&got, wire, 0) == 6);
  assert(encode_packet_header(&got, again, 0) == 6);
  for (size_t i = 0; i < 6; i++) { assert(again[i] == wire[i]); }
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

/* ---- System Information In Message: 4 bytes ---------------------------------- */

/* Requests the system information of the trading system */
typedef struct {
  uint8_t last_update_portfolio_time[4];  /* bytes 0 to 3 */
} SystemInformationInMessage;

/* any System Information In Message at all: every byte one the checker chooses */
static void any_system_information_in_message(SystemInformationInMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->last_update_portfolio_time[i] = arbitrary(); }
}

/* System Information In Message to the wire: 4 bytes from at, returning where the next byte goes */
static size_t encode_system_information_in_message(const SystemInformationInMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->last_update_portfolio_time[i]; }

  return at;
}

/* System Information In Message off the wire: 4 bytes from at, returning where the next byte lies */
static size_t decode_system_information_in_message(SystemInformationInMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->last_update_portfolio_time[i] = wire[at++]; }

  return at;
}

/* what was read of System Information In Message is what was written, byte for byte */
static void equal_system_information_in_message(const SystemInformationInMessage *read, const SystemInformationInMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->last_update_portfolio_time[i] == written->last_update_portfolio_time[i]); }
}

/* System Information In Message: written and read back, then read and written back */
static void check_system_information_in_message(void) {
  SystemInformationInMessage sent;
  SystemInformationInMessage got;
  uint8_t wire[4];
  uint8_t again[4];

  any_system_information_in_message(&sent);
  assert(encode_system_information_in_message(&sent, wire, 0) == 4);
  assert(decode_system_information_in_message(&got, wire, 0) == 4);
  equal_system_information_in_message(&got, &sent);

  for (size_t i = 0; i < 4; i++) { wire[i] = arbitrary(); }
  assert(decode_system_information_in_message(&got, wire, 0) == 4);
  assert(encode_system_information_in_message(&got, again, 0) == 4);
  for (size_t i = 0; i < 4; i++) { assert(again[i] == wire[i]); }
}

/* ---- St Market Status: 8 bytes ----------------------------------------------- */

/* ST_MARKET_STATUS */
typedef struct {
  uint8_t normal[2];   /* bytes 0 to 1 */
  uint8_t oddlot[2];   /* bytes 2 to 3 */
  uint8_t spot[2];     /* bytes 4 to 5 */
  uint8_t auction[2];  /* bytes 6 to 7 */
} StMarketStatus;

/* any St Market Status at all: every byte one the checker chooses */
static void any_st_market_status(StMarketStatus *record) {
  for (size_t i = 0; i < 2; i++) { record->normal[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->oddlot[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->spot[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->auction[i] = arbitrary(); }
}

/* St Market Status to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_st_market_status(const StMarketStatus *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->normal[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->oddlot[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->spot[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->auction[i]; }

  return at;
}

/* St Market Status off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_st_market_status(StMarketStatus *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->normal[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->oddlot[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->spot[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->auction[i] = wire[at++]; }

  return at;
}

/* what was read of St Market Status is what was written, byte for byte */
static void equal_st_market_status(const StMarketStatus *read, const StMarketStatus *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->normal[i] == written->normal[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->oddlot[i] == written->oddlot[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->spot[i] == written->spot[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->auction[i] == written->auction[i]); }
}

/* St Market Status: written and read back, then read and written back */
static void check_st_market_status(void) {
  StMarketStatus sent;
  StMarketStatus got;
  uint8_t wire[8];
  uint8_t again[8];

  any_st_market_status(&sent);
  assert(encode_st_market_status(&sent, wire, 0) == 8);
  assert(decode_st_market_status(&got, wire, 0) == 8);
  equal_st_market_status(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_st_market_status(&got, wire, 0) == 8);
  assert(encode_st_market_status(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- St Ex Market Status: 8 bytes -------------------------------------------- */

/* ST_EX_MARKET_STATUS */
typedef struct {
  uint8_t normal[2];   /* bytes 0 to 1 */
  uint8_t oddlot[2];   /* bytes 2 to 3 */
  uint8_t spot[2];     /* bytes 4 to 5 */
  uint8_t auction[2];  /* bytes 6 to 7 */
} StExMarketStatus;

/* any St Ex Market Status at all: every byte one the checker chooses */
static void any_st_ex_market_status(StExMarketStatus *record) {
  for (size_t i = 0; i < 2; i++) { record->normal[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->oddlot[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->spot[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->auction[i] = arbitrary(); }
}

/* St Ex Market Status to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_st_ex_market_status(const StExMarketStatus *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->normal[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->oddlot[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->spot[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->auction[i]; }

  return at;
}

/* St Ex Market Status off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_st_ex_market_status(StExMarketStatus *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->normal[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->oddlot[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->spot[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->auction[i] = wire[at++]; }

  return at;
}

/* what was read of St Ex Market Status is what was written, byte for byte */
static void equal_st_ex_market_status(const StExMarketStatus *read, const StExMarketStatus *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->normal[i] == written->normal[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->oddlot[i] == written->oddlot[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->spot[i] == written->spot[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->auction[i] == written->auction[i]); }
}

/* St Ex Market Status: written and read back, then read and written back */
static void check_st_ex_market_status(void) {
  StExMarketStatus sent;
  StExMarketStatus got;
  uint8_t wire[8];
  uint8_t again[8];

  any_st_ex_market_status(&sent);
  assert(encode_st_ex_market_status(&sent, wire, 0) == 8);
  assert(decode_st_ex_market_status(&got, wire, 0) == 8);
  equal_st_ex_market_status(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_st_ex_market_status(&got, wire, 0) == 8);
  assert(encode_st_ex_market_status(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- St Pl Market Status: 8 bytes -------------------------------------------- */

/* ST_PL_MARKET_STATUS */
typedef struct {
  uint8_t normal[2];   /* bytes 0 to 1 */
  uint8_t oddlot[2];   /* bytes 2 to 3 */
  uint8_t spot[2];     /* bytes 4 to 5 */
  uint8_t auction[2];  /* bytes 6 to 7 */
} StPlMarketStatus;

/* any St Pl Market Status at all: every byte one the checker chooses */
static void any_st_pl_market_status(StPlMarketStatus *record) {
  for (size_t i = 0; i < 2; i++) { record->normal[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->oddlot[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->spot[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->auction[i] = arbitrary(); }
}

/* St Pl Market Status to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_st_pl_market_status(const StPlMarketStatus *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->normal[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->oddlot[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->spot[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->auction[i]; }

  return at;
}

/* St Pl Market Status off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_st_pl_market_status(StPlMarketStatus *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->normal[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->oddlot[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->spot[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->auction[i] = wire[at++]; }

  return at;
}

/* what was read of St Pl Market Status is what was written, byte for byte */
static void equal_st_pl_market_status(const StPlMarketStatus *read, const StPlMarketStatus *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->normal[i] == written->normal[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->oddlot[i] == written->oddlot[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->spot[i] == written->spot[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->auction[i] == written->auction[i]); }
}

/* St Pl Market Status: written and read back, then read and written back */
static void check_st_pl_market_status(void) {
  StPlMarketStatus sent;
  StPlMarketStatus got;
  uint8_t wire[8];
  uint8_t again[8];

  any_st_pl_market_status(&sent);
  assert(encode_st_pl_market_status(&sent, wire, 0) == 8);
  assert(decode_st_pl_market_status(&got, wire, 0) == 8);
  equal_st_pl_market_status(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_st_pl_market_status(&got, wire, 0) == 8);
  assert(encode_st_pl_market_status(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Update Local Database In Message: 42 bytes ------------------------------ */

/* Requests the local database download of securities, participants and open orders */
typedef struct {
  uint8_t last_update_security_time[4];     /* bytes 0 to 3 */
  uint8_t last_update_participant_time[4];  /* bytes 4 to 7 */
  uint8_t last_update_instrument_time[4];   /* bytes 8 to 11 */
  uint8_t last_update_index_time[4];        /* bytes 12 to 15 */
  uint8_t request_for_open_orders;          /* byte 16 */
  uint8_t c_filler;                         /* byte 17 */
  StMarketStatus st_market_status;          /* bytes 18 to 25 */
  StExMarketStatus st_ex_market_status;     /* bytes 26 to 33 */
  StPlMarketStatus st_pl_market_status;     /* bytes 34 to 41 */
} UpdateLocalDatabaseInMessage;

/* any Update Local Database In Message at all: every byte one the checker chooses */
static void any_update_local_database_in_message(UpdateLocalDatabaseInMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->last_update_security_time[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->last_update_participant_time[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->last_update_instrument_time[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->last_update_index_time[i] = arbitrary(); }
  record->request_for_open_orders = arbitrary();
  record->c_filler = arbitrary();
  any_st_market_status(&record->st_market_status);
  any_st_ex_market_status(&record->st_ex_market_status);
  any_st_pl_market_status(&record->st_pl_market_status);
}

/* Update Local Database In Message to the wire: 42 bytes from at, returning where the next byte goes */
static size_t encode_update_local_database_in_message(const UpdateLocalDatabaseInMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->last_update_security_time[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->last_update_participant_time[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->last_update_instrument_time[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->last_update_index_time[i]; }
  wire[at++] = record->request_for_open_orders;
  wire[at++] = record->c_filler;
  at = encode_st_market_status(&record->st_market_status, wire, at);
  at = encode_st_ex_market_status(&record->st_ex_market_status, wire, at);
  at = encode_st_pl_market_status(&record->st_pl_market_status, wire, at);

  return at;
}

/* Update Local Database In Message off the wire: 42 bytes from at, returning where the next byte lies */
static size_t decode_update_local_database_in_message(UpdateLocalDatabaseInMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->last_update_security_time[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->last_update_participant_time[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->last_update_instrument_time[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->last_update_index_time[i] = wire[at++]; }
  record->request_for_open_orders = wire[at++];
  record->c_filler = wire[at++];
  at = decode_st_market_status(&record->st_market_status, wire, at);
  at = decode_st_ex_market_status(&record->st_ex_market_status, wire, at);
  at = decode_st_pl_market_status(&record->st_pl_market_status, wire, at);

  return at;
}

/* what was read of Update Local Database In Message is what was written, byte for byte */
static void equal_update_local_database_in_message(const UpdateLocalDatabaseInMessage *read, const UpdateLocalDatabaseInMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->last_update_security_time[i] == written->last_update_security_time[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->last_update_participant_time[i] == written->last_update_participant_time[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->last_update_instrument_time[i] == written->last_update_instrument_time[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->last_update_index_time[i] == written->last_update_index_time[i]); }
  assert(read->request_for_open_orders == written->request_for_open_orders);
  assert(read->c_filler == written->c_filler);
  equal_st_market_status(&read->st_market_status, &written->st_market_status);
  equal_st_ex_market_status(&read->st_ex_market_status, &written->st_ex_market_status);
  equal_st_pl_market_status(&read->st_pl_market_status, &written->st_pl_market_status);
}

/* Update Local Database In Message: written and read back, then read and written back */
static void check_update_local_database_in_message(void) {
  UpdateLocalDatabaseInMessage sent;
  UpdateLocalDatabaseInMessage got;
  uint8_t wire[42];
  uint8_t again[42];

  any_update_local_database_in_message(&sent);
  assert(encode_update_local_database_in_message(&sent, wire, 0) == 42);
  assert(decode_update_local_database_in_message(&got, wire, 0) == 42);
  equal_update_local_database_in_message(&got, &sent);

  for (size_t i = 0; i < 42; i++) { wire[i] = arbitrary(); }
  assert(decode_update_local_database_in_message(&got, wire, 0) == 42);
  assert(encode_update_local_database_in_message(&got, again, 0) == 42);
  for (size_t i = 0; i < 42; i++) { assert(again[i] == wire[i]); }
}

/* ---- Contract Desc: 28 bytes ------------------------------------------------- */

/* CONTRACT_DESC */
typedef struct {
  uint8_t instrument_name[6];  /* bytes 0 to 5 */
  uint8_t symbol[10];          /* bytes 6 to 15 */
  uint8_t expiry_date[4];      /* bytes 16 to 19 */
  uint8_t strike_price[4];     /* bytes 20 to 23 */
  uint8_t option_type[2];      /* bytes 24 to 25 */
  uint8_t ca_level[2];         /* bytes 26 to 27 */
} ContractDesc;

/* any Contract Desc at all: every byte one the checker chooses */
static void any_contract_desc(ContractDesc *record) {
  for (size_t i = 0; i < 6; i++) { record->instrument_name[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->symbol[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->expiry_date[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->strike_price[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->option_type[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->ca_level[i] = arbitrary(); }
}

/* Contract Desc to the wire: 28 bytes from at, returning where the next byte goes */
static size_t encode_contract_desc(const ContractDesc *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->instrument_name[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->symbol[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->expiry_date[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->strike_price[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->option_type[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->ca_level[i]; }

  return at;
}

/* Contract Desc off the wire: 28 bytes from at, returning where the next byte lies */
static size_t decode_contract_desc(ContractDesc *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 6; i++) { record->instrument_name[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->symbol[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->expiry_date[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->strike_price[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->option_type[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->ca_level[i] = wire[at++]; }

  return at;
}

/* what was read of Contract Desc is what was written, byte for byte */
static void equal_contract_desc(const ContractDesc *read, const ContractDesc *written) {
  for (size_t i = 0; i < 6; i++) { assert(read->instrument_name[i] == written->instrument_name[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->symbol[i] == written->symbol[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->expiry_date[i] == written->expiry_date[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->strike_price[i] == written->strike_price[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->option_type[i] == written->option_type[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->ca_level[i] == written->ca_level[i]); }
}

/* Contract Desc: written and read back, then read and written back */
static void check_contract_desc(void) {
  ContractDesc sent;
  ContractDesc got;
  uint8_t wire[28];
  uint8_t again[28];

  any_contract_desc(&sent);
  assert(encode_contract_desc(&sent, wire, 0) == 28);
  assert(decode_contract_desc(&got, wire, 0) == 28);
  equal_contract_desc(&got, &sent);

  for (size_t i = 0; i < 28; i++) { wire[i] = arbitrary(); }
  assert(decode_contract_desc(&got, wire, 0) == 28);
  assert(encode_contract_desc(&got, again, 0) == 28);
  for (size_t i = 0; i < 28; i++) { assert(again[i] == wire[i]); }
}

/* ---- Trade Inquiry Body: 194 bytes ------------------------------------------- */

/* Trade Inquiry Body */
typedef struct {
  uint8_t token_no[4];              /* bytes 0 to 3 */
  ContractDesc contract_desc;       /* bytes 4 to 31 */
  uint8_t fill_number[4];           /* bytes 32 to 35 */
  uint8_t fill_quantity[4];         /* bytes 36 to 39 */
  uint8_t fill_price[4];            /* bytes 40 to 43 */
  uint8_t mkt_type;                 /* byte 44 */
  uint8_t buy_open_close;           /* byte 45 */
  uint8_t new_volume[4];            /* bytes 46 to 49 */
  uint8_t buy_broker_id[5];         /* bytes 50 to 54 */
  uint8_t sell_broker_id[5];        /* bytes 55 to 59 */
  uint8_t trader_id[4];             /* bytes 60 to 63 */
  uint8_t requested_by;             /* byte 64 */
  uint8_t sell_open_close;          /* byte 65 */
  uint8_t buy_account_number[10];   /* bytes 66 to 75 */
  uint8_t sell_account_number[10];  /* bytes 76 to 85 */
  uint8_t buy_participant[12];      /* bytes 86 to 97 */
  uint8_t sell_participant[12];     /* bytes 98 to 109 */
  uint8_t reserved_2[2];            /* bytes 110 to 111 */
  uint8_t buy_giveup_flag;          /* byte 112 */
  uint8_t sell_giveup_flag;         /* byte 113 */
  uint8_t reserved_80[80];          /* bytes 114 to 193 */
} TradeInquiryBody;

/* any Trade Inquiry Body at all: every byte one the checker chooses */
static void any_trade_inquiry_body(TradeInquiryBody *record) {
  for (size_t i = 0; i < 4; i++) { record->token_no[i] = arbitrary(); }
  any_contract_desc(&record->contract_desc);
  for (size_t i = 0; i < 4; i++) { record->fill_number[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->fill_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->fill_price[i] = arbitrary(); }
  record->mkt_type = arbitrary();
  record->buy_open_close = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->new_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 5; i++) { record->buy_broker_id[i] = arbitrary(); }
  for (size_t i = 0; i < 5; i++) { record->sell_broker_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->trader_id[i] = arbitrary(); }
  record->requested_by = arbitrary();
  record->sell_open_close = arbitrary();
  for (size_t i = 0; i < 10; i++) { record->buy_account_number[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->sell_account_number[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->buy_participant[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->sell_participant[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->reserved_2[i] = arbitrary(); }
  record->buy_giveup_flag = arbitrary();
  record->sell_giveup_flag = arbitrary();
  for (size_t i = 0; i < 80; i++) { record->reserved_80[i] = arbitrary(); }
}

/* Trade Inquiry Body to the wire: 194 bytes from at, returning where the next byte goes */
static size_t encode_trade_inquiry_body(const TradeInquiryBody *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->token_no[i]; }
  at = encode_contract_desc(&record->contract_desc, wire, at);
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->fill_number[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->fill_quantity[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->fill_price[i]; }
  wire[at++] = record->mkt_type;
  wire[at++] = record->buy_open_close;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->new_volume[i]; }
  for (size_t i = 0; i < 5; i++) { wire[at++] = record->buy_broker_id[i]; }
  for (size_t i = 0; i < 5; i++) { wire[at++] = record->sell_broker_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->trader_id[i]; }
  wire[at++] = record->requested_by;
  wire[at++] = record->sell_open_close;
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->buy_account_number[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->sell_account_number[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->buy_participant[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->sell_participant[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->reserved_2[i]; }
  wire[at++] = record->buy_giveup_flag;
  wire[at++] = record->sell_giveup_flag;
  for (size_t i = 0; i < 80; i++) { wire[at++] = record->reserved_80[i]; }

  return at;
}

/* Trade Inquiry Body off the wire: 194 bytes from at, returning where the next byte lies */
static size_t decode_trade_inquiry_body(TradeInquiryBody *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->token_no[i] = wire[at++]; }
  at = decode_contract_desc(&record->contract_desc, wire, at);
  for (size_t i = 0; i < 4; i++) { record->fill_number[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->fill_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->fill_price[i] = wire[at++]; }
  record->mkt_type = wire[at++];
  record->buy_open_close = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->new_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 5; i++) { record->buy_broker_id[i] = wire[at++]; }
  for (size_t i = 0; i < 5; i++) { record->sell_broker_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->trader_id[i] = wire[at++]; }
  record->requested_by = wire[at++];
  record->sell_open_close = wire[at++];
  for (size_t i = 0; i < 10; i++) { record->buy_account_number[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->sell_account_number[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->buy_participant[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->sell_participant[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->reserved_2[i] = wire[at++]; }
  record->buy_giveup_flag = wire[at++];
  record->sell_giveup_flag = wire[at++];
  for (size_t i = 0; i < 80; i++) { record->reserved_80[i] = wire[at++]; }

  return at;
}

/* what was read of Trade Inquiry Body is what was written, byte for byte */
static void equal_trade_inquiry_body(const TradeInquiryBody *read, const TradeInquiryBody *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->token_no[i] == written->token_no[i]); }
  equal_contract_desc(&read->contract_desc, &written->contract_desc);
  for (size_t i = 0; i < 4; i++) { assert(read->fill_number[i] == written->fill_number[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->fill_quantity[i] == written->fill_quantity[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->fill_price[i] == written->fill_price[i]); }
  assert(read->mkt_type == written->mkt_type);
  assert(read->buy_open_close == written->buy_open_close);
  for (size_t i = 0; i < 4; i++) { assert(read->new_volume[i] == written->new_volume[i]); }
  for (size_t i = 0; i < 5; i++) { assert(read->buy_broker_id[i] == written->buy_broker_id[i]); }
  for (size_t i = 0; i < 5; i++) { assert(read->sell_broker_id[i] == written->sell_broker_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->trader_id[i] == written->trader_id[i]); }
  assert(read->requested_by == written->requested_by);
  assert(read->sell_open_close == written->sell_open_close);
  for (size_t i = 0; i < 10; i++) { assert(read->buy_account_number[i] == written->buy_account_number[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->sell_account_number[i] == written->sell_account_number[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->buy_participant[i] == written->buy_participant[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->sell_participant[i] == written->sell_participant[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->reserved_2[i] == written->reserved_2[i]); }
  assert(read->buy_giveup_flag == written->buy_giveup_flag);
  assert(read->sell_giveup_flag == written->sell_giveup_flag);
  for (size_t i = 0; i < 80; i++) { assert(read->reserved_80[i] == written->reserved_80[i]); }
}

/* Trade Inquiry Body: written and read back, then read and written back */
static void check_trade_inquiry_body(void) {
  TradeInquiryBody sent;
  TradeInquiryBody got;
  uint8_t wire[194];
  uint8_t again[194];

  any_trade_inquiry_body(&sent);
  assert(encode_trade_inquiry_body(&sent, wire, 0) == 194);
  assert(decode_trade_inquiry_body(&got, wire, 0) == 194);
  equal_trade_inquiry_body(&got, &sent);

  for (size_t i = 0; i < 194; i++) { wire[i] = arbitrary(); }
  assert(decode_trade_inquiry_body(&got, wire, 0) == 194);
  assert(encode_trade_inquiry_body(&got, again, 0) == 194);
  for (size_t i = 0; i < 194; i++) { assert(again[i] == wire[i]); }
}

/* ---- Trade Inquiry Message: 194 bytes ---------------------------------------- */

/* Trade modification and cancellation requests, including the negotiated large trade forms, carried in the shared trade structure */
typedef struct {
  TradeInquiryBody trade_inquiry_body;  /* bytes 0 to 193 */
} TradeInquiryMessage;

/* any Trade Inquiry Message at all: every byte one the checker chooses */
static void any_trade_inquiry_message(TradeInquiryMessage *record) {
  any_trade_inquiry_body(&record->trade_inquiry_body);
}

/* Trade Inquiry Message to the wire: 194 bytes from at, returning where the next byte goes */
static size_t encode_trade_inquiry_message(const TradeInquiryMessage *record, uint8_t *wire, size_t at) {
  at = encode_trade_inquiry_body(&record->trade_inquiry_body, wire, at);

  return at;
}

/* Trade Inquiry Message off the wire: 194 bytes from at, returning where the next byte lies */
static size_t decode_trade_inquiry_message(TradeInquiryMessage *record, const uint8_t *wire, size_t at) {
  at = decode_trade_inquiry_body(&record->trade_inquiry_body, wire, at);

  return at;
}

/* what was read of Trade Inquiry Message is what was written, byte for byte */
static void equal_trade_inquiry_message(const TradeInquiryMessage *read, const TradeInquiryMessage *written) {
  equal_trade_inquiry_body(&read->trade_inquiry_body, &written->trade_inquiry_body);
}

/* Trade Inquiry Message: written and read back, then read and written back */
static void check_trade_inquiry_message(void) {
  TradeInquiryMessage sent;
  TradeInquiryMessage got;
  uint8_t wire[194];
  uint8_t again[194];

  any_trade_inquiry_message(&sent);
  assert(encode_trade_inquiry_message(&sent, wire, 0) == 194);
  assert(decode_trade_inquiry_message(&got, wire, 0) == 194);
  equal_trade_inquiry_message(&got, &sent);

  for (size_t i = 0; i < 194; i++) { wire[i] = arbitrary(); }
  assert(decode_trade_inquiry_message(&got, wire, 0) == 194);
  assert(encode_trade_inquiry_message(&got, again, 0) == 194);
  for (size_t i = 0; i < 194; i++) { assert(again[i] == wire[i]); }
}

/* ---- Gateway Router Request Message: 8 bytes --------------------------------- */

/* Asks the gateway router which gateway server to connect to */
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

/* ---- Secure Box Registration Request In Message: 2 bytes --------------------- */

/* Registers the box with the allocated gateway server */
typedef struct {
  uint8_t box_id[2];  /* bytes 0 to 1 */
} SecureBoxRegistrationRequestInMessage;

/* any Secure Box Registration Request In Message at all: every byte one the checker chooses */
static void any_secure_box_registration_request_in_message(SecureBoxRegistrationRequestInMessage *record) {
  for (size_t i = 0; i < 2; i++) { record->box_id[i] = arbitrary(); }
}

/* Secure Box Registration Request In Message to the wire: 2 bytes from at, returning where the next byte goes */
static size_t encode_secure_box_registration_request_in_message(const SecureBoxRegistrationRequestInMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->box_id[i]; }

  return at;
}

/* Secure Box Registration Request In Message off the wire: 2 bytes from at, returning where the next byte lies */
static size_t decode_secure_box_registration_request_in_message(SecureBoxRegistrationRequestInMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->box_id[i] = wire[at++]; }

  return at;
}

/* what was read of Secure Box Registration Request In Message is what was written, byte for byte */
static void equal_secure_box_registration_request_in_message(const SecureBoxRegistrationRequestInMessage *read, const SecureBoxRegistrationRequestInMessage *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->box_id[i] == written->box_id[i]); }
}

/* Secure Box Registration Request In Message: written and read back, then read and written back */
static void check_secure_box_registration_request_in_message(void) {
  SecureBoxRegistrationRequestInMessage sent;
  SecureBoxRegistrationRequestInMessage got;
  uint8_t wire[2];
  uint8_t again[2];

  any_secure_box_registration_request_in_message(&sent);
  assert(encode_secure_box_registration_request_in_message(&sent, wire, 0) == 2);
  assert(decode_secure_box_registration_request_in_message(&got, wire, 0) == 2);
  equal_secure_box_registration_request_in_message(&got, &sent);

  for (size_t i = 0; i < 2; i++) { wire[i] = arbitrary(); }
  assert(decode_secure_box_registration_request_in_message(&got, wire, 0) == 2);
  assert(encode_secure_box_registration_request_in_message(&got, again, 0) == 2);
  for (size_t i = 0; i < 2; i++) { assert(again[i] == wire[i]); }
}

/* ---- Box Sign On Request In Message: 20 bytes -------------------------------- */

/* Signs the box on to the allocated gateway server */
typedef struct {
  uint8_t box_id[2];       /* bytes 0 to 1 */
  uint8_t broker_id[5];    /* bytes 2 to 6 */
  uint8_t reserved_5[5];   /* bytes 7 to 11 */
  uint8_t session_key[8];  /* bytes 12 to 19 */
} BoxSignOnRequestInMessage;

/* any Box Sign On Request In Message at all: every byte one the checker chooses */
static void any_box_sign_on_request_in_message(BoxSignOnRequestInMessage *record) {
  for (size_t i = 0; i < 2; i++) { record->box_id[i] = arbitrary(); }
  for (size_t i = 0; i < 5; i++) { record->broker_id[i] = arbitrary(); }
  for (size_t i = 0; i < 5; i++) { record->reserved_5[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->session_key[i] = arbitrary(); }
}

/* Box Sign On Request In Message to the wire: 20 bytes from at, returning where the next byte goes */
static size_t encode_box_sign_on_request_in_message(const BoxSignOnRequestInMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->box_id[i]; }
  for (size_t i = 0; i < 5; i++) { wire[at++] = record->broker_id[i]; }
  for (size_t i = 0; i < 5; i++) { wire[at++] = record->reserved_5[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->session_key[i]; }

  return at;
}

/* Box Sign On Request In Message off the wire: 20 bytes from at, returning where the next byte lies */
static size_t decode_box_sign_on_request_in_message(BoxSignOnRequestInMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->box_id[i] = wire[at++]; }
  for (size_t i = 0; i < 5; i++) { record->broker_id[i] = wire[at++]; }
  for (size_t i = 0; i < 5; i++) { record->reserved_5[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->session_key[i] = wire[at++]; }

  return at;
}

/* what was read of Box Sign On Request In Message is what was written, byte for byte */
static void equal_box_sign_on_request_in_message(const BoxSignOnRequestInMessage *read, const BoxSignOnRequestInMessage *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->box_id[i] == written->box_id[i]); }
  for (size_t i = 0; i < 5; i++) { assert(read->broker_id[i] == written->broker_id[i]); }
  for (size_t i = 0; i < 5; i++) { assert(read->reserved_5[i] == written->reserved_5[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->session_key[i] == written->session_key[i]); }
}

/* Box Sign On Request In Message: written and read back, then read and written back */
static void check_box_sign_on_request_in_message(void) {
  BoxSignOnRequestInMessage sent;
  BoxSignOnRequestInMessage got;
  uint8_t wire[20];
  uint8_t again[20];

  any_box_sign_on_request_in_message(&sent);
  assert(encode_box_sign_on_request_in_message(&sent, wire, 0) == 20);
  assert(decode_box_sign_on_request_in_message(&got, wire, 0) == 20);
  equal_box_sign_on_request_in_message(&got, &sent);

  for (size_t i = 0; i < 20; i++) { wire[i] = arbitrary(); }
  assert(decode_box_sign_on_request_in_message(&got, wire, 0) == 20);
  assert(encode_box_sign_on_request_in_message(&got, again, 0) == 20);
  for (size_t i = 0; i < 20; i++) { assert(again[i] == wire[i]); }
}

/* ---- Reset User Password Message: 18 bytes ----------------------------------- */

/* Requests a reset of a user's password to the default */
typedef struct {
  uint8_t user_id[4];       /* bytes 0 to 3 */
  uint8_t reserved_14[14];  /* bytes 4 to 17 */
} ResetUserPasswordMessage;

/* any Reset User Password Message at all: every byte one the checker chooses */
static void any_reset_user_password_message(ResetUserPasswordMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->user_id[i] = arbitrary(); }
  for (size_t i = 0; i < 14; i++) { record->reserved_14[i] = arbitrary(); }
}

/* Reset User Password Message to the wire: 18 bytes from at, returning where the next byte goes */
static size_t encode_reset_user_password_message(const ResetUserPasswordMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->user_id[i]; }
  for (size_t i = 0; i < 14; i++) { wire[at++] = record->reserved_14[i]; }

  return at;
}

/* Reset User Password Message off the wire: 18 bytes from at, returning where the next byte lies */
static size_t decode_reset_user_password_message(ResetUserPasswordMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->user_id[i] = wire[at++]; }
  for (size_t i = 0; i < 14; i++) { record->reserved_14[i] = wire[at++]; }

  return at;
}

/* what was read of Reset User Password Message is what was written, byte for byte */
static void equal_reset_user_password_message(const ResetUserPasswordMessage *read, const ResetUserPasswordMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->user_id[i] == written->user_id[i]); }
  for (size_t i = 0; i < 14; i++) { assert(read->reserved_14[i] == written->reserved_14[i]); }
}

/* Reset User Password Message: written and read back, then read and written back */
static void check_reset_user_password_message(void) {
  ResetUserPasswordMessage sent;
  ResetUserPasswordMessage got;
  uint8_t wire[18];
  uint8_t again[18];

  any_reset_user_password_message(&sent);
  assert(encode_reset_user_password_message(&sent, wire, 0) == 18);
  assert(decode_reset_user_password_message(&got, wire, 0) == 18);
  equal_reset_user_password_message(&got, &sent);

  for (size_t i = 0; i < 18; i++) { wire[i] = arbitrary(); }
  assert(decode_reset_user_password_message(&got, wire, 0) == 18);
  assert(encode_reset_user_password_message(&got, again, 0) == 18);
  for (size_t i = 0; i < 18; i++) { assert(again[i] == wire[i]); }
}

/* ---- Collateral User Status Change Request Message: 12 bytes ----------------- */

/* Enables or disables cancel on logout for a user */
typedef struct {
  uint8_t user_id[4];     /* bytes 0 to 3 */
  uint8_t col_user_bit;   /* byte 4 */
  uint8_t reserved_7[7];  /* bytes 5 to 11 */
} CollateralUserStatusChangeRequestMessage;

/* any Collateral User Status Change Request Message at all: every byte one the checker chooses */
static void any_collateral_user_status_change_request_message(CollateralUserStatusChangeRequestMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->user_id[i] = arbitrary(); }
  record->col_user_bit = arbitrary();
  for (size_t i = 0; i < 7; i++) { record->reserved_7[i] = arbitrary(); }
}

/* Collateral User Status Change Request Message to the wire: 12 bytes from at, returning where the next byte goes */
static size_t encode_collateral_user_status_change_request_message(const CollateralUserStatusChangeRequestMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->user_id[i]; }
  wire[at++] = record->col_user_bit;
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->reserved_7[i]; }

  return at;
}

/* Collateral User Status Change Request Message off the wire: 12 bytes from at, returning where the next byte lies */
static size_t decode_collateral_user_status_change_request_message(CollateralUserStatusChangeRequestMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->user_id[i] = wire[at++]; }
  record->col_user_bit = wire[at++];
  for (size_t i = 0; i < 7; i++) { record->reserved_7[i] = wire[at++]; }

  return at;
}

/* what was read of Collateral User Status Change Request Message is what was written, byte for byte */
static void equal_collateral_user_status_change_request_message(const CollateralUserStatusChangeRequestMessage *read, const CollateralUserStatusChangeRequestMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->user_id[i] == written->user_id[i]); }
  assert(read->col_user_bit == written->col_user_bit);
  for (size_t i = 0; i < 7; i++) { assert(read->reserved_7[i] == written->reserved_7[i]); }
}

/* Collateral User Status Change Request Message: written and read back, then read and written back */
static void check_collateral_user_status_change_request_message(void) {
  CollateralUserStatusChangeRequestMessage sent;
  CollateralUserStatusChangeRequestMessage got;
  uint8_t wire[12];
  uint8_t again[12];

  any_collateral_user_status_change_request_message(&sent);
  assert(encode_collateral_user_status_change_request_message(&sent, wire, 0) == 12);
  assert(decode_collateral_user_status_change_request_message(&got, wire, 0) == 12);
  equal_collateral_user_status_change_request_message(&got, &sent);

  for (size_t i = 0; i < 12; i++) { wire[i] = arbitrary(); }
  assert(decode_collateral_user_status_change_request_message(&got, wire, 0) == 12);
  assert(encode_collateral_user_status_change_request_message(&got, again, 0) == 12);
  for (size_t i = 0; i < 12; i++) { assert(again[i] == wire[i]); }
}

/* ---- User Trade Modify Cancel Status Change Request Message: 12 bytes -------- */

/* Enables or disables trade modification or, with Alpha Char TX, trade cancellation for a user */
typedef struct {
  uint8_t user_id[4];       /* bytes 0 to 3 */
  uint8_t trd_mod_cxl_bit;  /* byte 4 */
  uint8_t reserved_7[7];    /* bytes 5 to 11 */
} UserTradeModifyCancelStatusChangeRequestMessage;

/* any User Trade Modify Cancel Status Change Request Message at all: every byte one the checker chooses */
static void any_user_trade_modify_cancel_status_change_request_message(UserTradeModifyCancelStatusChangeRequestMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->user_id[i] = arbitrary(); }
  record->trd_mod_cxl_bit = arbitrary();
  for (size_t i = 0; i < 7; i++) { record->reserved_7[i] = arbitrary(); }
}

/* User Trade Modify Cancel Status Change Request Message to the wire: 12 bytes from at, returning where the next byte goes */
static size_t encode_user_trade_modify_cancel_status_change_request_message(const UserTradeModifyCancelStatusChangeRequestMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->user_id[i]; }
  wire[at++] = record->trd_mod_cxl_bit;
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->reserved_7[i]; }

  return at;
}

/* User Trade Modify Cancel Status Change Request Message off the wire: 12 bytes from at, returning where the next byte lies */
static size_t decode_user_trade_modify_cancel_status_change_request_message(UserTradeModifyCancelStatusChangeRequestMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->user_id[i] = wire[at++]; }
  record->trd_mod_cxl_bit = wire[at++];
  for (size_t i = 0; i < 7; i++) { record->reserved_7[i] = wire[at++]; }

  return at;
}

/* what was read of User Trade Modify Cancel Status Change Request Message is what was written, byte for byte */
static void equal_user_trade_modify_cancel_status_change_request_message(const UserTradeModifyCancelStatusChangeRequestMessage *read, const UserTradeModifyCancelStatusChangeRequestMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->user_id[i] == written->user_id[i]); }
  assert(read->trd_mod_cxl_bit == written->trd_mod_cxl_bit);
  for (size_t i = 0; i < 7; i++) { assert(read->reserved_7[i] == written->reserved_7[i]); }
}

/* User Trade Modify Cancel Status Change Request Message: written and read back, then read and written back */
static void check_user_trade_modify_cancel_status_change_request_message(void) {
  UserTradeModifyCancelStatusChangeRequestMessage sent;
  UserTradeModifyCancelStatusChangeRequestMessage got;
  uint8_t wire[12];
  uint8_t again[12];

  any_user_trade_modify_cancel_status_change_request_message(&sent);
  assert(encode_user_trade_modify_cancel_status_change_request_message(&sent, wire, 0) == 12);
  assert(decode_user_trade_modify_cancel_status_change_request_message(&got, wire, 0) == 12);
  equal_user_trade_modify_cancel_status_change_request_message(&got, &sent);

  for (size_t i = 0; i < 12; i++) { wire[i] = arbitrary(); }
  assert(decode_user_trade_modify_cancel_status_change_request_message(&got, wire, 0) == 12);
  assert(encode_user_trade_modify_cancel_status_change_request_message(&got, again, 0) == 12);
  for (size_t i = 0; i < 12; i++) { assert(again[i] == wire[i]); }
}

/* ---- User Address Unlock Request Message: 74 bytes --------------------------- */

/* Requests that a locked user be unlocked */
typedef struct {
  uint8_t user_id[4];       /* bytes 0 to 3 */
  uint8_t reserved_70[70];  /* bytes 4 to 73 */
} UserAddressUnlockRequestMessage;

/* any User Address Unlock Request Message at all: every byte one the checker chooses */
static void any_user_address_unlock_request_message(UserAddressUnlockRequestMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->user_id[i] = arbitrary(); }
  for (size_t i = 0; i < 70; i++) { record->reserved_70[i] = arbitrary(); }
}

/* User Address Unlock Request Message to the wire: 74 bytes from at, returning where the next byte goes */
static size_t encode_user_address_unlock_request_message(const UserAddressUnlockRequestMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->user_id[i]; }
  for (size_t i = 0; i < 70; i++) { wire[at++] = record->reserved_70[i]; }

  return at;
}

/* User Address Unlock Request Message off the wire: 74 bytes from at, returning where the next byte lies */
static size_t decode_user_address_unlock_request_message(UserAddressUnlockRequestMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->user_id[i] = wire[at++]; }
  for (size_t i = 0; i < 70; i++) { record->reserved_70[i] = wire[at++]; }

  return at;
}

/* what was read of User Address Unlock Request Message is what was written, byte for byte */
static void equal_user_address_unlock_request_message(const UserAddressUnlockRequestMessage *read, const UserAddressUnlockRequestMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->user_id[i] == written->user_id[i]); }
  for (size_t i = 0; i < 70; i++) { assert(read->reserved_70[i] == written->reserved_70[i]); }
}

/* User Address Unlock Request Message: written and read back, then read and written back */
static void check_user_address_unlock_request_message(void) {
  UserAddressUnlockRequestMessage sent;
  UserAddressUnlockRequestMessage got;
  uint8_t wire[74];
  uint8_t again[74];

  any_user_address_unlock_request_message(&sent);
  assert(encode_user_address_unlock_request_message(&sent, wire, 0) == 74);
  assert(decode_user_address_unlock_request_message(&got, wire, 0) == 74);
  equal_user_address_unlock_request_message(&got, &sent);

  for (size_t i = 0; i < 74; i++) { wire[i] = arbitrary(); }
  assert(decode_user_address_unlock_request_message(&got, wire, 0) == 74);
  assert(encode_user_address_unlock_request_message(&got, again, 0) == 74);
  for (size_t i = 0; i < 74; i++) { assert(again[i] == wire[i]); }
}

/* ---- Nlt Order Inquiry Request Message: 6 bytes ------------------------------ */

/* One time inquiry by a corporate manager for the negotiated large trade counter orders placed against the member */
typedef struct {
  uint8_t broker_id[5];  /* bytes 0 to 4 */
  uint8_t reserved_1;    /* byte 5 */
} NltOrderInquiryRequestMessage;

/* any Nlt Order Inquiry Request Message at all: every byte one the checker chooses */
static void any_nlt_order_inquiry_request_message(NltOrderInquiryRequestMessage *record) {
  for (size_t i = 0; i < 5; i++) { record->broker_id[i] = arbitrary(); }
  record->reserved_1 = arbitrary();
}

/* Nlt Order Inquiry Request Message to the wire: 6 bytes from at, returning where the next byte goes */
static size_t encode_nlt_order_inquiry_request_message(const NltOrderInquiryRequestMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 5; i++) { wire[at++] = record->broker_id[i]; }
  wire[at++] = record->reserved_1;

  return at;
}

/* Nlt Order Inquiry Request Message off the wire: 6 bytes from at, returning where the next byte lies */
static size_t decode_nlt_order_inquiry_request_message(NltOrderInquiryRequestMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 5; i++) { record->broker_id[i] = wire[at++]; }
  record->reserved_1 = wire[at++];

  return at;
}

/* what was read of Nlt Order Inquiry Request Message is what was written, byte for byte */
static void equal_nlt_order_inquiry_request_message(const NltOrderInquiryRequestMessage *read, const NltOrderInquiryRequestMessage *written) {
  for (size_t i = 0; i < 5; i++) { assert(read->broker_id[i] == written->broker_id[i]); }
  assert(read->reserved_1 == written->reserved_1);
}

/* Nlt Order Inquiry Request Message: written and read back, then read and written back */
static void check_nlt_order_inquiry_request_message(void) {
  NltOrderInquiryRequestMessage sent;
  NltOrderInquiryRequestMessage got;
  uint8_t wire[6];
  uint8_t again[6];

  any_nlt_order_inquiry_request_message(&sent);
  assert(encode_nlt_order_inquiry_request_message(&sent, wire, 0) == 6);
  assert(decode_nlt_order_inquiry_request_message(&got, wire, 0) == 6);
  equal_nlt_order_inquiry_request_message(&got, &sent);

  for (size_t i = 0; i < 6; i++) { wire[i] = arbitrary(); }
  assert(decode_nlt_order_inquiry_request_message(&got, wire, 0) == 6);
  assert(encode_nlt_order_inquiry_request_message(&got, again, 0) == 6);
  for (size_t i = 0; i < 6; i++) { assert(again[i] == wire[i]); }
}

/* ---- What esbmc checks ------------------------------------------------------- */

/* every record of the protocol, each on its own buffers */
static void checks(void) {
  check_packet_header();
  check_message_header();
  check_system_information_in_message();
  check_st_market_status();
  check_st_ex_market_status();
  check_st_pl_market_status();
  check_update_local_database_in_message();
  check_contract_desc();
  check_trade_inquiry_body();
  check_trade_inquiry_message();
  check_gateway_router_request_message();
  check_secure_box_registration_request_in_message();
  check_box_sign_on_request_in_message();
  check_reset_user_password_message();
  check_collateral_user_status_change_request_message();
  check_user_trade_modify_cancel_status_change_request_message();
  check_user_address_unlock_request_message();
  check_nlt_order_inquiry_request_message();
}

int main(void) {
#ifdef CONCRETE
  for (pattern = 0; pattern < 4; pattern++) { checks(); }
#else
  checks();
#endif

  return 0;
}
