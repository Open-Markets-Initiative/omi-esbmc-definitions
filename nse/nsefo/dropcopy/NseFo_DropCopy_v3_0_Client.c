// nse/nsefo/dropcopy/NseFo_DropCopy_v3_0_Client.c
/*
 * National Stock Exchange of India Ltd Drop Copy
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

/* ---- Packet Header: 22 bytes ------------------------------------------------- */

/* Drop copy twenty two byte packet header */
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

/* ---- Request Message Header: 24 bytes ---------------------------------------- */

/* REQUEST_MESSAGE_HEADER */
typedef struct {
  uint8_t transaction_code[2];         /* bytes 0 to 1 */
  uint8_t trader_id[4];                /* bytes 2 to 5 */
  uint8_t request_sequence_number[8];  /* bytes 6 to 13 */
  uint8_t partition_id[6];             /* bytes 14 to 19 */
  uint8_t concurrent_login_id[2];      /* bytes 20 to 21 */
  uint8_t func_indc;                   /* byte 22 */
  uint8_t reserve;                     /* byte 23 */
} RequestMessageHeader;

/* any Request Message Header at all: every byte one the checker chooses */
static void any_request_message_header(RequestMessageHeader *record) {
  for (size_t i = 0; i < 2; i++) { record->transaction_code[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->trader_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->request_sequence_number[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->partition_id[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->concurrent_login_id[i] = arbitrary(); }
  record->func_indc = arbitrary();
  record->reserve = arbitrary();
}

/* Request Message Header to the wire: 24 bytes from at, returning where the next byte goes */
static size_t encode_request_message_header(const RequestMessageHeader *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->transaction_code[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->trader_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->request_sequence_number[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->partition_id[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->concurrent_login_id[i]; }
  wire[at++] = record->func_indc;
  wire[at++] = record->reserve;

  return at;
}

/* Request Message Header off the wire: 24 bytes from at, returning where the next byte lies */
static size_t decode_request_message_header(RequestMessageHeader *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->transaction_code[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->trader_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->request_sequence_number[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->partition_id[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->concurrent_login_id[i] = wire[at++]; }
  record->func_indc = wire[at++];
  record->reserve = wire[at++];

  return at;
}

/* what was read of Request Message Header is what was written, byte for byte */
static void equal_request_message_header(const RequestMessageHeader *read, const RequestMessageHeader *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->transaction_code[i] == written->transaction_code[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->trader_id[i] == written->trader_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->request_sequence_number[i] == written->request_sequence_number[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->partition_id[i] == written->partition_id[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->concurrent_login_id[i] == written->concurrent_login_id[i]); }
  assert(read->func_indc == written->func_indc);
  assert(read->reserve == written->reserve);
}

/* Request Message Header: written and read back, then read and written back */
static void check_request_message_header(void) {
  RequestMessageHeader sent;
  RequestMessageHeader got;
  uint8_t wire[24];
  uint8_t again[24];

  any_request_message_header(&sent);
  assert(encode_request_message_header(&sent, wire, 0) == 24);
  assert(decode_request_message_header(&got, wire, 0) == 24);
  equal_request_message_header(&got, &sent);

  for (size_t i = 0; i < 24; i++) { wire[i] = arbitrary(); }
  assert(decode_request_message_header(&got, wire, 0) == 24);
  assert(encode_request_message_header(&got, again, 0) == 24);
  for (size_t i = 0; i < 24; i++) { assert(again[i] == wire[i]); }
}

/* ---- Dc Signon In Message: 16 bytes ------------------------------------------ */

/* Logs the member on to a partition of the drop copy service */
typedef struct {
  uint8_t password[8];     /* bytes 0 to 7 */
  uint8_t session_key[8];  /* bytes 8 to 15 */
} DcSignonInMessage;

/* any Dc Signon In Message at all: every byte one the checker chooses */
static void any_dc_signon_in_message(DcSignonInMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->password[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->session_key[i] = arbitrary(); }
}

/* Dc Signon In Message to the wire: 16 bytes from at, returning where the next byte goes */
static size_t encode_dc_signon_in_message(const DcSignonInMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->password[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->session_key[i]; }

  return at;
}

/* Dc Signon In Message off the wire: 16 bytes from at, returning where the next byte lies */
static size_t decode_dc_signon_in_message(DcSignonInMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->password[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->session_key[i] = wire[at++]; }

  return at;
}

/* what was read of Dc Signon In Message is what was written, byte for byte */
static void equal_dc_signon_in_message(const DcSignonInMessage *read, const DcSignonInMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->password[i] == written->password[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->session_key[i] == written->session_key[i]); }
}

/* Dc Signon In Message: written and read back, then read and written back */
static void check_dc_signon_in_message(void) {
  DcSignonInMessage sent;
  DcSignonInMessage got;
  uint8_t wire[16];
  uint8_t again[16];

  any_dc_signon_in_message(&sent);
  assert(encode_dc_signon_in_message(&sent, wire, 0) == 16);
  assert(decode_dc_signon_in_message(&got, wire, 0) == 16);
  equal_dc_signon_in_message(&got, &sent);

  for (size_t i = 0; i < 16; i++) { wire[i] = arbitrary(); }
  assert(decode_dc_signon_in_message(&got, wire, 0) == 16);
  assert(encode_dc_signon_in_message(&got, again, 0) == 16);
  for (size_t i = 0; i < 16; i++) { assert(again[i] == wire[i]); }
}

/* ---- Dc Trd Subscription Request Message: 8 bytes ---------------------------- */

/* Subscribes to the trade only drop copy on this partition from the named sequence number */
typedef struct {
  uint8_t sequence_number[8];  /* bytes 0 to 7 */
} DcTrdSubscriptionRequestMessage;

/* any Dc Trd Subscription Request Message at all: every byte one the checker chooses */
static void any_dc_trd_subscription_request_message(DcTrdSubscriptionRequestMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->sequence_number[i] = arbitrary(); }
}

/* Dc Trd Subscription Request Message to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_dc_trd_subscription_request_message(const DcTrdSubscriptionRequestMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->sequence_number[i]; }

  return at;
}

/* Dc Trd Subscription Request Message off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_dc_trd_subscription_request_message(DcTrdSubscriptionRequestMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->sequence_number[i] = wire[at++]; }

  return at;
}

/* what was read of Dc Trd Subscription Request Message is what was written, byte for byte */
static void equal_dc_trd_subscription_request_message(const DcTrdSubscriptionRequestMessage *read, const DcTrdSubscriptionRequestMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->sequence_number[i] == written->sequence_number[i]); }
}

/* Dc Trd Subscription Request Message: written and read back, then read and written back */
static void check_dc_trd_subscription_request_message(void) {
  DcTrdSubscriptionRequestMessage sent;
  DcTrdSubscriptionRequestMessage got;
  uint8_t wire[8];
  uint8_t again[8];

  any_dc_trd_subscription_request_message(&sent);
  assert(encode_dc_trd_subscription_request_message(&sent, wire, 0) == 8);
  assert(decode_dc_trd_subscription_request_message(&got, wire, 0) == 8);
  equal_dc_trd_subscription_request_message(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_dc_trd_subscription_request_message(&got, wire, 0) == 8);
  assert(encode_dc_trd_subscription_request_message(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Dc Ont Subscription Request Message: 8 bytes ---------------------------- */

/* Subscribes to the order and trade drop copy on this partition from the named sequence number */
typedef struct {
  uint8_t sequence_number[8];  /* bytes 0 to 7 */
} DcOntSubscriptionRequestMessage;

/* any Dc Ont Subscription Request Message at all: every byte one the checker chooses */
static void any_dc_ont_subscription_request_message(DcOntSubscriptionRequestMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->sequence_number[i] = arbitrary(); }
}

/* Dc Ont Subscription Request Message to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_dc_ont_subscription_request_message(const DcOntSubscriptionRequestMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->sequence_number[i]; }

  return at;
}

/* Dc Ont Subscription Request Message off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_dc_ont_subscription_request_message(DcOntSubscriptionRequestMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->sequence_number[i] = wire[at++]; }

  return at;
}

/* what was read of Dc Ont Subscription Request Message is what was written, byte for byte */
static void equal_dc_ont_subscription_request_message(const DcOntSubscriptionRequestMessage *read, const DcOntSubscriptionRequestMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->sequence_number[i] == written->sequence_number[i]); }
}

/* Dc Ont Subscription Request Message: written and read back, then read and written back */
static void check_dc_ont_subscription_request_message(void) {
  DcOntSubscriptionRequestMessage sent;
  DcOntSubscriptionRequestMessage got;
  uint8_t wire[8];
  uint8_t again[8];

  any_dc_ont_subscription_request_message(&sent);
  assert(encode_dc_ont_subscription_request_message(&sent, wire, 0) == 8);
  assert(decode_dc_ont_subscription_request_message(&got, wire, 0) == 8);
  equal_dc_ont_subscription_request_message(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_dc_ont_subscription_request_message(&got, wire, 0) == 8);
  assert(encode_dc_ont_subscription_request_message(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- What esbmc checks ------------------------------------------------------- */

/* every record of the protocol, each on its own buffers */
static void checks(void) {
  check_packet_header();
  check_request_message_header();
  check_dc_signon_in_message();
  check_dc_trd_subscription_request_message();
  check_dc_ont_subscription_request_message();
}

int main(void) {
#ifdef CONCRETE
  for (pattern = 0; pattern < 4; pattern++) { checks(); }
#else
  checks();
#endif

  return 0;
}
