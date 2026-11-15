// finra/trace/spds144a/Trace_Spds144A_v2_1.c
/*
 * Financial Industry Regulatory Authority Securitized Products Dissemination Service for 144A Transactions
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
 *   - a run counted by a field
 *   - the dispatch that chooses a message by its type
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

/* ---- Packet Header: 20 bytes ------------------------------------------------- */

typedef struct {
  uint8_t session[10];  /* bytes 0 to 9 */
  uint8_t sequence[8];  /* bytes 10 to 17 */
  uint8_t count[2];     /* bytes 18 to 19 */
} PacketHeader;

/* any Packet Header at all: every byte one the checker chooses */
static void any_packet_header(PacketHeader *record) {
  for (size_t i = 0; i < 10; i++) { record->session[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->sequence[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->count[i] = arbitrary(); }
}

/* Packet Header to the wire: 20 bytes from at, returning where the next byte goes */
static size_t encode_packet_header(const PacketHeader *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->session[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->sequence[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->count[i]; }

  return at;
}

/* Packet Header off the wire: 20 bytes from at, returning where the next byte lies */
static size_t decode_packet_header(PacketHeader *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 10; i++) { record->session[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->sequence[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->count[i] = wire[at++]; }

  return at;
}

/* what was read of Packet Header is what was written, byte for byte */
static void equal_packet_header(const PacketHeader *read, const PacketHeader *written) {
  for (size_t i = 0; i < 10; i++) { assert(read->session[i] == written->session[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->sequence[i] == written->sequence[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->count[i] == written->count[i]); }
}

/* Packet Header: written and read back, then read and written back */
static void check_packet_header(void) {
  PacketHeader sent;
  PacketHeader got;
  uint8_t wire[20];
  uint8_t again[20];

  any_packet_header(&sent);
  assert(encode_packet_header(&sent, wire, 0) == 20);
  assert(decode_packet_header(&got, wire, 0) == 20);
  equal_packet_header(&got, &sent);

  for (size_t i = 0; i < 20; i++) { wire[i] = arbitrary(); }
  assert(decode_packet_header(&got, wire, 0) == 20);
  assert(encode_packet_header(&got, again, 0) == 20);
  for (size_t i = 0; i < 20; i++) { assert(again[i] == wire[i]); }
}

/* ---- Mold Udp64: 3 bytes ----------------------------------------------------- */

/* Mold Udp64 Dfi Message Header */
typedef struct {
  uint8_t length[2];         /* bytes 0 to 1 */
  uint8_t message_category;  /* byte 2 */
} MoldUdp64;

/* any Mold Udp64 at all: every byte one the checker chooses */
static void any_mold_udp64(MoldUdp64 *record) {
  for (size_t i = 0; i < 2; i++) { record->length[i] = arbitrary(); }
  record->message_category = arbitrary();
}

/* Mold Udp64 to the wire: 3 bytes from at, returning where the next byte goes */
static size_t encode_mold_udp64(const MoldUdp64 *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->length[i]; }
  wire[at++] = record->message_category;

  return at;
}

/* Mold Udp64 off the wire: 3 bytes from at, returning where the next byte lies */
static size_t decode_mold_udp64(MoldUdp64 *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->length[i] = wire[at++]; }
  record->message_category = wire[at++];

  return at;
}

/* what was read of Mold Udp64 is what was written, byte for byte */
static void equal_mold_udp64(const MoldUdp64 *read, const MoldUdp64 *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->length[i] == written->length[i]); }
  assert(read->message_category == written->message_category);
}

/* Mold Udp64: written and read back, then read and written back */
static void check_mold_udp64(void) {
  MoldUdp64 sent;
  MoldUdp64 got;
  uint8_t wire[3];
  uint8_t again[3];

  any_mold_udp64(&sent);
  assert(encode_mold_udp64(&sent, wire, 0) == 3);
  assert(decode_mold_udp64(&got, wire, 0) == 3);
  equal_mold_udp64(&got, &sent);

  for (size_t i = 0; i < 3; i++) { wire[i] = arbitrary(); }
  assert(decode_mold_udp64(&got, wire, 0) == 3);
  assert(encode_mold_udp64(&got, again, 0) == 3);
  for (size_t i = 0; i < 3; i++) { assert(again[i] == wire[i]); }
}

/* ---- Datetime: 14 bytes ------------------------------------------------------ */

/* Datetime */
typedef struct {
  uint8_t year[4];    /* bytes 0 to 3 */
  uint8_t month[2];   /* bytes 4 to 5 */
  uint8_t day[2];     /* bytes 6 to 7 */
  uint8_t hour[2];    /* bytes 8 to 9 */
  uint8_t minute[2];  /* bytes 10 to 11 */
  uint8_t second[2];  /* bytes 12 to 13 */
} Datetime;

/* any Datetime at all: every byte one the checker chooses */
static void any_datetime(Datetime *record) {
  for (size_t i = 0; i < 4; i++) { record->year[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->month[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->day[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->hour[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->minute[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->second[i] = arbitrary(); }
}

/* Datetime to the wire: 14 bytes from at, returning where the next byte goes */
static size_t encode_datetime(const Datetime *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->year[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->month[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->day[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->hour[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->minute[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->second[i]; }

  return at;
}

/* Datetime off the wire: 14 bytes from at, returning where the next byte lies */
static size_t decode_datetime(Datetime *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->year[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->month[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->day[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->hour[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->minute[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->second[i] = wire[at++]; }

  return at;
}

/* what was read of Datetime is what was written, byte for byte */
static void equal_datetime(const Datetime *read, const Datetime *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->year[i] == written->year[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->month[i] == written->month[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->day[i] == written->day[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->hour[i] == written->hour[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->minute[i] == written->minute[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->second[i] == written->second[i]); }
}

/* Datetime: written and read back, then read and written back */
static void check_datetime(void) {
  Datetime sent;
  Datetime got;
  uint8_t wire[14];
  uint8_t again[14];

  any_datetime(&sent);
  assert(encode_datetime(&sent, wire, 0) == 14);
  assert(decode_datetime(&got, wire, 0) == 14);
  equal_datetime(&got, &sent);

  for (size_t i = 0; i < 14; i++) { wire[i] = arbitrary(); }
  assert(decode_datetime(&got, wire, 0) == 14);
  assert(encode_datetime(&got, again, 0) == 14);
  for (size_t i = 0; i < 14; i++) { assert(again[i] == wire[i]); }
}

/* ---- Message Header: 22 bytes ------------------------------------------------ */

/* Message Header */
typedef struct {
  uint8_t trade_identifier[7];          /* bytes 0 to 6 */
  uint8_t market_center_originator_id;  /* byte 7 */
  Datetime datetime;                    /* bytes 8 to 21 */
} MessageHeader;

/* any Message Header at all: every byte one the checker chooses */
static void any_message_header(MessageHeader *record) {
  for (size_t i = 0; i < 7; i++) { record->trade_identifier[i] = arbitrary(); }
  record->market_center_originator_id = arbitrary();
  any_datetime(&record->datetime);
}

/* Message Header to the wire: 22 bytes from at, returning where the next byte goes */
static size_t encode_message_header(const MessageHeader *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->trade_identifier[i]; }
  wire[at++] = record->market_center_originator_id;
  at = encode_datetime(&record->datetime, wire, at);

  return at;
}

/* Message Header off the wire: 22 bytes from at, returning where the next byte lies */
static size_t decode_message_header(MessageHeader *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { record->trade_identifier[i] = wire[at++]; }
  record->market_center_originator_id = wire[at++];
  at = decode_datetime(&record->datetime, wire, at);

  return at;
}

/* what was read of Message Header is what was written, byte for byte */
static void equal_message_header(const MessageHeader *read, const MessageHeader *written) {
  for (size_t i = 0; i < 7; i++) { assert(read->trade_identifier[i] == written->trade_identifier[i]); }
  assert(read->market_center_originator_id == written->market_center_originator_id);
  equal_datetime(&read->datetime, &written->datetime);
}

/* Message Header: written and read back, then read and written back */
static void check_message_header(void) {
  MessageHeader sent;
  MessageHeader got;
  uint8_t wire[22];
  uint8_t again[22];

  any_message_header(&sent);
  assert(encode_message_header(&sent, wire, 0) == 22);
  assert(decode_message_header(&got, wire, 0) == 22);
  equal_message_header(&got, &sent);

  for (size_t i = 0; i < 22; i++) { wire[i] = arbitrary(); }
  assert(decode_message_header(&got, wire, 0) == 22);
  assert(encode_message_header(&got, again, 0) == 22);
  for (size_t i = 0; i < 22; i++) { assert(again[i] == wire[i]); }
}

/* ---- Label: 40 bytes --------------------------------------------------------- */

/* Label */
typedef struct {
  uint8_t symbol[14];           /* bytes 0 to 13 */
  uint8_t cusip[9];             /* bytes 14 to 22 */
  uint8_t bsym[12];             /* bytes 23 to 34 */
  uint8_t sub_product_type[5];  /* bytes 35 to 39 */
} Label;

/* any Label at all: every byte one the checker chooses */
static void any_label(Label *record) {
  for (size_t i = 0; i < 14; i++) { record->symbol[i] = arbitrary(); }
  for (size_t i = 0; i < 9; i++) { record->cusip[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->bsym[i] = arbitrary(); }
  for (size_t i = 0; i < 5; i++) { record->sub_product_type[i] = arbitrary(); }
}

/* Label to the wire: 40 bytes from at, returning where the next byte goes */
static size_t encode_label(const Label *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 14; i++) { wire[at++] = record->symbol[i]; }
  for (size_t i = 0; i < 9; i++) { wire[at++] = record->cusip[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->bsym[i]; }
  for (size_t i = 0; i < 5; i++) { wire[at++] = record->sub_product_type[i]; }

  return at;
}

/* Label off the wire: 40 bytes from at, returning where the next byte lies */
static size_t decode_label(Label *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 14; i++) { record->symbol[i] = wire[at++]; }
  for (size_t i = 0; i < 9; i++) { record->cusip[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->bsym[i] = wire[at++]; }
  for (size_t i = 0; i < 5; i++) { record->sub_product_type[i] = wire[at++]; }

  return at;
}

/* what was read of Label is what was written, byte for byte */
static void equal_label(const Label *read, const Label *written) {
  for (size_t i = 0; i < 14; i++) { assert(read->symbol[i] == written->symbol[i]); }
  for (size_t i = 0; i < 9; i++) { assert(read->cusip[i] == written->cusip[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->bsym[i] == written->bsym[i]); }
  for (size_t i = 0; i < 5; i++) { assert(read->sub_product_type[i] == written->sub_product_type[i]); }
}

/* Label: written and read back, then read and written back */
static void check_label(void) {
  Label sent;
  Label got;
  uint8_t wire[40];
  uint8_t again[40];

  any_label(&sent);
  assert(encode_label(&sent, wire, 0) == 40);
  assert(decode_label(&got, wire, 0) == 40);
  equal_label(&got, &sent);

  for (size_t i = 0; i < 40; i++) { wire[i] = arbitrary(); }
  assert(decode_label(&got, wire, 0) == 40);
  assert(encode_label(&got, again, 0) == 40);
  for (size_t i = 0; i < 40; i++) { assert(again[i] == wire[i]); }
}

/* ---- Original Dissemination Date: 8 bytes ------------------------------------ */

/* Original Dissemination Date */
typedef struct {
  uint8_t year[4];   /* bytes 0 to 3 */
  uint8_t month[2];  /* bytes 4 to 5 */
  uint8_t day[2];    /* bytes 6 to 7 */
} OriginalDisseminationDate;

/* any Original Dissemination Date at all: every byte one the checker chooses */
static void any_original_dissemination_date(OriginalDisseminationDate *record) {
  for (size_t i = 0; i < 4; i++) { record->year[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->month[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->day[i] = arbitrary(); }
}

/* Original Dissemination Date to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_original_dissemination_date(const OriginalDisseminationDate *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->year[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->month[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->day[i]; }

  return at;
}

/* Original Dissemination Date off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_original_dissemination_date(OriginalDisseminationDate *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->year[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->month[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->day[i] = wire[at++]; }

  return at;
}

/* what was read of Original Dissemination Date is what was written, byte for byte */
static void equal_original_dissemination_date(const OriginalDisseminationDate *read, const OriginalDisseminationDate *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->year[i] == written->year[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->month[i] == written->month[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->day[i] == written->day[i]); }
}

/* Original Dissemination Date: written and read back, then read and written back */
static void check_original_dissemination_date(void) {
  OriginalDisseminationDate sent;
  OriginalDisseminationDate got;
  uint8_t wire[8];
  uint8_t again[8];

  any_original_dissemination_date(&sent);
  assert(encode_original_dissemination_date(&sent, wire, 0) == 8);
  assert(decode_original_dissemination_date(&got, wire, 0) == 8);
  equal_original_dissemination_date(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_original_dissemination_date(&got, wire, 0) == 8);
  assert(encode_original_dissemination_date(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Execution Datetime: 14 bytes -------------------------------------------- */

/* Execution Datetime */
typedef struct {
  uint8_t year[4];    /* bytes 0 to 3 */
  uint8_t month[2];   /* bytes 4 to 5 */
  uint8_t day[2];     /* bytes 6 to 7 */
  uint8_t hour[2];    /* bytes 8 to 9 */
  uint8_t minute[2];  /* bytes 10 to 11 */
  uint8_t second[2];  /* bytes 12 to 13 */
} ExecutionDatetime;

/* any Execution Datetime at all: every byte one the checker chooses */
static void any_execution_datetime(ExecutionDatetime *record) {
  for (size_t i = 0; i < 4; i++) { record->year[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->month[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->day[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->hour[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->minute[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->second[i] = arbitrary(); }
}

/* Execution Datetime to the wire: 14 bytes from at, returning where the next byte goes */
static size_t encode_execution_datetime(const ExecutionDatetime *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->year[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->month[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->day[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->hour[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->minute[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->second[i]; }

  return at;
}

/* Execution Datetime off the wire: 14 bytes from at, returning where the next byte lies */
static size_t decode_execution_datetime(ExecutionDatetime *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->year[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->month[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->day[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->hour[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->minute[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->second[i] = wire[at++]; }

  return at;
}

/* what was read of Execution Datetime is what was written, byte for byte */
static void equal_execution_datetime(const ExecutionDatetime *read, const ExecutionDatetime *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->year[i] == written->year[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->month[i] == written->month[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->day[i] == written->day[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->hour[i] == written->hour[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->minute[i] == written->minute[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->second[i] == written->second[i]); }
}

/* Execution Datetime: written and read back, then read and written back */
static void check_execution_datetime(void) {
  ExecutionDatetime sent;
  ExecutionDatetime got;
  uint8_t wire[14];
  uint8_t again[14];

  any_execution_datetime(&sent);
  assert(encode_execution_datetime(&sent, wire, 0) == 14);
  assert(decode_execution_datetime(&got, wire, 0) == 14);
  equal_execution_datetime(&got, &sent);

  for (size_t i = 0; i < 14; i++) { wire[i] = arbitrary(); }
  assert(decode_execution_datetime(&got, wire, 0) == 14);
  assert(encode_execution_datetime(&got, again, 0) == 14);
  for (size_t i = 0; i < 14; i++) { assert(again[i] == wire[i]); }
}

/* ---- Settlement Date: 8 bytes ------------------------------------------------ */

/* Settlement Date */
typedef struct {
  uint8_t year[4];   /* bytes 0 to 3 */
  uint8_t month[2];  /* bytes 4 to 5 */
  uint8_t day[2];    /* bytes 6 to 7 */
} SettlementDate;

/* any Settlement Date at all: every byte one the checker chooses */
static void any_settlement_date(SettlementDate *record) {
  for (size_t i = 0; i < 4; i++) { record->year[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->month[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->day[i] = arbitrary(); }
}

/* Settlement Date to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_settlement_date(const SettlementDate *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->year[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->month[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->day[i]; }

  return at;
}

/* Settlement Date off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_settlement_date(SettlementDate *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->year[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->month[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->day[i] = wire[at++]; }

  return at;
}

/* what was read of Settlement Date is what was written, byte for byte */
static void equal_settlement_date(const SettlementDate *read, const SettlementDate *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->year[i] == written->year[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->month[i] == written->month[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->day[i] == written->day[i]); }
}

/* Settlement Date: written and read back, then read and written back */
static void check_settlement_date(void) {
  SettlementDate sent;
  SettlementDate got;
  uint8_t wire[8];
  uint8_t again[8];

  any_settlement_date(&sent);
  assert(encode_settlement_date(&sent, wire, 0) == 8);
  assert(decode_settlement_date(&got, wire, 0) == 8);
  equal_settlement_date(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_settlement_date(&got, wire, 0) == 8);
  assert(encode_settlement_date(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Trade Information: 71 bytes --------------------------------------------- */

/* Trade Information */
typedef struct {
  uint8_t quantity_indicator;            /* byte 0 */
  uint8_t quantity[14];                  /* bytes 1 to 14 */
  uint8_t price[11];                     /* bytes 15 to 25 */
  uint8_t remuneration;                  /* byte 26 */
  uint8_t special_price_indicator;       /* byte 27 */
  uint8_t side;                          /* byte 28 */
  uint8_t as_of_indicator;               /* byte 29 */
  ExecutionDatetime execution_datetime;  /* bytes 30 to 43 */
  uint8_t future_use[2];                 /* bytes 44 to 45 */
  uint8_t sale_condition_3;              /* byte 46 */
  uint8_t sale_condition_4;              /* byte 47 */
  SettlementDate settlement_date;        /* bytes 48 to 55 */
  uint8_t factor[12];                    /* bytes 56 to 67 */
  uint8_t reporting_party_type;          /* byte 68 */
  uint8_t contra_party_type;             /* byte 69 */
  uint8_t ats_indicator;                 /* byte 70 */
} TradeInformation;

/* any Trade Information at all: every byte one the checker chooses */
static void any_trade_information(TradeInformation *record) {
  record->quantity_indicator = arbitrary();
  for (size_t i = 0; i < 14; i++) { record->quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->price[i] = arbitrary(); }
  record->remuneration = arbitrary();
  record->special_price_indicator = arbitrary();
  record->side = arbitrary();
  record->as_of_indicator = arbitrary();
  any_execution_datetime(&record->execution_datetime);
  for (size_t i = 0; i < 2; i++) { record->future_use[i] = arbitrary(); }
  record->sale_condition_3 = arbitrary();
  record->sale_condition_4 = arbitrary();
  any_settlement_date(&record->settlement_date);
  for (size_t i = 0; i < 12; i++) { record->factor[i] = arbitrary(); }
  record->reporting_party_type = arbitrary();
  record->contra_party_type = arbitrary();
  record->ats_indicator = arbitrary();
}

/* Trade Information to the wire: 71 bytes from at, returning where the next byte goes */
static size_t encode_trade_information(const TradeInformation *record, uint8_t *wire, size_t at) {
  wire[at++] = record->quantity_indicator;
  for (size_t i = 0; i < 14; i++) { wire[at++] = record->quantity[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->price[i]; }
  wire[at++] = record->remuneration;
  wire[at++] = record->special_price_indicator;
  wire[at++] = record->side;
  wire[at++] = record->as_of_indicator;
  at = encode_execution_datetime(&record->execution_datetime, wire, at);
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->future_use[i]; }
  wire[at++] = record->sale_condition_3;
  wire[at++] = record->sale_condition_4;
  at = encode_settlement_date(&record->settlement_date, wire, at);
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->factor[i]; }
  wire[at++] = record->reporting_party_type;
  wire[at++] = record->contra_party_type;
  wire[at++] = record->ats_indicator;

  return at;
}

/* Trade Information off the wire: 71 bytes from at, returning where the next byte lies */
static size_t decode_trade_information(TradeInformation *record, const uint8_t *wire, size_t at) {
  record->quantity_indicator = wire[at++];
  for (size_t i = 0; i < 14; i++) { record->quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->price[i] = wire[at++]; }
  record->remuneration = wire[at++];
  record->special_price_indicator = wire[at++];
  record->side = wire[at++];
  record->as_of_indicator = wire[at++];
  at = decode_execution_datetime(&record->execution_datetime, wire, at);
  for (size_t i = 0; i < 2; i++) { record->future_use[i] = wire[at++]; }
  record->sale_condition_3 = wire[at++];
  record->sale_condition_4 = wire[at++];
  at = decode_settlement_date(&record->settlement_date, wire, at);
  for (size_t i = 0; i < 12; i++) { record->factor[i] = wire[at++]; }
  record->reporting_party_type = wire[at++];
  record->contra_party_type = wire[at++];
  record->ats_indicator = wire[at++];

  return at;
}

/* what was read of Trade Information is what was written, byte for byte */
static void equal_trade_information(const TradeInformation *read, const TradeInformation *written) {
  assert(read->quantity_indicator == written->quantity_indicator);
  for (size_t i = 0; i < 14; i++) { assert(read->quantity[i] == written->quantity[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->price[i] == written->price[i]); }
  assert(read->remuneration == written->remuneration);
  assert(read->special_price_indicator == written->special_price_indicator);
  assert(read->side == written->side);
  assert(read->as_of_indicator == written->as_of_indicator);
  equal_execution_datetime(&read->execution_datetime, &written->execution_datetime);
  for (size_t i = 0; i < 2; i++) { assert(read->future_use[i] == written->future_use[i]); }
  assert(read->sale_condition_3 == written->sale_condition_3);
  assert(read->sale_condition_4 == written->sale_condition_4);
  equal_settlement_date(&read->settlement_date, &written->settlement_date);
  for (size_t i = 0; i < 12; i++) { assert(read->factor[i] == written->factor[i]); }
  assert(read->reporting_party_type == written->reporting_party_type);
  assert(read->contra_party_type == written->contra_party_type);
  assert(read->ats_indicator == written->ats_indicator);
}

/* Trade Information: written and read back, then read and written back */
static void check_trade_information(void) {
  TradeInformation sent;
  TradeInformation got;
  uint8_t wire[71];
  uint8_t again[71];

  any_trade_information(&sent);
  assert(encode_trade_information(&sent, wire, 0) == 71);
  assert(decode_trade_information(&got, wire, 0) == 71);
  equal_trade_information(&got, &sent);

  for (size_t i = 0; i < 71; i++) { wire[i] = arbitrary(); }
  assert(decode_trade_information(&got, wire, 0) == 71);
  assert(encode_trade_information(&got, again, 0) == 71);
  for (size_t i = 0; i < 71; i++) { assert(again[i] == wire[i]); }
}

/* ---- Trade Report Message: 142 bytes ----------------------------------------- */

/* Used to transmit trade transaction information for Abs and certain Cmo transactions */
typedef struct {
  MessageHeader message_header;                           /* bytes 0 to 21 */
  Label label;                                            /* bytes 22 to 61 */
  OriginalDisseminationDate original_dissemination_date;  /* bytes 62 to 69 */
  TradeInformation trade_information;                     /* bytes 70 to 140 */
  uint8_t change_indicator;                               /* byte 141 */
} TradeReportMessage;

/* any Trade Report Message at all: every byte one the checker chooses */
static void any_trade_report_message(TradeReportMessage *record) {
  any_message_header(&record->message_header);
  any_label(&record->label);
  any_original_dissemination_date(&record->original_dissemination_date);
  any_trade_information(&record->trade_information);
  record->change_indicator = arbitrary();
}

/* Trade Report Message to the wire: 142 bytes from at, returning where the next byte goes */
static size_t encode_trade_report_message(const TradeReportMessage *record, uint8_t *wire, size_t at) {
  at = encode_message_header(&record->message_header, wire, at);
  at = encode_label(&record->label, wire, at);
  at = encode_original_dissemination_date(&record->original_dissemination_date, wire, at);
  at = encode_trade_information(&record->trade_information, wire, at);
  wire[at++] = record->change_indicator;

  return at;
}

/* Trade Report Message off the wire: 142 bytes from at, returning where the next byte lies */
static size_t decode_trade_report_message(TradeReportMessage *record, const uint8_t *wire, size_t at) {
  at = decode_message_header(&record->message_header, wire, at);
  at = decode_label(&record->label, wire, at);
  at = decode_original_dissemination_date(&record->original_dissemination_date, wire, at);
  at = decode_trade_information(&record->trade_information, wire, at);
  record->change_indicator = wire[at++];

  return at;
}

/* what was read of Trade Report Message is what was written, byte for byte */
static void equal_trade_report_message(const TradeReportMessage *read, const TradeReportMessage *written) {
  equal_message_header(&read->message_header, &written->message_header);
  equal_label(&read->label, &written->label);
  equal_original_dissemination_date(&read->original_dissemination_date, &written->original_dissemination_date);
  equal_trade_information(&read->trade_information, &written->trade_information);
  assert(read->change_indicator == written->change_indicator);
}

/* Trade Report Message: written and read back, then read and written back */
static void check_trade_report_message(void) {
  TradeReportMessage sent;
  TradeReportMessage got;
  uint8_t wire[142];
  uint8_t again[142];

  any_trade_report_message(&sent);
  assert(encode_trade_report_message(&sent, wire, 0) == 142);
  assert(decode_trade_report_message(&got, wire, 0) == 142);
  equal_trade_report_message(&got, &sent);

  for (size_t i = 0; i < 142; i++) { wire[i] = arbitrary(); }
  assert(decode_trade_report_message(&got, wire, 0) == 142);
  assert(encode_trade_report_message(&got, again, 0) == 142);
  for (size_t i = 0; i < 142; i++) { assert(again[i] == wire[i]); }
}

/* ---- Original Trade Information: 71 bytes ------------------------------------ */

/* Original Trade Information */
typedef struct {
  uint8_t quantity_indicator;            /* byte 0 */
  uint8_t quantity[14];                  /* bytes 1 to 14 */
  uint8_t price[11];                     /* bytes 15 to 25 */
  uint8_t remuneration;                  /* byte 26 */
  uint8_t special_price_indicator;       /* byte 27 */
  uint8_t side;                          /* byte 28 */
  uint8_t as_of_indicator;               /* byte 29 */
  ExecutionDatetime execution_datetime;  /* bytes 30 to 43 */
  uint8_t future_use[2];                 /* bytes 44 to 45 */
  uint8_t sale_condition_3;              /* byte 46 */
  uint8_t sale_condition_4;              /* byte 47 */
  SettlementDate settlement_date;        /* bytes 48 to 55 */
  uint8_t factor[12];                    /* bytes 56 to 67 */
  uint8_t reporting_party_type;          /* byte 68 */
  uint8_t contra_party_type;             /* byte 69 */
  uint8_t ats_indicator;                 /* byte 70 */
} OriginalTradeInformation;

/* any Original Trade Information at all: every byte one the checker chooses */
static void any_original_trade_information(OriginalTradeInformation *record) {
  record->quantity_indicator = arbitrary();
  for (size_t i = 0; i < 14; i++) { record->quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->price[i] = arbitrary(); }
  record->remuneration = arbitrary();
  record->special_price_indicator = arbitrary();
  record->side = arbitrary();
  record->as_of_indicator = arbitrary();
  any_execution_datetime(&record->execution_datetime);
  for (size_t i = 0; i < 2; i++) { record->future_use[i] = arbitrary(); }
  record->sale_condition_3 = arbitrary();
  record->sale_condition_4 = arbitrary();
  any_settlement_date(&record->settlement_date);
  for (size_t i = 0; i < 12; i++) { record->factor[i] = arbitrary(); }
  record->reporting_party_type = arbitrary();
  record->contra_party_type = arbitrary();
  record->ats_indicator = arbitrary();
}

/* Original Trade Information to the wire: 71 bytes from at, returning where the next byte goes */
static size_t encode_original_trade_information(const OriginalTradeInformation *record, uint8_t *wire, size_t at) {
  wire[at++] = record->quantity_indicator;
  for (size_t i = 0; i < 14; i++) { wire[at++] = record->quantity[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->price[i]; }
  wire[at++] = record->remuneration;
  wire[at++] = record->special_price_indicator;
  wire[at++] = record->side;
  wire[at++] = record->as_of_indicator;
  at = encode_execution_datetime(&record->execution_datetime, wire, at);
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->future_use[i]; }
  wire[at++] = record->sale_condition_3;
  wire[at++] = record->sale_condition_4;
  at = encode_settlement_date(&record->settlement_date, wire, at);
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->factor[i]; }
  wire[at++] = record->reporting_party_type;
  wire[at++] = record->contra_party_type;
  wire[at++] = record->ats_indicator;

  return at;
}

/* Original Trade Information off the wire: 71 bytes from at, returning where the next byte lies */
static size_t decode_original_trade_information(OriginalTradeInformation *record, const uint8_t *wire, size_t at) {
  record->quantity_indicator = wire[at++];
  for (size_t i = 0; i < 14; i++) { record->quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->price[i] = wire[at++]; }
  record->remuneration = wire[at++];
  record->special_price_indicator = wire[at++];
  record->side = wire[at++];
  record->as_of_indicator = wire[at++];
  at = decode_execution_datetime(&record->execution_datetime, wire, at);
  for (size_t i = 0; i < 2; i++) { record->future_use[i] = wire[at++]; }
  record->sale_condition_3 = wire[at++];
  record->sale_condition_4 = wire[at++];
  at = decode_settlement_date(&record->settlement_date, wire, at);
  for (size_t i = 0; i < 12; i++) { record->factor[i] = wire[at++]; }
  record->reporting_party_type = wire[at++];
  record->contra_party_type = wire[at++];
  record->ats_indicator = wire[at++];

  return at;
}

/* what was read of Original Trade Information is what was written, byte for byte */
static void equal_original_trade_information(const OriginalTradeInformation *read, const OriginalTradeInformation *written) {
  assert(read->quantity_indicator == written->quantity_indicator);
  for (size_t i = 0; i < 14; i++) { assert(read->quantity[i] == written->quantity[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->price[i] == written->price[i]); }
  assert(read->remuneration == written->remuneration);
  assert(read->special_price_indicator == written->special_price_indicator);
  assert(read->side == written->side);
  assert(read->as_of_indicator == written->as_of_indicator);
  equal_execution_datetime(&read->execution_datetime, &written->execution_datetime);
  for (size_t i = 0; i < 2; i++) { assert(read->future_use[i] == written->future_use[i]); }
  assert(read->sale_condition_3 == written->sale_condition_3);
  assert(read->sale_condition_4 == written->sale_condition_4);
  equal_settlement_date(&read->settlement_date, &written->settlement_date);
  for (size_t i = 0; i < 12; i++) { assert(read->factor[i] == written->factor[i]); }
  assert(read->reporting_party_type == written->reporting_party_type);
  assert(read->contra_party_type == written->contra_party_type);
  assert(read->ats_indicator == written->ats_indicator);
}

/* Original Trade Information: written and read back, then read and written back */
static void check_original_trade_information(void) {
  OriginalTradeInformation sent;
  OriginalTradeInformation got;
  uint8_t wire[71];
  uint8_t again[71];

  any_original_trade_information(&sent);
  assert(encode_original_trade_information(&sent, wire, 0) == 71);
  assert(decode_original_trade_information(&got, wire, 0) == 71);
  equal_original_trade_information(&got, &sent);

  for (size_t i = 0; i < 71; i++) { wire[i] = arbitrary(); }
  assert(decode_original_trade_information(&got, wire, 0) == 71);
  assert(encode_original_trade_information(&got, again, 0) == 71);
  for (size_t i = 0; i < 71; i++) { assert(again[i] == wire[i]); }
}

/* ---- Trade Summary Information: 34 bytes ------------------------------------- */

/* Trade Summary Information */
typedef struct {
  uint8_t high_price[11];       /* bytes 0 to 10 */
  uint8_t low_price[11];        /* bytes 11 to 21 */
  uint8_t last_sale_price[11];  /* bytes 22 to 32 */
  uint8_t change_indicator;     /* byte 33 */
} TradeSummaryInformation;

/* any Trade Summary Information at all: every byte one the checker chooses */
static void any_trade_summary_information(TradeSummaryInformation *record) {
  for (size_t i = 0; i < 11; i++) { record->high_price[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->low_price[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->last_sale_price[i] = arbitrary(); }
  record->change_indicator = arbitrary();
}

/* Trade Summary Information to the wire: 34 bytes from at, returning where the next byte goes */
static size_t encode_trade_summary_information(const TradeSummaryInformation *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->high_price[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->low_price[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->last_sale_price[i]; }
  wire[at++] = record->change_indicator;

  return at;
}

/* Trade Summary Information off the wire: 34 bytes from at, returning where the next byte lies */
static size_t decode_trade_summary_information(TradeSummaryInformation *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 11; i++) { record->high_price[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->low_price[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->last_sale_price[i] = wire[at++]; }
  record->change_indicator = wire[at++];

  return at;
}

/* what was read of Trade Summary Information is what was written, byte for byte */
static void equal_trade_summary_information(const TradeSummaryInformation *read, const TradeSummaryInformation *written) {
  for (size_t i = 0; i < 11; i++) { assert(read->high_price[i] == written->high_price[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->low_price[i] == written->low_price[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->last_sale_price[i] == written->last_sale_price[i]); }
  assert(read->change_indicator == written->change_indicator);
}

/* Trade Summary Information: written and read back, then read and written back */
static void check_trade_summary_information(void) {
  TradeSummaryInformation sent;
  TradeSummaryInformation got;
  uint8_t wire[34];
  uint8_t again[34];

  any_trade_summary_information(&sent);
  assert(encode_trade_summary_information(&sent, wire, 0) == 34);
  assert(decode_trade_summary_information(&got, wire, 0) == 34);
  equal_trade_summary_information(&got, &sent);

  for (size_t i = 0; i < 34; i++) { wire[i] = arbitrary(); }
  assert(decode_trade_summary_information(&got, wire, 0) == 34);
  assert(encode_trade_summary_information(&got, again, 0) == 34);
  for (size_t i = 0; i < 34; i++) { assert(again[i] == wire[i]); }
}

/* ---- Trade Cancel Message: 183 bytes ----------------------------------------- */

/* Notifies subscribers that a trade report entered during the past 20 business days has been cancelled */
typedef struct {
  MessageHeader message_header;                           /* bytes 0 to 21 */
  Label label;                                            /* bytes 22 to 61 */
  OriginalDisseminationDate original_dissemination_date;  /* bytes 62 to 69 */
  uint8_t original_trade_identifier[7];                   /* bytes 70 to 76 */
  uint8_t report_function;                                /* byte 77 */
  OriginalTradeInformation original_trade_information;    /* bytes 78 to 148 */
  TradeSummaryInformation trade_summary_information;      /* bytes 149 to 182 */
} TradeCancelMessage;

/* any Trade Cancel Message at all: every byte one the checker chooses */
static void any_trade_cancel_message(TradeCancelMessage *record) {
  any_message_header(&record->message_header);
  any_label(&record->label);
  any_original_dissemination_date(&record->original_dissemination_date);
  for (size_t i = 0; i < 7; i++) { record->original_trade_identifier[i] = arbitrary(); }
  record->report_function = arbitrary();
  any_original_trade_information(&record->original_trade_information);
  any_trade_summary_information(&record->trade_summary_information);
}

/* Trade Cancel Message to the wire: 183 bytes from at, returning where the next byte goes */
static size_t encode_trade_cancel_message(const TradeCancelMessage *record, uint8_t *wire, size_t at) {
  at = encode_message_header(&record->message_header, wire, at);
  at = encode_label(&record->label, wire, at);
  at = encode_original_dissemination_date(&record->original_dissemination_date, wire, at);
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->original_trade_identifier[i]; }
  wire[at++] = record->report_function;
  at = encode_original_trade_information(&record->original_trade_information, wire, at);
  at = encode_trade_summary_information(&record->trade_summary_information, wire, at);

  return at;
}

/* Trade Cancel Message off the wire: 183 bytes from at, returning where the next byte lies */
static size_t decode_trade_cancel_message(TradeCancelMessage *record, const uint8_t *wire, size_t at) {
  at = decode_message_header(&record->message_header, wire, at);
  at = decode_label(&record->label, wire, at);
  at = decode_original_dissemination_date(&record->original_dissemination_date, wire, at);
  for (size_t i = 0; i < 7; i++) { record->original_trade_identifier[i] = wire[at++]; }
  record->report_function = wire[at++];
  at = decode_original_trade_information(&record->original_trade_information, wire, at);
  at = decode_trade_summary_information(&record->trade_summary_information, wire, at);

  return at;
}

/* what was read of Trade Cancel Message is what was written, byte for byte */
static void equal_trade_cancel_message(const TradeCancelMessage *read, const TradeCancelMessage *written) {
  equal_message_header(&read->message_header, &written->message_header);
  equal_label(&read->label, &written->label);
  equal_original_dissemination_date(&read->original_dissemination_date, &written->original_dissemination_date);
  for (size_t i = 0; i < 7; i++) { assert(read->original_trade_identifier[i] == written->original_trade_identifier[i]); }
  assert(read->report_function == written->report_function);
  equal_original_trade_information(&read->original_trade_information, &written->original_trade_information);
  equal_trade_summary_information(&read->trade_summary_information, &written->trade_summary_information);
}

/* Trade Cancel Message: written and read back, then read and written back */
static void check_trade_cancel_message(void) {
  TradeCancelMessage sent;
  TradeCancelMessage got;
  uint8_t wire[183];
  uint8_t again[183];

  any_trade_cancel_message(&sent);
  assert(encode_trade_cancel_message(&sent, wire, 0) == 183);
  assert(decode_trade_cancel_message(&got, wire, 0) == 183);
  equal_trade_cancel_message(&got, &sent);

  for (size_t i = 0; i < 183; i++) { wire[i] = arbitrary(); }
  assert(decode_trade_cancel_message(&got, wire, 0) == 183);
  assert(encode_trade_cancel_message(&got, again, 0) == 183);
  for (size_t i = 0; i < 183; i++) { assert(again[i] == wire[i]); }
}

/* ---- Correction Trade Information: 71 bytes ---------------------------------- */

/* Correction Trade Information */
typedef struct {
  uint8_t quantity_indicator;            /* byte 0 */
  uint8_t quantity[14];                  /* bytes 1 to 14 */
  uint8_t price[11];                     /* bytes 15 to 25 */
  uint8_t remuneration;                  /* byte 26 */
  uint8_t special_price_indicator;       /* byte 27 */
  uint8_t side;                          /* byte 28 */
  uint8_t as_of_indicator;               /* byte 29 */
  ExecutionDatetime execution_datetime;  /* bytes 30 to 43 */
  uint8_t future_use[2];                 /* bytes 44 to 45 */
  uint8_t sale_condition_3;              /* byte 46 */
  uint8_t sale_condition_4;              /* byte 47 */
  SettlementDate settlement_date;        /* bytes 48 to 55 */
  uint8_t factor[12];                    /* bytes 56 to 67 */
  uint8_t reporting_party_type;          /* byte 68 */
  uint8_t contra_party_type;             /* byte 69 */
  uint8_t ats_indicator;                 /* byte 70 */
} CorrectionTradeInformation;

/* any Correction Trade Information at all: every byte one the checker chooses */
static void any_correction_trade_information(CorrectionTradeInformation *record) {
  record->quantity_indicator = arbitrary();
  for (size_t i = 0; i < 14; i++) { record->quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->price[i] = arbitrary(); }
  record->remuneration = arbitrary();
  record->special_price_indicator = arbitrary();
  record->side = arbitrary();
  record->as_of_indicator = arbitrary();
  any_execution_datetime(&record->execution_datetime);
  for (size_t i = 0; i < 2; i++) { record->future_use[i] = arbitrary(); }
  record->sale_condition_3 = arbitrary();
  record->sale_condition_4 = arbitrary();
  any_settlement_date(&record->settlement_date);
  for (size_t i = 0; i < 12; i++) { record->factor[i] = arbitrary(); }
  record->reporting_party_type = arbitrary();
  record->contra_party_type = arbitrary();
  record->ats_indicator = arbitrary();
}

/* Correction Trade Information to the wire: 71 bytes from at, returning where the next byte goes */
static size_t encode_correction_trade_information(const CorrectionTradeInformation *record, uint8_t *wire, size_t at) {
  wire[at++] = record->quantity_indicator;
  for (size_t i = 0; i < 14; i++) { wire[at++] = record->quantity[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->price[i]; }
  wire[at++] = record->remuneration;
  wire[at++] = record->special_price_indicator;
  wire[at++] = record->side;
  wire[at++] = record->as_of_indicator;
  at = encode_execution_datetime(&record->execution_datetime, wire, at);
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->future_use[i]; }
  wire[at++] = record->sale_condition_3;
  wire[at++] = record->sale_condition_4;
  at = encode_settlement_date(&record->settlement_date, wire, at);
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->factor[i]; }
  wire[at++] = record->reporting_party_type;
  wire[at++] = record->contra_party_type;
  wire[at++] = record->ats_indicator;

  return at;
}

/* Correction Trade Information off the wire: 71 bytes from at, returning where the next byte lies */
static size_t decode_correction_trade_information(CorrectionTradeInformation *record, const uint8_t *wire, size_t at) {
  record->quantity_indicator = wire[at++];
  for (size_t i = 0; i < 14; i++) { record->quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->price[i] = wire[at++]; }
  record->remuneration = wire[at++];
  record->special_price_indicator = wire[at++];
  record->side = wire[at++];
  record->as_of_indicator = wire[at++];
  at = decode_execution_datetime(&record->execution_datetime, wire, at);
  for (size_t i = 0; i < 2; i++) { record->future_use[i] = wire[at++]; }
  record->sale_condition_3 = wire[at++];
  record->sale_condition_4 = wire[at++];
  at = decode_settlement_date(&record->settlement_date, wire, at);
  for (size_t i = 0; i < 12; i++) { record->factor[i] = wire[at++]; }
  record->reporting_party_type = wire[at++];
  record->contra_party_type = wire[at++];
  record->ats_indicator = wire[at++];

  return at;
}

/* what was read of Correction Trade Information is what was written, byte for byte */
static void equal_correction_trade_information(const CorrectionTradeInformation *read, const CorrectionTradeInformation *written) {
  assert(read->quantity_indicator == written->quantity_indicator);
  for (size_t i = 0; i < 14; i++) { assert(read->quantity[i] == written->quantity[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->price[i] == written->price[i]); }
  assert(read->remuneration == written->remuneration);
  assert(read->special_price_indicator == written->special_price_indicator);
  assert(read->side == written->side);
  assert(read->as_of_indicator == written->as_of_indicator);
  equal_execution_datetime(&read->execution_datetime, &written->execution_datetime);
  for (size_t i = 0; i < 2; i++) { assert(read->future_use[i] == written->future_use[i]); }
  assert(read->sale_condition_3 == written->sale_condition_3);
  assert(read->sale_condition_4 == written->sale_condition_4);
  equal_settlement_date(&read->settlement_date, &written->settlement_date);
  for (size_t i = 0; i < 12; i++) { assert(read->factor[i] == written->factor[i]); }
  assert(read->reporting_party_type == written->reporting_party_type);
  assert(read->contra_party_type == written->contra_party_type);
  assert(read->ats_indicator == written->ats_indicator);
}

/* Correction Trade Information: written and read back, then read and written back */
static void check_correction_trade_information(void) {
  CorrectionTradeInformation sent;
  CorrectionTradeInformation got;
  uint8_t wire[71];
  uint8_t again[71];

  any_correction_trade_information(&sent);
  assert(encode_correction_trade_information(&sent, wire, 0) == 71);
  assert(decode_correction_trade_information(&got, wire, 0) == 71);
  equal_correction_trade_information(&got, &sent);

  for (size_t i = 0; i < 71; i++) { wire[i] = arbitrary(); }
  assert(decode_correction_trade_information(&got, wire, 0) == 71);
  assert(encode_correction_trade_information(&got, again, 0) == 71);
  for (size_t i = 0; i < 71; i++) { assert(again[i] == wire[i]); }
}

/* ---- Trade Correction Message: 254 bytes ------------------------------------- */

/* Notifies subscribers that a trade report entered during the past 20 business days has been corrected */
typedef struct {
  MessageHeader message_header;                             /* bytes 0 to 21 */
  Label label;                                              /* bytes 22 to 61 */
  OriginalDisseminationDate original_dissemination_date;    /* bytes 62 to 69 */
  uint8_t original_trade_identifier[7];                     /* bytes 70 to 76 */
  uint8_t report_function;                                  /* byte 77 */
  OriginalTradeInformation original_trade_information;      /* bytes 78 to 148 */
  CorrectionTradeInformation correction_trade_information;  /* bytes 149 to 219 */
  TradeSummaryInformation trade_summary_information;        /* bytes 220 to 253 */
} TradeCorrectionMessage;

/* any Trade Correction Message at all: every byte one the checker chooses */
static void any_trade_correction_message(TradeCorrectionMessage *record) {
  any_message_header(&record->message_header);
  any_label(&record->label);
  any_original_dissemination_date(&record->original_dissemination_date);
  for (size_t i = 0; i < 7; i++) { record->original_trade_identifier[i] = arbitrary(); }
  record->report_function = arbitrary();
  any_original_trade_information(&record->original_trade_information);
  any_correction_trade_information(&record->correction_trade_information);
  any_trade_summary_information(&record->trade_summary_information);
}

/* Trade Correction Message to the wire: 254 bytes from at, returning where the next byte goes */
static size_t encode_trade_correction_message(const TradeCorrectionMessage *record, uint8_t *wire, size_t at) {
  at = encode_message_header(&record->message_header, wire, at);
  at = encode_label(&record->label, wire, at);
  at = encode_original_dissemination_date(&record->original_dissemination_date, wire, at);
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->original_trade_identifier[i]; }
  wire[at++] = record->report_function;
  at = encode_original_trade_information(&record->original_trade_information, wire, at);
  at = encode_correction_trade_information(&record->correction_trade_information, wire, at);
  at = encode_trade_summary_information(&record->trade_summary_information, wire, at);

  return at;
}

/* Trade Correction Message off the wire: 254 bytes from at, returning where the next byte lies */
static size_t decode_trade_correction_message(TradeCorrectionMessage *record, const uint8_t *wire, size_t at) {
  at = decode_message_header(&record->message_header, wire, at);
  at = decode_label(&record->label, wire, at);
  at = decode_original_dissemination_date(&record->original_dissemination_date, wire, at);
  for (size_t i = 0; i < 7; i++) { record->original_trade_identifier[i] = wire[at++]; }
  record->report_function = wire[at++];
  at = decode_original_trade_information(&record->original_trade_information, wire, at);
  at = decode_correction_trade_information(&record->correction_trade_information, wire, at);
  at = decode_trade_summary_information(&record->trade_summary_information, wire, at);

  return at;
}

/* what was read of Trade Correction Message is what was written, byte for byte */
static void equal_trade_correction_message(const TradeCorrectionMessage *read, const TradeCorrectionMessage *written) {
  equal_message_header(&read->message_header, &written->message_header);
  equal_label(&read->label, &written->label);
  equal_original_dissemination_date(&read->original_dissemination_date, &written->original_dissemination_date);
  for (size_t i = 0; i < 7; i++) { assert(read->original_trade_identifier[i] == written->original_trade_identifier[i]); }
  assert(read->report_function == written->report_function);
  equal_original_trade_information(&read->original_trade_information, &written->original_trade_information);
  equal_correction_trade_information(&read->correction_trade_information, &written->correction_trade_information);
  equal_trade_summary_information(&read->trade_summary_information, &written->trade_summary_information);
}

/* Trade Correction Message: written and read back, then read and written back */
static void check_trade_correction_message(void) {
  TradeCorrectionMessage sent;
  TradeCorrectionMessage got;
  uint8_t wire[254];
  uint8_t again[254];

  any_trade_correction_message(&sent);
  assert(encode_trade_correction_message(&sent, wire, 0) == 254);
  assert(decode_trade_correction_message(&got, wire, 0) == 254);
  equal_trade_correction_message(&got, &sent);

  for (size_t i = 0; i < 254; i++) { wire[i] = arbitrary(); }
  assert(decode_trade_correction_message(&got, wire, 0) == 254);
  assert(encode_trade_correction_message(&got, again, 0) == 254);
  for (size_t i = 0; i < 254; i++) { assert(again[i] == wire[i]); }
}

/* ---- Daily Trade Summary Message: 95 bytes ----------------------------------- */

/* Price summary disseminated for each security that traded during the normal trading hours */
typedef struct {
  MessageHeader message_header;   /* bytes 0 to 21 */
  Label label;                    /* bytes 22 to 61 */
  uint8_t daily_high_price[11];   /* bytes 62 to 72 */
  uint8_t daily_low_price[11];    /* bytes 73 to 83 */
  uint8_t daily_close_price[11];  /* bytes 84 to 94 */
} DailyTradeSummaryMessage;

/* any Daily Trade Summary Message at all: every byte one the checker chooses */
static void any_daily_trade_summary_message(DailyTradeSummaryMessage *record) {
  any_message_header(&record->message_header);
  any_label(&record->label);
  for (size_t i = 0; i < 11; i++) { record->daily_high_price[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->daily_low_price[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->daily_close_price[i] = arbitrary(); }
}

/* Daily Trade Summary Message to the wire: 95 bytes from at, returning where the next byte goes */
static size_t encode_daily_trade_summary_message(const DailyTradeSummaryMessage *record, uint8_t *wire, size_t at) {
  at = encode_message_header(&record->message_header, wire, at);
  at = encode_label(&record->label, wire, at);
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->daily_high_price[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->daily_low_price[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->daily_close_price[i]; }

  return at;
}

/* Daily Trade Summary Message off the wire: 95 bytes from at, returning where the next byte lies */
static size_t decode_daily_trade_summary_message(DailyTradeSummaryMessage *record, const uint8_t *wire, size_t at) {
  at = decode_message_header(&record->message_header, wire, at);
  at = decode_label(&record->label, wire, at);
  for (size_t i = 0; i < 11; i++) { record->daily_high_price[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->daily_low_price[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->daily_close_price[i] = wire[at++]; }

  return at;
}

/* what was read of Daily Trade Summary Message is what was written, byte for byte */
static void equal_daily_trade_summary_message(const DailyTradeSummaryMessage *read, const DailyTradeSummaryMessage *written) {
  equal_message_header(&read->message_header, &written->message_header);
  equal_label(&read->label, &written->label);
  for (size_t i = 0; i < 11; i++) { assert(read->daily_high_price[i] == written->daily_high_price[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->daily_low_price[i] == written->daily_low_price[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->daily_close_price[i] == written->daily_close_price[i]); }
}

/* Daily Trade Summary Message: written and read back, then read and written back */
static void check_daily_trade_summary_message(void) {
  DailyTradeSummaryMessage sent;
  DailyTradeSummaryMessage got;
  uint8_t wire[95];
  uint8_t again[95];

  any_daily_trade_summary_message(&sent);
  assert(encode_daily_trade_summary_message(&sent, wire, 0) == 95);
  assert(decode_daily_trade_summary_message(&got, wire, 0) == 95);
  equal_daily_trade_summary_message(&got, &sent);

  for (size_t i = 0; i < 95; i++) { wire[i] = arbitrary(); }
  assert(decode_daily_trade_summary_message(&got, wire, 0) == 95);
  assert(encode_daily_trade_summary_message(&got, again, 0) == 95);
  for (size_t i = 0; i < 95; i++) { assert(again[i] == wire[i]); }
}

/* ---- Action Datetime: 14 bytes ----------------------------------------------- */

/* Action Datetime */
typedef struct {
  uint8_t year[4];    /* bytes 0 to 3 */
  uint8_t month[2];   /* bytes 4 to 5 */
  uint8_t day[2];     /* bytes 6 to 7 */
  uint8_t hour[2];    /* bytes 8 to 9 */
  uint8_t minute[2];  /* bytes 10 to 11 */
  uint8_t second[2];  /* bytes 12 to 13 */
} ActionDatetime;

/* any Action Datetime at all: every byte one the checker chooses */
static void any_action_datetime(ActionDatetime *record) {
  for (size_t i = 0; i < 4; i++) { record->year[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->month[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->day[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->hour[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->minute[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->second[i] = arbitrary(); }
}

/* Action Datetime to the wire: 14 bytes from at, returning where the next byte goes */
static size_t encode_action_datetime(const ActionDatetime *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->year[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->month[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->day[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->hour[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->minute[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->second[i]; }

  return at;
}

/* Action Datetime off the wire: 14 bytes from at, returning where the next byte lies */
static size_t decode_action_datetime(ActionDatetime *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->year[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->month[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->day[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->hour[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->minute[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->second[i] = wire[at++]; }

  return at;
}

/* what was read of Action Datetime is what was written, byte for byte */
static void equal_action_datetime(const ActionDatetime *read, const ActionDatetime *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->year[i] == written->year[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->month[i] == written->month[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->day[i] == written->day[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->hour[i] == written->hour[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->minute[i] == written->minute[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->second[i] == written->second[i]); }
}

/* Action Datetime: written and read back, then read and written back */
static void check_action_datetime(void) {
  ActionDatetime sent;
  ActionDatetime got;
  uint8_t wire[14];
  uint8_t again[14];

  any_action_datetime(&sent);
  assert(encode_action_datetime(&sent, wire, 0) == 14);
  assert(decode_action_datetime(&got, wire, 0) == 14);
  equal_action_datetime(&got, &sent);

  for (size_t i = 0; i < 14; i++) { wire[i] = arbitrary(); }
  assert(decode_action_datetime(&got, wire, 0) == 14);
  assert(encode_action_datetime(&got, again, 0) == 14);
  for (size_t i = 0; i < 14; i++) { assert(again[i] == wire[i]); }
}

/* ---- Trading Halt Message: 111 bytes ----------------------------------------- */

/* Disseminated when a trading halt is instituted or removed for a security */
typedef struct {
  MessageHeader message_header;    /* bytes 0 to 21 */
  Label label;                     /* bytes 22 to 61 */
  uint8_t issuer[30];              /* bytes 62 to 91 */
  uint8_t action;                  /* byte 92 */
  ActionDatetime action_datetime;  /* bytes 93 to 106 */
  uint8_t halt_reason[4];          /* bytes 107 to 110 */
} TradingHaltMessage;

/* any Trading Halt Message at all: every byte one the checker chooses */
static void any_trading_halt_message(TradingHaltMessage *record) {
  any_message_header(&record->message_header);
  any_label(&record->label);
  for (size_t i = 0; i < 30; i++) { record->issuer[i] = arbitrary(); }
  record->action = arbitrary();
  any_action_datetime(&record->action_datetime);
  for (size_t i = 0; i < 4; i++) { record->halt_reason[i] = arbitrary(); }
}

/* Trading Halt Message to the wire: 111 bytes from at, returning where the next byte goes */
static size_t encode_trading_halt_message(const TradingHaltMessage *record, uint8_t *wire, size_t at) {
  at = encode_message_header(&record->message_header, wire, at);
  at = encode_label(&record->label, wire, at);
  for (size_t i = 0; i < 30; i++) { wire[at++] = record->issuer[i]; }
  wire[at++] = record->action;
  at = encode_action_datetime(&record->action_datetime, wire, at);
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->halt_reason[i]; }

  return at;
}

/* Trading Halt Message off the wire: 111 bytes from at, returning where the next byte lies */
static size_t decode_trading_halt_message(TradingHaltMessage *record, const uint8_t *wire, size_t at) {
  at = decode_message_header(&record->message_header, wire, at);
  at = decode_label(&record->label, wire, at);
  for (size_t i = 0; i < 30; i++) { record->issuer[i] = wire[at++]; }
  record->action = wire[at++];
  at = decode_action_datetime(&record->action_datetime, wire, at);
  for (size_t i = 0; i < 4; i++) { record->halt_reason[i] = wire[at++]; }

  return at;
}

/* what was read of Trading Halt Message is what was written, byte for byte */
static void equal_trading_halt_message(const TradingHaltMessage *read, const TradingHaltMessage *written) {
  equal_message_header(&read->message_header, &written->message_header);
  equal_label(&read->label, &written->label);
  for (size_t i = 0; i < 30; i++) { assert(read->issuer[i] == written->issuer[i]); }
  assert(read->action == written->action);
  equal_action_datetime(&read->action_datetime, &written->action_datetime);
  for (size_t i = 0; i < 4; i++) { assert(read->halt_reason[i] == written->halt_reason[i]); }
}

/* Trading Halt Message: written and read back, then read and written back */
static void check_trading_halt_message(void) {
  TradingHaltMessage sent;
  TradingHaltMessage got;
  uint8_t wire[111];
  uint8_t again[111];

  any_trading_halt_message(&sent);
  assert(encode_trading_halt_message(&sent, wire, 0) == 111);
  assert(decode_trading_halt_message(&got, wire, 0) == 111);
  equal_trading_halt_message(&got, &sent);

  for (size_t i = 0; i < 111; i++) { wire[i] = arbitrary(); }
  assert(decode_trading_halt_message(&got, wire, 0) == 111);
  assert(encode_trading_halt_message(&got, again, 0) == 111);
  for (size_t i = 0; i < 111; i++) { assert(again[i] == wire[i]); }
}

/* ---- Start Of Day Message: 22 bytes ------------------------------------------ */

/* Signifies the beginning of Finra's daily operational cycle */
typedef struct {
  MessageHeader message_header;  /* bytes 0 to 21 */
} StartOfDayMessage;

/* any Start Of Day Message at all: every byte one the checker chooses */
static void any_start_of_day_message(StartOfDayMessage *record) {
  any_message_header(&record->message_header);
}

/* Start Of Day Message to the wire: 22 bytes from at, returning where the next byte goes */
static size_t encode_start_of_day_message(const StartOfDayMessage *record, uint8_t *wire, size_t at) {
  at = encode_message_header(&record->message_header, wire, at);

  return at;
}

/* Start Of Day Message off the wire: 22 bytes from at, returning where the next byte lies */
static size_t decode_start_of_day_message(StartOfDayMessage *record, const uint8_t *wire, size_t at) {
  at = decode_message_header(&record->message_header, wire, at);

  return at;
}

/* what was read of Start Of Day Message is what was written, byte for byte */
static void equal_start_of_day_message(const StartOfDayMessage *read, const StartOfDayMessage *written) {
  equal_message_header(&read->message_header, &written->message_header);
}

/* Start Of Day Message: written and read back, then read and written back */
static void check_start_of_day_message(void) {
  StartOfDayMessage sent;
  StartOfDayMessage got;
  uint8_t wire[22];
  uint8_t again[22];

  any_start_of_day_message(&sent);
  assert(encode_start_of_day_message(&sent, wire, 0) == 22);
  assert(decode_start_of_day_message(&got, wire, 0) == 22);
  equal_start_of_day_message(&got, &sent);

  for (size_t i = 0; i < 22; i++) { wire[i] = arbitrary(); }
  assert(decode_start_of_day_message(&got, wire, 0) == 22);
  assert(encode_start_of_day_message(&got, again, 0) == 22);
  for (size_t i = 0; i < 22; i++) { assert(again[i] == wire[i]); }
}

/* ---- End Of Day Message: 22 bytes -------------------------------------------- */

/* Signals the end of activity for the operational cycle */
typedef struct {
  MessageHeader message_header;  /* bytes 0 to 21 */
} EndOfDayMessage;

/* any End Of Day Message at all: every byte one the checker chooses */
static void any_end_of_day_message(EndOfDayMessage *record) {
  any_message_header(&record->message_header);
}

/* End Of Day Message to the wire: 22 bytes from at, returning where the next byte goes */
static size_t encode_end_of_day_message(const EndOfDayMessage *record, uint8_t *wire, size_t at) {
  at = encode_message_header(&record->message_header, wire, at);

  return at;
}

/* End Of Day Message off the wire: 22 bytes from at, returning where the next byte lies */
static size_t decode_end_of_day_message(EndOfDayMessage *record, const uint8_t *wire, size_t at) {
  at = decode_message_header(&record->message_header, wire, at);

  return at;
}

/* what was read of End Of Day Message is what was written, byte for byte */
static void equal_end_of_day_message(const EndOfDayMessage *read, const EndOfDayMessage *written) {
  equal_message_header(&read->message_header, &written->message_header);
}

/* End Of Day Message: written and read back, then read and written back */
static void check_end_of_day_message(void) {
  EndOfDayMessage sent;
  EndOfDayMessage got;
  uint8_t wire[22];
  uint8_t again[22];

  any_end_of_day_message(&sent);
  assert(encode_end_of_day_message(&sent, wire, 0) == 22);
  assert(decode_end_of_day_message(&got, wire, 0) == 22);
  equal_end_of_day_message(&got, &sent);

  for (size_t i = 0; i < 22; i++) { wire[i] = arbitrary(); }
  assert(decode_end_of_day_message(&got, wire, 0) == 22);
  assert(encode_end_of_day_message(&got, again, 0) == 22);
  for (size_t i = 0; i < 22; i++) { assert(again[i] == wire[i]); }
}

/* ---- Market Session Open Message: 22 bytes ----------------------------------- */

/* Signifies the opening of the market for the session indicated in the message header */
typedef struct {
  MessageHeader message_header;  /* bytes 0 to 21 */
} MarketSessionOpenMessage;

/* any Market Session Open Message at all: every byte one the checker chooses */
static void any_market_session_open_message(MarketSessionOpenMessage *record) {
  any_message_header(&record->message_header);
}

/* Market Session Open Message to the wire: 22 bytes from at, returning where the next byte goes */
static size_t encode_market_session_open_message(const MarketSessionOpenMessage *record, uint8_t *wire, size_t at) {
  at = encode_message_header(&record->message_header, wire, at);

  return at;
}

/* Market Session Open Message off the wire: 22 bytes from at, returning where the next byte lies */
static size_t decode_market_session_open_message(MarketSessionOpenMessage *record, const uint8_t *wire, size_t at) {
  at = decode_message_header(&record->message_header, wire, at);

  return at;
}

/* what was read of Market Session Open Message is what was written, byte for byte */
static void equal_market_session_open_message(const MarketSessionOpenMessage *read, const MarketSessionOpenMessage *written) {
  equal_message_header(&read->message_header, &written->message_header);
}

/* Market Session Open Message: written and read back, then read and written back */
static void check_market_session_open_message(void) {
  MarketSessionOpenMessage sent;
  MarketSessionOpenMessage got;
  uint8_t wire[22];
  uint8_t again[22];

  any_market_session_open_message(&sent);
  assert(encode_market_session_open_message(&sent, wire, 0) == 22);
  assert(decode_market_session_open_message(&got, wire, 0) == 22);
  equal_market_session_open_message(&got, &sent);

  for (size_t i = 0; i < 22; i++) { wire[i] = arbitrary(); }
  assert(decode_market_session_open_message(&got, wire, 0) == 22);
  assert(encode_market_session_open_message(&got, again, 0) == 22);
  for (size_t i = 0; i < 22; i++) { assert(again[i] == wire[i]); }
}

/* ---- Market Session Close Message: 22 bytes ---------------------------------- */

/* Signals the closing of the market for the session indicated in the message header */
typedef struct {
  MessageHeader message_header;  /* bytes 0 to 21 */
} MarketSessionCloseMessage;

/* any Market Session Close Message at all: every byte one the checker chooses */
static void any_market_session_close_message(MarketSessionCloseMessage *record) {
  any_message_header(&record->message_header);
}

/* Market Session Close Message to the wire: 22 bytes from at, returning where the next byte goes */
static size_t encode_market_session_close_message(const MarketSessionCloseMessage *record, uint8_t *wire, size_t at) {
  at = encode_message_header(&record->message_header, wire, at);

  return at;
}

/* Market Session Close Message off the wire: 22 bytes from at, returning where the next byte lies */
static size_t decode_market_session_close_message(MarketSessionCloseMessage *record, const uint8_t *wire, size_t at) {
  at = decode_message_header(&record->message_header, wire, at);

  return at;
}

/* what was read of Market Session Close Message is what was written, byte for byte */
static void equal_market_session_close_message(const MarketSessionCloseMessage *read, const MarketSessionCloseMessage *written) {
  equal_message_header(&read->message_header, &written->message_header);
}

/* Market Session Close Message: written and read back, then read and written back */
static void check_market_session_close_message(void) {
  MarketSessionCloseMessage sent;
  MarketSessionCloseMessage got;
  uint8_t wire[22];
  uint8_t again[22];

  any_market_session_close_message(&sent);
  assert(encode_market_session_close_message(&sent, wire, 0) == 22);
  assert(decode_market_session_close_message(&got, wire, 0) == 22);
  equal_market_session_close_message(&got, &sent);

  for (size_t i = 0; i < 22; i++) { wire[i] = arbitrary(); }
  assert(decode_market_session_close_message(&got, wire, 0) == 22);
  assert(encode_market_session_close_message(&got, again, 0) == 22);
  for (size_t i = 0; i < 22; i++) { assert(again[i] == wire[i]); }
}

/* ---- End Of Trade Reporting Message: 22 bytes -------------------------------- */

/* Signals that no further trade reports or corrections will be sent for that market session */
typedef struct {
  MessageHeader message_header;  /* bytes 0 to 21 */
} EndOfTradeReportingMessage;

/* any End Of Trade Reporting Message at all: every byte one the checker chooses */
static void any_end_of_trade_reporting_message(EndOfTradeReportingMessage *record) {
  any_message_header(&record->message_header);
}

/* End Of Trade Reporting Message to the wire: 22 bytes from at, returning where the next byte goes */
static size_t encode_end_of_trade_reporting_message(const EndOfTradeReportingMessage *record, uint8_t *wire, size_t at) {
  at = encode_message_header(&record->message_header, wire, at);

  return at;
}

/* End Of Trade Reporting Message off the wire: 22 bytes from at, returning where the next byte lies */
static size_t decode_end_of_trade_reporting_message(EndOfTradeReportingMessage *record, const uint8_t *wire, size_t at) {
  at = decode_message_header(&record->message_header, wire, at);

  return at;
}

/* what was read of End Of Trade Reporting Message is what was written, byte for byte */
static void equal_end_of_trade_reporting_message(const EndOfTradeReportingMessage *read, const EndOfTradeReportingMessage *written) {
  equal_message_header(&read->message_header, &written->message_header);
}

/* End Of Trade Reporting Message: written and read back, then read and written back */
static void check_end_of_trade_reporting_message(void) {
  EndOfTradeReportingMessage sent;
  EndOfTradeReportingMessage got;
  uint8_t wire[22];
  uint8_t again[22];

  any_end_of_trade_reporting_message(&sent);
  assert(encode_end_of_trade_reporting_message(&sent, wire, 0) == 22);
  assert(decode_end_of_trade_reporting_message(&got, wire, 0) == 22);
  equal_end_of_trade_reporting_message(&got, &sent);

  for (size_t i = 0; i < 22; i++) { wire[i] = arbitrary(); }
  assert(decode_end_of_trade_reporting_message(&got, wire, 0) == 22);
  assert(encode_end_of_trade_reporting_message(&got, again, 0) == 22);
  for (size_t i = 0; i < 22; i++) { assert(again[i] == wire[i]); }
}

/* ---- End Of Transmissions Message: 22 bytes ---------------------------------- */

/* Signals that there will be no further transmissions of data */
typedef struct {
  MessageHeader message_header;  /* bytes 0 to 21 */
} EndOfTransmissionsMessage;

/* any End Of Transmissions Message at all: every byte one the checker chooses */
static void any_end_of_transmissions_message(EndOfTransmissionsMessage *record) {
  any_message_header(&record->message_header);
}

/* End Of Transmissions Message to the wire: 22 bytes from at, returning where the next byte goes */
static size_t encode_end_of_transmissions_message(const EndOfTransmissionsMessage *record, uint8_t *wire, size_t at) {
  at = encode_message_header(&record->message_header, wire, at);

  return at;
}

/* End Of Transmissions Message off the wire: 22 bytes from at, returning where the next byte lies */
static size_t decode_end_of_transmissions_message(EndOfTransmissionsMessage *record, const uint8_t *wire, size_t at) {
  at = decode_message_header(&record->message_header, wire, at);

  return at;
}

/* what was read of End Of Transmissions Message is what was written, byte for byte */
static void equal_end_of_transmissions_message(const EndOfTransmissionsMessage *read, const EndOfTransmissionsMessage *written) {
  equal_message_header(&read->message_header, &written->message_header);
}

/* End Of Transmissions Message: written and read back, then read and written back */
static void check_end_of_transmissions_message(void) {
  EndOfTransmissionsMessage sent;
  EndOfTransmissionsMessage got;
  uint8_t wire[22];
  uint8_t again[22];

  any_end_of_transmissions_message(&sent);
  assert(encode_end_of_transmissions_message(&sent, wire, 0) == 22);
  assert(decode_end_of_transmissions_message(&got, wire, 0) == 22);
  equal_end_of_transmissions_message(&got, &sent);

  for (size_t i = 0; i < 22; i++) { wire[i] = arbitrary(); }
  assert(decode_end_of_transmissions_message(&got, wire, 0) == 22);
  assert(encode_end_of_transmissions_message(&got, again, 0) == 22);
  for (size_t i = 0; i < 22; i++) { assert(again[i] == wire[i]); }
}

/* ---- What esbmc checks ------------------------------------------------------- */

/* every record of the protocol, each on its own buffers */
static void checks(void) {
  check_packet_header();
  check_mold_udp64();
  check_datetime();
  check_message_header();
  check_label();
  check_original_dissemination_date();
  check_execution_datetime();
  check_settlement_date();
  check_trade_information();
  check_trade_report_message();
  check_original_trade_information();
  check_trade_summary_information();
  check_trade_cancel_message();
  check_correction_trade_information();
  check_trade_correction_message();
  check_daily_trade_summary_message();
  check_action_datetime();
  check_trading_halt_message();
  check_start_of_day_message();
  check_end_of_day_message();
  check_market_session_open_message();
  check_market_session_close_message();
  check_end_of_trade_reporting_message();
  check_end_of_transmissions_message();
}

int main(void) {
#ifdef CONCRETE
  for (pattern = 0; pattern < 4; pattern++) { checks(); }
#else
  checks();
#endif

  return 0;
}
