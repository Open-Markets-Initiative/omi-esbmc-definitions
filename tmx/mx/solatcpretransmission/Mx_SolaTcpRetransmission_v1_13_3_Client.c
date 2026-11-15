// tmx/mx/solatcpretransmission/Mx_SolaTcpRetransmission_v1_13_3_Client.c
/*
 * TMX Group Sola Tcp Retransmission
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

/* ---- Client Message Header: 12 bytes ----------------------------------------- */

/* Standard Hsvf message header */
typedef struct {
  uint8_t sequence_number[10];     /* bytes 0 to 9 */
  uint8_t client_message_type[2];  /* bytes 10 to 11 */
} ClientMessageHeader;

/* any Client Message Header at all: every byte one the checker chooses */
static void any_client_message_header(ClientMessageHeader *record) {
  for (size_t i = 0; i < 10; i++) { record->sequence_number[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->client_message_type[i] = arbitrary(); }
}

/* Client Message Header to the wire: 12 bytes from at, returning where the next byte goes */
static size_t encode_client_message_header(const ClientMessageHeader *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->sequence_number[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->client_message_type[i]; }

  return at;
}

/* Client Message Header off the wire: 12 bytes from at, returning where the next byte lies */
static size_t decode_client_message_header(ClientMessageHeader *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 10; i++) { record->sequence_number[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->client_message_type[i] = wire[at++]; }

  return at;
}

/* what was read of Client Message Header is what was written, byte for byte */
static void equal_client_message_header(const ClientMessageHeader *read, const ClientMessageHeader *written) {
  for (size_t i = 0; i < 10; i++) { assert(read->sequence_number[i] == written->sequence_number[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->client_message_type[i] == written->client_message_type[i]); }
}

/* Client Message Header: written and read back, then read and written back */
static void check_client_message_header(void) {
  ClientMessageHeader sent;
  ClientMessageHeader got;
  uint8_t wire[12];
  uint8_t again[12];

  any_client_message_header(&sent);
  assert(encode_client_message_header(&sent, wire, 0) == 12);
  assert(decode_client_message_header(&got, wire, 0) == 12);
  equal_client_message_header(&got, &sent);

  for (size_t i = 0; i < 12; i++) { wire[i] = arbitrary(); }
  assert(decode_client_message_header(&got, wire, 0) == 12);
  assert(encode_client_message_header(&got, again, 0) == 12);
  for (size_t i = 0; i < 12; i++) { assert(again[i] == wire[i]); }
}

/* ---- Login Message: 40 bytes ------------------------------------------------- */

/* Login */
typedef struct {
  uint8_t user[16];            /* bytes 0 to 15 */
  uint8_t pwd[16];             /* bytes 16 to 31 */
  uint8_t login_timestamp[6];  /* bytes 32 to 37 */
  uint8_t protocol[2];         /* bytes 38 to 39 */
} LoginMessage;

/* any Login Message at all: every byte one the checker chooses */
static void any_login_message(LoginMessage *record) {
  for (size_t i = 0; i < 16; i++) { record->user[i] = arbitrary(); }
  for (size_t i = 0; i < 16; i++) { record->pwd[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->login_timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->protocol[i] = arbitrary(); }
}

/* Login Message to the wire: 40 bytes from at, returning where the next byte goes */
static size_t encode_login_message(const LoginMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->user[i]; }
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->pwd[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->login_timestamp[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->protocol[i]; }

  return at;
}

/* Login Message off the wire: 40 bytes from at, returning where the next byte lies */
static size_t decode_login_message(LoginMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 16; i++) { record->user[i] = wire[at++]; }
  for (size_t i = 0; i < 16; i++) { record->pwd[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->login_timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->protocol[i] = wire[at++]; }

  return at;
}

/* what was read of Login Message is what was written, byte for byte */
static void equal_login_message(const LoginMessage *read, const LoginMessage *written) {
  for (size_t i = 0; i < 16; i++) { assert(read->user[i] == written->user[i]); }
  for (size_t i = 0; i < 16; i++) { assert(read->pwd[i] == written->pwd[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->login_timestamp[i] == written->login_timestamp[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->protocol[i] == written->protocol[i]); }
}

/* Login Message: written and read back, then read and written back */
static void check_login_message(void) {
  LoginMessage sent;
  LoginMessage got;
  uint8_t wire[40];
  uint8_t again[40];

  any_login_message(&sent);
  assert(encode_login_message(&sent, wire, 0) == 40);
  assert(decode_login_message(&got, wire, 0) == 40);
  equal_login_message(&got, &sent);

  for (size_t i = 0; i < 40; i++) { wire[i] = arbitrary(); }
  assert(decode_login_message(&got, wire, 0) == 40);
  assert(encode_login_message(&got, again, 0) == 40);
  for (size_t i = 0; i < 40; i++) { assert(again[i] == wire[i]); }
}

/* ---- Retransmission Request Message: 22 bytes -------------------------------- */

/* Retransmission Request */
typedef struct {
  uint8_t line[2];    /* bytes 0 to 1 */
  uint8_t start[10];  /* bytes 2 to 11 */
  uint8_t end[10];    /* bytes 12 to 21 */
} RetransmissionRequestMessage;

/* any Retransmission Request Message at all: every byte one the checker chooses */
static void any_retransmission_request_message(RetransmissionRequestMessage *record) {
  for (size_t i = 0; i < 2; i++) { record->line[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->start[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->end[i] = arbitrary(); }
}

/* Retransmission Request Message to the wire: 22 bytes from at, returning where the next byte goes */
static size_t encode_retransmission_request_message(const RetransmissionRequestMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->line[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->start[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->end[i]; }

  return at;
}

/* Retransmission Request Message off the wire: 22 bytes from at, returning where the next byte lies */
static size_t decode_retransmission_request_message(RetransmissionRequestMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->line[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->start[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->end[i] = wire[at++]; }

  return at;
}

/* what was read of Retransmission Request Message is what was written, byte for byte */
static void equal_retransmission_request_message(const RetransmissionRequestMessage *read, const RetransmissionRequestMessage *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->line[i] == written->line[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->start[i] == written->start[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->end[i] == written->end[i]); }
}

/* Retransmission Request Message: written and read back, then read and written back */
static void check_retransmission_request_message(void) {
  RetransmissionRequestMessage sent;
  RetransmissionRequestMessage got;
  uint8_t wire[22];
  uint8_t again[22];

  any_retransmission_request_message(&sent);
  assert(encode_retransmission_request_message(&sent, wire, 0) == 22);
  assert(decode_retransmission_request_message(&got, wire, 0) == 22);
  equal_retransmission_request_message(&got, &sent);

  for (size_t i = 0; i < 22; i++) { wire[i] = arbitrary(); }
  assert(decode_retransmission_request_message(&got, wire, 0) == 22);
  assert(encode_retransmission_request_message(&got, again, 0) == 22);
  for (size_t i = 0; i < 22; i++) { assert(again[i] == wire[i]); }
}

/* ---- What esbmc checks ------------------------------------------------------- */

/* every record of the protocol, each on its own buffers */
static void checks(void) {
  check_client_message_header();
  check_login_message();
  check_retransmission_request_message();
}

int main(void) {
#ifdef CONCRETE
  for (pattern = 0; pattern < 4; pattern++) { checks(); }
#else
  checks();
#endif

  return 0;
}
