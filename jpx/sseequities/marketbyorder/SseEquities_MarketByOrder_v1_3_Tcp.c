// jpx/sseequities/marketbyorder/SseEquities_MarketByOrder_v1_3_Tcp.c
/*
 * Japan Exchange Group Market By Order
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
 *   - a field filling what is left of what holds it
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

/* ---- Tcp Packet Header: 3 bytes ---------------------------------------------- */

/* Jpx Flex Tcp packet header carrying length prefix and packet type discriminator */
typedef struct {
  uint8_t packet_length[2];  /* bytes 0 to 1 */
  uint8_t packet_type;       /* byte 2 */
} TcpPacketHeader;

/* any Tcp Packet Header at all: every byte one the checker chooses */
static void any_tcp_packet_header(TcpPacketHeader *record) {
  for (size_t i = 0; i < 2; i++) { record->packet_length[i] = arbitrary(); }
  record->packet_type = arbitrary();
}

/* Tcp Packet Header to the wire: 3 bytes from at, returning where the next byte goes */
static size_t encode_tcp_packet_header(const TcpPacketHeader *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->packet_length[i]; }
  wire[at++] = record->packet_type;

  return at;
}

/* Tcp Packet Header off the wire: 3 bytes from at, returning where the next byte lies */
static size_t decode_tcp_packet_header(TcpPacketHeader *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->packet_length[i] = wire[at++]; }
  record->packet_type = wire[at++];

  return at;
}

/* what was read of Tcp Packet Header is what was written, byte for byte */
static void equal_tcp_packet_header(const TcpPacketHeader *read, const TcpPacketHeader *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->packet_length[i] == written->packet_length[i]); }
  assert(read->packet_type == written->packet_type);
}

/* Tcp Packet Header: written and read back, then read and written back */
static void check_tcp_packet_header(void) {
  TcpPacketHeader sent;
  TcpPacketHeader got;
  uint8_t wire[3];
  uint8_t again[3];

  any_tcp_packet_header(&sent);
  assert(encode_tcp_packet_header(&sent, wire, 0) == 3);
  assert(decode_tcp_packet_header(&got, wire, 0) == 3);
  equal_tcp_packet_header(&got, &sent);

  for (size_t i = 0; i < 3; i++) { wire[i] = arbitrary(); }
  assert(decode_tcp_packet_header(&got, wire, 0) == 3);
  assert(encode_tcp_packet_header(&got, again, 0) == 3);
  for (size_t i = 0; i < 3; i++) { assert(again[i] == wire[i]); }
}

/* ---- Login Request Retransmission Message: 15 bytes -------------------------- */

/* Tcp login request selecting retransmission, sent by the user. One of the two Packet Type codes the document gives the 18 byte Login Request. */
typedef struct {
  uint8_t user_id[6];                  /* bytes 0 to 5 */
  uint8_t multicast_group_number;      /* byte 6 */
  uint8_t number_of_system_reboots;    /* byte 7 */
  uint8_t sequence_number[4];          /* bytes 8 to 11 */
  uint8_t requested_message_count[3];  /* bytes 12 to 14 */
} LoginRequestRetransmissionMessage;

/* any Login Request Retransmission Message at all: every byte one the checker chooses */
static void any_login_request_retransmission_message(LoginRequestRetransmissionMessage *record) {
  for (size_t i = 0; i < 6; i++) { record->user_id[i] = arbitrary(); }
  record->multicast_group_number = arbitrary();
  record->number_of_system_reboots = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->sequence_number[i] = arbitrary(); }
  for (size_t i = 0; i < 3; i++) { record->requested_message_count[i] = arbitrary(); }
}

/* Login Request Retransmission Message to the wire: 15 bytes from at, returning where the next byte goes */
static size_t encode_login_request_retransmission_message(const LoginRequestRetransmissionMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->user_id[i]; }
  wire[at++] = record->multicast_group_number;
  wire[at++] = record->number_of_system_reboots;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->sequence_number[i]; }
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->requested_message_count[i]; }

  return at;
}

/* Login Request Retransmission Message off the wire: 15 bytes from at, returning where the next byte lies */
static size_t decode_login_request_retransmission_message(LoginRequestRetransmissionMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 6; i++) { record->user_id[i] = wire[at++]; }
  record->multicast_group_number = wire[at++];
  record->number_of_system_reboots = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->sequence_number[i] = wire[at++]; }
  for (size_t i = 0; i < 3; i++) { record->requested_message_count[i] = wire[at++]; }

  return at;
}

/* what was read of Login Request Retransmission Message is what was written, byte for byte */
static void equal_login_request_retransmission_message(const LoginRequestRetransmissionMessage *read, const LoginRequestRetransmissionMessage *written) {
  for (size_t i = 0; i < 6; i++) { assert(read->user_id[i] == written->user_id[i]); }
  assert(read->multicast_group_number == written->multicast_group_number);
  assert(read->number_of_system_reboots == written->number_of_system_reboots);
  for (size_t i = 0; i < 4; i++) { assert(read->sequence_number[i] == written->sequence_number[i]); }
  for (size_t i = 0; i < 3; i++) { assert(read->requested_message_count[i] == written->requested_message_count[i]); }
}

/* Login Request Retransmission Message: written and read back, then read and written back */
static void check_login_request_retransmission_message(void) {
  LoginRequestRetransmissionMessage sent;
  LoginRequestRetransmissionMessage got;
  uint8_t wire[15];
  uint8_t again[15];

  any_login_request_retransmission_message(&sent);
  assert(encode_login_request_retransmission_message(&sent, wire, 0) == 15);
  assert(decode_login_request_retransmission_message(&got, wire, 0) == 15);
  equal_login_request_retransmission_message(&got, &sent);

  for (size_t i = 0; i < 15; i++) { wire[i] = arbitrary(); }
  assert(decode_login_request_retransmission_message(&got, wire, 0) == 15);
  assert(encode_login_request_retransmission_message(&got, again, 0) == 15);
  for (size_t i = 0; i < 15; i++) { assert(again[i] == wire[i]); }
}

/* ---- Login Request Snapshot Message: 15 bytes -------------------------------- */

/* Tcp login request selecting snapshot, sent by the user. Same layout as the retransmission request; Number of System Reboots, Sequence Number and Requested Message Count are all set to 0. */
typedef struct {
  uint8_t user_id[6];                  /* bytes 0 to 5 */
  uint8_t multicast_group_number;      /* byte 6 */
  uint8_t number_of_system_reboots;    /* byte 7 */
  uint8_t sequence_number[4];          /* bytes 8 to 11 */
  uint8_t requested_message_count[3];  /* bytes 12 to 14 */
} LoginRequestSnapshotMessage;

/* any Login Request Snapshot Message at all: every byte one the checker chooses */
static void any_login_request_snapshot_message(LoginRequestSnapshotMessage *record) {
  for (size_t i = 0; i < 6; i++) { record->user_id[i] = arbitrary(); }
  record->multicast_group_number = arbitrary();
  record->number_of_system_reboots = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->sequence_number[i] = arbitrary(); }
  for (size_t i = 0; i < 3; i++) { record->requested_message_count[i] = arbitrary(); }
}

/* Login Request Snapshot Message to the wire: 15 bytes from at, returning where the next byte goes */
static size_t encode_login_request_snapshot_message(const LoginRequestSnapshotMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->user_id[i]; }
  wire[at++] = record->multicast_group_number;
  wire[at++] = record->number_of_system_reboots;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->sequence_number[i]; }
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->requested_message_count[i]; }

  return at;
}

/* Login Request Snapshot Message off the wire: 15 bytes from at, returning where the next byte lies */
static size_t decode_login_request_snapshot_message(LoginRequestSnapshotMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 6; i++) { record->user_id[i] = wire[at++]; }
  record->multicast_group_number = wire[at++];
  record->number_of_system_reboots = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->sequence_number[i] = wire[at++]; }
  for (size_t i = 0; i < 3; i++) { record->requested_message_count[i] = wire[at++]; }

  return at;
}

/* what was read of Login Request Snapshot Message is what was written, byte for byte */
static void equal_login_request_snapshot_message(const LoginRequestSnapshotMessage *read, const LoginRequestSnapshotMessage *written) {
  for (size_t i = 0; i < 6; i++) { assert(read->user_id[i] == written->user_id[i]); }
  assert(read->multicast_group_number == written->multicast_group_number);
  assert(read->number_of_system_reboots == written->number_of_system_reboots);
  for (size_t i = 0; i < 4; i++) { assert(read->sequence_number[i] == written->sequence_number[i]); }
  for (size_t i = 0; i < 3; i++) { assert(read->requested_message_count[i] == written->requested_message_count[i]); }
}

/* Login Request Snapshot Message: written and read back, then read and written back */
static void check_login_request_snapshot_message(void) {
  LoginRequestSnapshotMessage sent;
  LoginRequestSnapshotMessage got;
  uint8_t wire[15];
  uint8_t again[15];

  any_login_request_snapshot_message(&sent);
  assert(encode_login_request_snapshot_message(&sent, wire, 0) == 15);
  assert(decode_login_request_snapshot_message(&got, wire, 0) == 15);
  equal_login_request_snapshot_message(&got, &sent);

  for (size_t i = 0; i < 15; i++) { wire[i] = arbitrary(); }
  assert(decode_login_request_snapshot_message(&got, wire, 0) == 15);
  assert(encode_login_request_snapshot_message(&got, again, 0) == 15);
  for (size_t i = 0; i < 15; i++) { assert(again[i] == wire[i]); }
}

/* ---- Login Result Accepted Message: 2 bytes ---------------------------------- */

/* Tcp login response accepting the request. Result Code carries A. */
typedef struct {
  uint8_t multicast_group_number;  /* byte 0 */
  uint8_t result_code;             /* byte 1 */
} LoginResultAcceptedMessage;

/* any Login Result Accepted Message at all: every byte one the checker chooses */
static void any_login_result_accepted_message(LoginResultAcceptedMessage *record) {
  record->multicast_group_number = arbitrary();
  record->result_code = arbitrary();
}

/* Login Result Accepted Message to the wire: 2 bytes from at, returning where the next byte goes */
static size_t encode_login_result_accepted_message(const LoginResultAcceptedMessage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->multicast_group_number;
  wire[at++] = record->result_code;

  return at;
}

/* Login Result Accepted Message off the wire: 2 bytes from at, returning where the next byte lies */
static size_t decode_login_result_accepted_message(LoginResultAcceptedMessage *record, const uint8_t *wire, size_t at) {
  record->multicast_group_number = wire[at++];
  record->result_code = wire[at++];

  return at;
}

/* what was read of Login Result Accepted Message is what was written, byte for byte */
static void equal_login_result_accepted_message(const LoginResultAcceptedMessage *read, const LoginResultAcceptedMessage *written) {
  assert(read->multicast_group_number == written->multicast_group_number);
  assert(read->result_code == written->result_code);
}

/* Login Result Accepted Message: written and read back, then read and written back */
static void check_login_result_accepted_message(void) {
  LoginResultAcceptedMessage sent;
  LoginResultAcceptedMessage got;
  uint8_t wire[2];
  uint8_t again[2];

  any_login_result_accepted_message(&sent);
  assert(encode_login_result_accepted_message(&sent, wire, 0) == 2);
  assert(decode_login_result_accepted_message(&got, wire, 0) == 2);
  equal_login_result_accepted_message(&got, &sent);

  for (size_t i = 0; i < 2; i++) { wire[i] = arbitrary(); }
  assert(decode_login_result_accepted_message(&got, wire, 0) == 2);
  assert(encode_login_result_accepted_message(&got, again, 0) == 2);
  for (size_t i = 0; i < 2; i++) { assert(again[i] == wire[i]); }
}

/* ---- Login Result Rejected Message: 2 bytes ---------------------------------- */

/* Tcp login response rejecting the request. Same layout as the accepted response; Result Code carries the reason the request failed. */
typedef struct {
  uint8_t multicast_group_number;  /* byte 0 */
  uint8_t result_code;             /* byte 1 */
} LoginResultRejectedMessage;

/* any Login Result Rejected Message at all: every byte one the checker chooses */
static void any_login_result_rejected_message(LoginResultRejectedMessage *record) {
  record->multicast_group_number = arbitrary();
  record->result_code = arbitrary();
}

/* Login Result Rejected Message to the wire: 2 bytes from at, returning where the next byte goes */
static size_t encode_login_result_rejected_message(const LoginResultRejectedMessage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->multicast_group_number;
  wire[at++] = record->result_code;

  return at;
}

/* Login Result Rejected Message off the wire: 2 bytes from at, returning where the next byte lies */
static size_t decode_login_result_rejected_message(LoginResultRejectedMessage *record, const uint8_t *wire, size_t at) {
  record->multicast_group_number = wire[at++];
  record->result_code = wire[at++];

  return at;
}

/* what was read of Login Result Rejected Message is what was written, byte for byte */
static void equal_login_result_rejected_message(const LoginResultRejectedMessage *read, const LoginResultRejectedMessage *written) {
  assert(read->multicast_group_number == written->multicast_group_number);
  assert(read->result_code == written->result_code);
}

/* Login Result Rejected Message: written and read back, then read and written back */
static void check_login_result_rejected_message(void) {
  LoginResultRejectedMessage sent;
  LoginResultRejectedMessage got;
  uint8_t wire[2];
  uint8_t again[2];

  any_login_result_rejected_message(&sent);
  assert(encode_login_result_rejected_message(&sent, wire, 0) == 2);
  assert(decode_login_result_rejected_message(&got, wire, 0) == 2);
  equal_login_result_rejected_message(&got, &sent);

  for (size_t i = 0; i < 2; i++) { wire[i] = arbitrary(); }
  assert(decode_login_result_rejected_message(&got, wire, 0) == 2);
  assert(encode_login_result_rejected_message(&got, again, 0) == 2);
  for (size_t i = 0; i < 2; i++) { assert(again[i] == wire[i]); }
}

/* ---- End Of Message Message: 6 bytes ----------------------------------------- */

/* Tcp end of message marker terminating a retransmission or snapshot session. */
typedef struct {
  uint8_t multicast_group_number;    /* byte 0 */
  uint8_t number_of_system_reboots;  /* byte 1 */
  uint8_t next_sequence_number[4];   /* bytes 2 to 5 */
} EndOfMessageMessage;

/* any End Of Message Message at all: every byte one the checker chooses */
static void any_end_of_message_message(EndOfMessageMessage *record) {
  record->multicast_group_number = arbitrary();
  record->number_of_system_reboots = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->next_sequence_number[i] = arbitrary(); }
}

/* End Of Message Message to the wire: 6 bytes from at, returning where the next byte goes */
static size_t encode_end_of_message_message(const EndOfMessageMessage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->multicast_group_number;
  wire[at++] = record->number_of_system_reboots;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->next_sequence_number[i]; }

  return at;
}

/* End Of Message Message off the wire: 6 bytes from at, returning where the next byte lies */
static size_t decode_end_of_message_message(EndOfMessageMessage *record, const uint8_t *wire, size_t at) {
  record->multicast_group_number = wire[at++];
  record->number_of_system_reboots = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->next_sequence_number[i] = wire[at++]; }

  return at;
}

/* what was read of End Of Message Message is what was written, byte for byte */
static void equal_end_of_message_message(const EndOfMessageMessage *read, const EndOfMessageMessage *written) {
  assert(read->multicast_group_number == written->multicast_group_number);
  assert(read->number_of_system_reboots == written->number_of_system_reboots);
  for (size_t i = 0; i < 4; i++) { assert(read->next_sequence_number[i] == written->next_sequence_number[i]); }
}

/* End Of Message Message: written and read back, then read and written back */
static void check_end_of_message_message(void) {
  EndOfMessageMessage sent;
  EndOfMessageMessage got;
  uint8_t wire[6];
  uint8_t again[6];

  any_end_of_message_message(&sent);
  assert(encode_end_of_message_message(&sent, wire, 0) == 6);
  assert(decode_end_of_message_message(&got, wire, 0) == 6);
  equal_end_of_message_message(&got, &sent);

  for (size_t i = 0; i < 6; i++) { wire[i] = arbitrary(); }
  assert(decode_end_of_message_message(&got, wire, 0) == 6);
  assert(encode_end_of_message_message(&got, again, 0) == 6);
  for (size_t i = 0; i < 6; i++) { assert(again[i] == wire[i]); }
}

/* ---- What esbmc checks ------------------------------------------------------- */

/* every record of the protocol, each on its own buffers */
static void checks(void) {
  check_tcp_packet_header();
  check_login_request_retransmission_message();
  check_login_request_snapshot_message();
  check_login_result_accepted_message();
  check_login_result_rejected_message();
  check_end_of_message_message();
}

int main(void) {
#ifdef CONCRETE
  for (pattern = 0; pattern < 4; pattern++) { checks(); }
#else
  checks();
#endif

  return 0;
}
