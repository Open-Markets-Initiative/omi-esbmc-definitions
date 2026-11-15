// finra/finraorf/tdds/FinraOrf_Tdds_v2_1.c
/*
 * Financial Industry Regulatory Authority Trade Data Dissemination Service
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

/* ---- Datetime: 23 bytes ------------------------------------------------------ */

/* Datetime */
typedef struct {
  uint8_t year[4];               /* bytes 0 to 3 */
  uint8_t month[2];              /* bytes 4 to 5 */
  uint8_t day[2];                /* bytes 6 to 7 */
  uint8_t hour[2];               /* bytes 8 to 9 */
  uint8_t minute[2];             /* bytes 10 to 11 */
  uint8_t second[2];             /* bytes 12 to 13 */
  uint8_t fractional_second[9];  /* bytes 14 to 22 */
} Datetime;

/* any Datetime at all: every byte one the checker chooses */
static void any_datetime(Datetime *record) {
  for (size_t i = 0; i < 4; i++) { record->year[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->month[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->day[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->hour[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->minute[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->second[i] = arbitrary(); }
  for (size_t i = 0; i < 9; i++) { record->fractional_second[i] = arbitrary(); }
}

/* Datetime to the wire: 23 bytes from at, returning where the next byte goes */
static size_t encode_datetime(const Datetime *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->year[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->month[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->day[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->hour[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->minute[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->second[i]; }
  for (size_t i = 0; i < 9; i++) { wire[at++] = record->fractional_second[i]; }

  return at;
}

/* Datetime off the wire: 23 bytes from at, returning where the next byte lies */
static size_t decode_datetime(Datetime *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->year[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->month[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->day[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->hour[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->minute[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->second[i] = wire[at++]; }
  for (size_t i = 0; i < 9; i++) { record->fractional_second[i] = wire[at++]; }

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
  for (size_t i = 0; i < 9; i++) { assert(read->fractional_second[i] == written->fractional_second[i]); }
}

/* Datetime: written and read back, then read and written back */
static void check_datetime(void) {
  Datetime sent;
  Datetime got;
  uint8_t wire[23];
  uint8_t again[23];

  any_datetime(&sent);
  assert(encode_datetime(&sent, wire, 0) == 23);
  assert(decode_datetime(&got, wire, 0) == 23);
  equal_datetime(&got, &sent);

  for (size_t i = 0; i < 23; i++) { wire[i] = arbitrary(); }
  assert(decode_datetime(&got, wire, 0) == 23);
  assert(encode_datetime(&got, again, 0) == 23);
  for (size_t i = 0; i < 23; i++) { assert(again[i] == wire[i]); }
}

/* ---- Message Header: 33 bytes ------------------------------------------------ */

/* Message Header */
typedef struct {
  uint8_t trade_identifier[8];             /* bytes 0 to 7 */
  uint8_t market_center_originator_id[2];  /* bytes 8 to 9 */
  Datetime datetime;                       /* bytes 10 to 32 */
} MessageHeader;

/* any Message Header at all: every byte one the checker chooses */
static void any_message_header(MessageHeader *record) {
  for (size_t i = 0; i < 8; i++) { record->trade_identifier[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->market_center_originator_id[i] = arbitrary(); }
  any_datetime(&record->datetime);
}

/* Message Header to the wire: 33 bytes from at, returning where the next byte goes */
static size_t encode_message_header(const MessageHeader *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->trade_identifier[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->market_center_originator_id[i]; }
  at = encode_datetime(&record->datetime, wire, at);

  return at;
}

/* Message Header off the wire: 33 bytes from at, returning where the next byte lies */
static size_t decode_message_header(MessageHeader *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->trade_identifier[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->market_center_originator_id[i] = wire[at++]; }
  at = decode_datetime(&record->datetime, wire, at);

  return at;
}

/* what was read of Message Header is what was written, byte for byte */
static void equal_message_header(const MessageHeader *read, const MessageHeader *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->trade_identifier[i] == written->trade_identifier[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->market_center_originator_id[i] == written->market_center_originator_id[i]); }
  equal_datetime(&read->datetime, &written->datetime);
}

/* Message Header: written and read back, then read and written back */
static void check_message_header(void) {
  MessageHeader sent;
  MessageHeader got;
  uint8_t wire[33];
  uint8_t again[33];

  any_message_header(&sent);
  assert(encode_message_header(&sent, wire, 0) == 33);
  assert(decode_message_header(&got, wire, 0) == 33);
  equal_message_header(&got, &sent);

  for (size_t i = 0; i < 33; i++) { wire[i] = arbitrary(); }
  assert(decode_message_header(&got, wire, 0) == 33);
  assert(encode_message_header(&got, again, 0) == 33);
  for (size_t i = 0; i < 33; i++) { assert(again[i] == wire[i]); }
}

/* ---- Trade Report Short Form Message: 53 bytes ------------------------------- */

/* Economized trade report */
typedef struct {
  MessageHeader message_header;      /* bytes 0 to 32 */
  uint8_t security_symbol_short[5];  /* bytes 33 to 37 */
  uint8_t sale_condition_level_1;    /* byte 38 */
  uint8_t trade_price_denominator;   /* byte 39 */
  uint8_t trade_price_short[6];      /* bytes 40 to 45 */
  uint8_t report_volume_short[6];    /* bytes 46 to 51 */
  uint8_t price_change_indicator;    /* byte 52 */
} TradeReportShortFormMessage;

/* any Trade Report Short Form Message at all: every byte one the checker chooses */
static void any_trade_report_short_form_message(TradeReportShortFormMessage *record) {
  any_message_header(&record->message_header);
  for (size_t i = 0; i < 5; i++) { record->security_symbol_short[i] = arbitrary(); }
  record->sale_condition_level_1 = arbitrary();
  record->trade_price_denominator = arbitrary();
  for (size_t i = 0; i < 6; i++) { record->trade_price_short[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->report_volume_short[i] = arbitrary(); }
  record->price_change_indicator = arbitrary();
}

/* Trade Report Short Form Message to the wire: 53 bytes from at, returning where the next byte goes */
static size_t encode_trade_report_short_form_message(const TradeReportShortFormMessage *record, uint8_t *wire, size_t at) {
  at = encode_message_header(&record->message_header, wire, at);
  for (size_t i = 0; i < 5; i++) { wire[at++] = record->security_symbol_short[i]; }
  wire[at++] = record->sale_condition_level_1;
  wire[at++] = record->trade_price_denominator;
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->trade_price_short[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->report_volume_short[i]; }
  wire[at++] = record->price_change_indicator;

  return at;
}

/* Trade Report Short Form Message off the wire: 53 bytes from at, returning where the next byte lies */
static size_t decode_trade_report_short_form_message(TradeReportShortFormMessage *record, const uint8_t *wire, size_t at) {
  at = decode_message_header(&record->message_header, wire, at);
  for (size_t i = 0; i < 5; i++) { record->security_symbol_short[i] = wire[at++]; }
  record->sale_condition_level_1 = wire[at++];
  record->trade_price_denominator = wire[at++];
  for (size_t i = 0; i < 6; i++) { record->trade_price_short[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->report_volume_short[i] = wire[at++]; }
  record->price_change_indicator = wire[at++];

  return at;
}

/* what was read of Trade Report Short Form Message is what was written, byte for byte */
static void equal_trade_report_short_form_message(const TradeReportShortFormMessage *read, const TradeReportShortFormMessage *written) {
  equal_message_header(&read->message_header, &written->message_header);
  for (size_t i = 0; i < 5; i++) { assert(read->security_symbol_short[i] == written->security_symbol_short[i]); }
  assert(read->sale_condition_level_1 == written->sale_condition_level_1);
  assert(read->trade_price_denominator == written->trade_price_denominator);
  for (size_t i = 0; i < 6; i++) { assert(read->trade_price_short[i] == written->trade_price_short[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->report_volume_short[i] == written->report_volume_short[i]); }
  assert(read->price_change_indicator == written->price_change_indicator);
}

/* Trade Report Short Form Message: written and read back, then read and written back */
static void check_trade_report_short_form_message(void) {
  TradeReportShortFormMessage sent;
  TradeReportShortFormMessage got;
  uint8_t wire[53];
  uint8_t again[53];

  any_trade_report_short_form_message(&sent);
  assert(encode_trade_report_short_form_message(&sent, wire, 0) == 53);
  assert(decode_trade_report_short_form_message(&got, wire, 0) == 53);
  equal_trade_report_short_form_message(&got, &sent);

  for (size_t i = 0; i < 53; i++) { wire[i] = arbitrary(); }
  assert(decode_trade_report_short_form_message(&got, wire, 0) == 53);
  assert(encode_trade_report_short_form_message(&got, again, 0) == 53);
  for (size_t i = 0; i < 53; i++) { assert(again[i] == wire[i]); }
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

/* ---- Execution Datetime: 23 bytes -------------------------------------------- */

/* Execution Datetime */
typedef struct {
  uint8_t year[4];               /* bytes 0 to 3 */
  uint8_t month[2];              /* bytes 4 to 5 */
  uint8_t day[2];                /* bytes 6 to 7 */
  uint8_t hour[2];               /* bytes 8 to 9 */
  uint8_t minute[2];             /* bytes 10 to 11 */
  uint8_t second[2];             /* bytes 12 to 13 */
  uint8_t fractional_second[9];  /* bytes 14 to 22 */
} ExecutionDatetime;

/* any Execution Datetime at all: every byte one the checker chooses */
static void any_execution_datetime(ExecutionDatetime *record) {
  for (size_t i = 0; i < 4; i++) { record->year[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->month[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->day[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->hour[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->minute[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->second[i] = arbitrary(); }
  for (size_t i = 0; i < 9; i++) { record->fractional_second[i] = arbitrary(); }
}

/* Execution Datetime to the wire: 23 bytes from at, returning where the next byte goes */
static size_t encode_execution_datetime(const ExecutionDatetime *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->year[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->month[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->day[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->hour[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->minute[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->second[i]; }
  for (size_t i = 0; i < 9; i++) { wire[at++] = record->fractional_second[i]; }

  return at;
}

/* Execution Datetime off the wire: 23 bytes from at, returning where the next byte lies */
static size_t decode_execution_datetime(ExecutionDatetime *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->year[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->month[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->day[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->hour[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->minute[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->second[i] = wire[at++]; }
  for (size_t i = 0; i < 9; i++) { record->fractional_second[i] = wire[at++]; }

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
  for (size_t i = 0; i < 9; i++) { assert(read->fractional_second[i] == written->fractional_second[i]); }
}

/* Execution Datetime: written and read back, then read and written back */
static void check_execution_datetime(void) {
  ExecutionDatetime sent;
  ExecutionDatetime got;
  uint8_t wire[23];
  uint8_t again[23];

  any_execution_datetime(&sent);
  assert(encode_execution_datetime(&sent, wire, 0) == 23);
  assert(decode_execution_datetime(&got, wire, 0) == 23);
  equal_execution_datetime(&got, &sent);

  for (size_t i = 0; i < 23; i++) { wire[i] = arbitrary(); }
  assert(decode_execution_datetime(&got, wire, 0) == 23);
  assert(encode_execution_datetime(&got, again, 0) == 23);
  for (size_t i = 0; i < 23; i++) { assert(again[i] == wire[i]); }
}

/* ---- Trade Information: 55 bytes --------------------------------------------- */

/* Trade Information */
typedef struct {
  uint8_t report_volume[8];              /* bytes 0 to 7 */
  uint8_t trade_price_denominator;       /* byte 8 */
  uint8_t trade_price[12];               /* bytes 9 to 20 */
  uint8_t currency[3];                   /* bytes 21 to 23 */
  uint8_t as_of_indicator;               /* byte 24 */
  ExecutionDatetime execution_datetime;  /* bytes 25 to 47 */
  uint8_t sale_condition_level_1;        /* byte 48 */
  uint8_t sale_condition_level_2;        /* byte 49 */
  uint8_t sale_condition_level_3;        /* byte 50 */
  uint8_t sale_condition_level_4;        /* byte 51 */
  uint8_t sellers_sale_days[2];          /* bytes 52 to 53 */
  uint8_t price_change_indicator;        /* byte 54 */
} TradeInformation;

/* any Trade Information at all: every byte one the checker chooses */
static void any_trade_information(TradeInformation *record) {
  for (size_t i = 0; i < 8; i++) { record->report_volume[i] = arbitrary(); }
  record->trade_price_denominator = arbitrary();
  for (size_t i = 0; i < 12; i++) { record->trade_price[i] = arbitrary(); }
  for (size_t i = 0; i < 3; i++) { record->currency[i] = arbitrary(); }
  record->as_of_indicator = arbitrary();
  any_execution_datetime(&record->execution_datetime);
  record->sale_condition_level_1 = arbitrary();
  record->sale_condition_level_2 = arbitrary();
  record->sale_condition_level_3 = arbitrary();
  record->sale_condition_level_4 = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->sellers_sale_days[i] = arbitrary(); }
  record->price_change_indicator = arbitrary();
}

/* Trade Information to the wire: 55 bytes from at, returning where the next byte goes */
static size_t encode_trade_information(const TradeInformation *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->report_volume[i]; }
  wire[at++] = record->trade_price_denominator;
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->trade_price[i]; }
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->currency[i]; }
  wire[at++] = record->as_of_indicator;
  at = encode_execution_datetime(&record->execution_datetime, wire, at);
  wire[at++] = record->sale_condition_level_1;
  wire[at++] = record->sale_condition_level_2;
  wire[at++] = record->sale_condition_level_3;
  wire[at++] = record->sale_condition_level_4;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->sellers_sale_days[i]; }
  wire[at++] = record->price_change_indicator;

  return at;
}

/* Trade Information off the wire: 55 bytes from at, returning where the next byte lies */
static size_t decode_trade_information(TradeInformation *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->report_volume[i] = wire[at++]; }
  record->trade_price_denominator = wire[at++];
  for (size_t i = 0; i < 12; i++) { record->trade_price[i] = wire[at++]; }
  for (size_t i = 0; i < 3; i++) { record->currency[i] = wire[at++]; }
  record->as_of_indicator = wire[at++];
  at = decode_execution_datetime(&record->execution_datetime, wire, at);
  record->sale_condition_level_1 = wire[at++];
  record->sale_condition_level_2 = wire[at++];
  record->sale_condition_level_3 = wire[at++];
  record->sale_condition_level_4 = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->sellers_sale_days[i] = wire[at++]; }
  record->price_change_indicator = wire[at++];

  return at;
}

/* what was read of Trade Information is what was written, byte for byte */
static void equal_trade_information(const TradeInformation *read, const TradeInformation *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->report_volume[i] == written->report_volume[i]); }
  assert(read->trade_price_denominator == written->trade_price_denominator);
  for (size_t i = 0; i < 12; i++) { assert(read->trade_price[i] == written->trade_price[i]); }
  for (size_t i = 0; i < 3; i++) { assert(read->currency[i] == written->currency[i]); }
  assert(read->as_of_indicator == written->as_of_indicator);
  equal_execution_datetime(&read->execution_datetime, &written->execution_datetime);
  assert(read->sale_condition_level_1 == written->sale_condition_level_1);
  assert(read->sale_condition_level_2 == written->sale_condition_level_2);
  assert(read->sale_condition_level_3 == written->sale_condition_level_3);
  assert(read->sale_condition_level_4 == written->sale_condition_level_4);
  for (size_t i = 0; i < 2; i++) { assert(read->sellers_sale_days[i] == written->sellers_sale_days[i]); }
  assert(read->price_change_indicator == written->price_change_indicator);
}

/* Trade Information: written and read back, then read and written back */
static void check_trade_information(void) {
  TradeInformation sent;
  TradeInformation got;
  uint8_t wire[55];
  uint8_t again[55];

  any_trade_information(&sent);
  assert(encode_trade_information(&sent, wire, 0) == 55);
  assert(decode_trade_information(&got, wire, 0) == 55);
  equal_trade_information(&got, &sent);

  for (size_t i = 0; i < 55; i++) { wire[i] = arbitrary(); }
  assert(decode_trade_information(&got, wire, 0) == 55);
  assert(encode_trade_information(&got, again, 0) == 55);
  for (size_t i = 0; i < 55; i++) { assert(again[i] == wire[i]); }
}

/* ---- Trade Report Long Form Message: 110 bytes ------------------------------- */

/* Complete trade report */
typedef struct {
  MessageHeader message_header;                           /* bytes 0 to 32 */
  uint8_t security_symbol[14];                            /* bytes 33 to 46 */
  OriginalDisseminationDate original_dissemination_date;  /* bytes 47 to 54 */
  TradeInformation trade_information;                     /* bytes 55 to 109 */
} TradeReportLongFormMessage;

/* any Trade Report Long Form Message at all: every byte one the checker chooses */
static void any_trade_report_long_form_message(TradeReportLongFormMessage *record) {
  any_message_header(&record->message_header);
  for (size_t i = 0; i < 14; i++) { record->security_symbol[i] = arbitrary(); }
  any_original_dissemination_date(&record->original_dissemination_date);
  any_trade_information(&record->trade_information);
}

/* Trade Report Long Form Message to the wire: 110 bytes from at, returning where the next byte goes */
static size_t encode_trade_report_long_form_message(const TradeReportLongFormMessage *record, uint8_t *wire, size_t at) {
  at = encode_message_header(&record->message_header, wire, at);
  for (size_t i = 0; i < 14; i++) { wire[at++] = record->security_symbol[i]; }
  at = encode_original_dissemination_date(&record->original_dissemination_date, wire, at);
  at = encode_trade_information(&record->trade_information, wire, at);

  return at;
}

/* Trade Report Long Form Message off the wire: 110 bytes from at, returning where the next byte lies */
static size_t decode_trade_report_long_form_message(TradeReportLongFormMessage *record, const uint8_t *wire, size_t at) {
  at = decode_message_header(&record->message_header, wire, at);
  for (size_t i = 0; i < 14; i++) { record->security_symbol[i] = wire[at++]; }
  at = decode_original_dissemination_date(&record->original_dissemination_date, wire, at);
  at = decode_trade_information(&record->trade_information, wire, at);

  return at;
}

/* what was read of Trade Report Long Form Message is what was written, byte for byte */
static void equal_trade_report_long_form_message(const TradeReportLongFormMessage *read, const TradeReportLongFormMessage *written) {
  equal_message_header(&read->message_header, &written->message_header);
  for (size_t i = 0; i < 14; i++) { assert(read->security_symbol[i] == written->security_symbol[i]); }
  equal_original_dissemination_date(&read->original_dissemination_date, &written->original_dissemination_date);
  equal_trade_information(&read->trade_information, &written->trade_information);
}

/* Trade Report Long Form Message: written and read back, then read and written back */
static void check_trade_report_long_form_message(void) {
  TradeReportLongFormMessage sent;
  TradeReportLongFormMessage got;
  uint8_t wire[110];
  uint8_t again[110];

  any_trade_report_long_form_message(&sent);
  assert(encode_trade_report_long_form_message(&sent, wire, 0) == 110);
  assert(decode_trade_report_long_form_message(&got, wire, 0) == 110);
  equal_trade_report_long_form_message(&got, &sent);

  for (size_t i = 0; i < 110; i++) { wire[i] = arbitrary(); }
  assert(decode_trade_report_long_form_message(&got, wire, 0) == 110);
  assert(encode_trade_report_long_form_message(&got, again, 0) == 110);
  for (size_t i = 0; i < 110; i++) { assert(again[i] == wire[i]); }
}

/* ---- Original Trade Information: 54 bytes ------------------------------------ */

/* Original Trade Information */
typedef struct {
  uint8_t report_volume[8];              /* bytes 0 to 7 */
  uint8_t trade_price_denominator;       /* byte 8 */
  uint8_t trade_price[12];               /* bytes 9 to 20 */
  uint8_t currency[3];                   /* bytes 21 to 23 */
  uint8_t as_of_indicator;               /* byte 24 */
  ExecutionDatetime execution_datetime;  /* bytes 25 to 47 */
  uint8_t sale_condition_level_1;        /* byte 48 */
  uint8_t sale_condition_level_2;        /* byte 49 */
  uint8_t sale_condition_level_3;        /* byte 50 */
  uint8_t sale_condition_level_4;        /* byte 51 */
  uint8_t sellers_sale_days[2];          /* bytes 52 to 53 */
} OriginalTradeInformation;

/* any Original Trade Information at all: every byte one the checker chooses */
static void any_original_trade_information(OriginalTradeInformation *record) {
  for (size_t i = 0; i < 8; i++) { record->report_volume[i] = arbitrary(); }
  record->trade_price_denominator = arbitrary();
  for (size_t i = 0; i < 12; i++) { record->trade_price[i] = arbitrary(); }
  for (size_t i = 0; i < 3; i++) { record->currency[i] = arbitrary(); }
  record->as_of_indicator = arbitrary();
  any_execution_datetime(&record->execution_datetime);
  record->sale_condition_level_1 = arbitrary();
  record->sale_condition_level_2 = arbitrary();
  record->sale_condition_level_3 = arbitrary();
  record->sale_condition_level_4 = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->sellers_sale_days[i] = arbitrary(); }
}

/* Original Trade Information to the wire: 54 bytes from at, returning where the next byte goes */
static size_t encode_original_trade_information(const OriginalTradeInformation *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->report_volume[i]; }
  wire[at++] = record->trade_price_denominator;
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->trade_price[i]; }
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->currency[i]; }
  wire[at++] = record->as_of_indicator;
  at = encode_execution_datetime(&record->execution_datetime, wire, at);
  wire[at++] = record->sale_condition_level_1;
  wire[at++] = record->sale_condition_level_2;
  wire[at++] = record->sale_condition_level_3;
  wire[at++] = record->sale_condition_level_4;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->sellers_sale_days[i]; }

  return at;
}

/* Original Trade Information off the wire: 54 bytes from at, returning where the next byte lies */
static size_t decode_original_trade_information(OriginalTradeInformation *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->report_volume[i] = wire[at++]; }
  record->trade_price_denominator = wire[at++];
  for (size_t i = 0; i < 12; i++) { record->trade_price[i] = wire[at++]; }
  for (size_t i = 0; i < 3; i++) { record->currency[i] = wire[at++]; }
  record->as_of_indicator = wire[at++];
  at = decode_execution_datetime(&record->execution_datetime, wire, at);
  record->sale_condition_level_1 = wire[at++];
  record->sale_condition_level_2 = wire[at++];
  record->sale_condition_level_3 = wire[at++];
  record->sale_condition_level_4 = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->sellers_sale_days[i] = wire[at++]; }

  return at;
}

/* what was read of Original Trade Information is what was written, byte for byte */
static void equal_original_trade_information(const OriginalTradeInformation *read, const OriginalTradeInformation *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->report_volume[i] == written->report_volume[i]); }
  assert(read->trade_price_denominator == written->trade_price_denominator);
  for (size_t i = 0; i < 12; i++) { assert(read->trade_price[i] == written->trade_price[i]); }
  for (size_t i = 0; i < 3; i++) { assert(read->currency[i] == written->currency[i]); }
  assert(read->as_of_indicator == written->as_of_indicator);
  equal_execution_datetime(&read->execution_datetime, &written->execution_datetime);
  assert(read->sale_condition_level_1 == written->sale_condition_level_1);
  assert(read->sale_condition_level_2 == written->sale_condition_level_2);
  assert(read->sale_condition_level_3 == written->sale_condition_level_3);
  assert(read->sale_condition_level_4 == written->sale_condition_level_4);
  for (size_t i = 0; i < 2; i++) { assert(read->sellers_sale_days[i] == written->sellers_sale_days[i]); }
}

/* Original Trade Information: written and read back, then read and written back */
static void check_original_trade_information(void) {
  OriginalTradeInformation sent;
  OriginalTradeInformation got;
  uint8_t wire[54];
  uint8_t again[54];

  any_original_trade_information(&sent);
  assert(encode_original_trade_information(&sent, wire, 0) == 54);
  assert(decode_original_trade_information(&got, wire, 0) == 54);
  equal_original_trade_information(&got, &sent);

  for (size_t i = 0; i < 54; i++) { wire[i] = arbitrary(); }
  assert(decode_original_trade_information(&got, wire, 0) == 54);
  assert(encode_original_trade_information(&got, again, 0) == 54);
  for (size_t i = 0; i < 54; i++) { assert(again[i] == wire[i]); }
}

/* ---- Trade Summary Information: 52 bytes ------------------------------------- */

/* Trade Summary Information */
typedef struct {
  uint8_t high_price_denominator;         /* byte 0 */
  uint8_t high_price[12];                 /* bytes 1 to 12 */
  uint8_t low_price_denominator;          /* byte 13 */
  uint8_t low_price[12];                  /* bytes 14 to 25 */
  uint8_t last_sale_price_denominator;    /* byte 26 */
  uint8_t last_sale_price[12];            /* bytes 27 to 38 */
  uint8_t last_sale_price_market_center;  /* byte 39 */
  uint8_t total_security_volume[11];      /* bytes 40 to 50 */
  uint8_t price_change_indicator;         /* byte 51 */
} TradeSummaryInformation;

/* any Trade Summary Information at all: every byte one the checker chooses */
static void any_trade_summary_information(TradeSummaryInformation *record) {
  record->high_price_denominator = arbitrary();
  for (size_t i = 0; i < 12; i++) { record->high_price[i] = arbitrary(); }
  record->low_price_denominator = arbitrary();
  for (size_t i = 0; i < 12; i++) { record->low_price[i] = arbitrary(); }
  record->last_sale_price_denominator = arbitrary();
  for (size_t i = 0; i < 12; i++) { record->last_sale_price[i] = arbitrary(); }
  record->last_sale_price_market_center = arbitrary();
  for (size_t i = 0; i < 11; i++) { record->total_security_volume[i] = arbitrary(); }
  record->price_change_indicator = arbitrary();
}

/* Trade Summary Information to the wire: 52 bytes from at, returning where the next byte goes */
static size_t encode_trade_summary_information(const TradeSummaryInformation *record, uint8_t *wire, size_t at) {
  wire[at++] = record->high_price_denominator;
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->high_price[i]; }
  wire[at++] = record->low_price_denominator;
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->low_price[i]; }
  wire[at++] = record->last_sale_price_denominator;
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->last_sale_price[i]; }
  wire[at++] = record->last_sale_price_market_center;
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->total_security_volume[i]; }
  wire[at++] = record->price_change_indicator;

  return at;
}

/* Trade Summary Information off the wire: 52 bytes from at, returning where the next byte lies */
static size_t decode_trade_summary_information(TradeSummaryInformation *record, const uint8_t *wire, size_t at) {
  record->high_price_denominator = wire[at++];
  for (size_t i = 0; i < 12; i++) { record->high_price[i] = wire[at++]; }
  record->low_price_denominator = wire[at++];
  for (size_t i = 0; i < 12; i++) { record->low_price[i] = wire[at++]; }
  record->last_sale_price_denominator = wire[at++];
  for (size_t i = 0; i < 12; i++) { record->last_sale_price[i] = wire[at++]; }
  record->last_sale_price_market_center = wire[at++];
  for (size_t i = 0; i < 11; i++) { record->total_security_volume[i] = wire[at++]; }
  record->price_change_indicator = wire[at++];

  return at;
}

/* what was read of Trade Summary Information is what was written, byte for byte */
static void equal_trade_summary_information(const TradeSummaryInformation *read, const TradeSummaryInformation *written) {
  assert(read->high_price_denominator == written->high_price_denominator);
  for (size_t i = 0; i < 12; i++) { assert(read->high_price[i] == written->high_price[i]); }
  assert(read->low_price_denominator == written->low_price_denominator);
  for (size_t i = 0; i < 12; i++) { assert(read->low_price[i] == written->low_price[i]); }
  assert(read->last_sale_price_denominator == written->last_sale_price_denominator);
  for (size_t i = 0; i < 12; i++) { assert(read->last_sale_price[i] == written->last_sale_price[i]); }
  assert(read->last_sale_price_market_center == written->last_sale_price_market_center);
  for (size_t i = 0; i < 11; i++) { assert(read->total_security_volume[i] == written->total_security_volume[i]); }
  assert(read->price_change_indicator == written->price_change_indicator);
}

/* Trade Summary Information: written and read back, then read and written back */
static void check_trade_summary_information(void) {
  TradeSummaryInformation sent;
  TradeSummaryInformation got;
  uint8_t wire[52];
  uint8_t again[52];

  any_trade_summary_information(&sent);
  assert(encode_trade_summary_information(&sent, wire, 0) == 52);
  assert(decode_trade_summary_information(&got, wire, 0) == 52);
  equal_trade_summary_information(&got, &sent);

  for (size_t i = 0; i < 52; i++) { wire[i] = arbitrary(); }
  assert(decode_trade_summary_information(&got, wire, 0) == 52);
  assert(encode_trade_summary_information(&got, again, 0) == 52);
  for (size_t i = 0; i < 52; i++) { assert(again[i] == wire[i]); }
}

/* ---- Trade Cancel Error Message: 162 bytes ----------------------------------- */

/* This message is used to notify TDDS customers if a trade report entered during the current business day, or up to the past three business days, has been canceled */
typedef struct {
  MessageHeader message_header;                           /* bytes 0 to 32 */
  uint8_t security_symbol[14];                            /* bytes 33 to 46 */
  OriginalDisseminationDate original_dissemination_date;  /* bytes 47 to 54 */
  uint8_t report_function;                                /* byte 55 */
  OriginalTradeInformation original_trade_information;    /* bytes 56 to 109 */
  TradeSummaryInformation trade_summary_information;      /* bytes 110 to 161 */
} TradeCancelErrorMessage;

/* any Trade Cancel Error Message at all: every byte one the checker chooses */
static void any_trade_cancel_error_message(TradeCancelErrorMessage *record) {
  any_message_header(&record->message_header);
  for (size_t i = 0; i < 14; i++) { record->security_symbol[i] = arbitrary(); }
  any_original_dissemination_date(&record->original_dissemination_date);
  record->report_function = arbitrary();
  any_original_trade_information(&record->original_trade_information);
  any_trade_summary_information(&record->trade_summary_information);
}

/* Trade Cancel Error Message to the wire: 162 bytes from at, returning where the next byte goes */
static size_t encode_trade_cancel_error_message(const TradeCancelErrorMessage *record, uint8_t *wire, size_t at) {
  at = encode_message_header(&record->message_header, wire, at);
  for (size_t i = 0; i < 14; i++) { wire[at++] = record->security_symbol[i]; }
  at = encode_original_dissemination_date(&record->original_dissemination_date, wire, at);
  wire[at++] = record->report_function;
  at = encode_original_trade_information(&record->original_trade_information, wire, at);
  at = encode_trade_summary_information(&record->trade_summary_information, wire, at);

  return at;
}

/* Trade Cancel Error Message off the wire: 162 bytes from at, returning where the next byte lies */
static size_t decode_trade_cancel_error_message(TradeCancelErrorMessage *record, const uint8_t *wire, size_t at) {
  at = decode_message_header(&record->message_header, wire, at);
  for (size_t i = 0; i < 14; i++) { record->security_symbol[i] = wire[at++]; }
  at = decode_original_dissemination_date(&record->original_dissemination_date, wire, at);
  record->report_function = wire[at++];
  at = decode_original_trade_information(&record->original_trade_information, wire, at);
  at = decode_trade_summary_information(&record->trade_summary_information, wire, at);

  return at;
}

/* what was read of Trade Cancel Error Message is what was written, byte for byte */
static void equal_trade_cancel_error_message(const TradeCancelErrorMessage *read, const TradeCancelErrorMessage *written) {
  equal_message_header(&read->message_header, &written->message_header);
  for (size_t i = 0; i < 14; i++) { assert(read->security_symbol[i] == written->security_symbol[i]); }
  equal_original_dissemination_date(&read->original_dissemination_date, &written->original_dissemination_date);
  assert(read->report_function == written->report_function);
  equal_original_trade_information(&read->original_trade_information, &written->original_trade_information);
  equal_trade_summary_information(&read->trade_summary_information, &written->trade_summary_information);
}

/* Trade Cancel Error Message: written and read back, then read and written back */
static void check_trade_cancel_error_message(void) {
  TradeCancelErrorMessage sent;
  TradeCancelErrorMessage got;
  uint8_t wire[162];
  uint8_t again[162];

  any_trade_cancel_error_message(&sent);
  assert(encode_trade_cancel_error_message(&sent, wire, 0) == 162);
  assert(decode_trade_cancel_error_message(&got, wire, 0) == 162);
  equal_trade_cancel_error_message(&got, &sent);

  for (size_t i = 0; i < 162; i++) { wire[i] = arbitrary(); }
  assert(decode_trade_cancel_error_message(&got, wire, 0) == 162);
  assert(encode_trade_cancel_error_message(&got, again, 0) == 162);
  for (size_t i = 0; i < 162; i++) { assert(again[i] == wire[i]); }
}

/* ---- Corrected Trade Information: 54 bytes ----------------------------------- */

/* Corrected Trade Information */
typedef struct {
  uint8_t report_volume[8];              /* bytes 0 to 7 */
  uint8_t trade_price_denominator;       /* byte 8 */
  uint8_t trade_price[12];               /* bytes 9 to 20 */
  uint8_t currency[3];                   /* bytes 21 to 23 */
  uint8_t as_of_indicator;               /* byte 24 */
  ExecutionDatetime execution_datetime;  /* bytes 25 to 47 */
  uint8_t sale_condition_level_1;        /* byte 48 */
  uint8_t sale_condition_level_2;        /* byte 49 */
  uint8_t sale_condition_level_3;        /* byte 50 */
  uint8_t sale_condition_level_4;        /* byte 51 */
  uint8_t sellers_sale_days[2];          /* bytes 52 to 53 */
} CorrectedTradeInformation;

/* any Corrected Trade Information at all: every byte one the checker chooses */
static void any_corrected_trade_information(CorrectedTradeInformation *record) {
  for (size_t i = 0; i < 8; i++) { record->report_volume[i] = arbitrary(); }
  record->trade_price_denominator = arbitrary();
  for (size_t i = 0; i < 12; i++) { record->trade_price[i] = arbitrary(); }
  for (size_t i = 0; i < 3; i++) { record->currency[i] = arbitrary(); }
  record->as_of_indicator = arbitrary();
  any_execution_datetime(&record->execution_datetime);
  record->sale_condition_level_1 = arbitrary();
  record->sale_condition_level_2 = arbitrary();
  record->sale_condition_level_3 = arbitrary();
  record->sale_condition_level_4 = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->sellers_sale_days[i] = arbitrary(); }
}

/* Corrected Trade Information to the wire: 54 bytes from at, returning where the next byte goes */
static size_t encode_corrected_trade_information(const CorrectedTradeInformation *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->report_volume[i]; }
  wire[at++] = record->trade_price_denominator;
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->trade_price[i]; }
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->currency[i]; }
  wire[at++] = record->as_of_indicator;
  at = encode_execution_datetime(&record->execution_datetime, wire, at);
  wire[at++] = record->sale_condition_level_1;
  wire[at++] = record->sale_condition_level_2;
  wire[at++] = record->sale_condition_level_3;
  wire[at++] = record->sale_condition_level_4;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->sellers_sale_days[i]; }

  return at;
}

/* Corrected Trade Information off the wire: 54 bytes from at, returning where the next byte lies */
static size_t decode_corrected_trade_information(CorrectedTradeInformation *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->report_volume[i] = wire[at++]; }
  record->trade_price_denominator = wire[at++];
  for (size_t i = 0; i < 12; i++) { record->trade_price[i] = wire[at++]; }
  for (size_t i = 0; i < 3; i++) { record->currency[i] = wire[at++]; }
  record->as_of_indicator = wire[at++];
  at = decode_execution_datetime(&record->execution_datetime, wire, at);
  record->sale_condition_level_1 = wire[at++];
  record->sale_condition_level_2 = wire[at++];
  record->sale_condition_level_3 = wire[at++];
  record->sale_condition_level_4 = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->sellers_sale_days[i] = wire[at++]; }

  return at;
}

/* what was read of Corrected Trade Information is what was written, byte for byte */
static void equal_corrected_trade_information(const CorrectedTradeInformation *read, const CorrectedTradeInformation *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->report_volume[i] == written->report_volume[i]); }
  assert(read->trade_price_denominator == written->trade_price_denominator);
  for (size_t i = 0; i < 12; i++) { assert(read->trade_price[i] == written->trade_price[i]); }
  for (size_t i = 0; i < 3; i++) { assert(read->currency[i] == written->currency[i]); }
  assert(read->as_of_indicator == written->as_of_indicator);
  equal_execution_datetime(&read->execution_datetime, &written->execution_datetime);
  assert(read->sale_condition_level_1 == written->sale_condition_level_1);
  assert(read->sale_condition_level_2 == written->sale_condition_level_2);
  assert(read->sale_condition_level_3 == written->sale_condition_level_3);
  assert(read->sale_condition_level_4 == written->sale_condition_level_4);
  for (size_t i = 0; i < 2; i++) { assert(read->sellers_sale_days[i] == written->sellers_sale_days[i]); }
}

/* Corrected Trade Information: written and read back, then read and written back */
static void check_corrected_trade_information(void) {
  CorrectedTradeInformation sent;
  CorrectedTradeInformation got;
  uint8_t wire[54];
  uint8_t again[54];

  any_corrected_trade_information(&sent);
  assert(encode_corrected_trade_information(&sent, wire, 0) == 54);
  assert(decode_corrected_trade_information(&got, wire, 0) == 54);
  equal_corrected_trade_information(&got, &sent);

  for (size_t i = 0; i < 54; i++) { wire[i] = arbitrary(); }
  assert(decode_corrected_trade_information(&got, wire, 0) == 54);
  assert(encode_corrected_trade_information(&got, again, 0) == 54);
  for (size_t i = 0; i < 54; i++) { assert(again[i] == wire[i]); }
}

/* ---- Trade Correction Message: 216 bytes ------------------------------------- */

/* Used to notify TDDS customers if a trade report entered during the current business day, or up to the past three business days, has been modified */
typedef struct {
  MessageHeader message_header;                           /* bytes 0 to 32 */
  uint8_t security_symbol[14];                            /* bytes 33 to 46 */
  OriginalDisseminationDate original_dissemination_date;  /* bytes 47 to 54 */
  uint8_t report_function;                                /* byte 55 */
  OriginalTradeInformation original_trade_information;    /* bytes 56 to 109 */
  CorrectedTradeInformation corrected_trade_information;  /* bytes 110 to 163 */
  TradeSummaryInformation trade_summary_information;      /* bytes 164 to 215 */
} TradeCorrectionMessage;

/* any Trade Correction Message at all: every byte one the checker chooses */
static void any_trade_correction_message(TradeCorrectionMessage *record) {
  any_message_header(&record->message_header);
  for (size_t i = 0; i < 14; i++) { record->security_symbol[i] = arbitrary(); }
  any_original_dissemination_date(&record->original_dissemination_date);
  record->report_function = arbitrary();
  any_original_trade_information(&record->original_trade_information);
  any_corrected_trade_information(&record->corrected_trade_information);
  any_trade_summary_information(&record->trade_summary_information);
}

/* Trade Correction Message to the wire: 216 bytes from at, returning where the next byte goes */
static size_t encode_trade_correction_message(const TradeCorrectionMessage *record, uint8_t *wire, size_t at) {
  at = encode_message_header(&record->message_header, wire, at);
  for (size_t i = 0; i < 14; i++) { wire[at++] = record->security_symbol[i]; }
  at = encode_original_dissemination_date(&record->original_dissemination_date, wire, at);
  wire[at++] = record->report_function;
  at = encode_original_trade_information(&record->original_trade_information, wire, at);
  at = encode_corrected_trade_information(&record->corrected_trade_information, wire, at);
  at = encode_trade_summary_information(&record->trade_summary_information, wire, at);

  return at;
}

/* Trade Correction Message off the wire: 216 bytes from at, returning where the next byte lies */
static size_t decode_trade_correction_message(TradeCorrectionMessage *record, const uint8_t *wire, size_t at) {
  at = decode_message_header(&record->message_header, wire, at);
  for (size_t i = 0; i < 14; i++) { record->security_symbol[i] = wire[at++]; }
  at = decode_original_dissemination_date(&record->original_dissemination_date, wire, at);
  record->report_function = wire[at++];
  at = decode_original_trade_information(&record->original_trade_information, wire, at);
  at = decode_corrected_trade_information(&record->corrected_trade_information, wire, at);
  at = decode_trade_summary_information(&record->trade_summary_information, wire, at);

  return at;
}

/* what was read of Trade Correction Message is what was written, byte for byte */
static void equal_trade_correction_message(const TradeCorrectionMessage *read, const TradeCorrectionMessage *written) {
  equal_message_header(&read->message_header, &written->message_header);
  for (size_t i = 0; i < 14; i++) { assert(read->security_symbol[i] == written->security_symbol[i]); }
  equal_original_dissemination_date(&read->original_dissemination_date, &written->original_dissemination_date);
  assert(read->report_function == written->report_function);
  equal_original_trade_information(&read->original_trade_information, &written->original_trade_information);
  equal_corrected_trade_information(&read->corrected_trade_information, &written->corrected_trade_information);
  equal_trade_summary_information(&read->trade_summary_information, &written->trade_summary_information);
}

/* Trade Correction Message: written and read back, then read and written back */
static void check_trade_correction_message(void) {
  TradeCorrectionMessage sent;
  TradeCorrectionMessage got;
  uint8_t wire[216];
  uint8_t again[216];

  any_trade_correction_message(&sent);
  assert(encode_trade_correction_message(&sent, wire, 0) == 216);
  assert(decode_trade_correction_message(&got, wire, 0) == 216);
  equal_trade_correction_message(&got, &sent);

  for (size_t i = 0; i < 216; i++) { wire[i] = arbitrary(); }
  assert(decode_trade_correction_message(&got, wire, 0) == 216);
  assert(encode_trade_correction_message(&got, again, 0) == 216);
  for (size_t i = 0; i < 216; i++) { assert(again[i] == wire[i]); }
}

/* ---- Closing Trade Summary Report Message: 114 bytes ------------------------- */

/* The closing trade summary will reflect the daily high, low, and closing prices as well as the total volume for the security */
typedef struct {
  MessageHeader message_header;          /* bytes 0 to 32 */
  uint8_t security_symbol[14];           /* bytes 33 to 46 */
  uint8_t daily_high_price_denominator;  /* byte 47 */
  uint8_t daily_high_price[12];          /* bytes 48 to 59 */
  uint8_t daily_low_price_denominator;   /* byte 60 */
  uint8_t daily_low_price[12];           /* bytes 61 to 72 */
  uint8_t closing_price_market_center;   /* byte 73 */
  uint8_t closing_price_denominator;     /* byte 74 */
  uint8_t closing_price[12];             /* bytes 75 to 86 */
  uint8_t reserved_1;                    /* byte 87 */
  uint8_t net_change_denominator;        /* byte 88 */
  uint8_t net_change_amount[10];         /* bytes 89 to 98 */
  uint8_t net_change_direction;          /* byte 99 */
  uint8_t currency[3];                   /* bytes 100 to 102 */
  uint8_t total_security_volume[11];     /* bytes 103 to 113 */
} ClosingTradeSummaryReportMessage;

/* any Closing Trade Summary Report Message at all: every byte one the checker chooses */
static void any_closing_trade_summary_report_message(ClosingTradeSummaryReportMessage *record) {
  any_message_header(&record->message_header);
  for (size_t i = 0; i < 14; i++) { record->security_symbol[i] = arbitrary(); }
  record->daily_high_price_denominator = arbitrary();
  for (size_t i = 0; i < 12; i++) { record->daily_high_price[i] = arbitrary(); }
  record->daily_low_price_denominator = arbitrary();
  for (size_t i = 0; i < 12; i++) { record->daily_low_price[i] = arbitrary(); }
  record->closing_price_market_center = arbitrary();
  record->closing_price_denominator = arbitrary();
  for (size_t i = 0; i < 12; i++) { record->closing_price[i] = arbitrary(); }
  record->reserved_1 = arbitrary();
  record->net_change_denominator = arbitrary();
  for (size_t i = 0; i < 10; i++) { record->net_change_amount[i] = arbitrary(); }
  record->net_change_direction = arbitrary();
  for (size_t i = 0; i < 3; i++) { record->currency[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->total_security_volume[i] = arbitrary(); }
}

/* Closing Trade Summary Report Message to the wire: 114 bytes from at, returning where the next byte goes */
static size_t encode_closing_trade_summary_report_message(const ClosingTradeSummaryReportMessage *record, uint8_t *wire, size_t at) {
  at = encode_message_header(&record->message_header, wire, at);
  for (size_t i = 0; i < 14; i++) { wire[at++] = record->security_symbol[i]; }
  wire[at++] = record->daily_high_price_denominator;
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->daily_high_price[i]; }
  wire[at++] = record->daily_low_price_denominator;
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->daily_low_price[i]; }
  wire[at++] = record->closing_price_market_center;
  wire[at++] = record->closing_price_denominator;
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->closing_price[i]; }
  wire[at++] = record->reserved_1;
  wire[at++] = record->net_change_denominator;
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->net_change_amount[i]; }
  wire[at++] = record->net_change_direction;
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->currency[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->total_security_volume[i]; }

  return at;
}

/* Closing Trade Summary Report Message off the wire: 114 bytes from at, returning where the next byte lies */
static size_t decode_closing_trade_summary_report_message(ClosingTradeSummaryReportMessage *record, const uint8_t *wire, size_t at) {
  at = decode_message_header(&record->message_header, wire, at);
  for (size_t i = 0; i < 14; i++) { record->security_symbol[i] = wire[at++]; }
  record->daily_high_price_denominator = wire[at++];
  for (size_t i = 0; i < 12; i++) { record->daily_high_price[i] = wire[at++]; }
  record->daily_low_price_denominator = wire[at++];
  for (size_t i = 0; i < 12; i++) { record->daily_low_price[i] = wire[at++]; }
  record->closing_price_market_center = wire[at++];
  record->closing_price_denominator = wire[at++];
  for (size_t i = 0; i < 12; i++) { record->closing_price[i] = wire[at++]; }
  record->reserved_1 = wire[at++];
  record->net_change_denominator = wire[at++];
  for (size_t i = 0; i < 10; i++) { record->net_change_amount[i] = wire[at++]; }
  record->net_change_direction = wire[at++];
  for (size_t i = 0; i < 3; i++) { record->currency[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->total_security_volume[i] = wire[at++]; }

  return at;
}

/* what was read of Closing Trade Summary Report Message is what was written, byte for byte */
static void equal_closing_trade_summary_report_message(const ClosingTradeSummaryReportMessage *read, const ClosingTradeSummaryReportMessage *written) {
  equal_message_header(&read->message_header, &written->message_header);
  for (size_t i = 0; i < 14; i++) { assert(read->security_symbol[i] == written->security_symbol[i]); }
  assert(read->daily_high_price_denominator == written->daily_high_price_denominator);
  for (size_t i = 0; i < 12; i++) { assert(read->daily_high_price[i] == written->daily_high_price[i]); }
  assert(read->daily_low_price_denominator == written->daily_low_price_denominator);
  for (size_t i = 0; i < 12; i++) { assert(read->daily_low_price[i] == written->daily_low_price[i]); }
  assert(read->closing_price_market_center == written->closing_price_market_center);
  assert(read->closing_price_denominator == written->closing_price_denominator);
  for (size_t i = 0; i < 12; i++) { assert(read->closing_price[i] == written->closing_price[i]); }
  assert(read->reserved_1 == written->reserved_1);
  assert(read->net_change_denominator == written->net_change_denominator);
  for (size_t i = 0; i < 10; i++) { assert(read->net_change_amount[i] == written->net_change_amount[i]); }
  assert(read->net_change_direction == written->net_change_direction);
  for (size_t i = 0; i < 3; i++) { assert(read->currency[i] == written->currency[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->total_security_volume[i] == written->total_security_volume[i]); }
}

/* Closing Trade Summary Report Message: written and read back, then read and written back */
static void check_closing_trade_summary_report_message(void) {
  ClosingTradeSummaryReportMessage sent;
  ClosingTradeSummaryReportMessage got;
  uint8_t wire[114];
  uint8_t again[114];

  any_closing_trade_summary_report_message(&sent);
  assert(encode_closing_trade_summary_report_message(&sent, wire, 0) == 114);
  assert(decode_closing_trade_summary_report_message(&got, wire, 0) == 114);
  equal_closing_trade_summary_report_message(&got, &sent);

  for (size_t i = 0; i < 114; i++) { wire[i] = arbitrary(); }
  assert(decode_closing_trade_summary_report_message(&got, wire, 0) == 114);
  assert(encode_closing_trade_summary_report_message(&got, again, 0) == 114);
  for (size_t i = 0; i < 114; i++) { assert(again[i] == wire[i]); }
}

/* ---- Action Datetime: 23 bytes ----------------------------------------------- */

/* Action Datetime */
typedef struct {
  uint8_t year[4];               /* bytes 0 to 3 */
  uint8_t month[2];              /* bytes 4 to 5 */
  uint8_t day[2];                /* bytes 6 to 7 */
  uint8_t hour[2];               /* bytes 8 to 9 */
  uint8_t minute[2];             /* bytes 10 to 11 */
  uint8_t second[2];             /* bytes 12 to 13 */
  uint8_t fractional_second[9];  /* bytes 14 to 22 */
} ActionDatetime;

/* any Action Datetime at all: every byte one the checker chooses */
static void any_action_datetime(ActionDatetime *record) {
  for (size_t i = 0; i < 4; i++) { record->year[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->month[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->day[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->hour[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->minute[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->second[i] = arbitrary(); }
  for (size_t i = 0; i < 9; i++) { record->fractional_second[i] = arbitrary(); }
}

/* Action Datetime to the wire: 23 bytes from at, returning where the next byte goes */
static size_t encode_action_datetime(const ActionDatetime *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->year[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->month[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->day[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->hour[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->minute[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->second[i]; }
  for (size_t i = 0; i < 9; i++) { wire[at++] = record->fractional_second[i]; }

  return at;
}

/* Action Datetime off the wire: 23 bytes from at, returning where the next byte lies */
static size_t decode_action_datetime(ActionDatetime *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->year[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->month[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->day[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->hour[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->minute[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->second[i] = wire[at++]; }
  for (size_t i = 0; i < 9; i++) { record->fractional_second[i] = wire[at++]; }

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
  for (size_t i = 0; i < 9; i++) { assert(read->fractional_second[i] == written->fractional_second[i]); }
}

/* Action Datetime: written and read back, then read and written back */
static void check_action_datetime(void) {
  ActionDatetime sent;
  ActionDatetime got;
  uint8_t wire[23];
  uint8_t again[23];

  any_action_datetime(&sent);
  assert(encode_action_datetime(&sent, wire, 0) == 23);
  assert(decode_action_datetime(&got, wire, 0) == 23);
  equal_action_datetime(&got, &sent);

  for (size_t i = 0; i < 23; i++) { wire[i] = arbitrary(); }
  assert(decode_action_datetime(&got, wire, 0) == 23);
  assert(encode_action_datetime(&got, again, 0) == 23);
  for (size_t i = 0; i < 23; i++) { assert(again[i] == wire[i]); }
}

/* ---- Trading Action Message: 77 bytes ---------------------------------------- */

/* FINRA will disseminate this message to inform customers of trading actions, such as halts or trading resumptions which affect individual OTCBB or Other OTC securities */
typedef struct {
  MessageHeader message_header;           /* bytes 0 to 32 */
  uint8_t security_symbol[14];            /* bytes 33 to 46 */
  uint8_t action;                         /* byte 47 */
  ActionDatetime action_datetime;         /* bytes 48 to 70 */
  uint8_t trading_action_reason_code[6];  /* bytes 71 to 76 */
} TradingActionMessage;

/* any Trading Action Message at all: every byte one the checker chooses */
static void any_trading_action_message(TradingActionMessage *record) {
  any_message_header(&record->message_header);
  for (size_t i = 0; i < 14; i++) { record->security_symbol[i] = arbitrary(); }
  record->action = arbitrary();
  any_action_datetime(&record->action_datetime);
  for (size_t i = 0; i < 6; i++) { record->trading_action_reason_code[i] = arbitrary(); }
}

/* Trading Action Message to the wire: 77 bytes from at, returning where the next byte goes */
static size_t encode_trading_action_message(const TradingActionMessage *record, uint8_t *wire, size_t at) {
  at = encode_message_header(&record->message_header, wire, at);
  for (size_t i = 0; i < 14; i++) { wire[at++] = record->security_symbol[i]; }
  wire[at++] = record->action;
  at = encode_action_datetime(&record->action_datetime, wire, at);
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->trading_action_reason_code[i]; }

  return at;
}

/* Trading Action Message off the wire: 77 bytes from at, returning where the next byte lies */
static size_t decode_trading_action_message(TradingActionMessage *record, const uint8_t *wire, size_t at) {
  at = decode_message_header(&record->message_header, wire, at);
  for (size_t i = 0; i < 14; i++) { record->security_symbol[i] = wire[at++]; }
  record->action = wire[at++];
  at = decode_action_datetime(&record->action_datetime, wire, at);
  for (size_t i = 0; i < 6; i++) { record->trading_action_reason_code[i] = wire[at++]; }

  return at;
}

/* what was read of Trading Action Message is what was written, byte for byte */
static void equal_trading_action_message(const TradingActionMessage *read, const TradingActionMessage *written) {
  equal_message_header(&read->message_header, &written->message_header);
  for (size_t i = 0; i < 14; i++) { assert(read->security_symbol[i] == written->security_symbol[i]); }
  assert(read->action == written->action);
  equal_action_datetime(&read->action_datetime, &written->action_datetime);
  for (size_t i = 0; i < 6; i++) { assert(read->trading_action_reason_code[i] == written->trading_action_reason_code[i]); }
}

/* Trading Action Message: written and read back, then read and written back */
static void check_trading_action_message(void) {
  TradingActionMessage sent;
  TradingActionMessage got;
  uint8_t wire[77];
  uint8_t again[77];

  any_trading_action_message(&sent);
  assert(encode_trading_action_message(&sent, wire, 0) == 77);
  assert(decode_trading_action_message(&got, wire, 0) == 77);
  equal_trading_action_message(&got, &sent);

  for (size_t i = 0; i < 77; i++) { wire[i] = arbitrary(); }
  assert(decode_trading_action_message(&got, wire, 0) == 77);
  assert(encode_trading_action_message(&got, again, 0) == 77);
  for (size_t i = 0; i < 77; i++) { assert(again[i] == wire[i]); }
}

/* ---- Market Wide Circuit Breaker Event Message: 63 bytes --------------------- */

/* FINRA will disseminate this message to inform customers of an extraordinary market event trading action or a market wide circuit breaker event which will affect all security symbols for either OTCBB, Other OTC or both OTCBB and Other OTC market places */
typedef struct {
  MessageHeader message_header;                        /* bytes 0 to 32 */
  uint8_t action;                                      /* byte 33 */
  ActionDatetime action_datetime;                      /* bytes 34 to 56 */
  uint8_t market_wide_circuit_breaker_reason_code[6];  /* bytes 57 to 62 */
} MarketWideCircuitBreakerEventMessage;

/* any Market Wide Circuit Breaker Event Message at all: every byte one the checker chooses */
static void any_market_wide_circuit_breaker_event_message(MarketWideCircuitBreakerEventMessage *record) {
  any_message_header(&record->message_header);
  record->action = arbitrary();
  any_action_datetime(&record->action_datetime);
  for (size_t i = 0; i < 6; i++) { record->market_wide_circuit_breaker_reason_code[i] = arbitrary(); }
}

/* Market Wide Circuit Breaker Event Message to the wire: 63 bytes from at, returning where the next byte goes */
static size_t encode_market_wide_circuit_breaker_event_message(const MarketWideCircuitBreakerEventMessage *record, uint8_t *wire, size_t at) {
  at = encode_message_header(&record->message_header, wire, at);
  wire[at++] = record->action;
  at = encode_action_datetime(&record->action_datetime, wire, at);
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->market_wide_circuit_breaker_reason_code[i]; }

  return at;
}

/* Market Wide Circuit Breaker Event Message off the wire: 63 bytes from at, returning where the next byte lies */
static size_t decode_market_wide_circuit_breaker_event_message(MarketWideCircuitBreakerEventMessage *record, const uint8_t *wire, size_t at) {
  at = decode_message_header(&record->message_header, wire, at);
  record->action = wire[at++];
  at = decode_action_datetime(&record->action_datetime, wire, at);
  for (size_t i = 0; i < 6; i++) { record->market_wide_circuit_breaker_reason_code[i] = wire[at++]; }

  return at;
}

/* what was read of Market Wide Circuit Breaker Event Message is what was written, byte for byte */
static void equal_market_wide_circuit_breaker_event_message(const MarketWideCircuitBreakerEventMessage *read, const MarketWideCircuitBreakerEventMessage *written) {
  equal_message_header(&read->message_header, &written->message_header);
  assert(read->action == written->action);
  equal_action_datetime(&read->action_datetime, &written->action_datetime);
  for (size_t i = 0; i < 6; i++) { assert(read->market_wide_circuit_breaker_reason_code[i] == written->market_wide_circuit_breaker_reason_code[i]); }
}

/* Market Wide Circuit Breaker Event Message: written and read back, then read and written back */
static void check_market_wide_circuit_breaker_event_message(void) {
  MarketWideCircuitBreakerEventMessage sent;
  MarketWideCircuitBreakerEventMessage got;
  uint8_t wire[63];
  uint8_t again[63];

  any_market_wide_circuit_breaker_event_message(&sent);
  assert(encode_market_wide_circuit_breaker_event_message(&sent, wire, 0) == 63);
  assert(decode_market_wide_circuit_breaker_event_message(&got, wire, 0) == 63);
  equal_market_wide_circuit_breaker_event_message(&got, &sent);

  for (size_t i = 0; i < 63; i++) { wire[i] = arbitrary(); }
  assert(decode_market_wide_circuit_breaker_event_message(&got, wire, 0) == 63);
  assert(encode_market_wide_circuit_breaker_event_message(&got, again, 0) == 63);
  for (size_t i = 0; i < 63; i++) { assert(again[i] == wire[i]); }
}

/* ---- Start Of Day Message: 33 bytes ------------------------------------------ */

/* The Start of Day control message signifies the beginning of each operational cycle for TDDS processing */
typedef struct {
  MessageHeader message_header;  /* bytes 0 to 32 */
} StartOfDayMessage;

/* any Start Of Day Message at all: every byte one the checker chooses */
static void any_start_of_day_message(StartOfDayMessage *record) {
  any_message_header(&record->message_header);
}

/* Start Of Day Message to the wire: 33 bytes from at, returning where the next byte goes */
static size_t encode_start_of_day_message(const StartOfDayMessage *record, uint8_t *wire, size_t at) {
  at = encode_message_header(&record->message_header, wire, at);

  return at;
}

/* Start Of Day Message off the wire: 33 bytes from at, returning where the next byte lies */
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
  uint8_t wire[33];
  uint8_t again[33];

  any_start_of_day_message(&sent);
  assert(encode_start_of_day_message(&sent, wire, 0) == 33);
  assert(decode_start_of_day_message(&got, wire, 0) == 33);
  equal_start_of_day_message(&got, &sent);

  for (size_t i = 0; i < 33; i++) { wire[i] = arbitrary(); }
  assert(decode_start_of_day_message(&got, wire, 0) == 33);
  assert(encode_start_of_day_message(&got, again, 0) == 33);
  for (size_t i = 0; i < 33; i++) { assert(again[i] == wire[i]); }
}

/* ---- End Of Day Message: 33 bytes -------------------------------------------- */

/* The End of Day control message signals the end of active message dissemination for the TDDS operational cycle */
typedef struct {
  MessageHeader message_header;  /* bytes 0 to 32 */
} EndOfDayMessage;

/* any End Of Day Message at all: every byte one the checker chooses */
static void any_end_of_day_message(EndOfDayMessage *record) {
  any_message_header(&record->message_header);
}

/* End Of Day Message to the wire: 33 bytes from at, returning where the next byte goes */
static size_t encode_end_of_day_message(const EndOfDayMessage *record, uint8_t *wire, size_t at) {
  at = encode_message_header(&record->message_header, wire, at);

  return at;
}

/* End Of Day Message off the wire: 33 bytes from at, returning where the next byte lies */
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
  uint8_t wire[33];
  uint8_t again[33];

  any_end_of_day_message(&sent);
  assert(encode_end_of_day_message(&sent, wire, 0) == 33);
  assert(decode_end_of_day_message(&got, wire, 0) == 33);
  equal_end_of_day_message(&got, &sent);

  for (size_t i = 0; i < 33; i++) { wire[i] = arbitrary(); }
  assert(decode_end_of_day_message(&got, wire, 0) == 33);
  assert(encode_end_of_day_message(&got, again, 0) == 33);
  for (size_t i = 0; i < 33; i++) { assert(again[i] == wire[i]); }
}

/* ---- Market Session Open Message: 33 bytes ----------------------------------- */

/* The Market Session Open Control Message signifies the opening of FINRA’s market systems for the session indicated in the Message Header */
typedef struct {
  MessageHeader message_header;  /* bytes 0 to 32 */
} MarketSessionOpenMessage;

/* any Market Session Open Message at all: every byte one the checker chooses */
static void any_market_session_open_message(MarketSessionOpenMessage *record) {
  any_message_header(&record->message_header);
}

/* Market Session Open Message to the wire: 33 bytes from at, returning where the next byte goes */
static size_t encode_market_session_open_message(const MarketSessionOpenMessage *record, uint8_t *wire, size_t at) {
  at = encode_message_header(&record->message_header, wire, at);

  return at;
}

/* Market Session Open Message off the wire: 33 bytes from at, returning where the next byte lies */
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
  uint8_t wire[33];
  uint8_t again[33];

  any_market_session_open_message(&sent);
  assert(encode_market_session_open_message(&sent, wire, 0) == 33);
  assert(decode_market_session_open_message(&got, wire, 0) == 33);
  equal_market_session_open_message(&got, &sent);

  for (size_t i = 0; i < 33; i++) { wire[i] = arbitrary(); }
  assert(decode_market_session_open_message(&got, wire, 0) == 33);
  assert(encode_market_session_open_message(&got, again, 0) == 33);
  for (size_t i = 0; i < 33; i++) { assert(again[i] == wire[i]); }
}

/* ---- Market Session Close Message: 33 bytes ---------------------------------- */

/* The Session Close Control Message signals the closing of FINRA’s market systems for the session indicated in the Message Header */
typedef struct {
  MessageHeader message_header;  /* bytes 0 to 32 */
} MarketSessionCloseMessage;

/* any Market Session Close Message at all: every byte one the checker chooses */
static void any_market_session_close_message(MarketSessionCloseMessage *record) {
  any_message_header(&record->message_header);
}

/* Market Session Close Message to the wire: 33 bytes from at, returning where the next byte goes */
static size_t encode_market_session_close_message(const MarketSessionCloseMessage *record, uint8_t *wire, size_t at) {
  at = encode_message_header(&record->message_header, wire, at);

  return at;
}

/* Market Session Close Message off the wire: 33 bytes from at, returning where the next byte lies */
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
  uint8_t wire[33];
  uint8_t again[33];

  any_market_session_close_message(&sent);
  assert(encode_market_session_close_message(&sent, wire, 0) == 33);
  assert(decode_market_session_close_message(&got, wire, 0) == 33);
  equal_market_session_close_message(&got, &sent);

  for (size_t i = 0; i < 33; i++) { wire[i] = arbitrary(); }
  assert(decode_market_session_close_message(&got, wire, 0) == 33);
  assert(encode_market_session_close_message(&got, again, 0) == 33);
  for (size_t i = 0; i < 33; i++) { assert(again[i] == wire[i]); }
}

/* ---- End Of Retransmission Requests Message: 33 bytes ------------------------ */

/* This message signals that no further retransmission requests will be honored. The End of Retransmission Requests message will be sent three times, at one-minute intervals */
typedef struct {
  MessageHeader message_header;  /* bytes 0 to 32 */
} EndOfRetransmissionRequestsMessage;

/* any End Of Retransmission Requests Message at all: every byte one the checker chooses */
static void any_end_of_retransmission_requests_message(EndOfRetransmissionRequestsMessage *record) {
  any_message_header(&record->message_header);
}

/* End Of Retransmission Requests Message to the wire: 33 bytes from at, returning where the next byte goes */
static size_t encode_end_of_retransmission_requests_message(const EndOfRetransmissionRequestsMessage *record, uint8_t *wire, size_t at) {
  at = encode_message_header(&record->message_header, wire, at);

  return at;
}

/* End Of Retransmission Requests Message off the wire: 33 bytes from at, returning where the next byte lies */
static size_t decode_end_of_retransmission_requests_message(EndOfRetransmissionRequestsMessage *record, const uint8_t *wire, size_t at) {
  at = decode_message_header(&record->message_header, wire, at);

  return at;
}

/* what was read of End Of Retransmission Requests Message is what was written, byte for byte */
static void equal_end_of_retransmission_requests_message(const EndOfRetransmissionRequestsMessage *read, const EndOfRetransmissionRequestsMessage *written) {
  equal_message_header(&read->message_header, &written->message_header);
}

/* End Of Retransmission Requests Message: written and read back, then read and written back */
static void check_end_of_retransmission_requests_message(void) {
  EndOfRetransmissionRequestsMessage sent;
  EndOfRetransmissionRequestsMessage got;
  uint8_t wire[33];
  uint8_t again[33];

  any_end_of_retransmission_requests_message(&sent);
  assert(encode_end_of_retransmission_requests_message(&sent, wire, 0) == 33);
  assert(decode_end_of_retransmission_requests_message(&got, wire, 0) == 33);
  equal_end_of_retransmission_requests_message(&got, &sent);

  for (size_t i = 0; i < 33; i++) { wire[i] = arbitrary(); }
  assert(decode_end_of_retransmission_requests_message(&got, wire, 0) == 33);
  assert(encode_end_of_retransmission_requests_message(&got, again, 0) == 33);
  for (size_t i = 0; i < 33; i++) { assert(again[i] == wire[i]); }
}

/* ---- End Of Transmissions Message: 33 bytes ---------------------------------- */

/* The End of Transmissions Message signals that there will be no further transmissions of data sent through the TDDS line. */
typedef struct {
  MessageHeader message_header;  /* bytes 0 to 32 */
} EndOfTransmissionsMessage;

/* any End Of Transmissions Message at all: every byte one the checker chooses */
static void any_end_of_transmissions_message(EndOfTransmissionsMessage *record) {
  any_message_header(&record->message_header);
}

/* End Of Transmissions Message to the wire: 33 bytes from at, returning where the next byte goes */
static size_t encode_end_of_transmissions_message(const EndOfTransmissionsMessage *record, uint8_t *wire, size_t at) {
  at = encode_message_header(&record->message_header, wire, at);

  return at;
}

/* End Of Transmissions Message off the wire: 33 bytes from at, returning where the next byte lies */
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
  uint8_t wire[33];
  uint8_t again[33];

  any_end_of_transmissions_message(&sent);
  assert(encode_end_of_transmissions_message(&sent, wire, 0) == 33);
  assert(decode_end_of_transmissions_message(&got, wire, 0) == 33);
  equal_end_of_transmissions_message(&got, &sent);

  for (size_t i = 0; i < 33; i++) { wire[i] = arbitrary(); }
  assert(decode_end_of_transmissions_message(&got, wire, 0) == 33);
  assert(encode_end_of_transmissions_message(&got, again, 0) == 33);
  for (size_t i = 0; i < 33; i++) { assert(again[i] == wire[i]); }
}

/* ---- Line Integrity Message: 33 bytes ---------------------------------------- */

/* The Line Integrity Control Message will be transmitted at approximately one-minute intervals to verify the operational integrity of the TDDS message transmission, and will be intermixed with other messages */
typedef struct {
  MessageHeader message_header;  /* bytes 0 to 32 */
} LineIntegrityMessage;

/* any Line Integrity Message at all: every byte one the checker chooses */
static void any_line_integrity_message(LineIntegrityMessage *record) {
  any_message_header(&record->message_header);
}

/* Line Integrity Message to the wire: 33 bytes from at, returning where the next byte goes */
static size_t encode_line_integrity_message(const LineIntegrityMessage *record, uint8_t *wire, size_t at) {
  at = encode_message_header(&record->message_header, wire, at);

  return at;
}

/* Line Integrity Message off the wire: 33 bytes from at, returning where the next byte lies */
static size_t decode_line_integrity_message(LineIntegrityMessage *record, const uint8_t *wire, size_t at) {
  at = decode_message_header(&record->message_header, wire, at);

  return at;
}

/* what was read of Line Integrity Message is what was written, byte for byte */
static void equal_line_integrity_message(const LineIntegrityMessage *read, const LineIntegrityMessage *written) {
  equal_message_header(&read->message_header, &written->message_header);
}

/* Line Integrity Message: written and read back, then read and written back */
static void check_line_integrity_message(void) {
  LineIntegrityMessage sent;
  LineIntegrityMessage got;
  uint8_t wire[33];
  uint8_t again[33];

  any_line_integrity_message(&sent);
  assert(encode_line_integrity_message(&sent, wire, 0) == 33);
  assert(decode_line_integrity_message(&got, wire, 0) == 33);
  equal_line_integrity_message(&got, &sent);

  for (size_t i = 0; i < 33; i++) { wire[i] = arbitrary(); }
  assert(decode_line_integrity_message(&got, wire, 0) == 33);
  assert(encode_line_integrity_message(&got, again, 0) == 33);
  for (size_t i = 0; i < 33; i++) { assert(again[i] == wire[i]); }
}

/* ---- Sequence Number Reset Message: 33 bytes --------------------------------- */

/* The Sequence Number Reset Message forces the resetting of the Sequence Number. The Sequence Number will either be reset to zero or to a number greater than the last number previously transmitted */
typedef struct {
  MessageHeader message_header;  /* bytes 0 to 32 */
} SequenceNumberResetMessage;

/* any Sequence Number Reset Message at all: every byte one the checker chooses */
static void any_sequence_number_reset_message(SequenceNumberResetMessage *record) {
  any_message_header(&record->message_header);
}

/* Sequence Number Reset Message to the wire: 33 bytes from at, returning where the next byte goes */
static size_t encode_sequence_number_reset_message(const SequenceNumberResetMessage *record, uint8_t *wire, size_t at) {
  at = encode_message_header(&record->message_header, wire, at);

  return at;
}

/* Sequence Number Reset Message off the wire: 33 bytes from at, returning where the next byte lies */
static size_t decode_sequence_number_reset_message(SequenceNumberResetMessage *record, const uint8_t *wire, size_t at) {
  at = decode_message_header(&record->message_header, wire, at);

  return at;
}

/* what was read of Sequence Number Reset Message is what was written, byte for byte */
static void equal_sequence_number_reset_message(const SequenceNumberResetMessage *read, const SequenceNumberResetMessage *written) {
  equal_message_header(&read->message_header, &written->message_header);
}

/* Sequence Number Reset Message: written and read back, then read and written back */
static void check_sequence_number_reset_message(void) {
  SequenceNumberResetMessage sent;
  SequenceNumberResetMessage got;
  uint8_t wire[33];
  uint8_t again[33];

  any_sequence_number_reset_message(&sent);
  assert(encode_sequence_number_reset_message(&sent, wire, 0) == 33);
  assert(decode_sequence_number_reset_message(&got, wire, 0) == 33);
  equal_sequence_number_reset_message(&got, &sent);

  for (size_t i = 0; i < 33; i++) { wire[i] = arbitrary(); }
  assert(decode_sequence_number_reset_message(&got, wire, 0) == 33);
  assert(encode_sequence_number_reset_message(&got, again, 0) == 33);
  for (size_t i = 0; i < 33; i++) { assert(again[i] == wire[i]); }
}

/* ---- End Of Trade Reporting Message: 33 bytes -------------------------------- */

/* The End of Trade Reporting Control Message signals that the ORF system is closed for market participant trade transactions */
typedef struct {
  MessageHeader message_header;  /* bytes 0 to 32 */
} EndOfTradeReportingMessage;

/* any End Of Trade Reporting Message at all: every byte one the checker chooses */
static void any_end_of_trade_reporting_message(EndOfTradeReportingMessage *record) {
  any_message_header(&record->message_header);
}

/* End Of Trade Reporting Message to the wire: 33 bytes from at, returning where the next byte goes */
static size_t encode_end_of_trade_reporting_message(const EndOfTradeReportingMessage *record, uint8_t *wire, size_t at) {
  at = encode_message_header(&record->message_header, wire, at);

  return at;
}

/* End Of Trade Reporting Message off the wire: 33 bytes from at, returning where the next byte lies */
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
  uint8_t wire[33];
  uint8_t again[33];

  any_end_of_trade_reporting_message(&sent);
  assert(encode_end_of_trade_reporting_message(&sent, wire, 0) == 33);
  assert(decode_end_of_trade_reporting_message(&got, wire, 0) == 33);
  equal_end_of_trade_reporting_message(&got, &sent);

  for (size_t i = 0; i < 33; i++) { wire[i] = arbitrary(); }
  assert(decode_end_of_trade_reporting_message(&got, wire, 0) == 33);
  assert(encode_end_of_trade_reporting_message(&got, again, 0) == 33);
  for (size_t i = 0; i < 33; i++) { assert(again[i] == wire[i]); }
}

/* ---- What esbmc checks ------------------------------------------------------- */

/* every record of the protocol, each on its own buffers */
static void checks(void) {
  check_packet_header();
  check_mold_udp64();
  check_datetime();
  check_message_header();
  check_trade_report_short_form_message();
  check_original_dissemination_date();
  check_execution_datetime();
  check_trade_information();
  check_trade_report_long_form_message();
  check_original_trade_information();
  check_trade_summary_information();
  check_trade_cancel_error_message();
  check_corrected_trade_information();
  check_trade_correction_message();
  check_closing_trade_summary_report_message();
  check_action_datetime();
  check_trading_action_message();
  check_market_wide_circuit_breaker_event_message();
  check_start_of_day_message();
  check_end_of_day_message();
  check_market_session_open_message();
  check_market_session_close_message();
  check_end_of_retransmission_requests_message();
  check_end_of_transmissions_message();
  check_line_integrity_message();
  check_sequence_number_reset_message();
  check_end_of_trade_reporting_message();
}

int main(void) {
#ifdef CONCRETE
  for (pattern = 0; pattern < 4; pattern++) { checks(); }
#else
  checks();
#endif

  return 0;
}
