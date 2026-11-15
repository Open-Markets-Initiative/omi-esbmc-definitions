// finra/finraorf/tdds/FinraOrf_Tdds_v2_0.c
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
 *   - a run filling what frames it
 *   - the dispatch that chooses a message by its type
 *   - a field ended by the first of several bytes it does not carry
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

/* ---- Datetime: 17 bytes ------------------------------------------------------ */

/* Datetime */
typedef struct {
  uint8_t year[4];         /* bytes 0 to 3 */
  uint8_t month[2];        /* bytes 4 to 5 */
  uint8_t day[2];          /* bytes 6 to 7 */
  uint8_t hour[2];         /* bytes 8 to 9 */
  uint8_t minute[2];       /* bytes 10 to 11 */
  uint8_t second[2];       /* bytes 12 to 13 */
  uint8_t millisecond[3];  /* bytes 14 to 16 */
} Datetime;

/* any Datetime at all: every byte one the checker chooses */
static void any_datetime(Datetime *record) {
  for (size_t i = 0; i < 4; i++) { record->year[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->month[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->day[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->hour[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->minute[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->second[i] = arbitrary(); }
  for (size_t i = 0; i < 3; i++) { record->millisecond[i] = arbitrary(); }
}

/* Datetime to the wire: 17 bytes from at, returning where the next byte goes */
static size_t encode_datetime(const Datetime *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->year[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->month[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->day[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->hour[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->minute[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->second[i]; }
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->millisecond[i]; }

  return at;
}

/* Datetime off the wire: 17 bytes from at, returning where the next byte lies */
static size_t decode_datetime(Datetime *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->year[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->month[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->day[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->hour[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->minute[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->second[i] = wire[at++]; }
  for (size_t i = 0; i < 3; i++) { record->millisecond[i] = wire[at++]; }

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
  for (size_t i = 0; i < 3; i++) { assert(read->millisecond[i] == written->millisecond[i]); }
}

/* Datetime: written and read back, then read and written back */
static void check_datetime(void) {
  Datetime sent;
  Datetime got;
  uint8_t wire[17];
  uint8_t again[17];

  any_datetime(&sent);
  assert(encode_datetime(&sent, wire, 0) == 17);
  assert(decode_datetime(&got, wire, 0) == 17);
  equal_datetime(&got, &sent);

  for (size_t i = 0; i < 17; i++) { wire[i] = arbitrary(); }
  assert(decode_datetime(&got, wire, 0) == 17);
  assert(encode_datetime(&got, again, 0) == 17);
  for (size_t i = 0; i < 17; i++) { assert(again[i] == wire[i]); }
}

/* ---- Message Header: 30 bytes ------------------------------------------------ */

/* Message Header */
typedef struct {
  uint8_t session_identifier;              /* byte 0 */
  uint8_t retransmission_requester[2];     /* bytes 1 to 2 */
  uint8_t message_sequence_number[8];      /* bytes 3 to 10 */
  uint8_t market_center_originator_id[2];  /* bytes 11 to 12 */
  Datetime datetime;                       /* bytes 13 to 29 */
} MessageHeader;

/* any Message Header at all: every byte one the checker chooses */
static void any_message_header(MessageHeader *record) {
  record->session_identifier = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->retransmission_requester[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->message_sequence_number[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->market_center_originator_id[i] = arbitrary(); }
  any_datetime(&record->datetime);
}

/* Message Header to the wire: 30 bytes from at, returning where the next byte goes */
static size_t encode_message_header(const MessageHeader *record, uint8_t *wire, size_t at) {
  wire[at++] = record->session_identifier;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->retransmission_requester[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->message_sequence_number[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->market_center_originator_id[i]; }
  at = encode_datetime(&record->datetime, wire, at);

  return at;
}

/* Message Header off the wire: 30 bytes from at, returning where the next byte lies */
static size_t decode_message_header(MessageHeader *record, const uint8_t *wire, size_t at) {
  record->session_identifier = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->retransmission_requester[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->message_sequence_number[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->market_center_originator_id[i] = wire[at++]; }
  at = decode_datetime(&record->datetime, wire, at);

  return at;
}

/* what was read of Message Header is what was written, byte for byte */
static void equal_message_header(const MessageHeader *read, const MessageHeader *written) {
  assert(read->session_identifier == written->session_identifier);
  for (size_t i = 0; i < 2; i++) { assert(read->retransmission_requester[i] == written->retransmission_requester[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->message_sequence_number[i] == written->message_sequence_number[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->market_center_originator_id[i] == written->market_center_originator_id[i]); }
  equal_datetime(&read->datetime, &written->datetime);
}

/* Message Header: written and read back, then read and written back */
static void check_message_header(void) {
  MessageHeader sent;
  MessageHeader got;
  uint8_t wire[30];
  uint8_t again[30];

  any_message_header(&sent);
  assert(encode_message_header(&sent, wire, 0) == 30);
  assert(decode_message_header(&got, wire, 0) == 30);
  equal_message_header(&got, &sent);

  for (size_t i = 0; i < 30; i++) { wire[i] = arbitrary(); }
  assert(decode_message_header(&got, wire, 0) == 30);
  assert(encode_message_header(&got, again, 0) == 30);
  for (size_t i = 0; i < 30; i++) { assert(again[i] == wire[i]); }
}

/* ---- Trade Report Short Form Message: 50 bytes ------------------------------- */

/* Economized trade report */
typedef struct {
  MessageHeader message_header;      /* bytes 0 to 29 */
  uint8_t security_symbol_short[5];  /* bytes 30 to 34 */
  uint8_t sale_condition_level_1;    /* byte 35 */
  uint8_t trade_price_denominator;   /* byte 36 */
  uint8_t trade_price_short[6];      /* bytes 37 to 42 */
  uint8_t report_volume_short[6];    /* bytes 43 to 48 */
  uint8_t price_change_indicator;    /* byte 49 */
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

/* Trade Report Short Form Message to the wire: 50 bytes from at, returning where the next byte goes */
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

/* Trade Report Short Form Message off the wire: 50 bytes from at, returning where the next byte lies */
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
  uint8_t wire[50];
  uint8_t again[50];

  any_trade_report_short_form_message(&sent);
  assert(encode_trade_report_short_form_message(&sent, wire, 0) == 50);
  assert(decode_trade_report_short_form_message(&got, wire, 0) == 50);
  equal_trade_report_short_form_message(&got, &sent);

  for (size_t i = 0; i < 50; i++) { wire[i] = arbitrary(); }
  assert(decode_trade_report_short_form_message(&got, wire, 0) == 50);
  assert(encode_trade_report_short_form_message(&got, again, 0) == 50);
  for (size_t i = 0; i < 50; i++) { assert(again[i] == wire[i]); }
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

/* ---- Execution Datetime: 17 bytes -------------------------------------------- */

/* Execution Datetime */
typedef struct {
  uint8_t year[4];         /* bytes 0 to 3 */
  uint8_t month[2];        /* bytes 4 to 5 */
  uint8_t day[2];          /* bytes 6 to 7 */
  uint8_t hour[2];         /* bytes 8 to 9 */
  uint8_t minute[2];       /* bytes 10 to 11 */
  uint8_t second[2];       /* bytes 12 to 13 */
  uint8_t millisecond[3];  /* bytes 14 to 16 */
} ExecutionDatetime;

/* any Execution Datetime at all: every byte one the checker chooses */
static void any_execution_datetime(ExecutionDatetime *record) {
  for (size_t i = 0; i < 4; i++) { record->year[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->month[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->day[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->hour[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->minute[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->second[i] = arbitrary(); }
  for (size_t i = 0; i < 3; i++) { record->millisecond[i] = arbitrary(); }
}

/* Execution Datetime to the wire: 17 bytes from at, returning where the next byte goes */
static size_t encode_execution_datetime(const ExecutionDatetime *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->year[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->month[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->day[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->hour[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->minute[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->second[i]; }
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->millisecond[i]; }

  return at;
}

/* Execution Datetime off the wire: 17 bytes from at, returning where the next byte lies */
static size_t decode_execution_datetime(ExecutionDatetime *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->year[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->month[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->day[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->hour[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->minute[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->second[i] = wire[at++]; }
  for (size_t i = 0; i < 3; i++) { record->millisecond[i] = wire[at++]; }

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
  for (size_t i = 0; i < 3; i++) { assert(read->millisecond[i] == written->millisecond[i]); }
}

/* Execution Datetime: written and read back, then read and written back */
static void check_execution_datetime(void) {
  ExecutionDatetime sent;
  ExecutionDatetime got;
  uint8_t wire[17];
  uint8_t again[17];

  any_execution_datetime(&sent);
  assert(encode_execution_datetime(&sent, wire, 0) == 17);
  assert(decode_execution_datetime(&got, wire, 0) == 17);
  equal_execution_datetime(&got, &sent);

  for (size_t i = 0; i < 17; i++) { wire[i] = arbitrary(); }
  assert(decode_execution_datetime(&got, wire, 0) == 17);
  assert(encode_execution_datetime(&got, again, 0) == 17);
  for (size_t i = 0; i < 17; i++) { assert(again[i] == wire[i]); }
}

/* ---- Trade Information: 49 bytes --------------------------------------------- */

/* Trade Information */
typedef struct {
  uint8_t report_volume[8];              /* bytes 0 to 7 */
  uint8_t trade_price_denominator;       /* byte 8 */
  uint8_t trade_price[12];               /* bytes 9 to 20 */
  uint8_t currency[3];                   /* bytes 21 to 23 */
  uint8_t as_of_indicator;               /* byte 24 */
  ExecutionDatetime execution_datetime;  /* bytes 25 to 41 */
  uint8_t sale_condition_level_1;        /* byte 42 */
  uint8_t sale_condition_level_2;        /* byte 43 */
  uint8_t sale_condition_level_3;        /* byte 44 */
  uint8_t sale_condition_level_4;        /* byte 45 */
  uint8_t sellers_sale_days[2];          /* bytes 46 to 47 */
  uint8_t price_change_indicator;        /* byte 48 */
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

/* Trade Information to the wire: 49 bytes from at, returning where the next byte goes */
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

/* Trade Information off the wire: 49 bytes from at, returning where the next byte lies */
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
  uint8_t wire[49];
  uint8_t again[49];

  any_trade_information(&sent);
  assert(encode_trade_information(&sent, wire, 0) == 49);
  assert(decode_trade_information(&got, wire, 0) == 49);
  equal_trade_information(&got, &sent);

  for (size_t i = 0; i < 49; i++) { wire[i] = arbitrary(); }
  assert(decode_trade_information(&got, wire, 0) == 49);
  assert(encode_trade_information(&got, again, 0) == 49);
  for (size_t i = 0; i < 49; i++) { assert(again[i] == wire[i]); }
}

/* ---- Trade Report Long Form Message: 101 bytes ------------------------------- */

/* Complete trade report */
typedef struct {
  MessageHeader message_header;                           /* bytes 0 to 29 */
  uint8_t security_symbol[14];                            /* bytes 30 to 43 */
  OriginalDisseminationDate original_dissemination_date;  /* bytes 44 to 51 */
  TradeInformation trade_information;                     /* bytes 52 to 100 */
} TradeReportLongFormMessage;

/* any Trade Report Long Form Message at all: every byte one the checker chooses */
static void any_trade_report_long_form_message(TradeReportLongFormMessage *record) {
  any_message_header(&record->message_header);
  for (size_t i = 0; i < 14; i++) { record->security_symbol[i] = arbitrary(); }
  any_original_dissemination_date(&record->original_dissemination_date);
  any_trade_information(&record->trade_information);
}

/* Trade Report Long Form Message to the wire: 101 bytes from at, returning where the next byte goes */
static size_t encode_trade_report_long_form_message(const TradeReportLongFormMessage *record, uint8_t *wire, size_t at) {
  at = encode_message_header(&record->message_header, wire, at);
  for (size_t i = 0; i < 14; i++) { wire[at++] = record->security_symbol[i]; }
  at = encode_original_dissemination_date(&record->original_dissemination_date, wire, at);
  at = encode_trade_information(&record->trade_information, wire, at);

  return at;
}

/* Trade Report Long Form Message off the wire: 101 bytes from at, returning where the next byte lies */
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
  uint8_t wire[101];
  uint8_t again[101];

  any_trade_report_long_form_message(&sent);
  assert(encode_trade_report_long_form_message(&sent, wire, 0) == 101);
  assert(decode_trade_report_long_form_message(&got, wire, 0) == 101);
  equal_trade_report_long_form_message(&got, &sent);

  for (size_t i = 0; i < 101; i++) { wire[i] = arbitrary(); }
  assert(decode_trade_report_long_form_message(&got, wire, 0) == 101);
  assert(encode_trade_report_long_form_message(&got, again, 0) == 101);
  for (size_t i = 0; i < 101; i++) { assert(again[i] == wire[i]); }
}

/* ---- Original Trade Information: 48 bytes ------------------------------------ */

/* Original Trade Information */
typedef struct {
  uint8_t report_volume[8];              /* bytes 0 to 7 */
  uint8_t trade_price_denominator;       /* byte 8 */
  uint8_t trade_price[12];               /* bytes 9 to 20 */
  uint8_t currency[3];                   /* bytes 21 to 23 */
  uint8_t as_of_indicator;               /* byte 24 */
  ExecutionDatetime execution_datetime;  /* bytes 25 to 41 */
  uint8_t sale_condition_level_1;        /* byte 42 */
  uint8_t sale_condition_level_2;        /* byte 43 */
  uint8_t sale_condition_level_3;        /* byte 44 */
  uint8_t sale_condition_level_4;        /* byte 45 */
  uint8_t sellers_sale_days[2];          /* bytes 46 to 47 */
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

/* Original Trade Information to the wire: 48 bytes from at, returning where the next byte goes */
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

/* Original Trade Information off the wire: 48 bytes from at, returning where the next byte lies */
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
  uint8_t wire[48];
  uint8_t again[48];

  any_original_trade_information(&sent);
  assert(encode_original_trade_information(&sent, wire, 0) == 48);
  assert(decode_original_trade_information(&got, wire, 0) == 48);
  equal_original_trade_information(&got, &sent);

  for (size_t i = 0; i < 48; i++) { wire[i] = arbitrary(); }
  assert(decode_original_trade_information(&got, wire, 0) == 48);
  assert(encode_original_trade_information(&got, again, 0) == 48);
  for (size_t i = 0; i < 48; i++) { assert(again[i] == wire[i]); }
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

/* ---- Trade Cancel Error Message: 161 bytes ----------------------------------- */

/* This message is used to notify TDDS customers if a trade report entered during the current business day, or up to the past three business days, has been canceled */
typedef struct {
  MessageHeader message_header;                           /* bytes 0 to 29 */
  uint8_t security_symbol[14];                            /* bytes 30 to 43 */
  OriginalDisseminationDate original_dissemination_date;  /* bytes 44 to 51 */
  uint8_t original_message_sequence_number[8];            /* bytes 52 to 59 */
  uint8_t report_function;                                /* byte 60 */
  OriginalTradeInformation original_trade_information;    /* bytes 61 to 108 */
  TradeSummaryInformation trade_summary_information;      /* bytes 109 to 160 */
} TradeCancelErrorMessage;

/* any Trade Cancel Error Message at all: every byte one the checker chooses */
static void any_trade_cancel_error_message(TradeCancelErrorMessage *record) {
  any_message_header(&record->message_header);
  for (size_t i = 0; i < 14; i++) { record->security_symbol[i] = arbitrary(); }
  any_original_dissemination_date(&record->original_dissemination_date);
  for (size_t i = 0; i < 8; i++) { record->original_message_sequence_number[i] = arbitrary(); }
  record->report_function = arbitrary();
  any_original_trade_information(&record->original_trade_information);
  any_trade_summary_information(&record->trade_summary_information);
}

/* Trade Cancel Error Message to the wire: 161 bytes from at, returning where the next byte goes */
static size_t encode_trade_cancel_error_message(const TradeCancelErrorMessage *record, uint8_t *wire, size_t at) {
  at = encode_message_header(&record->message_header, wire, at);
  for (size_t i = 0; i < 14; i++) { wire[at++] = record->security_symbol[i]; }
  at = encode_original_dissemination_date(&record->original_dissemination_date, wire, at);
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->original_message_sequence_number[i]; }
  wire[at++] = record->report_function;
  at = encode_original_trade_information(&record->original_trade_information, wire, at);
  at = encode_trade_summary_information(&record->trade_summary_information, wire, at);

  return at;
}

/* Trade Cancel Error Message off the wire: 161 bytes from at, returning where the next byte lies */
static size_t decode_trade_cancel_error_message(TradeCancelErrorMessage *record, const uint8_t *wire, size_t at) {
  at = decode_message_header(&record->message_header, wire, at);
  for (size_t i = 0; i < 14; i++) { record->security_symbol[i] = wire[at++]; }
  at = decode_original_dissemination_date(&record->original_dissemination_date, wire, at);
  for (size_t i = 0; i < 8; i++) { record->original_message_sequence_number[i] = wire[at++]; }
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
  for (size_t i = 0; i < 8; i++) { assert(read->original_message_sequence_number[i] == written->original_message_sequence_number[i]); }
  assert(read->report_function == written->report_function);
  equal_original_trade_information(&read->original_trade_information, &written->original_trade_information);
  equal_trade_summary_information(&read->trade_summary_information, &written->trade_summary_information);
}

/* Trade Cancel Error Message: written and read back, then read and written back */
static void check_trade_cancel_error_message(void) {
  TradeCancelErrorMessage sent;
  TradeCancelErrorMessage got;
  uint8_t wire[161];
  uint8_t again[161];

  any_trade_cancel_error_message(&sent);
  assert(encode_trade_cancel_error_message(&sent, wire, 0) == 161);
  assert(decode_trade_cancel_error_message(&got, wire, 0) == 161);
  equal_trade_cancel_error_message(&got, &sent);

  for (size_t i = 0; i < 161; i++) { wire[i] = arbitrary(); }
  assert(decode_trade_cancel_error_message(&got, wire, 0) == 161);
  assert(encode_trade_cancel_error_message(&got, again, 0) == 161);
  for (size_t i = 0; i < 161; i++) { assert(again[i] == wire[i]); }
}

/* ---- Corrected Trade Information: 48 bytes ----------------------------------- */

/* Corrected Trade Information */
typedef struct {
  uint8_t report_volume[8];              /* bytes 0 to 7 */
  uint8_t trade_price_denominator;       /* byte 8 */
  uint8_t trade_price[12];               /* bytes 9 to 20 */
  uint8_t currency[3];                   /* bytes 21 to 23 */
  uint8_t as_of_indicator;               /* byte 24 */
  ExecutionDatetime execution_datetime;  /* bytes 25 to 41 */
  uint8_t sale_condition_level_1;        /* byte 42 */
  uint8_t sale_condition_level_2;        /* byte 43 */
  uint8_t sale_condition_level_3;        /* byte 44 */
  uint8_t sale_condition_level_4;        /* byte 45 */
  uint8_t sellers_sale_days[2];          /* bytes 46 to 47 */
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

/* Corrected Trade Information to the wire: 48 bytes from at, returning where the next byte goes */
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

/* Corrected Trade Information off the wire: 48 bytes from at, returning where the next byte lies */
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
  uint8_t wire[48];
  uint8_t again[48];

  any_corrected_trade_information(&sent);
  assert(encode_corrected_trade_information(&sent, wire, 0) == 48);
  assert(decode_corrected_trade_information(&got, wire, 0) == 48);
  equal_corrected_trade_information(&got, &sent);

  for (size_t i = 0; i < 48; i++) { wire[i] = arbitrary(); }
  assert(decode_corrected_trade_information(&got, wire, 0) == 48);
  assert(encode_corrected_trade_information(&got, again, 0) == 48);
  for (size_t i = 0; i < 48; i++) { assert(again[i] == wire[i]); }
}

/* ---- Trade Correction Message: 209 bytes ------------------------------------- */

/* Used to notify TDDS customers if a trade report entered during the current business day, or up to the past three business days, has been modified */
typedef struct {
  MessageHeader message_header;                           /* bytes 0 to 29 */
  uint8_t security_symbol[14];                            /* bytes 30 to 43 */
  OriginalDisseminationDate original_dissemination_date;  /* bytes 44 to 51 */
  uint8_t original_message_sequence_number[8];            /* bytes 52 to 59 */
  uint8_t report_function;                                /* byte 60 */
  OriginalTradeInformation original_trade_information;    /* bytes 61 to 108 */
  CorrectedTradeInformation corrected_trade_information;  /* bytes 109 to 156 */
  TradeSummaryInformation trade_summary_information;      /* bytes 157 to 208 */
} TradeCorrectionMessage;

/* any Trade Correction Message at all: every byte one the checker chooses */
static void any_trade_correction_message(TradeCorrectionMessage *record) {
  any_message_header(&record->message_header);
  for (size_t i = 0; i < 14; i++) { record->security_symbol[i] = arbitrary(); }
  any_original_dissemination_date(&record->original_dissemination_date);
  for (size_t i = 0; i < 8; i++) { record->original_message_sequence_number[i] = arbitrary(); }
  record->report_function = arbitrary();
  any_original_trade_information(&record->original_trade_information);
  any_corrected_trade_information(&record->corrected_trade_information);
  any_trade_summary_information(&record->trade_summary_information);
}

/* Trade Correction Message to the wire: 209 bytes from at, returning where the next byte goes */
static size_t encode_trade_correction_message(const TradeCorrectionMessage *record, uint8_t *wire, size_t at) {
  at = encode_message_header(&record->message_header, wire, at);
  for (size_t i = 0; i < 14; i++) { wire[at++] = record->security_symbol[i]; }
  at = encode_original_dissemination_date(&record->original_dissemination_date, wire, at);
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->original_message_sequence_number[i]; }
  wire[at++] = record->report_function;
  at = encode_original_trade_information(&record->original_trade_information, wire, at);
  at = encode_corrected_trade_information(&record->corrected_trade_information, wire, at);
  at = encode_trade_summary_information(&record->trade_summary_information, wire, at);

  return at;
}

/* Trade Correction Message off the wire: 209 bytes from at, returning where the next byte lies */
static size_t decode_trade_correction_message(TradeCorrectionMessage *record, const uint8_t *wire, size_t at) {
  at = decode_message_header(&record->message_header, wire, at);
  for (size_t i = 0; i < 14; i++) { record->security_symbol[i] = wire[at++]; }
  at = decode_original_dissemination_date(&record->original_dissemination_date, wire, at);
  for (size_t i = 0; i < 8; i++) { record->original_message_sequence_number[i] = wire[at++]; }
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
  for (size_t i = 0; i < 8; i++) { assert(read->original_message_sequence_number[i] == written->original_message_sequence_number[i]); }
  assert(read->report_function == written->report_function);
  equal_original_trade_information(&read->original_trade_information, &written->original_trade_information);
  equal_corrected_trade_information(&read->corrected_trade_information, &written->corrected_trade_information);
  equal_trade_summary_information(&read->trade_summary_information, &written->trade_summary_information);
}

/* Trade Correction Message: written and read back, then read and written back */
static void check_trade_correction_message(void) {
  TradeCorrectionMessage sent;
  TradeCorrectionMessage got;
  uint8_t wire[209];
  uint8_t again[209];

  any_trade_correction_message(&sent);
  assert(encode_trade_correction_message(&sent, wire, 0) == 209);
  assert(decode_trade_correction_message(&got, wire, 0) == 209);
  equal_trade_correction_message(&got, &sent);

  for (size_t i = 0; i < 209; i++) { wire[i] = arbitrary(); }
  assert(decode_trade_correction_message(&got, wire, 0) == 209);
  assert(encode_trade_correction_message(&got, again, 0) == 209);
  for (size_t i = 0; i < 209; i++) { assert(again[i] == wire[i]); }
}

/* ---- Closing Trade Summary Report Message: 113 bytes ------------------------- */

/* The closing trade summary will reflect the daily high, low, and closing prices as well as the total volume for the security */
typedef struct {
  MessageHeader message_header;          /* bytes 0 to 29 */
  uint8_t security_symbol[14];           /* bytes 30 to 43 */
  uint8_t daily_high_price_denominator;  /* byte 44 */
  uint8_t daily_high_price[12];          /* bytes 45 to 56 */
  uint8_t daily_low_price_denominator;   /* byte 57 */
  uint8_t daily_low_price[12];           /* bytes 58 to 69 */
  uint8_t closing_price_market_center;   /* byte 70 */
  uint8_t closing_price_denominator;     /* byte 71 */
  uint8_t closing_price[12];             /* bytes 72 to 83 */
  uint8_t reserved_1;                    /* byte 84 */
  uint8_t net_change_denominator;        /* byte 85 */
  uint8_t net_change_amount[12];         /* bytes 86 to 97 */
  uint8_t net_change_direction;          /* byte 98 */
  uint8_t currency[3];                   /* bytes 99 to 101 */
  uint8_t total_security_volume[11];     /* bytes 102 to 112 */
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
  for (size_t i = 0; i < 12; i++) { record->net_change_amount[i] = arbitrary(); }
  record->net_change_direction = arbitrary();
  for (size_t i = 0; i < 3; i++) { record->currency[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->total_security_volume[i] = arbitrary(); }
}

/* Closing Trade Summary Report Message to the wire: 113 bytes from at, returning where the next byte goes */
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
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->net_change_amount[i]; }
  wire[at++] = record->net_change_direction;
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->currency[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->total_security_volume[i]; }

  return at;
}

/* Closing Trade Summary Report Message off the wire: 113 bytes from at, returning where the next byte lies */
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
  for (size_t i = 0; i < 12; i++) { record->net_change_amount[i] = wire[at++]; }
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
  for (size_t i = 0; i < 12; i++) { assert(read->net_change_amount[i] == written->net_change_amount[i]); }
  assert(read->net_change_direction == written->net_change_direction);
  for (size_t i = 0; i < 3; i++) { assert(read->currency[i] == written->currency[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->total_security_volume[i] == written->total_security_volume[i]); }
}

/* Closing Trade Summary Report Message: written and read back, then read and written back */
static void check_closing_trade_summary_report_message(void) {
  ClosingTradeSummaryReportMessage sent;
  ClosingTradeSummaryReportMessage got;
  uint8_t wire[113];
  uint8_t again[113];

  any_closing_trade_summary_report_message(&sent);
  assert(encode_closing_trade_summary_report_message(&sent, wire, 0) == 113);
  assert(decode_closing_trade_summary_report_message(&got, wire, 0) == 113);
  equal_closing_trade_summary_report_message(&got, &sent);

  for (size_t i = 0; i < 113; i++) { wire[i] = arbitrary(); }
  assert(decode_closing_trade_summary_report_message(&got, wire, 0) == 113);
  assert(encode_closing_trade_summary_report_message(&got, again, 0) == 113);
  for (size_t i = 0; i < 113; i++) { assert(again[i] == wire[i]); }
}

/* ---- Action Datetime: 17 bytes ----------------------------------------------- */

/* Action Datetime */
typedef struct {
  uint8_t year[4];         /* bytes 0 to 3 */
  uint8_t month[2];        /* bytes 4 to 5 */
  uint8_t day[2];          /* bytes 6 to 7 */
  uint8_t hour[2];         /* bytes 8 to 9 */
  uint8_t minute[2];       /* bytes 10 to 11 */
  uint8_t second[2];       /* bytes 12 to 13 */
  uint8_t millisecond[3];  /* bytes 14 to 16 */
} ActionDatetime;

/* any Action Datetime at all: every byte one the checker chooses */
static void any_action_datetime(ActionDatetime *record) {
  for (size_t i = 0; i < 4; i++) { record->year[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->month[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->day[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->hour[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->minute[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->second[i] = arbitrary(); }
  for (size_t i = 0; i < 3; i++) { record->millisecond[i] = arbitrary(); }
}

/* Action Datetime to the wire: 17 bytes from at, returning where the next byte goes */
static size_t encode_action_datetime(const ActionDatetime *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->year[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->month[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->day[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->hour[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->minute[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->second[i]; }
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->millisecond[i]; }

  return at;
}

/* Action Datetime off the wire: 17 bytes from at, returning where the next byte lies */
static size_t decode_action_datetime(ActionDatetime *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->year[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->month[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->day[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->hour[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->minute[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->second[i] = wire[at++]; }
  for (size_t i = 0; i < 3; i++) { record->millisecond[i] = wire[at++]; }

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
  for (size_t i = 0; i < 3; i++) { assert(read->millisecond[i] == written->millisecond[i]); }
}

/* Action Datetime: written and read back, then read and written back */
static void check_action_datetime(void) {
  ActionDatetime sent;
  ActionDatetime got;
  uint8_t wire[17];
  uint8_t again[17];

  any_action_datetime(&sent);
  assert(encode_action_datetime(&sent, wire, 0) == 17);
  assert(decode_action_datetime(&got, wire, 0) == 17);
  equal_action_datetime(&got, &sent);

  for (size_t i = 0; i < 17; i++) { wire[i] = arbitrary(); }
  assert(decode_action_datetime(&got, wire, 0) == 17);
  assert(encode_action_datetime(&got, again, 0) == 17);
  for (size_t i = 0; i < 17; i++) { assert(again[i] == wire[i]); }
}

/* ---- Trading Action Message: 68 bytes ---------------------------------------- */

/* FINRA will disseminate this message to inform customers of trading actions, such as halts or trading resumptions which affect individual OTCBB or Other OTC securities */
typedef struct {
  MessageHeader message_header;           /* bytes 0 to 29 */
  uint8_t security_symbol[14];            /* bytes 30 to 43 */
  uint8_t action;                         /* byte 44 */
  ActionDatetime action_datetime;         /* bytes 45 to 61 */
  uint8_t trading_action_reason_code[6];  /* bytes 62 to 67 */
} TradingActionMessage;

/* any Trading Action Message at all: every byte one the checker chooses */
static void any_trading_action_message(TradingActionMessage *record) {
  any_message_header(&record->message_header);
  for (size_t i = 0; i < 14; i++) { record->security_symbol[i] = arbitrary(); }
  record->action = arbitrary();
  any_action_datetime(&record->action_datetime);
  for (size_t i = 0; i < 6; i++) { record->trading_action_reason_code[i] = arbitrary(); }
}

/* Trading Action Message to the wire: 68 bytes from at, returning where the next byte goes */
static size_t encode_trading_action_message(const TradingActionMessage *record, uint8_t *wire, size_t at) {
  at = encode_message_header(&record->message_header, wire, at);
  for (size_t i = 0; i < 14; i++) { wire[at++] = record->security_symbol[i]; }
  wire[at++] = record->action;
  at = encode_action_datetime(&record->action_datetime, wire, at);
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->trading_action_reason_code[i]; }

  return at;
}

/* Trading Action Message off the wire: 68 bytes from at, returning where the next byte lies */
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
  uint8_t wire[68];
  uint8_t again[68];

  any_trading_action_message(&sent);
  assert(encode_trading_action_message(&sent, wire, 0) == 68);
  assert(decode_trading_action_message(&got, wire, 0) == 68);
  equal_trading_action_message(&got, &sent);

  for (size_t i = 0; i < 68; i++) { wire[i] = arbitrary(); }
  assert(decode_trading_action_message(&got, wire, 0) == 68);
  assert(encode_trading_action_message(&got, again, 0) == 68);
  for (size_t i = 0; i < 68; i++) { assert(again[i] == wire[i]); }
}

/* ---- Market Wide Circuit Breaker Event Message: 54 bytes --------------------- */

/* FINRA will disseminate this message to inform customers of an extraordinary market event trading action or a market wide circuit breaker event which will affect all security symbols for either OTCBB, Other OTC or both OTCBB and Other OTC market places */
typedef struct {
  MessageHeader message_header;                        /* bytes 0 to 29 */
  uint8_t action;                                      /* byte 30 */
  ActionDatetime action_datetime;                      /* bytes 31 to 47 */
  uint8_t market_wide_circuit_breaker_reason_code[6];  /* bytes 48 to 53 */
} MarketWideCircuitBreakerEventMessage;

/* any Market Wide Circuit Breaker Event Message at all: every byte one the checker chooses */
static void any_market_wide_circuit_breaker_event_message(MarketWideCircuitBreakerEventMessage *record) {
  any_message_header(&record->message_header);
  record->action = arbitrary();
  any_action_datetime(&record->action_datetime);
  for (size_t i = 0; i < 6; i++) { record->market_wide_circuit_breaker_reason_code[i] = arbitrary(); }
}

/* Market Wide Circuit Breaker Event Message to the wire: 54 bytes from at, returning where the next byte goes */
static size_t encode_market_wide_circuit_breaker_event_message(const MarketWideCircuitBreakerEventMessage *record, uint8_t *wire, size_t at) {
  at = encode_message_header(&record->message_header, wire, at);
  wire[at++] = record->action;
  at = encode_action_datetime(&record->action_datetime, wire, at);
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->market_wide_circuit_breaker_reason_code[i]; }

  return at;
}

/* Market Wide Circuit Breaker Event Message off the wire: 54 bytes from at, returning where the next byte lies */
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
  uint8_t wire[54];
  uint8_t again[54];

  any_market_wide_circuit_breaker_event_message(&sent);
  assert(encode_market_wide_circuit_breaker_event_message(&sent, wire, 0) == 54);
  assert(decode_market_wide_circuit_breaker_event_message(&got, wire, 0) == 54);
  equal_market_wide_circuit_breaker_event_message(&got, &sent);

  for (size_t i = 0; i < 54; i++) { wire[i] = arbitrary(); }
  assert(decode_market_wide_circuit_breaker_event_message(&got, wire, 0) == 54);
  assert(encode_market_wide_circuit_breaker_event_message(&got, again, 0) == 54);
  for (size_t i = 0; i < 54; i++) { assert(again[i] == wire[i]); }
}

/* ---- Start Of Day Message: 30 bytes ------------------------------------------ */

/* The Start of Day control message signifies the beginning of each operational cycle for TDDS processing */
typedef struct {
  MessageHeader message_header;  /* bytes 0 to 29 */
} StartOfDayMessage;

/* any Start Of Day Message at all: every byte one the checker chooses */
static void any_start_of_day_message(StartOfDayMessage *record) {
  any_message_header(&record->message_header);
}

/* Start Of Day Message to the wire: 30 bytes from at, returning where the next byte goes */
static size_t encode_start_of_day_message(const StartOfDayMessage *record, uint8_t *wire, size_t at) {
  at = encode_message_header(&record->message_header, wire, at);

  return at;
}

/* Start Of Day Message off the wire: 30 bytes from at, returning where the next byte lies */
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
  uint8_t wire[30];
  uint8_t again[30];

  any_start_of_day_message(&sent);
  assert(encode_start_of_day_message(&sent, wire, 0) == 30);
  assert(decode_start_of_day_message(&got, wire, 0) == 30);
  equal_start_of_day_message(&got, &sent);

  for (size_t i = 0; i < 30; i++) { wire[i] = arbitrary(); }
  assert(decode_start_of_day_message(&got, wire, 0) == 30);
  assert(encode_start_of_day_message(&got, again, 0) == 30);
  for (size_t i = 0; i < 30; i++) { assert(again[i] == wire[i]); }
}

/* ---- End Of Day Message: 30 bytes -------------------------------------------- */

/* The End of Day control message signals the end of active message dissemination for the TDDS operational cycle */
typedef struct {
  MessageHeader message_header;  /* bytes 0 to 29 */
} EndOfDayMessage;

/* any End Of Day Message at all: every byte one the checker chooses */
static void any_end_of_day_message(EndOfDayMessage *record) {
  any_message_header(&record->message_header);
}

/* End Of Day Message to the wire: 30 bytes from at, returning where the next byte goes */
static size_t encode_end_of_day_message(const EndOfDayMessage *record, uint8_t *wire, size_t at) {
  at = encode_message_header(&record->message_header, wire, at);

  return at;
}

/* End Of Day Message off the wire: 30 bytes from at, returning where the next byte lies */
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
  uint8_t wire[30];
  uint8_t again[30];

  any_end_of_day_message(&sent);
  assert(encode_end_of_day_message(&sent, wire, 0) == 30);
  assert(decode_end_of_day_message(&got, wire, 0) == 30);
  equal_end_of_day_message(&got, &sent);

  for (size_t i = 0; i < 30; i++) { wire[i] = arbitrary(); }
  assert(decode_end_of_day_message(&got, wire, 0) == 30);
  assert(encode_end_of_day_message(&got, again, 0) == 30);
  for (size_t i = 0; i < 30; i++) { assert(again[i] == wire[i]); }
}

/* ---- Market Session Open Message: 30 bytes ----------------------------------- */

/* The Market Session Open Control Message signifies the opening of FINRA’s market systems for the session indicated in the Message Header */
typedef struct {
  MessageHeader message_header;  /* bytes 0 to 29 */
} MarketSessionOpenMessage;

/* any Market Session Open Message at all: every byte one the checker chooses */
static void any_market_session_open_message(MarketSessionOpenMessage *record) {
  any_message_header(&record->message_header);
}

/* Market Session Open Message to the wire: 30 bytes from at, returning where the next byte goes */
static size_t encode_market_session_open_message(const MarketSessionOpenMessage *record, uint8_t *wire, size_t at) {
  at = encode_message_header(&record->message_header, wire, at);

  return at;
}

/* Market Session Open Message off the wire: 30 bytes from at, returning where the next byte lies */
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
  uint8_t wire[30];
  uint8_t again[30];

  any_market_session_open_message(&sent);
  assert(encode_market_session_open_message(&sent, wire, 0) == 30);
  assert(decode_market_session_open_message(&got, wire, 0) == 30);
  equal_market_session_open_message(&got, &sent);

  for (size_t i = 0; i < 30; i++) { wire[i] = arbitrary(); }
  assert(decode_market_session_open_message(&got, wire, 0) == 30);
  assert(encode_market_session_open_message(&got, again, 0) == 30);
  for (size_t i = 0; i < 30; i++) { assert(again[i] == wire[i]); }
}

/* ---- Market Session Close Message: 30 bytes ---------------------------------- */

/* The Session Close Control Message signals the closing of FINRA’s market systems for the session indicated in the Message Header */
typedef struct {
  MessageHeader message_header;  /* bytes 0 to 29 */
} MarketSessionCloseMessage;

/* any Market Session Close Message at all: every byte one the checker chooses */
static void any_market_session_close_message(MarketSessionCloseMessage *record) {
  any_message_header(&record->message_header);
}

/* Market Session Close Message to the wire: 30 bytes from at, returning where the next byte goes */
static size_t encode_market_session_close_message(const MarketSessionCloseMessage *record, uint8_t *wire, size_t at) {
  at = encode_message_header(&record->message_header, wire, at);

  return at;
}

/* Market Session Close Message off the wire: 30 bytes from at, returning where the next byte lies */
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
  uint8_t wire[30];
  uint8_t again[30];

  any_market_session_close_message(&sent);
  assert(encode_market_session_close_message(&sent, wire, 0) == 30);
  assert(decode_market_session_close_message(&got, wire, 0) == 30);
  equal_market_session_close_message(&got, &sent);

  for (size_t i = 0; i < 30; i++) { wire[i] = arbitrary(); }
  assert(decode_market_session_close_message(&got, wire, 0) == 30);
  assert(encode_market_session_close_message(&got, again, 0) == 30);
  for (size_t i = 0; i < 30; i++) { assert(again[i] == wire[i]); }
}

/* ---- End Of Retransmission Requests Message: 30 bytes ------------------------ */

/* This message signals that no further retransmission requests will be honored. The End of Retransmission Requests message will be sent three times, at one-minute intervals */
typedef struct {
  MessageHeader message_header;  /* bytes 0 to 29 */
} EndOfRetransmissionRequestsMessage;

/* any End Of Retransmission Requests Message at all: every byte one the checker chooses */
static void any_end_of_retransmission_requests_message(EndOfRetransmissionRequestsMessage *record) {
  any_message_header(&record->message_header);
}

/* End Of Retransmission Requests Message to the wire: 30 bytes from at, returning where the next byte goes */
static size_t encode_end_of_retransmission_requests_message(const EndOfRetransmissionRequestsMessage *record, uint8_t *wire, size_t at) {
  at = encode_message_header(&record->message_header, wire, at);

  return at;
}

/* End Of Retransmission Requests Message off the wire: 30 bytes from at, returning where the next byte lies */
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
  uint8_t wire[30];
  uint8_t again[30];

  any_end_of_retransmission_requests_message(&sent);
  assert(encode_end_of_retransmission_requests_message(&sent, wire, 0) == 30);
  assert(decode_end_of_retransmission_requests_message(&got, wire, 0) == 30);
  equal_end_of_retransmission_requests_message(&got, &sent);

  for (size_t i = 0; i < 30; i++) { wire[i] = arbitrary(); }
  assert(decode_end_of_retransmission_requests_message(&got, wire, 0) == 30);
  assert(encode_end_of_retransmission_requests_message(&got, again, 0) == 30);
  for (size_t i = 0; i < 30; i++) { assert(again[i] == wire[i]); }
}

/* ---- End Of Transmissions Message: 30 bytes ---------------------------------- */

/* The End of Transmissions Message signals that there will be no further transmissions of data sent through the TDDS line. */
typedef struct {
  MessageHeader message_header;  /* bytes 0 to 29 */
} EndOfTransmissionsMessage;

/* any End Of Transmissions Message at all: every byte one the checker chooses */
static void any_end_of_transmissions_message(EndOfTransmissionsMessage *record) {
  any_message_header(&record->message_header);
}

/* End Of Transmissions Message to the wire: 30 bytes from at, returning where the next byte goes */
static size_t encode_end_of_transmissions_message(const EndOfTransmissionsMessage *record, uint8_t *wire, size_t at) {
  at = encode_message_header(&record->message_header, wire, at);

  return at;
}

/* End Of Transmissions Message off the wire: 30 bytes from at, returning where the next byte lies */
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
  uint8_t wire[30];
  uint8_t again[30];

  any_end_of_transmissions_message(&sent);
  assert(encode_end_of_transmissions_message(&sent, wire, 0) == 30);
  assert(decode_end_of_transmissions_message(&got, wire, 0) == 30);
  equal_end_of_transmissions_message(&got, &sent);

  for (size_t i = 0; i < 30; i++) { wire[i] = arbitrary(); }
  assert(decode_end_of_transmissions_message(&got, wire, 0) == 30);
  assert(encode_end_of_transmissions_message(&got, again, 0) == 30);
  for (size_t i = 0; i < 30; i++) { assert(again[i] == wire[i]); }
}

/* ---- Line Integrity Message: 30 bytes ---------------------------------------- */

/* The Line Integrity Control Message will be transmitted at approximately one-minute intervals to verify the operational integrity of the TDDS message transmission, and will be intermixed with other messages */
typedef struct {
  MessageHeader message_header;  /* bytes 0 to 29 */
} LineIntegrityMessage;

/* any Line Integrity Message at all: every byte one the checker chooses */
static void any_line_integrity_message(LineIntegrityMessage *record) {
  any_message_header(&record->message_header);
}

/* Line Integrity Message to the wire: 30 bytes from at, returning where the next byte goes */
static size_t encode_line_integrity_message(const LineIntegrityMessage *record, uint8_t *wire, size_t at) {
  at = encode_message_header(&record->message_header, wire, at);

  return at;
}

/* Line Integrity Message off the wire: 30 bytes from at, returning where the next byte lies */
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
  uint8_t wire[30];
  uint8_t again[30];

  any_line_integrity_message(&sent);
  assert(encode_line_integrity_message(&sent, wire, 0) == 30);
  assert(decode_line_integrity_message(&got, wire, 0) == 30);
  equal_line_integrity_message(&got, &sent);

  for (size_t i = 0; i < 30; i++) { wire[i] = arbitrary(); }
  assert(decode_line_integrity_message(&got, wire, 0) == 30);
  assert(encode_line_integrity_message(&got, again, 0) == 30);
  for (size_t i = 0; i < 30; i++) { assert(again[i] == wire[i]); }
}

/* ---- Sequence Number Reset Message: 30 bytes --------------------------------- */

/* The Sequence Number Reset Message forces the resetting of the Sequence Number. The Sequence Number will either be reset to zero or to a number greater than the last number previously transmitted */
typedef struct {
  MessageHeader message_header;  /* bytes 0 to 29 */
} SequenceNumberResetMessage;

/* any Sequence Number Reset Message at all: every byte one the checker chooses */
static void any_sequence_number_reset_message(SequenceNumberResetMessage *record) {
  any_message_header(&record->message_header);
}

/* Sequence Number Reset Message to the wire: 30 bytes from at, returning where the next byte goes */
static size_t encode_sequence_number_reset_message(const SequenceNumberResetMessage *record, uint8_t *wire, size_t at) {
  at = encode_message_header(&record->message_header, wire, at);

  return at;
}

/* Sequence Number Reset Message off the wire: 30 bytes from at, returning where the next byte lies */
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
  uint8_t wire[30];
  uint8_t again[30];

  any_sequence_number_reset_message(&sent);
  assert(encode_sequence_number_reset_message(&sent, wire, 0) == 30);
  assert(decode_sequence_number_reset_message(&got, wire, 0) == 30);
  equal_sequence_number_reset_message(&got, &sent);

  for (size_t i = 0; i < 30; i++) { wire[i] = arbitrary(); }
  assert(decode_sequence_number_reset_message(&got, wire, 0) == 30);
  assert(encode_sequence_number_reset_message(&got, again, 0) == 30);
  for (size_t i = 0; i < 30; i++) { assert(again[i] == wire[i]); }
}

/* ---- End Of Trade Reporting Message: 30 bytes -------------------------------- */

/* The End of Trade Reporting Control Message signals that the ORF system is closed for market participant trade transactions */
typedef struct {
  MessageHeader message_header;  /* bytes 0 to 29 */
} EndOfTradeReportingMessage;

/* any End Of Trade Reporting Message at all: every byte one the checker chooses */
static void any_end_of_trade_reporting_message(EndOfTradeReportingMessage *record) {
  any_message_header(&record->message_header);
}

/* End Of Trade Reporting Message to the wire: 30 bytes from at, returning where the next byte goes */
static size_t encode_end_of_trade_reporting_message(const EndOfTradeReportingMessage *record, uint8_t *wire, size_t at) {
  at = encode_message_header(&record->message_header, wire, at);

  return at;
}

/* End Of Trade Reporting Message off the wire: 30 bytes from at, returning where the next byte lies */
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
  uint8_t wire[30];
  uint8_t again[30];

  any_end_of_trade_reporting_message(&sent);
  assert(encode_end_of_trade_reporting_message(&sent, wire, 0) == 30);
  assert(decode_end_of_trade_reporting_message(&got, wire, 0) == 30);
  equal_end_of_trade_reporting_message(&got, &sent);

  for (size_t i = 0; i < 30; i++) { wire[i] = arbitrary(); }
  assert(decode_end_of_trade_reporting_message(&got, wire, 0) == 30);
  assert(encode_end_of_trade_reporting_message(&got, again, 0) == 30);
  for (size_t i = 0; i < 30; i++) { assert(again[i] == wire[i]); }
}

/* ---- What esbmc checks ------------------------------------------------------- */

/* every record of the protocol, each on its own buffers */
static void checks(void) {
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
