// finra/finraotc/bbds/FinraOtc_Bbds_v2018_1A.c
/*
 * Financial Industry Regulatory Authority Bulletin Board Dissemination Service
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
 *   - a field present only on a condition
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

/* ---- Datetime: 7 bytes ------------------------------------------------------- */

/* Datetime */
typedef struct {
  uint8_t year[2];  /* bytes 0 to 1 */
  uint8_t month;    /* byte 2 */
  uint8_t day;      /* byte 3 */
  uint8_t hour;     /* byte 4 */
  uint8_t minute;   /* byte 5 */
  uint8_t second;   /* byte 6 */
} Datetime;

/* any Datetime at all: every byte one the checker chooses */
static void any_datetime(Datetime *record) {
  for (size_t i = 0; i < 2; i++) { record->year[i] = arbitrary(); }
  record->month = arbitrary();
  record->day = arbitrary();
  record->hour = arbitrary();
  record->minute = arbitrary();
  record->second = arbitrary();
}

/* Datetime to the wire: 7 bytes from at, returning where the next byte goes */
static size_t encode_datetime(const Datetime *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->year[i]; }
  wire[at++] = record->month;
  wire[at++] = record->day;
  wire[at++] = record->hour;
  wire[at++] = record->minute;
  wire[at++] = record->second;

  return at;
}

/* Datetime off the wire: 7 bytes from at, returning where the next byte lies */
static size_t decode_datetime(Datetime *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->year[i] = wire[at++]; }
  record->month = wire[at++];
  record->day = wire[at++];
  record->hour = wire[at++];
  record->minute = wire[at++];
  record->second = wire[at++];

  return at;
}

/* what was read of Datetime is what was written, byte for byte */
static void equal_datetime(const Datetime *read, const Datetime *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->year[i] == written->year[i]); }
  assert(read->month == written->month);
  assert(read->day == written->day);
  assert(read->hour == written->hour);
  assert(read->minute == written->minute);
  assert(read->second == written->second);
}

/* Datetime: written and read back, then read and written back */
static void check_datetime(void) {
  Datetime sent;
  Datetime got;
  uint8_t wire[7];
  uint8_t again[7];

  any_datetime(&sent);
  assert(encode_datetime(&sent, wire, 0) == 7);
  assert(decode_datetime(&got, wire, 0) == 7);
  equal_datetime(&got, &sent);

  for (size_t i = 0; i < 7; i++) { wire[i] = arbitrary(); }
  assert(decode_datetime(&got, wire, 0) == 7);
  assert(encode_datetime(&got, again, 0) == 7);
  for (size_t i = 0; i < 7; i++) { assert(again[i] == wire[i]); }
}

/* ---- Message Header: 20 bytes ------------------------------------------------ */

/* Message Header */
typedef struct {
  uint8_t session_identifier;           /* byte 0 */
  uint8_t retransmission_requester[2];  /* bytes 1 to 2 */
  uint8_t message_sequence_number[8];   /* bytes 3 to 10 */
  uint8_t market_center_originator_id;  /* byte 11 */
  Datetime datetime;                    /* bytes 12 to 18 */
  uint8_t reserved_1;                   /* byte 19 */
} MessageHeader;

/* any Message Header at all: every byte one the checker chooses */
static void any_message_header(MessageHeader *record) {
  record->session_identifier = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->retransmission_requester[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->message_sequence_number[i] = arbitrary(); }
  record->market_center_originator_id = arbitrary();
  any_datetime(&record->datetime);
  record->reserved_1 = arbitrary();
}

/* Message Header to the wire: 20 bytes from at, returning where the next byte goes */
static size_t encode_message_header(const MessageHeader *record, uint8_t *wire, size_t at) {
  wire[at++] = record->session_identifier;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->retransmission_requester[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->message_sequence_number[i]; }
  wire[at++] = record->market_center_originator_id;
  at = encode_datetime(&record->datetime, wire, at);
  wire[at++] = record->reserved_1;

  return at;
}

/* Message Header off the wire: 20 bytes from at, returning where the next byte lies */
static size_t decode_message_header(MessageHeader *record, const uint8_t *wire, size_t at) {
  record->session_identifier = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->retransmission_requester[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->message_sequence_number[i] = wire[at++]; }
  record->market_center_originator_id = wire[at++];
  at = decode_datetime(&record->datetime, wire, at);
  record->reserved_1 = wire[at++];

  return at;
}

/* what was read of Message Header is what was written, byte for byte */
static void equal_message_header(const MessageHeader *read, const MessageHeader *written) {
  assert(read->session_identifier == written->session_identifier);
  for (size_t i = 0; i < 2; i++) { assert(read->retransmission_requester[i] == written->retransmission_requester[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->message_sequence_number[i] == written->message_sequence_number[i]); }
  assert(read->market_center_originator_id == written->market_center_originator_id);
  equal_datetime(&read->datetime, &written->datetime);
  assert(read->reserved_1 == written->reserved_1);
}

/* Message Header: written and read back, then read and written back */
static void check_message_header(void) {
  MessageHeader sent;
  MessageHeader got;
  uint8_t wire[20];
  uint8_t again[20];

  any_message_header(&sent);
  assert(encode_message_header(&sent, wire, 0) == 20);
  assert(decode_message_header(&got, wire, 0) == 20);
  equal_message_header(&got, &sent);

  for (size_t i = 0; i < 20; i++) { wire[i] = arbitrary(); }
  assert(decode_message_header(&got, wire, 0) == 20);
  assert(encode_message_header(&got, again, 0) == 20);
  for (size_t i = 0; i < 20; i++) { assert(again[i] == wire[i]); }
}

/* ---- Action Datetime: 7 bytes ------------------------------------------------ */

/* Action Datetime */
typedef struct {
  uint8_t year[2];  /* bytes 0 to 1 */
  uint8_t month;    /* byte 2 */
  uint8_t day;      /* byte 3 */
  uint8_t hour;     /* byte 4 */
  uint8_t minute;   /* byte 5 */
  uint8_t second;   /* byte 6 */
} ActionDatetime;

/* any Action Datetime at all: every byte one the checker chooses */
static void any_action_datetime(ActionDatetime *record) {
  for (size_t i = 0; i < 2; i++) { record->year[i] = arbitrary(); }
  record->month = arbitrary();
  record->day = arbitrary();
  record->hour = arbitrary();
  record->minute = arbitrary();
  record->second = arbitrary();
}

/* Action Datetime to the wire: 7 bytes from at, returning where the next byte goes */
static size_t encode_action_datetime(const ActionDatetime *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->year[i]; }
  wire[at++] = record->month;
  wire[at++] = record->day;
  wire[at++] = record->hour;
  wire[at++] = record->minute;
  wire[at++] = record->second;

  return at;
}

/* Action Datetime off the wire: 7 bytes from at, returning where the next byte lies */
static size_t decode_action_datetime(ActionDatetime *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->year[i] = wire[at++]; }
  record->month = wire[at++];
  record->day = wire[at++];
  record->hour = wire[at++];
  record->minute = wire[at++];
  record->second = wire[at++];

  return at;
}

/* what was read of Action Datetime is what was written, byte for byte */
static void equal_action_datetime(const ActionDatetime *read, const ActionDatetime *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->year[i] == written->year[i]); }
  assert(read->month == written->month);
  assert(read->day == written->day);
  assert(read->hour == written->hour);
  assert(read->minute == written->minute);
  assert(read->second == written->second);
}

/* Action Datetime: written and read back, then read and written back */
static void check_action_datetime(void) {
  ActionDatetime sent;
  ActionDatetime got;
  uint8_t wire[7];
  uint8_t again[7];

  any_action_datetime(&sent);
  assert(encode_action_datetime(&sent, wire, 0) == 7);
  assert(decode_action_datetime(&got, wire, 0) == 7);
  equal_action_datetime(&got, &sent);

  for (size_t i = 0; i < 7; i++) { wire[i] = arbitrary(); }
  assert(decode_action_datetime(&got, wire, 0) == 7);
  assert(encode_action_datetime(&got, again, 0) == 7);
  for (size_t i = 0; i < 7; i++) { assert(again[i] == wire[i]); }
}

/* ---- Trading Action Message: 45 bytes ---------------------------------------- */

/* FINRA will disseminate this message to inform customers of trading actions, such as halts or trading resumptions which affect individual OTCBB or Other OTC securities */
typedef struct {
  MessageHeader message_header;    /* bytes 0 to 19 */
  uint8_t stock_symbol[11];        /* bytes 20 to 30 */
  uint8_t action;                  /* byte 31 */
  ActionDatetime action_datetime;  /* bytes 32 to 38 */
  uint8_t reason_code[6];          /* bytes 39 to 44 */
} TradingActionMessage;

/* any Trading Action Message at all: every byte one the checker chooses */
static void any_trading_action_message(TradingActionMessage *record) {
  any_message_header(&record->message_header);
  for (size_t i = 0; i < 11; i++) { record->stock_symbol[i] = arbitrary(); }
  record->action = arbitrary();
  any_action_datetime(&record->action_datetime);
  for (size_t i = 0; i < 6; i++) { record->reason_code[i] = arbitrary(); }
}

/* Trading Action Message to the wire: 45 bytes from at, returning where the next byte goes */
static size_t encode_trading_action_message(const TradingActionMessage *record, uint8_t *wire, size_t at) {
  at = encode_message_header(&record->message_header, wire, at);
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->stock_symbol[i]; }
  wire[at++] = record->action;
  at = encode_action_datetime(&record->action_datetime, wire, at);
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->reason_code[i]; }

  return at;
}

/* Trading Action Message off the wire: 45 bytes from at, returning where the next byte lies */
static size_t decode_trading_action_message(TradingActionMessage *record, const uint8_t *wire, size_t at) {
  at = decode_message_header(&record->message_header, wire, at);
  for (size_t i = 0; i < 11; i++) { record->stock_symbol[i] = wire[at++]; }
  record->action = wire[at++];
  at = decode_action_datetime(&record->action_datetime, wire, at);
  for (size_t i = 0; i < 6; i++) { record->reason_code[i] = wire[at++]; }

  return at;
}

/* what was read of Trading Action Message is what was written, byte for byte */
static void equal_trading_action_message(const TradingActionMessage *read, const TradingActionMessage *written) {
  equal_message_header(&read->message_header, &written->message_header);
  for (size_t i = 0; i < 11; i++) { assert(read->stock_symbol[i] == written->stock_symbol[i]); }
  assert(read->action == written->action);
  equal_action_datetime(&read->action_datetime, &written->action_datetime);
  for (size_t i = 0; i < 6; i++) { assert(read->reason_code[i] == written->reason_code[i]); }
}

/* Trading Action Message: written and read back, then read and written back */
static void check_trading_action_message(void) {
  TradingActionMessage sent;
  TradingActionMessage got;
  uint8_t wire[45];
  uint8_t again[45];

  any_trading_action_message(&sent);
  assert(encode_trading_action_message(&sent, wire, 0) == 45);
  assert(decode_trading_action_message(&got, wire, 0) == 45);
  equal_trading_action_message(&got, &sent);

  for (size_t i = 0; i < 45; i++) { wire[i] = arbitrary(); }
  assert(decode_trading_action_message(&got, wire, 0) == 45);
  assert(encode_trading_action_message(&got, again, 0) == 45);
  for (size_t i = 0; i < 45; i++) { assert(again[i] == wire[i]); }
}

/* ---- Start Of Day Message: 20 bytes ------------------------------------------ */

/* The Start of Day control message signifies the beginning of each operational cycle for TDDS processing */
typedef struct {
  MessageHeader message_header;  /* bytes 0 to 19 */
} StartOfDayMessage;

/* any Start Of Day Message at all: every byte one the checker chooses */
static void any_start_of_day_message(StartOfDayMessage *record) {
  any_message_header(&record->message_header);
}

/* Start Of Day Message to the wire: 20 bytes from at, returning where the next byte goes */
static size_t encode_start_of_day_message(const StartOfDayMessage *record, uint8_t *wire, size_t at) {
  at = encode_message_header(&record->message_header, wire, at);

  return at;
}

/* Start Of Day Message off the wire: 20 bytes from at, returning where the next byte lies */
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
  uint8_t wire[20];
  uint8_t again[20];

  any_start_of_day_message(&sent);
  assert(encode_start_of_day_message(&sent, wire, 0) == 20);
  assert(decode_start_of_day_message(&got, wire, 0) == 20);
  equal_start_of_day_message(&got, &sent);

  for (size_t i = 0; i < 20; i++) { wire[i] = arbitrary(); }
  assert(decode_start_of_day_message(&got, wire, 0) == 20);
  assert(encode_start_of_day_message(&got, again, 0) == 20);
  for (size_t i = 0; i < 20; i++) { assert(again[i] == wire[i]); }
}

/* ---- End Of Day Message: 20 bytes -------------------------------------------- */

/* The End of Day control message signals the end of active message dissemination for the TDDS operational cycle */
typedef struct {
  MessageHeader message_header;  /* bytes 0 to 19 */
} EndOfDayMessage;

/* any End Of Day Message at all: every byte one the checker chooses */
static void any_end_of_day_message(EndOfDayMessage *record) {
  any_message_header(&record->message_header);
}

/* End Of Day Message to the wire: 20 bytes from at, returning where the next byte goes */
static size_t encode_end_of_day_message(const EndOfDayMessage *record, uint8_t *wire, size_t at) {
  at = encode_message_header(&record->message_header, wire, at);

  return at;
}

/* End Of Day Message off the wire: 20 bytes from at, returning where the next byte lies */
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
  uint8_t wire[20];
  uint8_t again[20];

  any_end_of_day_message(&sent);
  assert(encode_end_of_day_message(&sent, wire, 0) == 20);
  assert(decode_end_of_day_message(&got, wire, 0) == 20);
  equal_end_of_day_message(&got, &sent);

  for (size_t i = 0; i < 20; i++) { wire[i] = arbitrary(); }
  assert(decode_end_of_day_message(&got, wire, 0) == 20);
  assert(encode_end_of_day_message(&got, again, 0) == 20);
  for (size_t i = 0; i < 20; i++) { assert(again[i] == wire[i]); }
}

/* ---- Market Session Open Message: 20 bytes ----------------------------------- */

/* The Market Session Open Control Message signifies the opening of FINRA’s market systems for the session indicated in the Message Header */
typedef struct {
  MessageHeader message_header;  /* bytes 0 to 19 */
} MarketSessionOpenMessage;

/* any Market Session Open Message at all: every byte one the checker chooses */
static void any_market_session_open_message(MarketSessionOpenMessage *record) {
  any_message_header(&record->message_header);
}

/* Market Session Open Message to the wire: 20 bytes from at, returning where the next byte goes */
static size_t encode_market_session_open_message(const MarketSessionOpenMessage *record, uint8_t *wire, size_t at) {
  at = encode_message_header(&record->message_header, wire, at);

  return at;
}

/* Market Session Open Message off the wire: 20 bytes from at, returning where the next byte lies */
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
  uint8_t wire[20];
  uint8_t again[20];

  any_market_session_open_message(&sent);
  assert(encode_market_session_open_message(&sent, wire, 0) == 20);
  assert(decode_market_session_open_message(&got, wire, 0) == 20);
  equal_market_session_open_message(&got, &sent);

  for (size_t i = 0; i < 20; i++) { wire[i] = arbitrary(); }
  assert(decode_market_session_open_message(&got, wire, 0) == 20);
  assert(encode_market_session_open_message(&got, again, 0) == 20);
  for (size_t i = 0; i < 20; i++) { assert(again[i] == wire[i]); }
}

/* ---- Market Session Close Message: 20 bytes ---------------------------------- */

/* The Session Close Control Message signals the closing of FINRA’s market systems for the session indicated in the Message Header */
typedef struct {
  MessageHeader message_header;  /* bytes 0 to 19 */
} MarketSessionCloseMessage;

/* any Market Session Close Message at all: every byte one the checker chooses */
static void any_market_session_close_message(MarketSessionCloseMessage *record) {
  any_message_header(&record->message_header);
}

/* Market Session Close Message to the wire: 20 bytes from at, returning where the next byte goes */
static size_t encode_market_session_close_message(const MarketSessionCloseMessage *record, uint8_t *wire, size_t at) {
  at = encode_message_header(&record->message_header, wire, at);

  return at;
}

/* Market Session Close Message off the wire: 20 bytes from at, returning where the next byte lies */
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
  uint8_t wire[20];
  uint8_t again[20];

  any_market_session_close_message(&sent);
  assert(encode_market_session_close_message(&sent, wire, 0) == 20);
  assert(decode_market_session_close_message(&got, wire, 0) == 20);
  equal_market_session_close_message(&got, &sent);

  for (size_t i = 0; i < 20; i++) { wire[i] = arbitrary(); }
  assert(decode_market_session_close_message(&got, wire, 0) == 20);
  assert(encode_market_session_close_message(&got, again, 0) == 20);
  for (size_t i = 0; i < 20; i++) { assert(again[i] == wire[i]); }
}

/* ---- End Of Retransmission Requests Message: 20 bytes ------------------------ */

/* This message signals that no further retransmission requests will be honored. The End of Retransmission Requests message will be sent three times, at one-minute intervals */
typedef struct {
  MessageHeader message_header;  /* bytes 0 to 19 */
} EndOfRetransmissionRequestsMessage;

/* any End Of Retransmission Requests Message at all: every byte one the checker chooses */
static void any_end_of_retransmission_requests_message(EndOfRetransmissionRequestsMessage *record) {
  any_message_header(&record->message_header);
}

/* End Of Retransmission Requests Message to the wire: 20 bytes from at, returning where the next byte goes */
static size_t encode_end_of_retransmission_requests_message(const EndOfRetransmissionRequestsMessage *record, uint8_t *wire, size_t at) {
  at = encode_message_header(&record->message_header, wire, at);

  return at;
}

/* End Of Retransmission Requests Message off the wire: 20 bytes from at, returning where the next byte lies */
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
  uint8_t wire[20];
  uint8_t again[20];

  any_end_of_retransmission_requests_message(&sent);
  assert(encode_end_of_retransmission_requests_message(&sent, wire, 0) == 20);
  assert(decode_end_of_retransmission_requests_message(&got, wire, 0) == 20);
  equal_end_of_retransmission_requests_message(&got, &sent);

  for (size_t i = 0; i < 20; i++) { wire[i] = arbitrary(); }
  assert(decode_end_of_retransmission_requests_message(&got, wire, 0) == 20);
  assert(encode_end_of_retransmission_requests_message(&got, again, 0) == 20);
  for (size_t i = 0; i < 20; i++) { assert(again[i] == wire[i]); }
}

/* ---- End Of Transmissions Message: 20 bytes ---------------------------------- */

/* The End of Transmissions Message signals that there will be no further transmissions of data sent through the TDDS line. */
typedef struct {
  MessageHeader message_header;  /* bytes 0 to 19 */
} EndOfTransmissionsMessage;

/* any End Of Transmissions Message at all: every byte one the checker chooses */
static void any_end_of_transmissions_message(EndOfTransmissionsMessage *record) {
  any_message_header(&record->message_header);
}

/* End Of Transmissions Message to the wire: 20 bytes from at, returning where the next byte goes */
static size_t encode_end_of_transmissions_message(const EndOfTransmissionsMessage *record, uint8_t *wire, size_t at) {
  at = encode_message_header(&record->message_header, wire, at);

  return at;
}

/* End Of Transmissions Message off the wire: 20 bytes from at, returning where the next byte lies */
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
  uint8_t wire[20];
  uint8_t again[20];

  any_end_of_transmissions_message(&sent);
  assert(encode_end_of_transmissions_message(&sent, wire, 0) == 20);
  assert(decode_end_of_transmissions_message(&got, wire, 0) == 20);
  equal_end_of_transmissions_message(&got, &sent);

  for (size_t i = 0; i < 20; i++) { wire[i] = arbitrary(); }
  assert(decode_end_of_transmissions_message(&got, wire, 0) == 20);
  assert(encode_end_of_transmissions_message(&got, again, 0) == 20);
  for (size_t i = 0; i < 20; i++) { assert(again[i] == wire[i]); }
}

/* ---- Line Integrity Message: 20 bytes ---------------------------------------- */

/* The Line Integrity Control Message will be transmitted at approximately one-minute intervals to verify the operational integrity of the TDDS message transmission, and will be intermixed with other messages */
typedef struct {
  MessageHeader message_header;  /* bytes 0 to 19 */
} LineIntegrityMessage;

/* any Line Integrity Message at all: every byte one the checker chooses */
static void any_line_integrity_message(LineIntegrityMessage *record) {
  any_message_header(&record->message_header);
}

/* Line Integrity Message to the wire: 20 bytes from at, returning where the next byte goes */
static size_t encode_line_integrity_message(const LineIntegrityMessage *record, uint8_t *wire, size_t at) {
  at = encode_message_header(&record->message_header, wire, at);

  return at;
}

/* Line Integrity Message off the wire: 20 bytes from at, returning where the next byte lies */
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
  uint8_t wire[20];
  uint8_t again[20];

  any_line_integrity_message(&sent);
  assert(encode_line_integrity_message(&sent, wire, 0) == 20);
  assert(decode_line_integrity_message(&got, wire, 0) == 20);
  equal_line_integrity_message(&got, &sent);

  for (size_t i = 0; i < 20; i++) { wire[i] = arbitrary(); }
  assert(decode_line_integrity_message(&got, wire, 0) == 20);
  assert(encode_line_integrity_message(&got, again, 0) == 20);
  for (size_t i = 0; i < 20; i++) { assert(again[i] == wire[i]); }
}

/* ---- Sequence Number Reset Message: 20 bytes --------------------------------- */

/* The Sequence Number Reset Message forces the resetting of the Sequence Number. The Sequence Number will either be reset to zero or to a number greater than the last number previously transmitted */
typedef struct {
  MessageHeader message_header;  /* bytes 0 to 19 */
} SequenceNumberResetMessage;

/* any Sequence Number Reset Message at all: every byte one the checker chooses */
static void any_sequence_number_reset_message(SequenceNumberResetMessage *record) {
  any_message_header(&record->message_header);
}

/* Sequence Number Reset Message to the wire: 20 bytes from at, returning where the next byte goes */
static size_t encode_sequence_number_reset_message(const SequenceNumberResetMessage *record, uint8_t *wire, size_t at) {
  at = encode_message_header(&record->message_header, wire, at);

  return at;
}

/* Sequence Number Reset Message off the wire: 20 bytes from at, returning where the next byte lies */
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
  uint8_t wire[20];
  uint8_t again[20];

  any_sequence_number_reset_message(&sent);
  assert(encode_sequence_number_reset_message(&sent, wire, 0) == 20);
  assert(decode_sequence_number_reset_message(&got, wire, 0) == 20);
  equal_sequence_number_reset_message(&got, &sent);

  for (size_t i = 0; i < 20; i++) { wire[i] = arbitrary(); }
  assert(decode_sequence_number_reset_message(&got, wire, 0) == 20);
  assert(encode_sequence_number_reset_message(&got, again, 0) == 20);
  for (size_t i = 0; i < 20; i++) { assert(again[i] == wire[i]); }
}

/* ---- End Of Trade Reporting Message: 20 bytes -------------------------------- */

/* The End of Trade Reporting Control Message signals that the ORF system is closed for market participant trade transactions */
typedef struct {
  MessageHeader message_header;  /* bytes 0 to 19 */
} EndOfTradeReportingMessage;

/* any End Of Trade Reporting Message at all: every byte one the checker chooses */
static void any_end_of_trade_reporting_message(EndOfTradeReportingMessage *record) {
  any_message_header(&record->message_header);
}

/* End Of Trade Reporting Message to the wire: 20 bytes from at, returning where the next byte goes */
static size_t encode_end_of_trade_reporting_message(const EndOfTradeReportingMessage *record, uint8_t *wire, size_t at) {
  at = encode_message_header(&record->message_header, wire, at);

  return at;
}

/* End Of Trade Reporting Message off the wire: 20 bytes from at, returning where the next byte lies */
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
  uint8_t wire[20];
  uint8_t again[20];

  any_end_of_trade_reporting_message(&sent);
  assert(encode_end_of_trade_reporting_message(&sent, wire, 0) == 20);
  assert(decode_end_of_trade_reporting_message(&got, wire, 0) == 20);
  equal_end_of_trade_reporting_message(&got, &sent);

  for (size_t i = 0; i < 20; i++) { wire[i] = arbitrary(); }
  assert(decode_end_of_trade_reporting_message(&got, wire, 0) == 20);
  assert(encode_end_of_trade_reporting_message(&got, again, 0) == 20);
  for (size_t i = 0; i < 20; i++) { assert(again[i] == wire[i]); }
}

/* ---- What esbmc checks ------------------------------------------------------- */

/* every record of the protocol, each on its own buffers */
static void checks(void) {
  check_datetime();
  check_message_header();
  check_action_datetime();
  check_trading_action_message();
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
