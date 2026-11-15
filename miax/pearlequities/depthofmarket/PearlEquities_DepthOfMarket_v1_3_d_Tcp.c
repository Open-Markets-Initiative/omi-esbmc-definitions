// miax/pearlequities/depthofmarket/PearlEquities_DepthOfMarket_v1_3_d_Tcp.c
/*
 * Miami International Holdings Depth Of Market
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

/* ---- Esesm Packet Header: 3 bytes -------------------------------------------- */

/* ESesM packet header */
typedef struct {
  uint8_t esesm_packet_length[2];  /* bytes 0 to 1 */
  uint8_t esesm_packet_type;       /* byte 2 */
} EsesmPacketHeader;

/* any Esesm Packet Header at all: every byte one the checker chooses */
static void any_esesm_packet_header(EsesmPacketHeader *record) {
  for (size_t i = 0; i < 2; i++) { record->esesm_packet_length[i] = arbitrary(); }
  record->esesm_packet_type = arbitrary();
}

/* Esesm Packet Header to the wire: 3 bytes from at, returning where the next byte goes */
static size_t encode_esesm_packet_header(const EsesmPacketHeader *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->esesm_packet_length[i]; }
  wire[at++] = record->esesm_packet_type;

  return at;
}

/* Esesm Packet Header off the wire: 3 bytes from at, returning where the next byte lies */
static size_t decode_esesm_packet_header(EsesmPacketHeader *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->esesm_packet_length[i] = wire[at++]; }
  record->esesm_packet_type = wire[at++];

  return at;
}

/* what was read of Esesm Packet Header is what was written, byte for byte */
static void equal_esesm_packet_header(const EsesmPacketHeader *read, const EsesmPacketHeader *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->esesm_packet_length[i] == written->esesm_packet_length[i]); }
  assert(read->esesm_packet_type == written->esesm_packet_type);
}

/* Esesm Packet Header: written and read back, then read and written back */
static void check_esesm_packet_header(void) {
  EsesmPacketHeader sent;
  EsesmPacketHeader got;
  uint8_t wire[3];
  uint8_t again[3];

  any_esesm_packet_header(&sent);
  assert(encode_esesm_packet_header(&sent, wire, 0) == 3);
  assert(decode_esesm_packet_header(&got, wire, 0) == 3);
  equal_esesm_packet_header(&got, &sent);

  for (size_t i = 0; i < 3; i++) { wire[i] = arbitrary(); }
  assert(decode_esesm_packet_header(&got, wire, 0) == 3);
  assert(encode_esesm_packet_header(&got, again, 0) == 3);
  for (size_t i = 0; i < 3; i++) { assert(again[i] == wire[i]); }
}

/* ---- Refresh Request Message: 1 byte ----------------------------------------- */

/* Sent by the firm over the DoM Retransmission Interface (ESeSM Unsequenced Data Packet) to request a Last Value Refresh of a particular data set identified by Refresh Message Type. */
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

/* ---- Refresh Response Message: 8 bytes --------------------------------------- */

/* Sent by MIAX Pearl Equities over the DoM Retransmission Interface (ESeSM Unsequenced Data Packet) carrying one Application Message that satisfies a previous Refresh Request. */
typedef struct {
  uint8_t sequence_number[8];  /* bytes 0 to 7 */
} RefreshResponseMessage;

/* any Refresh Response Message at all: every byte one the checker chooses */
static void any_refresh_response_message(RefreshResponseMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->sequence_number[i] = arbitrary(); }
}

/* Refresh Response Message to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_refresh_response_message(const RefreshResponseMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->sequence_number[i]; }

  return at;
}

/* Refresh Response Message off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_refresh_response_message(RefreshResponseMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->sequence_number[i] = wire[at++]; }

  return at;
}

/* what was read of Refresh Response Message is what was written, byte for byte */
static void equal_refresh_response_message(const RefreshResponseMessage *read, const RefreshResponseMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->sequence_number[i] == written->sequence_number[i]); }
}

/* Refresh Response Message: written and read back, then read and written back */
static void check_refresh_response_message(void) {
  RefreshResponseMessage sent;
  RefreshResponseMessage got;
  uint8_t wire[8];
  uint8_t again[8];

  any_refresh_response_message(&sent);
  assert(encode_refresh_response_message(&sent, wire, 0) == 8);
  assert(decode_refresh_response_message(&got, wire, 0) == 8);
  equal_refresh_response_message(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_refresh_response_message(&got, wire, 0) == 8);
  assert(encode_refresh_response_message(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- End Of Refresh Notification Message: 1 byte ----------------------------- */

/* Sent by MIAX Pearl Equities over the DoM Retransmission Interface (ESeSM Unsequenced Data Packet) when the refresh response is complete. */
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

/* ---- Synchronization Complete: 1 byte ---------------------------------------- */

/* The ESesM server sends a Synchronization complete packet when it is done replaying all the old packets and is ready to start sending new packets from the Matching Engine */
typedef struct {
  uint8_t matching_engine_id;  /* byte 0 */
} SynchronizationComplete;

/* any Synchronization Complete at all: every byte one the checker chooses */
static void any_synchronization_complete(SynchronizationComplete *record) {
  record->matching_engine_id = arbitrary();
}

/* Synchronization Complete to the wire: 1 byte from at, returning where the next byte goes */
static size_t encode_synchronization_complete(const SynchronizationComplete *record, uint8_t *wire, size_t at) {
  wire[at++] = record->matching_engine_id;

  return at;
}

/* Synchronization Complete off the wire: 1 byte from at, returning where the next byte lies */
static size_t decode_synchronization_complete(SynchronizationComplete *record, const uint8_t *wire, size_t at) {
  record->matching_engine_id = wire[at++];

  return at;
}

/* what was read of Synchronization Complete is what was written, byte for byte */
static void equal_synchronization_complete(const SynchronizationComplete *read, const SynchronizationComplete *written) {
  assert(read->matching_engine_id == written->matching_engine_id);
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

/* The ESesM client uses this packet to request a retransmission server to retransmit a range of packets */
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

/* ---- Trading Session Update: 2 bytes ----------------------------------------- */

/* The ESesM server sends a Trading Session Update packet to inform the client that a new trading session is starting on the specified Matching Engine */
typedef struct {
  uint8_t matching_engine_id;  /* byte 0 */
  uint8_t trading_session_id;  /* byte 1 */
} TradingSessionUpdate;

/* any Trading Session Update at all: every byte one the checker chooses */
static void any_trading_session_update(TradingSessionUpdate *record) {
  record->matching_engine_id = arbitrary();
  record->trading_session_id = arbitrary();
}

/* Trading Session Update to the wire: 2 bytes from at, returning where the next byte goes */
static size_t encode_trading_session_update(const TradingSessionUpdate *record, uint8_t *wire, size_t at) {
  wire[at++] = record->matching_engine_id;
  wire[at++] = record->trading_session_id;

  return at;
}

/* Trading Session Update off the wire: 2 bytes from at, returning where the next byte lies */
static size_t decode_trading_session_update(TradingSessionUpdate *record, const uint8_t *wire, size_t at) {
  record->matching_engine_id = wire[at++];
  record->trading_session_id = wire[at++];

  return at;
}

/* what was read of Trading Session Update is what was written, byte for byte */
static void equal_trading_session_update(const TradingSessionUpdate *read, const TradingSessionUpdate *written) {
  assert(read->matching_engine_id == written->matching_engine_id);
  assert(read->trading_session_id == written->trading_session_id);
}

/* Trading Session Update: written and read back, then read and written back */
static void check_trading_session_update(void) {
  TradingSessionUpdate sent;
  TradingSessionUpdate got;
  uint8_t wire[2];
  uint8_t again[2];

  any_trading_session_update(&sent);
  assert(encode_trading_session_update(&sent, wire, 0) == 2);
  assert(decode_trading_session_update(&got, wire, 0) == 2);
  equal_trading_session_update(&got, &sent);

  for (size_t i = 0; i < 2; i++) { wire[i] = arbitrary(); }
  assert(decode_trading_session_update(&got, wire, 0) == 2);
  assert(encode_trading_session_update(&got, again, 0) == 2);
  for (size_t i = 0; i < 2; i++) { assert(again[i] == wire[i]); }
}

/* ---- What esbmc checks ------------------------------------------------------- */

/* every record of the protocol, each on its own buffers */
static void checks(void) {
  check_esesm_packet_header();
  check_refresh_request_message();
  check_refresh_response_message();
  check_end_of_refresh_notification_message();
  check_synchronization_complete();
  check_retransmission_request();
  check_trading_session_update();
}

int main(void) {
#ifdef CONCRETE
  for (pattern = 0; pattern < 4; pattern++) { checks(); }
#else
  checks();
#endif

  return 0;
}
