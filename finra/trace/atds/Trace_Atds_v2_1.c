// finra/trace/atds/Trace_Atds_v2_1.c
/*
 * Financial Industry Regulatory Authority Agency Debt Trade Dissemination Service
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

/* ---- Trade Information: 74 bytes --------------------------------------------- */

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
  uint8_t yield_direction;               /* byte 56 */
  uint8_t yield[13];                     /* bytes 57 to 69 */
  uint8_t when_issued_indicator;         /* byte 70 */
  uint8_t reporting_party_type;          /* byte 71 */
  uint8_t contra_party_type;             /* byte 72 */
  uint8_t ats_indicator;                 /* byte 73 */
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
  record->yield_direction = arbitrary();
  for (size_t i = 0; i < 13; i++) { record->yield[i] = arbitrary(); }
  record->when_issued_indicator = arbitrary();
  record->reporting_party_type = arbitrary();
  record->contra_party_type = arbitrary();
  record->ats_indicator = arbitrary();
}

/* Trade Information to the wire: 74 bytes from at, returning where the next byte goes */
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
  wire[at++] = record->yield_direction;
  for (size_t i = 0; i < 13; i++) { wire[at++] = record->yield[i]; }
  wire[at++] = record->when_issued_indicator;
  wire[at++] = record->reporting_party_type;
  wire[at++] = record->contra_party_type;
  wire[at++] = record->ats_indicator;

  return at;
}

/* Trade Information off the wire: 74 bytes from at, returning where the next byte lies */
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
  record->yield_direction = wire[at++];
  for (size_t i = 0; i < 13; i++) { record->yield[i] = wire[at++]; }
  record->when_issued_indicator = wire[at++];
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
  assert(read->yield_direction == written->yield_direction);
  for (size_t i = 0; i < 13; i++) { assert(read->yield[i] == written->yield[i]); }
  assert(read->when_issued_indicator == written->when_issued_indicator);
  assert(read->reporting_party_type == written->reporting_party_type);
  assert(read->contra_party_type == written->contra_party_type);
  assert(read->ats_indicator == written->ats_indicator);
}

/* Trade Information: written and read back, then read and written back */
static void check_trade_information(void) {
  TradeInformation sent;
  TradeInformation got;
  uint8_t wire[74];
  uint8_t again[74];

  any_trade_information(&sent);
  assert(encode_trade_information(&sent, wire, 0) == 74);
  assert(decode_trade_information(&got, wire, 0) == 74);
  equal_trade_information(&got, &sent);

  for (size_t i = 0; i < 74; i++) { wire[i] = arbitrary(); }
  assert(decode_trade_information(&got, wire, 0) == 74);
  assert(encode_trade_information(&got, again, 0) == 74);
  for (size_t i = 0; i < 74; i++) { assert(again[i] == wire[i]); }
}

/* ---- Trade Report Message: 145 bytes ----------------------------------------- */

/* Used to transmit agency debt trade transaction information to subscribers */
typedef struct {
  MessageHeader message_header;                           /* bytes 0 to 21 */
  Label label;                                            /* bytes 22 to 61 */
  OriginalDisseminationDate original_dissemination_date;  /* bytes 62 to 69 */
  TradeInformation trade_information;                     /* bytes 70 to 143 */
  uint8_t change_indicator;                               /* byte 144 */
} TradeReportMessage;

/* any Trade Report Message at all: every byte one the checker chooses */
static void any_trade_report_message(TradeReportMessage *record) {
  any_message_header(&record->message_header);
  any_label(&record->label);
  any_original_dissemination_date(&record->original_dissemination_date);
  any_trade_information(&record->trade_information);
  record->change_indicator = arbitrary();
}

/* Trade Report Message to the wire: 145 bytes from at, returning where the next byte goes */
static size_t encode_trade_report_message(const TradeReportMessage *record, uint8_t *wire, size_t at) {
  at = encode_message_header(&record->message_header, wire, at);
  at = encode_label(&record->label, wire, at);
  at = encode_original_dissemination_date(&record->original_dissemination_date, wire, at);
  at = encode_trade_information(&record->trade_information, wire, at);
  wire[at++] = record->change_indicator;

  return at;
}

/* Trade Report Message off the wire: 145 bytes from at, returning where the next byte lies */
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
  uint8_t wire[145];
  uint8_t again[145];

  any_trade_report_message(&sent);
  assert(encode_trade_report_message(&sent, wire, 0) == 145);
  assert(decode_trade_report_message(&got, wire, 0) == 145);
  equal_trade_report_message(&got, &sent);

  for (size_t i = 0; i < 145; i++) { wire[i] = arbitrary(); }
  assert(decode_trade_report_message(&got, wire, 0) == 145);
  assert(encode_trade_report_message(&got, again, 0) == 145);
  for (size_t i = 0; i < 145; i++) { assert(again[i] == wire[i]); }
}

/* ---- Original Trade Information: 74 bytes ------------------------------------ */

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
  uint8_t yield_direction;               /* byte 56 */
  uint8_t yield[13];                     /* bytes 57 to 69 */
  uint8_t when_issued_indicator;         /* byte 70 */
  uint8_t reporting_party_type;          /* byte 71 */
  uint8_t contra_party_type;             /* byte 72 */
  uint8_t ats_indicator;                 /* byte 73 */
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
  record->yield_direction = arbitrary();
  for (size_t i = 0; i < 13; i++) { record->yield[i] = arbitrary(); }
  record->when_issued_indicator = arbitrary();
  record->reporting_party_type = arbitrary();
  record->contra_party_type = arbitrary();
  record->ats_indicator = arbitrary();
}

/* Original Trade Information to the wire: 74 bytes from at, returning where the next byte goes */
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
  wire[at++] = record->yield_direction;
  for (size_t i = 0; i < 13; i++) { wire[at++] = record->yield[i]; }
  wire[at++] = record->when_issued_indicator;
  wire[at++] = record->reporting_party_type;
  wire[at++] = record->contra_party_type;
  wire[at++] = record->ats_indicator;

  return at;
}

/* Original Trade Information off the wire: 74 bytes from at, returning where the next byte lies */
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
  record->yield_direction = wire[at++];
  for (size_t i = 0; i < 13; i++) { record->yield[i] = wire[at++]; }
  record->when_issued_indicator = wire[at++];
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
  assert(read->yield_direction == written->yield_direction);
  for (size_t i = 0; i < 13; i++) { assert(read->yield[i] == written->yield[i]); }
  assert(read->when_issued_indicator == written->when_issued_indicator);
  assert(read->reporting_party_type == written->reporting_party_type);
  assert(read->contra_party_type == written->contra_party_type);
  assert(read->ats_indicator == written->ats_indicator);
}

/* Original Trade Information: written and read back, then read and written back */
static void check_original_trade_information(void) {
  OriginalTradeInformation sent;
  OriginalTradeInformation got;
  uint8_t wire[74];
  uint8_t again[74];

  any_original_trade_information(&sent);
  assert(encode_original_trade_information(&sent, wire, 0) == 74);
  assert(decode_original_trade_information(&got, wire, 0) == 74);
  equal_original_trade_information(&got, &sent);

  for (size_t i = 0; i < 74; i++) { wire[i] = arbitrary(); }
  assert(decode_original_trade_information(&got, wire, 0) == 74);
  assert(encode_original_trade_information(&got, again, 0) == 74);
  for (size_t i = 0; i < 74; i++) { assert(again[i] == wire[i]); }
}

/* ---- Trade Summary Information: 76 bytes ------------------------------------- */

/* Trade Summary Information */
typedef struct {
  uint8_t high_price[11];             /* bytes 0 to 10 */
  uint8_t high_yield_direction;       /* byte 11 */
  uint8_t high_yield[13];             /* bytes 12 to 24 */
  uint8_t low_price[11];              /* bytes 25 to 35 */
  uint8_t low_yield_direction;        /* byte 36 */
  uint8_t low_yield[13];              /* bytes 37 to 49 */
  uint8_t last_sale_price[11];        /* bytes 50 to 60 */
  uint8_t last_sale_yield_direction;  /* byte 61 */
  uint8_t last_sale_yield[13];        /* bytes 62 to 74 */
  uint8_t change_indicator;           /* byte 75 */
} TradeSummaryInformation;

/* any Trade Summary Information at all: every byte one the checker chooses */
static void any_trade_summary_information(TradeSummaryInformation *record) {
  for (size_t i = 0; i < 11; i++) { record->high_price[i] = arbitrary(); }
  record->high_yield_direction = arbitrary();
  for (size_t i = 0; i < 13; i++) { record->high_yield[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->low_price[i] = arbitrary(); }
  record->low_yield_direction = arbitrary();
  for (size_t i = 0; i < 13; i++) { record->low_yield[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->last_sale_price[i] = arbitrary(); }
  record->last_sale_yield_direction = arbitrary();
  for (size_t i = 0; i < 13; i++) { record->last_sale_yield[i] = arbitrary(); }
  record->change_indicator = arbitrary();
}

/* Trade Summary Information to the wire: 76 bytes from at, returning where the next byte goes */
static size_t encode_trade_summary_information(const TradeSummaryInformation *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->high_price[i]; }
  wire[at++] = record->high_yield_direction;
  for (size_t i = 0; i < 13; i++) { wire[at++] = record->high_yield[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->low_price[i]; }
  wire[at++] = record->low_yield_direction;
  for (size_t i = 0; i < 13; i++) { wire[at++] = record->low_yield[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->last_sale_price[i]; }
  wire[at++] = record->last_sale_yield_direction;
  for (size_t i = 0; i < 13; i++) { wire[at++] = record->last_sale_yield[i]; }
  wire[at++] = record->change_indicator;

  return at;
}

/* Trade Summary Information off the wire: 76 bytes from at, returning where the next byte lies */
static size_t decode_trade_summary_information(TradeSummaryInformation *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 11; i++) { record->high_price[i] = wire[at++]; }
  record->high_yield_direction = wire[at++];
  for (size_t i = 0; i < 13; i++) { record->high_yield[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->low_price[i] = wire[at++]; }
  record->low_yield_direction = wire[at++];
  for (size_t i = 0; i < 13; i++) { record->low_yield[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->last_sale_price[i] = wire[at++]; }
  record->last_sale_yield_direction = wire[at++];
  for (size_t i = 0; i < 13; i++) { record->last_sale_yield[i] = wire[at++]; }
  record->change_indicator = wire[at++];

  return at;
}

/* what was read of Trade Summary Information is what was written, byte for byte */
static void equal_trade_summary_information(const TradeSummaryInformation *read, const TradeSummaryInformation *written) {
  for (size_t i = 0; i < 11; i++) { assert(read->high_price[i] == written->high_price[i]); }
  assert(read->high_yield_direction == written->high_yield_direction);
  for (size_t i = 0; i < 13; i++) { assert(read->high_yield[i] == written->high_yield[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->low_price[i] == written->low_price[i]); }
  assert(read->low_yield_direction == written->low_yield_direction);
  for (size_t i = 0; i < 13; i++) { assert(read->low_yield[i] == written->low_yield[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->last_sale_price[i] == written->last_sale_price[i]); }
  assert(read->last_sale_yield_direction == written->last_sale_yield_direction);
  for (size_t i = 0; i < 13; i++) { assert(read->last_sale_yield[i] == written->last_sale_yield[i]); }
  assert(read->change_indicator == written->change_indicator);
}

/* Trade Summary Information: written and read back, then read and written back */
static void check_trade_summary_information(void) {
  TradeSummaryInformation sent;
  TradeSummaryInformation got;
  uint8_t wire[76];
  uint8_t again[76];

  any_trade_summary_information(&sent);
  assert(encode_trade_summary_information(&sent, wire, 0) == 76);
  assert(decode_trade_summary_information(&got, wire, 0) == 76);
  equal_trade_summary_information(&got, &sent);

  for (size_t i = 0; i < 76; i++) { wire[i] = arbitrary(); }
  assert(decode_trade_summary_information(&got, wire, 0) == 76);
  assert(encode_trade_summary_information(&got, again, 0) == 76);
  for (size_t i = 0; i < 76; i++) { assert(again[i] == wire[i]); }
}

/* ---- Trade Cancel Message: 228 bytes ----------------------------------------- */

/* Used to notify subscribers that a trade report entered during the current business day, or up to the past 19 business days, has been cancelled */
typedef struct {
  MessageHeader message_header;                           /* bytes 0 to 21 */
  Label label;                                            /* bytes 22 to 61 */
  OriginalDisseminationDate original_dissemination_date;  /* bytes 62 to 69 */
  uint8_t original_trade_identifier[7];                   /* bytes 70 to 76 */
  uint8_t report_function;                                /* byte 77 */
  OriginalTradeInformation original_trade_information;    /* bytes 78 to 151 */
  TradeSummaryInformation trade_summary_information;      /* bytes 152 to 227 */
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

/* Trade Cancel Message to the wire: 228 bytes from at, returning where the next byte goes */
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

/* Trade Cancel Message off the wire: 228 bytes from at, returning where the next byte lies */
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
  uint8_t wire[228];
  uint8_t again[228];

  any_trade_cancel_message(&sent);
  assert(encode_trade_cancel_message(&sent, wire, 0) == 228);
  assert(decode_trade_cancel_message(&got, wire, 0) == 228);
  equal_trade_cancel_message(&got, &sent);

  for (size_t i = 0; i < 228; i++) { wire[i] = arbitrary(); }
  assert(decode_trade_cancel_message(&got, wire, 0) == 228);
  assert(encode_trade_cancel_message(&got, again, 0) == 228);
  for (size_t i = 0; i < 228; i++) { assert(again[i] == wire[i]); }
}

/* ---- Correction Trade Information: 74 bytes ---------------------------------- */

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
  uint8_t yield_direction;               /* byte 56 */
  uint8_t yield[13];                     /* bytes 57 to 69 */
  uint8_t when_issued_indicator;         /* byte 70 */
  uint8_t reporting_party_type;          /* byte 71 */
  uint8_t contra_party_type;             /* byte 72 */
  uint8_t ats_indicator;                 /* byte 73 */
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
  record->yield_direction = arbitrary();
  for (size_t i = 0; i < 13; i++) { record->yield[i] = arbitrary(); }
  record->when_issued_indicator = arbitrary();
  record->reporting_party_type = arbitrary();
  record->contra_party_type = arbitrary();
  record->ats_indicator = arbitrary();
}

/* Correction Trade Information to the wire: 74 bytes from at, returning where the next byte goes */
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
  wire[at++] = record->yield_direction;
  for (size_t i = 0; i < 13; i++) { wire[at++] = record->yield[i]; }
  wire[at++] = record->when_issued_indicator;
  wire[at++] = record->reporting_party_type;
  wire[at++] = record->contra_party_type;
  wire[at++] = record->ats_indicator;

  return at;
}

/* Correction Trade Information off the wire: 74 bytes from at, returning where the next byte lies */
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
  record->yield_direction = wire[at++];
  for (size_t i = 0; i < 13; i++) { record->yield[i] = wire[at++]; }
  record->when_issued_indicator = wire[at++];
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
  assert(read->yield_direction == written->yield_direction);
  for (size_t i = 0; i < 13; i++) { assert(read->yield[i] == written->yield[i]); }
  assert(read->when_issued_indicator == written->when_issued_indicator);
  assert(read->reporting_party_type == written->reporting_party_type);
  assert(read->contra_party_type == written->contra_party_type);
  assert(read->ats_indicator == written->ats_indicator);
}

/* Correction Trade Information: written and read back, then read and written back */
static void check_correction_trade_information(void) {
  CorrectionTradeInformation sent;
  CorrectionTradeInformation got;
  uint8_t wire[74];
  uint8_t again[74];

  any_correction_trade_information(&sent);
  assert(encode_correction_trade_information(&sent, wire, 0) == 74);
  assert(decode_correction_trade_information(&got, wire, 0) == 74);
  equal_correction_trade_information(&got, &sent);

  for (size_t i = 0; i < 74; i++) { wire[i] = arbitrary(); }
  assert(decode_correction_trade_information(&got, wire, 0) == 74);
  assert(encode_correction_trade_information(&got, again, 0) == 74);
  for (size_t i = 0; i < 74; i++) { assert(again[i] == wire[i]); }
}

/* ---- Trade Correction Message: 302 bytes ------------------------------------- */

/* Used to transmit trade correction data from a transaction that was entered either earlier in the day or within the past 19 business days */
typedef struct {
  MessageHeader message_header;                             /* bytes 0 to 21 */
  Label label;                                              /* bytes 22 to 61 */
  OriginalDisseminationDate original_dissemination_date;    /* bytes 62 to 69 */
  uint8_t original_trade_identifier[7];                     /* bytes 70 to 76 */
  uint8_t report_function;                                  /* byte 77 */
  OriginalTradeInformation original_trade_information;      /* bytes 78 to 151 */
  CorrectionTradeInformation correction_trade_information;  /* bytes 152 to 225 */
  TradeSummaryInformation trade_summary_information;        /* bytes 226 to 301 */
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

/* Trade Correction Message to the wire: 302 bytes from at, returning where the next byte goes */
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

/* Trade Correction Message off the wire: 302 bytes from at, returning where the next byte lies */
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
  uint8_t wire[302];
  uint8_t again[302];

  any_trade_correction_message(&sent);
  assert(encode_trade_correction_message(&sent, wire, 0) == 302);
  assert(decode_trade_correction_message(&got, wire, 0) == 302);
  equal_trade_correction_message(&got, &sent);

  for (size_t i = 0; i < 302; i++) { wire[i] = arbitrary(); }
  assert(decode_trade_correction_message(&got, wire, 0) == 302);
  assert(encode_trade_correction_message(&got, again, 0) == 302);
  for (size_t i = 0; i < 302; i++) { assert(again[i] == wire[i]); }
}

/* ---- Daily Trade Summary Message: 138 bytes ---------------------------------- */

/* Price summary message disseminated for each agency debt security that traded during the day during the normal trading hours */
typedef struct {
  MessageHeader message_header;   /* bytes 0 to 21 */
  Label label;                    /* bytes 22 to 61 */
  uint8_t when_issued_indicator;  /* byte 62 */
  uint8_t daily_high_price[11];   /* bytes 63 to 73 */
  uint8_t high_yield_direction;   /* byte 74 */
  uint8_t daily_high_yield[13];   /* bytes 75 to 87 */
  uint8_t daily_low_price[11];    /* bytes 88 to 98 */
  uint8_t low_yield_direction;    /* byte 99 */
  uint8_t daily_low_yield[13];    /* bytes 100 to 112 */
  uint8_t daily_close_price[11];  /* bytes 113 to 123 */
  uint8_t close_yield_direction;  /* byte 124 */
  uint8_t daily_close_yield[13];  /* bytes 125 to 137 */
} DailyTradeSummaryMessage;

/* any Daily Trade Summary Message at all: every byte one the checker chooses */
static void any_daily_trade_summary_message(DailyTradeSummaryMessage *record) {
  any_message_header(&record->message_header);
  any_label(&record->label);
  record->when_issued_indicator = arbitrary();
  for (size_t i = 0; i < 11; i++) { record->daily_high_price[i] = arbitrary(); }
  record->high_yield_direction = arbitrary();
  for (size_t i = 0; i < 13; i++) { record->daily_high_yield[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->daily_low_price[i] = arbitrary(); }
  record->low_yield_direction = arbitrary();
  for (size_t i = 0; i < 13; i++) { record->daily_low_yield[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->daily_close_price[i] = arbitrary(); }
  record->close_yield_direction = arbitrary();
  for (size_t i = 0; i < 13; i++) { record->daily_close_yield[i] = arbitrary(); }
}

/* Daily Trade Summary Message to the wire: 138 bytes from at, returning where the next byte goes */
static size_t encode_daily_trade_summary_message(const DailyTradeSummaryMessage *record, uint8_t *wire, size_t at) {
  at = encode_message_header(&record->message_header, wire, at);
  at = encode_label(&record->label, wire, at);
  wire[at++] = record->when_issued_indicator;
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->daily_high_price[i]; }
  wire[at++] = record->high_yield_direction;
  for (size_t i = 0; i < 13; i++) { wire[at++] = record->daily_high_yield[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->daily_low_price[i]; }
  wire[at++] = record->low_yield_direction;
  for (size_t i = 0; i < 13; i++) { wire[at++] = record->daily_low_yield[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->daily_close_price[i]; }
  wire[at++] = record->close_yield_direction;
  for (size_t i = 0; i < 13; i++) { wire[at++] = record->daily_close_yield[i]; }

  return at;
}

/* Daily Trade Summary Message off the wire: 138 bytes from at, returning where the next byte lies */
static size_t decode_daily_trade_summary_message(DailyTradeSummaryMessage *record, const uint8_t *wire, size_t at) {
  at = decode_message_header(&record->message_header, wire, at);
  at = decode_label(&record->label, wire, at);
  record->when_issued_indicator = wire[at++];
  for (size_t i = 0; i < 11; i++) { record->daily_high_price[i] = wire[at++]; }
  record->high_yield_direction = wire[at++];
  for (size_t i = 0; i < 13; i++) { record->daily_high_yield[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->daily_low_price[i] = wire[at++]; }
  record->low_yield_direction = wire[at++];
  for (size_t i = 0; i < 13; i++) { record->daily_low_yield[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->daily_close_price[i] = wire[at++]; }
  record->close_yield_direction = wire[at++];
  for (size_t i = 0; i < 13; i++) { record->daily_close_yield[i] = wire[at++]; }

  return at;
}

/* what was read of Daily Trade Summary Message is what was written, byte for byte */
static void equal_daily_trade_summary_message(const DailyTradeSummaryMessage *read, const DailyTradeSummaryMessage *written) {
  equal_message_header(&read->message_header, &written->message_header);
  equal_label(&read->label, &written->label);
  assert(read->when_issued_indicator == written->when_issued_indicator);
  for (size_t i = 0; i < 11; i++) { assert(read->daily_high_price[i] == written->daily_high_price[i]); }
  assert(read->high_yield_direction == written->high_yield_direction);
  for (size_t i = 0; i < 13; i++) { assert(read->daily_high_yield[i] == written->daily_high_yield[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->daily_low_price[i] == written->daily_low_price[i]); }
  assert(read->low_yield_direction == written->low_yield_direction);
  for (size_t i = 0; i < 13; i++) { assert(read->daily_low_yield[i] == written->daily_low_yield[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->daily_close_price[i] == written->daily_close_price[i]); }
  assert(read->close_yield_direction == written->close_yield_direction);
  for (size_t i = 0; i < 13; i++) { assert(read->daily_close_yield[i] == written->daily_close_yield[i]); }
}

/* Daily Trade Summary Message: written and read back, then read and written back */
static void check_daily_trade_summary_message(void) {
  DailyTradeSummaryMessage sent;
  DailyTradeSummaryMessage got;
  uint8_t wire[138];
  uint8_t again[138];

  any_daily_trade_summary_message(&sent);
  assert(encode_daily_trade_summary_message(&sent, wire, 0) == 138);
  assert(decode_daily_trade_summary_message(&got, wire, 0) == 138);
  equal_daily_trade_summary_message(&got, &sent);

  for (size_t i = 0; i < 138; i++) { wire[i] = arbitrary(); }
  assert(decode_daily_trade_summary_message(&got, wire, 0) == 138);
  assert(encode_daily_trade_summary_message(&got, again, 0) == 138);
  for (size_t i = 0; i < 138; i++) { assert(again[i] == wire[i]); }
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

/* Disseminated when a trading halt is instituted or removed for an agency debt security */
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

/* ---- Market Breadth Information: 196 bytes ----------------------------------- */

/* Market Breadth Information */
typedef struct {
  uint8_t total_securities_traded_all_securities[6];  /* bytes 0 to 5 */
  uint8_t total_securities_traded_freddie_mac[6];     /* bytes 6 to 11 */
  uint8_t total_securities_traded_fannie_mae[6];      /* bytes 12 to 17 */
  uint8_t total_securities_traded_fhlb[6];            /* bytes 18 to 23 */
  uint8_t advances_all_securities[6];                 /* bytes 24 to 29 */
  uint8_t advances_freddie_mac[6];                    /* bytes 30 to 35 */
  uint8_t advances_fannie_mae[6];                     /* bytes 36 to 41 */
  uint8_t advances_fhlb[6];                           /* bytes 42 to 47 */
  uint8_t declines_all_securities[6];                 /* bytes 48 to 53 */
  uint8_t declines_freddie_mac[6];                    /* bytes 54 to 59 */
  uint8_t declines_fannie_mae[6];                     /* bytes 60 to 65 */
  uint8_t declines_fhlb[6];                           /* bytes 66 to 71 */
  uint8_t unchanged_all_securities[6];                /* bytes 72 to 77 */
  uint8_t unchanged_freddie_mac[6];                   /* bytes 78 to 83 */
  uint8_t unchanged_fannie_mae[6];                    /* bytes 84 to 89 */
  uint8_t unchanged_fhlb[6];                          /* bytes 90 to 95 */
  uint8_t fifty_two_week_high_all_securities[6];      /* bytes 96 to 101 */
  uint8_t fifty_two_week_high_freddie_mac[6];         /* bytes 102 to 107 */
  uint8_t fifty_two_week_high_fannie_mae[6];          /* bytes 108 to 113 */
  uint8_t fifty_two_week_high_fhlb[6];                /* bytes 114 to 119 */
  uint8_t fifty_two_week_low_all_securities[6];       /* bytes 120 to 125 */
  uint8_t fifty_two_week_low_freddie_mac[6];          /* bytes 126 to 131 */
  uint8_t fifty_two_week_low_fannie_mae[6];           /* bytes 132 to 137 */
  uint8_t fifty_two_week_low_fhlb[6];                 /* bytes 138 to 143 */
  uint8_t total_volume_all_securities[13];            /* bytes 144 to 156 */
  uint8_t total_volume_freddie_mac[13];               /* bytes 157 to 169 */
  uint8_t total_volume_fannie_mae[13];                /* bytes 170 to 182 */
  uint8_t total_volume_fhlb[13];                      /* bytes 183 to 195 */
} MarketBreadthInformation;

/* any Market Breadth Information at all: every byte one the checker chooses */
static void any_market_breadth_information(MarketBreadthInformation *record) {
  for (size_t i = 0; i < 6; i++) { record->total_securities_traded_all_securities[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->total_securities_traded_freddie_mac[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->total_securities_traded_fannie_mae[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->total_securities_traded_fhlb[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->advances_all_securities[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->advances_freddie_mac[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->advances_fannie_mae[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->advances_fhlb[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->declines_all_securities[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->declines_freddie_mac[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->declines_fannie_mae[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->declines_fhlb[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->unchanged_all_securities[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->unchanged_freddie_mac[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->unchanged_fannie_mae[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->unchanged_fhlb[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->fifty_two_week_high_all_securities[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->fifty_two_week_high_freddie_mac[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->fifty_two_week_high_fannie_mae[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->fifty_two_week_high_fhlb[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->fifty_two_week_low_all_securities[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->fifty_two_week_low_freddie_mac[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->fifty_two_week_low_fannie_mae[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->fifty_two_week_low_fhlb[i] = arbitrary(); }
  for (size_t i = 0; i < 13; i++) { record->total_volume_all_securities[i] = arbitrary(); }
  for (size_t i = 0; i < 13; i++) { record->total_volume_freddie_mac[i] = arbitrary(); }
  for (size_t i = 0; i < 13; i++) { record->total_volume_fannie_mae[i] = arbitrary(); }
  for (size_t i = 0; i < 13; i++) { record->total_volume_fhlb[i] = arbitrary(); }
}

/* Market Breadth Information to the wire: 196 bytes from at, returning where the next byte goes */
static size_t encode_market_breadth_information(const MarketBreadthInformation *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->total_securities_traded_all_securities[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->total_securities_traded_freddie_mac[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->total_securities_traded_fannie_mae[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->total_securities_traded_fhlb[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->advances_all_securities[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->advances_freddie_mac[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->advances_fannie_mae[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->advances_fhlb[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->declines_all_securities[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->declines_freddie_mac[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->declines_fannie_mae[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->declines_fhlb[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->unchanged_all_securities[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->unchanged_freddie_mac[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->unchanged_fannie_mae[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->unchanged_fhlb[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->fifty_two_week_high_all_securities[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->fifty_two_week_high_freddie_mac[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->fifty_two_week_high_fannie_mae[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->fifty_two_week_high_fhlb[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->fifty_two_week_low_all_securities[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->fifty_two_week_low_freddie_mac[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->fifty_two_week_low_fannie_mae[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->fifty_two_week_low_fhlb[i]; }
  for (size_t i = 0; i < 13; i++) { wire[at++] = record->total_volume_all_securities[i]; }
  for (size_t i = 0; i < 13; i++) { wire[at++] = record->total_volume_freddie_mac[i]; }
  for (size_t i = 0; i < 13; i++) { wire[at++] = record->total_volume_fannie_mae[i]; }
  for (size_t i = 0; i < 13; i++) { wire[at++] = record->total_volume_fhlb[i]; }

  return at;
}

/* Market Breadth Information off the wire: 196 bytes from at, returning where the next byte lies */
static size_t decode_market_breadth_information(MarketBreadthInformation *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 6; i++) { record->total_securities_traded_all_securities[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->total_securities_traded_freddie_mac[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->total_securities_traded_fannie_mae[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->total_securities_traded_fhlb[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->advances_all_securities[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->advances_freddie_mac[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->advances_fannie_mae[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->advances_fhlb[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->declines_all_securities[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->declines_freddie_mac[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->declines_fannie_mae[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->declines_fhlb[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->unchanged_all_securities[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->unchanged_freddie_mac[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->unchanged_fannie_mae[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->unchanged_fhlb[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->fifty_two_week_high_all_securities[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->fifty_two_week_high_freddie_mac[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->fifty_two_week_high_fannie_mae[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->fifty_two_week_high_fhlb[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->fifty_two_week_low_all_securities[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->fifty_two_week_low_freddie_mac[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->fifty_two_week_low_fannie_mae[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->fifty_two_week_low_fhlb[i] = wire[at++]; }
  for (size_t i = 0; i < 13; i++) { record->total_volume_all_securities[i] = wire[at++]; }
  for (size_t i = 0; i < 13; i++) { record->total_volume_freddie_mac[i] = wire[at++]; }
  for (size_t i = 0; i < 13; i++) { record->total_volume_fannie_mae[i] = wire[at++]; }
  for (size_t i = 0; i < 13; i++) { record->total_volume_fhlb[i] = wire[at++]; }

  return at;
}

/* what was read of Market Breadth Information is what was written, byte for byte */
static void equal_market_breadth_information(const MarketBreadthInformation *read, const MarketBreadthInformation *written) {
  for (size_t i = 0; i < 6; i++) { assert(read->total_securities_traded_all_securities[i] == written->total_securities_traded_all_securities[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->total_securities_traded_freddie_mac[i] == written->total_securities_traded_freddie_mac[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->total_securities_traded_fannie_mae[i] == written->total_securities_traded_fannie_mae[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->total_securities_traded_fhlb[i] == written->total_securities_traded_fhlb[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->advances_all_securities[i] == written->advances_all_securities[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->advances_freddie_mac[i] == written->advances_freddie_mac[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->advances_fannie_mae[i] == written->advances_fannie_mae[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->advances_fhlb[i] == written->advances_fhlb[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->declines_all_securities[i] == written->declines_all_securities[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->declines_freddie_mac[i] == written->declines_freddie_mac[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->declines_fannie_mae[i] == written->declines_fannie_mae[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->declines_fhlb[i] == written->declines_fhlb[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->unchanged_all_securities[i] == written->unchanged_all_securities[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->unchanged_freddie_mac[i] == written->unchanged_freddie_mac[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->unchanged_fannie_mae[i] == written->unchanged_fannie_mae[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->unchanged_fhlb[i] == written->unchanged_fhlb[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->fifty_two_week_high_all_securities[i] == written->fifty_two_week_high_all_securities[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->fifty_two_week_high_freddie_mac[i] == written->fifty_two_week_high_freddie_mac[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->fifty_two_week_high_fannie_mae[i] == written->fifty_two_week_high_fannie_mae[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->fifty_two_week_high_fhlb[i] == written->fifty_two_week_high_fhlb[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->fifty_two_week_low_all_securities[i] == written->fifty_two_week_low_all_securities[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->fifty_two_week_low_freddie_mac[i] == written->fifty_two_week_low_freddie_mac[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->fifty_two_week_low_fannie_mae[i] == written->fifty_two_week_low_fannie_mae[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->fifty_two_week_low_fhlb[i] == written->fifty_two_week_low_fhlb[i]); }
  for (size_t i = 0; i < 13; i++) { assert(read->total_volume_all_securities[i] == written->total_volume_all_securities[i]); }
  for (size_t i = 0; i < 13; i++) { assert(read->total_volume_freddie_mac[i] == written->total_volume_freddie_mac[i]); }
  for (size_t i = 0; i < 13; i++) { assert(read->total_volume_fannie_mae[i] == written->total_volume_fannie_mae[i]); }
  for (size_t i = 0; i < 13; i++) { assert(read->total_volume_fhlb[i] == written->total_volume_fhlb[i]); }
}

/* Market Breadth Information: written and read back, then read and written back */
static void check_market_breadth_information(void) {
  MarketBreadthInformation sent;
  MarketBreadthInformation got;
  uint8_t wire[196];
  uint8_t again[196];

  any_market_breadth_information(&sent);
  assert(encode_market_breadth_information(&sent, wire, 0) == 196);
  assert(decode_market_breadth_information(&got, wire, 0) == 196);
  equal_market_breadth_information(&got, &sent);

  for (size_t i = 0; i < 196; i++) { wire[i] = arbitrary(); }
  assert(decode_market_breadth_information(&got, wire, 0) == 196);
  assert(encode_market_breadth_information(&got, again, 0) == 196);
  for (size_t i = 0; i < 196; i++) { assert(again[i] == wire[i]); }
}

/* ---- Market Breadth Message: 218 bytes --------------------------------------- */

/* End of day market breadth aggregate data for Trace eligible publicly traded securities */
typedef struct {
  MessageHeader message_header;                         /* bytes 0 to 21 */
  MarketBreadthInformation market_breadth_information;  /* bytes 22 to 217 */
} MarketBreadthMessage;

/* any Market Breadth Message at all: every byte one the checker chooses */
static void any_market_breadth_message(MarketBreadthMessage *record) {
  any_message_header(&record->message_header);
  any_market_breadth_information(&record->market_breadth_information);
}

/* Market Breadth Message to the wire: 218 bytes from at, returning where the next byte goes */
static size_t encode_market_breadth_message(const MarketBreadthMessage *record, uint8_t *wire, size_t at) {
  at = encode_message_header(&record->message_header, wire, at);
  at = encode_market_breadth_information(&record->market_breadth_information, wire, at);

  return at;
}

/* Market Breadth Message off the wire: 218 bytes from at, returning where the next byte lies */
static size_t decode_market_breadth_message(MarketBreadthMessage *record, const uint8_t *wire, size_t at) {
  at = decode_message_header(&record->message_header, wire, at);
  at = decode_market_breadth_information(&record->market_breadth_information, wire, at);

  return at;
}

/* what was read of Market Breadth Message is what was written, byte for byte */
static void equal_market_breadth_message(const MarketBreadthMessage *read, const MarketBreadthMessage *written) {
  equal_message_header(&read->message_header, &written->message_header);
  equal_market_breadth_information(&read->market_breadth_information, &written->market_breadth_information);
}

/* Market Breadth Message: written and read back, then read and written back */
static void check_market_breadth_message(void) {
  MarketBreadthMessage sent;
  MarketBreadthMessage got;
  uint8_t wire[218];
  uint8_t again[218];

  any_market_breadth_message(&sent);
  assert(encode_market_breadth_message(&sent, wire, 0) == 218);
  assert(decode_market_breadth_message(&got, wire, 0) == 218);
  equal_market_breadth_message(&got, &sent);

  for (size_t i = 0; i < 218; i++) { wire[i] = arbitrary(); }
  assert(decode_market_breadth_message(&got, wire, 0) == 218);
  assert(encode_market_breadth_message(&got, again, 0) == 218);
  for (size_t i = 0; i < 218; i++) { assert(again[i] == wire[i]); }
}

/* ---- Market Sentiment Information: 150 bytes --------------------------------- */

/* Market Sentiment Information */
typedef struct {
  uint8_t total_number_of_transactions_all_securities[6];  /* bytes 0 to 5 */
  uint8_t total_securities_traded_all_securities[6];       /* bytes 6 to 11 */
  uint8_t total_volume_all_securities[13];                 /* bytes 12 to 24 */
  uint8_t total_number_of_transactions_customer_buy[6];    /* bytes 25 to 30 */
  uint8_t total_securities_traded_customer_buy[6];         /* bytes 31 to 36 */
  uint8_t total_volume_customer_buy[13];                   /* bytes 37 to 49 */
  uint8_t total_number_of_transactions_customer_sell[6];   /* bytes 50 to 55 */
  uint8_t total_securities_traded_customer_sell[6];        /* bytes 56 to 61 */
  uint8_t total_volume_customer_sell[13];                  /* bytes 62 to 74 */
  uint8_t total_number_of_transactions_affiliate_buy[6];   /* bytes 75 to 80 */
  uint8_t total_securities_traded_affiliate_buy[6];        /* bytes 81 to 86 */
  uint8_t total_volume_affiliate_buy[13];                  /* bytes 87 to 99 */
  uint8_t total_number_of_transactions_affiliate_sell[6];  /* bytes 100 to 105 */
  uint8_t total_securities_traded_affiliate_sell[6];       /* bytes 106 to 111 */
  uint8_t total_volume_affiliate_sell[13];                 /* bytes 112 to 124 */
  uint8_t total_number_of_transactions_inter_dealer[6];    /* bytes 125 to 130 */
  uint8_t total_securities_traded_inter_dealer[6];         /* bytes 131 to 136 */
  uint8_t total_volume_inter_dealer[13];                   /* bytes 137 to 149 */
} MarketSentimentInformation;

/* any Market Sentiment Information at all: every byte one the checker chooses */
static void any_market_sentiment_information(MarketSentimentInformation *record) {
  for (size_t i = 0; i < 6; i++) { record->total_number_of_transactions_all_securities[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->total_securities_traded_all_securities[i] = arbitrary(); }
  for (size_t i = 0; i < 13; i++) { record->total_volume_all_securities[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->total_number_of_transactions_customer_buy[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->total_securities_traded_customer_buy[i] = arbitrary(); }
  for (size_t i = 0; i < 13; i++) { record->total_volume_customer_buy[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->total_number_of_transactions_customer_sell[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->total_securities_traded_customer_sell[i] = arbitrary(); }
  for (size_t i = 0; i < 13; i++) { record->total_volume_customer_sell[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->total_number_of_transactions_affiliate_buy[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->total_securities_traded_affiliate_buy[i] = arbitrary(); }
  for (size_t i = 0; i < 13; i++) { record->total_volume_affiliate_buy[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->total_number_of_transactions_affiliate_sell[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->total_securities_traded_affiliate_sell[i] = arbitrary(); }
  for (size_t i = 0; i < 13; i++) { record->total_volume_affiliate_sell[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->total_number_of_transactions_inter_dealer[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->total_securities_traded_inter_dealer[i] = arbitrary(); }
  for (size_t i = 0; i < 13; i++) { record->total_volume_inter_dealer[i] = arbitrary(); }
}

/* Market Sentiment Information to the wire: 150 bytes from at, returning where the next byte goes */
static size_t encode_market_sentiment_information(const MarketSentimentInformation *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->total_number_of_transactions_all_securities[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->total_securities_traded_all_securities[i]; }
  for (size_t i = 0; i < 13; i++) { wire[at++] = record->total_volume_all_securities[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->total_number_of_transactions_customer_buy[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->total_securities_traded_customer_buy[i]; }
  for (size_t i = 0; i < 13; i++) { wire[at++] = record->total_volume_customer_buy[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->total_number_of_transactions_customer_sell[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->total_securities_traded_customer_sell[i]; }
  for (size_t i = 0; i < 13; i++) { wire[at++] = record->total_volume_customer_sell[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->total_number_of_transactions_affiliate_buy[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->total_securities_traded_affiliate_buy[i]; }
  for (size_t i = 0; i < 13; i++) { wire[at++] = record->total_volume_affiliate_buy[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->total_number_of_transactions_affiliate_sell[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->total_securities_traded_affiliate_sell[i]; }
  for (size_t i = 0; i < 13; i++) { wire[at++] = record->total_volume_affiliate_sell[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->total_number_of_transactions_inter_dealer[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->total_securities_traded_inter_dealer[i]; }
  for (size_t i = 0; i < 13; i++) { wire[at++] = record->total_volume_inter_dealer[i]; }

  return at;
}

/* Market Sentiment Information off the wire: 150 bytes from at, returning where the next byte lies */
static size_t decode_market_sentiment_information(MarketSentimentInformation *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 6; i++) { record->total_number_of_transactions_all_securities[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->total_securities_traded_all_securities[i] = wire[at++]; }
  for (size_t i = 0; i < 13; i++) { record->total_volume_all_securities[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->total_number_of_transactions_customer_buy[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->total_securities_traded_customer_buy[i] = wire[at++]; }
  for (size_t i = 0; i < 13; i++) { record->total_volume_customer_buy[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->total_number_of_transactions_customer_sell[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->total_securities_traded_customer_sell[i] = wire[at++]; }
  for (size_t i = 0; i < 13; i++) { record->total_volume_customer_sell[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->total_number_of_transactions_affiliate_buy[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->total_securities_traded_affiliate_buy[i] = wire[at++]; }
  for (size_t i = 0; i < 13; i++) { record->total_volume_affiliate_buy[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->total_number_of_transactions_affiliate_sell[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->total_securities_traded_affiliate_sell[i] = wire[at++]; }
  for (size_t i = 0; i < 13; i++) { record->total_volume_affiliate_sell[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->total_number_of_transactions_inter_dealer[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->total_securities_traded_inter_dealer[i] = wire[at++]; }
  for (size_t i = 0; i < 13; i++) { record->total_volume_inter_dealer[i] = wire[at++]; }

  return at;
}

/* what was read of Market Sentiment Information is what was written, byte for byte */
static void equal_market_sentiment_information(const MarketSentimentInformation *read, const MarketSentimentInformation *written) {
  for (size_t i = 0; i < 6; i++) { assert(read->total_number_of_transactions_all_securities[i] == written->total_number_of_transactions_all_securities[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->total_securities_traded_all_securities[i] == written->total_securities_traded_all_securities[i]); }
  for (size_t i = 0; i < 13; i++) { assert(read->total_volume_all_securities[i] == written->total_volume_all_securities[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->total_number_of_transactions_customer_buy[i] == written->total_number_of_transactions_customer_buy[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->total_securities_traded_customer_buy[i] == written->total_securities_traded_customer_buy[i]); }
  for (size_t i = 0; i < 13; i++) { assert(read->total_volume_customer_buy[i] == written->total_volume_customer_buy[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->total_number_of_transactions_customer_sell[i] == written->total_number_of_transactions_customer_sell[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->total_securities_traded_customer_sell[i] == written->total_securities_traded_customer_sell[i]); }
  for (size_t i = 0; i < 13; i++) { assert(read->total_volume_customer_sell[i] == written->total_volume_customer_sell[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->total_number_of_transactions_affiliate_buy[i] == written->total_number_of_transactions_affiliate_buy[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->total_securities_traded_affiliate_buy[i] == written->total_securities_traded_affiliate_buy[i]); }
  for (size_t i = 0; i < 13; i++) { assert(read->total_volume_affiliate_buy[i] == written->total_volume_affiliate_buy[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->total_number_of_transactions_affiliate_sell[i] == written->total_number_of_transactions_affiliate_sell[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->total_securities_traded_affiliate_sell[i] == written->total_securities_traded_affiliate_sell[i]); }
  for (size_t i = 0; i < 13; i++) { assert(read->total_volume_affiliate_sell[i] == written->total_volume_affiliate_sell[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->total_number_of_transactions_inter_dealer[i] == written->total_number_of_transactions_inter_dealer[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->total_securities_traded_inter_dealer[i] == written->total_securities_traded_inter_dealer[i]); }
  for (size_t i = 0; i < 13; i++) { assert(read->total_volume_inter_dealer[i] == written->total_volume_inter_dealer[i]); }
}

/* Market Sentiment Information: written and read back, then read and written back */
static void check_market_sentiment_information(void) {
  MarketSentimentInformation sent;
  MarketSentimentInformation got;
  uint8_t wire[150];
  uint8_t again[150];

  any_market_sentiment_information(&sent);
  assert(encode_market_sentiment_information(&sent, wire, 0) == 150);
  assert(decode_market_sentiment_information(&got, wire, 0) == 150);
  equal_market_sentiment_information(&got, &sent);

  for (size_t i = 0; i < 150; i++) { wire[i] = arbitrary(); }
  assert(decode_market_sentiment_information(&got, wire, 0) == 150);
  assert(encode_market_sentiment_information(&got, again, 0) == 150);
  for (size_t i = 0; i < 150; i++) { assert(again[i] == wire[i]); }
}

/* ---- Market Sentiment All Securities Message: 172 bytes ---------------------- */

/* End of day market sentiment aggregate data for all securities */
typedef struct {
  MessageHeader message_header;                             /* bytes 0 to 21 */
  MarketSentimentInformation market_sentiment_information;  /* bytes 22 to 171 */
} MarketSentimentAllSecuritiesMessage;

/* any Market Sentiment All Securities Message at all: every byte one the checker chooses */
static void any_market_sentiment_all_securities_message(MarketSentimentAllSecuritiesMessage *record) {
  any_message_header(&record->message_header);
  any_market_sentiment_information(&record->market_sentiment_information);
}

/* Market Sentiment All Securities Message to the wire: 172 bytes from at, returning where the next byte goes */
static size_t encode_market_sentiment_all_securities_message(const MarketSentimentAllSecuritiesMessage *record, uint8_t *wire, size_t at) {
  at = encode_message_header(&record->message_header, wire, at);
  at = encode_market_sentiment_information(&record->market_sentiment_information, wire, at);

  return at;
}

/* Market Sentiment All Securities Message off the wire: 172 bytes from at, returning where the next byte lies */
static size_t decode_market_sentiment_all_securities_message(MarketSentimentAllSecuritiesMessage *record, const uint8_t *wire, size_t at) {
  at = decode_message_header(&record->message_header, wire, at);
  at = decode_market_sentiment_information(&record->market_sentiment_information, wire, at);

  return at;
}

/* what was read of Market Sentiment All Securities Message is what was written, byte for byte */
static void equal_market_sentiment_all_securities_message(const MarketSentimentAllSecuritiesMessage *read, const MarketSentimentAllSecuritiesMessage *written) {
  equal_message_header(&read->message_header, &written->message_header);
  equal_market_sentiment_information(&read->market_sentiment_information, &written->market_sentiment_information);
}

/* Market Sentiment All Securities Message: written and read back, then read and written back */
static void check_market_sentiment_all_securities_message(void) {
  MarketSentimentAllSecuritiesMessage sent;
  MarketSentimentAllSecuritiesMessage got;
  uint8_t wire[172];
  uint8_t again[172];

  any_market_sentiment_all_securities_message(&sent);
  assert(encode_market_sentiment_all_securities_message(&sent, wire, 0) == 172);
  assert(decode_market_sentiment_all_securities_message(&got, wire, 0) == 172);
  equal_market_sentiment_all_securities_message(&got, &sent);

  for (size_t i = 0; i < 172; i++) { wire[i] = arbitrary(); }
  assert(decode_market_sentiment_all_securities_message(&got, wire, 0) == 172);
  assert(encode_market_sentiment_all_securities_message(&got, again, 0) == 172);
  for (size_t i = 0; i < 172; i++) { assert(again[i] == wire[i]); }
}

/* ---- Market Sentiment Fannie Mae Message: 172 bytes -------------------------- */

/* End of day market sentiment aggregate data for Fannie Mae issues */
typedef struct {
  MessageHeader message_header;                             /* bytes 0 to 21 */
  MarketSentimentInformation market_sentiment_information;  /* bytes 22 to 171 */
} MarketSentimentFannieMaeMessage;

/* any Market Sentiment Fannie Mae Message at all: every byte one the checker chooses */
static void any_market_sentiment_fannie_mae_message(MarketSentimentFannieMaeMessage *record) {
  any_message_header(&record->message_header);
  any_market_sentiment_information(&record->market_sentiment_information);
}

/* Market Sentiment Fannie Mae Message to the wire: 172 bytes from at, returning where the next byte goes */
static size_t encode_market_sentiment_fannie_mae_message(const MarketSentimentFannieMaeMessage *record, uint8_t *wire, size_t at) {
  at = encode_message_header(&record->message_header, wire, at);
  at = encode_market_sentiment_information(&record->market_sentiment_information, wire, at);

  return at;
}

/* Market Sentiment Fannie Mae Message off the wire: 172 bytes from at, returning where the next byte lies */
static size_t decode_market_sentiment_fannie_mae_message(MarketSentimentFannieMaeMessage *record, const uint8_t *wire, size_t at) {
  at = decode_message_header(&record->message_header, wire, at);
  at = decode_market_sentiment_information(&record->market_sentiment_information, wire, at);

  return at;
}

/* what was read of Market Sentiment Fannie Mae Message is what was written, byte for byte */
static void equal_market_sentiment_fannie_mae_message(const MarketSentimentFannieMaeMessage *read, const MarketSentimentFannieMaeMessage *written) {
  equal_message_header(&read->message_header, &written->message_header);
  equal_market_sentiment_information(&read->market_sentiment_information, &written->market_sentiment_information);
}

/* Market Sentiment Fannie Mae Message: written and read back, then read and written back */
static void check_market_sentiment_fannie_mae_message(void) {
  MarketSentimentFannieMaeMessage sent;
  MarketSentimentFannieMaeMessage got;
  uint8_t wire[172];
  uint8_t again[172];

  any_market_sentiment_fannie_mae_message(&sent);
  assert(encode_market_sentiment_fannie_mae_message(&sent, wire, 0) == 172);
  assert(decode_market_sentiment_fannie_mae_message(&got, wire, 0) == 172);
  equal_market_sentiment_fannie_mae_message(&got, &sent);

  for (size_t i = 0; i < 172; i++) { wire[i] = arbitrary(); }
  assert(decode_market_sentiment_fannie_mae_message(&got, wire, 0) == 172);
  assert(encode_market_sentiment_fannie_mae_message(&got, again, 0) == 172);
  for (size_t i = 0; i < 172; i++) { assert(again[i] == wire[i]); }
}

/* ---- Market Sentiment Fhlb Message: 172 bytes -------------------------------- */

/* End of day market sentiment aggregate data for Federal Home Loan Bank issues */
typedef struct {
  MessageHeader message_header;                             /* bytes 0 to 21 */
  MarketSentimentInformation market_sentiment_information;  /* bytes 22 to 171 */
} MarketSentimentFhlbMessage;

/* any Market Sentiment Fhlb Message at all: every byte one the checker chooses */
static void any_market_sentiment_fhlb_message(MarketSentimentFhlbMessage *record) {
  any_message_header(&record->message_header);
  any_market_sentiment_information(&record->market_sentiment_information);
}

/* Market Sentiment Fhlb Message to the wire: 172 bytes from at, returning where the next byte goes */
static size_t encode_market_sentiment_fhlb_message(const MarketSentimentFhlbMessage *record, uint8_t *wire, size_t at) {
  at = encode_message_header(&record->message_header, wire, at);
  at = encode_market_sentiment_information(&record->market_sentiment_information, wire, at);

  return at;
}

/* Market Sentiment Fhlb Message off the wire: 172 bytes from at, returning where the next byte lies */
static size_t decode_market_sentiment_fhlb_message(MarketSentimentFhlbMessage *record, const uint8_t *wire, size_t at) {
  at = decode_message_header(&record->message_header, wire, at);
  at = decode_market_sentiment_information(&record->market_sentiment_information, wire, at);

  return at;
}

/* what was read of Market Sentiment Fhlb Message is what was written, byte for byte */
static void equal_market_sentiment_fhlb_message(const MarketSentimentFhlbMessage *read, const MarketSentimentFhlbMessage *written) {
  equal_message_header(&read->message_header, &written->message_header);
  equal_market_sentiment_information(&read->market_sentiment_information, &written->market_sentiment_information);
}

/* Market Sentiment Fhlb Message: written and read back, then read and written back */
static void check_market_sentiment_fhlb_message(void) {
  MarketSentimentFhlbMessage sent;
  MarketSentimentFhlbMessage got;
  uint8_t wire[172];
  uint8_t again[172];

  any_market_sentiment_fhlb_message(&sent);
  assert(encode_market_sentiment_fhlb_message(&sent, wire, 0) == 172);
  assert(decode_market_sentiment_fhlb_message(&got, wire, 0) == 172);
  equal_market_sentiment_fhlb_message(&got, &sent);

  for (size_t i = 0; i < 172; i++) { wire[i] = arbitrary(); }
  assert(decode_market_sentiment_fhlb_message(&got, wire, 0) == 172);
  assert(encode_market_sentiment_fhlb_message(&got, again, 0) == 172);
  for (size_t i = 0; i < 172; i++) { assert(again[i] == wire[i]); }
}

/* ---- Market Sentiment Freddie Mac Message: 172 bytes ------------------------- */

/* End of day market sentiment aggregate data for Freddie Mac issues */
typedef struct {
  MessageHeader message_header;                             /* bytes 0 to 21 */
  MarketSentimentInformation market_sentiment_information;  /* bytes 22 to 171 */
} MarketSentimentFreddieMacMessage;

/* any Market Sentiment Freddie Mac Message at all: every byte one the checker chooses */
static void any_market_sentiment_freddie_mac_message(MarketSentimentFreddieMacMessage *record) {
  any_message_header(&record->message_header);
  any_market_sentiment_information(&record->market_sentiment_information);
}

/* Market Sentiment Freddie Mac Message to the wire: 172 bytes from at, returning where the next byte goes */
static size_t encode_market_sentiment_freddie_mac_message(const MarketSentimentFreddieMacMessage *record, uint8_t *wire, size_t at) {
  at = encode_message_header(&record->message_header, wire, at);
  at = encode_market_sentiment_information(&record->market_sentiment_information, wire, at);

  return at;
}

/* Market Sentiment Freddie Mac Message off the wire: 172 bytes from at, returning where the next byte lies */
static size_t decode_market_sentiment_freddie_mac_message(MarketSentimentFreddieMacMessage *record, const uint8_t *wire, size_t at) {
  at = decode_message_header(&record->message_header, wire, at);
  at = decode_market_sentiment_information(&record->market_sentiment_information, wire, at);

  return at;
}

/* what was read of Market Sentiment Freddie Mac Message is what was written, byte for byte */
static void equal_market_sentiment_freddie_mac_message(const MarketSentimentFreddieMacMessage *read, const MarketSentimentFreddieMacMessage *written) {
  equal_message_header(&read->message_header, &written->message_header);
  equal_market_sentiment_information(&read->market_sentiment_information, &written->market_sentiment_information);
}

/* Market Sentiment Freddie Mac Message: written and read back, then read and written back */
static void check_market_sentiment_freddie_mac_message(void) {
  MarketSentimentFreddieMacMessage sent;
  MarketSentimentFreddieMacMessage got;
  uint8_t wire[172];
  uint8_t again[172];

  any_market_sentiment_freddie_mac_message(&sent);
  assert(encode_market_sentiment_freddie_mac_message(&sent, wire, 0) == 172);
  assert(decode_market_sentiment_freddie_mac_message(&got, wire, 0) == 172);
  equal_market_sentiment_freddie_mac_message(&got, &sent);

  for (size_t i = 0; i < 172; i++) { wire[i] = arbitrary(); }
  assert(decode_market_sentiment_freddie_mac_message(&got, wire, 0) == 172);
  assert(encode_market_sentiment_freddie_mac_message(&got, again, 0) == 172);
  for (size_t i = 0; i < 172; i++) { assert(again[i] == wire[i]); }
}

/* ---- Start Of Day Message: 22 bytes ------------------------------------------ */

/* Signifies the beginning of each operational cycle */
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

/* Signifies the end of each operational cycle */
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

/* Signifies the opening of the market session */
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

/* Signifies the closing of the market session */
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

/* Signifies the end of the trade reporting session */
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

/* Signifies that no further transmissions will be sent for the day */
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
  check_market_breadth_information();
  check_market_breadth_message();
  check_market_sentiment_information();
  check_market_sentiment_all_securities_message();
  check_market_sentiment_fannie_mae_message();
  check_market_sentiment_fhlb_message();
  check_market_sentiment_freddie_mac_message();
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
