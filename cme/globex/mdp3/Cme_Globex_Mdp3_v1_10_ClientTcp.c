// cme/globex/mdp3/Cme_Globex_Mdp3_v1_10_ClientTcp.c
/*
 * CME Group Market Data Platform 3
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
 *   - a block whose stated length holds more than its fields
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

/* ---- Client Technical Header: 14 bytes --------------------------------------- */

/* Cme Technical Header sent by the firm to Cme */
typedef struct {
  uint8_t encoding_type[2];            /* bytes 0 to 1 */
  uint8_t message_sequence_number[4];  /* bytes 2 to 5 */
  uint8_t tcp_sending_time[8];         /* bytes 6 to 13 */
} ClientTechnicalHeader;

/* any Client Technical Header at all: every byte one the checker chooses */
static void any_client_technical_header(ClientTechnicalHeader *record) {
  for (size_t i = 0; i < 2; i++) { record->encoding_type[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->message_sequence_number[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->tcp_sending_time[i] = arbitrary(); }
}

/* Client Technical Header to the wire: 14 bytes from at, returning where the next byte goes */
static size_t encode_client_technical_header(const ClientTechnicalHeader *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->encoding_type[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->message_sequence_number[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->tcp_sending_time[i]; }

  return at;
}

/* Client Technical Header off the wire: 14 bytes from at, returning where the next byte lies */
static size_t decode_client_technical_header(ClientTechnicalHeader *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->encoding_type[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->message_sequence_number[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->tcp_sending_time[i] = wire[at++]; }

  return at;
}

/* what was read of Client Technical Header is what was written, byte for byte */
static void equal_client_technical_header(const ClientTechnicalHeader *read, const ClientTechnicalHeader *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->encoding_type[i] == written->encoding_type[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->message_sequence_number[i] == written->message_sequence_number[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->tcp_sending_time[i] == written->tcp_sending_time[i]); }
}

/* Client Technical Header: written and read back, then read and written back */
static void check_client_technical_header(void) {
  ClientTechnicalHeader sent;
  ClientTechnicalHeader got;
  uint8_t wire[14];
  uint8_t again[14];

  any_client_technical_header(&sent);
  assert(encode_client_technical_header(&sent, wire, 0) == 14);
  assert(decode_client_technical_header(&got, wire, 0) == 14);
  equal_client_technical_header(&got, &sent);

  for (size_t i = 0; i < 14; i++) { wire[i] = arbitrary(); }
  assert(decode_client_technical_header(&got, wire, 0) == 14);
  assert(encode_client_technical_header(&got, again, 0) == 14);
  for (size_t i = 0; i < 14; i++) { assert(again[i] == wire[i]); }
}

/* ---- Simple Binary Header: 8 bytes ------------------------------------------- */

/* Template ID and length of message root */
typedef struct {
  uint8_t block_length[2];  /* bytes 0 to 1 */
  uint8_t template_id[2];   /* bytes 2 to 3 */
  uint8_t schema_id[2];     /* bytes 4 to 5 */
  uint8_t version[2];       /* bytes 6 to 7 */
} SimpleBinaryHeader;

/* any Simple Binary Header at all: every byte one the checker chooses */
static void any_simple_binary_header(SimpleBinaryHeader *record) {
  for (size_t i = 0; i < 2; i++) { record->block_length[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->template_id[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->schema_id[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->version[i] = arbitrary(); }
}

/* Simple Binary Header to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_simple_binary_header(const SimpleBinaryHeader *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->block_length[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->template_id[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->schema_id[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->version[i]; }

  return at;
}

/* Simple Binary Header off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_simple_binary_header(SimpleBinaryHeader *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->block_length[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->template_id[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->schema_id[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->version[i] = wire[at++]; }

  return at;
}

/* what was read of Simple Binary Header is what was written, byte for byte */
static void equal_simple_binary_header(const SimpleBinaryHeader *read, const SimpleBinaryHeader *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->block_length[i] == written->block_length[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->template_id[i] == written->template_id[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->schema_id[i] == written->schema_id[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->version[i] == written->version[i]); }
}

/* Simple Binary Header: written and read back, then read and written back */
static void check_simple_binary_header(void) {
  SimpleBinaryHeader sent;
  SimpleBinaryHeader got;
  uint8_t wire[8];
  uint8_t again[8];

  any_simple_binary_header(&sent);
  assert(encode_simple_binary_header(&sent, wire, 0) == 8);
  assert(decode_simple_binary_header(&got, wire, 0) == 8);
  equal_simple_binary_header(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_simple_binary_header(&got, wire, 0) == 8);
  assert(encode_simple_binary_header(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Message Header: 10 bytes ------------------------------------------------ */

/* Message Size followed by the Simple Binary Header */
typedef struct {
  uint8_t message_size[2];                  /* bytes 0 to 1 */
  SimpleBinaryHeader simple_binary_header;  /* bytes 2 to 9 */
} MessageHeader;

/* any Message Header at all: every byte one the checker chooses */
static void any_message_header(MessageHeader *record) {
  for (size_t i = 0; i < 2; i++) { record->message_size[i] = arbitrary(); }
  any_simple_binary_header(&record->simple_binary_header);
}

/* Message Header to the wire: 10 bytes from at, returning where the next byte goes */
static size_t encode_message_header(const MessageHeader *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->message_size[i]; }
  at = encode_simple_binary_header(&record->simple_binary_header, wire, at);

  return at;
}

/* Message Header off the wire: 10 bytes from at, returning where the next byte lies */
static size_t decode_message_header(MessageHeader *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->message_size[i] = wire[at++]; }
  at = decode_simple_binary_header(&record->simple_binary_header, wire, at);

  return at;
}

/* what was read of Message Header is what was written, byte for byte */
static void equal_message_header(const MessageHeader *read, const MessageHeader *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->message_size[i] == written->message_size[i]); }
  equal_simple_binary_header(&read->simple_binary_header, &written->simple_binary_header);
}

/* Message Header: written and read back, then read and written back */
static void check_message_header(void) {
  MessageHeader sent;
  MessageHeader got;
  uint8_t wire[10];
  uint8_t again[10];

  any_message_header(&sent);
  assert(encode_message_header(&sent, wire, 0) == 10);
  assert(decode_message_header(&got, wire, 0) == 10);
  equal_message_header(&got, &sent);

  for (size_t i = 0; i < 10; i++) { wire[i] = arbitrary(); }
  assert(decode_message_header(&got, wire, 0) == 10);
  assert(encode_message_header(&got, again, 0) == 10);
  for (size_t i = 0; i < 10; i++) { assert(again[i] == wire[i]); }
}

/* ---- Negotiate: 78 bytes ----------------------------------------------------- */

/* Negotiate */
typedef struct {
  uint8_t hmac_signature[32];    /* bytes 0 to 31 */
  uint8_t access_key_id[20];     /* bytes 32 to 51 */
  uint8_t uuid[8];               /* bytes 52 to 59 */
  uint8_t request_timestamp[8];  /* bytes 60 to 67 */
  uint8_t session[5];            /* bytes 68 to 72 */
  uint8_t firm[5];               /* bytes 73 to 77 */
} Negotiate;

/* any Negotiate at all: every byte one the checker chooses */
static void any_negotiate(Negotiate *record) {
  for (size_t i = 0; i < 32; i++) { record->hmac_signature[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->access_key_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->uuid[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->request_timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 5; i++) { record->session[i] = arbitrary(); }
  for (size_t i = 0; i < 5; i++) { record->firm[i] = arbitrary(); }
}

/* Negotiate to the wire: 78 bytes from at, returning where the next byte goes */
static size_t encode_negotiate(const Negotiate *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 32; i++) { wire[at++] = record->hmac_signature[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->access_key_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->uuid[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->request_timestamp[i]; }
  for (size_t i = 0; i < 5; i++) { wire[at++] = record->session[i]; }
  for (size_t i = 0; i < 5; i++) { wire[at++] = record->firm[i]; }

  return at;
}

/* Negotiate off the wire: 78 bytes from at, returning where the next byte lies */
static size_t decode_negotiate(Negotiate *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 32; i++) { record->hmac_signature[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->access_key_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->uuid[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->request_timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 5; i++) { record->session[i] = wire[at++]; }
  for (size_t i = 0; i < 5; i++) { record->firm[i] = wire[at++]; }

  return at;
}

/* what was read of Negotiate is what was written, byte for byte */
static void equal_negotiate(const Negotiate *read, const Negotiate *written) {
  for (size_t i = 0; i < 32; i++) { assert(read->hmac_signature[i] == written->hmac_signature[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->access_key_id[i] == written->access_key_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->uuid[i] == written->uuid[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->request_timestamp[i] == written->request_timestamp[i]); }
  for (size_t i = 0; i < 5; i++) { assert(read->session[i] == written->session[i]); }
  for (size_t i = 0; i < 5; i++) { assert(read->firm[i] == written->firm[i]); }
}

/* Negotiate: written and read back, then read and written back */
static void check_negotiate(void) {
  Negotiate sent;
  Negotiate got;
  uint8_t wire[78];
  uint8_t again[78];

  any_negotiate(&sent);
  assert(encode_negotiate(&sent, wire, 0) == 78);
  assert(decode_negotiate(&got, wire, 0) == 78);
  equal_negotiate(&got, &sent);

  for (size_t i = 0; i < 78; i++) { wire[i] = arbitrary(); }
  assert(decode_negotiate(&got, wire, 0) == 78);
  assert(encode_negotiate(&got, again, 0) == 78);
  for (size_t i = 0; i < 78; i++) { assert(again[i] == wire[i]); }
}

/* ---- Terminate: 70 bytes ----------------------------------------------------- */

/* Terminate */
typedef struct {
  uint8_t reason[48];            /* bytes 0 to 47 */
  uint8_t uuid[8];               /* bytes 48 to 55 */
  uint8_t request_timestamp[8];  /* bytes 56 to 63 */
  uint8_t error_codes;           /* byte 64 */
  uint8_t padding_5[5];          /* bytes 65 to 69 */
} Terminate;

/* any Terminate at all: every byte one the checker chooses */
static void any_terminate(Terminate *record) {
  for (size_t i = 0; i < 48; i++) { record->reason[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->uuid[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->request_timestamp[i] = arbitrary(); }
  record->error_codes = arbitrary();
  for (size_t i = 0; i < 5; i++) { record->padding_5[i] = arbitrary(); }
}

/* Terminate to the wire: 70 bytes from at, returning where the next byte goes */
static size_t encode_terminate(const Terminate *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 48; i++) { wire[at++] = record->reason[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->uuid[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->request_timestamp[i]; }
  wire[at++] = record->error_codes;
  for (size_t i = 0; i < 5; i++) { wire[at++] = record->padding_5[i]; }

  return at;
}

/* Terminate off the wire: 70 bytes from at, returning where the next byte lies */
static size_t decode_terminate(Terminate *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 48; i++) { record->reason[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->uuid[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->request_timestamp[i] = wire[at++]; }
  record->error_codes = wire[at++];
  for (size_t i = 0; i < 5; i++) { record->padding_5[i] = wire[at++]; }

  return at;
}

/* what was read of Terminate is what was written, byte for byte */
static void equal_terminate(const Terminate *read, const Terminate *written) {
  for (size_t i = 0; i < 48; i++) { assert(read->reason[i] == written->reason[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->uuid[i] == written->uuid[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->request_timestamp[i] == written->request_timestamp[i]); }
  assert(read->error_codes == written->error_codes);
  for (size_t i = 0; i < 5; i++) { assert(read->padding_5[i] == written->padding_5[i]); }
}

/* Terminate: written and read back, then read and written back */
static void check_terminate(void) {
  Terminate sent;
  Terminate got;
  uint8_t wire[70];
  uint8_t again[70];

  any_terminate(&sent);
  assert(encode_terminate(&sent, wire, 0) == 70);
  assert(decode_terminate(&got, wire, 0) == 70);
  equal_terminate(&got, &sent);

  for (size_t i = 0; i < 70; i++) { wire[i] = arbitrary(); }
  assert(decode_terminate(&got, wire, 0) == 70);
  assert(encode_terminate(&got, again, 0) == 70);
  for (size_t i = 0; i < 70; i++) { assert(again[i] == wire[i]); }
}

/* ---- Group Size: 3 bytes ----------------------------------------------------- */

/* Repeating group dimensions */
typedef struct {
  uint8_t block_length[2];  /* bytes 0 to 1 */
  uint8_t num_in_group;     /* byte 2 */
} GroupSize;

/* any Group Size at all: every byte one the checker chooses */
static void any_group_size(GroupSize *record) {
  for (size_t i = 0; i < 2; i++) { record->block_length[i] = arbitrary(); }
  record->num_in_group = arbitrary();
}

/* Group Size to the wire: 3 bytes from at, returning where the next byte goes */
static size_t encode_group_size(const GroupSize *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->block_length[i]; }
  wire[at++] = record->num_in_group;

  return at;
}

/* Group Size off the wire: 3 bytes from at, returning where the next byte lies */
static size_t decode_group_size(GroupSize *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->block_length[i] = wire[at++]; }
  record->num_in_group = wire[at++];

  return at;
}

/* what was read of Group Size is what was written, byte for byte */
static void equal_group_size(const GroupSize *read, const GroupSize *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->block_length[i] == written->block_length[i]); }
  assert(read->num_in_group == written->num_in_group);
}

/* Group Size: written and read back, then read and written back */
static void check_group_size(void) {
  GroupSize sent;
  GroupSize got;
  uint8_t wire[3];
  uint8_t again[3];

  any_group_size(&sent);
  assert(encode_group_size(&sent, wire, 0) == 3);
  assert(decode_group_size(&got, wire, 0) == 3);
  equal_group_size(&got, &sent);

  for (size_t i = 0; i < 3; i++) { wire[i] = arbitrary(); }
  assert(decode_group_size(&got, wire, 0) == 3);
  assert(encode_group_size(&got, again, 0) == 3);
  for (size_t i = 0; i < 3; i++) { assert(again[i] == wire[i]); }
}

/* ---- What esbmc checks ------------------------------------------------------- */

/* every record of the protocol, each on its own buffers */
static void checks(void) {
  check_client_technical_header();
  check_simple_binary_header();
  check_message_header();
  check_negotiate();
  check_terminate();
  check_group_size();
}

int main(void) {
#ifdef CONCRETE
  for (pattern = 0; pattern < 4; pattern++) { checks(); }
#else
  checks();
#endif

  return 0;
}
