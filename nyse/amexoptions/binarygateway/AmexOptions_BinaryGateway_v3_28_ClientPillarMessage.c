// nyse/amexoptions/binarygateway/AmexOptions_BinaryGateway_v3_28_ClientPillarMessage.c
/*
 * New York Stock Exchange Binary Gateway
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
 *   - a Reassemble rule
 *   - a length prefix framing what follows
 *   - a field present only on a condition
 *   - a run filling what frames it
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

/* ---- Msg Header: 4 bytes ----------------------------------------------------- */

/* Pillar Stream Message Header */
typedef struct {
  uint8_t msg_type[2];    /* bytes 0 to 1 */
  uint8_t msg_length[2];  /* bytes 2 to 3 */
} MsgHeader;

/* any Msg Header at all: every byte one the checker chooses */
static void any_msg_header(MsgHeader *record) {
  for (size_t i = 0; i < 2; i++) { record->msg_type[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->msg_length[i] = arbitrary(); }
}

/* Msg Header to the wire: 4 bytes from at, returning where the next byte goes */
static size_t encode_msg_header(const MsgHeader *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->msg_type[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->msg_length[i]; }

  return at;
}

/* Msg Header off the wire: 4 bytes from at, returning where the next byte lies */
static size_t decode_msg_header(MsgHeader *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->msg_type[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->msg_length[i] = wire[at++]; }

  return at;
}

/* what was read of Msg Header is what was written, byte for byte */
static void equal_msg_header(const MsgHeader *read, const MsgHeader *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->msg_type[i] == written->msg_type[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->msg_length[i] == written->msg_length[i]); }
}

/* Msg Header: written and read back, then read and written back */
static void check_msg_header(void) {
  MsgHeader sent;
  MsgHeader got;
  uint8_t wire[4];
  uint8_t again[4];

  any_msg_header(&sent);
  assert(encode_msg_header(&sent, wire, 0) == 4);
  assert(decode_msg_header(&got, wire, 0) == 4);
  equal_msg_header(&got, &sent);

  for (size_t i = 0; i < 4; i++) { wire[i] = arbitrary(); }
  assert(decode_msg_header(&got, wire, 0) == 4);
  assert(encode_msg_header(&got, again, 0) == 4);
  for (size_t i = 0; i < 4; i++) { assert(again[i] == wire[i]); }
}

/* ---- Stream Id: 8 bytes ------------------------------------------------------ */

/* Pillar Stream Protocol Stream Identifier */
typedef struct {
  uint8_t sess[4];   /* bytes 0 to 3 */
  uint8_t value[4];  /* bytes 4 to 7 */
} StreamId;

/* any Stream Id at all: every byte one the checker chooses */
static void any_stream_id(StreamId *record) {
  for (size_t i = 0; i < 4; i++) { record->sess[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->value[i] = arbitrary(); }
}

/* Stream Id to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_stream_id(const StreamId *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->sess[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->value[i]; }

  return at;
}

/* Stream Id off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_stream_id(StreamId *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->sess[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->value[i] = wire[at++]; }

  return at;
}

/* what was read of Stream Id is what was written, byte for byte */
static void equal_stream_id(const StreamId *read, const StreamId *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->sess[i] == written->sess[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->value[i] == written->value[i]); }
}

/* Stream Id: written and read back, then read and written back */
static void check_stream_id(void) {
  StreamId sent;
  StreamId got;
  uint8_t wire[8];
  uint8_t again[8];

  any_stream_id(&sent);
  assert(encode_stream_id(&sent, wire, 0) == 8);
  assert(decode_stream_id(&got, wire, 0) == 8);
  equal_stream_id(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_stream_id(&got, wire, 0) == 8);
  assert(encode_stream_id(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Seq Msg Id: 16 bytes ---------------------------------------------------- */

/* Pillar Stream Sequenced Message Identifier */
typedef struct {
  StreamId stream_id;  /* bytes 0 to 7 */
  uint8_t seq[8];      /* bytes 8 to 15 */
} SeqMsgId;

/* any Seq Msg Id at all: every byte one the checker chooses */
static void any_seq_msg_id(SeqMsgId *record) {
  any_stream_id(&record->stream_id);
  for (size_t i = 0; i < 8; i++) { record->seq[i] = arbitrary(); }
}

/* Seq Msg Id to the wire: 16 bytes from at, returning where the next byte goes */
static size_t encode_seq_msg_id(const SeqMsgId *record, uint8_t *wire, size_t at) {
  at = encode_stream_id(&record->stream_id, wire, at);
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->seq[i]; }

  return at;
}

/* Seq Msg Id off the wire: 16 bytes from at, returning where the next byte lies */
static size_t decode_seq_msg_id(SeqMsgId *record, const uint8_t *wire, size_t at) {
  at = decode_stream_id(&record->stream_id, wire, at);
  for (size_t i = 0; i < 8; i++) { record->seq[i] = wire[at++]; }

  return at;
}

/* what was read of Seq Msg Id is what was written, byte for byte */
static void equal_seq_msg_id(const SeqMsgId *read, const SeqMsgId *written) {
  equal_stream_id(&read->stream_id, &written->stream_id);
  for (size_t i = 0; i < 8; i++) { assert(read->seq[i] == written->seq[i]); }
}

/* Seq Msg Id: written and read back, then read and written back */
static void check_seq_msg_id(void) {
  SeqMsgId sent;
  SeqMsgId got;
  uint8_t wire[16];
  uint8_t again[16];

  any_seq_msg_id(&sent);
  assert(encode_seq_msg_id(&sent, wire, 0) == 16);
  assert(decode_seq_msg_id(&got, wire, 0) == 16);
  equal_seq_msg_id(&got, &sent);

  for (size_t i = 0; i < 16; i++) { wire[i] = arbitrary(); }
  assert(decode_seq_msg_id(&got, wire, 0) == 16);
  assert(encode_seq_msg_id(&got, again, 0) == 16);
  for (size_t i = 0; i < 16; i++) { assert(again[i] == wire[i]); }
}

/* ---- Seq Msg Header: 4 bytes ------------------------------------------------- */

/* Pillar Stream Sequenced Message Header */
typedef struct {
  uint8_t seq_msg_type[2];    /* bytes 0 to 1 */
  uint8_t seq_msg_length[2];  /* bytes 2 to 3 */
} SeqMsgHeader;

/* any Seq Msg Header at all: every byte one the checker chooses */
static void any_seq_msg_header(SeqMsgHeader *record) {
  for (size_t i = 0; i < 2; i++) { record->seq_msg_type[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->seq_msg_length[i] = arbitrary(); }
}

/* Seq Msg Header to the wire: 4 bytes from at, returning where the next byte goes */
static size_t encode_seq_msg_header(const SeqMsgHeader *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->seq_msg_type[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->seq_msg_length[i]; }

  return at;
}

/* Seq Msg Header off the wire: 4 bytes from at, returning where the next byte lies */
static size_t decode_seq_msg_header(SeqMsgHeader *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->seq_msg_type[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->seq_msg_length[i] = wire[at++]; }

  return at;
}

/* what was read of Seq Msg Header is what was written, byte for byte */
static void equal_seq_msg_header(const SeqMsgHeader *read, const SeqMsgHeader *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->seq_msg_type[i] == written->seq_msg_type[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->seq_msg_length[i] == written->seq_msg_length[i]); }
}

/* Seq Msg Header: written and read back, then read and written back */
static void check_seq_msg_header(void) {
  SeqMsgHeader sent;
  SeqMsgHeader got;
  uint8_t wire[4];
  uint8_t again[4];

  any_seq_msg_header(&sent);
  assert(encode_seq_msg_header(&sent, wire, 0) == 4);
  assert(decode_seq_msg_header(&got, wire, 0) == 4);
  equal_seq_msg_header(&got, &sent);

  for (size_t i = 0; i < 4; i++) { wire[i] = arbitrary(); }
  assert(decode_seq_msg_header(&got, wire, 0) == 4);
  assert(encode_seq_msg_header(&got, again, 0) == 4);
  for (size_t i = 0; i < 4; i++) { assert(again[i] == wire[i]); }
}

/* ---- Sub Msg Header: 4 bytes ------------------------------------------------- */

/* Pillar Stream Sub Message Item Header */
typedef struct {
  uint8_t sub_msg_type[2];    /* bytes 0 to 1 */
  uint8_t sub_msg_length[2];  /* bytes 2 to 3 */
} SubMsgHeader;

/* any Sub Msg Header at all: every byte one the checker chooses */
static void any_sub_msg_header(SubMsgHeader *record) {
  for (size_t i = 0; i < 2; i++) { record->sub_msg_type[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->sub_msg_length[i] = arbitrary(); }
}

/* Sub Msg Header to the wire: 4 bytes from at, returning where the next byte goes */
static size_t encode_sub_msg_header(const SubMsgHeader *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->sub_msg_type[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->sub_msg_length[i]; }

  return at;
}

/* Sub Msg Header off the wire: 4 bytes from at, returning where the next byte lies */
static size_t decode_sub_msg_header(SubMsgHeader *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->sub_msg_type[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->sub_msg_length[i] = wire[at++]; }

  return at;
}

/* what was read of Sub Msg Header is what was written, byte for byte */
static void equal_sub_msg_header(const SubMsgHeader *read, const SubMsgHeader *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->sub_msg_type[i] == written->sub_msg_type[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->sub_msg_length[i] == written->sub_msg_length[i]); }
}

/* Sub Msg Header: written and read back, then read and written back */
static void check_sub_msg_header(void) {
  SubMsgHeader sent;
  SubMsgHeader got;
  uint8_t wire[4];
  uint8_t again[4];

  any_sub_msg_header(&sent);
  assert(encode_sub_msg_header(&sent, wire, 0) == 4);
  assert(decode_sub_msg_header(&got, wire, 0) == 4);
  equal_sub_msg_header(&got, &sent);

  for (size_t i = 0; i < 4; i++) { wire[i] = arbitrary(); }
  assert(decode_sub_msg_header(&got, wire, 0) == 4);
  assert(encode_sub_msg_header(&got, again, 0) == 4);
  for (size_t i = 0; i < 4; i++) { assert(again[i] == wire[i]); }
}

/* ---- What esbmc checks ------------------------------------------------------- */

/* every record of the protocol, each on its own buffers */
static void checks(void) {
  check_msg_header();
  check_stream_id();
  check_seq_msg_id();
  check_seq_msg_header();
  check_sub_msg_header();
}

int main(void) {
#ifdef CONCRETE
  for (pattern = 0; pattern < 4; pattern++) { checks(); }
#else
  checks();
#endif

  return 0;
}
