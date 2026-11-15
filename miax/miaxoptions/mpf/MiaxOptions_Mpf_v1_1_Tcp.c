// miax/miaxoptions/mpf/MiaxOptions_Mpf_v1_1_Tcp.c
/*
 * Miami International Holdings MIAX Product Feed
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

/* ---- Sesm Packet Header: 3 bytes --------------------------------------------- */

/* SesM packet header */
typedef struct {
  uint8_t sesm_packet_length[2];  /* bytes 0 to 1 */
  uint8_t sesm_packet_type;       /* byte 2 */
} SesmPacketHeader;

/* any Sesm Packet Header at all: every byte one the checker chooses */
static void any_sesm_packet_header(SesmPacketHeader *record) {
  for (size_t i = 0; i < 2; i++) { record->sesm_packet_length[i] = arbitrary(); }
  record->sesm_packet_type = arbitrary();
}

/* Sesm Packet Header to the wire: 3 bytes from at, returning where the next byte goes */
static size_t encode_sesm_packet_header(const SesmPacketHeader *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->sesm_packet_length[i]; }
  wire[at++] = record->sesm_packet_type;

  return at;
}

/* Sesm Packet Header off the wire: 3 bytes from at, returning where the next byte lies */
static size_t decode_sesm_packet_header(SesmPacketHeader *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->sesm_packet_length[i] = wire[at++]; }
  record->sesm_packet_type = wire[at++];

  return at;
}

/* what was read of Sesm Packet Header is what was written, byte for byte */
static void equal_sesm_packet_header(const SesmPacketHeader *read, const SesmPacketHeader *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->sesm_packet_length[i] == written->sesm_packet_length[i]); }
  assert(read->sesm_packet_type == written->sesm_packet_type);
}

/* Sesm Packet Header: written and read back, then read and written back */
static void check_sesm_packet_header(void) {
  SesmPacketHeader sent;
  SesmPacketHeader got;
  uint8_t wire[3];
  uint8_t again[3];

  any_sesm_packet_header(&sent);
  assert(encode_sesm_packet_header(&sent, wire, 0) == 3);
  assert(decode_sesm_packet_header(&got, wire, 0) == 3);
  equal_sesm_packet_header(&got, &sent);

  for (size_t i = 0; i < 3; i++) { wire[i] = arbitrary(); }
  assert(decode_sesm_packet_header(&got, wire, 0) == 3);
  assert(encode_sesm_packet_header(&got, again, 0) == 3);
  for (size_t i = 0; i < 3; i++) { assert(again[i] == wire[i]); }
}

/* ---- Refresh Request Message: 1 byte ----------------------------------------- */

/* Sent by the firm over the MPF Retransmission Interface (SesM Unsequenced Data Packet) to request a Last Value Refresh of a particular data set identified by Refresh Message Type. */
typedef struct {
  uint8_t refresh_message_type;  /* byte 0 */
} RefreshRequestMessage;

/* any Refresh Request Message at all: every byte one the checker chooses */
static void any_refresh_request_message(RefreshRequestMessage *record) {
  record->refresh_message_type = arbitrary();
}

/* Refresh Request Message to the wire: 1 byte from at, returning where the next byte goes */
static size_t encode_refresh_request_message(const RefreshRequestMessage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->refresh_message_type;

  return at;
}

/* Refresh Request Message off the wire: 1 byte from at, returning where the next byte lies */
static size_t decode_refresh_request_message(RefreshRequestMessage *record, const uint8_t *wire, size_t at) {
  record->refresh_message_type = wire[at++];

  return at;
}

/* what was read of Refresh Request Message is what was written, byte for byte */
static void equal_refresh_request_message(const RefreshRequestMessage *read, const RefreshRequestMessage *written) {
  assert(read->refresh_message_type == written->refresh_message_type);
}

/* Refresh Request Message: written and read back, then read and written back */
static void check_refresh_request_message(void) {
  RefreshRequestMessage sent;
  RefreshRequestMessage got;
  uint8_t wire[1];
  uint8_t again[1];

  any_refresh_request_message(&sent);
  assert(encode_refresh_request_message(&sent, wire, 0) == 1);
  assert(decode_refresh_request_message(&got, wire, 0) == 1);
  equal_refresh_request_message(&got, &sent);

  for (size_t i = 0; i < 1; i++) { wire[i] = arbitrary(); }
  assert(decode_refresh_request_message(&got, wire, 0) == 1);
  assert(encode_refresh_request_message(&got, again, 0) == 1);
  for (size_t i = 0; i < 1; i++) { assert(again[i] == wire[i]); }
}

/* ---- System Time Message: 4 bytes -------------------------------------------- */

/* This is the message format that will be used to disseminate the “seconds” part of the timestamp that is applicable to all messages that are sent in the current second. */
typedef struct {
  uint8_t seconds[4];  /* bytes 0 to 3 */
} SystemTimeMessage;

/* any System Time Message at all: every byte one the checker chooses */
static void any_system_time_message(SystemTimeMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->seconds[i] = arbitrary(); }
}

/* System Time Message to the wire: 4 bytes from at, returning where the next byte goes */
static size_t encode_system_time_message(const SystemTimeMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->seconds[i]; }

  return at;
}

/* System Time Message off the wire: 4 bytes from at, returning where the next byte lies */
static size_t decode_system_time_message(SystemTimeMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->seconds[i] = wire[at++]; }

  return at;
}

/* what was read of System Time Message is what was written, byte for byte */
static void equal_system_time_message(const SystemTimeMessage *read, const SystemTimeMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->seconds[i] == written->seconds[i]); }
}

/* System Time Message: written and read back, then read and written back */
static void check_system_time_message(void) {
  SystemTimeMessage sent;
  SystemTimeMessage got;
  uint8_t wire[4];
  uint8_t again[4];

  any_system_time_message(&sent);
  assert(encode_system_time_message(&sent, wire, 0) == 4);
  assert(decode_system_time_message(&got, wire, 0) == 4);
  equal_system_time_message(&got, &sent);

  for (size_t i = 0; i < 4; i++) { wire[i] = arbitrary(); }
  assert(decode_system_time_message(&got, wire, 0) == 4);
  assert(encode_system_time_message(&got, again, 0) == 4);
  for (size_t i = 0; i < 4; i++) { assert(again[i] == wire[i]); }
}

/* ---- Symbol Definition Message: 37 bytes ------------------------------------- */

/* This is the message format that will be used to disseminate all Synthetic Future symbol definitions for the current session. */
typedef struct {
  uint8_t nanoseconds[4];              /* bytes 0 to 3 */
  uint8_t synthetic_future_symbol[8];  /* bytes 4 to 11 */
  uint8_t settlement_date[8];          /* bytes 12 to 19 */
  uint8_t symbol_status;               /* byte 20 */
  uint8_t reserved_16[16];             /* bytes 21 to 36 */
} SymbolDefinitionMessage;

/* any Symbol Definition Message at all: every byte one the checker chooses */
static void any_symbol_definition_message(SymbolDefinitionMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->synthetic_future_symbol[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->settlement_date[i] = arbitrary(); }
  record->symbol_status = arbitrary();
  for (size_t i = 0; i < 16; i++) { record->reserved_16[i] = arbitrary(); }
}

/* Symbol Definition Message to the wire: 37 bytes from at, returning where the next byte goes */
static size_t encode_symbol_definition_message(const SymbolDefinitionMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->nanoseconds[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->synthetic_future_symbol[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->settlement_date[i]; }
  wire[at++] = record->symbol_status;
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->reserved_16[i]; }

  return at;
}

/* Symbol Definition Message off the wire: 37 bytes from at, returning where the next byte lies */
static size_t decode_symbol_definition_message(SymbolDefinitionMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->synthetic_future_symbol[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->settlement_date[i] = wire[at++]; }
  record->symbol_status = wire[at++];
  for (size_t i = 0; i < 16; i++) { record->reserved_16[i] = wire[at++]; }

  return at;
}

/* what was read of Symbol Definition Message is what was written, byte for byte */
static void equal_symbol_definition_message(const SymbolDefinitionMessage *read, const SymbolDefinitionMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->nanoseconds[i] == written->nanoseconds[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->synthetic_future_symbol[i] == written->synthetic_future_symbol[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->settlement_date[i] == written->settlement_date[i]); }
  assert(read->symbol_status == written->symbol_status);
  for (size_t i = 0; i < 16; i++) { assert(read->reserved_16[i] == written->reserved_16[i]); }
}

/* Symbol Definition Message: written and read back, then read and written back */
static void check_symbol_definition_message(void) {
  SymbolDefinitionMessage sent;
  SymbolDefinitionMessage got;
  uint8_t wire[37];
  uint8_t again[37];

  any_symbol_definition_message(&sent);
  assert(encode_symbol_definition_message(&sent, wire, 0) == 37);
  assert(decode_symbol_definition_message(&got, wire, 0) == 37);
  equal_symbol_definition_message(&got, &sent);

  for (size_t i = 0; i < 37; i++) { wire[i] = arbitrary(); }
  assert(decode_symbol_definition_message(&got, wire, 0) == 37);
  assert(encode_symbol_definition_message(&got, again, 0) == 37);
  for (size_t i = 0; i < 37; i++) { assert(again[i] == wire[i]); }
}

/* ---- Index Value Message: 13 bytes ------------------------------------------- */

/* This is the message format that will be used to disseminate current index value. The index value may be the index cash value or the index settlement value, as identified by the Index Symbol. */
typedef struct {
  uint8_t nanoseconds[4];  /* bytes 0 to 3 */
  uint8_t symbol[5];       /* bytes 4 to 8 */
  uint8_t value[4];        /* bytes 9 to 12 */
} IndexValueMessage;

/* any Index Value Message at all: every byte one the checker chooses */
static void any_index_value_message(IndexValueMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = arbitrary(); }
  for (size_t i = 0; i < 5; i++) { record->symbol[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->value[i] = arbitrary(); }
}

/* Index Value Message to the wire: 13 bytes from at, returning where the next byte goes */
static size_t encode_index_value_message(const IndexValueMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->nanoseconds[i]; }
  for (size_t i = 0; i < 5; i++) { wire[at++] = record->symbol[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->value[i]; }

  return at;
}

/* Index Value Message off the wire: 13 bytes from at, returning where the next byte lies */
static size_t decode_index_value_message(IndexValueMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = wire[at++]; }
  for (size_t i = 0; i < 5; i++) { record->symbol[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->value[i] = wire[at++]; }

  return at;
}

/* what was read of Index Value Message is what was written, byte for byte */
static void equal_index_value_message(const IndexValueMessage *read, const IndexValueMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->nanoseconds[i] == written->nanoseconds[i]); }
  for (size_t i = 0; i < 5; i++) { assert(read->symbol[i] == written->symbol[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->value[i] == written->value[i]); }
}

/* Index Value Message: written and read back, then read and written back */
static void check_index_value_message(void) {
  IndexValueMessage sent;
  IndexValueMessage got;
  uint8_t wire[13];
  uint8_t again[13];

  any_index_value_message(&sent);
  assert(encode_index_value_message(&sent, wire, 0) == 13);
  assert(decode_index_value_message(&got, wire, 0) == 13);
  equal_index_value_message(&got, &sent);

  for (size_t i = 0; i < 13; i++) { wire[i] = arbitrary(); }
  assert(decode_index_value_message(&got, wire, 0) == 13);
  assert(encode_index_value_message(&got, again, 0) == 13);
  for (size_t i = 0; i < 13; i++) { assert(again[i] == wire[i]); }
}

/* ---- Synthetic Future Value Message: 24 bytes -------------------------------- */

/* This is the message format that will be used to disseminate current Synthetic Future values. The specific Synthetic Future value is identified by the Synthetic Future Symbol. */
typedef struct {
  uint8_t nanoseconds[4];              /* bytes 0 to 3 */
  uint8_t synthetic_future_symbol[8];  /* bytes 4 to 11 */
  uint8_t value[4];                    /* bytes 12 to 15 */
  uint8_t reserved_8[8];               /* bytes 16 to 23 */
} SyntheticFutureValueMessage;

/* any Synthetic Future Value Message at all: every byte one the checker chooses */
static void any_synthetic_future_value_message(SyntheticFutureValueMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->synthetic_future_symbol[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->value[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->reserved_8[i] = arbitrary(); }
}

/* Synthetic Future Value Message to the wire: 24 bytes from at, returning where the next byte goes */
static size_t encode_synthetic_future_value_message(const SyntheticFutureValueMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->nanoseconds[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->synthetic_future_symbol[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->value[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->reserved_8[i]; }

  return at;
}

/* Synthetic Future Value Message off the wire: 24 bytes from at, returning where the next byte lies */
static size_t decode_synthetic_future_value_message(SyntheticFutureValueMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->synthetic_future_symbol[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->value[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->reserved_8[i] = wire[at++]; }

  return at;
}

/* what was read of Synthetic Future Value Message is what was written, byte for byte */
static void equal_synthetic_future_value_message(const SyntheticFutureValueMessage *read, const SyntheticFutureValueMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->nanoseconds[i] == written->nanoseconds[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->synthetic_future_symbol[i] == written->synthetic_future_symbol[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->value[i] == written->value[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->reserved_8[i] == written->reserved_8[i]); }
}

/* Synthetic Future Value Message: written and read back, then read and written back */
static void check_synthetic_future_value_message(void) {
  SyntheticFutureValueMessage sent;
  SyntheticFutureValueMessage got;
  uint8_t wire[24];
  uint8_t again[24];

  any_synthetic_future_value_message(&sent);
  assert(encode_synthetic_future_value_message(&sent, wire, 0) == 24);
  assert(decode_synthetic_future_value_message(&got, wire, 0) == 24);
  equal_synthetic_future_value_message(&got, &sent);

  for (size_t i = 0; i < 24; i++) { wire[i] = arbitrary(); }
  assert(decode_synthetic_future_value_message(&got, wire, 0) == 24);
  assert(encode_synthetic_future_value_message(&got, again, 0) == 24);
  for (size_t i = 0; i < 24; i++) { assert(again[i] == wire[i]); }
}

/* ---- End Of Refresh Notification Message: 1 byte ----------------------------- */

/* Sent by MIAX Options over the MPF Retransmission Interface (SesM Unsequenced Data Packet) when the refresh response is complete. */
typedef struct {
  uint8_t refresh_message_type;  /* byte 0 */
} EndOfRefreshNotificationMessage;

/* any End Of Refresh Notification Message at all: every byte one the checker chooses */
static void any_end_of_refresh_notification_message(EndOfRefreshNotificationMessage *record) {
  record->refresh_message_type = arbitrary();
}

/* End Of Refresh Notification Message to the wire: 1 byte from at, returning where the next byte goes */
static size_t encode_end_of_refresh_notification_message(const EndOfRefreshNotificationMessage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->refresh_message_type;

  return at;
}

/* End Of Refresh Notification Message off the wire: 1 byte from at, returning where the next byte lies */
static size_t decode_end_of_refresh_notification_message(EndOfRefreshNotificationMessage *record, const uint8_t *wire, size_t at) {
  record->refresh_message_type = wire[at++];

  return at;
}

/* what was read of End Of Refresh Notification Message is what was written, byte for byte */
static void equal_end_of_refresh_notification_message(const EndOfRefreshNotificationMessage *read, const EndOfRefreshNotificationMessage *written) {
  assert(read->refresh_message_type == written->refresh_message_type);
}

/* End Of Refresh Notification Message: written and read back, then read and written back */
static void check_end_of_refresh_notification_message(void) {
  EndOfRefreshNotificationMessage sent;
  EndOfRefreshNotificationMessage got;
  uint8_t wire[1];
  uint8_t again[1];

  any_end_of_refresh_notification_message(&sent);
  assert(encode_end_of_refresh_notification_message(&sent, wire, 0) == 1);
  assert(decode_end_of_refresh_notification_message(&got, wire, 0) == 1);
  equal_end_of_refresh_notification_message(&got, &sent);

  for (size_t i = 0; i < 1; i++) { wire[i] = arbitrary(); }
  assert(decode_end_of_refresh_notification_message(&got, wire, 0) == 1);
  assert(encode_end_of_refresh_notification_message(&got, again, 0) == 1);
  for (size_t i = 0; i < 1; i++) { assert(again[i] == wire[i]); }
}

/* ---- Login Request: 35 bytes ------------------------------------------------- */

/* The SesM client must send a Login request packet immediately upon establishing a new TCP/IP socket connection to the server */
typedef struct {
  uint8_t sesm_version[5];               /* bytes 0 to 4 */
  uint8_t username[5];                   /* bytes 5 to 9 */
  uint8_t computer_id[8];                /* bytes 10 to 17 */
  uint8_t application_protocol[8];       /* bytes 18 to 25 */
  uint8_t requested_trading_session_id;  /* byte 26 */
  uint8_t requested_sequence_number[8];  /* bytes 27 to 34 */
} LoginRequest;

/* any Login Request at all: every byte one the checker chooses */
static void any_login_request(LoginRequest *record) {
  for (size_t i = 0; i < 5; i++) { record->sesm_version[i] = arbitrary(); }
  for (size_t i = 0; i < 5; i++) { record->username[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->computer_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->application_protocol[i] = arbitrary(); }
  record->requested_trading_session_id = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->requested_sequence_number[i] = arbitrary(); }
}

/* Login Request to the wire: 35 bytes from at, returning where the next byte goes */
static size_t encode_login_request(const LoginRequest *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 5; i++) { wire[at++] = record->sesm_version[i]; }
  for (size_t i = 0; i < 5; i++) { wire[at++] = record->username[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->computer_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->application_protocol[i]; }
  wire[at++] = record->requested_trading_session_id;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->requested_sequence_number[i]; }

  return at;
}

/* Login Request off the wire: 35 bytes from at, returning where the next byte lies */
static size_t decode_login_request(LoginRequest *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 5; i++) { record->sesm_version[i] = wire[at++]; }
  for (size_t i = 0; i < 5; i++) { record->username[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->computer_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->application_protocol[i] = wire[at++]; }
  record->requested_trading_session_id = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->requested_sequence_number[i] = wire[at++]; }

  return at;
}

/* what was read of Login Request is what was written, byte for byte */
static void equal_login_request(const LoginRequest *read, const LoginRequest *written) {
  for (size_t i = 0; i < 5; i++) { assert(read->sesm_version[i] == written->sesm_version[i]); }
  for (size_t i = 0; i < 5; i++) { assert(read->username[i] == written->username[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->computer_id[i] == written->computer_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->application_protocol[i] == written->application_protocol[i]); }
  assert(read->requested_trading_session_id == written->requested_trading_session_id);
  for (size_t i = 0; i < 8; i++) { assert(read->requested_sequence_number[i] == written->requested_sequence_number[i]); }
}

/* Login Request: written and read back, then read and written back */
static void check_login_request(void) {
  LoginRequest sent;
  LoginRequest got;
  uint8_t wire[35];
  uint8_t again[35];

  any_login_request(&sent);
  assert(encode_login_request(&sent, wire, 0) == 35);
  assert(decode_login_request(&got, wire, 0) == 35);
  equal_login_request(&got, &sent);

  for (size_t i = 0; i < 35; i++) { wire[i] = arbitrary(); }
  assert(decode_login_request(&got, wire, 0) == 35);
  assert(encode_login_request(&got, again, 0) == 35);
  for (size_t i = 0; i < 35; i++) { assert(again[i] == wire[i]); }
}

/* ---- Login Response: 11 bytes ------------------------------------------------ */

/* The SesM server sends a Login response packet in response a Login request packet from the client */
typedef struct {
  uint8_t number_of_matching_engines;  /* byte 0 */
  uint8_t login_status;                /* byte 1 */
  uint8_t trading_session_id;          /* byte 2 */
  uint8_t highest_sequence_number[8];  /* bytes 3 to 10 */
} LoginResponse;

/* any Login Response at all: every byte one the checker chooses */
static void any_login_response(LoginResponse *record) {
  record->number_of_matching_engines = arbitrary();
  record->login_status = arbitrary();
  record->trading_session_id = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->highest_sequence_number[i] = arbitrary(); }
}

/* Login Response to the wire: 11 bytes from at, returning where the next byte goes */
static size_t encode_login_response(const LoginResponse *record, uint8_t *wire, size_t at) {
  wire[at++] = record->number_of_matching_engines;
  wire[at++] = record->login_status;
  wire[at++] = record->trading_session_id;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->highest_sequence_number[i]; }

  return at;
}

/* Login Response off the wire: 11 bytes from at, returning where the next byte lies */
static size_t decode_login_response(LoginResponse *record, const uint8_t *wire, size_t at) {
  record->number_of_matching_engines = wire[at++];
  record->login_status = wire[at++];
  record->trading_session_id = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->highest_sequence_number[i] = wire[at++]; }

  return at;
}

/* what was read of Login Response is what was written, byte for byte */
static void equal_login_response(const LoginResponse *read, const LoginResponse *written) {
  assert(read->number_of_matching_engines == written->number_of_matching_engines);
  assert(read->login_status == written->login_status);
  assert(read->trading_session_id == written->trading_session_id);
  for (size_t i = 0; i < 8; i++) { assert(read->highest_sequence_number[i] == written->highest_sequence_number[i]); }
}

/* Login Response: written and read back, then read and written back */
static void check_login_response(void) {
  LoginResponse sent;
  LoginResponse got;
  uint8_t wire[11];
  uint8_t again[11];

  any_login_response(&sent);
  assert(encode_login_response(&sent, wire, 0) == 11);
  assert(decode_login_response(&got, wire, 0) == 11);
  equal_login_response(&got, &sent);

  for (size_t i = 0; i < 11; i++) { wire[i] = arbitrary(); }
  assert(decode_login_response(&got, wire, 0) == 11);
  assert(encode_login_response(&got, again, 0) == 11);
  for (size_t i = 0; i < 11; i++) { assert(again[i] == wire[i]); }
}

/* ---- Synchronization Complete: 1 byte ---------------------------------------- */

/* The SesM server sends a Login response packet in response a Login request packet from the client */
typedef struct {
  uint8_t number_of_matching_engines;  /* byte 0 */
} SynchronizationComplete;

/* any Synchronization Complete at all: every byte one the checker chooses */
static void any_synchronization_complete(SynchronizationComplete *record) {
  record->number_of_matching_engines = arbitrary();
}

/* Synchronization Complete to the wire: 1 byte from at, returning where the next byte goes */
static size_t encode_synchronization_complete(const SynchronizationComplete *record, uint8_t *wire, size_t at) {
  wire[at++] = record->number_of_matching_engines;

  return at;
}

/* Synchronization Complete off the wire: 1 byte from at, returning where the next byte lies */
static size_t decode_synchronization_complete(SynchronizationComplete *record, const uint8_t *wire, size_t at) {
  record->number_of_matching_engines = wire[at++];

  return at;
}

/* what was read of Synchronization Complete is what was written, byte for byte */
static void equal_synchronization_complete(const SynchronizationComplete *read, const SynchronizationComplete *written) {
  assert(read->number_of_matching_engines == written->number_of_matching_engines);
}

/* Synchronization Complete: written and read back, then read and written back */
static void check_synchronization_complete(void) {
  SynchronizationComplete sent;
  SynchronizationComplete got;
  uint8_t wire[1];
  uint8_t again[1];

  any_synchronization_complete(&sent);
  assert(encode_synchronization_complete(&sent, wire, 0) == 1);
  assert(decode_synchronization_complete(&got, wire, 0) == 1);
  equal_synchronization_complete(&got, &sent);

  for (size_t i = 0; i < 1; i++) { wire[i] = arbitrary(); }
  assert(decode_synchronization_complete(&got, wire, 0) == 1);
  assert(encode_synchronization_complete(&got, again, 0) == 1);
  for (size_t i = 0; i < 1; i++) { assert(again[i] == wire[i]); }
}

/* ---- Retransmission Request: 16 bytes ---------------------------------------- */

/* The SesM client uses this packet to request a retransmission server to retransmit a range of packets */
typedef struct {
  uint8_t start_sequence_number[8];  /* bytes 0 to 7 */
  uint8_t end_sequence_number[8];    /* bytes 8 to 15 */
} RetransmissionRequest;

/* any Retransmission Request at all: every byte one the checker chooses */
static void any_retransmission_request(RetransmissionRequest *record) {
  for (size_t i = 0; i < 8; i++) { record->start_sequence_number[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->end_sequence_number[i] = arbitrary(); }
}

/* Retransmission Request to the wire: 16 bytes from at, returning where the next byte goes */
static size_t encode_retransmission_request(const RetransmissionRequest *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->start_sequence_number[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->end_sequence_number[i]; }

  return at;
}

/* Retransmission Request off the wire: 16 bytes from at, returning where the next byte lies */
static size_t decode_retransmission_request(RetransmissionRequest *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->start_sequence_number[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->end_sequence_number[i] = wire[at++]; }

  return at;
}

/* what was read of Retransmission Request is what was written, byte for byte */
static void equal_retransmission_request(const RetransmissionRequest *read, const RetransmissionRequest *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->start_sequence_number[i] == written->start_sequence_number[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->end_sequence_number[i] == written->end_sequence_number[i]); }
}

/* Retransmission Request: written and read back, then read and written back */
static void check_retransmission_request(void) {
  RetransmissionRequest sent;
  RetransmissionRequest got;
  uint8_t wire[16];
  uint8_t again[16];

  any_retransmission_request(&sent);
  assert(encode_retransmission_request(&sent, wire, 0) == 16);
  assert(decode_retransmission_request(&got, wire, 0) == 16);
  equal_retransmission_request(&got, &sent);

  for (size_t i = 0; i < 16; i++) { wire[i] = arbitrary(); }
  assert(decode_retransmission_request(&got, wire, 0) == 16);
  assert(encode_retransmission_request(&got, again, 0) == 16);
  for (size_t i = 0; i < 16; i++) { assert(again[i] == wire[i]); }
}

/* ---- What esbmc checks ------------------------------------------------------- */

/* every record of the protocol, each on its own buffers */
static void checks(void) {
  check_sesm_packet_header();
  check_refresh_request_message();
  check_system_time_message();
  check_symbol_definition_message();
  check_index_value_message();
  check_synthetic_future_value_message();
  check_end_of_refresh_notification_message();
  check_login_request();
  check_login_response();
  check_synchronization_complete();
  check_retransmission_request();
}

int main(void) {
#ifdef CONCRETE
  for (pattern = 0; pattern < 4; pattern++) { checks(); }
#else
  checks();
#endif

  return 0;
}
